from pyradioconfig.parts.jumbo.profiles.profile_wisun_fan_1_1 import ProfileWisunFan1v1Jumbo
from pyradioconfig.parts.common.profiles.ocelot_regs import build_modem_regs_ocelot
from pyradioconfig.parts.common.profiles.profile_common import buildCrcOutputs, buildFecOutputs, buildFrameOutputs, \
    buildWhiteOutputs
from pyradioconfig.parts.common.utils.units_multiplier import UnitsMultiplier
from pycalcmodel.core.output import ModelOutput, ModelOutputType
from pyradioconfig.parts.ocelot.profiles.sw_profile_outputs_common import sw_profile_outputs_common_ocelot
from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr


class ProfileWisunFan1v1Ocelot(ProfileWisunFan1v1Jumbo):

    def __init__(self):
        super().__init__()
        self._family = "ocelot"
        self._sw_profile_outputs_common = sw_profile_outputs_common_ocelot()

    def buildProfileModel(self, model):
        # Build profile object and append it to the model
        profile = self._makeProfile(model)

        # Build inputs
        self.build_required_profile_inputs(model, profile)
        self.build_optional_profile_inputs(model, profile)
        self.build_advanced_profile_inputs(model, profile)
        self.build_hidden_profile_inputs(model, profile)
        self.build_deprecated_profile_inputs(model, profile)

        # Build outputs
        self.build_register_profile_outputs(model, profile)
        self.build_variable_profile_outputs(model, profile)
        self.build_info_profile_outputs(model, profile)

        self._sw_profile_outputs_common.buildStudioLogOutput(model, profile)

        return profile

    def build_required_profile_inputs(self, model, profile):

        self.make_required_input(profile, model.vars.wisun_reg_domain, "WiSUN",
                                     readable_name="Wi-SUN Regulatory Domain")

        self.make_required_input(profile, model.vars.wisun_phy_mode_id_select, "WiSUN",
                                     readable_name="Wi-SUN PHY Operating Mode ID")

        self.make_required_input(profile, model.vars.wisun_channel_plan_id, "WiSUN",
                                     readable_name="Wi-SUN Channel Plan ID")

        self.make_required_input(profile, model.vars.xtal_frequency_hz, "crystal",
                                     readable_name="Crystal Frequency", value_limit_min=38000000,
                                     value_limit_max=40000000, units_multiplier=UnitsMultiplier.MEGA)

    def build_advanced_profile_inputs(self, model, profile):
        #Start with the same advanced inputs as Series 1
        super().build_advanced_profile_inputs(model, profile)

        #Add antenna diversity inputs
        self.make_linked_io(profile, model.vars.antdivmode, 'Advanced', readable_name="Antenna diversity mode")
        self.make_linked_io(profile, model.vars.antdivrepeatdis, 'Advanced', readable_name="Diversity Select-Best repeat")
        self.make_linked_io(profile, model.vars.skip2ant, 'Advanced', 'Skip 2nd antenna check with phase demod antenna diversity')

    def build_hidden_profile_inputs(self, model, profile):
        # Hidden inputs to allow for fixed frame length testing
        self.make_hidden_input(profile, model.vars.frame_length_type, 'frame_general',
                                   readable_name="Frame Length Algorithm")
        self.make_hidden_input(profile, model.vars.fixed_length_size, category='frame_fixed_length',
                                   readable_name="Fixed Payload Size", value_limit_min=0, value_limit_max=0x7fffffff)

        # Hidden inputs to allow for keeping absolute tolerance the same when testing at 915M
        self.make_hidden_input(profile, model.vars.rx_xtal_error_ppm, category="general",
                                   readable_name="Set desired xtal tolerance on RX side", value_limit_min=0,
                                   value_limit_max=100)
        self.make_hidden_input(profile, model.vars.tx_xtal_error_ppm, category="general",
                                   readable_name="Set desired xtal tolerance on TX side", value_limit_min=0,
                                   value_limit_max=100)
        self.make_hidden_input(profile, model.vars.freq_offset_hz, 'Advanced',
                                   readable_name="Frequency Offset Compensation (AFC) Limit", value_limit_min=0,
                                   value_limit_max=500000, units_multiplier=UnitsMultiplier.KILO)

        # Hidden inputs to allow for control of channel BW (CSMA-CA)
        bandwidth_limit_adc = 2530000
        self.make_hidden_input(profile, model.vars.bandwidth_hz, 'Advanced',
                               readable_name="Acquisition Channel Bandwidth", value_limit_min=0,
                               value_limit_max=bandwidth_limit_adc, units_multiplier=UnitsMultiplier.KILO)
        self.make_hidden_input(profile, model.vars.if_frequency_hz, 'Advanced',
                               readable_name="IF Frequency", value_limit_min=70000, value_limit_max=1900000,
                               units_multiplier=UnitsMultiplier.KILO)
        self.make_hidden_input(profile, model.vars.afc_run_mode, 'Advanced',
                               readable_name="AFC Run Mode")

        self.make_hidden_input(profile, model.vars.modulation_index_for_ksi, "Advanced",
                               readable_name="Modulation index used by ksi calculation",
                               value_limit_min=0.0, value_limit_max=5.0, fractional_digits=2)

    def build_register_profile_outputs(self, model, profile):
        # Overriding this method to include modem regs for Ocelot
        family = self._family
        build_modem_regs_ocelot(model, profile)
        buildFrameOutputs(model, profile)
        buildCrcOutputs(model, profile)
        buildWhiteOutputs(model, profile)
        buildFecOutputs(model, profile)

    def build_variable_profile_outputs(self, model, profile):
        self._sw_profile_outputs_common.build_rail_outputs(model, profile)
        self._sw_profile_outputs_common.build_ircal_outputs(model, profile)
        profile.outputs.append(ModelOutput(model.vars.wisun_phy_mode_id, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='WiSUN PhyModeID'))
        profile.outputs.append(ModelOutput(model.vars.wisun_mode_switch_phr, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='WiSUN Mode Switch PHR'))
        profile.outputs.append(ModelOutput(model.vars.bch_lut_data, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='BCH lookup table for error correction'))


    def _fixed_wisun_vars(self, model):
        #Start with the inherited vars
        super()._fixed_wisun_vars(model)

        #Add deviation tolerance and xtal error for Ocelot
        model.vars.deviation_tol_ppm.value_forced = 300000
        model.vars.rx_xtal_error_ppm.value_forced = 20  # FAN EU Mode #1b, WiSUN 20140727-PHY-Profile Table 7 (assume RX=TX value)
        model.vars.tx_xtal_error_ppm.value_forced = 20  # FAN EU Mode #1b, WiSUN 20140727-PHY-Profile Table 7 (assume RX=TX value)

    def _fixed_wisun_thresholds(self, model):
        #No hard-coded thresholds on Ocelot
        pass

    def _fixed_wisun_agc(self, model):
        #No hard-coded AGC settings on Ocelot
        pass

    def _lookup_from_wisun_mode(self, model):
        # This function calculates some variables/registers based on the PhyModeID

        # Read the profile inputs (not yet written to model vars)
        wisun_phy_mode_id_select = model.profile.inputs.wisun_phy_mode_id_select.var_value.value
        shaping_filter = model.profile.inputs.shaping_filter.var_value
        shaping_filter_param = model.profile.inputs.shaping_filter_param.var_value
        payload_white_en = model.profile.inputs.payload_white_en.var_value

        PhyType = wisun_phy_mode_id_select >> 4  # Top 4 bits of PhyModeID
        PhyMode = wisun_phy_mode_id_select & 0xF  # Bottom 4 bits of PhyModeID

        # Set FEC enable and modulation type based on PhyType
        if PhyType == 0:
            # FSK without FEC
            fec_tx_enable = model.vars.fec_tx_enable.var_enum.DISABLED
            modulation_type = model.vars.modulation_type.var_enum.FSK2
        else:
            fec_tx_enable = model.vars.fec_tx_enable.var_enum.ENABLED
            modulation_type = model.vars.modulation_type.var_enum.FSK2

        # Set the FEC TX enable and modulation type vars
        model.vars.fec_tx_enable.value_forced = fec_tx_enable
        model.vars.modulation_type.value_forced = modulation_type

        # Set defaults for shaping and whitening (for FSK)
        if shaping_filter is None:
            model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.Gaussian
        if shaping_filter_param is None:
            model.vars.shaping_filter_param.value_forced = 2.0
        if payload_white_en is None:
            model.vars.payload_white_en.value_forced = True

        # We need to modify the net bitrate (data rate) based on whether FEC is enabled or not
        fec_factor = 2 if fec_tx_enable else 1

        # Set bitrate and deviation based on PhyMode

        error = False
        if PhyMode <= 1:
            # Mode1a
            model.vars.bitrate.value_forced = 50000//fec_factor
            model.vars.deviation.value_forced = 12500
            model.vars.MODEM_REALTIMCFE_RTSCHWIN.value_forced = 4
            model.vars.MODEM_TRECPMDET_PMCOSTVALTHD.value_forced = 3
            model.vars.preamble_length.value_forced = 8 * 8

            if PhyMode == 0:
                # Unsupported
                error = True

        elif PhyMode == 2:
            # Mode1b
            model.vars.bitrate.value_forced = 50000//fec_factor
            model.vars.deviation.value_forced = 25000
            model.vars.preamble_length.value_forced = 8 * 8

        elif PhyMode == 3:
            # Mode2a
            model.vars.bitrate.value_forced = 100000//fec_factor
            model.vars.deviation.value_forced = 25000
            model.vars.preamble_length.value_forced = 8 * 8


        elif PhyMode == 4:
            # Mode2b
            model.vars.bitrate.value_forced = 100000//fec_factor
            model.vars.deviation.value_forced = 50000
            model.vars.preamble_length.value_forced = 8 * 8


        elif PhyMode == 5:
            # Mode3
            model.vars.bitrate.value_forced = 150000//fec_factor
            model.vars.deviation.value_forced = 37500
            model.vars.preamble_length.value_forced = 12 * 8

        elif PhyMode == 6:
            # Mode4a
            model.vars.bitrate.value_forced = 200000//fec_factor
            model.vars.deviation.value_forced = 50000
            model.vars.preamble_length.value_forced = 12 * 8


        elif PhyMode == 7:
            # Mode4b
            model.vars.bitrate.value_forced = 200000//fec_factor
            model.vars.deviation.value_forced = 100000
            model.vars.preamble_length.value_forced = 12 * 8


        else:
            # Mode5
            model.vars.bitrate.value_forced = 300000//fec_factor
            model.vars.deviation.value_forced = 75000
            model.vars.preamble_length.value_forced = 24 * 8

            if PhyMode > 8:
                # Unsupported
                error = True

        if error:
            LogMgr.Error("Error: Unsupported Wi-SUN PhyModeID for this part")

    def _lookup_syncword_from_fec(self, model):
        # This function sets sync0 and sync1 based on whether FEC is enabled or not
        # This is because we need sync0 to be correct for the active FEC setting (RAIL assumes this)

        # This is set in the _lookup_from_wisun_mode()
        fec_tx_enable = model.vars.fec_tx_enable.value

        # Lookup the syncword to use
        if fec_tx_enable == model.vars.fec_tx_enable.var_enum.DISABLED:
            # Not compatible with dynamic FEC, uncoded as sync0
            syncword_0 = self.phySunFskSfd_0_uncoded
            syncword_1 = self.phySunFskSfd_0_uncoded  # Populating to keep PHY as dual sync detect
        else:
            # Dynamic FEC ready with coded as sync0
            syncword_0 = self.phySunFskSfd_0_coded
            syncword_1 = self.phySunFskSfd_0_uncoded

        model.vars.syncword_0.value_forced = syncword_0
        model.vars.syncword_1.value_forced = syncword_1

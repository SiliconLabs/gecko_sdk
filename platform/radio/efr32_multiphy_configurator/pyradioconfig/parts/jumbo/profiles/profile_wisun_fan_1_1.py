from pyradioconfig.calculator_model_framework.interfaces.iprofile import IProfile
from pyradioconfig.parts.common.utils.units_multiplier import UnitsMultiplier
from pyradioconfig.parts.common.profiles.jumbo_regs import build_modem_regs_jumbo
from pyradioconfig.parts.common.profiles.profile_modem import buildModemInfoOutputs, buildRailOutputs
from pyradioconfig.parts.common.profiles.profile_common import buildCrcOutputs, buildFecOutputs, buildFrameOutputs, \
    buildWhiteOutputs, build_ircal_sw_vars, buildStudioLogOutput
from pycalcmodel.core.output import ModelOutput, ModelOutputType
from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr
from collections import namedtuple

chplan_id_params = namedtuple('chplan_id_params', ['enum_name', 'b_freq_hz', 'chsp_hz'])

class ProfileWisunFan1v1Jumbo(IProfile):

    phySunFskSfd_0_uncoded = 0b1001000001001110
    phySunFskSfd_1_uncoded = 0b0111101000001110
    phySunFskSfd_0_coded = 0b0110111101001110
    phySunFskSfd_1_coded = 0b0110001100101101

    # Below info is from WiSUN FAN TPS 2v01, Table 6
    wisun_1v1_chplan_table = {
        # wisun_channel_plan_id: chplan_id_params(enum_name, base_frequency_hz, channel_spacing_hz)

        1:   chplan_id_params('Plan1_902M_928M_200k', 902.2e6, 200e3),
        2:   chplan_id_params('Plan2_902M_928M_400k', 902.4e6, 400e3),
        3:   chplan_id_params('Plan3_902M_928M_600k', 902.6e6, 600e3),
        4:   chplan_id_params('Plan4_902M_928M_800k', 902.8e6, 800e3),
        5:   chplan_id_params('Plan5_902M_928M_1200k', 903.2e6, 1.2e6),
        21:  chplan_id_params('Plan21_920M_928M_200k', 920.6e6, 200e3),
        22:  chplan_id_params('Plan22_920M_928M_400k', 920.9e6, 400e3),
        23:  chplan_id_params('Plan23_920M_928M_600k', 920.8e6, 600e3),
        24:  chplan_id_params('Plan24_920M_928M_800k', 921.1e6, 800e3),
        32:  chplan_id_params('Plan32_863M_870M_100k', 863.1e6, 100e3),
        33:  chplan_id_params('Plan33_863M_870M_200k', 863.1e6, 200e3),
        34:  chplan_id_params('Plan34_870M_876M_100k', 870.1e6, 100e3),
        35:  chplan_id_params('Plan35_870M_876M_200k', 870.2e6, 200e3),
        36:  chplan_id_params('Plan36_863M_876M_100k', 863.1e6, 100e3),
        37:  chplan_id_params('Plan37_863M_876M_200k', 863.1e6, 200e3),
        38:  chplan_id_params('Plan38_863M_870M_400k', 863.5e6, 400e3),
        39:  chplan_id_params('Plan39_865M_868M_100k', 865.1e6, 100e3),
        40:  chplan_id_params('Plan40_865M_868M_200k', 865.1e6, 200e3),
        48:  chplan_id_params('Plan48_915M_928M_200k', 915.2e6, 200e3),
        49:  chplan_id_params('Plan49_915M_928M_400k', 915.4e6, 400e3),
        64:  chplan_id_params('Plan64_920M_925M_200k', 920.2e6, 200e3),
        65:  chplan_id_params('Plan65_920M_925M_400k', 920.4e6, 400e3),
        80:  chplan_id_params('Plan80_919M_923M_200k', 919.2e6, 200e3),
        81:  chplan_id_params('Plan81_919M_923M_400k', 919.2e6, 400e3),
        96:  chplan_id_params('Plan96_917M_923M_200k', 917.1e6, 200e3),
        97:  chplan_id_params('Plan97_917M_923M_400k', 917.3e6, 400e3),

        # WW chplan definition conflict - see https://jira.silabs.com/browse/MCUW_RADIO_CFG-2183
        # We will stick to what's coherent throughout calculator
        112: chplan_id_params('Plan112_2400M_2483M_200k', 2400.4e6, 200e3),
        113: chplan_id_params('Plan113_2400M_2483M_400k', 2400.2e6, 400e3),

        128: chplan_id_params('Plan128_920M_925M_250k', 920.625e6, 250e3),
        144: chplan_id_params('Plan144_779M_787M_200k', 779.2e6, 200e3),
        145: chplan_id_params('Plan145_779M_787M_400k', 779.4e6, 400e3),
        160: chplan_id_params('Plan160_470M_510M_200k', 470.2e6, 200e3),

    }

    # Region exceptions for b_freq_hz (mismatch with chplan id b_freq_hz)
    # Get this list from Apps (see https://jira.silabs.com/browse/MCUW_RADIO_CFG-2313)
    wisun_1v1_chanfreq0_exception = {
        # (region, chplan_id): b_freq_hz
        ('SG', 32): 866.1e6,
        ('SG', 33): 866.1e6,
        ('SG', 38): 866.3e6
    }

    def __init__(self):
        self._profileName = "wisun_fan_1_1"
        self._readable_name = "Wi-SUN FAN 1.1 Profile"
        self._category = ""
        self._description = "Profile used for Wi-SUN FAN 1.1 PHYs"
        self._default = False
        self._activation_logic = ""
        self._family = "jumbo"

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

        buildStudioLogOutput(model, profile)

        return profile

    def profile_calculate(self, model):
        self._fixed_wisun_vars(model)
        self._lookup_from_wisun_mode(model)
        self._lookup_from_channel_plan(model)
        self._lookup_syncword_from_fec(model)
        self._handle_concurrent_ofdm(model)

    def build_required_profile_inputs(self, model, profile):

        IProfile.make_required_input(profile, model.vars.wisun_reg_domain, "WiSUN",
                                     readable_name="Wi-SUN Regulatory Domain")

        IProfile.make_required_input(profile, model.vars.wisun_phy_mode_id_select, "WiSUN",
                                     readable_name="Wi-SUN PHY Operating Mode ID")

        IProfile.make_required_input(profile, model.vars.wisun_channel_plan_id, "WiSUN",
                                     readable_name="Wi-SUN Channel Plan ID")

        IProfile.make_required_input(profile, model.vars.xtal_frequency_hz, "crystal",
                                     readable_name="Crystal Frequency", value_limit_min=38000000,
                                     value_limit_max=40000000, units_multiplier=UnitsMultiplier.MEGA)

    def build_optional_profile_inputs(self, model, profile):
        IProfile.make_optional_input(profile, model.vars.shaping_filter, "modem", readable_name="Shaping Filter",
                                     default=model.vars.shaping_filter.var_enum.Gaussian)
        IProfile.make_optional_input(profile, model.vars.shaping_filter_param, "modem",
                                readable_name="Shaping Filter Parameter (BT or R)", value_limit_min=0.3,
                                     value_limit_max=2.0, fractional_digits=2, default = 2.0)
        IProfile.make_optional_input(profile, model.vars.payload_white_en, 'advanced',
                                readable_name="Payload Whitening Enable", default=True)

    def build_advanced_profile_inputs(self, model, profile):
        IProfile.make_linked_io(profile, model.vars.base_frequency_hz, "advanced",
                                     readable_name="Base Channel Frequency", value_limit_min=100000000,
                                     value_limit_max=956000000, units_multiplier=UnitsMultiplier.MEGA)
        IProfile.make_linked_io(profile, model.vars.channel_spacing_hz, "advanced",
                                     readable_name="Channel Spacing", value_limit_min=0,
                                     value_limit_max=10000000,
                                     units_multiplier=UnitsMultiplier.KILO)

    def build_hidden_profile_inputs(self, model, profile):
        # Hidden inputs to allow for fixed frame length testing
        IProfile.make_hidden_input(profile, model.vars.frame_length_type, 'frame_general',
                                   readable_name="Frame Length Algorithm")
        IProfile.make_hidden_input(profile, model.vars.fixed_length_size, category='frame_fixed_length',
                                   readable_name="Fixed Payload Size", value_limit_min=0, value_limit_max=0x7fffffff)

        # Hidden inputs to allow for keeping absolute tolerance the same when testing at 915M
        IProfile.make_hidden_input(profile, model.vars.rx_xtal_error_ppm, category="general",
                                   readable_name="Set desired xtal tolerance on RX side", value_limit_min=0,
                                   value_limit_max=100)
        IProfile.make_hidden_input(profile, model.vars.tx_xtal_error_ppm, category="general",
                                   readable_name="Set desired xtal tolerance on TX side", value_limit_min=0,
                                   value_limit_max=100)
        IProfile.make_hidden_input(profile, model.vars.freq_offset_hz, 'Advanced',
                                   readable_name="Frequency Offset Compensation (AFC) Limit", value_limit_min=0,
                                   value_limit_max=500000, units_multiplier=UnitsMultiplier.KILO)
        IProfile.make_hidden_input(profile, model.vars.timing_detection_threshold, 'Advanced',
                                   readable_name="Timing Detection Threshold", value_limit_min=0,
                                   value_limit_max=255)

        # Hidden inputs to allow for control of channel BW (CSMA-CA)
        bandwidth_limit_adc = 2530000
        IProfile.make_hidden_input(profile, model.vars.bandwidth_hz, 'Advanced',
                                   readable_name="Acquisition Channel Bandwidth", value_limit_min=0,
                                   value_limit_max=bandwidth_limit_adc, units_multiplier=UnitsMultiplier.KILO)
        IProfile.make_hidden_input(profile, model.vars.if_frequency_hz, 'Advanced',
                                   readable_name="IF Frequency", value_limit_min=70000, value_limit_max=1900000,
                                   units_multiplier=UnitsMultiplier.KILO)

    def build_deprecated_profile_inputs(self, model, profile):
        #No deprecated Profile Inputs on Jumbo
        pass

    def build_register_profile_outputs(self, model, profile):
        family = self._family
        build_modem_regs_jumbo(model, profile)
        buildFrameOutputs(model, profile)
        buildCrcOutputs(model, profile)
        buildWhiteOutputs(model, profile)
        buildFecOutputs(model, profile)

    def build_variable_profile_outputs(self, model, profile):
        buildRailOutputs(model, profile)
        build_ircal_sw_vars(model, profile)
        profile.outputs.append(ModelOutput(model.vars.ircal_power_level, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='IR cal power level (amplitude)'))
        profile.outputs.append(ModelOutput(model.vars.wisun_phy_mode_id, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='WiSUN PhyModeID'))
        profile.outputs.append(ModelOutput(model.vars.wisun_mode_switch_phr, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='WiSUN Mode Switch PHR'))

    def build_info_profile_outputs(self, model, profile):
        buildModemInfoOutputs(model, profile)

    def _fixed_wisun_vars(self, model):
        # Calculate all of the fixed values (forces) unique to this profile

        # All spec references are to IEEE Std 802.15.4-2015 (shortened to 802154)

        # All WiSUN PHYs have sufficient preamble to disable TSAMPLIM
        # Also force the frequency comp mode
        self._fixed_wisun_thresholds(model)

        # Always use fast AGC
        self._fixed_wisun_agc(model)

        # Variable Length and Endianness Inputs
        model.vars.frame_bitendian.value_forced = model.vars.frame_bitendian.var_enum.LSB_FIRST  # 802154 17.2.2 (Reference Modulator Diagram)
        model.vars.frame_length_type.value_forced = model.vars.frame_length_type.var_enum.VARIABLE_LENGTH  # 802154 20.2.2 (PHR Field Format)
        model.vars.var_length_bitendian.value_forced = model.vars.var_length_bitendian.var_enum.MSB_FIRST  # 802154 20.2.2 (PHR Field Format)
        model.vars.var_length_byteendian.value_forced = model.vars.var_length_byteendian.var_enum.MSB_FIRST  # Consistent with var_length_bitendian above
        model.vars.var_length_numbits.value_forced = 11  # Frame Length contained in bits 5-15 (11 total bits) of PHR
        model.vars.var_length_shift.value_forced = 0  # Since the length is stored MSB_FIRST, we don't need to shift as the MSB is in bit 15
        model.vars.var_length_maxlength.value_forced = 2047  # 11-bit field for Frame Length
        model.vars.var_length_minlength.value_forced = 0
        model.vars.var_length_includecrc.value_forced = True  # Length is the total number of octets contained in the PSDU
        model.vars.var_length_adjust.value_forced = 0

        # Header Inputs
        model.vars.header_calc_crc.value_forced = False  # No CRC on the header itself
        model.vars.header_en.value_forced = True  # 802154 20.2.2 (PHR Field Format)
        model.vars.header_size.value_forced = 2  # Header size is 16 bits
        model.vars.header_white_en.value_forced = False  # When whitening is enabled it shall be applied only over the PSDU

        # FEC settings (note that there is a separate variable fec_tx_enable that determines if FEC is on/off in TX)
        model.vars.fec_en.value_forced = model.vars.fec_en.var_enum.FEC_154G_NRNSC_INTERLEAVING

        # Whitening Inputs set consistent with 802154 17.2.3
        model.vars.white_poly.value_forced = model.vars.white_poly.var_enum.PN9_802154
        model.vars.white_seed.value_forced = 0xFF  # This has been tested, need a 0 in position 8 due to EFR32 whitening architecture
        model.vars.white_output_bit.value_forced = 8

        # CRC Inputs set to match 802.15.4 settings in PHY_COMMON_FRAME_154
        self._fixed_wisun_crc(model)
        model.vars.payload_crc_en.value_forced = True
        model.vars.crc_bit_endian.value_forced = model.vars.crc_bit_endian.var_enum.MSB_FIRST
        model.vars.crc_byte_endian.value_forced = model.vars.crc_byte_endian.var_enum.MSB_FIRST
        model.vars.crc_input_order.value_forced = model.vars.crc_input_order.var_enum.LSB_FIRST

        # Symbol mapping and encoding
        model.vars.diff_encoding_mode.value_forced = model.vars.diff_encoding_mode.var_enum.DISABLED
        model.vars.dsss_chipping_code.value_forced = 0
        model.vars.dsss_len.value_forced = 0
        model.vars.dsss_spreading_factor.value_forced = 0
        model.vars.fsk_symbol_map.value_forced = model.vars.fsk_symbol_map.var_enum.MAP0  # 802154 Table 20.8 and 20.9
        model.vars.symbol_encoding.value_forced = model.vars.symbol_encoding.var_enum.NRZ

        # Preamble and syncword definition
        model.vars.preamble_pattern.value_forced = 1  # 802154 20.2.1.1 (Preamble field)
        model.vars.preamble_pattern_len.value_forced = 2
        model.vars.syncword_length.value_forced = 16

        # Tolerance values
        model.vars.baudrate_tol_ppm.value_forced = 300

        # Variables that are optional inputs in the Base profile and need to be explicitly set
        model.vars.asynchronous_rx_enable.value_forced = False
        model.vars.manchester_mapping.value_forced = model.vars.manchester_mapping.var_enum.Default
        model.vars.syncword_tx_skip.value_forced = False
        model.vars.test_ber.value_forced = False
        model.vars.frame_coding.value_forced = model.vars.frame_coding.var_enum.NONE
        model.vars.fixed_length_size.value_forced = 1
        model.vars.frame_type_0_filter.value_forced = True
        model.vars.frame_type_0_length.value_forced = 0
        model.vars.frame_type_0_valid.value_forced = False
        model.vars.frame_type_1_filter.value_forced = True
        model.vars.frame_type_1_length.value_forced = 0
        model.vars.frame_type_1_valid.value_forced = False
        model.vars.frame_type_2_filter.value_forced = True
        model.vars.frame_type_2_length.value_forced = 0
        model.vars.frame_type_2_valid.value_forced = False
        model.vars.frame_type_3_filter.value_forced = True
        model.vars.frame_type_3_length.value_forced = 0
        model.vars.frame_type_3_valid.value_forced = False
        model.vars.frame_type_4_filter.value_forced = True
        model.vars.frame_type_4_length.value_forced = 0
        model.vars.frame_type_4_valid.value_forced = False
        model.vars.frame_type_5_filter.value_forced = True
        model.vars.frame_type_5_length.value_forced = 0
        model.vars.frame_type_5_valid.value_forced = False
        model.vars.frame_type_6_filter.value_forced = True
        model.vars.frame_type_6_length.value_forced = 0
        model.vars.frame_type_6_valid.value_forced = False
        model.vars.frame_type_7_filter.value_forced = True
        model.vars.frame_type_7_length.value_forced = 0
        model.vars.frame_type_7_valid.value_forced = False
        model.vars.frame_type_bits.value_forced = 3
        model.vars.frame_type_loc.value_forced = 0
        model.vars.frame_type_lsbit.value_forced = 0

        self._region_ww_wisun_tol_temp_overrides(model)   # Implement this to allow Ocelot to call the same overrides

    def _region_ww_wisun_tol_temp_overrides(self, model):

        # For WiSUN 2.4GHz PHYs, tolerances have not been finalized.
        # See https://jira.silabs.com/browse/MCUW_RADIO_CFG-2183
        if model.profile.inputs.wisun_reg_domain.var_value == model.vars.wisun_reg_domain.var_enum.WW \
                and model.profile.inputs.wisun_phy_mode_id_select.var_value.value < 8:
            model.vars.rx_xtal_error_ppm.value_forced = 10
            model.vars.tx_xtal_error_ppm.value_forced = 10


    def _fixed_wisun_crc(self, model):
        model.vars.crc_poly.value_forced = model.vars.crc_poly.var_enum.ANSIX366_1979
        model.vars.crc_invert.value_forced = True
        model.vars.crc_pad_input.value_forced = True
        model.vars.crc_seed.value_forced = 0xFFFFFFFF

    def _fixed_wisun_thresholds(self, model):
        model.vars.timing_sample_threshold.value_forced = 0
        model.vars.frequency_comp_mode.value_forced = model.vars.frequency_comp_mode.var_enum.INTERNAL_LOCK_AT_PREAMBLE_DETECT

    def _fixed_wisun_agc(self, model):
        model.vars.agc_speed.value_forced = model.vars.agc_speed.var_enum.FAST

    def _lookup_from_wisun_mode(self, model):
        # This function calculates some variables/registers based on the PhyModeID

        # Read profile inputs (not yet written to model vars)
        wisun_phy_mode_id_select = model.profile.inputs.wisun_phy_mode_id_select.var_value.value
        wisun_reg_domain = model.profile.inputs.wisun_reg_domain.var_value
        shaping_filter = model.profile.inputs.shaping_filter.var_value
        shaping_filter_param = model.profile.inputs.shaping_filter_param.var_value
        payload_white_en = model.profile.inputs.payload_white_en.var_value

        PhyType = wisun_phy_mode_id_select >> 4 #Top 4 bits of PhyModeID
        PhyMode = wisun_phy_mode_id_select & 0xF #Bottom 4 bits of PhyModeID

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

        # Set bitrate and deviation based on PhyMode
        # Note that for series 1, the bitrate variable represents chiprate, and so is unchanged between FEC on/off

        error = False
        if PhyMode <= 1:
            # Mode1a
            model.vars.bitrate.value_forced = 50000
            model.vars.deviation.value_forced = 12500
            model.vars.preamble_length.value_forced = 8*8

            #Performance optimizations
            model.vars.number_of_timing_windows.value_forced = 2
            model.vars.timing_detection_threshold.value_forced = 16
            model.vars.timing_resync_period.value_forced = 1
            model.vars.MODEM_MODINDEX_FREQGAINM.value_forced = 3
            model.vars.MODEM_MODINDEX_FREQGAINE.value_forced = 2

            if PhyMode == 0:
                # Unsupported
                error = True

        elif PhyMode == 2:
            # Mode1b
            model.vars.bitrate.value_forced = 50000
            model.vars.deviation.value_forced = 25000
            model.vars.preamble_length.value_forced = 8 * 8

            # Performance optimizations
            if wisun_reg_domain == model.vars.wisun_reg_domain.var_enum.CN:
                model.vars.number_of_timing_windows.value_forced = 2 #Applies only to CN

        elif PhyMode == 3:
            # Mode2a
            model.vars.bitrate.value_forced = 100000
            model.vars.deviation.value_forced = 25000
            model.vars.preamble_length.value_forced = 8 * 8

            # Performance optimizations
            model.vars.timing_detection_threshold.value_forced = 30

        elif PhyMode == 4:
            # Mode2b
            model.vars.bitrate.value_forced = 100000
            model.vars.deviation.value_forced = 50000
            model.vars.preamble_length.value_forced = 8 * 8

        elif PhyMode == 5:
            # Mode3
            model.vars.bitrate.value_forced = 150000
            model.vars.deviation.value_forced = 37500
            model.vars.preamble_length.value_forced = 12 * 8

            # Performance optimizations
            model.vars.number_of_timing_windows.value_forced = 4

        elif PhyMode == 6:
            # Mode4a
            model.vars.bitrate.value_forced = 200000
            model.vars.deviation.value_forced = 50000
            model.vars.preamble_length.value_forced = 12 * 8

            #Performance optimizations
            model.vars.MODEM_MODINDEX_FREQGAINM.value_forced = 7 #Only way to achieve this is with reg overrides currently
            model.vars.MODEM_MODINDEX_FREQGAINE.value_forced = 1
            model.vars.MODEM_CTRL2_DEVWEIGHTDIS.value_forced = 1

        elif PhyMode == 7:
            # Mode4b
            model.vars.bitrate.value_forced = 200000
            model.vars.deviation.value_forced = 100000
            model.vars.preamble_length.value_forced = 12 * 8

        else:
            # Mode5
            model.vars.bitrate.value_forced = 300000
            model.vars.deviation.value_forced = 75000
            model.vars.preamble_length.value_forced = 24 * 8

            #Performance optimizations
            model.vars.MODEM_MODINDEX_FREQGAINM.value_forced = 6 #Only way to achieve this is with reg overrides currently
            model.vars.MODEM_MODINDEX_FREQGAINE.value_forced = 1
            model.vars.MODEM_CTRL2_DEVWEIGHTDIS.value_forced = 1

            if PhyMode > 8:
                # Unsupported
                error = True

        if error:
            LogMgr.Error("Error: Unsupported Wi-SUN PhyModeID for this part")

        #Also calculate xtal error based on mode
        if PhyMode <= 1:
            # Mode1a
            model.vars.rx_xtal_error_ppm.value_forced = 20
            model.vars.tx_xtal_error_ppm.value_forced = 20
        else:
            model.vars.rx_xtal_error_ppm.value_forced = 10
            model.vars.tx_xtal_error_ppm.value_forced = 10

    def _lookup_from_channel_plan(self, model):
        # This function calculates some variables/registers based on the ChanPlanId
        wisun_channel_plan_id = model.profile.inputs.wisun_channel_plan_id.var_value
        wisun_reg_domain = model.profile.inputs.wisun_reg_domain.var_value


        error, b_freq_hz, chsp_hz = self._get_info_from_chplan_table(wisun_channel_plan_id, wisun_reg_domain)
        base_frequency_hz = b_freq_hz
        channel_spacing_hz = chsp_hz
        if error:
            LogMgr.Error("Error: Unsupported Wi-SUN ChanPlanID")

        #Write the variables
        model.vars.base_frequency_hz.value_forced = int(base_frequency_hz)
        model.vars.channel_spacing_hz.value_forced = int(channel_spacing_hz)

    def _get_info_from_chplan_table(self, wisun_chplan_id, wisun_reg_domain):

        error = False
        ref_chplan_id = wisun_chplan_id       # If valid id, use as reference

        if wisun_chplan_id not in self.wisun_1v1_chplan_table:        # Invalid id
            error = True
            if wisun_chplan_id > max(self.wisun_1v1_chplan_table.keys()):
                # Use largest valid ID as ref
                ref_chplan_id = max(self.wisun_1v1_chplan_table.keys())
            else:
                # Use smallest valid ID larger than requested ID as ref
                ref_chplan_id = min([id for id in self.wisun_1v1_chplan_table.keys() if id > wisun_chplan_id])


        # Account for mismatches between chplan b_freq_hz and region
        wisun_reg_domain_str = wisun_reg_domain.name
        if (wisun_reg_domain_str, wisun_chplan_id) in self.wisun_1v1_chanfreq0_exception:
            b_freq_hz = self.wisun_1v1_chanfreq0_exception[(wisun_reg_domain_str, wisun_chplan_id)]
            LogMgr.Info(f"Overwriting channel plan base_frequency_hz to {b_freq_hz} "
                           f"for reg domain '{wisun_reg_domain_str}',  chplan id {wisun_chplan_id}")
        else:
            b_freq_hz = self.wisun_1v1_chplan_table[ref_chplan_id].b_freq_hz

        chsp_hz = self.wisun_1v1_chplan_table[ref_chplan_id].chsp_hz

        return error, b_freq_hz, chsp_hz

    def _lookup_syncword_from_fec(self, model):
        #This function sets sync0 and sync1 based on whether FEC is enabled or not
        #This is because we need sync0 to be correct for the active FEC setting (RAIL assumes this)

        # This is set in the _lookup_from_wisun_mode()
        fec_tx_enable = model.vars.fec_tx_enable.value

        #Lookup the syncword to use
        if fec_tx_enable == model.vars.fec_tx_enable.var_enum.DISABLED:
            #Not compatible with dynamic FEC, uncoded as sync0
            syncword_0 = self.phySunFskSfd_0_uncoded
            syncword_1 = 0x00000000
        else:
            #Dynamic FEC ready with coded as sync0
            syncword_0 = self.phySunFskSfd_0_coded
            syncword_1 = self.phySunFskSfd_0_uncoded

        model.vars.syncword_0.value_forced = syncword_0
        model.vars.syncword_1.value_forced = syncword_1

    def _handle_concurrent_ofdm(self, model):
        #Not supported until Sol
        pass

from pyradioconfig.parts.ocelot.profiles.profile_wisun_fan_1_1 import ProfileWisunFan1v1Ocelot
from pyradioconfig.parts.sol.profiles.sw_profile_outputs_common import sw_profile_outputs_common_sol
from pyradioconfig.parts.sol.profiles.wisun_profile_outputs_common import wisun_profile_outputs_common_sol
from pyradioconfig.parts.sol.calculators.calc_synth import Calc_Synth_Sol
from pyradioconfig.parts.sol.calculators.calc_demodulator import Calc_Demodulator_Sol
from pyradioconfig.parts.common.utils.units_multiplier import UnitsMultiplier
from pyradioconfig.calculator_model_framework.CalcManager import CalcManager
from pycalcmodel.core.output import ModelOutputType
import re

class ProfileWisunFan1v1Sol(ProfileWisunFan1v1Ocelot):

    def __init__(self):
        super().__init__()
        self._family = "sol"
        self._sw_profile_outputs_common = sw_profile_outputs_common_sol()
        self._wisun_profile_outputs_common = wisun_profile_outputs_common_sol()

    def _fixed_wisun_crc(self, model):
        model.vars.fcs_type_802154.value_forced = model.vars.fcs_type_802154.var_enum.FOUR_BYTE
        model.vars.crc_invert.value_forced = True
        model.vars.crc_pad_input.value_forced = True
        model.vars.crc_seed.value_forced = 0xFFFFFFFF

    def build_required_profile_inputs(self, model, profile):

        self.make_required_input(profile, model.vars.wisun_reg_domain, "WiSUN",
                                     readable_name="Wi-SUN Regulatory Domain")

        self.make_required_input(profile, model.vars.wisun_phy_mode_id_select, "WiSUN",
                                     readable_name="Wi-SUN PHY Operating Mode ID", value_limit_min=0,
                                     value_limit_max=0x5F)  # Now with OFDM support

        self.make_required_input(profile, model.vars.wisun_channel_plan_id, "WiSUN",
                                     readable_name="Wi-SUN Channel Plan ID", value_limit_min=0,
                                     value_limit_max=63)

        self.make_required_input(profile, model.vars.xtal_frequency_hz, "crystal",
                                     readable_name="Crystal Frequency", value_limit_min=38000000,
                                     value_limit_max=40000000, units_multiplier=UnitsMultiplier.MEGA)

    def build_optional_profile_inputs(self, model, profile):
        self.make_optional_input(profile, model.vars.shaping_filter, "modem", readable_name="Shaping Filter (FSK only)",
                                 default=model.vars.shaping_filter.var_enum.Gaussian)
        self.make_optional_input(profile, model.vars.shaping_filter_param, "modem",
                            readable_name="Shaping Filter Parameter (BT or R)", value_limit_min=0.3,
                            value_limit_max=2.0, fractional_digits=2, default = 2.0)
        self.make_optional_input(profile, model.vars.payload_white_en, 'advanced',
                            readable_name="Payload Whitening Enable (FSK only)", default=True)
        self.make_optional_input(profile, model.vars.conc_ofdm_option, 'Concurrent',
                                 readable_name="Concurrent OFDM Option", default=model.vars.conc_ofdm_option.var_enum.NONE)

    def build_advanced_profile_inputs(self, model, profile):
        self.make_linked_io(profile, model.vars.base_frequency_hz, "advanced", readable_name="Base Channel Frequency",
                            value_limit_min=358000000, value_limit_max=956000000, units_multiplier=UnitsMultiplier.MEGA)
        self.make_linked_io(profile, model.vars.channel_spacing_hz, "advanced",
                                readable_name="Channel Spacing", value_limit_min=0, value_limit_max=10000000,
                                units_multiplier=UnitsMultiplier.KILO)
        self.make_linked_io(profile, model.vars.fpll_band, 'crystal', readable_name="RF Frequency Planning Band")

    def build_hidden_profile_inputs(self, model, profile):

        super().build_hidden_profile_inputs(model, profile)

        self.make_hidden_input(profile, model.vars.demod_select, 'Advanced', readable_name="Demod Selection")
        self.make_hidden_input(profile, model.vars.trecs_enabled, 'Advanced', readable_name="trecs_enabled")

        # Hidden input for dual front-end filter support
        self.make_hidden_input(profile, model.vars.dual_fefilt, "Advanced", readable_name="Dual front-end filter enable")
        self.make_hidden_input(profile, model.vars.antdivmode, "Advanced", readable_name="Antenna diversity mode")

    def build_variable_profile_outputs(self, model, profile):
        self._sw_profile_outputs_common.build_rail_outputs(model, profile)
        self._sw_profile_outputs_common.build_ircal_outputs(model, profile)
        self._wisun_profile_outputs_common.build_wisun_mode_switch_outputs(model, profile)

    def _fixed_wisun_vars(self, model):
        pass

    def _lookup_from_wisun_mode(self, model):
        # This function calculates some variables/registers based on the PhyModeID

        # Read the mode and fec_en from the profile inputs (not yet written to model vars)
        wisun_phy_mode_id_select = model.profile.inputs.wisun_phy_mode_id_select.var_value
        shaping_filter = model.profile.inputs.shaping_filter.var_value
        shaping_filter_param = model.profile.inputs.shaping_filter_param.var_value
        payload_white_en = model.profile.inputs.payload_white_en.var_value

        PhyType = wisun_phy_mode_id_select >> 4  # Top 4 bits of PhyModeID

        # Set FEC enable and modulation type based on PhyType
        if PhyType <= 1:
            # Wi-SUN FSK
            # Use the calculations from Ocelot
            super()._lookup_from_wisun_mode(model)
            super()._fixed_wisun_vars(model)
        else:
            #Wi-SUN OFDM
            model.vars.fec_tx_enable.value_forced = model.vars.fec_tx_enable.var_enum.DISABLED
            model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.OFDM

            # Set defaults for shaping and whitening (for OFDM)
            if shaping_filter is None:
                model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.Gaussian
            if shaping_filter_param is None:
                model.vars.shaping_filter_param.value_forced = 0.5
            if payload_white_en is None:
                model.vars.payload_white_en.value_forced = False

            # Set bitrate to the highest rate for given option # up to 2400 with MCS6
            if PhyType == 2:
                #OPT 1
                model.vars.ofdm_option.value_forced = model.vars.ofdm_option.var_enum.OPT1
                model.vars.bitrate.value_forced = 2400000
            elif PhyType == 3:
                #OPT 2
                model.vars.ofdm_option.value_forced = model.vars.ofdm_option.var_enum.OPT2
                model.vars.bitrate.value_forced = 1200000
            elif PhyType == 4:
                # OPT 3
                model.vars.ofdm_option.value_forced = model.vars.ofdm_option.var_enum.OPT3
                model.vars.bitrate.value_forced = 600000
            elif PhyType == 5:
                # OPT 4
                model.vars.ofdm_option.value_forced = model.vars.ofdm_option.var_enum.OPT4
                model.vars.bitrate.value_forced = 300000

            # Set other fixed vars for Wi-SUN OFDM
            self._fixed_wisun_ofdm_vars(model)

    def _lookup_syncword_from_fec(self, model):
        modulation_type = model.vars.modulation_type.value #This is set by the _lookup_from_wisun_mode() method

        if modulation_type == model.vars.modulation_type.var_enum.FSK2:
            # Call method from Ocelot for 2FSK
            # For OFDM, syncword is set in fixed vars
            super()._lookup_syncword_from_fec(model)

    def _fixed_wisun_ofdm_vars(self, model):

        #AGC
        self._fixed_wisun_ofdm_agc(model,ofdm_option_int=int(model.vars.ofdm_option.value)+1)

        #OFDM modulation
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.OFDM

        #Use fullrate ADC (needs further study, improves sensitivity esp for OPT4 PHY)
        model.vars.adc_rate_mode.value_forced = model.vars.adc_rate_mode.var_enum.FULLRATE

        #Tolerance
        model.vars.rx_xtal_error_ppm.value_forced = 0
        model.vars.tx_xtal_error_ppm.value_forced = 0
        model.vars.baudrate_tol_ppm.value_forced = 0
        model.vars.deviation_tol_ppm.value_forced = 0

        #Encoding and Whitening (unused)
        model.vars.diff_encoding_mode.value_forced = model.vars.diff_encoding_mode.var_enum.DISABLED
        model.vars.dsss_chipping_code.value_forced = 0
        model.vars.dsss_len.value_forced = 0
        model.vars.dsss_spreading_factor.value_forced = 0
        model.vars.symbol_encoding.value_forced = model.vars.symbol_encoding.var_enum.NRZ
        model.vars.manchester_mapping.value_forced = model.vars.manchester_mapping.var_enum.Default
        model.vars.frame_coding.value_forced = model.vars.frame_coding.var_enum.NONE
        model.vars.white_poly.value_forced = model.vars.white_poly.var_enum.NONE
        model.vars.white_seed.value_forced = 0
        model.vars.white_output_bit.value_forced = 0

        #Preamble and syncword (unused)
        model.vars.preamble_length.value_forced = 2
        model.vars.preamble_pattern.value_forced = 1
        model.vars.preamble_pattern_len.value_forced = 2
        model.vars.syncword_0.value_forced = 0x12345678
        model.vars.syncword_1.value_forced = 0x12345678
        model.vars.syncword_length.value_forced = 16

        #Modulation parameters (unused)
        model.vars.deviation.value_forced = 0
        model.vars.fsk_symbol_map.value_forced = model.vars.fsk_symbol_map.var_enum.MAP0

        #Frame settings (unused)
        model.vars.frame_bitendian.value_forced = model.vars.frame_bitendian.var_enum.LSB_FIRST
        model.vars.frame_length_type.value_forced = model.vars.frame_length_type.var_enum.FIXED_LENGTH
        model.vars.payload_white_en.value_forced = False
        model.vars.payload_crc_en.value_forced = False
        model.vars.header_en.value_forced = True
        model.vars.header_size.value_forced = 1
        model.vars.header_calc_crc.value_forced = False
        model.vars.header_white_en.value_forced = False
        model.vars.var_length_numbits.value_forced = 8
        model.vars.var_length_bitendian.value_forced = model.vars.var_length_bitendian.var_enum.LSB_FIRST
        model.vars.var_length_shift.value_forced = 0
        model.vars.var_length_minlength.value_forced = 5
        model.vars.var_length_maxlength.value_forced = 0x7F
        model.vars.var_length_includecrc.value_forced = False
        model.vars.var_length_adjust.value_forced = 0
        model.vars.var_length_byteendian.value_forced = model.vars.var_length_byteendian.var_enum.LSB_FIRST
        model.vars.fcs_type_802154.value_forced = model.vars.fcs_type_802154.var_enum.FOUR_BYTE
        model.vars.crc_seed.value_forced = 0x00000000
        model.vars.crc_input_order.value_forced = model.vars.crc_input_order.var_enum.LSB_FIRST
        model.vars.crc_bit_endian.value_forced = model.vars.crc_bit_endian.var_enum.MSB_FIRST
        model.vars.crc_byte_endian.value_forced = model.vars.crc_byte_endian.var_enum.MSB_FIRST
        model.vars.crc_pad_input.value_forced = False
        model.vars.crc_invert.value_forced = False
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

        #Other
        model.vars.asynchronous_rx_enable.value_forced = False
        model.vars.syncword_tx_skip.value_forced = False

    def _fixed_wisun_ofdm_agc(self, model, ofdm_option_int):

        model.vars.RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI.value_forced = 5  # 60mVrms
        model.vars.RAC_PGACTRL_PGATHRPKDHISEL.value_forced = 3   # 125mV
        model.vars.RAC_PGACTRL_PGATHRPKDLOSEL.value_forced = 0  # 100mV
        model.vars.AGC_GAINSTEPLIM1_PNINDEXMAX.value_forced = 17  # Per Yang Gao 10/1/20
        model.vars.AGC_GAINRANGE_PNGAINSTEP.value_forced = 3
        model.vars.AGC_AGCPERIOD0_PERIODHI.value_forced = 44
        model.vars.AGC_HICNTREGION0_HICNTREGION0.value_forced = 37  # PERIODHI-SETTLETIMEIF-1
        model.vars.AGC_HICNTREGION0_HICNTREGION1.value_forced = 100
        model.vars.AGC_HICNTREGION0_HICNTREGION2.value_forced = 100
        model.vars.AGC_HICNTREGION0_HICNTREGION3.value_forced = 100
        model.vars.AGC_HICNTREGION1_HICNTREGION4.value_forced = 100
        model.vars.AGC_AGCPERIOD0_MAXHICNTTHD.value_forced = 100  # > PERIODHI means disabled
        model.vars.AGC_STEPDWN_STEPDWN0.value_forced = 1
        model.vars.AGC_STEPDWN_STEPDWN1.value_forced = 2
        model.vars.AGC_STEPDWN_STEPDWN2.value_forced = 2
        model.vars.AGC_STEPDWN_STEPDWN3.value_forced = 2
        model.vars.AGC_STEPDWN_STEPDWN4.value_forced = 2
        model.vars.AGC_STEPDWN_STEPDWN5.value_forced = 2
        model.vars.AGC_CTRL7_SUBDEN.value_forced = 1
        model.vars.AGC_CTRL7_SUBINT.value_forced = 16
        model.vars.AGC_CTRL7_SUBNUM.value_forced = 0
        model.vars.AGC_CTRL7_SUBPERIOD.value_forced = 1

        if ofdm_option_int == 1:
            model.vars.AGC_CTRL4_RFPKDPRDGEAR.value_forced = 2  # 25usec dispngainup period
            model.vars.AGC_AGCPERIOD1_PERIODLOW.value_forced = 960  # 960 STF cycle = 24 usec
            model.vars.AGC_CTRL1_PWRPERIOD.value_forced = 2
            model.vars.AGC_CTRL1_RSSIPERIOD.value_forced = 3
        elif ofdm_option_int == 2:
            model.vars.AGC_CTRL4_RFPKDPRDGEAR.value_forced = 2  # 25usec dispngainup period
            model.vars.AGC_AGCPERIOD1_PERIODLOW.value_forced = 1920  # STF cycle = 48 usec
            model.vars.AGC_CTRL1_PWRPERIOD.value_forced = 2
            model.vars.AGC_CTRL1_RSSIPERIOD.value_forced = 3
        elif ofdm_option_int == 3:
            model.vars.AGC_CTRL4_RFPKDPRDGEAR.value_forced = 2  # 25usec dispngainup period
            model.vars.AGC_AGCPERIOD1_PERIODLOW.value_forced = 3840  # STF cycle = 96 usec
            model.vars.AGC_CTRL1_PWRPERIOD.value_forced = 1
            model.vars.AGC_CTRL1_RSSIPERIOD.value_forced = 2
        else:
            model.vars.AGC_CTRL4_RFPKDPRDGEAR.value_forced = 1  # 48usec dispngainup period
            model.vars.AGC_AGCPERIOD1_PERIODLOW.value_forced = 3840  # STF cycle = 96 usec
            model.vars.AGC_CTRL1_PWRPERIOD.value_forced = 2
            model.vars.AGC_CTRL1_RSSIPERIOD.value_forced = 2

    def _handle_concurrent_ofdm(self, model):

            # This method is called when we are calculating a Wi-SUN FSK PHY and also have the concurrent_ofdm_opt set
            # In this case we need to call the Radio Configurator for the OFDM PHY and then merge the PHYs together

            conc_ofdm_option = model.profile.inputs.conc_ofdm_option.var_value
            wisun_reg_domain = model.profile.inputs.wisun_reg_domain.var_value
            xtal_frequency_hz = model.profile.inputs.xtal_frequency_hz.var_value
            base_frequency_hz = model.profile.inputs.base_frequency_hz.var_value
            shaping_filter = model.profile.inputs.shaping_filter.var_value
            shaping_filter_param = model.profile.inputs.shaping_filter_param.var_value

            if conc_ofdm_option != model.vars.conc_ofdm_option.var_enum.NONE:

                #Load in additional model vars that were previously populated
                fec_tx_enable = (model.vars.fec_tx_enable.value == model.vars.fec_tx_enable.var_enum.ENABLED)
                fec_factor = 2 if fec_tx_enable else 1
                deviation = model.vars.deviation.value
                baudrate = model.vars.bitrate.value * fec_factor
                rx_xtal_error_ppm = model.vars.rx_xtal_error_ppm.value
                tx_xtal_error_ppm = model.vars.tx_xtal_error_ppm.value

                # Placeholder calculation for wisun_channel_plan_id
                # This is probably a don't care anyway since alternate base freq and channel spacing will come from multiphy config
                if conc_ofdm_option == model.vars.conc_ofdm_option.var_enum.OPT1:
                    wisun_channel_plan_id = 5
                elif conc_ofdm_option == model.vars.conc_ofdm_option.var_enum.OPT2:
                    wisun_channel_plan_id = 4
                elif conc_ofdm_option == model.vars.conc_ofdm_option.var_enum.OPT3:
                    wisun_channel_plan_id = 2
                else:
                    wisun_channel_plan_id = 1

                # Pre-calculate bandwidth of FSK PHY
                modulation_index = 2.0 * deviation / baudrate
                bw_carson = baudrate + 2 * deviation
                freq_offset_hz = int(round(base_frequency_hz / 1e6 * (rx_xtal_error_ppm + tx_xtal_error_ppm)))
                alpha = Calc_Demodulator_Sol().get_alpha(model, modulation_index, shaping_filter, shaping_filter_param)
                fsk_bandwidth = Calc_Demodulator_Sol().get_target_2fsk_bandwidth(bw_carson, freq_offset_hz, alpha)

                # Pre-calculate what IF frequency we will use for both FSK and OFDM PHYs
                fsk_if_frequency = Calc_Synth_Sol().get_if_freq(100e3, fsk_bandwidth)
                ofdm_if_frequency = Calc_Synth_Sol().lookup_ofdm_if_freq(int(conc_ofdm_option)-1)
                if_frequency_hz = max(fsk_if_frequency, ofdm_if_frequency)
                model.vars.if_frequency_hz.value_forced = if_frequency_hz #Force the FSK IF freq

                # Calculate the OFDM PHY
                input_dict = {
                    'wisun_reg_domain': wisun_reg_domain,
                    'wisun_phy_mode_id_select': (1 + int(conc_ofdm_option)) << 4,  # Corresponds to MCS0, the MCS is really a don't care
                    'wisun_channel_plan_id': wisun_channel_plan_id,
                    'xtal_frequency_hz': xtal_frequency_hz,
                    'base_frequency_hz': base_frequency_hz,  # Set base frequency to be co-located with FSK by default
                    'if_frequency_hz': if_frequency_hz  # Force the OFDM IF freq
                }
                ofdm_phy_model = CalcManager(part_family=model.part_family, part_rev=model.part_revision,
                                             target=model.target).calc_config_profile(profile_name='wisun_fan_1_1',
                                                                                      optional_inputs=input_dict)

                # Assign special concurrent PHY variables
                model.vars.alt_min_if_hz.value_forced = ofdm_phy_model.vars.min_if_hz.value
                model.vars.alt_softmodem_used.value_forced = 1  # softmodem always used for OFDM
                model.vars.alt_wisun_mode_switch_phr.value_forced = ofdm_phy_model.vars.wisun_mode_switch_phr.value
                model.vars.alt_wisun_phy_mode_id.value_forced = ofdm_phy_model.vars.wisun_phy_mode_id.value
                model.vars.alt_stack_info.value_forced = ofdm_phy_model.vars.stack_info.value

                # Finally loop go through the Profile Outputs for the concurrent PHY and copy them over
                reg_fields_from_ofdm = ['AGC_.*','FEFILT1_*', 'SUNOFDM_*', 'TXFRONT_*', 'RAC_PGACTRL_PGABWMODE']
                for reg_field in reg_fields_from_ofdm:
                    for profile_output in ofdm_phy_model.profile.outputs:
                        if (profile_output.output_type == ModelOutputType.SVD_REG_FIELD) and \
                                re.search("^" + reg_field.lower(), profile_output.var_name.lower()):
                            fsk_phy_model_var = getattr(model.profile.outputs, profile_output.var_name)
                            if fsk_phy_model_var.override is None: #If already forced then use that value
                                fsk_phy_model_var.override = profile_output.var_value

                #Add fixed Wi-SUN OFDM AGC settings
                #This time we pass in the OFDM option from the conc_ofdm_option variable
                self._fixed_wisun_ofdm_agc(model, int(conc_ofdm_option))

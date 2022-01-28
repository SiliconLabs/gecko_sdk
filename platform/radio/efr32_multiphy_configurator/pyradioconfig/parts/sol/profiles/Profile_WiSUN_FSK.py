from pyradioconfig.parts.ocelot.profiles.Profile_WiSUN import Profile_WiSUN_Ocelot
from pyradioconfig.parts.common.utils.units_multiplier import UnitsMultiplier
from pyradioconfig.parts.sol.profiles.sw_profile_outputs_common import sw_profile_outputs_common_sol

class Profile_WiSUN_FSK_Sol(Profile_WiSUN_Ocelot):

    def __init__(self):
        self._profileName = "WiSUN_FSK"
        self._readable_name = "Wi-SUN FSK Profile"
        self._category = ""
        self._description = "Profile used for Wi-SUN FSK PHYs"
        self._default = False
        self._activation_logic = ""
        self._family = "sol"
        self._sw_profile_outputs_common = sw_profile_outputs_common_sol()

    def _fixed_wisun_vars(self, model):

        #Use the fixed wisun vars from Ocelot
        super()._fixed_wisun_vars(model)

        #Add the ofdm_option variable
        model.vars.ofdm_option.value_forced = model.vars.ofdm_option.var_enum.OPT1

    def build_required_profile_inputs(self, model, profile):

        self.make_required_input(profile, model.vars.base_frequency_hz, "operational_frequency",
                                     readable_name="Base Channel Frequency", value_limit_min=358000000,
                                     value_limit_max=956000000, units_multiplier=UnitsMultiplier.MEGA)
        self.make_required_input(profile, model.vars.channel_spacing_hz, "operational_frequency",
                                     readable_name="Channel Spacing", value_limit_min=0,
                                     value_limit_max=10000000,
                                     units_multiplier=UnitsMultiplier.KILO)
        self.make_required_input(profile, model.vars.xtal_frequency_hz, "crystal",
                                     readable_name="Crystal Frequency", value_limit_min=38000000,
                                     value_limit_max=40000000, units_multiplier=UnitsMultiplier.MEGA)
        self.make_required_input(profile, model.vars.preamble_length, "preamble",
                                     readable_name="Preamble Length Total", value_limit_min=0, value_limit_max=2097151)
        self.make_required_input(profile, model.vars.wisun_mode, "WiSUN",
                                     readable_name="Wi-SUN Mode")
        self.make_required_input(profile, model.vars.fcs_type_802154, 'WiSUN', readable_name="FCS Type (CRC)")

    def build_hidden_profile_inputs(self, model, profile):

        # Hidden inputs to allow for fixed frame length testing
        self.make_hidden_input(profile, model.vars.frame_length_type, 'frame_general',
                                   readable_name="Frame Length Algorithm")
        self.make_hidden_input(profile, model.vars.fixed_length_size, category='frame_fixed_length',
                                   readable_name="Fixed Payload Size", value_limit_min=0, value_limit_max=0x7fffffff)

        #Hidden inputs to allow for keeping absolute tolerance the same when testing at 915M
        self.make_hidden_input(profile, model.vars.rx_xtal_error_ppm, category="general",
                                   readable_name="Set desired xtal tolerance on RX side", value_limit_min=0,
                                   value_limit_max=100)
        self.make_hidden_input(profile, model.vars.tx_xtal_error_ppm, category="general",
                                   readable_name="Set desired xtal tolerance on TX side", value_limit_min=0,
                                   value_limit_max=100)
        self.make_hidden_input(profile, model.vars.freq_offset_hz, 'Advanced',
                                   readable_name="Frequency Offset Compensation (AFC) Limit", value_limit_min=0,
                                   value_limit_max=500000, units_multiplier=UnitsMultiplier.KILO)

        self.make_hidden_input(profile, model.vars.demod_select, 'Advanced', readable_name="Demod Selection")

        self.make_hidden_input(profile, model.vars.afc_run_mode, 'Advanced', readable_name="afc_run_mode")
        self.make_hidden_input(profile, model.vars.trecs_enabled, 'Advanced', readable_name="trecs_enabled")

        # Hidden input for dual front-end filter support
        self.make_hidden_input(profile, model.vars.dual_fefilt, "Advanced",
                               readable_name="Dual front-end filter enable")

    def _lookup_from_crc_type(self, model):
        # This function sets CRC parameters based on the CRC specified

        # Read the FCS type
        fcs_type_802154 = model.profile.inputs.fcs_type_802154.var_value

        # Based on the CRC type, set the CRC seed, invert, and padding settings
        if fcs_type_802154 == model.vars.fcs_type_802154.var_enum.FOUR_BYTE:
            crc_invert = True
            crc_pad_input = True
            crc_seed = 0xFFFFFFFF
        else:
            crc_invert = False
            crc_pad_input = False
            crc_seed = 0x00000000

        # Write the variables
        model.vars.crc_invert.value_forced = crc_invert
        model.vars.crc_pad_input.value_forced = crc_pad_input
        model.vars.crc_seed.value_forced = crc_seed
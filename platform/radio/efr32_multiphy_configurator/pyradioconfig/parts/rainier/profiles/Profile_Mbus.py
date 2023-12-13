from pyradioconfig.parts.bobcat.profiles.Profile_Mbus import Profile_Mbus_Bobcat
from pyradioconfig.parts.rainier.profiles.sw_profile_outputs_common import SwProfileOutputsCommonRainier
from pyradioconfig.parts.common.profiles.profile_common import *
from pyradioconfig.parts.common.profiles.rainier_regs import build_modem_regs_rainier
from pyradioconfig.parts.common.utils.units_multiplier import UnitsMultiplier


class ProfileMbusRainier(Profile_Mbus_Bobcat):

    def __init__(self):
        super().__init__()
        self._family = "rainier"
        self._profileName = "Mbus"
        self._readable_name = "Mbus Profile"
        self._category = ""
        self._description = "Profile used for Mbus phys"
        self._default = False
        self._activation_logic = ""
        self._sw_profile_outputs_common = SwProfileOutputsCommonRainier()


    """
    Builds inputs, forced, outputs into modem model
    """
    def buildProfileModel(self, model):

        family = self._family

        # Build profile
        profile = self._makeProfile(model)

        self.make_required_input(profile, model.vars.preamble_length, "general", readable_name="Preamble Length Total", value_limit_min=16, value_limit_max=2097151)
        self.make_required_input(profile, model.vars.mbus_mode,            category="general", readable_name="Mbus Mode")
        self.make_required_input(profile, model.vars.mbus_frame_format,    category="general", readable_name="Mbus Frame Format")
        self.make_required_input(profile, model.vars.mbus_symbol_encoding, category="general", readable_name="Symbol Encoding")
        self.make_required_input(profile, model.vars.syncword_dualsync,    category="general", readable_name="Enable Dual Syncword Detection")

        self.make_required_input(profile, model.vars.base_frequency_hz,    category="operational_frequency", readable_name="Base Channel Frequency",  value_limit_min=long(100000000), value_limit_max=long(2500000000), units_multiplier=UnitsMultiplier.MEGA)
        self.make_required_input(profile, model.vars.channel_spacing_hz,   category="operational_frequency", readable_name="Channel Spacing",         value_limit_min=0,          value_limit_max=10000000,    units_multiplier=UnitsMultiplier.KILO)
        self.make_required_input(profile, model.vars.xtal_frequency_hz, "crystal",
                                     readable_name="Crystal Frequency", value_limit_min=38000000,
                                     value_limit_max=40000000, units_multiplier=UnitsMultiplier.MEGA)

        # Hidden test inputs
        self.make_hidden_input(profile, model.vars.fixed_length_size, category='frame_fixed_length', readable_name="Fixed Payload Size", value_limit_min=0, value_limit_max=0x7fffffff)
        self.make_hidden_input(profile, model.vars.payload_crc_en,    category='frame_payload',      readable_name="Insert/Check CRC after payload")

        self.make_hidden_input(profile, model.vars.crc_poly,        category='crc', readable_name="CRC Polynomial")
        self.make_hidden_input(profile, model.vars.crc_byte_endian, category='crc', readable_name="CRC Byte Endian")
        self.make_hidden_input(profile, model.vars.crc_bit_endian,  category='crc', readable_name="CRC Output Bit Endian")
        self.make_hidden_input(profile, model.vars.crc_pad_input,   category='crc', readable_name="CRC Input Padding")
        self.make_hidden_input(profile, model.vars.crc_input_order, category='crc', readable_name="CRC Input Bit Endian")
        self.make_hidden_input(profile, model.vars.crc_invert,      category='crc', readable_name="CRC Invert")

        self.make_optional_input(profile, model.vars.test_ber,      category="testing", readable_name="Reconfigure for BER testing", default=False)

        self.make_optional_input(profile, model.vars.mbus_postamble_length, category="general", default=0,
                                     readable_name="Mbus postamble legnth", value_limit_min=0,
                                     value_limit_max=4)
        self.make_hidden_input(profile, model.vars.target_osr,      category="general", readable_name="Set desired OSR", value_limit_min=3, value_limit_max=9)
        self.make_hidden_input(profile, model.vars.bitrate,       category="modem",   readable_name="Bitrate", value_limit_min=100, value_limit_max=2000000,units_multiplier=UnitsMultiplier.KILO)

        #These can not be hidden because they are used in Studio PHYs. These can not be optional inputs because of the way the variables are forced in the Mbus code.
        self.make_linked_io(profile, model.vars.rx_xtal_error_ppm, category="general", readable_name="Set desired xtal tolerance on RX side", value_limit_min=0, value_limit_max=100)
        self.make_linked_io(profile, model.vars.tx_xtal_error_ppm, category="general", readable_name="Set desired xtal tolerance on TX side", value_limit_min=0, value_limit_max=100)

        self.make_hidden_input(profile, model.vars.demod_select, 'Advanced', readable_name="Demod Selection")

        # TODO:  Change this to MSB_FIRst in the lab phys, then remove this input and move it to the forced section below
        self.make_hidden_input(profile, model.vars.frame_bitendian, category='frame_general', readable_name="Frame Bit Endian")

        self.make_hidden_input(profile, model.vars.synth_settling_mode, 'modem', readable_name="Synth Settling Mode")
        self.make_optional_input(profile, model.vars.deviation_tol_ppm, 'modem', default=0, readable_name="Maximum deviation offset expected in ppm",value_limit_min=0, value_limit_max=500000)


        # Informational output
        self._sw_profile_outputs_common.build_info_outputs(model, profile)

        # RAIL Outputs
        self._sw_profile_outputs_common.build_rail_outputs(model, profile)

        # Output fields
        buildFrameOutputs(model, profile)
        buildCrcOutputs(model, profile)
        buildWhiteOutputs(model, profile)
        buildFecOutputs(model, profile)

        build_modem_regs_rainier(model, profile)

        build_ircal_sw_vars(model, profile)

        return profile
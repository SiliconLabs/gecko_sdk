from pyradioconfig.parts.sol.profiles.Profile_Base import Profile_Base_Sol
from pyradioconfig.parts.sol.profiles.frame_profile_inputs_common import frame_profile_inputs_common_sol
from pyradioconfig.parts.sol.profiles.sw_profile_outputs_common import sw_profile_outputs_common_sol

class Profile_Connect_Sol(Profile_Base_Sol):

    def __init__(self):
        self._profileName = "Connect"
        self._readable_name = "Connect Profile"
        self._category = ""
        self._description = "Profile used for Connect phys"
        self._default = False
        self._activation_logic = ""
        self._family = "sol"
        self._frame_profile_inputs_common = frame_profile_inputs_common_sol()
        self._sw_profile_outputs_common = sw_profile_outputs_common_sol()

    def buildProfileModel(self, model):

        # Start with base profile
        profile = super(Profile_Connect_Sol, self).buildProfileModel(model)

        # Do not remove the following profile inputs from the base profile.
        retain_profile_input_list = [
            "fcs_type_802154",
            "crc_byte_endian",
            "crc_bit_endian",
            "header_size",
            "white_poly", # : Expose whitening option for Sol Connect support for SUN-FSK based phys
            "white_seed",
            "white_output_bit",
            "payload_white_en"
        ]

        # Start with a profile that has lots of knobs, and remove most of them.
        # Note that profile inputs included in "retain_profile_input_list" will not be removed.
        # Remove those that are not in a certain category
        for input in profile.inputs:
            # Force things in these categories
            if (input.category.startswith('frame_')) or (input.category == 'crc') or (input.category == 'whitening'):
                if input._var._name not in retain_profile_input_list:
                    self._removeVariableFromInputs(profile, input._var, input.default)

        # : Allow selection of Two Octet CRC vs. Four Octet CRC defined in IEEE802154-2020 (7.2.11)
        self.make_optional_input(profile, model.vars.fcs_type_802154, 'advanced', readable_name="FCS Type (CRC)",
                                 default=model.vars.fcs_type_802154.var_enum.TWO_BYTE)

        #Hidden inputs to allow for fixed frame length testing
        self.make_hidden_input(profile, model.vars.frame_length_type, 'frame_general',
                                   readable_name="Frame Length Algorithm")
        self.make_hidden_input(profile, model.vars.fixed_length_size, category='frame_fixed_length',
                                   readable_name="Fixed Payload Size", value_limit_min=0, value_limit_max=0x7fffffff)

        return profile

    def profile_calculate(self, model):

        model.vars.protocol_id.value_forced = model.vars.protocol_id.var_enum.Connect

        # frame_general
        model.vars.frame_bitendian.value_forced = model.vars.frame_bitendian.var_enum.LSB_FIRST
        model.vars.frame_length_type.value_forced = model.vars.frame_length_type.var_enum.VARIABLE_LENGTH
        model.vars.header_en.value_forced = True
        model.vars.frame_coding.value_forced = model.vars.frame_coding.var_enum.NONE

        # frame_header
        model.vars.header_calc_crc.value_forced = False

        # frame_fixed_length
        model.vars.fixed_length_size.value_forced = 16

        # frame_var_length
        self._lookup_framing_from_header_size(model)

        # frame_type_length
        model.vars.frame_type_loc.value_forced = 0
        model.vars.frame_type_bits.value_forced = 3
        model.vars.frame_type_lsbit.value_forced = 0
        model.vars.frame_type_0_length.value_forced = 0
        model.vars.frame_type_1_length.value_forced = 0
        model.vars.frame_type_2_length.value_forced = 0
        model.vars.frame_type_3_length.value_forced = 0
        model.vars.frame_type_4_length.value_forced = 0
        model.vars.frame_type_5_length.value_forced = 0
        model.vars.frame_type_6_length.value_forced = 0
        model.vars.frame_type_7_length.value_forced = 0
        model.vars.frame_type_0_valid.value_forced = False
        model.vars.frame_type_1_valid.value_forced = False
        model.vars.frame_type_2_valid.value_forced = False
        model.vars.frame_type_3_valid.value_forced = False
        model.vars.frame_type_4_valid.value_forced = False
        model.vars.frame_type_5_valid.value_forced = False
        model.vars.frame_type_6_valid.value_forced = False
        model.vars.frame_type_7_valid.value_forced = False

        # crc
        # frame_payload
        model.vars.payload_crc_en.value_forced = True
        model.vars.crc_input_order.value_forced = model.vars.crc_input_order.var_enum.LSB_FIRST
        self._lookup_crc_from_fcs_type(model)

        # : Whitening Option
        model.vars.header_white_en.value_forced = False # Always disable header whitening

        # unused OFDM
        model.vars.ofdm_option.value_forced = model.vars.ofdm_option.var_enum.OPT1_OFDM_BW_1p2MHz

    def _lookup_framing_from_header_size(self, model):
        # frame_var_length
        if model.profile.inputs.header_size.var_value == 1:  # : One byte header as defined by IEEE802154 GFSK / OQPSK
            model.vars.var_length_numbits.value_forced = 7
            model.vars.var_length_bitendian.value_forced = model.vars.var_length_bitendian.var_enum.LSB_FIRST
            model.vars.var_length_shift.value_forced = 0
            model.vars.var_length_minlength.value_forced = 5
            model.vars.var_length_maxlength.value_forced = 127
            model.vars.var_length_includecrc.value_forced = True
            model.vars.var_length_adjust.value_forced = 0
            model.vars.var_length_byteendian.value_forced = model.vars.var_length_byteendian.var_enum.LSB_FIRST
        else:  # : Two byte header as defined by SUN-FSK
            model.vars.var_length_numbits.value_forced = 11
            model.vars.var_length_bitendian.value_forced = model.vars.var_length_bitendian.var_enum.MSB_FIRST
            model.vars.var_length_shift.value_forced = 0
            model.vars.var_length_minlength.value_forced = 0
            model.vars.var_length_maxlength.value_forced = 2047
            model.vars.var_length_includecrc.value_forced = True
            model.vars.var_length_adjust.value_forced = 0
            model.vars.var_length_byteendian.value_forced = model.vars.var_length_byteendian.var_enum.MSB_FIRST

    def _lookup_crc_from_fcs_type(self, model):
        if model.profile.inputs.fcs_type_802154.var_value == model.vars.fcs_type_802154.var_enum.TWO_BYTE:
            model.vars.fcs_type_802154.value_forced = model.vars.fcs_type_802154.var_enum.TWO_BYTE
            model.vars.crc_poly.value_forced = model.vars.crc_poly.var_enum.CCITT_16
            model.vars.crc_invert.value_forced = False
            model.vars.crc_pad_input.value_forced = False
            model.vars.crc_seed.value_forced = 0x00000000
        else: # : Four Octet CRC per IEEE802154-2020 7.2.11
            model.vars.fcs_type_802154.value_forced = model.vars.fcs_type_802154.var_enum.FOUR_BYTE
            model.vars.crc_poly.value_forced = model.vars.crc_poly.var_enum.ANSIX366_1979
            model.vars.crc_invert.value_forced = True
            model.vars.crc_pad_input.value_forced = True
            model.vars.crc_seed.value_forced = 0xFFFFFFFF
from pyradioconfig.parts.ocelot.profiles.Profile_LongRange import Profile_Long_Range_Ocelot
from pyradioconfig.parts.sol.profiles.sw_profile_outputs_common import sw_profile_outputs_common_sol

class Profile_Long_Range_Sol(Profile_Long_Range_Ocelot):

    def __init__(self):
        super().__init__()
        self._family = 'sol'
        self._sw_profile_outputs_common = sw_profile_outputs_common_sol()

    def build_advanced_profile_inputs(self, model, profile):
        self.make_linked_io(profile, model.vars.fec_en, 'Channel_Coding', readable_name="FEC Algorithm")
        self.make_linked_io(profile, model.vars.fpll_band, 'crystal', readable_name="RF Frequency Planning Band")

    def _fixed_longrange_vars(self, model):
        super()._fixed_longrange_vars(model)
        model.vars.ofdm_option.value_forced = model.vars.ofdm_option.var_enum.OPT1

    def build_optional_profile_inputs(self, model, profile):
        pass

    def _lookup_from_longrange_mode(self, model):
        #This function calculates some variables/registers based on the longrange mode

        #Read the mode and fec_en from the profile inputs (not yet written to model vars)
        longrange_mode = model.profile.inputs.longrange_mode.var_value
        fec_en = model.profile.inputs.fec_en.var_value

        # We need to modify the net bitrate (data rate) based on whether FEC is enabled or not
        if fec_en is not None and fec_en != model.vars.fec_en.var_enum.NONE:
            fec_factor=2
        else:
            fec_factor=1

        if longrange_mode == model.vars.longrange_mode.var_enum.LR_1p2k:
            model.vars.bitrate.value_forced = 1200//fec_factor
            model.vars.deviation.value_forced = 2400

        elif longrange_mode == model.vars.longrange_mode.var_enum.LR_2p4k:
            model.vars.bitrate.value_forced = 2400//fec_factor
            model.vars.deviation.value_forced = 4800
            if model.profile.inputs.base_frequency_hz.var_value <= 500e6:
                model.vars.AGC_GAINSTEPLIM0_CFLOOPDEL.value_forced = 25

        elif longrange_mode == model.vars.longrange_mode.var_enum.LR_4p8k:
            model.vars.bitrate.value_forced = 4800//fec_factor
            model.vars.deviation.value_forced = 9600

        elif longrange_mode == model.vars.longrange_mode.var_enum.LR_9p6k:
            model.vars.bitrate.value_forced = 9600//fec_factor
            model.vars.deviation.value_forced = 19200

        elif longrange_mode == model.vars.longrange_mode.var_enum.LR_19p2k:
            model.vars.bitrate.value_forced = 19200//fec_factor
            model.vars.deviation.value_forced = 38400

        elif longrange_mode == model.vars.longrange_mode.var_enum.LR_38p4k:
            model.vars.bitrate.value_forced = 38400//fec_factor
            model.vars.deviation.value_forced = 76800

        elif longrange_mode == model.vars.longrange_mode.var_enum.LR_80p0k:
            model.vars.bitrate.value_forced = 80000//fec_factor
            model.vars.deviation.value_forced = 160000
from pyradioconfig.parts.bobcat.profiles.Profile_Base import Profile_Base_Bobcat
from pyradioconfig.parts.common.profiles.viper_regs import build_modem_regs_viper
from pyradioconfig.parts.viper.profiles.sw_profile_outputs_common import sw_profile_outputs_common_viper
from pyradioconfig.calculator_model_framework.interfaces.iprofile import IProfile

class profile_base_viper(Profile_Base_Bobcat):

    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs"
        self._family = "viper"
        self._sw_profile_outputs_common = sw_profile_outputs_common_viper()

    def buildRegisterOutputs(self, model, profile):
        build_modem_regs_viper(model, profile)

    def build_info_profile_outputs(self, model, profile):
        self._sw_profile_outputs_common.build_info_outputs(model, profile)

    def build_hidden_profile_inputs(self, model, profile):
        Profile_Base_Bobcat.build_hidden_profile_inputs(self,model, profile)

        IProfile.make_hidden_input(profile, model.vars.syncword_trisync, 'Advanced',
                                   readable_name="TRI-SYNC Word Dection")

        IProfile.make_hidden_input(profile, model.vars.syncword_dualsync, 'Advanced',
                                   readable_name="DUAL-SYNC Word Dection")

        IProfile.make_hidden_input(profile, model.vars.modulator_select, 'Advanced',
                                   readable_name="Modulator Selection")

        IProfile.make_hidden_input(profile, model.vars.target_bwsel, 'Advanced',
                                   readable_name="Target for BW selection")
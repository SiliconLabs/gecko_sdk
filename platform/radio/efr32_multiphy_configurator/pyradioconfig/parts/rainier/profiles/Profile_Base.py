from pyradioconfig.parts.common.profiles.rainier_regs import build_modem_regs_rainier
from pyradioconfig.parts.rainier.profiles.sw_profile_outputs_common import SwProfileOutputsCommonRainier
from pyradioconfig.parts.bobcat.profiles.Profile_Base import Profile_Base_Bobcat
from pyradioconfig.calculator_model_framework.interfaces.iprofile import IProfile

class ProfileBaseRainier(Profile_Base_Bobcat):

    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs"
        self._family = "rainier"
        self._sw_profile_outputs_common = SwProfileOutputsCommonRainier()

    def buildRegisterOutputs(self, model, profile):
        build_modem_regs_rainier(model, profile)

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

        IProfile.make_linked_io(profile, model.vars.lock_bandwidth_hz, 'Advanced',
                                   readable_name="Lock Channel Bandwidth",value_limit_min=100, value_limit_max=3000000)
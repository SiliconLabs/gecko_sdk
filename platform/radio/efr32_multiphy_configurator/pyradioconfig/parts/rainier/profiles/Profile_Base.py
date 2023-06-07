from pyradioconfig.parts.viper.profiles.Profile_Base import profile_base_viper
from pyradioconfig.parts.common.profiles.rainier_regs import build_modem_regs_rainier
from pyradioconfig.parts.rainier.profiles.sw_profile_outputs_common import SwProfileOutputsCommonRainier

class ProfileBaseRainier(profile_base_viper):

    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs"
        self._family = "rainier"
        self._sw_profile_outputs_common = SwProfileOutputsCommonRainier()

    def buildRegisterOutputs(self, model, profile):
        build_modem_regs_rainier(model, profile)

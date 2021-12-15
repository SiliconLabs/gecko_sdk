from pyradioconfig.parts.bobcat.profiles.Profile_Base import Profile_Base_Bobcat
from pyradioconfig.parts.common.profiles.viper_regs import build_modem_regs_viper

class profile_base_viper(Profile_Base_Bobcat):

    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs"
        self._family = "viper"

    def buildRegisterOutputs(self, model, profile, family):
        build_modem_regs_viper(model, profile, family)

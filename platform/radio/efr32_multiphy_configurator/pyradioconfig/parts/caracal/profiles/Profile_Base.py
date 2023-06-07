from pyradioconfig.parts.bobcat.profiles.Profile_Base import Profile_Base_Bobcat
from pyradioconfig.parts.common.profiles.caracal_regs import build_momem_regs_caracal
from pyradioconfig.parts.caracal.profiles.sw_profile_outputs_common import sw_profile_outputs_common_bobcat


class Profile_Base_Caracal(Profile_Base_Bobcat):

    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs"
        self._family = "caracal"
        self._sw_profile_outputs_common = sw_profile_outputs_common_bobcat()

    def buildRegisterOutputs(self, model, profile):
        build_momem_regs_caracal(model, profile)

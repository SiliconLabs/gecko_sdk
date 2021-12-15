from pyradioconfig.parts.ocelot.profiles.Profile_WiSUN import Profile_WiSUN_Ocelot
from pyradioconfig.parts.common.profiles.bobcat_regs import build_modem_regs_bobcat
from pyradioconfig.parts.common.profiles.profile_common import buildCrcOutputs, buildFecOutputs, buildFrameOutputs, \
    buildWhiteOutputs

class Profile_WiSUN_Bobcat(Profile_WiSUN_Ocelot):

    def __init__(self):
        self._profileName = "WiSUN"
        self._readable_name = "WiSUN Profile"
        self._category = ""
        self._description = "Profile used for WiSUN PHYs"
        self._default = False
        self._activation_logic = ""
        self._family = "bobcat"

    def build_register_profile_outputs(self, model, profile):
        family = self._family
        build_modem_regs_bobcat(model, profile, family)
        buildFrameOutputs(model, profile, family)
        buildCrcOutputs(model, profile, family)
        buildWhiteOutputs(model, profile)
        buildFecOutputs(model, profile)
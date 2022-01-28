from pyradioconfig.parts.ocelot.profiles.Profile_WiSUN import Profile_WiSUN_Ocelot
from pyradioconfig.parts.common.profiles.margay_regs import build_modem_regs_margay
from pyradioconfig.parts.common.profiles.profile_common import buildCrcOutputs, buildFecOutputs, buildFrameOutputs, \
    buildWhiteOutputs
from pyradioconfig.parts.margay.profiles.sw_profile_outputs_common import sw_profile_outputs_common_margay


class Profile_WiSUN_Margay(Profile_WiSUN_Ocelot):

    def __init__(self):
        self._profileName = "WiSUN"
        self._readable_name = "Wi-SUN FSK Profile"
        self._category = ""
        self._description = "Profile used for Wi-SUN FSK PHYs"
        self._default = False
        self._activation_logic = ""
        self._family = "margay"
        self._sw_profile_outputs_common = sw_profile_outputs_common_margay()

    def build_register_profile_outputs(self, model, profile):
        build_modem_regs_margay(model, profile)
        buildFrameOutputs(model, profile, self._family)
        buildCrcOutputs(model, profile, self._family)
        buildWhiteOutputs(model, profile)
        buildFecOutputs(model, profile)

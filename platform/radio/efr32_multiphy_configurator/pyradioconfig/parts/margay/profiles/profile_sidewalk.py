from pyradioconfig.parts.ocelot.profiles.profile_sidewalk import ProfileSidewalkOcelot
from pyradioconfig.calculator_model_framework.interfaces.iprofile import IProfile
from pyradioconfig.parts.common.utils.units_multiplier import UnitsMultiplier
from pyradioconfig.parts.common.profiles.margay_regs import build_modem_regs_margay
from pyradioconfig.parts.common.profiles.profile_common import buildCrcOutputs, buildFecOutputs, buildFrameOutputs, \
    buildWhiteOutputs
from pyradioconfig.parts.margay.profiles.sw_profile_outputs_common import sw_profile_outputs_common_margay


class ProfileSidewalkMargay(ProfileSidewalkOcelot):

    fec_enabled_sync = 0x6F4E
    fec_disabled_sync = 0x904E #default

    def __init__(self):
        super().__init__()
        self._family = "margay"
        self._sw_profile_outputs_common = sw_profile_outputs_common_margay()

    def build_register_profile_outputs(self, model, profile):
        build_modem_regs_margay(model, profile)
        buildFrameOutputs(model, profile)
        buildCrcOutputs(model, profile)
        buildWhiteOutputs(model, profile)
        buildFecOutputs(model, profile)

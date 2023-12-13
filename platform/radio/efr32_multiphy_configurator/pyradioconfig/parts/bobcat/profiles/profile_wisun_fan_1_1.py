from pyradioconfig.parts.ocelot.profiles.profile_wisun_fan_1_1 import ProfileWisunFan1v1Ocelot
from pyradioconfig.parts.common.profiles.profile_common import buildCrcOutputs, buildFecOutputs, buildFrameOutputs, \
    buildWhiteOutputs
from pyradioconfig.parts.common.profiles.bobcat_regs import build_modem_regs_bobcat
from pyradioconfig.parts.bobcat.profiles.sw_profile_outputs_common import sw_profile_outputs_common_bobcat


class ProfileWisunFan1v1Bobcat(ProfileWisunFan1v1Ocelot):

    def __init__(self):
        super().__init__()
        self._family = "Bobcat"
        self._sw_profile_outputs_common = sw_profile_outputs_common_bobcat()

    def _fixed_wisun_vars(self, model):
        # Start with the inherited vars
        super()._fixed_wisun_vars(model)

        # Invoke ww tol overrides
        self._region_ww_wisun_tol_temp_overrides(model)

    def build_register_profile_outputs(self, model, profile):
        # Overriding this method to include modem regs for Bobcat
        build_modem_regs_bobcat(model, profile)
        buildFrameOutputs(model, profile)
        buildCrcOutputs(model, profile)
        buildWhiteOutputs(model, profile)
        buildFecOutputs(model, profile)
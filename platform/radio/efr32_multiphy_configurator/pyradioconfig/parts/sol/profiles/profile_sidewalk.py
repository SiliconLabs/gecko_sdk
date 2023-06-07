from pyradioconfig.parts.ocelot.profiles.profile_sidewalk import ProfileSidewalkOcelot
from pyradioconfig.parts.sol.profiles.sw_profile_outputs_common import sw_profile_outputs_common_sol


class ProfileSidewalkSol(ProfileSidewalkOcelot):

    fec_enabled_sync = 0x6F4E
    fec_disabled_sync = 0x904E #default

    def __init__(self):
        super().__init__()
        self._family = "sol"
        self._sw_profile_outputs_common = sw_profile_outputs_common_sol()

    def build_advanced_profile_inputs(self, model, profile):
        super().build_advanced_profile_inputs(model, profile)
        self.make_linked_io(profile, model.vars.fpll_band, 'crystal', readable_name="RF Frequency Planning Band")



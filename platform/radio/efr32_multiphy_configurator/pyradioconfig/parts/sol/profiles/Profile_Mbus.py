from pyradioconfig.parts.ocelot.profiles.Profile_Mbus import Profile_Mbus_Ocelot

class Profile_Mbus_Sol(Profile_Mbus_Ocelot):

    def __init__(self):
        super().__init__()
        self._family = "sol"

    def mbus_profile_radio_common(self, model):
        super().mbus_profile_radio_common(model)
        model.vars.ofdm_option.value_forced = model.vars.ofdm_option.var_enum.OPT1
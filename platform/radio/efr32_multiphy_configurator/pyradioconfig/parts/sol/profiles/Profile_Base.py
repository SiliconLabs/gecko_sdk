from pyradioconfig.parts.ocelot.profiles.Profile_Base import Profile_Base_Ocelot

class Profile_Base_Sol(Profile_Base_Ocelot):

    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs"
        self._family = "sol"

    def profile_calculate(self, model):

        #Call existing profile calculations
        super().profile_calculate(model)

        #Fixed variables (required inputs for other Profiles)
        #Using .value only so that we can force this in internal test PHYs
        model.vars.ofdm_option.value = model.vars.ofdm_option.var_enum.OPT1

from pyradioconfig.parts.common.profiles.Profile_Base import *



class Profile_Base_Nerio(Profile_Base):

    """
    Init internal variables
    """
    def __init__(self):
        super(self.__class__, self).__init__()
        self._description = "Profile used for most phy's on EFR32xG13 parts"
        self._family = "nerio"


    def buildProfileModel(self, model):
        profile = super().buildProfileModel(model)
        # adding this to support Signify PHYs for Nerio and Panther. Adding this as hidden input for all parts
        IProfile.make_hidden_input(profile, model.vars.fec_tx_enable, 'Channel_Coding',
                                   readable_name="Enable FEC for TX")
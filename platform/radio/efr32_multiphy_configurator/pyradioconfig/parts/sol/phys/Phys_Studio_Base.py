from pyradioconfig.parts.ocelot.phys.Phys_Studio_Base import PHYS_Studio_Base_Ocelot
from pyradioconfig.calculator_model_framework.decorators.phy_decorators import do_not_inherit_phys

@do_not_inherit_phys
class PHYS_Studio_Base_Sol(PHYS_Studio_Base_Ocelot):

    ##########2FSK PHYS##########

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-48
    def PHY_Studio_915M_2GFSK_2Mbps_500K(self, model, phy_name=None):
        phy = super().PHY_Studio_915M_2GFSK_2Mbps_500K(model, phy_name=phy_name)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-47
    def PHY_Studio_915M_2GFSK_500Kbps_175K_mi0p7(self, model, phy_name=None):
        phy = super().PHY_Studio_915M_2GFSK_500Kbps_175K_mi0p7(model, phy_name=phy_name)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-82
    def PHY_Studio_915M_2GFSK_600bps_800(self, model, phy_name=None):
        self._makePhy(model, model.profiles.Base, readable_name='915M 2GFSK 600Kbps 800', phy_name=phy_name)
        phy = super().PHY_Studio_868M_2GFSK_600bps_800(model, phy_name=phy_name)

        #Change to 915M center frequency
        phy.profile_inputs.base_frequency_hz.value = 915000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-49
    def PHY_Studio_868M_GMSK_500Kbps(self, model, phy_name=None):
        phy = super().PHY_Studio_868M_GMSK_500Kbps(model, phy_name=phy_name)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-51
    def PHY_Studio_868M_2GFSK_38p4Kbps_20K(self, model, phy_name=None):
        phy = super().PHY_Studio_868M_2GFSK_38p4Kbps_20K(model, phy_name=phy_name)
        return phy

    def PHY_Studio_868M_2GFSK_10Kbps_5K(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.Base, readable_name='868MHz 2GFSK 10Kbps 5KHz', phy_name=phy_name)

        # Start with the base function
        # Sets xtal tolerance to +/-20ppm total
        self.Studio_2GFSK_base(phy, model)

        # Add data-rate specific parameters
        phy.profile_inputs.bitrate.value = 10000
        phy.profile_inputs.deviation.value = 5000

        # Add band-specific parameters
        phy.profile_inputs.base_frequency_hz.value = 868000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-50
    def PHY_Studio_868M_2GFSK_600bps_800(self, model, phy_name=None):
        phy = super().PHY_Studio_868M_2GFSK_600bps_800(model, phy_name=phy_name)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-52
    def PHY_Studio_490M_2GFSK_38p4Kbps_20K(self, model, phy_name=None):
        phy = super().PHY_Studio_490M_2GFSK_38p4Kbps_20K(model, phy_name=phy_name)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-53
    def PHY_Studio_490M_2GFSK_10Kbps_5K(self, model, phy_name=None):
        phy = super().PHY_Studio_490M_2GFSK_10Kbps_5K(model, phy_name=phy_name)
        return phy

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGSOLVALTEST-2184
    def PHY_Datasheet_490M_2GFSK_10Kbps_25K_20ppm(self, model, phy_name=None):
        phy = super().PHY_Datasheet_490M_2GFSK_10Kbps_25K_20ppm(model, phy_name=phy_name)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-54
    def PHY_Studio_490M_2GFSK_2p4Kbps_1p2K(self, model, phy_name=None):
        phy = super().PHY_Studio_490M_2GFSK_2p4Kbps_1p2K(model, phy_name=phy_name)
        return phy

    ##########4FSK PHYS##########

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-46
    def PHY_Studio_915M_4GFSK_200Kbps_16p6K(self, model, phy_name=None):
        phy = super().PHY_Studio_915M_4GFSK_200Kbps_16p6K(model, phy_name=phy_name)
        return phy

    ##########OOK PHYS (tested by Apps)##########

    def PHY_Studio_915M_OOK_120kbps(self, model, phy_name=None):
        phy = super().PHY_Studio_915M_OOK_120kbps(model, phy_name=phy_name)
        return phy

    def PHY_Studio_915M_OOK_4p8kbps(self, model, phy_name=None):
        phy = super().PHY_Studio_915M_OOK_4p8kbps(model, phy_name=None)
        return phy



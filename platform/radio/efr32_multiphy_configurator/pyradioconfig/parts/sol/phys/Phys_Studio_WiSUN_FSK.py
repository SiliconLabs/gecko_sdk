from pyradioconfig.parts.ocelot.phys.Phys_Studio_WiSUN import PHYS_IEEE802154_WiSUN_Ocelot
from pyradioconfig.calculator_model_framework.decorators.phy_decorators import do_not_inherit_phys

@do_not_inherit_phys
class PHYS_IEEE802154_WiSUN_FSK_Sol(PHYS_IEEE802154_WiSUN_Ocelot):

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-30
    def PHY_IEEE802154_WISUN_868MHz_2GFSK_50kbps_1a_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, EU-868MHz, 1a (2FSK 50kbps mi=0.5)',
                            phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 1/17 (FEC off/on)
        # ChanPlanID: 32 (863_870_100, 100kHz spacing, Ch0 863.1MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 863100000
        phy.profile_inputs.channel_spacing_hz.value = 100000
        phy.profile_inputs.preamble_length.value = 8 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-31
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_50kbps_1b_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, NA-915MHz, 1b (2FSK 50kbps mi=1.0)',
                            phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 2/18 (FEC off/on)
        # ChanPlanID: 1 (902_928_200, 200kHz spacing, Ch0 902.2MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902200000
        phy.profile_inputs.channel_spacing_hz.value = 200000
        phy.profile_inputs.preamble_length.value = 8 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-32
    def PHY_IEEE802154_WISUN_920MHz_2GFSK_50kbps_1b_JP_ECHONET(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK,
                            readable_name='Wi-SUN ECHONET, JP-920MHz, 1b (2FSK 50kbps mi=1.0)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 2/18 (FEC off/on)
        # ChanPlanID: 21 (920_928_200, 200kHz spacing, Ch0 920.6MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 920600000
        phy.profile_inputs.channel_spacing_hz.value = 200000
        phy.profile_inputs.preamble_length.value = 8 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.TWO_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-33
    def PHY_IEEE802154_WISUN_470MHz_2GFSK_50kbps_1b_CN(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, CN-470MHz, 1b (2FSK 50kbps mi=1.0)',
                            phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 2/18 (FEC off/on)
        # ChanPlanID: TBD

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 470200000
        phy.profile_inputs.channel_spacing_hz.value = 200000
        phy.profile_inputs.preamble_length.value = 8 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-34
    def PHY_IEEE802154_WISUN_868MHz_2GFSK_100kbps_2a_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK,
                            readable_name='Wi-SUN FAN, EU-868MHz, 2a (2FSK 100kbps mi=0.5)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 3/19 (FEC off/on)
        # ChanPlanID: 33 (863_870_200, 200kHz spacing, Ch0 863.1MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 863100000
        phy.profile_inputs.channel_spacing_hz.value = 200000
        phy.profile_inputs.preamble_length.value = 8 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-35
    def PHY_IEEE802154_WISUN_470MHz_2GFSK_100kbps_2a_CN(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK,
                            readable_name='Wi-SUN FAN, CN-470MHz, 2a (2FSK 100kbps mi=0.5)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 3/19 (FEC off/on)
        # ChanPlanID: TBD

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 470200000
        phy.profile_inputs.channel_spacing_hz.value = 200000
        phy.profile_inputs.preamble_length.value = 8 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-36
    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2b_JP_ECHONET(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK,
                            readable_name='Wi-SUN ECHONET, JP-920MHz, 2b (2FSK 100kbps mi=1.0)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 4/20 (FEC off/on)
        # ChanPlanID: 22 (920_928_400, 400kHz spacing, Ch0 920.9MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 920900000
        phy.profile_inputs.channel_spacing_hz.value = 400000
        phy.profile_inputs.preamble_length.value = 15 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.TWO_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2b_JP(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, JP-920MHz, 2b (2FSK 100kbps mi=1.0)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 4/20 (FEC off/on)
        # ChanPlanID: 22 (920_928_400, 400kHz spacing, Ch0 920.9MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 920900000
        phy.profile_inputs.channel_spacing_hz.value = 400000
        phy.profile_inputs.preamble_length.value = 8 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-37
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_150kbps_3_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, NA-915MHz, 3 (2FSK 150kbps mi=0.5)',
                            phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 5/21 (FEC off/on)
        # ChanPlanID: 2 (902_928_400, 400kHz spacing, Ch0 902.4MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode3

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902400000
        phy.profile_inputs.channel_spacing_hz.value = 400000
        phy.profile_inputs.preamble_length.value = 12 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-85
    def PHY_IEEE802154_WISUN_868MHz_2GFSK_150kbps_3_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, EU-868MHz, 3 (2FSK 150kbps mi=0.5)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 5/21 (FEC off/on)
        # ChanPlanID: 33 (863_870_200, 200kHz spacing, Ch0 863.1MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode3

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 863100000
        phy.profile_inputs.channel_spacing_hz.value = 200000
        phy.profile_inputs.preamble_length.value = 12 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-38
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_200kbps_4a_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, NA-915MHz, 4a (2GFSK 200kbps mi=0.5)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 6/22 (FEC off/on)
        # ChanPlanID: 2 (902_928_400, 400kHz spacing, Ch0 902.4MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode4a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902400000
        phy.profile_inputs.channel_spacing_hz.value = 400000
        phy.profile_inputs.preamble_length.value = 12 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-39
    def PHY_IEEE802154_WISUN_920MHz_2GFSK_200kbps_4b_JP(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, JP-920MHz, 4b (2GFSK 200kbps mi=1.0)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 7/23 (FEC off/on)
        # ChanPlanID: 23 (920_928_600, 600kHz spacing, Ch0 920.8MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode4b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 920800000
        phy.profile_inputs.channel_spacing_hz.value = 600000
        phy.profile_inputs.preamble_length.value = 12 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-40
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_300kbps_5_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN_FSK, readable_name='Wi-SUN FAN, NA-915MHz, 5 (2GFSK 300kbps mi=0.5)', phy_name=phy_name)

        ### Frequency Band and Channel Parameters ###
        # PhyModeID: 8/24 (FEC off/on)
        # ChanPlanID: 3 (902_928_600, 600kHz spacing, Ch0 902.6MHz)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode5

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902600000
        phy.profile_inputs.channel_spacing_hz.value = 600000
        phy.profile_inputs.preamble_length.value = 24 * 8
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy
from pyradioconfig.calculator_model_framework.interfaces.iphy import IPhy


class PHYS_IEEE802154_WiSUN_Ocelot(IPhy):

    ### EU Region ###

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-166
    def PHY_IEEE802154_WISUN_868MHz_2GFSK_50kbps_1a_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, EU-868MHz, 1a (2FSK 50kbps mi=0.5)', phy_name=phy_name)

        #Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1a

        #Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 863100000 # FAN EU Mode #1a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 100000 # FAN EU Mode #1a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8  # FAN EU Mode #1a, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        #Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    #Apps-verified
    def PHY_IEEE802154_WISUN_873MHz_2GFSK_50kbps_1a_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, EU-873MHz, 1a (2FSK 50kbps mi=0.5)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 870100000  # FAN EU Mode #1a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 100000  # FAN EU Mode #1a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8  # FAN EU Mode #1a, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-165
    def PHY_IEEE802154_WISUN_868MHz_2GFSK_100kbps_2a_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, EU-868MHz, 2a (2FSK 100kbps mi=0.5)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2a

        #Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 863100000 # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000 # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8  # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Apps-verified
    def PHY_IEEE802154_WISUN_873MHz_2GFSK_100kbps_2a_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, EU-873MHz, 2a (2FSK 100kbps mi=0.5)',
                            phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 870200000  # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000  # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8  # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Apps-verified
    def PHY_IEEE802154_WISUN_868MHz_2GFSK_150kbps_3_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, EU-868MHz, 3 (2FSK 150kbps mi=0.5)',
                            phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode3

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 863100000  # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000  # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 12 * 8  # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

    # Apps-verified
    def PHY_IEEE802154_WISUN_873MHz_2GFSK_150kbps_3_EU(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, EU-873MHz, 3 (2FSK 150kbps mi=0.5)',
                            phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode3

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 870200000  # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000  # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 12 * 8  # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000


    ### NA Region ###

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-168
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_50kbps_1b_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, NA-915MHz, 1b (2FSK 50kbps mi=1.0)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1b

        #Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902200000 # FAN NA Mode #1b, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000 # FAN NA Mode #1b, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8  # FAN NA Mode #1b, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Apps-verified
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_100kbps_2a_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN,
                            readable_name='Wi-SUN FAN, NA-915MHz, 2a (2FSK 100kbps mi=0.5)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902200000  # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000  # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8  # FAN EU Mode #2a, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-167
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_150kbps_3_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, NA-915MHz, 3 (2FSK 150kbps mi=0.5)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode3

        #Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902400000 # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 400000 # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 12 * 8 # FAN NA Mode #3, WiSUN 20140727-PHY-Profile Table 6
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    #Apps-verified
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_200kbps_4a_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN,
                            readable_name='Wi-SUN FAN, NA-915MHz, 4a (2GFSK 200kbps mi=0.5)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode4a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902400000
        phy.profile_inputs.channel_spacing_hz.value = 400000
        phy.profile_inputs.preamble_length.value = 12 * 8
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

    # Apps-verified
    def PHY_IEEE802154_WISUN_915MHz_2GFSK_300kbps_5_NA(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN,
                            readable_name='Wi-SUN FAN, NA-915MHz, 5 (2GFSK 300kbps mi=0.5)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode5

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 902600000
        phy.profile_inputs.channel_spacing_hz.value = 600000
        phy.profile_inputs.preamble_length.value = 24 * 8
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

    ### JP Region ###

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-170
    def PHY_IEEE802154_WISUN_920MHz_2GFSK_50kbps_1b_JP_ECHONET(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN ECHONET, JP-920MHz, 1b (2FSK 50kbps mi=1.0)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1b

        #Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 920600000 # Echonet JP Mode #1b, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000 # Echonet JP Mode #1b, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8 # Echonet JP Mode #1b, WiSUN 20140727-PHY-Profile Table 5
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.CCITT_16 # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-169
    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2b_JP_ECHONET(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN ECHONET, JP-920MHz, 2b (2FSK 100kbps mi=1.0)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2b

        #Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 920900000 # Echonet JP Mode #2b, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 400000 # Echonet JP Mode #2b, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 15 * 8 # Echonet JP Mode #2b, WiSUN 20140727-PHY-Profile Table 5
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.CCITT_16 # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    #Apps-verified
    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2b_JP(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, JP-920MHz, 2b (2FSK 100kbps mi=1.0)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 920900000
        phy.profile_inputs.channel_spacing_hz.value = 400000
        phy.profile_inputs.preamble_length.value = 8 * 8
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    #Apps-verified
    def PHY_IEEE802154_WISUN_920MHz_2GFSK_200kbps_4b_JP(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN,
                            readable_name='Wi-SUN FAN, JP-920MHz, 4b (2GFSK 200kbps mi=1.0)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode4b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 920800000
        phy.profile_inputs.channel_spacing_hz.value = 600000
        phy.profile_inputs.preamble_length.value = 12 * 8
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

    ### CN Region ###

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-1218
    def PHY_IEEE802154_WISUN_470MHz_2GFSK_50kbps_1b_CN(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, CN-470MHz, 1b (2FSK 50kbps mi=1.0)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode1b

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 470200000  # FAN CN Mode #1b, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000  # FAN CN Mode #1b, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8  # FAN CN Mode #1b, WiSUN 20140727-PHY-Profile Table 5
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy

    # Owner: Casey Weltzin
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-1219
    def PHY_IEEE802154_WISUN_470MHz_2GFSK_100kbps_2a_CN(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.WiSUN, readable_name='Wi-SUN FAN, CN-470MHz, 2a (2FSK 100kbps mi=0.5)', phy_name=phy_name)

        # Select the correct SUNFSK mode
        phy.profile_inputs.wisun_mode.value = model.vars.wisun_mode.var_enum.Mode2a

        # Define WiSUN Profile / Region specific inputs
        phy.profile_inputs.base_frequency_hz.value = 470200000  # FAN CN Mode #2a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.channel_spacing_hz.value = 200000  # FAN CN Mode #2a, WiSUN 20140727-PHY-Profile Table 3
        phy.profile_inputs.preamble_length.value = 8 * 8  # FAN CN Mode #2a, WiSUN 20140727-PHY-Profile Table 5
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.ANSIX366_1979  # 802.15.4-2015, 7.2.10

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        return phy
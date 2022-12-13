from pyradioconfig.calculator_model_framework.interfaces.iphy import IPhy


class WisunFanChannelParams():

    wisun_operating_mode_info = {'Mode1a': ('50','0.5'),
                                 'Mode1b': ('50','1.0'),
                                 'Mode2a': ('100', '0.5'),
                                 'Mode2b': ('100', '1.0'),
                                 'Mode3': ('150', '0.5'),
                                 'Mode4a': ('200', '0.5'),
                                 'Mode4b': ('200', '1.0'),
                                 'Mode5': ('300', '0.5'),
                                 }

    def __init__(self, wisun_reg_domain, wisun_operating_class, wisun_mode, channel_spacing_hz, base_frequency_hz, band_string):
        self.wisun_reg_domain = wisun_reg_domain
        self.wisun_operating_class = wisun_operating_class
        self.wisun_mode = wisun_mode
        self.channel_spacing_hz = channel_spacing_hz
        self.base_frequency_hz = base_frequency_hz
        self.readable_name = self._get_readable_name(band_string)

    def _get_readable_name(self, band_string):
        standard_string = 'Wi-SUN FAN'
        mode_string = self.wisun_mode[4:]
        rate_string = self.wisun_operating_mode_info[self.wisun_mode][0]
        mi_string = self.wisun_operating_mode_info[self.wisun_mode][1]
        return '%s, %s, %s (2FSK %skbps mi=%s)' %(standard_string, band_string, mode_string, rate_string, mi_string)

class PhysStudioWisunFanJumbo(IPhy):

    # Helper method to fill out all of the PHY contents
    def _make_wisun_fan_phy(self, model, wisun_fan_channel_params, phy_name=None):
        phy = self._makePhy(model, model.profiles.wisun_fan_1_0,
                            readable_name=wisun_fan_channel_params.readable_name,
                            phy_name=phy_name)

        # Wi-SUN Inputs
        phy.profile_inputs.wisun_mode.value = getattr(model.vars.wisun_mode.var_enum, wisun_fan_channel_params.wisun_mode)
        phy.profile_inputs.wisun_reg_domain.value = getattr(model.vars.wisun_reg_domain.var_enum, wisun_fan_channel_params.wisun_reg_domain)
        phy.profile_inputs.wisun_operating_class.value = wisun_fan_channel_params.wisun_operating_class

        # Default xtal frequency of 38.4MHz
        self._set_xtal_frequency(model, phy)

        # Temporary redundant inputs for base frequency and channel spacing (required due to Studio UI limitations)
        phy.profile_inputs.base_frequency_hz.value = wisun_fan_channel_params.base_frequency_hz
        phy.profile_inputs.channel_spacing_hz.value = wisun_fan_channel_params.channel_spacing_hz

        return phy

    def _set_xtal_frequency(self, model, phy):
        phy.profile_inputs.xtal_frequency_hz.value = 38400000

    ### CN Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_470MHz_2GFSK_50kbps_1b_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN',1,'Mode1b',200000, 470200000, 'CN-470MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_470MHz_2GFSK_100kbps_2a_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN',1,'Mode2a',200000, 470200000, 'CN-470MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_470MHz_2GFSK_150kbps_3_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN',1,'Mode3',200000, 470200000, 'CN-470MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_780MHz_2GFSK_50kbps_1b_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN',2,'Mode1b',200000, 779200000, 'CN-780MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_780MHz_2GFSK_100kbps_2a_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN',2,'Mode2a',200000, 779200000, 'CN-780MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 3

    def PHY_IEEE802154_WISUN_780MHz_2GFSK_150kbps_3_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN', 3, 'Mode3', 400000, 779400000, 'CN-780MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_780MHz_2GFSK_200kbps_4a_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN', 3, 'Mode4a', 400000, 779400000, 'CN-780MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_780MHz_2GFSK_300kbps_5_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN', 3, 'Mode5', 400000, 779400000, 'CN-780MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 4

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_50kbps_1b_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN', 4, 'Mode1b', 250000, 920625000, 'CN-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2a_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN', 4, 'Mode2a', 250000, 920625000, 'CN-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_150kbps_3_CN(self, model, phy_name=None):
        params = WisunFanChannelParams('CN', 4, 'Mode3', 250000, 920625000, 'CN-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### EU Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_868MHz_2GFSK_50kbps_1a_EU(self, model, phy_name=None):
        params = WisunFanChannelParams('EU', 1, 'Mode1a', 100000, 863100000, 'EU-863MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_868MHz_2GFSK_100kbps_2a_EU(self, model, phy_name=None):
        params = WisunFanChannelParams('EU', 2, 'Mode2a', 200000, 863100000, 'EU-863MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_868MHz_2GFSK_150kbps_3_EU(self, model, phy_name=None):
        params = WisunFanChannelParams('EU', 2, 'Mode3', 200000, 863100000, 'EU-863MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 3

    def PHY_IEEE802154_WISUN_873MHz_2GFSK_50kbps_1a_EU(self, model, phy_name=None):
        params = WisunFanChannelParams('EU', 3, 'Mode1a', 100000, 870100000, 'EU-870MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 4

    def PHY_IEEE802154_WISUN_873MHz_2GFSK_100kbps_2a_EU(self, model, phy_name=None):
        params = WisunFanChannelParams('EU', 4, 'Mode2a', 200000, 870200000, 'EU-870MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_873MHz_2GFSK_150kbps_3_EU(self, model, phy_name=None):
        params = WisunFanChannelParams('EU', 4, 'Mode3', 200000, 870200000, 'EU-870MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### IN Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_866MHz_2GFSK_50kbps_1a_IN(self, model, phy_name=None):
        params = WisunFanChannelParams('IN', 1, 'Mode1a', 100000, 865100000, 'IN-866MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_866MHz_2GFSK_100kbps_2a_IN(self, model, phy_name=None):
        params = WisunFanChannelParams('IN', 2, 'Mode2a', 200000, 865100000, 'IN-866MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_866MHz_2GFSK_150kbps_3_IN(self, model, phy_name=None):
        params = WisunFanChannelParams('IN', 2, 'Mode3', 200000, 865100000, 'IN-866MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### SG Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_867MHz_2GFSK_50kbps_1a_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 1, 'Mode1a', 100000, 866100000, 'SG-867MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_867MHz_2GFSK_100kbps_2a_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 2, 'Mode2a', 200000, 866100000, 'SG-867MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_867MHz_2GFSK_150kbps_3_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 2, 'Mode3', 200000, 866100000, 'SG-867MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 3

    def PHY_IEEE802154_WISUN_867MHz_2GFSK_200kbps_4a_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 3, 'Mode4a', 400000, 866300000, 'SG-867MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_867MHz_2GFSK_300kbps_5_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 3, 'Mode5', 400000, 866300000, 'SG-867MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 4

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_50kbps_1b_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 4, 'Mode1b', 200000, 920200000, 'SG-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2a_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 4, 'Mode2a', 200000, 920200000, 'SG-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 5

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_150kbps_3_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 5, 'Mode3', 400000, 920400000, 'SG-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_200kbps_4a_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 5, 'Mode4a', 400000, 920400000, 'SG-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_300kbps_5_SG(self, model, phy_name=None):
        params = WisunFanChannelParams('SG', 5, 'Mode5', 400000, 920400000, 'SG-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### MX Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_50kbps_1b_MX(self, model, phy_name=None):
        params = WisunFanChannelParams('MX', 1, 'Mode1b', 200000, 902200000, 'MX-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_100kbps_2a_MX(self, model, phy_name=None):
        params = WisunFanChannelParams('MX', 1, 'Mode2a', 200000, 902200000, 'MX-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_150kbps_3_MX(self, model, phy_name=None):
        params = WisunFanChannelParams('MX', 2, 'Mode3', 400000, 902400000, 'MX-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_200kbps_4a_MX(self, model, phy_name=None):
        params = WisunFanChannelParams('MX', 2, 'Mode4a', 400000, 902400000, 'MX-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_300kbps_5_MX(self, model, phy_name=None):
        params = WisunFanChannelParams('MX', 2, 'Mode5', 400000, 902400000, 'MX-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### NA Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_50kbps_1b_NA(self, model, phy_name=None):
        params = WisunFanChannelParams('NA', 1, 'Mode1b', 200000, 902200000, 'NA-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_100kbps_2a_NA(self, model, phy_name=None):
        params = WisunFanChannelParams('NA', 1, 'Mode2a', 200000, 902200000, 'NA-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_150kbps_3_NA(self, model, phy_name=None):
        params = WisunFanChannelParams('NA', 2, 'Mode3', 400000, 902400000, 'NA-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_200kbps_4a_NA(self, model, phy_name=None):
        params = WisunFanChannelParams('NA', 2, 'Mode4a', 400000, 902400000, 'NA-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 3

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_300kbps_5_NA(self, model, phy_name=None):
        params = WisunFanChannelParams('NA', 3, 'Mode5', 600000, 902600000, 'NA-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### BZ Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_50kbps_1b_BZ(self, model, phy_name=None):
        params = WisunFanChannelParams('BZ', 1, 'Mode1b', 200000, 902200000, 'BZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_100kbps_2a_BZ(self, model, phy_name=None):
        params = WisunFanChannelParams('BZ', 1, 'Mode2a', 200000, 902200000, 'BZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_150kbps_3_BZ(self, model, phy_name=None):
        params = WisunFanChannelParams('BZ', 2, 'Mode3', 400000, 902400000, 'BZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_200kbps_4a_BZ(self, model, phy_name=None):
        params = WisunFanChannelParams('BZ', 2, 'Mode4a', 400000, 902400000, 'BZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 3

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_300kbps_5_BZ(self, model, phy_name=None):
        params = WisunFanChannelParams('BZ', 3, 'Mode5', 600000, 902600000, 'BZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### AZ_NZ Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_50kbps_1b_AZ_NZ(self, model, phy_name=None):
        params = WisunFanChannelParams('AZ_NZ', 1, 'Mode1b', 200000, 915200000, 'AZ_NZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_100kbps_2a_AZ_NZ(self, model, phy_name=None):
        params = WisunFanChannelParams('AZ_NZ', 1, 'Mode2a', 200000, 915200000, 'AZ_NZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_150kbps_3_AZ_NZ(self, model, phy_name=None):
        params = WisunFanChannelParams('AZ_NZ', 2, 'Mode3', 400000, 915400000, 'AZ_NZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_200kbps_4a_AZ_NZ(self, model, phy_name=None):
        params = WisunFanChannelParams('AZ_NZ', 2, 'Mode4a', 400000, 915400000, 'AZ_NZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_300kbps_5_AZ_NZ(self, model, phy_name=None):
        params = WisunFanChannelParams('AZ_NZ', 2, 'Mode5', 400000, 915400000, 'AZ_NZ-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### KR Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_917MHz_2GFSK_50kbps_1b_KR(self, model, phy_name=None):
        params = WisunFanChannelParams('KR', 1, 'Mode1b', 200000, 917100000, 'KR-917MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_917MHz_2GFSK_100kbps_2a_KR(self, model, phy_name=None):
        params = WisunFanChannelParams('KR', 1, 'Mode2a', 200000, 917100000, 'KR-917MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_917MHz_2GFSK_150kbps_3_KR(self, model, phy_name=None):
        params = WisunFanChannelParams('KR', 2, 'Mode3', 400000, 917300000, 'KR-917MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_917MHz_2GFSK_200kbps_4a_KR(self, model, phy_name=None):
        params = WisunFanChannelParams('KR', 2, 'Mode4a', 400000, 917300000, 'KR-917MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_917MHz_2GFSK_300kbps_5_KR(self, model, phy_name=None):
        params = WisunFanChannelParams('KR', 2, 'Mode5', 400000, 917300000, 'KR-917MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### PH Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_50kbps_1b_PH(self, model, phy_name=None):
        params = WisunFanChannelParams('PH', 1, 'Mode1b', 200000, 915200000, 'PH-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_100kbps_2a_PH(self, model, phy_name=None):
        params = WisunFanChannelParams('PH', 1, 'Mode2a', 200000, 915200000, 'PH-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_150kbps_3_PH(self, model, phy_name=None):
        params = WisunFanChannelParams('PH', 2, 'Mode3', 400000, 915400000, 'PH-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_200kbps_4a_PH(self, model, phy_name=None):
        params = WisunFanChannelParams('PH', 2, 'Mode4a', 400000, 915400000, 'PH-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_915MHz_2GFSK_300kbps_5_PH(self, model, phy_name=None):
        params = WisunFanChannelParams('PH', 2, 'Mode5', 400000, 915400000, 'PH-915MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### MY Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_919MHz_2GFSK_50kbps_1b_MY(self, model, phy_name=None):
        params = WisunFanChannelParams('MY', 1, 'Mode1b', 200000, 919200000, 'MY-919MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_919MHz_2GFSK_100kbps_2a_MY(self, model, phy_name=None):
        params = WisunFanChannelParams('MY', 1, 'Mode2a', 200000, 919200000, 'MY-919MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_919MHz_2GFSK_150kbps_3_MY(self, model, phy_name=None):
        params = WisunFanChannelParams('MY', 2, 'Mode3', 400000, 919400000, 'MY-919MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_919MHz_2GFSK_200kbps_4a_MY(self, model, phy_name=None):
        params = WisunFanChannelParams('MY', 2, 'Mode4a', 400000, 919400000, 'MY-919MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_919MHz_2GFSK_300kbps_5_MY(self, model, phy_name=None):
        params = WisunFanChannelParams('MY', 2, 'Mode5', 400000, 919400000, 'MY-919MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### HK Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_50kbps_1b_HK(self, model, phy_name=None):
        params = WisunFanChannelParams('HK', 1, 'Mode1b', 200000, 920200000, 'HK-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2a_HK(self, model, phy_name=None):
        params = WisunFanChannelParams('HK', 1, 'Mode2a', 200000, 920200000, 'HK-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_150kbps_3_HK(self, model, phy_name=None):
        params = WisunFanChannelParams('HK', 2, 'Mode3', 400000, 920400000, 'HK-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_200kbps_4a_HK(self, model, phy_name=None):
        params = WisunFanChannelParams('HK', 2, 'Mode4a', 400000, 920400000, 'HK-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_300kbps_5_HK(self, model, phy_name=None):
        params = WisunFanChannelParams('HK', 2, 'Mode5', 400000, 920400000, 'HK-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### TH Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_50kbps_1b_TH(self, model, phy_name=None):
        params = WisunFanChannelParams('TH', 1, 'Mode1b', 200000, 920200000, 'TH-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2a_TH(self, model, phy_name=None):
        params = WisunFanChannelParams('TH', 1, 'Mode2a', 200000, 920200000, 'TH-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_150kbps_3_TH(self, model, phy_name=None):
        params = WisunFanChannelParams('TH', 2, 'Mode3', 400000, 920400000, 'TH-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_200kbps_4a_TH(self, model, phy_name=None):
        params = WisunFanChannelParams('TH', 2, 'Mode4a', 400000, 920400000, 'TH-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_300kbps_5_TH(self, model, phy_name=None):
        params = WisunFanChannelParams('TH', 2, 'Mode5', 400000, 920400000, 'TH-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### VN Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_50kbps_1b_VN(self, model, phy_name=None):
        params = WisunFanChannelParams('VN', 1, 'Mode1b', 200000, 920200000, 'VN-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2a_VN(self, model, phy_name=None):
        params = WisunFanChannelParams('VN', 1, 'Mode2a', 200000, 920200000, 'VN-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_150kbps_3_VN(self, model, phy_name=None):
        params = WisunFanChannelParams('VN', 2, 'Mode3', 400000, 920400000, 'VN-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_200kbps_4a_VN(self, model, phy_name=None):
        params = WisunFanChannelParams('VN', 2, 'Mode4a', 400000, 920400000, 'VN-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_300kbps_5_VN(self, model, phy_name=None):
        params = WisunFanChannelParams('VN', 2, 'Mode5', 400000, 920400000, 'VN-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### JP Region PHYs From Wi-SUN FAN 1.0 Spec###

    # Operating Class 1

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_50kbps_1b_JP(self, model, phy_name=None):
        params = WisunFanChannelParams('JP', 1, 'Mode1b', 200000, 920600000, 'JP-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 2

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_100kbps_2b_JP(self, model, phy_name=None):
        params = WisunFanChannelParams('JP', 2, 'Mode2b', 400000, 920900000, 'JP-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_150kbps_3_JP(self, model, phy_name=None):
        params = WisunFanChannelParams('JP', 2, 'Mode3', 400000, 920900000, 'JP-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # Operating Class 3

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_200kbps_4b_JP(self, model, phy_name=None):
        params = WisunFanChannelParams('JP', 3, 'Mode4b', 600000, 920800000, 'JP-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_IEEE802154_WISUN_920MHz_2GFSK_300kbps_5_JP(self, model, phy_name=None):
        params = WisunFanChannelParams('JP', 3, 'Mode5', 600000, 920800000, 'JP-920MHz')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

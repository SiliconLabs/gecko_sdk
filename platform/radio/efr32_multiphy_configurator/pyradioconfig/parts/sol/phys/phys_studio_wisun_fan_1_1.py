from pyradioconfig.parts.ocelot.phys.phys_studio_wisun_fan_1_1 import PhysStudioWisunFan1v1Ocelot, WisunFan1v1ChannelParamsOcelot

class WisunFan1v1ChannelParamsSol(WisunFan1v1ChannelParamsOcelot):
    #Inherit all
    pass

class PhysStudioWisunFan1v1Sol(PhysStudioWisunFan1v1Ocelot):

    ### EU Region OFDM PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 33

    def PHY_WISUN_FAN_1v1_863MHz_Plan33_OFDM_OPT4_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('EU', 84, 33, 200000, 863100000,
                                          'Wi-SUN FAN, EU 863-870 MHz, OFDM OPTION 4')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 35

    def PHY_WISUN_FAN_1v1_870MHz_Plan35_OFDM_OPT4_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('EU', 84, 35, 200000, 870200000,
                                             'Wi-SUN FAN, EU 870-876 MHz, OFDM OPTION 4')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 37

    def PHY_WISUN_FAN_1v1_863MHz_Plan37_OFDM_OPT4_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('EU', 84, 37, 200000, 863100000,
                                             'Wi-SUN FAN, EU 863-876 MHz, OFDM OPTION 4')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### NA Region OFDM PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 1

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_OFDM_OPT4_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('NA', 84, 1, 200000, 902200000,
                                             'Wi-SUN FAN, NA 902-928 MHz, OFDM OPTION 4')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 2

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_OFDM_OPT3_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('NA', 68, 2, 400000, 902400000,
                                             'Wi-SUN FAN, NA 902-928 MHz, OFDM OPTION 3')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 4

    def PHY_WISUN_FAN_1v1_915MHz_Plan4_OFDM_OPT2_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('NA', 51, 4, 800000, 902800000,
                                             'Wi-SUN FAN, NA 902-928 MHz, OFDM OPTION 2')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 5

    def PHY_WISUN_FAN_1v1_915MHz_Plan5_OFDM_OPT1_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('NA', 34, 5, 1200000, 903200000,
                                             'Wi-SUN FAN, NA 902-928 MHz, OFDM OPTION 1')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### BZ Region OFDM PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 1

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_OFDM_OPT4_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('BZ', 84, 1, 200000, 902200000,
                                             'Wi-SUN FAN, BZ 902-928 MHz, OFDM OPTION 4')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 2

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_OFDM_OPT3_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('BZ', 68, 2, 400000, 902400000,
                                             'Wi-SUN FAN, BZ 902-928 MHz, OFDM OPTION 3')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 4

    def PHY_WISUN_FAN_1v1_915MHz_Plan4_OFDM_OPT2_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('BZ', 51, 4, 800000, 902800000,
                                             'Wi-SUN FAN, BZ 902-928 MHz, OFDM OPTION 2')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 5

    def PHY_WISUN_FAN_1v1_915MHz_Plan5_OFDM_OPT1_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('BZ', 34, 5, 1200000, 903200000,
                                             'Wi-SUN FAN, BZ 902-928 MHz, OFDM OPTION 1')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### JP Region OFDM PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 21

    def PHY_WISUN_FAN_1v1_920MHz_Plan21_OFDM_OPT4_JP(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('JP', 84, 21, 200000, 920600000,
                                             'Wi-SUN FAN, JP 920-928 MHz, OFDM OPTION 4')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 22

    def PHY_WISUN_FAN_1v1_920MHz_Plan22_OFDM_OPT3_JP(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('JP', 68, 22, 400000, 920900000,
                                             'Wi-SUN FAN, JP 920-928 MHz, OFDM OPTION 3')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 24

    def PHY_WISUN_FAN_1v1_920MHz_Plan24_OFDM_OPT2_JP(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('JP', 51, 24, 800000, 921100000,
                                             'Wi-SUN FAN, JP 920-928 MHz, OFDM OPTION 2')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### IN Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 40
    def PHY_WISUN_FAN_1v1_866MHz_Plan40_OFDM_OPT4_IN(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('IN', 84, 40, 200000, 865100000,
                                             'Wi-SUN FAN, IN 865-867 MHz, OFDM OPTION 4')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy


    ### SG Region PHYs From Wi-SUN FAN 1.1 Spec###
    
    # ChanPlanID 33
    def PHY_WISUN_FAN_1v1_867MHz_Plan33_OFDM_OPT4_SG(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsSol('SG', 84, 33, 200000, 866100000,
                                             'Wi-SUN FAN, SG 865-867 MHz, OFDM OPTION 4')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy
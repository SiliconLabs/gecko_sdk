from pyradioconfig.calculator_model_framework.decorators.phy_decorators import do_not_inherit_phys
from pyradioconfig.parts.jumbo.phys.phys_studio_wisun_fan_1_1 import PhysStudioWisunFan1v1Jumbo, WisunFan1v1ChannelParamsJumbo


class WisunFan1v1ChannelParamsOcelot(WisunFan1v1ChannelParamsJumbo):
    #Inherit all
    pass


class PhysStudioWisunFan1v1Ocelot(PhysStudioWisunFan1v1Jumbo):

    def _set_xtal_frequency(self, model, phy):
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

    # Adding FEC-enabled PHYs

    ### EU Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 32

    def PHY_WISUN_FAN_1v1_863MHz_Plan32_2FSK_1a_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 17, 32, 100000, 863100000,
                                               'Wi-SUN FAN, EU 863-870 MHz, Mode1a (2FSK 50kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 33

    def PHY_WISUN_FAN_1v1_863MHz_Plan33_2FSK_2a_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 19, 33, 200000, 863100000,
                                               'Wi-SUN FAN, EU 863-870 MHz, Mode2a (2FSK 100kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_863MHz_Plan33_2FSK_3_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 21, 33, 200000, 863100000,
                                               'Wi-SUN FAN, EU 863-870 MHz, Mode3 (2FSK 150kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 34

    def PHY_WISUN_FAN_1v1_870MHz_Plan34_2FSK_1a_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 17, 34, 100000, 870100000,
                                               'Wi-SUN FAN, EU 870-876 MHz, Mode1a (2FSK 50kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 35

    def PHY_WISUN_FAN_1v1_870MHz_Plan35_2FSK_2a_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 19, 35, 200000, 870200000,
                                               'Wi-SUN FAN, EU 870-876 MHz, Mode2a (2FSK 100kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_870MHz_Plan35_2FSK_3_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 21, 35, 200000, 870200000,
                                               'Wi-SUN FAN, EU 870-876 MHz, Mode3 (2FSK 150kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 36

    def PHY_WISUN_FAN_1v1_863MHz_Plan36_2FSK_1a_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 17, 36, 100000, 863100000,
                                               'Wi-SUN FAN, EU 863-876 MHz, Mode1a (2FSK 50kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 37

    def PHY_WISUN_FAN_1v1_863MHz_Plan37_2FSK_2a_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 19, 37, 200000, 863100000,
                                               'Wi-SUN FAN, EU 863-876 MHz, Mode2a (2FSK 100kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_863MHz_Plan37_2FSK_3_EU_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 21, 37, 200000, 863100000,
                                               'Wi-SUN FAN, EU 863-876 MHz, Mode3 (2FSK 150kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### NA Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 1

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_2FSK_1b_NA_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 18, 1, 200000, 902200000,
                                               'Wi-SUN FAN, NA 902-928 MHz, Mode1b (2FSK 50kbps mi=1.0), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_2FSK_2a_NA_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 19, 1, 200000, 902200000,
                                               'Wi-SUN FAN, NA 902-928 MHz, Mode2a (2FSK 100kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 2

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_2FSK_3_NA_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 21, 2, 400000, 902400000,
                                               'Wi-SUN FAN, NA 902-928 MHz, Mode3 (2FSK 150kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_2FSK_4a_NA_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 22, 2, 400000, 902400000,
                                               'Wi-SUN FAN, NA 902-928 MHz, Mode4a (2FSK 200kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 3

    def PHY_WISUN_FAN_1v1_915MHz_Plan3_2FSK_5_NA_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 24, 3, 600000, 902600000,
                                               'Wi-SUN FAN, NA 902-928 MHz, Mode5 (2FSK 300kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### BZ Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 1

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_2FSK_1b_BZ_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 18, 1, 200000, 902200000,
                                               'Wi-SUN FAN, BZ 902-928 MHz, Mode1b (2FSK 50kbps mi=1.0), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_2FSK_2a_BZ_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 19, 1, 200000, 902200000,
                                               'Wi-SUN FAN, BZ 902-928 MHz, Mode2a (2FSK 100kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 2

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_2FSK_3_BZ_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 21, 2, 400000, 902400000,
                                               'Wi-SUN FAN, BZ 902-928 MHz, Mode3 (2FSK 150kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_2FSK_4a_BZ_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 22, 2, 400000, 902400000,
                                               'Wi-SUN FAN, BZ 902-928 MHz, Mode4a (2FSK 200kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 3

    def PHY_WISUN_FAN_1v1_915MHz_Plan3_2FSK_5_BZ_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 24, 3, 600000, 902600000,
                                               'Wi-SUN FAN, BZ 902-928 MHz, Mode5 (2FSK 300kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### JP Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 21

    def PHY_WISUN_FAN_1v1_920MHz_Plan21_2FSK_1b_JP_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 18, 21, 200000, 920600000,
                                               'Wi-SUN FAN, JP 920-928 MHz, Mode1b (2FSK 50kbps mi=1.0), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 22

    def PHY_WISUN_FAN_1v1_920MHz_Plan22_2FSK_2b_JP_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 20, 22, 400000, 920900000,
                                               'Wi-SUN FAN, JP 920-928 MHz, Mode2b (2FSK 100kbps mi=1.0), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy


    def PHY_WISUN_FAN_1v1_920MHz_Plan22_2FSK_3_JP_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 21, 22, 400000, 920900000,
                                               'Wi-SUN FAN, JP 920-928 MHz, Mode3 (2FSK 150kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 23

    def PHY_WISUN_FAN_1v1_920MHz_Plan23_2FSK_4b_JP_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 23, 23, 600000, 920800000,
                                               'Wi-SUN FAN, JP 920-928 MHz, Mode4b (2FSK 200kbps mi=1.0), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_920MHz_Plan23_2FSK_5_JP_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 24, 23, 600000, 920800000,
                                               'Wi-SUN FAN, JP 920-928 MHz, Mode5 (2FSK 300kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy


    ### IN Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 39
    def PHY_WISUN_FAN_1v1_866MHz_Plan39_2FSK_1a_IN_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('IN', 17, 39, 100000, 865100000, 'Wi-SUN FAN, IN 865-867 MHz, Mode1a (2FSK 50kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 40
    def PHY_WISUN_FAN_1v1_866MHz_Plan40_2FSK_2a_IN_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('IN', 19, 40, 200000, 865100000, 'Wi-SUN FAN, IN 865-867 MHz, Mode2a (2FSK 100kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_866MHz_Plan40_2FSK_3_IN_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('IN', 21, 40, 200000, 865100000, 'Wi-SUN FAN, IN 865-867 MHz, Mode3 (2FSK 150kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy


    ### SG Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 38
    def PHY_WISUN_FAN_1v1_867MHz_Plan38_2FSK_4a_SG_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('SG', 22, 38, 400000, 866300000, 'Wi-SUN FAN, SG 865-867 MHz, Mode4a (2FSK 200kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_867MHz_Plan38_2FSK_5_SG_FEC(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('SG', 24, 38, 400000, 866300000, 'Wi-SUN FAN, SG 865-867 MHz, Mode5 (2FSK 300kbps mi=0.5), FEC')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy
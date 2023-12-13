from pyradioconfig.calculator_model_framework.interfaces.iphy import IPhy


class WisunFan1v1ChannelParamsJumbo():

    def __init__(self, wisun_reg_domain, wisun_phy_mode_id_select, wisun_channnel_plan_id, channel_spacing_hz, base_frequency_hz, readable_name):
        self.wisun_reg_domain = wisun_reg_domain
        self.wisun_phy_mode_id_select = wisun_phy_mode_id_select
        self.wisun_channnel_plan_id = wisun_channnel_plan_id
        self.channel_spacing_hz = channel_spacing_hz
        self.base_frequency_hz = base_frequency_hz
        self.readable_name = readable_name

class PhysStudioWisunFan1v1Jumbo(IPhy):

    # Helper method to fill out all of the PHY contents
    def _make_wisun_fan_phy(self, model, wisun_fan_channel_params, phy_name=None):
        phy = self._makePhy(model, model.profiles.wisun_fan_1_1,
                            readable_name=wisun_fan_channel_params.readable_name,
                            phy_name=phy_name)

        # Wi-SUN Inputs
        phy.profile_inputs.wisun_phy_mode_id_select.value = model.vars.wisun_phy_mode_id_select.var_enum(
            wisun_fan_channel_params.wisun_phy_mode_id_select)
        phy.profile_inputs.wisun_reg_domain.value = getattr(model.vars.wisun_reg_domain.var_enum, wisun_fan_channel_params.wisun_reg_domain)
        phy.profile_inputs.wisun_channel_plan_id.value = model.vars.wisun_channel_plan_id.var_enum(
            wisun_fan_channel_params.wisun_channnel_plan_id)

        # Default xtal frequency of 38.4MHz
        self._set_xtal_frequency(model, phy)

        # Temporary redundant inputs for base frequency and channel spacing (required due to Studio UI limitations)
        phy.profile_inputs.base_frequency_hz.value = wisun_fan_channel_params.base_frequency_hz
        phy.profile_inputs.channel_spacing_hz.value = wisun_fan_channel_params.channel_spacing_hz

        return phy

    def _set_xtal_frequency(self, model, phy):
        phy.profile_inputs.xtal_frequency_hz.value = 38400000

    ### EU Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 32

    def PHY_WISUN_FAN_1v1_863MHz_Plan32_2FSK_1a_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 1, 32, 100000, 863100000, 'Wi-SUN FAN, EU 863-870 MHz, Mode1a (2FSK 50kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 33

    def PHY_WISUN_FAN_1v1_863MHz_Plan33_2FSK_2a_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 3, 33, 200000, 863100000, 'Wi-SUN FAN, EU 863-870 MHz, Mode2a (2FSK 100kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_863MHz_Plan33_2FSK_3_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 5, 33, 200000, 863100000, 'Wi-SUN FAN, EU 863-870 MHz, Mode3 (2FSK 150kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 34

    def PHY_WISUN_FAN_1v1_870MHz_Plan34_2FSK_1a_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 1, 34, 100000, 870100000, 'Wi-SUN FAN, EU 870-876 MHz, Mode1a (2FSK 50kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 35

    def PHY_WISUN_FAN_1v1_870MHz_Plan35_2FSK_2a_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 3, 35, 200000, 870200000, 'Wi-SUN FAN, EU 870-876 MHz, Mode2a (2FSK 100kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_870MHz_Plan35_2FSK_3_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 5, 35, 200000, 870200000, 'Wi-SUN FAN, EU 870-876 MHz, Mode3 (2FSK 150kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 36

    def PHY_WISUN_FAN_1v1_863MHz_Plan36_2FSK_1a_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 1, 36, 100000, 863100000, 'Wi-SUN FAN, EU 863-876 MHz, Mode1a (2FSK 50kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 37

    def PHY_WISUN_FAN_1v1_863MHz_Plan37_2FSK_2a_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 3, 37, 200000, 863100000, 'Wi-SUN FAN, EU 863-876 MHz, Mode2a (2FSK 100kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_863MHz_Plan37_2FSK_3_EU(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('EU', 5, 37, 200000, 863100000, 'Wi-SUN FAN, EU 863-876 MHz, Mode3 (2FSK 150kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### NA Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 1

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_2FSK_1b_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 2, 1, 200000, 902200000, 'Wi-SUN FAN, NA 902-928 MHz, Mode1b (2FSK 50kbps mi=1.0)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_2FSK_2a_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 3, 1, 200000, 902200000, 'Wi-SUN FAN, NA 902-928 MHz, Mode2a (2FSK 100kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 2

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_2FSK_3_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 5, 2, 400000, 902400000, 'Wi-SUN FAN, NA 902-928 MHz, Mode3 (2FSK 150kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_2FSK_4a_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 6, 2, 400000, 902400000, 'Wi-SUN FAN, NA 902-928 MHz, Mode4a (2FSK 200kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 3

    def PHY_WISUN_FAN_1v1_915MHz_Plan3_2FSK_5_NA(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('NA', 8, 3, 600000, 902600000, 'Wi-SUN FAN, NA 902-928 MHz, Mode5 (2FSK 300kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### BZ Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 1

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_2FSK_1b_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 2, 1, 200000, 902200000, 'Wi-SUN FAN, BZ 902-928 MHz, Mode1b (2FSK 50kbps mi=1.0)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_915MHz_Plan1_2FSK_2a_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 3, 1, 200000, 902200000, 'Wi-SUN FAN, BZ 902-928 MHz, Mode2a (2FSK 100kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 2

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_2FSK_3_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 5, 2, 400000, 902400000, 'Wi-SUN FAN, BZ 902-928 MHz, Mode3 (2FSK 150kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_915MHz_Plan2_2FSK_4a_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 6, 2, 400000, 902400000, 'Wi-SUN FAN, BZ 902-928 MHz, Mode4a (2FSK 200kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 3

    def PHY_WISUN_FAN_1v1_915MHz_Plan3_2FSK_5_BZ(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('BZ', 8, 3, 600000, 902600000, 'Wi-SUN FAN, BZ 902-928 MHz, Mode5 (2FSK 300kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    ### JP Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 21

    def PHY_WISUN_FAN_1v1_920MHz_Plan21_2FSK_1b_JP(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 2, 21, 200000, 920600000, 'Wi-SUN FAN, JP 920-928 MHz, Mode1b (2FSK 50kbps mi=1.0)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 22

    def PHY_WISUN_FAN_1v1_920MHz_Plan22_2FSK_2b_JP(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 4, 22, 400000, 920900000, 'Wi-SUN FAN, JP 920-928 MHz, Mode2b (2FSK 100kbps mi=1.0)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_920MHz_Plan22_2FSK_3_JP(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 5, 22, 400000, 920900000, 'Wi-SUN FAN, JP 920-928 MHz, Mode3 (2FSK 150kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 23

    def PHY_WISUN_FAN_1v1_920MHz_Plan23_2FSK_4b_JP(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 7, 23, 600000, 920800000, 'Wi-SUN FAN, JP 920-928 MHz, Mode4b (2FSK 200kbps mi=1.0)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_920MHz_Plan23_2FSK_5_JP(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('JP', 8, 23, 600000, 920800000, 'Wi-SUN FAN, JP 920-928 MHz, Mode5 (2FSK 300kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy


    ### IN Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 39
    def PHY_WISUN_FAN_1v1_866MHz_Plan39_2FSK_1a_IN(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('IN', 1, 39, 100000, 865100000, 'Wi-SUN FAN, IN 865-867 MHz, Mode1a (2FSK 50kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    # ChanPlanID 40
    def PHY_WISUN_FAN_1v1_866MHz_Plan40_2FSK_2a_IN(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('IN', 3, 40, 200000, 865100000, 'Wi-SUN FAN, IN 865-867 MHz, Mode2a (2FSK 100kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_866MHz_Plan40_2FSK_3_IN(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('IN', 5, 40, 200000, 865100000, 'Wi-SUN FAN, IN 865-867 MHz, Mode3 (2FSK 150kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy


    ### SG Region PHYs From Wi-SUN FAN 1.1 Spec###

    # ChanPlanID 38
    def PHY_WISUN_FAN_1v1_867MHz_Plan38_2FSK_4a_SG(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('SG', 6, 38, 400000, 866300000, 'Wi-SUN FAN, SG 865-867 MHz, Mode4a (2FSK 200kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy

    def PHY_WISUN_FAN_1v1_867MHz_Plan38_2FSK_5_SG(self, model, phy_name=None):
        params = WisunFan1v1ChannelParamsJumbo('SG', 8, 38, 400000, 866300000, 'Wi-SUN FAN, SG 865-867 MHz, Mode5 (2FSK 300kbps mi=0.5)')
        phy = self._make_wisun_fan_phy(model, params, phy_name=phy_name)
        return phy
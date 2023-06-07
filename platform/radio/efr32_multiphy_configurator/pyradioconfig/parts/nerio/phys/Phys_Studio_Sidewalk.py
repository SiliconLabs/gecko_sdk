from pyradioconfig.calculator_model_framework.interfaces.iphy import IPhy

# Though this file/class is named "Studio", we actually only expose for later parts at this time
class PhysStudioSidewalkNerio(IPhy):

    def PHY_Sidewalk_2GFSK_50Kbps(self, model):
        phy = self._makePhy(model, model.profiles.sidewalk, readable_name='Sidewalk 50kbps 2GFSK mi=1.0')

        # Sidewalk inputs
        phy.profile_inputs.sidewalk_mode.value = model.vars.sidewalk_mode.var_enum.FSK_50kbps
        phy.profile_inputs.preamble_length.value = 8 * 8  # Use 64-bit preamble for TX by default
        phy.profile_inputs.shaping_filter.value = model.vars.shaping_filter.var_enum.Gaussian
        phy.profile_inputs.shaping_filter_param.value = 1.0

        # Base freq and channel spacing
        phy.profile_inputs.base_frequency_hz.value = 902200000
        phy.profile_inputs.channel_spacing_hz.value = 200000

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

    ### Sidewalk 150kbps and 250kbps currently not in spec ###

    '''
    def PHY_Sidewalk_2GFSK_150Kbps(self, model):
        phy = self._makePhy(model, model.profiles.sidewalk, readable_name='Sidewalk 150kbps 2GFSK mi=0.5')

        # Sidewalk inputs
        phy.profile_inputs.sidewalk_mode.value = model.vars.sidewalk_mode.var_enum.FSK_150kbps
        phy.profile_inputs.preamble_length.value = 8 * 8  # Use 64-bit preamble for TX by default
        phy.profile_inputs.shaping_filter.value = model.vars.shaping_filter.var_enum.Gaussian
        phy.profile_inputs.shaping_filter_param.value = 0.5

        # Base freq and channel spacing
        phy.profile_inputs.base_frequency_hz.value = 902200000
        phy.profile_inputs.channel_spacing_hz.value = 406349

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

    def PHY_Sidewalk_2GFSK_250Kbps(self, model):
        phy = self._makePhy(model, model.profiles.sidewalk, readable_name='Sidewalk 250kbps 2GFSK mi=0.5')

        # Sidewalk inputs
        phy.profile_inputs.sidewalk_mode.value = model.vars.sidewalk_mode.var_enum.FSK_250kbps
        phy.profile_inputs.preamble_length.value = 8 * 8  # Use 64-bit preamble for TX by default
        phy.profile_inputs.shaping_filter.value = model.vars.shaping_filter.var_enum.Gaussian
        phy.profile_inputs.shaping_filter_param.value = 0.5

        # Base freq and channel spacing
        phy.profile_inputs.base_frequency_hz.value = 902200000
        phy.profile_inputs.channel_spacing_hz.value = 512000

        # Default xtal frequency of 39MHz
        phy.profile_inputs.xtal_frequency_hz.value = 39000000
    '''
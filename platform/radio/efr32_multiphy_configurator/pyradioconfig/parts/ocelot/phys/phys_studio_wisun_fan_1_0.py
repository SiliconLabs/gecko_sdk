from pyradioconfig.calculator_model_framework.decorators.phy_decorators import do_not_inherit_phys
from pyradioconfig.parts.jumbo.phys.phys_studio_wisun_fan_1_0 import PhysStudioWisunFanJumbo


class PhysStudioWisunFanOcelot(PhysStudioWisunFanJumbo):

    def _set_xtal_frequency(self, model, phy):
        phy.profile_inputs.xtal_frequency_hz.value = 39000000
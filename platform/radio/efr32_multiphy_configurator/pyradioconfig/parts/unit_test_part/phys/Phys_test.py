from pyradioconfig.calculator_model_framework.decorators.phy_decorators import phy_guid
from pyradioconfig.calculator_model_framework.interfaces.iphy import IPhy

from py_2_and_3_compatibility import *

class PHYS_test(IPhy):
    """
    Init internal variables
    """
    def __init__(self):
        self._phy_name = "Test Phys"
        self._major = 1
        self._minor = 0
        self._patch = 0


    def PHY_Test_868M_38p4kbps(self, model):

        phy = self._makePhy(model, model.profiles.Base, 'PHY Test 868M 38p4kbps', tags="#unittest #example_tag")

        phy.profile_inputs.shaping_filter.values = model.vars.shaping_filter.var_enum.NONE

        phy.profile_inputs.base_frequency_hz.values = long(868300000)

    @phy_guid('abcd-efgh-0123-4567')
    def PHY_Test_868M_38p4kbps_long_preamble(self, modem_model):

        phy = self._makePhy(modem_model, modem_model.profiles.Base, 'PHY Test 868M 38p4kbps long preamble')

        phy.profile_inputs.shaping_filter.values = 1

        phy.profile_inputs.base_frequency_hz.values = long(868000003)

        phy.profile_inputs.preamble_pattern.values = 1







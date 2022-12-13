from pyradioconfig.parts.ocelot.calculators.calc_global import CALC_Global_ocelot
from pycalcmodel.core.variable import ModelVariableFormat

class CALC_Global_Margay(CALC_Global_ocelot):

    def buildVariables(self, model):

        # Build variables from the Lynx calculations
        super().buildVariables(model)

        self._addModelRegister(model, 'MODEM.LOG2X4.LOG2X4', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.LOG2X4.LOG2X4FWSEL', int, ModelVariableFormat.HEX)

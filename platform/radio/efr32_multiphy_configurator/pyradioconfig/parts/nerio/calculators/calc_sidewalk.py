from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum

class CalcSidewalkNerio(ICalculator):

    def buildVariables(self, model):
        var = self._addModelVariable(model, 'sidewalk_mode', Enum, ModelVariableFormat.DECIMAL,
                                     'Sidewalk Mode')
        member_data = [
            ['FSK_50kbps', 0, '2FSK 50kbps mi=1.0'],
        ]
        var.var_enum = CreateModelVariableEnum(
            'SidewalkModeEnum',
            'List of supported Sidewalk Modes',
            member_data)

        # Note that 150kbps and 250kbps modes are not published in the Sidewalk spec
        # Below are the definitions in case we want to add them in the future
        # ['FSK_150kbps', 1, '2FSK 150kbps mi=0.5']
        # ['FSK_250kbps', 2, '2FSK 250kbps mi=0.5']
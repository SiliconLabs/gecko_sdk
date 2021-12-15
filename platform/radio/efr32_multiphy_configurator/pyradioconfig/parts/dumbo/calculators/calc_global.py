from pyradioconfig.parts.common.calculators.calc_global import CALC_Global
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum

class CALC_Global_dumbo(CALC_Global):

    def buildVariables(self, model):

        #Build variables from the global calculations
        super().buildVariables(model)

        #Add a chip identifier
        self._addModelVariable(model, 'family',                           str,   ModelVariableFormat.ASCII)
	
    def calc_family_name(self, model):
        model.vars.family.value = "dumbo"
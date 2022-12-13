from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum

class CALC_FEC_Lynx(ICalculator):

    def buildVariables(self, model):
        pass

    def calc_convramaddr_reg(self, model):

        #Value is static per part
        conv_ram_addr = 0x0000 >> 2

        self._reg_write(model.vars.FRC_CONVRAMADDR_CONVRAMADDR, conv_ram_addr)
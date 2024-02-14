from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum
from pyradioconfig.parts.common.calculators.calc_fec import CALC_FEC

class CALC_FEC_Panther(CALC_FEC):

    def calc_convramaddr_reg(self, model):

        #Value is static per part
        conv_ram_addr = 0x0000 >> 2

        self._reg_write(model.vars.FRC_CONVRAMADDR_CONVRAMADDR, conv_ram_addr)
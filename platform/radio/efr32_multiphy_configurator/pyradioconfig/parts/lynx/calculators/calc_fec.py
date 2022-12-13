from pyradioconfig.parts.common.calculators.calc_fec import CALC_FEC
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum

class CALC_FEC_Lynx(CALC_FEC):

    def calc_convramaddr_reg(self, model):

        #Value is static per part
        conv_ram_addr = 0x4000 >> 2

        self._reg_write(model.vars.FRC_CONVRAMADDR_CONVRAMADDR, conv_ram_addr)
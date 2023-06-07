from pyradioconfig.parts.lynx.calculators.calc_crc import CALC_CRC as CALC_CRC_lynx
from enum import Enum
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum

class CALC_CRC_ocelot(CALC_CRC_lynx):

    def buildVariables(self, model):
        super().buildVariables(model)

        # 802154 FCS Type
        self._addModelVariable(model, 'fcs_type_802154', Enum, ModelVariableFormat.DECIMAL,
                               desc='FCS type for 802154 PHYs')
        model.vars.fcs_type_802154.var_enum = CreateModelVariableEnum(
            enum_name='FcsTypeEnum',
            enum_desc='802154 FCS Type',
            member_data=[
                ['TWO_BYTE', 1, '16-bit ITU-T CRC'],
                ['FOUR_BYTE', 0, '32-bit ANSI X3.66-1979 CRC'],
            ])
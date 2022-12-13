from pyradioconfig.parts.jumbo.calculators.calc_wisun import CALC_WiSUN_Jumbo
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum

class CALC_WiSUN_Ocelot(CALC_WiSUN_Jumbo):

    def buildVariables(self, model):

        #Call the inherited version
        super().buildVariables(model)

        self._addModelVariable(model, 'bch_lut_data', int, ModelVariableFormat.DECIMAL,
                               desc='BCH lookup table for error correction', is_array=True)

    def calc_bch_lut_data(self, model):

        protocol_id = model.vars.protocol_id.value
        modulation_type = model.vars.modulation_type.value

        # See https://jira.silabs.com/browse/MCUW_RADIO_CFG-1859
        # This calculation only applies to Wi-SUN FSK (FAN/HAN)
        if protocol_id == model.vars.protocol_id.var_enum.WiSUN and \
                modulation_type == model.vars.modulation_type.var_enum.FSK2:
            bch_lut_data = [
                0b000000000000000,
                0b000100000000000,
                0b001000000000000,
                0b000000100000000,
                0b010000000000000,
                0b000000000100000,
                0b000001000000000,
                0b000000000001000,
                0b100000000000000,
                0b000000000000001,
                0b000000001000000,
                0b000000000000010,
                0b000010000000000,
                0b000000010000000,
                0b000000000010000,
                0b000000000000100
            ]

            #Write the model var
            model.vars.bch_lut_data.value = bch_lut_data
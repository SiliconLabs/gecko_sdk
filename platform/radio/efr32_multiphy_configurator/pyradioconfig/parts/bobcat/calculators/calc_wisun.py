from pyradioconfig.parts.ocelot.calculators.calc_wisun import CALC_WiSUN_Ocelot
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum

class CALC_WiSUN_Bobcat(CALC_WiSUN_Ocelot):

    def buildVariables(self, model):
        super().buildVariables(model)
        model.vars.wisun_reg_domain.var_enum = CreateModelVariableEnum(
            enum_name='WiSUNRegDomainEnum',
            enum_desc='List of supported WiSUN Regulatory Domains',
            member_data=[
                ['WW', 0x10, 'Worldwide'],
            ])
    pass
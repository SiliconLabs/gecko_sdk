from pyradioconfig.parts.ocelot.calculators.calc_global import CALC_Global_ocelot


class CALC_Global_Margay(CALC_Global_ocelot):

    def calc_family_name(self, model):
        model.vars.family.value = "margay"

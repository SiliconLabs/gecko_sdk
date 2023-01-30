from pyradioconfig.parts.ocelot.calculators.calc_ircal import CALC_IrCal_Ocelot

class Calc_IrCal_Sol(CALC_IrCal_Ocelot):

    def calc_ircal_murshf_muishf(self, model):

        #Hard coded for Sol
        model.vars.ircal_murshf.value = 28
        model.vars.ircal_muishf.value = 38
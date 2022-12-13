from pyradioconfig.parts.ocelot.calculators.calc_agc import CALC_AGC_ocelot


class CALC_AGC_Margay(CALC_AGC_ocelot):

    def calc_lnamixenrfpkdlothresh_reg(self, model):
        #This field is owned by RAIL for Margay
        pass
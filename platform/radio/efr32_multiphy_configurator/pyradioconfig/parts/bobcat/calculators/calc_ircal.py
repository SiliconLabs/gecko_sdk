from pyradioconfig.parts.ocelot.calculators.calc_ircal import CALC_IrCal_Ocelot

class Calc_IrCal_Bobcat(CALC_IrCal_Ocelot):

    def calc_ircal_murshf_muishf(self, model):
        # if there is a 2.4Ghz PHY being built, it should use the same ircal coefficient
        # as all the 2.4GHz PHYs should get the coefficient from DEVINFO
        pass
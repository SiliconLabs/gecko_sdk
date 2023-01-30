from pyradioconfig.parts.ocelot.calculators.calc_ircal import CALC_IrCal_Ocelot


class CALC_IrCal_Margay(CALC_IrCal_Ocelot):

    def calc_ircal_murshf_muishf(self, model):
        base_frequency_hz = model.vars.base_frequency_hz.value

        # Calculated based on band
        if base_frequency_hz > 400e6:
            #Use the same coefficients as for Sol
            ircal_murshf = 28
            ircal_muishf = 38
        else:
            # Use the same coefficients as for Ocelot
            ircal_murshf = 24
            ircal_muishf = 34

        model.vars.ircal_murshf.value = ircal_murshf
        model.vars.ircal_muishf.value = ircal_muishf
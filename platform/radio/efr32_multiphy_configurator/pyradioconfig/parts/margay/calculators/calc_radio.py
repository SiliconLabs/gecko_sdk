from pyradioconfig.parts.ocelot.calculators.calc_radio import CALC_Radio_ocelot


class CALC_Radio_Margay(CALC_Radio_ocelot):

    def calc_lnamix_reg(self, model):
        super().calc_lnamix_reg(model)

        rf_band = model.vars.rf_band.value

        if rf_band == model.vars.rf_band.var_enum.BAND_2400:
            lnamixmxrbias = 3
        else:
            lnamixmxrbias = 2

        self._reg_write(model.vars.RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1, lnamixmxrbias) #For RF-1 path only, but RC doesn't know
        self._reg_write(model.vars.RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0, lnamixmxrbias) #For RF-0 path only, but RC doesn't know

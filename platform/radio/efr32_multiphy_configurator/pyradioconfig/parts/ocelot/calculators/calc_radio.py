from pyradioconfig.parts.lynx.calculators.calc_radio import CALC_Radio_lynx

#This file contains calculations related to the configuring the analog front end

class CALC_Radio_ocelot(CALC_Radio_lynx):

    def calc_lpfbwrx(self, model):
        pass

    def calc_lpfbwtx(self, model):
        pass

    def calc_lpfbwtx_reg(self, model):
        self._reg_write(model.vars.SYNTH_LPFCTRL2RX_VCMLVLRX, 0)

    def calc_lpfbwrx_reg(self, model):
        pass

    def calc_reg_vcodetamplitude(self, model):
        pass

    def calc_if_frequency_hz_value(self,model):
        #The IF frequency calculation is now in the calc_synth file for Ocelot
        pass

    def calc_txtrimdregbleed_reg(self, model):
        #This method calculates the value of RAC_PATRIM3_TXTRIMDREGBLEED

        base_frequency_hz = model.vars.base_frequency_hz.value
        modulation_type = model.vars.modulation_type.value

        if modulation_type == model.vars.modulation_type.var_enum.OOK:
            bleed = 2
        else:
            if base_frequency_hz > 450e6:
                bleed = 1
            else:
                bleed = 2

        self._reg_write(model.vars.RAC_PATRIM3_TXTRIMDREGBLEED, bleed)

    def calc_lnamix_reg(self, model):

        rf_band = model.vars.rf_band.value

        #Calculate RFPKDTHRESHSEL based on band
        if rf_band == model.vars.rf_band.var_enum.BAND_2400:
            lnamixrfpkdthreshsello = 1
            lnamixrfpkdthreshselhi = 3
        else:
            lnamixrfpkdthreshsello = 2
            lnamixrfpkdthreshselhi = 4

        self._reg_write(model.vars.RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO, lnamixrfpkdthreshsello)
        self._reg_write(model.vars.RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI, lnamixrfpkdthreshselhi)

        #Set the following to defaults
        self._reg_write_default(model.vars.RAC_RX_LNAMIXLDOLOWCUR)
        self._reg_write_default(model.vars.RAC_LNAMIXTRIM0_LNAMIXLNA0CAPSEL)
        self._reg_write_default(model.vars.RAC_LNAMIXTRIM1_LNAMIXLNA1CAPSEL)

        #Set statically
        self._reg_write(model.vars.RAC_PGACTRL_PGATHRPKDLOSEL, 1)
        self._reg_write(model.vars.RAC_PGACTRL_PGATHRPKDHISEL, 5)






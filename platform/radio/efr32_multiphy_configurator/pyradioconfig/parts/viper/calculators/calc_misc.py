from pyradioconfig.parts.bobcat.calculators.calc_misc import Calc_Misc_Bobcat

class calc_misc_viper(Calc_Misc_Bobcat):
    def calc_misc_Bobcat(self, model):
        pass

    def calc_misc_Viper(self, model):
        """
        These aren't really calculating right now.  Just using defaults or forced values.
       fefilt_selected = model.vars.fefilt_selected.value
        Args:
             model (ModelRoot) : Data model to read and write variables from
        """

        self._reg_write(model.vars.MODEM_TXCORR_TXDGAIN6DB, 0)
        self._reg_write(model.vars.MODEM_TXCORR_TXDGAIN, 2)
        self._reg_write(model.vars.MODEM_TXCORR_TXGAINIMB, 0)
        self._reg_write(model.vars.MODEM_TXCORR_TXPHSIMB, 0)
        self._reg_write(model.vars.MODEM_TXCORR_TXFREQCORR, 0)

        self._reg_write(model.vars.MODEM_TXMISC_FORCECLKEN, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXIQIMBEN, 1)
        self._reg_write(model.vars.MODEM_TXMISC_TXINTPEN, 1)
        self._reg_write(model.vars.MODEM_TXMISC_TXDSEN, 1)
        self._reg_write(model.vars.MODEM_TXMISC_TXIQSWAP, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXDACFORMAT, 1)
        self._reg_write(model.vars.MODEM_TXMISC_TXDACFORCE, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXDCI, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXDCQ, 0)
  #      self._reg_write(model.vars.MODEM_TXMISC_BR2M, 1)

        self._reg_write(model.vars.MODEM_EHDSSSCTRL_EHDSSSEN, 0)
        self._reg_write(model.vars.MODEM_EHDSSSCTRL_DSSSTIMEACQUTHD,0)
        self._reg_write(model.vars.MODEM_EHDSSSCTRL_FOEBIAS,0)
        self._reg_write(model.vars.MODEM_EHDSSSCTRL_FREQCORREN,0)
        self._reg_write(model.vars.MODEM_EHDSSSCTRL_DSSSFRQLIM,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG0_DSSSPATT,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG1_DSSSEXPSYNCLEN,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG1_DSSSCORRTHD,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG1_DSSSDSAQTHD,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_DSSSTIMCORRTHD,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_DSSSFRTCORRTHD,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_DSSSTRACKINGWIN,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_DSSSCORRSCHWIN,0)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_ONESYMBOLMBDD,0)

    # FIXME: amtudave: Remove SYNCERRORS from viper once tri sync word logic is working

    def calc_sync2_reg(self, model):
        self._reg_write(model.vars.MODEM_SYNC2_SYNC2, 0)


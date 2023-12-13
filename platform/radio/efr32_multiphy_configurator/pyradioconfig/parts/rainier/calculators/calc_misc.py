from pyradioconfig.parts.bobcat.calculators.calc_misc import Calc_Misc_Bobcat


class CalcMiscRainier(Calc_Misc_Bobcat):

    def calc_misc(self, model):
        """
        These aren't really calculating right now.  Just using defaults or forced values.
       fefilt_selected = model.vars.fefilt_selected.value
        Args:
             model (ModelRoot) : Data model to read and write variables from
        """
        super().calc_misc(model)

        self._reg_write_default(model.vars.RAC_ADCTRIM0_ADCSIDETONEAMP)
        self._reg_write(model.vars.RAC_ADCEN0_ADCENNEGRES, 1)
        self._reg_write(model.vars.RAC_LNAMIXCTRL1_LNAMIXRFPKDTHRESHSELHI, 3)
        self._reg_write(model.vars.RAC_LNAMIXCTRL1_LNAMIXRFPKDTHRESHSELLO, 1)
        self._reg_write(model.vars.RAC_TIAEN_TIAENLATCHI, 1)
        self._reg_write(model.vars.RAC_TIAEN_TIAENLATCHQ, 1)
        self._reg_write(model.vars.RAC_TIACTRL0_TIATHRPKDHISEL, 5)
        self._reg_write(model.vars.RAC_TIACTRL0_TIATHRPKDLOSEL, 1)

        self._reg_write(model.vars.MODEM_TXCORR_TXDGAIN6DB, 0)
        self._reg_write(model.vars.MODEM_TXCORR_TXDGAIN, 2)
        self._reg_write(model.vars.MODEM_TXCORR_TXGAINIMB, 0)
        self._reg_write(model.vars.MODEM_TXCORR_TXPHSIMB, 0)

        self._reg_write(model.vars.MODEM_TXMISC_FORCECLKEN, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXIQIMBEN, 1)
        self._reg_write(model.vars.MODEM_TXMISC_TXINTPEN, 1)
        self._reg_write(model.vars.MODEM_TXMISC_TXDSEN, 1)
        self._reg_write(model.vars.MODEM_TXMISC_TXIQSWAP, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXDACFORMAT, 1)
        self._reg_write(model.vars.MODEM_TXMISC_TXDCI, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXDCQ, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXDOFORCEI, 0)
        self._reg_write(model.vars.MODEM_TXMISC_TXDOFORCEQ, 0)
        #      self._reg_write(model.vars.MODEM_TXMISC_BR2M, 1)

        self._reg_write(model.vars.SYNTH_DLFCTRL_LOCKLPFBWGEAR0, 15)
        self._reg_write(model.vars.SYNTH_DLFCTRL_LOCKLPFBWGEAR1, 15)

        self._reg_write(model.vars.MODEM_EHDSSSCTRL_EHDSSSEN, 0)
        self._reg_write(model.vars.MODEM_EHDSSSCTRL_DSSSTIMEACQUTHD, 16)
        self._reg_write(model.vars.MODEM_EHDSSSCTRL_FOEBIAS, 1)
        self._reg_write(model.vars.MODEM_EHDSSSCTRL_FREQCORREN, 1)
        self._reg_write(model.vars.MODEM_EHDSSSCTRL_DSSSFRQLIM, 16)
        self._reg_write(model.vars.MODEM_EHDSSSCFG0_DSSSPATT, 122)
        self._reg_write(model.vars.MODEM_EHDSSSCFG1_DSSSEXPSYNCLEN, 128)
        self._reg_write(model.vars.MODEM_EHDSSSCFG1_DSSSCORRTHD, 400)
        self._reg_write(model.vars.MODEM_EHDSSSCFG1_DSSSDSAQTHD, 700)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_DSSSTIMCORRTHD, 600)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_DSSSFRTCORRTHD, 700)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_DSSSTRACKINGWIN, 5)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_DSSSCORRSCHWIN, 8)
        self._reg_write(model.vars.MODEM_EHDSSSCFG2_ONESYMBOLMBDD, 1)

        self._reg_write(model.vars.MODEM_TRECSCFG_SOFTD, 0)
        self._reg_write(model.vars.MODEM_TRECSCFG_SDSCALE, 3)

        # : TODO FIX ME! Following register values are not being calculated.
        self._reg_write_default(model.vars.SYNTH_DSMCTRLTX_DITHERDACTX)
        self._reg_write_default(model.vars.SYNTH_DSMCTRLRX_DITHERDACRX)
        self._reg_write_default(model.vars.SYNTH_DLFCTRLTX_TXLOCKLPFBWGEAR4)
        self._reg_write_default(model.vars.SYNTH_DSMCTRLRX_REQORDERRX)
        self._reg_write_default(model.vars.SYNTH_DSMCTRLTX_PHISELTX)
        self._reg_write_default(model.vars.SYNTH_DSMCTRLTX_REQORDERTX)
        self._reg_write_default(model.vars.SYNTH_QNCCTRL_QNCMODE)
        self._reg_write_default(model.vars.SYNTH_QNCCTRL_QNCOFFSET)
        self._reg_write_default(model.vars.SYNTH_HOPPING_HCAPRETIMEEN)
        self._reg_write_default(model.vars.SYNTH_LMSOVERRIDE_GLMSOVERRIDEEN)
        self._reg_write_default(model.vars.SYNTH_LMSOVERRIDE_GLMSOVERRIDEVAL)
        self._reg_write_default(model.vars.SYNTH_LMSOVERRIDE_PLMSOVERRIDEEN)
        self._reg_write_default(model.vars.SYNTH_LMSOVERRIDE_PLMSOVERRIDEVAL)
        self._reg_write_default(model.vars.MODEM_TXFREQCORR_TXFREQCORR)
        self._reg_write_default(model.vars.MODEM_TXDACVAL_TXFORCEDI)
        self._reg_write_default(model.vars.MODEM_TXDACVAL_TXFORCEDQ)
        self._reg_write_default(model.vars.MODEM_TXDACVAL_TXIDLEI)
        self._reg_write_default(model.vars.MODEM_TXDACVAL_TXIDLEQ)
        self._reg_write_default(model.vars.MODEM_EXPECTPATTDUAL_EXPECTPATTDUAL)
        self._reg_write_default(model.vars.MODEM_COCURRMODE_DSSSCONCURRENT)
        self._reg_write_default(model.vars.MODEM_EHDSSSCTRL_DSSSDSATHD)
        self._reg_write_default(model.vars.MODEM_EHDSSSCTRL_DUALDSA)
        self._reg_write_default(model.vars.MODEM_EHDSSSCFG2_MAXSCHMODE)
        self._reg_write_default(model.vars.MODEM_EHDSSSCFG2_DSSSDSAQUALEN)
        self._reg_write_default(model.vars.MODEM_EHDSSSCFG3_DSSSDASMAXTHD)
        self._reg_write_default(model.vars.MODEM_EHDSSSCFG3_DSSSFOETRACKGEAR)
        self._reg_write_default(model.vars.MODEM_EHDSSSCFG3_OPMODE)
        self._reg_write_default(model.vars.MODEM_EHDSSSCFG3_DSSSINITIMLEN)
        self._reg_write_default(model.vars.MODEM_DUALTIM_DUALTIMEN)
        self._reg_write_default(model.vars.MODEM_DUALTIM_MINCOSTTHD2)
        self._reg_write_default(model.vars.MODEM_DUALTIM_SYNCACQWIN2)
        self._reg_write_default(model.vars.MODEM_PHDMODCTRL_CHPWRQUAL)
        self._reg_write_default(model.vars.MODEM_CTRL3_ANTDIVMODE)
        self._reg_write_default(model.vars.MODEM_DIGMIXCTRL_BLEORZB)
        self._reg_write_default(model.vars.MODEM_DIGMIXCTRL_MULTIPHYHOP)
        self._reg_write_default(model.vars.MODEM_DIGMIXCTRL_HOPPINGSRC)
        self._reg_write_default(model.vars.MODEM_DIGMIXCTRL_RXBRINTSHIFT)
        self._reg_write_default(model.vars.MODEM_DIGMIXCTRL_DSSSCFECOMBO)
        self._reg_write_default(model.vars.MODEM_SYNC3_SYNC3)
        self._reg_write_default(model.vars.MODEM_EHDSSSCTRL_DSSSPMTIMEOUT)
        self._reg_write_default(model.vars.MODEM_EHDSSSCTRL_DSSSFRMTIMEOUT)
        self._reg_write_default(model.vars.MODEM_COCURRMODE_DSSSDSACHK)
        self._reg_write_default(model.vars.MODEM_COCURRMODE_TRECSDSACHK)
        self._reg_write_default(model.vars.MODEM_COCURRMODE_CORRCHKMUTE)
        self._reg_write_default(model.vars.MODEM_SYNCWORDCTRL_SYNCBITS2TH)
        self._reg_write_default(model.vars.MODEM_SYNCWORDCTRL_SYNC3ERRORS)
        self._reg_write_default(model.vars.MODEM_SYNCWORDCTRL_DUALSYNC2TH)
        self._reg_write_default(model.vars.MODEM_SYNCWORDCTRL_SYNCSWFEC)
        self._reg_write_default(model.vars.MODEM_SICTRL1_SYMIDENTDIS)
        self._reg_write_default(model.vars.MODEM_SICTRL2_SISTARTDELAY)

    # FIXME: amtudave: Uncomment to remove SYNCERRORS from viper once tri sync word logic is working
    # def calc_syncerrors_reg(self, model):
    #     # MODEM_CTRL1_SYNCERRORS removed in viper, see MODEM_SYNCWORDCTRL_SYNC0ERRORS
    #     pass

    def calc_sync2_reg(self, model):
        self._reg_write(model.vars.MODEM_SYNC2_SYNC2, 0)

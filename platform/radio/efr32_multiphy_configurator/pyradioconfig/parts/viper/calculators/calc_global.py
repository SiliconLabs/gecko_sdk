from pyradioconfig.parts.bobcat.calculators.calc_global import Calc_Global_Bobcat
from pycalcmodel.core.variable import ModelVariableFormat
from py_2_and_3_compatibility import *

class Calc_Global_Viper(Calc_Global_Bobcat):
    def buildVariables(self, model):
            
        # Build variables from the Ocelot calculations
        super().buildVariables(model)

        self._addModelRegister(model, 'RAC.RX.SYPFDCHPLPENRX', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.TXCORR.TXDGAIN6DB', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXCORR.TXDGAIN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXCORR.TXGAINIMB', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXCORR.TXPHSIMB', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXCORR.TXFREQCORR', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.TXMISC.FORCECLKEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXIQIMBEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXINTPEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXDSEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXIQSWAP', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXDACFORMAT', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXDACFORCE', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXDCI', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXDCQ', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.BR2M', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.TXMISC.TXMOD', int, ModelVariableFormat.HEX)

        self._addModelVariable(model, 'br2m', int, ModelVariableFormat.DECIMAL)

        self._addModelActual(model, 'shaping_filter_gain_iqmod', float, ModelVariableFormat.DECIMAL)

        self._addModelVariable(model, 'syncword_trisync', bool, ModelVariableFormat.ASCII)
        self._addModelRegister(model, 'MODEM.SYNC2.SYNC2', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.SYNCWORDCTRL.SYNC0BITS', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SYNCWORDCTRL.SYNC1BITS', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SYNCWORDCTRL.SYNC2BITS', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SYNCWORDCTRL.SYNC0ERRORS', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SYNCWORDCTRL.SYNC1ERRORS', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SYNCWORDCTRL.SYNC2ERRORS', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SYNCWORDCTRL.DUALSYNC', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SYNCWORDCTRL.TRISYNC', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.EHDSSSCTRL.EHDSSSEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCTRL.DSSSTIMEACQUTHD', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCTRL.FOEBIAS', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCTRL.FREQCORREN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCTRL.DSSSFRQLIM', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG0.DSSSPATT', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG1.DSSSEXPSYNCLEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG1.DSSSCORRTHD', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG1.DSSSDSAQTHD', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG2.DSSSTIMCORRTHD', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG2.DSSSFRTCORRTHD', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG2.DSSSTRACKINGWIN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG2.DSSSCORRSCHWIN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.EHDSSSCFG2.ONESYMBOLMBDD', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.PHDMODCTRL.FASTHOPPINGEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.CMD.HOPPINGSTART', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.DIGMIXCTRL.FWHOPPING', int, ModelVariableFormat.HEX)

        #
        # self._addModelRegister(model, 'MODEM.CTRL1.TXSYNC', int, ModelVariableFormat.HEX)
        # self._addModelRegister(model, 'MODEM.CTRL1.SYNCDATA', int, ModelVariableFormat.HEX)
        # self._addModelRegister(model, 'MODEM.CTRL1.SYNC1INV', int, ModelVariableFormat.HEX)
        # self._addModelRegister(model, 'MODEM.CTRL1.COMPMODE', int, ModelVariableFormat.HEX)
        # self._addModelRegister(model, 'MODEM.CTRL1.RESYNCPER', int, ModelVariableFormat.HEX)
        # self._addModelRegister(model, 'MODEM.CTRL1.PHASEDEMOD', int, ModelVariableFormat.HEX)
        # self._addModelRegister(model, 'MODEM.CTRL1.FREQOFFESTPER', int, ModelVariableFormat.HEX)
        # self._addModelRegister(model, 'MODEM.CTRL1.FREQOFFESTLIM', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.SICTRL0.SIMODE', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL0.NDFOCAL', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL0.PEAKNUMTHRESHLW', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL0.FREQNOMINAL', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL0.SWPEAKNUMADJ', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL0.NOISETHRESH', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL0.NOISETHRESHADJ', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.SICTRL1.TWOSYMBEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL1.SMALLSAMPLETHRESH', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL1.SUPERCHIPTOLERANCE', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL1.FASTMODE', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL1.PEAKNUMP2ADJ', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL1.ZCEN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL1.ZCSAMPLETHRESH', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL1.SOFTCLIPBYPASS', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL1.SOFTCLIPTHRESH', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.SICTRL2.SIRSTAGCMODE', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL2.SIRSTPRSMODE', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL2.SIRSTCCAMODE', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL2.DISSIFRAMEDET', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL2.AGCRSTUPONSI', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL2.SUPERCHIPNUM', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL2.CORRNUM', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL2.SHFTWIN', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICTRL2.NARROWPULSETHRESH', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.SICORR.CORRTHRESH', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICORR.CORRTHRESHLOW', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICORR.CORRTHRESHUP', int, ModelVariableFormat.HEX)
        self._addModelRegister(model, 'MODEM.SICORR.CORRTHRESH2SYMB', int, ModelVariableFormat.HEX)

        self._addModelRegister(model, 'MODEM.SRCCHF.CHMUTETIMER', int, ModelVariableFormat.HEX)

    def _add_TXBR_regs(self, model):
        self._addModelRegister(model, 'MODEM.TXBR.TXBRNUM', int, ModelVariableFormat.HEX)


    def _add_REALTIMECFE_EXTENSCHBYP_field(self, model):
        pass

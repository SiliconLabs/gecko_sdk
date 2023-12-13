from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator


class CalcEnhancedRainier(ICalculator):

    def buildVariables(self, modem_model):
        #Required method
        pass

    def calc_enhanced_misc(self, model):
        demod_select = model.vars.demod_select.value

        if demod_select == model.vars.demod_select.var_enum.ENHANCED_DSSS:
            do_not_care = False
        else:
            do_not_care = True

        #Set the following to POR values for now when Enhanced demod is selected, otherwise don't care
        self._reg_write(model.vars.MODEM_SICTRL0_SIMODE, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL0_NOISETHRESH, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL0_PEAKNUMTHRESHLW, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL0_PEAKNUMADJ, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL0_NOISETHRESHADJ, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL0_FREQNOMINAL, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL0_NDFOCAL, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_SUPERCHIPTOLERANCE, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_SMALLSAMPLETHRESH, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_PEAKNUMP2ADJ, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_FASTMODE, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_TWOSYMBEN, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_ZCEN, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_ZCSAMPLETHRESH, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_SOFTCLIPBYPASS, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL1_SOFTCLIPTHRESH, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_SIRSTAGCMODE, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_SIRSTPRSMODE, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_SIRSTCCAMODE, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_DISSIFRAMEDET, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_AGCRSTUPONSI, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_SHFTWIN, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_SUPERCHIPNUM, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_CORRNUM, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_NARROWPULSETHRESH, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICTRL2_PEAKNUMADJEN, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICORR_CORRTHRESH, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICORR_CORRTHRESHLOW, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICORR_CORRTHRESHUP, default=True, do_not_care=do_not_care)
        self._reg_write(model.vars.MODEM_SICORR_CORRTHRESH2SYMB, default=True, do_not_care=do_not_care)

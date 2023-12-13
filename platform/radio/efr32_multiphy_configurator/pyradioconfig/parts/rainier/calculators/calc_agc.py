from pyradioconfig.parts.bobcat.calculators.calc_agc import Calc_AGC_Bobcat


class CalcAgcRainier(Calc_AGC_Bobcat):

    def calc_rssiperiod_val(self, model):
        rssi_period_val = 3
        model.vars.rssi_period.value = rssi_period_val

    def calc_antdiv_gainmode_reg(self, model):
        self._reg_write(model.vars.AGC_ANTDIV_GAINMODE, 0)

    def calc_antdiv_debouncecntthd(self, model):
        #This is do not care (functionality disabled)
        self._reg_do_not_care(model.vars.AGC_ANTDIV_DEBOUNCECNTTHD)

    # override Bobcat calc_frzpkden_reg (register has been removed in Viper)
    # Also removed in common/profiles/lynx_regs.py for Viper only
    def calc_frzpkden_reg(self, model):
        pass
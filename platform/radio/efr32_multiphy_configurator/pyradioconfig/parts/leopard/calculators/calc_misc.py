from pyradioconfig.parts.lynx.calculators.calc_misc import CALC_Misc_lynx

class calc_misc_leopard(CALC_Misc_lynx):

    def calc_lnamixlowcur_reg(self, model):
        #This field is now programmed by PTE and so don't set it in the Radio Configurator
        pass

    def calc_misc_ifadcenhalfmode(self, model):
        #This calculation is moved to calc_synth for Leopard
        pass

    def calc_misc_sylodivrloadcclksel(self, model):
        # This calculation is moved to calc_synth for Leopard
        pass

    def calc_misc_bbssdebouncetim(self, model):
        #Now moved to calc_demodulator as this is used for log2x4 for A1
        pass
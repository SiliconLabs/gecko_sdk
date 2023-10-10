from pyradioconfig.parts.viper.calculators.calc_synth import calc_synth_viper


class CalcSynthRainier(calc_synth_viper):

    def calc_sytrim_misc(self, model):
        # Removed due to SYTRIM regs no longer present in reg model for Rainier
        pass

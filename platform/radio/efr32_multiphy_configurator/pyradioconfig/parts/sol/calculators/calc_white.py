from pyradioconfig.parts.ocelot.calculators.calc_white import CALC_Whitening_Ocelot

class Calc_Whitening_Sol(CALC_Whitening_Ocelot):
    def calc_white_settings(self, model):
        self._set_block_coder_white_settings(model)

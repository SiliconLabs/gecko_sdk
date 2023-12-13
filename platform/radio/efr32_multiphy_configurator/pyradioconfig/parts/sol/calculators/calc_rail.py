from pyradioconfig.parts.ocelot.calculators.calc_rail import CalcRailOcelot

class CalcRailSol(CalcRailOcelot):

    def calc_txdone_reg(self, model):
        """
        calc_txdone_reg
        TX_DONE_DONE controls mux selecting the source of the TX_DONE signal

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        demod_sel = model.vars.demod_select.value
        is_soft_demod = demod_sel == model.vars.demod_select.var_enum.SOFT_DEMOD.value
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value

        # : MCUW_RADIO_CFG-2285 - set to 0 for Soft Modem OFDM PHYs
        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            txdone = 0
        else:
            txdone = 1

        self._reg_write(model.vars.SMCTRL_TXDONE_TXDONE, txdone, do_not_care=not is_soft_demod)
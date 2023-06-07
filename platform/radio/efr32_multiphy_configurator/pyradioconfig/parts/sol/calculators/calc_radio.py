from pyradioconfig.parts.ocelot.calculators.calc_radio import CALC_Radio_ocelot

class Calc_Radio_Sol(CALC_Radio_ocelot):

    def calc_txofdm_reg(self, model):

        #Read in model vars
        modulator_select = model.vars.modulator_select.value
        conc_ofdm = (model.vars.conc_ofdm_option.value != model.vars.conc_ofdm_option.var_enum.NONE)

        if modulator_select == model.vars.modulator_select.var_enum.IQ_MOD or conc_ofdm:
            #This method enables OFDM TX
            txenbbreg = 1
            txenmix = 1
        else:
            txenbbreg = 0
            txenmix = 0

        #Write the registers
        self._reg_write(model.vars.RAC_TXOFDM_TXENBBREG, txenbbreg)
        self._reg_write(model.vars.RAC_TXOFDM_TXENMIX, txenmix)

    def calc_rx_fefiltoutputsel_reg(self, model):
        #This method calulates the FEFILTOUTPUTSEL field

        # Read in model vars
        demod_select = model.vars.demod_select.value

        # Calculate the field
        if demod_select == model.vars.demod_select.var_enum.SOFT_DEMOD:
            fefiltoutputsel = 1
        else:
            fefiltoutputsel = 0

        # Write the register
        self._reg_write(model.vars.RAC_RX_FEFILTOUTPUTSEL, fefiltoutputsel)

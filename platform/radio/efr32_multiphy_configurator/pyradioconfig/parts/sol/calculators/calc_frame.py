from pyradioconfig.parts.ocelot.calculators.calc_frame import CALC_Frame_ocelot

class Calc_Frame_Sol(CALC_Frame_ocelot):

    def calc_ctrl_lpmodedis_reg(self, model):
        #This method calculates the LPMODEDIS field

        #Read in model vars
        demod_select = model.vars.demod_select.value

        # Calculate the field
        if demod_select == model.vars.demod_select.var_enum.SOFT_DEMOD:
            lpmodedis = 1
        else:
            lpmodedis = 0

        # Write the register
        self._reg_write(model.vars.FRC_CTRL_LPMODEDIS, lpmodedis)

    def _configure_variable_length(self, model):
        demod_select = model.vars.demod_select.value

        # Call old calculation first
        super(Calc_Frame_Sol, self)._configure_variable_length(model)

        if demod_select == model.vars.demod_select.var_enum.SOFT_DEMOD:
            # Set FRC_DFLCTRL_DFLMODE to DISABLE mode for Soft Modem modulations
            # Preserving all other settings as they are still used by packet generator
            self._reg_write(model.vars.FRC_DFLCTRL_DFLMODE, 0)


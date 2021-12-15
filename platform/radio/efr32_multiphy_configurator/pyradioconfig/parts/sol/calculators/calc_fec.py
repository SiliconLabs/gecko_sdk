from pyradioconfig.parts.ocelot.calculators.calc_fec import CALC_FEC_Ocelot

class Calc_FEC_Sol(CALC_FEC_Ocelot):

    def calc_postamble_regs(self, model):
        demod_select = model.vars.demod_select.value
        fcs_type_802154 = model.vars.fcs_type_802154.value

        if demod_select == model.vars.demod_select.var_enum.SOFT_DEMOD:
            trailtxdata = 0
            trailtxdataforce = 1
            postambleen = 0
            trailtxdatacnt = 7

            if fcs_type_802154 == model.vars.fcs_type_802154.var_enum.TWO_BYTE:
                fcs_len_byte = 2
            else:
                fcs_len_byte = 4

            trailtxreplen = fcs_len_byte - 1

            self._reg_write(model.vars.FRC_TRAILTXDATACTRL_TRAILTXDATA, trailtxdata)
            self._reg_write(model.vars.FRC_TRAILTXDATACTRL_TRAILTXDATAFORCE, trailtxdataforce)
            self._reg_write(model.vars.FRC_TRAILTXDATACTRL_POSTAMBLEEN, postambleen)
            self._reg_write(model.vars.FRC_TRAILTXDATACTRL_TRAILTXDATACNT, trailtxdatacnt)
            self._reg_write(model.vars.FRC_TRAILTXDATACTRL_TRAILTXREPLEN, trailtxreplen)

        else:
            super(Calc_FEC_Sol, self).calc_postamble_regs(model)

from pyradioconfig.parts.ocelot.calculators.calc_fec import CALC_FEC_Ocelot


class CALC_FEC_Margay(CALC_FEC_Ocelot):

    def calc_convramaddr_reg(self, model):

        #Value is static per part
        conv_ram_addr = 0x6000 >> 2

        self._reg_write(model.vars.FRC_CONVRAMADDR_CONVRAMADDR, conv_ram_addr)
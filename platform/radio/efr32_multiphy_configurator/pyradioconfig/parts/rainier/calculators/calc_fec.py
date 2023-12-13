from pyradioconfig.parts.bobcat.calculators.calc_fec import Calc_FEC_Bobcat


class CalcFecRainier(Calc_FEC_Bobcat):
	def calc_convramaddr_reg(self, model):

		#Value is static per part
		conv_ram_addr = 0xA000E000 >> 2

		self._reg_write(model.vars.FRC_CONVRAMADDR_CONVRAMADDR, conv_ram_addr)

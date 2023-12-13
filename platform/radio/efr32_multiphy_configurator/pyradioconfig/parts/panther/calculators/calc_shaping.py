from pyradioconfig.parts.nixi.calculators.calc_shaping import CALC_Shaping_nixi

class CALC_Shaping_panther(CALC_Shaping_nixi):


    def write_coeff_registers(self, model, coeff, shaping):

        self._reg_write(model.vars.MODEM_SHAPING0_COEFF0, int(coeff[0]))
        self._reg_write(model.vars.MODEM_SHAPING0_COEFF1, int(coeff[1]))
        self._reg_write(model.vars.MODEM_SHAPING0_COEFF2, int(coeff[2]))
        self._reg_write(model.vars.MODEM_SHAPING0_COEFF3, int(coeff[3]))
        self._reg_write(model.vars.MODEM_SHAPING1_COEFF4, int(coeff[4]))
        self._reg_write(model.vars.MODEM_SHAPING1_COEFF5, int(coeff[5]))
        self._reg_write(model.vars.MODEM_SHAPING1_COEFF6, int(coeff[6]))
        self._reg_write(model.vars.MODEM_SHAPING1_COEFF7, int(coeff[7]))
        self._reg_write(model.vars.MODEM_SHAPING2_COEFF8, int(coeff[8]))
        self._reg_write(model.vars.MODEM_SHAPING2_COEFF9, int(coeff[9]))
        self._reg_write(model.vars.MODEM_SHAPING2_COEFF10, int(coeff[10]))
        self._reg_write(model.vars.MODEM_SHAPING2_COEFF11, int(coeff[11]))
        self._reg_write(model.vars.MODEM_SHAPING3_COEFF12, int(coeff[12]))
        self._reg_write(model.vars.MODEM_SHAPING3_COEFF13, int(coeff[13]))
        self._reg_write(model.vars.MODEM_SHAPING3_COEFF14, int(coeff[14]))
        self._reg_write(model.vars.MODEM_SHAPING3_COEFF15, int(coeff[15]))
        self._reg_write(model.vars.MODEM_SHAPING4_COEFF16, int(coeff[16]))
        self._reg_write(model.vars.MODEM_SHAPING4_COEFF17, int(coeff[17]))
        self._reg_write(model.vars.MODEM_SHAPING4_COEFF18, int(coeff[18]))
        self._reg_write(model.vars.MODEM_SHAPING4_COEFF19, int(coeff[19]))
        self._reg_write(model.vars.MODEM_SHAPING4_COEFF20, int(coeff[20]))
        self._reg_write(model.vars.MODEM_SHAPING4_COEFF21, int(coeff[21]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF22, int(coeff[22]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF23, int(coeff[23]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF24, int(coeff[24]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF25, int(coeff[25]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF26, int(coeff[26]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF27, int(coeff[27]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF28, int(coeff[28]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF29, int(coeff[29]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF30, int(coeff[30]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF31, int(coeff[31]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF32, int(coeff[32]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF33, int(coeff[33]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF34, int(coeff[34]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF35, int(coeff[35]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF36, int(coeff[36]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF37, int(coeff[37]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF38, int(coeff[38]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF39, int(coeff[39]))

        self._reg_write(model.vars.MODEM_CTRL0_SHAPING, shaping)

    pass
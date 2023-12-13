from pyradioconfig.parts.lynx.calculators.calc_shaping import CALC_Shaping_lynx
import numpy as np
from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from pyradioconfig.calculator_model_framework.Utils.CustomExceptions import CalculationException


class CALC_Shaping_ocelot(CALC_Shaping_lynx):

    # In mode 1 and 2, I think, the calculator only generates filters with up to 8 coefficients anyway so no need to
    # update the gain calculations for those cases. If, however, we change shaping filter coefficient calculation we
    # might need to update gain calculations as well. -- Guner

    def buildVariables(self, model):
        super().buildVariables(model)
        self._addModelVariable(model, 'shaping_filter_taps', int, ModelVariableFormat.DECIMAL,
                               desc='Number of taps in the shaping filter')

    def calc_shaping_filter_gain_actual(self, model):
        # The Ocelot shaping filter registers have changed in the register map, so need to override this function

        shaping_filter_mode = model.vars.MODEM_CTRL0_SHAPING.value
        c0 = model.vars.MODEM_SHAPING0_COEFF0.value  # SHAPING0
        c1 = model.vars.MODEM_SHAPING0_COEFF1.value
        c2 = model.vars.MODEM_SHAPING0_COEFF2.value
        c3 = model.vars.MODEM_SHAPING0_COEFF3.value
        c4 = model.vars.MODEM_SHAPING1_COEFF4.value  # SHAPING1
        c5 = model.vars.MODEM_SHAPING1_COEFF5.value
        c6 = model.vars.MODEM_SHAPING1_COEFF6.value
        c7 = model.vars.MODEM_SHAPING1_COEFF7.value
        c8 = model.vars.MODEM_SHAPING2_COEFF8.value  # SHAPING2
        c9 = model.vars.MODEM_SHAPING2_COEFF9.value
        c10 = model.vars.MODEM_SHAPING2_COEFF10.value
        c11 = model.vars.MODEM_SHAPING2_COEFF11.value
        c12 = model.vars.MODEM_SHAPING3_COEFF12.value  # SHAPING3
        c13 = model.vars.MODEM_SHAPING3_COEFF13.value
        c14 = model.vars.MODEM_SHAPING3_COEFF14.value
        c15 = model.vars.MODEM_SHAPING3_COEFF15.value
        c16 = model.vars.MODEM_SHAPING4_COEFF16.value  # SHAPING4
        c17 = model.vars.MODEM_SHAPING4_COEFF17.value
        c18 = model.vars.MODEM_SHAPING4_COEFF18.value
        c19 = model.vars.MODEM_SHAPING4_COEFF19.value
        c20 = model.vars.MODEM_SHAPING5_COEFF20.value  # SHAPING5
        c21 = model.vars.MODEM_SHAPING5_COEFF21.value
        c22 = model.vars.MODEM_SHAPING5_COEFF22.value
        c23 = model.vars.MODEM_SHAPING5_COEFF23.value
        c24 = model.vars.MODEM_SHAPING6_COEFF24.value  # SHAPING6
        c25 = model.vars.MODEM_SHAPING6_COEFF25.value
        c26 = model.vars.MODEM_SHAPING6_COEFF26.value
        c27 = model.vars.MODEM_SHAPING6_COEFF27.value
        c28 = model.vars.MODEM_SHAPING7_COEFF28.value  # SHAPING7
        c29 = model.vars.MODEM_SHAPING7_COEFF29.value
        c30 = model.vars.MODEM_SHAPING7_COEFF30.value
        c31 = model.vars.MODEM_SHAPING7_COEFF31.value
        c32 = model.vars.MODEM_SHAPING8_COEFF32.value  # SHAPING8
        c33 = model.vars.MODEM_SHAPING8_COEFF33.value
        c34 = model.vars.MODEM_SHAPING8_COEFF34.value
        c35 = model.vars.MODEM_SHAPING8_COEFF35.value
        c36 = model.vars.MODEM_SHAPING9_COEFF36.value  # SHAPING9
        c37 = model.vars.MODEM_SHAPING9_COEFF37.value
        c38 = model.vars.MODEM_SHAPING9_COEFF38.value
        c39 = model.vars.MODEM_SHAPING9_COEFF39.value
        c40 = model.vars.MODEM_SHAPING10_COEFF40.value  # SHAPING10
        c41 = model.vars.MODEM_SHAPING10_COEFF41.value
        c42 = model.vars.MODEM_SHAPING10_COEFF42.value
        c43 = model.vars.MODEM_SHAPING10_COEFF43.value
        c44 = model.vars.MODEM_SHAPING11_COEFF44.value  # SHAPING11
        c45 = model.vars.MODEM_SHAPING11_COEFF45.value
        c46 = model.vars.MODEM_SHAPING11_COEFF46.value
        c47 = model.vars.MODEM_SHAPING11_COEFF47.value
        c48 = model.vars.MODEM_SHAPING12_COEFF48.value  # SHAPING12
        c49 = model.vars.MODEM_SHAPING12_COEFF49.value
        c50 = model.vars.MODEM_SHAPING12_COEFF50.value
        c51 = model.vars.MODEM_SHAPING12_COEFF51.value
        c52 = model.vars.MODEM_SHAPING13_COEFF52.value  # SHAPING13
        c53 = model.vars.MODEM_SHAPING13_COEFF53.value
        c54 = model.vars.MODEM_SHAPING13_COEFF54.value
        c55 = model.vars.MODEM_SHAPING13_COEFF55.value
        c56 = model.vars.MODEM_SHAPING14_COEFF56.value  # SHAPING14
        c57 = model.vars.MODEM_SHAPING14_COEFF57.value
        c58 = model.vars.MODEM_SHAPING14_COEFF58.value
        c59 = model.vars.MODEM_SHAPING14_COEFF59.value
        c60 = model.vars.MODEM_SHAPING15_COEFF60.value  # SHAPING15
        c61 = model.vars.MODEM_SHAPING15_COEFF61.value
        c62 = model.vars.MODEM_SHAPING15_COEFF62.value
        c63 = model.vars.MODEM_SHAPING15_COEFF63.value


        if shaping_filter_mode == 0:
            shaping_filter_gain = 127

        elif shaping_filter_mode == 1:
            shaping_filter_gain = max(c0 + c8 + c0, c1 + c7, c2 + c6, c3 + c5, c4 + c4)

        elif shaping_filter_mode == 2:
            shaping_filter_gain = max(c0 + c7, c1 + c6, c2 + c5, c3 + c4)

        else:
            shaping_filter_gain = max(c0 + c8 + c16 + c24 + c32 + c40 + c48 + c56,
                                      c1 + c9 + c17 + c25 + c33 + c41 + c49 + c57,
                                      c2 + c10 + c18 + c26 + c34 + c42 + c50 + c58,
                                      c3 + c11 + c19 + c27 + c35 + c43 + c51 + c59,
                                      c4 + c12 + c20 + c28 + c36 + c44 + c52 + c60,
                                      c5 + c13 + c21 + c29 + c37 + c45 + c53 + c61,
                                      c6 + c14 + c22 + c30 + c38 + c46 + c54 + c62,
                                      c7 + c15 + c23 + c31 + c39 + c47 + c55 + c63)

        model.vars.shaping_filter_gain_actual.value = int(shaping_filter_gain)

    def get_shaping_filter(self, model):
        # Construct shaping filter from register settings

        shaping_filter_mode = model.vars.MODEM_CTRL0_SHAPING.value
        c0 = model.vars.MODEM_SHAPING0_COEFF0.value  # SHAPING0
        c1 = model.vars.MODEM_SHAPING0_COEFF1.value
        c2 = model.vars.MODEM_SHAPING0_COEFF2.value
        c3 = model.vars.MODEM_SHAPING0_COEFF3.value
        c4 = model.vars.MODEM_SHAPING1_COEFF4.value  # SHAPING1
        c5 = model.vars.MODEM_SHAPING1_COEFF5.value
        c6 = model.vars.MODEM_SHAPING1_COEFF6.value
        c7 = model.vars.MODEM_SHAPING1_COEFF7.value
        c8 = model.vars.MODEM_SHAPING2_COEFF8.value  # SHAPING2
        c9 = model.vars.MODEM_SHAPING2_COEFF9.value
        c10 = model.vars.MODEM_SHAPING2_COEFF10.value
        c11 = model.vars.MODEM_SHAPING2_COEFF11.value
        c12 = model.vars.MODEM_SHAPING3_COEFF12.value  # SHAPING3
        c13 = model.vars.MODEM_SHAPING3_COEFF13.value
        c14 = model.vars.MODEM_SHAPING3_COEFF14.value
        c15 = model.vars.MODEM_SHAPING3_COEFF15.value
        c16 = model.vars.MODEM_SHAPING4_COEFF16.value  # SHAPING4
        c17 = model.vars.MODEM_SHAPING4_COEFF17.value
        c18 = model.vars.MODEM_SHAPING4_COEFF18.value
        c19 = model.vars.MODEM_SHAPING4_COEFF19.value
        c20 = model.vars.MODEM_SHAPING5_COEFF20.value  # SHAPING5
        c21 = model.vars.MODEM_SHAPING5_COEFF21.value
        c22 = model.vars.MODEM_SHAPING5_COEFF22.value
        c23 = model.vars.MODEM_SHAPING5_COEFF23.value
        c24 = model.vars.MODEM_SHAPING6_COEFF24.value  # SHAPING6
        c25 = model.vars.MODEM_SHAPING6_COEFF25.value
        c26 = model.vars.MODEM_SHAPING6_COEFF26.value
        c27 = model.vars.MODEM_SHAPING6_COEFF27.value
        c28 = model.vars.MODEM_SHAPING7_COEFF28.value  # SHAPING7
        c29 = model.vars.MODEM_SHAPING7_COEFF29.value
        c30 = model.vars.MODEM_SHAPING7_COEFF30.value
        c31 = model.vars.MODEM_SHAPING7_COEFF31.value
        c32 = model.vars.MODEM_SHAPING8_COEFF32.value  # SHAPING8
        c33 = model.vars.MODEM_SHAPING8_COEFF33.value
        c34 = model.vars.MODEM_SHAPING8_COEFF34.value
        c35 = model.vars.MODEM_SHAPING8_COEFF35.value
        c36 = model.vars.MODEM_SHAPING9_COEFF36.value  # SHAPING9
        c37 = model.vars.MODEM_SHAPING9_COEFF37.value
        c38 = model.vars.MODEM_SHAPING9_COEFF38.value
        c39 = model.vars.MODEM_SHAPING9_COEFF39.value
        c40 = model.vars.MODEM_SHAPING10_COEFF40.value  # SHAPING10
        c41 = model.vars.MODEM_SHAPING10_COEFF41.value
        c42 = model.vars.MODEM_SHAPING10_COEFF42.value
        c43 = model.vars.MODEM_SHAPING10_COEFF43.value
        c44 = model.vars.MODEM_SHAPING11_COEFF44.value  # SHAPING11
        c45 = model.vars.MODEM_SHAPING11_COEFF45.value
        c46 = model.vars.MODEM_SHAPING11_COEFF46.value
        c47 = model.vars.MODEM_SHAPING11_COEFF47.value
        c48 = model.vars.MODEM_SHAPING12_COEFF48.value  # SHAPING12
        c49 = model.vars.MODEM_SHAPING12_COEFF49.value
        c50 = model.vars.MODEM_SHAPING12_COEFF50.value
        c51 = model.vars.MODEM_SHAPING12_COEFF51.value
        c52 = model.vars.MODEM_SHAPING13_COEFF52.value  # SHAPING13
        c53 = model.vars.MODEM_SHAPING13_COEFF53.value
        c54 = model.vars.MODEM_SHAPING13_COEFF54.value
        c55 = model.vars.MODEM_SHAPING13_COEFF55.value
        c56 = model.vars.MODEM_SHAPING14_COEFF56.value  # SHAPING14
        c57 = model.vars.MODEM_SHAPING14_COEFF57.value
        c58 = model.vars.MODEM_SHAPING14_COEFF58.value
        c59 = model.vars.MODEM_SHAPING14_COEFF59.value
        c60 = model.vars.MODEM_SHAPING15_COEFF60.value  # SHAPING15
        c61 = model.vars.MODEM_SHAPING15_COEFF61.value
        c62 = model.vars.MODEM_SHAPING15_COEFF62.value
        c63 = model.vars.MODEM_SHAPING15_COEFF63.value

        if shaping_filter_mode == 0:
            sp = np.array([127, 127, 127, 127, 127, 127, 127, 127])

        elif shaping_filter_mode == 1:
            sp = np.array([c0, c1, c2, c3, c4, c5, c6, c7, c8, c7, c6, c5, c4, c3, c2, c1, c0])

        elif shaping_filter_mode == 2:
            sp = np.array([c0, c1, c2, c3, c4, c5, c6, c7, c7, c6, c5, c4, c3, c2, c1, c0])

        else:
            sp = np.array([ c0,  c1,  c2,  c3,  c4,  c5,  c6,  c7,  c8,  c9, c10, c11, c12, c13, c14, c15,
                            c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27, c28, c29, c30, c31,
                            c32, c33, c34, c35, c36, c37, c38, c39, c40, c41, c42, c43, c44, c45, c46, c47,
                            c48, c49, c50, c51, c52, c53, c54, c55, c56, c57, c58, c59, c60, c61, c62, c63])
        return sp

    def calc_filter_tap_length(self, model):
        """ Calculate shaping filter delay in samples """
        shaping = model.vars.MODEM_CTRL0_SHAPING.value

        taps = 0
        if shaping == 0: # : DISABLED
            taps = 8
        elif shaping == 1: # : ODDLENGTH
            taps = 17
        elif shaping == 2: # : EVENLENGTH
            taps = 16
        elif shaping == 3: # : Asymmetric
            taps = 64
        else: # : Unsupported selection
            LogMgr.Error(f"Error: Unsupported shaping value of {shaping}!")

        model.vars.shaping_filter_taps.value = taps

    def calc_max_available_filter_taps(self, model):
        # this is fixed for a family of parts
        model.vars.max_filter_taps.value = 64

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
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF20, int(coeff[20]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF21, int(coeff[21]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF22, int(coeff[22]))
        self._reg_write(model.vars.MODEM_SHAPING5_COEFF23, int(coeff[23]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF24, int(coeff[24]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF25, int(coeff[25]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF26, int(coeff[26]))
        self._reg_write(model.vars.MODEM_SHAPING6_COEFF27, int(coeff[27]))
        self._reg_write(model.vars.MODEM_SHAPING7_COEFF28, int(coeff[28]))
        self._reg_write(model.vars.MODEM_SHAPING7_COEFF29, int(coeff[29]))
        self._reg_write(model.vars.MODEM_SHAPING7_COEFF30, int(coeff[30]))
        self._reg_write(model.vars.MODEM_SHAPING7_COEFF31, int(coeff[31]))
        self._reg_write(model.vars.MODEM_SHAPING8_COEFF32, int(coeff[32]))
        self._reg_write(model.vars.MODEM_SHAPING8_COEFF33, int(coeff[33]))
        self._reg_write(model.vars.MODEM_SHAPING8_COEFF34, int(coeff[34]))
        self._reg_write(model.vars.MODEM_SHAPING8_COEFF35, int(coeff[35]))
        self._reg_write(model.vars.MODEM_SHAPING9_COEFF36, int(coeff[36]))
        self._reg_write(model.vars.MODEM_SHAPING9_COEFF37, int(coeff[37]))
        self._reg_write(model.vars.MODEM_SHAPING9_COEFF38, int(coeff[38]))
        self._reg_write(model.vars.MODEM_SHAPING9_COEFF39, int(coeff[39]))
        self._reg_write(model.vars.MODEM_SHAPING10_COEFF40, int(coeff[40]))
        self._reg_write(model.vars.MODEM_SHAPING10_COEFF41, int(coeff[41]))
        self._reg_write(model.vars.MODEM_SHAPING10_COEFF42, int(coeff[42]))
        self._reg_write(model.vars.MODEM_SHAPING10_COEFF43, int(coeff[43]))
        self._reg_write(model.vars.MODEM_SHAPING11_COEFF44, int(coeff[44]))
        self._reg_write(model.vars.MODEM_SHAPING11_COEFF45, int(coeff[45]))
        self._reg_write(model.vars.MODEM_SHAPING11_COEFF46, int(coeff[46]))
        self._reg_write(model.vars.MODEM_SHAPING11_COEFF47, int(coeff[47]))
        self._reg_write(model.vars.MODEM_SHAPING12_COEFF48, int(coeff[48]))
        self._reg_write(model.vars.MODEM_SHAPING12_COEFF49, int(coeff[49]))
        self._reg_write(model.vars.MODEM_SHAPING12_COEFF50, int(coeff[50]))
        self._reg_write(model.vars.MODEM_SHAPING12_COEFF51, int(coeff[51]))
        self._reg_write(model.vars.MODEM_SHAPING13_COEFF52, int(coeff[52]))
        self._reg_write(model.vars.MODEM_SHAPING13_COEFF53, int(coeff[53]))
        self._reg_write(model.vars.MODEM_SHAPING13_COEFF54, int(coeff[54]))
        self._reg_write(model.vars.MODEM_SHAPING13_COEFF55, int(coeff[55]))
        self._reg_write(model.vars.MODEM_SHAPING14_COEFF56, int(coeff[56]))
        self._reg_write(model.vars.MODEM_SHAPING14_COEFF57, int(coeff[57]))
        self._reg_write(model.vars.MODEM_SHAPING14_COEFF58, int(coeff[58]))
        self._reg_write(model.vars.MODEM_SHAPING14_COEFF59, int(coeff[59]))
        self._reg_write(model.vars.MODEM_SHAPING15_COEFF60, int(coeff[60]))
        self._reg_write(model.vars.MODEM_SHAPING15_COEFF61, int(coeff[61]))
        self._reg_write(model.vars.MODEM_SHAPING15_COEFF62, int(coeff[62]))
        self._reg_write(model.vars.MODEM_SHAPING15_COEFF63, int(coeff[63]))

        self._reg_write(model.vars.MODEM_CTRL0_SHAPING, shaping)

    def get_coeff_ceil(self, model):
        # all filter taps are 8 bit signed registers
        max_filter_taps = model.vars.max_filter_taps.value
        coeff_ceil = np.empty(max_filter_taps)
        # all filter taps are 8 bit signed registers
        coeff_ceil.fill((2 ** (8 - 1)) - 1)
        return coeff_ceil
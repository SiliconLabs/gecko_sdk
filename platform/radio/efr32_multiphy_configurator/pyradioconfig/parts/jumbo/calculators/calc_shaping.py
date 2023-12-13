"""Core AGC Calculator Package

Calculator functions are pulled by using their names.
Calculator functions must start with "calc_", if they are to be consumed by the framework.
    Or they should be returned by overriding the function:
        def getCalculationList(self):
"""

from collections import OrderedDict
import math
import numpy as np

from enum import Enum
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator
from pycalcmodel.core.variable import ModelVariableFormat
from pyradioconfig.parts.common.utils.tinynumpy import tinynumpy
from pyradioconfig.parts.common.calculators.calc_shaping import CALC_Shaping
from pyradioconfig.calculator_model_framework.Utils.CustomExceptions import CalculationException
from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr

class CALC_Shaping_jumbo(CALC_Shaping):

    def gaussian_shaping_filter(self, model, scaling_fac = 127):
        """

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        # for gaussian pulse shapes pulse_shape_parameter holds BT value
        bt = model.vars.shaping_filter_param.value
        max_filter_taps = model.vars.max_filter_taps.value
        req_filter_taps = self.get_required_filter_taps(bt)

        if req_filter_taps > max_filter_taps:
            minumum_bt_supported = 8 / max_filter_taps
            bt = minumum_bt_supported
            LogMgr.Error("ERROR: BT < {} not supported on this part, overriding the current BT to {}".format(minumum_bt_supported, minumum_bt_supported))


        # Even mode uses 16 taps (c0, c1...c7, c7, c6... c1, c0). Therefore anything that needs less than 16 taps can be
        # implemented using Even mode
        if req_filter_taps < 17:
            shaping = 2 # sets shaping filter in Even mode
            # map BT value to standard deviation
            std = 1.05 / bt

            # generate gaussian pulse shape
            w = self.gaussian(17, std)
            # scale for unit DC gain
            w = tinynumpy.divide(w, w.sum())
            # convolve with square wave of oversampling rate width which is 8 for the shaping filter
            f_hack = tinynumpy.convolve(w, tinynumpy.ones((1, 8)).flatten())
            # scale and quantize coefficients
            c_hack = tinynumpy.round_((84.5 * f_hack))
            # keep only 8 coeffs from the peak filter tap
            coeff = c_hack[4:12]

            return coeff, shaping

        else:
            shaping = 3 # sets shaping filter in Asymmetric mode
            # map BT value to standard deviation
            std = 1.05 / bt

            # generate gaussian pulse shape
            w = self.gaussian(int(max_filter_taps + 1 - 8), std) # To get max_filter_taps points after convolution
            # scale for unit DC gain
            w = tinynumpy.divide(w, w.sum())
            # convolve with square wave of oversampling rate width which is 8 for the shaping filter
            f_hack = tinynumpy.convolve(w, tinynumpy.ones((1, 8)).flatten())
            # scale and quantize coefficients
            c_hack = tinynumpy.round_((scaling_fac * f_hack))
            # keep only non 0 coeffs as 0 coeffs in the beginning add unnecessary delay to the TX chain
            c_hack = np.array(c_hack)
            coeff = c_hack[c_hack != 0]
            # return coeffs
            return coeff, shaping

    def calc_shaping_filter_gain_actual(self, model):
        """
        given shaping filter coefficients and mode calculate shaping filter gain
        Equations from Table 5.26 in EFR32 Reference Manual (internal.pdf)

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        shaping_filter_mode = model.vars.MODEM_CTRL0_SHAPING.value
        c0 = model.vars.MODEM_SHAPING0_COEFF0.value
        c1 = model.vars.MODEM_SHAPING0_COEFF1.value
        c2 = model.vars.MODEM_SHAPING0_COEFF2.value
        c3 = model.vars.MODEM_SHAPING0_COEFF3.value
        c4 = model.vars.MODEM_SHAPING1_COEFF4.value
        c5 = model.vars.MODEM_SHAPING1_COEFF5.value
        c6 = model.vars.MODEM_SHAPING1_COEFF6.value
        c7 = model.vars.MODEM_SHAPING1_COEFF7.value
        c8 = model.vars.MODEM_SHAPING2_COEFF8.value
        c9 = model.vars.MODEM_SHAPING2_COEFF9.value
        c10 = model.vars.MODEM_SHAPING2_COEFF10.value
        c11 = model.vars.MODEM_SHAPING2_COEFF11.value
        c12 = model.vars.MODEM_SHAPING3_COEFF12.value
        c13 = model.vars.MODEM_SHAPING3_COEFF13.value
        c14 = model.vars.MODEM_SHAPING3_COEFF14.value
        c15 = model.vars.MODEM_SHAPING3_COEFF15.value
        c16 = model.vars.MODEM_SHAPING4_COEFF16.value
        c17 = model.vars.MODEM_SHAPING4_COEFF17.value
        c18 = model.vars.MODEM_SHAPING4_COEFF18.value
        c19 = model.vars.MODEM_SHAPING4_COEFF19.value
        c20 = model.vars.MODEM_SHAPING4_COEFF20.value
        c21 = model.vars.MODEM_SHAPING4_COEFF21.value
        c22 = model.vars.MODEM_SHAPING5_COEFF22.value
        c23 = model.vars.MODEM_SHAPING5_COEFF23.value
        c24 = model.vars.MODEM_SHAPING5_COEFF24.value
        c25 = model.vars.MODEM_SHAPING5_COEFF25.value
        c26 = model.vars.MODEM_SHAPING5_COEFF26.value
        c27 = model.vars.MODEM_SHAPING5_COEFF27.value
        c28 = model.vars.MODEM_SHAPING5_COEFF28.value
        c29 = model.vars.MODEM_SHAPING5_COEFF29.value
        c30 = model.vars.MODEM_SHAPING6_COEFF30.value
        c31 = model.vars.MODEM_SHAPING6_COEFF31.value
        c32 = model.vars.MODEM_SHAPING6_COEFF32.value
        c33 = model.vars.MODEM_SHAPING6_COEFF33.value
        c34 = model.vars.MODEM_SHAPING6_COEFF34.value
        c35 = model.vars.MODEM_SHAPING6_COEFF35.value
        c36 = model.vars.MODEM_SHAPING6_COEFF36.value
        c37 = model.vars.MODEM_SHAPING6_COEFF37.value
        c38 = model.vars.MODEM_SHAPING6_COEFF38.value
        c39 = model.vars.MODEM_SHAPING6_COEFF39.value


        if shaping_filter_mode == 0:
            shaping_filter_gain = 127

        elif shaping_filter_mode == 1:
            shaping_filter_gain = max(c0+c8+c0, c1+c7, c2+c6, c3+c5, c4+c4)

        elif shaping_filter_mode == 2:
            shaping_filter_gain = max(c0+c7, c1+c6, c2+c5, c3+c4)

        else:
            shaping_filter_gain = max(c0+c8 +c16+c24+c32,
                                      c1+c9 +c17+c25+c33,
                                      c2+c10+c18+c26+c34,
                                      c3+c11+c19+c27+c35,
                                      c4+c12+c20+c28+c36,
                                      c5+c13+c21+c29+c37,
                                      c6+c14+c22+c30+c38,
                                      c7+c15+c23+c31+c39)

        model.vars.shaping_filter_gain_actual.value = int(shaping_filter_gain)

    def calc_max_available_filter_taps(self, model):
        # this is fixed for a family of parts
        model.vars.max_filter_taps.value = 40

    def calc_shaping_reg(self, model):
        """
        given shaping filter input parameter set shaping filter coeffs and type

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        shaping_filter_option = model.vars.shaping_filter.value
        max_filter_taps = model.vars.max_filter_taps.value
        coeff = np.zeros(max_filter_taps)
        shaping = 0
        if shaping_filter_option.value == model.vars.shaping_filter.var_enum.NONE.value:
            shaping = 0

        elif shaping_filter_option.value == model.vars.shaping_filter.var_enum.Gaussian.value:
            calc_coeff_error = True
            scaling_fac = 127
            # The loop here uses "check_coeff_write_error" to make sure we are not writing any filter tap coefficient
            # with a value greater than its bit-width capacity. If "check_coeff_write_error" returns True, we scale the
            # coefficients down and keep scaling the coefficients down untill all coefficients fit the respective
            # signed bit-wdith fields.
            # This is to handle the special case of Nerio, Nixi and Jumbo where not all filter taps coefficients are
            # 8-bit signed registers
            while calc_coeff_error:
                # adding an exit condition
                if scaling_fac < 0:
                    c = np.zeros(max_filter_taps)
                    shaping = 3
                else:
                    c, shaping = self.gaussian_shaping_filter(model, scaling_fac)
                    # Create temporary coeff
                    temp_coeff = np.zeros(max_filter_taps)
                    # read values in temporary coffs
                    temp_coeff = self.update_coeffs(model, c, temp_coeff)
                    calc_coeff_error = self.check_coeff_write_error(model, temp_coeff)
                    scaling_fac = scaling_fac - 10

            coeff = self.update_coeffs(model, c, coeff)

        elif shaping_filter_option.value == model.vars.shaping_filter.var_enum.Custom_OQPSK.value:
            # Not sure what filter this is
            coeff[0] = coeff[1] = 1
            coeff[2] = 16
            coeff[3] = 48
            coeff[4] = 80
            coeff[5] = 112
            coeff[6] = coeff[7] = 127
            coeff[8] = 0
            shaping = 2

        elif shaping_filter_option.value == model.vars.shaping_filter.var_enum.Raised_Cosine.value:
            c = self.raised_cosine_filter(model)
            shaping = 1
            coeff = self.update_coeffs(model, c, coeff)

        elif shaping_filter_option.value == model.vars.shaping_filter.var_enum.Root_Raised_Cosine.value:
            c = self.root_raised_cosine_filter(model)
            shaping = 1
            coeff = self.update_coeffs(model, c, coeff)

        # filter derived from Imagotag legacy PHY transmit capture
        elif shaping_filter_option.value == model.vars.shaping_filter.var_enum.Custom_PSK.value:
            coeff[0] = 51
            coeff[1] = 117
            coeff[2] = 96
            coeff[3] = 53
            coeff[4] = 20
            coeff[5] = 2
            coeff[6] = 0
            coeff[7] = 0
            coeff[8] = 0  # not used
            shaping = 3
        else:
            raise CalculationException("ERROR: Unrecognized shaping filter option")

        self.write_coeff_registers(model, coeff, shaping)


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

    def update_coeffs(self, model, calc_c, coeff):
        """
        Coefficients calculated are mostly not the same length as the available filter taps. This method basically copys
        the calculated coefficients (from COEFF0 onwards) to corresponding taps and keep other non-calculated tap's
        coeffs to 0

        Args:
            model: rc model
            calc_c: calculated coefficients
            coeff: coefficients that will be copied into registers

        Returns:
            coeff: coefficents with calculated coeffs
        """
        max_filter_taps = model.vars.max_filter_taps.value
        # replace calculated coefficients and keep others as 0
        for idx in range(len(calc_c)):
            if idx > max_filter_taps:
                coeff[idx] = 0
            else:
                coeff[idx] = calc_c[idx]
        return coeff

    def get_coeff_ceil(self, model):
        max_filter_taps = model.vars.max_filter_taps.value
        coeff_ceil = np.zeros(max_filter_taps)
        coeff_ceil[0] = 2 ** (model.vars.MODEM_SHAPING0_COEFF0.get_bit_width() - 1) - 1
        coeff_ceil[1] = 2 ** (model.vars.MODEM_SHAPING0_COEFF1.get_bit_width() - 1) - 1
        coeff_ceil[2] = 2 ** (model.vars.MODEM_SHAPING0_COEFF2.get_bit_width() - 1) - 1
        coeff_ceil[3] = 2 ** (model.vars.MODEM_SHAPING0_COEFF3.get_bit_width() - 1) - 1
        coeff_ceil[4] = 2 ** (model.vars.MODEM_SHAPING1_COEFF4.get_bit_width() - 1) - 1
        coeff_ceil[5] = 2 ** (model.vars.MODEM_SHAPING1_COEFF5.get_bit_width() - 1) - 1
        coeff_ceil[6] = 2 ** (model.vars.MODEM_SHAPING1_COEFF6.get_bit_width() - 1) - 1
        coeff_ceil[7] = 2 ** (model.vars.MODEM_SHAPING1_COEFF7.get_bit_width() - 1) - 1
        coeff_ceil[8] = 2 ** (model.vars.MODEM_SHAPING2_COEFF8.get_bit_width() - 1) - 1
        coeff_ceil[9] = 2 ** (model.vars.MODEM_SHAPING2_COEFF9.get_bit_width() - 1) - 1
        coeff_ceil[10] = 2 ** (model.vars.MODEM_SHAPING2_COEFF10.get_bit_width() - 1) - 1
        coeff_ceil[11] = 2 ** (model.vars.MODEM_SHAPING2_COEFF11.get_bit_width() - 1) - 1
        coeff_ceil[12] = 2 ** (model.vars.MODEM_SHAPING3_COEFF12.get_bit_width() - 1) - 1
        coeff_ceil[13] = 2 ** (model.vars.MODEM_SHAPING3_COEFF13.get_bit_width() - 1) - 1
        coeff_ceil[14] = 2 ** (model.vars.MODEM_SHAPING3_COEFF14.get_bit_width() - 1) - 1
        coeff_ceil[15] = 2 ** (model.vars.MODEM_SHAPING3_COEFF15.get_bit_width() - 1) - 1
        coeff_ceil[16] = 2 ** (model.vars.MODEM_SHAPING4_COEFF16.get_bit_width() - 1) - 1
        coeff_ceil[17] = 2 ** (model.vars.MODEM_SHAPING4_COEFF17.get_bit_width() - 1) - 1
        coeff_ceil[18] = 2 ** (model.vars.MODEM_SHAPING4_COEFF18.get_bit_width() - 1) - 1
        coeff_ceil[19] = 2 ** (model.vars.MODEM_SHAPING4_COEFF19.get_bit_width() - 1) - 1
        coeff_ceil[20] = 2 ** (model.vars.MODEM_SHAPING4_COEFF20.get_bit_width() - 1) - 1
        coeff_ceil[21] = 2 ** (model.vars.MODEM_SHAPING4_COEFF21.get_bit_width() - 1) - 1
        coeff_ceil[22] = 2 ** (model.vars.MODEM_SHAPING5_COEFF22.get_bit_width() - 1) - 1
        coeff_ceil[23] = 2 ** (model.vars.MODEM_SHAPING5_COEFF23.get_bit_width() - 1) - 1
        coeff_ceil[24] = 2 ** (model.vars.MODEM_SHAPING5_COEFF24.get_bit_width() - 1) - 1
        coeff_ceil[25] = 2 ** (model.vars.MODEM_SHAPING5_COEFF25.get_bit_width() - 1) - 1
        coeff_ceil[26] = 2 ** (model.vars.MODEM_SHAPING5_COEFF26.get_bit_width() - 1) - 1
        coeff_ceil[27] = 2 ** (model.vars.MODEM_SHAPING5_COEFF27.get_bit_width() - 1) - 1
        coeff_ceil[28] = 2 ** (model.vars.MODEM_SHAPING5_COEFF28.get_bit_width() - 1) - 1
        coeff_ceil[29] = 2 ** (model.vars.MODEM_SHAPING5_COEFF29.get_bit_width() - 1) - 1
        coeff_ceil[30] = 2 ** (model.vars.MODEM_SHAPING6_COEFF30.get_bit_width() - 1) - 1
        coeff_ceil[31] = 2 ** (model.vars.MODEM_SHAPING6_COEFF31.get_bit_width() - 1) - 1
        coeff_ceil[32] = 2 ** (model.vars.MODEM_SHAPING6_COEFF32.get_bit_width() - 1) - 1
        coeff_ceil[33] = 2 ** (model.vars.MODEM_SHAPING6_COEFF33.get_bit_width() - 1) - 1
        coeff_ceil[34] = 2 ** (model.vars.MODEM_SHAPING6_COEFF34.get_bit_width() - 1) - 1
        coeff_ceil[35] = 2 ** (model.vars.MODEM_SHAPING6_COEFF35.get_bit_width() - 1) - 1
        coeff_ceil[36] = 2 ** (model.vars.MODEM_SHAPING6_COEFF36.get_bit_width() - 1) - 1
        coeff_ceil[37] = 2 ** (model.vars.MODEM_SHAPING6_COEFF37.get_bit_width() - 1) - 1
        coeff_ceil[38] = 2 ** (model.vars.MODEM_SHAPING6_COEFF38.get_bit_width() - 1) - 1
        coeff_ceil[39] = 2 ** (model.vars.MODEM_SHAPING6_COEFF39.get_bit_width() - 1) - 1
        return coeff_ceil

    def check_coeff_write_error(self, model, temp_coeffs):
        """
        COEFF 0-15        8 bits
        COEFF 16-18       6 bits
        COEFF 19-20       5 bits
        COEFF 21-31       4 bits
        COEFF 32-39       3 bits
        For Nerio, Nixi and Panther, we don't have all filter taps coefficients using 8 bit width registers. This method
        basically checks and makes sure calculator run doesn't fails if we try to write a value greater than
        the supported bit width for a register.
        Args:
            model: rc model
            temp_coeffs: temporary calculated coefficients to be checked

        Returns:
            error: True if we are writing a value greater than  the supported bit width for a register
        """
        coeff_ceil = self.get_coeff_ceil(model)
        if len(coeff_ceil) != len(temp_coeffs):
            return True
        else:
            coeff_ceil = np.array(coeff_ceil)
            temp_coeffs = np.array(temp_coeffs)
            # check if any temp_coeffs is greater than coeff_ceil
            error = np.any((coeff_ceil - temp_coeffs) < 0)

            return error

from pyradioconfig.parts.common.calculators.calc_modulator import CALC_Modulator
from py_2_and_3_compatibility import *


class CALC_Modulator_Panther(CALC_Modulator):

    def calc_txbr_reg(self, model):
        """
        given desired TX baudrate ratio calculate TXBRNUM and TXBRDEN
        that gets as close as possible to the ratio.
        Note that we start from the highest possible value for TXBRDEN
        and go down since having largest possible values in these register
        to have better phase resolution in OQPSK and MSK (see end of section
        5.6.5 in the manual)

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        ratio = model.vars.txbr_ratio.value
        txbr_num_err_tol = 0.003
        txbr_max_den = 255

        # : local variable for finding baudrate ratio that minimizes error between desired and actual baudrate
        txbr_num_err_map = {}

        # find best integer ratio to match desired ratio
        found_best_ratio = False
        for den in xrange(txbr_max_den, 0, -1):
            num = ratio * den
            txbr_num_err = abs(round(num) - num)

            if num < 32768:
                txbr_num_err_map[den] = abs(txbr_num_err - txbr_num_err_tol)
                if txbr_num_err < txbr_num_err_tol:
                    found_best_ratio = True
                    break

        # if best integer ratio is not found, re-calculate and find the ratio that is closest to the tolerance
        if not found_best_ratio:
            if len(txbr_num_err_map) > 0:
                den = min(txbr_num_err_map, key=txbr_num_err_map.get)
            else:
                den = 1
            num = ratio * den

        self._reg_write(model.vars.MODEM_TXBR_TXBRNUM, int(round(num)))
        self._reg_write(model.vars.MODEM_TXBR_TXBRDEN, int(den))
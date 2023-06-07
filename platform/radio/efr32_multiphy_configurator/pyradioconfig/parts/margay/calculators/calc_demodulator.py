from pyradioconfig.parts.ocelot.calculators.calc_demodulator import CALC_Demodulator_ocelot
from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr
from math import *


class CALC_Demodulator_Margay(CALC_Demodulator_ocelot):

    # override inhereited variable defining threshold for _channel_filter_clocks_valid
    chf_required_clks_per_sample = 3  # fixed in PGMARGAY-1557

    def _check_trecs_required_clk_cycles(self, adc_freq, baudrate, osr, dec0, dec1, xtal_frequency_hz, relaxsrc2,
                                         model):
        # Returns True if the filter chain configuration meets the requirement for trecs
        # minimum clock cycles between samples. Returns False if the configuration is invalid
        #
        # PGMARGAY-106 added configurable clk spacing for interpolated samples. Compute minimum sample clk spacing.
        # (same as sol) but since margay inherits from ocelot, copy here.

        # calculate the src_ratio as this function is called in the process of evaluating
        # osr, dec0, dec1, so the src_ratio_actual cannot be calculated
        dec1_freq = adc_freq / (8 * dec0 * dec1)
        src_freq = baudrate * osr
        src_ratio = src_freq / dec1_freq
        TRECS_REQUIRED_CLKS_PER_SAMPLE = 3

        if src_ratio > 1:
            # sample clk is not equi-spaced, interpolated samples have best-case spacing of 1/2 relative to src disabled
            # while using UPGAPS clk delay adjustment in the SRW CMU
            cycles_per_sample = floor(xtal_frequency_hz / src_freq / 2)
        else:
            cycles_per_sample = floor(xtal_frequency_hz / src_freq)

        if cycles_per_sample < TRECS_REQUIRED_CLKS_PER_SAMPLE:
            return False
        else:
            return True

    def calc_log2x4fwsel_reg(self, model):
        # set to use LOG2X4 register value for log2 calculation in DEC1 rather than HW calculation
        self._reg_write(model.vars.MODEM_LOG2X4_LOG2X4FWSEL, 1)

    def calc_log2x4_reg(self, model):
        # given DEC1 decimation ratio calculate log2 in 4Q2 format
        dec1 = model.vars.dec1_actual.value

        val = floor(4.0*log2(dec1))

        self._reg_write(model.vars.MODEM_LOG2X4_LOG2X4, val)

    def calc_log2x4_actual(self, model):
        # Read in model vars
        log2x4fwsel = model.vars.MODEM_LOG2X4_LOG2X4FWSEL.value
        log2x4_reg = model.vars.MODEM_LOG2X4_LOG2X4.value
        dec1_actual = model.vars.dec1_actual.value

        if log2x4fwsel == 1:
            log2x4_actual = log2x4_reg
        else:
            log2x4_actual = floor(4*log2(dec1_actual))

        # Write the model var
        model.vars.log2x4_actual.value = log2x4_actual

    def calc_rssi_rf_adjust_db(self, model):

        #Read in model vars
        rf_band = model.vars.rf_band.value

        #Calculate rf adjustment based on band
        if rf_band == model.vars.rf_band.var_enum.BAND_169:
            rssi_rf_adjust_db = -19.03
        elif rf_band == model.vars.rf_band.var_enum.BAND_315:
            rssi_rf_adjust_db = -17.13
        elif rf_band == model.vars.rf_band.var_enum.BAND_434:
            rssi_rf_adjust_db = -15.98
        elif rf_band == model.vars.rf_band.var_enum.BAND_490:
            rssi_rf_adjust_db = -14.90
        elif rf_band == model.vars.rf_band.var_enum.BAND_868:
            rssi_rf_adjust_db = -11.02
        elif rf_band == model.vars.rf_band.var_enum.BAND_915:
            rssi_rf_adjust_db = -10.10
        elif rf_band == model.vars.rf_band.var_enum.BAND_2400:
            rssi_rf_adjust_db = -2.65
        else:
            LogMgr.Warning("Warning: No RSSI adjustment available for this band")
            rssi_rf_adjust_db = -11.0 #This was the default in early RAIL for Margay and so won't impact customers for now

        #Write the model var
        model.vars.rssi_rf_adjust_db.value = rssi_rf_adjust_db
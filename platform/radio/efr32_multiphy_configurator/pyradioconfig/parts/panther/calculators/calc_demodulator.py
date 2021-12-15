from pyradioconfig.parts.nixi.calculators.calc_demodulator import CALC_Demodulator_nixi
import math
import itertools

from py_2_and_3_compatibility import *

class CALC_Demodulator_panther(CALC_Demodulator_nixi):

    def calc_fxo_or_fdec8(self, model):
        if (model.phy.name.find("CTUNE") > 0) or (model.phy.name.find("CW") > 0):
            # Leaving the legacy EFR32 90nm calculation here so the utility PHYs will calculate
            # Otherwise the utility PHYs will never resolve model.vars.xtal_frequency.value, so many, many calculations will never run.
            # TODO: Likely need a better solution here long term
            model.vars.fxo_or_fdec8.value = model.vars.xtal_frequency.value * 1.0

            # FIXME: Some 40nm PHYs must specify phy.profile_inputs.if_frequency_hz.value
            # Seems connected to a circular dependency in calc_fxo_or_fdec8 needing  model.vars.rx_synth_freq_actual

        # Note Panther will overload this to LO / 64
        # EFR32 90nm parts (Dumbo, Jumbo, Nerio, Nixi) use fxo here.
        model.vars.fxo_or_fdec8.value = model.vars.rx_synth_freq_actual.value / 64.0 # Panther-unique



    def calc_src12_bit_widths(self, model):
        # Note Panther will overload this to reflect its different architecture and use 8, 15
        # EFR32 90nm parts (Dumbo, Jumbo, Nerio, Nixi) use different values
        model.vars.src1_bit_width.value = 8
        model.vars.src2_bit_width.value = 15

    def calc_ch_filt_bw_available(self, model):
        # Note Panther will overload this to reflect its different architecture.
        model.vars.ch_filt_bw_available = [0.263]

    def calc_src1_range_available(self, model):
        # EFR32 90nm parts (Dumbo, Jumbo, Nerio, Nixi)
        # Note Panther will overload this to reflect its different architecture.

        # optional input, 125 by default. Some PHYs may increase this so calculated value always matches RAIL
        model.vars.src1_range_available_minimum.value = 125
        src1_range_available_minimum = model.vars.src1_range_available_minimum.value

        model.vars.src1_range_available = xrange(src1_range_available_minimum, 156, 1)


    def calc_sqithresh_reg(self, model):
        """set sqithresh register - intermediate variable used to override as advanced input

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        # Nixi would write this to 200...
        #self._reg_write(model.vars.MODEM_CTRL2_SQITHRESH, model.vars.sqi_threshold.value)
        pass

    def calc_viterbi_demod_expect_patt_value(self, model):

        flag_using_Viterbi_demod = (model.vars.MODEM_VITERBIDEMOD_VTDEMODEN.value == 1)
        flag_using_BLELR = (model.vars.MODEM_LONGRANGE_LRBLE.value == 1)
        syncword0 = model.vars.syncword_0.value
        preamble_pattern = model.vars.preamble_pattern.value

        if flag_using_Viterbi_demod and not flag_using_BLELR:
            # Last bit of preamble followed by all but one bit of syncword
            viterbi_demod_expect_patt = (syncword0 >> 1) | ((preamble_pattern & 1) << 31)
            model.vars.viterbi_demod_expect_patt.value = viterbi_demod_expect_patt
        else:
            # set to default reset value
            model.vars.viterbi_demod_expect_patt.value = long(0x123556B7)


    def calc_viterbi_demod_expect_patt_reg(self, model):

        viterbi_demod_expect_patt = model.vars.viterbi_demod_expect_patt.value


        self._reg_write(model.vars.MODEM_VTCORRCFG0_EXPECTPATT, viterbi_demod_expect_patt)

    def calc_viterbi_demod_expect_patt_head_tail_value(self, model):

        flag_using_Viterbi_demod = (model.vars.MODEM_VITERBIDEMOD_VTDEMODEN.value == 1)
        flag_using_BLELR = (model.vars.MODEM_LONGRANGE_LRBLE.value == 1)
        syncword0 = model.vars.syncword_0.value
        
        if flag_using_Viterbi_demod and not flag_using_BLELR:
            # Head and tail bits of syncword
            viterbi_demod_expect_patt_head_tail = int((((syncword0 >> 32) & 1)<<2)  | ((syncword0 & 1)<<1))
            model.vars.viterbi_demod_expect_patt_head_tail.value = viterbi_demod_expect_patt_head_tail
        else:
            # set to default reset value
            model.vars.viterbi_demod_expect_patt_head_tail.value = 5


    def calc_viterbi_demod_expect_patt_head_tail_reg(self, model):

        viterbi_demod_expect_patt_head_tail = model.vars.viterbi_demod_expect_patt_head_tail.value


        self._reg_write(model.vars.MODEM_VTCORRCFG1_EXPECTHT, viterbi_demod_expect_patt_head_tail)

    def calc_viterbidemod_disdemodof_viterbi_demod_disable_overflow_detect_value(self, model):

        flag_using_Viterbi_demod = (model.vars.MODEM_VITERBIDEMOD_VTDEMODEN.value == 1)

        if flag_using_Viterbi_demod:
            model.vars.viterbidemod_disdemodof_viterbi_demod_disable_overflow_detect.value = 1
        else:
            # set to default reset value
            model.vars.viterbidemod_disdemodof_viterbi_demod_disable_overflow_detect.value = 0

    def calc_viterbidemod_disdemodof_viterbi_demod_disable_overflow_detect_reg(self, model):
        viterbidemod_disdemodof_viterbi_demod_disable_overflow_detect = model.vars.viterbidemod_disdemodof_viterbi_demod_disable_overflow_detect.value

        self._reg_write(model.vars.MODEM_VITERBIDEMOD_DISDEMODOF, viterbidemod_disdemodof_viterbi_demod_disable_overflow_detect)

    def calc_dec0_values_available(self, model):
        # Series 2 parts (Panther, Lynx, Ocelot) add optional inputs to disallow decimation by 3 or 8


        # Default to allow (the optional input)
        model.vars.input_decimation_filter_allow_dec3.value = 1
        model.vars.input_decimation_filter_allow_dec8.value = 1

        # Unless specified otherwise by optional inputs
        model.vars.input_decimation_filter_allow_dec3.value = model.vars.input_decimation_filter_allow_dec3.value
        model.vars.input_decimation_filter_allow_dec8.value = model.vars.input_decimation_filter_allow_dec8.value
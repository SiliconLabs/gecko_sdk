from pyradioconfig.parts.bobcat.calculators.calc_demodulator import Calc_Demodulator_Bobcat
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from math import *
from enum import Enum

class CalcDemodulatorRainier(Calc_Demodulator_Bobcat):

    # override inhereited variable defining threshold for _channel_filter_clocks_valid
    chf_required_clks_per_sample = 3  # fixed in PGVIPER-248

    def buildVariables(self, model):
        """Populates a list of needed variables for this calculator
        Args:
           model (ModelRoot) : Builds the variables specific to this calculator
        """
        super().buildVariables(model)

        self._addModelActual(model, 'adc_rate_mode', Enum, ModelVariableFormat.DECIMAL)
        model.vars.adc_rate_mode_actual.var_enum = model.vars.adc_rate_mode.var_enum

    def _add_demod_select_variable(self, model):

        #Add ENHANCED_DSSS demod
        model.vars.demod_select.var_enum = CreateModelVariableEnum(
            enum_name='DemodSelectEnum',
            enum_desc='Demod Selection',
            member_data=[
                ['LEGACY', 0, 'Legacy Demod'],
                ['COHERENT', 1, 'Coherent Demod'],
                ['TRECS_VITERBI', 2, 'TRecS + Viterbi Demod'],
                ['TRECS_SLICER', 3, 'TRecS + HD Demod'],
                ['BCR', 4, 'PRO2 BCR Demod'],
                ['LONGRANGE', 5, 'BLE Long Range Demod'],
                ['ENHANCED_DSSS', 6, 'Enhanced OQPSK+DSSS Demod'],
                ['BTC', 7, 'Bluetooth Classic Demod'],
                ['HDT', 8, 'BLE Higher Data Rate Demod']
            ])

    def get_limits(self, demod_select, withremod, relaxsrc2, model):

        if demod_select == model.vars.demod_select.var_enum.ENHANCED_DSSS or \
                demod_select == model.vars.demod_select.var_enum.BTC or \
                demod_select == model.vars.demod_select.var_enum.HDT:
            osr_list = [4]
            min_osr = 4
            max_osr = 4
            min_src2 = 0.8
            max_src2 = 1.2
            min_dec2 = 1
            max_dec2 = 1
            min_bwsel = 0.15
            target_bwsel = 0.4
            max_bwsel = 0.4
            min_chfilt_osr = None
            max_chfilt_osr = None

        else:
            min_bwsel, max_bwsel, min_chfilt_osr, max_chfilt_osr, min_src2, max_src2, min_dec2, max_dec2, min_osr, max_osr, target_bwsel, osr_list = \
                super().get_limits(demod_select, withremod, relaxsrc2, model)

        # save to use in other functions
        model.vars.min_bwsel.value = min_bwsel  # min value for normalized channel filter bandwidth
        model.vars.max_bwsel.value = max_bwsel  # max value for normalized channel filter bandwidth
        model.vars.min_src2.value = min_src2  # min value for SRC2
        model.vars.max_src2.value = max_src2  # max value for SRC2
        model.vars.max_dec2.value = max_dec2
        model.vars.min_dec2.value = min_dec2

        return min_bwsel, max_bwsel, min_chfilt_osr, max_chfilt_osr, min_src2, max_src2, min_dec2, max_dec2, min_osr, max_osr, target_bwsel, osr_list

    def calc_syncacqwin_actual(self, model):
        """ set syc word acquisition window for TRECS basd on register value

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """
        model.vars.syncacqwin_actual.value = (model.vars.MODEM_REALTIMCFE_SYNCACQWIN.value + 1)

    #
    def calc_syncbits_actual(self, model):
        syncword_bits = model.vars.syncword_length.value ##fix me
        model.vars.syncbits_actual.value = syncword_bits

    def calc_target_demod_bandwidth(self, model):

        demod_select = model.vars.demod_select.value
        baudrate = model.vars.baudrate.value

        if demod_select == model.vars.demod_select.var_enum.ENHANCED_DSSS:

            model.vars.demod_bandwidth_hz.value = int(baudrate * 0.9)
        else:
            super().calc_target_demod_bandwidth(model)

    def calc_lock_bandwidth(self, model, softmodem_narrowing=False):

        demod_select = model.vars.demod_select.value
        bw_demod = model.vars.demod_bandwidth_hz.value

        if demod_select == model.vars.demod_select.var_enum.ENHANCED_DSSS:

            model.vars.lock_bandwidth_hz.value = int(bw_demod)
        else:
            super().calc_lock_bandwidth(model)

    def return_osr_dec0_dec1(self, model, demod_select, withremod=False, relaxsrc2=False, quitatfirstvalid=True):

        # Load model variables into local variables
        bandwidth = model.vars.bandwidth_hz.value  # from calc_target_bandwidth
        adc_freq = model.vars.adc_freq_actual.value
        baudrate = model.vars.baudrate.value  # We don't know the actual bandrate yet
        modtype = model.vars.modulation_type.value
        mi = model.vars.modulation_index.value
        if_frequency_hz = model.vars.if_frequency_hz.value
        etsi_cat1_compatability = model.vars.etsi_cat1_compatible.value
        bw_var = model.vars.bandwidth_tol.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        # set limits based on selected demod
        [min_bwsel, max_bwsel, min_chfilt_osr, max_chfilt_osr, min_src2, max_src2, min_dec2, \
            max_dec2, min_osr, max_osr, target_bwsel, osr_list] = self.get_limits(demod_select, withremod, relaxsrc2, model)

        # read from advanced variable
        if (model.vars.target_bwsel._value_forced != None):
            target_bwsel = model.vars.target_bwsel._value_forced

        # initialize output
        best_bwsel_error = 1e9
        best_osr = 0
        best_dec0 = 0
        best_dec1 = 0

        # Setup for osr loop
        # osr_list is a prioritized list, where first value with valid config will be returned
        if (model.vars.target_osr._value_forced != None):
            osr_forced = model.vars.target_osr._value_forced
            osr_list = [osr_forced]

        # Setup for dec0 loop
        # dec0_list is a prioritized list, where ties in best bwsel go to earlier value in list
        dec0_list = self.return_dec0_list(if_frequency_hz,adc_freq)

        # Search values of osr, dec0, dec1 to find solution
        # Exit on first osr with valid dec0 and dec1
        for osr in osr_list:
            for dec0 in dec0_list:

                # define integer range for dec1
                min_dec1 = int(max(1, ceil(float(adc_freq) * min_bwsel / (8 * dec0 * bandwidth*(1+bw_var)))))
                max_dec1 = int(min(11500, floor(float(adc_freq) * max_bwsel / (8 * dec0 * bandwidth*(1-bw_var)))))
                if min_dec1 <= max_dec1:
                    # Order list from highest to lowest, bwsel from highest to lowest
                    dec1_list = range(max_dec1,min_dec1-1,-1)
                else:
                    # No solution
                    continue

                for dec1 in dec1_list:

                    # check configuration does trigger IPMCUSRW-876 channel filter issue when input sample rate
                    # is too fast relative to the processing clock cycles needed
                    # if not self._channel_filter_clocks_valid(model, dec0, dec1):
                    #     continue

                    # calculated dec2 range
                    if demod_select == model.vars.demod_select.var_enum.BCR:
                        calc_min_dec2 = 1
                        calc_max_dec2 = 1
                        chfilt_osr_actual = float(adc_freq) / (8 * dec0 * dec1 * baudrate)

                        if (modtype == model.vars.modulation_type.var_enum.OOK) or \
                                (modtype == model.vars.modulation_type.var_enum.ASK):
                            if chfilt_osr_actual < osr or chfilt_osr_actual > osr + 1.0:
                                continue
                        else:
                            if (chfilt_osr_actual < min_chfilt_osr) or (chfilt_osr_actual > max_chfilt_osr):
                                # not a solution, next value of dec1 loop
                                continue

                    elif demod_select == model.vars.demod_select.var_enum.TRECS_SLICER or \
                         demod_select == model.vars.demod_select.var_enum.TRECS_VITERBI:
                        # forcing integer osr condition, which applies to TRECS
                        # check for TRECS minimum clk cycle requirements
                        calc_min_dec2 = ceil(min_src2 * float(adc_freq) / (osr * dec0 * dec1 * 8 * baudrate))
                        calc_max_dec2 = floor(max_src2 * float(adc_freq) / (osr * dec0 * dec1 * 8 * baudrate))

                        # trecs_src_interp_okay = self._check_trecs_required_clk_cycles(adc_freq, baudrate, osr, dec0,
                        #                                                              dec1, xtal_frequency_hz, relaxsrc2, model)
                        # if not trecs_src_interp_okay:
                        #     # not a solution due to trecs clocking constraints, continue
                        #     continue
                    else:
                        # forcing integer osr condition, which applies to LEGACY, COHERENT
                        calc_min_dec2 = ceil(min_src2 * float(adc_freq) / (osr * dec0 * dec1 * 8 * baudrate))
                        calc_max_dec2 = floor(max_src2 * float(adc_freq) / (osr * dec0 * dec1 * 8 * baudrate))

                    if (calc_min_dec2 <= calc_max_dec2) and (calc_min_dec2 <= max_dec2) and \
                            (calc_max_dec2 >= min_dec2):

                        # calculation of dec1 has constrained bwsel to range bwsel_min to bwsel_max
                        bwsel = bandwidth * (8 * dec0 * dec1) / float(adc_freq)

                        bwsel_error = abs(bwsel - target_bwsel)

                        # Select largest bwsel as best result
                        if (bwsel_error < best_bwsel_error):
                            best_bwsel_error = bwsel_error
                            best_osr = osr
                            best_dec0 = dec0
                            best_dec1 = dec1
                            best_bwsel = bwsel

            if best_osr > 0 and quitatfirstvalid:

                # break out of the osr loop on first successful configuration
                break

        return best_osr, best_dec0, best_dec1, min_osr, max_osr

    def calc_chmutetimer(self, model):
        #Set to POR default (only used in select PHYs for now)
        self._reg_write(model.vars.MODEM_SRCCHF_CHMUTETIMER, default=True)
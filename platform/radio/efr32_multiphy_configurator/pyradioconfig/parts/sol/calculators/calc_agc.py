import math
from pyradioconfig.parts.ocelot.calculators.calc_agc import CALC_AGC_ocelot


class Calc_AGC_Sol(CALC_AGC_ocelot):

    def calc_frzpkden_reg(self, model):

        # Enable peak detector freeze
        self._reg_write(model.vars.AGC_CTRL4_FRZPKDEN, 1)

    def calc_settlingindctrl_reg(self, model):

        # For now, always disable
        settlingindctrl_en = 0
        delayperiod = 0

        # Write the registers
        self._reg_write(model.vars.AGC_SETTLINGINDCTRL_EN, settlingindctrl_en)
        self._reg_write(model.vars.AGC_SETTLINGINDCTRL_POSTHD, 1)
        self._reg_write(model.vars.AGC_SETTLINGINDCTRL_NEGTHD, 1)
        self._reg_write(model.vars.AGC_SETTLINGINDPER_SETTLEDPERIOD, 200)  # fast loop
        self._reg_write(model.vars.AGC_SETTLINGINDPER_DELAYPERIOD, delayperiod)  # fast loop

    def calc_lnamixrfatt_reg(self, model):

        # Load in model variables
        rf_band = model.vars.rf_band.value

        # Calculate the LNAMIXRFATT values based on band
        if rf_band == model.vars.rf_band.var_enum.BAND_915:
            lnamixrfatt = [0, 25, 58, 101, 150, 218, 448, 698, 982, 1456, 1970, 2538, 3322, 4350, 5842, 7514,
                           9882, 12664, 16383, 14042, 14800, 16383, 16383]
            pnindexmax = 19
        elif rf_band == model.vars.rf_band.var_enum.BAND_868:
            lnamixrfatt = [0, 63, 141, 238, 502, 940, 1269, 1942, 2526, 3484, 4547, 6035, 7678, 9973, 12989, 16383,
                           5630, 7160, 9180, 11700, 14800, 16383, 16383]
            pnindexmax = 16
        elif rf_band == model.vars.rf_band.var_enum.BAND_490:
            lnamixrfatt = [0, 20, 45, 78, 125, 175, 246, 477, 726, 1012, 1471, 1983, 2703, 3485, 4543, 5835,
                           7582, 9707, 12672, 16359, 16383, 16383, 16383]
            pnindexmax = 20
        elif rf_band == model.vars.rf_band.var_enum.BAND_434:
            lnamixrfatt = [0, 15, 44, 77, 117, 172, 239, 468, 725, 998, 1469, 1983, 2551, 3491, 4525, 5849,
                           7623, 9910, 12750, 16383, 14800, 16383, 16383]
            pnindexmax = 20
        elif rf_band == model.vars.rf_band.var_enum.BAND_315:
            lnamixrfatt = [0, 12, 29, 52, 78, 111, 156, 207, 420, 502, 750, 1187, 1502, 2012, 2720, 3521,
                           4557, 5870, 7623, 9711, 12719, 16383, 16383]
            pnindexmax = 22
        elif rf_band == model.vars.rf_band.var_enum.BAND_169:
            lnamixrfatt = [0, 13, 36, 63, 99, 141, 199, 412, 502, 757, 1190, 1507, 2029, 2743, 3541, 4601,
                           6055, 7811, 9966, 12964, 16383, 16383, 16383]
            pnindexmax = 21

        else:
            lnamixrfatt = [0, 20, 48, 76, 116, 164, 228, 436, 668, 924, 1210, 1530, 2030, 2720, 3480, 4350,
                           5630, 7160, 9180, 11700, 14800, 16383, 16383]
            pnindexmax = 17

        # Write registers
        self._reg_write(model.vars.AGC_PNRFATT0_LNAMIXRFATT1, lnamixrfatt[0])
        self._reg_write(model.vars.AGC_PNRFATT0_LNAMIXRFATT2, lnamixrfatt[1])
        self._reg_write(model.vars.AGC_PNRFATT1_LNAMIXRFATT3, lnamixrfatt[2])
        self._reg_write(model.vars.AGC_PNRFATT1_LNAMIXRFATT4, lnamixrfatt[3])
        self._reg_write(model.vars.AGC_PNRFATT2_LNAMIXRFATT5, lnamixrfatt[4])
        self._reg_write(model.vars.AGC_PNRFATT2_LNAMIXRFATT6, lnamixrfatt[5])
        self._reg_write(model.vars.AGC_PNRFATT3_LNAMIXRFATT7, lnamixrfatt[6])
        self._reg_write(model.vars.AGC_PNRFATT3_LNAMIXRFATT8, lnamixrfatt[7])
        self._reg_write(model.vars.AGC_PNRFATT4_LNAMIXRFATT9, lnamixrfatt[8])
        self._reg_write(model.vars.AGC_PNRFATT4_LNAMIXRFATT10, lnamixrfatt[9])
        self._reg_write(model.vars.AGC_PNRFATT5_LNAMIXRFATT11, lnamixrfatt[10])
        self._reg_write(model.vars.AGC_PNRFATT5_LNAMIXRFATT12, lnamixrfatt[11])
        self._reg_write(model.vars.AGC_PNRFATT6_LNAMIXRFATT13, lnamixrfatt[12])
        self._reg_write(model.vars.AGC_PNRFATT6_LNAMIXRFATT14, lnamixrfatt[13])
        self._reg_write(model.vars.AGC_PNRFATT7_LNAMIXRFATT15, lnamixrfatt[14])
        self._reg_write(model.vars.AGC_PNRFATT7_LNAMIXRFATT16, lnamixrfatt[15])
        self._reg_write(model.vars.AGC_PNRFATT8_LNAMIXRFATT17, lnamixrfatt[16])
        self._reg_write(model.vars.AGC_PNRFATT8_LNAMIXRFATT18, lnamixrfatt[17])
        self._reg_write(model.vars.AGC_PNRFATT9_LNAMIXRFATT19, lnamixrfatt[18])
        self._reg_write(model.vars.AGC_PNRFATT9_LNAMIXRFATT20, lnamixrfatt[19])
        self._reg_write(model.vars.AGC_PNRFATT10_LNAMIXRFATT21, lnamixrfatt[20])
        self._reg_write(model.vars.AGC_PNRFATT10_LNAMIXRFATT22, lnamixrfatt[21])
        self._reg_write(model.vars.AGC_PNRFATT11_LNAMIXRFATT23, lnamixrfatt[22])
        self._reg_write(model.vars.AGC_GAINSTEPLIM1_PNINDEXMAX, pnindexmax)

    def calc_rssifilten_reg(self, model):
        # This method calculates the FEFILT1 RSSIFILTEN reg depending on demod

        # Read in model vars
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            rssifilten = 1
        else:
            rssifilten = 0

        # Write the reg
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTEN, rssifilten)

    def calc_fefilt1_rssifilt(self, model):

        # Read in model vars
        fefilt1_rssifilten = model.vars.FEFILT1_RSSIFILT_RSSIFILTEN.value

        if fefilt1_rssifilten == 1:
            rssifilt_coeffs = [1, 1, 2, 1, 1, 0, 0, 0]
            rssifiltgain = 2
            rssifiltdec = 1
            do_not_care = False
        else:
            rssifilt_coeffs = [0] * 8
            rssifiltgain = 0
            rssifiltdec = 0
            do_not_care = True

        # Write the regs
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTCOEF0, rssifilt_coeffs[0], do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTCOEF1, rssifilt_coeffs[1], do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTCOEF2, rssifilt_coeffs[2], do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTCOEF3, rssifilt_coeffs[3], do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTCOEF4, rssifilt_coeffs[4], do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTCOEF5, rssifilt_coeffs[5], do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTCOEF6, rssifilt_coeffs[6], do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTCOEF7, rssifilt_coeffs[7], do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTGAIN, rssifiltgain, do_not_care=do_not_care)
        self._reg_write(model.vars.FEFILT1_RSSIFILT_RSSIFILTDEC, rssifiltdec, do_not_care=do_not_care)

    def calc_agc_colldetctrl_regs(self, model):

        # Read in model vars
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            ofdm_option = model.vars.ofdm_option.value

            do_not_care = False
            macompensel = 0  # PRE_DET
            ovrthdsel = 1
            rssiinsel = 0  # MAFILTER
            inputsel = 2  # SOFTM
            if ofdm_option == model.vars.ofdm_option.var_enum.OPT1_OFDM_BW_1p2MHz:
                matap = 3  # 16 taps
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT2_OFDM_BW_0p8MHz:
                matap = 2  # 8 taps
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT3_OFDM_BW_0p4MHz:
                matap = 1  # 4 taps
            else:
                matap = 0  # 2 taps

        else:
            do_not_care = True
            matap = 0
            macompensel = 0
            ovrthdsel = 0
            rssiinsel = 0
            inputsel = 0

        # Write the regs
        self._reg_write(model.vars.AGC_COLLDETCTRL_MATAP, matap, do_not_care=do_not_care)
        self._reg_write(model.vars.AGC_COLLDETCTRL_MACOMPENSEL, macompensel, do_not_care=do_not_care)
        self._reg_write(model.vars.AGC_COLLDETCTRL_OVRTHDSEL, ovrthdsel, do_not_care=do_not_care)
        self._reg_write(model.vars.AGC_COLLDETCTRL_RSSIINSEL, rssiinsel, do_not_care=do_not_care)
        self._reg_write(model.vars.AGC_COLLDETCTRL_INPUTSEL, inputsel, do_not_care=do_not_care)

    def calc_cfloopdel_reg(self, model):

        """Calculate AGC settling delay which is basically the group delay of decimation and
        channel filters through the datapath plus processing delays.

        Calculations are in channel filter clock cycles to directly program into CFLOOPDEL

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """
        # Read in model variables
        antdivmode = model.vars.antdivmode.value
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM \
                and antdivmode != model.vars.antdivmode.var_enum.DISABLE\
                and antdivmode != model.vars.antdivmode.var_enum.ANTENNA1:
            # In OFDM antenna diversity, we do not need the measurement of the power after channel filtering.
            # The delay before the measurement (CFLOOPDEL) is cut to the minimum to avoid delay in the SFM.
            cfloopdel = 1
        else:
            agc_delay = model.vars.agc_settling_delay.value
            cfloopdel = min(127, agc_delay)

        self._reg_write(model.vars.AGC_GAINSTEPLIM0_CFLOOPDEL, int(math.ceil(cfloopdel)))

    def calc_antdiv_gainmode_reg(self, model):
        antdivmode = model.vars.antdivmode.value
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        conc_ofdm_option = model.vars.conc_ofdm_option.value

        if (antdivmode == model.vars.antdivmode.var_enum.DISABLE or
                antdivmode == model.vars.antdivmode.var_enum.ANTENNA1)\
                or (softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM
                    and conc_ofdm_option == model.vars.conc_ofdm_option.var_enum.NONE):
            # In OFDM, not concurrent antenna diversity:
            # Never use single_packet mode. Gain recover is performed in FW.
            # See https://jira.silabs.com/browse/MCUW_RADIO_CFG-2232
            gainmode = 0
        else:
            # In FSK or concurrent antenna diversity:
            # always enable gain restore mode - clear stored gain from last packet when RX is turned off.
            gainmode = 1

        self._reg_write(model.vars.AGC_ANTDIV_GAINMODE, gainmode)

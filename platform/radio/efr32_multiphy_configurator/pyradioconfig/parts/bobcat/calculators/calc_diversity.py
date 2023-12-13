from pyradioconfig.parts.ocelot.calculators.calc_diversity import CALC_Diversity_Ocelot
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
import math
from enum import Enum

class Calc_Diversity_Bobcat(CALC_Diversity_Ocelot):

    def buildVariables(self, model):
        """Populates a list of needed variables for this calculator
        Args:
            model (ModelRoot) : Builds the variables specific to this calculator
        """

        # Build variables from Ocelot
        calc_diversity_ocelot_obj = CALC_Diversity_Ocelot()
        calc_diversity_ocelot_obj.buildVariables(model)

        # Internal variables
        self._addModelVariable(model, 'antdiv_switch_delay_us', float, ModelVariableFormat.DECIMAL, desc='Delay correlation samples after antenna switch.')
        self._addModelVariable(model, 'antdiv_switch_skip_us', float, ModelVariableFormat.DECIMAL, desc='Skip correlation samples after antenna switch.')
        self._addModelVariable(model, 'antdiv_freq_offset_bias', int, ModelVariableFormat.DECIMAL, desc='Antenna diversity frequency offset bias.')
        self._addModelVariable(model, 'antdiv_enable_parallel_correlation', bool, ModelVariableFormat.ASCII, desc='Antenna diversity enable parallel correlation')
        self._addModelVariable(model, 'antdiv_enable_dual_window', bool, ModelVariableFormat.ASCII, desc='Enable dual correlation window')
        self._addModelVariable(model, 'antdiv_adpcsigampthr', int, ModelVariableFormat.DECIMAL, desc='Signal Amplitude Threshold')
        self._addModelVariable(model, 'antdiv_adpcwndsize', int, ModelVariableFormat.DECIMAL, desc='Antenna Diversity Correlation window size in chips')
        self._addModelVariable(model, 'antdiv_adbbss_refamp', int, ModelVariableFormat.DECIMAL, desc='Antenna Diversity ADBBSS LUT reference amplitude (coherent only)')
    pass

    def calc_diversity_default_configs(self, model):
        demod_sel = model.vars.demod_select.value

        # : Assign default values to antenna diversity profile inputs on non-diversity phys
        model.vars.antdiv_enable_parallel_correlation.value = False
        model.vars.antdiv_switch_delay_us.value = 0.0
        model.vars.antdiv_switch_skip_us.value = 0.0
        model.vars.antdiv_adpcwndsize.value = 32
        model.vars.antdiv_adpcsigampthr.value = 0
        model.vars.antdiv_adbbss_refamp.value = 0

        # : Disable freq offset bias for coherent mode
        if demod_sel == model.vars.demod_select.var_enum.COHERENT:
            freq_offset_bias = 0
        else:
            freq_offset_bias = -16
        model.vars.antdiv_freq_offset_bias.value = freq_offset_bias

    def calc_diversity_adpcen(self, model):
        enable_parallel_correlation = model.vars.antdiv_enable_parallel_correlation.value

        if enable_parallel_correlation:
            adpcen = 1
        else:
            adpcen = 0

        self._reg_write(model.vars.MODEM_ADPC1_ADPCEN, adpcen)

    def calc_diveristy_adpc_windowsize(self, model):
        adpcwndsizechip = model.vars.antdiv_adpcwndsize.value
        self._reg_write(model.vars.MODEM_ADPC1_ADPCWNDSIZECHIP, adpcwndsizechip)

    def calc_diversity_adpc_windowcnt(self, model):
        adpcen = model.vars.MODEM_ADPC1_ADPCEN.value

        if adpcen: # : enable dual window if paralle correlation is enabled
            adpcwndcnt = 2
        else:
            adpcwndcnt = 1

        self._reg_write(model.vars.MODEM_ADPC1_ADPCWNDCNT, adpcwndcnt)

    def calc_diversity_adpc_timingbauds(self, model):
        adpcwndsizechip = model.vars.MODEM_ADPC1_ADPCWNDSIZECHIP.value
        adpcwndcnt = model.vars.MODEM_ADPC1_ADPCWNDCNT.value

        # : Calculate number of bauds (window size in chips times total number of windows)
        adpctimingbauds = adpcwndsizechip * adpcwndcnt

        self._reg_write(model.vars.MODEM_ADPC1_ADPCTIMINGBAUDS, adpctimingbauds)

    def calc_diversity_adpc_corroffsetchip(self, model):
        adpcwndsizechip = model.vars.MODEM_ADPC1_ADPCWNDSIZECHIP.value
        adpcwndcnt = model.vars.MODEM_ADPC1_ADPCWNDCNT.value
        adpctimingbauds = model.vars.MODEM_ADPC1_ADPCTIMINGBAUDS.value

        adpccorroffsetchip = adpcwndsizechip * adpcwndcnt - adpctimingbauds

        self._reg_write(model.vars.MODEM_ADPC1_ADPCCORROFFSETCHIP, adpccorroffsetchip)

    def calc_diversity_adpc_corrsamples(self, model):
        adpcen = model.vars.MODEM_ADPC1_ADPCEN.value
        oversampling_rate_actual = model.vars.oversampling_rate_actual.value
        adpctimingbauds = model.vars.MODEM_ADPC1_ADPCTIMINGBAUDS.value

        if adpcen == 1:
            adpccorrsamples = adpctimingbauds * oversampling_rate_actual
        else:
            adpccorrsamples = 160

        adpccorrsamples_int = int(round(adpccorrsamples))

        self._reg_write(model.vars.MODEM_ADPC2_ADPCCORRSAMPLES, adpccorrsamples_int)

    def calc_diversity_adpc_buffersize(self, model):
        adpcen = model.vars.MODEM_ADPC1_ADPCEN.value
        delay_us = model.vars.antdiv_switch_delay_us.value
        skip_us = model.vars.antdiv_switch_skip_us.value
        oversampling_rate_actual = model.vars.oversampling_rate_actual.value
        baudrate_actual = model.vars.rx_baud_rate_actual.value
        adpcwndsizechip = model.vars.MODEM_ADPC1_ADPCWNDSIZECHIP.value

        # : calculate chip period in us
        chip_period_us = 1.0 / baudrate_actual * 1e6  # chip_us

        # : Convert delay/skip in us to number of chips
        delay_chips = delay_us / chip_period_us
        skip_chips = skip_us / chip_period_us

        # : calculate buffer size and write size
        adpcantsampbuf = delay_chips * oversampling_rate_actual
        adpcantsampwrite = adpcantsampbuf + skip_chips * oversampling_rate_actual

        # : calculate how long to stay on one antenna in number of adc samples
        adpcantsampswitch = (adpcwndsizechip + skip_chips) * oversampling_rate_actual

        # : convert to int
        adpcantsampbuf_int = int(round(adpcantsampbuf))
        adpcantsampwrite_int = int(round(adpcantsampwrite))
        adpcantsampswitch_int = int(round(adpcantsampswitch))

        if adpcen == 1:
            self._reg_write(model.vars.MODEM_ADPC8_ADPCANTSAMPBUF, adpcantsampbuf_int)
            self._reg_write(model.vars.MODEM_ADPC8_ADPCANTSAMPWRITE, adpcantsampwrite_int)
            self._reg_write(model.vars.MODEM_ADPC8_ADPCANTSAMPSWITCH, adpcantsampswitch_int)
        else:
            self._reg_write(model.vars.MODEM_ADPC8_ADPCANTSAMPBUF, 1)
            self._reg_write(model.vars.MODEM_ADPC8_ADPCANTSAMPWRITE, 0x1F)
            self._reg_write(model.vars.MODEM_ADPC8_ADPCANTSAMPSWITCH, 0xBE)

    def calc_diversity_adctrl1(self, model):
        demod_sel = model.vars.demod_select.value
        adpcen = model.vars.MODEM_ADPC1_ADPCEN.value
        frequency_offset_bias = model.vars.antdiv_freq_offset_bias.value
        adbacorrthr = model.vars.MODEM_ADQUAL6_ADBACORRTHR.value
        adbacorrdiff = model.vars.MODEM_ADQUAL6_ADBACORRDIFF.value

        # : Enable or disable correlation threshold decision
        adbacorrthr_dis_val = 1 if adbacorrthr == 0 else 0


        # : Enable or disable correlation difference decision
        adbacorrdiff_dis_val = 1 if adbacorrdiff == 0 else 0

        # : Calculate frequency offset bias by converting to two's complement
        frequency_offset_bias_val = frequency_offset_bias + 32 if frequency_offset_bias < 0 else frequency_offset_bias

        # : calculate
        if demod_sel == model.vars.demod_select.var_enum.COHERENT:
            adbarssithr_dis_val = 1
        else:
            adbarssithr_dis_val = 0

        # : Register field definitions for adctrl1 does not exists in cmsis.
        # : Manually define offsets for each field within adctrl1 register
        field_offsets_vals = {
            'QUAL_UPDATE_TDS'   : [0, 1],
            'FSM_RESET'         : [1, 0],
            'DEMODRXREQ_RST'    : [2, 0],
            'DEMODRXREQ_SET'    : [3, 0],
            'DEMODRXREQ_CLR'    : [4, 0],
            'DEMODRXREQ_FORCE'  : [5, 0],
            'DEMODRXREQ_VAL'    : [6, 0],
            'RSSIVALID_SW'      : [7, 0],
            'IT_ENTER'          : [8, 0],
            'IT_LEAVE'          : [9, 0],
            'RSVD'              : [10, 0],
            'PWR_SWFSM'         : [11, 0],
            'PWR_SWO'           : [12, 0],
            'QUAL_UPD_NOTIMDET' : [13, 0],
            'QUAL_CLR_NOTIMDET' : [14, 0],
            'BA_OPT'            : [15, 0],
            'BA_CORR_HI_DIS'    : [16, adbacorrthr_dis_val],
            'BA_CORR_EQ_DIS'    : [17, adbacorrdiff_dis_val],
            'BA_RSSI_HI_DIS'    : [18, adbarssithr_dis_val],
            'BA_RSSI_EQ_DIS'    : [19, 1],
            'BA_GAIN_LO_DIS'    : [20, 0],
            'FGR_HI_CORR_DIS'   : [21, 0],
            'FGR_GR_RSSI_DIS'   : [22, 0],
            'FGR_GR_AGC_DIS'    : [23, 0],
            'FGR_GR_GAIN_DIS'   : [24, 0],
            'FGR_GR_DIS'        : [25, 0],
            'FREQ_BIAS'         : [26, frequency_offset_bias_val],
        }

        # : calculate ctrl1 register by applying offsets to each field
        adctrl1 = 0
        if adpcen == 1:
            adctrl1 = 0
            for field_name in field_offsets_vals:
                adctrl1 += field_offsets_vals[field_name][1] * pow(2, field_offsets_vals[field_name][0])

        self._reg_write(model.vars.MODEM_ADCTRL1_ADCTRL1, adctrl1)

    def calc_diversity_adctrl2(self, model):
        demod_sel = model.vars.demod_select.value
        adpcen = model.vars.MODEM_ADPC1_ADPCEN.value

        if demod_sel == model.vars.demod_select.var_enum.COHERENT:
            wnd_amp_rst = 0
            wnd_rst_amp = 1
        else:
            wnd_amp_rst = 1
            wnd_rst_amp = 0


        # : Register field definitions for adctrl2 does not exists in cmsis.
        # : Manually define offsets for each field within adctrl2 register
        field_offsets_vals = {
            'PCORR_EN_BC' : [0,  1],
            'ANTSEL_DELAY': [11, 1],
            'BA_AMP_DIS'  : [19, 0],
            'WND_AMP_RST' : [20, wnd_amp_rst],
            'TIM_AMP_THR' : [21, 0],
            'FOC_MODE0': [23, 0],
            'FOC_MODE1': [24, 0],
            'WND_RST_AMP' : [25, wnd_rst_amp],
            'WND_RST_BBSS': [27, 0],
        }

        # : calculate ctrl2 register by applying offsets to each field
        if adpcen == 1:
            adctrl2 = 0
            for field_name in field_offsets_vals:
                adctrl2 += field_offsets_vals[field_name][1] * pow(2, field_offsets_vals[field_name][0])
        else:
            adctrl2 = 129

        self._reg_write(model.vars.MODEM_ADCTRL2_ADCTRL2, adctrl2)

    def calc_adpcsigampthr_reg(self, model):
        sigampthr_dec = model.vars.antdiv_adpcsigampthr.value

        # compress ampthr to adpcsigampthr (ampthr = [7:4] << [3:0])
        i = 0
        while i < 16:
            div = round(sigampthr_dec / float(pow(2, i)))
            if div < 16:
                break
            i += 1
        adpcsigampthr = div * 16 + i

        self._reg_write(model.vars.MODEM_ADPC2_ADPCSIGAMPTHR, adpcsigampthr)

    def calc_adprethresh_scale(self, model):
        adpcen = model.vars.MODEM_ADPC1_ADPCEN.value

        if adpcen:
            antdiv_adprethresh_scale = 0.2
        else:
            antdiv_adprethresh_scale = 0.0

        model.vars.antdiv_adprethresh_scale.value = antdiv_adprethresh_scale

    def adbbss_lut(self, refamp, nbitgain, index):
        sat_val = round(math.pow(2, nbitgain) - 1)
        if index == 0:
            int_val = sat_val
        else:
            int_val = round(1.0 * refamp / index * math.pow(2, nbitgain - 1))
            if int_val > sat_val:
                int_val = sat_val
        return int_val

    def calc_adpc_adbbss(self, model):
        demod_sel = model.vars.demod_select.value
        refamp = model.vars.antdiv_adbbss_refamp.value
        antdivmode = model.vars.antdivmode.value

        if demod_sel == model.vars.demod_select.var_enum.COHERENT and antdivmode != model.vars.antdivmode.var_enum.DISABLE:
            nbitgain = 5
            adbbss_lut = []
            for lut_idx in range(16):
                adbbss_lut.append(self.adbbss_lut(refamp, nbitgain, lut_idx))
        else:
            adbbss_lut = [31, 31, 31, 31, 31, 31, 31, 27, 24, 21, 19, 17, 16, 14, 13, 12]

        self._reg_write(model.vars.MODEM_ADPC4_ADBBSSAMPLUT0, adbbss_lut[0])
        self._reg_write(model.vars.MODEM_ADPC4_ADBBSSAMPLUT1, adbbss_lut[1])
        self._reg_write(model.vars.MODEM_ADPC4_ADBBSSAMPLUT2, adbbss_lut[2])
        self._reg_write(model.vars.MODEM_ADPC4_ADBBSSAMPLUT3, adbbss_lut[3])
        self._reg_write(model.vars.MODEM_ADPC5_ADBBSSAMPLUT4, adbbss_lut[4])
        self._reg_write(model.vars.MODEM_ADPC5_ADBBSSAMPLUT5, adbbss_lut[5])
        self._reg_write(model.vars.MODEM_ADPC5_ADBBSSAMPLUT6, adbbss_lut[6])
        self._reg_write(model.vars.MODEM_ADPC5_ADBBSSAMPLUT7, adbbss_lut[7])
        self._reg_write(model.vars.MODEM_ADPC6_ADBBSSAMPLUT8, adbbss_lut[8])
        self._reg_write(model.vars.MODEM_ADPC6_ADBBSSAMPLUT9, adbbss_lut[9])
        self._reg_write(model.vars.MODEM_ADPC6_ADBBSSAMPLUT10, adbbss_lut[10])
        self._reg_write(model.vars.MODEM_ADPC6_ADBBSSAMPLUT11, adbbss_lut[11])
        self._reg_write(model.vars.MODEM_ADPC7_ADBBSSAMPLUT12, adbbss_lut[12])
        self._reg_write(model.vars.MODEM_ADPC7_ADBBSSAMPLUT13, adbbss_lut[13])
        self._reg_write(model.vars.MODEM_ADPC7_ADBBSSAMPLUT14, adbbss_lut[14])
        self._reg_write(model.vars.MODEM_ADPC7_ADBBSSAMPLUT15, adbbss_lut[15])
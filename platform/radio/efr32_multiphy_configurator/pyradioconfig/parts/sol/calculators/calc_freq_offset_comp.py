from pyradioconfig.parts.ocelot.calculators.calc_freq_offset_comp import CALC_Freq_Offset_Comp_ocelot
from pyradioconfig.parts.sol.calculators.calc_utilities import Calc_Utilities_Sol

class Calc_Freq_Offset_Comp_Sol(CALC_Freq_Offset_Comp_ocelot):
    def calc_afc_scale_value(self, model):
        # Overriding this function due to variable name change

        # Load model values into local variables
        freqgain = model.vars.freq_gain_actual.value
        mod_format = model.vars.modulation_type.value
        mode = model.vars.frequency_comp_mode.value
        scale = model.vars.afc_step_scale.value
        remoden = model.vars.MODEM_PHDMODCTRL_REMODEN.value
        remodoutsel = model.vars.MODEM_PHDMODCTRL_REMODOUTSEL.value
        digmix_res = model.vars.digmix_res_actual.value
        synth_res = model.vars.synth_res_actual.value
        phscale = 2 ** model.vars.MODEM_TRECPMDET_PHSCALE.value
        mode_index = self.freq_comp_mode_index(model, mode)
        demod_sel = model.vars.demod_select.value
        digmixfb = Calc_Utilities_Sol().get_fefilt_actual(model, 'DIGMIXCTRL_DIGMIXFBENABLE')
        baudrate = model.vars.rx_baud_rate_actual.value
        osr = model.vars.oversampling_rate_actual.value
        afc_tx_adjust_enable = model.vars.afc_tx_adjust_enable.value
        afc_oneshot = model.vars.MODEM_AFC_AFCONESHOT.value
        freq_offset_hz = model.vars.freq_offset_hz.value
        baudrate = model.vars.baudrate.value
        modulation_index = model.vars.modulation_index.value

        if digmixfb:
            res = digmix_res
        else:
            res = synth_res

        # AFC to synth for Legacy
        if(demod_sel==model.vars.demod_select.var_enum.LEGACY):
            if mode_index >= 4 and freqgain > 0:
                if mod_format == model.vars.modulation_type.var_enum.FSK2 or \
                    mod_format == model.vars.modulation_type.var_enum.FSK4:
                    afcscale = baudrate * osr / ( 256 * freqgain * res)
                    afcscale_tx = baudrate * osr / ( 256 * freqgain * synth_res)
                else:
                    afcscale = baudrate * osr / ( 256 * res)
                    afcscale_tx = baudrate * osr / ( 256 * synth_res)
            else:
                afcscale = 0.0
                afcscale_tx = 0.0

        elif((demod_sel==model.vars.demod_select.var_enum.TRECS_VITERBI or
              demod_sel==model.vars.demod_select.var_enum.TRECS_SLICER) and
             model.vars.MODEM_VITERBIDEMOD_VITERBIKSI1.value != 0) or \
                demod_sel==model.vars.demod_select.var_enum.LONGRANGE or \
            (demod_sel==model.vars.demod_select.var_enum.SOFT_DEMOD and
             mod_format == model.vars.modulation_type.var_enum.FSK2):
            if remoden and remodoutsel == 1:
                afcscale = baudrate * osr * phscale / (256 * freqgain * res)
                afcscale_tx = baudrate * osr * phscale / (256 * freqgain * synth_res)
            elif (freq_offset_hz / baudrate) > 0.57 and modulation_index <= 0.5:
                afc_boost = baudrate / freq_offset_hz
                afcscale = afc_boost * baudrate * phscale / (256 * res)
                afcscale_tx = baudrate * phscale / (256 * synth_res)
            else:
                afcscale = baudrate * phscale / (256 * res)
                afcscale_tx = baudrate * phscale / (256 * synth_res)

        elif (demod_sel == model.vars.demod_select.var_enum.BCR):
            # digital mixer frequency comp
            afcscale =  model.vars.pro2_afc_gain.value /  res
            afcscale_tx = model.vars.pro2_afc_gain.value / synth_res
        else:
            afcscale = 0.0
            afcscale_tx = 0.0

        afcscale = afcscale * scale

        #Special case to set afc_scale_tx to 0 to disable TX AFC adjust when using oneshot
        #See https://jira.silabs.com/browse/MCUW_RADIO_CFG-1510
        if (afc_tx_adjust_enable == False) and afc_oneshot:
            afcscale_tx = 0.0

        model.vars.afc_scale.value = afcscale
        model.vars.afc_scale_tx.value = afcscale_tx

#    def calc_afc_scale_tx_reg(self, model):
#        """
#        convert AFC scale TX value to mantissa and exponent register values
#
#        Args:
#            model (ModelRoot) : Data model to read and write variables from
#        """
#
#        afc_scale = model.vars.afc_scale_tx.value
#
#        if afc_scale == 0:
#            best_m = 0
#            best_e = 0
#        else:
#            best_diff = 99e9
#            # find best m, e pair that gives a scale less than or equal to the target scale
#            for m in range(1,32):
#                for e in range(-8,8):
#                    diff = afc_scale - m * 2**e
#
#                    if diff > 0 and diff <= best_diff:
#                        best_diff = diff
#                        best_e = e
#                        best_m = m
#
#            if best_e < 0:
#                best_e += 16
#
#        self._reg_write(model.vars.MODEM_AFCADJTX_AFCSCALEE, int(best_e))
#        self._reg_write(model.vars.MODEM_AFCADJTX_AFCSCALEM, int(best_m))
#
#    def calc_afc_scale_tx_actual(self, model):
#        """
#
#        Args:
#            model (ModelRoot) : Data model to read and write variables from
#        """
#
#        e = float(model.vars.MODEM_AFCADJTX_AFCSCALEE.value)
#        m = float(model.vars.MODEM_AFCADJTX_AFCSCALEM.value)
#
#        if e > 7:
#            e -= 16
#
#        model.vars.afc_scale_tx_actual.value = m * 2**e
#
#    def calc_fdm0thresh_val(self, model):
#        """
#        in FDM0 mode set FDM0THRESH register
#
#        Args:
#            model (ModelRoot) : Data model to read and write variables from
#        """
#
#        timingbases = model.vars.timingbases_actual.value
#        #scale = model.vars.freq_gain_scale.value
#
#        # only used in FDM0 mode which is active if timingbases = 0
#        if timingbases > 0:
#            model.vars.fdm0_thresh.value = 0
#            return
#
#        # nominal frequency deviation is +/- 64 we like to set this threshold
#        # to half of that so 32 but if the FREQGAIN setting is scaled to avoid
#        # saturation we need to scale this value accordingly
#        fdm0_thresh = 32 #* scale
#
#        if fdm0_thresh < 8:
#            fdm0_thresh = 8
#        elif fdm0_thresh > 71:      # Limiting so the register won't overflow
#            fdm0_thresh = 71        # See calc_fdm0thresh_reg for details
#
#        model.vars.fdm0_thresh.value = int(fdm0_thresh)
#
#    def calc_afc_scale_reg(self, model):
#        """
#        convert AFC scale value to mantissa and exponent register values
#
#        Args:
#            model (ModelRoot) : Data model to read and write variables from
#        """
#
#        afc_scale = model.vars.afc_scale.value
#
#        if afc_scale == 0:
#            best_m = 0
#            best_e = 0
#        else:
#            best_diff = 99e9
#            best_e = 0
#            best_m = 0
#            # start with the highest allowed mantissa and find best m, e pair
#            for m in xrange(1, 31, 1):
#                e = math.floor(math.log(afc_scale / m, 2))
#                diff = abs(afc_scale - m * 2**e)
#
#                # solution is valid only if e is within the limits
#                if (diff < best_diff) and e >= -8 and e <= 7:
#                    best_diff = diff
#                    best_e = e
#                    best_m = m
#
#            if best_e < 0:
#                best_e += 16
#
#            if best_m > 31:
#                best_m = 31
#
#        self._reg_write(model.vars.MODEM_AFCADJRX_AFCSCALEE, int(best_e))
#        self._reg_write(model.vars.MODEM_AFCADJRX_AFCSCALEM, int(best_m))
#
#    def calc_afc_scale_actual(self, model):
#        """
#        Args:
#            model (ModelRoot) : Data model to read and write variables from
#        """
#        e = float(model.vars.MODEM_AFCADJRX_AFCSCALEE.value)
#        m = float(model.vars.MODEM_AFCADJRX_AFCSCALEM.value)
#
#        if e > 7:
#            e -= 16
#
#        model.vars.afc_scale_actual.value = m * 2**e
#
#    def calc_freq_comp_mode(self, model):
#        """
#        determine best frequency compensation mode based on emprical data
#
#        Args:
#            model (ModelRoot) : Data model to read and write variables from
#        """
#        preamble_len = model.vars.preamble_length.value
#        demod_select = model.vars.demod_select.value
#        preamsch = model.vars.MODEM_TRECPMDET_PREAMSCH.value
#        modtype = model.vars.modulation_type.value
#        afc_mode = model.vars.afc_run_mode.var_enum.CONTINUOUS
#        tol = model.vars.baudrate_tol_ppm.value
#
#        # enable 1-shot for Viterbi demod only if preamble length is larger than 15 and preamble search mode is enabled
#        if demod_select == model.vars.demod_select.var_enum.TRECS_VITERBI or demod_select == model.vars.demod_select.var_enum.TRECS_SLICER:
#            if preamble_len >= 16 and preamsch:
#                afc_mode = model.vars.afc_run_mode.var_enum.ONE_SHOT
#        # enable 1-shot for BCR only if preamble length is larger than 15 and modulation is not OOK and baudrate offset is less than 1%
#        elif demod_select == model.vars.demod_select.var_enum.BCR:
#            if preamble_len >= 16 and modtype != model.vars.modulation_type.var_enum.OOK  and tol < 50000:
#                afc_mode = model.vars.afc_run_mode.var_enum.ONE_SHOT
#
#        # default mode
#        freq_mode = model.vars.frequency_comp_mode.var_enum.INTERNAL_ALWAYS_ON
#
#        model.vars.frequency_comp_mode.value = freq_mode
#        model.vars.afc_run_mode.value = afc_mode
#
#
#    def calc_afconeshoft_reg(self, model):
#        modtype = model.vars.modulation_type.value
#        run_mode = model.vars.afc_run_mode.value
#        comp_mode = model.vars.frequency_comp_mode.value
#
#        comp_mode_index = self.freq_comp_mode_index(model, comp_mode)
#
#        if (run_mode == model.vars.afc_run_mode.var_enum.ONE_SHOT) and (modtype != model.vars.modulation_type.var_enum.OOK and modtype != model.vars.modulation_type.var_enum.ASK): #and comp_mode_index > 3:
#            oneshot = 1
#        else:
#            oneshot = 0
#
#        if comp_mode_index > 3:
#            limreset = 1
#        else:
#            limreset = 0
#
#        self._reg_write(model.vars.MODEM_AFC_AFCONESHOT, oneshot)
#        self._reg_write(model.vars.MODEM_AFC_AFCDELDET, 0)
#        self._reg_write(model.vars.MODEM_AFC_AFCDSAFREQOFFEST, 0)
#        self._reg_write(model.vars.MODEM_AFC_AFCENINTCOMP, 0)
#        self._reg_write(model.vars.MODEM_AFC_AFCLIMRESET, limreset)
#        self._reg_write(model.vars.MODEM_AFC_AFCGEAR, 3)
#
#    def calc_afcdel_reg(self, model):
#        """
#        calculate AFC Delay based on over sampling rate (osr) if AFC is enabled
#
#        Args:
#            model (ModelRoot) : Data model to read and write variables from
#        """
#
#        mode = model.vars.frequency_comp_mode.value
#        osr = model.vars.oversampling_rate_actual.value
#        demod_select = model.vars.demod_select.value
#        afconeshot = model.vars.MODEM_AFC_AFCONESHOT.value
#        del_digmix_to_demod = model.vars.grpdelay_to_demod.value
#        remoddwn = model.vars.MODEM_PHDMODCTRL_REMODDWN.value + 1
#
#        if demod_select == model.vars.demod_select.var_enum.TRECS_VITERBI or demod_select == model.vars.demod_select.var_enum.TRECS_SLICER:
#            if afconeshot:
#                # AFCDEL is in symbols when used for Viterbi Demod so divide by OSR
#                # if REMODDWN is not 1 that will also need to be taken into account
#                afcdel = math.ceil(del_digmix_to_demod / osr * remoddwn)
#            else:
#                afcdel = 0
#        else:
#            mode_index = self.freq_comp_mode_index(model, mode)
#
#            # AFC mode
#            if mode_index >= 4:
#                afcdel = model.vars.grpdelay_to_demod.value
#            else:
#                afcdel = 0
#
#        if afcdel > 31:
#            afcdel = 31
#
#        self._reg_write(model.vars.MODEM_AFC_AFCDEL, int(afcdel))


    def afc_adj_limit(self, model):

        freq_limit = model.vars.freq_offset_hz.value
        synth_res = model.vars.synth_res_actual.value
        afclimreset = model.vars.afc_lim_reset_actual.value
        digmix_res = model.vars.digmix_res_actual.value
        digmixfb = Calc_Utilities_Sol().get_fefilt_actual(model, 'DIGMIXCTRL_DIGMIXFBENABLE')

        if digmixfb:
            res = digmix_res
        else:
            res = synth_res

        # calculate limit
        afcadjlim = freq_limit / res

        # if AFC_LIM_RESET is enabled we reset to the center frequency
        # once the accumulated offset reaches the limit. In this mode we
        # like to set the limit to about 20% higher than where we like the
        # limit to be
        if afclimreset:
            afcadjlim *= 1.2

        return int(round(afcadjlim))

    def calc_afc_adjlim_actual(self, model):

        afcadjlim = model.vars.MODEM_AFCADJLIM_AFCADJLIM.value
        synth_res = model.vars.synth_res_actual.value
        digmix_res = model.vars.digmix_res_actual.value
        digmixfb = digmixfb = Calc_Utilities_Sol().get_fefilt_actual(model, 'DIGMIXCTRL_DIGMIXFBENABLE')

        if digmixfb:
            res = digmix_res
        else:
            res = synth_res

        model.vars.afc_limit_hz_actual.value = afcadjlim * res

    def calc_afconeshoft_reg(self, model):

        modtype = model.vars.modulation_type.value
        run_mode = model.vars.afc_run_mode.value
        comp_mode = model.vars.frequency_comp_mode.value
        demod_select = model.vars.demod_select.value

        comp_mode_index = self.freq_comp_mode_index(model, comp_mode)

        if (run_mode == model.vars.afc_run_mode.var_enum.ONE_SHOT) and (modtype != model.vars.modulation_type.var_enum.OOK and modtype != model.vars.modulation_type.var_enum.ASK):
            oneshot = 1
        else:
            oneshot = 0

        if (comp_mode_index > 3) or (demod_select == model.vars.demod_select.var_enum.BCR):
            limreset = 1
        else:
            limreset = 0

        self._reg_write(model.vars.MODEM_AFC_AFCONESHOT, oneshot)
        self._reg_write(model.vars.MODEM_AFC_AFCDELDET, 0)
        self._reg_write(model.vars.MODEM_AFC_AFCDSAFREQOFFEST, 0)
        self._reg_write(model.vars.MODEM_AFC_AFCENINTCOMP, 0)
        self._reg_write(model.vars.MODEM_AFC_AFCLIMRESET, limreset)
        self._reg_write(model.vars.MODEM_AFC_AFCGEAR, 3)
from pyradioconfig.parts.ocelot.calculators.calc_freq_offset_comp import CALC_Freq_Offset_Comp_ocelot


class CALC_Freq_Offset_Comp_Margay(CALC_Freq_Offset_Comp_ocelot):
    #Inherit all from Ocelot

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
        digmixfb = model.vars.MODEM_DIGMIXCTRL_DIGMIXFB.value
        baudrate = model.vars.rx_baud_rate_actual.value
        osr = model.vars.oversampling_rate_actual.value
        afc_tx_adjust_enable = model.vars.afc_tx_adjust_enable.value
        afc_oneshot = model.vars.MODEM_AFC_AFCONESHOT.value
        bcr_det_en = model.vars.MODEM_PHDMODCTRL_BCRDETECTOR.value

        if digmixfb:
            res = digmix_res
        else:
            res = synth_res

        # AFC to synth for Legacy
        if(demod_sel==model.vars.demod_select.var_enum.LEGACY):
            if mode_index >= 4 and freqgain > 0:
                if mod_format == model.vars.modulation_type.var_enum.FSK2 or \
                    mod_format == model.vars.modulation_type.var_enum.MSK or \
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
                demod_sel==model.vars.demod_select.var_enum.LONGRANGE:
            if remoden and remodoutsel == 1:
                afcscale = baudrate * osr * phscale / (256 * freqgain * res)
                afcscale_tx = baudrate * osr * phscale / (256 * freqgain * synth_res)
            else:
                afcscale = 1.0 * baudrate * phscale / (256 * res)
                afcscale_tx = baudrate * phscale / (256 * synth_res)

                # Reduce afc scale by eighth if oneshot is disabled. Following BLE case
                if afc_oneshot == 0 and bcr_det_en == 1:
                    afcscale = afcscale / 8.0
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

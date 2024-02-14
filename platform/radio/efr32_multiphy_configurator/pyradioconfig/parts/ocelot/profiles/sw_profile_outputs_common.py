from pyradioconfig.calculator_model_framework.interfaces.iprofile import ModelOutput, ModelOutputType

class sw_profile_outputs_common_ocelot(object):
    # : Apps requested variables that need to be included in public studio log
    studio_log_output_list = {
        'base_frequency_actual': 'Actual Carrier Frequency [Hz]',
        'if_frequency_hz_actual': 'Actual Intermediate Frequency [Hz]',
        'synth_res_actual': 'Synthesizer Resolution [Hz]',
        'baudrate': 'Desired Bitrate [bps]',
        'tx_baud_rate_actual': 'Actual TX Baudrate [baud]',
        'rx_baud_rate_actual': 'Actual RX Baudrate [baud]',
        'tx_deviation_actual': 'Actual Deviation [Hz]',
        'modulation_index': 'Target Modulation Index',
        'modulation_index_actual': 'Actual Modulation Index',
        'demod_select': 'Selected Demodulator',
        'bandwidth_carson_hz': 'Carson Bandwidth [Hz]',
        'demod_bandwidth_hz': 'Theoretical Required Demodulator Bandwidth [Hz]',
        'rx_xtal_error_ppm': 'RX Crystal Accuracy [ppm]',
        'tx_xtal_error_ppm': 'TX Crystal Accuracy [ppm]',
        'bandwidth_actual': 'Pre Signal Lock RX Bandwidth [Hz]',
        'lock_bandwidth_actual': 'Post Signal Lock RX Bandwidth [Hz]',
        'rssi_adjust_db': 'Calculated RSSI Offset [dB]',
        'rssi_period': "RSSI Measurement Period",
        'oversampling_rate_actual': 'Actual Demodulator Oversampling Rate',
        'iq_rate_actual': 'Raw Data Sampling Rate [sps]',
        'delay_adc_to_demod_symbols': 'Signal Propagation Delay [symbol]',
        'trecs_effective_syncword_len': 'Effective Syncword Length',
        'trecs_effective_preamble_len': 'Effective Preamble Length',
        'trecs_pre_bits_to_syncword': 'Number of Bits Used from Preamble to Syncword [bits]',
        'preamble_string': 'Preamble Binary Pattern',
        'syncword_string': 'Syncword Binary Pattern',
        'lo_injection_side': 'Injection Side',
        'trecs_syncword_timeout_us': 'TRECS syncword timeout [us]',
        'rssi_period_sym_actual': 'RSSI Update Period [symbol]',
        'rssi_access_time_us_actual': 'RSSI Access Time After RX Start [us]'
    }

    """
        Builds studio log outputs into modem model
    """
    def buildStudioLogOutput(self, model, profile):

        # : Apps requested variables that need to be included in public studio log
        studio_log_output_list = self.studio_log_output_list

        # : create missing ModelOutput as INFO type
        for model_var_name, readable_name in studio_log_output_list.items():

            # : check if duplicate exists in the profile output. If so, replace with log output defined above
            for profile_output in profile.outputs:
                if profile_output._var.name == model_var_name:
                    profile.outputs.get_output(model_var_name).readable_name = readable_name

            if not hasattr(profile.outputs, model_var_name):
                if hasattr(model.vars, model_var_name):
                    model_vars_attr = getattr(model.vars, model_var_name)
                    profile.outputs.append(ModelOutput(model_vars_attr, '', ModelOutputType.INFO,
                                                       readable_name=readable_name))

        # : Set flag to True and display model output in Studio log
        for var_name in model.profile.outputs.__dict__.keys():
            model_attr = getattr(model.profile.outputs, var_name)
            if 'ModelOutput' in str(type(model_attr)):
                if var_name in studio_log_output_list.keys():
                    model_attr.in_public_log = True

                # : include all linked io vars in public log
                if model_attr.output_type == ModelOutputType.LINKED_IO:
                    model_attr.in_public_log = True

    def build_info_outputs(self, model, profile):
        profile.outputs.append(ModelOutput(model.vars.preamble_string, '', ModelOutputType.INFO,
                                           readable_name="Preamble Binary Pattern"))
        profile.outputs.append(ModelOutput(model.vars.syncword_string, '', ModelOutputType.INFO,
                                           readable_name="Sync Word Binary Pattern"))
        profile.outputs.append(ModelOutput(model.vars.bandwidth_actual, '', ModelOutputType.INFO,
                                           readable_name='Pre-Signal-Lock BW'))
        profile.outputs.append(ModelOutput(model.vars.baudrate, '', ModelOutputType.INFO,
                                           readable_name='Desired baudrate'))
        profile.outputs.append(ModelOutput(model.vars.sample_freq_actual, '', ModelOutputType.INFO,
                                           readable_name='Actual sample frequency'))
        profile.outputs.append(ModelOutput(model.vars.frc_conv_decoder_buffer_size, '', ModelOutputType.SW_VAR,
                                           readable_name='Convolutional Decoder Buffer Size'))
        profile.outputs.append(ModelOutput(model.vars.fec_enabled, '', ModelOutputType.SW_VAR,
                                           readable_name='FEC enabled flag'))

    def build_ircal_outputs(self, model, profile):
        profile.outputs.append(ModelOutput(model.vars.ircal_auxndiv, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL auxndiv'))
        profile.outputs.append(ModelOutput(model.vars.ircal_auxlodiv, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL auxlodiv'))
        profile.outputs.append(ModelOutput(model.vars.ircal_rampval, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL rampval'))
        profile.outputs.append(ModelOutput(model.vars.ircal_rxamppll, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL rxamppll'))
        profile.outputs.append(ModelOutput(model.vars.ircal_rxamppa, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL rxamppa'))
        profile.outputs.append(ModelOutput(model.vars.ircal_manufconfigvalid, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL manufconfigvalid'))
        profile.outputs.append(ModelOutput(model.vars.ircal_pllconfigvalid, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL pllconfigvalid'))
        profile.outputs.append(ModelOutput(model.vars.ircal_paconfigvalid, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL paconfigvalid'))
        profile.outputs.append(ModelOutput(model.vars.ircal_useswrssiaveraging, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL useswrssiaveraging'))
        profile.outputs.append(ModelOutput(model.vars.ircal_numrssitoavg, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL numrssitoavg'))
        profile.outputs.append(ModelOutput(model.vars.ircal_throwawaybeforerssi, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL throwawaybeforerssi'))
        profile.outputs.append(ModelOutput(model.vars.ircal_delayusbeforerssi, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL delayusbeforerssi'))
        profile.outputs.append(ModelOutput(model.vars.ircal_delayusbetweenswrssi, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL delayusbetweenswrssi'))
        profile.outputs.append(ModelOutput(model.vars.ircal_bestconfig, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL bestconfig'))
        profile.outputs.append(ModelOutput(model.vars.ircal_murshf, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL MURSHF'))
        profile.outputs.append(ModelOutput(model.vars.ircal_muishf, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL MUISHF'))

        # All but one (agcrssiperiod) of these were created for backwards compatibility with RAIL 1.x - remove in RAIL 2.x
        profile.outputs.append(ModelOutput(model.vars.ircal_agcrssiperiod, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL agcrssiperiod'))
        profile.outputs.append(ModelOutput(model.vars.ircal_useswrssiaveraging2, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL useswrssiaveraging new'))
        profile.outputs.append(ModelOutput(model.vars.ircal_numrssitoavg2, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL numrssitoavg new'))
        profile.outputs.append(ModelOutput(model.vars.ircal_throwawaybeforerssi2, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL throwawaybeforerssi new'))
        profile.outputs.append(ModelOutput(model.vars.ircal_delayusbeforerssi2, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL delayusbeforerssi new'))
        profile.outputs.append(ModelOutput(model.vars.ircal_delayusbetweenswrssi2, '', ModelOutputType.SW_VAR,
                                           readable_name='IRCAL delayusbetweenswrssi new'))

    def build_rail_outputs(self, model, profile):
        profile.outputs.append(ModelOutput(model.vars.frequency_offset_factor, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Frequency Offset Factor'))
        profile.outputs.append(ModelOutput(model.vars.frequency_offset_factor_fxp, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Frequency Offset Factor FXP'))
        profile.outputs.append(ModelOutput(model.vars.dynamic_slicer_enabled, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Dynamic Slicer Feature Enabled'))
        profile.outputs.append(ModelOutput(model.vars.dynamic_slicer_threshold_values, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Dynamic Slicer Threshold Values'))
        profile.outputs.append(ModelOutput(model.vars.dynamic_slicer_level_values, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Dynamic Slicer Level Values'))
        profile.outputs.append(ModelOutput(model.vars.src1_calcDenominator, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='SRC1 Helper Calculation'))
        profile.outputs.append(ModelOutput(model.vars.src2_calcDenominator, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='SRC2 Helper Calculation'))
        profile.outputs.append(ModelOutput(model.vars.tx_baud_rate_actual, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='TX Baud Rate'))
        profile.outputs.append(ModelOutput(model.vars.baud_per_symbol_actual, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Number of baud to transmit 1 symbol'))
        profile.outputs.append(ModelOutput(model.vars.bits_per_symbol_actual, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Number of bits contained in 1 symbol'))
        profile.outputs.append(ModelOutput(model.vars.rx_ch_hopping_order_num, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='For receive scanning PHYs: order of PHY in scanning sequence'))
        profile.outputs.append(ModelOutput(model.vars.rx_ch_hopping_mode, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='For receive scanning PHYs: event to trigger a hop to next PHY'))
        profile.outputs.append(ModelOutput(model.vars.rx_ch_hopping_delay_usec, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='For receive scanning PHYs: delay in microseconds to look for RX on a particular PHY'))
        profile.outputs.append(ModelOutput(model.vars.ppnd_0, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='DCDC Pulse Period for first quarter of synth region'))
        profile.outputs.append(ModelOutput(model.vars.ppnd_1, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='DCDC Pulse Period for second quarter of synth region'))
        profile.outputs.append(ModelOutput(model.vars.ppnd_2, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='DCDC Pulse Period for third quarter of synth region'))
        profile.outputs.append(ModelOutput(model.vars.ppnd_3, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='DCDC Pulse Period for forth quarter of synth region'))
        profile.outputs.append(ModelOutput(model.vars.psm_max_sleep_us, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Maximum time to sleep in PSM (us)'))
        profile.outputs.append(ModelOutput(model.vars.am_low_ramplev, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='LOW ramp level for amplitude modulation'))
        profile.outputs.append(ModelOutput(model.vars.ircal_power_level, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='IR cal power level (amplitude)'))
        profile.outputs.append(ModelOutput(model.vars.div_antdivmode, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Antenna diversity mode'))
        profile.outputs.append(ModelOutput(model.vars.div_antdivrepeatdis, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Disable repeated measurement of first antenna when Select-Best algorithm is used'))
        profile.outputs.append(ModelOutput(model.vars.rssi_adjust_db, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='RSSI compensation value calculated from decimation and digital gains'))
        profile.outputs.append(ModelOutput(model.vars.stack_info, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Stack information containing protocol and PHY IDs'))
        profile.outputs.append(ModelOutput(model.vars.rx_sync_delay_ns, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Time needed from start of preamble on-air to sync detect'))
        profile.outputs.append(ModelOutput(model.vars.rx_eof_delay_ns, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Time from end of frame on-air to RX EOF timestamp'))
        profile.outputs.append(ModelOutput(model.vars.tx_eof_delay_ns, '', ModelOutputType.RAIL_CONFIG,
                                           readable_name='Time from end of frame on-air to TX EOF timestamp'))

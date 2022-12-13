from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from pyradioconfig.parts.common.calculators.calc_frame_detect import CALC_Frame_Detect
from pyradioconfig.parts.ocelot.calculators.calc_demodulator import CALC_Demodulator_ocelot
from enum import Enum
from math import *

class calc_softmodem_sol(ICalculator):

    def buildVariables(self, model):
        self._addModelVariable(model, 'softmodem_modulation_type', Enum, ModelVariableFormat.DECIMAL, desc='Modulation type used for softmodem calculations')
        model.vars.softmodem_modulation_type.var_enum = CreateModelVariableEnum(
            enum_name='SoftmodemModulationTypeEnum',
            enum_desc='Softmodem Modulation Type',
            member_data=[
                ['NONE', 0, 'None'],
                ['SUN_OFDM', 1, 'SUN OFDM'],
                ['SUN_OQPSK', 2, 'SUN OQPSK'],
                ['SUN_FSK', 3, 'SUN FSK'],
                ['LEGACY_OQPSK', 4, 'Legacy OQPSK'],
                ['CW', 5, 'CW']
            ])

        self._addModelVariable(model, 'ofdm_interleaving_depth', Enum, ModelVariableFormat.DECIMAL, desc='Interleaving depth for SUN OFDM PHYs corresponding to PIB attribute phyOfdmInterleaving')
        model.vars.ofdm_interleaving_depth.var_enum = CreateModelVariableEnum(
            enum_name='OfdmInterleavingEnum',
            enum_desc='SUN OFDM Interleaving Depth',
            member_data=[
                ['ONE_SYMBOL', 0, 'One symbol'],
                ['SPREADING_FACTOR', 1, 'Number of symbols is equal to the frequency domain spreading factor']
            ])

        self._addModelVariable(model, 'ofdm_symbol_rate', float, ModelVariableFormat.DECIMAL, desc='Symbol rate for OFDM')

        self._addModelVariable(model, 'fcs_type_802154', Enum, ModelVariableFormat.DECIMAL, desc='FCS type for 802154 PHYs')
        model.vars.fcs_type_802154.var_enum = CreateModelVariableEnum(
            enum_name='FcsTypeEnum',
            enum_desc='802154 FCS Type',
            member_data=[
                ['TWO_BYTE', 1, '16-bit ITU-T CRC'],
                ['FOUR_BYTE', 0, '32-bit ANSI X3.66-1979 CRC'],
            ])

        self._addModelVariable(model, 'sun_oqpsk_chiprate', Enum, ModelVariableFormat.DECIMAL, desc='Chiprate for SUN OQPSK PHYs')
        model.vars.sun_oqpsk_chiprate.var_enum = CreateModelVariableEnum(
            enum_name='SunOqpskChiprateEnum',
            enum_desc='SUN OQPSK Chiprate',
            member_data=[
                ['_100_KCPS', 0, '100 kcps'],
                ['_400_KCPS', 1, '400 kcps'],
                ['_1000_KCPS', 2, '1000 kcps'],
                ['_2000_KCPS', 3, '2000 kcps']
            ])

        self._addModelVariable(model, 'sun_fsk_fecsel', Enum, ModelVariableFormat.DECIMAL,
                               desc='FEC selection for SUN FSK PHYs')
        model.vars.sun_fsk_fecsel.var_enum = CreateModelVariableEnum(
            enum_name='SunFskFecSelEnum',
            enum_desc='SUN FSK FEC Selection',
            member_data=[
                ['NONE', 0, 'No FEC'],
                ['NRNSC_INTERLEAVING', 1, 'NRNSC interleaving'],
                ['RSC_NO_INTERLEAVING', 2, 'RSC no interleaving'],
                ['RSC_INTERLEAVING', 3, 'RSC interleaving']
            ])

        self._addModelVariable(model, 'sun_fsk_sfd', int, ModelVariableFormat.DECIMAL,
                               desc='SFD value for SUN FSK PHYs corresponding to PIB attribute phySunFskSfd')

        self._addModelVariable(model, 'cw_signal_type', Enum, ModelVariableFormat.DECIMAL,
                               desc='CW signal type selection')
        model.vars.cw_signal_type.var_enum = CreateModelVariableEnum(
            enum_name='CwSignalTypeEnum',
            enum_desc='CW signal type selection',
            member_data=[
                ['COMPLEX', 0, 'CW complex tone on I and Q'],
                ['I_ONLY', 1, 'CW real tone on I only (Q=0)'],
                ['Q_ONLY', 2, 'CW real tone on Q only (I=0)'],
                ['DUAL', 3, 'CW complex tone + its dual tone left shifted of 100 KHz']
            ])

        self._addModelVariable(model, 'cw_dual_path', Enum, ModelVariableFormat.DECIMAL,
                               desc='CW dual path selection')
        model.vars.cw_dual_path.var_enum = CreateModelVariableEnum(
            enum_name='CwDualPathEnum',
            enum_desc='CW dual path selection',
            member_data=[
                ['RXF1', 0, 'RXF1 single reception'],
                ['RXF1_RXF2', 1, 'RXF1 RXF2 dual reception']
            ])

        self._addModelVariable(model, 'cw_nfft_log2', int, ModelVariableFormat.DECIMAL,
                               desc='CW RX log2 of Nfft')

        self._addModelVariable(model, 'cw_fft_analyze', Enum, ModelVariableFormat.DECIMAL,
                               desc='CW fft analysis')
        model.vars.cw_fft_analyze.var_enum = CreateModelVariableEnum(
            enum_name='CwFftAnalysisEnum',
            enum_desc='CW fft analysis',
            member_data=[
                ['NONE', 0, 'FFT analysis not done'],
                ['ONE_BIN', 1, 'FFT analysis expects to find 1 single bin at CW Tone frequency value FREQ'],
                ['TWO_BINS', 2, 'FFT analysis expects to find 2 symmetrical bins at CW Tone frequency values +FREQ and -FREQ'],
                ['DUAL', 3, 'FFT anaysis expects to find 1 bin at FREQ + a 2nd bin left shifted of 100 KHz of FREQ'],
                ['LOOPBACK', 4, 'Specific FFT analysis mode for CW loopback sim']
            ])

        self._addModelVariable(model, 'cw_freq', int, ModelVariableFormat.DECIMAL,
                               desc='CW frequency for softmodem DAC')

        self._addModelVariable(model, 'cw_amp', int, ModelVariableFormat.DECIMAL,
                               desc='CW amplitude for softmodem DAC')

        self._addModelVariable(model, 'band_freq_mhz_802154', int, ModelVariableFormat.DECIMAL,
                               desc='Band frequency (in MHz) for SUN PHYs')

    def calc_softmodem_defaults(self, model):
        #This function assigns defaults to the softmodem vars so that other Profiles will correctly populate the vars
        model.vars.ofdm_option.value = model.vars.ofdm_option.var_enum.OPT1
        model.vars.sun_oqpsk_chiprate.value = model.vars.sun_oqpsk_chiprate.var_enum._100_KCPS

    def calc_softmodem_modulation_type(self, model):
        #For now, calculate the softmodem modulation type as None by default (must be manually set per softmodem PHY)
        #We can sometimes predict this based on the modulation type and demod selected

        #Read in model vars
        demod_select = model.vars.demod_select.value
        modulation_type = model.vars.modulation_type.value

        if demod_select == model.vars.demod_select.var_enum.SOFT_DEMOD:

            if modulation_type == model.vars.modulation_type.var_enum.OFDM:
                softmodem_modulation_type = model.vars.softmodem_modulation_type.var_enum.SUN_OFDM
            elif modulation_type == model.vars.modulation_type.var_enum.OQPSK:
                #Assume SUN OQPSK for now, but need to either add code to predict LEGACY OQPSK or hard code this
                #Probably calculate this based on the Profile selected once all Profiles are complete
                softmodem_modulation_type = model.vars.softmodem_modulation_type.var_enum.SUN_OQPSK
            elif modulation_type == model.vars.modulation_type.var_enum.FSK2 or \
                    modulation_type == model.vars.modulation_type.var_enum.FSK4:
                softmodem_modulation_type = model.vars.softmodem_modulation_type.var_enum.SUN_FSK
            else:
                softmodem_modulation_type = model.vars.softmodem_modulation_type.var_enum.NONE

        else:
            softmodem_modulation_type = model.vars.softmodem_modulation_type.var_enum.NONE

        #Write the variable
        model.vars.softmodem_modulation_type.value = softmodem_modulation_type

    def calc_ofdm_interleaving_depth(self, model):
        #By default set the interleaving depth to 1 symbol

        model.vars.ofdm_interleaving_depth.value = model.vars.ofdm_interleaving_depth.var_enum.ONE_SYMBOL

    def calc_fcs_type_802154(self, model):

        #For the Wi-SUN Profiles, calc the CRC from the FCS that is specified in the Profile
        if 'sun' in model.profile.name.lower():
            fcs_type_802154 = model.vars.fcs_type_802154.value
            if fcs_type_802154 == model.vars.fcs_type_802154.var_enum.TWO_BYTE:
                crc_poly = model.vars.crc_poly.var_enum.CCITT_16
            else:
                crc_poly = model.vars.crc_poly.var_enum.ANSIX366_1979
            model.vars.crc_poly.value = crc_poly

        #For the other Profiles, calculate the FCS type variable from the CRC Profile Input
        else:
            crc_poly = model.vars.crc_poly.value
            if crc_poly == model.vars.crc_poly.var_enum.CCITT_16:
                fcs_type_802154 = model.vars.fcs_type_802154.var_enum.TWO_BYTE
            else:
                fcs_type_802154 = model.vars.fcs_type_802154.var_enum.FOUR_BYTE
            model.vars.fcs_type_802154.value = fcs_type_802154

    def calc_sun_fsk_fecsel(self, model):

        #Read in model variables
        fec_en = model.vars.fec_en.value

        #Translate between fec_en variable and the new FSK FEC variable
        if fec_en == model.vars.fec_en.var_enum.FEC_154G_NRNSC_INTERLEAVING:
            sun_fsk_fecsel = model.vars.sun_fsk_fecsel.var_enum.NRNSC_INTERLEAVING
        elif fec_en == model.vars.fec_en.var_enum.FEC_154G_RSC_INTERLEAVING:
            sun_fsk_fecsel = model.vars.sun_fsk_fecsel.var_enum.RSC_INTERLEAVING
        elif fec_en == model.vars.fec_en.var_enum.FEC_154G_RSC_NO_INTERLEAVING:
            sun_fsk_fecsel = model.vars.sun_fsk_fecsel.var_enum.RSC_NO_INTERLEAVING
        else:
            sun_fsk_fecsel = model.vars.sun_fsk_fecsel.var_enum.NONE

        #Write the variable
        model.vars.sun_fsk_fecsel.value = sun_fsk_fecsel

    def calc_sun_fsk_sfd(self, model):

        #For now, always set to 0 by default
        model.vars.sun_fsk_sfd.value = 0

    def calc_band_freq_mhz_802154(self, model):

        #Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        base_frequency_hz = model.vars.base_frequency_hz.value

        #From 802154-2020 Table 10-14—Channel numbering for SUN PHYs
        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OQPSK:
            if base_frequency_hz < 779.2e6:
                band_freq_mhz_802154 = 470
            elif base_frequency_hz < 863.1e6:
                band_freq_mhz_802154 = 780
            elif base_frequency_hz <  870.1e6:
                band_freq_mhz_802154 = 868
            elif base_frequency_hz <  919.2e6:
                band_freq_mhz_802154 = 915
            elif base_frequency_hz < 920.6e6:
                band_freq_mhz_802154 = 917
            else:
                band_freq_mhz_802154 = 920

            #Write the model var
            model.vars.band_freq_mhz_802154.value = band_freq_mhz_802154

    def calc_softmodem_dont_cares(self, model):
        # We must be very careful with softmodem virtual regs and don't cares,
        # because multiple regs share the same memory space

        #Read in the softmodem modulation type used
        softmodem_modulation_type_actual = model.vars.softmodem_modulation_type.value
        softmodem_modulation_type_enum = model.vars.softmodem_modulation_type.var_enum

        #Store softmodem reg prefixes in a dict
        softmodem_reg_prefixes = {
            softmodem_modulation_type_enum.SUN_OFDM:'SUNOFDM_',
            softmodem_modulation_type_enum.SUN_OQPSK:'SUNOQPSK_',
            softmodem_modulation_type_enum.SUN_FSK:'SUNFSK_',
            softmodem_modulation_type_enum.LEGACY_OQPSK:'LEGOQPSK_',
            softmodem_modulation_type_enum.CW:'CW_'
        }

        #Build a tuple of prefix strings we want to don't care
        prefix_tuple = ()
        for modulation_type in softmodem_reg_prefixes:
            if modulation_type != softmodem_modulation_type_actual:
                prefix_tuple += (softmodem_reg_prefixes[modulation_type],)

        #Set the don't cares
        for model_var in model.vars:
            if (model_var.name.startswith(prefix_tuple)) and (model_var.svd_mapping is not None):
                    model_var.value_do_not_care = True

    def calc_softmodem_cw_version_regs(self, model):
        self._reg_write(model.vars.CW_VREGS_MAJORVERSION, 0)
        self._reg_write(model.vars.CW_VREGS_MINORVERSION, 0)

    def calc_softmodem_cw(self, model):

        #Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value
        dac_freq_actual = model.vars.dac_freq_actual.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.CW:

            model.vars.cw_amp.value = 24000  # Set default amplitude to 24000 (any forced value will override)
            model.vars.cw_nfft_log2.value = 9 # Set FFT size to 512
            model.vars.cw_fft_analyze.value = model.vars.cw_fft_analyze.var_enum.NONE

            cw_amp = model.vars.cw_amp.value
            cw_freq = model.vars.cw_freq.value
            cw_dual_path = model.vars.cw_dual_path.value
            cw_signal_type = model.vars.cw_signal_type.value
            cw_nfft_log2 = model.vars.cw_nfft_log2.value
            cw_fft_analyze = model.vars.cw_fft_analyze.value
            softmodem_tx_interpolation1_actual = model.vars.TXFRONT_INT1CFG_RATIO.value + 1
            softmodem_tx_interpolation2_actual = model.vars.TXFRONT_INT2CFG_RATIO.value + 1

            #Copy modulation type into CW register
            modulation_field = softmodem_modulation_type

            #Calculate tone frequency
            # CW_tone_freq (Hz) = sampFreqHz * (freq/(2**16))
            freq_field = cw_freq / dac_freq_actual * softmodem_tx_interpolation1_actual * softmodem_tx_interpolation2_actual * (2**16)

            #Calculate dual path and signal type
            dual_path_field = cw_dual_path
            sig_type_field = cw_signal_type

            nfft_log2_field = cw_nfft_log2
            fft_analyze_field = cw_fft_analyze

            #Set digital amplitude to fullscale for now
            amp_field = cw_amp # CW tone amplitude [0:32767] - TX only - max 24000 to consider no saturation at TX FrontEnd output

            #Write crystal frequency
            xtal_freq_field = xtal_frequency_hz / 1000

        else:
            modulation_field = model.vars.softmodem_modulation_type.var_enum.NONE
            freq_field = 0
            amp_field = 0
            xtal_freq_field = 0
            nfft_log2_field = 0
            fft_analyze_field = 0
            dual_path_field = model.vars.cw_dual_path.var_enum.RXF1
            sig_type_field = model.vars.cw_signal_type.var_enum.COMPLEX

        #Note that tone amplitude is managed by RAIL firmware

        #Write the registers
        self._reg_write(model.vars.CW_CFG1_MODULATION, int(modulation_field))
        self._reg_write(model.vars.CW_CFG1_NFFTLOG2, int(nfft_log2_field))
        self._reg_write(model.vars.CW_CFG1_DUALPATH, int(dual_path_field))
        self._reg_write(model.vars.CW_CFG1_FFTANALYZE, int(fft_analyze_field))
        self._reg_write(model.vars.CW_CFG1_SIGTYPE, int(sig_type_field))
        self._reg_write(model.vars.CW_CFG2_FREQ, int(freq_field))
        self._reg_write(model.vars.CW_CFG2_AMP, int(amp_field))
        self._reg_write(model.vars.CW_CFG3_XTALFREQ, int(xtal_freq_field))

    def calc_softmodem_sunofdm_version_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_VREGS_MAJORVERSION, 1)
        self._reg_write(model.vars.SUNOFDM_VREGS_MINORVERSION, 0)

    def calc_softmodem_sunofdm_cfg1_regs(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        ofdm_option = model.vars.ofdm_option.value
        ofdm_interleaving_depth = model.vars.ofdm_interleaving_depth.value
        fcs_type_802154 = model.vars.fcs_type_802154.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:

            # Copy modulation type into SUNOFDM register
            modulation_field = softmodem_modulation_type

            # Write OFDM option (the field is stored as option number minus one)
            ofdmoption_field = ofdm_option

            # Write interleaving PIB
            interleaving_field = ofdm_interleaving_depth

            # Write FCS type
            macfcstype_field = fcs_type_802154

            # Write crystal frequency
            xtal_freq_field = xtal_frequency_hz / 1000

        else:
            modulation_field = model.vars.softmodem_modulation_type.var_enum.NONE
            ofdmoption_field = 0
            interleaving_field = 0
            macfcstype_field = 0
            xtal_freq_field = 0

        #Write the registers
        self._reg_write(model.vars.SUNOFDM_CFG1_MODULATION, int(modulation_field))
        self._reg_write(model.vars.SUNOFDM_CFG1_OFDMOPTION, int(ofdmoption_field))
        self._reg_write(model.vars.SUNOFDM_CFG1_INTERLEAVING, int(interleaving_field))
        self._reg_write(model.vars.SUNOFDM_CFG1_MACFCSTYPE, int(macfcstype_field))
        self._reg_write(model.vars.SUNOFDM_CFG1_XTALFREQ, int(xtal_freq_field))

    def calc_softmodem_sunofdm_cfg2_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_CFG2_NBSTF, 5)

    def calc_softmodem_sunofdm_rxcfg1_regs(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        ofdm_option = model.vars.ofdm_option.value
        base_frequency_hz = model.vars.base_frequency_hz.value
        ofdm_subcarrier_spacing_hz = model.vars.ofdm_subcarrier_spacing_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:

            target_ppm = 75
            target_kHz = (target_ppm/1000000.0 * base_frequency_hz)/1000
            ICS_kHz = ofdm_subcarrier_spacing_hz/1000

            if ofdm_option == model.vars.ofdm_option.var_enum.OPT1:
                STF_spacing = 8
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT2:
                STF_spacing = 4
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT3:
                STF_spacing = 4
            else:
                STF_spacing = 2

            coarsefreq_lower = ICS_kHz/2.0*(-STF_spacing+0)
            coarsefreq_upper = ICS_kHz/2.0*(STF_spacing+2)

            extfreqlower_field = floor((-target_kHz-coarsefreq_lower)/(ICS_kHz*STF_spacing))
            extfrequpper_field = ceil((target_kHz-coarsefreq_upper)/(ICS_kHz*STF_spacing))

            dualphr_field = 1 #Dual PHR enabled
            coarsefreq_field = 1 #Coarse freq enabled
            extcoarsefreq_field = 1  # Ext coarse freq enabled
            girecomb_field = 0 #Disabled

        else:
            extfreqlower_field = 0
            extfrequpper_field = 0
            dualphr_field = 0
            coarsefreq_field = 0
            extcoarsefreq_field = 0
            girecomb_field = 0

        self._reg_write(model.vars.SUNOFDM_RXCFG1_EXTFREQLOWER, int(extfreqlower_field), allow_neg=True, check_saturation=True)
        self._reg_write(model.vars.SUNOFDM_RXCFG1_EXTFREQUPPER, int(extfrequpper_field), check_saturation=True)
        self._reg_write(model.vars.SUNOFDM_RXCFG1_DUALPHR, int(dualphr_field))
        self._reg_write(model.vars.SUNOFDM_RXCFG1_COARSEFREQ, int(coarsefreq_field))
        self._reg_write(model.vars.SUNOFDM_RXCFG1_EXTCOARSEFREQ, int(extcoarsefreq_field))
        self._reg_write(model.vars.SUNOFDM_RXCFG1_GIRECOMB, int(girecomb_field))

    def calc_softmodem_sunofdm_rxcfg2_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_RXCFG2_RSSISETPOINT, 20000)

    def calc_softmodem_sunofdm_colldet_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_COLLDET_COLLDET, 1) #Collision detection enabled
        self._reg_write(model.vars.SUNOFDM_COLLDET_COLLDETTHR, 10)

    def calc_softmodem_sunofdm_afc_regs(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        lodiv_actual = model.vars.lodiv_actual.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value
        ofdm_option_index = int(model.vars.ofdm_option.value)
        adc_freq_actual = model.vars.adc_freq_actual.value
        dec0_actual = model.vars.dec0_actual.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            afc_correction = 2
            fdec0_out_hz = adc_freq_actual/8.0/dec0_actual

            if afc_correction == 2: #For now we always choose this
                afc_mixer_ratio_att = 16
                afc_mixer_ratio_gain = round(1302*lodiv_actual/xtal_frequency_hz*(2**(13+afc_mixer_ratio_att-ofdm_option_index)))
            else:
                afc_mixer_ratio_att = 15
                afc_mixer_ratio_gain = round(1302/fdec0_out_hz*(2**(14+afc_mixer_ratio_att-ofdm_option_index)))

        else:
            afc_correction = 0
            afc_mixer_ratio_att = 0
            afc_mixer_ratio_gain = 0

        self._reg_write(model.vars.SUNOFDM_AFC_AFCMIXERRATIOGAIN, int(afc_mixer_ratio_gain), check_saturation=True)
        self._reg_write(model.vars.SUNOFDM_AFC_AFCMIXERRATIOATT, int(afc_mixer_ratio_att), check_saturation=True)
        self._reg_write(model.vars.SUNOFDM_AFC_AFCCORRECTION, int(afc_correction))

    def calc_softmodem_sunofdm_txcfg1_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_TXCFG1_TXROTATERAMP, 1)  # Enabled
        self._reg_write(model.vars.SUNOFDM_TXCFG1_TXHCSERRORS, 0)  # Disabled
        self._reg_write(model.vars.SUNOFDM_TXCFG1_TXFCSERRORS, 0)  # Disabled

    def calc_softmodem_sunofdm_ant_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_ANT_ANTDIV, 0)  # Disabled
        self._reg_write(model.vars.SUNOFDM_ANT_ANTSEL, 0)  # Auto

    def calc_softmodem_sunofdm_pdet_regs(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            ofdm_option = model.vars.ofdm_option.value

            pdetcorrelwidth_field = 5
            pdetcf_field = 12
            pdetexcludecw_field = 1
            pdetcwthrgain_field = 3
            pdetcwthratt_field = 4

            if ofdm_option == model.vars.ofdm_option.var_enum.OPT1:
                pdetthrgain_field = 2
                pdet_thr_att_field = 4
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT2:
                pdetthrgain_field = 2
                pdet_thr_att_field = 4
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT3:
                pdetthrgain_field = 2
                pdet_thr_att_field = 4
            else:
                pdetthrgain_field = 6
                pdet_thr_att_field = 4
        else:
            pdetcorrelwidth_field = 0
            pdetcf_field = 0
            pdetexcludecw_field = 0
            pdetthrgain_field = 0
            pdetcwthrgain_field = 0
            pdetcwthratt_field = 0
            pdet_thr_att_field = 0

        self._reg_write(model.vars.SUNOFDM_PDET_PDETCORRELWIDTH, int(pdetcorrelwidth_field))
        self._reg_write(model.vars.SUNOFDM_PDET_PDETCF, int(pdetcf_field))
        self._reg_write(model.vars.SUNOFDM_PDET_PDETEXCLUDECW, int(pdetexcludecw_field))
        self._reg_write(model.vars.SUNOFDM_PDET_PDETTHRGAIN, int(pdetthrgain_field))
        self._reg_write(model.vars.SUNOFDM_PDET_PDETTHRATT, int(pdet_thr_att_field))
        self._reg_write(model.vars.SUNOFDM_PDET_PDETCWTHRGAIN, int(pdetcwthrgain_field))
        self._reg_write(model.vars.SUNOFDM_PDET_PDETCWTHRATT, int(pdetcwthratt_field))

    def calc_softmodem_sunofdm_decfiltcfg_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_DECFILTCFG_NTAPS, 32)
        self._reg_write(model.vars.SUNOFDM_DECFILTCFG_SYMMETRIC, 1)
        self._reg_write(model.vars.SUNOFDM_DECFILTCFG_INTERP, 0)
        self._reg_write(model.vars.SUNOFDM_DECFILTCFG_DECIM, 0) #Default
        self._reg_write(model.vars.SUNOFDM_DECFILTCFG_NSHIFT, 0) #Default
        self._reg_write(model.vars.SUNOFDM_DECFILTCFG_SKIPFIRST, 0) #Default

    def calc_softmodem_sunofdm_decfilt_regs(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            ofdm_option = model.vars.ofdm_option.value

            if ofdm_option == model.vars.ofdm_option.var_enum.OPT1:
                filter_coeffs = [7177, 2600, -1229, -1133, 537, 687, -262, -448, 120, 293, -44, -186, 9, 143, 82, 3]
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT2:
                filter_coeffs = [7415, 2369, -1461, -920, 754, 503, -459, -299, 294, 173, -187, -87, 107, 35, -51, -21]
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT3:
                filter_coeffs = [7386, 2416, -1455, -974, 763, 563, -474, -369, 319, 252, -231, -156, 164, 78, -116, -67]
            else:
                filter_coeffs = [8990, 70, -1803, 1203, 67, -772, 568, 61, -442, 320, 50, -273, 205, 32, -380, -118]

        else:
            filter_coeffs = [0]*16

        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF0_COEFF0, filter_coeffs[0], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF0_COEFF1, filter_coeffs[1], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF1_COEFF2, filter_coeffs[2], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF1_COEFF3, filter_coeffs[3], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF2_COEFF4, filter_coeffs[4], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF2_COEFF5, filter_coeffs[5], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF3_COEFF6, filter_coeffs[6], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF3_COEFF7, filter_coeffs[7], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF4_COEFF8, filter_coeffs[8], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF4_COEFF9, filter_coeffs[9], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF5_COEFF10, filter_coeffs[10], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF5_COEFF11, filter_coeffs[11], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF6_COEFF12, filter_coeffs[12], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF6_COEFF13, filter_coeffs[13], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF7_COEFF14, filter_coeffs[14], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_DECFILTCOEFF7_COEFF15, filter_coeffs[15], allow_neg=True)

    def calc_softmodem_sunofdm_pdetfiltcfg_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_PDETFILTCFG_NTAPS, 31)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCFG_SYMMETRIC, 1)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCFG_INTERP, 0)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCFG_DECIM, 0) #Default
        self._reg_write(model.vars.SUNOFDM_PDETFILTCFG_NSHIFT, 0) #Default
        self._reg_write(model.vars.SUNOFDM_PDETFILTCFG_SKIPFIRST, 0) #Default

    def calc_softmodem_sunofdm_pdetfilt_regs(self, model):
        filter_coeffs = [5804, 4648, 2014, -324, -1145, -605, 240, 525, 202, -232, -374, -225, -20, 72, 58, 19]
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF0_COEFF0, filter_coeffs[0], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF0_COEFF1, filter_coeffs[1], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF1_COEFF2, filter_coeffs[2], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF1_COEFF3, filter_coeffs[3], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF2_COEFF4, filter_coeffs[4], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF2_COEFF5, filter_coeffs[5], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF3_COEFF6, filter_coeffs[6], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF3_COEFF7, filter_coeffs[7], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF4_COEFF8, filter_coeffs[8], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF4_COEFF9, filter_coeffs[9], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF5_COEFF10, filter_coeffs[10], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF5_COEFF11, filter_coeffs[11], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF6_COEFF12, filter_coeffs[12], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF6_COEFF13, filter_coeffs[13], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF7_COEFF14, filter_coeffs[14], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_PDETFILTCOEFF7_COEFF15, filter_coeffs[15], allow_neg=True)

    def calc_softmodem_sunofdm_txfiltcfg_regs(self, model):
        TXF_NB_BIT_IQ_IN = 12
        FILT_NBIT_IQ_IN = 14
        nshift_field = -13+TXF_NB_BIT_IQ_IN-FILT_NBIT_IQ_IN
        self._reg_write(model.vars.SUNOFDM_TXFILTCFG_NTAPS, 32)
        self._reg_write(model.vars.SUNOFDM_TXFILTCFG_SYMMETRIC, 1)
        self._reg_write(model.vars.SUNOFDM_TXFILTCFG_INTERP, 0)
        self._reg_write(model.vars.SUNOFDM_TXFILTCFG_DECIM, 0)
        self._reg_write(model.vars.SUNOFDM_TXFILTCFG_NSHIFT, nshift_field, allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCFG_SKIPFIRST, 0)  # Default

    def calc_softmodem_sunofdm_txfilt_regs(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            ofdm_option = model.vars.ofdm_option.value

            if ofdm_option == model.vars.ofdm_option.var_enum.OPT1:
                filter_coeffs = [3428, 1436, -431, -648, 125, 418, 9, -289, -59, 196, 102, -116, -91, 57, 115, -69]
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT2:
                filter_coeffs = [3727, 1160, -736, -417, 395, 220, -234, -120, 142, 65, -81, -31, 43, 14, -21, -1]
            elif ofdm_option == model.vars.ofdm_option.var_enum.OPT3:
                filter_coeffs = [3770, 1115, -776, -370, 431, 180, -264, -86, 165, 39, -98, -13, 53, 2, -27, 6]
            else:
                filter_coeffs = [3807, 1076, -809, -332, 459, 146, -285, -57, 179, 16, -107, 4, 58, -9, -30, 13]

        else:
            filter_coeffs = [0]*16

        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF0_COEFF0, filter_coeffs[0], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF0_COEFF1, filter_coeffs[1], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF1_COEFF2, filter_coeffs[2], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF1_COEFF3, filter_coeffs[3], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF2_COEFF4, filter_coeffs[4], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF2_COEFF5, filter_coeffs[5], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF3_COEFF6, filter_coeffs[6], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF3_COEFF7, filter_coeffs[7], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF4_COEFF8, filter_coeffs[8], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF4_COEFF9, filter_coeffs[9], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF5_COEFF10, filter_coeffs[10], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF5_COEFF11, filter_coeffs[11], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF6_COEFF12, filter_coeffs[12], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF6_COEFF13, filter_coeffs[13], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF7_COEFF14, filter_coeffs[14], allow_neg=True)
        self._reg_write(model.vars.SUNOFDM_TXFILTCOEFF7_COEFF15, filter_coeffs[15], allow_neg=True)

    def calc_softmodem_sunofdm_papr_regs(self, model):
        self._reg_write(model.vars.SUNOFDM_PAPR_ENPAPR, 0)
        self._reg_write(model.vars.SUNOFDM_PAPR_GAINSAT, 0)
        self._reg_write(model.vars.SUNOFDM_PAPR_GAINATT, 0)

    def calc_softmodem_sunoqpsk_version_regs(self, model):
        self._reg_write(model.vars.SUNOQPSK_VREGS_MAJORVERSION, 0)
        self._reg_write(model.vars.SUNOQPSK_VREGS_MINORVERSION, 0)

    def calc_softmodem_sunoqpsk(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        base_frequency_hz = model.vars.base_frequency_hz.value
        fcs_type_802154 = model.vars.fcs_type_802154.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OQPSK:
            sun_oqpsk_chiprate = model.vars.sun_oqpsk_chiprate.value
            band_freq_mhz_802154 = model.vars.band_freq_mhz_802154.value

            # Copy modulation type into SUNOQPSK register
            modulation_field = softmodem_modulation_type

            #Write OQPSK chiprate
            chiprate_field = sun_oqpsk_chiprate

            #Write band freq
            bandfreqmhz_field = band_freq_mhz_802154

            # Write FCS type
            macfcstype_field = fcs_type_802154

            # Write crystal frequency
            xtal_freq_field = xtal_frequency_hz / 1000

        else:
            modulation_field = model.vars.softmodem_modulation_type.var_enum.NONE
            chiprate_field = 0
            bandfreqmhz_field = 0
            macfcstype_field = 0
            xtal_freq_field = 0

        #Write the registers
        self._reg_write(model.vars.SUNOQPSK_CFG1_MODULATION, int(modulation_field))
        self._reg_write(model.vars.SUNOQPSK_CFG1_CHIPRATE, int(chiprate_field))
        self._reg_write(model.vars.SUNOQPSK_CFG1_BANDFREQMHZ, int(bandfreqmhz_field))
        self._reg_write(model.vars.SUNOQPSK_CFG2_MACFCSTYPE, int(macfcstype_field))
        self._reg_write(model.vars.SUNOQPSK_CFG2_XTALFREQ, int(xtal_freq_field))

    def calc_softmodem_legoqpsk_version_regs(self, model):
        self._reg_write(model.vars.LEGOQPSK_VREGS_MAJORVERSION, 0)
        self._reg_write(model.vars.LEGOQPSK_VREGS_MINORVERSION, 0)

    def calc_softmodem_legoqpsk(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        base_frequency_hz = model.vars.base_frequency_hz.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.LEGACY_OQPSK:
            sun_oqpsk_chiprate = model.vars.sun_oqpsk_chiprate.value

            # Copy modulation type into LEGOQPSK register
            modulation_field = softmodem_modulation_type

            # Write OQPSK chiprate
            chiprate_field = sun_oqpsk_chiprate

            # Write band freq
            bandfreqmhz_field = int(base_frequency_hz / 1e6)

            # Write crystal frequency
            xtal_freq_field = xtal_frequency_hz / 1000

        else:
            modulation_field = model.vars.softmodem_modulation_type.var_enum.NONE
            chiprate_field = 0
            bandfreqmhz_field = 0
            xtal_freq_field = 0

        # Write the registers
        self._reg_write(model.vars.LEGOQPSK_CFG1_MODULATION, int(modulation_field))
        self._reg_write(model.vars.LEGOQPSK_CFG1_CHIPRATE, int(chiprate_field))
        self._reg_write(model.vars.LEGOQPSK_CFG1_BANDFREQMHZ, int(bandfreqmhz_field))
        self._reg_write(model.vars.LEGOQPSK_CFG2_XTALFREQ, int(xtal_freq_field))

    def calc_softmodem_sunfsk_version_regs(self, model):
        self._reg_write(model.vars.SUNFSK_VREGS_MAJORVERSION, 0)
        self._reg_write(model.vars.SUNFSK_VREGS_MINORVERSION, 0)

    def calc_softmodem_sunfsk(self, model):

        #Here we will copy results from many TRECS register calculations into the soft demod registers
        #At some point we will want to stop calculating hard demod registers and make them don't care
        #When we do this we will have to separate calculation of the field values and the reg writes themselves
        #by making additional model variables and then replacing register accesses here with those variables

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        modulation_type = model.vars.modulation_type.value
        sun_fsk_sfd = model.vars.sun_fsk_sfd.value
        preamble_length = model.vars.preamble_length.value #This is the TX preamble length, ok for now
        syncword_length = model.vars.syncword_length.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_FSK:

            #This access is inside the SUN_FSK case as shaping_filter_param is not defined for some Mbus PHYs
            shaping_filter_param = model.vars.shaping_filter_param.value

            modulation_field = int(softmodem_modulation_type)
            physunfsksfd_field = int(sun_fsk_sfd)
            fskpreamblelength_field = int(preamble_length // 8)  # This field is denoted in bytes
            modscheme_field = 0 if modulation_type == model.vars.modulation_type.var_enum.FSK2 else 1 #Set to 0 for 2FSK
            bt_field = 0 if (shaping_filter_param < 0.6) else 1
            preambletimeout_field = 2 #fnicolas : preambletimeout which was not used in the FW is instead used to set abort_cnt_thd (to 2)
            preamblepatt_field =  0xAAAAAAAA #Always alternating 01 for SUN FSK - flipped in order
            sfdlen_field = syncword_length
            timingtrackgear_field = 1 # scale prompt phase's cost by 0.75 before comparing to early/late to avoid jitter
            timingtracksym_field = 32 # FW only supports 32 bit frame in timing search
            timingmintrans_field = 2 # optimized for 32 bit frame in timing search
            realtimesearch_field = 1 # this is currently not used in FW. We always do realtime search now.
            nbsymbbatch_field = 26 # Static number of symbols in batch. optimized in FW for WISUN packet structure. Should not be changed without updating FW first.
            chfilterswen_field = 1 # enable narrowing of channel filter after preamble detection. Not yet used in FW. We currently always narrow the filter.
            afcmode_field = 1 # set to 1-shot update to mixer. Not yet used in FW. We currently always use 1-shot to feedback estimate to digital mixer.
            xtalfreq_field = int(xtal_frequency_hz / 1000)

        else:
            modulation_field = 0
            physunfsksfd_field = 0
            fskpreamblelength_field = 0
            modscheme_field = 0
            bt_field = 0
            preambletimeout_field = 0
            preamblepatt_field = 0
            sfdlen_field = 0
            timingtrackgear_field = 0
            timingtracksym_field = 0
            timingmintrans_field = 0
            realtimesearch_field = 0
            nbsymbbatch_field = 0
            chfilterswen_field = 0
            afcmode_field = 0
            xtalfreq_field = 0

        self._reg_write(model.vars.SUNFSK_CFG1_MODULATION, modulation_field)
        self._reg_write(model.vars.SUNFSK_CFG1_PHYSUNFSKSFD, physunfsksfd_field)
        self._reg_write(model.vars.SUNFSK_CFG1_FSKPREAMBLELENGTH, fskpreamblelength_field)
        self._reg_write(model.vars.SUNFSK_CFG1_MODSCHEME, modscheme_field)
        self._reg_write(model.vars.SUNFSK_CFG1_BT, bt_field)
        self._reg_write(model.vars.SUNFSK_CFG5_PREAMBLETIMEOUT, preambletimeout_field)
        self._reg_write(model.vars.SUNFSK_CFG6_PREAMBLEPATT, preamblepatt_field)
        self._reg_write(model.vars.SUNFSK_CFG10_SFDLEN, sfdlen_field)
        self._reg_write(model.vars.SUNFSK_CFG11_TIMINGTRACKGEAR, timingtrackgear_field)
        self._reg_write(model.vars.SUNFSK_CFG12_TIMINGTRACKSYMB, timingtracksym_field)
        self._reg_write(model.vars.SUNFSK_CFG12_TIMINGMINTRANS, timingmintrans_field)
        self._reg_write(model.vars.SUNFSK_CFG12_REALTIMESEARCH, realtimesearch_field)
        self._reg_write(model.vars.SUNFSK_CFG12_NBSYMBBATCH, nbsymbbatch_field)
        self._reg_write(model.vars.SUNFSK_CFG13_CHFILTERSWEN, chfilterswen_field)
        self._reg_write(model.vars.SUNFSK_CFG13_AFCMODE, afcmode_field)
        self._reg_write(model.vars.SUNFSK_CFG15_XTALFREQ, xtalfreq_field)

    def calc_sunfsk_modindex(self, model):

        modulation_index = model.vars.modulation_index.value
        # modulation index = 0.25 + (Modulation Index field value) × 0.05
        modindex_field = int((modulation_index - 0.25) // 0.5) if modulation_index >= 0.25 else 0
        self._reg_write(model.vars.SUNFSK_CFG1_MODINDEX, modindex_field)

    def calc_sunfsk_fecsel_reg(self, model):

        if (model.vars.fec_tx_enable.value == model.vars.fec_tx_enable.var_enum.ENABLED):
            sun_fsk_fecsel = 1
        else:
            sun_fsk_fecsel = 0

        self._reg_write(model.vars.SUNFSK_CFG1_FECSEL, int(sun_fsk_fecsel))

    def calc_sunfsk_sdfcostthd_reg(self, model):
        # this function sets the threshold for frame (sync) detection
        # note that compared to hard modem frequency samples the soft modem samples are scaled by 4
        # value optimized for 16-bit SUN FSK sync words
        sync_len = model.vars.syncword_length.value
        val = 1500
        self._reg_write(model.vars.SUNFSK_CFG10_SFDCOSTTHD, round(val/16*sync_len))

    def calc_sunfsk_sfderrors_reg(self, model):
        # this function sets the number of bit errors allowed in the sync word for valid frame (sync) detection
        syncword_length = model.vars.syncword_length.value
        # value optimized for SUN FSK where detected sync words determines if FEC is enabled or disabled
        val = round(syncword_length/8)
        self._reg_write(model.vars.SUNFSK_CFG11_SFDERRORS, val)

    def calc_sunfsk_sfdtimeout_reg(self, model):
        # this function sets the timeout in symbols between timing (preamble) detection and frame (sync) detection
        preamble_length = model.vars.preamble_length.value
        sync_len = model.vars.syncword_length.value
        batch_size = model.vars.SUNFSK_CFG12_NBSYMBBATCH.value

        # set timeout to preamble length + sync word length + number of symbols processed in one batch
        self._reg_write(model.vars.SUNFSK_CFG11_SFDTIMEOUT, preamble_length + sync_len + batch_size)

    def calc_sunfsk_afcscale_reg(self, model):
        # AFSCALE has a slightly different meaning compared to the HW AFCSCALE register
        # In HW this value holds the value needed to translate estimated offset in terms of frequency scale (nominal 64)
        # to digital mixer scale. Sometimes that value is scaled to feedback more or less than the nominal estimate.
        # In the soft modem the translation part is handled by FW and this scale only determines the desired scale.
        # 1024 results in no scaling. 512 would feeback only half of the estimated offset to the digital mixer.
        val = 1024
        self._reg_write(model.vars.SUNFSK_CFG13_AFCSCALE, val)

    def calc_sunfsk_afcadjlim_reg(self, model):
        # adjustment limit disabled in soft modem SUN FSK PHYs until we see the need for it
        #freq_limit = model.vars.freq_offset_hz.value
        freq_limit = 0
        digmix_res = model.vars.digmix_res_actual.value
        self._reg_write(model.vars.SUNFSK_CFG14_AFCADJLIM, int(round(freq_limit / digmix_res)))

    def calc_sunfsk_afcadjperiod_reg(self, model):
        # continues frequency tracking disabled in soft modem SUN FSK PHYs until we see the need for it
        # if non zero frequency is estimated and updated every period 32-bit intervals during payload decoding
        # e.g. period = 1 updated every 32 bits, period = 2 update every 64 bits etc.
        period = 0
        self._reg_write(model.vars.SUNFSK_CFG15_AFCADJPERIOD, period)

    def calc_sunfsk_afcostthd_reg(self, model):
        # when frequency tracking is enabled this threshold determines if the frequency estimate should be used or not
        # if the cost value is higher than this threshold the estimate is deemed unreliable and not used
        # in this case we skip that periods update for frequency offset
        # cost value is calclated over 32 bits so this threshold should be set accordingly
        # if tracking is disabled with AFCADJPERIOD=0 this field is not used
        val = 8
        self._reg_write(model.vars.SUNFSK_CFG15_AFCCOSTTHD, val)

    def calc_sunfsk_veqen_reg(self, model):
        # this function sets the VEQ mode: 0 for no Viterbi equalization, 1 for hard decision, 2 for soft decision
        mi = model.vars.modulation_index.value

        veqen = 2 if mi < 1.0 else 0

        self._reg_write(model.vars.SUNFSK_CFG2_VEQEN, veqen)

    def calc_sunfsk_osr_reg(self, model):
        # this function sets the oversampling rate at the SW demod
        osr = int(model.vars.oversampling_rate_actual.value)
        self._reg_write(model.vars.SUNFSK_CFG3_OSR, osr)

    def calc_sunfsk_phscale_reg(self, model):
        # this function sets the shift value to adjust phase value from the CORDIC
        mi = model.vars.modulation_index.value
        if mi > 0:
            phscale = int(round(log(2 * mi, 2)))
        else:
            phscale = 0

        phscale = 0 if phscale < 0 else phscale

        self._reg_write(model.vars.SUNFSK_CFG3_PHASESCALE, phscale)

    def calc_sunfsk_preamblelen_reg(self, model):
        # this function set the preamble length used in timing search
        preamsch_len = 32
        self._reg_write(model.vars.SUNFSK_CFG5_PREAMBLELEN, preamsch_len)

    def calc_sunfsk_preamblecntthd_reg(self, model):
        # this function sets the number of times the cost value must go velow PREAMBLECOSTTHD within PREABMLECNTWIN
        # symbols for timing detection
        preamsch_len = model.vars.preamsch_len.value
        reg = 2 if preamsch_len <= 16 else 3
        self._reg_write(model.vars.SUNFSK_CFG4_PREAMBLECNTTHD, reg)

    def calc_sunfsk_preamblecostthd_reg(self, model):
        # this function sets the threshold for preamble detection
        # val below is optimized for 32-bit SUN FSK preamble
        preamsch_len = model.vars.preamsch_len.value
        #val = 3000
        val = 3072 #temporary fix as PREAMBLECOSTMAX is on 8 bits (instead of 16) and then set to 12*256=3072
        self._reg_write(model.vars.SUNFSK_CFG4_PREAMBLECOSTTHD, round(val/32*preamsch_len))

    def calc_sunfsk_preamblecntwin_reg(self, model):
        # this function sets window size in symbols over which we count the number of threshold crossing for valid
        # timing (preamble) detection
        # cnt below is optmized for 32-bit SUN FSK premble
        preamsch_len = model.vars.preamsch_len.value
        cnt = 12
        self._reg_write(model.vars.SUNFSK_CFG4_PREAMBLECNTWIN, round(cnt/32*preamsch_len))

    def calc_sunfsk_preambleerrors_reg(self, model):
        # this function sets the number of bit errors we allow for valid preamble (timing) detection
        # errors below is optimized for 32-bit SUN FSK preamble
        # SNR is lower with FEC enabled which can cause bit errors in the preamble
        # setting this to 6 prevents us from missing frames due to bit errors in the preamble
        preamsch_len = model.vars.preamsch_len.value
        errors = 6
        self._reg_write(model.vars.SUNFSK_CFG5_PREAMBLEERRORS, round(errors/32*preamsch_len))

    def calc_sunfsk_preamblecostmax_reg(self, model):
        # this function sets threshold for min cost above which we ignore timing (preamble) detection
        # currently set to the same value as PREAMBLECOSTTHD which means this is inactive
        # PREAMBLECOSTTHD is set higher than usual because when FEC is enabled and SNR is low the cost can be high
        #val = 3000
        val = 12 #temporary fix as PREAMBLECOSTMAX is on 8 bits instead of 16 : 12*256=3072
        self._reg_write(model.vars.SUNFSK_CFG7_PREAMBLECOSTMAX, val)

    def calc_sunfsk_preamblefreqlim_reg(self, model):
        # this function sets the limit on the estimated frequency offset when detecting the preamble
        # this feature is currently disabled by setting this register to 0
        self._reg_write(model.vars.SUNFSK_CFG7_PREAMBLEFREQLIM, 0)

    def calc_sunfsk_sfd1_reg(self, model):
        # this function writes the first sync word in reverse bit order compared to the 802.15.4 definition
        # this is the sync word for coded format
        sync_len = model.vars.syncword_length.value
        sync = CALC_Frame_Detect.flip_bits(model.vars.syncword_1.value, sync_len)
        self._reg_write(model.vars.SUNFSK_CFG8_SFD1, sync)

    def calc_sunfsk_sfd2_reg(self, model):
        # this function writes the second sync word in reverse bit order compared to the 802.15.4 definition
        # this is the sync word for uncoded format
        sync_len = model.vars.syncword_length.value
        sync = CALC_Frame_Detect.flip_bits(model.vars.syncword_0.value, sync_len)

        self._reg_write(model.vars.SUNFSK_CFG9_SFD2, sync)

    def calc_softmodem_ksi_reg(self, model):
        # this function writes ksi values

        ksi1 = model.vars.ksi1.value
        ksi2 = model.vars.ksi2.value
        ksi3 = model.vars.ksi3.value
        ksi3wb = model.vars.ksi3wb.value

        self._reg_sat_write(model.vars.SUNFSK_CFG2_KSI1, ksi1)
        self._reg_sat_write(model.vars.SUNFSK_CFG2_KSI2, ksi2)
        self._reg_sat_write(model.vars.SUNFSK_CFG2_KSI3, ksi3)
        self._reg_sat_write(model.vars.SUNFSK_CFG3_KSI3W, ksi3wb)

    def calc_softmodem_clken(self, model):
        #Read in model vars
        demod_select = model.vars.demod_select.value
        #Need to set CLKEN=1 for RTL sims, but this is ignored in rail_scripts
        #Avoid disabling clock for hardmodem PHYs as this could impact LabATE testing
        if demod_select == model.vars.demod_select.var_enum.SOFT_DEMOD:
            self._reg_write(model.vars.RAC_SOFTMCTRL_CLKEN, 1)
        else:
            self._reg_do_not_care(model.vars.RAC_SOFTMCTRL_CLKEN)

    def calc_sunfsk_mode_reg(self, model):
        # MODE = 0 forces FW to read parameters from the calculator settings of SUNFSK_CFG registers
        self._reg_sat_write(model.vars.SUNFSK_CFG16_MODE, 0)

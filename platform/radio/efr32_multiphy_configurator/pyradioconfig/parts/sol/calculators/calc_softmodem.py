from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum

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

        self._addModelVariable(model, 'cw_fft_analyze', int, ModelVariableFormat.DECIMAL,
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
            elif modulation_type == model.vars.modulation_type.var_enum.FSK2:
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

        #For the Wi-SUN Profiles, calc the CRC from the FCS that is specified as a Profile Input
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

    def calc_softmodem_cw(self, model):

        #Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value
        dac_freq_actual = model.vars.dac_freq_actual.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.CW:

            model.vars.cw_amp.value = 24000  # Set default amplitude to 24000 (any forced value will override)
            model.vars.cw_nfft_log2.value = 9 # Set FFT size to 512
            model.vars.cw_fft_analyze.value = model.vars.cw_fft_analyze.var_enum.NONE

            do_not_care = False
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
            do_not_care = True
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
        self._reg_write(model.vars.CW_CFG1_MODULATION, int(modulation_field), do_not_care=do_not_care)
        self._reg_write(model.vars.CW_CFG1_NFFTLOG2, int(nfft_log2_field), do_not_care=do_not_care)
        self._reg_write(model.vars.CW_CFG1_DUALPATH, int(dual_path_field), do_not_care=do_not_care)
        self._reg_write(model.vars.CW_CFG1_FFTANALYZE, int(fft_analyze_field), do_not_care=do_not_care)
        self._reg_write(model.vars.CW_CFG1_SIGTYPE, int(sig_type_field), do_not_care=do_not_care)
        self._reg_write(model.vars.CW_CFG2_FREQ, int(freq_field), do_not_care=do_not_care)
        self._reg_write(model.vars.CW_CFG2_AMP, int(amp_field), do_not_care=do_not_care)
        self._reg_write(model.vars.CW_CFG3_XTALFREQ, int(xtal_freq_field), do_not_care=do_not_care)

    def calc_softmodem_sunofdm(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        ofdm_option = model.vars.ofdm_option.value
        ofdm_interleaving_depth = model.vars.ofdm_interleaving_depth.value
        fcs_type_802154 = model.vars.fcs_type_802154.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            do_not_care = False

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
            do_not_care = True
            modulation_field = model.vars.softmodem_modulation_type.var_enum.NONE
            ofdmoption_field = 0
            interleaving_field = 0
            macfcstype_field = 0
            xtal_freq_field = 0

        #Write the registers
        self._reg_write(model.vars.SUNOFDM_CFG1_MODULATION, int(modulation_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNOFDM_CFG1_OFDMOPTION, int(ofdmoption_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNOFDM_CFG1_INTERLEAVING, int(interleaving_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNOFDM_CFG1_MACFCSTYPE, int(macfcstype_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNOFDM_CFG1_XTALFREQ, int(xtal_freq_field), do_not_care=do_not_care)

    def calc_softmodem_sunoqpsk(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        base_frequency_hz = model.vars.base_frequency_hz.value
        fcs_type_802154 = model.vars.fcs_type_802154.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OQPSK:
            do_not_care = False
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
            do_not_care = True
            modulation_field = model.vars.softmodem_modulation_type.var_enum.NONE
            chiprate_field = 0
            bandfreqmhz_field = 0
            macfcstype_field = 0
            xtal_freq_field = 0

        #Write the registers
        self._reg_write(model.vars.SUNOQPSK_CFG1_MODULATION, int(modulation_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNOQPSK_CFG1_CHIPRATE, int(chiprate_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNOQPSK_CFG1_BANDFREQMHZ, int(bandfreqmhz_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNOQPSK_CFG2_MACFCSTYPE, int(macfcstype_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNOQPSK_CFG2_XTALFREQ, int(xtal_freq_field), do_not_care=do_not_care)

    def calc_softmodem_legoqpsk(self, model):

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        base_frequency_hz = model.vars.base_frequency_hz.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.LEGACY_OQPSK:
            do_not_care = False
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
            do_not_care = True
            modulation_field = model.vars.softmodem_modulation_type.var_enum.NONE
            chiprate_field = 0
            bandfreqmhz_field = 0
            xtal_freq_field = 0

        # Write the registers
        self._reg_write(model.vars.LEGOQPSK_CFG1_MODULATION, int(modulation_field), do_not_care=do_not_care)
        self._reg_write(model.vars.LEGOQPSK_CFG1_CHIPRATE, int(chiprate_field), do_not_care=do_not_care)
        self._reg_write(model.vars.LEGOQPSK_CFG1_BANDFREQMHZ, int(bandfreqmhz_field), do_not_care=do_not_care)
        self._reg_write(model.vars.LEGOQPSK_CFG2_XTALFREQ, int(xtal_freq_field), do_not_care=do_not_care)

    def calc_softmodem_sunfsk(self, model):

        #Here we will copy results from many TRECS register calculations into the soft demod registers
        #At some point we will want to stop calculating hard demod registers and make them don't care
        #When we do this we will have to separate calculation of the field values and the reg writes themselves
        #by making additional model variables and then replacing register accesses here with those variables

        # Read in model variables
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        sun_fsk_fecsel = model.vars.sun_fsk_fecsel.value
        sun_fsk_sfd = model.vars.sun_fsk_sfd.value
        preamble_length = model.vars.preamble_length.value #This is the TX preamble length, ok for now
        modulation_index = model.vars.modulation_index.value
        trecsosr = model.vars.MODEM_TRECSCFG_TRECSOSR.value
        harddecision = model.vars.MODEM_VITERBIDEMOD_HARDDECISION.value
        ksi1 = model.vars.MODEM_VITERBIDEMOD_VITERBIKSI1.value
        ksi2 = model.vars.MODEM_VITERBIDEMOD_VITERBIKSI2.value
        ksi3 = model.vars.MODEM_VITERBIDEMOD_VITERBIKSI3.value
        ksi3w = model.vars.ksi3wb_actual.value
        phscale = model.vars.MODEM_TRECPMDET_PHSCALE.value
        pmmincostthd = model.vars.MODEM_TRECPMDET_PMMINCOSTTHD.value
        rtschwin = model.vars.MODEM_REALTIMCFE_RTSCHWIN.value
        pmcostvalthd = model.vars.MODEM_TRECPMDET_PMCOSTVALTHD.value
        preamsch_len = model.vars.preamsch_len.value
        errors_in_timing_window = model.vars.errors_in_timing_window.value
        pmtimeoutsel = model.vars.MODEM_TRECPMDET_PMTIMEOUTSEL.value
        vtfrqlim = model.vars.MODEM_VTCORRCFG1_VTFRQLIM.value
        pmtimlosthd = model.vars.MODEM_PHDMODCTRL_PMTIMLOSTHD.value
        syncword_0 = model.vars.syncword_0.value
        syncword_1 = model.vars.syncword_1.value
        syncword_length = model.vars.syncword_length.value
        mincostthd = model.vars.MODEM_REALTIMCFE_MINCOSTTHD.value
        frmschtime = model.vars.MODEM_FRMSCHTIME_FRMSCHTIME.value
        syncerrors = model.vars.MODEM_CTRL1_SYNCERRORS.value
        timgear = model.vars.MODEM_VTTRACK_TIMGEAR.value
        trackingwin = model.vars.MODEM_REALTIMCFE_TRACKINGWIN.value
        timtrackthd = model.vars.MODEM_VTTRACK_TIMTRACKTHD.value
        afc_scale = model.vars.afc_scale.value
        afcadjlim = model.vars.MODEM_AFCADJLIM_AFCADJLIM.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_FSK:
            #This access is inside the SUN_FSK case as shaping_filter_param is not defined for some Mbus PHYs
            shaping_filter_param = model.vars.shaping_filter_param.value

            do_not_care = False
            modulation_field = softmodem_modulation_type
            fecsel_field = sun_fsk_fecsel
            physunfsksfd_field = sun_fsk_sfd
            fskpreamblelength_field = int(preamble_length // 8) #This field is denoted in bytes
            modscheme_field = 0 #Set to 0 for 2FSK
            bt_field = 0 if (shaping_filter_param < 0.6) else 1
            modindex_field = int((modulation_index - 0.25)//0.5) # modulation index = 0.25 + (Modulation Index field value) × 0.05
            osr_field = trecsosr
            veqen_field = 1 if (harddecision == 0) else 0
            ksi1_field = ksi1
            ksi2_field = ksi2
            ksi3_field = ksi3
            ksi3w_field = int(ksi3w)
            phasescale_field = phscale
            preamblecostthd_field = pmmincostthd
            preamblecntwin_field = rtschwin
            preamblecntthd_field = pmcostvalthd
            preamblelen_field = preamsch_len #Use calculated preamble search length
            preambleerrors_field = errors_in_timing_window
            preambletimeout_field = 16 + 8*pmtimeoutsel #pmtimeoutsel value in symbols
            preamblepatt_field = 0x55555555 #Always alternating 01 for SUN FSK
            preamblefreqlim_field = vtfrqlim
            preamblecostmax_field = pmtimlosthd
            sfd1_field = syncword_0
            sfd2_field = syncword_1
            sfdlen_field = syncword_length
            sfdcostthd_field = mincostthd
            sfdtimeout_field = frmschtime
            sfderrors_field = syncerrors
            timtrackgear_field = timgear
            timtracksymb_field = (trackingwin + 1)  * 4
            timmintrans_field = timtrackthd
            realtimesearch_field = 1 #Always enable real time search for now
            nsymbbatch_field = 26 #Static number of symbols in batch for now
            chfiltswen_field = 1 #Enable BW narrowing (assume sufficient preamble for AFC)
            afcmode_field = 1 #digmix one-shot
            afcscale_field = int(afc_scale)
            afcadjlim_field = afcadjlim
            afcadjperiod_field = 1 #Hard coded for now
            afccostthd_field = pmcostvalthd
            xtal_freq_field = xtal_frequency_hz / 1000
        else:
            do_not_care = True
            modulation_field = model.vars.softmodem_modulation_type.var_enum.NONE
            fecsel_field = model.vars.sun_fsk_fecsel.var_enum.NONE
            physunfsksfd_field = 0
            fskpreamblelength_field = 0
            modscheme_field = 0
            bt_field = 0
            modindex_field = 0
            osr_field = 0
            veqen_field = 0
            ksi1_field = 0
            ksi2_field = 0
            ksi3_field = 0
            ksi3w_field = 0
            phasescale_field = 0
            preamblecostthd_field = 0
            preamblecntwin_field = 0
            preamblecntthd_field = 0
            preamblelen_field = 0
            preambleerrors_field = 0
            preambletimeout_field = 0
            preamblepatt_field = 0
            preamblefreqlim_field = 0
            preamblecostmax_field = 0
            sfd1_field = 0
            sfd2_field = 0
            sfdlen_field = 0
            sfdcostthd_field = 0
            sfdtimeout_field = 0
            sfderrors_field = 0
            timtrackgear_field = 0
            timtracksymb_field = 0
            timmintrans_field = 0
            realtimesearch_field = 0
            nsymbbatch_field = 0
            chfiltswen_field = 0
            afcmode_field = 0
            afcscale_field = 0
            afcadjlim_field = 0
            afcadjperiod_field = 0
            afccostthd_field = 0
            xtal_freq_field = 0

        # Write the registers
        self._reg_write(model.vars.SUNFSK_CFG1_MODULATION, int(modulation_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG1_FECSEL, int(fecsel_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG1_PHYSUNFSKSFD, int(physunfsksfd_field), do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG1_FSKPREAMBLELENGTH, fskpreamblelength_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG1_MODSCHEME, modscheme_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG1_BT, bt_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG1_MODINDEX, modindex_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG3_OSR, osr_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG2_VEQEN, veqen_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG2_KSI1, ksi1_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG2_KSI2, ksi2_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG2_KSI3, ksi3_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG3_KSI3W, ksi3w_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG3_PHASESCALE, phasescale_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG4_PREAMBLECOSTTHD, preamblecostthd_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG4_PREAMBLECNTWIN, preamblecntwin_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG4_PREAMBLECNTTHD, preamblecntthd_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG5_PREAMBLELEN, preamblelen_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG5_PREAMBLEERRORS, preambleerrors_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG5_PREAMBLETIMEOUT, preambletimeout_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG6_PREAMBLEPATT, preamblepatt_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG7_PREAMBLEFREQLIM, preamblefreqlim_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG7_PREAMBLECOSTMAX, preamblecostmax_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG8_SFD1, sfd1_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG9_SFD2, sfd2_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG10_SFDLEN, sfdlen_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG10_SFDCOSTTHD, sfdcostthd_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG11_SFDTIMEOUT, sfdtimeout_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG11_SFDERRORS, sfderrors_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG11_TIMINGTRACKGEAR, timtrackgear_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG12_TIMINGTRACKSYMB, timtracksymb_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG12_TIMINGMINTRANS, timmintrans_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG12_REALTIMESEARCH, realtimesearch_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG12_NBSYMBBATCH, nsymbbatch_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG13_CHFILTERSWEN, chfiltswen_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG13_AFCMODE, afcmode_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG13_AFCSCALE, afcscale_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG14_AFCADJLIM, afcadjlim_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG15_AFCADJPERIOD, afcadjperiod_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG15_AFCCOSTTHD, afccostthd_field, do_not_care=do_not_care)
        self._reg_write(model.vars.SUNFSK_CFG15_XTALFREQ, int(xtal_freq_field), do_not_care=do_not_care)

    def calc_softmodem_clken(self, model):

        #Read in model vars
        demod_select = model.vars.demod_select.value

        #Need to set CLKEN=1 for RTL sims, but this is ignored in rail_scripts
        #Avoid disabling clock for hardmodem PHYs as this could impact LabATE testing
        if demod_select == model.vars.demod_select.var_enum.SOFT_DEMOD:
            self._reg_write(model.vars.RAC_SOFTMCTRL_CLKEN, 1)
        else:
            self._reg_do_not_care(model.vars.RAC_SOFTMCTRL_CLKEN)

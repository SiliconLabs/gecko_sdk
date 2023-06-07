from pyradioconfig.parts.ocelot.calculators.calc_viterbi import CALC_Viterbi_ocelot


class CALC_Viterbi_Margay(CALC_Viterbi_ocelot):

    def calc_freqtrackmode_reg(self, model):

        vtdemoden = model.vars.MODEM_VITERBIDEMOD_VTDEMODEN.value
        remoden = (model.vars.MODEM_PHDMODCTRL_REMODEN.value == 1)
        rtschmode = model.vars.MODEM_REALTIMCFE_RTSCHMODE.value
        freq_offset_hz = model.vars.freq_offset_hz.value
        deviation = model.vars.deviation.value

        if deviation != 0:
            large_freq_offset = (freq_offset_hz / deviation) > 2
        else:
            large_freq_offset = False

        if vtdemoden:
            if (rtschmode == 1) and not remoden:
                # Special case for dual syncword detection case where hard slicing on syncword is required
                # When RTSCHMODE=1, we can not use CFE for additional AFC corrections during syncword
                freqtrackmode = 3
            else:
                freqtrackmode = 1
        else:
            freqtrackmode = 0

        self._reg_write(model.vars.MODEM_VTTRACK_FREQTRACKMODE, freqtrackmode)

    def calc_realtimcfe_trackingwin(self, model):
        #This function calculates the REALTIMCFE_TRACKINGWIN reg field

        #Read in model variables
        baudrate_tol_ppm = model.vars.baudrate_tol_ppm.value
        vtdemoden = model.vars.MODEM_VITERBIDEMOD_VTDEMODEN.value
        freq_offset_hz = model.vars.freq_offset_hz.value
        modulation_index = model.vars.modulation_index.value
        baudrate = model.vars.baudrate.value

        if vtdemoden:
            #If the tol request is at least 5000ppm, then reduce the tracking win size
            if baudrate_tol_ppm >= 5000:
                trackingwin = 5
            elif (freq_offset_hz / baudrate) > 0.57 and modulation_index <= 0.5:
                trackingwin = 3 #Do not set below 3 as this causes floor in Apps + Design setups
            else:
                trackingwin = 7
        else:
            trackingwin = 0

        #Write the reg
        self._reg_write(model.vars.MODEM_REALTIMCFE_TRACKINGWIN, trackingwin)

    def calc_pmoffset_reg(self, model):

        afc_oneshot_enabled = (model.vars.MODEM_AFC_AFCONESHOT.value == 1)
        rtschmode = model.vars.MODEM_REALTIMCFE_RTSCHMODE.value
        osr = model.vars.MODEM_TRECSCFG_TRECSOSR.value
        pmwinsize = model.vars.pmacquingwin_actual.value

        if (rtschmode==1) and afc_oneshot_enabled:
            #Special case for dual syncword detection case where hard slicing on syncword is required
            #In this case we choose a minimal PMOFFSET to avoid a bad estimate due to AFC transient
            pmoffset = 2
        else:
            # + 2 for processing delay. See expsynclen register description. These are used in the same way.
            pmoffset =  osr * pmwinsize + 2

        self._reg_write(model.vars.MODEM_TRECSCFG_PMOFFSET,  pmoffset)


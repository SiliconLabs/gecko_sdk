from pyradioconfig.parts.ocelot.calculators.calc_viterbi import CALC_Viterbi_ocelot
from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr

class Calc_Viterbi_Bobcat(CALC_Viterbi_ocelot):

    def calc_synthafc_reg(self, model):

        demod_select = model.vars.demod_select.value
        afc1shot_en = model.vars.MODEM_AFC_AFCONESHOT.value
        ber_force_freq_comp_off = model.vars.ber_force_freq_comp_off.value
        do_not_care = False

        if ber_force_freq_comp_off:
            reg = 1
        # : If Legacy, set if oneshot afc is enabled
        elif demod_select == model.vars.demod_select.var_enum.LEGACY:
            if afc1shot_en:
                reg = 1
            else:
                reg = 0
        # : If TRECS, always set SYNTHAFC = 1
        elif demod_select == model.vars.demod_select.var_enum.TRECS_VITERBI or \
                demod_select == model.vars.demod_select.var_enum.TRECS_SLICER:
            reg = 1
        # : Not used by BCR, Coherent, or Longrange
        else:
            do_not_care = True
            reg = 0

        self._reg_write(model.vars.MODEM_VITERBIDEMOD_SYNTHAFC, reg, do_not_care=do_not_care)

    def calc_swcoeffen_reg(self, model):

        afc1shot_en = model.vars.MODEM_AFC_AFCONESHOT.value
        aox_en = model.vars.aox_enable.value == model.vars.aox_enable.var_enum.ENABLED

        if afc1shot_en and aox_en:
            LogMgr.Error('both AFC oneshot and AoX cannot be simultaneously enabled as they both use the second CHF coefficient set')

        swcoeffen = 1 if afc1shot_en or aox_en else 0 # affects the channel filter switching only
        ksi3swenable = afc1shot_en
        # don't switch for aox, as KSI3 switch mechanism is based on dsa/preamble, but the aox channel switch is based on the CTE
        # Don't care about the demodulated data during CTE, so just leave it on the KSI3

        self._reg_write(model.vars.MODEM_CHFCTRL_SWCOEFFEN, swcoeffen)
        self._reg_write(model.vars.MODEM_VTCORRCFG1_KSI3SWENABLE, ksi3swenable)

    def calc_pmoffset_reg(self, model):
        """
        Calcs moved from Viper to handle dual syncword detection
        see https://jira.silabs.com/browse/MCUW_RADIO_CFG-2183
        """

        afc_oneshot_enabled = (model.vars.MODEM_AFC_AFCONESHOT.value == 1)
        rtschmode = model.vars.MODEM_REALTIMCFE_RTSCHMODE.value
        osr = model.vars.MODEM_TRECSCFG_TRECSOSR.value
        pmwinsize = model.vars.pmacquingwin_actual.value

        if (rtschmode == 1) and afc_oneshot_enabled:
            # Special case for dual syncword detection case where hard slicing on syncword is required
            # In this case we choose a minimal PMOFFSET to avoid a bad estimate due to AFC transient
            pmoffset = 2
        else:
            # + 2 for processing delay. See expsynclen register description. These are used in the same way.
            pmoffset = osr * pmwinsize + 2

        self._reg_write(model.vars.MODEM_TRECSCFG_PMOFFSET, pmoffset)

    def calc_freqtrackmode_reg(self, model):
        # Copied old Ocelot method to avoid regression impact on later parts
        vtdemoden = model.vars.MODEM_VITERBIDEMOD_VTDEMODEN.value

        if vtdemoden:
            freqtrackmode = 1
        else:
            freqtrackmode = 0

        self._reg_write(model.vars.MODEM_VTTRACK_FREQTRACKMODE, freqtrackmode)
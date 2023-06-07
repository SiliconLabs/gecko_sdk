from pyradioconfig.parts.bobcat.calculators.calc_viterbi import Calc_Viterbi_Bobcat

class Calc_Viterbi_Viper(Calc_Viterbi_Bobcat):

    acqwin_unit = 1

    def calc_pmoffset_reg(self, model):

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

    def calc_realtimcfe_extenschbyp_reg(self, model):
        pass
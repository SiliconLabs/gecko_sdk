from pyradioconfig.parts.common.profiles.bobcat_regs import build_modem_regs_bobcat
from pycalcmodel.core.output import ModelOutput, ModelOutputType

def build_modem_regs_viper(model, profile):
    build_modem_regs_bobcat(model, profile)
    build_modem_regs_viper_only(model, profile)

def build_modem_regs_viper_only(model, profile):
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXCORR_TXDGAIN6DB          , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXCORR.TXDGAIN6DB'                 ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXCORR_TXDGAIN             , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXCORR.TXDGAIN'                    ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXCORR_TXGAINIMB           , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXCORR.TXGAINIMB'                  ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXCORR_TXPHSIMB            , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXCORR.TXPHSIMB'                   ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXCORR_TXFREQCORR          , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXCORR.TXFREQCORR'                 ))

    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_FORCECLKEN          , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.FORCECLKEN'                 ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXIQIMBEN           , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXIQIMBEN'                  ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXINTPEN            , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXINTPEN'                   ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXDSEN              , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXDSEN'                     ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXIQSWAP            , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXIQSWAP'                   ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXDACFORMAT         , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXDACFORMAT'                ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXDACFORCE          , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXDACFORCE'                 ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXDCI               , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXDCI'                      ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXDCQ               , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXDCQ'                      ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_BR2M                , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.BR2M'                       ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_TXMISC_TXMOD              , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.TXMISC.TXMOD'                       ))

    #
    # profile.outputs.append(ModelOutput(model.vars.MODEM_CTRL1_COMPMODE, '',          ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CTRL1.COMPMODE'            ))
    # profile.outputs.append(ModelOutput(model.vars.MODEM_CTRL1_TXSYNC, '',          ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CTRL1.TXSYNC'            ))
    # profile.outputs.append(ModelOutput(model.vars.MODEM_CTRL1_FREQOFFESTLIM, '',     ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CTRL1.FREQOFFESTLIM'       ))
    # profile.outputs.append(ModelOutput(model.vars.MODEM_CTRL1_FREQOFFESTPER, '',     ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CTRL1.FREQOFFESTPER'       ))
    # profile.outputs.append(ModelOutput(model.vars.MODEM_CTRL1_PHASEDEMOD, '',        ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CTRL1.PHASEDEMOD'          ))
    # profile.outputs.append(ModelOutput(model.vars.MODEM_CTRL1_RESYNCPER, '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CTRL1.RESYNCPER'           ))
    # profile.outputs.append(ModelOutput(model.vars.MODEM_CTRL1_SYNC1INV, '',          ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CTRL1.SYNC1INV'            ))
    # profile.outputs.append(ModelOutput(model.vars.MODEM_CTRL1_SYNCDATA, '',          ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CTRL1.SYNCDATA'            ))

    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNC2_SYNC2                , '',         ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNC2.SYNC2'                       ))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNCWORDCTRL_SYNC0BITS, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNCWORDCTRL.SYNC0BITS'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNCWORDCTRL_SYNC1BITS, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNCWORDCTRL.SYNC1BITS'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNCWORDCTRL_SYNC2BITS, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNCWORDCTRL.SYNC2BITS'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNCWORDCTRL_SYNC0ERRORS, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNCWORDCTRL.SYNC0ERRORS'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNCWORDCTRL_SYNC1ERRORS, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNCWORDCTRL.SYNC1ERRORS'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNCWORDCTRL_SYNC2ERRORS, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNCWORDCTRL.SYNC2ERRORS'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNCWORDCTRL_DUALSYNC, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNCWORDCTRL.DUALSYNC'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SYNCWORDCTRL_TRISYNC, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SYNCWORDCTRL.TRISYNC'))

    if model.part_family.lower() not in ["rainier"]:
        profile.outputs.append(ModelOutput(model.vars.MODEM_SRCCHF_CHMUTETIMER, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SRCCHF.CHMUTETIMER'))

    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCTRL_EHDSSSEN, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCTRL.EHDSSSEN'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCTRL_DSSSTIMEACQUTHD, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCTRL.DSSSTIMEACQUTHD'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCTRL_FOEBIAS, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCTRL.FOEBIAS'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCTRL_FREQCORREN, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCTRL.FREQCORREN'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCTRL_DSSSFRQLIM, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCTRL.DSSSFRQLIM'))

    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG0_DSSSPATT, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG0.DSSSPATT'))

    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG1_DSSSEXPSYNCLEN, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG1.DSSSEXPSYNCLEN'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG1_DSSSCORRTHD, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG1.DSSSCORRTHD'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG1_DSSSDSAQTHD, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG1.DSSSDSAQTHD'))

    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG2_DSSSTIMCORRTHD, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG2.DSSSTIMCORRTHD'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG2_DSSSFRTCORRTHD, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG2.DSSSFRTCORRTHD'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG2_DSSSTRACKINGWIN,'', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG2.DSSSTRACKINGWIN'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG2_DSSSCORRSCHWIN, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG2.DSSSCORRSCHWIN'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_EHDSSSCFG2_ONESYMBOLMBDD,  '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.EHDSSSCFG2.ONESYMBOLMBDD'))

    if model.part_family.lower() not in ["rainier"]:
        profile.outputs.append(ModelOutput(model.vars.MODEM_PHDMODCTRL_FASTHOPPINGEN,  '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.PHDMODCTRL.FASTHOPPINGEN'))
        profile.outputs.append(ModelOutput(model.vars.MODEM_CMD_HOPPINGSTART,  '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.CMD.HOPPINGSTART'))
        profile.outputs.append(ModelOutput(model.vars.MODEM_DIGMIXCTRL_FWHOPPING,  '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.DIGMIXCTRL.FWHOPPING'))

    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL0_SIMODE, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL0.SIMODE'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL0_NOISETHRESH, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL0.NOISETHRESH'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL0_PEAKNUMTHRESHLW, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL0.PEAKNUMTHRESHLW'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL0_SWPEAKNUMADJ, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL0.SWPEAKNUMADJ'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL0_NOISETHRESHADJ, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL0.NOISETHRESHADJ'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL0_FREQNOMINAL, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL0.FREQNOMINAL'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL0_NDFOCAL, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL0.NDFOCAL'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_SUPERCHIPTOLERANCE, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.SUPERCHIPTOLERANCE'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_SMALLSAMPLETHRESH, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.SMALLSAMPLETHRESH'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_PEAKNUMP2ADJ, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.PEAKNUMP2ADJ'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_FASTMODE, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.FASTMODE'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_TWOSYMBEN, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.TWOSYMBEN'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_ZCEN, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.ZCEN'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_ZCSAMPLETHRESH, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.ZCSAMPLETHRESH'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_SOFTCLIPBYPASS, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.SOFTCLIPBYPASS'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL1_SOFTCLIPTHRESH, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL1.SOFTCLIPTHRESH'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_SIRSTAGCMODE, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.SIRSTAGCMODE'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_SIRSTPRSMODE, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.SIRSTPRSMODE'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_SIRSTCCAMODE, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.SIRSTCCAMODE'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_DISSIFRAMEDET, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.DISSIFRAMEDET'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_AGCRSTUPONSI, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.AGCRSTUPONSI'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_SHFTWIN, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.SHFTWIN'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_SUPERCHIPNUM, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.SUPERCHIPNUM'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_CORRNUM, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.CORRNUM'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICTRL2_NARROWPULSETHRESH, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICTRL2.NARROWPULSETHRESH'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICORR_CORRTHRESH, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICORR.CORRTHRESH'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICORR_CORRTHRESHLOW, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICORR.CORRTHRESHLOW'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICORR_CORRTHRESHUP, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICORR.CORRTHRESHUP'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_SICORR_CORRTHRESH2SYMB, '', ModelOutputType.SVD_REG_FIELD, readable_name='MODEM.SICORR.CORRTHRESH2SYMB'))




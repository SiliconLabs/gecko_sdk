
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_SUNOFDM_CFG1_MODULATION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_CFG1_MODULATION, self).__init__(register,
            'MODULATION', 'SUNOFDM.CFG1.MODULATION', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_CFG1_OFDMOPTION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_CFG1_OFDMOPTION, self).__init__(register,
            'OFDMOPTION', 'SUNOFDM.CFG1.OFDMOPTION', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_CFG1_INTERLEAVING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_CFG1_INTERLEAVING, self).__init__(register,
            'INTERLEAVING', 'SUNOFDM.CFG1.INTERLEAVING', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_CFG1_MACFCSTYPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_CFG1_MACFCSTYPE, self).__init__(register,
            'MACFCSTYPE', 'SUNOFDM.CFG1.MACFCSTYPE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_CFG1_CONCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_CFG1_CONCURRENT, self).__init__(register,
            'CONCURRENT', 'SUNOFDM.CFG1.CONCURRENT', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_CFG1_XTALFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_CFG1_XTALFREQ, self).__init__(register,
            'XTALFREQ', 'SUNOFDM.CFG1.XTALFREQ', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_CFG2_NBSTF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_CFG2_NBSTF, self).__init__(register,
            'NBSTF', 'SUNOFDM.CFG2.NBSTF', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_VREGS_MINORVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_VREGS_MINORVERSION, self).__init__(register,
            'MINORVERSION', 'SUNOFDM.VREGS.MINORVERSION', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_VREGS_MAJORVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_VREGS_MAJORVERSION, self).__init__(register,
            'MAJORVERSION', 'SUNOFDM.VREGS.MAJORVERSION', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_RXCFG1_EXTFREQUPPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_RXCFG1_EXTFREQUPPER, self).__init__(register,
            'EXTFREQUPPER', 'SUNOFDM.RXCFG1.EXTFREQUPPER', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_RXCFG1_EXTFREQLOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_RXCFG1_EXTFREQLOWER, self).__init__(register,
            'EXTFREQLOWER', 'SUNOFDM.RXCFG1.EXTFREQLOWER', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_RXCFG1_DUALPHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_RXCFG1_DUALPHR, self).__init__(register,
            'DUALPHR', 'SUNOFDM.RXCFG1.DUALPHR', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_RXCFG1_COARSEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_RXCFG1_COARSEFREQ, self).__init__(register,
            'COARSEFREQ', 'SUNOFDM.RXCFG1.COARSEFREQ', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_RXCFG1_EXTCOARSEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_RXCFG1_EXTCOARSEFREQ, self).__init__(register,
            'EXTCOARSEFREQ', 'SUNOFDM.RXCFG1.EXTCOARSEFREQ', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_RXCFG1_GIRECOMB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_RXCFG1_GIRECOMB, self).__init__(register,
            'GIRECOMB', 'SUNOFDM.RXCFG1.GIRECOMB', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_RXCFG2_RSSISETPOINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_RXCFG2_RSSISETPOINT, self).__init__(register,
            'RSSISETPOINT', 'SUNOFDM.RXCFG2.RSSISETPOINT', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_COLLDET_COLLDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_COLLDET_COLLDET, self).__init__(register,
            'COLLDET', 'SUNOFDM.COLLDET.COLLDET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_COLLDET_COLLDETTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_COLLDET_COLLDETTHR, self).__init__(register,
            'COLLDETTHR', 'SUNOFDM.COLLDET.COLLDETTHR', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_AFC_AFCMIXERRATIOGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_AFC_AFCMIXERRATIOGAIN, self).__init__(register,
            'AFCMIXERRATIOGAIN', 'SUNOFDM.AFC.AFCMIXERRATIOGAIN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_AFC_AFCMIXERRATIOATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_AFC_AFCMIXERRATIOATT, self).__init__(register,
            'AFCMIXERRATIOATT', 'SUNOFDM.AFC.AFCMIXERRATIOATT', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_AFC_AFCCORRECTION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_AFC_AFCCORRECTION, self).__init__(register,
            'AFCCORRECTION', 'SUNOFDM.AFC.AFCCORRECTION', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXCFG1_TXROTATERAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXCFG1_TXROTATERAMP, self).__init__(register,
            'TXROTATERAMP', 'SUNOFDM.TXCFG1.TXROTATERAMP', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXCFG1_TXHCSERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXCFG1_TXHCSERRORS, self).__init__(register,
            'TXHCSERRORS', 'SUNOFDM.TXCFG1.TXHCSERRORS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXCFG1_TXFCSERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXCFG1_TXFCSERRORS, self).__init__(register,
            'TXFCSERRORS', 'SUNOFDM.TXCFG1.TXFCSERRORS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXCFG1_TXFCSBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXCFG1_TXFCSBYP, self).__init__(register,
            'TXFCSBYP', 'SUNOFDM.TXCFG1.TXFCSBYP', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANT_ANTDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANT_ANTDIV, self).__init__(register,
            'ANTDIV', 'SUNOFDM.ANT.ANTDIV', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANT_ANTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANT_ANTSEL, self).__init__(register,
            'ANTSEL', 'SUNOFDM.ANT.ANTSEL', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANT_ANTCORRTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANT_ANTCORRTHR, self).__init__(register,
            'ANTCORRTHR', 'SUNOFDM.ANT.ANTCORRTHR', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANT_ANTRSSITHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANT_ANTRSSITHR, self).__init__(register,
            'ANTRSSITHR', 'SUNOFDM.ANT.ANTRSSITHR', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDET_PDETCORRELWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDET_PDETCORRELWIDTH, self).__init__(register,
            'PDETCORRELWIDTH', 'SUNOFDM.PDET.PDETCORRELWIDTH', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDET_PDETCF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDET_PDETCF, self).__init__(register,
            'PDETCF', 'SUNOFDM.PDET.PDETCF', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDET_PDETEXCLUDECW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDET_PDETEXCLUDECW, self).__init__(register,
            'PDETEXCLUDECW', 'SUNOFDM.PDET.PDETEXCLUDECW', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDET_PDETTHRGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDET_PDETTHRGAIN, self).__init__(register,
            'PDETTHRGAIN', 'SUNOFDM.PDET.PDETTHRGAIN', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDET_PDETTHRATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDET_PDETTHRATT, self).__init__(register,
            'PDETTHRATT', 'SUNOFDM.PDET.PDETTHRATT', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDET_PDETCWTHRGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDET_PDETCWTHRGAIN, self).__init__(register,
            'PDETCWTHRGAIN', 'SUNOFDM.PDET.PDETCWTHRGAIN', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDET_PDETCWTHRATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDET_PDETCWTHRATT, self).__init__(register,
            'PDETCWTHRATT', 'SUNOFDM.PDET.PDETCWTHRATT', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCFG_NTAPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCFG_NTAPS, self).__init__(register,
            'NTAPS', 'SUNOFDM.DECFILTCFG.NTAPS', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCFG_SYMMETRIC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCFG_SYMMETRIC, self).__init__(register,
            'SYMMETRIC', 'SUNOFDM.DECFILTCFG.SYMMETRIC', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCFG_INTERP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCFG_INTERP, self).__init__(register,
            'INTERP', 'SUNOFDM.DECFILTCFG.INTERP', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCFG_DECIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCFG_DECIM, self).__init__(register,
            'DECIM', 'SUNOFDM.DECFILTCFG.DECIM', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCFG_NSHIFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCFG_NSHIFT, self).__init__(register,
            'NSHIFT', 'SUNOFDM.DECFILTCFG.NSHIFT', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCFG_SKIPFIRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCFG_SKIPFIRST, self).__init__(register,
            'SKIPFIRST', 'SUNOFDM.DECFILTCFG.SKIPFIRST', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF0_COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF0_COEFF0, self).__init__(register,
            'COEFF0', 'SUNOFDM.DECFILTCOEFF0.COEFF0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF0_COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF0_COEFF1, self).__init__(register,
            'COEFF1', 'SUNOFDM.DECFILTCOEFF0.COEFF1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF1_COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF1_COEFF2, self).__init__(register,
            'COEFF2', 'SUNOFDM.DECFILTCOEFF1.COEFF2', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF1_COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF1_COEFF3, self).__init__(register,
            'COEFF3', 'SUNOFDM.DECFILTCOEFF1.COEFF3', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF2_COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF2_COEFF4, self).__init__(register,
            'COEFF4', 'SUNOFDM.DECFILTCOEFF2.COEFF4', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF2_COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF2_COEFF5, self).__init__(register,
            'COEFF5', 'SUNOFDM.DECFILTCOEFF2.COEFF5', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF3_COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF3_COEFF6, self).__init__(register,
            'COEFF6', 'SUNOFDM.DECFILTCOEFF3.COEFF6', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF3_COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF3_COEFF7, self).__init__(register,
            'COEFF7', 'SUNOFDM.DECFILTCOEFF3.COEFF7', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF4_COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF4_COEFF8, self).__init__(register,
            'COEFF8', 'SUNOFDM.DECFILTCOEFF4.COEFF8', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF4_COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF4_COEFF9, self).__init__(register,
            'COEFF9', 'SUNOFDM.DECFILTCOEFF4.COEFF9', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF5_COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF5_COEFF10, self).__init__(register,
            'COEFF10', 'SUNOFDM.DECFILTCOEFF5.COEFF10', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF5_COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF5_COEFF11, self).__init__(register,
            'COEFF11', 'SUNOFDM.DECFILTCOEFF5.COEFF11', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF6_COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF6_COEFF12, self).__init__(register,
            'COEFF12', 'SUNOFDM.DECFILTCOEFF6.COEFF12', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF6_COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF6_COEFF13, self).__init__(register,
            'COEFF13', 'SUNOFDM.DECFILTCOEFF6.COEFF13', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF7_COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF7_COEFF14, self).__init__(register,
            'COEFF14', 'SUNOFDM.DECFILTCOEFF7.COEFF14', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_DECFILTCOEFF7_COEFF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_DECFILTCOEFF7_COEFF15, self).__init__(register,
            'COEFF15', 'SUNOFDM.DECFILTCOEFF7.COEFF15', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCFG_NTAPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCFG_NTAPS, self).__init__(register,
            'NTAPS', 'SUNOFDM.PDETFILTCFG.NTAPS', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCFG_SYMMETRIC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCFG_SYMMETRIC, self).__init__(register,
            'SYMMETRIC', 'SUNOFDM.PDETFILTCFG.SYMMETRIC', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCFG_INTERP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCFG_INTERP, self).__init__(register,
            'INTERP', 'SUNOFDM.PDETFILTCFG.INTERP', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCFG_DECIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCFG_DECIM, self).__init__(register,
            'DECIM', 'SUNOFDM.PDETFILTCFG.DECIM', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCFG_NSHIFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCFG_NSHIFT, self).__init__(register,
            'NSHIFT', 'SUNOFDM.PDETFILTCFG.NSHIFT', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCFG_SKIPFIRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCFG_SKIPFIRST, self).__init__(register,
            'SKIPFIRST', 'SUNOFDM.PDETFILTCFG.SKIPFIRST', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF0_COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF0_COEFF0, self).__init__(register,
            'COEFF0', 'SUNOFDM.PDETFILTCOEFF0.COEFF0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF0_COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF0_COEFF1, self).__init__(register,
            'COEFF1', 'SUNOFDM.PDETFILTCOEFF0.COEFF1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF1_COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF1_COEFF2, self).__init__(register,
            'COEFF2', 'SUNOFDM.PDETFILTCOEFF1.COEFF2', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF1_COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF1_COEFF3, self).__init__(register,
            'COEFF3', 'SUNOFDM.PDETFILTCOEFF1.COEFF3', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF2_COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF2_COEFF4, self).__init__(register,
            'COEFF4', 'SUNOFDM.PDETFILTCOEFF2.COEFF4', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF2_COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF2_COEFF5, self).__init__(register,
            'COEFF5', 'SUNOFDM.PDETFILTCOEFF2.COEFF5', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF3_COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF3_COEFF6, self).__init__(register,
            'COEFF6', 'SUNOFDM.PDETFILTCOEFF3.COEFF6', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF3_COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF3_COEFF7, self).__init__(register,
            'COEFF7', 'SUNOFDM.PDETFILTCOEFF3.COEFF7', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF4_COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF4_COEFF8, self).__init__(register,
            'COEFF8', 'SUNOFDM.PDETFILTCOEFF4.COEFF8', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF4_COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF4_COEFF9, self).__init__(register,
            'COEFF9', 'SUNOFDM.PDETFILTCOEFF4.COEFF9', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF5_COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF5_COEFF10, self).__init__(register,
            'COEFF10', 'SUNOFDM.PDETFILTCOEFF5.COEFF10', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF5_COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF5_COEFF11, self).__init__(register,
            'COEFF11', 'SUNOFDM.PDETFILTCOEFF5.COEFF11', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF6_COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF6_COEFF12, self).__init__(register,
            'COEFF12', 'SUNOFDM.PDETFILTCOEFF6.COEFF12', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF6_COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF6_COEFF13, self).__init__(register,
            'COEFF13', 'SUNOFDM.PDETFILTCOEFF6.COEFF13', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF7_COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF7_COEFF14, self).__init__(register,
            'COEFF14', 'SUNOFDM.PDETFILTCOEFF7.COEFF14', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PDETFILTCOEFF7_COEFF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PDETFILTCOEFF7_COEFF15, self).__init__(register,
            'COEFF15', 'SUNOFDM.PDETFILTCOEFF7.COEFF15', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_FELATENCIES_RXLATENCY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_FELATENCIES_RXLATENCY, self).__init__(register,
            'RXLATENCY', 'SUNOFDM.FELATENCIES.RXLATENCY', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_FELATENCIES_TXLATENCY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_FELATENCIES_TXLATENCY, self).__init__(register,
            'TXLATENCY', 'SUNOFDM.FELATENCIES.TXLATENCY', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PAPR_ENPAPR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PAPR_ENPAPR, self).__init__(register,
            'ENPAPR', 'SUNOFDM.PAPR.ENPAPR', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PAPR_GAINSAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PAPR_GAINSAT, self).__init__(register,
            'GAINSAT', 'SUNOFDM.PAPR.GAINSAT', 'read-write',
            u"",
            1, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PAPR_GAINATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PAPR_GAINATT, self).__init__(register,
            'GAINATT', 'SUNOFDM.PAPR.GAINATT', 'read-write',
            u"",
            16, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCFG_NTAPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCFG_NTAPS, self).__init__(register,
            'NTAPS', 'SUNOFDM.TXFILTCFG.NTAPS', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCFG_SYMMETRIC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCFG_SYMMETRIC, self).__init__(register,
            'SYMMETRIC', 'SUNOFDM.TXFILTCFG.SYMMETRIC', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCFG_INTERP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCFG_INTERP, self).__init__(register,
            'INTERP', 'SUNOFDM.TXFILTCFG.INTERP', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCFG_DECIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCFG_DECIM, self).__init__(register,
            'DECIM', 'SUNOFDM.TXFILTCFG.DECIM', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCFG_NSHIFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCFG_NSHIFT, self).__init__(register,
            'NSHIFT', 'SUNOFDM.TXFILTCFG.NSHIFT', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCFG_SKIPFIRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCFG_SKIPFIRST, self).__init__(register,
            'SKIPFIRST', 'SUNOFDM.TXFILTCFG.SKIPFIRST', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF0_COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF0_COEFF0, self).__init__(register,
            'COEFF0', 'SUNOFDM.TXFILTCOEFF0.COEFF0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF0_COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF0_COEFF1, self).__init__(register,
            'COEFF1', 'SUNOFDM.TXFILTCOEFF0.COEFF1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF1_COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF1_COEFF2, self).__init__(register,
            'COEFF2', 'SUNOFDM.TXFILTCOEFF1.COEFF2', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF1_COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF1_COEFF3, self).__init__(register,
            'COEFF3', 'SUNOFDM.TXFILTCOEFF1.COEFF3', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF2_COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF2_COEFF4, self).__init__(register,
            'COEFF4', 'SUNOFDM.TXFILTCOEFF2.COEFF4', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF2_COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF2_COEFF5, self).__init__(register,
            'COEFF5', 'SUNOFDM.TXFILTCOEFF2.COEFF5', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF3_COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF3_COEFF6, self).__init__(register,
            'COEFF6', 'SUNOFDM.TXFILTCOEFF3.COEFF6', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF3_COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF3_COEFF7, self).__init__(register,
            'COEFF7', 'SUNOFDM.TXFILTCOEFF3.COEFF7', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF4_COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF4_COEFF8, self).__init__(register,
            'COEFF8', 'SUNOFDM.TXFILTCOEFF4.COEFF8', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF4_COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF4_COEFF9, self).__init__(register,
            'COEFF9', 'SUNOFDM.TXFILTCOEFF4.COEFF9', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF5_COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF5_COEFF10, self).__init__(register,
            'COEFF10', 'SUNOFDM.TXFILTCOEFF5.COEFF10', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF5_COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF5_COEFF11, self).__init__(register,
            'COEFF11', 'SUNOFDM.TXFILTCOEFF5.COEFF11', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF6_COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF6_COEFF12, self).__init__(register,
            'COEFF12', 'SUNOFDM.TXFILTCOEFF6.COEFF12', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF6_COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF6_COEFF13, self).__init__(register,
            'COEFF13', 'SUNOFDM.TXFILTCOEFF6.COEFF13', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF7_COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF7_COEFF14, self).__init__(register,
            'COEFF14', 'SUNOFDM.TXFILTCOEFF7.COEFF14', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_TXFILTCOEFF7_COEFF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_TXFILTCOEFF7_COEFF15, self).__init__(register,
            'COEFF15', 'SUNOFDM.TXFILTCOEFF7.COEFF15', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANTDIVDLY_AGCRELDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANTDIVDLY_AGCRELDLY, self).__init__(register,
            'AGCRELDLY', 'SUNOFDM.ANTDIVDLY.AGCRELDLY', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANTDIVDLY_AGCCONVDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANTDIVDLY_AGCCONVDLY, self).__init__(register,
            'AGCCONVDLY', 'SUNOFDM.ANTDIVDLY.AGCCONVDLY', 'read-write',
            u"",
            6, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANTDIVDLY_SETTLINGTIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANTDIVDLY_SETTLINGTIME, self).__init__(register,
            'SETTLINGTIME', 'SUNOFDM.ANTDIVDLY.SETTLINGTIME', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANTDIVDLY_ANTICPSWITCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANTDIVDLY_ANTICPSWITCH, self).__init__(register,
            'ANTICPSWITCH', 'SUNOFDM.ANTDIVDLY.ANTICPSWITCH', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPH_PREEMPHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPH_PREEMPHEN, self).__init__(register,
            'PREEMPHEN', 'SUNOFDM.PREEMPH.PREEMPHEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPH_PREEMPHSTFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPH_PREEMPHSTFEN, self).__init__(register,
            'PREEMPHSTFEN', 'SUNOFDM.PREEMPH.PREEMPHSTFEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPH_MCSTABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPH_MCSTABLE, self).__init__(register,
            'MCSTABLE', 'SUNOFDM.PREEMPH.MCSTABLE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR0_COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR0_COEFF0, self).__init__(register,
            'COEFF0', 'SUNOFDM.PREEMPHCOGR0.COEFF0', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR0_COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR0_COEFF1, self).__init__(register,
            'COEFF1', 'SUNOFDM.PREEMPHCOGR0.COEFF1', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR0_COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR0_COEFF2, self).__init__(register,
            'COEFF2', 'SUNOFDM.PREEMPHCOGR0.COEFF2', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR0_COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR0_COEFF3, self).__init__(register,
            'COEFF3', 'SUNOFDM.PREEMPHCOGR0.COEFF3', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR1_COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR1_COEFF4, self).__init__(register,
            'COEFF4', 'SUNOFDM.PREEMPHCOGR1.COEFF4', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR1_COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR1_COEFF5, self).__init__(register,
            'COEFF5', 'SUNOFDM.PREEMPHCOGR1.COEFF5', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR1_COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR1_COEFF6, self).__init__(register,
            'COEFF6', 'SUNOFDM.PREEMPHCOGR1.COEFF6', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR1_COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR1_COEFF7, self).__init__(register,
            'COEFF7', 'SUNOFDM.PREEMPHCOGR1.COEFF7', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR2_COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR2_COEFF8, self).__init__(register,
            'COEFF8', 'SUNOFDM.PREEMPHCOGR2.COEFF8', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR2_COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR2_COEFF9, self).__init__(register,
            'COEFF9', 'SUNOFDM.PREEMPHCOGR2.COEFF9', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR2_COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR2_COEFF10, self).__init__(register,
            'COEFF10', 'SUNOFDM.PREEMPHCOGR2.COEFF10', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR2_COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR2_COEFF11, self).__init__(register,
            'COEFF11', 'SUNOFDM.PREEMPHCOGR2.COEFF11', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR3_COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR3_COEFF12, self).__init__(register,
            'COEFF12', 'SUNOFDM.PREEMPHCOGR3.COEFF12', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR3_COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR3_COEFF13, self).__init__(register,
            'COEFF13', 'SUNOFDM.PREEMPHCOGR3.COEFF13', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR3_COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR3_COEFF14, self).__init__(register,
            'COEFF14', 'SUNOFDM.PREEMPHCOGR3.COEFF14', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR3_COEFF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR3_COEFF15, self).__init__(register,
            'COEFF15', 'SUNOFDM.PREEMPHCOGR3.COEFF15', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR4_COEFF16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR4_COEFF16, self).__init__(register,
            'COEFF16', 'SUNOFDM.PREEMPHCOGR4.COEFF16', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR4_COEFF17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR4_COEFF17, self).__init__(register,
            'COEFF17', 'SUNOFDM.PREEMPHCOGR4.COEFF17', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR4_COEFF18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR4_COEFF18, self).__init__(register,
            'COEFF18', 'SUNOFDM.PREEMPHCOGR4.COEFF18', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR4_COEFF19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR4_COEFF19, self).__init__(register,
            'COEFF19', 'SUNOFDM.PREEMPHCOGR4.COEFF19', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR5_COEFF20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR5_COEFF20, self).__init__(register,
            'COEFF20', 'SUNOFDM.PREEMPHCOGR5.COEFF20', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR5_COEFF21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR5_COEFF21, self).__init__(register,
            'COEFF21', 'SUNOFDM.PREEMPHCOGR5.COEFF21', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR5_COEFF22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR5_COEFF22, self).__init__(register,
            'COEFF22', 'SUNOFDM.PREEMPHCOGR5.COEFF22', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR5_COEFF23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR5_COEFF23, self).__init__(register,
            'COEFF23', 'SUNOFDM.PREEMPHCOGR5.COEFF23', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR6_COEFF24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR6_COEFF24, self).__init__(register,
            'COEFF24', 'SUNOFDM.PREEMPHCOGR6.COEFF24', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR6_COEFF25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR6_COEFF25, self).__init__(register,
            'COEFF25', 'SUNOFDM.PREEMPHCOGR6.COEFF25', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR6_COEFF26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR6_COEFF26, self).__init__(register,
            'COEFF26', 'SUNOFDM.PREEMPHCOGR6.COEFF26', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR6_COEFF27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR6_COEFF27, self).__init__(register,
            'COEFF27', 'SUNOFDM.PREEMPHCOGR6.COEFF27', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR7_COEFF28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR7_COEFF28, self).__init__(register,
            'COEFF28', 'SUNOFDM.PREEMPHCOGR7.COEFF28', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR7_COEFF29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR7_COEFF29, self).__init__(register,
            'COEFF29', 'SUNOFDM.PREEMPHCOGR7.COEFF29', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR7_COEFF30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR7_COEFF30, self).__init__(register,
            'COEFF30', 'SUNOFDM.PREEMPHCOGR7.COEFF30', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR7_COEFF31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR7_COEFF31, self).__init__(register,
            'COEFF31', 'SUNOFDM.PREEMPHCOGR7.COEFF31', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR8_COEFF32(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR8_COEFF32, self).__init__(register,
            'COEFF32', 'SUNOFDM.PREEMPHCOGR8.COEFF32', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR8_COEFF33(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR8_COEFF33, self).__init__(register,
            'COEFF33', 'SUNOFDM.PREEMPHCOGR8.COEFF33', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR8_COEFF34(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR8_COEFF34, self).__init__(register,
            'COEFF34', 'SUNOFDM.PREEMPHCOGR8.COEFF34', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR8_COEFF35(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR8_COEFF35, self).__init__(register,
            'COEFF35', 'SUNOFDM.PREEMPHCOGR8.COEFF35', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR9_COEFF36(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR9_COEFF36, self).__init__(register,
            'COEFF36', 'SUNOFDM.PREEMPHCOGR9.COEFF36', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR9_COEFF37(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR9_COEFF37, self).__init__(register,
            'COEFF37', 'SUNOFDM.PREEMPHCOGR9.COEFF37', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR9_COEFF38(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR9_COEFF38, self).__init__(register,
            'COEFF38', 'SUNOFDM.PREEMPHCOGR9.COEFF38', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR9_COEFF39(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR9_COEFF39, self).__init__(register,
            'COEFF39', 'SUNOFDM.PREEMPHCOGR9.COEFF39', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR10_COEFF40(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR10_COEFF40, self).__init__(register,
            'COEFF40', 'SUNOFDM.PREEMPHCOGR10.COEFF40', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR10_COEFF41(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR10_COEFF41, self).__init__(register,
            'COEFF41', 'SUNOFDM.PREEMPHCOGR10.COEFF41', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR10_COEFF42(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR10_COEFF42, self).__init__(register,
            'COEFF42', 'SUNOFDM.PREEMPHCOGR10.COEFF42', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR10_COEFF43(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR10_COEFF43, self).__init__(register,
            'COEFF43', 'SUNOFDM.PREEMPHCOGR10.COEFF43', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR11_COEFF44(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR11_COEFF44, self).__init__(register,
            'COEFF44', 'SUNOFDM.PREEMPHCOGR11.COEFF44', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR11_COEFF45(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR11_COEFF45, self).__init__(register,
            'COEFF45', 'SUNOFDM.PREEMPHCOGR11.COEFF45', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR11_COEFF46(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR11_COEFF46, self).__init__(register,
            'COEFF46', 'SUNOFDM.PREEMPHCOGR11.COEFF46', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR11_COEFF47(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR11_COEFF47, self).__init__(register,
            'COEFF47', 'SUNOFDM.PREEMPHCOGR11.COEFF47', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR12_COEFF48(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR12_COEFF48, self).__init__(register,
            'COEFF48', 'SUNOFDM.PREEMPHCOGR12.COEFF48', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR12_COEFF49(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR12_COEFF49, self).__init__(register,
            'COEFF49', 'SUNOFDM.PREEMPHCOGR12.COEFF49', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR12_COEFF50(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR12_COEFF50, self).__init__(register,
            'COEFF50', 'SUNOFDM.PREEMPHCOGR12.COEFF50', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_PREEMPHCOGR12_COEFF51(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_PREEMPHCOGR12_COEFF51, self).__init__(register,
            'COEFF51', 'SUNOFDM.PREEMPHCOGR12.COEFF51', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOFDM_ANTDIVDLY2_AGCCONVDLYRED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOFDM_ANTDIVDLY2_AGCCONVDLYRED, self).__init__(register,
            'AGCCONVDLYRED', 'SUNOFDM.ANTDIVDLY2.AGCCONVDLYRED', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True



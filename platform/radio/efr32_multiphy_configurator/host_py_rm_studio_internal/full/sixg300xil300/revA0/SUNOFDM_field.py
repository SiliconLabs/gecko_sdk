
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
            1, 2)
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



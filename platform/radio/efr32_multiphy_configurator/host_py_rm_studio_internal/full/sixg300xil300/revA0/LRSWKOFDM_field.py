
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_LRSWKOFDM_CFG1_MODULATION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_CFG1_MODULATION, self).__init__(register,
            'MODULATION', 'LRSWKOFDM.CFG1.MODULATION', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_CFG1_OFDMOPTION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_CFG1_OFDMOPTION, self).__init__(register,
            'OFDMOPTION', 'LRSWKOFDM.CFG1.OFDMOPTION', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_CFG1_INTERLEAVING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_CFG1_INTERLEAVING, self).__init__(register,
            'INTERLEAVING', 'LRSWKOFDM.CFG1.INTERLEAVING', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_CFG1_MACFCSTYPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_CFG1_MACFCSTYPE, self).__init__(register,
            'MACFCSTYPE', 'LRSWKOFDM.CFG1.MACFCSTYPE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_CFG1_XTALFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_CFG1_XTALFREQ, self).__init__(register,
            'XTALFREQ', 'LRSWKOFDM.CFG1.XTALFREQ', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_VREGS_MINORVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_VREGS_MINORVERSION, self).__init__(register,
            'MINORVERSION', 'LRSWKOFDM.VREGS.MINORVERSION', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_VREGS_MAJORVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_VREGS_MAJORVERSION, self).__init__(register,
            'MAJORVERSION', 'LRSWKOFDM.VREGS.MAJORVERSION', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_COLLDET_COLLDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_COLLDET_COLLDET, self).__init__(register,
            'COLLDET', 'LRSWKOFDM.COLLDET.COLLDET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_COLLDET_COLLDETTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_COLLDET_COLLDETTHR, self).__init__(register,
            'COLLDETTHR', 'LRSWKOFDM.COLLDET.COLLDETTHR', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_AFC_AFCMIXERRATIOGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_AFC_AFCMIXERRATIOGAIN, self).__init__(register,
            'AFCMIXERRATIOGAIN', 'LRSWKOFDM.AFC.AFCMIXERRATIOGAIN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_AFC_AFCMIXERRATIOATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_AFC_AFCMIXERRATIOATT, self).__init__(register,
            'AFCMIXERRATIOATT', 'LRSWKOFDM.AFC.AFCMIXERRATIOATT', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_AFC_AFCCORRECTION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_AFC_AFCCORRECTION, self).__init__(register,
            'AFCCORRECTION', 'LRSWKOFDM.AFC.AFCCORRECTION', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_TXCFG1_TXROTATERAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_TXCFG1_TXROTATERAMP, self).__init__(register,
            'TXROTATERAMP', 'LRSWKOFDM.TXCFG1.TXROTATERAMP', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_TXCFG1_TXHCSERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_TXCFG1_TXHCSERRORS, self).__init__(register,
            'TXHCSERRORS', 'LRSWKOFDM.TXCFG1.TXHCSERRORS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_TXCFG1_TXFCSERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_TXCFG1_TXFCSERRORS, self).__init__(register,
            'TXFCSERRORS', 'LRSWKOFDM.TXCFG1.TXFCSERRORS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_ANT_ANTDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_ANT_ANTDIV, self).__init__(register,
            'ANTDIV', 'LRSWKOFDM.ANT.ANTDIV', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LRSWKOFDM_ANT_ANTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LRSWKOFDM_ANT_ANTSEL, self).__init__(register,
            'ANTSEL', 'LRSWKOFDM.ANT.ANTSEL', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True



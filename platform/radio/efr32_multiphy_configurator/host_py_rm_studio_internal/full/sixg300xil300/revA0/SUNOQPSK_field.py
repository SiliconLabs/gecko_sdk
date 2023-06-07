
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_SUNOQPSK_CFG1_MODULATION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_CFG1_MODULATION, self).__init__(register,
            'MODULATION', 'SUNOQPSK.CFG1.MODULATION', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_CFG1_CHIPRATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_CFG1_CHIPRATE, self).__init__(register,
            'CHIPRATE', 'SUNOQPSK.CFG1.CHIPRATE', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_CFG1_BANDFREQMHZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_CFG1_BANDFREQMHZ, self).__init__(register,
            'BANDFREQMHZ', 'SUNOQPSK.CFG1.BANDFREQMHZ', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_CFG2_MACFCSTYPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_CFG2_MACFCSTYPE, self).__init__(register,
            'MACFCSTYPE', 'SUNOQPSK.CFG2.MACFCSTYPE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_CFG2_NBPREAMB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_CFG2_NBPREAMB, self).__init__(register,
            'NBPREAMB', 'SUNOQPSK.CFG2.NBPREAMB', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_CFG2_XTALFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_CFG2_XTALFREQ, self).__init__(register,
            'XTALFREQ', 'SUNOQPSK.CFG2.XTALFREQ', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_VREGS_MINORVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_VREGS_MINORVERSION, self).__init__(register,
            'MINORVERSION', 'SUNOQPSK.VREGS.MINORVERSION', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_VREGS_MAJORVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_VREGS_MAJORVERSION, self).__init__(register,
            'MAJORVERSION', 'SUNOQPSK.VREGS.MAJORVERSION', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_COLLDET_COLLDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_COLLDET_COLLDET, self).__init__(register,
            'COLLDET', 'SUNOQPSK.COLLDET.COLLDET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_COLLDET_COLLDETTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_COLLDET_COLLDETTHR, self).__init__(register,
            'COLLDETTHR', 'SUNOQPSK.COLLDET.COLLDETTHR', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_AFC_AFCMIXERRATIOGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_AFC_AFCMIXERRATIOGAIN, self).__init__(register,
            'AFCMIXERRATIOGAIN', 'SUNOQPSK.AFC.AFCMIXERRATIOGAIN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_AFC_AFCMIXERRATIOATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_AFC_AFCMIXERRATIOATT, self).__init__(register,
            'AFCMIXERRATIOATT', 'SUNOQPSK.AFC.AFCMIXERRATIOATT', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_AFC_AFCFBITER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_AFC_AFCFBITER, self).__init__(register,
            'AFCFBITER', 'SUNOQPSK.AFC.AFCFBITER', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_AFC_AFCCORRECTION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_AFC_AFCCORRECTION, self).__init__(register,
            'AFCCORRECTION', 'SUNOQPSK.AFC.AFCCORRECTION', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_TXCFG1_TXHCSERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_TXCFG1_TXHCSERRORS, self).__init__(register,
            'TXHCSERRORS', 'SUNOQPSK.TXCFG1.TXHCSERRORS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_TXCFG1_TXFCSERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_TXCFG1_TXFCSERRORS, self).__init__(register,
            'TXFCSERRORS', 'SUNOQPSK.TXCFG1.TXFCSERRORS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_ANT_ANTDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_ANT_ANTDIV, self).__init__(register,
            'ANTDIV', 'SUNOQPSK.ANT.ANTDIV', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_ANT_ANTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_ANT_ANTSEL, self).__init__(register,
            'ANTSEL', 'SUNOQPSK.ANT.ANTSEL', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_PDET_NBHITSDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_PDET_NBHITSDET, self).__init__(register,
            'NBHITSDET', 'SUNOQPSK.PDET.NBHITSDET', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_PDET_NSPDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_PDET_NSPDET, self).__init__(register,
            'NSPDET', 'SUNOQPSK.PDET.NSPDET', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_PDET_NBCHUNKS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_PDET_NBCHUNKS, self).__init__(register,
            'NBCHUNKS', 'SUNOQPSK.PDET.NBCHUNKS', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_PDTHR_MINTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_PDTHR_MINTHR, self).__init__(register,
            'MINTHR', 'SUNOQPSK.PDTHR.MINTHR', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_SUNOQPSK_PDTHR_TSRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SUNOQPSK_PDTHR_TSRATIO, self).__init__(register,
            'TSRATIO', 'SUNOQPSK.PDTHR.TSRATIO', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True




# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_LEGOQPSK_CFG1_MODULATION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_CFG1_MODULATION, self).__init__(register,
            'MODULATION', 'LEGOQPSK.CFG1.MODULATION', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_CFG1_CHIPRATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_CFG1_CHIPRATE, self).__init__(register,
            'CHIPRATE', 'LEGOQPSK.CFG1.CHIPRATE', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_CFG1_BANDFREQMHZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_CFG1_BANDFREQMHZ, self).__init__(register,
            'BANDFREQMHZ', 'LEGOQPSK.CFG1.BANDFREQMHZ', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_CFG2_MACFCSTYPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_CFG2_MACFCSTYPE, self).__init__(register,
            'MACFCSTYPE', 'LEGOQPSK.CFG2.MACFCSTYPE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_CFG2_NBPREAMB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_CFG2_NBPREAMB, self).__init__(register,
            'NBPREAMB', 'LEGOQPSK.CFG2.NBPREAMB', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_CFG2_XTALFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_CFG2_XTALFREQ, self).__init__(register,
            'XTALFREQ', 'LEGOQPSK.CFG2.XTALFREQ', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_VREGS_MINORVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_VREGS_MINORVERSION, self).__init__(register,
            'MINORVERSION', 'LEGOQPSK.VREGS.MINORVERSION', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_VREGS_MAJORVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_VREGS_MAJORVERSION, self).__init__(register,
            'MAJORVERSION', 'LEGOQPSK.VREGS.MAJORVERSION', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_COLLDET_COLLDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_COLLDET_COLLDET, self).__init__(register,
            'COLLDET', 'LEGOQPSK.COLLDET.COLLDET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_COLLDET_COLLDETTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_COLLDET_COLLDETTHR, self).__init__(register,
            'COLLDETTHR', 'LEGOQPSK.COLLDET.COLLDETTHR', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_AFC_AFCMIXERRATIOGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_AFC_AFCMIXERRATIOGAIN, self).__init__(register,
            'AFCMIXERRATIOGAIN', 'LEGOQPSK.AFC.AFCMIXERRATIOGAIN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_AFC_AFCMIXERRATIOATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_AFC_AFCMIXERRATIOATT, self).__init__(register,
            'AFCMIXERRATIOATT', 'LEGOQPSK.AFC.AFCMIXERRATIOATT', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_AFC_AFCFBITER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_AFC_AFCFBITER, self).__init__(register,
            'AFCFBITER', 'LEGOQPSK.AFC.AFCFBITER', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_AFC_AFCCORRECTION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_AFC_AFCCORRECTION, self).__init__(register,
            'AFCCORRECTION', 'LEGOQPSK.AFC.AFCCORRECTION', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_TXCFG1_TXHCSERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_TXCFG1_TXHCSERRORS, self).__init__(register,
            'TXHCSERRORS', 'LEGOQPSK.TXCFG1.TXHCSERRORS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_TXCFG1_TXFCSERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_TXCFG1_TXFCSERRORS, self).__init__(register,
            'TXFCSERRORS', 'LEGOQPSK.TXCFG1.TXFCSERRORS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_ANT_ANTDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_ANT_ANTDIV, self).__init__(register,
            'ANTDIV', 'LEGOQPSK.ANT.ANTDIV', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_ANT_ANTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_ANT_ANTSEL, self).__init__(register,
            'ANTSEL', 'LEGOQPSK.ANT.ANTSEL', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_PDET_NBHITSDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_PDET_NBHITSDET, self).__init__(register,
            'NBHITSDET', 'LEGOQPSK.PDET.NBHITSDET', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_PDET_NSPDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_PDET_NSPDET, self).__init__(register,
            'NSPDET', 'LEGOQPSK.PDET.NSPDET', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_PDET_NBCHUNKS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_PDET_NBCHUNKS, self).__init__(register,
            'NBCHUNKS', 'LEGOQPSK.PDET.NBCHUNKS', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_PDTHR_MINTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_PDTHR_MINTHR, self).__init__(register,
            'MINTHR', 'LEGOQPSK.PDTHR.MINTHR', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_LEGOQPSK_PDTHR_TSRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_LEGOQPSK_PDTHR_TSRATIO, self).__init__(register,
            'TSRATIO', 'LEGOQPSK.PDTHR.TSRATIO', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True



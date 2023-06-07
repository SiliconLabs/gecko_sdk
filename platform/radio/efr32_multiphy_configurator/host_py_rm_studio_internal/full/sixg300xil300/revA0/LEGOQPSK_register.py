
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . LEGOQPSK_field import *


class RM_Register_LEGOQPSK_CFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_CFG1, self).__init__(rmio, label,
            0xb500fc00, 0x000,
            'CFG1', 'LEGOQPSK.CFG1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODULATION = RM_Field_LEGOQPSK_CFG1_MODULATION(self)
        self.zz_fdict['MODULATION'] = self.MODULATION
        self.CHIPRATE = RM_Field_LEGOQPSK_CFG1_CHIPRATE(self)
        self.zz_fdict['CHIPRATE'] = self.CHIPRATE
        self.BANDFREQMHZ = RM_Field_LEGOQPSK_CFG1_BANDFREQMHZ(self)
        self.zz_fdict['BANDFREQMHZ'] = self.BANDFREQMHZ
        self.__dict__['zz_frozen'] = True


class RM_Register_LEGOQPSK_CFG2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_CFG2, self).__init__(rmio, label,
            0xb500fc00, 0x004,
            'CFG2', 'LEGOQPSK.CFG2', 'read-write',
            u"",
            0x00000001, 0xFFFFFF01,
            0x00001000, 0x00002000,
            0x00003000)

        self.MACFCSTYPE = RM_Field_LEGOQPSK_CFG2_MACFCSTYPE(self)
        self.zz_fdict['MACFCSTYPE'] = self.MACFCSTYPE
        self.NBPREAMB = RM_Field_LEGOQPSK_CFG2_NBPREAMB(self)
        self.zz_fdict['NBPREAMB'] = self.NBPREAMB
        self.XTALFREQ = RM_Field_LEGOQPSK_CFG2_XTALFREQ(self)
        self.zz_fdict['XTALFREQ'] = self.XTALFREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_LEGOQPSK_VREGS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_VREGS, self).__init__(rmio, label,
            0xb500fc00, 0x008,
            'VREGS', 'LEGOQPSK.VREGS', 'read-write',
            u"",
            0x00000000, 0xFFFF0000,
            0x00001000, 0x00002000,
            0x00003000)

        self.MINORVERSION = RM_Field_LEGOQPSK_VREGS_MINORVERSION(self)
        self.zz_fdict['MINORVERSION'] = self.MINORVERSION
        self.MAJORVERSION = RM_Field_LEGOQPSK_VREGS_MAJORVERSION(self)
        self.zz_fdict['MAJORVERSION'] = self.MAJORVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_LEGOQPSK_COLLDET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_COLLDET, self).__init__(rmio, label,
            0xb500fc00, 0x014,
            'COLLDET', 'LEGOQPSK.COLLDET', 'read-write',
            u"",
            0x00000014, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.COLLDET = RM_Field_LEGOQPSK_COLLDET_COLLDET(self)
        self.zz_fdict['COLLDET'] = self.COLLDET
        self.COLLDETTHR = RM_Field_LEGOQPSK_COLLDET_COLLDETTHR(self)
        self.zz_fdict['COLLDETTHR'] = self.COLLDETTHR
        self.__dict__['zz_frozen'] = True


class RM_Register_LEGOQPSK_AFC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_AFC, self).__init__(rmio, label,
            0xb500fc00, 0x018,
            'AFC', 'LEGOQPSK.AFC', 'read-write',
            u"",
            0x00000000, 0xCF1FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCMIXERRATIOGAIN = RM_Field_LEGOQPSK_AFC_AFCMIXERRATIOGAIN(self)
        self.zz_fdict['AFCMIXERRATIOGAIN'] = self.AFCMIXERRATIOGAIN
        self.AFCMIXERRATIOATT = RM_Field_LEGOQPSK_AFC_AFCMIXERRATIOATT(self)
        self.zz_fdict['AFCMIXERRATIOATT'] = self.AFCMIXERRATIOATT
        self.AFCFBITER = RM_Field_LEGOQPSK_AFC_AFCFBITER(self)
        self.zz_fdict['AFCFBITER'] = self.AFCFBITER
        self.AFCCORRECTION = RM_Field_LEGOQPSK_AFC_AFCCORRECTION(self)
        self.zz_fdict['AFCCORRECTION'] = self.AFCCORRECTION
        self.__dict__['zz_frozen'] = True


class RM_Register_LEGOQPSK_TXCFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_TXCFG1, self).__init__(rmio, label,
            0xb500fc00, 0x01C,
            'TXCFG1', 'LEGOQPSK.TXCFG1', 'read-write',
            u"",
            0x00000000, 0x00000006,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXHCSERRORS = RM_Field_LEGOQPSK_TXCFG1_TXHCSERRORS(self)
        self.zz_fdict['TXHCSERRORS'] = self.TXHCSERRORS
        self.TXFCSERRORS = RM_Field_LEGOQPSK_TXCFG1_TXFCSERRORS(self)
        self.zz_fdict['TXFCSERRORS'] = self.TXFCSERRORS
        self.__dict__['zz_frozen'] = True


class RM_Register_LEGOQPSK_ANT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_ANT, self).__init__(rmio, label,
            0xb500fc00, 0x020,
            'ANT', 'LEGOQPSK.ANT', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTDIV = RM_Field_LEGOQPSK_ANT_ANTDIV(self)
        self.zz_fdict['ANTDIV'] = self.ANTDIV
        self.ANTSEL = RM_Field_LEGOQPSK_ANT_ANTSEL(self)
        self.zz_fdict['ANTSEL'] = self.ANTSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_LEGOQPSK_PDET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_PDET, self).__init__(rmio, label,
            0xb500fc00, 0x030,
            'PDET', 'LEGOQPSK.PDET', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.NBHITSDET = RM_Field_LEGOQPSK_PDET_NBHITSDET(self)
        self.zz_fdict['NBHITSDET'] = self.NBHITSDET
        self.NSPDET = RM_Field_LEGOQPSK_PDET_NSPDET(self)
        self.zz_fdict['NSPDET'] = self.NSPDET
        self.NBCHUNKS = RM_Field_LEGOQPSK_PDET_NBCHUNKS(self)
        self.zz_fdict['NBCHUNKS'] = self.NBCHUNKS
        self.__dict__['zz_frozen'] = True


class RM_Register_LEGOQPSK_PDTHR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LEGOQPSK_PDTHR, self).__init__(rmio, label,
            0xb500fc00, 0x034,
            'PDTHR', 'LEGOQPSK.PDTHR', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MINTHR = RM_Field_LEGOQPSK_PDTHR_MINTHR(self)
        self.zz_fdict['MINTHR'] = self.MINTHR
        self.TSRATIO = RM_Field_LEGOQPSK_PDTHR_TSRATIO(self)
        self.zz_fdict['TSRATIO'] = self.TSRATIO
        self.__dict__['zz_frozen'] = True



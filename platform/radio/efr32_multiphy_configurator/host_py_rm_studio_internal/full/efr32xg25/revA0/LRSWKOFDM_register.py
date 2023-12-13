
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . LRSWKOFDM_field import *


class RM_Register_LRSWKOFDM_CFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LRSWKOFDM_CFG1, self).__init__(rmio, label,
            0xb500fc00, 0x000,
            'CFG1', 'LRSWKOFDM.CFG1', 'read-write',
            u"",
            0x00000000, 0xFFFF0FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODULATION = RM_Field_LRSWKOFDM_CFG1_MODULATION(self)
        self.zz_fdict['MODULATION'] = self.MODULATION
        self.OFDMOPTION = RM_Field_LRSWKOFDM_CFG1_OFDMOPTION(self)
        self.zz_fdict['OFDMOPTION'] = self.OFDMOPTION
        self.INTERLEAVING = RM_Field_LRSWKOFDM_CFG1_INTERLEAVING(self)
        self.zz_fdict['INTERLEAVING'] = self.INTERLEAVING
        self.MACFCSTYPE = RM_Field_LRSWKOFDM_CFG1_MACFCSTYPE(self)
        self.zz_fdict['MACFCSTYPE'] = self.MACFCSTYPE
        self.XTALFREQ = RM_Field_LRSWKOFDM_CFG1_XTALFREQ(self)
        self.zz_fdict['XTALFREQ'] = self.XTALFREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_LRSWKOFDM_VREGS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LRSWKOFDM_VREGS, self).__init__(rmio, label,
            0xb500fc00, 0x008,
            'VREGS', 'LRSWKOFDM.VREGS', 'read-write',
            u"",
            0x00000000, 0xFFFF0000,
            0x00001000, 0x00002000,
            0x00003000)

        self.MINORVERSION = RM_Field_LRSWKOFDM_VREGS_MINORVERSION(self)
        self.zz_fdict['MINORVERSION'] = self.MINORVERSION
        self.MAJORVERSION = RM_Field_LRSWKOFDM_VREGS_MAJORVERSION(self)
        self.zz_fdict['MAJORVERSION'] = self.MAJORVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_LRSWKOFDM_COLLDET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LRSWKOFDM_COLLDET, self).__init__(rmio, label,
            0xb500fc00, 0x014,
            'COLLDET', 'LRSWKOFDM.COLLDET', 'read-write',
            u"",
            0x00000014, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.COLLDET = RM_Field_LRSWKOFDM_COLLDET_COLLDET(self)
        self.zz_fdict['COLLDET'] = self.COLLDET
        self.COLLDETTHR = RM_Field_LRSWKOFDM_COLLDET_COLLDETTHR(self)
        self.zz_fdict['COLLDETTHR'] = self.COLLDETTHR
        self.__dict__['zz_frozen'] = True


class RM_Register_LRSWKOFDM_AFC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LRSWKOFDM_AFC, self).__init__(rmio, label,
            0xb500fc00, 0x018,
            'AFC', 'LRSWKOFDM.AFC', 'read-write',
            u"",
            0x00000000, 0xC01FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCMIXERRATIOGAIN = RM_Field_LRSWKOFDM_AFC_AFCMIXERRATIOGAIN(self)
        self.zz_fdict['AFCMIXERRATIOGAIN'] = self.AFCMIXERRATIOGAIN
        self.AFCMIXERRATIOATT = RM_Field_LRSWKOFDM_AFC_AFCMIXERRATIOATT(self)
        self.zz_fdict['AFCMIXERRATIOATT'] = self.AFCMIXERRATIOATT
        self.AFCCORRECTION = RM_Field_LRSWKOFDM_AFC_AFCCORRECTION(self)
        self.zz_fdict['AFCCORRECTION'] = self.AFCCORRECTION
        self.__dict__['zz_frozen'] = True


class RM_Register_LRSWKOFDM_TXCFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LRSWKOFDM_TXCFG1, self).__init__(rmio, label,
            0xb500fc00, 0x01C,
            'TXCFG1', 'LRSWKOFDM.TXCFG1', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXROTATERAMP = RM_Field_LRSWKOFDM_TXCFG1_TXROTATERAMP(self)
        self.zz_fdict['TXROTATERAMP'] = self.TXROTATERAMP
        self.TXHCSERRORS = RM_Field_LRSWKOFDM_TXCFG1_TXHCSERRORS(self)
        self.zz_fdict['TXHCSERRORS'] = self.TXHCSERRORS
        self.TXFCSERRORS = RM_Field_LRSWKOFDM_TXCFG1_TXFCSERRORS(self)
        self.zz_fdict['TXFCSERRORS'] = self.TXFCSERRORS
        self.__dict__['zz_frozen'] = True


class RM_Register_LRSWKOFDM_ANT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_LRSWKOFDM_ANT, self).__init__(rmio, label,
            0xb500fc00, 0x020,
            'ANT', 'LRSWKOFDM.ANT', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTDIV = RM_Field_LRSWKOFDM_ANT_ANTDIV(self)
        self.zz_fdict['ANTDIV'] = self.ANTDIV
        self.ANTSEL = RM_Field_LRSWKOFDM_ANT_ANTSEL(self)
        self.zz_fdict['ANTSEL'] = self.ANTSEL
        self.__dict__['zz_frozen'] = True



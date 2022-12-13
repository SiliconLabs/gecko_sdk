
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . SUNOFDM_field import *


class RM_Register_SUNOFDM_CFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_CFG1, self).__init__(rmio, label,
            0xb500fc00, 0x000,
            'CFG1', 'SUNOFDM.CFG1', 'read-write',
            u"",
            0x00000000, 0xFFFF1FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODULATION = RM_Field_SUNOFDM_CFG1_MODULATION(self)
        self.zz_fdict['MODULATION'] = self.MODULATION
        self.OFDMOPTION = RM_Field_SUNOFDM_CFG1_OFDMOPTION(self)
        self.zz_fdict['OFDMOPTION'] = self.OFDMOPTION
        self.INTERLEAVING = RM_Field_SUNOFDM_CFG1_INTERLEAVING(self)
        self.zz_fdict['INTERLEAVING'] = self.INTERLEAVING
        self.MACFCSTYPE = RM_Field_SUNOFDM_CFG1_MACFCSTYPE(self)
        self.zz_fdict['MACFCSTYPE'] = self.MACFCSTYPE
        self.CONCURRENT = RM_Field_SUNOFDM_CFG1_CONCURRENT(self)
        self.zz_fdict['CONCURRENT'] = self.CONCURRENT
        self.XTALFREQ = RM_Field_SUNOFDM_CFG1_XTALFREQ(self)
        self.zz_fdict['XTALFREQ'] = self.XTALFREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_CFG2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_CFG2, self).__init__(rmio, label,
            0xb500fc00, 0x004,
            'CFG2', 'SUNOFDM.CFG2', 'read-write',
            u"",
            0x00000000, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.NBSTF = RM_Field_SUNOFDM_CFG2_NBSTF(self)
        self.zz_fdict['NBSTF'] = self.NBSTF
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_VREGS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_VREGS, self).__init__(rmio, label,
            0xb500fc00, 0x008,
            'VREGS', 'SUNOFDM.VREGS', 'read-write',
            u"",
            0x00000000, 0xFFFF0000,
            0x00001000, 0x00002000,
            0x00003000)

        self.MINORVERSION = RM_Field_SUNOFDM_VREGS_MINORVERSION(self)
        self.zz_fdict['MINORVERSION'] = self.MINORVERSION
        self.MAJORVERSION = RM_Field_SUNOFDM_VREGS_MAJORVERSION(self)
        self.zz_fdict['MAJORVERSION'] = self.MAJORVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_RXCFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_RXCFG1, self).__init__(rmio, label,
            0xb500fc00, 0x00C,
            'RXCFG1', 'SUNOFDM.RXCFG1', 'read-write',
            u"",
            0x00000000, 0x00001FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.EXTFREQUPPER = RM_Field_SUNOFDM_RXCFG1_EXTFREQUPPER(self)
        self.zz_fdict['EXTFREQUPPER'] = self.EXTFREQUPPER
        self.EXTFREQLOWER = RM_Field_SUNOFDM_RXCFG1_EXTFREQLOWER(self)
        self.zz_fdict['EXTFREQLOWER'] = self.EXTFREQLOWER
        self.DUALPHR = RM_Field_SUNOFDM_RXCFG1_DUALPHR(self)
        self.zz_fdict['DUALPHR'] = self.DUALPHR
        self.COARSEFREQ = RM_Field_SUNOFDM_RXCFG1_COARSEFREQ(self)
        self.zz_fdict['COARSEFREQ'] = self.COARSEFREQ
        self.EXTCOARSEFREQ = RM_Field_SUNOFDM_RXCFG1_EXTCOARSEFREQ(self)
        self.zz_fdict['EXTCOARSEFREQ'] = self.EXTCOARSEFREQ
        self.GIRECOMB = RM_Field_SUNOFDM_RXCFG1_GIRECOMB(self)
        self.zz_fdict['GIRECOMB'] = self.GIRECOMB
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_RXCFG2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_RXCFG2, self).__init__(rmio, label,
            0xb500fc00, 0x010,
            'RXCFG2', 'SUNOFDM.RXCFG2', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RSSISETPOINT = RM_Field_SUNOFDM_RXCFG2_RSSISETPOINT(self)
        self.zz_fdict['RSSISETPOINT'] = self.RSSISETPOINT
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_COLLDET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_COLLDET, self).__init__(rmio, label,
            0xb500fc00, 0x014,
            'COLLDET', 'SUNOFDM.COLLDET', 'read-write',
            u"",
            0x00000014, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.COLLDET = RM_Field_SUNOFDM_COLLDET_COLLDET(self)
        self.zz_fdict['COLLDET'] = self.COLLDET
        self.COLLDETTHR = RM_Field_SUNOFDM_COLLDET_COLLDETTHR(self)
        self.zz_fdict['COLLDETTHR'] = self.COLLDETTHR
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_AFC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_AFC, self).__init__(rmio, label,
            0xb500fc00, 0x018,
            'AFC', 'SUNOFDM.AFC', 'read-write',
            u"",
            0x00000000, 0xC01FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCMIXERRATIOGAIN = RM_Field_SUNOFDM_AFC_AFCMIXERRATIOGAIN(self)
        self.zz_fdict['AFCMIXERRATIOGAIN'] = self.AFCMIXERRATIOGAIN
        self.AFCMIXERRATIOATT = RM_Field_SUNOFDM_AFC_AFCMIXERRATIOATT(self)
        self.zz_fdict['AFCMIXERRATIOATT'] = self.AFCMIXERRATIOATT
        self.AFCCORRECTION = RM_Field_SUNOFDM_AFC_AFCCORRECTION(self)
        self.zz_fdict['AFCCORRECTION'] = self.AFCCORRECTION
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXCFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXCFG1, self).__init__(rmio, label,
            0xb500fc00, 0x01C,
            'TXCFG1', 'SUNOFDM.TXCFG1', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXROTATERAMP = RM_Field_SUNOFDM_TXCFG1_TXROTATERAMP(self)
        self.zz_fdict['TXROTATERAMP'] = self.TXROTATERAMP
        self.TXHCSERRORS = RM_Field_SUNOFDM_TXCFG1_TXHCSERRORS(self)
        self.zz_fdict['TXHCSERRORS'] = self.TXHCSERRORS
        self.TXFCSERRORS = RM_Field_SUNOFDM_TXCFG1_TXFCSERRORS(self)
        self.zz_fdict['TXFCSERRORS'] = self.TXFCSERRORS
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_ANT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_ANT, self).__init__(rmio, label,
            0xb500fc00, 0x020,
            'ANT', 'SUNOFDM.ANT', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTDIV = RM_Field_SUNOFDM_ANT_ANTDIV(self)
        self.zz_fdict['ANTDIV'] = self.ANTDIV
        self.ANTSEL = RM_Field_SUNOFDM_ANT_ANTSEL(self)
        self.zz_fdict['ANTSEL'] = self.ANTSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDET, self).__init__(rmio, label,
            0xb500fc00, 0x030,
            'PDET', 'SUNOFDM.PDET', 'read-write',
            u"",
            0x00000000, 0xFFFF9F07,
            0x00001000, 0x00002000,
            0x00003000)

        self.PDETCORRELWIDTH = RM_Field_SUNOFDM_PDET_PDETCORRELWIDTH(self)
        self.zz_fdict['PDETCORRELWIDTH'] = self.PDETCORRELWIDTH
        self.PDETCF = RM_Field_SUNOFDM_PDET_PDETCF(self)
        self.zz_fdict['PDETCF'] = self.PDETCF
        self.PDETEXCLUDECW = RM_Field_SUNOFDM_PDET_PDETEXCLUDECW(self)
        self.zz_fdict['PDETEXCLUDECW'] = self.PDETEXCLUDECW
        self.PDETTHRGAIN = RM_Field_SUNOFDM_PDET_PDETTHRGAIN(self)
        self.zz_fdict['PDETTHRGAIN'] = self.PDETTHRGAIN
        self.PDETTHRATT = RM_Field_SUNOFDM_PDET_PDETTHRATT(self)
        self.zz_fdict['PDETTHRATT'] = self.PDETTHRATT
        self.PDETCWTHRGAIN = RM_Field_SUNOFDM_PDET_PDETCWTHRGAIN(self)
        self.zz_fdict['PDETCWTHRGAIN'] = self.PDETCWTHRGAIN
        self.PDETCWTHRATT = RM_Field_SUNOFDM_PDET_PDETCWTHRATT(self)
        self.zz_fdict['PDETCWTHRATT'] = self.PDETCWTHRATT
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCFG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCFG, self).__init__(rmio, label,
            0xb500fc00, 0x034,
            'DECFILTCFG', 'SUNOFDM.DECFILTCFG', 'read-write',
            u"",
            0x00000080, 0x013F77BF,
            0x00001000, 0x00002000,
            0x00003000)

        self.NTAPS = RM_Field_SUNOFDM_DECFILTCFG_NTAPS(self)
        self.zz_fdict['NTAPS'] = self.NTAPS
        self.SYMMETRIC = RM_Field_SUNOFDM_DECFILTCFG_SYMMETRIC(self)
        self.zz_fdict['SYMMETRIC'] = self.SYMMETRIC
        self.INTERP = RM_Field_SUNOFDM_DECFILTCFG_INTERP(self)
        self.zz_fdict['INTERP'] = self.INTERP
        self.DECIM = RM_Field_SUNOFDM_DECFILTCFG_DECIM(self)
        self.zz_fdict['DECIM'] = self.DECIM
        self.NSHIFT = RM_Field_SUNOFDM_DECFILTCFG_NSHIFT(self)
        self.zz_fdict['NSHIFT'] = self.NSHIFT
        self.SKIPFIRST = RM_Field_SUNOFDM_DECFILTCFG_SKIPFIRST(self)
        self.zz_fdict['SKIPFIRST'] = self.SKIPFIRST
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCOEFF0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCOEFF0, self).__init__(rmio, label,
            0xb500fc00, 0x038,
            'DECFILTCOEFF0', 'SUNOFDM.DECFILTCOEFF0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF0 = RM_Field_SUNOFDM_DECFILTCOEFF0_COEFF0(self)
        self.zz_fdict['COEFF0'] = self.COEFF0
        self.COEFF1 = RM_Field_SUNOFDM_DECFILTCOEFF0_COEFF1(self)
        self.zz_fdict['COEFF1'] = self.COEFF1
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCOEFF1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCOEFF1, self).__init__(rmio, label,
            0xb500fc00, 0x03C,
            'DECFILTCOEFF1', 'SUNOFDM.DECFILTCOEFF1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF2 = RM_Field_SUNOFDM_DECFILTCOEFF1_COEFF2(self)
        self.zz_fdict['COEFF2'] = self.COEFF2
        self.COEFF3 = RM_Field_SUNOFDM_DECFILTCOEFF1_COEFF3(self)
        self.zz_fdict['COEFF3'] = self.COEFF3
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCOEFF2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCOEFF2, self).__init__(rmio, label,
            0xb500fc00, 0x040,
            'DECFILTCOEFF2', 'SUNOFDM.DECFILTCOEFF2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF4 = RM_Field_SUNOFDM_DECFILTCOEFF2_COEFF4(self)
        self.zz_fdict['COEFF4'] = self.COEFF4
        self.COEFF5 = RM_Field_SUNOFDM_DECFILTCOEFF2_COEFF5(self)
        self.zz_fdict['COEFF5'] = self.COEFF5
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCOEFF3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCOEFF3, self).__init__(rmio, label,
            0xb500fc00, 0x044,
            'DECFILTCOEFF3', 'SUNOFDM.DECFILTCOEFF3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF6 = RM_Field_SUNOFDM_DECFILTCOEFF3_COEFF6(self)
        self.zz_fdict['COEFF6'] = self.COEFF6
        self.COEFF7 = RM_Field_SUNOFDM_DECFILTCOEFF3_COEFF7(self)
        self.zz_fdict['COEFF7'] = self.COEFF7
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCOEFF4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCOEFF4, self).__init__(rmio, label,
            0xb500fc00, 0x048,
            'DECFILTCOEFF4', 'SUNOFDM.DECFILTCOEFF4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF8 = RM_Field_SUNOFDM_DECFILTCOEFF4_COEFF8(self)
        self.zz_fdict['COEFF8'] = self.COEFF8
        self.COEFF9 = RM_Field_SUNOFDM_DECFILTCOEFF4_COEFF9(self)
        self.zz_fdict['COEFF9'] = self.COEFF9
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCOEFF5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCOEFF5, self).__init__(rmio, label,
            0xb500fc00, 0x04C,
            'DECFILTCOEFF5', 'SUNOFDM.DECFILTCOEFF5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF10 = RM_Field_SUNOFDM_DECFILTCOEFF5_COEFF10(self)
        self.zz_fdict['COEFF10'] = self.COEFF10
        self.COEFF11 = RM_Field_SUNOFDM_DECFILTCOEFF5_COEFF11(self)
        self.zz_fdict['COEFF11'] = self.COEFF11
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCOEFF6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCOEFF6, self).__init__(rmio, label,
            0xb500fc00, 0x050,
            'DECFILTCOEFF6', 'SUNOFDM.DECFILTCOEFF6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF12 = RM_Field_SUNOFDM_DECFILTCOEFF6_COEFF12(self)
        self.zz_fdict['COEFF12'] = self.COEFF12
        self.COEFF13 = RM_Field_SUNOFDM_DECFILTCOEFF6_COEFF13(self)
        self.zz_fdict['COEFF13'] = self.COEFF13
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_DECFILTCOEFF7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_DECFILTCOEFF7, self).__init__(rmio, label,
            0xb500fc00, 0x054,
            'DECFILTCOEFF7', 'SUNOFDM.DECFILTCOEFF7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF14 = RM_Field_SUNOFDM_DECFILTCOEFF7_COEFF14(self)
        self.zz_fdict['COEFF14'] = self.COEFF14
        self.COEFF15 = RM_Field_SUNOFDM_DECFILTCOEFF7_COEFF15(self)
        self.zz_fdict['COEFF15'] = self.COEFF15
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCFG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCFG, self).__init__(rmio, label,
            0xb500fc00, 0x058,
            'PDETFILTCFG', 'SUNOFDM.PDETFILTCFG', 'read-write',
            u"",
            0x00000080, 0x013F77BF,
            0x00001000, 0x00002000,
            0x00003000)

        self.NTAPS = RM_Field_SUNOFDM_PDETFILTCFG_NTAPS(self)
        self.zz_fdict['NTAPS'] = self.NTAPS
        self.SYMMETRIC = RM_Field_SUNOFDM_PDETFILTCFG_SYMMETRIC(self)
        self.zz_fdict['SYMMETRIC'] = self.SYMMETRIC
        self.INTERP = RM_Field_SUNOFDM_PDETFILTCFG_INTERP(self)
        self.zz_fdict['INTERP'] = self.INTERP
        self.DECIM = RM_Field_SUNOFDM_PDETFILTCFG_DECIM(self)
        self.zz_fdict['DECIM'] = self.DECIM
        self.NSHIFT = RM_Field_SUNOFDM_PDETFILTCFG_NSHIFT(self)
        self.zz_fdict['NSHIFT'] = self.NSHIFT
        self.SKIPFIRST = RM_Field_SUNOFDM_PDETFILTCFG_SKIPFIRST(self)
        self.zz_fdict['SKIPFIRST'] = self.SKIPFIRST
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCOEFF0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCOEFF0, self).__init__(rmio, label,
            0xb500fc00, 0x05C,
            'PDETFILTCOEFF0', 'SUNOFDM.PDETFILTCOEFF0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF0 = RM_Field_SUNOFDM_PDETFILTCOEFF0_COEFF0(self)
        self.zz_fdict['COEFF0'] = self.COEFF0
        self.COEFF1 = RM_Field_SUNOFDM_PDETFILTCOEFF0_COEFF1(self)
        self.zz_fdict['COEFF1'] = self.COEFF1
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCOEFF1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCOEFF1, self).__init__(rmio, label,
            0xb500fc00, 0x060,
            'PDETFILTCOEFF1', 'SUNOFDM.PDETFILTCOEFF1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF2 = RM_Field_SUNOFDM_PDETFILTCOEFF1_COEFF2(self)
        self.zz_fdict['COEFF2'] = self.COEFF2
        self.COEFF3 = RM_Field_SUNOFDM_PDETFILTCOEFF1_COEFF3(self)
        self.zz_fdict['COEFF3'] = self.COEFF3
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCOEFF2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCOEFF2, self).__init__(rmio, label,
            0xb500fc00, 0x064,
            'PDETFILTCOEFF2', 'SUNOFDM.PDETFILTCOEFF2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF4 = RM_Field_SUNOFDM_PDETFILTCOEFF2_COEFF4(self)
        self.zz_fdict['COEFF4'] = self.COEFF4
        self.COEFF5 = RM_Field_SUNOFDM_PDETFILTCOEFF2_COEFF5(self)
        self.zz_fdict['COEFF5'] = self.COEFF5
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCOEFF3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCOEFF3, self).__init__(rmio, label,
            0xb500fc00, 0x068,
            'PDETFILTCOEFF3', 'SUNOFDM.PDETFILTCOEFF3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF6 = RM_Field_SUNOFDM_PDETFILTCOEFF3_COEFF6(self)
        self.zz_fdict['COEFF6'] = self.COEFF6
        self.COEFF7 = RM_Field_SUNOFDM_PDETFILTCOEFF3_COEFF7(self)
        self.zz_fdict['COEFF7'] = self.COEFF7
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCOEFF4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCOEFF4, self).__init__(rmio, label,
            0xb500fc00, 0x06C,
            'PDETFILTCOEFF4', 'SUNOFDM.PDETFILTCOEFF4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF8 = RM_Field_SUNOFDM_PDETFILTCOEFF4_COEFF8(self)
        self.zz_fdict['COEFF8'] = self.COEFF8
        self.COEFF9 = RM_Field_SUNOFDM_PDETFILTCOEFF4_COEFF9(self)
        self.zz_fdict['COEFF9'] = self.COEFF9
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCOEFF5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCOEFF5, self).__init__(rmio, label,
            0xb500fc00, 0x070,
            'PDETFILTCOEFF5', 'SUNOFDM.PDETFILTCOEFF5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF10 = RM_Field_SUNOFDM_PDETFILTCOEFF5_COEFF10(self)
        self.zz_fdict['COEFF10'] = self.COEFF10
        self.COEFF11 = RM_Field_SUNOFDM_PDETFILTCOEFF5_COEFF11(self)
        self.zz_fdict['COEFF11'] = self.COEFF11
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCOEFF6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCOEFF6, self).__init__(rmio, label,
            0xb500fc00, 0x074,
            'PDETFILTCOEFF6', 'SUNOFDM.PDETFILTCOEFF6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF12 = RM_Field_SUNOFDM_PDETFILTCOEFF6_COEFF12(self)
        self.zz_fdict['COEFF12'] = self.COEFF12
        self.COEFF13 = RM_Field_SUNOFDM_PDETFILTCOEFF6_COEFF13(self)
        self.zz_fdict['COEFF13'] = self.COEFF13
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PDETFILTCOEFF7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PDETFILTCOEFF7, self).__init__(rmio, label,
            0xb500fc00, 0x078,
            'PDETFILTCOEFF7', 'SUNOFDM.PDETFILTCOEFF7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF14 = RM_Field_SUNOFDM_PDETFILTCOEFF7_COEFF14(self)
        self.zz_fdict['COEFF14'] = self.COEFF14
        self.COEFF15 = RM_Field_SUNOFDM_PDETFILTCOEFF7_COEFF15(self)
        self.zz_fdict['COEFF15'] = self.COEFF15
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_FELATENCIES(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_FELATENCIES, self).__init__(rmio, label,
            0xb500fc00, 0x07C,
            'FELATENCIES', 'SUNOFDM.FELATENCIES', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXLATENCY = RM_Field_SUNOFDM_FELATENCIES_RXLATENCY(self)
        self.zz_fdict['RXLATENCY'] = self.RXLATENCY
        self.TXLATENCY = RM_Field_SUNOFDM_FELATENCIES_TXLATENCY(self)
        self.zz_fdict['TXLATENCY'] = self.TXLATENCY
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_PAPR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_PAPR, self).__init__(rmio, label,
            0xb500fc00, 0x080,
            'PAPR', 'SUNOFDM.PAPR', 'read-write',
            u"",
            0x10001000, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENPAPR = RM_Field_SUNOFDM_PAPR_ENPAPR(self)
        self.zz_fdict['ENPAPR'] = self.ENPAPR
        self.GAINSAT = RM_Field_SUNOFDM_PAPR_GAINSAT(self)
        self.zz_fdict['GAINSAT'] = self.GAINSAT
        self.GAINATT = RM_Field_SUNOFDM_PAPR_GAINATT(self)
        self.zz_fdict['GAINATT'] = self.GAINATT
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCFG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCFG, self).__init__(rmio, label,
            0xb500fc00, 0x084,
            'TXFILTCFG', 'SUNOFDM.TXFILTCFG', 'read-write',
            u"",
            0x00000080, 0x013F77BF,
            0x00001000, 0x00002000,
            0x00003000)

        self.NTAPS = RM_Field_SUNOFDM_TXFILTCFG_NTAPS(self)
        self.zz_fdict['NTAPS'] = self.NTAPS
        self.SYMMETRIC = RM_Field_SUNOFDM_TXFILTCFG_SYMMETRIC(self)
        self.zz_fdict['SYMMETRIC'] = self.SYMMETRIC
        self.INTERP = RM_Field_SUNOFDM_TXFILTCFG_INTERP(self)
        self.zz_fdict['INTERP'] = self.INTERP
        self.DECIM = RM_Field_SUNOFDM_TXFILTCFG_DECIM(self)
        self.zz_fdict['DECIM'] = self.DECIM
        self.NSHIFT = RM_Field_SUNOFDM_TXFILTCFG_NSHIFT(self)
        self.zz_fdict['NSHIFT'] = self.NSHIFT
        self.SKIPFIRST = RM_Field_SUNOFDM_TXFILTCFG_SKIPFIRST(self)
        self.zz_fdict['SKIPFIRST'] = self.SKIPFIRST
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCOEFF0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCOEFF0, self).__init__(rmio, label,
            0xb500fc00, 0x088,
            'TXFILTCOEFF0', 'SUNOFDM.TXFILTCOEFF0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF0 = RM_Field_SUNOFDM_TXFILTCOEFF0_COEFF0(self)
        self.zz_fdict['COEFF0'] = self.COEFF0
        self.COEFF1 = RM_Field_SUNOFDM_TXFILTCOEFF0_COEFF1(self)
        self.zz_fdict['COEFF1'] = self.COEFF1
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCOEFF1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCOEFF1, self).__init__(rmio, label,
            0xb500fc00, 0x08C,
            'TXFILTCOEFF1', 'SUNOFDM.TXFILTCOEFF1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF2 = RM_Field_SUNOFDM_TXFILTCOEFF1_COEFF2(self)
        self.zz_fdict['COEFF2'] = self.COEFF2
        self.COEFF3 = RM_Field_SUNOFDM_TXFILTCOEFF1_COEFF3(self)
        self.zz_fdict['COEFF3'] = self.COEFF3
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCOEFF2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCOEFF2, self).__init__(rmio, label,
            0xb500fc00, 0x090,
            'TXFILTCOEFF2', 'SUNOFDM.TXFILTCOEFF2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF4 = RM_Field_SUNOFDM_TXFILTCOEFF2_COEFF4(self)
        self.zz_fdict['COEFF4'] = self.COEFF4
        self.COEFF5 = RM_Field_SUNOFDM_TXFILTCOEFF2_COEFF5(self)
        self.zz_fdict['COEFF5'] = self.COEFF5
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCOEFF3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCOEFF3, self).__init__(rmio, label,
            0xb500fc00, 0x094,
            'TXFILTCOEFF3', 'SUNOFDM.TXFILTCOEFF3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF6 = RM_Field_SUNOFDM_TXFILTCOEFF3_COEFF6(self)
        self.zz_fdict['COEFF6'] = self.COEFF6
        self.COEFF7 = RM_Field_SUNOFDM_TXFILTCOEFF3_COEFF7(self)
        self.zz_fdict['COEFF7'] = self.COEFF7
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCOEFF4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCOEFF4, self).__init__(rmio, label,
            0xb500fc00, 0x098,
            'TXFILTCOEFF4', 'SUNOFDM.TXFILTCOEFF4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF8 = RM_Field_SUNOFDM_TXFILTCOEFF4_COEFF8(self)
        self.zz_fdict['COEFF8'] = self.COEFF8
        self.COEFF9 = RM_Field_SUNOFDM_TXFILTCOEFF4_COEFF9(self)
        self.zz_fdict['COEFF9'] = self.COEFF9
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCOEFF5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCOEFF5, self).__init__(rmio, label,
            0xb500fc00, 0x09C,
            'TXFILTCOEFF5', 'SUNOFDM.TXFILTCOEFF5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF10 = RM_Field_SUNOFDM_TXFILTCOEFF5_COEFF10(self)
        self.zz_fdict['COEFF10'] = self.COEFF10
        self.COEFF11 = RM_Field_SUNOFDM_TXFILTCOEFF5_COEFF11(self)
        self.zz_fdict['COEFF11'] = self.COEFF11
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCOEFF6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCOEFF6, self).__init__(rmio, label,
            0xb500fc00, 0x0A0,
            'TXFILTCOEFF6', 'SUNOFDM.TXFILTCOEFF6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF12 = RM_Field_SUNOFDM_TXFILTCOEFF6_COEFF12(self)
        self.zz_fdict['COEFF12'] = self.COEFF12
        self.COEFF13 = RM_Field_SUNOFDM_TXFILTCOEFF6_COEFF13(self)
        self.zz_fdict['COEFF13'] = self.COEFF13
        self.__dict__['zz_frozen'] = True


class RM_Register_SUNOFDM_TXFILTCOEFF7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SUNOFDM_TXFILTCOEFF7, self).__init__(rmio, label,
            0xb500fc00, 0x0A4,
            'TXFILTCOEFF7', 'SUNOFDM.TXFILTCOEFF7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF14 = RM_Field_SUNOFDM_TXFILTCOEFF7_COEFF14(self)
        self.zz_fdict['COEFF14'] = self.COEFF14
        self.COEFF15 = RM_Field_SUNOFDM_TXFILTCOEFF7_COEFF15(self)
        self.zz_fdict['COEFF15'] = self.COEFF15
        self.__dict__['zz_frozen'] = True



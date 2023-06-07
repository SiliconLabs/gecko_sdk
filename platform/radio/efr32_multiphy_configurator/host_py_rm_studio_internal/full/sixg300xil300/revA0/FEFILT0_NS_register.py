
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . FEFILT0_NS_field import *


class RM_Register_FEFILT0_NS_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_IPVERSION, self).__init__(rmio, label,
            0xb8040000, 0x000,
            'IPVERSION', 'FEFILT0_NS.IPVERSION', 'read-only',
            u"",
            0x00000001, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_FEFILT0_NS_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_EN, self).__init__(rmio, label,
            0xb8040000, 0x004,
            'EN', 'FEFILT0_NS.EN', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_FEFILT0_NS_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.DISABLING = RM_Field_FEFILT0_NS_EN_DISABLING(self)
        self.zz_fdict['DISABLING'] = self.DISABLING
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_SWRST(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_SWRST, self).__init__(rmio, label,
            0xb8040000, 0x008,
            'SWRST', 'FEFILT0_NS.SWRST', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWRST = RM_Field_FEFILT0_NS_SWRST_SWRST(self)
        self.zz_fdict['SWRST'] = self.SWRST
        self.RESETTING = RM_Field_FEFILT0_NS_SWRST_RESETTING(self)
        self.zz_fdict['RESETTING'] = self.RESETTING
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_STATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_STATUS, self).__init__(rmio, label,
            0xb8040000, 0x00C,
            'STATUS', 'FEFILT0_NS.STATUS', 'read-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.FEFILTLOCKSTATUS = RM_Field_FEFILT0_NS_STATUS_FEFILTLOCKSTATUS(self)
        self.zz_fdict['FEFILTLOCKSTATUS'] = self.FEFILTLOCKSTATUS
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_LOCK(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_LOCK, self).__init__(rmio, label,
            0xb8040000, 0x010,
            'LOCK', 'FEFILT0_NS.LOCK', 'write-only',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FEFILTLOCKKEY = RM_Field_FEFILT0_NS_LOCK_FEFILTLOCKKEY(self)
        self.zz_fdict['FEFILTLOCKKEY'] = self.FEFILTLOCKKEY
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CFG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CFG, self).__init__(rmio, label,
            0xb8040000, 0x014,
            'CFG', 'FEFILT0_NS.CFG', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOSYNCRESETENABLE = RM_Field_FEFILT0_NS_CFG_LOSYNCRESETENABLE(self)
        self.zz_fdict['LOSYNCRESETENABLE'] = self.LOSYNCRESETENABLE
        self.CMUENRECONFIG = RM_Field_FEFILT0_NS_CFG_CMUENRECONFIG(self)
        self.zz_fdict['CMUENRECONFIG'] = self.CMUENRECONFIG
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CMD, self).__init__(rmio, label,
            0xb8040000, 0x018,
            'CMD', 'FEFILT0_NS.CMD', 'write-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWGAINCHANGE = RM_Field_FEFILT0_NS_CMD_SWGAINCHANGE(self)
        self.zz_fdict['SWGAINCHANGE'] = self.SWGAINCHANGE
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CF, self).__init__(rmio, label,
            0xb8040000, 0x100,
            'CF', 'FEFILT0_NS.CF', 'read-write',
            u"",
            0x00000000, 0xC001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DEC0 = RM_Field_FEFILT0_NS_CF_DEC0(self)
        self.zz_fdict['DEC0'] = self.DEC0
        self.DEC1 = RM_Field_FEFILT0_NS_CF_DEC1(self)
        self.zz_fdict['DEC1'] = self.DEC1
        self.ADCBITORDERI = RM_Field_FEFILT0_NS_CF_ADCBITORDERI(self)
        self.zz_fdict['ADCBITORDERI'] = self.ADCBITORDERI
        self.ADCBITORDERQ = RM_Field_FEFILT0_NS_CF_ADCBITORDERQ(self)
        self.zz_fdict['ADCBITORDERQ'] = self.ADCBITORDERQ
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_SRC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_SRC, self).__init__(rmio, label,
            0xb8040000, 0x104,
            'SRC', 'FEFILT0_NS.SRC', 'read-write',
            u"",
            0x00000000, 0x39CFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SRCRATIO = RM_Field_FEFILT0_NS_SRC_SRCRATIO(self)
        self.zz_fdict['SRCRATIO'] = self.SRCRATIO
        self.UPGAPS = RM_Field_FEFILT0_NS_SRC_UPGAPS(self)
        self.zz_fdict['UPGAPS'] = self.UPGAPS
        self.SRCENABLE = RM_Field_FEFILT0_NS_SRC_SRCENABLE(self)
        self.zz_fdict['SRCENABLE'] = self.SRCENABLE
        self.SRCSRD = RM_Field_FEFILT0_NS_SRC_SRCSRD(self)
        self.zz_fdict['SRCSRD'] = self.SRCSRD
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_DIGIGAINCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_DIGIGAINCTRL, self).__init__(rmio, label,
            0xb8040000, 0x108,
            'DIGIGAINCTRL', 'FEFILT0_NS.DIGIGAINCTRL', 'read-write',
            u"",
            0x00000000, 0x003FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DIGIGAINEN = RM_Field_FEFILT0_NS_DIGIGAINCTRL_DIGIGAINEN(self)
        self.zz_fdict['DIGIGAINEN'] = self.DIGIGAINEN
        self.DIGIGAIN = RM_Field_FEFILT0_NS_DIGIGAINCTRL_DIGIGAIN(self)
        self.zz_fdict['DIGIGAIN'] = self.DIGIGAIN
        self.DEC0GAIN = RM_Field_FEFILT0_NS_DIGIGAINCTRL_DEC0GAIN(self)
        self.zz_fdict['DEC0GAIN'] = self.DEC0GAIN
        self.DEC1GAIN = RM_Field_FEFILT0_NS_DIGIGAINCTRL_DEC1GAIN(self)
        self.zz_fdict['DEC1GAIN'] = self.DEC1GAIN
        self.BBSS = RM_Field_FEFILT0_NS_DIGIGAINCTRL_BBSS(self)
        self.zz_fdict['BBSS'] = self.BBSS
        self.DEC1LOG2X4 = RM_Field_FEFILT0_NS_DIGIGAINCTRL_DEC1LOG2X4(self)
        self.zz_fdict['DEC1LOG2X4'] = self.DEC1LOG2X4
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE00(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE00, self).__init__(rmio, label,
            0xb8040000, 0x10C,
            'CHFCOE00', 'FEFILT0_NS.CHFCOE00', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET0COEFF0 = RM_Field_FEFILT0_NS_CHFCOE00_SET0COEFF0(self)
        self.zz_fdict['SET0COEFF0'] = self.SET0COEFF0
        self.SET0COEFF1 = RM_Field_FEFILT0_NS_CHFCOE00_SET0COEFF1(self)
        self.zz_fdict['SET0COEFF1'] = self.SET0COEFF1
        self.SET0COEFF2 = RM_Field_FEFILT0_NS_CHFCOE00_SET0COEFF2(self)
        self.zz_fdict['SET0COEFF2'] = self.SET0COEFF2
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE01(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE01, self).__init__(rmio, label,
            0xb8040000, 0x110,
            'CHFCOE01', 'FEFILT0_NS.CHFCOE01', 'read-write',
            u"",
            0x00000000, 0x003FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET0COEFF3 = RM_Field_FEFILT0_NS_CHFCOE01_SET0COEFF3(self)
        self.zz_fdict['SET0COEFF3'] = self.SET0COEFF3
        self.SET0COEFF4 = RM_Field_FEFILT0_NS_CHFCOE01_SET0COEFF4(self)
        self.zz_fdict['SET0COEFF4'] = self.SET0COEFF4
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE02(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE02, self).__init__(rmio, label,
            0xb8040000, 0x114,
            'CHFCOE02', 'FEFILT0_NS.CHFCOE02', 'read-write',
            u"",
            0x00000000, 0x007FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET0COEFF5 = RM_Field_FEFILT0_NS_CHFCOE02_SET0COEFF5(self)
        self.zz_fdict['SET0COEFF5'] = self.SET0COEFF5
        self.SET0COEFF6 = RM_Field_FEFILT0_NS_CHFCOE02_SET0COEFF6(self)
        self.zz_fdict['SET0COEFF6'] = self.SET0COEFF6
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE03(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE03, self).__init__(rmio, label,
            0xb8040000, 0x118,
            'CHFCOE03', 'FEFILT0_NS.CHFCOE03', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET0COEFF7 = RM_Field_FEFILT0_NS_CHFCOE03_SET0COEFF7(self)
        self.zz_fdict['SET0COEFF7'] = self.SET0COEFF7
        self.SET0COEFF8 = RM_Field_FEFILT0_NS_CHFCOE03_SET0COEFF8(self)
        self.zz_fdict['SET0COEFF8'] = self.SET0COEFF8
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE04(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE04, self).__init__(rmio, label,
            0xb8040000, 0x11C,
            'CHFCOE04', 'FEFILT0_NS.CHFCOE04', 'read-write',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET0COEFF9 = RM_Field_FEFILT0_NS_CHFCOE04_SET0COEFF9(self)
        self.zz_fdict['SET0COEFF9'] = self.SET0COEFF9
        self.SET0COEFF10 = RM_Field_FEFILT0_NS_CHFCOE04_SET0COEFF10(self)
        self.zz_fdict['SET0COEFF10'] = self.SET0COEFF10
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE05(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE05, self).__init__(rmio, label,
            0xb8040000, 0x120,
            'CHFCOE05', 'FEFILT0_NS.CHFCOE05', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET0COEFF11 = RM_Field_FEFILT0_NS_CHFCOE05_SET0COEFF11(self)
        self.zz_fdict['SET0COEFF11'] = self.SET0COEFF11
        self.SET0COEFF12 = RM_Field_FEFILT0_NS_CHFCOE05_SET0COEFF12(self)
        self.zz_fdict['SET0COEFF12'] = self.SET0COEFF12
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE06(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE06, self).__init__(rmio, label,
            0xb8040000, 0x124,
            'CHFCOE06', 'FEFILT0_NS.CHFCOE06', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET0COEFF13 = RM_Field_FEFILT0_NS_CHFCOE06_SET0COEFF13(self)
        self.zz_fdict['SET0COEFF13'] = self.SET0COEFF13
        self.SET0COEFF14 = RM_Field_FEFILT0_NS_CHFCOE06_SET0COEFF14(self)
        self.zz_fdict['SET0COEFF14'] = self.SET0COEFF14
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE10, self).__init__(rmio, label,
            0xb8040000, 0x128,
            'CHFCOE10', 'FEFILT0_NS.CHFCOE10', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET1COEFF0 = RM_Field_FEFILT0_NS_CHFCOE10_SET1COEFF0(self)
        self.zz_fdict['SET1COEFF0'] = self.SET1COEFF0
        self.SET1COEFF1 = RM_Field_FEFILT0_NS_CHFCOE10_SET1COEFF1(self)
        self.zz_fdict['SET1COEFF1'] = self.SET1COEFF1
        self.SET1COEFF2 = RM_Field_FEFILT0_NS_CHFCOE10_SET1COEFF2(self)
        self.zz_fdict['SET1COEFF2'] = self.SET1COEFF2
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE11(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE11, self).__init__(rmio, label,
            0xb8040000, 0x12C,
            'CHFCOE11', 'FEFILT0_NS.CHFCOE11', 'read-write',
            u"",
            0x00000000, 0x003FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET1COEFF3 = RM_Field_FEFILT0_NS_CHFCOE11_SET1COEFF3(self)
        self.zz_fdict['SET1COEFF3'] = self.SET1COEFF3
        self.SET1COEFF4 = RM_Field_FEFILT0_NS_CHFCOE11_SET1COEFF4(self)
        self.zz_fdict['SET1COEFF4'] = self.SET1COEFF4
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE12(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE12, self).__init__(rmio, label,
            0xb8040000, 0x130,
            'CHFCOE12', 'FEFILT0_NS.CHFCOE12', 'read-write',
            u"",
            0x00000000, 0x007FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET1COEFF5 = RM_Field_FEFILT0_NS_CHFCOE12_SET1COEFF5(self)
        self.zz_fdict['SET1COEFF5'] = self.SET1COEFF5
        self.SET1COEFF6 = RM_Field_FEFILT0_NS_CHFCOE12_SET1COEFF6(self)
        self.zz_fdict['SET1COEFF6'] = self.SET1COEFF6
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE13(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE13, self).__init__(rmio, label,
            0xb8040000, 0x134,
            'CHFCOE13', 'FEFILT0_NS.CHFCOE13', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET1COEFF7 = RM_Field_FEFILT0_NS_CHFCOE13_SET1COEFF7(self)
        self.zz_fdict['SET1COEFF7'] = self.SET1COEFF7
        self.SET1COEFF8 = RM_Field_FEFILT0_NS_CHFCOE13_SET1COEFF8(self)
        self.zz_fdict['SET1COEFF8'] = self.SET1COEFF8
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE15(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE15, self).__init__(rmio, label,
            0xb8040000, 0x138,
            'CHFCOE15', 'FEFILT0_NS.CHFCOE15', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET1COEFF11 = RM_Field_FEFILT0_NS_CHFCOE15_SET1COEFF11(self)
        self.zz_fdict['SET1COEFF11'] = self.SET1COEFF11
        self.SET1COEFF12 = RM_Field_FEFILT0_NS_CHFCOE15_SET1COEFF12(self)
        self.zz_fdict['SET1COEFF12'] = self.SET1COEFF12
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE14(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE14, self).__init__(rmio, label,
            0xb8040000, 0x13C,
            'CHFCOE14', 'FEFILT0_NS.CHFCOE14', 'read-write',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET1COEFF9 = RM_Field_FEFILT0_NS_CHFCOE14_SET1COEFF9(self)
        self.zz_fdict['SET1COEFF9'] = self.SET1COEFF9
        self.SET1COEFF10 = RM_Field_FEFILT0_NS_CHFCOE14_SET1COEFF10(self)
        self.zz_fdict['SET1COEFF10'] = self.SET1COEFF10
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCOE16(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCOE16, self).__init__(rmio, label,
            0xb8040000, 0x140,
            'CHFCOE16', 'FEFILT0_NS.CHFCOE16', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SET1COEFF13 = RM_Field_FEFILT0_NS_CHFCOE16_SET1COEFF13(self)
        self.zz_fdict['SET1COEFF13'] = self.SET1COEFF13
        self.SET1COEFF14 = RM_Field_FEFILT0_NS_CHFCOE16_SET1COEFF14(self)
        self.zz_fdict['SET1COEFF14'] = self.SET1COEFF14
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CHFCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CHFCTRL, self).__init__(rmio, label,
            0xb8040000, 0x144,
            'CHFCTRL', 'FEFILT0_NS.CHFCTRL', 'read-write',
            u"",
            0x00000000, 0xFE000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.CHFLATENCY = RM_Field_FEFILT0_NS_CHFCTRL_CHFLATENCY(self)
        self.zz_fdict['CHFLATENCY'] = self.CHFLATENCY
        self.GAINREDUCTION = RM_Field_FEFILT0_NS_CHFCTRL_GAINREDUCTION(self)
        self.zz_fdict['GAINREDUCTION'] = self.GAINREDUCTION
        self.SWCOEFFEN = RM_Field_FEFILT0_NS_CHFCTRL_SWCOEFFEN(self)
        self.zz_fdict['SWCOEFFEN'] = self.SWCOEFFEN
        self.SWCOEFFSELECTION = RM_Field_FEFILT0_NS_CHFCTRL_SWCOEFFSELECTION(self)
        self.zz_fdict['SWCOEFFSELECTION'] = self.SWCOEFFSELECTION
        self.FWSWCOEFFEN = RM_Field_FEFILT0_NS_CHFCTRL_FWSWCOEFFEN(self)
        self.zz_fdict['FWSWCOEFFEN'] = self.FWSWCOEFFEN
        self.FWSELCOEFF = RM_Field_FEFILT0_NS_CHFCTRL_FWSELCOEFF(self)
        self.zz_fdict['FWSELCOEFF'] = self.FWSELCOEFF
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_CTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_CTRL, self).__init__(rmio, label,
            0xb8040000, 0x14C,
            'CTRL', 'FEFILT0_NS.CTRL', 'read-write',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWAFCADJRX = RM_Field_FEFILT0_NS_CTRL_SWAFCADJRX(self)
        self.zz_fdict['SWAFCADJRX'] = self.SWAFCADJRX
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_BLANKING(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_BLANKING, self).__init__(rmio, label,
            0xb8040000, 0x150,
            'BLANKING', 'FEFILT0_NS.BLANKING', 'read-write',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BLANKDELAY = RM_Field_FEFILT0_NS_BLANKING_BLANKDELAY(self)
        self.zz_fdict['BLANKDELAY'] = self.BLANKDELAY
        self.BLANKDURATION = RM_Field_FEFILT0_NS_BLANKING_BLANKDURATION(self)
        self.zz_fdict['BLANKDURATION'] = self.BLANKDURATION
        self.BLANKMODE = RM_Field_FEFILT0_NS_BLANKING_BLANKMODE(self)
        self.zz_fdict['BLANKMODE'] = self.BLANKMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_RSSIFILT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_RSSIFILT, self).__init__(rmio, label,
            0xb8040000, 0x154,
            'RSSIFILT', 'FEFILT0_NS.RSSIFILT', 'read-write',
            u"",
            0x00000000, 0x001FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RSSIFILTEN = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTEN(self)
        self.zz_fdict['RSSIFILTEN'] = self.RSSIFILTEN
        self.RSSIFILTDEC = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTDEC(self)
        self.zz_fdict['RSSIFILTDEC'] = self.RSSIFILTDEC
        self.RSSIFILTGAIN = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTGAIN(self)
        self.zz_fdict['RSSIFILTGAIN'] = self.RSSIFILTGAIN
        self.RSSIFILTCOEF0 = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTCOEF0(self)
        self.zz_fdict['RSSIFILTCOEF0'] = self.RSSIFILTCOEF0
        self.RSSIFILTCOEF1 = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTCOEF1(self)
        self.zz_fdict['RSSIFILTCOEF1'] = self.RSSIFILTCOEF1
        self.RSSIFILTCOEF2 = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTCOEF2(self)
        self.zz_fdict['RSSIFILTCOEF2'] = self.RSSIFILTCOEF2
        self.RSSIFILTCOEF3 = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTCOEF3(self)
        self.zz_fdict['RSSIFILTCOEF3'] = self.RSSIFILTCOEF3
        self.RSSIFILTCOEF4 = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTCOEF4(self)
        self.zz_fdict['RSSIFILTCOEF4'] = self.RSSIFILTCOEF4
        self.RSSIFILTCOEF5 = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTCOEF5(self)
        self.zz_fdict['RSSIFILTCOEF5'] = self.RSSIFILTCOEF5
        self.RSSIFILTCOEF6 = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTCOEF6(self)
        self.zz_fdict['RSSIFILTCOEF6'] = self.RSSIFILTCOEF6
        self.RSSIFILTCOEF7 = RM_Field_FEFILT0_NS_RSSIFILT_RSSIFILTCOEF7(self)
        self.zz_fdict['RSSIFILTCOEF7'] = self.RSSIFILTCOEF7
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_DIGMIXCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_DIGMIXCTRL, self).__init__(rmio, label,
            0xb8040000, 0x200,
            'DIGMIXCTRL', 'FEFILT0_NS.DIGMIXCTRL', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DIGMIXFREQ = RM_Field_FEFILT0_NS_DIGMIXCTRL_DIGMIXFREQ(self)
        self.zz_fdict['DIGMIXFREQ'] = self.DIGMIXFREQ
        self.DIGIQSWAPEN = RM_Field_FEFILT0_NS_DIGMIXCTRL_DIGIQSWAPEN(self)
        self.zz_fdict['DIGIQSWAPEN'] = self.DIGIQSWAPEN
        self.MIXERCONJ = RM_Field_FEFILT0_NS_DIGMIXCTRL_MIXERCONJ(self)
        self.zz_fdict['MIXERCONJ'] = self.MIXERCONJ
        self.DIGMIXFBENABLE = RM_Field_FEFILT0_NS_DIGMIXCTRL_DIGMIXFBENABLE(self)
        self.zz_fdict['DIGMIXFBENABLE'] = self.DIGMIXFBENABLE
        self.ZIFMODEENABLE = RM_Field_FEFILT0_NS_DIGMIXCTRL_ZIFMODEENABLE(self)
        self.zz_fdict['ZIFMODEENABLE'] = self.ZIFMODEENABLE
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_DCCOMP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_DCCOMP, self).__init__(rmio, label,
            0xb8040000, 0x220,
            'DCCOMP', 'FEFILT0_NS.DCCOMP', 'read-write',
            u"",
            0x00000030, 0x01FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCESTIEN = RM_Field_FEFILT0_NS_DCCOMP_DCESTIEN(self)
        self.zz_fdict['DCESTIEN'] = self.DCESTIEN
        self.DCCOMPEN = RM_Field_FEFILT0_NS_DCCOMP_DCCOMPEN(self)
        self.zz_fdict['DCCOMPEN'] = self.DCCOMPEN
        self.DCRSTEN = RM_Field_FEFILT0_NS_DCCOMP_DCRSTEN(self)
        self.zz_fdict['DCRSTEN'] = self.DCRSTEN
        self.DCCOMPFREEZE = RM_Field_FEFILT0_NS_DCCOMP_DCCOMPFREEZE(self)
        self.zz_fdict['DCCOMPFREEZE'] = self.DCCOMPFREEZE
        self.DCCOMPGEAR = RM_Field_FEFILT0_NS_DCCOMP_DCCOMPGEAR(self)
        self.zz_fdict['DCCOMPGEAR'] = self.DCCOMPGEAR
        self.DCLIMIT = RM_Field_FEFILT0_NS_DCCOMP_DCLIMIT(self)
        self.zz_fdict['DCLIMIT'] = self.DCLIMIT
        self.DCGAINGEAREN = RM_Field_FEFILT0_NS_DCCOMP_DCGAINGEAREN(self)
        self.zz_fdict['DCGAINGEAREN'] = self.DCGAINGEAREN
        self.DCGAINGEAR = RM_Field_FEFILT0_NS_DCCOMP_DCGAINGEAR(self)
        self.zz_fdict['DCGAINGEAR'] = self.DCGAINGEAR
        self.DCGAINGEARSMPS = RM_Field_FEFILT0_NS_DCCOMP_DCGAINGEARSMPS(self)
        self.zz_fdict['DCGAINGEARSMPS'] = self.DCGAINGEARSMPS
        self.GEARGAINCHANGESEL = RM_Field_FEFILT0_NS_DCCOMP_GEARGAINCHANGESEL(self)
        self.zz_fdict['GEARGAINCHANGESEL'] = self.GEARGAINCHANGESEL
        self.GEARFREEZEENABLE = RM_Field_FEFILT0_NS_DCCOMP_GEARFREEZEENABLE(self)
        self.zz_fdict['GEARFREEZEENABLE'] = self.GEARFREEZEENABLE
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_DCCOMPFILTINIT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_DCCOMPFILTINIT, self).__init__(rmio, label,
            0xb8040000, 0x224,
            'DCCOMPFILTINIT', 'FEFILT0_NS.DCCOMPFILTINIT', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCCOMPINITVALI = RM_Field_FEFILT0_NS_DCCOMPFILTINIT_DCCOMPINITVALI(self)
        self.zz_fdict['DCCOMPINITVALI'] = self.DCCOMPINITVALI
        self.DCCOMPINITVALQ = RM_Field_FEFILT0_NS_DCCOMPFILTINIT_DCCOMPINITVALQ(self)
        self.zz_fdict['DCCOMPINITVALQ'] = self.DCCOMPINITVALQ
        self.DCCOMPINIT = RM_Field_FEFILT0_NS_DCCOMPFILTINIT_DCCOMPINIT(self)
        self.zz_fdict['DCCOMPINIT'] = self.DCCOMPINIT
        self.DCCOMPFORCEINIT = RM_Field_FEFILT0_NS_DCCOMPFILTINIT_DCCOMPFORCEINIT(self)
        self.zz_fdict['DCCOMPFORCEINIT'] = self.DCCOMPFORCEINIT
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_DCESTI(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_DCESTI, self).__init__(rmio, label,
            0xb8040000, 0x228,
            'DCESTI', 'FEFILT0_NS.DCESTI', 'read-only',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCCOMPESTIVALI = RM_Field_FEFILT0_NS_DCESTI_DCCOMPESTIVALI(self)
        self.zz_fdict['DCCOMPESTIVALI'] = self.DCCOMPESTIVALI
        self.DCCOMPESTIVALQ = RM_Field_FEFILT0_NS_DCESTI_DCCOMPESTIVALQ(self)
        self.zz_fdict['DCCOMPESTIVALQ'] = self.DCCOMPESTIVALQ
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_IRCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_IRCAL, self).__init__(rmio, label,
            0xb8040000, 0x270,
            'IRCAL', 'FEFILT0_NS.IRCAL', 'read-write',
            u"",
            0x00000000, 0x0000FFBF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IRCALEN = RM_Field_FEFILT0_NS_IRCAL_IRCALEN(self)
        self.zz_fdict['IRCALEN'] = self.IRCALEN
        self.MURSHF = RM_Field_FEFILT0_NS_IRCAL_MURSHF(self)
        self.zz_fdict['MURSHF'] = self.MURSHF
        self.MUISHF = RM_Field_FEFILT0_NS_IRCAL_MUISHF(self)
        self.zz_fdict['MUISHF'] = self.MUISHF
        self.IRCORREN = RM_Field_FEFILT0_NS_IRCAL_IRCORREN(self)
        self.zz_fdict['IRCORREN'] = self.IRCORREN
        self.IRCALCOEFRSTCMD = RM_Field_FEFILT0_NS_IRCAL_IRCALCOEFRSTCMD(self)
        self.zz_fdict['IRCALCOEFRSTCMD'] = self.IRCALCOEFRSTCMD
        self.IRCALIFADCDBG = RM_Field_FEFILT0_NS_IRCAL_IRCALIFADCDBG(self)
        self.zz_fdict['IRCALIFADCDBG'] = self.IRCALIFADCDBG
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_IRCALCOEF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_IRCALCOEF, self).__init__(rmio, label,
            0xb8040000, 0x274,
            'IRCALCOEF', 'FEFILT0_NS.IRCALCOEF', 'read-only',
            u"",
            0x00000000, 0x7FFF7FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CRV = RM_Field_FEFILT0_NS_IRCALCOEF_CRV(self)
        self.zz_fdict['CRV'] = self.CRV
        self.CIV = RM_Field_FEFILT0_NS_IRCALCOEF_CIV(self)
        self.zz_fdict['CIV'] = self.CIV
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_IRCALCOEFWR0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_IRCALCOEFWR0, self).__init__(rmio, label,
            0xb8040000, 0x320,
            'IRCALCOEFWR0', 'FEFILT0_NS.IRCALCOEFWR0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CRVWD = RM_Field_FEFILT0_NS_IRCALCOEFWR0_CRVWD(self)
        self.zz_fdict['CRVWD'] = self.CRVWD
        self.CRVWEN = RM_Field_FEFILT0_NS_IRCALCOEFWR0_CRVWEN(self)
        self.zz_fdict['CRVWEN'] = self.CRVWEN
        self.CIVWD = RM_Field_FEFILT0_NS_IRCALCOEFWR0_CIVWD(self)
        self.zz_fdict['CIVWD'] = self.CIVWD
        self.CIVWEN = RM_Field_FEFILT0_NS_IRCALCOEFWR0_CIVWEN(self)
        self.zz_fdict['CIVWEN'] = self.CIVWEN
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_IRCALCOEFWR1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_IRCALCOEFWR1, self).__init__(rmio, label,
            0xb8040000, 0x324,
            'IRCALCOEFWR1', 'FEFILT0_NS.IRCALCOEFWR1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CRVWD = RM_Field_FEFILT0_NS_IRCALCOEFWR1_CRVWD(self)
        self.zz_fdict['CRVWD'] = self.CRVWD
        self.CRVWEN = RM_Field_FEFILT0_NS_IRCALCOEFWR1_CRVWEN(self)
        self.zz_fdict['CRVWEN'] = self.CRVWEN
        self.CIVWD = RM_Field_FEFILT0_NS_IRCALCOEFWR1_CIVWD(self)
        self.zz_fdict['CIVWD'] = self.CIVWD
        self.CIVWEN = RM_Field_FEFILT0_NS_IRCALCOEFWR1_CIVWEN(self)
        self.zz_fdict['CIVWEN'] = self.CIVWEN
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_ADPC3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_ADPC3, self).__init__(rmio, label,
            0xb8040000, 0x3E0,
            'ADPC3', 'FEFILT0_NS.ADPC3', 'read-write',
            u"",
            0x01005008, 0x03FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBBSSEN = RM_Field_FEFILT0_NS_ADPC3_ADBBSSEN(self)
        self.zz_fdict['ADBBSSEN'] = self.ADBBSSEN
        self.ADBBSSFILTLENGTH = RM_Field_FEFILT0_NS_ADPC3_ADBBSSFILTLENGTH(self)
        self.zz_fdict['ADBBSSFILTLENGTH'] = self.ADBBSSFILTLENGTH
        self.ADBBSSAVGEN = RM_Field_FEFILT0_NS_ADPC3_ADBBSSAVGEN(self)
        self.zz_fdict['ADBBSSAVGEN'] = self.ADBBSSAVGEN
        self.ADBBSSAVGPER = RM_Field_FEFILT0_NS_ADPC3_ADBBSSAVGPER(self)
        self.zz_fdict['ADBBSSAVGPER'] = self.ADBBSSAVGPER
        self.ADBBSSAMPMANT = RM_Field_FEFILT0_NS_ADPC3_ADBBSSAMPMANT(self)
        self.zz_fdict['ADBBSSAMPMANT'] = self.ADBBSSAMPMANT
        self.ADBBSSAMPEXP = RM_Field_FEFILT0_NS_ADPC3_ADBBSSAMPEXP(self)
        self.zz_fdict['ADBBSSAMPEXP'] = self.ADBBSSAMPEXP
        self.ADBBSSAVGWAIT = RM_Field_FEFILT0_NS_ADPC3_ADBBSSAVGWAIT(self)
        self.zz_fdict['ADBBSSAVGWAIT'] = self.ADBBSSAVGWAIT
        self.ADBBSSAVGFREEZE = RM_Field_FEFILT0_NS_ADPC3_ADBBSSAVGFREEZE(self)
        self.zz_fdict['ADBBSSAVGFREEZE'] = self.ADBBSSAVGFREEZE
        self.ADBBSSSELWRDATA = RM_Field_FEFILT0_NS_ADPC3_ADBBSSSELWRDATA(self)
        self.zz_fdict['ADBBSSSELWRDATA'] = self.ADBBSSSELWRDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_ADPC4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_ADPC4, self).__init__(rmio, label,
            0xb8040000, 0x3E4,
            'ADPC4', 'FEFILT0_NS.ADPC4', 'read-write',
            u"",
            0x1F1F1F1F, 0x1F1F1F1F,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBBSSAMPLUT0 = RM_Field_FEFILT0_NS_ADPC4_ADBBSSAMPLUT0(self)
        self.zz_fdict['ADBBSSAMPLUT0'] = self.ADBBSSAMPLUT0
        self.ADBBSSAMPLUT1 = RM_Field_FEFILT0_NS_ADPC4_ADBBSSAMPLUT1(self)
        self.zz_fdict['ADBBSSAMPLUT1'] = self.ADBBSSAMPLUT1
        self.ADBBSSAMPLUT2 = RM_Field_FEFILT0_NS_ADPC4_ADBBSSAMPLUT2(self)
        self.zz_fdict['ADBBSSAMPLUT2'] = self.ADBBSSAMPLUT2
        self.ADBBSSAMPLUT3 = RM_Field_FEFILT0_NS_ADPC4_ADBBSSAMPLUT3(self)
        self.zz_fdict['ADBBSSAMPLUT3'] = self.ADBBSSAMPLUT3
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_ADPC5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_ADPC5, self).__init__(rmio, label,
            0xb8040000, 0x3E8,
            'ADPC5', 'FEFILT0_NS.ADPC5', 'read-write',
            u"",
            0x1B1F1F1F, 0x1F1F1F1F,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBBSSAMPLUT4 = RM_Field_FEFILT0_NS_ADPC5_ADBBSSAMPLUT4(self)
        self.zz_fdict['ADBBSSAMPLUT4'] = self.ADBBSSAMPLUT4
        self.ADBBSSAMPLUT5 = RM_Field_FEFILT0_NS_ADPC5_ADBBSSAMPLUT5(self)
        self.zz_fdict['ADBBSSAMPLUT5'] = self.ADBBSSAMPLUT5
        self.ADBBSSAMPLUT6 = RM_Field_FEFILT0_NS_ADPC5_ADBBSSAMPLUT6(self)
        self.zz_fdict['ADBBSSAMPLUT6'] = self.ADBBSSAMPLUT6
        self.ADBBSSAMPLUT7 = RM_Field_FEFILT0_NS_ADPC5_ADBBSSAMPLUT7(self)
        self.zz_fdict['ADBBSSAMPLUT7'] = self.ADBBSSAMPLUT7
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_ADPC6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_ADPC6, self).__init__(rmio, label,
            0xb8040000, 0x3EC,
            'ADPC6', 'FEFILT0_NS.ADPC6', 'read-write',
            u"",
            0x11131518, 0x1F1F1F1F,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBBSSAMPLUT8 = RM_Field_FEFILT0_NS_ADPC6_ADBBSSAMPLUT8(self)
        self.zz_fdict['ADBBSSAMPLUT8'] = self.ADBBSSAMPLUT8
        self.ADBBSSAMPLUT9 = RM_Field_FEFILT0_NS_ADPC6_ADBBSSAMPLUT9(self)
        self.zz_fdict['ADBBSSAMPLUT9'] = self.ADBBSSAMPLUT9
        self.ADBBSSAMPLUT10 = RM_Field_FEFILT0_NS_ADPC6_ADBBSSAMPLUT10(self)
        self.zz_fdict['ADBBSSAMPLUT10'] = self.ADBBSSAMPLUT10
        self.ADBBSSAMPLUT11 = RM_Field_FEFILT0_NS_ADPC6_ADBBSSAMPLUT11(self)
        self.zz_fdict['ADBBSSAMPLUT11'] = self.ADBBSSAMPLUT11
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_ADPC7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_ADPC7, self).__init__(rmio, label,
            0xb8040000, 0x3F0,
            'ADPC7', 'FEFILT0_NS.ADPC7', 'read-write',
            u"",
            0x0C0D0E10, 0x1F1F1F1F,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBBSSAMPLUT12 = RM_Field_FEFILT0_NS_ADPC7_ADBBSSAMPLUT12(self)
        self.zz_fdict['ADBBSSAMPLUT12'] = self.ADBBSSAMPLUT12
        self.ADBBSSAMPLUT13 = RM_Field_FEFILT0_NS_ADPC7_ADBBSSAMPLUT13(self)
        self.zz_fdict['ADBBSSAMPLUT13'] = self.ADBBSSAMPLUT13
        self.ADBBSSAMPLUT14 = RM_Field_FEFILT0_NS_ADPC7_ADBBSSAMPLUT14(self)
        self.zz_fdict['ADBBSSAMPLUT14'] = self.ADBBSSAMPLUT14
        self.ADBBSSAMPLUT15 = RM_Field_FEFILT0_NS_ADPC7_ADBBSSAMPLUT15(self)
        self.zz_fdict['ADBBSSAMPLUT15'] = self.ADBBSSAMPLUT15
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_ADPC9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_ADPC9, self).__init__(rmio, label,
            0xb8040000, 0x3F8,
            'ADPC9', 'FEFILT0_NS.ADPC9', 'read-write',
            u"",
            0x00000000, 0x01FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBBSSAMPAVGLIM = RM_Field_FEFILT0_NS_ADPC9_ADBBSSAMPAVGLIM(self)
        self.zz_fdict['ADBBSSAMPAVGLIM'] = self.ADBBSSAMPAVGLIM
        self.ADBBSSAMPTHR = RM_Field_FEFILT0_NS_ADPC9_ADBBSSAMPTHR(self)
        self.zz_fdict['ADBBSSAMPTHR'] = self.ADBBSSAMPTHR
        self.ADBBSSSYNCEN = RM_Field_FEFILT0_NS_ADPC9_ADBBSSSYNCEN(self)
        self.zz_fdict['ADBBSSSYNCEN'] = self.ADBBSSSYNCEN
        self.ADBBSSUPTHR = RM_Field_FEFILT0_NS_ADPC9_ADBBSSUPTHR(self)
        self.zz_fdict['ADBBSSUPTHR'] = self.ADBBSSUPTHR
        self.ADBBSSDNTHR = RM_Field_FEFILT0_NS_ADPC9_ADBBSSDNTHR(self)
        self.zz_fdict['ADBBSSDNTHR'] = self.ADBBSSDNTHR
        self.__dict__['zz_frozen'] = True


class RM_Register_FEFILT0_NS_ADPC10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FEFILT0_NS_ADPC10, self).__init__(rmio, label,
            0xb8040000, 0x3FC,
            'ADPC10', 'FEFILT0_NS.ADPC10', 'read-write',
            u"",
            0x00000000, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBBSSAMPJUMP = RM_Field_FEFILT0_NS_ADPC10_ADBBSSAMPJUMP(self)
        self.zz_fdict['ADBBSSAMPJUMP'] = self.ADBBSSAMPJUMP
        self.ADBBSSCHANGEEN = RM_Field_FEFILT0_NS_ADPC10_ADBBSSCHANGEEN(self)
        self.zz_fdict['ADBBSSCHANGEEN'] = self.ADBBSSCHANGEEN
        self.ADBBSSCHGUPTHR = RM_Field_FEFILT0_NS_ADPC10_ADBBSSCHGUPTHR(self)
        self.zz_fdict['ADBBSSCHGUPTHR'] = self.ADBBSSCHGUPTHR
        self.ADBBSSCHGDNTHR = RM_Field_FEFILT0_NS_ADPC10_ADBBSSCHGDNTHR(self)
        self.zz_fdict['ADBBSSCHGDNTHR'] = self.ADBBSSCHGDNTHR
        self.__dict__['zz_frozen'] = True



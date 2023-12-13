
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . SMCTRL_NS_field import *


class RM_Register_SMCTRL_NS_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_IPVERSION, self).__init__(rmio, label,
            0xb6040000, 0x000,
            'IPVERSION', 'SMCTRL_NS.IPVERSION', 'read-only',
            u"",
            0x00000001, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_SMCTRL_NS_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_EN, self).__init__(rmio, label,
            0xb6040000, 0x004,
            'EN', 'SMCTRL_NS.EN', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_SMCTRL_NS_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.DISABLING = RM_Field_SMCTRL_NS_EN_DISABLING(self)
        self.zz_fdict['DISABLING'] = self.DISABLING
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SWRST(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SWRST, self).__init__(rmio, label,
            0xb6040000, 0x008,
            'SWRST', 'SMCTRL_NS.SWRST', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWRST = RM_Field_SMCTRL_NS_SWRST_SWRST(self)
        self.zz_fdict['SWRST'] = self.SWRST
        self.RESETTING = RM_Field_SMCTRL_NS_SWRST_RESETTING(self)
        self.zz_fdict['RESETTING'] = self.RESETTING
        self.COMBRESETTING = RM_Field_SMCTRL_NS_SWRST_COMBRESETTING(self)
        self.zz_fdict['COMBRESETTING'] = self.COMBRESETTING
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_MAINIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_MAINIF, self).__init__(rmio, label,
            0xb6040000, 0x010,
            'MAINIF', 'SMCTRL_NS.MAINIF', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MAINIF0 = RM_Field_SMCTRL_NS_MAINIF_MAINIF0(self)
        self.zz_fdict['MAINIF0'] = self.MAINIF0
        self.MAINIF1 = RM_Field_SMCTRL_NS_MAINIF_MAINIF1(self)
        self.zz_fdict['MAINIF1'] = self.MAINIF1
        self.MAINIF2 = RM_Field_SMCTRL_NS_MAINIF_MAINIF2(self)
        self.zz_fdict['MAINIF2'] = self.MAINIF2
        self.MAINIF3 = RM_Field_SMCTRL_NS_MAINIF_MAINIF3(self)
        self.zz_fdict['MAINIF3'] = self.MAINIF3
        self.MAINIF4 = RM_Field_SMCTRL_NS_MAINIF_MAINIF4(self)
        self.zz_fdict['MAINIF4'] = self.MAINIF4
        self.MAINIF5 = RM_Field_SMCTRL_NS_MAINIF_MAINIF5(self)
        self.zz_fdict['MAINIF5'] = self.MAINIF5
        self.MAINIF6 = RM_Field_SMCTRL_NS_MAINIF_MAINIF6(self)
        self.zz_fdict['MAINIF6'] = self.MAINIF6
        self.MAINIF7 = RM_Field_SMCTRL_NS_MAINIF_MAINIF7(self)
        self.zz_fdict['MAINIF7'] = self.MAINIF7
        self.MAINIF8 = RM_Field_SMCTRL_NS_MAINIF_MAINIF8(self)
        self.zz_fdict['MAINIF8'] = self.MAINIF8
        self.MAINIF9 = RM_Field_SMCTRL_NS_MAINIF_MAINIF9(self)
        self.zz_fdict['MAINIF9'] = self.MAINIF9
        self.MAINIF10 = RM_Field_SMCTRL_NS_MAINIF_MAINIF10(self)
        self.zz_fdict['MAINIF10'] = self.MAINIF10
        self.MAINIF11 = RM_Field_SMCTRL_NS_MAINIF_MAINIF11(self)
        self.zz_fdict['MAINIF11'] = self.MAINIF11
        self.MAINIF12 = RM_Field_SMCTRL_NS_MAINIF_MAINIF12(self)
        self.zz_fdict['MAINIF12'] = self.MAINIF12
        self.MAINIF13 = RM_Field_SMCTRL_NS_MAINIF_MAINIF13(self)
        self.zz_fdict['MAINIF13'] = self.MAINIF13
        self.MAINIF14 = RM_Field_SMCTRL_NS_MAINIF_MAINIF14(self)
        self.zz_fdict['MAINIF14'] = self.MAINIF14
        self.MAINIF15 = RM_Field_SMCTRL_NS_MAINIF_MAINIF15(self)
        self.zz_fdict['MAINIF15'] = self.MAINIF15
        self.MAINIF16 = RM_Field_SMCTRL_NS_MAINIF_MAINIF16(self)
        self.zz_fdict['MAINIF16'] = self.MAINIF16
        self.MAINIF17 = RM_Field_SMCTRL_NS_MAINIF_MAINIF17(self)
        self.zz_fdict['MAINIF17'] = self.MAINIF17
        self.MAINIF18 = RM_Field_SMCTRL_NS_MAINIF_MAINIF18(self)
        self.zz_fdict['MAINIF18'] = self.MAINIF18
        self.MAINIF19 = RM_Field_SMCTRL_NS_MAINIF_MAINIF19(self)
        self.zz_fdict['MAINIF19'] = self.MAINIF19
        self.MAINIF20 = RM_Field_SMCTRL_NS_MAINIF_MAINIF20(self)
        self.zz_fdict['MAINIF20'] = self.MAINIF20
        self.MAINIF21 = RM_Field_SMCTRL_NS_MAINIF_MAINIF21(self)
        self.zz_fdict['MAINIF21'] = self.MAINIF21
        self.MAINIF22 = RM_Field_SMCTRL_NS_MAINIF_MAINIF22(self)
        self.zz_fdict['MAINIF22'] = self.MAINIF22
        self.MAINIF23 = RM_Field_SMCTRL_NS_MAINIF_MAINIF23(self)
        self.zz_fdict['MAINIF23'] = self.MAINIF23
        self.MAINIF24 = RM_Field_SMCTRL_NS_MAINIF_MAINIF24(self)
        self.zz_fdict['MAINIF24'] = self.MAINIF24
        self.MAINIF25 = RM_Field_SMCTRL_NS_MAINIF_MAINIF25(self)
        self.zz_fdict['MAINIF25'] = self.MAINIF25
        self.MAINIF26 = RM_Field_SMCTRL_NS_MAINIF_MAINIF26(self)
        self.zz_fdict['MAINIF26'] = self.MAINIF26
        self.MAINIF27 = RM_Field_SMCTRL_NS_MAINIF_MAINIF27(self)
        self.zz_fdict['MAINIF27'] = self.MAINIF27
        self.MAINIF28 = RM_Field_SMCTRL_NS_MAINIF_MAINIF28(self)
        self.zz_fdict['MAINIF28'] = self.MAINIF28
        self.MAINIF29 = RM_Field_SMCTRL_NS_MAINIF_MAINIF29(self)
        self.zz_fdict['MAINIF29'] = self.MAINIF29
        self.MAINIF30 = RM_Field_SMCTRL_NS_MAINIF_MAINIF30(self)
        self.zz_fdict['MAINIF30'] = self.MAINIF30
        self.MAINIF31 = RM_Field_SMCTRL_NS_MAINIF_MAINIF31(self)
        self.zz_fdict['MAINIF31'] = self.MAINIF31
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_MAINIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_MAINIEN, self).__init__(rmio, label,
            0xb6040000, 0x014,
            'MAINIEN', 'SMCTRL_NS.MAINIEN', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MAINIEN0 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN0(self)
        self.zz_fdict['MAINIEN0'] = self.MAINIEN0
        self.MAINIEN1 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN1(self)
        self.zz_fdict['MAINIEN1'] = self.MAINIEN1
        self.MAINIEN2 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN2(self)
        self.zz_fdict['MAINIEN2'] = self.MAINIEN2
        self.MAINIEN3 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN3(self)
        self.zz_fdict['MAINIEN3'] = self.MAINIEN3
        self.MAINIEN4 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN4(self)
        self.zz_fdict['MAINIEN4'] = self.MAINIEN4
        self.MAINIEN5 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN5(self)
        self.zz_fdict['MAINIEN5'] = self.MAINIEN5
        self.MAINIEN6 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN6(self)
        self.zz_fdict['MAINIEN6'] = self.MAINIEN6
        self.MAINIEN7 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN7(self)
        self.zz_fdict['MAINIEN7'] = self.MAINIEN7
        self.MAINIEN8 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN8(self)
        self.zz_fdict['MAINIEN8'] = self.MAINIEN8
        self.MAINIEN9 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN9(self)
        self.zz_fdict['MAINIEN9'] = self.MAINIEN9
        self.MAINIEN10 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN10(self)
        self.zz_fdict['MAINIEN10'] = self.MAINIEN10
        self.MAINIEN11 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN11(self)
        self.zz_fdict['MAINIEN11'] = self.MAINIEN11
        self.MAINIEN12 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN12(self)
        self.zz_fdict['MAINIEN12'] = self.MAINIEN12
        self.MAINIEN13 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN13(self)
        self.zz_fdict['MAINIEN13'] = self.MAINIEN13
        self.MAINIEN14 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN14(self)
        self.zz_fdict['MAINIEN14'] = self.MAINIEN14
        self.MAINIEN15 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN15(self)
        self.zz_fdict['MAINIEN15'] = self.MAINIEN15
        self.MAINIEN16 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN16(self)
        self.zz_fdict['MAINIEN16'] = self.MAINIEN16
        self.MAINIEN17 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN17(self)
        self.zz_fdict['MAINIEN17'] = self.MAINIEN17
        self.MAINIEN18 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN18(self)
        self.zz_fdict['MAINIEN18'] = self.MAINIEN18
        self.MAINIEN19 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN19(self)
        self.zz_fdict['MAINIEN19'] = self.MAINIEN19
        self.MAINIEN20 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN20(self)
        self.zz_fdict['MAINIEN20'] = self.MAINIEN20
        self.MAINIEN21 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN21(self)
        self.zz_fdict['MAINIEN21'] = self.MAINIEN21
        self.MAINIEN22 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN22(self)
        self.zz_fdict['MAINIEN22'] = self.MAINIEN22
        self.MAINIEN23 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN23(self)
        self.zz_fdict['MAINIEN23'] = self.MAINIEN23
        self.MAINIEN24 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN24(self)
        self.zz_fdict['MAINIEN24'] = self.MAINIEN24
        self.MAINIEN25 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN25(self)
        self.zz_fdict['MAINIEN25'] = self.MAINIEN25
        self.MAINIEN26 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN26(self)
        self.zz_fdict['MAINIEN26'] = self.MAINIEN26
        self.MAINIEN27 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN27(self)
        self.zz_fdict['MAINIEN27'] = self.MAINIEN27
        self.MAINIEN28 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN28(self)
        self.zz_fdict['MAINIEN28'] = self.MAINIEN28
        self.MAINIEN29 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN29(self)
        self.zz_fdict['MAINIEN29'] = self.MAINIEN29
        self.MAINIEN30 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN30(self)
        self.zz_fdict['MAINIEN30'] = self.MAINIEN30
        self.MAINIEN31 = RM_Field_SMCTRL_NS_MAINIEN_MAINIEN31(self)
        self.zz_fdict['MAINIEN31'] = self.MAINIEN31
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SEQIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SEQIF, self).__init__(rmio, label,
            0xb6040000, 0x018,
            'SEQIF', 'SMCTRL_NS.SEQIF', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SEQIF0 = RM_Field_SMCTRL_NS_SEQIF_SEQIF0(self)
        self.zz_fdict['SEQIF0'] = self.SEQIF0
        self.SEQIF1 = RM_Field_SMCTRL_NS_SEQIF_SEQIF1(self)
        self.zz_fdict['SEQIF1'] = self.SEQIF1
        self.SEQIF2 = RM_Field_SMCTRL_NS_SEQIF_SEQIF2(self)
        self.zz_fdict['SEQIF2'] = self.SEQIF2
        self.SEQIF3 = RM_Field_SMCTRL_NS_SEQIF_SEQIF3(self)
        self.zz_fdict['SEQIF3'] = self.SEQIF3
        self.SEQIF4 = RM_Field_SMCTRL_NS_SEQIF_SEQIF4(self)
        self.zz_fdict['SEQIF4'] = self.SEQIF4
        self.SEQIF5 = RM_Field_SMCTRL_NS_SEQIF_SEQIF5(self)
        self.zz_fdict['SEQIF5'] = self.SEQIF5
        self.SEQIF6 = RM_Field_SMCTRL_NS_SEQIF_SEQIF6(self)
        self.zz_fdict['SEQIF6'] = self.SEQIF6
        self.SEQIF7 = RM_Field_SMCTRL_NS_SEQIF_SEQIF7(self)
        self.zz_fdict['SEQIF7'] = self.SEQIF7
        self.SEQIF8 = RM_Field_SMCTRL_NS_SEQIF_SEQIF8(self)
        self.zz_fdict['SEQIF8'] = self.SEQIF8
        self.SEQIF9 = RM_Field_SMCTRL_NS_SEQIF_SEQIF9(self)
        self.zz_fdict['SEQIF9'] = self.SEQIF9
        self.SEQIF10 = RM_Field_SMCTRL_NS_SEQIF_SEQIF10(self)
        self.zz_fdict['SEQIF10'] = self.SEQIF10
        self.SEQIF11 = RM_Field_SMCTRL_NS_SEQIF_SEQIF11(self)
        self.zz_fdict['SEQIF11'] = self.SEQIF11
        self.SEQIF12 = RM_Field_SMCTRL_NS_SEQIF_SEQIF12(self)
        self.zz_fdict['SEQIF12'] = self.SEQIF12
        self.SEQIF13 = RM_Field_SMCTRL_NS_SEQIF_SEQIF13(self)
        self.zz_fdict['SEQIF13'] = self.SEQIF13
        self.SEQIF14 = RM_Field_SMCTRL_NS_SEQIF_SEQIF14(self)
        self.zz_fdict['SEQIF14'] = self.SEQIF14
        self.SEQIF15 = RM_Field_SMCTRL_NS_SEQIF_SEQIF15(self)
        self.zz_fdict['SEQIF15'] = self.SEQIF15
        self.SEQIF16 = RM_Field_SMCTRL_NS_SEQIF_SEQIF16(self)
        self.zz_fdict['SEQIF16'] = self.SEQIF16
        self.SEQIF17 = RM_Field_SMCTRL_NS_SEQIF_SEQIF17(self)
        self.zz_fdict['SEQIF17'] = self.SEQIF17
        self.SEQIF18 = RM_Field_SMCTRL_NS_SEQIF_SEQIF18(self)
        self.zz_fdict['SEQIF18'] = self.SEQIF18
        self.SEQIF19 = RM_Field_SMCTRL_NS_SEQIF_SEQIF19(self)
        self.zz_fdict['SEQIF19'] = self.SEQIF19
        self.SEQIF20 = RM_Field_SMCTRL_NS_SEQIF_SEQIF20(self)
        self.zz_fdict['SEQIF20'] = self.SEQIF20
        self.SEQIF21 = RM_Field_SMCTRL_NS_SEQIF_SEQIF21(self)
        self.zz_fdict['SEQIF21'] = self.SEQIF21
        self.SEQIF22 = RM_Field_SMCTRL_NS_SEQIF_SEQIF22(self)
        self.zz_fdict['SEQIF22'] = self.SEQIF22
        self.SEQIF23 = RM_Field_SMCTRL_NS_SEQIF_SEQIF23(self)
        self.zz_fdict['SEQIF23'] = self.SEQIF23
        self.SEQIF24 = RM_Field_SMCTRL_NS_SEQIF_SEQIF24(self)
        self.zz_fdict['SEQIF24'] = self.SEQIF24
        self.SEQIF25 = RM_Field_SMCTRL_NS_SEQIF_SEQIF25(self)
        self.zz_fdict['SEQIF25'] = self.SEQIF25
        self.SEQIF26 = RM_Field_SMCTRL_NS_SEQIF_SEQIF26(self)
        self.zz_fdict['SEQIF26'] = self.SEQIF26
        self.SEQIF27 = RM_Field_SMCTRL_NS_SEQIF_SEQIF27(self)
        self.zz_fdict['SEQIF27'] = self.SEQIF27
        self.SEQIF28 = RM_Field_SMCTRL_NS_SEQIF_SEQIF28(self)
        self.zz_fdict['SEQIF28'] = self.SEQIF28
        self.SEQIF29 = RM_Field_SMCTRL_NS_SEQIF_SEQIF29(self)
        self.zz_fdict['SEQIF29'] = self.SEQIF29
        self.SEQIF30 = RM_Field_SMCTRL_NS_SEQIF_SEQIF30(self)
        self.zz_fdict['SEQIF30'] = self.SEQIF30
        self.SEQIF31 = RM_Field_SMCTRL_NS_SEQIF_SEQIF31(self)
        self.zz_fdict['SEQIF31'] = self.SEQIF31
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SEQIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SEQIEN, self).__init__(rmio, label,
            0xb6040000, 0x01C,
            'SEQIEN', 'SMCTRL_NS.SEQIEN', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SEQIEN0 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN0(self)
        self.zz_fdict['SEQIEN0'] = self.SEQIEN0
        self.SEQIEN1 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN1(self)
        self.zz_fdict['SEQIEN1'] = self.SEQIEN1
        self.SEQIEN2 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN2(self)
        self.zz_fdict['SEQIEN2'] = self.SEQIEN2
        self.SEQIEN3 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN3(self)
        self.zz_fdict['SEQIEN3'] = self.SEQIEN3
        self.SEQIEN4 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN4(self)
        self.zz_fdict['SEQIEN4'] = self.SEQIEN4
        self.SEQIEN5 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN5(self)
        self.zz_fdict['SEQIEN5'] = self.SEQIEN5
        self.SEQIEN6 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN6(self)
        self.zz_fdict['SEQIEN6'] = self.SEQIEN6
        self.SEQIEN7 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN7(self)
        self.zz_fdict['SEQIEN7'] = self.SEQIEN7
        self.SEQIEN8 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN8(self)
        self.zz_fdict['SEQIEN8'] = self.SEQIEN8
        self.SEQIEN9 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN9(self)
        self.zz_fdict['SEQIEN9'] = self.SEQIEN9
        self.SEQIEN10 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN10(self)
        self.zz_fdict['SEQIEN10'] = self.SEQIEN10
        self.SEQIEN11 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN11(self)
        self.zz_fdict['SEQIEN11'] = self.SEQIEN11
        self.SEQIEN12 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN12(self)
        self.zz_fdict['SEQIEN12'] = self.SEQIEN12
        self.SEQIEN13 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN13(self)
        self.zz_fdict['SEQIEN13'] = self.SEQIEN13
        self.SEQIEN14 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN14(self)
        self.zz_fdict['SEQIEN14'] = self.SEQIEN14
        self.SEQIEN15 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN15(self)
        self.zz_fdict['SEQIEN15'] = self.SEQIEN15
        self.SEQIEN16 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN16(self)
        self.zz_fdict['SEQIEN16'] = self.SEQIEN16
        self.SEQIEN17 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN17(self)
        self.zz_fdict['SEQIEN17'] = self.SEQIEN17
        self.SEQIEN18 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN18(self)
        self.zz_fdict['SEQIEN18'] = self.SEQIEN18
        self.SEQIEN19 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN19(self)
        self.zz_fdict['SEQIEN19'] = self.SEQIEN19
        self.SEQIEN20 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN20(self)
        self.zz_fdict['SEQIEN20'] = self.SEQIEN20
        self.SEQIEN21 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN21(self)
        self.zz_fdict['SEQIEN21'] = self.SEQIEN21
        self.SEQIEN22 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN22(self)
        self.zz_fdict['SEQIEN22'] = self.SEQIEN22
        self.SEQIEN23 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN23(self)
        self.zz_fdict['SEQIEN23'] = self.SEQIEN23
        self.SEQIEN24 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN24(self)
        self.zz_fdict['SEQIEN24'] = self.SEQIEN24
        self.SEQIEN25 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN25(self)
        self.zz_fdict['SEQIEN25'] = self.SEQIEN25
        self.SEQIEN26 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN26(self)
        self.zz_fdict['SEQIEN26'] = self.SEQIEN26
        self.SEQIEN27 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN27(self)
        self.zz_fdict['SEQIEN27'] = self.SEQIEN27
        self.SEQIEN28 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN28(self)
        self.zz_fdict['SEQIEN28'] = self.SEQIEN28
        self.SEQIEN29 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN29(self)
        self.zz_fdict['SEQIEN29'] = self.SEQIEN29
        self.SEQIEN30 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN30(self)
        self.zz_fdict['SEQIEN30'] = self.SEQIEN30
        self.SEQIEN31 = RM_Field_SMCTRL_NS_SEQIEN_SEQIEN31(self)
        self.zz_fdict['SEQIEN31'] = self.SEQIEN31
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SWIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SWIF, self).__init__(rmio, label,
            0xb6040000, 0x020,
            'SWIF', 'SMCTRL_NS.SWIF', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWIF0 = RM_Field_SMCTRL_NS_SWIF_SWIF0(self)
        self.zz_fdict['SWIF0'] = self.SWIF0
        self.SWIF1 = RM_Field_SMCTRL_NS_SWIF_SWIF1(self)
        self.zz_fdict['SWIF1'] = self.SWIF1
        self.SWIF2 = RM_Field_SMCTRL_NS_SWIF_SWIF2(self)
        self.zz_fdict['SWIF2'] = self.SWIF2
        self.SWIF3 = RM_Field_SMCTRL_NS_SWIF_SWIF3(self)
        self.zz_fdict['SWIF3'] = self.SWIF3
        self.SWIF4 = RM_Field_SMCTRL_NS_SWIF_SWIF4(self)
        self.zz_fdict['SWIF4'] = self.SWIF4
        self.SWIF5 = RM_Field_SMCTRL_NS_SWIF_SWIF5(self)
        self.zz_fdict['SWIF5'] = self.SWIF5
        self.SWIF6 = RM_Field_SMCTRL_NS_SWIF_SWIF6(self)
        self.zz_fdict['SWIF6'] = self.SWIF6
        self.SWIF7 = RM_Field_SMCTRL_NS_SWIF_SWIF7(self)
        self.zz_fdict['SWIF7'] = self.SWIF7
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SWIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SWIEN, self).__init__(rmio, label,
            0xb6040000, 0x024,
            'SWIEN', 'SMCTRL_NS.SWIEN', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWIEN0 = RM_Field_SMCTRL_NS_SWIEN_SWIEN0(self)
        self.zz_fdict['SWIEN0'] = self.SWIEN0
        self.SWIEN1 = RM_Field_SMCTRL_NS_SWIEN_SWIEN1(self)
        self.zz_fdict['SWIEN1'] = self.SWIEN1
        self.SWIEN2 = RM_Field_SMCTRL_NS_SWIEN_SWIEN2(self)
        self.zz_fdict['SWIEN2'] = self.SWIEN2
        self.SWIEN3 = RM_Field_SMCTRL_NS_SWIEN_SWIEN3(self)
        self.zz_fdict['SWIEN3'] = self.SWIEN3
        self.SWIEN4 = RM_Field_SMCTRL_NS_SWIEN_SWIEN4(self)
        self.zz_fdict['SWIEN4'] = self.SWIEN4
        self.SWIEN5 = RM_Field_SMCTRL_NS_SWIEN_SWIEN5(self)
        self.zz_fdict['SWIEN5'] = self.SWIEN5
        self.SWIEN6 = RM_Field_SMCTRL_NS_SWIEN_SWIEN6(self)
        self.zz_fdict['SWIEN6'] = self.SWIEN6
        self.SWIEN7 = RM_Field_SMCTRL_NS_SWIEN_SWIEN7(self)
        self.zz_fdict['SWIEN7'] = self.SWIEN7
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_GPREG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_GPREG, self).__init__(rmio, label,
            0xb6040000, 0x028,
            'GPREG', 'SMCTRL_NS.GPREG', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.GPREG0 = RM_Field_SMCTRL_NS_GPREG_GPREG0(self)
        self.zz_fdict['GPREG0'] = self.GPREG0
        self.GPREG1 = RM_Field_SMCTRL_NS_GPREG_GPREG1(self)
        self.zz_fdict['GPREG1'] = self.GPREG1
        self.GPREG2 = RM_Field_SMCTRL_NS_GPREG_GPREG2(self)
        self.zz_fdict['GPREG2'] = self.GPREG2
        self.GPREG3 = RM_Field_SMCTRL_NS_GPREG_GPREG3(self)
        self.zz_fdict['GPREG3'] = self.GPREG3
        self.GPREG4 = RM_Field_SMCTRL_NS_GPREG_GPREG4(self)
        self.zz_fdict['GPREG4'] = self.GPREG4
        self.GPREG5 = RM_Field_SMCTRL_NS_GPREG_GPREG5(self)
        self.zz_fdict['GPREG5'] = self.GPREG5
        self.GPREG6 = RM_Field_SMCTRL_NS_GPREG_GPREG6(self)
        self.zz_fdict['GPREG6'] = self.GPREG6
        self.GPREG7 = RM_Field_SMCTRL_NS_GPREG_GPREG7(self)
        self.zz_fdict['GPREG7'] = self.GPREG7
        self.GPREG8 = RM_Field_SMCTRL_NS_GPREG_GPREG8(self)
        self.zz_fdict['GPREG8'] = self.GPREG8
        self.GPREG9 = RM_Field_SMCTRL_NS_GPREG_GPREG9(self)
        self.zz_fdict['GPREG9'] = self.GPREG9
        self.GPREG10 = RM_Field_SMCTRL_NS_GPREG_GPREG10(self)
        self.zz_fdict['GPREG10'] = self.GPREG10
        self.GPREG11 = RM_Field_SMCTRL_NS_GPREG_GPREG11(self)
        self.zz_fdict['GPREG11'] = self.GPREG11
        self.GPREG12 = RM_Field_SMCTRL_NS_GPREG_GPREG12(self)
        self.zz_fdict['GPREG12'] = self.GPREG12
        self.GPREG13 = RM_Field_SMCTRL_NS_GPREG_GPREG13(self)
        self.zz_fdict['GPREG13'] = self.GPREG13
        self.GPREG14 = RM_Field_SMCTRL_NS_GPREG_GPREG14(self)
        self.zz_fdict['GPREG14'] = self.GPREG14
        self.GPREG15 = RM_Field_SMCTRL_NS_GPREG_GPREG15(self)
        self.zz_fdict['GPREG15'] = self.GPREG15
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_TIMIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_TIMIF, self).__init__(rmio, label,
            0xb6040000, 0x02C,
            'TIMIF', 'SMCTRL_NS.TIMIF', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMIF0 = RM_Field_SMCTRL_NS_TIMIF_TIMIF0(self)
        self.zz_fdict['TIMIF0'] = self.TIMIF0
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_TIMIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_TIMIEN, self).__init__(rmio, label,
            0xb6040000, 0x030,
            'TIMIEN', 'SMCTRL_NS.TIMIEN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMIEN0 = RM_Field_SMCTRL_NS_TIMIEN_TIMIEN0(self)
        self.zz_fdict['TIMIEN0'] = self.TIMIEN0
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_FRCRXCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_FRCRXCTRL, self).__init__(rmio, label,
            0xb6040000, 0x100,
            'FRCRXCTRL', 'SMCTRL_NS.FRCRXCTRL', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.FDETFALLEDGE = RM_Field_SMCTRL_NS_FRCRXCTRL_FDETFALLEDGE(self)
        self.zz_fdict['FDETFALLEDGE'] = self.FDETFALLEDGE
        self.FDETCLR = RM_Field_SMCTRL_NS_FRCRXCTRL_FDETCLR(self)
        self.zz_fdict['FDETCLR'] = self.FDETCLR
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_CTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_CTRL, self).__init__(rmio, label,
            0xb6040000, 0x104,
            'CTRL', 'SMCTRL_NS.CTRL', 'read-write',
            u"",
            0x0003FF00, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FETCHEN = RM_Field_SMCTRL_NS_CTRL_FETCHEN(self)
        self.zz_fdict['FETCHEN'] = self.FETCHEN
        self.FEFILT0INPUTSEL = RM_Field_SMCTRL_NS_CTRL_FEFILT0INPUTSEL(self)
        self.zz_fdict['FEFILT0INPUTSEL'] = self.FEFILT0INPUTSEL
        self.IRCAL0SEL = RM_Field_SMCTRL_NS_CTRL_IRCAL0SEL(self)
        self.zz_fdict['IRCAL0SEL'] = self.IRCAL0SEL
        self.IRCAL1SEL = RM_Field_SMCTRL_NS_CTRL_IRCAL1SEL(self)
        self.zz_fdict['IRCAL1SEL'] = self.IRCAL1SEL
        self.RISCVSSRESETREQ = RM_Field_SMCTRL_NS_CTRL_RISCVSSRESETREQ(self)
        self.zz_fdict['RISCVSSRESETREQ'] = self.RISCVSSRESETREQ
        self.RISCVSSRESETACK = RM_Field_SMCTRL_NS_CTRL_RISCVSSRESETACK(self)
        self.zz_fdict['RISCVSSRESETACK'] = self.RISCVSSRESETACK
        self.ECA0INPUTSEL = RM_Field_SMCTRL_NS_CTRL_ECA0INPUTSEL(self)
        self.zz_fdict['ECA0INPUTSEL'] = self.ECA0INPUTSEL
        self.ECA1INPUTSEL = RM_Field_SMCTRL_NS_CTRL_ECA1INPUTSEL(self)
        self.zz_fdict['ECA1INPUTSEL'] = self.ECA1INPUTSEL
        self.RXF1TIMEREN = RM_Field_SMCTRL_NS_CTRL_RXF1TIMEREN(self)
        self.zz_fdict['RXF1TIMEREN'] = self.RXF1TIMEREN
        self.RXF2TIMEREN = RM_Field_SMCTRL_NS_CTRL_RXF2TIMEREN(self)
        self.zz_fdict['RXF2TIMEREN'] = self.RXF2TIMEREN
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_PC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_PC, self).__init__(rmio, label,
            0xb6040000, 0x108,
            'PC', 'SMCTRL_NS.PC', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PC = RM_Field_SMCTRL_NS_PC_PC(self)
        self.zz_fdict['PC'] = self.PC
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SCRATCH0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SCRATCH0, self).__init__(rmio, label,
            0xb6040000, 0x180,
            'SCRATCH0', 'SMCTRL_NS.SCRATCH0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH0 = RM_Field_SMCTRL_NS_SCRATCH0_SCRATCH0(self)
        self.zz_fdict['SCRATCH0'] = self.SCRATCH0
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SCRATCH1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SCRATCH1, self).__init__(rmio, label,
            0xb6040000, 0x184,
            'SCRATCH1', 'SMCTRL_NS.SCRATCH1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH1 = RM_Field_SMCTRL_NS_SCRATCH1_SCRATCH1(self)
        self.zz_fdict['SCRATCH1'] = self.SCRATCH1
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SCRATCH2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SCRATCH2, self).__init__(rmio, label,
            0xb6040000, 0x188,
            'SCRATCH2', 'SMCTRL_NS.SCRATCH2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH2 = RM_Field_SMCTRL_NS_SCRATCH2_SCRATCH2(self)
        self.zz_fdict['SCRATCH2'] = self.SCRATCH2
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SCRATCH3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SCRATCH3, self).__init__(rmio, label,
            0xb6040000, 0x18C,
            'SCRATCH3', 'SMCTRL_NS.SCRATCH3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH3 = RM_Field_SMCTRL_NS_SCRATCH3_SCRATCH3(self)
        self.zz_fdict['SCRATCH3'] = self.SCRATCH3
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SCRATCH4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SCRATCH4, self).__init__(rmio, label,
            0xb6040000, 0x190,
            'SCRATCH4', 'SMCTRL_NS.SCRATCH4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH4 = RM_Field_SMCTRL_NS_SCRATCH4_SCRATCH4(self)
        self.zz_fdict['SCRATCH4'] = self.SCRATCH4
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SCRATCH5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SCRATCH5, self).__init__(rmio, label,
            0xb6040000, 0x194,
            'SCRATCH5', 'SMCTRL_NS.SCRATCH5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH5 = RM_Field_SMCTRL_NS_SCRATCH5_SCRATCH5(self)
        self.zz_fdict['SCRATCH5'] = self.SCRATCH5
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SCRATCH6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SCRATCH6, self).__init__(rmio, label,
            0xb6040000, 0x198,
            'SCRATCH6', 'SMCTRL_NS.SCRATCH6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH6 = RM_Field_SMCTRL_NS_SCRATCH6_SCRATCH6(self)
        self.zz_fdict['SCRATCH6'] = self.SCRATCH6
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SCRATCH7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SCRATCH7, self).__init__(rmio, label,
            0xb6040000, 0x19C,
            'SCRATCH7', 'SMCTRL_NS.SCRATCH7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH7 = RM_Field_SMCTRL_NS_SCRATCH7_SCRATCH7(self)
        self.zz_fdict['SCRATCH7'] = self.SCRATCH7
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_PRSMUXLSB(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_PRSMUXLSB, self).__init__(rmio, label,
            0xb6040000, 0x1B0,
            'PRSMUXLSB', 'SMCTRL_NS.PRSMUXLSB', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PRSMUXLSB0 = RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB0(self)
        self.zz_fdict['PRSMUXLSB0'] = self.PRSMUXLSB0
        self.PRSMUXLSB1 = RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB1(self)
        self.zz_fdict['PRSMUXLSB1'] = self.PRSMUXLSB1
        self.PRSMUXLSB2 = RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB2(self)
        self.zz_fdict['PRSMUXLSB2'] = self.PRSMUXLSB2
        self.PRSMUXLSB3 = RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB3(self)
        self.zz_fdict['PRSMUXLSB3'] = self.PRSMUXLSB3
        self.PRSMUXLSB4 = RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB4(self)
        self.zz_fdict['PRSMUXLSB4'] = self.PRSMUXLSB4
        self.PRSMUXLSB5 = RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB5(self)
        self.zz_fdict['PRSMUXLSB5'] = self.PRSMUXLSB5
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_PRSMUXMSB(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_PRSMUXMSB, self).__init__(rmio, label,
            0xb6040000, 0x1B4,
            'PRSMUXMSB', 'SMCTRL_NS.PRSMUXMSB', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PRSMUXMSB0 = RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB0(self)
        self.zz_fdict['PRSMUXMSB0'] = self.PRSMUXMSB0
        self.PRSMUXMSB1 = RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB1(self)
        self.zz_fdict['PRSMUXMSB1'] = self.PRSMUXMSB1
        self.PRSMUXMSB2 = RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB2(self)
        self.zz_fdict['PRSMUXMSB2'] = self.PRSMUXMSB2
        self.PRSMUXMSB3 = RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB3(self)
        self.zz_fdict['PRSMUXMSB3'] = self.PRSMUXMSB3
        self.PRSMUXMSB4 = RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB4(self)
        self.zz_fdict['PRSMUXMSB4'] = self.PRSMUXMSB4
        self.PRSMUXMSB5 = RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB5(self)
        self.zz_fdict['PRSMUXMSB5'] = self.PRSMUXMSB5
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_PRSOUT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_PRSOUT, self).__init__(rmio, label,
            0xb6040000, 0x1B8,
            'PRSOUT', 'SMCTRL_NS.PRSOUT', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PRSOUT0 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT0(self)
        self.zz_fdict['PRSOUT0'] = self.PRSOUT0
        self.PRSOUT1 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT1(self)
        self.zz_fdict['PRSOUT1'] = self.PRSOUT1
        self.PRSOUT2 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT2(self)
        self.zz_fdict['PRSOUT2'] = self.PRSOUT2
        self.PRSOUT3 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT3(self)
        self.zz_fdict['PRSOUT3'] = self.PRSOUT3
        self.PRSOUT4 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT4(self)
        self.zz_fdict['PRSOUT4'] = self.PRSOUT4
        self.PRSOUT5 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT5(self)
        self.zz_fdict['PRSOUT5'] = self.PRSOUT5
        self.PRSOUT6 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT6(self)
        self.zz_fdict['PRSOUT6'] = self.PRSOUT6
        self.PRSOUT7 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT7(self)
        self.zz_fdict['PRSOUT7'] = self.PRSOUT7
        self.PRSOUT8 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT8(self)
        self.zz_fdict['PRSOUT8'] = self.PRSOUT8
        self.PRSOUT9 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT9(self)
        self.zz_fdict['PRSOUT9'] = self.PRSOUT9
        self.PRSOUT10 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT10(self)
        self.zz_fdict['PRSOUT10'] = self.PRSOUT10
        self.PRSOUT11 = RM_Field_SMCTRL_NS_PRSOUT_PRSOUT11(self)
        self.zz_fdict['PRSOUT11'] = self.PRSOUT11
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_RXEVMUX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_RXEVMUX, self).__init__(rmio, label,
            0xb6040000, 0x1C0,
            'RXEVMUX', 'SMCTRL_NS.RXEVMUX', 'read-write',
            u"",
            0x14131211, 0x1F1F1F1F,
            0x00001000, 0x00002000,
            0x00003000)

        self.MUX0 = RM_Field_SMCTRL_NS_RXEVMUX_MUX0(self)
        self.zz_fdict['MUX0'] = self.MUX0
        self.MUX1 = RM_Field_SMCTRL_NS_RXEVMUX_MUX1(self)
        self.zz_fdict['MUX1'] = self.MUX1
        self.MUX2 = RM_Field_SMCTRL_NS_RXEVMUX_MUX2(self)
        self.zz_fdict['MUX2'] = self.MUX2
        self.MUX3 = RM_Field_SMCTRL_NS_RXEVMUX_MUX3(self)
        self.zz_fdict['MUX3'] = self.MUX3
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_TIMCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_TIMCTRL, self).__init__(rmio, label,
            0xb6040000, 0x1C4,
            'TIMCTRL', 'SMCTRL_NS.TIMCTRL', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INIT0 = RM_Field_SMCTRL_NS_TIMCTRL_INIT0(self)
        self.zz_fdict['INIT0'] = self.INIT0
        self.INIT1 = RM_Field_SMCTRL_NS_TIMCTRL_INIT1(self)
        self.zz_fdict['INIT1'] = self.INIT1
        self.INIT2 = RM_Field_SMCTRL_NS_TIMCTRL_INIT2(self)
        self.zz_fdict['INIT2'] = self.INIT2
        self.INIT3 = RM_Field_SMCTRL_NS_TIMCTRL_INIT3(self)
        self.zz_fdict['INIT3'] = self.INIT3
        self.INIT4 = RM_Field_SMCTRL_NS_TIMCTRL_INIT4(self)
        self.zz_fdict['INIT4'] = self.INIT4
        self.INIT5 = RM_Field_SMCTRL_NS_TIMCTRL_INIT5(self)
        self.zz_fdict['INIT5'] = self.INIT5
        self.INIT6 = RM_Field_SMCTRL_NS_TIMCTRL_INIT6(self)
        self.zz_fdict['INIT6'] = self.INIT6
        self.INIT7 = RM_Field_SMCTRL_NS_TIMCTRL_INIT7(self)
        self.zz_fdict['INIT7'] = self.INIT7
        self.INIT8 = RM_Field_SMCTRL_NS_TIMCTRL_INIT8(self)
        self.zz_fdict['INIT8'] = self.INIT8
        self.INIT9 = RM_Field_SMCTRL_NS_TIMCTRL_INIT9(self)
        self.zz_fdict['INIT9'] = self.INIT9
        self.INIT10 = RM_Field_SMCTRL_NS_TIMCTRL_INIT10(self)
        self.zz_fdict['INIT10'] = self.INIT10
        self.INIT11 = RM_Field_SMCTRL_NS_TIMCTRL_INIT11(self)
        self.zz_fdict['INIT11'] = self.INIT11
        self.INIT12 = RM_Field_SMCTRL_NS_TIMCTRL_INIT12(self)
        self.zz_fdict['INIT12'] = self.INIT12
        self.INIT13 = RM_Field_SMCTRL_NS_TIMCTRL_INIT13(self)
        self.zz_fdict['INIT13'] = self.INIT13
        self.INIT14 = RM_Field_SMCTRL_NS_TIMCTRL_INIT14(self)
        self.zz_fdict['INIT14'] = self.INIT14
        self.INIT15 = RM_Field_SMCTRL_NS_TIMCTRL_INIT15(self)
        self.zz_fdict['INIT15'] = self.INIT15
        self.INIT16 = RM_Field_SMCTRL_NS_TIMCTRL_INIT16(self)
        self.zz_fdict['INIT16'] = self.INIT16
        self.INIT17 = RM_Field_SMCTRL_NS_TIMCTRL_INIT17(self)
        self.zz_fdict['INIT17'] = self.INIT17
        self.INIT18 = RM_Field_SMCTRL_NS_TIMCTRL_INIT18(self)
        self.zz_fdict['INIT18'] = self.INIT18
        self.INIT19 = RM_Field_SMCTRL_NS_TIMCTRL_INIT19(self)
        self.zz_fdict['INIT19'] = self.INIT19
        self.INIT20 = RM_Field_SMCTRL_NS_TIMCTRL_INIT20(self)
        self.zz_fdict['INIT20'] = self.INIT20
        self.INIT21 = RM_Field_SMCTRL_NS_TIMCTRL_INIT21(self)
        self.zz_fdict['INIT21'] = self.INIT21
        self.INIT22 = RM_Field_SMCTRL_NS_TIMCTRL_INIT22(self)
        self.zz_fdict['INIT22'] = self.INIT22
        self.INIT23 = RM_Field_SMCTRL_NS_TIMCTRL_INIT23(self)
        self.zz_fdict['INIT23'] = self.INIT23
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_TIMSTAT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_TIMSTAT, self).__init__(rmio, label,
            0xb6040000, 0x1C8,
            'TIMSTAT', 'SMCTRL_NS.TIMSTAT', 'read-only',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VALUE0 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE0(self)
        self.zz_fdict['VALUE0'] = self.VALUE0
        self.VALUE1 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE1(self)
        self.zz_fdict['VALUE1'] = self.VALUE1
        self.VALUE2 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE2(self)
        self.zz_fdict['VALUE2'] = self.VALUE2
        self.VALUE3 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE3(self)
        self.zz_fdict['VALUE3'] = self.VALUE3
        self.VALUE4 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE4(self)
        self.zz_fdict['VALUE4'] = self.VALUE4
        self.VALUE5 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE5(self)
        self.zz_fdict['VALUE5'] = self.VALUE5
        self.VALUE6 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE6(self)
        self.zz_fdict['VALUE6'] = self.VALUE6
        self.VALUE7 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE7(self)
        self.zz_fdict['VALUE7'] = self.VALUE7
        self.VALUE8 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE8(self)
        self.zz_fdict['VALUE8'] = self.VALUE8
        self.VALUE9 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE9(self)
        self.zz_fdict['VALUE9'] = self.VALUE9
        self.VALUE10 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE10(self)
        self.zz_fdict['VALUE10'] = self.VALUE10
        self.VALUE11 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE11(self)
        self.zz_fdict['VALUE11'] = self.VALUE11
        self.VALUE12 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE12(self)
        self.zz_fdict['VALUE12'] = self.VALUE12
        self.VALUE13 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE13(self)
        self.zz_fdict['VALUE13'] = self.VALUE13
        self.VALUE14 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE14(self)
        self.zz_fdict['VALUE14'] = self.VALUE14
        self.VALUE15 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE15(self)
        self.zz_fdict['VALUE15'] = self.VALUE15
        self.VALUE16 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE16(self)
        self.zz_fdict['VALUE16'] = self.VALUE16
        self.VALUE17 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE17(self)
        self.zz_fdict['VALUE17'] = self.VALUE17
        self.VALUE18 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE18(self)
        self.zz_fdict['VALUE18'] = self.VALUE18
        self.VALUE19 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE19(self)
        self.zz_fdict['VALUE19'] = self.VALUE19
        self.VALUE20 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE20(self)
        self.zz_fdict['VALUE20'] = self.VALUE20
        self.VALUE21 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE21(self)
        self.zz_fdict['VALUE21'] = self.VALUE21
        self.VALUE22 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE22(self)
        self.zz_fdict['VALUE22'] = self.VALUE22
        self.VALUE23 = RM_Field_SMCTRL_NS_TIMSTAT_VALUE23(self)
        self.zz_fdict['VALUE23'] = self.VALUE23
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_SHIFTS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_SHIFTS, self).__init__(rmio, label,
            0xb6040000, 0x1D0,
            'SHIFTS', 'SMCTRL_NS.SHIFTS', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.SHIFTRXF1 = RM_Field_SMCTRL_NS_SHIFTS_SHIFTRXF1(self)
        self.zz_fdict['SHIFTRXF1'] = self.SHIFTRXF1
        self.SHIFTRXF2 = RM_Field_SMCTRL_NS_SHIFTS_SHIFTRXF2(self)
        self.zz_fdict['SHIFTRXF2'] = self.SHIFTRXF2
        self.__dict__['zz_frozen'] = True


class RM_Register_SMCTRL_NS_TXDONE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SMCTRL_NS_TXDONE, self).__init__(rmio, label,
            0xb6040000, 0x1D4,
            'TXDONE', 'SMCTRL_NS.TXDONE', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXDONE = RM_Field_SMCTRL_NS_TXDONE_TXDONE(self)
        self.zz_fdict['TXDONE'] = self.TXDONE
        self.__dict__['zz_frozen'] = True



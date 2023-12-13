
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_SMCTRL_NS_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'SMCTRL_NS.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_EN_EN, self).__init__(register,
            'EN', 'SMCTRL_NS.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_EN_DISABLING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_EN_DISABLING, self).__init__(register,
            'DISABLING', 'SMCTRL_NS.EN.DISABLING', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWRST_SWRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWRST_SWRST, self).__init__(register,
            'SWRST', 'SMCTRL_NS.SWRST.SWRST', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWRST_RESETTING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWRST_RESETTING, self).__init__(register,
            'RESETTING', 'SMCTRL_NS.SWRST.RESETTING', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWRST_COMBRESETTING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWRST_COMBRESETTING, self).__init__(register,
            'COMBRESETTING', 'SMCTRL_NS.SWRST.COMBRESETTING', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF0, self).__init__(register,
            'MAINIF0', 'SMCTRL_NS.MAINIF.MAINIF0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF1, self).__init__(register,
            'MAINIF1', 'SMCTRL_NS.MAINIF.MAINIF1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF2, self).__init__(register,
            'MAINIF2', 'SMCTRL_NS.MAINIF.MAINIF2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF3, self).__init__(register,
            'MAINIF3', 'SMCTRL_NS.MAINIF.MAINIF3', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF4, self).__init__(register,
            'MAINIF4', 'SMCTRL_NS.MAINIF.MAINIF4', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF5, self).__init__(register,
            'MAINIF5', 'SMCTRL_NS.MAINIF.MAINIF5', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF6, self).__init__(register,
            'MAINIF6', 'SMCTRL_NS.MAINIF.MAINIF6', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF7, self).__init__(register,
            'MAINIF7', 'SMCTRL_NS.MAINIF.MAINIF7', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF8, self).__init__(register,
            'MAINIF8', 'SMCTRL_NS.MAINIF.MAINIF8', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF9, self).__init__(register,
            'MAINIF9', 'SMCTRL_NS.MAINIF.MAINIF9', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF10, self).__init__(register,
            'MAINIF10', 'SMCTRL_NS.MAINIF.MAINIF10', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF11, self).__init__(register,
            'MAINIF11', 'SMCTRL_NS.MAINIF.MAINIF11', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF12, self).__init__(register,
            'MAINIF12', 'SMCTRL_NS.MAINIF.MAINIF12', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF13, self).__init__(register,
            'MAINIF13', 'SMCTRL_NS.MAINIF.MAINIF13', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF14, self).__init__(register,
            'MAINIF14', 'SMCTRL_NS.MAINIF.MAINIF14', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF15, self).__init__(register,
            'MAINIF15', 'SMCTRL_NS.MAINIF.MAINIF15', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF16, self).__init__(register,
            'MAINIF16', 'SMCTRL_NS.MAINIF.MAINIF16', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF17, self).__init__(register,
            'MAINIF17', 'SMCTRL_NS.MAINIF.MAINIF17', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF18, self).__init__(register,
            'MAINIF18', 'SMCTRL_NS.MAINIF.MAINIF18', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF19, self).__init__(register,
            'MAINIF19', 'SMCTRL_NS.MAINIF.MAINIF19', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF20, self).__init__(register,
            'MAINIF20', 'SMCTRL_NS.MAINIF.MAINIF20', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF21, self).__init__(register,
            'MAINIF21', 'SMCTRL_NS.MAINIF.MAINIF21', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF22, self).__init__(register,
            'MAINIF22', 'SMCTRL_NS.MAINIF.MAINIF22', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF23, self).__init__(register,
            'MAINIF23', 'SMCTRL_NS.MAINIF.MAINIF23', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF24, self).__init__(register,
            'MAINIF24', 'SMCTRL_NS.MAINIF.MAINIF24', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF25, self).__init__(register,
            'MAINIF25', 'SMCTRL_NS.MAINIF.MAINIF25', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF26, self).__init__(register,
            'MAINIF26', 'SMCTRL_NS.MAINIF.MAINIF26', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF27, self).__init__(register,
            'MAINIF27', 'SMCTRL_NS.MAINIF.MAINIF27', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF28, self).__init__(register,
            'MAINIF28', 'SMCTRL_NS.MAINIF.MAINIF28', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF29, self).__init__(register,
            'MAINIF29', 'SMCTRL_NS.MAINIF.MAINIF29', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF30, self).__init__(register,
            'MAINIF30', 'SMCTRL_NS.MAINIF.MAINIF30', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIF_MAINIF31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIF_MAINIF31, self).__init__(register,
            'MAINIF31', 'SMCTRL_NS.MAINIF.MAINIF31', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN0, self).__init__(register,
            'MAINIEN0', 'SMCTRL_NS.MAINIEN.MAINIEN0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN1, self).__init__(register,
            'MAINIEN1', 'SMCTRL_NS.MAINIEN.MAINIEN1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN2, self).__init__(register,
            'MAINIEN2', 'SMCTRL_NS.MAINIEN.MAINIEN2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN3, self).__init__(register,
            'MAINIEN3', 'SMCTRL_NS.MAINIEN.MAINIEN3', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN4, self).__init__(register,
            'MAINIEN4', 'SMCTRL_NS.MAINIEN.MAINIEN4', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN5, self).__init__(register,
            'MAINIEN5', 'SMCTRL_NS.MAINIEN.MAINIEN5', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN6, self).__init__(register,
            'MAINIEN6', 'SMCTRL_NS.MAINIEN.MAINIEN6', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN7, self).__init__(register,
            'MAINIEN7', 'SMCTRL_NS.MAINIEN.MAINIEN7', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN8, self).__init__(register,
            'MAINIEN8', 'SMCTRL_NS.MAINIEN.MAINIEN8', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN9, self).__init__(register,
            'MAINIEN9', 'SMCTRL_NS.MAINIEN.MAINIEN9', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN10, self).__init__(register,
            'MAINIEN10', 'SMCTRL_NS.MAINIEN.MAINIEN10', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN11, self).__init__(register,
            'MAINIEN11', 'SMCTRL_NS.MAINIEN.MAINIEN11', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN12, self).__init__(register,
            'MAINIEN12', 'SMCTRL_NS.MAINIEN.MAINIEN12', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN13, self).__init__(register,
            'MAINIEN13', 'SMCTRL_NS.MAINIEN.MAINIEN13', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN14, self).__init__(register,
            'MAINIEN14', 'SMCTRL_NS.MAINIEN.MAINIEN14', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN15, self).__init__(register,
            'MAINIEN15', 'SMCTRL_NS.MAINIEN.MAINIEN15', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN16, self).__init__(register,
            'MAINIEN16', 'SMCTRL_NS.MAINIEN.MAINIEN16', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN17, self).__init__(register,
            'MAINIEN17', 'SMCTRL_NS.MAINIEN.MAINIEN17', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN18, self).__init__(register,
            'MAINIEN18', 'SMCTRL_NS.MAINIEN.MAINIEN18', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN19, self).__init__(register,
            'MAINIEN19', 'SMCTRL_NS.MAINIEN.MAINIEN19', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN20, self).__init__(register,
            'MAINIEN20', 'SMCTRL_NS.MAINIEN.MAINIEN20', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN21, self).__init__(register,
            'MAINIEN21', 'SMCTRL_NS.MAINIEN.MAINIEN21', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN22, self).__init__(register,
            'MAINIEN22', 'SMCTRL_NS.MAINIEN.MAINIEN22', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN23, self).__init__(register,
            'MAINIEN23', 'SMCTRL_NS.MAINIEN.MAINIEN23', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN24, self).__init__(register,
            'MAINIEN24', 'SMCTRL_NS.MAINIEN.MAINIEN24', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN25, self).__init__(register,
            'MAINIEN25', 'SMCTRL_NS.MAINIEN.MAINIEN25', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN26, self).__init__(register,
            'MAINIEN26', 'SMCTRL_NS.MAINIEN.MAINIEN26', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN27, self).__init__(register,
            'MAINIEN27', 'SMCTRL_NS.MAINIEN.MAINIEN27', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN28, self).__init__(register,
            'MAINIEN28', 'SMCTRL_NS.MAINIEN.MAINIEN28', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN29, self).__init__(register,
            'MAINIEN29', 'SMCTRL_NS.MAINIEN.MAINIEN29', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN30, self).__init__(register,
            'MAINIEN30', 'SMCTRL_NS.MAINIEN.MAINIEN30', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_MAINIEN_MAINIEN31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_MAINIEN_MAINIEN31, self).__init__(register,
            'MAINIEN31', 'SMCTRL_NS.MAINIEN.MAINIEN31', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF0, self).__init__(register,
            'SEQIF0', 'SMCTRL_NS.SEQIF.SEQIF0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF1, self).__init__(register,
            'SEQIF1', 'SMCTRL_NS.SEQIF.SEQIF1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF2, self).__init__(register,
            'SEQIF2', 'SMCTRL_NS.SEQIF.SEQIF2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF3, self).__init__(register,
            'SEQIF3', 'SMCTRL_NS.SEQIF.SEQIF3', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF4, self).__init__(register,
            'SEQIF4', 'SMCTRL_NS.SEQIF.SEQIF4', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF5, self).__init__(register,
            'SEQIF5', 'SMCTRL_NS.SEQIF.SEQIF5', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF6, self).__init__(register,
            'SEQIF6', 'SMCTRL_NS.SEQIF.SEQIF6', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF7, self).__init__(register,
            'SEQIF7', 'SMCTRL_NS.SEQIF.SEQIF7', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF8, self).__init__(register,
            'SEQIF8', 'SMCTRL_NS.SEQIF.SEQIF8', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF9, self).__init__(register,
            'SEQIF9', 'SMCTRL_NS.SEQIF.SEQIF9', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF10, self).__init__(register,
            'SEQIF10', 'SMCTRL_NS.SEQIF.SEQIF10', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF11, self).__init__(register,
            'SEQIF11', 'SMCTRL_NS.SEQIF.SEQIF11', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF12, self).__init__(register,
            'SEQIF12', 'SMCTRL_NS.SEQIF.SEQIF12', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF13, self).__init__(register,
            'SEQIF13', 'SMCTRL_NS.SEQIF.SEQIF13', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF14, self).__init__(register,
            'SEQIF14', 'SMCTRL_NS.SEQIF.SEQIF14', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF15, self).__init__(register,
            'SEQIF15', 'SMCTRL_NS.SEQIF.SEQIF15', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF16, self).__init__(register,
            'SEQIF16', 'SMCTRL_NS.SEQIF.SEQIF16', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF17, self).__init__(register,
            'SEQIF17', 'SMCTRL_NS.SEQIF.SEQIF17', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF18, self).__init__(register,
            'SEQIF18', 'SMCTRL_NS.SEQIF.SEQIF18', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF19, self).__init__(register,
            'SEQIF19', 'SMCTRL_NS.SEQIF.SEQIF19', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF20, self).__init__(register,
            'SEQIF20', 'SMCTRL_NS.SEQIF.SEQIF20', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF21, self).__init__(register,
            'SEQIF21', 'SMCTRL_NS.SEQIF.SEQIF21', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF22, self).__init__(register,
            'SEQIF22', 'SMCTRL_NS.SEQIF.SEQIF22', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF23, self).__init__(register,
            'SEQIF23', 'SMCTRL_NS.SEQIF.SEQIF23', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF24, self).__init__(register,
            'SEQIF24', 'SMCTRL_NS.SEQIF.SEQIF24', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF25, self).__init__(register,
            'SEQIF25', 'SMCTRL_NS.SEQIF.SEQIF25', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF26, self).__init__(register,
            'SEQIF26', 'SMCTRL_NS.SEQIF.SEQIF26', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF27, self).__init__(register,
            'SEQIF27', 'SMCTRL_NS.SEQIF.SEQIF27', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF28, self).__init__(register,
            'SEQIF28', 'SMCTRL_NS.SEQIF.SEQIF28', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF29, self).__init__(register,
            'SEQIF29', 'SMCTRL_NS.SEQIF.SEQIF29', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF30, self).__init__(register,
            'SEQIF30', 'SMCTRL_NS.SEQIF.SEQIF30', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIF_SEQIF31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIF_SEQIF31, self).__init__(register,
            'SEQIF31', 'SMCTRL_NS.SEQIF.SEQIF31', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN0, self).__init__(register,
            'SEQIEN0', 'SMCTRL_NS.SEQIEN.SEQIEN0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN1, self).__init__(register,
            'SEQIEN1', 'SMCTRL_NS.SEQIEN.SEQIEN1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN2, self).__init__(register,
            'SEQIEN2', 'SMCTRL_NS.SEQIEN.SEQIEN2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN3, self).__init__(register,
            'SEQIEN3', 'SMCTRL_NS.SEQIEN.SEQIEN3', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN4, self).__init__(register,
            'SEQIEN4', 'SMCTRL_NS.SEQIEN.SEQIEN4', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN5, self).__init__(register,
            'SEQIEN5', 'SMCTRL_NS.SEQIEN.SEQIEN5', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN6, self).__init__(register,
            'SEQIEN6', 'SMCTRL_NS.SEQIEN.SEQIEN6', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN7, self).__init__(register,
            'SEQIEN7', 'SMCTRL_NS.SEQIEN.SEQIEN7', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN8, self).__init__(register,
            'SEQIEN8', 'SMCTRL_NS.SEQIEN.SEQIEN8', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN9, self).__init__(register,
            'SEQIEN9', 'SMCTRL_NS.SEQIEN.SEQIEN9', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN10, self).__init__(register,
            'SEQIEN10', 'SMCTRL_NS.SEQIEN.SEQIEN10', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN11, self).__init__(register,
            'SEQIEN11', 'SMCTRL_NS.SEQIEN.SEQIEN11', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN12, self).__init__(register,
            'SEQIEN12', 'SMCTRL_NS.SEQIEN.SEQIEN12', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN13, self).__init__(register,
            'SEQIEN13', 'SMCTRL_NS.SEQIEN.SEQIEN13', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN14, self).__init__(register,
            'SEQIEN14', 'SMCTRL_NS.SEQIEN.SEQIEN14', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN15, self).__init__(register,
            'SEQIEN15', 'SMCTRL_NS.SEQIEN.SEQIEN15', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN16, self).__init__(register,
            'SEQIEN16', 'SMCTRL_NS.SEQIEN.SEQIEN16', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN17, self).__init__(register,
            'SEQIEN17', 'SMCTRL_NS.SEQIEN.SEQIEN17', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN18, self).__init__(register,
            'SEQIEN18', 'SMCTRL_NS.SEQIEN.SEQIEN18', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN19, self).__init__(register,
            'SEQIEN19', 'SMCTRL_NS.SEQIEN.SEQIEN19', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN20, self).__init__(register,
            'SEQIEN20', 'SMCTRL_NS.SEQIEN.SEQIEN20', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN21, self).__init__(register,
            'SEQIEN21', 'SMCTRL_NS.SEQIEN.SEQIEN21', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN22, self).__init__(register,
            'SEQIEN22', 'SMCTRL_NS.SEQIEN.SEQIEN22', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN23, self).__init__(register,
            'SEQIEN23', 'SMCTRL_NS.SEQIEN.SEQIEN23', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN24, self).__init__(register,
            'SEQIEN24', 'SMCTRL_NS.SEQIEN.SEQIEN24', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN25, self).__init__(register,
            'SEQIEN25', 'SMCTRL_NS.SEQIEN.SEQIEN25', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN26, self).__init__(register,
            'SEQIEN26', 'SMCTRL_NS.SEQIEN.SEQIEN26', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN27, self).__init__(register,
            'SEQIEN27', 'SMCTRL_NS.SEQIEN.SEQIEN27', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN28, self).__init__(register,
            'SEQIEN28', 'SMCTRL_NS.SEQIEN.SEQIEN28', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN29, self).__init__(register,
            'SEQIEN29', 'SMCTRL_NS.SEQIEN.SEQIEN29', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN30, self).__init__(register,
            'SEQIEN30', 'SMCTRL_NS.SEQIEN.SEQIEN30', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SEQIEN_SEQIEN31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SEQIEN_SEQIEN31, self).__init__(register,
            'SEQIEN31', 'SMCTRL_NS.SEQIEN.SEQIEN31', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIF_SWIF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIF_SWIF0, self).__init__(register,
            'SWIF0', 'SMCTRL_NS.SWIF.SWIF0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIF_SWIF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIF_SWIF1, self).__init__(register,
            'SWIF1', 'SMCTRL_NS.SWIF.SWIF1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIF_SWIF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIF_SWIF2, self).__init__(register,
            'SWIF2', 'SMCTRL_NS.SWIF.SWIF2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIF_SWIF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIF_SWIF3, self).__init__(register,
            'SWIF3', 'SMCTRL_NS.SWIF.SWIF3', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIF_SWIF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIF_SWIF4, self).__init__(register,
            'SWIF4', 'SMCTRL_NS.SWIF.SWIF4', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIF_SWIF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIF_SWIF5, self).__init__(register,
            'SWIF5', 'SMCTRL_NS.SWIF.SWIF5', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIF_SWIF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIF_SWIF6, self).__init__(register,
            'SWIF6', 'SMCTRL_NS.SWIF.SWIF6', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIF_SWIF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIF_SWIF7, self).__init__(register,
            'SWIF7', 'SMCTRL_NS.SWIF.SWIF7', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIEN_SWIEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIEN_SWIEN0, self).__init__(register,
            'SWIEN0', 'SMCTRL_NS.SWIEN.SWIEN0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIEN_SWIEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIEN_SWIEN1, self).__init__(register,
            'SWIEN1', 'SMCTRL_NS.SWIEN.SWIEN1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIEN_SWIEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIEN_SWIEN2, self).__init__(register,
            'SWIEN2', 'SMCTRL_NS.SWIEN.SWIEN2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIEN_SWIEN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIEN_SWIEN3, self).__init__(register,
            'SWIEN3', 'SMCTRL_NS.SWIEN.SWIEN3', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIEN_SWIEN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIEN_SWIEN4, self).__init__(register,
            'SWIEN4', 'SMCTRL_NS.SWIEN.SWIEN4', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIEN_SWIEN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIEN_SWIEN5, self).__init__(register,
            'SWIEN5', 'SMCTRL_NS.SWIEN.SWIEN5', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIEN_SWIEN6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIEN_SWIEN6, self).__init__(register,
            'SWIEN6', 'SMCTRL_NS.SWIEN.SWIEN6', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SWIEN_SWIEN7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SWIEN_SWIEN7, self).__init__(register,
            'SWIEN7', 'SMCTRL_NS.SWIEN.SWIEN7', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG0, self).__init__(register,
            'GPREG0', 'SMCTRL_NS.GPREG.GPREG0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG1, self).__init__(register,
            'GPREG1', 'SMCTRL_NS.GPREG.GPREG1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG2, self).__init__(register,
            'GPREG2', 'SMCTRL_NS.GPREG.GPREG2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG3, self).__init__(register,
            'GPREG3', 'SMCTRL_NS.GPREG.GPREG3', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG4, self).__init__(register,
            'GPREG4', 'SMCTRL_NS.GPREG.GPREG4', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG5, self).__init__(register,
            'GPREG5', 'SMCTRL_NS.GPREG.GPREG5', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG6, self).__init__(register,
            'GPREG6', 'SMCTRL_NS.GPREG.GPREG6', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG7, self).__init__(register,
            'GPREG7', 'SMCTRL_NS.GPREG.GPREG7', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG8, self).__init__(register,
            'GPREG8', 'SMCTRL_NS.GPREG.GPREG8', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG9, self).__init__(register,
            'GPREG9', 'SMCTRL_NS.GPREG.GPREG9', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG10, self).__init__(register,
            'GPREG10', 'SMCTRL_NS.GPREG.GPREG10', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG11, self).__init__(register,
            'GPREG11', 'SMCTRL_NS.GPREG.GPREG11', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG12, self).__init__(register,
            'GPREG12', 'SMCTRL_NS.GPREG.GPREG12', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG13, self).__init__(register,
            'GPREG13', 'SMCTRL_NS.GPREG.GPREG13', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG14, self).__init__(register,
            'GPREG14', 'SMCTRL_NS.GPREG.GPREG14', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_GPREG_GPREG15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_GPREG_GPREG15, self).__init__(register,
            'GPREG15', 'SMCTRL_NS.GPREG.GPREG15', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMIF_TIMIF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMIF_TIMIF0, self).__init__(register,
            'TIMIF0', 'SMCTRL_NS.TIMIF.TIMIF0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMIEN_TIMIEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMIEN_TIMIEN0, self).__init__(register,
            'TIMIEN0', 'SMCTRL_NS.TIMIEN.TIMIEN0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_FRCRXCTRL_FDETFALLEDGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_FRCRXCTRL_FDETFALLEDGE, self).__init__(register,
            'FDETFALLEDGE', 'SMCTRL_NS.FRCRXCTRL.FDETFALLEDGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_FRCRXCTRL_FDETCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_FRCRXCTRL_FDETCLR, self).__init__(register,
            'FDETCLR', 'SMCTRL_NS.FRCRXCTRL.FDETCLR', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_FETCHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_FETCHEN, self).__init__(register,
            'FETCHEN', 'SMCTRL_NS.CTRL.FETCHEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_FEFILT0INPUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_FEFILT0INPUTSEL, self).__init__(register,
            'FEFILT0INPUTSEL', 'SMCTRL_NS.CTRL.FEFILT0INPUTSEL', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_IRCAL0SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_IRCAL0SEL, self).__init__(register,
            'IRCAL0SEL', 'SMCTRL_NS.CTRL.IRCAL0SEL', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_IRCAL1SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_IRCAL1SEL, self).__init__(register,
            'IRCAL1SEL', 'SMCTRL_NS.CTRL.IRCAL1SEL', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_RISCVSSRESETREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_RISCVSSRESETREQ, self).__init__(register,
            'RISCVSSRESETREQ', 'SMCTRL_NS.CTRL.RISCVSSRESETREQ', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_RISCVSSRESETACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_RISCVSSRESETACK, self).__init__(register,
            'RISCVSSRESETACK', 'SMCTRL_NS.CTRL.RISCVSSRESETACK', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_ECA0INPUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_ECA0INPUTSEL, self).__init__(register,
            'ECA0INPUTSEL', 'SMCTRL_NS.CTRL.ECA0INPUTSEL', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_ECA1INPUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_ECA1INPUTSEL, self).__init__(register,
            'ECA1INPUTSEL', 'SMCTRL_NS.CTRL.ECA1INPUTSEL', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_RXF1TIMEREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_RXF1TIMEREN, self).__init__(register,
            'RXF1TIMEREN', 'SMCTRL_NS.CTRL.RXF1TIMEREN', 'read-write',
            u"",
            8, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_CTRL_RXF2TIMEREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_CTRL_RXF2TIMEREN, self).__init__(register,
            'RXF2TIMEREN', 'SMCTRL_NS.CTRL.RXF2TIMEREN', 'read-write',
            u"",
            18, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PC_PC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PC_PC, self).__init__(register,
            'PC', 'SMCTRL_NS.PC.PC', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SCRATCH0_SCRATCH0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SCRATCH0_SCRATCH0, self).__init__(register,
            'SCRATCH0', 'SMCTRL_NS.SCRATCH0.SCRATCH0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SCRATCH1_SCRATCH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SCRATCH1_SCRATCH1, self).__init__(register,
            'SCRATCH1', 'SMCTRL_NS.SCRATCH1.SCRATCH1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SCRATCH2_SCRATCH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SCRATCH2_SCRATCH2, self).__init__(register,
            'SCRATCH2', 'SMCTRL_NS.SCRATCH2.SCRATCH2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SCRATCH3_SCRATCH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SCRATCH3_SCRATCH3, self).__init__(register,
            'SCRATCH3', 'SMCTRL_NS.SCRATCH3.SCRATCH3', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SCRATCH4_SCRATCH4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SCRATCH4_SCRATCH4, self).__init__(register,
            'SCRATCH4', 'SMCTRL_NS.SCRATCH4.SCRATCH4', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SCRATCH5_SCRATCH5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SCRATCH5_SCRATCH5, self).__init__(register,
            'SCRATCH5', 'SMCTRL_NS.SCRATCH5.SCRATCH5', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SCRATCH6_SCRATCH6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SCRATCH6_SCRATCH6, self).__init__(register,
            'SCRATCH6', 'SMCTRL_NS.SCRATCH6.SCRATCH6', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SCRATCH7_SCRATCH7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SCRATCH7_SCRATCH7, self).__init__(register,
            'SCRATCH7', 'SMCTRL_NS.SCRATCH7.SCRATCH7', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB0, self).__init__(register,
            'PRSMUXLSB0', 'SMCTRL_NS.PRSMUXLSB.PRSMUXLSB0', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB1, self).__init__(register,
            'PRSMUXLSB1', 'SMCTRL_NS.PRSMUXLSB.PRSMUXLSB1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB2, self).__init__(register,
            'PRSMUXLSB2', 'SMCTRL_NS.PRSMUXLSB.PRSMUXLSB2', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB3, self).__init__(register,
            'PRSMUXLSB3', 'SMCTRL_NS.PRSMUXLSB.PRSMUXLSB3', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB4, self).__init__(register,
            'PRSMUXLSB4', 'SMCTRL_NS.PRSMUXLSB.PRSMUXLSB4', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXLSB_PRSMUXLSB5, self).__init__(register,
            'PRSMUXLSB5', 'SMCTRL_NS.PRSMUXLSB.PRSMUXLSB5', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB0, self).__init__(register,
            'PRSMUXMSB0', 'SMCTRL_NS.PRSMUXMSB.PRSMUXMSB0', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB1, self).__init__(register,
            'PRSMUXMSB1', 'SMCTRL_NS.PRSMUXMSB.PRSMUXMSB1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB2, self).__init__(register,
            'PRSMUXMSB2', 'SMCTRL_NS.PRSMUXMSB.PRSMUXMSB2', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB3, self).__init__(register,
            'PRSMUXMSB3', 'SMCTRL_NS.PRSMUXMSB.PRSMUXMSB3', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB4, self).__init__(register,
            'PRSMUXMSB4', 'SMCTRL_NS.PRSMUXMSB.PRSMUXMSB4', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSMUXMSB_PRSMUXMSB5, self).__init__(register,
            'PRSMUXMSB5', 'SMCTRL_NS.PRSMUXMSB.PRSMUXMSB5', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT0, self).__init__(register,
            'PRSOUT0', 'SMCTRL_NS.PRSOUT.PRSOUT0', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT1, self).__init__(register,
            'PRSOUT1', 'SMCTRL_NS.PRSOUT.PRSOUT1', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT2, self).__init__(register,
            'PRSOUT2', 'SMCTRL_NS.PRSOUT.PRSOUT2', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT3, self).__init__(register,
            'PRSOUT3', 'SMCTRL_NS.PRSOUT.PRSOUT3', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT4, self).__init__(register,
            'PRSOUT4', 'SMCTRL_NS.PRSOUT.PRSOUT4', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT5, self).__init__(register,
            'PRSOUT5', 'SMCTRL_NS.PRSOUT.PRSOUT5', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT6, self).__init__(register,
            'PRSOUT6', 'SMCTRL_NS.PRSOUT.PRSOUT6', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT7, self).__init__(register,
            'PRSOUT7', 'SMCTRL_NS.PRSOUT.PRSOUT7', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT8, self).__init__(register,
            'PRSOUT8', 'SMCTRL_NS.PRSOUT.PRSOUT8', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT9, self).__init__(register,
            'PRSOUT9', 'SMCTRL_NS.PRSOUT.PRSOUT9', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT10, self).__init__(register,
            'PRSOUT10', 'SMCTRL_NS.PRSOUT.PRSOUT10', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_PRSOUT_PRSOUT11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_PRSOUT_PRSOUT11, self).__init__(register,
            'PRSOUT11', 'SMCTRL_NS.PRSOUT.PRSOUT11', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_RXEVMUX_MUX0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_RXEVMUX_MUX0, self).__init__(register,
            'MUX0', 'SMCTRL_NS.RXEVMUX.MUX0', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_RXEVMUX_MUX1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_RXEVMUX_MUX1, self).__init__(register,
            'MUX1', 'SMCTRL_NS.RXEVMUX.MUX1', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_RXEVMUX_MUX2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_RXEVMUX_MUX2, self).__init__(register,
            'MUX2', 'SMCTRL_NS.RXEVMUX.MUX2', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_RXEVMUX_MUX3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_RXEVMUX_MUX3, self).__init__(register,
            'MUX3', 'SMCTRL_NS.RXEVMUX.MUX3', 'read-write',
            u"",
            24, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT0, self).__init__(register,
            'INIT0', 'SMCTRL_NS.TIMCTRL.INIT0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT1, self).__init__(register,
            'INIT1', 'SMCTRL_NS.TIMCTRL.INIT1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT2, self).__init__(register,
            'INIT2', 'SMCTRL_NS.TIMCTRL.INIT2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT3, self).__init__(register,
            'INIT3', 'SMCTRL_NS.TIMCTRL.INIT3', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT4, self).__init__(register,
            'INIT4', 'SMCTRL_NS.TIMCTRL.INIT4', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT5, self).__init__(register,
            'INIT5', 'SMCTRL_NS.TIMCTRL.INIT5', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT6, self).__init__(register,
            'INIT6', 'SMCTRL_NS.TIMCTRL.INIT6', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT7, self).__init__(register,
            'INIT7', 'SMCTRL_NS.TIMCTRL.INIT7', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT8, self).__init__(register,
            'INIT8', 'SMCTRL_NS.TIMCTRL.INIT8', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT9, self).__init__(register,
            'INIT9', 'SMCTRL_NS.TIMCTRL.INIT9', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT10, self).__init__(register,
            'INIT10', 'SMCTRL_NS.TIMCTRL.INIT10', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT11, self).__init__(register,
            'INIT11', 'SMCTRL_NS.TIMCTRL.INIT11', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT12, self).__init__(register,
            'INIT12', 'SMCTRL_NS.TIMCTRL.INIT12', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT13, self).__init__(register,
            'INIT13', 'SMCTRL_NS.TIMCTRL.INIT13', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT14, self).__init__(register,
            'INIT14', 'SMCTRL_NS.TIMCTRL.INIT14', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT15, self).__init__(register,
            'INIT15', 'SMCTRL_NS.TIMCTRL.INIT15', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT16, self).__init__(register,
            'INIT16', 'SMCTRL_NS.TIMCTRL.INIT16', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT17, self).__init__(register,
            'INIT17', 'SMCTRL_NS.TIMCTRL.INIT17', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT18, self).__init__(register,
            'INIT18', 'SMCTRL_NS.TIMCTRL.INIT18', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT19, self).__init__(register,
            'INIT19', 'SMCTRL_NS.TIMCTRL.INIT19', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT20, self).__init__(register,
            'INIT20', 'SMCTRL_NS.TIMCTRL.INIT20', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT21, self).__init__(register,
            'INIT21', 'SMCTRL_NS.TIMCTRL.INIT21', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT22, self).__init__(register,
            'INIT22', 'SMCTRL_NS.TIMCTRL.INIT22', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMCTRL_INIT23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMCTRL_INIT23, self).__init__(register,
            'INIT23', 'SMCTRL_NS.TIMCTRL.INIT23', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE0, self).__init__(register,
            'VALUE0', 'SMCTRL_NS.TIMSTAT.VALUE0', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE1, self).__init__(register,
            'VALUE1', 'SMCTRL_NS.TIMSTAT.VALUE1', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE2, self).__init__(register,
            'VALUE2', 'SMCTRL_NS.TIMSTAT.VALUE2', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE3, self).__init__(register,
            'VALUE3', 'SMCTRL_NS.TIMSTAT.VALUE3', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE4, self).__init__(register,
            'VALUE4', 'SMCTRL_NS.TIMSTAT.VALUE4', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE5, self).__init__(register,
            'VALUE5', 'SMCTRL_NS.TIMSTAT.VALUE5', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE6, self).__init__(register,
            'VALUE6', 'SMCTRL_NS.TIMSTAT.VALUE6', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE7, self).__init__(register,
            'VALUE7', 'SMCTRL_NS.TIMSTAT.VALUE7', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE8, self).__init__(register,
            'VALUE8', 'SMCTRL_NS.TIMSTAT.VALUE8', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE9, self).__init__(register,
            'VALUE9', 'SMCTRL_NS.TIMSTAT.VALUE9', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE10, self).__init__(register,
            'VALUE10', 'SMCTRL_NS.TIMSTAT.VALUE10', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE11, self).__init__(register,
            'VALUE11', 'SMCTRL_NS.TIMSTAT.VALUE11', 'read-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE12, self).__init__(register,
            'VALUE12', 'SMCTRL_NS.TIMSTAT.VALUE12', 'read-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE13, self).__init__(register,
            'VALUE13', 'SMCTRL_NS.TIMSTAT.VALUE13', 'read-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE14, self).__init__(register,
            'VALUE14', 'SMCTRL_NS.TIMSTAT.VALUE14', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE15, self).__init__(register,
            'VALUE15', 'SMCTRL_NS.TIMSTAT.VALUE15', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE16, self).__init__(register,
            'VALUE16', 'SMCTRL_NS.TIMSTAT.VALUE16', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE17, self).__init__(register,
            'VALUE17', 'SMCTRL_NS.TIMSTAT.VALUE17', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE18, self).__init__(register,
            'VALUE18', 'SMCTRL_NS.TIMSTAT.VALUE18', 'read-only',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE19, self).__init__(register,
            'VALUE19', 'SMCTRL_NS.TIMSTAT.VALUE19', 'read-only',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE20, self).__init__(register,
            'VALUE20', 'SMCTRL_NS.TIMSTAT.VALUE20', 'read-only',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE21, self).__init__(register,
            'VALUE21', 'SMCTRL_NS.TIMSTAT.VALUE21', 'read-only',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE22, self).__init__(register,
            'VALUE22', 'SMCTRL_NS.TIMSTAT.VALUE22', 'read-only',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TIMSTAT_VALUE23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TIMSTAT_VALUE23, self).__init__(register,
            'VALUE23', 'SMCTRL_NS.TIMSTAT.VALUE23', 'read-only',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SHIFTS_SHIFTRXF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SHIFTS_SHIFTRXF1, self).__init__(register,
            'SHIFTRXF1', 'SMCTRL_NS.SHIFTS.SHIFTRXF1', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_SHIFTS_SHIFTRXF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_SHIFTS_SHIFTRXF2, self).__init__(register,
            'SHIFTRXF2', 'SMCTRL_NS.SHIFTS.SHIFTRXF2', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SMCTRL_NS_TXDONE_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SMCTRL_NS_TXDONE_TXDONE, self).__init__(register,
            'TXDONE', 'SMCTRL_NS.TXDONE.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True



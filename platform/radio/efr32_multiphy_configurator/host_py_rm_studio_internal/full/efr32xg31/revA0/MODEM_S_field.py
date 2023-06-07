
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_MODEM_S_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'MODEM_S.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EN_EN, self).__init__(register,
            'EN', 'MODEM_S.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_TXFRAMESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_TXFRAMESENT, self).__init__(register,
            'TXFRAMESENT', 'MODEM_S.IF.TXFRAMESENT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_TXSYNCSENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_TXSYNCSENT, self).__init__(register,
            'TXSYNCSENT', 'MODEM_S.IF.TXSYNCSENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_TXPRESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_TXPRESENT, self).__init__(register,
            'TXPRESENT', 'MODEM_S.IF.TXPRESENT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_TXRAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_TXRAMPDONE, self).__init__(register,
            'TXRAMPDONE', 'MODEM_S.IF.TXRAMPDONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_LDTNOARR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_LDTNOARR, self).__init__(register,
            'LDTNOARR', 'MODEM_S.IF.LDTNOARR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_PHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_PHDSADET, self).__init__(register,
            'PHDSADET', 'MODEM_S.IF.PHDSADET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_PHYUNCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_PHYUNCODEDET, self).__init__(register,
            'PHYUNCODEDET', 'MODEM_S.IF.PHYUNCODEDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_PHYCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_PHYCODEDET, self).__init__(register,
            'PHYCODEDET', 'MODEM_S.IF.PHYCODEDET', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXTIMDET, self).__init__(register,
            'RXTIMDET', 'MODEM_S.IF.RXTIMDET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXPREDET, self).__init__(register,
            'RXPREDET', 'MODEM_S.IF.RXPREDET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXFRAMEDET0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXFRAMEDET0, self).__init__(register,
            'RXFRAMEDET0', 'MODEM_S.IF.RXFRAMEDET0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXFRAMEDET1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXFRAMEDET1, self).__init__(register,
            'RXFRAMEDET1', 'MODEM_S.IF.RXFRAMEDET1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXTIMLOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXTIMLOST, self).__init__(register,
            'RXTIMLOST', 'MODEM_S.IF.RXTIMLOST', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXPRELOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXPRELOST, self).__init__(register,
            'RXPRELOST', 'MODEM_S.IF.RXPRELOST', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXFRAMEDETOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXFRAMEDETOF, self).__init__(register,
            'RXFRAMEDETOF', 'MODEM_S.IF.RXFRAMEDETOF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXTIMNF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXTIMNF, self).__init__(register,
            'RXTIMNF', 'MODEM_S.IF.RXTIMNF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_FRCTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_FRCTIMOUT, self).__init__(register,
            'FRCTIMOUT', 'MODEM_S.IF.FRCTIMOUT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_ETS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_ETS, self).__init__(register,
            'ETS', 'MODEM_S.IF.ETS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_CFGANTPATTRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_CFGANTPATTRD, self).__init__(register,
            'CFGANTPATTRD', 'MODEM_S.IF.CFGANTPATTRD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXRESTARTRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXRESTARTRSSIMAPRE, self).__init__(register,
            'RXRESTARTRSSIMAPRE', 'MODEM_S.IF.RXRESTARTRSSIMAPRE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_RXRESTARTRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_RXRESTARTRSSIMASYNC, self).__init__(register,
            'RXRESTARTRSSIMASYNC', 'MODEM_S.IF.RXRESTARTRSSIMASYNC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_SQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_SQDET, self).__init__(register,
            'SQDET', 'MODEM_S.IF.SQDET', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_SQNOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_SQNOTDET, self).__init__(register,
            'SQNOTDET', 'MODEM_S.IF.SQNOTDET', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_ANTDIVRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_ANTDIVRDY, self).__init__(register,
            'ANTDIVRDY', 'MODEM_S.IF.ANTDIVRDY', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_SOFTRESETDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_SOFTRESETDONE, self).__init__(register,
            'SOFTRESETDONE', 'MODEM_S.IF.SOFTRESETDONE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_SQPRENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_SQPRENOTDET, self).__init__(register,
            'SQPRENOTDET', 'MODEM_S.IF.SQPRENOTDET', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_SQFRAMENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_SQFRAMENOTDET, self).__init__(register,
            'SQFRAMENOTDET', 'MODEM_S.IF.SQFRAMENOTDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_SQAFCOUTOFBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_SQAFCOUTOFBAND, self).__init__(register,
            'SQAFCOUTOFBAND', 'MODEM_S.IF.SQAFCOUTOFBAND', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_SIDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_SIDET, self).__init__(register,
            'SIDET', 'MODEM_S.IF.SIDET', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_SIRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_SIRESET, self).__init__(register,
            'SIRESET', 'MODEM_S.IF.SIRESET', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_HOPPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_HOPPING, self).__init__(register,
            'HOPPING', 'MODEM_S.IF.HOPPING', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IF_NOISEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IF_NOISEDET, self).__init__(register,
            'NOISEDET', 'MODEM_S.IF.NOISEDET', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_TXFRAMESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_TXFRAMESENT, self).__init__(register,
            'TXFRAMESENT', 'MODEM_S.IEN.TXFRAMESENT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_TXSYNCSENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_TXSYNCSENT, self).__init__(register,
            'TXSYNCSENT', 'MODEM_S.IEN.TXSYNCSENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_TXPRESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_TXPRESENT, self).__init__(register,
            'TXPRESENT', 'MODEM_S.IEN.TXPRESENT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_TXRAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_TXRAMPDONE, self).__init__(register,
            'TXRAMPDONE', 'MODEM_S.IEN.TXRAMPDONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_LDTNOARR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_LDTNOARR, self).__init__(register,
            'LDTNOARR', 'MODEM_S.IEN.LDTNOARR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_PHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_PHDSADET, self).__init__(register,
            'PHDSADET', 'MODEM_S.IEN.PHDSADET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_PHYUNCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_PHYUNCODEDET, self).__init__(register,
            'PHYUNCODEDET', 'MODEM_S.IEN.PHYUNCODEDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_PHYCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_PHYCODEDET, self).__init__(register,
            'PHYCODEDET', 'MODEM_S.IEN.PHYCODEDET', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXTIMDET, self).__init__(register,
            'RXTIMDET', 'MODEM_S.IEN.RXTIMDET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXPREDET, self).__init__(register,
            'RXPREDET', 'MODEM_S.IEN.RXPREDET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXFRAMEDET0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXFRAMEDET0, self).__init__(register,
            'RXFRAMEDET0', 'MODEM_S.IEN.RXFRAMEDET0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXFRAMEDET1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXFRAMEDET1, self).__init__(register,
            'RXFRAMEDET1', 'MODEM_S.IEN.RXFRAMEDET1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXTIMLOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXTIMLOST, self).__init__(register,
            'RXTIMLOST', 'MODEM_S.IEN.RXTIMLOST', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXPRELOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXPRELOST, self).__init__(register,
            'RXPRELOST', 'MODEM_S.IEN.RXPRELOST', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXFRAMEDETOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXFRAMEDETOF, self).__init__(register,
            'RXFRAMEDETOF', 'MODEM_S.IEN.RXFRAMEDETOF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXTIMNF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXTIMNF, self).__init__(register,
            'RXTIMNF', 'MODEM_S.IEN.RXTIMNF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_FRCTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_FRCTIMOUT, self).__init__(register,
            'FRCTIMOUT', 'MODEM_S.IEN.FRCTIMOUT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_ETS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_ETS, self).__init__(register,
            'ETS', 'MODEM_S.IEN.ETS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_CFGANTPATTRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_CFGANTPATTRD, self).__init__(register,
            'CFGANTPATTRD', 'MODEM_S.IEN.CFGANTPATTRD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXRESTARTRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXRESTARTRSSIMAPRE, self).__init__(register,
            'RXRESTARTRSSIMAPRE', 'MODEM_S.IEN.RXRESTARTRSSIMAPRE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_RXRESTARTRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_RXRESTARTRSSIMASYNC, self).__init__(register,
            'RXRESTARTRSSIMASYNC', 'MODEM_S.IEN.RXRESTARTRSSIMASYNC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_SQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_SQDET, self).__init__(register,
            'SQDET', 'MODEM_S.IEN.SQDET', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_SQNOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_SQNOTDET, self).__init__(register,
            'SQNOTDET', 'MODEM_S.IEN.SQNOTDET', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_ANTDIVRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_ANTDIVRDY, self).__init__(register,
            'ANTDIVRDY', 'MODEM_S.IEN.ANTDIVRDY', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_SOFTRESETDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_SOFTRESETDONE, self).__init__(register,
            'SOFTRESETDONE', 'MODEM_S.IEN.SOFTRESETDONE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_SQPRENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_SQPRENOTDET, self).__init__(register,
            'SQPRENOTDET', 'MODEM_S.IEN.SQPRENOTDET', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_SQFRAMENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_SQFRAMENOTDET, self).__init__(register,
            'SQFRAMENOTDET', 'MODEM_S.IEN.SQFRAMENOTDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_SQAFCOUTOFBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_SQAFCOUTOFBAND, self).__init__(register,
            'SQAFCOUTOFBAND', 'MODEM_S.IEN.SQAFCOUTOFBAND', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_SIDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_SIDET, self).__init__(register,
            'SIDET', 'MODEM_S.IEN.SIDET', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_SIRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_SIRESET, self).__init__(register,
            'SIRESET', 'MODEM_S.IEN.SIRESET', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_HOPPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_HOPPING, self).__init__(register,
            'HOPPING', 'MODEM_S.IEN.HOPPING', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IEN_NOISEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IEN_NOISEDET, self).__init__(register,
            'NOISEDET', 'MODEM_S.IEN.NOISEDET', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_TXFRAMESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_TXFRAMESENT, self).__init__(register,
            'TXFRAMESENT', 'MODEM_S.SEQIF.TXFRAMESENT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_TXSYNCSENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_TXSYNCSENT, self).__init__(register,
            'TXSYNCSENT', 'MODEM_S.SEQIF.TXSYNCSENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_TXPRESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_TXPRESENT, self).__init__(register,
            'TXPRESENT', 'MODEM_S.SEQIF.TXPRESENT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_TXRAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_TXRAMPDONE, self).__init__(register,
            'TXRAMPDONE', 'MODEM_S.SEQIF.TXRAMPDONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_LDTNOARR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_LDTNOARR, self).__init__(register,
            'LDTNOARR', 'MODEM_S.SEQIF.LDTNOARR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_PHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_PHDSADET, self).__init__(register,
            'PHDSADET', 'MODEM_S.SEQIF.PHDSADET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_PHYUNCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_PHYUNCODEDET, self).__init__(register,
            'PHYUNCODEDET', 'MODEM_S.SEQIF.PHYUNCODEDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_PHYCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_PHYCODEDET, self).__init__(register,
            'PHYCODEDET', 'MODEM_S.SEQIF.PHYCODEDET', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXTIMDET, self).__init__(register,
            'RXTIMDET', 'MODEM_S.SEQIF.RXTIMDET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXPREDET, self).__init__(register,
            'RXPREDET', 'MODEM_S.SEQIF.RXPREDET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXFRAMEDET0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXFRAMEDET0, self).__init__(register,
            'RXFRAMEDET0', 'MODEM_S.SEQIF.RXFRAMEDET0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXFRAMEDET1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXFRAMEDET1, self).__init__(register,
            'RXFRAMEDET1', 'MODEM_S.SEQIF.RXFRAMEDET1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXTIMLOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXTIMLOST, self).__init__(register,
            'RXTIMLOST', 'MODEM_S.SEQIF.RXTIMLOST', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXPRELOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXPRELOST, self).__init__(register,
            'RXPRELOST', 'MODEM_S.SEQIF.RXPRELOST', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXFRAMEDETOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXFRAMEDETOF, self).__init__(register,
            'RXFRAMEDETOF', 'MODEM_S.SEQIF.RXFRAMEDETOF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXTIMNF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXTIMNF, self).__init__(register,
            'RXTIMNF', 'MODEM_S.SEQIF.RXTIMNF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_FRCTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_FRCTIMOUT, self).__init__(register,
            'FRCTIMOUT', 'MODEM_S.SEQIF.FRCTIMOUT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_ETS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_ETS, self).__init__(register,
            'ETS', 'MODEM_S.SEQIF.ETS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_CFGANTPATTRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_CFGANTPATTRD, self).__init__(register,
            'CFGANTPATTRD', 'MODEM_S.SEQIF.CFGANTPATTRD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXRESTARTRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXRESTARTRSSIMAPRE, self).__init__(register,
            'RXRESTARTRSSIMAPRE', 'MODEM_S.SEQIF.RXRESTARTRSSIMAPRE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_RXRESTARTRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_RXRESTARTRSSIMASYNC, self).__init__(register,
            'RXRESTARTRSSIMASYNC', 'MODEM_S.SEQIF.RXRESTARTRSSIMASYNC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_SQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_SQDET, self).__init__(register,
            'SQDET', 'MODEM_S.SEQIF.SQDET', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_SQNOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_SQNOTDET, self).__init__(register,
            'SQNOTDET', 'MODEM_S.SEQIF.SQNOTDET', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_ANTDIVRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_ANTDIVRDY, self).__init__(register,
            'ANTDIVRDY', 'MODEM_S.SEQIF.ANTDIVRDY', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_SOFTRESETDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_SOFTRESETDONE, self).__init__(register,
            'SOFTRESETDONE', 'MODEM_S.SEQIF.SOFTRESETDONE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_SQPRENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_SQPRENOTDET, self).__init__(register,
            'SQPRENOTDET', 'MODEM_S.SEQIF.SQPRENOTDET', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_SQFRAMENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_SQFRAMENOTDET, self).__init__(register,
            'SQFRAMENOTDET', 'MODEM_S.SEQIF.SQFRAMENOTDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_SQAFCOUTOFBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_SQAFCOUTOFBAND, self).__init__(register,
            'SQAFCOUTOFBAND', 'MODEM_S.SEQIF.SQAFCOUTOFBAND', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_SIDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_SIDET, self).__init__(register,
            'SIDET', 'MODEM_S.SEQIF.SIDET', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_SIRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_SIRESET, self).__init__(register,
            'SIRESET', 'MODEM_S.SEQIF.SIRESET', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_HOPPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_HOPPING, self).__init__(register,
            'HOPPING', 'MODEM_S.SEQIF.HOPPING', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIF_NOISEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIF_NOISEDET, self).__init__(register,
            'NOISEDET', 'MODEM_S.SEQIF.NOISEDET', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_TXFRAMESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_TXFRAMESENT, self).__init__(register,
            'TXFRAMESENT', 'MODEM_S.SEQIEN.TXFRAMESENT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_TXSYNCSENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_TXSYNCSENT, self).__init__(register,
            'TXSYNCSENT', 'MODEM_S.SEQIEN.TXSYNCSENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_TXPRESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_TXPRESENT, self).__init__(register,
            'TXPRESENT', 'MODEM_S.SEQIEN.TXPRESENT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_TXRAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_TXRAMPDONE, self).__init__(register,
            'TXRAMPDONE', 'MODEM_S.SEQIEN.TXRAMPDONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_LDTNOARR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_LDTNOARR, self).__init__(register,
            'LDTNOARR', 'MODEM_S.SEQIEN.LDTNOARR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_PHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_PHDSADET, self).__init__(register,
            'PHDSADET', 'MODEM_S.SEQIEN.PHDSADET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_PHYUNCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_PHYUNCODEDET, self).__init__(register,
            'PHYUNCODEDET', 'MODEM_S.SEQIEN.PHYUNCODEDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_PHYCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_PHYCODEDET, self).__init__(register,
            'PHYCODEDET', 'MODEM_S.SEQIEN.PHYCODEDET', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXTIMDET, self).__init__(register,
            'RXTIMDET', 'MODEM_S.SEQIEN.RXTIMDET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXPREDET, self).__init__(register,
            'RXPREDET', 'MODEM_S.SEQIEN.RXPREDET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXFRAMEDET0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXFRAMEDET0, self).__init__(register,
            'RXFRAMEDET0', 'MODEM_S.SEQIEN.RXFRAMEDET0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXFRAMEDET1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXFRAMEDET1, self).__init__(register,
            'RXFRAMEDET1', 'MODEM_S.SEQIEN.RXFRAMEDET1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXTIMLOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXTIMLOST, self).__init__(register,
            'RXTIMLOST', 'MODEM_S.SEQIEN.RXTIMLOST', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXPRELOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXPRELOST, self).__init__(register,
            'RXPRELOST', 'MODEM_S.SEQIEN.RXPRELOST', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXFRAMEDETOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXFRAMEDETOF, self).__init__(register,
            'RXFRAMEDETOF', 'MODEM_S.SEQIEN.RXFRAMEDETOF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXTIMNF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXTIMNF, self).__init__(register,
            'RXTIMNF', 'MODEM_S.SEQIEN.RXTIMNF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_FRCTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_FRCTIMOUT, self).__init__(register,
            'FRCTIMOUT', 'MODEM_S.SEQIEN.FRCTIMOUT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_ETS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_ETS, self).__init__(register,
            'ETS', 'MODEM_S.SEQIEN.ETS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_CFGANTPATTRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_CFGANTPATTRD, self).__init__(register,
            'CFGANTPATTRD', 'MODEM_S.SEQIEN.CFGANTPATTRD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXRESTARTRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXRESTARTRSSIMAPRE, self).__init__(register,
            'RXRESTARTRSSIMAPRE', 'MODEM_S.SEQIEN.RXRESTARTRSSIMAPRE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_RXRESTARTRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_RXRESTARTRSSIMASYNC, self).__init__(register,
            'RXRESTARTRSSIMASYNC', 'MODEM_S.SEQIEN.RXRESTARTRSSIMASYNC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_SQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_SQDET, self).__init__(register,
            'SQDET', 'MODEM_S.SEQIEN.SQDET', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_SQNOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_SQNOTDET, self).__init__(register,
            'SQNOTDET', 'MODEM_S.SEQIEN.SQNOTDET', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_ANTDIVRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_ANTDIVRDY, self).__init__(register,
            'ANTDIVRDY', 'MODEM_S.SEQIEN.ANTDIVRDY', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_SOFTRESETDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_SOFTRESETDONE, self).__init__(register,
            'SOFTRESETDONE', 'MODEM_S.SEQIEN.SOFTRESETDONE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_SQPRENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_SQPRENOTDET, self).__init__(register,
            'SQPRENOTDET', 'MODEM_S.SEQIEN.SQPRENOTDET', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_SQFRAMENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_SQFRAMENOTDET, self).__init__(register,
            'SQFRAMENOTDET', 'MODEM_S.SEQIEN.SQFRAMENOTDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_SQAFCOUTOFBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_SQAFCOUTOFBAND, self).__init__(register,
            'SQAFCOUTOFBAND', 'MODEM_S.SEQIEN.SQAFCOUTOFBAND', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_SIDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_SIDET, self).__init__(register,
            'SIDET', 'MODEM_S.SEQIEN.SIDET', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_SIRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_SIRESET, self).__init__(register,
            'SIRESET', 'MODEM_S.SEQIEN.SIRESET', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_HOPPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_HOPPING, self).__init__(register,
            'HOPPING', 'MODEM_S.SEQIEN.HOPPING', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SEQIEN_NOISEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SEQIEN_NOISEDET, self).__init__(register,
            'NOISEDET', 'MODEM_S.SEQIEN.NOISEDET', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_DEMODSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_DEMODSTATE, self).__init__(register,
            'DEMODSTATE', 'MODEM_S.STATUS.DEMODSTATE', 'read-only',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_BCRCFEDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_BCRCFEDSADET, self).__init__(register,
            'BCRCFEDSADET', 'MODEM_S.STATUS.BCRCFEDSADET', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_FRAMEDETID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_FRAMEDETID, self).__init__(register,
            'FRAMEDETID', 'MODEM_S.STATUS.FRAMEDETID', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_ANTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_ANTSEL, self).__init__(register,
            'ANTSEL', 'MODEM_S.STATUS.ANTSEL', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_TIMSEQINV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_TIMSEQINV, self).__init__(register,
            'TIMSEQINV', 'MODEM_S.STATUS.TIMSEQINV', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_TIMLOSTCAUSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_TIMLOSTCAUSE, self).__init__(register,
            'TIMLOSTCAUSE', 'MODEM_S.STATUS.TIMLOSTCAUSE', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_DSADETECTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_DSADETECTED, self).__init__(register,
            'DSADETECTED', 'MODEM_S.STATUS.DSADETECTED', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_DSAFREQESTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_DSAFREQESTDONE, self).__init__(register,
            'DSAFREQESTDONE', 'MODEM_S.STATUS.DSAFREQESTDONE', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_VITERBIDEMODTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_VITERBIDEMODTIMDET, self).__init__(register,
            'VITERBIDEMODTIMDET', 'MODEM_S.STATUS.VITERBIDEMODTIMDET', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_VITERBIDEMODFRAMEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_VITERBIDEMODFRAMEDET, self).__init__(register,
            'VITERBIDEMODFRAMEDET', 'MODEM_S.STATUS.VITERBIDEMODFRAMEDET', 'read-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_STAMPSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_STAMPSTATE, self).__init__(register,
            'STAMPSTATE', 'MODEM_S.STATUS.STAMPSTATE', 'read-only',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_TRECSDSAADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_TRECSDSAADET, self).__init__(register,
            'TRECSDSAADET', 'MODEM_S.STATUS.TRECSDSAADET', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_CORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_CORR, self).__init__(register,
            'CORR', 'MODEM_S.STATUS.CORR', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS_WEAKSYMBOLS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS_WEAKSYMBOLS, self).__init__(register,
            'WEAKSYMBOLS', 'MODEM_S.STATUS.WEAKSYMBOLS', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS2_CHPWRACCUMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS2_CHPWRACCUMUX, self).__init__(register,
            'CHPWRACCUMUX', 'MODEM_S.STATUS2.CHPWRACCUMUX', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS2_BBSSMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS2_BBSSMUX, self).__init__(register,
            'BBSSMUX', 'MODEM_S.STATUS2.BBSSMUX', 'read-only',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS2_LRBLECI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS2_LRBLECI, self).__init__(register,
            'LRBLECI', 'MODEM_S.STATUS2.LRBLECI', 'read-only',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS2_UNCODEDPHY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS2_UNCODEDPHY, self).__init__(register,
            'UNCODEDPHY', 'MODEM_S.STATUS2.UNCODEDPHY', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS2_CODEDPHY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS2_CODEDPHY, self).__init__(register,
            'CODEDPHY', 'MODEM_S.STATUS2.CODEDPHY', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS2_RTCOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS2_RTCOST, self).__init__(register,
            'RTCOST', 'MODEM_S.STATUS2.RTCOST', 'read-only',
            u"",
            18, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS3_BBPFOUTABS1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS3_BBPFOUTABS1, self).__init__(register,
            'BBPFOUTABS1', 'MODEM_S.STATUS3.BBPFOUTABS1', 'read-only',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS3_BBPFOUTABS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS3_BBPFOUTABS, self).__init__(register,
            'BBPFOUTABS', 'MODEM_S.STATUS3.BBPFOUTABS', 'read-only',
            u"",
            11, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS3_LRDSALIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS3_LRDSALIVE, self).__init__(register,
            'LRDSALIVE', 'MODEM_S.STATUS3.LRDSALIVE', 'read-only',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS3_COHDSALIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS3_COHDSALIVE, self).__init__(register,
            'COHDSALIVE', 'MODEM_S.STATUS3.COHDSALIVE', 'read-only',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS3_LRDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS3_LRDSADET, self).__init__(register,
            'LRDSADET', 'MODEM_S.STATUS3.LRDSADET', 'read-only',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS3_COHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS3_COHDSADET, self).__init__(register,
            'COHDSADET', 'MODEM_S.STATUS3.COHDSADET', 'read-only',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS3_SYNCSECPEAKABTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS3_SYNCSECPEAKABTH, self).__init__(register,
            'SYNCSECPEAKABTH', 'MODEM_S.STATUS3.SYNCSECPEAKABTH', 'read-only',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS3_SOFTRSTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS3_SOFTRSTDONE, self).__init__(register,
            'SOFTRSTDONE', 'MODEM_S.STATUS3.SOFTRSTDONE', 'read-only',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS4_ANT0RSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS4_ANT0RSSI, self).__init__(register,
            'ANT0RSSI', 'MODEM_S.STATUS4.ANT0RSSI', 'read-only',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS4_ANT1RSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS4_ANT1RSSI, self).__init__(register,
            'ANT1RSSI', 'MODEM_S.STATUS4.ANT1RSSI', 'read-only',
            u"",
            16, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS5_RXRESTARTMAFLTDOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS5_RXRESTARTMAFLTDOUT, self).__init__(register,
            'RXRESTARTMAFLTDOUT', 'MODEM_S.STATUS5.RXRESTARTMAFLTDOUT', 'read-only',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS6_ANT0CORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS6_ANT0CORR, self).__init__(register,
            'ANT0CORR', 'MODEM_S.STATUS6.ANT0CORR', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS6_ANT1CORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS6_ANT1CORR, self).__init__(register,
            'ANT1CORR', 'MODEM_S.STATUS6.ANT1CORR', 'read-only',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS6_ANT0OUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS6_ANT0OUT, self).__init__(register,
            'ANT0OUT', 'MODEM_S.STATUS6.ANT0OUT', 'read-only',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS6_ANT1OUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS6_ANT1OUT, self).__init__(register,
            'ANT1OUT', 'MODEM_S.STATUS6.ANT1OUT', 'read-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS7_FDEVEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS7_FDEVEST, self).__init__(register,
            'FDEVEST', 'MODEM_S.STATUS7.FDEVEST', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS7_DEMODSOFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS7_DEMODSOFT, self).__init__(register,
            'DEMODSOFT', 'MODEM_S.STATUS7.DEMODSOFT', 'read-only',
            u"",
            6, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS7_CFEPHDIFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS7_CFEPHDIFF, self).__init__(register,
            'CFEPHDIFF', 'MODEM_S.STATUS7.CFEPHDIFF', 'read-only',
            u"",
            19, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS7_MINCOSTPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS7_MINCOSTPASS, self).__init__(register,
            'MINCOSTPASS', 'MODEM_S.STATUS7.MINCOSTPASS', 'read-only',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_STATUS7_CFEDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_STATUS7_CFEDSADET, self).__init__(register,
            'CFEDSADET', 'MODEM_S.STATUS7.CFEDSADET', 'read-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMDETSTATUS_TIMDETCORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMDETSTATUS_TIMDETCORR, self).__init__(register,
            'TIMDETCORR', 'MODEM_S.TIMDETSTATUS.TIMDETCORR', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMDETSTATUS_TIMDETFREQOFFEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMDETSTATUS_TIMDETFREQOFFEST, self).__init__(register,
            'TIMDETFREQOFFEST', 'MODEM_S.TIMDETSTATUS.TIMDETFREQOFFEST', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMDETSTATUS_TIMDETPREERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMDETSTATUS_TIMDETPREERRORS, self).__init__(register,
            'TIMDETPREERRORS', 'MODEM_S.TIMDETSTATUS.TIMDETPREERRORS', 'read-only',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMDETSTATUS_TIMDETPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMDETSTATUS_TIMDETPASS, self).__init__(register,
            'TIMDETPASS', 'MODEM_S.TIMDETSTATUS.TIMDETPASS', 'read-only',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMDETSTATUS_TIMDETINDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMDETSTATUS_TIMDETINDEX, self).__init__(register,
            'TIMDETINDEX', 'MODEM_S.TIMDETSTATUS.TIMDETINDEX', 'read-only',
            u"",
            25, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FSMSTATUS_DETSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FSMSTATUS_DETSTATE, self).__init__(register,
            'DETSTATE', 'MODEM_S.FSMSTATUS.DETSTATE', 'read-only',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FSMSTATUS_DSASTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FSMSTATUS_DSASTATE, self).__init__(register,
            'DSASTATE', 'MODEM_S.FSMSTATUS.DSASTATE', 'read-only',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FSMSTATUS_LRBLESTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FSMSTATUS_LRBLESTATE, self).__init__(register,
            'LRBLESTATE', 'MODEM_S.FSMSTATUS.LRBLESTATE', 'read-only',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FSMSTATUS_NBBLESTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FSMSTATUS_NBBLESTATE, self).__init__(register,
            'NBBLESTATE', 'MODEM_S.FSMSTATUS.NBBLESTATE', 'read-only',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FSMSTATUS_ANTDIVSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FSMSTATUS_ANTDIVSTATE, self).__init__(register,
            'ANTDIVSTATE', 'MODEM_S.FSMSTATUS.ANTDIVSTATE', 'read-only',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FSMSTATUS_EHDSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FSMSTATUS_EHDSTATE, self).__init__(register,
            'EHDSTATE', 'MODEM_S.FSMSTATUS.EHDSTATE', 'read-only',
            u"",
            24, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FREQOFFEST_FREQOFFEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FREQOFFEST_FREQOFFEST, self).__init__(register,
            'FREQOFFEST', 'MODEM_S.FREQOFFEST.FREQOFFEST', 'read-only',
            u"",
            0, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FREQOFFEST_CORRVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FREQOFFEST_CORRVAL, self).__init__(register,
            'CORRVAL', 'MODEM_S.FREQOFFEST.CORRVAL', 'read-only',
            u"",
            13, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FREQOFFEST_SOFTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FREQOFFEST_SOFTVAL, self).__init__(register,
            'SOFTVAL', 'MODEM_S.FREQOFFEST.SOFTVAL', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFCADJRX_AFCADJRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFCADJRX_AFCADJRX, self).__init__(register,
            'AFCADJRX', 'MODEM_S.AFCADJRX.AFCADJRX', 'read-only',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFCADJRX_AFCSCALEM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFCADJRX_AFCSCALEM, self).__init__(register,
            'AFCSCALEM', 'MODEM_S.AFCADJRX.AFCSCALEM', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFCADJRX_AFCSCALEE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFCADJRX_AFCSCALEE, self).__init__(register,
            'AFCSCALEE', 'MODEM_S.AFCADJRX.AFCSCALEE', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFCADJTX_AFCADJTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFCADJTX_AFCADJTX, self).__init__(register,
            'AFCADJTX', 'MODEM_S.AFCADJTX.AFCADJTX', 'read-only',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFCADJTX_AFCSCALEM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFCADJTX_AFCSCALEM, self).__init__(register,
            'AFCSCALEM', 'MODEM_S.AFCADJTX.AFCSCALEM', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFCADJTX_AFCSCALEE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFCADJTX_AFCSCALEE, self).__init__(register,
            'AFCSCALEE', 'MODEM_S.AFCADJTX.AFCSCALEE', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_MIXCTRL_DIGIQSWAPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_MIXCTRL_DIGIQSWAPEN, self).__init__(register,
            'DIGIQSWAPEN', 'MODEM_S.MIXCTRL.DIGIQSWAPEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_FDM0DIFFDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_FDM0DIFFDIS, self).__init__(register,
            'FDM0DIFFDIS', 'MODEM_S.CTRL0.FDM0DIFFDIS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_MAPFSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_MAPFSK, self).__init__(register,
            'MAPFSK', 'MODEM_S.CTRL0.MAPFSK', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_CODING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_CODING, self).__init__(register,
            'CODING', 'MODEM_S.CTRL0.CODING', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_MODFORMAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_MODFORMAT, self).__init__(register,
            'MODFORMAT', 'MODEM_S.CTRL0.MODFORMAT', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_DUALCORROPTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_DUALCORROPTDIS, self).__init__(register,
            'DUALCORROPTDIS', 'MODEM_S.CTRL0.DUALCORROPTDIS', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_OOKASYNCPIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_OOKASYNCPIN, self).__init__(register,
            'OOKASYNCPIN', 'MODEM_S.CTRL0.OOKASYNCPIN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_DSSSLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_DSSSLEN, self).__init__(register,
            'DSSSLEN', 'MODEM_S.CTRL0.DSSSLEN', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_DSSSSHIFTS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_DSSSSHIFTS, self).__init__(register,
            'DSSSSHIFTS', 'MODEM_S.CTRL0.DSSSSHIFTS', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_DSSSDOUBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_DSSSDOUBLE, self).__init__(register,
            'DSSSDOUBLE', 'MODEM_S.CTRL0.DSSSDOUBLE', 'read-write',
            u"",
            19, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_DETDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_DETDIS, self).__init__(register,
            'DETDIS', 'MODEM_S.CTRL0.DETDIS', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_DIFFENCMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_DIFFENCMODE, self).__init__(register,
            'DIFFENCMODE', 'MODEM_S.CTRL0.DIFFENCMODE', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_SHAPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_SHAPING, self).__init__(register,
            'SHAPING', 'MODEM_S.CTRL0.SHAPING', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_DEMODRAWDATASEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_DEMODRAWDATASEL, self).__init__(register,
            'DEMODRAWDATASEL', 'MODEM_S.CTRL0.DEMODRAWDATASEL', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL0_FRAMEDETDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL0_FRAMEDETDEL, self).__init__(register,
            'FRAMEDETDEL', 'MODEM_S.CTRL0.FRAMEDETDEL', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_SYNCBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_SYNCBITS, self).__init__(register,
            'SYNCBITS', 'MODEM_S.CTRL1.SYNCBITS', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_SYNCERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_SYNCERRORS, self).__init__(register,
            'SYNCERRORS', 'MODEM_S.CTRL1.SYNCERRORS', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_TXSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_TXSYNC, self).__init__(register,
            'TXSYNC', 'MODEM_S.CTRL1.TXSYNC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_SYNCDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_SYNCDATA, self).__init__(register,
            'SYNCDATA', 'MODEM_S.CTRL1.SYNCDATA', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_SYNC1INV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_SYNC1INV, self).__init__(register,
            'SYNC1INV', 'MODEM_S.CTRL1.SYNC1INV', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_COMPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_COMPMODE, self).__init__(register,
            'COMPMODE', 'MODEM_S.CTRL1.COMPMODE', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_RESYNCPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_RESYNCPER, self).__init__(register,
            'RESYNCPER', 'MODEM_S.CTRL1.RESYNCPER', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_PHASEDEMOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_PHASEDEMOD, self).__init__(register,
            'PHASEDEMOD', 'MODEM_S.CTRL1.PHASEDEMOD', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_FREQOFFESTPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_FREQOFFESTPER, self).__init__(register,
            'FREQOFFESTPER', 'MODEM_S.CTRL1.FREQOFFESTPER', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL1_FREQOFFESTLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL1_FREQOFFESTLIM, self).__init__(register,
            'FREQOFFESTLIM', 'MODEM_S.CTRL1.FREQOFFESTLIM', 'read-write',
            u"",
            25, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_SQITHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_SQITHRESH, self).__init__(register,
            'SQITHRESH', 'MODEM_S.CTRL2.SQITHRESH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_RXFRCDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_RXFRCDIS, self).__init__(register,
            'RXFRCDIS', 'MODEM_S.CTRL2.RXFRCDIS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_RXPINMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_RXPINMODE, self).__init__(register,
            'RXPINMODE', 'MODEM_S.CTRL2.RXPINMODE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_TXPINMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_TXPINMODE, self).__init__(register,
            'TXPINMODE', 'MODEM_S.CTRL2.TXPINMODE', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_DATAFILTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_DATAFILTER, self).__init__(register,
            'DATAFILTER', 'MODEM_S.CTRL2.DATAFILTER', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_BRDIVA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_BRDIVA, self).__init__(register,
            'BRDIVA', 'MODEM_S.CTRL2.BRDIVA', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_BRDIVB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_BRDIVB, self).__init__(register,
            'BRDIVB', 'MODEM_S.CTRL2.BRDIVB', 'read-write',
            u"",
            19, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_DEVMULA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_DEVMULA, self).__init__(register,
            'DEVMULA', 'MODEM_S.CTRL2.DEVMULA', 'read-write',
            u"",
            23, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_DEVMULB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_DEVMULB, self).__init__(register,
            'DEVMULB', 'MODEM_S.CTRL2.DEVMULB', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_RATESELMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_RATESELMODE, self).__init__(register,
            'RATESELMODE', 'MODEM_S.CTRL2.RATESELMODE', 'read-write',
            u"",
            27, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_DEVWEIGHTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_DEVWEIGHTDIS, self).__init__(register,
            'DEVWEIGHTDIS', 'MODEM_S.CTRL2.DEVWEIGHTDIS', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL2_DMASEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL2_DMASEL, self).__init__(register,
            'DMASEL', 'MODEM_S.CTRL2.DMASEL', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_PRSDINEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_PRSDINEN, self).__init__(register,
            'PRSDINEN', 'MODEM_S.CTRL3.PRSDINEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_TIMINGBASESGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_TIMINGBASESGAIN, self).__init__(register,
            'TIMINGBASESGAIN', 'MODEM_S.CTRL3.TIMINGBASESGAIN', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_DEVMULBCW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_DEVMULBCW, self).__init__(register,
            'DEVMULBCW', 'MODEM_S.CTRL3.DEVMULBCW', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_RAMTESTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_RAMTESTEN, self).__init__(register,
            'RAMTESTEN', 'MODEM_S.CTRL3.RAMTESTEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_ANTDIVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_ANTDIVMODE, self).__init__(register,
            'ANTDIVMODE', 'MODEM_S.CTRL3.ANTDIVMODE', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_ANTDIVREPEATDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_ANTDIVREPEATDIS, self).__init__(register,
            'ANTDIVREPEATDIS', 'MODEM_S.CTRL3.ANTDIVREPEATDIS', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_TSAMPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_TSAMPMODE, self).__init__(register,
            'TSAMPMODE', 'MODEM_S.CTRL3.TSAMPMODE', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_TSAMPDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_TSAMPDEL, self).__init__(register,
            'TSAMPDEL', 'MODEM_S.CTRL3.TSAMPDEL', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL3_TSAMPLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL3_TSAMPLIM, self).__init__(register,
            'TSAMPLIM', 'MODEM_S.CTRL3.TSAMPLIM', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_ISICOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_ISICOMP, self).__init__(register,
            'ISICOMP', 'MODEM_S.CTRL4.ISICOMP', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_DEVOFFCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_DEVOFFCOMP, self).__init__(register,
            'DEVOFFCOMP', 'MODEM_S.CTRL4.DEVOFFCOMP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_PREDISTGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_PREDISTGAIN, self).__init__(register,
            'PREDISTGAIN', 'MODEM_S.CTRL4.PREDISTGAIN', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_PREDISTDEB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_PREDISTDEB, self).__init__(register,
            'PREDISTDEB', 'MODEM_S.CTRL4.PREDISTDEB', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_PREDISTAVG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_PREDISTAVG, self).__init__(register,
            'PREDISTAVG', 'MODEM_S.CTRL4.PREDISTAVG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_PREDISTRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_PREDISTRST, self).__init__(register,
            'PREDISTRST', 'MODEM_S.CTRL4.PREDISTRST', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_PHASECLICKFILT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_PHASECLICKFILT, self).__init__(register,
            'PHASECLICKFILT', 'MODEM_S.CTRL4.PHASECLICKFILT', 'read-write',
            u"",
            15, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_SOFTDSSSMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_SOFTDSSSMODE, self).__init__(register,
            'SOFTDSSSMODE', 'MODEM_S.CTRL4.SOFTDSSSMODE', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_ADCSATLEVEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_ADCSATLEVEL, self).__init__(register,
            'ADCSATLEVEL', 'MODEM_S.CTRL4.ADCSATLEVEL', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_ADCSATDENS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_ADCSATDENS, self).__init__(register,
            'ADCSATDENS', 'MODEM_S.CTRL4.ADCSATDENS', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_OFFSETPHASEMASKING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_OFFSETPHASEMASKING, self).__init__(register,
            'OFFSETPHASEMASKING', 'MODEM_S.CTRL4.OFFSETPHASEMASKING', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_OFFSETPHASESCALING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_OFFSETPHASESCALING, self).__init__(register,
            'OFFSETPHASESCALING', 'MODEM_S.CTRL4.OFFSETPHASESCALING', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL4_CLKUNDIVREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL4_CLKUNDIVREQ, self).__init__(register,
            'CLKUNDIVREQ', 'MODEM_S.CTRL4.CLKUNDIVREQ', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_BRCALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_BRCALEN, self).__init__(register,
            'BRCALEN', 'MODEM_S.CTRL5.BRCALEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_BRCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_BRCALMODE, self).__init__(register,
            'BRCALMODE', 'MODEM_S.CTRL5.BRCALMODE', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_BRCALAVG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_BRCALAVG, self).__init__(register,
            'BRCALAVG', 'MODEM_S.CTRL5.BRCALAVG', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_DETDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_DETDEL, self).__init__(register,
            'DETDEL', 'MODEM_S.CTRL5.DETDEL', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_TDEDGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_TDEDGE, self).__init__(register,
            'TDEDGE', 'MODEM_S.CTRL5.TDEDGE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_TREDGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_TREDGE, self).__init__(register,
            'TREDGE', 'MODEM_S.CTRL5.TREDGE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_DSSSCTD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_DSSSCTD, self).__init__(register,
            'DSSSCTD', 'MODEM_S.CTRL5.DSSSCTD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_BBSS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_BBSS, self).__init__(register,
            'BBSS', 'MODEM_S.CTRL5.BBSS', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_POEPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_POEPER, self).__init__(register,
            'POEPER', 'MODEM_S.CTRL5.POEPER', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_DEMODRAWDATASEL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_DEMODRAWDATASEL2, self).__init__(register,
            'DEMODRAWDATASEL2', 'MODEM_S.CTRL5.DEMODRAWDATASEL2', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_FOEPREAVG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_FOEPREAVG, self).__init__(register,
            'FOEPREAVG', 'MODEM_S.CTRL5.FOEPREAVG', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_LINCORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_LINCORR, self).__init__(register,
            'LINCORR', 'MODEM_S.CTRL5.LINCORR', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_RESYNCBAUDTRANS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_RESYNCBAUDTRANS, self).__init__(register,
            'RESYNCBAUDTRANS', 'MODEM_S.CTRL5.RESYNCBAUDTRANS', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL5_RESYNCLIMIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL5_RESYNCLIMIT, self).__init__(register,
            'RESYNCLIMIT', 'MODEM_S.CTRL5.RESYNCLIMIT', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_TDREW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_TDREW, self).__init__(register,
            'TDREW', 'MODEM_S.CTRL6.TDREW', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_PREBASES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_PREBASES, self).__init__(register,
            'PREBASES', 'MODEM_S.CTRL6.PREBASES', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_PSTIMABORT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_PSTIMABORT0, self).__init__(register,
            'PSTIMABORT0', 'MODEM_S.CTRL6.PSTIMABORT0', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_PSTIMABORT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_PSTIMABORT1, self).__init__(register,
            'PSTIMABORT1', 'MODEM_S.CTRL6.PSTIMABORT1', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_PSTIMABORT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_PSTIMABORT2, self).__init__(register,
            'PSTIMABORT2', 'MODEM_S.CTRL6.PSTIMABORT2', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_PSTIMABORT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_PSTIMABORT3, self).__init__(register,
            'PSTIMABORT3', 'MODEM_S.CTRL6.PSTIMABORT3', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_ARW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_ARW, self).__init__(register,
            'ARW', 'MODEM_S.CTRL6.ARW', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_TIMTHRESHGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_TIMTHRESHGAIN, self).__init__(register,
            'TIMTHRESHGAIN', 'MODEM_S.CTRL6.TIMTHRESHGAIN', 'read-write',
            u"",
            17, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_CPLXCORREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_CPLXCORREN, self).__init__(register,
            'CPLXCORREN', 'MODEM_S.CTRL6.CPLXCORREN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_DSSS3SYMBOLSYNCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_DSSS3SYMBOLSYNCEN, self).__init__(register,
            'DSSS3SYMBOLSYNCEN', 'MODEM_S.CTRL6.DSSS3SYMBOLSYNCEN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_TXDBPSKINV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_TXDBPSKINV, self).__init__(register,
            'TXDBPSKINV', 'MODEM_S.CTRL6.TXDBPSKINV', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_TXDBPSKRAMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_TXDBPSKRAMPEN, self).__init__(register,
            'TXDBPSKRAMPEN', 'MODEM_S.CTRL6.TXDBPSKRAMPEN', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_IFADCDIGGAINCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_IFADCDIGGAINCLKSEL, self).__init__(register,
            'IFADCDIGGAINCLKSEL', 'MODEM_S.CTRL6.IFADCDIGGAINCLKSEL', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_CODINGB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_CODINGB, self).__init__(register,
            'CODINGB', 'MODEM_S.CTRL6.CODINGB', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_IFADCDIGGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_IFADCDIGGAIN, self).__init__(register,
            'IFADCDIGGAIN', 'MODEM_S.CTRL6.IFADCDIGGAIN', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_RXRESTARTUPONRSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_RXRESTARTUPONRSSI, self).__init__(register,
            'RXRESTARTUPONRSSI', 'MODEM_S.CTRL6.RXRESTARTUPONRSSI', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_RXRESTARTUPONSHORTRSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_RXRESTARTUPONSHORTRSSI, self).__init__(register,
            'RXRESTARTUPONSHORTRSSI', 'MODEM_S.CTRL6.RXRESTARTUPONSHORTRSSI', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_RXBRCALCDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_RXBRCALCDIS, self).__init__(register,
            'RXBRCALCDIS', 'MODEM_S.CTRL6.RXBRCALCDIS', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CTRL6_DEMODRESTARTALL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CTRL6_DEMODRESTARTALL, self).__init__(register,
            'DEMODRESTARTALL', 'MODEM_S.CTRL6.DEMODRESTARTALL', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXBR_TXBRNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXBR_TXBRNUM, self).__init__(register,
            'TXBRNUM', 'MODEM_S.TXBR.TXBRNUM', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXBR_TXBRDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXBR_TXBRDEN, self).__init__(register,
            'TXBRDEN', 'MODEM_S.TXBR.TXBRDEN', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXBR_RXBRNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXBR_RXBRNUM, self).__init__(register,
            'RXBRNUM', 'MODEM_S.RXBR.RXBRNUM', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXBR_RXBRDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXBR_RXBRDEN, self).__init__(register,
            'RXBRDEN', 'MODEM_S.RXBR.RXBRDEN', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXBR_RXBRINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXBR_RXBRINT, self).__init__(register,
            'RXBRINT', 'MODEM_S.RXBR.RXBRINT', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CF_DEC0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CF_DEC0, self).__init__(register,
            'DEC0', 'MODEM_S.CF.DEC0', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CF_DEC1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CF_DEC1, self).__init__(register,
            'DEC1', 'MODEM_S.CF.DEC1', 'read-write',
            u"",
            3, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CF_DEC2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CF_DEC2, self).__init__(register,
            'DEC2', 'MODEM_S.CF.DEC2', 'read-write',
            u"",
            17, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CF_CFOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CF_CFOSR, self).__init__(register,
            'CFOSR', 'MODEM_S.CF.CFOSR', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CF_DEC1GAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CF_DEC1GAIN, self).__init__(register,
            'DEC1GAIN', 'MODEM_S.CF.DEC1GAIN', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CF_ADCBITORDERI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CF_ADCBITORDERI, self).__init__(register,
            'ADCBITORDERI', 'MODEM_S.CF.ADCBITORDERI', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CF_ADCBITORDERQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CF_ADCBITORDERQ, self).__init__(register,
            'ADCBITORDERQ', 'MODEM_S.CF.ADCBITORDERQ', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_BASE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_BASE, self).__init__(register,
            'BASE', 'MODEM_S.PRE.BASE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_BASEBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_BASEBITS, self).__init__(register,
            'BASEBITS', 'MODEM_S.PRE.BASEBITS', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_PRESYMB4FSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_PRESYMB4FSK, self).__init__(register,
            'PRESYMB4FSK', 'MODEM_S.PRE.PRESYMB4FSK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_PREERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_PREERRORS, self).__init__(register,
            'PREERRORS', 'MODEM_S.PRE.PREERRORS', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_DSSSPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_DSSSPRE, self).__init__(register,
            'DSSSPRE', 'MODEM_S.PRE.DSSSPRE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_SYNCSYMB4FSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_SYNCSYMB4FSK, self).__init__(register,
            'SYNCSYMB4FSK', 'MODEM_S.PRE.SYNCSYMB4FSK', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_PREAMBDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_PREAMBDETEN, self).__init__(register,
            'PREAMBDETEN', 'MODEM_S.PRE.PREAMBDETEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_PREWNDERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_PREWNDERRORS, self).__init__(register,
            'PREWNDERRORS', 'MODEM_S.PRE.PREWNDERRORS', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRE_TXBASES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRE_TXBASES, self).__init__(register,
            'TXBASES', 'MODEM_S.PRE.TXBASES', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_TIMTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_TIMTHRESH, self).__init__(register,
            'TIMTHRESH', 'MODEM_S.TIMING.TIMTHRESH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_TIMINGBASES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_TIMINGBASES, self).__init__(register,
            'TIMINGBASES', 'MODEM_S.TIMING.TIMINGBASES', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_ADDTIMSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_ADDTIMSEQ, self).__init__(register,
            'ADDTIMSEQ', 'MODEM_S.TIMING.ADDTIMSEQ', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_TIMSEQINVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_TIMSEQINVEN, self).__init__(register,
            'TIMSEQINVEN', 'MODEM_S.TIMING.TIMSEQINVEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_TIMSEQSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_TIMSEQSYNC, self).__init__(register,
            'TIMSEQSYNC', 'MODEM_S.TIMING.TIMSEQSYNC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_FDM0THRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_FDM0THRESH, self).__init__(register,
            'FDM0THRESH', 'MODEM_S.TIMING.FDM0THRESH', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_OFFSUBNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_OFFSUBNUM, self).__init__(register,
            'OFFSUBNUM', 'MODEM_S.TIMING.OFFSUBNUM', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_OFFSUBDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_OFFSUBDEN, self).__init__(register,
            'OFFSUBDEN', 'MODEM_S.TIMING.OFFSUBDEN', 'read-write',
            u"",
            25, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_TSAGCDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_TSAGCDEL, self).__init__(register,
            'TSAGCDEL', 'MODEM_S.TIMING.TSAGCDEL', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TIMING_FASTRESYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TIMING_FASTRESYNC, self).__init__(register,
            'FASTRESYNC', 'MODEM_S.TIMING.FASTRESYNC', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSSS0_DSSS0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSSS0_DSSS0, self).__init__(register,
            'DSSS0', 'MODEM_S.DSSS0.DSSS0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_MODINDEX_MODINDEXM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_MODINDEX_MODINDEXM, self).__init__(register,
            'MODINDEXM', 'MODEM_S.MODINDEX.MODINDEXM', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_MODINDEX_MODINDEXE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_MODINDEX_MODINDEXE, self).__init__(register,
            'MODINDEXE', 'MODEM_S.MODINDEX.MODINDEXE', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_MODINDEX_FREQGAINE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_MODINDEX_FREQGAINE, self).__init__(register,
            'FREQGAINE', 'MODEM_S.MODINDEX.FREQGAINE', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_MODINDEX_FREQGAINM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_MODINDEX_FREQGAINM, self).__init__(register,
            'FREQGAINM', 'MODEM_S.MODINDEX.FREQGAINM', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_MODINDEX_AMMODINDEXM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_MODINDEX_AMMODINDEXM, self).__init__(register,
            'AMMODINDEXM', 'MODEM_S.MODINDEX.AMMODINDEXM', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_MODINDEX_AMMODINDEXE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_MODINDEX_AMMODINDEXE, self).__init__(register,
            'AMMODINDEXE', 'MODEM_S.MODINDEX.AMMODINDEXE', 'read-write',
            u"",
            21, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCRXMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCRXMODE, self).__init__(register,
            'AFCRXMODE', 'MODEM_S.AFC.AFCRXMODE', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCTXMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCTXMODE, self).__init__(register,
            'AFCTXMODE', 'MODEM_S.AFC.AFCTXMODE', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCRXCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCRXCLR, self).__init__(register,
            'AFCRXCLR', 'MODEM_S.AFC.AFCRXCLR', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCDEL, self).__init__(register,
            'AFCDEL', 'MODEM_S.AFC.AFCDEL', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCAVGPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCAVGPER, self).__init__(register,
            'AFCAVGPER', 'MODEM_S.AFC.AFCAVGPER', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCLIMRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCLIMRESET, self).__init__(register,
            'AFCLIMRESET', 'MODEM_S.AFC.AFCLIMRESET', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCONESHOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCONESHOT, self).__init__(register,
            'AFCONESHOT', 'MODEM_S.AFC.AFCONESHOT', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCENINTCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCENINTCOMP, self).__init__(register,
            'AFCENINTCOMP', 'MODEM_S.AFC.AFCENINTCOMP', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCDSAFREQOFFEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCDSAFREQOFFEST, self).__init__(register,
            'AFCDSAFREQOFFEST', 'MODEM_S.AFC.AFCDSAFREQOFFEST', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCDELDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCDELDET, self).__init__(register,
            'AFCDELDET', 'MODEM_S.AFC.AFCDELDET', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_AFCGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_AFCGEAR, self).__init__(register,
            'AFCGEAR', 'MODEM_S.AFC.AFCGEAR', 'read-write',
            u"",
            29, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFC_DISAFCCTE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFC_DISAFCCTE, self).__init__(register,
            'DISAFCCTE', 'MODEM_S.AFC.DISAFCCTE', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AFCADJLIM_AFCADJLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AFCADJLIM_AFCADJLIM, self).__init__(register,
            'AFCADJLIM', 'MODEM_S.AFCADJLIM.AFCADJLIM', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING0_COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING0_COEFF0, self).__init__(register,
            'COEFF0', 'MODEM_S.SHAPING0.COEFF0', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING0_COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING0_COEFF1, self).__init__(register,
            'COEFF1', 'MODEM_S.SHAPING0.COEFF1', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING0_COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING0_COEFF2, self).__init__(register,
            'COEFF2', 'MODEM_S.SHAPING0.COEFF2', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING0_COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING0_COEFF3, self).__init__(register,
            'COEFF3', 'MODEM_S.SHAPING0.COEFF3', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING1_COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING1_COEFF4, self).__init__(register,
            'COEFF4', 'MODEM_S.SHAPING1.COEFF4', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING1_COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING1_COEFF5, self).__init__(register,
            'COEFF5', 'MODEM_S.SHAPING1.COEFF5', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING1_COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING1_COEFF6, self).__init__(register,
            'COEFF6', 'MODEM_S.SHAPING1.COEFF6', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING1_COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING1_COEFF7, self).__init__(register,
            'COEFF7', 'MODEM_S.SHAPING1.COEFF7', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING2_COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING2_COEFF8, self).__init__(register,
            'COEFF8', 'MODEM_S.SHAPING2.COEFF8', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING2_COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING2_COEFF9, self).__init__(register,
            'COEFF9', 'MODEM_S.SHAPING2.COEFF9', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING2_COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING2_COEFF10, self).__init__(register,
            'COEFF10', 'MODEM_S.SHAPING2.COEFF10', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING2_COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING2_COEFF11, self).__init__(register,
            'COEFF11', 'MODEM_S.SHAPING2.COEFF11', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING3_COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING3_COEFF12, self).__init__(register,
            'COEFF12', 'MODEM_S.SHAPING3.COEFF12', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING3_COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING3_COEFF13, self).__init__(register,
            'COEFF13', 'MODEM_S.SHAPING3.COEFF13', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING3_COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING3_COEFF14, self).__init__(register,
            'COEFF14', 'MODEM_S.SHAPING3.COEFF14', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING3_COEFF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING3_COEFF15, self).__init__(register,
            'COEFF15', 'MODEM_S.SHAPING3.COEFF15', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING4_COEFF16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING4_COEFF16, self).__init__(register,
            'COEFF16', 'MODEM_S.SHAPING4.COEFF16', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING4_COEFF17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING4_COEFF17, self).__init__(register,
            'COEFF17', 'MODEM_S.SHAPING4.COEFF17', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING4_COEFF18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING4_COEFF18, self).__init__(register,
            'COEFF18', 'MODEM_S.SHAPING4.COEFF18', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING4_COEFF19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING4_COEFF19, self).__init__(register,
            'COEFF19', 'MODEM_S.SHAPING4.COEFF19', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING5_COEFF20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING5_COEFF20, self).__init__(register,
            'COEFF20', 'MODEM_S.SHAPING5.COEFF20', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING5_COEFF21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING5_COEFF21, self).__init__(register,
            'COEFF21', 'MODEM_S.SHAPING5.COEFF21', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING5_COEFF22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING5_COEFF22, self).__init__(register,
            'COEFF22', 'MODEM_S.SHAPING5.COEFF22', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING5_COEFF23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING5_COEFF23, self).__init__(register,
            'COEFF23', 'MODEM_S.SHAPING5.COEFF23', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING6_COEFF24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING6_COEFF24, self).__init__(register,
            'COEFF24', 'MODEM_S.SHAPING6.COEFF24', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING6_COEFF25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING6_COEFF25, self).__init__(register,
            'COEFF25', 'MODEM_S.SHAPING6.COEFF25', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING6_COEFF26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING6_COEFF26, self).__init__(register,
            'COEFF26', 'MODEM_S.SHAPING6.COEFF26', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING6_COEFF27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING6_COEFF27, self).__init__(register,
            'COEFF27', 'MODEM_S.SHAPING6.COEFF27', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING7_COEFF28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING7_COEFF28, self).__init__(register,
            'COEFF28', 'MODEM_S.SHAPING7.COEFF28', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING7_COEFF29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING7_COEFF29, self).__init__(register,
            'COEFF29', 'MODEM_S.SHAPING7.COEFF29', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING7_COEFF30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING7_COEFF30, self).__init__(register,
            'COEFF30', 'MODEM_S.SHAPING7.COEFF30', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING7_COEFF31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING7_COEFF31, self).__init__(register,
            'COEFF31', 'MODEM_S.SHAPING7.COEFF31', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING8_COEFF32(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING8_COEFF32, self).__init__(register,
            'COEFF32', 'MODEM_S.SHAPING8.COEFF32', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING8_COEFF33(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING8_COEFF33, self).__init__(register,
            'COEFF33', 'MODEM_S.SHAPING8.COEFF33', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING8_COEFF34(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING8_COEFF34, self).__init__(register,
            'COEFF34', 'MODEM_S.SHAPING8.COEFF34', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING8_COEFF35(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING8_COEFF35, self).__init__(register,
            'COEFF35', 'MODEM_S.SHAPING8.COEFF35', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING9_COEFF36(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING9_COEFF36, self).__init__(register,
            'COEFF36', 'MODEM_S.SHAPING9.COEFF36', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING9_COEFF37(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING9_COEFF37, self).__init__(register,
            'COEFF37', 'MODEM_S.SHAPING9.COEFF37', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING9_COEFF38(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING9_COEFF38, self).__init__(register,
            'COEFF38', 'MODEM_S.SHAPING9.COEFF38', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING9_COEFF39(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING9_COEFF39, self).__init__(register,
            'COEFF39', 'MODEM_S.SHAPING9.COEFF39', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING10_COEFF40(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING10_COEFF40, self).__init__(register,
            'COEFF40', 'MODEM_S.SHAPING10.COEFF40', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING10_COEFF41(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING10_COEFF41, self).__init__(register,
            'COEFF41', 'MODEM_S.SHAPING10.COEFF41', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING10_COEFF42(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING10_COEFF42, self).__init__(register,
            'COEFF42', 'MODEM_S.SHAPING10.COEFF42', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING10_COEFF43(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING10_COEFF43, self).__init__(register,
            'COEFF43', 'MODEM_S.SHAPING10.COEFF43', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING11_COEFF44(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING11_COEFF44, self).__init__(register,
            'COEFF44', 'MODEM_S.SHAPING11.COEFF44', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING11_COEFF45(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING11_COEFF45, self).__init__(register,
            'COEFF45', 'MODEM_S.SHAPING11.COEFF45', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING11_COEFF46(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING11_COEFF46, self).__init__(register,
            'COEFF46', 'MODEM_S.SHAPING11.COEFF46', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING11_COEFF47(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING11_COEFF47, self).__init__(register,
            'COEFF47', 'MODEM_S.SHAPING11.COEFF47', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING12_COEFF48(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING12_COEFF48, self).__init__(register,
            'COEFF48', 'MODEM_S.SHAPING12.COEFF48', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING12_COEFF49(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING12_COEFF49, self).__init__(register,
            'COEFF49', 'MODEM_S.SHAPING12.COEFF49', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING12_COEFF50(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING12_COEFF50, self).__init__(register,
            'COEFF50', 'MODEM_S.SHAPING12.COEFF50', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING12_COEFF51(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING12_COEFF51, self).__init__(register,
            'COEFF51', 'MODEM_S.SHAPING12.COEFF51', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING13_COEFF52(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING13_COEFF52, self).__init__(register,
            'COEFF52', 'MODEM_S.SHAPING13.COEFF52', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING13_COEFF53(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING13_COEFF53, self).__init__(register,
            'COEFF53', 'MODEM_S.SHAPING13.COEFF53', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING13_COEFF54(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING13_COEFF54, self).__init__(register,
            'COEFF54', 'MODEM_S.SHAPING13.COEFF54', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING13_COEFF55(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING13_COEFF55, self).__init__(register,
            'COEFF55', 'MODEM_S.SHAPING13.COEFF55', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING14_COEFF56(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING14_COEFF56, self).__init__(register,
            'COEFF56', 'MODEM_S.SHAPING14.COEFF56', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING14_COEFF57(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING14_COEFF57, self).__init__(register,
            'COEFF57', 'MODEM_S.SHAPING14.COEFF57', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING14_COEFF58(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING14_COEFF58, self).__init__(register,
            'COEFF58', 'MODEM_S.SHAPING14.COEFF58', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING14_COEFF59(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING14_COEFF59, self).__init__(register,
            'COEFF59', 'MODEM_S.SHAPING14.COEFF59', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING15_COEFF60(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING15_COEFF60, self).__init__(register,
            'COEFF60', 'MODEM_S.SHAPING15.COEFF60', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING15_COEFF61(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING15_COEFF61, self).__init__(register,
            'COEFF61', 'MODEM_S.SHAPING15.COEFF61', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING15_COEFF62(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING15_COEFF62, self).__init__(register,
            'COEFF62', 'MODEM_S.SHAPING15.COEFF62', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SHAPING15_COEFF63(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SHAPING15_COEFF63, self).__init__(register,
            'COEFF63', 'MODEM_S.SHAPING15.COEFF63', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RAMPCTRL_RAMPRATE0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RAMPCTRL_RAMPRATE0, self).__init__(register,
            'RAMPRATE0', 'MODEM_S.RAMPCTRL.RAMPRATE0', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RAMPCTRL_RAMPRATE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RAMPCTRL_RAMPRATE1, self).__init__(register,
            'RAMPRATE1', 'MODEM_S.RAMPCTRL.RAMPRATE1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RAMPCTRL_RAMPRATE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RAMPCTRL_RAMPRATE2, self).__init__(register,
            'RAMPRATE2', 'MODEM_S.RAMPCTRL.RAMPRATE2', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RAMPCTRL_RAMPDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RAMPCTRL_RAMPDIS, self).__init__(register,
            'RAMPDIS', 'MODEM_S.RAMPCTRL.RAMPDIS', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RAMPCTRL_RAMPVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RAMPCTRL_RAMPVAL, self).__init__(register,
            'RAMPVAL', 'MODEM_S.RAMPCTRL.RAMPVAL', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RAMPLEV_RAMPLEV0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RAMPLEV_RAMPLEV0, self).__init__(register,
            'RAMPLEV0', 'MODEM_S.RAMPLEV.RAMPLEV0', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RAMPLEV_RAMPLEV1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RAMPLEV_RAMPLEV1, self).__init__(register,
            'RAMPLEV1', 'MODEM_S.RAMPLEV.RAMPLEV1', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RAMPLEV_RAMPLEV2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RAMPLEV_RAMPLEV2, self).__init__(register,
            'RAMPLEV2', 'MODEM_S.RAMPLEV.RAMPLEV2', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANARAMPCTRL_RAMPOVREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANARAMPCTRL_RAMPOVREN, self).__init__(register,
            'RAMPOVREN', 'MODEM_S.ANARAMPCTRL.RAMPOVREN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANARAMPCTRL_RAMPOVRUPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANARAMPCTRL_RAMPOVRUPD, self).__init__(register,
            'RAMPOVRUPD', 'MODEM_S.ANARAMPCTRL.RAMPOVRUPD', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANARAMPCTRL_VMIDCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANARAMPCTRL_VMIDCTRL, self).__init__(register,
            'VMIDCTRL', 'MODEM_S.ANARAMPCTRL.VMIDCTRL', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANARAMPCTRL_MUTEDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANARAMPCTRL_MUTEDLY, self).__init__(register,
            'MUTEDLY', 'MODEM_S.ANARAMPCTRL.MUTEDLY', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCESTIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCESTIEN, self).__init__(register,
            'DCESTIEN', 'MODEM_S.DCCOMP.DCESTIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCCOMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCCOMPEN, self).__init__(register,
            'DCCOMPEN', 'MODEM_S.DCCOMP.DCCOMPEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCRSTEN, self).__init__(register,
            'DCRSTEN', 'MODEM_S.DCCOMP.DCRSTEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCCOMPFREEZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCCOMPFREEZE, self).__init__(register,
            'DCCOMPFREEZE', 'MODEM_S.DCCOMP.DCCOMPFREEZE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCCOMPGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCCOMPGEAR, self).__init__(register,
            'DCCOMPGEAR', 'MODEM_S.DCCOMP.DCCOMPGEAR', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCLIMIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCLIMIT, self).__init__(register,
            'DCLIMIT', 'MODEM_S.DCCOMP.DCLIMIT', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCGAINGEAREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCGAINGEAREN, self).__init__(register,
            'DCGAINGEAREN', 'MODEM_S.DCCOMP.DCGAINGEAREN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCGAINGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCGAINGEAR, self).__init__(register,
            'DCGAINGEAR', 'MODEM_S.DCCOMP.DCGAINGEAR', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMP_DCGAINGEARSMPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMP_DCGAINGEARSMPS, self).__init__(register,
            'DCGAINGEARSMPS', 'MODEM_S.DCCOMP.DCGAINGEARSMPS', 'read-write',
            u"",
            13, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMPFILTINIT_DCCOMPINITVALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMPFILTINIT_DCCOMPINITVALI, self).__init__(register,
            'DCCOMPINITVALI', 'MODEM_S.DCCOMPFILTINIT.DCCOMPINITVALI', 'read-write',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMPFILTINIT_DCCOMPINITVALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMPFILTINIT_DCCOMPINITVALQ, self).__init__(register,
            'DCCOMPINITVALQ', 'MODEM_S.DCCOMPFILTINIT.DCCOMPINITVALQ', 'read-write',
            u"",
            15, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCCOMPFILTINIT_DCCOMPINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCCOMPFILTINIT_DCCOMPINIT, self).__init__(register,
            'DCCOMPINIT', 'MODEM_S.DCCOMPFILTINIT.DCCOMPINIT', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCESTI_DCCOMPESTIVALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCESTI_DCCOMPESTIVALI, self).__init__(register,
            'DCCOMPESTIVALI', 'MODEM_S.DCESTI.DCCOMPESTIVALI', 'read-only',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DCESTI_DCCOMPESTIVALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DCESTI_DCCOMPESTIVALQ, self).__init__(register,
            'DCCOMPESTIVALQ', 'MODEM_S.DCESTI.DCCOMPESTIVALQ', 'read-only',
            u"",
            15, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SRCCHF_CHMUTETIMER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SRCCHF_CHMUTETIMER, self).__init__(register,
            'CHMUTETIMER', 'MODEM_S.SRCCHF.CHMUTETIMER', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SRCCHF_SRCRATIO2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SRCCHF_SRCRATIO2, self).__init__(register,
            'SRCRATIO2', 'MODEM_S.SRCCHF.SRCRATIO2', 'read-write',
            u"",
            12, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SRCCHF_SRCENABLE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SRCCHF_SRCENABLE2, self).__init__(register,
            'SRCENABLE2', 'MODEM_S.SRCCHF.SRCENABLE2', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SRCCHF_INTOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SRCCHF_INTOSR, self).__init__(register,
            'INTOSR', 'MODEM_S.SRCCHF.INTOSR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_INTAFC_FOEPREAVG0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_INTAFC_FOEPREAVG0, self).__init__(register,
            'FOEPREAVG0', 'MODEM_S.INTAFC.FOEPREAVG0', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_INTAFC_FOEPREAVG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_INTAFC_FOEPREAVG1, self).__init__(register,
            'FOEPREAVG1', 'MODEM_S.INTAFC.FOEPREAVG1', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_INTAFC_FOEPREAVG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_INTAFC_FOEPREAVG2, self).__init__(register,
            'FOEPREAVG2', 'MODEM_S.INTAFC.FOEPREAVG2', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_INTAFC_FOEPREAVG3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_INTAFC_FOEPREAVG3, self).__init__(register,
            'FOEPREAVG3', 'MODEM_S.INTAFC.FOEPREAVG3', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_INTAFC_FOEPREAVG4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_INTAFC_FOEPREAVG4, self).__init__(register,
            'FOEPREAVG4', 'MODEM_S.INTAFC.FOEPREAVG4', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_INTAFC_FOEPREAVG5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_INTAFC_FOEPREAVG5, self).__init__(register,
            'FOEPREAVG5', 'MODEM_S.INTAFC.FOEPREAVG5', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_INTAFC_FOEPREAVG6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_INTAFC_FOEPREAVG6, self).__init__(register,
            'FOEPREAVG6', 'MODEM_S.INTAFC.FOEPREAVG6', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_INTAFC_FOEPREAVG7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_INTAFC_FOEPREAVG7, self).__init__(register,
            'FOEPREAVG7', 'MODEM_S.INTAFC.FOEPREAVG7', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD0_SPIKETHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD0_SPIKETHD, self).__init__(register,
            'SPIKETHD', 'MODEM_S.DSATHD0.SPIKETHD', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD0_UNMODTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD0_UNMODTHD, self).__init__(register,
            'UNMODTHD', 'MODEM_S.DSATHD0.UNMODTHD', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD0_FDEVMINTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD0_FDEVMINTHD, self).__init__(register,
            'FDEVMINTHD', 'MODEM_S.DSATHD0.FDEVMINTHD', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD0_FDEVMAXTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD0_FDEVMAXTHD, self).__init__(register,
            'FDEVMAXTHD', 'MODEM_S.DSATHD0.FDEVMAXTHD', 'read-write',
            u"",
            20, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_POWABSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_POWABSTHD, self).__init__(register,
            'POWABSTHD', 'MODEM_S.DSATHD1.POWABSTHD', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_POWRELTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_POWRELTHD, self).__init__(register,
            'POWRELTHD', 'MODEM_S.DSATHD1.POWRELTHD', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_DSARSTCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_DSARSTCNT, self).__init__(register,
            'DSARSTCNT', 'MODEM_S.DSATHD1.DSARSTCNT', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_RSSIJMPTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_RSSIJMPTHD, self).__init__(register,
            'RSSIJMPTHD', 'MODEM_S.DSATHD1.RSSIJMPTHD', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_FREQLATDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_FREQLATDLY, self).__init__(register,
            'FREQLATDLY', 'MODEM_S.DSATHD1.FREQLATDLY', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_PWRFLTBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_PWRFLTBYP, self).__init__(register,
            'PWRFLTBYP', 'MODEM_S.DSATHD1.PWRFLTBYP', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_AMPFLTBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_AMPFLTBYP, self).__init__(register,
            'AMPFLTBYP', 'MODEM_S.DSATHD1.AMPFLTBYP', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_PWRDETDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_PWRDETDIS, self).__init__(register,
            'PWRDETDIS', 'MODEM_S.DSATHD1.PWRDETDIS', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD1_FREQSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD1_FREQSCALE, self).__init__(register,
            'FREQSCALE', 'MODEM_S.DSATHD1.FREQSCALE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD2_POWABSTHDLOG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD2_POWABSTHDLOG, self).__init__(register,
            'POWABSTHDLOG', 'MODEM_S.DSATHD2.POWABSTHDLOG', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD2_JUMPDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD2_JUMPDETEN, self).__init__(register,
            'JUMPDETEN', 'MODEM_S.DSATHD2.JUMPDETEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD2_FDADJTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD2_FDADJTHD, self).__init__(register,
            'FDADJTHD', 'MODEM_S.DSATHD2.FDADJTHD', 'read-write',
            u"",
            10, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD2_PMDETPASSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD2_PMDETPASSTHD, self).__init__(register,
            'PMDETPASSTHD', 'MODEM_S.DSATHD2.PMDETPASSTHD', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD2_FREQESTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD2_FREQESTTHD, self).__init__(register,
            'FREQESTTHD', 'MODEM_S.DSATHD2.FREQESTTHD', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD2_INTERFERDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD2_INTERFERDET, self).__init__(register,
            'INTERFERDET', 'MODEM_S.DSATHD2.INTERFERDET', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD2_PMDETFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD2_PMDETFORCE, self).__init__(register,
            'PMDETFORCE', 'MODEM_S.DSATHD2.PMDETFORCE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD3_SPIKETHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD3_SPIKETHDLO, self).__init__(register,
            'SPIKETHDLO', 'MODEM_S.DSATHD3.SPIKETHDLO', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD3_UNMODTHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD3_UNMODTHDLO, self).__init__(register,
            'UNMODTHDLO', 'MODEM_S.DSATHD3.UNMODTHDLO', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD3_FDEVMINTHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD3_FDEVMINTHDLO, self).__init__(register,
            'FDEVMINTHDLO', 'MODEM_S.DSATHD3.FDEVMINTHDLO', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD3_FDEVMAXTHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD3_FDEVMAXTHDLO, self).__init__(register,
            'FDEVMAXTHDLO', 'MODEM_S.DSATHD3.FDEVMAXTHDLO', 'read-write',
            u"",
            20, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD4_POWABSTHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD4_POWABSTHDLO, self).__init__(register,
            'POWABSTHDLO', 'MODEM_S.DSATHD4.POWABSTHDLO', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD4_ARRTOLERTHD0LO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD4_ARRTOLERTHD0LO, self).__init__(register,
            'ARRTOLERTHD0LO', 'MODEM_S.DSATHD4.ARRTOLERTHD0LO', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD4_ARRTOLERTHD1LO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD4_ARRTOLERTHD1LO, self).__init__(register,
            'ARRTOLERTHD1LO', 'MODEM_S.DSATHD4.ARRTOLERTHD1LO', 'read-write',
            u"",
            21, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSATHD4_SWTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSATHD4_SWTHD, self).__init__(register,
            'SWTHD', 'MODEM_S.DSATHD4.SWTHD', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_DSAMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_DSAMODE, self).__init__(register,
            'DSAMODE', 'MODEM_S.DSACTRL.DSAMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_ARRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_ARRTHD, self).__init__(register,
            'ARRTHD', 'MODEM_S.DSACTRL.ARRTHD', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_ARRTOLERTHD0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_ARRTOLERTHD0, self).__init__(register,
            'ARRTOLERTHD0', 'MODEM_S.DSACTRL.ARRTOLERTHD0', 'read-write',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_ARRTOLERTHD1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_ARRTOLERTHD1, self).__init__(register,
            'ARRTOLERTHD1', 'MODEM_S.DSACTRL.ARRTOLERTHD1', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_SCHPRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_SCHPRD, self).__init__(register,
            'SCHPRD', 'MODEM_S.DSACTRL.SCHPRD', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_FREQAVGSYM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_FREQAVGSYM, self).__init__(register,
            'FREQAVGSYM', 'MODEM_S.DSACTRL.FREQAVGSYM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_TRANRSTDSA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_TRANRSTDSA, self).__init__(register,
            'TRANRSTDSA', 'MODEM_S.DSACTRL.TRANRSTDSA', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_DSARSTON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_DSARSTON, self).__init__(register,
            'DSARSTON', 'MODEM_S.DSACTRL.DSARSTON', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_GAINREDUCDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_GAINREDUCDLY, self).__init__(register,
            'GAINREDUCDLY', 'MODEM_S.DSACTRL.GAINREDUCDLY', 'read-write',
            u"",
            21, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_LOWDUTY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_LOWDUTY, self).__init__(register,
            'LOWDUTY', 'MODEM_S.DSACTRL.LOWDUTY', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_RESTORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_RESTORE, self).__init__(register,
            'RESTORE', 'MODEM_S.DSACTRL.RESTORE', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_AGCBAUDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_AGCBAUDEN, self).__init__(register,
            'AGCBAUDEN', 'MODEM_S.DSACTRL.AGCBAUDEN', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DSACTRL_AMPJUPTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DSACTRL_AMPJUPTHD, self).__init__(register,
            'AMPJUPTHD', 'MODEM_S.DSACTRL.AMPJUPTHD', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGMIXCTRL_DIGMIXFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGMIXCTRL_DIGMIXFREQ, self).__init__(register,
            'DIGMIXFREQ', 'MODEM_S.DIGMIXCTRL.DIGMIXFREQ', 'read-write',
            u"",
            0, 20)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGMIXCTRL_DIGMIXMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGMIXCTRL_DIGMIXMODE, self).__init__(register,
            'DIGMIXMODE', 'MODEM_S.DIGMIXCTRL.DIGMIXMODE', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGMIXCTRL_MIXERCONJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGMIXCTRL_MIXERCONJ, self).__init__(register,
            'MIXERCONJ', 'MODEM_S.DIGMIXCTRL.MIXERCONJ', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGMIXCTRL_DIGMIXFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGMIXCTRL_DIGMIXFB, self).__init__(register,
            'DIGMIXFB', 'MODEM_S.DIGMIXCTRL.DIGMIXFB', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGMIXCTRL_FWHOPPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGMIXCTRL_FWHOPPING, self).__init__(register,
            'FWHOPPING', 'MODEM_S.DIGMIXCTRL.FWHOPPING', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VITERBIDEMOD_VTDEMODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VITERBIDEMOD_VTDEMODEN, self).__init__(register,
            'VTDEMODEN', 'MODEM_S.VITERBIDEMOD.VTDEMODEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VITERBIDEMOD_HARDDECISION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VITERBIDEMOD_HARDDECISION, self).__init__(register,
            'HARDDECISION', 'MODEM_S.VITERBIDEMOD.HARDDECISION', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VITERBIDEMOD_VITERBIKSI1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VITERBIDEMOD_VITERBIKSI1, self).__init__(register,
            'VITERBIKSI1', 'MODEM_S.VITERBIDEMOD.VITERBIKSI1', 'read-write',
            u"",
            2, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VITERBIDEMOD_VITERBIKSI2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VITERBIDEMOD_VITERBIKSI2, self).__init__(register,
            'VITERBIKSI2', 'MODEM_S.VITERBIDEMOD.VITERBIKSI2', 'read-write',
            u"",
            9, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VITERBIDEMOD_VITERBIKSI3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VITERBIDEMOD_VITERBIKSI3, self).__init__(register,
            'VITERBIKSI3', 'MODEM_S.VITERBIDEMOD.VITERBIKSI3', 'read-write',
            u"",
            16, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VITERBIDEMOD_SYNTHAFC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VITERBIDEMOD_SYNTHAFC, self).__init__(register,
            'SYNTHAFC', 'MODEM_S.VITERBIDEMOD.SYNTHAFC', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VITERBIDEMOD_CORRCYCLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VITERBIDEMOD_CORRCYCLE, self).__init__(register,
            'CORRCYCLE', 'MODEM_S.VITERBIDEMOD.CORRCYCLE', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VITERBIDEMOD_CORRSTPSIZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VITERBIDEMOD_CORRSTPSIZE, self).__init__(register,
            'CORRSTPSIZE', 'MODEM_S.VITERBIDEMOD.CORRSTPSIZE', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTCORRCFG0_EXPECTPATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTCORRCFG0_EXPECTPATT, self).__init__(register,
            'EXPECTPATT', 'MODEM_S.VTCORRCFG0.EXPECTPATT', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTCORRCFG1_VITERBIKSI3WB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTCORRCFG1_VITERBIKSI3WB, self).__init__(register,
            'VITERBIKSI3WB', 'MODEM_S.VTCORRCFG1.VITERBIKSI3WB', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTCORRCFG1_KSI3SWENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTCORRCFG1_KSI3SWENABLE, self).__init__(register,
            'KSI3SWENABLE', 'MODEM_S.VTCORRCFG1.KSI3SWENABLE', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTCORRCFG1_VTFRQLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTCORRCFG1_VTFRQLIM, self).__init__(register,
            'VTFRQLIM', 'MODEM_S.VTCORRCFG1.VTFRQLIM', 'read-write',
            u"",
            8, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTCORRCFG1_EXPSYNCLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTCORRCFG1_EXPSYNCLEN, self).__init__(register,
            'EXPSYNCLEN', 'MODEM_S.VTCORRCFG1.EXPSYNCLEN', 'read-write',
            u"",
            18, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTCORRCFG1_EXPECTHT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTCORRCFG1_EXPECTHT, self).__init__(register,
            'EXPECTHT', 'MODEM_S.VTCORRCFG1.EXPECTHT', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTTRACK_FREQTRACKMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTTRACK_FREQTRACKMODE, self).__init__(register,
            'FREQTRACKMODE', 'MODEM_S.VTTRACK.FREQTRACKMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTTRACK_TIMTRACKTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTTRACK_TIMTRACKTHD, self).__init__(register,
            'TIMTRACKTHD', 'MODEM_S.VTTRACK.TIMTRACKTHD', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTTRACK_TIMEACQUTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTTRACK_TIMEACQUTHD, self).__init__(register,
            'TIMEACQUTHD', 'MODEM_S.VTTRACK.TIMEACQUTHD', 'read-write',
            u"",
            6, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTTRACK_TIMGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTTRACK_TIMGEAR, self).__init__(register,
            'TIMGEAR', 'MODEM_S.VTTRACK.TIMGEAR', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTTRACK_FREQBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTTRACK_FREQBIAS, self).__init__(register,
            'FREQBIAS', 'MODEM_S.VTTRACK.FREQBIAS', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTTRACK_HIPWRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTTRACK_HIPWRTHD, self).__init__(register,
            'HIPWRTHD', 'MODEM_S.VTTRACK.HIPWRTHD', 'read-write',
            u"",
            22, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTBLETIMING_VTBLETIMINGSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTBLETIMING_VTBLETIMINGSEL, self).__init__(register,
            'VTBLETIMINGSEL', 'MODEM_S.VTBLETIMING.VTBLETIMINGSEL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTBLETIMING_VTBLETIMINGCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTBLETIMING_VTBLETIMINGCLKSEL, self).__init__(register,
            'VTBLETIMINGCLKSEL', 'MODEM_S.VTBLETIMING.VTBLETIMINGCLKSEL', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTBLETIMING_TIMINGDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTBLETIMING_TIMINGDELAY, self).__init__(register,
            'TIMINGDELAY', 'MODEM_S.VTBLETIMING.TIMINGDELAY', 'read-write',
            u"",
            4, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTBLETIMING_FLENOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTBLETIMING_FLENOFF, self).__init__(register,
            'FLENOFF', 'MODEM_S.VTBLETIMING.FLENOFF', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_VTBLETIMING_DISDEMODOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_VTBLETIMING_DISDEMODOF, self).__init__(register,
            'DISDEMODOF', 'MODEM_S.VTBLETIMING.DISDEMODOF', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_BREST_BRESTINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_BREST_BRESTINT, self).__init__(register,
            'BRESTINT', 'MODEM_S.BREST.BRESTINT', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_BREST_BRESTNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_BREST_BRESTNUM, self).__init__(register,
            'BRESTNUM', 'MODEM_S.BREST.BRESTNUM', 'read-only',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_AUTOCG_AUTOCGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_AUTOCG_AUTOCGEN, self).__init__(register,
            'AUTOCGEN', 'MODEM_S.AUTOCG.AUTOCGEN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CGCLKSTOP_FORCEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CGCLKSTOP_FORCEOFF, self).__init__(register,
            'FORCEOFF', 'MODEM_S.CGCLKSTOP.FORCEOFF', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_POE_POEI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_POE_POEI, self).__init__(register,
            'POEI', 'MODEM_S.POE.POEI', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_POE_POEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_POE_POEQ, self).__init__(register,
            'POEQ', 'MODEM_S.POE.POEQ', 'read-only',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIRECTMODE_DMENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIRECTMODE_DMENABLE, self).__init__(register,
            'DMENABLE', 'MODEM_S.DIRECTMODE.DMENABLE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIRECTMODE_SYNCASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIRECTMODE_SYNCASYNC, self).__init__(register,
            'SYNCASYNC', 'MODEM_S.DIRECTMODE.SYNCASYNC', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIRECTMODE_SYNCPREAM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIRECTMODE_SYNCPREAM, self).__init__(register,
            'SYNCPREAM', 'MODEM_S.DIRECTMODE.SYNCPREAM', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIRECTMODE_CLKWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIRECTMODE_CLKWIDTH, self).__init__(register,
            'CLKWIDTH', 'MODEM_S.DIRECTMODE.CLKWIDTH', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE_LRCORRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE_LRCORRTHD, self).__init__(register,
            'LRCORRTHD', 'MODEM_S.LONGRANGE.LRCORRTHD', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE_LRCORRSCHWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE_LRCORRSCHWIN, self).__init__(register,
            'LRCORRSCHWIN', 'MODEM_S.LONGRANGE.LRCORRSCHWIN', 'read-write',
            u"",
            11, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE_LRBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE_LRBLE, self).__init__(register,
            'LRBLE', 'MODEM_S.LONGRANGE.LRBLE', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE_LRTIMCORRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE_LRTIMCORRTHD, self).__init__(register,
            'LRTIMCORRTHD', 'MODEM_S.LONGRANGE.LRTIMCORRTHD', 'read-write',
            u"",
            16, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE_LRBLEDSA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE_LRBLEDSA, self).__init__(register,
            'LRBLEDSA', 'MODEM_S.LONGRANGE.LRBLEDSA', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE_LRDEC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE_LRDEC, self).__init__(register,
            'LRDEC', 'MODEM_S.LONGRANGE.LRDEC', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_LRSS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_LRSS, self).__init__(register,
            'LRSS', 'MODEM_S.LONGRANGE1.LRSS', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_LRTIMEOUTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_LRTIMEOUTTHD, self).__init__(register,
            'LRTIMEOUTTHD', 'MODEM_S.LONGRANGE1.LRTIMEOUTTHD', 'read-write',
            u"",
            4, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_CHPWRACCUDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_CHPWRACCUDEL, self).__init__(register,
            'CHPWRACCUDEL', 'MODEM_S.LONGRANGE1.CHPWRACCUDEL', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_HYSVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_HYSVAL, self).__init__(register,
            'HYSVAL', 'MODEM_S.LONGRANGE1.HYSVAL', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_AVGWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_AVGWIN, self).__init__(register,
            'AVGWIN', 'MODEM_S.LONGRANGE1.AVGWIN', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_LRSPIKETHADD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_LRSPIKETHADD, self).__init__(register,
            'LRSPIKETHADD', 'MODEM_S.LONGRANGE1.LRSPIKETHADD', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_LOGICBASEDPUGATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_LOGICBASEDPUGATE, self).__init__(register,
            'LOGICBASEDPUGATE', 'MODEM_S.LONGRANGE1.LOGICBASEDPUGATE', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_LOGICBASEDLRDEMODGATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_LOGICBASEDLRDEMODGATE, self).__init__(register,
            'LOGICBASEDLRDEMODGATE', 'MODEM_S.LONGRANGE1.LOGICBASEDLRDEMODGATE', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE1_PREFILTLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE1_PREFILTLEN, self).__init__(register,
            'PREFILTLEN', 'MODEM_S.LONGRANGE1.PREFILTLEN', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE2_LRCHPWRTH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE2_LRCHPWRTH1, self).__init__(register,
            'LRCHPWRTH1', 'MODEM_S.LONGRANGE2.LRCHPWRTH1', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE2_LRCHPWRTH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE2_LRCHPWRTH2, self).__init__(register,
            'LRCHPWRTH2', 'MODEM_S.LONGRANGE2.LRCHPWRTH2', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE2_LRCHPWRTH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE2_LRCHPWRTH3, self).__init__(register,
            'LRCHPWRTH3', 'MODEM_S.LONGRANGE2.LRCHPWRTH3', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE2_LRCHPWRTH4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE2_LRCHPWRTH4, self).__init__(register,
            'LRCHPWRTH4', 'MODEM_S.LONGRANGE2.LRCHPWRTH4', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE3_LRCHPWRTH5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE3_LRCHPWRTH5, self).__init__(register,
            'LRCHPWRTH5', 'MODEM_S.LONGRANGE3.LRCHPWRTH5', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE3_LRCHPWRTH6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE3_LRCHPWRTH6, self).__init__(register,
            'LRCHPWRTH6', 'MODEM_S.LONGRANGE3.LRCHPWRTH6', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE3_LRCHPWRTH7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE3_LRCHPWRTH7, self).__init__(register,
            'LRCHPWRTH7', 'MODEM_S.LONGRANGE3.LRCHPWRTH7', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE3_LRCHPWRTH8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE3_LRCHPWRTH8, self).__init__(register,
            'LRCHPWRTH8', 'MODEM_S.LONGRANGE3.LRCHPWRTH8', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE4_LRCHPWRTH9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE4_LRCHPWRTH9, self).__init__(register,
            'LRCHPWRTH9', 'MODEM_S.LONGRANGE4.LRCHPWRTH9', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE4_LRCHPWRTH10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE4_LRCHPWRTH10, self).__init__(register,
            'LRCHPWRTH10', 'MODEM_S.LONGRANGE4.LRCHPWRTH10', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE4_LRCHPWRSH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE4_LRCHPWRSH1, self).__init__(register,
            'LRCHPWRSH1', 'MODEM_S.LONGRANGE4.LRCHPWRSH1', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE4_LRCHPWRSH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE4_LRCHPWRSH2, self).__init__(register,
            'LRCHPWRSH2', 'MODEM_S.LONGRANGE4.LRCHPWRSH2', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE4_LRCHPWRSH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE4_LRCHPWRSH3, self).__init__(register,
            'LRCHPWRSH3', 'MODEM_S.LONGRANGE4.LRCHPWRSH3', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE4_LRCHPWRSH4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE4_LRCHPWRSH4, self).__init__(register,
            'LRCHPWRSH4', 'MODEM_S.LONGRANGE4.LRCHPWRSH4', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH5, self).__init__(register,
            'LRCHPWRSH5', 'MODEM_S.LONGRANGE5.LRCHPWRSH5', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH6, self).__init__(register,
            'LRCHPWRSH6', 'MODEM_S.LONGRANGE5.LRCHPWRSH6', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH7, self).__init__(register,
            'LRCHPWRSH7', 'MODEM_S.LONGRANGE5.LRCHPWRSH7', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH8, self).__init__(register,
            'LRCHPWRSH8', 'MODEM_S.LONGRANGE5.LRCHPWRSH8', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH9, self).__init__(register,
            'LRCHPWRSH9', 'MODEM_S.LONGRANGE5.LRCHPWRSH9', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH10, self).__init__(register,
            'LRCHPWRSH10', 'MODEM_S.LONGRANGE5.LRCHPWRSH10', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE5_LRCHPWRSH11, self).__init__(register,
            'LRCHPWRSH11', 'MODEM_S.LONGRANGE5.LRCHPWRSH11', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE6_LRCHPWRSPIKETH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE6_LRCHPWRSPIKETH, self).__init__(register,
            'LRCHPWRSPIKETH', 'MODEM_S.LONGRANGE6.LRCHPWRSPIKETH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE6_LRSPIKETHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE6_LRSPIKETHD, self).__init__(register,
            'LRSPIKETHD', 'MODEM_S.LONGRANGE6.LRSPIKETHD', 'read-write',
            u"",
            8, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE6_LRCHPWRTH11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE6_LRCHPWRTH11, self).__init__(register,
            'LRCHPWRTH11', 'MODEM_S.LONGRANGE6.LRCHPWRTH11', 'read-write',
            u"",
            20, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LONGRANGE6_LRCHPWRSH12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LONGRANGE6_LRCHPWRSH12, self).__init__(register,
            'LRCHPWRSH12', 'MODEM_S.LONGRANGE6.LRCHPWRSH12', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LRFRC_CI500(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LRFRC_CI500, self).__init__(register,
            'CI500', 'MODEM_S.LRFRC.CI500', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LRFRC_FRCACKTIMETHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LRFRC_FRCACKTIMETHD, self).__init__(register,
            'FRCACKTIMETHD', 'MODEM_S.LRFRC.FRCACKTIMETHD', 'read-write',
            u"",
            2, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_LRFRC_LRCORRMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_LRFRC_LRCORRMODE, self).__init__(register,
            'LRCORRMODE', 'MODEM_S.LRFRC.LRCORRMODE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHDYNAMICBBSSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHDYNAMICBBSSEN, self).__init__(register,
            'COHDYNAMICBBSSEN', 'MODEM_S.COH0.COHDYNAMICBBSSEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHDYNAMICSYNCTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHDYNAMICSYNCTHRESH, self).__init__(register,
            'COHDYNAMICSYNCTHRESH', 'MODEM_S.COH0.COHDYNAMICSYNCTHRESH', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHDYNAMICPRETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHDYNAMICPRETHRESH, self).__init__(register,
            'COHDYNAMICPRETHRESH', 'MODEM_S.COH0.COHDYNAMICPRETHRESH', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHCHPWRLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHCHPWRLOCK, self).__init__(register,
            'COHCHPWRLOCK', 'MODEM_S.COH0.COHCHPWRLOCK', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHCHPWRRESTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHCHPWRRESTART, self).__init__(register,
            'COHCHPWRRESTART', 'MODEM_S.COH0.COHCHPWRRESTART', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHDYNAMICPRETHRESHSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHDYNAMICPRETHRESHSEL, self).__init__(register,
            'COHDYNAMICPRETHRESHSEL', 'MODEM_S.COH0.COHDYNAMICPRETHRESHSEL', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHCHPWRTH0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHCHPWRTH0, self).__init__(register,
            'COHCHPWRTH0', 'MODEM_S.COH0.COHCHPWRTH0', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHCHPWRTH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHCHPWRTH1, self).__init__(register,
            'COHCHPWRTH1', 'MODEM_S.COH0.COHCHPWRTH1', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH0_COHCHPWRTH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH0_COHCHPWRTH2, self).__init__(register,
            'COHCHPWRTH2', 'MODEM_S.COH0.COHCHPWRTH2', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH1_SYNCTHRESH0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH1_SYNCTHRESH0, self).__init__(register,
            'SYNCTHRESH0', 'MODEM_S.COH1.SYNCTHRESH0', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH1_SYNCTHRESH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH1_SYNCTHRESH1, self).__init__(register,
            'SYNCTHRESH1', 'MODEM_S.COH1.SYNCTHRESH1', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH1_SYNCTHRESH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH1_SYNCTHRESH2, self).__init__(register,
            'SYNCTHRESH2', 'MODEM_S.COH1.SYNCTHRESH2', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH1_SYNCTHRESH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH1_SYNCTHRESH3, self).__init__(register,
            'SYNCTHRESH3', 'MODEM_S.COH1.SYNCTHRESH3', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH2_SYNCTHRESHDELTA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH2_SYNCTHRESHDELTA0, self).__init__(register,
            'SYNCTHRESHDELTA0', 'MODEM_S.COH2.SYNCTHRESHDELTA0', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH2_SYNCTHRESHDELTA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH2_SYNCTHRESHDELTA1, self).__init__(register,
            'SYNCTHRESHDELTA1', 'MODEM_S.COH2.SYNCTHRESHDELTA1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH2_SYNCTHRESHDELTA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH2_SYNCTHRESHDELTA2, self).__init__(register,
            'SYNCTHRESHDELTA2', 'MODEM_S.COH2.SYNCTHRESHDELTA2', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH2_SYNCTHRESHDELTA3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH2_SYNCTHRESHDELTA3, self).__init__(register,
            'SYNCTHRESHDELTA3', 'MODEM_S.COH2.SYNCTHRESHDELTA3', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH2_DSAPEAKCHPWRTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH2_DSAPEAKCHPWRTH, self).__init__(register,
            'DSAPEAKCHPWRTH', 'MODEM_S.COH2.DSAPEAKCHPWRTH', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH2_FIXEDCDTHFORIIR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH2_FIXEDCDTHFORIIR, self).__init__(register,
            'FIXEDCDTHFORIIR', 'MODEM_S.COH2.FIXEDCDTHFORIIR', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_COHDSAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_COHDSAEN, self).__init__(register,
            'COHDSAEN', 'MODEM_S.COH3.COHDSAEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_COHDSAADDWNDSIZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_COHDSAADDWNDSIZE, self).__init__(register,
            'COHDSAADDWNDSIZE', 'MODEM_S.COH3.COHDSAADDWNDSIZE', 'read-write',
            u"",
            1, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_CDSS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_CDSS, self).__init__(register,
            'CDSS', 'MODEM_S.COH3.CDSS', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_DSAPEAKCHKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_DSAPEAKCHKEN, self).__init__(register,
            'DSAPEAKCHKEN', 'MODEM_S.COH3.DSAPEAKCHKEN', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_DSAPEAKINDLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_DSAPEAKINDLEN, self).__init__(register,
            'DSAPEAKINDLEN', 'MODEM_S.COH3.DSAPEAKINDLEN', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_DSAPEAKCHPWREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_DSAPEAKCHPWREN, self).__init__(register,
            'DSAPEAKCHPWREN', 'MODEM_S.COH3.DSAPEAKCHPWREN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_LOGICBASEDCOHDEMODGATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_LOGICBASEDCOHDEMODGATE, self).__init__(register,
            'LOGICBASEDCOHDEMODGATE', 'MODEM_S.COH3.LOGICBASEDCOHDEMODGATE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_DYNIIRCOEFOPTION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_DYNIIRCOEFOPTION, self).__init__(register,
            'DYNIIRCOEFOPTION', 'MODEM_S.COH3.DYNIIRCOEFOPTION', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_ONEPEAKQUALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_ONEPEAKQUALEN, self).__init__(register,
            'ONEPEAKQUALEN', 'MODEM_S.COH3.ONEPEAKQUALEN', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_PEAKCHKTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_PEAKCHKTIMOUT, self).__init__(register,
            'PEAKCHKTIMOUT', 'MODEM_S.COH3.PEAKCHKTIMOUT', 'read-write',
            u"",
            23, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_COHDSADETDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_COHDSADETDIS, self).__init__(register,
            'COHDSADETDIS', 'MODEM_S.COH3.COHDSADETDIS', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COH3_COHDSACMPLX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COH3_COHDSACMPLX, self).__init__(register,
            'COHDSACMPLX', 'MODEM_S.COH3.COHDSACMPLX', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CMD_PRESTOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CMD_PRESTOP, self).__init__(register,
            'PRESTOP', 'MODEM_S.CMD.PRESTOP', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CMD_CHPWRACCUCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CMD_CHPWRACCUCLR, self).__init__(register,
            'CHPWRACCUCLR', 'MODEM_S.CMD.CHPWRACCUCLR', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CMD_AFCTXLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CMD_AFCTXLOCK, self).__init__(register,
            'AFCTXLOCK', 'MODEM_S.CMD.AFCTXLOCK', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CMD_AFCTXCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CMD_AFCTXCLEAR, self).__init__(register,
            'AFCTXCLEAR', 'MODEM_S.CMD.AFCTXCLEAR', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CMD_AFCRXCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CMD_AFCRXCLEAR, self).__init__(register,
            'AFCRXCLEAR', 'MODEM_S.CMD.AFCRXCLEAR', 'write-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CMD_HOPPINGSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CMD_HOPPINGSTART, self).__init__(register,
            'HOPPINGSTART', 'MODEM_S.CMD.HOPPINGSTART', 'write-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCPROPERTIES_STATICSYNCTHRESHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCPROPERTIES_STATICSYNCTHRESHEN, self).__init__(register,
            'STATICSYNCTHRESHEN', 'MODEM_S.SYNCPROPERTIES.STATICSYNCTHRESHEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCPROPERTIES_STATICSYNCTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCPROPERTIES_STATICSYNCTHRESH, self).__init__(register,
            'STATICSYNCTHRESH', 'MODEM_S.SYNCPROPERTIES.STATICSYNCTHRESH', 'read-write',
            u"",
            9, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGIGAINCTRL_DIGIGAINEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGIGAINCTRL_DIGIGAINEN, self).__init__(register,
            'DIGIGAINEN', 'MODEM_S.DIGIGAINCTRL.DIGIGAINEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGIGAINCTRL_DIGIGAINSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGIGAINCTRL_DIGIGAINSEL, self).__init__(register,
            'DIGIGAINSEL', 'MODEM_S.DIGIGAINCTRL.DIGIGAINSEL', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGIGAINCTRL_DIGIGAINDOUBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGIGAINCTRL_DIGIGAINDOUBLE, self).__init__(register,
            'DIGIGAINDOUBLE', 'MODEM_S.DIGIGAINCTRL.DIGIGAINDOUBLE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGIGAINCTRL_DIGIGAINHALF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGIGAINCTRL_DIGIGAINHALF, self).__init__(register,
            'DIGIGAINHALF', 'MODEM_S.DIGIGAINCTRL.DIGIGAINHALF', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DIGIGAINCTRL_DEC0GAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DIGIGAINCTRL_DEC0GAIN, self).__init__(register,
            'DEC0GAIN', 'MODEM_S.DIGIGAINCTRL.DEC0GAIN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_POSTPONESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_POSTPONESEL, self).__init__(register,
            'POSTPONESEL', 'MODEM_S.PRSCTRL.POSTPONESEL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_ADVANCESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_ADVANCESEL, self).__init__(register,
            'ADVANCESEL', 'MODEM_S.PRSCTRL.ADVANCESEL', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_NEWWNDSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_NEWWNDSEL, self).__init__(register,
            'NEWWNDSEL', 'MODEM_S.PRSCTRL.NEWWNDSEL', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_WEAKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_WEAKSEL, self).__init__(register,
            'WEAKSEL', 'MODEM_S.PRSCTRL.WEAKSEL', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_SYNCSENTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_SYNCSENTSEL, self).__init__(register,
            'SYNCSENTSEL', 'MODEM_S.PRSCTRL.SYNCSENTSEL', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_PRESENTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_PRESENTSEL, self).__init__(register,
            'PRESENTSEL', 'MODEM_S.PRSCTRL.PRESENTSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_LOWCORRSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_LOWCORRSEL, self).__init__(register,
            'LOWCORRSEL', 'MODEM_S.PRSCTRL.LOWCORRSEL', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_ANT0SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_ANT0SEL, self).__init__(register,
            'ANT0SEL', 'MODEM_S.PRSCTRL.ANT0SEL', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_ANT1SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_ANT1SEL, self).__init__(register,
            'ANT1SEL', 'MODEM_S.PRSCTRL.ANT1SEL', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PRSCTRL_IFADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PRSCTRL_IFADCCLKSEL, self).__init__(register,
            'IFADCCLKSEL', 'MODEM_S.PRSCTRL.IFADCCLKSEL', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PADEBUG_MANPACLKAMPCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PADEBUG_MANPACLKAMPCTRL, self).__init__(register,
            'MANPACLKAMPCTRL', 'MODEM_S.PADEBUG.MANPACLKAMPCTRL', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PADEBUG_ENMANPACLKAMPCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PADEBUG_ENMANPACLKAMPCTRL, self).__init__(register,
            'ENMANPACLKAMPCTRL', 'MODEM_S.PADEBUG.ENMANPACLKAMPCTRL', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PADEBUG_ENMANPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PADEBUG_ENMANPAPOWER, self).__init__(register,
            'ENMANPAPOWER', 'MODEM_S.PADEBUG.ENMANPAPOWER', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PADEBUG_ENMANPASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PADEBUG_ENMANPASELSLICE, self).__init__(register,
            'ENMANPASELSLICE', 'MODEM_S.PADEBUG.ENMANPASELSLICE', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_MINCOSTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_MINCOSTTHD, self).__init__(register,
            'MINCOSTTHD', 'MODEM_S.REALTIMCFE.MINCOSTTHD', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_RTSCHWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_RTSCHWIN, self).__init__(register,
            'RTSCHWIN', 'MODEM_S.REALTIMCFE.RTSCHWIN', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_RTSCHMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_RTSCHMODE, self).__init__(register,
            'RTSCHMODE', 'MODEM_S.REALTIMCFE.RTSCHMODE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_TRACKINGWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_TRACKINGWIN, self).__init__(register,
            'TRACKINGWIN', 'MODEM_S.REALTIMCFE.TRACKINGWIN', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_SYNCACQWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_SYNCACQWIN, self).__init__(register,
            'SYNCACQWIN', 'MODEM_S.REALTIMCFE.SYNCACQWIN', 'read-write',
            u"",
            18, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_EXTENSCHBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_EXTENSCHBYP, self).__init__(register,
            'EXTENSCHBYP', 'MODEM_S.REALTIMCFE.EXTENSCHBYP', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_SINEWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_SINEWEN, self).__init__(register,
            'SINEWEN', 'MODEM_S.REALTIMCFE.SINEWEN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_VTAFCFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_VTAFCFRAME, self).__init__(register,
            'VTAFCFRAME', 'MODEM_S.REALTIMCFE.VTAFCFRAME', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_REALTIMCFE_RTCFEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_REALTIMCFE_RTCFEEN, self).__init__(register,
            'RTCFEEN', 'MODEM_S.REALTIMCFE.RTCFEEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ETSCTRL_ETSLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ETSCTRL_ETSLOC, self).__init__(register,
            'ETSLOC', 'MODEM_S.ETSCTRL.ETSLOC', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ETSCTRL_CAPSIGONPRS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ETSCTRL_CAPSIGONPRS, self).__init__(register,
            'CAPSIGONPRS', 'MODEM_S.ETSCTRL.CAPSIGONPRS', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ETSCTRL_CAPTRIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ETSCTRL_CAPTRIG, self).__init__(register,
            'CAPTRIG', 'MODEM_S.ETSCTRL.CAPTRIG', 'read-write',
            u"",
            12, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ETSTIM_ETSTIMVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ETSTIM_ETSTIMVAL, self).__init__(register,
            'ETSTIMVAL', 'MODEM_S.ETSTIM.ETSTIMVAL', 'read-write',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ETSTIM_ETSCOUNTEREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ETSTIM_ETSCOUNTEREN, self).__init__(register,
            'ETSCOUNTEREN', 'MODEM_S.ETSTIM.ETSCOUNTEREN', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWCTRL_ANTDFLTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWCTRL_ANTDFLTSEL, self).__init__(register,
            'ANTDFLTSEL', 'MODEM_S.ANTSWCTRL.ANTDFLTSEL', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWCTRL_ANTCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWCTRL_ANTCOUNT, self).__init__(register,
            'ANTCOUNT', 'MODEM_S.ANTSWCTRL.ANTCOUNT', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWCTRL_ANTSWTYPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWCTRL_ANTSWTYPE, self).__init__(register,
            'ANTSWTYPE', 'MODEM_S.ANTSWCTRL.ANTSWTYPE', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWCTRL_ANTSWRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWCTRL_ANTSWRST, self).__init__(register,
            'ANTSWRST', 'MODEM_S.ANTSWCTRL.ANTSWRST', 'write-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWCTRL_CFGANTPATTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWCTRL_CFGANTPATTEN, self).__init__(register,
            'CFGANTPATTEN', 'MODEM_S.ANTSWCTRL.CFGANTPATTEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWCTRL_ANTSWENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWCTRL_ANTSWENABLE, self).__init__(register,
            'ANTSWENABLE', 'MODEM_S.ANTSWCTRL.ANTSWENABLE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWCTRL_EXTDSTOPPULSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWCTRL_EXTDSTOPPULSECNT, self).__init__(register,
            'EXTDSTOPPULSECNT', 'MODEM_S.ANTSWCTRL.EXTDSTOPPULSECNT', 'read-write',
            u"",
            17, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWCTRL1_TIMEPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWCTRL1_TIMEPERIOD, self).__init__(register,
            'TIMEPERIOD', 'MODEM_S.ANTSWCTRL1.TIMEPERIOD', 'read-write',
            u"",
            0, 24)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWSTART_ANTSWSTARTTIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWSTART_ANTSWSTARTTIM, self).__init__(register,
            'ANTSWSTARTTIM', 'MODEM_S.ANTSWSTART.ANTSWSTARTTIM', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTSWEND_ANTSWENDTIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTSWEND_ANTSWENDTIM, self).__init__(register,
            'ANTSWENDTIM', 'MODEM_S.ANTSWEND.ANTSWENDTIM', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECPMPATT_PMEXPECTPATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECPMPATT_PMEXPECTPATT, self).__init__(register,
            'PMEXPECTPATT', 'MODEM_S.TRECPMPATT.PMEXPECTPATT', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECPMDET_PMACQUINGWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECPMDET_PMACQUINGWIN, self).__init__(register,
            'PMACQUINGWIN', 'MODEM_S.TRECPMDET.PMACQUINGWIN', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECPMDET_PMCOSTVALTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECPMDET_PMCOSTVALTHD, self).__init__(register,
            'PMCOSTVALTHD', 'MODEM_S.TRECPMDET.PMCOSTVALTHD', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECPMDET_PMTIMEOUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECPMDET_PMTIMEOUTSEL, self).__init__(register,
            'PMTIMEOUTSEL', 'MODEM_S.TRECPMDET.PMTIMEOUTSEL', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECPMDET_PHSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECPMDET_PHSCALE, self).__init__(register,
            'PHSCALE', 'MODEM_S.TRECPMDET.PHSCALE', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECPMDET_PMMINCOSTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECPMDET_PMMINCOSTTHD, self).__init__(register,
            'PMMINCOSTTHD', 'MODEM_S.TRECPMDET.PMMINCOSTTHD', 'read-write',
            u"",
            14, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECPMDET_COSTHYST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECPMDET_COSTHYST, self).__init__(register,
            'COSTHYST', 'MODEM_S.TRECPMDET.COSTHYST', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECPMDET_PREAMSCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECPMDET_PREAMSCH, self).__init__(register,
            'PREAMSCH', 'MODEM_S.TRECPMDET.PREAMSCH', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECSCFG_TRECSOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECSCFG_TRECSOSR, self).__init__(register,
            'TRECSOSR', 'MODEM_S.TRECSCFG.TRECSOSR', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECSCFG_DTIMLOSSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECSCFG_DTIMLOSSTHD, self).__init__(register,
            'DTIMLOSSTHD', 'MODEM_S.TRECSCFG.DTIMLOSSTHD', 'read-write',
            u"",
            3, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECSCFG_DTIMLOSSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECSCFG_DTIMLOSSEN, self).__init__(register,
            'DTIMLOSSEN', 'MODEM_S.TRECSCFG.DTIMLOSSEN', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECSCFG_PMOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECSCFG_PMOFFSET, self).__init__(register,
            'PMOFFSET', 'MODEM_S.TRECSCFG.PMOFFSET', 'read-write',
            u"",
            16, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECSCFG_SDSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECSCFG_SDSCALE, self).__init__(register,
            'SDSCALE', 'MODEM_S.TRECSCFG.SDSCALE', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TRECSCFG_SOFTD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TRECSCFG_SOFTD, self).__init__(register,
            'SOFTD', 'MODEM_S.TRECSCFG.SOFTD', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CFGANTPATT_CFGANTPATTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CFGANTPATT_CFGANTPATTVAL, self).__init__(register,
            'CFGANTPATTVAL', 'MODEM_S.CFGANTPATT.CFGANTPATTVAL', 'read-write',
            u"",
            0, 30)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_COCURRMODE_CONCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_COCURRMODE_CONCURRENT, self).__init__(register,
            'CONCURRENT', 'MODEM_S.COCURRMODE.CONCURRENT', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE00_SET0COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE00_SET0COEFF0, self).__init__(register,
            'SET0COEFF0', 'MODEM_S.CHFCOE00.SET0COEFF0', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE00_SET0COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE00_SET0COEFF1, self).__init__(register,
            'SET0COEFF1', 'MODEM_S.CHFCOE00.SET0COEFF1', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE00_SET0COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE00_SET0COEFF2, self).__init__(register,
            'SET0COEFF2', 'MODEM_S.CHFCOE00.SET0COEFF2', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE01_SET0COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE01_SET0COEFF3, self).__init__(register,
            'SET0COEFF3', 'MODEM_S.CHFCOE01.SET0COEFF3', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE01_SET0COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE01_SET0COEFF4, self).__init__(register,
            'SET0COEFF4', 'MODEM_S.CHFCOE01.SET0COEFF4', 'read-write',
            u"",
            11, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE02_SET0COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE02_SET0COEFF5, self).__init__(register,
            'SET0COEFF5', 'MODEM_S.CHFCOE02.SET0COEFF5', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE02_SET0COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE02_SET0COEFF6, self).__init__(register,
            'SET0COEFF6', 'MODEM_S.CHFCOE02.SET0COEFF6', 'read-write',
            u"",
            11, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE03_SET0COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE03_SET0COEFF7, self).__init__(register,
            'SET0COEFF7', 'MODEM_S.CHFCOE03.SET0COEFF7', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE03_SET0COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE03_SET0COEFF8, self).__init__(register,
            'SET0COEFF8', 'MODEM_S.CHFCOE03.SET0COEFF8', 'read-write',
            u"",
            12, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE04_SET0COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE04_SET0COEFF9, self).__init__(register,
            'SET0COEFF9', 'MODEM_S.CHFCOE04.SET0COEFF9', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE04_SET0COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE04_SET0COEFF10, self).__init__(register,
            'SET0COEFF10', 'MODEM_S.CHFCOE04.SET0COEFF10', 'read-write',
            u"",
            14, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE05_SET0COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE05_SET0COEFF11, self).__init__(register,
            'SET0COEFF11', 'MODEM_S.CHFCOE05.SET0COEFF11', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE05_SET0COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE05_SET0COEFF12, self).__init__(register,
            'SET0COEFF12', 'MODEM_S.CHFCOE05.SET0COEFF12', 'read-write',
            u"",
            14, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE06_SET0COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE06_SET0COEFF13, self).__init__(register,
            'SET0COEFF13', 'MODEM_S.CHFCOE06.SET0COEFF13', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE06_SET0COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE06_SET0COEFF14, self).__init__(register,
            'SET0COEFF14', 'MODEM_S.CHFCOE06.SET0COEFF14', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE10_SET1COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE10_SET1COEFF0, self).__init__(register,
            'SET1COEFF0', 'MODEM_S.CHFCOE10.SET1COEFF0', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE10_SET1COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE10_SET1COEFF1, self).__init__(register,
            'SET1COEFF1', 'MODEM_S.CHFCOE10.SET1COEFF1', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE10_SET1COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE10_SET1COEFF2, self).__init__(register,
            'SET1COEFF2', 'MODEM_S.CHFCOE10.SET1COEFF2', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE11_SET1COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE11_SET1COEFF3, self).__init__(register,
            'SET1COEFF3', 'MODEM_S.CHFCOE11.SET1COEFF3', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE11_SET1COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE11_SET1COEFF4, self).__init__(register,
            'SET1COEFF4', 'MODEM_S.CHFCOE11.SET1COEFF4', 'read-write',
            u"",
            11, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE12_SET1COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE12_SET1COEFF5, self).__init__(register,
            'SET1COEFF5', 'MODEM_S.CHFCOE12.SET1COEFF5', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE12_SET1COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE12_SET1COEFF6, self).__init__(register,
            'SET1COEFF6', 'MODEM_S.CHFCOE12.SET1COEFF6', 'read-write',
            u"",
            11, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE13_SET1COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE13_SET1COEFF7, self).__init__(register,
            'SET1COEFF7', 'MODEM_S.CHFCOE13.SET1COEFF7', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE13_SET1COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE13_SET1COEFF8, self).__init__(register,
            'SET1COEFF8', 'MODEM_S.CHFCOE13.SET1COEFF8', 'read-write',
            u"",
            12, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE14_SET1COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE14_SET1COEFF9, self).__init__(register,
            'SET1COEFF9', 'MODEM_S.CHFCOE14.SET1COEFF9', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE14_SET1COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE14_SET1COEFF10, self).__init__(register,
            'SET1COEFF10', 'MODEM_S.CHFCOE14.SET1COEFF10', 'read-write',
            u"",
            14, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE15_SET1COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE15_SET1COEFF11, self).__init__(register,
            'SET1COEFF11', 'MODEM_S.CHFCOE15.SET1COEFF11', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE15_SET1COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE15_SET1COEFF12, self).__init__(register,
            'SET1COEFF12', 'MODEM_S.CHFCOE15.SET1COEFF12', 'read-write',
            u"",
            14, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE16_SET1COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE16_SET1COEFF13, self).__init__(register,
            'SET1COEFF13', 'MODEM_S.CHFCOE16.SET1COEFF13', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCOE16_SET1COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCOE16_SET1COEFF14, self).__init__(register,
            'SET1COEFF14', 'MODEM_S.CHFCOE16.SET1COEFF14', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCTRL_FWSWCOEFFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCTRL_FWSWCOEFFEN, self).__init__(register,
            'FWSWCOEFFEN', 'MODEM_S.CHFCTRL.FWSWCOEFFEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCTRL_FWSELCOEFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCTRL_FWSELCOEFF, self).__init__(register,
            'FWSELCOEFF', 'MODEM_S.CHFCTRL.FWSELCOEFF', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCTRL_CHFSWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCTRL_CHFSWSEL, self).__init__(register,
            'CHFSWSEL', 'MODEM_S.CHFCTRL.CHFSWSEL', 'read-write',
            u"",
            28, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFCTRL_SWCOEFFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFCTRL_SWCOEFFEN, self).__init__(register,
            'SWCOEFFEN', 'MODEM_S.CHFCTRL.SWCOEFFEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFLATENCYCTRL_CHFLATENCY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFLATENCYCTRL_CHFLATENCY, self).__init__(register,
            'CHFLATENCY', 'MODEM_S.CHFLATENCYCTRL.CHFLATENCY', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FRMSCHTIME_FRMSCHTIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FRMSCHTIME_FRMSCHTIME, self).__init__(register,
            'FRMSCHTIME', 'MODEM_S.FRMSCHTIME.FRMSCHTIME', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FRMSCHTIME_PMRSTSYCNEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FRMSCHTIME_PMRSTSYCNEN, self).__init__(register,
            'PMRSTSYCNEN', 'MODEM_S.FRMSCHTIME.PMRSTSYCNEN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FRMSCHTIME_DSARSTSYCNEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FRMSCHTIME_DSARSTSYCNEN, self).__init__(register,
            'DSARSTSYCNEN', 'MODEM_S.FRMSCHTIME.DSARSTSYCNEN', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_FRMSCHTIME_PMENDSCHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_FRMSCHTIME_PMENDSCHEN, self).__init__(register,
            'PMENDSCHEN', 'MODEM_S.FRMSCHTIME.PMENDSCHEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PREFILTCOEFF_PREFILTCOEFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PREFILTCOEFF_PREFILTCOEFF, self).__init__(register,
            'PREFILTCOEFF', 'MODEM_S.PREFILTCOEFF.PREFILTCOEFF', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXRESTART_RXRESTARTUPONMARSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXRESTART_RXRESTARTUPONMARSSI, self).__init__(register,
            'RXRESTARTUPONMARSSI', 'MODEM_S.RXRESTART.RXRESTARTUPONMARSSI', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXRESTART_RXRESTARTMATHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXRESTART_RXRESTARTMATHRESHOLD, self).__init__(register,
            'RXRESTARTMATHRESHOLD', 'MODEM_S.RXRESTART.RXRESTARTMATHRESHOLD', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXRESTART_RXRESTARTMALATCHSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXRESTART_RXRESTARTMALATCHSEL, self).__init__(register,
            'RXRESTARTMALATCHSEL', 'MODEM_S.RXRESTART.RXRESTARTMALATCHSEL', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXRESTART_RXRESTARTMACOMPENSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXRESTART_RXRESTARTMACOMPENSEL, self).__init__(register,
            'RXRESTARTMACOMPENSEL', 'MODEM_S.RXRESTART.RXRESTARTMACOMPENSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXRESTART_RXRESTARTMATAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXRESTART_RXRESTARTMATAP, self).__init__(register,
            'RXRESTARTMATAP', 'MODEM_S.RXRESTART.RXRESTARTMATAP', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXRESTART_RXRESTARTB4PREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXRESTART_RXRESTARTB4PREDET, self).__init__(register,
            'RXRESTARTB4PREDET', 'MODEM_S.RXRESTART.RXRESTARTB4PREDET', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXRESTART_ANTSWRSTFLTTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXRESTART_ANTSWRSTFLTTDIS, self).__init__(register,
            'ANTSWRSTFLTTDIS', 'MODEM_S.RXRESTART.ANTSWRSTFLTTDIS', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_RXRESTART_FLTRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_RXRESTART_FLTRSTEN, self).__init__(register,
            'FLTRSTEN', 'MODEM_S.RXRESTART.FLTRSTEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SQ_SQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SQ_SQEN, self).__init__(register,
            'SQEN', 'MODEM_S.SQ.SQEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SQ_SQSWRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SQ_SQSWRST, self).__init__(register,
            'SQSWRST', 'MODEM_S.SQ.SQSWRST', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SQ_SQTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SQ_SQTIMOUT, self).__init__(register,
            'SQTIMOUT', 'MODEM_S.SQ.SQTIMOUT', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SQEXT_SQSTG2TIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SQEXT_SQSTG2TIMOUT, self).__init__(register,
            'SQSTG2TIMOUT', 'MODEM_S.SQEXT.SQSTG2TIMOUT', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SQEXT_SQSTG3TIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SQEXT_SQSTG3TIMOUT, self).__init__(register,
            'SQSTG3TIMOUT', 'MODEM_S.SQEXT.SQSTG3TIMOUT', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SQI_SQISELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SQI_SQISELECT, self).__init__(register,
            'SQISELECT', 'MODEM_S.SQI.SQISELECT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SQI_CHIPERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SQI_CHIPERROR, self).__init__(register,
            'CHIPERROR', 'MODEM_S.SQI.CHIPERROR', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTDIVCTRL_ADPRETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTDIVCTRL_ADPRETHRESH, self).__init__(register,
            'ADPRETHRESH', 'MODEM_S.ANTDIVCTRL.ADPRETHRESH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTDIVCTRL_ENADPRETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTDIVCTRL_ENADPRETHRESH, self).__init__(register,
            'ENADPRETHRESH', 'MODEM_S.ANTDIVCTRL.ENADPRETHRESH', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTDIVCTRL_ANTDIVDISCCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTDIVCTRL_ANTDIVDISCCA, self).__init__(register,
            'ANTDIVDISCCA', 'MODEM_S.ANTDIVCTRL.ANTDIVDISCCA', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTDIVCTRL_ANTDIVSELCCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTDIVCTRL_ANTDIVSELCCA, self).__init__(register,
            'ANTDIVSELCCA', 'MODEM_S.ANTDIVCTRL.ANTDIVSELCCA', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTDIVFW_FWSELANT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTDIVFW_FWSELANT, self).__init__(register,
            'FWSELANT', 'MODEM_S.ANTDIVFW.FWSELANT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTDIVFW_FWANTSWCMD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTDIVFW_FWANTSWCMD, self).__init__(register,
            'FWANTSWCMD', 'MODEM_S.ANTDIVFW.FWANTSWCMD', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ANTDIVFW_FWANTDIVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ANTDIVFW_FWANTDIVEN, self).__init__(register,
            'FWANTDIVEN', 'MODEM_S.ANTDIVFW.FWANTDIVEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODANTDIV_ANTWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODANTDIV_ANTWAIT, self).__init__(register,
            'ANTWAIT', 'MODEM_S.PHDMODANTDIV.ANTWAIT', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODANTDIV_SKIPRSSITHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODANTDIV_SKIPRSSITHD, self).__init__(register,
            'SKIPRSSITHD', 'MODEM_S.PHDMODANTDIV.SKIPRSSITHD', 'read-write',
            u"",
            5, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODANTDIV_SKIPCORRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODANTDIV_SKIPCORRTHD, self).__init__(register,
            'SKIPCORRTHD', 'MODEM_S.PHDMODANTDIV.SKIPCORRTHD', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODANTDIV_SKIP2ANT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODANTDIV_SKIP2ANT, self).__init__(register,
            'SKIP2ANT', 'MODEM_S.PHDMODANTDIV.SKIP2ANT', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHANTDECSION_CORRANDDIVTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHANTDECSION_CORRANDDIVTHD, self).__init__(register,
            'CORRANDDIVTHD', 'MODEM_S.PHANTDECSION.CORRANDDIVTHD', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHANTDECSION_RSSIANDDIVTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHANTDECSION_RSSIANDDIVTHD, self).__init__(register,
            'RSSIANDDIVTHD', 'MODEM_S.PHANTDECSION.RSSIANDDIVTHD', 'read-write',
            u"",
            10, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHANTDECSION_RSSICORR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHANTDECSION_RSSICORR0, self).__init__(register,
            'RSSICORR0', 'MODEM_S.PHANTDECSION.RSSICORR0', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHANTDECSION_RSSICORR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHANTDECSION_RSSICORR1, self).__init__(register,
            'RSSICORR1', 'MODEM_S.PHANTDECSION.RSSICORR1', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHANTDECSION_RSSICORR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHANTDECSION_RSSICORR2, self).__init__(register,
            'RSSICORR2', 'MODEM_S.PHANTDECSION.RSSICORR2', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHANTDECSION_RSSICORR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHANTDECSION_RSSICORR3, self).__init__(register,
            'RSSICORR3', 'MODEM_S.PHANTDECSION.RSSICORR3', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_PMDETTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_PMDETTHD, self).__init__(register,
            'PMDETTHD', 'MODEM_S.PHDMODCTRL.PMDETTHD', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_PMTIMLOSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_PMTIMLOSTHD, self).__init__(register,
            'PMTIMLOSTHD', 'MODEM_S.PHDMODCTRL.PMTIMLOSTHD', 'read-write',
            u"",
            5, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_PMTIMLOSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_PMTIMLOSEN, self).__init__(register,
            'PMTIMLOSEN', 'MODEM_S.PHDMODCTRL.PMTIMLOSEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_RSSIFLTBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_RSSIFLTBYP, self).__init__(register,
            'RSSIFLTBYP', 'MODEM_S.PHDMODCTRL.RSSIFLTBYP', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_PMDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_PMDETEN, self).__init__(register,
            'PMDETEN', 'MODEM_S.PHDMODCTRL.PMDETEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_REMODOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_REMODOSR, self).__init__(register,
            'REMODOSR', 'MODEM_S.PHDMODCTRL.REMODOSR', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_BCRTRECSCONC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_BCRTRECSCONC, self).__init__(register,
            'BCRTRECSCONC', 'MODEM_S.PHDMODCTRL.BCRTRECSCONC', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_REMODDWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_REMODDWN, self).__init__(register,
            'REMODDWN', 'MODEM_S.PHDMODCTRL.REMODDWN', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_REMODOUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_REMODOUTSEL, self).__init__(register,
            'REMODOUTSEL', 'MODEM_S.PHDMODCTRL.REMODOUTSEL', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_REMODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_REMODEN, self).__init__(register,
            'REMODEN', 'MODEM_S.PHDMODCTRL.REMODEN', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_BCRDETECTOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_BCRDETECTOR, self).__init__(register,
            'BCRDETECTOR', 'MODEM_S.PHDMODCTRL.BCRDETECTOR', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_BCRLEGACYCONC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_BCRLEGACYCONC, self).__init__(register,
            'BCRLEGACYCONC', 'MODEM_S.PHDMODCTRL.BCRLEGACYCONC', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_PHDMODCTRL_FASTHOPPINGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_PHDMODCTRL_FASTHOPPINGEN, self).__init__(register,
            'FASTHOPPINGEN', 'MODEM_S.PHDMODCTRL.FASTHOPPINGEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICORR_CORRTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICORR_CORRTHRESH, self).__init__(register,
            'CORRTHRESH', 'MODEM_S.SICORR.CORRTHRESH', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICORR_CORRTHRESHLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICORR_CORRTHRESHLOW, self).__init__(register,
            'CORRTHRESHLOW', 'MODEM_S.SICORR.CORRTHRESHLOW', 'read-write',
            u"",
            9, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICORR_CORRTHRESHUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICORR_CORRTHRESHUP, self).__init__(register,
            'CORRTHRESHUP', 'MODEM_S.SICORR.CORRTHRESHUP', 'read-write',
            u"",
            16, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICORR_CORRTHRESH2SYMB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICORR_CORRTHRESH2SYMB, self).__init__(register,
            'CORRTHRESH2SYMB', 'MODEM_S.SICORR.CORRTHRESH2SYMB', 'read-write',
            u"",
            23, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL0_SIMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL0_SIMODE, self).__init__(register,
            'SIMODE', 'MODEM_S.SICTRL0.SIMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL0_NOISETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL0_NOISETHRESH, self).__init__(register,
            'NOISETHRESH', 'MODEM_S.SICTRL0.NOISETHRESH', 'read-write',
            u"",
            2, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL0_PEAKNUMTHRESHLW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL0_PEAKNUMTHRESHLW, self).__init__(register,
            'PEAKNUMTHRESHLW', 'MODEM_S.SICTRL0.PEAKNUMTHRESHLW', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL0_SWPEAKNUMADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL0_SWPEAKNUMADJ, self).__init__(register,
            'SWPEAKNUMADJ', 'MODEM_S.SICTRL0.SWPEAKNUMADJ', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL0_NOISETHRESHADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL0_NOISETHRESHADJ, self).__init__(register,
            'NOISETHRESHADJ', 'MODEM_S.SICTRL0.NOISETHRESHADJ', 'read-write',
            u"",
            17, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL0_FREQNOMINAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL0_FREQNOMINAL, self).__init__(register,
            'FREQNOMINAL', 'MODEM_S.SICTRL0.FREQNOMINAL', 'read-write',
            u"",
            23, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL0_NDFOCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL0_NDFOCAL, self).__init__(register,
            'NDFOCAL', 'MODEM_S.SICTRL0.NDFOCAL', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_SUPERCHIPTOLERANCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_SUPERCHIPTOLERANCE, self).__init__(register,
            'SUPERCHIPTOLERANCE', 'MODEM_S.SICTRL1.SUPERCHIPTOLERANCE', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_SMALLSAMPLETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_SMALLSAMPLETHRESH, self).__init__(register,
            'SMALLSAMPLETHRESH', 'MODEM_S.SICTRL1.SMALLSAMPLETHRESH', 'read-write',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_PEAKNUMP2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_PEAKNUMP2ADJ, self).__init__(register,
            'PEAKNUMP2ADJ', 'MODEM_S.SICTRL1.PEAKNUMP2ADJ', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_FASTMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_FASTMODE, self).__init__(register,
            'FASTMODE', 'MODEM_S.SICTRL1.FASTMODE', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_TWOSYMBEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_TWOSYMBEN, self).__init__(register,
            'TWOSYMBEN', 'MODEM_S.SICTRL1.TWOSYMBEN', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_ZCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_ZCEN, self).__init__(register,
            'ZCEN', 'MODEM_S.SICTRL1.ZCEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_ZCSAMPLETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_ZCSAMPLETHRESH, self).__init__(register,
            'ZCSAMPLETHRESH', 'MODEM_S.SICTRL1.ZCSAMPLETHRESH', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_SOFTCLIPBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_SOFTCLIPBYPASS, self).__init__(register,
            'SOFTCLIPBYPASS', 'MODEM_S.SICTRL1.SOFTCLIPBYPASS', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL1_SOFTCLIPTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL1_SOFTCLIPTHRESH, self).__init__(register,
            'SOFTCLIPTHRESH', 'MODEM_S.SICTRL1.SOFTCLIPTHRESH', 'read-write',
            u"",
            22, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_SISTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_SISTATE, self).__init__(register,
            'SISTATE', 'MODEM_S.SISTATUS.SISTATE', 'read-only',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_NOISE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_NOISE, self).__init__(register,
            'NOISE', 'MODEM_S.SISTATUS.NOISE', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_LWPEAKCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_LWPEAKCOUNT, self).__init__(register,
            'LWPEAKCOUNT', 'MODEM_S.SISTATUS.LWPEAKCOUNT', 'read-only',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_NARROWCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_NARROWCOUNT, self).__init__(register,
            'NARROWCOUNT', 'MODEM_S.SISTATUS.NARROWCOUNT', 'read-only',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_TIMELOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_TIMELOCK, self).__init__(register,
            'TIMELOCK', 'MODEM_S.SISTATUS.TIMELOCK', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_SUPERCHIPFAIL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_SUPERCHIPFAIL, self).__init__(register,
            'SUPERCHIPFAIL', 'MODEM_S.SISTATUS.SUPERCHIPFAIL', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_SUPERCHIPPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_SUPERCHIPPASS, self).__init__(register,
            'SUPERCHIPPASS', 'MODEM_S.SISTATUS.SUPERCHIPPASS', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_TIMEOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_TIMEOFFSET, self).__init__(register,
            'TIMEOFFSET', 'MODEM_S.SISTATUS.TIMEOFFSET', 'read-only',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_CORRPASSNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_CORRPASSNUM, self).__init__(register,
            'CORRPASSNUM', 'MODEM_S.SISTATUS.CORRPASSNUM', 'read-only',
            u"",
            20, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_SNIFFDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_SNIFFDONE, self).__init__(register,
            'SNIFFDONE', 'MODEM_S.SISTATUS.SNIFFDONE', 'read-only',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SISTATUS_SIDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SISTATUS_SIDET, self).__init__(register,
            'SIDET', 'MODEM_S.SISTATUS.SIDET', 'read-only',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CFGANTPATTEXT_CFGANTPATTVALEXT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CFGANTPATTEXT_CFGANTPATTVALEXT, self).__init__(register,
            'CFGANTPATTVALEXT', 'MODEM_S.CFGANTPATTEXT.CFGANTPATTVALEXT', 'read-write',
            u"",
            0, 30)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_SIRSTAGCMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_SIRSTAGCMODE, self).__init__(register,
            'SIRSTAGCMODE', 'MODEM_S.SICTRL2.SIRSTAGCMODE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_SIRSTPRSMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_SIRSTPRSMODE, self).__init__(register,
            'SIRSTPRSMODE', 'MODEM_S.SICTRL2.SIRSTPRSMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_SIRSTCCAMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_SIRSTCCAMODE, self).__init__(register,
            'SIRSTCCAMODE', 'MODEM_S.SICTRL2.SIRSTCCAMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_DISSIFRAMEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_DISSIFRAMEDET, self).__init__(register,
            'DISSIFRAMEDET', 'MODEM_S.SICTRL2.DISSIFRAMEDET', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_AGCRSTUPONSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_AGCRSTUPONSI, self).__init__(register,
            'AGCRSTUPONSI', 'MODEM_S.SICTRL2.AGCRSTUPONSI', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_SHFTWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_SHFTWIN, self).__init__(register,
            'SHFTWIN', 'MODEM_S.SICTRL2.SHFTWIN', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_SUPERCHIPNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_SUPERCHIPNUM, self).__init__(register,
            'SUPERCHIPNUM', 'MODEM_S.SICTRL2.SUPERCHIPNUM', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_CORRNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_CORRNUM, self).__init__(register,
            'CORRNUM', 'MODEM_S.SICTRL2.CORRNUM', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SICTRL2_NARROWPULSETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SICTRL2_NARROWPULSETHRESH, self).__init__(register,
            'NARROWPULSETHRESH', 'MODEM_S.SICTRL2.NARROWPULSETHRESH', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_CHFSWCTRL_CHFSWTIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_CHFSWCTRL_CHFSWTIME, self).__init__(register,
            'CHFSWTIME', 'MODEM_S.CHFSWCTRL.CHFSWTIME', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DUALTIM_MINCOSTTHD2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DUALTIM_MINCOSTTHD2, self).__init__(register,
            'MINCOSTTHD2', 'MODEM_S.DUALTIM.MINCOSTTHD2', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DUALTIM_SYNCACQWIN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DUALTIM_SYNCACQWIN2, self).__init__(register,
            'SYNCACQWIN2', 'MODEM_S.DUALTIM.SYNCACQWIN2', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_DUALTIM_DUALTIMEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_DUALTIM_DUALTIMEN, self).__init__(register,
            'DUALTIMEN', 'MODEM_S.DUALTIM.DUALTIMEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCAL_IRCALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCAL_IRCALEN, self).__init__(register,
            'IRCALEN', 'MODEM_S.IRCAL.IRCALEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCAL_MURSHF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCAL_MURSHF, self).__init__(register,
            'MURSHF', 'MODEM_S.IRCAL.MURSHF', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCAL_MUISHF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCAL_MUISHF, self).__init__(register,
            'MUISHF', 'MODEM_S.IRCAL.MUISHF', 'read-write',
            u"",
            7, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCAL_IRCORREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCAL_IRCORREN, self).__init__(register,
            'IRCORREN', 'MODEM_S.IRCAL.IRCORREN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCAL_IRCALCOEFRSTCMD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCAL_IRCALCOEFRSTCMD, self).__init__(register,
            'IRCALCOEFRSTCMD', 'MODEM_S.IRCAL.IRCALCOEFRSTCMD', 'write-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCAL_IRCALIFADCDBG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCAL_IRCALIFADCDBG, self).__init__(register,
            'IRCALIFADCDBG', 'MODEM_S.IRCAL.IRCALIFADCDBG', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCALCOEF_CRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCALCOEF_CRV, self).__init__(register,
            'CRV', 'MODEM_S.IRCALCOEF.CRV', 'read-only',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCALCOEF_CIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCALCOEF_CIV, self).__init__(register,
            'CIV', 'MODEM_S.IRCALCOEF.CIV', 'read-only',
            u"",
            16, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCALCOEFWR0_CRVWD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCALCOEFWR0_CRVWD, self).__init__(register,
            'CRVWD', 'MODEM_S.IRCALCOEFWR0.CRVWD', 'read-write',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCALCOEFWR0_CRVWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCALCOEFWR0_CRVWEN, self).__init__(register,
            'CRVWEN', 'MODEM_S.IRCALCOEFWR0.CRVWEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCALCOEFWR0_CIVWD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCALCOEFWR0_CIVWD, self).__init__(register,
            'CIVWD', 'MODEM_S.IRCALCOEFWR0.CIVWD', 'read-write',
            u"",
            16, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_IRCALCOEFWR0_CIVWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_IRCALCOEFWR0_CIVWEN, self).__init__(register,
            'CIVWEN', 'MODEM_S.IRCALCOEFWR0.CIVWEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADCTRL1_ADCTRL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADCTRL1_ADCTRL1, self).__init__(register,
            'ADCTRL1', 'MODEM_S.ADCTRL1.ADCTRL1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADCTRL2_ADCTRL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADCTRL2_ADCTRL2, self).__init__(register,
            'ADCTRL2', 'MODEM_S.ADCTRL2.ADCTRL2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL0_ADRSSI0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL0_ADRSSI0, self).__init__(register,
            'ADRSSI0', 'MODEM_S.ADQUAL0.ADRSSI0', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL0_ADRSSI1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL0_ADRSSI1, self).__init__(register,
            'ADRSSI1', 'MODEM_S.ADQUAL0.ADRSSI1', 'read-only',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL1_ADCORR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL1_ADCORR0, self).__init__(register,
            'ADCORR0', 'MODEM_S.ADQUAL1.ADCORR0', 'read-only',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL1_ADSTAT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL1_ADSTAT1, self).__init__(register,
            'ADSTAT1', 'MODEM_S.ADQUAL1.ADSTAT1', 'read-only',
            u"",
            17, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL2_ADRSSI0P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL2_ADRSSI0P, self).__init__(register,
            'ADRSSI0P', 'MODEM_S.ADQUAL2.ADRSSI0P', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL2_ADRSSI1P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL2_ADRSSI1P, self).__init__(register,
            'ADRSSI1P', 'MODEM_S.ADQUAL2.ADRSSI1P', 'read-only',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL3_ADCORR0P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL3_ADCORR0P, self).__init__(register,
            'ADCORR0P', 'MODEM_S.ADQUAL3.ADCORR0P', 'read-only',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL3_ADSTAT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL3_ADSTAT2, self).__init__(register,
            'ADSTAT2', 'MODEM_S.ADQUAL3.ADSTAT2', 'read-only',
            u"",
            17, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL4_ADAGCGRTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL4_ADAGCGRTHR, self).__init__(register,
            'ADAGCGRTHR', 'MODEM_S.ADQUAL4.ADAGCGRTHR', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL4_ADRSSIGRTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL4_ADRSSIGRTHR, self).__init__(register,
            'ADRSSIGRTHR', 'MODEM_S.ADQUAL4.ADRSSIGRTHR', 'read-write',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL4_ADGRMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL4_ADGRMODE, self).__init__(register,
            'ADGRMODE', 'MODEM_S.ADQUAL4.ADGRMODE', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL5_ADDIRECTCORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL5_ADDIRECTCORR, self).__init__(register,
            'ADDIRECTCORR', 'MODEM_S.ADQUAL5.ADDIRECTCORR', 'read-write',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL6_ADBACORRTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL6_ADBACORRTHR, self).__init__(register,
            'ADBACORRTHR', 'MODEM_S.ADQUAL6.ADBACORRTHR', 'read-write',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL6_ADBACORRDIFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL6_ADBACORRDIFF, self).__init__(register,
            'ADBACORRDIFF', 'MODEM_S.ADQUAL6.ADBACORRDIFF', 'read-write',
            u"",
            17, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL7_ADBARSSITHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL7_ADBARSSITHR, self).__init__(register,
            'ADBARSSITHR', 'MODEM_S.ADQUAL7.ADBARSSITHR', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL7_ADBARSSIDIFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL7_ADBARSSIDIFF, self).__init__(register,
            'ADBARSSIDIFF', 'MODEM_S.ADQUAL7.ADBARSSIDIFF', 'read-write',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL8_ADBACORRTHR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL8_ADBACORRTHR2, self).__init__(register,
            'ADBACORRTHR2', 'MODEM_S.ADQUAL8.ADBACORRTHR2', 'read-write',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL8_ADBAMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL8_ADBAMODE, self).__init__(register,
            'ADBAMODE', 'MODEM_S.ADQUAL8.ADBAMODE', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL8_ADBAAGCTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL8_ADBAAGCTHR, self).__init__(register,
            'ADBAAGCTHR', 'MODEM_S.ADQUAL8.ADBAAGCTHR', 'read-write',
            u"",
            24, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL9_ADCORR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL9_ADCORR1, self).__init__(register,
            'ADCORR1', 'MODEM_S.ADQUAL9.ADCORR1', 'read-only',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADQUAL10_ADCORR1P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADQUAL10_ADCORR1P, self).__init__(register,
            'ADCORR1P', 'MODEM_S.ADQUAL10.ADCORR1P', 'read-only',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADSTATEC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADSTATEC, self).__init__(register,
            'ADSTATEC', 'MODEM_S.ADFSM0.ADSTATEC', 'read-only',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADSTATEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADSTATEP, self).__init__(register,
            'ADSTATEP', 'MODEM_S.ADFSM0.ADSTATEP', 'read-only',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADSTATEP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADSTATEP2, self).__init__(register,
            'ADSTATEP2', 'MODEM_S.ADFSM0.ADSTATEP2', 'read-only',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADSTATEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADSTATEN, self).__init__(register,
            'ADSTATEN', 'MODEM_S.ADFSM0.ADSTATEN', 'read-only',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADTD0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADTD0, self).__init__(register,
            'ADTD0', 'MODEM_S.ADFSM0.ADTD0', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADTD0P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADTD0P, self).__init__(register,
            'ADTD0P', 'MODEM_S.ADFSM0.ADTD0P', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADTD1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADTD1, self).__init__(register,
            'ADTD1', 'MODEM_S.ADFSM0.ADTD1', 'read-only',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADTD1P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADTD1P, self).__init__(register,
            'ADTD1P', 'MODEM_S.ADFSM0.ADTD1P', 'read-only',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADSTATREAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADSTATREAD, self).__init__(register,
            'ADSTATREAD', 'MODEM_S.ADFSM0.ADSTATREAD', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADSTAT1SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADSTAT1SEL, self).__init__(register,
            'ADSTAT1SEL', 'MODEM_S.ADFSM0.ADSTAT1SEL', 'read-write',
            u"",
            21, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM0_ADSTAT2SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM0_ADSTAT2SEL, self).__init__(register,
            'ADSTAT2SEL', 'MODEM_S.ADFSM0.ADSTAT2SEL', 'read-write',
            u"",
            26, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM1_ADOSETANT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM1_ADOSETANT0, self).__init__(register,
            'ADOSETANT0', 'MODEM_S.ADFSM1.ADOSETANT0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM1_ADOSETANT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM1_ADOSETANT1, self).__init__(register,
            'ADOSETANT1', 'MODEM_S.ADFSM1.ADOSETANT1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM2_ADOSWITCHANT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM2_ADOSWITCHANT, self).__init__(register,
            'ADOSWITCHANT', 'MODEM_S.ADFSM2.ADOSWITCHANT', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM2_ADORESTARTRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM2_ADORESTARTRX, self).__init__(register,
            'ADORESTARTRX', 'MODEM_S.ADFSM2.ADORESTARTRX', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM3_ADOQUAL0UPDATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM3_ADOQUAL0UPDATE, self).__init__(register,
            'ADOQUAL0UPDATE', 'MODEM_S.ADFSM3.ADOQUAL0UPDATE', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM3_ADOQUAL1UPDATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM3_ADOQUAL1UPDATE, self).__init__(register,
            'ADOQUAL1UPDATE', 'MODEM_S.ADFSM3.ADOQUAL1UPDATE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM4_ADOQUAL0CLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM4_ADOQUAL0CLEAR, self).__init__(register,
            'ADOQUAL0CLEAR', 'MODEM_S.ADFSM4.ADOQUAL0CLEAR', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM4_ADOQUAL1CLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM4_ADOQUAL1CLEAR, self).__init__(register,
            'ADOQUAL1CLEAR', 'MODEM_S.ADFSM4.ADOQUAL1CLEAR', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM5_ADOMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM5_ADOMUX, self).__init__(register,
            'ADOMUX', 'MODEM_S.ADFSM5.ADOMUX', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM6_ADNEXTSTATESW0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM6_ADNEXTSTATESW0, self).__init__(register,
            'ADNEXTSTATESW0', 'MODEM_S.ADFSM6.ADNEXTSTATESW0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM6_ADNEXTSTATESW1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM6_ADNEXTSTATESW1, self).__init__(register,
            'ADNEXTSTATESW1', 'MODEM_S.ADFSM6.ADNEXTSTATESW1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM7_ADNEXTSTATESW2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM7_ADNEXTSTATESW2, self).__init__(register,
            'ADNEXTSTATESW2', 'MODEM_S.ADFSM7.ADNEXTSTATESW2', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM7_ADNEXTSTATESW3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM7_ADNEXTSTATESW3, self).__init__(register,
            'ADNEXTSTATESW3', 'MODEM_S.ADFSM7.ADNEXTSTATESW3', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM8_ADNEXTSTATESW4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM8_ADNEXTSTATESW4, self).__init__(register,
            'ADNEXTSTATESW4', 'MODEM_S.ADFSM8.ADNEXTSTATESW4', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM8_ADNEXTSTATESW5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM8_ADNEXTSTATESW5, self).__init__(register,
            'ADNEXTSTATESW5', 'MODEM_S.ADFSM8.ADNEXTSTATESW5', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM9_ADNEXTSTATESW6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM9_ADNEXTSTATESW6, self).__init__(register,
            'ADNEXTSTATESW6', 'MODEM_S.ADFSM9.ADNEXTSTATESW6', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM9_ADNEXTSTATESW7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM9_ADNEXTSTATESW7, self).__init__(register,
            'ADNEXTSTATESW7', 'MODEM_S.ADFSM9.ADNEXTSTATESW7', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM10_ADNEXTSTATESW8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM10_ADNEXTSTATESW8, self).__init__(register,
            'ADNEXTSTATESW8', 'MODEM_S.ADFSM10.ADNEXTSTATESW8', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM10_ADNEXTSTATESW9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM10_ADNEXTSTATESW9, self).__init__(register,
            'ADNEXTSTATESW9', 'MODEM_S.ADFSM10.ADNEXTSTATESW9', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM11_ADNEXTSTATESW10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM11_ADNEXTSTATESW10, self).__init__(register,
            'ADNEXTSTATESW10', 'MODEM_S.ADFSM11.ADNEXTSTATESW10', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM11_ADNEXTSTATESW11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM11_ADNEXTSTATESW11, self).__init__(register,
            'ADNEXTSTATESW11', 'MODEM_S.ADFSM11.ADNEXTSTATESW11', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM12_ADNEXTSTATESW12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM12_ADNEXTSTATESW12, self).__init__(register,
            'ADNEXTSTATESW12', 'MODEM_S.ADFSM12.ADNEXTSTATESW12', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM12_ADNEXTSTATESW13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM12_ADNEXTSTATESW13, self).__init__(register,
            'ADNEXTSTATESW13', 'MODEM_S.ADFSM12.ADNEXTSTATESW13', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM13_ADNEXTSTATESW14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM13_ADNEXTSTATESW14, self).__init__(register,
            'ADNEXTSTATESW14', 'MODEM_S.ADFSM13.ADNEXTSTATESW14', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM13_ADNEXTSTATESW15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM13_ADNEXTSTATESW15, self).__init__(register,
            'ADNEXTSTATESW15', 'MODEM_S.ADFSM13.ADNEXTSTATESW15', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM14_ADFSMCOND0ENA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM14_ADFSMCOND0ENA, self).__init__(register,
            'ADFSMCOND0ENA', 'MODEM_S.ADFSM14.ADFSMCOND0ENA', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM14_ADFSMCOND1ENA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM14_ADFSMCOND1ENA, self).__init__(register,
            'ADFSMCOND1ENA', 'MODEM_S.ADFSM14.ADFSMCOND1ENA', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM15_ADFSMCOND2ENA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM15_ADFSMCOND2ENA, self).__init__(register,
            'ADFSMCOND2ENA', 'MODEM_S.ADFSM15.ADFSMCOND2ENA', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM15_ADFSMCOND3ENA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM15_ADFSMCOND3ENA, self).__init__(register,
            'ADFSMCOND3ENA', 'MODEM_S.ADFSM15.ADFSMCOND3ENA', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM16_ADFSMCOND0ENB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM16_ADFSMCOND0ENB, self).__init__(register,
            'ADFSMCOND0ENB', 'MODEM_S.ADFSM16.ADFSMCOND0ENB', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM16_ADFSMCOND1ENB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM16_ADFSMCOND1ENB, self).__init__(register,
            'ADFSMCOND1ENB', 'MODEM_S.ADFSM16.ADFSMCOND1ENB', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM17_ADFSMCOND2ENB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM17_ADFSMCOND2ENB, self).__init__(register,
            'ADFSMCOND2ENB', 'MODEM_S.ADFSM17.ADFSMCOND2ENB', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM17_ADFSMCOND3ENB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM17_ADFSMCOND3ENB, self).__init__(register,
            'ADFSMCOND3ENB', 'MODEM_S.ADFSM17.ADFSMCOND3ENB', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM18_ADFSMCONDSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM18_ADFSMCONDSEL, self).__init__(register,
            'ADFSMCONDSEL', 'MODEM_S.ADFSM18.ADFSMCONDSEL', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM19_ADFSMNEXTFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM19_ADFSMNEXTFORCE, self).__init__(register,
            'ADFSMNEXTFORCE', 'MODEM_S.ADFSM19.ADFSMNEXTFORCE', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM19_ADFSMCONDTRUE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM19_ADFSMCONDTRUE, self).__init__(register,
            'ADFSMCONDTRUE', 'MODEM_S.ADFSM19.ADFSMCONDTRUE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM20_ADITENTEREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM20_ADITENTEREN, self).__init__(register,
            'ADITENTEREN', 'MODEM_S.ADFSM20.ADITENTEREN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM20_ADITLEAVEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM20_ADITLEAVEEN, self).__init__(register,
            'ADITLEAVEEN', 'MODEM_S.ADFSM20.ADITLEAVEEN', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM21_ADENTERFREEZEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM21_ADENTERFREEZEEN, self).__init__(register,
            'ADENTERFREEZEEN', 'MODEM_S.ADFSM21.ADENTERFREEZEEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM21_ADLEAVEFREEZEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM21_ADLEAVEFREEZEEN, self).__init__(register,
            'ADLEAVEFREEZEEN', 'MODEM_S.ADFSM21.ADLEAVEFREEZEEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM21_ADFROZEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM21_ADFROZEN, self).__init__(register,
            'ADFROZEN', 'MODEM_S.ADFSM21.ADFROZEN', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM21_ADUNFREEZENEXT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM21_ADUNFREEZENEXT, self).__init__(register,
            'ADUNFREEZENEXT', 'MODEM_S.ADFSM21.ADUNFREEZENEXT', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM21_ADAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM21_ADAS, self).__init__(register,
            'ADAS', 'MODEM_S.ADFSM21.ADAS', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM21_ADBA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM21_ADBA, self).__init__(register,
            'ADBA', 'MODEM_S.ADFSM21.ADBA', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM21_ADUNFREEZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM21_ADUNFREEZE, self).__init__(register,
            'ADUNFREEZE', 'MODEM_S.ADFSM21.ADUNFREEZE', 'write-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM22_ADITENTERSTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM22_ADITENTERSTATUS, self).__init__(register,
            'ADITENTERSTATUS', 'MODEM_S.ADFSM22.ADITENTERSTATUS', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM22_ADITLEAVESTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM22_ADITLEAVESTATUS, self).__init__(register,
            'ADITLEAVESTATUS', 'MODEM_S.ADFSM22.ADITLEAVESTATUS', 'read-only',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM23_ADFSMCOND0ENC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM23_ADFSMCOND0ENC, self).__init__(register,
            'ADFSMCOND0ENC', 'MODEM_S.ADFSM23.ADFSMCOND0ENC', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM23_ADFSMCOND1ENC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM23_ADFSMCOND1ENC, self).__init__(register,
            'ADFSMCOND1ENC', 'MODEM_S.ADFSM23.ADFSMCOND1ENC', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM24_ADFSMCOND2ENC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM24_ADFSMCOND2ENC, self).__init__(register,
            'ADFSMCOND2ENC', 'MODEM_S.ADFSM24.ADFSMCOND2ENC', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM24_ADFSMCOND3ENC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM24_ADFSMCOND3ENC, self).__init__(register,
            'ADFSMCOND3ENC', 'MODEM_S.ADFSM24.ADFSMCOND3ENC', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM25_ADFSMCONDOR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM25_ADFSMCONDOR0, self).__init__(register,
            'ADFSMCONDOR0', 'MODEM_S.ADFSM25.ADFSMCONDOR0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM25_ADFSMCONDOR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM25_ADFSMCONDOR1, self).__init__(register,
            'ADFSMCONDOR1', 'MODEM_S.ADFSM25.ADFSMCONDOR1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM26_ADFSMCOND0END(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM26_ADFSMCOND0END, self).__init__(register,
            'ADFSMCOND0END', 'MODEM_S.ADFSM26.ADFSMCOND0END', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM26_ADFSMCOND1END(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM26_ADFSMCOND1END, self).__init__(register,
            'ADFSMCOND1END', 'MODEM_S.ADFSM26.ADFSMCOND1END', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM27_ADFSMCOND2END(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM27_ADFSMCOND2END, self).__init__(register,
            'ADFSMCOND2END', 'MODEM_S.ADFSM27.ADFSMCOND2END', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM27_ADFSMCOND3END(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM27_ADFSMCOND3END, self).__init__(register,
            'ADFSMCOND3END', 'MODEM_S.ADFSM27.ADFSMCOND3END', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM28_ADOSETANTFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM28_ADOSETANTFORCE, self).__init__(register,
            'ADOSETANTFORCE', 'MODEM_S.ADFSM28.ADOSETANTFORCE', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM28_ADORESTARTRXFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM28_ADORESTARTRXFORCE, self).__init__(register,
            'ADORESTARTRXFORCE', 'MODEM_S.ADFSM28.ADORESTARTRXFORCE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM29_ADOQUALUPDATEFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM29_ADOQUALUPDATEFORCE, self).__init__(register,
            'ADOQUALUPDATEFORCE', 'MODEM_S.ADFSM29.ADOQUALUPDATEFORCE', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM29_ADOQUALCLEARFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM29_ADOQUALCLEARFORCE, self).__init__(register,
            'ADOQUALCLEARFORCE', 'MODEM_S.ADFSM29.ADOQUALCLEARFORCE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADFSM30_ADODEMODRXREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADFSM30_ADODEMODRXREQ, self).__init__(register,
            'ADODEMODRXREQ', 'MODEM_S.ADFSM30.ADODEMODRXREQ', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC1_ADPCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC1_ADPCEN, self).__init__(register,
            'ADPCEN', 'MODEM_S.ADPC1.ADPCEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC1_ADPCWNDSIZECHIP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC1_ADPCWNDSIZECHIP, self).__init__(register,
            'ADPCWNDSIZECHIP', 'MODEM_S.ADPC1.ADPCWNDSIZECHIP', 'read-write',
            u"",
            1, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC1_ADPCCORROFFSETCHIP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC1_ADPCCORROFFSETCHIP, self).__init__(register,
            'ADPCCORROFFSETCHIP', 'MODEM_S.ADPC1.ADPCCORROFFSETCHIP', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC1_ADPCTIMINGBAUDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC1_ADPCTIMINGBAUDS, self).__init__(register,
            'ADPCTIMINGBAUDS', 'MODEM_S.ADPC1.ADPCTIMINGBAUDS', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC1_ADPCWNDCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC1_ADPCWNDCNT, self).__init__(register,
            'ADPCWNDCNT', 'MODEM_S.ADPC1.ADPCWNDCNT', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC1_ADPCSKIPCHIPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC1_ADPCSKIPCHIPS, self).__init__(register,
            'ADPCSKIPCHIPS', 'MODEM_S.ADPC1.ADPCSKIPCHIPS', 'read-write',
            u"",
            27, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC2_ADPCCORRSAMPLES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC2_ADPCCORRSAMPLES, self).__init__(register,
            'ADPCCORRSAMPLES', 'MODEM_S.ADPC2.ADPCCORRSAMPLES', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC2_ADPCPRETIMINGBAUDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC2_ADPCPRETIMINGBAUDS, self).__init__(register,
            'ADPCPRETIMINGBAUDS', 'MODEM_S.ADPC2.ADPCPRETIMINGBAUDS', 'read-write',
            u"",
            10, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC2_ADENCORR32(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC2_ADENCORR32, self).__init__(register,
            'ADENCORR32', 'MODEM_S.ADPC2.ADENCORR32', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC2_ADPCSIGAMPTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC2_ADPCSIGAMPTHR, self).__init__(register,
            'ADPCSIGAMPTHR', 'MODEM_S.ADPC2.ADPCSIGAMPTHR', 'read-write',
            u"",
            19, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC2_ADPCWNDCNTRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC2_ADPCWNDCNTRST, self).__init__(register,
            'ADPCWNDCNTRST', 'MODEM_S.ADPC2.ADPCWNDCNTRST', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSEN, self).__init__(register,
            'ADBBSSEN', 'MODEM_S.ADPC3.ADBBSSEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSFILTLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSFILTLENGTH, self).__init__(register,
            'ADBBSSFILTLENGTH', 'MODEM_S.ADPC3.ADBBSSFILTLENGTH', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSAVGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSAVGEN, self).__init__(register,
            'ADBBSSAVGEN', 'MODEM_S.ADPC3.ADBBSSAVGEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSAVGPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSAVGPER, self).__init__(register,
            'ADBBSSAVGPER', 'MODEM_S.ADPC3.ADBBSSAVGPER', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSAMPMANT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSAMPMANT, self).__init__(register,
            'ADBBSSAMPMANT', 'MODEM_S.ADPC3.ADBBSSAMPMANT', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSAMPEXP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSAMPEXP, self).__init__(register,
            'ADBBSSAMPEXP', 'MODEM_S.ADPC3.ADBBSSAMPEXP', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSAVGWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSAVGWAIT, self).__init__(register,
            'ADBBSSAVGWAIT', 'MODEM_S.ADPC3.ADBBSSAVGWAIT', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSAVGFREEZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSAVGFREEZE, self).__init__(register,
            'ADBBSSAVGFREEZE', 'MODEM_S.ADPC3.ADBBSSAVGFREEZE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC3_ADBBSSSELWRDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC3_ADBBSSSELWRDATA, self).__init__(register,
            'ADBBSSSELWRDATA', 'MODEM_S.ADPC3.ADBBSSSELWRDATA', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC4_ADBBSSAMPLUT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC4_ADBBSSAMPLUT0, self).__init__(register,
            'ADBBSSAMPLUT0', 'MODEM_S.ADPC4.ADBBSSAMPLUT0', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC4_ADBBSSAMPLUT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC4_ADBBSSAMPLUT1, self).__init__(register,
            'ADBBSSAMPLUT1', 'MODEM_S.ADPC4.ADBBSSAMPLUT1', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC4_ADBBSSAMPLUT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC4_ADBBSSAMPLUT2, self).__init__(register,
            'ADBBSSAMPLUT2', 'MODEM_S.ADPC4.ADBBSSAMPLUT2', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC4_ADBBSSAMPLUT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC4_ADBBSSAMPLUT3, self).__init__(register,
            'ADBBSSAMPLUT3', 'MODEM_S.ADPC4.ADBBSSAMPLUT3', 'read-write',
            u"",
            24, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC5_ADBBSSAMPLUT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC5_ADBBSSAMPLUT4, self).__init__(register,
            'ADBBSSAMPLUT4', 'MODEM_S.ADPC5.ADBBSSAMPLUT4', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC5_ADBBSSAMPLUT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC5_ADBBSSAMPLUT5, self).__init__(register,
            'ADBBSSAMPLUT5', 'MODEM_S.ADPC5.ADBBSSAMPLUT5', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC5_ADBBSSAMPLUT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC5_ADBBSSAMPLUT6, self).__init__(register,
            'ADBBSSAMPLUT6', 'MODEM_S.ADPC5.ADBBSSAMPLUT6', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC5_ADBBSSAMPLUT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC5_ADBBSSAMPLUT7, self).__init__(register,
            'ADBBSSAMPLUT7', 'MODEM_S.ADPC5.ADBBSSAMPLUT7', 'read-write',
            u"",
            24, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC6_ADBBSSAMPLUT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC6_ADBBSSAMPLUT8, self).__init__(register,
            'ADBBSSAMPLUT8', 'MODEM_S.ADPC6.ADBBSSAMPLUT8', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC6_ADBBSSAMPLUT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC6_ADBBSSAMPLUT9, self).__init__(register,
            'ADBBSSAMPLUT9', 'MODEM_S.ADPC6.ADBBSSAMPLUT9', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC6_ADBBSSAMPLUT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC6_ADBBSSAMPLUT10, self).__init__(register,
            'ADBBSSAMPLUT10', 'MODEM_S.ADPC6.ADBBSSAMPLUT10', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC6_ADBBSSAMPLUT11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC6_ADBBSSAMPLUT11, self).__init__(register,
            'ADBBSSAMPLUT11', 'MODEM_S.ADPC6.ADBBSSAMPLUT11', 'read-write',
            u"",
            24, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC7_ADBBSSAMPLUT12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC7_ADBBSSAMPLUT12, self).__init__(register,
            'ADBBSSAMPLUT12', 'MODEM_S.ADPC7.ADBBSSAMPLUT12', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC7_ADBBSSAMPLUT13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC7_ADBBSSAMPLUT13, self).__init__(register,
            'ADBBSSAMPLUT13', 'MODEM_S.ADPC7.ADBBSSAMPLUT13', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC7_ADBBSSAMPLUT14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC7_ADBBSSAMPLUT14, self).__init__(register,
            'ADBBSSAMPLUT14', 'MODEM_S.ADPC7.ADBBSSAMPLUT14', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC7_ADBBSSAMPLUT15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC7_ADBBSSAMPLUT15, self).__init__(register,
            'ADBBSSAMPLUT15', 'MODEM_S.ADPC7.ADBBSSAMPLUT15', 'read-write',
            u"",
            24, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC8_ADPCOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC8_ADPCOSR, self).__init__(register,
            'ADPCOSR', 'MODEM_S.ADPC8.ADPCOSR', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC8_ADPCANTSAMPOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC8_ADPCANTSAMPOFFSET, self).__init__(register,
            'ADPCANTSAMPOFFSET', 'MODEM_S.ADPC8.ADPCANTSAMPOFFSET', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC8_ADPCANTSAMPSWITCHWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC8_ADPCANTSAMPSWITCHWAIT, self).__init__(register,
            'ADPCANTSAMPSWITCHWAIT', 'MODEM_S.ADPC8.ADPCANTSAMPSWITCHWAIT', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC8_ADPCANTSAMPBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC8_ADPCANTSAMPBUF, self).__init__(register,
            'ADPCANTSAMPBUF', 'MODEM_S.ADPC8.ADPCANTSAMPBUF', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC8_ADPCANTSAMPWRITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC8_ADPCANTSAMPWRITE, self).__init__(register,
            'ADPCANTSAMPWRITE', 'MODEM_S.ADPC8.ADPCANTSAMPWRITE', 'read-write',
            u"",
            14, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC8_ADPCANTSAMPSWITCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC8_ADPCANTSAMPSWITCH, self).__init__(register,
            'ADPCANTSAMPSWITCH', 'MODEM_S.ADPC8.ADPCANTSAMPSWITCH', 'read-write',
            u"",
            22, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC9_ADBBSSAMPAVGLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC9_ADBBSSAMPAVGLIM, self).__init__(register,
            'ADBBSSAMPAVGLIM', 'MODEM_S.ADPC9.ADBBSSAMPAVGLIM', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC9_ADBBSSAMPTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC9_ADBBSSAMPTHR, self).__init__(register,
            'ADBBSSAMPTHR', 'MODEM_S.ADPC9.ADBBSSAMPTHR', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC9_ADBBSSSYNCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC9_ADBBSSSYNCEN, self).__init__(register,
            'ADBBSSSYNCEN', 'MODEM_S.ADPC9.ADBBSSSYNCEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC9_ADBBSSUPTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC9_ADBBSSUPTHR, self).__init__(register,
            'ADBBSSUPTHR', 'MODEM_S.ADPC9.ADBBSSUPTHR', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC9_ADBBSSDNTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC9_ADBBSSDNTHR, self).__init__(register,
            'ADBBSSDNTHR', 'MODEM_S.ADPC9.ADBBSSDNTHR', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC10_ADBBSSAMPJUMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC10_ADBBSSAMPJUMP, self).__init__(register,
            'ADBBSSAMPJUMP', 'MODEM_S.ADPC10.ADBBSSAMPJUMP', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC10_ADBBSSCHANGEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC10_ADBBSSCHANGEEN, self).__init__(register,
            'ADBBSSCHANGEEN', 'MODEM_S.ADPC10.ADBBSSCHANGEEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC10_ADBBSSCHGUPTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC10_ADBBSSCHGUPTHR, self).__init__(register,
            'ADBBSSCHGUPTHR', 'MODEM_S.ADPC10.ADBBSSCHGUPTHR', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_ADPC10_ADBBSSCHGDNTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_ADPC10_ADBBSSCHGDNTHR, self).__init__(register,
            'ADBBSSCHGDNTHR', 'MODEM_S.ADPC10.ADBBSSCHGDNTHR', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_HADMEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_HADMEN, self).__init__(register,
            'HADMEN', 'MODEM_S.HADMCTRL0.HADMEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_TESEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_TESEN, self).__init__(register,
            'TESEN', 'MODEM_S.HADMCTRL0.TESEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_PESEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_PESEN, self).__init__(register,
            'PESEN', 'MODEM_S.HADMCTRL0.PESEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_SNDSEQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_SNDSEQEN, self).__init__(register,
            'SNDSEQEN', 'MODEM_S.HADMCTRL0.SNDSEQEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_ROLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_ROLE, self).__init__(register,
            'ROLE', 'MODEM_S.HADMCTRL0.ROLE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_RTTPHY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_RTTPHY, self).__init__(register,
            'RTTPHY', 'MODEM_S.HADMCTRL0.RTTPHY', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_PM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_PM, self).__init__(register,
            'PM', 'MODEM_S.HADMCTRL0.PM', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_AVGMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_AVGMODE, self).__init__(register,
            'AVGMODE', 'MODEM_S.HADMCTRL0.AVGMODE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_DFTSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_DFTSCALE, self).__init__(register,
            'DFTSCALE', 'MODEM_S.HADMCTRL0.DFTSCALE', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_PKTSENTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_PKTSENTSEL, self).__init__(register,
            'PKTSENTSEL', 'MODEM_S.HADMCTRL0.PKTSENTSEL', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_TXUPSAMPOSR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_TXUPSAMPOSR4, self).__init__(register,
            'TXUPSAMPOSR4', 'MODEM_S.HADMCTRL0.TXUPSAMPOSR4', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_SSAFCGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_SSAFCGEAR, self).__init__(register,
            'SSAFCGEAR', 'MODEM_S.HADMCTRL0.SSAFCGEAR', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL0_SRC2AUTOSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL0_SRC2AUTOSCALE, self).__init__(register,
            'SRC2AUTOSCALE', 'MODEM_S.HADMCTRL0.SRC2AUTOSCALE', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL1_STEPSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL1_STEPSTATE, self).__init__(register,
            'STEPSTATE', 'MODEM_S.HADMCTRL1.STEPSTATE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL1_DFTSTARTOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL1_DFTSTARTOFF, self).__init__(register,
            'DFTSTARTOFF', 'MODEM_S.HADMCTRL1.DFTSTARTOFF', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL1_MAXSCHWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL1_MAXSCHWIN, self).__init__(register,
            'MAXSCHWIN', 'MODEM_S.HADMCTRL1.MAXSCHWIN', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMCTRL1_AVGSTARTOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMCTRL1_AVGSTARTOFF, self).__init__(register,
            'AVGSTARTOFF', 'MODEM_S.HADMCTRL1.AVGSTARTOFF', 'read-write',
            u"",
            22, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS0_AVG0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS0_AVG0, self).__init__(register,
            'AVG0', 'MODEM_S.HADMSTATUS0.AVG0', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS0_AVG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS0_AVG1, self).__init__(register,
            'AVG1', 'MODEM_S.HADMSTATUS0.AVG1', 'read-only',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS1_FREQOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS1_FREQOFFSET, self).__init__(register,
            'FREQOFFSET', 'MODEM_S.HADMSTATUS1.FREQOFFSET', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS1_TIMETOX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS1_TIMETOX, self).__init__(register,
            'TIMETOX', 'MODEM_S.HADMSTATUS1.TIMETOX', 'read-only',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS2_COSTLATE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS2_COSTLATE1, self).__init__(register,
            'COSTLATE1', 'MODEM_S.HADMSTATUS2.COSTLATE1', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS2_COSTCURR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS2_COSTCURR1, self).__init__(register,
            'COSTCURR1', 'MODEM_S.HADMSTATUS2.COSTCURR1', 'read-only',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS2_COSTEARL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS2_COSTEARL1, self).__init__(register,
            'COSTEARL1', 'MODEM_S.HADMSTATUS2.COSTEARL1', 'read-only',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS3_COSTLATE0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS3_COSTLATE0, self).__init__(register,
            'COSTLATE0', 'MODEM_S.HADMSTATUS3.COSTLATE0', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS3_COSTCURR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS3_COSTCURR0, self).__init__(register,
            'COSTCURR0', 'MODEM_S.HADMSTATUS3.COSTCURR0', 'read-only',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS3_COSTEARL0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS3_COSTEARL0, self).__init__(register,
            'COSTEARL0', 'MODEM_S.HADMSTATUS3.COSTEARL0', 'read-only',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS4_SBSP500I(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS4_SBSP500I, self).__init__(register,
            'SBSP500I', 'MODEM_S.HADMSTATUS4.SBSP500I', 'read-only',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS4_SBSP500Q(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS4_SBSP500Q, self).__init__(register,
            'SBSP500Q', 'MODEM_S.HADMSTATUS4.SBSP500Q', 'read-only',
            u"",
            16, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS5_SBSM500I(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS5_SBSM500I, self).__init__(register,
            'SBSM500I', 'MODEM_S.HADMSTATUS5.SBSM500I', 'read-only',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS5_SBSM500Q(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS5_SBSM500Q, self).__init__(register,
            'SBSM500Q', 'MODEM_S.HADMSTATUS5.SBSM500Q', 'read-only',
            u"",
            16, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS6_FREQMEAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS6_FREQMEAS, self).__init__(register,
            'FREQMEAS', 'MODEM_S.HADMSTATUS6.FREQMEAS', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS6_SBSPSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS6_SBSPSCALE, self).__init__(register,
            'SBSPSCALE', 'MODEM_S.HADMSTATUS6.SBSPSCALE', 'read-only',
            u"",
            20, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_HADMSTATUS6_SBSMSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_HADMSTATUS6_SBSMSCALE, self).__init__(register,
            'SBSMSCALE', 'MODEM_S.HADMSTATUS6.SBSMSCALE', 'read-only',
            u"",
            26, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCTRL_EHDSSSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCTRL_EHDSSSEN, self).__init__(register,
            'EHDSSSEN', 'MODEM_S.EHDSSSCTRL.EHDSSSEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCTRL_DSSSTIMEACQUTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCTRL_DSSSTIMEACQUTHD, self).__init__(register,
            'DSSSTIMEACQUTHD', 'MODEM_S.EHDSSSCTRL.DSSSTIMEACQUTHD', 'read-write',
            u"",
            1, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCTRL_FOEBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCTRL_FOEBIAS, self).__init__(register,
            'FOEBIAS', 'MODEM_S.EHDSSSCTRL.FOEBIAS', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCTRL_FREQCORREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCTRL_FREQCORREN, self).__init__(register,
            'FREQCORREN', 'MODEM_S.EHDSSSCTRL.FREQCORREN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCTRL_DSSSFRQLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCTRL_DSSSFRQLIM, self).__init__(register,
            'DSSSFRQLIM', 'MODEM_S.EHDSSSCTRL.DSSSFRQLIM', 'read-write',
            u"",
            14, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCTRL_OPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCTRL_OPMODE, self).__init__(register,
            'OPMODE', 'MODEM_S.EHDSSSCTRL.OPMODE', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCTRL_DSSSPMTIMEOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCTRL_DSSSPMTIMEOUT, self).__init__(register,
            'DSSSPMTIMEOUT', 'MODEM_S.EHDSSSCTRL.DSSSPMTIMEOUT', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCTRL_DSSSFRMTIMEOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCTRL_DSSSFRMTIMEOUT, self).__init__(register,
            'DSSSFRMTIMEOUT', 'MODEM_S.EHDSSSCTRL.DSSSFRMTIMEOUT', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG0_DSSSPATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG0_DSSSPATT, self).__init__(register,
            'DSSSPATT', 'MODEM_S.EHDSSSCFG0.DSSSPATT', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG1_DSSSEXPSYNCLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG1_DSSSEXPSYNCLEN, self).__init__(register,
            'DSSSEXPSYNCLEN', 'MODEM_S.EHDSSSCFG1.DSSSEXPSYNCLEN', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG1_DSSSCORRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG1_DSSSCORRTHD, self).__init__(register,
            'DSSSCORRTHD', 'MODEM_S.EHDSSSCFG1.DSSSCORRTHD', 'read-write',
            u"",
            9, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG1_DSSSDSAQTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG1_DSSSDSAQTHD, self).__init__(register,
            'DSSSDSAQTHD', 'MODEM_S.EHDSSSCFG1.DSSSDSAQTHD', 'read-write',
            u"",
            20, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG2_DSSSTIMCORRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG2_DSSSTIMCORRTHD, self).__init__(register,
            'DSSSTIMCORRTHD', 'MODEM_S.EHDSSSCFG2.DSSSTIMCORRTHD', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG2_DSSSFRTCORRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG2_DSSSFRTCORRTHD, self).__init__(register,
            'DSSSFRTCORRTHD', 'MODEM_S.EHDSSSCFG2.DSSSFRTCORRTHD', 'read-write',
            u"",
            11, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG2_DSSSTRACKINGWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG2_DSSSTRACKINGWIN, self).__init__(register,
            'DSSSTRACKINGWIN', 'MODEM_S.EHDSSSCFG2.DSSSTRACKINGWIN', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG2_DSSSCORRSCHWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG2_DSSSCORRSCHWIN, self).__init__(register,
            'DSSSCORRSCHWIN', 'MODEM_S.EHDSSSCFG2.DSSSCORRSCHWIN', 'read-write',
            u"",
            25, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_EHDSSSCFG2_ONESYMBOLMBDD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_EHDSSSCFG2_ONESYMBOLMBDD, self).__init__(register,
            'ONESYMBOLMBDD', 'MODEM_S.EHDSSSCFG2.ONESYMBOLMBDD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP0_SYM2CH0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP0_SYM2CH0, self).__init__(register,
            'SYM2CH0', 'MODEM_S.SYMBOL2CHIP0.SYM2CH0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP1_SYM2CH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP1_SYM2CH1, self).__init__(register,
            'SYM2CH1', 'MODEM_S.SYMBOL2CHIP1.SYM2CH1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP2_SYM2CH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP2_SYM2CH2, self).__init__(register,
            'SYM2CH2', 'MODEM_S.SYMBOL2CHIP2.SYM2CH2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP3_SYM2CH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP3_SYM2CH3, self).__init__(register,
            'SYM2CH3', 'MODEM_S.SYMBOL2CHIP3.SYM2CH3', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP4_SYM2CH4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP4_SYM2CH4, self).__init__(register,
            'SYM2CH4', 'MODEM_S.SYMBOL2CHIP4.SYM2CH4', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP5_SYM2CH5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP5_SYM2CH5, self).__init__(register,
            'SYM2CH5', 'MODEM_S.SYMBOL2CHIP5.SYM2CH5', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP6_SYM2CH6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP6_SYM2CH6, self).__init__(register,
            'SYM2CH6', 'MODEM_S.SYMBOL2CHIP6.SYM2CH6', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP7_SYM2CH7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP7_SYM2CH7, self).__init__(register,
            'SYM2CH7', 'MODEM_S.SYMBOL2CHIP7.SYM2CH7', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP8_SYM2CH8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP8_SYM2CH8, self).__init__(register,
            'SYM2CH8', 'MODEM_S.SYMBOL2CHIP8.SYM2CH8', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIP9_SYM2CH9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIP9_SYM2CH9, self).__init__(register,
            'SYM2CH9', 'MODEM_S.SYMBOL2CHIP9.SYM2CH9', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIPA_SYM2CHA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIPA_SYM2CHA, self).__init__(register,
            'SYM2CHA', 'MODEM_S.SYMBOL2CHIPA.SYM2CHA', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIPB_SYM2CHB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIPB_SYM2CHB, self).__init__(register,
            'SYM2CHB', 'MODEM_S.SYMBOL2CHIPB.SYM2CHB', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIPC_SYM2CHC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIPC_SYM2CHC, self).__init__(register,
            'SYM2CHC', 'MODEM_S.SYMBOL2CHIPC.SYM2CHC', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIPD_SYM2CHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIPD_SYM2CHD, self).__init__(register,
            'SYM2CHD', 'MODEM_S.SYMBOL2CHIPD.SYM2CHD', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIPE_SYM2CHE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIPE_SYM2CHE, self).__init__(register,
            'SYM2CHE', 'MODEM_S.SYMBOL2CHIPE.SYM2CHE', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYMBOL2CHIPF_SYM2CHF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYMBOL2CHIPF_SYM2CHF, self).__init__(register,
            'SYM2CHF', 'MODEM_S.SYMBOL2CHIPF.SYM2CHF', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SPARE_SPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SPARE_SPARE, self).__init__(register,
            'SPARE', 'MODEM_S.SPARE.SPARE', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNC0_SYNC0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNC0_SYNC0, self).__init__(register,
            'SYNC0', 'MODEM_S.SYNC0.SYNC0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNC1_SYNC1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNC1_SYNC1, self).__init__(register,
            'SYNC1', 'MODEM_S.SYNC1.SYNC1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNC2_SYNC2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNC2_SYNC2, self).__init__(register,
            'SYNC2', 'MODEM_S.SYNC2.SYNC2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCWORDCTRL_SYNC0BITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCWORDCTRL_SYNC0BITS, self).__init__(register,
            'SYNC0BITS', 'MODEM_S.SYNCWORDCTRL.SYNC0BITS', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCWORDCTRL_SYNC1BITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCWORDCTRL_SYNC1BITS, self).__init__(register,
            'SYNC1BITS', 'MODEM_S.SYNCWORDCTRL.SYNC1BITS', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCWORDCTRL_SYNC2BITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCWORDCTRL_SYNC2BITS, self).__init__(register,
            'SYNC2BITS', 'MODEM_S.SYNCWORDCTRL.SYNC2BITS', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCWORDCTRL_SYNC0ERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCWORDCTRL_SYNC0ERRORS, self).__init__(register,
            'SYNC0ERRORS', 'MODEM_S.SYNCWORDCTRL.SYNC0ERRORS', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCWORDCTRL_SYNC1ERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCWORDCTRL_SYNC1ERRORS, self).__init__(register,
            'SYNC1ERRORS', 'MODEM_S.SYNCWORDCTRL.SYNC1ERRORS', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCWORDCTRL_SYNC2ERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCWORDCTRL_SYNC2ERRORS, self).__init__(register,
            'SYNC2ERRORS', 'MODEM_S.SYNCWORDCTRL.SYNC2ERRORS', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCWORDCTRL_DUALSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCWORDCTRL_DUALSYNC, self).__init__(register,
            'DUALSYNC', 'MODEM_S.SYNCWORDCTRL.DUALSYNC', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_SYNCWORDCTRL_TRISYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_SYNCWORDCTRL_TRISYNC, self).__init__(register,
            'TRISYNC', 'MODEM_S.SYNCWORDCTRL.TRISYNC', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXCORR_TXDGAIN6DB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXCORR_TXDGAIN6DB, self).__init__(register,
            'TXDGAIN6DB', 'MODEM_S.TXCORR.TXDGAIN6DB', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXCORR_TXDGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXCORR_TXDGAIN, self).__init__(register,
            'TXDGAIN', 'MODEM_S.TXCORR.TXDGAIN', 'read-write',
            u"",
            1, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXCORR_TXGAINIMB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXCORR_TXGAINIMB, self).__init__(register,
            'TXGAINIMB', 'MODEM_S.TXCORR.TXGAINIMB', 'read-write',
            u"",
            5, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXCORR_TXPHSIMB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXCORR_TXPHSIMB, self).__init__(register,
            'TXPHSIMB', 'MODEM_S.TXCORR.TXPHSIMB', 'read-write',
            u"",
            11, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXCORR_TXFREQCORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXCORR_TXFREQCORR, self).__init__(register,
            'TXFREQCORR', 'MODEM_S.TXCORR.TXFREQCORR', 'read-write',
            u"",
            17, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_FORCECLKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_FORCECLKEN, self).__init__(register,
            'FORCECLKEN', 'MODEM_S.TXMISC.FORCECLKEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXIQIMBEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXIQIMBEN, self).__init__(register,
            'TXIQIMBEN', 'MODEM_S.TXMISC.TXIQIMBEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXINTPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXINTPEN, self).__init__(register,
            'TXINTPEN', 'MODEM_S.TXMISC.TXINTPEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXDSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXDSEN, self).__init__(register,
            'TXDSEN', 'MODEM_S.TXMISC.TXDSEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXIQSWAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXIQSWAP, self).__init__(register,
            'TXIQSWAP', 'MODEM_S.TXMISC.TXIQSWAP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXDACFORMAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXDACFORMAT, self).__init__(register,
            'TXDACFORMAT', 'MODEM_S.TXMISC.TXDACFORMAT', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXDACFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXDACFORCE, self).__init__(register,
            'TXDACFORCE', 'MODEM_S.TXMISC.TXDACFORCE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXDCI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXDCI, self).__init__(register,
            'TXDCI', 'MODEM_S.TXMISC.TXDCI', 'read-write',
            u"",
            7, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXDCQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXDCQ, self).__init__(register,
            'TXDCQ', 'MODEM_S.TXMISC.TXDCQ', 'read-write',
            u"",
            15, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_BR2M(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_BR2M, self).__init__(register,
            'BR2M', 'MODEM_S.TXMISC.BR2M', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_S_TXMISC_TXMOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_S_TXMISC_TXMOD, self).__init__(register,
            'TXMOD', 'MODEM_S.TXMISC.TXMOD', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True



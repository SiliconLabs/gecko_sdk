
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_MODEM_NS_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'MODEM_NS.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_EN_EN, self).__init__(register,
            'EN', 'MODEM_NS.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_TXFRAMESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_TXFRAMESENT, self).__init__(register,
            'TXFRAMESENT', 'MODEM_NS.IF.TXFRAMESENT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_TXSYNCSENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_TXSYNCSENT, self).__init__(register,
            'TXSYNCSENT', 'MODEM_NS.IF.TXSYNCSENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_TXPRESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_TXPRESENT, self).__init__(register,
            'TXPRESENT', 'MODEM_NS.IF.TXPRESENT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_TXRAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_TXRAMPDONE, self).__init__(register,
            'TXRAMPDONE', 'MODEM_NS.IF.TXRAMPDONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_LDTNOARR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_LDTNOARR, self).__init__(register,
            'LDTNOARR', 'MODEM_NS.IF.LDTNOARR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_PHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_PHDSADET, self).__init__(register,
            'PHDSADET', 'MODEM_NS.IF.PHDSADET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_PHYUNCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_PHYUNCODEDET, self).__init__(register,
            'PHYUNCODEDET', 'MODEM_NS.IF.PHYUNCODEDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_PHYCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_PHYCODEDET, self).__init__(register,
            'PHYCODEDET', 'MODEM_NS.IF.PHYCODEDET', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXTIMDET, self).__init__(register,
            'RXTIMDET', 'MODEM_NS.IF.RXTIMDET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXPREDET, self).__init__(register,
            'RXPREDET', 'MODEM_NS.IF.RXPREDET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXFRAMEDET0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXFRAMEDET0, self).__init__(register,
            'RXFRAMEDET0', 'MODEM_NS.IF.RXFRAMEDET0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXFRAMEDET1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXFRAMEDET1, self).__init__(register,
            'RXFRAMEDET1', 'MODEM_NS.IF.RXFRAMEDET1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXTIMLOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXTIMLOST, self).__init__(register,
            'RXTIMLOST', 'MODEM_NS.IF.RXTIMLOST', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXPRELOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXPRELOST, self).__init__(register,
            'RXPRELOST', 'MODEM_NS.IF.RXPRELOST', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXFRAMEDETOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXFRAMEDETOF, self).__init__(register,
            'RXFRAMEDETOF', 'MODEM_NS.IF.RXFRAMEDETOF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXTIMNF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXTIMNF, self).__init__(register,
            'RXTIMNF', 'MODEM_NS.IF.RXTIMNF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_FRCTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_FRCTIMOUT, self).__init__(register,
            'FRCTIMOUT', 'MODEM_NS.IF.FRCTIMOUT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_ETS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_ETS, self).__init__(register,
            'ETS', 'MODEM_NS.IF.ETS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_CFGANTPATTRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_CFGANTPATTRD, self).__init__(register,
            'CFGANTPATTRD', 'MODEM_NS.IF.CFGANTPATTRD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXRESTARTRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXRESTARTRSSIMAPRE, self).__init__(register,
            'RXRESTARTRSSIMAPRE', 'MODEM_NS.IF.RXRESTARTRSSIMAPRE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_RXRESTARTRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_RXRESTARTRSSIMASYNC, self).__init__(register,
            'RXRESTARTRSSIMASYNC', 'MODEM_NS.IF.RXRESTARTRSSIMASYNC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_SQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_SQDET, self).__init__(register,
            'SQDET', 'MODEM_NS.IF.SQDET', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_SQNOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_SQNOTDET, self).__init__(register,
            'SQNOTDET', 'MODEM_NS.IF.SQNOTDET', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_ANTDIVRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_ANTDIVRDY, self).__init__(register,
            'ANTDIVRDY', 'MODEM_NS.IF.ANTDIVRDY', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_SOFTRESETDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_SOFTRESETDONE, self).__init__(register,
            'SOFTRESETDONE', 'MODEM_NS.IF.SOFTRESETDONE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_SQPRENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_SQPRENOTDET, self).__init__(register,
            'SQPRENOTDET', 'MODEM_NS.IF.SQPRENOTDET', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_SQFRAMENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_SQFRAMENOTDET, self).__init__(register,
            'SQFRAMENOTDET', 'MODEM_NS.IF.SQFRAMENOTDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IF_SQAFCOUTOFBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IF_SQAFCOUTOFBAND, self).__init__(register,
            'SQAFCOUTOFBAND', 'MODEM_NS.IF.SQAFCOUTOFBAND', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_TXFRAMESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_TXFRAMESENT, self).__init__(register,
            'TXFRAMESENT', 'MODEM_NS.IEN.TXFRAMESENT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_TXSYNCSENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_TXSYNCSENT, self).__init__(register,
            'TXSYNCSENT', 'MODEM_NS.IEN.TXSYNCSENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_TXPRESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_TXPRESENT, self).__init__(register,
            'TXPRESENT', 'MODEM_NS.IEN.TXPRESENT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_TXRAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_TXRAMPDONE, self).__init__(register,
            'TXRAMPDONE', 'MODEM_NS.IEN.TXRAMPDONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_LDTNOARR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_LDTNOARR, self).__init__(register,
            'LDTNOARR', 'MODEM_NS.IEN.LDTNOARR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_PHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_PHDSADET, self).__init__(register,
            'PHDSADET', 'MODEM_NS.IEN.PHDSADET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_PHYUNCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_PHYUNCODEDET, self).__init__(register,
            'PHYUNCODEDET', 'MODEM_NS.IEN.PHYUNCODEDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_PHYCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_PHYCODEDET, self).__init__(register,
            'PHYCODEDET', 'MODEM_NS.IEN.PHYCODEDET', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXTIMDET, self).__init__(register,
            'RXTIMDET', 'MODEM_NS.IEN.RXTIMDET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXPREDET, self).__init__(register,
            'RXPREDET', 'MODEM_NS.IEN.RXPREDET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXFRAMEDET0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXFRAMEDET0, self).__init__(register,
            'RXFRAMEDET0', 'MODEM_NS.IEN.RXFRAMEDET0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXFRAMEDET1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXFRAMEDET1, self).__init__(register,
            'RXFRAMEDET1', 'MODEM_NS.IEN.RXFRAMEDET1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXTIMLOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXTIMLOST, self).__init__(register,
            'RXTIMLOST', 'MODEM_NS.IEN.RXTIMLOST', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXPRELOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXPRELOST, self).__init__(register,
            'RXPRELOST', 'MODEM_NS.IEN.RXPRELOST', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXFRAMEDETOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXFRAMEDETOF, self).__init__(register,
            'RXFRAMEDETOF', 'MODEM_NS.IEN.RXFRAMEDETOF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXTIMNF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXTIMNF, self).__init__(register,
            'RXTIMNF', 'MODEM_NS.IEN.RXTIMNF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_FRCTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_FRCTIMOUT, self).__init__(register,
            'FRCTIMOUT', 'MODEM_NS.IEN.FRCTIMOUT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_ETS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_ETS, self).__init__(register,
            'ETS', 'MODEM_NS.IEN.ETS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_CFGANTPATTRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_CFGANTPATTRD, self).__init__(register,
            'CFGANTPATTRD', 'MODEM_NS.IEN.CFGANTPATTRD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXRESTARTRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXRESTARTRSSIMAPRE, self).__init__(register,
            'RXRESTARTRSSIMAPRE', 'MODEM_NS.IEN.RXRESTARTRSSIMAPRE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_RXRESTARTRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_RXRESTARTRSSIMASYNC, self).__init__(register,
            'RXRESTARTRSSIMASYNC', 'MODEM_NS.IEN.RXRESTARTRSSIMASYNC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_SQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_SQDET, self).__init__(register,
            'SQDET', 'MODEM_NS.IEN.SQDET', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_SQNOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_SQNOTDET, self).__init__(register,
            'SQNOTDET', 'MODEM_NS.IEN.SQNOTDET', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_ANTDIVRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_ANTDIVRDY, self).__init__(register,
            'ANTDIVRDY', 'MODEM_NS.IEN.ANTDIVRDY', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_SOFTRESETDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_SOFTRESETDONE, self).__init__(register,
            'SOFTRESETDONE', 'MODEM_NS.IEN.SOFTRESETDONE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_SQPRENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_SQPRENOTDET, self).__init__(register,
            'SQPRENOTDET', 'MODEM_NS.IEN.SQPRENOTDET', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_SQFRAMENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_SQFRAMENOTDET, self).__init__(register,
            'SQFRAMENOTDET', 'MODEM_NS.IEN.SQFRAMENOTDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IEN_SQAFCOUTOFBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IEN_SQAFCOUTOFBAND, self).__init__(register,
            'SQAFCOUTOFBAND', 'MODEM_NS.IEN.SQAFCOUTOFBAND', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_TXFRAMESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_TXFRAMESENT, self).__init__(register,
            'TXFRAMESENT', 'MODEM_NS.SEQIF.TXFRAMESENT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_TXSYNCSENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_TXSYNCSENT, self).__init__(register,
            'TXSYNCSENT', 'MODEM_NS.SEQIF.TXSYNCSENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_TXPRESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_TXPRESENT, self).__init__(register,
            'TXPRESENT', 'MODEM_NS.SEQIF.TXPRESENT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_TXRAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_TXRAMPDONE, self).__init__(register,
            'TXRAMPDONE', 'MODEM_NS.SEQIF.TXRAMPDONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_LDTNOARR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_LDTNOARR, self).__init__(register,
            'LDTNOARR', 'MODEM_NS.SEQIF.LDTNOARR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_PHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_PHDSADET, self).__init__(register,
            'PHDSADET', 'MODEM_NS.SEQIF.PHDSADET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_PHYUNCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_PHYUNCODEDET, self).__init__(register,
            'PHYUNCODEDET', 'MODEM_NS.SEQIF.PHYUNCODEDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_PHYCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_PHYCODEDET, self).__init__(register,
            'PHYCODEDET', 'MODEM_NS.SEQIF.PHYCODEDET', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXTIMDET, self).__init__(register,
            'RXTIMDET', 'MODEM_NS.SEQIF.RXTIMDET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXPREDET, self).__init__(register,
            'RXPREDET', 'MODEM_NS.SEQIF.RXPREDET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXFRAMEDET0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXFRAMEDET0, self).__init__(register,
            'RXFRAMEDET0', 'MODEM_NS.SEQIF.RXFRAMEDET0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXFRAMEDET1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXFRAMEDET1, self).__init__(register,
            'RXFRAMEDET1', 'MODEM_NS.SEQIF.RXFRAMEDET1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXTIMLOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXTIMLOST, self).__init__(register,
            'RXTIMLOST', 'MODEM_NS.SEQIF.RXTIMLOST', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXPRELOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXPRELOST, self).__init__(register,
            'RXPRELOST', 'MODEM_NS.SEQIF.RXPRELOST', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXFRAMEDETOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXFRAMEDETOF, self).__init__(register,
            'RXFRAMEDETOF', 'MODEM_NS.SEQIF.RXFRAMEDETOF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXTIMNF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXTIMNF, self).__init__(register,
            'RXTIMNF', 'MODEM_NS.SEQIF.RXTIMNF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_FRCTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_FRCTIMOUT, self).__init__(register,
            'FRCTIMOUT', 'MODEM_NS.SEQIF.FRCTIMOUT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_ETS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_ETS, self).__init__(register,
            'ETS', 'MODEM_NS.SEQIF.ETS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_CFGANTPATTRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_CFGANTPATTRD, self).__init__(register,
            'CFGANTPATTRD', 'MODEM_NS.SEQIF.CFGANTPATTRD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXRESTARTRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXRESTARTRSSIMAPRE, self).__init__(register,
            'RXRESTARTRSSIMAPRE', 'MODEM_NS.SEQIF.RXRESTARTRSSIMAPRE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_RXRESTARTRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_RXRESTARTRSSIMASYNC, self).__init__(register,
            'RXRESTARTRSSIMASYNC', 'MODEM_NS.SEQIF.RXRESTARTRSSIMASYNC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_SQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_SQDET, self).__init__(register,
            'SQDET', 'MODEM_NS.SEQIF.SQDET', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_SQNOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_SQNOTDET, self).__init__(register,
            'SQNOTDET', 'MODEM_NS.SEQIF.SQNOTDET', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_ANTDIVRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_ANTDIVRDY, self).__init__(register,
            'ANTDIVRDY', 'MODEM_NS.SEQIF.ANTDIVRDY', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_SOFTRESETDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_SOFTRESETDONE, self).__init__(register,
            'SOFTRESETDONE', 'MODEM_NS.SEQIF.SOFTRESETDONE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_SQPRENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_SQPRENOTDET, self).__init__(register,
            'SQPRENOTDET', 'MODEM_NS.SEQIF.SQPRENOTDET', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_SQFRAMENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_SQFRAMENOTDET, self).__init__(register,
            'SQFRAMENOTDET', 'MODEM_NS.SEQIF.SQFRAMENOTDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIF_SQAFCOUTOFBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIF_SQAFCOUTOFBAND, self).__init__(register,
            'SQAFCOUTOFBAND', 'MODEM_NS.SEQIF.SQAFCOUTOFBAND', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_TXFRAMESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_TXFRAMESENT, self).__init__(register,
            'TXFRAMESENT', 'MODEM_NS.SEQIEN.TXFRAMESENT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_TXSYNCSENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_TXSYNCSENT, self).__init__(register,
            'TXSYNCSENT', 'MODEM_NS.SEQIEN.TXSYNCSENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_TXPRESENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_TXPRESENT, self).__init__(register,
            'TXPRESENT', 'MODEM_NS.SEQIEN.TXPRESENT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_TXRAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_TXRAMPDONE, self).__init__(register,
            'TXRAMPDONE', 'MODEM_NS.SEQIEN.TXRAMPDONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_LDTNOARR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_LDTNOARR, self).__init__(register,
            'LDTNOARR', 'MODEM_NS.SEQIEN.LDTNOARR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_PHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_PHDSADET, self).__init__(register,
            'PHDSADET', 'MODEM_NS.SEQIEN.PHDSADET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_PHYUNCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_PHYUNCODEDET, self).__init__(register,
            'PHYUNCODEDET', 'MODEM_NS.SEQIEN.PHYUNCODEDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_PHYCODEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_PHYCODEDET, self).__init__(register,
            'PHYCODEDET', 'MODEM_NS.SEQIEN.PHYCODEDET', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXTIMDET, self).__init__(register,
            'RXTIMDET', 'MODEM_NS.SEQIEN.RXTIMDET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXPREDET, self).__init__(register,
            'RXPREDET', 'MODEM_NS.SEQIEN.RXPREDET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXFRAMEDET0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXFRAMEDET0, self).__init__(register,
            'RXFRAMEDET0', 'MODEM_NS.SEQIEN.RXFRAMEDET0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXFRAMEDET1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXFRAMEDET1, self).__init__(register,
            'RXFRAMEDET1', 'MODEM_NS.SEQIEN.RXFRAMEDET1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXTIMLOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXTIMLOST, self).__init__(register,
            'RXTIMLOST', 'MODEM_NS.SEQIEN.RXTIMLOST', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXPRELOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXPRELOST, self).__init__(register,
            'RXPRELOST', 'MODEM_NS.SEQIEN.RXPRELOST', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXFRAMEDETOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXFRAMEDETOF, self).__init__(register,
            'RXFRAMEDETOF', 'MODEM_NS.SEQIEN.RXFRAMEDETOF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXTIMNF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXTIMNF, self).__init__(register,
            'RXTIMNF', 'MODEM_NS.SEQIEN.RXTIMNF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_FRCTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_FRCTIMOUT, self).__init__(register,
            'FRCTIMOUT', 'MODEM_NS.SEQIEN.FRCTIMOUT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_ETS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_ETS, self).__init__(register,
            'ETS', 'MODEM_NS.SEQIEN.ETS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_CFGANTPATTRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_CFGANTPATTRD, self).__init__(register,
            'CFGANTPATTRD', 'MODEM_NS.SEQIEN.CFGANTPATTRD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXRESTARTRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXRESTARTRSSIMAPRE, self).__init__(register,
            'RXRESTARTRSSIMAPRE', 'MODEM_NS.SEQIEN.RXRESTARTRSSIMAPRE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_RXRESTARTRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_RXRESTARTRSSIMASYNC, self).__init__(register,
            'RXRESTARTRSSIMASYNC', 'MODEM_NS.SEQIEN.RXRESTARTRSSIMASYNC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_SQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_SQDET, self).__init__(register,
            'SQDET', 'MODEM_NS.SEQIEN.SQDET', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_SQNOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_SQNOTDET, self).__init__(register,
            'SQNOTDET', 'MODEM_NS.SEQIEN.SQNOTDET', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_ANTDIVRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_ANTDIVRDY, self).__init__(register,
            'ANTDIVRDY', 'MODEM_NS.SEQIEN.ANTDIVRDY', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_SOFTRESETDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_SOFTRESETDONE, self).__init__(register,
            'SOFTRESETDONE', 'MODEM_NS.SEQIEN.SOFTRESETDONE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_SQPRENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_SQPRENOTDET, self).__init__(register,
            'SQPRENOTDET', 'MODEM_NS.SEQIEN.SQPRENOTDET', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_SQFRAMENOTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_SQFRAMENOTDET, self).__init__(register,
            'SQFRAMENOTDET', 'MODEM_NS.SEQIEN.SQFRAMENOTDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SEQIEN_SQAFCOUTOFBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SEQIEN_SQAFCOUTOFBAND, self).__init__(register,
            'SQAFCOUTOFBAND', 'MODEM_NS.SEQIEN.SQAFCOUTOFBAND', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_DEMODSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_DEMODSTATE, self).__init__(register,
            'DEMODSTATE', 'MODEM_NS.STATUS.DEMODSTATE', 'read-only',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_BCRCFEDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_BCRCFEDSADET, self).__init__(register,
            'BCRCFEDSADET', 'MODEM_NS.STATUS.BCRCFEDSADET', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_FRAMEDETID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_FRAMEDETID, self).__init__(register,
            'FRAMEDETID', 'MODEM_NS.STATUS.FRAMEDETID', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_ANTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_ANTSEL, self).__init__(register,
            'ANTSEL', 'MODEM_NS.STATUS.ANTSEL', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_TIMSEQINV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_TIMSEQINV, self).__init__(register,
            'TIMSEQINV', 'MODEM_NS.STATUS.TIMSEQINV', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_TIMLOSTCAUSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_TIMLOSTCAUSE, self).__init__(register,
            'TIMLOSTCAUSE', 'MODEM_NS.STATUS.TIMLOSTCAUSE', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_DSADETECTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_DSADETECTED, self).__init__(register,
            'DSADETECTED', 'MODEM_NS.STATUS.DSADETECTED', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_DSAFREQESTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_DSAFREQESTDONE, self).__init__(register,
            'DSAFREQESTDONE', 'MODEM_NS.STATUS.DSAFREQESTDONE', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_VITERBIDEMODTIMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_VITERBIDEMODTIMDET, self).__init__(register,
            'VITERBIDEMODTIMDET', 'MODEM_NS.STATUS.VITERBIDEMODTIMDET', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_VITERBIDEMODFRAMEDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_VITERBIDEMODFRAMEDET, self).__init__(register,
            'VITERBIDEMODFRAMEDET', 'MODEM_NS.STATUS.VITERBIDEMODFRAMEDET', 'read-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_STAMPSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_STAMPSTATE, self).__init__(register,
            'STAMPSTATE', 'MODEM_NS.STATUS.STAMPSTATE', 'read-only',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_TRECSDSAADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_TRECSDSAADET, self).__init__(register,
            'TRECSDSAADET', 'MODEM_NS.STATUS.TRECSDSAADET', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_CORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_CORR, self).__init__(register,
            'CORR', 'MODEM_NS.STATUS.CORR', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS_WEAKSYMBOLS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS_WEAKSYMBOLS, self).__init__(register,
            'WEAKSYMBOLS', 'MODEM_NS.STATUS.WEAKSYMBOLS', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS2_CHPWRACCUMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS2_CHPWRACCUMUX, self).__init__(register,
            'CHPWRACCUMUX', 'MODEM_NS.STATUS2.CHPWRACCUMUX', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS2_BBSSMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS2_BBSSMUX, self).__init__(register,
            'BBSSMUX', 'MODEM_NS.STATUS2.BBSSMUX', 'read-only',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS2_LRBLECI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS2_LRBLECI, self).__init__(register,
            'LRBLECI', 'MODEM_NS.STATUS2.LRBLECI', 'read-only',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS2_UNCODEDPHY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS2_UNCODEDPHY, self).__init__(register,
            'UNCODEDPHY', 'MODEM_NS.STATUS2.UNCODEDPHY', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS2_CODEDPHY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS2_CODEDPHY, self).__init__(register,
            'CODEDPHY', 'MODEM_NS.STATUS2.CODEDPHY', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS2_RTCOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS2_RTCOST, self).__init__(register,
            'RTCOST', 'MODEM_NS.STATUS2.RTCOST', 'read-only',
            u"",
            18, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS3_BBPFOUTABS1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS3_BBPFOUTABS1, self).__init__(register,
            'BBPFOUTABS1', 'MODEM_NS.STATUS3.BBPFOUTABS1', 'read-only',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS3_BBPFOUTABS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS3_BBPFOUTABS, self).__init__(register,
            'BBPFOUTABS', 'MODEM_NS.STATUS3.BBPFOUTABS', 'read-only',
            u"",
            11, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS3_LRDSALIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS3_LRDSALIVE, self).__init__(register,
            'LRDSALIVE', 'MODEM_NS.STATUS3.LRDSALIVE', 'read-only',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS3_COHDSALIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS3_COHDSALIVE, self).__init__(register,
            'COHDSALIVE', 'MODEM_NS.STATUS3.COHDSALIVE', 'read-only',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS3_LRDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS3_LRDSADET, self).__init__(register,
            'LRDSADET', 'MODEM_NS.STATUS3.LRDSADET', 'read-only',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS3_COHDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS3_COHDSADET, self).__init__(register,
            'COHDSADET', 'MODEM_NS.STATUS3.COHDSADET', 'read-only',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS3_SYNCSECPEAKABTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS3_SYNCSECPEAKABTH, self).__init__(register,
            'SYNCSECPEAKABTH', 'MODEM_NS.STATUS3.SYNCSECPEAKABTH', 'read-only',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS3_SOFTRSTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS3_SOFTRSTDONE, self).__init__(register,
            'SOFTRSTDONE', 'MODEM_NS.STATUS3.SOFTRSTDONE', 'read-only',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS4_ANT0RSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS4_ANT0RSSI, self).__init__(register,
            'ANT0RSSI', 'MODEM_NS.STATUS4.ANT0RSSI', 'read-only',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS4_ANT1RSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS4_ANT1RSSI, self).__init__(register,
            'ANT1RSSI', 'MODEM_NS.STATUS4.ANT1RSSI', 'read-only',
            u"",
            16, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS5_RXRESTARTMAFLTDOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS5_RXRESTARTMAFLTDOUT, self).__init__(register,
            'RXRESTARTMAFLTDOUT', 'MODEM_NS.STATUS5.RXRESTARTMAFLTDOUT', 'read-only',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS6_ANT0CORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS6_ANT0CORR, self).__init__(register,
            'ANT0CORR', 'MODEM_NS.STATUS6.ANT0CORR', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS6_ANT1CORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS6_ANT1CORR, self).__init__(register,
            'ANT1CORR', 'MODEM_NS.STATUS6.ANT1CORR', 'read-only',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS6_ANT0OUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS6_ANT0OUT, self).__init__(register,
            'ANT0OUT', 'MODEM_NS.STATUS6.ANT0OUT', 'read-only',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS6_ANT1OUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS6_ANT1OUT, self).__init__(register,
            'ANT1OUT', 'MODEM_NS.STATUS6.ANT1OUT', 'read-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS7_FDEVEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS7_FDEVEST, self).__init__(register,
            'FDEVEST', 'MODEM_NS.STATUS7.FDEVEST', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS7_DEMODSOFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS7_DEMODSOFT, self).__init__(register,
            'DEMODSOFT', 'MODEM_NS.STATUS7.DEMODSOFT', 'read-only',
            u"",
            6, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS7_CFEPHDIFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS7_CFEPHDIFF, self).__init__(register,
            'CFEPHDIFF', 'MODEM_NS.STATUS7.CFEPHDIFF', 'read-only',
            u"",
            19, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS7_MINCOSTPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS7_MINCOSTPASS, self).__init__(register,
            'MINCOSTPASS', 'MODEM_NS.STATUS7.MINCOSTPASS', 'read-only',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_STATUS7_CFEDSADET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_STATUS7_CFEDSADET, self).__init__(register,
            'CFEDSADET', 'MODEM_NS.STATUS7.CFEDSADET', 'read-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETCORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETCORR, self).__init__(register,
            'TIMDETCORR', 'MODEM_NS.TIMDETSTATUS.TIMDETCORR', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETFREQOFFEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETFREQOFFEST, self).__init__(register,
            'TIMDETFREQOFFEST', 'MODEM_NS.TIMDETSTATUS.TIMDETFREQOFFEST', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETPREERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETPREERRORS, self).__init__(register,
            'TIMDETPREERRORS', 'MODEM_NS.TIMDETSTATUS.TIMDETPREERRORS', 'read-only',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETPASS, self).__init__(register,
            'TIMDETPASS', 'MODEM_NS.TIMDETSTATUS.TIMDETPASS', 'read-only',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETINDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETINDEX, self).__init__(register,
            'TIMDETINDEX', 'MODEM_NS.TIMDETSTATUS.TIMDETINDEX', 'read-only',
            u"",
            25, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FSMSTATUS_DETSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FSMSTATUS_DETSTATE, self).__init__(register,
            'DETSTATE', 'MODEM_NS.FSMSTATUS.DETSTATE', 'read-only',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FSMSTATUS_DSASTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FSMSTATUS_DSASTATE, self).__init__(register,
            'DSASTATE', 'MODEM_NS.FSMSTATUS.DSASTATE', 'read-only',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FSMSTATUS_LRBLESTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FSMSTATUS_LRBLESTATE, self).__init__(register,
            'LRBLESTATE', 'MODEM_NS.FSMSTATUS.LRBLESTATE', 'read-only',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FSMSTATUS_NBBLESTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FSMSTATUS_NBBLESTATE, self).__init__(register,
            'NBBLESTATE', 'MODEM_NS.FSMSTATUS.NBBLESTATE', 'read-only',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FSMSTATUS_ANTDIVSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FSMSTATUS_ANTDIVSTATE, self).__init__(register,
            'ANTDIVSTATE', 'MODEM_NS.FSMSTATUS.ANTDIVSTATE', 'read-only',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FREQOFFEST_FREQOFFEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FREQOFFEST_FREQOFFEST, self).__init__(register,
            'FREQOFFEST', 'MODEM_NS.FREQOFFEST.FREQOFFEST', 'read-only',
            u"",
            0, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FREQOFFEST_CORRVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FREQOFFEST_CORRVAL, self).__init__(register,
            'CORRVAL', 'MODEM_NS.FREQOFFEST.CORRVAL', 'read-only',
            u"",
            13, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FREQOFFEST_SOFTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FREQOFFEST_SOFTVAL, self).__init__(register,
            'SOFTVAL', 'MODEM_NS.FREQOFFEST.SOFTVAL', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFCADJRX_AFCADJRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFCADJRX_AFCADJRX, self).__init__(register,
            'AFCADJRX', 'MODEM_NS.AFCADJRX.AFCADJRX', 'read-only',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFCADJRX_AFCSCALEM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFCADJRX_AFCSCALEM, self).__init__(register,
            'AFCSCALEM', 'MODEM_NS.AFCADJRX.AFCSCALEM', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFCADJRX_AFCSCALEE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFCADJRX_AFCSCALEE, self).__init__(register,
            'AFCSCALEE', 'MODEM_NS.AFCADJRX.AFCSCALEE', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFCADJTX_AFCADJTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFCADJTX_AFCADJTX, self).__init__(register,
            'AFCADJTX', 'MODEM_NS.AFCADJTX.AFCADJTX', 'read-only',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFCADJTX_AFCSCALEM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFCADJTX_AFCSCALEM, self).__init__(register,
            'AFCSCALEM', 'MODEM_NS.AFCADJTX.AFCSCALEM', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFCADJTX_AFCSCALEE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFCADJTX_AFCSCALEE, self).__init__(register,
            'AFCSCALEE', 'MODEM_NS.AFCADJTX.AFCSCALEE', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_MIXCTRL_DIGIQSWAPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_MIXCTRL_DIGIQSWAPEN, self).__init__(register,
            'DIGIQSWAPEN', 'MODEM_NS.MIXCTRL.DIGIQSWAPEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_FDM0DIFFDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_FDM0DIFFDIS, self).__init__(register,
            'FDM0DIFFDIS', 'MODEM_NS.CTRL0.FDM0DIFFDIS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_MAPFSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_MAPFSK, self).__init__(register,
            'MAPFSK', 'MODEM_NS.CTRL0.MAPFSK', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_CODING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_CODING, self).__init__(register,
            'CODING', 'MODEM_NS.CTRL0.CODING', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_MODFORMAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_MODFORMAT, self).__init__(register,
            'MODFORMAT', 'MODEM_NS.CTRL0.MODFORMAT', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_DUALCORROPTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_DUALCORROPTDIS, self).__init__(register,
            'DUALCORROPTDIS', 'MODEM_NS.CTRL0.DUALCORROPTDIS', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_OOKASYNCPIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_OOKASYNCPIN, self).__init__(register,
            'OOKASYNCPIN', 'MODEM_NS.CTRL0.OOKASYNCPIN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_DSSSLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_DSSSLEN, self).__init__(register,
            'DSSSLEN', 'MODEM_NS.CTRL0.DSSSLEN', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_DSSSSHIFTS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_DSSSSHIFTS, self).__init__(register,
            'DSSSSHIFTS', 'MODEM_NS.CTRL0.DSSSSHIFTS', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_DSSSDOUBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_DSSSDOUBLE, self).__init__(register,
            'DSSSDOUBLE', 'MODEM_NS.CTRL0.DSSSDOUBLE', 'read-write',
            u"",
            19, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_DETDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_DETDIS, self).__init__(register,
            'DETDIS', 'MODEM_NS.CTRL0.DETDIS', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_DIFFENCMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_DIFFENCMODE, self).__init__(register,
            'DIFFENCMODE', 'MODEM_NS.CTRL0.DIFFENCMODE', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_SHAPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_SHAPING, self).__init__(register,
            'SHAPING', 'MODEM_NS.CTRL0.SHAPING', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_DEMODRAWDATASEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_DEMODRAWDATASEL, self).__init__(register,
            'DEMODRAWDATASEL', 'MODEM_NS.CTRL0.DEMODRAWDATASEL', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL0_FRAMEDETDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL0_FRAMEDETDEL, self).__init__(register,
            'FRAMEDETDEL', 'MODEM_NS.CTRL0.FRAMEDETDEL', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_SYNCBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_SYNCBITS, self).__init__(register,
            'SYNCBITS', 'MODEM_NS.CTRL1.SYNCBITS', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_SYNCERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_SYNCERRORS, self).__init__(register,
            'SYNCERRORS', 'MODEM_NS.CTRL1.SYNCERRORS', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_DUALSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_DUALSYNC, self).__init__(register,
            'DUALSYNC', 'MODEM_NS.CTRL1.DUALSYNC', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_TXSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_TXSYNC, self).__init__(register,
            'TXSYNC', 'MODEM_NS.CTRL1.TXSYNC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_SYNCDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_SYNCDATA, self).__init__(register,
            'SYNCDATA', 'MODEM_NS.CTRL1.SYNCDATA', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_SYNC1INV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_SYNC1INV, self).__init__(register,
            'SYNC1INV', 'MODEM_NS.CTRL1.SYNC1INV', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_COMPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_COMPMODE, self).__init__(register,
            'COMPMODE', 'MODEM_NS.CTRL1.COMPMODE', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_RESYNCPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_RESYNCPER, self).__init__(register,
            'RESYNCPER', 'MODEM_NS.CTRL1.RESYNCPER', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_PHASEDEMOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_PHASEDEMOD, self).__init__(register,
            'PHASEDEMOD', 'MODEM_NS.CTRL1.PHASEDEMOD', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_FREQOFFESTPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_FREQOFFESTPER, self).__init__(register,
            'FREQOFFESTPER', 'MODEM_NS.CTRL1.FREQOFFESTPER', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL1_FREQOFFESTLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL1_FREQOFFESTLIM, self).__init__(register,
            'FREQOFFESTLIM', 'MODEM_NS.CTRL1.FREQOFFESTLIM', 'read-write',
            u"",
            25, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_SQITHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_SQITHRESH, self).__init__(register,
            'SQITHRESH', 'MODEM_NS.CTRL2.SQITHRESH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_RXFRCDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_RXFRCDIS, self).__init__(register,
            'RXFRCDIS', 'MODEM_NS.CTRL2.RXFRCDIS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_RXPINMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_RXPINMODE, self).__init__(register,
            'RXPINMODE', 'MODEM_NS.CTRL2.RXPINMODE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_TXPINMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_TXPINMODE, self).__init__(register,
            'TXPINMODE', 'MODEM_NS.CTRL2.TXPINMODE', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_DATAFILTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_DATAFILTER, self).__init__(register,
            'DATAFILTER', 'MODEM_NS.CTRL2.DATAFILTER', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_BRDIVA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_BRDIVA, self).__init__(register,
            'BRDIVA', 'MODEM_NS.CTRL2.BRDIVA', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_BRDIVB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_BRDIVB, self).__init__(register,
            'BRDIVB', 'MODEM_NS.CTRL2.BRDIVB', 'read-write',
            u"",
            19, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_DEVMULA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_DEVMULA, self).__init__(register,
            'DEVMULA', 'MODEM_NS.CTRL2.DEVMULA', 'read-write',
            u"",
            23, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_DEVMULB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_DEVMULB, self).__init__(register,
            'DEVMULB', 'MODEM_NS.CTRL2.DEVMULB', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_RATESELMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_RATESELMODE, self).__init__(register,
            'RATESELMODE', 'MODEM_NS.CTRL2.RATESELMODE', 'read-write',
            u"",
            27, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_DEVWEIGHTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_DEVWEIGHTDIS, self).__init__(register,
            'DEVWEIGHTDIS', 'MODEM_NS.CTRL2.DEVWEIGHTDIS', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL2_DMASEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL2_DMASEL, self).__init__(register,
            'DMASEL', 'MODEM_NS.CTRL2.DMASEL', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL3_PRSDINEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL3_PRSDINEN, self).__init__(register,
            'PRSDINEN', 'MODEM_NS.CTRL3.PRSDINEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL3_TIMINGBASESGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL3_TIMINGBASESGAIN, self).__init__(register,
            'TIMINGBASESGAIN', 'MODEM_NS.CTRL3.TIMINGBASESGAIN', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL3_RAMTESTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL3_RAMTESTEN, self).__init__(register,
            'RAMTESTEN', 'MODEM_NS.CTRL3.RAMTESTEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL3_ANTDIVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL3_ANTDIVMODE, self).__init__(register,
            'ANTDIVMODE', 'MODEM_NS.CTRL3.ANTDIVMODE', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL3_ANTDIVREPEATDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL3_ANTDIVREPEATDIS, self).__init__(register,
            'ANTDIVREPEATDIS', 'MODEM_NS.CTRL3.ANTDIVREPEATDIS', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL3_TSAMPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL3_TSAMPMODE, self).__init__(register,
            'TSAMPMODE', 'MODEM_NS.CTRL3.TSAMPMODE', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL3_TSAMPDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL3_TSAMPDEL, self).__init__(register,
            'TSAMPDEL', 'MODEM_NS.CTRL3.TSAMPDEL', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL3_TSAMPLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL3_TSAMPLIM, self).__init__(register,
            'TSAMPLIM', 'MODEM_NS.CTRL3.TSAMPLIM', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_ISICOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_ISICOMP, self).__init__(register,
            'ISICOMP', 'MODEM_NS.CTRL4.ISICOMP', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_DEVOFFCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_DEVOFFCOMP, self).__init__(register,
            'DEVOFFCOMP', 'MODEM_NS.CTRL4.DEVOFFCOMP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_PREDISTGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_PREDISTGAIN, self).__init__(register,
            'PREDISTGAIN', 'MODEM_NS.CTRL4.PREDISTGAIN', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_PREDISTDEB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_PREDISTDEB, self).__init__(register,
            'PREDISTDEB', 'MODEM_NS.CTRL4.PREDISTDEB', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_PREDISTAVG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_PREDISTAVG, self).__init__(register,
            'PREDISTAVG', 'MODEM_NS.CTRL4.PREDISTAVG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_PREDISTRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_PREDISTRST, self).__init__(register,
            'PREDISTRST', 'MODEM_NS.CTRL4.PREDISTRST', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_PHASECLICKFILT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_PHASECLICKFILT, self).__init__(register,
            'PHASECLICKFILT', 'MODEM_NS.CTRL4.PHASECLICKFILT', 'read-write',
            u"",
            15, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_SOFTDSSSMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_SOFTDSSSMODE, self).__init__(register,
            'SOFTDSSSMODE', 'MODEM_NS.CTRL4.SOFTDSSSMODE', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_ADCSATLEVEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_ADCSATLEVEL, self).__init__(register,
            'ADCSATLEVEL', 'MODEM_NS.CTRL4.ADCSATLEVEL', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_ADCSATDENS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_ADCSATDENS, self).__init__(register,
            'ADCSATDENS', 'MODEM_NS.CTRL4.ADCSATDENS', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_OFFSETPHASEMASKING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_OFFSETPHASEMASKING, self).__init__(register,
            'OFFSETPHASEMASKING', 'MODEM_NS.CTRL4.OFFSETPHASEMASKING', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_OFFSETPHASESCALING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_OFFSETPHASESCALING, self).__init__(register,
            'OFFSETPHASESCALING', 'MODEM_NS.CTRL4.OFFSETPHASESCALING', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL4_CLKUNDIVREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL4_CLKUNDIVREQ, self).__init__(register,
            'CLKUNDIVREQ', 'MODEM_NS.CTRL4.CLKUNDIVREQ', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_BRCALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_BRCALEN, self).__init__(register,
            'BRCALEN', 'MODEM_NS.CTRL5.BRCALEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_BRCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_BRCALMODE, self).__init__(register,
            'BRCALMODE', 'MODEM_NS.CTRL5.BRCALMODE', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_BRCALAVG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_BRCALAVG, self).__init__(register,
            'BRCALAVG', 'MODEM_NS.CTRL5.BRCALAVG', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_DETDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_DETDEL, self).__init__(register,
            'DETDEL', 'MODEM_NS.CTRL5.DETDEL', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_TDEDGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_TDEDGE, self).__init__(register,
            'TDEDGE', 'MODEM_NS.CTRL5.TDEDGE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_TREDGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_TREDGE, self).__init__(register,
            'TREDGE', 'MODEM_NS.CTRL5.TREDGE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_DSSSCTD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_DSSSCTD, self).__init__(register,
            'DSSSCTD', 'MODEM_NS.CTRL5.DSSSCTD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_BBSS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_BBSS, self).__init__(register,
            'BBSS', 'MODEM_NS.CTRL5.BBSS', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_POEPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_POEPER, self).__init__(register,
            'POEPER', 'MODEM_NS.CTRL5.POEPER', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_DEMODRAWDATASEL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_DEMODRAWDATASEL2, self).__init__(register,
            'DEMODRAWDATASEL2', 'MODEM_NS.CTRL5.DEMODRAWDATASEL2', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_FOEPREAVG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_FOEPREAVG, self).__init__(register,
            'FOEPREAVG', 'MODEM_NS.CTRL5.FOEPREAVG', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_LINCORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_LINCORR, self).__init__(register,
            'LINCORR', 'MODEM_NS.CTRL5.LINCORR', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_RESYNCBAUDTRANS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_RESYNCBAUDTRANS, self).__init__(register,
            'RESYNCBAUDTRANS', 'MODEM_NS.CTRL5.RESYNCBAUDTRANS', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL5_RESYNCLIMIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL5_RESYNCLIMIT, self).__init__(register,
            'RESYNCLIMIT', 'MODEM_NS.CTRL5.RESYNCLIMIT', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_TDREW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_TDREW, self).__init__(register,
            'TDREW', 'MODEM_NS.CTRL6.TDREW', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_PREBASES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_PREBASES, self).__init__(register,
            'PREBASES', 'MODEM_NS.CTRL6.PREBASES', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_PSTIMABORT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_PSTIMABORT0, self).__init__(register,
            'PSTIMABORT0', 'MODEM_NS.CTRL6.PSTIMABORT0', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_PSTIMABORT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_PSTIMABORT1, self).__init__(register,
            'PSTIMABORT1', 'MODEM_NS.CTRL6.PSTIMABORT1', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_PSTIMABORT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_PSTIMABORT2, self).__init__(register,
            'PSTIMABORT2', 'MODEM_NS.CTRL6.PSTIMABORT2', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_PSTIMABORT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_PSTIMABORT3, self).__init__(register,
            'PSTIMABORT3', 'MODEM_NS.CTRL6.PSTIMABORT3', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_ARW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_ARW, self).__init__(register,
            'ARW', 'MODEM_NS.CTRL6.ARW', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_TIMTHRESHGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_TIMTHRESHGAIN, self).__init__(register,
            'TIMTHRESHGAIN', 'MODEM_NS.CTRL6.TIMTHRESHGAIN', 'read-write',
            u"",
            17, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_CPLXCORREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_CPLXCORREN, self).__init__(register,
            'CPLXCORREN', 'MODEM_NS.CTRL6.CPLXCORREN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_DSSS3SYMBOLSYNCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_DSSS3SYMBOLSYNCEN, self).__init__(register,
            'DSSS3SYMBOLSYNCEN', 'MODEM_NS.CTRL6.DSSS3SYMBOLSYNCEN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_TXDBPSKINV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_TXDBPSKINV, self).__init__(register,
            'TXDBPSKINV', 'MODEM_NS.CTRL6.TXDBPSKINV', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_TXDBPSKRAMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_TXDBPSKRAMPEN, self).__init__(register,
            'TXDBPSKRAMPEN', 'MODEM_NS.CTRL6.TXDBPSKRAMPEN', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_CODINGB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_CODINGB, self).__init__(register,
            'CODINGB', 'MODEM_NS.CTRL6.CODINGB', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_RXRESTARTUPONRSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_RXRESTARTUPONRSSI, self).__init__(register,
            'RXRESTARTUPONRSSI', 'MODEM_NS.CTRL6.RXRESTARTUPONRSSI', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_RXRESTARTUPONSHORTRSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_RXRESTARTUPONSHORTRSSI, self).__init__(register,
            'RXRESTARTUPONSHORTRSSI', 'MODEM_NS.CTRL6.RXRESTARTUPONSHORTRSSI', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_RXBRCALCDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_RXBRCALCDIS, self).__init__(register,
            'RXBRCALCDIS', 'MODEM_NS.CTRL6.RXBRCALCDIS', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CTRL6_DEMODRESTARTALL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CTRL6_DEMODRESTARTALL, self).__init__(register,
            'DEMODRESTARTALL', 'MODEM_NS.CTRL6.DEMODRESTARTALL', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TXBR_TXBRNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TXBR_TXBRNUM, self).__init__(register,
            'TXBRNUM', 'MODEM_NS.TXBR.TXBRNUM', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TXBR_TXBRDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TXBR_TXBRDEN, self).__init__(register,
            'TXBRDEN', 'MODEM_NS.TXBR.TXBRDEN', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXBR_RXBRNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXBR_RXBRNUM, self).__init__(register,
            'RXBRNUM', 'MODEM_NS.RXBR.RXBRNUM', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXBR_RXBRDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXBR_RXBRDEN, self).__init__(register,
            'RXBRDEN', 'MODEM_NS.RXBR.RXBRDEN', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXBR_RXBRINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXBR_RXBRINT, self).__init__(register,
            'RXBRINT', 'MODEM_NS.RXBR.RXBRINT', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CF_DEC0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CF_DEC0, self).__init__(register,
            'DEC0', 'MODEM_NS.CF.DEC0', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CF_DEC1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CF_DEC1, self).__init__(register,
            'DEC1', 'MODEM_NS.CF.DEC1', 'read-write',
            u"",
            3, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CF_DEC2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CF_DEC2, self).__init__(register,
            'DEC2', 'MODEM_NS.CF.DEC2', 'read-write',
            u"",
            17, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CF_CFOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CF_CFOSR, self).__init__(register,
            'CFOSR', 'MODEM_NS.CF.CFOSR', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CF_DEC1GAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CF_DEC1GAIN, self).__init__(register,
            'DEC1GAIN', 'MODEM_NS.CF.DEC1GAIN', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CF_ADCBITORDERI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CF_ADCBITORDERI, self).__init__(register,
            'ADCBITORDERI', 'MODEM_NS.CF.ADCBITORDERI', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CF_ADCBITORDERQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CF_ADCBITORDERQ, self).__init__(register,
            'ADCBITORDERQ', 'MODEM_NS.CF.ADCBITORDERQ', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_BASE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_BASE, self).__init__(register,
            'BASE', 'MODEM_NS.PRE.BASE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_BASEBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_BASEBITS, self).__init__(register,
            'BASEBITS', 'MODEM_NS.PRE.BASEBITS', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_PRESYMB4FSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_PRESYMB4FSK, self).__init__(register,
            'PRESYMB4FSK', 'MODEM_NS.PRE.PRESYMB4FSK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_PREERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_PREERRORS, self).__init__(register,
            'PREERRORS', 'MODEM_NS.PRE.PREERRORS', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_DSSSPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_DSSSPRE, self).__init__(register,
            'DSSSPRE', 'MODEM_NS.PRE.DSSSPRE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_SYNCSYMB4FSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_SYNCSYMB4FSK, self).__init__(register,
            'SYNCSYMB4FSK', 'MODEM_NS.PRE.SYNCSYMB4FSK', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_PREAMBDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_PREAMBDETEN, self).__init__(register,
            'PREAMBDETEN', 'MODEM_NS.PRE.PREAMBDETEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_PREWNDERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_PREWNDERRORS, self).__init__(register,
            'PREWNDERRORS', 'MODEM_NS.PRE.PREWNDERRORS', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRE_TXBASES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRE_TXBASES, self).__init__(register,
            'TXBASES', 'MODEM_NS.PRE.TXBASES', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SYNC0_SYNC0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SYNC0_SYNC0, self).__init__(register,
            'SYNC0', 'MODEM_NS.SYNC0.SYNC0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SYNC1_SYNC1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SYNC1_SYNC1, self).__init__(register,
            'SYNC1', 'MODEM_NS.SYNC1.SYNC1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_TIMTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_TIMTHRESH, self).__init__(register,
            'TIMTHRESH', 'MODEM_NS.TIMING.TIMTHRESH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_TIMINGBASES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_TIMINGBASES, self).__init__(register,
            'TIMINGBASES', 'MODEM_NS.TIMING.TIMINGBASES', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_ADDTIMSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_ADDTIMSEQ, self).__init__(register,
            'ADDTIMSEQ', 'MODEM_NS.TIMING.ADDTIMSEQ', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_TIMSEQINVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_TIMSEQINVEN, self).__init__(register,
            'TIMSEQINVEN', 'MODEM_NS.TIMING.TIMSEQINVEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_TIMSEQSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_TIMSEQSYNC, self).__init__(register,
            'TIMSEQSYNC', 'MODEM_NS.TIMING.TIMSEQSYNC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_FDM0THRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_FDM0THRESH, self).__init__(register,
            'FDM0THRESH', 'MODEM_NS.TIMING.FDM0THRESH', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_OFFSUBNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_OFFSUBNUM, self).__init__(register,
            'OFFSUBNUM', 'MODEM_NS.TIMING.OFFSUBNUM', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_OFFSUBDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_OFFSUBDEN, self).__init__(register,
            'OFFSUBDEN', 'MODEM_NS.TIMING.OFFSUBDEN', 'read-write',
            u"",
            25, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_TSAGCDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_TSAGCDEL, self).__init__(register,
            'TSAGCDEL', 'MODEM_NS.TIMING.TSAGCDEL', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TIMING_FASTRESYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TIMING_FASTRESYNC, self).__init__(register,
            'FASTRESYNC', 'MODEM_NS.TIMING.FASTRESYNC', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSSS0_DSSS0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSSS0_DSSS0, self).__init__(register,
            'DSSS0', 'MODEM_NS.DSSS0.DSSS0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_MODINDEX_MODINDEXM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_MODINDEX_MODINDEXM, self).__init__(register,
            'MODINDEXM', 'MODEM_NS.MODINDEX.MODINDEXM', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_MODINDEX_MODINDEXE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_MODINDEX_MODINDEXE, self).__init__(register,
            'MODINDEXE', 'MODEM_NS.MODINDEX.MODINDEXE', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_MODINDEX_FREQGAINE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_MODINDEX_FREQGAINE, self).__init__(register,
            'FREQGAINE', 'MODEM_NS.MODINDEX.FREQGAINE', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_MODINDEX_FREQGAINM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_MODINDEX_FREQGAINM, self).__init__(register,
            'FREQGAINM', 'MODEM_NS.MODINDEX.FREQGAINM', 'read-write',
            u"",
            19, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCRXMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCRXMODE, self).__init__(register,
            'AFCRXMODE', 'MODEM_NS.AFC.AFCRXMODE', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCTXMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCTXMODE, self).__init__(register,
            'AFCTXMODE', 'MODEM_NS.AFC.AFCTXMODE', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCRXCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCRXCLR, self).__init__(register,
            'AFCRXCLR', 'MODEM_NS.AFC.AFCRXCLR', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCDEL, self).__init__(register,
            'AFCDEL', 'MODEM_NS.AFC.AFCDEL', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCAVGPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCAVGPER, self).__init__(register,
            'AFCAVGPER', 'MODEM_NS.AFC.AFCAVGPER', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCLIMRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCLIMRESET, self).__init__(register,
            'AFCLIMRESET', 'MODEM_NS.AFC.AFCLIMRESET', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCONESHOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCONESHOT, self).__init__(register,
            'AFCONESHOT', 'MODEM_NS.AFC.AFCONESHOT', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCENINTCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCENINTCOMP, self).__init__(register,
            'AFCENINTCOMP', 'MODEM_NS.AFC.AFCENINTCOMP', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCDSAFREQOFFEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCDSAFREQOFFEST, self).__init__(register,
            'AFCDSAFREQOFFEST', 'MODEM_NS.AFC.AFCDSAFREQOFFEST', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCDELDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCDELDET, self).__init__(register,
            'AFCDELDET', 'MODEM_NS.AFC.AFCDELDET', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFC_AFCGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFC_AFCGEAR, self).__init__(register,
            'AFCGEAR', 'MODEM_NS.AFC.AFCGEAR', 'read-write',
            u"",
            29, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AFCADJLIM_AFCADJLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AFCADJLIM_AFCADJLIM, self).__init__(register,
            'AFCADJLIM', 'MODEM_NS.AFCADJLIM.AFCADJLIM', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING0_COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING0_COEFF0, self).__init__(register,
            'COEFF0', 'MODEM_NS.SHAPING0.COEFF0', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING0_COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING0_COEFF1, self).__init__(register,
            'COEFF1', 'MODEM_NS.SHAPING0.COEFF1', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING0_COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING0_COEFF2, self).__init__(register,
            'COEFF2', 'MODEM_NS.SHAPING0.COEFF2', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING0_COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING0_COEFF3, self).__init__(register,
            'COEFF3', 'MODEM_NS.SHAPING0.COEFF3', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING1_COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING1_COEFF4, self).__init__(register,
            'COEFF4', 'MODEM_NS.SHAPING1.COEFF4', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING1_COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING1_COEFF5, self).__init__(register,
            'COEFF5', 'MODEM_NS.SHAPING1.COEFF5', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING1_COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING1_COEFF6, self).__init__(register,
            'COEFF6', 'MODEM_NS.SHAPING1.COEFF6', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING1_COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING1_COEFF7, self).__init__(register,
            'COEFF7', 'MODEM_NS.SHAPING1.COEFF7', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING2_COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING2_COEFF8, self).__init__(register,
            'COEFF8', 'MODEM_NS.SHAPING2.COEFF8', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING2_COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING2_COEFF9, self).__init__(register,
            'COEFF9', 'MODEM_NS.SHAPING2.COEFF9', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING2_COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING2_COEFF10, self).__init__(register,
            'COEFF10', 'MODEM_NS.SHAPING2.COEFF10', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING2_COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING2_COEFF11, self).__init__(register,
            'COEFF11', 'MODEM_NS.SHAPING2.COEFF11', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING3_COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING3_COEFF12, self).__init__(register,
            'COEFF12', 'MODEM_NS.SHAPING3.COEFF12', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING3_COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING3_COEFF13, self).__init__(register,
            'COEFF13', 'MODEM_NS.SHAPING3.COEFF13', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING3_COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING3_COEFF14, self).__init__(register,
            'COEFF14', 'MODEM_NS.SHAPING3.COEFF14', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING3_COEFF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING3_COEFF15, self).__init__(register,
            'COEFF15', 'MODEM_NS.SHAPING3.COEFF15', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING4_COEFF16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING4_COEFF16, self).__init__(register,
            'COEFF16', 'MODEM_NS.SHAPING4.COEFF16', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING4_COEFF17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING4_COEFF17, self).__init__(register,
            'COEFF17', 'MODEM_NS.SHAPING4.COEFF17', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING4_COEFF18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING4_COEFF18, self).__init__(register,
            'COEFF18', 'MODEM_NS.SHAPING4.COEFF18', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING4_COEFF19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING4_COEFF19, self).__init__(register,
            'COEFF19', 'MODEM_NS.SHAPING4.COEFF19', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING5_COEFF20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING5_COEFF20, self).__init__(register,
            'COEFF20', 'MODEM_NS.SHAPING5.COEFF20', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING5_COEFF21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING5_COEFF21, self).__init__(register,
            'COEFF21', 'MODEM_NS.SHAPING5.COEFF21', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING5_COEFF22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING5_COEFF22, self).__init__(register,
            'COEFF22', 'MODEM_NS.SHAPING5.COEFF22', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING5_COEFF23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING5_COEFF23, self).__init__(register,
            'COEFF23', 'MODEM_NS.SHAPING5.COEFF23', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING6_COEFF24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING6_COEFF24, self).__init__(register,
            'COEFF24', 'MODEM_NS.SHAPING6.COEFF24', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING6_COEFF25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING6_COEFF25, self).__init__(register,
            'COEFF25', 'MODEM_NS.SHAPING6.COEFF25', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING6_COEFF26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING6_COEFF26, self).__init__(register,
            'COEFF26', 'MODEM_NS.SHAPING6.COEFF26', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING6_COEFF27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING6_COEFF27, self).__init__(register,
            'COEFF27', 'MODEM_NS.SHAPING6.COEFF27', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING7_COEFF28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING7_COEFF28, self).__init__(register,
            'COEFF28', 'MODEM_NS.SHAPING7.COEFF28', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING7_COEFF29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING7_COEFF29, self).__init__(register,
            'COEFF29', 'MODEM_NS.SHAPING7.COEFF29', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING7_COEFF30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING7_COEFF30, self).__init__(register,
            'COEFF30', 'MODEM_NS.SHAPING7.COEFF30', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING7_COEFF31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING7_COEFF31, self).__init__(register,
            'COEFF31', 'MODEM_NS.SHAPING7.COEFF31', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING8_COEFF32(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING8_COEFF32, self).__init__(register,
            'COEFF32', 'MODEM_NS.SHAPING8.COEFF32', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING8_COEFF33(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING8_COEFF33, self).__init__(register,
            'COEFF33', 'MODEM_NS.SHAPING8.COEFF33', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING8_COEFF34(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING8_COEFF34, self).__init__(register,
            'COEFF34', 'MODEM_NS.SHAPING8.COEFF34', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING8_COEFF35(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING8_COEFF35, self).__init__(register,
            'COEFF35', 'MODEM_NS.SHAPING8.COEFF35', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING9_COEFF36(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING9_COEFF36, self).__init__(register,
            'COEFF36', 'MODEM_NS.SHAPING9.COEFF36', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING9_COEFF37(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING9_COEFF37, self).__init__(register,
            'COEFF37', 'MODEM_NS.SHAPING9.COEFF37', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING9_COEFF38(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING9_COEFF38, self).__init__(register,
            'COEFF38', 'MODEM_NS.SHAPING9.COEFF38', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING9_COEFF39(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING9_COEFF39, self).__init__(register,
            'COEFF39', 'MODEM_NS.SHAPING9.COEFF39', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING10_COEFF40(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING10_COEFF40, self).__init__(register,
            'COEFF40', 'MODEM_NS.SHAPING10.COEFF40', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING10_COEFF41(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING10_COEFF41, self).__init__(register,
            'COEFF41', 'MODEM_NS.SHAPING10.COEFF41', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING10_COEFF42(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING10_COEFF42, self).__init__(register,
            'COEFF42', 'MODEM_NS.SHAPING10.COEFF42', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING10_COEFF43(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING10_COEFF43, self).__init__(register,
            'COEFF43', 'MODEM_NS.SHAPING10.COEFF43', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING11_COEFF44(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING11_COEFF44, self).__init__(register,
            'COEFF44', 'MODEM_NS.SHAPING11.COEFF44', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING11_COEFF45(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING11_COEFF45, self).__init__(register,
            'COEFF45', 'MODEM_NS.SHAPING11.COEFF45', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING11_COEFF46(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING11_COEFF46, self).__init__(register,
            'COEFF46', 'MODEM_NS.SHAPING11.COEFF46', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING11_COEFF47(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING11_COEFF47, self).__init__(register,
            'COEFF47', 'MODEM_NS.SHAPING11.COEFF47', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING12_COEFF48(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING12_COEFF48, self).__init__(register,
            'COEFF48', 'MODEM_NS.SHAPING12.COEFF48', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING12_COEFF49(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING12_COEFF49, self).__init__(register,
            'COEFF49', 'MODEM_NS.SHAPING12.COEFF49', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING12_COEFF50(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING12_COEFF50, self).__init__(register,
            'COEFF50', 'MODEM_NS.SHAPING12.COEFF50', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING12_COEFF51(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING12_COEFF51, self).__init__(register,
            'COEFF51', 'MODEM_NS.SHAPING12.COEFF51', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING13_COEFF52(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING13_COEFF52, self).__init__(register,
            'COEFF52', 'MODEM_NS.SHAPING13.COEFF52', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING13_COEFF53(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING13_COEFF53, self).__init__(register,
            'COEFF53', 'MODEM_NS.SHAPING13.COEFF53', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING13_COEFF54(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING13_COEFF54, self).__init__(register,
            'COEFF54', 'MODEM_NS.SHAPING13.COEFF54', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING13_COEFF55(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING13_COEFF55, self).__init__(register,
            'COEFF55', 'MODEM_NS.SHAPING13.COEFF55', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING14_COEFF56(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING14_COEFF56, self).__init__(register,
            'COEFF56', 'MODEM_NS.SHAPING14.COEFF56', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING14_COEFF57(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING14_COEFF57, self).__init__(register,
            'COEFF57', 'MODEM_NS.SHAPING14.COEFF57', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING14_COEFF58(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING14_COEFF58, self).__init__(register,
            'COEFF58', 'MODEM_NS.SHAPING14.COEFF58', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING14_COEFF59(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING14_COEFF59, self).__init__(register,
            'COEFF59', 'MODEM_NS.SHAPING14.COEFF59', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING15_COEFF60(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING15_COEFF60, self).__init__(register,
            'COEFF60', 'MODEM_NS.SHAPING15.COEFF60', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING15_COEFF61(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING15_COEFF61, self).__init__(register,
            'COEFF61', 'MODEM_NS.SHAPING15.COEFF61', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING15_COEFF62(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING15_COEFF62, self).__init__(register,
            'COEFF62', 'MODEM_NS.SHAPING15.COEFF62', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SHAPING15_COEFF63(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SHAPING15_COEFF63, self).__init__(register,
            'COEFF63', 'MODEM_NS.SHAPING15.COEFF63', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGEN, self).__init__(register,
            'OOKSHAPINGEN', 'MODEM_NS.OOKSHAPING.OOKSHAPINGEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGSTEP, self).__init__(register,
            'OOKSHAPINGSTEP', 'MODEM_NS.OOKSHAPING.OOKSHAPINGSTEP', 'read-write',
            u"",
            1, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGRATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGRATE, self).__init__(register,
            'OOKSHAPINGRATE', 'MODEM_NS.OOKSHAPING.OOKSHAPINGRATE', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGLUTSIZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGLUTSIZE, self).__init__(register,
            'OOKSHAPINGLUTSIZE', 'MODEM_NS.OOKSHAPING.OOKSHAPINGLUTSIZE', 'read-write',
            u"",
            13, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE0, self).__init__(register,
            'RAMPRATE0', 'MODEM_NS.RAMPCTRL.RAMPRATE0', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE1, self).__init__(register,
            'RAMPRATE1', 'MODEM_NS.RAMPCTRL.RAMPRATE1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE2, self).__init__(register,
            'RAMPRATE2', 'MODEM_NS.RAMPCTRL.RAMPRATE2', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RAMPCTRL_RAMPDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RAMPCTRL_RAMPDIS, self).__init__(register,
            'RAMPDIS', 'MODEM_NS.RAMPCTRL.RAMPDIS', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RAMPCTRL_RAMPVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RAMPCTRL_RAMPVAL, self).__init__(register,
            'RAMPVAL', 'MODEM_NS.RAMPCTRL.RAMPVAL', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RAMPLEV_RAMPLEV0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RAMPLEV_RAMPLEV0, self).__init__(register,
            'RAMPLEV0', 'MODEM_NS.RAMPLEV.RAMPLEV0', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RAMPLEV_RAMPLEV1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RAMPLEV_RAMPLEV1, self).__init__(register,
            'RAMPLEV1', 'MODEM_NS.RAMPLEV.RAMPLEV1', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RAMPLEV_RAMPLEV2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RAMPLEV_RAMPLEV2, self).__init__(register,
            'RAMPLEV2', 'MODEM_NS.RAMPLEV.RAMPLEV2', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMPCTRL_ANARAMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMPCTRL_ANARAMPEN, self).__init__(register,
            'ANARAMPEN', 'MODEM_NS.ANARAMPCTRL.ANARAMPEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMPCTRL_RAMPOVREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMPCTRL_RAMPOVREN, self).__init__(register,
            'RAMPOVREN', 'MODEM_NS.ANARAMPCTRL.RAMPOVREN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMPCTRL_RAMPOVRUPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMPCTRL_RAMPOVRUPD, self).__init__(register,
            'RAMPOVRUPD', 'MODEM_NS.ANARAMPCTRL.RAMPOVRUPD', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMPCTRL_ANARAMPLUTODEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMPCTRL_ANARAMPLUTODEV, self).__init__(register,
            'ANARAMPLUTODEV', 'MODEM_NS.ANARAMPCTRL.ANARAMPLUTODEV', 'read-write',
            u"",
            3, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMPCTRL_VMIDCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMPCTRL_VMIDCTRL, self).__init__(register,
            'VMIDCTRL', 'MODEM_NS.ANARAMPCTRL.VMIDCTRL', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMPCTRL_MUTEDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMPCTRL_MUTEDLY, self).__init__(register,
            'MUTEDLY', 'MODEM_NS.ANARAMPCTRL.MUTEDLY', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT0, self).__init__(register,
            'ANARAMPLUT0', 'MODEM_NS.ANARAMP0.ANARAMPLUT0', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT1, self).__init__(register,
            'ANARAMPLUT1', 'MODEM_NS.ANARAMP0.ANARAMPLUT1', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT2, self).__init__(register,
            'ANARAMPLUT2', 'MODEM_NS.ANARAMP0.ANARAMPLUT2', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT3, self).__init__(register,
            'ANARAMPLUT3', 'MODEM_NS.ANARAMP0.ANARAMPLUT3', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT4, self).__init__(register,
            'ANARAMPLUT4', 'MODEM_NS.ANARAMP0.ANARAMPLUT4', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT5, self).__init__(register,
            'ANARAMPLUT5', 'MODEM_NS.ANARAMP0.ANARAMPLUT5', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT6, self).__init__(register,
            'ANARAMPLUT6', 'MODEM_NS.ANARAMP1.ANARAMPLUT6', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT7, self).__init__(register,
            'ANARAMPLUT7', 'MODEM_NS.ANARAMP1.ANARAMPLUT7', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT8, self).__init__(register,
            'ANARAMPLUT8', 'MODEM_NS.ANARAMP1.ANARAMPLUT8', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT9, self).__init__(register,
            'ANARAMPLUT9', 'MODEM_NS.ANARAMP1.ANARAMPLUT9', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT10, self).__init__(register,
            'ANARAMPLUT10', 'MODEM_NS.ANARAMP1.ANARAMPLUT10', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT11, self).__init__(register,
            'ANARAMPLUT11', 'MODEM_NS.ANARAMP1.ANARAMPLUT11', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT12, self).__init__(register,
            'ANARAMPLUT12', 'MODEM_NS.ANARAMP2.ANARAMPLUT12', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT13, self).__init__(register,
            'ANARAMPLUT13', 'MODEM_NS.ANARAMP2.ANARAMPLUT13', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT14, self).__init__(register,
            'ANARAMPLUT14', 'MODEM_NS.ANARAMP2.ANARAMPLUT14', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT15, self).__init__(register,
            'ANARAMPLUT15', 'MODEM_NS.ANARAMP2.ANARAMPLUT15', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT16, self).__init__(register,
            'ANARAMPLUT16', 'MODEM_NS.ANARAMP2.ANARAMPLUT16', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT17, self).__init__(register,
            'ANARAMPLUT17', 'MODEM_NS.ANARAMP2.ANARAMPLUT17', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT18, self).__init__(register,
            'ANARAMPLUT18', 'MODEM_NS.ANARAMP3.ANARAMPLUT18', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT19, self).__init__(register,
            'ANARAMPLUT19', 'MODEM_NS.ANARAMP3.ANARAMPLUT19', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT20, self).__init__(register,
            'ANARAMPLUT20', 'MODEM_NS.ANARAMP3.ANARAMPLUT20', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT21, self).__init__(register,
            'ANARAMPLUT21', 'MODEM_NS.ANARAMP3.ANARAMPLUT21', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT22, self).__init__(register,
            'ANARAMPLUT22', 'MODEM_NS.ANARAMP3.ANARAMPLUT22', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT23, self).__init__(register,
            'ANARAMPLUT23', 'MODEM_NS.ANARAMP3.ANARAMPLUT23', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT24, self).__init__(register,
            'ANARAMPLUT24', 'MODEM_NS.ANARAMP4.ANARAMPLUT24', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT25, self).__init__(register,
            'ANARAMPLUT25', 'MODEM_NS.ANARAMP4.ANARAMPLUT25', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT26, self).__init__(register,
            'ANARAMPLUT26', 'MODEM_NS.ANARAMP4.ANARAMPLUT26', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT27, self).__init__(register,
            'ANARAMPLUT27', 'MODEM_NS.ANARAMP4.ANARAMPLUT27', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT28, self).__init__(register,
            'ANARAMPLUT28', 'MODEM_NS.ANARAMP4.ANARAMPLUT28', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT29, self).__init__(register,
            'ANARAMPLUT29', 'MODEM_NS.ANARAMP4.ANARAMPLUT29', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT30, self).__init__(register,
            'ANARAMPLUT30', 'MODEM_NS.ANARAMP5.ANARAMPLUT30', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT31, self).__init__(register,
            'ANARAMPLUT31', 'MODEM_NS.ANARAMP5.ANARAMPLUT31', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT32(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT32, self).__init__(register,
            'ANARAMPLUT32', 'MODEM_NS.ANARAMP5.ANARAMPLUT32', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT33(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT33, self).__init__(register,
            'ANARAMPLUT33', 'MODEM_NS.ANARAMP5.ANARAMPLUT33', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT34(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT34, self).__init__(register,
            'ANARAMPLUT34', 'MODEM_NS.ANARAMP5.ANARAMPLUT34', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT35(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT35, self).__init__(register,
            'ANARAMPLUT35', 'MODEM_NS.ANARAMP5.ANARAMPLUT35', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT36(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT36, self).__init__(register,
            'ANARAMPLUT36', 'MODEM_NS.ANARAMP6.ANARAMPLUT36', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT37(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT37, self).__init__(register,
            'ANARAMPLUT37', 'MODEM_NS.ANARAMP6.ANARAMPLUT37', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT38(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT38, self).__init__(register,
            'ANARAMPLUT38', 'MODEM_NS.ANARAMP6.ANARAMPLUT38', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT39(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT39, self).__init__(register,
            'ANARAMPLUT39', 'MODEM_NS.ANARAMP6.ANARAMPLUT39', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT40(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT40, self).__init__(register,
            'ANARAMPLUT40', 'MODEM_NS.ANARAMP6.ANARAMPLUT40', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT41(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT41, self).__init__(register,
            'ANARAMPLUT41', 'MODEM_NS.ANARAMP6.ANARAMPLUT41', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT42(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT42, self).__init__(register,
            'ANARAMPLUT42', 'MODEM_NS.ANARAMP7.ANARAMPLUT42', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT43(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT43, self).__init__(register,
            'ANARAMPLUT43', 'MODEM_NS.ANARAMP7.ANARAMPLUT43', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT44(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT44, self).__init__(register,
            'ANARAMPLUT44', 'MODEM_NS.ANARAMP7.ANARAMPLUT44', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT45(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT45, self).__init__(register,
            'ANARAMPLUT45', 'MODEM_NS.ANARAMP7.ANARAMPLUT45', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT46(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT46, self).__init__(register,
            'ANARAMPLUT46', 'MODEM_NS.ANARAMP7.ANARAMPLUT46', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT47(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT47, self).__init__(register,
            'ANARAMPLUT47', 'MODEM_NS.ANARAMP7.ANARAMPLUT47', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT48(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT48, self).__init__(register,
            'ANARAMPLUT48', 'MODEM_NS.ANARAMP8.ANARAMPLUT48', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT49(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT49, self).__init__(register,
            'ANARAMPLUT49', 'MODEM_NS.ANARAMP8.ANARAMPLUT49', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT50(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT50, self).__init__(register,
            'ANARAMPLUT50', 'MODEM_NS.ANARAMP8.ANARAMPLUT50', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT51(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT51, self).__init__(register,
            'ANARAMPLUT51', 'MODEM_NS.ANARAMP8.ANARAMPLUT51', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT52(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT52, self).__init__(register,
            'ANARAMPLUT52', 'MODEM_NS.ANARAMP8.ANARAMPLUT52', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT53(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT53, self).__init__(register,
            'ANARAMPLUT53', 'MODEM_NS.ANARAMP8.ANARAMPLUT53', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT54(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT54, self).__init__(register,
            'ANARAMPLUT54', 'MODEM_NS.ANARAMP9.ANARAMPLUT54', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT55(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT55, self).__init__(register,
            'ANARAMPLUT55', 'MODEM_NS.ANARAMP9.ANARAMPLUT55', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT56(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT56, self).__init__(register,
            'ANARAMPLUT56', 'MODEM_NS.ANARAMP9.ANARAMPLUT56', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT57(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT57, self).__init__(register,
            'ANARAMPLUT57', 'MODEM_NS.ANARAMP9.ANARAMPLUT57', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT58(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT58, self).__init__(register,
            'ANARAMPLUT58', 'MODEM_NS.ANARAMP9.ANARAMPLUT58', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT59(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT59, self).__init__(register,
            'ANARAMPLUT59', 'MODEM_NS.ANARAMP9.ANARAMPLUT59', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT60(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT60, self).__init__(register,
            'ANARAMPLUT60', 'MODEM_NS.ANARAMP10.ANARAMPLUT60', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT61(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT61, self).__init__(register,
            'ANARAMPLUT61', 'MODEM_NS.ANARAMP10.ANARAMPLUT61', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT62(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT62, self).__init__(register,
            'ANARAMPLUT62', 'MODEM_NS.ANARAMP10.ANARAMPLUT62', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT63(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT63, self).__init__(register,
            'ANARAMPLUT63', 'MODEM_NS.ANARAMP10.ANARAMPLUT63', 'read-write',
            u"",
            15, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCESTIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCESTIEN, self).__init__(register,
            'DCESTIEN', 'MODEM_NS.DCCOMP.DCESTIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCCOMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCCOMPEN, self).__init__(register,
            'DCCOMPEN', 'MODEM_NS.DCCOMP.DCCOMPEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCRSTEN, self).__init__(register,
            'DCRSTEN', 'MODEM_NS.DCCOMP.DCRSTEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCCOMPFREEZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCCOMPFREEZE, self).__init__(register,
            'DCCOMPFREEZE', 'MODEM_NS.DCCOMP.DCCOMPFREEZE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCCOMPGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCCOMPGEAR, self).__init__(register,
            'DCCOMPGEAR', 'MODEM_NS.DCCOMP.DCCOMPGEAR', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCLIMIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCLIMIT, self).__init__(register,
            'DCLIMIT', 'MODEM_NS.DCCOMP.DCLIMIT', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCGAINGEAREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCGAINGEAREN, self).__init__(register,
            'DCGAINGEAREN', 'MODEM_NS.DCCOMP.DCGAINGEAREN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCGAINGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCGAINGEAR, self).__init__(register,
            'DCGAINGEAR', 'MODEM_NS.DCCOMP.DCGAINGEAR', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMP_DCGAINGEARSMPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMP_DCGAINGEARSMPS, self).__init__(register,
            'DCGAINGEARSMPS', 'MODEM_NS.DCCOMP.DCGAINGEARSMPS', 'read-write',
            u"",
            13, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINITVALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINITVALI, self).__init__(register,
            'DCCOMPINITVALI', 'MODEM_NS.DCCOMPFILTINIT.DCCOMPINITVALI', 'read-write',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINITVALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINITVALQ, self).__init__(register,
            'DCCOMPINITVALQ', 'MODEM_NS.DCCOMPFILTINIT.DCCOMPINITVALQ', 'read-write',
            u"",
            15, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINIT, self).__init__(register,
            'DCCOMPINIT', 'MODEM_NS.DCCOMPFILTINIT.DCCOMPINIT', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCESTI_DCCOMPESTIVALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCESTI_DCCOMPESTIVALI, self).__init__(register,
            'DCCOMPESTIVALI', 'MODEM_NS.DCESTI.DCCOMPESTIVALI', 'read-only',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DCESTI_DCCOMPESTIVALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DCESTI_DCCOMPESTIVALQ, self).__init__(register,
            'DCCOMPESTIVALQ', 'MODEM_NS.DCESTI.DCCOMPESTIVALQ', 'read-only',
            u"",
            15, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SRCCHF_SRCRATIO2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SRCCHF_SRCRATIO2, self).__init__(register,
            'SRCRATIO2', 'MODEM_NS.SRCCHF.SRCRATIO2', 'read-write',
            u"",
            12, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SRCCHF_SRCENABLE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SRCCHF_SRCENABLE2, self).__init__(register,
            'SRCENABLE2', 'MODEM_NS.SRCCHF.SRCENABLE2', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SRCCHF_UPGAPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SRCCHF_UPGAPS, self).__init__(register,
            'UPGAPS', 'MODEM_NS.SRCCHF.UPGAPS', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SRCCHF_INTOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SRCCHF_INTOSR, self).__init__(register,
            'INTOSR', 'MODEM_NS.SRCCHF.INTOSR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_INTAFC_FOEPREAVG0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_INTAFC_FOEPREAVG0, self).__init__(register,
            'FOEPREAVG0', 'MODEM_NS.INTAFC.FOEPREAVG0', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_INTAFC_FOEPREAVG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_INTAFC_FOEPREAVG1, self).__init__(register,
            'FOEPREAVG1', 'MODEM_NS.INTAFC.FOEPREAVG1', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_INTAFC_FOEPREAVG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_INTAFC_FOEPREAVG2, self).__init__(register,
            'FOEPREAVG2', 'MODEM_NS.INTAFC.FOEPREAVG2', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_INTAFC_FOEPREAVG3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_INTAFC_FOEPREAVG3, self).__init__(register,
            'FOEPREAVG3', 'MODEM_NS.INTAFC.FOEPREAVG3', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_INTAFC_FOEPREAVG4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_INTAFC_FOEPREAVG4, self).__init__(register,
            'FOEPREAVG4', 'MODEM_NS.INTAFC.FOEPREAVG4', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_INTAFC_FOEPREAVG5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_INTAFC_FOEPREAVG5, self).__init__(register,
            'FOEPREAVG5', 'MODEM_NS.INTAFC.FOEPREAVG5', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_INTAFC_FOEPREAVG6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_INTAFC_FOEPREAVG6, self).__init__(register,
            'FOEPREAVG6', 'MODEM_NS.INTAFC.FOEPREAVG6', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_INTAFC_FOEPREAVG7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_INTAFC_FOEPREAVG7, self).__init__(register,
            'FOEPREAVG7', 'MODEM_NS.INTAFC.FOEPREAVG7', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD0_SPIKETHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD0_SPIKETHD, self).__init__(register,
            'SPIKETHD', 'MODEM_NS.DSATHD0.SPIKETHD', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD0_UNMODTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD0_UNMODTHD, self).__init__(register,
            'UNMODTHD', 'MODEM_NS.DSATHD0.UNMODTHD', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD0_FDEVMINTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD0_FDEVMINTHD, self).__init__(register,
            'FDEVMINTHD', 'MODEM_NS.DSATHD0.FDEVMINTHD', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD0_FDEVMAXTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD0_FDEVMAXTHD, self).__init__(register,
            'FDEVMAXTHD', 'MODEM_NS.DSATHD0.FDEVMAXTHD', 'read-write',
            u"",
            20, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_POWABSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_POWABSTHD, self).__init__(register,
            'POWABSTHD', 'MODEM_NS.DSATHD1.POWABSTHD', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_POWRELTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_POWRELTHD, self).__init__(register,
            'POWRELTHD', 'MODEM_NS.DSATHD1.POWRELTHD', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_DSARSTCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_DSARSTCNT, self).__init__(register,
            'DSARSTCNT', 'MODEM_NS.DSATHD1.DSARSTCNT', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_RSSIJMPTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_RSSIJMPTHD, self).__init__(register,
            'RSSIJMPTHD', 'MODEM_NS.DSATHD1.RSSIJMPTHD', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_FREQLATDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_FREQLATDLY, self).__init__(register,
            'FREQLATDLY', 'MODEM_NS.DSATHD1.FREQLATDLY', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_PWRFLTBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_PWRFLTBYP, self).__init__(register,
            'PWRFLTBYP', 'MODEM_NS.DSATHD1.PWRFLTBYP', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_AMPFLTBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_AMPFLTBYP, self).__init__(register,
            'AMPFLTBYP', 'MODEM_NS.DSATHD1.AMPFLTBYP', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_PWRDETDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_PWRDETDIS, self).__init__(register,
            'PWRDETDIS', 'MODEM_NS.DSATHD1.PWRDETDIS', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD1_FREQSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD1_FREQSCALE, self).__init__(register,
            'FREQSCALE', 'MODEM_NS.DSATHD1.FREQSCALE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD2_POWABSTHDLOG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD2_POWABSTHDLOG, self).__init__(register,
            'POWABSTHDLOG', 'MODEM_NS.DSATHD2.POWABSTHDLOG', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD2_JUMPDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD2_JUMPDETEN, self).__init__(register,
            'JUMPDETEN', 'MODEM_NS.DSATHD2.JUMPDETEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD2_FDADJTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD2_FDADJTHD, self).__init__(register,
            'FDADJTHD', 'MODEM_NS.DSATHD2.FDADJTHD', 'read-write',
            u"",
            10, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD2_PMDETPASSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD2_PMDETPASSTHD, self).__init__(register,
            'PMDETPASSTHD', 'MODEM_NS.DSATHD2.PMDETPASSTHD', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD2_FREQESTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD2_FREQESTTHD, self).__init__(register,
            'FREQESTTHD', 'MODEM_NS.DSATHD2.FREQESTTHD', 'read-write',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD2_INTERFERDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD2_INTERFERDET, self).__init__(register,
            'INTERFERDET', 'MODEM_NS.DSATHD2.INTERFERDET', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD2_PMDETFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD2_PMDETFORCE, self).__init__(register,
            'PMDETFORCE', 'MODEM_NS.DSATHD2.PMDETFORCE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD3_SPIKETHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD3_SPIKETHDLO, self).__init__(register,
            'SPIKETHDLO', 'MODEM_NS.DSATHD3.SPIKETHDLO', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD3_UNMODTHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD3_UNMODTHDLO, self).__init__(register,
            'UNMODTHDLO', 'MODEM_NS.DSATHD3.UNMODTHDLO', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD3_FDEVMINTHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD3_FDEVMINTHDLO, self).__init__(register,
            'FDEVMINTHDLO', 'MODEM_NS.DSATHD3.FDEVMINTHDLO', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD3_FDEVMAXTHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD3_FDEVMAXTHDLO, self).__init__(register,
            'FDEVMAXTHDLO', 'MODEM_NS.DSATHD3.FDEVMAXTHDLO', 'read-write',
            u"",
            20, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD4_POWABSTHDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD4_POWABSTHDLO, self).__init__(register,
            'POWABSTHDLO', 'MODEM_NS.DSATHD4.POWABSTHDLO', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD4_ARRTOLERTHD0LO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD4_ARRTOLERTHD0LO, self).__init__(register,
            'ARRTOLERTHD0LO', 'MODEM_NS.DSATHD4.ARRTOLERTHD0LO', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD4_ARRTOLERTHD1LO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD4_ARRTOLERTHD1LO, self).__init__(register,
            'ARRTOLERTHD1LO', 'MODEM_NS.DSATHD4.ARRTOLERTHD1LO', 'read-write',
            u"",
            21, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSATHD4_SWTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSATHD4_SWTHD, self).__init__(register,
            'SWTHD', 'MODEM_NS.DSATHD4.SWTHD', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_DSAMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_DSAMODE, self).__init__(register,
            'DSAMODE', 'MODEM_NS.DSACTRL.DSAMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_ARRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_ARRTHD, self).__init__(register,
            'ARRTHD', 'MODEM_NS.DSACTRL.ARRTHD', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_ARRTOLERTHD0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_ARRTOLERTHD0, self).__init__(register,
            'ARRTOLERTHD0', 'MODEM_NS.DSACTRL.ARRTOLERTHD0', 'read-write',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_ARRTOLERTHD1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_ARRTOLERTHD1, self).__init__(register,
            'ARRTOLERTHD1', 'MODEM_NS.DSACTRL.ARRTOLERTHD1', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_SCHPRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_SCHPRD, self).__init__(register,
            'SCHPRD', 'MODEM_NS.DSACTRL.SCHPRD', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_FREQAVGSYM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_FREQAVGSYM, self).__init__(register,
            'FREQAVGSYM', 'MODEM_NS.DSACTRL.FREQAVGSYM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_TRANRSTDSA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_TRANRSTDSA, self).__init__(register,
            'TRANRSTDSA', 'MODEM_NS.DSACTRL.TRANRSTDSA', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_DSARSTON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_DSARSTON, self).__init__(register,
            'DSARSTON', 'MODEM_NS.DSACTRL.DSARSTON', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_GAINREDUCDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_GAINREDUCDLY, self).__init__(register,
            'GAINREDUCDLY', 'MODEM_NS.DSACTRL.GAINREDUCDLY', 'read-write',
            u"",
            21, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_LOWDUTY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_LOWDUTY, self).__init__(register,
            'LOWDUTY', 'MODEM_NS.DSACTRL.LOWDUTY', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_RESTORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_RESTORE, self).__init__(register,
            'RESTORE', 'MODEM_NS.DSACTRL.RESTORE', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_AGCBAUDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_AGCBAUDEN, self).__init__(register,
            'AGCBAUDEN', 'MODEM_NS.DSACTRL.AGCBAUDEN', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DSACTRL_AMPJUPTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DSACTRL_AMPJUPTHD, self).__init__(register,
            'AMPJUPTHD', 'MODEM_NS.DSACTRL.AMPJUPTHD', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXFREQ, self).__init__(register,
            'DIGMIXFREQ', 'MODEM_NS.DIGMIXCTRL.DIGMIXFREQ', 'read-write',
            u"",
            0, 20)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXMODE, self).__init__(register,
            'DIGMIXMODE', 'MODEM_NS.DIGMIXCTRL.DIGMIXMODE', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGMIXCTRL_MIXERCONJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGMIXCTRL_MIXERCONJ, self).__init__(register,
            'MIXERCONJ', 'MODEM_NS.DIGMIXCTRL.MIXERCONJ', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXFB, self).__init__(register,
            'DIGMIXFB', 'MODEM_NS.DIGMIXCTRL.DIGMIXFB', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VITERBIDEMOD_VTDEMODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VITERBIDEMOD_VTDEMODEN, self).__init__(register,
            'VTDEMODEN', 'MODEM_NS.VITERBIDEMOD.VTDEMODEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VITERBIDEMOD_HARDDECISION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VITERBIDEMOD_HARDDECISION, self).__init__(register,
            'HARDDECISION', 'MODEM_NS.VITERBIDEMOD.HARDDECISION', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI1, self).__init__(register,
            'VITERBIKSI1', 'MODEM_NS.VITERBIDEMOD.VITERBIKSI1', 'read-write',
            u"",
            2, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI2, self).__init__(register,
            'VITERBIKSI2', 'MODEM_NS.VITERBIDEMOD.VITERBIKSI2', 'read-write',
            u"",
            9, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI3, self).__init__(register,
            'VITERBIKSI3', 'MODEM_NS.VITERBIDEMOD.VITERBIKSI3', 'read-write',
            u"",
            16, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VITERBIDEMOD_SYNTHAFC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VITERBIDEMOD_SYNTHAFC, self).__init__(register,
            'SYNTHAFC', 'MODEM_NS.VITERBIDEMOD.SYNTHAFC', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VITERBIDEMOD_CORRCYCLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VITERBIDEMOD_CORRCYCLE, self).__init__(register,
            'CORRCYCLE', 'MODEM_NS.VITERBIDEMOD.CORRCYCLE', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VITERBIDEMOD_CORRSTPSIZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VITERBIDEMOD_CORRSTPSIZE, self).__init__(register,
            'CORRSTPSIZE', 'MODEM_NS.VITERBIDEMOD.CORRSTPSIZE', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTCORRCFG0_EXPECTPATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTCORRCFG0_EXPECTPATT, self).__init__(register,
            'EXPECTPATT', 'MODEM_NS.VTCORRCFG0.EXPECTPATT', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTCORRCFG1_VITERBIKSI3WB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTCORRCFG1_VITERBIKSI3WB, self).__init__(register,
            'VITERBIKSI3WB', 'MODEM_NS.VTCORRCFG1.VITERBIKSI3WB', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTCORRCFG1_KSI3SWENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTCORRCFG1_KSI3SWENABLE, self).__init__(register,
            'KSI3SWENABLE', 'MODEM_NS.VTCORRCFG1.KSI3SWENABLE', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTCORRCFG1_VTFRQLIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTCORRCFG1_VTFRQLIM, self).__init__(register,
            'VTFRQLIM', 'MODEM_NS.VTCORRCFG1.VTFRQLIM', 'read-write',
            u"",
            8, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTCORRCFG1_EXPSYNCLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTCORRCFG1_EXPSYNCLEN, self).__init__(register,
            'EXPSYNCLEN', 'MODEM_NS.VTCORRCFG1.EXPSYNCLEN', 'read-write',
            u"",
            18, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTCORRCFG1_EXPECTHT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTCORRCFG1_EXPECTHT, self).__init__(register,
            'EXPECTHT', 'MODEM_NS.VTCORRCFG1.EXPECTHT', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTTRACK_FREQTRACKMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTTRACK_FREQTRACKMODE, self).__init__(register,
            'FREQTRACKMODE', 'MODEM_NS.VTTRACK.FREQTRACKMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTTRACK_TIMTRACKTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTTRACK_TIMTRACKTHD, self).__init__(register,
            'TIMTRACKTHD', 'MODEM_NS.VTTRACK.TIMTRACKTHD', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTTRACK_TIMEACQUTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTTRACK_TIMEACQUTHD, self).__init__(register,
            'TIMEACQUTHD', 'MODEM_NS.VTTRACK.TIMEACQUTHD', 'read-write',
            u"",
            6, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTTRACK_TIMGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTTRACK_TIMGEAR, self).__init__(register,
            'TIMGEAR', 'MODEM_NS.VTTRACK.TIMGEAR', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTTRACK_FREQBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTTRACK_FREQBIAS, self).__init__(register,
            'FREQBIAS', 'MODEM_NS.VTTRACK.FREQBIAS', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTTRACK_HIPWRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTTRACK_HIPWRTHD, self).__init__(register,
            'HIPWRTHD', 'MODEM_NS.VTTRACK.HIPWRTHD', 'read-write',
            u"",
            22, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTBLETIMING_VTBLETIMINGSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTBLETIMING_VTBLETIMINGSEL, self).__init__(register,
            'VTBLETIMINGSEL', 'MODEM_NS.VTBLETIMING.VTBLETIMINGSEL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTBLETIMING_TIMINGDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTBLETIMING_TIMINGDELAY, self).__init__(register,
            'TIMINGDELAY', 'MODEM_NS.VTBLETIMING.TIMINGDELAY', 'read-write',
            u"",
            4, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTBLETIMING_FLENOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTBLETIMING_FLENOFF, self).__init__(register,
            'FLENOFF', 'MODEM_NS.VTBLETIMING.FLENOFF', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_VTBLETIMING_DISDEMODOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_VTBLETIMING_DISDEMODOF, self).__init__(register,
            'DISDEMODOF', 'MODEM_NS.VTBLETIMING.DISDEMODOF', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BREST_BRESTINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BREST_BRESTINT, self).__init__(register,
            'BRESTINT', 'MODEM_NS.BREST.BRESTINT', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BREST_BRESTNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BREST_BRESTNUM, self).__init__(register,
            'BRESTNUM', 'MODEM_NS.BREST.BRESTNUM', 'read-only',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_AUTOCG_AUTOCGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_AUTOCG_AUTOCGEN, self).__init__(register,
            'AUTOCGEN', 'MODEM_NS.AUTOCG.AUTOCGEN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CGCLKSTOP_FORCEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CGCLKSTOP_FORCEOFF, self).__init__(register,
            'FORCEOFF', 'MODEM_NS.CGCLKSTOP.FORCEOFF', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_POE_POEI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_POE_POEI, self).__init__(register,
            'POEI', 'MODEM_NS.POE.POEI', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_POE_POEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_POE_POEQ, self).__init__(register,
            'POEQ', 'MODEM_NS.POE.POEQ', 'read-only',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIRECTMODE_DMENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIRECTMODE_DMENABLE, self).__init__(register,
            'DMENABLE', 'MODEM_NS.DIRECTMODE.DMENABLE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIRECTMODE_SYNCASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIRECTMODE_SYNCASYNC, self).__init__(register,
            'SYNCASYNC', 'MODEM_NS.DIRECTMODE.SYNCASYNC', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIRECTMODE_SYNCPREAM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIRECTMODE_SYNCPREAM, self).__init__(register,
            'SYNCPREAM', 'MODEM_NS.DIRECTMODE.SYNCPREAM', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIRECTMODE_CLKWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIRECTMODE_CLKWIDTH, self).__init__(register,
            'CLKWIDTH', 'MODEM_NS.DIRECTMODE.CLKWIDTH', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_LRSS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_LRSS, self).__init__(register,
            'LRSS', 'MODEM_NS.LONGRANGE1.LRSS', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_LRTIMEOUTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_LRTIMEOUTTHD, self).__init__(register,
            'LRTIMEOUTTHD', 'MODEM_NS.LONGRANGE1.LRTIMEOUTTHD', 'read-write',
            u"",
            4, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_CHPWRACCUDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_CHPWRACCUDEL, self).__init__(register,
            'CHPWRACCUDEL', 'MODEM_NS.LONGRANGE1.CHPWRACCUDEL', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_HYSVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_HYSVAL, self).__init__(register,
            'HYSVAL', 'MODEM_NS.LONGRANGE1.HYSVAL', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_AVGWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_AVGWIN, self).__init__(register,
            'AVGWIN', 'MODEM_NS.LONGRANGE1.AVGWIN', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_LRSPIKETHADD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_LRSPIKETHADD, self).__init__(register,
            'LRSPIKETHADD', 'MODEM_NS.LONGRANGE1.LRSPIKETHADD', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_LOGICBASEDPUGATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_LOGICBASEDPUGATE, self).__init__(register,
            'LOGICBASEDPUGATE', 'MODEM_NS.LONGRANGE1.LOGICBASEDPUGATE', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_LOGICBASEDLRDEMODGATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_LOGICBASEDLRDEMODGATE, self).__init__(register,
            'LOGICBASEDLRDEMODGATE', 'MODEM_NS.LONGRANGE1.LOGICBASEDLRDEMODGATE', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE1_PREFILTLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE1_PREFILTLEN, self).__init__(register,
            'PREFILTLEN', 'MODEM_NS.LONGRANGE1.PREFILTLEN', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH1, self).__init__(register,
            'LRCHPWRTH1', 'MODEM_NS.LONGRANGE2.LRCHPWRTH1', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH2, self).__init__(register,
            'LRCHPWRTH2', 'MODEM_NS.LONGRANGE2.LRCHPWRTH2', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH3, self).__init__(register,
            'LRCHPWRTH3', 'MODEM_NS.LONGRANGE2.LRCHPWRTH3', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH4, self).__init__(register,
            'LRCHPWRTH4', 'MODEM_NS.LONGRANGE2.LRCHPWRTH4', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH5, self).__init__(register,
            'LRCHPWRTH5', 'MODEM_NS.LONGRANGE3.LRCHPWRTH5', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH6, self).__init__(register,
            'LRCHPWRTH6', 'MODEM_NS.LONGRANGE3.LRCHPWRTH6', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH7, self).__init__(register,
            'LRCHPWRTH7', 'MODEM_NS.LONGRANGE3.LRCHPWRTH7', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH8, self).__init__(register,
            'LRCHPWRTH8', 'MODEM_NS.LONGRANGE3.LRCHPWRTH8', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRTH9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRTH9, self).__init__(register,
            'LRCHPWRTH9', 'MODEM_NS.LONGRANGE4.LRCHPWRTH9', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRTH10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRTH10, self).__init__(register,
            'LRCHPWRTH10', 'MODEM_NS.LONGRANGE4.LRCHPWRTH10', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH1, self).__init__(register,
            'LRCHPWRSH1', 'MODEM_NS.LONGRANGE4.LRCHPWRSH1', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH2, self).__init__(register,
            'LRCHPWRSH2', 'MODEM_NS.LONGRANGE4.LRCHPWRSH2', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH3, self).__init__(register,
            'LRCHPWRSH3', 'MODEM_NS.LONGRANGE4.LRCHPWRSH3', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH4, self).__init__(register,
            'LRCHPWRSH4', 'MODEM_NS.LONGRANGE4.LRCHPWRSH4', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH5, self).__init__(register,
            'LRCHPWRSH5', 'MODEM_NS.LONGRANGE5.LRCHPWRSH5', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH6, self).__init__(register,
            'LRCHPWRSH6', 'MODEM_NS.LONGRANGE5.LRCHPWRSH6', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH7, self).__init__(register,
            'LRCHPWRSH7', 'MODEM_NS.LONGRANGE5.LRCHPWRSH7', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH8, self).__init__(register,
            'LRCHPWRSH8', 'MODEM_NS.LONGRANGE5.LRCHPWRSH8', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH9, self).__init__(register,
            'LRCHPWRSH9', 'MODEM_NS.LONGRANGE5.LRCHPWRSH9', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH10, self).__init__(register,
            'LRCHPWRSH10', 'MODEM_NS.LONGRANGE5.LRCHPWRSH10', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH11, self).__init__(register,
            'LRCHPWRSH11', 'MODEM_NS.LONGRANGE5.LRCHPWRSH11', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRSPIKETH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRSPIKETH, self).__init__(register,
            'LRCHPWRSPIKETH', 'MODEM_NS.LONGRANGE6.LRCHPWRSPIKETH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE6_LRSPIKETHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE6_LRSPIKETHD, self).__init__(register,
            'LRSPIKETHD', 'MODEM_NS.LONGRANGE6.LRSPIKETHD', 'read-write',
            u"",
            8, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRTH11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRTH11, self).__init__(register,
            'LRCHPWRTH11', 'MODEM_NS.LONGRANGE6.LRCHPWRTH11', 'read-write',
            u"",
            20, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRSH12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRSH12, self).__init__(register,
            'LRCHPWRSH12', 'MODEM_NS.LONGRANGE6.LRCHPWRSH12', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LRFRC_CI500(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LRFRC_CI500, self).__init__(register,
            'CI500', 'MODEM_NS.LRFRC.CI500', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LRFRC_FRCACKTIMETHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LRFRC_FRCACKTIMETHD, self).__init__(register,
            'FRCACKTIMETHD', 'MODEM_NS.LRFRC.FRCACKTIMETHD', 'read-write',
            u"",
            2, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LRFRC_LRCORRMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LRFRC_LRCORRMODE, self).__init__(register,
            'LRCORRMODE', 'MODEM_NS.LRFRC.LRCORRMODE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHDYNAMICBBSSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHDYNAMICBBSSEN, self).__init__(register,
            'COHDYNAMICBBSSEN', 'MODEM_NS.COH0.COHDYNAMICBBSSEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHDYNAMICSYNCTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHDYNAMICSYNCTHRESH, self).__init__(register,
            'COHDYNAMICSYNCTHRESH', 'MODEM_NS.COH0.COHDYNAMICSYNCTHRESH', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHDYNAMICPRETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHDYNAMICPRETHRESH, self).__init__(register,
            'COHDYNAMICPRETHRESH', 'MODEM_NS.COH0.COHDYNAMICPRETHRESH', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHCHPWRLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHCHPWRLOCK, self).__init__(register,
            'COHCHPWRLOCK', 'MODEM_NS.COH0.COHCHPWRLOCK', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHCHPWRRESTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHCHPWRRESTART, self).__init__(register,
            'COHCHPWRRESTART', 'MODEM_NS.COH0.COHCHPWRRESTART', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHDYNAMICPRETHRESHSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHDYNAMICPRETHRESHSEL, self).__init__(register,
            'COHDYNAMICPRETHRESHSEL', 'MODEM_NS.COH0.COHDYNAMICPRETHRESHSEL', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHCHPWRTH0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHCHPWRTH0, self).__init__(register,
            'COHCHPWRTH0', 'MODEM_NS.COH0.COHCHPWRTH0', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHCHPWRTH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHCHPWRTH1, self).__init__(register,
            'COHCHPWRTH1', 'MODEM_NS.COH0.COHCHPWRTH1', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH0_COHCHPWRTH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH0_COHCHPWRTH2, self).__init__(register,
            'COHCHPWRTH2', 'MODEM_NS.COH0.COHCHPWRTH2', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH1_SYNCTHRESH0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH1_SYNCTHRESH0, self).__init__(register,
            'SYNCTHRESH0', 'MODEM_NS.COH1.SYNCTHRESH0', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH1_SYNCTHRESH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH1_SYNCTHRESH1, self).__init__(register,
            'SYNCTHRESH1', 'MODEM_NS.COH1.SYNCTHRESH1', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH1_SYNCTHRESH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH1_SYNCTHRESH2, self).__init__(register,
            'SYNCTHRESH2', 'MODEM_NS.COH1.SYNCTHRESH2', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH1_SYNCTHRESH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH1_SYNCTHRESH3, self).__init__(register,
            'SYNCTHRESH3', 'MODEM_NS.COH1.SYNCTHRESH3', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA0, self).__init__(register,
            'SYNCTHRESHDELTA0', 'MODEM_NS.COH2.SYNCTHRESHDELTA0', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA1, self).__init__(register,
            'SYNCTHRESHDELTA1', 'MODEM_NS.COH2.SYNCTHRESHDELTA1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA2, self).__init__(register,
            'SYNCTHRESHDELTA2', 'MODEM_NS.COH2.SYNCTHRESHDELTA2', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA3, self).__init__(register,
            'SYNCTHRESHDELTA3', 'MODEM_NS.COH2.SYNCTHRESHDELTA3', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH2_DSAPEAKCHPWRTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH2_DSAPEAKCHPWRTH, self).__init__(register,
            'DSAPEAKCHPWRTH', 'MODEM_NS.COH2.DSAPEAKCHPWRTH', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH2_FIXEDCDTHFORIIR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH2_FIXEDCDTHFORIIR, self).__init__(register,
            'FIXEDCDTHFORIIR', 'MODEM_NS.COH2.FIXEDCDTHFORIIR', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_COHDSAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_COHDSAEN, self).__init__(register,
            'COHDSAEN', 'MODEM_NS.COH3.COHDSAEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_COHDSAADDWNDSIZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_COHDSAADDWNDSIZE, self).__init__(register,
            'COHDSAADDWNDSIZE', 'MODEM_NS.COH3.COHDSAADDWNDSIZE', 'read-write',
            u"",
            1, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_CDSS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_CDSS, self).__init__(register,
            'CDSS', 'MODEM_NS.COH3.CDSS', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_DSAPEAKCHKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_DSAPEAKCHKEN, self).__init__(register,
            'DSAPEAKCHKEN', 'MODEM_NS.COH3.DSAPEAKCHKEN', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_DSAPEAKINDLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_DSAPEAKINDLEN, self).__init__(register,
            'DSAPEAKINDLEN', 'MODEM_NS.COH3.DSAPEAKINDLEN', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_DSAPEAKCHPWREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_DSAPEAKCHPWREN, self).__init__(register,
            'DSAPEAKCHPWREN', 'MODEM_NS.COH3.DSAPEAKCHPWREN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_LOGICBASEDCOHDEMODGATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_LOGICBASEDCOHDEMODGATE, self).__init__(register,
            'LOGICBASEDCOHDEMODGATE', 'MODEM_NS.COH3.LOGICBASEDCOHDEMODGATE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_DYNIIRCOEFOPTION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_DYNIIRCOEFOPTION, self).__init__(register,
            'DYNIIRCOEFOPTION', 'MODEM_NS.COH3.DYNIIRCOEFOPTION', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_ONEPEAKQUALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_ONEPEAKQUALEN, self).__init__(register,
            'ONEPEAKQUALEN', 'MODEM_NS.COH3.ONEPEAKQUALEN', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_PEAKCHKTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_PEAKCHKTIMOUT, self).__init__(register,
            'PEAKCHKTIMOUT', 'MODEM_NS.COH3.PEAKCHKTIMOUT', 'read-write',
            u"",
            23, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_COHDSADETDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_COHDSADETDIS, self).__init__(register,
            'COHDSADETDIS', 'MODEM_NS.COH3.COHDSADETDIS', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_COH3_COHDSACMPLX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_COH3_COHDSACMPLX, self).__init__(register,
            'COHDSACMPLX', 'MODEM_NS.COH3.COHDSACMPLX', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CMD_PRESTOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CMD_PRESTOP, self).__init__(register,
            'PRESTOP', 'MODEM_NS.CMD.PRESTOP', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CMD_CHPWRACCUCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CMD_CHPWRACCUCLR, self).__init__(register,
            'CHPWRACCUCLR', 'MODEM_NS.CMD.CHPWRACCUCLR', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CMD_AFCTXLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CMD_AFCTXLOCK, self).__init__(register,
            'AFCTXLOCK', 'MODEM_NS.CMD.AFCTXLOCK', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CMD_AFCTXCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CMD_AFCTXCLEAR, self).__init__(register,
            'AFCTXCLEAR', 'MODEM_NS.CMD.AFCTXCLEAR', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CMD_AFCRXCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CMD_AFCRXCLEAR, self).__init__(register,
            'AFCRXCLEAR', 'MODEM_NS.CMD.AFCRXCLEAR', 'write-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SYNCPROPERTIES_STATICSYNCTHRESHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SYNCPROPERTIES_STATICSYNCTHRESHEN, self).__init__(register,
            'STATICSYNCTHRESHEN', 'MODEM_NS.SYNCPROPERTIES.STATICSYNCTHRESHEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SYNCPROPERTIES_STATICSYNCTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SYNCPROPERTIES_STATICSYNCTHRESH, self).__init__(register,
            'STATICSYNCTHRESH', 'MODEM_NS.SYNCPROPERTIES.STATICSYNCTHRESH', 'read-write',
            u"",
            9, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINEN, self).__init__(register,
            'DIGIGAINEN', 'MODEM_NS.DIGIGAINCTRL.DIGIGAINEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINSEL, self).__init__(register,
            'DIGIGAINSEL', 'MODEM_NS.DIGIGAINCTRL.DIGIGAINSEL', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINDOUBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINDOUBLE, self).__init__(register,
            'DIGIGAINDOUBLE', 'MODEM_NS.DIGIGAINCTRL.DIGIGAINDOUBLE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINHALF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINHALF, self).__init__(register,
            'DIGIGAINHALF', 'MODEM_NS.DIGIGAINCTRL.DIGIGAINHALF', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_DIGIGAINCTRL_DEC0GAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_DIGIGAINCTRL_DEC0GAIN, self).__init__(register,
            'DEC0GAIN', 'MODEM_NS.DIGIGAINCTRL.DEC0GAIN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_POSTPONESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_POSTPONESEL, self).__init__(register,
            'POSTPONESEL', 'MODEM_NS.PRSCTRL.POSTPONESEL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_ADVANCESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_ADVANCESEL, self).__init__(register,
            'ADVANCESEL', 'MODEM_NS.PRSCTRL.ADVANCESEL', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_NEWWNDSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_NEWWNDSEL, self).__init__(register,
            'NEWWNDSEL', 'MODEM_NS.PRSCTRL.NEWWNDSEL', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_WEAKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_WEAKSEL, self).__init__(register,
            'WEAKSEL', 'MODEM_NS.PRSCTRL.WEAKSEL', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_SYNCSENTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_SYNCSENTSEL, self).__init__(register,
            'SYNCSENTSEL', 'MODEM_NS.PRSCTRL.SYNCSENTSEL', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_PRESENTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_PRESENTSEL, self).__init__(register,
            'PRESENTSEL', 'MODEM_NS.PRSCTRL.PRESENTSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_LOWCORRSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_LOWCORRSEL, self).__init__(register,
            'LOWCORRSEL', 'MODEM_NS.PRSCTRL.LOWCORRSEL', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_ANT0SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_ANT0SEL, self).__init__(register,
            'ANT0SEL', 'MODEM_NS.PRSCTRL.ANT0SEL', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_ANT1SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_ANT1SEL, self).__init__(register,
            'ANT1SEL', 'MODEM_NS.PRSCTRL.ANT1SEL', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PRSCTRL_IFADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PRSCTRL_IFADCCLKSEL, self).__init__(register,
            'IFADCCLKSEL', 'MODEM_NS.PRSCTRL.IFADCCLKSEL', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PADEBUG_MANPACLKAMPCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PADEBUG_MANPACLKAMPCTRL, self).__init__(register,
            'MANPACLKAMPCTRL', 'MODEM_NS.PADEBUG.MANPACLKAMPCTRL', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PADEBUG_ENMANPACLKAMPCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PADEBUG_ENMANPACLKAMPCTRL, self).__init__(register,
            'ENMANPACLKAMPCTRL', 'MODEM_NS.PADEBUG.ENMANPACLKAMPCTRL', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PADEBUG_ENMANPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PADEBUG_ENMANPAPOWER, self).__init__(register,
            'ENMANPAPOWER', 'MODEM_NS.PADEBUG.ENMANPAPOWER', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PADEBUG_ENMANPASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PADEBUG_ENMANPASELSLICE, self).__init__(register,
            'ENMANPASELSLICE', 'MODEM_NS.PADEBUG.ENMANPASELSLICE', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_MINCOSTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_MINCOSTTHD, self).__init__(register,
            'MINCOSTTHD', 'MODEM_NS.REALTIMCFE.MINCOSTTHD', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_RTSCHWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_RTSCHWIN, self).__init__(register,
            'RTSCHWIN', 'MODEM_NS.REALTIMCFE.RTSCHWIN', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_RTSCHMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_RTSCHMODE, self).__init__(register,
            'RTSCHMODE', 'MODEM_NS.REALTIMCFE.RTSCHMODE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_TRACKINGWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_TRACKINGWIN, self).__init__(register,
            'TRACKINGWIN', 'MODEM_NS.REALTIMCFE.TRACKINGWIN', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_SYNCACQWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_SYNCACQWIN, self).__init__(register,
            'SYNCACQWIN', 'MODEM_NS.REALTIMCFE.SYNCACQWIN', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_EXTENSCHBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_EXTENSCHBYP, self).__init__(register,
            'EXTENSCHBYP', 'MODEM_NS.REALTIMCFE.EXTENSCHBYP', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_SINEWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_SINEWEN, self).__init__(register,
            'SINEWEN', 'MODEM_NS.REALTIMCFE.SINEWEN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_VTAFCFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_VTAFCFRAME, self).__init__(register,
            'VTAFCFRAME', 'MODEM_NS.REALTIMCFE.VTAFCFRAME', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_REALTIMCFE_RTCFEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_REALTIMCFE_RTCFEEN, self).__init__(register,
            'RTCFEEN', 'MODEM_NS.REALTIMCFE.RTCFEEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ETSCTRL_ETSLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ETSCTRL_ETSLOC, self).__init__(register,
            'ETSLOC', 'MODEM_NS.ETSCTRL.ETSLOC', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ETSCTRL_CAPSIGONPRS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ETSCTRL_CAPSIGONPRS, self).__init__(register,
            'CAPSIGONPRS', 'MODEM_NS.ETSCTRL.CAPSIGONPRS', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ETSCTRL_CAPTRIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ETSCTRL_CAPTRIG, self).__init__(register,
            'CAPTRIG', 'MODEM_NS.ETSCTRL.CAPTRIG', 'read-write',
            u"",
            12, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ETSTIM_ETSTIMVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ETSTIM_ETSTIMVAL, self).__init__(register,
            'ETSTIMVAL', 'MODEM_NS.ETSTIM.ETSTIMVAL', 'read-write',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ETSTIM_ETSCOUNTEREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ETSTIM_ETSCOUNTEREN, self).__init__(register,
            'ETSCOUNTEREN', 'MODEM_NS.ETSTIM.ETSCOUNTEREN', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWCTRL_ANTDFLTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWCTRL_ANTDFLTSEL, self).__init__(register,
            'ANTDFLTSEL', 'MODEM_NS.ANTSWCTRL.ANTDFLTSEL', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWCTRL_ANTCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWCTRL_ANTCOUNT, self).__init__(register,
            'ANTCOUNT', 'MODEM_NS.ANTSWCTRL.ANTCOUNT', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWCTRL_ANTSWTYPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWCTRL_ANTSWTYPE, self).__init__(register,
            'ANTSWTYPE', 'MODEM_NS.ANTSWCTRL.ANTSWTYPE', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWCTRL_ANTSWRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWCTRL_ANTSWRST, self).__init__(register,
            'ANTSWRST', 'MODEM_NS.ANTSWCTRL.ANTSWRST', 'write-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWCTRL_CFGANTPATTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWCTRL_CFGANTPATTEN, self).__init__(register,
            'CFGANTPATTEN', 'MODEM_NS.ANTSWCTRL.CFGANTPATTEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWCTRL_ANTSWENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWCTRL_ANTSWENABLE, self).__init__(register,
            'ANTSWENABLE', 'MODEM_NS.ANTSWCTRL.ANTSWENABLE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWCTRL_EXTDSTOPPULSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWCTRL_EXTDSTOPPULSECNT, self).__init__(register,
            'EXTDSTOPPULSECNT', 'MODEM_NS.ANTSWCTRL.EXTDSTOPPULSECNT', 'read-write',
            u"",
            17, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWCTRL1_TIMEPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWCTRL1_TIMEPERIOD, self).__init__(register,
            'TIMEPERIOD', 'MODEM_NS.ANTSWCTRL1.TIMEPERIOD', 'read-write',
            u"",
            0, 24)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWSTART_ANTSWSTARTTIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWSTART_ANTSWSTARTTIM, self).__init__(register,
            'ANTSWSTARTTIM', 'MODEM_NS.ANTSWSTART.ANTSWSTARTTIM', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTSWEND_ANTSWENDTIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTSWEND_ANTSWENDTIM, self).__init__(register,
            'ANTSWENDTIM', 'MODEM_NS.ANTSWEND.ANTSWENDTIM', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECPMPATT_PMEXPECTPATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECPMPATT_PMEXPECTPATT, self).__init__(register,
            'PMEXPECTPATT', 'MODEM_NS.TRECPMPATT.PMEXPECTPATT', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECPMDET_PMACQUINGWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECPMDET_PMACQUINGWIN, self).__init__(register,
            'PMACQUINGWIN', 'MODEM_NS.TRECPMDET.PMACQUINGWIN', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECPMDET_PMCOSTVALTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECPMDET_PMCOSTVALTHD, self).__init__(register,
            'PMCOSTVALTHD', 'MODEM_NS.TRECPMDET.PMCOSTVALTHD', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECPMDET_PMTIMEOUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECPMDET_PMTIMEOUTSEL, self).__init__(register,
            'PMTIMEOUTSEL', 'MODEM_NS.TRECPMDET.PMTIMEOUTSEL', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECPMDET_PHSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECPMDET_PHSCALE, self).__init__(register,
            'PHSCALE', 'MODEM_NS.TRECPMDET.PHSCALE', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECPMDET_PMMINCOSTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECPMDET_PMMINCOSTTHD, self).__init__(register,
            'PMMINCOSTTHD', 'MODEM_NS.TRECPMDET.PMMINCOSTTHD', 'read-write',
            u"",
            14, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECPMDET_COSTHYST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECPMDET_COSTHYST, self).__init__(register,
            'COSTHYST', 'MODEM_NS.TRECPMDET.COSTHYST', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECPMDET_PREAMSCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECPMDET_PREAMSCH, self).__init__(register,
            'PREAMSCH', 'MODEM_NS.TRECPMDET.PREAMSCH', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECSCFG_TRECSOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECSCFG_TRECSOSR, self).__init__(register,
            'TRECSOSR', 'MODEM_NS.TRECSCFG.TRECSOSR', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECSCFG_DTIMLOSSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECSCFG_DTIMLOSSTHD, self).__init__(register,
            'DTIMLOSSTHD', 'MODEM_NS.TRECSCFG.DTIMLOSSTHD', 'read-write',
            u"",
            3, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECSCFG_DTIMLOSSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECSCFG_DTIMLOSSEN, self).__init__(register,
            'DTIMLOSSEN', 'MODEM_NS.TRECSCFG.DTIMLOSSEN', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_TRECSCFG_PMOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_TRECSCFG_PMOFFSET, self).__init__(register,
            'PMOFFSET', 'MODEM_NS.TRECSCFG.PMOFFSET', 'read-write',
            u"",
            16, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CFGANTPATT_CFGANTPATTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CFGANTPATT_CFGANTPATTVAL, self).__init__(register,
            'CFGANTPATTVAL', 'MODEM_NS.CFGANTPATT.CFGANTPATTVAL', 'read-write',
            u"",
            0, 30)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE00_SET0COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE00_SET0COEFF0, self).__init__(register,
            'SET0COEFF0', 'MODEM_NS.CHFCOE00.SET0COEFF0', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE00_SET0COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE00_SET0COEFF1, self).__init__(register,
            'SET0COEFF1', 'MODEM_NS.CHFCOE00.SET0COEFF1', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE00_SET0COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE00_SET0COEFF2, self).__init__(register,
            'SET0COEFF2', 'MODEM_NS.CHFCOE00.SET0COEFF2', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE01_SET0COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE01_SET0COEFF3, self).__init__(register,
            'SET0COEFF3', 'MODEM_NS.CHFCOE01.SET0COEFF3', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE01_SET0COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE01_SET0COEFF4, self).__init__(register,
            'SET0COEFF4', 'MODEM_NS.CHFCOE01.SET0COEFF4', 'read-write',
            u"",
            11, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE02_SET0COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE02_SET0COEFF5, self).__init__(register,
            'SET0COEFF5', 'MODEM_NS.CHFCOE02.SET0COEFF5', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE02_SET0COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE02_SET0COEFF6, self).__init__(register,
            'SET0COEFF6', 'MODEM_NS.CHFCOE02.SET0COEFF6', 'read-write',
            u"",
            11, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE03_SET0COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE03_SET0COEFF7, self).__init__(register,
            'SET0COEFF7', 'MODEM_NS.CHFCOE03.SET0COEFF7', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE03_SET0COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE03_SET0COEFF8, self).__init__(register,
            'SET0COEFF8', 'MODEM_NS.CHFCOE03.SET0COEFF8', 'read-write',
            u"",
            12, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE04_SET0COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE04_SET0COEFF9, self).__init__(register,
            'SET0COEFF9', 'MODEM_NS.CHFCOE04.SET0COEFF9', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE04_SET0COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE04_SET0COEFF10, self).__init__(register,
            'SET0COEFF10', 'MODEM_NS.CHFCOE04.SET0COEFF10', 'read-write',
            u"",
            14, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE05_SET0COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE05_SET0COEFF11, self).__init__(register,
            'SET0COEFF11', 'MODEM_NS.CHFCOE05.SET0COEFF11', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE05_SET0COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE05_SET0COEFF12, self).__init__(register,
            'SET0COEFF12', 'MODEM_NS.CHFCOE05.SET0COEFF12', 'read-write',
            u"",
            14, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE06_SET0COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE06_SET0COEFF13, self).__init__(register,
            'SET0COEFF13', 'MODEM_NS.CHFCOE06.SET0COEFF13', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE06_SET0COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE06_SET0COEFF14, self).__init__(register,
            'SET0COEFF14', 'MODEM_NS.CHFCOE06.SET0COEFF14', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE10_SET1COEFF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE10_SET1COEFF0, self).__init__(register,
            'SET1COEFF0', 'MODEM_NS.CHFCOE10.SET1COEFF0', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE10_SET1COEFF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE10_SET1COEFF1, self).__init__(register,
            'SET1COEFF1', 'MODEM_NS.CHFCOE10.SET1COEFF1', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE10_SET1COEFF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE10_SET1COEFF2, self).__init__(register,
            'SET1COEFF2', 'MODEM_NS.CHFCOE10.SET1COEFF2', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE11_SET1COEFF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE11_SET1COEFF3, self).__init__(register,
            'SET1COEFF3', 'MODEM_NS.CHFCOE11.SET1COEFF3', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE11_SET1COEFF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE11_SET1COEFF4, self).__init__(register,
            'SET1COEFF4', 'MODEM_NS.CHFCOE11.SET1COEFF4', 'read-write',
            u"",
            11, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE12_SET1COEFF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE12_SET1COEFF5, self).__init__(register,
            'SET1COEFF5', 'MODEM_NS.CHFCOE12.SET1COEFF5', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE12_SET1COEFF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE12_SET1COEFF6, self).__init__(register,
            'SET1COEFF6', 'MODEM_NS.CHFCOE12.SET1COEFF6', 'read-write',
            u"",
            11, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE13_SET1COEFF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE13_SET1COEFF7, self).__init__(register,
            'SET1COEFF7', 'MODEM_NS.CHFCOE13.SET1COEFF7', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE13_SET1COEFF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE13_SET1COEFF8, self).__init__(register,
            'SET1COEFF8', 'MODEM_NS.CHFCOE13.SET1COEFF8', 'read-write',
            u"",
            12, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE14_SET1COEFF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE14_SET1COEFF9, self).__init__(register,
            'SET1COEFF9', 'MODEM_NS.CHFCOE14.SET1COEFF9', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE14_SET1COEFF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE14_SET1COEFF10, self).__init__(register,
            'SET1COEFF10', 'MODEM_NS.CHFCOE14.SET1COEFF10', 'read-write',
            u"",
            14, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE15_SET1COEFF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE15_SET1COEFF11, self).__init__(register,
            'SET1COEFF11', 'MODEM_NS.CHFCOE15.SET1COEFF11', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE15_SET1COEFF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE15_SET1COEFF12, self).__init__(register,
            'SET1COEFF12', 'MODEM_NS.CHFCOE15.SET1COEFF12', 'read-write',
            u"",
            14, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE16_SET1COEFF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE16_SET1COEFF13, self).__init__(register,
            'SET1COEFF13', 'MODEM_NS.CHFCOE16.SET1COEFF13', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCOE16_SET1COEFF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCOE16_SET1COEFF14, self).__init__(register,
            'SET1COEFF14', 'MODEM_NS.CHFCOE16.SET1COEFF14', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCTRL_FWSWCOEFFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCTRL_FWSWCOEFFEN, self).__init__(register,
            'FWSWCOEFFEN', 'MODEM_NS.CHFCTRL.FWSWCOEFFEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCTRL_FWSELCOEFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCTRL_FWSELCOEFF, self).__init__(register,
            'FWSELCOEFF', 'MODEM_NS.CHFCTRL.FWSELCOEFF', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFCTRL_SWCOEFFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFCTRL_SWCOEFFEN, self).__init__(register,
            'SWCOEFFEN', 'MODEM_NS.CHFCTRL.SWCOEFFEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_CHFLATENCYCTRL_CHFLATENCY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_CHFLATENCYCTRL_CHFLATENCY, self).__init__(register,
            'CHFLATENCY', 'MODEM_NS.CHFLATENCYCTRL.CHFLATENCY', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FRMSCHTIME_FRMSCHTIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FRMSCHTIME_FRMSCHTIME, self).__init__(register,
            'FRMSCHTIME', 'MODEM_NS.FRMSCHTIME.FRMSCHTIME', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FRMSCHTIME_PMRSTSYCNEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FRMSCHTIME_PMRSTSYCNEN, self).__init__(register,
            'PMRSTSYCNEN', 'MODEM_NS.FRMSCHTIME.PMRSTSYCNEN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FRMSCHTIME_DSARSTSYCNEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FRMSCHTIME_DSARSTSYCNEN, self).__init__(register,
            'DSARSTSYCNEN', 'MODEM_NS.FRMSCHTIME.DSARSTSYCNEN', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_FRMSCHTIME_PMENDSCHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_FRMSCHTIME_PMENDSCHEN, self).__init__(register,
            'PMENDSCHEN', 'MODEM_NS.FRMSCHTIME.PMENDSCHEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PREFILTCOEFF_PREFILTCOEFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PREFILTCOEFF_PREFILTCOEFF, self).__init__(register,
            'PREFILTCOEFF', 'MODEM_NS.PREFILTCOEFF.PREFILTCOEFF', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXRESTART_RXRESTARTUPONMARSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXRESTART_RXRESTARTUPONMARSSI, self).__init__(register,
            'RXRESTARTUPONMARSSI', 'MODEM_NS.RXRESTART.RXRESTARTUPONMARSSI', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXRESTART_RXRESTARTMATHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXRESTART_RXRESTARTMATHRESHOLD, self).__init__(register,
            'RXRESTARTMATHRESHOLD', 'MODEM_NS.RXRESTART.RXRESTARTMATHRESHOLD', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXRESTART_RXRESTARTMALATCHSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXRESTART_RXRESTARTMALATCHSEL, self).__init__(register,
            'RXRESTARTMALATCHSEL', 'MODEM_NS.RXRESTART.RXRESTARTMALATCHSEL', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXRESTART_RXRESTARTMACOMPENSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXRESTART_RXRESTARTMACOMPENSEL, self).__init__(register,
            'RXRESTARTMACOMPENSEL', 'MODEM_NS.RXRESTART.RXRESTARTMACOMPENSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXRESTART_RXRESTARTMATAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXRESTART_RXRESTARTMATAP, self).__init__(register,
            'RXRESTARTMATAP', 'MODEM_NS.RXRESTART.RXRESTARTMATAP', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXRESTART_RXRESTARTB4PREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXRESTART_RXRESTARTB4PREDET, self).__init__(register,
            'RXRESTARTB4PREDET', 'MODEM_NS.RXRESTART.RXRESTARTB4PREDET', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXRESTART_ANTSWRSTFLTTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXRESTART_ANTSWRSTFLTTDIS, self).__init__(register,
            'ANTSWRSTFLTTDIS', 'MODEM_NS.RXRESTART.ANTSWRSTFLTTDIS', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_RXRESTART_FLTRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_RXRESTART_FLTRSTEN, self).__init__(register,
            'FLTRSTEN', 'MODEM_NS.RXRESTART.FLTRSTEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SQ_SQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SQ_SQEN, self).__init__(register,
            'SQEN', 'MODEM_NS.SQ.SQEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SQ_SQSWRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SQ_SQSWRST, self).__init__(register,
            'SQSWRST', 'MODEM_NS.SQ.SQSWRST', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SQ_SQTIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SQ_SQTIMOUT, self).__init__(register,
            'SQTIMOUT', 'MODEM_NS.SQ.SQTIMOUT', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SQEXT_SQSTG2TIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SQEXT_SQSTG2TIMOUT, self).__init__(register,
            'SQSTG2TIMOUT', 'MODEM_NS.SQEXT.SQSTG2TIMOUT', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SQEXT_SQSTG3TIMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SQEXT_SQSTG3TIMOUT, self).__init__(register,
            'SQSTG3TIMOUT', 'MODEM_NS.SQEXT.SQSTG3TIMOUT', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SQI_SQISELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SQI_SQISELECT, self).__init__(register,
            'SQISELECT', 'MODEM_NS.SQI.SQISELECT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SQI_CHIPERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SQI_CHIPERROR, self).__init__(register,
            'CHIPERROR', 'MODEM_NS.SQI.CHIPERROR', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTDIVCTRL_ADPRETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTDIVCTRL_ADPRETHRESH, self).__init__(register,
            'ADPRETHRESH', 'MODEM_NS.ANTDIVCTRL.ADPRETHRESH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTDIVCTRL_ENADPRETHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTDIVCTRL_ENADPRETHRESH, self).__init__(register,
            'ENADPRETHRESH', 'MODEM_NS.ANTDIVCTRL.ENADPRETHRESH', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTDIVCTRL_ANTDIVDISCCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTDIVCTRL_ANTDIVDISCCA, self).__init__(register,
            'ANTDIVDISCCA', 'MODEM_NS.ANTDIVCTRL.ANTDIVDISCCA', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTDIVCTRL_ANTDIVSELCCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTDIVCTRL_ANTDIVSELCCA, self).__init__(register,
            'ANTDIVSELCCA', 'MODEM_NS.ANTDIVCTRL.ANTDIVSELCCA', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTDIVFW_FWSELANT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTDIVFW_FWSELANT, self).__init__(register,
            'FWSELANT', 'MODEM_NS.ANTDIVFW.FWSELANT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTDIVFW_FWANTSWCMD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTDIVFW_FWANTSWCMD, self).__init__(register,
            'FWANTSWCMD', 'MODEM_NS.ANTDIVFW.FWANTSWCMD', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ANTDIVFW_FWANTDIVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ANTDIVFW_FWANTDIVEN, self).__init__(register,
            'FWANTDIVEN', 'MODEM_NS.ANTDIVFW.FWANTDIVEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODANTDIV_ANTWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODANTDIV_ANTWAIT, self).__init__(register,
            'ANTWAIT', 'MODEM_NS.PHDMODANTDIV.ANTWAIT', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODANTDIV_SKIPRSSITHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODANTDIV_SKIPRSSITHD, self).__init__(register,
            'SKIPRSSITHD', 'MODEM_NS.PHDMODANTDIV.SKIPRSSITHD', 'read-write',
            u"",
            5, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODANTDIV_SKIPCORRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODANTDIV_SKIPCORRTHD, self).__init__(register,
            'SKIPCORRTHD', 'MODEM_NS.PHDMODANTDIV.SKIPCORRTHD', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODANTDIV_SKIP2ANT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODANTDIV_SKIP2ANT, self).__init__(register,
            'SKIP2ANT', 'MODEM_NS.PHDMODANTDIV.SKIP2ANT', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHANTDECSION_CORRANDDIVTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHANTDECSION_CORRANDDIVTHD, self).__init__(register,
            'CORRANDDIVTHD', 'MODEM_NS.PHANTDECSION.CORRANDDIVTHD', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHANTDECSION_RSSIANDDIVTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHANTDECSION_RSSIANDDIVTHD, self).__init__(register,
            'RSSIANDDIVTHD', 'MODEM_NS.PHANTDECSION.RSSIANDDIVTHD', 'read-write',
            u"",
            10, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHANTDECSION_RSSICORR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHANTDECSION_RSSICORR0, self).__init__(register,
            'RSSICORR0', 'MODEM_NS.PHANTDECSION.RSSICORR0', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHANTDECSION_RSSICORR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHANTDECSION_RSSICORR1, self).__init__(register,
            'RSSICORR1', 'MODEM_NS.PHANTDECSION.RSSICORR1', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHANTDECSION_RSSICORR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHANTDECSION_RSSICORR2, self).__init__(register,
            'RSSICORR2', 'MODEM_NS.PHANTDECSION.RSSICORR2', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHANTDECSION_RSSICORR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHANTDECSION_RSSICORR3, self).__init__(register,
            'RSSICORR3', 'MODEM_NS.PHANTDECSION.RSSICORR3', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_PMDETTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_PMDETTHD, self).__init__(register,
            'PMDETTHD', 'MODEM_NS.PHDMODCTRL.PMDETTHD', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_PMTIMLOSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_PMTIMLOSTHD, self).__init__(register,
            'PMTIMLOSTHD', 'MODEM_NS.PHDMODCTRL.PMTIMLOSTHD', 'read-write',
            u"",
            5, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_PMTIMLOSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_PMTIMLOSEN, self).__init__(register,
            'PMTIMLOSEN', 'MODEM_NS.PHDMODCTRL.PMTIMLOSEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_RSSIFLTBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_RSSIFLTBYP, self).__init__(register,
            'RSSIFLTBYP', 'MODEM_NS.PHDMODCTRL.RSSIFLTBYP', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_PMDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_PMDETEN, self).__init__(register,
            'PMDETEN', 'MODEM_NS.PHDMODCTRL.PMDETEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_REMODOSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_REMODOSR, self).__init__(register,
            'REMODOSR', 'MODEM_NS.PHDMODCTRL.REMODOSR', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_REMODDWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_REMODDWN, self).__init__(register,
            'REMODDWN', 'MODEM_NS.PHDMODCTRL.REMODDWN', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_REMODOUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_REMODOUTSEL, self).__init__(register,
            'REMODOUTSEL', 'MODEM_NS.PHDMODCTRL.REMODOUTSEL', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_REMODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_REMODEN, self).__init__(register,
            'REMODEN', 'MODEM_NS.PHDMODCTRL.REMODEN', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_BCRDETECTOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_BCRDETECTOR, self).__init__(register,
            'BCRDETECTOR', 'MODEM_NS.PHDMODCTRL.BCRDETECTOR', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_BCRTRECSCONC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_BCRTRECSCONC, self).__init__(register,
            'BCRTRECSCONC', 'MODEM_NS.PHDMODCTRL.BCRTRECSCONC', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL_BCRLEGACYCONC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL_BCRLEGACYCONC, self).__init__(register,
            'BCRLEGACYCONC', 'MODEM_NS.PHDMODCTRL.BCRLEGACYCONC', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_PHDMODCTRL1_TRECSFREQESTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_PHDMODCTRL1_TRECSFREQESTSEL, self).__init__(register,
            'TRECSFREQESTSEL', 'MODEM_NS.PHDMODCTRL1.TRECSFREQESTSEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LOG2X4_LOG2X4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LOG2X4_LOG2X4, self).__init__(register,
            'LOG2X4', 'MODEM_NS.LOG2X4.LOG2X4', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_LOG2X4_LOG2X4FWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_LOG2X4_LOG2X4FWSEL, self).__init__(register,
            'LOG2X4FWSEL', 'MODEM_NS.LOG2X4.LOG2X4FWSEL', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCAL_IRCALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCAL_IRCALEN, self).__init__(register,
            'IRCALEN', 'MODEM_NS.IRCAL.IRCALEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCAL_MURSHF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCAL_MURSHF, self).__init__(register,
            'MURSHF', 'MODEM_NS.IRCAL.MURSHF', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCAL_MUISHF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCAL_MUISHF, self).__init__(register,
            'MUISHF', 'MODEM_NS.IRCAL.MUISHF', 'read-write',
            u"",
            7, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCAL_IRCORREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCAL_IRCORREN, self).__init__(register,
            'IRCORREN', 'MODEM_NS.IRCAL.IRCORREN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCAL_IRCALCOEFRSTCMD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCAL_IRCALCOEFRSTCMD, self).__init__(register,
            'IRCALCOEFRSTCMD', 'MODEM_NS.IRCAL.IRCALCOEFRSTCMD', 'write-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCAL_IRCALIFADCDBG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCAL_IRCALIFADCDBG, self).__init__(register,
            'IRCALIFADCDBG', 'MODEM_NS.IRCAL.IRCALIFADCDBG', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEF_CRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEF_CRV, self).__init__(register,
            'CRV', 'MODEM_NS.IRCALCOEF.CRV', 'read-only',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEF_CIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEF_CIV, self).__init__(register,
            'CIV', 'MODEM_NS.IRCALCOEF.CIV', 'read-only',
            u"",
            16, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEFWR0_CRVWD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEFWR0_CRVWD, self).__init__(register,
            'CRVWD', 'MODEM_NS.IRCALCOEFWR0.CRVWD', 'read-write',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEFWR0_CRVWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEFWR0_CRVWEN, self).__init__(register,
            'CRVWEN', 'MODEM_NS.IRCALCOEFWR0.CRVWEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEFWR0_CIVWD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEFWR0_CIVWD, self).__init__(register,
            'CIVWD', 'MODEM_NS.IRCALCOEFWR0.CIVWD', 'read-write',
            u"",
            16, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEFWR0_CIVWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEFWR0_CIVWEN, self).__init__(register,
            'CIVWEN', 'MODEM_NS.IRCALCOEFWR0.CIVWEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEFWR1_CRVWD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEFWR1_CRVWD, self).__init__(register,
            'CRVWD', 'MODEM_NS.IRCALCOEFWR1.CRVWD', 'read-write',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEFWR1_CRVWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEFWR1_CRVWEN, self).__init__(register,
            'CRVWEN', 'MODEM_NS.IRCALCOEFWR1.CRVWEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEFWR1_CIVWD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEFWR1_CIVWD, self).__init__(register,
            'CIVWD', 'MODEM_NS.IRCALCOEFWR1.CIVWD', 'read-write',
            u"",
            16, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_IRCALCOEFWR1_CIVWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_IRCALCOEFWR1_CIVWEN, self).__init__(register,
            'CIVWEN', 'MODEM_NS.IRCALCOEFWR1.CIVWEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADCTRL1_ADCTRL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADCTRL1_ADCTRL1, self).__init__(register,
            'ADCTRL1', 'MODEM_NS.ADCTRL1.ADCTRL1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADCTRL2_ADCTRL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADCTRL2_ADCTRL2, self).__init__(register,
            'ADCTRL2', 'MODEM_NS.ADCTRL2.ADCTRL2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL0_ADRSSI0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL0_ADRSSI0, self).__init__(register,
            'ADRSSI0', 'MODEM_NS.ADQUAL0.ADRSSI0', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL0_ADRSSI1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL0_ADRSSI1, self).__init__(register,
            'ADRSSI1', 'MODEM_NS.ADQUAL0.ADRSSI1', 'read-only',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL1_ADCORR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL1_ADCORR0, self).__init__(register,
            'ADCORR0', 'MODEM_NS.ADQUAL1.ADCORR0', 'read-only',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL1_ADSTAT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL1_ADSTAT1, self).__init__(register,
            'ADSTAT1', 'MODEM_NS.ADQUAL1.ADSTAT1', 'read-only',
            u"",
            17, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL2_ADRSSI0P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL2_ADRSSI0P, self).__init__(register,
            'ADRSSI0P', 'MODEM_NS.ADQUAL2.ADRSSI0P', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL2_ADRSSI1P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL2_ADRSSI1P, self).__init__(register,
            'ADRSSI1P', 'MODEM_NS.ADQUAL2.ADRSSI1P', 'read-only',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL3_ADCORR0P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL3_ADCORR0P, self).__init__(register,
            'ADCORR0P', 'MODEM_NS.ADQUAL3.ADCORR0P', 'read-only',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL3_ADSTAT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL3_ADSTAT2, self).__init__(register,
            'ADSTAT2', 'MODEM_NS.ADQUAL3.ADSTAT2', 'read-only',
            u"",
            17, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL4_ADAGCGRTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL4_ADAGCGRTHR, self).__init__(register,
            'ADAGCGRTHR', 'MODEM_NS.ADQUAL4.ADAGCGRTHR', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL4_ADRSSIGRTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL4_ADRSSIGRTHR, self).__init__(register,
            'ADRSSIGRTHR', 'MODEM_NS.ADQUAL4.ADRSSIGRTHR', 'read-write',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL4_ADGRMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL4_ADGRMODE, self).__init__(register,
            'ADGRMODE', 'MODEM_NS.ADQUAL4.ADGRMODE', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL5_ADDIRECTCORR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL5_ADDIRECTCORR, self).__init__(register,
            'ADDIRECTCORR', 'MODEM_NS.ADQUAL5.ADDIRECTCORR', 'read-write',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL6_ADBACORRTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL6_ADBACORRTHR, self).__init__(register,
            'ADBACORRTHR', 'MODEM_NS.ADQUAL6.ADBACORRTHR', 'read-write',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL6_ADBACORRDIFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL6_ADBACORRDIFF, self).__init__(register,
            'ADBACORRDIFF', 'MODEM_NS.ADQUAL6.ADBACORRDIFF', 'read-write',
            u"",
            17, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL7_ADBARSSITHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL7_ADBARSSITHR, self).__init__(register,
            'ADBARSSITHR', 'MODEM_NS.ADQUAL7.ADBARSSITHR', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL7_ADBARSSIDIFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL7_ADBARSSIDIFF, self).__init__(register,
            'ADBARSSIDIFF', 'MODEM_NS.ADQUAL7.ADBARSSIDIFF', 'read-write',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL8_ADBAAGCTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL8_ADBAAGCTHR, self).__init__(register,
            'ADBAAGCTHR', 'MODEM_NS.ADQUAL8.ADBAAGCTHR', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL8_ADBAMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL8_ADBAMODE, self).__init__(register,
            'ADBAMODE', 'MODEM_NS.ADQUAL8.ADBAMODE', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL9_ADCORR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL9_ADCORR1, self).__init__(register,
            'ADCORR1', 'MODEM_NS.ADQUAL9.ADCORR1', 'read-only',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADQUAL10_ADCORR1P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADQUAL10_ADCORR1P, self).__init__(register,
            'ADCORR1P', 'MODEM_NS.ADQUAL10.ADCORR1P', 'read-only',
            u"",
            0, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADSTATEC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADSTATEC, self).__init__(register,
            'ADSTATEC', 'MODEM_NS.ADFSM0.ADSTATEC', 'read-only',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADSTATEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADSTATEP, self).__init__(register,
            'ADSTATEP', 'MODEM_NS.ADFSM0.ADSTATEP', 'read-only',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADSTATEP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADSTATEP2, self).__init__(register,
            'ADSTATEP2', 'MODEM_NS.ADFSM0.ADSTATEP2', 'read-only',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADSTATEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADSTATEN, self).__init__(register,
            'ADSTATEN', 'MODEM_NS.ADFSM0.ADSTATEN', 'read-only',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADTD0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADTD0, self).__init__(register,
            'ADTD0', 'MODEM_NS.ADFSM0.ADTD0', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADTD0P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADTD0P, self).__init__(register,
            'ADTD0P', 'MODEM_NS.ADFSM0.ADTD0P', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADTD1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADTD1, self).__init__(register,
            'ADTD1', 'MODEM_NS.ADFSM0.ADTD1', 'read-only',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADTD1P(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADTD1P, self).__init__(register,
            'ADTD1P', 'MODEM_NS.ADFSM0.ADTD1P', 'read-only',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADAS, self).__init__(register,
            'ADAS', 'MODEM_NS.ADFSM0.ADAS', 'read-only',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADBA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADBA, self).__init__(register,
            'ADBA', 'MODEM_NS.ADFSM0.ADBA', 'read-only',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADSTATREAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADSTATREAD, self).__init__(register,
            'ADSTATREAD', 'MODEM_NS.ADFSM0.ADSTATREAD', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADSTAT1SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADSTAT1SEL, self).__init__(register,
            'ADSTAT1SEL', 'MODEM_NS.ADFSM0.ADSTAT1SEL', 'read-write',
            u"",
            23, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM0_ADSTAT2SEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM0_ADSTAT2SEL, self).__init__(register,
            'ADSTAT2SEL', 'MODEM_NS.ADFSM0.ADSTAT2SEL', 'read-write',
            u"",
            27, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM1_ADOSETANT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM1_ADOSETANT0, self).__init__(register,
            'ADOSETANT0', 'MODEM_NS.ADFSM1.ADOSETANT0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM1_ADOSETANT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM1_ADOSETANT1, self).__init__(register,
            'ADOSETANT1', 'MODEM_NS.ADFSM1.ADOSETANT1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM2_ADOSWITCHANT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM2_ADOSWITCHANT, self).__init__(register,
            'ADOSWITCHANT', 'MODEM_NS.ADFSM2.ADOSWITCHANT', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM2_ADORESTARTRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM2_ADORESTARTRX, self).__init__(register,
            'ADORESTARTRX', 'MODEM_NS.ADFSM2.ADORESTARTRX', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM3_ADOQUAL0UPDATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM3_ADOQUAL0UPDATE, self).__init__(register,
            'ADOQUAL0UPDATE', 'MODEM_NS.ADFSM3.ADOQUAL0UPDATE', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM3_ADOQUAL1UPDATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM3_ADOQUAL1UPDATE, self).__init__(register,
            'ADOQUAL1UPDATE', 'MODEM_NS.ADFSM3.ADOQUAL1UPDATE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM4_ADOQUAL0CLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM4_ADOQUAL0CLEAR, self).__init__(register,
            'ADOQUAL0CLEAR', 'MODEM_NS.ADFSM4.ADOQUAL0CLEAR', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM4_ADOQUAL1CLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM4_ADOQUAL1CLEAR, self).__init__(register,
            'ADOQUAL1CLEAR', 'MODEM_NS.ADFSM4.ADOQUAL1CLEAR', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM5_ADOMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM5_ADOMUX, self).__init__(register,
            'ADOMUX', 'MODEM_NS.ADFSM5.ADOMUX', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM6_ADNEXTSTATESW0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM6_ADNEXTSTATESW0, self).__init__(register,
            'ADNEXTSTATESW0', 'MODEM_NS.ADFSM6.ADNEXTSTATESW0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM6_ADNEXTSTATESW1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM6_ADNEXTSTATESW1, self).__init__(register,
            'ADNEXTSTATESW1', 'MODEM_NS.ADFSM6.ADNEXTSTATESW1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM7_ADNEXTSTATESW2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM7_ADNEXTSTATESW2, self).__init__(register,
            'ADNEXTSTATESW2', 'MODEM_NS.ADFSM7.ADNEXTSTATESW2', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM7_ADNEXTSTATESW3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM7_ADNEXTSTATESW3, self).__init__(register,
            'ADNEXTSTATESW3', 'MODEM_NS.ADFSM7.ADNEXTSTATESW3', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM8_ADNEXTSTATESW4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM8_ADNEXTSTATESW4, self).__init__(register,
            'ADNEXTSTATESW4', 'MODEM_NS.ADFSM8.ADNEXTSTATESW4', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM8_ADNEXTSTATESW5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM8_ADNEXTSTATESW5, self).__init__(register,
            'ADNEXTSTATESW5', 'MODEM_NS.ADFSM8.ADNEXTSTATESW5', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM9_ADNEXTSTATESW6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM9_ADNEXTSTATESW6, self).__init__(register,
            'ADNEXTSTATESW6', 'MODEM_NS.ADFSM9.ADNEXTSTATESW6', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM9_ADNEXTSTATESW7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM9_ADNEXTSTATESW7, self).__init__(register,
            'ADNEXTSTATESW7', 'MODEM_NS.ADFSM9.ADNEXTSTATESW7', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM10_ADNEXTSTATESW8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM10_ADNEXTSTATESW8, self).__init__(register,
            'ADNEXTSTATESW8', 'MODEM_NS.ADFSM10.ADNEXTSTATESW8', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM10_ADNEXTSTATESW9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM10_ADNEXTSTATESW9, self).__init__(register,
            'ADNEXTSTATESW9', 'MODEM_NS.ADFSM10.ADNEXTSTATESW9', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM11_ADNEXTSTATESW10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM11_ADNEXTSTATESW10, self).__init__(register,
            'ADNEXTSTATESW10', 'MODEM_NS.ADFSM11.ADNEXTSTATESW10', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM11_ADNEXTSTATESW11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM11_ADNEXTSTATESW11, self).__init__(register,
            'ADNEXTSTATESW11', 'MODEM_NS.ADFSM11.ADNEXTSTATESW11', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM12_ADNEXTSTATESW12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM12_ADNEXTSTATESW12, self).__init__(register,
            'ADNEXTSTATESW12', 'MODEM_NS.ADFSM12.ADNEXTSTATESW12', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM12_ADNEXTSTATESW13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM12_ADNEXTSTATESW13, self).__init__(register,
            'ADNEXTSTATESW13', 'MODEM_NS.ADFSM12.ADNEXTSTATESW13', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM13_ADNEXTSTATESW14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM13_ADNEXTSTATESW14, self).__init__(register,
            'ADNEXTSTATESW14', 'MODEM_NS.ADFSM13.ADNEXTSTATESW14', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM13_ADNEXTSTATESW15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM13_ADNEXTSTATESW15, self).__init__(register,
            'ADNEXTSTATESW15', 'MODEM_NS.ADFSM13.ADNEXTSTATESW15', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM14_ADFSMCOND0ENA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM14_ADFSMCOND0ENA, self).__init__(register,
            'ADFSMCOND0ENA', 'MODEM_NS.ADFSM14.ADFSMCOND0ENA', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM14_ADFSMCOND1ENA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM14_ADFSMCOND1ENA, self).__init__(register,
            'ADFSMCOND1ENA', 'MODEM_NS.ADFSM14.ADFSMCOND1ENA', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM15_ADFSMCOND2ENA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM15_ADFSMCOND2ENA, self).__init__(register,
            'ADFSMCOND2ENA', 'MODEM_NS.ADFSM15.ADFSMCOND2ENA', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM15_ADFSMCOND3ENA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM15_ADFSMCOND3ENA, self).__init__(register,
            'ADFSMCOND3ENA', 'MODEM_NS.ADFSM15.ADFSMCOND3ENA', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM16_ADFSMCOND0ENB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM16_ADFSMCOND0ENB, self).__init__(register,
            'ADFSMCOND0ENB', 'MODEM_NS.ADFSM16.ADFSMCOND0ENB', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM16_ADFSMCOND1ENB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM16_ADFSMCOND1ENB, self).__init__(register,
            'ADFSMCOND1ENB', 'MODEM_NS.ADFSM16.ADFSMCOND1ENB', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM17_ADFSMCOND2ENB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM17_ADFSMCOND2ENB, self).__init__(register,
            'ADFSMCOND2ENB', 'MODEM_NS.ADFSM17.ADFSMCOND2ENB', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM17_ADFSMCOND3ENB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM17_ADFSMCOND3ENB, self).__init__(register,
            'ADFSMCOND3ENB', 'MODEM_NS.ADFSM17.ADFSMCOND3ENB', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM18_ADFSMCONDSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM18_ADFSMCONDSEL, self).__init__(register,
            'ADFSMCONDSEL', 'MODEM_NS.ADFSM18.ADFSMCONDSEL', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM19_ADFSMNEXTFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM19_ADFSMNEXTFORCE, self).__init__(register,
            'ADFSMNEXTFORCE', 'MODEM_NS.ADFSM19.ADFSMNEXTFORCE', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM19_ADFSMCONDTRUE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM19_ADFSMCONDTRUE, self).__init__(register,
            'ADFSMCONDTRUE', 'MODEM_NS.ADFSM19.ADFSMCONDTRUE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM20_ADITENTEREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM20_ADITENTEREN, self).__init__(register,
            'ADITENTEREN', 'MODEM_NS.ADFSM20.ADITENTEREN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM20_ADITLEAVEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM20_ADITLEAVEEN, self).__init__(register,
            'ADITLEAVEEN', 'MODEM_NS.ADFSM20.ADITLEAVEEN', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM21_ADENTERFREEZEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM21_ADENTERFREEZEEN, self).__init__(register,
            'ADENTERFREEZEEN', 'MODEM_NS.ADFSM21.ADENTERFREEZEEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM21_ADLEAVEFREEZEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM21_ADLEAVEFREEZEEN, self).__init__(register,
            'ADLEAVEFREEZEEN', 'MODEM_NS.ADFSM21.ADLEAVEFREEZEEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM21_ADFROZEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM21_ADFROZEN, self).__init__(register,
            'ADFROZEN', 'MODEM_NS.ADFSM21.ADFROZEN', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM21_ADUNFREEZENEXT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM21_ADUNFREEZENEXT, self).__init__(register,
            'ADUNFREEZENEXT', 'MODEM_NS.ADFSM21.ADUNFREEZENEXT', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM21_ADUNFREEZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM21_ADUNFREEZE, self).__init__(register,
            'ADUNFREEZE', 'MODEM_NS.ADFSM21.ADUNFREEZE', 'write-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM22_ADITENTERSTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM22_ADITENTERSTATUS, self).__init__(register,
            'ADITENTERSTATUS', 'MODEM_NS.ADFSM22.ADITENTERSTATUS', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM22_ADITLEAVESTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM22_ADITLEAVESTATUS, self).__init__(register,
            'ADITLEAVESTATUS', 'MODEM_NS.ADFSM22.ADITLEAVESTATUS', 'read-only',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM23_ADFSMCOND0ENC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM23_ADFSMCOND0ENC, self).__init__(register,
            'ADFSMCOND0ENC', 'MODEM_NS.ADFSM23.ADFSMCOND0ENC', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM23_ADFSMCOND1ENC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM23_ADFSMCOND1ENC, self).__init__(register,
            'ADFSMCOND1ENC', 'MODEM_NS.ADFSM23.ADFSMCOND1ENC', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM24_ADFSMCOND2ENC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM24_ADFSMCOND2ENC, self).__init__(register,
            'ADFSMCOND2ENC', 'MODEM_NS.ADFSM24.ADFSMCOND2ENC', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM24_ADFSMCOND3ENC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM24_ADFSMCOND3ENC, self).__init__(register,
            'ADFSMCOND3ENC', 'MODEM_NS.ADFSM24.ADFSMCOND3ENC', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM25_ADFSMCONDOR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM25_ADFSMCONDOR0, self).__init__(register,
            'ADFSMCONDOR0', 'MODEM_NS.ADFSM25.ADFSMCONDOR0', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM25_ADFSMCONDOR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM25_ADFSMCONDOR1, self).__init__(register,
            'ADFSMCONDOR1', 'MODEM_NS.ADFSM25.ADFSMCONDOR1', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM26_ADFSMCOND0END(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM26_ADFSMCOND0END, self).__init__(register,
            'ADFSMCOND0END', 'MODEM_NS.ADFSM26.ADFSMCOND0END', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM26_ADFSMCOND1END(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM26_ADFSMCOND1END, self).__init__(register,
            'ADFSMCOND1END', 'MODEM_NS.ADFSM26.ADFSMCOND1END', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM27_ADFSMCOND2END(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM27_ADFSMCOND2END, self).__init__(register,
            'ADFSMCOND2END', 'MODEM_NS.ADFSM27.ADFSMCOND2END', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM27_ADFSMCOND3END(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM27_ADFSMCOND3END, self).__init__(register,
            'ADFSMCOND3END', 'MODEM_NS.ADFSM27.ADFSMCOND3END', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM28_ADOSETANTFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM28_ADOSETANTFORCE, self).__init__(register,
            'ADOSETANTFORCE', 'MODEM_NS.ADFSM28.ADOSETANTFORCE', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM28_ADORESTARTRXFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM28_ADORESTARTRXFORCE, self).__init__(register,
            'ADORESTARTRXFORCE', 'MODEM_NS.ADFSM28.ADORESTARTRXFORCE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM29_ADOQUALUPDATEFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM29_ADOQUALUPDATEFORCE, self).__init__(register,
            'ADOQUALUPDATEFORCE', 'MODEM_NS.ADFSM29.ADOQUALUPDATEFORCE', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM29_ADOQUALCLEARFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM29_ADOQUALCLEARFORCE, self).__init__(register,
            'ADOQUALCLEARFORCE', 'MODEM_NS.ADFSM29.ADOQUALCLEARFORCE', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_ADFSM30_ADODEMODRXREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_ADFSM30_ADODEMODRXREQ, self).__init__(register,
            'ADODEMODRXREQ', 'MODEM_NS.ADFSM30.ADODEMODRXREQ', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL0_BCRNCOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL0_BCRNCOFF, self).__init__(register,
            'BCRNCOFF', 'MODEM_NS.BCRCTRL0.BCRNCOFF', 'read-write',
            u"",
            0, 22)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL0_BCRERRRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL0_BCRERRRSTEN, self).__init__(register,
            'BCRERRRSTEN', 'MODEM_NS.BCRCTRL0.BCRERRRSTEN', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL0_BCRFBBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL0_BCRFBBYP, self).__init__(register,
            'BCRFBBYP', 'MODEM_NS.BCRCTRL0.BCRFBBYP', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL0_BCRALIGN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL0_BCRALIGN, self).__init__(register,
            'BCRALIGN', 'MODEM_NS.BCRCTRL0.BCRALIGN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL0_DISTOGG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL0_DISTOGG, self).__init__(register,
            'DISTOGG', 'MODEM_NS.BCRCTRL0.DISTOGG', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL0_CRSLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL0_CRSLOW, self).__init__(register,
            'CRSLOW', 'MODEM_NS.BCRCTRL0.CRSLOW', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL0_CRFAST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL0_CRFAST, self).__init__(register,
            'CRFAST', 'MODEM_NS.BCRCTRL0.CRFAST', 'read-write',
            u"",
            29, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_CRGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_CRGAIN, self).__init__(register,
            'CRGAIN', 'MODEM_NS.BCRCTRL1.CRGAIN', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_CGAINX2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_CGAINX2, self).__init__(register,
            'CGAINX2', 'MODEM_NS.BCRCTRL1.CGAINX2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_RXNCOCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_RXNCOCOMP, self).__init__(register,
            'RXNCOCOMP', 'MODEM_NS.BCRCTRL1.RXNCOCOMP', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_RXCOMPLAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_RXCOMPLAT, self).__init__(register,
            'RXCOMPLAT', 'MODEM_NS.BCRCTRL1.RXCOMPLAT', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_ESCMIDPT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_ESCMIDPT, self).__init__(register,
            'ESCMIDPT', 'MODEM_NS.BCRCTRL1.ESCMIDPT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_DISMIDPT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_DISMIDPT, self).__init__(register,
            'DISMIDPT', 'MODEM_NS.BCRCTRL1.DISMIDPT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_BCROSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_BCROSR, self).__init__(register,
            'BCROSR', 'MODEM_NS.BCRCTRL1.BCROSR', 'read-write',
            u"",
            16, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_ESTOSREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_ESTOSREN, self).__init__(register,
            'ESTOSREN', 'MODEM_NS.BCRCTRL1.ESTOSREN', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_BCRSWSYCW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_BCRSWSYCW, self).__init__(register,
            'BCRSWSYCW', 'MODEM_NS.BCRCTRL1.BCRSWSYCW', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_PHCOMP2FSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_PHCOMP2FSK, self).__init__(register,
            'PHCOMP2FSK', 'MODEM_NS.BCRCTRL1.PHCOMP2FSK', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRCTRL1_SLICEFBBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRCTRL1_SLICEFBBYP, self).__init__(register,
            'SLICEFBBYP', 'MODEM_NS.BCRCTRL1.SLICEFBBYP', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_BCRDEMODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_BCRDEMODEN, self).__init__(register,
            'BCRDEMODEN', 'MODEM_NS.BCRDEMODCTRL.BCRDEMODEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_PULCORRBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_PULCORRBYP, self).__init__(register,
            'PULCORRBYP', 'MODEM_NS.BCRDEMODCTRL.PULCORRBYP', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_RAWSYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_RAWSYN, self).__init__(register,
            'RAWSYN', 'MODEM_NS.BCRDEMODCTRL.RAWSYN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_CONSCHKBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_CONSCHKBYP, self).__init__(register,
            'CONSCHKBYP', 'MODEM_NS.BCRDEMODCTRL.CONSCHKBYP', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_PH0SIZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_PH0SIZE, self).__init__(register,
            'PH0SIZE', 'MODEM_NS.BCRDEMODCTRL.PH0SIZE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_LOCKUPBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_LOCKUPBYP, self).__init__(register,
            'LOCKUPBYP', 'MODEM_NS.BCRDEMODCTRL.LOCKUPBYP', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_RAWFASTMA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_RAWFASTMA, self).__init__(register,
            'RAWFASTMA', 'MODEM_NS.BCRDEMODCTRL.RAWFASTMA', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_SPIKEREMOV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_SPIKEREMOV, self).__init__(register,
            'SPIKEREMOV', 'MODEM_NS.BCRDEMODCTRL.SPIKEREMOV', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_RAWFLTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_RAWFLTSEL, self).__init__(register,
            'RAWFLTSEL', 'MODEM_NS.BCRDEMODCTRL.RAWFLTSEL', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_MANCHDLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_MANCHDLY, self).__init__(register,
            'MANCHDLY', 'MODEM_NS.BCRDEMODCTRL.MANCHDLY', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_CICDINSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_CICDINSCALE, self).__init__(register,
            'CICDINSCALE', 'MODEM_NS.BCRDEMODCTRL.CICDINSCALE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_DATAFLTBY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_DATAFLTBY, self).__init__(register,
            'DATAFLTBY', 'MODEM_NS.BCRDEMODCTRL.DATAFLTBY', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_RSTEXTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_RSTEXTEN, self).__init__(register,
            'RSTEXTEN', 'MODEM_NS.BCRDEMODCTRL.RSTEXTEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_PREATH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_PREATH, self).__init__(register,
            'PREATH', 'MODEM_NS.BCRDEMODCTRL.PREATH', 'read-write',
            u"",
            14, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_SKIPSYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_SKIPSYN, self).__init__(register,
            'SKIPSYN', 'MODEM_NS.BCRDEMODCTRL.SKIPSYN', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_PMPATTERN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_PMPATTERN, self).__init__(register,
            'PMPATTERN', 'MODEM_NS.BCRDEMODCTRL.PMPATTERN', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_NONSTDPK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_NONSTDPK, self).__init__(register,
            'NONSTDPK', 'MODEM_NS.BCRDEMODCTRL.NONSTDPK', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_SLICERFAST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_SLICERFAST, self).__init__(register,
            'SLICERFAST', 'MODEM_NS.BCRDEMODCTRL.SLICERFAST', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_DIRECTMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_DIRECTMODE, self).__init__(register,
            'DIRECTMODE', 'MODEM_NS.BCRDEMODCTRL.DIRECTMODE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_DETECTORSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_DETECTORSEL, self).__init__(register,
            'DETECTORSEL', 'MODEM_NS.BCRDEMODCTRL.DETECTORSEL', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_BBPMDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_BBPMDETEN, self).__init__(register,
            'BBPMDETEN', 'MODEM_NS.BCRDEMODCTRL.BBPMDETEN', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_MANCHPH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_MANCHPH, self).__init__(register,
            'MANCHPH', 'MODEM_NS.BCRDEMODCTRL.MANCHPH', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_INVRXBIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_INVRXBIT, self).__init__(register,
            'INVRXBIT', 'MODEM_NS.BCRDEMODCTRL.INVRXBIT', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODCTRL_PHSRCSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODCTRL_PHSRCSEL, self).__init__(register,
            'PHSRCSEL', 'MODEM_NS.BCRDEMODCTRL.PHSRCSEL', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_OOKFRZEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_OOKFRZEN, self).__init__(register,
            'OOKFRZEN', 'MODEM_NS.BCRDEMODOOK.OOKFRZEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_RAWGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_RAWGAIN, self).__init__(register,
            'RAWGAIN', 'MODEM_NS.BCRDEMODOOK.RAWGAIN', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_NOISEFLEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_NOISEFLEST, self).__init__(register,
            'NOISEFLEST', 'MODEM_NS.BCRDEMODOOK.NOISEFLEST', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_PKTRUNK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_PKTRUNK, self).__init__(register,
            'PKTRUNK', 'MODEM_NS.BCRDEMODOOK.PKTRUNK', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_MAFREQDWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_MAFREQDWN, self).__init__(register,
            'MAFREQDWN', 'MODEM_NS.BCRDEMODOOK.MAFREQDWN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_SQUELCLKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_SQUELCLKEN, self).__init__(register,
            'SQUELCLKEN', 'MODEM_NS.BCRDEMODOOK.SQUELCLKEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_BWPK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_BWPK, self).__init__(register,
            'BWPK', 'MODEM_NS.BCRDEMODOOK.BWPK', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_ABPK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_ABPK, self).__init__(register,
            'ABPK', 'MODEM_NS.BCRDEMODOOK.ABPK', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_DECAYSWAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_DECAYSWAL, self).__init__(register,
            'DECAYSWAL', 'MODEM_NS.BCRDEMODOOK.DECAYSWAL', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_DECAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_DECAY, self).__init__(register,
            'DECAY', 'MODEM_NS.BCRDEMODOOK.DECAY', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_ATTACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_ATTACK, self).__init__(register,
            'ATTACK', 'MODEM_NS.BCRDEMODOOK.ATTACK', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_SQUELCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_SQUELCH, self).__init__(register,
            'SQUELCH', 'MODEM_NS.BCRDEMODOOK.SQUELCH', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_RAWNDEC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_RAWNDEC, self).__init__(register,
            'RAWNDEC', 'MODEM_NS.BCRDEMODOOK.RAWNDEC', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODOOK_BCRDEMODOOK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODOOK_BCRDEMODOOK, self).__init__(register,
            'BCRDEMODOOK', 'MODEM_NS.BCRDEMODOOK.BCRDEMODOOK', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC0_ZEROOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC0_ZEROOFF, self).__init__(register,
            'ZEROOFF', 'MODEM_NS.BCRDEMODAFC0.ZEROOFF', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC0_LARGEFREQERR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC0_LARGEFREQERR, self).__init__(register,
            'LARGEFREQERR', 'MODEM_NS.BCRDEMODAFC0.LARGEFREQERR', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC0_AFCGAINOVRFLW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC0_AFCGAINOVRFLW, self).__init__(register,
            'AFCGAINOVRFLW', 'MODEM_NS.BCRDEMODAFC0.AFCGAINOVRFLW', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC0_EN2TBEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC0_EN2TBEST, self).__init__(register,
            'EN2TBEST', 'MODEM_NS.BCRDEMODAFC0.EN2TBEST', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC0_ENAFCCLKSW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC0_ENAFCCLKSW, self).__init__(register,
            'ENAFCCLKSW', 'MODEM_NS.BCRDEMODAFC0.ENAFCCLKSW', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_LGWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_LGWAIT, self).__init__(register,
            'LGWAIT', 'MODEM_NS.BCRDEMODAFC1.LGWAIT', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_SHWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_SHWAIT, self).__init__(register,
            'SHWAIT', 'MODEM_NS.BCRDEMODAFC1.SHWAIT', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_GEARSW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_GEARSW, self).__init__(register,
            'GEARSW', 'MODEM_NS.BCRDEMODAFC1.GEARSW', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_AFCMAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_AFCMAEN, self).__init__(register,
            'AFCMAEN', 'MODEM_NS.BCRDEMODAFC1.AFCMAEN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_ENFZPMEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_ENFZPMEND, self).__init__(register,
            'ENFZPMEND', 'MODEM_NS.BCRDEMODAFC1.ENFZPMEND', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_NONFRZEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_NONFRZEN, self).__init__(register,
            'NONFRZEN', 'MODEM_NS.BCRDEMODAFC1.NONFRZEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_ONESHOTWAITCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_ONESHOTWAITCNT, self).__init__(register,
            'ONESHOTWAITCNT', 'MODEM_NS.BCRDEMODAFC1.ONESHOTWAITCNT', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_ONESHOTAFCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_ONESHOTAFCEN, self).__init__(register,
            'ONESHOTAFCEN', 'MODEM_NS.BCRDEMODAFC1.ONESHOTAFCEN', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_SKIPPMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_SKIPPMDET, self).__init__(register,
            'SKIPPMDET', 'MODEM_NS.BCRDEMODAFC1.SKIPPMDET', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_PMRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_PMRSTEN, self).__init__(register,
            'PMRSTEN', 'MODEM_NS.BCRDEMODAFC1.PMRSTEN', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_ENAFCFRZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_ENAFCFRZ, self).__init__(register,
            'ENAFCFRZ', 'MODEM_NS.BCRDEMODAFC1.ENAFCFRZ', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_HALFPHCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_HALFPHCOMP, self).__init__(register,
            'HALFPHCOMP', 'MODEM_NS.BCRDEMODAFC1.HALFPHCOMP', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_ENAFC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_ENAFC, self).__init__(register,
            'ENAFC', 'MODEM_NS.BCRDEMODAFC1.ENAFC', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODAFC1_ENFBPLL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODAFC1_ENFBPLL, self).__init__(register,
            'ENFBPLL', 'MODEM_NS.BCRDEMODAFC1.ENFBPLL', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK0_THD4GFSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK0_THD4GFSK, self).__init__(register,
            'THD4GFSK', 'MODEM_NS.BCRDEMOD4FSK0.THD4GFSK', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK0_CODE4GFSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK0_CODE4GFSK, self).__init__(register,
            'CODE4GFSK', 'MODEM_NS.BCRDEMOD4FSK0.CODE4GFSK', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK0_PHCOMPBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK0_PHCOMPBYP, self).__init__(register,
            'PHCOMPBYP', 'MODEM_NS.BCRDEMOD4FSK0.PHCOMPBYP', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK0_EN4GFSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK0_EN4GFSK, self).__init__(register,
            'EN4GFSK', 'MODEM_NS.BCRDEMOD4FSK0.EN4GFSK', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK1_PHCOMP4FSK0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK1_PHCOMP4FSK0, self).__init__(register,
            'PHCOMP4FSK0', 'MODEM_NS.BCRDEMOD4FSK1.PHCOMP4FSK0', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK1_PHCOMP4FSK1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK1_PHCOMP4FSK1, self).__init__(register,
            'PHCOMP4FSK1', 'MODEM_NS.BCRDEMOD4FSK1.PHCOMP4FSK1', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK1_FDEVCOMPRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK1_FDEVCOMPRATIO, self).__init__(register,
            'FDEVCOMPRATIO', 'MODEM_NS.BCRDEMOD4FSK1.FDEVCOMPRATIO', 'read-write',
            u"",
            16, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK1_FDEVCOMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK1_FDEVCOMPEN, self).__init__(register,
            'FDEVCOMPEN', 'MODEM_NS.BCRDEMOD4FSK1.FDEVCOMPEN', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMOD4FSK1_S2PMAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMOD4FSK1_S2PMAP, self).__init__(register,
            'S2PMAP', 'MODEM_NS.BCRDEMOD4FSK1.S2PMAP', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_SWANTTIMER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_SWANTTIMER, self).__init__(register,
            'SWANTTIMER', 'MODEM_NS.BCRDEMODANT.SWANTTIMER', 'read-write',
            u"",
            5, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_BECOEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_BECOEN, self).__init__(register,
            'BECOEN', 'MODEM_NS.BCRDEMODANT.BECOEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_SKIP2PHTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_SKIP2PHTHD, self).__init__(register,
            'SKIP2PHTHD', 'MODEM_NS.BCRDEMODANT.SKIP2PHTHD', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_ANWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_ANWAIT, self).__init__(register,
            'ANWAIT', 'MODEM_NS.BCRDEMODANT.ANWAIT', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_AGCGAINUPB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_AGCGAINUPB, self).__init__(register,
            'AGCGAINUPB', 'MODEM_NS.BCRDEMODANT.AGCGAINUPB', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_SKIP2PH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_SKIP2PH, self).__init__(register,
            'SKIP2PH', 'MODEM_NS.BCRDEMODANT.SKIP2PH', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_BYP1P5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_BYP1P5, self).__init__(register,
            'BYP1P5', 'MODEM_NS.BCRDEMODANT.BYP1P5', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_ANT2PMTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_ANT2PMTHD, self).__init__(register,
            'ANT2PMTHD', 'MODEM_NS.BCRDEMODANT.ANT2PMTHD', 'read-write',
            u"",
            25, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODANT_BCRDEMODANTDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODANT_BCRDEMODANTDIV, self).__init__(register,
            'BCRDEMODANTDIV', 'MODEM_NS.BCRDEMODANT.BCRDEMODANTDIV', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODRSSI_RSSIARRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODRSSI_RSSIARRTHD, self).__init__(register,
            'RSSIARRTHD', 'MODEM_NS.BCRDEMODRSSI.RSSIARRTHD', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODRSSI_RSSIMATAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODRSSI_RSSIMATAP, self).__init__(register,
            'RSSIMATAP', 'MODEM_NS.BCRDEMODRSSI.RSSIMATAP', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODRSSI_MUTERSSICNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODRSSI_MUTERSSICNT, self).__init__(register,
            'MUTERSSICNT', 'MODEM_NS.BCRDEMODRSSI.MUTERSSICNT', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODRSSI_PRWOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODRSSI_PRWOFFSET, self).__init__(register,
            'PRWOFFSET', 'MODEM_NS.BCRDEMODRSSI.PRWOFFSET', 'read-write',
            u"",
            25, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_SCHPRDLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_SCHPRDLO, self).__init__(register,
            'SCHPRDLO', 'MODEM_NS.BCRDEMODARR0.SCHPRDLO', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_EYEQUALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_EYEQUALEN, self).__init__(register,
            'EYEQUALEN', 'MODEM_NS.BCRDEMODARR0.EYEQUALEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_SCHPRDHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_SCHPRDHI, self).__init__(register,
            'SCHPRDHI', 'MODEM_NS.BCRDEMODARR0.SCHPRDHI', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_ARRRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_ARRRSTEN, self).__init__(register,
            'ARRRSTEN', 'MODEM_NS.BCRDEMODARR0.ARRRSTEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_ARRTOLER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_ARRTOLER, self).__init__(register,
            'ARRTOLER', 'MODEM_NS.BCRDEMODARR0.ARRTOLER', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_DIFF0RSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_DIFF0RSTEN, self).__init__(register,
            'DIFF0RSTEN', 'MODEM_NS.BCRDEMODARR0.DIFF0RSTEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_PHSPIKETHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_PHSPIKETHD, self).__init__(register,
            'PHSPIKETHD', 'MODEM_NS.BCRDEMODARR0.PHSPIKETHD', 'read-write',
            u"",
            14, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETTHD, self).__init__(register,
            'ARRDETTHD', 'MODEM_NS.BCRDEMODARR0.ARRDETTHD', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_SCHFRZEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_SCHFRZEN, self).__init__(register,
            'SCHFRZEN', 'MODEM_NS.BCRDEMODARR0.SCHFRZEN', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_EYEXESTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_EYEXESTEN, self).__init__(register,
            'EYEXESTEN', 'MODEM_NS.BCRDEMODARR0.EYEXESTEN', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_EYEXESTFAST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_EYEXESTFAST, self).__init__(register,
            'EYEXESTFAST', 'MODEM_NS.BCRDEMODARR0.EYEXESTFAST', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETSRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETSRC, self).__init__(register,
            'ARRDETSRC', 'MODEM_NS.BCRDEMODARR0.ARRDETSRC', 'read-write',
            u"",
            28, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_ARRQPM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_ARRQPM, self).__init__(register,
            'ARRQPM', 'MODEM_NS.BCRDEMODARR0.ARRQPM', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETEN, self).__init__(register,
            'ARRDETEN', 'MODEM_NS.BCRDEMODARR0.ARRDETEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR1_ARREYEQUAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR1_ARREYEQUAL, self).__init__(register,
            'ARREYEQUAL', 'MODEM_NS.BCRDEMODARR1.ARREYEQUAL', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR1_EYEOPENTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR1_EYEOPENTHD, self).__init__(register,
            'EYEOPENTHD', 'MODEM_NS.BCRDEMODARR1.EYEOPENTHD', 'read-write',
            u"",
            7, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR1_SYMBWMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR1_SYMBWMAX, self).__init__(register,
            'SYMBWMAX', 'MODEM_NS.BCRDEMODARR1.SYMBWMAX', 'read-write',
            u"",
            18, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR1_SYMBWMIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR1_SYMBWMIN, self).__init__(register,
            'SYMBWMIN', 'MODEM_NS.BCRDEMODARR1.SYMBWMIN', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR1_BCRCFESRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR1_BCRCFESRC, self).__init__(register,
            'BCRCFESRC', 'MODEM_NS.BCRDEMODARR1.BCRCFESRC', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR1_CFEQUALTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR1_CFEQUALTHD, self).__init__(register,
            'CFEQUALTHD', 'MODEM_NS.BCRDEMODARR1.CFEQUALTHD', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR1_KSICOMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR1_KSICOMPEN, self).__init__(register,
            'KSICOMPEN', 'MODEM_NS.BCRDEMODARR1.KSICOMPEN', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR1_ENCFEQUAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR1_ENCFEQUAL, self).__init__(register,
            'ENCFEQUAL', 'MODEM_NS.BCRDEMODARR1.ENCFEQUAL', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR2_CONSYMOL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR2_CONSYMOL, self).__init__(register,
            'CONSYMOL', 'MODEM_NS.BCRDEMODARR2.CONSYMOL', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR2_RAWDCHKALWAYON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR2_RAWDCHKALWAYON, self).__init__(register,
            'RAWDCHKALWAYON', 'MODEM_NS.BCRDEMODARR2.RAWDCHKALWAYON', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODARR2_OUTRNGCHK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODARR2_OUTRNGCHK, self).__init__(register,
            'OUTRNGCHK', 'MODEM_NS.BCRDEMODARR2.OUTRNGCHK', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI1, self).__init__(register,
            'BCRKSI1', 'MODEM_NS.BCRDEMODKSI.BCRKSI1', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI2, self).__init__(register,
            'BCRKSI2', 'MODEM_NS.BCRDEMODKSI.BCRKSI2', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI3, self).__init__(register,
            'BCRKSI3', 'MODEM_NS.BCRDEMODKSI.BCRKSI3', 'read-write',
            u"",
            16, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPMEXP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPMEXP, self).__init__(register,
            'BCRPMEXP', 'MODEM_NS.BCRDEMODPMEXP.BCRPMEXP', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRCFECOSTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRCFECOSTTHD, self).__init__(register,
            'BCRCFECOSTTHD', 'MODEM_NS.BCRDEMODPMEXP.BCRCFECOSTTHD', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPHSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPHSCALE, self).__init__(register,
            'BCRPHSCALE', 'MODEM_NS.BCRDEMODPMEXP.BCRPHSCALE', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRCFESCHWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRCFESCHWIN, self).__init__(register,
            'BCRCFESCHWIN', 'MODEM_NS.BCRDEMODPMEXP.BCRCFESCHWIN', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPMACQWIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPMACQWIN, self).__init__(register,
            'BCRPMACQWIN', 'MODEM_NS.BCRDEMODPMEXP.BCRPMACQWIN', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_MODEM_NS_SPARE_SPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_MODEM_NS_SPARE_SPARE, self).__init__(register,
            'SPARE', 'MODEM_NS.SPARE.SPARE', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True



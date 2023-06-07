
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . MODEM_NS_field import *


class RM_Register_MODEM_NS_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IPVERSION, self).__init__(rmio, label,
            0xb8014000, 0x000,
            'IPVERSION', 'MODEM_NS.IPVERSION', 'read-only',
            u"",
            0x00000004, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_MODEM_NS_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_EN, self).__init__(rmio, label,
            0xb8014000, 0x004,
            'EN', 'MODEM_NS.EN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_MODEM_NS_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_IF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IF, self).__init__(rmio, label,
            0xb8014000, 0x008,
            'IF', 'MODEM_NS.IF', 'read-write',
            u"",
            0x00000000, 0x3FE7FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXFRAMESENT = RM_Field_MODEM_NS_IF_TXFRAMESENT(self)
        self.zz_fdict['TXFRAMESENT'] = self.TXFRAMESENT
        self.TXSYNCSENT = RM_Field_MODEM_NS_IF_TXSYNCSENT(self)
        self.zz_fdict['TXSYNCSENT'] = self.TXSYNCSENT
        self.TXPRESENT = RM_Field_MODEM_NS_IF_TXPRESENT(self)
        self.zz_fdict['TXPRESENT'] = self.TXPRESENT
        self.TXRAMPDONE = RM_Field_MODEM_NS_IF_TXRAMPDONE(self)
        self.zz_fdict['TXRAMPDONE'] = self.TXRAMPDONE
        self.LDTNOARR = RM_Field_MODEM_NS_IF_LDTNOARR(self)
        self.zz_fdict['LDTNOARR'] = self.LDTNOARR
        self.PHDSADET = RM_Field_MODEM_NS_IF_PHDSADET(self)
        self.zz_fdict['PHDSADET'] = self.PHDSADET
        self.PHYUNCODEDET = RM_Field_MODEM_NS_IF_PHYUNCODEDET(self)
        self.zz_fdict['PHYUNCODEDET'] = self.PHYUNCODEDET
        self.PHYCODEDET = RM_Field_MODEM_NS_IF_PHYCODEDET(self)
        self.zz_fdict['PHYCODEDET'] = self.PHYCODEDET
        self.RXTIMDET = RM_Field_MODEM_NS_IF_RXTIMDET(self)
        self.zz_fdict['RXTIMDET'] = self.RXTIMDET
        self.RXPREDET = RM_Field_MODEM_NS_IF_RXPREDET(self)
        self.zz_fdict['RXPREDET'] = self.RXPREDET
        self.RXFRAMEDET0 = RM_Field_MODEM_NS_IF_RXFRAMEDET0(self)
        self.zz_fdict['RXFRAMEDET0'] = self.RXFRAMEDET0
        self.RXFRAMEDET1 = RM_Field_MODEM_NS_IF_RXFRAMEDET1(self)
        self.zz_fdict['RXFRAMEDET1'] = self.RXFRAMEDET1
        self.RXTIMLOST = RM_Field_MODEM_NS_IF_RXTIMLOST(self)
        self.zz_fdict['RXTIMLOST'] = self.RXTIMLOST
        self.RXPRELOST = RM_Field_MODEM_NS_IF_RXPRELOST(self)
        self.zz_fdict['RXPRELOST'] = self.RXPRELOST
        self.RXFRAMEDETOF = RM_Field_MODEM_NS_IF_RXFRAMEDETOF(self)
        self.zz_fdict['RXFRAMEDETOF'] = self.RXFRAMEDETOF
        self.RXTIMNF = RM_Field_MODEM_NS_IF_RXTIMNF(self)
        self.zz_fdict['RXTIMNF'] = self.RXTIMNF
        self.FRCTIMOUT = RM_Field_MODEM_NS_IF_FRCTIMOUT(self)
        self.zz_fdict['FRCTIMOUT'] = self.FRCTIMOUT
        self.ETS = RM_Field_MODEM_NS_IF_ETS(self)
        self.zz_fdict['ETS'] = self.ETS
        self.CFGANTPATTRD = RM_Field_MODEM_NS_IF_CFGANTPATTRD(self)
        self.zz_fdict['CFGANTPATTRD'] = self.CFGANTPATTRD
        self.SQDET = RM_Field_MODEM_NS_IF_SQDET(self)
        self.zz_fdict['SQDET'] = self.SQDET
        self.SQNOTDET = RM_Field_MODEM_NS_IF_SQNOTDET(self)
        self.zz_fdict['SQNOTDET'] = self.SQNOTDET
        self.ANTDIVRDY = RM_Field_MODEM_NS_IF_ANTDIVRDY(self)
        self.zz_fdict['ANTDIVRDY'] = self.ANTDIVRDY
        self.SOFTRESETDONE = RM_Field_MODEM_NS_IF_SOFTRESETDONE(self)
        self.zz_fdict['SOFTRESETDONE'] = self.SOFTRESETDONE
        self.SQPRENOTDET = RM_Field_MODEM_NS_IF_SQPRENOTDET(self)
        self.zz_fdict['SQPRENOTDET'] = self.SQPRENOTDET
        self.SQFRAMENOTDET = RM_Field_MODEM_NS_IF_SQFRAMENOTDET(self)
        self.zz_fdict['SQFRAMENOTDET'] = self.SQFRAMENOTDET
        self.SQAFCOUTOFBAND = RM_Field_MODEM_NS_IF_SQAFCOUTOFBAND(self)
        self.zz_fdict['SQAFCOUTOFBAND'] = self.SQAFCOUTOFBAND
        self.SIDET = RM_Field_MODEM_NS_IF_SIDET(self)
        self.zz_fdict['SIDET'] = self.SIDET
        self.SIRESET = RM_Field_MODEM_NS_IF_SIRESET(self)
        self.zz_fdict['SIRESET'] = self.SIRESET
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_IEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IEN, self).__init__(rmio, label,
            0xb8014000, 0x00C,
            'IEN', 'MODEM_NS.IEN', 'read-write',
            u"",
            0x00000000, 0x3FE7FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXFRAMESENT = RM_Field_MODEM_NS_IEN_TXFRAMESENT(self)
        self.zz_fdict['TXFRAMESENT'] = self.TXFRAMESENT
        self.TXSYNCSENT = RM_Field_MODEM_NS_IEN_TXSYNCSENT(self)
        self.zz_fdict['TXSYNCSENT'] = self.TXSYNCSENT
        self.TXPRESENT = RM_Field_MODEM_NS_IEN_TXPRESENT(self)
        self.zz_fdict['TXPRESENT'] = self.TXPRESENT
        self.TXRAMPDONE = RM_Field_MODEM_NS_IEN_TXRAMPDONE(self)
        self.zz_fdict['TXRAMPDONE'] = self.TXRAMPDONE
        self.LDTNOARR = RM_Field_MODEM_NS_IEN_LDTNOARR(self)
        self.zz_fdict['LDTNOARR'] = self.LDTNOARR
        self.PHDSADET = RM_Field_MODEM_NS_IEN_PHDSADET(self)
        self.zz_fdict['PHDSADET'] = self.PHDSADET
        self.PHYUNCODEDET = RM_Field_MODEM_NS_IEN_PHYUNCODEDET(self)
        self.zz_fdict['PHYUNCODEDET'] = self.PHYUNCODEDET
        self.PHYCODEDET = RM_Field_MODEM_NS_IEN_PHYCODEDET(self)
        self.zz_fdict['PHYCODEDET'] = self.PHYCODEDET
        self.RXTIMDET = RM_Field_MODEM_NS_IEN_RXTIMDET(self)
        self.zz_fdict['RXTIMDET'] = self.RXTIMDET
        self.RXPREDET = RM_Field_MODEM_NS_IEN_RXPREDET(self)
        self.zz_fdict['RXPREDET'] = self.RXPREDET
        self.RXFRAMEDET0 = RM_Field_MODEM_NS_IEN_RXFRAMEDET0(self)
        self.zz_fdict['RXFRAMEDET0'] = self.RXFRAMEDET0
        self.RXFRAMEDET1 = RM_Field_MODEM_NS_IEN_RXFRAMEDET1(self)
        self.zz_fdict['RXFRAMEDET1'] = self.RXFRAMEDET1
        self.RXTIMLOST = RM_Field_MODEM_NS_IEN_RXTIMLOST(self)
        self.zz_fdict['RXTIMLOST'] = self.RXTIMLOST
        self.RXPRELOST = RM_Field_MODEM_NS_IEN_RXPRELOST(self)
        self.zz_fdict['RXPRELOST'] = self.RXPRELOST
        self.RXFRAMEDETOF = RM_Field_MODEM_NS_IEN_RXFRAMEDETOF(self)
        self.zz_fdict['RXFRAMEDETOF'] = self.RXFRAMEDETOF
        self.RXTIMNF = RM_Field_MODEM_NS_IEN_RXTIMNF(self)
        self.zz_fdict['RXTIMNF'] = self.RXTIMNF
        self.FRCTIMOUT = RM_Field_MODEM_NS_IEN_FRCTIMOUT(self)
        self.zz_fdict['FRCTIMOUT'] = self.FRCTIMOUT
        self.ETS = RM_Field_MODEM_NS_IEN_ETS(self)
        self.zz_fdict['ETS'] = self.ETS
        self.CFGANTPATTRD = RM_Field_MODEM_NS_IEN_CFGANTPATTRD(self)
        self.zz_fdict['CFGANTPATTRD'] = self.CFGANTPATTRD
        self.SQDET = RM_Field_MODEM_NS_IEN_SQDET(self)
        self.zz_fdict['SQDET'] = self.SQDET
        self.SQNOTDET = RM_Field_MODEM_NS_IEN_SQNOTDET(self)
        self.zz_fdict['SQNOTDET'] = self.SQNOTDET
        self.ANTDIVRDY = RM_Field_MODEM_NS_IEN_ANTDIVRDY(self)
        self.zz_fdict['ANTDIVRDY'] = self.ANTDIVRDY
        self.SOFTRESETDONE = RM_Field_MODEM_NS_IEN_SOFTRESETDONE(self)
        self.zz_fdict['SOFTRESETDONE'] = self.SOFTRESETDONE
        self.SQPRENOTDET = RM_Field_MODEM_NS_IEN_SQPRENOTDET(self)
        self.zz_fdict['SQPRENOTDET'] = self.SQPRENOTDET
        self.SQFRAMENOTDET = RM_Field_MODEM_NS_IEN_SQFRAMENOTDET(self)
        self.zz_fdict['SQFRAMENOTDET'] = self.SQFRAMENOTDET
        self.SQAFCOUTOFBAND = RM_Field_MODEM_NS_IEN_SQAFCOUTOFBAND(self)
        self.zz_fdict['SQAFCOUTOFBAND'] = self.SQAFCOUTOFBAND
        self.SIDET = RM_Field_MODEM_NS_IEN_SIDET(self)
        self.zz_fdict['SIDET'] = self.SIDET
        self.SIRESET = RM_Field_MODEM_NS_IEN_SIRESET(self)
        self.zz_fdict['SIRESET'] = self.SIRESET
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SEQIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SEQIF, self).__init__(rmio, label,
            0xb8014000, 0x010,
            'SEQIF', 'MODEM_NS.SEQIF', 'read-write',
            u"",
            0x00000000, 0x3FE7FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXFRAMESENT = RM_Field_MODEM_NS_SEQIF_TXFRAMESENT(self)
        self.zz_fdict['TXFRAMESENT'] = self.TXFRAMESENT
        self.TXSYNCSENT = RM_Field_MODEM_NS_SEQIF_TXSYNCSENT(self)
        self.zz_fdict['TXSYNCSENT'] = self.TXSYNCSENT
        self.TXPRESENT = RM_Field_MODEM_NS_SEQIF_TXPRESENT(self)
        self.zz_fdict['TXPRESENT'] = self.TXPRESENT
        self.TXRAMPDONE = RM_Field_MODEM_NS_SEQIF_TXRAMPDONE(self)
        self.zz_fdict['TXRAMPDONE'] = self.TXRAMPDONE
        self.LDTNOARR = RM_Field_MODEM_NS_SEQIF_LDTNOARR(self)
        self.zz_fdict['LDTNOARR'] = self.LDTNOARR
        self.PHDSADET = RM_Field_MODEM_NS_SEQIF_PHDSADET(self)
        self.zz_fdict['PHDSADET'] = self.PHDSADET
        self.PHYUNCODEDET = RM_Field_MODEM_NS_SEQIF_PHYUNCODEDET(self)
        self.zz_fdict['PHYUNCODEDET'] = self.PHYUNCODEDET
        self.PHYCODEDET = RM_Field_MODEM_NS_SEQIF_PHYCODEDET(self)
        self.zz_fdict['PHYCODEDET'] = self.PHYCODEDET
        self.RXTIMDET = RM_Field_MODEM_NS_SEQIF_RXTIMDET(self)
        self.zz_fdict['RXTIMDET'] = self.RXTIMDET
        self.RXPREDET = RM_Field_MODEM_NS_SEQIF_RXPREDET(self)
        self.zz_fdict['RXPREDET'] = self.RXPREDET
        self.RXFRAMEDET0 = RM_Field_MODEM_NS_SEQIF_RXFRAMEDET0(self)
        self.zz_fdict['RXFRAMEDET0'] = self.RXFRAMEDET0
        self.RXFRAMEDET1 = RM_Field_MODEM_NS_SEQIF_RXFRAMEDET1(self)
        self.zz_fdict['RXFRAMEDET1'] = self.RXFRAMEDET1
        self.RXTIMLOST = RM_Field_MODEM_NS_SEQIF_RXTIMLOST(self)
        self.zz_fdict['RXTIMLOST'] = self.RXTIMLOST
        self.RXPRELOST = RM_Field_MODEM_NS_SEQIF_RXPRELOST(self)
        self.zz_fdict['RXPRELOST'] = self.RXPRELOST
        self.RXFRAMEDETOF = RM_Field_MODEM_NS_SEQIF_RXFRAMEDETOF(self)
        self.zz_fdict['RXFRAMEDETOF'] = self.RXFRAMEDETOF
        self.RXTIMNF = RM_Field_MODEM_NS_SEQIF_RXTIMNF(self)
        self.zz_fdict['RXTIMNF'] = self.RXTIMNF
        self.FRCTIMOUT = RM_Field_MODEM_NS_SEQIF_FRCTIMOUT(self)
        self.zz_fdict['FRCTIMOUT'] = self.FRCTIMOUT
        self.ETS = RM_Field_MODEM_NS_SEQIF_ETS(self)
        self.zz_fdict['ETS'] = self.ETS
        self.CFGANTPATTRD = RM_Field_MODEM_NS_SEQIF_CFGANTPATTRD(self)
        self.zz_fdict['CFGANTPATTRD'] = self.CFGANTPATTRD
        self.SQDET = RM_Field_MODEM_NS_SEQIF_SQDET(self)
        self.zz_fdict['SQDET'] = self.SQDET
        self.SQNOTDET = RM_Field_MODEM_NS_SEQIF_SQNOTDET(self)
        self.zz_fdict['SQNOTDET'] = self.SQNOTDET
        self.ANTDIVRDY = RM_Field_MODEM_NS_SEQIF_ANTDIVRDY(self)
        self.zz_fdict['ANTDIVRDY'] = self.ANTDIVRDY
        self.SOFTRESETDONE = RM_Field_MODEM_NS_SEQIF_SOFTRESETDONE(self)
        self.zz_fdict['SOFTRESETDONE'] = self.SOFTRESETDONE
        self.SQPRENOTDET = RM_Field_MODEM_NS_SEQIF_SQPRENOTDET(self)
        self.zz_fdict['SQPRENOTDET'] = self.SQPRENOTDET
        self.SQFRAMENOTDET = RM_Field_MODEM_NS_SEQIF_SQFRAMENOTDET(self)
        self.zz_fdict['SQFRAMENOTDET'] = self.SQFRAMENOTDET
        self.SQAFCOUTOFBAND = RM_Field_MODEM_NS_SEQIF_SQAFCOUTOFBAND(self)
        self.zz_fdict['SQAFCOUTOFBAND'] = self.SQAFCOUTOFBAND
        self.SIDET = RM_Field_MODEM_NS_SEQIF_SIDET(self)
        self.zz_fdict['SIDET'] = self.SIDET
        self.SIRESET = RM_Field_MODEM_NS_SEQIF_SIRESET(self)
        self.zz_fdict['SIRESET'] = self.SIRESET
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SEQIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SEQIEN, self).__init__(rmio, label,
            0xb8014000, 0x014,
            'SEQIEN', 'MODEM_NS.SEQIEN', 'read-write',
            u"",
            0x00000000, 0x3FE7FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXFRAMESENT = RM_Field_MODEM_NS_SEQIEN_TXFRAMESENT(self)
        self.zz_fdict['TXFRAMESENT'] = self.TXFRAMESENT
        self.TXSYNCSENT = RM_Field_MODEM_NS_SEQIEN_TXSYNCSENT(self)
        self.zz_fdict['TXSYNCSENT'] = self.TXSYNCSENT
        self.TXPRESENT = RM_Field_MODEM_NS_SEQIEN_TXPRESENT(self)
        self.zz_fdict['TXPRESENT'] = self.TXPRESENT
        self.TXRAMPDONE = RM_Field_MODEM_NS_SEQIEN_TXRAMPDONE(self)
        self.zz_fdict['TXRAMPDONE'] = self.TXRAMPDONE
        self.LDTNOARR = RM_Field_MODEM_NS_SEQIEN_LDTNOARR(self)
        self.zz_fdict['LDTNOARR'] = self.LDTNOARR
        self.PHDSADET = RM_Field_MODEM_NS_SEQIEN_PHDSADET(self)
        self.zz_fdict['PHDSADET'] = self.PHDSADET
        self.PHYUNCODEDET = RM_Field_MODEM_NS_SEQIEN_PHYUNCODEDET(self)
        self.zz_fdict['PHYUNCODEDET'] = self.PHYUNCODEDET
        self.PHYCODEDET = RM_Field_MODEM_NS_SEQIEN_PHYCODEDET(self)
        self.zz_fdict['PHYCODEDET'] = self.PHYCODEDET
        self.RXTIMDET = RM_Field_MODEM_NS_SEQIEN_RXTIMDET(self)
        self.zz_fdict['RXTIMDET'] = self.RXTIMDET
        self.RXPREDET = RM_Field_MODEM_NS_SEQIEN_RXPREDET(self)
        self.zz_fdict['RXPREDET'] = self.RXPREDET
        self.RXFRAMEDET0 = RM_Field_MODEM_NS_SEQIEN_RXFRAMEDET0(self)
        self.zz_fdict['RXFRAMEDET0'] = self.RXFRAMEDET0
        self.RXFRAMEDET1 = RM_Field_MODEM_NS_SEQIEN_RXFRAMEDET1(self)
        self.zz_fdict['RXFRAMEDET1'] = self.RXFRAMEDET1
        self.RXTIMLOST = RM_Field_MODEM_NS_SEQIEN_RXTIMLOST(self)
        self.zz_fdict['RXTIMLOST'] = self.RXTIMLOST
        self.RXPRELOST = RM_Field_MODEM_NS_SEQIEN_RXPRELOST(self)
        self.zz_fdict['RXPRELOST'] = self.RXPRELOST
        self.RXFRAMEDETOF = RM_Field_MODEM_NS_SEQIEN_RXFRAMEDETOF(self)
        self.zz_fdict['RXFRAMEDETOF'] = self.RXFRAMEDETOF
        self.RXTIMNF = RM_Field_MODEM_NS_SEQIEN_RXTIMNF(self)
        self.zz_fdict['RXTIMNF'] = self.RXTIMNF
        self.FRCTIMOUT = RM_Field_MODEM_NS_SEQIEN_FRCTIMOUT(self)
        self.zz_fdict['FRCTIMOUT'] = self.FRCTIMOUT
        self.ETS = RM_Field_MODEM_NS_SEQIEN_ETS(self)
        self.zz_fdict['ETS'] = self.ETS
        self.CFGANTPATTRD = RM_Field_MODEM_NS_SEQIEN_CFGANTPATTRD(self)
        self.zz_fdict['CFGANTPATTRD'] = self.CFGANTPATTRD
        self.SQDET = RM_Field_MODEM_NS_SEQIEN_SQDET(self)
        self.zz_fdict['SQDET'] = self.SQDET
        self.SQNOTDET = RM_Field_MODEM_NS_SEQIEN_SQNOTDET(self)
        self.zz_fdict['SQNOTDET'] = self.SQNOTDET
        self.ANTDIVRDY = RM_Field_MODEM_NS_SEQIEN_ANTDIVRDY(self)
        self.zz_fdict['ANTDIVRDY'] = self.ANTDIVRDY
        self.SOFTRESETDONE = RM_Field_MODEM_NS_SEQIEN_SOFTRESETDONE(self)
        self.zz_fdict['SOFTRESETDONE'] = self.SOFTRESETDONE
        self.SQPRENOTDET = RM_Field_MODEM_NS_SEQIEN_SQPRENOTDET(self)
        self.zz_fdict['SQPRENOTDET'] = self.SQPRENOTDET
        self.SQFRAMENOTDET = RM_Field_MODEM_NS_SEQIEN_SQFRAMENOTDET(self)
        self.zz_fdict['SQFRAMENOTDET'] = self.SQFRAMENOTDET
        self.SQAFCOUTOFBAND = RM_Field_MODEM_NS_SEQIEN_SQAFCOUTOFBAND(self)
        self.zz_fdict['SQAFCOUTOFBAND'] = self.SQAFCOUTOFBAND
        self.SIDET = RM_Field_MODEM_NS_SEQIEN_SIDET(self)
        self.zz_fdict['SIDET'] = self.SIDET
        self.SIRESET = RM_Field_MODEM_NS_SEQIEN_SIRESET(self)
        self.zz_fdict['SIRESET'] = self.SIRESET
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS, self).__init__(rmio, label,
            0xb8014000, 0x018,
            'STATUS', 'MODEM_NS.STATUS', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DEMODSTATE = RM_Field_MODEM_NS_STATUS_DEMODSTATE(self)
        self.zz_fdict['DEMODSTATE'] = self.DEMODSTATE
        self.BCRCFEDSADET = RM_Field_MODEM_NS_STATUS_BCRCFEDSADET(self)
        self.zz_fdict['BCRCFEDSADET'] = self.BCRCFEDSADET
        self.FRAMEDETID = RM_Field_MODEM_NS_STATUS_FRAMEDETID(self)
        self.zz_fdict['FRAMEDETID'] = self.FRAMEDETID
        self.ANTSEL = RM_Field_MODEM_NS_STATUS_ANTSEL(self)
        self.zz_fdict['ANTSEL'] = self.ANTSEL
        self.TIMSEQINV = RM_Field_MODEM_NS_STATUS_TIMSEQINV(self)
        self.zz_fdict['TIMSEQINV'] = self.TIMSEQINV
        self.TIMLOSTCAUSE = RM_Field_MODEM_NS_STATUS_TIMLOSTCAUSE(self)
        self.zz_fdict['TIMLOSTCAUSE'] = self.TIMLOSTCAUSE
        self.DSADETECTED = RM_Field_MODEM_NS_STATUS_DSADETECTED(self)
        self.zz_fdict['DSADETECTED'] = self.DSADETECTED
        self.DSAFREQESTDONE = RM_Field_MODEM_NS_STATUS_DSAFREQESTDONE(self)
        self.zz_fdict['DSAFREQESTDONE'] = self.DSAFREQESTDONE
        self.VITERBIDEMODTIMDET = RM_Field_MODEM_NS_STATUS_VITERBIDEMODTIMDET(self)
        self.zz_fdict['VITERBIDEMODTIMDET'] = self.VITERBIDEMODTIMDET
        self.VITERBIDEMODFRAMEDET = RM_Field_MODEM_NS_STATUS_VITERBIDEMODFRAMEDET(self)
        self.zz_fdict['VITERBIDEMODFRAMEDET'] = self.VITERBIDEMODFRAMEDET
        self.STAMPSTATE = RM_Field_MODEM_NS_STATUS_STAMPSTATE(self)
        self.zz_fdict['STAMPSTATE'] = self.STAMPSTATE
        self.TRECSDSAADET = RM_Field_MODEM_NS_STATUS_TRECSDSAADET(self)
        self.zz_fdict['TRECSDSAADET'] = self.TRECSDSAADET
        self.CORR = RM_Field_MODEM_NS_STATUS_CORR(self)
        self.zz_fdict['CORR'] = self.CORR
        self.WEAKSYMBOLS = RM_Field_MODEM_NS_STATUS_WEAKSYMBOLS(self)
        self.zz_fdict['WEAKSYMBOLS'] = self.WEAKSYMBOLS
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS2, self).__init__(rmio, label,
            0xb8014000, 0x01C,
            'STATUS2', 'MODEM_NS.STATUS2', 'read-only',
            u"",
            0x00000000, 0xFFFCF0FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CHPWRACCUMUX = RM_Field_MODEM_NS_STATUS2_CHPWRACCUMUX(self)
        self.zz_fdict['CHPWRACCUMUX'] = self.CHPWRACCUMUX
        self.LRBLECI = RM_Field_MODEM_NS_STATUS2_LRBLECI(self)
        self.zz_fdict['LRBLECI'] = self.LRBLECI
        self.UNCODEDPHY = RM_Field_MODEM_NS_STATUS2_UNCODEDPHY(self)
        self.zz_fdict['UNCODEDPHY'] = self.UNCODEDPHY
        self.CODEDPHY = RM_Field_MODEM_NS_STATUS2_CODEDPHY(self)
        self.zz_fdict['CODEDPHY'] = self.CODEDPHY
        self.RTCOST = RM_Field_MODEM_NS_STATUS2_RTCOST(self)
        self.zz_fdict['RTCOST'] = self.RTCOST
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS3, self).__init__(rmio, label,
            0xb8014000, 0x020,
            'STATUS3', 'MODEM_NS.STATUS3', 'read-only',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BBPFOUTABS1 = RM_Field_MODEM_NS_STATUS3_BBPFOUTABS1(self)
        self.zz_fdict['BBPFOUTABS1'] = self.BBPFOUTABS1
        self.BBPFOUTABS = RM_Field_MODEM_NS_STATUS3_BBPFOUTABS(self)
        self.zz_fdict['BBPFOUTABS'] = self.BBPFOUTABS
        self.LRDSALIVE = RM_Field_MODEM_NS_STATUS3_LRDSALIVE(self)
        self.zz_fdict['LRDSALIVE'] = self.LRDSALIVE
        self.COHDSALIVE = RM_Field_MODEM_NS_STATUS3_COHDSALIVE(self)
        self.zz_fdict['COHDSALIVE'] = self.COHDSALIVE
        self.LRDSADET = RM_Field_MODEM_NS_STATUS3_LRDSADET(self)
        self.zz_fdict['LRDSADET'] = self.LRDSADET
        self.COHDSADET = RM_Field_MODEM_NS_STATUS3_COHDSADET(self)
        self.zz_fdict['COHDSADET'] = self.COHDSADET
        self.SYNCSECPEAKABTH = RM_Field_MODEM_NS_STATUS3_SYNCSECPEAKABTH(self)
        self.zz_fdict['SYNCSECPEAKABTH'] = self.SYNCSECPEAKABTH
        self.SOFTRSTDONE = RM_Field_MODEM_NS_STATUS3_SOFTRSTDONE(self)
        self.zz_fdict['SOFTRSTDONE'] = self.SOFTRSTDONE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS4, self).__init__(rmio, label,
            0xb8014000, 0x024,
            'STATUS4', 'MODEM_NS.STATUS4', 'read-only',
            u"",
            0x00000000, 0x01FF01FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANT0RSSI = RM_Field_MODEM_NS_STATUS4_ANT0RSSI(self)
        self.zz_fdict['ANT0RSSI'] = self.ANT0RSSI
        self.ANT1RSSI = RM_Field_MODEM_NS_STATUS4_ANT1RSSI(self)
        self.zz_fdict['ANT1RSSI'] = self.ANT1RSSI
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS6, self).__init__(rmio, label,
            0xb8014000, 0x02C,
            'STATUS6', 'MODEM_NS.STATUS6', 'read-only',
            u"",
            0x00000000, 0xC00FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANT0CORR = RM_Field_MODEM_NS_STATUS6_ANT0CORR(self)
        self.zz_fdict['ANT0CORR'] = self.ANT0CORR
        self.ANT1CORR = RM_Field_MODEM_NS_STATUS6_ANT1CORR(self)
        self.zz_fdict['ANT1CORR'] = self.ANT1CORR
        self.ANT0OUT = RM_Field_MODEM_NS_STATUS6_ANT0OUT(self)
        self.zz_fdict['ANT0OUT'] = self.ANT0OUT
        self.ANT1OUT = RM_Field_MODEM_NS_STATUS6_ANT1OUT(self)
        self.zz_fdict['ANT1OUT'] = self.ANT1OUT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS7, self).__init__(rmio, label,
            0xb8014000, 0x030,
            'STATUS7', 'MODEM_NS.STATUS7', 'read-only',
            u"",
            0x00000000, 0xBFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FDEVEST = RM_Field_MODEM_NS_STATUS7_FDEVEST(self)
        self.zz_fdict['FDEVEST'] = self.FDEVEST
        self.DEMODSOFT = RM_Field_MODEM_NS_STATUS7_DEMODSOFT(self)
        self.zz_fdict['DEMODSOFT'] = self.DEMODSOFT
        self.CFEPHDIFF = RM_Field_MODEM_NS_STATUS7_CFEPHDIFF(self)
        self.zz_fdict['CFEPHDIFF'] = self.CFEPHDIFF
        self.MINCOSTPASS = RM_Field_MODEM_NS_STATUS7_MINCOSTPASS(self)
        self.zz_fdict['MINCOSTPASS'] = self.MINCOSTPASS
        self.CFEDSADET = RM_Field_MODEM_NS_STATUS7_CFEDSADET(self)
        self.zz_fdict['CFEDSADET'] = self.CFEDSADET
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TIMDETSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TIMDETSTATUS, self).__init__(rmio, label,
            0xb8014000, 0x034,
            'TIMDETSTATUS', 'MODEM_NS.TIMDETSTATUS', 'read-only',
            u"",
            0x00000000, 0x1F0FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMDETCORR = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETCORR(self)
        self.zz_fdict['TIMDETCORR'] = self.TIMDETCORR
        self.TIMDETFREQOFFEST = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETFREQOFFEST(self)
        self.zz_fdict['TIMDETFREQOFFEST'] = self.TIMDETFREQOFFEST
        self.TIMDETPREERRORS = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETPREERRORS(self)
        self.zz_fdict['TIMDETPREERRORS'] = self.TIMDETPREERRORS
        self.TIMDETPASS = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETPASS(self)
        self.zz_fdict['TIMDETPASS'] = self.TIMDETPASS
        self.TIMDETINDEX = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETINDEX(self)
        self.zz_fdict['TIMDETINDEX'] = self.TIMDETINDEX
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_FSMSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_FSMSTATUS, self).__init__(rmio, label,
            0xb8014000, 0x038,
            'FSMSTATUS', 'MODEM_NS.FSMSTATUS', 'read-only',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DETSTATE = RM_Field_MODEM_NS_FSMSTATUS_DETSTATE(self)
        self.zz_fdict['DETSTATE'] = self.DETSTATE
        self.DSASTATE = RM_Field_MODEM_NS_FSMSTATUS_DSASTATE(self)
        self.zz_fdict['DSASTATE'] = self.DSASTATE
        self.LRBLESTATE = RM_Field_MODEM_NS_FSMSTATUS_LRBLESTATE(self)
        self.zz_fdict['LRBLESTATE'] = self.LRBLESTATE
        self.NBBLESTATE = RM_Field_MODEM_NS_FSMSTATUS_NBBLESTATE(self)
        self.zz_fdict['NBBLESTATE'] = self.NBBLESTATE
        self.ANTDIVSTATE = RM_Field_MODEM_NS_FSMSTATUS_ANTDIVSTATE(self)
        self.zz_fdict['ANTDIVSTATE'] = self.ANTDIVSTATE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_FREQOFFEST(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_FREQOFFEST, self).__init__(rmio, label,
            0xb8014000, 0x03C,
            'FREQOFFEST', 'MODEM_NS.FREQOFFEST', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FREQOFFEST = RM_Field_MODEM_NS_FREQOFFEST_FREQOFFEST(self)
        self.zz_fdict['FREQOFFEST'] = self.FREQOFFEST
        self.CORRVAL = RM_Field_MODEM_NS_FREQOFFEST_CORRVAL(self)
        self.zz_fdict['CORRVAL'] = self.CORRVAL
        self.SOFTVAL = RM_Field_MODEM_NS_FREQOFFEST_SOFTVAL(self)
        self.zz_fdict['SOFTVAL'] = self.SOFTVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AFCADJRX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AFCADJRX, self).__init__(rmio, label,
            0xb8014000, 0x040,
            'AFCADJRX', 'MODEM_NS.AFCADJRX', 'read-write',
            u"",
            0x00000000, 0xF1F7FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCADJRX = RM_Field_MODEM_NS_AFCADJRX_AFCADJRX(self)
        self.zz_fdict['AFCADJRX'] = self.AFCADJRX
        self.AFCSCALEM = RM_Field_MODEM_NS_AFCADJRX_AFCSCALEM(self)
        self.zz_fdict['AFCSCALEM'] = self.AFCSCALEM
        self.AFCSCALEE = RM_Field_MODEM_NS_AFCADJRX_AFCSCALEE(self)
        self.zz_fdict['AFCSCALEE'] = self.AFCSCALEE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AFCADJTX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AFCADJTX, self).__init__(rmio, label,
            0xb8014000, 0x044,
            'AFCADJTX', 'MODEM_NS.AFCADJTX', 'read-write',
            u"",
            0x00000000, 0xF1F7FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCADJTX = RM_Field_MODEM_NS_AFCADJTX_AFCADJTX(self)
        self.zz_fdict['AFCADJTX'] = self.AFCADJTX
        self.AFCSCALEM = RM_Field_MODEM_NS_AFCADJTX_AFCSCALEM(self)
        self.zz_fdict['AFCSCALEM'] = self.AFCSCALEM
        self.AFCSCALEE = RM_Field_MODEM_NS_AFCADJTX_AFCSCALEE(self)
        self.zz_fdict['AFCSCALEE'] = self.AFCSCALEE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL0, self).__init__(rmio, label,
            0xb8014000, 0x04C,
            'CTRL0', 'MODEM_NS.CTRL0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FDM0DIFFDIS = RM_Field_MODEM_NS_CTRL0_FDM0DIFFDIS(self)
        self.zz_fdict['FDM0DIFFDIS'] = self.FDM0DIFFDIS
        self.MAPFSK = RM_Field_MODEM_NS_CTRL0_MAPFSK(self)
        self.zz_fdict['MAPFSK'] = self.MAPFSK
        self.CODING = RM_Field_MODEM_NS_CTRL0_CODING(self)
        self.zz_fdict['CODING'] = self.CODING
        self.MODFORMAT = RM_Field_MODEM_NS_CTRL0_MODFORMAT(self)
        self.zz_fdict['MODFORMAT'] = self.MODFORMAT
        self.DUALCORROPTDIS = RM_Field_MODEM_NS_CTRL0_DUALCORROPTDIS(self)
        self.zz_fdict['DUALCORROPTDIS'] = self.DUALCORROPTDIS
        self.OOKASYNCPIN = RM_Field_MODEM_NS_CTRL0_OOKASYNCPIN(self)
        self.zz_fdict['OOKASYNCPIN'] = self.OOKASYNCPIN
        self.DSSSLEN = RM_Field_MODEM_NS_CTRL0_DSSSLEN(self)
        self.zz_fdict['DSSSLEN'] = self.DSSSLEN
        self.DSSSSHIFTS = RM_Field_MODEM_NS_CTRL0_DSSSSHIFTS(self)
        self.zz_fdict['DSSSSHIFTS'] = self.DSSSSHIFTS
        self.DSSSDOUBLE = RM_Field_MODEM_NS_CTRL0_DSSSDOUBLE(self)
        self.zz_fdict['DSSSDOUBLE'] = self.DSSSDOUBLE
        self.DETDIS = RM_Field_MODEM_NS_CTRL0_DETDIS(self)
        self.zz_fdict['DETDIS'] = self.DETDIS
        self.DIFFENCMODE = RM_Field_MODEM_NS_CTRL0_DIFFENCMODE(self)
        self.zz_fdict['DIFFENCMODE'] = self.DIFFENCMODE
        self.SHAPING = RM_Field_MODEM_NS_CTRL0_SHAPING(self)
        self.zz_fdict['SHAPING'] = self.SHAPING
        self.DEMODRAWDATASEL = RM_Field_MODEM_NS_CTRL0_DEMODRAWDATASEL(self)
        self.zz_fdict['DEMODRAWDATASEL'] = self.DEMODRAWDATASEL
        self.FRAMEDETDEL = RM_Field_MODEM_NS_CTRL0_FRAMEDETDEL(self)
        self.zz_fdict['FRAMEDETDEL'] = self.FRAMEDETDEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL1, self).__init__(rmio, label,
            0xb8014000, 0x050,
            'CTRL1', 'MODEM_NS.CTRL1', 'read-write',
            u"",
            0x00000000, 0xFFFFDFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNCBITS = RM_Field_MODEM_NS_CTRL1_SYNCBITS(self)
        self.zz_fdict['SYNCBITS'] = self.SYNCBITS
        self.SYNCERRORS = RM_Field_MODEM_NS_CTRL1_SYNCERRORS(self)
        self.zz_fdict['SYNCERRORS'] = self.SYNCERRORS
        self.DUALSYNC = RM_Field_MODEM_NS_CTRL1_DUALSYNC(self)
        self.zz_fdict['DUALSYNC'] = self.DUALSYNC
        self.TXSYNC = RM_Field_MODEM_NS_CTRL1_TXSYNC(self)
        self.zz_fdict['TXSYNC'] = self.TXSYNC
        self.SYNCDATA = RM_Field_MODEM_NS_CTRL1_SYNCDATA(self)
        self.zz_fdict['SYNCDATA'] = self.SYNCDATA
        self.SYNC1INV = RM_Field_MODEM_NS_CTRL1_SYNC1INV(self)
        self.zz_fdict['SYNC1INV'] = self.SYNC1INV
        self.COMPMODE = RM_Field_MODEM_NS_CTRL1_COMPMODE(self)
        self.zz_fdict['COMPMODE'] = self.COMPMODE
        self.RESYNCPER = RM_Field_MODEM_NS_CTRL1_RESYNCPER(self)
        self.zz_fdict['RESYNCPER'] = self.RESYNCPER
        self.PHASEDEMOD = RM_Field_MODEM_NS_CTRL1_PHASEDEMOD(self)
        self.zz_fdict['PHASEDEMOD'] = self.PHASEDEMOD
        self.FREQOFFESTPER = RM_Field_MODEM_NS_CTRL1_FREQOFFESTPER(self)
        self.zz_fdict['FREQOFFESTPER'] = self.FREQOFFESTPER
        self.FREQOFFESTLIM = RM_Field_MODEM_NS_CTRL1_FREQOFFESTLIM(self)
        self.zz_fdict['FREQOFFESTLIM'] = self.FREQOFFESTLIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL2, self).__init__(rmio, label,
            0xb8014000, 0x054,
            'CTRL2', 'MODEM_NS.CTRL2', 'read-write',
            u"",
            0x00001000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SQITHRESH = RM_Field_MODEM_NS_CTRL2_SQITHRESH(self)
        self.zz_fdict['SQITHRESH'] = self.SQITHRESH
        self.RXFRCDIS = RM_Field_MODEM_NS_CTRL2_RXFRCDIS(self)
        self.zz_fdict['RXFRCDIS'] = self.RXFRCDIS
        self.RXPINMODE = RM_Field_MODEM_NS_CTRL2_RXPINMODE(self)
        self.zz_fdict['RXPINMODE'] = self.RXPINMODE
        self.TXPINMODE = RM_Field_MODEM_NS_CTRL2_TXPINMODE(self)
        self.zz_fdict['TXPINMODE'] = self.TXPINMODE
        self.DATAFILTER = RM_Field_MODEM_NS_CTRL2_DATAFILTER(self)
        self.zz_fdict['DATAFILTER'] = self.DATAFILTER
        self.BRDIVA = RM_Field_MODEM_NS_CTRL2_BRDIVA(self)
        self.zz_fdict['BRDIVA'] = self.BRDIVA
        self.BRDIVB = RM_Field_MODEM_NS_CTRL2_BRDIVB(self)
        self.zz_fdict['BRDIVB'] = self.BRDIVB
        self.DEVMULA = RM_Field_MODEM_NS_CTRL2_DEVMULA(self)
        self.zz_fdict['DEVMULA'] = self.DEVMULA
        self.DEVMULB = RM_Field_MODEM_NS_CTRL2_DEVMULB(self)
        self.zz_fdict['DEVMULB'] = self.DEVMULB
        self.RATESELMODE = RM_Field_MODEM_NS_CTRL2_RATESELMODE(self)
        self.zz_fdict['RATESELMODE'] = self.RATESELMODE
        self.DEVWEIGHTDIS = RM_Field_MODEM_NS_CTRL2_DEVWEIGHTDIS(self)
        self.zz_fdict['DEVWEIGHTDIS'] = self.DEVWEIGHTDIS
        self.DMASEL = RM_Field_MODEM_NS_CTRL2_DMASEL(self)
        self.zz_fdict['DMASEL'] = self.DMASEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL3, self).__init__(rmio, label,
            0xb8014000, 0x058,
            'CTRL3', 'MODEM_NS.CTRL3', 'read-write',
            u"",
            0x00008000, 0xFFFFFF8F,
            0x00001000, 0x00002000,
            0x00003000)

        self.PRSDINEN = RM_Field_MODEM_NS_CTRL3_PRSDINEN(self)
        self.zz_fdict['PRSDINEN'] = self.PRSDINEN
        self.TIMINGBASESGAIN = RM_Field_MODEM_NS_CTRL3_TIMINGBASESGAIN(self)
        self.zz_fdict['TIMINGBASESGAIN'] = self.TIMINGBASESGAIN
        self.DEVMULBCW = RM_Field_MODEM_NS_CTRL3_DEVMULBCW(self)
        self.zz_fdict['DEVMULBCW'] = self.DEVMULBCW
        self.RAMTESTEN = RM_Field_MODEM_NS_CTRL3_RAMTESTEN(self)
        self.zz_fdict['RAMTESTEN'] = self.RAMTESTEN
        self.ANTDIVMODE = RM_Field_MODEM_NS_CTRL3_ANTDIVMODE(self)
        self.zz_fdict['ANTDIVMODE'] = self.ANTDIVMODE
        self.ANTDIVREPEATDIS = RM_Field_MODEM_NS_CTRL3_ANTDIVREPEATDIS(self)
        self.zz_fdict['ANTDIVREPEATDIS'] = self.ANTDIVREPEATDIS
        self.TSAMPMODE = RM_Field_MODEM_NS_CTRL3_TSAMPMODE(self)
        self.zz_fdict['TSAMPMODE'] = self.TSAMPMODE
        self.TSAMPDEL = RM_Field_MODEM_NS_CTRL3_TSAMPDEL(self)
        self.zz_fdict['TSAMPDEL'] = self.TSAMPDEL
        self.TSAMPLIM = RM_Field_MODEM_NS_CTRL3_TSAMPLIM(self)
        self.zz_fdict['TSAMPLIM'] = self.TSAMPLIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL4, self).__init__(rmio, label,
            0xb8014000, 0x05C,
            'CTRL4', 'MODEM_NS.CTRL4', 'read-write',
            u"",
            0x03000000, 0xBFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ISICOMP = RM_Field_MODEM_NS_CTRL4_ISICOMP(self)
        self.zz_fdict['ISICOMP'] = self.ISICOMP
        self.DEVOFFCOMP = RM_Field_MODEM_NS_CTRL4_DEVOFFCOMP(self)
        self.zz_fdict['DEVOFFCOMP'] = self.DEVOFFCOMP
        self.PREDISTGAIN = RM_Field_MODEM_NS_CTRL4_PREDISTGAIN(self)
        self.zz_fdict['PREDISTGAIN'] = self.PREDISTGAIN
        self.PREDISTDEB = RM_Field_MODEM_NS_CTRL4_PREDISTDEB(self)
        self.zz_fdict['PREDISTDEB'] = self.PREDISTDEB
        self.PREDISTAVG = RM_Field_MODEM_NS_CTRL4_PREDISTAVG(self)
        self.zz_fdict['PREDISTAVG'] = self.PREDISTAVG
        self.PREDISTRST = RM_Field_MODEM_NS_CTRL4_PREDISTRST(self)
        self.zz_fdict['PREDISTRST'] = self.PREDISTRST
        self.PHASECLICKFILT = RM_Field_MODEM_NS_CTRL4_PHASECLICKFILT(self)
        self.zz_fdict['PHASECLICKFILT'] = self.PHASECLICKFILT
        self.SOFTDSSSMODE = RM_Field_MODEM_NS_CTRL4_SOFTDSSSMODE(self)
        self.zz_fdict['SOFTDSSSMODE'] = self.SOFTDSSSMODE
        self.ADCSATLEVEL = RM_Field_MODEM_NS_CTRL4_ADCSATLEVEL(self)
        self.zz_fdict['ADCSATLEVEL'] = self.ADCSATLEVEL
        self.ADCSATDENS = RM_Field_MODEM_NS_CTRL4_ADCSATDENS(self)
        self.zz_fdict['ADCSATDENS'] = self.ADCSATDENS
        self.OFFSETPHASEMASKING = RM_Field_MODEM_NS_CTRL4_OFFSETPHASEMASKING(self)
        self.zz_fdict['OFFSETPHASEMASKING'] = self.OFFSETPHASEMASKING
        self.OFFSETPHASESCALING = RM_Field_MODEM_NS_CTRL4_OFFSETPHASESCALING(self)
        self.zz_fdict['OFFSETPHASESCALING'] = self.OFFSETPHASESCALING
        self.CLKUNDIVREQ = RM_Field_MODEM_NS_CTRL4_CLKUNDIVREQ(self)
        self.zz_fdict['CLKUNDIVREQ'] = self.CLKUNDIVREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL5, self).__init__(rmio, label,
            0xb8014000, 0x060,
            'CTRL5', 'MODEM_NS.CTRL5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFE,
            0x00001000, 0x00002000,
            0x00003000)

        self.BRCALEN = RM_Field_MODEM_NS_CTRL5_BRCALEN(self)
        self.zz_fdict['BRCALEN'] = self.BRCALEN
        self.BRCALMODE = RM_Field_MODEM_NS_CTRL5_BRCALMODE(self)
        self.zz_fdict['BRCALMODE'] = self.BRCALMODE
        self.BRCALAVG = RM_Field_MODEM_NS_CTRL5_BRCALAVG(self)
        self.zz_fdict['BRCALAVG'] = self.BRCALAVG
        self.DETDEL = RM_Field_MODEM_NS_CTRL5_DETDEL(self)
        self.zz_fdict['DETDEL'] = self.DETDEL
        self.TDEDGE = RM_Field_MODEM_NS_CTRL5_TDEDGE(self)
        self.zz_fdict['TDEDGE'] = self.TDEDGE
        self.TREDGE = RM_Field_MODEM_NS_CTRL5_TREDGE(self)
        self.zz_fdict['TREDGE'] = self.TREDGE
        self.DSSSCTD = RM_Field_MODEM_NS_CTRL5_DSSSCTD(self)
        self.zz_fdict['DSSSCTD'] = self.DSSSCTD
        self.RESYNCLIMIT = RM_Field_MODEM_NS_CTRL5_RESYNCLIMIT(self)
        self.zz_fdict['RESYNCLIMIT'] = self.RESYNCLIMIT
        self.FOEPREAVG = RM_Field_MODEM_NS_CTRL5_FOEPREAVG(self)
        self.zz_fdict['FOEPREAVG'] = self.FOEPREAVG
        self.POEPER = RM_Field_MODEM_NS_CTRL5_POEPER(self)
        self.zz_fdict['POEPER'] = self.POEPER
        self.DEMODRAWDATASEL2 = RM_Field_MODEM_NS_CTRL5_DEMODRAWDATASEL2(self)
        self.zz_fdict['DEMODRAWDATASEL2'] = self.DEMODRAWDATASEL2
        self.LINCORR = RM_Field_MODEM_NS_CTRL5_LINCORR(self)
        self.zz_fdict['LINCORR'] = self.LINCORR
        self.DEC2 = RM_Field_MODEM_NS_CTRL5_DEC2(self)
        self.zz_fdict['DEC2'] = self.DEC2
        self.RESYNCBAUDTRANS = RM_Field_MODEM_NS_CTRL5_RESYNCBAUDTRANS(self)
        self.zz_fdict['RESYNCBAUDTRANS'] = self.RESYNCBAUDTRANS
        self.INTOSR = RM_Field_MODEM_NS_CTRL5_INTOSR(self)
        self.zz_fdict['INTOSR'] = self.INTOSR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL6, self).__init__(rmio, label,
            0xb8014000, 0x064,
            'CTRL6', 'MODEM_NS.CTRL6', 'read-write',
            u"",
            0x00000000, 0xF6FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TDREW = RM_Field_MODEM_NS_CTRL6_TDREW(self)
        self.zz_fdict['TDREW'] = self.TDREW
        self.PREBASES = RM_Field_MODEM_NS_CTRL6_PREBASES(self)
        self.zz_fdict['PREBASES'] = self.PREBASES
        self.PSTIMABORT0 = RM_Field_MODEM_NS_CTRL6_PSTIMABORT0(self)
        self.zz_fdict['PSTIMABORT0'] = self.PSTIMABORT0
        self.PSTIMABORT1 = RM_Field_MODEM_NS_CTRL6_PSTIMABORT1(self)
        self.zz_fdict['PSTIMABORT1'] = self.PSTIMABORT1
        self.PSTIMABORT2 = RM_Field_MODEM_NS_CTRL6_PSTIMABORT2(self)
        self.zz_fdict['PSTIMABORT2'] = self.PSTIMABORT2
        self.PSTIMABORT3 = RM_Field_MODEM_NS_CTRL6_PSTIMABORT3(self)
        self.zz_fdict['PSTIMABORT3'] = self.PSTIMABORT3
        self.ARW = RM_Field_MODEM_NS_CTRL6_ARW(self)
        self.zz_fdict['ARW'] = self.ARW
        self.TIMTHRESHGAIN = RM_Field_MODEM_NS_CTRL6_TIMTHRESHGAIN(self)
        self.zz_fdict['TIMTHRESHGAIN'] = self.TIMTHRESHGAIN
        self.CPLXCORREN = RM_Field_MODEM_NS_CTRL6_CPLXCORREN(self)
        self.zz_fdict['CPLXCORREN'] = self.CPLXCORREN
        self.DSSS3SYMBOLSYNCEN = RM_Field_MODEM_NS_CTRL6_DSSS3SYMBOLSYNCEN(self)
        self.zz_fdict['DSSS3SYMBOLSYNCEN'] = self.DSSS3SYMBOLSYNCEN
        self.TXDBPSKINV = RM_Field_MODEM_NS_CTRL6_TXDBPSKINV(self)
        self.zz_fdict['TXDBPSKINV'] = self.TXDBPSKINV
        self.TXDBPSKRAMPEN = RM_Field_MODEM_NS_CTRL6_TXDBPSKRAMPEN(self)
        self.zz_fdict['TXDBPSKRAMPEN'] = self.TXDBPSKRAMPEN
        self.CODINGB = RM_Field_MODEM_NS_CTRL6_CODINGB(self)
        self.zz_fdict['CODINGB'] = self.CODINGB
        self.RXRESTARTUPONRSSI = RM_Field_MODEM_NS_CTRL6_RXRESTARTUPONRSSI(self)
        self.zz_fdict['RXRESTARTUPONRSSI'] = self.RXRESTARTUPONRSSI
        self.RXRESTARTUPONSHORTRSSI = RM_Field_MODEM_NS_CTRL6_RXRESTARTUPONSHORTRSSI(self)
        self.zz_fdict['RXRESTARTUPONSHORTRSSI'] = self.RXRESTARTUPONSHORTRSSI
        self.RXBRCALCDIS = RM_Field_MODEM_NS_CTRL6_RXBRCALCDIS(self)
        self.zz_fdict['RXBRCALCDIS'] = self.RXBRCALCDIS
        self.DEMODRESTARTALL = RM_Field_MODEM_NS_CTRL6_DEMODRESTARTALL(self)
        self.zz_fdict['DEMODRESTARTALL'] = self.DEMODRESTARTALL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TXBR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TXBR, self).__init__(rmio, label,
            0xb8014000, 0x068,
            'TXBR', 'MODEM_NS.TXBR', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXBRNUM = RM_Field_MODEM_NS_TXBR_TXBRNUM(self)
        self.zz_fdict['TXBRNUM'] = self.TXBRNUM
        self.TXBRDEN = RM_Field_MODEM_NS_TXBR_TXBRDEN(self)
        self.zz_fdict['TXBRDEN'] = self.TXBRDEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_RXBR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_RXBR, self).__init__(rmio, label,
            0xb8014000, 0x06C,
            'RXBR', 'MODEM_NS.RXBR', 'read-write',
            u"",
            0x00000000, 0x00001FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXBRNUM = RM_Field_MODEM_NS_RXBR_RXBRNUM(self)
        self.zz_fdict['RXBRNUM'] = self.RXBRNUM
        self.RXBRDEN = RM_Field_MODEM_NS_RXBR_RXBRDEN(self)
        self.zz_fdict['RXBRDEN'] = self.RXBRDEN
        self.RXBRINT = RM_Field_MODEM_NS_RXBR_RXBRINT(self)
        self.zz_fdict['RXBRINT'] = self.RXBRINT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PRE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PRE, self).__init__(rmio, label,
            0xb8014000, 0x074,
            'PRE', 'MODEM_NS.PRE', 'read-write',
            u"",
            0x00000000, 0xFFFFDFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BASE = RM_Field_MODEM_NS_PRE_BASE(self)
        self.zz_fdict['BASE'] = self.BASE
        self.BASEBITS = RM_Field_MODEM_NS_PRE_BASEBITS(self)
        self.zz_fdict['BASEBITS'] = self.BASEBITS
        self.PRESYMB4FSK = RM_Field_MODEM_NS_PRE_PRESYMB4FSK(self)
        self.zz_fdict['PRESYMB4FSK'] = self.PRESYMB4FSK
        self.PREERRORS = RM_Field_MODEM_NS_PRE_PREERRORS(self)
        self.zz_fdict['PREERRORS'] = self.PREERRORS
        self.DSSSPRE = RM_Field_MODEM_NS_PRE_DSSSPRE(self)
        self.zz_fdict['DSSSPRE'] = self.DSSSPRE
        self.SYNCSYMB4FSK = RM_Field_MODEM_NS_PRE_SYNCSYMB4FSK(self)
        self.zz_fdict['SYNCSYMB4FSK'] = self.SYNCSYMB4FSK
        self.PREWNDERRORS = RM_Field_MODEM_NS_PRE_PREWNDERRORS(self)
        self.zz_fdict['PREWNDERRORS'] = self.PREWNDERRORS
        self.TXBASES = RM_Field_MODEM_NS_PRE_TXBASES(self)
        self.zz_fdict['TXBASES'] = self.TXBASES
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYNC0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYNC0, self).__init__(rmio, label,
            0xb8014000, 0x078,
            'SYNC0', 'MODEM_NS.SYNC0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNC0 = RM_Field_MODEM_NS_SYNC0_SYNC0(self)
        self.zz_fdict['SYNC0'] = self.SYNC0
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYNC1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYNC1, self).__init__(rmio, label,
            0xb8014000, 0x07C,
            'SYNC1', 'MODEM_NS.SYNC1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNC1 = RM_Field_MODEM_NS_SYNC1_SYNC1(self)
        self.zz_fdict['SYNC1'] = self.SYNC1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TIMING(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TIMING, self).__init__(rmio, label,
            0xb8014000, 0x080,
            'TIMING', 'MODEM_NS.TIMING', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMTHRESH = RM_Field_MODEM_NS_TIMING_TIMTHRESH(self)
        self.zz_fdict['TIMTHRESH'] = self.TIMTHRESH
        self.TIMINGBASES = RM_Field_MODEM_NS_TIMING_TIMINGBASES(self)
        self.zz_fdict['TIMINGBASES'] = self.TIMINGBASES
        self.ADDTIMSEQ = RM_Field_MODEM_NS_TIMING_ADDTIMSEQ(self)
        self.zz_fdict['ADDTIMSEQ'] = self.ADDTIMSEQ
        self.TIMSEQINVEN = RM_Field_MODEM_NS_TIMING_TIMSEQINVEN(self)
        self.zz_fdict['TIMSEQINVEN'] = self.TIMSEQINVEN
        self.TIMSEQSYNC = RM_Field_MODEM_NS_TIMING_TIMSEQSYNC(self)
        self.zz_fdict['TIMSEQSYNC'] = self.TIMSEQSYNC
        self.FDM0THRESH = RM_Field_MODEM_NS_TIMING_FDM0THRESH(self)
        self.zz_fdict['FDM0THRESH'] = self.FDM0THRESH
        self.OFFSUBNUM = RM_Field_MODEM_NS_TIMING_OFFSUBNUM(self)
        self.zz_fdict['OFFSUBNUM'] = self.OFFSUBNUM
        self.OFFSUBDEN = RM_Field_MODEM_NS_TIMING_OFFSUBDEN(self)
        self.zz_fdict['OFFSUBDEN'] = self.OFFSUBDEN
        self.TSAGCDEL = RM_Field_MODEM_NS_TIMING_TSAGCDEL(self)
        self.zz_fdict['TSAGCDEL'] = self.TSAGCDEL
        self.FASTRESYNC = RM_Field_MODEM_NS_TIMING_FASTRESYNC(self)
        self.zz_fdict['FASTRESYNC'] = self.FASTRESYNC
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSSS0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSSS0, self).__init__(rmio, label,
            0xb8014000, 0x084,
            'DSSS0', 'MODEM_NS.DSSS0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DSSS0 = RM_Field_MODEM_NS_DSSS0_DSSS0(self)
        self.zz_fdict['DSSS0'] = self.DSSS0
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_MODINDEX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_MODINDEX, self).__init__(rmio, label,
            0xb8014000, 0x088,
            'MODINDEX', 'MODEM_NS.MODINDEX', 'read-write',
            u"",
            0x00000000, 0x003F1FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODINDEXM = RM_Field_MODEM_NS_MODINDEX_MODINDEXM(self)
        self.zz_fdict['MODINDEXM'] = self.MODINDEXM
        self.MODINDEXE = RM_Field_MODEM_NS_MODINDEX_MODINDEXE(self)
        self.zz_fdict['MODINDEXE'] = self.MODINDEXE
        self.FREQGAINE = RM_Field_MODEM_NS_MODINDEX_FREQGAINE(self)
        self.zz_fdict['FREQGAINE'] = self.FREQGAINE
        self.FREQGAINM = RM_Field_MODEM_NS_MODINDEX_FREQGAINM(self)
        self.zz_fdict['FREQGAINM'] = self.FREQGAINM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AFC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AFC, self).__init__(rmio, label,
            0xb8014000, 0x08C,
            'AFC', 'MODEM_NS.AFC', 'read-write',
            u"",
            0x00000000, 0xFFFFFC00,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCRXMODE = RM_Field_MODEM_NS_AFC_AFCRXMODE(self)
        self.zz_fdict['AFCRXMODE'] = self.AFCRXMODE
        self.AFCTXMODE = RM_Field_MODEM_NS_AFC_AFCTXMODE(self)
        self.zz_fdict['AFCTXMODE'] = self.AFCTXMODE
        self.AFCRXCLR = RM_Field_MODEM_NS_AFC_AFCRXCLR(self)
        self.zz_fdict['AFCRXCLR'] = self.AFCRXCLR
        self.AFCDEL = RM_Field_MODEM_NS_AFC_AFCDEL(self)
        self.zz_fdict['AFCDEL'] = self.AFCDEL
        self.AFCAVGPER = RM_Field_MODEM_NS_AFC_AFCAVGPER(self)
        self.zz_fdict['AFCAVGPER'] = self.AFCAVGPER
        self.AFCLIMRESET = RM_Field_MODEM_NS_AFC_AFCLIMRESET(self)
        self.zz_fdict['AFCLIMRESET'] = self.AFCLIMRESET
        self.AFCONESHOT = RM_Field_MODEM_NS_AFC_AFCONESHOT(self)
        self.zz_fdict['AFCONESHOT'] = self.AFCONESHOT
        self.AFCENINTCOMP = RM_Field_MODEM_NS_AFC_AFCENINTCOMP(self)
        self.zz_fdict['AFCENINTCOMP'] = self.AFCENINTCOMP
        self.AFCDSAFREQOFFEST = RM_Field_MODEM_NS_AFC_AFCDSAFREQOFFEST(self)
        self.zz_fdict['AFCDSAFREQOFFEST'] = self.AFCDSAFREQOFFEST
        self.AFCDELDET = RM_Field_MODEM_NS_AFC_AFCDELDET(self)
        self.zz_fdict['AFCDELDET'] = self.AFCDELDET
        self.AFCGEAR = RM_Field_MODEM_NS_AFC_AFCGEAR(self)
        self.zz_fdict['AFCGEAR'] = self.AFCGEAR
        self.DISAFCCTE = RM_Field_MODEM_NS_AFC_DISAFCCTE(self)
        self.zz_fdict['DISAFCCTE'] = self.DISAFCCTE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AFCADJLIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AFCADJLIM, self).__init__(rmio, label,
            0xb8014000, 0x090,
            'AFCADJLIM', 'MODEM_NS.AFCADJLIM', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCADJLIM = RM_Field_MODEM_NS_AFCADJLIM_AFCADJLIM(self)
        self.zz_fdict['AFCADJLIM'] = self.AFCADJLIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING0, self).__init__(rmio, label,
            0xb8014000, 0x094,
            'SHAPING0', 'MODEM_NS.SHAPING0', 'read-write',
            u"",
            0x22130A04, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF0 = RM_Field_MODEM_NS_SHAPING0_COEFF0(self)
        self.zz_fdict['COEFF0'] = self.COEFF0
        self.COEFF1 = RM_Field_MODEM_NS_SHAPING0_COEFF1(self)
        self.zz_fdict['COEFF1'] = self.COEFF1
        self.COEFF2 = RM_Field_MODEM_NS_SHAPING0_COEFF2(self)
        self.zz_fdict['COEFF2'] = self.COEFF2
        self.COEFF3 = RM_Field_MODEM_NS_SHAPING0_COEFF3(self)
        self.zz_fdict['COEFF3'] = self.COEFF3
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING1, self).__init__(rmio, label,
            0xb8014000, 0x098,
            'SHAPING1', 'MODEM_NS.SHAPING1', 'read-write',
            u"",
            0x4F4A4132, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF4 = RM_Field_MODEM_NS_SHAPING1_COEFF4(self)
        self.zz_fdict['COEFF4'] = self.COEFF4
        self.COEFF5 = RM_Field_MODEM_NS_SHAPING1_COEFF5(self)
        self.zz_fdict['COEFF5'] = self.COEFF5
        self.COEFF6 = RM_Field_MODEM_NS_SHAPING1_COEFF6(self)
        self.zz_fdict['COEFF6'] = self.COEFF6
        self.COEFF7 = RM_Field_MODEM_NS_SHAPING1_COEFF7(self)
        self.zz_fdict['COEFF7'] = self.COEFF7
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING2, self).__init__(rmio, label,
            0xb8014000, 0x09C,
            'SHAPING2', 'MODEM_NS.SHAPING2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF8 = RM_Field_MODEM_NS_SHAPING2_COEFF8(self)
        self.zz_fdict['COEFF8'] = self.COEFF8
        self.COEFF9 = RM_Field_MODEM_NS_SHAPING2_COEFF9(self)
        self.zz_fdict['COEFF9'] = self.COEFF9
        self.COEFF10 = RM_Field_MODEM_NS_SHAPING2_COEFF10(self)
        self.zz_fdict['COEFF10'] = self.COEFF10
        self.COEFF11 = RM_Field_MODEM_NS_SHAPING2_COEFF11(self)
        self.zz_fdict['COEFF11'] = self.COEFF11
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING3, self).__init__(rmio, label,
            0xb8014000, 0x0A0,
            'SHAPING3', 'MODEM_NS.SHAPING3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF12 = RM_Field_MODEM_NS_SHAPING3_COEFF12(self)
        self.zz_fdict['COEFF12'] = self.COEFF12
        self.COEFF13 = RM_Field_MODEM_NS_SHAPING3_COEFF13(self)
        self.zz_fdict['COEFF13'] = self.COEFF13
        self.COEFF14 = RM_Field_MODEM_NS_SHAPING3_COEFF14(self)
        self.zz_fdict['COEFF14'] = self.COEFF14
        self.COEFF15 = RM_Field_MODEM_NS_SHAPING3_COEFF15(self)
        self.zz_fdict['COEFF15'] = self.COEFF15
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING4, self).__init__(rmio, label,
            0xb8014000, 0x0A4,
            'SHAPING4', 'MODEM_NS.SHAPING4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF16 = RM_Field_MODEM_NS_SHAPING4_COEFF16(self)
        self.zz_fdict['COEFF16'] = self.COEFF16
        self.COEFF17 = RM_Field_MODEM_NS_SHAPING4_COEFF17(self)
        self.zz_fdict['COEFF17'] = self.COEFF17
        self.COEFF18 = RM_Field_MODEM_NS_SHAPING4_COEFF18(self)
        self.zz_fdict['COEFF18'] = self.COEFF18
        self.COEFF19 = RM_Field_MODEM_NS_SHAPING4_COEFF19(self)
        self.zz_fdict['COEFF19'] = self.COEFF19
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING5, self).__init__(rmio, label,
            0xb8014000, 0x0A8,
            'SHAPING5', 'MODEM_NS.SHAPING5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF20 = RM_Field_MODEM_NS_SHAPING5_COEFF20(self)
        self.zz_fdict['COEFF20'] = self.COEFF20
        self.COEFF21 = RM_Field_MODEM_NS_SHAPING5_COEFF21(self)
        self.zz_fdict['COEFF21'] = self.COEFF21
        self.COEFF22 = RM_Field_MODEM_NS_SHAPING5_COEFF22(self)
        self.zz_fdict['COEFF22'] = self.COEFF22
        self.COEFF23 = RM_Field_MODEM_NS_SHAPING5_COEFF23(self)
        self.zz_fdict['COEFF23'] = self.COEFF23
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING6, self).__init__(rmio, label,
            0xb8014000, 0x0AC,
            'SHAPING6', 'MODEM_NS.SHAPING6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF24 = RM_Field_MODEM_NS_SHAPING6_COEFF24(self)
        self.zz_fdict['COEFF24'] = self.COEFF24
        self.COEFF25 = RM_Field_MODEM_NS_SHAPING6_COEFF25(self)
        self.zz_fdict['COEFF25'] = self.COEFF25
        self.COEFF26 = RM_Field_MODEM_NS_SHAPING6_COEFF26(self)
        self.zz_fdict['COEFF26'] = self.COEFF26
        self.COEFF27 = RM_Field_MODEM_NS_SHAPING6_COEFF27(self)
        self.zz_fdict['COEFF27'] = self.COEFF27
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING7, self).__init__(rmio, label,
            0xb8014000, 0x0B0,
            'SHAPING7', 'MODEM_NS.SHAPING7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF28 = RM_Field_MODEM_NS_SHAPING7_COEFF28(self)
        self.zz_fdict['COEFF28'] = self.COEFF28
        self.COEFF29 = RM_Field_MODEM_NS_SHAPING7_COEFF29(self)
        self.zz_fdict['COEFF29'] = self.COEFF29
        self.COEFF30 = RM_Field_MODEM_NS_SHAPING7_COEFF30(self)
        self.zz_fdict['COEFF30'] = self.COEFF30
        self.COEFF31 = RM_Field_MODEM_NS_SHAPING7_COEFF31(self)
        self.zz_fdict['COEFF31'] = self.COEFF31
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING8, self).__init__(rmio, label,
            0xb8014000, 0x0B4,
            'SHAPING8', 'MODEM_NS.SHAPING8', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF32 = RM_Field_MODEM_NS_SHAPING8_COEFF32(self)
        self.zz_fdict['COEFF32'] = self.COEFF32
        self.COEFF33 = RM_Field_MODEM_NS_SHAPING8_COEFF33(self)
        self.zz_fdict['COEFF33'] = self.COEFF33
        self.COEFF34 = RM_Field_MODEM_NS_SHAPING8_COEFF34(self)
        self.zz_fdict['COEFF34'] = self.COEFF34
        self.COEFF35 = RM_Field_MODEM_NS_SHAPING8_COEFF35(self)
        self.zz_fdict['COEFF35'] = self.COEFF35
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING9, self).__init__(rmio, label,
            0xb8014000, 0x0B8,
            'SHAPING9', 'MODEM_NS.SHAPING9', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF36 = RM_Field_MODEM_NS_SHAPING9_COEFF36(self)
        self.zz_fdict['COEFF36'] = self.COEFF36
        self.COEFF37 = RM_Field_MODEM_NS_SHAPING9_COEFF37(self)
        self.zz_fdict['COEFF37'] = self.COEFF37
        self.COEFF38 = RM_Field_MODEM_NS_SHAPING9_COEFF38(self)
        self.zz_fdict['COEFF38'] = self.COEFF38
        self.COEFF39 = RM_Field_MODEM_NS_SHAPING9_COEFF39(self)
        self.zz_fdict['COEFF39'] = self.COEFF39
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING10, self).__init__(rmio, label,
            0xb8014000, 0x0BC,
            'SHAPING10', 'MODEM_NS.SHAPING10', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF40 = RM_Field_MODEM_NS_SHAPING10_COEFF40(self)
        self.zz_fdict['COEFF40'] = self.COEFF40
        self.COEFF41 = RM_Field_MODEM_NS_SHAPING10_COEFF41(self)
        self.zz_fdict['COEFF41'] = self.COEFF41
        self.COEFF42 = RM_Field_MODEM_NS_SHAPING10_COEFF42(self)
        self.zz_fdict['COEFF42'] = self.COEFF42
        self.COEFF43 = RM_Field_MODEM_NS_SHAPING10_COEFF43(self)
        self.zz_fdict['COEFF43'] = self.COEFF43
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING11(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING11, self).__init__(rmio, label,
            0xb8014000, 0x0C0,
            'SHAPING11', 'MODEM_NS.SHAPING11', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF44 = RM_Field_MODEM_NS_SHAPING11_COEFF44(self)
        self.zz_fdict['COEFF44'] = self.COEFF44
        self.COEFF45 = RM_Field_MODEM_NS_SHAPING11_COEFF45(self)
        self.zz_fdict['COEFF45'] = self.COEFF45
        self.COEFF46 = RM_Field_MODEM_NS_SHAPING11_COEFF46(self)
        self.zz_fdict['COEFF46'] = self.COEFF46
        self.COEFF47 = RM_Field_MODEM_NS_SHAPING11_COEFF47(self)
        self.zz_fdict['COEFF47'] = self.COEFF47
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING12(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING12, self).__init__(rmio, label,
            0xb8014000, 0x0C4,
            'SHAPING12', 'MODEM_NS.SHAPING12', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF48 = RM_Field_MODEM_NS_SHAPING12_COEFF48(self)
        self.zz_fdict['COEFF48'] = self.COEFF48
        self.COEFF49 = RM_Field_MODEM_NS_SHAPING12_COEFF49(self)
        self.zz_fdict['COEFF49'] = self.COEFF49
        self.COEFF50 = RM_Field_MODEM_NS_SHAPING12_COEFF50(self)
        self.zz_fdict['COEFF50'] = self.COEFF50
        self.COEFF51 = RM_Field_MODEM_NS_SHAPING12_COEFF51(self)
        self.zz_fdict['COEFF51'] = self.COEFF51
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING13(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING13, self).__init__(rmio, label,
            0xb8014000, 0x0C8,
            'SHAPING13', 'MODEM_NS.SHAPING13', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF52 = RM_Field_MODEM_NS_SHAPING13_COEFF52(self)
        self.zz_fdict['COEFF52'] = self.COEFF52
        self.COEFF53 = RM_Field_MODEM_NS_SHAPING13_COEFF53(self)
        self.zz_fdict['COEFF53'] = self.COEFF53
        self.COEFF54 = RM_Field_MODEM_NS_SHAPING13_COEFF54(self)
        self.zz_fdict['COEFF54'] = self.COEFF54
        self.COEFF55 = RM_Field_MODEM_NS_SHAPING13_COEFF55(self)
        self.zz_fdict['COEFF55'] = self.COEFF55
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING14(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING14, self).__init__(rmio, label,
            0xb8014000, 0x0CC,
            'SHAPING14', 'MODEM_NS.SHAPING14', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF56 = RM_Field_MODEM_NS_SHAPING14_COEFF56(self)
        self.zz_fdict['COEFF56'] = self.COEFF56
        self.COEFF57 = RM_Field_MODEM_NS_SHAPING14_COEFF57(self)
        self.zz_fdict['COEFF57'] = self.COEFF57
        self.COEFF58 = RM_Field_MODEM_NS_SHAPING14_COEFF58(self)
        self.zz_fdict['COEFF58'] = self.COEFF58
        self.COEFF59 = RM_Field_MODEM_NS_SHAPING14_COEFF59(self)
        self.zz_fdict['COEFF59'] = self.COEFF59
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING15(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING15, self).__init__(rmio, label,
            0xb8014000, 0x0D0,
            'SHAPING15', 'MODEM_NS.SHAPING15', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF60 = RM_Field_MODEM_NS_SHAPING15_COEFF60(self)
        self.zz_fdict['COEFF60'] = self.COEFF60
        self.COEFF61 = RM_Field_MODEM_NS_SHAPING15_COEFF61(self)
        self.zz_fdict['COEFF61'] = self.COEFF61
        self.COEFF62 = RM_Field_MODEM_NS_SHAPING15_COEFF62(self)
        self.zz_fdict['COEFF62'] = self.COEFF62
        self.COEFF63 = RM_Field_MODEM_NS_SHAPING15_COEFF63(self)
        self.zz_fdict['COEFF63'] = self.COEFF63
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_OOKSHAPING(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_OOKSHAPING, self).__init__(rmio, label,
            0xb8014000, 0x0D4,
            'OOKSHAPING', 'MODEM_NS.OOKSHAPING', 'read-write',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.OOKSHAPINGEN = RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGEN(self)
        self.zz_fdict['OOKSHAPINGEN'] = self.OOKSHAPINGEN
        self.OOKSHAPINGSTEP = RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGSTEP(self)
        self.zz_fdict['OOKSHAPINGSTEP'] = self.OOKSHAPINGSTEP
        self.OOKSHAPINGRATE = RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGRATE(self)
        self.zz_fdict['OOKSHAPINGRATE'] = self.OOKSHAPINGRATE
        self.OOKSHAPINGLUTSIZE = RM_Field_MODEM_NS_OOKSHAPING_OOKSHAPINGLUTSIZE(self)
        self.zz_fdict['OOKSHAPINGLUTSIZE'] = self.OOKSHAPINGLUTSIZE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_RAMPCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_RAMPCTRL, self).__init__(rmio, label,
            0xb8014000, 0x0D8,
            'RAMPCTRL', 'MODEM_NS.RAMPCTRL', 'read-write',
            u"",
            0x00000555, 0x00FF1FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RAMPRATE0 = RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE0(self)
        self.zz_fdict['RAMPRATE0'] = self.RAMPRATE0
        self.RAMPRATE1 = RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE1(self)
        self.zz_fdict['RAMPRATE1'] = self.RAMPRATE1
        self.RAMPRATE2 = RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE2(self)
        self.zz_fdict['RAMPRATE2'] = self.RAMPRATE2
        self.RAMPDIS = RM_Field_MODEM_NS_RAMPCTRL_RAMPDIS(self)
        self.zz_fdict['RAMPDIS'] = self.RAMPDIS
        self.RAMPVAL = RM_Field_MODEM_NS_RAMPCTRL_RAMPVAL(self)
        self.zz_fdict['RAMPVAL'] = self.RAMPVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_RAMPLEV(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_RAMPLEV, self).__init__(rmio, label,
            0xb8014000, 0x0DC,
            'RAMPLEV', 'MODEM_NS.RAMPLEV', 'read-write',
            u"",
            0x009F9F9F, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RAMPLEV0 = RM_Field_MODEM_NS_RAMPLEV_RAMPLEV0(self)
        self.zz_fdict['RAMPLEV0'] = self.RAMPLEV0
        self.RAMPLEV1 = RM_Field_MODEM_NS_RAMPLEV_RAMPLEV1(self)
        self.zz_fdict['RAMPLEV1'] = self.RAMPLEV1
        self.RAMPLEV2 = RM_Field_MODEM_NS_RAMPLEV_RAMPLEV2(self)
        self.zz_fdict['RAMPLEV2'] = self.RAMPLEV2
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMPCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMPCTRL, self).__init__(rmio, label,
            0xb8014000, 0x0E0,
            'ANARAMPCTRL', 'MODEM_NS.ANARAMPCTRL', 'read-write',
            u"",
            0x00000A81, 0x00001FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPEN = RM_Field_MODEM_NS_ANARAMPCTRL_ANARAMPEN(self)
        self.zz_fdict['ANARAMPEN'] = self.ANARAMPEN
        self.RAMPOVREN = RM_Field_MODEM_NS_ANARAMPCTRL_RAMPOVREN(self)
        self.zz_fdict['RAMPOVREN'] = self.RAMPOVREN
        self.RAMPOVRUPD = RM_Field_MODEM_NS_ANARAMPCTRL_RAMPOVRUPD(self)
        self.zz_fdict['RAMPOVRUPD'] = self.RAMPOVRUPD
        self.ANARAMPLUTODEV = RM_Field_MODEM_NS_ANARAMPCTRL_ANARAMPLUTODEV(self)
        self.zz_fdict['ANARAMPLUTODEV'] = self.ANARAMPLUTODEV
        self.VMIDCTRL = RM_Field_MODEM_NS_ANARAMPCTRL_VMIDCTRL(self)
        self.zz_fdict['VMIDCTRL'] = self.VMIDCTRL
        self.MUTEDLY = RM_Field_MODEM_NS_ANARAMPCTRL_MUTEDLY(self)
        self.zz_fdict['MUTEDLY'] = self.MUTEDLY
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP0, self).__init__(rmio, label,
            0xb8014000, 0x0E4,
            'ANARAMP0', 'MODEM_NS.ANARAMP0', 'read-write',
            u"",
            0x08418C40, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT0 = RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT0(self)
        self.zz_fdict['ANARAMPLUT0'] = self.ANARAMPLUT0
        self.ANARAMPLUT1 = RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT1(self)
        self.zz_fdict['ANARAMPLUT1'] = self.ANARAMPLUT1
        self.ANARAMPLUT2 = RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT2(self)
        self.zz_fdict['ANARAMPLUT2'] = self.ANARAMPLUT2
        self.ANARAMPLUT3 = RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT3(self)
        self.zz_fdict['ANARAMPLUT3'] = self.ANARAMPLUT3
        self.ANARAMPLUT4 = RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT4(self)
        self.zz_fdict['ANARAMPLUT4'] = self.ANARAMPLUT4
        self.ANARAMPLUT5 = RM_Field_MODEM_NS_ANARAMP0_ANARAMPLUT5(self)
        self.zz_fdict['ANARAMPLUT5'] = self.ANARAMPLUT5
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP1, self).__init__(rmio, label,
            0xb8014000, 0x0E8,
            'ANARAMP1', 'MODEM_NS.ANARAMP1', 'read-write',
            u"",
            0x18A4A0C5, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT6 = RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT6(self)
        self.zz_fdict['ANARAMPLUT6'] = self.ANARAMPLUT6
        self.ANARAMPLUT7 = RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT7(self)
        self.zz_fdict['ANARAMPLUT7'] = self.ANARAMPLUT7
        self.ANARAMPLUT8 = RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT8(self)
        self.zz_fdict['ANARAMPLUT8'] = self.ANARAMPLUT8
        self.ANARAMPLUT9 = RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT9(self)
        self.zz_fdict['ANARAMPLUT9'] = self.ANARAMPLUT9
        self.ANARAMPLUT10 = RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT10(self)
        self.zz_fdict['ANARAMPLUT10'] = self.ANARAMPLUT10
        self.ANARAMPLUT11 = RM_Field_MODEM_NS_ANARAMP1_ANARAMPLUT11(self)
        self.zz_fdict['ANARAMPLUT11'] = self.ANARAMPLUT11
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP2, self).__init__(rmio, label,
            0xb8014000, 0x0EC,
            'ANARAMP2', 'MODEM_NS.ANARAMP2', 'read-write',
            u"",
            0x020ED60D, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT12 = RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT12(self)
        self.zz_fdict['ANARAMPLUT12'] = self.ANARAMPLUT12
        self.ANARAMPLUT13 = RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT13(self)
        self.zz_fdict['ANARAMPLUT13'] = self.ANARAMPLUT13
        self.ANARAMPLUT14 = RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT14(self)
        self.zz_fdict['ANARAMPLUT14'] = self.ANARAMPLUT14
        self.ANARAMPLUT15 = RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT15(self)
        self.zz_fdict['ANARAMPLUT15'] = self.ANARAMPLUT15
        self.ANARAMPLUT16 = RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT16(self)
        self.zz_fdict['ANARAMPLUT16'] = self.ANARAMPLUT16
        self.ANARAMPLUT17 = RM_Field_MODEM_NS_ANARAMP2_ANARAMPLUT17(self)
        self.zz_fdict['ANARAMPLUT17'] = self.ANARAMPLUT17
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP3, self).__init__(rmio, label,
            0xb8014000, 0x0F0,
            'ANARAMP3', 'MODEM_NS.ANARAMP3', 'read-write',
            u"",
            0x06210821, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT18 = RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT18(self)
        self.zz_fdict['ANARAMPLUT18'] = self.ANARAMPLUT18
        self.ANARAMPLUT19 = RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT19(self)
        self.zz_fdict['ANARAMPLUT19'] = self.ANARAMPLUT19
        self.ANARAMPLUT20 = RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT20(self)
        self.zz_fdict['ANARAMPLUT20'] = self.ANARAMPLUT20
        self.ANARAMPLUT21 = RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT21(self)
        self.zz_fdict['ANARAMPLUT21'] = self.ANARAMPLUT21
        self.ANARAMPLUT22 = RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT22(self)
        self.zz_fdict['ANARAMPLUT22'] = self.ANARAMPLUT22
        self.ANARAMPLUT23 = RM_Field_MODEM_NS_ANARAMP3_ANARAMPLUT23(self)
        self.zz_fdict['ANARAMPLUT23'] = self.ANARAMPLUT23
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP4, self).__init__(rmio, label,
            0xb8014000, 0x0F4,
            'ANARAMP4', 'MODEM_NS.ANARAMP4', 'read-write',
            u"",
            0x08420C63, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT24 = RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT24(self)
        self.zz_fdict['ANARAMPLUT24'] = self.ANARAMPLUT24
        self.ANARAMPLUT25 = RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT25(self)
        self.zz_fdict['ANARAMPLUT25'] = self.ANARAMPLUT25
        self.ANARAMPLUT26 = RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT26(self)
        self.zz_fdict['ANARAMPLUT26'] = self.ANARAMPLUT26
        self.ANARAMPLUT27 = RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT27(self)
        self.zz_fdict['ANARAMPLUT27'] = self.ANARAMPLUT27
        self.ANARAMPLUT28 = RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT28(self)
        self.zz_fdict['ANARAMPLUT28'] = self.ANARAMPLUT28
        self.ANARAMPLUT29 = RM_Field_MODEM_NS_ANARAMP4_ANARAMPLUT29(self)
        self.zz_fdict['ANARAMPLUT29'] = self.ANARAMPLUT29
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP5, self).__init__(rmio, label,
            0xb8014000, 0x0F8,
            'ANARAMP5', 'MODEM_NS.ANARAMP5', 'read-write',
            u"",
            0x0C6294A5, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT30 = RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT30(self)
        self.zz_fdict['ANARAMPLUT30'] = self.ANARAMPLUT30
        self.ANARAMPLUT31 = RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT31(self)
        self.zz_fdict['ANARAMPLUT31'] = self.ANARAMPLUT31
        self.ANARAMPLUT32 = RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT32(self)
        self.zz_fdict['ANARAMPLUT32'] = self.ANARAMPLUT32
        self.ANARAMPLUT33 = RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT33(self)
        self.zz_fdict['ANARAMPLUT33'] = self.ANARAMPLUT33
        self.ANARAMPLUT34 = RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT34(self)
        self.zz_fdict['ANARAMPLUT34'] = self.ANARAMPLUT34
        self.ANARAMPLUT35 = RM_Field_MODEM_NS_ANARAMP5_ANARAMPLUT35(self)
        self.zz_fdict['ANARAMPLUT35'] = self.ANARAMPLUT35
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP6, self).__init__(rmio, label,
            0xb8014000, 0x0FC,
            'ANARAMP6', 'MODEM_NS.ANARAMP6', 'read-write',
            u"",
            0x10739CE6, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT36 = RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT36(self)
        self.zz_fdict['ANARAMPLUT36'] = self.ANARAMPLUT36
        self.ANARAMPLUT37 = RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT37(self)
        self.zz_fdict['ANARAMPLUT37'] = self.ANARAMPLUT37
        self.ANARAMPLUT38 = RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT38(self)
        self.zz_fdict['ANARAMPLUT38'] = self.ANARAMPLUT38
        self.ANARAMPLUT39 = RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT39(self)
        self.zz_fdict['ANARAMPLUT39'] = self.ANARAMPLUT39
        self.ANARAMPLUT40 = RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT40(self)
        self.zz_fdict['ANARAMPLUT40'] = self.ANARAMPLUT40
        self.ANARAMPLUT41 = RM_Field_MODEM_NS_ANARAMP6_ANARAMPLUT41(self)
        self.zz_fdict['ANARAMPLUT41'] = self.ANARAMPLUT41
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP7, self).__init__(rmio, label,
            0xb8014000, 0x100,
            'ANARAMP7', 'MODEM_NS.ANARAMP7', 'read-write',
            u"",
            0x1494A508, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT42 = RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT42(self)
        self.zz_fdict['ANARAMPLUT42'] = self.ANARAMPLUT42
        self.ANARAMPLUT43 = RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT43(self)
        self.zz_fdict['ANARAMPLUT43'] = self.ANARAMPLUT43
        self.ANARAMPLUT44 = RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT44(self)
        self.zz_fdict['ANARAMPLUT44'] = self.ANARAMPLUT44
        self.ANARAMPLUT45 = RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT45(self)
        self.zz_fdict['ANARAMPLUT45'] = self.ANARAMPLUT45
        self.ANARAMPLUT46 = RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT46(self)
        self.zz_fdict['ANARAMPLUT46'] = self.ANARAMPLUT46
        self.ANARAMPLUT47 = RM_Field_MODEM_NS_ANARAMP7_ANARAMPLUT47(self)
        self.zz_fdict['ANARAMPLUT47'] = self.ANARAMPLUT47
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP8, self).__init__(rmio, label,
            0xb8014000, 0x104,
            'ANARAMP8', 'MODEM_NS.ANARAMP8', 'read-write',
            u"",
            0x18C5AD4A, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT48 = RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT48(self)
        self.zz_fdict['ANARAMPLUT48'] = self.ANARAMPLUT48
        self.ANARAMPLUT49 = RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT49(self)
        self.zz_fdict['ANARAMPLUT49'] = self.ANARAMPLUT49
        self.ANARAMPLUT50 = RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT50(self)
        self.zz_fdict['ANARAMPLUT50'] = self.ANARAMPLUT50
        self.ANARAMPLUT51 = RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT51(self)
        self.zz_fdict['ANARAMPLUT51'] = self.ANARAMPLUT51
        self.ANARAMPLUT52 = RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT52(self)
        self.zz_fdict['ANARAMPLUT52'] = self.ANARAMPLUT52
        self.ANARAMPLUT53 = RM_Field_MODEM_NS_ANARAMP8_ANARAMPLUT53(self)
        self.zz_fdict['ANARAMPLUT53'] = self.ANARAMPLUT53
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP9, self).__init__(rmio, label,
            0xb8014000, 0x108,
            'ANARAMP9', 'MODEM_NS.ANARAMP9', 'read-write',
            u"",
            0x2307B9AD, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT54 = RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT54(self)
        self.zz_fdict['ANARAMPLUT54'] = self.ANARAMPLUT54
        self.ANARAMPLUT55 = RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT55(self)
        self.zz_fdict['ANARAMPLUT55'] = self.ANARAMPLUT55
        self.ANARAMPLUT56 = RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT56(self)
        self.zz_fdict['ANARAMPLUT56'] = self.ANARAMPLUT56
        self.ANARAMPLUT57 = RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT57(self)
        self.zz_fdict['ANARAMPLUT57'] = self.ANARAMPLUT57
        self.ANARAMPLUT58 = RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT58(self)
        self.zz_fdict['ANARAMPLUT58'] = self.ANARAMPLUT58
        self.ANARAMPLUT59 = RM_Field_MODEM_NS_ANARAMP9_ANARAMPLUT59(self)
        self.zz_fdict['ANARAMPLUT59'] = self.ANARAMPLUT59
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANARAMP10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANARAMP10, self).__init__(rmio, label,
            0xb8014000, 0x10C,
            'ANARAMP10', 'MODEM_NS.ANARAMP10', 'read-write',
            u"",
            0x000FF2F3, 0x000FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANARAMPLUT60 = RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT60(self)
        self.zz_fdict['ANARAMPLUT60'] = self.ANARAMPLUT60
        self.ANARAMPLUT61 = RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT61(self)
        self.zz_fdict['ANARAMPLUT61'] = self.ANARAMPLUT61
        self.ANARAMPLUT62 = RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT62(self)
        self.zz_fdict['ANARAMPLUT62'] = self.ANARAMPLUT62
        self.ANARAMPLUT63 = RM_Field_MODEM_NS_ANARAMP10_ANARAMPLUT63(self)
        self.zz_fdict['ANARAMPLUT63'] = self.ANARAMPLUT63
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_INTAFC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_INTAFC, self).__init__(rmio, label,
            0xb8014000, 0x120,
            'INTAFC', 'MODEM_NS.INTAFC', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FOEPREAVG0 = RM_Field_MODEM_NS_INTAFC_FOEPREAVG0(self)
        self.zz_fdict['FOEPREAVG0'] = self.FOEPREAVG0
        self.FOEPREAVG1 = RM_Field_MODEM_NS_INTAFC_FOEPREAVG1(self)
        self.zz_fdict['FOEPREAVG1'] = self.FOEPREAVG1
        self.FOEPREAVG2 = RM_Field_MODEM_NS_INTAFC_FOEPREAVG2(self)
        self.zz_fdict['FOEPREAVG2'] = self.FOEPREAVG2
        self.FOEPREAVG3 = RM_Field_MODEM_NS_INTAFC_FOEPREAVG3(self)
        self.zz_fdict['FOEPREAVG3'] = self.FOEPREAVG3
        self.FOEPREAVG4 = RM_Field_MODEM_NS_INTAFC_FOEPREAVG4(self)
        self.zz_fdict['FOEPREAVG4'] = self.FOEPREAVG4
        self.FOEPREAVG5 = RM_Field_MODEM_NS_INTAFC_FOEPREAVG5(self)
        self.zz_fdict['FOEPREAVG5'] = self.FOEPREAVG5
        self.FOEPREAVG6 = RM_Field_MODEM_NS_INTAFC_FOEPREAVG6(self)
        self.zz_fdict['FOEPREAVG6'] = self.FOEPREAVG6
        self.FOEPREAVG7 = RM_Field_MODEM_NS_INTAFC_FOEPREAVG7(self)
        self.zz_fdict['FOEPREAVG7'] = self.FOEPREAVG7
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD0, self).__init__(rmio, label,
            0xb8014000, 0x124,
            'DSATHD0', 'MODEM_NS.DSATHD0', 'read-write',
            u"",
            0x07830464, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SPIKETHD = RM_Field_MODEM_NS_DSATHD0_SPIKETHD(self)
        self.zz_fdict['SPIKETHD'] = self.SPIKETHD
        self.UNMODTHD = RM_Field_MODEM_NS_DSATHD0_UNMODTHD(self)
        self.zz_fdict['UNMODTHD'] = self.UNMODTHD
        self.FDEVMINTHD = RM_Field_MODEM_NS_DSATHD0_FDEVMINTHD(self)
        self.zz_fdict['FDEVMINTHD'] = self.FDEVMINTHD
        self.FDEVMAXTHD = RM_Field_MODEM_NS_DSATHD0_FDEVMAXTHD(self)
        self.zz_fdict['FDEVMAXTHD'] = self.FDEVMAXTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD1, self).__init__(rmio, label,
            0xb8014000, 0x128,
            'DSATHD1', 'MODEM_NS.DSATHD1', 'read-write',
            u"",
            0x3AC81388, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POWABSTHD = RM_Field_MODEM_NS_DSATHD1_POWABSTHD(self)
        self.zz_fdict['POWABSTHD'] = self.POWABSTHD
        self.POWRELTHD = RM_Field_MODEM_NS_DSATHD1_POWRELTHD(self)
        self.zz_fdict['POWRELTHD'] = self.POWRELTHD
        self.DSARSTCNT = RM_Field_MODEM_NS_DSATHD1_DSARSTCNT(self)
        self.zz_fdict['DSARSTCNT'] = self.DSARSTCNT
        self.RSSIJMPTHD = RM_Field_MODEM_NS_DSATHD1_RSSIJMPTHD(self)
        self.zz_fdict['RSSIJMPTHD'] = self.RSSIJMPTHD
        self.FREQLATDLY = RM_Field_MODEM_NS_DSATHD1_FREQLATDLY(self)
        self.zz_fdict['FREQLATDLY'] = self.FREQLATDLY
        self.PWRFLTBYP = RM_Field_MODEM_NS_DSATHD1_PWRFLTBYP(self)
        self.zz_fdict['PWRFLTBYP'] = self.PWRFLTBYP
        self.AMPFLTBYP = RM_Field_MODEM_NS_DSATHD1_AMPFLTBYP(self)
        self.zz_fdict['AMPFLTBYP'] = self.AMPFLTBYP
        self.PWRDETDIS = RM_Field_MODEM_NS_DSATHD1_PWRDETDIS(self)
        self.zz_fdict['PWRDETDIS'] = self.PWRDETDIS
        self.FREQSCALE = RM_Field_MODEM_NS_DSATHD1_FREQSCALE(self)
        self.zz_fdict['FREQSCALE'] = self.FREQSCALE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD2, self).__init__(rmio, label,
            0xb8014000, 0x12C,
            'DSATHD2', 'MODEM_NS.DSATHD2', 'read-write',
            u"",
            0x0C660664, 0x7FFFFEFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POWABSTHDLOG = RM_Field_MODEM_NS_DSATHD2_POWABSTHDLOG(self)
        self.zz_fdict['POWABSTHDLOG'] = self.POWABSTHDLOG
        self.JUMPDETEN = RM_Field_MODEM_NS_DSATHD2_JUMPDETEN(self)
        self.zz_fdict['JUMPDETEN'] = self.JUMPDETEN
        self.FDADJTHD = RM_Field_MODEM_NS_DSATHD2_FDADJTHD(self)
        self.zz_fdict['FDADJTHD'] = self.FDADJTHD
        self.PMDETPASSTHD = RM_Field_MODEM_NS_DSATHD2_PMDETPASSTHD(self)
        self.zz_fdict['PMDETPASSTHD'] = self.PMDETPASSTHD
        self.FREQESTTHD = RM_Field_MODEM_NS_DSATHD2_FREQESTTHD(self)
        self.zz_fdict['FREQESTTHD'] = self.FREQESTTHD
        self.INTERFERDET = RM_Field_MODEM_NS_DSATHD2_INTERFERDET(self)
        self.zz_fdict['INTERFERDET'] = self.INTERFERDET
        self.PMDETFORCE = RM_Field_MODEM_NS_DSATHD2_PMDETFORCE(self)
        self.zz_fdict['PMDETFORCE'] = self.PMDETFORCE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD3, self).__init__(rmio, label,
            0xb8014000, 0x130,
            'DSATHD3', 'MODEM_NS.DSATHD3', 'read-write',
            u"",
            0x07830464, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SPIKETHDLO = RM_Field_MODEM_NS_DSATHD3_SPIKETHDLO(self)
        self.zz_fdict['SPIKETHDLO'] = self.SPIKETHDLO
        self.UNMODTHDLO = RM_Field_MODEM_NS_DSATHD3_UNMODTHDLO(self)
        self.zz_fdict['UNMODTHDLO'] = self.UNMODTHDLO
        self.FDEVMINTHDLO = RM_Field_MODEM_NS_DSATHD3_FDEVMINTHDLO(self)
        self.zz_fdict['FDEVMINTHDLO'] = self.FDEVMINTHDLO
        self.FDEVMAXTHDLO = RM_Field_MODEM_NS_DSATHD3_FDEVMAXTHDLO(self)
        self.zz_fdict['FDEVMAXTHDLO'] = self.FDEVMAXTHDLO
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD4, self).__init__(rmio, label,
            0xb8014000, 0x134,
            'DSATHD4', 'MODEM_NS.DSATHD4', 'read-write',
            u"",
            0x00821388, 0x07FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POWABSTHDLO = RM_Field_MODEM_NS_DSATHD4_POWABSTHDLO(self)
        self.zz_fdict['POWABSTHDLO'] = self.POWABSTHDLO
        self.ARRTOLERTHD0LO = RM_Field_MODEM_NS_DSATHD4_ARRTOLERTHD0LO(self)
        self.zz_fdict['ARRTOLERTHD0LO'] = self.ARRTOLERTHD0LO
        self.ARRTOLERTHD1LO = RM_Field_MODEM_NS_DSATHD4_ARRTOLERTHD1LO(self)
        self.zz_fdict['ARRTOLERTHD1LO'] = self.ARRTOLERTHD1LO
        self.SWTHD = RM_Field_MODEM_NS_DSATHD4_SWTHD(self)
        self.zz_fdict['SWTHD'] = self.SWTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSACTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSACTRL, self).__init__(rmio, label,
            0xb8014000, 0x138,
            'DSACTRL', 'MODEM_NS.DSACTRL', 'read-write',
            u"",
            0x000A2090, 0xFFEFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DSAMODE = RM_Field_MODEM_NS_DSACTRL_DSAMODE(self)
        self.zz_fdict['DSAMODE'] = self.DSAMODE
        self.ARRTHD = RM_Field_MODEM_NS_DSACTRL_ARRTHD(self)
        self.zz_fdict['ARRTHD'] = self.ARRTHD
        self.ARRTOLERTHD0 = RM_Field_MODEM_NS_DSACTRL_ARRTOLERTHD0(self)
        self.zz_fdict['ARRTOLERTHD0'] = self.ARRTOLERTHD0
        self.ARRTOLERTHD1 = RM_Field_MODEM_NS_DSACTRL_ARRTOLERTHD1(self)
        self.zz_fdict['ARRTOLERTHD1'] = self.ARRTOLERTHD1
        self.SCHPRD = RM_Field_MODEM_NS_DSACTRL_SCHPRD(self)
        self.zz_fdict['SCHPRD'] = self.SCHPRD
        self.FREQAVGSYM = RM_Field_MODEM_NS_DSACTRL_FREQAVGSYM(self)
        self.zz_fdict['FREQAVGSYM'] = self.FREQAVGSYM
        self.TRANRSTDSA = RM_Field_MODEM_NS_DSACTRL_TRANRSTDSA(self)
        self.zz_fdict['TRANRSTDSA'] = self.TRANRSTDSA
        self.DSARSTON = RM_Field_MODEM_NS_DSACTRL_DSARSTON(self)
        self.zz_fdict['DSARSTON'] = self.DSARSTON
        self.GAINREDUCDLY = RM_Field_MODEM_NS_DSACTRL_GAINREDUCDLY(self)
        self.zz_fdict['GAINREDUCDLY'] = self.GAINREDUCDLY
        self.LOWDUTY = RM_Field_MODEM_NS_DSACTRL_LOWDUTY(self)
        self.zz_fdict['LOWDUTY'] = self.LOWDUTY
        self.RESTORE = RM_Field_MODEM_NS_DSACTRL_RESTORE(self)
        self.zz_fdict['RESTORE'] = self.RESTORE
        self.AGCBAUDEN = RM_Field_MODEM_NS_DSACTRL_AGCBAUDEN(self)
        self.zz_fdict['AGCBAUDEN'] = self.AGCBAUDEN
        self.AMPJUPTHD = RM_Field_MODEM_NS_DSACTRL_AMPJUPTHD(self)
        self.zz_fdict['AMPJUPTHD'] = self.AMPJUPTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VITERBIDEMOD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VITERBIDEMOD, self).__init__(rmio, label,
            0xb8014000, 0x140,
            'VITERBIDEMOD', 'MODEM_NS.VITERBIDEMOD', 'read-write',
            u"",
            0x00206100, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VTDEMODEN = RM_Field_MODEM_NS_VITERBIDEMOD_VTDEMODEN(self)
        self.zz_fdict['VTDEMODEN'] = self.VTDEMODEN
        self.HARDDECISION = RM_Field_MODEM_NS_VITERBIDEMOD_HARDDECISION(self)
        self.zz_fdict['HARDDECISION'] = self.HARDDECISION
        self.VITERBIKSI1 = RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI1(self)
        self.zz_fdict['VITERBIKSI1'] = self.VITERBIKSI1
        self.VITERBIKSI2 = RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI2(self)
        self.zz_fdict['VITERBIKSI2'] = self.VITERBIKSI2
        self.VITERBIKSI3 = RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI3(self)
        self.zz_fdict['VITERBIKSI3'] = self.VITERBIKSI3
        self.SYNTHAFC = RM_Field_MODEM_NS_VITERBIDEMOD_SYNTHAFC(self)
        self.zz_fdict['SYNTHAFC'] = self.SYNTHAFC
        self.CORRCYCLE = RM_Field_MODEM_NS_VITERBIDEMOD_CORRCYCLE(self)
        self.zz_fdict['CORRCYCLE'] = self.CORRCYCLE
        self.CORRSTPSIZE = RM_Field_MODEM_NS_VITERBIDEMOD_CORRSTPSIZE(self)
        self.zz_fdict['CORRSTPSIZE'] = self.CORRSTPSIZE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VTCORRCFG0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VTCORRCFG0, self).__init__(rmio, label,
            0xb8014000, 0x144,
            'VTCORRCFG0', 'MODEM_NS.VTCORRCFG0', 'read-write',
            u"",
            0x123556B7, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.EXPECTPATT = RM_Field_MODEM_NS_VTCORRCFG0_EXPECTPATT(self)
        self.zz_fdict['EXPECTPATT'] = self.EXPECTPATT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VTCORRCFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VTCORRCFG1, self).__init__(rmio, label,
            0xb8014000, 0x148,
            'VTCORRCFG1', 'MODEM_NS.VTCORRCFG1', 'read-write',
            u"",
            0x5020C000, 0xF7FDFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VITERBIKSI3WB = RM_Field_MODEM_NS_VTCORRCFG1_VITERBIKSI3WB(self)
        self.zz_fdict['VITERBIKSI3WB'] = self.VITERBIKSI3WB
        self.KSI3SWENABLE = RM_Field_MODEM_NS_VTCORRCFG1_KSI3SWENABLE(self)
        self.zz_fdict['KSI3SWENABLE'] = self.KSI3SWENABLE
        self.VTFRQLIM = RM_Field_MODEM_NS_VTCORRCFG1_VTFRQLIM(self)
        self.zz_fdict['VTFRQLIM'] = self.VTFRQLIM
        self.EXPSYNCLEN = RM_Field_MODEM_NS_VTCORRCFG1_EXPSYNCLEN(self)
        self.zz_fdict['EXPSYNCLEN'] = self.EXPSYNCLEN
        self.EXPECTHT = RM_Field_MODEM_NS_VTCORRCFG1_EXPECTHT(self)
        self.zz_fdict['EXPECTHT'] = self.EXPECTHT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VTTRACK(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VTTRACK, self).__init__(rmio, label,
            0xb8014000, 0x14C,
            'VTTRACK', 'MODEM_NS.VTTRACK', 'read-write',
            u"",
            0x0D803B88, 0x3FFF3FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FREQTRACKMODE = RM_Field_MODEM_NS_VTTRACK_FREQTRACKMODE(self)
        self.zz_fdict['FREQTRACKMODE'] = self.FREQTRACKMODE
        self.TIMTRACKTHD = RM_Field_MODEM_NS_VTTRACK_TIMTRACKTHD(self)
        self.zz_fdict['TIMTRACKTHD'] = self.TIMTRACKTHD
        self.TIMEACQUTHD = RM_Field_MODEM_NS_VTTRACK_TIMEACQUTHD(self)
        self.zz_fdict['TIMEACQUTHD'] = self.TIMEACQUTHD
        self.TIMGEAR = RM_Field_MODEM_NS_VTTRACK_TIMGEAR(self)
        self.zz_fdict['TIMGEAR'] = self.TIMGEAR
        self.FREQBIAS = RM_Field_MODEM_NS_VTTRACK_FREQBIAS(self)
        self.zz_fdict['FREQBIAS'] = self.FREQBIAS
        self.HIPWRTHD = RM_Field_MODEM_NS_VTTRACK_HIPWRTHD(self)
        self.zz_fdict['HIPWRTHD'] = self.HIPWRTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VTBLETIMING(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VTBLETIMING, self).__init__(rmio, label,
            0xb8014000, 0x150,
            'VTBLETIMING', 'MODEM_NS.VTBLETIMING', 'read-write',
            u"",
            0x00000000, 0x8000FFF7,
            0x00001000, 0x00002000,
            0x00003000)

        self.VTBLETIMINGSEL = RM_Field_MODEM_NS_VTBLETIMING_VTBLETIMINGSEL(self)
        self.zz_fdict['VTBLETIMINGSEL'] = self.VTBLETIMINGSEL
        self.VTBLETIMINGCLKSEL = RM_Field_MODEM_NS_VTBLETIMING_VTBLETIMINGCLKSEL(self)
        self.zz_fdict['VTBLETIMINGCLKSEL'] = self.VTBLETIMINGCLKSEL
        self.TIMINGDELAY = RM_Field_MODEM_NS_VTBLETIMING_TIMINGDELAY(self)
        self.zz_fdict['TIMINGDELAY'] = self.TIMINGDELAY
        self.FLENOFF = RM_Field_MODEM_NS_VTBLETIMING_FLENOFF(self)
        self.zz_fdict['FLENOFF'] = self.FLENOFF
        self.DISDEMODOF = RM_Field_MODEM_NS_VTBLETIMING_DISDEMODOF(self)
        self.zz_fdict['DISDEMODOF'] = self.DISDEMODOF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BREST(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BREST, self).__init__(rmio, label,
            0xb8014000, 0x154,
            'BREST', 'MODEM_NS.BREST', 'read-only',
            u"",
            0x00000000, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BRESTINT = RM_Field_MODEM_NS_BREST_BRESTINT(self)
        self.zz_fdict['BRESTINT'] = self.BRESTINT
        self.BRESTNUM = RM_Field_MODEM_NS_BREST_BRESTNUM(self)
        self.zz_fdict['BRESTNUM'] = self.BRESTNUM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AUTOCG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AUTOCG, self).__init__(rmio, label,
            0xb8014000, 0x158,
            'AUTOCG', 'MODEM_NS.AUTOCG', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUTOCGEN = RM_Field_MODEM_NS_AUTOCG_AUTOCGEN(self)
        self.zz_fdict['AUTOCGEN'] = self.AUTOCGEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CGCLKSTOP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CGCLKSTOP, self).__init__(rmio, label,
            0xb8014000, 0x15C,
            'CGCLKSTOP', 'MODEM_NS.CGCLKSTOP', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FORCEOFF = RM_Field_MODEM_NS_CGCLKSTOP_FORCEOFF(self)
        self.zz_fdict['FORCEOFF'] = self.FORCEOFF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_POE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_POE, self).__init__(rmio, label,
            0xb8014000, 0x160,
            'POE', 'MODEM_NS.POE', 'read-only',
            u"",
            0x00000000, 0x03FF03FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POEI = RM_Field_MODEM_NS_POE_POEI(self)
        self.zz_fdict['POEI'] = self.POEI
        self.POEQ = RM_Field_MODEM_NS_POE_POEQ(self)
        self.zz_fdict['POEQ'] = self.POEQ
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DIRECTMODE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DIRECTMODE, self).__init__(rmio, label,
            0xb8014000, 0x164,
            'DIRECTMODE', 'MODEM_NS.DIRECTMODE', 'read-write',
            u"",
            0x0000010C, 0x00001F0F,
            0x00001000, 0x00002000,
            0x00003000)

        self.DMENABLE = RM_Field_MODEM_NS_DIRECTMODE_DMENABLE(self)
        self.zz_fdict['DMENABLE'] = self.DMENABLE
        self.SYNCASYNC = RM_Field_MODEM_NS_DIRECTMODE_SYNCASYNC(self)
        self.zz_fdict['SYNCASYNC'] = self.SYNCASYNC
        self.SYNCPREAM = RM_Field_MODEM_NS_DIRECTMODE_SYNCPREAM(self)
        self.zz_fdict['SYNCPREAM'] = self.SYNCPREAM
        self.CLKWIDTH = RM_Field_MODEM_NS_DIRECTMODE_CLKWIDTH(self)
        self.zz_fdict['CLKWIDTH'] = self.CLKWIDTH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE, self).__init__(rmio, label,
            0xb8014000, 0x168,
            'LONGRANGE', 'MODEM_NS.LONGRANGE', 'read-write',
            u"",
            0x00FA53E8, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCORRTHD = RM_Field_MODEM_NS_LONGRANGE_LRCORRTHD(self)
        self.zz_fdict['LRCORRTHD'] = self.LRCORRTHD
        self.LRCORRSCHWIN = RM_Field_MODEM_NS_LONGRANGE_LRCORRSCHWIN(self)
        self.zz_fdict['LRCORRSCHWIN'] = self.LRCORRSCHWIN
        self.LRBLE = RM_Field_MODEM_NS_LONGRANGE_LRBLE(self)
        self.zz_fdict['LRBLE'] = self.LRBLE
        self.LRTIMCORRTHD = RM_Field_MODEM_NS_LONGRANGE_LRTIMCORRTHD(self)
        self.zz_fdict['LRTIMCORRTHD'] = self.LRTIMCORRTHD
        self.LRBLEDSA = RM_Field_MODEM_NS_LONGRANGE_LRBLEDSA(self)
        self.zz_fdict['LRBLEDSA'] = self.LRBLEDSA
        self.LRDEC = RM_Field_MODEM_NS_LONGRANGE_LRDEC(self)
        self.zz_fdict['LRDEC'] = self.LRDEC
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE1, self).__init__(rmio, label,
            0xb8014000, 0x16C,
            'LONGRANGE1', 'MODEM_NS.LONGRANGE1', 'read-write',
            u"",
            0x40000000, 0xFFFF7FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRSS = RM_Field_MODEM_NS_LONGRANGE1_LRSS(self)
        self.zz_fdict['LRSS'] = self.LRSS
        self.LRTIMEOUTTHD = RM_Field_MODEM_NS_LONGRANGE1_LRTIMEOUTTHD(self)
        self.zz_fdict['LRTIMEOUTTHD'] = self.LRTIMEOUTTHD
        self.CHPWRACCUDEL = RM_Field_MODEM_NS_LONGRANGE1_CHPWRACCUDEL(self)
        self.zz_fdict['CHPWRACCUDEL'] = self.CHPWRACCUDEL
        self.HYSVAL = RM_Field_MODEM_NS_LONGRANGE1_HYSVAL(self)
        self.zz_fdict['HYSVAL'] = self.HYSVAL
        self.AVGWIN = RM_Field_MODEM_NS_LONGRANGE1_AVGWIN(self)
        self.zz_fdict['AVGWIN'] = self.AVGWIN
        self.LRSPIKETHADD = RM_Field_MODEM_NS_LONGRANGE1_LRSPIKETHADD(self)
        self.zz_fdict['LRSPIKETHADD'] = self.LRSPIKETHADD
        self.LOGICBASEDPUGATE = RM_Field_MODEM_NS_LONGRANGE1_LOGICBASEDPUGATE(self)
        self.zz_fdict['LOGICBASEDPUGATE'] = self.LOGICBASEDPUGATE
        self.LOGICBASEDLRDEMODGATE = RM_Field_MODEM_NS_LONGRANGE1_LOGICBASEDLRDEMODGATE(self)
        self.zz_fdict['LOGICBASEDLRDEMODGATE'] = self.LOGICBASEDLRDEMODGATE
        self.PREFILTLEN = RM_Field_MODEM_NS_LONGRANGE1_PREFILTLEN(self)
        self.zz_fdict['PREFILTLEN'] = self.PREFILTLEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE2, self).__init__(rmio, label,
            0xb8014000, 0x170,
            'LONGRANGE2', 'MODEM_NS.LONGRANGE2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRTH1 = RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH1(self)
        self.zz_fdict['LRCHPWRTH1'] = self.LRCHPWRTH1
        self.LRCHPWRTH2 = RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH2(self)
        self.zz_fdict['LRCHPWRTH2'] = self.LRCHPWRTH2
        self.LRCHPWRTH3 = RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH3(self)
        self.zz_fdict['LRCHPWRTH3'] = self.LRCHPWRTH3
        self.LRCHPWRTH4 = RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH4(self)
        self.zz_fdict['LRCHPWRTH4'] = self.LRCHPWRTH4
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE3, self).__init__(rmio, label,
            0xb8014000, 0x174,
            'LONGRANGE3', 'MODEM_NS.LONGRANGE3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRTH5 = RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH5(self)
        self.zz_fdict['LRCHPWRTH5'] = self.LRCHPWRTH5
        self.LRCHPWRTH6 = RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH6(self)
        self.zz_fdict['LRCHPWRTH6'] = self.LRCHPWRTH6
        self.LRCHPWRTH7 = RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH7(self)
        self.zz_fdict['LRCHPWRTH7'] = self.LRCHPWRTH7
        self.LRCHPWRTH8 = RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH8(self)
        self.zz_fdict['LRCHPWRTH8'] = self.LRCHPWRTH8
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE4, self).__init__(rmio, label,
            0xb8014000, 0x178,
            'LONGRANGE4', 'MODEM_NS.LONGRANGE4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRTH9 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRTH9(self)
        self.zz_fdict['LRCHPWRTH9'] = self.LRCHPWRTH9
        self.LRCHPWRTH10 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRTH10(self)
        self.zz_fdict['LRCHPWRTH10'] = self.LRCHPWRTH10
        self.LRCHPWRSH1 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH1(self)
        self.zz_fdict['LRCHPWRSH1'] = self.LRCHPWRSH1
        self.LRCHPWRSH2 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH2(self)
        self.zz_fdict['LRCHPWRSH2'] = self.LRCHPWRSH2
        self.LRCHPWRSH3 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH3(self)
        self.zz_fdict['LRCHPWRSH3'] = self.LRCHPWRSH3
        self.LRCHPWRSH4 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH4(self)
        self.zz_fdict['LRCHPWRSH4'] = self.LRCHPWRSH4
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE5, self).__init__(rmio, label,
            0xb8014000, 0x17C,
            'LONGRANGE5', 'MODEM_NS.LONGRANGE5', 'read-write',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRSH5 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH5(self)
        self.zz_fdict['LRCHPWRSH5'] = self.LRCHPWRSH5
        self.LRCHPWRSH6 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH6(self)
        self.zz_fdict['LRCHPWRSH6'] = self.LRCHPWRSH6
        self.LRCHPWRSH7 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH7(self)
        self.zz_fdict['LRCHPWRSH7'] = self.LRCHPWRSH7
        self.LRCHPWRSH8 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH8(self)
        self.zz_fdict['LRCHPWRSH8'] = self.LRCHPWRSH8
        self.LRCHPWRSH9 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH9(self)
        self.zz_fdict['LRCHPWRSH9'] = self.LRCHPWRSH9
        self.LRCHPWRSH10 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH10(self)
        self.zz_fdict['LRCHPWRSH10'] = self.LRCHPWRSH10
        self.LRCHPWRSH11 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH11(self)
        self.zz_fdict['LRCHPWRSH11'] = self.LRCHPWRSH11
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE6, self).__init__(rmio, label,
            0xb8014000, 0x180,
            'LONGRANGE6', 'MODEM_NS.LONGRANGE6', 'read-write',
            u"",
            0x00000000, 0xFFF7FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRSPIKETH = RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRSPIKETH(self)
        self.zz_fdict['LRCHPWRSPIKETH'] = self.LRCHPWRSPIKETH
        self.LRSPIKETHD = RM_Field_MODEM_NS_LONGRANGE6_LRSPIKETHD(self)
        self.zz_fdict['LRSPIKETHD'] = self.LRSPIKETHD
        self.LRCHPWRTH11 = RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRTH11(self)
        self.zz_fdict['LRCHPWRTH11'] = self.LRCHPWRTH11
        self.LRCHPWRSH12 = RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRSH12(self)
        self.zz_fdict['LRCHPWRSH12'] = self.LRCHPWRSH12
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LRFRC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LRFRC, self).__init__(rmio, label,
            0xb8014000, 0x184,
            'LRFRC', 'MODEM_NS.LRFRC', 'read-write',
            u"",
            0x00000101, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CI500 = RM_Field_MODEM_NS_LRFRC_CI500(self)
        self.zz_fdict['CI500'] = self.CI500
        self.FRCACKTIMETHD = RM_Field_MODEM_NS_LRFRC_FRCACKTIMETHD(self)
        self.zz_fdict['FRCACKTIMETHD'] = self.FRCACKTIMETHD
        self.LRCORRMODE = RM_Field_MODEM_NS_LRFRC_LRCORRMODE(self)
        self.zz_fdict['LRCORRMODE'] = self.LRCORRMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_COH0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_COH0, self).__init__(rmio, label,
            0xb8014000, 0x188,
            'COH0', 'MODEM_NS.COH0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COHDYNAMICBBSSEN = RM_Field_MODEM_NS_COH0_COHDYNAMICBBSSEN(self)
        self.zz_fdict['COHDYNAMICBBSSEN'] = self.COHDYNAMICBBSSEN
        self.COHDYNAMICSYNCTHRESH = RM_Field_MODEM_NS_COH0_COHDYNAMICSYNCTHRESH(self)
        self.zz_fdict['COHDYNAMICSYNCTHRESH'] = self.COHDYNAMICSYNCTHRESH
        self.COHDYNAMICPRETHRESH = RM_Field_MODEM_NS_COH0_COHDYNAMICPRETHRESH(self)
        self.zz_fdict['COHDYNAMICPRETHRESH'] = self.COHDYNAMICPRETHRESH
        self.COHCHPWRLOCK = RM_Field_MODEM_NS_COH0_COHCHPWRLOCK(self)
        self.zz_fdict['COHCHPWRLOCK'] = self.COHCHPWRLOCK
        self.COHCHPWRRESTART = RM_Field_MODEM_NS_COH0_COHCHPWRRESTART(self)
        self.zz_fdict['COHCHPWRRESTART'] = self.COHCHPWRRESTART
        self.COHDYNAMICPRETHRESHSEL = RM_Field_MODEM_NS_COH0_COHDYNAMICPRETHRESHSEL(self)
        self.zz_fdict['COHDYNAMICPRETHRESHSEL'] = self.COHDYNAMICPRETHRESHSEL
        self.COHCHPWRTH0 = RM_Field_MODEM_NS_COH0_COHCHPWRTH0(self)
        self.zz_fdict['COHCHPWRTH0'] = self.COHCHPWRTH0
        self.COHCHPWRTH1 = RM_Field_MODEM_NS_COH0_COHCHPWRTH1(self)
        self.zz_fdict['COHCHPWRTH1'] = self.COHCHPWRTH1
        self.COHCHPWRTH2 = RM_Field_MODEM_NS_COH0_COHCHPWRTH2(self)
        self.zz_fdict['COHCHPWRTH2'] = self.COHCHPWRTH2
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_COH1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_COH1, self).__init__(rmio, label,
            0xb8014000, 0x18C,
            'COH1', 'MODEM_NS.COH1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNCTHRESH0 = RM_Field_MODEM_NS_COH1_SYNCTHRESH0(self)
        self.zz_fdict['SYNCTHRESH0'] = self.SYNCTHRESH0
        self.SYNCTHRESH1 = RM_Field_MODEM_NS_COH1_SYNCTHRESH1(self)
        self.zz_fdict['SYNCTHRESH1'] = self.SYNCTHRESH1
        self.SYNCTHRESH2 = RM_Field_MODEM_NS_COH1_SYNCTHRESH2(self)
        self.zz_fdict['SYNCTHRESH2'] = self.SYNCTHRESH2
        self.SYNCTHRESH3 = RM_Field_MODEM_NS_COH1_SYNCTHRESH3(self)
        self.zz_fdict['SYNCTHRESH3'] = self.SYNCTHRESH3
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_COH2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_COH2, self).__init__(rmio, label,
            0xb8014000, 0x190,
            'COH2', 'MODEM_NS.COH2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNCTHRESHDELTA0 = RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA0(self)
        self.zz_fdict['SYNCTHRESHDELTA0'] = self.SYNCTHRESHDELTA0
        self.SYNCTHRESHDELTA1 = RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA1(self)
        self.zz_fdict['SYNCTHRESHDELTA1'] = self.SYNCTHRESHDELTA1
        self.SYNCTHRESHDELTA2 = RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA2(self)
        self.zz_fdict['SYNCTHRESHDELTA2'] = self.SYNCTHRESHDELTA2
        self.SYNCTHRESHDELTA3 = RM_Field_MODEM_NS_COH2_SYNCTHRESHDELTA3(self)
        self.zz_fdict['SYNCTHRESHDELTA3'] = self.SYNCTHRESHDELTA3
        self.DSAPEAKCHPWRTH = RM_Field_MODEM_NS_COH2_DSAPEAKCHPWRTH(self)
        self.zz_fdict['DSAPEAKCHPWRTH'] = self.DSAPEAKCHPWRTH
        self.FIXEDCDTHFORIIR = RM_Field_MODEM_NS_COH2_FIXEDCDTHFORIIR(self)
        self.zz_fdict['FIXEDCDTHFORIIR'] = self.FIXEDCDTHFORIIR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_COH3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_COH3, self).__init__(rmio, label,
            0xb8014000, 0x194,
            'COH3', 'MODEM_NS.COH3', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COHDSAEN = RM_Field_MODEM_NS_COH3_COHDSAEN(self)
        self.zz_fdict['COHDSAEN'] = self.COHDSAEN
        self.COHDSAADDWNDSIZE = RM_Field_MODEM_NS_COH3_COHDSAADDWNDSIZE(self)
        self.zz_fdict['COHDSAADDWNDSIZE'] = self.COHDSAADDWNDSIZE
        self.CDSS = RM_Field_MODEM_NS_COH3_CDSS(self)
        self.zz_fdict['CDSS'] = self.CDSS
        self.DSAPEAKCHKEN = RM_Field_MODEM_NS_COH3_DSAPEAKCHKEN(self)
        self.zz_fdict['DSAPEAKCHKEN'] = self.DSAPEAKCHKEN
        self.DSAPEAKINDLEN = RM_Field_MODEM_NS_COH3_DSAPEAKINDLEN(self)
        self.zz_fdict['DSAPEAKINDLEN'] = self.DSAPEAKINDLEN
        self.DSAPEAKCHPWREN = RM_Field_MODEM_NS_COH3_DSAPEAKCHPWREN(self)
        self.zz_fdict['DSAPEAKCHPWREN'] = self.DSAPEAKCHPWREN
        self.LOGICBASEDCOHDEMODGATE = RM_Field_MODEM_NS_COH3_LOGICBASEDCOHDEMODGATE(self)
        self.zz_fdict['LOGICBASEDCOHDEMODGATE'] = self.LOGICBASEDCOHDEMODGATE
        self.DYNIIRCOEFOPTION = RM_Field_MODEM_NS_COH3_DYNIIRCOEFOPTION(self)
        self.zz_fdict['DYNIIRCOEFOPTION'] = self.DYNIIRCOEFOPTION
        self.ONEPEAKQUALEN = RM_Field_MODEM_NS_COH3_ONEPEAKQUALEN(self)
        self.zz_fdict['ONEPEAKQUALEN'] = self.ONEPEAKQUALEN
        self.PEAKCHKTIMOUT = RM_Field_MODEM_NS_COH3_PEAKCHKTIMOUT(self)
        self.zz_fdict['PEAKCHKTIMOUT'] = self.PEAKCHKTIMOUT
        self.COHDSADETDIS = RM_Field_MODEM_NS_COH3_COHDSADETDIS(self)
        self.zz_fdict['COHDSADETDIS'] = self.COHDSADETDIS
        self.COHDSACMPLX = RM_Field_MODEM_NS_COH3_COHDSACMPLX(self)
        self.zz_fdict['COHDSACMPLX'] = self.COHDSACMPLX
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CMD, self).__init__(rmio, label,
            0xb8014000, 0x198,
            'CMD', 'MODEM_NS.CMD', 'write-only',
            u"",
            0x00000000, 0x0000003B,
            0x00001000, 0x00002000,
            0x00003000)

        self.PRESTOP = RM_Field_MODEM_NS_CMD_PRESTOP(self)
        self.zz_fdict['PRESTOP'] = self.PRESTOP
        self.CHPWRACCUCLR = RM_Field_MODEM_NS_CMD_CHPWRACCUCLR(self)
        self.zz_fdict['CHPWRACCUCLR'] = self.CHPWRACCUCLR
        self.AFCTXLOCK = RM_Field_MODEM_NS_CMD_AFCTXLOCK(self)
        self.zz_fdict['AFCTXLOCK'] = self.AFCTXLOCK
        self.AFCTXCLEAR = RM_Field_MODEM_NS_CMD_AFCTXCLEAR(self)
        self.zz_fdict['AFCTXCLEAR'] = self.AFCTXCLEAR
        self.AFCRXCLEAR = RM_Field_MODEM_NS_CMD_AFCRXCLEAR(self)
        self.zz_fdict['AFCRXCLEAR'] = self.AFCRXCLEAR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYNCPROPERTIES(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYNCPROPERTIES, self).__init__(rmio, label,
            0xb8014000, 0x1A4,
            'SYNCPROPERTIES', 'MODEM_NS.SYNCPROPERTIES', 'read-write',
            u"",
            0x00000000, 0x0001FF00,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATICSYNCTHRESHEN = RM_Field_MODEM_NS_SYNCPROPERTIES_STATICSYNCTHRESHEN(self)
        self.zz_fdict['STATICSYNCTHRESHEN'] = self.STATICSYNCTHRESHEN
        self.STATICSYNCTHRESH = RM_Field_MODEM_NS_SYNCPROPERTIES_STATICSYNCTHRESH(self)
        self.zz_fdict['STATICSYNCTHRESH'] = self.STATICSYNCTHRESH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PRSCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PRSCTRL, self).__init__(rmio, label,
            0xb8014000, 0x1AC,
            'PRSCTRL', 'MODEM_NS.PRSCTRL', 'read-write',
            u"",
            0x00000000, 0x000FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POSTPONESEL = RM_Field_MODEM_NS_PRSCTRL_POSTPONESEL(self)
        self.zz_fdict['POSTPONESEL'] = self.POSTPONESEL
        self.ADVANCESEL = RM_Field_MODEM_NS_PRSCTRL_ADVANCESEL(self)
        self.zz_fdict['ADVANCESEL'] = self.ADVANCESEL
        self.NEWWNDSEL = RM_Field_MODEM_NS_PRSCTRL_NEWWNDSEL(self)
        self.zz_fdict['NEWWNDSEL'] = self.NEWWNDSEL
        self.WEAKSEL = RM_Field_MODEM_NS_PRSCTRL_WEAKSEL(self)
        self.zz_fdict['WEAKSEL'] = self.WEAKSEL
        self.SYNCSENTSEL = RM_Field_MODEM_NS_PRSCTRL_SYNCSENTSEL(self)
        self.zz_fdict['SYNCSENTSEL'] = self.SYNCSENTSEL
        self.PRESENTSEL = RM_Field_MODEM_NS_PRSCTRL_PRESENTSEL(self)
        self.zz_fdict['PRESENTSEL'] = self.PRESENTSEL
        self.LOWCORRSEL = RM_Field_MODEM_NS_PRSCTRL_LOWCORRSEL(self)
        self.zz_fdict['LOWCORRSEL'] = self.LOWCORRSEL
        self.ANT0SEL = RM_Field_MODEM_NS_PRSCTRL_ANT0SEL(self)
        self.zz_fdict['ANT0SEL'] = self.ANT0SEL
        self.ANT1SEL = RM_Field_MODEM_NS_PRSCTRL_ANT1SEL(self)
        self.zz_fdict['ANT1SEL'] = self.ANT1SEL
        self.IFADCCLKSEL = RM_Field_MODEM_NS_PRSCTRL_IFADCCLKSEL(self)
        self.zz_fdict['IFADCCLKSEL'] = self.IFADCCLKSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PADEBUG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PADEBUG, self).__init__(rmio, label,
            0xb8014000, 0x1B0,
            'PADEBUG', 'MODEM_NS.PADEBUG', 'read-write',
            u"",
            0x00000000, 0x00001E00,
            0x00001000, 0x00002000,
            0x00003000)

        self.MANPACLKAMPCTRL = RM_Field_MODEM_NS_PADEBUG_MANPACLKAMPCTRL(self)
        self.zz_fdict['MANPACLKAMPCTRL'] = self.MANPACLKAMPCTRL
        self.ENMANPACLKAMPCTRL = RM_Field_MODEM_NS_PADEBUG_ENMANPACLKAMPCTRL(self)
        self.zz_fdict['ENMANPACLKAMPCTRL'] = self.ENMANPACLKAMPCTRL
        self.ENMANPAPOWER = RM_Field_MODEM_NS_PADEBUG_ENMANPAPOWER(self)
        self.zz_fdict['ENMANPAPOWER'] = self.ENMANPAPOWER
        self.ENMANPASELSLICE = RM_Field_MODEM_NS_PADEBUG_ENMANPASELSLICE(self)
        self.zz_fdict['ENMANPASELSLICE'] = self.ENMANPASELSLICE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_REALTIMCFE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_REALTIMCFE, self).__init__(rmio, label,
            0xb8014000, 0x1B4,
            'REALTIMCFE', 'MODEM_NS.REALTIMCFE', 'read-write',
            u"",
            0x001F81F4, 0xE03FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MINCOSTTHD = RM_Field_MODEM_NS_REALTIMCFE_MINCOSTTHD(self)
        self.zz_fdict['MINCOSTTHD'] = self.MINCOSTTHD
        self.RTSCHWIN = RM_Field_MODEM_NS_REALTIMCFE_RTSCHWIN(self)
        self.zz_fdict['RTSCHWIN'] = self.RTSCHWIN
        self.RTSCHMODE = RM_Field_MODEM_NS_REALTIMCFE_RTSCHMODE(self)
        self.zz_fdict['RTSCHMODE'] = self.RTSCHMODE
        self.TRACKINGWIN = RM_Field_MODEM_NS_REALTIMCFE_TRACKINGWIN(self)
        self.zz_fdict['TRACKINGWIN'] = self.TRACKINGWIN
        self.SYNCACQWIN = RM_Field_MODEM_NS_REALTIMCFE_SYNCACQWIN(self)
        self.zz_fdict['SYNCACQWIN'] = self.SYNCACQWIN
        self.EXTENSCHBYP = RM_Field_MODEM_NS_REALTIMCFE_EXTENSCHBYP(self)
        self.zz_fdict['EXTENSCHBYP'] = self.EXTENSCHBYP
        self.SINEWEN = RM_Field_MODEM_NS_REALTIMCFE_SINEWEN(self)
        self.zz_fdict['SINEWEN'] = self.SINEWEN
        self.VTAFCFRAME = RM_Field_MODEM_NS_REALTIMCFE_VTAFCFRAME(self)
        self.zz_fdict['VTAFCFRAME'] = self.VTAFCFRAME
        self.RTCFEEN = RM_Field_MODEM_NS_REALTIMCFE_RTCFEEN(self)
        self.zz_fdict['RTCFEEN'] = self.RTCFEEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ETSCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ETSCTRL, self).__init__(rmio, label,
            0xb8014000, 0x1B8,
            'ETSCTRL', 'MODEM_NS.ETSCTRL', 'read-write',
            u"",
            0x00000000, 0x3FFFF7FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ETSLOC = RM_Field_MODEM_NS_ETSCTRL_ETSLOC(self)
        self.zz_fdict['ETSLOC'] = self.ETSLOC
        self.CAPSIGONPRS = RM_Field_MODEM_NS_ETSCTRL_CAPSIGONPRS(self)
        self.zz_fdict['CAPSIGONPRS'] = self.CAPSIGONPRS
        self.CAPTRIG = RM_Field_MODEM_NS_ETSCTRL_CAPTRIG(self)
        self.zz_fdict['CAPTRIG'] = self.CAPTRIG
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ETSTIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ETSTIM, self).__init__(rmio, label,
            0xb8014000, 0x1BC,
            'ETSTIM', 'MODEM_NS.ETSTIM', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ETSTIMVAL = RM_Field_MODEM_NS_ETSTIM_ETSTIMVAL(self)
        self.zz_fdict['ETSTIMVAL'] = self.ETSTIMVAL
        self.ETSCOUNTEREN = RM_Field_MODEM_NS_ETSTIM_ETSCOUNTEREN(self)
        self.zz_fdict['ETSCOUNTEREN'] = self.ETSCOUNTEREN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTSWCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTSWCTRL, self).__init__(rmio, label,
            0xb8014000, 0x1C0,
            'ANTSWCTRL', 'MODEM_NS.ANTSWCTRL', 'read-write',
            u"",
            0x003C0000, 0x01FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTDFLTSEL = RM_Field_MODEM_NS_ANTSWCTRL_ANTDFLTSEL(self)
        self.zz_fdict['ANTDFLTSEL'] = self.ANTDFLTSEL
        self.ANTCOUNT = RM_Field_MODEM_NS_ANTSWCTRL_ANTCOUNT(self)
        self.zz_fdict['ANTCOUNT'] = self.ANTCOUNT
        self.ANTSWTYPE = RM_Field_MODEM_NS_ANTSWCTRL_ANTSWTYPE(self)
        self.zz_fdict['ANTSWTYPE'] = self.ANTSWTYPE
        self.ANTSWRST = RM_Field_MODEM_NS_ANTSWCTRL_ANTSWRST(self)
        self.zz_fdict['ANTSWRST'] = self.ANTSWRST
        self.CFGANTPATTEN = RM_Field_MODEM_NS_ANTSWCTRL_CFGANTPATTEN(self)
        self.zz_fdict['CFGANTPATTEN'] = self.CFGANTPATTEN
        self.ANTSWENABLE = RM_Field_MODEM_NS_ANTSWCTRL_ANTSWENABLE(self)
        self.zz_fdict['ANTSWENABLE'] = self.ANTSWENABLE
        self.EXTDSTOPPULSECNT = RM_Field_MODEM_NS_ANTSWCTRL_EXTDSTOPPULSECNT(self)
        self.zz_fdict['EXTDSTOPPULSECNT'] = self.EXTDSTOPPULSECNT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTSWCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTSWCTRL1, self).__init__(rmio, label,
            0xb8014000, 0x1C4,
            'ANTSWCTRL1', 'MODEM_NS.ANTSWCTRL1', 'read-write',
            u"",
            0x0006AAAA, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMEPERIOD = RM_Field_MODEM_NS_ANTSWCTRL1_TIMEPERIOD(self)
        self.zz_fdict['TIMEPERIOD'] = self.TIMEPERIOD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTSWSTART(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTSWSTART, self).__init__(rmio, label,
            0xb8014000, 0x1C8,
            'ANTSWSTART', 'MODEM_NS.ANTSWSTART', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTSWSTARTTIM = RM_Field_MODEM_NS_ANTSWSTART_ANTSWSTARTTIM(self)
        self.zz_fdict['ANTSWSTARTTIM'] = self.ANTSWSTARTTIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTSWEND(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTSWEND, self).__init__(rmio, label,
            0xb8014000, 0x1CC,
            'ANTSWEND', 'MODEM_NS.ANTSWEND', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTSWENDTIM = RM_Field_MODEM_NS_ANTSWEND_ANTSWENDTIM(self)
        self.zz_fdict['ANTSWENDTIM'] = self.ANTSWENDTIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TRECPMPATT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TRECPMPATT, self).__init__(rmio, label,
            0xb8014000, 0x1D0,
            'TRECPMPATT', 'MODEM_NS.TRECPMPATT', 'read-write',
            u"",
            0x55555555, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PMEXPECTPATT = RM_Field_MODEM_NS_TRECPMPATT_PMEXPECTPATT(self)
        self.zz_fdict['PMEXPECTPATT'] = self.PMEXPECTPATT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TRECPMDET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TRECPMDET, self).__init__(rmio, label,
            0xb8014000, 0x1D4,
            'TRECPMDET', 'MODEM_NS.TRECPMDET', 'read-write',
            u"",
            0x00000017, 0xBEFFC3FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PMACQUINGWIN = RM_Field_MODEM_NS_TRECPMDET_PMACQUINGWIN(self)
        self.zz_fdict['PMACQUINGWIN'] = self.PMACQUINGWIN
        self.PMCOSTVALTHD = RM_Field_MODEM_NS_TRECPMDET_PMCOSTVALTHD(self)
        self.zz_fdict['PMCOSTVALTHD'] = self.PMCOSTVALTHD
        self.PMTIMEOUTSEL = RM_Field_MODEM_NS_TRECPMDET_PMTIMEOUTSEL(self)
        self.zz_fdict['PMTIMEOUTSEL'] = self.PMTIMEOUTSEL
        self.PHSCALE = RM_Field_MODEM_NS_TRECPMDET_PHSCALE(self)
        self.zz_fdict['PHSCALE'] = self.PHSCALE
        self.PMMINCOSTTHD = RM_Field_MODEM_NS_TRECPMDET_PMMINCOSTTHD(self)
        self.zz_fdict['PMMINCOSTTHD'] = self.PMMINCOSTTHD
        self.COSTHYST = RM_Field_MODEM_NS_TRECPMDET_COSTHYST(self)
        self.zz_fdict['COSTHYST'] = self.COSTHYST
        self.PREAMSCH = RM_Field_MODEM_NS_TRECPMDET_PREAMSCH(self)
        self.zz_fdict['PREAMSCH'] = self.PREAMSCH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TRECSCFG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TRECSCFG, self).__init__(rmio, label,
            0xb8014000, 0x1D8,
            'TRECSCFG', 'MODEM_NS.TRECSCFG', 'read-write',
            u"",
            0x30020004, 0xF1FF5FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TRECSOSR = RM_Field_MODEM_NS_TRECSCFG_TRECSOSR(self)
        self.zz_fdict['TRECSOSR'] = self.TRECSOSR
        self.DTIMLOSSTHD = RM_Field_MODEM_NS_TRECSCFG_DTIMLOSSTHD(self)
        self.zz_fdict['DTIMLOSSTHD'] = self.DTIMLOSSTHD
        self.DTIMLOSSEN = RM_Field_MODEM_NS_TRECSCFG_DTIMLOSSEN(self)
        self.zz_fdict['DTIMLOSSEN'] = self.DTIMLOSSEN
        self.PMOFFSET = RM_Field_MODEM_NS_TRECSCFG_PMOFFSET(self)
        self.zz_fdict['PMOFFSET'] = self.PMOFFSET
        self.SDSCALE = RM_Field_MODEM_NS_TRECSCFG_SDSCALE(self)
        self.zz_fdict['SDSCALE'] = self.SDSCALE
        self.SOFTD = RM_Field_MODEM_NS_TRECSCFG_SOFTD(self)
        self.zz_fdict['SOFTD'] = self.SOFTD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CFGANTPATT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CFGANTPATT, self).__init__(rmio, label,
            0xb8014000, 0x1DC,
            'CFGANTPATT', 'MODEM_NS.CFGANTPATT', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CFGANTPATTVAL = RM_Field_MODEM_NS_CFGANTPATT_CFGANTPATTVAL(self)
        self.zz_fdict['CFGANTPATTVAL'] = self.CFGANTPATTVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_COCURRMODE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_COCURRMODE, self).__init__(rmio, label,
            0xb8014000, 0x1E0,
            'COCURRMODE', 'MODEM_NS.COCURRMODE', 'read-write',
            u"",
            0x00000000, 0x80000000,
            0x00001000, 0x00002000,
            0x00003000)

        self.CONCURRENT = RM_Field_MODEM_NS_COCURRMODE_CONCURRENT(self)
        self.zz_fdict['CONCURRENT'] = self.CONCURRENT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_FRMSCHTIME(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_FRMSCHTIME, self).__init__(rmio, label,
            0xb8014000, 0x224,
            'FRMSCHTIME', 'MODEM_NS.FRMSCHTIME', 'read-write',
            u"",
            0x00000040, 0xE000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FRMSCHTIME = RM_Field_MODEM_NS_FRMSCHTIME_FRMSCHTIME(self)
        self.zz_fdict['FRMSCHTIME'] = self.FRMSCHTIME
        self.PMRSTSYCNEN = RM_Field_MODEM_NS_FRMSCHTIME_PMRSTSYCNEN(self)
        self.zz_fdict['PMRSTSYCNEN'] = self.PMRSTSYCNEN
        self.DSARSTSYCNEN = RM_Field_MODEM_NS_FRMSCHTIME_DSARSTSYCNEN(self)
        self.zz_fdict['DSARSTSYCNEN'] = self.DSARSTSYCNEN
        self.PMENDSCHEN = RM_Field_MODEM_NS_FRMSCHTIME_PMENDSCHEN(self)
        self.zz_fdict['PMENDSCHEN'] = self.PMENDSCHEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PREFILTCOEFF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PREFILTCOEFF, self).__init__(rmio, label,
            0xb8014000, 0x228,
            'PREFILTCOEFF', 'MODEM_NS.PREFILTCOEFF', 'read-write',
            u"",
            0x3B3B3B3B, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREFILTCOEFF = RM_Field_MODEM_NS_PREFILTCOEFF_PREFILTCOEFF(self)
        self.zz_fdict['PREFILTCOEFF'] = self.PREFILTCOEFF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_RXRESTART(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_RXRESTART, self).__init__(rmio, label,
            0xb8014000, 0x22C,
            'RXRESTART', 'MODEM_NS.RXRESTART', 'read-write',
            u"",
            0x00000000, 0xC0010001,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXRESTARTUPONMARSSI = RM_Field_MODEM_NS_RXRESTART_RXRESTARTUPONMARSSI(self)
        self.zz_fdict['RXRESTARTUPONMARSSI'] = self.RXRESTARTUPONMARSSI
        self.RXRESTARTB4PREDET = RM_Field_MODEM_NS_RXRESTART_RXRESTARTB4PREDET(self)
        self.zz_fdict['RXRESTARTB4PREDET'] = self.RXRESTARTB4PREDET
        self.ANTSWRSTFLTTDIS = RM_Field_MODEM_NS_RXRESTART_ANTSWRSTFLTTDIS(self)
        self.zz_fdict['ANTSWRSTFLTTDIS'] = self.ANTSWRSTFLTTDIS
        self.FLTRSTEN = RM_Field_MODEM_NS_RXRESTART_FLTRSTEN(self)
        self.zz_fdict['FLTRSTEN'] = self.FLTRSTEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SQ(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SQ, self).__init__(rmio, label,
            0xb8014000, 0x230,
            'SQ', 'MODEM_NS.SQ', 'read-write',
            u"",
            0x00000000, 0xFFFF0003,
            0x00001000, 0x00002000,
            0x00003000)

        self.SQEN = RM_Field_MODEM_NS_SQ_SQEN(self)
        self.zz_fdict['SQEN'] = self.SQEN
        self.SQSWRST = RM_Field_MODEM_NS_SQ_SQSWRST(self)
        self.zz_fdict['SQSWRST'] = self.SQSWRST
        self.SQTIMOUT = RM_Field_MODEM_NS_SQ_SQTIMOUT(self)
        self.zz_fdict['SQTIMOUT'] = self.SQTIMOUT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SQEXT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SQEXT, self).__init__(rmio, label,
            0xb8014000, 0x234,
            'SQEXT', 'MODEM_NS.SQEXT', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SQSTG2TIMOUT = RM_Field_MODEM_NS_SQEXT_SQSTG2TIMOUT(self)
        self.zz_fdict['SQSTG2TIMOUT'] = self.SQSTG2TIMOUT
        self.SQSTG3TIMOUT = RM_Field_MODEM_NS_SQEXT_SQSTG3TIMOUT(self)
        self.zz_fdict['SQSTG3TIMOUT'] = self.SQSTG3TIMOUT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SQI(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SQI, self).__init__(rmio, label,
            0xb8014000, 0x238,
            'SQI', 'MODEM_NS.SQI', 'read-write',
            u"",
            0x00000000, 0x00FF0001,
            0x00001000, 0x00002000,
            0x00003000)

        self.SQISELECT = RM_Field_MODEM_NS_SQI_SQISELECT(self)
        self.zz_fdict['SQISELECT'] = self.SQISELECT
        self.CHIPERROR = RM_Field_MODEM_NS_SQI_CHIPERROR(self)
        self.zz_fdict['CHIPERROR'] = self.CHIPERROR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTDIVCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTDIVCTRL, self).__init__(rmio, label,
            0xb8014000, 0x23C,
            'ANTDIVCTRL', 'MODEM_NS.ANTDIVCTRL', 'read-write',
            u"",
            0x00000000, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADPRETHRESH = RM_Field_MODEM_NS_ANTDIVCTRL_ADPRETHRESH(self)
        self.zz_fdict['ADPRETHRESH'] = self.ADPRETHRESH
        self.ENADPRETHRESH = RM_Field_MODEM_NS_ANTDIVCTRL_ENADPRETHRESH(self)
        self.zz_fdict['ENADPRETHRESH'] = self.ENADPRETHRESH
        self.ANTDIVDISCCA = RM_Field_MODEM_NS_ANTDIVCTRL_ANTDIVDISCCA(self)
        self.zz_fdict['ANTDIVDISCCA'] = self.ANTDIVDISCCA
        self.ANTDIVSELCCA = RM_Field_MODEM_NS_ANTDIVCTRL_ANTDIVSELCCA(self)
        self.zz_fdict['ANTDIVSELCCA'] = self.ANTDIVSELCCA
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTDIVFW(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTDIVFW, self).__init__(rmio, label,
            0xb8014000, 0x240,
            'ANTDIVFW', 'MODEM_NS.ANTDIVFW', 'read-write',
            u"",
            0x00000000, 0x80000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.FWSELANT = RM_Field_MODEM_NS_ANTDIVFW_FWSELANT(self)
        self.zz_fdict['FWSELANT'] = self.FWSELANT
        self.FWANTSWCMD = RM_Field_MODEM_NS_ANTDIVFW_FWANTSWCMD(self)
        self.zz_fdict['FWANTSWCMD'] = self.FWANTSWCMD
        self.FWANTDIVEN = RM_Field_MODEM_NS_ANTDIVFW_FWANTDIVEN(self)
        self.zz_fdict['FWANTDIVEN'] = self.FWANTDIVEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PHDMODANTDIV(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PHDMODANTDIV, self).__init__(rmio, label,
            0xb8014000, 0x244,
            'PHDMODANTDIV', 'MODEM_NS.PHDMODANTDIV', 'read-write',
            u"",
            0x0000000F, 0xF3FF3FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTWAIT = RM_Field_MODEM_NS_PHDMODANTDIV_ANTWAIT(self)
        self.zz_fdict['ANTWAIT'] = self.ANTWAIT
        self.SKIPRSSITHD = RM_Field_MODEM_NS_PHDMODANTDIV_SKIPRSSITHD(self)
        self.zz_fdict['SKIPRSSITHD'] = self.SKIPRSSITHD
        self.SKIPCORRTHD = RM_Field_MODEM_NS_PHDMODANTDIV_SKIPCORRTHD(self)
        self.zz_fdict['SKIPCORRTHD'] = self.SKIPCORRTHD
        self.SKIPTHDSEL = RM_Field_MODEM_NS_PHDMODANTDIV_SKIPTHDSEL(self)
        self.zz_fdict['SKIPTHDSEL'] = self.SKIPTHDSEL
        self.RECHKCORREN = RM_Field_MODEM_NS_PHDMODANTDIV_RECHKCORREN(self)
        self.zz_fdict['RECHKCORREN'] = self.RECHKCORREN
        self.SKIP2ANT = RM_Field_MODEM_NS_PHDMODANTDIV_SKIP2ANT(self)
        self.zz_fdict['SKIP2ANT'] = self.SKIP2ANT
        self.ANTDECRSTBYP = RM_Field_MODEM_NS_PHDMODANTDIV_ANTDECRSTBYP(self)
        self.zz_fdict['ANTDECRSTBYP'] = self.ANTDECRSTBYP
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PHANTDECSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PHANTDECSION, self).__init__(rmio, label,
            0xb8014000, 0x248,
            'PHANTDECSION', 'MODEM_NS.PHANTDECSION', 'read-write',
            u"",
            0x00000000, 0xF007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CORRANDDIVTHD = RM_Field_MODEM_NS_PHANTDECSION_CORRANDDIVTHD(self)
        self.zz_fdict['CORRANDDIVTHD'] = self.CORRANDDIVTHD
        self.RSSIANDDIVTHD = RM_Field_MODEM_NS_PHANTDECSION_RSSIANDDIVTHD(self)
        self.zz_fdict['RSSIANDDIVTHD'] = self.RSSIANDDIVTHD
        self.RSSICORR0 = RM_Field_MODEM_NS_PHANTDECSION_RSSICORR0(self)
        self.zz_fdict['RSSICORR0'] = self.RSSICORR0
        self.RSSICORR1 = RM_Field_MODEM_NS_PHANTDECSION_RSSICORR1(self)
        self.zz_fdict['RSSICORR1'] = self.RSSICORR1
        self.RSSICORR2 = RM_Field_MODEM_NS_PHANTDECSION_RSSICORR2(self)
        self.zz_fdict['RSSICORR2'] = self.RSSICORR2
        self.RSSICORR3 = RM_Field_MODEM_NS_PHANTDECSION_RSSICORR3(self)
        self.zz_fdict['RSSICORR3'] = self.RSSICORR3
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PHDMODCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PHDMODCTRL, self).__init__(rmio, label,
            0xb8014000, 0x24C,
            'PHDMODCTRL', 'MODEM_NS.PHDMODCTRL', 'read-write',
            u"",
            0x01DF0004, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PMDETTHD = RM_Field_MODEM_NS_PHDMODCTRL_PMDETTHD(self)
        self.zz_fdict['PMDETTHD'] = self.PMDETTHD
        self.PMTIMLOSTHD = RM_Field_MODEM_NS_PHDMODCTRL_PMTIMLOSTHD(self)
        self.zz_fdict['PMTIMLOSTHD'] = self.PMTIMLOSTHD
        self.PMTIMLOSEN = RM_Field_MODEM_NS_PHDMODCTRL_PMTIMLOSEN(self)
        self.zz_fdict['PMTIMLOSEN'] = self.PMTIMLOSEN
        self.RSSIFLTBYP = RM_Field_MODEM_NS_PHDMODCTRL_RSSIFLTBYP(self)
        self.zz_fdict['RSSIFLTBYP'] = self.RSSIFLTBYP
        self.PMDETEN = RM_Field_MODEM_NS_PHDMODCTRL_PMDETEN(self)
        self.zz_fdict['PMDETEN'] = self.PMDETEN
        self.REMODOSR = RM_Field_MODEM_NS_PHDMODCTRL_REMODOSR(self)
        self.zz_fdict['REMODOSR'] = self.REMODOSR
        self.REMODDWN = RM_Field_MODEM_NS_PHDMODCTRL_REMODDWN(self)
        self.zz_fdict['REMODDWN'] = self.REMODDWN
        self.REMODOUTSEL = RM_Field_MODEM_NS_PHDMODCTRL_REMODOUTSEL(self)
        self.zz_fdict['REMODOUTSEL'] = self.REMODOUTSEL
        self.REMODEN = RM_Field_MODEM_NS_PHDMODCTRL_REMODEN(self)
        self.zz_fdict['REMODEN'] = self.REMODEN
        self.BCRDETECTOR = RM_Field_MODEM_NS_PHDMODCTRL_BCRDETECTOR(self)
        self.zz_fdict['BCRDETECTOR'] = self.BCRDETECTOR
        self.BCRTRECSCONC = RM_Field_MODEM_NS_PHDMODCTRL_BCRTRECSCONC(self)
        self.zz_fdict['BCRTRECSCONC'] = self.BCRTRECSCONC
        self.BCRLEGACYCONC = RM_Field_MODEM_NS_PHDMODCTRL_BCRLEGACYCONC(self)
        self.zz_fdict['BCRLEGACYCONC'] = self.BCRLEGACYCONC
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PHDMODCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PHDMODCTRL1, self).__init__(rmio, label,
            0xb8014000, 0x250,
            'PHDMODCTRL1', 'MODEM_NS.PHDMODCTRL1', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.TRECSFREQESTSEL = RM_Field_MODEM_NS_PHDMODCTRL1_TRECSFREQESTSEL(self)
        self.zz_fdict['TRECSFREQESTSEL'] = self.TRECSFREQESTSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SICTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SICTRL0, self).__init__(rmio, label,
            0xb8014000, 0x254,
            'SICTRL0', 'MODEM_NS.SICTRL0', 'read-write',
            u"",
            0x00000000, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODE = RM_Field_MODEM_NS_SICTRL0_MODE(self)
        self.zz_fdict['MODE'] = self.MODE
        self.NOISETHRESH = RM_Field_MODEM_NS_SICTRL0_NOISETHRESH(self)
        self.zz_fdict['NOISETHRESH'] = self.NOISETHRESH
        self.PEAKNUMTHRESHLW = RM_Field_MODEM_NS_SICTRL0_PEAKNUMTHRESHLW(self)
        self.zz_fdict['PEAKNUMTHRESHLW'] = self.PEAKNUMTHRESHLW
        self.SWPEAKNUMADJ = RM_Field_MODEM_NS_SICTRL0_SWPEAKNUMADJ(self)
        self.zz_fdict['SWPEAKNUMADJ'] = self.SWPEAKNUMADJ
        self.NOISETHRESHADJ = RM_Field_MODEM_NS_SICTRL0_NOISETHRESHADJ(self)
        self.zz_fdict['NOISETHRESHADJ'] = self.NOISETHRESHADJ
        self.FREQNOMINAL = RM_Field_MODEM_NS_SICTRL0_FREQNOMINAL(self)
        self.zz_fdict['FREQNOMINAL'] = self.FREQNOMINAL
        self.NDFOCAL = RM_Field_MODEM_NS_SICTRL0_NDFOCAL(self)
        self.zz_fdict['NDFOCAL'] = self.NDFOCAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SICTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SICTRL1, self).__init__(rmio, label,
            0xb8014000, 0x258,
            'SICTRL1', 'MODEM_NS.SICTRL1', 'read-write',
            u"",
            0x00000000, 0x1FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SUPERCHIPTOLERANCE = RM_Field_MODEM_NS_SICTRL1_SUPERCHIPTOLERANCE(self)
        self.zz_fdict['SUPERCHIPTOLERANCE'] = self.SUPERCHIPTOLERANCE
        self.SMALLSAMPLETHRESH = RM_Field_MODEM_NS_SICTRL1_SMALLSAMPLETHRESH(self)
        self.zz_fdict['SMALLSAMPLETHRESH'] = self.SMALLSAMPLETHRESH
        self.PEAKNUMP2ADJ = RM_Field_MODEM_NS_SICTRL1_PEAKNUMP2ADJ(self)
        self.zz_fdict['PEAKNUMP2ADJ'] = self.PEAKNUMP2ADJ
        self.FASTMODE = RM_Field_MODEM_NS_SICTRL1_FASTMODE(self)
        self.zz_fdict['FASTMODE'] = self.FASTMODE
        self.TWOSYMBEN = RM_Field_MODEM_NS_SICTRL1_TWOSYMBEN(self)
        self.zz_fdict['TWOSYMBEN'] = self.TWOSYMBEN
        self.ZCEN = RM_Field_MODEM_NS_SICTRL1_ZCEN(self)
        self.zz_fdict['ZCEN'] = self.ZCEN
        self.ZCSAMPLETHRESH = RM_Field_MODEM_NS_SICTRL1_ZCSAMPLETHRESH(self)
        self.zz_fdict['ZCSAMPLETHRESH'] = self.ZCSAMPLETHRESH
        self.SOFTCLIPBYPASS = RM_Field_MODEM_NS_SICTRL1_SOFTCLIPBYPASS(self)
        self.zz_fdict['SOFTCLIPBYPASS'] = self.SOFTCLIPBYPASS
        self.SOFTCLIPTHRESH = RM_Field_MODEM_NS_SICTRL1_SOFTCLIPTHRESH(self)
        self.zz_fdict['SOFTCLIPTHRESH'] = self.SOFTCLIPTHRESH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SISTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SISTATUS, self).__init__(rmio, label,
            0xb8014000, 0x25C,
            'SISTATUS', 'MODEM_NS.SISTATUS', 'read-only',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SISTATE = RM_Field_MODEM_NS_SISTATUS_SISTATE(self)
        self.zz_fdict['SISTATE'] = self.SISTATE
        self.NOISE = RM_Field_MODEM_NS_SISTATUS_NOISE(self)
        self.zz_fdict['NOISE'] = self.NOISE
        self.LWPEAKCOUNT = RM_Field_MODEM_NS_SISTATUS_LWPEAKCOUNT(self)
        self.zz_fdict['LWPEAKCOUNT'] = self.LWPEAKCOUNT
        self.NARROWCOUNT = RM_Field_MODEM_NS_SISTATUS_NARROWCOUNT(self)
        self.zz_fdict['NARROWCOUNT'] = self.NARROWCOUNT
        self.TIMELOCK = RM_Field_MODEM_NS_SISTATUS_TIMELOCK(self)
        self.zz_fdict['TIMELOCK'] = self.TIMELOCK
        self.SUPERCHIPFAIL = RM_Field_MODEM_NS_SISTATUS_SUPERCHIPFAIL(self)
        self.zz_fdict['SUPERCHIPFAIL'] = self.SUPERCHIPFAIL
        self.SUPERCHIPPASS = RM_Field_MODEM_NS_SISTATUS_SUPERCHIPPASS(self)
        self.zz_fdict['SUPERCHIPPASS'] = self.SUPERCHIPPASS
        self.TIMEOFFSET = RM_Field_MODEM_NS_SISTATUS_TIMEOFFSET(self)
        self.zz_fdict['TIMEOFFSET'] = self.TIMEOFFSET
        self.CORRPASSNUM = RM_Field_MODEM_NS_SISTATUS_CORRPASSNUM(self)
        self.zz_fdict['CORRPASSNUM'] = self.CORRPASSNUM
        self.SNIFFDONE = RM_Field_MODEM_NS_SISTATUS_SNIFFDONE(self)
        self.zz_fdict['SNIFFDONE'] = self.SNIFFDONE
        self.SIDET = RM_Field_MODEM_NS_SISTATUS_SIDET(self)
        self.zz_fdict['SIDET'] = self.SIDET
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CFGANTPATTEXT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CFGANTPATTEXT, self).__init__(rmio, label,
            0xb8014000, 0x260,
            'CFGANTPATTEXT', 'MODEM_NS.CFGANTPATTEXT', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CFGANTPATTVALEXT = RM_Field_MODEM_NS_CFGANTPATTEXT_CFGANTPATTVALEXT(self)
        self.zz_fdict['CFGANTPATTVALEXT'] = self.CFGANTPATTVALEXT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SICORR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SICORR, self).__init__(rmio, label,
            0xb8014000, 0x264,
            'SICORR', 'MODEM_NS.SICORR', 'read-write',
            u"",
            0x00000000, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CORRTHRESH = RM_Field_MODEM_NS_SICORR_CORRTHRESH(self)
        self.zz_fdict['CORRTHRESH'] = self.CORRTHRESH
        self.CORRTHRESHLOW = RM_Field_MODEM_NS_SICORR_CORRTHRESHLOW(self)
        self.zz_fdict['CORRTHRESHLOW'] = self.CORRTHRESHLOW
        self.CORRTHRESHUP = RM_Field_MODEM_NS_SICORR_CORRTHRESHUP(self)
        self.zz_fdict['CORRTHRESHUP'] = self.CORRTHRESHUP
        self.CORRTHRESH2SYMB = RM_Field_MODEM_NS_SICORR_CORRTHRESH2SYMB(self)
        self.zz_fdict['CORRTHRESH2SYMB'] = self.CORRTHRESH2SYMB
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SICTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SICTRL2, self).__init__(rmio, label,
            0xb8014000, 0x268,
            'SICTRL2', 'MODEM_NS.SICTRL2', 'read-write',
            u"",
            0x00000000, 0x000FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SIRSTAGCMODE = RM_Field_MODEM_NS_SICTRL2_SIRSTAGCMODE(self)
        self.zz_fdict['SIRSTAGCMODE'] = self.SIRSTAGCMODE
        self.SIRSTPRSMODE = RM_Field_MODEM_NS_SICTRL2_SIRSTPRSMODE(self)
        self.zz_fdict['SIRSTPRSMODE'] = self.SIRSTPRSMODE
        self.SIRSTCCAMODE = RM_Field_MODEM_NS_SICTRL2_SIRSTCCAMODE(self)
        self.zz_fdict['SIRSTCCAMODE'] = self.SIRSTCCAMODE
        self.DISSIFRAMEDET = RM_Field_MODEM_NS_SICTRL2_DISSIFRAMEDET(self)
        self.zz_fdict['DISSIFRAMEDET'] = self.DISSIFRAMEDET
        self.AGCRSTUPONSI = RM_Field_MODEM_NS_SICTRL2_AGCRSTUPONSI(self)
        self.zz_fdict['AGCRSTUPONSI'] = self.AGCRSTUPONSI
        self.SHFTWIN = RM_Field_MODEM_NS_SICTRL2_SHFTWIN(self)
        self.zz_fdict['SHFTWIN'] = self.SHFTWIN
        self.SUPERCHIPNUM = RM_Field_MODEM_NS_SICTRL2_SUPERCHIPNUM(self)
        self.zz_fdict['SUPERCHIPNUM'] = self.SUPERCHIPNUM
        self.CORRNUM = RM_Field_MODEM_NS_SICTRL2_CORRNUM(self)
        self.zz_fdict['CORRNUM'] = self.CORRNUM
        self.NARROWPULSETHRESH = RM_Field_MODEM_NS_SICTRL2_NARROWPULSETHRESH(self)
        self.zz_fdict['NARROWPULSETHRESH'] = self.NARROWPULSETHRESH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CHFSWCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CHFSWCTRL, self).__init__(rmio, label,
            0xb8014000, 0x26C,
            'CHFSWCTRL', 'MODEM_NS.CHFSWCTRL', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CHFSWTIME = RM_Field_MODEM_NS_CHFSWCTRL_CHFSWTIME(self)
        self.zz_fdict['CHFSWTIME'] = self.CHFSWTIME
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LOG2X4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LOG2X4, self).__init__(rmio, label,
            0xb8014000, 0x270,
            'LOG2X4', 'MODEM_NS.LOG2X4', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOG2X4 = RM_Field_MODEM_NS_LOG2X4_LOG2X4(self)
        self.zz_fdict['LOG2X4'] = self.LOG2X4
        self.LOG2X4FWSEL = RM_Field_MODEM_NS_LOG2X4_LOG2X4FWSEL(self)
        self.zz_fdict['LOG2X4FWSEL'] = self.LOG2X4FWSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADCTRL1, self).__init__(rmio, label,
            0xb8014000, 0x280,
            'ADCTRL1', 'MODEM_NS.ADCTRL1', 'read-write',
            u"",
            0x00080000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCTRL1 = RM_Field_MODEM_NS_ADCTRL1_ADCTRL1(self)
        self.zz_fdict['ADCTRL1'] = self.ADCTRL1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADCTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADCTRL2, self).__init__(rmio, label,
            0xb8014000, 0x284,
            'ADCTRL2', 'MODEM_NS.ADCTRL2', 'read-write',
            u"",
            0x00000001, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCTRL2 = RM_Field_MODEM_NS_ADCTRL2_ADCTRL2(self)
        self.zz_fdict['ADCTRL2'] = self.ADCTRL2
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL0, self).__init__(rmio, label,
            0xb8014000, 0x288,
            'ADQUAL0', 'MODEM_NS.ADQUAL0', 'read-only',
            u"",
            0x00000000, 0x03FF03FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADRSSI0 = RM_Field_MODEM_NS_ADQUAL0_ADRSSI0(self)
        self.zz_fdict['ADRSSI0'] = self.ADRSSI0
        self.ADRSSI1 = RM_Field_MODEM_NS_ADQUAL0_ADRSSI1(self)
        self.zz_fdict['ADRSSI1'] = self.ADRSSI1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL1, self).__init__(rmio, label,
            0xb8014000, 0x28C,
            'ADQUAL1', 'MODEM_NS.ADQUAL1', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCORR0 = RM_Field_MODEM_NS_ADQUAL1_ADCORR0(self)
        self.zz_fdict['ADCORR0'] = self.ADCORR0
        self.ADSTAT1 = RM_Field_MODEM_NS_ADQUAL1_ADSTAT1(self)
        self.zz_fdict['ADSTAT1'] = self.ADSTAT1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL2, self).__init__(rmio, label,
            0xb8014000, 0x290,
            'ADQUAL2', 'MODEM_NS.ADQUAL2', 'read-only',
            u"",
            0x00000000, 0x03FF03FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADRSSI0P = RM_Field_MODEM_NS_ADQUAL2_ADRSSI0P(self)
        self.zz_fdict['ADRSSI0P'] = self.ADRSSI0P
        self.ADRSSI1P = RM_Field_MODEM_NS_ADQUAL2_ADRSSI1P(self)
        self.zz_fdict['ADRSSI1P'] = self.ADRSSI1P
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL3, self).__init__(rmio, label,
            0xb8014000, 0x294,
            'ADQUAL3', 'MODEM_NS.ADQUAL3', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCORR0P = RM_Field_MODEM_NS_ADQUAL3_ADCORR0P(self)
        self.zz_fdict['ADCORR0P'] = self.ADCORR0P
        self.ADSTAT2 = RM_Field_MODEM_NS_ADQUAL3_ADSTAT2(self)
        self.zz_fdict['ADSTAT2'] = self.ADSTAT2
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL4, self).__init__(rmio, label,
            0xb8014000, 0x298,
            'ADQUAL4', 'MODEM_NS.ADQUAL4', 'read-write',
            u"",
            0x0200003F, 0x03FF003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADAGCGRTHR = RM_Field_MODEM_NS_ADQUAL4_ADAGCGRTHR(self)
        self.zz_fdict['ADAGCGRTHR'] = self.ADAGCGRTHR
        self.ADRSSIGRTHR = RM_Field_MODEM_NS_ADQUAL4_ADRSSIGRTHR(self)
        self.zz_fdict['ADRSSIGRTHR'] = self.ADRSSIGRTHR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL5, self).__init__(rmio, label,
            0xb8014000, 0x29C,
            'ADQUAL5', 'MODEM_NS.ADQUAL5', 'read-write',
            u"",
            0x0000FFFF, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADDIRECTCORR = RM_Field_MODEM_NS_ADQUAL5_ADDIRECTCORR(self)
        self.zz_fdict['ADDIRECTCORR'] = self.ADDIRECTCORR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL6, self).__init__(rmio, label,
            0xb8014000, 0x2A0,
            'ADQUAL6', 'MODEM_NS.ADQUAL6', 'read-write',
            u"",
            0x0000FFFF, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBACORRTHR = RM_Field_MODEM_NS_ADQUAL6_ADBACORRTHR(self)
        self.zz_fdict['ADBACORRTHR'] = self.ADBACORRTHR
        self.ADBACORRDIFF = RM_Field_MODEM_NS_ADQUAL6_ADBACORRDIFF(self)
        self.zz_fdict['ADBACORRDIFF'] = self.ADBACORRDIFF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL7, self).__init__(rmio, label,
            0xb8014000, 0x2A4,
            'ADQUAL7', 'MODEM_NS.ADQUAL7', 'read-write',
            u"",
            0x000003FF, 0x03FF03FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBARSSITHR = RM_Field_MODEM_NS_ADQUAL7_ADBARSSITHR(self)
        self.zz_fdict['ADBARSSITHR'] = self.ADBARSSITHR
        self.ADBARSSIDIFF = RM_Field_MODEM_NS_ADQUAL7_ADBARSSIDIFF(self)
        self.zz_fdict['ADBARSSIDIFF'] = self.ADBARSSIDIFF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL8, self).__init__(rmio, label,
            0xb8014000, 0x2A8,
            'ADQUAL8', 'MODEM_NS.ADQUAL8', 'read-write',
            u"",
            0x0000FFFF, 0x3F31FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADBACORRTHR2 = RM_Field_MODEM_NS_ADQUAL8_ADBACORRTHR2(self)
        self.zz_fdict['ADBACORRTHR2'] = self.ADBACORRTHR2
        self.ADBAMODE = RM_Field_MODEM_NS_ADQUAL8_ADBAMODE(self)
        self.zz_fdict['ADBAMODE'] = self.ADBAMODE
        self.ADBAAGCTHR = RM_Field_MODEM_NS_ADQUAL8_ADBAAGCTHR(self)
        self.zz_fdict['ADBAAGCTHR'] = self.ADBAAGCTHR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL9, self).__init__(rmio, label,
            0xb8014000, 0x2AC,
            'ADQUAL9', 'MODEM_NS.ADQUAL9', 'read-only',
            u"",
            0x00000000, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCORR1 = RM_Field_MODEM_NS_ADQUAL9_ADCORR1(self)
        self.zz_fdict['ADCORR1'] = self.ADCORR1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADQUAL10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADQUAL10, self).__init__(rmio, label,
            0xb8014000, 0x2B0,
            'ADQUAL10', 'MODEM_NS.ADQUAL10', 'read-only',
            u"",
            0x00000000, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCORR1P = RM_Field_MODEM_NS_ADQUAL10_ADCORR1P(self)
        self.zz_fdict['ADCORR1P'] = self.ADCORR1P
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM0, self).__init__(rmio, label,
            0xb8014000, 0x2B4,
            'ADFSM0', 'MODEM_NS.ADFSM0', 'read-write',
            u"",
            0x00000000, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADSTATEC = RM_Field_MODEM_NS_ADFSM0_ADSTATEC(self)
        self.zz_fdict['ADSTATEC'] = self.ADSTATEC
        self.ADSTATEP = RM_Field_MODEM_NS_ADFSM0_ADSTATEP(self)
        self.zz_fdict['ADSTATEP'] = self.ADSTATEP
        self.ADSTATEP2 = RM_Field_MODEM_NS_ADFSM0_ADSTATEP2(self)
        self.zz_fdict['ADSTATEP2'] = self.ADSTATEP2
        self.ADSTATEN = RM_Field_MODEM_NS_ADFSM0_ADSTATEN(self)
        self.zz_fdict['ADSTATEN'] = self.ADSTATEN
        self.ADTD0 = RM_Field_MODEM_NS_ADFSM0_ADTD0(self)
        self.zz_fdict['ADTD0'] = self.ADTD0
        self.ADTD0P = RM_Field_MODEM_NS_ADFSM0_ADTD0P(self)
        self.zz_fdict['ADTD0P'] = self.ADTD0P
        self.ADTD1 = RM_Field_MODEM_NS_ADFSM0_ADTD1(self)
        self.zz_fdict['ADTD1'] = self.ADTD1
        self.ADTD1P = RM_Field_MODEM_NS_ADFSM0_ADTD1P(self)
        self.zz_fdict['ADTD1P'] = self.ADTD1P
        self.ADSTATREAD = RM_Field_MODEM_NS_ADFSM0_ADSTATREAD(self)
        self.zz_fdict['ADSTATREAD'] = self.ADSTATREAD
        self.ADSTAT1SEL = RM_Field_MODEM_NS_ADFSM0_ADSTAT1SEL(self)
        self.zz_fdict['ADSTAT1SEL'] = self.ADSTAT1SEL
        self.ADSTAT2SEL = RM_Field_MODEM_NS_ADFSM0_ADSTAT2SEL(self)
        self.zz_fdict['ADSTAT2SEL'] = self.ADSTAT2SEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM1, self).__init__(rmio, label,
            0xb8014000, 0x2B8,
            'ADFSM1', 'MODEM_NS.ADFSM1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADOSETANT0 = RM_Field_MODEM_NS_ADFSM1_ADOSETANT0(self)
        self.zz_fdict['ADOSETANT0'] = self.ADOSETANT0
        self.ADOSETANT1 = RM_Field_MODEM_NS_ADFSM1_ADOSETANT1(self)
        self.zz_fdict['ADOSETANT1'] = self.ADOSETANT1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM2, self).__init__(rmio, label,
            0xb8014000, 0x2BC,
            'ADFSM2', 'MODEM_NS.ADFSM2', 'read-write',
            u"",
            0x00000000, 0xFFFF0000,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADORESTARTRX = RM_Field_MODEM_NS_ADFSM2_ADORESTARTRX(self)
        self.zz_fdict['ADORESTARTRX'] = self.ADORESTARTRX
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM3, self).__init__(rmio, label,
            0xb8014000, 0x2C0,
            'ADFSM3', 'MODEM_NS.ADFSM3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADOQUAL0UPDATE = RM_Field_MODEM_NS_ADFSM3_ADOQUAL0UPDATE(self)
        self.zz_fdict['ADOQUAL0UPDATE'] = self.ADOQUAL0UPDATE
        self.ADOQUAL1UPDATE = RM_Field_MODEM_NS_ADFSM3_ADOQUAL1UPDATE(self)
        self.zz_fdict['ADOQUAL1UPDATE'] = self.ADOQUAL1UPDATE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM4, self).__init__(rmio, label,
            0xb8014000, 0x2C4,
            'ADFSM4', 'MODEM_NS.ADFSM4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADOQUAL0CLEAR = RM_Field_MODEM_NS_ADFSM4_ADOQUAL0CLEAR(self)
        self.zz_fdict['ADOQUAL0CLEAR'] = self.ADOQUAL0CLEAR
        self.ADOQUAL1CLEAR = RM_Field_MODEM_NS_ADFSM4_ADOQUAL1CLEAR(self)
        self.zz_fdict['ADOQUAL1CLEAR'] = self.ADOQUAL1CLEAR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM5, self).__init__(rmio, label,
            0xb8014000, 0x2C8,
            'ADFSM5', 'MODEM_NS.ADFSM5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADOMUX = RM_Field_MODEM_NS_ADFSM5_ADOMUX(self)
        self.zz_fdict['ADOMUX'] = self.ADOMUX
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM6, self).__init__(rmio, label,
            0xb8014000, 0x2CC,
            'ADFSM6', 'MODEM_NS.ADFSM6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADNEXTSTATESW0 = RM_Field_MODEM_NS_ADFSM6_ADNEXTSTATESW0(self)
        self.zz_fdict['ADNEXTSTATESW0'] = self.ADNEXTSTATESW0
        self.ADNEXTSTATESW1 = RM_Field_MODEM_NS_ADFSM6_ADNEXTSTATESW1(self)
        self.zz_fdict['ADNEXTSTATESW1'] = self.ADNEXTSTATESW1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM7, self).__init__(rmio, label,
            0xb8014000, 0x2D0,
            'ADFSM7', 'MODEM_NS.ADFSM7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADNEXTSTATESW2 = RM_Field_MODEM_NS_ADFSM7_ADNEXTSTATESW2(self)
        self.zz_fdict['ADNEXTSTATESW2'] = self.ADNEXTSTATESW2
        self.ADNEXTSTATESW3 = RM_Field_MODEM_NS_ADFSM7_ADNEXTSTATESW3(self)
        self.zz_fdict['ADNEXTSTATESW3'] = self.ADNEXTSTATESW3
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM8, self).__init__(rmio, label,
            0xb8014000, 0x2D4,
            'ADFSM8', 'MODEM_NS.ADFSM8', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADNEXTSTATESW4 = RM_Field_MODEM_NS_ADFSM8_ADNEXTSTATESW4(self)
        self.zz_fdict['ADNEXTSTATESW4'] = self.ADNEXTSTATESW4
        self.ADNEXTSTATESW5 = RM_Field_MODEM_NS_ADFSM8_ADNEXTSTATESW5(self)
        self.zz_fdict['ADNEXTSTATESW5'] = self.ADNEXTSTATESW5
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM9, self).__init__(rmio, label,
            0xb8014000, 0x2D8,
            'ADFSM9', 'MODEM_NS.ADFSM9', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADNEXTSTATESW6 = RM_Field_MODEM_NS_ADFSM9_ADNEXTSTATESW6(self)
        self.zz_fdict['ADNEXTSTATESW6'] = self.ADNEXTSTATESW6
        self.ADNEXTSTATESW7 = RM_Field_MODEM_NS_ADFSM9_ADNEXTSTATESW7(self)
        self.zz_fdict['ADNEXTSTATESW7'] = self.ADNEXTSTATESW7
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM10, self).__init__(rmio, label,
            0xb8014000, 0x2DC,
            'ADFSM10', 'MODEM_NS.ADFSM10', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADNEXTSTATESW8 = RM_Field_MODEM_NS_ADFSM10_ADNEXTSTATESW8(self)
        self.zz_fdict['ADNEXTSTATESW8'] = self.ADNEXTSTATESW8
        self.ADNEXTSTATESW9 = RM_Field_MODEM_NS_ADFSM10_ADNEXTSTATESW9(self)
        self.zz_fdict['ADNEXTSTATESW9'] = self.ADNEXTSTATESW9
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM11(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM11, self).__init__(rmio, label,
            0xb8014000, 0x2E0,
            'ADFSM11', 'MODEM_NS.ADFSM11', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADNEXTSTATESW10 = RM_Field_MODEM_NS_ADFSM11_ADNEXTSTATESW10(self)
        self.zz_fdict['ADNEXTSTATESW10'] = self.ADNEXTSTATESW10
        self.ADNEXTSTATESW11 = RM_Field_MODEM_NS_ADFSM11_ADNEXTSTATESW11(self)
        self.zz_fdict['ADNEXTSTATESW11'] = self.ADNEXTSTATESW11
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM12(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM12, self).__init__(rmio, label,
            0xb8014000, 0x2E4,
            'ADFSM12', 'MODEM_NS.ADFSM12', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADNEXTSTATESW12 = RM_Field_MODEM_NS_ADFSM12_ADNEXTSTATESW12(self)
        self.zz_fdict['ADNEXTSTATESW12'] = self.ADNEXTSTATESW12
        self.ADNEXTSTATESW13 = RM_Field_MODEM_NS_ADFSM12_ADNEXTSTATESW13(self)
        self.zz_fdict['ADNEXTSTATESW13'] = self.ADNEXTSTATESW13
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM13(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM13, self).__init__(rmio, label,
            0xb8014000, 0x2E8,
            'ADFSM13', 'MODEM_NS.ADFSM13', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADNEXTSTATESW14 = RM_Field_MODEM_NS_ADFSM13_ADNEXTSTATESW14(self)
        self.zz_fdict['ADNEXTSTATESW14'] = self.ADNEXTSTATESW14
        self.ADNEXTSTATESW15 = RM_Field_MODEM_NS_ADFSM13_ADNEXTSTATESW15(self)
        self.zz_fdict['ADNEXTSTATESW15'] = self.ADNEXTSTATESW15
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM14(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM14, self).__init__(rmio, label,
            0xb8014000, 0x2EC,
            'ADFSM14', 'MODEM_NS.ADFSM14', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCOND0ENA = RM_Field_MODEM_NS_ADFSM14_ADFSMCOND0ENA(self)
        self.zz_fdict['ADFSMCOND0ENA'] = self.ADFSMCOND0ENA
        self.ADFSMCOND1ENA = RM_Field_MODEM_NS_ADFSM14_ADFSMCOND1ENA(self)
        self.zz_fdict['ADFSMCOND1ENA'] = self.ADFSMCOND1ENA
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM15(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM15, self).__init__(rmio, label,
            0xb8014000, 0x2F0,
            'ADFSM15', 'MODEM_NS.ADFSM15', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCOND2ENA = RM_Field_MODEM_NS_ADFSM15_ADFSMCOND2ENA(self)
        self.zz_fdict['ADFSMCOND2ENA'] = self.ADFSMCOND2ENA
        self.ADFSMCOND3ENA = RM_Field_MODEM_NS_ADFSM15_ADFSMCOND3ENA(self)
        self.zz_fdict['ADFSMCOND3ENA'] = self.ADFSMCOND3ENA
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM16(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM16, self).__init__(rmio, label,
            0xb8014000, 0x2F4,
            'ADFSM16', 'MODEM_NS.ADFSM16', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCOND0ENB = RM_Field_MODEM_NS_ADFSM16_ADFSMCOND0ENB(self)
        self.zz_fdict['ADFSMCOND0ENB'] = self.ADFSMCOND0ENB
        self.ADFSMCOND1ENB = RM_Field_MODEM_NS_ADFSM16_ADFSMCOND1ENB(self)
        self.zz_fdict['ADFSMCOND1ENB'] = self.ADFSMCOND1ENB
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM17(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM17, self).__init__(rmio, label,
            0xb8014000, 0x2F8,
            'ADFSM17', 'MODEM_NS.ADFSM17', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCOND2ENB = RM_Field_MODEM_NS_ADFSM17_ADFSMCOND2ENB(self)
        self.zz_fdict['ADFSMCOND2ENB'] = self.ADFSMCOND2ENB
        self.ADFSMCOND3ENB = RM_Field_MODEM_NS_ADFSM17_ADFSMCOND3ENB(self)
        self.zz_fdict['ADFSMCOND3ENB'] = self.ADFSMCOND3ENB
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM18(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM18, self).__init__(rmio, label,
            0xb8014000, 0x2FC,
            'ADFSM18', 'MODEM_NS.ADFSM18', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCONDSEL = RM_Field_MODEM_NS_ADFSM18_ADFSMCONDSEL(self)
        self.zz_fdict['ADFSMCONDSEL'] = self.ADFSMCONDSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM19(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM19, self).__init__(rmio, label,
            0xb8014000, 0x300,
            'ADFSM19', 'MODEM_NS.ADFSM19', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMNEXTFORCE = RM_Field_MODEM_NS_ADFSM19_ADFSMNEXTFORCE(self)
        self.zz_fdict['ADFSMNEXTFORCE'] = self.ADFSMNEXTFORCE
        self.ADFSMCONDTRUE = RM_Field_MODEM_NS_ADFSM19_ADFSMCONDTRUE(self)
        self.zz_fdict['ADFSMCONDTRUE'] = self.ADFSMCONDTRUE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM20(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM20, self).__init__(rmio, label,
            0xb8014000, 0x304,
            'ADFSM20', 'MODEM_NS.ADFSM20', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADITENTEREN = RM_Field_MODEM_NS_ADFSM20_ADITENTEREN(self)
        self.zz_fdict['ADITENTEREN'] = self.ADITENTEREN
        self.ADITLEAVEEN = RM_Field_MODEM_NS_ADFSM20_ADITLEAVEEN(self)
        self.zz_fdict['ADITLEAVEEN'] = self.ADITLEAVEEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM21(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM21, self).__init__(rmio, label,
            0xb8014000, 0x308,
            'ADFSM21', 'MODEM_NS.ADFSM21', 'read-write',
            u"",
            0x00000000, 0x000101FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADENTERFREEZEEN = RM_Field_MODEM_NS_ADFSM21_ADENTERFREEZEEN(self)
        self.zz_fdict['ADENTERFREEZEEN'] = self.ADENTERFREEZEEN
        self.ADLEAVEFREEZEEN = RM_Field_MODEM_NS_ADFSM21_ADLEAVEFREEZEEN(self)
        self.zz_fdict['ADLEAVEFREEZEEN'] = self.ADLEAVEFREEZEEN
        self.ADFROZEN = RM_Field_MODEM_NS_ADFSM21_ADFROZEN(self)
        self.zz_fdict['ADFROZEN'] = self.ADFROZEN
        self.ADUNFREEZENEXT = RM_Field_MODEM_NS_ADFSM21_ADUNFREEZENEXT(self)
        self.zz_fdict['ADUNFREEZENEXT'] = self.ADUNFREEZENEXT
        self.ADAS = RM_Field_MODEM_NS_ADFSM21_ADAS(self)
        self.zz_fdict['ADAS'] = self.ADAS
        self.ADBA = RM_Field_MODEM_NS_ADFSM21_ADBA(self)
        self.zz_fdict['ADBA'] = self.ADBA
        self.ADUNFREEZE = RM_Field_MODEM_NS_ADFSM21_ADUNFREEZE(self)
        self.zz_fdict['ADUNFREEZE'] = self.ADUNFREEZE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM22(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM22, self).__init__(rmio, label,
            0xb8014000, 0x30C,
            'ADFSM22', 'MODEM_NS.ADFSM22', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADITENTERSTATUS = RM_Field_MODEM_NS_ADFSM22_ADITENTERSTATUS(self)
        self.zz_fdict['ADITENTERSTATUS'] = self.ADITENTERSTATUS
        self.ADITLEAVESTATUS = RM_Field_MODEM_NS_ADFSM22_ADITLEAVESTATUS(self)
        self.zz_fdict['ADITLEAVESTATUS'] = self.ADITLEAVESTATUS
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM23(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM23, self).__init__(rmio, label,
            0xb8014000, 0x310,
            'ADFSM23', 'MODEM_NS.ADFSM23', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCOND0ENC = RM_Field_MODEM_NS_ADFSM23_ADFSMCOND0ENC(self)
        self.zz_fdict['ADFSMCOND0ENC'] = self.ADFSMCOND0ENC
        self.ADFSMCOND1ENC = RM_Field_MODEM_NS_ADFSM23_ADFSMCOND1ENC(self)
        self.zz_fdict['ADFSMCOND1ENC'] = self.ADFSMCOND1ENC
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM24(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM24, self).__init__(rmio, label,
            0xb8014000, 0x314,
            'ADFSM24', 'MODEM_NS.ADFSM24', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCOND2ENC = RM_Field_MODEM_NS_ADFSM24_ADFSMCOND2ENC(self)
        self.zz_fdict['ADFSMCOND2ENC'] = self.ADFSMCOND2ENC
        self.ADFSMCOND3ENC = RM_Field_MODEM_NS_ADFSM24_ADFSMCOND3ENC(self)
        self.zz_fdict['ADFSMCOND3ENC'] = self.ADFSMCOND3ENC
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM25(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM25, self).__init__(rmio, label,
            0xb8014000, 0x318,
            'ADFSM25', 'MODEM_NS.ADFSM25', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCONDOR0 = RM_Field_MODEM_NS_ADFSM25_ADFSMCONDOR0(self)
        self.zz_fdict['ADFSMCONDOR0'] = self.ADFSMCONDOR0
        self.ADFSMCONDOR1 = RM_Field_MODEM_NS_ADFSM25_ADFSMCONDOR1(self)
        self.zz_fdict['ADFSMCONDOR1'] = self.ADFSMCONDOR1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM26(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM26, self).__init__(rmio, label,
            0xb8014000, 0x31C,
            'ADFSM26', 'MODEM_NS.ADFSM26', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCOND0END = RM_Field_MODEM_NS_ADFSM26_ADFSMCOND0END(self)
        self.zz_fdict['ADFSMCOND0END'] = self.ADFSMCOND0END
        self.ADFSMCOND1END = RM_Field_MODEM_NS_ADFSM26_ADFSMCOND1END(self)
        self.zz_fdict['ADFSMCOND1END'] = self.ADFSMCOND1END
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM27(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM27, self).__init__(rmio, label,
            0xb8014000, 0x320,
            'ADFSM27', 'MODEM_NS.ADFSM27', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADFSMCOND2END = RM_Field_MODEM_NS_ADFSM27_ADFSMCOND2END(self)
        self.zz_fdict['ADFSMCOND2END'] = self.ADFSMCOND2END
        self.ADFSMCOND3END = RM_Field_MODEM_NS_ADFSM27_ADFSMCOND3END(self)
        self.zz_fdict['ADFSMCOND3END'] = self.ADFSMCOND3END
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM28(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM28, self).__init__(rmio, label,
            0xb8014000, 0x324,
            'ADFSM28', 'MODEM_NS.ADFSM28', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADOSETANTFORCE = RM_Field_MODEM_NS_ADFSM28_ADOSETANTFORCE(self)
        self.zz_fdict['ADOSETANTFORCE'] = self.ADOSETANTFORCE
        self.ADORESTARTRXFORCE = RM_Field_MODEM_NS_ADFSM28_ADORESTARTRXFORCE(self)
        self.zz_fdict['ADORESTARTRXFORCE'] = self.ADORESTARTRXFORCE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM29(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM29, self).__init__(rmio, label,
            0xb8014000, 0x328,
            'ADFSM29', 'MODEM_NS.ADFSM29', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADOQUALUPDATEFORCE = RM_Field_MODEM_NS_ADFSM29_ADOQUALUPDATEFORCE(self)
        self.zz_fdict['ADOQUALUPDATEFORCE'] = self.ADOQUALUPDATEFORCE
        self.ADOQUALCLEARFORCE = RM_Field_MODEM_NS_ADFSM29_ADOQUALCLEARFORCE(self)
        self.zz_fdict['ADOQUALCLEARFORCE'] = self.ADOQUALCLEARFORCE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADFSM30(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADFSM30, self).__init__(rmio, label,
            0xb8014000, 0x32C,
            'ADFSM30', 'MODEM_NS.ADFSM30', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADODEMODRXREQ = RM_Field_MODEM_NS_ADFSM30_ADODEMODRXREQ(self)
        self.zz_fdict['ADODEMODRXREQ'] = self.ADODEMODRXREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADPC1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADPC1, self).__init__(rmio, label,
            0xb8014000, 0x330,
            'ADPC1', 'MODEM_NS.ADPC1', 'read-write',
            u"",
            0x01200040, 0xFFFF7FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADPCEN = RM_Field_MODEM_NS_ADPC1_ADPCEN(self)
        self.zz_fdict['ADPCEN'] = self.ADPCEN
        self.ADPCWNDSIZECHIP = RM_Field_MODEM_NS_ADPC1_ADPCWNDSIZECHIP(self)
        self.zz_fdict['ADPCWNDSIZECHIP'] = self.ADPCWNDSIZECHIP
        self.ADPCCORROFFSETCHIP = RM_Field_MODEM_NS_ADPC1_ADPCCORROFFSETCHIP(self)
        self.zz_fdict['ADPCCORROFFSETCHIP'] = self.ADPCCORROFFSETCHIP
        self.ADPCTIMINGBAUDS = RM_Field_MODEM_NS_ADPC1_ADPCTIMINGBAUDS(self)
        self.zz_fdict['ADPCTIMINGBAUDS'] = self.ADPCTIMINGBAUDS
        self.ADPCWNDCNT = RM_Field_MODEM_NS_ADPC1_ADPCWNDCNT(self)
        self.zz_fdict['ADPCWNDCNT'] = self.ADPCWNDCNT
        self.ADPCSKIPCHIPS = RM_Field_MODEM_NS_ADPC1_ADPCSKIPCHIPS(self)
        self.zz_fdict['ADPCSKIPCHIPS'] = self.ADPCSKIPCHIPS
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADPC2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADPC2, self).__init__(rmio, label,
            0xb8014000, 0x334,
            'ADPC2', 'MODEM_NS.ADPC2', 'read-write',
            u"",
            0x000000A0, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADPCCORRSAMPLES = RM_Field_MODEM_NS_ADPC2_ADPCCORRSAMPLES(self)
        self.zz_fdict['ADPCCORRSAMPLES'] = self.ADPCCORRSAMPLES
        self.ADPCPRETIMINGBAUDS = RM_Field_MODEM_NS_ADPC2_ADPCPRETIMINGBAUDS(self)
        self.zz_fdict['ADPCPRETIMINGBAUDS'] = self.ADPCPRETIMINGBAUDS
        self.ADENCORR32 = RM_Field_MODEM_NS_ADPC2_ADENCORR32(self)
        self.zz_fdict['ADENCORR32'] = self.ADENCORR32
        self.ADPCSIGAMPTHR = RM_Field_MODEM_NS_ADPC2_ADPCSIGAMPTHR(self)
        self.zz_fdict['ADPCSIGAMPTHR'] = self.ADPCSIGAMPTHR
        self.ADPCWNDCNTRST = RM_Field_MODEM_NS_ADPC2_ADPCWNDCNTRST(self)
        self.zz_fdict['ADPCWNDCNTRST'] = self.ADPCWNDCNTRST
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ADPC8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ADPC8, self).__init__(rmio, label,
            0xb8014000, 0x34C,
            'ADPC8', 'MODEM_NS.ADPC8', 'read-write',
            u"",
            0x2F87C145, 0xFFFFFF7F,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADPCOSR = RM_Field_MODEM_NS_ADPC8_ADPCOSR(self)
        self.zz_fdict['ADPCOSR'] = self.ADPCOSR
        self.ADPCANTSAMPOFFSET = RM_Field_MODEM_NS_ADPC8_ADPCANTSAMPOFFSET(self)
        self.zz_fdict['ADPCANTSAMPOFFSET'] = self.ADPCANTSAMPOFFSET
        self.ADPCANTSAMPSWITCHWAIT = RM_Field_MODEM_NS_ADPC8_ADPCANTSAMPSWITCHWAIT(self)
        self.zz_fdict['ADPCANTSAMPSWITCHWAIT'] = self.ADPCANTSAMPSWITCHWAIT
        self.ADPCANTSAMPBUF = RM_Field_MODEM_NS_ADPC8_ADPCANTSAMPBUF(self)
        self.zz_fdict['ADPCANTSAMPBUF'] = self.ADPCANTSAMPBUF
        self.ADPCANTSAMPWRITE = RM_Field_MODEM_NS_ADPC8_ADPCANTSAMPWRITE(self)
        self.zz_fdict['ADPCANTSAMPWRITE'] = self.ADPCANTSAMPWRITE
        self.ADPCANTSAMPSWITCH = RM_Field_MODEM_NS_ADPC8_ADPCANTSAMPSWITCH(self)
        self.zz_fdict['ADPCANTSAMPSWITCH'] = self.ADPCANTSAMPSWITCH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRCTRL0, self).__init__(rmio, label,
            0xb8014000, 0x370,
            'BCRCTRL0', 'MODEM_NS.BCRCTRL0', 'read-write',
            u"",
            0x08857628, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BCRNCOFF = RM_Field_MODEM_NS_BCRCTRL0_BCRNCOFF(self)
        self.zz_fdict['BCRNCOFF'] = self.BCRNCOFF
        self.BCRERRRSTEN = RM_Field_MODEM_NS_BCRCTRL0_BCRERRRSTEN(self)
        self.zz_fdict['BCRERRRSTEN'] = self.BCRERRRSTEN
        self.BCRFBBYP = RM_Field_MODEM_NS_BCRCTRL0_BCRFBBYP(self)
        self.zz_fdict['BCRFBBYP'] = self.BCRFBBYP
        self.BCRALIGN = RM_Field_MODEM_NS_BCRCTRL0_BCRALIGN(self)
        self.zz_fdict['BCRALIGN'] = self.BCRALIGN
        self.DISTOGG = RM_Field_MODEM_NS_BCRCTRL0_DISTOGG(self)
        self.zz_fdict['DISTOGG'] = self.DISTOGG
        self.CRSLOW = RM_Field_MODEM_NS_BCRCTRL0_CRSLOW(self)
        self.zz_fdict['CRSLOW'] = self.CRSLOW
        self.CRFAST = RM_Field_MODEM_NS_BCRCTRL0_CRFAST(self)
        self.zz_fdict['CRFAST'] = self.CRFAST
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRCTRL1, self).__init__(rmio, label,
            0xb8014000, 0x374,
            'BCRCTRL1', 'MODEM_NS.BCRCTRL1', 'read-write',
            u"",
            0x005E07FF, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CRGAIN = RM_Field_MODEM_NS_BCRCTRL1_CRGAIN(self)
        self.zz_fdict['CRGAIN'] = self.CRGAIN
        self.CGAINX2 = RM_Field_MODEM_NS_BCRCTRL1_CGAINX2(self)
        self.zz_fdict['CGAINX2'] = self.CGAINX2
        self.RXNCOCOMP = RM_Field_MODEM_NS_BCRCTRL1_RXNCOCOMP(self)
        self.zz_fdict['RXNCOCOMP'] = self.RXNCOCOMP
        self.RXCOMPLAT = RM_Field_MODEM_NS_BCRCTRL1_RXCOMPLAT(self)
        self.zz_fdict['RXCOMPLAT'] = self.RXCOMPLAT
        self.ESCMIDPT = RM_Field_MODEM_NS_BCRCTRL1_ESCMIDPT(self)
        self.zz_fdict['ESCMIDPT'] = self.ESCMIDPT
        self.DISMIDPT = RM_Field_MODEM_NS_BCRCTRL1_DISMIDPT(self)
        self.zz_fdict['DISMIDPT'] = self.DISMIDPT
        self.BCROSR = RM_Field_MODEM_NS_BCRCTRL1_BCROSR(self)
        self.zz_fdict['BCROSR'] = self.BCROSR
        self.ESTOSREN = RM_Field_MODEM_NS_BCRCTRL1_ESTOSREN(self)
        self.zz_fdict['ESTOSREN'] = self.ESTOSREN
        self.BCRSWSYCW = RM_Field_MODEM_NS_BCRCTRL1_BCRSWSYCW(self)
        self.zz_fdict['BCRSWSYCW'] = self.BCRSWSYCW
        self.PHCOMP2FSK = RM_Field_MODEM_NS_BCRCTRL1_PHCOMP2FSK(self)
        self.zz_fdict['PHCOMP2FSK'] = self.PHCOMP2FSK
        self.SLICEFBBYP = RM_Field_MODEM_NS_BCRCTRL1_SLICEFBBYP(self)
        self.zz_fdict['SLICEFBBYP'] = self.SLICEFBBYP
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODCTRL, self).__init__(rmio, label,
            0xb8014000, 0x378,
            'BCRDEMODCTRL', 'MODEM_NS.BCRDEMODCTRL', 'read-write',
            u"",
            0x06892100, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BCRDEMODEN = RM_Field_MODEM_NS_BCRDEMODCTRL_BCRDEMODEN(self)
        self.zz_fdict['BCRDEMODEN'] = self.BCRDEMODEN
        self.PULCORRBYP = RM_Field_MODEM_NS_BCRDEMODCTRL_PULCORRBYP(self)
        self.zz_fdict['PULCORRBYP'] = self.PULCORRBYP
        self.RAWSYN = RM_Field_MODEM_NS_BCRDEMODCTRL_RAWSYN(self)
        self.zz_fdict['RAWSYN'] = self.RAWSYN
        self.CONSCHKBYP = RM_Field_MODEM_NS_BCRDEMODCTRL_CONSCHKBYP(self)
        self.zz_fdict['CONSCHKBYP'] = self.CONSCHKBYP
        self.PH0SIZE = RM_Field_MODEM_NS_BCRDEMODCTRL_PH0SIZE(self)
        self.zz_fdict['PH0SIZE'] = self.PH0SIZE
        self.LOCKUPBYP = RM_Field_MODEM_NS_BCRDEMODCTRL_LOCKUPBYP(self)
        self.zz_fdict['LOCKUPBYP'] = self.LOCKUPBYP
        self.RAWFASTMA = RM_Field_MODEM_NS_BCRDEMODCTRL_RAWFASTMA(self)
        self.zz_fdict['RAWFASTMA'] = self.RAWFASTMA
        self.SPIKEREMOV = RM_Field_MODEM_NS_BCRDEMODCTRL_SPIKEREMOV(self)
        self.zz_fdict['SPIKEREMOV'] = self.SPIKEREMOV
        self.RAWFLTSEL = RM_Field_MODEM_NS_BCRDEMODCTRL_RAWFLTSEL(self)
        self.zz_fdict['RAWFLTSEL'] = self.RAWFLTSEL
        self.MANCHDLY = RM_Field_MODEM_NS_BCRDEMODCTRL_MANCHDLY(self)
        self.zz_fdict['MANCHDLY'] = self.MANCHDLY
        self.CICDINSCALE = RM_Field_MODEM_NS_BCRDEMODCTRL_CICDINSCALE(self)
        self.zz_fdict['CICDINSCALE'] = self.CICDINSCALE
        self.DATAFLTBY = RM_Field_MODEM_NS_BCRDEMODCTRL_DATAFLTBY(self)
        self.zz_fdict['DATAFLTBY'] = self.DATAFLTBY
        self.RSTEXTEN = RM_Field_MODEM_NS_BCRDEMODCTRL_RSTEXTEN(self)
        self.zz_fdict['RSTEXTEN'] = self.RSTEXTEN
        self.PREATH = RM_Field_MODEM_NS_BCRDEMODCTRL_PREATH(self)
        self.zz_fdict['PREATH'] = self.PREATH
        self.SKIPSYN = RM_Field_MODEM_NS_BCRDEMODCTRL_SKIPSYN(self)
        self.zz_fdict['SKIPSYN'] = self.SKIPSYN
        self.PMPATTERN = RM_Field_MODEM_NS_BCRDEMODCTRL_PMPATTERN(self)
        self.zz_fdict['PMPATTERN'] = self.PMPATTERN
        self.NONSTDPK = RM_Field_MODEM_NS_BCRDEMODCTRL_NONSTDPK(self)
        self.zz_fdict['NONSTDPK'] = self.NONSTDPK
        self.SLICERFAST = RM_Field_MODEM_NS_BCRDEMODCTRL_SLICERFAST(self)
        self.zz_fdict['SLICERFAST'] = self.SLICERFAST
        self.DIRECTMODE = RM_Field_MODEM_NS_BCRDEMODCTRL_DIRECTMODE(self)
        self.zz_fdict['DIRECTMODE'] = self.DIRECTMODE
        self.DETECTORSEL = RM_Field_MODEM_NS_BCRDEMODCTRL_DETECTORSEL(self)
        self.zz_fdict['DETECTORSEL'] = self.DETECTORSEL
        self.BBPMDETEN = RM_Field_MODEM_NS_BCRDEMODCTRL_BBPMDETEN(self)
        self.zz_fdict['BBPMDETEN'] = self.BBPMDETEN
        self.MANCHPH = RM_Field_MODEM_NS_BCRDEMODCTRL_MANCHPH(self)
        self.zz_fdict['MANCHPH'] = self.MANCHPH
        self.INVRXBIT = RM_Field_MODEM_NS_BCRDEMODCTRL_INVRXBIT(self)
        self.zz_fdict['INVRXBIT'] = self.INVRXBIT
        self.PHSRCSEL = RM_Field_MODEM_NS_BCRDEMODCTRL_PHSRCSEL(self)
        self.zz_fdict['PHSRCSEL'] = self.PHSRCSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODOOK(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODOOK, self).__init__(rmio, label,
            0xb8014000, 0x37C,
            'BCRDEMODOOK', 'MODEM_NS.BCRDEMODOOK', 'read-write',
            u"",
            0x00A00C03, 0xFFFFFFEF,
            0x00001000, 0x00002000,
            0x00003000)

        self.OOKFRZEN = RM_Field_MODEM_NS_BCRDEMODOOK_OOKFRZEN(self)
        self.zz_fdict['OOKFRZEN'] = self.OOKFRZEN
        self.RAWGAIN = RM_Field_MODEM_NS_BCRDEMODOOK_RAWGAIN(self)
        self.zz_fdict['RAWGAIN'] = self.RAWGAIN
        self.NOISEFLEST = RM_Field_MODEM_NS_BCRDEMODOOK_NOISEFLEST(self)
        self.zz_fdict['NOISEFLEST'] = self.NOISEFLEST
        self.PKTRUNK = RM_Field_MODEM_NS_BCRDEMODOOK_PKTRUNK(self)
        self.zz_fdict['PKTRUNK'] = self.PKTRUNK
        self.MAFREQDWN = RM_Field_MODEM_NS_BCRDEMODOOK_MAFREQDWN(self)
        self.zz_fdict['MAFREQDWN'] = self.MAFREQDWN
        self.SQUELCLKEN = RM_Field_MODEM_NS_BCRDEMODOOK_SQUELCLKEN(self)
        self.zz_fdict['SQUELCLKEN'] = self.SQUELCLKEN
        self.BWPK = RM_Field_MODEM_NS_BCRDEMODOOK_BWPK(self)
        self.zz_fdict['BWPK'] = self.BWPK
        self.ABPK = RM_Field_MODEM_NS_BCRDEMODOOK_ABPK(self)
        self.zz_fdict['ABPK'] = self.ABPK
        self.DECAYSWAL = RM_Field_MODEM_NS_BCRDEMODOOK_DECAYSWAL(self)
        self.zz_fdict['DECAYSWAL'] = self.DECAYSWAL
        self.DECAY = RM_Field_MODEM_NS_BCRDEMODOOK_DECAY(self)
        self.zz_fdict['DECAY'] = self.DECAY
        self.ATTACK = RM_Field_MODEM_NS_BCRDEMODOOK_ATTACK(self)
        self.zz_fdict['ATTACK'] = self.ATTACK
        self.SQUELCH = RM_Field_MODEM_NS_BCRDEMODOOK_SQUELCH(self)
        self.zz_fdict['SQUELCH'] = self.SQUELCH
        self.RAWNDEC = RM_Field_MODEM_NS_BCRDEMODOOK_RAWNDEC(self)
        self.zz_fdict['RAWNDEC'] = self.RAWNDEC
        self.BCRDEMODOOK = RM_Field_MODEM_NS_BCRDEMODOOK_BCRDEMODOOK(self)
        self.zz_fdict['BCRDEMODOOK'] = self.BCRDEMODOOK
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODAFC0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODAFC0, self).__init__(rmio, label,
            0xb8014000, 0x380,
            'BCRDEMODAFC0', 'MODEM_NS.BCRDEMODAFC0', 'read-write',
            u"",
            0x40000000, 0xE000807F,
            0x00001000, 0x00002000,
            0x00003000)

        self.ZEROOFF = RM_Field_MODEM_NS_BCRDEMODAFC0_ZEROOFF(self)
        self.zz_fdict['ZEROOFF'] = self.ZEROOFF
        self.LARGEFREQERR = RM_Field_MODEM_NS_BCRDEMODAFC0_LARGEFREQERR(self)
        self.zz_fdict['LARGEFREQERR'] = self.LARGEFREQERR
        self.AFCGAINOVRFLW = RM_Field_MODEM_NS_BCRDEMODAFC0_AFCGAINOVRFLW(self)
        self.zz_fdict['AFCGAINOVRFLW'] = self.AFCGAINOVRFLW
        self.EN2TBEST = RM_Field_MODEM_NS_BCRDEMODAFC0_EN2TBEST(self)
        self.zz_fdict['EN2TBEST'] = self.EN2TBEST
        self.ENAFCCLKSW = RM_Field_MODEM_NS_BCRDEMODAFC0_ENAFCCLKSW(self)
        self.zz_fdict['ENAFCCLKSW'] = self.ENAFCCLKSW
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODAFC1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODAFC1, self).__init__(rmio, label,
            0xb8014000, 0x384,
            'BCRDEMODAFC1', 'MODEM_NS.BCRDEMODAFC1', 'read-write',
            u"",
            0x10100012, 0xFFFCC0FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LGWAIT = RM_Field_MODEM_NS_BCRDEMODAFC1_LGWAIT(self)
        self.zz_fdict['LGWAIT'] = self.LGWAIT
        self.SHWAIT = RM_Field_MODEM_NS_BCRDEMODAFC1_SHWAIT(self)
        self.zz_fdict['SHWAIT'] = self.SHWAIT
        self.GEARSW = RM_Field_MODEM_NS_BCRDEMODAFC1_GEARSW(self)
        self.zz_fdict['GEARSW'] = self.GEARSW
        self.AFCMAEN = RM_Field_MODEM_NS_BCRDEMODAFC1_AFCMAEN(self)
        self.zz_fdict['AFCMAEN'] = self.AFCMAEN
        self.ENFZPMEND = RM_Field_MODEM_NS_BCRDEMODAFC1_ENFZPMEND(self)
        self.zz_fdict['ENFZPMEND'] = self.ENFZPMEND
        self.NONFRZEN = RM_Field_MODEM_NS_BCRDEMODAFC1_NONFRZEN(self)
        self.zz_fdict['NONFRZEN'] = self.NONFRZEN
        self.ONESHOTWAITCNT = RM_Field_MODEM_NS_BCRDEMODAFC1_ONESHOTWAITCNT(self)
        self.zz_fdict['ONESHOTWAITCNT'] = self.ONESHOTWAITCNT
        self.ONESHOTAFCEN = RM_Field_MODEM_NS_BCRDEMODAFC1_ONESHOTAFCEN(self)
        self.zz_fdict['ONESHOTAFCEN'] = self.ONESHOTAFCEN
        self.SKIPPMDET = RM_Field_MODEM_NS_BCRDEMODAFC1_SKIPPMDET(self)
        self.zz_fdict['SKIPPMDET'] = self.SKIPPMDET
        self.PMRSTEN = RM_Field_MODEM_NS_BCRDEMODAFC1_PMRSTEN(self)
        self.zz_fdict['PMRSTEN'] = self.PMRSTEN
        self.ENAFCFRZ = RM_Field_MODEM_NS_BCRDEMODAFC1_ENAFCFRZ(self)
        self.zz_fdict['ENAFCFRZ'] = self.ENAFCFRZ
        self.HALFPHCOMP = RM_Field_MODEM_NS_BCRDEMODAFC1_HALFPHCOMP(self)
        self.zz_fdict['HALFPHCOMP'] = self.HALFPHCOMP
        self.ENAFC = RM_Field_MODEM_NS_BCRDEMODAFC1_ENAFC(self)
        self.zz_fdict['ENAFC'] = self.ENAFC
        self.ENFBPLL = RM_Field_MODEM_NS_BCRDEMODAFC1_ENFBPLL(self)
        self.zz_fdict['ENFBPLL'] = self.ENFBPLL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMOD4FSK0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMOD4FSK0, self).__init__(rmio, label,
            0xb8014000, 0x388,
            'BCRDEMOD4FSK0', 'MODEM_NS.BCRDEMOD4FSK0', 'read-write',
            u"",
            0x00B4299A, 0xC0FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.THD4GFSK = RM_Field_MODEM_NS_BCRDEMOD4FSK0_THD4GFSK(self)
        self.zz_fdict['THD4GFSK'] = self.THD4GFSK
        self.CODE4GFSK = RM_Field_MODEM_NS_BCRDEMOD4FSK0_CODE4GFSK(self)
        self.zz_fdict['CODE4GFSK'] = self.CODE4GFSK
        self.PHCOMPBYP = RM_Field_MODEM_NS_BCRDEMOD4FSK0_PHCOMPBYP(self)
        self.zz_fdict['PHCOMPBYP'] = self.PHCOMPBYP
        self.EN4GFSK = RM_Field_MODEM_NS_BCRDEMOD4FSK0_EN4GFSK(self)
        self.zz_fdict['EN4GFSK'] = self.EN4GFSK
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMOD4FSK1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMOD4FSK1, self).__init__(rmio, label,
            0xb8014000, 0x38C,
            'BCRDEMOD4FSK1', 'MODEM_NS.BCRDEMOD4FSK1', 'read-write',
            u"",
            0x00000B1C, 0xC0FF7F7F,
            0x00001000, 0x00002000,
            0x00003000)

        self.PHCOMP4FSK0 = RM_Field_MODEM_NS_BCRDEMOD4FSK1_PHCOMP4FSK0(self)
        self.zz_fdict['PHCOMP4FSK0'] = self.PHCOMP4FSK0
        self.PHCOMP4FSK1 = RM_Field_MODEM_NS_BCRDEMOD4FSK1_PHCOMP4FSK1(self)
        self.zz_fdict['PHCOMP4FSK1'] = self.PHCOMP4FSK1
        self.FDEVCOMPRATIO = RM_Field_MODEM_NS_BCRDEMOD4FSK1_FDEVCOMPRATIO(self)
        self.zz_fdict['FDEVCOMPRATIO'] = self.FDEVCOMPRATIO
        self.FDEVCOMPEN = RM_Field_MODEM_NS_BCRDEMOD4FSK1_FDEVCOMPEN(self)
        self.zz_fdict['FDEVCOMPEN'] = self.FDEVCOMPEN
        self.S2PMAP = RM_Field_MODEM_NS_BCRDEMOD4FSK1_S2PMAP(self)
        self.zz_fdict['S2PMAP'] = self.S2PMAP
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODANT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODANT, self).__init__(rmio, label,
            0xb8014000, 0x390,
            'BCRDEMODANT', 'MODEM_NS.BCRDEMODANT', 'read-write',
            u"",
            0x10020000, 0x9FFF97E0,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWANTTIMER = RM_Field_MODEM_NS_BCRDEMODANT_SWANTTIMER(self)
        self.zz_fdict['SWANTTIMER'] = self.SWANTTIMER
        self.BECOEN = RM_Field_MODEM_NS_BCRDEMODANT_BECOEN(self)
        self.zz_fdict['BECOEN'] = self.BECOEN
        self.SKIP2PHTHD = RM_Field_MODEM_NS_BCRDEMODANT_SKIP2PHTHD(self)
        self.zz_fdict['SKIP2PHTHD'] = self.SKIP2PHTHD
        self.ANWAIT = RM_Field_MODEM_NS_BCRDEMODANT_ANWAIT(self)
        self.zz_fdict['ANWAIT'] = self.ANWAIT
        self.AGCGAINUPB = RM_Field_MODEM_NS_BCRDEMODANT_AGCGAINUPB(self)
        self.zz_fdict['AGCGAINUPB'] = self.AGCGAINUPB
        self.SKIP2PH = RM_Field_MODEM_NS_BCRDEMODANT_SKIP2PH(self)
        self.zz_fdict['SKIP2PH'] = self.SKIP2PH
        self.BYP1P5 = RM_Field_MODEM_NS_BCRDEMODANT_BYP1P5(self)
        self.zz_fdict['BYP1P5'] = self.BYP1P5
        self.ANT2PMTHD = RM_Field_MODEM_NS_BCRDEMODANT_ANT2PMTHD(self)
        self.zz_fdict['ANT2PMTHD'] = self.ANT2PMTHD
        self.BCRDEMODANTDIV = RM_Field_MODEM_NS_BCRDEMODANT_BCRDEMODANTDIV(self)
        self.zz_fdict['BCRDEMODANTDIV'] = self.BCRDEMODANTDIV
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODRSSI(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODRSSI, self).__init__(rmio, label,
            0xb8014000, 0x394,
            'BCRDEMODRSSI', 'MODEM_NS.BCRDEMODRSSI', 'read-write',
            u"",
            0x60000020, 0xFE001DFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RSSIARRTHD = RM_Field_MODEM_NS_BCRDEMODRSSI_RSSIARRTHD(self)
        self.zz_fdict['RSSIARRTHD'] = self.RSSIARRTHD
        self.RSSIMATAP = RM_Field_MODEM_NS_BCRDEMODRSSI_RSSIMATAP(self)
        self.zz_fdict['RSSIMATAP'] = self.RSSIMATAP
        self.MUTERSSICNT = RM_Field_MODEM_NS_BCRDEMODRSSI_MUTERSSICNT(self)
        self.zz_fdict['MUTERSSICNT'] = self.MUTERSSICNT
        self.PRWOFFSET = RM_Field_MODEM_NS_BCRDEMODRSSI_PRWOFFSET(self)
        self.zz_fdict['PRWOFFSET'] = self.PRWOFFSET
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODARR0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODARR0, self).__init__(rmio, label,
            0xb8014000, 0x398,
            'BCRDEMODARR0', 'MODEM_NS.BCRDEMODARR0', 'read-write',
            u"",
            0x00600026, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCHPRDLO = RM_Field_MODEM_NS_BCRDEMODARR0_SCHPRDLO(self)
        self.zz_fdict['SCHPRDLO'] = self.SCHPRDLO
        self.EYEQUALEN = RM_Field_MODEM_NS_BCRDEMODARR0_EYEQUALEN(self)
        self.zz_fdict['EYEQUALEN'] = self.EYEQUALEN
        self.SCHPRDHI = RM_Field_MODEM_NS_BCRDEMODARR0_SCHPRDHI(self)
        self.zz_fdict['SCHPRDHI'] = self.SCHPRDHI
        self.ARRRSTEN = RM_Field_MODEM_NS_BCRDEMODARR0_ARRRSTEN(self)
        self.zz_fdict['ARRRSTEN'] = self.ARRRSTEN
        self.ARRTOLER = RM_Field_MODEM_NS_BCRDEMODARR0_ARRTOLER(self)
        self.zz_fdict['ARRTOLER'] = self.ARRTOLER
        self.DIFF0RSTEN = RM_Field_MODEM_NS_BCRDEMODARR0_DIFF0RSTEN(self)
        self.zz_fdict['DIFF0RSTEN'] = self.DIFF0RSTEN
        self.PHSPIKETHD = RM_Field_MODEM_NS_BCRDEMODARR0_PHSPIKETHD(self)
        self.zz_fdict['PHSPIKETHD'] = self.PHSPIKETHD
        self.ARRDETTHD = RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETTHD(self)
        self.zz_fdict['ARRDETTHD'] = self.ARRDETTHD
        self.SCHFRZEN = RM_Field_MODEM_NS_BCRDEMODARR0_SCHFRZEN(self)
        self.zz_fdict['SCHFRZEN'] = self.SCHFRZEN
        self.EYEXESTEN = RM_Field_MODEM_NS_BCRDEMODARR0_EYEXESTEN(self)
        self.zz_fdict['EYEXESTEN'] = self.EYEXESTEN
        self.EYEXESTFAST = RM_Field_MODEM_NS_BCRDEMODARR0_EYEXESTFAST(self)
        self.zz_fdict['EYEXESTFAST'] = self.EYEXESTFAST
        self.ARRDETSRC = RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETSRC(self)
        self.zz_fdict['ARRDETSRC'] = self.ARRDETSRC
        self.ARRQPM = RM_Field_MODEM_NS_BCRDEMODARR0_ARRQPM(self)
        self.zz_fdict['ARRQPM'] = self.ARRQPM
        self.ARRDETEN = RM_Field_MODEM_NS_BCRDEMODARR0_ARRDETEN(self)
        self.zz_fdict['ARRDETEN'] = self.ARRDETEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODARR1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODARR1, self).__init__(rmio, label,
            0xb8014000, 0x39C,
            'BCRDEMODARR1', 'MODEM_NS.BCRDEMODARR1', 'read-write',
            u"",
            0x80000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ARREYEQUAL = RM_Field_MODEM_NS_BCRDEMODARR1_ARREYEQUAL(self)
        self.zz_fdict['ARREYEQUAL'] = self.ARREYEQUAL
        self.EYEOPENTHD = RM_Field_MODEM_NS_BCRDEMODARR1_EYEOPENTHD(self)
        self.zz_fdict['EYEOPENTHD'] = self.EYEOPENTHD
        self.SYMBWMAX = RM_Field_MODEM_NS_BCRDEMODARR1_SYMBWMAX(self)
        self.zz_fdict['SYMBWMAX'] = self.SYMBWMAX
        self.SYMBWMIN = RM_Field_MODEM_NS_BCRDEMODARR1_SYMBWMIN(self)
        self.zz_fdict['SYMBWMIN'] = self.SYMBWMIN
        self.BCRCFESRC = RM_Field_MODEM_NS_BCRDEMODARR1_BCRCFESRC(self)
        self.zz_fdict['BCRCFESRC'] = self.BCRCFESRC
        self.CFEQUALTHD = RM_Field_MODEM_NS_BCRDEMODARR1_CFEQUALTHD(self)
        self.zz_fdict['CFEQUALTHD'] = self.CFEQUALTHD
        self.KSICOMPEN = RM_Field_MODEM_NS_BCRDEMODARR1_KSICOMPEN(self)
        self.zz_fdict['KSICOMPEN'] = self.KSICOMPEN
        self.ENCFEQUAL = RM_Field_MODEM_NS_BCRDEMODARR1_ENCFEQUAL(self)
        self.zz_fdict['ENCFEQUAL'] = self.ENCFEQUAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODARR2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODARR2, self).__init__(rmio, label,
            0xb8014000, 0x3A0,
            'BCRDEMODARR2', 'MODEM_NS.BCRDEMODARR2', 'read-write',
            u"",
            0x00000000, 0x8000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.CONSYMOL = RM_Field_MODEM_NS_BCRDEMODARR2_CONSYMOL(self)
        self.zz_fdict['CONSYMOL'] = self.CONSYMOL
        self.RAWDCHKALWAYON = RM_Field_MODEM_NS_BCRDEMODARR2_RAWDCHKALWAYON(self)
        self.zz_fdict['RAWDCHKALWAYON'] = self.RAWDCHKALWAYON
        self.OUTRNGCHK = RM_Field_MODEM_NS_BCRDEMODARR2_OUTRNGCHK(self)
        self.zz_fdict['OUTRNGCHK'] = self.OUTRNGCHK
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODKSI(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODKSI, self).__init__(rmio, label,
            0xb8014000, 0x3A4,
            'BCRDEMODKSI', 'MODEM_NS.BCRDEMODKSI', 'read-write',
            u"",
            0x002C2020, 0x007F7F7F,
            0x00001000, 0x00002000,
            0x00003000)

        self.BCRKSI1 = RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI1(self)
        self.zz_fdict['BCRKSI1'] = self.BCRKSI1
        self.BCRKSI2 = RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI2(self)
        self.zz_fdict['BCRKSI2'] = self.BCRKSI2
        self.BCRKSI3 = RM_Field_MODEM_NS_BCRDEMODKSI_BCRKSI3(self)
        self.zz_fdict['BCRKSI3'] = self.BCRKSI3
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BCRDEMODPMEXP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BCRDEMODPMEXP, self).__init__(rmio, label,
            0xb8014000, 0x3A8,
            'BCRDEMODPMEXP', 'MODEM_NS.BCRDEMODPMEXP', 'read-write',
            u"",
            0x58965555, 0xFEFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BCRPMEXP = RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPMEXP(self)
        self.zz_fdict['BCRPMEXP'] = self.BCRPMEXP
        self.BCRCFECOSTTHD = RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRCFECOSTTHD(self)
        self.zz_fdict['BCRCFECOSTTHD'] = self.BCRCFECOSTTHD
        self.BCRPHSCALE = RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPHSCALE(self)
        self.zz_fdict['BCRPHSCALE'] = self.BCRPHSCALE
        self.BCRCFESCHWIN = RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRCFESCHWIN(self)
        self.zz_fdict['BCRCFESCHWIN'] = self.BCRCFESCHWIN
        self.BCRPMACQWIN = RM_Field_MODEM_NS_BCRDEMODPMEXP_BCRPMACQWIN(self)
        self.zz_fdict['BCRPMACQWIN'] = self.BCRPMACQWIN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMCTRL0, self).__init__(rmio, label,
            0xb8014000, 0x3B0,
            'HADMCTRL0', 'MODEM_NS.HADMCTRL0', 'read-write',
            u"",
            0x00000000, 0xFC00703F,
            0x00001000, 0x00002000,
            0x00003000)

        self.HADMEN = RM_Field_MODEM_NS_HADMCTRL0_HADMEN(self)
        self.zz_fdict['HADMEN'] = self.HADMEN
        self.TESEN = RM_Field_MODEM_NS_HADMCTRL0_TESEN(self)
        self.zz_fdict['TESEN'] = self.TESEN
        self.PESEN = RM_Field_MODEM_NS_HADMCTRL0_PESEN(self)
        self.zz_fdict['PESEN'] = self.PESEN
        self.SNDSEQEN = RM_Field_MODEM_NS_HADMCTRL0_SNDSEQEN(self)
        self.zz_fdict['SNDSEQEN'] = self.SNDSEQEN
        self.ROLE = RM_Field_MODEM_NS_HADMCTRL0_ROLE(self)
        self.zz_fdict['ROLE'] = self.ROLE
        self.RTTPHY = RM_Field_MODEM_NS_HADMCTRL0_RTTPHY(self)
        self.zz_fdict['RTTPHY'] = self.RTTPHY
        self.PM = RM_Field_MODEM_NS_HADMCTRL0_PM(self)
        self.zz_fdict['PM'] = self.PM
        self.AVGMODE = RM_Field_MODEM_NS_HADMCTRL0_AVGMODE(self)
        self.zz_fdict['AVGMODE'] = self.AVGMODE
        self.DFTSCALE = RM_Field_MODEM_NS_HADMCTRL0_DFTSCALE(self)
        self.zz_fdict['DFTSCALE'] = self.DFTSCALE
        self.PKTSENTSEL = RM_Field_MODEM_NS_HADMCTRL0_PKTSENTSEL(self)
        self.zz_fdict['PKTSENTSEL'] = self.PKTSENTSEL
        self.TXUPSAMPOSR4 = RM_Field_MODEM_NS_HADMCTRL0_TXUPSAMPOSR4(self)
        self.zz_fdict['TXUPSAMPOSR4'] = self.TXUPSAMPOSR4
        self.SSAFCGEAR = RM_Field_MODEM_NS_HADMCTRL0_SSAFCGEAR(self)
        self.zz_fdict['SSAFCGEAR'] = self.SSAFCGEAR
        self.SRC2AUTOSCALE = RM_Field_MODEM_NS_HADMCTRL0_SRC2AUTOSCALE(self)
        self.zz_fdict['SRC2AUTOSCALE'] = self.SRC2AUTOSCALE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMCTRL1, self).__init__(rmio, label,
            0xb8014000, 0x3B4,
            'HADMCTRL1', 'MODEM_NS.HADMCTRL1', 'read-write',
            u"",
            0x00040000, 0xFFC7FF07,
            0x00001000, 0x00002000,
            0x00003000)

        self.STEPSTATE = RM_Field_MODEM_NS_HADMCTRL1_STEPSTATE(self)
        self.zz_fdict['STEPSTATE'] = self.STEPSTATE
        self.DFTSTARTOFF = RM_Field_MODEM_NS_HADMCTRL1_DFTSTARTOFF(self)
        self.zz_fdict['DFTSTARTOFF'] = self.DFTSTARTOFF
        self.MAXSCHWIN = RM_Field_MODEM_NS_HADMCTRL1_MAXSCHWIN(self)
        self.zz_fdict['MAXSCHWIN'] = self.MAXSCHWIN
        self.AVGSTARTOFF = RM_Field_MODEM_NS_HADMCTRL1_AVGSTARTOFF(self)
        self.zz_fdict['AVGSTARTOFF'] = self.AVGSTARTOFF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMSTATUS0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMSTATUS0, self).__init__(rmio, label,
            0xb8014000, 0x3B8,
            'HADMSTATUS0', 'MODEM_NS.HADMSTATUS0', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AVG0 = RM_Field_MODEM_NS_HADMSTATUS0_AVG0(self)
        self.zz_fdict['AVG0'] = self.AVG0
        self.AVG1 = RM_Field_MODEM_NS_HADMSTATUS0_AVG1(self)
        self.zz_fdict['AVG1'] = self.AVG1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMSTATUS1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMSTATUS1, self).__init__(rmio, label,
            0xb8014000, 0x3BC,
            'HADMSTATUS1', 'MODEM_NS.HADMSTATUS1', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FREQOFFSET = RM_Field_MODEM_NS_HADMSTATUS1_FREQOFFSET(self)
        self.zz_fdict['FREQOFFSET'] = self.FREQOFFSET
        self.TIMETOX = RM_Field_MODEM_NS_HADMSTATUS1_TIMETOX(self)
        self.zz_fdict['TIMETOX'] = self.TIMETOX
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMSTATUS2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMSTATUS2, self).__init__(rmio, label,
            0xb8014000, 0x3C0,
            'HADMSTATUS2', 'MODEM_NS.HADMSTATUS2', 'read-only',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COSTLATE1 = RM_Field_MODEM_NS_HADMSTATUS2_COSTLATE1(self)
        self.zz_fdict['COSTLATE1'] = self.COSTLATE1
        self.COSTCURR1 = RM_Field_MODEM_NS_HADMSTATUS2_COSTCURR1(self)
        self.zz_fdict['COSTCURR1'] = self.COSTCURR1
        self.COSTEARL1 = RM_Field_MODEM_NS_HADMSTATUS2_COSTEARL1(self)
        self.zz_fdict['COSTEARL1'] = self.COSTEARL1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMSTATUS3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMSTATUS3, self).__init__(rmio, label,
            0xb8014000, 0x3C4,
            'HADMSTATUS3', 'MODEM_NS.HADMSTATUS3', 'read-only',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COSTLATE0 = RM_Field_MODEM_NS_HADMSTATUS3_COSTLATE0(self)
        self.zz_fdict['COSTLATE0'] = self.COSTLATE0
        self.COSTCURR0 = RM_Field_MODEM_NS_HADMSTATUS3_COSTCURR0(self)
        self.zz_fdict['COSTCURR0'] = self.COSTCURR0
        self.COSTEARL0 = RM_Field_MODEM_NS_HADMSTATUS3_COSTEARL0(self)
        self.zz_fdict['COSTEARL0'] = self.COSTEARL0
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMSTATUS4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMSTATUS4, self).__init__(rmio, label,
            0xb8014000, 0x3C8,
            'HADMSTATUS4', 'MODEM_NS.HADMSTATUS4', 'read-only',
            u"",
            0x00000000, 0x7FFF7FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SBSP500I = RM_Field_MODEM_NS_HADMSTATUS4_SBSP500I(self)
        self.zz_fdict['SBSP500I'] = self.SBSP500I
        self.SBSP500Q = RM_Field_MODEM_NS_HADMSTATUS4_SBSP500Q(self)
        self.zz_fdict['SBSP500Q'] = self.SBSP500Q
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMSTATUS5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMSTATUS5, self).__init__(rmio, label,
            0xb8014000, 0x3CC,
            'HADMSTATUS5', 'MODEM_NS.HADMSTATUS5', 'read-only',
            u"",
            0x00000000, 0x7FFF7FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SBSM500I = RM_Field_MODEM_NS_HADMSTATUS5_SBSM500I(self)
        self.zz_fdict['SBSM500I'] = self.SBSM500I
        self.SBSM500Q = RM_Field_MODEM_NS_HADMSTATUS5_SBSM500Q(self)
        self.zz_fdict['SBSM500Q'] = self.SBSM500Q
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_HADMSTATUS6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_HADMSTATUS6, self).__init__(rmio, label,
            0xb8014000, 0x3D0,
            'HADMSTATUS6', 'MODEM_NS.HADMSTATUS6', 'read-only',
            u"",
            0x00000000, 0xFFF0FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FREQMEAS = RM_Field_MODEM_NS_HADMSTATUS6_FREQMEAS(self)
        self.zz_fdict['FREQMEAS'] = self.FREQMEAS
        self.SBSPSCALE = RM_Field_MODEM_NS_HADMSTATUS6_SBSPSCALE(self)
        self.zz_fdict['SBSPSCALE'] = self.SBSPSCALE
        self.SBSMSCALE = RM_Field_MODEM_NS_HADMSTATUS6_SBSMSCALE(self)
        self.zz_fdict['SBSMSCALE'] = self.SBSMSCALE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TXCORR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TXCORR, self).__init__(rmio, label,
            0xb8014000, 0x3F0,
            'TXCORR', 'MODEM_NS.TXCORR', 'read-write',
            u"",
            0x00000000, 0x07FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXDGAIN6DB = RM_Field_MODEM_NS_TXCORR_TXDGAIN6DB(self)
        self.zz_fdict['TXDGAIN6DB'] = self.TXDGAIN6DB
        self.TXDGAIN = RM_Field_MODEM_NS_TXCORR_TXDGAIN(self)
        self.zz_fdict['TXDGAIN'] = self.TXDGAIN
        self.TXGAINIMB = RM_Field_MODEM_NS_TXCORR_TXGAINIMB(self)
        self.zz_fdict['TXGAINIMB'] = self.TXGAINIMB
        self.TXPHSIMB = RM_Field_MODEM_NS_TXCORR_TXPHSIMB(self)
        self.zz_fdict['TXPHSIMB'] = self.TXPHSIMB
        self.TXFREQCORR = RM_Field_MODEM_NS_TXCORR_TXFREQCORR(self)
        self.zz_fdict['TXFREQCORR'] = self.TXFREQCORR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TXMISC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TXMISC, self).__init__(rmio, label,
            0xb8014000, 0x3F4,
            'TXMISC', 'MODEM_NS.TXMISC', 'read-write',
            u"",
            0x0000000E, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FORCECLKEN = RM_Field_MODEM_NS_TXMISC_FORCECLKEN(self)
        self.zz_fdict['FORCECLKEN'] = self.FORCECLKEN
        self.TXIQIMBEN = RM_Field_MODEM_NS_TXMISC_TXIQIMBEN(self)
        self.zz_fdict['TXIQIMBEN'] = self.TXIQIMBEN
        self.TXINTPEN = RM_Field_MODEM_NS_TXMISC_TXINTPEN(self)
        self.zz_fdict['TXINTPEN'] = self.TXINTPEN
        self.TXDSEN = RM_Field_MODEM_NS_TXMISC_TXDSEN(self)
        self.zz_fdict['TXDSEN'] = self.TXDSEN
        self.TXIQSWAP = RM_Field_MODEM_NS_TXMISC_TXIQSWAP(self)
        self.zz_fdict['TXIQSWAP'] = self.TXIQSWAP
        self.TXDACFORMAT = RM_Field_MODEM_NS_TXMISC_TXDACFORMAT(self)
        self.zz_fdict['TXDACFORMAT'] = self.TXDACFORMAT
        self.TXDACFORCE = RM_Field_MODEM_NS_TXMISC_TXDACFORCE(self)
        self.zz_fdict['TXDACFORCE'] = self.TXDACFORCE
        self.TXDCI = RM_Field_MODEM_NS_TXMISC_TXDCI(self)
        self.zz_fdict['TXDCI'] = self.TXDCI
        self.TXDCQ = RM_Field_MODEM_NS_TXMISC_TXDCQ(self)
        self.zz_fdict['TXDCQ'] = self.TXDCQ
        self.BR2M = RM_Field_MODEM_NS_TXMISC_BR2M(self)
        self.zz_fdict['BR2M'] = self.BR2M
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SPARE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SPARE, self).__init__(rmio, label,
            0xb8014000, 0x400,
            'SPARE', 'MODEM_NS.SPARE', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SPARE = RM_Field_MODEM_NS_SPARE_SPARE(self)
        self.zz_fdict['SPARE'] = self.SPARE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_EHDSSSCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_EHDSSSCTRL, self).__init__(rmio, label,
            0xb8014000, 0x404,
            'EHDSSSCTRL', 'MODEM_NS.EHDSSSCTRL', 'read-write',
            u"",
            0x000001DD, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.EHDSSSEN = RM_Field_MODEM_NS_EHDSSSCTRL_EHDSSSEN(self)
        self.zz_fdict['EHDSSSEN'] = self.EHDSSSEN
        self.DSSSTIMEACQUTHD = RM_Field_MODEM_NS_EHDSSSCTRL_DSSSTIMEACQUTHD(self)
        self.zz_fdict['DSSSTIMEACQUTHD'] = self.DSSSTIMEACQUTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_EHDSSSCFG0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_EHDSSSCFG0, self).__init__(rmio, label,
            0xb8014000, 0x408,
            'EHDSSSCFG0', 'MODEM_NS.EHDSSSCFG0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DSSSPATT = RM_Field_MODEM_NS_EHDSSSCFG0_DSSSPATT(self)
        self.zz_fdict['DSSSPATT'] = self.DSSSPATT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_EHDSSSCFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_EHDSSSCFG1, self).__init__(rmio, label,
            0xb8014000, 0x40C,
            'EHDSSSCFG1', 'MODEM_NS.EHDSSSCFG1', 'read-write',
            u"",
            0x3207D080, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DSSSEXPSYNCLEN = RM_Field_MODEM_NS_EHDSSSCFG1_DSSSEXPSYNCLEN(self)
        self.zz_fdict['DSSSEXPSYNCLEN'] = self.DSSSEXPSYNCLEN
        self.DSSSCORRTHD = RM_Field_MODEM_NS_EHDSSSCFG1_DSSSCORRTHD(self)
        self.zz_fdict['DSSSCORRTHD'] = self.DSSSCORRTHD
        self.DSSSDSAQTHD = RM_Field_MODEM_NS_EHDSSSCFG1_DSSSDSAQTHD(self)
        self.zz_fdict['DSSSDSAQTHD'] = self.DSSSDSAQTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_EHDSSSCFG2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_EHDSSSCFG2, self).__init__(rmio, label,
            0xb8014000, 0x410,
            'EHDSSSCFG2', 'MODEM_NS.EHDSSSCFG2', 'read-write',
            u"",
            0x356260FA, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DSSSTIMCORRTHD = RM_Field_MODEM_NS_EHDSSSCFG2_DSSSTIMCORRTHD(self)
        self.zz_fdict['DSSSTIMCORRTHD'] = self.DSSSTIMCORRTHD
        self.DSSSFRTCORRTHD = RM_Field_MODEM_NS_EHDSSSCFG2_DSSSFRTCORRTHD(self)
        self.zz_fdict['DSSSFRTCORRTHD'] = self.DSSSFRTCORRTHD
        self.DSSSTRACKINGWIN = RM_Field_MODEM_NS_EHDSSSCFG2_DSSSTRACKINGWIN(self)
        self.zz_fdict['DSSSTRACKINGWIN'] = self.DSSSTRACKINGWIN
        self.DSSSCORRSCHWIN = RM_Field_MODEM_NS_EHDSSSCFG2_DSSSCORRSCHWIN(self)
        self.zz_fdict['DSSSCORRSCHWIN'] = self.DSSSCORRSCHWIN
        self.ONESYMBOLMBDD = RM_Field_MODEM_NS_EHDSSSCFG2_ONESYMBOLMBDD(self)
        self.zz_fdict['ONESYMBOLMBDD'] = self.ONESYMBOLMBDD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP0, self).__init__(rmio, label,
            0xb8014000, 0x414,
            'SYMBOL2CHIP0', 'MODEM_NS.SYMBOL2CHIP0', 'read-write',
            u"",
            0xD9C3522E, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH0 = RM_Field_MODEM_NS_SYMBOL2CHIP0_SYM2CH0(self)
        self.zz_fdict['SYM2CH0'] = self.SYM2CH0
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP1, self).__init__(rmio, label,
            0xb8014000, 0x418,
            'SYMBOL2CHIP1', 'MODEM_NS.SYMBOL2CHIP1', 'read-write',
            u"",
            0xED9C3522, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH1 = RM_Field_MODEM_NS_SYMBOL2CHIP1_SYM2CH1(self)
        self.zz_fdict['SYM2CH1'] = self.SYM2CH1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP2, self).__init__(rmio, label,
            0xb8014000, 0x41C,
            'SYMBOL2CHIP2', 'MODEM_NS.SYMBOL2CHIP2', 'read-write',
            u"",
            0x2ED9C352, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH2 = RM_Field_MODEM_NS_SYMBOL2CHIP2_SYM2CH2(self)
        self.zz_fdict['SYM2CH2'] = self.SYM2CH2
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP3, self).__init__(rmio, label,
            0xb8014000, 0x420,
            'SYMBOL2CHIP3', 'MODEM_NS.SYMBOL2CHIP3', 'read-write',
            u"",
            0x22ED9C35, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH3 = RM_Field_MODEM_NS_SYMBOL2CHIP3_SYM2CH3(self)
        self.zz_fdict['SYM2CH3'] = self.SYM2CH3
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP4, self).__init__(rmio, label,
            0xb8014000, 0x424,
            'SYMBOL2CHIP4', 'MODEM_NS.SYMBOL2CHIP4', 'read-write',
            u"",
            0x522ED9C3, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH4 = RM_Field_MODEM_NS_SYMBOL2CHIP4_SYM2CH4(self)
        self.zz_fdict['SYM2CH4'] = self.SYM2CH4
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP5, self).__init__(rmio, label,
            0xb8014000, 0x428,
            'SYMBOL2CHIP5', 'MODEM_NS.SYMBOL2CHIP5', 'read-write',
            u"",
            0x3522ED9C, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH5 = RM_Field_MODEM_NS_SYMBOL2CHIP5_SYM2CH5(self)
        self.zz_fdict['SYM2CH5'] = self.SYM2CH5
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP6, self).__init__(rmio, label,
            0xb8014000, 0x42C,
            'SYMBOL2CHIP6', 'MODEM_NS.SYMBOL2CHIP6', 'read-write',
            u"",
            0xC3522ED9, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH6 = RM_Field_MODEM_NS_SYMBOL2CHIP6_SYM2CH6(self)
        self.zz_fdict['SYM2CH6'] = self.SYM2CH6
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP7, self).__init__(rmio, label,
            0xb8014000, 0x430,
            'SYMBOL2CHIP7', 'MODEM_NS.SYMBOL2CHIP7', 'read-write',
            u"",
            0x9C3522ED, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH7 = RM_Field_MODEM_NS_SYMBOL2CHIP7_SYM2CH7(self)
        self.zz_fdict['SYM2CH7'] = self.SYM2CH7
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP8, self).__init__(rmio, label,
            0xb8014000, 0x434,
            'SYMBOL2CHIP8', 'MODEM_NS.SYMBOL2CHIP8', 'read-write',
            u"",
            0x8C96077B, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH8 = RM_Field_MODEM_NS_SYMBOL2CHIP8_SYM2CH8(self)
        self.zz_fdict['SYM2CH8'] = self.SYM2CH8
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIP9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIP9, self).__init__(rmio, label,
            0xb8014000, 0x438,
            'SYMBOL2CHIP9', 'MODEM_NS.SYMBOL2CHIP9', 'read-write',
            u"",
            0xB8C96077, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CH9 = RM_Field_MODEM_NS_SYMBOL2CHIP9_SYM2CH9(self)
        self.zz_fdict['SYM2CH9'] = self.SYM2CH9
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIPA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIPA, self).__init__(rmio, label,
            0xb8014000, 0x43C,
            'SYMBOL2CHIPA', 'MODEM_NS.SYMBOL2CHIPA', 'read-write',
            u"",
            0x7B8C9607, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CHA = RM_Field_MODEM_NS_SYMBOL2CHIPA_SYM2CHA(self)
        self.zz_fdict['SYM2CHA'] = self.SYM2CHA
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIPB(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIPB, self).__init__(rmio, label,
            0xb8014000, 0x440,
            'SYMBOL2CHIPB', 'MODEM_NS.SYMBOL2CHIPB', 'read-write',
            u"",
            0x77B8C960, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CHB = RM_Field_MODEM_NS_SYMBOL2CHIPB_SYM2CHB(self)
        self.zz_fdict['SYM2CHB'] = self.SYM2CHB
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIPC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIPC, self).__init__(rmio, label,
            0xb8014000, 0x444,
            'SYMBOL2CHIPC', 'MODEM_NS.SYMBOL2CHIPC', 'read-write',
            u"",
            0x077B8C96, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CHC = RM_Field_MODEM_NS_SYMBOL2CHIPC_SYM2CHC(self)
        self.zz_fdict['SYM2CHC'] = self.SYM2CHC
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIPD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIPD, self).__init__(rmio, label,
            0xb8014000, 0x448,
            'SYMBOL2CHIPD', 'MODEM_NS.SYMBOL2CHIPD', 'read-write',
            u"",
            0x6077B8C9, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CHD = RM_Field_MODEM_NS_SYMBOL2CHIPD_SYM2CHD(self)
        self.zz_fdict['SYM2CHD'] = self.SYM2CHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIPE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIPE, self).__init__(rmio, label,
            0xb8014000, 0x44C,
            'SYMBOL2CHIPE', 'MODEM_NS.SYMBOL2CHIPE', 'read-write',
            u"",
            0x96077B8C, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CHE = RM_Field_MODEM_NS_SYMBOL2CHIPE_SYM2CHE(self)
        self.zz_fdict['SYM2CHE'] = self.SYM2CHE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYMBOL2CHIPF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYMBOL2CHIPF, self).__init__(rmio, label,
            0xb8014000, 0x450,
            'SYMBOL2CHIPF', 'MODEM_NS.SYMBOL2CHIPF', 'read-write',
            u"",
            0xC96077B8, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYM2CHF = RM_Field_MODEM_NS_SYMBOL2CHIPF_SYM2CHF(self)
        self.zz_fdict['SYM2CHF'] = self.SYM2CHF
        self.__dict__['zz_frozen'] = True



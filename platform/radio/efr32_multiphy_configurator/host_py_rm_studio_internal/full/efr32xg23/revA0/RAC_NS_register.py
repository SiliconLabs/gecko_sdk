
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . RAC_NS_field import *


class RM_Register_RAC_NS_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IPVERSION, self).__init__(rmio, label,
            0xb8020000, 0x000,
            'IPVERSION', 'RAC_NS.IPVERSION', 'read-only',
            u"",
            0x00000002, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_RAC_NS_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_EN, self).__init__(rmio, label,
            0xb8020000, 0x004,
            'EN', 'RAC_NS.EN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_RAC_NS_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RXENSRCEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RXENSRCEN, self).__init__(rmio, label,
            0xb8020000, 0x008,
            'RXENSRCEN', 'RAC_NS.RXENSRCEN', 'read-write',
            u"",
            0x00000000, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWRXEN = RM_Field_RAC_NS_RXENSRCEN_SWRXEN(self)
        self.zz_fdict['SWRXEN'] = self.SWRXEN
        self.CHANNELBUSYEN = RM_Field_RAC_NS_RXENSRCEN_CHANNELBUSYEN(self)
        self.zz_fdict['CHANNELBUSYEN'] = self.CHANNELBUSYEN
        self.TIMDETEN = RM_Field_RAC_NS_RXENSRCEN_TIMDETEN(self)
        self.zz_fdict['TIMDETEN'] = self.TIMDETEN
        self.PREDETEN = RM_Field_RAC_NS_RXENSRCEN_PREDETEN(self)
        self.zz_fdict['PREDETEN'] = self.PREDETEN
        self.FRAMEDETEN = RM_Field_RAC_NS_RXENSRCEN_FRAMEDETEN(self)
        self.zz_fdict['FRAMEDETEN'] = self.FRAMEDETEN
        self.DEMODRXREQEN = RM_Field_RAC_NS_RXENSRCEN_DEMODRXREQEN(self)
        self.zz_fdict['DEMODRXREQEN'] = self.DEMODRXREQEN
        self.PRSRXEN = RM_Field_RAC_NS_RXENSRCEN_PRSRXEN(self)
        self.zz_fdict['PRSRXEN'] = self.PRSRXEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_STATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_STATUS, self).__init__(rmio, label,
            0xb8020000, 0x00C,
            'STATUS', 'RAC_NS.STATUS', 'read-only',
            u"",
            0x00000000, 0xFFF8FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXMASK = RM_Field_RAC_NS_STATUS_RXMASK(self)
        self.zz_fdict['RXMASK'] = self.RXMASK
        self.FORCESTATEACTIVE = RM_Field_RAC_NS_STATUS_FORCESTATEACTIVE(self)
        self.zz_fdict['FORCESTATEACTIVE'] = self.FORCESTATEACTIVE
        self.TXAFTERFRAMEPEND = RM_Field_RAC_NS_STATUS_TXAFTERFRAMEPEND(self)
        self.zz_fdict['TXAFTERFRAMEPEND'] = self.TXAFTERFRAMEPEND
        self.TXAFTERFRAMEACTIVE = RM_Field_RAC_NS_STATUS_TXAFTERFRAMEACTIVE(self)
        self.zz_fdict['TXAFTERFRAMEACTIVE'] = self.TXAFTERFRAMEACTIVE
        self.SEQSLEEPING = RM_Field_RAC_NS_STATUS_SEQSLEEPING(self)
        self.zz_fdict['SEQSLEEPING'] = self.SEQSLEEPING
        self.SEQSLEEPDEEP = RM_Field_RAC_NS_STATUS_SEQSLEEPDEEP(self)
        self.zz_fdict['SEQSLEEPDEEP'] = self.SEQSLEEPDEEP
        self.STATE = RM_Field_RAC_NS_STATUS_STATE(self)
        self.zz_fdict['STATE'] = self.STATE
        self.SEQACTIVE = RM_Field_RAC_NS_STATUS_SEQACTIVE(self)
        self.zz_fdict['SEQACTIVE'] = self.SEQACTIVE
        self.DEMODENS = RM_Field_RAC_NS_STATUS_DEMODENS(self)
        self.zz_fdict['DEMODENS'] = self.DEMODENS
        self.TXENS = RM_Field_RAC_NS_STATUS_TXENS(self)
        self.zz_fdict['TXENS'] = self.TXENS
        self.RXENS = RM_Field_RAC_NS_STATUS_RXENS(self)
        self.zz_fdict['RXENS'] = self.RXENS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CMD, self).__init__(rmio, label,
            0xb8020000, 0x010,
            'CMD', 'RAC_NS.CMD', 'write-only',
            u"",
            0x00000000, 0xC000FDFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXEN = RM_Field_RAC_NS_CMD_TXEN(self)
        self.zz_fdict['TXEN'] = self.TXEN
        self.FORCETX = RM_Field_RAC_NS_CMD_FORCETX(self)
        self.zz_fdict['FORCETX'] = self.FORCETX
        self.TXONCCA = RM_Field_RAC_NS_CMD_TXONCCA(self)
        self.zz_fdict['TXONCCA'] = self.TXONCCA
        self.CLEARTXEN = RM_Field_RAC_NS_CMD_CLEARTXEN(self)
        self.zz_fdict['CLEARTXEN'] = self.CLEARTXEN
        self.TXAFTERFRAME = RM_Field_RAC_NS_CMD_TXAFTERFRAME(self)
        self.zz_fdict['TXAFTERFRAME'] = self.TXAFTERFRAME
        self.TXDIS = RM_Field_RAC_NS_CMD_TXDIS(self)
        self.zz_fdict['TXDIS'] = self.TXDIS
        self.CLEARRXOVERFLOW = RM_Field_RAC_NS_CMD_CLEARRXOVERFLOW(self)
        self.zz_fdict['CLEARRXOVERFLOW'] = self.CLEARRXOVERFLOW
        self.RXCAL = RM_Field_RAC_NS_CMD_RXCAL(self)
        self.zz_fdict['RXCAL'] = self.RXCAL
        self.RXDIS = RM_Field_RAC_NS_CMD_RXDIS(self)
        self.zz_fdict['RXDIS'] = self.RXDIS
        self.FRCWR = RM_Field_RAC_NS_CMD_FRCWR(self)
        self.zz_fdict['FRCWR'] = self.FRCWR
        self.FRCRD = RM_Field_RAC_NS_CMD_FRCRD(self)
        self.zz_fdict['FRCRD'] = self.FRCRD
        self.PAENSET = RM_Field_RAC_NS_CMD_PAENSET(self)
        self.zz_fdict['PAENSET'] = self.PAENSET
        self.PAENCLEAR = RM_Field_RAC_NS_CMD_PAENCLEAR(self)
        self.zz_fdict['PAENCLEAR'] = self.PAENCLEAR
        self.LNAENSET = RM_Field_RAC_NS_CMD_LNAENSET(self)
        self.zz_fdict['LNAENSET'] = self.LNAENSET
        self.LNAENCLEAR = RM_Field_RAC_NS_CMD_LNAENCLEAR(self)
        self.zz_fdict['LNAENCLEAR'] = self.LNAENCLEAR
        self.DEMODENSET = RM_Field_RAC_NS_CMD_DEMODENSET(self)
        self.zz_fdict['DEMODENSET'] = self.DEMODENSET
        self.DEMODENCLEAR = RM_Field_RAC_NS_CMD_DEMODENCLEAR(self)
        self.zz_fdict['DEMODENCLEAR'] = self.DEMODENCLEAR
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CTRL, self).__init__(rmio, label,
            0xb8020000, 0x014,
            'CTRL', 'RAC_NS.CTRL', 'read-write',
            u"",
            0x00000000, 0x1F0107EF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FORCEDISABLE = RM_Field_RAC_NS_CTRL_FORCEDISABLE(self)
        self.zz_fdict['FORCEDISABLE'] = self.FORCEDISABLE
        self.PRSTXEN = RM_Field_RAC_NS_CTRL_PRSTXEN(self)
        self.zz_fdict['PRSTXEN'] = self.PRSTXEN
        self.TXAFTERRX = RM_Field_RAC_NS_CTRL_TXAFTERRX(self)
        self.zz_fdict['TXAFTERRX'] = self.TXAFTERRX
        self.PRSMODE = RM_Field_RAC_NS_CTRL_PRSMODE(self)
        self.zz_fdict['PRSMODE'] = self.PRSMODE
        self.PRSCLR = RM_Field_RAC_NS_CTRL_PRSCLR(self)
        self.zz_fdict['PRSCLR'] = self.PRSCLR
        self.TXPOSTPONE = RM_Field_RAC_NS_CTRL_TXPOSTPONE(self)
        self.zz_fdict['TXPOSTPONE'] = self.TXPOSTPONE
        self.ACTIVEPOL = RM_Field_RAC_NS_CTRL_ACTIVEPOL(self)
        self.zz_fdict['ACTIVEPOL'] = self.ACTIVEPOL
        self.PAENPOL = RM_Field_RAC_NS_CTRL_PAENPOL(self)
        self.zz_fdict['PAENPOL'] = self.PAENPOL
        self.LNAENPOL = RM_Field_RAC_NS_CTRL_LNAENPOL(self)
        self.zz_fdict['LNAENPOL'] = self.LNAENPOL
        self.PRSRXDIS = RM_Field_RAC_NS_CTRL_PRSRXDIS(self)
        self.zz_fdict['PRSRXDIS'] = self.PRSRXDIS
        self.PRSFORCETX = RM_Field_RAC_NS_CTRL_PRSFORCETX(self)
        self.zz_fdict['PRSFORCETX'] = self.PRSFORCETX
        self.SEQRESET = RM_Field_RAC_NS_CTRL_SEQRESET(self)
        self.zz_fdict['SEQRESET'] = self.SEQRESET
        self.EXITSHUTDOWNDIS = RM_Field_RAC_NS_CTRL_EXITSHUTDOWNDIS(self)
        self.zz_fdict['EXITSHUTDOWNDIS'] = self.EXITSHUTDOWNDIS
        self.CPUWAITDIS = RM_Field_RAC_NS_CTRL_CPUWAITDIS(self)
        self.zz_fdict['CPUWAITDIS'] = self.CPUWAITDIS
        self.SEQCLKDIS = RM_Field_RAC_NS_CTRL_SEQCLKDIS(self)
        self.zz_fdict['SEQCLKDIS'] = self.SEQCLKDIS
        self.RXOFDIS = RM_Field_RAC_NS_CTRL_RXOFDIS(self)
        self.zz_fdict['RXOFDIS'] = self.RXOFDIS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_FORCESTATE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_FORCESTATE, self).__init__(rmio, label,
            0xb8020000, 0x018,
            'FORCESTATE', 'RAC_NS.FORCESTATE', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.FORCESTATE = RM_Field_RAC_NS_FORCESTATE_FORCESTATE(self)
        self.zz_fdict['FORCESTATE'] = self.FORCESTATE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IF, self).__init__(rmio, label,
            0xb8020000, 0x01C,
            'IF', 'RAC_NS.IF', 'read-write',
            u"",
            0x00000000, 0x00FF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGE = RM_Field_RAC_NS_IF_STATECHANGE(self)
        self.zz_fdict['STATECHANGE'] = self.STATECHANGE
        self.STIMCMPEV = RM_Field_RAC_NS_IF_STIMCMPEV(self)
        self.zz_fdict['STIMCMPEV'] = self.STIMCMPEV
        self.SEQLOCKUP = RM_Field_RAC_NS_IF_SEQLOCKUP(self)
        self.zz_fdict['SEQLOCKUP'] = self.SEQLOCKUP
        self.SEQRESETREQ = RM_Field_RAC_NS_IF_SEQRESETREQ(self)
        self.zz_fdict['SEQRESETREQ'] = self.SEQRESETREQ
        self.SEQ = RM_Field_RAC_NS_IF_SEQ(self)
        self.zz_fdict['SEQ'] = self.SEQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IEN, self).__init__(rmio, label,
            0xb8020000, 0x020,
            'IEN', 'RAC_NS.IEN', 'read-write',
            u"",
            0x00000000, 0x00FF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGE = RM_Field_RAC_NS_IEN_STATECHANGE(self)
        self.zz_fdict['STATECHANGE'] = self.STATECHANGE
        self.STIMCMPEV = RM_Field_RAC_NS_IEN_STIMCMPEV(self)
        self.zz_fdict['STIMCMPEV'] = self.STIMCMPEV
        self.SEQLOCKUP = RM_Field_RAC_NS_IEN_SEQLOCKUP(self)
        self.zz_fdict['SEQLOCKUP'] = self.SEQLOCKUP
        self.SEQRESETREQ = RM_Field_RAC_NS_IEN_SEQRESETREQ(self)
        self.zz_fdict['SEQRESETREQ'] = self.SEQRESETREQ
        self.SEQ = RM_Field_RAC_NS_IEN_SEQ(self)
        self.zz_fdict['SEQ'] = self.SEQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TESTCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TESTCTRL, self).__init__(rmio, label,
            0xb8020000, 0x024,
            'TESTCTRL', 'RAC_NS.TESTCTRL', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODEN = RM_Field_RAC_NS_TESTCTRL_MODEN(self)
        self.zz_fdict['MODEN'] = self.MODEN
        self.DEMODEN = RM_Field_RAC_NS_TESTCTRL_DEMODEN(self)
        self.zz_fdict['DEMODEN'] = self.DEMODEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SEQIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SEQIF, self).__init__(rmio, label,
            0xb8020000, 0x028,
            'SEQIF', 'RAC_NS.SEQIF', 'read-write',
            u"",
            0x00000000, 0x3FFF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGESEQ = RM_Field_RAC_NS_SEQIF_STATECHANGESEQ(self)
        self.zz_fdict['STATECHANGESEQ'] = self.STATECHANGESEQ
        self.STIMCMPEVSEQ = RM_Field_RAC_NS_SEQIF_STIMCMPEVSEQ(self)
        self.zz_fdict['STIMCMPEVSEQ'] = self.STIMCMPEVSEQ
        self.DEMODRXREQCLRSEQ = RM_Field_RAC_NS_SEQIF_DEMODRXREQCLRSEQ(self)
        self.zz_fdict['DEMODRXREQCLRSEQ'] = self.DEMODRXREQCLRSEQ
        self.PRSEVENTSEQ = RM_Field_RAC_NS_SEQIF_PRSEVENTSEQ(self)
        self.zz_fdict['PRSEVENTSEQ'] = self.PRSEVENTSEQ
        self.STATEOFF = RM_Field_RAC_NS_SEQIF_STATEOFF(self)
        self.zz_fdict['STATEOFF'] = self.STATEOFF
        self.STATERXWARM = RM_Field_RAC_NS_SEQIF_STATERXWARM(self)
        self.zz_fdict['STATERXWARM'] = self.STATERXWARM
        self.STATERXSEARCH = RM_Field_RAC_NS_SEQIF_STATERXSEARCH(self)
        self.zz_fdict['STATERXSEARCH'] = self.STATERXSEARCH
        self.STATERXFRAME = RM_Field_RAC_NS_SEQIF_STATERXFRAME(self)
        self.zz_fdict['STATERXFRAME'] = self.STATERXFRAME
        self.STATERXPD = RM_Field_RAC_NS_SEQIF_STATERXPD(self)
        self.zz_fdict['STATERXPD'] = self.STATERXPD
        self.STATERX2RX = RM_Field_RAC_NS_SEQIF_STATERX2RX(self)
        self.zz_fdict['STATERX2RX'] = self.STATERX2RX
        self.STATERXOVERFLOW = RM_Field_RAC_NS_SEQIF_STATERXOVERFLOW(self)
        self.zz_fdict['STATERXOVERFLOW'] = self.STATERXOVERFLOW
        self.STATERX2TX = RM_Field_RAC_NS_SEQIF_STATERX2TX(self)
        self.zz_fdict['STATERX2TX'] = self.STATERX2TX
        self.STATETXWARM = RM_Field_RAC_NS_SEQIF_STATETXWARM(self)
        self.zz_fdict['STATETXWARM'] = self.STATETXWARM
        self.STATETX = RM_Field_RAC_NS_SEQIF_STATETX(self)
        self.zz_fdict['STATETX'] = self.STATETX
        self.STATETXPD = RM_Field_RAC_NS_SEQIF_STATETXPD(self)
        self.zz_fdict['STATETXPD'] = self.STATETXPD
        self.STATETX2RX = RM_Field_RAC_NS_SEQIF_STATETX2RX(self)
        self.zz_fdict['STATETX2RX'] = self.STATETX2RX
        self.STATETX2TX = RM_Field_RAC_NS_SEQIF_STATETX2TX(self)
        self.zz_fdict['STATETX2TX'] = self.STATETX2TX
        self.STATESHUTDOWN = RM_Field_RAC_NS_SEQIF_STATESHUTDOWN(self)
        self.zz_fdict['STATESHUTDOWN'] = self.STATESHUTDOWN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SEQIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SEQIEN, self).__init__(rmio, label,
            0xb8020000, 0x02C,
            'SEQIEN', 'RAC_NS.SEQIEN', 'read-write',
            u"",
            0x00000000, 0x3FFF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGESEQ = RM_Field_RAC_NS_SEQIEN_STATECHANGESEQ(self)
        self.zz_fdict['STATECHANGESEQ'] = self.STATECHANGESEQ
        self.STIMCMPEVSEQ = RM_Field_RAC_NS_SEQIEN_STIMCMPEVSEQ(self)
        self.zz_fdict['STIMCMPEVSEQ'] = self.STIMCMPEVSEQ
        self.DEMODRXREQCLRSEQ = RM_Field_RAC_NS_SEQIEN_DEMODRXREQCLRSEQ(self)
        self.zz_fdict['DEMODRXREQCLRSEQ'] = self.DEMODRXREQCLRSEQ
        self.PRSEVENTSEQ = RM_Field_RAC_NS_SEQIEN_PRSEVENTSEQ(self)
        self.zz_fdict['PRSEVENTSEQ'] = self.PRSEVENTSEQ
        self.STATEOFF = RM_Field_RAC_NS_SEQIEN_STATEOFF(self)
        self.zz_fdict['STATEOFF'] = self.STATEOFF
        self.STATERXWARM = RM_Field_RAC_NS_SEQIEN_STATERXWARM(self)
        self.zz_fdict['STATERXWARM'] = self.STATERXWARM
        self.STATERXSEARCH = RM_Field_RAC_NS_SEQIEN_STATERXSEARCH(self)
        self.zz_fdict['STATERXSEARCH'] = self.STATERXSEARCH
        self.STATERXFRAME = RM_Field_RAC_NS_SEQIEN_STATERXFRAME(self)
        self.zz_fdict['STATERXFRAME'] = self.STATERXFRAME
        self.STATERXPD = RM_Field_RAC_NS_SEQIEN_STATERXPD(self)
        self.zz_fdict['STATERXPD'] = self.STATERXPD
        self.STATERX2RX = RM_Field_RAC_NS_SEQIEN_STATERX2RX(self)
        self.zz_fdict['STATERX2RX'] = self.STATERX2RX
        self.STATERXOVERFLOW = RM_Field_RAC_NS_SEQIEN_STATERXOVERFLOW(self)
        self.zz_fdict['STATERXOVERFLOW'] = self.STATERXOVERFLOW
        self.STATERX2TX = RM_Field_RAC_NS_SEQIEN_STATERX2TX(self)
        self.zz_fdict['STATERX2TX'] = self.STATERX2TX
        self.STATETXWARM = RM_Field_RAC_NS_SEQIEN_STATETXWARM(self)
        self.zz_fdict['STATETXWARM'] = self.STATETXWARM
        self.STATETX = RM_Field_RAC_NS_SEQIEN_STATETX(self)
        self.zz_fdict['STATETX'] = self.STATETX
        self.STATETXPD = RM_Field_RAC_NS_SEQIEN_STATETXPD(self)
        self.zz_fdict['STATETXPD'] = self.STATETXPD
        self.STATETX2RX = RM_Field_RAC_NS_SEQIEN_STATETX2RX(self)
        self.zz_fdict['STATETX2RX'] = self.STATETX2RX
        self.STATETX2TX = RM_Field_RAC_NS_SEQIEN_STATETX2TX(self)
        self.zz_fdict['STATETX2TX'] = self.STATETX2TX
        self.STATESHUTDOWN = RM_Field_RAC_NS_SEQIEN_STATESHUTDOWN(self)
        self.zz_fdict['STATESHUTDOWN'] = self.STATESHUTDOWN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_STATUS1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_STATUS1, self).__init__(rmio, label,
            0xb8020000, 0x030,
            'STATUS1', 'RAC_NS.STATUS1', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXMASK = RM_Field_RAC_NS_STATUS1_TXMASK(self)
        self.zz_fdict['TXMASK'] = self.TXMASK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_STIMER(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_STIMER, self).__init__(rmio, label,
            0xb8020000, 0x034,
            'STIMER', 'RAC_NS.STIMER', 'read-only',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STIMER = RM_Field_RAC_NS_STIMER_STIMER(self)
        self.zz_fdict['STIMER'] = self.STIMER
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_STIMERCOMP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_STIMERCOMP, self).__init__(rmio, label,
            0xb8020000, 0x038,
            'STIMERCOMP', 'RAC_NS.STIMERCOMP', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STIMERCOMP = RM_Field_RAC_NS_STIMERCOMP_STIMERCOMP(self)
        self.zz_fdict['STIMERCOMP'] = self.STIMERCOMP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SEQCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SEQCTRL, self).__init__(rmio, label,
            0xb8020000, 0x03C,
            'SEQCTRL', 'RAC_NS.SEQCTRL', 'read-write',
            u"",
            0x00000000, 0x0300007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.COMPACT = RM_Field_RAC_NS_SEQCTRL_COMPACT(self)
        self.zz_fdict['COMPACT'] = self.COMPACT
        self.COMPINVALMODE = RM_Field_RAC_NS_SEQCTRL_COMPINVALMODE(self)
        self.zz_fdict['COMPINVALMODE'] = self.COMPINVALMODE
        self.RELATIVE = RM_Field_RAC_NS_SEQCTRL_RELATIVE(self)
        self.zz_fdict['RELATIVE'] = self.RELATIVE
        self.STIMERALWAYSRUN = RM_Field_RAC_NS_SEQCTRL_STIMERALWAYSRUN(self)
        self.zz_fdict['STIMERALWAYSRUN'] = self.STIMERALWAYSRUN
        self.STIMERDEBUGRUN = RM_Field_RAC_NS_SEQCTRL_STIMERDEBUGRUN(self)
        self.zz_fdict['STIMERDEBUGRUN'] = self.STIMERDEBUGRUN
        self.STATEDEBUGRUN = RM_Field_RAC_NS_SEQCTRL_STATEDEBUGRUN(self)
        self.zz_fdict['STATEDEBUGRUN'] = self.STATEDEBUGRUN
        self.SWIRQ = RM_Field_RAC_NS_SEQCTRL_SWIRQ(self)
        self.zz_fdict['SWIRQ'] = self.SWIRQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PRESC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PRESC, self).__init__(rmio, label,
            0xb8020000, 0x040,
            'PRESC', 'RAC_NS.PRESC', 'read-write',
            u"",
            0x00000007, 0x0000007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STIMER = RM_Field_RAC_NS_PRESC_STIMER(self)
        self.zz_fdict['STIMER'] = self.STIMER
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SR0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SR0, self).__init__(rmio, label,
            0xb8020000, 0x044,
            'SR0', 'RAC_NS.SR0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SR0 = RM_Field_RAC_NS_SR0_SR0(self)
        self.zz_fdict['SR0'] = self.SR0
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SR1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SR1, self).__init__(rmio, label,
            0xb8020000, 0x048,
            'SR1', 'RAC_NS.SR1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SR1 = RM_Field_RAC_NS_SR1_SR1(self)
        self.zz_fdict['SR1'] = self.SR1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SR2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SR2, self).__init__(rmio, label,
            0xb8020000, 0x04C,
            'SR2', 'RAC_NS.SR2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SR2 = RM_Field_RAC_NS_SR2_SR2(self)
        self.zz_fdict['SR2'] = self.SR2
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SR3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SR3, self).__init__(rmio, label,
            0xb8020000, 0x050,
            'SR3', 'RAC_NS.SR3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SR3 = RM_Field_RAC_NS_SR3_SR3(self)
        self.zz_fdict['SR3'] = self.SR3
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_STCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_STCTRL, self).__init__(rmio, label,
            0xb8020000, 0x054,
            'STCTRL', 'RAC_NS.STCTRL', 'read-write',
            u"",
            0x00000000, 0x01FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STCAL = RM_Field_RAC_NS_STCTRL_STCAL(self)
        self.zz_fdict['STCAL'] = self.STCAL
        self.STSKEW = RM_Field_RAC_NS_STCTRL_STSKEW(self)
        self.zz_fdict['STSKEW'] = self.STSKEW
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_FRCTXWORD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_FRCTXWORD, self).__init__(rmio, label,
            0xb8020000, 0x058,
            'FRCTXWORD', 'RAC_NS.FRCTXWORD', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.WDATA = RM_Field_RAC_NS_FRCTXWORD_WDATA(self)
        self.zz_fdict['WDATA'] = self.WDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_FRCRXWORD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_FRCRXWORD, self).__init__(rmio, label,
            0xb8020000, 0x05C,
            'FRCRXWORD', 'RAC_NS.FRCRXWORD', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RDATA = RM_Field_RAC_NS_FRCRXWORD_RDATA(self)
        self.zz_fdict['RDATA'] = self.RDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_EM1PCSR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_EM1PCSR, self).__init__(rmio, label,
            0xb8020000, 0x060,
            'EM1PCSR', 'RAC_NS.EM1PCSR', 'read-write',
            u"",
            0x00000000, 0x00070033,
            0x00001000, 0x00002000,
            0x00003000)

        self.RADIOEM1PMODE = RM_Field_RAC_NS_EM1PCSR_RADIOEM1PMODE(self)
        self.zz_fdict['RADIOEM1PMODE'] = self.RADIOEM1PMODE
        self.RADIOEM1PDISSWREQ = RM_Field_RAC_NS_EM1PCSR_RADIOEM1PDISSWREQ(self)
        self.zz_fdict['RADIOEM1PDISSWREQ'] = self.RADIOEM1PDISSWREQ
        self.MCUEM1PMODE = RM_Field_RAC_NS_EM1PCSR_MCUEM1PMODE(self)
        self.zz_fdict['MCUEM1PMODE'] = self.MCUEM1PMODE
        self.MCUEM1PDISSWREQ = RM_Field_RAC_NS_EM1PCSR_MCUEM1PDISSWREQ(self)
        self.zz_fdict['MCUEM1PDISSWREQ'] = self.MCUEM1PDISSWREQ
        self.RADIOEM1PREQ = RM_Field_RAC_NS_EM1PCSR_RADIOEM1PREQ(self)
        self.zz_fdict['RADIOEM1PREQ'] = self.RADIOEM1PREQ
        self.RADIOEM1PACK = RM_Field_RAC_NS_EM1PCSR_RADIOEM1PACK(self)
        self.zz_fdict['RADIOEM1PACK'] = self.RADIOEM1PACK
        self.RADIOEM1PHWREQ = RM_Field_RAC_NS_EM1PCSR_RADIOEM1PHWREQ(self)
        self.zz_fdict['RADIOEM1PHWREQ'] = self.RADIOEM1PHWREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYNTHENCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYNTHENCTRL, self).__init__(rmio, label,
            0xb8020000, 0x098,
            'SYNTHENCTRL', 'RAC_NS.SYNTHENCTRL', 'read-write',
            u"",
            0x00000000, 0x00100682,
            0x00001000, 0x00002000,
            0x00003000)

        self.VCOSTARTUP = RM_Field_RAC_NS_SYNTHENCTRL_VCOSTARTUP(self)
        self.zz_fdict['VCOSTARTUP'] = self.VCOSTARTUP
        self.VCBUFEN = RM_Field_RAC_NS_SYNTHENCTRL_VCBUFEN(self)
        self.zz_fdict['VCBUFEN'] = self.VCBUFEN
        self.SYNTHSTARTREQ = RM_Field_RAC_NS_SYNTHENCTRL_SYNTHSTARTREQ(self)
        self.zz_fdict['SYNTHSTARTREQ'] = self.SYNTHSTARTREQ
        self.MMDPOWERBALANCEDISABLE = RM_Field_RAC_NS_SYNTHENCTRL_MMDPOWERBALANCEDISABLE(self)
        self.zz_fdict['MMDPOWERBALANCEDISABLE'] = self.MMDPOWERBALANCEDISABLE
        self.LPFBWSEL = RM_Field_RAC_NS_SYNTHENCTRL_LPFBWSEL(self)
        self.zz_fdict['LPFBWSEL'] = self.LPFBWSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYNTHREGCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYNTHREGCTRL, self).__init__(rmio, label,
            0xb8020000, 0x09C,
            'SYNTHREGCTRL', 'RAC_NS.SYNTHREGCTRL', 'read-write',
            u"",
            0x04000C00, 0x07001C00,
            0x00001000, 0x00002000,
            0x00003000)

        self.MMDLDOVREFTRIM = RM_Field_RAC_NS_SYNTHREGCTRL_MMDLDOVREFTRIM(self)
        self.zz_fdict['MMDLDOVREFTRIM'] = self.MMDLDOVREFTRIM
        self.CHPLDOVREFTRIM = RM_Field_RAC_NS_SYNTHREGCTRL_CHPLDOVREFTRIM(self)
        self.zz_fdict['CHPLDOVREFTRIM'] = self.CHPLDOVREFTRIM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_VCOCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_VCOCTRL, self).__init__(rmio, label,
            0xb8020000, 0x0A0,
            'VCOCTRL', 'RAC_NS.VCOCTRL', 'read-write',
            u"",
            0x0000044C, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VCOAMPLITUDE = RM_Field_RAC_NS_VCOCTRL_VCOAMPLITUDE(self)
        self.zz_fdict['VCOAMPLITUDE'] = self.VCOAMPLITUDE
        self.VCODETAMPLITUDERX = RM_Field_RAC_NS_VCOCTRL_VCODETAMPLITUDERX(self)
        self.zz_fdict['VCODETAMPLITUDERX'] = self.VCODETAMPLITUDERX
        self.VCODETAMPLITUDETX = RM_Field_RAC_NS_VCOCTRL_VCODETAMPLITUDETX(self)
        self.zz_fdict['VCODETAMPLITUDETX'] = self.VCODETAMPLITUDETX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CHPCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CHPCTRL, self).__init__(rmio, label,
            0xb8020000, 0x0A4,
            'CHPCTRL', 'RAC_NS.CHPCTRL', 'read-write',
            u"",
            0x00000000, 0x00004000,
            0x00001000, 0x00002000,
            0x00003000)

        self.CHPOUTPUTTRISTATEMODE = RM_Field_RAC_NS_CHPCTRL_CHPOUTPUTTRISTATEMODE(self)
        self.zz_fdict['CHPOUTPUTTRISTATEMODE'] = self.CHPOUTPUTTRISTATEMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFSTATUS, self).__init__(rmio, label,
            0xb8020000, 0x0AC,
            'RFSTATUS', 'RAC_NS.RFSTATUS', 'read-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODRAMPUPDONE = RM_Field_RAC_NS_RFSTATUS_MODRAMPUPDONE(self)
        self.zz_fdict['MODRAMPUPDONE'] = self.MODRAMPUPDONE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_STATUS2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_STATUS2, self).__init__(rmio, label,
            0xb8020000, 0x0B0,
            'STATUS2', 'RAC_NS.STATUS2', 'read-only',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREVSTATE1 = RM_Field_RAC_NS_STATUS2_PREVSTATE1(self)
        self.zz_fdict['PREVSTATE1'] = self.PREVSTATE1
        self.PREVSTATE2 = RM_Field_RAC_NS_STATUS2_PREVSTATE2(self)
        self.zz_fdict['PREVSTATE2'] = self.PREVSTATE2
        self.PREVSTATE3 = RM_Field_RAC_NS_STATUS2_PREVSTATE3(self)
        self.zz_fdict['PREVSTATE3'] = self.PREVSTATE3
        self.CURRSTATE = RM_Field_RAC_NS_STATUS2_CURRSTATE(self)
        self.zz_fdict['CURRSTATE'] = self.CURRSTATE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFPGACTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFPGACTRL, self).__init__(rmio, label,
            0xb8020000, 0x0B4,
            'IFPGACTRL', 'RAC_NS.IFPGACTRL', 'read-write',
            u"",
            0x00000000, 0x0FF80000,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCCALON = RM_Field_RAC_NS_IFPGACTRL_DCCALON(self)
        self.zz_fdict['DCCALON'] = self.DCCALON
        self.DCRSTEN = RM_Field_RAC_NS_IFPGACTRL_DCRSTEN(self)
        self.zz_fdict['DCRSTEN'] = self.DCRSTEN
        self.DCESTIEN = RM_Field_RAC_NS_IFPGACTRL_DCESTIEN(self)
        self.zz_fdict['DCESTIEN'] = self.DCESTIEN
        self.DCCALDEC0 = RM_Field_RAC_NS_IFPGACTRL_DCCALDEC0(self)
        self.zz_fdict['DCCALDEC0'] = self.DCCALDEC0
        self.DCCALDCGEAR = RM_Field_RAC_NS_IFPGACTRL_DCCALDCGEAR(self)
        self.zz_fdict['DCCALDCGEAR'] = self.DCCALDCGEAR
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PAENCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PAENCTRL, self).__init__(rmio, label,
            0xb8020000, 0x0B8,
            'PAENCTRL', 'RAC_NS.PAENCTRL', 'read-write',
            u"",
            0x00000000, 0x00070100,
            0x00001000, 0x00002000,
            0x00003000)

        self.PARAMP = RM_Field_RAC_NS_PAENCTRL_PARAMP(self)
        self.zz_fdict['PARAMP'] = self.PARAMP
        self.INVRAMPCLK = RM_Field_RAC_NS_PAENCTRL_INVRAMPCLK(self)
        self.zz_fdict['INVRAMPCLK'] = self.INVRAMPCLK
        self.DIV2RAMPCLK = RM_Field_RAC_NS_PAENCTRL_DIV2RAMPCLK(self)
        self.zz_fdict['DIV2RAMPCLK'] = self.DIV2RAMPCLK
        self.RSTDIV2RAMPCLK = RM_Field_RAC_NS_PAENCTRL_RSTDIV2RAMPCLK(self)
        self.zz_fdict['RSTDIV2RAMPCLK'] = self.RSTDIV2RAMPCLK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_APC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_APC, self).__init__(rmio, label,
            0xb8020000, 0x0BC,
            'APC', 'RAC_NS.APC', 'read-write',
            u"",
            0xFF000000, 0xFF000004,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENAPCSW = RM_Field_RAC_NS_APC_ENAPCSW(self)
        self.zz_fdict['ENAPCSW'] = self.ENAPCSW
        self.AMPCONTROLLIMITSW = RM_Field_RAC_NS_APC_AMPCONTROLLIMITSW(self)
        self.zz_fdict['AMPCONTROLLIMITSW'] = self.AMPCONTROLLIMITSW
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_ANTDIV(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_ANTDIV, self).__init__(rmio, label,
            0xb8020000, 0x0C0,
            'ANTDIV', 'RAC_NS.ANTDIV', 'read-write',
            u"",
            0x00000000, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTDIVLNAMIXEN0 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXEN0(self)
        self.zz_fdict['INTDIVLNAMIXEN0'] = self.INTDIVLNAMIXEN0
        self.INTDIVLNAMIXENAMP0 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXENAMP0(self)
        self.zz_fdict['INTDIVLNAMIXENAMP0'] = self.INTDIVLNAMIXENAMP0
        self.INTDIVLNAMIXRFATTDCEN0 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFATTDCEN0(self)
        self.zz_fdict['INTDIVLNAMIXRFATTDCEN0'] = self.INTDIVLNAMIXRFATTDCEN0
        self.INTDIVLNAMIXRFPKDENRF0 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFPKDENRF0(self)
        self.zz_fdict['INTDIVLNAMIXRFPKDENRF0'] = self.INTDIVLNAMIXRFPKDENRF0
        self.INTDIVSYLODIVRLO0SUBGEN = RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO0SUBGEN(self)
        self.zz_fdict['INTDIVSYLODIVRLO0SUBGEN'] = self.INTDIVSYLODIVRLO0SUBGEN
        self.INTDIVLNAMIXEN1 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXEN1(self)
        self.zz_fdict['INTDIVLNAMIXEN1'] = self.INTDIVLNAMIXEN1
        self.INTDIVLNAMIXENAMP1 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXENAMP1(self)
        self.zz_fdict['INTDIVLNAMIXENAMP1'] = self.INTDIVLNAMIXENAMP1
        self.INTDIVLNAMIXRFATTDCEN1 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFATTDCEN1(self)
        self.zz_fdict['INTDIVLNAMIXRFATTDCEN1'] = self.INTDIVLNAMIXRFATTDCEN1
        self.INTDIVLNAMIXRFPKDENRF1 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFPKDENRF1(self)
        self.zz_fdict['INTDIVLNAMIXRFPKDENRF1'] = self.INTDIVLNAMIXRFPKDENRF1
        self.INTDIVSYLODIVRLO1SUBGEN = RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO1SUBGEN(self)
        self.zz_fdict['INTDIVSYLODIVRLO1SUBGEN'] = self.INTDIVSYLODIVRLO1SUBGEN
        self.ANTDIVSTATUS = RM_Field_RAC_NS_ANTDIV_ANTDIVSTATUS(self)
        self.zz_fdict['ANTDIVSTATUS'] = self.ANTDIVSTATUS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCTRIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCTRIM, self).__init__(rmio, label,
            0xb8020000, 0x0C4,
            'AUXADCTRIM', 'RAC_NS.AUXADCTRIM', 'read-write',
            u"",
            0x06D55504, 0x1FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCCLKINVERT = RM_Field_RAC_NS_AUXADCTRIM_AUXADCCLKINVERT(self)
        self.zz_fdict['AUXADCCLKINVERT'] = self.AUXADCCLKINVERT
        self.AUXADCLDOVREFTRIM = RM_Field_RAC_NS_AUXADCTRIM_AUXADCLDOVREFTRIM(self)
        self.zz_fdict['AUXADCLDOVREFTRIM'] = self.AUXADCLDOVREFTRIM
        self.AUXADCOUTPUTINVERT = RM_Field_RAC_NS_AUXADCTRIM_AUXADCOUTPUTINVERT(self)
        self.zz_fdict['AUXADCOUTPUTINVERT'] = self.AUXADCOUTPUTINVERT
        self.AUXADCRCTUNE = RM_Field_RAC_NS_AUXADCTRIM_AUXADCRCTUNE(self)
        self.zz_fdict['AUXADCRCTUNE'] = self.AUXADCRCTUNE
        self.AUXADCTRIMADCINPUTRES = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMADCINPUTRES(self)
        self.zz_fdict['AUXADCTRIMADCINPUTRES'] = self.AUXADCTRIMADCINPUTRES
        self.AUXADCTRIMCURRINPUTBUF = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF(self)
        self.zz_fdict['AUXADCTRIMCURRINPUTBUF'] = self.AUXADCTRIMCURRINPUTBUF
        self.AUXADCTRIMCURROPA1 = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURROPA1(self)
        self.zz_fdict['AUXADCTRIMCURROPA1'] = self.AUXADCTRIMCURROPA1
        self.AUXADCTRIMCURROPA2 = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURROPA2(self)
        self.zz_fdict['AUXADCTRIMCURROPA2'] = self.AUXADCTRIMCURROPA2
        self.AUXADCTRIMCURRREFBUF = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRREFBUF(self)
        self.zz_fdict['AUXADCTRIMCURRREFBUF'] = self.AUXADCTRIMCURRREFBUF
        self.AUXADCTRIMCURRTSENSE = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRTSENSE(self)
        self.zz_fdict['AUXADCTRIMCURRTSENSE'] = self.AUXADCTRIMCURRTSENSE
        self.AUXADCTRIMCURRVCMBUF = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRVCMBUF(self)
        self.zz_fdict['AUXADCTRIMCURRVCMBUF'] = self.AUXADCTRIMCURRVCMBUF
        self.AUXADCTRIMLDOHIGHCURRENT = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT(self)
        self.zz_fdict['AUXADCTRIMLDOHIGHCURRENT'] = self.AUXADCTRIMLDOHIGHCURRENT
        self.AUXADCTRIMREFP = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMREFP(self)
        self.zz_fdict['AUXADCTRIMREFP'] = self.AUXADCTRIMREFP
        self.AUXADCTRIMVREFVCM = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMVREFVCM(self)
        self.zz_fdict['AUXADCTRIMVREFVCM'] = self.AUXADCTRIMVREFVCM
        self.AUXADCTSENSETRIMVBE2 = RM_Field_RAC_NS_AUXADCTRIM_AUXADCTSENSETRIMVBE2(self)
        self.zz_fdict['AUXADCTSENSETRIMVBE2'] = self.AUXADCTSENSETRIMVBE2
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCEN, self).__init__(rmio, label,
            0xb8020000, 0x0C8,
            'AUXADCEN', 'RAC_NS.AUXADCEN', 'read-write',
            u"",
            0x00000000, 0x000003FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCENAUXADC = RM_Field_RAC_NS_AUXADCEN_AUXADCENAUXADC(self)
        self.zz_fdict['AUXADCENAUXADC'] = self.AUXADCENAUXADC
        self.AUXADCENINPUTBUFFER = RM_Field_RAC_NS_AUXADCEN_AUXADCENINPUTBUFFER(self)
        self.zz_fdict['AUXADCENINPUTBUFFER'] = self.AUXADCENINPUTBUFFER
        self.AUXADCENLDO = RM_Field_RAC_NS_AUXADCEN_AUXADCENLDO(self)
        self.zz_fdict['AUXADCENLDO'] = self.AUXADCENLDO
        self.AUXADCENOUTPUTDRV = RM_Field_RAC_NS_AUXADCEN_AUXADCENOUTPUTDRV(self)
        self.zz_fdict['AUXADCENOUTPUTDRV'] = self.AUXADCENOUTPUTDRV
        self.AUXADCENPMON = RM_Field_RAC_NS_AUXADCEN_AUXADCENPMON(self)
        self.zz_fdict['AUXADCENPMON'] = self.AUXADCENPMON
        self.AUXADCENRESONDIAGA = RM_Field_RAC_NS_AUXADCEN_AUXADCENRESONDIAGA(self)
        self.zz_fdict['AUXADCENRESONDIAGA'] = self.AUXADCENRESONDIAGA
        self.AUXADCENTSENSE = RM_Field_RAC_NS_AUXADCEN_AUXADCENTSENSE(self)
        self.zz_fdict['AUXADCENTSENSE'] = self.AUXADCENTSENSE
        self.AUXADCENTSENSECAL = RM_Field_RAC_NS_AUXADCEN_AUXADCENTSENSECAL(self)
        self.zz_fdict['AUXADCENTSENSECAL'] = self.AUXADCENTSENSECAL
        self.AUXADCINPUTBUFFERBYPASS = RM_Field_RAC_NS_AUXADCEN_AUXADCINPUTBUFFERBYPASS(self)
        self.zz_fdict['AUXADCINPUTBUFFERBYPASS'] = self.AUXADCINPUTBUFFERBYPASS
        self.AUXADCENMEASTHERMISTOR = RM_Field_RAC_NS_AUXADCEN_AUXADCENMEASTHERMISTOR(self)
        self.zz_fdict['AUXADCENMEASTHERMISTOR'] = self.AUXADCENMEASTHERMISTOR
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCCTRL0, self).__init__(rmio, label,
            0xb8020000, 0x0CC,
            'AUXADCCTRL0', 'RAC_NS.AUXADCCTRL0', 'read-write',
            u"",
            0x00000100, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CYCLES = RM_Field_RAC_NS_AUXADCCTRL0_CYCLES(self)
        self.zz_fdict['CYCLES'] = self.CYCLES
        self.MUXSEL = RM_Field_RAC_NS_AUXADCCTRL0_MUXSEL(self)
        self.zz_fdict['MUXSEL'] = self.MUXSEL
        self.CLRCOUNTER = RM_Field_RAC_NS_AUXADCCTRL0_CLRCOUNTER(self)
        self.zz_fdict['CLRCOUNTER'] = self.CLRCOUNTER
        self.CLRFILTER = RM_Field_RAC_NS_AUXADCCTRL0_CLRFILTER(self)
        self.zz_fdict['CLRFILTER'] = self.CLRFILTER
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCCTRL1, self).__init__(rmio, label,
            0xb8020000, 0x0D0,
            'AUXADCCTRL1', 'RAC_NS.AUXADCCTRL1', 'read-write',
            u"",
            0x00000000, 0xF31F0FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCINPUTRESSEL = RM_Field_RAC_NS_AUXADCCTRL1_AUXADCINPUTRESSEL(self)
        self.zz_fdict['AUXADCINPUTRESSEL'] = self.AUXADCINPUTRESSEL
        self.AUXADCINPUTSELECT = RM_Field_RAC_NS_AUXADCCTRL1_AUXADCINPUTSELECT(self)
        self.zz_fdict['AUXADCINPUTSELECT'] = self.AUXADCINPUTSELECT
        self.AUXADCPMONSELECT = RM_Field_RAC_NS_AUXADCCTRL1_AUXADCPMONSELECT(self)
        self.zz_fdict['AUXADCPMONSELECT'] = self.AUXADCPMONSELECT
        self.AUXADCTSENSESELCURR = RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTSENSESELCURR(self)
        self.zz_fdict['AUXADCTSENSESELCURR'] = self.AUXADCTSENSESELCURR
        self.AUXADCRESET = RM_Field_RAC_NS_AUXADCCTRL1_AUXADCRESET(self)
        self.zz_fdict['AUXADCRESET'] = self.AUXADCRESET
        self.AUXADCTSENSESELVBE = RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTSENSESELVBE(self)
        self.zz_fdict['AUXADCTSENSESELVBE'] = self.AUXADCTSENSESELVBE
        self.AUXADCTHERMISTORFREQSEL = RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL(self)
        self.zz_fdict['AUXADCTHERMISTORFREQSEL'] = self.AUXADCTHERMISTORFREQSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCOUT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCOUT, self).__init__(rmio, label,
            0xb8020000, 0x0D4,
            'AUXADCOUT', 'RAC_NS.AUXADCOUT', 'read-only',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCOUT = RM_Field_RAC_NS_AUXADCOUT_AUXADCOUT(self)
        self.zz_fdict['AUXADCOUT'] = self.AUXADCOUT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CLKMULTEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CLKMULTEN0, self).__init__(rmio, label,
            0xb8020000, 0x0D8,
            'CLKMULTEN0', 'RAC_NS.CLKMULTEN0', 'read-write',
            u"",
            0xAA400005, 0xFFDFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTBWCAL = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTBWCAL(self)
        self.zz_fdict['CLKMULTBWCAL'] = self.CLKMULTBWCAL
        self.CLKMULTDISICO = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTDISICO(self)
        self.zz_fdict['CLKMULTDISICO'] = self.CLKMULTDISICO
        self.CLKMULTENBBDET = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBDET(self)
        self.zz_fdict['CLKMULTENBBDET'] = self.CLKMULTENBBDET
        self.CLKMULTENBBXLDET = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBXLDET(self)
        self.zz_fdict['CLKMULTENBBXLDET'] = self.CLKMULTENBBXLDET
        self.CLKMULTENBBXMDET = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBXMDET(self)
        self.zz_fdict['CLKMULTENBBXMDET'] = self.CLKMULTENBBXMDET
        self.CLKMULTENCFDET = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENCFDET(self)
        self.zz_fdict['CLKMULTENCFDET'] = self.CLKMULTENCFDET
        self.CLKMULTENDITHER = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDITHER(self)
        self.zz_fdict['CLKMULTENDITHER'] = self.CLKMULTENDITHER
        self.CLKMULTENDRVADC = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVADC(self)
        self.zz_fdict['CLKMULTENDRVADC'] = self.CLKMULTENDRVADC
        self.CLKMULTENDRVN = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVN(self)
        self.zz_fdict['CLKMULTENDRVN'] = self.CLKMULTENDRVN
        self.CLKMULTENDRVP = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVP(self)
        self.zz_fdict['CLKMULTENDRVP'] = self.CLKMULTENDRVP
        self.CLKMULTENDRVRX2P4G = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRX2P4G(self)
        self.zz_fdict['CLKMULTENDRVRX2P4G'] = self.CLKMULTENDRVRX2P4G
        self.CLKMULTENDRVRXSUBG = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRXSUBG(self)
        self.zz_fdict['CLKMULTENDRVRXSUBG'] = self.CLKMULTENDRVRXSUBG
        self.CLKMULTENDRVTXDUALB = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVTXDUALB(self)
        self.zz_fdict['CLKMULTENDRVTXDUALB'] = self.CLKMULTENDRVTXDUALB
        self.CLKMULTENFBDIV = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENFBDIV(self)
        self.zz_fdict['CLKMULTENFBDIV'] = self.CLKMULTENFBDIV
        self.CLKMULTENREFDIV = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREFDIV(self)
        self.zz_fdict['CLKMULTENREFDIV'] = self.CLKMULTENREFDIV
        self.CLKMULTENREG1 = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1(self)
        self.zz_fdict['CLKMULTENREG1'] = self.CLKMULTENREG1
        self.CLKMULTENREG2 = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG2(self)
        self.zz_fdict['CLKMULTENREG2'] = self.CLKMULTENREG2
        self.CLKMULTENREG3 = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG3(self)
        self.zz_fdict['CLKMULTENREG3'] = self.CLKMULTENREG3
        self.CLKMULTENROTDET = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENROTDET(self)
        self.zz_fdict['CLKMULTENROTDET'] = self.CLKMULTENROTDET
        self.CLKMULTENBYPASS40MHZ = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBYPASS40MHZ(self)
        self.zz_fdict['CLKMULTENBYPASS40MHZ'] = self.CLKMULTENBYPASS40MHZ
        self.CLKMULTFREQCAL = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTFREQCAL(self)
        self.zz_fdict['CLKMULTFREQCAL'] = self.CLKMULTFREQCAL
        self.CLKMULTREG2ADJI = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJI(self)
        self.zz_fdict['CLKMULTREG2ADJI'] = self.CLKMULTREG2ADJI
        self.CLKMULTREG1ADJV = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG1ADJV(self)
        self.zz_fdict['CLKMULTREG1ADJV'] = self.CLKMULTREG1ADJV
        self.CLKMULTREG2ADJV = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJV(self)
        self.zz_fdict['CLKMULTREG2ADJV'] = self.CLKMULTREG2ADJV
        self.CLKMULTREG3ADJV = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG3ADJV(self)
        self.zz_fdict['CLKMULTREG3ADJV'] = self.CLKMULTREG3ADJV
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CLKMULTEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CLKMULTEN1, self).__init__(rmio, label,
            0xb8020000, 0x0DC,
            'CLKMULTEN1', 'RAC_NS.CLKMULTEN1', 'read-write',
            u"",
            0x00000188, 0x0001FDEF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTINNIBBLE = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTINNIBBLE(self)
        self.zz_fdict['CLKMULTINNIBBLE'] = self.CLKMULTINNIBBLE
        self.CLKMULTLDFNIB = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDFNIB(self)
        self.zz_fdict['CLKMULTLDFNIB'] = self.CLKMULTLDFNIB
        self.CLKMULTLDMNIB = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDMNIB(self)
        self.zz_fdict['CLKMULTLDMNIB'] = self.CLKMULTLDMNIB
        self.CLKMULTRDNIBBLE = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTRDNIBBLE(self)
        self.zz_fdict['CLKMULTRDNIBBLE'] = self.CLKMULTRDNIBBLE
        self.CLKMULTLDCNIB = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDCNIB(self)
        self.zz_fdict['CLKMULTLDCNIB'] = self.CLKMULTLDCNIB
        self.CLKMULTDRVAMPSEL = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDRVAMPSEL(self)
        self.zz_fdict['CLKMULTDRVAMPSEL'] = self.CLKMULTDRVAMPSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CLKMULTCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CLKMULTCTRL, self).__init__(rmio, label,
            0xb8020000, 0x0E0,
            'CLKMULTCTRL', 'RAC_NS.CLKMULTCTRL', 'read-write',
            u"",
            0x000000C0, 0x00007FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTDIVN = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVN(self)
        self.zz_fdict['CLKMULTDIVN'] = self.CLKMULTDIVN
        self.CLKMULTDIVR = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVR(self)
        self.zz_fdict['CLKMULTDIVR'] = self.CLKMULTDIVR
        self.CLKMULTDIVX = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVX(self)
        self.zz_fdict['CLKMULTDIVX'] = self.CLKMULTDIVX
        self.CLKMULTENRESYNC = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTENRESYNC(self)
        self.zz_fdict['CLKMULTENRESYNC'] = self.CLKMULTENRESYNC
        self.CLKMULTVALID = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTVALID(self)
        self.zz_fdict['CLKMULTVALID'] = self.CLKMULTVALID
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CLKMULTSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CLKMULTSTATUS, self).__init__(rmio, label,
            0xb8020000, 0x0E4,
            'CLKMULTSTATUS', 'RAC_NS.CLKMULTSTATUS', 'read-only',
            u"",
            0x00000000, 0x0000001F,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTOUTNIBBLE = RM_Field_RAC_NS_CLKMULTSTATUS_CLKMULTOUTNIBBLE(self)
        self.zz_fdict['CLKMULTOUTNIBBLE'] = self.CLKMULTOUTNIBBLE
        self.CLKMULTACKVALID = RM_Field_RAC_NS_CLKMULTSTATUS_CLKMULTACKVALID(self)
        self.zz_fdict['CLKMULTACKVALID'] = self.CLKMULTACKVALID
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCDBG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCDBG, self).__init__(rmio, label,
            0xb8020000, 0x0E8,
            'IFADCDBG', 'RAC_NS.IFADCDBG', 'read-write',
            u"",
            0x0000000E, 0x0000007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCENADC = RM_Field_RAC_NS_IFADCDBG_IFADCENADC(self)
        self.zz_fdict['IFADCENADC'] = self.IFADCENADC
        self.IFADCENCLK = RM_Field_RAC_NS_IFADCDBG_IFADCENCLK(self)
        self.zz_fdict['IFADCENCLK'] = self.IFADCENCLK
        self.IFADCENREFBUF = RM_Field_RAC_NS_IFADCDBG_IFADCENREFBUF(self)
        self.zz_fdict['IFADCENREFBUF'] = self.IFADCENREFBUF
        self.IFADCENSIDETONE = RM_Field_RAC_NS_IFADCDBG_IFADCENSIDETONE(self)
        self.zz_fdict['IFADCENSIDETONE'] = self.IFADCENSIDETONE
        self.IFADCINVERTCLK = RM_Field_RAC_NS_IFADCDBG_IFADCINVERTCLK(self)
        self.zz_fdict['IFADCINVERTCLK'] = self.IFADCINVERTCLK
        self.IFADCSHORTINPUT = RM_Field_RAC_NS_IFADCDBG_IFADCSHORTINPUT(self)
        self.zz_fdict['IFADCSHORTINPUT'] = self.IFADCSHORTINPUT
        self.IFADCDISABLECLK = RM_Field_RAC_NS_IFADCDBG_IFADCDISABLECLK(self)
        self.zz_fdict['IFADCDISABLECLK'] = self.IFADCDISABLECLK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCTRIM0, self).__init__(rmio, label,
            0xb8020000, 0x0EC,
            'IFADCTRIM0', 'RAC_NS.IFADCTRIM0', 'read-write',
            u"",
            0x11512C6C, 0x7FFFFFFD,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCCLKSEL = RM_Field_RAC_NS_IFADCTRIM0_IFADCCLKSEL(self)
        self.zz_fdict['IFADCCLKSEL'] = self.IFADCCLKSEL
        self.IFADCLDOSERIESAMPLVL = RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSERIESAMPLVL(self)
        self.zz_fdict['IFADCLDOSERIESAMPLVL'] = self.IFADCLDOSERIESAMPLVL
        self.IFADCLDOSHUNTAMPLVL1 = RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1(self)
        self.zz_fdict['IFADCLDOSHUNTAMPLVL1'] = self.IFADCLDOSHUNTAMPLVL1
        self.IFADCLDOSHUNTAMPLVL2 = RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2(self)
        self.zz_fdict['IFADCLDOSHUNTAMPLVL2'] = self.IFADCLDOSHUNTAMPLVL2
        self.IFADCLDOSHUNTCURLVL1 = RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTCURLVL1(self)
        self.zz_fdict['IFADCLDOSHUNTCURLVL1'] = self.IFADCLDOSHUNTCURLVL1
        self.IFADCLDOSHUNTCURLVL2 = RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTCURLVL2(self)
        self.zz_fdict['IFADCLDOSHUNTCURLVL2'] = self.IFADCLDOSHUNTCURLVL2
        self.IFADCOTACURRENT = RM_Field_RAC_NS_IFADCTRIM0_IFADCOTACURRENT(self)
        self.zz_fdict['IFADCOTACURRENT'] = self.IFADCOTACURRENT
        self.IFADCREFBUFAMPLVL = RM_Field_RAC_NS_IFADCTRIM0_IFADCREFBUFAMPLVL(self)
        self.zz_fdict['IFADCREFBUFAMPLVL'] = self.IFADCREFBUFAMPLVL
        self.IFADCREFBUFCURLVL = RM_Field_RAC_NS_IFADCTRIM0_IFADCREFBUFCURLVL(self)
        self.zz_fdict['IFADCREFBUFCURLVL'] = self.IFADCREFBUFCURLVL
        self.IFADCSIDETONEAMP = RM_Field_RAC_NS_IFADCTRIM0_IFADCSIDETONEAMP(self)
        self.zz_fdict['IFADCSIDETONEAMP'] = self.IFADCSIDETONEAMP
        self.IFADCSIDETONEFREQ = RM_Field_RAC_NS_IFADCTRIM0_IFADCSIDETONEFREQ(self)
        self.zz_fdict['IFADCSIDETONEFREQ'] = self.IFADCSIDETONEFREQ
        self.IFADCENHALFMODE = RM_Field_RAC_NS_IFADCTRIM0_IFADCENHALFMODE(self)
        self.zz_fdict['IFADCENHALFMODE'] = self.IFADCENHALFMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCTRIM1, self).__init__(rmio, label,
            0xb8020000, 0x0F0,
            'IFADCTRIM1', 'RAC_NS.IFADCTRIM1', 'read-write',
            u"",
            0x00000123, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCVCMLVL = RM_Field_RAC_NS_IFADCTRIM1_IFADCVCMLVL(self)
        self.zz_fdict['IFADCVCMLVL'] = self.IFADCVCMLVL
        self.IFADCENNEGRES = RM_Field_RAC_NS_IFADCTRIM1_IFADCENNEGRES(self)
        self.zz_fdict['IFADCENNEGRES'] = self.IFADCENNEGRES
        self.IFADCNEGRESCURRENT = RM_Field_RAC_NS_IFADCTRIM1_IFADCNEGRESCURRENT(self)
        self.zz_fdict['IFADCNEGRESCURRENT'] = self.IFADCNEGRESCURRENT
        self.IFADCNEGRESVCM = RM_Field_RAC_NS_IFADCTRIM1_IFADCNEGRESVCM(self)
        self.zz_fdict['IFADCNEGRESVCM'] = self.IFADCNEGRESVCM
        self.IFADCENSUBGMODE = RM_Field_RAC_NS_IFADCTRIM1_IFADCENSUBGMODE(self)
        self.zz_fdict['IFADCENSUBGMODE'] = self.IFADCENSUBGMODE
        self.IFADCTZ = RM_Field_RAC_NS_IFADCTRIM1_IFADCTZ(self)
        self.zz_fdict['IFADCTZ'] = self.IFADCTZ
        self.IFADCENXOBYPASS = RM_Field_RAC_NS_IFADCTRIM1_IFADCENXOBYPASS(self)
        self.zz_fdict['IFADCENXOBYPASS'] = self.IFADCENXOBYPASS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCCAL, self).__init__(rmio, label,
            0xb8020000, 0x0F4,
            'IFADCCAL', 'RAC_NS.IFADCCAL', 'read-write',
            u"",
            0x00000C00, 0x00FF1F03,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCENRCCAL = RM_Field_RAC_NS_IFADCCAL_IFADCENRCCAL(self)
        self.zz_fdict['IFADCENRCCAL'] = self.IFADCENRCCAL
        self.IFADCTUNERCCALMODE = RM_Field_RAC_NS_IFADCCAL_IFADCTUNERCCALMODE(self)
        self.zz_fdict['IFADCTUNERCCALMODE'] = self.IFADCTUNERCCALMODE
        self.IFADCTUNERC = RM_Field_RAC_NS_IFADCCAL_IFADCTUNERC(self)
        self.zz_fdict['IFADCTUNERC'] = self.IFADCTUNERC
        self.IFADCRCCALCOUNTERSTARTVAL = RM_Field_RAC_NS_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL(self)
        self.zz_fdict['IFADCRCCALCOUNTERSTARTVAL'] = self.IFADCRCCALCOUNTERSTARTVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCSTATUS, self).__init__(rmio, label,
            0xb8020000, 0x0F8,
            'IFADCSTATUS', 'RAC_NS.IFADCSTATUS', 'read-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCRCCALOUT = RM_Field_RAC_NS_IFADCSTATUS_IFADCRCCALOUT(self)
        self.zz_fdict['IFADCRCCALOUT'] = self.IFADCRCCALOUT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXDEBUG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXDEBUG, self).__init__(rmio, label,
            0xb8020000, 0x0FC,
            'LNAMIXDEBUG', 'RAC_NS.LNAMIXDEBUG', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXDISMXR0 = RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR0(self)
        self.zz_fdict['LNAMIXDISMXR0'] = self.LNAMIXDISMXR0
        self.LNAMIXDISMXR1 = RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR1(self)
        self.zz_fdict['LNAMIXDISMXR1'] = self.LNAMIXDISMXR1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM0, self).__init__(rmio, label,
            0xb8020000, 0x100,
            'LNAMIXTRIM0', 'RAC_NS.LNAMIXTRIM0', 'read-write',
            u"",
            0x00000110, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXLNA0CAPSEL = RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXLNA0CAPSEL(self)
        self.zz_fdict['LNAMIXLNA0CAPSEL'] = self.LNAMIXLNA0CAPSEL
        self.LNAMIXMXRBIAS0 = RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXMXRBIAS0(self)
        self.zz_fdict['LNAMIXMXRBIAS0'] = self.LNAMIXMXRBIAS0
        self.LNAMIXVOUT0ADJ = RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXVOUT0ADJ(self)
        self.zz_fdict['LNAMIXVOUT0ADJ'] = self.LNAMIXVOUT0ADJ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM1, self).__init__(rmio, label,
            0xb8020000, 0x104,
            'LNAMIXTRIM1', 'RAC_NS.LNAMIXTRIM1', 'read-write',
            u"",
            0x00000110, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXLNA1CAPSEL = RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXLNA1CAPSEL(self)
        self.zz_fdict['LNAMIXLNA1CAPSEL'] = self.LNAMIXLNA1CAPSEL
        self.LNAMIXMXRBIAS1 = RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXMXRBIAS1(self)
        self.zz_fdict['LNAMIXMXRBIAS1'] = self.LNAMIXMXRBIAS1
        self.LNAMIXVOUT1ADJ = RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXVOUT1ADJ(self)
        self.zz_fdict['LNAMIXVOUT1ADJ'] = self.LNAMIXVOUT1ADJ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM2, self).__init__(rmio, label,
            0xb8020000, 0x108,
            'LNAMIXTRIM2', 'RAC_NS.LNAMIXTRIM2', 'read-write',
            u"",
            0x0115E3D0, 0x01FFFFF0,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXCURCTRL = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXCURCTRL(self)
        self.zz_fdict['LNAMIXCURCTRL'] = self.LNAMIXCURCTRL
        self.LNAMIXHIGHCUR = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXHIGHCUR(self)
        self.zz_fdict['LNAMIXHIGHCUR'] = self.LNAMIXHIGHCUR
        self.LNAMIXLOWCUR = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXLOWCUR(self)
        self.zz_fdict['LNAMIXLOWCUR'] = self.LNAMIXLOWCUR
        self.LNAMIXLNARESADJ = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXLNARESADJ(self)
        self.zz_fdict['LNAMIXLNARESADJ'] = self.LNAMIXLNARESADJ
        self.LNAMIXNCASADJ = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXNCASADJ(self)
        self.zz_fdict['LNAMIXNCASADJ'] = self.LNAMIXNCASADJ
        self.LNAMIXPCASADJ = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXPCASADJ(self)
        self.zz_fdict['LNAMIXPCASADJ'] = self.LNAMIXPCASADJ
        self.LNAMIXTRIMVREG = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXTRIMVREG(self)
        self.zz_fdict['LNAMIXTRIMVREG'] = self.LNAMIXTRIMVREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM3, self).__init__(rmio, label,
            0xb8020000, 0x10C,
            'LNAMIXTRIM3', 'RAC_NS.LNAMIXTRIM3', 'read-write',
            u"",
            0x00002A10, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXIBIASADJN = RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASADJN(self)
        self.zz_fdict['LNAMIXIBIASADJN'] = self.LNAMIXIBIASADJN
        self.LNAMIXIBIASADJP = RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASADJP(self)
        self.zz_fdict['LNAMIXIBIASADJP'] = self.LNAMIXIBIASADJP
        self.LNAMIXIBIASRANGEADJN = RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASRANGEADJN(self)
        self.zz_fdict['LNAMIXIBIASRANGEADJN'] = self.LNAMIXIBIASRANGEADJN
        self.LNAMIXIBIASRANGEADJP = RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASRANGEADJP(self)
        self.zz_fdict['LNAMIXIBIASRANGEADJP'] = self.LNAMIXIBIASRANGEADJP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM4, self).__init__(rmio, label,
            0xb8020000, 0x110,
            'LNAMIXTRIM4', 'RAC_NS.LNAMIXTRIM4', 'read-write',
            u"",
            0x52082002, 0xFF0FFF03,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXRFPKDBWSEL = RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDBWSEL(self)
        self.zz_fdict['LNAMIXRFPKDBWSEL'] = self.LNAMIXRFPKDBWSEL
        self.LNAMIXRFPKDCALCMLO = RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO(self)
        self.zz_fdict['LNAMIXRFPKDCALCMLO'] = self.LNAMIXRFPKDCALCMLO
        self.LNAMIXRFPKDCALCMHI = RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI(self)
        self.zz_fdict['LNAMIXRFPKDCALCMHI'] = self.LNAMIXRFPKDCALCMHI
        self.LNAMIXRFPKDTHRESHSELLO = RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO(self)
        self.zz_fdict['LNAMIXRFPKDTHRESHSELLO'] = self.LNAMIXRFPKDTHRESHSELLO
        self.LNAMIXRFPKDTHRESHSELHI = RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI(self)
        self.zz_fdict['LNAMIXRFPKDTHRESHSELHI'] = self.LNAMIXRFPKDTHRESHSELHI
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXCAL, self).__init__(rmio, label,
            0xb8020000, 0x114,
            'LNAMIXCAL', 'RAC_NS.LNAMIXCAL', 'read-write',
            u"",
            0x000007E0, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXCALPMOSEN = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALPMOSEN(self)
        self.zz_fdict['LNAMIXCALPMOSEN'] = self.LNAMIXCALPMOSEN
        self.LNAMIXCALNMOSEN = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALNMOSEN(self)
        self.zz_fdict['LNAMIXCALNMOSEN'] = self.LNAMIXCALNMOSEN
        self.LNAMIXCALVMODE = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALVMODE(self)
        self.zz_fdict['LNAMIXCALVMODE'] = self.LNAMIXCALVMODE
        self.LNAMIXENIRCAL0 = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL0(self)
        self.zz_fdict['LNAMIXENIRCAL0'] = self.LNAMIXENIRCAL0
        self.LNAMIXENIRCAL1 = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL1(self)
        self.zz_fdict['LNAMIXENIRCAL1'] = self.LNAMIXENIRCAL1
        self.LNAMIXIRCAL0AMP = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL0AMP(self)
        self.zz_fdict['LNAMIXIRCAL0AMP'] = self.LNAMIXIRCAL0AMP
        self.LNAMIXIRCAL1AMP = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL1AMP(self)
        self.zz_fdict['LNAMIXIRCAL1AMP'] = self.LNAMIXIRCAL1AMP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXEN, self).__init__(rmio, label,
            0xb8020000, 0x118,
            'LNAMIXEN', 'RAC_NS.LNAMIXEN', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXENAMP0 = RM_Field_RAC_NS_LNAMIXEN_LNAMIXENAMP0(self)
        self.zz_fdict['LNAMIXENAMP0'] = self.LNAMIXENAMP0
        self.LNAMIXENAMP1 = RM_Field_RAC_NS_LNAMIXEN_LNAMIXENAMP1(self)
        self.zz_fdict['LNAMIXENAMP1'] = self.LNAMIXENAMP1
        self.LNAMIXENBIAS = RM_Field_RAC_NS_LNAMIXEN_LNAMIXENBIAS(self)
        self.zz_fdict['LNAMIXENBIAS'] = self.LNAMIXENBIAS
        self.LNAMIXENLDO = RM_Field_RAC_NS_LNAMIXEN_LNAMIXENLDO(self)
        self.zz_fdict['LNAMIXENLDO'] = self.LNAMIXENLDO
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PRECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PRECTRL, self).__init__(rmio, label,
            0xb8020000, 0x11C,
            'PRECTRL', 'RAC_NS.PRECTRL', 'read-write',
            u"",
            0x00000026, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREBYPFORCE = RM_Field_RAC_NS_PRECTRL_PREBYPFORCE(self)
        self.zz_fdict['PREBYPFORCE'] = self.PREBYPFORCE
        self.PREREGTRIM = RM_Field_RAC_NS_PRECTRL_PREREGTRIM(self)
        self.zz_fdict['PREREGTRIM'] = self.PREREGTRIM
        self.PREVREFTRIM = RM_Field_RAC_NS_PRECTRL_PREVREFTRIM(self)
        self.zz_fdict['PREVREFTRIM'] = self.PREVREFTRIM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PATRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PATRIM0, self).__init__(rmio, label,
            0xb8020000, 0x120,
            'PATRIM0', 'RAC_NS.PATRIM0', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXTRIMLPAVMID = RM_Field_RAC_NS_PATRIM0_TXTRIMLPAVMID(self)
        self.zz_fdict['TXTRIMLPAVMID'] = self.TXTRIMLPAVMID
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PATRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PATRIM1, self).__init__(rmio, label,
            0xb8020000, 0x124,
            'PATRIM1', 'RAC_NS.PATRIM1', 'read-write',
            u"",
            0x0000235B, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXTRIMXPAVNB = RM_Field_RAC_NS_PATRIM1_TXTRIMXPAVNB(self)
        self.zz_fdict['TXTRIMXPAVNB'] = self.TXTRIMXPAVNB
        self.TXTRIMXPAVPB = RM_Field_RAC_NS_PATRIM1_TXTRIMXPAVPB(self)
        self.zz_fdict['TXTRIMXPAVPB'] = self.TXTRIMXPAVPB
        self.TXTRIMHPAVMID = RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVMID(self)
        self.zz_fdict['TXTRIMHPAVMID'] = self.TXTRIMHPAVMID
        self.TXTRIMHPAVNCAS = RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVNCAS(self)
        self.zz_fdict['TXTRIMHPAVNCAS'] = self.TXTRIMHPAVNCAS
        self.TXTRIMHPAVPCAS = RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVPCAS(self)
        self.zz_fdict['TXTRIMHPAVPCAS'] = self.TXTRIMHPAVPCAS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PATRIM2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PATRIM2, self).__init__(rmio, label,
            0xb8020000, 0x128,
            'PATRIM2', 'RAC_NS.PATRIM2', 'read-write',
            u"",
            0x00007777, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXTRIMCLKGENDUTYN = RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENDUTYN(self)
        self.zz_fdict['TXTRIMCLKGENDUTYN'] = self.TXTRIMCLKGENDUTYN
        self.TXTRIMCLKGENDUTYP = RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENDUTYP(self)
        self.zz_fdict['TXTRIMCLKGENDUTYP'] = self.TXTRIMCLKGENDUTYP
        self.TXTRIMCLKGENNOVFALL = RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENNOVFALL(self)
        self.zz_fdict['TXTRIMCLKGENNOVFALL'] = self.TXTRIMCLKGENNOVFALL
        self.TXTRIMCLKGENNOVRISE = RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENNOVRISE(self)
        self.zz_fdict['TXTRIMCLKGENNOVRISE'] = self.TXTRIMCLKGENNOVRISE
        self.TXTRIMDRVEDGENN = RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGENN(self)
        self.zz_fdict['TXTRIMDRVEDGENN'] = self.TXTRIMDRVEDGENN
        self.TXTRIMDRVEDGENP = RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGENP(self)
        self.zz_fdict['TXTRIMDRVEDGENP'] = self.TXTRIMDRVEDGENP
        self.TXTRIMDRVEDGEPN = RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGEPN(self)
        self.zz_fdict['TXTRIMDRVEDGEPN'] = self.TXTRIMDRVEDGEPN
        self.TXTRIMDRVEDGEPP = RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGEPP(self)
        self.zz_fdict['TXTRIMDRVEDGEPP'] = self.TXTRIMDRVEDGEPP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PATRIM3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PATRIM3, self).__init__(rmio, label,
            0xb8020000, 0x12C,
            'PATRIM3', 'RAC_NS.PATRIM3', 'read-write',
            u"",
            0x00910CAA, 0x1FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXTRIMDREGBLEED = RM_Field_RAC_NS_PATRIM3_TXTRIMDREGBLEED(self)
        self.zz_fdict['TXTRIMDREGBLEED'] = self.TXTRIMDREGBLEED
        self.TXTRIMDREGBLEEDAUTO = RM_Field_RAC_NS_PATRIM3_TXTRIMDREGBLEEDAUTO(self)
        self.zz_fdict['TXTRIMDREGBLEEDAUTO'] = self.TXTRIMDREGBLEEDAUTO
        self.TXTRIMOREGBLEEDAUTO = RM_Field_RAC_NS_PATRIM3_TXTRIMOREGBLEEDAUTO(self)
        self.zz_fdict['TXTRIMOREGBLEEDAUTO'] = self.TXTRIMOREGBLEEDAUTO
        self.TXTRIMDREGFB = RM_Field_RAC_NS_PATRIM3_TXTRIMDREGFB(self)
        self.zz_fdict['TXTRIMDREGFB'] = self.TXTRIMDREGFB
        self.TXTRIMOREGFB = RM_Field_RAC_NS_PATRIM3_TXTRIMOREGFB(self)
        self.zz_fdict['TXTRIMOREGFB'] = self.TXTRIMOREGFB
        self.TXTRIMDREG = RM_Field_RAC_NS_PATRIM3_TXTRIMDREG(self)
        self.zz_fdict['TXTRIMDREG'] = self.TXTRIMDREG
        self.TXTRIMOREG = RM_Field_RAC_NS_PATRIM3_TXTRIMOREG(self)
        self.zz_fdict['TXTRIMOREG'] = self.TXTRIMOREG
        self.TXTRIMRREG = RM_Field_RAC_NS_PATRIM3_TXTRIMRREG(self)
        self.zz_fdict['TXTRIMRREG'] = self.TXTRIMRREG
        self.TXTRIMDREGPSR = RM_Field_RAC_NS_PATRIM3_TXTRIMDREGPSR(self)
        self.zz_fdict['TXTRIMDREGPSR'] = self.TXTRIMDREGPSR
        self.TXTRIMOREGPSR = RM_Field_RAC_NS_PATRIM3_TXTRIMOREGPSR(self)
        self.zz_fdict['TXTRIMOREGPSR'] = self.TXTRIMOREGPSR
        self.TXTRIMDREGSLICES = RM_Field_RAC_NS_PATRIM3_TXTRIMDREGSLICES(self)
        self.zz_fdict['TXTRIMDREGSLICES'] = self.TXTRIMDREGSLICES
        self.TXTRIMOREGSLICES = RM_Field_RAC_NS_PATRIM3_TXTRIMOREGSLICES(self)
        self.zz_fdict['TXTRIMOREGSLICES'] = self.TXTRIMOREGSLICES
        self.TXTRIMDREGMOREBW = RM_Field_RAC_NS_PATRIM3_TXTRIMDREGMOREBW(self)
        self.zz_fdict['TXTRIMDREGMOREBW'] = self.TXTRIMDREGMOREBW
        self.TXTRIMOREGMOREBW = RM_Field_RAC_NS_PATRIM3_TXTRIMOREGMOREBW(self)
        self.zz_fdict['TXTRIMOREGMOREBW'] = self.TXTRIMOREGMOREBW
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PATRIM4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PATRIM4, self).__init__(rmio, label,
            0xb8020000, 0x130,
            'PATRIM4', 'RAC_NS.PATRIM4', 'read-write',
            u"",
            0x00FC0075, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXTRIMXPAVNBDRV = RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVNBDRV(self)
        self.zz_fdict['TXTRIMXPAVNBDRV'] = self.TXTRIMXPAVNBDRV
        self.TXTRIMXPAVPBDRV = RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVPBDRV(self)
        self.zz_fdict['TXTRIMXPAVPBDRV'] = self.TXTRIMXPAVPBDRV
        self.TXTRIMXPAVXSCURRENT = RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVXSCURRENT(self)
        self.zz_fdict['TXTRIMXPAVXSCURRENT'] = self.TXTRIMXPAVXSCURRENT
        self.TXXPAVXSCURRENTCOARSE = RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTCOARSE(self)
        self.zz_fdict['TXXPAVXSCURRENTCOARSE'] = self.TXXPAVXSCURRENTCOARSE
        self.TXXPAVXSCURRENTCOARSEMIN = RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTCOARSEMIN(self)
        self.zz_fdict['TXXPAVXSCURRENTCOARSEMIN'] = self.TXXPAVXSCURRENTCOARSEMIN
        self.TXXPAVXSCURRENTFINE = RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTFINE(self)
        self.zz_fdict['TXXPAVXSCURRENTFINE'] = self.TXXPAVXSCURRENTFINE
        self.TXXPAVXSCURRENTSELHPA = RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTSELHPA(self)
        self.zz_fdict['TXXPAVXSCURRENTSELHPA'] = self.TXXPAVXSCURRENTSELHPA
        self.TXVXSCURRENTVREFN = RM_Field_RAC_NS_PATRIM4_TXVXSCURRENTVREFN(self)
        self.zz_fdict['TXVXSCURRENTVREFN'] = self.TXVXSCURRENTVREFN
        self.TXVXSCURRENTVREFP = RM_Field_RAC_NS_PATRIM4_TXVXSCURRENTVREFP(self)
        self.zz_fdict['TXVXSCURRENTVREFP'] = self.TXVXSCURRENTVREFP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PATRIM5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PATRIM5, self).__init__(rmio, label,
            0xb8020000, 0x134,
            'PATRIM5', 'RAC_NS.PATRIM5', 'read-write',
            u"",
            0x000000FC, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXVNSRAIL = RM_Field_RAC_NS_PATRIM5_TXVNSRAIL(self)
        self.zz_fdict['TXVNSRAIL'] = self.TXVNSRAIL
        self.TXVPSRAIL = RM_Field_RAC_NS_PATRIM5_TXVPSRAIL(self)
        self.zz_fdict['TXVPSRAIL'] = self.TXVPSRAIL
        self.TXTRIMXPAVNS = RM_Field_RAC_NS_PATRIM5_TXTRIMXPAVNS(self)
        self.zz_fdict['TXTRIMXPAVNS'] = self.TXTRIMXPAVNS
        self.TXTRIMXPAVPS = RM_Field_RAC_NS_PATRIM5_TXTRIMXPAVPS(self)
        self.zz_fdict['TXTRIMXPAVPS'] = self.TXTRIMXPAVPS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PADEBUG0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PADEBUG0, self).__init__(rmio, label,
            0xb8020000, 0x138,
            'PADEBUG0', 'RAC_NS.PADEBUG0', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXOREGBYPASS = RM_Field_RAC_NS_PADEBUG0_TXOREGBYPASS(self)
        self.zz_fdict['TXOREGBYPASS'] = self.TXOREGBYPASS
        self.TXDREGBYPASS = RM_Field_RAC_NS_PADEBUG0_TXDREGBYPASS(self)
        self.zz_fdict['TXDREGBYPASS'] = self.TXDREGBYPASS
        self.TXRREGBYPASS = RM_Field_RAC_NS_PADEBUG0_TXRREGBYPASS(self)
        self.zz_fdict['TXRREGBYPASS'] = self.TXRREGBYPASS
        self.TXPDNVDDPA = RM_Field_RAC_NS_PADEBUG0_TXPDNVDDPA(self)
        self.zz_fdict['TXPDNVDDPA'] = self.TXPDNVDDPA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXPOWER(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXPOWER, self).__init__(rmio, label,
            0xb8020000, 0x13C,
            'TXPOWER', 'RAC_NS.TXPOWER', 'read-write',
            u"",
            0x007FE020, 0x007FEEFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXSTRIPE = RM_Field_RAC_NS_TXPOWER_TXSTRIPE(self)
        self.zz_fdict['TXSTRIPE'] = self.TXSTRIPE
        self.TXSLICE = RM_Field_RAC_NS_TXPOWER_TXSLICE(self)
        self.zz_fdict['TXSLICE'] = self.TXSLICE
        self.TXDRVSLICE = RM_Field_RAC_NS_TXPOWER_TXDRVSLICE(self)
        self.zz_fdict['TXDRVSLICE'] = self.TXDRVSLICE
        self.TXANARAMPODEV = RM_Field_RAC_NS_TXPOWER_TXANARAMPODEV(self)
        self.zz_fdict['TXANARAMPODEV'] = self.TXANARAMPODEV
        self.TXANARAMPDRVFF = RM_Field_RAC_NS_TXPOWER_TXANARAMPDRVFF(self)
        self.zz_fdict['TXANARAMPDRVFF'] = self.TXANARAMPDRVFF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXRAMP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXRAMP, self).__init__(rmio, label,
            0xb8020000, 0x140,
            'TXRAMP', 'RAC_NS.TXRAMP', 'read-write',
            u"",
            0x0000003F, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXANARAMPDRVBW = RM_Field_RAC_NS_TXRAMP_TXANARAMPDRVBW(self)
        self.zz_fdict['TXANARAMPDRVBW'] = self.TXANARAMPDRVBW
        self.TXANARAMPDRVEN = RM_Field_RAC_NS_TXRAMP_TXANARAMPDRVEN(self)
        self.zz_fdict['TXANARAMPDRVEN'] = self.TXANARAMPDRVEN
        self.TXANARAMPODEVBW = RM_Field_RAC_NS_TXRAMP_TXANARAMPODEVBW(self)
        self.zz_fdict['TXANARAMPODEVBW'] = self.TXANARAMPODEVBW
        self.TXANARAMPODEVEN = RM_Field_RAC_NS_TXRAMP_TXANARAMPODEVEN(self)
        self.zz_fdict['TXANARAMPODEVEN'] = self.TXANARAMPODEVEN
        self.TXBYPASSRAMPCLK = RM_Field_RAC_NS_TXRAMP_TXBYPASSRAMPCLK(self)
        self.zz_fdict['TXBYPASSRAMPCLK'] = self.TXBYPASSRAMPCLK
        self.TXMODEPHASEFLIP = RM_Field_RAC_NS_TXRAMP_TXMODEPHASEFLIP(self)
        self.zz_fdict['TXMODEPHASEFLIP'] = self.TXMODEPHASEFLIP
        self.TXPHASEDIGITAL = RM_Field_RAC_NS_TXRAMP_TXPHASEDIGITAL(self)
        self.zz_fdict['TXPHASEDIGITAL'] = self.TXPHASEDIGITAL
        self.TXRESETPAPOWER = RM_Field_RAC_NS_TXRAMP_TXRESETPAPOWER(self)
        self.zz_fdict['TXRESETPAPOWER'] = self.TXRESETPAPOWER
        self.TXUNMUTEENDRVFF = RM_Field_RAC_NS_TXRAMP_TXUNMUTEENDRVFF(self)
        self.zz_fdict['TXUNMUTEENDRVFF'] = self.TXUNMUTEENDRVFF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PGADEBUG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PGADEBUG, self).__init__(rmio, label,
            0xb8020000, 0x144,
            'PGADEBUG', 'RAC_NS.PGADEBUG', 'read-write',
            u"",
            0x00000004, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.PGACCTRIM = RM_Field_RAC_NS_PGADEBUG_PGACCTRIM(self)
        self.zz_fdict['PGACCTRIM'] = self.PGACCTRIM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PGATRIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PGATRIM, self).__init__(rmio, label,
            0xb8020000, 0x148,
            'PGATRIM', 'RAC_NS.PGATRIM', 'read-write',
            u"",
            0x00000547, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PGACTUNE = RM_Field_RAC_NS_PGATRIM_PGACTUNE(self)
        self.zz_fdict['PGACTUNE'] = self.PGACTUNE
        self.PGADISANTILOCK = RM_Field_RAC_NS_PGATRIM_PGADISANTILOCK(self)
        self.zz_fdict['PGADISANTILOCK'] = self.PGADISANTILOCK
        self.PGAVCMOUTTRIM = RM_Field_RAC_NS_PGATRIM_PGAVCMOUTTRIM(self)
        self.zz_fdict['PGAVCMOUTTRIM'] = self.PGAVCMOUTTRIM
        self.PGAVLDOTRIM = RM_Field_RAC_NS_PGATRIM_PGAVLDOTRIM(self)
        self.zz_fdict['PGAVLDOTRIM'] = self.PGAVLDOTRIM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PGACAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PGACAL, self).__init__(rmio, label,
            0xb8020000, 0x14C,
            'PGACAL', 'RAC_NS.PGACAL', 'read-write',
            u"",
            0x20202020, 0x3F3F3F3F,
            0x00001000, 0x00002000,
            0x00003000)

        self.PGAOFFNCALI = RM_Field_RAC_NS_PGACAL_PGAOFFNCALI(self)
        self.zz_fdict['PGAOFFNCALI'] = self.PGAOFFNCALI
        self.PGAOFFNCALQ = RM_Field_RAC_NS_PGACAL_PGAOFFNCALQ(self)
        self.zz_fdict['PGAOFFNCALQ'] = self.PGAOFFNCALQ
        self.PGAOFFPCALI = RM_Field_RAC_NS_PGACAL_PGAOFFPCALI(self)
        self.zz_fdict['PGAOFFPCALI'] = self.PGAOFFPCALI
        self.PGAOFFPCALQ = RM_Field_RAC_NS_PGACAL_PGAOFFPCALQ(self)
        self.zz_fdict['PGAOFFPCALQ'] = self.PGAOFFPCALQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PGACTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PGACTRL, self).__init__(rmio, label,
            0xb8020000, 0x150,
            'PGACTRL', 'RAC_NS.PGACTRL', 'read-write',
            u"",
            0x00000003, 0x00FFFEEF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PGABWMODE = RM_Field_RAC_NS_PGACTRL_PGABWMODE(self)
        self.zz_fdict['PGABWMODE'] = self.PGABWMODE
        self.PGAENBIAS = RM_Field_RAC_NS_PGACTRL_PGAENBIAS(self)
        self.zz_fdict['PGAENBIAS'] = self.PGAENBIAS
        self.PGAENGHZ = RM_Field_RAC_NS_PGACTRL_PGAENGHZ(self)
        self.zz_fdict['PGAENGHZ'] = self.PGAENGHZ
        self.PGAENLATCHI = RM_Field_RAC_NS_PGACTRL_PGAENLATCHI(self)
        self.zz_fdict['PGAENLATCHI'] = self.PGAENLATCHI
        self.PGAENLATCHQ = RM_Field_RAC_NS_PGACTRL_PGAENLATCHQ(self)
        self.zz_fdict['PGAENLATCHQ'] = self.PGAENLATCHQ
        self.PGAENLDOLOAD = RM_Field_RAC_NS_PGACTRL_PGAENLDOLOAD(self)
        self.zz_fdict['PGAENLDOLOAD'] = self.PGAENLDOLOAD
        self.PGAENPGAI = RM_Field_RAC_NS_PGACTRL_PGAENPGAI(self)
        self.zz_fdict['PGAENPGAI'] = self.PGAENPGAI
        self.PGAENPGAQ = RM_Field_RAC_NS_PGACTRL_PGAENPGAQ(self)
        self.zz_fdict['PGAENPGAQ'] = self.PGAENPGAQ
        self.PGAENPKD = RM_Field_RAC_NS_PGACTRL_PGAENPKD(self)
        self.zz_fdict['PGAENPKD'] = self.PGAENPKD
        self.PGAENRCMOUT = RM_Field_RAC_NS_PGACTRL_PGAENRCMOUT(self)
        self.zz_fdict['PGAENRCMOUT'] = self.PGAENRCMOUT
        self.PGAENSUBG = RM_Field_RAC_NS_PGACTRL_PGAENSUBG(self)
        self.zz_fdict['PGAENSUBG'] = self.PGAENSUBG
        self.PGAPOWERMODE = RM_Field_RAC_NS_PGACTRL_PGAPOWERMODE(self)
        self.zz_fdict['PGAPOWERMODE'] = self.PGAPOWERMODE
        self.PGATHRPKDLOSEL = RM_Field_RAC_NS_PGACTRL_PGATHRPKDLOSEL(self)
        self.zz_fdict['PGATHRPKDLOSEL'] = self.PGATHRPKDLOSEL
        self.PGATHRPKDHISEL = RM_Field_RAC_NS_PGACTRL_PGATHRPKDHISEL(self)
        self.zz_fdict['PGATHRPKDHISEL'] = self.PGATHRPKDHISEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFBIASCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFBIASCAL, self).__init__(rmio, label,
            0xb8020000, 0x154,
            'RFBIASCAL', 'RAC_NS.RFBIASCAL', 'read-write',
            u"",
            0x30203020, 0x3F3F3F3F,
            0x00001000, 0x00002000,
            0x00003000)

        self.RFBIASCALBIAS = RM_Field_RAC_NS_RFBIASCAL_RFBIASCALBIAS(self)
        self.zz_fdict['RFBIASCALBIAS'] = self.RFBIASCALBIAS
        self.RFBIASCALTC = RM_Field_RAC_NS_RFBIASCAL_RFBIASCALTC(self)
        self.zz_fdict['RFBIASCALTC'] = self.RFBIASCALTC
        self.RFBIASCALVREF = RM_Field_RAC_NS_RFBIASCAL_RFBIASCALVREF(self)
        self.zz_fdict['RFBIASCALVREF'] = self.RFBIASCALVREF
        self.RFBIASCALVREFSTARTUP = RM_Field_RAC_NS_RFBIASCAL_RFBIASCALVREFSTARTUP(self)
        self.zz_fdict['RFBIASCALVREFSTARTUP'] = self.RFBIASCALVREFSTARTUP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFBIASCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFBIASCTRL, self).__init__(rmio, label,
            0xb8020000, 0x158,
            'RFBIASCTRL', 'RAC_NS.RFBIASCTRL', 'read-write',
            u"",
            0x00040000, 0x000F001F,
            0x00001000, 0x00002000,
            0x00003000)

        self.RFBIASDISABLEBOOTSTRAP = RM_Field_RAC_NS_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP(self)
        self.zz_fdict['RFBIASDISABLEBOOTSTRAP'] = self.RFBIASDISABLEBOOTSTRAP
        self.RFBIASLDOHIGHCURRENT = RM_Field_RAC_NS_RFBIASCTRL_RFBIASLDOHIGHCURRENT(self)
        self.zz_fdict['RFBIASLDOHIGHCURRENT'] = self.RFBIASLDOHIGHCURRENT
        self.RFBIASNONFLASHMODE = RM_Field_RAC_NS_RFBIASCTRL_RFBIASNONFLASHMODE(self)
        self.zz_fdict['RFBIASNONFLASHMODE'] = self.RFBIASNONFLASHMODE
        self.RFBIASSTARTUPCORE = RM_Field_RAC_NS_RFBIASCTRL_RFBIASSTARTUPCORE(self)
        self.zz_fdict['RFBIASSTARTUPCORE'] = self.RFBIASSTARTUPCORE
        self.RFBIASSTARTUPSUPPLY = RM_Field_RAC_NS_RFBIASCTRL_RFBIASSTARTUPSUPPLY(self)
        self.zz_fdict['RFBIASSTARTUPSUPPLY'] = self.RFBIASSTARTUPSUPPLY
        self.RFBIASLDOVREFTRIM = RM_Field_RAC_NS_RFBIASCTRL_RFBIASLDOVREFTRIM(self)
        self.zz_fdict['RFBIASLDOVREFTRIM'] = self.RFBIASLDOVREFTRIM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RADIOEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RADIOEN, self).__init__(rmio, label,
            0xb8020000, 0x15C,
            'RADIOEN', 'RAC_NS.RADIOEN', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREEN = RM_Field_RAC_NS_RADIOEN_PREEN(self)
        self.zz_fdict['PREEN'] = self.PREEN
        self.PRESTB100UDIS = RM_Field_RAC_NS_RADIOEN_PRESTB100UDIS(self)
        self.zz_fdict['PRESTB100UDIS'] = self.PRESTB100UDIS
        self.RFBIASEN = RM_Field_RAC_NS_RADIOEN_RFBIASEN(self)
        self.zz_fdict['RFBIASEN'] = self.RFBIASEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFPATHEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFPATHEN0, self).__init__(rmio, label,
            0xb8020000, 0x160,
            'RFPATHEN0', 'RAC_NS.RFPATHEN0', 'read-write',
            u"",
            0x000000C2, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXEN0 = RM_Field_RAC_NS_RFPATHEN0_LNAMIXEN0(self)
        self.zz_fdict['LNAMIXEN0'] = self.LNAMIXEN0
        self.LNAMIXRFATTDCEN0 = RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFATTDCEN0(self)
        self.zz_fdict['LNAMIXRFATTDCEN0'] = self.LNAMIXRFATTDCEN0
        self.LNAMIXRFPKDENRF0 = RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFPKDENRF0(self)
        self.zz_fdict['LNAMIXRFPKDENRF0'] = self.LNAMIXRFPKDENRF0
        self.SYLODIVRLO0SUBGEN = RM_Field_RAC_NS_RFPATHEN0_SYLODIVRLO0SUBGEN(self)
        self.zz_fdict['SYLODIVRLO0SUBGEN'] = self.SYLODIVRLO0SUBGEN
        self.TXENHPA0 = RM_Field_RAC_NS_RFPATHEN0_TXENHPA0(self)
        self.zz_fdict['TXENHPA0'] = self.TXENHPA0
        self.TXENLPA0 = RM_Field_RAC_NS_RFPATHEN0_TXENLPA0(self)
        self.zz_fdict['TXENLPA0'] = self.TXENLPA0
        self.TXENVMIDHPA0 = RM_Field_RAC_NS_RFPATHEN0_TXENVMIDHPA0(self)
        self.zz_fdict['TXENVMIDHPA0'] = self.TXENVMIDHPA0
        self.TXENVMIDLPA0 = RM_Field_RAC_NS_RFPATHEN0_TXENVMIDLPA0(self)
        self.zz_fdict['TXENVMIDLPA0'] = self.TXENVMIDLPA0
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFPATHEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFPATHEN1, self).__init__(rmio, label,
            0xb8020000, 0x164,
            'RFPATHEN1', 'RAC_NS.RFPATHEN1', 'read-write',
            u"",
            0x000000C2, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXEN1 = RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN1(self)
        self.zz_fdict['LNAMIXEN1'] = self.LNAMIXEN1
        self.LNAMIXRFATTDCEN1 = RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFATTDCEN1(self)
        self.zz_fdict['LNAMIXRFATTDCEN1'] = self.LNAMIXRFATTDCEN1
        self.LNAMIXRFPKDENRF1 = RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFPKDENRF1(self)
        self.zz_fdict['LNAMIXRFPKDENRF1'] = self.LNAMIXRFPKDENRF1
        self.SYLODIVRLO1SUBGEN = RM_Field_RAC_NS_RFPATHEN1_SYLODIVRLO1SUBGEN(self)
        self.zz_fdict['SYLODIVRLO1SUBGEN'] = self.SYLODIVRLO1SUBGEN
        self.TXENHPA1 = RM_Field_RAC_NS_RFPATHEN1_TXENHPA1(self)
        self.zz_fdict['TXENHPA1'] = self.TXENHPA1
        self.TXENLPA1 = RM_Field_RAC_NS_RFPATHEN1_TXENLPA1(self)
        self.zz_fdict['TXENLPA1'] = self.TXENLPA1
        self.TXENVMIDHPA1 = RM_Field_RAC_NS_RFPATHEN1_TXENVMIDHPA1(self)
        self.zz_fdict['TXENVMIDHPA1'] = self.TXENVMIDHPA1
        self.TXENVMIDLPA1 = RM_Field_RAC_NS_RFPATHEN1_TXENVMIDLPA1(self)
        self.zz_fdict['TXENVMIDLPA1'] = self.TXENVMIDLPA1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RX, self).__init__(rmio, label,
            0xb8020000, 0x168,
            'RX', 'RAC_NS.RX', 'read-write',
            u"",
            0x00000000, 0x000F03FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCCAPRESET = RM_Field_RAC_NS_RX_IFADCCAPRESET(self)
        self.zz_fdict['IFADCCAPRESET'] = self.IFADCCAPRESET
        self.IFADCENLDOSERIES = RM_Field_RAC_NS_RX_IFADCENLDOSERIES(self)
        self.zz_fdict['IFADCENLDOSERIES'] = self.IFADCENLDOSERIES
        self.IFADCENLDOSHUNT = RM_Field_RAC_NS_RX_IFADCENLDOSHUNT(self)
        self.zz_fdict['IFADCENLDOSHUNT'] = self.IFADCENLDOSHUNT
        self.LNAMIXENRFPKD = RM_Field_RAC_NS_RX_LNAMIXENRFPKD(self)
        self.zz_fdict['LNAMIXENRFPKD'] = self.LNAMIXENRFPKD
        self.LNAMIXENRFPKDLOTHRESH = RM_Field_RAC_NS_RX_LNAMIXENRFPKDLOTHRESH(self)
        self.zz_fdict['LNAMIXENRFPKDLOTHRESH'] = self.LNAMIXENRFPKDLOTHRESH
        self.LNAMIXLDOLOWCUR = RM_Field_RAC_NS_RX_LNAMIXLDOLOWCUR(self)
        self.zz_fdict['LNAMIXLDOLOWCUR'] = self.LNAMIXLDOLOWCUR
        self.LNAMIXREGLOADEN = RM_Field_RAC_NS_RX_LNAMIXREGLOADEN(self)
        self.zz_fdict['LNAMIXREGLOADEN'] = self.LNAMIXREGLOADEN
        self.PGAENLDO = RM_Field_RAC_NS_RX_PGAENLDO(self)
        self.zz_fdict['PGAENLDO'] = self.PGAENLDO
        self.SYCHPQNC3EN = RM_Field_RAC_NS_RX_SYCHPQNC3EN(self)
        self.zz_fdict['SYCHPQNC3EN'] = self.SYCHPQNC3EN
        self.SYCHPBIASTRIMBUFRX = RM_Field_RAC_NS_RX_SYCHPBIASTRIMBUFRX(self)
        self.zz_fdict['SYCHPBIASTRIMBUFRX'] = self.SYCHPBIASTRIMBUFRX
        self.SYPFDCHPLPENRX = RM_Field_RAC_NS_RX_SYPFDCHPLPENRX(self)
        self.zz_fdict['SYPFDCHPLPENRX'] = self.SYPFDCHPLPENRX
        self.SYPFDFPWENRX = RM_Field_RAC_NS_RX_SYPFDFPWENRX(self)
        self.zz_fdict['SYPFDFPWENRX'] = self.SYPFDFPWENRX
        self.SYVCOVCAPFASTRAMPRX = RM_Field_RAC_NS_RX_SYVCOVCAPFASTRAMPRX(self)
        self.zz_fdict['SYVCOVCAPFASTRAMPRX'] = self.SYVCOVCAPFASTRAMPRX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX, self).__init__(rmio, label,
            0xb8020000, 0x16C,
            'TX', 'RAC_NS.TX', 'read-write',
            u"",
            0x00002000, 0xC00F3FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXENDREG = RM_Field_RAC_NS_TX_TXENDREG(self)
        self.zz_fdict['TXENDREG'] = self.TXENDREG
        self.TXENOREG = RM_Field_RAC_NS_TX_TXENOREG(self)
        self.zz_fdict['TXENOREG'] = self.TXENOREG
        self.TXENOREGBLEED = RM_Field_RAC_NS_TX_TXENOREGBLEED(self)
        self.zz_fdict['TXENOREGBLEED'] = self.TXENOREGBLEED
        self.TXENRREG = RM_Field_RAC_NS_TX_TXENRREG(self)
        self.zz_fdict['TXENRREG'] = self.TXENRREG
        self.TXENCLKGEN = RM_Field_RAC_NS_TX_TXENCLKGEN(self)
        self.zz_fdict['TXENCLKGEN'] = self.TXENCLKGEN
        self.TXENPADDCFORCE = RM_Field_RAC_NS_TX_TXENPADDCFORCE(self)
        self.zz_fdict['TXENPADDCFORCE'] = self.TXENPADDCFORCE
        self.TXENPKDOGND = RM_Field_RAC_NS_TX_TXENPKDOGND(self)
        self.zz_fdict['TXENPKDOGND'] = self.TXENPKDOGND
        self.TXENPKDOGNDCLK = RM_Field_RAC_NS_TX_TXENPKDOGNDCLK(self)
        self.zz_fdict['TXENPKDOGNDCLK'] = self.TXENPKDOGNDCLK
        self.TXENPUPDNPROTECT = RM_Field_RAC_NS_TX_TXENPUPDNPROTECT(self)
        self.zz_fdict['TXENPUPDNPROTECT'] = self.TXENPUPDNPROTECT
        self.TXENRAMPCLK = RM_Field_RAC_NS_TX_TXENRAMPCLK(self)
        self.zz_fdict['TXENRAMPCLK'] = self.TXENRAMPCLK
        self.TXENVTRCURRENT = RM_Field_RAC_NS_TX_TXENVTRCURRENT(self)
        self.zz_fdict['TXENVTRCURRENT'] = self.TXENVTRCURRENT
        self.TXENXDRVVMID = RM_Field_RAC_NS_TX_TXENXDRVVMID(self)
        self.zz_fdict['TXENXDRVVMID'] = self.TXENXDRVVMID
        self.TXMODEPMOSOFF = RM_Field_RAC_NS_TX_TXMODEPMOSOFF(self)
        self.zz_fdict['TXMODEPMOSOFF'] = self.TXMODEPMOSOFF
        self.TXMODESE = RM_Field_RAC_NS_TX_TXMODESE(self)
        self.zz_fdict['TXMODESE'] = self.TXMODESE
        self.SYCHPBIASTRIMBUFTX = RM_Field_RAC_NS_TX_SYCHPBIASTRIMBUFTX(self)
        self.zz_fdict['SYCHPBIASTRIMBUFTX'] = self.SYCHPBIASTRIMBUFTX
        self.SYPFDCHPLPENTX = RM_Field_RAC_NS_TX_SYPFDCHPLPENTX(self)
        self.zz_fdict['SYPFDCHPLPENTX'] = self.SYPFDCHPLPENTX
        self.SYPFDFPWENTX = RM_Field_RAC_NS_TX_SYPFDFPWENTX(self)
        self.zz_fdict['SYPFDFPWENTX'] = self.SYPFDFPWENTX
        self.SYVCOVCAPFASTRAMPTX = RM_Field_RAC_NS_TX_SYVCOVCAPFASTRAMPTX(self)
        self.zz_fdict['SYVCOVCAPFASTRAMPTX'] = self.SYVCOVCAPFASTRAMPTX
        self.ENPAPOWER = RM_Field_RAC_NS_TX_ENPAPOWER(self)
        self.zz_fdict['ENPAPOWER'] = self.ENPAPOWER
        self.ENPASELSLICE = RM_Field_RAC_NS_TX_ENPASELSLICE(self)
        self.zz_fdict['ENPASELSLICE'] = self.ENPASELSLICE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYDEBUG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYDEBUG, self).__init__(rmio, label,
            0xb8020000, 0x170,
            'SYDEBUG', 'RAC_NS.SYDEBUG', 'read-write',
            u"",
            0x00000020, 0x00000177,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYCHPSWITCHEDBIASEN = RM_Field_RAC_NS_SYDEBUG_SYCHPSWITCHEDBIASEN(self)
        self.zz_fdict['SYCHPSWITCHEDBIASEN'] = self.SYCHPSWITCHEDBIASEN
        self.SYENMMDDREGBIASSTB = RM_Field_RAC_NS_SYDEBUG_SYENMMDDREGBIASSTB(self)
        self.zz_fdict['SYENMMDDREGBIASSTB'] = self.SYENMMDDREGBIASSTB
        self.SYLODIVAUXLODIS = RM_Field_RAC_NS_SYDEBUG_SYLODIVAUXLODIS(self)
        self.zz_fdict['SYLODIVAUXLODIS'] = self.SYLODIVAUXLODIS
        self.SYLODIVLDOPSRTRIM = RM_Field_RAC_NS_SYDEBUG_SYLODIVLDOPSRTRIM(self)
        self.zz_fdict['SYLODIVLDOPSRTRIM'] = self.SYLODIVLDOPSRTRIM
        self.SYPFDLOCKWINDOWN = RM_Field_RAC_NS_SYDEBUG_SYPFDLOCKWINDOWN(self)
        self.zz_fdict['SYPFDLOCKWINDOWN'] = self.SYPFDLOCKWINDOWN
        self.SYPFDTRADMODEEN = RM_Field_RAC_NS_SYDEBUG_SYPFDTRADMODEEN(self)
        self.zz_fdict['SYPFDTRADMODEEN'] = self.SYPFDTRADMODEEN
        self.SYVCOREGBYPASS = RM_Field_RAC_NS_SYDEBUG_SYVCOREGBYPASS(self)
        self.zz_fdict['SYVCOREGBYPASS'] = self.SYVCOREGBYPASS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYTRIM0, self).__init__(rmio, label,
            0xb8020000, 0x174,
            'SYTRIM0', 'RAC_NS.SYTRIM0', 'read-write',
            u"",
            0x018FF169, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYCHPBIAS = RM_Field_RAC_NS_SYTRIM0_SYCHPBIAS(self)
        self.zz_fdict['SYCHPBIAS'] = self.SYCHPBIAS
        self.SYCHPCURRRX = RM_Field_RAC_NS_SYTRIM0_SYCHPCURRRX(self)
        self.zz_fdict['SYCHPCURRRX'] = self.SYCHPCURRRX
        self.SYCHPCURRTX = RM_Field_RAC_NS_SYTRIM0_SYCHPCURRTX(self)
        self.zz_fdict['SYCHPCURRTX'] = self.SYCHPCURRTX
        self.SYCHPLEVNSRC = RM_Field_RAC_NS_SYTRIM0_SYCHPLEVNSRC(self)
        self.zz_fdict['SYCHPLEVNSRC'] = self.SYCHPLEVNSRC
        self.SYCHPLEVPSRCRX = RM_Field_RAC_NS_SYTRIM0_SYCHPLEVPSRCRX(self)
        self.zz_fdict['SYCHPLEVPSRCRX'] = self.SYCHPLEVPSRCRX
        self.SYCHPLEVPSRCTX = RM_Field_RAC_NS_SYTRIM0_SYCHPLEVPSRCTX(self)
        self.zz_fdict['SYCHPLEVPSRCTX'] = self.SYCHPLEVPSRCTX
        self.SYCHPSRCENRX = RM_Field_RAC_NS_SYTRIM0_SYCHPSRCENRX(self)
        self.zz_fdict['SYCHPSRCENRX'] = self.SYCHPSRCENRX
        self.SYCHPSRCENTX = RM_Field_RAC_NS_SYTRIM0_SYCHPSRCENTX(self)
        self.zz_fdict['SYCHPSRCENTX'] = self.SYCHPSRCENTX
        self.SYCHPREPLICACURRADJ = RM_Field_RAC_NS_SYTRIM0_SYCHPREPLICACURRADJ(self)
        self.zz_fdict['SYCHPREPLICACURRADJ'] = self.SYCHPREPLICACURRADJ
        self.SYTRIMCHPREGAMPBIAS = RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBIAS(self)
        self.zz_fdict['SYTRIMCHPREGAMPBIAS'] = self.SYTRIMCHPREGAMPBIAS
        self.SYTRIMCHPREGAMPBW = RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBW(self)
        self.zz_fdict['SYTRIMCHPREGAMPBW'] = self.SYTRIMCHPREGAMPBW
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYTRIM1, self).__init__(rmio, label,
            0xb8020000, 0x178,
            'SYTRIM1', 'RAC_NS.SYTRIM1', 'read-write',
            u"",
            0x1FE00440, 0xFFFC4FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYLODIVLDOTRIMCORERX = RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMCORERX(self)
        self.zz_fdict['SYLODIVLDOTRIMCORERX'] = self.SYLODIVLDOTRIMCORERX
        self.SYLODIVLDOTRIMCORETX = RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMCORETX(self)
        self.zz_fdict['SYLODIVLDOTRIMCORETX'] = self.SYLODIVLDOTRIMCORETX
        self.SYLODIVLDOTRIMNDIORX = RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMNDIORX(self)
        self.zz_fdict['SYLODIVLDOTRIMNDIORX'] = self.SYLODIVLDOTRIMNDIORX
        self.SYLODIVLDOTRIMNDIOTX = RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMNDIOTX(self)
        self.zz_fdict['SYLODIVLDOTRIMNDIOTX'] = self.SYLODIVLDOTRIMNDIOTX
        self.SYLODIVSELOUTINVADC = RM_Field_RAC_NS_SYTRIM1_SYLODIVSELOUTINVADC(self)
        self.zz_fdict['SYLODIVSELOUTINVADC'] = self.SYLODIVSELOUTINVADC
        self.SYLODIVTLOTRIMDELAY = RM_Field_RAC_NS_SYTRIM1_SYLODIVTLOTRIMDELAY(self)
        self.zz_fdict['SYLODIVTLOTRIMDELAY'] = self.SYLODIVTLOTRIMDELAY
        self.SYMMDREPLICA1CURRADJ = RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA1CURRADJ(self)
        self.zz_fdict['SYMMDREPLICA1CURRADJ'] = self.SYMMDREPLICA1CURRADJ
        self.SYMMDREPLICA2CURRADJ = RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA2CURRADJ(self)
        self.zz_fdict['SYMMDREPLICA2CURRADJ'] = self.SYMMDREPLICA2CURRADJ
        self.SYTRIMMMDREGAMPBIAS = RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBIAS(self)
        self.zz_fdict['SYTRIMMMDREGAMPBIAS'] = self.SYTRIMMMDREGAMPBIAS
        self.SYTRIMMMDREGAMPBW = RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBW(self)
        self.zz_fdict['SYTRIMMMDREGAMPBW'] = self.SYTRIMMMDREGAMPBW
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYCAL, self).__init__(rmio, label,
            0xb8020000, 0x17C,
            'SYCAL', 'RAC_NS.SYCAL', 'read-write',
            u"",
            0x01008100, 0x03018700,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYVCOMODEPKD = RM_Field_RAC_NS_SYCAL_SYVCOMODEPKD(self)
        self.zz_fdict['SYVCOMODEPKD'] = self.SYVCOMODEPKD
        self.SYVCOMORECURRENT = RM_Field_RAC_NS_SYCAL_SYVCOMORECURRENT(self)
        self.zz_fdict['SYVCOMORECURRENT'] = self.SYVCOMORECURRENT
        self.SYVCOSLOWNOISEFILTER = RM_Field_RAC_NS_SYCAL_SYVCOSLOWNOISEFILTER(self)
        self.zz_fdict['SYVCOSLOWNOISEFILTER'] = self.SYVCOSLOWNOISEFILTER
        self.SYVCOVCAPVCM = RM_Field_RAC_NS_SYCAL_SYVCOVCAPVCM(self)
        self.zz_fdict['SYVCOVCAPVCM'] = self.SYVCOVCAPVCM
        self.SYHILOADCHPREG = RM_Field_RAC_NS_SYCAL_SYHILOADCHPREG(self)
        self.zz_fdict['SYHILOADCHPREG'] = self.SYHILOADCHPREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYEN, self).__init__(rmio, label,
            0xb8020000, 0x180,
            'SYEN', 'RAC_NS.SYEN', 'read-write',
            u"",
            0x00000000, 0x000067FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYCHPEN = RM_Field_RAC_NS_SYEN_SYCHPEN(self)
        self.zz_fdict['SYCHPEN'] = self.SYCHPEN
        self.SYCHPLPENRX = RM_Field_RAC_NS_SYEN_SYCHPLPENRX(self)
        self.zz_fdict['SYCHPLPENRX'] = self.SYCHPLPENRX
        self.SYCHPLPENTX = RM_Field_RAC_NS_SYEN_SYCHPLPENTX(self)
        self.zz_fdict['SYCHPLPENTX'] = self.SYCHPLPENTX
        self.SYENCHPREG = RM_Field_RAC_NS_SYEN_SYENCHPREG(self)
        self.zz_fdict['SYENCHPREG'] = self.SYENCHPREG
        self.SYENCHPREPLICA = RM_Field_RAC_NS_SYEN_SYENCHPREPLICA(self)
        self.zz_fdict['SYENCHPREPLICA'] = self.SYENCHPREPLICA
        self.SYENMMDREG = RM_Field_RAC_NS_SYEN_SYENMMDREG(self)
        self.zz_fdict['SYENMMDREG'] = self.SYENMMDREG
        self.SYENMMDREPLICA1 = RM_Field_RAC_NS_SYEN_SYENMMDREPLICA1(self)
        self.zz_fdict['SYENMMDREPLICA1'] = self.SYENMMDREPLICA1
        self.SYENMMDREPLICA2 = RM_Field_RAC_NS_SYEN_SYENMMDREPLICA2(self)
        self.zz_fdict['SYENMMDREPLICA2'] = self.SYENMMDREPLICA2
        self.SYENVCOBIAS = RM_Field_RAC_NS_SYEN_SYENVCOBIAS(self)
        self.zz_fdict['SYENVCOBIAS'] = self.SYENVCOBIAS
        self.SYENVCOPFET = RM_Field_RAC_NS_SYEN_SYENVCOPFET(self)
        self.zz_fdict['SYENVCOPFET'] = self.SYENVCOPFET
        self.SYENVCOREG = RM_Field_RAC_NS_SYEN_SYENVCOREG(self)
        self.zz_fdict['SYENVCOREG'] = self.SYENVCOREG
        self.SYSTARTCHPREG = RM_Field_RAC_NS_SYEN_SYSTARTCHPREG(self)
        self.zz_fdict['SYSTARTCHPREG'] = self.SYSTARTCHPREG
        self.SYSTARTMMDREG = RM_Field_RAC_NS_SYEN_SYSTARTMMDREG(self)
        self.zz_fdict['SYSTARTMMDREG'] = self.SYSTARTMMDREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYLOEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYLOEN, self).__init__(rmio, label,
            0xb8020000, 0x184,
            'SYLOEN', 'RAC_NS.SYLOEN', 'read-write',
            u"",
            0x00000000, 0x0000039E,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYLODIVEN = RM_Field_RAC_NS_SYLOEN_SYLODIVEN(self)
        self.zz_fdict['SYLODIVEN'] = self.SYLODIVEN
        self.SYLODIVLDOBIASEN = RM_Field_RAC_NS_SYLOEN_SYLODIVLDOBIASEN(self)
        self.zz_fdict['SYLODIVLDOBIASEN'] = self.SYLODIVLDOBIASEN
        self.SYLODIVLDOEN = RM_Field_RAC_NS_SYLOEN_SYLODIVLDOEN(self)
        self.zz_fdict['SYLODIVLDOEN'] = self.SYLODIVLDOEN
        self.SYLODIVRLOSUBGRADCCLKEN = RM_Field_RAC_NS_SYLOEN_SYLODIVRLOSUBGRADCCLKEN(self)
        self.zz_fdict['SYLODIVRLOSUBGRADCCLKEN'] = self.SYLODIVRLOSUBGRADCCLKEN
        self.SYLODIVSMUXDIVEN = RM_Field_RAC_NS_SYLOEN_SYLODIVSMUXDIVEN(self)
        self.zz_fdict['SYLODIVSMUXDIVEN'] = self.SYLODIVSMUXDIVEN
        self.SYLODIVTLOSUBGAUXEN = RM_Field_RAC_NS_SYLOEN_SYLODIVTLOSUBGAUXEN(self)
        self.zz_fdict['SYLODIVTLOSUBGAUXEN'] = self.SYLODIVTLOSUBGAUXEN
        self.SYLODIVTLOSUBGEN = RM_Field_RAC_NS_SYLOEN_SYLODIVTLOSUBGEN(self)
        self.zz_fdict['SYLODIVTLOSUBGEN'] = self.SYLODIVTLOSUBGEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYMMDCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYMMDCTRL, self).__init__(rmio, label,
            0xb8020000, 0x188,
            'SYMMDCTRL', 'RAC_NS.SYMMDCTRL', 'read-write',
            u"",
            0x00000048, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYMMDDIVRSDIG = RM_Field_RAC_NS_SYMMDCTRL_SYMMDDIVRSDIG(self)
        self.zz_fdict['SYMMDDIVRSDIG'] = self.SYMMDDIVRSDIG
        self.SYMMDMODERX = RM_Field_RAC_NS_SYMMDCTRL_SYMMDMODERX(self)
        self.zz_fdict['SYMMDMODERX'] = self.SYMMDMODERX
        self.SYMMDMODETX = RM_Field_RAC_NS_SYMMDCTRL_SYMMDMODETX(self)
        self.zz_fdict['SYMMDMODETX'] = self.SYMMDMODETX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYDIVCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYDIVCTRL, self).__init__(rmio, label,
            0xb8020000, 0x18C,
            'SYDIVCTRL', 'RAC_NS.SYDIVCTRL', 'read-write',
            u"",
            0x00000000, 0x00033C00,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYLODIVRADCDIV = RM_Field_RAC_NS_SYDIVCTRL_SYLODIVRADCDIV(self)
        self.zz_fdict['SYLODIVRADCDIV'] = self.SYLODIVRADCDIV
        self.SYLODIVSMUXDIV = RM_Field_RAC_NS_SYDIVCTRL_SYLODIVSMUXDIV(self)
        self.zz_fdict['SYLODIVSMUXDIV'] = self.SYLODIVSMUXDIV
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_DIGCLKRETIMECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_DIGCLKRETIMECTRL, self).__init__(rmio, label,
            0xb8020000, 0x190,
            'DIGCLKRETIMECTRL', 'RAC_NS.DIGCLKRETIMECTRL', 'read-write',
            u"",
            0x00000000, 0x00000777,
            0x00001000, 0x00002000,
            0x00003000)

        self.DIGCLKRETIMEENRETIME = RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME(self)
        self.zz_fdict['DIGCLKRETIMEENRETIME'] = self.DIGCLKRETIMEENRETIME
        self.DIGCLKRETIMEDISRETIME = RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME(self)
        self.zz_fdict['DIGCLKRETIMEDISRETIME'] = self.DIGCLKRETIMEDISRETIME
        self.DIGCLKRETIMERESETN = RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN(self)
        self.zz_fdict['DIGCLKRETIMERESETN'] = self.DIGCLKRETIMERESETN
        self.DIGCLKRETIMELIMITH = RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH(self)
        self.zz_fdict['DIGCLKRETIMELIMITH'] = self.DIGCLKRETIMELIMITH
        self.DIGCLKRETIMELIMITL = RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL(self)
        self.zz_fdict['DIGCLKRETIMELIMITL'] = self.DIGCLKRETIMELIMITL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_DIGCLKRETIMESTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_DIGCLKRETIMESTATUS, self).__init__(rmio, label,
            0xb8020000, 0x194,
            'DIGCLKRETIMESTATUS', 'RAC_NS.DIGCLKRETIMESTATUS', 'read-only',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.DIGCLKRETIMECLKSEL = RM_Field_RAC_NS_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL(self)
        self.zz_fdict['DIGCLKRETIMECLKSEL'] = self.DIGCLKRETIMECLKSEL
        self.DIGCLKRETIMERESETNLO = RM_Field_RAC_NS_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO(self)
        self.zz_fdict['DIGCLKRETIMERESETNLO'] = self.DIGCLKRETIMERESETNLO
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_XORETIMECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_XORETIMECTRL, self).__init__(rmio, label,
            0xb8020000, 0x198,
            'XORETIMECTRL', 'RAC_NS.XORETIMECTRL', 'read-write',
            u"",
            0x00000000, 0x00000777,
            0x00001000, 0x00002000,
            0x00003000)

        self.XORETIMEENRETIME = RM_Field_RAC_NS_XORETIMECTRL_XORETIMEENRETIME(self)
        self.zz_fdict['XORETIMEENRETIME'] = self.XORETIMEENRETIME
        self.XORETIMEDISRETIME = RM_Field_RAC_NS_XORETIMECTRL_XORETIMEDISRETIME(self)
        self.zz_fdict['XORETIMEDISRETIME'] = self.XORETIMEDISRETIME
        self.XORETIMERESETN = RM_Field_RAC_NS_XORETIMECTRL_XORETIMERESETN(self)
        self.zz_fdict['XORETIMERESETN'] = self.XORETIMERESETN
        self.XORETIMELIMITH = RM_Field_RAC_NS_XORETIMECTRL_XORETIMELIMITH(self)
        self.zz_fdict['XORETIMELIMITH'] = self.XORETIMELIMITH
        self.XORETIMELIMITL = RM_Field_RAC_NS_XORETIMECTRL_XORETIMELIMITL(self)
        self.zz_fdict['XORETIMELIMITL'] = self.XORETIMELIMITL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_XORETIMESTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_XORETIMESTATUS, self).__init__(rmio, label,
            0xb8020000, 0x19C,
            'XORETIMESTATUS', 'RAC_NS.XORETIMESTATUS', 'read-only',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.XORETIMECLKSEL = RM_Field_RAC_NS_XORETIMESTATUS_XORETIMECLKSEL(self)
        self.zz_fdict['XORETIMECLKSEL'] = self.XORETIMECLKSEL
        self.XORETIMERESETNLO = RM_Field_RAC_NS_XORETIMESTATUS_XORETIMERESETNLO(self)
        self.zz_fdict['XORETIMERESETNLO'] = self.XORETIMERESETNLO
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AGCOVERWRITE0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AGCOVERWRITE0, self).__init__(rmio, label,
            0xb8020000, 0x1A0,
            'AGCOVERWRITE0', 'RAC_NS.AGCOVERWRITE0', 'read-write',
            u"",
            0x00000000, 0x03F0FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENMANLNAMIXRFATT = RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXRFATT(self)
        self.zz_fdict['ENMANLNAMIXRFATT'] = self.ENMANLNAMIXRFATT
        self.ENMANLNAMIXSLICE = RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXSLICE(self)
        self.zz_fdict['ENMANLNAMIXSLICE'] = self.ENMANLNAMIXSLICE
        self.ENMANPGAGAIN = RM_Field_RAC_NS_AGCOVERWRITE0_ENMANPGAGAIN(self)
        self.zz_fdict['ENMANPGAGAIN'] = self.ENMANPGAGAIN
        self.ENMANIFADCSCALE = RM_Field_RAC_NS_AGCOVERWRITE0_ENMANIFADCSCALE(self)
        self.zz_fdict['ENMANIFADCSCALE'] = self.ENMANIFADCSCALE
        self.MANLNAMIXSLICE0 = RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXSLICE0(self)
        self.zz_fdict['MANLNAMIXSLICE0'] = self.MANLNAMIXSLICE0
        self.MANLNAMIXSLICE1 = RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXSLICE1(self)
        self.zz_fdict['MANLNAMIXSLICE1'] = self.MANLNAMIXSLICE1
        self.MANPGAGAIN = RM_Field_RAC_NS_AGCOVERWRITE0_MANPGAGAIN(self)
        self.zz_fdict['MANPGAGAIN'] = self.MANPGAGAIN
        self.MANIFADCSCALE = RM_Field_RAC_NS_AGCOVERWRITE0_MANIFADCSCALE(self)
        self.zz_fdict['MANIFADCSCALE'] = self.MANIFADCSCALE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AGCOVERWRITE1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AGCOVERWRITE1, self).__init__(rmio, label,
            0xb8020000, 0x1A4,
            'AGCOVERWRITE1', 'RAC_NS.AGCOVERWRITE1', 'read-write',
            u"",
            0x00000000, 0x3FFF3FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MANLNAMIXRFATT0 = RM_Field_RAC_NS_AGCOVERWRITE1_MANLNAMIXRFATT0(self)
        self.zz_fdict['MANLNAMIXRFATT0'] = self.MANLNAMIXRFATT0
        self.MANLNAMIXRFATT1 = RM_Field_RAC_NS_AGCOVERWRITE1_MANLNAMIXRFATT1(self)
        self.zz_fdict['MANLNAMIXRFATT1'] = self.MANLNAMIXRFATT1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCPLLCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCPLLCTRL, self).__init__(rmio, label,
            0xb8020000, 0x1A8,
            'IFADCPLLCTRL', 'RAC_NS.IFADCPLLCTRL', 'read-write',
            u"",
            0x00000000, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCPLLINNIBBLE = RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLINNIBBLE(self)
        self.zz_fdict['IFADCPLLINNIBBLE'] = self.IFADCPLLINNIBBLE
        self.IFADCPLLLDCNIB = RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDCNIB(self)
        self.zz_fdict['IFADCPLLLDCNIB'] = self.IFADCPLLLDCNIB
        self.IFADCPLLLDFNIB = RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDFNIB(self)
        self.zz_fdict['IFADCPLLLDFNIB'] = self.IFADCPLLLDFNIB
        self.IFADCPLLLDMNIB = RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDMNIB(self)
        self.zz_fdict['IFADCPLLLDMNIB'] = self.IFADCPLLLDMNIB
        self.IFADCPLLRDNIBBLE = RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLRDNIBBLE(self)
        self.zz_fdict['IFADCPLLRDNIBBLE'] = self.IFADCPLLRDNIBBLE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCPLLDCO(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCPLLDCO, self).__init__(rmio, label,
            0xb8020000, 0x1AC,
            'IFADCPLLDCO', 'RAC_NS.IFADCPLLDCO', 'read-write',
            u"",
            0x00010104, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCPLLDCOBBCAL = RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOBBCAL(self)
        self.zz_fdict['IFADCPLLDCOBBCAL'] = self.IFADCPLLDCOBBCAL
        self.IFADCPLLDCOTEMPADJ = RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOTEMPADJ(self)
        self.zz_fdict['IFADCPLLDCOTEMPADJ'] = self.IFADCPLLDCOTEMPADJ
        self.IFADCPLLDCOBIASHALF = RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOBIASHALF(self)
        self.zz_fdict['IFADCPLLDCOBIASHALF'] = self.IFADCPLLDCOBIASHALF
        self.IFADCPLLDCOENABLE = RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOENABLE(self)
        self.zz_fdict['IFADCPLLDCOENABLE'] = self.IFADCPLLDCOENABLE
        self.IFADCPLLDCOFILTER = RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOFILTER(self)
        self.zz_fdict['IFADCPLLDCOFILTER'] = self.IFADCPLLDCOFILTER
        self.IFADCPLLDCOFULLRATE = RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOFULLRATE(self)
        self.zz_fdict['IFADCPLLDCOFULLRATE'] = self.IFADCPLLDCOFULLRATE
        self.IFADCPLLDCOMSBCURRENT = RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOMSBCURRENT(self)
        self.zz_fdict['IFADCPLLDCOMSBCURRENT'] = self.IFADCPLLDCOMSBCURRENT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCPLLEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCPLLEN, self).__init__(rmio, label,
            0xb8020000, 0x1B0,
            'IFADCPLLEN', 'RAC_NS.IFADCPLLEN', 'read-write',
            u"",
            0x00000000, 0x000003FD,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCPLLENBBDET = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBDET(self)
        self.zz_fdict['IFADCPLLENBBDET'] = self.IFADCPLLENBBDET
        self.IFADCPLLENBBXLDET = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBXLDET(self)
        self.zz_fdict['IFADCPLLENBBXLDET'] = self.IFADCPLLENBBXLDET
        self.IFADCPLLENBBXMDET = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBXMDET(self)
        self.zz_fdict['IFADCPLLENBBXMDET'] = self.IFADCPLLENBBXMDET
        self.IFADCPLLENCFDET = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENCFDET(self)
        self.zz_fdict['IFADCPLLENCFDET'] = self.IFADCPLLENCFDET
        self.IFADCPLLENROTDET = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENROTDET(self)
        self.zz_fdict['IFADCPLLENROTDET'] = self.IFADCPLLENROTDET
        self.IFADCPLLSERIEREGENABLE = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLSERIEREGENABLE(self)
        self.zz_fdict['IFADCPLLSERIEREGENABLE'] = self.IFADCPLLSERIEREGENABLE
        self.IFADCPLLSHUNTREGENABLE = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLSHUNTREGENABLE(self)
        self.zz_fdict['IFADCPLLSHUNTREGENABLE'] = self.IFADCPLLSHUNTREGENABLE
        self.IFADCPLLENREFBUF = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENREFBUF(self)
        self.zz_fdict['IFADCPLLENREFBUF'] = self.IFADCPLLENREFBUF
        self.IFADCPLLENXOBYP = RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENXOBYP(self)
        self.zz_fdict['IFADCPLLENXOBYP'] = self.IFADCPLLENXOBYP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCPLLREG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCPLLREG, self).__init__(rmio, label,
            0xb8020000, 0x1B4,
            'IFADCPLLREG', 'RAC_NS.IFADCPLLREG', 'read-write',
            u"",
            0x00000136, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCPLLSERIEREGFILTER = RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSERIEREGFILTER(self)
        self.zz_fdict['IFADCPLLSERIEREGFILTER'] = self.IFADCPLLSERIEREGFILTER
        self.IFADCPLLSERIEREGVCTRL = RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSERIEREGVCTRL(self)
        self.zz_fdict['IFADCPLLSERIEREGVCTRL'] = self.IFADCPLLSERIEREGVCTRL
        self.IFADCPLLSHUNTREGICTRL = RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSHUNTREGICTRL(self)
        self.zz_fdict['IFADCPLLSHUNTREGICTRL'] = self.IFADCPLLSHUNTREGICTRL
        self.IFADCPLLSHUNTREGVCTRL = RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSHUNTREGVCTRL(self)
        self.zz_fdict['IFADCPLLSHUNTREGVCTRL'] = self.IFADCPLLSHUNTREGVCTRL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCPLLOUTSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCPLLOUTSTATUS, self).__init__(rmio, label,
            0xb8020000, 0x1B8,
            'IFADCPLLOUTSTATUS', 'RAC_NS.IFADCPLLOUTSTATUS', 'read-only',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCPLLOUTNIBBLE = RM_Field_RAC_NS_IFADCPLLOUTSTATUS_IFADCPLLOUTNIBBLE(self)
        self.zz_fdict['IFADCPLLOUTNIBBLE'] = self.IFADCPLLOUTNIBBLE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXOGNDPKD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXOGNDPKD, self).__init__(rmio, label,
            0xb8020000, 0x1BC,
            'TXOGNDPKD', 'RAC_NS.TXOGNDPKD', 'read-write',
            u"",
            0x00000000, 0x0000007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXPKDOGNDTHRESH = RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDTHRESH(self)
        self.zz_fdict['TXPKDOGNDTHRESH'] = self.TXPKDOGNDTHRESH
        self.TXPKDOGNDBYPASSLATCH = RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDBYPASSLATCH(self)
        self.zz_fdict['TXPKDOGNDBYPASSLATCH'] = self.TXPKDOGNDBYPASSLATCH
        self.TXPKDOGNDTYPE = RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDTYPE(self)
        self.zz_fdict['TXPKDOGNDTYPE'] = self.TXPKDOGNDTYPE
        self.TXPKDOGNDRESET = RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDRESET(self)
        self.zz_fdict['TXPKDOGNDRESET'] = self.TXPKDOGNDRESET
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXOGNDPKDSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXOGNDPKDSTATUS, self).__init__(rmio, label,
            0xb8020000, 0x1C0,
            'TXOGNDPKDSTATUS', 'RAC_NS.TXOGNDPKDSTATUS', 'read-only',
            u"",
            0x00000001, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXOGNDPKDN = RM_Field_RAC_NS_TXOGNDPKDSTATUS_TXOGNDPKDN(self)
        self.zz_fdict['TXOGNDPKDN'] = self.TXOGNDPKDN
        self.TXOGNDPKDP = RM_Field_RAC_NS_TXOGNDPKDSTATUS_TXOGNDPKDP(self)
        self.zz_fdict['TXOGNDPKDP'] = self.TXOGNDPKDP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SPARE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SPARE, self).__init__(rmio, label,
            0xb8020000, 0x1C4,
            'SPARE', 'RAC_NS.SPARE', 'read-write',
            u"",
            0x00000000, 0xFC007FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCSPARE = RM_Field_RAC_NS_SPARE_AUXADCSPARE(self)
        self.zz_fdict['AUXADCSPARE'] = self.AUXADCSPARE
        self.CLKMULTSPARE = RM_Field_RAC_NS_SPARE_CLKMULTSPARE(self)
        self.zz_fdict['CLKMULTSPARE'] = self.CLKMULTSPARE
        self.IFADCPLLSPARE = RM_Field_RAC_NS_SPARE_IFADCPLLSPARE(self)
        self.zz_fdict['IFADCPLLSPARE'] = self.IFADCPLLSPARE
        self.SYSPARE = RM_Field_RAC_NS_SPARE_SYSPARE(self)
        self.zz_fdict['SYSPARE'] = self.SYSPARE
        self.TXSPARE = RM_Field_RAC_NS_SPARE_TXSPARE(self)
        self.zz_fdict['TXSPARE'] = self.TXSPARE
        self.IFADCCTRLRESERVED = RM_Field_RAC_NS_SPARE_IFADCCTRLRESERVED(self)
        self.zz_fdict['IFADCCTRLRESERVED'] = self.IFADCCTRLRESERVED
        self.IFADCCTRLRESERVEDLV = RM_Field_RAC_NS_SPARE_IFADCCTRLRESERVEDLV(self)
        self.zz_fdict['IFADCCTRLRESERVEDLV'] = self.IFADCCTRLRESERVEDLV
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SCRATCH0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SCRATCH0, self).__init__(rmio, label,
            0xb8020000, 0x3E0,
            'SCRATCH0', 'RAC_NS.SCRATCH0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH0 = RM_Field_RAC_NS_SCRATCH0_SCRATCH0(self)
        self.zz_fdict['SCRATCH0'] = self.SCRATCH0
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SCRATCH1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SCRATCH1, self).__init__(rmio, label,
            0xb8020000, 0x3E4,
            'SCRATCH1', 'RAC_NS.SCRATCH1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH1 = RM_Field_RAC_NS_SCRATCH1_SCRATCH1(self)
        self.zz_fdict['SCRATCH1'] = self.SCRATCH1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SCRATCH2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SCRATCH2, self).__init__(rmio, label,
            0xb8020000, 0x3E8,
            'SCRATCH2', 'RAC_NS.SCRATCH2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH2 = RM_Field_RAC_NS_SCRATCH2_SCRATCH2(self)
        self.zz_fdict['SCRATCH2'] = self.SCRATCH2
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SCRATCH3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SCRATCH3, self).__init__(rmio, label,
            0xb8020000, 0x3EC,
            'SCRATCH3', 'RAC_NS.SCRATCH3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH3 = RM_Field_RAC_NS_SCRATCH3_SCRATCH3(self)
        self.zz_fdict['SCRATCH3'] = self.SCRATCH3
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SCRATCH4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SCRATCH4, self).__init__(rmio, label,
            0xb8020000, 0x3F0,
            'SCRATCH4', 'RAC_NS.SCRATCH4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH4 = RM_Field_RAC_NS_SCRATCH4_SCRATCH4(self)
        self.zz_fdict['SCRATCH4'] = self.SCRATCH4
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SCRATCH5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SCRATCH5, self).__init__(rmio, label,
            0xb8020000, 0x3F4,
            'SCRATCH5', 'RAC_NS.SCRATCH5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH5 = RM_Field_RAC_NS_SCRATCH5_SCRATCH5(self)
        self.zz_fdict['SCRATCH5'] = self.SCRATCH5
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SCRATCH6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SCRATCH6, self).__init__(rmio, label,
            0xb8020000, 0x3F8,
            'SCRATCH6', 'RAC_NS.SCRATCH6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH6 = RM_Field_RAC_NS_SCRATCH6_SCRATCH6(self)
        self.zz_fdict['SCRATCH6'] = self.SCRATCH6
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SCRATCH7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SCRATCH7, self).__init__(rmio, label,
            0xb8020000, 0x3FC,
            'SCRATCH7', 'RAC_NS.SCRATCH7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH7 = RM_Field_RAC_NS_SCRATCH7_SCRATCH7(self)
        self.zz_fdict['SCRATCH7'] = self.SCRATCH7
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_THMSW(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_THMSW, self).__init__(rmio, label,
            0xb8020000, 0x7E8,
            'THMSW', 'RAC_NS.THMSW', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_RAC_NS_THMSW_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.HALFSWITCH = RM_Field_RAC_NS_THMSW_HALFSWITCH(self)
        self.zz_fdict['HALFSWITCH'] = self.HALFSWITCH
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_DIAGAALTEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_DIAGAALTEN, self).__init__(rmio, label,
            0xb8020000, 0x7EC,
            'DIAGAALTEN', 'RAC_NS.DIAGAALTEN', 'read-write',
            u"",
            0x00000000, 0x00000002,
            0x00001000, 0x00002000,
            0x00003000)

        self.RFEN = RM_Field_RAC_NS_DIAGAALTEN_RFEN(self)
        self.zz_fdict['RFEN'] = self.RFEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_DIAGAALTSEL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_DIAGAALTSEL, self).__init__(rmio, label,
            0xb8020000, 0x7F0,
            'DIAGAALTSEL', 'RAC_NS.DIAGAALTSEL', 'read-write',
            u"",
            0x00000000, 0x00007F3F,
            0x00001000, 0x00002000,
            0x00003000)

        self.TP = RM_Field_RAC_NS_DIAGAALTSEL_TP(self)
        self.zz_fdict['TP'] = self.TP
        self.BLK = RM_Field_RAC_NS_DIAGAALTSEL_BLK(self)
        self.zz_fdict['BLK'] = self.BLK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_DIAGAALTBRIDGECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_DIAGAALTBRIDGECTRL, self).__init__(rmio, label,
            0xb8020000, 0x7F4,
            'DIAGAALTBRIDGECTRL', 'RAC_NS.DIAGAALTBRIDGECTRL', 'read-write',
            u"",
            0x00000000, 0x00000020,
            0x00001000, 0x00002000,
            0x00003000)

        self.RFSHORTDIS = RM_Field_RAC_NS_DIAGAALTBRIDGECTRL_RFSHORTDIS(self)
        self.zz_fdict['RFSHORTDIS'] = self.RFSHORTDIS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFLOCK0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFLOCK0, self).__init__(rmio, label,
            0xb8020000, 0x7F8,
            'RFLOCK0', 'RAC_NS.RFLOCK0', 'read-write',
            u"",
            0x80000000, 0xFFC703FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNTHLODIVFREQCTRL = RM_Field_RAC_NS_RFLOCK0_SYNTHLODIVFREQCTRL(self)
        self.zz_fdict['SYNTHLODIVFREQCTRL'] = self.SYNTHLODIVFREQCTRL
        self.RACIFPGAEN = RM_Field_RAC_NS_RFLOCK0_RACIFPGAEN(self)
        self.zz_fdict['RACIFPGAEN'] = self.RACIFPGAEN
        self.RACTXENLPA = RM_Field_RAC_NS_RFLOCK0_RACTXENLPA(self)
        self.zz_fdict['RACTXENLPA'] = self.RACTXENLPA
        self.RACTXENHPA = RM_Field_RAC_NS_RFLOCK0_RACTXENHPA(self)
        self.zz_fdict['RACTXENHPA'] = self.RACTXENHPA
        self.FRCCONVMODE = RM_Field_RAC_NS_RFLOCK0_FRCCONVMODE(self)
        self.zz_fdict['FRCCONVMODE'] = self.FRCCONVMODE
        self.FRCPAUSING = RM_Field_RAC_NS_RFLOCK0_FRCPAUSING(self)
        self.zz_fdict['FRCPAUSING'] = self.FRCPAUSING
        self.MODEMANTSWENABLE = RM_Field_RAC_NS_RFLOCK0_MODEMANTSWENABLE(self)
        self.zz_fdict['MODEMANTSWENABLE'] = self.MODEMANTSWENABLE
        self.MODEMLRBLE = RM_Field_RAC_NS_RFLOCK0_MODEMLRBLE(self)
        self.zz_fdict['MODEMLRBLE'] = self.MODEMLRBLE
        self.MODEMDSSS = RM_Field_RAC_NS_RFLOCK0_MODEMDSSS(self)
        self.zz_fdict['MODEMDSSS'] = self.MODEMDSSS
        self.MODEMDEC1 = RM_Field_RAC_NS_RFLOCK0_MODEMDEC1(self)
        self.zz_fdict['MODEMDEC1'] = self.MODEMDEC1
        self.MODEMMODFORMAT = RM_Field_RAC_NS_RFLOCK0_MODEMMODFORMAT(self)
        self.zz_fdict['MODEMMODFORMAT'] = self.MODEMMODFORMAT
        self.MODEMDUALSYNC = RM_Field_RAC_NS_RFLOCK0_MODEMDUALSYNC(self)
        self.zz_fdict['MODEMDUALSYNC'] = self.MODEMDUALSYNC
        self.MODEMANTDIVMODE = RM_Field_RAC_NS_RFLOCK0_MODEMANTDIVMODE(self)
        self.zz_fdict['MODEMANTDIVMODE'] = self.MODEMANTDIVMODE
        self.UNLOCKED = RM_Field_RAC_NS_RFLOCK0_UNLOCKED(self)
        self.zz_fdict['UNLOCKED'] = self.UNLOCKED
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFLOCK1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFLOCK1, self).__init__(rmio, label,
            0xb8020000, 0x7FC,
            'RFLOCK1', 'RAC_NS.RFLOCK1', 'read-write',
            u"",
            0x000000FF, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RACPASTRIPE = RM_Field_RAC_NS_RFLOCK1_RACPASTRIPE(self)
        self.zz_fdict['RACPASTRIPE'] = self.RACPASTRIPE
        self.RACPASLICE = RM_Field_RAC_NS_RFLOCK1_RACPASLICE(self)
        self.zz_fdict['RACPASLICE'] = self.RACPASLICE
        self.__dict__['zz_frozen'] = True



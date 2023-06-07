
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
            0x00000005, 0xFFFFFFFF,
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
            0x00000000, 0xBFFF000F,
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
        self.RFTXPKD = RM_Field_RAC_NS_SEQIF_RFTXPKD(self)
        self.zz_fdict['RFTXPKD'] = self.RFTXPKD
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SEQIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SEQIEN, self).__init__(rmio, label,
            0xb8020000, 0x02C,
            'SEQIEN', 'RAC_NS.SEQIEN', 'read-write',
            u"",
            0x00000000, 0xBFFF000F,
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
        self.RFTXPKD = RM_Field_RAC_NS_SEQIEN_RFTXPKD(self)
        self.zz_fdict['RFTXPKD'] = self.RFTXPKD
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


class RM_Register_RAC_NS_FEMCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_FEMCTRL, self).__init__(rmio, label,
            0xb8020000, 0x034,
            'FEMCTRL', 'RAC_NS.FEMCTRL', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.FEMEN = RM_Field_RAC_NS_FEMCTRL_FEMEN(self)
        self.zz_fdict['FEMEN'] = self.FEMEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_FEMDATA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_FEMDATA, self).__init__(rmio, label,
            0xb8020000, 0x038,
            'FEMDATA', 'RAC_NS.FEMDATA', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.FEMDATA = RM_Field_RAC_NS_FEMDATA_FEMDATA(self)
        self.zz_fdict['FEMDATA'] = self.FEMDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_STIMER(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_STIMER, self).__init__(rmio, label,
            0xb8020000, 0x050,
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
            0xb8020000, 0x054,
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
            0xb8020000, 0x058,
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
            0xb8020000, 0x05C,
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
            0xb8020000, 0x060,
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
            0xb8020000, 0x064,
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
            0xb8020000, 0x068,
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
            0xb8020000, 0x06C,
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
            0xb8020000, 0x070,
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
            0xb8020000, 0x074,
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
            0xb8020000, 0x078,
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
            0xb8020000, 0x07C,
            'EM1PCSR', 'RAC_NS.EM1PCSR', 'read-write',
            u"",
            0x00000000, 0x000F0033,
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
        self.MCUEM1PSWRUNNING = RM_Field_RAC_NS_EM1PCSR_MCUEM1PSWRUNNING(self)
        self.zz_fdict['MCUEM1PSWRUNNING'] = self.MCUEM1PSWRUNNING
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
            0x00000000, 0x1FF80000,
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


class RM_Register_RAC_NS_AGCOVERWRITE0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AGCOVERWRITE0, self).__init__(rmio, label,
            0xb8020000, 0x100,
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
            0xb8020000, 0x104,
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


class RM_Register_RAC_NS_AGCOVERWRITE2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AGCOVERWRITE2, self).__init__(rmio, label,
            0xb8020000, 0x108,
            'AGCOVERWRITE2', 'RAC_NS.AGCOVERWRITE2', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENMANFENOTCH = RM_Field_RAC_NS_AGCOVERWRITE2_ENMANFENOTCH(self)
        self.zz_fdict['ENMANFENOTCH'] = self.ENMANFENOTCH
        self.MANFENOTCHEN = RM_Field_RAC_NS_AGCOVERWRITE2_MANFENOTCHEN(self)
        self.zz_fdict['MANFENOTCHEN'] = self.MANFENOTCHEN
        self.MANFENOTCHATTNSEL = RM_Field_RAC_NS_AGCOVERWRITE2_MANFENOTCHATTNSEL(self)
        self.zz_fdict['MANFENOTCHATTNSEL'] = self.MANFENOTCHATTNSEL
        self.MANFENOTCHRATTNENRF0 = RM_Field_RAC_NS_AGCOVERWRITE2_MANFENOTCHRATTNENRF0(self)
        self.zz_fdict['MANFENOTCHRATTNENRF0'] = self.MANFENOTCHRATTNENRF0
        self.MANFENOTCHRATTNENRF1 = RM_Field_RAC_NS_AGCOVERWRITE2_MANFENOTCHRATTNENRF1(self)
        self.zz_fdict['MANFENOTCHRATTNENRF1'] = self.MANFENOTCHRATTNENRF1
        self.MANFENOTCHCAPCRSE = RM_Field_RAC_NS_AGCOVERWRITE2_MANFENOTCHCAPCRSE(self)
        self.zz_fdict['MANFENOTCHCAPCRSE'] = self.MANFENOTCHCAPCRSE
        self.MANFENOTCHCAPFINE = RM_Field_RAC_NS_AGCOVERWRITE2_MANFENOTCHCAPFINE(self)
        self.zz_fdict['MANFENOTCHCAPFINE'] = self.MANFENOTCHCAPFINE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXPKDCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXPKDCTRL, self).__init__(rmio, label,
            0xb8020000, 0x300,
            'TXPKDCTRL', 'RAC_NS.TXPKDCTRL', 'read-write',
            u"",
            0x00000000, 0x0001FFF7,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXPKDCLKDIV = RM_Field_RAC_NS_TXPKDCTRL_TXPKDCLKDIV(self)
        self.zz_fdict['TXPKDCLKDIV'] = self.TXPKDCLKDIV
        self.TXPKDCNTLEN = RM_Field_RAC_NS_TXPKDCTRL_TXPKDCNTLEN(self)
        self.zz_fdict['TXPKDCNTLEN'] = self.TXPKDCNTLEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXPKDCMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXPKDCMD, self).__init__(rmio, label,
            0xb8020000, 0x304,
            'TXPKDCMD', 'RAC_NS.TXPKDCMD', 'write-only',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXPKDSTART = RM_Field_RAC_NS_TXPKDCMD_TXPKDSTART(self)
        self.zz_fdict['TXPKDSTART'] = self.TXPKDSTART
        self.TXPKDSTOP = RM_Field_RAC_NS_TXPKDCMD_TXPKDSTOP(self)
        self.zz_fdict['TXPKDSTOP'] = self.TXPKDSTOP
        self.TXPKDCLR = RM_Field_RAC_NS_TXPKDCMD_TXPKDCLR(self)
        self.zz_fdict['TXPKDCLR'] = self.TXPKDCLR
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXPKDSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXPKDSTATUS, self).__init__(rmio, label,
            0xb8020000, 0x308,
            'TXPKDSTATUS', 'RAC_NS.TXPKDSTATUS', 'read-only',
            u"",
            0x00000000, 0x0001FFF1,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXPKDDONE = RM_Field_RAC_NS_TXPKDSTATUS_TXPKDDONE(self)
        self.zz_fdict['TXPKDDONE'] = self.TXPKDDONE
        self.TXPKDCNT = RM_Field_RAC_NS_TXPKDSTATUS_TXPKDCNT(self)
        self.zz_fdict['TXPKDCNT'] = self.TXPKDCNT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RADIOCLKCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RADIOCLKCTRL, self).__init__(rmio, label,
            0xb8020000, 0x3D0,
            'RADIOCLKCTRL', 'RAC_NS.RADIOCLKCTRL', 'read-write',
            u"",
            0x00000101, 0x00000111,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKSRWUHSPRESC = RM_Field_RAC_NS_RADIOCLKCTRL_CLKSRWUHSPRESC(self)
        self.zz_fdict['CLKSRWUHSPRESC'] = self.CLKSRWUHSPRESC
        self.CLKSRWHSPRESC = RM_Field_RAC_NS_RADIOCLKCTRL_CLKSRWHSPRESC(self)
        self.zz_fdict['CLKSRWHSPRESC'] = self.CLKSRWHSPRESC
        self.CLKSRWLSPRESC = RM_Field_RAC_NS_RADIOCLKCTRL_CLKSRWLSPRESC(self)
        self.zz_fdict['CLKSRWLSPRESC'] = self.CLKSRWLSPRESC
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


class RM_Register_RAC_NS_SOFTMCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SOFTMCTRL, self).__init__(rmio, label,
            0xb8020000, 0x400,
            'SOFTMCTRL', 'RAC_NS.SOFTMCTRL', 'read-write',
            u"",
            0x00000000, 0x00000DFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXPATHEN = RM_Field_RAC_NS_SOFTMCTRL_TXPATHEN(self)
        self.zz_fdict['TXPATHEN'] = self.TXPATHEN
        self.RXPATHEN = RM_Field_RAC_NS_SOFTMCTRL_RXPATHEN(self)
        self.zz_fdict['RXPATHEN'] = self.RXPATHEN
        self.FRCPATHEN = RM_Field_RAC_NS_SOFTMCTRL_FRCPATHEN(self)
        self.zz_fdict['FRCPATHEN'] = self.FRCPATHEN
        self.CLKEN = RM_Field_RAC_NS_SOFTMCTRL_CLKEN(self)
        self.zz_fdict['CLKEN'] = self.CLKEN
        self.CLKRUNNING = RM_Field_RAC_NS_SOFTMCTRL_CLKRUNNING(self)
        self.zz_fdict['CLKRUNNING'] = self.CLKRUNNING
        self.TXMODSEL = RM_Field_RAC_NS_SOFTMCTRL_TXMODSEL(self)
        self.zz_fdict['TXMODSEL'] = self.TXMODSEL
        self.ANTSELSRCSEL = RM_Field_RAC_NS_SOFTMCTRL_ANTSELSRCSEL(self)
        self.zz_fdict['ANTSELSRCSEL'] = self.ANTSELSRCSEL
        self.FRCEN = RM_Field_RAC_NS_SOFTMCTRL_FRCEN(self)
        self.zz_fdict['FRCEN'] = self.FRCEN
        self.DISLEGACYPATH = RM_Field_RAC_NS_SOFTMCTRL_DISLEGACYPATH(self)
        self.zz_fdict['DISLEGACYPATH'] = self.DISLEGACYPATH
        self.TXDACDISABLECLK = RM_Field_RAC_NS_SOFTMCTRL_TXDACDISABLECLK(self)
        self.zz_fdict['TXDACDISABLECLK'] = self.TXDACDISABLECLK
        self.TXDACINVERTCLK = RM_Field_RAC_NS_SOFTMCTRL_TXDACINVERTCLK(self)
        self.zz_fdict['TXDACINVERTCLK'] = self.TXDACINVERTCLK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SFMIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SFMIF, self).__init__(rmio, label,
            0xb8020000, 0x404,
            'SFMIF', 'RAC_NS.SFMIF', 'read-write',
            u"",
            0x00000000, 0x00FF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGESFMIF = RM_Field_RAC_NS_SFMIF_STATECHANGESFMIF(self)
        self.zz_fdict['STATECHANGESFMIF'] = self.STATECHANGESFMIF
        self.STIMCMPEVSFMIF = RM_Field_RAC_NS_SFMIF_STIMCMPEVSFMIF(self)
        self.zz_fdict['STIMCMPEVSFMIF'] = self.STIMCMPEVSFMIF
        self.SEQLOCKUPSFMIF = RM_Field_RAC_NS_SFMIF_SEQLOCKUPSFMIF(self)
        self.zz_fdict['SEQLOCKUPSFMIF'] = self.SEQLOCKUPSFMIF
        self.SEQRESETREQSFMIF = RM_Field_RAC_NS_SFMIF_SEQRESETREQSFMIF(self)
        self.zz_fdict['SEQRESETREQSFMIF'] = self.SEQRESETREQSFMIF
        self.SEQSFMIF = RM_Field_RAC_NS_SFMIF_SEQSFMIF(self)
        self.zz_fdict['SEQSFMIF'] = self.SEQSFMIF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SFMIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SFMIEN, self).__init__(rmio, label,
            0xb8020000, 0x408,
            'SFMIEN', 'RAC_NS.SFMIEN', 'read-write',
            u"",
            0x00000000, 0x00FF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGESFMIEN = RM_Field_RAC_NS_SFMIEN_STATECHANGESFMIEN(self)
        self.zz_fdict['STATECHANGESFMIEN'] = self.STATECHANGESFMIEN
        self.STIMCMPEVSFMIEN = RM_Field_RAC_NS_SFMIEN_STIMCMPEVSFMIEN(self)
        self.zz_fdict['STIMCMPEVSFMIEN'] = self.STIMCMPEVSFMIEN
        self.SEQLOCKUPSFMIEN = RM_Field_RAC_NS_SFMIEN_SEQLOCKUPSFMIEN(self)
        self.zz_fdict['SEQLOCKUPSFMIEN'] = self.SEQLOCKUPSFMIEN
        self.SEQRESETREQSFMIEN = RM_Field_RAC_NS_SFMIEN_SEQRESETREQSFMIEN(self)
        self.zz_fdict['SEQRESETREQSFMIEN'] = self.SEQRESETREQSFMIEN
        self.SEQSFMIEN = RM_Field_RAC_NS_SFMIEN_SEQSFMIEN(self)
        self.zz_fdict['SEQSFMIEN'] = self.SEQSFMIEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFLOCK0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFLOCK0, self).__init__(rmio, label,
            0xb8020000, 0x7F8,
            'RFLOCK0', 'RAC_NS.RFLOCK0', 'read-write',
            u"",
            0x80000000, 0xFFFFF3FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNTHLODIVFREQCTRL = RM_Field_RAC_NS_RFLOCK0_SYNTHLODIVFREQCTRL(self)
        self.zz_fdict['SYNTHLODIVFREQCTRL'] = self.SYNTHLODIVFREQCTRL
        self.TXIQENABLE = RM_Field_RAC_NS_RFLOCK0_TXIQENABLE(self)
        self.zz_fdict['TXIQENABLE'] = self.TXIQENABLE
        self.FFTCOPRO = RM_Field_RAC_NS_RFLOCK0_FFTCOPRO(self)
        self.zz_fdict['FFTCOPRO'] = self.FFTCOPRO
        self.OFDMMODE = RM_Field_RAC_NS_RFLOCK0_OFDMMODE(self)
        self.zz_fdict['OFDMMODE'] = self.OFDMMODE
        self.RACTXENOFDMPA = RM_Field_RAC_NS_RFLOCK0_RACTXENOFDMPA(self)
        self.zz_fdict['RACTXENOFDMPA'] = self.RACTXENOFDMPA
        self.RACIFPGAEN = RM_Field_RAC_NS_RFLOCK0_RACIFPGAEN(self)
        self.zz_fdict['RACIFPGAEN'] = self.RACIFPGAEN
        self.RACTXENFSKPA = RM_Field_RAC_NS_RFLOCK0_RACTXENFSKPA(self)
        self.zz_fdict['RACTXENFSKPA'] = self.RACTXENFSKPA
        self.RACTX0DBM = RM_Field_RAC_NS_RFLOCK0_RACTX0DBM(self)
        self.zz_fdict['RACTX0DBM'] = self.RACTX0DBM
        self.RACTX10DBM = RM_Field_RAC_NS_RFLOCK0_RACTX10DBM(self)
        self.zz_fdict['RACTX10DBM'] = self.RACTX10DBM
        self.RACTX20DBM = RM_Field_RAC_NS_RFLOCK0_RACTX20DBM(self)
        self.zz_fdict['RACTX20DBM'] = self.RACTX20DBM
        self.FRCCONVMODE = RM_Field_RAC_NS_RFLOCK0_FRCCONVMODE(self)
        self.zz_fdict['FRCCONVMODE'] = self.FRCCONVMODE
        self.FRCPAUSING = RM_Field_RAC_NS_RFLOCK0_FRCPAUSING(self)
        self.zz_fdict['FRCPAUSING'] = self.FRCPAUSING
        self.MODEMHADM = RM_Field_RAC_NS_RFLOCK0_MODEMHADM(self)
        self.zz_fdict['MODEMHADM'] = self.MODEMHADM
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



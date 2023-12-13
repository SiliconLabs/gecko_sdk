
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . RAC_S_field import *


class RM_Register_RAC_S_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_IPVERSION, self).__init__(rmio, label,
            0xa0220000, 0x000,
            'IPVERSION', 'RAC_S.IPVERSION', 'read-only',
            u"",
            0x00000005, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_RAC_S_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_EN, self).__init__(rmio, label,
            0xa0220000, 0x004,
            'EN', 'RAC_S.EN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_RAC_S_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RXENSRCEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RXENSRCEN, self).__init__(rmio, label,
            0xa0220000, 0x008,
            'RXENSRCEN', 'RAC_S.RXENSRCEN', 'read-write',
            u"",
            0x00000000, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SWRXEN = RM_Field_RAC_S_RXENSRCEN_SWRXEN(self)
        self.zz_fdict['SWRXEN'] = self.SWRXEN
        self.CHANNELBUSYEN = RM_Field_RAC_S_RXENSRCEN_CHANNELBUSYEN(self)
        self.zz_fdict['CHANNELBUSYEN'] = self.CHANNELBUSYEN
        self.TIMDETEN = RM_Field_RAC_S_RXENSRCEN_TIMDETEN(self)
        self.zz_fdict['TIMDETEN'] = self.TIMDETEN
        self.PREDETEN = RM_Field_RAC_S_RXENSRCEN_PREDETEN(self)
        self.zz_fdict['PREDETEN'] = self.PREDETEN
        self.FRAMEDETEN = RM_Field_RAC_S_RXENSRCEN_FRAMEDETEN(self)
        self.zz_fdict['FRAMEDETEN'] = self.FRAMEDETEN
        self.DEMODRXREQEN = RM_Field_RAC_S_RXENSRCEN_DEMODRXREQEN(self)
        self.zz_fdict['DEMODRXREQEN'] = self.DEMODRXREQEN
        self.PRSRXEN = RM_Field_RAC_S_RXENSRCEN_PRSRXEN(self)
        self.zz_fdict['PRSRXEN'] = self.PRSRXEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_STATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_STATUS, self).__init__(rmio, label,
            0xa0220000, 0x00C,
            'STATUS', 'RAC_S.STATUS', 'read-only',
            u"",
            0x00000000, 0xFFF8FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXMASK = RM_Field_RAC_S_STATUS_RXMASK(self)
        self.zz_fdict['RXMASK'] = self.RXMASK
        self.FORCESTATEACTIVE = RM_Field_RAC_S_STATUS_FORCESTATEACTIVE(self)
        self.zz_fdict['FORCESTATEACTIVE'] = self.FORCESTATEACTIVE
        self.TXAFTERFRAMEPEND = RM_Field_RAC_S_STATUS_TXAFTERFRAMEPEND(self)
        self.zz_fdict['TXAFTERFRAMEPEND'] = self.TXAFTERFRAMEPEND
        self.TXAFTERFRAMEACTIVE = RM_Field_RAC_S_STATUS_TXAFTERFRAMEACTIVE(self)
        self.zz_fdict['TXAFTERFRAMEACTIVE'] = self.TXAFTERFRAMEACTIVE
        self.SEQSLEEPING = RM_Field_RAC_S_STATUS_SEQSLEEPING(self)
        self.zz_fdict['SEQSLEEPING'] = self.SEQSLEEPING
        self.SEQSLEEPDEEP = RM_Field_RAC_S_STATUS_SEQSLEEPDEEP(self)
        self.zz_fdict['SEQSLEEPDEEP'] = self.SEQSLEEPDEEP
        self.STATE = RM_Field_RAC_S_STATUS_STATE(self)
        self.zz_fdict['STATE'] = self.STATE
        self.SEQACTIVE = RM_Field_RAC_S_STATUS_SEQACTIVE(self)
        self.zz_fdict['SEQACTIVE'] = self.SEQACTIVE
        self.DEMODENS = RM_Field_RAC_S_STATUS_DEMODENS(self)
        self.zz_fdict['DEMODENS'] = self.DEMODENS
        self.TXENS = RM_Field_RAC_S_STATUS_TXENS(self)
        self.zz_fdict['TXENS'] = self.TXENS
        self.RXENS = RM_Field_RAC_S_STATUS_RXENS(self)
        self.zz_fdict['RXENS'] = self.RXENS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_CMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_CMD, self).__init__(rmio, label,
            0xa0220000, 0x010,
            'CMD', 'RAC_S.CMD', 'write-only',
            u"",
            0x00000000, 0xC000FDBF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXEN = RM_Field_RAC_S_CMD_TXEN(self)
        self.zz_fdict['TXEN'] = self.TXEN
        self.FORCETX = RM_Field_RAC_S_CMD_FORCETX(self)
        self.zz_fdict['FORCETX'] = self.FORCETX
        self.TXONCCA = RM_Field_RAC_S_CMD_TXONCCA(self)
        self.zz_fdict['TXONCCA'] = self.TXONCCA
        self.CLEARTXEN = RM_Field_RAC_S_CMD_CLEARTXEN(self)
        self.zz_fdict['CLEARTXEN'] = self.CLEARTXEN
        self.TXAFTERFRAME = RM_Field_RAC_S_CMD_TXAFTERFRAME(self)
        self.zz_fdict['TXAFTERFRAME'] = self.TXAFTERFRAME
        self.TXDIS = RM_Field_RAC_S_CMD_TXDIS(self)
        self.zz_fdict['TXDIS'] = self.TXDIS
        self.RXCAL = RM_Field_RAC_S_CMD_RXCAL(self)
        self.zz_fdict['RXCAL'] = self.RXCAL
        self.RXDIS = RM_Field_RAC_S_CMD_RXDIS(self)
        self.zz_fdict['RXDIS'] = self.RXDIS
        self.FRCWR = RM_Field_RAC_S_CMD_FRCWR(self)
        self.zz_fdict['FRCWR'] = self.FRCWR
        self.FRCRD = RM_Field_RAC_S_CMD_FRCRD(self)
        self.zz_fdict['FRCRD'] = self.FRCRD
        self.PAENSET = RM_Field_RAC_S_CMD_PAENSET(self)
        self.zz_fdict['PAENSET'] = self.PAENSET
        self.PAENCLEAR = RM_Field_RAC_S_CMD_PAENCLEAR(self)
        self.zz_fdict['PAENCLEAR'] = self.PAENCLEAR
        self.LNAENSET = RM_Field_RAC_S_CMD_LNAENSET(self)
        self.zz_fdict['LNAENSET'] = self.LNAENSET
        self.LNAENCLEAR = RM_Field_RAC_S_CMD_LNAENCLEAR(self)
        self.zz_fdict['LNAENCLEAR'] = self.LNAENCLEAR
        self.DEMODENSET = RM_Field_RAC_S_CMD_DEMODENSET(self)
        self.zz_fdict['DEMODENSET'] = self.DEMODENSET
        self.DEMODENCLEAR = RM_Field_RAC_S_CMD_DEMODENCLEAR(self)
        self.zz_fdict['DEMODENCLEAR'] = self.DEMODENCLEAR
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_CTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_CTRL, self).__init__(rmio, label,
            0xa0220000, 0x014,
            'CTRL', 'RAC_S.CTRL', 'read-write',
            u"",
            0x08840000, 0xFFBF7FEF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FORCEDISABLE = RM_Field_RAC_S_CTRL_FORCEDISABLE(self)
        self.zz_fdict['FORCEDISABLE'] = self.FORCEDISABLE
        self.PRSTXEN = RM_Field_RAC_S_CTRL_PRSTXEN(self)
        self.zz_fdict['PRSTXEN'] = self.PRSTXEN
        self.TXAFTERRX = RM_Field_RAC_S_CTRL_TXAFTERRX(self)
        self.zz_fdict['TXAFTERRX'] = self.TXAFTERRX
        self.PRSMODE = RM_Field_RAC_S_CTRL_PRSMODE(self)
        self.zz_fdict['PRSMODE'] = self.PRSMODE
        self.PRSCLR = RM_Field_RAC_S_CTRL_PRSCLR(self)
        self.zz_fdict['PRSCLR'] = self.PRSCLR
        self.TXPOSTPONE = RM_Field_RAC_S_CTRL_TXPOSTPONE(self)
        self.zz_fdict['TXPOSTPONE'] = self.TXPOSTPONE
        self.ACTIVEPOL = RM_Field_RAC_S_CTRL_ACTIVEPOL(self)
        self.zz_fdict['ACTIVEPOL'] = self.ACTIVEPOL
        self.PAENPOL = RM_Field_RAC_S_CTRL_PAENPOL(self)
        self.zz_fdict['PAENPOL'] = self.PAENPOL
        self.LNAENPOL = RM_Field_RAC_S_CTRL_LNAENPOL(self)
        self.zz_fdict['LNAENPOL'] = self.LNAENPOL
        self.PRSRXDIS = RM_Field_RAC_S_CTRL_PRSRXDIS(self)
        self.zz_fdict['PRSRXDIS'] = self.PRSRXDIS
        self.AHBSYNC0MODE = RM_Field_RAC_S_CTRL_AHBSYNC0MODE(self)
        self.zz_fdict['AHBSYNC0MODE'] = self.AHBSYNC0MODE
        self.AHBSYNC0REQ = RM_Field_RAC_S_CTRL_AHBSYNC0REQ(self)
        self.zz_fdict['AHBSYNC0REQ'] = self.AHBSYNC0REQ
        self.AHBSYNC0ACK = RM_Field_RAC_S_CTRL_AHBSYNC0ACK(self)
        self.zz_fdict['AHBSYNC0ACK'] = self.AHBSYNC0ACK
        self.PRSFORCETX = RM_Field_RAC_S_CTRL_PRSFORCETX(self)
        self.zz_fdict['PRSFORCETX'] = self.PRSFORCETX
        self.FSMRXABORTHW = RM_Field_RAC_S_CTRL_FSMRXABORTHW(self)
        self.zz_fdict['FSMRXABORTHW'] = self.FSMRXABORTHW
        self.FSMRXABORTHWSYNC = RM_Field_RAC_S_CTRL_FSMRXABORTHWSYNC(self)
        self.zz_fdict['FSMRXABORTHWSYNC'] = self.FSMRXABORTHWSYNC
        self.FSMRXFRAMEEND = RM_Field_RAC_S_CTRL_FSMRXFRAMEEND(self)
        self.zz_fdict['FSMRXFRAMEEND'] = self.FSMRXFRAMEEND
        self.FSMDEMODEN = RM_Field_RAC_S_CTRL_FSMDEMODEN(self)
        self.zz_fdict['FSMDEMODEN'] = self.FSMDEMODEN
        self.FSMWRAPUPNEXTDIS = RM_Field_RAC_S_CTRL_FSMWRAPUPNEXTDIS(self)
        self.zz_fdict['FSMWRAPUPNEXTDIS'] = self.FSMWRAPUPNEXTDIS
        self.HYDRARAMCLKDIS = RM_Field_RAC_S_CTRL_HYDRARAMCLKDIS(self)
        self.zz_fdict['HYDRARAMCLKDIS'] = self.HYDRARAMCLKDIS
        self.SEQRESET = RM_Field_RAC_S_CTRL_SEQRESET(self)
        self.zz_fdict['SEQRESET'] = self.SEQRESET
        self.EXITSHUTDOWNDIS = RM_Field_RAC_S_CTRL_EXITSHUTDOWNDIS(self)
        self.zz_fdict['EXITSHUTDOWNDIS'] = self.EXITSHUTDOWNDIS
        self.CPUWAITDIS = RM_Field_RAC_S_CTRL_CPUWAITDIS(self)
        self.zz_fdict['CPUWAITDIS'] = self.CPUWAITDIS
        self.SEQCLKDIS = RM_Field_RAC_S_CTRL_SEQCLKDIS(self)
        self.zz_fdict['SEQCLKDIS'] = self.SEQCLKDIS
        self.AHBSYNC1MODE = RM_Field_RAC_S_CTRL_AHBSYNC1MODE(self)
        self.zz_fdict['AHBSYNC1MODE'] = self.AHBSYNC1MODE
        self.AHBSYNC1REQ = RM_Field_RAC_S_CTRL_AHBSYNC1REQ(self)
        self.zz_fdict['AHBSYNC1REQ'] = self.AHBSYNC1REQ
        self.AHBSYNC1ACK = RM_Field_RAC_S_CTRL_AHBSYNC1ACK(self)
        self.zz_fdict['AHBSYNC1ACK'] = self.AHBSYNC1ACK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_FORCESTATE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_FORCESTATE, self).__init__(rmio, label,
            0xa0220000, 0x018,
            'FORCESTATE', 'RAC_S.FORCESTATE', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.FORCESTATE = RM_Field_RAC_S_FORCESTATE_FORCESTATE(self)
        self.zz_fdict['FORCESTATE'] = self.FORCESTATE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_IF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_IF, self).__init__(rmio, label,
            0xa0220000, 0x01C,
            'IF', 'RAC_S.IF', 'read-write',
            u"",
            0x00000000, 0xFFFFFF3F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGE = RM_Field_RAC_S_IF_STATECHANGE(self)
        self.zz_fdict['STATECHANGE'] = self.STATECHANGE
        self.STIMCMPEV = RM_Field_RAC_S_IF_STIMCMPEV(self)
        self.zz_fdict['STIMCMPEV'] = self.STIMCMPEV
        self.SEQLOCKUP = RM_Field_RAC_S_IF_SEQLOCKUP(self)
        self.zz_fdict['SEQLOCKUP'] = self.SEQLOCKUP
        self.SEQRESETREQ = RM_Field_RAC_S_IF_SEQRESETREQ(self)
        self.zz_fdict['SEQRESETREQ'] = self.SEQRESETREQ
        self.FSWLOCKUP = RM_Field_RAC_S_IF_FSWLOCKUP(self)
        self.zz_fdict['FSWLOCKUP'] = self.FSWLOCKUP
        self.FSWRESETREQ = RM_Field_RAC_S_IF_FSWRESETREQ(self)
        self.zz_fdict['FSWRESETREQ'] = self.FSWRESETREQ
        self.SEQ = RM_Field_RAC_S_IF_SEQ(self)
        self.zz_fdict['SEQ'] = self.SEQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_IEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_IEN, self).__init__(rmio, label,
            0xa0220000, 0x020,
            'IEN', 'RAC_S.IEN', 'read-write',
            u"",
            0x00000000, 0xFFFFFF3F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGE = RM_Field_RAC_S_IEN_STATECHANGE(self)
        self.zz_fdict['STATECHANGE'] = self.STATECHANGE
        self.STIMCMPEV = RM_Field_RAC_S_IEN_STIMCMPEV(self)
        self.zz_fdict['STIMCMPEV'] = self.STIMCMPEV
        self.SEQLOCKUP = RM_Field_RAC_S_IEN_SEQLOCKUP(self)
        self.zz_fdict['SEQLOCKUP'] = self.SEQLOCKUP
        self.SEQRESETREQ = RM_Field_RAC_S_IEN_SEQRESETREQ(self)
        self.zz_fdict['SEQRESETREQ'] = self.SEQRESETREQ
        self.FSWLOCKUP = RM_Field_RAC_S_IEN_FSWLOCKUP(self)
        self.zz_fdict['FSWLOCKUP'] = self.FSWLOCKUP
        self.FSWRESETREQ = RM_Field_RAC_S_IEN_FSWRESETREQ(self)
        self.zz_fdict['FSWRESETREQ'] = self.FSWRESETREQ
        self.SEQ = RM_Field_RAC_S_IEN_SEQ(self)
        self.zz_fdict['SEQ'] = self.SEQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TESTCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TESTCTRL, self).__init__(rmio, label,
            0xa0220000, 0x024,
            'TESTCTRL', 'RAC_S.TESTCTRL', 'read-write',
            u"",
            0x00000000, 0x00000005,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODEN = RM_Field_RAC_S_TESTCTRL_MODEN(self)
        self.zz_fdict['MODEN'] = self.MODEN
        self.DEMODON = RM_Field_RAC_S_TESTCTRL_DEMODON(self)
        self.zz_fdict['DEMODON'] = self.DEMODON
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SEQIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SEQIF, self).__init__(rmio, label,
            0xa0220000, 0x028,
            'SEQIF', 'RAC_S.SEQIF', 'read-write',
            u"",
            0x00000000, 0x01FF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGE = RM_Field_RAC_S_SEQIF_STATECHANGE(self)
        self.zz_fdict['STATECHANGE'] = self.STATECHANGE
        self.STIMCMPEV = RM_Field_RAC_S_SEQIF_STIMCMPEV(self)
        self.zz_fdict['STIMCMPEV'] = self.STIMCMPEV
        self.DEMODRXREQCLR = RM_Field_RAC_S_SEQIF_DEMODRXREQCLR(self)
        self.zz_fdict['DEMODRXREQCLR'] = self.DEMODRXREQCLR
        self.PRSEVENT = RM_Field_RAC_S_SEQIF_PRSEVENT(self)
        self.zz_fdict['PRSEVENT'] = self.PRSEVENT
        self.STATEOFF = RM_Field_RAC_S_SEQIF_STATEOFF(self)
        self.zz_fdict['STATEOFF'] = self.STATEOFF
        self.STATERXWARM = RM_Field_RAC_S_SEQIF_STATERXWARM(self)
        self.zz_fdict['STATERXWARM'] = self.STATERXWARM
        self.STATERXSEARCH = RM_Field_RAC_S_SEQIF_STATERXSEARCH(self)
        self.zz_fdict['STATERXSEARCH'] = self.STATERXSEARCH
        self.STATERXFRAME = RM_Field_RAC_S_SEQIF_STATERXFRAME(self)
        self.zz_fdict['STATERXFRAME'] = self.STATERXFRAME
        self.STATERXWRAPUP = RM_Field_RAC_S_SEQIF_STATERXWRAPUP(self)
        self.zz_fdict['STATERXWRAPUP'] = self.STATERXWRAPUP
        self.STATETXWARM = RM_Field_RAC_S_SEQIF_STATETXWARM(self)
        self.zz_fdict['STATETXWARM'] = self.STATETXWARM
        self.STATETX = RM_Field_RAC_S_SEQIF_STATETX(self)
        self.zz_fdict['STATETX'] = self.STATETX
        self.STATETXWRAPUP = RM_Field_RAC_S_SEQIF_STATETXWRAPUP(self)
        self.zz_fdict['STATETXWRAPUP'] = self.STATETXWRAPUP
        self.STATESHUTDOWN = RM_Field_RAC_S_SEQIF_STATESHUTDOWN(self)
        self.zz_fdict['STATESHUTDOWN'] = self.STATESHUTDOWN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SEQIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SEQIEN, self).__init__(rmio, label,
            0xa0220000, 0x02C,
            'SEQIEN', 'RAC_S.SEQIEN', 'read-write',
            u"",
            0x00000000, 0x01FF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGE = RM_Field_RAC_S_SEQIEN_STATECHANGE(self)
        self.zz_fdict['STATECHANGE'] = self.STATECHANGE
        self.STIMCMPEV = RM_Field_RAC_S_SEQIEN_STIMCMPEV(self)
        self.zz_fdict['STIMCMPEV'] = self.STIMCMPEV
        self.DEMODRXREQCLR = RM_Field_RAC_S_SEQIEN_DEMODRXREQCLR(self)
        self.zz_fdict['DEMODRXREQCLR'] = self.DEMODRXREQCLR
        self.PRSEVENT = RM_Field_RAC_S_SEQIEN_PRSEVENT(self)
        self.zz_fdict['PRSEVENT'] = self.PRSEVENT
        self.STATEOFF = RM_Field_RAC_S_SEQIEN_STATEOFF(self)
        self.zz_fdict['STATEOFF'] = self.STATEOFF
        self.STATERXWARM = RM_Field_RAC_S_SEQIEN_STATERXWARM(self)
        self.zz_fdict['STATERXWARM'] = self.STATERXWARM
        self.STATERXSEARCH = RM_Field_RAC_S_SEQIEN_STATERXSEARCH(self)
        self.zz_fdict['STATERXSEARCH'] = self.STATERXSEARCH
        self.STATERXFRAME = RM_Field_RAC_S_SEQIEN_STATERXFRAME(self)
        self.zz_fdict['STATERXFRAME'] = self.STATERXFRAME
        self.STATERXWRAPUP = RM_Field_RAC_S_SEQIEN_STATERXWRAPUP(self)
        self.zz_fdict['STATERXWRAPUP'] = self.STATERXWRAPUP
        self.STATETXWARM = RM_Field_RAC_S_SEQIEN_STATETXWARM(self)
        self.zz_fdict['STATETXWARM'] = self.STATETXWARM
        self.STATETX = RM_Field_RAC_S_SEQIEN_STATETX(self)
        self.zz_fdict['STATETX'] = self.STATETX
        self.STATETXWRAPUP = RM_Field_RAC_S_SEQIEN_STATETXWRAPUP(self)
        self.zz_fdict['STATETXWRAPUP'] = self.STATETXWRAPUP
        self.STATESHUTDOWN = RM_Field_RAC_S_SEQIEN_STATESHUTDOWN(self)
        self.zz_fdict['STATESHUTDOWN'] = self.STATESHUTDOWN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_STATUS1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_STATUS1, self).__init__(rmio, label,
            0xa0220000, 0x030,
            'STATUS1', 'RAC_S.STATUS1', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXMASK = RM_Field_RAC_S_STATUS1_TXMASK(self)
        self.zz_fdict['TXMASK'] = self.TXMASK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_FSWIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_FSWIF, self).__init__(rmio, label,
            0xa0220000, 0x034,
            'FSWIF', 'RAC_S.FSWIF', 'read-write',
            u"",
            0x00000000, 0x01FF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGE = RM_Field_RAC_S_FSWIF_STATECHANGE(self)
        self.zz_fdict['STATECHANGE'] = self.STATECHANGE
        self.STIMCMPEV = RM_Field_RAC_S_FSWIF_STIMCMPEV(self)
        self.zz_fdict['STIMCMPEV'] = self.STIMCMPEV
        self.DEMODRXREQCLR = RM_Field_RAC_S_FSWIF_DEMODRXREQCLR(self)
        self.zz_fdict['DEMODRXREQCLR'] = self.DEMODRXREQCLR
        self.PRSEVENT = RM_Field_RAC_S_FSWIF_PRSEVENT(self)
        self.zz_fdict['PRSEVENT'] = self.PRSEVENT
        self.STATEOFF = RM_Field_RAC_S_FSWIF_STATEOFF(self)
        self.zz_fdict['STATEOFF'] = self.STATEOFF
        self.STATERXWARM = RM_Field_RAC_S_FSWIF_STATERXWARM(self)
        self.zz_fdict['STATERXWARM'] = self.STATERXWARM
        self.STATERXSEARCH = RM_Field_RAC_S_FSWIF_STATERXSEARCH(self)
        self.zz_fdict['STATERXSEARCH'] = self.STATERXSEARCH
        self.STATERXFRAME = RM_Field_RAC_S_FSWIF_STATERXFRAME(self)
        self.zz_fdict['STATERXFRAME'] = self.STATERXFRAME
        self.STATERXWRAPUP = RM_Field_RAC_S_FSWIF_STATERXWRAPUP(self)
        self.zz_fdict['STATERXWRAPUP'] = self.STATERXWRAPUP
        self.STATETXWARM = RM_Field_RAC_S_FSWIF_STATETXWARM(self)
        self.zz_fdict['STATETXWARM'] = self.STATETXWARM
        self.STATETX = RM_Field_RAC_S_FSWIF_STATETX(self)
        self.zz_fdict['STATETX'] = self.STATETX
        self.STATETXWRAPUP = RM_Field_RAC_S_FSWIF_STATETXWRAPUP(self)
        self.zz_fdict['STATETXWRAPUP'] = self.STATETXWRAPUP
        self.STATESHUTDOWN = RM_Field_RAC_S_FSWIF_STATESHUTDOWN(self)
        self.zz_fdict['STATESHUTDOWN'] = self.STATESHUTDOWN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_FSWIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_FSWIEN, self).__init__(rmio, label,
            0xa0220000, 0x038,
            'FSWIEN', 'RAC_S.FSWIEN', 'read-write',
            u"",
            0x00000000, 0x01FF000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATECHANGE = RM_Field_RAC_S_FSWIEN_STATECHANGE(self)
        self.zz_fdict['STATECHANGE'] = self.STATECHANGE
        self.STIMCMPEV = RM_Field_RAC_S_FSWIEN_STIMCMPEV(self)
        self.zz_fdict['STIMCMPEV'] = self.STIMCMPEV
        self.DEMODRXREQCLR = RM_Field_RAC_S_FSWIEN_DEMODRXREQCLR(self)
        self.zz_fdict['DEMODRXREQCLR'] = self.DEMODRXREQCLR
        self.PRSEVENT = RM_Field_RAC_S_FSWIEN_PRSEVENT(self)
        self.zz_fdict['PRSEVENT'] = self.PRSEVENT
        self.STATEOFF = RM_Field_RAC_S_FSWIEN_STATEOFF(self)
        self.zz_fdict['STATEOFF'] = self.STATEOFF
        self.STATERXWARM = RM_Field_RAC_S_FSWIEN_STATERXWARM(self)
        self.zz_fdict['STATERXWARM'] = self.STATERXWARM
        self.STATERXSEARCH = RM_Field_RAC_S_FSWIEN_STATERXSEARCH(self)
        self.zz_fdict['STATERXSEARCH'] = self.STATERXSEARCH
        self.STATERXFRAME = RM_Field_RAC_S_FSWIEN_STATERXFRAME(self)
        self.zz_fdict['STATERXFRAME'] = self.STATERXFRAME
        self.STATERXWRAPUP = RM_Field_RAC_S_FSWIEN_STATERXWRAPUP(self)
        self.zz_fdict['STATERXWRAPUP'] = self.STATERXWRAPUP
        self.STATETXWARM = RM_Field_RAC_S_FSWIEN_STATETXWARM(self)
        self.zz_fdict['STATETXWARM'] = self.STATETXWARM
        self.STATETX = RM_Field_RAC_S_FSWIEN_STATETX(self)
        self.zz_fdict['STATETX'] = self.STATETX
        self.STATETXWRAPUP = RM_Field_RAC_S_FSWIEN_STATETXWRAPUP(self)
        self.zz_fdict['STATETXWRAPUP'] = self.STATETXWRAPUP
        self.STATESHUTDOWN = RM_Field_RAC_S_FSWIEN_STATESHUTDOWN(self)
        self.zz_fdict['STATESHUTDOWN'] = self.STATESHUTDOWN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TXWRAPUPNEXT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TXWRAPUPNEXT, self).__init__(rmio, label,
            0xa0220000, 0x03C,
            'TXWRAPUPNEXT', 'RAC_S.TXWRAPUPNEXT', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXWRAPUPNEXT = RM_Field_RAC_S_TXWRAPUPNEXT_TXWRAPUPNEXT(self)
        self.zz_fdict['TXWRAPUPNEXT'] = self.TXWRAPUPNEXT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RXWRAPUPNEXT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RXWRAPUPNEXT, self).__init__(rmio, label,
            0xa0220000, 0x040,
            'RXWRAPUPNEXT', 'RAC_S.RXWRAPUPNEXT', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXWRAPUPNEXT = RM_Field_RAC_S_RXWRAPUPNEXT_RXWRAPUPNEXT(self)
        self.zz_fdict['RXWRAPUPNEXT'] = self.RXWRAPUPNEXT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SEQEND(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SEQEND, self).__init__(rmio, label,
            0xa0220000, 0x044,
            'SEQEND', 'RAC_S.SEQEND', 'read-write',
            u"",
            0x00000000, 0x01FF0000,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATEOFFSEQEND = RM_Field_RAC_S_SEQEND_STATEOFFSEQEND(self)
        self.zz_fdict['STATEOFFSEQEND'] = self.STATEOFFSEQEND
        self.STATERXWARMSEQEND = RM_Field_RAC_S_SEQEND_STATERXWARMSEQEND(self)
        self.zz_fdict['STATERXWARMSEQEND'] = self.STATERXWARMSEQEND
        self.STATERXSEARCHSEQEND = RM_Field_RAC_S_SEQEND_STATERXSEARCHSEQEND(self)
        self.zz_fdict['STATERXSEARCHSEQEND'] = self.STATERXSEARCHSEQEND
        self.STATERXFRAMESEQEND = RM_Field_RAC_S_SEQEND_STATERXFRAMESEQEND(self)
        self.zz_fdict['STATERXFRAMESEQEND'] = self.STATERXFRAMESEQEND
        self.STATERXWRAPUPSEQEND = RM_Field_RAC_S_SEQEND_STATERXWRAPUPSEQEND(self)
        self.zz_fdict['STATERXWRAPUPSEQEND'] = self.STATERXWRAPUPSEQEND
        self.STATETXWARMSEQEND = RM_Field_RAC_S_SEQEND_STATETXWARMSEQEND(self)
        self.zz_fdict['STATETXWARMSEQEND'] = self.STATETXWARMSEQEND
        self.STATETXSEQEND = RM_Field_RAC_S_SEQEND_STATETXSEQEND(self)
        self.zz_fdict['STATETXSEQEND'] = self.STATETXSEQEND
        self.STATETXWRAPUPSEQEND = RM_Field_RAC_S_SEQEND_STATETXWRAPUPSEQEND(self)
        self.zz_fdict['STATETXWRAPUPSEQEND'] = self.STATETXWRAPUPSEQEND
        self.STATESHUTDOWNSEQEND = RM_Field_RAC_S_SEQEND_STATESHUTDOWNSEQEND(self)
        self.zz_fdict['STATESHUTDOWNSEQEND'] = self.STATESHUTDOWNSEQEND
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SEQENDEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SEQENDEN, self).__init__(rmio, label,
            0xa0220000, 0x048,
            'SEQENDEN', 'RAC_S.SEQENDEN', 'read-write',
            u"",
            0x00000000, 0x01FF0000,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATEOFFSEQENDEN = RM_Field_RAC_S_SEQENDEN_STATEOFFSEQENDEN(self)
        self.zz_fdict['STATEOFFSEQENDEN'] = self.STATEOFFSEQENDEN
        self.STATERXWARMSEQENDEN = RM_Field_RAC_S_SEQENDEN_STATERXWARMSEQENDEN(self)
        self.zz_fdict['STATERXWARMSEQENDEN'] = self.STATERXWARMSEQENDEN
        self.STATERXSEARCHSEQENDEN = RM_Field_RAC_S_SEQENDEN_STATERXSEARCHSEQENDEN(self)
        self.zz_fdict['STATERXSEARCHSEQENDEN'] = self.STATERXSEARCHSEQENDEN
        self.STATERXFRAMESEQENDEN = RM_Field_RAC_S_SEQENDEN_STATERXFRAMESEQENDEN(self)
        self.zz_fdict['STATERXFRAMESEQENDEN'] = self.STATERXFRAMESEQENDEN
        self.STATERXWRAPUPSEQENDEN = RM_Field_RAC_S_SEQENDEN_STATERXWRAPUPSEQENDEN(self)
        self.zz_fdict['STATERXWRAPUPSEQENDEN'] = self.STATERXWRAPUPSEQENDEN
        self.STATETXWARMSEQENDEN = RM_Field_RAC_S_SEQENDEN_STATETXWARMSEQENDEN(self)
        self.zz_fdict['STATETXWARMSEQENDEN'] = self.STATETXWARMSEQENDEN
        self.STATETXSEQENDEN = RM_Field_RAC_S_SEQENDEN_STATETXSEQENDEN(self)
        self.zz_fdict['STATETXSEQENDEN'] = self.STATETXSEQENDEN
        self.STATETXWRAPUPSEQENDEN = RM_Field_RAC_S_SEQENDEN_STATETXWRAPUPSEQENDEN(self)
        self.zz_fdict['STATETXWRAPUPSEQENDEN'] = self.STATETXWRAPUPSEQENDEN
        self.STATESHUTDOWNSEQENDEN = RM_Field_RAC_S_SEQENDEN_STATESHUTDOWNSEQENDEN(self)
        self.zz_fdict['STATESHUTDOWNSEQENDEN'] = self.STATESHUTDOWNSEQENDEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_FRCCLKDIS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_FRCCLKDIS, self).__init__(rmio, label,
            0xa0220000, 0x04C,
            'FRCCLKDIS', 'RAC_S.FRCCLKDIS', 'read-write',
            u"",
            0x00000006, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATEOFFFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATEOFFFRCCLKDIS(self)
        self.zz_fdict['STATEOFFFRCCLKDIS'] = self.STATEOFFFRCCLKDIS
        self.STATERXWARMFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATERXWARMFRCCLKDIS(self)
        self.zz_fdict['STATERXWARMFRCCLKDIS'] = self.STATERXWARMFRCCLKDIS
        self.STATERXSEARCHFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATERXSEARCHFRCCLKDIS(self)
        self.zz_fdict['STATERXSEARCHFRCCLKDIS'] = self.STATERXSEARCHFRCCLKDIS
        self.STATERXFRAMEFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATERXFRAMEFRCCLKDIS(self)
        self.zz_fdict['STATERXFRAMEFRCCLKDIS'] = self.STATERXFRAMEFRCCLKDIS
        self.STATERXWRAPUPFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATERXWRAPUPFRCCLKDIS(self)
        self.zz_fdict['STATERXWRAPUPFRCCLKDIS'] = self.STATERXWRAPUPFRCCLKDIS
        self.STATETXWARMFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATETXWARMFRCCLKDIS(self)
        self.zz_fdict['STATETXWARMFRCCLKDIS'] = self.STATETXWARMFRCCLKDIS
        self.STATETXFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATETXFRCCLKDIS(self)
        self.zz_fdict['STATETXFRCCLKDIS'] = self.STATETXFRCCLKDIS
        self.STATETXWRAPUPFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATETXWRAPUPFRCCLKDIS(self)
        self.zz_fdict['STATETXWRAPUPFRCCLKDIS'] = self.STATETXWRAPUPFRCCLKDIS
        self.STATESHUTDOWNFRCCLKDIS = RM_Field_RAC_S_FRCCLKDIS_STATESHUTDOWNFRCCLKDIS(self)
        self.zz_fdict['STATESHUTDOWNFRCCLKDIS'] = self.STATESHUTDOWNFRCCLKDIS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_BUFCCLKDIS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_BUFCCLKDIS, self).__init__(rmio, label,
            0xa0220000, 0x050,
            'BUFCCLKDIS', 'RAC_S.BUFCCLKDIS', 'read-write',
            u"",
            0x00000006, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STATEOFFBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATEOFFBUFCCLKDIS(self)
        self.zz_fdict['STATEOFFBUFCCLKDIS'] = self.STATEOFFBUFCCLKDIS
        self.STATERXWARMBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATERXWARMBUFCCLKDIS(self)
        self.zz_fdict['STATERXWARMBUFCCLKDIS'] = self.STATERXWARMBUFCCLKDIS
        self.STATERXSEARCHBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATERXSEARCHBUFCCLKDIS(self)
        self.zz_fdict['STATERXSEARCHBUFCCLKDIS'] = self.STATERXSEARCHBUFCCLKDIS
        self.STATERXFRAMEBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATERXFRAMEBUFCCLKDIS(self)
        self.zz_fdict['STATERXFRAMEBUFCCLKDIS'] = self.STATERXFRAMEBUFCCLKDIS
        self.STATERXWRAPUPBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATERXWRAPUPBUFCCLKDIS(self)
        self.zz_fdict['STATERXWRAPUPBUFCCLKDIS'] = self.STATERXWRAPUPBUFCCLKDIS
        self.STATETXWARMBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATETXWARMBUFCCLKDIS(self)
        self.zz_fdict['STATETXWARMBUFCCLKDIS'] = self.STATETXWARMBUFCCLKDIS
        self.STATETXBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATETXBUFCCLKDIS(self)
        self.zz_fdict['STATETXBUFCCLKDIS'] = self.STATETXBUFCCLKDIS
        self.STATETXWRAPUPBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATETXWRAPUPBUFCCLKDIS(self)
        self.zz_fdict['STATETXWRAPUPBUFCCLKDIS'] = self.STATETXWRAPUPBUFCCLKDIS
        self.STATESHUTDOWNBUFCCLKDIS = RM_Field_RAC_S_BUFCCLKDIS_STATESHUTDOWNBUFCCLKDIS(self)
        self.zz_fdict['STATESHUTDOWNBUFCCLKDIS'] = self.STATESHUTDOWNBUFCCLKDIS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_STIMER(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_STIMER, self).__init__(rmio, label,
            0xa0220000, 0x058,
            'STIMER', 'RAC_S.STIMER', 'read-only',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STIMER = RM_Field_RAC_S_STIMER_STIMER(self)
        self.zz_fdict['STIMER'] = self.STIMER
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_STIMERCOMP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_STIMERCOMP, self).__init__(rmio, label,
            0xa0220000, 0x05C,
            'STIMERCOMP', 'RAC_S.STIMERCOMP', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STIMERCOMP = RM_Field_RAC_S_STIMERCOMP_STIMERCOMP(self)
        self.zz_fdict['STIMERCOMP'] = self.STIMERCOMP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SEQCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SEQCTRL, self).__init__(rmio, label,
            0xa0220000, 0x060,
            'SEQCTRL', 'RAC_S.SEQCTRL', 'read-write',
            u"",
            0x00000000, 0x0300007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.COMPACT = RM_Field_RAC_S_SEQCTRL_COMPACT(self)
        self.zz_fdict['COMPACT'] = self.COMPACT
        self.COMPINVALMODE = RM_Field_RAC_S_SEQCTRL_COMPINVALMODE(self)
        self.zz_fdict['COMPINVALMODE'] = self.COMPINVALMODE
        self.RELATIVE = RM_Field_RAC_S_SEQCTRL_RELATIVE(self)
        self.zz_fdict['RELATIVE'] = self.RELATIVE
        self.STIMERALWAYSRUN = RM_Field_RAC_S_SEQCTRL_STIMERALWAYSRUN(self)
        self.zz_fdict['STIMERALWAYSRUN'] = self.STIMERALWAYSRUN
        self.STIMERDEBUGRUN = RM_Field_RAC_S_SEQCTRL_STIMERDEBUGRUN(self)
        self.zz_fdict['STIMERDEBUGRUN'] = self.STIMERDEBUGRUN
        self.STATEDEBUGRUN = RM_Field_RAC_S_SEQCTRL_STATEDEBUGRUN(self)
        self.zz_fdict['STATEDEBUGRUN'] = self.STATEDEBUGRUN
        self.SWIRQ = RM_Field_RAC_S_SEQCTRL_SWIRQ(self)
        self.zz_fdict['SWIRQ'] = self.SWIRQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_PRESC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_PRESC, self).__init__(rmio, label,
            0xa0220000, 0x064,
            'PRESC', 'RAC_S.PRESC', 'read-write',
            u"",
            0x00000007, 0x0000007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.STIMER = RM_Field_RAC_S_PRESC_STIMER(self)
        self.zz_fdict['STIMER'] = self.STIMER
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SR0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SR0, self).__init__(rmio, label,
            0xa0220000, 0x068,
            'SR0', 'RAC_S.SR0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SR0 = RM_Field_RAC_S_SR0_SR0(self)
        self.zz_fdict['SR0'] = self.SR0
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SR1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SR1, self).__init__(rmio, label,
            0xa0220000, 0x06C,
            'SR1', 'RAC_S.SR1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SR1 = RM_Field_RAC_S_SR1_SR1(self)
        self.zz_fdict['SR1'] = self.SR1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SR2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SR2, self).__init__(rmio, label,
            0xa0220000, 0x070,
            'SR2', 'RAC_S.SR2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SR2 = RM_Field_RAC_S_SR2_SR2(self)
        self.zz_fdict['SR2'] = self.SR2
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SR3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SR3, self).__init__(rmio, label,
            0xa0220000, 0x074,
            'SR3', 'RAC_S.SR3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SR3 = RM_Field_RAC_S_SR3_SR3(self)
        self.zz_fdict['SR3'] = self.SR3
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_FRCTXWORD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_FRCTXWORD, self).__init__(rmio, label,
            0xa0220000, 0x07C,
            'FRCTXWORD', 'RAC_S.FRCTXWORD', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.WDATA = RM_Field_RAC_S_FRCTXWORD_WDATA(self)
        self.zz_fdict['WDATA'] = self.WDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_FRCRXWORD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_FRCRXWORD, self).__init__(rmio, label,
            0xa0220000, 0x080,
            'FRCRXWORD', 'RAC_S.FRCRXWORD', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RDATA = RM_Field_RAC_S_FRCRXWORD_RDATA(self)
        self.zz_fdict['RDATA'] = self.RDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_EM1PCSR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_EM1PCSR, self).__init__(rmio, label,
            0xa0220000, 0x084,
            'EM1PCSR', 'RAC_S.EM1PCSR', 'read-write',
            u"",
            0x00000000, 0x00070033,
            0x00001000, 0x00002000,
            0x00003000)

        self.RADIOEM1PMODE = RM_Field_RAC_S_EM1PCSR_RADIOEM1PMODE(self)
        self.zz_fdict['RADIOEM1PMODE'] = self.RADIOEM1PMODE
        self.RADIOEM1PDISSWREQ = RM_Field_RAC_S_EM1PCSR_RADIOEM1PDISSWREQ(self)
        self.zz_fdict['RADIOEM1PDISSWREQ'] = self.RADIOEM1PDISSWREQ
        self.MCUEM1PMODE = RM_Field_RAC_S_EM1PCSR_MCUEM1PMODE(self)
        self.zz_fdict['MCUEM1PMODE'] = self.MCUEM1PMODE
        self.MCUEM1PDISSWREQ = RM_Field_RAC_S_EM1PCSR_MCUEM1PDISSWREQ(self)
        self.zz_fdict['MCUEM1PDISSWREQ'] = self.MCUEM1PDISSWREQ
        self.RADIOEM1PREQ = RM_Field_RAC_S_EM1PCSR_RADIOEM1PREQ(self)
        self.zz_fdict['RADIOEM1PREQ'] = self.RADIOEM1PREQ
        self.RADIOEM1PACK = RM_Field_RAC_S_EM1PCSR_RADIOEM1PACK(self)
        self.zz_fdict['RADIOEM1PACK'] = self.RADIOEM1PACK
        self.RADIOEM1PHWREQ = RM_Field_RAC_S_EM1PCSR_RADIOEM1PHWREQ(self)
        self.zz_fdict['RADIOEM1PHWREQ'] = self.RADIOEM1PHWREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_HYDRARAMREMAP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_HYDRARAMREMAP, self).__init__(rmio, label,
            0xa0220000, 0x088,
            'HYDRARAMREMAP', 'RAC_S.HYDRARAMREMAP', 'read-write',
            u"",
            0x00000000, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.HYDRARAMREMAP = RM_Field_RAC_S_HYDRARAMREMAP_HYDRARAMREMAP(self)
        self.zz_fdict['HYDRARAMREMAP'] = self.HYDRARAMREMAP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYNTHENCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYNTHENCTRL, self).__init__(rmio, label,
            0xa0220000, 0x098,
            'SYNTHENCTRL', 'RAC_S.SYNTHENCTRL', 'read-write',
            u"",
            0x00000000, 0x00100200,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNTHSTARTREQ = RM_Field_RAC_S_SYNTHENCTRL_SYNTHSTARTREQ(self)
        self.zz_fdict['SYNTHSTARTREQ'] = self.SYNTHSTARTREQ
        self.LPFBWSEL = RM_Field_RAC_S_SYNTHENCTRL_LPFBWSEL(self)
        self.zz_fdict['LPFBWSEL'] = self.LPFBWSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RFSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RFSTATUS, self).__init__(rmio, label,
            0xa0220000, 0x0AC,
            'RFSTATUS', 'RAC_S.RFSTATUS', 'read-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODRAMPUPDONE = RM_Field_RAC_S_RFSTATUS_MODRAMPUPDONE(self)
        self.zz_fdict['MODRAMPUPDONE'] = self.MODRAMPUPDONE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_STATUS2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_STATUS2, self).__init__(rmio, label,
            0xa0220000, 0x0B0,
            'STATUS2', 'RAC_S.STATUS2', 'read-only',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREVSTATE1 = RM_Field_RAC_S_STATUS2_PREVSTATE1(self)
        self.zz_fdict['PREVSTATE1'] = self.PREVSTATE1
        self.PREVSTATE2 = RM_Field_RAC_S_STATUS2_PREVSTATE2(self)
        self.zz_fdict['PREVSTATE2'] = self.PREVSTATE2
        self.PREVSTATE3 = RM_Field_RAC_S_STATUS2_PREVSTATE3(self)
        self.zz_fdict['PREVSTATE3'] = self.PREVSTATE3
        self.CURRSTATE = RM_Field_RAC_S_STATUS2_CURRSTATE(self)
        self.zz_fdict['CURRSTATE'] = self.CURRSTATE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_IFPGACTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_IFPGACTRL, self).__init__(rmio, label,
            0xa0220000, 0x0B4,
            'IFPGACTRL', 'RAC_S.IFPGACTRL', 'read-write',
            u"",
            0x00000000, 0x0E380000,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCCALON = RM_Field_RAC_S_IFPGACTRL_DCCALON(self)
        self.zz_fdict['DCCALON'] = self.DCCALON
        self.DCRSTEN = RM_Field_RAC_S_IFPGACTRL_DCRSTEN(self)
        self.zz_fdict['DCRSTEN'] = self.DCRSTEN
        self.DCESTIEN = RM_Field_RAC_S_IFPGACTRL_DCESTIEN(self)
        self.zz_fdict['DCESTIEN'] = self.DCESTIEN
        self.DCCALDCGEAR = RM_Field_RAC_S_IFPGACTRL_DCCALDCGEAR(self)
        self.zz_fdict['DCCALDCGEAR'] = self.DCCALDCGEAR
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_PAENCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_PAENCTRL, self).__init__(rmio, label,
            0xa0220000, 0x0B8,
            'PAENCTRL', 'RAC_S.PAENCTRL', 'read-write',
            u"",
            0x00000000, 0x00070100,
            0x00001000, 0x00002000,
            0x00003000)

        self.PARAMP = RM_Field_RAC_S_PAENCTRL_PARAMP(self)
        self.zz_fdict['PARAMP'] = self.PARAMP
        self.INVRAMPCLK = RM_Field_RAC_S_PAENCTRL_INVRAMPCLK(self)
        self.zz_fdict['INVRAMPCLK'] = self.INVRAMPCLK
        self.DIV2RAMPCLK = RM_Field_RAC_S_PAENCTRL_DIV2RAMPCLK(self)
        self.zz_fdict['DIV2RAMPCLK'] = self.DIV2RAMPCLK
        self.RSTDIV2RAMPCLK = RM_Field_RAC_S_PAENCTRL_RSTDIV2RAMPCLK(self)
        self.zz_fdict['RSTDIV2RAMPCLK'] = self.RSTDIV2RAMPCLK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_APC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_APC, self).__init__(rmio, label,
            0xa0220000, 0x0BC,
            'APC', 'RAC_S.APC', 'read-write',
            u"",
            0xFF000000, 0xFF000004,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENAPCSW = RM_Field_RAC_S_APC_ENAPCSW(self)
        self.zz_fdict['ENAPCSW'] = self.ENAPCSW
        self.AMPCONTROLLIMITSW = RM_Field_RAC_S_APC_AMPCONTROLLIMITSW(self)
        self.zz_fdict['AMPCONTROLLIMITSW'] = self.AMPCONTROLLIMITSW
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_ANTDIV(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_ANTDIV, self).__init__(rmio, label,
            0xa0220000, 0x0C0,
            'ANTDIV', 'RAC_S.ANTDIV', 'read-write',
            u"",
            0x00000000, 0x00000DA0,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTDIVLNAMIXEN1 = RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN1(self)
        self.zz_fdict['INTDIVLNAMIXEN1'] = self.INTDIVLNAMIXEN1
        self.INTDIVLNAMIXRFATTDCEN1 = RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFATTDCEN1(self)
        self.zz_fdict['INTDIVLNAMIXRFATTDCEN1'] = self.INTDIVLNAMIXRFATTDCEN1
        self.INTDIVLNAMIXRFPKDENRF1 = RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFPKDENRF1(self)
        self.zz_fdict['INTDIVLNAMIXRFPKDENRF1'] = self.INTDIVLNAMIXRFPKDENRF1
        self.ANTDIVSTATUS = RM_Field_RAC_S_ANTDIV_ANTDIVSTATUS(self)
        self.zz_fdict['ANTDIVSTATUS'] = self.ANTDIVSTATUS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_AUXADCEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_AUXADCEN, self).__init__(rmio, label,
            0xa0220000, 0x0C8,
            'AUXADCEN', 'RAC_S.AUXADCEN', 'read-write',
            u"",
            0x00000000, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCENTSENSE = RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSE(self)
        self.zz_fdict['AUXADCENTSENSE'] = self.AUXADCENTSENSE
        self.AUXADCENTSENSECAL = RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSECAL(self)
        self.zz_fdict['AUXADCENTSENSECAL'] = self.AUXADCENTSENSECAL
        self.AUXADCENAUXADC = RM_Field_RAC_S_AUXADCEN_AUXADCENAUXADC(self)
        self.zz_fdict['AUXADCENAUXADC'] = self.AUXADCENAUXADC
        self.AUXADCENINPUTBUFFER = RM_Field_RAC_S_AUXADCEN_AUXADCENINPUTBUFFER(self)
        self.zz_fdict['AUXADCENINPUTBUFFER'] = self.AUXADCENINPUTBUFFER
        self.AUXADCENPMON = RM_Field_RAC_S_AUXADCEN_AUXADCENPMON(self)
        self.zz_fdict['AUXADCENPMON'] = self.AUXADCENPMON
        self.AUXADCENRESONDIAGA = RM_Field_RAC_S_AUXADCEN_AUXADCENRESONDIAGA(self)
        self.zz_fdict['AUXADCENRESONDIAGA'] = self.AUXADCENRESONDIAGA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_AUXADCCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_AUXADCCTRL0, self).__init__(rmio, label,
            0xa0220000, 0x0CC,
            'AUXADCCTRL0', 'RAC_S.AUXADCCTRL0', 'read-write',
            u"",
            0x00000100, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CYCLES = RM_Field_RAC_S_AUXADCCTRL0_CYCLES(self)
        self.zz_fdict['CYCLES'] = self.CYCLES
        self.MUXSEL = RM_Field_RAC_S_AUXADCCTRL0_MUXSEL(self)
        self.zz_fdict['MUXSEL'] = self.MUXSEL
        self.CLRCOUNTER = RM_Field_RAC_S_AUXADCCTRL0_CLRCOUNTER(self)
        self.zz_fdict['CLRCOUNTER'] = self.CLRCOUNTER
        self.CLRFILTER = RM_Field_RAC_S_AUXADCCTRL0_CLRFILTER(self)
        self.zz_fdict['CLRFILTER'] = self.CLRFILTER
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_AUXADCCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_AUXADCCTRL1, self).__init__(rmio, label,
            0xa0220000, 0x0D0,
            'AUXADCCTRL1', 'RAC_S.AUXADCCTRL1', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCINPUTRESSEL = RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTRESSEL(self)
        self.zz_fdict['AUXADCINPUTRESSEL'] = self.AUXADCINPUTRESSEL
        self.AUXADCTSENSESELVBE = RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSESELVBE(self)
        self.zz_fdict['AUXADCTSENSESELVBE'] = self.AUXADCTSENSESELVBE
        self.AUXADCINPUTBUFFERBYPASS = RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTBUFFERBYPASS(self)
        self.zz_fdict['AUXADCINPUTBUFFERBYPASS'] = self.AUXADCINPUTBUFFERBYPASS
        self.AUXADCINPUTSELECT = RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTSELECT(self)
        self.zz_fdict['AUXADCINPUTSELECT'] = self.AUXADCINPUTSELECT
        self.AUXADCTSENSETRIMVBE2 = RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSETRIMVBE2(self)
        self.zz_fdict['AUXADCTSENSETRIMVBE2'] = self.AUXADCTSENSETRIMVBE2
        self.AUXADCPMONSELECT = RM_Field_RAC_S_AUXADCCTRL1_AUXADCPMONSELECT(self)
        self.zz_fdict['AUXADCPMONSELECT'] = self.AUXADCPMONSELECT
        self.AUXADCENVOLTSCALING = RM_Field_RAC_S_AUXADCCTRL1_AUXADCENVOLTSCALING(self)
        self.zz_fdict['AUXADCENVOLTSCALING'] = self.AUXADCENVOLTSCALING
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_AUXADCOUT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_AUXADCOUT, self).__init__(rmio, label,
            0xa0220000, 0x0D4,
            'AUXADCOUT', 'RAC_S.AUXADCOUT', 'read-only',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCOUT = RM_Field_RAC_S_AUXADCOUT_AUXADCOUT(self)
        self.zz_fdict['AUXADCOUT'] = self.AUXADCOUT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_CLKMULTEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_CLKMULTEN0, self).__init__(rmio, label,
            0xa0220000, 0x0D8,
            'CLKMULTEN0', 'RAC_S.CLKMULTEN0', 'read-write',
            u"",
            0x00400301, 0x07FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTDISICO = RM_Field_RAC_S_CLKMULTEN0_CLKMULTDISICO(self)
        self.zz_fdict['CLKMULTDISICO'] = self.CLKMULTDISICO
        self.CLKMULTENBBDET = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBDET(self)
        self.zz_fdict['CLKMULTENBBDET'] = self.CLKMULTENBBDET
        self.CLKMULTENBBXLDET = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXLDET(self)
        self.zz_fdict['CLKMULTENBBXLDET'] = self.CLKMULTENBBXLDET
        self.CLKMULTENBBXMDET = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXMDET(self)
        self.zz_fdict['CLKMULTENBBXMDET'] = self.CLKMULTENBBXMDET
        self.CLKMULTLDFNIB = RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDFNIB(self)
        self.zz_fdict['CLKMULTLDFNIB'] = self.CLKMULTLDFNIB
        self.CLKMULTENCFDET = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENCFDET(self)
        self.zz_fdict['CLKMULTENCFDET'] = self.CLKMULTENCFDET
        self.CLKMULTLDMNIB = RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDMNIB(self)
        self.zz_fdict['CLKMULTLDMNIB'] = self.CLKMULTLDMNIB
        self.CLKMULTENDITHER = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDITHER(self)
        self.zz_fdict['CLKMULTENDITHER'] = self.CLKMULTENDITHER
        self.CLKMULTRDNIBBLE = RM_Field_RAC_S_CLKMULTEN0_CLKMULTRDNIBBLE(self)
        self.zz_fdict['CLKMULTRDNIBBLE'] = self.CLKMULTRDNIBBLE
        self.CLKMULTENDRVN = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVN(self)
        self.zz_fdict['CLKMULTENDRVN'] = self.CLKMULTENDRVN
        self.CLKMULTLDCNIB = RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDCNIB(self)
        self.zz_fdict['CLKMULTLDCNIB'] = self.CLKMULTLDCNIB
        self.CLKMULTENDRVADC = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVADC(self)
        self.zz_fdict['CLKMULTENDRVADC'] = self.CLKMULTENDRVADC
        self.CLKMULTENDRVP = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVP(self)
        self.zz_fdict['CLKMULTENDRVP'] = self.CLKMULTENDRVP
        self.CLKMULTENFBDIV = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENFBDIV(self)
        self.zz_fdict['CLKMULTENFBDIV'] = self.CLKMULTENFBDIV
        self.CLKMULTENREFDIV = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREFDIV(self)
        self.zz_fdict['CLKMULTENREFDIV'] = self.CLKMULTENREFDIV
        self.CLKMULTENREG1 = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1(self)
        self.zz_fdict['CLKMULTENREG1'] = self.CLKMULTENREG1
        self.CLKMULTENREG2 = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG2(self)
        self.zz_fdict['CLKMULTENREG2'] = self.CLKMULTENREG2
        self.CLKMULTENDRVDAC = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVDAC(self)
        self.zz_fdict['CLKMULTENDRVDAC'] = self.CLKMULTENDRVDAC
        self.CLKMULTENROTDET = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENROTDET(self)
        self.zz_fdict['CLKMULTENROTDET'] = self.CLKMULTENROTDET
        self.CLKMULTENBYPASS40MHZ = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBYPASS40MHZ(self)
        self.zz_fdict['CLKMULTENBYPASS40MHZ'] = self.CLKMULTENBYPASS40MHZ
        self.CLKMULTENDRVIRCAL = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVIRCAL(self)
        self.zz_fdict['CLKMULTENDRVIRCAL'] = self.CLKMULTENDRVIRCAL
        self.CLKMULTENREG1FORCEDSTARTUP = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1FORCEDSTARTUP(self)
        self.zz_fdict['CLKMULTENREG1FORCEDSTARTUP'] = self.CLKMULTENREG1FORCEDSTARTUP
        self.CLKMULTENREG1IBIAS = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1IBIAS(self)
        self.zz_fdict['CLKMULTENREG1IBIAS'] = self.CLKMULTENREG1IBIAS
        self.CLKMULTENREG1REPLICA = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1REPLICA(self)
        self.zz_fdict['CLKMULTENREG1REPLICA'] = self.CLKMULTENREG1REPLICA
        self.CLKMULTENREG1STBLOAD = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1STBLOAD(self)
        self.zz_fdict['CLKMULTENREG1STBLOAD'] = self.CLKMULTENREG1STBLOAD
        self.CLKMULTENDRVTEST = RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTEST(self)
        self.zz_fdict['CLKMULTENDRVTEST'] = self.CLKMULTENDRVTEST
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_CLKMULTEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_CLKMULTEN1, self).__init__(rmio, label,
            0xa0220000, 0x0DC,
            'CLKMULTEN1', 'RAC_S.CLKMULTEN1', 'read-write',
            u"",
            0x01607018, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTINNIBBLE = RM_Field_RAC_S_CLKMULTEN1_CLKMULTINNIBBLE(self)
        self.zz_fdict['CLKMULTINNIBBLE'] = self.CLKMULTINNIBBLE
        self.CLKMULTBWCAL = RM_Field_RAC_S_CLKMULTEN1_CLKMULTBWCAL(self)
        self.zz_fdict['CLKMULTBWCAL'] = self.CLKMULTBWCAL
        self.CLKMULTDRVAMPSEL = RM_Field_RAC_S_CLKMULTEN1_CLKMULTDRVAMPSEL(self)
        self.zz_fdict['CLKMULTDRVAMPSEL'] = self.CLKMULTDRVAMPSEL
        self.CLKMULTILOADREG2 = RM_Field_RAC_S_CLKMULTEN1_CLKMULTILOADREG2(self)
        self.zz_fdict['CLKMULTILOADREG2'] = self.CLKMULTILOADREG2
        self.CLKMULTDIVN = RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVN(self)
        self.zz_fdict['CLKMULTDIVN'] = self.CLKMULTDIVN
        self.CLKMULTFREQCAL = RM_Field_RAC_S_CLKMULTEN1_CLKMULTFREQCAL(self)
        self.zz_fdict['CLKMULTFREQCAL'] = self.CLKMULTFREQCAL
        self.CLKMULTDIVR = RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVR(self)
        self.zz_fdict['CLKMULTDIVR'] = self.CLKMULTDIVR
        self.CLKMULTDIVX = RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVX(self)
        self.zz_fdict['CLKMULTDIVX'] = self.CLKMULTDIVX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_CLKMULTCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_CLKMULTCTRL, self).__init__(rmio, label,
            0xa0220000, 0x0E0,
            'CLKMULTCTRL', 'RAC_S.CLKMULTCTRL', 'read-write',
            u"",
            0x00002448, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTENRESYNC = RM_Field_RAC_S_CLKMULTCTRL_CLKMULTENRESYNC(self)
        self.zz_fdict['CLKMULTENRESYNC'] = self.CLKMULTENRESYNC
        self.CLKMULTVALID = RM_Field_RAC_S_CLKMULTCTRL_CLKMULTVALID(self)
        self.zz_fdict['CLKMULTVALID'] = self.CLKMULTVALID
        self.CLKMULTRESETPHFRQDET = RM_Field_RAC_S_CLKMULTCTRL_CLKMULTRESETPHFRQDET(self)
        self.zz_fdict['CLKMULTRESETPHFRQDET'] = self.CLKMULTRESETPHFRQDET
        self.CLKMULTTRIMVREF1 = RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREF1(self)
        self.zz_fdict['CLKMULTTRIMVREF1'] = self.CLKMULTTRIMVREF1
        self.CLKMULTTRIMVREF2 = RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREF2(self)
        self.zz_fdict['CLKMULTTRIMVREF2'] = self.CLKMULTTRIMVREF2
        self.CLKMULTTRIMVREG1 = RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREG1(self)
        self.zz_fdict['CLKMULTTRIMVREG1'] = self.CLKMULTTRIMVREG1
        self.CLKMULTTRIMREG2IBIAS = RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMREG2IBIAS(self)
        self.zz_fdict['CLKMULTTRIMREG2IBIAS'] = self.CLKMULTTRIMREG2IBIAS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_CLKMULTSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_CLKMULTSTATUS, self).__init__(rmio, label,
            0xa0220000, 0x0E4,
            'CLKMULTSTATUS', 'RAC_S.CLKMULTSTATUS', 'read-only',
            u"",
            0x00000000, 0x0000001F,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTOUTNIBBLE = RM_Field_RAC_S_CLKMULTSTATUS_CLKMULTOUTNIBBLE(self)
        self.zz_fdict['CLKMULTOUTNIBBLE'] = self.CLKMULTOUTNIBBLE
        self.CLKMULTACKVALID = RM_Field_RAC_S_CLKMULTSTATUS_CLKMULTACKVALID(self)
        self.zz_fdict['CLKMULTACKVALID'] = self.CLKMULTACKVALID
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_ADCSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_ADCSTATUS, self).__init__(rmio, label,
            0xa0220000, 0x0F8,
            'ADCSTATUS', 'RAC_S.ADCSTATUS', 'read-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCRCCALOUT = RM_Field_RAC_S_ADCSTATUS_ADCRCCALOUT(self)
        self.zz_fdict['ADCRCCALOUT'] = self.ADCRCCALOUT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_LNAMIXTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_LNAMIXTRIM0, self).__init__(rmio, label,
            0xa0220000, 0x100,
            'LNAMIXTRIM0', 'RAC_S.LNAMIXTRIM0', 'read-write',
            u"",
            0x008EF078, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXTRIMVREG = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXTRIMVREG(self)
        self.zz_fdict['LNAMIXTRIMVREG'] = self.LNAMIXTRIMVREG
        self.LNAMIXIRCAL1AMP = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXIRCAL1AMP(self)
        self.zz_fdict['LNAMIXIRCAL1AMP'] = self.LNAMIXIRCAL1AMP
        self.LNAMIXENREGVHIGH = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXENREGVHIGH(self)
        self.zz_fdict['LNAMIXENREGVHIGH'] = self.LNAMIXENREGVHIGH
        self.LNAMIXLNA1CAPSEL = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXLNA1CAPSEL(self)
        self.zz_fdict['LNAMIXLNA1CAPSEL'] = self.LNAMIXLNA1CAPSEL
        self.LNAMIXRFPKDBWSEL = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDBWSEL(self)
        self.zz_fdict['LNAMIXRFPKDBWSEL'] = self.LNAMIXRFPKDBWSEL
        self.LNAMIXMXRBIAS1 = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXMXRBIAS1(self)
        self.zz_fdict['LNAMIXMXRBIAS1'] = self.LNAMIXMXRBIAS1
        self.LNAMIXIBIAS1TRIM = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXIBIAS1TRIM(self)
        self.zz_fdict['LNAMIXIBIAS1TRIM'] = self.LNAMIXIBIAS1TRIM
        self.LNAMIXTRIMLOW1EN = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXTRIMLOW1EN(self)
        self.zz_fdict['LNAMIXTRIMLOW1EN'] = self.LNAMIXTRIMLOW1EN
        self.LNAMIXNCAS1ADJ = RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXNCAS1ADJ(self)
        self.zz_fdict['LNAMIXNCAS1ADJ'] = self.LNAMIXNCAS1ADJ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_LNAMIXTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_LNAMIXTRIM1, self).__init__(rmio, label,
            0xa0220000, 0x104,
            'LNAMIXTRIM1', 'RAC_S.LNAMIXTRIM1', 'read-write',
            u"",
            0x00000820, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXRFPKDCALCMLO = RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXRFPKDCALCMLO(self)
        self.zz_fdict['LNAMIXRFPKDCALCMLO'] = self.LNAMIXRFPKDCALCMLO
        self.LNAMIXRFPKDCALCMHI = RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXRFPKDCALCMHI(self)
        self.zz_fdict['LNAMIXRFPKDCALCMHI'] = self.LNAMIXRFPKDCALCMHI
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_LNAMIXCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_LNAMIXCAL, self).__init__(rmio, label,
            0xa0220000, 0x114,
            'LNAMIXCAL', 'RAC_S.LNAMIXCAL', 'read-write',
            u"",
            0x00000000, 0x10000000,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXENMXRBIASCAL1 = RM_Field_RAC_S_LNAMIXCAL_LNAMIXENMXRBIASCAL1(self)
        self.zz_fdict['LNAMIXENMXRBIASCAL1'] = self.LNAMIXENMXRBIASCAL1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_PRECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_PRECTRL, self).__init__(rmio, label,
            0xa0220000, 0x11C,
            'PRECTRL', 'RAC_S.PRECTRL', 'read-write',
            u"",
            0x00000000, 0x0000005F,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGBYPFORCE = RM_Field_RAC_S_PRECTRL_PREREGBYPFORCE(self)
        self.zz_fdict['PREREGBYPFORCE'] = self.PREREGBYPFORCE
        self.PREREGENBYPCMP = RM_Field_RAC_S_PRECTRL_PREREGENBYPCMP(self)
        self.zz_fdict['PREREGENBYPCMP'] = self.PREREGENBYPCMP
        self.PREREGENINTBIAS = RM_Field_RAC_S_PRECTRL_PREREGENINTBIAS(self)
        self.zz_fdict['PREREGENINTBIAS'] = self.PREREGENINTBIAS
        self.PREREGENVTRMINI = RM_Field_RAC_S_PRECTRL_PREREGENVTRMINI(self)
        self.zz_fdict['PREREGENVTRMINI'] = self.PREREGENVTRMINI
        self.PREREGENVTRMINISTARTUP = RM_Field_RAC_S_PRECTRL_PREREGENVTRMINISTARTUP(self)
        self.zz_fdict['PREREGENVTRMINISTARTUP'] = self.PREREGENVTRMINISTARTUP
        self.PREREGPOWERSEQUENCEFLAG = RM_Field_RAC_S_PRECTRL_PREREGPOWERSEQUENCEFLAG(self)
        self.zz_fdict['PREREGPOWERSEQUENCEFLAG'] = self.PREREGPOWERSEQUENCEFLAG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_PATRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_PATRIM0, self).__init__(rmio, label,
            0xa0220000, 0x120,
            'PATRIM0', 'RAC_S.PATRIM0', 'read-write',
            u"",
            0x00000000, 0x00020000,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENAMPCTRLREG = RM_Field_RAC_S_PATRIM0_ENAMPCTRLREG(self)
        self.zz_fdict['ENAMPCTRLREG'] = self.ENAMPCTRLREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TXRAMP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TXRAMP, self).__init__(rmio, label,
            0xa0220000, 0x140,
            'TXRAMP', 'RAC_S.TXRAMP', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.PARAMPMODE = RM_Field_RAC_S_TXRAMP_PARAMPMODE(self)
        self.zz_fdict['PARAMPMODE'] = self.PARAMPMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RADIOEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RADIOEN, self).__init__(rmio, label,
            0xa0220000, 0x15C,
            'RADIOEN', 'RAC_S.RADIOEN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGENREG = RM_Field_RAC_S_RADIOEN_PREREGENREG(self)
        self.zz_fdict['PREREGENREG'] = self.PREREGENREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RFPATHEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RFPATHEN0, self).__init__(rmio, label,
            0xa0220000, 0x160,
            'RFPATHEN0', 'RAC_S.RFPATHEN0', 'read-write',
            u"",
            0x00000001, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXRFATTDCEN1 = RM_Field_RAC_S_RFPATHEN0_LNAMIXRFATTDCEN1(self)
        self.zz_fdict['LNAMIXRFATTDCEN1'] = self.LNAMIXRFATTDCEN1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RFPATHEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RFPATHEN1, self).__init__(rmio, label,
            0xa0220000, 0x164,
            'RFPATHEN1', 'RAC_S.RFPATHEN1', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXEN1 = RM_Field_RAC_S_RFPATHEN1_LNAMIXEN1(self)
        self.zz_fdict['LNAMIXEN1'] = self.LNAMIXEN1
        self.LNAMIXRFPKDENRF1 = RM_Field_RAC_S_RFPATHEN1_LNAMIXRFPKDENRF1(self)
        self.zz_fdict['LNAMIXRFPKDENRF1'] = self.LNAMIXRFPKDENRF1
        self.LNAMIXTRSW1 = RM_Field_RAC_S_RFPATHEN1_LNAMIXTRSW1(self)
        self.zz_fdict['LNAMIXTRSW1'] = self.LNAMIXTRSW1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RX, self).__init__(rmio, label,
            0xa0220000, 0x168,
            'RX', 'RAC_S.RX', 'read-write',
            u"",
            0x00000000, 0x00000004,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXENMXRBIAS1 = RM_Field_RAC_S_RX_LNAMIXENMXRBIAS1(self)
        self.zz_fdict['LNAMIXENMXRBIAS1'] = self.LNAMIXENMXRBIAS1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX, self).__init__(rmio, label,
            0xa0220000, 0x16C,
            'TX', 'RAC_S.TX', 'read-write',
            u"",
            0x03FC0201, 0x83FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENPAPOWER = RM_Field_RAC_S_TX_ENPAPOWER(self)
        self.zz_fdict['ENPAPOWER'] = self.ENPAPOWER
        self.ENMANPAPOWER = RM_Field_RAC_S_TX_ENMANPAPOWER(self)
        self.zz_fdict['ENMANPAPOWER'] = self.ENMANPAPOWER
        self.PAPOWERSCALOR = RM_Field_RAC_S_TX_PAPOWERSCALOR(self)
        self.zz_fdict['PAPOWERSCALOR'] = self.PAPOWERSCALOR
        self.MANPAPOWER = RM_Field_RAC_S_TX_MANPAPOWER(self)
        self.zz_fdict['MANPAPOWER'] = self.MANPAPOWER
        self.SWPAPOWERLIMIT = RM_Field_RAC_S_TX_SWPAPOWERLIMIT(self)
        self.zz_fdict['SWPAPOWERLIMIT'] = self.SWPAPOWERLIMIT
        self.ENPASELSLICE = RM_Field_RAC_S_TX_ENPASELSLICE(self)
        self.zz_fdict['ENPASELSLICE'] = self.ENPASELSLICE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYDEBUG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYDEBUG, self).__init__(rmio, label,
            0xa0220000, 0x170,
            'SYDEBUG', 'RAC_S.SYDEBUG', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.XOINJMUXSEL = RM_Field_RAC_S_SYDEBUG_XOINJMUXSEL(self)
        self.zz_fdict['XOINJMUXSEL'] = self.XOINJMUXSEL
        self.XOINJFORCEOFF = RM_Field_RAC_S_SYDEBUG_XOINJFORCEOFF(self)
        self.zz_fdict['XOINJFORCEOFF'] = self.XOINJFORCEOFF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYTRIM0, self).__init__(rmio, label,
            0xa0220000, 0x174,
            'SYTRIM0', 'RAC_S.SYTRIM0', 'read-write',
            u"",
            0x00000008, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDTCRDACTRIM1 = RM_Field_RAC_S_SYTRIM0_SYDTCRDACTRIM1(self)
        self.zz_fdict['SYDTCRDACTRIM1'] = self.SYDTCRDACTRIM1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYTRIM1, self).__init__(rmio, label,
            0xa0220000, 0x178,
            'SYTRIM1', 'RAC_S.SYTRIM1', 'read-write',
            u"",
            0x470AB0D6, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYTDCTRIMDLYSTOPRING = RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYSTOPRING(self)
        self.zz_fdict['SYTDCTRIMDLYSTOPRING'] = self.SYTDCTRIMDLYSTOPRING
        self.SYTDCTRIMDLYCNT = RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCNT(self)
        self.zz_fdict['SYTDCTRIMDLYCNT'] = self.SYTDCTRIMDLYCNT
        self.SYTDCTRIMDLYLOAD = RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYLOAD(self)
        self.zz_fdict['SYTDCTRIMDLYLOAD'] = self.SYTDCTRIMDLYLOAD
        self.SYTDCTRIMDLYSTOPMETA = RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYSTOPMETA(self)
        self.zz_fdict['SYTDCTRIMDLYSTOPMETA'] = self.SYTDCTRIMDLYSTOPMETA
        self.SYDTCREGTRIMVREF = RM_Field_RAC_S_SYTRIM1_SYDTCREGTRIMVREF(self)
        self.zz_fdict['SYDTCREGTRIMVREF'] = self.SYDTCREGTRIMVREF
        self.SYTDCTRIMDLYCK1 = RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCK1(self)
        self.zz_fdict['SYTDCTRIMDLYCK1'] = self.SYTDCTRIMDLYCK1
        self.SYTDCTRIMPERLOAD = RM_Field_RAC_S_SYTRIM1_SYTDCTRIMPERLOAD(self)
        self.zz_fdict['SYTDCTRIMPERLOAD'] = self.SYTDCTRIMPERLOAD
        self.SYDSMDACREGTRIMVREF = RM_Field_RAC_S_SYTRIM1_SYDSMDACREGTRIMVREF(self)
        self.zz_fdict['SYDSMDACREGTRIMVREF'] = self.SYDSMDACREGTRIMVREF
        self.SYDTCRDACTRIM = RM_Field_RAC_S_SYTRIM1_SYDTCRDACTRIM(self)
        self.zz_fdict['SYDTCRDACTRIM'] = self.SYDTCRDACTRIM
        self.SYTDCREGTRIMTEMPCOP = RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMTEMPCOP(self)
        self.zz_fdict['SYTDCREGTRIMTEMPCOP'] = self.SYTDCREGTRIMTEMPCOP
        self.SYTDCREGTRIMTEMPCON = RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMTEMPCON(self)
        self.zz_fdict['SYTDCREGTRIMTEMPCON'] = self.SYTDCREGTRIMTEMPCON
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYLOEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYLOEN0, self).__init__(rmio, label,
            0xa0220000, 0x184,
            'SYLOEN0', 'RAC_S.SYLOEN0', 'read-write',
            u"",
            0x00000000, 0x00004000,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENLODIVDSMDACCLK = RM_Field_RAC_S_SYLOEN0_SYENLODIVDSMDACCLK(self)
        self.zz_fdict['SYENLODIVDSMDACCLK'] = self.SYENLODIVDSMDACCLK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYMMDCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYMMDCTRL, self).__init__(rmio, label,
            0xa0220000, 0x188,
            'SYMMDCTRL', 'RAC_S.SYMMDCTRL', 'read-write',
            u"",
            0x00000000, 0x000701FE,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYMMDCLKDTCPULSEWIDTH = RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKDTCPULSEWIDTH(self)
        self.zz_fdict['SYMMDCLKDTCPULSEWIDTH'] = self.SYMMDCLKDTCPULSEWIDTH
        self.SYMMDCYCSLIPSTROBECOUNT = RM_Field_RAC_S_SYMMDCTRL_SYMMDCYCSLIPSTROBECOUNT(self)
        self.zz_fdict['SYMMDCYCSLIPSTROBECOUNT'] = self.SYMMDCYCSLIPSTROBECOUNT
        self.SYMMDSEL56STG = RM_Field_RAC_S_SYMMDCTRL_SYMMDSEL56STG(self)
        self.zz_fdict['SYMMDSEL56STG'] = self.SYMMDSEL56STG
        self.SYMMDCLKINJXOINTN = RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKINJXOINTN(self)
        self.zz_fdict['SYMMDCLKINJXOINTN'] = self.SYMMDCLKINJXOINTN
        self.SYMMDCLKINJXOINTNFORCE = RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKINJXOINTNFORCE(self)
        self.zz_fdict['SYMMDCLKINJXOINTNFORCE'] = self.SYMMDCLKINJXOINTNFORCE
        self.SYMMDSEL56STGTX = RM_Field_RAC_S_SYMMDCTRL_SYMMDSEL56STGTX(self)
        self.zz_fdict['SYMMDSEL56STGTX'] = self.SYMMDSEL56STGTX
        self.SYMMDCLKDTCPULSEWIDTHTX = RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKDTCPULSEWIDTHTX(self)
        self.zz_fdict['SYMMDCLKDTCPULSEWIDTHTX'] = self.SYMMDCLKDTCPULSEWIDTHTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_DIGCLKRETIMECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_DIGCLKRETIMECTRL, self).__init__(rmio, label,
            0xa0220000, 0x190,
            'DIGCLKRETIMECTRL', 'RAC_S.DIGCLKRETIMECTRL', 'read-write',
            u"",
            0x00000000, 0x0000077F,
            0x00001000, 0x00002000,
            0x00003000)

        self.DIGCLKRETIMEENRETIME = RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME(self)
        self.zz_fdict['DIGCLKRETIMEENRETIME'] = self.DIGCLKRETIMEENRETIME
        self.DIGCLKRETIMEDISRETIME = RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME(self)
        self.zz_fdict['DIGCLKRETIMEDISRETIME'] = self.DIGCLKRETIMEDISRETIME
        self.DIGCLKRETIMERESETN = RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN(self)
        self.zz_fdict['DIGCLKRETIMERESETN'] = self.DIGCLKRETIMERESETN
        self.DIGCLKLPWRETIMERESETN = RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKLPWRETIMERESETN(self)
        self.zz_fdict['DIGCLKLPWRETIMERESETN'] = self.DIGCLKLPWRETIMERESETN
        self.DIGCLKRETIMELIMITH = RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH(self)
        self.zz_fdict['DIGCLKRETIMELIMITH'] = self.DIGCLKRETIMELIMITH
        self.DIGCLKRETIMELIMITL = RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL(self)
        self.zz_fdict['DIGCLKRETIMELIMITL'] = self.DIGCLKRETIMELIMITL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_DIGCLKRETIMESTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_DIGCLKRETIMESTATUS, self).__init__(rmio, label,
            0xa0220000, 0x194,
            'DIGCLKRETIMESTATUS', 'RAC_S.DIGCLKRETIMESTATUS', 'read-only',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.DIGCLKRETIMECLKSEL = RM_Field_RAC_S_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL(self)
        self.zz_fdict['DIGCLKRETIMECLKSEL'] = self.DIGCLKRETIMECLKSEL
        self.DIGCLKRETIMERESETNLO = RM_Field_RAC_S_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO(self)
        self.zz_fdict['DIGCLKRETIMERESETNLO'] = self.DIGCLKRETIMERESETNLO
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_XORETIMECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_XORETIMECTRL, self).__init__(rmio, label,
            0xa0220000, 0x198,
            'XORETIMECTRL', 'RAC_S.XORETIMECTRL', 'read-write',
            u"",
            0x00000000, 0x00000777,
            0x00001000, 0x00002000,
            0x00003000)

        self.XORETIMEENRETIME = RM_Field_RAC_S_XORETIMECTRL_XORETIMEENRETIME(self)
        self.zz_fdict['XORETIMEENRETIME'] = self.XORETIMEENRETIME
        self.XORETIMEDISRETIME = RM_Field_RAC_S_XORETIMECTRL_XORETIMEDISRETIME(self)
        self.zz_fdict['XORETIMEDISRETIME'] = self.XORETIMEDISRETIME
        self.XORETIMERESETN = RM_Field_RAC_S_XORETIMECTRL_XORETIMERESETN(self)
        self.zz_fdict['XORETIMERESETN'] = self.XORETIMERESETN
        self.XORETIMELIMITH = RM_Field_RAC_S_XORETIMECTRL_XORETIMELIMITH(self)
        self.zz_fdict['XORETIMELIMITH'] = self.XORETIMELIMITH
        self.XORETIMELIMITL = RM_Field_RAC_S_XORETIMECTRL_XORETIMELIMITL(self)
        self.zz_fdict['XORETIMELIMITL'] = self.XORETIMELIMITL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_XORETIMESTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_XORETIMESTATUS, self).__init__(rmio, label,
            0xa0220000, 0x19C,
            'XORETIMESTATUS', 'RAC_S.XORETIMESTATUS', 'read-only',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.XORETIMECLKSEL = RM_Field_RAC_S_XORETIMESTATUS_XORETIMECLKSEL(self)
        self.zz_fdict['XORETIMECLKSEL'] = self.XORETIMECLKSEL
        self.XORETIMERESETNLO = RM_Field_RAC_S_XORETIMESTATUS_XORETIMERESETNLO(self)
        self.zz_fdict['XORETIMERESETNLO'] = self.XORETIMERESETNLO
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_AGCOVERWRITE0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_AGCOVERWRITE0, self).__init__(rmio, label,
            0xa0220000, 0x1A0,
            'AGCOVERWRITE0', 'RAC_S.AGCOVERWRITE0', 'read-write',
            u"",
            0x00000000, 0x1FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENMANLNAMIXRFATT = RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXRFATT(self)
        self.zz_fdict['ENMANLNAMIXRFATT'] = self.ENMANLNAMIXRFATT
        self.ENMANLNAMIXSLICE = RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXSLICE(self)
        self.zz_fdict['ENMANLNAMIXSLICE'] = self.ENMANLNAMIXSLICE
        self.ENMANPGAGAIN = RM_Field_RAC_S_AGCOVERWRITE0_ENMANPGAGAIN(self)
        self.zz_fdict['ENMANPGAGAIN'] = self.ENMANPGAGAIN
        self.ENMANIFADCSCALE = RM_Field_RAC_S_AGCOVERWRITE0_ENMANIFADCSCALE(self)
        self.zz_fdict['ENMANIFADCSCALE'] = self.ENMANIFADCSCALE
        self.MANLNAMIXSLICE0 = RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXSLICE0(self)
        self.zz_fdict['MANLNAMIXSLICE0'] = self.MANLNAMIXSLICE0
        self.MANLNAMIXSLICE1 = RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXSLICE1(self)
        self.zz_fdict['MANLNAMIXSLICE1'] = self.MANLNAMIXSLICE1
        self.ENMANTIACOMP = RM_Field_RAC_S_AGCOVERWRITE0_ENMANTIACOMP(self)
        self.zz_fdict['ENMANTIACOMP'] = self.ENMANTIACOMP
        self.MANTIACOMP = RM_Field_RAC_S_AGCOVERWRITE0_MANTIACOMP(self)
        self.zz_fdict['MANTIACOMP'] = self.MANTIACOMP
        self.MANPGAGAIN = RM_Field_RAC_S_AGCOVERWRITE0_MANPGAGAIN(self)
        self.zz_fdict['MANPGAGAIN'] = self.MANPGAGAIN
        self.MANIFADCSCALE = RM_Field_RAC_S_AGCOVERWRITE0_MANIFADCSCALE(self)
        self.zz_fdict['MANIFADCSCALE'] = self.MANIFADCSCALE
        self.ENMANLNAMIXCUREN = RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXCUREN(self)
        self.zz_fdict['ENMANLNAMIXCUREN'] = self.ENMANLNAMIXCUREN
        self.MANLNAMIXCUREN0 = RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXCUREN0(self)
        self.zz_fdict['MANLNAMIXCUREN0'] = self.MANLNAMIXCUREN0
        self.MANLNAMIXCUREN1 = RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXCUREN1(self)
        self.zz_fdict['MANLNAMIXCUREN1'] = self.MANLNAMIXCUREN1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_AGCOVERWRITE1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_AGCOVERWRITE1, self).__init__(rmio, label,
            0xa0220000, 0x1A4,
            'AGCOVERWRITE1', 'RAC_S.AGCOVERWRITE1', 'read-write',
            u"",
            0x00000000, 0x3FFF3FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MANLNAMIXRFATT0 = RM_Field_RAC_S_AGCOVERWRITE1_MANLNAMIXRFATT0(self)
        self.zz_fdict['MANLNAMIXRFATT0'] = self.MANLNAMIXRFATT0
        self.MANLNAMIXRFATT1 = RM_Field_RAC_S_AGCOVERWRITE1_MANLNAMIXRFATT1(self)
        self.zz_fdict['MANLNAMIXRFATT1'] = self.MANLNAMIXRFATT1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SPARE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SPARE, self).__init__(rmio, label,
            0xa0220000, 0x1C4,
            'SPARE', 'RAC_S.SPARE', 'read-write',
            u"",
            0x01800000, 0x01FF87FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTSPARE = RM_Field_RAC_S_SPARE_CLKMULTSPARE(self)
        self.zz_fdict['CLKMULTSPARE'] = self.CLKMULTSPARE
        self.MIXDACTRIMSPAREVREGCORE = RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGCORE(self)
        self.zz_fdict['MIXDACTRIMSPAREVREGCORE'] = self.MIXDACTRIMSPAREVREGCORE
        self.MIXDACTRIMSPARE02 = RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE02(self)
        self.zz_fdict['MIXDACTRIMSPARE02'] = self.MIXDACTRIMSPARE02
        self.MIXDACTRIMSPARE01 = RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE01(self)
        self.zz_fdict['MIXDACTRIMSPARE01'] = self.MIXDACTRIMSPARE01
        self.MIXDACENSPARE02 = RM_Field_RAC_S_SPARE_MIXDACENSPARE02(self)
        self.zz_fdict['MIXDACENSPARE02'] = self.MIXDACENSPARE02
        self.MIXDACTRIMSPAREVREGDIG = RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGDIG(self)
        self.zz_fdict['MIXDACTRIMSPAREVREGDIG'] = self.MIXDACTRIMSPAREVREGDIG
        self.MIXDACENSPARE01 = RM_Field_RAC_S_SPARE_MIXDACENSPARE01(self)
        self.zz_fdict['MIXDACENSPARE01'] = self.MIXDACENSPARE01
        self.SYMMDSPARES = RM_Field_RAC_S_SPARE_SYMMDSPARES(self)
        self.zz_fdict['SYMMDSPARES'] = self.SYMMDSPARES
        self.SYVCOSPARES = RM_Field_RAC_S_SPARE_SYVCOSPARES(self)
        self.zz_fdict['SYVCOSPARES'] = self.SYVCOSPARES
        self.SYTDCSPARES = RM_Field_RAC_S_SPARE_SYTDCSPARES(self)
        self.zz_fdict['SYTDCSPARES'] = self.SYTDCSPARES
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_MIXDACTRIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_MIXDACTRIM, self).__init__(rmio, label,
            0xa0220000, 0x1D4,
            'MIXDACTRIM', 'RAC_S.MIXDACTRIM', 'read-write',
            u"",
            0x030C5B8C, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MIXDACTRIMBBFILTERRES = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMBBFILTERRES(self)
        self.zz_fdict['MIXDACTRIMBBFILTERRES'] = self.MIXDACTRIMBBFILTERRES
        self.MIXDACTRIMLOBIASNMOS = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMLOBIASNMOS(self)
        self.zz_fdict['MIXDACTRIMLOBIASNMOS'] = self.MIXDACTRIMLOBIASNMOS
        self.MIXDACTRIMLOBIASPMOS = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMLOBIASPMOS(self)
        self.zz_fdict['MIXDACTRIMLOBIASPMOS'] = self.MIXDACTRIMLOBIASPMOS
        self.MIXDACTRIMNDACCASC = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMNDACCASC(self)
        self.zz_fdict['MIXDACTRIMNDACCASC'] = self.MIXDACTRIMNDACCASC
        self.MIXDACTRIMPDACCASC = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMPDACCASC(self)
        self.zz_fdict['MIXDACTRIMPDACCASC'] = self.MIXDACTRIMPDACCASC
        self.MIXDACTRIMREFCURRENT = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMREFCURRENT(self)
        self.zz_fdict['MIXDACTRIMREFCURRENT'] = self.MIXDACTRIMREFCURRENT
        self.MIXDACTRIMVREGCORE = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGCORE(self)
        self.zz_fdict['MIXDACTRIMVREGCORE'] = self.MIXDACTRIMVREGCORE
        self.MIXDACTRIMVREGCOREVREF = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGCOREVREF(self)
        self.zz_fdict['MIXDACTRIMVREGCOREVREF'] = self.MIXDACTRIMVREGCOREVREF
        self.MIXDACTRIMVREGDIG = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGDIG(self)
        self.zz_fdict['MIXDACTRIMVREGDIG'] = self.MIXDACTRIMVREGDIG
        self.MIXDACTRIMVREGDIGVREF = RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGDIGVREF(self)
        self.zz_fdict['MIXDACTRIMVREGDIGVREF'] = self.MIXDACTRIMVREGDIGVREF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYTRIM2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYTRIM2, self).__init__(rmio, label,
            0xa0220000, 0x1DC,
            'SYTRIM2', 'RAC_S.SYTRIM2', 'read-write',
            u"",
            0x00007080, 0x0007FFFB,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYMMDREGTRIMVREF = RM_Field_RAC_S_SYTRIM2_SYMMDREGTRIMVREF(self)
        self.zz_fdict['SYMMDREGTRIMVREF'] = self.SYMMDREGTRIMVREF
        self.SYDTCREGVTTRACKSEL = RM_Field_RAC_S_SYTRIM2_SYDTCREGVTTRACKSEL(self)
        self.zz_fdict['SYDTCREGVTTRACKSEL'] = self.SYDTCREGVTTRACKSEL
        self.SYDTCCOFFSETTRIM = RM_Field_RAC_S_SYTRIM2_SYDTCCOFFSETTRIM(self)
        self.zz_fdict['SYDTCCOFFSETTRIM'] = self.SYDTCCOFFSETTRIM
        self.SYENVCOPKD = RM_Field_RAC_S_SYTRIM2_SYENVCOPKD(self)
        self.zz_fdict['SYENVCOPKD'] = self.SYENVCOPKD
        self.SYDTCREGTRIMVTTRACK = RM_Field_RAC_S_SYTRIM2_SYDTCREGTRIMVTTRACK(self)
        self.zz_fdict['SYDTCREGTRIMVTTRACK'] = self.SYDTCREGTRIMVTTRACK
        self.SYTDCREGTRIMVREF = RM_Field_RAC_S_SYTRIM2_SYTDCREGTRIMVREF(self)
        self.zz_fdict['SYTDCREGTRIMVREF'] = self.SYTDCREGTRIMVREF
        self.SYMMDREGTRIMVREGOFFS = RM_Field_RAC_S_SYTRIM2_SYMMDREGTRIMVREGOFFS(self)
        self.zz_fdict['SYMMDREGTRIMVREGOFFS'] = self.SYMMDREGTRIMVREGOFFS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYDLFCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYDLFCTRL1, self).__init__(rmio, label,
            0xa0220000, 0x1E4,
            'SYDLFCTRL1', 'RAC_S.SYDLFCTRL1', 'read-write',
            u"",
            0x00000000, 0x01FF01FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFDQNCGAIN = RM_Field_RAC_S_SYDLFCTRL1_SYDLFDQNCGAIN(self)
        self.zz_fdict['SYDLFDQNCGAIN'] = self.SYDLFDQNCGAIN
        self.SYDLFDTHIN = RM_Field_RAC_S_SYDLFCTRL1_SYDLFDTHIN(self)
        self.zz_fdict['SYDLFDTHIN'] = self.SYDLFDTHIN
        self.SYDLFDQNCGAINTX = RM_Field_RAC_S_SYDLFCTRL1_SYDLFDQNCGAINTX(self)
        self.zz_fdict['SYDLFDQNCGAINTX'] = self.SYDLFDQNCGAINTX
        self.SYDLFDTHINTX = RM_Field_RAC_S_SYDLFCTRL1_SYDLFDTHINTX(self)
        self.zz_fdict['SYDLFDTHINTX'] = self.SYDLFDTHINTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYSTATUS, self).__init__(rmio, label,
            0xa0220000, 0x1E8,
            'SYSTATUS', 'RAC_S.SYSTATUS', 'read-only',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFLMSP0M = RM_Field_RAC_S_SYSTATUS_SYDLFLMSP0M(self)
        self.zz_fdict['SYDLFLMSP0M'] = self.SYDLFLMSP0M
        self.SYDLFVCTRLHI = RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLHI(self)
        self.zz_fdict['SYDLFVCTRLHI'] = self.SYDLFVCTRLHI
        self.SYDLFVCTRLLO = RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLLO(self)
        self.zz_fdict['SYDLFVCTRLLO'] = self.SYDLFVCTRLLO
        self.SYDLFPFDLOCKSAMPLE = RM_Field_RAC_S_SYSTATUS_SYDLFPFDLOCKSAMPLE(self)
        self.zz_fdict['SYDLFPFDLOCKSAMPLE'] = self.SYDLFPFDLOCKSAMPLE
        self.SYDLFPFDREFLEAD = RM_Field_RAC_S_SYSTATUS_SYDLFPFDREFLEAD(self)
        self.zz_fdict['SYDLFPFDREFLEAD'] = self.SYDLFPFDREFLEAD
        self.SYDLFSTATE = RM_Field_RAC_S_SYSTATUS_SYDLFSTATE(self)
        self.zz_fdict['SYDLFSTATE'] = self.SYDLFSTATE
        self.SYMMDCYCSLIPDETECTED = RM_Field_RAC_S_SYSTATUS_SYMMDCYCSLIPDETECTED(self)
        self.zz_fdict['SYMMDCYCSLIPDETECTED'] = self.SYMMDCYCSLIPDETECTED
        self.SYDLFLOCKDETECTED = RM_Field_RAC_S_SYSTATUS_SYDLFLOCKDETECTED(self)
        self.zz_fdict['SYDLFLOCKDETECTED'] = self.SYDLFLOCKDETECTED
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYCTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYCTRL2, self).__init__(rmio, label,
            0xa0220000, 0x1EC,
            'SYCTRL2', 'RAC_S.SYCTRL2', 'read-write',
            u"",
            0x00000008, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDTCREGILOAD = RM_Field_RAC_S_SYCTRL2_SYDTCREGILOAD(self)
        self.zz_fdict['SYDTCREGILOAD'] = self.SYDTCREGILOAD
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TIATRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TIATRIM0, self).__init__(rmio, label,
            0xa0220000, 0x1F0,
            'TIATRIM0', 'RAC_S.TIATRIM0', 'read-write',
            u"",
            0x000000C8, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIATRIMVREF = RM_Field_RAC_S_TIATRIM0_TIATRIMVREF(self)
        self.zz_fdict['TIATRIMVREF'] = self.TIATRIMVREF
        self.TIATRIMVREG = RM_Field_RAC_S_TIATRIM0_TIATRIMVREG(self)
        self.zz_fdict['TIATRIMVREG'] = self.TIATRIMVREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TIAEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TIAEN, self).__init__(rmio, label,
            0xa0220000, 0x1F8,
            'TIAEN', 'RAC_S.TIAEN', 'read-write',
            u"",
            0x00000008, 0x080061FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIAENBIAS = RM_Field_RAC_S_TIAEN_TIAENBIAS(self)
        self.zz_fdict['TIAENBIAS'] = self.TIAENBIAS
        self.TIABIASCURR = RM_Field_RAC_S_TIAEN_TIABIASCURR(self)
        self.zz_fdict['TIABIASCURR'] = self.TIABIASCURR
        self.TIAENREG = RM_Field_RAC_S_TIAEN_TIAENREG(self)
        self.zz_fdict['TIAENREG'] = self.TIAENREG
        self.TIAENSTBLOAD = RM_Field_RAC_S_TIAEN_TIAENSTBLOAD(self)
        self.zz_fdict['TIAENSTBLOAD'] = self.TIAENSTBLOAD
        self.TIAENLATCHI = RM_Field_RAC_S_TIAEN_TIAENLATCHI(self)
        self.zz_fdict['TIAENLATCHI'] = self.TIAENLATCHI
        self.TIAENPKD = RM_Field_RAC_S_TIAEN_TIAENPKD(self)
        self.zz_fdict['TIAENPKD'] = self.TIAENPKD
        self.TIAENLATCHQ = RM_Field_RAC_S_TIAEN_TIAENLATCHQ(self)
        self.zz_fdict['TIAENLATCHQ'] = self.TIAENLATCHQ
        self.TIAENTIAI = RM_Field_RAC_S_TIAEN_TIAENTIAI(self)
        self.zz_fdict['TIAENTIAI'] = self.TIAENTIAI
        self.TIAENTIAQ = RM_Field_RAC_S_TIAEN_TIAENTIAQ(self)
        self.zz_fdict['TIAENTIAQ'] = self.TIAENTIAQ
        self.TIAENDCOC = RM_Field_RAC_S_TIAEN_TIAENDCOC(self)
        self.zz_fdict['TIAENDCOC'] = self.TIAENDCOC
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_VTRCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_VTRCTRL0, self).__init__(rmio, label,
            0xa0220000, 0x1FC,
            'VTRCTRL0', 'RAC_S.VTRCTRL0', 'read-write',
            u"",
            0x00000028, 0x000003FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VTRENINTBIAS = RM_Field_RAC_S_VTRCTRL0_VTRENINTBIAS(self)
        self.zz_fdict['VTRENINTBIAS'] = self.VTRENINTBIAS
        self.VTRENBIASREG = RM_Field_RAC_S_VTRCTRL0_VTRENBIASREG(self)
        self.zz_fdict['VTRENBIASREG'] = self.VTRENBIASREG
        self.VTRENFORCEDVTRSTARTUP = RM_Field_RAC_S_VTRCTRL0_VTRENFORCEDVTRSTARTUP(self)
        self.zz_fdict['VTRENFORCEDVTRSTARTUP'] = self.VTRENFORCEDVTRSTARTUP
        self.VTRDISABLEVTRSTARTUP = RM_Field_RAC_S_VTRCTRL0_VTRDISABLEVTRSTARTUP(self)
        self.zz_fdict['VTRDISABLEVTRSTARTUP'] = self.VTRDISABLEVTRSTARTUP
        self.VTRENCORE = RM_Field_RAC_S_VTRCTRL0_VTRENCORE(self)
        self.zz_fdict['VTRENCORE'] = self.VTRENCORE
        self.VTRENSTBLOADREG = RM_Field_RAC_S_VTRCTRL0_VTRENSTBLOADREG(self)
        self.zz_fdict['VTRENSTBLOADREG'] = self.VTRENSTBLOADREG
        self.VTRSTARTUPCORE = RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPCORE(self)
        self.zz_fdict['VTRSTARTUPCORE'] = self.VTRSTARTUPCORE
        self.VTRSTARTUPSUPPLY = RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPSUPPLY(self)
        self.zz_fdict['VTRSTARTUPSUPPLY'] = self.VTRSTARTUPSUPPLY
        self.VTRHIGHCURRENTHV = RM_Field_RAC_S_VTRCTRL0_VTRHIGHCURRENTHV(self)
        self.zz_fdict['VTRHIGHCURRENTHV'] = self.VTRHIGHCURRENTHV
        self.VTRENREG = RM_Field_RAC_S_VTRCTRL0_VTRENREG(self)
        self.zz_fdict['VTRENREG'] = self.VTRENREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_AUXADCCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_AUXADCCAL, self).__init__(rmio, label,
            0xa0220000, 0x200,
            'AUXADCCAL', 'RAC_S.AUXADCCAL', 'read-write',
            u"",
            0x00000040, 0x0000007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXADCTSENSESELCURR = RM_Field_RAC_S_AUXADCCAL_AUXADCTSENSESELCURR(self)
        self.zz_fdict['AUXADCTSENSESELCURR'] = self.AUXADCTSENSESELCURR
        self.AUXADCTRIMCURRINPUTBUF = RM_Field_RAC_S_AUXADCCAL_AUXADCTRIMCURRINPUTBUF(self)
        self.zz_fdict['AUXADCTRIMCURRINPUTBUF'] = self.AUXADCTRIMCURRINPUTBUF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_AUXADCCTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_AUXADCCTRL2, self).__init__(rmio, label,
            0xa0220000, 0x208,
            'AUXADCCTRL2', 'RAC_S.AUXADCCTRL2', 'read-write',
            u"",
            0x00000000, 0x00000004,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFADCS2PRSTN = RM_Field_RAC_S_AUXADCCTRL2_IFADCS2PRSTN(self)
        self.zz_fdict['IFADCS2PRSTN'] = self.IFADCS2PRSTN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_LNAMIXEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_LNAMIXEN0, self).__init__(rmio, label,
            0xa0220000, 0x20C,
            'LNAMIXEN0', 'RAC_S.LNAMIXEN0', 'read-write',
            u"",
            0x00000000, 0x000001C3,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXENIRCAL1 = RM_Field_RAC_S_LNAMIXEN0_LNAMIXENIRCAL1(self)
        self.zz_fdict['LNAMIXENIRCAL1'] = self.LNAMIXENIRCAL1
        self.LNAMIXENREG = RM_Field_RAC_S_LNAMIXEN0_LNAMIXENREG(self)
        self.zz_fdict['LNAMIXENREG'] = self.LNAMIXENREG
        self.LNAMIXENLOTHRESH = RM_Field_RAC_S_LNAMIXEN0_LNAMIXENLOTHRESH(self)
        self.zz_fdict['LNAMIXENLOTHRESH'] = self.LNAMIXENLOTHRESH
        self.LNAMIXENRFPKD = RM_Field_RAC_S_LNAMIXEN0_LNAMIXENRFPKD(self)
        self.zz_fdict['LNAMIXENRFPKD'] = self.LNAMIXENRFPKD
        self.IRCALON = RM_Field_RAC_S_LNAMIXEN0_IRCALON(self)
        self.zz_fdict['IRCALON'] = self.IRCALON
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_MIXDACEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_MIXDACEN, self).__init__(rmio, label,
            0xa0220000, 0x210,
            'MIXDACEN', 'RAC_S.MIXDACEN', 'read-write',
            u"",
            0x00000000, 0x00033FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MIXDACEN0DBMPA = RM_Field_RAC_S_MIXDACEN_MIXDACEN0DBMPA(self)
        self.zz_fdict['MIXDACEN0DBMPA'] = self.MIXDACEN0DBMPA
        self.MIXDACENBIASVREGDIG = RM_Field_RAC_S_MIXDACEN_MIXDACENBIASVREGDIG(self)
        self.zz_fdict['MIXDACENBIASVREGDIG'] = self.MIXDACENBIASVREGDIG
        self.MIXDACEN10DBMPA = RM_Field_RAC_S_MIXDACEN_MIXDACEN10DBMPA(self)
        self.zz_fdict['MIXDACEN10DBMPA'] = self.MIXDACEN10DBMPA
        self.MIXDACENCLKMULT2P4G = RM_Field_RAC_S_MIXDACEN_MIXDACENCLKMULT2P4G(self)
        self.zz_fdict['MIXDACENCLKMULT2P4G'] = self.MIXDACENCLKMULT2P4G
        self.MIXDACENCORE = RM_Field_RAC_S_MIXDACEN_MIXDACENCORE(self)
        self.zz_fdict['MIXDACENCORE'] = self.MIXDACENCORE
        self.MIXDACENSTBLOADVREGCORE = RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGCORE(self)
        self.zz_fdict['MIXDACENSTBLOADVREGCORE'] = self.MIXDACENSTBLOADVREGCORE
        self.MIXDACENSTBLOADVREGDIG = RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGDIG(self)
        self.zz_fdict['MIXDACENSTBLOADVREGDIG'] = self.MIXDACENSTBLOADVREGDIG
        self.MIXDACENBIASVREGCORE = RM_Field_RAC_S_MIXDACEN_MIXDACENBIASVREGCORE(self)
        self.zz_fdict['MIXDACENBIASVREGCORE'] = self.MIXDACENBIASVREGCORE
        self.MIXDACENVREGCORE = RM_Field_RAC_S_MIXDACEN_MIXDACENVREGCORE(self)
        self.zz_fdict['MIXDACENVREGCORE'] = self.MIXDACENVREGCORE
        self.MIXDACENVREGDIG = RM_Field_RAC_S_MIXDACEN_MIXDACENVREGDIG(self)
        self.zz_fdict['MIXDACENVREGDIG'] = self.MIXDACENVREGDIG
        self.MIXDACENFORCEDSTARTUPVREGDIG = RM_Field_RAC_S_MIXDACEN_MIXDACENFORCEDSTARTUPVREGDIG(self)
        self.zz_fdict['MIXDACENFORCEDSTARTUPVREGDIG'] = self.MIXDACENFORCEDSTARTUPVREGDIG
        self.MIXDACENIRCAL = RM_Field_RAC_S_MIXDACEN_MIXDACENIRCAL(self)
        self.zz_fdict['MIXDACENIRCAL'] = self.MIXDACENIRCAL
        self.MIXDACENPOSEDGEDACCLK = RM_Field_RAC_S_MIXDACEN_MIXDACENPOSEDGEDACCLK(self)
        self.zz_fdict['MIXDACENPOSEDGEDACCLK'] = self.MIXDACENPOSEDGEDACCLK
        self.MIXDACENRFSYNTH = RM_Field_RAC_S_MIXDACEN_MIXDACENRFSYNTH(self)
        self.zz_fdict['MIXDACENRFSYNTH'] = self.MIXDACENRFSYNTH
        self.MIXDACENSTBLOADVREGDIGREPLICA = RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGDIGREPLICA(self)
        self.zz_fdict['MIXDACENSTBLOADVREGDIGREPLICA'] = self.MIXDACENSTBLOADVREGDIGREPLICA
        self.MIXDACENVREGDIGREPLICA = RM_Field_RAC_S_MIXDACEN_MIXDACENVREGDIGREPLICA(self)
        self.zz_fdict['MIXDACENVREGDIGREPLICA'] = self.MIXDACENVREGDIGREPLICA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYCTRL1, self).__init__(rmio, label,
            0xa0220000, 0x214,
            'SYCTRL1', 'RAC_S.SYCTRL1', 'read-write',
            u"",
            0x00000000, 0x000701F3,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYMMDTRIMSYNCTMARGIN = RM_Field_RAC_S_SYCTRL1_SYMMDTRIMSYNCTMARGIN(self)
        self.zz_fdict['SYMMDTRIMSYNCTMARGIN'] = self.SYMMDTRIMSYNCTMARGIN
        self.SYLODIVSELFP4G82G4 = RM_Field_RAC_S_SYCTRL1_SYLODIVSELFP4G82G4(self)
        self.zz_fdict['SYLODIVSELFP4G82G4'] = self.SYLODIVSELFP4G82G4
        self.SYVCOFASTSTARTUP = RM_Field_RAC_S_SYCTRL1_SYVCOFASTSTARTUP(self)
        self.zz_fdict['SYVCOFASTSTARTUP'] = self.SYVCOFASTSTARTUP
        self.SYLODIVSELFP4G82G4TX = RM_Field_RAC_S_SYCTRL1_SYLODIVSELFP4G82G4TX(self)
        self.zz_fdict['SYLODIVSELFP4G82G4TX'] = self.SYLODIVSELFP4G82G4TX
        self.SYMMDREGTRIMVREG = RM_Field_RAC_S_SYCTRL1_SYMMDREGTRIMVREG(self)
        self.zz_fdict['SYMMDREGTRIMVREG'] = self.SYMMDREGTRIMVREG
        self.SYMMDREGTRIMVREGTX = RM_Field_RAC_S_SYCTRL1_SYMMDREGTRIMVREGTX(self)
        self.zz_fdict['SYMMDREGTRIMVREGTX'] = self.SYMMDREGTRIMVREGTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX0DBMEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX0DBMEN, self).__init__(rmio, label,
            0xa0220000, 0x220,
            'TX0DBMEN', 'RAC_S.TX0DBMEN', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMENPAREG = RM_Field_RAC_S_TX0DBMEN_TX0DBMENPAREG(self)
        self.zz_fdict['TX0DBMENPAREG'] = self.TX0DBMENPAREG
        self.TX0DBMENPREDRVREG = RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRVREG(self)
        self.zz_fdict['TX0DBMENPREDRVREG'] = self.TX0DBMENPREDRVREG
        self.TX0DBMENPREDRV = RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRV(self)
        self.zz_fdict['TX0DBMENPREDRV'] = self.TX0DBMENPREDRV
        self.TX0DBMENBYPASSREGPA = RM_Field_RAC_S_TX0DBMEN_TX0DBMENBYPASSREGPA(self)
        self.zz_fdict['TX0DBMENBYPASSREGPA'] = self.TX0DBMENBYPASSREGPA
        self.TX0DBMENREPLICABIASREGPA = RM_Field_RAC_S_TX0DBMEN_TX0DBMENREPLICABIASREGPA(self)
        self.zz_fdict['TX0DBMENREPLICABIASREGPA'] = self.TX0DBMENREPLICABIASREGPA
        self.TX0DBMENPA = RM_Field_RAC_S_TX0DBMEN_TX0DBMENPA(self)
        self.zz_fdict['TX0DBMENPA'] = self.TX0DBMENPA
        self.TX0DBMENPAREGSTBLOAD = RM_Field_RAC_S_TX0DBMEN_TX0DBMENPAREGSTBLOAD(self)
        self.zz_fdict['TX0DBMENPAREGSTBLOAD'] = self.TX0DBMENPAREGSTBLOAD
        self.TX0DBMENPREDRVREGSTBLOAD = RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRVREGSTBLOAD(self)
        self.zz_fdict['TX0DBMENPREDRVREGSTBLOAD'] = self.TX0DBMENPREDRVREGSTBLOAD
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX0DBMCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX0DBMCTRL, self).__init__(rmio, label,
            0xa0220000, 0x224,
            'TX0DBMCTRL', 'RAC_S.TX0DBMCTRL', 'read-write',
            u"",
            0x00000000, 0x00000060,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMPOWERRAMPRESET = RM_Field_RAC_S_TX0DBMCTRL_TX0DBMPOWERRAMPRESET(self)
        self.zz_fdict['TX0DBMPOWERRAMPRESET'] = self.TX0DBMPOWERRAMPRESET
        self.TX0DBMRAMPCLKBYPASS = RM_Field_RAC_S_TX0DBMCTRL_TX0DBMRAMPCLKBYPASS(self)
        self.zz_fdict['TX0DBMRAMPCLKBYPASS'] = self.TX0DBMRAMPCLKBYPASS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX0DBMTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX0DBMTRIM1, self).__init__(rmio, label,
            0xa0220000, 0x228,
            'TX0DBMTRIM1', 'RAC_S.TX0DBMTRIM1', 'read-write',
            u"",
            0x04630776, 0x07FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMTRIMDUTYCYN = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMDUTYCYN(self)
        self.zz_fdict['TX0DBMTRIMDUTYCYN'] = self.TX0DBMTRIMDUTYCYN
        self.TX0DBMTRIMNBIASPA = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMNBIASPA(self)
        self.zz_fdict['TX0DBMTRIMNBIASPA'] = self.TX0DBMTRIMNBIASPA
        self.TX0DBMTRIMPBIASPA = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPBIASPA(self)
        self.zz_fdict['TX0DBMTRIMPBIASPA'] = self.TX0DBMTRIMPBIASPA
        self.TX0DBMTRIMLOINTVDDAPREDRV = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMLOINTVDDAPREDRV(self)
        self.zz_fdict['TX0DBMTRIMLOINTVDDAPREDRV'] = self.TX0DBMTRIMLOINTVDDAPREDRV
        self.TX0DBMTRIMRFBREGPA = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMRFBREGPA(self)
        self.zz_fdict['TX0DBMTRIMRFBREGPA'] = self.TX0DBMTRIMRFBREGPA
        self.TX0DBMTRIMPREDRVREGEXTRALOAD = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPREDRVREGEXTRALOAD(self)
        self.zz_fdict['TX0DBMTRIMPREDRVREGEXTRALOAD'] = self.TX0DBMTRIMPREDRVREGEXTRALOAD
        self.TX0DBMTRIMPAREGEXTRALOAD = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPAREGEXTRALOAD(self)
        self.zz_fdict['TX0DBMTRIMPAREGEXTRALOAD'] = self.TX0DBMTRIMPAREGEXTRALOAD
        self.TX0DBMTRIMDUTYCYP = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMDUTYCYP(self)
        self.zz_fdict['TX0DBMTRIMDUTYCYP'] = self.TX0DBMTRIMDUTYCYP
        self.TX0DBMTRIMVREFREGPREDRV = RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMVREFREGPREDRV(self)
        self.zz_fdict['TX0DBMTRIMVREFREGPREDRV'] = self.TX0DBMTRIMVREFREGPREDRV
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX0DBMTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX0DBMTRIM0, self).__init__(rmio, label,
            0xa0220000, 0x22C,
            'TX0DBMTRIM0', 'RAC_S.TX0DBMTRIM0', 'read-write',
            u"",
            0x0008080C, 0x000F0FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMTRIMPSRBSTREGPREDRV = RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPSRBSTREGPREDRV(self)
        self.zz_fdict['TX0DBMTRIMPSRBSTREGPREDRV'] = self.TX0DBMTRIMPSRBSTREGPREDRV
        self.TX0DBMTRIMPREDRVSLOPE = RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPREDRVSLOPE(self)
        self.zz_fdict['TX0DBMTRIMPREDRVSLOPE'] = self.TX0DBMTRIMPREDRVSLOPE
        self.TX0DBMTRIMPSRBSTREGPA = RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPSRBSTREGPA(self)
        self.zz_fdict['TX0DBMTRIMPSRBSTREGPA'] = self.TX0DBMTRIMPSRBSTREGPA
        self.TX0DBMTRIMTAPCAP100F = RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMTAPCAP100F(self)
        self.zz_fdict['TX0DBMTRIMTAPCAP100F'] = self.TX0DBMTRIMTAPCAP100F
        self.TX0DBMTRIMTAPCAP200F = RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMTAPCAP200F(self)
        self.zz_fdict['TX0DBMTRIMTAPCAP200F'] = self.TX0DBMTRIMTAPCAP200F
        self.TX0DBMTRIMVREFREGPA = RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMVREFREGPA(self)
        self.zz_fdict['TX0DBMTRIMVREFREGPA'] = self.TX0DBMTRIMVREFREGPA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX10DBMEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX10DBMEN, self).__init__(rmio, label,
            0xa0220000, 0x230,
            'TX10DBMEN', 'RAC_S.TX10DBMEN', 'read-write',
            u"",
            0x00000000, 0x0007077E,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMENPA = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPA(self)
        self.zz_fdict['TX10DBMENPA'] = self.TX10DBMENPA
        self.TX10DBMENPAREG = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREG(self)
        self.zz_fdict['TX10DBMENPAREG'] = self.TX10DBMENPAREG
        self.TX10DBMENPREDRV = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRV(self)
        self.zz_fdict['TX10DBMENPREDRV'] = self.TX10DBMENPREDRV
        self.TX10DBMENPREDRVREG = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRVREG(self)
        self.zz_fdict['TX10DBMENPREDRVREG'] = self.TX10DBMENPREDRVREG
        self.TX10DBMENPAREGPULLDOWN = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGPULLDOWN(self)
        self.zz_fdict['TX10DBMENPAREGPULLDOWN'] = self.TX10DBMENPAREGPULLDOWN
        self.TX10DBMENPAREGSTBLOAD = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGSTBLOAD(self)
        self.zz_fdict['TX10DBMENPAREGSTBLOAD'] = self.TX10DBMENPAREGSTBLOAD
        self.TX10DBMENPAOUTBIAS = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAOUTBIAS(self)
        self.zz_fdict['TX10DBMENPAOUTBIAS'] = self.TX10DBMENPAOUTBIAS
        self.TX10DBMENRXPADATTN = RM_Field_RAC_S_TX10DBMEN_TX10DBMENRXPADATTN(self)
        self.zz_fdict['TX10DBMENRXPADATTN'] = self.TX10DBMENRXPADATTN
        self.TX10DBMENPREDRVREGSTBLOAD = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRVREGSTBLOAD(self)
        self.zz_fdict['TX10DBMENPREDRVREGSTBLOAD'] = self.TX10DBMENPREDRVREGSTBLOAD
        self.TX10DBMENPAREGPULLDOWNTX = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGPULLDOWNTX(self)
        self.zz_fdict['TX10DBMENPAREGPULLDOWNTX'] = self.TX10DBMENPAREGPULLDOWNTX
        self.TX10DBMENPAOUTBIASTX = RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAOUTBIASTX(self)
        self.zz_fdict['TX10DBMENPAOUTBIASTX'] = self.TX10DBMENPAOUTBIASTX
        self.TX10DBMENRXPADATTNTX = RM_Field_RAC_S_TX10DBMEN_TX10DBMENRXPADATTNTX(self)
        self.zz_fdict['TX10DBMENRXPADATTNTX'] = self.TX10DBMENRXPADATTNTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX10DBMCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX10DBMCTRL0, self).__init__(rmio, label,
            0xa0220000, 0x234,
            'TX10DBMCTRL0', 'RAC_S.TX10DBMCTRL0', 'read-write',
            u"",
            0x00000000, 0x0000187F,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMPOWER = RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMPOWER(self)
        self.zz_fdict['TX10DBMPOWER'] = self.TX10DBMPOWER
        self.TX10DBMRAMPCLKBYPASS = RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMRAMPCLKBYPASS(self)
        self.zz_fdict['TX10DBMRAMPCLKBYPASS'] = self.TX10DBMRAMPCLKBYPASS
        self.TX10DBMPOWERRAMPRESET = RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMPOWERRAMPRESET(self)
        self.zz_fdict['TX10DBMPOWERRAMPRESET'] = self.TX10DBMPOWERRAMPRESET
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX10DBMTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX10DBMTRIM1, self).__init__(rmio, label,
            0xa0220000, 0x240,
            'TX10DBMTRIM1', 'RAC_S.TX10DBMTRIM1', 'read-write',
            u"",
            0x002020AD, 0x03FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMTRIMBIASDION = RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASDION(self)
        self.zz_fdict['TX10DBMTRIMBIASDION'] = self.TX10DBMTRIMBIASDION
        self.TX10DBMTRIMBIASDIOP = RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASDIOP(self)
        self.zz_fdict['TX10DBMTRIMBIASDIOP'] = self.TX10DBMTRIMBIASDIOP
        self.TX10DBMTRIMNSWBIAS = RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMNSWBIAS(self)
        self.zz_fdict['TX10DBMTRIMNSWBIAS'] = self.TX10DBMTRIMNSWBIAS
        self.TX10DBMTRIMPSWBIAS = RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMPSWBIAS(self)
        self.zz_fdict['TX10DBMTRIMPSWBIAS'] = self.TX10DBMTRIMPSWBIAS
        self.TX10DBMTRIMBIASN = RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASN(self)
        self.zz_fdict['TX10DBMTRIMBIASN'] = self.TX10DBMTRIMBIASN
        self.TX10DBMTRIMDUTYN = RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMDUTYN(self)
        self.zz_fdict['TX10DBMTRIMDUTYN'] = self.TX10DBMTRIMDUTYN
        self.TX10DBMTRIMBIASP = RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASP(self)
        self.zz_fdict['TX10DBMTRIMBIASP'] = self.TX10DBMTRIMBIASP
        self.TX10DBMTRIMDUTYP = RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMDUTYP(self)
        self.zz_fdict['TX10DBMTRIMDUTYP'] = self.TX10DBMTRIMDUTYP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX10DBMTRIM2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX10DBMTRIM2, self).__init__(rmio, label,
            0xa0220000, 0x244,
            'TX10DBMTRIM2', 'RAC_S.TX10DBMTRIM2', 'read-write',
            u"",
            0x00B2EE14, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMTRIMPREDRVREGSLICES = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGSLICES(self)
        self.zz_fdict['TX10DBMTRIMPREDRVREGSLICES'] = self.TX10DBMTRIMPREDRVREGSLICES
        self.TX10DBMTRIMPREDRVSLC = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVSLC(self)
        self.zz_fdict['TX10DBMTRIMPREDRVSLC'] = self.TX10DBMTRIMPREDRVSLC
        self.TX10DBMTRIMPREDRVREGPSR = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGPSR(self)
        self.zz_fdict['TX10DBMTRIMPREDRVREGPSR'] = self.TX10DBMTRIMPREDRVREGPSR
        self.TX10DBMTRIMPREDRVREG = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREG(self)
        self.zz_fdict['TX10DBMTRIMPREDRVREG'] = self.TX10DBMTRIMPREDRVREG
        self.TX10DBMTRIMPAREG = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREG(self)
        self.zz_fdict['TX10DBMTRIMPAREG'] = self.TX10DBMTRIMPAREG
        self.TX10DBMTRIMPAREGVREF = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREGVREF(self)
        self.zz_fdict['TX10DBMTRIMPAREGVREF'] = self.TX10DBMTRIMPAREGVREF
        self.TX10DBMTRIMPREDRVREGVREF = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGVREF(self)
        self.zz_fdict['TX10DBMTRIMPREDRVREGVREF'] = self.TX10DBMTRIMPREDRVREGVREF
        self.TX10DBMTRIMPAREGPSR = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREGPSR(self)
        self.zz_fdict['TX10DBMTRIMPAREGPSR'] = self.TX10DBMTRIMPAREGPSR
        self.TX10DBMTRIMPREDRVCAP = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVCAP(self)
        self.zz_fdict['TX10DBMTRIMPREDRVCAP'] = self.TX10DBMTRIMPREDRVCAP
        self.TX10DBMTRIMLOINTVDDAPREDRV = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMLOINTVDDAPREDRV(self)
        self.zz_fdict['TX10DBMTRIMLOINTVDDAPREDRV'] = self.TX10DBMTRIMLOINTVDDAPREDRV
        self.TX10DBMENPAREGSTBLOADAUTO = RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMENPAREGSTBLOADAUTO(self)
        self.zz_fdict['TX10DBMENPAREGSTBLOADAUTO'] = self.TX10DBMENPAREGSTBLOADAUTO
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_PREREGTRIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_PREREGTRIM, self).__init__(rmio, label,
            0xa0220000, 0x248,
            'PREREGTRIM', 'RAC_S.PREREGTRIM', 'read-write',
            u"",
            0x000042CC, 0x00007FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGTRIMVREG = RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVREG(self)
        self.zz_fdict['PREREGTRIMVREG'] = self.PREREGTRIMVREG
        self.PREREGTRIMVTRMINIVOLTAGE = RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVTRMINIVOLTAGE(self)
        self.zz_fdict['PREREGTRIMVTRMINIVOLTAGE'] = self.PREREGTRIMVTRMINIVOLTAGE
        self.PREREGTRIMBYPCMPVREF = RM_Field_RAC_S_PREREGTRIM_PREREGTRIMBYPCMPVREF(self)
        self.zz_fdict['PREREGTRIMBYPCMPVREF'] = self.PREREGTRIMBYPCMPVREF
        self.PREREGTRIMVTRMINITEMPCO = RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVTRMINITEMPCO(self)
        self.zz_fdict['PREREGTRIMVTRMINITEMPCO'] = self.PREREGTRIMVTRMINITEMPCO
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_MIXDACTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_MIXDACTRIM1, self).__init__(rmio, label,
            0xa0220000, 0x24C,
            'MIXDACTRIM1', 'RAC_S.MIXDACTRIM1', 'read-write',
            u"",
            0x00000002, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.MIXDACTRIMBBSUPPLYSERIESRES = RM_Field_RAC_S_MIXDACTRIM1_MIXDACTRIMBBSUPPLYSERIESRES(self)
        self.zz_fdict['MIXDACTRIMBBSUPPLYSERIESRES'] = self.MIXDACTRIMBBSUPPLYSERIESRES
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYDLF1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYDLF1, self).__init__(rmio, label,
            0xa0220000, 0x250,
            'SYDLF1', 'RAC_S.SYDLF1', 'read-write',
            u"",
            0x00000000, 0x03FF03FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFTDCDBIAS = RM_Field_RAC_S_SYDLF1_SYDLFTDCDBIAS(self)
        self.zz_fdict['SYDLFTDCDBIAS'] = self.SYDLFTDCDBIAS
        self.SYDLFTDCDBIASTX = RM_Field_RAC_S_SYDLF1_SYDLFTDCDBIASTX(self)
        self.zz_fdict['SYDLFTDCDBIASTX'] = self.SYDLFTDCDBIASTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SPARE1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SPARE1, self).__init__(rmio, label,
            0xa0220000, 0x258,
            'SPARE1', 'RAC_S.SPARE1', 'read-write',
            u"",
            0x00000000, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXSPARE1 = RM_Field_RAC_S_SPARE1_LNAMIXSPARE1(self)
        self.zz_fdict['LNAMIXSPARE1'] = self.LNAMIXSPARE1
        self.LNAMIXSPARE2 = RM_Field_RAC_S_SPARE1_LNAMIXSPARE2(self)
        self.zz_fdict['LNAMIXSPARE2'] = self.LNAMIXSPARE2
        self.TIASPARE = RM_Field_RAC_S_SPARE1_TIASPARE(self)
        self.zz_fdict['TIASPARE'] = self.TIASPARE
        self.TX10DBMSPARE = RM_Field_RAC_S_SPARE1_TX10DBMSPARE(self)
        self.zz_fdict['TX10DBMSPARE'] = self.TX10DBMSPARE
        self.VTRSPARES = RM_Field_RAC_S_SPARE1_VTRSPARES(self)
        self.zz_fdict['VTRSPARES'] = self.VTRSPARES
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_PREREGSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_PREREGSTATUS, self).__init__(rmio, label,
            0xa0220000, 0x25C,
            'PREREGSTATUS', 'RAC_S.PREREGSTATUS', 'read-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGBYPOUTCOLLAPSED = RM_Field_RAC_S_PREREGSTATUS_PREREGBYPOUTCOLLAPSED(self)
        self.zz_fdict['PREREGBYPOUTCOLLAPSED'] = self.PREREGBYPOUTCOLLAPSED
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_VTRTRIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_VTRTRIM, self).__init__(rmio, label,
            0xa0220000, 0x260,
            'VTRTRIM', 'RAC_S.VTRTRIM', 'read-write',
            u"",
            0x008B76E7, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VTRTRIMIBIAS = RM_Field_RAC_S_VTRTRIM_VTRTRIMIBIAS(self)
        self.zz_fdict['VTRTRIMIBIAS'] = self.VTRTRIMIBIAS
        self.VTRTRIMVREF = RM_Field_RAC_S_VTRTRIM_VTRTRIMVREF(self)
        self.zz_fdict['VTRTRIMVREF'] = self.VTRTRIMVREF
        self.VTRTRIMTC = RM_Field_RAC_S_VTRTRIM_VTRTRIMTC(self)
        self.zz_fdict['VTRTRIMTC'] = self.VTRTRIMTC
        self.VTRTRIMVREFPREREG = RM_Field_RAC_S_VTRTRIM_VTRTRIMVREFPREREG(self)
        self.zz_fdict['VTRTRIMVREFPREREG'] = self.VTRTRIMVREFPREREG
        self.VTRTRIMVREFVTR = RM_Field_RAC_S_VTRTRIM_VTRTRIMVREFVTR(self)
        self.zz_fdict['VTRTRIMVREFVTR'] = self.VTRTRIMVREFVTR
        self.VTRTRIMVREG = RM_Field_RAC_S_VTRTRIM_VTRTRIMVREG(self)
        self.zz_fdict['VTRTRIMVREG'] = self.VTRTRIMVREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_ADCCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_ADCCTRL0, self).__init__(rmio, label,
            0xa0220000, 0x264,
            'ADCCTRL0', 'RAC_S.ADCCTRL0', 'read-write',
            u"",
            0x18CE2400, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCTUNERCCALMODE = RM_Field_RAC_S_ADCCTRL0_ADCTUNERCCALMODE(self)
        self.zz_fdict['ADCTUNERCCALMODE'] = self.ADCTUNERCCALMODE
        self.ADCCAPRESET = RM_Field_RAC_S_ADCCTRL0_ADCCAPRESET(self)
        self.zz_fdict['ADCCAPRESET'] = self.ADCCAPRESET
        self.ADCCLKSEL = RM_Field_RAC_S_ADCCTRL0_ADCCLKSEL(self)
        self.zz_fdict['ADCCLKSEL'] = self.ADCCLKSEL
        self.ADCCTRLRESERVED = RM_Field_RAC_S_ADCCTRL0_ADCCTRLRESERVED(self)
        self.zz_fdict['ADCCTRLRESERVED'] = self.ADCCTRLRESERVED
        self.ADCINVERTCLK = RM_Field_RAC_S_ADCCTRL0_ADCINVERTCLK(self)
        self.zz_fdict['ADCINVERTCLK'] = self.ADCINVERTCLK
        self.ADCCTRLRESERVEDLV = RM_Field_RAC_S_ADCCTRL0_ADCCTRLRESERVEDLV(self)
        self.zz_fdict['ADCCTRLRESERVEDLV'] = self.ADCCTRLRESERVEDLV
        self.ADCZEROOPT = RM_Field_RAC_S_ADCCTRL0_ADCZEROOPT(self)
        self.zz_fdict['ADCZEROOPT'] = self.ADCZEROOPT
        self.ADCLOWCUR = RM_Field_RAC_S_ADCCTRL0_ADCLOWCUR(self)
        self.zz_fdict['ADCLOWCUR'] = self.ADCLOWCUR
        self.ADCNEGRESVCM = RM_Field_RAC_S_ADCCTRL0_ADCNEGRESVCM(self)
        self.zz_fdict['ADCNEGRESVCM'] = self.ADCNEGRESVCM
        self.ADCLDOSHUNTCURLVL2 = RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTCURLVL2(self)
        self.zz_fdict['ADCLDOSHUNTCURLVL2'] = self.ADCLDOSHUNTCURLVL2
        self.ADCNEGRESCURRENT = RM_Field_RAC_S_ADCCTRL0_ADCNEGRESCURRENT(self)
        self.zz_fdict['ADCNEGRESCURRENT'] = self.ADCNEGRESCURRENT
        self.ADCLDOSHUNTAMPLVL2 = RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTAMPLVL2(self)
        self.zz_fdict['ADCLDOSHUNTAMPLVL2'] = self.ADCLDOSHUNTAMPLVL2
        self.ADCLDOSHUNTAMPLVL1 = RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTAMPLVL1(self)
        self.zz_fdict['ADCLDOSHUNTAMPLVL1'] = self.ADCLDOSHUNTAMPLVL1
        self.ADCTUNERC = RM_Field_RAC_S_ADCCTRL0_ADCTUNERC(self)
        self.zz_fdict['ADCTUNERC'] = self.ADCTUNERC
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_ADCCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_ADCCTRL1, self).__init__(rmio, label,
            0xa0220000, 0x268,
            'ADCCTRL1', 'RAC_S.ADCCTRL1', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCENHALFBW = RM_Field_RAC_S_ADCCTRL1_ADCENHALFBW(self)
        self.zz_fdict['ADCENHALFBW'] = self.ADCENHALFBW
        self.ADCENHALFMODE = RM_Field_RAC_S_ADCCTRL1_ADCENHALFMODE(self)
        self.zz_fdict['ADCENHALFMODE'] = self.ADCENHALFMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_ADCEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_ADCEN0, self).__init__(rmio, label,
            0xa0220000, 0x26C,
            'ADCEN0', 'RAC_S.ADCEN0', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCENADC = RM_Field_RAC_S_ADCEN0_ADCENADC(self)
        self.zz_fdict['ADCENADC'] = self.ADCENADC
        self.ADCENRCCAL = RM_Field_RAC_S_ADCEN0_ADCENRCCAL(self)
        self.zz_fdict['ADCENRCCAL'] = self.ADCENRCCAL
        self.ADCENSIDETONE = RM_Field_RAC_S_ADCEN0_ADCENSIDETONE(self)
        self.zz_fdict['ADCENSIDETONE'] = self.ADCENSIDETONE
        self.ADCENLDOSHUNT = RM_Field_RAC_S_ADCEN0_ADCENLDOSHUNT(self)
        self.zz_fdict['ADCENLDOSHUNT'] = self.ADCENLDOSHUNT
        self.ADCENCLK = RM_Field_RAC_S_ADCEN0_ADCENCLK(self)
        self.zz_fdict['ADCENCLK'] = self.ADCENCLK
        self.ADCENLDOSERIES = RM_Field_RAC_S_ADCEN0_ADCENLDOSERIES(self)
        self.zz_fdict['ADCENLDOSERIES'] = self.ADCENLDOSERIES
        self.ADCENNEGRES = RM_Field_RAC_S_ADCEN0_ADCENNEGRES(self)
        self.zz_fdict['ADCENNEGRES'] = self.ADCENNEGRES
        self.ADCENLDOBIASSERIES = RM_Field_RAC_S_ADCEN0_ADCENLDOBIASSERIES(self)
        self.zz_fdict['ADCENLDOBIASSERIES'] = self.ADCENLDOBIASSERIES
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_ADCTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_ADCTRIM0, self).__init__(rmio, label,
            0xa0220000, 0x270,
            'ADCTRIM0', 'RAC_S.ADCTRIM0', 'read-write',
            u"",
            0x0034521C, 0x007FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCLDOSHUNTCURLVL1 = RM_Field_RAC_S_ADCTRIM0_ADCLDOSHUNTCURLVL1(self)
        self.zz_fdict['ADCLDOSHUNTCURLVL1'] = self.ADCLDOSHUNTCURLVL1
        self.ADCLDOSERIESAMPLVL = RM_Field_RAC_S_ADCTRIM0_ADCLDOSERIESAMPLVL(self)
        self.zz_fdict['ADCLDOSERIESAMPLVL'] = self.ADCLDOSERIESAMPLVL
        self.ADCLDOSERIESAMPLVL2 = RM_Field_RAC_S_ADCTRIM0_ADCLDOSERIESAMPLVL2(self)
        self.zz_fdict['ADCLDOSERIESAMPLVL2'] = self.ADCLDOSERIESAMPLVL2
        self.ADCSIDETONEFREQ = RM_Field_RAC_S_ADCTRIM0_ADCSIDETONEFREQ(self)
        self.zz_fdict['ADCSIDETONEFREQ'] = self.ADCSIDETONEFREQ
        self.ADCSIDETONEAMP = RM_Field_RAC_S_ADCTRIM0_ADCSIDETONEAMP(self)
        self.zz_fdict['ADCSIDETONEAMP'] = self.ADCSIDETONEAMP
        self.ADCREFBUFCURLVL = RM_Field_RAC_S_ADCTRIM0_ADCREFBUFCURLVL(self)
        self.zz_fdict['ADCREFBUFCURLVL'] = self.ADCREFBUFCURLVL
        self.ADCVCMLVL = RM_Field_RAC_S_ADCTRIM0_ADCVCMLVL(self)
        self.zz_fdict['ADCVCMLVL'] = self.ADCVCMLVL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_ADCCTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_ADCCTRL2, self).__init__(rmio, label,
            0xa0220000, 0x274,
            'ADCCTRL2', 'RAC_S.ADCCTRL2', 'read-write',
            u"",
            0x0000400C, 0x00007FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCOTACURRENT = RM_Field_RAC_S_ADCCTRL2_ADCOTACURRENT(self)
        self.zz_fdict['ADCOTACURRENT'] = self.ADCOTACURRENT
        self.ADCVCMBUFBYPASS = RM_Field_RAC_S_ADCCTRL2_ADCVCMBUFBYPASS(self)
        self.zz_fdict['ADCVCMBUFBYPASS'] = self.ADCVCMBUFBYPASS
        self.ADCRCCALCOUNTERSTARTVAL = RM_Field_RAC_S_ADCCTRL2_ADCRCCALCOUNTERSTARTVAL(self)
        self.zz_fdict['ADCRCCALCOUNTERSTARTVAL'] = self.ADCRCCALCOUNTERSTARTVAL
        self.ADCSHORTINPUT = RM_Field_RAC_S_ADCCTRL2_ADCSHORTINPUT(self)
        self.zz_fdict['ADCSHORTINPUT'] = self.ADCSHORTINPUT
        self.ADCLDOSERIESFORCEDSTARTUP = RM_Field_RAC_S_ADCCTRL2_ADCLDOSERIESFORCEDSTARTUP(self)
        self.zz_fdict['ADCLDOSERIESFORCEDSTARTUP'] = self.ADCLDOSERIESFORCEDSTARTUP
        self.ADCSETVINCM400M = RM_Field_RAC_S_ADCCTRL2_ADCSETVINCM400M(self)
        self.zz_fdict['ADCSETVINCM400M'] = self.ADCSETVINCM400M
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_LNAMIXEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_LNAMIXEN1, self).__init__(rmio, label,
            0xa0220000, 0x278,
            'LNAMIXEN1', 'RAC_S.LNAMIXEN1', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXDOUBLECUR1EN = RM_Field_RAC_S_LNAMIXEN1_LNAMIXDOUBLECUR1EN(self)
        self.zz_fdict['LNAMIXDOUBLECUR1EN'] = self.LNAMIXDOUBLECUR1EN
        self.LNAMIXMXRLOSEL = RM_Field_RAC_S_LNAMIXEN1_LNAMIXMXRLOSEL(self)
        self.zz_fdict['LNAMIXMXRLOSEL'] = self.LNAMIXMXRLOSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_LNAMIXCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_LNAMIXCTRL0, self).__init__(rmio, label,
            0xa0220000, 0x27C,
            'LNAMIXCTRL0', 'RAC_S.LNAMIXCTRL0', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXENSTBLOAD = RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXENSTBLOAD(self)
        self.zz_fdict['LNAMIXENSTBLOAD'] = self.LNAMIXENSTBLOAD
        self.LNAMIXREGLOWPWR = RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXREGLOWPWR(self)
        self.zz_fdict['LNAMIXREGLOWPWR'] = self.LNAMIXREGLOWPWR
        self.LNAMIXTXIRCALSEL = RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXTXIRCALSEL(self)
        self.zz_fdict['LNAMIXTXIRCALSEL'] = self.LNAMIXTXIRCALSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_LNAMIXCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_LNAMIXCTRL1, self).__init__(rmio, label,
            0xa0220000, 0x280,
            'LNAMIXCTRL1', 'RAC_S.LNAMIXCTRL1', 'read-write',
            u"",
            0x00000088, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXRFPKDTHRESHSELLO = RM_Field_RAC_S_LNAMIXCTRL1_LNAMIXRFPKDTHRESHSELLO(self)
        self.zz_fdict['LNAMIXRFPKDTHRESHSELLO'] = self.LNAMIXRFPKDTHRESHSELLO
        self.LNAMIXRFPKDTHRESHSELHI = RM_Field_RAC_S_LNAMIXCTRL1_LNAMIXRFPKDTHRESHSELHI(self)
        self.zz_fdict['LNAMIXRFPKDTHRESHSELHI'] = self.LNAMIXRFPKDTHRESHSELHI
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_PREREGEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_PREREGEN, self).__init__(rmio, label,
            0xa0220000, 0x284,
            'PREREGEN', 'RAC_S.PREREGEN', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGENSTBILOAD = RM_Field_RAC_S_PREREGEN_PREREGENSTBILOAD(self)
        self.zz_fdict['PREREGENSTBILOAD'] = self.PREREGENSTBILOAD
        self.PREREGENCALLOAD = RM_Field_RAC_S_PREREGEN_PREREGENCALLOAD(self)
        self.zz_fdict['PREREGENCALLOAD'] = self.PREREGENCALLOAD
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_PREDEBUG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_PREDEBUG, self).__init__(rmio, label,
            0xa0220000, 0x288,
            'PREDEBUG', 'RAC_S.PREDEBUG', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGSTARTUPFORCE = RM_Field_RAC_S_PREDEBUG_PREREGSTARTUPFORCE(self)
        self.zz_fdict['PREREGSTARTUPFORCE'] = self.PREREGSTARTUPFORCE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYDLFCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYDLFCTRL0, self).__init__(rmio, label,
            0xa0220000, 0x28C,
            'SYDLFCTRL0', 'RAC_S.SYDLFCTRL0', 'read-write',
            u"",
            0x00000007, 0x003FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFCLAMPTH = RM_Field_RAC_S_SYDLFCTRL0_SYDLFCLAMPTH(self)
        self.zz_fdict['SYDLFCLAMPTH'] = self.SYDLFCLAMPTH
        self.SYDLFTDCA2 = RM_Field_RAC_S_SYDLFCTRL0_SYDLFTDCA2(self)
        self.zz_fdict['SYDLFTDCA2'] = self.SYDLFTDCA2
        self.SYDLFLOCKTHRESHOLD = RM_Field_RAC_S_SYDLFCTRL0_SYDLFLOCKTHRESHOLD(self)
        self.zz_fdict['SYDLFLOCKTHRESHOLD'] = self.SYDLFLOCKTHRESHOLD
        self.SYDLFREADXI = RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADXI(self)
        self.zz_fdict['SYDLFREADXI'] = self.SYDLFREADXI
        self.SYDLFREADXF = RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADXF(self)
        self.zz_fdict['SYDLFREADXF'] = self.SYDLFREADXF
        self.SYDLFREADACAPCK2 = RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADACAPCK2(self)
        self.zz_fdict['SYDLFREADACAPCK2'] = self.SYDLFREADACAPCK2
        self.SYDLFPFDLOCKSAMPLETH = RM_Field_RAC_S_SYDLFCTRL0_SYDLFPFDLOCKSAMPLETH(self)
        self.zz_fdict['SYDLFPFDLOCKSAMPLETH'] = self.SYDLFPFDLOCKSAMPLETH
        self.SYDLFPOSITIVECOEFF = RM_Field_RAC_S_SYDLFCTRL0_SYDLFPOSITIVECOEFF(self)
        self.zz_fdict['SYDLFPOSITIVECOEFF'] = self.SYDLFPOSITIVECOEFF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYEN0, self).__init__(rmio, label,
            0xa0220000, 0x290,
            'SYEN0', 'RAC_S.SYEN0', 'read-write',
            u"",
            0x00000000, 0x00000013,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENDLFTDCA2 = RM_Field_RAC_S_SYEN0_SYENDLFTDCA2(self)
        self.zz_fdict['SYENDLFTDCA2'] = self.SYENDLFTDCA2
        self.SYENMMDCLKINJXO = RM_Field_RAC_S_SYEN0_SYENMMDCLKINJXO(self)
        self.zz_fdict['SYENMMDCLKINJXO'] = self.SYENMMDCLKINJXO
        self.SYENDLFTDCA2TX = RM_Field_RAC_S_SYEN0_SYENDLFTDCA2TX(self)
        self.zz_fdict['SYENDLFTDCA2TX'] = self.SYENDLFTDCA2TX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYEN1, self).__init__(rmio, label,
            0xa0220000, 0x294,
            'SYEN1', 'RAC_S.SYEN1', 'read-write',
            u"",
            0x00003000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENVCOREG = RM_Field_RAC_S_SYEN1_SYENVCOREG(self)
        self.zz_fdict['SYENVCOREG'] = self.SYENVCOREG
        self.SYENMMDREGSTBLOAD = RM_Field_RAC_S_SYEN1_SYENMMDREGSTBLOAD(self)
        self.zz_fdict['SYENMMDREGSTBLOAD'] = self.SYENMMDREGSTBLOAD
        self.SYENTDCREG = RM_Field_RAC_S_SYEN1_SYENTDCREG(self)
        self.zz_fdict['SYENTDCREG'] = self.SYENTDCREG
        self.SYENTDCREGSTBLOAD = RM_Field_RAC_S_SYEN1_SYENTDCREGSTBLOAD(self)
        self.zz_fdict['SYENTDCREGSTBLOAD'] = self.SYENTDCREGSTBLOAD
        self.SYENTDC = RM_Field_RAC_S_SYEN1_SYENTDC(self)
        self.zz_fdict['SYENTDC'] = self.SYENTDC
        self.SYENDLF = RM_Field_RAC_S_SYEN1_SYENDLF(self)
        self.zz_fdict['SYENDLF'] = self.SYENDLF
        self.SYENVCOIBIAS = RM_Field_RAC_S_SYEN1_SYENVCOIBIAS(self)
        self.zz_fdict['SYENVCOIBIAS'] = self.SYENVCOIBIAS
        self.SYENDSMDAC = RM_Field_RAC_S_SYEN1_SYENDSMDAC(self)
        self.zz_fdict['SYENDSMDAC'] = self.SYENDSMDAC
        self.SYENVCOBIAS = RM_Field_RAC_S_SYEN1_SYENVCOBIAS(self)
        self.zz_fdict['SYENVCOBIAS'] = self.SYENVCOBIAS
        self.SYENDSMDACREG = RM_Field_RAC_S_SYEN1_SYENDSMDACREG(self)
        self.zz_fdict['SYENDSMDACREG'] = self.SYENDSMDACREG
        self.SYENVCOREGLOAD = RM_Field_RAC_S_SYEN1_SYENVCOREGLOAD(self)
        self.zz_fdict['SYENVCOREGLOAD'] = self.SYENVCOREGLOAD
        self.SYENMMDREG = RM_Field_RAC_S_SYEN1_SYENMMDREG(self)
        self.zz_fdict['SYENMMDREG'] = self.SYENMMDREG
        self.SYENDTCCORE = RM_Field_RAC_S_SYEN1_SYENDTCCORE(self)
        self.zz_fdict['SYENDTCCORE'] = self.SYENDTCCORE
        self.SYENDTCREG = RM_Field_RAC_S_SYEN1_SYENDTCREG(self)
        self.zz_fdict['SYENDTCREG'] = self.SYENDTCREG
        self.SYENMMDOUTPUTS = RM_Field_RAC_S_SYEN1_SYENMMDOUTPUTS(self)
        self.zz_fdict['SYENMMDOUTPUTS'] = self.SYENMMDOUTPUTS
        self.SYENMMDREGBIAS = RM_Field_RAC_S_SYEN1_SYENMMDREGBIAS(self)
        self.zz_fdict['SYENMMDREGBIAS'] = self.SYENMMDREGBIAS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYEN2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYEN2, self).__init__(rmio, label,
            0xa0220000, 0x298,
            'SYEN2', 'RAC_S.SYEN2', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENTDCAQNC = RM_Field_RAC_S_SYEN2_SYENTDCAQNC(self)
        self.zz_fdict['SYENTDCAQNC'] = self.SYENTDCAQNC
        self.SELSYDTCRDACTRIM = RM_Field_RAC_S_SYEN2_SELSYDTCRDACTRIM(self)
        self.zz_fdict['SELSYDTCRDACTRIM'] = self.SELSYDTCRDACTRIM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYCTRL0, self).__init__(rmio, label,
            0xa0220000, 0x29C,
            'SYCTRL0', 'RAC_S.SYCTRL0', 'read-write',
            u"",
            0x00210049, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYVCOTRIMIPTAT = RM_Field_RAC_S_SYCTRL0_SYVCOTRIMIPTAT(self)
        self.zz_fdict['SYVCOTRIMIPTAT'] = self.SYVCOTRIMIPTAT
        self.SYENMMDREGREPLICA = RM_Field_RAC_S_SYCTRL0_SYENMMDREGREPLICA(self)
        self.zz_fdict['SYENMMDREGREPLICA'] = self.SYENMMDREGREPLICA
        self.SYDSMDACREGILOAD = RM_Field_RAC_S_SYCTRL0_SYDSMDACREGILOAD(self)
        self.zz_fdict['SYDSMDACREGILOAD'] = self.SYDSMDACREGILOAD
        self.SYDSMDACREGTRIMSTBLOAD = RM_Field_RAC_S_SYCTRL0_SYDSMDACREGTRIMSTBLOAD(self)
        self.zz_fdict['SYDSMDACREGTRIMSTBLOAD'] = self.SYDSMDACREGTRIMSTBLOAD
        self.SYENMMDSYNC = RM_Field_RAC_S_SYCTRL0_SYENMMDSYNC(self)
        self.zz_fdict['SYENMMDSYNC'] = self.SYENMMDSYNC
        self.SYVCOTRIMPKDAMP = RM_Field_RAC_S_SYCTRL0_SYVCOTRIMPKDAMP(self)
        self.zz_fdict['SYVCOTRIMPKDAMP'] = self.SYVCOTRIMPKDAMP
        self.SYVCOREGLOWCUR = RM_Field_RAC_S_SYCTRL0_SYVCOREGLOWCUR(self)
        self.zz_fdict['SYVCOREGLOWCUR'] = self.SYVCOREGLOWCUR
        self.SYENLODIVDIVSE = RM_Field_RAC_S_SYCTRL0_SYENLODIVDIVSE(self)
        self.zz_fdict['SYENLODIVDIVSE'] = self.SYENLODIVDIVSE
        self.SYENMMDAQNC = RM_Field_RAC_S_SYCTRL0_SYENMMDAQNC(self)
        self.zz_fdict['SYENMMDAQNC'] = self.SYENMMDAQNC
        self.SYVCOTRIMIBIAS = RM_Field_RAC_S_SYCTRL0_SYVCOTRIMIBIAS(self)
        self.zz_fdict['SYVCOTRIMIBIAS'] = self.SYVCOTRIMIBIAS
        self.SYDSMDACTRIMLOADBALDLF = RM_Field_RAC_S_SYCTRL0_SYDSMDACTRIMLOADBALDLF(self)
        self.zz_fdict['SYDSMDACTRIMLOADBALDLF'] = self.SYDSMDACTRIMLOADBALDLF
        self.SYDSMDACTRIMLOADBALDSM = RM_Field_RAC_S_SYCTRL0_SYDSMDACTRIMLOADBALDSM(self)
        self.zz_fdict['SYDSMDACTRIMLOADBALDSM'] = self.SYDSMDACTRIMLOADBALDSM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYLOEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYLOEN1, self).__init__(rmio, label,
            0xa0220000, 0x2A0,
            'SYLOEN1', 'RAC_S.SYLOEN1', 'read-write',
            u"",
            0x00000000, 0x0000010F,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENLODIVREGREPLICA = RM_Field_RAC_S_SYLOEN1_SYENLODIVREGREPLICA(self)
        self.zz_fdict['SYENLODIVREGREPLICA'] = self.SYENLODIVREGREPLICA
        self.SYENLODIVREGBIAS = RM_Field_RAC_S_SYLOEN1_SYENLODIVREGBIAS(self)
        self.zz_fdict['SYENLODIVREGBIAS'] = self.SYENLODIVREGBIAS
        self.SYENLODIVREG = RM_Field_RAC_S_SYLOEN1_SYENLODIVREG(self)
        self.zz_fdict['SYENLODIVREG'] = self.SYENLODIVREG
        self.SYENLODIVREGSTBLOAD = RM_Field_RAC_S_SYLOEN1_SYENLODIVREGSTBLOAD(self)
        self.zz_fdict['SYENLODIVREGSTBLOAD'] = self.SYENLODIVREGSTBLOAD
        self.SYENLODIVREGREPLICATX = RM_Field_RAC_S_SYLOEN1_SYENLODIVREGREPLICATX(self)
        self.zz_fdict['SYENLODIVREGREPLICATX'] = self.SYENLODIVREGREPLICATX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYLOEN2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYLOEN2, self).__init__(rmio, label,
            0xa0220000, 0x2A4,
            'SYLOEN2', 'RAC_S.SYLOEN2', 'read-write',
            u"",
            0x00000000, 0x00000011,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENLODIVADCCLK = RM_Field_RAC_S_SYLOEN2_SYENLODIVADCCLK(self)
        self.zz_fdict['SYENLODIVADCCLK'] = self.SYENLODIVADCCLK
        self.SYENLODIVADCCLKTX = RM_Field_RAC_S_SYLOEN2_SYENLODIVADCCLKTX(self)
        self.zz_fdict['SYENLODIVADCCLKTX'] = self.SYENLODIVADCCLKTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYLOCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYLOCTRL0, self).__init__(rmio, label,
            0xa0220000, 0x2A8,
            'SYLOCTRL0', 'RAC_S.SYLOCTRL0', 'read-write',
            u"",
            0x00000000, 0x1FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYLODIVSELFPSRC2G4 = RM_Field_RAC_S_SYLOCTRL0_SYLODIVSELFPSRC2G4(self)
        self.zz_fdict['SYLODIVSELFPSRC2G4'] = self.SYLODIVSELFPSRC2G4
        self.SYLODIVBYPASSIQCLKBIASDELTA = RM_Field_RAC_S_SYLOCTRL0_SYLODIVBYPASSIQCLKBIASDELTA(self)
        self.zz_fdict['SYLODIVBYPASSIQCLKBIASDELTA'] = self.SYLODIVBYPASSIQCLKBIASDELTA
        self.SYLODIVSELFCALCLK = RM_Field_RAC_S_SYLOCTRL0_SYLODIVSELFCALCLK(self)
        self.zz_fdict['SYLODIVSELFCALCLK'] = self.SYLODIVSELFCALCLK
        self.SYLODIVTRIMIQCLKBIASDELTA = RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASDELTA(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASDELTA'] = self.SYLODIVTRIMIQCLKBIASDELTA
        self.SYLODIVDSMDACCLKDIVRATIO = RM_Field_RAC_S_SYLOCTRL0_SYLODIVDSMDACCLKDIVRATIO(self)
        self.zz_fdict['SYLODIVDSMDACCLKDIVRATIO'] = self.SYLODIVDSMDACCLKDIVRATIO
        self.SYLODIVSPARES = RM_Field_RAC_S_SYLOCTRL0_SYLODIVSPARES(self)
        self.zz_fdict['SYLODIVSPARES'] = self.SYLODIVSPARES
        self.SYLODIVSMUXCLKDIVRATIO = RM_Field_RAC_S_SYLOCTRL0_SYLODIVSMUXCLKDIVRATIO(self)
        self.zz_fdict['SYLODIVSMUXCLKDIVRATIO'] = self.SYLODIVSMUXCLKDIVRATIO
        self.SYLODIVTRIMIQCLKBIASNDIO = RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASNDIO(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASNDIO'] = self.SYLODIVTRIMIQCLKBIASNDIO
        self.SYLODIVTRIMIQCLKBIASIBIAS = RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASIBIAS(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASIBIAS'] = self.SYLODIVTRIMIQCLKBIASIBIAS
        self.SYLODIVADCDIVRATIO = RM_Field_RAC_S_SYLOCTRL0_SYLODIVADCDIVRATIO(self)
        self.zz_fdict['SYLODIVADCDIVRATIO'] = self.SYLODIVADCDIVRATIO
        self.SYLODIVREGTRIMVREG = RM_Field_RAC_S_SYLOCTRL0_SYLODIVREGTRIMVREG(self)
        self.zz_fdict['SYLODIVREGTRIMVREG'] = self.SYLODIVREGTRIMVREG
        self.SYLODIVREGTRIMVREGTX = RM_Field_RAC_S_SYLOCTRL0_SYLODIVREGTRIMVREGTX(self)
        self.zz_fdict['SYLODIVREGTRIMVREGTX'] = self.SYLODIVREGTRIMVREGTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYLOCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYLOCTRL1, self).__init__(rmio, label,
            0xa0220000, 0x2AC,
            'SYLOCTRL1', 'RAC_S.SYLOCTRL1', 'read-write',
            u"",
            0x00000000, 0x000003FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENLODIVHADMDIV = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMDIV(self)
        self.zz_fdict['SYENLODIVHADMDIV'] = self.SYENLODIVHADMDIV
        self.SYENLODIVHADMLO = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMLO(self)
        self.zz_fdict['SYENLODIVHADMLO'] = self.SYENLODIVHADMLO
        self.SYENLODIVHADMRXLO = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMRXLO(self)
        self.zz_fdict['SYENLODIVHADMRXLO'] = self.SYENLODIVHADMRXLO
        self.SYENLODIVHADMTXLO = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMTXLO(self)
        self.zz_fdict['SYENLODIVHADMTXLO'] = self.SYENLODIVHADMTXLO
        self.SYENLODIVLPRXLO = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVLPRXLO(self)
        self.zz_fdict['SYENLODIVLPRXLO'] = self.SYENLODIVLPRXLO
        self.SYENLODIVLPRXDIV = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVLPRXDIV(self)
        self.zz_fdict['SYENLODIVLPRXDIV'] = self.SYENLODIVLPRXDIV
        self.SYENLODIVIQCLKBIAS = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVIQCLKBIAS(self)
        self.zz_fdict['SYENLODIVIQCLKBIAS'] = self.SYENLODIVIQCLKBIAS
        self.SYENLODIVSECLKBIAS = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVSECLKBIAS(self)
        self.zz_fdict['SYENLODIVSECLKBIAS'] = self.SYENLODIVSECLKBIAS
        self.SYENLODIVSMUXCLK = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVSMUXCLK(self)
        self.zz_fdict['SYENLODIVSMUXCLK'] = self.SYENLODIVSMUXCLK
        self.SYENLODIVTXRF0DBM = RM_Field_RAC_S_SYLOCTRL1_SYENLODIVTXRF0DBM(self)
        self.zz_fdict['SYENLODIVTXRF0DBM'] = self.SYENLODIVTXRF0DBM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYLOTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYLOTRIM0, self).__init__(rmio, label,
            0xa0220000, 0x2B0,
            'SYLOTRIM0', 'RAC_S.SYLOTRIM0', 'read-write',
            u"",
            0x00000000, 0x0000001F,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYLODIVREGTRIMVREF = RM_Field_RAC_S_SYLOTRIM0_SYLODIVREGTRIMVREF(self)
        self.zz_fdict['SYLODIVREGTRIMVREF'] = self.SYLODIVREGTRIMVREF
        self.SYLODIVREGTRIMVREGOFFS = RM_Field_RAC_S_SYLOTRIM0_SYLODIVREGTRIMVREGOFFS(self)
        self.zz_fdict['SYLODIVREGTRIMVREGOFFS'] = self.SYLODIVREGTRIMVREGOFFS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYTRIM3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYTRIM3, self).__init__(rmio, label,
            0xa0220000, 0x2B4,
            'SYTRIM3', 'RAC_S.SYTRIM3', 'read-write',
            u"",
            0x009866E8, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYVCOREGTRIMVREF = RM_Field_RAC_S_SYTRIM3_SYVCOREGTRIMVREF(self)
        self.zz_fdict['SYVCOREGTRIMVREF'] = self.SYVCOREGTRIMVREF
        self.SYVCOTRIMR = RM_Field_RAC_S_SYTRIM3_SYVCOTRIMR(self)
        self.zz_fdict['SYVCOTRIMR'] = self.SYVCOTRIMR
        self.SYVCOREGTRIMVREG = RM_Field_RAC_S_SYTRIM3_SYVCOREGTRIMVREG(self)
        self.zz_fdict['SYVCOREGTRIMVREG'] = self.SYVCOREGTRIMVREG
        self.SYVCOTRIMBIASVREF = RM_Field_RAC_S_SYTRIM3_SYVCOTRIMBIASVREF(self)
        self.zz_fdict['SYVCOTRIMBIASVREF'] = self.SYVCOTRIMBIASVREF
        self.SYTDCREGTRIMBW = RM_Field_RAC_S_SYTRIM3_SYTDCREGTRIMBW(self)
        self.zz_fdict['SYTDCREGTRIMBW'] = self.SYTDCREGTRIMBW
        self.SYDTCSPARES = RM_Field_RAC_S_SYTRIM3_SYDTCSPARES(self)
        self.zz_fdict['SYDTCSPARES'] = self.SYDTCSPARES
        self.SYTDCREGTRIMVREG = RM_Field_RAC_S_SYTRIM3_SYTDCREGTRIMVREG(self)
        self.zz_fdict['SYTDCREGTRIMVREG'] = self.SYTDCREGTRIMVREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TIACTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TIACTRL0, self).__init__(rmio, label,
            0xa0220000, 0x2B8,
            'TIACTRL0', 'RAC_S.TIACTRL0', 'read-write',
            u"",
            0x00007000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIAOXI = RM_Field_RAC_S_TIACTRL0_TIAOXI(self)
        self.zz_fdict['TIAOXI'] = self.TIAOXI
        self.TIAOXQ = RM_Field_RAC_S_TIACTRL0_TIAOXQ(self)
        self.zz_fdict['TIAOXQ'] = self.TIAOXQ
        self.TIASETVCM = RM_Field_RAC_S_TIACTRL0_TIASETVCM(self)
        self.zz_fdict['TIASETVCM'] = self.TIASETVCM
        self.TIATHRPKDLOSEL = RM_Field_RAC_S_TIACTRL0_TIATHRPKDLOSEL(self)
        self.zz_fdict['TIATHRPKDLOSEL'] = self.TIATHRPKDLOSEL
        self.TIATHRPKDHISEL = RM_Field_RAC_S_TIACTRL0_TIATHRPKDHISEL(self)
        self.zz_fdict['TIATHRPKDHISEL'] = self.TIATHRPKDHISEL
        self.TIARESFB = RM_Field_RAC_S_TIACTRL0_TIARESFB(self)
        self.zz_fdict['TIARESFB'] = self.TIARESFB
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TIACTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TIACTRL1, self).__init__(rmio, label,
            0xa0220000, 0x2BC,
            'TIACTRL1', 'RAC_S.TIACTRL1', 'read-write',
            u"",
            0x00000000, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIACAPFB = RM_Field_RAC_S_TIACTRL1_TIACAPFB(self)
        self.zz_fdict['TIACAPFB'] = self.TIACAPFB
        self.TIACOMP = RM_Field_RAC_S_TIACTRL1_TIACOMP(self)
        self.zz_fdict['TIACOMP'] = self.TIACOMP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX10DBMCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX10DBMCTRL1, self).__init__(rmio, label,
            0xa0220000, 0x2C0,
            'TX10DBMCTRL1', 'RAC_S.TX10DBMCTRL1', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMRXPADATTN = RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMRXPADATTN(self)
        self.zz_fdict['TX10DBMRXPADATTN'] = self.TX10DBMRXPADATTN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_TX10DBMTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_TX10DBMTRIM0, self).__init__(rmio, label,
            0xa0220000, 0x2C4,
            'TX10DBMTRIM0', 'RAC_S.TX10DBMTRIM0', 'read-write',
            u"",
            0x000000AA, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMTRIMHFCTAP = RM_Field_RAC_S_TX10DBMTRIM0_TX10DBMTRIMHFCTAP(self)
        self.zz_fdict['TX10DBMTRIMHFCTAP'] = self.TX10DBMTRIMHFCTAP
        self.TX10DBMTRIMHFCTAPTX = RM_Field_RAC_S_TX10DBMTRIM0_TX10DBMTRIMHFCTAPTX(self)
        self.zz_fdict['TX10DBMTRIMHFCTAPTX'] = self.TX10DBMTRIMHFCTAPTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYCTRLTX0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYCTRLTX0, self).__init__(rmio, label,
            0xa0220000, 0x2C8,
            'SYCTRLTX0', 'RAC_S.SYCTRLTX0', 'read-write',
            u"",
            0x00200049, 0x3FF81FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYVCOTRIMIPTATTX = RM_Field_RAC_S_SYCTRLTX0_SYVCOTRIMIPTATTX(self)
        self.zz_fdict['SYVCOTRIMIPTATTX'] = self.SYVCOTRIMIPTATTX
        self.SYENMMDREGREPLICATX = RM_Field_RAC_S_SYCTRLTX0_SYENMMDREGREPLICATX(self)
        self.zz_fdict['SYENMMDREGREPLICATX'] = self.SYENMMDREGREPLICATX
        self.SYDSMDACREGILOADTX = RM_Field_RAC_S_SYCTRLTX0_SYDSMDACREGILOADTX(self)
        self.zz_fdict['SYDSMDACREGILOADTX'] = self.SYDSMDACREGILOADTX
        self.SYDSMDACREGTRIMSTBLOADTX = RM_Field_RAC_S_SYCTRLTX0_SYDSMDACREGTRIMSTBLOADTX(self)
        self.zz_fdict['SYDSMDACREGTRIMSTBLOADTX'] = self.SYDSMDACREGTRIMSTBLOADTX
        self.SYENMMDSYNCTX = RM_Field_RAC_S_SYCTRLTX0_SYENMMDSYNCTX(self)
        self.zz_fdict['SYENMMDSYNCTX'] = self.SYENMMDSYNCTX
        self.SYENMMDAQNCTX = RM_Field_RAC_S_SYCTRLTX0_SYENMMDAQNCTX(self)
        self.zz_fdict['SYENMMDAQNCTX'] = self.SYENMMDAQNCTX
        self.SYVCOTRIMIBIASTX = RM_Field_RAC_S_SYCTRLTX0_SYVCOTRIMIBIASTX(self)
        self.zz_fdict['SYVCOTRIMIBIASTX'] = self.SYVCOTRIMIBIASTX
        self.SYDSMDACTRIMLOADBALDLFTX = RM_Field_RAC_S_SYCTRLTX0_SYDSMDACTRIMLOADBALDLFTX(self)
        self.zz_fdict['SYDSMDACTRIMLOADBALDLFTX'] = self.SYDSMDACTRIMLOADBALDLFTX
        self.SYDSMDACTRIMLOADBALDSMTX = RM_Field_RAC_S_SYCTRLTX0_SYDSMDACTRIMLOADBALDSMTX(self)
        self.zz_fdict['SYDSMDACTRIMLOADBALDSMTX'] = self.SYDSMDACTRIMLOADBALDSMTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYLOCTRLTX0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYLOCTRLTX0, self).__init__(rmio, label,
            0xa0220000, 0x2CC,
            'SYLOCTRLTX0', 'RAC_S.SYLOCTRLTX0', 'read-write',
            u"",
            0x00000000, 0x007FE1FB,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYLODIVSELFPSRC2G4TX = RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVSELFPSRC2G4TX(self)
        self.zz_fdict['SYLODIVSELFPSRC2G4TX'] = self.SYLODIVSELFPSRC2G4TX
        self.SYLODIVBYPASSIQCLKBIASDELTATX = RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVBYPASSIQCLKBIASDELTATX(self)
        self.zz_fdict['SYLODIVBYPASSIQCLKBIASDELTATX'] = self.SYLODIVBYPASSIQCLKBIASDELTATX
        self.SYLODIVTRIMIQCLKBIASDELTATX = RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASDELTATX(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASDELTATX'] = self.SYLODIVTRIMIQCLKBIASDELTATX
        self.SYLODIVDSMDACCLKDIVRATIOTX = RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVDSMDACCLKDIVRATIOTX(self)
        self.zz_fdict['SYLODIVDSMDACCLKDIVRATIOTX'] = self.SYLODIVDSMDACCLKDIVRATIOTX
        self.SYLODIVSMUXCLKDIVRATIOTX = RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVSMUXCLKDIVRATIOTX(self)
        self.zz_fdict['SYLODIVSMUXCLKDIVRATIOTX'] = self.SYLODIVSMUXCLKDIVRATIOTX
        self.SYLODIVTRIMIQCLKBIASNDIOTX = RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASNDIOTX(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASNDIOTX'] = self.SYLODIVTRIMIQCLKBIASNDIOTX
        self.SYLODIVTRIMIQCLKBIASIBIASTX = RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASIBIASTX(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASIBIASTX'] = self.SYLODIVTRIMIQCLKBIASIBIASTX
        self.SYLODIVADCDIVRATIOTX = RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVADCDIVRATIOTX(self)
        self.zz_fdict['SYLODIVADCDIVRATIOTX'] = self.SYLODIVADCDIVRATIOTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SYLOCTRLTX1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SYLOCTRLTX1, self).__init__(rmio, label,
            0xa0220000, 0x2D0,
            'SYLOCTRLTX1', 'RAC_S.SYLOCTRLTX1', 'read-write',
            u"",
            0x00000000, 0x0000037F,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENLODIVHADMDIVTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMDIVTX(self)
        self.zz_fdict['SYENLODIVHADMDIVTX'] = self.SYENLODIVHADMDIVTX
        self.SYENLODIVHADMLOTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMLOTX(self)
        self.zz_fdict['SYENLODIVHADMLOTX'] = self.SYENLODIVHADMLOTX
        self.SYENLODIVHADMRXLOTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMRXLOTX(self)
        self.zz_fdict['SYENLODIVHADMRXLOTX'] = self.SYENLODIVHADMRXLOTX
        self.SYENLODIVHADMTXLOTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMTXLOTX(self)
        self.zz_fdict['SYENLODIVHADMTXLOTX'] = self.SYENLODIVHADMTXLOTX
        self.SYENLODIVLPRXLOTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVLPRXLOTX(self)
        self.zz_fdict['SYENLODIVLPRXLOTX'] = self.SYENLODIVLPRXLOTX
        self.SYENLODIVLPRXDIVTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVLPRXDIVTX(self)
        self.zz_fdict['SYENLODIVLPRXDIVTX'] = self.SYENLODIVLPRXDIVTX
        self.SYENLODIVIQCLKBIASTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVIQCLKBIASTX(self)
        self.zz_fdict['SYENLODIVIQCLKBIASTX'] = self.SYENLODIVIQCLKBIASTX
        self.SYENLODIVSMUXCLKTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVSMUXCLKTX(self)
        self.zz_fdict['SYENLODIVSMUXCLKTX'] = self.SYENLODIVSMUXCLKTX
        self.SYENLODIVTXRF0DBMTX = RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVTXRF0DBMTX(self)
        self.zz_fdict['SYENLODIVTXRF0DBMTX'] = self.SYENLODIVTXRF0DBMTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_CLKMULTEN2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_CLKMULTEN2, self).__init__(rmio, label,
            0xa0220000, 0x2D4,
            'CLKMULTEN2', 'RAC_S.CLKMULTEN2', 'read-write',
            u"",
            0x00000180, 0x00007FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTENBYPASS40MHZTX = RM_Field_RAC_S_CLKMULTEN2_CLKMULTENBYPASS40MHZTX(self)
        self.zz_fdict['CLKMULTENBYPASS40MHZTX'] = self.CLKMULTENBYPASS40MHZTX
        self.CLKMULTDIVNTX = RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVNTX(self)
        self.zz_fdict['CLKMULTDIVNTX'] = self.CLKMULTDIVNTX
        self.CLKMULTDIVRTX = RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVRTX(self)
        self.zz_fdict['CLKMULTDIVRTX'] = self.CLKMULTDIVRTX
        self.CLKMULTDIVXTX = RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVXTX(self)
        self.zz_fdict['CLKMULTDIVXTX'] = self.CLKMULTDIVXTX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SCRATCH0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SCRATCH0, self).__init__(rmio, label,
            0xa0220000, 0x3E0,
            'SCRATCH0', 'RAC_S.SCRATCH0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH0 = RM_Field_RAC_S_SCRATCH0_SCRATCH0(self)
        self.zz_fdict['SCRATCH0'] = self.SCRATCH0
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SCRATCH1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SCRATCH1, self).__init__(rmio, label,
            0xa0220000, 0x3E4,
            'SCRATCH1', 'RAC_S.SCRATCH1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH1 = RM_Field_RAC_S_SCRATCH1_SCRATCH1(self)
        self.zz_fdict['SCRATCH1'] = self.SCRATCH1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SCRATCH2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SCRATCH2, self).__init__(rmio, label,
            0xa0220000, 0x3E8,
            'SCRATCH2', 'RAC_S.SCRATCH2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH2 = RM_Field_RAC_S_SCRATCH2_SCRATCH2(self)
        self.zz_fdict['SCRATCH2'] = self.SCRATCH2
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SCRATCH3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SCRATCH3, self).__init__(rmio, label,
            0xa0220000, 0x3EC,
            'SCRATCH3', 'RAC_S.SCRATCH3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH3 = RM_Field_RAC_S_SCRATCH3_SCRATCH3(self)
        self.zz_fdict['SCRATCH3'] = self.SCRATCH3
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SCRATCH4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SCRATCH4, self).__init__(rmio, label,
            0xa0220000, 0x3F0,
            'SCRATCH4', 'RAC_S.SCRATCH4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH4 = RM_Field_RAC_S_SCRATCH4_SCRATCH4(self)
        self.zz_fdict['SCRATCH4'] = self.SCRATCH4
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SCRATCH5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SCRATCH5, self).__init__(rmio, label,
            0xa0220000, 0x3F4,
            'SCRATCH5', 'RAC_S.SCRATCH5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH5 = RM_Field_RAC_S_SCRATCH5_SCRATCH5(self)
        self.zz_fdict['SCRATCH5'] = self.SCRATCH5
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SCRATCH6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SCRATCH6, self).__init__(rmio, label,
            0xa0220000, 0x3F8,
            'SCRATCH6', 'RAC_S.SCRATCH6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH6 = RM_Field_RAC_S_SCRATCH6_SCRATCH6(self)
        self.zz_fdict['SCRATCH6'] = self.SCRATCH6
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_SCRATCH7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_SCRATCH7, self).__init__(rmio, label,
            0xa0220000, 0x3FC,
            'SCRATCH7', 'RAC_S.SCRATCH7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCRATCH7 = RM_Field_RAC_S_SCRATCH7_SCRATCH7(self)
        self.zz_fdict['SCRATCH7'] = self.SCRATCH7
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_FSWCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_FSWCTRL, self).__init__(rmio, label,
            0xa0220000, 0x600,
            'FSWCTRL', 'RAC_S.FSWCTRL', 'read-write',
            u"",
            0x00000001, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.FSWRISCVCLKDIS = RM_Field_RAC_S_FSWCTRL_FSWRISCVCLKDIS(self)
        self.zz_fdict['FSWRISCVCLKDIS'] = self.FSWRISCVCLKDIS
        self.FSWRISCVRESET = RM_Field_RAC_S_FSWCTRL_FSWRISCVRESET(self)
        self.zz_fdict['FSWRISCVRESET'] = self.FSWRISCVRESET
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_THMSW(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_THMSW, self).__init__(rmio, label,
            0xa0220000, 0x7E8,
            'THMSW', 'RAC_S.THMSW', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_RAC_S_THMSW_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.HALFSWITCH = RM_Field_RAC_S_THMSW_HALFSWITCH(self)
        self.zz_fdict['HALFSWITCH'] = self.HALFSWITCH
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_DIAGAALTEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_DIAGAALTEN, self).__init__(rmio, label,
            0xa0220000, 0x7EC,
            'DIAGAALTEN', 'RAC_S.DIAGAALTEN', 'read-write',
            u"",
            0x00000000, 0x00000002,
            0x00001000, 0x00002000,
            0x00003000)

        self.RFEN = RM_Field_RAC_S_DIAGAALTEN_RFEN(self)
        self.zz_fdict['RFEN'] = self.RFEN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_DIAGAALTSEL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_DIAGAALTSEL, self).__init__(rmio, label,
            0xa0220000, 0x7F0,
            'DIAGAALTSEL', 'RAC_S.DIAGAALTSEL', 'read-write',
            u"",
            0x00000000, 0x00007F3F,
            0x00001000, 0x00002000,
            0x00003000)

        self.TP = RM_Field_RAC_S_DIAGAALTSEL_TP(self)
        self.zz_fdict['TP'] = self.TP
        self.BLK = RM_Field_RAC_S_DIAGAALTSEL_BLK(self)
        self.zz_fdict['BLK'] = self.BLK
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_DIAGAALTBRIDGECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_DIAGAALTBRIDGECTRL, self).__init__(rmio, label,
            0xa0220000, 0x7F4,
            'DIAGAALTBRIDGECTRL', 'RAC_S.DIAGAALTBRIDGECTRL', 'read-write',
            u"",
            0x00000000, 0x00000020,
            0x00001000, 0x00002000,
            0x00003000)

        self.RFSHORTDIS = RM_Field_RAC_S_DIAGAALTBRIDGECTRL_RFSHORTDIS(self)
        self.zz_fdict['RFSHORTDIS'] = self.RFSHORTDIS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RFLOCK0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RFLOCK0, self).__init__(rmio, label,
            0xa0220000, 0x7F8,
            'RFLOCK0', 'RAC_S.RFLOCK0', 'read-write',
            u"",
            0x80000000, 0xF7E003FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNTHLODIVFREQCTRL = RM_Field_RAC_S_RFLOCK0_SYNTHLODIVFREQCTRL(self)
        self.zz_fdict['SYNTHLODIVFREQCTRL'] = self.SYNTHLODIVFREQCTRL
        self.MODEMHADM = RM_Field_RAC_S_RFLOCK0_MODEMHADM(self)
        self.zz_fdict['MODEMHADM'] = self.MODEMHADM
        self.FRCCONVMODE = RM_Field_RAC_S_RFLOCK0_FRCCONVMODE(self)
        self.zz_fdict['FRCCONVMODE'] = self.FRCCONVMODE
        self.FRCPAUSING = RM_Field_RAC_S_RFLOCK0_FRCPAUSING(self)
        self.zz_fdict['FRCPAUSING'] = self.FRCPAUSING
        self.MODEMANTSWENABLE = RM_Field_RAC_S_RFLOCK0_MODEMANTSWENABLE(self)
        self.zz_fdict['MODEMANTSWENABLE'] = self.MODEMANTSWENABLE
        self.MODEMLRBLE = RM_Field_RAC_S_RFLOCK0_MODEMLRBLE(self)
        self.zz_fdict['MODEMLRBLE'] = self.MODEMLRBLE
        self.MODEMDSSS = RM_Field_RAC_S_RFLOCK0_MODEMDSSS(self)
        self.zz_fdict['MODEMDSSS'] = self.MODEMDSSS
        self.MODEMMODFORMAT = RM_Field_RAC_S_RFLOCK0_MODEMMODFORMAT(self)
        self.zz_fdict['MODEMMODFORMAT'] = self.MODEMMODFORMAT
        self.MODEMDUALSYNC = RM_Field_RAC_S_RFLOCK0_MODEMDUALSYNC(self)
        self.zz_fdict['MODEMDUALSYNC'] = self.MODEMDUALSYNC
        self.MODEMANTDIVMODE = RM_Field_RAC_S_RFLOCK0_MODEMANTDIVMODE(self)
        self.zz_fdict['MODEMANTDIVMODE'] = self.MODEMANTDIVMODE
        self.UNLOCKED = RM_Field_RAC_S_RFLOCK0_UNLOCKED(self)
        self.zz_fdict['UNLOCKED'] = self.UNLOCKED
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_S_RFLOCK1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_S_RFLOCK1, self).__init__(rmio, label,
            0xa0220000, 0x7FC,
            'RFLOCK1', 'RAC_S.RFLOCK1', 'read-write',
            u"",
            0x000FFFFF, 0x000FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RACPASTRIPE = RM_Field_RAC_S_RFLOCK1_RACPASTRIPE(self)
        self.zz_fdict['RACPASTRIPE'] = self.RACPASTRIPE
        self.RACPASLICE = RM_Field_RAC_S_RFLOCK1_RACPASLICE(self)
        self.zz_fdict['RACPASLICE'] = self.RACPASLICE
        self.TX0DBMPOWERLIMIT = RM_Field_RAC_S_RFLOCK1_TX0DBMPOWERLIMIT(self)
        self.zz_fdict['TX0DBMPOWERLIMIT'] = self.TX0DBMPOWERLIMIT
        self.TX10DBMPOWERLIMIT = RM_Field_RAC_S_RFLOCK1_TX10DBMPOWERLIMIT(self)
        self.zz_fdict['TX10DBMPOWERLIMIT'] = self.TX10DBMPOWERLIMIT
        self.__dict__['zz_frozen'] = True



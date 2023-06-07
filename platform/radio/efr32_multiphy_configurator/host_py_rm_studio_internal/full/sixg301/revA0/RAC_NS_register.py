
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
            0x00000003, 0xFFFFFFFF,
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

        self.STATECHANGESEQIF = RM_Field_RAC_NS_SEQIF_STATECHANGESEQIF(self)
        self.zz_fdict['STATECHANGESEQIF'] = self.STATECHANGESEQIF
        self.STIMCMPEVSEQIF = RM_Field_RAC_NS_SEQIF_STIMCMPEVSEQIF(self)
        self.zz_fdict['STIMCMPEVSEQIF'] = self.STIMCMPEVSEQIF
        self.DEMODRXREQCLRSEQIF = RM_Field_RAC_NS_SEQIF_DEMODRXREQCLRSEQIF(self)
        self.zz_fdict['DEMODRXREQCLRSEQIF'] = self.DEMODRXREQCLRSEQIF
        self.PRSEVENTSEQIF = RM_Field_RAC_NS_SEQIF_PRSEVENTSEQIF(self)
        self.zz_fdict['PRSEVENTSEQIF'] = self.PRSEVENTSEQIF
        self.STATEOFFIF = RM_Field_RAC_NS_SEQIF_STATEOFFIF(self)
        self.zz_fdict['STATEOFFIF'] = self.STATEOFFIF
        self.STATERXWARMIF = RM_Field_RAC_NS_SEQIF_STATERXWARMIF(self)
        self.zz_fdict['STATERXWARMIF'] = self.STATERXWARMIF
        self.STATERXSEARCHIF = RM_Field_RAC_NS_SEQIF_STATERXSEARCHIF(self)
        self.zz_fdict['STATERXSEARCHIF'] = self.STATERXSEARCHIF
        self.STATERXFRAMEIF = RM_Field_RAC_NS_SEQIF_STATERXFRAMEIF(self)
        self.zz_fdict['STATERXFRAMEIF'] = self.STATERXFRAMEIF
        self.STATERXPDIF = RM_Field_RAC_NS_SEQIF_STATERXPDIF(self)
        self.zz_fdict['STATERXPDIF'] = self.STATERXPDIF
        self.STATERX2RXIF = RM_Field_RAC_NS_SEQIF_STATERX2RXIF(self)
        self.zz_fdict['STATERX2RXIF'] = self.STATERX2RXIF
        self.STATERXOVERFLOWIF = RM_Field_RAC_NS_SEQIF_STATERXOVERFLOWIF(self)
        self.zz_fdict['STATERXOVERFLOWIF'] = self.STATERXOVERFLOWIF
        self.STATERX2TXIF = RM_Field_RAC_NS_SEQIF_STATERX2TXIF(self)
        self.zz_fdict['STATERX2TXIF'] = self.STATERX2TXIF
        self.STATETXWARMIF = RM_Field_RAC_NS_SEQIF_STATETXWARMIF(self)
        self.zz_fdict['STATETXWARMIF'] = self.STATETXWARMIF
        self.STATETXIF = RM_Field_RAC_NS_SEQIF_STATETXIF(self)
        self.zz_fdict['STATETXIF'] = self.STATETXIF
        self.STATETXPDIF = RM_Field_RAC_NS_SEQIF_STATETXPDIF(self)
        self.zz_fdict['STATETXPDIF'] = self.STATETXPDIF
        self.STATETX2RXIF = RM_Field_RAC_NS_SEQIF_STATETX2RXIF(self)
        self.zz_fdict['STATETX2RXIF'] = self.STATETX2RXIF
        self.STATETX2TXIF = RM_Field_RAC_NS_SEQIF_STATETX2TXIF(self)
        self.zz_fdict['STATETX2TXIF'] = self.STATETX2TXIF
        self.STATESHUTDOWNIF = RM_Field_RAC_NS_SEQIF_STATESHUTDOWNIF(self)
        self.zz_fdict['STATESHUTDOWNIF'] = self.STATESHUTDOWNIF
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

        self.STATECHANGESEQIEN = RM_Field_RAC_NS_SEQIEN_STATECHANGESEQIEN(self)
        self.zz_fdict['STATECHANGESEQIEN'] = self.STATECHANGESEQIEN
        self.STIMCMPEVSEQIEN = RM_Field_RAC_NS_SEQIEN_STIMCMPEVSEQIEN(self)
        self.zz_fdict['STIMCMPEVSEQIEN'] = self.STIMCMPEVSEQIEN
        self.DEMODRXREQCLRSEQIEN = RM_Field_RAC_NS_SEQIEN_DEMODRXREQCLRSEQIEN(self)
        self.zz_fdict['DEMODRXREQCLRSEQIEN'] = self.DEMODRXREQCLRSEQIEN
        self.PRSEVENTSEQIEN = RM_Field_RAC_NS_SEQIEN_PRSEVENTSEQIEN(self)
        self.zz_fdict['PRSEVENTSEQIEN'] = self.PRSEVENTSEQIEN
        self.STATEOFFIEN = RM_Field_RAC_NS_SEQIEN_STATEOFFIEN(self)
        self.zz_fdict['STATEOFFIEN'] = self.STATEOFFIEN
        self.STATERXWARMIEN = RM_Field_RAC_NS_SEQIEN_STATERXWARMIEN(self)
        self.zz_fdict['STATERXWARMIEN'] = self.STATERXWARMIEN
        self.STATERXSEARCHIEN = RM_Field_RAC_NS_SEQIEN_STATERXSEARCHIEN(self)
        self.zz_fdict['STATERXSEARCHIEN'] = self.STATERXSEARCHIEN
        self.STATERXFRAMEIEN = RM_Field_RAC_NS_SEQIEN_STATERXFRAMEIEN(self)
        self.zz_fdict['STATERXFRAMEIEN'] = self.STATERXFRAMEIEN
        self.STATERXPDIEN = RM_Field_RAC_NS_SEQIEN_STATERXPDIEN(self)
        self.zz_fdict['STATERXPDIEN'] = self.STATERXPDIEN
        self.STATERX2RXIEN = RM_Field_RAC_NS_SEQIEN_STATERX2RXIEN(self)
        self.zz_fdict['STATERX2RXIEN'] = self.STATERX2RXIEN
        self.STATERXOVERFLOWIEN = RM_Field_RAC_NS_SEQIEN_STATERXOVERFLOWIEN(self)
        self.zz_fdict['STATERXOVERFLOWIEN'] = self.STATERXOVERFLOWIEN
        self.STATERX2TXIEN = RM_Field_RAC_NS_SEQIEN_STATERX2TXIEN(self)
        self.zz_fdict['STATERX2TXIEN'] = self.STATERX2TXIEN
        self.STATETXWARMIEN = RM_Field_RAC_NS_SEQIEN_STATETXWARMIEN(self)
        self.zz_fdict['STATETXWARMIEN'] = self.STATETXWARMIEN
        self.STATETXIEN = RM_Field_RAC_NS_SEQIEN_STATETXIEN(self)
        self.zz_fdict['STATETXIEN'] = self.STATETXIEN
        self.STATETXPDIEN = RM_Field_RAC_NS_SEQIEN_STATETXPDIEN(self)
        self.zz_fdict['STATETXPDIEN'] = self.STATETXPDIEN
        self.STATETX2RXIEN = RM_Field_RAC_NS_SEQIEN_STATETX2RXIEN(self)
        self.zz_fdict['STATETX2RXIEN'] = self.STATETX2RXIEN
        self.STATETX2TXIEN = RM_Field_RAC_NS_SEQIEN_STATETX2TXIEN(self)
        self.zz_fdict['STATETX2TXIEN'] = self.STATETX2TXIEN
        self.STATESHUTDOWNIEN = RM_Field_RAC_NS_SEQIEN_STATESHUTDOWNIEN(self)
        self.zz_fdict['STATESHUTDOWNIEN'] = self.STATESHUTDOWNIEN
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
            0x00000000, 0x00100200,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNTHSTARTREQ = RM_Field_RAC_NS_SYNTHENCTRL_SYNTHSTARTREQ(self)
        self.zz_fdict['SYNTHSTARTREQ'] = self.SYNTHSTARTREQ
        self.LPFBWSEL = RM_Field_RAC_NS_SYNTHENCTRL_LPFBWSEL(self)
        self.zz_fdict['LPFBWSEL'] = self.LPFBWSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_VCOCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_VCOCTRL, self).__init__(rmio, label,
            0xb8020000, 0x0A0,
            'VCOCTRL', 'RAC_NS.VCOCTRL', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYVCOVCAP = RM_Field_RAC_NS_VCOCTRL_SYVCOVCAP(self)
        self.zz_fdict['SYVCOVCAP'] = self.SYVCOVCAP
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


class RM_Register_RAC_NS_VCOTUNE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_VCOTUNE, self).__init__(rmio, label,
            0xb8020000, 0x0A8,
            'VCOTUNE', 'RAC_NS.VCOTUNE', 'read-write',
            u"",
            0x00000000, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYVCOTUNING = RM_Field_RAC_NS_VCOTUNE_SYVCOTUNING(self)
        self.zz_fdict['SYVCOTUNING'] = self.SYVCOTUNING
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
            0x00000000, 0x0E380000,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCCALON = RM_Field_RAC_NS_IFPGACTRL_DCCALON(self)
        self.zz_fdict['DCCALON'] = self.DCCALON
        self.DCRSTEN = RM_Field_RAC_NS_IFPGACTRL_DCRSTEN(self)
        self.zz_fdict['DCRSTEN'] = self.DCRSTEN
        self.DCESTIEN = RM_Field_RAC_NS_IFPGACTRL_DCESTIEN(self)
        self.zz_fdict['DCESTIEN'] = self.DCESTIEN
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
            0x00000000, 0x00000FBD,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTDIVLNAMIXEN0 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXEN0(self)
        self.zz_fdict['INTDIVLNAMIXEN0'] = self.INTDIVLNAMIXEN0
        self.INTDIVLNAMIXRFATTDCEN0 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFATTDCEN0(self)
        self.zz_fdict['INTDIVLNAMIXRFATTDCEN0'] = self.INTDIVLNAMIXRFATTDCEN0
        self.INTDIVLNAMIXRFPKDENRF0 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFPKDENRF0(self)
        self.zz_fdict['INTDIVLNAMIXRFPKDENRF0'] = self.INTDIVLNAMIXRFPKDENRF0
        self.INTDIVSYLODIVRLO02G4EN = RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO02G4EN(self)
        self.zz_fdict['INTDIVSYLODIVRLO02G4EN'] = self.INTDIVSYLODIVRLO02G4EN
        self.INTDIVLNAMIXEN1 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXEN1(self)
        self.zz_fdict['INTDIVLNAMIXEN1'] = self.INTDIVLNAMIXEN1
        self.INTDIVLNAMIXRFATTDCEN1 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFATTDCEN1(self)
        self.zz_fdict['INTDIVLNAMIXRFATTDCEN1'] = self.INTDIVLNAMIXRFATTDCEN1
        self.INTDIVLNAMIXRFPKDENRF1 = RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFPKDENRF1(self)
        self.zz_fdict['INTDIVLNAMIXRFPKDENRF1'] = self.INTDIVLNAMIXRFPKDENRF1
        self.INTDIVSYLODIVRLO12G4EN = RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO12G4EN(self)
        self.zz_fdict['INTDIVSYLODIVRLO12G4EN'] = self.INTDIVSYLODIVRLO12G4EN
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
            0x00003080, 0x00007FFE,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCTSENSESELCURR = RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSESELCURR(self)
        self.zz_fdict['ADCTSENSESELCURR'] = self.ADCTSENSESELCURR
        self.ADCTRIMCURRTSENSE = RM_Field_RAC_NS_AUXADCTRIM_ADCTRIMCURRTSENSE(self)
        self.zz_fdict['ADCTRIMCURRTSENSE'] = self.ADCTRIMCURRTSENSE
        self.ADCTSENSESELVBE = RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSESELVBE(self)
        self.zz_fdict['ADCTSENSESELVBE'] = self.ADCTSENSESELVBE
        self.ADCTSENSETRIMVBE2 = RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSETRIMVBE2(self)
        self.zz_fdict['ADCTSENSETRIMVBE2'] = self.ADCTSENSETRIMVBE2
        self.ADCTUNERC = RM_Field_RAC_NS_AUXADCTRIM_ADCTUNERC(self)
        self.zz_fdict['ADCTUNERC'] = self.ADCTUNERC
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCEN, self).__init__(rmio, label,
            0xb8020000, 0x0C8,
            'AUXADCEN', 'RAC_NS.AUXADCEN', 'read-write',
            u"",
            0x00000000, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCENADC = RM_Field_RAC_NS_AUXADCEN_ADCENADC(self)
        self.zz_fdict['ADCENADC'] = self.ADCENADC
        self.ADCENCLK = RM_Field_RAC_NS_AUXADCEN_ADCENCLK(self)
        self.zz_fdict['ADCENCLK'] = self.ADCENCLK
        self.ADCENAUXADC = RM_Field_RAC_NS_AUXADCEN_ADCENAUXADC(self)
        self.zz_fdict['ADCENAUXADC'] = self.ADCENAUXADC
        self.ADCENINPUTBUFFER = RM_Field_RAC_NS_AUXADCEN_ADCENINPUTBUFFER(self)
        self.zz_fdict['ADCENINPUTBUFFER'] = self.ADCENINPUTBUFFER
        self.ADCENLDOSERIES = RM_Field_RAC_NS_AUXADCEN_ADCENLDOSERIES(self)
        self.zz_fdict['ADCENLDOSERIES'] = self.ADCENLDOSERIES
        self.ADCENNEGRES = RM_Field_RAC_NS_AUXADCEN_ADCENNEGRES(self)
        self.zz_fdict['ADCENNEGRES'] = self.ADCENNEGRES
        self.ADCENPMON = RM_Field_RAC_NS_AUXADCEN_ADCENPMON(self)
        self.zz_fdict['ADCENPMON'] = self.ADCENPMON
        self.ADCENRESONDIAGA = RM_Field_RAC_NS_AUXADCEN_ADCENRESONDIAGA(self)
        self.zz_fdict['ADCENRESONDIAGA'] = self.ADCENRESONDIAGA
        self.ADCENTSENSECAL = RM_Field_RAC_NS_AUXADCEN_ADCENTSENSECAL(self)
        self.zz_fdict['ADCENTSENSECAL'] = self.ADCENTSENSECAL
        self.ADCINPUTBUFFERBYPASS = RM_Field_RAC_NS_AUXADCEN_ADCINPUTBUFFERBYPASS(self)
        self.zz_fdict['ADCINPUTBUFFERBYPASS'] = self.ADCINPUTBUFFERBYPASS
        self.ADCENLDOBIASSERIES = RM_Field_RAC_NS_AUXADCEN_ADCENLDOBIASSERIES(self)
        self.zz_fdict['ADCENLDOBIASSERIES'] = self.ADCENLDOBIASSERIES
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
            0x00000A20, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCINPUTRESSEL = RM_Field_RAC_NS_AUXADCCTRL1_ADCINPUTRESSEL(self)
        self.zz_fdict['ADCINPUTRESSEL'] = self.ADCINPUTRESSEL
        self.ADCINPUTSCALE = RM_Field_RAC_NS_AUXADCCTRL1_ADCINPUTSCALE(self)
        self.zz_fdict['ADCINPUTSCALE'] = self.ADCINPUTSCALE
        self.ADCINVERTCLK = RM_Field_RAC_NS_AUXADCCTRL1_ADCINVERTCLK(self)
        self.zz_fdict['ADCINVERTCLK'] = self.ADCINVERTCLK
        self.ADCLDOSHUNTCURLVL2 = RM_Field_RAC_NS_AUXADCCTRL1_ADCLDOSHUNTCURLVL2(self)
        self.zz_fdict['ADCLDOSHUNTCURLVL2'] = self.ADCLDOSHUNTCURLVL2
        self.ADCTUNERCCALMODE = RM_Field_RAC_NS_AUXADCCTRL1_ADCTUNERCCALMODE(self)
        self.zz_fdict['ADCTUNERCCALMODE'] = self.ADCTUNERCCALMODE
        self.ADCZEROOPT = RM_Field_RAC_NS_AUXADCCTRL1_ADCZEROOPT(self)
        self.zz_fdict['ADCZEROOPT'] = self.ADCZEROOPT
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
            0x01402005, 0x1FFFFFFF,
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
        self.CLKMULTILOADREG2 = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTILOADREG2(self)
        self.zz_fdict['CLKMULTILOADREG2'] = self.CLKMULTILOADREG2
        self.CLKMULTENFBDIV = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENFBDIV(self)
        self.zz_fdict['CLKMULTENFBDIV'] = self.CLKMULTENFBDIV
        self.CLKMULTENREFDIV = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREFDIV(self)
        self.zz_fdict['CLKMULTENREFDIV'] = self.CLKMULTENREFDIV
        self.CLKMULTENREG1 = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1(self)
        self.zz_fdict['CLKMULTENREG1'] = self.CLKMULTENREG1
        self.CLKMULTENREG2 = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG2(self)
        self.zz_fdict['CLKMULTENREG2'] = self.CLKMULTENREG2
        self.CLKMULTENDRVDAC = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVDAC(self)
        self.zz_fdict['CLKMULTENDRVDAC'] = self.CLKMULTENDRVDAC
        self.CLKMULTENROTDET = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENROTDET(self)
        self.zz_fdict['CLKMULTENROTDET'] = self.CLKMULTENROTDET
        self.CLKMULTENBYPASS40MHZ = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBYPASS40MHZ(self)
        self.zz_fdict['CLKMULTENBYPASS40MHZ'] = self.CLKMULTENBYPASS40MHZ
        self.CLKMULTENDRVIRCAL = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVIRCAL(self)
        self.zz_fdict['CLKMULTENDRVIRCAL'] = self.CLKMULTENDRVIRCAL
        self.CLKMULTFREQCAL = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTFREQCAL(self)
        self.zz_fdict['CLKMULTFREQCAL'] = self.CLKMULTFREQCAL
        self.CLKMULTENREG1FORCEDSTARTUP = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1FORCEDSTARTUP(self)
        self.zz_fdict['CLKMULTENREG1FORCEDSTARTUP'] = self.CLKMULTENREG1FORCEDSTARTUP
        self.CLKMULTENREG1IBIAS = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1IBIAS(self)
        self.zz_fdict['CLKMULTENREG1IBIAS'] = self.CLKMULTENREG1IBIAS
        self.CLKMULTENREG1REPLICA = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1REPLICA(self)
        self.zz_fdict['CLKMULTENREG1REPLICA'] = self.CLKMULTENREG1REPLICA
        self.CLKMULTENREG1STBLOAD = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1STBLOAD(self)
        self.zz_fdict['CLKMULTENREG1STBLOAD'] = self.CLKMULTENREG1STBLOAD
        self.CLKMULTENDRVTEST = RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVTEST(self)
        self.zz_fdict['CLKMULTENDRVTEST'] = self.CLKMULTENDRVTEST
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CLKMULTEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CLKMULTEN1, self).__init__(rmio, label,
            0xb8020000, 0x0DC,
            'CLKMULTEN1', 'RAC_NS.CLKMULTEN1', 'read-write',
            u"",
            0x01800188, 0x7FFFFDEF,
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
        self.CLKMULTDIVN = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVN(self)
        self.zz_fdict['CLKMULTDIVN'] = self.CLKMULTDIVN
        self.CLKMULTDIVR = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVR(self)
        self.zz_fdict['CLKMULTDIVR'] = self.CLKMULTDIVR
        self.CLKMULTDIVX = RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVX(self)
        self.zz_fdict['CLKMULTDIVX'] = self.CLKMULTDIVX
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_CLKMULTCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_CLKMULTCTRL, self).__init__(rmio, label,
            0xb8020000, 0x0E0,
            'CLKMULTCTRL', 'RAC_NS.CLKMULTCTRL', 'read-write',
            u"",
            0x00000548, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTENRESYNC = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTENRESYNC(self)
        self.zz_fdict['CLKMULTENRESYNC'] = self.CLKMULTENRESYNC
        self.CLKMULTVALID = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTVALID(self)
        self.zz_fdict['CLKMULTVALID'] = self.CLKMULTVALID
        self.CLKMULTRESETPHFRQDET = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTRESETPHFRQDET(self)
        self.zz_fdict['CLKMULTRESETPHFRQDET'] = self.CLKMULTRESETPHFRQDET
        self.CLKMULTTRIMVREF1 = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREF1(self)
        self.zz_fdict['CLKMULTTRIMVREF1'] = self.CLKMULTTRIMVREF1
        self.CLKMULTTRIMVREF2 = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREF2(self)
        self.zz_fdict['CLKMULTTRIMVREF2'] = self.CLKMULTTRIMVREF2
        self.CLKMULTTRIMVREG1 = RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREG1(self)
        self.zz_fdict['CLKMULTTRIMVREG1'] = self.CLKMULTTRIMVREG1
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
            0x00000000, 0x0000007B,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCENSIDETONE = RM_Field_RAC_NS_IFADCDBG_ADCENSIDETONE(self)
        self.zz_fdict['ADCENSIDETONE'] = self.ADCENSIDETONE
        self.ADCENTSENSE = RM_Field_RAC_NS_IFADCDBG_ADCENTSENSE(self)
        self.zz_fdict['ADCENTSENSE'] = self.ADCENTSENSE
        self.ADCINPUTSELECT = RM_Field_RAC_NS_IFADCDBG_ADCINPUTSELECT(self)
        self.zz_fdict['ADCINPUTSELECT'] = self.ADCINPUTSELECT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCTRIM0, self).__init__(rmio, label,
            0xb8020000, 0x0EC,
            'IFADCTRIM0', 'RAC_NS.IFADCTRIM0', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCCLKSEL = RM_Field_RAC_NS_IFADCTRIM0_ADCCLKSEL(self)
        self.zz_fdict['ADCCLKSEL'] = self.ADCCLKSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCTRIM1, self).__init__(rmio, label,
            0xb8020000, 0x0F0,
            'IFADCTRIM1', 'RAC_NS.IFADCTRIM1', 'read-write',
            u"",
            0x00028000, 0x000FC000,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCREFBUFCURLVL = RM_Field_RAC_NS_IFADCTRIM1_ADCREFBUFCURLVL(self)
        self.zz_fdict['ADCREFBUFCURLVL'] = self.ADCREFBUFCURLVL
        self.ADCSIDETONEAMP = RM_Field_RAC_NS_IFADCTRIM1_ADCSIDETONEAMP(self)
        self.zz_fdict['ADCSIDETONEAMP'] = self.ADCSIDETONEAMP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_IFADCCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_IFADCCAL, self).__init__(rmio, label,
            0xb8020000, 0x0F4,
            'IFADCCAL', 'RAC_NS.IFADCCAL', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCENRCCAL = RM_Field_RAC_NS_IFADCCAL_ADCENRCCAL(self)
        self.zz_fdict['ADCENRCCAL'] = self.ADCENRCCAL
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

        self.ADCRCCALOUT = RM_Field_RAC_NS_IFADCSTATUS_ADCRCCALOUT(self)
        self.zz_fdict['ADCRCCALOUT'] = self.ADCRCCALOUT
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM0, self).__init__(rmio, label,
            0xb8020000, 0x100,
            'LNAMIXTRIM0', 'RAC_NS.LNAMIXTRIM0', 'read-write',
            u"",
            0x00000008, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXTRIMVREG = RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXTRIMVREG(self)
        self.zz_fdict['LNAMIXTRIMVREG'] = self.LNAMIXTRIMVREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM1, self).__init__(rmio, label,
            0xb8020000, 0x104,
            'LNAMIXTRIM1', 'RAC_NS.LNAMIXTRIM1', 'read-write',
            u"",
            0x000009D8, 0x00001BFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXLNA1CAPSEL = RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXLNA1CAPSEL(self)
        self.zz_fdict['LNAMIXLNA1CAPSEL'] = self.LNAMIXLNA1CAPSEL
        self.LNAMIXMXRBIAS1 = RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXMXRBIAS1(self)
        self.zz_fdict['LNAMIXMXRBIAS1'] = self.LNAMIXMXRBIAS1
        self.LNAMIXIBIAS1TRIM = RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXIBIAS1TRIM(self)
        self.zz_fdict['LNAMIXIBIAS1TRIM'] = self.LNAMIXIBIAS1TRIM
        self.LNAMIXNCAS1ADJ = RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXNCAS1ADJ(self)
        self.zz_fdict['LNAMIXNCAS1ADJ'] = self.LNAMIXNCAS1ADJ
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM2, self).__init__(rmio, label,
            0xb8020000, 0x108,
            'LNAMIXTRIM2', 'RAC_NS.LNAMIXTRIM2', 'read-write',
            u"",
            0x00000000, 0x0000001F,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXHIGHCUR = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXHIGHCUR(self)
        self.zz_fdict['LNAMIXHIGHCUR'] = self.LNAMIXHIGHCUR
        self.LNAMIXENREGVHIGH = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXENREGVHIGH(self)
        self.zz_fdict['LNAMIXENREGVHIGH'] = self.LNAMIXENREGVHIGH
        self.LNAMIXENSTBLOAD = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXENSTBLOAD(self)
        self.zz_fdict['LNAMIXENSTBLOAD'] = self.LNAMIXENSTBLOAD
        self.LNAMIXREGLOWPWR = RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXREGLOWPWR(self)
        self.zz_fdict['LNAMIXREGLOWPWR'] = self.LNAMIXREGLOWPWR
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM3, self).__init__(rmio, label,
            0xb8020000, 0x10C,
            'LNAMIXTRIM3', 'RAC_NS.LNAMIXTRIM3', 'read-write',
            u"",
            0x00082000, 0x000FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXRFATT1 = RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFATT1(self)
        self.zz_fdict['LNAMIXRFATT1'] = self.LNAMIXRFATT1
        self.LNAMIXRFPKDCALCMLO = RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFPKDCALCMLO(self)
        self.zz_fdict['LNAMIXRFPKDCALCMLO'] = self.LNAMIXRFPKDCALCMLO
        self.LNAMIXRFPKDCALCMHI = RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFPKDCALCMHI(self)
        self.zz_fdict['LNAMIXRFPKDCALCMHI'] = self.LNAMIXRFPKDCALCMHI
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXTRIM4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXTRIM4, self).__init__(rmio, label,
            0xb8020000, 0x110,
            'LNAMIXTRIM4', 'RAC_NS.LNAMIXTRIM4', 'read-write',
            u"",
            0x00000002, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXRFPKDBWSEL = RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDBWSEL(self)
        self.zz_fdict['LNAMIXRFPKDBWSEL'] = self.LNAMIXRFPKDBWSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXCAL, self).__init__(rmio, label,
            0xb8020000, 0x114,
            'LNAMIXCAL', 'RAC_NS.LNAMIXCAL', 'read-write',
            u"",
            0x000000E0, 0x000000E4,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXCALVMODE = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALVMODE(self)
        self.zz_fdict['LNAMIXCALVMODE'] = self.LNAMIXCALVMODE
        self.LNAMIXIRCAL1AMP = RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL1AMP(self)
        self.zz_fdict['LNAMIXIRCAL1AMP'] = self.LNAMIXIRCAL1AMP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PRECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PRECTRL, self).__init__(rmio, label,
            0xb8020000, 0x11C,
            'PRECTRL', 'RAC_NS.PRECTRL', 'read-write',
            u"",
            0x00000000, 0x0000007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGBYPFORCE = RM_Field_RAC_NS_PRECTRL_PREREGBYPFORCE(self)
        self.zz_fdict['PREREGBYPFORCE'] = self.PREREGBYPFORCE
        self.PREREGENBYPCMP = RM_Field_RAC_NS_PRECTRL_PREREGENBYPCMP(self)
        self.zz_fdict['PREREGENBYPCMP'] = self.PREREGENBYPCMP
        self.PREREGENSTBILOAD = RM_Field_RAC_NS_PRECTRL_PREREGENSTBILOAD(self)
        self.zz_fdict['PREREGENSTBILOAD'] = self.PREREGENSTBILOAD
        self.PREREGENINTBIAS = RM_Field_RAC_NS_PRECTRL_PREREGENINTBIAS(self)
        self.zz_fdict['PREREGENINTBIAS'] = self.PREREGENINTBIAS
        self.PREREGENVTRMINI = RM_Field_RAC_NS_PRECTRL_PREREGENVTRMINI(self)
        self.zz_fdict['PREREGENVTRMINI'] = self.PREREGENVTRMINI
        self.PREREGENVTRMINISTARTUP = RM_Field_RAC_NS_PRECTRL_PREREGENVTRMINISTARTUP(self)
        self.zz_fdict['PREREGENVTRMINISTARTUP'] = self.PREREGENVTRMINISTARTUP
        self.PREREGSTARTUPFORCE = RM_Field_RAC_NS_PRECTRL_PREREGSTARTUPFORCE(self)
        self.zz_fdict['PREREGSTARTUPFORCE'] = self.PREREGSTARTUPFORCE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PATRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PATRIM0, self).__init__(rmio, label,
            0xb8020000, 0x120,
            'PATRIM0', 'RAC_NS.PATRIM0', 'read-write',
            u"",
            0x00000000, 0x0002FF00,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXPAAMPCTRL = RM_Field_RAC_NS_PATRIM0_TXPAAMPCTRL(self)
        self.zz_fdict['TXPAAMPCTRL'] = self.TXPAAMPCTRL
        self.ENAMPCTRLREG = RM_Field_RAC_NS_PATRIM0_ENAMPCTRLREG(self)
        self.zz_fdict['ENAMPCTRLREG'] = self.ENAMPCTRLREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXPOWER(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXPOWER, self).__init__(rmio, label,
            0xb8020000, 0x13C,
            'TXPOWER', 'RAC_NS.TXPOWER', 'read-write',
            u"",
            0x00000000, 0x00000300,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMSELSLICE = RM_Field_RAC_NS_TXPOWER_TX0DBMSELSLICE(self)
        self.zz_fdict['TX0DBMSELSLICE'] = self.TX0DBMSELSLICE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TXRAMP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TXRAMP, self).__init__(rmio, label,
            0xb8020000, 0x140,
            'TXRAMP', 'RAC_NS.TXRAMP', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.PARAMPMODE = RM_Field_RAC_NS_TXRAMP_PARAMPMODE(self)
        self.zz_fdict['PARAMPMODE'] = self.PARAMPMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RADIOEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RADIOEN, self).__init__(rmio, label,
            0xb8020000, 0x15C,
            'RADIOEN', 'RAC_NS.RADIOEN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGENREG = RM_Field_RAC_NS_RADIOEN_PREREGENREG(self)
        self.zz_fdict['PREREGENREG'] = self.PREREGENREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFPATHEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFPATHEN0, self).__init__(rmio, label,
            0xb8020000, 0x160,
            'RFPATHEN0', 'RAC_NS.RFPATHEN0', 'read-write',
            u"",
            0x00000002, 0x00000002,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXRFATTDCEN1 = RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFATTDCEN1(self)
        self.zz_fdict['LNAMIXRFATTDCEN1'] = self.LNAMIXRFATTDCEN1
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RFPATHEN1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RFPATHEN1, self).__init__(rmio, label,
            0xb8020000, 0x164,
            'RFPATHEN1', 'RAC_NS.RFPATHEN1', 'read-write',
            u"",
            0x00000000, 0x0000008D,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXEN1 = RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN1(self)
        self.zz_fdict['LNAMIXEN1'] = self.LNAMIXEN1
        self.LNAMIXRFPKDENRF1 = RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFPKDENRF1(self)
        self.zz_fdict['LNAMIXRFPKDENRF1'] = self.LNAMIXRFPKDENRF1
        self.LNAMIXTRSW1 = RM_Field_RAC_NS_RFPATHEN1_LNAMIXTRSW1(self)
        self.zz_fdict['LNAMIXTRSW1'] = self.LNAMIXTRSW1
        self.LNAMIXREGLOWCUR = RM_Field_RAC_NS_RFPATHEN1_LNAMIXREGLOWCUR(self)
        self.zz_fdict['LNAMIXREGLOWCUR'] = self.LNAMIXREGLOWCUR
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_RX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_RX, self).__init__(rmio, label,
            0xb8020000, 0x168,
            'RX', 'RAC_NS.RX', 'read-write',
            u"",
            0x8835D700, 0xFFFFFFBF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCCAPRESET = RM_Field_RAC_NS_RX_ADCCAPRESET(self)
        self.zz_fdict['ADCCAPRESET'] = self.ADCCAPRESET
        self.ADCENLDOSHUNT = RM_Field_RAC_NS_RX_ADCENLDOSHUNT(self)
        self.zz_fdict['ADCENLDOSHUNT'] = self.ADCENLDOSHUNT
        self.LNAMIXCALEN = RM_Field_RAC_NS_RX_LNAMIXCALEN(self)
        self.zz_fdict['LNAMIXCALEN'] = self.LNAMIXCALEN
        self.LNAMIXENRFPKD = RM_Field_RAC_NS_RX_LNAMIXENRFPKD(self)
        self.zz_fdict['LNAMIXENRFPKD'] = self.LNAMIXENRFPKD
        self.LNAMIXENLOTHRESH = RM_Field_RAC_NS_RX_LNAMIXENLOTHRESH(self)
        self.zz_fdict['LNAMIXENLOTHRESH'] = self.LNAMIXENLOTHRESH
        self.LNAMIXMXRLOSEL = RM_Field_RAC_NS_RX_LNAMIXMXRLOSEL(self)
        self.zz_fdict['LNAMIXMXRLOSEL'] = self.LNAMIXMXRLOSEL
        self.LNAMIXCURCTRL = RM_Field_RAC_NS_RX_LNAMIXCURCTRL(self)
        self.zz_fdict['LNAMIXCURCTRL'] = self.LNAMIXCURCTRL
        self.LNAMIXLNA1SLICE = RM_Field_RAC_NS_RX_LNAMIXLNA1SLICE(self)
        self.zz_fdict['LNAMIXLNA1SLICE'] = self.LNAMIXLNA1SLICE
        self.LNAMIXDOUBLECUR1EN = RM_Field_RAC_NS_RX_LNAMIXDOUBLECUR1EN(self)
        self.zz_fdict['LNAMIXDOUBLECUR1EN'] = self.LNAMIXDOUBLECUR1EN
        self.LNAMIXLOWCUR = RM_Field_RAC_NS_RX_LNAMIXLOWCUR(self)
        self.zz_fdict['LNAMIXLOWCUR'] = self.LNAMIXLOWCUR
        self.LNAMIXRFPKDTHRESHSELLO = RM_Field_RAC_NS_RX_LNAMIXRFPKDTHRESHSELLO(self)
        self.zz_fdict['LNAMIXRFPKDTHRESHSELLO'] = self.LNAMIXRFPKDTHRESHSELLO
        self.LNAMIXRFPKDTHRESHSELHI = RM_Field_RAC_NS_RX_LNAMIXRFPKDTHRESHSELHI(self)
        self.zz_fdict['LNAMIXRFPKDTHRESHSELHI'] = self.LNAMIXRFPKDTHRESHSELHI
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX, self).__init__(rmio, label,
            0xb8020000, 0x16C,
            'TX', 'RAC_NS.TX', 'read-write',
            u"",
            0x00000000, 0xF8000000,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYCHPBIASTRIMBUFTX = RM_Field_RAC_NS_TX_SYCHPBIASTRIMBUFTX(self)
        self.zz_fdict['SYCHPBIASTRIMBUFTX'] = self.SYCHPBIASTRIMBUFTX
        self.SYPFDCHPLPENTX = RM_Field_RAC_NS_TX_SYPFDCHPLPENTX(self)
        self.zz_fdict['SYPFDCHPLPENTX'] = self.SYPFDCHPLPENTX
        self.SYPFDFPWENTX = RM_Field_RAC_NS_TX_SYPFDFPWENTX(self)
        self.zz_fdict['SYPFDFPWENTX'] = self.SYPFDFPWENTX
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
            0x00000000, 0x00001707,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYPFDFPWENRX = RM_Field_RAC_NS_SYDEBUG_SYPFDFPWENRX(self)
        self.zz_fdict['SYPFDFPWENRX'] = self.SYPFDFPWENRX
        self.SYPFDCHPLPENRX = RM_Field_RAC_NS_SYDEBUG_SYPFDCHPLPENRX(self)
        self.zz_fdict['SYPFDCHPLPENRX'] = self.SYPFDCHPLPENRX
        self.SYCHPBIASTRIMBUFRX = RM_Field_RAC_NS_SYDEBUG_SYCHPBIASTRIMBUFRX(self)
        self.zz_fdict['SYCHPBIASTRIMBUFRX'] = self.SYCHPBIASTRIMBUFRX
        self.SYENMMDREGBIAS = RM_Field_RAC_NS_SYDEBUG_SYENMMDREGBIAS(self)
        self.zz_fdict['SYENMMDREGBIAS'] = self.SYENMMDREGBIAS
        self.SYENMMDREGFORCEDSTARTUP = RM_Field_RAC_NS_SYDEBUG_SYENMMDREGFORCEDSTARTUP(self)
        self.zz_fdict['SYENMMDREGFORCEDSTARTUP'] = self.SYENMMDREGFORCEDSTARTUP
        self.SYENMMDREGREPLICA = RM_Field_RAC_NS_SYDEBUG_SYENMMDREGREPLICA(self)
        self.zz_fdict['SYENMMDREGREPLICA'] = self.SYENMMDREGREPLICA
        self.SYENMMDSYNC = RM_Field_RAC_NS_SYDEBUG_SYENMMDSYNC(self)
        self.zz_fdict['SYENMMDSYNC'] = self.SYENMMDSYNC
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYTRIM0, self).__init__(rmio, label,
            0xb8020000, 0x174,
            'SYTRIM0', 'RAC_NS.SYTRIM0', 'read-write',
            u"",
            0x110AE429, 0x7BFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYVCOTRIMIPTAT = RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMIPTAT(self)
        self.zz_fdict['SYVCOTRIMIPTAT'] = self.SYVCOTRIMIPTAT
        self.SYLODIVREGTRIMVREG = RM_Field_RAC_NS_SYTRIM0_SYLODIVREGTRIMVREG(self)
        self.zz_fdict['SYLODIVREGTRIMVREG'] = self.SYLODIVREGTRIMVREG
        self.SYVCOTRIMPKDAMP = RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMPKDAMP(self)
        self.zz_fdict['SYVCOTRIMPKDAMP'] = self.SYVCOTRIMPKDAMP
        self.SYVCOREGLOWCUR = RM_Field_RAC_NS_SYTRIM0_SYVCOREGLOWCUR(self)
        self.zz_fdict['SYVCOREGLOWCUR'] = self.SYVCOREGLOWCUR
        self.SYVCOTRIMR = RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMR(self)
        self.zz_fdict['SYVCOTRIMR'] = self.SYVCOTRIMR
        self.SYVCOTRIMREF = RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMREF(self)
        self.zz_fdict['SYVCOTRIMREF'] = self.SYVCOTRIMREF
        self.SYTDCREGTRIMBW = RM_Field_RAC_NS_SYTRIM0_SYTDCREGTRIMBW(self)
        self.zz_fdict['SYTDCREGTRIMBW'] = self.SYTDCREGTRIMBW
        self.SYVCOHCAPRETIMESEL = RM_Field_RAC_NS_SYTRIM0_SYVCOHCAPRETIMESEL(self)
        self.zz_fdict['SYVCOHCAPRETIMESEL'] = self.SYVCOHCAPRETIMESEL
        self.SYVCOREGTRIMVREG = RM_Field_RAC_NS_SYTRIM0_SYVCOREGTRIMVREG(self)
        self.zz_fdict['SYVCOREGTRIMVREG'] = self.SYVCOREGTRIMVREG
        self.SYVCOTRIMIBIAS = RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMIBIAS(self)
        self.zz_fdict['SYVCOTRIMIBIAS'] = self.SYVCOTRIMIBIAS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYTRIM1, self).__init__(rmio, label,
            0xb8020000, 0x178,
            'SYTRIM1', 'RAC_NS.SYTRIM1', 'read-write',
            u"",
            0x00008200, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYTDCTRIMDLYCNT = RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYCNT(self)
        self.zz_fdict['SYTDCTRIMDLYCNT'] = self.SYTDCTRIMDLYCNT
        self.SYTDCTRIMDLYLOAD = RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYLOAD(self)
        self.zz_fdict['SYTDCTRIMDLYLOAD'] = self.SYTDCTRIMDLYLOAD
        self.SYTDCTRIMDLYSTOPMETA = RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYSTOPMETA(self)
        self.zz_fdict['SYTDCTRIMDLYSTOPMETA'] = self.SYTDCTRIMDLYSTOPMETA
        self.SYDTCREGTRIMVREF = RM_Field_RAC_NS_SYTRIM1_SYDTCREGTRIMVREF(self)
        self.zz_fdict['SYDTCREGTRIMVREF'] = self.SYDTCREGTRIMVREF
        self.SYTDCTRIMDLYCK1 = RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYCK1(self)
        self.zz_fdict['SYTDCTRIMDLYCK1'] = self.SYTDCTRIMDLYCK1
        self.SYDTCRDACTRIM = RM_Field_RAC_NS_SYTRIM1_SYDTCRDACTRIM(self)
        self.zz_fdict['SYDTCRDACTRIM'] = self.SYDTCRDACTRIM
        self.SYTDCREGTRIMVREG = RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMVREG(self)
        self.zz_fdict['SYTDCREGTRIMVREG'] = self.SYTDCREGTRIMVREG
        self.SYTDCREGTRIMTEMPCOP = RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMTEMPCOP(self)
        self.zz_fdict['SYTDCREGTRIMTEMPCOP'] = self.SYTDCREGTRIMTEMPCOP
        self.SYTDCREGTRIMVREF = RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMVREF(self)
        self.zz_fdict['SYTDCREGTRIMVREF'] = self.SYTDCREGTRIMVREF
        self.SYTDCREGTRIMTEMPCON = RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMTEMPCON(self)
        self.zz_fdict['SYTDCREGTRIMTEMPCON'] = self.SYTDCREGTRIMTEMPCON
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYEN, self).__init__(rmio, label,
            0xb8020000, 0x180,
            'SYEN', 'RAC_NS.SYEN', 'read-write',
            u"",
            0x00000000, 0x0193E803,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENVCOREG = RM_Field_RAC_NS_SYEN_SYENVCOREG(self)
        self.zz_fdict['SYENVCOREG'] = self.SYENVCOREG
        self.SYENDLFAQNC = RM_Field_RAC_NS_SYEN_SYENDLFAQNC(self)
        self.zz_fdict['SYENDLFAQNC'] = self.SYENDLFAQNC
        self.SYENMMDREGSTBLOAD = RM_Field_RAC_NS_SYEN_SYENMMDREGSTBLOAD(self)
        self.zz_fdict['SYENMMDREGSTBLOAD'] = self.SYENMMDREGSTBLOAD
        self.SYENTDCAQNC = RM_Field_RAC_NS_SYEN_SYENTDCAQNC(self)
        self.zz_fdict['SYENTDCAQNC'] = self.SYENTDCAQNC
        self.SYENTDCREG = RM_Field_RAC_NS_SYEN_SYENTDCREG(self)
        self.zz_fdict['SYENTDCREG'] = self.SYENTDCREG
        self.SYENTDCREGSTBLOAD = RM_Field_RAC_NS_SYEN_SYENTDCREGSTBLOAD(self)
        self.zz_fdict['SYENTDCREGSTBLOAD'] = self.SYENTDCREGSTBLOAD
        self.SYENVCOIBIAS = RM_Field_RAC_NS_SYEN_SYENVCOIBIAS(self)
        self.zz_fdict['SYENVCOIBIAS'] = self.SYENVCOIBIAS
        self.SYENVCOPKD = RM_Field_RAC_NS_SYEN_SYENVCOPKD(self)
        self.zz_fdict['SYENVCOPKD'] = self.SYENVCOPKD
        self.SYENVCOBIAS = RM_Field_RAC_NS_SYEN_SYENVCOBIAS(self)
        self.zz_fdict['SYENVCOBIAS'] = self.SYENVCOBIAS
        self.SYENTDC = RM_Field_RAC_NS_SYEN_SYENTDC(self)
        self.zz_fdict['SYENTDC'] = self.SYENTDC
        self.SYENVCOHCAPRETIME = RM_Field_RAC_NS_SYEN_SYENVCOHCAPRETIME(self)
        self.zz_fdict['SYENVCOHCAPRETIME'] = self.SYENVCOHCAPRETIME
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYLOEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYLOEN, self).__init__(rmio, label,
            0xb8020000, 0x184,
            'SYLOEN', 'RAC_NS.SYLOEN', 'read-write',
            u"",
            0x00C00080, 0x01FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENLODIVADCCLK = RM_Field_RAC_NS_SYLOEN_SYENLODIVADCCLK(self)
        self.zz_fdict['SYENLODIVADCCLK'] = self.SYENLODIVADCCLK
        self.SYENLODIVFCAL = RM_Field_RAC_NS_SYLOEN_SYENLODIVFCAL(self)
        self.zz_fdict['SYENLODIVFCAL'] = self.SYENLODIVFCAL
        self.SYENLODIVHADMDIV = RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMDIV(self)
        self.zz_fdict['SYENLODIVHADMDIV'] = self.SYENLODIVHADMDIV
        self.SYENLODIVHADMLO = RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMLO(self)
        self.zz_fdict['SYENLODIVHADMLO'] = self.SYENLODIVHADMLO
        self.SYENLODIVHADMRXLO = RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMRXLO(self)
        self.zz_fdict['SYENLODIVHADMRXLO'] = self.SYENLODIVHADMRXLO
        self.SYENLODIVHADMTXLO = RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMTXLO(self)
        self.zz_fdict['SYENLODIVHADMTXLO'] = self.SYENLODIVHADMTXLO
        self.SYENLODIVREGREPLICA = RM_Field_RAC_NS_SYLOEN_SYENLODIVREGREPLICA(self)
        self.zz_fdict['SYENLODIVREGREPLICA'] = self.SYENLODIVREGREPLICA
        self.SYENLODIVREGFORCEDSTARTUP = RM_Field_RAC_NS_SYLOEN_SYENLODIVREGFORCEDSTARTUP(self)
        self.zz_fdict['SYENLODIVREGFORCEDSTARTUP'] = self.SYENLODIVREGFORCEDSTARTUP
        self.SYENLODIVREGBIAS = RM_Field_RAC_NS_SYLOEN_SYENLODIVREGBIAS(self)
        self.zz_fdict['SYENLODIVREGBIAS'] = self.SYENLODIVREGBIAS
        self.SYENLODIVREG = RM_Field_RAC_NS_SYLOEN_SYENLODIVREG(self)
        self.zz_fdict['SYENLODIVREG'] = self.SYENLODIVREG
        self.SYENLODIVLPRXLO = RM_Field_RAC_NS_SYLOEN_SYENLODIVLPRXLO(self)
        self.zz_fdict['SYENLODIVLPRXLO'] = self.SYENLODIVLPRXLO
        self.SYENLODIVLPRXDIV = RM_Field_RAC_NS_SYLOEN_SYENLODIVLPRXDIV(self)
        self.zz_fdict['SYENLODIVLPRXDIV'] = self.SYENLODIVLPRXDIV
        self.SYENLODIVIQCLKBIAS = RM_Field_RAC_NS_SYLOEN_SYENLODIVIQCLKBIAS(self)
        self.zz_fdict['SYENLODIVIQCLKBIAS'] = self.SYENLODIVIQCLKBIAS
        self.SYENLODIVDIVSE = RM_Field_RAC_NS_SYLOEN_SYENLODIVDIVSE(self)
        self.zz_fdict['SYENLODIVDIVSE'] = self.SYENLODIVDIVSE
        self.SYENLODIVDSMDACCLK = RM_Field_RAC_NS_SYLOEN_SYENLODIVDSMDACCLK(self)
        self.zz_fdict['SYENLODIVDSMDACCLK'] = self.SYENLODIVDSMDACCLK
        self.SYENLODIVFPSRC2G4 = RM_Field_RAC_NS_SYLOEN_SYENLODIVFPSRC2G4(self)
        self.zz_fdict['SYENLODIVFPSRC2G4'] = self.SYENLODIVFPSRC2G4
        self.SYENLODIVREGSTBLOAD = RM_Field_RAC_NS_SYLOEN_SYENLODIVREGSTBLOAD(self)
        self.zz_fdict['SYENLODIVREGSTBLOAD'] = self.SYENLODIVREGSTBLOAD
        self.SYENLODIVSECLKBIAS = RM_Field_RAC_NS_SYLOEN_SYENLODIVSECLKBIAS(self)
        self.zz_fdict['SYENLODIVSECLKBIAS'] = self.SYENLODIVSECLKBIAS
        self.SYENLODIVSMUXCLK = RM_Field_RAC_NS_SYLOEN_SYENLODIVSMUXCLK(self)
        self.zz_fdict['SYENLODIVSMUXCLK'] = self.SYENLODIVSMUXCLK
        self.SYENLODIVTXRF0DBM = RM_Field_RAC_NS_SYLOEN_SYENLODIVTXRF0DBM(self)
        self.zz_fdict['SYENLODIVTXRF0DBM'] = self.SYENLODIVTXRF0DBM
        self.SYENMMDREG = RM_Field_RAC_NS_SYLOEN_SYENMMDREG(self)
        self.zz_fdict['SYENMMDREG'] = self.SYENMMDREG
        self.SYENMMDCLKINJXO = RM_Field_RAC_NS_SYLOEN_SYENMMDCLKINJXO(self)
        self.zz_fdict['SYENMMDCLKINJXO'] = self.SYENMMDCLKINJXO
        self.SYENDTCCORE = RM_Field_RAC_NS_SYLOEN_SYENDTCCORE(self)
        self.zz_fdict['SYENDTCCORE'] = self.SYENDTCCORE
        self.SYENDTCREG = RM_Field_RAC_NS_SYLOEN_SYENDTCREG(self)
        self.zz_fdict['SYENDTCREG'] = self.SYENDTCREG
        self.SYENMMDAQNC = RM_Field_RAC_NS_SYLOEN_SYENMMDAQNC(self)
        self.zz_fdict['SYENMMDAQNC'] = self.SYENMMDAQNC
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYMMDCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYMMDCTRL, self).__init__(rmio, label,
            0xb8020000, 0x188,
            'SYMMDCTRL', 'RAC_NS.SYMMDCTRL', 'read-write',
            u"",
            0x00000000, 0x00000002,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYMMDPHISEL = RM_Field_RAC_NS_SYMMDCTRL_SYMMDPHISEL(self)
        self.zz_fdict['SYMMDPHISEL'] = self.SYMMDPHISEL
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
            0x00000000, 0x1FFFFFFF,
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
        self.ENMANTIACOMP = RM_Field_RAC_NS_AGCOVERWRITE0_ENMANTIACOMP(self)
        self.zz_fdict['ENMANTIACOMP'] = self.ENMANTIACOMP
        self.MANTIACOMP = RM_Field_RAC_NS_AGCOVERWRITE0_MANTIACOMP(self)
        self.zz_fdict['MANTIACOMP'] = self.MANTIACOMP
        self.MANPGAGAIN = RM_Field_RAC_NS_AGCOVERWRITE0_MANPGAGAIN(self)
        self.zz_fdict['MANPGAGAIN'] = self.MANPGAGAIN
        self.MANIFADCSCALE = RM_Field_RAC_NS_AGCOVERWRITE0_MANIFADCSCALE(self)
        self.zz_fdict['MANIFADCSCALE'] = self.MANIFADCSCALE
        self.ENMANLNAMIXCUREN = RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXCUREN(self)
        self.zz_fdict['ENMANLNAMIXCUREN'] = self.ENMANLNAMIXCUREN
        self.MANLNAMIXCUREN0 = RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXCUREN0(self)
        self.zz_fdict['MANLNAMIXCUREN0'] = self.MANLNAMIXCUREN0
        self.MANLNAMIXCUREN1 = RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXCUREN1(self)
        self.zz_fdict['MANLNAMIXCUREN1'] = self.MANLNAMIXCUREN1
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


class RM_Register_RAC_NS_SPARE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SPARE, self).__init__(rmio, label,
            0xb8020000, 0x1C4,
            'SPARE', 'RAC_NS.SPARE', 'read-write',
            u"",
            0x00000000, 0x3FFFFF0F,
            0x00001000, 0x00002000,
            0x00003000)

        self.CLKMULTSPARE = RM_Field_RAC_NS_SPARE_CLKMULTSPARE(self)
        self.zz_fdict['CLKMULTSPARE'] = self.CLKMULTSPARE
        self.MIXDACTRIMSPAREVREGCORE = RM_Field_RAC_NS_SPARE_MIXDACTRIMSPAREVREGCORE(self)
        self.zz_fdict['MIXDACTRIMSPAREVREGCORE'] = self.MIXDACTRIMSPAREVREGCORE
        self.MIXDACTRIMSPARE02 = RM_Field_RAC_NS_SPARE_MIXDACTRIMSPARE02(self)
        self.zz_fdict['MIXDACTRIMSPARE02'] = self.MIXDACTRIMSPARE02
        self.MIXDACTRIMSPARE01 = RM_Field_RAC_NS_SPARE_MIXDACTRIMSPARE01(self)
        self.zz_fdict['MIXDACTRIMSPARE01'] = self.MIXDACTRIMSPARE01
        self.MIXDACENSPARE02 = RM_Field_RAC_NS_SPARE_MIXDACENSPARE02(self)
        self.zz_fdict['MIXDACENSPARE02'] = self.MIXDACENSPARE02
        self.MIXDACTRIMSPAREVREGDIG = RM_Field_RAC_NS_SPARE_MIXDACTRIMSPAREVREGDIG(self)
        self.zz_fdict['MIXDACTRIMSPAREVREGDIG'] = self.MIXDACTRIMSPAREVREGDIG
        self.MIXDACENSPARE01 = RM_Field_RAC_NS_SPARE_MIXDACENSPARE01(self)
        self.zz_fdict['MIXDACENSPARE01'] = self.MIXDACENSPARE01
        self.SYLODIVSPARES = RM_Field_RAC_NS_SPARE_SYLODIVSPARES(self)
        self.zz_fdict['SYLODIVSPARES'] = self.SYLODIVSPARES
        self.SYMMDSPARES = RM_Field_RAC_NS_SPARE_SYMMDSPARES(self)
        self.zz_fdict['SYMMDSPARES'] = self.SYMMDSPARES
        self.SYVCOSPARES = RM_Field_RAC_NS_SPARE_SYVCOSPARES(self)
        self.zz_fdict['SYVCOSPARES'] = self.SYVCOSPARES
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PACTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PACTRL, self).__init__(rmio, label,
            0xb8020000, 0x1C8,
            'PACTRL', 'RAC_NS.PACTRL', 'read-write',
            u"",
            0x00000000, 0x0000F0F0,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXPAPOWER = RM_Field_RAC_NS_PACTRL_TXPAPOWER(self)
        self.zz_fdict['TXPAPOWER'] = self.TXPAPOWER
        self.TXPASELSLICE = RM_Field_RAC_NS_PACTRL_TXPASELSLICE(self)
        self.zz_fdict['TXPASELSLICE'] = self.TXPASELSLICE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYDLFKI(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYDLFKI, self).__init__(rmio, label,
            0xb8020000, 0x1CC,
            'SYDLFKI', 'RAC_NS.SYDLFKI', 'read-write',
            u"",
            0x000186A0, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFLPFBWKI = RM_Field_RAC_NS_SYDLFKI_SYDLFLPFBWKI(self)
        self.zz_fdict['SYDLFLPFBWKI'] = self.SYDLFLPFBWKI
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYDLFKF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYDLFKF, self).__init__(rmio, label,
            0xb8020000, 0x1D0,
            'SYDLFKF', 'RAC_NS.SYDLFKF', 'read-write',
            u"",
            0x000F4240, 0x003FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFLPFBWKF = RM_Field_RAC_NS_SYDLFKF_SYDLFLPFBWKF(self)
        self.zz_fdict['SYDLFLPFBWKF'] = self.SYDLFLPFBWKF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_MIXDACTRIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_MIXDACTRIM, self).__init__(rmio, label,
            0xb8020000, 0x1D4,
            'MIXDACTRIM', 'RAC_NS.MIXDACTRIM', 'read-write',
            u"",
            0x05145B8F, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MIXDACTRIMBBFILTERRES = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMBBFILTERRES(self)
        self.zz_fdict['MIXDACTRIMBBFILTERRES'] = self.MIXDACTRIMBBFILTERRES
        self.MIXDACTRIMLOBIASNMOS = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMLOBIASNMOS(self)
        self.zz_fdict['MIXDACTRIMLOBIASNMOS'] = self.MIXDACTRIMLOBIASNMOS
        self.MIXDACTRIMLOBIASPMOS = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMLOBIASPMOS(self)
        self.zz_fdict['MIXDACTRIMLOBIASPMOS'] = self.MIXDACTRIMLOBIASPMOS
        self.MIXDACTRIMNDACCASC = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMNDACCASC(self)
        self.zz_fdict['MIXDACTRIMNDACCASC'] = self.MIXDACTRIMNDACCASC
        self.MIXDACTRIMPDACCASC = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMPDACCASC(self)
        self.zz_fdict['MIXDACTRIMPDACCASC'] = self.MIXDACTRIMPDACCASC
        self.MIXDACTRIMREFCURRENT = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMREFCURRENT(self)
        self.zz_fdict['MIXDACTRIMREFCURRENT'] = self.MIXDACTRIMREFCURRENT
        self.MIXDACTRIMVREGCORE = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGCORE(self)
        self.zz_fdict['MIXDACTRIMVREGCORE'] = self.MIXDACTRIMVREGCORE
        self.MIXDACTRIMVREGCOREVREF = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGCOREVREF(self)
        self.zz_fdict['MIXDACTRIMVREGCOREVREF'] = self.MIXDACTRIMVREGCOREVREF
        self.MIXDACTRIMVREGDIG = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGDIG(self)
        self.zz_fdict['MIXDACTRIMVREGDIG'] = self.MIXDACTRIMVREGDIG
        self.MIXDACTRIMVREGDIGVREF = RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGDIGVREF(self)
        self.zz_fdict['MIXDACTRIMVREGDIGVREF'] = self.MIXDACTRIMVREGDIGVREF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYTRIM2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYTRIM2, self).__init__(rmio, label,
            0xb8020000, 0x1DC,
            'SYTRIM2', 'RAC_NS.SYTRIM2', 'read-write',
            u"",
            0x00041108, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYTDCTRIMDLYSTOPRING = RM_Field_RAC_NS_SYTRIM2_SYTDCTRIMDLYSTOPRING(self)
        self.zz_fdict['SYTDCTRIMDLYSTOPRING'] = self.SYTDCTRIMDLYSTOPRING
        self.SYMMDREGTRIMVREG = RM_Field_RAC_NS_SYTRIM2_SYMMDREGTRIMVREG(self)
        self.zz_fdict['SYMMDREGTRIMVREG'] = self.SYMMDREGTRIMVREG
        self.SYDTCCOFFSETTRIM = RM_Field_RAC_NS_SYTRIM2_SYDTCCOFFSETTRIM(self)
        self.zz_fdict['SYDTCCOFFSETTRIM'] = self.SYDTCCOFFSETTRIM
        self.SYDTCREGTRIMVTTRACK = RM_Field_RAC_NS_SYTRIM2_SYDTCREGTRIMVTTRACK(self)
        self.zz_fdict['SYDTCREGTRIMVTTRACK'] = self.SYDTCREGTRIMVTTRACK
        self.SYTDCTRIMPERLOAD = RM_Field_RAC_NS_SYTRIM2_SYTDCTRIMPERLOAD(self)
        self.zz_fdict['SYTDCTRIMPERLOAD'] = self.SYTDCTRIMPERLOAD
        self.SYVCOREGTRIMVREF = RM_Field_RAC_NS_SYTRIM2_SYVCOREGTRIMVREF(self)
        self.zz_fdict['SYVCOREGTRIMVREF'] = self.SYVCOREGTRIMVREF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYDLFCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYDLFCTRL1, self).__init__(rmio, label,
            0xb8020000, 0x1E4,
            'SYDLFCTRL1', 'RAC_NS.SYDLFCTRL1', 'read-write',
            u"",
            0x00000000, 0x0001FF0E,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFVCTRLLOTH = RM_Field_RAC_NS_SYDLFCTRL1_SYDLFVCTRLLOTH(self)
        self.zz_fdict['SYDLFVCTRLLOTH'] = self.SYDLFVCTRLLOTH
        self.SYDLFTDCA2 = RM_Field_RAC_NS_SYDLFCTRL1_SYDLFTDCA2(self)
        self.zz_fdict['SYDLFTDCA2'] = self.SYDLFTDCA2
        self.SYDLFVCTRLCMPRESET = RM_Field_RAC_NS_SYDLFCTRL1_SYDLFVCTRLCMPRESET(self)
        self.zz_fdict['SYDLFVCTRLCMPRESET'] = self.SYDLFVCTRLCMPRESET
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYSTATUS, self).__init__(rmio, label,
            0xb8020000, 0x1E8,
            'SYSTATUS', 'RAC_NS.SYSTATUS', 'read-only',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFSTATE = RM_Field_RAC_NS_SYSTATUS_SYDLFSTATE(self)
        self.zz_fdict['SYDLFSTATE'] = self.SYDLFSTATE
        self.SYDLFLMSP0M = RM_Field_RAC_NS_SYSTATUS_SYDLFLMSP0M(self)
        self.zz_fdict['SYDLFLMSP0M'] = self.SYDLFLMSP0M
        self.SYDLFVCTRLHI = RM_Field_RAC_NS_SYSTATUS_SYDLFVCTRLHI(self)
        self.zz_fdict['SYDLFVCTRLHI'] = self.SYDLFVCTRLHI
        self.SYDLFVCTRLLO = RM_Field_RAC_NS_SYSTATUS_SYDLFVCTRLLO(self)
        self.zz_fdict['SYDLFVCTRLLO'] = self.SYDLFVCTRLLO
        self.SYDLFPFDLOCKSAMPLE = RM_Field_RAC_NS_SYSTATUS_SYDLFPFDLOCKSAMPLE(self)
        self.zz_fdict['SYDLFPFDLOCKSAMPLE'] = self.SYDLFPFDLOCKSAMPLE
        self.SYDLFPFDREFLEAD = RM_Field_RAC_NS_SYSTATUS_SYDLFPFDREFLEAD(self)
        self.zz_fdict['SYDLFPFDREFLEAD'] = self.SYDLFPFDREFLEAD
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYCTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYCTRL2, self).__init__(rmio, label,
            0xb8020000, 0x1EC,
            'SYCTRL2', 'RAC_NS.SYCTRL2', 'read-write',
            u"",
            0x00018028, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDTCREGILOAD = RM_Field_RAC_NS_SYCTRL2_SYDTCREGILOAD(self)
        self.zz_fdict['SYDTCREGILOAD'] = self.SYDTCREGILOAD
        self.SYDTCREGVTTRACKSEL = RM_Field_RAC_NS_SYCTRL2_SYDTCREGVTTRACKSEL(self)
        self.zz_fdict['SYDTCREGVTTRACKSEL'] = self.SYDTCREGVTTRACKSEL
        self.SYLODIVBYPASSIQCLKBIASDELTA = RM_Field_RAC_NS_SYCTRL2_SYLODIVBYPASSIQCLKBIASDELTA(self)
        self.zz_fdict['SYLODIVBYPASSIQCLKBIASDELTA'] = self.SYLODIVBYPASSIQCLKBIASDELTA
        self.SYDSMDACREGTRIMSTBLOAD = RM_Field_RAC_NS_SYCTRL2_SYDSMDACREGTRIMSTBLOAD(self)
        self.zz_fdict['SYDSMDACREGTRIMSTBLOAD'] = self.SYDSMDACREGTRIMSTBLOAD
        self.SYLODIVTRIMIQCLKBIASDELTA = RM_Field_RAC_NS_SYCTRL2_SYLODIVTRIMIQCLKBIASDELTA(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASDELTA'] = self.SYLODIVTRIMIQCLKBIASDELTA
        self.SYLODIVTRIMIQCLKBIASNDIO = RM_Field_RAC_NS_SYCTRL2_SYLODIVTRIMIQCLKBIASNDIO(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASNDIO'] = self.SYLODIVTRIMIQCLKBIASNDIO
        self.SYVCOHCAP = RM_Field_RAC_NS_SYCTRL2_SYVCOHCAP(self)
        self.zz_fdict['SYVCOHCAP'] = self.SYVCOHCAP
        self.SYVCOACAP = RM_Field_RAC_NS_SYCTRL2_SYVCOACAP(self)
        self.zz_fdict['SYVCOACAP'] = self.SYVCOACAP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TIATRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TIATRIM0, self).__init__(rmio, label,
            0xb8020000, 0x1F0,
            'TIATRIM0', 'RAC_NS.TIATRIM0', 'read-write',
            u"",
            0x00000000, 0x03FFF800,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIACAPFB = RM_Field_RAC_NS_TIATRIM0_TIACAPFB(self)
        self.zz_fdict['TIACAPFB'] = self.TIACAPFB
        self.TIACOMP = RM_Field_RAC_NS_TIATRIM0_TIACOMP(self)
        self.zz_fdict['TIACOMP'] = self.TIACOMP
        self.TIARESFB = RM_Field_RAC_NS_TIATRIM0_TIARESFB(self)
        self.zz_fdict['TIARESFB'] = self.TIARESFB
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TIATRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TIATRIM1, self).__init__(rmio, label,
            0xb8020000, 0x1F4,
            'TIATRIM1', 'RAC_NS.TIATRIM1', 'read-write',
            u"",
            0x00008000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIAOXI = RM_Field_RAC_NS_TIATRIM1_TIAOXI(self)
        self.zz_fdict['TIAOXI'] = self.TIAOXI
        self.TIAOXQ = RM_Field_RAC_NS_TIATRIM1_TIAOXQ(self)
        self.zz_fdict['TIAOXQ'] = self.TIAOXQ
        self.TIASETVCM = RM_Field_RAC_NS_TIATRIM1_TIASETVCM(self)
        self.zz_fdict['TIASETVCM'] = self.TIASETVCM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TIAEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TIAEN, self).__init__(rmio, label,
            0xb8020000, 0x1F8,
            'TIAEN', 'RAC_NS.TIAEN', 'read-write',
            u"",
            0x06001008, 0x07FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIAENBIAS = RM_Field_RAC_NS_TIAEN_TIAENBIAS(self)
        self.zz_fdict['TIAENBIAS'] = self.TIAENBIAS
        self.TIABIASCURR = RM_Field_RAC_NS_TIAEN_TIABIASCURR(self)
        self.zz_fdict['TIABIASCURR'] = self.TIABIASCURR
        self.TIAENREG = RM_Field_RAC_NS_TIAEN_TIAENREG(self)
        self.zz_fdict['TIAENREG'] = self.TIAENREG
        self.TIAENSTBLOAD = RM_Field_RAC_NS_TIAEN_TIAENSTBLOAD(self)
        self.zz_fdict['TIAENSTBLOAD'] = self.TIAENSTBLOAD
        self.TIAENLATCHI = RM_Field_RAC_NS_TIAEN_TIAENLATCHI(self)
        self.zz_fdict['TIAENLATCHI'] = self.TIAENLATCHI
        self.TIAENPKD = RM_Field_RAC_NS_TIAEN_TIAENPKD(self)
        self.zz_fdict['TIAENPKD'] = self.TIAENPKD
        self.TIAENLATCHQ = RM_Field_RAC_NS_TIAEN_TIAENLATCHQ(self)
        self.zz_fdict['TIAENLATCHQ'] = self.TIAENLATCHQ
        self.TIAVLDOTRIMVREF = RM_Field_RAC_NS_TIAEN_TIAVLDOTRIMVREF(self)
        self.zz_fdict['TIAVLDOTRIMVREF'] = self.TIAVLDOTRIMVREF
        self.TIAENTIAI = RM_Field_RAC_NS_TIAEN_TIAENTIAI(self)
        self.zz_fdict['TIAENTIAI'] = self.TIAENTIAI
        self.TIAENTIAQ = RM_Field_RAC_NS_TIAEN_TIAENTIAQ(self)
        self.zz_fdict['TIAENTIAQ'] = self.TIAENTIAQ
        self.TIATHRPKDLOSEL = RM_Field_RAC_NS_TIAEN_TIATHRPKDLOSEL(self)
        self.zz_fdict['TIATHRPKDLOSEL'] = self.TIATHRPKDLOSEL
        self.TIATHRPKDHISEL = RM_Field_RAC_NS_TIAEN_TIATHRPKDHISEL(self)
        self.zz_fdict['TIATHRPKDHISEL'] = self.TIATHRPKDHISEL
        self.TIAVLDOTRIMVREG = RM_Field_RAC_NS_TIAEN_TIAVLDOTRIMVREG(self)
        self.zz_fdict['TIAVLDOTRIMVREG'] = self.TIAVLDOTRIMVREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_VTRCTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_VTRCTRL0, self).__init__(rmio, label,
            0xb8020000, 0x1FC,
            'VTRCTRL0', 'RAC_NS.VTRCTRL0', 'read-write',
            u"",
            0x02010C20, 0x07FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VTRCALBIAS = RM_Field_RAC_NS_VTRCTRL0_VTRCALBIAS(self)
        self.zz_fdict['VTRCALBIAS'] = self.VTRCALBIAS
        self.VTRCALTC = RM_Field_RAC_NS_VTRCTRL0_VTRCALTC(self)
        self.zz_fdict['VTRCALTC'] = self.VTRCALTC
        self.VTRDISABLEBOOTSTRAP = RM_Field_RAC_NS_VTRCTRL0_VTRDISABLEBOOTSTRAP(self)
        self.zz_fdict['VTRDISABLEBOOTSTRAP'] = self.VTRDISABLEBOOTSTRAP
        self.VTREN = RM_Field_RAC_NS_VTRCTRL0_VTREN(self)
        self.zz_fdict['VTREN'] = self.VTREN
        self.VTRLDOVREFTRIM = RM_Field_RAC_NS_VTRCTRL0_VTRLDOVREFTRIM(self)
        self.zz_fdict['VTRLDOVREFTRIM'] = self.VTRLDOVREFTRIM
        self.VTRSTARTUPCORE = RM_Field_RAC_NS_VTRCTRL0_VTRSTARTUPCORE(self)
        self.zz_fdict['VTRSTARTUPCORE'] = self.VTRSTARTUPCORE
        self.VTRSTARTUPSUPPLY = RM_Field_RAC_NS_VTRCTRL0_VTRSTARTUPSUPPLY(self)
        self.zz_fdict['VTRSTARTUPSUPPLY'] = self.VTRSTARTUPSUPPLY
        self.VTRCALVREF = RM_Field_RAC_NS_VTRCTRL0_VTRCALVREF(self)
        self.zz_fdict['VTRCALVREF'] = self.VTRCALVREF
        self.VTRHIGHCURRENTHV = RM_Field_RAC_NS_VTRCTRL0_VTRHIGHCURRENTHV(self)
        self.zz_fdict['VTRHIGHCURRENTHV'] = self.VTRHIGHCURRENTHV
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCCAL, self).__init__(rmio, label,
            0xb8020000, 0x200,
            'AUXADCCAL', 'RAC_NS.AUXADCCAL', 'read-write',
            u"",
            0x00391A1C, 0x007FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCLDOSHUNTCURLVL1 = RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTCURLVL1(self)
        self.zz_fdict['ADCLDOSHUNTCURLVL1'] = self.ADCLDOSHUNTCURLVL1
        self.ADCLDOSERIESAMPLVL = RM_Field_RAC_NS_AUXADCCAL_ADCLDOSERIESAMPLVL(self)
        self.zz_fdict['ADCLDOSERIESAMPLVL'] = self.ADCLDOSERIESAMPLVL
        self.ADCLDOSERIESAMPLVL2 = RM_Field_RAC_NS_AUXADCCAL_ADCLDOSERIESAMPLVL2(self)
        self.zz_fdict['ADCLDOSERIESAMPLVL2'] = self.ADCLDOSERIESAMPLVL2
        self.ADCLDOSHUNTAMPLVL1 = RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTAMPLVL1(self)
        self.zz_fdict['ADCLDOSHUNTAMPLVL1'] = self.ADCLDOSHUNTAMPLVL1
        self.ADCLDOSHUNTAMPLVL2 = RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTAMPLVL2(self)
        self.zz_fdict['ADCLDOSHUNTAMPLVL2'] = self.ADCLDOSHUNTAMPLVL2
        self.ADCSIDETONEFREQ = RM_Field_RAC_NS_AUXADCCAL_ADCSIDETONEFREQ(self)
        self.zz_fdict['ADCSIDETONEFREQ'] = self.ADCSIDETONEFREQ
        self.ADCTRIMCURRINPUTBUF = RM_Field_RAC_NS_AUXADCCAL_ADCTRIMCURRINPUTBUF(self)
        self.zz_fdict['ADCTRIMCURRINPUTBUF'] = self.ADCTRIMCURRINPUTBUF
        self.ADCVCMLVL = RM_Field_RAC_NS_AUXADCCAL_ADCVCMLVL(self)
        self.zz_fdict['ADCVCMLVL'] = self.ADCVCMLVL
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCCTRL, self).__init__(rmio, label,
            0xb8020000, 0x204,
            'AUXADCCTRL', 'RAC_NS.AUXADCCTRL', 'read-write',
            u"",
            0x60008B00, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCCTRLRESERVED = RM_Field_RAC_NS_AUXADCCTRL_ADCCTRLRESERVED(self)
        self.zz_fdict['ADCCTRLRESERVED'] = self.ADCCTRLRESERVED
        self.ADCCTRLRESERVEDLV = RM_Field_RAC_NS_AUXADCCTRL_ADCCTRLRESERVEDLV(self)
        self.zz_fdict['ADCCTRLRESERVEDLV'] = self.ADCCTRLRESERVEDLV
        self.ADCLOWCUR = RM_Field_RAC_NS_AUXADCCTRL_ADCLOWCUR(self)
        self.zz_fdict['ADCLOWCUR'] = self.ADCLOWCUR
        self.ADCNEGRESCURRENT = RM_Field_RAC_NS_AUXADCCTRL_ADCNEGRESCURRENT(self)
        self.zz_fdict['ADCNEGRESCURRENT'] = self.ADCNEGRESCURRENT
        self.ADCNEGRESVCM = RM_Field_RAC_NS_AUXADCCTRL_ADCNEGRESVCM(self)
        self.zz_fdict['ADCNEGRESVCM'] = self.ADCNEGRESVCM
        self.ADCOTACURRENT = RM_Field_RAC_NS_AUXADCCTRL_ADCOTACURRENT(self)
        self.zz_fdict['ADCOTACURRENT'] = self.ADCOTACURRENT
        self.ADCPMONSELECT = RM_Field_RAC_NS_AUXADCCTRL_ADCPMONSELECT(self)
        self.zz_fdict['ADCPMONSELECT'] = self.ADCPMONSELECT
        self.ADCRCCALCOUNTERSTARTVAL = RM_Field_RAC_NS_AUXADCCTRL_ADCRCCALCOUNTERSTARTVAL(self)
        self.zz_fdict['ADCRCCALCOUNTERSTARTVAL'] = self.ADCRCCALCOUNTERSTARTVAL
        self.ADCSHORTINPUT = RM_Field_RAC_NS_AUXADCCTRL_ADCSHORTINPUT(self)
        self.zz_fdict['ADCSHORTINPUT'] = self.ADCSHORTINPUT
        self.ADCSETVINCM400M = RM_Field_RAC_NS_AUXADCCTRL_ADCSETVINCM400M(self)
        self.zz_fdict['ADCSETVINCM400M'] = self.ADCSETVINCM400M
        self.ADCVCMBUFBYPASS = RM_Field_RAC_NS_AUXADCCTRL_ADCVCMBUFBYPASS(self)
        self.zz_fdict['ADCVCMBUFBYPASS'] = self.ADCVCMBUFBYPASS
        self.ADCLDOSERIESFORCEDSTARTUP = RM_Field_RAC_NS_AUXADCCTRL_ADCLDOSERIESFORCEDSTARTUP(self)
        self.zz_fdict['ADCLDOSERIESFORCEDSTARTUP'] = self.ADCLDOSERIESFORCEDSTARTUP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_AUXADCCTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_AUXADCCTRL2, self).__init__(rmio, label,
            0xb8020000, 0x208,
            'AUXADCCTRL2', 'RAC_NS.AUXADCCTRL2', 'read-write',
            u"",
            0x00000000, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADCENHALFBW = RM_Field_RAC_NS_AUXADCCTRL2_ADCENHALFBW(self)
        self.zz_fdict['ADCENHALFBW'] = self.ADCENHALFBW
        self.ADCENHALFMODE = RM_Field_RAC_NS_AUXADCCTRL2_ADCENHALFMODE(self)
        self.zz_fdict['ADCENHALFMODE'] = self.ADCENHALFMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_LNAMIXEN0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_LNAMIXEN0, self).__init__(rmio, label,
            0xb8020000, 0x20C,
            'LNAMIXEN0', 'RAC_NS.LNAMIXEN0', 'read-write',
            u"",
            0x00000000, 0x00000007,
            0x00001000, 0x00002000,
            0x00003000)

        self.LNAMIXDISMXR1 = RM_Field_RAC_NS_LNAMIXEN0_LNAMIXDISMXR1(self)
        self.zz_fdict['LNAMIXDISMXR1'] = self.LNAMIXDISMXR1
        self.LNAMIXENIRCAL1 = RM_Field_RAC_NS_LNAMIXEN0_LNAMIXENIRCAL1(self)
        self.zz_fdict['LNAMIXENIRCAL1'] = self.LNAMIXENIRCAL1
        self.LNAMIXENREG = RM_Field_RAC_NS_LNAMIXEN0_LNAMIXENREG(self)
        self.zz_fdict['LNAMIXENREG'] = self.LNAMIXENREG
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_MIXDACEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_MIXDACEN, self).__init__(rmio, label,
            0xb8020000, 0x210,
            'MIXDACEN', 'RAC_NS.MIXDACEN', 'read-write',
            u"",
            0x00000000, 0x00033FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MIXDACEN0DBMPA = RM_Field_RAC_NS_MIXDACEN_MIXDACEN0DBMPA(self)
        self.zz_fdict['MIXDACEN0DBMPA'] = self.MIXDACEN0DBMPA
        self.MIXDACENBIASVREGDIG = RM_Field_RAC_NS_MIXDACEN_MIXDACENBIASVREGDIG(self)
        self.zz_fdict['MIXDACENBIASVREGDIG'] = self.MIXDACENBIASVREGDIG
        self.MIXDACEN10DBMPA = RM_Field_RAC_NS_MIXDACEN_MIXDACEN10DBMPA(self)
        self.zz_fdict['MIXDACEN10DBMPA'] = self.MIXDACEN10DBMPA
        self.MIXDACENCLKMULT2P4G = RM_Field_RAC_NS_MIXDACEN_MIXDACENCLKMULT2P4G(self)
        self.zz_fdict['MIXDACENCLKMULT2P4G'] = self.MIXDACENCLKMULT2P4G
        self.MIXDACENCORE = RM_Field_RAC_NS_MIXDACEN_MIXDACENCORE(self)
        self.zz_fdict['MIXDACENCORE'] = self.MIXDACENCORE
        self.MIXDACENSTBLOADVREGCORE = RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGCORE(self)
        self.zz_fdict['MIXDACENSTBLOADVREGCORE'] = self.MIXDACENSTBLOADVREGCORE
        self.MIXDACENSTBLOADVREGDIG = RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGDIG(self)
        self.zz_fdict['MIXDACENSTBLOADVREGDIG'] = self.MIXDACENSTBLOADVREGDIG
        self.MIXDACENBIASVREGCORE = RM_Field_RAC_NS_MIXDACEN_MIXDACENBIASVREGCORE(self)
        self.zz_fdict['MIXDACENBIASVREGCORE'] = self.MIXDACENBIASVREGCORE
        self.MIXDACENVREGCORE = RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGCORE(self)
        self.zz_fdict['MIXDACENVREGCORE'] = self.MIXDACENVREGCORE
        self.MIXDACENVREGDIG = RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGDIG(self)
        self.zz_fdict['MIXDACENVREGDIG'] = self.MIXDACENVREGDIG
        self.MIXDACENFORCEDSTARTUPVREGDIG = RM_Field_RAC_NS_MIXDACEN_MIXDACENFORCEDSTARTUPVREGDIG(self)
        self.zz_fdict['MIXDACENFORCEDSTARTUPVREGDIG'] = self.MIXDACENFORCEDSTARTUPVREGDIG
        self.MIXDACENIRCAL = RM_Field_RAC_NS_MIXDACEN_MIXDACENIRCAL(self)
        self.zz_fdict['MIXDACENIRCAL'] = self.MIXDACENIRCAL
        self.MIXDACENPOSEDGEDACCLK = RM_Field_RAC_NS_MIXDACEN_MIXDACENPOSEDGEDACCLK(self)
        self.zz_fdict['MIXDACENPOSEDGEDACCLK'] = self.MIXDACENPOSEDGEDACCLK
        self.MIXDACENRFSYNTH = RM_Field_RAC_NS_MIXDACEN_MIXDACENRFSYNTH(self)
        self.zz_fdict['MIXDACENRFSYNTH'] = self.MIXDACENRFSYNTH
        self.MIXDACENSTBLOADVREGDIGREPLICA = RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGDIGREPLICA(self)
        self.zz_fdict['MIXDACENSTBLOADVREGDIGREPLICA'] = self.MIXDACENSTBLOADVREGDIGREPLICA
        self.MIXDACENVREGDIGREPLICA = RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGDIGREPLICA(self)
        self.zz_fdict['MIXDACENVREGDIGREPLICA'] = self.MIXDACENVREGDIGREPLICA
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYCTRL1, self).__init__(rmio, label,
            0xb8020000, 0x214,
            'SYCTRL1', 'RAC_NS.SYCTRL1', 'read-write',
            u"",
            0x02605048, 0xFFFBFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYENDLFVCTRLMONITOR = RM_Field_RAC_NS_SYCTRL1_SYENDLFVCTRLMONITOR(self)
        self.zz_fdict['SYENDLFVCTRLMONITOR'] = self.SYENDLFVCTRLMONITOR
        self.SYENDLFTDCA2 = RM_Field_RAC_NS_SYCTRL1_SYENDLFTDCA2(self)
        self.zz_fdict['SYENDLFTDCA2'] = self.SYENDLFTDCA2
        self.SYMMDSELFP4G82G4 = RM_Field_RAC_NS_SYCTRL1_SYMMDSELFP4G82G4(self)
        self.zz_fdict['SYMMDSELFP4G82G4'] = self.SYMMDSELFP4G82G4
        self.SYLODIVREGTRIMVREF = RM_Field_RAC_NS_SYCTRL1_SYLODIVREGTRIMVREF(self)
        self.zz_fdict['SYLODIVREGTRIMVREF'] = self.SYLODIVREGTRIMVREF
        self.SYDSMDACREGILOAD = RM_Field_RAC_NS_SYCTRL1_SYDSMDACREGILOAD(self)
        self.zz_fdict['SYDSMDACREGILOAD'] = self.SYDSMDACREGILOAD
        self.SYLODIVSELFCALCLK = RM_Field_RAC_NS_SYCTRL1_SYLODIVSELFCALCLK(self)
        self.zz_fdict['SYLODIVSELFCALCLK'] = self.SYLODIVSELFCALCLK
        self.SYENDLF = RM_Field_RAC_NS_SYCTRL1_SYENDLF(self)
        self.zz_fdict['SYENDLF'] = self.SYENDLF
        self.SYLODIVFCALRD = RM_Field_RAC_NS_SYCTRL1_SYLODIVFCALRD(self)
        self.zz_fdict['SYLODIVFCALRD'] = self.SYLODIVFCALRD
        self.SYVCOACAPFORCE = RM_Field_RAC_NS_SYCTRL1_SYVCOACAPFORCE(self)
        self.zz_fdict['SYVCOACAPFORCE'] = self.SYVCOACAPFORCE
        self.SYLODIVDSMDACCLKDIVRATIO = RM_Field_RAC_NS_SYCTRL1_SYLODIVDSMDACCLKDIVRATIO(self)
        self.zz_fdict['SYLODIVDSMDACCLKDIVRATIO'] = self.SYLODIVDSMDACCLKDIVRATIO
        self.SYENDLFDQNC = RM_Field_RAC_NS_SYCTRL1_SYENDLFDQNC(self)
        self.zz_fdict['SYENDLFDQNC'] = self.SYENDLFDQNC
        self.SYLODIVFCALCLR = RM_Field_RAC_NS_SYCTRL1_SYLODIVFCALCLR(self)
        self.zz_fdict['SYLODIVFCALCLR'] = self.SYLODIVFCALCLR
        self.SYLODIVSMUXCLKDIVRATIO = RM_Field_RAC_NS_SYCTRL1_SYLODIVSMUXCLKDIVRATIO(self)
        self.zz_fdict['SYLODIVSMUXCLKDIVRATIO'] = self.SYLODIVSMUXCLKDIVRATIO
        self.SYENDSMDACREG = RM_Field_RAC_NS_SYCTRL1_SYENDSMDACREG(self)
        self.zz_fdict['SYENDSMDACREG'] = self.SYENDSMDACREG
        self.SYENVCOREGLOAD = RM_Field_RAC_NS_SYCTRL1_SYENVCOREGLOAD(self)
        self.zz_fdict['SYENVCOREGLOAD'] = self.SYENVCOREGLOAD
        self.SYLODIVTRIMIQCLKBIASIBIAS = RM_Field_RAC_NS_SYCTRL1_SYLODIVTRIMIQCLKBIASIBIAS(self)
        self.zz_fdict['SYLODIVTRIMIQCLKBIASIBIAS'] = self.SYLODIVTRIMIQCLKBIASIBIAS
        self.SYLODIVSELFP4G82G4 = RM_Field_RAC_NS_SYCTRL1_SYLODIVSELFP4G82G4(self)
        self.zz_fdict['SYLODIVSELFP4G82G4'] = self.SYLODIVSELFP4G82G4
        self.SYMMDREGTRIMVREF = RM_Field_RAC_NS_SYCTRL1_SYMMDREGTRIMVREF(self)
        self.zz_fdict['SYMMDREGTRIMVREF'] = self.SYMMDREGTRIMVREF
        self.SYVCOFASTSTARTUP = RM_Field_RAC_NS_SYCTRL1_SYVCOFASTSTARTUP(self)
        self.zz_fdict['SYVCOFASTSTARTUP'] = self.SYVCOFASTSTARTUP
        self.SYMMDCLKINJXOINTN = RM_Field_RAC_NS_SYCTRL1_SYMMDCLKINJXOINTN(self)
        self.zz_fdict['SYMMDCLKINJXOINTN'] = self.SYMMDCLKINJXOINTN
        self.SYMMDCLKINJXOINTNFORCE = RM_Field_RAC_NS_SYCTRL1_SYMMDCLKINJXOINTNFORCE(self)
        self.zz_fdict['SYMMDCLKINJXOINTNFORCE'] = self.SYMMDCLKINJXOINTNFORCE
        self.SYENDSMDAC = RM_Field_RAC_NS_SYCTRL1_SYENDSMDAC(self)
        self.zz_fdict['SYENDSMDAC'] = self.SYENDSMDAC
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYCTRL3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYCTRL3, self).__init__(rmio, label,
            0xb8020000, 0x218,
            'SYCTRL3', 'RAC_NS.SYCTRL3', 'read-write',
            u"",
            0x00001007, 0x001FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFCLAMPTH = RM_Field_RAC_NS_SYCTRL3_SYDLFCLAMPTH(self)
        self.zz_fdict['SYDLFCLAMPTH'] = self.SYDLFCLAMPTH
        self.SYDLFREADXI = RM_Field_RAC_NS_SYCTRL3_SYDLFREADXI(self)
        self.zz_fdict['SYDLFREADXI'] = self.SYDLFREADXI
        self.SYDLFREADXF = RM_Field_RAC_NS_SYCTRL3_SYDLFREADXF(self)
        self.zz_fdict['SYDLFREADXF'] = self.SYDLFREADXF
        self.SYDLFDQNCGAIN = RM_Field_RAC_NS_SYCTRL3_SYDLFDQNCGAIN(self)
        self.zz_fdict['SYDLFDQNCGAIN'] = self.SYDLFDQNCGAIN
        self.SYDLFREADACAPCK2 = RM_Field_RAC_NS_SYCTRL3_SYDLFREADACAPCK2(self)
        self.zz_fdict['SYDLFREADACAPCK2'] = self.SYDLFREADACAPCK2
        self.SYLODIVFCALRUN = RM_Field_RAC_NS_SYCTRL3_SYLODIVFCALRUN(self)
        self.zz_fdict['SYLODIVFCALRUN'] = self.SYLODIVFCALRUN
        self.SYVCOHCAPRETIME = RM_Field_RAC_NS_SYCTRL3_SYVCOHCAPRETIME(self)
        self.zz_fdict['SYVCOHCAPRETIME'] = self.SYVCOHCAPRETIME
        self.SYDSMDACREGTRIMVREF = RM_Field_RAC_NS_SYCTRL3_SYDSMDACREGTRIMVREF(self)
        self.zz_fdict['SYDSMDACREGTRIMVREF'] = self.SYDSMDACREGTRIMVREF
        self.SYMMDDENOM = RM_Field_RAC_NS_SYCTRL3_SYMMDDENOM(self)
        self.zz_fdict['SYMMDDENOM'] = self.SYMMDDENOM
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYDLF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYDLF, self).__init__(rmio, label,
            0xb8020000, 0x21C,
            'SYDLF', 'RAC_NS.SYDLF', 'read-write',
            u"",
            0x00100000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFDACVALTHM = RM_Field_RAC_NS_SYDLF_SYDLFDACVALTHM(self)
        self.zz_fdict['SYDLFDACVALTHM'] = self.SYDLFDACVALTHM
        self.SYDLFVCTRLHITH = RM_Field_RAC_NS_SYDLF_SYDLFVCTRLHITH(self)
        self.zz_fdict['SYDLFVCTRLHITH'] = self.SYDLFVCTRLHITH
        self.SYDLFLPFBWZP = RM_Field_RAC_NS_SYDLF_SYDLFLPFBWZP(self)
        self.zz_fdict['SYDLFLPFBWZP'] = self.SYDLFLPFBWZP
        self.SYDLFLPFBWLOAD = RM_Field_RAC_NS_SYDLF_SYDLFLPFBWLOAD(self)
        self.zz_fdict['SYDLFLPFBWLOAD'] = self.SYDLFLPFBWLOAD
        self.SYDLFDACVALBIN = RM_Field_RAC_NS_SYDLF_SYDLFDACVALBIN(self)
        self.zz_fdict['SYDLFDACVALBIN'] = self.SYDLFDACVALBIN
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX0DBMEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX0DBMEN, self).__init__(rmio, label,
            0xb8020000, 0x220,
            'TX0DBMEN', 'RAC_NS.TX0DBMEN', 'read-write',
            u"",
            0x00000000, 0x00000FDF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMENPAREG = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPAREG(self)
        self.zz_fdict['TX0DBMENPAREG'] = self.TX0DBMENPAREG
        self.TX0DBMENPREDRVREG = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRVREG(self)
        self.zz_fdict['TX0DBMENPREDRVREG'] = self.TX0DBMENPREDRVREG
        self.TX0DBMENPREDRV = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRV(self)
        self.zz_fdict['TX0DBMENPREDRV'] = self.TX0DBMENPREDRV
        self.TX0DBMENLOADREGPREDRV = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENLOADREGPREDRV(self)
        self.zz_fdict['TX0DBMENLOADREGPREDRV'] = self.TX0DBMENLOADREGPREDRV
        self.TX0DBMENLOADREGPA = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENLOADREGPA(self)
        self.zz_fdict['TX0DBMENLOADREGPA'] = self.TX0DBMENLOADREGPA
        self.TX0DBMENBYPASSREGPA = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENBYPASSREGPA(self)
        self.zz_fdict['TX0DBMENBYPASSREGPA'] = self.TX0DBMENBYPASSREGPA
        self.TX0DBMENBIASREGPREDRV = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENBIASREGPREDRV(self)
        self.zz_fdict['TX0DBMENBIASREGPREDRV'] = self.TX0DBMENBIASREGPREDRV
        self.TX0DBMENREPLICABIASREGPA = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENREPLICABIASREGPA(self)
        self.zz_fdict['TX0DBMENREPLICABIASREGPA'] = self.TX0DBMENREPLICABIASREGPA
        self.TX0DBMENPA = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPA(self)
        self.zz_fdict['TX0DBMENPA'] = self.TX0DBMENPA
        self.TX0DBMENPAREGSTBLOAD = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPAREGSTBLOAD(self)
        self.zz_fdict['TX0DBMENPAREGSTBLOAD'] = self.TX0DBMENPAREGSTBLOAD
        self.TX0DBMENPREDRVREGSTBLOAD = RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRVREGSTBLOAD(self)
        self.zz_fdict['TX0DBMENPREDRVREGSTBLOAD'] = self.TX0DBMENPREDRVREGSTBLOAD
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX0DBMCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX0DBMCTRL, self).__init__(rmio, label,
            0xb8020000, 0x224,
            'TX0DBMCTRL', 'RAC_NS.TX0DBMCTRL', 'read-write',
            u"",
            0x00000000, 0x000003FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMPOWER = RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMPOWER(self)
        self.zz_fdict['TX0DBMPOWER'] = self.TX0DBMPOWER
        self.TX0DBMLATCHBYPASS = RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMLATCHBYPASS(self)
        self.zz_fdict['TX0DBMLATCHBYPASS'] = self.TX0DBMLATCHBYPASS
        self.TX0DBMSLICERESET = RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMSLICERESET(self)
        self.zz_fdict['TX0DBMSLICERESET'] = self.TX0DBMSLICERESET
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX0DBMTRIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX0DBMTRIM, self).__init__(rmio, label,
            0xb8020000, 0x228,
            'TX0DBMTRIM', 'RAC_NS.TX0DBMTRIM', 'read-write',
            u"",
            0x1008080C, 0x1C0F0FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMTRIMPSRBSTREGPREDRV = RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPREDRV(self)
        self.zz_fdict['TX0DBMTRIMPSRBSTREGPREDRV'] = self.TX0DBMTRIMPSRBSTREGPREDRV
        self.TX0DBMTRIMPREDRVSLOPE = RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPREDRVSLOPE(self)
        self.zz_fdict['TX0DBMTRIMPREDRVSLOPE'] = self.TX0DBMTRIMPREDRVSLOPE
        self.TX0DBMTRIMPSRBSTREGPA = RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPA(self)
        self.zz_fdict['TX0DBMTRIMPSRBSTREGPA'] = self.TX0DBMTRIMPSRBSTREGPA
        self.TX0DBMTRIMTAPCAP100F = RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMTAPCAP100F(self)
        self.zz_fdict['TX0DBMTRIMTAPCAP100F'] = self.TX0DBMTRIMTAPCAP100F
        self.TX0DBMTRIMTAPCAP200F = RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMTAPCAP200F(self)
        self.zz_fdict['TX0DBMTRIMTAPCAP200F'] = self.TX0DBMTRIMTAPCAP200F
        self.TX0DBMTRIMVREFREGPA = RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMVREFREGPA(self)
        self.zz_fdict['TX0DBMTRIMVREFREGPA'] = self.TX0DBMTRIMVREFREGPA
        self.TX0DBMTRIMVREFREGPREDRV = RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMVREFREGPREDRV(self)
        self.zz_fdict['TX0DBMTRIMVREFREGPREDRV'] = self.TX0DBMTRIMVREFREGPREDRV
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX0DBMTRIM0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX0DBMTRIM0, self).__init__(rmio, label,
            0xb8020000, 0x22C,
            'TX0DBMTRIM0', 'RAC_NS.TX0DBMTRIM0', 'read-write',
            u"",
            0x0006C776, 0x000FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX0DBMTRIMDUTYCYN = RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMDUTYCYN(self)
        self.zz_fdict['TX0DBMTRIMDUTYCYN'] = self.TX0DBMTRIMDUTYCYN
        self.TX0DBMTRIMNBIASPA = RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMNBIASPA(self)
        self.zz_fdict['TX0DBMTRIMNBIASPA'] = self.TX0DBMTRIMNBIASPA
        self.TX0DBMTRIMPBIASPA = RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMPBIASPA(self)
        self.zz_fdict['TX0DBMTRIMPBIASPA'] = self.TX0DBMTRIMPBIASPA
        self.TX0DBMTRIMRFBREGPA = RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMRFBREGPA(self)
        self.zz_fdict['TX0DBMTRIMRFBREGPA'] = self.TX0DBMTRIMRFBREGPA
        self.TX0DBMTRIMDUTYCYP = RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMDUTYCYP(self)
        self.zz_fdict['TX0DBMTRIMDUTYCYP'] = self.TX0DBMTRIMDUTYCYP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX10DBMEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX10DBMEN, self).__init__(rmio, label,
            0xb8020000, 0x230,
            'TX10DBMEN', 'RAC_NS.TX10DBMEN', 'read-write',
            u"",
            0x00000000, 0x000007FE,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMENPA = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPA(self)
        self.zz_fdict['TX10DBMENPA'] = self.TX10DBMENPA
        self.TX10DBMENPAREG = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREG(self)
        self.zz_fdict['TX10DBMENPAREG'] = self.TX10DBMENPAREG
        self.TX10DBMENPREDRV = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRV(self)
        self.zz_fdict['TX10DBMENPREDRV'] = self.TX10DBMENPREDRV
        self.TX10DBMENPREDRVREG = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRVREG(self)
        self.zz_fdict['TX10DBMENPREDRVREG'] = self.TX10DBMENPREDRVREG
        self.TX10DBMENPAREGPULLDOWN = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGPULLDOWN(self)
        self.zz_fdict['TX10DBMENPAREGPULLDOWN'] = self.TX10DBMENPAREGPULLDOWN
        self.TX10DBMENPAREGSTBLOAD = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGSTBLOAD(self)
        self.zz_fdict['TX10DBMENPAREGSTBLOAD'] = self.TX10DBMENPAREGSTBLOAD
        self.TX10DBMENPAREGSTBLOADAUTO = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGSTBLOADAUTO(self)
        self.zz_fdict['TX10DBMENPAREGSTBLOADAUTO'] = self.TX10DBMENPAREGSTBLOADAUTO
        self.TX10DBMENPAOUTBIAS = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAOUTBIAS(self)
        self.zz_fdict['TX10DBMENPAOUTBIAS'] = self.TX10DBMENPAOUTBIAS
        self.TX10DBMENRXPADATTN = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENRXPADATTN(self)
        self.zz_fdict['TX10DBMENRXPADATTN'] = self.TX10DBMENRXPADATTN
        self.TX10DBMENPREDRVREGSTBLOAD = RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRVREGSTBLOAD(self)
        self.zz_fdict['TX10DBMENPREDRVREGSTBLOAD'] = self.TX10DBMENPREDRVREGSTBLOAD
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX10DBMCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX10DBMCTRL1, self).__init__(rmio, label,
            0xb8020000, 0x234,
            'TX10DBMCTRL1', 'RAC_NS.TX10DBMCTRL1', 'read-write',
            u"",
            0x00000000, 0x00007DFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMPOWER = RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMPOWER(self)
        self.zz_fdict['TX10DBMPOWER'] = self.TX10DBMPOWER
        self.TX10DBMSLICERST = RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMSLICERST(self)
        self.zz_fdict['TX10DBMSLICERST'] = self.TX10DBMSLICERST
        self.TX10DBMRXPADATTN = RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMRXPADATTN(self)
        self.zz_fdict['TX10DBMRXPADATTN'] = self.TX10DBMRXPADATTN
        self.TX10DBMRAMPCLKBYPASS = RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMRAMPCLKBYPASS(self)
        self.zz_fdict['TX10DBMRAMPCLKBYPASS'] = self.TX10DBMRAMPCLKBYPASS
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX10DBMTX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX10DBMTX, self).__init__(rmio, label,
            0xb8020000, 0x23C,
            'TX10DBMTX', 'RAC_NS.TX10DBMTX', 'read-write',
            u"",
            0x00280000, 0x003C0000,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMTRIMHFCTAP = RM_Field_RAC_NS_TX10DBMTX_TX10DBMTRIMHFCTAP(self)
        self.zz_fdict['TX10DBMTRIMHFCTAP'] = self.TX10DBMTRIMHFCTAP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX10DBMTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX10DBMTRIM1, self).__init__(rmio, label,
            0xb8020000, 0x240,
            'TX10DBMTRIM1', 'RAC_NS.TX10DBMTRIM1', 'read-write',
            u"",
            0x002020AD, 0x03FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMTRIMBIASDION = RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASDION(self)
        self.zz_fdict['TX10DBMTRIMBIASDION'] = self.TX10DBMTRIMBIASDION
        self.TX10DBMTRIMBIASDIOP = RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASDIOP(self)
        self.zz_fdict['TX10DBMTRIMBIASDIOP'] = self.TX10DBMTRIMBIASDIOP
        self.TX10DBMTRIMNSWBIAS = RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMNSWBIAS(self)
        self.zz_fdict['TX10DBMTRIMNSWBIAS'] = self.TX10DBMTRIMNSWBIAS
        self.TX10DBMTRIMPSWBIAS = RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMPSWBIAS(self)
        self.zz_fdict['TX10DBMTRIMPSWBIAS'] = self.TX10DBMTRIMPSWBIAS
        self.TX10DBMTRIMBIASN = RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASN(self)
        self.zz_fdict['TX10DBMTRIMBIASN'] = self.TX10DBMTRIMBIASN
        self.TX10DBMTRIMDUTYN = RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMDUTYN(self)
        self.zz_fdict['TX10DBMTRIMDUTYN'] = self.TX10DBMTRIMDUTYN
        self.TX10DBMTRIMBIASP = RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASP(self)
        self.zz_fdict['TX10DBMTRIMBIASP'] = self.TX10DBMTRIMBIASP
        self.TX10DBMTRIMDUTYP = RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMDUTYP(self)
        self.zz_fdict['TX10DBMTRIMDUTYP'] = self.TX10DBMTRIMDUTYP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_TX10DBMTRIM2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_TX10DBMTRIM2, self).__init__(rmio, label,
            0xb8020000, 0x244,
            'TX10DBMTRIM2', 'RAC_NS.TX10DBMTRIM2', 'read-write',
            u"",
            0x00175416, 0x001FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TX10DBMTRIMPREDRVREGSLICES = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGSLICES(self)
        self.zz_fdict['TX10DBMTRIMPREDRVREGSLICES'] = self.TX10DBMTRIMPREDRVREGSLICES
        self.TX10DBMTRIMPREDRVSLC = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVSLC(self)
        self.zz_fdict['TX10DBMTRIMPREDRVSLC'] = self.TX10DBMTRIMPREDRVSLC
        self.TX10DBMTRIMPREDRVREGPSR = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGPSR(self)
        self.zz_fdict['TX10DBMTRIMPREDRVREGPSR'] = self.TX10DBMTRIMPREDRVREGPSR
        self.TX10DBMTRIMPREDRVREG = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREG(self)
        self.zz_fdict['TX10DBMTRIMPREDRVREG'] = self.TX10DBMTRIMPREDRVREG
        self.TX10DBMTRIMPAREG = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREG(self)
        self.zz_fdict['TX10DBMTRIMPAREG'] = self.TX10DBMTRIMPAREG
        self.TX10DBMTRIMPAREGVREF = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREGVREF(self)
        self.zz_fdict['TX10DBMTRIMPAREGVREF'] = self.TX10DBMTRIMPAREGVREF
        self.TX10DBMTRIMPREDRVREGVREF = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGVREF(self)
        self.zz_fdict['TX10DBMTRIMPREDRVREGVREF'] = self.TX10DBMTRIMPREDRVREGVREF
        self.TX10DBMTRIMPAREGPSR = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREGPSR(self)
        self.zz_fdict['TX10DBMTRIMPAREGPSR'] = self.TX10DBMTRIMPAREGPSR
        self.TX10DBMTRIMPREDRVCAP = RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVCAP(self)
        self.zz_fdict['TX10DBMTRIMPREDRVCAP'] = self.TX10DBMTRIMPREDRVCAP
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_PREREGTRIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_PREREGTRIM, self).__init__(rmio, label,
            0xb8020000, 0x248,
            'PREREGTRIM', 'RAC_NS.PREREGTRIM', 'read-write',
            u"",
            0x00000000, 0x00007FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PREREGTRIMVREG = RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVREG(self)
        self.zz_fdict['PREREGTRIMVREG'] = self.PREREGTRIMVREG
        self.PREREGTRIMVTRMINIVOLTAGE = RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVTRMINIVOLTAGE(self)
        self.zz_fdict['PREREGTRIMVTRMINIVOLTAGE'] = self.PREREGTRIMVTRMINIVOLTAGE
        self.PREREGTRIMBYPCMPVREF = RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMBYPCMPVREF(self)
        self.zz_fdict['PREREGTRIMBYPCMPVREF'] = self.PREREGTRIMBYPCMPVREF
        self.PREREGTRIMVTRMINITEMPCO = RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVTRMINITEMPCO(self)
        self.zz_fdict['PREREGTRIMVTRMINITEMPCO'] = self.PREREGTRIMVTRMINITEMPCO
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_MIXDACTRIM1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_MIXDACTRIM1, self).__init__(rmio, label,
            0xb8020000, 0x24C,
            'MIXDACTRIM1', 'RAC_NS.MIXDACTRIM1', 'read-write',
            u"",
            0x00000002, 0x00000003,
            0x00001000, 0x00002000,
            0x00003000)

        self.MIXDACTRIMBBSUPPLYSERIESRES = RM_Field_RAC_NS_MIXDACTRIM1_MIXDACTRIMBBSUPPLYSERIESRES(self)
        self.zz_fdict['MIXDACTRIMBBSUPPLYSERIESRES'] = self.MIXDACTRIMBBSUPPLYSERIESRES
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SYDLF1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SYDLF1, self).__init__(rmio, label,
            0xb8020000, 0x250,
            'SYDLF1', 'RAC_NS.SYDLF1', 'read-write',
            u"",
            0x00000000, 0x001FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYDLFTDCDBIAS = RM_Field_RAC_NS_SYDLF1_SYDLFTDCDBIAS(self)
        self.zz_fdict['SYDLFTDCDBIAS'] = self.SYDLFTDCDBIAS
        self.SYDLFPFDLOCKSAMPLETH = RM_Field_RAC_NS_SYDLF1_SYDLFPFDLOCKSAMPLETH(self)
        self.zz_fdict['SYDLFPFDLOCKSAMPLETH'] = self.SYDLFPFDLOCKSAMPLETH
        self.SYDLFDTHIN = RM_Field_RAC_NS_SYDLF1_SYDLFDTHIN(self)
        self.zz_fdict['SYDLFDTHIN'] = self.SYDLFDTHIN
        self.SYDLFPOSITIVECOEFF = RM_Field_RAC_NS_SYDLF1_SYDLFPOSITIVECOEFF(self)
        self.zz_fdict['SYDLFPOSITIVECOEFF'] = self.SYDLFPOSITIVECOEFF
        self.__dict__['zz_frozen'] = True


class RM_Register_RAC_NS_SPARE1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RAC_NS_SPARE1, self).__init__(rmio, label,
            0xb8020000, 0x258,
            'SPARE1', 'RAC_NS.SPARE1', 'read-write',
            u"",
            0x00000000, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYZZZSPARES = RM_Field_RAC_NS_SPARE1_SYZZZSPARES(self)
        self.zz_fdict['SYZZZSPARES'] = self.SYZZZSPARES
        self.TIASPARE = RM_Field_RAC_NS_SPARE1_TIASPARE(self)
        self.zz_fdict['TIASPARE'] = self.TIASPARE
        self.TX10DBMSPARE = RM_Field_RAC_NS_SPARE1_TX10DBMSPARE(self)
        self.zz_fdict['TX10DBMSPARE'] = self.TX10DBMSPARE
        self.VTRSPARES = RM_Field_RAC_NS_SPARE1_VTRSPARES(self)
        self.zz_fdict['VTRSPARES'] = self.VTRSPARES
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
            0x80000000, 0xF7EF03FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNTHLODIVFREQCTRL = RM_Field_RAC_NS_RFLOCK0_SYNTHLODIVFREQCTRL(self)
        self.zz_fdict['SYNTHLODIVFREQCTRL'] = self.SYNTHLODIVFREQCTRL
        self.RACIFPGAEN = RM_Field_RAC_NS_RFLOCK0_RACIFPGAEN(self)
        self.zz_fdict['RACIFPGAEN'] = self.RACIFPGAEN
        self.RACTX0DBM = RM_Field_RAC_NS_RFLOCK0_RACTX0DBM(self)
        self.zz_fdict['RACTX0DBM'] = self.RACTX0DBM
        self.RACTX10DBM = RM_Field_RAC_NS_RFLOCK0_RACTX10DBM(self)
        self.zz_fdict['RACTX10DBM'] = self.RACTX10DBM
        self.RACTX20DBM = RM_Field_RAC_NS_RFLOCK0_RACTX20DBM(self)
        self.zz_fdict['RACTX20DBM'] = self.RACTX20DBM
        self.MODEMHADM = RM_Field_RAC_NS_RFLOCK0_MODEMHADM(self)
        self.zz_fdict['MODEMHADM'] = self.MODEMHADM
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




# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_RAC_S_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'RAC_S.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EN_EN, self).__init__(register,
            'EN', 'RAC_S.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RXENSRCEN_SWRXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RXENSRCEN_SWRXEN, self).__init__(register,
            'SWRXEN', 'RAC_S.RXENSRCEN.SWRXEN', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RXENSRCEN_CHANNELBUSYEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RXENSRCEN_CHANNELBUSYEN, self).__init__(register,
            'CHANNELBUSYEN', 'RAC_S.RXENSRCEN.CHANNELBUSYEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RXENSRCEN_TIMDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RXENSRCEN_TIMDETEN, self).__init__(register,
            'TIMDETEN', 'RAC_S.RXENSRCEN.TIMDETEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RXENSRCEN_PREDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RXENSRCEN_PREDETEN, self).__init__(register,
            'PREDETEN', 'RAC_S.RXENSRCEN.PREDETEN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RXENSRCEN_FRAMEDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RXENSRCEN_FRAMEDETEN, self).__init__(register,
            'FRAMEDETEN', 'RAC_S.RXENSRCEN.FRAMEDETEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RXENSRCEN_DEMODRXREQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RXENSRCEN_DEMODRXREQEN, self).__init__(register,
            'DEMODRXREQEN', 'RAC_S.RXENSRCEN.DEMODRXREQEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RXENSRCEN_PRSRXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RXENSRCEN_PRSRXEN, self).__init__(register,
            'PRSRXEN', 'RAC_S.RXENSRCEN.PRSRXEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_RXMASK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_RXMASK, self).__init__(register,
            'RXMASK', 'RAC_S.STATUS.RXMASK', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_FORCESTATEACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_FORCESTATEACTIVE, self).__init__(register,
            'FORCESTATEACTIVE', 'RAC_S.STATUS.FORCESTATEACTIVE', 'read-only',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_TXAFTERFRAMEPEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_TXAFTERFRAMEPEND, self).__init__(register,
            'TXAFTERFRAMEPEND', 'RAC_S.STATUS.TXAFTERFRAMEPEND', 'read-only',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_TXAFTERFRAMEACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_TXAFTERFRAMEACTIVE, self).__init__(register,
            'TXAFTERFRAMEACTIVE', 'RAC_S.STATUS.TXAFTERFRAMEACTIVE', 'read-only',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_STATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_STATE, self).__init__(register,
            'STATE', 'RAC_S.STATUS.STATE', 'read-only',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_DEMODENS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_DEMODENS, self).__init__(register,
            'DEMODENS', 'RAC_S.STATUS.DEMODENS', 'read-only',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_TXENS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_TXENS, self).__init__(register,
            'TXENS', 'RAC_S.STATUS.TXENS', 'read-only',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_RXENS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_RXENS, self).__init__(register,
            'RXENS', 'RAC_S.STATUS.RXENS', 'read-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_TXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_TXEN, self).__init__(register,
            'TXEN', 'RAC_S.CMD.TXEN', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_FORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_FORCETX, self).__init__(register,
            'FORCETX', 'RAC_S.CMD.FORCETX', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_TXONCCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_TXONCCA, self).__init__(register,
            'TXONCCA', 'RAC_S.CMD.TXONCCA', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_CLEARTXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_CLEARTXEN, self).__init__(register,
            'CLEARTXEN', 'RAC_S.CMD.CLEARTXEN', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_TXAFTERFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_TXAFTERFRAME, self).__init__(register,
            'TXAFTERFRAME', 'RAC_S.CMD.TXAFTERFRAME', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_TXDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_TXDIS, self).__init__(register,
            'TXDIS', 'RAC_S.CMD.TXDIS', 'write-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_CLEARRXOVERFLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_CLEARRXOVERFLOW, self).__init__(register,
            'CLEARRXOVERFLOW', 'RAC_S.CMD.CLEARRXOVERFLOW', 'write-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_RXCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_RXCAL, self).__init__(register,
            'RXCAL', 'RAC_S.CMD.RXCAL', 'write-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_RXDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_RXDIS, self).__init__(register,
            'RXDIS', 'RAC_S.CMD.RXDIS', 'write-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_PAENSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_PAENSET, self).__init__(register,
            'PAENSET', 'RAC_S.CMD.PAENSET', 'write-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_PAENCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_PAENCLEAR, self).__init__(register,
            'PAENCLEAR', 'RAC_S.CMD.PAENCLEAR', 'write-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_LNAENSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_LNAENSET, self).__init__(register,
            'LNAENSET', 'RAC_S.CMD.LNAENSET', 'write-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_LNAENCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_LNAENCLEAR, self).__init__(register,
            'LNAENCLEAR', 'RAC_S.CMD.LNAENCLEAR', 'write-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_DEMODENSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_DEMODENSET, self).__init__(register,
            'DEMODENSET', 'RAC_S.CMD.DEMODENSET', 'write-only',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_DEMODENCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_DEMODENCLEAR, self).__init__(register,
            'DEMODENCLEAR', 'RAC_S.CMD.DEMODENCLEAR', 'write-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_FORCEDISABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_FORCEDISABLE, self).__init__(register,
            'FORCEDISABLE', 'RAC_S.CTRL.FORCEDISABLE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_PRSTXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_PRSTXEN, self).__init__(register,
            'PRSTXEN', 'RAC_S.CTRL.PRSTXEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_TXAFTERRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_TXAFTERRX, self).__init__(register,
            'TXAFTERRX', 'RAC_S.CTRL.TXAFTERRX', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_PRSMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_PRSMODE, self).__init__(register,
            'PRSMODE', 'RAC_S.CTRL.PRSMODE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_PRSCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_PRSCLR, self).__init__(register,
            'PRSCLR', 'RAC_S.CTRL.PRSCLR', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_TXPOSTPONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_TXPOSTPONE, self).__init__(register,
            'TXPOSTPONE', 'RAC_S.CTRL.TXPOSTPONE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_ACTIVEPOL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_ACTIVEPOL, self).__init__(register,
            'ACTIVEPOL', 'RAC_S.CTRL.ACTIVEPOL', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_PAENPOL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_PAENPOL, self).__init__(register,
            'PAENPOL', 'RAC_S.CTRL.PAENPOL', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_LNAENPOL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_LNAENPOL, self).__init__(register,
            'LNAENPOL', 'RAC_S.CTRL.LNAENPOL', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_PRSRXDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_PRSRXDIS, self).__init__(register,
            'PRSRXDIS', 'RAC_S.CTRL.PRSRXDIS', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_PRSFORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_PRSFORCETX, self).__init__(register,
            'PRSFORCETX', 'RAC_S.CTRL.PRSFORCETX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FORCESTATE_FORCESTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FORCESTATE_FORCESTATE, self).__init__(register,
            'FORCESTATE', 'RAC_S.FORCESTATE.FORCESTATE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IF_STATECHANGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_STATECHANGE, self).__init__(register,
            'STATECHANGE', 'RAC_S.IF.STATECHANGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IF_STIMCMPEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_STIMCMPEV, self).__init__(register,
            'STIMCMPEV', 'RAC_S.IF.STIMCMPEV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IF_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_BUSERROR, self).__init__(register,
            'BUSERROR', 'RAC_S.IF.BUSERROR', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IF_SEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_SEQ, self).__init__(register,
            'SEQ', 'RAC_S.IF.SEQ', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IEN_STATECHANGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_STATECHANGE, self).__init__(register,
            'STATECHANGE', 'RAC_S.IEN.STATECHANGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IEN_STIMCMPEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_STIMCMPEV, self).__init__(register,
            'STIMCMPEV', 'RAC_S.IEN.STIMCMPEV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IEN_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_BUSERROR, self).__init__(register,
            'BUSERROR', 'RAC_S.IEN.BUSERROR', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IEN_SEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_SEQ, self).__init__(register,
            'SEQ', 'RAC_S.IEN.SEQ', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TESTCTRL_MODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TESTCTRL_MODEN, self).__init__(register,
            'MODEN', 'RAC_S.TESTCTRL.MODEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TESTCTRL_DEMODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TESTCTRL_DEMODEN, self).__init__(register,
            'DEMODEN', 'RAC_S.TESTCTRL.DEMODEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TESTCTRL_AUX2RFSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TESTCTRL_AUX2RFSENSE, self).__init__(register,
            'AUX2RFSENSE', 'RAC_S.TESTCTRL.AUX2RFSENSE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TESTCTRL_LOOPBACK2LNAINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TESTCTRL_LOOPBACK2LNAINPUT, self).__init__(register,
            'LOOPBACK2LNAINPUT', 'RAC_S.TESTCTRL.LOOPBACK2LNAINPUT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TESTCTRL_LOOPBACK2LNAOUTPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TESTCTRL_LOOPBACK2LNAOUTPUT, self).__init__(register,
            'LOOPBACK2LNAOUTPUT', 'RAC_S.TESTCTRL.LOOPBACK2LNAOUTPUT', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_STOPPED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_STOPPED, self).__init__(register,
            'STOPPED', 'RAC_S.SEQSTATUS.STOPPED', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_BKPT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_BKPT, self).__init__(register,
            'BKPT', 'RAC_S.SEQSTATUS.BKPT', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_WAITING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_WAITING, self).__init__(register,
            'WAITING', 'RAC_S.SEQSTATUS.WAITING', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_WAITMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_WAITMODE, self).__init__(register,
            'WAITMODE', 'RAC_S.SEQSTATUS.WAITMODE', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_DONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_DONE, self).__init__(register,
            'DONE', 'RAC_S.SEQSTATUS.DONE', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_NEG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_NEG, self).__init__(register,
            'NEG', 'RAC_S.SEQSTATUS.NEG', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_POS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_POS, self).__init__(register,
            'POS', 'RAC_S.SEQSTATUS.POS', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_ZERO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_ZERO, self).__init__(register,
            'ZERO', 'RAC_S.SEQSTATUS.ZERO', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_CARRY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_CARRY, self).__init__(register,
            'CARRY', 'RAC_S.SEQSTATUS.CARRY', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQSTATUS_ABORTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQSTATUS_ABORTEN, self).__init__(register,
            'ABORTEN', 'RAC_S.SEQSTATUS.ABORTEN', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCMD_HALT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCMD_HALT, self).__init__(register,
            'HALT', 'RAC_S.SEQCMD.HALT', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCMD_STEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCMD_STEP, self).__init__(register,
            'STEP', 'RAC_S.SEQCMD.STEP', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCMD_RESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCMD_RESUME, self).__init__(register,
            'RESUME', 'RAC_S.SEQCMD.RESUME', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCMD_BKPTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCMD_BKPTEN, self).__init__(register,
            'BKPTEN', 'RAC_S.SEQCMD.BKPTEN', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCMD_BKPTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCMD_BKPTDIS, self).__init__(register,
            'BKPTDIS', 'RAC_S.SEQCMD.BKPTDIS', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCMD_ABORT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCMD_ABORT, self).__init__(register,
            'ABORT', 'RAC_S.SEQCMD.ABORT', 'write-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCMD_ABORTENSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCMD_ABORTENSET, self).__init__(register,
            'ABORTENSET', 'RAC_S.SEQCMD.ABORTENSET', 'write-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCMD_ABORTENCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCMD_ABORTENCLEAR, self).__init__(register,
            'ABORTENCLEAR', 'RAC_S.SEQCMD.ABORTENCLEAR', 'write-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BREAKPOINT_BKPADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BREAKPOINT_BKPADDR, self).__init__(register,
            'BKPADDR', 'RAC_S.BREAKPOINT.BKPADDR', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_R0_R0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_R0_R0, self).__init__(register,
            'R0', 'RAC_S.R0.R0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_R1_R1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_R1_R1, self).__init__(register,
            'R1', 'RAC_S.R1.R1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_R2_R2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_R2_R2, self).__init__(register,
            'R2', 'RAC_S.R2.R2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_R3_R3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_R3_R3, self).__init__(register,
            'R3', 'RAC_S.R3.R3', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_R4_R4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_R4_R4, self).__init__(register,
            'R4', 'RAC_S.R4.R4', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_R5_R5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_R5_R5, self).__init__(register,
            'R5', 'RAC_S.R5.R5', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_R6_R6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_R6_R6, self).__init__(register,
            'R6', 'RAC_S.R6.R6', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_R7_R7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_R7_R7, self).__init__(register,
            'R7', 'RAC_S.R7.R7', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_STCMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_STCMP, self).__init__(register,
            'STCMP', 'RAC_S.WAITMASK.STCMP', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_FRCRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_FRCRX, self).__init__(register,
            'FRCRX', 'RAC_S.WAITMASK.FRCRX', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_FRCTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_FRCTX, self).__init__(register,
            'FRCTX', 'RAC_S.WAITMASK.FRCTX', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_PRSEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_PRSEVENT, self).__init__(register,
            'PRSEVENT', 'RAC_S.WAITMASK.PRSEVENT', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_DEMODRXREQCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_DEMODRXREQCLR, self).__init__(register,
            'DEMODRXREQCLR', 'RAC_S.WAITMASK.DEMODRXREQCLR', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_SYNTHRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_SYNTHRDY, self).__init__(register,
            'SYNTHRDY', 'RAC_S.WAITMASK.SYNTHRDY', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_RAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_RAMPDONE, self).__init__(register,
            'RAMPDONE', 'RAC_S.WAITMASK.RAMPDONE', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_FRCPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_FRCPAUSED, self).__init__(register,
            'FRCPAUSED', 'RAC_S.WAITMASK.FRCPAUSED', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITMASK_ANTSWITCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITMASK_ANTSWITCH, self).__init__(register,
            'ANTSWITCH', 'RAC_S.WAITMASK.ANTSWITCH', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WAITSNSH_WAITSNSH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WAITSNSH_WAITSNSH, self).__init__(register,
            'WAITSNSH', 'RAC_S.WAITSNSH.WAITSNSH', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STIMER_STIMER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STIMER_STIMER, self).__init__(register,
            'STIMER', 'RAC_S.STIMER.STIMER', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STIMERCOMP_STIMERCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STIMERCOMP_STIMERCOMP, self).__init__(register,
            'STIMERCOMP', 'RAC_S.STIMERCOMP.STIMERCOMP', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VECTADDR_VECTADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VECTADDR_VECTADDR, self).__init__(register,
            'VECTADDR', 'RAC_S.VECTADDR.VECTADDR', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_COMPACT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_COMPACT, self).__init__(register,
            'COMPACT', 'RAC_S.SEQCTRL.COMPACT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_COMPINVALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_COMPINVALMODE, self).__init__(register,
            'COMPINVALMODE', 'RAC_S.SEQCTRL.COMPINVALMODE', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_STIMERDEBUGRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_STIMERDEBUGRUN, self).__init__(register,
            'STIMERDEBUGRUN', 'RAC_S.SEQCTRL.STIMERDEBUGRUN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_CPUHALTREQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_CPUHALTREQEN, self).__init__(register,
            'CPUHALTREQEN', 'RAC_S.SEQCTRL.CPUHALTREQEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_SEQHALTUPONCPUHALTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_SEQHALTUPONCPUHALTEN, self).__init__(register,
            'SEQHALTUPONCPUHALTEN', 'RAC_S.SEQCTRL.SEQHALTUPONCPUHALTEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRESC_STIMER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRESC_STIMER, self).__init__(register,
            'STIMER', 'RAC_S.PRESC.STIMER', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SR0_SR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SR0_SR0, self).__init__(register,
            'SR0', 'RAC_S.SR0.SR0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SR1_SR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SR1_SR1, self).__init__(register,
            'SR1', 'RAC_S.SR1.SR1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SR2_SR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SR2_SR2, self).__init__(register,
            'SR2', 'RAC_S.SR2.SR2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SR3_SR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SR3_SR3, self).__init__(register,
            'SR3', 'RAC_S.SR3.SR3', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WUREQ_MANUAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WUREQ_MANUAL, self).__init__(register,
            'MANUAL', 'RAC_S.WUREQ.MANUAL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WUREQ_OVERRIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WUREQ_OVERRIDE, self).__init__(register,
            'OVERRIDE', 'RAC_S.WUREQ.OVERRIDE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_WUREQ_STATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_WUREQ_STATUS, self).__init__(register,
            'STATUS', 'RAC_S.WUREQ.STATUS', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYNTHENCTRL_VCOSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYNTHENCTRL_VCOSTARTUP, self).__init__(register,
            'VCOSTARTUP', 'RAC_S.SYNTHENCTRL.VCOSTARTUP', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYNTHENCTRL_VCBUFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYNTHENCTRL_VCBUFEN, self).__init__(register,
            'VCBUFEN', 'RAC_S.SYNTHENCTRL.VCBUFEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYNTHENCTRL_SYNTHSTARTREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYNTHENCTRL_SYNTHSTARTREQ, self).__init__(register,
            'SYNTHSTARTREQ', 'RAC_S.SYNTHENCTRL.SYNTHSTARTREQ', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYNTHENCTRL_LPFBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYNTHENCTRL_LPFBWSEL, self).__init__(register,
            'LPFBWSEL', 'RAC_S.SYNTHENCTRL.LPFBWSEL', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYNTHREGCTRL_MMDLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYNTHREGCTRL_MMDLDOVREFTRIM, self).__init__(register,
            'MMDLDOVREFTRIM', 'RAC_S.SYNTHREGCTRL.MMDLDOVREFTRIM', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYNTHREGCTRL_CHPLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYNTHREGCTRL_CHPLDOVREFTRIM, self).__init__(register,
            'CHPLDOVREFTRIM', 'RAC_S.SYNTHREGCTRL.CHPLDOVREFTRIM', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VCOCTRL_VCOAMPLITUDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VCOCTRL_VCOAMPLITUDE, self).__init__(register,
            'VCOAMPLITUDE', 'RAC_S.VCOCTRL.VCOAMPLITUDE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VCOCTRL_VCODETAMPLITUDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VCOCTRL_VCODETAMPLITUDE, self).__init__(register,
            'VCODETAMPLITUDE', 'RAC_S.VCOCTRL.VCODETAMPLITUDE', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CHPCTRL_CHPOUTPUTTRISTATEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CHPCTRL_CHPOUTPUTTRISTATEMODE, self).__init__(register,
            'CHPOUTPUTTRISTATEMODE', 'RAC_S.CHPCTRL.CHPOUTPUTTRISTATEMODE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYNTHCTRL_MMDPOWERBALANCEDISABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYNTHCTRL_MMDPOWERBALANCEDISABLE, self).__init__(register,
            'MMDPOWERBALANCEDISABLE', 'RAC_S.SYNTHCTRL.MMDPOWERBALANCEDISABLE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFSTATUS_MODRAMPUPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFSTATUS_MODRAMPUPDONE, self).__init__(register,
            'MODRAMPUPDONE', 'RAC_S.RFSTATUS.MODRAMPUPDONE', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS2_PREVSTATE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS2_PREVSTATE1, self).__init__(register,
            'PREVSTATE1', 'RAC_S.STATUS2.PREVSTATE1', 'read-only',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS2_PREVSTATE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS2_PREVSTATE2, self).__init__(register,
            'PREVSTATE2', 'RAC_S.STATUS2.PREVSTATE2', 'read-only',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS2_PREVSTATE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS2_PREVSTATE3, self).__init__(register,
            'PREVSTATE3', 'RAC_S.STATUS2.PREVSTATE3', 'read-only',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFPGACTRL_DCCALON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFPGACTRL_DCCALON, self).__init__(register,
            'DCCALON', 'RAC_S.IFPGACTRL.DCCALON', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFPGACTRL_DCRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFPGACTRL_DCRSTEN, self).__init__(register,
            'DCRSTEN', 'RAC_S.IFPGACTRL.DCRSTEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFPGACTRL_DCESTIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFPGACTRL_DCESTIEN, self).__init__(register,
            'DCESTIEN', 'RAC_S.IFPGACTRL.DCESTIEN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFPGACTRL_DCCALDEC0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFPGACTRL_DCCALDEC0, self).__init__(register,
            'DCCALDEC0', 'RAC_S.IFPGACTRL.DCCALDEC0', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFPGACTRL_DCCALDCGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFPGACTRL_DCCALDCGEAR, self).__init__(register,
            'DCCALDCGEAR', 'RAC_S.IFPGACTRL.DCCALDCGEAR', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PAENCTRL_PARAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PAENCTRL_PARAMP, self).__init__(register,
            'PARAMP', 'RAC_S.PAENCTRL.PARAMP', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_APC_ENAPCSW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_APC_ENAPCSW, self).__init__(register,
            'ENAPCSW', 'RAC_S.APC.ENAPCSW', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_APC_AMPCONTROLLIMITSW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_APC_AMPCONTROLLIMITSW, self).__init__(register,
            'AMPCONTROLLIMITSW', 'RAC_S.APC.AMPCONTROLLIMITSW', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCCLKINVERT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCCLKINVERT, self).__init__(register,
            'AUXADCCLKINVERT', 'RAC_S.AUXADCTRIM.AUXADCCLKINVERT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCLDOVREFTRIM, self).__init__(register,
            'AUXADCLDOVREFTRIM', 'RAC_S.AUXADCTRIM.AUXADCLDOVREFTRIM', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCOUTPUTINVERT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCOUTPUTINVERT, self).__init__(register,
            'AUXADCOUTPUTINVERT', 'RAC_S.AUXADCTRIM.AUXADCOUTPUTINVERT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCRCTUNE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCRCTUNE, self).__init__(register,
            'AUXADCRCTUNE', 'RAC_S.AUXADCTRIM.AUXADCRCTUNE', 'read-write',
            u"",
            4, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMADCINPUTRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMADCINPUTRES, self).__init__(register,
            'AUXADCTRIMADCINPUTRES', 'RAC_S.AUXADCTRIM.AUXADCTRIMADCINPUTRES', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF, self).__init__(register,
            'AUXADCTRIMCURRINPUTBUF', 'RAC_S.AUXADCTRIM.AUXADCTRIMCURRINPUTBUF', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURROPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURROPA1, self).__init__(register,
            'AUXADCTRIMCURROPA1', 'RAC_S.AUXADCTRIM.AUXADCTRIMCURROPA1', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURROPA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURROPA2, self).__init__(register,
            'AUXADCTRIMCURROPA2', 'RAC_S.AUXADCTRIM.AUXADCTRIMCURROPA2', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURRREFBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURRREFBUF, self).__init__(register,
            'AUXADCTRIMCURRREFBUF', 'RAC_S.AUXADCTRIM.AUXADCTRIMCURRREFBUF', 'read-write',
            u"",
            17, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURRTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURRTSENSE, self).__init__(register,
            'AUXADCTRIMCURRTSENSE', 'RAC_S.AUXADCTRIM.AUXADCTRIMCURRTSENSE', 'read-write',
            u"",
            19, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURRVCMBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMCURRVCMBUF, self).__init__(register,
            'AUXADCTRIMCURRVCMBUF', 'RAC_S.AUXADCTRIM.AUXADCTRIMCURRVCMBUF', 'read-write',
            u"",
            21, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT, self).__init__(register,
            'AUXADCTRIMLDOHIGHCURRENT', 'RAC_S.AUXADCTRIM.AUXADCTRIMLDOHIGHCURRENT', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMREFP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMREFP, self).__init__(register,
            'AUXADCTRIMREFP', 'RAC_S.AUXADCTRIM.AUXADCTRIMREFP', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMVREFVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTRIMVREFVCM, self).__init__(register,
            'AUXADCTRIMVREFVCM', 'RAC_S.AUXADCTRIM.AUXADCTRIMVREFVCM', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_AUXADCTSENSETRIMVBE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_AUXADCTSENSETRIMVBE2, self).__init__(register,
            'AUXADCTSENSETRIMVBE2', 'RAC_S.AUXADCTRIM.AUXADCTSENSETRIMVBE2', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENAUXADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENAUXADC, self).__init__(register,
            'AUXADCENAUXADC', 'RAC_S.AUXADCEN.AUXADCENAUXADC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENINPUTBUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENINPUTBUFFER, self).__init__(register,
            'AUXADCENINPUTBUFFER', 'RAC_S.AUXADCEN.AUXADCENINPUTBUFFER', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENLDO, self).__init__(register,
            'AUXADCENLDO', 'RAC_S.AUXADCEN.AUXADCENLDO', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENOUTPUTDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENOUTPUTDRV, self).__init__(register,
            'AUXADCENOUTPUTDRV', 'RAC_S.AUXADCEN.AUXADCENOUTPUTDRV', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENPMON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENPMON, self).__init__(register,
            'AUXADCENPMON', 'RAC_S.AUXADCEN.AUXADCENPMON', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENRESONDIAGA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENRESONDIAGA, self).__init__(register,
            'AUXADCENRESONDIAGA', 'RAC_S.AUXADCEN.AUXADCENRESONDIAGA', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSE, self).__init__(register,
            'AUXADCENTSENSE', 'RAC_S.AUXADCEN.AUXADCENTSENSE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSECAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSECAL, self).__init__(register,
            'AUXADCENTSENSECAL', 'RAC_S.AUXADCEN.AUXADCENTSENSECAL', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCINPUTBUFFERBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCINPUTBUFFERBYPASS, self).__init__(register,
            'AUXADCINPUTBUFFERBYPASS', 'RAC_S.AUXADCEN.AUXADCINPUTBUFFERBYPASS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL0_CYCLES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL0_CYCLES, self).__init__(register,
            'CYCLES', 'RAC_S.AUXADCCTRL0.CYCLES', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL0_MUXSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL0_MUXSEL, self).__init__(register,
            'MUXSEL', 'RAC_S.AUXADCCTRL0.MUXSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL0_CLRCOUNTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL0_CLRCOUNTER, self).__init__(register,
            'CLRCOUNTER', 'RAC_S.AUXADCCTRL0.CLRCOUNTER', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL0_CLRFILTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL0_CLRFILTER, self).__init__(register,
            'CLRFILTER', 'RAC_S.AUXADCCTRL0.CLRFILTER', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL0_INPUTRESSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL0_INPUTRESSEL, self).__init__(register,
            'INPUTRESSEL', 'RAC_S.AUXADCCTRL0.INPUTRESSEL', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTRESSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTRESSEL, self).__init__(register,
            'AUXADCINPUTRESSEL', 'RAC_S.AUXADCCTRL1.AUXADCINPUTRESSEL', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTSELECT, self).__init__(register,
            'AUXADCINPUTSELECT', 'RAC_S.AUXADCCTRL1.AUXADCINPUTSELECT', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCPMONSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCPMONSELECT, self).__init__(register,
            'AUXADCPMONSELECT', 'RAC_S.AUXADCCTRL1.AUXADCPMONSELECT', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSESELCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSESELCURR, self).__init__(register,
            'AUXADCTSENSESELCURR', 'RAC_S.AUXADCCTRL1.AUXADCTSENSESELCURR', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCRESET, self).__init__(register,
            'AUXADCRESET', 'RAC_S.AUXADCCTRL1.AUXADCRESET', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSESELVBE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSESELVBE, self).__init__(register,
            'AUXADCTSENSESELVBE', 'RAC_S.AUXADCCTRL1.AUXADCTSENSESELVBE', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCOUT_AUXADCOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCOUT_AUXADCOUT, self).__init__(register,
            'AUXADCOUT', 'RAC_S.AUXADCOUT.AUXADCOUT', 'read-only',
            u"",
            0, 28)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTBWCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTBWCAL, self).__init__(register,
            'CLKMULTBWCAL', 'RAC_S.CLKMULTEN0.CLKMULTBWCAL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTDISICO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTDISICO, self).__init__(register,
            'CLKMULTDISICO', 'RAC_S.CLKMULTEN0.CLKMULTDISICO', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBDET, self).__init__(register,
            'CLKMULTENBBDET', 'RAC_S.CLKMULTEN0.CLKMULTENBBDET', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXLDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXLDET, self).__init__(register,
            'CLKMULTENBBXLDET', 'RAC_S.CLKMULTEN0.CLKMULTENBBXLDET', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXMDET, self).__init__(register,
            'CLKMULTENBBXMDET', 'RAC_S.CLKMULTEN0.CLKMULTENBBXMDET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENCFDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENCFDET, self).__init__(register,
            'CLKMULTENCFDET', 'RAC_S.CLKMULTEN0.CLKMULTENCFDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDITHER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDITHER, self).__init__(register,
            'CLKMULTENDITHER', 'RAC_S.CLKMULTEN0.CLKMULTENDITHER', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVADC, self).__init__(register,
            'CLKMULTENDRVADC', 'RAC_S.CLKMULTEN0.CLKMULTENDRVADC', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVDIFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVDIFF, self).__init__(register,
            'CLKMULTENDRVDIFF', 'RAC_S.CLKMULTEN0.CLKMULTENDRVDIFF', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVRX2P4G(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVRX2P4G, self).__init__(register,
            'CLKMULTENDRVRX2P4G', 'RAC_S.CLKMULTEN0.CLKMULTENDRVRX2P4G', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVRXSUBG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVRXSUBG, self).__init__(register,
            'CLKMULTENDRVRXSUBG', 'RAC_S.CLKMULTEN0.CLKMULTENDRVRXSUBG', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTXDUALB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTXDUALB, self).__init__(register,
            'CLKMULTENDRVTXDUALB', 'RAC_S.CLKMULTEN0.CLKMULTENDRVTXDUALB', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENFBDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENFBDIV, self).__init__(register,
            'CLKMULTENFBDIV', 'RAC_S.CLKMULTEN0.CLKMULTENFBDIV', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREFDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREFDIV, self).__init__(register,
            'CLKMULTENREFDIV', 'RAC_S.CLKMULTEN0.CLKMULTENREFDIV', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1, self).__init__(register,
            'CLKMULTENREG1', 'RAC_S.CLKMULTEN0.CLKMULTENREG1', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG2, self).__init__(register,
            'CLKMULTENREG2', 'RAC_S.CLKMULTEN0.CLKMULTENREG2', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENROTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENROTDET, self).__init__(register,
            'CLKMULTENROTDET', 'RAC_S.CLKMULTEN0.CLKMULTENROTDET', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTFREQCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTFREQCAL, self).__init__(register,
            'CLKMULTFREQCAL', 'RAC_S.CLKMULTEN0.CLKMULTFREQCAL', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG1ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG1ADJV, self).__init__(register,
            'CLKMULTREG1ADJV', 'RAC_S.CLKMULTEN0.CLKMULTREG1ADJV', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG2ADJI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG2ADJI, self).__init__(register,
            'CLKMULTREG2ADJI', 'RAC_S.CLKMULTEN0.CLKMULTREG2ADJI', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG2ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG2ADJV, self).__init__(register,
            'CLKMULTREG2ADJV', 'RAC_S.CLKMULTEN0.CLKMULTREG2ADJV', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTINNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTINNIBBLE, self).__init__(register,
            'CLKMULTINNIBBLE', 'RAC_S.CLKMULTEN1.CLKMULTINNIBBLE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTLDCNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTLDCNIB, self).__init__(register,
            'CLKMULTLDCNIB', 'RAC_S.CLKMULTEN1.CLKMULTLDCNIB', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTLDFNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTLDFNIB, self).__init__(register,
            'CLKMULTLDFNIB', 'RAC_S.CLKMULTEN1.CLKMULTLDFNIB', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTLDMNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTLDMNIB, self).__init__(register,
            'CLKMULTLDMNIB', 'RAC_S.CLKMULTEN1.CLKMULTLDMNIB', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTRDNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTRDNIBBLE, self).__init__(register,
            'CLKMULTRDNIBBLE', 'RAC_S.CLKMULTEN1.CLKMULTRDNIBBLE', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTDIVN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTDIVN, self).__init__(register,
            'CLKMULTDIVN', 'RAC_S.CLKMULTCTRL.CLKMULTDIVN', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTDIVR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTDIVR, self).__init__(register,
            'CLKMULTDIVR', 'RAC_S.CLKMULTCTRL.CLKMULTDIVR', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTDIVX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTDIVX, self).__init__(register,
            'CLKMULTDIVX', 'RAC_S.CLKMULTCTRL.CLKMULTDIVX', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTENRESYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTENRESYNC, self).__init__(register,
            'CLKMULTENRESYNC', 'RAC_S.CLKMULTCTRL.CLKMULTENRESYNC', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTVALID, self).__init__(register,
            'CLKMULTVALID', 'RAC_S.CLKMULTCTRL.CLKMULTVALID', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTSTATUS_CLKMULTOUTNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTSTATUS_CLKMULTOUTNIBBLE, self).__init__(register,
            'CLKMULTOUTNIBBLE', 'RAC_S.CLKMULTSTATUS.CLKMULTOUTNIBBLE', 'read-only',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTSTATUS_CLKMULTACKVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTSTATUS_CLKMULTACKVALID, self).__init__(register,
            'CLKMULTACKVALID', 'RAC_S.CLKMULTSTATUS.CLKMULTACKVALID', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCDBG_IFADCENADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_IFADCENADC, self).__init__(register,
            'IFADCENADC', 'RAC_S.IFADCDBG.IFADCENADC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCDBG_IFADCENCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_IFADCENCLK, self).__init__(register,
            'IFADCENCLK', 'RAC_S.IFADCDBG.IFADCENCLK', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCDBG_IFADCENREFBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_IFADCENREFBUF, self).__init__(register,
            'IFADCENREFBUF', 'RAC_S.IFADCDBG.IFADCENREFBUF', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCDBG_IFADCENSIDETONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_IFADCENSIDETONE, self).__init__(register,
            'IFADCENSIDETONE', 'RAC_S.IFADCDBG.IFADCENSIDETONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCDBG_IFADCINVERTCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_IFADCINVERTCLK, self).__init__(register,
            'IFADCINVERTCLK', 'RAC_S.IFADCDBG.IFADCINVERTCLK', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCDBG_IFADCSHORTINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_IFADCSHORTINPUT, self).__init__(register,
            'IFADCSHORTINPUT', 'RAC_S.IFADCDBG.IFADCSHORTINPUT', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCCLKSEL, self).__init__(register,
            'IFADCCLKSEL', 'RAC_S.IFADCTRIM.IFADCCLKSEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCENHALFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCENHALFMODE, self).__init__(register,
            'IFADCENHALFMODE', 'RAC_S.IFADCTRIM.IFADCENHALFMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCLDOSERIESAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCLDOSERIESAMPLVL, self).__init__(register,
            'IFADCLDOSERIESAMPLVL', 'RAC_S.IFADCTRIM.IFADCLDOSERIESAMPLVL', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCLDOSHUNTAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCLDOSHUNTAMPLVL, self).__init__(register,
            'IFADCLDOSHUNTAMPLVL', 'RAC_S.IFADCTRIM.IFADCLDOSHUNTAMPLVL', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCLDOSHUNTCURLP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCLDOSHUNTCURLP, self).__init__(register,
            'IFADCLDOSHUNTCURLP', 'RAC_S.IFADCTRIM.IFADCLDOSHUNTCURLP', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCLDOSHUNTCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCLDOSHUNTCURLVL, self).__init__(register,
            'IFADCLDOSHUNTCURLVL', 'RAC_S.IFADCTRIM.IFADCLDOSHUNTCURLVL', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCOTAST1CURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCOTAST1CURRENT, self).__init__(register,
            'IFADCOTAST1CURRENT', 'RAC_S.IFADCTRIM.IFADCOTAST1CURRENT', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCOTAST2CURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCOTAST2CURRENT, self).__init__(register,
            'IFADCOTAST2CURRENT', 'RAC_S.IFADCTRIM.IFADCOTAST2CURRENT', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCREFBUFAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCREFBUFAMPLVL, self).__init__(register,
            'IFADCREFBUFAMPLVL', 'RAC_S.IFADCTRIM.IFADCREFBUFAMPLVL', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCREFBUFCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCREFBUFCURLVL, self).__init__(register,
            'IFADCREFBUFCURLVL', 'RAC_S.IFADCTRIM.IFADCREFBUFCURLVL', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCSIDETONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCSIDETONEAMP, self).__init__(register,
            'IFADCSIDETONEAMP', 'RAC_S.IFADCTRIM.IFADCSIDETONEAMP', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCSIDETONEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCSIDETONEFREQ, self).__init__(register,
            'IFADCSIDETONEFREQ', 'RAC_S.IFADCTRIM.IFADCSIDETONEFREQ', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCTUNEZERO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCTUNEZERO, self).__init__(register,
            'IFADCTUNEZERO', 'RAC_S.IFADCTRIM.IFADCTUNEZERO', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM_IFADCVCMLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM_IFADCVCMLVL, self).__init__(register,
            'IFADCVCMLVL', 'RAC_S.IFADCTRIM.IFADCVCMLVL', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCCAL_IFADCENRCCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCCAL_IFADCENRCCAL, self).__init__(register,
            'IFADCENRCCAL', 'RAC_S.IFADCCAL.IFADCENRCCAL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCCAL_IFADCTUNERCCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCCAL_IFADCTUNERCCALMODE, self).__init__(register,
            'IFADCTUNERCCALMODE', 'RAC_S.IFADCCAL.IFADCTUNERCCALMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCCAL_IFADCTUNERC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCCAL_IFADCTUNERC, self).__init__(register,
            'IFADCTUNERC', 'RAC_S.IFADCCAL.IFADCTUNERC', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCSTATUS_IFADCRCCALOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCSTATUS_IFADCRCCALOUT, self).__init__(register,
            'IFADCRCCALOUT', 'RAC_S.IFADCSTATUS.IFADCRCCALOUT', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXDEBUG_LNAMIXDISMXR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXDEBUG_LNAMIXDISMXR1, self).__init__(register,
            'LNAMIXDISMXR1', 'RAC_S.LNAMIXDEBUG.LNAMIXDISMXR1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXDEBUG_LNAMIXDISMXR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXDEBUG_LNAMIXDISMXR2, self).__init__(register,
            'LNAMIXDISMXR2', 'RAC_S.LNAMIXDEBUG.LNAMIXDISMXR2', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXCURCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXCURCTRL, self).__init__(register,
            'LNAMIXCURCTRL', 'RAC_S.LNAMIXTRIM0.LNAMIXCURCTRL', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXHIGHCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXHIGHCUR, self).__init__(register,
            'LNAMIXHIGHCUR', 'RAC_S.LNAMIXTRIM0.LNAMIXHIGHCUR', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXLOWCUR, self).__init__(register,
            'LNAMIXLOWCUR', 'RAC_S.LNAMIXTRIM0.LNAMIXLOWCUR', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDBWSEL, self).__init__(register,
            'LNAMIXRFPKDBWSEL', 'RAC_S.LNAMIXTRIM0.LNAMIXRFPKDBWSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDCALCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDCALCM, self).__init__(register,
            'LNAMIXRFPKDCALCM', 'RAC_S.LNAMIXTRIM0.LNAMIXRFPKDCALCM', 'read-write',
            u"",
            12, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDCALDM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDCALDM, self).__init__(register,
            'LNAMIXRFPKDCALDM', 'RAC_S.LNAMIXTRIM0.LNAMIXRFPKDCALDM', 'read-write',
            u"",
            18, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXTRIMVREG, self).__init__(register,
            'LNAMIXTRIMVREG', 'RAC_S.LNAMIXTRIM0.LNAMIXTRIMVREG', 'read-write',
            u"",
            23, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXIBIAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXIBIAS1ADJ, self).__init__(register,
            'LNAMIXIBIAS1ADJ', 'RAC_S.LNAMIXTRIM1.LNAMIXIBIAS1ADJ', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXLNA1CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXLNA1CAPSEL, self).__init__(register,
            'LNAMIXLNA1CAPSEL', 'RAC_S.LNAMIXTRIM1.LNAMIXLNA1CAPSEL', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXMXRBIAS1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXMXRBIAS1, self).__init__(register,
            'LNAMIXMXRBIAS1', 'RAC_S.LNAMIXTRIM1.LNAMIXMXRBIAS1', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXNCAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXNCAS1ADJ, self).__init__(register,
            'LNAMIXNCAS1ADJ', 'RAC_S.LNAMIXTRIM1.LNAMIXNCAS1ADJ', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXPCAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXPCAS1ADJ, self).__init__(register,
            'LNAMIXPCAS1ADJ', 'RAC_S.LNAMIXTRIM1.LNAMIXPCAS1ADJ', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXVOUT1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXVOUT1ADJ, self).__init__(register,
            'LNAMIXVOUT1ADJ', 'RAC_S.LNAMIXTRIM1.LNAMIXVOUT1ADJ', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXIBIAS2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXIBIAS2ADJ, self).__init__(register,
            'LNAMIXIBIAS2ADJ', 'RAC_S.LNAMIXTRIM2.LNAMIXIBIAS2ADJ', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXLNA2CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXLNA2CAPSEL, self).__init__(register,
            'LNAMIXLNA2CAPSEL', 'RAC_S.LNAMIXTRIM2.LNAMIXLNA2CAPSEL', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXMXRBIAS2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXMXRBIAS2, self).__init__(register,
            'LNAMIXMXRBIAS2', 'RAC_S.LNAMIXTRIM2.LNAMIXMXRBIAS2', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXNCAS2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXNCAS2ADJ, self).__init__(register,
            'LNAMIXNCAS2ADJ', 'RAC_S.LNAMIXTRIM2.LNAMIXNCAS2ADJ', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXPCAS2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXPCAS2ADJ, self).__init__(register,
            'LNAMIXPCAS2ADJ', 'RAC_S.LNAMIXTRIM2.LNAMIXPCAS2ADJ', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXVOUT2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXVOUT2ADJ, self).__init__(register,
            'LNAMIXVOUT2ADJ', 'RAC_S.LNAMIXTRIM2.LNAMIXVOUT2ADJ', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALEN, self).__init__(register,
            'LNAMIXCALEN', 'RAC_S.LNAMIXCAL.LNAMIXCALEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALVMODE, self).__init__(register,
            'LNAMIXCALVMODE', 'RAC_S.LNAMIXCAL.LNAMIXCALVMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXENIRCAL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXENIRCAL1, self).__init__(register,
            'LNAMIXENIRCAL1', 'RAC_S.LNAMIXCAL.LNAMIXENIRCAL1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXENIRCAL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXENIRCAL2, self).__init__(register,
            'LNAMIXENIRCAL2', 'RAC_S.LNAMIXCAL.LNAMIXENIRCAL2', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL1AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL1AMP, self).__init__(register,
            'LNAMIXIRCAL1AMP', 'RAC_S.LNAMIXCAL.LNAMIXIRCAL1AMP', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL2AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL2AMP, self).__init__(register,
            'LNAMIXIRCAL2AMP', 'RAC_S.LNAMIXCAL.LNAMIXIRCAL2AMP', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN_LNAMIXENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN_LNAMIXENLDO, self).__init__(register,
            'LNAMIXENLDO', 'RAC_S.LNAMIXEN.LNAMIXENLDO', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREBYPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREBYPFORCE, self).__init__(register,
            'PREBYPFORCE', 'RAC_S.PRECTRL.PREBYPFORCE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGTRIM, self).__init__(register,
            'PREREGTRIM', 'RAC_S.PRECTRL.PREREGTRIM', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREVREFTRIM, self).__init__(register,
            'PREVREFTRIM', 'RAC_S.PRECTRL.PREVREFTRIM', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMDRVREGIBCORE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMDRVREGIBCORE0DBM, self).__init__(register,
            'PATRIMDRVREGIBCORE0DBM', 'RAC_S.PATRIM0.PATRIMDRVREGIBCORE0DBM', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMDRVREGIBNDIO0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMDRVREGIBNDIO0DBM, self).__init__(register,
            'PATRIMDRVREGIBNDIO0DBM', 'RAC_S.PATRIM0.PATRIMDRVREGIBNDIO0DBM', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMDRVREGPSR0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMDRVREGPSR0DBM, self).__init__(register,
            'PATRIMDRVREGPSR0DBM', 'RAC_S.PATRIM0.PATRIMDRVREGPSR0DBM', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMDRVSLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMDRVSLICE0DBM, self).__init__(register,
            'PATRIMDRVSLICE0DBM', 'RAC_S.PATRIM0.PATRIMDRVSLICE0DBM', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMFB0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMFB0DBM, self).__init__(register,
            'PATRIMFB0DBM', 'RAC_S.PATRIM0.PATRIMFB0DBM', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMPABIASN0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMPABIASN0DBM, self).__init__(register,
            'PATRIMPABIASN0DBM', 'RAC_S.PATRIM0.PATRIMPABIASN0DBM', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMPABIASP0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMPABIASP0DBM, self).__init__(register,
            'PATRIMPABIASP0DBM', 'RAC_S.PATRIM0.PATRIMPABIASP0DBM', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMPASLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMPASLICE0DBM, self).__init__(register,
            'PATRIMPASLICE0DBM', 'RAC_S.PATRIM0.PATRIMPASLICE0DBM', 'read-write',
            u"",
            21, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_PATRIMVREF0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_PATRIMVREF0DBM, self).__init__(register,
            'PATRIMVREF0DBM', 'RAC_S.PATRIM0.PATRIMVREF0DBM', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIM10DBMDUTYCYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIM10DBMDUTYCYN, self).__init__(register,
            'PATRIM10DBMDUTYCYN', 'RAC_S.PATRIM1.PATRIM10DBMDUTYCYN', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIM10DBMDUTYCYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIM10DBMDUTYCYP, self).__init__(register,
            'PATRIM10DBMDUTYCYP', 'RAC_S.PATRIM1.PATRIM10DBMDUTYCYP', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIM20DBMPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIM20DBMPREDRV, self).__init__(register,
            'PATRIM20DBMPREDRV', 'RAC_S.PATRIM1.PATRIM20DBMPREDRV', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMANTSWBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMANTSWBIAS, self).__init__(register,
            'PATRIMANTSWBIAS', 'RAC_S.PATRIM1.PATRIMANTSWBIAS', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMBLEEDAUTOPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMBLEEDAUTOPREREG, self).__init__(register,
            'PATRIMBLEEDAUTOPREREG', 'RAC_S.PATRIM1.PATRIMBLEEDAUTOPREREG', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMCAPPAOUTM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMCAPPAOUTM, self).__init__(register,
            'PATRIMCAPPAOUTM', 'RAC_S.PATRIM1.PATRIMCAPPAOUTM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMCAPPAOUTP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMCAPPAOUTP, self).__init__(register,
            'PATRIMCAPPAOUTP', 'RAC_S.PATRIM1.PATRIMCAPPAOUTP', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMCMGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMCMGAIN, self).__init__(register,
            'PATRIMCMGAIN', 'RAC_S.PATRIM1.PATRIMCMGAIN', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMDLY0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMDLY0, self).__init__(register,
            'PATRIMDLY0', 'RAC_S.PATRIM1.PATRIMDLY0', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMDLY1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMDLY1, self).__init__(register,
            'PATRIMDLY1', 'RAC_S.PATRIM1.PATRIMDLY1', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMFBKATTPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMFBKATTPDRVLDO, self).__init__(register,
            'PATRIMFBKATTPDRVLDO', 'RAC_S.PATRIM1.PATRIMFBKATTPDRVLDO', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_PATRIMIBIASMASTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_PATRIMIBIASMASTER, self).__init__(register,
            'PATRIMIBIASMASTER', 'RAC_S.PATRIM1.PATRIMIBIASMASTER', 'read-write',
            u"",
            29, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMLDOFBHVPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMLDOFBHVPDRVLDO, self).__init__(register,
            'PATRIMLDOFBHVPDRVLDO', 'RAC_S.PATRIM2.PATRIMLDOFBHVPDRVLDO', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMLDOFBHVPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMLDOFBHVPREREG, self).__init__(register,
            'PATRIMLDOFBHVPREREG', 'RAC_S.PATRIM2.PATRIMLDOFBHVPREREG', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMLDOHVPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMLDOHVPDRVLDO, self).__init__(register,
            'PATRIMLDOHVPDRVLDO', 'RAC_S.PATRIM2.PATRIMLDOHVPDRVLDO', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMLDOHVPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMLDOHVPREREG, self).__init__(register,
            'PATRIMLDOHVPREREG', 'RAC_S.PATRIM2.PATRIMLDOHVPREREG', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMLDOPSRPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMLDOPSRPDRVLDO, self).__init__(register,
            'PATRIMLDOPSRPDRVLDO', 'RAC_S.PATRIM2.PATRIMLDOPSRPDRVLDO', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMLDOPSRPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMLDOPSRPREREG, self).__init__(register,
            'PATRIMLDOPSRPREREG', 'RAC_S.PATRIM2.PATRIMLDOPSRPREREG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMLDOSLICESPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMLDOSLICESPDRVLDO, self).__init__(register,
            'PATRIMLDOSLICESPDRVLDO', 'RAC_S.PATRIM2.PATRIMLDOSLICESPDRVLDO', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMLDOSLICESPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMLDOSLICESPREREG, self).__init__(register,
            'PATRIMLDOSLICESPREREG', 'RAC_S.PATRIM2.PATRIMLDOSLICESPREREG', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMPADACGLITCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMPADACGLITCH, self).__init__(register,
            'PATRIMPADACGLITCH', 'RAC_S.PATRIM2.PATRIMPADACGLITCH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMNBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMNBIAS, self).__init__(register,
            'PATRIMNBIAS', 'RAC_S.PATRIM2.PATRIMNBIAS', 'read-write',
            u"",
            19, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMNCASC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMNCASC, self).__init__(register,
            'PATRIMNCASC', 'RAC_S.PATRIM2.PATRIMNCASC', 'read-write',
            u"",
            23, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMPBIAS, self).__init__(register,
            'PATRIMPBIAS', 'RAC_S.PATRIM2.PATRIMPBIAS', 'read-write',
            u"",
            25, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_PATRIMPCASC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_PATRIMPCASC, self).__init__(register,
            'PATRIMPCASC', 'RAC_S.PATRIM2.PATRIMPCASC', 'read-write',
            u"",
            29, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAEN10DBMVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAEN10DBMVMID, self).__init__(register,
            'PAEN10DBMVMID', 'RAC_S.PACTRL.PAEN10DBMVMID', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAEN20DBMVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAEN20DBMVMID, self).__init__(register,
            'PAEN20DBMVMID', 'RAC_S.PACTRL.PAEN20DBMVMID', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAENCAPATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAENCAPATT, self).__init__(register,
            'PAENCAPATT', 'RAC_S.PACTRL.PAENCAPATT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAENLATCHBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAENLATCHBYPASS, self).__init__(register,
            'PAENLATCHBYPASS', 'RAC_S.PACTRL.PAENLATCHBYPASS', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAENPOWERRAMPINGCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAENPOWERRAMPINGCLK, self).__init__(register,
            'PAENPOWERRAMPINGCLK', 'RAC_S.PACTRL.PAENPOWERRAMPINGCLK', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAPULLDOWNVDDPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAPULLDOWNVDDPA, self).__init__(register,
            'PAPULLDOWNVDDPA', 'RAC_S.PACTRL.PAPULLDOWNVDDPA', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAREGBYPASSPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAREGBYPASSPDRVLDO, self).__init__(register,
            'PAREGBYPASSPDRVLDO', 'RAC_S.PACTRL.PAREGBYPASSPDRVLDO', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAREGBYPASSPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAREGBYPASSPREREG, self).__init__(register,
            'PAREGBYPASSPREREG', 'RAC_S.PACTRL.PAREGBYPASSPREREG', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PASELLDOVDDPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PASELLDOVDDPA, self).__init__(register,
            'PASELLDOVDDPA', 'RAC_S.PACTRL.PASELLDOVDDPA', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PASELLDOVDDRF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PASELLDOVDDRF, self).__init__(register,
            'PASELLDOVDDRF', 'RAC_S.PACTRL.PASELLDOVDDRF', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PASLICERST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PASLICERST, self).__init__(register,
            'PASLICERST', 'RAC_S.PACTRL.PASLICERST', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PAPOWER, self).__init__(register,
            'PAPOWER', 'RAC_S.PACTRL.PAPOWER', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_PASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_PASELSLICE, self).__init__(register,
            'PASELSLICE', 'RAC_S.PACTRL.PASELSLICE', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGADEBUG_PGACCTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGADEBUG_PGACCTRIM, self).__init__(register,
            'PGACCTRIM', 'RAC_S.PGADEBUG.PGACCTRIM', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGATRIM_PGACTUNE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGATRIM_PGACTUNE, self).__init__(register,
            'PGACTUNE', 'RAC_S.PGATRIM.PGACTUNE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGATRIM_PGADISANTILOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGATRIM_PGADISANTILOCK, self).__init__(register,
            'PGADISANTILOCK', 'RAC_S.PGATRIM.PGADISANTILOCK', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGATRIM_PGAVCMOUTTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGATRIM_PGAVCMOUTTRIM, self).__init__(register,
            'PGAVCMOUTTRIM', 'RAC_S.PGATRIM.PGAVCMOUTTRIM', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGATRIM_PGAVLDOTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGATRIM_PGAVLDOTRIM, self).__init__(register,
            'PGAVLDOTRIM', 'RAC_S.PGATRIM.PGAVLDOTRIM', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACAL_PGAOFFNCALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACAL_PGAOFFNCALI, self).__init__(register,
            'PGAOFFNCALI', 'RAC_S.PGACAL.PGAOFFNCALI', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACAL_PGAOFFNCALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACAL_PGAOFFNCALQ, self).__init__(register,
            'PGAOFFNCALQ', 'RAC_S.PGACAL.PGAOFFNCALQ', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACAL_PGAOFFPCALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACAL_PGAOFFPCALI, self).__init__(register,
            'PGAOFFPCALI', 'RAC_S.PGACAL.PGAOFFPCALI', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACAL_PGAOFFPCALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACAL_PGAOFFPCALQ, self).__init__(register,
            'PGAOFFPCALQ', 'RAC_S.PGACAL.PGAOFFPCALQ', 'read-write',
            u"",
            24, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGABWMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGABWMODE, self).__init__(register,
            'PGABWMODE', 'RAC_S.PGACTRL.PGABWMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENBIAS, self).__init__(register,
            'PGAENBIAS', 'RAC_S.PGACTRL.PGAENBIAS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENGHZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENGHZ, self).__init__(register,
            'PGAENGHZ', 'RAC_S.PGACTRL.PGAENGHZ', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENHYST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENHYST, self).__init__(register,
            'PGAENHYST', 'RAC_S.PGACTRL.PGAENHYST', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENLATCHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENLATCHI, self).__init__(register,
            'PGAENLATCHI', 'RAC_S.PGACTRL.PGAENLATCHI', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENLATCHQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENLATCHQ, self).__init__(register,
            'PGAENLATCHQ', 'RAC_S.PGACTRL.PGAENLATCHQ', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENLDOLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENLDOLOAD, self).__init__(register,
            'PGAENLDOLOAD', 'RAC_S.PGACTRL.PGAENLDOLOAD', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENOFFD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENOFFD, self).__init__(register,
            'PGAENOFFD', 'RAC_S.PGACTRL.PGAENOFFD', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENPGAI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENPGAI, self).__init__(register,
            'PGAENPGAI', 'RAC_S.PGACTRL.PGAENPGAI', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENPGAQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENPGAQ, self).__init__(register,
            'PGAENPGAQ', 'RAC_S.PGACTRL.PGAENPGAQ', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENPKD, self).__init__(register,
            'PGAENPKD', 'RAC_S.PGACTRL.PGAENPKD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENRCMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENRCMOUT, self).__init__(register,
            'PGAENRCMOUT', 'RAC_S.PGACTRL.PGAENRCMOUT', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENSUBG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENSUBG, self).__init__(register,
            'PGAENSUBG', 'RAC_S.PGACTRL.PGAENSUBG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAPOWERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAPOWERMODE, self).__init__(register,
            'PGAPOWERMODE', 'RAC_S.PGACTRL.PGAPOWERMODE', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGATHRPKDLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGATHRPKDLOSEL, self).__init__(register,
            'PGATHRPKDLOSEL', 'RAC_S.PGACTRL.PGATHRPKDLOSEL', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGATHRPKDHISEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGATHRPKDHISEL, self).__init__(register,
            'PGATHRPKDHISEL', 'RAC_S.PGACTRL.PGATHRPKDHISEL', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_LNAMIXRFPKDTHRESHSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_LNAMIXRFPKDTHRESHSEL, self).__init__(register,
            'LNAMIXRFPKDTHRESHSEL', 'RAC_S.PGACTRL.LNAMIXRFPKDTHRESHSEL', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCAL_RFBIASCALBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCAL_RFBIASCALBIAS, self).__init__(register,
            'RFBIASCALBIAS', 'RAC_S.RFBIASCAL.RFBIASCALBIAS', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCAL_RFBIASCALTC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCAL_RFBIASCALTC, self).__init__(register,
            'RFBIASCALTC', 'RAC_S.RFBIASCAL.RFBIASCALTC', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCAL_RFBIASCALVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCAL_RFBIASCALVREF, self).__init__(register,
            'RFBIASCALVREF', 'RAC_S.RFBIASCAL.RFBIASCALVREF', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCAL_RFBIASCALVREFSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCAL_RFBIASCALVREFSTARTUP, self).__init__(register,
            'RFBIASCALVREFSTARTUP', 'RAC_S.RFBIASCAL.RFBIASCALVREFSTARTUP', 'read-write',
            u"",
            24, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP, self).__init__(register,
            'RFBIASDISABLEBOOTSTRAP', 'RAC_S.RFBIASCTRL.RFBIASDISABLEBOOTSTRAP', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCTRL_RFBIASLDOHIGHCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCTRL_RFBIASLDOHIGHCURRENT, self).__init__(register,
            'RFBIASLDOHIGHCURRENT', 'RAC_S.RFBIASCTRL.RFBIASLDOHIGHCURRENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCTRL_RFBIASNONFLASHMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCTRL_RFBIASNONFLASHMODE, self).__init__(register,
            'RFBIASNONFLASHMODE', 'RAC_S.RFBIASCTRL.RFBIASNONFLASHMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCTRL_RFBIASSTARTUPCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCTRL_RFBIASSTARTUPCORE, self).__init__(register,
            'RFBIASSTARTUPCORE', 'RAC_S.RFBIASCTRL.RFBIASSTARTUPCORE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCTRL_RFBIASSTARTUPSUPPLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCTRL_RFBIASSTARTUPSUPPLY, self).__init__(register,
            'RFBIASSTARTUPSUPPLY', 'RAC_S.RFBIASCTRL.RFBIASSTARTUPSUPPLY', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFBIASCTRL_RFBIASLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFBIASCTRL_RFBIASLDOVREFTRIM, self).__init__(register,
            'RFBIASLDOVREFTRIM', 'RAC_S.RFBIASCTRL.RFBIASLDOVREFTRIM', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RADIOEN_PREEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RADIOEN_PREEN, self).__init__(register,
            'PREEN', 'RAC_S.RADIOEN.PREEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RADIOEN_PRESTB100UDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RADIOEN_PRESTB100UDIS, self).__init__(register,
            'PRESTB100UDIS', 'RAC_S.RADIOEN.PRESTB100UDIS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RADIOEN_RFBIASEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RADIOEN_RFBIASEN, self).__init__(register,
            'RFBIASEN', 'RAC_S.RADIOEN.RFBIASEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXEN0DBMPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXEN0DBMPA1, self).__init__(register,
            'LNAMIXEN0DBMPA1', 'RAC_S.RFPATHEN1.LNAMIXEN0DBMPA1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXEN1, self).__init__(register,
            'LNAMIXEN1', 'RAC_S.RFPATHEN1.LNAMIXEN1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXRFATTDCEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXRFATTDCEN1, self).__init__(register,
            'LNAMIXRFATTDCEN1', 'RAC_S.RFPATHEN1.LNAMIXRFATTDCEN1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXRFPKDENRF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXRFPKDENRF1, self).__init__(register,
            'LNAMIXRFPKDENRF1', 'RAC_S.RFPATHEN1.LNAMIXRFPKDENRF1', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXTRSW1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXTRSW1, self).__init__(register,
            'LNAMIXTRSW1', 'RAC_S.RFPATHEN1.LNAMIXTRSW1', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_PAENANT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_PAENANT1, self).__init__(register,
            'PAENANT1', 'RAC_S.RFPATHEN1.PAENANT1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_PAENPA10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_PAENPA10DBM, self).__init__(register,
            'PAENPA10DBM', 'RAC_S.RFPATHEN1.PAENPA10DBM', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_PAENPAPREDRV10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_PAENPAPREDRV10DBM, self).__init__(register,
            'PAENPAPREDRV10DBM', 'RAC_S.RFPATHEN1.PAENPAPREDRV10DBM', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN2_LNAMIXEN0DBMPA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN2_LNAMIXEN0DBMPA2, self).__init__(register,
            'LNAMIXEN0DBMPA2', 'RAC_S.RFPATHEN2.LNAMIXEN0DBMPA2', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN2_LNAMIXEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN2_LNAMIXEN2, self).__init__(register,
            'LNAMIXEN2', 'RAC_S.RFPATHEN2.LNAMIXEN2', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN2_LNAMIXRFATTDCEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN2_LNAMIXRFATTDCEN2, self).__init__(register,
            'LNAMIXRFATTDCEN2', 'RAC_S.RFPATHEN2.LNAMIXRFATTDCEN2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN2_LNAMIXRFPKDENRF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN2_LNAMIXRFPKDENRF2, self).__init__(register,
            'LNAMIXRFPKDENRF2', 'RAC_S.RFPATHEN2.LNAMIXRFPKDENRF2', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN2_LNAMIXTRSW2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN2_LNAMIXTRSW2, self).__init__(register,
            'LNAMIXTRSW2', 'RAC_S.RFPATHEN2.LNAMIXTRSW2', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN2_PAENANT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN2_PAENANT2, self).__init__(register,
            'PAENANT2', 'RAC_S.RFPATHEN2.PAENANT2', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN2_PAENPA20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN2_PAENPA20DBM, self).__init__(register,
            'PAENPA20DBM', 'RAC_S.RFPATHEN2.PAENPA20DBM', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN2_PAENPAPREDRV20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN2_PAENPAPREDRV20DBM, self).__init__(register,
            'PAENPAPREDRV20DBM', 'RAC_S.RFPATHEN2.PAENPAPREDRV20DBM', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_IFADCCAPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_IFADCCAPRESET, self).__init__(register,
            'IFADCCAPRESET', 'RAC_S.RX.IFADCCAPRESET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_IFADCENLDOSERIES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_IFADCENLDOSERIES, self).__init__(register,
            'IFADCENLDOSERIES', 'RAC_S.RX.IFADCENLDOSERIES', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_IFADCENLDOSHUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_IFADCENLDOSHUNT, self).__init__(register,
            'IFADCENLDOSHUNT', 'RAC_S.RX.IFADCENLDOSHUNT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXENRFPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXENRFPKD, self).__init__(register,
            'LNAMIXENRFPKD', 'RAC_S.RX.LNAMIXENRFPKD', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXLDOLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXLDOLOWCUR, self).__init__(register,
            'LNAMIXLDOLOWCUR', 'RAC_S.RX.LNAMIXLDOLOWCUR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXREGLOADEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXREGLOADEN, self).__init__(register,
            'LNAMIXREGLOADEN', 'RAC_S.RX.LNAMIXREGLOADEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_PGAENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_PGAENLDO, self).__init__(register,
            'PGAENLDO', 'RAC_S.RX.PGAENLDO', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYCHPBIASTRIMBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYCHPBIASTRIMBUF, self).__init__(register,
            'SYCHPBIASTRIMBUF', 'RAC_S.RX.SYCHPBIASTRIMBUF', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYCHPQNC3EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYCHPQNC3EN, self).__init__(register,
            'SYCHPQNC3EN', 'RAC_S.RX.SYCHPQNC3EN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYMMDMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYMMDMODE, self).__init__(register,
            'SYMMDMODE', 'RAC_S.RX.SYMMDMODE', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYPFDCHPLPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYPFDCHPLPEN, self).__init__(register,
            'SYPFDCHPLPEN', 'RAC_S.RX.SYPFDCHPLPEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYPFDFPWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYPFDFPWEN, self).__init__(register,
            'SYPFDFPWEN', 'RAC_S.RX.SYPFDFPWEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PABLEEDDRVREG0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PABLEEDDRVREG0DBM, self).__init__(register,
            'PABLEEDDRVREG0DBM', 'RAC_S.TX.PABLEEDDRVREG0DBM', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PABLEEDREG0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PABLEEDREG0DBM, self).__init__(register,
            'PABLEEDREG0DBM', 'RAC_S.TX.PABLEEDREG0DBM', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENBIAS0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENBIAS0DBM, self).__init__(register,
            'PAENBIAS0DBM', 'RAC_S.TX.PAENBIAS0DBM', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENDRVREG0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENDRVREG0DBM, self).__init__(register,
            'PAENDRVREG0DBM', 'RAC_S.TX.PAENDRVREG0DBM', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENDRVREGBIAS0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENDRVREGBIAS0DBM, self).__init__(register,
            'PAENDRVREGBIAS0DBM', 'RAC_S.TX.PAENDRVREGBIAS0DBM', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENLO0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENLO0DBM, self).__init__(register,
            'PAENLO0DBM', 'RAC_S.TX.PAENLO0DBM', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENREG0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENREG0DBM, self).__init__(register,
            'PAENREG0DBM', 'RAC_S.TX.PAENREG0DBM', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENTAPCAP0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENTAPCAP0DBM, self).__init__(register,
            'PAENTAPCAP0DBM', 'RAC_S.TX.PAENTAPCAP0DBM', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_ENPATRIMPASLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_ENPATRIMPASLICE0DBM, self).__init__(register,
            'ENPATRIMPASLICE0DBM', 'RAC_S.TX.ENPATRIMPASLICE0DBM', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAEN10DBMM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAEN10DBMM, self).__init__(register,
            'PAEN10DBMM', 'RAC_S.TX.PAEN10DBMM', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAEN10DBMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAEN10DBMP, self).__init__(register,
            'PAEN10DBMP', 'RAC_S.TX.PAEN10DBMP', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAEN10DBMPDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAEN10DBMPDRV, self).__init__(register,
            'PAEN10DBMPDRV', 'RAC_S.TX.PAEN10DBMPDRV', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAEN20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAEN20DBM, self).__init__(register,
            'PAEN20DBM', 'RAC_S.TX.PAEN20DBM', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAEN20DBMPDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAEN20DBMPDRV, self).__init__(register,
            'PAEN20DBMPDRV', 'RAC_S.TX.PAEN20DBMPDRV', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENBLEEDPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENBLEEDPDRVLDO, self).__init__(register,
            'PAENBLEEDPDRVLDO', 'RAC_S.TX.PAENBLEEDPDRVLDO', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENBLEEDPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENBLEEDPREREG, self).__init__(register,
            'PAENBLEEDPREREG', 'RAC_S.TX.PAENBLEEDPREREG', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENLDOHVPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENLDOHVPDRVLDO, self).__init__(register,
            'PAENLDOHVPDRVLDO', 'RAC_S.TX.PAENLDOHVPDRVLDO', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENLDOHVPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENLDOHVPREREG, self).__init__(register,
            'PAENLDOHVPREREG', 'RAC_S.TX.PAENLDOHVPREREG', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAENPAOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAENPAOUT, self).__init__(register,
            'PAENPAOUT', 'RAC_S.TX.PAENPAOUT', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_ENXOSQBUFFILT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_ENXOSQBUFFILT, self).__init__(register,
            'ENXOSQBUFFILT', 'RAC_S.TX.ENXOSQBUFFILT', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_ENPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_ENPAPOWER, self).__init__(register,
            'ENPAPOWER', 'RAC_S.TX.ENPAPOWER', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_ENPASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_ENPASELSLICE, self).__init__(register,
            'ENPASELSLICE', 'RAC_S.TX.ENPASELSLICE', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYCHPSWITCHEDBIASEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYCHPSWITCHEDBIASEN, self).__init__(register,
            'SYCHPSWITCHEDBIASEN', 'RAC_S.SYDEBUG.SYCHPSWITCHEDBIASEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYENMMDDREGBIASSTB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYENMMDDREGBIASSTB, self).__init__(register,
            'SYENMMDDREGBIASSTB', 'RAC_S.SYDEBUG.SYENMMDDREGBIASSTB', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYLODIVAUXLODIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYLODIVAUXLODIS, self).__init__(register,
            'SYLODIVAUXLODIS', 'RAC_S.SYDEBUG.SYLODIVAUXLODIS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYLODIVCLKSYNCSGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYLODIVCLKSYNCSGEN, self).__init__(register,
            'SYLODIVCLKSYNCSGEN', 'RAC_S.SYDEBUG.SYLODIVCLKSYNCSGEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYLODIVLDOPSRTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYLODIVLDOPSRTRIM, self).__init__(register,
            'SYLODIVLDOPSRTRIM', 'RAC_S.SYDEBUG.SYLODIVLDOPSRTRIM', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYPFDLOCKWINDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYPFDLOCKWINDOWN, self).__init__(register,
            'SYPFDLOCKWINDOWN', 'RAC_S.SYDEBUG.SYPFDLOCKWINDOWN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYPFDTRADMODEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYPFDTRADMODEEN, self).__init__(register,
            'SYPFDTRADMODEEN', 'RAC_S.SYDEBUG.SYPFDTRADMODEEN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYVCOREGBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYVCOREGBYPASS, self).__init__(register,
            'SYVCOREGBYPASS', 'RAC_S.SYDEBUG.SYVCOREGBYPASS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPBIAS, self).__init__(register,
            'SYCHPBIAS', 'RAC_S.SYTRIM0.SYCHPBIAS', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPCURR, self).__init__(register,
            'SYCHPCURR', 'RAC_S.SYTRIM0.SYCHPCURR', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPLEVNSRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPLEVNSRC, self).__init__(register,
            'SYCHPLEVNSRC', 'RAC_S.SYTRIM0.SYCHPLEVNSRC', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPLEVPSRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPLEVPSRC, self).__init__(register,
            'SYCHPLEVPSRC', 'RAC_S.SYTRIM0.SYCHPLEVPSRC', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPSRCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPSRCEN, self).__init__(register,
            'SYCHPSRCEN', 'RAC_S.SYTRIM0.SYCHPSRCEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPREPLICACURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPREPLICACURRADJ, self).__init__(register,
            'SYCHPREPLICACURRADJ', 'RAC_S.SYTRIM0.SYCHPREPLICACURRADJ', 'read-write',
            u"",
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYTRIMCHPREGAMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYTRIMCHPREGAMPBIAS, self).__init__(register,
            'SYTRIMCHPREGAMPBIAS', 'RAC_S.SYTRIM0.SYTRIMCHPREGAMPBIAS', 'read-write',
            u"",
            17, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYTRIMCHPREGAMPBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYTRIMCHPREGAMPBW, self).__init__(register,
            'SYTRIMCHPREGAMPBW', 'RAC_S.SYTRIM0.SYTRIMCHPREGAMPBW', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMCORE, self).__init__(register,
            'SYLODIVLDOTRIMCORE', 'RAC_S.SYTRIM1.SYLODIVLDOTRIMCORE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMNDIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMNDIO, self).__init__(register,
            'SYLODIVLDOTRIMNDIO', 'RAC_S.SYTRIM1.SYLODIVLDOTRIMNDIO', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYMMDREPLICA1CURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYMMDREPLICA1CURRADJ, self).__init__(register,
            'SYMMDREPLICA1CURRADJ', 'RAC_S.SYTRIM1.SYMMDREPLICA1CURRADJ', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYMMDREPLICA2CURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYMMDREPLICA2CURRADJ, self).__init__(register,
            'SYMMDREPLICA2CURRADJ', 'RAC_S.SYTRIM1.SYMMDREPLICA2CURRADJ', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTRIMMMDREGAMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTRIMMMDREGAMPBIAS, self).__init__(register,
            'SYTRIMMMDREGAMPBIAS', 'RAC_S.SYTRIM1.SYTRIMMMDREGAMPBIAS', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTRIMMMDREGAMPBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTRIMMMDREGAMPBW, self).__init__(register,
            'SYTRIMMMDREGAMPBW', 'RAC_S.SYTRIM1.SYTRIMMMDREGAMPBW', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCAL_SYVCOMODEPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCAL_SYVCOMODEPKD, self).__init__(register,
            'SYVCOMODEPKD', 'RAC_S.SYCAL.SYVCOMODEPKD', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCAL_SYVCOMORECURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCAL_SYVCOMORECURRENT, self).__init__(register,
            'SYVCOMORECURRENT', 'RAC_S.SYCAL.SYVCOMORECURRENT', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCAL_SYVCOSLOWNOISEFILTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCAL_SYVCOSLOWNOISEFILTER, self).__init__(register,
            'SYVCOSLOWNOISEFILTER', 'RAC_S.SYCAL.SYVCOSLOWNOISEFILTER', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCAL_SYVCOVCAPVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCAL_SYVCOVCAPVCM, self).__init__(register,
            'SYVCOVCAPVCM', 'RAC_S.SYCAL.SYVCOVCAPVCM', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCAL_SYHILOADCHPREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCAL_SYHILOADCHPREG, self).__init__(register,
            'SYHILOADCHPREG', 'RAC_S.SYCAL.SYHILOADCHPREG', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYCHPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYCHPEN, self).__init__(register,
            'SYCHPEN', 'RAC_S.SYEN.SYCHPEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYCHPLPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYCHPLPEN, self).__init__(register,
            'SYCHPLPEN', 'RAC_S.SYEN.SYCHPLPEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENCHPREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENCHPREG, self).__init__(register,
            'SYENCHPREG', 'RAC_S.SYEN.SYENCHPREG', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENCHPREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENCHPREPLICA, self).__init__(register,
            'SYENCHPREPLICA', 'RAC_S.SYEN.SYENCHPREPLICA', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENMMDREG, self).__init__(register,
            'SYENMMDREG', 'RAC_S.SYEN.SYENMMDREG', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENMMDREPLICA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENMMDREPLICA1, self).__init__(register,
            'SYENMMDREPLICA1', 'RAC_S.SYEN.SYENMMDREPLICA1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENMMDREPLICA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENMMDREPLICA2, self).__init__(register,
            'SYENMMDREPLICA2', 'RAC_S.SYEN.SYENMMDREPLICA2', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOBIAS, self).__init__(register,
            'SYENVCOBIAS', 'RAC_S.SYEN.SYENVCOBIAS', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOPFET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOPFET, self).__init__(register,
            'SYENVCOPFET', 'RAC_S.SYEN.SYENVCOPFET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOREG, self).__init__(register,
            'SYENVCOREG', 'RAC_S.SYEN.SYENVCOREG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYLODIVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYLODIVEN, self).__init__(register,
            'SYLODIVEN', 'RAC_S.SYEN.SYLODIVEN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYLODIVLDOBIASEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYLODIVLDOBIASEN, self).__init__(register,
            'SYLODIVLDOBIASEN', 'RAC_S.SYEN.SYLODIVLDOBIASEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYLODIVLDOEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYLODIVLDOEN, self).__init__(register,
            'SYLODIVLDOEN', 'RAC_S.SYEN.SYLODIVLDOEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYSTARTCHPREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYSTARTCHPREG, self).__init__(register,
            'SYSTARTCHPREG', 'RAC_S.SYEN.SYSTARTCHPREG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYSTARTMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYSTARTMMDREG, self).__init__(register,
            'SYSTARTMMDREG', 'RAC_S.SYEN.SYSTARTMMDREG', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVRLOADCCLK2G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVRLOADCCLK2G4EN, self).__init__(register,
            'SYLODIVRLOADCCLK2G4EN', 'RAC_S.SYLOEN.SYLODIVRLOADCCLK2G4EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVRLO12G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVRLO12G4EN, self).__init__(register,
            'SYLODIVRLO12G4EN', 'RAC_S.SYLOEN.SYLODIVRLO12G4EN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVRLO1SGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVRLO1SGEN, self).__init__(register,
            'SYLODIVRLO1SGEN', 'RAC_S.SYLOEN.SYLODIVRLO1SGEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVRLO22G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVRLO22G4EN, self).__init__(register,
            'SYLODIVRLO22G4EN', 'RAC_S.SYLOEN.SYLODIVRLO22G4EN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVRLO2SGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVRLO2SGEN, self).__init__(register,
            'SYLODIVRLO2SGEN', 'RAC_S.SYLOEN.SYLODIVRLO2SGEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLO0DBM2G4AUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLO0DBM2G4AUXEN, self).__init__(register,
            'SYLODIVTLO0DBM2G4AUXEN', 'RAC_S.SYLOEN.SYLODIVTLO0DBM2G4AUXEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLO0DBM2G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLO0DBM2G4EN, self).__init__(register,
            'SYLODIVTLO0DBM2G4EN', 'RAC_S.SYLOEN.SYLODIVTLO0DBM2G4EN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLO0DBMSGAUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLO0DBMSGAUXEN, self).__init__(register,
            'SYLODIVTLO0DBMSGAUXEN', 'RAC_S.SYLOEN.SYLODIVTLO0DBMSGAUXEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLO0DBMSGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLO0DBMSGEN, self).__init__(register,
            'SYLODIVTLO0DBMSGEN', 'RAC_S.SYLOEN.SYLODIVTLO0DBMSGEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLO20DBM2G4AUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLO20DBM2G4AUXEN, self).__init__(register,
            'SYLODIVTLO20DBM2G4AUXEN', 'RAC_S.SYLOEN.SYLODIVTLO20DBM2G4AUXEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLO20DBM2G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLO20DBM2G4EN, self).__init__(register,
            'SYLODIVTLO20DBM2G4EN', 'RAC_S.SYLOEN.SYLODIVTLO20DBM2G4EN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLO20DBMSGAUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLO20DBMSGAUXEN, self).__init__(register,
            'SYLODIVTLO20DBMSGAUXEN', 'RAC_S.SYLOEN.SYLODIVTLO20DBMSGAUXEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLO20DBMSGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLO20DBMSGEN, self).__init__(register,
            'SYLODIVTLO20DBMSGEN', 'RAC_S.SYLOEN.SYLODIVTLO20DBMSGEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDENRSDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDENRSDIG, self).__init__(register,
            'SYMMDENRSDIG', 'RAC_S.SYMMDCTRL.SYMMDENRSDIG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDDIVRSDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDDIVRSDIG, self).__init__(register,
            'SYMMDDIVRSDIG', 'RAC_S.SYMMDCTRL.SYMMDDIVRSDIG', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME, self).__init__(register,
            'DIGCLKRETIMEENRETIME', 'RAC_S.DIGCLKRETIMECTRL.DIGCLKRETIMEENRETIME', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME, self).__init__(register,
            'DIGCLKRETIMEDISRETIME', 'RAC_S.DIGCLKRETIMECTRL.DIGCLKRETIMEDISRETIME', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN, self).__init__(register,
            'DIGCLKRETIMERESETN', 'RAC_S.DIGCLKRETIMECTRL.DIGCLKRETIMERESETN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH, self).__init__(register,
            'DIGCLKRETIMELIMITH', 'RAC_S.DIGCLKRETIMECTRL.DIGCLKRETIMELIMITH', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL, self).__init__(register,
            'DIGCLKRETIMELIMITL', 'RAC_S.DIGCLKRETIMECTRL.DIGCLKRETIMELIMITL', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL, self).__init__(register,
            'DIGCLKRETIMECLKSEL', 'RAC_S.DIGCLKRETIMESTATUS.DIGCLKRETIMECLKSEL', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO, self).__init__(register,
            'DIGCLKRETIMERESETNLO', 'RAC_S.DIGCLKRETIMESTATUS.DIGCLKRETIMERESETNLO', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_XORETIMECTRL_XORETIMEENRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_XORETIMECTRL_XORETIMEENRETIME, self).__init__(register,
            'XORETIMEENRETIME', 'RAC_S.XORETIMECTRL.XORETIMEENRETIME', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_XORETIMECTRL_XORETIMEDISRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_XORETIMECTRL_XORETIMEDISRETIME, self).__init__(register,
            'XORETIMEDISRETIME', 'RAC_S.XORETIMECTRL.XORETIMEDISRETIME', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_XORETIMECTRL_XORETIMERESETN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_XORETIMECTRL_XORETIMERESETN, self).__init__(register,
            'XORETIMERESETN', 'RAC_S.XORETIMECTRL.XORETIMERESETN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_XORETIMECTRL_XORETIMELIMITH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_XORETIMECTRL_XORETIMELIMITH, self).__init__(register,
            'XORETIMELIMITH', 'RAC_S.XORETIMECTRL.XORETIMELIMITH', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_XORETIMECTRL_XORETIMELIMITL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_XORETIMECTRL_XORETIMELIMITL, self).__init__(register,
            'XORETIMELIMITL', 'RAC_S.XORETIMECTRL.XORETIMELIMITL', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_XORETIMESTATUS_XORETIMECLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_XORETIMESTATUS_XORETIMECLKSEL, self).__init__(register,
            'XORETIMECLKSEL', 'RAC_S.XORETIMESTATUS.XORETIMECLKSEL', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_XORETIMESTATUS_XORETIMERESETNLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_XORETIMESTATUS_XORETIMERESETNLO, self).__init__(register,
            'XORETIMERESETNLO', 'RAC_S.XORETIMESTATUS.XORETIMERESETNLO', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_XOSQBUFFILT_XOSQBUFFILT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_XOSQBUFFILT_XOSQBUFFILT, self).__init__(register,
            'XOSQBUFFILT', 'RAC_S.XOSQBUFFILT.XOSQBUFFILT', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_AUXADCSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_AUXADCSPARE, self).__init__(register,
            'AUXADCSPARE', 'RAC_S.SPARE.AUXADCSPARE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_CLKMULTSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_CLKMULTSPARE, self).__init__(register,
            'CLKMULTSPARE', 'RAC_S.SPARE.CLKMULTSPARE', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_IFADCSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_IFADCSPARE, self).__init__(register,
            'IFADCSPARE', 'RAC_S.SPARE.IFADCSPARE', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_PATRIMSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_PATRIMSPARE, self).__init__(register,
            'PATRIMSPARE', 'RAC_S.SPARE.PATRIMSPARE', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_PGASPACER0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_PGASPACER0, self).__init__(register,
            'PGASPACER0', 'RAC_S.SPARE.PGASPACER0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_SYSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SYSPARE, self).__init__(register,
            'SYSPARE', 'RAC_S.SPARE.SYSPARE', 'read-write',
            u"",
            11, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_EN, self).__init__(register,
            'EN', 'RAC_S.ANTDIV.EN', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_STATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_STATUS, self).__init__(register,
            'STATUS', 'RAC_S.ANTDIV.STATUS', 'read-only',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SCRATCH0_SCRATCH0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SCRATCH0_SCRATCH0, self).__init__(register,
            'SCRATCH0', 'RAC_S.SCRATCH0.SCRATCH0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SCRATCH1_SCRATCH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SCRATCH1_SCRATCH1, self).__init__(register,
            'SCRATCH1', 'RAC_S.SCRATCH1.SCRATCH1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SCRATCH2_SCRATCH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SCRATCH2_SCRATCH2, self).__init__(register,
            'SCRATCH2', 'RAC_S.SCRATCH2.SCRATCH2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SCRATCH3_SCRATCH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SCRATCH3_SCRATCH3, self).__init__(register,
            'SCRATCH3', 'RAC_S.SCRATCH3.SCRATCH3', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SCRATCH4_SCRATCH4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SCRATCH4_SCRATCH4, self).__init__(register,
            'SCRATCH4', 'RAC_S.SCRATCH4.SCRATCH4', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SCRATCH5_SCRATCH5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SCRATCH5_SCRATCH5, self).__init__(register,
            'SCRATCH5', 'RAC_S.SCRATCH5.SCRATCH5', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SCRATCH6_SCRATCH6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SCRATCH6_SCRATCH6, self).__init__(register,
            'SCRATCH6', 'RAC_S.SCRATCH6.SCRATCH6', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SCRATCH7_SCRATCH7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SCRATCH7_SCRATCH7, self).__init__(register,
            'SCRATCH7', 'RAC_S.SCRATCH7.SCRATCH7', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_SYNTHLODIVFREQCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_SYNTHLODIVFREQCTRL, self).__init__(register,
            'SYNTHLODIVFREQCTRL', 'RAC_S.RFLOCK0.SYNTHLODIVFREQCTRL', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACIFPGAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACIFPGAEN, self).__init__(register,
            'RACIFPGAEN', 'RAC_S.RFLOCK0.RACIFPGAEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACPAEN10DBMM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACPAEN10DBMM, self).__init__(register,
            'RACPAEN10DBMM', 'RAC_S.RFLOCK0.RACPAEN10DBMM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACPAEN10DBMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACPAEN10DBMP, self).__init__(register,
            'RACPAEN10DBMP', 'RAC_S.RFLOCK0.RACPAEN10DBMP', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACPAEN20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACPAEN20DBM, self).__init__(register,
            'RACPAEN20DBM', 'RAC_S.RFLOCK0.RACPAEN20DBM', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACSGPAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACSGPAEN, self).__init__(register,
            'RACSGPAEN', 'RAC_S.RFLOCK0.RACSGPAEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_FRCCONVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_FRCCONVMODE, self).__init__(register,
            'FRCCONVMODE', 'RAC_S.RFLOCK0.FRCCONVMODE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_FRCPAUSING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_FRCPAUSING, self).__init__(register,
            'FRCPAUSING', 'RAC_S.RFLOCK0.FRCPAUSING', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_MODEMDSSS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_MODEMDSSS, self).__init__(register,
            'MODEMDSSS', 'RAC_S.RFLOCK0.MODEMDSSS', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_MODEMDEC1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_MODEMDEC1, self).__init__(register,
            'MODEMDEC1', 'RAC_S.RFLOCK0.MODEMDEC1', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_MODEMMODFORMAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_MODEMMODFORMAT, self).__init__(register,
            'MODEMMODFORMAT', 'RAC_S.RFLOCK0.MODEMMODFORMAT', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_MODEMDUALSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_MODEMDUALSYNC, self).__init__(register,
            'MODEMDUALSYNC', 'RAC_S.RFLOCK0.MODEMDUALSYNC', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_MODEMANTDIVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_MODEMANTDIVMODE, self).__init__(register,
            'MODEMANTDIVMODE', 'RAC_S.RFLOCK0.MODEMANTDIVMODE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'RAC_S.RFLOCK0.UNLOCKED', 'read-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_RACPASLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASLICE0DBM, self).__init__(register,
            'RACPASLICE0DBM', 'RAC_S.RFLOCK1.RACPASLICE0DBM', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_RACDRVSLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACDRVSLICE0DBM, self).__init__(register,
            'RACDRVSLICE0DBM', 'RAC_S.RFLOCK1.RACDRVSLICE0DBM', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_RACPASTRIPE10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASTRIPE10DBM, self).__init__(register,
            'RACPASTRIPE10DBM', 'RAC_S.RFLOCK1.RACPASTRIPE10DBM', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_RACPASLICE10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASLICE10DBM, self).__init__(register,
            'RACPASLICE10DBM', 'RAC_S.RFLOCK1.RACPASLICE10DBM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_RACPASTRIPE20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASTRIPE20DBM, self).__init__(register,
            'RACPASTRIPE20DBM', 'RAC_S.RFLOCK1.RACPASTRIPE20DBM', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_RACPASLICE20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASLICE20DBM, self).__init__(register,
            'RACPASLICE20DBM', 'RAC_S.RFLOCK1.RACPASLICE20DBM', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True



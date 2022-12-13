
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_RAC_NS_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'RAC_NS.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_EN_EN, self).__init__(register,
            'EN', 'RAC_NS.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RXENSRCEN_SWRXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RXENSRCEN_SWRXEN, self).__init__(register,
            'SWRXEN', 'RAC_NS.RXENSRCEN.SWRXEN', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RXENSRCEN_CHANNELBUSYEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RXENSRCEN_CHANNELBUSYEN, self).__init__(register,
            'CHANNELBUSYEN', 'RAC_NS.RXENSRCEN.CHANNELBUSYEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RXENSRCEN_TIMDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RXENSRCEN_TIMDETEN, self).__init__(register,
            'TIMDETEN', 'RAC_NS.RXENSRCEN.TIMDETEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RXENSRCEN_PREDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RXENSRCEN_PREDETEN, self).__init__(register,
            'PREDETEN', 'RAC_NS.RXENSRCEN.PREDETEN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RXENSRCEN_FRAMEDETEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RXENSRCEN_FRAMEDETEN, self).__init__(register,
            'FRAMEDETEN', 'RAC_NS.RXENSRCEN.FRAMEDETEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RXENSRCEN_DEMODRXREQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RXENSRCEN_DEMODRXREQEN, self).__init__(register,
            'DEMODRXREQEN', 'RAC_NS.RXENSRCEN.DEMODRXREQEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RXENSRCEN_PRSRXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RXENSRCEN_PRSRXEN, self).__init__(register,
            'PRSRXEN', 'RAC_NS.RXENSRCEN.PRSRXEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_RXMASK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_RXMASK, self).__init__(register,
            'RXMASK', 'RAC_NS.STATUS.RXMASK', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_FORCESTATEACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_FORCESTATEACTIVE, self).__init__(register,
            'FORCESTATEACTIVE', 'RAC_NS.STATUS.FORCESTATEACTIVE', 'read-only',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_TXAFTERFRAMEPEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_TXAFTERFRAMEPEND, self).__init__(register,
            'TXAFTERFRAMEPEND', 'RAC_NS.STATUS.TXAFTERFRAMEPEND', 'read-only',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_TXAFTERFRAMEACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_TXAFTERFRAMEACTIVE, self).__init__(register,
            'TXAFTERFRAMEACTIVE', 'RAC_NS.STATUS.TXAFTERFRAMEACTIVE', 'read-only',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_STATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_STATE, self).__init__(register,
            'STATE', 'RAC_NS.STATUS.STATE', 'read-only',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_DEMODENS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_DEMODENS, self).__init__(register,
            'DEMODENS', 'RAC_NS.STATUS.DEMODENS', 'read-only',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_TXENS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_TXENS, self).__init__(register,
            'TXENS', 'RAC_NS.STATUS.TXENS', 'read-only',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_RXENS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_RXENS, self).__init__(register,
            'RXENS', 'RAC_NS.STATUS.RXENS', 'read-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_TXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_TXEN, self).__init__(register,
            'TXEN', 'RAC_NS.CMD.TXEN', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_FORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_FORCETX, self).__init__(register,
            'FORCETX', 'RAC_NS.CMD.FORCETX', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_TXONCCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_TXONCCA, self).__init__(register,
            'TXONCCA', 'RAC_NS.CMD.TXONCCA', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_CLEARTXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_CLEARTXEN, self).__init__(register,
            'CLEARTXEN', 'RAC_NS.CMD.CLEARTXEN', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_TXAFTERFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_TXAFTERFRAME, self).__init__(register,
            'TXAFTERFRAME', 'RAC_NS.CMD.TXAFTERFRAME', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_TXDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_TXDIS, self).__init__(register,
            'TXDIS', 'RAC_NS.CMD.TXDIS', 'write-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_CLEARRXOVERFLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_CLEARRXOVERFLOW, self).__init__(register,
            'CLEARRXOVERFLOW', 'RAC_NS.CMD.CLEARRXOVERFLOW', 'write-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_RXCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_RXCAL, self).__init__(register,
            'RXCAL', 'RAC_NS.CMD.RXCAL', 'write-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_RXDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_RXDIS, self).__init__(register,
            'RXDIS', 'RAC_NS.CMD.RXDIS', 'write-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_PAENSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_PAENSET, self).__init__(register,
            'PAENSET', 'RAC_NS.CMD.PAENSET', 'write-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_PAENCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_PAENCLEAR, self).__init__(register,
            'PAENCLEAR', 'RAC_NS.CMD.PAENCLEAR', 'write-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_LNAENSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_LNAENSET, self).__init__(register,
            'LNAENSET', 'RAC_NS.CMD.LNAENSET', 'write-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_LNAENCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_LNAENCLEAR, self).__init__(register,
            'LNAENCLEAR', 'RAC_NS.CMD.LNAENCLEAR', 'write-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_DEMODENSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_DEMODENSET, self).__init__(register,
            'DEMODENSET', 'RAC_NS.CMD.DEMODENSET', 'write-only',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_DEMODENCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_DEMODENCLEAR, self).__init__(register,
            'DEMODENCLEAR', 'RAC_NS.CMD.DEMODENCLEAR', 'write-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_FORCEDISABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_FORCEDISABLE, self).__init__(register,
            'FORCEDISABLE', 'RAC_NS.CTRL.FORCEDISABLE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_PRSTXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_PRSTXEN, self).__init__(register,
            'PRSTXEN', 'RAC_NS.CTRL.PRSTXEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_TXAFTERRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_TXAFTERRX, self).__init__(register,
            'TXAFTERRX', 'RAC_NS.CTRL.TXAFTERRX', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_PRSMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_PRSMODE, self).__init__(register,
            'PRSMODE', 'RAC_NS.CTRL.PRSMODE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_PRSCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_PRSCLR, self).__init__(register,
            'PRSCLR', 'RAC_NS.CTRL.PRSCLR', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_TXPOSTPONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_TXPOSTPONE, self).__init__(register,
            'TXPOSTPONE', 'RAC_NS.CTRL.TXPOSTPONE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_ACTIVEPOL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_ACTIVEPOL, self).__init__(register,
            'ACTIVEPOL', 'RAC_NS.CTRL.ACTIVEPOL', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_PAENPOL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_PAENPOL, self).__init__(register,
            'PAENPOL', 'RAC_NS.CTRL.PAENPOL', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_LNAENPOL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_LNAENPOL, self).__init__(register,
            'LNAENPOL', 'RAC_NS.CTRL.LNAENPOL', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_PRSRXDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_PRSRXDIS, self).__init__(register,
            'PRSRXDIS', 'RAC_NS.CTRL.PRSRXDIS', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_PRSFORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_PRSFORCETX, self).__init__(register,
            'PRSFORCETX', 'RAC_NS.CTRL.PRSFORCETX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_FORCESTATE_FORCESTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_FORCESTATE_FORCESTATE, self).__init__(register,
            'FORCESTATE', 'RAC_NS.FORCESTATE.FORCESTATE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IF_STATECHANGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IF_STATECHANGE, self).__init__(register,
            'STATECHANGE', 'RAC_NS.IF.STATECHANGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IF_STIMCMPEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IF_STIMCMPEV, self).__init__(register,
            'STIMCMPEV', 'RAC_NS.IF.STIMCMPEV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IF_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IF_BUSERROR, self).__init__(register,
            'BUSERROR', 'RAC_NS.IF.BUSERROR', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IF_SEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IF_SEQ, self).__init__(register,
            'SEQ', 'RAC_NS.IF.SEQ', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IEN_STATECHANGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IEN_STATECHANGE, self).__init__(register,
            'STATECHANGE', 'RAC_NS.IEN.STATECHANGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IEN_STIMCMPEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IEN_STIMCMPEV, self).__init__(register,
            'STIMCMPEV', 'RAC_NS.IEN.STIMCMPEV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IEN_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IEN_BUSERROR, self).__init__(register,
            'BUSERROR', 'RAC_NS.IEN.BUSERROR', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IEN_SEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IEN_SEQ, self).__init__(register,
            'SEQ', 'RAC_NS.IEN.SEQ', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TESTCTRL_MODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TESTCTRL_MODEN, self).__init__(register,
            'MODEN', 'RAC_NS.TESTCTRL.MODEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TESTCTRL_DEMODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TESTCTRL_DEMODEN, self).__init__(register,
            'DEMODEN', 'RAC_NS.TESTCTRL.DEMODEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TESTCTRL_AUX2RFSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TESTCTRL_AUX2RFSENSE, self).__init__(register,
            'AUX2RFSENSE', 'RAC_NS.TESTCTRL.AUX2RFSENSE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TESTCTRL_LOOPBACK2LNAINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TESTCTRL_LOOPBACK2LNAINPUT, self).__init__(register,
            'LOOPBACK2LNAINPUT', 'RAC_NS.TESTCTRL.LOOPBACK2LNAINPUT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TESTCTRL_LOOPBACK2LNAOUTPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TESTCTRL_LOOPBACK2LNAOUTPUT, self).__init__(register,
            'LOOPBACK2LNAOUTPUT', 'RAC_NS.TESTCTRL.LOOPBACK2LNAOUTPUT', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_STOPPED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_STOPPED, self).__init__(register,
            'STOPPED', 'RAC_NS.SEQSTATUS.STOPPED', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_BKPT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_BKPT, self).__init__(register,
            'BKPT', 'RAC_NS.SEQSTATUS.BKPT', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_WAITING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_WAITING, self).__init__(register,
            'WAITING', 'RAC_NS.SEQSTATUS.WAITING', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_WAITMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_WAITMODE, self).__init__(register,
            'WAITMODE', 'RAC_NS.SEQSTATUS.WAITMODE', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_DONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_DONE, self).__init__(register,
            'DONE', 'RAC_NS.SEQSTATUS.DONE', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_NEG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_NEG, self).__init__(register,
            'NEG', 'RAC_NS.SEQSTATUS.NEG', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_POS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_POS, self).__init__(register,
            'POS', 'RAC_NS.SEQSTATUS.POS', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_ZERO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_ZERO, self).__init__(register,
            'ZERO', 'RAC_NS.SEQSTATUS.ZERO', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_CARRY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_CARRY, self).__init__(register,
            'CARRY', 'RAC_NS.SEQSTATUS.CARRY', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQSTATUS_ABORTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQSTATUS_ABORTEN, self).__init__(register,
            'ABORTEN', 'RAC_NS.SEQSTATUS.ABORTEN', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCMD_HALT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCMD_HALT, self).__init__(register,
            'HALT', 'RAC_NS.SEQCMD.HALT', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCMD_STEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCMD_STEP, self).__init__(register,
            'STEP', 'RAC_NS.SEQCMD.STEP', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCMD_RESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCMD_RESUME, self).__init__(register,
            'RESUME', 'RAC_NS.SEQCMD.RESUME', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCMD_BKPTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCMD_BKPTEN, self).__init__(register,
            'BKPTEN', 'RAC_NS.SEQCMD.BKPTEN', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCMD_BKPTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCMD_BKPTDIS, self).__init__(register,
            'BKPTDIS', 'RAC_NS.SEQCMD.BKPTDIS', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCMD_ABORT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCMD_ABORT, self).__init__(register,
            'ABORT', 'RAC_NS.SEQCMD.ABORT', 'write-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCMD_ABORTENSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCMD_ABORTENSET, self).__init__(register,
            'ABORTENSET', 'RAC_NS.SEQCMD.ABORTENSET', 'write-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCMD_ABORTENCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCMD_ABORTENCLEAR, self).__init__(register,
            'ABORTENCLEAR', 'RAC_NS.SEQCMD.ABORTENCLEAR', 'write-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_BREAKPOINT_BKPADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_BREAKPOINT_BKPADDR, self).__init__(register,
            'BKPADDR', 'RAC_NS.BREAKPOINT.BKPADDR', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_R0_R0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_R0_R0, self).__init__(register,
            'R0', 'RAC_NS.R0.R0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_R1_R1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_R1_R1, self).__init__(register,
            'R1', 'RAC_NS.R1.R1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_R2_R2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_R2_R2, self).__init__(register,
            'R2', 'RAC_NS.R2.R2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_R3_R3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_R3_R3, self).__init__(register,
            'R3', 'RAC_NS.R3.R3', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_R4_R4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_R4_R4, self).__init__(register,
            'R4', 'RAC_NS.R4.R4', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_R5_R5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_R5_R5, self).__init__(register,
            'R5', 'RAC_NS.R5.R5', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_R6_R6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_R6_R6, self).__init__(register,
            'R6', 'RAC_NS.R6.R6', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_R7_R7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_R7_R7, self).__init__(register,
            'R7', 'RAC_NS.R7.R7', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_STCMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_STCMP, self).__init__(register,
            'STCMP', 'RAC_NS.WAITMASK.STCMP', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_FRCRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_FRCRX, self).__init__(register,
            'FRCRX', 'RAC_NS.WAITMASK.FRCRX', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_FRCTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_FRCTX, self).__init__(register,
            'FRCTX', 'RAC_NS.WAITMASK.FRCTX', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_PRSEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_PRSEVENT, self).__init__(register,
            'PRSEVENT', 'RAC_NS.WAITMASK.PRSEVENT', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_DEMODRXREQCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_DEMODRXREQCLR, self).__init__(register,
            'DEMODRXREQCLR', 'RAC_NS.WAITMASK.DEMODRXREQCLR', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_SYNTHRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_SYNTHRDY, self).__init__(register,
            'SYNTHRDY', 'RAC_NS.WAITMASK.SYNTHRDY', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_RAMPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_RAMPDONE, self).__init__(register,
            'RAMPDONE', 'RAC_NS.WAITMASK.RAMPDONE', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_FRCPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_FRCPAUSED, self).__init__(register,
            'FRCPAUSED', 'RAC_NS.WAITMASK.FRCPAUSED', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITMASK_ANTSWITCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITMASK_ANTSWITCH, self).__init__(register,
            'ANTSWITCH', 'RAC_NS.WAITMASK.ANTSWITCH', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WAITSNSH_WAITSNSH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WAITSNSH_WAITSNSH, self).__init__(register,
            'WAITSNSH', 'RAC_NS.WAITSNSH.WAITSNSH', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STIMER_STIMER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STIMER_STIMER, self).__init__(register,
            'STIMER', 'RAC_NS.STIMER.STIMER', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STIMERCOMP_STIMERCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STIMERCOMP_STIMERCOMP, self).__init__(register,
            'STIMERCOMP', 'RAC_NS.STIMERCOMP.STIMERCOMP', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VECTADDR_VECTADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VECTADDR_VECTADDR, self).__init__(register,
            'VECTADDR', 'RAC_NS.VECTADDR.VECTADDR', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_COMPACT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_COMPACT, self).__init__(register,
            'COMPACT', 'RAC_NS.SEQCTRL.COMPACT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_COMPINVALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_COMPINVALMODE, self).__init__(register,
            'COMPINVALMODE', 'RAC_NS.SEQCTRL.COMPINVALMODE', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_STIMERDEBUGRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_STIMERDEBUGRUN, self).__init__(register,
            'STIMERDEBUGRUN', 'RAC_NS.SEQCTRL.STIMERDEBUGRUN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_CPUHALTREQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_CPUHALTREQEN, self).__init__(register,
            'CPUHALTREQEN', 'RAC_NS.SEQCTRL.CPUHALTREQEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_SEQHALTUPONCPUHALTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_SEQHALTUPONCPUHALTEN, self).__init__(register,
            'SEQHALTUPONCPUHALTEN', 'RAC_NS.SEQCTRL.SEQHALTUPONCPUHALTEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRESC_STIMER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRESC_STIMER, self).__init__(register,
            'STIMER', 'RAC_NS.PRESC.STIMER', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SR0_SR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SR0_SR0, self).__init__(register,
            'SR0', 'RAC_NS.SR0.SR0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SR1_SR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SR1_SR1, self).__init__(register,
            'SR1', 'RAC_NS.SR1.SR1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SR2_SR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SR2_SR2, self).__init__(register,
            'SR2', 'RAC_NS.SR2.SR2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SR3_SR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SR3_SR3, self).__init__(register,
            'SR3', 'RAC_NS.SR3.SR3', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WUREQ_MANUAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WUREQ_MANUAL, self).__init__(register,
            'MANUAL', 'RAC_NS.WUREQ.MANUAL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WUREQ_OVERRIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WUREQ_OVERRIDE, self).__init__(register,
            'OVERRIDE', 'RAC_NS.WUREQ.OVERRIDE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_WUREQ_STATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_WUREQ_STATUS, self).__init__(register,
            'STATUS', 'RAC_NS.WUREQ.STATUS', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYNTHENCTRL_VCOSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYNTHENCTRL_VCOSTARTUP, self).__init__(register,
            'VCOSTARTUP', 'RAC_NS.SYNTHENCTRL.VCOSTARTUP', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYNTHENCTRL_VCBUFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYNTHENCTRL_VCBUFEN, self).__init__(register,
            'VCBUFEN', 'RAC_NS.SYNTHENCTRL.VCBUFEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYNTHENCTRL_SYNTHSTARTREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYNTHENCTRL_SYNTHSTARTREQ, self).__init__(register,
            'SYNTHSTARTREQ', 'RAC_NS.SYNTHENCTRL.SYNTHSTARTREQ', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYNTHENCTRL_LPFBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYNTHENCTRL_LPFBWSEL, self).__init__(register,
            'LPFBWSEL', 'RAC_NS.SYNTHENCTRL.LPFBWSEL', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYNTHREGCTRL_MMDLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYNTHREGCTRL_MMDLDOVREFTRIM, self).__init__(register,
            'MMDLDOVREFTRIM', 'RAC_NS.SYNTHREGCTRL.MMDLDOVREFTRIM', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYNTHREGCTRL_CHPLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYNTHREGCTRL_CHPLDOVREFTRIM, self).__init__(register,
            'CHPLDOVREFTRIM', 'RAC_NS.SYNTHREGCTRL.CHPLDOVREFTRIM', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VCOCTRL_VCOAMPLITUDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VCOCTRL_VCOAMPLITUDE, self).__init__(register,
            'VCOAMPLITUDE', 'RAC_NS.VCOCTRL.VCOAMPLITUDE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VCOCTRL_VCODETAMPLITUDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VCOCTRL_VCODETAMPLITUDE, self).__init__(register,
            'VCODETAMPLITUDE', 'RAC_NS.VCOCTRL.VCODETAMPLITUDE', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CHPCTRL_CHPOUTPUTTRISTATEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CHPCTRL_CHPOUTPUTTRISTATEMODE, self).__init__(register,
            'CHPOUTPUTTRISTATEMODE', 'RAC_NS.CHPCTRL.CHPOUTPUTTRISTATEMODE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYNTHCTRL_MMDPOWERBALANCEDISABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYNTHCTRL_MMDPOWERBALANCEDISABLE, self).__init__(register,
            'MMDPOWERBALANCEDISABLE', 'RAC_NS.SYNTHCTRL.MMDPOWERBALANCEDISABLE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFSTATUS_MODRAMPUPDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFSTATUS_MODRAMPUPDONE, self).__init__(register,
            'MODRAMPUPDONE', 'RAC_NS.RFSTATUS.MODRAMPUPDONE', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS2_PREVSTATE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS2_PREVSTATE1, self).__init__(register,
            'PREVSTATE1', 'RAC_NS.STATUS2.PREVSTATE1', 'read-only',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS2_PREVSTATE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS2_PREVSTATE2, self).__init__(register,
            'PREVSTATE2', 'RAC_NS.STATUS2.PREVSTATE2', 'read-only',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS2_PREVSTATE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS2_PREVSTATE3, self).__init__(register,
            'PREVSTATE3', 'RAC_NS.STATUS2.PREVSTATE3', 'read-only',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFPGACTRL_DCCALON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFPGACTRL_DCCALON, self).__init__(register,
            'DCCALON', 'RAC_NS.IFPGACTRL.DCCALON', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFPGACTRL_DCRSTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFPGACTRL_DCRSTEN, self).__init__(register,
            'DCRSTEN', 'RAC_NS.IFPGACTRL.DCRSTEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFPGACTRL_DCESTIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFPGACTRL_DCESTIEN, self).__init__(register,
            'DCESTIEN', 'RAC_NS.IFPGACTRL.DCESTIEN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFPGACTRL_DCCALDEC0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFPGACTRL_DCCALDEC0, self).__init__(register,
            'DCCALDEC0', 'RAC_NS.IFPGACTRL.DCCALDEC0', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFPGACTRL_DCCALDCGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFPGACTRL_DCCALDCGEAR, self).__init__(register,
            'DCCALDCGEAR', 'RAC_NS.IFPGACTRL.DCCALDCGEAR', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PAENCTRL_PARAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PAENCTRL_PARAMP, self).__init__(register,
            'PARAMP', 'RAC_NS.PAENCTRL.PARAMP', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_APC_ENAPCSW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_APC_ENAPCSW, self).__init__(register,
            'ENAPCSW', 'RAC_NS.APC.ENAPCSW', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_APC_AMPCONTROLLIMITSW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_APC_AMPCONTROLLIMITSW, self).__init__(register,
            'AMPCONTROLLIMITSW', 'RAC_NS.APC.AMPCONTROLLIMITSW', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCCLKINVERT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCCLKINVERT, self).__init__(register,
            'AUXADCCLKINVERT', 'RAC_NS.AUXADCTRIM.AUXADCCLKINVERT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCLDOVREFTRIM, self).__init__(register,
            'AUXADCLDOVREFTRIM', 'RAC_NS.AUXADCTRIM.AUXADCLDOVREFTRIM', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCOUTPUTINVERT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCOUTPUTINVERT, self).__init__(register,
            'AUXADCOUTPUTINVERT', 'RAC_NS.AUXADCTRIM.AUXADCOUTPUTINVERT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCRCTUNE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCRCTUNE, self).__init__(register,
            'AUXADCRCTUNE', 'RAC_NS.AUXADCTRIM.AUXADCRCTUNE', 'read-write',
            u"",
            4, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMADCINPUTRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMADCINPUTRES, self).__init__(register,
            'AUXADCTRIMADCINPUTRES', 'RAC_NS.AUXADCTRIM.AUXADCTRIMADCINPUTRES', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF, self).__init__(register,
            'AUXADCTRIMCURRINPUTBUF', 'RAC_NS.AUXADCTRIM.AUXADCTRIMCURRINPUTBUF', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURROPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURROPA1, self).__init__(register,
            'AUXADCTRIMCURROPA1', 'RAC_NS.AUXADCTRIM.AUXADCTRIMCURROPA1', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURROPA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURROPA2, self).__init__(register,
            'AUXADCTRIMCURROPA2', 'RAC_NS.AUXADCTRIM.AUXADCTRIMCURROPA2', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRREFBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRREFBUF, self).__init__(register,
            'AUXADCTRIMCURRREFBUF', 'RAC_NS.AUXADCTRIM.AUXADCTRIMCURRREFBUF', 'read-write',
            u"",
            17, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRTSENSE, self).__init__(register,
            'AUXADCTRIMCURRTSENSE', 'RAC_NS.AUXADCTRIM.AUXADCTRIMCURRTSENSE', 'read-write',
            u"",
            19, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRVCMBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMCURRVCMBUF, self).__init__(register,
            'AUXADCTRIMCURRVCMBUF', 'RAC_NS.AUXADCTRIM.AUXADCTRIMCURRVCMBUF', 'read-write',
            u"",
            21, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT, self).__init__(register,
            'AUXADCTRIMLDOHIGHCURRENT', 'RAC_NS.AUXADCTRIM.AUXADCTRIMLDOHIGHCURRENT', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMREFP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMREFP, self).__init__(register,
            'AUXADCTRIMREFP', 'RAC_NS.AUXADCTRIM.AUXADCTRIMREFP', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMVREFVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTRIMVREFVCM, self).__init__(register,
            'AUXADCTRIMVREFVCM', 'RAC_NS.AUXADCTRIM.AUXADCTRIMVREFVCM', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_AUXADCTSENSETRIMVBE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_AUXADCTSENSETRIMVBE2, self).__init__(register,
            'AUXADCTSENSETRIMVBE2', 'RAC_NS.AUXADCTRIM.AUXADCTSENSETRIMVBE2', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCENAUXADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENAUXADC, self).__init__(register,
            'AUXADCENAUXADC', 'RAC_NS.AUXADCEN.AUXADCENAUXADC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCENINPUTBUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENINPUTBUFFER, self).__init__(register,
            'AUXADCENINPUTBUFFER', 'RAC_NS.AUXADCEN.AUXADCENINPUTBUFFER', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENLDO, self).__init__(register,
            'AUXADCENLDO', 'RAC_NS.AUXADCEN.AUXADCENLDO', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCENOUTPUTDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENOUTPUTDRV, self).__init__(register,
            'AUXADCENOUTPUTDRV', 'RAC_NS.AUXADCEN.AUXADCENOUTPUTDRV', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCENPMON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENPMON, self).__init__(register,
            'AUXADCENPMON', 'RAC_NS.AUXADCEN.AUXADCENPMON', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCENRESONDIAGA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENRESONDIAGA, self).__init__(register,
            'AUXADCENRESONDIAGA', 'RAC_NS.AUXADCEN.AUXADCENRESONDIAGA', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCENTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENTSENSE, self).__init__(register,
            'AUXADCENTSENSE', 'RAC_NS.AUXADCEN.AUXADCENTSENSE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCENTSENSECAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENTSENSECAL, self).__init__(register,
            'AUXADCENTSENSECAL', 'RAC_NS.AUXADCEN.AUXADCENTSENSECAL', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_AUXADCINPUTBUFFERBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCINPUTBUFFERBYPASS, self).__init__(register,
            'AUXADCINPUTBUFFERBYPASS', 'RAC_NS.AUXADCEN.AUXADCINPUTBUFFERBYPASS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL0_CYCLES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL0_CYCLES, self).__init__(register,
            'CYCLES', 'RAC_NS.AUXADCCTRL0.CYCLES', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL0_MUXSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL0_MUXSEL, self).__init__(register,
            'MUXSEL', 'RAC_NS.AUXADCCTRL0.MUXSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL0_CLRCOUNTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL0_CLRCOUNTER, self).__init__(register,
            'CLRCOUNTER', 'RAC_NS.AUXADCCTRL0.CLRCOUNTER', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL0_CLRFILTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL0_CLRFILTER, self).__init__(register,
            'CLRFILTER', 'RAC_NS.AUXADCCTRL0.CLRFILTER', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL0_INPUTRESSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL0_INPUTRESSEL, self).__init__(register,
            'INPUTRESSEL', 'RAC_NS.AUXADCCTRL0.INPUTRESSEL', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_AUXADCINPUTRESSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_AUXADCINPUTRESSEL, self).__init__(register,
            'AUXADCINPUTRESSEL', 'RAC_NS.AUXADCCTRL1.AUXADCINPUTRESSEL', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_AUXADCINPUTSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_AUXADCINPUTSELECT, self).__init__(register,
            'AUXADCINPUTSELECT', 'RAC_NS.AUXADCCTRL1.AUXADCINPUTSELECT', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_AUXADCPMONSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_AUXADCPMONSELECT, self).__init__(register,
            'AUXADCPMONSELECT', 'RAC_NS.AUXADCCTRL1.AUXADCPMONSELECT', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTSENSESELCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTSENSESELCURR, self).__init__(register,
            'AUXADCTSENSESELCURR', 'RAC_NS.AUXADCCTRL1.AUXADCTSENSESELCURR', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_AUXADCRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_AUXADCRESET, self).__init__(register,
            'AUXADCRESET', 'RAC_NS.AUXADCCTRL1.AUXADCRESET', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTSENSESELVBE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTSENSESELVBE, self).__init__(register,
            'AUXADCTSENSESELVBE', 'RAC_NS.AUXADCCTRL1.AUXADCTSENSESELVBE', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCOUT_AUXADCOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCOUT_AUXADCOUT, self).__init__(register,
            'AUXADCOUT', 'RAC_NS.AUXADCOUT.AUXADCOUT', 'read-only',
            u"",
            0, 28)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTBWCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTBWCAL, self).__init__(register,
            'CLKMULTBWCAL', 'RAC_NS.CLKMULTEN0.CLKMULTBWCAL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTDISICO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTDISICO, self).__init__(register,
            'CLKMULTDISICO', 'RAC_NS.CLKMULTEN0.CLKMULTDISICO', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBDET, self).__init__(register,
            'CLKMULTENBBDET', 'RAC_NS.CLKMULTEN0.CLKMULTENBBDET', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBXLDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBXLDET, self).__init__(register,
            'CLKMULTENBBXLDET', 'RAC_NS.CLKMULTEN0.CLKMULTENBBXLDET', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBXMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBBXMDET, self).__init__(register,
            'CLKMULTENBBXMDET', 'RAC_NS.CLKMULTEN0.CLKMULTENBBXMDET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENCFDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENCFDET, self).__init__(register,
            'CLKMULTENCFDET', 'RAC_NS.CLKMULTEN0.CLKMULTENCFDET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDITHER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDITHER, self).__init__(register,
            'CLKMULTENDITHER', 'RAC_NS.CLKMULTEN0.CLKMULTENDITHER', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVADC, self).__init__(register,
            'CLKMULTENDRVADC', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVADC', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVDIFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVDIFF, self).__init__(register,
            'CLKMULTENDRVDIFF', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVDIFF', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRX2P4G(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRX2P4G, self).__init__(register,
            'CLKMULTENDRVRX2P4G', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVRX2P4G', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRXSUBG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRXSUBG, self).__init__(register,
            'CLKMULTENDRVRXSUBG', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVRXSUBG', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVTXDUALB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVTXDUALB, self).__init__(register,
            'CLKMULTENDRVTXDUALB', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVTXDUALB', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENFBDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENFBDIV, self).__init__(register,
            'CLKMULTENFBDIV', 'RAC_NS.CLKMULTEN0.CLKMULTENFBDIV', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREFDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREFDIV, self).__init__(register,
            'CLKMULTENREFDIV', 'RAC_NS.CLKMULTEN0.CLKMULTENREFDIV', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1, self).__init__(register,
            'CLKMULTENREG1', 'RAC_NS.CLKMULTEN0.CLKMULTENREG1', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG2, self).__init__(register,
            'CLKMULTENREG2', 'RAC_NS.CLKMULTEN0.CLKMULTENREG2', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENROTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENROTDET, self).__init__(register,
            'CLKMULTENROTDET', 'RAC_NS.CLKMULTEN0.CLKMULTENROTDET', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTFREQCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTFREQCAL, self).__init__(register,
            'CLKMULTFREQCAL', 'RAC_NS.CLKMULTEN0.CLKMULTFREQCAL', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG1ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG1ADJV, self).__init__(register,
            'CLKMULTREG1ADJV', 'RAC_NS.CLKMULTEN0.CLKMULTREG1ADJV', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJI, self).__init__(register,
            'CLKMULTREG2ADJI', 'RAC_NS.CLKMULTEN0.CLKMULTREG2ADJI', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJV, self).__init__(register,
            'CLKMULTREG2ADJV', 'RAC_NS.CLKMULTEN0.CLKMULTREG2ADJV', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTINNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTINNIBBLE, self).__init__(register,
            'CLKMULTINNIBBLE', 'RAC_NS.CLKMULTEN1.CLKMULTINNIBBLE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDCNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDCNIB, self).__init__(register,
            'CLKMULTLDCNIB', 'RAC_NS.CLKMULTEN1.CLKMULTLDCNIB', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDFNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDFNIB, self).__init__(register,
            'CLKMULTLDFNIB', 'RAC_NS.CLKMULTEN1.CLKMULTLDFNIB', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDMNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDMNIB, self).__init__(register,
            'CLKMULTLDMNIB', 'RAC_NS.CLKMULTEN1.CLKMULTLDMNIB', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTRDNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTRDNIBBLE, self).__init__(register,
            'CLKMULTRDNIBBLE', 'RAC_NS.CLKMULTEN1.CLKMULTRDNIBBLE', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVN, self).__init__(register,
            'CLKMULTDIVN', 'RAC_NS.CLKMULTCTRL.CLKMULTDIVN', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVR, self).__init__(register,
            'CLKMULTDIVR', 'RAC_NS.CLKMULTCTRL.CLKMULTDIVR', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTDIVX, self).__init__(register,
            'CLKMULTDIVX', 'RAC_NS.CLKMULTCTRL.CLKMULTDIVX', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTENRESYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTENRESYNC, self).__init__(register,
            'CLKMULTENRESYNC', 'RAC_NS.CLKMULTCTRL.CLKMULTENRESYNC', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTVALID, self).__init__(register,
            'CLKMULTVALID', 'RAC_NS.CLKMULTCTRL.CLKMULTVALID', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTSTATUS_CLKMULTOUTNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTSTATUS_CLKMULTOUTNIBBLE, self).__init__(register,
            'CLKMULTOUTNIBBLE', 'RAC_NS.CLKMULTSTATUS.CLKMULTOUTNIBBLE', 'read-only',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTSTATUS_CLKMULTACKVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTSTATUS_CLKMULTACKVALID, self).__init__(register,
            'CLKMULTACKVALID', 'RAC_NS.CLKMULTSTATUS.CLKMULTACKVALID', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCDBG_IFADCENADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_IFADCENADC, self).__init__(register,
            'IFADCENADC', 'RAC_NS.IFADCDBG.IFADCENADC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCDBG_IFADCENCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_IFADCENCLK, self).__init__(register,
            'IFADCENCLK', 'RAC_NS.IFADCDBG.IFADCENCLK', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCDBG_IFADCENREFBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_IFADCENREFBUF, self).__init__(register,
            'IFADCENREFBUF', 'RAC_NS.IFADCDBG.IFADCENREFBUF', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCDBG_IFADCENSIDETONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_IFADCENSIDETONE, self).__init__(register,
            'IFADCENSIDETONE', 'RAC_NS.IFADCDBG.IFADCENSIDETONE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCDBG_IFADCINVERTCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_IFADCINVERTCLK, self).__init__(register,
            'IFADCINVERTCLK', 'RAC_NS.IFADCDBG.IFADCINVERTCLK', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCDBG_IFADCSHORTINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_IFADCSHORTINPUT, self).__init__(register,
            'IFADCSHORTINPUT', 'RAC_NS.IFADCDBG.IFADCSHORTINPUT', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCCLKSEL, self).__init__(register,
            'IFADCCLKSEL', 'RAC_NS.IFADCTRIM.IFADCCLKSEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCENHALFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCENHALFMODE, self).__init__(register,
            'IFADCENHALFMODE', 'RAC_NS.IFADCTRIM.IFADCENHALFMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCLDOSERIESAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCLDOSERIESAMPLVL, self).__init__(register,
            'IFADCLDOSERIESAMPLVL', 'RAC_NS.IFADCTRIM.IFADCLDOSERIESAMPLVL', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCLDOSHUNTAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCLDOSHUNTAMPLVL, self).__init__(register,
            'IFADCLDOSHUNTAMPLVL', 'RAC_NS.IFADCTRIM.IFADCLDOSHUNTAMPLVL', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCLDOSHUNTCURLP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCLDOSHUNTCURLP, self).__init__(register,
            'IFADCLDOSHUNTCURLP', 'RAC_NS.IFADCTRIM.IFADCLDOSHUNTCURLP', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCLDOSHUNTCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCLDOSHUNTCURLVL, self).__init__(register,
            'IFADCLDOSHUNTCURLVL', 'RAC_NS.IFADCTRIM.IFADCLDOSHUNTCURLVL', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCOTAST1CURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCOTAST1CURRENT, self).__init__(register,
            'IFADCOTAST1CURRENT', 'RAC_NS.IFADCTRIM.IFADCOTAST1CURRENT', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCOTAST2CURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCOTAST2CURRENT, self).__init__(register,
            'IFADCOTAST2CURRENT', 'RAC_NS.IFADCTRIM.IFADCOTAST2CURRENT', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCREFBUFAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCREFBUFAMPLVL, self).__init__(register,
            'IFADCREFBUFAMPLVL', 'RAC_NS.IFADCTRIM.IFADCREFBUFAMPLVL', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCREFBUFCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCREFBUFCURLVL, self).__init__(register,
            'IFADCREFBUFCURLVL', 'RAC_NS.IFADCTRIM.IFADCREFBUFCURLVL', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCSIDETONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCSIDETONEAMP, self).__init__(register,
            'IFADCSIDETONEAMP', 'RAC_NS.IFADCTRIM.IFADCSIDETONEAMP', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCSIDETONEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCSIDETONEFREQ, self).__init__(register,
            'IFADCSIDETONEFREQ', 'RAC_NS.IFADCTRIM.IFADCSIDETONEFREQ', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCTUNEZERO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCTUNEZERO, self).__init__(register,
            'IFADCTUNEZERO', 'RAC_NS.IFADCTRIM.IFADCTUNEZERO', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM_IFADCVCMLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM_IFADCVCMLVL, self).__init__(register,
            'IFADCVCMLVL', 'RAC_NS.IFADCTRIM.IFADCVCMLVL', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCCAL_IFADCENRCCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCCAL_IFADCENRCCAL, self).__init__(register,
            'IFADCENRCCAL', 'RAC_NS.IFADCCAL.IFADCENRCCAL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCCAL_IFADCTUNERCCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCCAL_IFADCTUNERCCALMODE, self).__init__(register,
            'IFADCTUNERCCALMODE', 'RAC_NS.IFADCCAL.IFADCTUNERCCALMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCCAL_IFADCTUNERC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCCAL_IFADCTUNERC, self).__init__(register,
            'IFADCTUNERC', 'RAC_NS.IFADCCAL.IFADCTUNERC', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCSTATUS_IFADCRCCALOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCSTATUS_IFADCRCCALOUT, self).__init__(register,
            'IFADCRCCALOUT', 'RAC_NS.IFADCSTATUS.IFADCRCCALOUT', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR1, self).__init__(register,
            'LNAMIXDISMXR1', 'RAC_NS.LNAMIXDEBUG.LNAMIXDISMXR1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR2, self).__init__(register,
            'LNAMIXDISMXR2', 'RAC_NS.LNAMIXDEBUG.LNAMIXDISMXR2', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXCURCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXCURCTRL, self).__init__(register,
            'LNAMIXCURCTRL', 'RAC_NS.LNAMIXTRIM0.LNAMIXCURCTRL', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXHIGHCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXHIGHCUR, self).__init__(register,
            'LNAMIXHIGHCUR', 'RAC_NS.LNAMIXTRIM0.LNAMIXHIGHCUR', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXLOWCUR, self).__init__(register,
            'LNAMIXLOWCUR', 'RAC_NS.LNAMIXTRIM0.LNAMIXLOWCUR', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXRFPKDBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXRFPKDBWSEL, self).__init__(register,
            'LNAMIXRFPKDBWSEL', 'RAC_NS.LNAMIXTRIM0.LNAMIXRFPKDBWSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXRFPKDCALCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXRFPKDCALCM, self).__init__(register,
            'LNAMIXRFPKDCALCM', 'RAC_NS.LNAMIXTRIM0.LNAMIXRFPKDCALCM', 'read-write',
            u"",
            12, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXRFPKDCALDM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXRFPKDCALDM, self).__init__(register,
            'LNAMIXRFPKDCALDM', 'RAC_NS.LNAMIXTRIM0.LNAMIXRFPKDCALDM', 'read-write',
            u"",
            18, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXTRIMVREG, self).__init__(register,
            'LNAMIXTRIMVREG', 'RAC_NS.LNAMIXTRIM0.LNAMIXTRIMVREG', 'read-write',
            u"",
            23, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXIBIAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXIBIAS1ADJ, self).__init__(register,
            'LNAMIXIBIAS1ADJ', 'RAC_NS.LNAMIXTRIM1.LNAMIXIBIAS1ADJ', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXLNA1CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXLNA1CAPSEL, self).__init__(register,
            'LNAMIXLNA1CAPSEL', 'RAC_NS.LNAMIXTRIM1.LNAMIXLNA1CAPSEL', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXMXRBIAS1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXMXRBIAS1, self).__init__(register,
            'LNAMIXMXRBIAS1', 'RAC_NS.LNAMIXTRIM1.LNAMIXMXRBIAS1', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXNCAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXNCAS1ADJ, self).__init__(register,
            'LNAMIXNCAS1ADJ', 'RAC_NS.LNAMIXTRIM1.LNAMIXNCAS1ADJ', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXPCAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXPCAS1ADJ, self).__init__(register,
            'LNAMIXPCAS1ADJ', 'RAC_NS.LNAMIXTRIM1.LNAMIXPCAS1ADJ', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXVOUT1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXVOUT1ADJ, self).__init__(register,
            'LNAMIXVOUT1ADJ', 'RAC_NS.LNAMIXTRIM1.LNAMIXVOUT1ADJ', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXIBIAS2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXIBIAS2ADJ, self).__init__(register,
            'LNAMIXIBIAS2ADJ', 'RAC_NS.LNAMIXTRIM2.LNAMIXIBIAS2ADJ', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXLNA2CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXLNA2CAPSEL, self).__init__(register,
            'LNAMIXLNA2CAPSEL', 'RAC_NS.LNAMIXTRIM2.LNAMIXLNA2CAPSEL', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXMXRBIAS2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXMXRBIAS2, self).__init__(register,
            'LNAMIXMXRBIAS2', 'RAC_NS.LNAMIXTRIM2.LNAMIXMXRBIAS2', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXNCAS2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXNCAS2ADJ, self).__init__(register,
            'LNAMIXNCAS2ADJ', 'RAC_NS.LNAMIXTRIM2.LNAMIXNCAS2ADJ', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXPCAS2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXPCAS2ADJ, self).__init__(register,
            'LNAMIXPCAS2ADJ', 'RAC_NS.LNAMIXTRIM2.LNAMIXPCAS2ADJ', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXVOUT2ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXVOUT2ADJ, self).__init__(register,
            'LNAMIXVOUT2ADJ', 'RAC_NS.LNAMIXTRIM2.LNAMIXVOUT2ADJ', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALEN, self).__init__(register,
            'LNAMIXCALEN', 'RAC_NS.LNAMIXCAL.LNAMIXCALEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALVMODE, self).__init__(register,
            'LNAMIXCALVMODE', 'RAC_NS.LNAMIXCAL.LNAMIXCALVMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL1, self).__init__(register,
            'LNAMIXENIRCAL1', 'RAC_NS.LNAMIXCAL.LNAMIXENIRCAL1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL2, self).__init__(register,
            'LNAMIXENIRCAL2', 'RAC_NS.LNAMIXCAL.LNAMIXENIRCAL2', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL1AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL1AMP, self).__init__(register,
            'LNAMIXIRCAL1AMP', 'RAC_NS.LNAMIXCAL.LNAMIXIRCAL1AMP', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL2AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL2AMP, self).__init__(register,
            'LNAMIXIRCAL2AMP', 'RAC_NS.LNAMIXCAL.LNAMIXIRCAL2AMP', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXEN_LNAMIXENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXEN_LNAMIXENLDO, self).__init__(register,
            'LNAMIXENLDO', 'RAC_NS.LNAMIXEN.LNAMIXENLDO', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREBYPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREBYPFORCE, self).__init__(register,
            'PREBYPFORCE', 'RAC_NS.PRECTRL.PREBYPFORCE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREREGTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREREGTRIM, self).__init__(register,
            'PREREGTRIM', 'RAC_NS.PRECTRL.PREREGTRIM', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREVREFTRIM, self).__init__(register,
            'PREVREFTRIM', 'RAC_NS.PRECTRL.PREVREFTRIM', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMDRVREGIBCORE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMDRVREGIBCORE0DBM, self).__init__(register,
            'PATRIMDRVREGIBCORE0DBM', 'RAC_NS.PATRIM0.PATRIMDRVREGIBCORE0DBM', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMDRVREGIBNDIO0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMDRVREGIBNDIO0DBM, self).__init__(register,
            'PATRIMDRVREGIBNDIO0DBM', 'RAC_NS.PATRIM0.PATRIMDRVREGIBNDIO0DBM', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMDRVREGPSR0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMDRVREGPSR0DBM, self).__init__(register,
            'PATRIMDRVREGPSR0DBM', 'RAC_NS.PATRIM0.PATRIMDRVREGPSR0DBM', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMDRVSLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMDRVSLICE0DBM, self).__init__(register,
            'PATRIMDRVSLICE0DBM', 'RAC_NS.PATRIM0.PATRIMDRVSLICE0DBM', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMFB0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMFB0DBM, self).__init__(register,
            'PATRIMFB0DBM', 'RAC_NS.PATRIM0.PATRIMFB0DBM', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMPABIASN0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMPABIASN0DBM, self).__init__(register,
            'PATRIMPABIASN0DBM', 'RAC_NS.PATRIM0.PATRIMPABIASN0DBM', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMPABIASP0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMPABIASP0DBM, self).__init__(register,
            'PATRIMPABIASP0DBM', 'RAC_NS.PATRIM0.PATRIMPABIASP0DBM', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMPASLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMPASLICE0DBM, self).__init__(register,
            'PATRIMPASLICE0DBM', 'RAC_NS.PATRIM0.PATRIMPASLICE0DBM', 'read-write',
            u"",
            21, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_PATRIMVREF0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_PATRIMVREF0DBM, self).__init__(register,
            'PATRIMVREF0DBM', 'RAC_NS.PATRIM0.PATRIMVREF0DBM', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIM10DBMDUTYCYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIM10DBMDUTYCYN, self).__init__(register,
            'PATRIM10DBMDUTYCYN', 'RAC_NS.PATRIM1.PATRIM10DBMDUTYCYN', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIM10DBMDUTYCYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIM10DBMDUTYCYP, self).__init__(register,
            'PATRIM10DBMDUTYCYP', 'RAC_NS.PATRIM1.PATRIM10DBMDUTYCYP', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIM20DBMPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIM20DBMPREDRV, self).__init__(register,
            'PATRIM20DBMPREDRV', 'RAC_NS.PATRIM1.PATRIM20DBMPREDRV', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMANTSWBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMANTSWBIAS, self).__init__(register,
            'PATRIMANTSWBIAS', 'RAC_NS.PATRIM1.PATRIMANTSWBIAS', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMBLEEDAUTOPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMBLEEDAUTOPREREG, self).__init__(register,
            'PATRIMBLEEDAUTOPREREG', 'RAC_NS.PATRIM1.PATRIMBLEEDAUTOPREREG', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMCAPPAOUTM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMCAPPAOUTM, self).__init__(register,
            'PATRIMCAPPAOUTM', 'RAC_NS.PATRIM1.PATRIMCAPPAOUTM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMCAPPAOUTP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMCAPPAOUTP, self).__init__(register,
            'PATRIMCAPPAOUTP', 'RAC_NS.PATRIM1.PATRIMCAPPAOUTP', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMCMGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMCMGAIN, self).__init__(register,
            'PATRIMCMGAIN', 'RAC_NS.PATRIM1.PATRIMCMGAIN', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMDLY0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMDLY0, self).__init__(register,
            'PATRIMDLY0', 'RAC_NS.PATRIM1.PATRIMDLY0', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMDLY1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMDLY1, self).__init__(register,
            'PATRIMDLY1', 'RAC_NS.PATRIM1.PATRIMDLY1', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMFBKATTPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMFBKATTPDRVLDO, self).__init__(register,
            'PATRIMFBKATTPDRVLDO', 'RAC_NS.PATRIM1.PATRIMFBKATTPDRVLDO', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_PATRIMIBIASMASTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_PATRIMIBIASMASTER, self).__init__(register,
            'PATRIMIBIASMASTER', 'RAC_NS.PATRIM1.PATRIMIBIASMASTER', 'read-write',
            u"",
            29, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMLDOFBHVPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMLDOFBHVPDRVLDO, self).__init__(register,
            'PATRIMLDOFBHVPDRVLDO', 'RAC_NS.PATRIM2.PATRIMLDOFBHVPDRVLDO', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMLDOFBHVPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMLDOFBHVPREREG, self).__init__(register,
            'PATRIMLDOFBHVPREREG', 'RAC_NS.PATRIM2.PATRIMLDOFBHVPREREG', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMLDOHVPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMLDOHVPDRVLDO, self).__init__(register,
            'PATRIMLDOHVPDRVLDO', 'RAC_NS.PATRIM2.PATRIMLDOHVPDRVLDO', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMLDOHVPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMLDOHVPREREG, self).__init__(register,
            'PATRIMLDOHVPREREG', 'RAC_NS.PATRIM2.PATRIMLDOHVPREREG', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMLDOPSRPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMLDOPSRPDRVLDO, self).__init__(register,
            'PATRIMLDOPSRPDRVLDO', 'RAC_NS.PATRIM2.PATRIMLDOPSRPDRVLDO', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMLDOPSRPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMLDOPSRPREREG, self).__init__(register,
            'PATRIMLDOPSRPREREG', 'RAC_NS.PATRIM2.PATRIMLDOPSRPREREG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMLDOSLICESPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMLDOSLICESPDRVLDO, self).__init__(register,
            'PATRIMLDOSLICESPDRVLDO', 'RAC_NS.PATRIM2.PATRIMLDOSLICESPDRVLDO', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMLDOSLICESPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMLDOSLICESPREREG, self).__init__(register,
            'PATRIMLDOSLICESPREREG', 'RAC_NS.PATRIM2.PATRIMLDOSLICESPREREG', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMPADACGLITCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMPADACGLITCH, self).__init__(register,
            'PATRIMPADACGLITCH', 'RAC_NS.PATRIM2.PATRIMPADACGLITCH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMNBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMNBIAS, self).__init__(register,
            'PATRIMNBIAS', 'RAC_NS.PATRIM2.PATRIMNBIAS', 'read-write',
            u"",
            19, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMNCASC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMNCASC, self).__init__(register,
            'PATRIMNCASC', 'RAC_NS.PATRIM2.PATRIMNCASC', 'read-write',
            u"",
            23, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMPBIAS, self).__init__(register,
            'PATRIMPBIAS', 'RAC_NS.PATRIM2.PATRIMPBIAS', 'read-write',
            u"",
            25, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_PATRIMPCASC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_PATRIMPCASC, self).__init__(register,
            'PATRIMPCASC', 'RAC_NS.PATRIM2.PATRIMPCASC', 'read-write',
            u"",
            29, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAEN10DBMVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAEN10DBMVMID, self).__init__(register,
            'PAEN10DBMVMID', 'RAC_NS.PACTRL.PAEN10DBMVMID', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAEN20DBMVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAEN20DBMVMID, self).__init__(register,
            'PAEN20DBMVMID', 'RAC_NS.PACTRL.PAEN20DBMVMID', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAENCAPATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAENCAPATT, self).__init__(register,
            'PAENCAPATT', 'RAC_NS.PACTRL.PAENCAPATT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAENLATCHBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAENLATCHBYPASS, self).__init__(register,
            'PAENLATCHBYPASS', 'RAC_NS.PACTRL.PAENLATCHBYPASS', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAENPOWERRAMPINGCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAENPOWERRAMPINGCLK, self).__init__(register,
            'PAENPOWERRAMPINGCLK', 'RAC_NS.PACTRL.PAENPOWERRAMPINGCLK', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAPULLDOWNVDDPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAPULLDOWNVDDPA, self).__init__(register,
            'PAPULLDOWNVDDPA', 'RAC_NS.PACTRL.PAPULLDOWNVDDPA', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAREGBYPASSPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAREGBYPASSPDRVLDO, self).__init__(register,
            'PAREGBYPASSPDRVLDO', 'RAC_NS.PACTRL.PAREGBYPASSPDRVLDO', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAREGBYPASSPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAREGBYPASSPREREG, self).__init__(register,
            'PAREGBYPASSPREREG', 'RAC_NS.PACTRL.PAREGBYPASSPREREG', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PASELLDOVDDPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PASELLDOVDDPA, self).__init__(register,
            'PASELLDOVDDPA', 'RAC_NS.PACTRL.PASELLDOVDDPA', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PASELLDOVDDRF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PASELLDOVDDRF, self).__init__(register,
            'PASELLDOVDDRF', 'RAC_NS.PACTRL.PASELLDOVDDRF', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PASLICERST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PASLICERST, self).__init__(register,
            'PASLICERST', 'RAC_NS.PACTRL.PASLICERST', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PAPOWER, self).__init__(register,
            'PAPOWER', 'RAC_NS.PACTRL.PAPOWER', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_PASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_PASELSLICE, self).__init__(register,
            'PASELSLICE', 'RAC_NS.PACTRL.PASELSLICE', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGADEBUG_PGACCTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGADEBUG_PGACCTRIM, self).__init__(register,
            'PGACCTRIM', 'RAC_NS.PGADEBUG.PGACCTRIM', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGATRIM_PGACTUNE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGATRIM_PGACTUNE, self).__init__(register,
            'PGACTUNE', 'RAC_NS.PGATRIM.PGACTUNE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGATRIM_PGADISANTILOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGATRIM_PGADISANTILOCK, self).__init__(register,
            'PGADISANTILOCK', 'RAC_NS.PGATRIM.PGADISANTILOCK', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGATRIM_PGAVCMOUTTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGATRIM_PGAVCMOUTTRIM, self).__init__(register,
            'PGAVCMOUTTRIM', 'RAC_NS.PGATRIM.PGAVCMOUTTRIM', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGATRIM_PGAVLDOTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGATRIM_PGAVLDOTRIM, self).__init__(register,
            'PGAVLDOTRIM', 'RAC_NS.PGATRIM.PGAVLDOTRIM', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACAL_PGAOFFNCALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACAL_PGAOFFNCALI, self).__init__(register,
            'PGAOFFNCALI', 'RAC_NS.PGACAL.PGAOFFNCALI', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACAL_PGAOFFNCALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACAL_PGAOFFNCALQ, self).__init__(register,
            'PGAOFFNCALQ', 'RAC_NS.PGACAL.PGAOFFNCALQ', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACAL_PGAOFFPCALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACAL_PGAOFFPCALI, self).__init__(register,
            'PGAOFFPCALI', 'RAC_NS.PGACAL.PGAOFFPCALI', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACAL_PGAOFFPCALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACAL_PGAOFFPCALQ, self).__init__(register,
            'PGAOFFPCALQ', 'RAC_NS.PGACAL.PGAOFFPCALQ', 'read-write',
            u"",
            24, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGABWMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGABWMODE, self).__init__(register,
            'PGABWMODE', 'RAC_NS.PGACTRL.PGABWMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENBIAS, self).__init__(register,
            'PGAENBIAS', 'RAC_NS.PGACTRL.PGAENBIAS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENGHZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENGHZ, self).__init__(register,
            'PGAENGHZ', 'RAC_NS.PGACTRL.PGAENGHZ', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENHYST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENHYST, self).__init__(register,
            'PGAENHYST', 'RAC_NS.PGACTRL.PGAENHYST', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENLATCHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENLATCHI, self).__init__(register,
            'PGAENLATCHI', 'RAC_NS.PGACTRL.PGAENLATCHI', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENLATCHQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENLATCHQ, self).__init__(register,
            'PGAENLATCHQ', 'RAC_NS.PGACTRL.PGAENLATCHQ', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENLDOLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENLDOLOAD, self).__init__(register,
            'PGAENLDOLOAD', 'RAC_NS.PGACTRL.PGAENLDOLOAD', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENOFFD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENOFFD, self).__init__(register,
            'PGAENOFFD', 'RAC_NS.PGACTRL.PGAENOFFD', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENPGAI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENPGAI, self).__init__(register,
            'PGAENPGAI', 'RAC_NS.PGACTRL.PGAENPGAI', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENPGAQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENPGAQ, self).__init__(register,
            'PGAENPGAQ', 'RAC_NS.PGACTRL.PGAENPGAQ', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENPKD, self).__init__(register,
            'PGAENPKD', 'RAC_NS.PGACTRL.PGAENPKD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENRCMOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENRCMOUT, self).__init__(register,
            'PGAENRCMOUT', 'RAC_NS.PGACTRL.PGAENRCMOUT', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAENSUBG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAENSUBG, self).__init__(register,
            'PGAENSUBG', 'RAC_NS.PGACTRL.PGAENSUBG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGAPOWERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGAPOWERMODE, self).__init__(register,
            'PGAPOWERMODE', 'RAC_NS.PGACTRL.PGAPOWERMODE', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGATHRPKDLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGATHRPKDLOSEL, self).__init__(register,
            'PGATHRPKDLOSEL', 'RAC_NS.PGACTRL.PGATHRPKDLOSEL', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_PGATHRPKDHISEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_PGATHRPKDHISEL, self).__init__(register,
            'PGATHRPKDHISEL', 'RAC_NS.PGACTRL.PGATHRPKDHISEL', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PGACTRL_LNAMIXRFPKDTHRESHSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PGACTRL_LNAMIXRFPKDTHRESHSEL, self).__init__(register,
            'LNAMIXRFPKDTHRESHSEL', 'RAC_NS.PGACTRL.LNAMIXRFPKDTHRESHSEL', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCAL_RFBIASCALBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCAL_RFBIASCALBIAS, self).__init__(register,
            'RFBIASCALBIAS', 'RAC_NS.RFBIASCAL.RFBIASCALBIAS', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCAL_RFBIASCALTC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCAL_RFBIASCALTC, self).__init__(register,
            'RFBIASCALTC', 'RAC_NS.RFBIASCAL.RFBIASCALTC', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCAL_RFBIASCALVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCAL_RFBIASCALVREF, self).__init__(register,
            'RFBIASCALVREF', 'RAC_NS.RFBIASCAL.RFBIASCALVREF', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCAL_RFBIASCALVREFSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCAL_RFBIASCALVREFSTARTUP, self).__init__(register,
            'RFBIASCALVREFSTARTUP', 'RAC_NS.RFBIASCAL.RFBIASCALVREFSTARTUP', 'read-write',
            u"",
            24, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP, self).__init__(register,
            'RFBIASDISABLEBOOTSTRAP', 'RAC_NS.RFBIASCTRL.RFBIASDISABLEBOOTSTRAP', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCTRL_RFBIASLDOHIGHCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCTRL_RFBIASLDOHIGHCURRENT, self).__init__(register,
            'RFBIASLDOHIGHCURRENT', 'RAC_NS.RFBIASCTRL.RFBIASLDOHIGHCURRENT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCTRL_RFBIASNONFLASHMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCTRL_RFBIASNONFLASHMODE, self).__init__(register,
            'RFBIASNONFLASHMODE', 'RAC_NS.RFBIASCTRL.RFBIASNONFLASHMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCTRL_RFBIASSTARTUPCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCTRL_RFBIASSTARTUPCORE, self).__init__(register,
            'RFBIASSTARTUPCORE', 'RAC_NS.RFBIASCTRL.RFBIASSTARTUPCORE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCTRL_RFBIASSTARTUPSUPPLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCTRL_RFBIASSTARTUPSUPPLY, self).__init__(register,
            'RFBIASSTARTUPSUPPLY', 'RAC_NS.RFBIASCTRL.RFBIASSTARTUPSUPPLY', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFBIASCTRL_RFBIASLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFBIASCTRL_RFBIASLDOVREFTRIM, self).__init__(register,
            'RFBIASLDOVREFTRIM', 'RAC_NS.RFBIASCTRL.RFBIASLDOVREFTRIM', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RADIOEN_PREEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RADIOEN_PREEN, self).__init__(register,
            'PREEN', 'RAC_NS.RADIOEN.PREEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RADIOEN_PRESTB100UDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RADIOEN_PRESTB100UDIS, self).__init__(register,
            'PRESTB100UDIS', 'RAC_NS.RADIOEN.PRESTB100UDIS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RADIOEN_RFBIASEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RADIOEN_RFBIASEN, self).__init__(register,
            'RFBIASEN', 'RAC_NS.RADIOEN.RFBIASEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN0DBMPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN0DBMPA1, self).__init__(register,
            'LNAMIXEN0DBMPA1', 'RAC_NS.RFPATHEN1.LNAMIXEN0DBMPA1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN1, self).__init__(register,
            'LNAMIXEN1', 'RAC_NS.RFPATHEN1.LNAMIXEN1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFATTDCEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFATTDCEN1, self).__init__(register,
            'LNAMIXRFATTDCEN1', 'RAC_NS.RFPATHEN1.LNAMIXRFATTDCEN1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFPKDENRF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFPKDENRF1, self).__init__(register,
            'LNAMIXRFPKDENRF1', 'RAC_NS.RFPATHEN1.LNAMIXRFPKDENRF1', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXTRSW1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXTRSW1, self).__init__(register,
            'LNAMIXTRSW1', 'RAC_NS.RFPATHEN1.LNAMIXTRSW1', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_PAENANT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_PAENANT1, self).__init__(register,
            'PAENANT1', 'RAC_NS.RFPATHEN1.PAENANT1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_PAENPA10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_PAENPA10DBM, self).__init__(register,
            'PAENPA10DBM', 'RAC_NS.RFPATHEN1.PAENPA10DBM', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_PAENPAPREDRV10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_PAENPAPREDRV10DBM, self).__init__(register,
            'PAENPAPREDRV10DBM', 'RAC_NS.RFPATHEN1.PAENPAPREDRV10DBM', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN2_LNAMIXEN0DBMPA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN2_LNAMIXEN0DBMPA2, self).__init__(register,
            'LNAMIXEN0DBMPA2', 'RAC_NS.RFPATHEN2.LNAMIXEN0DBMPA2', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN2_LNAMIXEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN2_LNAMIXEN2, self).__init__(register,
            'LNAMIXEN2', 'RAC_NS.RFPATHEN2.LNAMIXEN2', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN2_LNAMIXRFATTDCEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN2_LNAMIXRFATTDCEN2, self).__init__(register,
            'LNAMIXRFATTDCEN2', 'RAC_NS.RFPATHEN2.LNAMIXRFATTDCEN2', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN2_LNAMIXRFPKDENRF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN2_LNAMIXRFPKDENRF2, self).__init__(register,
            'LNAMIXRFPKDENRF2', 'RAC_NS.RFPATHEN2.LNAMIXRFPKDENRF2', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN2_LNAMIXTRSW2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN2_LNAMIXTRSW2, self).__init__(register,
            'LNAMIXTRSW2', 'RAC_NS.RFPATHEN2.LNAMIXTRSW2', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN2_PAENANT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN2_PAENANT2, self).__init__(register,
            'PAENANT2', 'RAC_NS.RFPATHEN2.PAENANT2', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN2_PAENPA20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN2_PAENPA20DBM, self).__init__(register,
            'PAENPA20DBM', 'RAC_NS.RFPATHEN2.PAENPA20DBM', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN2_PAENPAPREDRV20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN2_PAENPAPREDRV20DBM, self).__init__(register,
            'PAENPAPREDRV20DBM', 'RAC_NS.RFPATHEN2.PAENPAPREDRV20DBM', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_IFADCCAPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_IFADCCAPRESET, self).__init__(register,
            'IFADCCAPRESET', 'RAC_NS.RX.IFADCCAPRESET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_IFADCENLDOSERIES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_IFADCENLDOSERIES, self).__init__(register,
            'IFADCENLDOSERIES', 'RAC_NS.RX.IFADCENLDOSERIES', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_IFADCENLDOSHUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_IFADCENLDOSHUNT, self).__init__(register,
            'IFADCENLDOSHUNT', 'RAC_NS.RX.IFADCENLDOSHUNT', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXENRFPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXENRFPKD, self).__init__(register,
            'LNAMIXENRFPKD', 'RAC_NS.RX.LNAMIXENRFPKD', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXLDOLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXLDOLOWCUR, self).__init__(register,
            'LNAMIXLDOLOWCUR', 'RAC_NS.RX.LNAMIXLDOLOWCUR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXREGLOADEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXREGLOADEN, self).__init__(register,
            'LNAMIXREGLOADEN', 'RAC_NS.RX.LNAMIXREGLOADEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_PGAENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_PGAENLDO, self).__init__(register,
            'PGAENLDO', 'RAC_NS.RX.PGAENLDO', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYCHPBIASTRIMBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYCHPBIASTRIMBUF, self).__init__(register,
            'SYCHPBIASTRIMBUF', 'RAC_NS.RX.SYCHPBIASTRIMBUF', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYCHPQNC3EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYCHPQNC3EN, self).__init__(register,
            'SYCHPQNC3EN', 'RAC_NS.RX.SYCHPQNC3EN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYMMDMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYMMDMODE, self).__init__(register,
            'SYMMDMODE', 'RAC_NS.RX.SYMMDMODE', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYPFDCHPLPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYPFDCHPLPEN, self).__init__(register,
            'SYPFDCHPLPEN', 'RAC_NS.RX.SYPFDCHPLPEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYPFDFPWEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYPFDFPWEN, self).__init__(register,
            'SYPFDFPWEN', 'RAC_NS.RX.SYPFDFPWEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PABLEEDDRVREG0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PABLEEDDRVREG0DBM, self).__init__(register,
            'PABLEEDDRVREG0DBM', 'RAC_NS.TX.PABLEEDDRVREG0DBM', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PABLEEDREG0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PABLEEDREG0DBM, self).__init__(register,
            'PABLEEDREG0DBM', 'RAC_NS.TX.PABLEEDREG0DBM', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENBIAS0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENBIAS0DBM, self).__init__(register,
            'PAENBIAS0DBM', 'RAC_NS.TX.PAENBIAS0DBM', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENDRVREG0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENDRVREG0DBM, self).__init__(register,
            'PAENDRVREG0DBM', 'RAC_NS.TX.PAENDRVREG0DBM', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENDRVREGBIAS0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENDRVREGBIAS0DBM, self).__init__(register,
            'PAENDRVREGBIAS0DBM', 'RAC_NS.TX.PAENDRVREGBIAS0DBM', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENLO0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENLO0DBM, self).__init__(register,
            'PAENLO0DBM', 'RAC_NS.TX.PAENLO0DBM', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENREG0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENREG0DBM, self).__init__(register,
            'PAENREG0DBM', 'RAC_NS.TX.PAENREG0DBM', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENTAPCAP0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENTAPCAP0DBM, self).__init__(register,
            'PAENTAPCAP0DBM', 'RAC_NS.TX.PAENTAPCAP0DBM', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_ENPATRIMPASLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_ENPATRIMPASLICE0DBM, self).__init__(register,
            'ENPATRIMPASLICE0DBM', 'RAC_NS.TX.ENPATRIMPASLICE0DBM', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAEN10DBMM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAEN10DBMM, self).__init__(register,
            'PAEN10DBMM', 'RAC_NS.TX.PAEN10DBMM', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAEN10DBMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAEN10DBMP, self).__init__(register,
            'PAEN10DBMP', 'RAC_NS.TX.PAEN10DBMP', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAEN10DBMPDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAEN10DBMPDRV, self).__init__(register,
            'PAEN10DBMPDRV', 'RAC_NS.TX.PAEN10DBMPDRV', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAEN20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAEN20DBM, self).__init__(register,
            'PAEN20DBM', 'RAC_NS.TX.PAEN20DBM', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAEN20DBMPDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAEN20DBMPDRV, self).__init__(register,
            'PAEN20DBMPDRV', 'RAC_NS.TX.PAEN20DBMPDRV', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENBLEEDPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENBLEEDPDRVLDO, self).__init__(register,
            'PAENBLEEDPDRVLDO', 'RAC_NS.TX.PAENBLEEDPDRVLDO', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENBLEEDPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENBLEEDPREREG, self).__init__(register,
            'PAENBLEEDPREREG', 'RAC_NS.TX.PAENBLEEDPREREG', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENLDOHVPDRVLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENLDOHVPDRVLDO, self).__init__(register,
            'PAENLDOHVPDRVLDO', 'RAC_NS.TX.PAENLDOHVPDRVLDO', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENLDOHVPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENLDOHVPREREG, self).__init__(register,
            'PAENLDOHVPREREG', 'RAC_NS.TX.PAENLDOHVPREREG', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_PAENPAOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_PAENPAOUT, self).__init__(register,
            'PAENPAOUT', 'RAC_NS.TX.PAENPAOUT', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_ENXOSQBUFFILT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_ENXOSQBUFFILT, self).__init__(register,
            'ENXOSQBUFFILT', 'RAC_NS.TX.ENXOSQBUFFILT', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_ENPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_ENPAPOWER, self).__init__(register,
            'ENPAPOWER', 'RAC_NS.TX.ENPAPOWER', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_ENPASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_ENPASELSLICE, self).__init__(register,
            'ENPASELSLICE', 'RAC_NS.TX.ENPASELSLICE', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYCHPSWITCHEDBIASEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYCHPSWITCHEDBIASEN, self).__init__(register,
            'SYCHPSWITCHEDBIASEN', 'RAC_NS.SYDEBUG.SYCHPSWITCHEDBIASEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYENMMDDREGBIASSTB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYENMMDDREGBIASSTB, self).__init__(register,
            'SYENMMDDREGBIASSTB', 'RAC_NS.SYDEBUG.SYENMMDDREGBIASSTB', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYLODIVAUXLODIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYLODIVAUXLODIS, self).__init__(register,
            'SYLODIVAUXLODIS', 'RAC_NS.SYDEBUG.SYLODIVAUXLODIS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYLODIVCLKSYNCSGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYLODIVCLKSYNCSGEN, self).__init__(register,
            'SYLODIVCLKSYNCSGEN', 'RAC_NS.SYDEBUG.SYLODIVCLKSYNCSGEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYLODIVLDOPSRTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYLODIVLDOPSRTRIM, self).__init__(register,
            'SYLODIVLDOPSRTRIM', 'RAC_NS.SYDEBUG.SYLODIVLDOPSRTRIM', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYPFDLOCKWINDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYPFDLOCKWINDOWN, self).__init__(register,
            'SYPFDLOCKWINDOWN', 'RAC_NS.SYDEBUG.SYPFDLOCKWINDOWN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYPFDTRADMODEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYPFDTRADMODEEN, self).__init__(register,
            'SYPFDTRADMODEEN', 'RAC_NS.SYDEBUG.SYPFDTRADMODEEN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYVCOREGBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYVCOREGBYPASS, self).__init__(register,
            'SYVCOREGBYPASS', 'RAC_NS.SYDEBUG.SYVCOREGBYPASS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPBIAS, self).__init__(register,
            'SYCHPBIAS', 'RAC_NS.SYTRIM0.SYCHPBIAS', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPCURR, self).__init__(register,
            'SYCHPCURR', 'RAC_NS.SYTRIM0.SYCHPCURR', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPLEVNSRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPLEVNSRC, self).__init__(register,
            'SYCHPLEVNSRC', 'RAC_NS.SYTRIM0.SYCHPLEVNSRC', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPLEVPSRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPLEVPSRC, self).__init__(register,
            'SYCHPLEVPSRC', 'RAC_NS.SYTRIM0.SYCHPLEVPSRC', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPSRCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPSRCEN, self).__init__(register,
            'SYCHPSRCEN', 'RAC_NS.SYTRIM0.SYCHPSRCEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPREPLICACURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPREPLICACURRADJ, self).__init__(register,
            'SYCHPREPLICACURRADJ', 'RAC_NS.SYTRIM0.SYCHPREPLICACURRADJ', 'read-write',
            u"",
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBIAS, self).__init__(register,
            'SYTRIMCHPREGAMPBIAS', 'RAC_NS.SYTRIM0.SYTRIMCHPREGAMPBIAS', 'read-write',
            u"",
            17, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBW, self).__init__(register,
            'SYTRIMCHPREGAMPBW', 'RAC_NS.SYTRIM0.SYTRIMCHPREGAMPBW', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMCORE, self).__init__(register,
            'SYLODIVLDOTRIMCORE', 'RAC_NS.SYTRIM1.SYLODIVLDOTRIMCORE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMNDIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMNDIO, self).__init__(register,
            'SYLODIVLDOTRIMNDIO', 'RAC_NS.SYTRIM1.SYLODIVLDOTRIMNDIO', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA1CURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA1CURRADJ, self).__init__(register,
            'SYMMDREPLICA1CURRADJ', 'RAC_NS.SYTRIM1.SYMMDREPLICA1CURRADJ', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA2CURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA2CURRADJ, self).__init__(register,
            'SYMMDREPLICA2CURRADJ', 'RAC_NS.SYTRIM1.SYMMDREPLICA2CURRADJ', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBIAS, self).__init__(register,
            'SYTRIMMMDREGAMPBIAS', 'RAC_NS.SYTRIM1.SYTRIMMMDREGAMPBIAS', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBW, self).__init__(register,
            'SYTRIMMMDREGAMPBW', 'RAC_NS.SYTRIM1.SYTRIMMMDREGAMPBW', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCAL_SYVCOMODEPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCAL_SYVCOMODEPKD, self).__init__(register,
            'SYVCOMODEPKD', 'RAC_NS.SYCAL.SYVCOMODEPKD', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCAL_SYVCOMORECURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCAL_SYVCOMORECURRENT, self).__init__(register,
            'SYVCOMORECURRENT', 'RAC_NS.SYCAL.SYVCOMORECURRENT', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCAL_SYVCOSLOWNOISEFILTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCAL_SYVCOSLOWNOISEFILTER, self).__init__(register,
            'SYVCOSLOWNOISEFILTER', 'RAC_NS.SYCAL.SYVCOSLOWNOISEFILTER', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCAL_SYVCOVCAPVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCAL_SYVCOVCAPVCM, self).__init__(register,
            'SYVCOVCAPVCM', 'RAC_NS.SYCAL.SYVCOVCAPVCM', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCAL_SYHILOADCHPREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCAL_SYHILOADCHPREG, self).__init__(register,
            'SYHILOADCHPREG', 'RAC_NS.SYCAL.SYHILOADCHPREG', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYCHPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYCHPEN, self).__init__(register,
            'SYCHPEN', 'RAC_NS.SYEN.SYCHPEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYCHPLPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYCHPLPEN, self).__init__(register,
            'SYCHPLPEN', 'RAC_NS.SYEN.SYCHPLPEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENCHPREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENCHPREG, self).__init__(register,
            'SYENCHPREG', 'RAC_NS.SYEN.SYENCHPREG', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENCHPREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENCHPREPLICA, self).__init__(register,
            'SYENCHPREPLICA', 'RAC_NS.SYEN.SYENCHPREPLICA', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENMMDREG, self).__init__(register,
            'SYENMMDREG', 'RAC_NS.SYEN.SYENMMDREG', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENMMDREPLICA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENMMDREPLICA1, self).__init__(register,
            'SYENMMDREPLICA1', 'RAC_NS.SYEN.SYENMMDREPLICA1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENMMDREPLICA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENMMDREPLICA2, self).__init__(register,
            'SYENMMDREPLICA2', 'RAC_NS.SYEN.SYENMMDREPLICA2', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOBIAS, self).__init__(register,
            'SYENVCOBIAS', 'RAC_NS.SYEN.SYENVCOBIAS', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOPFET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOPFET, self).__init__(register,
            'SYENVCOPFET', 'RAC_NS.SYEN.SYENVCOPFET', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOREG, self).__init__(register,
            'SYENVCOREG', 'RAC_NS.SYEN.SYENVCOREG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYLODIVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYLODIVEN, self).__init__(register,
            'SYLODIVEN', 'RAC_NS.SYEN.SYLODIVEN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYLODIVLDOBIASEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYLODIVLDOBIASEN, self).__init__(register,
            'SYLODIVLDOBIASEN', 'RAC_NS.SYEN.SYLODIVLDOBIASEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYLODIVLDOEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYLODIVLDOEN, self).__init__(register,
            'SYLODIVLDOEN', 'RAC_NS.SYEN.SYLODIVLDOEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYSTARTCHPREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYSTARTCHPREG, self).__init__(register,
            'SYSTARTCHPREG', 'RAC_NS.SYEN.SYSTARTCHPREG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYSTARTMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYSTARTMMDREG, self).__init__(register,
            'SYSTARTMMDREG', 'RAC_NS.SYEN.SYSTARTMMDREG', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVRLOADCCLK2G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVRLOADCCLK2G4EN, self).__init__(register,
            'SYLODIVRLOADCCLK2G4EN', 'RAC_NS.SYLOEN.SYLODIVRLOADCCLK2G4EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVRLO12G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVRLO12G4EN, self).__init__(register,
            'SYLODIVRLO12G4EN', 'RAC_NS.SYLOEN.SYLODIVRLO12G4EN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVRLO1SGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVRLO1SGEN, self).__init__(register,
            'SYLODIVRLO1SGEN', 'RAC_NS.SYLOEN.SYLODIVRLO1SGEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVRLO22G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVRLO22G4EN, self).__init__(register,
            'SYLODIVRLO22G4EN', 'RAC_NS.SYLOEN.SYLODIVRLO22G4EN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVRLO2SGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVRLO2SGEN, self).__init__(register,
            'SYLODIVRLO2SGEN', 'RAC_NS.SYLOEN.SYLODIVRLO2SGEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLO0DBM2G4AUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLO0DBM2G4AUXEN, self).__init__(register,
            'SYLODIVTLO0DBM2G4AUXEN', 'RAC_NS.SYLOEN.SYLODIVTLO0DBM2G4AUXEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLO0DBM2G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLO0DBM2G4EN, self).__init__(register,
            'SYLODIVTLO0DBM2G4EN', 'RAC_NS.SYLOEN.SYLODIVTLO0DBM2G4EN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLO0DBMSGAUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLO0DBMSGAUXEN, self).__init__(register,
            'SYLODIVTLO0DBMSGAUXEN', 'RAC_NS.SYLOEN.SYLODIVTLO0DBMSGAUXEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLO0DBMSGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLO0DBMSGEN, self).__init__(register,
            'SYLODIVTLO0DBMSGEN', 'RAC_NS.SYLOEN.SYLODIVTLO0DBMSGEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLO20DBM2G4AUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLO20DBM2G4AUXEN, self).__init__(register,
            'SYLODIVTLO20DBM2G4AUXEN', 'RAC_NS.SYLOEN.SYLODIVTLO20DBM2G4AUXEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLO20DBM2G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLO20DBM2G4EN, self).__init__(register,
            'SYLODIVTLO20DBM2G4EN', 'RAC_NS.SYLOEN.SYLODIVTLO20DBM2G4EN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLO20DBMSGAUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLO20DBMSGAUXEN, self).__init__(register,
            'SYLODIVTLO20DBMSGAUXEN', 'RAC_NS.SYLOEN.SYLODIVTLO20DBMSGAUXEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLO20DBMSGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLO20DBMSGEN, self).__init__(register,
            'SYLODIVTLO20DBMSGEN', 'RAC_NS.SYLOEN.SYLODIVTLO20DBMSGEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYMMDCTRL_SYMMDENRSDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYMMDCTRL_SYMMDENRSDIG, self).__init__(register,
            'SYMMDENRSDIG', 'RAC_NS.SYMMDCTRL.SYMMDENRSDIG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYMMDCTRL_SYMMDDIVRSDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYMMDCTRL_SYMMDDIVRSDIG, self).__init__(register,
            'SYMMDDIVRSDIG', 'RAC_NS.SYMMDCTRL.SYMMDDIVRSDIG', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME, self).__init__(register,
            'DIGCLKRETIMEENRETIME', 'RAC_NS.DIGCLKRETIMECTRL.DIGCLKRETIMEENRETIME', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME, self).__init__(register,
            'DIGCLKRETIMEDISRETIME', 'RAC_NS.DIGCLKRETIMECTRL.DIGCLKRETIMEDISRETIME', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN, self).__init__(register,
            'DIGCLKRETIMERESETN', 'RAC_NS.DIGCLKRETIMECTRL.DIGCLKRETIMERESETN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH, self).__init__(register,
            'DIGCLKRETIMELIMITH', 'RAC_NS.DIGCLKRETIMECTRL.DIGCLKRETIMELIMITH', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL, self).__init__(register,
            'DIGCLKRETIMELIMITL', 'RAC_NS.DIGCLKRETIMECTRL.DIGCLKRETIMELIMITL', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL, self).__init__(register,
            'DIGCLKRETIMECLKSEL', 'RAC_NS.DIGCLKRETIMESTATUS.DIGCLKRETIMECLKSEL', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO, self).__init__(register,
            'DIGCLKRETIMERESETNLO', 'RAC_NS.DIGCLKRETIMESTATUS.DIGCLKRETIMERESETNLO', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_XORETIMECTRL_XORETIMEENRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_XORETIMECTRL_XORETIMEENRETIME, self).__init__(register,
            'XORETIMEENRETIME', 'RAC_NS.XORETIMECTRL.XORETIMEENRETIME', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_XORETIMECTRL_XORETIMEDISRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_XORETIMECTRL_XORETIMEDISRETIME, self).__init__(register,
            'XORETIMEDISRETIME', 'RAC_NS.XORETIMECTRL.XORETIMEDISRETIME', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_XORETIMECTRL_XORETIMERESETN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_XORETIMECTRL_XORETIMERESETN, self).__init__(register,
            'XORETIMERESETN', 'RAC_NS.XORETIMECTRL.XORETIMERESETN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_XORETIMECTRL_XORETIMELIMITH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_XORETIMECTRL_XORETIMELIMITH, self).__init__(register,
            'XORETIMELIMITH', 'RAC_NS.XORETIMECTRL.XORETIMELIMITH', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_XORETIMECTRL_XORETIMELIMITL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_XORETIMECTRL_XORETIMELIMITL, self).__init__(register,
            'XORETIMELIMITL', 'RAC_NS.XORETIMECTRL.XORETIMELIMITL', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_XORETIMESTATUS_XORETIMECLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_XORETIMESTATUS_XORETIMECLKSEL, self).__init__(register,
            'XORETIMECLKSEL', 'RAC_NS.XORETIMESTATUS.XORETIMECLKSEL', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_XORETIMESTATUS_XORETIMERESETNLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_XORETIMESTATUS_XORETIMERESETNLO, self).__init__(register,
            'XORETIMERESETNLO', 'RAC_NS.XORETIMESTATUS.XORETIMERESETNLO', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_XOSQBUFFILT_XOSQBUFFILT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_XOSQBUFFILT_XOSQBUFFILT, self).__init__(register,
            'XOSQBUFFILT', 'RAC_NS.XOSQBUFFILT.XOSQBUFFILT', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_AUXADCSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_AUXADCSPARE, self).__init__(register,
            'AUXADCSPARE', 'RAC_NS.SPARE.AUXADCSPARE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_CLKMULTSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_CLKMULTSPARE, self).__init__(register,
            'CLKMULTSPARE', 'RAC_NS.SPARE.CLKMULTSPARE', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_IFADCSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_IFADCSPARE, self).__init__(register,
            'IFADCSPARE', 'RAC_NS.SPARE.IFADCSPARE', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_PATRIMSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_PATRIMSPARE, self).__init__(register,
            'PATRIMSPARE', 'RAC_NS.SPARE.PATRIMSPARE', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_PGASPACER0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_PGASPACER0, self).__init__(register,
            'PGASPACER0', 'RAC_NS.SPARE.PGASPACER0', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_SYSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_SYSPARE, self).__init__(register,
            'SYSPARE', 'RAC_NS.SPARE.SYSPARE', 'read-write',
            u"",
            11, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_EN, self).__init__(register,
            'EN', 'RAC_NS.ANTDIV.EN', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_STATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_STATUS, self).__init__(register,
            'STATUS', 'RAC_NS.ANTDIV.STATUS', 'read-only',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SCRATCH0_SCRATCH0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SCRATCH0_SCRATCH0, self).__init__(register,
            'SCRATCH0', 'RAC_NS.SCRATCH0.SCRATCH0', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SCRATCH1_SCRATCH1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SCRATCH1_SCRATCH1, self).__init__(register,
            'SCRATCH1', 'RAC_NS.SCRATCH1.SCRATCH1', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SCRATCH2_SCRATCH2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SCRATCH2_SCRATCH2, self).__init__(register,
            'SCRATCH2', 'RAC_NS.SCRATCH2.SCRATCH2', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SCRATCH3_SCRATCH3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SCRATCH3_SCRATCH3, self).__init__(register,
            'SCRATCH3', 'RAC_NS.SCRATCH3.SCRATCH3', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SCRATCH4_SCRATCH4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SCRATCH4_SCRATCH4, self).__init__(register,
            'SCRATCH4', 'RAC_NS.SCRATCH4.SCRATCH4', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SCRATCH5_SCRATCH5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SCRATCH5_SCRATCH5, self).__init__(register,
            'SCRATCH5', 'RAC_NS.SCRATCH5.SCRATCH5', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SCRATCH6_SCRATCH6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SCRATCH6_SCRATCH6, self).__init__(register,
            'SCRATCH6', 'RAC_NS.SCRATCH6.SCRATCH6', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SCRATCH7_SCRATCH7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SCRATCH7_SCRATCH7, self).__init__(register,
            'SCRATCH7', 'RAC_NS.SCRATCH7.SCRATCH7', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_SYNTHLODIVFREQCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_SYNTHLODIVFREQCTRL, self).__init__(register,
            'SYNTHLODIVFREQCTRL', 'RAC_NS.RFLOCK0.SYNTHLODIVFREQCTRL', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACIFPGAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACIFPGAEN, self).__init__(register,
            'RACIFPGAEN', 'RAC_NS.RFLOCK0.RACIFPGAEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACPAEN10DBMM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACPAEN10DBMM, self).__init__(register,
            'RACPAEN10DBMM', 'RAC_NS.RFLOCK0.RACPAEN10DBMM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACPAEN10DBMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACPAEN10DBMP, self).__init__(register,
            'RACPAEN10DBMP', 'RAC_NS.RFLOCK0.RACPAEN10DBMP', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACPAEN20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACPAEN20DBM, self).__init__(register,
            'RACPAEN20DBM', 'RAC_NS.RFLOCK0.RACPAEN20DBM', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACSGPAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACSGPAEN, self).__init__(register,
            'RACSGPAEN', 'RAC_NS.RFLOCK0.RACSGPAEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_FRCCONVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_FRCCONVMODE, self).__init__(register,
            'FRCCONVMODE', 'RAC_NS.RFLOCK0.FRCCONVMODE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_FRCPAUSING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_FRCPAUSING, self).__init__(register,
            'FRCPAUSING', 'RAC_NS.RFLOCK0.FRCPAUSING', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_MODEMDSSS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_MODEMDSSS, self).__init__(register,
            'MODEMDSSS', 'RAC_NS.RFLOCK0.MODEMDSSS', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_MODEMDEC1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_MODEMDEC1, self).__init__(register,
            'MODEMDEC1', 'RAC_NS.RFLOCK0.MODEMDEC1', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_MODEMMODFORMAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_MODEMMODFORMAT, self).__init__(register,
            'MODEMMODFORMAT', 'RAC_NS.RFLOCK0.MODEMMODFORMAT', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_MODEMDUALSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_MODEMDUALSYNC, self).__init__(register,
            'MODEMDUALSYNC', 'RAC_NS.RFLOCK0.MODEMDUALSYNC', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_MODEMANTDIVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_MODEMANTDIVMODE, self).__init__(register,
            'MODEMANTDIVMODE', 'RAC_NS.RFLOCK0.MODEMANTDIVMODE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'RAC_NS.RFLOCK0.UNLOCKED', 'read-only',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK1_RACPASLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACPASLICE0DBM, self).__init__(register,
            'RACPASLICE0DBM', 'RAC_NS.RFLOCK1.RACPASLICE0DBM', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK1_RACDRVSLICE0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACDRVSLICE0DBM, self).__init__(register,
            'RACDRVSLICE0DBM', 'RAC_NS.RFLOCK1.RACDRVSLICE0DBM', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK1_RACPASTRIPE10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACPASTRIPE10DBM, self).__init__(register,
            'RACPASTRIPE10DBM', 'RAC_NS.RFLOCK1.RACPASTRIPE10DBM', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK1_RACPASLICE10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACPASLICE10DBM, self).__init__(register,
            'RACPASLICE10DBM', 'RAC_NS.RFLOCK1.RACPASLICE10DBM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK1_RACPASTRIPE20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACPASTRIPE20DBM, self).__init__(register,
            'RACPASTRIPE20DBM', 'RAC_NS.RFLOCK1.RACPASTRIPE20DBM', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK1_RACPASLICE20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACPASLICE20DBM, self).__init__(register,
            'RACPASLICE20DBM', 'RAC_NS.RFLOCK1.RACPASLICE20DBM', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True



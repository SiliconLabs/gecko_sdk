
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


class RM_Field_RAC_NS_STATUS_SEQSLEEPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_SEQSLEEPING, self).__init__(register,
            'SEQSLEEPING', 'RAC_NS.STATUS.SEQSLEEPING', 'read-only',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_SEQSLEEPDEEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_SEQSLEEPDEEP, self).__init__(register,
            'SEQSLEEPDEEP', 'RAC_NS.STATUS.SEQSLEEPDEEP', 'read-only',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_STATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_STATE, self).__init__(register,
            'STATE', 'RAC_NS.STATUS.STATE', 'read-only',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS_SEQACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS_SEQACTIVE, self).__init__(register,
            'SEQACTIVE', 'RAC_NS.STATUS.SEQACTIVE', 'read-only',
            u"",
            28, 1)
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


class RM_Field_RAC_NS_CMD_FRCWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_FRCWR, self).__init__(register,
            'FRCWR', 'RAC_NS.CMD.FRCWR', 'write-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CMD_FRCRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CMD_FRCRD, self).__init__(register,
            'FRCRD', 'RAC_NS.CMD.FRCRD', 'write-only',
            u"",
            11, 1)
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


class RM_Field_RAC_NS_CTRL_SEQRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_SEQRESET, self).__init__(register,
            'SEQRESET', 'RAC_NS.CTRL.SEQRESET', 'write-only',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_EXITSHUTDOWNDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_EXITSHUTDOWNDIS, self).__init__(register,
            'EXITSHUTDOWNDIS', 'RAC_NS.CTRL.EXITSHUTDOWNDIS', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_CPUWAITDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_CPUWAITDIS, self).__init__(register,
            'CPUWAITDIS', 'RAC_NS.CTRL.CPUWAITDIS', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_SEQCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_SEQCLKDIS, self).__init__(register,
            'SEQCLKDIS', 'RAC_NS.CTRL.SEQCLKDIS', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CTRL_RXOFDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CTRL_RXOFDIS, self).__init__(register,
            'RXOFDIS', 'RAC_NS.CTRL.RXOFDIS', 'read-write',
            u"",
            28, 1)
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


class RM_Field_RAC_NS_IF_SEQLOCKUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IF_SEQLOCKUP, self).__init__(register,
            'SEQLOCKUP', 'RAC_NS.IF.SEQLOCKUP', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IF_SEQRESETREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IF_SEQRESETREQ, self).__init__(register,
            'SEQRESETREQ', 'RAC_NS.IF.SEQRESETREQ', 'read-write',
            u"",
            3, 1)
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


class RM_Field_RAC_NS_IEN_SEQLOCKUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IEN_SEQLOCKUP, self).__init__(register,
            'SEQLOCKUP', 'RAC_NS.IEN.SEQLOCKUP', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IEN_SEQRESETREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IEN_SEQRESETREQ, self).__init__(register,
            'SEQRESETREQ', 'RAC_NS.IEN.SEQRESETREQ', 'read-write',
            u"",
            3, 1)
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


class RM_Field_RAC_NS_SEQIF_STATECHANGESEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATECHANGESEQ, self).__init__(register,
            'STATECHANGESEQ', 'RAC_NS.SEQIF.STATECHANGESEQ', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STIMCMPEVSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STIMCMPEVSEQ, self).__init__(register,
            'STIMCMPEVSEQ', 'RAC_NS.SEQIF.STIMCMPEVSEQ', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_DEMODRXREQCLRSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_DEMODRXREQCLRSEQ, self).__init__(register,
            'DEMODRXREQCLRSEQ', 'RAC_NS.SEQIF.DEMODRXREQCLRSEQ', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_PRSEVENTSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_PRSEVENTSEQ, self).__init__(register,
            'PRSEVENTSEQ', 'RAC_NS.SEQIF.PRSEVENTSEQ', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATEOFF, self).__init__(register,
            'STATEOFF', 'RAC_NS.SEQIF.STATEOFF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXWARM, self).__init__(register,
            'STATERXWARM', 'RAC_NS.SEQIF.STATERXWARM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXSEARCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXSEARCH, self).__init__(register,
            'STATERXSEARCH', 'RAC_NS.SEQIF.STATERXSEARCH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXFRAME, self).__init__(register,
            'STATERXFRAME', 'RAC_NS.SEQIF.STATERXFRAME', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXPD, self).__init__(register,
            'STATERXPD', 'RAC_NS.SEQIF.STATERXPD', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERX2RX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERX2RX, self).__init__(register,
            'STATERX2RX', 'RAC_NS.SEQIF.STATERX2RX', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXOVERFLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXOVERFLOW, self).__init__(register,
            'STATERXOVERFLOW', 'RAC_NS.SEQIF.STATERXOVERFLOW', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERX2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERX2TX, self).__init__(register,
            'STATERX2TX', 'RAC_NS.SEQIF.STATERX2TX', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETXWARM, self).__init__(register,
            'STATETXWARM', 'RAC_NS.SEQIF.STATETXWARM', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETX, self).__init__(register,
            'STATETX', 'RAC_NS.SEQIF.STATETX', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETXPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETXPD, self).__init__(register,
            'STATETXPD', 'RAC_NS.SEQIF.STATETXPD', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETX2RX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETX2RX, self).__init__(register,
            'STATETX2RX', 'RAC_NS.SEQIF.STATETX2RX', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETX2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETX2TX, self).__init__(register,
            'STATETX2TX', 'RAC_NS.SEQIF.STATETX2TX', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATESHUTDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATESHUTDOWN, self).__init__(register,
            'STATESHUTDOWN', 'RAC_NS.SEQIF.STATESHUTDOWN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATECHANGESEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATECHANGESEQ, self).__init__(register,
            'STATECHANGESEQ', 'RAC_NS.SEQIEN.STATECHANGESEQ', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STIMCMPEVSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STIMCMPEVSEQ, self).__init__(register,
            'STIMCMPEVSEQ', 'RAC_NS.SEQIEN.STIMCMPEVSEQ', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_DEMODRXREQCLRSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_DEMODRXREQCLRSEQ, self).__init__(register,
            'DEMODRXREQCLRSEQ', 'RAC_NS.SEQIEN.DEMODRXREQCLRSEQ', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_PRSEVENTSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_PRSEVENTSEQ, self).__init__(register,
            'PRSEVENTSEQ', 'RAC_NS.SEQIEN.PRSEVENTSEQ', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATEOFF, self).__init__(register,
            'STATEOFF', 'RAC_NS.SEQIEN.STATEOFF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXWARM, self).__init__(register,
            'STATERXWARM', 'RAC_NS.SEQIEN.STATERXWARM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXSEARCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXSEARCH, self).__init__(register,
            'STATERXSEARCH', 'RAC_NS.SEQIEN.STATERXSEARCH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXFRAME, self).__init__(register,
            'STATERXFRAME', 'RAC_NS.SEQIEN.STATERXFRAME', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXPD, self).__init__(register,
            'STATERXPD', 'RAC_NS.SEQIEN.STATERXPD', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERX2RX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERX2RX, self).__init__(register,
            'STATERX2RX', 'RAC_NS.SEQIEN.STATERX2RX', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXOVERFLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXOVERFLOW, self).__init__(register,
            'STATERXOVERFLOW', 'RAC_NS.SEQIEN.STATERXOVERFLOW', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERX2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERX2TX, self).__init__(register,
            'STATERX2TX', 'RAC_NS.SEQIEN.STATERX2TX', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETXWARM, self).__init__(register,
            'STATETXWARM', 'RAC_NS.SEQIEN.STATETXWARM', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETX, self).__init__(register,
            'STATETX', 'RAC_NS.SEQIEN.STATETX', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETXPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETXPD, self).__init__(register,
            'STATETXPD', 'RAC_NS.SEQIEN.STATETXPD', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETX2RX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETX2RX, self).__init__(register,
            'STATETX2RX', 'RAC_NS.SEQIEN.STATETX2RX', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETX2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETX2TX, self).__init__(register,
            'STATETX2TX', 'RAC_NS.SEQIEN.STATETX2TX', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATESHUTDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATESHUTDOWN, self).__init__(register,
            'STATESHUTDOWN', 'RAC_NS.SEQIEN.STATESHUTDOWN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STATUS1_TXMASK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS1_TXMASK, self).__init__(register,
            'TXMASK', 'RAC_NS.STATUS1.TXMASK', 'read-only',
            u"",
            0, 8)
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


class RM_Field_RAC_NS_SEQCTRL_RELATIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_RELATIVE, self).__init__(register,
            'RELATIVE', 'RAC_NS.SEQCTRL.RELATIVE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_STIMERALWAYSRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_STIMERALWAYSRUN, self).__init__(register,
            'STIMERALWAYSRUN', 'RAC_NS.SEQCTRL.STIMERALWAYSRUN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_STIMERDEBUGRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_STIMERDEBUGRUN, self).__init__(register,
            'STIMERDEBUGRUN', 'RAC_NS.SEQCTRL.STIMERDEBUGRUN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_STATEDEBUGRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_STATEDEBUGRUN, self).__init__(register,
            'STATEDEBUGRUN', 'RAC_NS.SEQCTRL.STATEDEBUGRUN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQCTRL_SWIRQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQCTRL_SWIRQ, self).__init__(register,
            'SWIRQ', 'RAC_NS.SEQCTRL.SWIRQ', 'read-write',
            u"",
            24, 2)
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


class RM_Field_RAC_NS_STCTRL_STCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STCTRL_STCAL, self).__init__(register,
            'STCAL', 'RAC_NS.STCTRL.STCAL', 'read-write',
            u"",
            0, 24)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_STCTRL_STSKEW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STCTRL_STSKEW, self).__init__(register,
            'STSKEW', 'RAC_NS.STCTRL.STSKEW', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_FRCTXWORD_WDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_FRCTXWORD_WDATA, self).__init__(register,
            'WDATA', 'RAC_NS.FRCTXWORD.WDATA', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_FRCRXWORD_RDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_FRCRXWORD_RDATA, self).__init__(register,
            'RDATA', 'RAC_NS.FRCRXWORD.RDATA', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_EM1PCSR_RADIOEM1PMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_EM1PCSR_RADIOEM1PMODE, self).__init__(register,
            'RADIOEM1PMODE', 'RAC_NS.EM1PCSR.RADIOEM1PMODE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_EM1PCSR_RADIOEM1PDISSWREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_EM1PCSR_RADIOEM1PDISSWREQ, self).__init__(register,
            'RADIOEM1PDISSWREQ', 'RAC_NS.EM1PCSR.RADIOEM1PDISSWREQ', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_EM1PCSR_MCUEM1PMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_EM1PCSR_MCUEM1PMODE, self).__init__(register,
            'MCUEM1PMODE', 'RAC_NS.EM1PCSR.MCUEM1PMODE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_EM1PCSR_MCUEM1PDISSWREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_EM1PCSR_MCUEM1PDISSWREQ, self).__init__(register,
            'MCUEM1PDISSWREQ', 'RAC_NS.EM1PCSR.MCUEM1PDISSWREQ', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_EM1PCSR_RADIOEM1PREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_EM1PCSR_RADIOEM1PREQ, self).__init__(register,
            'RADIOEM1PREQ', 'RAC_NS.EM1PCSR.RADIOEM1PREQ', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_EM1PCSR_RADIOEM1PACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_EM1PCSR_RADIOEM1PACK, self).__init__(register,
            'RADIOEM1PACK', 'RAC_NS.EM1PCSR.RADIOEM1PACK', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_EM1PCSR_RADIOEM1PHWREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_EM1PCSR_RADIOEM1PHWREQ, self).__init__(register,
            'RADIOEM1PHWREQ', 'RAC_NS.EM1PCSR.RADIOEM1PHWREQ', 'read-only',
            u"",
            18, 1)
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


class RM_Field_RAC_NS_SYNTHENCTRL_MMDPOWERBALANCEDISABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYNTHENCTRL_MMDPOWERBALANCEDISABLE, self).__init__(register,
            'MMDPOWERBALANCEDISABLE', 'RAC_NS.SYNTHENCTRL.MMDPOWERBALANCEDISABLE', 'read-write',
            u"",
            10, 1)
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


class RM_Field_RAC_NS_VCOCTRL_VCODETAMPLITUDERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VCOCTRL_VCODETAMPLITUDERX, self).__init__(register,
            'VCODETAMPLITUDERX', 'RAC_NS.VCOCTRL.VCODETAMPLITUDERX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VCOCTRL_VCODETAMPLITUDETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VCOCTRL_VCODETAMPLITUDETX, self).__init__(register,
            'VCODETAMPLITUDETX', 'RAC_NS.VCOCTRL.VCODETAMPLITUDETX', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CHPCTRL_CHPOUTPUTTRISTATEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CHPCTRL_CHPOUTPUTTRISTATEMODE, self).__init__(register,
            'CHPOUTPUTTRISTATEMODE', 'RAC_NS.CHPCTRL.CHPOUTPUTTRISTATEMODE', 'read-write',
            u"",
            14, 1)
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


class RM_Field_RAC_NS_STATUS2_CURRSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_STATUS2_CURRSTATE, self).__init__(register,
            'CURRSTATE', 'RAC_NS.STATUS2.CURRSTATE', 'read-only',
            u"",
            12, 4)
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


class RM_Field_RAC_NS_PAENCTRL_INVRAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PAENCTRL_INVRAMPCLK, self).__init__(register,
            'INVRAMPCLK', 'RAC_NS.PAENCTRL.INVRAMPCLK', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PAENCTRL_DIV2RAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PAENCTRL_DIV2RAMPCLK, self).__init__(register,
            'DIV2RAMPCLK', 'RAC_NS.PAENCTRL.DIV2RAMPCLK', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PAENCTRL_RSTDIV2RAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PAENCTRL_RSTDIV2RAMPCLK, self).__init__(register,
            'RSTDIV2RAMPCLK', 'RAC_NS.PAENCTRL.RSTDIV2RAMPCLK', 'read-write',
            u"",
            18, 1)
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


class RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXEN0, self).__init__(register,
            'INTDIVLNAMIXEN0', 'RAC_NS.ANTDIV.INTDIVLNAMIXEN0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXENAMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXENAMP0, self).__init__(register,
            'INTDIVLNAMIXENAMP0', 'RAC_NS.ANTDIV.INTDIVLNAMIXENAMP0', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFATTDCEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFATTDCEN0, self).__init__(register,
            'INTDIVLNAMIXRFATTDCEN0', 'RAC_NS.ANTDIV.INTDIVLNAMIXRFATTDCEN0', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFPKDENRF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFPKDENRF0, self).__init__(register,
            'INTDIVLNAMIXRFPKDENRF0', 'RAC_NS.ANTDIV.INTDIVLNAMIXRFPKDENRF0', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO0SUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO0SUBGEN, self).__init__(register,
            'INTDIVSYLODIVRLO0SUBGEN', 'RAC_NS.ANTDIV.INTDIVSYLODIVRLO0SUBGEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXEN1, self).__init__(register,
            'INTDIVLNAMIXEN1', 'RAC_NS.ANTDIV.INTDIVLNAMIXEN1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXENAMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXENAMP1, self).__init__(register,
            'INTDIVLNAMIXENAMP1', 'RAC_NS.ANTDIV.INTDIVLNAMIXENAMP1', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFATTDCEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFATTDCEN1, self).__init__(register,
            'INTDIVLNAMIXRFATTDCEN1', 'RAC_NS.ANTDIV.INTDIVLNAMIXRFATTDCEN1', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFPKDENRF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVLNAMIXRFPKDENRF1, self).__init__(register,
            'INTDIVLNAMIXRFPKDENRF1', 'RAC_NS.ANTDIV.INTDIVLNAMIXRFPKDENRF1', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO1SUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO1SUBGEN, self).__init__(register,
            'INTDIVSYLODIVRLO1SUBGEN', 'RAC_NS.ANTDIV.INTDIVSYLODIVRLO1SUBGEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_ANTDIV_ANTDIVSTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_ANTDIVSTATUS, self).__init__(register,
            'ANTDIVSTATUS', 'RAC_NS.ANTDIV.ANTDIVSTATUS', 'read-only',
            u"",
            10, 2)
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


class RM_Field_RAC_NS_AUXADCEN_AUXADCENMEASTHERMISTOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_AUXADCENMEASTHERMISTOR, self).__init__(register,
            'AUXADCENMEASTHERMISTOR', 'RAC_NS.AUXADCEN.AUXADCENMEASTHERMISTOR', 'read-write',
            u"",
            9, 1)
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


class RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL, self).__init__(register,
            'AUXADCTHERMISTORFREQSEL', 'RAC_NS.AUXADCCTRL1.AUXADCTHERMISTORFREQSEL', 'read-write',
            u"",
            28, 4)
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


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVN, self).__init__(register,
            'CLKMULTENDRVN', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVP, self).__init__(register,
            'CLKMULTENDRVP', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVP', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRX2P4G(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRX2P4G, self).__init__(register,
            'CLKMULTENDRVRX2P4G', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVRX2P4G', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRXSUBG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVRXSUBG, self).__init__(register,
            'CLKMULTENDRVRXSUBG', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVRXSUBG', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVTXDUALB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVTXDUALB, self).__init__(register,
            'CLKMULTENDRVTXDUALB', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVTXDUALB', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENFBDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENFBDIV, self).__init__(register,
            'CLKMULTENFBDIV', 'RAC_NS.CLKMULTEN0.CLKMULTENFBDIV', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREFDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREFDIV, self).__init__(register,
            'CLKMULTENREFDIV', 'RAC_NS.CLKMULTEN0.CLKMULTENREFDIV', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1, self).__init__(register,
            'CLKMULTENREG1', 'RAC_NS.CLKMULTEN0.CLKMULTENREG1', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG2, self).__init__(register,
            'CLKMULTENREG2', 'RAC_NS.CLKMULTEN0.CLKMULTENREG2', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG3, self).__init__(register,
            'CLKMULTENREG3', 'RAC_NS.CLKMULTEN0.CLKMULTENREG3', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENROTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENROTDET, self).__init__(register,
            'CLKMULTENROTDET', 'RAC_NS.CLKMULTEN0.CLKMULTENROTDET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBYPASS40MHZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENBYPASS40MHZ, self).__init__(register,
            'CLKMULTENBYPASS40MHZ', 'RAC_NS.CLKMULTEN0.CLKMULTENBYPASS40MHZ', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTFREQCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTFREQCAL, self).__init__(register,
            'CLKMULTFREQCAL', 'RAC_NS.CLKMULTEN0.CLKMULTFREQCAL', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJI, self).__init__(register,
            'CLKMULTREG2ADJI', 'RAC_NS.CLKMULTEN0.CLKMULTREG2ADJI', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG1ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG1ADJV, self).__init__(register,
            'CLKMULTREG1ADJV', 'RAC_NS.CLKMULTEN0.CLKMULTREG1ADJV', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG2ADJV, self).__init__(register,
            'CLKMULTREG2ADJV', 'RAC_NS.CLKMULTEN0.CLKMULTREG2ADJV', 'read-write',
            u"",
            28, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG3ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTREG3ADJV, self).__init__(register,
            'CLKMULTREG3ADJV', 'RAC_NS.CLKMULTEN0.CLKMULTREG3ADJV', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTINNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTINNIBBLE, self).__init__(register,
            'CLKMULTINNIBBLE', 'RAC_NS.CLKMULTEN1.CLKMULTINNIBBLE', 'read-write',
            u"",
            0, 4)
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


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDCNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTLDCNIB, self).__init__(register,
            'CLKMULTLDCNIB', 'RAC_NS.CLKMULTEN1.CLKMULTLDCNIB', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDRVAMPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDRVAMPSEL, self).__init__(register,
            'CLKMULTDRVAMPSEL', 'RAC_NS.CLKMULTEN1.CLKMULTDRVAMPSEL', 'read-write',
            u"",
            11, 6)
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


class RM_Field_RAC_NS_IFADCDBG_IFADCDISABLECLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_IFADCDISABLECLK, self).__init__(register,
            'IFADCDISABLECLK', 'RAC_NS.IFADCDBG.IFADCDISABLECLK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCCLKSEL, self).__init__(register,
            'IFADCCLKSEL', 'RAC_NS.IFADCTRIM0.IFADCCLKSEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSERIESAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSERIESAMPLVL, self).__init__(register,
            'IFADCLDOSERIESAMPLVL', 'RAC_NS.IFADCTRIM0.IFADCLDOSERIESAMPLVL', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1, self).__init__(register,
            'IFADCLDOSHUNTAMPLVL1', 'RAC_NS.IFADCTRIM0.IFADCLDOSHUNTAMPLVL1', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2, self).__init__(register,
            'IFADCLDOSHUNTAMPLVL2', 'RAC_NS.IFADCTRIM0.IFADCLDOSHUNTAMPLVL2', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTCURLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTCURLVL1, self).__init__(register,
            'IFADCLDOSHUNTCURLVL1', 'RAC_NS.IFADCTRIM0.IFADCLDOSHUNTCURLVL1', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTCURLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCLDOSHUNTCURLVL2, self).__init__(register,
            'IFADCLDOSHUNTCURLVL2', 'RAC_NS.IFADCTRIM0.IFADCLDOSHUNTCURLVL2', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCOTACURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCOTACURRENT, self).__init__(register,
            'IFADCOTACURRENT', 'RAC_NS.IFADCTRIM0.IFADCOTACURRENT', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCREFBUFAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCREFBUFAMPLVL, self).__init__(register,
            'IFADCREFBUFAMPLVL', 'RAC_NS.IFADCTRIM0.IFADCREFBUFAMPLVL', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCREFBUFCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCREFBUFCURLVL, self).__init__(register,
            'IFADCREFBUFCURLVL', 'RAC_NS.IFADCTRIM0.IFADCREFBUFCURLVL', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCSIDETONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCSIDETONEAMP, self).__init__(register,
            'IFADCSIDETONEAMP', 'RAC_NS.IFADCTRIM0.IFADCSIDETONEAMP', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCSIDETONEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCSIDETONEFREQ, self).__init__(register,
            'IFADCSIDETONEFREQ', 'RAC_NS.IFADCTRIM0.IFADCSIDETONEFREQ', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_IFADCENHALFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_IFADCENHALFMODE, self).__init__(register,
            'IFADCENHALFMODE', 'RAC_NS.IFADCTRIM0.IFADCENHALFMODE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_IFADCVCMLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_IFADCVCMLVL, self).__init__(register,
            'IFADCVCMLVL', 'RAC_NS.IFADCTRIM1.IFADCVCMLVL', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_IFADCENNEGRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_IFADCENNEGRES, self).__init__(register,
            'IFADCENNEGRES', 'RAC_NS.IFADCTRIM1.IFADCENNEGRES', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_IFADCNEGRESCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_IFADCNEGRESCURRENT, self).__init__(register,
            'IFADCNEGRESCURRENT', 'RAC_NS.IFADCTRIM1.IFADCNEGRESCURRENT', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_IFADCNEGRESVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_IFADCNEGRESVCM, self).__init__(register,
            'IFADCNEGRESVCM', 'RAC_NS.IFADCTRIM1.IFADCNEGRESVCM', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_IFADCENSUBGMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_IFADCENSUBGMODE, self).__init__(register,
            'IFADCENSUBGMODE', 'RAC_NS.IFADCTRIM1.IFADCENSUBGMODE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_IFADCTZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_IFADCTZ, self).__init__(register,
            'IFADCTZ', 'RAC_NS.IFADCTRIM1.IFADCTZ', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_IFADCENXOBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_IFADCENXOBYPASS, self).__init__(register,
            'IFADCENXOBYPASS', 'RAC_NS.IFADCTRIM1.IFADCENXOBYPASS', 'read-write',
            u"",
            13, 1)
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


class RM_Field_RAC_NS_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL, self).__init__(register,
            'IFADCRCCALCOUNTERSTARTVAL', 'RAC_NS.IFADCCAL.IFADCRCCALCOUNTERSTARTVAL', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCSTATUS_IFADCRCCALOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCSTATUS_IFADCRCCALOUT, self).__init__(register,
            'IFADCRCCALOUT', 'RAC_NS.IFADCSTATUS.IFADCRCCALOUT', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR0, self).__init__(register,
            'LNAMIXDISMXR0', 'RAC_NS.LNAMIXDEBUG.LNAMIXDISMXR0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXDEBUG_LNAMIXDISMXR1, self).__init__(register,
            'LNAMIXDISMXR1', 'RAC_NS.LNAMIXDEBUG.LNAMIXDISMXR1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXLNA0CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXLNA0CAPSEL, self).__init__(register,
            'LNAMIXLNA0CAPSEL', 'RAC_NS.LNAMIXTRIM0.LNAMIXLNA0CAPSEL', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXMXRBIAS0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXMXRBIAS0, self).__init__(register,
            'LNAMIXMXRBIAS0', 'RAC_NS.LNAMIXTRIM0.LNAMIXMXRBIAS0', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXVOUT0ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXVOUT0ADJ, self).__init__(register,
            'LNAMIXVOUT0ADJ', 'RAC_NS.LNAMIXTRIM0.LNAMIXVOUT0ADJ', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXLNA1CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXLNA1CAPSEL, self).__init__(register,
            'LNAMIXLNA1CAPSEL', 'RAC_NS.LNAMIXTRIM1.LNAMIXLNA1CAPSEL', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXMXRBIAS1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXMXRBIAS1, self).__init__(register,
            'LNAMIXMXRBIAS1', 'RAC_NS.LNAMIXTRIM1.LNAMIXMXRBIAS1', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXVOUT1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXVOUT1ADJ, self).__init__(register,
            'LNAMIXVOUT1ADJ', 'RAC_NS.LNAMIXTRIM1.LNAMIXVOUT1ADJ', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXCURCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXCURCTRL, self).__init__(register,
            'LNAMIXCURCTRL', 'RAC_NS.LNAMIXTRIM2.LNAMIXCURCTRL', 'read-write',
            u"",
            4, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXHIGHCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXHIGHCUR, self).__init__(register,
            'LNAMIXHIGHCUR', 'RAC_NS.LNAMIXTRIM2.LNAMIXHIGHCUR', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXLOWCUR, self).__init__(register,
            'LNAMIXLOWCUR', 'RAC_NS.LNAMIXTRIM2.LNAMIXLOWCUR', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXLNARESADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXLNARESADJ, self).__init__(register,
            'LNAMIXLNARESADJ', 'RAC_NS.LNAMIXTRIM2.LNAMIXLNARESADJ', 'read-write',
            u"",
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXNCASADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXNCASADJ, self).__init__(register,
            'LNAMIXNCASADJ', 'RAC_NS.LNAMIXTRIM2.LNAMIXNCASADJ', 'read-write',
            u"",
            17, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXPCASADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXPCASADJ, self).__init__(register,
            'LNAMIXPCASADJ', 'RAC_NS.LNAMIXTRIM2.LNAMIXPCASADJ', 'read-write',
            u"",
            19, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXTRIMVREG, self).__init__(register,
            'LNAMIXTRIMVREG', 'RAC_NS.LNAMIXTRIM2.LNAMIXTRIMVREG', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASADJN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASADJN, self).__init__(register,
            'LNAMIXIBIASADJN', 'RAC_NS.LNAMIXTRIM3.LNAMIXIBIASADJN', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASADJP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASADJP, self).__init__(register,
            'LNAMIXIBIASADJP', 'RAC_NS.LNAMIXTRIM3.LNAMIXIBIASADJP', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASRANGEADJN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASRANGEADJN, self).__init__(register,
            'LNAMIXIBIASRANGEADJN', 'RAC_NS.LNAMIXTRIM3.LNAMIXIBIASRANGEADJN', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASRANGEADJP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXIBIASRANGEADJP, self).__init__(register,
            'LNAMIXIBIASRANGEADJP', 'RAC_NS.LNAMIXTRIM3.LNAMIXIBIASRANGEADJP', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDBWSEL, self).__init__(register,
            'LNAMIXRFPKDBWSEL', 'RAC_NS.LNAMIXTRIM4.LNAMIXRFPKDBWSEL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO, self).__init__(register,
            'LNAMIXRFPKDCALCMLO', 'RAC_NS.LNAMIXTRIM4.LNAMIXRFPKDCALCMLO', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI, self).__init__(register,
            'LNAMIXRFPKDCALCMHI', 'RAC_NS.LNAMIXTRIM4.LNAMIXRFPKDCALCMHI', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELLO', 'RAC_NS.LNAMIXTRIM4.LNAMIXRFPKDTHRESHSELLO', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELHI', 'RAC_NS.LNAMIXTRIM4.LNAMIXRFPKDTHRESHSELHI', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALPMOSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALPMOSEN, self).__init__(register,
            'LNAMIXCALPMOSEN', 'RAC_NS.LNAMIXCAL.LNAMIXCALPMOSEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALNMOSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALNMOSEN, self).__init__(register,
            'LNAMIXCALNMOSEN', 'RAC_NS.LNAMIXCAL.LNAMIXCALNMOSEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALVMODE, self).__init__(register,
            'LNAMIXCALVMODE', 'RAC_NS.LNAMIXCAL.LNAMIXCALVMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL0, self).__init__(register,
            'LNAMIXENIRCAL0', 'RAC_NS.LNAMIXCAL.LNAMIXENIRCAL0', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXENIRCAL1, self).__init__(register,
            'LNAMIXENIRCAL1', 'RAC_NS.LNAMIXCAL.LNAMIXENIRCAL1', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL0AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL0AMP, self).__init__(register,
            'LNAMIXIRCAL0AMP', 'RAC_NS.LNAMIXCAL.LNAMIXIRCAL0AMP', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL1AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL1AMP, self).__init__(register,
            'LNAMIXIRCAL1AMP', 'RAC_NS.LNAMIXCAL.LNAMIXIRCAL1AMP', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXEN_LNAMIXENAMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXEN_LNAMIXENAMP0, self).__init__(register,
            'LNAMIXENAMP0', 'RAC_NS.LNAMIXEN.LNAMIXENAMP0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXEN_LNAMIXENAMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXEN_LNAMIXENAMP1, self).__init__(register,
            'LNAMIXENAMP1', 'RAC_NS.LNAMIXEN.LNAMIXENAMP1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXEN_LNAMIXENBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXEN_LNAMIXENBIAS, self).__init__(register,
            'LNAMIXENBIAS', 'RAC_NS.LNAMIXEN.LNAMIXENBIAS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXEN_LNAMIXENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXEN_LNAMIXENLDO, self).__init__(register,
            'LNAMIXENLDO', 'RAC_NS.LNAMIXEN.LNAMIXENLDO', 'read-write',
            u"",
            3, 1)
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


class RM_Field_RAC_NS_PATRIM0_TXTRIMLPAVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_TXTRIMLPAVMID, self).__init__(register,
            'TXTRIMLPAVMID', 'RAC_NS.PATRIM0.TXTRIMLPAVMID', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_TXTRIMXPAVNB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_TXTRIMXPAVNB, self).__init__(register,
            'TXTRIMXPAVNB', 'RAC_NS.PATRIM1.TXTRIMXPAVNB', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_TXTRIMXPAVPB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_TXTRIMXPAVPB, self).__init__(register,
            'TXTRIMXPAVPB', 'RAC_NS.PATRIM1.TXTRIMXPAVPB', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVMID, self).__init__(register,
            'TXTRIMHPAVMID', 'RAC_NS.PATRIM1.TXTRIMHPAVMID', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVNCAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVNCAS, self).__init__(register,
            'TXTRIMHPAVNCAS', 'RAC_NS.PATRIM1.TXTRIMHPAVNCAS', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVPCAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM1_TXTRIMHPAVPCAS, self).__init__(register,
            'TXTRIMHPAVPCAS', 'RAC_NS.PATRIM1.TXTRIMHPAVPCAS', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENDUTYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENDUTYN, self).__init__(register,
            'TXTRIMCLKGENDUTYN', 'RAC_NS.PATRIM2.TXTRIMCLKGENDUTYN', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENDUTYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENDUTYP, self).__init__(register,
            'TXTRIMCLKGENDUTYP', 'RAC_NS.PATRIM2.TXTRIMCLKGENDUTYP', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENNOVFALL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENNOVFALL, self).__init__(register,
            'TXTRIMCLKGENNOVFALL', 'RAC_NS.PATRIM2.TXTRIMCLKGENNOVFALL', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENNOVRISE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_TXTRIMCLKGENNOVRISE, self).__init__(register,
            'TXTRIMCLKGENNOVRISE', 'RAC_NS.PATRIM2.TXTRIMCLKGENNOVRISE', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGENN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGENN, self).__init__(register,
            'TXTRIMDRVEDGENN', 'RAC_NS.PATRIM2.TXTRIMDRVEDGENN', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGENP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGENP, self).__init__(register,
            'TXTRIMDRVEDGENP', 'RAC_NS.PATRIM2.TXTRIMDRVEDGENP', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGEPN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGEPN, self).__init__(register,
            'TXTRIMDRVEDGEPN', 'RAC_NS.PATRIM2.TXTRIMDRVEDGEPN', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGEPP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM2_TXTRIMDRVEDGEPP, self).__init__(register,
            'TXTRIMDRVEDGEPP', 'RAC_NS.PATRIM2.TXTRIMDRVEDGEPP', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMDREGBLEED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMDREGBLEED, self).__init__(register,
            'TXTRIMDREGBLEED', 'RAC_NS.PATRIM3.TXTRIMDREGBLEED', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMDREGBLEEDAUTO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMDREGBLEEDAUTO, self).__init__(register,
            'TXTRIMDREGBLEEDAUTO', 'RAC_NS.PATRIM3.TXTRIMDREGBLEEDAUTO', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMOREGBLEEDAUTO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMOREGBLEEDAUTO, self).__init__(register,
            'TXTRIMOREGBLEEDAUTO', 'RAC_NS.PATRIM3.TXTRIMOREGBLEEDAUTO', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMDREGFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMDREGFB, self).__init__(register,
            'TXTRIMDREGFB', 'RAC_NS.PATRIM3.TXTRIMDREGFB', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMOREGFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMOREGFB, self).__init__(register,
            'TXTRIMOREGFB', 'RAC_NS.PATRIM3.TXTRIMOREGFB', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMDREG, self).__init__(register,
            'TXTRIMDREG', 'RAC_NS.PATRIM3.TXTRIMDREG', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMOREG, self).__init__(register,
            'TXTRIMOREG', 'RAC_NS.PATRIM3.TXTRIMOREG', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMRREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMRREG, self).__init__(register,
            'TXTRIMRREG', 'RAC_NS.PATRIM3.TXTRIMRREG', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMDREGPSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMDREGPSR, self).__init__(register,
            'TXTRIMDREGPSR', 'RAC_NS.PATRIM3.TXTRIMDREGPSR', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMOREGPSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMOREGPSR, self).__init__(register,
            'TXTRIMOREGPSR', 'RAC_NS.PATRIM3.TXTRIMOREGPSR', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMDREGSLICES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMDREGSLICES, self).__init__(register,
            'TXTRIMDREGSLICES', 'RAC_NS.PATRIM3.TXTRIMDREGSLICES', 'read-write',
            u"",
            23, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMOREGSLICES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMOREGSLICES, self).__init__(register,
            'TXTRIMOREGSLICES', 'RAC_NS.PATRIM3.TXTRIMOREGSLICES', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMDREGMOREBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMDREGMOREBW, self).__init__(register,
            'TXTRIMDREGMOREBW', 'RAC_NS.PATRIM3.TXTRIMDREGMOREBW', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM3_TXTRIMOREGMOREBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM3_TXTRIMOREGMOREBW, self).__init__(register,
            'TXTRIMOREGMOREBW', 'RAC_NS.PATRIM3.TXTRIMOREGMOREBW', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVNBDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVNBDRV, self).__init__(register,
            'TXTRIMXPAVNBDRV', 'RAC_NS.PATRIM4.TXTRIMXPAVNBDRV', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVPBDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVPBDRV, self).__init__(register,
            'TXTRIMXPAVPBDRV', 'RAC_NS.PATRIM4.TXTRIMXPAVPBDRV', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVXSCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXTRIMXPAVXSCURRENT, self).__init__(register,
            'TXTRIMXPAVXSCURRENT', 'RAC_NS.PATRIM4.TXTRIMXPAVXSCURRENT', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTCOARSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTCOARSE, self).__init__(register,
            'TXXPAVXSCURRENTCOARSE', 'RAC_NS.PATRIM4.TXXPAVXSCURRENTCOARSE', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTCOARSEMIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTCOARSEMIN, self).__init__(register,
            'TXXPAVXSCURRENTCOARSEMIN', 'RAC_NS.PATRIM4.TXXPAVXSCURRENTCOARSEMIN', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTFINE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTFINE, self).__init__(register,
            'TXXPAVXSCURRENTFINE', 'RAC_NS.PATRIM4.TXXPAVXSCURRENTFINE', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTSELHPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXXPAVXSCURRENTSELHPA, self).__init__(register,
            'TXXPAVXSCURRENTSELHPA', 'RAC_NS.PATRIM4.TXXPAVXSCURRENTSELHPA', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXVXSCURRENTVREFN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXVXSCURRENTVREFN, self).__init__(register,
            'TXVXSCURRENTVREFN', 'RAC_NS.PATRIM4.TXVXSCURRENTVREFN', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM4_TXVXSCURRENTVREFP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM4_TXVXSCURRENTVREFP, self).__init__(register,
            'TXVXSCURRENTVREFP', 'RAC_NS.PATRIM4.TXVXSCURRENTVREFP', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM5_TXVNSRAIL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM5_TXVNSRAIL, self).__init__(register,
            'TXVNSRAIL', 'RAC_NS.PATRIM5.TXVNSRAIL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM5_TXVPSRAIL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM5_TXVPSRAIL, self).__init__(register,
            'TXVPSRAIL', 'RAC_NS.PATRIM5.TXVPSRAIL', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM5_TXTRIMXPAVNS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM5_TXTRIMXPAVNS, self).__init__(register,
            'TXTRIMXPAVNS', 'RAC_NS.PATRIM5.TXTRIMXPAVNS', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM5_TXTRIMXPAVPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM5_TXTRIMXPAVPS, self).__init__(register,
            'TXTRIMXPAVPS', 'RAC_NS.PATRIM5.TXTRIMXPAVPS', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PADEBUG0_TXOREGBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PADEBUG0_TXOREGBYPASS, self).__init__(register,
            'TXOREGBYPASS', 'RAC_NS.PADEBUG0.TXOREGBYPASS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PADEBUG0_TXDREGBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PADEBUG0_TXDREGBYPASS, self).__init__(register,
            'TXDREGBYPASS', 'RAC_NS.PADEBUG0.TXDREGBYPASS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PADEBUG0_TXRREGBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PADEBUG0_TXRREGBYPASS, self).__init__(register,
            'TXRREGBYPASS', 'RAC_NS.PADEBUG0.TXRREGBYPASS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PADEBUG0_TXPDNVDDPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PADEBUG0_TXPDNVDDPA, self).__init__(register,
            'TXPDNVDDPA', 'RAC_NS.PADEBUG0.TXPDNVDDPA', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXPOWER_TXSTRIPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXPOWER_TXSTRIPE, self).__init__(register,
            'TXSTRIPE', 'RAC_NS.TXPOWER.TXSTRIPE', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXPOWER_TXSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXPOWER_TXSLICE, self).__init__(register,
            'TXSLICE', 'RAC_NS.TXPOWER.TXSLICE', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXPOWER_TXDRVSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXPOWER_TXDRVSLICE, self).__init__(register,
            'TXDRVSLICE', 'RAC_NS.TXPOWER.TXDRVSLICE', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXPOWER_TXANARAMPODEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXPOWER_TXANARAMPODEV, self).__init__(register,
            'TXANARAMPODEV', 'RAC_NS.TXPOWER.TXANARAMPODEV', 'read-write',
            u"",
            13, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXPOWER_TXANARAMPDRVFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXPOWER_TXANARAMPDRVFF, self).__init__(register,
            'TXANARAMPDRVFF', 'RAC_NS.TXPOWER.TXANARAMPDRVFF', 'read-write',
            u"",
            18, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXANARAMPDRVBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXANARAMPDRVBW, self).__init__(register,
            'TXANARAMPDRVBW', 'RAC_NS.TXRAMP.TXANARAMPDRVBW', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXANARAMPDRVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXANARAMPDRVEN, self).__init__(register,
            'TXANARAMPDRVEN', 'RAC_NS.TXRAMP.TXANARAMPDRVEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXANARAMPODEVBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXANARAMPODEVBW, self).__init__(register,
            'TXANARAMPODEVBW', 'RAC_NS.TXRAMP.TXANARAMPODEVBW', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXANARAMPODEVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXANARAMPODEVEN, self).__init__(register,
            'TXANARAMPODEVEN', 'RAC_NS.TXRAMP.TXANARAMPODEVEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXBYPASSRAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXBYPASSRAMPCLK, self).__init__(register,
            'TXBYPASSRAMPCLK', 'RAC_NS.TXRAMP.TXBYPASSRAMPCLK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXMODEPHASEFLIP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXMODEPHASEFLIP, self).__init__(register,
            'TXMODEPHASEFLIP', 'RAC_NS.TXRAMP.TXMODEPHASEFLIP', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXPHASEDIGITAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXPHASEDIGITAL, self).__init__(register,
            'TXPHASEDIGITAL', 'RAC_NS.TXRAMP.TXPHASEDIGITAL', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXRESETPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXRESETPAPOWER, self).__init__(register,
            'TXRESETPAPOWER', 'RAC_NS.TXRAMP.TXRESETPAPOWER', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_TXUNMUTEENDRVFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_TXUNMUTEENDRVFF, self).__init__(register,
            'TXUNMUTEENDRVFF', 'RAC_NS.TXRAMP.TXUNMUTEENDRVFF', 'read-write',
            u"",
            10, 1)
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


class RM_Field_RAC_NS_RFPATHEN0_LNAMIXEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_LNAMIXEN0, self).__init__(register,
            'LNAMIXEN0', 'RAC_NS.RFPATHEN0.LNAMIXEN0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFATTDCEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFATTDCEN0, self).__init__(register,
            'LNAMIXRFATTDCEN0', 'RAC_NS.RFPATHEN0.LNAMIXRFATTDCEN0', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFPKDENRF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFPKDENRF0, self).__init__(register,
            'LNAMIXRFPKDENRF0', 'RAC_NS.RFPATHEN0.LNAMIXRFPKDENRF0', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN0_SYLODIVRLO0SUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_SYLODIVRLO0SUBGEN, self).__init__(register,
            'SYLODIVRLO0SUBGEN', 'RAC_NS.RFPATHEN0.SYLODIVRLO0SUBGEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN0_TXENHPA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_TXENHPA0, self).__init__(register,
            'TXENHPA0', 'RAC_NS.RFPATHEN0.TXENHPA0', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN0_TXENLPA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_TXENLPA0, self).__init__(register,
            'TXENLPA0', 'RAC_NS.RFPATHEN0.TXENLPA0', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN0_TXENVMIDHPA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_TXENVMIDHPA0, self).__init__(register,
            'TXENVMIDHPA0', 'RAC_NS.RFPATHEN0.TXENVMIDHPA0', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN0_TXENVMIDLPA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_TXENVMIDLPA0, self).__init__(register,
            'TXENVMIDLPA0', 'RAC_NS.RFPATHEN0.TXENVMIDLPA0', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN1, self).__init__(register,
            'LNAMIXEN1', 'RAC_NS.RFPATHEN1.LNAMIXEN1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFATTDCEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFATTDCEN1, self).__init__(register,
            'LNAMIXRFATTDCEN1', 'RAC_NS.RFPATHEN1.LNAMIXRFATTDCEN1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFPKDENRF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFPKDENRF1, self).__init__(register,
            'LNAMIXRFPKDENRF1', 'RAC_NS.RFPATHEN1.LNAMIXRFPKDENRF1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_SYLODIVRLO1SUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_SYLODIVRLO1SUBGEN, self).__init__(register,
            'SYLODIVRLO1SUBGEN', 'RAC_NS.RFPATHEN1.SYLODIVRLO1SUBGEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_TXENHPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_TXENHPA1, self).__init__(register,
            'TXENHPA1', 'RAC_NS.RFPATHEN1.TXENHPA1', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_TXENLPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_TXENLPA1, self).__init__(register,
            'TXENLPA1', 'RAC_NS.RFPATHEN1.TXENLPA1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_TXENVMIDHPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_TXENVMIDHPA1, self).__init__(register,
            'TXENVMIDHPA1', 'RAC_NS.RFPATHEN1.TXENVMIDHPA1', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_TXENVMIDLPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_TXENVMIDLPA1, self).__init__(register,
            'TXENVMIDLPA1', 'RAC_NS.RFPATHEN1.TXENVMIDLPA1', 'read-write',
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


class RM_Field_RAC_NS_RX_LNAMIXENRFPKDLOTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXENRFPKDLOTHRESH, self).__init__(register,
            'LNAMIXENRFPKDLOTHRESH', 'RAC_NS.RX.LNAMIXENRFPKDLOTHRESH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXLDOLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXLDOLOWCUR, self).__init__(register,
            'LNAMIXLDOLOWCUR', 'RAC_NS.RX.LNAMIXLDOLOWCUR', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXREGLOADEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXREGLOADEN, self).__init__(register,
            'LNAMIXREGLOADEN', 'RAC_NS.RX.LNAMIXREGLOADEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_PGAENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_PGAENLDO, self).__init__(register,
            'PGAENLDO', 'RAC_NS.RX.PGAENLDO', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYCHPQNC3EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYCHPQNC3EN, self).__init__(register,
            'SYCHPQNC3EN', 'RAC_NS.RX.SYCHPQNC3EN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYCHPBIASTRIMBUFRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYCHPBIASTRIMBUFRX, self).__init__(register,
            'SYCHPBIASTRIMBUFRX', 'RAC_NS.RX.SYCHPBIASTRIMBUFRX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYPFDCHPLPENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYPFDCHPLPENRX, self).__init__(register,
            'SYPFDCHPLPENRX', 'RAC_NS.RX.SYPFDCHPLPENRX', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYPFDFPWENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYPFDFPWENRX, self).__init__(register,
            'SYPFDFPWENRX', 'RAC_NS.RX.SYPFDFPWENRX', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_SYVCOVCAPFASTRAMPRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_SYVCOVCAPFASTRAMPRX, self).__init__(register,
            'SYVCOVCAPFASTRAMPRX', 'RAC_NS.RX.SYVCOVCAPFASTRAMPRX', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENDREG, self).__init__(register,
            'TXENDREG', 'RAC_NS.TX.TXENDREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENOREG, self).__init__(register,
            'TXENOREG', 'RAC_NS.TX.TXENOREG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENOREGBLEED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENOREGBLEED, self).__init__(register,
            'TXENOREGBLEED', 'RAC_NS.TX.TXENOREGBLEED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENRREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENRREG, self).__init__(register,
            'TXENRREG', 'RAC_NS.TX.TXENRREG', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENCLKGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENCLKGEN, self).__init__(register,
            'TXENCLKGEN', 'RAC_NS.TX.TXENCLKGEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENPADDCFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENPADDCFORCE, self).__init__(register,
            'TXENPADDCFORCE', 'RAC_NS.TX.TXENPADDCFORCE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENPKDOGND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENPKDOGND, self).__init__(register,
            'TXENPKDOGND', 'RAC_NS.TX.TXENPKDOGND', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENPKDOGNDCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENPKDOGNDCLK, self).__init__(register,
            'TXENPKDOGNDCLK', 'RAC_NS.TX.TXENPKDOGNDCLK', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENPUPDNPROTECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENPUPDNPROTECT, self).__init__(register,
            'TXENPUPDNPROTECT', 'RAC_NS.TX.TXENPUPDNPROTECT', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENRAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENRAMPCLK, self).__init__(register,
            'TXENRAMPCLK', 'RAC_NS.TX.TXENRAMPCLK', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENVTRCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENVTRCURRENT, self).__init__(register,
            'TXENVTRCURRENT', 'RAC_NS.TX.TXENVTRCURRENT', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXENXDRVVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXENXDRVVMID, self).__init__(register,
            'TXENXDRVVMID', 'RAC_NS.TX.TXENXDRVVMID', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXMODEPMOSOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXMODEPMOSOFF, self).__init__(register,
            'TXMODEPMOSOFF', 'RAC_NS.TX.TXMODEPMOSOFF', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_TXMODESE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_TXMODESE, self).__init__(register,
            'TXMODESE', 'RAC_NS.TX.TXMODESE', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_SYCHPBIASTRIMBUFTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_SYCHPBIASTRIMBUFTX, self).__init__(register,
            'SYCHPBIASTRIMBUFTX', 'RAC_NS.TX.SYCHPBIASTRIMBUFTX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_SYPFDCHPLPENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_SYPFDCHPLPENTX, self).__init__(register,
            'SYPFDCHPLPENTX', 'RAC_NS.TX.SYPFDCHPLPENTX', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_SYPFDFPWENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_SYPFDFPWENTX, self).__init__(register,
            'SYPFDFPWENTX', 'RAC_NS.TX.SYPFDFPWENTX', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_SYVCOVCAPFASTRAMPTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_SYVCOVCAPFASTRAMPTX, self).__init__(register,
            'SYVCOVCAPFASTRAMPTX', 'RAC_NS.TX.SYVCOVCAPFASTRAMPTX', 'read-write',
            u"",
            19, 1)
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


class RM_Field_RAC_NS_SYTRIM0_SYCHPCURRRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPCURRRX, self).__init__(register,
            'SYCHPCURRRX', 'RAC_NS.SYTRIM0.SYCHPCURRRX', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPCURRTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPCURRTX, self).__init__(register,
            'SYCHPCURRTX', 'RAC_NS.SYTRIM0.SYCHPCURRTX', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPLEVNSRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPLEVNSRC, self).__init__(register,
            'SYCHPLEVNSRC', 'RAC_NS.SYTRIM0.SYCHPLEVNSRC', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPLEVPSRCRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPLEVPSRCRX, self).__init__(register,
            'SYCHPLEVPSRCRX', 'RAC_NS.SYTRIM0.SYCHPLEVPSRCRX', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPLEVPSRCTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPLEVPSRCTX, self).__init__(register,
            'SYCHPLEVPSRCTX', 'RAC_NS.SYTRIM0.SYCHPLEVPSRCTX', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPSRCENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPSRCENRX, self).__init__(register,
            'SYCHPSRCENRX', 'RAC_NS.SYTRIM0.SYCHPSRCENRX', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPSRCENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPSRCENTX, self).__init__(register,
            'SYCHPSRCENTX', 'RAC_NS.SYTRIM0.SYCHPSRCENTX', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYCHPREPLICACURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYCHPREPLICACURRADJ, self).__init__(register,
            'SYCHPREPLICACURRADJ', 'RAC_NS.SYTRIM0.SYCHPREPLICACURRADJ', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBIAS, self).__init__(register,
            'SYTRIMCHPREGAMPBIAS', 'RAC_NS.SYTRIM0.SYTRIMCHPREGAMPBIAS', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYTRIMCHPREGAMPBW, self).__init__(register,
            'SYTRIMCHPREGAMPBW', 'RAC_NS.SYTRIM0.SYTRIMCHPREGAMPBW', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMCORERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMCORERX, self).__init__(register,
            'SYLODIVLDOTRIMCORERX', 'RAC_NS.SYTRIM1.SYLODIVLDOTRIMCORERX', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMCORETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMCORETX, self).__init__(register,
            'SYLODIVLDOTRIMCORETX', 'RAC_NS.SYTRIM1.SYLODIVLDOTRIMCORETX', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMNDIORX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMNDIORX, self).__init__(register,
            'SYLODIVLDOTRIMNDIORX', 'RAC_NS.SYTRIM1.SYLODIVLDOTRIMNDIORX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMNDIOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYLODIVLDOTRIMNDIOTX, self).__init__(register,
            'SYLODIVLDOTRIMNDIOTX', 'RAC_NS.SYTRIM1.SYLODIVLDOTRIMNDIOTX', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYLODIVSELOUTINVADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYLODIVSELOUTINVADC, self).__init__(register,
            'SYLODIVSELOUTINVADC', 'RAC_NS.SYTRIM1.SYLODIVSELOUTINVADC', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYLODIVTLOTRIMDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYLODIVTLOTRIMDELAY, self).__init__(register,
            'SYLODIVTLOTRIMDELAY', 'RAC_NS.SYTRIM1.SYLODIVTLOTRIMDELAY', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA1CURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA1CURRADJ, self).__init__(register,
            'SYMMDREPLICA1CURRADJ', 'RAC_NS.SYTRIM1.SYMMDREPLICA1CURRADJ', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA2CURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYMMDREPLICA2CURRADJ, self).__init__(register,
            'SYMMDREPLICA2CURRADJ', 'RAC_NS.SYTRIM1.SYMMDREPLICA2CURRADJ', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBIAS, self).__init__(register,
            'SYTRIMMMDREGAMPBIAS', 'RAC_NS.SYTRIM1.SYTRIMMMDREGAMPBIAS', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTRIMMMDREGAMPBW, self).__init__(register,
            'SYTRIMMMDREGAMPBW', 'RAC_NS.SYTRIM1.SYTRIMMMDREGAMPBW', 'read-write',
            u"",
            30, 2)
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


class RM_Field_RAC_NS_SYEN_SYCHPLPENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYCHPLPENRX, self).__init__(register,
            'SYCHPLPENRX', 'RAC_NS.SYEN.SYCHPLPENRX', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYCHPLPENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYCHPLPENTX, self).__init__(register,
            'SYCHPLPENTX', 'RAC_NS.SYEN.SYCHPLPENTX', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENCHPREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENCHPREG, self).__init__(register,
            'SYENCHPREG', 'RAC_NS.SYEN.SYENCHPREG', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENCHPREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENCHPREPLICA, self).__init__(register,
            'SYENCHPREPLICA', 'RAC_NS.SYEN.SYENCHPREPLICA', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENMMDREG, self).__init__(register,
            'SYENMMDREG', 'RAC_NS.SYEN.SYENMMDREG', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENMMDREPLICA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENMMDREPLICA1, self).__init__(register,
            'SYENMMDREPLICA1', 'RAC_NS.SYEN.SYENMMDREPLICA1', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENMMDREPLICA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENMMDREPLICA2, self).__init__(register,
            'SYENMMDREPLICA2', 'RAC_NS.SYEN.SYENMMDREPLICA2', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOBIAS, self).__init__(register,
            'SYENVCOBIAS', 'RAC_NS.SYEN.SYENVCOBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOPFET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOPFET, self).__init__(register,
            'SYENVCOPFET', 'RAC_NS.SYEN.SYENVCOPFET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOREG, self).__init__(register,
            'SYENVCOREG', 'RAC_NS.SYEN.SYENVCOREG', 'read-write',
            u"",
            10, 1)
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


class RM_Field_RAC_NS_SYLOEN_SYLODIVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVEN, self).__init__(register,
            'SYLODIVEN', 'RAC_NS.SYLOEN.SYLODIVEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVLDOBIASEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVLDOBIASEN, self).__init__(register,
            'SYLODIVLDOBIASEN', 'RAC_NS.SYLOEN.SYLODIVLDOBIASEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVLDOEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVLDOEN, self).__init__(register,
            'SYLODIVLDOEN', 'RAC_NS.SYLOEN.SYLODIVLDOEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVRLOSUBGRADCCLKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVRLOSUBGRADCCLKEN, self).__init__(register,
            'SYLODIVRLOSUBGRADCCLKEN', 'RAC_NS.SYLOEN.SYLODIVRLOSUBGRADCCLKEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVSMUXDIVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVSMUXDIVEN, self).__init__(register,
            'SYLODIVSMUXDIVEN', 'RAC_NS.SYLOEN.SYLODIVSMUXDIVEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLOSUBGAUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLOSUBGAUXEN, self).__init__(register,
            'SYLODIVTLOSUBGAUXEN', 'RAC_NS.SYLOEN.SYLODIVTLOSUBGAUXEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYLODIVTLOSUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYLODIVTLOSUBGEN, self).__init__(register,
            'SYLODIVTLOSUBGEN', 'RAC_NS.SYLOEN.SYLODIVTLOSUBGEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYMMDCTRL_SYMMDDIVRSDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYMMDCTRL_SYMMDDIVRSDIG, self).__init__(register,
            'SYMMDDIVRSDIG', 'RAC_NS.SYMMDCTRL.SYMMDDIVRSDIG', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYMMDCTRL_SYMMDMODERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYMMDCTRL_SYMMDMODERX, self).__init__(register,
            'SYMMDMODERX', 'RAC_NS.SYMMDCTRL.SYMMDMODERX', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYMMDCTRL_SYMMDMODETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYMMDCTRL_SYMMDMODETX, self).__init__(register,
            'SYMMDMODETX', 'RAC_NS.SYMMDCTRL.SYMMDMODETX', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDIVCTRL_SYLODIVRADCDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDIVCTRL_SYLODIVRADCDIV, self).__init__(register,
            'SYLODIVRADCDIV', 'RAC_NS.SYDIVCTRL.SYLODIVRADCDIV', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDIVCTRL_SYLODIVSMUXDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDIVCTRL_SYLODIVSMUXDIV, self).__init__(register,
            'SYLODIVSMUXDIV', 'RAC_NS.SYDIVCTRL.SYLODIVSMUXDIV', 'read-write',
            u"",
            16, 2)
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


class RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXRFATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXRFATT, self).__init__(register,
            'ENMANLNAMIXRFATT', 'RAC_NS.AGCOVERWRITE0.ENMANLNAMIXRFATT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXSLICE, self).__init__(register,
            'ENMANLNAMIXSLICE', 'RAC_NS.AGCOVERWRITE0.ENMANLNAMIXSLICE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_ENMANPGAGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_ENMANPGAGAIN, self).__init__(register,
            'ENMANPGAGAIN', 'RAC_NS.AGCOVERWRITE0.ENMANPGAGAIN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_ENMANIFADCSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_ENMANIFADCSCALE, self).__init__(register,
            'ENMANIFADCSCALE', 'RAC_NS.AGCOVERWRITE0.ENMANIFADCSCALE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXSLICE0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXSLICE0, self).__init__(register,
            'MANLNAMIXSLICE0', 'RAC_NS.AGCOVERWRITE0.MANLNAMIXSLICE0', 'read-write',
            u"",
            4, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXSLICE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXSLICE1, self).__init__(register,
            'MANLNAMIXSLICE1', 'RAC_NS.AGCOVERWRITE0.MANLNAMIXSLICE1', 'read-write',
            u"",
            10, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_MANPGAGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_MANPGAGAIN, self).__init__(register,
            'MANPGAGAIN', 'RAC_NS.AGCOVERWRITE0.MANPGAGAIN', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_MANIFADCSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_MANIFADCSCALE, self).__init__(register,
            'MANIFADCSCALE', 'RAC_NS.AGCOVERWRITE0.MANIFADCSCALE', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE1_MANLNAMIXRFATT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE1_MANLNAMIXRFATT0, self).__init__(register,
            'MANLNAMIXRFATT0', 'RAC_NS.AGCOVERWRITE1.MANLNAMIXRFATT0', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE1_MANLNAMIXRFATT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE1_MANLNAMIXRFATT1, self).__init__(register,
            'MANLNAMIXRFATT1', 'RAC_NS.AGCOVERWRITE1.MANLNAMIXRFATT1', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLINNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLINNIBBLE, self).__init__(register,
            'IFADCPLLINNIBBLE', 'RAC_NS.IFADCPLLCTRL.IFADCPLLINNIBBLE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDCNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDCNIB, self).__init__(register,
            'IFADCPLLLDCNIB', 'RAC_NS.IFADCPLLCTRL.IFADCPLLLDCNIB', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDFNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDFNIB, self).__init__(register,
            'IFADCPLLLDFNIB', 'RAC_NS.IFADCPLLCTRL.IFADCPLLLDFNIB', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDMNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLLDMNIB, self).__init__(register,
            'IFADCPLLLDMNIB', 'RAC_NS.IFADCPLLCTRL.IFADCPLLLDMNIB', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLRDNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLCTRL_IFADCPLLRDNIBBLE, self).__init__(register,
            'IFADCPLLRDNIBBLE', 'RAC_NS.IFADCPLLCTRL.IFADCPLLRDNIBBLE', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOBBCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOBBCAL, self).__init__(register,
            'IFADCPLLDCOBBCAL', 'RAC_NS.IFADCPLLDCO.IFADCPLLDCOBBCAL', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOTEMPADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOTEMPADJ, self).__init__(register,
            'IFADCPLLDCOTEMPADJ', 'RAC_NS.IFADCPLLDCO.IFADCPLLDCOTEMPADJ', 'read-write',
            u"",
            3, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOBIASHALF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOBIASHALF, self).__init__(register,
            'IFADCPLLDCOBIASHALF', 'RAC_NS.IFADCPLLDCO.IFADCPLLDCOBIASHALF', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOENABLE, self).__init__(register,
            'IFADCPLLDCOENABLE', 'RAC_NS.IFADCPLLDCO.IFADCPLLDCOENABLE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOFILTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOFILTER, self).__init__(register,
            'IFADCPLLDCOFILTER', 'RAC_NS.IFADCPLLDCO.IFADCPLLDCOFILTER', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOFULLRATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOFULLRATE, self).__init__(register,
            'IFADCPLLDCOFULLRATE', 'RAC_NS.IFADCPLLDCO.IFADCPLLDCOFULLRATE', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOMSBCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLDCO_IFADCPLLDCOMSBCURRENT, self).__init__(register,
            'IFADCPLLDCOMSBCURRENT', 'RAC_NS.IFADCPLLDCO.IFADCPLLDCOMSBCURRENT', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBDET, self).__init__(register,
            'IFADCPLLENBBDET', 'RAC_NS.IFADCPLLEN.IFADCPLLENBBDET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBXLDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBXLDET, self).__init__(register,
            'IFADCPLLENBBXLDET', 'RAC_NS.IFADCPLLEN.IFADCPLLENBBXLDET', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBXMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENBBXMDET, self).__init__(register,
            'IFADCPLLENBBXMDET', 'RAC_NS.IFADCPLLEN.IFADCPLLENBBXMDET', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENCFDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENCFDET, self).__init__(register,
            'IFADCPLLENCFDET', 'RAC_NS.IFADCPLLEN.IFADCPLLENCFDET', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENROTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENROTDET, self).__init__(register,
            'IFADCPLLENROTDET', 'RAC_NS.IFADCPLLEN.IFADCPLLENROTDET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLSERIEREGENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLSERIEREGENABLE, self).__init__(register,
            'IFADCPLLSERIEREGENABLE', 'RAC_NS.IFADCPLLEN.IFADCPLLSERIEREGENABLE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLSHUNTREGENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLSHUNTREGENABLE, self).__init__(register,
            'IFADCPLLSHUNTREGENABLE', 'RAC_NS.IFADCPLLEN.IFADCPLLSHUNTREGENABLE', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENREFBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENREFBUF, self).__init__(register,
            'IFADCPLLENREFBUF', 'RAC_NS.IFADCPLLEN.IFADCPLLENREFBUF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENXOBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLEN_IFADCPLLENXOBYP, self).__init__(register,
            'IFADCPLLENXOBYP', 'RAC_NS.IFADCPLLEN.IFADCPLLENXOBYP', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSERIEREGFILTER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSERIEREGFILTER, self).__init__(register,
            'IFADCPLLSERIEREGFILTER', 'RAC_NS.IFADCPLLREG.IFADCPLLSERIEREGFILTER', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSERIEREGVCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSERIEREGVCTRL, self).__init__(register,
            'IFADCPLLSERIEREGVCTRL', 'RAC_NS.IFADCPLLREG.IFADCPLLSERIEREGVCTRL', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSHUNTREGICTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSHUNTREGICTRL, self).__init__(register,
            'IFADCPLLSHUNTREGICTRL', 'RAC_NS.IFADCPLLREG.IFADCPLLSHUNTREGICTRL', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSHUNTREGVCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLREG_IFADCPLLSHUNTREGVCTRL, self).__init__(register,
            'IFADCPLLSHUNTREGVCTRL', 'RAC_NS.IFADCPLLREG.IFADCPLLSHUNTREGVCTRL', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCPLLOUTSTATUS_IFADCPLLOUTNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCPLLOUTSTATUS_IFADCPLLOUTNIBBLE, self).__init__(register,
            'IFADCPLLOUTNIBBLE', 'RAC_NS.IFADCPLLOUTSTATUS.IFADCPLLOUTNIBBLE', 'read-only',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDTHRESH, self).__init__(register,
            'TXPKDOGNDTHRESH', 'RAC_NS.TXOGNDPKD.TXPKDOGNDTHRESH', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDBYPASSLATCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDBYPASSLATCH, self).__init__(register,
            'TXPKDOGNDBYPASSLATCH', 'RAC_NS.TXOGNDPKD.TXPKDOGNDBYPASSLATCH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDTYPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDTYPE, self).__init__(register,
            'TXPKDOGNDTYPE', 'RAC_NS.TXOGNDPKD.TXPKDOGNDTYPE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXOGNDPKD_TXPKDOGNDRESET, self).__init__(register,
            'TXPKDOGNDRESET', 'RAC_NS.TXOGNDPKD.TXPKDOGNDRESET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXOGNDPKDSTATUS_TXOGNDPKDN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXOGNDPKDSTATUS_TXOGNDPKDN, self).__init__(register,
            'TXOGNDPKDN', 'RAC_NS.TXOGNDPKDSTATUS.TXOGNDPKDN', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXOGNDPKDSTATUS_TXOGNDPKDP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXOGNDPKDSTATUS_TXOGNDPKDP, self).__init__(register,
            'TXOGNDPKDP', 'RAC_NS.TXOGNDPKDSTATUS.TXOGNDPKDP', 'read-only',
            u"",
            1, 1)
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


class RM_Field_RAC_NS_SPARE_IFADCPLLSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_IFADCPLLSPARE, self).__init__(register,
            'IFADCPLLSPARE', 'RAC_NS.SPARE.IFADCPLLSPARE', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_SYSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_SYSPARE, self).__init__(register,
            'SYSPARE', 'RAC_NS.SPARE.SYSPARE', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_TXSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_TXSPARE, self).__init__(register,
            'TXSPARE', 'RAC_NS.SPARE.TXSPARE', 'read-write',
            u"",
            11, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_IFADCCTRLRESERVED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_IFADCCTRLRESERVED, self).__init__(register,
            'IFADCCTRLRESERVED', 'RAC_NS.SPARE.IFADCCTRLRESERVED', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_IFADCCTRLRESERVEDLV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_IFADCCTRLRESERVEDLV, self).__init__(register,
            'IFADCCTRLRESERVEDLV', 'RAC_NS.SPARE.IFADCCTRLRESERVEDLV', 'read-write',
            u"",
            29, 3)
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


class RM_Field_RAC_NS_THMSW_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_THMSW_EN, self).__init__(register,
            'EN', 'RAC_NS.THMSW.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_THMSW_HALFSWITCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_THMSW_HALFSWITCH, self).__init__(register,
            'HALFSWITCH', 'RAC_NS.THMSW.HALFSWITCH', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIAGAALTEN_RFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIAGAALTEN_RFEN, self).__init__(register,
            'RFEN', 'RAC_NS.DIAGAALTEN.RFEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIAGAALTSEL_TP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIAGAALTSEL_TP, self).__init__(register,
            'TP', 'RAC_NS.DIAGAALTSEL.TP', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIAGAALTSEL_BLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIAGAALTSEL_BLK, self).__init__(register,
            'BLK', 'RAC_NS.DIAGAALTSEL.BLK', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_DIAGAALTBRIDGECTRL_RFSHORTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_DIAGAALTBRIDGECTRL_RFSHORTDIS, self).__init__(register,
            'RFSHORTDIS', 'RAC_NS.DIAGAALTBRIDGECTRL.RFSHORTDIS', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_SYNTHLODIVFREQCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_SYNTHLODIVFREQCTRL, self).__init__(register,
            'SYNTHLODIVFREQCTRL', 'RAC_NS.RFLOCK0.SYNTHLODIVFREQCTRL', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACIFPGAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACIFPGAEN, self).__init__(register,
            'RACIFPGAEN', 'RAC_NS.RFLOCK0.RACIFPGAEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACTXENLPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACTXENLPA, self).__init__(register,
            'RACTXENLPA', 'RAC_NS.RFLOCK0.RACTXENLPA', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACTXENHPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACTXENHPA, self).__init__(register,
            'RACTXENHPA', 'RAC_NS.RFLOCK0.RACTXENHPA', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_FRCCONVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_FRCCONVMODE, self).__init__(register,
            'FRCCONVMODE', 'RAC_NS.RFLOCK0.FRCCONVMODE', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_FRCPAUSING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_FRCPAUSING, self).__init__(register,
            'FRCPAUSING', 'RAC_NS.RFLOCK0.FRCPAUSING', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_MODEMANTSWENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_MODEMANTSWENABLE, self).__init__(register,
            'MODEMANTSWENABLE', 'RAC_NS.RFLOCK0.MODEMANTSWENABLE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_MODEMLRBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_MODEMLRBLE, self).__init__(register,
            'MODEMLRBLE', 'RAC_NS.RFLOCK0.MODEMLRBLE', 'read-write',
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


class RM_Field_RAC_NS_RFLOCK1_RACPASTRIPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACPASTRIPE, self).__init__(register,
            'RACPASTRIPE', 'RAC_NS.RFLOCK1.RACPASTRIPE', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK1_RACPASLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACPASLICE, self).__init__(register,
            'RACPASLICE', 'RAC_NS.RFLOCK1.RACPASLICE', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True



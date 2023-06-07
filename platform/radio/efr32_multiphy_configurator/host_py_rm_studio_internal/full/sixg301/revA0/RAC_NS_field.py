
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


class RM_Field_RAC_NS_SEQIF_STATECHANGESEQIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATECHANGESEQIF, self).__init__(register,
            'STATECHANGESEQIF', 'RAC_NS.SEQIF.STATECHANGESEQIF', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STIMCMPEVSEQIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STIMCMPEVSEQIF, self).__init__(register,
            'STIMCMPEVSEQIF', 'RAC_NS.SEQIF.STIMCMPEVSEQIF', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_DEMODRXREQCLRSEQIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_DEMODRXREQCLRSEQIF, self).__init__(register,
            'DEMODRXREQCLRSEQIF', 'RAC_NS.SEQIF.DEMODRXREQCLRSEQIF', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_PRSEVENTSEQIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_PRSEVENTSEQIF, self).__init__(register,
            'PRSEVENTSEQIF', 'RAC_NS.SEQIF.PRSEVENTSEQIF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATEOFFIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATEOFFIF, self).__init__(register,
            'STATEOFFIF', 'RAC_NS.SEQIF.STATEOFFIF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXWARMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXWARMIF, self).__init__(register,
            'STATERXWARMIF', 'RAC_NS.SEQIF.STATERXWARMIF', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXSEARCHIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXSEARCHIF, self).__init__(register,
            'STATERXSEARCHIF', 'RAC_NS.SEQIF.STATERXSEARCHIF', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXFRAMEIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXFRAMEIF, self).__init__(register,
            'STATERXFRAMEIF', 'RAC_NS.SEQIF.STATERXFRAMEIF', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXPDIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXPDIF, self).__init__(register,
            'STATERXPDIF', 'RAC_NS.SEQIF.STATERXPDIF', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERX2RXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERX2RXIF, self).__init__(register,
            'STATERX2RXIF', 'RAC_NS.SEQIF.STATERX2RXIF', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERXOVERFLOWIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERXOVERFLOWIF, self).__init__(register,
            'STATERXOVERFLOWIF', 'RAC_NS.SEQIF.STATERXOVERFLOWIF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATERX2TXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATERX2TXIF, self).__init__(register,
            'STATERX2TXIF', 'RAC_NS.SEQIF.STATERX2TXIF', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETXWARMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETXWARMIF, self).__init__(register,
            'STATETXWARMIF', 'RAC_NS.SEQIF.STATETXWARMIF', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETXIF, self).__init__(register,
            'STATETXIF', 'RAC_NS.SEQIF.STATETXIF', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETXPDIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETXPDIF, self).__init__(register,
            'STATETXPDIF', 'RAC_NS.SEQIF.STATETXPDIF', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETX2RXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETX2RXIF, self).__init__(register,
            'STATETX2RXIF', 'RAC_NS.SEQIF.STATETX2RXIF', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATETX2TXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATETX2TXIF, self).__init__(register,
            'STATETX2TXIF', 'RAC_NS.SEQIF.STATETX2TXIF', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIF_STATESHUTDOWNIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIF_STATESHUTDOWNIF, self).__init__(register,
            'STATESHUTDOWNIF', 'RAC_NS.SEQIF.STATESHUTDOWNIF', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATECHANGESEQIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATECHANGESEQIEN, self).__init__(register,
            'STATECHANGESEQIEN', 'RAC_NS.SEQIEN.STATECHANGESEQIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STIMCMPEVSEQIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STIMCMPEVSEQIEN, self).__init__(register,
            'STIMCMPEVSEQIEN', 'RAC_NS.SEQIEN.STIMCMPEVSEQIEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_DEMODRXREQCLRSEQIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_DEMODRXREQCLRSEQIEN, self).__init__(register,
            'DEMODRXREQCLRSEQIEN', 'RAC_NS.SEQIEN.DEMODRXREQCLRSEQIEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_PRSEVENTSEQIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_PRSEVENTSEQIEN, self).__init__(register,
            'PRSEVENTSEQIEN', 'RAC_NS.SEQIEN.PRSEVENTSEQIEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATEOFFIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATEOFFIEN, self).__init__(register,
            'STATEOFFIEN', 'RAC_NS.SEQIEN.STATEOFFIEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXWARMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXWARMIEN, self).__init__(register,
            'STATERXWARMIEN', 'RAC_NS.SEQIEN.STATERXWARMIEN', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXSEARCHIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXSEARCHIEN, self).__init__(register,
            'STATERXSEARCHIEN', 'RAC_NS.SEQIEN.STATERXSEARCHIEN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXFRAMEIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXFRAMEIEN, self).__init__(register,
            'STATERXFRAMEIEN', 'RAC_NS.SEQIEN.STATERXFRAMEIEN', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXPDIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXPDIEN, self).__init__(register,
            'STATERXPDIEN', 'RAC_NS.SEQIEN.STATERXPDIEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERX2RXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERX2RXIEN, self).__init__(register,
            'STATERX2RXIEN', 'RAC_NS.SEQIEN.STATERX2RXIEN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERXOVERFLOWIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERXOVERFLOWIEN, self).__init__(register,
            'STATERXOVERFLOWIEN', 'RAC_NS.SEQIEN.STATERXOVERFLOWIEN', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATERX2TXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATERX2TXIEN, self).__init__(register,
            'STATERX2TXIEN', 'RAC_NS.SEQIEN.STATERX2TXIEN', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETXWARMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETXWARMIEN, self).__init__(register,
            'STATETXWARMIEN', 'RAC_NS.SEQIEN.STATETXWARMIEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETXIEN, self).__init__(register,
            'STATETXIEN', 'RAC_NS.SEQIEN.STATETXIEN', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETXPDIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETXPDIEN, self).__init__(register,
            'STATETXPDIEN', 'RAC_NS.SEQIEN.STATETXPDIEN', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETX2RXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETX2RXIEN, self).__init__(register,
            'STATETX2RXIEN', 'RAC_NS.SEQIEN.STATETX2RXIEN', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATETX2TXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATETX2TXIEN, self).__init__(register,
            'STATETX2TXIEN', 'RAC_NS.SEQIEN.STATETX2TXIEN', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SEQIEN_STATESHUTDOWNIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SEQIEN_STATESHUTDOWNIEN, self).__init__(register,
            'STATESHUTDOWNIEN', 'RAC_NS.SEQIEN.STATESHUTDOWNIEN', 'read-write',
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


class RM_Field_RAC_NS_VCOCTRL_SYVCOVCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VCOCTRL_SYVCOVCAP, self).__init__(register,
            'SYVCOVCAP', 'RAC_NS.VCOCTRL.SYVCOVCAP', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CHPCTRL_CHPOUTPUTTRISTATEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CHPCTRL_CHPOUTPUTTRISTATEMODE, self).__init__(register,
            'CHPOUTPUTTRISTATEMODE', 'RAC_NS.CHPCTRL.CHPOUTPUTTRISTATEMODE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VCOTUNE_SYVCOTUNING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VCOTUNE_SYVCOTUNING, self).__init__(register,
            'SYVCOTUNING', 'RAC_NS.VCOTUNE.SYVCOTUNING', 'read-write',
            u"",
            0, 11)
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


class RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO02G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO02G4EN, self).__init__(register,
            'INTDIVSYLODIVRLO02G4EN', 'RAC_NS.ANTDIV.INTDIVSYLODIVRLO02G4EN', 'read-write',
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


class RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO12G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_ANTDIV_INTDIVSYLODIVRLO12G4EN, self).__init__(register,
            'INTDIVSYLODIVRLO12G4EN', 'RAC_NS.ANTDIV.INTDIVSYLODIVRLO12G4EN', 'read-write',
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


class RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSESELCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSESELCURR, self).__init__(register,
            'ADCTSENSESELCURR', 'RAC_NS.AUXADCTRIM.ADCTSENSESELCURR', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_ADCTRIMCURRTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_ADCTRIMCURRTSENSE, self).__init__(register,
            'ADCTRIMCURRTSENSE', 'RAC_NS.AUXADCTRIM.ADCTRIMCURRTSENSE', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSESELVBE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSESELVBE, self).__init__(register,
            'ADCTSENSESELVBE', 'RAC_NS.AUXADCTRIM.ADCTSENSESELVBE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSETRIMVBE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_ADCTSENSETRIMVBE2, self).__init__(register,
            'ADCTSENSETRIMVBE2', 'RAC_NS.AUXADCTRIM.ADCTSENSETRIMVBE2', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCTRIM_ADCTUNERC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCTRIM_ADCTUNERC, self).__init__(register,
            'ADCTUNERC', 'RAC_NS.AUXADCTRIM.ADCTUNERC', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENADC, self).__init__(register,
            'ADCENADC', 'RAC_NS.AUXADCEN.ADCENADC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENCLK, self).__init__(register,
            'ADCENCLK', 'RAC_NS.AUXADCEN.ADCENCLK', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENAUXADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENAUXADC, self).__init__(register,
            'ADCENAUXADC', 'RAC_NS.AUXADCEN.ADCENAUXADC', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENINPUTBUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENINPUTBUFFER, self).__init__(register,
            'ADCENINPUTBUFFER', 'RAC_NS.AUXADCEN.ADCENINPUTBUFFER', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENLDOSERIES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENLDOSERIES, self).__init__(register,
            'ADCENLDOSERIES', 'RAC_NS.AUXADCEN.ADCENLDOSERIES', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENNEGRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENNEGRES, self).__init__(register,
            'ADCENNEGRES', 'RAC_NS.AUXADCEN.ADCENNEGRES', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENPMON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENPMON, self).__init__(register,
            'ADCENPMON', 'RAC_NS.AUXADCEN.ADCENPMON', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENRESONDIAGA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENRESONDIAGA, self).__init__(register,
            'ADCENRESONDIAGA', 'RAC_NS.AUXADCEN.ADCENRESONDIAGA', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENTSENSECAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENTSENSECAL, self).__init__(register,
            'ADCENTSENSECAL', 'RAC_NS.AUXADCEN.ADCENTSENSECAL', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCINPUTBUFFERBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCINPUTBUFFERBYPASS, self).__init__(register,
            'ADCINPUTBUFFERBYPASS', 'RAC_NS.AUXADCEN.ADCINPUTBUFFERBYPASS', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCEN_ADCENLDOBIASSERIES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCEN_ADCENLDOBIASSERIES, self).__init__(register,
            'ADCENLDOBIASSERIES', 'RAC_NS.AUXADCEN.ADCENLDOBIASSERIES', 'read-write',
            u"",
            10, 1)
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


class RM_Field_RAC_NS_AUXADCCTRL1_ADCINPUTRESSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_ADCINPUTRESSEL, self).__init__(register,
            'ADCINPUTRESSEL', 'RAC_NS.AUXADCCTRL1.ADCINPUTRESSEL', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_ADCINPUTSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_ADCINPUTSCALE, self).__init__(register,
            'ADCINPUTSCALE', 'RAC_NS.AUXADCCTRL1.ADCINPUTSCALE', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_ADCINVERTCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_ADCINVERTCLK, self).__init__(register,
            'ADCINVERTCLK', 'RAC_NS.AUXADCCTRL1.ADCINVERTCLK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_ADCLDOSHUNTCURLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_ADCLDOSHUNTCURLVL2, self).__init__(register,
            'ADCLDOSHUNTCURLVL2', 'RAC_NS.AUXADCCTRL1.ADCLDOSHUNTCURLVL2', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_ADCTUNERCCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_ADCTUNERCCALMODE, self).__init__(register,
            'ADCTUNERCCALMODE', 'RAC_NS.AUXADCCTRL1.ADCTUNERCCALMODE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL1_ADCZEROOPT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL1_ADCZEROOPT, self).__init__(register,
            'ADCZEROOPT', 'RAC_NS.AUXADCCTRL1.ADCZEROOPT', 'read-write',
            u"",
            11, 1)
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


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTILOADREG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTILOADREG2, self).__init__(register,
            'CLKMULTILOADREG2', 'RAC_NS.CLKMULTEN0.CLKMULTILOADREG2', 'read-write',
            u"",
            11, 3)
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


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVDAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVDAC, self).__init__(register,
            'CLKMULTENDRVDAC', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVDAC', 'read-write',
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


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVIRCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVIRCAL, self).__init__(register,
            'CLKMULTENDRVIRCAL', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVIRCAL', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTFREQCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTFREQCAL, self).__init__(register,
            'CLKMULTFREQCAL', 'RAC_NS.CLKMULTEN0.CLKMULTFREQCAL', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1FORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1FORCEDSTARTUP, self).__init__(register,
            'CLKMULTENREG1FORCEDSTARTUP', 'RAC_NS.CLKMULTEN0.CLKMULTENREG1FORCEDSTARTUP', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1IBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1IBIAS, self).__init__(register,
            'CLKMULTENREG1IBIAS', 'RAC_NS.CLKMULTEN0.CLKMULTENREG1IBIAS', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1REPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1REPLICA, self).__init__(register,
            'CLKMULTENREG1REPLICA', 'RAC_NS.CLKMULTEN0.CLKMULTENREG1REPLICA', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1STBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENREG1STBLOAD, self).__init__(register,
            'CLKMULTENREG1STBLOAD', 'RAC_NS.CLKMULTEN0.CLKMULTENREG1STBLOAD', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVTEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN0_CLKMULTENDRVTEST, self).__init__(register,
            'CLKMULTENDRVTEST', 'RAC_NS.CLKMULTEN0.CLKMULTENDRVTEST', 'read-write',
            u"",
            28, 1)
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


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVN, self).__init__(register,
            'CLKMULTDIVN', 'RAC_NS.CLKMULTEN1.CLKMULTDIVN', 'read-write',
            u"",
            17, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVR, self).__init__(register,
            'CLKMULTDIVR', 'RAC_NS.CLKMULTEN1.CLKMULTDIVR', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTEN1_CLKMULTDIVX, self).__init__(register,
            'CLKMULTDIVX', 'RAC_NS.CLKMULTEN1.CLKMULTDIVX', 'read-write',
            u"",
            27, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTENRESYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTENRESYNC, self).__init__(register,
            'CLKMULTENRESYNC', 'RAC_NS.CLKMULTCTRL.CLKMULTENRESYNC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTVALID, self).__init__(register,
            'CLKMULTVALID', 'RAC_NS.CLKMULTCTRL.CLKMULTVALID', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTRESETPHFRQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTRESETPHFRQDET, self).__init__(register,
            'CLKMULTRESETPHFRQDET', 'RAC_NS.CLKMULTCTRL.CLKMULTRESETPHFRQDET', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREF1, self).__init__(register,
            'CLKMULTTRIMVREF1', 'RAC_NS.CLKMULTCTRL.CLKMULTTRIMVREF1', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREF2, self).__init__(register,
            'CLKMULTTRIMVREF2', 'RAC_NS.CLKMULTCTRL.CLKMULTTRIMVREF2', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_CLKMULTCTRL_CLKMULTTRIMVREG1, self).__init__(register,
            'CLKMULTTRIMVREG1', 'RAC_NS.CLKMULTCTRL.CLKMULTTRIMVREG1', 'read-write',
            u"",
            8, 3)
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


class RM_Field_RAC_NS_IFADCDBG_ADCENSIDETONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_ADCENSIDETONE, self).__init__(register,
            'ADCENSIDETONE', 'RAC_NS.IFADCDBG.ADCENSIDETONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCDBG_ADCENTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_ADCENTSENSE, self).__init__(register,
            'ADCENTSENSE', 'RAC_NS.IFADCDBG.ADCENTSENSE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCDBG_ADCINPUTSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCDBG_ADCINPUTSELECT, self).__init__(register,
            'ADCINPUTSELECT', 'RAC_NS.IFADCDBG.ADCINPUTSELECT', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM0_ADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM0_ADCCLKSEL, self).__init__(register,
            'ADCCLKSEL', 'RAC_NS.IFADCTRIM0.ADCCLKSEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_ADCREFBUFCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_ADCREFBUFCURLVL, self).__init__(register,
            'ADCREFBUFCURLVL', 'RAC_NS.IFADCTRIM1.ADCREFBUFCURLVL', 'read-write',
            u"",
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCTRIM1_ADCSIDETONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCTRIM1_ADCSIDETONEAMP, self).__init__(register,
            'ADCSIDETONEAMP', 'RAC_NS.IFADCTRIM1.ADCSIDETONEAMP', 'read-write',
            u"",
            17, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCCAL_ADCENRCCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCCAL_ADCENRCCAL, self).__init__(register,
            'ADCENRCCAL', 'RAC_NS.IFADCCAL.ADCENRCCAL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_IFADCSTATUS_ADCRCCALOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_IFADCSTATUS_ADCRCCALOUT, self).__init__(register,
            'ADCRCCALOUT', 'RAC_NS.IFADCSTATUS.ADCRCCALOUT', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM0_LNAMIXTRIMVREG, self).__init__(register,
            'LNAMIXTRIMVREG', 'RAC_NS.LNAMIXTRIM0.LNAMIXTRIMVREG', 'read-write',
            u"",
            0, 4)
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
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXIBIAS1TRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXIBIAS1TRIM, self).__init__(register,
            'LNAMIXIBIAS1TRIM', 'RAC_NS.LNAMIXTRIM1.LNAMIXIBIAS1TRIM', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXNCAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM1_LNAMIXNCAS1ADJ, self).__init__(register,
            'LNAMIXNCAS1ADJ', 'RAC_NS.LNAMIXTRIM1.LNAMIXNCAS1ADJ', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXHIGHCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXHIGHCUR, self).__init__(register,
            'LNAMIXHIGHCUR', 'RAC_NS.LNAMIXTRIM2.LNAMIXHIGHCUR', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXENREGVHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXENREGVHIGH, self).__init__(register,
            'LNAMIXENREGVHIGH', 'RAC_NS.LNAMIXTRIM2.LNAMIXENREGVHIGH', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXENSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXENSTBLOAD, self).__init__(register,
            'LNAMIXENSTBLOAD', 'RAC_NS.LNAMIXTRIM2.LNAMIXENSTBLOAD', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXREGLOWPWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM2_LNAMIXREGLOWPWR, self).__init__(register,
            'LNAMIXREGLOWPWR', 'RAC_NS.LNAMIXTRIM2.LNAMIXREGLOWPWR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFATT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFATT1, self).__init__(register,
            'LNAMIXRFATT1', 'RAC_NS.LNAMIXTRIM3.LNAMIXRFATT1', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFPKDCALCMLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFPKDCALCMLO, self).__init__(register,
            'LNAMIXRFPKDCALCMLO', 'RAC_NS.LNAMIXTRIM3.LNAMIXRFPKDCALCMLO', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFPKDCALCMHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM3_LNAMIXRFPKDCALCMHI, self).__init__(register,
            'LNAMIXRFPKDCALCMHI', 'RAC_NS.LNAMIXTRIM3.LNAMIXRFPKDCALCMHI', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXTRIM4_LNAMIXRFPKDBWSEL, self).__init__(register,
            'LNAMIXRFPKDBWSEL', 'RAC_NS.LNAMIXTRIM4.LNAMIXRFPKDBWSEL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXCALVMODE, self).__init__(register,
            'LNAMIXCALVMODE', 'RAC_NS.LNAMIXCAL.LNAMIXCALVMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL1AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXCAL_LNAMIXIRCAL1AMP, self).__init__(register,
            'LNAMIXIRCAL1AMP', 'RAC_NS.LNAMIXCAL.LNAMIXIRCAL1AMP', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREREGBYPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREREGBYPFORCE, self).__init__(register,
            'PREREGBYPFORCE', 'RAC_NS.PRECTRL.PREREGBYPFORCE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREREGENBYPCMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREREGENBYPCMP, self).__init__(register,
            'PREREGENBYPCMP', 'RAC_NS.PRECTRL.PREREGENBYPCMP', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREREGENSTBILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREREGENSTBILOAD, self).__init__(register,
            'PREREGENSTBILOAD', 'RAC_NS.PRECTRL.PREREGENSTBILOAD', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREREGENINTBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREREGENINTBIAS, self).__init__(register,
            'PREREGENINTBIAS', 'RAC_NS.PRECTRL.PREREGENINTBIAS', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREREGENVTRMINI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREREGENVTRMINI, self).__init__(register,
            'PREREGENVTRMINI', 'RAC_NS.PRECTRL.PREREGENVTRMINI', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREREGENVTRMINISTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREREGENVTRMINISTARTUP, self).__init__(register,
            'PREREGENVTRMINISTARTUP', 'RAC_NS.PRECTRL.PREREGENVTRMINISTARTUP', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PRECTRL_PREREGSTARTUPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PRECTRL_PREREGSTARTUPFORCE, self).__init__(register,
            'PREREGSTARTUPFORCE', 'RAC_NS.PRECTRL.PREREGSTARTUPFORCE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_TXPAAMPCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_TXPAAMPCTRL, self).__init__(register,
            'TXPAAMPCTRL', 'RAC_NS.PATRIM0.TXPAAMPCTRL', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PATRIM0_ENAMPCTRLREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PATRIM0_ENAMPCTRLREG, self).__init__(register,
            'ENAMPCTRLREG', 'RAC_NS.PATRIM0.ENAMPCTRLREG', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXPOWER_TX0DBMSELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXPOWER_TX0DBMSELSLICE, self).__init__(register,
            'TX0DBMSELSLICE', 'RAC_NS.TXPOWER.TX0DBMSELSLICE', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TXRAMP_PARAMPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TXRAMP_PARAMPMODE, self).__init__(register,
            'PARAMPMODE', 'RAC_NS.TXRAMP.PARAMPMODE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RADIOEN_PREREGENREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RADIOEN_PREREGENREG, self).__init__(register,
            'PREREGENREG', 'RAC_NS.RADIOEN.PREREGENREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFATTDCEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN0_LNAMIXRFATTDCEN1, self).__init__(register,
            'LNAMIXRFATTDCEN1', 'RAC_NS.RFPATHEN0.LNAMIXRFATTDCEN1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXEN1, self).__init__(register,
            'LNAMIXEN1', 'RAC_NS.RFPATHEN1.LNAMIXEN1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFPKDENRF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXRFPKDENRF1, self).__init__(register,
            'LNAMIXRFPKDENRF1', 'RAC_NS.RFPATHEN1.LNAMIXRFPKDENRF1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXTRSW1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXTRSW1, self).__init__(register,
            'LNAMIXTRSW1', 'RAC_NS.RFPATHEN1.LNAMIXTRSW1', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFPATHEN1_LNAMIXREGLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFPATHEN1_LNAMIXREGLOWCUR, self).__init__(register,
            'LNAMIXREGLOWCUR', 'RAC_NS.RFPATHEN1.LNAMIXREGLOWCUR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_ADCCAPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_ADCCAPRESET, self).__init__(register,
            'ADCCAPRESET', 'RAC_NS.RX.ADCCAPRESET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_ADCENLDOSHUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_ADCENLDOSHUNT, self).__init__(register,
            'ADCENLDOSHUNT', 'RAC_NS.RX.ADCENLDOSHUNT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXCALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXCALEN, self).__init__(register,
            'LNAMIXCALEN', 'RAC_NS.RX.LNAMIXCALEN', 'read-write',
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


class RM_Field_RAC_NS_RX_LNAMIXENLOTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXENLOTHRESH, self).__init__(register,
            'LNAMIXENLOTHRESH', 'RAC_NS.RX.LNAMIXENLOTHRESH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXMXRLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXMXRLOSEL, self).__init__(register,
            'LNAMIXMXRLOSEL', 'RAC_NS.RX.LNAMIXMXRLOSEL', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXCURCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXCURCTRL, self).__init__(register,
            'LNAMIXCURCTRL', 'RAC_NS.RX.LNAMIXCURCTRL', 'read-write',
            u"",
            7, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXLNA1SLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXLNA1SLICE, self).__init__(register,
            'LNAMIXLNA1SLICE', 'RAC_NS.RX.LNAMIXLNA1SLICE', 'read-write',
            u"",
            13, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXDOUBLECUR1EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXDOUBLECUR1EN, self).__init__(register,
            'LNAMIXDOUBLECUR1EN', 'RAC_NS.RX.LNAMIXDOUBLECUR1EN', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXLOWCUR, self).__init__(register,
            'LNAMIXLOWCUR', 'RAC_NS.RX.LNAMIXLOWCUR', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXRFPKDTHRESHSELLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXRFPKDTHRESHSELLO, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELLO', 'RAC_NS.RX.LNAMIXRFPKDTHRESHSELLO', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RX_LNAMIXRFPKDTHRESHSELHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RX_LNAMIXRFPKDTHRESHSELHI, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELHI', 'RAC_NS.RX.LNAMIXRFPKDTHRESHSELHI', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_SYCHPBIASTRIMBUFTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_SYCHPBIASTRIMBUFTX, self).__init__(register,
            'SYCHPBIASTRIMBUFTX', 'RAC_NS.TX.SYCHPBIASTRIMBUFTX', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_SYPFDCHPLPENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_SYPFDCHPLPENTX, self).__init__(register,
            'SYPFDCHPLPENTX', 'RAC_NS.TX.SYPFDCHPLPENTX', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX_SYPFDFPWENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX_SYPFDFPWENTX, self).__init__(register,
            'SYPFDFPWENTX', 'RAC_NS.TX.SYPFDFPWENTX', 'read-write',
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


class RM_Field_RAC_NS_SYDEBUG_SYPFDFPWENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYPFDFPWENRX, self).__init__(register,
            'SYPFDFPWENRX', 'RAC_NS.SYDEBUG.SYPFDFPWENRX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYPFDCHPLPENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYPFDCHPLPENRX, self).__init__(register,
            'SYPFDCHPLPENRX', 'RAC_NS.SYDEBUG.SYPFDCHPLPENRX', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYCHPBIASTRIMBUFRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYCHPBIASTRIMBUFRX, self).__init__(register,
            'SYCHPBIASTRIMBUFRX', 'RAC_NS.SYDEBUG.SYCHPBIASTRIMBUFRX', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYENMMDREGBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYENMMDREGBIAS, self).__init__(register,
            'SYENMMDREGBIAS', 'RAC_NS.SYDEBUG.SYENMMDREGBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYENMMDREGFORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYENMMDREGFORCEDSTARTUP, self).__init__(register,
            'SYENMMDREGFORCEDSTARTUP', 'RAC_NS.SYDEBUG.SYENMMDREGFORCEDSTARTUP', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYENMMDREGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYENMMDREGREPLICA, self).__init__(register,
            'SYENMMDREGREPLICA', 'RAC_NS.SYDEBUG.SYENMMDREGREPLICA', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDEBUG_SYENMMDSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDEBUG_SYENMMDSYNC, self).__init__(register,
            'SYENMMDSYNC', 'RAC_NS.SYDEBUG.SYENMMDSYNC', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMIPTAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMIPTAT, self).__init__(register,
            'SYVCOTRIMIPTAT', 'RAC_NS.SYTRIM0.SYVCOTRIMIPTAT', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYLODIVREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYLODIVREGTRIMVREG, self).__init__(register,
            'SYLODIVREGTRIMVREG', 'RAC_NS.SYTRIM0.SYLODIVREGTRIMVREG', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMPKDAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMPKDAMP, self).__init__(register,
            'SYVCOTRIMPKDAMP', 'RAC_NS.SYTRIM0.SYVCOTRIMPKDAMP', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYVCOREGLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYVCOREGLOWCUR, self).__init__(register,
            'SYVCOREGLOWCUR', 'RAC_NS.SYTRIM0.SYVCOREGLOWCUR', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMR, self).__init__(register,
            'SYVCOTRIMR', 'RAC_NS.SYTRIM0.SYVCOTRIMR', 'read-write',
            u"",
            12, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMREF, self).__init__(register,
            'SYVCOTRIMREF', 'RAC_NS.SYTRIM0.SYVCOTRIMREF', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYTDCREGTRIMBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYTDCREGTRIMBW, self).__init__(register,
            'SYTDCREGTRIMBW', 'RAC_NS.SYTRIM0.SYTDCREGTRIMBW', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYVCOHCAPRETIMESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYVCOHCAPRETIMESEL, self).__init__(register,
            'SYVCOHCAPRETIMESEL', 'RAC_NS.SYTRIM0.SYVCOHCAPRETIMESEL', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYVCOREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYVCOREGTRIMVREG, self).__init__(register,
            'SYVCOREGTRIMVREG', 'RAC_NS.SYTRIM0.SYVCOREGTRIMVREG', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM0_SYVCOTRIMIBIAS, self).__init__(register,
            'SYVCOTRIMIBIAS', 'RAC_NS.SYTRIM0.SYVCOTRIMIBIAS', 'read-write',
            u"",
            27, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYCNT, self).__init__(register,
            'SYTDCTRIMDLYCNT', 'RAC_NS.SYTRIM1.SYTDCTRIMDLYCNT', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYLOAD, self).__init__(register,
            'SYTDCTRIMDLYLOAD', 'RAC_NS.SYTRIM1.SYTDCTRIMDLYLOAD', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYSTOPMETA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYSTOPMETA, self).__init__(register,
            'SYTDCTRIMDLYSTOPMETA', 'RAC_NS.SYTRIM1.SYTDCTRIMDLYSTOPMETA', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYDTCREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYDTCREGTRIMVREF, self).__init__(register,
            'SYDTCREGTRIMVREF', 'RAC_NS.SYTRIM1.SYDTCREGTRIMVREF', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYCK1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTDCTRIMDLYCK1, self).__init__(register,
            'SYTDCTRIMDLYCK1', 'RAC_NS.SYTRIM1.SYTDCTRIMDLYCK1', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYDTCRDACTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYDTCRDACTRIM, self).__init__(register,
            'SYDTCRDACTRIM', 'RAC_NS.SYTRIM1.SYDTCRDACTRIM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMVREG, self).__init__(register,
            'SYTDCREGTRIMVREG', 'RAC_NS.SYTRIM1.SYTDCREGTRIMVREG', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMTEMPCOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMTEMPCOP, self).__init__(register,
            'SYTDCREGTRIMTEMPCOP', 'RAC_NS.SYTRIM1.SYTDCREGTRIMTEMPCOP', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMVREF, self).__init__(register,
            'SYTDCREGTRIMVREF', 'RAC_NS.SYTRIM1.SYTDCREGTRIMVREF', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMTEMPCON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM1_SYTDCREGTRIMTEMPCON, self).__init__(register,
            'SYTDCREGTRIMTEMPCON', 'RAC_NS.SYTRIM1.SYTDCREGTRIMTEMPCON', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOREG, self).__init__(register,
            'SYENVCOREG', 'RAC_NS.SYEN.SYENVCOREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENDLFAQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENDLFAQNC, self).__init__(register,
            'SYENDLFAQNC', 'RAC_NS.SYEN.SYENDLFAQNC', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENMMDREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENMMDREGSTBLOAD, self).__init__(register,
            'SYENMMDREGSTBLOAD', 'RAC_NS.SYEN.SYENMMDREGSTBLOAD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENTDCAQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENTDCAQNC, self).__init__(register,
            'SYENTDCAQNC', 'RAC_NS.SYEN.SYENTDCAQNC', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENTDCREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENTDCREG, self).__init__(register,
            'SYENTDCREG', 'RAC_NS.SYEN.SYENTDCREG', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENTDCREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENTDCREGSTBLOAD, self).__init__(register,
            'SYENTDCREGSTBLOAD', 'RAC_NS.SYEN.SYENTDCREGSTBLOAD', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOIBIAS, self).__init__(register,
            'SYENVCOIBIAS', 'RAC_NS.SYEN.SYENVCOIBIAS', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOPKD, self).__init__(register,
            'SYENVCOPKD', 'RAC_NS.SYEN.SYENVCOPKD', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOBIAS, self).__init__(register,
            'SYENVCOBIAS', 'RAC_NS.SYEN.SYENVCOBIAS', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENTDC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENTDC, self).__init__(register,
            'SYENTDC', 'RAC_NS.SYEN.SYENTDC', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYEN_SYENVCOHCAPRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYEN_SYENVCOHCAPRETIME, self).__init__(register,
            'SYENVCOHCAPRETIME', 'RAC_NS.SYEN.SYENVCOHCAPRETIME', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVADCCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVADCCLK, self).__init__(register,
            'SYENLODIVADCCLK', 'RAC_NS.SYLOEN.SYENLODIVADCCLK', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVFCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVFCAL, self).__init__(register,
            'SYENLODIVFCAL', 'RAC_NS.SYLOEN.SYENLODIVFCAL', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMDIV, self).__init__(register,
            'SYENLODIVHADMDIV', 'RAC_NS.SYLOEN.SYENLODIVHADMDIV', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMLO, self).__init__(register,
            'SYENLODIVHADMLO', 'RAC_NS.SYLOEN.SYENLODIVHADMLO', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMRXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMRXLO, self).__init__(register,
            'SYENLODIVHADMRXLO', 'RAC_NS.SYLOEN.SYENLODIVHADMRXLO', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMTXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVHADMTXLO, self).__init__(register,
            'SYENLODIVHADMTXLO', 'RAC_NS.SYLOEN.SYENLODIVHADMTXLO', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVREGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVREGREPLICA, self).__init__(register,
            'SYENLODIVREGREPLICA', 'RAC_NS.SYLOEN.SYENLODIVREGREPLICA', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVREGFORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVREGFORCEDSTARTUP, self).__init__(register,
            'SYENLODIVREGFORCEDSTARTUP', 'RAC_NS.SYLOEN.SYENLODIVREGFORCEDSTARTUP', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVREGBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVREGBIAS, self).__init__(register,
            'SYENLODIVREGBIAS', 'RAC_NS.SYLOEN.SYENLODIVREGBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVREG, self).__init__(register,
            'SYENLODIVREG', 'RAC_NS.SYLOEN.SYENLODIVREG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVLPRXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVLPRXLO, self).__init__(register,
            'SYENLODIVLPRXLO', 'RAC_NS.SYLOEN.SYENLODIVLPRXLO', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVLPRXDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVLPRXDIV, self).__init__(register,
            'SYENLODIVLPRXDIV', 'RAC_NS.SYLOEN.SYENLODIVLPRXDIV', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVIQCLKBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVIQCLKBIAS, self).__init__(register,
            'SYENLODIVIQCLKBIAS', 'RAC_NS.SYLOEN.SYENLODIVIQCLKBIAS', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVDIVSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVDIVSE, self).__init__(register,
            'SYENLODIVDIVSE', 'RAC_NS.SYLOEN.SYENLODIVDIVSE', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVDSMDACCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVDSMDACCLK, self).__init__(register,
            'SYENLODIVDSMDACCLK', 'RAC_NS.SYLOEN.SYENLODIVDSMDACCLK', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVFPSRC2G4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVFPSRC2G4, self).__init__(register,
            'SYENLODIVFPSRC2G4', 'RAC_NS.SYLOEN.SYENLODIVFPSRC2G4', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVREGSTBLOAD, self).__init__(register,
            'SYENLODIVREGSTBLOAD', 'RAC_NS.SYLOEN.SYENLODIVREGSTBLOAD', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVSECLKBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVSECLKBIAS, self).__init__(register,
            'SYENLODIVSECLKBIAS', 'RAC_NS.SYLOEN.SYENLODIVSECLKBIAS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVSMUXCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVSMUXCLK, self).__init__(register,
            'SYENLODIVSMUXCLK', 'RAC_NS.SYLOEN.SYENLODIVSMUXCLK', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENLODIVTXRF0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENLODIVTXRF0DBM, self).__init__(register,
            'SYENLODIVTXRF0DBM', 'RAC_NS.SYLOEN.SYENLODIVTXRF0DBM', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENMMDREG, self).__init__(register,
            'SYENMMDREG', 'RAC_NS.SYLOEN.SYENMMDREG', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENMMDCLKINJXO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENMMDCLKINJXO, self).__init__(register,
            'SYENMMDCLKINJXO', 'RAC_NS.SYLOEN.SYENMMDCLKINJXO', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENDTCCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENDTCCORE, self).__init__(register,
            'SYENDTCCORE', 'RAC_NS.SYLOEN.SYENDTCCORE', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENDTCREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENDTCREG, self).__init__(register,
            'SYENDTCREG', 'RAC_NS.SYLOEN.SYENDTCREG', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYLOEN_SYENMMDAQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYLOEN_SYENMMDAQNC, self).__init__(register,
            'SYENMMDAQNC', 'RAC_NS.SYLOEN.SYENMMDAQNC', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYMMDCTRL_SYMMDPHISEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYMMDCTRL_SYMMDPHISEL, self).__init__(register,
            'SYMMDPHISEL', 'RAC_NS.SYMMDCTRL.SYMMDPHISEL', 'read-write',
            u"",
            1, 1)
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


class RM_Field_RAC_NS_AGCOVERWRITE0_ENMANTIACOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_ENMANTIACOMP, self).__init__(register,
            'ENMANTIACOMP', 'RAC_NS.AGCOVERWRITE0.ENMANTIACOMP', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_MANTIACOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_MANTIACOMP, self).__init__(register,
            'MANTIACOMP', 'RAC_NS.AGCOVERWRITE0.MANTIACOMP', 'read-write',
            u"",
            17, 3)
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


class RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXCUREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_ENMANLNAMIXCUREN, self).__init__(register,
            'ENMANLNAMIXCUREN', 'RAC_NS.AGCOVERWRITE0.ENMANLNAMIXCUREN', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXCUREN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXCUREN0, self).__init__(register,
            'MANLNAMIXCUREN0', 'RAC_NS.AGCOVERWRITE0.MANLNAMIXCUREN0', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXCUREN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AGCOVERWRITE0_MANLNAMIXCUREN1, self).__init__(register,
            'MANLNAMIXCUREN1', 'RAC_NS.AGCOVERWRITE0.MANLNAMIXCUREN1', 'read-write',
            u"",
            28, 1)
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


class RM_Field_RAC_NS_SPARE_CLKMULTSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_CLKMULTSPARE, self).__init__(register,
            'CLKMULTSPARE', 'RAC_NS.SPARE.CLKMULTSPARE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_MIXDACTRIMSPAREVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_MIXDACTRIMSPAREVREGCORE, self).__init__(register,
            'MIXDACTRIMSPAREVREGCORE', 'RAC_NS.SPARE.MIXDACTRIMSPAREVREGCORE', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_MIXDACTRIMSPARE02(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_MIXDACTRIMSPARE02, self).__init__(register,
            'MIXDACTRIMSPARE02', 'RAC_NS.SPARE.MIXDACTRIMSPARE02', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_MIXDACTRIMSPARE01(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_MIXDACTRIMSPARE01, self).__init__(register,
            'MIXDACTRIMSPARE01', 'RAC_NS.SPARE.MIXDACTRIMSPARE01', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_MIXDACENSPARE02(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_MIXDACENSPARE02, self).__init__(register,
            'MIXDACENSPARE02', 'RAC_NS.SPARE.MIXDACENSPARE02', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_MIXDACTRIMSPAREVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_MIXDACTRIMSPAREVREGDIG, self).__init__(register,
            'MIXDACTRIMSPAREVREGDIG', 'RAC_NS.SPARE.MIXDACTRIMSPAREVREGDIG', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_MIXDACENSPARE01(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_MIXDACENSPARE01, self).__init__(register,
            'MIXDACENSPARE01', 'RAC_NS.SPARE.MIXDACENSPARE01', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_SYLODIVSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_SYLODIVSPARES, self).__init__(register,
            'SYLODIVSPARES', 'RAC_NS.SPARE.SYLODIVSPARES', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_SYMMDSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_SYMMDSPARES, self).__init__(register,
            'SYMMDSPARES', 'RAC_NS.SPARE.SYMMDSPARES', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE_SYVCOSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE_SYVCOSPARES, self).__init__(register,
            'SYVCOSPARES', 'RAC_NS.SPARE.SYVCOSPARES', 'read-write',
            u"",
            26, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_TXPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_TXPAPOWER, self).__init__(register,
            'TXPAPOWER', 'RAC_NS.PACTRL.TXPAPOWER', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PACTRL_TXPASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PACTRL_TXPASELSLICE, self).__init__(register,
            'TXPASELSLICE', 'RAC_NS.PACTRL.TXPASELSLICE', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLFKI_SYDLFLPFBWKI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLFKI_SYDLFLPFBWKI, self).__init__(register,
            'SYDLFLPFBWKI', 'RAC_NS.SYDLFKI.SYDLFLPFBWKI', 'read-write',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLFKF_SYDLFLPFBWKF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLFKF_SYDLFLPFBWKF, self).__init__(register,
            'SYDLFLPFBWKF', 'RAC_NS.SYDLFKF.SYDLFLPFBWKF', 'read-write',
            u"",
            0, 22)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMBBFILTERRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMBBFILTERRES, self).__init__(register,
            'MIXDACTRIMBBFILTERRES', 'RAC_NS.MIXDACTRIM.MIXDACTRIMBBFILTERRES', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMLOBIASNMOS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMLOBIASNMOS, self).__init__(register,
            'MIXDACTRIMLOBIASNMOS', 'RAC_NS.MIXDACTRIM.MIXDACTRIMLOBIASNMOS', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMLOBIASPMOS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMLOBIASPMOS, self).__init__(register,
            'MIXDACTRIMLOBIASPMOS', 'RAC_NS.MIXDACTRIM.MIXDACTRIMLOBIASPMOS', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMNDACCASC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMNDACCASC, self).__init__(register,
            'MIXDACTRIMNDACCASC', 'RAC_NS.MIXDACTRIM.MIXDACTRIMNDACCASC', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMPDACCASC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMPDACCASC, self).__init__(register,
            'MIXDACTRIMPDACCASC', 'RAC_NS.MIXDACTRIM.MIXDACTRIMPDACCASC', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMREFCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMREFCURRENT, self).__init__(register,
            'MIXDACTRIMREFCURRENT', 'RAC_NS.MIXDACTRIM.MIXDACTRIMREFCURRENT', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGCORE, self).__init__(register,
            'MIXDACTRIMVREGCORE', 'RAC_NS.MIXDACTRIM.MIXDACTRIMVREGCORE', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGCOREVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGCOREVREF, self).__init__(register,
            'MIXDACTRIMVREGCOREVREF', 'RAC_NS.MIXDACTRIM.MIXDACTRIMVREGCOREVREF', 'read-write',
            u"",
            19, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGDIG, self).__init__(register,
            'MIXDACTRIMVREGDIG', 'RAC_NS.MIXDACTRIM.MIXDACTRIMVREGDIG', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGDIGVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM_MIXDACTRIMVREGDIGVREF, self).__init__(register,
            'MIXDACTRIMVREGDIGVREF', 'RAC_NS.MIXDACTRIM.MIXDACTRIMVREGDIGVREF', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM2_SYTDCTRIMDLYSTOPRING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM2_SYTDCTRIMDLYSTOPRING, self).__init__(register,
            'SYTDCTRIMDLYSTOPRING', 'RAC_NS.SYTRIM2.SYTDCTRIMDLYSTOPRING', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM2_SYMMDREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM2_SYMMDREGTRIMVREG, self).__init__(register,
            'SYMMDREGTRIMVREG', 'RAC_NS.SYTRIM2.SYMMDREGTRIMVREG', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM2_SYDTCCOFFSETTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM2_SYDTCCOFFSETTRIM, self).__init__(register,
            'SYDTCCOFFSETTRIM', 'RAC_NS.SYTRIM2.SYDTCCOFFSETTRIM', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM2_SYDTCREGTRIMVTTRACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM2_SYDTCREGTRIMVTTRACK, self).__init__(register,
            'SYDTCREGTRIMVTTRACK', 'RAC_NS.SYTRIM2.SYDTCREGTRIMVTTRACK', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM2_SYTDCTRIMPERLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM2_SYTDCTRIMPERLOAD, self).__init__(register,
            'SYTDCTRIMPERLOAD', 'RAC_NS.SYTRIM2.SYTDCTRIMPERLOAD', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYTRIM2_SYVCOREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYTRIM2_SYVCOREGTRIMVREF, self).__init__(register,
            'SYVCOREGTRIMVREF', 'RAC_NS.SYTRIM2.SYVCOREGTRIMVREF', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLFCTRL1_SYDLFVCTRLLOTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLFCTRL1_SYDLFVCTRLLOTH, self).__init__(register,
            'SYDLFVCTRLLOTH', 'RAC_NS.SYDLFCTRL1.SYDLFVCTRLLOTH', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLFCTRL1_SYDLFTDCA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLFCTRL1_SYDLFTDCA2, self).__init__(register,
            'SYDLFTDCA2', 'RAC_NS.SYDLFCTRL1.SYDLFTDCA2', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLFCTRL1_SYDLFVCTRLCMPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLFCTRL1_SYDLFVCTRLCMPRESET, self).__init__(register,
            'SYDLFVCTRLCMPRESET', 'RAC_NS.SYDLFCTRL1.SYDLFVCTRLCMPRESET', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYSTATUS_SYDLFSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYSTATUS_SYDLFSTATE, self).__init__(register,
            'SYDLFSTATE', 'RAC_NS.SYSTATUS.SYDLFSTATE', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYSTATUS_SYDLFLMSP0M(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYSTATUS_SYDLFLMSP0M, self).__init__(register,
            'SYDLFLMSP0M', 'RAC_NS.SYSTATUS.SYDLFLMSP0M', 'read-only',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYSTATUS_SYDLFVCTRLHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYSTATUS_SYDLFVCTRLHI, self).__init__(register,
            'SYDLFVCTRLHI', 'RAC_NS.SYSTATUS.SYDLFVCTRLHI', 'read-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYSTATUS_SYDLFVCTRLLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYSTATUS_SYDLFVCTRLLO, self).__init__(register,
            'SYDLFVCTRLLO', 'RAC_NS.SYSTATUS.SYDLFVCTRLLO', 'read-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYSTATUS_SYDLFPFDLOCKSAMPLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYSTATUS_SYDLFPFDLOCKSAMPLE, self).__init__(register,
            'SYDLFPFDLOCKSAMPLE', 'RAC_NS.SYSTATUS.SYDLFPFDLOCKSAMPLE', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYSTATUS_SYDLFPFDREFLEAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYSTATUS_SYDLFPFDREFLEAD, self).__init__(register,
            'SYDLFPFDREFLEAD', 'RAC_NS.SYSTATUS.SYDLFPFDREFLEAD', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL2_SYDTCREGILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL2_SYDTCREGILOAD, self).__init__(register,
            'SYDTCREGILOAD', 'RAC_NS.SYCTRL2.SYDTCREGILOAD', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL2_SYDTCREGVTTRACKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL2_SYDTCREGVTTRACKSEL, self).__init__(register,
            'SYDTCREGVTTRACKSEL', 'RAC_NS.SYCTRL2.SYDTCREGVTTRACKSEL', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL2_SYLODIVBYPASSIQCLKBIASDELTA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL2_SYLODIVBYPASSIQCLKBIASDELTA, self).__init__(register,
            'SYLODIVBYPASSIQCLKBIASDELTA', 'RAC_NS.SYCTRL2.SYLODIVBYPASSIQCLKBIASDELTA', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL2_SYDSMDACREGTRIMSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL2_SYDSMDACREGTRIMSTBLOAD, self).__init__(register,
            'SYDSMDACREGTRIMSTBLOAD', 'RAC_NS.SYCTRL2.SYDSMDACREGTRIMSTBLOAD', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL2_SYLODIVTRIMIQCLKBIASDELTA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL2_SYLODIVTRIMIQCLKBIASDELTA, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASDELTA', 'RAC_NS.SYCTRL2.SYLODIVTRIMIQCLKBIASDELTA', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL2_SYLODIVTRIMIQCLKBIASNDIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL2_SYLODIVTRIMIQCLKBIASNDIO, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASNDIO', 'RAC_NS.SYCTRL2.SYLODIVTRIMIQCLKBIASNDIO', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL2_SYVCOHCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL2_SYVCOHCAP, self).__init__(register,
            'SYVCOHCAP', 'RAC_NS.SYCTRL2.SYVCOHCAP', 'read-write',
            u"",
            17, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL2_SYVCOACAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL2_SYVCOACAP, self).__init__(register,
            'SYVCOACAP', 'RAC_NS.SYCTRL2.SYVCOACAP', 'read-write',
            u"",
            23, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIATRIM0_TIACAPFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIATRIM0_TIACAPFB, self).__init__(register,
            'TIACAPFB', 'RAC_NS.TIATRIM0.TIACAPFB', 'read-write',
            u"",
            11, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIATRIM0_TIACOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIATRIM0_TIACOMP, self).__init__(register,
            'TIACOMP', 'RAC_NS.TIATRIM0.TIACOMP', 'read-write',
            u"",
            19, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIATRIM0_TIARESFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIATRIM0_TIARESFB, self).__init__(register,
            'TIARESFB', 'RAC_NS.TIATRIM0.TIARESFB', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIATRIM1_TIAOXI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIATRIM1_TIAOXI, self).__init__(register,
            'TIAOXI', 'RAC_NS.TIATRIM1.TIAOXI', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIATRIM1_TIAOXQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIATRIM1_TIAOXQ, self).__init__(register,
            'TIAOXQ', 'RAC_NS.TIATRIM1.TIAOXQ', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIATRIM1_TIASETVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIATRIM1_TIASETVCM, self).__init__(register,
            'TIASETVCM', 'RAC_NS.TIATRIM1.TIASETVCM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAENBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAENBIAS, self).__init__(register,
            'TIAENBIAS', 'RAC_NS.TIAEN.TIAENBIAS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIABIASCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIABIASCURR, self).__init__(register,
            'TIABIASCURR', 'RAC_NS.TIAEN.TIABIASCURR', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAENREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAENREG, self).__init__(register,
            'TIAENREG', 'RAC_NS.TIAEN.TIAENREG', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAENSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAENSTBLOAD, self).__init__(register,
            'TIAENSTBLOAD', 'RAC_NS.TIAEN.TIAENSTBLOAD', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAENLATCHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAENLATCHI, self).__init__(register,
            'TIAENLATCHI', 'RAC_NS.TIAEN.TIAENLATCHI', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAENPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAENPKD, self).__init__(register,
            'TIAENPKD', 'RAC_NS.TIAEN.TIAENPKD', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAENLATCHQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAENLATCHQ, self).__init__(register,
            'TIAENLATCHQ', 'RAC_NS.TIAEN.TIAENLATCHQ', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAVLDOTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAVLDOTRIMVREF, self).__init__(register,
            'TIAVLDOTRIMVREF', 'RAC_NS.TIAEN.TIAVLDOTRIMVREF', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAENTIAI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAENTIAI, self).__init__(register,
            'TIAENTIAI', 'RAC_NS.TIAEN.TIAENTIAI', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAENTIAQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAENTIAQ, self).__init__(register,
            'TIAENTIAQ', 'RAC_NS.TIAEN.TIAENTIAQ', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIATHRPKDLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIATHRPKDLOSEL, self).__init__(register,
            'TIATHRPKDLOSEL', 'RAC_NS.TIAEN.TIATHRPKDLOSEL', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIATHRPKDHISEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIATHRPKDHISEL, self).__init__(register,
            'TIATHRPKDHISEL', 'RAC_NS.TIAEN.TIATHRPKDHISEL', 'read-write',
            u"",
            19, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TIAEN_TIAVLDOTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TIAEN_TIAVLDOTRIMVREG, self).__init__(register,
            'TIAVLDOTRIMVREG', 'RAC_NS.TIAEN.TIAVLDOTRIMVREG', 'read-write',
            u"",
            23, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTRCALBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTRCALBIAS, self).__init__(register,
            'VTRCALBIAS', 'RAC_NS.VTRCTRL0.VTRCALBIAS', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTRCALTC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTRCALTC, self).__init__(register,
            'VTRCALTC', 'RAC_NS.VTRCTRL0.VTRCALTC', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTRDISABLEBOOTSTRAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTRDISABLEBOOTSTRAP, self).__init__(register,
            'VTRDISABLEBOOTSTRAP', 'RAC_NS.VTRCTRL0.VTRDISABLEBOOTSTRAP', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTREN, self).__init__(register,
            'VTREN', 'RAC_NS.VTRCTRL0.VTREN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTRLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTRLDOVREFTRIM, self).__init__(register,
            'VTRLDOVREFTRIM', 'RAC_NS.VTRCTRL0.VTRLDOVREFTRIM', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTRSTARTUPCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTRSTARTUPCORE, self).__init__(register,
            'VTRSTARTUPCORE', 'RAC_NS.VTRCTRL0.VTRSTARTUPCORE', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTRSTARTUPSUPPLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTRSTARTUPSUPPLY, self).__init__(register,
            'VTRSTARTUPSUPPLY', 'RAC_NS.VTRCTRL0.VTRSTARTUPSUPPLY', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTRCALVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTRCALVREF, self).__init__(register,
            'VTRCALVREF', 'RAC_NS.VTRCTRL0.VTRCALVREF', 'read-write',
            u"",
            20, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_VTRCTRL0_VTRHIGHCURRENTHV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_VTRCTRL0_VTRHIGHCURRENTHV, self).__init__(register,
            'VTRHIGHCURRENTHV', 'RAC_NS.VTRCTRL0.VTRHIGHCURRENTHV', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTCURLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTCURLVL1, self).__init__(register,
            'ADCLDOSHUNTCURLVL1', 'RAC_NS.AUXADCCAL.ADCLDOSHUNTCURLVL1', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCAL_ADCLDOSERIESAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCAL_ADCLDOSERIESAMPLVL, self).__init__(register,
            'ADCLDOSERIESAMPLVL', 'RAC_NS.AUXADCCAL.ADCLDOSERIESAMPLVL', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCAL_ADCLDOSERIESAMPLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCAL_ADCLDOSERIESAMPLVL2, self).__init__(register,
            'ADCLDOSERIESAMPLVL2', 'RAC_NS.AUXADCCAL.ADCLDOSERIESAMPLVL2', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTAMPLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTAMPLVL1, self).__init__(register,
            'ADCLDOSHUNTAMPLVL1', 'RAC_NS.AUXADCCAL.ADCLDOSHUNTAMPLVL1', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTAMPLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCAL_ADCLDOSHUNTAMPLVL2, self).__init__(register,
            'ADCLDOSHUNTAMPLVL2', 'RAC_NS.AUXADCCAL.ADCLDOSHUNTAMPLVL2', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCAL_ADCSIDETONEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCAL_ADCSIDETONEFREQ, self).__init__(register,
            'ADCSIDETONEFREQ', 'RAC_NS.AUXADCCAL.ADCSIDETONEFREQ', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCAL_ADCTRIMCURRINPUTBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCAL_ADCTRIMCURRINPUTBUF, self).__init__(register,
            'ADCTRIMCURRINPUTBUF', 'RAC_NS.AUXADCCAL.ADCTRIMCURRINPUTBUF', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCAL_ADCVCMLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCAL_ADCVCMLVL, self).__init__(register,
            'ADCVCMLVL', 'RAC_NS.AUXADCCAL.ADCVCMLVL', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCCTRLRESERVED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCCTRLRESERVED, self).__init__(register,
            'ADCCTRLRESERVED', 'RAC_NS.AUXADCCTRL.ADCCTRLRESERVED', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCCTRLRESERVEDLV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCCTRLRESERVEDLV, self).__init__(register,
            'ADCCTRLRESERVEDLV', 'RAC_NS.AUXADCCTRL.ADCCTRLRESERVEDLV', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCLOWCUR, self).__init__(register,
            'ADCLOWCUR', 'RAC_NS.AUXADCCTRL.ADCLOWCUR', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCNEGRESCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCNEGRESCURRENT, self).__init__(register,
            'ADCNEGRESCURRENT', 'RAC_NS.AUXADCCTRL.ADCNEGRESCURRENT', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCNEGRESVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCNEGRESVCM, self).__init__(register,
            'ADCNEGRESVCM', 'RAC_NS.AUXADCCTRL.ADCNEGRESVCM', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCOTACURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCOTACURRENT, self).__init__(register,
            'ADCOTACURRENT', 'RAC_NS.AUXADCCTRL.ADCOTACURRENT', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCPMONSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCPMONSELECT, self).__init__(register,
            'ADCPMONSELECT', 'RAC_NS.AUXADCCTRL.ADCPMONSELECT', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCRCCALCOUNTERSTARTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCRCCALCOUNTERSTARTVAL, self).__init__(register,
            'ADCRCCALCOUNTERSTARTVAL', 'RAC_NS.AUXADCCTRL.ADCRCCALCOUNTERSTARTVAL', 'read-write',
            u"",
            20, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCSHORTINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCSHORTINPUT, self).__init__(register,
            'ADCSHORTINPUT', 'RAC_NS.AUXADCCTRL.ADCSHORTINPUT', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCSETVINCM400M(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCSETVINCM400M, self).__init__(register,
            'ADCSETVINCM400M', 'RAC_NS.AUXADCCTRL.ADCSETVINCM400M', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCVCMBUFBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCVCMBUFBYPASS, self).__init__(register,
            'ADCVCMBUFBYPASS', 'RAC_NS.AUXADCCTRL.ADCVCMBUFBYPASS', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL_ADCLDOSERIESFORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL_ADCLDOSERIESFORCEDSTARTUP, self).__init__(register,
            'ADCLDOSERIESFORCEDSTARTUP', 'RAC_NS.AUXADCCTRL.ADCLDOSERIESFORCEDSTARTUP', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL2_ADCENHALFBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL2_ADCENHALFBW, self).__init__(register,
            'ADCENHALFBW', 'RAC_NS.AUXADCCTRL2.ADCENHALFBW', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_AUXADCCTRL2_ADCENHALFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_AUXADCCTRL2_ADCENHALFMODE, self).__init__(register,
            'ADCENHALFMODE', 'RAC_NS.AUXADCCTRL2.ADCENHALFMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXEN0_LNAMIXDISMXR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXEN0_LNAMIXDISMXR1, self).__init__(register,
            'LNAMIXDISMXR1', 'RAC_NS.LNAMIXEN0.LNAMIXDISMXR1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXEN0_LNAMIXENIRCAL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXEN0_LNAMIXENIRCAL1, self).__init__(register,
            'LNAMIXENIRCAL1', 'RAC_NS.LNAMIXEN0.LNAMIXENIRCAL1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_LNAMIXEN0_LNAMIXENREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_LNAMIXEN0_LNAMIXENREG, self).__init__(register,
            'LNAMIXENREG', 'RAC_NS.LNAMIXEN0.LNAMIXENREG', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACEN0DBMPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACEN0DBMPA, self).__init__(register,
            'MIXDACEN0DBMPA', 'RAC_NS.MIXDACEN.MIXDACEN0DBMPA', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENBIASVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENBIASVREGDIG, self).__init__(register,
            'MIXDACENBIASVREGDIG', 'RAC_NS.MIXDACEN.MIXDACENBIASVREGDIG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACEN10DBMPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACEN10DBMPA, self).__init__(register,
            'MIXDACEN10DBMPA', 'RAC_NS.MIXDACEN.MIXDACEN10DBMPA', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENCLKMULT2P4G(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENCLKMULT2P4G, self).__init__(register,
            'MIXDACENCLKMULT2P4G', 'RAC_NS.MIXDACEN.MIXDACENCLKMULT2P4G', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENCORE, self).__init__(register,
            'MIXDACENCORE', 'RAC_NS.MIXDACEN.MIXDACENCORE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGCORE, self).__init__(register,
            'MIXDACENSTBLOADVREGCORE', 'RAC_NS.MIXDACEN.MIXDACENSTBLOADVREGCORE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGDIG, self).__init__(register,
            'MIXDACENSTBLOADVREGDIG', 'RAC_NS.MIXDACEN.MIXDACENSTBLOADVREGDIG', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENBIASVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENBIASVREGCORE, self).__init__(register,
            'MIXDACENBIASVREGCORE', 'RAC_NS.MIXDACEN.MIXDACENBIASVREGCORE', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGCORE, self).__init__(register,
            'MIXDACENVREGCORE', 'RAC_NS.MIXDACEN.MIXDACENVREGCORE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGDIG, self).__init__(register,
            'MIXDACENVREGDIG', 'RAC_NS.MIXDACEN.MIXDACENVREGDIG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENFORCEDSTARTUPVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENFORCEDSTARTUPVREGDIG, self).__init__(register,
            'MIXDACENFORCEDSTARTUPVREGDIG', 'RAC_NS.MIXDACEN.MIXDACENFORCEDSTARTUPVREGDIG', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENIRCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENIRCAL, self).__init__(register,
            'MIXDACENIRCAL', 'RAC_NS.MIXDACEN.MIXDACENIRCAL', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENPOSEDGEDACCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENPOSEDGEDACCLK, self).__init__(register,
            'MIXDACENPOSEDGEDACCLK', 'RAC_NS.MIXDACEN.MIXDACENPOSEDGEDACCLK', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENRFSYNTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENRFSYNTH, self).__init__(register,
            'MIXDACENRFSYNTH', 'RAC_NS.MIXDACEN.MIXDACENRFSYNTH', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGDIGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENSTBLOADVREGDIGREPLICA, self).__init__(register,
            'MIXDACENSTBLOADVREGDIGREPLICA', 'RAC_NS.MIXDACEN.MIXDACENSTBLOADVREGDIGREPLICA', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGDIGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACEN_MIXDACENVREGDIGREPLICA, self).__init__(register,
            'MIXDACENVREGDIGREPLICA', 'RAC_NS.MIXDACEN.MIXDACENVREGDIGREPLICA', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYENDLFVCTRLMONITOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYENDLFVCTRLMONITOR, self).__init__(register,
            'SYENDLFVCTRLMONITOR', 'RAC_NS.SYCTRL1.SYENDLFVCTRLMONITOR', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYENDLFTDCA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYENDLFTDCA2, self).__init__(register,
            'SYENDLFTDCA2', 'RAC_NS.SYCTRL1.SYENDLFTDCA2', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYMMDSELFP4G82G4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYMMDSELFP4G82G4, self).__init__(register,
            'SYMMDSELFP4G82G4', 'RAC_NS.SYCTRL1.SYMMDSELFP4G82G4', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYLODIVREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYLODIVREGTRIMVREF, self).__init__(register,
            'SYLODIVREGTRIMVREF', 'RAC_NS.SYCTRL1.SYLODIVREGTRIMVREF', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYDSMDACREGILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYDSMDACREGILOAD, self).__init__(register,
            'SYDSMDACREGILOAD', 'RAC_NS.SYCTRL1.SYDSMDACREGILOAD', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYLODIVSELFCALCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYLODIVSELFCALCLK, self).__init__(register,
            'SYLODIVSELFCALCLK', 'RAC_NS.SYCTRL1.SYLODIVSELFCALCLK', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYENDLF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYENDLF, self).__init__(register,
            'SYENDLF', 'RAC_NS.SYCTRL1.SYENDLF', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYLODIVFCALRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYLODIVFCALRD, self).__init__(register,
            'SYLODIVFCALRD', 'RAC_NS.SYCTRL1.SYLODIVFCALRD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYVCOACAPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYVCOACAPFORCE, self).__init__(register,
            'SYVCOACAPFORCE', 'RAC_NS.SYCTRL1.SYVCOACAPFORCE', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYLODIVDSMDACCLKDIVRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYLODIVDSMDACCLKDIVRATIO, self).__init__(register,
            'SYLODIVDSMDACCLKDIVRATIO', 'RAC_NS.SYCTRL1.SYLODIVDSMDACCLKDIVRATIO', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYENDLFDQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYENDLFDQNC, self).__init__(register,
            'SYENDLFDQNC', 'RAC_NS.SYCTRL1.SYENDLFDQNC', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYLODIVFCALCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYLODIVFCALCLR, self).__init__(register,
            'SYLODIVFCALCLR', 'RAC_NS.SYCTRL1.SYLODIVFCALCLR', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYLODIVSMUXCLKDIVRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYLODIVSMUXCLKDIVRATIO, self).__init__(register,
            'SYLODIVSMUXCLKDIVRATIO', 'RAC_NS.SYCTRL1.SYLODIVSMUXCLKDIVRATIO', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYENDSMDACREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYENDSMDACREG, self).__init__(register,
            'SYENDSMDACREG', 'RAC_NS.SYCTRL1.SYENDSMDACREG', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYENVCOREGLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYENVCOREGLOAD, self).__init__(register,
            'SYENVCOREGLOAD', 'RAC_NS.SYCTRL1.SYENVCOREGLOAD', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYLODIVTRIMIQCLKBIASIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYLODIVTRIMIQCLKBIASIBIAS, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASIBIAS', 'RAC_NS.SYCTRL1.SYLODIVTRIMIQCLKBIASIBIAS', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYLODIVSELFP4G82G4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYLODIVSELFP4G82G4, self).__init__(register,
            'SYLODIVSELFP4G82G4', 'RAC_NS.SYCTRL1.SYLODIVSELFP4G82G4', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYMMDREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYMMDREGTRIMVREF, self).__init__(register,
            'SYMMDREGTRIMVREF', 'RAC_NS.SYCTRL1.SYMMDREGTRIMVREF', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYVCOFASTSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYVCOFASTSTARTUP, self).__init__(register,
            'SYVCOFASTSTARTUP', 'RAC_NS.SYCTRL1.SYVCOFASTSTARTUP', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYMMDCLKINJXOINTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYMMDCLKINJXOINTN, self).__init__(register,
            'SYMMDCLKINJXOINTN', 'RAC_NS.SYCTRL1.SYMMDCLKINJXOINTN', 'read-write',
            u"",
            28, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYMMDCLKINJXOINTNFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYMMDCLKINJXOINTNFORCE, self).__init__(register,
            'SYMMDCLKINJXOINTNFORCE', 'RAC_NS.SYCTRL1.SYMMDCLKINJXOINTNFORCE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL1_SYENDSMDAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL1_SYENDSMDAC, self).__init__(register,
            'SYENDSMDAC', 'RAC_NS.SYCTRL1.SYENDSMDAC', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYDLFCLAMPTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYDLFCLAMPTH, self).__init__(register,
            'SYDLFCLAMPTH', 'RAC_NS.SYCTRL3.SYDLFCLAMPTH', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYDLFREADXI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYDLFREADXI, self).__init__(register,
            'SYDLFREADXI', 'RAC_NS.SYCTRL3.SYDLFREADXI', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYDLFREADXF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYDLFREADXF, self).__init__(register,
            'SYDLFREADXF', 'RAC_NS.SYCTRL3.SYDLFREADXF', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYDLFDQNCGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYDLFDQNCGAIN, self).__init__(register,
            'SYDLFDQNCGAIN', 'RAC_NS.SYCTRL3.SYDLFDQNCGAIN', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYDLFREADACAPCK2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYDLFREADACAPCK2, self).__init__(register,
            'SYDLFREADACAPCK2', 'RAC_NS.SYCTRL3.SYDLFREADACAPCK2', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYLODIVFCALRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYLODIVFCALRUN, self).__init__(register,
            'SYLODIVFCALRUN', 'RAC_NS.SYCTRL3.SYLODIVFCALRUN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYVCOHCAPRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYVCOHCAPRETIME, self).__init__(register,
            'SYVCOHCAPRETIME', 'RAC_NS.SYCTRL3.SYVCOHCAPRETIME', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYDSMDACREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYDSMDACREGTRIMVREF, self).__init__(register,
            'SYDSMDACREGTRIMVREF', 'RAC_NS.SYCTRL3.SYDSMDACREGTRIMVREF', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYCTRL3_SYMMDDENOM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYCTRL3_SYMMDDENOM, self).__init__(register,
            'SYMMDDENOM', 'RAC_NS.SYCTRL3.SYMMDDENOM', 'read-write',
            u"",
            13, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF_SYDLFDACVALTHM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF_SYDLFDACVALTHM, self).__init__(register,
            'SYDLFDACVALTHM', 'RAC_NS.SYDLF.SYDLFDACVALTHM', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF_SYDLFVCTRLHITH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF_SYDLFVCTRLHITH, self).__init__(register,
            'SYDLFVCTRLHITH', 'RAC_NS.SYDLF.SYDLFVCTRLHITH', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF_SYDLFLPFBWZP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF_SYDLFLPFBWZP, self).__init__(register,
            'SYDLFLPFBWZP', 'RAC_NS.SYDLF.SYDLFLPFBWZP', 'read-write',
            u"",
            10, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF_SYDLFLPFBWLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF_SYDLFLPFBWLOAD, self).__init__(register,
            'SYDLFLPFBWLOAD', 'RAC_NS.SYDLF.SYDLFLPFBWLOAD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF_SYDLFDACVALBIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF_SYDLFDACVALBIN, self).__init__(register,
            'SYDLFDACVALBIN', 'RAC_NS.SYDLF.SYDLFDACVALBIN', 'read-write',
            u"",
            22, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPAREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPAREG, self).__init__(register,
            'TX0DBMENPAREG', 'RAC_NS.TX0DBMEN.TX0DBMENPAREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRVREG, self).__init__(register,
            'TX0DBMENPREDRVREG', 'RAC_NS.TX0DBMEN.TX0DBMENPREDRVREG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRV, self).__init__(register,
            'TX0DBMENPREDRV', 'RAC_NS.TX0DBMEN.TX0DBMENPREDRV', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENLOADREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENLOADREGPREDRV, self).__init__(register,
            'TX0DBMENLOADREGPREDRV', 'RAC_NS.TX0DBMEN.TX0DBMENLOADREGPREDRV', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENLOADREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENLOADREGPA, self).__init__(register,
            'TX0DBMENLOADREGPA', 'RAC_NS.TX0DBMEN.TX0DBMENLOADREGPA', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENBYPASSREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENBYPASSREGPA, self).__init__(register,
            'TX0DBMENBYPASSREGPA', 'RAC_NS.TX0DBMEN.TX0DBMENBYPASSREGPA', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENBIASREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENBIASREGPREDRV, self).__init__(register,
            'TX0DBMENBIASREGPREDRV', 'RAC_NS.TX0DBMEN.TX0DBMENBIASREGPREDRV', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENREPLICABIASREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENREPLICABIASREGPA, self).__init__(register,
            'TX0DBMENREPLICABIASREGPA', 'RAC_NS.TX0DBMEN.TX0DBMENREPLICABIASREGPA', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPA, self).__init__(register,
            'TX0DBMENPA', 'RAC_NS.TX0DBMEN.TX0DBMENPA', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPAREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPAREGSTBLOAD, self).__init__(register,
            'TX0DBMENPAREGSTBLOAD', 'RAC_NS.TX0DBMEN.TX0DBMENPAREGSTBLOAD', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRVREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMEN_TX0DBMENPREDRVREGSTBLOAD, self).__init__(register,
            'TX0DBMENPREDRVREGSTBLOAD', 'RAC_NS.TX0DBMEN.TX0DBMENPREDRVREGSTBLOAD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMPOWER, self).__init__(register,
            'TX0DBMPOWER', 'RAC_NS.TX0DBMCTRL.TX0DBMPOWER', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMLATCHBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMLATCHBYPASS, self).__init__(register,
            'TX0DBMLATCHBYPASS', 'RAC_NS.TX0DBMCTRL.TX0DBMLATCHBYPASS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMSLICERESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMCTRL_TX0DBMSLICERESET, self).__init__(register,
            'TX0DBMSLICERESET', 'RAC_NS.TX0DBMCTRL.TX0DBMSLICERESET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPREDRV, self).__init__(register,
            'TX0DBMTRIMPSRBSTREGPREDRV', 'RAC_NS.TX0DBMTRIM.TX0DBMTRIMPSRBSTREGPREDRV', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPREDRVSLOPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPREDRVSLOPE, self).__init__(register,
            'TX0DBMTRIMPREDRVSLOPE', 'RAC_NS.TX0DBMTRIM.TX0DBMTRIMPREDRVSLOPE', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPA, self).__init__(register,
            'TX0DBMTRIMPSRBSTREGPA', 'RAC_NS.TX0DBMTRIM.TX0DBMTRIMPSRBSTREGPA', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMTAPCAP100F(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMTAPCAP100F, self).__init__(register,
            'TX0DBMTRIMTAPCAP100F', 'RAC_NS.TX0DBMTRIM.TX0DBMTRIMTAPCAP100F', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMTAPCAP200F(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMTAPCAP200F, self).__init__(register,
            'TX0DBMTRIMTAPCAP200F', 'RAC_NS.TX0DBMTRIM.TX0DBMTRIMTAPCAP200F', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMVREFREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMVREFREGPA, self).__init__(register,
            'TX0DBMTRIMVREFREGPA', 'RAC_NS.TX0DBMTRIM.TX0DBMTRIMVREFREGPA', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMVREFREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM_TX0DBMTRIMVREFREGPREDRV, self).__init__(register,
            'TX0DBMTRIMVREFREGPREDRV', 'RAC_NS.TX0DBMTRIM.TX0DBMTRIMVREFREGPREDRV', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMDUTYCYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMDUTYCYN, self).__init__(register,
            'TX0DBMTRIMDUTYCYN', 'RAC_NS.TX0DBMTRIM0.TX0DBMTRIMDUTYCYN', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMNBIASPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMNBIASPA, self).__init__(register,
            'TX0DBMTRIMNBIASPA', 'RAC_NS.TX0DBMTRIM0.TX0DBMTRIMNBIASPA', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMPBIASPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMPBIASPA, self).__init__(register,
            'TX0DBMTRIMPBIASPA', 'RAC_NS.TX0DBMTRIM0.TX0DBMTRIMPBIASPA', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMRFBREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMRFBREGPA, self).__init__(register,
            'TX0DBMTRIMRFBREGPA', 'RAC_NS.TX0DBMTRIM0.TX0DBMTRIMRFBREGPA', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMDUTYCYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX0DBMTRIM0_TX0DBMTRIMDUTYCYP, self).__init__(register,
            'TX0DBMTRIMDUTYCYP', 'RAC_NS.TX0DBMTRIM0.TX0DBMTRIMDUTYCYP', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPA, self).__init__(register,
            'TX10DBMENPA', 'RAC_NS.TX10DBMEN.TX10DBMENPA', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREG, self).__init__(register,
            'TX10DBMENPAREG', 'RAC_NS.TX10DBMEN.TX10DBMENPAREG', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRV, self).__init__(register,
            'TX10DBMENPREDRV', 'RAC_NS.TX10DBMEN.TX10DBMENPREDRV', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRVREG, self).__init__(register,
            'TX10DBMENPREDRVREG', 'RAC_NS.TX10DBMEN.TX10DBMENPREDRVREG', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGPULLDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGPULLDOWN, self).__init__(register,
            'TX10DBMENPAREGPULLDOWN', 'RAC_NS.TX10DBMEN.TX10DBMENPAREGPULLDOWN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGSTBLOAD, self).__init__(register,
            'TX10DBMENPAREGSTBLOAD', 'RAC_NS.TX10DBMEN.TX10DBMENPAREGSTBLOAD', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGSTBLOADAUTO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAREGSTBLOADAUTO, self).__init__(register,
            'TX10DBMENPAREGSTBLOADAUTO', 'RAC_NS.TX10DBMEN.TX10DBMENPAREGSTBLOADAUTO', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAOUTBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPAOUTBIAS, self).__init__(register,
            'TX10DBMENPAOUTBIAS', 'RAC_NS.TX10DBMEN.TX10DBMENPAOUTBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENRXPADATTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENRXPADATTN, self).__init__(register,
            'TX10DBMENRXPADATTN', 'RAC_NS.TX10DBMEN.TX10DBMENRXPADATTN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRVREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMEN_TX10DBMENPREDRVREGSTBLOAD, self).__init__(register,
            'TX10DBMENPREDRVREGSTBLOAD', 'RAC_NS.TX10DBMEN.TX10DBMENPREDRVREGSTBLOAD', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMPOWER, self).__init__(register,
            'TX10DBMPOWER', 'RAC_NS.TX10DBMCTRL1.TX10DBMPOWER', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMSLICERST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMSLICERST, self).__init__(register,
            'TX10DBMSLICERST', 'RAC_NS.TX10DBMCTRL1.TX10DBMSLICERST', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMRXPADATTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMRXPADATTN, self).__init__(register,
            'TX10DBMRXPADATTN', 'RAC_NS.TX10DBMCTRL1.TX10DBMRXPADATTN', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMRAMPCLKBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMCTRL1_TX10DBMRAMPCLKBYPASS, self).__init__(register,
            'TX10DBMRAMPCLKBYPASS', 'RAC_NS.TX10DBMCTRL1.TX10DBMRAMPCLKBYPASS', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTX_TX10DBMTRIMHFCTAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTX_TX10DBMTRIMHFCTAP, self).__init__(register,
            'TX10DBMTRIMHFCTAP', 'RAC_NS.TX10DBMTX.TX10DBMTRIMHFCTAP', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASDION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASDION, self).__init__(register,
            'TX10DBMTRIMBIASDION', 'RAC_NS.TX10DBMTRIM1.TX10DBMTRIMBIASDION', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASDIOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASDIOP, self).__init__(register,
            'TX10DBMTRIMBIASDIOP', 'RAC_NS.TX10DBMTRIM1.TX10DBMTRIMBIASDIOP', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMNSWBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMNSWBIAS, self).__init__(register,
            'TX10DBMTRIMNSWBIAS', 'RAC_NS.TX10DBMTRIM1.TX10DBMTRIMNSWBIAS', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMPSWBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMPSWBIAS, self).__init__(register,
            'TX10DBMTRIMPSWBIAS', 'RAC_NS.TX10DBMTRIM1.TX10DBMTRIMPSWBIAS', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASN, self).__init__(register,
            'TX10DBMTRIMBIASN', 'RAC_NS.TX10DBMTRIM1.TX10DBMTRIMBIASN', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMDUTYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMDUTYN, self).__init__(register,
            'TX10DBMTRIMDUTYN', 'RAC_NS.TX10DBMTRIM1.TX10DBMTRIMDUTYN', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMBIASP, self).__init__(register,
            'TX10DBMTRIMBIASP', 'RAC_NS.TX10DBMTRIM1.TX10DBMTRIMBIASP', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMDUTYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM1_TX10DBMTRIMDUTYP, self).__init__(register,
            'TX10DBMTRIMDUTYP', 'RAC_NS.TX10DBMTRIM1.TX10DBMTRIMDUTYP', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGSLICES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGSLICES, self).__init__(register,
            'TX10DBMTRIMPREDRVREGSLICES', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPREDRVREGSLICES', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVSLC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVSLC, self).__init__(register,
            'TX10DBMTRIMPREDRVSLC', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPREDRVSLC', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGPSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGPSR, self).__init__(register,
            'TX10DBMTRIMPREDRVREGPSR', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPREDRVREGPSR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREG, self).__init__(register,
            'TX10DBMTRIMPREDRVREG', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPREDRVREG', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREG, self).__init__(register,
            'TX10DBMTRIMPAREG', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPAREG', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREGVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREGVREF, self).__init__(register,
            'TX10DBMTRIMPAREGVREF', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPAREGVREF', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGVREF, self).__init__(register,
            'TX10DBMTRIMPREDRVREGVREF', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPREDRVREGVREF', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREGPSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPAREGPSR, self).__init__(register,
            'TX10DBMTRIMPAREGPSR', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPAREGPSR', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_TX10DBMTRIM2_TX10DBMTRIMPREDRVCAP, self).__init__(register,
            'TX10DBMTRIMPREDRVCAP', 'RAC_NS.TX10DBMTRIM2.TX10DBMTRIMPREDRVCAP', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVREG, self).__init__(register,
            'PREREGTRIMVREG', 'RAC_NS.PREREGTRIM.PREREGTRIMVREG', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVTRMINIVOLTAGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVTRMINIVOLTAGE, self).__init__(register,
            'PREREGTRIMVTRMINIVOLTAGE', 'RAC_NS.PREREGTRIM.PREREGTRIMVTRMINIVOLTAGE', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMBYPCMPVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMBYPCMPVREF, self).__init__(register,
            'PREREGTRIMBYPCMPVREF', 'RAC_NS.PREREGTRIM.PREREGTRIMBYPCMPVREF', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVTRMINITEMPCO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_PREREGTRIM_PREREGTRIMVTRMINITEMPCO, self).__init__(register,
            'PREREGTRIMVTRMINITEMPCO', 'RAC_NS.PREREGTRIM.PREREGTRIMVTRMINITEMPCO', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_MIXDACTRIM1_MIXDACTRIMBBSUPPLYSERIESRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_MIXDACTRIM1_MIXDACTRIMBBSUPPLYSERIESRES, self).__init__(register,
            'MIXDACTRIMBBSUPPLYSERIESRES', 'RAC_NS.MIXDACTRIM1.MIXDACTRIMBBSUPPLYSERIESRES', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF1_SYDLFTDCDBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF1_SYDLFTDCDBIAS, self).__init__(register,
            'SYDLFTDCDBIAS', 'RAC_NS.SYDLF1.SYDLFTDCDBIAS', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF1_SYDLFPFDLOCKSAMPLETH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF1_SYDLFPFDLOCKSAMPLETH, self).__init__(register,
            'SYDLFPFDLOCKSAMPLETH', 'RAC_NS.SYDLF1.SYDLFPFDLOCKSAMPLETH', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF1_SYDLFDTHIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF1_SYDLFDTHIN, self).__init__(register,
            'SYDLFDTHIN', 'RAC_NS.SYDLF1.SYDLFDTHIN', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SYDLF1_SYDLFPOSITIVECOEFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SYDLF1_SYDLFPOSITIVECOEFF, self).__init__(register,
            'SYDLFPOSITIVECOEFF', 'RAC_NS.SYDLF1.SYDLFPOSITIVECOEFF', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE1_SYZZZSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE1_SYZZZSPARES, self).__init__(register,
            'SYZZZSPARES', 'RAC_NS.SPARE1.SYZZZSPARES', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE1_TIASPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE1_TIASPARE, self).__init__(register,
            'TIASPARE', 'RAC_NS.SPARE1.TIASPARE', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE1_TX10DBMSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE1_TX10DBMSPARE, self).__init__(register,
            'TX10DBMSPARE', 'RAC_NS.SPARE1.TX10DBMSPARE', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_SPARE1_VTRSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_SPARE1_VTRSPARES, self).__init__(register,
            'VTRSPARES', 'RAC_NS.SPARE1.VTRSPARES', 'read-write',
            u"",
            13, 4)
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


class RM_Field_RAC_NS_RFLOCK0_RACTX0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACTX0DBM, self).__init__(register,
            'RACTX0DBM', 'RAC_NS.RFLOCK0.RACTX0DBM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACTX10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACTX10DBM, self).__init__(register,
            'RACTX10DBM', 'RAC_NS.RFLOCK0.RACTX10DBM', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_RACTX20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_RACTX20DBM, self).__init__(register,
            'RACTX20DBM', 'RAC_NS.RFLOCK0.RACTX20DBM', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK0_MODEMHADM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK0_MODEMHADM, self).__init__(register,
            'MODEMHADM', 'RAC_NS.RFLOCK0.MODEMHADM', 'read-write',
            u"",
            21, 1)
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
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_NS_RFLOCK1_RACPASLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_NS_RFLOCK1_RACPASLICE, self).__init__(register,
            'RACPASLICE', 'RAC_NS.RFLOCK1.RACPASLICE', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True



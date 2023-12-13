
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


class RM_Field_RAC_S_STATUS_SEQSLEEPING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_SEQSLEEPING, self).__init__(register,
            'SEQSLEEPING', 'RAC_S.STATUS.SEQSLEEPING', 'read-only',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_SEQSLEEPDEEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_SEQSLEEPDEEP, self).__init__(register,
            'SEQSLEEPDEEP', 'RAC_S.STATUS.SEQSLEEPDEEP', 'read-only',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_STATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_STATE, self).__init__(register,
            'STATE', 'RAC_S.STATUS.STATE', 'read-only',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS_SEQACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS_SEQACTIVE, self).__init__(register,
            'SEQACTIVE', 'RAC_S.STATUS.SEQACTIVE', 'read-only',
            u"",
            28, 1)
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


class RM_Field_RAC_S_CMD_FRCWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_FRCWR, self).__init__(register,
            'FRCWR', 'RAC_S.CMD.FRCWR', 'write-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CMD_FRCRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CMD_FRCRD, self).__init__(register,
            'FRCRD', 'RAC_S.CMD.FRCRD', 'write-only',
            u"",
            11, 1)
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


class RM_Field_RAC_S_CTRL_AHBSYNC0MODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_AHBSYNC0MODE, self).__init__(register,
            'AHBSYNC0MODE', 'RAC_S.CTRL.AHBSYNC0MODE', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_AHBSYNC0REQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_AHBSYNC0REQ, self).__init__(register,
            'AHBSYNC0REQ', 'RAC_S.CTRL.AHBSYNC0REQ', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_AHBSYNC0ACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_AHBSYNC0ACK, self).__init__(register,
            'AHBSYNC0ACK', 'RAC_S.CTRL.AHBSYNC0ACK', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_PRSFORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_PRSFORCETX, self).__init__(register,
            'PRSFORCETX', 'RAC_S.CTRL.PRSFORCETX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_FSMRXABORTHW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_FSMRXABORTHW, self).__init__(register,
            'FSMRXABORTHW', 'RAC_S.CTRL.FSMRXABORTHW', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_FSMRXABORTHWSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_FSMRXABORTHWSYNC, self).__init__(register,
            'FSMRXABORTHWSYNC', 'RAC_S.CTRL.FSMRXABORTHWSYNC', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_FSMRXFRAMEEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_FSMRXFRAMEEND, self).__init__(register,
            'FSMRXFRAMEEND', 'RAC_S.CTRL.FSMRXFRAMEEND', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_FSMDEMODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_FSMDEMODEN, self).__init__(register,
            'FSMDEMODEN', 'RAC_S.CTRL.FSMDEMODEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_FSMWRAPUPNEXTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_FSMWRAPUPNEXTDIS, self).__init__(register,
            'FSMWRAPUPNEXTDIS', 'RAC_S.CTRL.FSMWRAPUPNEXTDIS', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_HYDRARAMCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_HYDRARAMCLKDIS, self).__init__(register,
            'HYDRARAMCLKDIS', 'RAC_S.CTRL.HYDRARAMCLKDIS', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_SEQRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_SEQRESET, self).__init__(register,
            'SEQRESET', 'RAC_S.CTRL.SEQRESET', 'write-only',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_EXITSHUTDOWNDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_EXITSHUTDOWNDIS, self).__init__(register,
            'EXITSHUTDOWNDIS', 'RAC_S.CTRL.EXITSHUTDOWNDIS', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_CPUWAITDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_CPUWAITDIS, self).__init__(register,
            'CPUWAITDIS', 'RAC_S.CTRL.CPUWAITDIS', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_SEQCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_SEQCLKDIS, self).__init__(register,
            'SEQCLKDIS', 'RAC_S.CTRL.SEQCLKDIS', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_AHBSYNC1MODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_AHBSYNC1MODE, self).__init__(register,
            'AHBSYNC1MODE', 'RAC_S.CTRL.AHBSYNC1MODE', 'read-write',
            u"",
            28, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_AHBSYNC1REQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_AHBSYNC1REQ, self).__init__(register,
            'AHBSYNC1REQ', 'RAC_S.CTRL.AHBSYNC1REQ', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CTRL_AHBSYNC1ACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_AHBSYNC1ACK, self).__init__(register,
            'AHBSYNC1ACK', 'RAC_S.CTRL.AHBSYNC1ACK', 'read-only',
            u"",
            31, 1)
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


class RM_Field_RAC_S_IF_SEQLOCKUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_SEQLOCKUP, self).__init__(register,
            'SEQLOCKUP', 'RAC_S.IF.SEQLOCKUP', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IF_SEQRESETREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_SEQRESETREQ, self).__init__(register,
            'SEQRESETREQ', 'RAC_S.IF.SEQRESETREQ', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IF_FSWLOCKUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_FSWLOCKUP, self).__init__(register,
            'FSWLOCKUP', 'RAC_S.IF.FSWLOCKUP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IF_FSWRESETREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_FSWRESETREQ, self).__init__(register,
            'FSWRESETREQ', 'RAC_S.IF.FSWRESETREQ', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IF_SEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IF_SEQ, self).__init__(register,
            'SEQ', 'RAC_S.IF.SEQ', 'read-write',
            u"",
            8, 24)
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


class RM_Field_RAC_S_IEN_SEQLOCKUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_SEQLOCKUP, self).__init__(register,
            'SEQLOCKUP', 'RAC_S.IEN.SEQLOCKUP', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IEN_SEQRESETREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_SEQRESETREQ, self).__init__(register,
            'SEQRESETREQ', 'RAC_S.IEN.SEQRESETREQ', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IEN_FSWLOCKUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_FSWLOCKUP, self).__init__(register,
            'FSWLOCKUP', 'RAC_S.IEN.FSWLOCKUP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IEN_FSWRESETREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_FSWRESETREQ, self).__init__(register,
            'FSWRESETREQ', 'RAC_S.IEN.FSWRESETREQ', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IEN_SEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IEN_SEQ, self).__init__(register,
            'SEQ', 'RAC_S.IEN.SEQ', 'read-write',
            u"",
            8, 24)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TESTCTRL_MODEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TESTCTRL_MODEN, self).__init__(register,
            'MODEN', 'RAC_S.TESTCTRL.MODEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TESTCTRL_DEMODON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TESTCTRL_DEMODON, self).__init__(register,
            'DEMODON', 'RAC_S.TESTCTRL.DEMODON', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATECHANGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATECHANGE, self).__init__(register,
            'STATECHANGE', 'RAC_S.SEQIF.STATECHANGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STIMCMPEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STIMCMPEV, self).__init__(register,
            'STIMCMPEV', 'RAC_S.SEQIF.STIMCMPEV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_DEMODRXREQCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_DEMODRXREQCLR, self).__init__(register,
            'DEMODRXREQCLR', 'RAC_S.SEQIF.DEMODRXREQCLR', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_PRSEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_PRSEVENT, self).__init__(register,
            'PRSEVENT', 'RAC_S.SEQIF.PRSEVENT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATEOFF, self).__init__(register,
            'STATEOFF', 'RAC_S.SEQIF.STATEOFF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXWARM, self).__init__(register,
            'STATERXWARM', 'RAC_S.SEQIF.STATERXWARM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXSEARCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXSEARCH, self).__init__(register,
            'STATERXSEARCH', 'RAC_S.SEQIF.STATERXSEARCH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXFRAME, self).__init__(register,
            'STATERXFRAME', 'RAC_S.SEQIF.STATERXFRAME', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXWRAPUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXWRAPUP, self).__init__(register,
            'STATERXWRAPUP', 'RAC_S.SEQIF.STATERXWRAPUP', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETXWARM, self).__init__(register,
            'STATETXWARM', 'RAC_S.SEQIF.STATETXWARM', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETX, self).__init__(register,
            'STATETX', 'RAC_S.SEQIF.STATETX', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETXWRAPUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETXWRAPUP, self).__init__(register,
            'STATETXWRAPUP', 'RAC_S.SEQIF.STATETXWRAPUP', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATESHUTDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATESHUTDOWN, self).__init__(register,
            'STATESHUTDOWN', 'RAC_S.SEQIF.STATESHUTDOWN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATECHANGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATECHANGE, self).__init__(register,
            'STATECHANGE', 'RAC_S.SEQIEN.STATECHANGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STIMCMPEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STIMCMPEV, self).__init__(register,
            'STIMCMPEV', 'RAC_S.SEQIEN.STIMCMPEV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_DEMODRXREQCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_DEMODRXREQCLR, self).__init__(register,
            'DEMODRXREQCLR', 'RAC_S.SEQIEN.DEMODRXREQCLR', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_PRSEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_PRSEVENT, self).__init__(register,
            'PRSEVENT', 'RAC_S.SEQIEN.PRSEVENT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATEOFF, self).__init__(register,
            'STATEOFF', 'RAC_S.SEQIEN.STATEOFF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXWARM, self).__init__(register,
            'STATERXWARM', 'RAC_S.SEQIEN.STATERXWARM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXSEARCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXSEARCH, self).__init__(register,
            'STATERXSEARCH', 'RAC_S.SEQIEN.STATERXSEARCH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXFRAME, self).__init__(register,
            'STATERXFRAME', 'RAC_S.SEQIEN.STATERXFRAME', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXWRAPUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXWRAPUP, self).__init__(register,
            'STATERXWRAPUP', 'RAC_S.SEQIEN.STATERXWRAPUP', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETXWARM, self).__init__(register,
            'STATETXWARM', 'RAC_S.SEQIEN.STATETXWARM', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETX, self).__init__(register,
            'STATETX', 'RAC_S.SEQIEN.STATETX', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETXWRAPUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETXWRAPUP, self).__init__(register,
            'STATETXWRAPUP', 'RAC_S.SEQIEN.STATETXWRAPUP', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATESHUTDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATESHUTDOWN, self).__init__(register,
            'STATESHUTDOWN', 'RAC_S.SEQIEN.STATESHUTDOWN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS1_TXMASK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS1_TXMASK, self).__init__(register,
            'TXMASK', 'RAC_S.STATUS1.TXMASK', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATECHANGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATECHANGE, self).__init__(register,
            'STATECHANGE', 'RAC_S.FSWIF.STATECHANGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STIMCMPEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STIMCMPEV, self).__init__(register,
            'STIMCMPEV', 'RAC_S.FSWIF.STIMCMPEV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_DEMODRXREQCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_DEMODRXREQCLR, self).__init__(register,
            'DEMODRXREQCLR', 'RAC_S.FSWIF.DEMODRXREQCLR', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_PRSEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_PRSEVENT, self).__init__(register,
            'PRSEVENT', 'RAC_S.FSWIF.PRSEVENT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATEOFF, self).__init__(register,
            'STATEOFF', 'RAC_S.FSWIF.STATEOFF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATERXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATERXWARM, self).__init__(register,
            'STATERXWARM', 'RAC_S.FSWIF.STATERXWARM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATERXSEARCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATERXSEARCH, self).__init__(register,
            'STATERXSEARCH', 'RAC_S.FSWIF.STATERXSEARCH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATERXFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATERXFRAME, self).__init__(register,
            'STATERXFRAME', 'RAC_S.FSWIF.STATERXFRAME', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATERXWRAPUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATERXWRAPUP, self).__init__(register,
            'STATERXWRAPUP', 'RAC_S.FSWIF.STATERXWRAPUP', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATETXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATETXWARM, self).__init__(register,
            'STATETXWARM', 'RAC_S.FSWIF.STATETXWARM', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATETX, self).__init__(register,
            'STATETX', 'RAC_S.FSWIF.STATETX', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATETXWRAPUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATETXWRAPUP, self).__init__(register,
            'STATETXWRAPUP', 'RAC_S.FSWIF.STATETXWRAPUP', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIF_STATESHUTDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIF_STATESHUTDOWN, self).__init__(register,
            'STATESHUTDOWN', 'RAC_S.FSWIF.STATESHUTDOWN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATECHANGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATECHANGE, self).__init__(register,
            'STATECHANGE', 'RAC_S.FSWIEN.STATECHANGE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STIMCMPEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STIMCMPEV, self).__init__(register,
            'STIMCMPEV', 'RAC_S.FSWIEN.STIMCMPEV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_DEMODRXREQCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_DEMODRXREQCLR, self).__init__(register,
            'DEMODRXREQCLR', 'RAC_S.FSWIEN.DEMODRXREQCLR', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_PRSEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_PRSEVENT, self).__init__(register,
            'PRSEVENT', 'RAC_S.FSWIEN.PRSEVENT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATEOFF, self).__init__(register,
            'STATEOFF', 'RAC_S.FSWIEN.STATEOFF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATERXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATERXWARM, self).__init__(register,
            'STATERXWARM', 'RAC_S.FSWIEN.STATERXWARM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATERXSEARCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATERXSEARCH, self).__init__(register,
            'STATERXSEARCH', 'RAC_S.FSWIEN.STATERXSEARCH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATERXFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATERXFRAME, self).__init__(register,
            'STATERXFRAME', 'RAC_S.FSWIEN.STATERXFRAME', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATERXWRAPUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATERXWRAPUP, self).__init__(register,
            'STATERXWRAPUP', 'RAC_S.FSWIEN.STATERXWRAPUP', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATETXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATETXWARM, self).__init__(register,
            'STATETXWARM', 'RAC_S.FSWIEN.STATETXWARM', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATETX, self).__init__(register,
            'STATETX', 'RAC_S.FSWIEN.STATETX', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATETXWRAPUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATETXWRAPUP, self).__init__(register,
            'STATETXWRAPUP', 'RAC_S.FSWIEN.STATETXWRAPUP', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWIEN_STATESHUTDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWIEN_STATESHUTDOWN, self).__init__(register,
            'STATESHUTDOWN', 'RAC_S.FSWIEN.STATESHUTDOWN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXWRAPUPNEXT_TXWRAPUPNEXT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXWRAPUPNEXT_TXWRAPUPNEXT, self).__init__(register,
            'TXWRAPUPNEXT', 'RAC_S.TXWRAPUPNEXT.TXWRAPUPNEXT', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RXWRAPUPNEXT_RXWRAPUPNEXT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RXWRAPUPNEXT_RXWRAPUPNEXT, self).__init__(register,
            'RXWRAPUPNEXT', 'RAC_S.RXWRAPUPNEXT.RXWRAPUPNEXT', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATEOFFSEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATEOFFSEQEND, self).__init__(register,
            'STATEOFFSEQEND', 'RAC_S.SEQEND.STATEOFFSEQEND', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATERXWARMSEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATERXWARMSEQEND, self).__init__(register,
            'STATERXWARMSEQEND', 'RAC_S.SEQEND.STATERXWARMSEQEND', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATERXSEARCHSEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATERXSEARCHSEQEND, self).__init__(register,
            'STATERXSEARCHSEQEND', 'RAC_S.SEQEND.STATERXSEARCHSEQEND', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATERXFRAMESEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATERXFRAMESEQEND, self).__init__(register,
            'STATERXFRAMESEQEND', 'RAC_S.SEQEND.STATERXFRAMESEQEND', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATERXWRAPUPSEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATERXWRAPUPSEQEND, self).__init__(register,
            'STATERXWRAPUPSEQEND', 'RAC_S.SEQEND.STATERXWRAPUPSEQEND', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATETXWARMSEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATETXWARMSEQEND, self).__init__(register,
            'STATETXWARMSEQEND', 'RAC_S.SEQEND.STATETXWARMSEQEND', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATETXSEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATETXSEQEND, self).__init__(register,
            'STATETXSEQEND', 'RAC_S.SEQEND.STATETXSEQEND', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATETXWRAPUPSEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATETXWRAPUPSEQEND, self).__init__(register,
            'STATETXWRAPUPSEQEND', 'RAC_S.SEQEND.STATETXWRAPUPSEQEND', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQEND_STATESHUTDOWNSEQEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQEND_STATESHUTDOWNSEQEND, self).__init__(register,
            'STATESHUTDOWNSEQEND', 'RAC_S.SEQEND.STATESHUTDOWNSEQEND', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATEOFFSEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATEOFFSEQENDEN, self).__init__(register,
            'STATEOFFSEQENDEN', 'RAC_S.SEQENDEN.STATEOFFSEQENDEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATERXWARMSEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATERXWARMSEQENDEN, self).__init__(register,
            'STATERXWARMSEQENDEN', 'RAC_S.SEQENDEN.STATERXWARMSEQENDEN', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATERXSEARCHSEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATERXSEARCHSEQENDEN, self).__init__(register,
            'STATERXSEARCHSEQENDEN', 'RAC_S.SEQENDEN.STATERXSEARCHSEQENDEN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATERXFRAMESEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATERXFRAMESEQENDEN, self).__init__(register,
            'STATERXFRAMESEQENDEN', 'RAC_S.SEQENDEN.STATERXFRAMESEQENDEN', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATERXWRAPUPSEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATERXWRAPUPSEQENDEN, self).__init__(register,
            'STATERXWRAPUPSEQENDEN', 'RAC_S.SEQENDEN.STATERXWRAPUPSEQENDEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATETXWARMSEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATETXWARMSEQENDEN, self).__init__(register,
            'STATETXWARMSEQENDEN', 'RAC_S.SEQENDEN.STATETXWARMSEQENDEN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATETXSEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATETXSEQENDEN, self).__init__(register,
            'STATETXSEQENDEN', 'RAC_S.SEQENDEN.STATETXSEQENDEN', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATETXWRAPUPSEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATETXWRAPUPSEQENDEN, self).__init__(register,
            'STATETXWRAPUPSEQENDEN', 'RAC_S.SEQENDEN.STATETXWRAPUPSEQENDEN', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQENDEN_STATESHUTDOWNSEQENDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQENDEN_STATESHUTDOWNSEQENDEN, self).__init__(register,
            'STATESHUTDOWNSEQENDEN', 'RAC_S.SEQENDEN.STATESHUTDOWNSEQENDEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATEOFFFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATEOFFFRCCLKDIS, self).__init__(register,
            'STATEOFFFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATEOFFFRCCLKDIS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATERXWARMFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATERXWARMFRCCLKDIS, self).__init__(register,
            'STATERXWARMFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATERXWARMFRCCLKDIS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATERXSEARCHFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATERXSEARCHFRCCLKDIS, self).__init__(register,
            'STATERXSEARCHFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATERXSEARCHFRCCLKDIS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATERXFRAMEFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATERXFRAMEFRCCLKDIS, self).__init__(register,
            'STATERXFRAMEFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATERXFRAMEFRCCLKDIS', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATERXWRAPUPFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATERXWRAPUPFRCCLKDIS, self).__init__(register,
            'STATERXWRAPUPFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATERXWRAPUPFRCCLKDIS', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATETXWARMFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATETXWARMFRCCLKDIS, self).__init__(register,
            'STATETXWARMFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATETXWARMFRCCLKDIS', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATETXFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATETXFRCCLKDIS, self).__init__(register,
            'STATETXFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATETXFRCCLKDIS', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATETXWRAPUPFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATETXWRAPUPFRCCLKDIS, self).__init__(register,
            'STATETXWRAPUPFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATETXWRAPUPFRCCLKDIS', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCCLKDIS_STATESHUTDOWNFRCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCCLKDIS_STATESHUTDOWNFRCCLKDIS, self).__init__(register,
            'STATESHUTDOWNFRCCLKDIS', 'RAC_S.FRCCLKDIS.STATESHUTDOWNFRCCLKDIS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATEOFFBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATEOFFBUFCCLKDIS, self).__init__(register,
            'STATEOFFBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATEOFFBUFCCLKDIS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATERXWARMBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATERXWARMBUFCCLKDIS, self).__init__(register,
            'STATERXWARMBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATERXWARMBUFCCLKDIS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATERXSEARCHBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATERXSEARCHBUFCCLKDIS, self).__init__(register,
            'STATERXSEARCHBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATERXSEARCHBUFCCLKDIS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATERXFRAMEBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATERXFRAMEBUFCCLKDIS, self).__init__(register,
            'STATERXFRAMEBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATERXFRAMEBUFCCLKDIS', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATERXWRAPUPBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATERXWRAPUPBUFCCLKDIS, self).__init__(register,
            'STATERXWRAPUPBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATERXWRAPUPBUFCCLKDIS', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATETXWARMBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATETXWARMBUFCCLKDIS, self).__init__(register,
            'STATETXWARMBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATETXWARMBUFCCLKDIS', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATETXBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATETXBUFCCLKDIS, self).__init__(register,
            'STATETXBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATETXBUFCCLKDIS', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATETXWRAPUPBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATETXWRAPUPBUFCCLKDIS, self).__init__(register,
            'STATETXWRAPUPBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATETXWRAPUPBUFCCLKDIS', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_BUFCCLKDIS_STATESHUTDOWNBUFCCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_BUFCCLKDIS_STATESHUTDOWNBUFCCLKDIS, self).__init__(register,
            'STATESHUTDOWNBUFCCLKDIS', 'RAC_S.BUFCCLKDIS.STATESHUTDOWNBUFCCLKDIS', 'read-write',
            u"",
            8, 1)
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


class RM_Field_RAC_S_SEQCTRL_RELATIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_RELATIVE, self).__init__(register,
            'RELATIVE', 'RAC_S.SEQCTRL.RELATIVE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_STIMERALWAYSRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_STIMERALWAYSRUN, self).__init__(register,
            'STIMERALWAYSRUN', 'RAC_S.SEQCTRL.STIMERALWAYSRUN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_STIMERDEBUGRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_STIMERDEBUGRUN, self).__init__(register,
            'STIMERDEBUGRUN', 'RAC_S.SEQCTRL.STIMERDEBUGRUN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_STATEDEBUGRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_STATEDEBUGRUN, self).__init__(register,
            'STATEDEBUGRUN', 'RAC_S.SEQCTRL.STATEDEBUGRUN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQCTRL_SWIRQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQCTRL_SWIRQ, self).__init__(register,
            'SWIRQ', 'RAC_S.SEQCTRL.SWIRQ', 'read-write',
            u"",
            24, 2)
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


class RM_Field_RAC_S_FRCTXWORD_WDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCTXWORD_WDATA, self).__init__(register,
            'WDATA', 'RAC_S.FRCTXWORD.WDATA', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FRCRXWORD_RDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FRCRXWORD_RDATA, self).__init__(register,
            'RDATA', 'RAC_S.FRCRXWORD.RDATA', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_EM1PCSR_RADIOEM1PMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EM1PCSR_RADIOEM1PMODE, self).__init__(register,
            'RADIOEM1PMODE', 'RAC_S.EM1PCSR.RADIOEM1PMODE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_EM1PCSR_RADIOEM1PDISSWREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EM1PCSR_RADIOEM1PDISSWREQ, self).__init__(register,
            'RADIOEM1PDISSWREQ', 'RAC_S.EM1PCSR.RADIOEM1PDISSWREQ', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_EM1PCSR_MCUEM1PMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EM1PCSR_MCUEM1PMODE, self).__init__(register,
            'MCUEM1PMODE', 'RAC_S.EM1PCSR.MCUEM1PMODE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_EM1PCSR_MCUEM1PDISSWREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EM1PCSR_MCUEM1PDISSWREQ, self).__init__(register,
            'MCUEM1PDISSWREQ', 'RAC_S.EM1PCSR.MCUEM1PDISSWREQ', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_EM1PCSR_RADIOEM1PREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EM1PCSR_RADIOEM1PREQ, self).__init__(register,
            'RADIOEM1PREQ', 'RAC_S.EM1PCSR.RADIOEM1PREQ', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_EM1PCSR_RADIOEM1PACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EM1PCSR_RADIOEM1PACK, self).__init__(register,
            'RADIOEM1PACK', 'RAC_S.EM1PCSR.RADIOEM1PACK', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_EM1PCSR_RADIOEM1PHWREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EM1PCSR_RADIOEM1PHWREQ, self).__init__(register,
            'RADIOEM1PHWREQ', 'RAC_S.EM1PCSR.RADIOEM1PHWREQ', 'read-only',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_HYDRARAMREMAP_HYDRARAMREMAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_HYDRARAMREMAP_HYDRARAMREMAP, self).__init__(register,
            'HYDRARAMREMAP', 'RAC_S.HYDRARAMREMAP.HYDRARAMREMAP', 'read-write',
            u"",
            0, 9)
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


class RM_Field_RAC_S_STATUS2_CURRSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS2_CURRSTATE, self).__init__(register,
            'CURRSTATE', 'RAC_S.STATUS2.CURRSTATE', 'read-only',
            u"",
            12, 4)
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


class RM_Field_RAC_S_PAENCTRL_INVRAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PAENCTRL_INVRAMPCLK, self).__init__(register,
            'INVRAMPCLK', 'RAC_S.PAENCTRL.INVRAMPCLK', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PAENCTRL_DIV2RAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PAENCTRL_DIV2RAMPCLK, self).__init__(register,
            'DIV2RAMPCLK', 'RAC_S.PAENCTRL.DIV2RAMPCLK', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PAENCTRL_RSTDIV2RAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PAENCTRL_RSTDIV2RAMPCLK, self).__init__(register,
            'RSTDIV2RAMPCLK', 'RAC_S.PAENCTRL.RSTDIV2RAMPCLK', 'read-write',
            u"",
            18, 1)
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


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN1, self).__init__(register,
            'INTDIVLNAMIXEN1', 'RAC_S.ANTDIV.INTDIVLNAMIXEN1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFATTDCEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFATTDCEN1, self).__init__(register,
            'INTDIVLNAMIXRFATTDCEN1', 'RAC_S.ANTDIV.INTDIVLNAMIXRFATTDCEN1', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFPKDENRF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFPKDENRF1, self).__init__(register,
            'INTDIVLNAMIXRFPKDENRF1', 'RAC_S.ANTDIV.INTDIVLNAMIXRFPKDENRF1', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_ANTDIVSTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_ANTDIVSTATUS, self).__init__(register,
            'ANTDIVSTATUS', 'RAC_S.ANTDIV.ANTDIVSTATUS', 'read-only',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSE, self).__init__(register,
            'AUXADCENTSENSE', 'RAC_S.AUXADCEN.AUXADCENTSENSE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSECAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENTSENSECAL, self).__init__(register,
            'AUXADCENTSENSECAL', 'RAC_S.AUXADCEN.AUXADCENTSENSECAL', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENAUXADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENAUXADC, self).__init__(register,
            'AUXADCENAUXADC', 'RAC_S.AUXADCEN.AUXADCENAUXADC', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_AUXADCENINPUTBUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENINPUTBUFFER, self).__init__(register,
            'AUXADCENINPUTBUFFER', 'RAC_S.AUXADCEN.AUXADCENINPUTBUFFER', 'read-write',
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


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTRESSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTRESSEL, self).__init__(register,
            'AUXADCINPUTRESSEL', 'RAC_S.AUXADCCTRL1.AUXADCINPUTRESSEL', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSESELVBE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSESELVBE, self).__init__(register,
            'AUXADCTSENSESELVBE', 'RAC_S.AUXADCCTRL1.AUXADCTSENSESELVBE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTBUFFERBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTBUFFERBYPASS, self).__init__(register,
            'AUXADCINPUTBUFFERBYPASS', 'RAC_S.AUXADCCTRL1.AUXADCINPUTBUFFERBYPASS', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCINPUTSELECT, self).__init__(register,
            'AUXADCINPUTSELECT', 'RAC_S.AUXADCCTRL1.AUXADCINPUTSELECT', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSETRIMVBE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCTSENSETRIMVBE2, self).__init__(register,
            'AUXADCTSENSETRIMVBE2', 'RAC_S.AUXADCCTRL1.AUXADCTSENSETRIMVBE2', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCPMONSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCPMONSELECT, self).__init__(register,
            'AUXADCPMONSELECT', 'RAC_S.AUXADCCTRL1.AUXADCPMONSELECT', 'read-write',
            u"",
            11, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCENVOLTSCALING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCENVOLTSCALING, self).__init__(register,
            'AUXADCENVOLTSCALING', 'RAC_S.AUXADCCTRL1.AUXADCENVOLTSCALING', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCOUT_AUXADCOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCOUT_AUXADCOUT, self).__init__(register,
            'AUXADCOUT', 'RAC_S.AUXADCOUT.AUXADCOUT', 'read-only',
            u"",
            0, 28)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTDISICO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTDISICO, self).__init__(register,
            'CLKMULTDISICO', 'RAC_S.CLKMULTEN0.CLKMULTDISICO', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBDET, self).__init__(register,
            'CLKMULTENBBDET', 'RAC_S.CLKMULTEN0.CLKMULTENBBDET', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXLDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXLDET, self).__init__(register,
            'CLKMULTENBBXLDET', 'RAC_S.CLKMULTEN0.CLKMULTENBBXLDET', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXMDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBBXMDET, self).__init__(register,
            'CLKMULTENBBXMDET', 'RAC_S.CLKMULTEN0.CLKMULTENBBXMDET', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDFNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDFNIB, self).__init__(register,
            'CLKMULTLDFNIB', 'RAC_S.CLKMULTEN0.CLKMULTLDFNIB', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENCFDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENCFDET, self).__init__(register,
            'CLKMULTENCFDET', 'RAC_S.CLKMULTEN0.CLKMULTENCFDET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDMNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDMNIB, self).__init__(register,
            'CLKMULTLDMNIB', 'RAC_S.CLKMULTEN0.CLKMULTLDMNIB', 'read-write',
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


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTRDNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTRDNIBBLE, self).__init__(register,
            'CLKMULTRDNIBBLE', 'RAC_S.CLKMULTEN0.CLKMULTRDNIBBLE', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVN, self).__init__(register,
            'CLKMULTENDRVN', 'RAC_S.CLKMULTEN0.CLKMULTENDRVN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDCNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTLDCNIB, self).__init__(register,
            'CLKMULTLDCNIB', 'RAC_S.CLKMULTEN0.CLKMULTLDCNIB', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVADC, self).__init__(register,
            'CLKMULTENDRVADC', 'RAC_S.CLKMULTEN0.CLKMULTENDRVADC', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVP, self).__init__(register,
            'CLKMULTENDRVP', 'RAC_S.CLKMULTEN0.CLKMULTENDRVP', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENFBDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENFBDIV, self).__init__(register,
            'CLKMULTENFBDIV', 'RAC_S.CLKMULTEN0.CLKMULTENFBDIV', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREFDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREFDIV, self).__init__(register,
            'CLKMULTENREFDIV', 'RAC_S.CLKMULTEN0.CLKMULTENREFDIV', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1, self).__init__(register,
            'CLKMULTENREG1', 'RAC_S.CLKMULTEN0.CLKMULTENREG1', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG2, self).__init__(register,
            'CLKMULTENREG2', 'RAC_S.CLKMULTEN0.CLKMULTENREG2', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVDAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVDAC, self).__init__(register,
            'CLKMULTENDRVDAC', 'RAC_S.CLKMULTEN0.CLKMULTENDRVDAC', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENROTDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENROTDET, self).__init__(register,
            'CLKMULTENROTDET', 'RAC_S.CLKMULTEN0.CLKMULTENROTDET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBYPASS40MHZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENBYPASS40MHZ, self).__init__(register,
            'CLKMULTENBYPASS40MHZ', 'RAC_S.CLKMULTEN0.CLKMULTENBYPASS40MHZ', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVIRCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVIRCAL, self).__init__(register,
            'CLKMULTENDRVIRCAL', 'RAC_S.CLKMULTEN0.CLKMULTENDRVIRCAL', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1FORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1FORCEDSTARTUP, self).__init__(register,
            'CLKMULTENREG1FORCEDSTARTUP', 'RAC_S.CLKMULTEN0.CLKMULTENREG1FORCEDSTARTUP', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1IBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1IBIAS, self).__init__(register,
            'CLKMULTENREG1IBIAS', 'RAC_S.CLKMULTEN0.CLKMULTENREG1IBIAS', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1REPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1REPLICA, self).__init__(register,
            'CLKMULTENREG1REPLICA', 'RAC_S.CLKMULTEN0.CLKMULTENREG1REPLICA', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1STBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1STBLOAD, self).__init__(register,
            'CLKMULTENREG1STBLOAD', 'RAC_S.CLKMULTEN0.CLKMULTENREG1STBLOAD', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTEST, self).__init__(register,
            'CLKMULTENDRVTEST', 'RAC_S.CLKMULTEN0.CLKMULTENDRVTEST', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTINNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTINNIBBLE, self).__init__(register,
            'CLKMULTINNIBBLE', 'RAC_S.CLKMULTEN1.CLKMULTINNIBBLE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTBWCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTBWCAL, self).__init__(register,
            'CLKMULTBWCAL', 'RAC_S.CLKMULTEN1.CLKMULTBWCAL', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTDRVAMPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTDRVAMPSEL, self).__init__(register,
            'CLKMULTDRVAMPSEL', 'RAC_S.CLKMULTEN1.CLKMULTDRVAMPSEL', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTILOADREG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTILOADREG2, self).__init__(register,
            'CLKMULTILOADREG2', 'RAC_S.CLKMULTEN1.CLKMULTILOADREG2', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVN, self).__init__(register,
            'CLKMULTDIVN', 'RAC_S.CLKMULTEN1.CLKMULTDIVN', 'read-write',
            u"",
            15, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTFREQCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTFREQCAL, self).__init__(register,
            'CLKMULTFREQCAL', 'RAC_S.CLKMULTEN1.CLKMULTFREQCAL', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVR, self).__init__(register,
            'CLKMULTDIVR', 'RAC_S.CLKMULTEN1.CLKMULTDIVR', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVX, self).__init__(register,
            'CLKMULTDIVX', 'RAC_S.CLKMULTEN1.CLKMULTDIVX', 'read-write',
            u"",
            27, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTENRESYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTENRESYNC, self).__init__(register,
            'CLKMULTENRESYNC', 'RAC_S.CLKMULTCTRL.CLKMULTENRESYNC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTVALID, self).__init__(register,
            'CLKMULTVALID', 'RAC_S.CLKMULTCTRL.CLKMULTVALID', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTRESETPHFRQDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTRESETPHFRQDET, self).__init__(register,
            'CLKMULTRESETPHFRQDET', 'RAC_S.CLKMULTCTRL.CLKMULTRESETPHFRQDET', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREF1, self).__init__(register,
            'CLKMULTTRIMVREF1', 'RAC_S.CLKMULTCTRL.CLKMULTTRIMVREF1', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREF2, self).__init__(register,
            'CLKMULTTRIMVREF2', 'RAC_S.CLKMULTCTRL.CLKMULTTRIMVREF2', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREG1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMVREG1, self).__init__(register,
            'CLKMULTTRIMVREG1', 'RAC_S.CLKMULTCTRL.CLKMULTTRIMVREG1', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMREG2IBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTCTRL_CLKMULTTRIMREG2IBIAS, self).__init__(register,
            'CLKMULTTRIMREG2IBIAS', 'RAC_S.CLKMULTCTRL.CLKMULTTRIMREG2IBIAS', 'read-write',
            u"",
            11, 3)
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


class RM_Field_RAC_S_ADCSTATUS_ADCRCCALOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCSTATUS_ADCRCCALOUT, self).__init__(register,
            'ADCRCCALOUT', 'RAC_S.ADCSTATUS.ADCRCCALOUT', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXTRIMVREG, self).__init__(register,
            'LNAMIXTRIMVREG', 'RAC_S.LNAMIXTRIM0.LNAMIXTRIMVREG', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXIRCAL1AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXIRCAL1AMP, self).__init__(register,
            'LNAMIXIRCAL1AMP', 'RAC_S.LNAMIXTRIM0.LNAMIXIRCAL1AMP', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXENREGVHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXENREGVHIGH, self).__init__(register,
            'LNAMIXENREGVHIGH', 'RAC_S.LNAMIXTRIM0.LNAMIXENREGVHIGH', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXLNA1CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXLNA1CAPSEL, self).__init__(register,
            'LNAMIXLNA1CAPSEL', 'RAC_S.LNAMIXTRIM0.LNAMIXLNA1CAPSEL', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXRFPKDBWSEL, self).__init__(register,
            'LNAMIXRFPKDBWSEL', 'RAC_S.LNAMIXTRIM0.LNAMIXRFPKDBWSEL', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXMXRBIAS1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXMXRBIAS1, self).__init__(register,
            'LNAMIXMXRBIAS1', 'RAC_S.LNAMIXTRIM0.LNAMIXMXRBIAS1', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXIBIAS1TRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXIBIAS1TRIM, self).__init__(register,
            'LNAMIXIBIAS1TRIM', 'RAC_S.LNAMIXTRIM0.LNAMIXIBIAS1TRIM', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXTRIMLOW1EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXTRIMLOW1EN, self).__init__(register,
            'LNAMIXTRIMLOW1EN', 'RAC_S.LNAMIXTRIM0.LNAMIXTRIMLOW1EN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXNCAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXNCAS1ADJ, self).__init__(register,
            'LNAMIXNCAS1ADJ', 'RAC_S.LNAMIXTRIM0.LNAMIXNCAS1ADJ', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXRFPKDCALCMLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXRFPKDCALCMLO, self).__init__(register,
            'LNAMIXRFPKDCALCMLO', 'RAC_S.LNAMIXTRIM1.LNAMIXRFPKDCALCMLO', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXRFPKDCALCMHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXRFPKDCALCMHI, self).__init__(register,
            'LNAMIXRFPKDCALCMHI', 'RAC_S.LNAMIXTRIM1.LNAMIXRFPKDCALCMHI', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXENMXRBIASCAL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXENMXRBIASCAL1, self).__init__(register,
            'LNAMIXENMXRBIASCAL1', 'RAC_S.LNAMIXCAL.LNAMIXENMXRBIASCAL1', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGBYPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGBYPFORCE, self).__init__(register,
            'PREREGBYPFORCE', 'RAC_S.PRECTRL.PREREGBYPFORCE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGENBYPCMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGENBYPCMP, self).__init__(register,
            'PREREGENBYPCMP', 'RAC_S.PRECTRL.PREREGENBYPCMP', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGENINTBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGENINTBIAS, self).__init__(register,
            'PREREGENINTBIAS', 'RAC_S.PRECTRL.PREREGENINTBIAS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGENVTRMINI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGENVTRMINI, self).__init__(register,
            'PREREGENVTRMINI', 'RAC_S.PRECTRL.PREREGENVTRMINI', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGENVTRMINISTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGENVTRMINISTARTUP, self).__init__(register,
            'PREREGENVTRMINISTARTUP', 'RAC_S.PRECTRL.PREREGENVTRMINISTARTUP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGPOWERSEQUENCEFLAG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGPOWERSEQUENCEFLAG, self).__init__(register,
            'PREREGPOWERSEQUENCEFLAG', 'RAC_S.PRECTRL.PREREGPOWERSEQUENCEFLAG', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_ENAMPCTRLREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_ENAMPCTRLREG, self).__init__(register,
            'ENAMPCTRLREG', 'RAC_S.PATRIM0.ENAMPCTRLREG', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_PARAMPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_PARAMPMODE, self).__init__(register,
            'PARAMPMODE', 'RAC_S.TXRAMP.PARAMPMODE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RADIOEN_PREREGENREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RADIOEN_PREREGENREG, self).__init__(register,
            'PREREGENREG', 'RAC_S.RADIOEN.PREREGENREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN0_LNAMIXRFATTDCEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN0_LNAMIXRFATTDCEN1, self).__init__(register,
            'LNAMIXRFATTDCEN1', 'RAC_S.RFPATHEN0.LNAMIXRFATTDCEN1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXEN1, self).__init__(register,
            'LNAMIXEN1', 'RAC_S.RFPATHEN1.LNAMIXEN1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXRFPKDENRF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXRFPKDENRF1, self).__init__(register,
            'LNAMIXRFPKDENRF1', 'RAC_S.RFPATHEN1.LNAMIXRFPKDENRF1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXTRSW1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXTRSW1, self).__init__(register,
            'LNAMIXTRSW1', 'RAC_S.RFPATHEN1.LNAMIXTRSW1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXENMXRBIAS1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXENMXRBIAS1, self).__init__(register,
            'LNAMIXENMXRBIAS1', 'RAC_S.RX.LNAMIXENMXRBIAS1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_ENPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_ENPAPOWER, self).__init__(register,
            'ENPAPOWER', 'RAC_S.TX.ENPAPOWER', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_ENMANPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_ENMANPAPOWER, self).__init__(register,
            'ENMANPAPOWER', 'RAC_S.TX.ENMANPAPOWER', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_PAPOWERSCALOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_PAPOWERSCALOR, self).__init__(register,
            'PAPOWERSCALOR', 'RAC_S.TX.PAPOWERSCALOR', 'read-write',
            u"",
            2, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_MANPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_MANPAPOWER, self).__init__(register,
            'MANPAPOWER', 'RAC_S.TX.MANPAPOWER', 'read-write',
            u"",
            10, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_SWPAPOWERLIMIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_SWPAPOWERLIMIT, self).__init__(register,
            'SWPAPOWERLIMIT', 'RAC_S.TX.SWPAPOWERLIMIT', 'read-write',
            u"",
            18, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_ENPASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_ENPASELSLICE, self).__init__(register,
            'ENPASELSLICE', 'RAC_S.TX.ENPASELSLICE', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_XOINJMUXSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_XOINJMUXSEL, self).__init__(register,
            'XOINJMUXSEL', 'RAC_S.SYDEBUG.XOINJMUXSEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_XOINJFORCEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_XOINJFORCEOFF, self).__init__(register,
            'XOINJFORCEOFF', 'RAC_S.SYDEBUG.XOINJFORCEOFF', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYDTCRDACTRIM1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYDTCRDACTRIM1, self).__init__(register,
            'SYDTCRDACTRIM1', 'RAC_S.SYTRIM0.SYDTCRDACTRIM1', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYSTOPRING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYSTOPRING, self).__init__(register,
            'SYTDCTRIMDLYSTOPRING', 'RAC_S.SYTRIM1.SYTDCTRIMDLYSTOPRING', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCNT, self).__init__(register,
            'SYTDCTRIMDLYCNT', 'RAC_S.SYTRIM1.SYTDCTRIMDLYCNT', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYLOAD, self).__init__(register,
            'SYTDCTRIMDLYLOAD', 'RAC_S.SYTRIM1.SYTDCTRIMDLYLOAD', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYSTOPMETA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYSTOPMETA, self).__init__(register,
            'SYTDCTRIMDLYSTOPMETA', 'RAC_S.SYTRIM1.SYTDCTRIMDLYSTOPMETA', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYDTCREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYDTCREGTRIMVREF, self).__init__(register,
            'SYDTCREGTRIMVREF', 'RAC_S.SYTRIM1.SYDTCREGTRIMVREF', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCK1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCK1, self).__init__(register,
            'SYTDCTRIMDLYCK1', 'RAC_S.SYTRIM1.SYTDCTRIMDLYCK1', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMPERLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMPERLOAD, self).__init__(register,
            'SYTDCTRIMPERLOAD', 'RAC_S.SYTRIM1.SYTDCTRIMPERLOAD', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYDSMDACREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYDSMDACREGTRIMVREF, self).__init__(register,
            'SYDSMDACREGTRIMVREF', 'RAC_S.SYTRIM1.SYDSMDACREGTRIMVREF', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYDTCRDACTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYDTCRDACTRIM, self).__init__(register,
            'SYDTCRDACTRIM', 'RAC_S.SYTRIM1.SYDTCRDACTRIM', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMTEMPCOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMTEMPCOP, self).__init__(register,
            'SYTDCREGTRIMTEMPCOP', 'RAC_S.SYTRIM1.SYTDCREGTRIMTEMPCOP', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMTEMPCON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMTEMPCON, self).__init__(register,
            'SYTDCREGTRIMTEMPCON', 'RAC_S.SYTRIM1.SYTDCREGTRIMTEMPCON', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN0_SYENLODIVDSMDACCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN0_SYENLODIVDSMDACCLK, self).__init__(register,
            'SYENLODIVDSMDACCLK', 'RAC_S.SYLOEN0.SYENLODIVDSMDACCLK', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKDTCPULSEWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKDTCPULSEWIDTH, self).__init__(register,
            'SYMMDCLKDTCPULSEWIDTH', 'RAC_S.SYMMDCTRL.SYMMDCLKDTCPULSEWIDTH', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDCYCSLIPSTROBECOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDCYCSLIPSTROBECOUNT, self).__init__(register,
            'SYMMDCYCSLIPSTROBECOUNT', 'RAC_S.SYMMDCTRL.SYMMDCYCSLIPSTROBECOUNT', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDSEL56STG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDSEL56STG, self).__init__(register,
            'SYMMDSEL56STG', 'RAC_S.SYMMDCTRL.SYMMDSEL56STG', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKINJXOINTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKINJXOINTN, self).__init__(register,
            'SYMMDCLKINJXOINTN', 'RAC_S.SYMMDCTRL.SYMMDCLKINJXOINTN', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKINJXOINTNFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKINJXOINTNFORCE, self).__init__(register,
            'SYMMDCLKINJXOINTNFORCE', 'RAC_S.SYMMDCTRL.SYMMDCLKINJXOINTNFORCE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDSEL56STGTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDSEL56STGTX, self).__init__(register,
            'SYMMDSEL56STGTX', 'RAC_S.SYMMDCTRL.SYMMDSEL56STGTX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKDTCPULSEWIDTHTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDCLKDTCPULSEWIDTHTX, self).__init__(register,
            'SYMMDCLKDTCPULSEWIDTHTX', 'RAC_S.SYMMDCTRL.SYMMDCLKDTCPULSEWIDTHTX', 'read-write',
            u"",
            17, 2)
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


class RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKLPWRETIMERESETN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIGCLKRETIMECTRL_DIGCLKLPWRETIMERESETN, self).__init__(register,
            'DIGCLKLPWRETIMERESETN', 'RAC_S.DIGCLKRETIMECTRL.DIGCLKLPWRETIMERESETN', 'read-write',
            u"",
            3, 1)
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


class RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXRFATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXRFATT, self).__init__(register,
            'ENMANLNAMIXRFATT', 'RAC_S.AGCOVERWRITE0.ENMANLNAMIXRFATT', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXSLICE, self).__init__(register,
            'ENMANLNAMIXSLICE', 'RAC_S.AGCOVERWRITE0.ENMANLNAMIXSLICE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_ENMANPGAGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_ENMANPGAGAIN, self).__init__(register,
            'ENMANPGAGAIN', 'RAC_S.AGCOVERWRITE0.ENMANPGAGAIN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_ENMANIFADCSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_ENMANIFADCSCALE, self).__init__(register,
            'ENMANIFADCSCALE', 'RAC_S.AGCOVERWRITE0.ENMANIFADCSCALE', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXSLICE0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXSLICE0, self).__init__(register,
            'MANLNAMIXSLICE0', 'RAC_S.AGCOVERWRITE0.MANLNAMIXSLICE0', 'read-write',
            u"",
            4, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXSLICE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXSLICE1, self).__init__(register,
            'MANLNAMIXSLICE1', 'RAC_S.AGCOVERWRITE0.MANLNAMIXSLICE1', 'read-write',
            u"",
            10, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_ENMANTIACOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_ENMANTIACOMP, self).__init__(register,
            'ENMANTIACOMP', 'RAC_S.AGCOVERWRITE0.ENMANTIACOMP', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_MANTIACOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_MANTIACOMP, self).__init__(register,
            'MANTIACOMP', 'RAC_S.AGCOVERWRITE0.MANTIACOMP', 'read-write',
            u"",
            17, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_MANPGAGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_MANPGAGAIN, self).__init__(register,
            'MANPGAGAIN', 'RAC_S.AGCOVERWRITE0.MANPGAGAIN', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_MANIFADCSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_MANIFADCSCALE, self).__init__(register,
            'MANIFADCSCALE', 'RAC_S.AGCOVERWRITE0.MANIFADCSCALE', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXCUREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_ENMANLNAMIXCUREN, self).__init__(register,
            'ENMANLNAMIXCUREN', 'RAC_S.AGCOVERWRITE0.ENMANLNAMIXCUREN', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXCUREN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXCUREN0, self).__init__(register,
            'MANLNAMIXCUREN0', 'RAC_S.AGCOVERWRITE0.MANLNAMIXCUREN0', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXCUREN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE0_MANLNAMIXCUREN1, self).__init__(register,
            'MANLNAMIXCUREN1', 'RAC_S.AGCOVERWRITE0.MANLNAMIXCUREN1', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE1_MANLNAMIXRFATT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE1_MANLNAMIXRFATT0, self).__init__(register,
            'MANLNAMIXRFATT0', 'RAC_S.AGCOVERWRITE1.MANLNAMIXRFATT0', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AGCOVERWRITE1_MANLNAMIXRFATT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AGCOVERWRITE1_MANLNAMIXRFATT1, self).__init__(register,
            'MANLNAMIXRFATT1', 'RAC_S.AGCOVERWRITE1.MANLNAMIXRFATT1', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_CLKMULTSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_CLKMULTSPARE, self).__init__(register,
            'CLKMULTSPARE', 'RAC_S.SPARE.CLKMULTSPARE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGCORE, self).__init__(register,
            'MIXDACTRIMSPAREVREGCORE', 'RAC_S.SPARE.MIXDACTRIMSPAREVREGCORE', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE02(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE02, self).__init__(register,
            'MIXDACTRIMSPARE02', 'RAC_S.SPARE.MIXDACTRIMSPARE02', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE01(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE01, self).__init__(register,
            'MIXDACTRIMSPARE01', 'RAC_S.SPARE.MIXDACTRIMSPARE01', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACENSPARE02(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACENSPARE02, self).__init__(register,
            'MIXDACENSPARE02', 'RAC_S.SPARE.MIXDACENSPARE02', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGDIG, self).__init__(register,
            'MIXDACTRIMSPAREVREGDIG', 'RAC_S.SPARE.MIXDACTRIMSPAREVREGDIG', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACENSPARE01(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACENSPARE01, self).__init__(register,
            'MIXDACENSPARE01', 'RAC_S.SPARE.MIXDACENSPARE01', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_SYMMDSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SYMMDSPARES, self).__init__(register,
            'SYMMDSPARES', 'RAC_S.SPARE.SYMMDSPARES', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_SYVCOSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SYVCOSPARES, self).__init__(register,
            'SYVCOSPARES', 'RAC_S.SPARE.SYVCOSPARES', 'read-write',
            u"",
            19, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_SYTDCSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SYTDCSPARES, self).__init__(register,
            'SYTDCSPARES', 'RAC_S.SPARE.SYTDCSPARES', 'read-write',
            u"",
            23, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMBBFILTERRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMBBFILTERRES, self).__init__(register,
            'MIXDACTRIMBBFILTERRES', 'RAC_S.MIXDACTRIM.MIXDACTRIMBBFILTERRES', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMLOBIASNMOS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMLOBIASNMOS, self).__init__(register,
            'MIXDACTRIMLOBIASNMOS', 'RAC_S.MIXDACTRIM.MIXDACTRIMLOBIASNMOS', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMLOBIASPMOS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMLOBIASPMOS, self).__init__(register,
            'MIXDACTRIMLOBIASPMOS', 'RAC_S.MIXDACTRIM.MIXDACTRIMLOBIASPMOS', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMNDACCASC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMNDACCASC, self).__init__(register,
            'MIXDACTRIMNDACCASC', 'RAC_S.MIXDACTRIM.MIXDACTRIMNDACCASC', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMPDACCASC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMPDACCASC, self).__init__(register,
            'MIXDACTRIMPDACCASC', 'RAC_S.MIXDACTRIM.MIXDACTRIMPDACCASC', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMREFCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMREFCURRENT, self).__init__(register,
            'MIXDACTRIMREFCURRENT', 'RAC_S.MIXDACTRIM.MIXDACTRIMREFCURRENT', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGCORE, self).__init__(register,
            'MIXDACTRIMVREGCORE', 'RAC_S.MIXDACTRIM.MIXDACTRIMVREGCORE', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGCOREVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGCOREVREF, self).__init__(register,
            'MIXDACTRIMVREGCOREVREF', 'RAC_S.MIXDACTRIM.MIXDACTRIMVREGCOREVREF', 'read-write',
            u"",
            19, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGDIG, self).__init__(register,
            'MIXDACTRIMVREGDIG', 'RAC_S.MIXDACTRIM.MIXDACTRIMVREGDIG', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGDIGVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM_MIXDACTRIMVREGDIGVREF, self).__init__(register,
            'MIXDACTRIMVREGDIGVREF', 'RAC_S.MIXDACTRIM.MIXDACTRIMVREGDIGVREF', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYMMDREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYMMDREGTRIMVREF, self).__init__(register,
            'SYMMDREGTRIMVREF', 'RAC_S.SYTRIM2.SYMMDREGTRIMVREF', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYDTCREGVTTRACKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYDTCREGVTTRACKSEL, self).__init__(register,
            'SYDTCREGVTTRACKSEL', 'RAC_S.SYTRIM2.SYDTCREGVTTRACKSEL', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYDTCCOFFSETTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYDTCCOFFSETTRIM, self).__init__(register,
            'SYDTCCOFFSETTRIM', 'RAC_S.SYTRIM2.SYDTCCOFFSETTRIM', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYENVCOPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYENVCOPKD, self).__init__(register,
            'SYENVCOPKD', 'RAC_S.SYTRIM2.SYENVCOPKD', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYDTCREGTRIMVTTRACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYDTCREGTRIMVTTRACK, self).__init__(register,
            'SYDTCREGTRIMVTTRACK', 'RAC_S.SYTRIM2.SYDTCREGTRIMVTTRACK', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYTDCREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYTDCREGTRIMVREF, self).__init__(register,
            'SYTDCREGTRIMVREF', 'RAC_S.SYTRIM2.SYTDCREGTRIMVREF', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYMMDREGTRIMVREGOFFS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYMMDREGTRIMVREGOFFS, self).__init__(register,
            'SYMMDREGTRIMVREGOFFS', 'RAC_S.SYTRIM2.SYMMDREGTRIMVREGOFFS', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL1_SYDLFDQNCGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL1_SYDLFDQNCGAIN, self).__init__(register,
            'SYDLFDQNCGAIN', 'RAC_S.SYDLFCTRL1.SYDLFDQNCGAIN', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL1_SYDLFDTHIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL1_SYDLFDTHIN, self).__init__(register,
            'SYDLFDTHIN', 'RAC_S.SYDLFCTRL1.SYDLFDTHIN', 'read-write',
            u"",
            3, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL1_SYDLFDQNCGAINTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL1_SYDLFDQNCGAINTX, self).__init__(register,
            'SYDLFDQNCGAINTX', 'RAC_S.SYDLFCTRL1.SYDLFDQNCGAINTX', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL1_SYDLFDTHINTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL1_SYDLFDTHINTX, self).__init__(register,
            'SYDLFDTHINTX', 'RAC_S.SYDLFCTRL1.SYDLFDTHINTX', 'read-write',
            u"",
            19, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFLMSP0M(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFLMSP0M, self).__init__(register,
            'SYDLFLMSP0M', 'RAC_S.SYSTATUS.SYDLFLMSP0M', 'read-only',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLHI, self).__init__(register,
            'SYDLFVCTRLHI', 'RAC_S.SYSTATUS.SYDLFVCTRLHI', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLLO, self).__init__(register,
            'SYDLFVCTRLLO', 'RAC_S.SYSTATUS.SYDLFVCTRLLO', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFPFDLOCKSAMPLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFPFDLOCKSAMPLE, self).__init__(register,
            'SYDLFPFDLOCKSAMPLE', 'RAC_S.SYSTATUS.SYDLFPFDLOCKSAMPLE', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFPFDREFLEAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFPFDREFLEAD, self).__init__(register,
            'SYDLFPFDREFLEAD', 'RAC_S.SYSTATUS.SYDLFPFDREFLEAD', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFSTATE, self).__init__(register,
            'SYDLFSTATE', 'RAC_S.SYSTATUS.SYDLFSTATE', 'read-only',
            u"",
            6, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYMMDCYCSLIPDETECTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYMMDCYCSLIPDETECTED, self).__init__(register,
            'SYMMDCYCSLIPDETECTED', 'RAC_S.SYSTATUS.SYMMDCYCSLIPDETECTED', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFLOCKDETECTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFLOCKDETECTED, self).__init__(register,
            'SYDLFLOCKDETECTED', 'RAC_S.SYSTATUS.SYDLFLOCKDETECTED', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYDTCREGILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYDTCREGILOAD, self).__init__(register,
            'SYDTCREGILOAD', 'RAC_S.SYCTRL2.SYDTCREGILOAD', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIATRIM0_TIATRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIATRIM0_TIATRIMVREF, self).__init__(register,
            'TIATRIMVREF', 'RAC_S.TIATRIM0.TIATRIMVREF', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIATRIM0_TIATRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIATRIM0_TIATRIMVREG, self).__init__(register,
            'TIATRIMVREG', 'RAC_S.TIATRIM0.TIATRIMVREG', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENBIAS, self).__init__(register,
            'TIAENBIAS', 'RAC_S.TIAEN.TIAENBIAS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIABIASCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIABIASCURR, self).__init__(register,
            'TIABIASCURR', 'RAC_S.TIAEN.TIABIASCURR', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENREG, self).__init__(register,
            'TIAENREG', 'RAC_S.TIAEN.TIAENREG', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENSTBLOAD, self).__init__(register,
            'TIAENSTBLOAD', 'RAC_S.TIAEN.TIAENSTBLOAD', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENLATCHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENLATCHI, self).__init__(register,
            'TIAENLATCHI', 'RAC_S.TIAEN.TIAENLATCHI', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENPKD, self).__init__(register,
            'TIAENPKD', 'RAC_S.TIAEN.TIAENPKD', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENLATCHQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENLATCHQ, self).__init__(register,
            'TIAENLATCHQ', 'RAC_S.TIAEN.TIAENLATCHQ', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENTIAI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENTIAI, self).__init__(register,
            'TIAENTIAI', 'RAC_S.TIAEN.TIAENTIAI', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENTIAQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENTIAQ, self).__init__(register,
            'TIAENTIAQ', 'RAC_S.TIAEN.TIAENTIAQ', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAENDCOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAENDCOC, self).__init__(register,
            'TIAENDCOC', 'RAC_S.TIAEN.TIAENDCOC', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRENINTBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRENINTBIAS, self).__init__(register,
            'VTRENINTBIAS', 'RAC_S.VTRCTRL0.VTRENINTBIAS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRENBIASREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRENBIASREG, self).__init__(register,
            'VTRENBIASREG', 'RAC_S.VTRCTRL0.VTRENBIASREG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRENFORCEDVTRSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRENFORCEDVTRSTARTUP, self).__init__(register,
            'VTRENFORCEDVTRSTARTUP', 'RAC_S.VTRCTRL0.VTRENFORCEDVTRSTARTUP', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRDISABLEVTRSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRDISABLEVTRSTARTUP, self).__init__(register,
            'VTRDISABLEVTRSTARTUP', 'RAC_S.VTRCTRL0.VTRDISABLEVTRSTARTUP', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRENCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRENCORE, self).__init__(register,
            'VTRENCORE', 'RAC_S.VTRCTRL0.VTRENCORE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRENSTBLOADREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRENSTBLOADREG, self).__init__(register,
            'VTRENSTBLOADREG', 'RAC_S.VTRCTRL0.VTRENSTBLOADREG', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPCORE, self).__init__(register,
            'VTRSTARTUPCORE', 'RAC_S.VTRCTRL0.VTRSTARTUPCORE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPSUPPLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPSUPPLY, self).__init__(register,
            'VTRSTARTUPSUPPLY', 'RAC_S.VTRCTRL0.VTRSTARTUPSUPPLY', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRHIGHCURRENTHV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRHIGHCURRENTHV, self).__init__(register,
            'VTRHIGHCURRENTHV', 'RAC_S.VTRCTRL0.VTRHIGHCURRENTHV', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRENREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRENREG, self).__init__(register,
            'VTRENREG', 'RAC_S.VTRCTRL0.VTRENREG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_AUXADCTSENSESELCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_AUXADCTSENSESELCURR, self).__init__(register,
            'AUXADCTSENSESELCURR', 'RAC_S.AUXADCCAL.AUXADCTSENSESELCURR', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_AUXADCTRIMCURRINPUTBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_AUXADCTRIMCURRINPUTBUF, self).__init__(register,
            'AUXADCTRIMCURRINPUTBUF', 'RAC_S.AUXADCCAL.AUXADCTRIMCURRINPUTBUF', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL2_IFADCS2PRSTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL2_IFADCS2PRSTN, self).__init__(register,
            'IFADCS2PRSTN', 'RAC_S.AUXADCCTRL2.IFADCS2PRSTN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN0_LNAMIXENIRCAL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN0_LNAMIXENIRCAL1, self).__init__(register,
            'LNAMIXENIRCAL1', 'RAC_S.LNAMIXEN0.LNAMIXENIRCAL1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN0_LNAMIXENREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN0_LNAMIXENREG, self).__init__(register,
            'LNAMIXENREG', 'RAC_S.LNAMIXEN0.LNAMIXENREG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN0_LNAMIXENLOTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN0_LNAMIXENLOTHRESH, self).__init__(register,
            'LNAMIXENLOTHRESH', 'RAC_S.LNAMIXEN0.LNAMIXENLOTHRESH', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN0_LNAMIXENRFPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN0_LNAMIXENRFPKD, self).__init__(register,
            'LNAMIXENRFPKD', 'RAC_S.LNAMIXEN0.LNAMIXENRFPKD', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN0_IRCALON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN0_IRCALON, self).__init__(register,
            'IRCALON', 'RAC_S.LNAMIXEN0.IRCALON', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACEN0DBMPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACEN0DBMPA, self).__init__(register,
            'MIXDACEN0DBMPA', 'RAC_S.MIXDACEN.MIXDACEN0DBMPA', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENBIASVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENBIASVREGDIG, self).__init__(register,
            'MIXDACENBIASVREGDIG', 'RAC_S.MIXDACEN.MIXDACENBIASVREGDIG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACEN10DBMPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACEN10DBMPA, self).__init__(register,
            'MIXDACEN10DBMPA', 'RAC_S.MIXDACEN.MIXDACEN10DBMPA', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENCLKMULT2P4G(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENCLKMULT2P4G, self).__init__(register,
            'MIXDACENCLKMULT2P4G', 'RAC_S.MIXDACEN.MIXDACENCLKMULT2P4G', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENCORE, self).__init__(register,
            'MIXDACENCORE', 'RAC_S.MIXDACEN.MIXDACENCORE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGCORE, self).__init__(register,
            'MIXDACENSTBLOADVREGCORE', 'RAC_S.MIXDACEN.MIXDACENSTBLOADVREGCORE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGDIG, self).__init__(register,
            'MIXDACENSTBLOADVREGDIG', 'RAC_S.MIXDACEN.MIXDACENSTBLOADVREGDIG', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENBIASVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENBIASVREGCORE, self).__init__(register,
            'MIXDACENBIASVREGCORE', 'RAC_S.MIXDACEN.MIXDACENBIASVREGCORE', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENVREGCORE, self).__init__(register,
            'MIXDACENVREGCORE', 'RAC_S.MIXDACEN.MIXDACENVREGCORE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENVREGDIG, self).__init__(register,
            'MIXDACENVREGDIG', 'RAC_S.MIXDACEN.MIXDACENVREGDIG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENFORCEDSTARTUPVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENFORCEDSTARTUPVREGDIG, self).__init__(register,
            'MIXDACENFORCEDSTARTUPVREGDIG', 'RAC_S.MIXDACEN.MIXDACENFORCEDSTARTUPVREGDIG', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENIRCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENIRCAL, self).__init__(register,
            'MIXDACENIRCAL', 'RAC_S.MIXDACEN.MIXDACENIRCAL', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENPOSEDGEDACCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENPOSEDGEDACCLK, self).__init__(register,
            'MIXDACENPOSEDGEDACCLK', 'RAC_S.MIXDACEN.MIXDACENPOSEDGEDACCLK', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENRFSYNTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENRFSYNTH, self).__init__(register,
            'MIXDACENRFSYNTH', 'RAC_S.MIXDACEN.MIXDACENRFSYNTH', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGDIGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENSTBLOADVREGDIGREPLICA, self).__init__(register,
            'MIXDACENSTBLOADVREGDIGREPLICA', 'RAC_S.MIXDACEN.MIXDACENSTBLOADVREGDIGREPLICA', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACEN_MIXDACENVREGDIGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACEN_MIXDACENVREGDIGREPLICA, self).__init__(register,
            'MIXDACENVREGDIGREPLICA', 'RAC_S.MIXDACEN.MIXDACENVREGDIGREPLICA', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYMMDTRIMSYNCTMARGIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYMMDTRIMSYNCTMARGIN, self).__init__(register,
            'SYMMDTRIMSYNCTMARGIN', 'RAC_S.SYCTRL1.SYMMDTRIMSYNCTMARGIN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVSELFP4G82G4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVSELFP4G82G4, self).__init__(register,
            'SYLODIVSELFP4G82G4', 'RAC_S.SYCTRL1.SYLODIVSELFP4G82G4', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYVCOFASTSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYVCOFASTSTARTUP, self).__init__(register,
            'SYVCOFASTSTARTUP', 'RAC_S.SYCTRL1.SYVCOFASTSTARTUP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVSELFP4G82G4TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVSELFP4G82G4TX, self).__init__(register,
            'SYLODIVSELFP4G82G4TX', 'RAC_S.SYCTRL1.SYLODIVSELFP4G82G4TX', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYMMDREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYMMDREGTRIMVREG, self).__init__(register,
            'SYMMDREGTRIMVREG', 'RAC_S.SYCTRL1.SYMMDREGTRIMVREG', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYMMDREGTRIMVREGTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYMMDREGTRIMVREGTX, self).__init__(register,
            'SYMMDREGTRIMVREGTX', 'RAC_S.SYCTRL1.SYMMDREGTRIMVREGTX', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPAREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPAREG, self).__init__(register,
            'TX0DBMENPAREG', 'RAC_S.TX0DBMEN.TX0DBMENPAREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRVREG, self).__init__(register,
            'TX0DBMENPREDRVREG', 'RAC_S.TX0DBMEN.TX0DBMENPREDRVREG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRV, self).__init__(register,
            'TX0DBMENPREDRV', 'RAC_S.TX0DBMEN.TX0DBMENPREDRV', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENBYPASSREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENBYPASSREGPA, self).__init__(register,
            'TX0DBMENBYPASSREGPA', 'RAC_S.TX0DBMEN.TX0DBMENBYPASSREGPA', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENREPLICABIASREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENREPLICABIASREGPA, self).__init__(register,
            'TX0DBMENREPLICABIASREGPA', 'RAC_S.TX0DBMEN.TX0DBMENREPLICABIASREGPA', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPA, self).__init__(register,
            'TX0DBMENPA', 'RAC_S.TX0DBMEN.TX0DBMENPA', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPAREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPAREGSTBLOAD, self).__init__(register,
            'TX0DBMENPAREGSTBLOAD', 'RAC_S.TX0DBMEN.TX0DBMENPAREGSTBLOAD', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRVREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRVREGSTBLOAD, self).__init__(register,
            'TX0DBMENPREDRVREGSTBLOAD', 'RAC_S.TX0DBMEN.TX0DBMENPREDRVREGSTBLOAD', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMCTRL_TX0DBMPOWERRAMPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMCTRL_TX0DBMPOWERRAMPRESET, self).__init__(register,
            'TX0DBMPOWERRAMPRESET', 'RAC_S.TX0DBMCTRL.TX0DBMPOWERRAMPRESET', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMCTRL_TX0DBMRAMPCLKBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMCTRL_TX0DBMRAMPCLKBYPASS, self).__init__(register,
            'TX0DBMRAMPCLKBYPASS', 'RAC_S.TX0DBMCTRL.TX0DBMRAMPCLKBYPASS', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMDUTYCYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMDUTYCYN, self).__init__(register,
            'TX0DBMTRIMDUTYCYN', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMDUTYCYN', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMNBIASPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMNBIASPA, self).__init__(register,
            'TX0DBMTRIMNBIASPA', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMNBIASPA', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPBIASPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPBIASPA, self).__init__(register,
            'TX0DBMTRIMPBIASPA', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMPBIASPA', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMLOINTVDDAPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMLOINTVDDAPREDRV, self).__init__(register,
            'TX0DBMTRIMLOINTVDDAPREDRV', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMLOINTVDDAPREDRV', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMRFBREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMRFBREGPA, self).__init__(register,
            'TX0DBMTRIMRFBREGPA', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMRFBREGPA', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPREDRVREGEXTRALOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPREDRVREGEXTRALOAD, self).__init__(register,
            'TX0DBMTRIMPREDRVREGEXTRALOAD', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMPREDRVREGEXTRALOAD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPAREGEXTRALOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMPAREGEXTRALOAD, self).__init__(register,
            'TX0DBMTRIMPAREGEXTRALOAD', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMPAREGEXTRALOAD', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMDUTYCYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMDUTYCYP, self).__init__(register,
            'TX0DBMTRIMDUTYCYP', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMDUTYCYP', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMVREFREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM1_TX0DBMTRIMVREFREGPREDRV, self).__init__(register,
            'TX0DBMTRIMVREFREGPREDRV', 'RAC_S.TX0DBMTRIM1.TX0DBMTRIMVREFREGPREDRV', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPSRBSTREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPSRBSTREGPREDRV, self).__init__(register,
            'TX0DBMTRIMPSRBSTREGPREDRV', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMPSRBSTREGPREDRV', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPREDRVSLOPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPREDRVSLOPE, self).__init__(register,
            'TX0DBMTRIMPREDRVSLOPE', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMPREDRVSLOPE', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPSRBSTREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPSRBSTREGPA, self).__init__(register,
            'TX0DBMTRIMPSRBSTREGPA', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMPSRBSTREGPA', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMTAPCAP100F(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMTAPCAP100F, self).__init__(register,
            'TX0DBMTRIMTAPCAP100F', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMTAPCAP100F', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMTAPCAP200F(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMTAPCAP200F, self).__init__(register,
            'TX0DBMTRIMTAPCAP200F', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMTAPCAP200F', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMVREFREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMVREFREGPA, self).__init__(register,
            'TX0DBMTRIMVREFREGPA', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMVREFREGPA', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPA, self).__init__(register,
            'TX10DBMENPA', 'RAC_S.TX10DBMEN.TX10DBMENPA', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREG, self).__init__(register,
            'TX10DBMENPAREG', 'RAC_S.TX10DBMEN.TX10DBMENPAREG', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRV, self).__init__(register,
            'TX10DBMENPREDRV', 'RAC_S.TX10DBMEN.TX10DBMENPREDRV', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRVREG, self).__init__(register,
            'TX10DBMENPREDRVREG', 'RAC_S.TX10DBMEN.TX10DBMENPREDRVREG', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGPULLDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGPULLDOWN, self).__init__(register,
            'TX10DBMENPAREGPULLDOWN', 'RAC_S.TX10DBMEN.TX10DBMENPAREGPULLDOWN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGSTBLOAD, self).__init__(register,
            'TX10DBMENPAREGSTBLOAD', 'RAC_S.TX10DBMEN.TX10DBMENPAREGSTBLOAD', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAOUTBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAOUTBIAS, self).__init__(register,
            'TX10DBMENPAOUTBIAS', 'RAC_S.TX10DBMEN.TX10DBMENPAOUTBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENRXPADATTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENRXPADATTN, self).__init__(register,
            'TX10DBMENRXPADATTN', 'RAC_S.TX10DBMEN.TX10DBMENRXPADATTN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRVREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPREDRVREGSTBLOAD, self).__init__(register,
            'TX10DBMENPREDRVREGSTBLOAD', 'RAC_S.TX10DBMEN.TX10DBMENPREDRVREGSTBLOAD', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGPULLDOWNTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGPULLDOWNTX, self).__init__(register,
            'TX10DBMENPAREGPULLDOWNTX', 'RAC_S.TX10DBMEN.TX10DBMENPAREGPULLDOWNTX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAOUTBIASTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAOUTBIASTX, self).__init__(register,
            'TX10DBMENPAOUTBIASTX', 'RAC_S.TX10DBMEN.TX10DBMENPAOUTBIASTX', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENRXPADATTNTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENRXPADATTNTX, self).__init__(register,
            'TX10DBMENRXPADATTNTX', 'RAC_S.TX10DBMEN.TX10DBMENRXPADATTNTX', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMPOWER, self).__init__(register,
            'TX10DBMPOWER', 'RAC_S.TX10DBMCTRL0.TX10DBMPOWER', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMRAMPCLKBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMRAMPCLKBYPASS, self).__init__(register,
            'TX10DBMRAMPCLKBYPASS', 'RAC_S.TX10DBMCTRL0.TX10DBMRAMPCLKBYPASS', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMPOWERRAMPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMCTRL0_TX10DBMPOWERRAMPRESET, self).__init__(register,
            'TX10DBMPOWERRAMPRESET', 'RAC_S.TX10DBMCTRL0.TX10DBMPOWERRAMPRESET', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASDION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASDION, self).__init__(register,
            'TX10DBMTRIMBIASDION', 'RAC_S.TX10DBMTRIM1.TX10DBMTRIMBIASDION', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASDIOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASDIOP, self).__init__(register,
            'TX10DBMTRIMBIASDIOP', 'RAC_S.TX10DBMTRIM1.TX10DBMTRIMBIASDIOP', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMNSWBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMNSWBIAS, self).__init__(register,
            'TX10DBMTRIMNSWBIAS', 'RAC_S.TX10DBMTRIM1.TX10DBMTRIMNSWBIAS', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMPSWBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMPSWBIAS, self).__init__(register,
            'TX10DBMTRIMPSWBIAS', 'RAC_S.TX10DBMTRIM1.TX10DBMTRIMPSWBIAS', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASN, self).__init__(register,
            'TX10DBMTRIMBIASN', 'RAC_S.TX10DBMTRIM1.TX10DBMTRIMBIASN', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMDUTYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMDUTYN, self).__init__(register,
            'TX10DBMTRIMDUTYN', 'RAC_S.TX10DBMTRIM1.TX10DBMTRIMDUTYN', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMBIASP, self).__init__(register,
            'TX10DBMTRIMBIASP', 'RAC_S.TX10DBMTRIM1.TX10DBMTRIMBIASP', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMDUTYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM1_TX10DBMTRIMDUTYP, self).__init__(register,
            'TX10DBMTRIMDUTYP', 'RAC_S.TX10DBMTRIM1.TX10DBMTRIMDUTYP', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGSLICES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGSLICES, self).__init__(register,
            'TX10DBMTRIMPREDRVREGSLICES', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPREDRVREGSLICES', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVSLC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVSLC, self).__init__(register,
            'TX10DBMTRIMPREDRVSLC', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPREDRVSLC', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGPSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGPSR, self).__init__(register,
            'TX10DBMTRIMPREDRVREGPSR', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPREDRVREGPSR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREG, self).__init__(register,
            'TX10DBMTRIMPREDRVREG', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPREDRVREG', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREG, self).__init__(register,
            'TX10DBMTRIMPAREG', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPAREG', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREGVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREGVREF, self).__init__(register,
            'TX10DBMTRIMPAREGVREF', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPAREGVREF', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVREGVREF, self).__init__(register,
            'TX10DBMTRIMPREDRVREGVREF', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPREDRVREGVREF', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREGPSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPAREGPSR, self).__init__(register,
            'TX10DBMTRIMPAREGPSR', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPAREGPSR', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMPREDRVCAP, self).__init__(register,
            'TX10DBMTRIMPREDRVCAP', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMPREDRVCAP', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMLOINTVDDAPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMTRIMLOINTVDDAPREDRV, self).__init__(register,
            'TX10DBMTRIMLOINTVDDAPREDRV', 'RAC_S.TX10DBMTRIM2.TX10DBMTRIMLOINTVDDAPREDRV', 'read-write',
            u"",
            21, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMENPAREGSTBLOADAUTO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM2_TX10DBMENPAREGSTBLOADAUTO, self).__init__(register,
            'TX10DBMENPAREGSTBLOADAUTO', 'RAC_S.TX10DBMTRIM2.TX10DBMENPAREGSTBLOADAUTO', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVREG, self).__init__(register,
            'PREREGTRIMVREG', 'RAC_S.PREREGTRIM.PREREGTRIMVREG', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVTRMINIVOLTAGE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVTRMINIVOLTAGE, self).__init__(register,
            'PREREGTRIMVTRMINIVOLTAGE', 'RAC_S.PREREGTRIM.PREREGTRIMVTRMINIVOLTAGE', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PREREGTRIM_PREREGTRIMBYPCMPVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PREREGTRIM_PREREGTRIMBYPCMPVREF, self).__init__(register,
            'PREREGTRIMBYPCMPVREF', 'RAC_S.PREREGTRIM.PREREGTRIMBYPCMPVREF', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVTRMINITEMPCO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PREREGTRIM_PREREGTRIMVTRMINITEMPCO, self).__init__(register,
            'PREREGTRIMVTRMINITEMPCO', 'RAC_S.PREREGTRIM.PREREGTRIMVTRMINITEMPCO', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_MIXDACTRIM1_MIXDACTRIMBBSUPPLYSERIESRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_MIXDACTRIM1_MIXDACTRIMBBSUPPLYSERIESRES, self).__init__(register,
            'MIXDACTRIMBBSUPPLYSERIESRES', 'RAC_S.MIXDACTRIM1.MIXDACTRIMBBSUPPLYSERIESRES', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF1_SYDLFTDCDBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF1_SYDLFTDCDBIAS, self).__init__(register,
            'SYDLFTDCDBIAS', 'RAC_S.SYDLF1.SYDLFTDCDBIAS', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF1_SYDLFTDCDBIASTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF1_SYDLFTDCDBIASTX, self).__init__(register,
            'SYDLFTDCDBIASTX', 'RAC_S.SYDLF1.SYDLFTDCDBIASTX', 'read-write',
            u"",
            16, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_LNAMIXSPARE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_LNAMIXSPARE1, self).__init__(register,
            'LNAMIXSPARE1', 'RAC_S.SPARE1.LNAMIXSPARE1', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_LNAMIXSPARE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_LNAMIXSPARE2, self).__init__(register,
            'LNAMIXSPARE2', 'RAC_S.SPARE1.LNAMIXSPARE2', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_TIASPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_TIASPARE, self).__init__(register,
            'TIASPARE', 'RAC_S.SPARE1.TIASPARE', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_TX10DBMSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_TX10DBMSPARE, self).__init__(register,
            'TX10DBMSPARE', 'RAC_S.SPARE1.TX10DBMSPARE', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_VTRSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_VTRSPARES, self).__init__(register,
            'VTRSPARES', 'RAC_S.SPARE1.VTRSPARES', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PREREGSTATUS_PREREGBYPOUTCOLLAPSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PREREGSTATUS_PREREGBYPOUTCOLLAPSED, self).__init__(register,
            'PREREGBYPOUTCOLLAPSED', 'RAC_S.PREREGSTATUS.PREREGBYPOUTCOLLAPSED', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRTRIM_VTRTRIMIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRTRIM_VTRTRIMIBIAS, self).__init__(register,
            'VTRTRIMIBIAS', 'RAC_S.VTRTRIM.VTRTRIMIBIAS', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRTRIM_VTRTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRTRIM_VTRTRIMVREF, self).__init__(register,
            'VTRTRIMVREF', 'RAC_S.VTRTRIM.VTRTRIMVREF', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRTRIM_VTRTRIMTC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRTRIM_VTRTRIMTC, self).__init__(register,
            'VTRTRIMTC', 'RAC_S.VTRTRIM.VTRTRIMTC', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRTRIM_VTRTRIMVREFPREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRTRIM_VTRTRIMVREFPREREG, self).__init__(register,
            'VTRTRIMVREFPREREG', 'RAC_S.VTRTRIM.VTRTRIMVREFPREREG', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRTRIM_VTRTRIMVREFVTR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRTRIM_VTRTRIMVREFVTR, self).__init__(register,
            'VTRTRIMVREFVTR', 'RAC_S.VTRTRIM.VTRTRIMVREFVTR', 'read-write',
            u"",
            19, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRTRIM_VTRTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRTRIM_VTRTRIMVREG, self).__init__(register,
            'VTRTRIMVREG', 'RAC_S.VTRTRIM.VTRTRIMVREG', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCTUNERCCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCTUNERCCALMODE, self).__init__(register,
            'ADCTUNERCCALMODE', 'RAC_S.ADCCTRL0.ADCTUNERCCALMODE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCCAPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCCAPRESET, self).__init__(register,
            'ADCCAPRESET', 'RAC_S.ADCCTRL0.ADCCAPRESET', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCCLKSEL, self).__init__(register,
            'ADCCLKSEL', 'RAC_S.ADCCTRL0.ADCCLKSEL', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCCTRLRESERVED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCCTRLRESERVED, self).__init__(register,
            'ADCCTRLRESERVED', 'RAC_S.ADCCTRL0.ADCCTRLRESERVED', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCINVERTCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCINVERTCLK, self).__init__(register,
            'ADCINVERTCLK', 'RAC_S.ADCCTRL0.ADCINVERTCLK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCCTRLRESERVEDLV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCCTRLRESERVEDLV, self).__init__(register,
            'ADCCTRLRESERVEDLV', 'RAC_S.ADCCTRL0.ADCCTRLRESERVEDLV', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCZEROOPT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCZEROOPT, self).__init__(register,
            'ADCZEROOPT', 'RAC_S.ADCCTRL0.ADCZEROOPT', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCLOWCUR, self).__init__(register,
            'ADCLOWCUR', 'RAC_S.ADCCTRL0.ADCLOWCUR', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCNEGRESVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCNEGRESVCM, self).__init__(register,
            'ADCNEGRESVCM', 'RAC_S.ADCCTRL0.ADCNEGRESVCM', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTCURLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTCURLVL2, self).__init__(register,
            'ADCLDOSHUNTCURLVL2', 'RAC_S.ADCCTRL0.ADCLDOSHUNTCURLVL2', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCNEGRESCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCNEGRESCURRENT, self).__init__(register,
            'ADCNEGRESCURRENT', 'RAC_S.ADCCTRL0.ADCNEGRESCURRENT', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTAMPLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTAMPLVL2, self).__init__(register,
            'ADCLDOSHUNTAMPLVL2', 'RAC_S.ADCCTRL0.ADCLDOSHUNTAMPLVL2', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTAMPLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCLDOSHUNTAMPLVL1, self).__init__(register,
            'ADCLDOSHUNTAMPLVL1', 'RAC_S.ADCCTRL0.ADCLDOSHUNTAMPLVL1', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL0_ADCTUNERC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL0_ADCTUNERC, self).__init__(register,
            'ADCTUNERC', 'RAC_S.ADCCTRL0.ADCTUNERC', 'read-write',
            u"",
            25, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL1_ADCENHALFBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL1_ADCENHALFBW, self).__init__(register,
            'ADCENHALFBW', 'RAC_S.ADCCTRL1.ADCENHALFBW', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL1_ADCENHALFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL1_ADCENHALFMODE, self).__init__(register,
            'ADCENHALFMODE', 'RAC_S.ADCCTRL1.ADCENHALFMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCEN0_ADCENADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCEN0_ADCENADC, self).__init__(register,
            'ADCENADC', 'RAC_S.ADCEN0.ADCENADC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCEN0_ADCENRCCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCEN0_ADCENRCCAL, self).__init__(register,
            'ADCENRCCAL', 'RAC_S.ADCEN0.ADCENRCCAL', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCEN0_ADCENSIDETONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCEN0_ADCENSIDETONE, self).__init__(register,
            'ADCENSIDETONE', 'RAC_S.ADCEN0.ADCENSIDETONE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCEN0_ADCENLDOSHUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCEN0_ADCENLDOSHUNT, self).__init__(register,
            'ADCENLDOSHUNT', 'RAC_S.ADCEN0.ADCENLDOSHUNT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCEN0_ADCENCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCEN0_ADCENCLK, self).__init__(register,
            'ADCENCLK', 'RAC_S.ADCEN0.ADCENCLK', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCEN0_ADCENLDOSERIES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCEN0_ADCENLDOSERIES, self).__init__(register,
            'ADCENLDOSERIES', 'RAC_S.ADCEN0.ADCENLDOSERIES', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCEN0_ADCENNEGRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCEN0_ADCENNEGRES, self).__init__(register,
            'ADCENNEGRES', 'RAC_S.ADCEN0.ADCENNEGRES', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCEN0_ADCENLDOBIASSERIES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCEN0_ADCENLDOBIASSERIES, self).__init__(register,
            'ADCENLDOBIASSERIES', 'RAC_S.ADCEN0.ADCENLDOBIASSERIES', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCTRIM0_ADCLDOSHUNTCURLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCTRIM0_ADCLDOSHUNTCURLVL1, self).__init__(register,
            'ADCLDOSHUNTCURLVL1', 'RAC_S.ADCTRIM0.ADCLDOSHUNTCURLVL1', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCTRIM0_ADCLDOSERIESAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCTRIM0_ADCLDOSERIESAMPLVL, self).__init__(register,
            'ADCLDOSERIESAMPLVL', 'RAC_S.ADCTRIM0.ADCLDOSERIESAMPLVL', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCTRIM0_ADCLDOSERIESAMPLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCTRIM0_ADCLDOSERIESAMPLVL2, self).__init__(register,
            'ADCLDOSERIESAMPLVL2', 'RAC_S.ADCTRIM0.ADCLDOSERIESAMPLVL2', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCTRIM0_ADCSIDETONEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCTRIM0_ADCSIDETONEFREQ, self).__init__(register,
            'ADCSIDETONEFREQ', 'RAC_S.ADCTRIM0.ADCSIDETONEFREQ', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCTRIM0_ADCSIDETONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCTRIM0_ADCSIDETONEAMP, self).__init__(register,
            'ADCSIDETONEAMP', 'RAC_S.ADCTRIM0.ADCSIDETONEAMP', 'read-write',
            u"",
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCTRIM0_ADCREFBUFCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCTRIM0_ADCREFBUFCURLVL, self).__init__(register,
            'ADCREFBUFCURLVL', 'RAC_S.ADCTRIM0.ADCREFBUFCURLVL', 'read-write',
            u"",
            17, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCTRIM0_ADCVCMLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCTRIM0_ADCVCMLVL, self).__init__(register,
            'ADCVCMLVL', 'RAC_S.ADCTRIM0.ADCVCMLVL', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL2_ADCOTACURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL2_ADCOTACURRENT, self).__init__(register,
            'ADCOTACURRENT', 'RAC_S.ADCCTRL2.ADCOTACURRENT', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL2_ADCVCMBUFBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL2_ADCVCMBUFBYPASS, self).__init__(register,
            'ADCVCMBUFBYPASS', 'RAC_S.ADCCTRL2.ADCVCMBUFBYPASS', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL2_ADCRCCALCOUNTERSTARTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL2_ADCRCCALCOUNTERSTARTVAL, self).__init__(register,
            'ADCRCCALCOUNTERSTARTVAL', 'RAC_S.ADCCTRL2.ADCRCCALCOUNTERSTARTVAL', 'read-write',
            u"",
            4, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL2_ADCSHORTINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL2_ADCSHORTINPUT, self).__init__(register,
            'ADCSHORTINPUT', 'RAC_S.ADCCTRL2.ADCSHORTINPUT', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL2_ADCLDOSERIESFORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL2_ADCLDOSERIESFORCEDSTARTUP, self).__init__(register,
            'ADCLDOSERIESFORCEDSTARTUP', 'RAC_S.ADCCTRL2.ADCLDOSERIESFORCEDSTARTUP', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ADCCTRL2_ADCSETVINCM400M(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ADCCTRL2_ADCSETVINCM400M, self).__init__(register,
            'ADCSETVINCM400M', 'RAC_S.ADCCTRL2.ADCSETVINCM400M', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN1_LNAMIXDOUBLECUR1EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN1_LNAMIXDOUBLECUR1EN, self).__init__(register,
            'LNAMIXDOUBLECUR1EN', 'RAC_S.LNAMIXEN1.LNAMIXDOUBLECUR1EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN1_LNAMIXMXRLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN1_LNAMIXMXRLOSEL, self).__init__(register,
            'LNAMIXMXRLOSEL', 'RAC_S.LNAMIXEN1.LNAMIXMXRLOSEL', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXENSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXENSTBLOAD, self).__init__(register,
            'LNAMIXENSTBLOAD', 'RAC_S.LNAMIXCTRL0.LNAMIXENSTBLOAD', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXREGLOWPWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXREGLOWPWR, self).__init__(register,
            'LNAMIXREGLOWPWR', 'RAC_S.LNAMIXCTRL0.LNAMIXREGLOWPWR', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXTXIRCALSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCTRL0_LNAMIXTXIRCALSEL, self).__init__(register,
            'LNAMIXTXIRCALSEL', 'RAC_S.LNAMIXCTRL0.LNAMIXTXIRCALSEL', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCTRL1_LNAMIXRFPKDTHRESHSELLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCTRL1_LNAMIXRFPKDTHRESHSELLO, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELLO', 'RAC_S.LNAMIXCTRL1.LNAMIXRFPKDTHRESHSELLO', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCTRL1_LNAMIXRFPKDTHRESHSELHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCTRL1_LNAMIXRFPKDTHRESHSELHI, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELHI', 'RAC_S.LNAMIXCTRL1.LNAMIXRFPKDTHRESHSELHI', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PREREGEN_PREREGENSTBILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PREREGEN_PREREGENSTBILOAD, self).__init__(register,
            'PREREGENSTBILOAD', 'RAC_S.PREREGEN.PREREGENSTBILOAD', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PREREGEN_PREREGENCALLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PREREGEN_PREREGENCALLOAD, self).__init__(register,
            'PREREGENCALLOAD', 'RAC_S.PREREGEN.PREREGENCALLOAD', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PREDEBUG_PREREGSTARTUPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PREDEBUG_PREREGSTARTUPFORCE, self).__init__(register,
            'PREREGSTARTUPFORCE', 'RAC_S.PREDEBUG.PREREGSTARTUPFORCE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL0_SYDLFCLAMPTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL0_SYDLFCLAMPTH, self).__init__(register,
            'SYDLFCLAMPTH', 'RAC_S.SYDLFCTRL0.SYDLFCLAMPTH', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL0_SYDLFTDCA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL0_SYDLFTDCA2, self).__init__(register,
            'SYDLFTDCA2', 'RAC_S.SYDLFCTRL0.SYDLFTDCA2', 'read-write',
            u"",
            3, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL0_SYDLFLOCKTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL0_SYDLFLOCKTHRESHOLD, self).__init__(register,
            'SYDLFLOCKTHRESHOLD', 'RAC_S.SYDLFCTRL0.SYDLFLOCKTHRESHOLD', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADXI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADXI, self).__init__(register,
            'SYDLFREADXI', 'RAC_S.SYDLFCTRL0.SYDLFREADXI', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADXF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADXF, self).__init__(register,
            'SYDLFREADXF', 'RAC_S.SYDLFCTRL0.SYDLFREADXF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADACAPCK2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL0_SYDLFREADACAPCK2, self).__init__(register,
            'SYDLFREADACAPCK2', 'RAC_S.SYDLFCTRL0.SYDLFREADACAPCK2', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL0_SYDLFPFDLOCKSAMPLETH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL0_SYDLFPFDLOCKSAMPLETH, self).__init__(register,
            'SYDLFPFDLOCKSAMPLETH', 'RAC_S.SYDLFCTRL0.SYDLFPFDLOCKSAMPLETH', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL0_SYDLFPOSITIVECOEFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL0_SYDLFPOSITIVECOEFF, self).__init__(register,
            'SYDLFPOSITIVECOEFF', 'RAC_S.SYDLFCTRL0.SYDLFPOSITIVECOEFF', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN0_SYENDLFTDCA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN0_SYENDLFTDCA2, self).__init__(register,
            'SYENDLFTDCA2', 'RAC_S.SYEN0.SYENDLFTDCA2', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN0_SYENMMDCLKINJXO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN0_SYENMMDCLKINJXO, self).__init__(register,
            'SYENMMDCLKINJXO', 'RAC_S.SYEN0.SYENMMDCLKINJXO', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN0_SYENDLFTDCA2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN0_SYENDLFTDCA2TX, self).__init__(register,
            'SYENDLFTDCA2TX', 'RAC_S.SYEN0.SYENDLFTDCA2TX', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENVCOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENVCOREG, self).__init__(register,
            'SYENVCOREG', 'RAC_S.SYEN1.SYENVCOREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENMMDREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENMMDREGSTBLOAD, self).__init__(register,
            'SYENMMDREGSTBLOAD', 'RAC_S.SYEN1.SYENMMDREGSTBLOAD', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENTDCREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENTDCREG, self).__init__(register,
            'SYENTDCREG', 'RAC_S.SYEN1.SYENTDCREG', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENTDCREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENTDCREGSTBLOAD, self).__init__(register,
            'SYENTDCREGSTBLOAD', 'RAC_S.SYEN1.SYENTDCREGSTBLOAD', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENTDC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENTDC, self).__init__(register,
            'SYENTDC', 'RAC_S.SYEN1.SYENTDC', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENDLF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENDLF, self).__init__(register,
            'SYENDLF', 'RAC_S.SYEN1.SYENDLF', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENVCOIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENVCOIBIAS, self).__init__(register,
            'SYENVCOIBIAS', 'RAC_S.SYEN1.SYENVCOIBIAS', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENDSMDAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENDSMDAC, self).__init__(register,
            'SYENDSMDAC', 'RAC_S.SYEN1.SYENDSMDAC', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENVCOBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENVCOBIAS, self).__init__(register,
            'SYENVCOBIAS', 'RAC_S.SYEN1.SYENVCOBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENDSMDACREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENDSMDACREG, self).__init__(register,
            'SYENDSMDACREG', 'RAC_S.SYEN1.SYENDSMDACREG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENVCOREGLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENVCOREGLOAD, self).__init__(register,
            'SYENVCOREGLOAD', 'RAC_S.SYEN1.SYENVCOREGLOAD', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENMMDREG, self).__init__(register,
            'SYENMMDREG', 'RAC_S.SYEN1.SYENMMDREG', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENDTCCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENDTCCORE, self).__init__(register,
            'SYENDTCCORE', 'RAC_S.SYEN1.SYENDTCCORE', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENDTCREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENDTCREG, self).__init__(register,
            'SYENDTCREG', 'RAC_S.SYEN1.SYENDTCREG', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENMMDOUTPUTS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENMMDOUTPUTS, self).__init__(register,
            'SYENMMDOUTPUTS', 'RAC_S.SYEN1.SYENMMDOUTPUTS', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN1_SYENMMDREGBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN1_SYENMMDREGBIAS, self).__init__(register,
            'SYENMMDREGBIAS', 'RAC_S.SYEN1.SYENMMDREGBIAS', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN2_SYENTDCAQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN2_SYENTDCAQNC, self).__init__(register,
            'SYENTDCAQNC', 'RAC_S.SYEN2.SYENTDCAQNC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN2_SELSYDTCRDACTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN2_SELSYDTCRDACTRIM, self).__init__(register,
            'SELSYDTCRDACTRIM', 'RAC_S.SYEN2.SELSYDTCRDACTRIM', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYVCOTRIMIPTAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYVCOTRIMIPTAT, self).__init__(register,
            'SYVCOTRIMIPTAT', 'RAC_S.SYCTRL0.SYVCOTRIMIPTAT', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYENMMDREGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYENMMDREGREPLICA, self).__init__(register,
            'SYENMMDREGREPLICA', 'RAC_S.SYCTRL0.SYENMMDREGREPLICA', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYDSMDACREGILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYDSMDACREGILOAD, self).__init__(register,
            'SYDSMDACREGILOAD', 'RAC_S.SYCTRL0.SYDSMDACREGILOAD', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYDSMDACREGTRIMSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYDSMDACREGTRIMSTBLOAD, self).__init__(register,
            'SYDSMDACREGTRIMSTBLOAD', 'RAC_S.SYCTRL0.SYDSMDACREGTRIMSTBLOAD', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYENMMDSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYENMMDSYNC, self).__init__(register,
            'SYENMMDSYNC', 'RAC_S.SYCTRL0.SYENMMDSYNC', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYVCOTRIMPKDAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYVCOTRIMPKDAMP, self).__init__(register,
            'SYVCOTRIMPKDAMP', 'RAC_S.SYCTRL0.SYVCOTRIMPKDAMP', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYVCOREGLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYVCOREGLOWCUR, self).__init__(register,
            'SYVCOREGLOWCUR', 'RAC_S.SYCTRL0.SYVCOREGLOWCUR', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYENLODIVDIVSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYENLODIVDIVSE, self).__init__(register,
            'SYENLODIVDIVSE', 'RAC_S.SYCTRL0.SYENLODIVDIVSE', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYENMMDAQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYENMMDAQNC, self).__init__(register,
            'SYENMMDAQNC', 'RAC_S.SYCTRL0.SYENMMDAQNC', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYVCOTRIMIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYVCOTRIMIBIAS, self).__init__(register,
            'SYVCOTRIMIBIAS', 'RAC_S.SYCTRL0.SYVCOTRIMIBIAS', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYDSMDACTRIMLOADBALDLF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYDSMDACTRIMLOADBALDLF, self).__init__(register,
            'SYDSMDACTRIMLOADBALDLF', 'RAC_S.SYCTRL0.SYDSMDACTRIMLOADBALDLF', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL0_SYDSMDACTRIMLOADBALDSM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL0_SYDSMDACTRIMLOADBALDSM, self).__init__(register,
            'SYDSMDACTRIMLOADBALDSM', 'RAC_S.SYCTRL0.SYDSMDACTRIMLOADBALDSM', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN1_SYENLODIVREGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN1_SYENLODIVREGREPLICA, self).__init__(register,
            'SYENLODIVREGREPLICA', 'RAC_S.SYLOEN1.SYENLODIVREGREPLICA', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN1_SYENLODIVREGBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN1_SYENLODIVREGBIAS, self).__init__(register,
            'SYENLODIVREGBIAS', 'RAC_S.SYLOEN1.SYENLODIVREGBIAS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN1_SYENLODIVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN1_SYENLODIVREG, self).__init__(register,
            'SYENLODIVREG', 'RAC_S.SYLOEN1.SYENLODIVREG', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN1_SYENLODIVREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN1_SYENLODIVREGSTBLOAD, self).__init__(register,
            'SYENLODIVREGSTBLOAD', 'RAC_S.SYLOEN1.SYENLODIVREGSTBLOAD', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN1_SYENLODIVREGREPLICATX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN1_SYENLODIVREGREPLICATX, self).__init__(register,
            'SYENLODIVREGREPLICATX', 'RAC_S.SYLOEN1.SYENLODIVREGREPLICATX', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN2_SYENLODIVADCCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN2_SYENLODIVADCCLK, self).__init__(register,
            'SYENLODIVADCCLK', 'RAC_S.SYLOEN2.SYENLODIVADCCLK', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN2_SYENLODIVADCCLKTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN2_SYENLODIVADCCLKTX, self).__init__(register,
            'SYENLODIVADCCLKTX', 'RAC_S.SYLOEN2.SYENLODIVADCCLKTX', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVSELFPSRC2G4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVSELFPSRC2G4, self).__init__(register,
            'SYLODIVSELFPSRC2G4', 'RAC_S.SYLOCTRL0.SYLODIVSELFPSRC2G4', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVBYPASSIQCLKBIASDELTA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVBYPASSIQCLKBIASDELTA, self).__init__(register,
            'SYLODIVBYPASSIQCLKBIASDELTA', 'RAC_S.SYLOCTRL0.SYLODIVBYPASSIQCLKBIASDELTA', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVSELFCALCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVSELFCALCLK, self).__init__(register,
            'SYLODIVSELFCALCLK', 'RAC_S.SYLOCTRL0.SYLODIVSELFCALCLK', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASDELTA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASDELTA, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASDELTA', 'RAC_S.SYLOCTRL0.SYLODIVTRIMIQCLKBIASDELTA', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVDSMDACCLKDIVRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVDSMDACCLKDIVRATIO, self).__init__(register,
            'SYLODIVDSMDACCLKDIVRATIO', 'RAC_S.SYLOCTRL0.SYLODIVDSMDACCLKDIVRATIO', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVSPARES, self).__init__(register,
            'SYLODIVSPARES', 'RAC_S.SYLOCTRL0.SYLODIVSPARES', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVSMUXCLKDIVRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVSMUXCLKDIVRATIO, self).__init__(register,
            'SYLODIVSMUXCLKDIVRATIO', 'RAC_S.SYLOCTRL0.SYLODIVSMUXCLKDIVRATIO', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASNDIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASNDIO, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASNDIO', 'RAC_S.SYLOCTRL0.SYLODIVTRIMIQCLKBIASNDIO', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVTRIMIQCLKBIASIBIAS, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASIBIAS', 'RAC_S.SYLOCTRL0.SYLODIVTRIMIQCLKBIASIBIAS', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVADCDIVRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVADCDIVRATIO, self).__init__(register,
            'SYLODIVADCDIVRATIO', 'RAC_S.SYLOCTRL0.SYLODIVADCDIVRATIO', 'read-write',
            u"",
            21, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVREGTRIMVREG, self).__init__(register,
            'SYLODIVREGTRIMVREG', 'RAC_S.SYLOCTRL0.SYLODIVREGTRIMVREG', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL0_SYLODIVREGTRIMVREGTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL0_SYLODIVREGTRIMVREGTX, self).__init__(register,
            'SYLODIVREGTRIMVREGTX', 'RAC_S.SYLOCTRL0.SYLODIVREGTRIMVREGTX', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMDIV, self).__init__(register,
            'SYENLODIVHADMDIV', 'RAC_S.SYLOCTRL1.SYENLODIVHADMDIV', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMLO, self).__init__(register,
            'SYENLODIVHADMLO', 'RAC_S.SYLOCTRL1.SYENLODIVHADMLO', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMRXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMRXLO, self).__init__(register,
            'SYENLODIVHADMRXLO', 'RAC_S.SYLOCTRL1.SYENLODIVHADMRXLO', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMTXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVHADMTXLO, self).__init__(register,
            'SYENLODIVHADMTXLO', 'RAC_S.SYLOCTRL1.SYENLODIVHADMTXLO', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVLPRXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVLPRXLO, self).__init__(register,
            'SYENLODIVLPRXLO', 'RAC_S.SYLOCTRL1.SYENLODIVLPRXLO', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVLPRXDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVLPRXDIV, self).__init__(register,
            'SYENLODIVLPRXDIV', 'RAC_S.SYLOCTRL1.SYENLODIVLPRXDIV', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVIQCLKBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVIQCLKBIAS, self).__init__(register,
            'SYENLODIVIQCLKBIAS', 'RAC_S.SYLOCTRL1.SYENLODIVIQCLKBIAS', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVSECLKBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVSECLKBIAS, self).__init__(register,
            'SYENLODIVSECLKBIAS', 'RAC_S.SYLOCTRL1.SYENLODIVSECLKBIAS', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVSMUXCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVSMUXCLK, self).__init__(register,
            'SYENLODIVSMUXCLK', 'RAC_S.SYLOCTRL1.SYENLODIVSMUXCLK', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRL1_SYENLODIVTXRF0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRL1_SYENLODIVTXRF0DBM, self).__init__(register,
            'SYENLODIVTXRF0DBM', 'RAC_S.SYLOCTRL1.SYENLODIVTXRF0DBM', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOTRIM0_SYLODIVREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOTRIM0_SYLODIVREGTRIMVREF, self).__init__(register,
            'SYLODIVREGTRIMVREF', 'RAC_S.SYLOTRIM0.SYLODIVREGTRIMVREF', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOTRIM0_SYLODIVREGTRIMVREGOFFS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOTRIM0_SYLODIVREGTRIMVREGOFFS, self).__init__(register,
            'SYLODIVREGTRIMVREGOFFS', 'RAC_S.SYLOTRIM0.SYLODIVREGTRIMVREGOFFS', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM3_SYVCOREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM3_SYVCOREGTRIMVREF, self).__init__(register,
            'SYVCOREGTRIMVREF', 'RAC_S.SYTRIM3.SYVCOREGTRIMVREF', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM3_SYVCOTRIMR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM3_SYVCOTRIMR, self).__init__(register,
            'SYVCOTRIMR', 'RAC_S.SYTRIM3.SYVCOTRIMR', 'read-write',
            u"",
            4, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM3_SYVCOREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM3_SYVCOREGTRIMVREG, self).__init__(register,
            'SYVCOREGTRIMVREG', 'RAC_S.SYTRIM3.SYVCOREGTRIMVREG', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM3_SYVCOTRIMBIASVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM3_SYVCOTRIMBIASVREF, self).__init__(register,
            'SYVCOTRIMBIASVREF', 'RAC_S.SYTRIM3.SYVCOTRIMBIASVREF', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM3_SYTDCREGTRIMBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM3_SYTDCREGTRIMBW, self).__init__(register,
            'SYTDCREGTRIMBW', 'RAC_S.SYTRIM3.SYTDCREGTRIMBW', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM3_SYDTCSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM3_SYDTCSPARES, self).__init__(register,
            'SYDTCSPARES', 'RAC_S.SYTRIM3.SYDTCSPARES', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM3_SYTDCREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM3_SYTDCREGTRIMVREG, self).__init__(register,
            'SYTDCREGTRIMVREG', 'RAC_S.SYTRIM3.SYTDCREGTRIMVREG', 'read-write',
            u"",
            18, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIACTRL0_TIAOXI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIACTRL0_TIAOXI, self).__init__(register,
            'TIAOXI', 'RAC_S.TIACTRL0.TIAOXI', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIACTRL0_TIAOXQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIACTRL0_TIAOXQ, self).__init__(register,
            'TIAOXQ', 'RAC_S.TIACTRL0.TIAOXQ', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIACTRL0_TIASETVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIACTRL0_TIASETVCM, self).__init__(register,
            'TIASETVCM', 'RAC_S.TIACTRL0.TIASETVCM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIACTRL0_TIATHRPKDLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIACTRL0_TIATHRPKDLOSEL, self).__init__(register,
            'TIATHRPKDLOSEL', 'RAC_S.TIACTRL0.TIATHRPKDLOSEL', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIACTRL0_TIATHRPKDHISEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIACTRL0_TIATHRPKDHISEL, self).__init__(register,
            'TIATHRPKDHISEL', 'RAC_S.TIACTRL0.TIATHRPKDHISEL', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIACTRL0_TIARESFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIACTRL0_TIARESFB, self).__init__(register,
            'TIARESFB', 'RAC_S.TIACTRL0.TIARESFB', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIACTRL1_TIACAPFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIACTRL1_TIACAPFB, self).__init__(register,
            'TIACAPFB', 'RAC_S.TIACTRL1.TIACAPFB', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIACTRL1_TIACOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIACTRL1_TIACOMP, self).__init__(register,
            'TIACOMP', 'RAC_S.TIACTRL1.TIACOMP', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMRXPADATTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMRXPADATTN, self).__init__(register,
            'TX10DBMRXPADATTN', 'RAC_S.TX10DBMCTRL1.TX10DBMRXPADATTN', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM0_TX10DBMTRIMHFCTAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM0_TX10DBMTRIMHFCTAP, self).__init__(register,
            'TX10DBMTRIMHFCTAP', 'RAC_S.TX10DBMTRIM0.TX10DBMTRIMHFCTAP', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTRIM0_TX10DBMTRIMHFCTAPTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTRIM0_TX10DBMTRIMHFCTAPTX, self).__init__(register,
            'TX10DBMTRIMHFCTAPTX', 'RAC_S.TX10DBMTRIM0.TX10DBMTRIMHFCTAPTX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYVCOTRIMIPTATTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYVCOTRIMIPTATTX, self).__init__(register,
            'SYVCOTRIMIPTATTX', 'RAC_S.SYCTRLTX0.SYVCOTRIMIPTATTX', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYENMMDREGREPLICATX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYENMMDREGREPLICATX, self).__init__(register,
            'SYENMMDREGREPLICATX', 'RAC_S.SYCTRLTX0.SYENMMDREGREPLICATX', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYDSMDACREGILOADTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYDSMDACREGILOADTX, self).__init__(register,
            'SYDSMDACREGILOADTX', 'RAC_S.SYCTRLTX0.SYDSMDACREGILOADTX', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYDSMDACREGTRIMSTBLOADTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYDSMDACREGTRIMSTBLOADTX, self).__init__(register,
            'SYDSMDACREGTRIMSTBLOADTX', 'RAC_S.SYCTRLTX0.SYDSMDACREGTRIMSTBLOADTX', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYENMMDSYNCTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYENMMDSYNCTX, self).__init__(register,
            'SYENMMDSYNCTX', 'RAC_S.SYCTRLTX0.SYENMMDSYNCTX', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYENMMDAQNCTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYENMMDAQNCTX, self).__init__(register,
            'SYENMMDAQNCTX', 'RAC_S.SYCTRLTX0.SYENMMDAQNCTX', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYVCOTRIMIBIASTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYVCOTRIMIBIASTX, self).__init__(register,
            'SYVCOTRIMIBIASTX', 'RAC_S.SYCTRLTX0.SYVCOTRIMIBIASTX', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYDSMDACTRIMLOADBALDLFTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYDSMDACTRIMLOADBALDLFTX, self).__init__(register,
            'SYDSMDACTRIMLOADBALDLFTX', 'RAC_S.SYCTRLTX0.SYDSMDACTRIMLOADBALDLFTX', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRLTX0_SYDSMDACTRIMLOADBALDSMTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRLTX0_SYDSMDACTRIMLOADBALDSMTX, self).__init__(register,
            'SYDSMDACTRIMLOADBALDSMTX', 'RAC_S.SYCTRLTX0.SYDSMDACTRIMLOADBALDSMTX', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVSELFPSRC2G4TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVSELFPSRC2G4TX, self).__init__(register,
            'SYLODIVSELFPSRC2G4TX', 'RAC_S.SYLOCTRLTX0.SYLODIVSELFPSRC2G4TX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVBYPASSIQCLKBIASDELTATX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVBYPASSIQCLKBIASDELTATX, self).__init__(register,
            'SYLODIVBYPASSIQCLKBIASDELTATX', 'RAC_S.SYLOCTRLTX0.SYLODIVBYPASSIQCLKBIASDELTATX', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASDELTATX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASDELTATX, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASDELTATX', 'RAC_S.SYLOCTRLTX0.SYLODIVTRIMIQCLKBIASDELTATX', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVDSMDACCLKDIVRATIOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVDSMDACCLKDIVRATIOTX, self).__init__(register,
            'SYLODIVDSMDACCLKDIVRATIOTX', 'RAC_S.SYLOCTRLTX0.SYLODIVDSMDACCLKDIVRATIOTX', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVSMUXCLKDIVRATIOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVSMUXCLKDIVRATIOTX, self).__init__(register,
            'SYLODIVSMUXCLKDIVRATIOTX', 'RAC_S.SYLOCTRLTX0.SYLODIVSMUXCLKDIVRATIOTX', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASNDIOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASNDIOTX, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASNDIOTX', 'RAC_S.SYLOCTRLTX0.SYLODIVTRIMIQCLKBIASNDIOTX', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASIBIASTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVTRIMIQCLKBIASIBIASTX, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASIBIASTX', 'RAC_S.SYLOCTRLTX0.SYLODIVTRIMIQCLKBIASIBIASTX', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVADCDIVRATIOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX0_SYLODIVADCDIVRATIOTX, self).__init__(register,
            'SYLODIVADCDIVRATIOTX', 'RAC_S.SYLOCTRLTX0.SYLODIVADCDIVRATIOTX', 'read-write',
            u"",
            21, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMDIVTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMDIVTX, self).__init__(register,
            'SYENLODIVHADMDIVTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVHADMDIVTX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMLOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMLOTX, self).__init__(register,
            'SYENLODIVHADMLOTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVHADMLOTX', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMRXLOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMRXLOTX, self).__init__(register,
            'SYENLODIVHADMRXLOTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVHADMRXLOTX', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMTXLOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVHADMTXLOTX, self).__init__(register,
            'SYENLODIVHADMTXLOTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVHADMTXLOTX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVLPRXLOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVLPRXLOTX, self).__init__(register,
            'SYENLODIVLPRXLOTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVLPRXLOTX', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVLPRXDIVTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVLPRXDIVTX, self).__init__(register,
            'SYENLODIVLPRXDIVTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVLPRXDIVTX', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVIQCLKBIASTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVIQCLKBIASTX, self).__init__(register,
            'SYENLODIVIQCLKBIASTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVIQCLKBIASTX', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVSMUXCLKTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVSMUXCLKTX, self).__init__(register,
            'SYENLODIVSMUXCLKTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVSMUXCLKTX', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVTXRF0DBMTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOCTRLTX1_SYENLODIVTXRF0DBMTX, self).__init__(register,
            'SYENLODIVTXRF0DBMTX', 'RAC_S.SYLOCTRLTX1.SYENLODIVTXRF0DBMTX', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN2_CLKMULTENBYPASS40MHZTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN2_CLKMULTENBYPASS40MHZTX, self).__init__(register,
            'CLKMULTENBYPASS40MHZTX', 'RAC_S.CLKMULTEN2.CLKMULTENBYPASS40MHZTX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVNTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVNTX, self).__init__(register,
            'CLKMULTDIVNTX', 'RAC_S.CLKMULTEN2.CLKMULTDIVNTX', 'read-write',
            u"",
            1, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVRTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVRTX, self).__init__(register,
            'CLKMULTDIVRTX', 'RAC_S.CLKMULTEN2.CLKMULTDIVRTX', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVXTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN2_CLKMULTDIVXTX, self).__init__(register,
            'CLKMULTDIVXTX', 'RAC_S.CLKMULTEN2.CLKMULTDIVXTX', 'read-write',
            u"",
            11, 4)
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


class RM_Field_RAC_S_FSWCTRL_FSWRISCVCLKDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWCTRL_FSWRISCVCLKDIS, self).__init__(register,
            'FSWRISCVCLKDIS', 'RAC_S.FSWCTRL.FSWRISCVCLKDIS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FSWCTRL_FSWRISCVRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FSWCTRL_FSWRISCVRESET, self).__init__(register,
            'FSWRISCVRESET', 'RAC_S.FSWCTRL.FSWRISCVRESET', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_THMSW_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_THMSW_EN, self).__init__(register,
            'EN', 'RAC_S.THMSW.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_THMSW_HALFSWITCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_THMSW_HALFSWITCH, self).__init__(register,
            'HALFSWITCH', 'RAC_S.THMSW.HALFSWITCH', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIAGAALTEN_RFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIAGAALTEN_RFEN, self).__init__(register,
            'RFEN', 'RAC_S.DIAGAALTEN.RFEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIAGAALTSEL_TP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIAGAALTSEL_TP, self).__init__(register,
            'TP', 'RAC_S.DIAGAALTSEL.TP', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIAGAALTSEL_BLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIAGAALTSEL_BLK, self).__init__(register,
            'BLK', 'RAC_S.DIAGAALTSEL.BLK', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_DIAGAALTBRIDGECTRL_RFSHORTDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_DIAGAALTBRIDGECTRL_RFSHORTDIS, self).__init__(register,
            'RFSHORTDIS', 'RAC_S.DIAGAALTBRIDGECTRL.RFSHORTDIS', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_SYNTHLODIVFREQCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_SYNTHLODIVFREQCTRL, self).__init__(register,
            'SYNTHLODIVFREQCTRL', 'RAC_S.RFLOCK0.SYNTHLODIVFREQCTRL', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_MODEMHADM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_MODEMHADM, self).__init__(register,
            'MODEMHADM', 'RAC_S.RFLOCK0.MODEMHADM', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_FRCCONVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_FRCCONVMODE, self).__init__(register,
            'FRCCONVMODE', 'RAC_S.RFLOCK0.FRCCONVMODE', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_FRCPAUSING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_FRCPAUSING, self).__init__(register,
            'FRCPAUSING', 'RAC_S.RFLOCK0.FRCPAUSING', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_MODEMANTSWENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_MODEMANTSWENABLE, self).__init__(register,
            'MODEMANTSWENABLE', 'RAC_S.RFLOCK0.MODEMANTSWENABLE', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_MODEMLRBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_MODEMLRBLE, self).__init__(register,
            'MODEMLRBLE', 'RAC_S.RFLOCK0.MODEMLRBLE', 'read-write',
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


class RM_Field_RAC_S_RFLOCK1_RACPASTRIPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASTRIPE, self).__init__(register,
            'RACPASTRIPE', 'RAC_S.RFLOCK1.RACPASTRIPE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_RACPASLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASLICE, self).__init__(register,
            'RACPASLICE', 'RAC_S.RFLOCK1.RACPASLICE', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_TX0DBMPOWERLIMIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_TX0DBMPOWERLIMIT, self).__init__(register,
            'TX0DBMPOWERLIMIT', 'RAC_S.RFLOCK1.TX0DBMPOWERLIMIT', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_TX10DBMPOWERLIMIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_TX10DBMPOWERLIMIT, self).__init__(register,
            'TX10DBMPOWERLIMIT', 'RAC_S.RFLOCK1.TX10DBMPOWERLIMIT', 'read-write',
            u"",
            13, 7)
        self.__dict__['zz_frozen'] = True



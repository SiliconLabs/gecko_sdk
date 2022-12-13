
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


class RM_Field_RAC_S_CTRL_PRSFORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_PRSFORCETX, self).__init__(register,
            'PRSFORCETX', 'RAC_S.CTRL.PRSFORCETX', 'read-write',
            u"",
            16, 1)
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


class RM_Field_RAC_S_CTRL_RXOFDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CTRL_RXOFDIS, self).__init__(register,
            'RXOFDIS', 'RAC_S.CTRL.RXOFDIS', 'read-write',
            u"",
            28, 1)
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


class RM_Field_RAC_S_SEQIF_STATECHANGESEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATECHANGESEQ, self).__init__(register,
            'STATECHANGESEQ', 'RAC_S.SEQIF.STATECHANGESEQ', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STIMCMPEVSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STIMCMPEVSEQ, self).__init__(register,
            'STIMCMPEVSEQ', 'RAC_S.SEQIF.STIMCMPEVSEQ', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_DEMODRXREQCLRSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_DEMODRXREQCLRSEQ, self).__init__(register,
            'DEMODRXREQCLRSEQ', 'RAC_S.SEQIF.DEMODRXREQCLRSEQ', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_PRSEVENTSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_PRSEVENTSEQ, self).__init__(register,
            'PRSEVENTSEQ', 'RAC_S.SEQIF.PRSEVENTSEQ', 'read-write',
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


class RM_Field_RAC_S_SEQIF_STATERXPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXPD, self).__init__(register,
            'STATERXPD', 'RAC_S.SEQIF.STATERXPD', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERX2RX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERX2RX, self).__init__(register,
            'STATERX2RX', 'RAC_S.SEQIF.STATERX2RX', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXOVERFLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXOVERFLOW, self).__init__(register,
            'STATERXOVERFLOW', 'RAC_S.SEQIF.STATERXOVERFLOW', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERX2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERX2TX, self).__init__(register,
            'STATERX2TX', 'RAC_S.SEQIF.STATERX2TX', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETXWARM, self).__init__(register,
            'STATETXWARM', 'RAC_S.SEQIF.STATETXWARM', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETX, self).__init__(register,
            'STATETX', 'RAC_S.SEQIF.STATETX', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETXPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETXPD, self).__init__(register,
            'STATETXPD', 'RAC_S.SEQIF.STATETXPD', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETX2RX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETX2RX, self).__init__(register,
            'STATETX2RX', 'RAC_S.SEQIF.STATETX2RX', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETX2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETX2TX, self).__init__(register,
            'STATETX2TX', 'RAC_S.SEQIF.STATETX2TX', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATESHUTDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATESHUTDOWN, self).__init__(register,
            'STATESHUTDOWN', 'RAC_S.SEQIF.STATESHUTDOWN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_RFTXPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_RFTXPKD, self).__init__(register,
            'RFTXPKD', 'RAC_S.SEQIF.RFTXPKD', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATECHANGESEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATECHANGESEQ, self).__init__(register,
            'STATECHANGESEQ', 'RAC_S.SEQIEN.STATECHANGESEQ', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STIMCMPEVSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STIMCMPEVSEQ, self).__init__(register,
            'STIMCMPEVSEQ', 'RAC_S.SEQIEN.STIMCMPEVSEQ', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_DEMODRXREQCLRSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_DEMODRXREQCLRSEQ, self).__init__(register,
            'DEMODRXREQCLRSEQ', 'RAC_S.SEQIEN.DEMODRXREQCLRSEQ', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_PRSEVENTSEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_PRSEVENTSEQ, self).__init__(register,
            'PRSEVENTSEQ', 'RAC_S.SEQIEN.PRSEVENTSEQ', 'read-write',
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


class RM_Field_RAC_S_SEQIEN_STATERXPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXPD, self).__init__(register,
            'STATERXPD', 'RAC_S.SEQIEN.STATERXPD', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERX2RX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERX2RX, self).__init__(register,
            'STATERX2RX', 'RAC_S.SEQIEN.STATERX2RX', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXOVERFLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXOVERFLOW, self).__init__(register,
            'STATERXOVERFLOW', 'RAC_S.SEQIEN.STATERXOVERFLOW', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERX2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERX2TX, self).__init__(register,
            'STATERX2TX', 'RAC_S.SEQIEN.STATERX2TX', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETXWARM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETXWARM, self).__init__(register,
            'STATETXWARM', 'RAC_S.SEQIEN.STATETXWARM', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETX, self).__init__(register,
            'STATETX', 'RAC_S.SEQIEN.STATETX', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETXPD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETXPD, self).__init__(register,
            'STATETXPD', 'RAC_S.SEQIEN.STATETXPD', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETX2RX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETX2RX, self).__init__(register,
            'STATETX2RX', 'RAC_S.SEQIEN.STATETX2RX', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETX2TX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETX2TX, self).__init__(register,
            'STATETX2TX', 'RAC_S.SEQIEN.STATETX2TX', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATESHUTDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATESHUTDOWN, self).__init__(register,
            'STATESHUTDOWN', 'RAC_S.SEQIEN.STATESHUTDOWN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_RFTXPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_RFTXPKD, self).__init__(register,
            'RFTXPKD', 'RAC_S.SEQIEN.RFTXPKD', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS1_TXMASK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS1_TXMASK, self).__init__(register,
            'TXMASK', 'RAC_S.STATUS1.TXMASK', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FEMCTRL_FEMEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FEMCTRL_FEMEN, self).__init__(register,
            'FEMEN', 'RAC_S.FEMCTRL.FEMEN', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_FEMDATA_FEMDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_FEMDATA_FEMDATA, self).__init__(register,
            'FEMDATA', 'RAC_S.FEMDATA.FEMDATA', 'read-write',
            u"",
            0, 4)
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


class RM_Field_RAC_S_STCTRL_STCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STCTRL_STCAL, self).__init__(register,
            'STCAL', 'RAC_S.STCTRL.STCAL', 'read-write',
            u"",
            0, 24)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STCTRL_STSKEW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STCTRL_STSKEW, self).__init__(register,
            'STSKEW', 'RAC_S.STCTRL.STSKEW', 'read-write',
            u"",
            24, 1)
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


class RM_Field_RAC_S_EM1PCSR_MCUEM1PSWRUNNING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_EM1PCSR_MCUEM1PSWRUNNING, self).__init__(register,
            'MCUEM1PSWRUNNING', 'RAC_S.EM1PCSR.MCUEM1PSWRUNNING', 'read-only',
            u"",
            19, 1)
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


class RM_Field_RAC_S_SYNTHENCTRL_MMDPOWERBALANCEDISABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYNTHENCTRL_MMDPOWERBALANCEDISABLE, self).__init__(register,
            'MMDPOWERBALANCEDISABLE', 'RAC_S.SYNTHENCTRL.MMDPOWERBALANCEDISABLE', 'read-write',
            u"",
            10, 1)
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


class RM_Field_RAC_S_VCOCTRL_VCODETAMPLITUDERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VCOCTRL_VCODETAMPLITUDERX, self).__init__(register,
            'VCODETAMPLITUDERX', 'RAC_S.VCOCTRL.VCODETAMPLITUDERX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VCOCTRL_VCODETAMPLITUDETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VCOCTRL_VCODETAMPLITUDETX, self).__init__(register,
            'VCODETAMPLITUDETX', 'RAC_S.VCOCTRL.VCODETAMPLITUDETX', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CHPCTRL_CHPOUTPUTTRISTATEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CHPCTRL_CHPOUTPUTTRISTATEMODE, self).__init__(register,
            'CHPOUTPUTTRISTATEMODE', 'RAC_S.CHPCTRL.CHPOUTPUTTRISTATEMODE', 'read-write',
            u"",
            14, 1)
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
            25, 4)
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


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN0, self).__init__(register,
            'INTDIVLNAMIXEN0', 'RAC_S.ANTDIV.INTDIVLNAMIXEN0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXENAMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXENAMP0, self).__init__(register,
            'INTDIVLNAMIXENAMP0', 'RAC_S.ANTDIV.INTDIVLNAMIXENAMP0', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFATTDCEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFATTDCEN0, self).__init__(register,
            'INTDIVLNAMIXRFATTDCEN0', 'RAC_S.ANTDIV.INTDIVLNAMIXRFATTDCEN0', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFPKDENRF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXRFPKDENRF0, self).__init__(register,
            'INTDIVLNAMIXRFPKDENRF0', 'RAC_S.ANTDIV.INTDIVLNAMIXRFPKDENRF0', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_INTDIVSYLODIVRLO0SUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVSYLODIVRLO0SUBGEN, self).__init__(register,
            'INTDIVSYLODIVRLO0SUBGEN', 'RAC_S.ANTDIV.INTDIVSYLODIVRLO0SUBGEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN1, self).__init__(register,
            'INTDIVLNAMIXEN1', 'RAC_S.ANTDIV.INTDIVLNAMIXEN1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXENAMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXENAMP1, self).__init__(register,
            'INTDIVLNAMIXENAMP1', 'RAC_S.ANTDIV.INTDIVLNAMIXENAMP1', 'read-write',
            u"",
            6, 1)
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


class RM_Field_RAC_S_ANTDIV_INTDIVSYLODIVRLO1SUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVSYLODIVRLO1SUBGEN, self).__init__(register,
            'INTDIVSYLODIVRLO1SUBGEN', 'RAC_S.ANTDIV.INTDIVSYLODIVRLO1SUBGEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_ANTDIV_ANTDIVSTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_ANTDIVSTATUS, self).__init__(register,
            'ANTDIVSTATUS', 'RAC_S.ANTDIV.ANTDIVSTATUS', 'read-only',
            u"",
            10, 2)
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


class RM_Field_RAC_S_AUXADCEN_AUXADCENMEASTHERMISTOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_AUXADCENMEASTHERMISTOR, self).__init__(register,
            'AUXADCENMEASTHERMISTOR', 'RAC_S.AUXADCEN.AUXADCENMEASTHERMISTOR', 'read-write',
            u"",
            9, 1)
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


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCIN6SHIMEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCIN6SHIMEN, self).__init__(register,
            'AUXADCIN6SHIMEN', 'RAC_S.AUXADCCTRL1.AUXADCIN6SHIMEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCIN8SHIMEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCIN8SHIMEN, self).__init__(register,
            'AUXADCIN8SHIMEN', 'RAC_S.AUXADCCTRL1.AUXADCIN8SHIMEN', 'read-write',
            u"",
            14, 1)
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


class RM_Field_RAC_S_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL, self).__init__(register,
            'AUXADCTHERMISTORFREQSEL', 'RAC_S.AUXADCCTRL1.AUXADCTHERMISTORFREQSEL', 'read-write',
            u"",
            28, 4)
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


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVN, self).__init__(register,
            'CLKMULTENDRVN', 'RAC_S.CLKMULTEN0.CLKMULTENDRVN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVP, self).__init__(register,
            'CLKMULTENDRVP', 'RAC_S.CLKMULTEN0.CLKMULTENDRVP', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVRX2P4G(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVRX2P4G, self).__init__(register,
            'CLKMULTENDRVRX2P4G', 'RAC_S.CLKMULTEN0.CLKMULTENDRVRX2P4G', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVRXSUBG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVRXSUBG, self).__init__(register,
            'CLKMULTENDRVRXSUBG', 'RAC_S.CLKMULTEN0.CLKMULTENDRVRXSUBG', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTXDUALB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTXDUALB, self).__init__(register,
            'CLKMULTENDRVTXDUALB', 'RAC_S.CLKMULTEN0.CLKMULTENDRVTXDUALB', 'read-write',
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


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG3, self).__init__(register,
            'CLKMULTENREG3', 'RAC_S.CLKMULTEN0.CLKMULTENREG3', 'read-write',
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


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTFREQCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTFREQCAL, self).__init__(register,
            'CLKMULTFREQCAL', 'RAC_S.CLKMULTEN0.CLKMULTFREQCAL', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG2ADJI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG2ADJI, self).__init__(register,
            'CLKMULTREG2ADJI', 'RAC_S.CLKMULTEN0.CLKMULTREG2ADJI', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG1ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG1ADJV, self).__init__(register,
            'CLKMULTREG1ADJV', 'RAC_S.CLKMULTEN0.CLKMULTREG1ADJV', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG2ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG2ADJV, self).__init__(register,
            'CLKMULTREG2ADJV', 'RAC_S.CLKMULTEN0.CLKMULTREG2ADJV', 'read-write',
            u"",
            28, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG3ADJV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTREG3ADJV, self).__init__(register,
            'CLKMULTREG3ADJV', 'RAC_S.CLKMULTEN0.CLKMULTREG3ADJV', 'read-write',
            u"",
            30, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTINNIBBLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTINNIBBLE, self).__init__(register,
            'CLKMULTINNIBBLE', 'RAC_S.CLKMULTEN1.CLKMULTINNIBBLE', 'read-write',
            u"",
            0, 4)
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


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTLDCNIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTLDCNIB, self).__init__(register,
            'CLKMULTLDCNIB', 'RAC_S.CLKMULTEN1.CLKMULTLDCNIB', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTDRVAMPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTDRVAMPSEL, self).__init__(register,
            'CLKMULTDRVAMPSEL', 'RAC_S.CLKMULTEN1.CLKMULTDRVAMPSEL', 'read-write',
            u"",
            11, 6)
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


class RM_Field_RAC_S_IFADCDBG_IFADCDISABLECLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_IFADCDISABLECLK, self).__init__(register,
            'IFADCDISABLECLK', 'RAC_S.IFADCDBG.IFADCDISABLECLK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCCLKSEL, self).__init__(register,
            'IFADCCLKSEL', 'RAC_S.IFADCTRIM0.IFADCCLKSEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSERIESAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSERIESAMPLVL, self).__init__(register,
            'IFADCLDOSERIESAMPLVL', 'RAC_S.IFADCTRIM0.IFADCLDOSERIESAMPLVL', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1, self).__init__(register,
            'IFADCLDOSHUNTAMPLVL1', 'RAC_S.IFADCTRIM0.IFADCLDOSHUNTAMPLVL1', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2, self).__init__(register,
            'IFADCLDOSHUNTAMPLVL2', 'RAC_S.IFADCTRIM0.IFADCLDOSHUNTAMPLVL2', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSHUNTCURLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSHUNTCURLVL1, self).__init__(register,
            'IFADCLDOSHUNTCURLVL1', 'RAC_S.IFADCTRIM0.IFADCLDOSHUNTCURLVL1', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSHUNTCURLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCLDOSHUNTCURLVL2, self).__init__(register,
            'IFADCLDOSHUNTCURLVL2', 'RAC_S.IFADCTRIM0.IFADCLDOSHUNTCURLVL2', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCOTACURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCOTACURRENT, self).__init__(register,
            'IFADCOTACURRENT', 'RAC_S.IFADCTRIM0.IFADCOTACURRENT', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCREFBUFAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCREFBUFAMPLVL, self).__init__(register,
            'IFADCREFBUFAMPLVL', 'RAC_S.IFADCTRIM0.IFADCREFBUFAMPLVL', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCREFBUFCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCREFBUFCURLVL, self).__init__(register,
            'IFADCREFBUFCURLVL', 'RAC_S.IFADCTRIM0.IFADCREFBUFCURLVL', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCSIDETONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCSIDETONEAMP, self).__init__(register,
            'IFADCSIDETONEAMP', 'RAC_S.IFADCTRIM0.IFADCSIDETONEAMP', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCSIDETONEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCSIDETONEFREQ, self).__init__(register,
            'IFADCSIDETONEFREQ', 'RAC_S.IFADCTRIM0.IFADCSIDETONEFREQ', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_IFADCENHALFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_IFADCENHALFMODE, self).__init__(register,
            'IFADCENHALFMODE', 'RAC_S.IFADCTRIM0.IFADCENHALFMODE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_IFADCVCMLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_IFADCVCMLVL, self).__init__(register,
            'IFADCVCMLVL', 'RAC_S.IFADCTRIM1.IFADCVCMLVL', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_IFADCENNEGRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_IFADCENNEGRES, self).__init__(register,
            'IFADCENNEGRES', 'RAC_S.IFADCTRIM1.IFADCENNEGRES', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_IFADCNEGRESCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_IFADCNEGRESCURRENT, self).__init__(register,
            'IFADCNEGRESCURRENT', 'RAC_S.IFADCTRIM1.IFADCNEGRESCURRENT', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_IFADCNEGRESVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_IFADCNEGRESVCM, self).__init__(register,
            'IFADCNEGRESVCM', 'RAC_S.IFADCTRIM1.IFADCNEGRESVCM', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_IFADCENSUBGMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_IFADCENSUBGMODE, self).__init__(register,
            'IFADCENSUBGMODE', 'RAC_S.IFADCTRIM1.IFADCENSUBGMODE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_IFADCTZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_IFADCTZ, self).__init__(register,
            'IFADCTZ', 'RAC_S.IFADCTRIM1.IFADCTZ', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_IFADCENXOBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_IFADCENXOBYPASS, self).__init__(register,
            'IFADCENXOBYPASS', 'RAC_S.IFADCTRIM1.IFADCENXOBYPASS', 'read-write',
            u"",
            13, 1)
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


class RM_Field_RAC_S_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL, self).__init__(register,
            'IFADCRCCALCOUNTERSTARTVAL', 'RAC_S.IFADCCAL.IFADCRCCALCOUNTERSTARTVAL', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCSTATUS_IFADCRCCALOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCSTATUS_IFADCRCCALOUT, self).__init__(register,
            'IFADCRCCALOUT', 'RAC_S.IFADCSTATUS.IFADCRCCALOUT', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXDEBUG_LNAMIXDISMXR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXDEBUG_LNAMIXDISMXR0, self).__init__(register,
            'LNAMIXDISMXR0', 'RAC_S.LNAMIXDEBUG.LNAMIXDISMXR0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXDEBUG_LNAMIXDISMXR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXDEBUG_LNAMIXDISMXR1, self).__init__(register,
            'LNAMIXDISMXR1', 'RAC_S.LNAMIXDEBUG.LNAMIXDISMXR1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXLNA0CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXLNA0CAPSEL, self).__init__(register,
            'LNAMIXLNA0CAPSEL', 'RAC_S.LNAMIXTRIM0.LNAMIXLNA0CAPSEL', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXMXRBIAS0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXMXRBIAS0, self).__init__(register,
            'LNAMIXMXRBIAS0', 'RAC_S.LNAMIXTRIM0.LNAMIXMXRBIAS0', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXVOUT0ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM0_LNAMIXVOUT0ADJ, self).__init__(register,
            'LNAMIXVOUT0ADJ', 'RAC_S.LNAMIXTRIM0.LNAMIXVOUT0ADJ', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXLNA1CAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXLNA1CAPSEL, self).__init__(register,
            'LNAMIXLNA1CAPSEL', 'RAC_S.LNAMIXTRIM1.LNAMIXLNA1CAPSEL', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXMXRBIAS1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXMXRBIAS1, self).__init__(register,
            'LNAMIXMXRBIAS1', 'RAC_S.LNAMIXTRIM1.LNAMIXMXRBIAS1', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXVOUT1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXVOUT1ADJ, self).__init__(register,
            'LNAMIXVOUT1ADJ', 'RAC_S.LNAMIXTRIM1.LNAMIXVOUT1ADJ', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXCURCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXCURCTRL, self).__init__(register,
            'LNAMIXCURCTRL', 'RAC_S.LNAMIXTRIM2.LNAMIXCURCTRL', 'read-write',
            u"",
            4, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXHIGHCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXHIGHCUR, self).__init__(register,
            'LNAMIXHIGHCUR', 'RAC_S.LNAMIXTRIM2.LNAMIXHIGHCUR', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXLOWCUR, self).__init__(register,
            'LNAMIXLOWCUR', 'RAC_S.LNAMIXTRIM2.LNAMIXLOWCUR', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXLNARESADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXLNARESADJ, self).__init__(register,
            'LNAMIXLNARESADJ', 'RAC_S.LNAMIXTRIM2.LNAMIXLNARESADJ', 'read-write',
            u"",
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXNCASADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXNCASADJ, self).__init__(register,
            'LNAMIXNCASADJ', 'RAC_S.LNAMIXTRIM2.LNAMIXNCASADJ', 'read-write',
            u"",
            17, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXPCASADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXPCASADJ, self).__init__(register,
            'LNAMIXPCASADJ', 'RAC_S.LNAMIXTRIM2.LNAMIXPCASADJ', 'read-write',
            u"",
            19, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXTRIMVREG, self).__init__(register,
            'LNAMIXTRIMVREG', 'RAC_S.LNAMIXTRIM2.LNAMIXTRIMVREG', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXIBIASADJN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXIBIASADJN, self).__init__(register,
            'LNAMIXIBIASADJN', 'RAC_S.LNAMIXTRIM3.LNAMIXIBIASADJN', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXIBIASADJP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXIBIASADJP, self).__init__(register,
            'LNAMIXIBIASADJP', 'RAC_S.LNAMIXTRIM3.LNAMIXIBIASADJP', 'read-write',
            u"",
            5, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXIBIASRANGEADJN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXIBIASRANGEADJN, self).__init__(register,
            'LNAMIXIBIASRANGEADJN', 'RAC_S.LNAMIXTRIM3.LNAMIXIBIASRANGEADJN', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXIBIASRANGEADJP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXIBIASRANGEADJP, self).__init__(register,
            'LNAMIXIBIASRANGEADJP', 'RAC_S.LNAMIXTRIM3.LNAMIXIBIASRANGEADJP', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDBWSEL, self).__init__(register,
            'LNAMIXRFPKDBWSEL', 'RAC_S.LNAMIXTRIM4.LNAMIXRFPKDBWSEL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO, self).__init__(register,
            'LNAMIXRFPKDCALCMLO', 'RAC_S.LNAMIXTRIM4.LNAMIXRFPKDCALCMLO', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI, self).__init__(register,
            'LNAMIXRFPKDCALCMHI', 'RAC_S.LNAMIXTRIM4.LNAMIXRFPKDCALCMHI', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELLO', 'RAC_S.LNAMIXTRIM4.LNAMIXRFPKDTHRESHSELLO', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELHI', 'RAC_S.LNAMIXTRIM4.LNAMIXRFPKDTHRESHSELHI', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALPMOSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALPMOSEN, self).__init__(register,
            'LNAMIXCALPMOSEN', 'RAC_S.LNAMIXCAL.LNAMIXCALPMOSEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALNMOSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALNMOSEN, self).__init__(register,
            'LNAMIXCALNMOSEN', 'RAC_S.LNAMIXCAL.LNAMIXCALNMOSEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALVMODE, self).__init__(register,
            'LNAMIXCALVMODE', 'RAC_S.LNAMIXCAL.LNAMIXCALVMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXENIRCAL0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXENIRCAL0, self).__init__(register,
            'LNAMIXENIRCAL0', 'RAC_S.LNAMIXCAL.LNAMIXENIRCAL0', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXENIRCAL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXENIRCAL1, self).__init__(register,
            'LNAMIXENIRCAL1', 'RAC_S.LNAMIXCAL.LNAMIXENIRCAL1', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL0AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL0AMP, self).__init__(register,
            'LNAMIXIRCAL0AMP', 'RAC_S.LNAMIXCAL.LNAMIXIRCAL0AMP', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL1AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL1AMP, self).__init__(register,
            'LNAMIXIRCAL1AMP', 'RAC_S.LNAMIXCAL.LNAMIXIRCAL1AMP', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN_LNAMIXENAMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN_LNAMIXENAMP0, self).__init__(register,
            'LNAMIXENAMP0', 'RAC_S.LNAMIXEN.LNAMIXENAMP0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN_LNAMIXENAMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN_LNAMIXENAMP1, self).__init__(register,
            'LNAMIXENAMP1', 'RAC_S.LNAMIXEN.LNAMIXENAMP1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN_LNAMIXENBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN_LNAMIXENBIAS, self).__init__(register,
            'LNAMIXENBIAS', 'RAC_S.LNAMIXEN.LNAMIXENBIAS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN_LNAMIXENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN_LNAMIXENLDO, self).__init__(register,
            'LNAMIXENLDO', 'RAC_S.LNAMIXEN.LNAMIXENLDO', 'read-write',
            u"",
            3, 1)
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


class RM_Field_RAC_S_PATRIM1_TXTRIMXPAVNB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_TXTRIMXPAVNB, self).__init__(register,
            'TXTRIMXPAVNB', 'RAC_S.PATRIM1.TXTRIMXPAVNB', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_TXTRIMXPAVPB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_TXTRIMXPAVPB, self).__init__(register,
            'TXTRIMXPAVPB', 'RAC_S.PATRIM1.TXTRIMXPAVPB', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_TXTRIMHPAVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_TXTRIMHPAVMID, self).__init__(register,
            'TXTRIMHPAVMID', 'RAC_S.PATRIM1.TXTRIMHPAVMID', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_TXTRIMHPAVNCAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_TXTRIMHPAVNCAS, self).__init__(register,
            'TXTRIMHPAVNCAS', 'RAC_S.PATRIM1.TXTRIMHPAVNCAS', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_TXTRIMHPAVPCAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_TXTRIMHPAVPCAS, self).__init__(register,
            'TXTRIMHPAVPCAS', 'RAC_S.PATRIM1.TXTRIMHPAVPCAS', 'read-write',
            u"",
            19, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM1_TXTRIMHPAVMIDCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM1_TXTRIMHPAVMIDCURRENT, self).__init__(register,
            'TXTRIMHPAVMIDCURRENT', 'RAC_S.PATRIM1.TXTRIMHPAVMIDCURRENT', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_TXTRIMCLKGENDUTYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_TXTRIMCLKGENDUTYN, self).__init__(register,
            'TXTRIMCLKGENDUTYN', 'RAC_S.PATRIM2.TXTRIMCLKGENDUTYN', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_TXTRIMCLKGENDUTYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_TXTRIMCLKGENDUTYP, self).__init__(register,
            'TXTRIMCLKGENDUTYP', 'RAC_S.PATRIM2.TXTRIMCLKGENDUTYP', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_TXTRIMCLKGENNOVFALL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_TXTRIMCLKGENNOVFALL, self).__init__(register,
            'TXTRIMCLKGENNOVFALL', 'RAC_S.PATRIM2.TXTRIMCLKGENNOVFALL', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_TXTRIMCLKGENNOVRISE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_TXTRIMCLKGENNOVRISE, self).__init__(register,
            'TXTRIMCLKGENNOVRISE', 'RAC_S.PATRIM2.TXTRIMCLKGENNOVRISE', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_TXTRIMDRVEDGENN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_TXTRIMDRVEDGENN, self).__init__(register,
            'TXTRIMDRVEDGENN', 'RAC_S.PATRIM2.TXTRIMDRVEDGENN', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_TXTRIMDRVEDGENP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_TXTRIMDRVEDGENP, self).__init__(register,
            'TXTRIMDRVEDGENP', 'RAC_S.PATRIM2.TXTRIMDRVEDGENP', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_TXTRIMDRVEDGEPN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_TXTRIMDRVEDGEPN, self).__init__(register,
            'TXTRIMDRVEDGEPN', 'RAC_S.PATRIM2.TXTRIMDRVEDGEPN', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM2_TXTRIMDRVEDGEPP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM2_TXTRIMDRVEDGEPP, self).__init__(register,
            'TXTRIMDRVEDGEPP', 'RAC_S.PATRIM2.TXTRIMDRVEDGEPP', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMDREGBLEED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMDREGBLEED, self).__init__(register,
            'TXTRIMDREGBLEED', 'RAC_S.PATRIM3.TXTRIMDREGBLEED', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMDREGBLEEDAUTO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMDREGBLEEDAUTO, self).__init__(register,
            'TXTRIMDREGBLEEDAUTO', 'RAC_S.PATRIM3.TXTRIMDREGBLEEDAUTO', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMOREGBLEEDAUTO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMOREGBLEEDAUTO, self).__init__(register,
            'TXTRIMOREGBLEEDAUTO', 'RAC_S.PATRIM3.TXTRIMOREGBLEEDAUTO', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMDREGFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMDREGFB, self).__init__(register,
            'TXTRIMDREGFB', 'RAC_S.PATRIM3.TXTRIMDREGFB', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMOREGFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMOREGFB, self).__init__(register,
            'TXTRIMOREGFB', 'RAC_S.PATRIM3.TXTRIMOREGFB', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMDREG, self).__init__(register,
            'TXTRIMDREG', 'RAC_S.PATRIM3.TXTRIMDREG', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMOREG, self).__init__(register,
            'TXTRIMOREG', 'RAC_S.PATRIM3.TXTRIMOREG', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMRREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMRREG, self).__init__(register,
            'TXTRIMRREG', 'RAC_S.PATRIM3.TXTRIMRREG', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMDREGPSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMDREGPSR, self).__init__(register,
            'TXTRIMDREGPSR', 'RAC_S.PATRIM3.TXTRIMDREGPSR', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMOREGPSR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMOREGPSR, self).__init__(register,
            'TXTRIMOREGPSR', 'RAC_S.PATRIM3.TXTRIMOREGPSR', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMDREGSLICES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMDREGSLICES, self).__init__(register,
            'TXTRIMDREGSLICES', 'RAC_S.PATRIM3.TXTRIMDREGSLICES', 'read-write',
            u"",
            23, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMOREGSLICES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMOREGSLICES, self).__init__(register,
            'TXTRIMOREGSLICES', 'RAC_S.PATRIM3.TXTRIMOREGSLICES', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMDREGMOREBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMDREGMOREBW, self).__init__(register,
            'TXTRIMDREGMOREBW', 'RAC_S.PATRIM3.TXTRIMDREGMOREBW', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMOREGMOREBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMOREGMOREBW, self).__init__(register,
            'TXTRIMOREGMOREBW', 'RAC_S.PATRIM3.TXTRIMOREGMOREBW', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM3_TXTRIMRREGCN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM3_TXTRIMRREGCN, self).__init__(register,
            'TXTRIMRREGCN', 'RAC_S.PATRIM3.TXTRIMRREGCN', 'read-write',
            u"",
            29, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXTRIMXPAVNBDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXTRIMXPAVNBDRV, self).__init__(register,
            'TXTRIMXPAVNBDRV', 'RAC_S.PATRIM4.TXTRIMXPAVNBDRV', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXTRIMXPAVPBDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXTRIMXPAVPBDRV, self).__init__(register,
            'TXTRIMXPAVPBDRV', 'RAC_S.PATRIM4.TXTRIMXPAVPBDRV', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXTRIMXPAVXSCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXTRIMXPAVXSCURRENT, self).__init__(register,
            'TXTRIMXPAVXSCURRENT', 'RAC_S.PATRIM4.TXTRIMXPAVXSCURRENT', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXXPAVXSCURRENTCOARSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXXPAVXSCURRENTCOARSE, self).__init__(register,
            'TXXPAVXSCURRENTCOARSE', 'RAC_S.PATRIM4.TXXPAVXSCURRENTCOARSE', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXXPAVXSCURRENTCOARSEMIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXXPAVXSCURRENTCOARSEMIN, self).__init__(register,
            'TXXPAVXSCURRENTCOARSEMIN', 'RAC_S.PATRIM4.TXXPAVXSCURRENTCOARSEMIN', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXXPAVXSCURRENTFINE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXXPAVXSCURRENTFINE, self).__init__(register,
            'TXXPAVXSCURRENTFINE', 'RAC_S.PATRIM4.TXXPAVXSCURRENTFINE', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXXPAVXSCURRENTSELHPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXXPAVXSCURRENTSELHPA, self).__init__(register,
            'TXXPAVXSCURRENTSELHPA', 'RAC_S.PATRIM4.TXXPAVXSCURRENTSELHPA', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXVXSCURRENTVREFN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXVXSCURRENTVREFN, self).__init__(register,
            'TXVXSCURRENTVREFN', 'RAC_S.PATRIM4.TXVXSCURRENTVREFN', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM4_TXVXSCURRENTVREFP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM4_TXVXSCURRENTVREFP, self).__init__(register,
            'TXVXSCURRENTVREFP', 'RAC_S.PATRIM4.TXVXSCURRENTVREFP', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM5_TXVNSRAIL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM5_TXVNSRAIL, self).__init__(register,
            'TXVNSRAIL', 'RAC_S.PATRIM5.TXVNSRAIL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM5_TXVPSRAIL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM5_TXVPSRAIL, self).__init__(register,
            'TXVPSRAIL', 'RAC_S.PATRIM5.TXVPSRAIL', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM5_TXVCASRAIL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM5_TXVCASRAIL, self).__init__(register,
            'TXVCASRAIL', 'RAC_S.PATRIM5.TXVCASRAIL', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM5_TXTRIMXPAVNS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM5_TXTRIMXPAVNS, self).__init__(register,
            'TXTRIMXPAVNS', 'RAC_S.PATRIM5.TXTRIMXPAVNS', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM5_TXTRIMXPAVPS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM5_TXTRIMXPAVPS, self).__init__(register,
            'TXTRIMXPAVPS', 'RAC_S.PATRIM5.TXTRIMXPAVPS', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PADEBUG0_TXOREGBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PADEBUG0_TXOREGBYPASS, self).__init__(register,
            'TXOREGBYPASS', 'RAC_S.PADEBUG0.TXOREGBYPASS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PADEBUG0_TXDREGBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PADEBUG0_TXDREGBYPASS, self).__init__(register,
            'TXDREGBYPASS', 'RAC_S.PADEBUG0.TXDREGBYPASS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PADEBUG0_TXRREGBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PADEBUG0_TXRREGBYPASS, self).__init__(register,
            'TXRREGBYPASS', 'RAC_S.PADEBUG0.TXRREGBYPASS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PADEBUG0_TXPDNVDDPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PADEBUG0_TXPDNVDDPA, self).__init__(register,
            'TXPDNVDDPA', 'RAC_S.PADEBUG0.TXPDNVDDPA', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPOWER_TXSTRIPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPOWER_TXSTRIPE, self).__init__(register,
            'TXSTRIPE', 'RAC_S.TXPOWER.TXSTRIPE', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPOWER_TXSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPOWER_TXSLICE, self).__init__(register,
            'TXSLICE', 'RAC_S.TXPOWER.TXSLICE', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPOWER_TXDRVSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPOWER_TXDRVSLICE, self).__init__(register,
            'TXDRVSLICE', 'RAC_S.TXPOWER.TXDRVSLICE', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPOWER_TXANARAMPODEV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPOWER_TXANARAMPODEV, self).__init__(register,
            'TXANARAMPODEV', 'RAC_S.TXPOWER.TXANARAMPODEV', 'read-write',
            u"",
            13, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPOWER_TXANARAMPDRVFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPOWER_TXANARAMPDRVFF, self).__init__(register,
            'TXANARAMPDRVFF', 'RAC_S.TXPOWER.TXANARAMPDRVFF', 'read-write',
            u"",
            18, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXANARAMPDRVBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXANARAMPDRVBW, self).__init__(register,
            'TXANARAMPDRVBW', 'RAC_S.TXRAMP.TXANARAMPDRVBW', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXANARAMPDRVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXANARAMPDRVEN, self).__init__(register,
            'TXANARAMPDRVEN', 'RAC_S.TXRAMP.TXANARAMPDRVEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXANARAMPODEVBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXANARAMPODEVBW, self).__init__(register,
            'TXANARAMPODEVBW', 'RAC_S.TXRAMP.TXANARAMPODEVBW', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXANARAMPODEVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXANARAMPODEVEN, self).__init__(register,
            'TXANARAMPODEVEN', 'RAC_S.TXRAMP.TXANARAMPODEVEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXBYPASSRAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXBYPASSRAMPCLK, self).__init__(register,
            'TXBYPASSRAMPCLK', 'RAC_S.TXRAMP.TXBYPASSRAMPCLK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXMODEPHASEFLIP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXMODEPHASEFLIP, self).__init__(register,
            'TXMODEPHASEFLIP', 'RAC_S.TXRAMP.TXMODEPHASEFLIP', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXPHASEDIGITAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXPHASEDIGITAL, self).__init__(register,
            'TXPHASEDIGITAL', 'RAC_S.TXRAMP.TXPHASEDIGITAL', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXRESETPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXRESETPAPOWER, self).__init__(register,
            'TXRESETPAPOWER', 'RAC_S.TXRAMP.TXRESETPAPOWER', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXUNMUTEENDRVFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXUNMUTEENDRVFF, self).__init__(register,
            'TXUNMUTEENDRVFF', 'RAC_S.TXRAMP.TXUNMUTEENDRVFF', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXBYPASSBBDIGREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXBYPASSBBDIGREG, self).__init__(register,
            'TXBYPASSBBDIGREG', 'RAC_S.TXRAMP.TXBYPASSBBDIGREG', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXBYPASSBUFREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXBYPASSBUFREG, self).__init__(register,
            'TXBYPASSBUFREG', 'RAC_S.TXRAMP.TXBYPASSBUFREG', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRAMP_TXSTARTUPITCCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRAMP_TXSTARTUPITCCORE, self).__init__(register,
            'TXSTARTUPITCCORE', 'RAC_S.TXRAMP.TXSTARTUPITCCORE', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGATRIM_PGACTUNE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGATRIM_PGACTUNE, self).__init__(register,
            'PGACTUNE', 'RAC_S.PGATRIM.PGACTUNE', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGATRIM_PGAVCMOUTTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGATRIM_PGAVCMOUTTRIM, self).__init__(register,
            'PGAVCMOUTTRIM', 'RAC_S.PGATRIM.PGAVCMOUTTRIM', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGATRIM_PGAVLDOTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGATRIM_PGAVLDOTRIM, self).__init__(register,
            'PGAVLDOTRIM', 'RAC_S.PGATRIM.PGAVLDOTRIM', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACAL_PGAOFFCALI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACAL_PGAOFFCALI, self).__init__(register,
            'PGAOFFCALI', 'RAC_S.PGACAL.PGAOFFCALI', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACAL_PGAOFFCALQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACAL_PGAOFFCALQ, self).__init__(register,
            'PGAOFFCALQ', 'RAC_S.PGACAL.PGAOFFCALQ', 'read-write',
            u"",
            24, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGABWMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGABWMODE, self).__init__(register,
            'PGABWMODE', 'RAC_S.PGACTRL.PGABWMODE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENBIAS, self).__init__(register,
            'PGAENBIAS', 'RAC_S.PGACTRL.PGAENBIAS', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENGHZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENGHZ, self).__init__(register,
            'PGAENGHZ', 'RAC_S.PGACTRL.PGAENGHZ', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENLATCHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENLATCHI, self).__init__(register,
            'PGAENLATCHI', 'RAC_S.PGACTRL.PGAENLATCHI', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENLATCHQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENLATCHQ, self).__init__(register,
            'PGAENLATCHQ', 'RAC_S.PGACTRL.PGAENLATCHQ', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGAENLDOLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGAENLDOLOAD, self).__init__(register,
            'PGAENLDOLOAD', 'RAC_S.PGACTRL.PGAENLDOLOAD', 'read-write',
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
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGATHRPKDLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGATHRPKDLOSEL, self).__init__(register,
            'PGATHRPKDLOSEL', 'RAC_S.PGACTRL.PGATHRPKDLOSEL', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PGACTRL_PGATHRPKDHISEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PGACTRL_PGATHRPKDHISEL, self).__init__(register,
            'PGATHRPKDHISEL', 'RAC_S.PGACTRL.PGATHRPKDHISEL', 'read-write',
            u"",
            21, 4)
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


class RM_Field_RAC_S_RFPATHEN0_LNAMIXEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN0_LNAMIXEN0, self).__init__(register,
            'LNAMIXEN0', 'RAC_S.RFPATHEN0.LNAMIXEN0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN0_LNAMIXRFATTDCEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN0_LNAMIXRFATTDCEN0, self).__init__(register,
            'LNAMIXRFATTDCEN0', 'RAC_S.RFPATHEN0.LNAMIXRFATTDCEN0', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN0_LNAMIXRFPKDENRF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN0_LNAMIXRFPKDENRF0, self).__init__(register,
            'LNAMIXRFPKDENRF0', 'RAC_S.RFPATHEN0.LNAMIXRFPKDENRF0', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN0_SYLODIVRLO0SUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN0_SYLODIVRLO0SUBGEN, self).__init__(register,
            'SYLODIVRLO0SUBGEN', 'RAC_S.RFPATHEN0.SYLODIVRLO0SUBGEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN0_TXENVMIDHPA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN0_TXENVMIDHPA0, self).__init__(register,
            'TXENVMIDHPA0', 'RAC_S.RFPATHEN0.TXENVMIDHPA0', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN0_TXENFSKPA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN0_TXENFSKPA0, self).__init__(register,
            'TXENFSKPA0', 'RAC_S.RFPATHEN0.TXENFSKPA0', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN0_TXENOFDMPA0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN0_TXENOFDMPA0, self).__init__(register,
            'TXENOFDMPA0', 'RAC_S.RFPATHEN0.TXENOFDMPA0', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXEN1, self).__init__(register,
            'LNAMIXEN1', 'RAC_S.RFPATHEN1.LNAMIXEN1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXRFATTDCEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXRFATTDCEN1, self).__init__(register,
            'LNAMIXRFATTDCEN1', 'RAC_S.RFPATHEN1.LNAMIXRFATTDCEN1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXRFPKDENRF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXRFPKDENRF1, self).__init__(register,
            'LNAMIXRFPKDENRF1', 'RAC_S.RFPATHEN1.LNAMIXRFPKDENRF1', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_SYLODIVRLO1SUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_SYLODIVRLO1SUBGEN, self).__init__(register,
            'SYLODIVRLO1SUBGEN', 'RAC_S.RFPATHEN1.SYLODIVRLO1SUBGEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_TXENVMIDHPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_TXENVMIDHPA1, self).__init__(register,
            'TXENVMIDHPA1', 'RAC_S.RFPATHEN1.TXENVMIDHPA1', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_TXENFSKPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_TXENFSKPA1, self).__init__(register,
            'TXENFSKPA1', 'RAC_S.RFPATHEN1.TXENFSKPA1', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_TXENOFDMPA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_TXENOFDMPA1, self).__init__(register,
            'TXENOFDMPA1', 'RAC_S.RFPATHEN1.TXENOFDMPA1', 'read-write',
            u"",
            12, 1)
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


class RM_Field_RAC_S_RX_LNAMIXENRFPKDLOTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXENRFPKDLOTHRESH, self).__init__(register,
            'LNAMIXENRFPKDLOTHRESH', 'RAC_S.RX.LNAMIXENRFPKDLOTHRESH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXLDOLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXLDOLOWCUR, self).__init__(register,
            'LNAMIXLDOLOWCUR', 'RAC_S.RX.LNAMIXLDOLOWCUR', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXREGLOADEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXREGLOADEN, self).__init__(register,
            'LNAMIXREGLOADEN', 'RAC_S.RX.LNAMIXREGLOADEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_PGAENLDO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_PGAENLDO, self).__init__(register,
            'PGAENLDO', 'RAC_S.RX.PGAENLDO', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYCHPQNC3EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYCHPQNC3EN, self).__init__(register,
            'SYCHPQNC3EN', 'RAC_S.RX.SYCHPQNC3EN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYCHPBIASTRIMBUFRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYCHPBIASTRIMBUFRX, self).__init__(register,
            'SYCHPBIASTRIMBUFRX', 'RAC_S.RX.SYCHPBIASTRIMBUFRX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYPFDCHPLPENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYPFDCHPLPENRX, self).__init__(register,
            'SYPFDCHPLPENRX', 'RAC_S.RX.SYPFDCHPLPENRX', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYPFDFPWENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYPFDFPWENRX, self).__init__(register,
            'SYPFDFPWENRX', 'RAC_S.RX.SYPFDFPWENRX', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_SYVCOVCAPFASTRAMPRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_SYVCOVCAPFASTRAMPRX, self).__init__(register,
            'SYVCOVCAPFASTRAMPRX', 'RAC_S.RX.SYVCOVCAPFASTRAMPRX', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_FEFILTOUTPUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_FEFILTOUTPUTSEL, self).__init__(register,
            'FEFILTOUTPUTSEL', 'RAC_S.RX.FEFILTOUTPUTSEL', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENDREG, self).__init__(register,
            'TXENDREG', 'RAC_S.TX.TXENDREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENOREG, self).__init__(register,
            'TXENOREG', 'RAC_S.TX.TXENOREG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENOREGBLEED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENOREGBLEED, self).__init__(register,
            'TXENOREGBLEED', 'RAC_S.TX.TXENOREGBLEED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENRREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENRREG, self).__init__(register,
            'TXENRREG', 'RAC_S.TX.TXENRREG', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENCLKGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENCLKGEN, self).__init__(register,
            'TXENCLKGEN', 'RAC_S.TX.TXENCLKGEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENPADDCFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENPADDCFORCE, self).__init__(register,
            'TXENPADDCFORCE', 'RAC_S.TX.TXENPADDCFORCE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENPKDOGND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENPKDOGND, self).__init__(register,
            'TXENPKDOGND', 'RAC_S.TX.TXENPKDOGND', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENPKDOGNDCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENPKDOGNDCLK, self).__init__(register,
            'TXENPKDOGNDCLK', 'RAC_S.TX.TXENPKDOGNDCLK', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENPUPDNPROTECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENPUPDNPROTECT, self).__init__(register,
            'TXENPUPDNPROTECT', 'RAC_S.TX.TXENPUPDNPROTECT', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENRAMPCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENRAMPCLK, self).__init__(register,
            'TXENRAMPCLK', 'RAC_S.TX.TXENRAMPCLK', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENVTRCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENVTRCURRENT, self).__init__(register,
            'TXENVTRCURRENT', 'RAC_S.TX.TXENVTRCURRENT', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENXDRVVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENXDRVVMID, self).__init__(register,
            'TXENXDRVVMID', 'RAC_S.TX.TXENXDRVVMID', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXMODESE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXMODESE, self).__init__(register,
            'TXMODESE', 'RAC_S.TX.TXMODESE', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENRFPKD0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENRFPKD0, self).__init__(register,
            'TXENRFPKD0', 'RAC_S.TX.TXENRFPKD0', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENRFPKD1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENRFPKD1, self).__init__(register,
            'TXENRFPKD1', 'RAC_S.TX.TXENRFPKD1', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENRREGBLEED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENRREGBLEED, self).__init__(register,
            'TXENRREGBLEED', 'RAC_S.TX.TXENRREGBLEED', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_SYCHPBIASTRIMBUFTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_SYCHPBIASTRIMBUFTX, self).__init__(register,
            'SYCHPBIASTRIMBUFTX', 'RAC_S.TX.SYCHPBIASTRIMBUFTX', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_SYPFDCHPLPENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_SYPFDCHPLPENTX, self).__init__(register,
            'SYPFDCHPLPENTX', 'RAC_S.TX.SYPFDCHPLPENTX', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_SYPFDFPWENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_SYPFDFPWENTX, self).__init__(register,
            'SYPFDFPWENTX', 'RAC_S.TX.SYPFDFPWENTX', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_SYVCOVCAPFASTRAMPTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_SYVCOVCAPFASTRAMPTX, self).__init__(register,
            'SYVCOVCAPFASTRAMPTX', 'RAC_S.TX.SYVCOVCAPFASTRAMPTX', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXMODEPMOSOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXMODEPMOSOFF, self).__init__(register,
            'TXMODEPMOSOFF', 'RAC_S.TX.TXMODEPMOSOFF', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXSWPENDACI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXSWPENDACI, self).__init__(register,
            'TXSWPENDACI', 'RAC_S.TX.TXSWPENDACI', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXSWPENDACQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXSWPENDACQ, self).__init__(register,
            'TXSWPENDACQ', 'RAC_S.TX.TXSWPENDACQ', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENITCDAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENITCDAC, self).__init__(register,
            'TXENITCDAC', 'RAC_S.TX.TXENITCDAC', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENITCPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENITCPA, self).__init__(register,
            'TXENITCPA', 'RAC_S.TX.TXENITCPA', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_TXENITCCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_TXENITCCORE, self).__init__(register,
            'TXENITCCORE', 'RAC_S.TX.TXENITCCORE', 'read-write',
            u"",
            28, 1)
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


class RM_Field_RAC_S_SYTRIM0_SYCHPCURRRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPCURRRX, self).__init__(register,
            'SYCHPCURRRX', 'RAC_S.SYTRIM0.SYCHPCURRRX', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPCURRTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPCURRTX, self).__init__(register,
            'SYCHPCURRTX', 'RAC_S.SYTRIM0.SYCHPCURRTX', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPLEVNSRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPLEVNSRC, self).__init__(register,
            'SYCHPLEVNSRC', 'RAC_S.SYTRIM0.SYCHPLEVNSRC', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPLEVPSRCRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPLEVPSRCRX, self).__init__(register,
            'SYCHPLEVPSRCRX', 'RAC_S.SYTRIM0.SYCHPLEVPSRCRX', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPLEVPSRCTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPLEVPSRCTX, self).__init__(register,
            'SYCHPLEVPSRCTX', 'RAC_S.SYTRIM0.SYCHPLEVPSRCTX', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPSRCENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPSRCENRX, self).__init__(register,
            'SYCHPSRCENRX', 'RAC_S.SYTRIM0.SYCHPSRCENRX', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPSRCENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPSRCENTX, self).__init__(register,
            'SYCHPSRCENTX', 'RAC_S.SYTRIM0.SYCHPSRCENTX', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYCHPREPLICACURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYCHPREPLICACURRADJ, self).__init__(register,
            'SYCHPREPLICACURRADJ', 'RAC_S.SYTRIM0.SYCHPREPLICACURRADJ', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYTRIMCHPREGAMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYTRIMCHPREGAMPBIAS, self).__init__(register,
            'SYTRIMCHPREGAMPBIAS', 'RAC_S.SYTRIM0.SYTRIMCHPREGAMPBIAS', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYTRIMCHPREGAMPBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYTRIMCHPREGAMPBW, self).__init__(register,
            'SYTRIMCHPREGAMPBW', 'RAC_S.SYTRIM0.SYTRIMCHPREGAMPBW', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMCORERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMCORERX, self).__init__(register,
            'SYLODIVLDOTRIMCORERX', 'RAC_S.SYTRIM1.SYLODIVLDOTRIMCORERX', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMCORETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMCORETX, self).__init__(register,
            'SYLODIVLDOTRIMCORETX', 'RAC_S.SYTRIM1.SYLODIVLDOTRIMCORETX', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMNDIORX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMNDIORX, self).__init__(register,
            'SYLODIVLDOTRIMNDIORX', 'RAC_S.SYTRIM1.SYLODIVLDOTRIMNDIORX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMNDIOTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVLDOTRIMNDIOTX, self).__init__(register,
            'SYLODIVLDOTRIMNDIOTX', 'RAC_S.SYTRIM1.SYLODIVLDOTRIMNDIOTX', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVSELOUTINVADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVSELOUTINVADC, self).__init__(register,
            'SYLODIVSELOUTINVADC', 'RAC_S.SYTRIM1.SYLODIVSELOUTINVADC', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVTLOTRIMDELAYOFDM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVTLOTRIMDELAYOFDM, self).__init__(register,
            'SYLODIVTLOTRIMDELAYOFDM', 'RAC_S.SYTRIM1.SYLODIVTLOTRIMDELAYOFDM', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYLODIVTLOTRIMDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYLODIVTLOTRIMDELAY, self).__init__(register,
            'SYLODIVTLOTRIMDELAY', 'RAC_S.SYTRIM1.SYLODIVTLOTRIMDELAY', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYMMDREPLICA1CURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYMMDREPLICA1CURRADJ, self).__init__(register,
            'SYMMDREPLICA1CURRADJ', 'RAC_S.SYTRIM1.SYMMDREPLICA1CURRADJ', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYMMDREPLICA2CURRADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYMMDREPLICA2CURRADJ, self).__init__(register,
            'SYMMDREPLICA2CURRADJ', 'RAC_S.SYTRIM1.SYMMDREPLICA2CURRADJ', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTRIMMMDREGAMPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTRIMMMDREGAMPBIAS, self).__init__(register,
            'SYTRIMMMDREGAMPBIAS', 'RAC_S.SYTRIM1.SYTRIMMMDREGAMPBIAS', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTRIMMMDREGAMPBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTRIMMMDREGAMPBW, self).__init__(register,
            'SYTRIMMMDREGAMPBW', 'RAC_S.SYTRIM1.SYTRIMMMDREGAMPBW', 'read-write',
            u"",
            30, 2)
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


class RM_Field_RAC_S_SYEN_SYCHPLPENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYCHPLPENRX, self).__init__(register,
            'SYCHPLPENRX', 'RAC_S.SYEN.SYCHPLPENRX', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYCHPLPENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYCHPLPENTX, self).__init__(register,
            'SYCHPLPENTX', 'RAC_S.SYEN.SYCHPLPENTX', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENCHPREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENCHPREG, self).__init__(register,
            'SYENCHPREG', 'RAC_S.SYEN.SYENCHPREG', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENCHPREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENCHPREPLICA, self).__init__(register,
            'SYENCHPREPLICA', 'RAC_S.SYEN.SYENCHPREPLICA', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENMMDREG, self).__init__(register,
            'SYENMMDREG', 'RAC_S.SYEN.SYENMMDREG', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENMMDREPLICA1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENMMDREPLICA1, self).__init__(register,
            'SYENMMDREPLICA1', 'RAC_S.SYEN.SYENMMDREPLICA1', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENMMDREPLICA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENMMDREPLICA2, self).__init__(register,
            'SYENMMDREPLICA2', 'RAC_S.SYEN.SYENMMDREPLICA2', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOBIAS, self).__init__(register,
            'SYENVCOBIAS', 'RAC_S.SYEN.SYENVCOBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOPFET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOPFET, self).__init__(register,
            'SYENVCOPFET', 'RAC_S.SYEN.SYENVCOPFET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOREG, self).__init__(register,
            'SYENVCOREG', 'RAC_S.SYEN.SYENVCOREG', 'read-write',
            u"",
            10, 1)
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


class RM_Field_RAC_S_SYLOEN_SYLODIVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVEN, self).__init__(register,
            'SYLODIVEN', 'RAC_S.SYLOEN.SYLODIVEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVLDOBIASEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVLDOBIASEN, self).__init__(register,
            'SYLODIVLDOBIASEN', 'RAC_S.SYLOEN.SYLODIVLDOBIASEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVLDOEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVLDOEN, self).__init__(register,
            'SYLODIVLDOEN', 'RAC_S.SYLOEN.SYLODIVLDOEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVRLOSUBGRADCCLKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVRLOSUBGRADCCLKEN, self).__init__(register,
            'SYLODIVRLOSUBGRADCCLKEN', 'RAC_S.SYLOEN.SYLODIVRLOSUBGRADCCLKEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVSMUXDIVEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVSMUXDIVEN, self).__init__(register,
            'SYLODIVSMUXDIVEN', 'RAC_S.SYLOEN.SYLODIVSMUXDIVEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLOSUBGAUXEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLOSUBGAUXEN, self).__init__(register,
            'SYLODIVTLOSUBGAUXEN', 'RAC_S.SYLOEN.SYLODIVTLOSUBGAUXEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLOSUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLOSUBGEN, self).__init__(register,
            'SYLODIVTLOSUBGEN', 'RAC_S.SYLOEN.SYLODIVTLOSUBGEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYLODIVTLOOFDMSUBGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYLODIVTLOOFDMSUBGEN, self).__init__(register,
            'SYLODIVTLOOFDMSUBGEN', 'RAC_S.SYLOEN.SYLODIVTLOOFDMSUBGEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDDIVRSDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDDIVRSDIG, self).__init__(register,
            'SYMMDDIVRSDIG', 'RAC_S.SYMMDCTRL.SYMMDDIVRSDIG', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDMODERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDMODERX, self).__init__(register,
            'SYMMDMODERX', 'RAC_S.SYMMDCTRL.SYMMDMODERX', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDMODETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDMODETX, self).__init__(register,
            'SYMMDMODETX', 'RAC_S.SYMMDCTRL.SYMMDMODETX', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDIVCTRL_SYLODIVRADCDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDIVCTRL_SYLODIVRADCDIV, self).__init__(register,
            'SYLODIVRADCDIV', 'RAC_S.SYDIVCTRL.SYLODIVRADCDIV', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDIVCTRL_SYLODIVSMUXDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDIVCTRL_SYLODIVSMUXDIV, self).__init__(register,
            'SYLODIVSMUXDIV', 'RAC_S.SYDIVCTRL.SYLODIVSMUXDIV', 'read-write',
            u"",
            16, 2)
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


class RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDTHRESH, self).__init__(register,
            'TXPKDOGNDTHRESH', 'RAC_S.TXOGNDPKD.TXPKDOGNDTHRESH', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDBYPASSLATCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDBYPASSLATCH, self).__init__(register,
            'TXPKDOGNDBYPASSLATCH', 'RAC_S.TXOGNDPKD.TXPKDOGNDBYPASSLATCH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDTYPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDTYPE, self).__init__(register,
            'TXPKDOGNDTYPE', 'RAC_S.TXOGNDPKD.TXPKDOGNDTYPE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDRESET, self).__init__(register,
            'TXPKDOGNDRESET', 'RAC_S.TXOGNDPKD.TXPKDOGNDRESET', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDATTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDATTEN, self).__init__(register,
            'TXPKDOGNDATTEN', 'RAC_S.TXOGNDPKD.TXPKDOGNDATTEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDCLKHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOGNDPKD_TXPKDOGNDCLKHIGH, self).__init__(register,
            'TXPKDOGNDCLKHIGH', 'RAC_S.TXOGNDPKD.TXPKDOGNDCLKHIGH', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOGNDPKDSTATUS_TXOGNDPKDN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOGNDPKDSTATUS_TXOGNDPKDN, self).__init__(register,
            'TXOGNDPKDN', 'RAC_S.TXOGNDPKDSTATUS.TXOGNDPKDN', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOGNDPKDSTATUS_TXOGNDPKDP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOGNDPKDSTATUS_TXOGNDPKDP, self).__init__(register,
            'TXOGNDPKDP', 'RAC_S.TXOGNDPKDSTATUS.TXOGNDPKDP', 'read-only',
            u"",
            1, 1)
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


class RM_Field_RAC_S_SPARE_SYSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SYSPARE, self).__init__(register,
            'SYSPARE', 'RAC_S.SPARE.SYSPARE', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_TXSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_TXSPARE, self).__init__(register,
            'TXSPARE', 'RAC_S.SPARE.TXSPARE', 'read-write',
            u"",
            11, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_SPARE0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SPARE0, self).__init__(register,
            'SPARE0', 'RAC_S.SPARE.SPARE0', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_IFADCCTRLRESERVED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_IFADCCTRLRESERVED, self).__init__(register,
            'IFADCCTRLRESERVED', 'RAC_S.SPARE.IFADCCTRLRESERVED', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_IFADCCTRLRESERVEDLV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_IFADCCTRLRESERVEDLV, self).__init__(register,
            'IFADCCTRLRESERVEDLV', 'RAC_S.SPARE.IFADCCTRLRESERVEDLV', 'read-write',
            u"",
            29, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMEENRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMEENRETIME, self).__init__(register,
            'GPPLLCLKRETIMEENRETIME', 'RAC_S.GPPLLCLKRETIMECTRL.GPPLLCLKRETIMEENRETIME', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMEDISRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMEDISRETIME, self).__init__(register,
            'GPPLLCLKRETIMEDISRETIME', 'RAC_S.GPPLLCLKRETIMECTRL.GPPLLCLKRETIMEDISRETIME', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMERESETN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMERESETN, self).__init__(register,
            'GPPLLCLKRETIMERESETN', 'RAC_S.GPPLLCLKRETIMECTRL.GPPLLCLKRETIMERESETN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMELIMITH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMELIMITH, self).__init__(register,
            'GPPLLCLKRETIMELIMITH', 'RAC_S.GPPLLCLKRETIMECTRL.GPPLLCLKRETIMELIMITH', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMELIMITL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_GPPLLCLKRETIMECTRL_GPPLLCLKRETIMELIMITL, self).__init__(register,
            'GPPLLCLKRETIMELIMITL', 'RAC_S.GPPLLCLKRETIMECTRL.GPPLLCLKRETIMELIMITL', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_GPPLLCLKRETIMESTATUS_GPPLLCLKRETIMECLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_GPPLLCLKRETIMESTATUS_GPPLLCLKRETIMECLKSEL, self).__init__(register,
            'GPPLLCLKRETIMECLKSEL', 'RAC_S.GPPLLCLKRETIMESTATUS.GPPLLCLKRETIMECLKSEL', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_GPPLLCLKRETIMESTATUS_GPPLLCLKRETIMERESETNLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_GPPLLCLKRETIMESTATUS_GPPLLCLKRETIMERESETNLO, self).__init__(register,
            'GPPLLCLKRETIMERESETNLO', 'RAC_S.GPPLLCLKRETIMESTATUS.GPPLLCLKRETIMERESETNLO', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMBBDIGREGIOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMBBDIGREGIOUT, self).__init__(register,
            'TXTRIMBBDIGREGIOUT', 'RAC_S.PATRIM6.TXTRIMBBDIGREGIOUT', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMBBREGVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMBBREGVREF, self).__init__(register,
            'TXTRIMBBREGVREF', 'RAC_S.PATRIM6.TXTRIMBBREGVREF', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMBBREGFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMBBREGFB, self).__init__(register,
            'TXTRIMBBREGFB', 'RAC_S.PATRIM6.TXTRIMBBREGFB', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMFILVCOM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMFILVCOM, self).__init__(register,
            'TXTRIMFILVCOM', 'RAC_S.PATRIM6.TXTRIMFILVCOM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMFILCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMFILCAP, self).__init__(register,
            'TXTRIMFILCAP', 'RAC_S.PATRIM6.TXTRIMFILCAP', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMFILGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMFILGAIN, self).__init__(register,
            'TXTRIMFILGAIN', 'RAC_S.PATRIM6.TXTRIMFILGAIN', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMFILRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMFILRES, self).__init__(register,
            'TXTRIMFILRES', 'RAC_S.PATRIM6.TXTRIMFILRES', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMBIASNMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMBIASNMAX, self).__init__(register,
            'TXTRIMBIASNMAX', 'RAC_S.PATRIM6.TXTRIMBIASNMAX', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM6_TXTRIMBIASPMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM6_TXTRIMBIASPMAX, self).__init__(register,
            'TXTRIMBIASPMAX', 'RAC_S.PATRIM6.TXTRIMBIASPMAX', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM7_TXTRIMMIXGMBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM7_TXTRIMMIXGMBIAS, self).__init__(register,
            'TXTRIMMIXGMBIAS', 'RAC_S.PATRIM7.TXTRIMMIXGMBIAS', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM7_TXTRIMMIXLOBIASI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM7_TXTRIMMIXLOBIASI, self).__init__(register,
            'TXTRIMMIXLOBIASI', 'RAC_S.PATRIM7.TXTRIMMIXLOBIASI', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM7_TXTRIMMIXLOBIASQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM7_TXTRIMMIXLOBIASQ, self).__init__(register,
            'TXTRIMMIXLOBIASQ', 'RAC_S.PATRIM7.TXTRIMMIXLOBIASQ', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM7_TXTRIMMIXINDSW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM7_TXTRIMMIXINDSW, self).__init__(register,
            'TXTRIMMIXINDSW', 'RAC_S.PATRIM7.TXTRIMMIXINDSW', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM7_TXTRIMSHVDDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM7_TXTRIMSHVDDREG, self).__init__(register,
            'TXTRIMSHVDDREG', 'RAC_S.PATRIM7.TXTRIMSHVDDREG', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM7_TXTRIMSHIBINBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM7_TXTRIMSHIBINBUF, self).__init__(register,
            'TXTRIMSHIBINBUF', 'RAC_S.PATRIM7.TXTRIMSHIBINBUF', 'read-write',
            u"",
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM7_TXTRIMSHIBVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM7_TXTRIMSHIBVCM, self).__init__(register,
            'TXTRIMSHIBVCM', 'RAC_S.PATRIM7.TXTRIMSHIBVCM', 'read-write',
            u"",
            19, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM7_TXTRIMSHVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM7_TXTRIMSHVCM, self).__init__(register,
            'TXTRIMSHVCM', 'RAC_S.PATRIM7.TXTRIMSHVCM', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM8_TXTRIMRFPKDVDDD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM8_TXTRIMRFPKDVDDD, self).__init__(register,
            'TXTRIMRFPKDVDDD', 'RAC_S.PATRIM8.TXTRIMRFPKDVDDD', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM8_TXTRIMRFPKDIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM8_TXTRIMRFPKDIB, self).__init__(register,
            'TXTRIMRFPKDIB', 'RAC_S.PATRIM8.TXTRIMRFPKDIB', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM8_TXTRIMRFPKDVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM8_TXTRIMRFPKDVCM, self).__init__(register,
            'TXTRIMRFPKDVCM', 'RAC_S.PATRIM8.TXTRIMRFPKDVCM', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM8_TXTRIMBUFBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM8_TXTRIMBUFBIAS, self).__init__(register,
            'TXTRIMBUFBIAS', 'RAC_S.PATRIM8.TXTRIMBUFBIAS', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM8_TXTRIMBUFSLICESN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM8_TXTRIMBUFSLICESN, self).__init__(register,
            'TXTRIMBUFSLICESN', 'RAC_S.PATRIM8.TXTRIMBUFSLICESN', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM8_TXTRIMBUFSLICESP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM8_TXTRIMBUFSLICESP, self).__init__(register,
            'TXTRIMBUFSLICESP', 'RAC_S.PATRIM8.TXTRIMBUFSLICESP', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM8_TXTRIMBUFVMID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM8_TXTRIMBUFVMID, self).__init__(register,
            'TXTRIMBUFVMID', 'RAC_S.PATRIM8.TXTRIMBUFVMID', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM8_TXTRIMBUFVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM8_TXTRIMBUFVREG, self).__init__(register,
            'TXTRIMBUFVREG', 'RAC_S.PATRIM8.TXTRIMBUFVREG', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM9_TXTRIMDACVCAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM9_TXTRIMDACVCAS, self).__init__(register,
            'TXTRIMDACVCAS', 'RAC_S.PATRIM9.TXTRIMDACVCAS', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM9_TXTRIMDACSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM9_TXTRIMDACSCALE, self).__init__(register,
            'TXTRIMDACSCALE', 'RAC_S.PATRIM9.TXTRIMDACSCALE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM9_TXTRIMDACVDDD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM9_TXTRIMDACVDDD, self).__init__(register,
            'TXTRIMDACVDDD', 'RAC_S.PATRIM9.TXTRIMDACVDDD', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM9_TXTRIMDACIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM9_TXTRIMDACIBIAS, self).__init__(register,
            'TXTRIMDACIBIAS', 'RAC_S.PATRIM9.TXTRIMDACIBIAS', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM9_TXTRIMPASLICESN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM9_TXTRIMPASLICESN, self).__init__(register,
            'TXTRIMPASLICESN', 'RAC_S.PATRIM9.TXTRIMPASLICESN', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM9_TXTRIMPASLICESP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM9_TXTRIMPASLICESP, self).__init__(register,
            'TXTRIMPASLICESP', 'RAC_S.PATRIM9.TXTRIMPASLICESP', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM10_TXTRIMPAMIRROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM10_TXTRIMPAMIRROR, self).__init__(register,
            'TXTRIMPAMIRROR', 'RAC_S.PATRIM10.TXTRIMPAMIRROR', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM10_TXTRIMPANBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM10_TXTRIMPANBIAS, self).__init__(register,
            'TXTRIMPANBIAS', 'RAC_S.PATRIM10.TXTRIMPANBIAS', 'read-write',
            u"",
            2, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM10_TXTRIMPANCBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM10_TXTRIMPANCBIAS, self).__init__(register,
            'TXTRIMPANCBIAS', 'RAC_S.PATRIM10.TXTRIMPANCBIAS', 'read-write',
            u"",
            10, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM10_TXTRIMPAPBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM10_TXTRIMPAPBIAS, self).__init__(register,
            'TXTRIMPAPBIAS', 'RAC_S.PATRIM10.TXTRIMPAPBIAS', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM10_TXTRIMPAPCBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM10_TXTRIMPAPCBIAS, self).__init__(register,
            'TXTRIMPAPCBIAS', 'RAC_S.PATRIM10.TXTRIMPAPCBIAS', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRFPKD_TXRESETRFPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRFPKD_TXRESETRFPKD, self).__init__(register,
            'TXRESETRFPKD', 'RAC_S.TXRFPKD.TXRESETRFPKD', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRFPKD_TXSELRFPKDREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRFPKD_TXSELRFPKDREF, self).__init__(register,
            'TXSELRFPKDREF', 'RAC_S.TXRFPKD.TXSELRFPKDREF', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRFPKD_TXRFPKDOUTMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRFPKD_TXRFPKDOUTMODE, self).__init__(register,
            'TXRFPKDOUTMODE', 'RAC_S.TXRFPKD.TXRFPKDOUTMODE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRFPKD_TXRFPKDCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRFPKD_TXRFPKDCALMODE, self).__init__(register,
            'TXRFPKDCALMODE', 'RAC_S.TXRFPKD.TXRFPKDCALMODE', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRFPKD_TXRFPKDCALCODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRFPKD_TXRFPKDCALCODE, self).__init__(register,
            'TXRFPKDCALCODE', 'RAC_S.TXRFPKD.TXRFPKDCALCODE', 'read-write',
            u"",
            12, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXRFPKD_TXRFPKDCAPATT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXRFPKD_TXRFPKDCAPATT, self).__init__(register,
            'TXRFPKDCAPATT', 'RAC_S.TXRFPKD.TXRFPKDCAPATT', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXSTATUS_TXRFPKDOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXSTATUS_TXRFPKDOUT, self).__init__(register,
            'TXRFPKDOUT', 'RAC_S.TXSTATUS.TXRFPKDOUT', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBBDIGREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBBDIGREG, self).__init__(register,
            'TXENBBDIGREG', 'RAC_S.TXOFDM.TXENBBDIGREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBBREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBBREG, self).__init__(register,
            'TXENBBREG', 'RAC_S.TXOFDM.TXENBBREG', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBBREGBLEED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBBREGBLEED, self).__init__(register,
            'TXENBBREGBLEED', 'RAC_S.TXOFDM.TXENBBREGBLEED', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBUF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBUF0, self).__init__(register,
            'TXENBUF0', 'RAC_S.TXOFDM.TXENBUF0', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBUF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBUF1, self).__init__(register,
            'TXENBUF1', 'RAC_S.TXOFDM.TXENBUF1', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBBDACI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBBDACI, self).__init__(register,
            'TXENBBDACI', 'RAC_S.TXOFDM.TXENBBDACI', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBBDACQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBBDACQ, self).__init__(register,
            'TXENBBDACQ', 'RAC_S.TXOFDM.TXENBBDACQ', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENMIX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENMIX, self).__init__(register,
            'TXENMIX', 'RAC_S.TXOFDM.TXENMIX', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBUFREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBUFREG, self).__init__(register,
            'TXENBUFREG', 'RAC_S.TXOFDM.TXENBUFREG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBUFREGBLEED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBUFREGBLEED, self).__init__(register,
            'TXENBUFREGBLEED', 'RAC_S.TXOFDM.TXENBUFREGBLEED', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENMIXRLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENMIXRLOAD, self).__init__(register,
            'TXENMIXRLOAD', 'RAC_S.TXOFDM.TXENMIXRLOAD', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENPAFASTSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENPAFASTSTARTUP, self).__init__(register,
            'TXENPAFASTSTARTUP', 'RAC_S.TXOFDM.TXENPAFASTSTARTUP', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENSH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENSH, self).__init__(register,
            'TXENSH', 'RAC_S.TXOFDM.TXENSH', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENSHINBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENSHINBUF, self).__init__(register,
            'TXENSHINBUF', 'RAC_S.TXOFDM.TXENSHINBUF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENSHUGB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENSHUGB, self).__init__(register,
            'TXENSHUGB', 'RAC_S.TXOFDM.TXENSHUGB', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENFILI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENFILI, self).__init__(register,
            'TXENFILI', 'RAC_S.TXOFDM.TXENFILI', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENFILQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENFILQ, self).__init__(register,
            'TXENFILQ', 'RAC_S.TXOFDM.TXENFILQ', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENBBDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENBBDATA, self).__init__(register,
            'TXENBBDATA', 'RAC_S.TXOFDM.TXENBBDATA', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENPACMOS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENPACMOS, self).__init__(register,
            'TXENPACMOS', 'RAC_S.TXOFDM.TXENPACMOS', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXENTXBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXENTXBIAS, self).__init__(register,
            'TXENTXBIAS', 'RAC_S.TXOFDM.TXENTXBIAS', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXRESETSHCLKDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXRESETSHCLKDIV, self).__init__(register,
            'TXRESETSHCLKDIV', 'RAC_S.TXOFDM.TXRESETSHCLKDIV', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXOFDM_TXSELPABIASMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXOFDM_TXSELPABIASMODE, self).__init__(register,
            'TXSELPABIASMODE', 'RAC_S.TXOFDM.TXSELPABIASMODE', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELMIXCTUNE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELMIXCTUNE, self).__init__(register,
            'TXSELMIXCTUNE', 'RAC_S.TXMIX.TXSELMIXCTUNE', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELMIXGMSLICEI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELMIXGMSLICEI, self).__init__(register,
            'TXSELMIXGMSLICEI', 'RAC_S.TXMIX.TXSELMIXGMSLICEI', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELMIXGMSLICEQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELMIXGMSLICEQ, self).__init__(register,
            'TXSELMIXGMSLICEQ', 'RAC_S.TXMIX.TXSELMIXGMSLICEQ', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELMIXRLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELMIXRLOAD, self).__init__(register,
            'TXSELMIXRLOAD', 'RAC_S.TXMIX.TXSELMIXRLOAD', 'read-write',
            u"",
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELMIXBAND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELMIXBAND, self).__init__(register,
            'TXSELMIXBAND', 'RAC_S.TXMIX.TXSELMIXBAND', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELMIXRDEG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELMIXRDEG, self).__init__(register,
            'TXSELMIXRDEG', 'RAC_S.TXMIX.TXSELMIXRDEG', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXMIXCAPPULLDOWN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXMIXCAPPULLDOWN, self).__init__(register,
            'TXMIXCAPPULLDOWN', 'RAC_S.TXMIX.TXMIXCAPPULLDOWN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELSHINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELSHINPUT, self).__init__(register,
            'TXSELSHINPUT', 'RAC_S.TXMIX.TXSELSHINPUT', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELSHCAPATTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELSHCAPATTN, self).__init__(register,
            'TXSELSHCAPATTN', 'RAC_S.TXMIX.TXSELSHCAPATTN', 'read-write',
            u"",
            23, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELSHCLKDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELSHCLKDIV, self).__init__(register,
            'TXSELSHCLKDIV', 'RAC_S.TXMIX.TXSELSHCLKDIV', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXMIX_TXSELSHINBUFATTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXMIX_TXSELSHINBUFATTN, self).__init__(register,
            'TXSELSHINBUFATTN', 'RAC_S.TXMIX.TXSELSHINBUFATTN', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXITC_TXSELITCDAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXITC_TXSELITCDAC, self).__init__(register,
            'TXSELITCDAC', 'RAC_S.TXITC.TXSELITCDAC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXITC_TXSELITCPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXITC_TXSELITCPA, self).__init__(register,
            'TXSELITCPA', 'RAC_S.TXITC.TXSELITCPA', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXITC_TXSELITCDACLEVEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXITC_TXSELITCDACLEVEL, self).__init__(register,
            'TXSELITCDACLEVEL', 'RAC_S.TXITC.TXSELITCDACLEVEL', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXITC_TXSELITCPALEVEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXITC_TXSELITCPALEVEL, self).__init__(register,
            'TXSELITCPALEVEL', 'RAC_S.TXITC.TXSELITCPALEVEL', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXCALITC_TXCALENITCDAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXCALITC_TXCALENITCDAC, self).__init__(register,
            'TXCALENITCDAC', 'RAC_S.TXCALITC.TXCALENITCDAC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXCALITC_TXCALENITCPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXCALITC_TXCALENITCPA, self).__init__(register,
            'TXCALENITCPA', 'RAC_S.TXCALITC.TXCALENITCPA', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXCALITC_TXCALITCDACIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXCALITC_TXCALITCDACIB, self).__init__(register,
            'TXCALITCDACIB', 'RAC_S.TXCALITC.TXCALITCDACIB', 'read-write',
            u"",
            4, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXCALITC_TXCALITCPAIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXCALITC_TXCALITCPAIB, self).__init__(register,
            'TXCALITCPAIB', 'RAC_S.TXCALITC.TXCALITCPAIB', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXCALITC_TXCALITCCOREIB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXCALITC_TXCALITCCOREIB, self).__init__(register,
            'TXCALITCCOREIB', 'RAC_S.TXCALITC.TXCALITCCOREIB', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXCALITC_TXCALITCCORETC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXCALITC_TXCALITCCORETC, self).__init__(register,
            'TXCALITCCORETC', 'RAC_S.TXCALITC.TXCALITCCORETC', 'read-write',
            u"",
            22, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPACER_CLKMULTSPACER0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPACER_CLKMULTSPACER0, self).__init__(register,
            'CLKMULTSPACER0', 'RAC_S.SPACER.CLKMULTSPACER0', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPACER_AUXADCSPACER1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPACER_AUXADCSPACER1, self).__init__(register,
            'AUXADCSPACER1', 'RAC_S.SPACER.AUXADCSPACER1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPACER_RXSPACER2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPACER_RXSPACER2, self).__init__(register,
            'RXSPACER2', 'RAC_S.SPACER.RXSPACER2', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPKDCTRL_TXPKDCLKDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPKDCTRL_TXPKDCLKDIV, self).__init__(register,
            'TXPKDCLKDIV', 'RAC_S.TXPKDCTRL.TXPKDCLKDIV', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPKDCTRL_TXPKDCNTLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPKDCTRL_TXPKDCNTLEN, self).__init__(register,
            'TXPKDCNTLEN', 'RAC_S.TXPKDCTRL.TXPKDCNTLEN', 'read-write',
            u"",
            4, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPKDCMD_TXPKDSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPKDCMD_TXPKDSTART, self).__init__(register,
            'TXPKDSTART', 'RAC_S.TXPKDCMD.TXPKDSTART', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPKDCMD_TXPKDSTOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPKDCMD_TXPKDSTOP, self).__init__(register,
            'TXPKDSTOP', 'RAC_S.TXPKDCMD.TXPKDSTOP', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPKDCMD_TXPKDCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPKDCMD_TXPKDCLR, self).__init__(register,
            'TXPKDCLR', 'RAC_S.TXPKDCMD.TXPKDCLR', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPKDSTATUS_TXPKDDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPKDSTATUS_TXPKDDONE, self).__init__(register,
            'TXPKDDONE', 'RAC_S.TXPKDSTATUS.TXPKDDONE', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPKDSTATUS_TXPKDCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPKDSTATUS_TXPKDCNT, self).__init__(register,
            'TXPKDCNT', 'RAC_S.TXPKDSTATUS.TXPKDCNT', 'read-only',
            u"",
            4, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RADIOCLKCTRL_CLKSRWUHSPRESC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RADIOCLKCTRL_CLKSRWUHSPRESC, self).__init__(register,
            'CLKSRWUHSPRESC', 'RAC_S.RADIOCLKCTRL.CLKSRWUHSPRESC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RADIOCLKCTRL_CLKSRWHSPRESC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RADIOCLKCTRL_CLKSRWHSPRESC, self).__init__(register,
            'CLKSRWHSPRESC', 'RAC_S.RADIOCLKCTRL.CLKSRWHSPRESC', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RADIOCLKCTRL_CLKSRWLSPRESC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RADIOCLKCTRL_CLKSRWLSPRESC, self).__init__(register,
            'CLKSRWLSPRESC', 'RAC_S.RADIOCLKCTRL.CLKSRWLSPRESC', 'read-write',
            u"",
            8, 1)
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


class RM_Field_RAC_S_SOFTMCTRL_TXPATHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_TXPATHEN, self).__init__(register,
            'TXPATHEN', 'RAC_S.SOFTMCTRL.TXPATHEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_RXPATHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_RXPATHEN, self).__init__(register,
            'RXPATHEN', 'RAC_S.SOFTMCTRL.RXPATHEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_FRCPATHEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_FRCPATHEN, self).__init__(register,
            'FRCPATHEN', 'RAC_S.SOFTMCTRL.FRCPATHEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_CLKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_CLKEN, self).__init__(register,
            'CLKEN', 'RAC_S.SOFTMCTRL.CLKEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_CLKRUNNING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_CLKRUNNING, self).__init__(register,
            'CLKRUNNING', 'RAC_S.SOFTMCTRL.CLKRUNNING', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_TXMODSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_TXMODSEL, self).__init__(register,
            'TXMODSEL', 'RAC_S.SOFTMCTRL.TXMODSEL', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_ANTSELSRCSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_ANTSELSRCSEL, self).__init__(register,
            'ANTSELSRCSEL', 'RAC_S.SOFTMCTRL.ANTSELSRCSEL', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_FRCEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_FRCEN, self).__init__(register,
            'FRCEN', 'RAC_S.SOFTMCTRL.FRCEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_DISLEGACYPATH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_DISLEGACYPATH, self).__init__(register,
            'DISLEGACYPATH', 'RAC_S.SOFTMCTRL.DISLEGACYPATH', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_TXDACDISABLECLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_TXDACDISABLECLK, self).__init__(register,
            'TXDACDISABLECLK', 'RAC_S.SOFTMCTRL.TXDACDISABLECLK', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SOFTMCTRL_TXDACINVERTCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SOFTMCTRL_TXDACINVERTCLK, self).__init__(register,
            'TXDACINVERTCLK', 'RAC_S.SOFTMCTRL.TXDACINVERTCLK', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIF_STATECHANGESFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIF_STATECHANGESFMIF, self).__init__(register,
            'STATECHANGESFMIF', 'RAC_S.SFMIF.STATECHANGESFMIF', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIF_STIMCMPEVSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIF_STIMCMPEVSFMIF, self).__init__(register,
            'STIMCMPEVSFMIF', 'RAC_S.SFMIF.STIMCMPEVSFMIF', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIF_SEQLOCKUPSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIF_SEQLOCKUPSFMIF, self).__init__(register,
            'SEQLOCKUPSFMIF', 'RAC_S.SFMIF.SEQLOCKUPSFMIF', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIF_SEQRESETREQSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIF_SEQRESETREQSFMIF, self).__init__(register,
            'SEQRESETREQSFMIF', 'RAC_S.SFMIF.SEQRESETREQSFMIF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIF_SEQSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIF_SEQSFMIF, self).__init__(register,
            'SEQSFMIF', 'RAC_S.SFMIF.SEQSFMIF', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIEN_STATECHANGESFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIEN_STATECHANGESFMIEN, self).__init__(register,
            'STATECHANGESFMIEN', 'RAC_S.SFMIEN.STATECHANGESFMIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIEN_STIMCMPEVSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIEN_STIMCMPEVSFMIEN, self).__init__(register,
            'STIMCMPEVSFMIEN', 'RAC_S.SFMIEN.STIMCMPEVSFMIEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIEN_SEQLOCKUPSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIEN_SEQLOCKUPSFMIEN, self).__init__(register,
            'SEQLOCKUPSFMIEN', 'RAC_S.SFMIEN.SEQLOCKUPSFMIEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIEN_SEQRESETREQSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIEN_SEQRESETREQSFMIEN, self).__init__(register,
            'SEQRESETREQSFMIEN', 'RAC_S.SFMIEN.SEQRESETREQSFMIEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SFMIEN_SEQSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SFMIEN_SEQSFMIEN, self).__init__(register,
            'SEQSFMIEN', 'RAC_S.SFMIEN.SEQSFMIEN', 'read-write',
            u"",
            16, 8)
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


class RM_Field_RAC_S_RFLOCK0_TXIQENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_TXIQENABLE, self).__init__(register,
            'TXIQENABLE', 'RAC_S.RFLOCK0.TXIQENABLE', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_FFTCORPRO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_FFTCORPRO, self).__init__(register,
            'FFTCORPRO', 'RAC_S.RFLOCK0.FFTCORPRO', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_OFDMMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_OFDMMODE, self).__init__(register,
            'OFDMMODE', 'RAC_S.RFLOCK0.OFDMMODE', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACIFPGAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACIFPGAEN, self).__init__(register,
            'RACIFPGAEN', 'RAC_S.RFLOCK0.RACIFPGAEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACTXENFSKPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACTXENFSKPA, self).__init__(register,
            'RACTXENFSKPA', 'RAC_S.RFLOCK0.RACTXENFSKPA', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACTXENOFDMPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACTXENOFDMPA, self).__init__(register,
            'RACTXENOFDMPA', 'RAC_S.RFLOCK0.RACTXENOFDMPA', 'read-write',
            u"",
            18, 1)
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


class RM_Field_RAC_S_RFLOCK1_RACPASTRIPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASTRIPE, self).__init__(register,
            'RACPASTRIPE', 'RAC_S.RFLOCK1.RACPASTRIPE', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK1_RACPASLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK1_RACPASLICE, self).__init__(register,
            'RACPASLICE', 'RAC_S.RFLOCK1.RACPASLICE', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True



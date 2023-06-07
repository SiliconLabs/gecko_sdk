
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


class RM_Field_RAC_S_SEQIF_STATECHANGESEQIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATECHANGESEQIF, self).__init__(register,
            'STATECHANGESEQIF', 'RAC_S.SEQIF.STATECHANGESEQIF', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STIMCMPEVSEQIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STIMCMPEVSEQIF, self).__init__(register,
            'STIMCMPEVSEQIF', 'RAC_S.SEQIF.STIMCMPEVSEQIF', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_DEMODRXREQCLRSEQIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_DEMODRXREQCLRSEQIF, self).__init__(register,
            'DEMODRXREQCLRSEQIF', 'RAC_S.SEQIF.DEMODRXREQCLRSEQIF', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_PRSEVENTSEQIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_PRSEVENTSEQIF, self).__init__(register,
            'PRSEVENTSEQIF', 'RAC_S.SEQIF.PRSEVENTSEQIF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATEOFFIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATEOFFIF, self).__init__(register,
            'STATEOFFIF', 'RAC_S.SEQIF.STATEOFFIF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXWARMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXWARMIF, self).__init__(register,
            'STATERXWARMIF', 'RAC_S.SEQIF.STATERXWARMIF', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXSEARCHIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXSEARCHIF, self).__init__(register,
            'STATERXSEARCHIF', 'RAC_S.SEQIF.STATERXSEARCHIF', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXFRAMEIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXFRAMEIF, self).__init__(register,
            'STATERXFRAMEIF', 'RAC_S.SEQIF.STATERXFRAMEIF', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXPDIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXPDIF, self).__init__(register,
            'STATERXPDIF', 'RAC_S.SEQIF.STATERXPDIF', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERX2RXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERX2RXIF, self).__init__(register,
            'STATERX2RXIF', 'RAC_S.SEQIF.STATERX2RXIF', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERXOVERFLOWIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERXOVERFLOWIF, self).__init__(register,
            'STATERXOVERFLOWIF', 'RAC_S.SEQIF.STATERXOVERFLOWIF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATERX2TXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATERX2TXIF, self).__init__(register,
            'STATERX2TXIF', 'RAC_S.SEQIF.STATERX2TXIF', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETXWARMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETXWARMIF, self).__init__(register,
            'STATETXWARMIF', 'RAC_S.SEQIF.STATETXWARMIF', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETXIF, self).__init__(register,
            'STATETXIF', 'RAC_S.SEQIF.STATETXIF', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETXPDIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETXPDIF, self).__init__(register,
            'STATETXPDIF', 'RAC_S.SEQIF.STATETXPDIF', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETX2RXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETX2RXIF, self).__init__(register,
            'STATETX2RXIF', 'RAC_S.SEQIF.STATETX2RXIF', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATETX2TXIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATETX2TXIF, self).__init__(register,
            'STATETX2TXIF', 'RAC_S.SEQIF.STATETX2TXIF', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIF_STATESHUTDOWNIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIF_STATESHUTDOWNIF, self).__init__(register,
            'STATESHUTDOWNIF', 'RAC_S.SEQIF.STATESHUTDOWNIF', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATECHANGESEQIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATECHANGESEQIEN, self).__init__(register,
            'STATECHANGESEQIEN', 'RAC_S.SEQIEN.STATECHANGESEQIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STIMCMPEVSEQIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STIMCMPEVSEQIEN, self).__init__(register,
            'STIMCMPEVSEQIEN', 'RAC_S.SEQIEN.STIMCMPEVSEQIEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_DEMODRXREQCLRSEQIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_DEMODRXREQCLRSEQIEN, self).__init__(register,
            'DEMODRXREQCLRSEQIEN', 'RAC_S.SEQIEN.DEMODRXREQCLRSEQIEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_PRSEVENTSEQIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_PRSEVENTSEQIEN, self).__init__(register,
            'PRSEVENTSEQIEN', 'RAC_S.SEQIEN.PRSEVENTSEQIEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATEOFFIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATEOFFIEN, self).__init__(register,
            'STATEOFFIEN', 'RAC_S.SEQIEN.STATEOFFIEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXWARMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXWARMIEN, self).__init__(register,
            'STATERXWARMIEN', 'RAC_S.SEQIEN.STATERXWARMIEN', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXSEARCHIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXSEARCHIEN, self).__init__(register,
            'STATERXSEARCHIEN', 'RAC_S.SEQIEN.STATERXSEARCHIEN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXFRAMEIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXFRAMEIEN, self).__init__(register,
            'STATERXFRAMEIEN', 'RAC_S.SEQIEN.STATERXFRAMEIEN', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXPDIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXPDIEN, self).__init__(register,
            'STATERXPDIEN', 'RAC_S.SEQIEN.STATERXPDIEN', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERX2RXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERX2RXIEN, self).__init__(register,
            'STATERX2RXIEN', 'RAC_S.SEQIEN.STATERX2RXIEN', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERXOVERFLOWIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERXOVERFLOWIEN, self).__init__(register,
            'STATERXOVERFLOWIEN', 'RAC_S.SEQIEN.STATERXOVERFLOWIEN', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATERX2TXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATERX2TXIEN, self).__init__(register,
            'STATERX2TXIEN', 'RAC_S.SEQIEN.STATERX2TXIEN', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETXWARMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETXWARMIEN, self).__init__(register,
            'STATETXWARMIEN', 'RAC_S.SEQIEN.STATETXWARMIEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETXIEN, self).__init__(register,
            'STATETXIEN', 'RAC_S.SEQIEN.STATETXIEN', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETXPDIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETXPDIEN, self).__init__(register,
            'STATETXPDIEN', 'RAC_S.SEQIEN.STATETXPDIEN', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETX2RXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETX2RXIEN, self).__init__(register,
            'STATETX2RXIEN', 'RAC_S.SEQIEN.STATETX2RXIEN', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATETX2TXIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATETX2TXIEN, self).__init__(register,
            'STATETX2TXIEN', 'RAC_S.SEQIEN.STATETX2TXIEN', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SEQIEN_STATESHUTDOWNIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SEQIEN_STATESHUTDOWNIEN, self).__init__(register,
            'STATESHUTDOWNIEN', 'RAC_S.SEQIEN.STATESHUTDOWNIEN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_STATUS1_TXMASK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_STATUS1_TXMASK, self).__init__(register,
            'TXMASK', 'RAC_S.STATUS1.TXMASK', 'read-only',
            u"",
            0, 8)
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


class RM_Field_RAC_S_VCOCTRL_SYVCOVCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VCOCTRL_SYVCOVCAP, self).__init__(register,
            'SYVCOVCAP', 'RAC_S.VCOCTRL.SYVCOVCAP', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CHPCTRL_CHPOUTPUTTRISTATEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CHPCTRL_CHPOUTPUTTRISTATEMODE, self).__init__(register,
            'CHPOUTPUTTRISTATEMODE', 'RAC_S.CHPCTRL.CHPOUTPUTTRISTATEMODE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VCOTUNE_SYVCOTUNING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VCOTUNE_SYVCOTUNING, self).__init__(register,
            'SYVCOTUNING', 'RAC_S.VCOTUNE.SYVCOTUNING', 'read-write',
            u"",
            0, 11)
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


class RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVLNAMIXEN0, self).__init__(register,
            'INTDIVLNAMIXEN0', 'RAC_S.ANTDIV.INTDIVLNAMIXEN0', 'read-write',
            u"",
            0, 1)
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


class RM_Field_RAC_S_ANTDIV_INTDIVSYLODIVRLO02G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVSYLODIVRLO02G4EN, self).__init__(register,
            'INTDIVSYLODIVRLO02G4EN', 'RAC_S.ANTDIV.INTDIVSYLODIVRLO02G4EN', 'read-write',
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


class RM_Field_RAC_S_ANTDIV_INTDIVSYLODIVRLO12G4EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_ANTDIV_INTDIVSYLODIVRLO12G4EN, self).__init__(register,
            'INTDIVSYLODIVRLO12G4EN', 'RAC_S.ANTDIV.INTDIVSYLODIVRLO12G4EN', 'read-write',
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


class RM_Field_RAC_S_AUXADCTRIM_ADCTSENSESELCURR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_ADCTSENSESELCURR, self).__init__(register,
            'ADCTSENSESELCURR', 'RAC_S.AUXADCTRIM.ADCTSENSESELCURR', 'read-write',
            u"",
            1, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_ADCTRIMCURRTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_ADCTRIMCURRTSENSE, self).__init__(register,
            'ADCTRIMCURRTSENSE', 'RAC_S.AUXADCTRIM.ADCTRIMCURRTSENSE', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_ADCTSENSESELVBE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_ADCTSENSESELVBE, self).__init__(register,
            'ADCTSENSESELVBE', 'RAC_S.AUXADCTRIM.ADCTSENSESELVBE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_ADCTSENSETRIMVBE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_ADCTSENSETRIMVBE2, self).__init__(register,
            'ADCTSENSETRIMVBE2', 'RAC_S.AUXADCTRIM.ADCTSENSETRIMVBE2', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCTRIM_ADCTUNERC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCTRIM_ADCTUNERC, self).__init__(register,
            'ADCTUNERC', 'RAC_S.AUXADCTRIM.ADCTUNERC', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENADC, self).__init__(register,
            'ADCENADC', 'RAC_S.AUXADCEN.ADCENADC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENCLK, self).__init__(register,
            'ADCENCLK', 'RAC_S.AUXADCEN.ADCENCLK', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENAUXADC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENAUXADC, self).__init__(register,
            'ADCENAUXADC', 'RAC_S.AUXADCEN.ADCENAUXADC', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENINPUTBUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENINPUTBUFFER, self).__init__(register,
            'ADCENINPUTBUFFER', 'RAC_S.AUXADCEN.ADCENINPUTBUFFER', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENLDOSERIES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENLDOSERIES, self).__init__(register,
            'ADCENLDOSERIES', 'RAC_S.AUXADCEN.ADCENLDOSERIES', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENNEGRES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENNEGRES, self).__init__(register,
            'ADCENNEGRES', 'RAC_S.AUXADCEN.ADCENNEGRES', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENPMON(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENPMON, self).__init__(register,
            'ADCENPMON', 'RAC_S.AUXADCEN.ADCENPMON', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENRESONDIAGA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENRESONDIAGA, self).__init__(register,
            'ADCENRESONDIAGA', 'RAC_S.AUXADCEN.ADCENRESONDIAGA', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENTSENSECAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENTSENSECAL, self).__init__(register,
            'ADCENTSENSECAL', 'RAC_S.AUXADCEN.ADCENTSENSECAL', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCINPUTBUFFERBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCINPUTBUFFERBYPASS, self).__init__(register,
            'ADCINPUTBUFFERBYPASS', 'RAC_S.AUXADCEN.ADCINPUTBUFFERBYPASS', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCEN_ADCENLDOBIASSERIES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCEN_ADCENLDOBIASSERIES, self).__init__(register,
            'ADCENLDOBIASSERIES', 'RAC_S.AUXADCEN.ADCENLDOBIASSERIES', 'read-write',
            u"",
            10, 1)
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


class RM_Field_RAC_S_AUXADCCTRL1_ADCINPUTRESSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_ADCINPUTRESSEL, self).__init__(register,
            'ADCINPUTRESSEL', 'RAC_S.AUXADCCTRL1.ADCINPUTRESSEL', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_ADCINPUTSCALE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_ADCINPUTSCALE, self).__init__(register,
            'ADCINPUTSCALE', 'RAC_S.AUXADCCTRL1.ADCINPUTSCALE', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_ADCINVERTCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_ADCINVERTCLK, self).__init__(register,
            'ADCINVERTCLK', 'RAC_S.AUXADCCTRL1.ADCINVERTCLK', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_ADCLDOSHUNTCURLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_ADCLDOSHUNTCURLVL2, self).__init__(register,
            'ADCLDOSHUNTCURLVL2', 'RAC_S.AUXADCCTRL1.ADCLDOSHUNTCURLVL2', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_ADCTUNERCCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_ADCTUNERCCALMODE, self).__init__(register,
            'ADCTUNERCCALMODE', 'RAC_S.AUXADCCTRL1.ADCTUNERCCALMODE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL1_ADCZEROOPT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL1_ADCZEROOPT, self).__init__(register,
            'ADCZEROOPT', 'RAC_S.AUXADCCTRL1.ADCZEROOPT', 'read-write',
            u"",
            11, 1)
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


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTILOADREG2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTILOADREG2, self).__init__(register,
            'CLKMULTILOADREG2', 'RAC_S.CLKMULTEN0.CLKMULTILOADREG2', 'read-write',
            u"",
            11, 3)
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


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTFREQCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTFREQCAL, self).__init__(register,
            'CLKMULTFREQCAL', 'RAC_S.CLKMULTEN0.CLKMULTFREQCAL', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1FORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1FORCEDSTARTUP, self).__init__(register,
            'CLKMULTENREG1FORCEDSTARTUP', 'RAC_S.CLKMULTEN0.CLKMULTENREG1FORCEDSTARTUP', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1IBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1IBIAS, self).__init__(register,
            'CLKMULTENREG1IBIAS', 'RAC_S.CLKMULTEN0.CLKMULTENREG1IBIAS', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1REPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1REPLICA, self).__init__(register,
            'CLKMULTENREG1REPLICA', 'RAC_S.CLKMULTEN0.CLKMULTENREG1REPLICA', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1STBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENREG1STBLOAD, self).__init__(register,
            'CLKMULTENREG1STBLOAD', 'RAC_S.CLKMULTEN0.CLKMULTENREG1STBLOAD', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN0_CLKMULTENDRVTEST, self).__init__(register,
            'CLKMULTENDRVTEST', 'RAC_S.CLKMULTEN0.CLKMULTENDRVTEST', 'read-write',
            u"",
            28, 1)
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


class RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_CLKMULTEN1_CLKMULTDIVN, self).__init__(register,
            'CLKMULTDIVN', 'RAC_S.CLKMULTEN1.CLKMULTDIVN', 'read-write',
            u"",
            17, 7)
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


class RM_Field_RAC_S_IFADCDBG_ADCENSIDETONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_ADCENSIDETONE, self).__init__(register,
            'ADCENSIDETONE', 'RAC_S.IFADCDBG.ADCENSIDETONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCDBG_ADCENTSENSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_ADCENTSENSE, self).__init__(register,
            'ADCENTSENSE', 'RAC_S.IFADCDBG.ADCENTSENSE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCDBG_ADCINPUTSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCDBG_ADCINPUTSELECT, self).__init__(register,
            'ADCINPUTSELECT', 'RAC_S.IFADCDBG.ADCINPUTSELECT', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM0_ADCCLKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM0_ADCCLKSEL, self).__init__(register,
            'ADCCLKSEL', 'RAC_S.IFADCTRIM0.ADCCLKSEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_ADCREFBUFCURLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_ADCREFBUFCURLVL, self).__init__(register,
            'ADCREFBUFCURLVL', 'RAC_S.IFADCTRIM1.ADCREFBUFCURLVL', 'read-write',
            u"",
            14, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCTRIM1_ADCSIDETONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCTRIM1_ADCSIDETONEAMP, self).__init__(register,
            'ADCSIDETONEAMP', 'RAC_S.IFADCTRIM1.ADCSIDETONEAMP', 'read-write',
            u"",
            17, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCCAL_ADCENRCCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCCAL_ADCENRCCAL, self).__init__(register,
            'ADCENRCCAL', 'RAC_S.IFADCCAL.ADCENRCCAL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_IFADCSTATUS_ADCRCCALOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_IFADCSTATUS_ADCRCCALOUT, self).__init__(register,
            'ADCRCCALOUT', 'RAC_S.IFADCSTATUS.ADCRCCALOUT', 'read-only',
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
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXIBIAS1TRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXIBIAS1TRIM, self).__init__(register,
            'LNAMIXIBIAS1TRIM', 'RAC_S.LNAMIXTRIM1.LNAMIXIBIAS1TRIM', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXNCAS1ADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM1_LNAMIXNCAS1ADJ, self).__init__(register,
            'LNAMIXNCAS1ADJ', 'RAC_S.LNAMIXTRIM1.LNAMIXNCAS1ADJ', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXHIGHCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXHIGHCUR, self).__init__(register,
            'LNAMIXHIGHCUR', 'RAC_S.LNAMIXTRIM2.LNAMIXHIGHCUR', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXENREGVHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXENREGVHIGH, self).__init__(register,
            'LNAMIXENREGVHIGH', 'RAC_S.LNAMIXTRIM2.LNAMIXENREGVHIGH', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXENSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXENSTBLOAD, self).__init__(register,
            'LNAMIXENSTBLOAD', 'RAC_S.LNAMIXTRIM2.LNAMIXENSTBLOAD', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXREGLOWPWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM2_LNAMIXREGLOWPWR, self).__init__(register,
            'LNAMIXREGLOWPWR', 'RAC_S.LNAMIXTRIM2.LNAMIXREGLOWPWR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXRFATT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXRFATT1, self).__init__(register,
            'LNAMIXRFATT1', 'RAC_S.LNAMIXTRIM3.LNAMIXRFATT1', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXRFPKDCALCMLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXRFPKDCALCMLO, self).__init__(register,
            'LNAMIXRFPKDCALCMLO', 'RAC_S.LNAMIXTRIM3.LNAMIXRFPKDCALCMLO', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXRFPKDCALCMHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM3_LNAMIXRFPKDCALCMHI, self).__init__(register,
            'LNAMIXRFPKDCALCMHI', 'RAC_S.LNAMIXTRIM3.LNAMIXRFPKDCALCMHI', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDBWSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXTRIM4_LNAMIXRFPKDBWSEL, self).__init__(register,
            'LNAMIXRFPKDBWSEL', 'RAC_S.LNAMIXTRIM4.LNAMIXRFPKDBWSEL', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXCALVMODE, self).__init__(register,
            'LNAMIXCALVMODE', 'RAC_S.LNAMIXCAL.LNAMIXCALVMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL1AMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXCAL_LNAMIXIRCAL1AMP, self).__init__(register,
            'LNAMIXIRCAL1AMP', 'RAC_S.LNAMIXCAL.LNAMIXIRCAL1AMP', 'read-write',
            u"",
            5, 3)
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


class RM_Field_RAC_S_PRECTRL_PREREGENSTBILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGENSTBILOAD, self).__init__(register,
            'PREREGENSTBILOAD', 'RAC_S.PRECTRL.PREREGENSTBILOAD', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGENINTBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGENINTBIAS, self).__init__(register,
            'PREREGENINTBIAS', 'RAC_S.PRECTRL.PREREGENINTBIAS', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGENVTRMINI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGENVTRMINI, self).__init__(register,
            'PREREGENVTRMINI', 'RAC_S.PRECTRL.PREREGENVTRMINI', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGENVTRMINISTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGENVTRMINISTARTUP, self).__init__(register,
            'PREREGENVTRMINISTARTUP', 'RAC_S.PRECTRL.PREREGENVTRMINISTARTUP', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PRECTRL_PREREGSTARTUPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PRECTRL_PREREGSTARTUPFORCE, self).__init__(register,
            'PREREGSTARTUPFORCE', 'RAC_S.PRECTRL.PREREGSTARTUPFORCE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_TXPAAMPCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_TXPAAMPCTRL, self).__init__(register,
            'TXPAAMPCTRL', 'RAC_S.PATRIM0.TXPAAMPCTRL', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PATRIM0_ENAMPCTRLREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PATRIM0_ENAMPCTRLREG, self).__init__(register,
            'ENAMPCTRLREG', 'RAC_S.PATRIM0.ENAMPCTRLREG', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TXPOWER_TX0DBMSELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TXPOWER_TX0DBMSELSLICE, self).__init__(register,
            'TX0DBMSELSLICE', 'RAC_S.TXPOWER.TX0DBMSELSLICE', 'read-write',
            u"",
            8, 2)
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
            1, 1)
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
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXTRSW1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXTRSW1, self).__init__(register,
            'LNAMIXTRSW1', 'RAC_S.RFPATHEN1.LNAMIXTRSW1', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFPATHEN1_LNAMIXREGLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFPATHEN1_LNAMIXREGLOWCUR, self).__init__(register,
            'LNAMIXREGLOWCUR', 'RAC_S.RFPATHEN1.LNAMIXREGLOWCUR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_ADCCAPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_ADCCAPRESET, self).__init__(register,
            'ADCCAPRESET', 'RAC_S.RX.ADCCAPRESET', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_ADCENLDOSHUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_ADCENLDOSHUNT, self).__init__(register,
            'ADCENLDOSHUNT', 'RAC_S.RX.ADCENLDOSHUNT', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXCALEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXCALEN, self).__init__(register,
            'LNAMIXCALEN', 'RAC_S.RX.LNAMIXCALEN', 'read-write',
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


class RM_Field_RAC_S_RX_LNAMIXENLOTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXENLOTHRESH, self).__init__(register,
            'LNAMIXENLOTHRESH', 'RAC_S.RX.LNAMIXENLOTHRESH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXMXRLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXMXRLOSEL, self).__init__(register,
            'LNAMIXMXRLOSEL', 'RAC_S.RX.LNAMIXMXRLOSEL', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXCURCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXCURCTRL, self).__init__(register,
            'LNAMIXCURCTRL', 'RAC_S.RX.LNAMIXCURCTRL', 'read-write',
            u"",
            7, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXLNA1SLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXLNA1SLICE, self).__init__(register,
            'LNAMIXLNA1SLICE', 'RAC_S.RX.LNAMIXLNA1SLICE', 'read-write',
            u"",
            13, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXDOUBLECUR1EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXDOUBLECUR1EN, self).__init__(register,
            'LNAMIXDOUBLECUR1EN', 'RAC_S.RX.LNAMIXDOUBLECUR1EN', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXLOWCUR, self).__init__(register,
            'LNAMIXLOWCUR', 'RAC_S.RX.LNAMIXLOWCUR', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXRFPKDTHRESHSELLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXRFPKDTHRESHSELLO, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELLO', 'RAC_S.RX.LNAMIXRFPKDTHRESHSELLO', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RX_LNAMIXRFPKDTHRESHSELHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RX_LNAMIXRFPKDTHRESHSELHI, self).__init__(register,
            'LNAMIXRFPKDTHRESHSELHI', 'RAC_S.RX.LNAMIXRFPKDTHRESHSELHI', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_SYCHPBIASTRIMBUFTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_SYCHPBIASTRIMBUFTX, self).__init__(register,
            'SYCHPBIASTRIMBUFTX', 'RAC_S.TX.SYCHPBIASTRIMBUFTX', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_SYPFDCHPLPENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_SYPFDCHPLPENTX, self).__init__(register,
            'SYPFDCHPLPENTX', 'RAC_S.TX.SYPFDCHPLPENTX', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX_SYPFDFPWENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX_SYPFDFPWENTX, self).__init__(register,
            'SYPFDFPWENTX', 'RAC_S.TX.SYPFDFPWENTX', 'read-write',
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


class RM_Field_RAC_S_SYDEBUG_SYPFDFPWENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYPFDFPWENRX, self).__init__(register,
            'SYPFDFPWENRX', 'RAC_S.SYDEBUG.SYPFDFPWENRX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYPFDCHPLPENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYPFDCHPLPENRX, self).__init__(register,
            'SYPFDCHPLPENRX', 'RAC_S.SYDEBUG.SYPFDCHPLPENRX', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYCHPBIASTRIMBUFRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYCHPBIASTRIMBUFRX, self).__init__(register,
            'SYCHPBIASTRIMBUFRX', 'RAC_S.SYDEBUG.SYCHPBIASTRIMBUFRX', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYENMMDREGBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYENMMDREGBIAS, self).__init__(register,
            'SYENMMDREGBIAS', 'RAC_S.SYDEBUG.SYENMMDREGBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYENMMDREGFORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYENMMDREGFORCEDSTARTUP, self).__init__(register,
            'SYENMMDREGFORCEDSTARTUP', 'RAC_S.SYDEBUG.SYENMMDREGFORCEDSTARTUP', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYENMMDREGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYENMMDREGREPLICA, self).__init__(register,
            'SYENMMDREGREPLICA', 'RAC_S.SYDEBUG.SYENMMDREGREPLICA', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDEBUG_SYENMMDSYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDEBUG_SYENMMDSYNC, self).__init__(register,
            'SYENMMDSYNC', 'RAC_S.SYDEBUG.SYENMMDSYNC', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYVCOTRIMIPTAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYVCOTRIMIPTAT, self).__init__(register,
            'SYVCOTRIMIPTAT', 'RAC_S.SYTRIM0.SYVCOTRIMIPTAT', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYLODIVREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYLODIVREGTRIMVREG, self).__init__(register,
            'SYLODIVREGTRIMVREG', 'RAC_S.SYTRIM0.SYLODIVREGTRIMVREG', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYVCOTRIMPKDAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYVCOTRIMPKDAMP, self).__init__(register,
            'SYVCOTRIMPKDAMP', 'RAC_S.SYTRIM0.SYVCOTRIMPKDAMP', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYVCOREGLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYVCOREGLOWCUR, self).__init__(register,
            'SYVCOREGLOWCUR', 'RAC_S.SYTRIM0.SYVCOREGLOWCUR', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYVCOTRIMR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYVCOTRIMR, self).__init__(register,
            'SYVCOTRIMR', 'RAC_S.SYTRIM0.SYVCOTRIMR', 'read-write',
            u"",
            12, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYVCOTRIMREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYVCOTRIMREF, self).__init__(register,
            'SYVCOTRIMREF', 'RAC_S.SYTRIM0.SYVCOTRIMREF', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYTDCREGTRIMBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYTDCREGTRIMBW, self).__init__(register,
            'SYTDCREGTRIMBW', 'RAC_S.SYTRIM0.SYTDCREGTRIMBW', 'read-write',
            u"",
            20, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYVCOHCAPRETIMESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYVCOHCAPRETIMESEL, self).__init__(register,
            'SYVCOHCAPRETIMESEL', 'RAC_S.SYTRIM0.SYVCOHCAPRETIMESEL', 'read-write',
            u"",
            22, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYVCOREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYVCOREGTRIMVREG, self).__init__(register,
            'SYVCOREGTRIMVREG', 'RAC_S.SYTRIM0.SYVCOREGTRIMVREG', 'read-write',
            u"",
            24, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM0_SYVCOTRIMIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM0_SYVCOTRIMIBIAS, self).__init__(register,
            'SYVCOTRIMIBIAS', 'RAC_S.SYTRIM0.SYVCOTRIMIBIAS', 'read-write',
            u"",
            27, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCNT, self).__init__(register,
            'SYTDCTRIMDLYCNT', 'RAC_S.SYTRIM1.SYTDCTRIMDLYCNT', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYLOAD, self).__init__(register,
            'SYTDCTRIMDLYLOAD', 'RAC_S.SYTRIM1.SYTDCTRIMDLYLOAD', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYSTOPMETA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYSTOPMETA, self).__init__(register,
            'SYTDCTRIMDLYSTOPMETA', 'RAC_S.SYTRIM1.SYTDCTRIMDLYSTOPMETA', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYDTCREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYDTCREGTRIMVREF, self).__init__(register,
            'SYDTCREGTRIMVREF', 'RAC_S.SYTRIM1.SYDTCREGTRIMVREF', 'read-write',
            u"",
            6, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCK1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCTRIMDLYCK1, self).__init__(register,
            'SYTDCTRIMDLYCK1', 'RAC_S.SYTRIM1.SYTDCTRIMDLYCK1', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYDTCRDACTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYDTCRDACTRIM, self).__init__(register,
            'SYDTCRDACTRIM', 'RAC_S.SYTRIM1.SYDTCRDACTRIM', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMVREG, self).__init__(register,
            'SYTDCREGTRIMVREG', 'RAC_S.SYTRIM1.SYTDCREGTRIMVREG', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMTEMPCOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMTEMPCOP, self).__init__(register,
            'SYTDCREGTRIMTEMPCOP', 'RAC_S.SYTRIM1.SYTDCREGTRIMTEMPCOP', 'read-write',
            u"",
            22, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM1_SYTDCREGTRIMVREF, self).__init__(register,
            'SYTDCREGTRIMVREF', 'RAC_S.SYTRIM1.SYTDCREGTRIMVREF', 'read-write',
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


class RM_Field_RAC_S_SYEN_SYENVCOREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOREG, self).__init__(register,
            'SYENVCOREG', 'RAC_S.SYEN.SYENVCOREG', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENDLFAQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENDLFAQNC, self).__init__(register,
            'SYENDLFAQNC', 'RAC_S.SYEN.SYENDLFAQNC', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENMMDREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENMMDREGSTBLOAD, self).__init__(register,
            'SYENMMDREGSTBLOAD', 'RAC_S.SYEN.SYENMMDREGSTBLOAD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENTDCAQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENTDCAQNC, self).__init__(register,
            'SYENTDCAQNC', 'RAC_S.SYEN.SYENTDCAQNC', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENTDCREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENTDCREG, self).__init__(register,
            'SYENTDCREG', 'RAC_S.SYEN.SYENTDCREG', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENTDCREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENTDCREGSTBLOAD, self).__init__(register,
            'SYENTDCREGSTBLOAD', 'RAC_S.SYEN.SYENTDCREGSTBLOAD', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOIBIAS, self).__init__(register,
            'SYENVCOIBIAS', 'RAC_S.SYEN.SYENVCOIBIAS', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOPKD, self).__init__(register,
            'SYENVCOPKD', 'RAC_S.SYEN.SYENVCOPKD', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOBIAS, self).__init__(register,
            'SYENVCOBIAS', 'RAC_S.SYEN.SYENVCOBIAS', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENTDC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENTDC, self).__init__(register,
            'SYENTDC', 'RAC_S.SYEN.SYENTDC', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYEN_SYENVCOHCAPRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYEN_SYENVCOHCAPRETIME, self).__init__(register,
            'SYENVCOHCAPRETIME', 'RAC_S.SYEN.SYENVCOHCAPRETIME', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVADCCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVADCCLK, self).__init__(register,
            'SYENLODIVADCCLK', 'RAC_S.SYLOEN.SYENLODIVADCCLK', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVFCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVFCAL, self).__init__(register,
            'SYENLODIVFCAL', 'RAC_S.SYLOEN.SYENLODIVFCAL', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVHADMDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVHADMDIV, self).__init__(register,
            'SYENLODIVHADMDIV', 'RAC_S.SYLOEN.SYENLODIVHADMDIV', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVHADMLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVHADMLO, self).__init__(register,
            'SYENLODIVHADMLO', 'RAC_S.SYLOEN.SYENLODIVHADMLO', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVHADMRXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVHADMRXLO, self).__init__(register,
            'SYENLODIVHADMRXLO', 'RAC_S.SYLOEN.SYENLODIVHADMRXLO', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVHADMTXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVHADMTXLO, self).__init__(register,
            'SYENLODIVHADMTXLO', 'RAC_S.SYLOEN.SYENLODIVHADMTXLO', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVREGREPLICA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVREGREPLICA, self).__init__(register,
            'SYENLODIVREGREPLICA', 'RAC_S.SYLOEN.SYENLODIVREGREPLICA', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVREGFORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVREGFORCEDSTARTUP, self).__init__(register,
            'SYENLODIVREGFORCEDSTARTUP', 'RAC_S.SYLOEN.SYENLODIVREGFORCEDSTARTUP', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVREGBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVREGBIAS, self).__init__(register,
            'SYENLODIVREGBIAS', 'RAC_S.SYLOEN.SYENLODIVREGBIAS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVREG, self).__init__(register,
            'SYENLODIVREG', 'RAC_S.SYLOEN.SYENLODIVREG', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVLPRXLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVLPRXLO, self).__init__(register,
            'SYENLODIVLPRXLO', 'RAC_S.SYLOEN.SYENLODIVLPRXLO', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVLPRXDIV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVLPRXDIV, self).__init__(register,
            'SYENLODIVLPRXDIV', 'RAC_S.SYLOEN.SYENLODIVLPRXDIV', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVIQCLKBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVIQCLKBIAS, self).__init__(register,
            'SYENLODIVIQCLKBIAS', 'RAC_S.SYLOEN.SYENLODIVIQCLKBIAS', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVDIVSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVDIVSE, self).__init__(register,
            'SYENLODIVDIVSE', 'RAC_S.SYLOEN.SYENLODIVDIVSE', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVDSMDACCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVDSMDACCLK, self).__init__(register,
            'SYENLODIVDSMDACCLK', 'RAC_S.SYLOEN.SYENLODIVDSMDACCLK', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVFPSRC2G4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVFPSRC2G4, self).__init__(register,
            'SYENLODIVFPSRC2G4', 'RAC_S.SYLOEN.SYENLODIVFPSRC2G4', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVREGSTBLOAD, self).__init__(register,
            'SYENLODIVREGSTBLOAD', 'RAC_S.SYLOEN.SYENLODIVREGSTBLOAD', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVSECLKBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVSECLKBIAS, self).__init__(register,
            'SYENLODIVSECLKBIAS', 'RAC_S.SYLOEN.SYENLODIVSECLKBIAS', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVSMUXCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVSMUXCLK, self).__init__(register,
            'SYENLODIVSMUXCLK', 'RAC_S.SYLOEN.SYENLODIVSMUXCLK', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENLODIVTXRF0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENLODIVTXRF0DBM, self).__init__(register,
            'SYENLODIVTXRF0DBM', 'RAC_S.SYLOEN.SYENLODIVTXRF0DBM', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENMMDREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENMMDREG, self).__init__(register,
            'SYENMMDREG', 'RAC_S.SYLOEN.SYENMMDREG', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENMMDCLKINJXO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENMMDCLKINJXO, self).__init__(register,
            'SYENMMDCLKINJXO', 'RAC_S.SYLOEN.SYENMMDCLKINJXO', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENDTCCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENDTCCORE, self).__init__(register,
            'SYENDTCCORE', 'RAC_S.SYLOEN.SYENDTCCORE', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENDTCREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENDTCREG, self).__init__(register,
            'SYENDTCREG', 'RAC_S.SYLOEN.SYENDTCREG', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYLOEN_SYENMMDAQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYLOEN_SYENMMDAQNC, self).__init__(register,
            'SYENMMDAQNC', 'RAC_S.SYLOEN.SYENMMDAQNC', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYMMDCTRL_SYMMDPHISEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYMMDCTRL_SYMMDPHISEL, self).__init__(register,
            'SYMMDPHISEL', 'RAC_S.SYMMDCTRL.SYMMDPHISEL', 'read-write',
            u"",
            1, 1)
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
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGCORE, self).__init__(register,
            'MIXDACTRIMSPAREVREGCORE', 'RAC_S.SPARE.MIXDACTRIMSPAREVREGCORE', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE02(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE02, self).__init__(register,
            'MIXDACTRIMSPARE02', 'RAC_S.SPARE.MIXDACTRIMSPARE02', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE01(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACTRIMSPARE01, self).__init__(register,
            'MIXDACTRIMSPARE01', 'RAC_S.SPARE.MIXDACTRIMSPARE01', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACENSPARE02(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACENSPARE02, self).__init__(register,
            'MIXDACENSPARE02', 'RAC_S.SPARE.MIXDACENSPARE02', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGDIG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACTRIMSPAREVREGDIG, self).__init__(register,
            'MIXDACTRIMSPAREVREGDIG', 'RAC_S.SPARE.MIXDACTRIMSPAREVREGDIG', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_MIXDACENSPARE01(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_MIXDACENSPARE01, self).__init__(register,
            'MIXDACENSPARE01', 'RAC_S.SPARE.MIXDACENSPARE01', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_SYLODIVSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SYLODIVSPARES, self).__init__(register,
            'SYLODIVSPARES', 'RAC_S.SPARE.SYLODIVSPARES', 'read-write',
            u"",
            18, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_SYMMDSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SYMMDSPARES, self).__init__(register,
            'SYMMDSPARES', 'RAC_S.SPARE.SYMMDSPARES', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE_SYVCOSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE_SYVCOSPARES, self).__init__(register,
            'SYVCOSPARES', 'RAC_S.SPARE.SYVCOSPARES', 'read-write',
            u"",
            26, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_TXPAPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_TXPAPOWER, self).__init__(register,
            'TXPAPOWER', 'RAC_S.PACTRL.TXPAPOWER', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_PACTRL_TXPASELSLICE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_PACTRL_TXPASELSLICE, self).__init__(register,
            'TXPASELSLICE', 'RAC_S.PACTRL.TXPASELSLICE', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFKI_SYDLFLPFBWKI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFKI_SYDLFLPFBWKI, self).__init__(register,
            'SYDLFLPFBWKI', 'RAC_S.SYDLFKI.SYDLFLPFBWKI', 'read-write',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFKF_SYDLFLPFBWKF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFKF_SYDLFLPFBWKF, self).__init__(register,
            'SYDLFLPFBWKF', 'RAC_S.SYDLFKF.SYDLFLPFBWKF', 'read-write',
            u"",
            0, 22)
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


class RM_Field_RAC_S_SYTRIM2_SYTDCTRIMDLYSTOPRING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYTDCTRIMDLYSTOPRING, self).__init__(register,
            'SYTDCTRIMDLYSTOPRING', 'RAC_S.SYTRIM2.SYTDCTRIMDLYSTOPRING', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYMMDREGTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYMMDREGTRIMVREG, self).__init__(register,
            'SYMMDREGTRIMVREG', 'RAC_S.SYTRIM2.SYMMDREGTRIMVREG', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYDTCCOFFSETTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYDTCCOFFSETTRIM, self).__init__(register,
            'SYDTCCOFFSETTRIM', 'RAC_S.SYTRIM2.SYDTCCOFFSETTRIM', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYDTCREGTRIMVTTRACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYDTCREGTRIMVTTRACK, self).__init__(register,
            'SYDTCREGTRIMVTTRACK', 'RAC_S.SYTRIM2.SYDTCREGTRIMVTTRACK', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYTDCTRIMPERLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYTDCTRIMPERLOAD, self).__init__(register,
            'SYTDCTRIMPERLOAD', 'RAC_S.SYTRIM2.SYTDCTRIMPERLOAD', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYTRIM2_SYVCOREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYTRIM2_SYVCOREGTRIMVREF, self).__init__(register,
            'SYVCOREGTRIMVREF', 'RAC_S.SYTRIM2.SYVCOREGTRIMVREF', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL1_SYDLFVCTRLLOTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL1_SYDLFVCTRLLOTH, self).__init__(register,
            'SYDLFVCTRLLOTH', 'RAC_S.SYDLFCTRL1.SYDLFVCTRLLOTH', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL1_SYDLFTDCA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL1_SYDLFTDCA2, self).__init__(register,
            'SYDLFTDCA2', 'RAC_S.SYDLFCTRL1.SYDLFTDCA2', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLFCTRL1_SYDLFVCTRLCMPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLFCTRL1_SYDLFVCTRLCMPRESET, self).__init__(register,
            'SYDLFVCTRLCMPRESET', 'RAC_S.SYDLFCTRL1.SYDLFVCTRLCMPRESET', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFSTATE, self).__init__(register,
            'SYDLFSTATE', 'RAC_S.SYSTATUS.SYDLFSTATE', 'read-only',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFLMSP0M(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFLMSP0M, self).__init__(register,
            'SYDLFLMSP0M', 'RAC_S.SYSTATUS.SYDLFLMSP0M', 'read-only',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLHI, self).__init__(register,
            'SYDLFVCTRLHI', 'RAC_S.SYSTATUS.SYDLFVCTRLHI', 'read-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLLO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFVCTRLLO, self).__init__(register,
            'SYDLFVCTRLLO', 'RAC_S.SYSTATUS.SYDLFVCTRLLO', 'read-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFPFDLOCKSAMPLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFPFDLOCKSAMPLE, self).__init__(register,
            'SYDLFPFDLOCKSAMPLE', 'RAC_S.SYSTATUS.SYDLFPFDLOCKSAMPLE', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYSTATUS_SYDLFPFDREFLEAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYSTATUS_SYDLFPFDREFLEAD, self).__init__(register,
            'SYDLFPFDREFLEAD', 'RAC_S.SYSTATUS.SYDLFPFDREFLEAD', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYDTCREGILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYDTCREGILOAD, self).__init__(register,
            'SYDTCREGILOAD', 'RAC_S.SYCTRL2.SYDTCREGILOAD', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYDTCREGVTTRACKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYDTCREGVTTRACKSEL, self).__init__(register,
            'SYDTCREGVTTRACKSEL', 'RAC_S.SYCTRL2.SYDTCREGVTTRACKSEL', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYLODIVBYPASSIQCLKBIASDELTA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYLODIVBYPASSIQCLKBIASDELTA, self).__init__(register,
            'SYLODIVBYPASSIQCLKBIASDELTA', 'RAC_S.SYCTRL2.SYLODIVBYPASSIQCLKBIASDELTA', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYDSMDACREGTRIMSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYDSMDACREGTRIMSTBLOAD, self).__init__(register,
            'SYDSMDACREGTRIMSTBLOAD', 'RAC_S.SYCTRL2.SYDSMDACREGTRIMSTBLOAD', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYLODIVTRIMIQCLKBIASDELTA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYLODIVTRIMIQCLKBIASDELTA, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASDELTA', 'RAC_S.SYCTRL2.SYLODIVTRIMIQCLKBIASDELTA', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYLODIVTRIMIQCLKBIASNDIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYLODIVTRIMIQCLKBIASNDIO, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASNDIO', 'RAC_S.SYCTRL2.SYLODIVTRIMIQCLKBIASNDIO', 'read-write',
            u"",
            13, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYVCOHCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYVCOHCAP, self).__init__(register,
            'SYVCOHCAP', 'RAC_S.SYCTRL2.SYVCOHCAP', 'read-write',
            u"",
            17, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL2_SYVCOACAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL2_SYVCOACAP, self).__init__(register,
            'SYVCOACAP', 'RAC_S.SYCTRL2.SYVCOACAP', 'read-write',
            u"",
            23, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIATRIM0_TIACAPFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIATRIM0_TIACAPFB, self).__init__(register,
            'TIACAPFB', 'RAC_S.TIATRIM0.TIACAPFB', 'read-write',
            u"",
            11, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIATRIM0_TIACOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIATRIM0_TIACOMP, self).__init__(register,
            'TIACOMP', 'RAC_S.TIATRIM0.TIACOMP', 'read-write',
            u"",
            19, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIATRIM0_TIARESFB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIATRIM0_TIARESFB, self).__init__(register,
            'TIARESFB', 'RAC_S.TIATRIM0.TIARESFB', 'read-write',
            u"",
            22, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIATRIM1_TIAOXI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIATRIM1_TIAOXI, self).__init__(register,
            'TIAOXI', 'RAC_S.TIATRIM1.TIAOXI', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIATRIM1_TIAOXQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIATRIM1_TIAOXQ, self).__init__(register,
            'TIAOXQ', 'RAC_S.TIATRIM1.TIAOXQ', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIATRIM1_TIASETVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIATRIM1_TIASETVCM, self).__init__(register,
            'TIASETVCM', 'RAC_S.TIATRIM1.TIASETVCM', 'read-write',
            u"",
            12, 4)
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


class RM_Field_RAC_S_TIAEN_TIAVLDOTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAVLDOTRIMVREF, self).__init__(register,
            'TIAVLDOTRIMVREF', 'RAC_S.TIAEN.TIAVLDOTRIMVREF', 'read-write',
            u"",
            9, 4)
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


class RM_Field_RAC_S_TIAEN_TIATHRPKDLOSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIATHRPKDLOSEL, self).__init__(register,
            'TIATHRPKDLOSEL', 'RAC_S.TIAEN.TIATHRPKDLOSEL', 'read-write',
            u"",
            15, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIATHRPKDHISEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIATHRPKDHISEL, self).__init__(register,
            'TIATHRPKDHISEL', 'RAC_S.TIAEN.TIATHRPKDHISEL', 'read-write',
            u"",
            19, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TIAEN_TIAVLDOTRIMVREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TIAEN_TIAVLDOTRIMVREG, self).__init__(register,
            'TIAVLDOTRIMVREG', 'RAC_S.TIAEN.TIAVLDOTRIMVREG', 'read-write',
            u"",
            23, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRCALBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRCALBIAS, self).__init__(register,
            'VTRCALBIAS', 'RAC_S.VTRCTRL0.VTRCALBIAS', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRCALTC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRCALTC, self).__init__(register,
            'VTRCALTC', 'RAC_S.VTRCTRL0.VTRCALTC', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRDISABLEBOOTSTRAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRDISABLEBOOTSTRAP, self).__init__(register,
            'VTRDISABLEBOOTSTRAP', 'RAC_S.VTRCTRL0.VTRDISABLEBOOTSTRAP', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTREN, self).__init__(register,
            'VTREN', 'RAC_S.VTRCTRL0.VTREN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRLDOVREFTRIM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRLDOVREFTRIM, self).__init__(register,
            'VTRLDOVREFTRIM', 'RAC_S.VTRCTRL0.VTRLDOVREFTRIM', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPCORE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPCORE, self).__init__(register,
            'VTRSTARTUPCORE', 'RAC_S.VTRCTRL0.VTRSTARTUPCORE', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPSUPPLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRSTARTUPSUPPLY, self).__init__(register,
            'VTRSTARTUPSUPPLY', 'RAC_S.VTRCTRL0.VTRSTARTUPSUPPLY', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRCALVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRCALVREF, self).__init__(register,
            'VTRCALVREF', 'RAC_S.VTRCTRL0.VTRCALVREF', 'read-write',
            u"",
            20, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_VTRCTRL0_VTRHIGHCURRENTHV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_VTRCTRL0_VTRHIGHCURRENTHV, self).__init__(register,
            'VTRHIGHCURRENTHV', 'RAC_S.VTRCTRL0.VTRHIGHCURRENTHV', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_ADCLDOSHUNTCURLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_ADCLDOSHUNTCURLVL1, self).__init__(register,
            'ADCLDOSHUNTCURLVL1', 'RAC_S.AUXADCCAL.ADCLDOSHUNTCURLVL1', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_ADCLDOSERIESAMPLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_ADCLDOSERIESAMPLVL, self).__init__(register,
            'ADCLDOSERIESAMPLVL', 'RAC_S.AUXADCCAL.ADCLDOSERIESAMPLVL', 'read-write',
            u"",
            3, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_ADCLDOSERIESAMPLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_ADCLDOSERIESAMPLVL2, self).__init__(register,
            'ADCLDOSERIESAMPLVL2', 'RAC_S.AUXADCCAL.ADCLDOSERIESAMPLVL2', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_ADCLDOSHUNTAMPLVL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_ADCLDOSHUNTAMPLVL1, self).__init__(register,
            'ADCLDOSHUNTAMPLVL1', 'RAC_S.AUXADCCAL.ADCLDOSHUNTAMPLVL1', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_ADCLDOSHUNTAMPLVL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_ADCLDOSHUNTAMPLVL2, self).__init__(register,
            'ADCLDOSHUNTAMPLVL2', 'RAC_S.AUXADCCAL.ADCLDOSHUNTAMPLVL2', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_ADCSIDETONEFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_ADCSIDETONEFREQ, self).__init__(register,
            'ADCSIDETONEFREQ', 'RAC_S.AUXADCCAL.ADCSIDETONEFREQ', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_ADCTRIMCURRINPUTBUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_ADCTRIMCURRINPUTBUF, self).__init__(register,
            'ADCTRIMCURRINPUTBUF', 'RAC_S.AUXADCCAL.ADCTRIMCURRINPUTBUF', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCAL_ADCVCMLVL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCAL_ADCVCMLVL, self).__init__(register,
            'ADCVCMLVL', 'RAC_S.AUXADCCAL.ADCVCMLVL', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCCTRLRESERVED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCCTRLRESERVED, self).__init__(register,
            'ADCCTRLRESERVED', 'RAC_S.AUXADCCTRL.ADCCTRLRESERVED', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCCTRLRESERVEDLV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCCTRLRESERVEDLV, self).__init__(register,
            'ADCCTRLRESERVEDLV', 'RAC_S.AUXADCCTRL.ADCCTRLRESERVEDLV', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCLOWCUR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCLOWCUR, self).__init__(register,
            'ADCLOWCUR', 'RAC_S.AUXADCCTRL.ADCLOWCUR', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCNEGRESCURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCNEGRESCURRENT, self).__init__(register,
            'ADCNEGRESCURRENT', 'RAC_S.AUXADCCTRL.ADCNEGRESCURRENT', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCNEGRESVCM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCNEGRESVCM, self).__init__(register,
            'ADCNEGRESVCM', 'RAC_S.AUXADCCTRL.ADCNEGRESVCM', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCOTACURRENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCOTACURRENT, self).__init__(register,
            'ADCOTACURRENT', 'RAC_S.AUXADCCTRL.ADCOTACURRENT', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCPMONSELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCPMONSELECT, self).__init__(register,
            'ADCPMONSELECT', 'RAC_S.AUXADCCTRL.ADCPMONSELECT', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCRCCALCOUNTERSTARTVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCRCCALCOUNTERSTARTVAL, self).__init__(register,
            'ADCRCCALCOUNTERSTARTVAL', 'RAC_S.AUXADCCTRL.ADCRCCALCOUNTERSTARTVAL', 'read-write',
            u"",
            20, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCSHORTINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCSHORTINPUT, self).__init__(register,
            'ADCSHORTINPUT', 'RAC_S.AUXADCCTRL.ADCSHORTINPUT', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCSETVINCM400M(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCSETVINCM400M, self).__init__(register,
            'ADCSETVINCM400M', 'RAC_S.AUXADCCTRL.ADCSETVINCM400M', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCVCMBUFBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCVCMBUFBYPASS, self).__init__(register,
            'ADCVCMBUFBYPASS', 'RAC_S.AUXADCCTRL.ADCVCMBUFBYPASS', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL_ADCLDOSERIESFORCEDSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL_ADCLDOSERIESFORCEDSTARTUP, self).__init__(register,
            'ADCLDOSERIESFORCEDSTARTUP', 'RAC_S.AUXADCCTRL.ADCLDOSERIESFORCEDSTARTUP', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL2_ADCENHALFBW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL2_ADCENHALFBW, self).__init__(register,
            'ADCENHALFBW', 'RAC_S.AUXADCCTRL2.ADCENHALFBW', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_AUXADCCTRL2_ADCENHALFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_AUXADCCTRL2_ADCENHALFMODE, self).__init__(register,
            'ADCENHALFMODE', 'RAC_S.AUXADCCTRL2.ADCENHALFMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN0_LNAMIXDISMXR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN0_LNAMIXDISMXR1, self).__init__(register,
            'LNAMIXDISMXR1', 'RAC_S.LNAMIXEN0.LNAMIXDISMXR1', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN0_LNAMIXENIRCAL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN0_LNAMIXENIRCAL1, self).__init__(register,
            'LNAMIXENIRCAL1', 'RAC_S.LNAMIXEN0.LNAMIXENIRCAL1', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_LNAMIXEN0_LNAMIXENREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_LNAMIXEN0_LNAMIXENREG, self).__init__(register,
            'LNAMIXENREG', 'RAC_S.LNAMIXEN0.LNAMIXENREG', 'read-write',
            u"",
            2, 1)
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


class RM_Field_RAC_S_SYCTRL1_SYENDLFVCTRLMONITOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYENDLFVCTRLMONITOR, self).__init__(register,
            'SYENDLFVCTRLMONITOR', 'RAC_S.SYCTRL1.SYENDLFVCTRLMONITOR', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYENDLFTDCA2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYENDLFTDCA2, self).__init__(register,
            'SYENDLFTDCA2', 'RAC_S.SYCTRL1.SYENDLFTDCA2', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYMMDSELFP4G82G4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYMMDSELFP4G82G4, self).__init__(register,
            'SYMMDSELFP4G82G4', 'RAC_S.SYCTRL1.SYMMDSELFP4G82G4', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVREGTRIMVREF, self).__init__(register,
            'SYLODIVREGTRIMVREF', 'RAC_S.SYCTRL1.SYLODIVREGTRIMVREF', 'read-write',
            u"",
            3, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYDSMDACREGILOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYDSMDACREGILOAD, self).__init__(register,
            'SYDSMDACREGILOAD', 'RAC_S.SYCTRL1.SYDSMDACREGILOAD', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVSELFCALCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVSELFCALCLK, self).__init__(register,
            'SYLODIVSELFCALCLK', 'RAC_S.SYCTRL1.SYLODIVSELFCALCLK', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYENDLF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYENDLF, self).__init__(register,
            'SYENDLF', 'RAC_S.SYCTRL1.SYENDLF', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVFCALRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVFCALRD, self).__init__(register,
            'SYLODIVFCALRD', 'RAC_S.SYCTRL1.SYLODIVFCALRD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYVCOACAPFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYVCOACAPFORCE, self).__init__(register,
            'SYVCOACAPFORCE', 'RAC_S.SYCTRL1.SYVCOACAPFORCE', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVDSMDACCLKDIVRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVDSMDACCLKDIVRATIO, self).__init__(register,
            'SYLODIVDSMDACCLKDIVRATIO', 'RAC_S.SYCTRL1.SYLODIVDSMDACCLKDIVRATIO', 'read-write',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYENDLFDQNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYENDLFDQNC, self).__init__(register,
            'SYENDLFDQNC', 'RAC_S.SYCTRL1.SYENDLFDQNC', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVFCALCLR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVFCALCLR, self).__init__(register,
            'SYLODIVFCALCLR', 'RAC_S.SYCTRL1.SYLODIVFCALCLR', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVSMUXCLKDIVRATIO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVSMUXCLKDIVRATIO, self).__init__(register,
            'SYLODIVSMUXCLKDIVRATIO', 'RAC_S.SYCTRL1.SYLODIVSMUXCLKDIVRATIO', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYENDSMDACREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYENDSMDACREG, self).__init__(register,
            'SYENDSMDACREG', 'RAC_S.SYCTRL1.SYENDSMDACREG', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYENVCOREGLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYENVCOREGLOAD, self).__init__(register,
            'SYENVCOREGLOAD', 'RAC_S.SYCTRL1.SYENVCOREGLOAD', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVTRIMIQCLKBIASIBIAS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVTRIMIQCLKBIASIBIAS, self).__init__(register,
            'SYLODIVTRIMIQCLKBIASIBIAS', 'RAC_S.SYCTRL1.SYLODIVTRIMIQCLKBIASIBIAS', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYLODIVSELFP4G82G4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYLODIVSELFP4G82G4, self).__init__(register,
            'SYLODIVSELFP4G82G4', 'RAC_S.SYCTRL1.SYLODIVSELFP4G82G4', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYMMDREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYMMDREGTRIMVREF, self).__init__(register,
            'SYMMDREGTRIMVREF', 'RAC_S.SYCTRL1.SYMMDREGTRIMVREF', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYVCOFASTSTARTUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYVCOFASTSTARTUP, self).__init__(register,
            'SYVCOFASTSTARTUP', 'RAC_S.SYCTRL1.SYVCOFASTSTARTUP', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYMMDCLKINJXOINTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYMMDCLKINJXOINTN, self).__init__(register,
            'SYMMDCLKINJXOINTN', 'RAC_S.SYCTRL1.SYMMDCLKINJXOINTN', 'read-write',
            u"",
            28, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYMMDCLKINJXOINTNFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYMMDCLKINJXOINTNFORCE, self).__init__(register,
            'SYMMDCLKINJXOINTNFORCE', 'RAC_S.SYCTRL1.SYMMDCLKINJXOINTNFORCE', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL1_SYENDSMDAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL1_SYENDSMDAC, self).__init__(register,
            'SYENDSMDAC', 'RAC_S.SYCTRL1.SYENDSMDAC', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYDLFCLAMPTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYDLFCLAMPTH, self).__init__(register,
            'SYDLFCLAMPTH', 'RAC_S.SYCTRL3.SYDLFCLAMPTH', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYDLFREADXI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYDLFREADXI, self).__init__(register,
            'SYDLFREADXI', 'RAC_S.SYCTRL3.SYDLFREADXI', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYDLFREADXF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYDLFREADXF, self).__init__(register,
            'SYDLFREADXF', 'RAC_S.SYCTRL3.SYDLFREADXF', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYDLFDQNCGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYDLFDQNCGAIN, self).__init__(register,
            'SYDLFDQNCGAIN', 'RAC_S.SYCTRL3.SYDLFDQNCGAIN', 'read-write',
            u"",
            5, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYDLFREADACAPCK2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYDLFREADACAPCK2, self).__init__(register,
            'SYDLFREADACAPCK2', 'RAC_S.SYCTRL3.SYDLFREADACAPCK2', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYLODIVFCALRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYLODIVFCALRUN, self).__init__(register,
            'SYLODIVFCALRUN', 'RAC_S.SYCTRL3.SYLODIVFCALRUN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYVCOHCAPRETIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYVCOHCAPRETIME, self).__init__(register,
            'SYVCOHCAPRETIME', 'RAC_S.SYCTRL3.SYVCOHCAPRETIME', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYDSMDACREGTRIMVREF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYDSMDACREGTRIMVREF, self).__init__(register,
            'SYDSMDACREGTRIMVREF', 'RAC_S.SYCTRL3.SYDSMDACREGTRIMVREF', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYCTRL3_SYMMDDENOM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYCTRL3_SYMMDDENOM, self).__init__(register,
            'SYMMDDENOM', 'RAC_S.SYCTRL3.SYMMDDENOM', 'read-write',
            u"",
            13, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF_SYDLFDACVALTHM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF_SYDLFDACVALTHM, self).__init__(register,
            'SYDLFDACVALTHM', 'RAC_S.SYDLF.SYDLFDACVALTHM', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF_SYDLFVCTRLHITH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF_SYDLFVCTRLHITH, self).__init__(register,
            'SYDLFVCTRLHITH', 'RAC_S.SYDLF.SYDLFVCTRLHITH', 'read-write',
            u"",
            7, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF_SYDLFLPFBWZP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF_SYDLFLPFBWZP, self).__init__(register,
            'SYDLFLPFBWZP', 'RAC_S.SYDLF.SYDLFLPFBWZP', 'read-write',
            u"",
            10, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF_SYDLFLPFBWLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF_SYDLFLPFBWLOAD, self).__init__(register,
            'SYDLFLPFBWLOAD', 'RAC_S.SYDLF.SYDLFLPFBWLOAD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF_SYDLFDACVALBIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF_SYDLFDACVALBIN, self).__init__(register,
            'SYDLFDACVALBIN', 'RAC_S.SYDLF.SYDLFDACVALBIN', 'read-write',
            u"",
            22, 6)
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


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENLOADREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENLOADREGPREDRV, self).__init__(register,
            'TX0DBMENLOADREGPREDRV', 'RAC_S.TX0DBMEN.TX0DBMENLOADREGPREDRV', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENLOADREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENLOADREGPA, self).__init__(register,
            'TX0DBMENLOADREGPA', 'RAC_S.TX0DBMEN.TX0DBMENLOADREGPA', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENBYPASSREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENBYPASSREGPA, self).__init__(register,
            'TX0DBMENBYPASSREGPA', 'RAC_S.TX0DBMEN.TX0DBMENBYPASSREGPA', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENBIASREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENBIASREGPREDRV, self).__init__(register,
            'TX0DBMENBIASREGPREDRV', 'RAC_S.TX0DBMEN.TX0DBMENBIASREGPREDRV', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENREPLICABIASREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENREPLICABIASREGPA, self).__init__(register,
            'TX0DBMENREPLICABIASREGPA', 'RAC_S.TX0DBMEN.TX0DBMENREPLICABIASREGPA', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPA, self).__init__(register,
            'TX0DBMENPA', 'RAC_S.TX0DBMEN.TX0DBMENPA', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPAREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPAREGSTBLOAD, self).__init__(register,
            'TX0DBMENPAREGSTBLOAD', 'RAC_S.TX0DBMEN.TX0DBMENPAREGSTBLOAD', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRVREGSTBLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMEN_TX0DBMENPREDRVREGSTBLOAD, self).__init__(register,
            'TX0DBMENPREDRVREGSTBLOAD', 'RAC_S.TX0DBMEN.TX0DBMENPREDRVREGSTBLOAD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMCTRL_TX0DBMPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMCTRL_TX0DBMPOWER, self).__init__(register,
            'TX0DBMPOWER', 'RAC_S.TX0DBMCTRL.TX0DBMPOWER', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMCTRL_TX0DBMLATCHBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMCTRL_TX0DBMLATCHBYPASS, self).__init__(register,
            'TX0DBMLATCHBYPASS', 'RAC_S.TX0DBMCTRL.TX0DBMLATCHBYPASS', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMCTRL_TX0DBMSLICERESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMCTRL_TX0DBMSLICERESET, self).__init__(register,
            'TX0DBMSLICERESET', 'RAC_S.TX0DBMCTRL.TX0DBMSLICERESET', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPREDRV, self).__init__(register,
            'TX0DBMTRIMPSRBSTREGPREDRV', 'RAC_S.TX0DBMTRIM.TX0DBMTRIMPSRBSTREGPREDRV', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMPREDRVSLOPE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMPREDRVSLOPE, self).__init__(register,
            'TX0DBMTRIMPREDRVSLOPE', 'RAC_S.TX0DBMTRIM.TX0DBMTRIMPREDRVSLOPE', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMPSRBSTREGPA, self).__init__(register,
            'TX0DBMTRIMPSRBSTREGPA', 'RAC_S.TX0DBMTRIM.TX0DBMTRIMPSRBSTREGPA', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMTAPCAP100F(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMTAPCAP100F, self).__init__(register,
            'TX0DBMTRIMTAPCAP100F', 'RAC_S.TX0DBMTRIM.TX0DBMTRIMTAPCAP100F', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMTAPCAP200F(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMTAPCAP200F, self).__init__(register,
            'TX0DBMTRIMTAPCAP200F', 'RAC_S.TX0DBMTRIM.TX0DBMTRIMTAPCAP200F', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMVREFREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMVREFREGPA, self).__init__(register,
            'TX0DBMTRIMVREFREGPA', 'RAC_S.TX0DBMTRIM.TX0DBMTRIMVREFREGPA', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMVREFREGPREDRV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM_TX0DBMTRIMVREFREGPREDRV, self).__init__(register,
            'TX0DBMTRIMVREFREGPREDRV', 'RAC_S.TX0DBMTRIM.TX0DBMTRIMVREFREGPREDRV', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMDUTYCYN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMDUTYCYN, self).__init__(register,
            'TX0DBMTRIMDUTYCYN', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMDUTYCYN', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMNBIASPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMNBIASPA, self).__init__(register,
            'TX0DBMTRIMNBIASPA', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMNBIASPA', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPBIASPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMPBIASPA, self).__init__(register,
            'TX0DBMTRIMPBIASPA', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMPBIASPA', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMRFBREGPA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMRFBREGPA, self).__init__(register,
            'TX0DBMTRIMRFBREGPA', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMRFBREGPA', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMDUTYCYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX0DBMTRIM0_TX0DBMTRIMDUTYCYP, self).__init__(register,
            'TX0DBMTRIMDUTYCYP', 'RAC_S.TX0DBMTRIM0.TX0DBMTRIMDUTYCYP', 'read-write',
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


class RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGSTBLOADAUTO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMEN_TX10DBMENPAREGSTBLOADAUTO, self).__init__(register,
            'TX10DBMENPAREGSTBLOADAUTO', 'RAC_S.TX10DBMEN.TX10DBMENPAREGSTBLOADAUTO', 'read-write',
            u"",
            7, 1)
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


class RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMPOWER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMPOWER, self).__init__(register,
            'TX10DBMPOWER', 'RAC_S.TX10DBMCTRL1.TX10DBMPOWER', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMSLICERST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMSLICERST, self).__init__(register,
            'TX10DBMSLICERST', 'RAC_S.TX10DBMCTRL1.TX10DBMSLICERST', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMRXPADATTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMRXPADATTN, self).__init__(register,
            'TX10DBMRXPADATTN', 'RAC_S.TX10DBMCTRL1.TX10DBMRXPADATTN', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMRAMPCLKBYPASS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMCTRL1_TX10DBMRAMPCLKBYPASS, self).__init__(register,
            'TX10DBMRAMPCLKBYPASS', 'RAC_S.TX10DBMCTRL1.TX10DBMRAMPCLKBYPASS', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_TX10DBMTX_TX10DBMTRIMHFCTAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_TX10DBMTX_TX10DBMTRIMHFCTAP, self).__init__(register,
            'TX10DBMTRIMHFCTAP', 'RAC_S.TX10DBMTX.TX10DBMTRIMHFCTAP', 'read-write',
            u"",
            18, 4)
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


class RM_Field_RAC_S_SYDLF1_SYDLFPFDLOCKSAMPLETH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF1_SYDLFPFDLOCKSAMPLETH, self).__init__(register,
            'SYDLFPFDLOCKSAMPLETH', 'RAC_S.SYDLF1.SYDLFPFDLOCKSAMPLETH', 'read-write',
            u"",
            10, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF1_SYDLFDTHIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF1_SYDLFDTHIN, self).__init__(register,
            'SYDLFDTHIN', 'RAC_S.SYDLF1.SYDLFDTHIN', 'read-write',
            u"",
            14, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SYDLF1_SYDLFPOSITIVECOEFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SYDLF1_SYDLFPOSITIVECOEFF, self).__init__(register,
            'SYDLFPOSITIVECOEFF', 'RAC_S.SYDLF1.SYDLFPOSITIVECOEFF', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_SYZZZSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_SYZZZSPARES, self).__init__(register,
            'SYZZZSPARES', 'RAC_S.SPARE1.SYZZZSPARES', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_TIASPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_TIASPARE, self).__init__(register,
            'TIASPARE', 'RAC_S.SPARE1.TIASPARE', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_TX10DBMSPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_TX10DBMSPARE, self).__init__(register,
            'TX10DBMSPARE', 'RAC_S.SPARE1.TX10DBMSPARE', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_SPARE1_VTRSPARES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_SPARE1_VTRSPARES, self).__init__(register,
            'VTRSPARES', 'RAC_S.SPARE1.VTRSPARES', 'read-write',
            u"",
            13, 4)
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


class RM_Field_RAC_S_RFLOCK0_RACIFPGAEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACIFPGAEN, self).__init__(register,
            'RACIFPGAEN', 'RAC_S.RFLOCK0.RACIFPGAEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACTX0DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACTX0DBM, self).__init__(register,
            'RACTX0DBM', 'RAC_S.RFLOCK0.RACTX0DBM', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACTX10DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACTX10DBM, self).__init__(register,
            'RACTX10DBM', 'RAC_S.RFLOCK0.RACTX10DBM', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RAC_S_RFLOCK0_RACTX20DBM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RAC_S_RFLOCK0_RACTX20DBM, self).__init__(register,
            'RACTX20DBM', 'RAC_S.RFLOCK0.RACTX20DBM', 'read-write',
            u"",
            19, 1)
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



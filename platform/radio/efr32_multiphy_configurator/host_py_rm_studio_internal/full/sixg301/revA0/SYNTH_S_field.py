
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_SYNTH_S_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'SYNTH_S.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_EN_EN, self).__init__(register,
            'EN', 'SYNTH_S.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IF_LOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IF_LOCKED, self).__init__(register,
            'LOCKED', 'SYNTH_S.IF.LOCKED', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IF_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IF_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'SYNTH_S.IF.UNLOCKED', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IF_SYRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IF_SYRDY, self).__init__(register,
            'SYRDY', 'SYNTH_S.IF.SYRDY', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IF_VCOHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IF_VCOHIGH, self).__init__(register,
            'VCOHIGH', 'SYNTH_S.IF.VCOHIGH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IF_VCOLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IF_VCOLOW, self).__init__(register,
            'VCOLOW', 'SYNTH_S.IF.VCOLOW', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IF_LOCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IF_LOCNTDONE, self).__init__(register,
            'LOCNTDONE', 'SYNTH_S.IF.LOCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IF_FCALDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IF_FCALDONE, self).__init__(register,
            'FCALDONE', 'SYNTH_S.IF.FCALDONE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IEN_LOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IEN_LOCKED, self).__init__(register,
            'LOCKED', 'SYNTH_S.IEN.LOCKED', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IEN_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IEN_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'SYNTH_S.IEN.UNLOCKED', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IEN_SYRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IEN_SYRDY, self).__init__(register,
            'SYRDY', 'SYNTH_S.IEN.SYRDY', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IEN_VCOHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IEN_VCOHIGH, self).__init__(register,
            'VCOHIGH', 'SYNTH_S.IEN.VCOHIGH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IEN_VCOLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IEN_VCOLOW, self).__init__(register,
            'VCOLOW', 'SYNTH_S.IEN.VCOLOW', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IEN_LOCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IEN_LOCNTDONE, self).__init__(register,
            'LOCNTDONE', 'SYNTH_S.IEN.LOCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IEN_FCALDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IEN_FCALDONE, self).__init__(register,
            'FCALDONE', 'SYNTH_S.IEN.FCALDONE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIF_LOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIF_LOCKED, self).__init__(register,
            'LOCKED', 'SYNTH_S.SEQIF.LOCKED', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIF_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIF_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'SYNTH_S.SEQIF.UNLOCKED', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIF_SYRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIF_SYRDY, self).__init__(register,
            'SYRDY', 'SYNTH_S.SEQIF.SYRDY', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIF_VCOHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIF_VCOHIGH, self).__init__(register,
            'VCOHIGH', 'SYNTH_S.SEQIF.VCOHIGH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIF_VCOLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIF_VCOLOW, self).__init__(register,
            'VCOLOW', 'SYNTH_S.SEQIF.VCOLOW', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIF_LOCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIF_LOCNTDONE, self).__init__(register,
            'LOCNTDONE', 'SYNTH_S.SEQIF.LOCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIF_FCALDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIF_FCALDONE, self).__init__(register,
            'FCALDONE', 'SYNTH_S.SEQIF.FCALDONE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIEN_LOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIEN_LOCKED, self).__init__(register,
            'LOCKED', 'SYNTH_S.SEQIEN.LOCKED', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIEN_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIEN_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'SYNTH_S.SEQIEN.UNLOCKED', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIEN_SYRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIEN_SYRDY, self).__init__(register,
            'SYRDY', 'SYNTH_S.SEQIEN.SYRDY', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIEN_VCOHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIEN_VCOHIGH, self).__init__(register,
            'VCOHIGH', 'SYNTH_S.SEQIEN.VCOHIGH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIEN_VCOLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIEN_VCOLOW, self).__init__(register,
            'VCOLOW', 'SYNTH_S.SEQIEN.VCOLOW', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIEN_LOCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIEN_LOCNTDONE, self).__init__(register,
            'LOCNTDONE', 'SYNTH_S.SEQIEN.LOCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SEQIEN_FCALDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SEQIEN_FCALDONE, self).__init__(register,
            'FCALDONE', 'SYNTH_S.SEQIEN.FCALDONE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_INLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_INLOCK, self).__init__(register,
            'INLOCK', 'SYNTH_S.STATUS.INLOCK', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_IFFREQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_IFFREQEN, self).__init__(register,
            'IFFREQEN', 'SYNTH_S.STATUS.IFFREQEN', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_SYNTHREADY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_SYNTHREADY, self).__init__(register,
            'SYNTHREADY', 'SYNTH_S.STATUS.SYNTHREADY', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_VCOFREQACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_VCOFREQACTIVE, self).__init__(register,
            'VCOFREQACTIVE', 'SYNTH_S.STATUS.VCOFREQACTIVE', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_LMSSTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_LMSSTATUS, self).__init__(register,
            'LMSSTATUS', 'SYNTH_S.STATUS.LMSSTATUS', 'read-only',
            u"",
            4, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CMD_SYNTHSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CMD_SYNTHSTART, self).__init__(register,
            'SYNTHSTART', 'SYNTH_S.CMD.SYNTHSTART', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CMD_SYNTHSTOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CMD_SYNTHSTOP, self).__init__(register,
            'SYNTHSTOP', 'SYNTH_S.CMD.SYNTHSTOP', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CMD_ENABLEIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CMD_ENABLEIF, self).__init__(register,
            'ENABLEIF', 'SYNTH_S.CMD.ENABLEIF', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CMD_DISABLEIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CMD_DISABLEIF, self).__init__(register,
            'DISABLEIF', 'SYNTH_S.CMD.DISABLEIF', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CMD_CAPCALSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CMD_CAPCALSTART, self).__init__(register,
            'CAPCALSTART', 'SYNTH_S.CMD.CAPCALSTART', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CMD_VCOADDCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CMD_VCOADDCAP, self).__init__(register,
            'VCOADDCAP', 'SYNTH_S.CMD.VCOADDCAP', 'write-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CMD_VCOSUBCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CMD_VCOSUBCAP, self).__init__(register,
            'VCOSUBCAP', 'SYNTH_S.CMD.VCOSUBCAP', 'write-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_LOCKTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_LOCKTHRESHOLD, self).__init__(register,
            'LOCKTHRESHOLD', 'SYNTH_S.CTRL.LOCKTHRESHOLD', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_PRSMUX0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_PRSMUX0, self).__init__(register,
            'PRSMUX0', 'SYNTH_S.CTRL.PRSMUX0', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_PRSMUX1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_PRSMUX1, self).__init__(register,
            'PRSMUX1', 'SYNTH_S.CTRL.PRSMUX1', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_DISCLKSYNTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_DISCLKSYNTH, self).__init__(register,
            'DISCLKSYNTH', 'SYNTH_S.CTRL.DISCLKSYNTH', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_INVCLKSYNTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_INVCLKSYNTH, self).__init__(register,
            'INVCLKSYNTH', 'SYNTH_S.CTRL.INVCLKSYNTH', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_INTEGERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_INTEGERMODE, self).__init__(register,
            'INTEGERMODE', 'SYNTH_S.CTRL.INTEGERMODE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_MMDRSTNOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_MMDRSTNOVERRIDEEN, self).__init__(register,
            'MMDRSTNOVERRIDEEN', 'SYNTH_S.CTRL.MMDRSTNOVERRIDEEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_MMDMANRSTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_MMDMANRSTN, self).__init__(register,
            'MMDMANRSTN', 'SYNTH_S.CTRL.MMDMANRSTN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_RDGLMS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_RDGLMS, self).__init__(register,
            'RDGLMS', 'SYNTH_S.CTRL.RDGLMS', 'write-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_RDPLMS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_RDPLMS, self).__init__(register,
            'RDPLMS', 'SYNTH_S.CTRL.RDPLMS', 'write-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_BOUNDARYCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_BOUNDARYCNT, self).__init__(register,
            'BOUNDARYCNT', 'SYNTH_S.CTRL.BOUNDARYCNT', 'read-write',
            u"",
            16, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_OWREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_OWREN, self).__init__(register,
            'OWREN', 'SYNTH_S.CTRL.OWREN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_QNCTONEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_QNCTONEEN, self).__init__(register,
            'QNCTONEEN', 'SYNTH_S.CTRL.QNCTONEEN', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCDACCTRL_VCDACVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCDACCTRL_VCDACVAL, self).__init__(register,
            'VCDACVAL', 'SYNTH_S.VCDACCTRL.VCDACVAL', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCDACCTRL_VCDACEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCDACCTRL_VCDACEN, self).__init__(register,
            'VCDACEN', 'SYNTH_S.VCDACCTRL.VCDACEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FREQ_FREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FREQ_FREQ, self).__init__(register,
            'FREQ', 'SYNTH_S.FREQ.FREQ', 'read-write',
            u"",
            0, 28)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IFFREQ_IFFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IFFREQ_IFFREQ, self).__init__(register,
            'IFFREQ', 'SYNTH_S.IFFREQ.IFFREQ', 'read-write',
            u"",
            0, 20)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_IFFREQ_LOSIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_IFFREQ_LOSIDE, self).__init__(register,
            'LOSIDE', 'SYNTH_S.IFFREQ.LOSIDE', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DIVCTRL_LODIVFREQCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DIVCTRL_LODIVFREQCTRL, self).__init__(register,
            'LODIVFREQCTRL', 'SYNTH_S.DIVCTRL.LODIVFREQCTRL', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CHCTRL_CHNO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CHCTRL_CHNO, self).__init__(register,
            'CHNO', 'SYNTH_S.CHCTRL.CHNO', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CHSP_CHSP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CHSP_CHSP, self).__init__(register,
            'CHSP', 'SYNTH_S.CHSP.CHSP', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALOFFSET_CALOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALOFFSET_CALOFFSET, self).__init__(register,
            'CALOFFSET', 'SYNTH_S.CALOFFSET.CALOFFSET', 'read-write',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCOTUNING_VCOTUNING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCOTUNING_VCOTUNING, self).__init__(register,
            'VCOTUNING', 'SYNTH_S.VCOTUNING.VCOTUNING', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCOTUNING_VCAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCOTUNING_VCAPSEL, self).__init__(register,
            'VCAPSEL', 'SYNTH_S.VCOTUNING.VCAPSEL', 'read-write',
            u"",
            11, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_MODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_MODE, self).__init__(register,
            'MODE', 'SYNTH_S.VCORANGE.MODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_SWITCHMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_SWITCHMODE, self).__init__(register,
            'SWITCHMODE', 'SYNTH_S.VCORANGE.SWITCHMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_HIGHTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_HIGHTHRESH, self).__init__(register,
            'HIGHTHRESH', 'SYNTH_S.VCORANGE.HIGHTHRESH', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_LOWTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_LOWTHRESH, self).__init__(register,
            'LOWTHRESH', 'SYNTH_S.VCORANGE.LOWTHRESH', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_OVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_OVERRIDEEN, self).__init__(register,
            'OVERRIDEEN', 'SYNTH_S.VCORANGE.OVERRIDEEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_DATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_DATA, self).__init__(register,
            'DATA', 'SYNTH_S.VCORANGE.DATA', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_LOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_LOAD, self).__init__(register,
            'LOAD', 'SYNTH_S.VCORANGE.LOAD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_RAMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_RAMPEN, self).__init__(register,
            'RAMPEN', 'SYNTH_S.VCORANGE.RAMPEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_CMPENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_CMPENABLE, self).__init__(register,
            'CMPENABLE', 'SYNTH_S.VCORANGE.CMPENABLE', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_CMPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_CMPRESET, self).__init__(register,
            'CMPRESET', 'SYNTH_S.VCORANGE.CMPRESET', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_RAMPRATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_RAMPRATE, self).__init__(register,
            'RAMPRATE', 'SYNTH_S.VCORANGE.RAMPRATE', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_THROUGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_THROUGH, self).__init__(register,
            'THROUGH', 'SYNTH_S.VCORANGE.THROUGH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCORANGE_INVCOMPDIR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCORANGE_INVCOMPDIR, self).__init__(register,
            'INVCOMPDIR', 'SYNTH_S.VCORANGE.INVCOMPDIR', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCOGAIN_VCOKVCOARSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCOGAIN_VCOKVCOARSE, self).__init__(register,
            'VCOKVCOARSE', 'SYNTH_S.VCOGAIN.VCOKVCOARSE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCOGAIN_VCOKVFINE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCOGAIN_VCOKVFINE, self).__init__(register,
            'VCOKVFINE', 'SYNTH_S.VCOGAIN.VCOKVFINE', 'read-write',
            u"",
            4, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCCTRL_QNCMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCCTRL_QNCMODE, self).__init__(register,
            'QNCMODE', 'SYNTH_S.QNCCTRL.QNCMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCCTRL_ENABLEDQNCTIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCCTRL_ENABLEDQNCTIME, self).__init__(register,
            'ENABLEDQNCTIME', 'SYNTH_S.QNCCTRL.ENABLEDQNCTIME', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCCTRL_QNCOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCCTRL_QNCOFFSET, self).__init__(register,
            'QNCOFFSET', 'SYNTH_S.QNCCTRL.QNCOFFSET', 'read-write',
            u"",
            6, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCCTRL_FORCEQNCCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCCTRL_FORCEQNCCLK, self).__init__(register,
            'FORCEQNCCLK', 'SYNTH_S.QNCCTRL.FORCEQNCCLK', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCCTRL_TDCSIGNDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCCTRL_TDCSIGNDEL, self).__init__(register,
            'TDCSIGNDEL', 'SYNTH_S.QNCCTRL.TDCSIGNDEL', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCDACCTRL_QNCDACVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCDACCTRL_QNCDACVAL, self).__init__(register,
            'QNCDACVAL', 'SYNTH_S.QNCDACCTRL.QNCDACVAL', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCDACCTRL_QNCDACOVERRIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCDACCTRL_QNCDACOVERRIDE, self).__init__(register,
            'QNCDACOVERRIDE', 'SYNTH_S.QNCDACCTRL.QNCDACOVERRIDE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCDACCTRL_QNCDACINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCDACCTRL_QNCDACINIT, self).__init__(register,
            'QNCDACINIT', 'SYNTH_S.QNCDACCTRL.QNCDACINIT', 'read-write',
            u"",
            10, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_QNCDACCTRL_QNCTONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_QNCDACCTRL_QNCTONEAMP, self).__init__(register,
            'QNCTONEAMP', 'SYNTH_S.QNCDACCTRL.QNCTONEAMP', 'read-write',
            u"",
            23, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCOFRCCAL_TIMEOUTCOUNTMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCOFRCCAL_TIMEOUTCOUNTMAX, self).__init__(register,
            'TIMEOUTCOUNTMAX', 'SYNTH_S.VCOFRCCAL.TIMEOUTCOUNTMAX', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCOFRCCAL_TIMEOUTCOUNTRESTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCOFRCCAL_TIMEOUTCOUNTRESTART, self).__init__(register,
            'TIMEOUTCOUNTRESTART', 'SYNTH_S.VCOFRCCAL.TIMEOUTCOUNTRESTART', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_ENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_ENABLE, self).__init__(register,
            'ENABLE', 'SYNTH_S.LOCNTCTRL.ENABLE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_CLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_CLEAR, self).__init__(register,
            'CLEAR', 'SYNTH_S.LOCNTCTRL.CLEAR', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_RUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_RUN, self).__init__(register,
            'RUN', 'SYNTH_S.LOCNTCTRL.RUN', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_READ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_READ, self).__init__(register,
            'READ', 'SYNTH_S.LOCNTCTRL.READ', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_LOCNTOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_LOCNTOVERRIDEEN, self).__init__(register,
            'LOCNTOVERRIDEEN', 'SYNTH_S.LOCNTCTRL.LOCNTOVERRIDEEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_LOCNTMANCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_LOCNTMANCLEAR, self).__init__(register,
            'LOCNTMANCLEAR', 'SYNTH_S.LOCNTCTRL.LOCNTMANCLEAR', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_LOCNTMANRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_LOCNTMANRUN, self).__init__(register,
            'LOCNTMANRUN', 'SYNTH_S.LOCNTCTRL.LOCNTMANRUN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_FCALRUNCLKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_FCALRUNCLKEN, self).__init__(register,
            'FCALRUNCLKEN', 'SYNTH_S.LOCNTCTRL.FCALRUNCLKEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE, self).__init__(register,
            'NUMCYCLE', 'SYNTH_S.LOCNTCTRL.NUMCYCLE', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE1, self).__init__(register,
            'NUMCYCLE1', 'SYNTH_S.LOCNTCTRL.NUMCYCLE1', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE2, self).__init__(register,
            'NUMCYCLE2', 'SYNTH_S.LOCNTCTRL.NUMCYCLE2', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE3, self).__init__(register,
            'NUMCYCLE3', 'SYNTH_S.LOCNTCTRL.NUMCYCLE3', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE4, self).__init__(register,
            'NUMCYCLE4', 'SYNTH_S.LOCNTCTRL.NUMCYCLE4', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE5, self).__init__(register,
            'NUMCYCLE5', 'SYNTH_S.LOCNTCTRL.NUMCYCLE5', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTSTATUS_LOCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTSTATUS_LOCOUNT, self).__init__(register,
            'LOCOUNT', 'SYNTH_S.LOCNTSTATUS.LOCOUNT', 'read-only',
            u"",
            0, 22)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTSTATUS_BUSY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTSTATUS_BUSY, self).__init__(register,
            'BUSY', 'SYNTH_S.LOCNTSTATUS.BUSY', 'read-only',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTTARGET_TARGET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTTARGET_TARGET, self).__init__(register,
            'TARGET', 'SYNTH_S.LOCNTTARGET.TARGET', 'read-only',
            u"",
            0, 22)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_MMDDENOMINIT_DENOMINIT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_MMDDENOMINIT_DENOMINIT0, self).__init__(register,
            'DENOMINIT0', 'SYNTH_S.MMDDENOMINIT.DENOMINIT0', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_MMDDENOMINIT_DENOMINIT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_MMDDENOMINIT_DENOMINIT1, self).__init__(register,
            'DENOMINIT1', 'SYNTH_S.MMDDENOMINIT.DENOMINIT1', 'read-write',
            u"",
            9, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_MMDDENOMINIT_MMDXOJINTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_MMDDENOMINIT_MMDXOJINTN, self).__init__(register,
            'MMDXOJINTN', 'SYNTH_S.MMDDENOMINIT.MMDXOJINTN', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_GLMS_GLMSENABLEDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_GLMS_GLMSENABLEDELAY, self).__init__(register,
            'GLMSENABLEDELAY', 'SYNTH_S.GLMS.GLMSENABLEDELAY', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_GLMS_GLMSGEARSLOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_GLMS_GLMSGEARSLOT, self).__init__(register,
            'GLMSGEARSLOT', 'SYNTH_S.GLMS.GLMSGEARSLOT', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_GLMS_GLMSGEAR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_GLMS_GLMSGEAR0, self).__init__(register,
            'GLMSGEAR0', 'SYNTH_S.GLMS.GLMSGEAR0', 'read-write',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_GLMS_GLMSGEAR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_GLMS_GLMSGEAR1, self).__init__(register,
            'GLMSGEAR1', 'SYNTH_S.GLMS.GLMSGEAR1', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_GLMS_GLMSGEAR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_GLMS_GLMSGEAR2, self).__init__(register,
            'GLMSGEAR2', 'SYNTH_S.GLMS.GLMSGEAR2', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_GLMS_GLMSGEAR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_GLMS_GLMSGEAR3, self).__init__(register,
            'GLMSGEAR3', 'SYNTH_S.GLMS.GLMSGEAR3', 'read-write',
            u"",
            21, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_GLMS_GLMSGEAR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_GLMS_GLMSGEAR4, self).__init__(register,
            'GLMSGEAR4', 'SYNTH_S.GLMS.GLMSGEAR4', 'read-write',
            u"",
            26, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_PLMS_PLMSENABLEDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_PLMS_PLMSENABLEDELAY, self).__init__(register,
            'PLMSENABLEDELAY', 'SYNTH_S.PLMS.PLMSENABLEDELAY', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_PLMS_PLMSGEARSLOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_PLMS_PLMSGEARSLOT, self).__init__(register,
            'PLMSGEARSLOT', 'SYNTH_S.PLMS.PLMSGEARSLOT', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_PLMS_PLMSGEAR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_PLMS_PLMSGEAR0, self).__init__(register,
            'PLMSGEAR0', 'SYNTH_S.PLMS.PLMSGEAR0', 'read-write',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_PLMS_PLMSGEAR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_PLMS_PLMSGEAR1, self).__init__(register,
            'PLMSGEAR1', 'SYNTH_S.PLMS.PLMSGEAR1', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_PLMS_PLMSGEAR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_PLMS_PLMSGEAR2, self).__init__(register,
            'PLMSGEAR2', 'SYNTH_S.PLMS.PLMSGEAR2', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_PLMS_PLMSGEAR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_PLMS_PLMSGEAR3, self).__init__(register,
            'PLMSGEAR3', 'SYNTH_S.PLMS.PLMSGEAR3', 'read-write',
            u"",
            21, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_PLMS_PLMSGEAR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_PLMS_PLMSGEAR4, self).__init__(register,
            'PLMSGEAR4', 'SYNTH_S.PLMS.PLMSGEAR4', 'read-write',
            u"",
            26, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LMSOVERRIDE_GLMSOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LMSOVERRIDE_GLMSOVERRIDEEN, self).__init__(register,
            'GLMSOVERRIDEEN', 'SYNTH_S.LMSOVERRIDE.GLMSOVERRIDEEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LMSOVERRIDE_GLMSOVERRIDEVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LMSOVERRIDE_GLMSOVERRIDEVAL, self).__init__(register,
            'GLMSOVERRIDEVAL', 'SYNTH_S.LMSOVERRIDE.GLMSOVERRIDEVAL', 'read-write',
            u"",
            1, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LMSOVERRIDE_PLMSOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LMSOVERRIDE_PLMSOVERRIDEEN, self).__init__(register,
            'PLMSOVERRIDEEN', 'SYNTH_S.LMSOVERRIDE.PLMSOVERRIDEEN', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LMSOVERRIDE_PLMSOVERRIDEVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LMSOVERRIDE_PLMSOVERRIDEVAL, self).__init__(register,
            'PLMSOVERRIDEVAL', 'SYNTH_S.LMSOVERRIDE.PLMSOVERRIDEVAL', 'read-write',
            u"",
            15, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR2, self).__init__(register,
            'TXLOCKLPFBWGEAR2', 'SYNTH_S.DLFCTRLTX.TXLOCKLPFBWGEAR2', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR3, self).__init__(register,
            'TXLOCKLPFBWGEAR3', 'SYNTH_S.DLFCTRLTX.TXLOCKLPFBWGEAR3', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR4, self).__init__(register,
            'TXLOCKLPFBWGEAR4', 'SYNTH_S.DLFCTRLTX.TXLOCKLPFBWGEAR4', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR5, self).__init__(register,
            'TXLOCKLPFBWGEAR5', 'SYNTH_S.DLFCTRLTX.TXLOCKLPFBWGEAR5', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR6, self).__init__(register,
            'TXLOCKLPFBWGEAR6', 'SYNTH_S.DLFCTRLTX.TXLOCKLPFBWGEAR6', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR7, self).__init__(register,
            'TXLOCKLPFBWGEAR7', 'SYNTH_S.DLFCTRLTX.TXLOCKLPFBWGEAR7', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR8, self).__init__(register,
            'TXLOCKLPFBWGEAR8', 'SYNTH_S.DLFCTRLTX.TXLOCKLPFBWGEAR8', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLTX_TXLOCKLPFBWGEAR9, self).__init__(register,
            'TXLOCKLPFBWGEAR9', 'SYNTH_S.DLFCTRLTX.TXLOCKLPFBWGEAR9', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR2, self).__init__(register,
            'RXLOCKLPFBWGEAR2', 'SYNTH_S.DLFCTRLRX.RXLOCKLPFBWGEAR2', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR3, self).__init__(register,
            'RXLOCKLPFBWGEAR3', 'SYNTH_S.DLFCTRLRX.RXLOCKLPFBWGEAR3', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR4, self).__init__(register,
            'RXLOCKLPFBWGEAR4', 'SYNTH_S.DLFCTRLRX.RXLOCKLPFBWGEAR4', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR5, self).__init__(register,
            'RXLOCKLPFBWGEAR5', 'SYNTH_S.DLFCTRLRX.RXLOCKLPFBWGEAR5', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR6, self).__init__(register,
            'RXLOCKLPFBWGEAR6', 'SYNTH_S.DLFCTRLRX.RXLOCKLPFBWGEAR6', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR7, self).__init__(register,
            'RXLOCKLPFBWGEAR7', 'SYNTH_S.DLFCTRLRX.RXLOCKLPFBWGEAR7', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR8, self).__init__(register,
            'RXLOCKLPFBWGEAR8', 'SYNTH_S.DLFCTRLRX.RXLOCKLPFBWGEAR8', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRLRX_RXLOCKLPFBWGEAR9, self).__init__(register,
            'RXLOCKLPFBWGEAR9', 'SYNTH_S.DLFCTRLRX.RXLOCKLPFBWGEAR9', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_LOCKLPFBWGEAR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_LOCKLPFBWGEAR0, self).__init__(register,
            'LOCKLPFBWGEAR0', 'SYNTH_S.DLFCTRL.LOCKLPFBWGEAR0', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_LOCKLPFBWGEAR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_LOCKLPFBWGEAR1, self).__init__(register,
            'LOCKLPFBWGEAR1', 'SYNTH_S.DLFCTRL.LOCKLPFBWGEAR1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_LOCKLPFBWGEARSLOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_LOCKLPFBWGEARSLOT, self).__init__(register,
            'LOCKLPFBWGEARSLOT', 'SYNTH_S.DLFCTRL.LOCKLPFBWGEARSLOT', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_LPFBWLOADDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_LPFBWLOADDEL, self).__init__(register,
            'LPFBWLOADDEL', 'SYNTH_S.DLFCTRL.LPFBWLOADDEL', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_LPFBWFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_LPFBWFORCE, self).__init__(register,
            'LPFBWFORCE', 'SYNTH_S.DLFCTRL.LPFBWFORCE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_LPFBWLOADMAN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_LPFBWLOADMAN, self).__init__(register,
            'LPFBWLOADMAN', 'SYNTH_S.DLFCTRL.LPFBWLOADMAN', 'write-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_LPFBWDURINGHOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_LPFBWDURINGHOP, self).__init__(register,
            'LPFBWDURINGHOP', 'SYNTH_S.DLFCTRL.LPFBWDURINGHOP', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_LPFBWAFTERHOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_LPFBWAFTERHOP, self).__init__(register,
            'LPFBWAFTERHOP', 'SYNTH_S.DLFCTRL.LPFBWAFTERHOP', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFCTRL_DLFADDRRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFCTRL_DLFADDRRST, self).__init__(register,
            'DLFADDRRST', 'SYNTH_S.DLFCTRL.DLFADDRRST', 'write-only',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFKF_KF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFKF_KF, self).__init__(register,
            'KF', 'SYNTH_S.DLFKF.KF', 'read-write',
            u"",
            0, 22)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFKIZP_KI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFKIZP_KI, self).__init__(register,
            'KI', 'SYNTH_S.DLFKIZP.KI', 'read-write',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DLFKIZP_ZP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DLFKIZP_ZP, self).__init__(register,
            'ZP', 'SYNTH_S.DLFKIZP.ZP', 'read-write',
            u"",
            19, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_DITHERDACRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_DITHERDACRX, self).__init__(register,
            'DITHERDACRX', 'SYNTH_S.DSMCTRLRX.DITHERDACRX', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_LSBFORCERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_LSBFORCERX, self).__init__(register,
            'LSBFORCERX', 'SYNTH_S.DSMCTRLRX.LSBFORCERX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_DEMMODERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_DEMMODERX, self).__init__(register,
            'DEMMODERX', 'SYNTH_S.DSMCTRLRX.DEMMODERX', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_REQORDERRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_REQORDERRX, self).__init__(register,
            'REQORDERRX', 'SYNTH_S.DSMCTRLRX.REQORDERRX', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_PHISELRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_PHISELRX, self).__init__(register,
            'PHISELRX', 'SYNTH_S.DSMCTRLRX.PHISELRX', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_DITHERDACTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_DITHERDACTX, self).__init__(register,
            'DITHERDACTX', 'SYNTH_S.DSMCTRLTX.DITHERDACTX', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_LSBFORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_LSBFORCETX, self).__init__(register,
            'LSBFORCETX', 'SYNTH_S.DSMCTRLTX.LSBFORCETX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_DEMMODETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_DEMMODETX, self).__init__(register,
            'DEMMODETX', 'SYNTH_S.DSMCTRLTX.DEMMODETX', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_REQORDERTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_REQORDERTX, self).__init__(register,
            'REQORDERTX', 'SYNTH_S.DSMCTRLTX.REQORDERTX', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_PHISELTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_PHISELTX, self).__init__(register,
            'PHISELTX', 'SYNTH_S.DSMCTRLTX.PHISELTX', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_HOPPING_HOPPINGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_HOPPING_HOPPINGEN, self).__init__(register,
            'HOPPINGEN', 'SYNTH_S.HOPPING.HOPPINGEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_HOPPING_HCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_HOPPING_HCAP, self).__init__(register,
            'HCAP', 'SYNTH_S.HOPPING.HCAP', 'read-write',
            u"",
            1, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_HOPPING_HOPLPFBWGEARSLOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_HOPPING_HOPLPFBWGEARSLOT, self).__init__(register,
            'HOPLPFBWGEARSLOT', 'SYNTH_S.HOPPING.HOPLPFBWGEARSLOT', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_HOPPING_HOPHCAPDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_HOPPING_HOPHCAPDELAY, self).__init__(register,
            'HOPHCAPDELAY', 'SYNTH_S.HOPPING.HOPHCAPDELAY', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_HOPPING_HCAPRETIMESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_HOPPING_HCAPRETIMESEL, self).__init__(register,
            'HCAPRETIMESEL', 'SYNTH_S.HOPPING.HCAPRETIMESEL', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_HOPPING_HCAPOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_HOPPING_HCAPOVERRIDEEN, self).__init__(register,
            'HCAPOVERRIDEEN', 'SYNTH_S.HOPPING.HCAPOVERRIDEEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_HOPPING_HCAPMANLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_HOPPING_HCAPMANLOAD, self).__init__(register,
            'HCAPMANLOAD', 'SYNTH_S.HOPPING.HCAPMANLOAD', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_HOPPING_HCAPRETIMEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_HOPPING_HCAPRETIMEEN, self).__init__(register,
            'HCAPRETIMEEN', 'SYNTH_S.HOPPING.HCAPRETIMEEN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_COMPANION_COMPANION0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_COMPANION_COMPANION0, self).__init__(register,
            'COMPANION0', 'SYNTH_S.COMPANION.COMPANION0', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_COMPANION_COMPANION1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_COMPANION_COMPANION1, self).__init__(register,
            'COMPANION1', 'SYNTH_S.COMPANION.COMPANION1', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_COMPANION_COMPANION2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_COMPANION_COMPANION2, self).__init__(register,
            'COMPANION2', 'SYNTH_S.COMPANION.COMPANION2', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_COMPANION_COMPANION3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_COMPANION_COMPANION3, self).__init__(register,
            'COMPANION3', 'SYNTH_S.COMPANION.COMPANION3', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_COMPANION_COMPANION4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_COMPANION_COMPANION4, self).__init__(register,
            'COMPANION4', 'SYNTH_S.COMPANION.COMPANION4', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_COMPANION_COMPANION5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_COMPANION_COMPANION5, self).__init__(register,
            'COMPANION5', 'SYNTH_S.COMPANION.COMPANION5', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_COMPANION_COMPANION6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_COMPANION_COMPANION6, self).__init__(register,
            'COMPANION6', 'SYNTH_S.COMPANION.COMPANION6', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_COMPANION_COMPANION7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_COMPANION_COMPANION7, self).__init__(register,
            'COMPANION7', 'SYNTH_S.COMPANION.COMPANION7', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE6, self).__init__(register,
            'NUMCYCLE6', 'SYNTH_S.FCALCTRL.NUMCYCLE6', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE7, self).__init__(register,
            'NUMCYCLE7', 'SYNTH_S.FCALCTRL.NUMCYCLE7', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE8, self).__init__(register,
            'NUMCYCLE8', 'SYNTH_S.FCALCTRL.NUMCYCLE8', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE9, self).__init__(register,
            'NUMCYCLE9', 'SYNTH_S.FCALCTRL.NUMCYCLE9', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALCTRL_NUMCYCLE10, self).__init__(register,
            'NUMCYCLE10', 'SYNTH_S.FCALCTRL.NUMCYCLE10', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALCTRL_STEPWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALCTRL_STEPWAIT, self).__init__(register,
            'STEPWAIT', 'SYNTH_S.FCALCTRL.STEPWAIT', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALCTRL_FCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALCTRL_FCALMODE, self).__init__(register,
            'FCALMODE', 'SYNTH_S.FCALCTRL.FCALMODE', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT1, self).__init__(register,
            'STEPWAIT1', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT1', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT2, self).__init__(register,
            'STEPWAIT2', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT2', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT3, self).__init__(register,
            'STEPWAIT3', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT3', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT4, self).__init__(register,
            'STEPWAIT4', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT4', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT5, self).__init__(register,
            'STEPWAIT5', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT5', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT6, self).__init__(register,
            'STEPWAIT6', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT6', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT7, self).__init__(register,
            'STEPWAIT7', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT7', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT8, self).__init__(register,
            'STEPWAIT8', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT8', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT9, self).__init__(register,
            'STEPWAIT9', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT9', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_FCALSTEPWAIT_STEPWAIT10, self).__init__(register,
            'STEPWAIT10', 'SYNTH_S.FCALSTEPWAIT.STEPWAIT10', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True



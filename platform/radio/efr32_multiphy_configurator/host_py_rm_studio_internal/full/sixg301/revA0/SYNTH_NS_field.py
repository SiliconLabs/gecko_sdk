
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_SYNTH_NS_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'SYNTH_NS.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_EN_EN, self).__init__(register,
            'EN', 'SYNTH_NS.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IF_LOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IF_LOCKED, self).__init__(register,
            'LOCKED', 'SYNTH_NS.IF.LOCKED', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IF_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IF_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'SYNTH_NS.IF.UNLOCKED', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IF_SYRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IF_SYRDY, self).__init__(register,
            'SYRDY', 'SYNTH_NS.IF.SYRDY', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IF_VCOHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IF_VCOHIGH, self).__init__(register,
            'VCOHIGH', 'SYNTH_NS.IF.VCOHIGH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IF_VCOLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IF_VCOLOW, self).__init__(register,
            'VCOLOW', 'SYNTH_NS.IF.VCOLOW', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IF_LOCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IF_LOCNTDONE, self).__init__(register,
            'LOCNTDONE', 'SYNTH_NS.IF.LOCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IF_FCALDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IF_FCALDONE, self).__init__(register,
            'FCALDONE', 'SYNTH_NS.IF.FCALDONE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IEN_LOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IEN_LOCKED, self).__init__(register,
            'LOCKED', 'SYNTH_NS.IEN.LOCKED', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IEN_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IEN_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'SYNTH_NS.IEN.UNLOCKED', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IEN_SYRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IEN_SYRDY, self).__init__(register,
            'SYRDY', 'SYNTH_NS.IEN.SYRDY', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IEN_VCOHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IEN_VCOHIGH, self).__init__(register,
            'VCOHIGH', 'SYNTH_NS.IEN.VCOHIGH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IEN_VCOLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IEN_VCOLOW, self).__init__(register,
            'VCOLOW', 'SYNTH_NS.IEN.VCOLOW', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IEN_LOCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IEN_LOCNTDONE, self).__init__(register,
            'LOCNTDONE', 'SYNTH_NS.IEN.LOCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IEN_FCALDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IEN_FCALDONE, self).__init__(register,
            'FCALDONE', 'SYNTH_NS.IEN.FCALDONE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIF_LOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIF_LOCKED, self).__init__(register,
            'LOCKED', 'SYNTH_NS.SEQIF.LOCKED', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIF_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIF_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'SYNTH_NS.SEQIF.UNLOCKED', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIF_SYRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIF_SYRDY, self).__init__(register,
            'SYRDY', 'SYNTH_NS.SEQIF.SYRDY', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIF_VCOHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIF_VCOHIGH, self).__init__(register,
            'VCOHIGH', 'SYNTH_NS.SEQIF.VCOHIGH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIF_VCOLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIF_VCOLOW, self).__init__(register,
            'VCOLOW', 'SYNTH_NS.SEQIF.VCOLOW', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIF_LOCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIF_LOCNTDONE, self).__init__(register,
            'LOCNTDONE', 'SYNTH_NS.SEQIF.LOCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIF_FCALDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIF_FCALDONE, self).__init__(register,
            'FCALDONE', 'SYNTH_NS.SEQIF.FCALDONE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIEN_LOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIEN_LOCKED, self).__init__(register,
            'LOCKED', 'SYNTH_NS.SEQIEN.LOCKED', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIEN_UNLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIEN_UNLOCKED, self).__init__(register,
            'UNLOCKED', 'SYNTH_NS.SEQIEN.UNLOCKED', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIEN_SYRDY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIEN_SYRDY, self).__init__(register,
            'SYRDY', 'SYNTH_NS.SEQIEN.SYRDY', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIEN_VCOHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIEN_VCOHIGH, self).__init__(register,
            'VCOHIGH', 'SYNTH_NS.SEQIEN.VCOHIGH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIEN_VCOLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIEN_VCOLOW, self).__init__(register,
            'VCOLOW', 'SYNTH_NS.SEQIEN.VCOLOW', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIEN_LOCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIEN_LOCNTDONE, self).__init__(register,
            'LOCNTDONE', 'SYNTH_NS.SEQIEN.LOCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_SEQIEN_FCALDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_SEQIEN_FCALDONE, self).__init__(register,
            'FCALDONE', 'SYNTH_NS.SEQIEN.FCALDONE', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_STATUS_INLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_STATUS_INLOCK, self).__init__(register,
            'INLOCK', 'SYNTH_NS.STATUS.INLOCK', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_STATUS_IFFREQEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_STATUS_IFFREQEN, self).__init__(register,
            'IFFREQEN', 'SYNTH_NS.STATUS.IFFREQEN', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_STATUS_SYNTHREADY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_STATUS_SYNTHREADY, self).__init__(register,
            'SYNTHREADY', 'SYNTH_NS.STATUS.SYNTHREADY', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_STATUS_VCOFREQACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_STATUS_VCOFREQACTIVE, self).__init__(register,
            'VCOFREQACTIVE', 'SYNTH_NS.STATUS.VCOFREQACTIVE', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_STATUS_LMSSTATUS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_STATUS_LMSSTATUS, self).__init__(register,
            'LMSSTATUS', 'SYNTH_NS.STATUS.LMSSTATUS', 'read-only',
            u"",
            4, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CMD_SYNTHSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CMD_SYNTHSTART, self).__init__(register,
            'SYNTHSTART', 'SYNTH_NS.CMD.SYNTHSTART', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CMD_SYNTHSTOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CMD_SYNTHSTOP, self).__init__(register,
            'SYNTHSTOP', 'SYNTH_NS.CMD.SYNTHSTOP', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CMD_ENABLEIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CMD_ENABLEIF, self).__init__(register,
            'ENABLEIF', 'SYNTH_NS.CMD.ENABLEIF', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CMD_DISABLEIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CMD_DISABLEIF, self).__init__(register,
            'DISABLEIF', 'SYNTH_NS.CMD.DISABLEIF', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CMD_CAPCALSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CMD_CAPCALSTART, self).__init__(register,
            'CAPCALSTART', 'SYNTH_NS.CMD.CAPCALSTART', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CMD_VCOADDCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CMD_VCOADDCAP, self).__init__(register,
            'VCOADDCAP', 'SYNTH_NS.CMD.VCOADDCAP', 'write-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CMD_VCOSUBCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CMD_VCOSUBCAP, self).__init__(register,
            'VCOSUBCAP', 'SYNTH_NS.CMD.VCOSUBCAP', 'write-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_LOCKTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_LOCKTHRESHOLD, self).__init__(register,
            'LOCKTHRESHOLD', 'SYNTH_NS.CTRL.LOCKTHRESHOLD', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_PRSMUX0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_PRSMUX0, self).__init__(register,
            'PRSMUX0', 'SYNTH_NS.CTRL.PRSMUX0', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_PRSMUX1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_PRSMUX1, self).__init__(register,
            'PRSMUX1', 'SYNTH_NS.CTRL.PRSMUX1', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_DISCLKSYNTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_DISCLKSYNTH, self).__init__(register,
            'DISCLKSYNTH', 'SYNTH_NS.CTRL.DISCLKSYNTH', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_INVCLKSYNTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_INVCLKSYNTH, self).__init__(register,
            'INVCLKSYNTH', 'SYNTH_NS.CTRL.INVCLKSYNTH', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_INTEGERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_INTEGERMODE, self).__init__(register,
            'INTEGERMODE', 'SYNTH_NS.CTRL.INTEGERMODE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_MMDRSTNOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_MMDRSTNOVERRIDEEN, self).__init__(register,
            'MMDRSTNOVERRIDEEN', 'SYNTH_NS.CTRL.MMDRSTNOVERRIDEEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_MMDMANRSTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_MMDMANRSTN, self).__init__(register,
            'MMDMANRSTN', 'SYNTH_NS.CTRL.MMDMANRSTN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_RDGLMS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_RDGLMS, self).__init__(register,
            'RDGLMS', 'SYNTH_NS.CTRL.RDGLMS', 'write-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_RDPLMS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_RDPLMS, self).__init__(register,
            'RDPLMS', 'SYNTH_NS.CTRL.RDPLMS', 'write-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_BOUNDARYCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_BOUNDARYCNT, self).__init__(register,
            'BOUNDARYCNT', 'SYNTH_NS.CTRL.BOUNDARYCNT', 'read-write',
            u"",
            16, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_OWREN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_OWREN, self).__init__(register,
            'OWREN', 'SYNTH_NS.CTRL.OWREN', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CTRL_QNCTONEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CTRL_QNCTONEEN, self).__init__(register,
            'QNCTONEEN', 'SYNTH_NS.CTRL.QNCTONEEN', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCDACCTRL_VCDACVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCDACCTRL_VCDACVAL, self).__init__(register,
            'VCDACVAL', 'SYNTH_NS.VCDACCTRL.VCDACVAL', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCDACCTRL_VCDACEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCDACCTRL_VCDACEN, self).__init__(register,
            'VCDACEN', 'SYNTH_NS.VCDACCTRL.VCDACEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FREQ_FREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FREQ_FREQ, self).__init__(register,
            'FREQ', 'SYNTH_NS.FREQ.FREQ', 'read-write',
            u"",
            0, 28)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IFFREQ_IFFREQ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IFFREQ_IFFREQ, self).__init__(register,
            'IFFREQ', 'SYNTH_NS.IFFREQ.IFFREQ', 'read-write',
            u"",
            0, 20)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_IFFREQ_LOSIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_IFFREQ_LOSIDE, self).__init__(register,
            'LOSIDE', 'SYNTH_NS.IFFREQ.LOSIDE', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DIVCTRL_LODIVFREQCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DIVCTRL_LODIVFREQCTRL, self).__init__(register,
            'LODIVFREQCTRL', 'SYNTH_NS.DIVCTRL.LODIVFREQCTRL', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CHCTRL_CHNO(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CHCTRL_CHNO, self).__init__(register,
            'CHNO', 'SYNTH_NS.CHCTRL.CHNO', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CHSP_CHSP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CHSP_CHSP, self).__init__(register,
            'CHSP', 'SYNTH_NS.CHSP.CHSP', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_CALOFFSET_CALOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_CALOFFSET_CALOFFSET, self).__init__(register,
            'CALOFFSET', 'SYNTH_NS.CALOFFSET.CALOFFSET', 'read-write',
            u"",
            0, 15)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCOTUNING_VCOTUNING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCOTUNING_VCOTUNING, self).__init__(register,
            'VCOTUNING', 'SYNTH_NS.VCOTUNING.VCOTUNING', 'read-write',
            u"",
            0, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCOTUNING_VCAPSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCOTUNING_VCAPSEL, self).__init__(register,
            'VCAPSEL', 'SYNTH_NS.VCOTUNING.VCAPSEL', 'read-write',
            u"",
            11, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_MODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_MODE, self).__init__(register,
            'MODE', 'SYNTH_NS.VCORANGE.MODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_SWITCHMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_SWITCHMODE, self).__init__(register,
            'SWITCHMODE', 'SYNTH_NS.VCORANGE.SWITCHMODE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_HIGHTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_HIGHTHRESH, self).__init__(register,
            'HIGHTHRESH', 'SYNTH_NS.VCORANGE.HIGHTHRESH', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_LOWTHRESH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_LOWTHRESH, self).__init__(register,
            'LOWTHRESH', 'SYNTH_NS.VCORANGE.LOWTHRESH', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_OVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_OVERRIDEEN, self).__init__(register,
            'OVERRIDEEN', 'SYNTH_NS.VCORANGE.OVERRIDEEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_DATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_DATA, self).__init__(register,
            'DATA', 'SYNTH_NS.VCORANGE.DATA', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_LOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_LOAD, self).__init__(register,
            'LOAD', 'SYNTH_NS.VCORANGE.LOAD', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_RAMPEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_RAMPEN, self).__init__(register,
            'RAMPEN', 'SYNTH_NS.VCORANGE.RAMPEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_CMPENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_CMPENABLE, self).__init__(register,
            'CMPENABLE', 'SYNTH_NS.VCORANGE.CMPENABLE', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_CMPRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_CMPRESET, self).__init__(register,
            'CMPRESET', 'SYNTH_NS.VCORANGE.CMPRESET', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_RAMPRATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_RAMPRATE, self).__init__(register,
            'RAMPRATE', 'SYNTH_NS.VCORANGE.RAMPRATE', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_THROUGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_THROUGH, self).__init__(register,
            'THROUGH', 'SYNTH_NS.VCORANGE.THROUGH', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCORANGE_INVCOMPDIR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCORANGE_INVCOMPDIR, self).__init__(register,
            'INVCOMPDIR', 'SYNTH_NS.VCORANGE.INVCOMPDIR', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCOGAIN_VCOKVCOARSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCOGAIN_VCOKVCOARSE, self).__init__(register,
            'VCOKVCOARSE', 'SYNTH_NS.VCOGAIN.VCOKVCOARSE', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCOGAIN_VCOKVFINE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCOGAIN_VCOKVFINE, self).__init__(register,
            'VCOKVFINE', 'SYNTH_NS.VCOGAIN.VCOKVFINE', 'read-write',
            u"",
            4, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCCTRL_QNCMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCCTRL_QNCMODE, self).__init__(register,
            'QNCMODE', 'SYNTH_NS.QNCCTRL.QNCMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCCTRL_ENABLEDQNCTIME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCCTRL_ENABLEDQNCTIME, self).__init__(register,
            'ENABLEDQNCTIME', 'SYNTH_NS.QNCCTRL.ENABLEDQNCTIME', 'read-write',
            u"",
            2, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCCTRL_QNCOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCCTRL_QNCOFFSET, self).__init__(register,
            'QNCOFFSET', 'SYNTH_NS.QNCCTRL.QNCOFFSET', 'read-write',
            u"",
            6, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCCTRL_FORCEQNCCLK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCCTRL_FORCEQNCCLK, self).__init__(register,
            'FORCEQNCCLK', 'SYNTH_NS.QNCCTRL.FORCEQNCCLK', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCCTRL_TDCSIGNDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCCTRL_TDCSIGNDEL, self).__init__(register,
            'TDCSIGNDEL', 'SYNTH_NS.QNCCTRL.TDCSIGNDEL', 'read-write',
            u"",
            26, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACVAL, self).__init__(register,
            'QNCDACVAL', 'SYNTH_NS.QNCDACCTRL.QNCDACVAL', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACOVERRIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACOVERRIDE, self).__init__(register,
            'QNCDACOVERRIDE', 'SYNTH_NS.QNCDACCTRL.QNCDACOVERRIDE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACINIT, self).__init__(register,
            'QNCDACINIT', 'SYNTH_NS.QNCDACCTRL.QNCDACINIT', 'read-write',
            u"",
            10, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_QNCDACCTRL_QNCTONEAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_QNCDACCTRL_QNCTONEAMP, self).__init__(register,
            'QNCTONEAMP', 'SYNTH_NS.QNCDACCTRL.QNCTONEAMP', 'read-write',
            u"",
            23, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCOFRCCAL_TIMEOUTCOUNTMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCOFRCCAL_TIMEOUTCOUNTMAX, self).__init__(register,
            'TIMEOUTCOUNTMAX', 'SYNTH_NS.VCOFRCCAL.TIMEOUTCOUNTMAX', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_VCOFRCCAL_TIMEOUTCOUNTRESTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_VCOFRCCAL_TIMEOUTCOUNTRESTART, self).__init__(register,
            'TIMEOUTCOUNTRESTART', 'SYNTH_NS.VCOFRCCAL.TIMEOUTCOUNTRESTART', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_ENABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_ENABLE, self).__init__(register,
            'ENABLE', 'SYNTH_NS.LOCNTCTRL.ENABLE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_CLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_CLEAR, self).__init__(register,
            'CLEAR', 'SYNTH_NS.LOCNTCTRL.CLEAR', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_RUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_RUN, self).__init__(register,
            'RUN', 'SYNTH_NS.LOCNTCTRL.RUN', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_READ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_READ, self).__init__(register,
            'READ', 'SYNTH_NS.LOCNTCTRL.READ', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTOVERRIDEEN, self).__init__(register,
            'LOCNTOVERRIDEEN', 'SYNTH_NS.LOCNTCTRL.LOCNTOVERRIDEEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTMANCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTMANCLEAR, self).__init__(register,
            'LOCNTMANCLEAR', 'SYNTH_NS.LOCNTCTRL.LOCNTMANCLEAR', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTMANRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTMANRUN, self).__init__(register,
            'LOCNTMANRUN', 'SYNTH_NS.LOCNTCTRL.LOCNTMANRUN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_FCALRUNCLKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_FCALRUNCLKEN, self).__init__(register,
            'FCALRUNCLKEN', 'SYNTH_NS.LOCNTCTRL.FCALRUNCLKEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE, self).__init__(register,
            'NUMCYCLE', 'SYNTH_NS.LOCNTCTRL.NUMCYCLE', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE1, self).__init__(register,
            'NUMCYCLE1', 'SYNTH_NS.LOCNTCTRL.NUMCYCLE1', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE2, self).__init__(register,
            'NUMCYCLE2', 'SYNTH_NS.LOCNTCTRL.NUMCYCLE2', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE3, self).__init__(register,
            'NUMCYCLE3', 'SYNTH_NS.LOCNTCTRL.NUMCYCLE3', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE4, self).__init__(register,
            'NUMCYCLE4', 'SYNTH_NS.LOCNTCTRL.NUMCYCLE4', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE5, self).__init__(register,
            'NUMCYCLE5', 'SYNTH_NS.LOCNTCTRL.NUMCYCLE5', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTSTATUS_LOCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTSTATUS_LOCOUNT, self).__init__(register,
            'LOCOUNT', 'SYNTH_NS.LOCNTSTATUS.LOCOUNT', 'read-only',
            u"",
            0, 22)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTSTATUS_BUSY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTSTATUS_BUSY, self).__init__(register,
            'BUSY', 'SYNTH_NS.LOCNTSTATUS.BUSY', 'read-only',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LOCNTTARGET_TARGET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LOCNTTARGET_TARGET, self).__init__(register,
            'TARGET', 'SYNTH_NS.LOCNTTARGET.TARGET', 'read-only',
            u"",
            0, 22)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_MMDDENOMINIT_DENOMINIT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_MMDDENOMINIT_DENOMINIT0, self).__init__(register,
            'DENOMINIT0', 'SYNTH_NS.MMDDENOMINIT.DENOMINIT0', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_MMDDENOMINIT_DENOMINIT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_MMDDENOMINIT_DENOMINIT1, self).__init__(register,
            'DENOMINIT1', 'SYNTH_NS.MMDDENOMINIT.DENOMINIT1', 'read-write',
            u"",
            9, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_MMDDENOMINIT_MMDXOJINTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_MMDDENOMINIT_MMDXOJINTN, self).__init__(register,
            'MMDXOJINTN', 'SYNTH_NS.MMDDENOMINIT.MMDXOJINTN', 'read-write',
            u"",
            18, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_GLMS_GLMSENABLEDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_GLMS_GLMSENABLEDELAY, self).__init__(register,
            'GLMSENABLEDELAY', 'SYNTH_NS.GLMS.GLMSENABLEDELAY', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_GLMS_GLMSGEARSLOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_GLMS_GLMSGEARSLOT, self).__init__(register,
            'GLMSGEARSLOT', 'SYNTH_NS.GLMS.GLMSGEARSLOT', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_GLMS_GLMSGEAR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_GLMS_GLMSGEAR0, self).__init__(register,
            'GLMSGEAR0', 'SYNTH_NS.GLMS.GLMSGEAR0', 'read-write',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_GLMS_GLMSGEAR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_GLMS_GLMSGEAR1, self).__init__(register,
            'GLMSGEAR1', 'SYNTH_NS.GLMS.GLMSGEAR1', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_GLMS_GLMSGEAR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_GLMS_GLMSGEAR2, self).__init__(register,
            'GLMSGEAR2', 'SYNTH_NS.GLMS.GLMSGEAR2', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_GLMS_GLMSGEAR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_GLMS_GLMSGEAR3, self).__init__(register,
            'GLMSGEAR3', 'SYNTH_NS.GLMS.GLMSGEAR3', 'read-write',
            u"",
            21, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_GLMS_GLMSGEAR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_GLMS_GLMSGEAR4, self).__init__(register,
            'GLMSGEAR4', 'SYNTH_NS.GLMS.GLMSGEAR4', 'read-write',
            u"",
            26, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_PLMS_PLMSENABLEDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_PLMS_PLMSENABLEDELAY, self).__init__(register,
            'PLMSENABLEDELAY', 'SYNTH_NS.PLMS.PLMSENABLEDELAY', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_PLMS_PLMSGEARSLOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_PLMS_PLMSGEARSLOT, self).__init__(register,
            'PLMSGEARSLOT', 'SYNTH_NS.PLMS.PLMSGEARSLOT', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_PLMS_PLMSGEAR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_PLMS_PLMSGEAR0, self).__init__(register,
            'PLMSGEAR0', 'SYNTH_NS.PLMS.PLMSGEAR0', 'read-write',
            u"",
            6, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_PLMS_PLMSGEAR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_PLMS_PLMSGEAR1, self).__init__(register,
            'PLMSGEAR1', 'SYNTH_NS.PLMS.PLMSGEAR1', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_PLMS_PLMSGEAR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_PLMS_PLMSGEAR2, self).__init__(register,
            'PLMSGEAR2', 'SYNTH_NS.PLMS.PLMSGEAR2', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_PLMS_PLMSGEAR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_PLMS_PLMSGEAR3, self).__init__(register,
            'PLMSGEAR3', 'SYNTH_NS.PLMS.PLMSGEAR3', 'read-write',
            u"",
            21, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_PLMS_PLMSGEAR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_PLMS_PLMSGEAR4, self).__init__(register,
            'PLMSGEAR4', 'SYNTH_NS.PLMS.PLMSGEAR4', 'read-write',
            u"",
            26, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LMSOVERRIDE_GLMSOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LMSOVERRIDE_GLMSOVERRIDEEN, self).__init__(register,
            'GLMSOVERRIDEEN', 'SYNTH_NS.LMSOVERRIDE.GLMSOVERRIDEEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LMSOVERRIDE_GLMSOVERRIDEVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LMSOVERRIDE_GLMSOVERRIDEVAL, self).__init__(register,
            'GLMSOVERRIDEVAL', 'SYNTH_NS.LMSOVERRIDE.GLMSOVERRIDEVAL', 'read-write',
            u"",
            1, 13)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LMSOVERRIDE_PLMSOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LMSOVERRIDE_PLMSOVERRIDEEN, self).__init__(register,
            'PLMSOVERRIDEEN', 'SYNTH_NS.LMSOVERRIDE.PLMSOVERRIDEEN', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_LMSOVERRIDE_PLMSOVERRIDEVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_LMSOVERRIDE_PLMSOVERRIDEVAL, self).__init__(register,
            'PLMSOVERRIDEVAL', 'SYNTH_NS.LMSOVERRIDE.PLMSOVERRIDEVAL', 'read-write',
            u"",
            15, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR2, self).__init__(register,
            'TXLOCKLPFBWGEAR2', 'SYNTH_NS.DLFCTRLTX.TXLOCKLPFBWGEAR2', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR3, self).__init__(register,
            'TXLOCKLPFBWGEAR3', 'SYNTH_NS.DLFCTRLTX.TXLOCKLPFBWGEAR3', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR4, self).__init__(register,
            'TXLOCKLPFBWGEAR4', 'SYNTH_NS.DLFCTRLTX.TXLOCKLPFBWGEAR4', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR5, self).__init__(register,
            'TXLOCKLPFBWGEAR5', 'SYNTH_NS.DLFCTRLTX.TXLOCKLPFBWGEAR5', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR6, self).__init__(register,
            'TXLOCKLPFBWGEAR6', 'SYNTH_NS.DLFCTRLTX.TXLOCKLPFBWGEAR6', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR7, self).__init__(register,
            'TXLOCKLPFBWGEAR7', 'SYNTH_NS.DLFCTRLTX.TXLOCKLPFBWGEAR7', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR8, self).__init__(register,
            'TXLOCKLPFBWGEAR8', 'SYNTH_NS.DLFCTRLTX.TXLOCKLPFBWGEAR8', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR9, self).__init__(register,
            'TXLOCKLPFBWGEAR9', 'SYNTH_NS.DLFCTRLTX.TXLOCKLPFBWGEAR9', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR2, self).__init__(register,
            'RXLOCKLPFBWGEAR2', 'SYNTH_NS.DLFCTRLRX.RXLOCKLPFBWGEAR2', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR3, self).__init__(register,
            'RXLOCKLPFBWGEAR3', 'SYNTH_NS.DLFCTRLRX.RXLOCKLPFBWGEAR3', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR4, self).__init__(register,
            'RXLOCKLPFBWGEAR4', 'SYNTH_NS.DLFCTRLRX.RXLOCKLPFBWGEAR4', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR5, self).__init__(register,
            'RXLOCKLPFBWGEAR5', 'SYNTH_NS.DLFCTRLRX.RXLOCKLPFBWGEAR5', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR6, self).__init__(register,
            'RXLOCKLPFBWGEAR6', 'SYNTH_NS.DLFCTRLRX.RXLOCKLPFBWGEAR6', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR7, self).__init__(register,
            'RXLOCKLPFBWGEAR7', 'SYNTH_NS.DLFCTRLRX.RXLOCKLPFBWGEAR7', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR8, self).__init__(register,
            'RXLOCKLPFBWGEAR8', 'SYNTH_NS.DLFCTRLRX.RXLOCKLPFBWGEAR8', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR9, self).__init__(register,
            'RXLOCKLPFBWGEAR9', 'SYNTH_NS.DLFCTRLRX.RXLOCKLPFBWGEAR9', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEAR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEAR0, self).__init__(register,
            'LOCKLPFBWGEAR0', 'SYNTH_NS.DLFCTRL.LOCKLPFBWGEAR0', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEAR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEAR1, self).__init__(register,
            'LOCKLPFBWGEAR1', 'SYNTH_NS.DLFCTRL.LOCKLPFBWGEAR1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEARSLOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEARSLOT, self).__init__(register,
            'LOCKLPFBWGEARSLOT', 'SYNTH_NS.DLFCTRL.LOCKLPFBWGEARSLOT', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_LPFBWLOADDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_LPFBWLOADDEL, self).__init__(register,
            'LPFBWLOADDEL', 'SYNTH_NS.DLFCTRL.LPFBWLOADDEL', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_LPFBWFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_LPFBWFORCE, self).__init__(register,
            'LPFBWFORCE', 'SYNTH_NS.DLFCTRL.LPFBWFORCE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_LPFBWLOADMAN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_LPFBWLOADMAN, self).__init__(register,
            'LPFBWLOADMAN', 'SYNTH_NS.DLFCTRL.LPFBWLOADMAN', 'write-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_LPFBWDURINGHOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_LPFBWDURINGHOP, self).__init__(register,
            'LPFBWDURINGHOP', 'SYNTH_NS.DLFCTRL.LPFBWDURINGHOP', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_LPFBWAFTERHOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_LPFBWAFTERHOP, self).__init__(register,
            'LPFBWAFTERHOP', 'SYNTH_NS.DLFCTRL.LPFBWAFTERHOP', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFCTRL_DLFADDRRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFCTRL_DLFADDRRST, self).__init__(register,
            'DLFADDRRST', 'SYNTH_NS.DLFCTRL.DLFADDRRST', 'write-only',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFKF_KF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFKF_KF, self).__init__(register,
            'KF', 'SYNTH_NS.DLFKF.KF', 'read-write',
            u"",
            0, 22)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFKIZP_KI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFKIZP_KI, self).__init__(register,
            'KI', 'SYNTH_NS.DLFKIZP.KI', 'read-write',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DLFKIZP_ZP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DLFKIZP_ZP, self).__init__(register,
            'ZP', 'SYNTH_NS.DLFKIZP.ZP', 'read-write',
            u"",
            19, 11)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLRX_DITHERDACRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLRX_DITHERDACRX, self).__init__(register,
            'DITHERDACRX', 'SYNTH_NS.DSMCTRLRX.DITHERDACRX', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLRX_LSBFORCERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLRX_LSBFORCERX, self).__init__(register,
            'LSBFORCERX', 'SYNTH_NS.DSMCTRLRX.LSBFORCERX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLRX_DEMMODERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLRX_DEMMODERX, self).__init__(register,
            'DEMMODERX', 'SYNTH_NS.DSMCTRLRX.DEMMODERX', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLRX_REQORDERRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLRX_REQORDERRX, self).__init__(register,
            'REQORDERRX', 'SYNTH_NS.DSMCTRLRX.REQORDERRX', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLRX_PHISELRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLRX_PHISELRX, self).__init__(register,
            'PHISELRX', 'SYNTH_NS.DSMCTRLRX.PHISELRX', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLTX_DITHERDACTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLTX_DITHERDACTX, self).__init__(register,
            'DITHERDACTX', 'SYNTH_NS.DSMCTRLTX.DITHERDACTX', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLTX_LSBFORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLTX_LSBFORCETX, self).__init__(register,
            'LSBFORCETX', 'SYNTH_NS.DSMCTRLTX.LSBFORCETX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLTX_DEMMODETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLTX_DEMMODETX, self).__init__(register,
            'DEMMODETX', 'SYNTH_NS.DSMCTRLTX.DEMMODETX', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLTX_REQORDERTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLTX_REQORDERTX, self).__init__(register,
            'REQORDERTX', 'SYNTH_NS.DSMCTRLTX.REQORDERTX', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_DSMCTRLTX_PHISELTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_DSMCTRLTX_PHISELTX, self).__init__(register,
            'PHISELTX', 'SYNTH_NS.DSMCTRLTX.PHISELTX', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_HOPPING_HOPPINGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_HOPPING_HOPPINGEN, self).__init__(register,
            'HOPPINGEN', 'SYNTH_NS.HOPPING.HOPPINGEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_HOPPING_HCAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_HOPPING_HCAP, self).__init__(register,
            'HCAP', 'SYNTH_NS.HOPPING.HCAP', 'read-write',
            u"",
            1, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_HOPPING_HOPLPFBWGEARSLOT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_HOPPING_HOPLPFBWGEARSLOT, self).__init__(register,
            'HOPLPFBWGEARSLOT', 'SYNTH_NS.HOPPING.HOPLPFBWGEARSLOT', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_HOPPING_HOPHCAPDELAY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_HOPPING_HOPHCAPDELAY, self).__init__(register,
            'HOPHCAPDELAY', 'SYNTH_NS.HOPPING.HOPHCAPDELAY', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_HOPPING_HCAPRETIMESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_HOPPING_HCAPRETIMESEL, self).__init__(register,
            'HCAPRETIMESEL', 'SYNTH_NS.HOPPING.HCAPRETIMESEL', 'read-write',
            u"",
            14, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_HOPPING_HCAPOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_HOPPING_HCAPOVERRIDEEN, self).__init__(register,
            'HCAPOVERRIDEEN', 'SYNTH_NS.HOPPING.HCAPOVERRIDEEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_HOPPING_HCAPMANLOAD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_HOPPING_HCAPMANLOAD, self).__init__(register,
            'HCAPMANLOAD', 'SYNTH_NS.HOPPING.HCAPMANLOAD', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_HOPPING_HCAPRETIMEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_HOPPING_HCAPRETIMEEN, self).__init__(register,
            'HCAPRETIMEEN', 'SYNTH_NS.HOPPING.HCAPRETIMEEN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_COMPANION_COMPANION0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_COMPANION_COMPANION0, self).__init__(register,
            'COMPANION0', 'SYNTH_NS.COMPANION.COMPANION0', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_COMPANION_COMPANION1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_COMPANION_COMPANION1, self).__init__(register,
            'COMPANION1', 'SYNTH_NS.COMPANION.COMPANION1', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_COMPANION_COMPANION2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_COMPANION_COMPANION2, self).__init__(register,
            'COMPANION2', 'SYNTH_NS.COMPANION.COMPANION2', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_COMPANION_COMPANION3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_COMPANION_COMPANION3, self).__init__(register,
            'COMPANION3', 'SYNTH_NS.COMPANION.COMPANION3', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_COMPANION_COMPANION4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_COMPANION_COMPANION4, self).__init__(register,
            'COMPANION4', 'SYNTH_NS.COMPANION.COMPANION4', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_COMPANION_COMPANION5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_COMPANION_COMPANION5, self).__init__(register,
            'COMPANION5', 'SYNTH_NS.COMPANION.COMPANION5', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_COMPANION_COMPANION6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_COMPANION_COMPANION6, self).__init__(register,
            'COMPANION6', 'SYNTH_NS.COMPANION.COMPANION6', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_COMPANION_COMPANION7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_COMPANION_COMPANION7, self).__init__(register,
            'COMPANION7', 'SYNTH_NS.COMPANION.COMPANION7', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE6, self).__init__(register,
            'NUMCYCLE6', 'SYNTH_NS.FCALCTRL.NUMCYCLE6', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE7, self).__init__(register,
            'NUMCYCLE7', 'SYNTH_NS.FCALCTRL.NUMCYCLE7', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE8, self).__init__(register,
            'NUMCYCLE8', 'SYNTH_NS.FCALCTRL.NUMCYCLE8', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE9, self).__init__(register,
            'NUMCYCLE9', 'SYNTH_NS.FCALCTRL.NUMCYCLE9', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE10, self).__init__(register,
            'NUMCYCLE10', 'SYNTH_NS.FCALCTRL.NUMCYCLE10', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALCTRL_STEPWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALCTRL_STEPWAIT, self).__init__(register,
            'STEPWAIT', 'SYNTH_NS.FCALCTRL.STEPWAIT', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALCTRL_FCALMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALCTRL_FCALMODE, self).__init__(register,
            'FCALMODE', 'SYNTH_NS.FCALCTRL.FCALMODE', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT1, self).__init__(register,
            'STEPWAIT1', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT1', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT2, self).__init__(register,
            'STEPWAIT2', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT2', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT3, self).__init__(register,
            'STEPWAIT3', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT3', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT4, self).__init__(register,
            'STEPWAIT4', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT4', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT5, self).__init__(register,
            'STEPWAIT5', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT5', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT6, self).__init__(register,
            'STEPWAIT6', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT6', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT7, self).__init__(register,
            'STEPWAIT7', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT7', 'read-write',
            u"",
            18, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT8, self).__init__(register,
            'STEPWAIT8', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT8', 'read-write',
            u"",
            21, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT9, self).__init__(register,
            'STEPWAIT9', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT9', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT10, self).__init__(register,
            'STEPWAIT10', 'SYNTH_NS.FCALSTEPWAIT.STEPWAIT10', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True



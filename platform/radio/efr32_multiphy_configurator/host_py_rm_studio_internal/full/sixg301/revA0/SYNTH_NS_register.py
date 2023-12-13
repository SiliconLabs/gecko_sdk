
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . SYNTH_NS_field import *


class RM_Register_SYNTH_NS_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_IPVERSION, self).__init__(rmio, label,
            0xb0218000, 0x000,
            'IPVERSION', 'SYNTH_NS.IPVERSION', 'read-only',
            u"",
            0x00000002, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_SYNTH_NS_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_EN, self).__init__(rmio, label,
            0xb0218000, 0x004,
            'EN', 'SYNTH_NS.EN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_SYNTH_NS_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_IF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_IF, self).__init__(rmio, label,
            0xb0218000, 0x008,
            'IF', 'SYNTH_NS.IF', 'read-write',
            u"",
            0x00000000, 0x00000637,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOCKED = RM_Field_SYNTH_NS_IF_LOCKED(self)
        self.zz_fdict['LOCKED'] = self.LOCKED
        self.UNLOCKED = RM_Field_SYNTH_NS_IF_UNLOCKED(self)
        self.zz_fdict['UNLOCKED'] = self.UNLOCKED
        self.SYRDY = RM_Field_SYNTH_NS_IF_SYRDY(self)
        self.zz_fdict['SYRDY'] = self.SYRDY
        self.VCOHIGH = RM_Field_SYNTH_NS_IF_VCOHIGH(self)
        self.zz_fdict['VCOHIGH'] = self.VCOHIGH
        self.VCOLOW = RM_Field_SYNTH_NS_IF_VCOLOW(self)
        self.zz_fdict['VCOLOW'] = self.VCOLOW
        self.LOCNTDONE = RM_Field_SYNTH_NS_IF_LOCNTDONE(self)
        self.zz_fdict['LOCNTDONE'] = self.LOCNTDONE
        self.FCALDONE = RM_Field_SYNTH_NS_IF_FCALDONE(self)
        self.zz_fdict['FCALDONE'] = self.FCALDONE
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_IEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_IEN, self).__init__(rmio, label,
            0xb0218000, 0x00C,
            'IEN', 'SYNTH_NS.IEN', 'read-write',
            u"",
            0x00000000, 0x00000637,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOCKED = RM_Field_SYNTH_NS_IEN_LOCKED(self)
        self.zz_fdict['LOCKED'] = self.LOCKED
        self.UNLOCKED = RM_Field_SYNTH_NS_IEN_UNLOCKED(self)
        self.zz_fdict['UNLOCKED'] = self.UNLOCKED
        self.SYRDY = RM_Field_SYNTH_NS_IEN_SYRDY(self)
        self.zz_fdict['SYRDY'] = self.SYRDY
        self.VCOHIGH = RM_Field_SYNTH_NS_IEN_VCOHIGH(self)
        self.zz_fdict['VCOHIGH'] = self.VCOHIGH
        self.VCOLOW = RM_Field_SYNTH_NS_IEN_VCOLOW(self)
        self.zz_fdict['VCOLOW'] = self.VCOLOW
        self.LOCNTDONE = RM_Field_SYNTH_NS_IEN_LOCNTDONE(self)
        self.zz_fdict['LOCNTDONE'] = self.LOCNTDONE
        self.FCALDONE = RM_Field_SYNTH_NS_IEN_FCALDONE(self)
        self.zz_fdict['FCALDONE'] = self.FCALDONE
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_SEQIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_SEQIF, self).__init__(rmio, label,
            0xb0218000, 0x010,
            'SEQIF', 'SYNTH_NS.SEQIF', 'read-write',
            u"",
            0x00000000, 0x00000637,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOCKED = RM_Field_SYNTH_NS_SEQIF_LOCKED(self)
        self.zz_fdict['LOCKED'] = self.LOCKED
        self.UNLOCKED = RM_Field_SYNTH_NS_SEQIF_UNLOCKED(self)
        self.zz_fdict['UNLOCKED'] = self.UNLOCKED
        self.SYRDY = RM_Field_SYNTH_NS_SEQIF_SYRDY(self)
        self.zz_fdict['SYRDY'] = self.SYRDY
        self.VCOHIGH = RM_Field_SYNTH_NS_SEQIF_VCOHIGH(self)
        self.zz_fdict['VCOHIGH'] = self.VCOHIGH
        self.VCOLOW = RM_Field_SYNTH_NS_SEQIF_VCOLOW(self)
        self.zz_fdict['VCOLOW'] = self.VCOLOW
        self.LOCNTDONE = RM_Field_SYNTH_NS_SEQIF_LOCNTDONE(self)
        self.zz_fdict['LOCNTDONE'] = self.LOCNTDONE
        self.FCALDONE = RM_Field_SYNTH_NS_SEQIF_FCALDONE(self)
        self.zz_fdict['FCALDONE'] = self.FCALDONE
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_SEQIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_SEQIEN, self).__init__(rmio, label,
            0xb0218000, 0x014,
            'SEQIEN', 'SYNTH_NS.SEQIEN', 'read-write',
            u"",
            0x00000000, 0x00000637,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOCKED = RM_Field_SYNTH_NS_SEQIEN_LOCKED(self)
        self.zz_fdict['LOCKED'] = self.LOCKED
        self.UNLOCKED = RM_Field_SYNTH_NS_SEQIEN_UNLOCKED(self)
        self.zz_fdict['UNLOCKED'] = self.UNLOCKED
        self.SYRDY = RM_Field_SYNTH_NS_SEQIEN_SYRDY(self)
        self.zz_fdict['SYRDY'] = self.SYRDY
        self.VCOHIGH = RM_Field_SYNTH_NS_SEQIEN_VCOHIGH(self)
        self.zz_fdict['VCOHIGH'] = self.VCOHIGH
        self.VCOLOW = RM_Field_SYNTH_NS_SEQIEN_VCOLOW(self)
        self.zz_fdict['VCOLOW'] = self.VCOLOW
        self.LOCNTDONE = RM_Field_SYNTH_NS_SEQIEN_LOCNTDONE(self)
        self.zz_fdict['LOCNTDONE'] = self.LOCNTDONE
        self.FCALDONE = RM_Field_SYNTH_NS_SEQIEN_FCALDONE(self)
        self.zz_fdict['FCALDONE'] = self.FCALDONE
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_STATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_STATUS, self).__init__(rmio, label,
            0xb0218000, 0x018,
            'STATUS', 'SYNTH_NS.STATUS', 'read-only',
            u"",
            0x00000000, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INLOCK = RM_Field_SYNTH_NS_STATUS_INLOCK(self)
        self.zz_fdict['INLOCK'] = self.INLOCK
        self.IFFREQEN = RM_Field_SYNTH_NS_STATUS_IFFREQEN(self)
        self.zz_fdict['IFFREQEN'] = self.IFFREQEN
        self.SYNTHREADY = RM_Field_SYNTH_NS_STATUS_SYNTHREADY(self)
        self.zz_fdict['SYNTHREADY'] = self.SYNTHREADY
        self.VCOFREQACTIVE = RM_Field_SYNTH_NS_STATUS_VCOFREQACTIVE(self)
        self.zz_fdict['VCOFREQACTIVE'] = self.VCOFREQACTIVE
        self.LMSSTATUS = RM_Field_SYNTH_NS_STATUS_LMSSTATUS(self)
        self.zz_fdict['LMSSTATUS'] = self.LMSSTATUS
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_CMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_CMD, self).__init__(rmio, label,
            0xb0218000, 0x01C,
            'CMD', 'SYNTH_NS.CMD', 'write-only',
            u"",
            0x00000000, 0x0000061F,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNTHSTART = RM_Field_SYNTH_NS_CMD_SYNTHSTART(self)
        self.zz_fdict['SYNTHSTART'] = self.SYNTHSTART
        self.SYNTHSTOP = RM_Field_SYNTH_NS_CMD_SYNTHSTOP(self)
        self.zz_fdict['SYNTHSTOP'] = self.SYNTHSTOP
        self.ENABLEIF = RM_Field_SYNTH_NS_CMD_ENABLEIF(self)
        self.zz_fdict['ENABLEIF'] = self.ENABLEIF
        self.DISABLEIF = RM_Field_SYNTH_NS_CMD_DISABLEIF(self)
        self.zz_fdict['DISABLEIF'] = self.DISABLEIF
        self.CAPCALSTART = RM_Field_SYNTH_NS_CMD_CAPCALSTART(self)
        self.zz_fdict['CAPCALSTART'] = self.CAPCALSTART
        self.VCOADDCAP = RM_Field_SYNTH_NS_CMD_VCOADDCAP(self)
        self.zz_fdict['VCOADDCAP'] = self.VCOADDCAP
        self.VCOSUBCAP = RM_Field_SYNTH_NS_CMD_VCOSUBCAP(self)
        self.zz_fdict['VCOSUBCAP'] = self.VCOSUBCAP
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_CTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_CTRL, self).__init__(rmio, label,
            0xb0218000, 0x020,
            'CTRL', 'SYNTH_NS.CTRL', 'read-write',
            u"",
            0x00000003, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOCKTHRESHOLD = RM_Field_SYNTH_NS_CTRL_LOCKTHRESHOLD(self)
        self.zz_fdict['LOCKTHRESHOLD'] = self.LOCKTHRESHOLD
        self.PRSMUX0 = RM_Field_SYNTH_NS_CTRL_PRSMUX0(self)
        self.zz_fdict['PRSMUX0'] = self.PRSMUX0
        self.PRSMUX1 = RM_Field_SYNTH_NS_CTRL_PRSMUX1(self)
        self.zz_fdict['PRSMUX1'] = self.PRSMUX1
        self.DISCLKSYNTH = RM_Field_SYNTH_NS_CTRL_DISCLKSYNTH(self)
        self.zz_fdict['DISCLKSYNTH'] = self.DISCLKSYNTH
        self.INVCLKSYNTH = RM_Field_SYNTH_NS_CTRL_INVCLKSYNTH(self)
        self.zz_fdict['INVCLKSYNTH'] = self.INVCLKSYNTH
        self.INTEGERMODE = RM_Field_SYNTH_NS_CTRL_INTEGERMODE(self)
        self.zz_fdict['INTEGERMODE'] = self.INTEGERMODE
        self.MMDRSTNOVERRIDEEN = RM_Field_SYNTH_NS_CTRL_MMDRSTNOVERRIDEEN(self)
        self.zz_fdict['MMDRSTNOVERRIDEEN'] = self.MMDRSTNOVERRIDEEN
        self.MMDMANRSTN = RM_Field_SYNTH_NS_CTRL_MMDMANRSTN(self)
        self.zz_fdict['MMDMANRSTN'] = self.MMDMANRSTN
        self.RDGLMS = RM_Field_SYNTH_NS_CTRL_RDGLMS(self)
        self.zz_fdict['RDGLMS'] = self.RDGLMS
        self.RDPLMS = RM_Field_SYNTH_NS_CTRL_RDPLMS(self)
        self.zz_fdict['RDPLMS'] = self.RDPLMS
        self.BOUNDARYCNT = RM_Field_SYNTH_NS_CTRL_BOUNDARYCNT(self)
        self.zz_fdict['BOUNDARYCNT'] = self.BOUNDARYCNT
        self.OWREN = RM_Field_SYNTH_NS_CTRL_OWREN(self)
        self.zz_fdict['OWREN'] = self.OWREN
        self.QNCTONEEN = RM_Field_SYNTH_NS_CTRL_QNCTONEEN(self)
        self.zz_fdict['QNCTONEEN'] = self.QNCTONEEN
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_VCDACCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_VCDACCTRL, self).__init__(rmio, label,
            0xb0218000, 0x024,
            'VCDACCTRL', 'SYNTH_NS.VCDACCTRL', 'read-write',
            u"",
            0x00000021, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VCDACVAL = RM_Field_SYNTH_NS_VCDACCTRL_VCDACVAL(self)
        self.zz_fdict['VCDACVAL'] = self.VCDACVAL
        self.VCDACEN = RM_Field_SYNTH_NS_VCDACCTRL_VCDACEN(self)
        self.zz_fdict['VCDACEN'] = self.VCDACEN
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_FREQ(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_FREQ, self).__init__(rmio, label,
            0xb0218000, 0x028,
            'FREQ', 'SYNTH_NS.FREQ', 'read-write',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FREQ = RM_Field_SYNTH_NS_FREQ_FREQ(self)
        self.zz_fdict['FREQ'] = self.FREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_IFFREQ(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_IFFREQ, self).__init__(rmio, label,
            0xb0218000, 0x02C,
            'IFFREQ', 'SYNTH_NS.IFFREQ', 'read-write',
            u"",
            0x00000000, 0x001FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IFFREQ = RM_Field_SYNTH_NS_IFFREQ_IFFREQ(self)
        self.zz_fdict['IFFREQ'] = self.IFFREQ
        self.LOSIDE = RM_Field_SYNTH_NS_IFFREQ_LOSIDE(self)
        self.zz_fdict['LOSIDE'] = self.LOSIDE
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_DIVCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_DIVCTRL, self).__init__(rmio, label,
            0xb0218000, 0x030,
            'DIVCTRL', 'SYNTH_NS.DIVCTRL', 'read-write',
            u"",
            0x00000001, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LODIVFREQCTRL = RM_Field_SYNTH_NS_DIVCTRL_LODIVFREQCTRL(self)
        self.zz_fdict['LODIVFREQCTRL'] = self.LODIVFREQCTRL
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_CHCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_CHCTRL, self).__init__(rmio, label,
            0xb0218000, 0x034,
            'CHCTRL', 'SYNTH_NS.CHCTRL', 'read-write',
            u"",
            0x00000000, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.CHNO = RM_Field_SYNTH_NS_CHCTRL_CHNO(self)
        self.zz_fdict['CHNO'] = self.CHNO
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_CHSP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_CHSP, self).__init__(rmio, label,
            0xb0218000, 0x038,
            'CHSP', 'SYNTH_NS.CHSP', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CHSP = RM_Field_SYNTH_NS_CHSP_CHSP(self)
        self.zz_fdict['CHSP'] = self.CHSP
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_CALOFFSET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_CALOFFSET, self).__init__(rmio, label,
            0xb0218000, 0x03C,
            'CALOFFSET', 'SYNTH_NS.CALOFFSET', 'read-write',
            u"",
            0x00000000, 0x00007FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CALOFFSET = RM_Field_SYNTH_NS_CALOFFSET_CALOFFSET(self)
        self.zz_fdict['CALOFFSET'] = self.CALOFFSET
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_VCOTUNING(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_VCOTUNING, self).__init__(rmio, label,
            0xb0218000, 0x040,
            'VCOTUNING', 'SYNTH_NS.VCOTUNING', 'read-write',
            u"",
            0x00004400, 0x00007FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VCOTUNING = RM_Field_SYNTH_NS_VCOTUNING_VCOTUNING(self)
        self.zz_fdict['VCOTUNING'] = self.VCOTUNING
        self.VCAPSEL = RM_Field_SYNTH_NS_VCOTUNING_VCAPSEL(self)
        self.zz_fdict['VCAPSEL'] = self.VCAPSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_VCORANGE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_VCORANGE, self).__init__(rmio, label,
            0xb0218000, 0x044,
            'VCORANGE', 'SYNTH_NS.VCORANGE', 'read-write',
            u"",
            0x00000000, 0x000FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODE = RM_Field_SYNTH_NS_VCORANGE_MODE(self)
        self.zz_fdict['MODE'] = self.MODE
        self.SWITCHMODE = RM_Field_SYNTH_NS_VCORANGE_SWITCHMODE(self)
        self.zz_fdict['SWITCHMODE'] = self.SWITCHMODE
        self.HIGHTHRESH = RM_Field_SYNTH_NS_VCORANGE_HIGHTHRESH(self)
        self.zz_fdict['HIGHTHRESH'] = self.HIGHTHRESH
        self.LOWTHRESH = RM_Field_SYNTH_NS_VCORANGE_LOWTHRESH(self)
        self.zz_fdict['LOWTHRESH'] = self.LOWTHRESH
        self.OVERRIDEEN = RM_Field_SYNTH_NS_VCORANGE_OVERRIDEEN(self)
        self.zz_fdict['OVERRIDEEN'] = self.OVERRIDEEN
        self.DATA = RM_Field_SYNTH_NS_VCORANGE_DATA(self)
        self.zz_fdict['DATA'] = self.DATA
        self.LOAD = RM_Field_SYNTH_NS_VCORANGE_LOAD(self)
        self.zz_fdict['LOAD'] = self.LOAD
        self.RAMPEN = RM_Field_SYNTH_NS_VCORANGE_RAMPEN(self)
        self.zz_fdict['RAMPEN'] = self.RAMPEN
        self.CMPENABLE = RM_Field_SYNTH_NS_VCORANGE_CMPENABLE(self)
        self.zz_fdict['CMPENABLE'] = self.CMPENABLE
        self.CMPRESET = RM_Field_SYNTH_NS_VCORANGE_CMPRESET(self)
        self.zz_fdict['CMPRESET'] = self.CMPRESET
        self.RAMPRATE = RM_Field_SYNTH_NS_VCORANGE_RAMPRATE(self)
        self.zz_fdict['RAMPRATE'] = self.RAMPRATE
        self.THROUGH = RM_Field_SYNTH_NS_VCORANGE_THROUGH(self)
        self.zz_fdict['THROUGH'] = self.THROUGH
        self.INVCOMPDIR = RM_Field_SYNTH_NS_VCORANGE_INVCOMPDIR(self)
        self.zz_fdict['INVCOMPDIR'] = self.INVCOMPDIR
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_VCOGAIN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_VCOGAIN, self).__init__(rmio, label,
            0xb0218000, 0x048,
            'VCOGAIN', 'SYNTH_NS.VCOGAIN', 'read-write',
            u"",
            0x000001F7, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VCOKVCOARSE = RM_Field_SYNTH_NS_VCOGAIN_VCOKVCOARSE(self)
        self.zz_fdict['VCOKVCOARSE'] = self.VCOKVCOARSE
        self.VCOKVFINE = RM_Field_SYNTH_NS_VCOGAIN_VCOKVFINE(self)
        self.zz_fdict['VCOKVFINE'] = self.VCOKVFINE
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_QNCCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_QNCCTRL, self).__init__(rmio, label,
            0xb0218000, 0x04C,
            'QNCCTRL', 'SYNTH_NS.QNCCTRL', 'read-write',
            u"",
            0x04000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.QNCMODE = RM_Field_SYNTH_NS_QNCCTRL_QNCMODE(self)
        self.zz_fdict['QNCMODE'] = self.QNCMODE
        self.ENABLEDQNCTIME = RM_Field_SYNTH_NS_QNCCTRL_ENABLEDQNCTIME(self)
        self.zz_fdict['ENABLEDQNCTIME'] = self.ENABLEDQNCTIME
        self.QNCOFFSET = RM_Field_SYNTH_NS_QNCCTRL_QNCOFFSET(self)
        self.zz_fdict['QNCOFFSET'] = self.QNCOFFSET
        self.FORCEQNCCLK = RM_Field_SYNTH_NS_QNCCTRL_FORCEQNCCLK(self)
        self.zz_fdict['FORCEQNCCLK'] = self.FORCEQNCCLK
        self.TDCSIGNDEL = RM_Field_SYNTH_NS_QNCCTRL_TDCSIGNDEL(self)
        self.zz_fdict['TDCSIGNDEL'] = self.TDCSIGNDEL
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_QNCDACCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_QNCDACCTRL, self).__init__(rmio, label,
            0xb0218000, 0x050,
            'QNCDACCTRL', 'SYNTH_NS.QNCDACCTRL', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.QNCDACVAL = RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACVAL(self)
        self.zz_fdict['QNCDACVAL'] = self.QNCDACVAL
        self.QNCDACOVERRIDE = RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACOVERRIDE(self)
        self.zz_fdict['QNCDACOVERRIDE'] = self.QNCDACOVERRIDE
        self.QNCDACINIT = RM_Field_SYNTH_NS_QNCDACCTRL_QNCDACINIT(self)
        self.zz_fdict['QNCDACINIT'] = self.QNCDACINIT
        self.QNCTONEAMP = RM_Field_SYNTH_NS_QNCDACCTRL_QNCTONEAMP(self)
        self.zz_fdict['QNCTONEAMP'] = self.QNCTONEAMP
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_VCOFRCCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_VCOFRCCAL, self).__init__(rmio, label,
            0xb0218000, 0x054,
            'VCOFRCCAL', 'SYNTH_NS.VCOFRCCAL', 'read-write',
            u"",
            0x01FF0FFF, 0x3FFF3FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMEOUTCOUNTMAX = RM_Field_SYNTH_NS_VCOFRCCAL_TIMEOUTCOUNTMAX(self)
        self.zz_fdict['TIMEOUTCOUNTMAX'] = self.TIMEOUTCOUNTMAX
        self.TIMEOUTCOUNTRESTART = RM_Field_SYNTH_NS_VCOFRCCAL_TIMEOUTCOUNTRESTART(self)
        self.zz_fdict['TIMEOUTCOUNTRESTART'] = self.TIMEOUTCOUNTRESTART
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_LOCNTCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_LOCNTCTRL, self).__init__(rmio, label,
            0xb0218000, 0x058,
            'LOCNTCTRL', 'SYNTH_NS.LOCNTCTRL', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ENABLE = RM_Field_SYNTH_NS_LOCNTCTRL_ENABLE(self)
        self.zz_fdict['ENABLE'] = self.ENABLE
        self.CLEAR = RM_Field_SYNTH_NS_LOCNTCTRL_CLEAR(self)
        self.zz_fdict['CLEAR'] = self.CLEAR
        self.RUN = RM_Field_SYNTH_NS_LOCNTCTRL_RUN(self)
        self.zz_fdict['RUN'] = self.RUN
        self.READ = RM_Field_SYNTH_NS_LOCNTCTRL_READ(self)
        self.zz_fdict['READ'] = self.READ
        self.LOCNTOVERRIDEEN = RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTOVERRIDEEN(self)
        self.zz_fdict['LOCNTOVERRIDEEN'] = self.LOCNTOVERRIDEEN
        self.LOCNTMANCLEAR = RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTMANCLEAR(self)
        self.zz_fdict['LOCNTMANCLEAR'] = self.LOCNTMANCLEAR
        self.LOCNTMANRUN = RM_Field_SYNTH_NS_LOCNTCTRL_LOCNTMANRUN(self)
        self.zz_fdict['LOCNTMANRUN'] = self.LOCNTMANRUN
        self.FCALRUNCLKEN = RM_Field_SYNTH_NS_LOCNTCTRL_FCALRUNCLKEN(self)
        self.zz_fdict['FCALRUNCLKEN'] = self.FCALRUNCLKEN
        self.NUMCYCLE = RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE(self)
        self.zz_fdict['NUMCYCLE'] = self.NUMCYCLE
        self.NUMCYCLE1 = RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE1(self)
        self.zz_fdict['NUMCYCLE1'] = self.NUMCYCLE1
        self.NUMCYCLE2 = RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE2(self)
        self.zz_fdict['NUMCYCLE2'] = self.NUMCYCLE2
        self.NUMCYCLE3 = RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE3(self)
        self.zz_fdict['NUMCYCLE3'] = self.NUMCYCLE3
        self.NUMCYCLE4 = RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE4(self)
        self.zz_fdict['NUMCYCLE4'] = self.NUMCYCLE4
        self.NUMCYCLE5 = RM_Field_SYNTH_NS_LOCNTCTRL_NUMCYCLE5(self)
        self.zz_fdict['NUMCYCLE5'] = self.NUMCYCLE5
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_LOCNTSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_LOCNTSTATUS, self).__init__(rmio, label,
            0xb0218000, 0x05C,
            'LOCNTSTATUS', 'SYNTH_NS.LOCNTSTATUS', 'read-only',
            u"",
            0x00000000, 0x007FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOCOUNT = RM_Field_SYNTH_NS_LOCNTSTATUS_LOCOUNT(self)
        self.zz_fdict['LOCOUNT'] = self.LOCOUNT
        self.BUSY = RM_Field_SYNTH_NS_LOCNTSTATUS_BUSY(self)
        self.zz_fdict['BUSY'] = self.BUSY
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_LOCNTTARGET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_LOCNTTARGET, self).__init__(rmio, label,
            0xb0218000, 0x060,
            'LOCNTTARGET', 'SYNTH_NS.LOCNTTARGET', 'read-only',
            u"",
            0x00000000, 0x003FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TARGET = RM_Field_SYNTH_NS_LOCNTTARGET_TARGET(self)
        self.zz_fdict['TARGET'] = self.TARGET
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_MMDDENOMINIT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_MMDDENOMINIT, self).__init__(rmio, label,
            0xb0218000, 0x064,
            'MMDDENOMINIT', 'SYNTH_NS.MMDDENOMINIT', 'read-write',
            u"",
            0x00008040, 0x000FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DENOMINIT0 = RM_Field_SYNTH_NS_MMDDENOMINIT_DENOMINIT0(self)
        self.zz_fdict['DENOMINIT0'] = self.DENOMINIT0
        self.DENOMINIT1 = RM_Field_SYNTH_NS_MMDDENOMINIT_DENOMINIT1(self)
        self.zz_fdict['DENOMINIT1'] = self.DENOMINIT1
        self.MMDXOJINTN = RM_Field_SYNTH_NS_MMDDENOMINIT_MMDXOJINTN(self)
        self.zz_fdict['MMDXOJINTN'] = self.MMDXOJINTN
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_GLMS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_GLMS, self).__init__(rmio, label,
            0xb0218000, 0x068,
            'GLMS', 'SYNTH_NS.GLMS', 'read-write',
            u"",
            0x00000002, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.GLMSENABLEDELAY = RM_Field_SYNTH_NS_GLMS_GLMSENABLEDELAY(self)
        self.zz_fdict['GLMSENABLEDELAY'] = self.GLMSENABLEDELAY
        self.GLMSGEARSLOT = RM_Field_SYNTH_NS_GLMS_GLMSGEARSLOT(self)
        self.zz_fdict['GLMSGEARSLOT'] = self.GLMSGEARSLOT
        self.GLMSGEAR0 = RM_Field_SYNTH_NS_GLMS_GLMSGEAR0(self)
        self.zz_fdict['GLMSGEAR0'] = self.GLMSGEAR0
        self.GLMSGEAR1 = RM_Field_SYNTH_NS_GLMS_GLMSGEAR1(self)
        self.zz_fdict['GLMSGEAR1'] = self.GLMSGEAR1
        self.GLMSGEAR2 = RM_Field_SYNTH_NS_GLMS_GLMSGEAR2(self)
        self.zz_fdict['GLMSGEAR2'] = self.GLMSGEAR2
        self.GLMSGEAR3 = RM_Field_SYNTH_NS_GLMS_GLMSGEAR3(self)
        self.zz_fdict['GLMSGEAR3'] = self.GLMSGEAR3
        self.GLMSGEAR4 = RM_Field_SYNTH_NS_GLMS_GLMSGEAR4(self)
        self.zz_fdict['GLMSGEAR4'] = self.GLMSGEAR4
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_PLMS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_PLMS, self).__init__(rmio, label,
            0xb0218000, 0x06C,
            'PLMS', 'SYNTH_NS.PLMS', 'read-write',
            u"",
            0x00000004, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PLMSENABLEDELAY = RM_Field_SYNTH_NS_PLMS_PLMSENABLEDELAY(self)
        self.zz_fdict['PLMSENABLEDELAY'] = self.PLMSENABLEDELAY
        self.PLMSGEARSLOT = RM_Field_SYNTH_NS_PLMS_PLMSGEARSLOT(self)
        self.zz_fdict['PLMSGEARSLOT'] = self.PLMSGEARSLOT
        self.PLMSGEAR0 = RM_Field_SYNTH_NS_PLMS_PLMSGEAR0(self)
        self.zz_fdict['PLMSGEAR0'] = self.PLMSGEAR0
        self.PLMSGEAR1 = RM_Field_SYNTH_NS_PLMS_PLMSGEAR1(self)
        self.zz_fdict['PLMSGEAR1'] = self.PLMSGEAR1
        self.PLMSGEAR2 = RM_Field_SYNTH_NS_PLMS_PLMSGEAR2(self)
        self.zz_fdict['PLMSGEAR2'] = self.PLMSGEAR2
        self.PLMSGEAR3 = RM_Field_SYNTH_NS_PLMS_PLMSGEAR3(self)
        self.zz_fdict['PLMSGEAR3'] = self.PLMSGEAR3
        self.PLMSGEAR4 = RM_Field_SYNTH_NS_PLMS_PLMSGEAR4(self)
        self.zz_fdict['PLMSGEAR4'] = self.PLMSGEAR4
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_LMSOVERRIDE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_LMSOVERRIDE, self).__init__(rmio, label,
            0xb0218000, 0x070,
            'LMSOVERRIDE', 'SYNTH_NS.LMSOVERRIDE', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.GLMSOVERRIDEEN = RM_Field_SYNTH_NS_LMSOVERRIDE_GLMSOVERRIDEEN(self)
        self.zz_fdict['GLMSOVERRIDEEN'] = self.GLMSOVERRIDEEN
        self.GLMSOVERRIDEVAL = RM_Field_SYNTH_NS_LMSOVERRIDE_GLMSOVERRIDEVAL(self)
        self.zz_fdict['GLMSOVERRIDEVAL'] = self.GLMSOVERRIDEVAL
        self.PLMSOVERRIDEEN = RM_Field_SYNTH_NS_LMSOVERRIDE_PLMSOVERRIDEEN(self)
        self.zz_fdict['PLMSOVERRIDEEN'] = self.PLMSOVERRIDEEN
        self.PLMSOVERRIDEVAL = RM_Field_SYNTH_NS_LMSOVERRIDE_PLMSOVERRIDEVAL(self)
        self.zz_fdict['PLMSOVERRIDEVAL'] = self.PLMSOVERRIDEVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_DLFCTRLTX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_DLFCTRLTX, self).__init__(rmio, label,
            0xb0218000, 0x074,
            'DLFCTRLTX', 'SYNTH_NS.DLFCTRLTX', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXLOCKLPFBWGEAR2 = RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR2(self)
        self.zz_fdict['TXLOCKLPFBWGEAR2'] = self.TXLOCKLPFBWGEAR2
        self.TXLOCKLPFBWGEAR3 = RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR3(self)
        self.zz_fdict['TXLOCKLPFBWGEAR3'] = self.TXLOCKLPFBWGEAR3
        self.TXLOCKLPFBWGEAR4 = RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR4(self)
        self.zz_fdict['TXLOCKLPFBWGEAR4'] = self.TXLOCKLPFBWGEAR4
        self.TXLOCKLPFBWGEAR5 = RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR5(self)
        self.zz_fdict['TXLOCKLPFBWGEAR5'] = self.TXLOCKLPFBWGEAR5
        self.TXLOCKLPFBWGEAR6 = RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR6(self)
        self.zz_fdict['TXLOCKLPFBWGEAR6'] = self.TXLOCKLPFBWGEAR6
        self.TXLOCKLPFBWGEAR7 = RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR7(self)
        self.zz_fdict['TXLOCKLPFBWGEAR7'] = self.TXLOCKLPFBWGEAR7
        self.TXLOCKLPFBWGEAR8 = RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR8(self)
        self.zz_fdict['TXLOCKLPFBWGEAR8'] = self.TXLOCKLPFBWGEAR8
        self.TXLOCKLPFBWGEAR9 = RM_Field_SYNTH_NS_DLFCTRLTX_TXLOCKLPFBWGEAR9(self)
        self.zz_fdict['TXLOCKLPFBWGEAR9'] = self.TXLOCKLPFBWGEAR9
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_DLFCTRLRX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_DLFCTRLRX, self).__init__(rmio, label,
            0xb0218000, 0x078,
            'DLFCTRLRX', 'SYNTH_NS.DLFCTRLRX', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXLOCKLPFBWGEAR2 = RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR2(self)
        self.zz_fdict['RXLOCKLPFBWGEAR2'] = self.RXLOCKLPFBWGEAR2
        self.RXLOCKLPFBWGEAR3 = RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR3(self)
        self.zz_fdict['RXLOCKLPFBWGEAR3'] = self.RXLOCKLPFBWGEAR3
        self.RXLOCKLPFBWGEAR4 = RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR4(self)
        self.zz_fdict['RXLOCKLPFBWGEAR4'] = self.RXLOCKLPFBWGEAR4
        self.RXLOCKLPFBWGEAR5 = RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR5(self)
        self.zz_fdict['RXLOCKLPFBWGEAR5'] = self.RXLOCKLPFBWGEAR5
        self.RXLOCKLPFBWGEAR6 = RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR6(self)
        self.zz_fdict['RXLOCKLPFBWGEAR6'] = self.RXLOCKLPFBWGEAR6
        self.RXLOCKLPFBWGEAR7 = RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR7(self)
        self.zz_fdict['RXLOCKLPFBWGEAR7'] = self.RXLOCKLPFBWGEAR7
        self.RXLOCKLPFBWGEAR8 = RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR8(self)
        self.zz_fdict['RXLOCKLPFBWGEAR8'] = self.RXLOCKLPFBWGEAR8
        self.RXLOCKLPFBWGEAR9 = RM_Field_SYNTH_NS_DLFCTRLRX_RXLOCKLPFBWGEAR9(self)
        self.zz_fdict['RXLOCKLPFBWGEAR9'] = self.RXLOCKLPFBWGEAR9
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_DLFCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_DLFCTRL, self).__init__(rmio, label,
            0xb0218000, 0x07C,
            'DLFCTRL', 'SYNTH_NS.DLFCTRL', 'read-write',
            u"",
            0x000F0000, 0x01FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LOCKLPFBWGEAR0 = RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEAR0(self)
        self.zz_fdict['LOCKLPFBWGEAR0'] = self.LOCKLPFBWGEAR0
        self.LOCKLPFBWGEAR1 = RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEAR1(self)
        self.zz_fdict['LOCKLPFBWGEAR1'] = self.LOCKLPFBWGEAR1
        self.LOCKLPFBWGEARSLOT = RM_Field_SYNTH_NS_DLFCTRL_LOCKLPFBWGEARSLOT(self)
        self.zz_fdict['LOCKLPFBWGEARSLOT'] = self.LOCKLPFBWGEARSLOT
        self.LPFBWLOADDEL = RM_Field_SYNTH_NS_DLFCTRL_LPFBWLOADDEL(self)
        self.zz_fdict['LPFBWLOADDEL'] = self.LPFBWLOADDEL
        self.LPFBWFORCE = RM_Field_SYNTH_NS_DLFCTRL_LPFBWFORCE(self)
        self.zz_fdict['LPFBWFORCE'] = self.LPFBWFORCE
        self.LPFBWLOADMAN = RM_Field_SYNTH_NS_DLFCTRL_LPFBWLOADMAN(self)
        self.zz_fdict['LPFBWLOADMAN'] = self.LPFBWLOADMAN
        self.LPFBWDURINGHOP = RM_Field_SYNTH_NS_DLFCTRL_LPFBWDURINGHOP(self)
        self.zz_fdict['LPFBWDURINGHOP'] = self.LPFBWDURINGHOP
        self.LPFBWAFTERHOP = RM_Field_SYNTH_NS_DLFCTRL_LPFBWAFTERHOP(self)
        self.zz_fdict['LPFBWAFTERHOP'] = self.LPFBWAFTERHOP
        self.DLFADDRRST = RM_Field_SYNTH_NS_DLFCTRL_DLFADDRRST(self)
        self.zz_fdict['DLFADDRRST'] = self.DLFADDRRST
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_DLFKF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_DLFKF, self).__init__(rmio, label,
            0xb0218000, 0x080,
            'DLFKF', 'SYNTH_NS.DLFKF', 'read-write',
            u"",
            0x00000000, 0x003FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.KF = RM_Field_SYNTH_NS_DLFKF_KF(self)
        self.zz_fdict['KF'] = self.KF
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_DLFKIZP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_DLFKIZP, self).__init__(rmio, label,
            0xb0218000, 0x084,
            'DLFKIZP', 'SYNTH_NS.DLFKIZP', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.KI = RM_Field_SYNTH_NS_DLFKIZP_KI(self)
        self.zz_fdict['KI'] = self.KI
        self.ZP = RM_Field_SYNTH_NS_DLFKIZP_ZP(self)
        self.zz_fdict['ZP'] = self.ZP
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_DSMCTRLRX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_DSMCTRLRX, self).__init__(rmio, label,
            0xb0218000, 0x088,
            'DSMCTRLRX', 'SYNTH_NS.DSMCTRLRX', 'read-write',
            u"",
            0x00000000, 0x0000007F,
            0x00001000, 0x00002000,
            0x00003000)

        self.DITHERDACRX = RM_Field_SYNTH_NS_DSMCTRLRX_DITHERDACRX(self)
        self.zz_fdict['DITHERDACRX'] = self.DITHERDACRX
        self.LSBFORCERX = RM_Field_SYNTH_NS_DSMCTRLRX_LSBFORCERX(self)
        self.zz_fdict['LSBFORCERX'] = self.LSBFORCERX
        self.DEMMODERX = RM_Field_SYNTH_NS_DSMCTRLRX_DEMMODERX(self)
        self.zz_fdict['DEMMODERX'] = self.DEMMODERX
        self.REQORDERRX = RM_Field_SYNTH_NS_DSMCTRLRX_REQORDERRX(self)
        self.zz_fdict['REQORDERRX'] = self.REQORDERRX
        self.PHISELRX = RM_Field_SYNTH_NS_DSMCTRLRX_PHISELRX(self)
        self.zz_fdict['PHISELRX'] = self.PHISELRX
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_DSMCTRLTX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_DSMCTRLTX, self).__init__(rmio, label,
            0xb0218000, 0x08C,
            'DSMCTRLTX', 'SYNTH_NS.DSMCTRLTX', 'read-write',
            u"",
            0x00000020, 0x000000EF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DITHERDACTX = RM_Field_SYNTH_NS_DSMCTRLTX_DITHERDACTX(self)
        self.zz_fdict['DITHERDACTX'] = self.DITHERDACTX
        self.LSBFORCETX = RM_Field_SYNTH_NS_DSMCTRLTX_LSBFORCETX(self)
        self.zz_fdict['LSBFORCETX'] = self.LSBFORCETX
        self.DEMMODETX = RM_Field_SYNTH_NS_DSMCTRLTX_DEMMODETX(self)
        self.zz_fdict['DEMMODETX'] = self.DEMMODETX
        self.REQORDERTX = RM_Field_SYNTH_NS_DSMCTRLTX_REQORDERTX(self)
        self.zz_fdict['REQORDERTX'] = self.REQORDERTX
        self.PHISELTX = RM_Field_SYNTH_NS_DSMCTRLTX_PHISELTX(self)
        self.zz_fdict['PHISELTX'] = self.PHISELTX
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_HOPPING(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_HOPPING, self).__init__(rmio, label,
            0xb0218000, 0x090,
            'HOPPING', 'SYNTH_NS.HOPPING', 'read-write',
            u"",
            0x00000040, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.HOPPINGEN = RM_Field_SYNTH_NS_HOPPING_HOPPINGEN(self)
        self.zz_fdict['HOPPINGEN'] = self.HOPPINGEN
        self.HCAP = RM_Field_SYNTH_NS_HOPPING_HCAP(self)
        self.zz_fdict['HCAP'] = self.HCAP
        self.HOPLPFBWGEARSLOT = RM_Field_SYNTH_NS_HOPPING_HOPLPFBWGEARSLOT(self)
        self.zz_fdict['HOPLPFBWGEARSLOT'] = self.HOPLPFBWGEARSLOT
        self.HOPHCAPDELAY = RM_Field_SYNTH_NS_HOPPING_HOPHCAPDELAY(self)
        self.zz_fdict['HOPHCAPDELAY'] = self.HOPHCAPDELAY
        self.HCAPRETIMESEL = RM_Field_SYNTH_NS_HOPPING_HCAPRETIMESEL(self)
        self.zz_fdict['HCAPRETIMESEL'] = self.HCAPRETIMESEL
        self.HCAPOVERRIDEEN = RM_Field_SYNTH_NS_HOPPING_HCAPOVERRIDEEN(self)
        self.zz_fdict['HCAPOVERRIDEEN'] = self.HCAPOVERRIDEEN
        self.HCAPMANLOAD = RM_Field_SYNTH_NS_HOPPING_HCAPMANLOAD(self)
        self.zz_fdict['HCAPMANLOAD'] = self.HCAPMANLOAD
        self.HCAPRETIMEEN = RM_Field_SYNTH_NS_HOPPING_HCAPRETIMEEN(self)
        self.zz_fdict['HCAPRETIMEEN'] = self.HCAPRETIMEEN
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_COMPANION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_COMPANION, self).__init__(rmio, label,
            0xb0218000, 0x094,
            'COMPANION', 'SYNTH_NS.COMPANION', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COMPANION0 = RM_Field_SYNTH_NS_COMPANION_COMPANION0(self)
        self.zz_fdict['COMPANION0'] = self.COMPANION0
        self.COMPANION1 = RM_Field_SYNTH_NS_COMPANION_COMPANION1(self)
        self.zz_fdict['COMPANION1'] = self.COMPANION1
        self.COMPANION2 = RM_Field_SYNTH_NS_COMPANION_COMPANION2(self)
        self.zz_fdict['COMPANION2'] = self.COMPANION2
        self.COMPANION3 = RM_Field_SYNTH_NS_COMPANION_COMPANION3(self)
        self.zz_fdict['COMPANION3'] = self.COMPANION3
        self.COMPANION4 = RM_Field_SYNTH_NS_COMPANION_COMPANION4(self)
        self.zz_fdict['COMPANION4'] = self.COMPANION4
        self.COMPANION5 = RM_Field_SYNTH_NS_COMPANION_COMPANION5(self)
        self.zz_fdict['COMPANION5'] = self.COMPANION5
        self.COMPANION6 = RM_Field_SYNTH_NS_COMPANION_COMPANION6(self)
        self.zz_fdict['COMPANION6'] = self.COMPANION6
        self.COMPANION7 = RM_Field_SYNTH_NS_COMPANION_COMPANION7(self)
        self.zz_fdict['COMPANION7'] = self.COMPANION7
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_FCALCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_FCALCTRL, self).__init__(rmio, label,
            0xb0218000, 0x098,
            'FCALCTRL', 'SYNTH_NS.FCALCTRL', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.NUMCYCLE6 = RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE6(self)
        self.zz_fdict['NUMCYCLE6'] = self.NUMCYCLE6
        self.NUMCYCLE7 = RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE7(self)
        self.zz_fdict['NUMCYCLE7'] = self.NUMCYCLE7
        self.NUMCYCLE8 = RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE8(self)
        self.zz_fdict['NUMCYCLE8'] = self.NUMCYCLE8
        self.NUMCYCLE9 = RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE9(self)
        self.zz_fdict['NUMCYCLE9'] = self.NUMCYCLE9
        self.NUMCYCLE10 = RM_Field_SYNTH_NS_FCALCTRL_NUMCYCLE10(self)
        self.zz_fdict['NUMCYCLE10'] = self.NUMCYCLE10
        self.STEPWAIT = RM_Field_SYNTH_NS_FCALCTRL_STEPWAIT(self)
        self.zz_fdict['STEPWAIT'] = self.STEPWAIT
        self.FCALMODE = RM_Field_SYNTH_NS_FCALCTRL_FCALMODE(self)
        self.zz_fdict['FCALMODE'] = self.FCALMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_SYNTH_NS_FCALSTEPWAIT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_SYNTH_NS_FCALSTEPWAIT, self).__init__(rmio, label,
            0xb0218000, 0x09C,
            'FCALSTEPWAIT', 'SYNTH_NS.FCALSTEPWAIT', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STEPWAIT1 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT1(self)
        self.zz_fdict['STEPWAIT1'] = self.STEPWAIT1
        self.STEPWAIT2 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT2(self)
        self.zz_fdict['STEPWAIT2'] = self.STEPWAIT2
        self.STEPWAIT3 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT3(self)
        self.zz_fdict['STEPWAIT3'] = self.STEPWAIT3
        self.STEPWAIT4 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT4(self)
        self.zz_fdict['STEPWAIT4'] = self.STEPWAIT4
        self.STEPWAIT5 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT5(self)
        self.zz_fdict['STEPWAIT5'] = self.STEPWAIT5
        self.STEPWAIT6 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT6(self)
        self.zz_fdict['STEPWAIT6'] = self.STEPWAIT6
        self.STEPWAIT7 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT7(self)
        self.zz_fdict['STEPWAIT7'] = self.STEPWAIT7
        self.STEPWAIT8 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT8(self)
        self.zz_fdict['STEPWAIT8'] = self.STEPWAIT8
        self.STEPWAIT9 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT9(self)
        self.zz_fdict['STEPWAIT9'] = self.STEPWAIT9
        self.STEPWAIT10 = RM_Field_SYNTH_NS_FCALSTEPWAIT_STEPWAIT10(self)
        self.zz_fdict['STEPWAIT10'] = self.STEPWAIT10
        self.__dict__['zz_frozen'] = True




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


class RM_Field_SYNTH_S_STATUS_CAPCALRUNNING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_CAPCALRUNNING, self).__init__(register,
            'CAPCALRUNNING', 'SYNTH_S.STATUS.CAPCALRUNNING', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_CAPCALBITRESULT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_CAPCALBITRESULT, self).__init__(register,
            'CAPCALBITRESULT', 'SYNTH_S.STATUS.CAPCALBITRESULT', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_CAPCALFULLWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_CAPCALFULLWAIT, self).__init__(register,
            'CAPCALFULLWAIT', 'SYNTH_S.STATUS.CAPCALFULLWAIT', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_CAPCALERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_CAPCALERROR, self).__init__(register,
            'CAPCALERROR', 'SYNTH_S.STATUS.CAPCALERROR', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_VCOFREQACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_VCOFREQACTIVE, self).__init__(register,
            'VCOFREQACTIVE', 'SYNTH_S.STATUS.VCOFREQACTIVE', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_STATUS_CHPALLOWTRISTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_STATUS_CHPALLOWTRISTATE, self).__init__(register,
            'CHPALLOWTRISTATE', 'SYNTH_S.STATUS.CHPALLOWTRISTATE', 'read-only',
            u"",
            26, 1)
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
            16, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_PRSMUX1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_PRSMUX1, self).__init__(register,
            'PRSMUX1', 'SYNTH_S.CTRL.PRSMUX1', 'read-write',
            u"",
            20, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_DISCLKSYNTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_DISCLKSYNTH, self).__init__(register,
            'DISCLKSYNTH', 'SYNTH_S.CTRL.DISCLKSYNTH', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_INVCLKSYNTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_INVCLKSYNTH, self).__init__(register,
            'INVCLKSYNTH', 'SYNTH_S.CTRL.INVCLKSYNTH', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_TRISTATEPOSTPONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_TRISTATEPOSTPONE, self).__init__(register,
            'TRISTATEPOSTPONE', 'SYNTH_S.CTRL.TRISTATEPOSTPONE', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_INTEGERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_INTEGERMODE, self).__init__(register,
            'INTEGERMODE', 'SYNTH_S.CTRL.INTEGERMODE', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_MMDRSTNOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_MMDRSTNOVERRIDEEN, self).__init__(register,
            'MMDRSTNOVERRIDEEN', 'SYNTH_S.CTRL.MMDRSTNOVERRIDEEN', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CTRL_MMDMANRSTN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CTRL_MMDMANRSTN, self).__init__(register,
            'MMDMANRSTN', 'SYNTH_S.CTRL.MMDMANRSTN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_NUMCYCLES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_NUMCYCLES, self).__init__(register,
            'NUMCYCLES', 'SYNTH_S.CALCTRL.NUMCYCLES', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_CAPCALSIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_CAPCALSIDE, self).__init__(register,
            'CAPCALSIDE', 'SYNTH_S.CALCTRL.CAPCALSIDE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_CAPCALENDMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_CAPCALENDMODE, self).__init__(register,
            'CAPCALENDMODE', 'SYNTH_S.CALCTRL.CAPCALENDMODE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_CAPCALCYCLEWAIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_CAPCALCYCLEWAIT, self).__init__(register,
            'CAPCALCYCLEWAIT', 'SYNTH_S.CALCTRL.CAPCALCYCLEWAIT', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_CAPCALWAITMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_CAPCALWAITMODE, self).__init__(register,
            'CAPCALWAITMODE', 'SYNTH_S.CALCTRL.CAPCALWAITMODE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_CAPCALSINGLESTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_CAPCALSINGLESTEP, self).__init__(register,
            'CAPCALSINGLESTEP', 'SYNTH_S.CALCTRL.CAPCALSINGLESTEP', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_STARTUPTIMING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_STARTUPTIMING, self).__init__(register,
            'STARTUPTIMING', 'SYNTH_S.CALCTRL.STARTUPTIMING', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_SYNTHOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_SYNTHOVERRIDEEN, self).__init__(register,
            'SYNTHOVERRIDEEN', 'SYNTH_S.CALCTRL.SYNTHOVERRIDEEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_CLKLOADDENOMVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_CLKLOADDENOMVAL, self).__init__(register,
            'CLKLOADDENOMVAL', 'SYNTH_S.CALCTRL.CLKLOADDENOMVAL', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_PRESCALERRESETVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_PRESCALERRESETVAL, self).__init__(register,
            'PRESCALERRESETVAL', 'SYNTH_S.CALCTRL.PRESCALERRESETVAL', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CALCTRL_COUNTERRESETVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CALCTRL_COUNTERRESETVAL, self).__init__(register,
            'COUNTERRESETVAL', 'SYNTH_S.CALCTRL.COUNTERRESETVAL', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCDACCTRL_VCDACVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCDACCTRL_VCDACVAL, self).__init__(register,
            'VCDACVAL', 'SYNTH_S.VCDACCTRL.VCDACVAL', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCDACCTRL_VCDACEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCDACCTRL_VCDACEN, self).__init__(register,
            'VCDACEN', 'SYNTH_S.VCDACCTRL.VCDACEN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCDACCTRL_LPFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCDACCTRL_LPFEN, self).__init__(register,
            'LPFEN', 'SYNTH_S.VCDACCTRL.LPFEN', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_VCDACCTRL_LPFQSEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_VCDACCTRL_LPFQSEN, self).__init__(register,
            'LPFQSEN', 'SYNTH_S.VCDACCTRL.LPFQSEN', 'read-write',
            u"",
            8, 1)
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
            11, 5)
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
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CHPDACCTRL_CHPDACVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CHPDACCTRL_CHPDACVAL, self).__init__(register,
            'CHPDACVAL', 'SYNTH_S.CHPDACCTRL.CHPDACVAL', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CHPDACCTRL_OVERRIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CHPDACCTRL_OVERRIDE, self).__init__(register,
            'OVERRIDE', 'SYNTH_S.CHPDACCTRL.OVERRIDE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CAPCALCYCLECNT_CAPCALCYCLECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CAPCALCYCLECNT_CAPCALCYCLECNT, self).__init__(register,
            'CAPCALCYCLECNT', 'SYNTH_S.CAPCALCYCLECNT.CAPCALCYCLECNT', 'read-only',
            u"",
            0, 10)
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


class RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_NUMCYCLE, self).__init__(register,
            'NUMCYCLE', 'SYNTH_S.LOCNTCTRL.NUMCYCLE', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_LOCNTOVERRIDEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_LOCNTOVERRIDEEN, self).__init__(register,
            'LOCNTOVERRIDEEN', 'SYNTH_S.LOCNTCTRL.LOCNTOVERRIDEEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_LOCNTMANCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_LOCNTMANCLEAR, self).__init__(register,
            'LOCNTMANCLEAR', 'SYNTH_S.LOCNTCTRL.LOCNTMANCLEAR', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_LOCNTMANRUN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_LOCNTMANRUN, self).__init__(register,
            'LOCNTMANRUN', 'SYNTH_S.LOCNTCTRL.LOCNTMANRUN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTCTRL_FCALRUNCLKEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTCTRL_FCALRUNCLKEN, self).__init__(register,
            'FCALRUNCLKEN', 'SYNTH_S.LOCNTCTRL.FCALRUNCLKEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTSTATUS_LOCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTSTATUS_LOCOUNT, self).__init__(register,
            'LOCOUNT', 'SYNTH_S.LOCNTSTATUS.LOCOUNT', 'read-only',
            u"",
            0, 19)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTSTATUS_BUSY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTSTATUS_BUSY, self).__init__(register,
            'BUSY', 'SYNTH_S.LOCNTSTATUS.BUSY', 'read-only',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LOCNTTARGET_TARGET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LOCNTTARGET_TARGET, self).__init__(register,
            'TARGET', 'SYNTH_S.LOCNTTARGET.TARGET', 'read-only',
            u"",
            0, 19)
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


class RM_Field_SYNTH_S_MMDDENOMINIT_DENOMINIT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_MMDDENOMINIT_DENOMINIT2, self).__init__(register,
            'DENOMINIT2', 'SYNTH_S.MMDDENOMINIT.DENOMINIT2', 'read-write',
            u"",
            18, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_CHPDACINIT_DACINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_CHPDACINIT_DACINIT, self).__init__(register,
            'DACINIT', 'SYNTH_S.CHPDACINIT.DACINIT', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1CAL_OP1BWCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1CAL_OP1BWCAL, self).__init__(register,
            'OP1BWCAL', 'SYNTH_S.LPFCTRL1CAL.OP1BWCAL', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1CAL_OP1COMPCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1CAL_OP1COMPCAL, self).__init__(register,
            'OP1COMPCAL', 'SYNTH_S.LPFCTRL1CAL.OP1COMPCAL', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1CAL_RFBVALCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1CAL_RFBVALCAL, self).__init__(register,
            'RFBVALCAL', 'SYNTH_S.LPFCTRL1CAL.RFBVALCAL', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1CAL_RPVALCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1CAL_RPVALCAL, self).__init__(register,
            'RPVALCAL', 'SYNTH_S.LPFCTRL1CAL.RPVALCAL', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1CAL_RZVALCAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1CAL_RZVALCAL, self).__init__(register,
            'RZVALCAL', 'SYNTH_S.LPFCTRL1CAL.RZVALCAL', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1RX_OP1BWRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1RX_OP1BWRX, self).__init__(register,
            'OP1BWRX', 'SYNTH_S.LPFCTRL1RX.OP1BWRX', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1RX_OP1COMPRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1RX_OP1COMPRX, self).__init__(register,
            'OP1COMPRX', 'SYNTH_S.LPFCTRL1RX.OP1COMPRX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1RX_RFBVALRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1RX_RFBVALRX, self).__init__(register,
            'RFBVALRX', 'SYNTH_S.LPFCTRL1RX.RFBVALRX', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1RX_RPVALRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1RX_RPVALRX, self).__init__(register,
            'RPVALRX', 'SYNTH_S.LPFCTRL1RX.RPVALRX', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1RX_RZVALRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1RX_RZVALRX, self).__init__(register,
            'RZVALRX', 'SYNTH_S.LPFCTRL1RX.RZVALRX', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1TX_OP1BWTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1TX_OP1BWTX, self).__init__(register,
            'OP1BWTX', 'SYNTH_S.LPFCTRL1TX.OP1BWTX', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1TX_OP1COMPTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1TX_OP1COMPTX, self).__init__(register,
            'OP1COMPTX', 'SYNTH_S.LPFCTRL1TX.OP1COMPTX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1TX_RFBVALTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1TX_RFBVALTX, self).__init__(register,
            'RFBVALTX', 'SYNTH_S.LPFCTRL1TX.RFBVALTX', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1TX_RPVALTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1TX_RPVALTX, self).__init__(register,
            'RPVALTX', 'SYNTH_S.LPFCTRL1TX.RPVALTX', 'read-write',
            u"",
            11, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL1TX_RZVALTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL1TX_RZVALTX, self).__init__(register,
            'RZVALTX', 'SYNTH_S.LPFCTRL1TX.RZVALTX', 'read-write',
            u"",
            14, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_LPFSWENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_LPFSWENRX, self).__init__(register,
            'LPFSWENRX', 'SYNTH_S.LPFCTRL2RX.LPFSWENRX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_LPFINCAPRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_LPFINCAPRX, self).__init__(register,
            'LPFINCAPRX', 'SYNTH_S.LPFCTRL2RX.LPFINCAPRX', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_LPFGNDSWENRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_LPFGNDSWENRX, self).__init__(register,
            'LPFGNDSWENRX', 'SYNTH_S.LPFCTRL2RX.LPFGNDSWENRX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_CALCRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_CALCRX, self).__init__(register,
            'CALCRX', 'SYNTH_S.LPFCTRL2RX.CALCRX', 'read-write',
            u"",
            4, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_CASELRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_CASELRX, self).__init__(register,
            'CASELRX', 'SYNTH_S.LPFCTRL2RX.CASELRX', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_CAVALRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_CAVALRX, self).__init__(register,
            'CAVALRX', 'SYNTH_S.LPFCTRL2RX.CAVALRX', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_CFBSELRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_CFBSELRX, self).__init__(register,
            'CFBSELRX', 'SYNTH_S.LPFCTRL2RX.CFBSELRX', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_CZSELRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_CZSELRX, self).__init__(register,
            'CZSELRX', 'SYNTH_S.LPFCTRL2RX.CZSELRX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_CZVALRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_CZVALRX, self).__init__(register,
            'CZVALRX', 'SYNTH_S.LPFCTRL2RX.CZVALRX', 'read-write',
            u"",
            17, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_MODESELRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_MODESELRX, self).__init__(register,
            'MODESELRX', 'SYNTH_S.LPFCTRL2RX.MODESELRX', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2RX_VCMLVLRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2RX_VCMLVLRX, self).__init__(register,
            'VCMLVLRX', 'SYNTH_S.LPFCTRL2RX.VCMLVLRX', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_LPFSWENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_LPFSWENTX, self).__init__(register,
            'LPFSWENTX', 'SYNTH_S.LPFCTRL2TX.LPFSWENTX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_LPFINCAPTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_LPFINCAPTX, self).__init__(register,
            'LPFINCAPTX', 'SYNTH_S.LPFCTRL2TX.LPFINCAPTX', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_LPFGNDSWENTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_LPFGNDSWENTX, self).__init__(register,
            'LPFGNDSWENTX', 'SYNTH_S.LPFCTRL2TX.LPFGNDSWENTX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_CALCTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_CALCTX, self).__init__(register,
            'CALCTX', 'SYNTH_S.LPFCTRL2TX.CALCTX', 'read-write',
            u"",
            4, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_CASELTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_CASELTX, self).__init__(register,
            'CASELTX', 'SYNTH_S.LPFCTRL2TX.CASELTX', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_CAVALTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_CAVALTX, self).__init__(register,
            'CAVALTX', 'SYNTH_S.LPFCTRL2TX.CAVALTX', 'read-write',
            u"",
            10, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_CFBSELTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_CFBSELTX, self).__init__(register,
            'CFBSELTX', 'SYNTH_S.LPFCTRL2TX.CFBSELTX', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_CZSELTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_CZSELTX, self).__init__(register,
            'CZSELTX', 'SYNTH_S.LPFCTRL2TX.CZSELTX', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_CZVALTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_CZVALTX, self).__init__(register,
            'CZVALTX', 'SYNTH_S.LPFCTRL2TX.CZVALTX', 'read-write',
            u"",
            17, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_MODESELTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_MODESELTX, self).__init__(register,
            'MODESELTX', 'SYNTH_S.LPFCTRL2TX.MODESELTX', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_LPFCTRL2TX_VCMLVLTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_LPFCTRL2TX_VCMLVLTX, self).__init__(register,
            'VCMLVLTX', 'SYNTH_S.LPFCTRL2TX.VCMLVLTX', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_DITHERDSMINPUTRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_DITHERDSMINPUTRX, self).__init__(register,
            'DITHERDSMINPUTRX', 'SYNTH_S.DSMCTRLRX.DITHERDSMINPUTRX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_DITHERDSMOUTPUTRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_DITHERDSMOUTPUTRX, self).__init__(register,
            'DITHERDSMOUTPUTRX', 'SYNTH_S.DSMCTRLRX.DITHERDSMOUTPUTRX', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_DITHERDACRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_DITHERDACRX, self).__init__(register,
            'DITHERDACRX', 'SYNTH_S.DSMCTRLRX.DITHERDACRX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_DSMMODERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_DSMMODERX, self).__init__(register,
            'DSMMODERX', 'SYNTH_S.DSMCTRLRX.DSMMODERX', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_LSBFORCERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_LSBFORCERX, self).__init__(register,
            'LSBFORCERX', 'SYNTH_S.DSMCTRLRX.LSBFORCERX', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_DEMMODERX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_DEMMODERX, self).__init__(register,
            'DEMMODERX', 'SYNTH_S.DSMCTRLRX.DEMMODERX', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_MASHORDERRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_MASHORDERRX, self).__init__(register,
            'MASHORDERRX', 'SYNTH_S.DSMCTRLRX.MASHORDERRX', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLRX_REQORDERRX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLRX_REQORDERRX, self).__init__(register,
            'REQORDERRX', 'SYNTH_S.DSMCTRLRX.REQORDERRX', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_DITHERDSMINPUTTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_DITHERDSMINPUTTX, self).__init__(register,
            'DITHERDSMINPUTTX', 'SYNTH_S.DSMCTRLTX.DITHERDSMINPUTTX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_DITHERDSMOUTPUTTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_DITHERDSMOUTPUTTX, self).__init__(register,
            'DITHERDSMOUTPUTTX', 'SYNTH_S.DSMCTRLTX.DITHERDSMOUTPUTTX', 'read-write',
            u"",
            1, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_DITHERDACTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_DITHERDACTX, self).__init__(register,
            'DITHERDACTX', 'SYNTH_S.DSMCTRLTX.DITHERDACTX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_DSMMODETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_DSMMODETX, self).__init__(register,
            'DSMMODETX', 'SYNTH_S.DSMCTRLTX.DSMMODETX', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_LSBFORCETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_LSBFORCETX, self).__init__(register,
            'LSBFORCETX', 'SYNTH_S.DSMCTRLTX.LSBFORCETX', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_DEMMODETX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_DEMMODETX, self).__init__(register,
            'DEMMODETX', 'SYNTH_S.DSMCTRLTX.DEMMODETX', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_MASHORDERTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_MASHORDERTX, self).__init__(register,
            'MASHORDERTX', 'SYNTH_S.DSMCTRLTX.MASHORDERTX', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_DSMCTRLTX_REQORDERTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_DSMCTRLTX_REQORDERTX, self).__init__(register,
            'REQORDERTX', 'SYNTH_S.DSMCTRLTX.REQORDERTX', 'read-write',
            u"",
            26, 1)
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


class RM_Field_SYNTH_S_SFMIF_LOCKEDSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIF_LOCKEDSFMIF, self).__init__(register,
            'LOCKEDSFMIF', 'SYNTH_S.SFMIF.LOCKEDSFMIF', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIF_UNLOCKEDSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIF_UNLOCKEDSFMIF, self).__init__(register,
            'UNLOCKEDSFMIF', 'SYNTH_S.SFMIF.UNLOCKEDSFMIF', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIF_SYRDYSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIF_SYRDYSFMIF, self).__init__(register,
            'SYRDYSFMIF', 'SYNTH_S.SFMIF.SYRDYSFMIF', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIF_VCOHIGHSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIF_VCOHIGHSFMIF, self).__init__(register,
            'VCOHIGHSFMIF', 'SYNTH_S.SFMIF.VCOHIGHSFMIF', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIF_VCOLOWSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIF_VCOLOWSFMIF, self).__init__(register,
            'VCOLOWSFMIF', 'SYNTH_S.SFMIF.VCOLOWSFMIF', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIF_LOCNTDONESFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIF_LOCNTDONESFMIF, self).__init__(register,
            'LOCNTDONESFMIF', 'SYNTH_S.SFMIF.LOCNTDONESFMIF', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIEN_LOCKEDSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIEN_LOCKEDSFMIEN, self).__init__(register,
            'LOCKEDSFMIEN', 'SYNTH_S.SFMIEN.LOCKEDSFMIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIEN_UNLOCKEDSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIEN_UNLOCKEDSFMIEN, self).__init__(register,
            'UNLOCKEDSFMIEN', 'SYNTH_S.SFMIEN.UNLOCKEDSFMIEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIEN_SYRDYSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIEN_SYRDYSFMIEN, self).__init__(register,
            'SYRDYSFMIEN', 'SYNTH_S.SFMIEN.SYRDYSFMIEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIEN_VCOHIGHSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIEN_VCOHIGHSFMIEN, self).__init__(register,
            'VCOHIGHSFMIEN', 'SYNTH_S.SFMIEN.VCOHIGHSFMIEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIEN_VCOLOWSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIEN_VCOLOWSFMIEN, self).__init__(register,
            'VCOLOWSFMIEN', 'SYNTH_S.SFMIEN.VCOLOWSFMIEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_SYNTH_S_SFMIEN_LOCNTDONESFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_SYNTH_S_SFMIEN_LOCNTDONESFMIEN, self).__init__(register,
            'LOCNTDONESFMIEN', 'SYNTH_S.SFMIEN.LOCNTDONESFMIEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True



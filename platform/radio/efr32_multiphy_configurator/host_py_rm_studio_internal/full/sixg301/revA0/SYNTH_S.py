
# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_SYNTH_S' ]

from . static import Base_RM_Peripheral
from . SYNTH_S_register import *

class RM_Peripheral_SYNTH_S(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_SYNTH_S, self).__init__(rmio, label,
            0xA0218000, 'SYNTH_S',
            u"",
            [])
        self.IPVERSION = RM_Register_SYNTH_S_IPVERSION(self.zz_rmio, self.zz_label)
        self.zz_rdict['IPVERSION'] = self.IPVERSION
        self.EN = RM_Register_SYNTH_S_EN(self.zz_rmio, self.zz_label)
        self.zz_rdict['EN'] = self.EN
        self.IF = RM_Register_SYNTH_S_IF(self.zz_rmio, self.zz_label)
        self.zz_rdict['IF'] = self.IF
        self.IEN = RM_Register_SYNTH_S_IEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['IEN'] = self.IEN
        self.SEQIF = RM_Register_SYNTH_S_SEQIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQIF'] = self.SEQIF
        self.SEQIEN = RM_Register_SYNTH_S_SEQIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQIEN'] = self.SEQIEN
        self.STATUS = RM_Register_SYNTH_S_STATUS(self.zz_rmio, self.zz_label)
        self.zz_rdict['STATUS'] = self.STATUS
        self.CMD = RM_Register_SYNTH_S_CMD(self.zz_rmio, self.zz_label)
        self.zz_rdict['CMD'] = self.CMD
        self.CTRL = RM_Register_SYNTH_S_CTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL'] = self.CTRL
        self.VCDACCTRL = RM_Register_SYNTH_S_VCDACCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['VCDACCTRL'] = self.VCDACCTRL
        self.FREQ = RM_Register_SYNTH_S_FREQ(self.zz_rmio, self.zz_label)
        self.zz_rdict['FREQ'] = self.FREQ
        self.IFFREQ = RM_Register_SYNTH_S_IFFREQ(self.zz_rmio, self.zz_label)
        self.zz_rdict['IFFREQ'] = self.IFFREQ
        self.DIVCTRL = RM_Register_SYNTH_S_DIVCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['DIVCTRL'] = self.DIVCTRL
        self.CHCTRL = RM_Register_SYNTH_S_CHCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['CHCTRL'] = self.CHCTRL
        self.CHSP = RM_Register_SYNTH_S_CHSP(self.zz_rmio, self.zz_label)
        self.zz_rdict['CHSP'] = self.CHSP
        self.CALOFFSET = RM_Register_SYNTH_S_CALOFFSET(self.zz_rmio, self.zz_label)
        self.zz_rdict['CALOFFSET'] = self.CALOFFSET
        self.VCOTUNING = RM_Register_SYNTH_S_VCOTUNING(self.zz_rmio, self.zz_label)
        self.zz_rdict['VCOTUNING'] = self.VCOTUNING
        self.VCORANGE = RM_Register_SYNTH_S_VCORANGE(self.zz_rmio, self.zz_label)
        self.zz_rdict['VCORANGE'] = self.VCORANGE
        self.VCOGAIN = RM_Register_SYNTH_S_VCOGAIN(self.zz_rmio, self.zz_label)
        self.zz_rdict['VCOGAIN'] = self.VCOGAIN
        self.QNCCTRL = RM_Register_SYNTH_S_QNCCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['QNCCTRL'] = self.QNCCTRL
        self.QNCDACCTRL = RM_Register_SYNTH_S_QNCDACCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['QNCDACCTRL'] = self.QNCDACCTRL
        self.VCOFRCCAL = RM_Register_SYNTH_S_VCOFRCCAL(self.zz_rmio, self.zz_label)
        self.zz_rdict['VCOFRCCAL'] = self.VCOFRCCAL
        self.LOCNTCTRL = RM_Register_SYNTH_S_LOCNTCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['LOCNTCTRL'] = self.LOCNTCTRL
        self.LOCNTSTATUS = RM_Register_SYNTH_S_LOCNTSTATUS(self.zz_rmio, self.zz_label)
        self.zz_rdict['LOCNTSTATUS'] = self.LOCNTSTATUS
        self.LOCNTTARGET = RM_Register_SYNTH_S_LOCNTTARGET(self.zz_rmio, self.zz_label)
        self.zz_rdict['LOCNTTARGET'] = self.LOCNTTARGET
        self.MMDDENOMINIT = RM_Register_SYNTH_S_MMDDENOMINIT(self.zz_rmio, self.zz_label)
        self.zz_rdict['MMDDENOMINIT'] = self.MMDDENOMINIT
        self.GLMS = RM_Register_SYNTH_S_GLMS(self.zz_rmio, self.zz_label)
        self.zz_rdict['GLMS'] = self.GLMS
        self.PLMS = RM_Register_SYNTH_S_PLMS(self.zz_rmio, self.zz_label)
        self.zz_rdict['PLMS'] = self.PLMS
        self.LMSOVERRIDE = RM_Register_SYNTH_S_LMSOVERRIDE(self.zz_rmio, self.zz_label)
        self.zz_rdict['LMSOVERRIDE'] = self.LMSOVERRIDE
        self.DLFCTRLTX = RM_Register_SYNTH_S_DLFCTRLTX(self.zz_rmio, self.zz_label)
        self.zz_rdict['DLFCTRLTX'] = self.DLFCTRLTX
        self.DLFCTRLRX = RM_Register_SYNTH_S_DLFCTRLRX(self.zz_rmio, self.zz_label)
        self.zz_rdict['DLFCTRLRX'] = self.DLFCTRLRX
        self.DLFCTRL = RM_Register_SYNTH_S_DLFCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['DLFCTRL'] = self.DLFCTRL
        self.DLFKF = RM_Register_SYNTH_S_DLFKF(self.zz_rmio, self.zz_label)
        self.zz_rdict['DLFKF'] = self.DLFKF
        self.DLFKIZP = RM_Register_SYNTH_S_DLFKIZP(self.zz_rmio, self.zz_label)
        self.zz_rdict['DLFKIZP'] = self.DLFKIZP
        self.DSMCTRLRX = RM_Register_SYNTH_S_DSMCTRLRX(self.zz_rmio, self.zz_label)
        self.zz_rdict['DSMCTRLRX'] = self.DSMCTRLRX
        self.DSMCTRLTX = RM_Register_SYNTH_S_DSMCTRLTX(self.zz_rmio, self.zz_label)
        self.zz_rdict['DSMCTRLTX'] = self.DSMCTRLTX
        self.HOPPING = RM_Register_SYNTH_S_HOPPING(self.zz_rmio, self.zz_label)
        self.zz_rdict['HOPPING'] = self.HOPPING
        self.COMPANION = RM_Register_SYNTH_S_COMPANION(self.zz_rmio, self.zz_label)
        self.zz_rdict['COMPANION'] = self.COMPANION
        self.FCALCTRL = RM_Register_SYNTH_S_FCALCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['FCALCTRL'] = self.FCALCTRL
        self.FCALSTEPWAIT = RM_Register_SYNTH_S_FCALSTEPWAIT(self.zz_rmio, self.zz_label)
        self.zz_rdict['FCALSTEPWAIT'] = self.FCALSTEPWAIT
        self.__dict__['zz_frozen'] = True
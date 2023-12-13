
# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_SMCTRL_NS' ]

from . static import Base_RM_Peripheral
from . SMCTRL_NS_register import *

class RM_Peripheral_SMCTRL_NS(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_SMCTRL_NS, self).__init__(rmio, label,
            0xB6040000, 'SMCTRL_NS',
            u"",
            [])
        self.IPVERSION = RM_Register_SMCTRL_NS_IPVERSION(self.zz_rmio, self.zz_label)
        self.zz_rdict['IPVERSION'] = self.IPVERSION
        self.EN = RM_Register_SMCTRL_NS_EN(self.zz_rmio, self.zz_label)
        self.zz_rdict['EN'] = self.EN
        self.SWRST = RM_Register_SMCTRL_NS_SWRST(self.zz_rmio, self.zz_label)
        self.zz_rdict['SWRST'] = self.SWRST
        self.MAINIF = RM_Register_SMCTRL_NS_MAINIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['MAINIF'] = self.MAINIF
        self.MAINIEN = RM_Register_SMCTRL_NS_MAINIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['MAINIEN'] = self.MAINIEN
        self.SEQIF = RM_Register_SMCTRL_NS_SEQIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQIF'] = self.SEQIF
        self.SEQIEN = RM_Register_SMCTRL_NS_SEQIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQIEN'] = self.SEQIEN
        self.SWIF = RM_Register_SMCTRL_NS_SWIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['SWIF'] = self.SWIF
        self.SWIEN = RM_Register_SMCTRL_NS_SWIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['SWIEN'] = self.SWIEN
        self.GPREG = RM_Register_SMCTRL_NS_GPREG(self.zz_rmio, self.zz_label)
        self.zz_rdict['GPREG'] = self.GPREG
        self.TIMIF = RM_Register_SMCTRL_NS_TIMIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['TIMIF'] = self.TIMIF
        self.TIMIEN = RM_Register_SMCTRL_NS_TIMIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['TIMIEN'] = self.TIMIEN
        self.FRCRXCTRL = RM_Register_SMCTRL_NS_FRCRXCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['FRCRXCTRL'] = self.FRCRXCTRL
        self.CTRL = RM_Register_SMCTRL_NS_CTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL'] = self.CTRL
        self.PC = RM_Register_SMCTRL_NS_PC(self.zz_rmio, self.zz_label)
        self.zz_rdict['PC'] = self.PC
        self.SCRATCH0 = RM_Register_SMCTRL_NS_SCRATCH0(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH0'] = self.SCRATCH0
        self.SCRATCH1 = RM_Register_SMCTRL_NS_SCRATCH1(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH1'] = self.SCRATCH1
        self.SCRATCH2 = RM_Register_SMCTRL_NS_SCRATCH2(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH2'] = self.SCRATCH2
        self.SCRATCH3 = RM_Register_SMCTRL_NS_SCRATCH3(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH3'] = self.SCRATCH3
        self.SCRATCH4 = RM_Register_SMCTRL_NS_SCRATCH4(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH4'] = self.SCRATCH4
        self.SCRATCH5 = RM_Register_SMCTRL_NS_SCRATCH5(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH5'] = self.SCRATCH5
        self.SCRATCH6 = RM_Register_SMCTRL_NS_SCRATCH6(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH6'] = self.SCRATCH6
        self.SCRATCH7 = RM_Register_SMCTRL_NS_SCRATCH7(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH7'] = self.SCRATCH7
        self.PRSMUXLSB = RM_Register_SMCTRL_NS_PRSMUXLSB(self.zz_rmio, self.zz_label)
        self.zz_rdict['PRSMUXLSB'] = self.PRSMUXLSB
        self.PRSMUXMSB = RM_Register_SMCTRL_NS_PRSMUXMSB(self.zz_rmio, self.zz_label)
        self.zz_rdict['PRSMUXMSB'] = self.PRSMUXMSB
        self.PRSOUT = RM_Register_SMCTRL_NS_PRSOUT(self.zz_rmio, self.zz_label)
        self.zz_rdict['PRSOUT'] = self.PRSOUT
        self.RXEVMUX = RM_Register_SMCTRL_NS_RXEVMUX(self.zz_rmio, self.zz_label)
        self.zz_rdict['RXEVMUX'] = self.RXEVMUX
        self.TIMCTRL = RM_Register_SMCTRL_NS_TIMCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['TIMCTRL'] = self.TIMCTRL
        self.TIMSTAT = RM_Register_SMCTRL_NS_TIMSTAT(self.zz_rmio, self.zz_label)
        self.zz_rdict['TIMSTAT'] = self.TIMSTAT
        self.SHIFTS = RM_Register_SMCTRL_NS_SHIFTS(self.zz_rmio, self.zz_label)
        self.zz_rdict['SHIFTS'] = self.SHIFTS
        self.TXDONE = RM_Register_SMCTRL_NS_TXDONE(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXDONE'] = self.TXDONE
        self.__dict__['zz_frozen'] = True

# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_SMCTRL_S' ]

from . static import Base_RM_Peripheral
from . SMCTRL_S_register import *

class RM_Peripheral_SMCTRL_S(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_SMCTRL_S, self).__init__(rmio, label,
            0xA6040000, 'SMCTRL_S',
            u"",
            [])
        self.IPVERSION = RM_Register_SMCTRL_S_IPVERSION(self.zz_rmio, self.zz_label)
        self.zz_rdict['IPVERSION'] = self.IPVERSION
        self.EN = RM_Register_SMCTRL_S_EN(self.zz_rmio, self.zz_label)
        self.zz_rdict['EN'] = self.EN
        self.SWRST = RM_Register_SMCTRL_S_SWRST(self.zz_rmio, self.zz_label)
        self.zz_rdict['SWRST'] = self.SWRST
        self.MAINIF = RM_Register_SMCTRL_S_MAINIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['MAINIF'] = self.MAINIF
        self.MAINIEN = RM_Register_SMCTRL_S_MAINIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['MAINIEN'] = self.MAINIEN
        self.SEQIF = RM_Register_SMCTRL_S_SEQIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQIF'] = self.SEQIF
        self.SEQIEN = RM_Register_SMCTRL_S_SEQIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQIEN'] = self.SEQIEN
        self.SWIF = RM_Register_SMCTRL_S_SWIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['SWIF'] = self.SWIF
        self.SWIEN = RM_Register_SMCTRL_S_SWIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['SWIEN'] = self.SWIEN
        self.GPREG = RM_Register_SMCTRL_S_GPREG(self.zz_rmio, self.zz_label)
        self.zz_rdict['GPREG'] = self.GPREG
        self.TIMIF = RM_Register_SMCTRL_S_TIMIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['TIMIF'] = self.TIMIF
        self.TIMIEN = RM_Register_SMCTRL_S_TIMIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['TIMIEN'] = self.TIMIEN
        self.FRCRXCTRL = RM_Register_SMCTRL_S_FRCRXCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['FRCRXCTRL'] = self.FRCRXCTRL
        self.CTRL = RM_Register_SMCTRL_S_CTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL'] = self.CTRL
        self.PC = RM_Register_SMCTRL_S_PC(self.zz_rmio, self.zz_label)
        self.zz_rdict['PC'] = self.PC
        self.SCRATCH0 = RM_Register_SMCTRL_S_SCRATCH0(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH0'] = self.SCRATCH0
        self.SCRATCH1 = RM_Register_SMCTRL_S_SCRATCH1(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH1'] = self.SCRATCH1
        self.SCRATCH2 = RM_Register_SMCTRL_S_SCRATCH2(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH2'] = self.SCRATCH2
        self.SCRATCH3 = RM_Register_SMCTRL_S_SCRATCH3(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH3'] = self.SCRATCH3
        self.SCRATCH4 = RM_Register_SMCTRL_S_SCRATCH4(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH4'] = self.SCRATCH4
        self.SCRATCH5 = RM_Register_SMCTRL_S_SCRATCH5(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH5'] = self.SCRATCH5
        self.SCRATCH6 = RM_Register_SMCTRL_S_SCRATCH6(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH6'] = self.SCRATCH6
        self.SCRATCH7 = RM_Register_SMCTRL_S_SCRATCH7(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH7'] = self.SCRATCH7
        self.PRSMUXLSB = RM_Register_SMCTRL_S_PRSMUXLSB(self.zz_rmio, self.zz_label)
        self.zz_rdict['PRSMUXLSB'] = self.PRSMUXLSB
        self.PRSMUXMSB = RM_Register_SMCTRL_S_PRSMUXMSB(self.zz_rmio, self.zz_label)
        self.zz_rdict['PRSMUXMSB'] = self.PRSMUXMSB
        self.PRSOUT = RM_Register_SMCTRL_S_PRSOUT(self.zz_rmio, self.zz_label)
        self.zz_rdict['PRSOUT'] = self.PRSOUT
        self.RXEVMUX = RM_Register_SMCTRL_S_RXEVMUX(self.zz_rmio, self.zz_label)
        self.zz_rdict['RXEVMUX'] = self.RXEVMUX
        self.TIMCTRL = RM_Register_SMCTRL_S_TIMCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['TIMCTRL'] = self.TIMCTRL
        self.TIMSTAT = RM_Register_SMCTRL_S_TIMSTAT(self.zz_rmio, self.zz_label)
        self.zz_rdict['TIMSTAT'] = self.TIMSTAT
        self.SHIFTS = RM_Register_SMCTRL_S_SHIFTS(self.zz_rmio, self.zz_label)
        self.zz_rdict['SHIFTS'] = self.SHIFTS
        self.TXDONE = RM_Register_SMCTRL_S_TXDONE(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXDONE'] = self.TXDONE
        self.__dict__['zz_frozen'] = True
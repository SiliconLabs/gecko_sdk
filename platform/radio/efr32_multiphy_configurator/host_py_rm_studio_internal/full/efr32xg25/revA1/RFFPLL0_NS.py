
# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_RFFPLL0_NS' ]

from . static import Base_RM_Peripheral
from . RFFPLL0_NS_register import *

class RM_Peripheral_RFFPLL0_NS(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_RFFPLL0_NS, self).__init__(rmio, label,
            0x500C8000, 'RFFPLL0_NS',
            u"",
            [])
        self.IPVERSION = RM_Register_RFFPLL0_NS_IPVERSION(self.zz_rmio, self.zz_label)
        self.zz_rdict['IPVERSION'] = self.IPVERSION
        self.CFG = RM_Register_RFFPLL0_NS_CFG(self.zz_rmio, self.zz_label)
        self.zz_rdict['CFG'] = self.CFG
        self.CTRL = RM_Register_RFFPLL0_NS_CTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL'] = self.CTRL
        self.STATUS = RM_Register_RFFPLL0_NS_STATUS(self.zz_rmio, self.zz_label)
        self.zz_rdict['STATUS'] = self.STATUS
        self.RFBIASFSMCFG = RM_Register_RFFPLL0_NS_RFBIASFSMCFG(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFBIASFSMCFG'] = self.RFBIASFSMCFG
        self.RFBIASCTRL = RM_Register_RFFPLL0_NS_RFBIASCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFBIASCTRL'] = self.RFBIASCTRL
        self.RFBIASCAL = RM_Register_RFFPLL0_NS_RFBIASCAL(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFBIASCAL'] = self.RFBIASCAL
        self.RFBIASCAL1 = RM_Register_RFFPLL0_NS_RFBIASCAL1(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFBIASCAL1'] = self.RFBIASCAL1
        self.RFFPLLFSMCFG = RM_Register_RFFPLL0_NS_RFFPLLFSMCFG(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFFPLLFSMCFG'] = self.RFFPLLFSMCFG
        self.RFFPLLCTRL = RM_Register_RFFPLL0_NS_RFFPLLCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFFPLLCTRL'] = self.RFFPLLCTRL
        self.RFFPLLCTRL1 = RM_Register_RFFPLL0_NS_RFFPLLCTRL1(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFFPLLCTRL1'] = self.RFFPLLCTRL1
        self.RFFPLLCAL = RM_Register_RFFPLL0_NS_RFFPLLCAL(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFFPLLCAL'] = self.RFFPLLCAL
        self.RFFPLLCAL1 = RM_Register_RFFPLL0_NS_RFFPLLCAL1(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFFPLLCAL1'] = self.RFFPLLCAL1
        self.RFFPLLSTATUS = RM_Register_RFFPLL0_NS_RFFPLLSTATUS(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFFPLLSTATUS'] = self.RFFPLLSTATUS
        self.IF = RM_Register_RFFPLL0_NS_IF(self.zz_rmio, self.zz_label)
        self.zz_rdict['IF'] = self.IF
        self.IEN = RM_Register_RFFPLL0_NS_IEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['IEN'] = self.IEN
        self.LOCK = RM_Register_RFFPLL0_NS_LOCK(self.zz_rmio, self.zz_label)
        self.zz_rdict['LOCK'] = self.LOCK
        self.__dict__['zz_frozen'] = True

# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_RFCRC_NS' ]

from . static import Base_RM_Peripheral
from . RFCRC_NS_register import *

class RM_Peripheral_RFCRC_NS(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_RFCRC_NS, self).__init__(rmio, label,
            0xB8010000, 'RFCRC_NS',
            u"",
            [])
        self.IPVERSION = RM_Register_RFCRC_NS_IPVERSION(self.zz_rmio, self.zz_label)
        self.zz_rdict['IPVERSION'] = self.IPVERSION
        self.EN = RM_Register_RFCRC_NS_EN(self.zz_rmio, self.zz_label)
        self.zz_rdict['EN'] = self.EN
        self.CTRL = RM_Register_RFCRC_NS_CTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL'] = self.CTRL
        self.STATUS = RM_Register_RFCRC_NS_STATUS(self.zz_rmio, self.zz_label)
        self.zz_rdict['STATUS'] = self.STATUS
        self.CMD = RM_Register_RFCRC_NS_CMD(self.zz_rmio, self.zz_label)
        self.zz_rdict['CMD'] = self.CMD
        self.INPUTDATA = RM_Register_RFCRC_NS_INPUTDATA(self.zz_rmio, self.zz_label)
        self.zz_rdict['INPUTDATA'] = self.INPUTDATA
        self.INIT = RM_Register_RFCRC_NS_INIT(self.zz_rmio, self.zz_label)
        self.zz_rdict['INIT'] = self.INIT
        self.DATA = RM_Register_RFCRC_NS_DATA(self.zz_rmio, self.zz_label)
        self.zz_rdict['DATA'] = self.DATA
        self.POLY = RM_Register_RFCRC_NS_POLY(self.zz_rmio, self.zz_label)
        self.zz_rdict['POLY'] = self.POLY
        self.__dict__['zz_frozen'] = True
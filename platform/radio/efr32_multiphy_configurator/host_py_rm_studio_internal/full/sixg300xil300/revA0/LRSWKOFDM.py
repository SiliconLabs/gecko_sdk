
# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_LRSWKOFDM' ]

from . static import Base_RM_Peripheral
from . LRSWKOFDM_register import *

class RM_Peripheral_LRSWKOFDM(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_LRSWKOFDM, self).__init__(rmio, label,
            0xB500FC00, 'LRSWKOFDM',
            u"",
            ['CW', 'LEGOQPSK', 'SUNFSK', 'SUNOFDM', 'SUNOQPSK'])
        self.CFG1 = RM_Register_LRSWKOFDM_CFG1(self.zz_rmio, self.zz_label)
        self.zz_rdict['CFG1'] = self.CFG1
        self.VREGS = RM_Register_LRSWKOFDM_VREGS(self.zz_rmio, self.zz_label)
        self.zz_rdict['VREGS'] = self.VREGS
        self.COLLDET = RM_Register_LRSWKOFDM_COLLDET(self.zz_rmio, self.zz_label)
        self.zz_rdict['COLLDET'] = self.COLLDET
        self.AFC = RM_Register_LRSWKOFDM_AFC(self.zz_rmio, self.zz_label)
        self.zz_rdict['AFC'] = self.AFC
        self.TXCFG1 = RM_Register_LRSWKOFDM_TXCFG1(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXCFG1'] = self.TXCFG1
        self.ANT = RM_Register_LRSWKOFDM_ANT(self.zz_rmio, self.zz_label)
        self.zz_rdict['ANT'] = self.ANT
        self.__dict__['zz_frozen'] = True
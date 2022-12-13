
# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_LEGOQPSK' ]

from . static import Base_RM_Peripheral
from . LEGOQPSK_register import *

class RM_Peripheral_LEGOQPSK(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_LEGOQPSK, self).__init__(rmio, label,
            0xB500FC00, 'LEGOQPSK',
            u"",
            ['CW', 'LRSWKOFDM', 'SUNFSK', 'SUNOFDM', 'SUNOQPSK'])
        self.CFG1 = RM_Register_LEGOQPSK_CFG1(self.zz_rmio, self.zz_label)
        self.zz_rdict['CFG1'] = self.CFG1
        self.CFG2 = RM_Register_LEGOQPSK_CFG2(self.zz_rmio, self.zz_label)
        self.zz_rdict['CFG2'] = self.CFG2
        self.VREGS = RM_Register_LEGOQPSK_VREGS(self.zz_rmio, self.zz_label)
        self.zz_rdict['VREGS'] = self.VREGS
        self.COLLDET = RM_Register_LEGOQPSK_COLLDET(self.zz_rmio, self.zz_label)
        self.zz_rdict['COLLDET'] = self.COLLDET
        self.AFC = RM_Register_LEGOQPSK_AFC(self.zz_rmio, self.zz_label)
        self.zz_rdict['AFC'] = self.AFC
        self.TXCFG1 = RM_Register_LEGOQPSK_TXCFG1(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXCFG1'] = self.TXCFG1
        self.ANT = RM_Register_LEGOQPSK_ANT(self.zz_rmio, self.zz_label)
        self.zz_rdict['ANT'] = self.ANT
        self.PDET = RM_Register_LEGOQPSK_PDET(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDET'] = self.PDET
        self.PDTHR = RM_Register_LEGOQPSK_PDTHR(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDTHR'] = self.PDTHR
        self.__dict__['zz_frozen'] = True
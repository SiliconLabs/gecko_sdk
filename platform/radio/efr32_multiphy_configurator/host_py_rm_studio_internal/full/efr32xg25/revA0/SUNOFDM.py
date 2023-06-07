
# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_SUNOFDM' ]

from . static import Base_RM_Peripheral
from . SUNOFDM_register import *

class RM_Peripheral_SUNOFDM(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_SUNOFDM, self).__init__(rmio, label,
            0xB500FC00, 'SUNOFDM',
            u"",
            ['LRSWKOFDM', 'SUNFSK', 'SUNOQPSK'])
        self.CFG1 = RM_Register_SUNOFDM_CFG1(self.zz_rmio, self.zz_label)
        self.zz_rdict['CFG1'] = self.CFG1
        self.CFG2 = RM_Register_SUNOFDM_CFG2(self.zz_rmio, self.zz_label)
        self.zz_rdict['CFG2'] = self.CFG2
        self.VREGS = RM_Register_SUNOFDM_VREGS(self.zz_rmio, self.zz_label)
        self.zz_rdict['VREGS'] = self.VREGS
        self.RXCFG1 = RM_Register_SUNOFDM_RXCFG1(self.zz_rmio, self.zz_label)
        self.zz_rdict['RXCFG1'] = self.RXCFG1
        self.RXCFG2 = RM_Register_SUNOFDM_RXCFG2(self.zz_rmio, self.zz_label)
        self.zz_rdict['RXCFG2'] = self.RXCFG2
        self.COLLDET = RM_Register_SUNOFDM_COLLDET(self.zz_rmio, self.zz_label)
        self.zz_rdict['COLLDET'] = self.COLLDET
        self.AFC = RM_Register_SUNOFDM_AFC(self.zz_rmio, self.zz_label)
        self.zz_rdict['AFC'] = self.AFC
        self.TXCFG1 = RM_Register_SUNOFDM_TXCFG1(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXCFG1'] = self.TXCFG1
        self.ANT = RM_Register_SUNOFDM_ANT(self.zz_rmio, self.zz_label)
        self.zz_rdict['ANT'] = self.ANT
        self.PDET = RM_Register_SUNOFDM_PDET(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDET'] = self.PDET
        self.DECFILTCFG = RM_Register_SUNOFDM_DECFILTCFG(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCFG'] = self.DECFILTCFG
        self.DECFILTCOEFF0 = RM_Register_SUNOFDM_DECFILTCOEFF0(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCOEFF0'] = self.DECFILTCOEFF0
        self.DECFILTCOEFF1 = RM_Register_SUNOFDM_DECFILTCOEFF1(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCOEFF1'] = self.DECFILTCOEFF1
        self.DECFILTCOEFF2 = RM_Register_SUNOFDM_DECFILTCOEFF2(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCOEFF2'] = self.DECFILTCOEFF2
        self.DECFILTCOEFF3 = RM_Register_SUNOFDM_DECFILTCOEFF3(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCOEFF3'] = self.DECFILTCOEFF3
        self.DECFILTCOEFF4 = RM_Register_SUNOFDM_DECFILTCOEFF4(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCOEFF4'] = self.DECFILTCOEFF4
        self.DECFILTCOEFF5 = RM_Register_SUNOFDM_DECFILTCOEFF5(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCOEFF5'] = self.DECFILTCOEFF5
        self.DECFILTCOEFF6 = RM_Register_SUNOFDM_DECFILTCOEFF6(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCOEFF6'] = self.DECFILTCOEFF6
        self.DECFILTCOEFF7 = RM_Register_SUNOFDM_DECFILTCOEFF7(self.zz_rmio, self.zz_label)
        self.zz_rdict['DECFILTCOEFF7'] = self.DECFILTCOEFF7
        self.PDETFILTCFG = RM_Register_SUNOFDM_PDETFILTCFG(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCFG'] = self.PDETFILTCFG
        self.PDETFILTCOEFF0 = RM_Register_SUNOFDM_PDETFILTCOEFF0(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCOEFF0'] = self.PDETFILTCOEFF0
        self.PDETFILTCOEFF1 = RM_Register_SUNOFDM_PDETFILTCOEFF1(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCOEFF1'] = self.PDETFILTCOEFF1
        self.PDETFILTCOEFF2 = RM_Register_SUNOFDM_PDETFILTCOEFF2(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCOEFF2'] = self.PDETFILTCOEFF2
        self.PDETFILTCOEFF3 = RM_Register_SUNOFDM_PDETFILTCOEFF3(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCOEFF3'] = self.PDETFILTCOEFF3
        self.PDETFILTCOEFF4 = RM_Register_SUNOFDM_PDETFILTCOEFF4(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCOEFF4'] = self.PDETFILTCOEFF4
        self.PDETFILTCOEFF5 = RM_Register_SUNOFDM_PDETFILTCOEFF5(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCOEFF5'] = self.PDETFILTCOEFF5
        self.PDETFILTCOEFF6 = RM_Register_SUNOFDM_PDETFILTCOEFF6(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCOEFF6'] = self.PDETFILTCOEFF6
        self.PDETFILTCOEFF7 = RM_Register_SUNOFDM_PDETFILTCOEFF7(self.zz_rmio, self.zz_label)
        self.zz_rdict['PDETFILTCOEFF7'] = self.PDETFILTCOEFF7
        self.FELATENCIES = RM_Register_SUNOFDM_FELATENCIES(self.zz_rmio, self.zz_label)
        self.zz_rdict['FELATENCIES'] = self.FELATENCIES
        self.PAPR = RM_Register_SUNOFDM_PAPR(self.zz_rmio, self.zz_label)
        self.zz_rdict['PAPR'] = self.PAPR
        self.TXFILTCFG = RM_Register_SUNOFDM_TXFILTCFG(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCFG'] = self.TXFILTCFG
        self.TXFILTCOEFF0 = RM_Register_SUNOFDM_TXFILTCOEFF0(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCOEFF0'] = self.TXFILTCOEFF0
        self.TXFILTCOEFF1 = RM_Register_SUNOFDM_TXFILTCOEFF1(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCOEFF1'] = self.TXFILTCOEFF1
        self.TXFILTCOEFF2 = RM_Register_SUNOFDM_TXFILTCOEFF2(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCOEFF2'] = self.TXFILTCOEFF2
        self.TXFILTCOEFF3 = RM_Register_SUNOFDM_TXFILTCOEFF3(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCOEFF3'] = self.TXFILTCOEFF3
        self.TXFILTCOEFF4 = RM_Register_SUNOFDM_TXFILTCOEFF4(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCOEFF4'] = self.TXFILTCOEFF4
        self.TXFILTCOEFF5 = RM_Register_SUNOFDM_TXFILTCOEFF5(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCOEFF5'] = self.TXFILTCOEFF5
        self.TXFILTCOEFF6 = RM_Register_SUNOFDM_TXFILTCOEFF6(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCOEFF6'] = self.TXFILTCOEFF6
        self.TXFILTCOEFF7 = RM_Register_SUNOFDM_TXFILTCOEFF7(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXFILTCOEFF7'] = self.TXFILTCOEFF7
        self.__dict__['zz_frozen'] = True
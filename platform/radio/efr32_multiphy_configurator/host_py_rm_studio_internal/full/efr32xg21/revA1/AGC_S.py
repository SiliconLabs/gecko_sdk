
# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_AGC_S' ]

from . static import Base_RM_Peripheral
from . AGC_S_register import *

class RM_Peripheral_AGC_S(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_AGC_S, self).__init__(rmio, label,
            0xA800C000, 'AGC_S',
            u"",
            [])
        self.IPVERSION = RM_Register_AGC_S_IPVERSION(self.zz_rmio, self.zz_label)
        self.zz_rdict['IPVERSION'] = self.IPVERSION
        self.EN = RM_Register_AGC_S_EN(self.zz_rmio, self.zz_label)
        self.zz_rdict['EN'] = self.EN
        self.STATUS0 = RM_Register_AGC_S_STATUS0(self.zz_rmio, self.zz_label)
        self.zz_rdict['STATUS0'] = self.STATUS0
        self.STATUS1 = RM_Register_AGC_S_STATUS1(self.zz_rmio, self.zz_label)
        self.zz_rdict['STATUS1'] = self.STATUS1
        self.RSSI = RM_Register_AGC_S_RSSI(self.zz_rmio, self.zz_label)
        self.zz_rdict['RSSI'] = self.RSSI
        self.FRAMERSSI = RM_Register_AGC_S_FRAMERSSI(self.zz_rmio, self.zz_label)
        self.zz_rdict['FRAMERSSI'] = self.FRAMERSSI
        self.CTRL0 = RM_Register_AGC_S_CTRL0(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL0'] = self.CTRL0
        self.CTRL1 = RM_Register_AGC_S_CTRL1(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL1'] = self.CTRL1
        self.CTRL2 = RM_Register_AGC_S_CTRL2(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL2'] = self.CTRL2
        self.CTRL3 = RM_Register_AGC_S_CTRL3(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL3'] = self.CTRL3
        self.RSSISTEPTHR = RM_Register_AGC_S_RSSISTEPTHR(self.zz_rmio, self.zz_label)
        self.zz_rdict['RSSISTEPTHR'] = self.RSSISTEPTHR
        self.MANGAIN = RM_Register_AGC_S_MANGAIN(self.zz_rmio, self.zz_label)
        self.zz_rdict['MANGAIN'] = self.MANGAIN
        self.IF = RM_Register_AGC_S_IF(self.zz_rmio, self.zz_label)
        self.zz_rdict['IF'] = self.IF
        self.IEN = RM_Register_AGC_S_IEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['IEN'] = self.IEN
        self.CMD = RM_Register_AGC_S_CMD(self.zz_rmio, self.zz_label)
        self.zz_rdict['CMD'] = self.CMD
        self.GAINRANGE = RM_Register_AGC_S_GAINRANGE(self.zz_rmio, self.zz_label)
        self.zz_rdict['GAINRANGE'] = self.GAINRANGE
        self.AGCPERIOD = RM_Register_AGC_S_AGCPERIOD(self.zz_rmio, self.zz_label)
        self.zz_rdict['AGCPERIOD'] = self.AGCPERIOD
        self.HICNTREGION = RM_Register_AGC_S_HICNTREGION(self.zz_rmio, self.zz_label)
        self.zz_rdict['HICNTREGION'] = self.HICNTREGION
        self.STEPDWN = RM_Register_AGC_S_STEPDWN(self.zz_rmio, self.zz_label)
        self.zz_rdict['STEPDWN'] = self.STEPDWN
        self.GAINSTEPLIM = RM_Register_AGC_S_GAINSTEPLIM(self.zz_rmio, self.zz_label)
        self.zz_rdict['GAINSTEPLIM'] = self.GAINSTEPLIM
        self.PNRFATT0 = RM_Register_AGC_S_PNRFATT0(self.zz_rmio, self.zz_label)
        self.zz_rdict['PNRFATT0'] = self.PNRFATT0
        self.PNRFATT1 = RM_Register_AGC_S_PNRFATT1(self.zz_rmio, self.zz_label)
        self.zz_rdict['PNRFATT1'] = self.PNRFATT1
        self.PNRFATT2 = RM_Register_AGC_S_PNRFATT2(self.zz_rmio, self.zz_label)
        self.zz_rdict['PNRFATT2'] = self.PNRFATT2
        self.LNAMIXCODE0 = RM_Register_AGC_S_LNAMIXCODE0(self.zz_rmio, self.zz_label)
        self.zz_rdict['LNAMIXCODE0'] = self.LNAMIXCODE0
        self.LNAMIXCODE1 = RM_Register_AGC_S_LNAMIXCODE1(self.zz_rmio, self.zz_label)
        self.zz_rdict['LNAMIXCODE1'] = self.LNAMIXCODE1
        self.PGACODE0 = RM_Register_AGC_S_PGACODE0(self.zz_rmio, self.zz_label)
        self.zz_rdict['PGACODE0'] = self.PGACODE0
        self.PGACODE1 = RM_Register_AGC_S_PGACODE1(self.zz_rmio, self.zz_label)
        self.zz_rdict['PGACODE1'] = self.PGACODE1
        self.LBT = RM_Register_AGC_S_LBT(self.zz_rmio, self.zz_label)
        self.zz_rdict['LBT'] = self.LBT
        self.MIRRORIF = RM_Register_AGC_S_MIRRORIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['MIRRORIF'] = self.MIRRORIF
        self.__dict__['zz_frozen'] = True
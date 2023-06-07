
# -*- coding: utf-8 -*-

__all__ = [ 'RM_Peripheral_RAC_S' ]

from . static import Base_RM_Peripheral
from . RAC_S_register import *

class RM_Peripheral_RAC_S(Base_RM_Peripheral):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Peripheral_RAC_S, self).__init__(rmio, label,
            0xA8020000, 'RAC_S',
            u"",
            [])
        self.IPVERSION = RM_Register_RAC_S_IPVERSION(self.zz_rmio, self.zz_label)
        self.zz_rdict['IPVERSION'] = self.IPVERSION
        self.EN = RM_Register_RAC_S_EN(self.zz_rmio, self.zz_label)
        self.zz_rdict['EN'] = self.EN
        self.RXENSRCEN = RM_Register_RAC_S_RXENSRCEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['RXENSRCEN'] = self.RXENSRCEN
        self.STATUS = RM_Register_RAC_S_STATUS(self.zz_rmio, self.zz_label)
        self.zz_rdict['STATUS'] = self.STATUS
        self.CMD = RM_Register_RAC_S_CMD(self.zz_rmio, self.zz_label)
        self.zz_rdict['CMD'] = self.CMD
        self.CTRL = RM_Register_RAC_S_CTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['CTRL'] = self.CTRL
        self.FORCESTATE = RM_Register_RAC_S_FORCESTATE(self.zz_rmio, self.zz_label)
        self.zz_rdict['FORCESTATE'] = self.FORCESTATE
        self.IF = RM_Register_RAC_S_IF(self.zz_rmio, self.zz_label)
        self.zz_rdict['IF'] = self.IF
        self.IEN = RM_Register_RAC_S_IEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['IEN'] = self.IEN
        self.TESTCTRL = RM_Register_RAC_S_TESTCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['TESTCTRL'] = self.TESTCTRL
        self.SEQIF = RM_Register_RAC_S_SEQIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQIF'] = self.SEQIF
        self.SEQIEN = RM_Register_RAC_S_SEQIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQIEN'] = self.SEQIEN
        self.STATUS1 = RM_Register_RAC_S_STATUS1(self.zz_rmio, self.zz_label)
        self.zz_rdict['STATUS1'] = self.STATUS1
        self.FEMCTRL = RM_Register_RAC_S_FEMCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['FEMCTRL'] = self.FEMCTRL
        self.FEMDATA = RM_Register_RAC_S_FEMDATA(self.zz_rmio, self.zz_label)
        self.zz_rdict['FEMDATA'] = self.FEMDATA
        self.STIMER = RM_Register_RAC_S_STIMER(self.zz_rmio, self.zz_label)
        self.zz_rdict['STIMER'] = self.STIMER
        self.STIMERCOMP = RM_Register_RAC_S_STIMERCOMP(self.zz_rmio, self.zz_label)
        self.zz_rdict['STIMERCOMP'] = self.STIMERCOMP
        self.SEQCTRL = RM_Register_RAC_S_SEQCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['SEQCTRL'] = self.SEQCTRL
        self.PRESC = RM_Register_RAC_S_PRESC(self.zz_rmio, self.zz_label)
        self.zz_rdict['PRESC'] = self.PRESC
        self.SR0 = RM_Register_RAC_S_SR0(self.zz_rmio, self.zz_label)
        self.zz_rdict['SR0'] = self.SR0
        self.SR1 = RM_Register_RAC_S_SR1(self.zz_rmio, self.zz_label)
        self.zz_rdict['SR1'] = self.SR1
        self.SR2 = RM_Register_RAC_S_SR2(self.zz_rmio, self.zz_label)
        self.zz_rdict['SR2'] = self.SR2
        self.SR3 = RM_Register_RAC_S_SR3(self.zz_rmio, self.zz_label)
        self.zz_rdict['SR3'] = self.SR3
        self.STCTRL = RM_Register_RAC_S_STCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['STCTRL'] = self.STCTRL
        self.FRCTXWORD = RM_Register_RAC_S_FRCTXWORD(self.zz_rmio, self.zz_label)
        self.zz_rdict['FRCTXWORD'] = self.FRCTXWORD
        self.FRCRXWORD = RM_Register_RAC_S_FRCRXWORD(self.zz_rmio, self.zz_label)
        self.zz_rdict['FRCRXWORD'] = self.FRCRXWORD
        self.EM1PCSR = RM_Register_RAC_S_EM1PCSR(self.zz_rmio, self.zz_label)
        self.zz_rdict['EM1PCSR'] = self.EM1PCSR
        self.RFSTATUS = RM_Register_RAC_S_RFSTATUS(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFSTATUS'] = self.RFSTATUS
        self.STATUS2 = RM_Register_RAC_S_STATUS2(self.zz_rmio, self.zz_label)
        self.zz_rdict['STATUS2'] = self.STATUS2
        self.IFPGACTRL = RM_Register_RAC_S_IFPGACTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['IFPGACTRL'] = self.IFPGACTRL
        self.PAENCTRL = RM_Register_RAC_S_PAENCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['PAENCTRL'] = self.PAENCTRL
        self.APC = RM_Register_RAC_S_APC(self.zz_rmio, self.zz_label)
        self.zz_rdict['APC'] = self.APC
        self.AGCOVERWRITE0 = RM_Register_RAC_S_AGCOVERWRITE0(self.zz_rmio, self.zz_label)
        self.zz_rdict['AGCOVERWRITE0'] = self.AGCOVERWRITE0
        self.AGCOVERWRITE1 = RM_Register_RAC_S_AGCOVERWRITE1(self.zz_rmio, self.zz_label)
        self.zz_rdict['AGCOVERWRITE1'] = self.AGCOVERWRITE1
        self.AGCOVERWRITE2 = RM_Register_RAC_S_AGCOVERWRITE2(self.zz_rmio, self.zz_label)
        self.zz_rdict['AGCOVERWRITE2'] = self.AGCOVERWRITE2
        self.TXPKDCTRL = RM_Register_RAC_S_TXPKDCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXPKDCTRL'] = self.TXPKDCTRL
        self.TXPKDCMD = RM_Register_RAC_S_TXPKDCMD(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXPKDCMD'] = self.TXPKDCMD
        self.TXPKDSTATUS = RM_Register_RAC_S_TXPKDSTATUS(self.zz_rmio, self.zz_label)
        self.zz_rdict['TXPKDSTATUS'] = self.TXPKDSTATUS
        self.RADIOCLKCTRL = RM_Register_RAC_S_RADIOCLKCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['RADIOCLKCTRL'] = self.RADIOCLKCTRL
        self.SCRATCH0 = RM_Register_RAC_S_SCRATCH0(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH0'] = self.SCRATCH0
        self.SCRATCH1 = RM_Register_RAC_S_SCRATCH1(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH1'] = self.SCRATCH1
        self.SCRATCH2 = RM_Register_RAC_S_SCRATCH2(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH2'] = self.SCRATCH2
        self.SCRATCH3 = RM_Register_RAC_S_SCRATCH3(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH3'] = self.SCRATCH3
        self.SCRATCH4 = RM_Register_RAC_S_SCRATCH4(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH4'] = self.SCRATCH4
        self.SCRATCH5 = RM_Register_RAC_S_SCRATCH5(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH5'] = self.SCRATCH5
        self.SCRATCH6 = RM_Register_RAC_S_SCRATCH6(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH6'] = self.SCRATCH6
        self.SCRATCH7 = RM_Register_RAC_S_SCRATCH7(self.zz_rmio, self.zz_label)
        self.zz_rdict['SCRATCH7'] = self.SCRATCH7
        self.SOFTMCTRL = RM_Register_RAC_S_SOFTMCTRL(self.zz_rmio, self.zz_label)
        self.zz_rdict['SOFTMCTRL'] = self.SOFTMCTRL
        self.SFMIF = RM_Register_RAC_S_SFMIF(self.zz_rmio, self.zz_label)
        self.zz_rdict['SFMIF'] = self.SFMIF
        self.SFMIEN = RM_Register_RAC_S_SFMIEN(self.zz_rmio, self.zz_label)
        self.zz_rdict['SFMIEN'] = self.SFMIEN
        self.RFLOCK0 = RM_Register_RAC_S_RFLOCK0(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFLOCK0'] = self.RFLOCK0
        self.RFLOCK1 = RM_Register_RAC_S_RFLOCK1(self.zz_rmio, self.zz_label)
        self.zz_rdict['RFLOCK1'] = self.RFLOCK1
        self.__dict__['zz_frozen'] = True
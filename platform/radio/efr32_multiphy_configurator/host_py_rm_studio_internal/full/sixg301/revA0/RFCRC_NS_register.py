
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . RFCRC_NS_field import *


class RM_Register_RFCRC_NS_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_IPVERSION, self).__init__(rmio, label,
            0xb0210000, 0x000,
            'IPVERSION', 'RFCRC_NS.IPVERSION', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_RFCRC_NS_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_RFCRC_NS_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_EN, self).__init__(rmio, label,
            0xb0210000, 0x004,
            'EN', 'RFCRC_NS.EN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_RFCRC_NS_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.__dict__['zz_frozen'] = True


class RM_Register_RFCRC_NS_CTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_CTRL, self).__init__(rmio, label,
            0xb0210000, 0x008,
            'CTRL', 'RFCRC_NS.CTRL', 'read-write',
            u"",
            0x00000704, 0x00001FEF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INPUTINV = RM_Field_RFCRC_NS_CTRL_INPUTINV(self)
        self.zz_fdict['INPUTINV'] = self.INPUTINV
        self.OUTPUTINV = RM_Field_RFCRC_NS_CTRL_OUTPUTINV(self)
        self.zz_fdict['OUTPUTINV'] = self.OUTPUTINV
        self.CRCWIDTH = RM_Field_RFCRC_NS_CTRL_CRCWIDTH(self)
        self.zz_fdict['CRCWIDTH'] = self.CRCWIDTH
        self.INPUTBITORDER = RM_Field_RFCRC_NS_CTRL_INPUTBITORDER(self)
        self.zz_fdict['INPUTBITORDER'] = self.INPUTBITORDER
        self.BYTEREVERSE = RM_Field_RFCRC_NS_CTRL_BYTEREVERSE(self)
        self.zz_fdict['BYTEREVERSE'] = self.BYTEREVERSE
        self.BITREVERSE = RM_Field_RFCRC_NS_CTRL_BITREVERSE(self)
        self.zz_fdict['BITREVERSE'] = self.BITREVERSE
        self.BITSPERWORD = RM_Field_RFCRC_NS_CTRL_BITSPERWORD(self)
        self.zz_fdict['BITSPERWORD'] = self.BITSPERWORD
        self.PADCRCINPUT = RM_Field_RFCRC_NS_CTRL_PADCRCINPUT(self)
        self.zz_fdict['PADCRCINPUT'] = self.PADCRCINPUT
        self.__dict__['zz_frozen'] = True


class RM_Register_RFCRC_NS_STATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_STATUS, self).__init__(rmio, label,
            0xb0210000, 0x00C,
            'STATUS', 'RFCRC_NS.STATUS', 'read-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.BUSY = RM_Field_RFCRC_NS_STATUS_BUSY(self)
        self.zz_fdict['BUSY'] = self.BUSY
        self.__dict__['zz_frozen'] = True


class RM_Register_RFCRC_NS_CMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_CMD, self).__init__(rmio, label,
            0xb0210000, 0x010,
            'CMD', 'RFCRC_NS.CMD', 'write-only',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.INITIALIZE = RM_Field_RFCRC_NS_CMD_INITIALIZE(self)
        self.zz_fdict['INITIALIZE'] = self.INITIALIZE
        self.__dict__['zz_frozen'] = True


class RM_Register_RFCRC_NS_INPUTDATA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_INPUTDATA, self).__init__(rmio, label,
            0xb0210000, 0x014,
            'INPUTDATA', 'RFCRC_NS.INPUTDATA', 'write-only',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INPUTDATA = RM_Field_RFCRC_NS_INPUTDATA_INPUTDATA(self)
        self.zz_fdict['INPUTDATA'] = self.INPUTDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_RFCRC_NS_INIT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_INIT, self).__init__(rmio, label,
            0xb0210000, 0x018,
            'INIT', 'RFCRC_NS.INIT', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INIT = RM_Field_RFCRC_NS_INIT_INIT(self)
        self.zz_fdict['INIT'] = self.INIT
        self.__dict__['zz_frozen'] = True


class RM_Register_RFCRC_NS_DATA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_DATA, self).__init__(rmio, label,
            0xb0210000, 0x01C,
            'DATA', 'RFCRC_NS.DATA', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DATA = RM_Field_RFCRC_NS_DATA_DATA(self)
        self.zz_fdict['DATA'] = self.DATA
        self.__dict__['zz_frozen'] = True


class RM_Register_RFCRC_NS_POLY(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_RFCRC_NS_POLY, self).__init__(rmio, label,
            0xb0210000, 0x020,
            'POLY', 'RFCRC_NS.POLY', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POLY = RM_Field_RFCRC_NS_POLY_POLY(self)
        self.zz_fdict['POLY'] = self.POLY
        self.__dict__['zz_frozen'] = True



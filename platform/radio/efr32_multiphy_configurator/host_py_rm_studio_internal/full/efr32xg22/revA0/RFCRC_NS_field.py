
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_RFCRC_NS_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'RFCRC_NS.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_EN_EN, self).__init__(register,
            'EN', 'RFCRC_NS.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CTRL_INPUTINV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CTRL_INPUTINV, self).__init__(register,
            'INPUTINV', 'RFCRC_NS.CTRL.INPUTINV', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CTRL_OUTPUTINV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CTRL_OUTPUTINV, self).__init__(register,
            'OUTPUTINV', 'RFCRC_NS.CTRL.OUTPUTINV', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CTRL_CRCWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CTRL_CRCWIDTH, self).__init__(register,
            'CRCWIDTH', 'RFCRC_NS.CTRL.CRCWIDTH', 'read-write',
            u"",
            2, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CTRL_INPUTBITORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CTRL_INPUTBITORDER, self).__init__(register,
            'INPUTBITORDER', 'RFCRC_NS.CTRL.INPUTBITORDER', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CTRL_BYTEREVERSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CTRL_BYTEREVERSE, self).__init__(register,
            'BYTEREVERSE', 'RFCRC_NS.CTRL.BYTEREVERSE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CTRL_BITREVERSE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CTRL_BITREVERSE, self).__init__(register,
            'BITREVERSE', 'RFCRC_NS.CTRL.BITREVERSE', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CTRL_BITSPERWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CTRL_BITSPERWORD, self).__init__(register,
            'BITSPERWORD', 'RFCRC_NS.CTRL.BITSPERWORD', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CTRL_PADCRCINPUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CTRL_PADCRCINPUT, self).__init__(register,
            'PADCRCINPUT', 'RFCRC_NS.CTRL.PADCRCINPUT', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_STATUS_BUSY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_STATUS_BUSY, self).__init__(register,
            'BUSY', 'RFCRC_NS.STATUS.BUSY', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_CMD_INITIALIZE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_CMD_INITIALIZE, self).__init__(register,
            'INITIALIZE', 'RFCRC_NS.CMD.INITIALIZE', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_INPUTDATA_INPUTDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_INPUTDATA_INPUTDATA, self).__init__(register,
            'INPUTDATA', 'RFCRC_NS.INPUTDATA.INPUTDATA', 'write-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_INIT_INIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_INIT_INIT, self).__init__(register,
            'INIT', 'RFCRC_NS.INIT.INIT', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_DATA_DATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_DATA_DATA, self).__init__(register,
            'DATA', 'RFCRC_NS.DATA.DATA', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_RFCRC_NS_POLY_POLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_RFCRC_NS_POLY_POLY, self).__init__(register,
            'POLY', 'RFCRC_NS.POLY.POLY', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True



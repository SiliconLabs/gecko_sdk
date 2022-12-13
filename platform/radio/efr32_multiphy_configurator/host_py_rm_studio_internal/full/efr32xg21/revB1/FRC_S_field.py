
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_FRC_S_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'FRC_S.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_EN_EN, self).__init__(register,
            'EN', 'FRC_S.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_SNIFFDCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_SNIFFDCOUNT, self).__init__(register,
            'SNIFFDCOUNT', 'FRC_S.STATUS.SNIFFDCOUNT', 'read-only',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_ACTIVETXFCD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_ACTIVETXFCD, self).__init__(register,
            'ACTIVETXFCD', 'FRC_S.STATUS.ACTIVETXFCD', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_ACTIVERXFCD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_ACTIVERXFCD, self).__init__(register,
            'ACTIVERXFCD', 'FRC_S.STATUS.ACTIVERXFCD', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_SNIFFDFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_SNIFFDFRAME, self).__init__(register,
            'SNIFFDFRAME', 'FRC_S.STATUS.SNIFFDFRAME', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_RXRAWBLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_RXRAWBLOCKED, self).__init__(register,
            'RXRAWBLOCKED', 'FRC_S.STATUS.RXRAWBLOCKED', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_FRAMEOK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_FRAMEOK, self).__init__(register,
            'FRAMEOK', 'FRC_S.STATUS.FRAMEOK', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_RXABORTINPROGRESS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_RXABORTINPROGRESS, self).__init__(register,
            'RXABORTINPROGRESS', 'FRC_S.STATUS.RXABORTINPROGRESS', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_S.STATUS.TXWORD', 'read-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_S.STATUS.RXWORD', 'read-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_S.STATUS.CONVPAUSED', 'read-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_S.STATUS.TXSUBFRAMEPAUSED', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_S.STATUS.INTERLEAVEREADPAUSED', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_S.STATUS.INTERLEAVEWRITEPAUSED', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_S.STATUS.FRAMEDETPAUSED', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_FRAMELENGTHERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_FRAMELENGTHERROR, self).__init__(register,
            'FRAMELENGTHERROR', 'FRC_S.STATUS.FRAMELENGTHERROR', 'read-only',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_DEMODERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_DEMODERROR, self).__init__(register,
            'DEMODERROR', 'FRC_S.STATUS.DEMODERROR', 'read-only',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DFLCTRL_DFLMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DFLCTRL_DFLMODE, self).__init__(register,
            'DFLMODE', 'FRC_S.DFLCTRL.DFLMODE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DFLCTRL_DFLBITORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DFLCTRL_DFLBITORDER, self).__init__(register,
            'DFLBITORDER', 'FRC_S.DFLCTRL.DFLBITORDER', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DFLCTRL_DFLSHIFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DFLCTRL_DFLSHIFT, self).__init__(register,
            'DFLSHIFT', 'FRC_S.DFLCTRL.DFLSHIFT', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DFLCTRL_DFLOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DFLCTRL_DFLOFFSET, self).__init__(register,
            'DFLOFFSET', 'FRC_S.DFLCTRL.DFLOFFSET', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DFLCTRL_DFLBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DFLCTRL_DFLBITS, self).__init__(register,
            'DFLBITS', 'FRC_S.DFLCTRL.DFLBITS', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DFLCTRL_MINLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DFLCTRL_MINLENGTH, self).__init__(register,
            'MINLENGTH', 'FRC_S.DFLCTRL.MINLENGTH', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DFLCTRL_DFLINCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DFLCTRL_DFLINCLUDECRC, self).__init__(register,
            'DFLINCLUDECRC', 'FRC_S.DFLCTRL.DFLINCLUDECRC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MAXLENGTH_MAXLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MAXLENGTH_MAXLENGTH, self).__init__(register,
            'MAXLENGTH', 'FRC_S.MAXLENGTH.MAXLENGTH', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MAXLENGTH_INILENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MAXLENGTH_INILENGTH, self).__init__(register,
            'INILENGTH', 'FRC_S.MAXLENGTH.INILENGTH', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_ADDRFILTCTRL_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_ADDRFILTCTRL_EN, self).__init__(register,
            'EN', 'FRC_S.ADDRFILTCTRL.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_ADDRFILTCTRL_BRDCST00EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_ADDRFILTCTRL_BRDCST00EN, self).__init__(register,
            'BRDCST00EN', 'FRC_S.ADDRFILTCTRL.BRDCST00EN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_ADDRFILTCTRL_BRDCSTFFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_ADDRFILTCTRL_BRDCSTFFEN, self).__init__(register,
            'BRDCSTFFEN', 'FRC_S.ADDRFILTCTRL.BRDCSTFFEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_ADDRFILTCTRL_ADDRESS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_ADDRFILTCTRL_ADDRESS, self).__init__(register,
            'ADDRESS', 'FRC_S.ADDRFILTCTRL.ADDRESS', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DATABUFFER_DATABUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DATABUFFER_DATABUFFER, self).__init__(register,
            'DATABUFFER', 'FRC_S.DATABUFFER.DATABUFFER', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WCNT_WCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WCNT_WCNT, self).__init__(register,
            'WCNT', 'FRC_S.WCNT.WCNT', 'read-only',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WCNTCMP0_FRAMELENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WCNTCMP0_FRAMELENGTH, self).__init__(register,
            'FRAMELENGTH', 'FRC_S.WCNTCMP0.FRAMELENGTH', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WCNTCMP1_LENGTHFIELDLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WCNTCMP1_LENGTHFIELDLOC, self).__init__(register,
            'LENGTHFIELDLOC', 'FRC_S.WCNTCMP1.LENGTHFIELDLOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WCNTCMP2_ADDRFIELDLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WCNTCMP2_ADDRFIELDLOC, self).__init__(register,
            'ADDRFIELDLOC', 'FRC_S.WCNTCMP2.ADDRFIELDLOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_RXABORT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_RXABORT, self).__init__(register,
            'RXABORT', 'FRC_S.CMD.RXABORT', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_FRAMEDETRESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_FRAMEDETRESUME, self).__init__(register,
            'FRAMEDETRESUME', 'FRC_S.CMD.FRAMEDETRESUME', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_INTERLEAVEWRITERESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_INTERLEAVEWRITERESUME, self).__init__(register,
            'INTERLEAVEWRITERESUME', 'FRC_S.CMD.INTERLEAVEWRITERESUME', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_INTERLEAVEREADRESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_INTERLEAVEREADRESUME, self).__init__(register,
            'INTERLEAVEREADRESUME', 'FRC_S.CMD.INTERLEAVEREADRESUME', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_CONVRESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_CONVRESUME, self).__init__(register,
            'CONVRESUME', 'FRC_S.CMD.CONVRESUME', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_CONVTERMINATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_CONVTERMINATE, self).__init__(register,
            'CONVTERMINATE', 'FRC_S.CMD.CONVTERMINATE', 'write-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_TXSUBFRAMERESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_TXSUBFRAMERESUME, self).__init__(register,
            'TXSUBFRAMERESUME', 'FRC_S.CMD.TXSUBFRAMERESUME', 'write-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_INTERLEAVEINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_INTERLEAVEINIT, self).__init__(register,
            'INTERLEAVEINIT', 'FRC_S.CMD.INTERLEAVEINIT', 'write-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_INTERLEAVECNTCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_INTERLEAVECNTCLEAR, self).__init__(register,
            'INTERLEAVECNTCLEAR', 'FRC_S.CMD.INTERLEAVECNTCLEAR', 'write-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_CONVINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_CONVINIT, self).__init__(register,
            'CONVINIT', 'FRC_S.CMD.CONVINIT', 'write-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_BLOCKINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_BLOCKINIT, self).__init__(register,
            'BLOCKINIT', 'FRC_S.CMD.BLOCKINIT', 'write-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_STATEINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_STATEINIT, self).__init__(register,
            'STATEINIT', 'FRC_S.CMD.STATEINIT', 'write-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CMD_RXRAWUNBLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_RXRAWUNBLOCK, self).__init__(register,
            'RXRAWUNBLOCK', 'FRC_S.CMD.RXRAWUNBLOCK', 'write-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WHITECTRL_FEEDBACKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WHITECTRL_FEEDBACKSEL, self).__init__(register,
            'FEEDBACKSEL', 'FRC_S.WHITECTRL.FEEDBACKSEL', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WHITECTRL_XORFEEDBACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WHITECTRL_XORFEEDBACK, self).__init__(register,
            'XORFEEDBACK', 'FRC_S.WHITECTRL.XORFEEDBACK', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WHITECTRL_SHROUTPUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WHITECTRL_SHROUTPUTSEL, self).__init__(register,
            'SHROUTPUTSEL', 'FRC_S.WHITECTRL.SHROUTPUTSEL', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WHITECTRL_BLOCKERRORCORRECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WHITECTRL_BLOCKERRORCORRECT, self).__init__(register,
            'BLOCKERRORCORRECT', 'FRC_S.WHITECTRL.BLOCKERRORCORRECT', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WHITEPOLY_POLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WHITEPOLY_POLY, self).__init__(register,
            'POLY', 'FRC_S.WHITEPOLY.POLY', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WHITEINIT_WHITEINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WHITEINIT_WHITEINIT, self).__init__(register,
            'WHITEINIT', 'FRC_S.WHITEINIT.WHITEINIT', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_BLOCKWHITEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_BLOCKWHITEMODE, self).__init__(register,
            'BLOCKWHITEMODE', 'FRC_S.FECCTRL.BLOCKWHITEMODE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_CONVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_CONVMODE, self).__init__(register,
            'CONVMODE', 'FRC_S.FECCTRL.CONVMODE', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_CONVDECODEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_CONVDECODEMODE, self).__init__(register,
            'CONVDECODEMODE', 'FRC_S.FECCTRL.CONVDECODEMODE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_CONVTRACEBACKDISABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_CONVTRACEBACKDISABLE, self).__init__(register,
            'CONVTRACEBACKDISABLE', 'FRC_S.FECCTRL.CONVTRACEBACKDISABLE', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_CONVINV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_CONVINV, self).__init__(register,
            'CONVINV', 'FRC_S.FECCTRL.CONVINV', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_INTERLEAVEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_INTERLEAVEMODE, self).__init__(register,
            'INTERLEAVEMODE', 'FRC_S.FECCTRL.INTERLEAVEMODE', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_INTERLEAVEFIRSTINDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_INTERLEAVEFIRSTINDEX, self).__init__(register,
            'INTERLEAVEFIRSTINDEX', 'FRC_S.FECCTRL.INTERLEAVEFIRSTINDEX', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_INTERLEAVEWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_INTERLEAVEWIDTH, self).__init__(register,
            'INTERLEAVEWIDTH', 'FRC_S.FECCTRL.INTERLEAVEWIDTH', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_CONVBUSLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_CONVBUSLOCK, self).__init__(register,
            'CONVBUSLOCK', 'FRC_S.FECCTRL.CONVBUSLOCK', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_CONVSUBFRAMETERMINATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_CONVSUBFRAMETERMINATE, self).__init__(register,
            'CONVSUBFRAMETERMINATE', 'FRC_S.FECCTRL.CONVSUBFRAMETERMINATE', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_SINGLEBLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_SINGLEBLOCK, self).__init__(register,
            'SINGLEBLOCK', 'FRC_S.FECCTRL.SINGLEBLOCK', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_FORCE2FSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_FORCE2FSK, self).__init__(register,
            'FORCE2FSK', 'FRC_S.FECCTRL.FORCE2FSK', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FECCTRL_CONVHARDERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FECCTRL_CONVHARDERROR, self).__init__(register,
            'CONVHARDERROR', 'FRC_S.FECCTRL.CONVHARDERROR', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_BLOCKRAMADDR_BLOCKRAMADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_BLOCKRAMADDR_BLOCKRAMADDR, self).__init__(register,
            'BLOCKRAMADDR', 'FRC_S.BLOCKRAMADDR.BLOCKRAMADDR', 'read-write',
            u"",
            2, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CONVRAMADDR_CONVRAMADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CONVRAMADDR_CONVRAMADDR, self).__init__(register,
            'CONVRAMADDR', 'FRC_S.CONVRAMADDR.CONVRAMADDR', 'read-write',
            u"",
            2, 17)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_RANDOMTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_RANDOMTX, self).__init__(register,
            'RANDOMTX', 'FRC_S.CTRL.RANDOMTX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_UARTMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_UARTMODE, self).__init__(register,
            'UARTMODE', 'FRC_S.CTRL.UARTMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_BITORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_BITORDER, self).__init__(register,
            'BITORDER', 'FRC_S.CTRL.BITORDER', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_TXFCDMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_TXFCDMODE, self).__init__(register,
            'TXFCDMODE', 'FRC_S.CTRL.TXFCDMODE', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_RXFCDMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_RXFCDMODE, self).__init__(register,
            'RXFCDMODE', 'FRC_S.CTRL.RXFCDMODE', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_BITSPERWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_BITSPERWORD, self).__init__(register,
            'BITSPERWORD', 'FRC_S.CTRL.BITSPERWORD', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_RATESELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_RATESELECT, self).__init__(register,
            'RATESELECT', 'FRC_S.CTRL.RATESELECT', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_TXPREFETCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_TXPREFETCH, self).__init__(register,
            'TXPREFETCH', 'FRC_S.CTRL.TXPREFETCH', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_SEQHANDSHAKE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_SEQHANDSHAKE, self).__init__(register,
            'SEQHANDSHAKE', 'FRC_S.CTRL.SEQHANDSHAKE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_PRBSTEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_PRBSTEST, self).__init__(register,
            'PRBSTEST', 'FRC_S.CTRL.PRBSTEST', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_STORECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_STORECRC, self).__init__(register,
            'STORECRC', 'FRC_S.RXCTRL.STORECRC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_ACCEPTCRCERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_ACCEPTCRCERRORS, self).__init__(register,
            'ACCEPTCRCERRORS', 'FRC_S.RXCTRL.ACCEPTCRCERRORS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_ACCEPTBLOCKERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_ACCEPTBLOCKERRORS, self).__init__(register,
            'ACCEPTBLOCKERRORS', 'FRC_S.RXCTRL.ACCEPTBLOCKERRORS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_TRACKABFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_TRACKABFRAME, self).__init__(register,
            'TRACKABFRAME', 'FRC_S.RXCTRL.TRACKABFRAME', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_BUFCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_BUFCLEAR, self).__init__(register,
            'BUFCLEAR', 'FRC_S.RXCTRL.BUFCLEAR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_BUFRESTOREFRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_BUFRESTOREFRAMEERROR, self).__init__(register,
            'BUFRESTOREFRAMEERROR', 'FRC_S.RXCTRL.BUFRESTOREFRAMEERROR', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_BUFRESTORERXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_BUFRESTORERXABORTED, self).__init__(register,
            'BUFRESTORERXABORTED', 'FRC_S.RXCTRL.BUFRESTORERXABORTED', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_RXFRAMEENDAHEADBYTES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_RXFRAMEENDAHEADBYTES, self).__init__(register,
            'RXFRAMEENDAHEADBYTES', 'FRC_S.RXCTRL.RXFRAMEENDAHEADBYTES', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATA, self).__init__(register,
            'TRAILTXDATA', 'FRC_S.TRAILTXDATACTRL.TRAILTXDATA', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATACNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATACNT, self).__init__(register,
            'TRAILTXDATACNT', 'FRC_S.TRAILTXDATACTRL.TRAILTXDATACNT', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATAFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATAFORCE, self).__init__(register,
            'TRAILTXDATAFORCE', 'FRC_S.TRAILTXDATACTRL.TRAILTXDATAFORCE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILRXDATA_RSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILRXDATA_RSSI, self).__init__(register,
            'RSSI', 'FRC_S.TRAILRXDATA.RSSI', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILRXDATA_CRCOK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILRXDATA_CRCOK, self).__init__(register,
            'CRCOK', 'FRC_S.TRAILRXDATA.CRCOK', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0BASE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0BASE, self).__init__(register,
            'PROTIMERCC0BASE', 'FRC_S.TRAILRXDATA.PROTIMERCC0BASE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0WRAPL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0WRAPL, self).__init__(register,
            'PROTIMERCC0WRAPL', 'FRC_S.TRAILRXDATA.PROTIMERCC0WRAPL', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0WRAPH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0WRAPH, self).__init__(register,
            'PROTIMERCC0WRAPH', 'FRC_S.TRAILRXDATA.PROTIMERCC0WRAPH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILRXDATA_RTCSTAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILRXDATA_RTCSTAMP, self).__init__(register,
            'RTCSTAMP', 'FRC_S.TRAILRXDATA.RTCSTAMP', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SCNT_SCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SCNT_SCNT, self).__init__(register,
            'SCNT', 'FRC_S.SCNT.SCNT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CONVGENERATOR_GENERATOR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CONVGENERATOR_GENERATOR0, self).__init__(register,
            'GENERATOR0', 'FRC_S.CONVGENERATOR.GENERATOR0', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CONVGENERATOR_GENERATOR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CONVGENERATOR_GENERATOR1, self).__init__(register,
            'GENERATOR1', 'FRC_S.CONVGENERATOR.GENERATOR1', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CONVGENERATOR_RECURSIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CONVGENERATOR_RECURSIVE, self).__init__(register,
            'RECURSIVE', 'FRC_S.CONVGENERATOR.RECURSIVE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CONVGENERATOR_NONSYSTEMATIC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CONVGENERATOR_NONSYSTEMATIC, self).__init__(register,
            'NONSYSTEMATIC', 'FRC_S.CONVGENERATOR.NONSYSTEMATIC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PUNCTCTRL_PUNCT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PUNCTCTRL_PUNCT0, self).__init__(register,
            'PUNCT0', 'FRC_S.PUNCTCTRL.PUNCT0', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PUNCTCTRL_PUNCT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PUNCTCTRL_PUNCT1, self).__init__(register,
            'PUNCT1', 'FRC_S.PUNCTCTRL.PUNCT1', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_FRAMEDETPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_FRAMEDETPAUSEEN, self).__init__(register,
            'FRAMEDETPAUSEEN', 'FRC_S.PAUSECTRL.FRAMEDETPAUSEEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_TXINTERLEAVEWRITEPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_TXINTERLEAVEWRITEPAUSEEN, self).__init__(register,
            'TXINTERLEAVEWRITEPAUSEEN', 'FRC_S.PAUSECTRL.TXINTERLEAVEWRITEPAUSEEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_RXINTERLEAVEWRITEPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_RXINTERLEAVEWRITEPAUSEEN, self).__init__(register,
            'RXINTERLEAVEWRITEPAUSEEN', 'FRC_S.PAUSECTRL.RXINTERLEAVEWRITEPAUSEEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_INTERLEAVEREADPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_INTERLEAVEREADPAUSEEN, self).__init__(register,
            'INTERLEAVEREADPAUSEEN', 'FRC_S.PAUSECTRL.INTERLEAVEREADPAUSEEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_TXSUBFRAMEPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_TXSUBFRAMEPAUSEEN, self).__init__(register,
            'TXSUBFRAMEPAUSEEN', 'FRC_S.PAUSECTRL.TXSUBFRAMEPAUSEEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_CONVPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_CONVPAUSECNT, self).__init__(register,
            'CONVPAUSECNT', 'FRC_S.PAUSECTRL.CONVPAUSECNT', 'read-write',
            u"",
            5, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_INTERLEAVEWRITEPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_INTERLEAVEWRITEPAUSECNT, self).__init__(register,
            'INTERLEAVEWRITEPAUSECNT', 'FRC_S.PAUSECTRL.INTERLEAVEWRITEPAUSECNT', 'read-write',
            u"",
            11, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_INTERLEAVEREADPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_INTERLEAVEREADPAUSECNT, self).__init__(register,
            'INTERLEAVEREADPAUSECNT', 'FRC_S.PAUSECTRL.INTERLEAVEREADPAUSECNT', 'read-write',
            u"",
            16, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_S.IF.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_S.IF.TXAFTERFRAMEDONE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_S.IF.TXABORTED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_TXUF, self).__init__(register,
            'TXUF', 'FRC_S.IF.TXUF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_S.IF.RXDONE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_S.IF.RXABORTED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_S.IF.FRAMEERROR', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_S.IF.BLOCKERROR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_RXOF, self).__init__(register,
            'RXOF', 'FRC_S.IF.RXOF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_WCNTCMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_WCNTCMP0, self).__init__(register,
            'WCNTCMP0', 'FRC_S.IF.WCNTCMP0', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_WCNTCMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_WCNTCMP1, self).__init__(register,
            'WCNTCMP1', 'FRC_S.IF.WCNTCMP1', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_WCNTCMP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_WCNTCMP2, self).__init__(register,
            'WCNTCMP2', 'FRC_S.IF.WCNTCMP2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_S.IF.ADDRERROR', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_S.IF.BUSERROR', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_RXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_RXRAWEVENT, self).__init__(register,
            'RXRAWEVENT', 'FRC_S.IF.RXRAWEVENT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_TXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_TXRAWEVENT, self).__init__(register,
            'TXRAWEVENT', 'FRC_S.IF.TXRAWEVENT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_S.IF.SNIFFOF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_S.IF.FRAMEDETPAUSED', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_S.IF.INTERLEAVEWRITEPAUSED', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_S.IF.INTERLEAVEREADPAUSED', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_S.IF.TXSUBFRAMEPAUSED', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_S.IF.CONVPAUSED', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_S.IF.RXWORD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_S.IF.TXWORD', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_S.IEN.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_S.IEN.TXAFTERFRAMEDONE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_S.IEN.TXABORTED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_TXUF, self).__init__(register,
            'TXUF', 'FRC_S.IEN.TXUF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_S.IEN.RXDONE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_S.IEN.RXABORTED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_S.IEN.FRAMEERROR', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_S.IEN.BLOCKERROR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_RXOF, self).__init__(register,
            'RXOF', 'FRC_S.IEN.RXOF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_WCNTCMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_WCNTCMP0, self).__init__(register,
            'WCNTCMP0', 'FRC_S.IEN.WCNTCMP0', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_WCNTCMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_WCNTCMP1, self).__init__(register,
            'WCNTCMP1', 'FRC_S.IEN.WCNTCMP1', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_WCNTCMP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_WCNTCMP2, self).__init__(register,
            'WCNTCMP2', 'FRC_S.IEN.WCNTCMP2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_S.IEN.ADDRERROR', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_S.IEN.BUSERROR', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_RXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_RXRAWEVENT, self).__init__(register,
            'RXRAWEVENT', 'FRC_S.IEN.RXRAWEVENT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_TXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_TXRAWEVENT, self).__init__(register,
            'TXRAWEVENT', 'FRC_S.IEN.TXRAWEVENT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_S.IEN.SNIFFOF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_S.IEN.FRAMEDETPAUSED', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_S.IEN.INTERLEAVEWRITEPAUSED', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_S.IEN.INTERLEAVEREADPAUSED', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_S.IEN.TXSUBFRAMEPAUSED', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_S.IEN.CONVPAUSED', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_S.IEN.RXWORD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_S.IEN.TXWORD', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_S.MIRRORIF.TXDONE', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_S.MIRRORIF.TXAFTERFRAMEDONE', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_S.MIRRORIF.TXABORTED', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_TXUF, self).__init__(register,
            'TXUF', 'FRC_S.MIRRORIF.TXUF', 'read-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_S.MIRRORIF.RXDONE', 'read-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_S.MIRRORIF.RXABORTED', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_S.MIRRORIF.FRAMEERROR', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_S.MIRRORIF.BLOCKERROR', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_RXOF, self).__init__(register,
            'RXOF', 'FRC_S.MIRRORIF.RXOF', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_S.MIRRORIF.ADDRERROR', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_S.MIRRORIF.BUSERROR', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_S.MIRRORIF.SNIFFOF', 'read-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_S.MIRRORIF.FRAMEDETPAUSED', 'read-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_S.MIRRORIF.INTERLEAVEWRITEPAUSED', 'read-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_S.MIRRORIF.INTERLEAVEREADPAUSED', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_S.MIRRORIF.TXSUBFRAMEPAUSED', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_S.MIRRORIF.CONVPAUSED', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_MIRRORIF_IFMIRRORCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_MIRRORIF_IFMIRRORCLEAR, self).__init__(register,
            'IFMIRRORCLEAR', 'FRC_S.MIRRORIF.IFMIRRORCLEAR', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_BUFFERMODE_TXBUFFERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_BUFFERMODE_TXBUFFERMODE, self).__init__(register,
            'TXBUFFERMODE', 'FRC_S.BUFFERMODE.TXBUFFERMODE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_BUFFERMODE_RXBUFFERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_BUFFERMODE_RXBUFFERMODE, self).__init__(register,
            'RXBUFFERMODE', 'FRC_S.BUFFERMODE.RXBUFFERMODE', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_BUFFERMODE_RXFRCBUFMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_BUFFERMODE_RXFRCBUFMUX, self).__init__(register,
            'RXFRCBUFMUX', 'FRC_S.BUFFERMODE.RXFRCBUFMUX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFMODE, self).__init__(register,
            'SNIFFMODE', 'FRC_S.SNIFFCTRL.SNIFFMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFBITS, self).__init__(register,
            'SNIFFBITS', 'FRC_S.SNIFFCTRL.SNIFFBITS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFRXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFRXDATA, self).__init__(register,
            'SNIFFRXDATA', 'FRC_S.SNIFFCTRL.SNIFFRXDATA', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFTXDATA, self).__init__(register,
            'SNIFFTXDATA', 'FRC_S.SNIFFCTRL.SNIFFTXDATA', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFRSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFRSSI, self).__init__(register,
            'SNIFFRSSI', 'FRC_S.SNIFFCTRL.SNIFFRSSI', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFSTATE, self).__init__(register,
            'SNIFFSTATE', 'FRC_S.SNIFFCTRL.SNIFFSTATE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFAUXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFAUXDATA, self).__init__(register,
            'SNIFFAUXDATA', 'FRC_S.SNIFFCTRL.SNIFFAUXDATA', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFBR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFBR, self).__init__(register,
            'SNIFFBR', 'FRC_S.SNIFFCTRL.SNIFFBR', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFSLEEPCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFSLEEPCTRL, self).__init__(register,
            'SNIFFSLEEPCTRL', 'FRC_S.SNIFFCTRL.SNIFFSLEEPCTRL', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SNIFFCTRL_SNIFFSYNCWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SNIFFCTRL_SNIFFSYNCWORD, self).__init__(register,
            'SNIFFSYNCWORD', 'FRC_S.SNIFFCTRL.SNIFFSYNCWORD', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_AUXDATA_AUXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_AUXDATA_AUXDATA, self).__init__(register,
            'AUXDATA', 'FRC_S.AUXDATA.AUXDATA', 'write-only',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RAWCTRL_TXRAWMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RAWCTRL_TXRAWMODE, self).__init__(register,
            'TXRAWMODE', 'FRC_S.RAWCTRL.TXRAWMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RAWCTRL_RXRAWMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RAWCTRL_RXRAWMODE, self).__init__(register,
            'RXRAWMODE', 'FRC_S.RAWCTRL.RXRAWMODE', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RAWCTRL_RXRAWRANDOM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RAWCTRL_RXRAWRANDOM, self).__init__(register,
            'RXRAWRANDOM', 'FRC_S.RAWCTRL.RXRAWRANDOM', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RAWCTRL_RXRAWTRIGGER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RAWCTRL_RXRAWTRIGGER, self).__init__(register,
            'RXRAWTRIGGER', 'FRC_S.RAWCTRL.RXRAWTRIGGER', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RAWCTRL_DEMODRAWDATAMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RAWCTRL_DEMODRAWDATAMUX, self).__init__(register,
            'DEMODRAWDATAMUX', 'FRC_S.RAWCTRL.DEMODRAWDATAMUX', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXRAWDATA_RXRAWDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXRAWDATA_RXRAWDATA, self).__init__(register,
            'RXRAWDATA', 'FRC_S.RXRAWDATA.RXRAWDATA', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSEDATA_PAUSEDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSEDATA_PAUSEDATA, self).__init__(register,
            'PAUSEDATA', 'FRC_S.PAUSEDATA.PAUSEDATA', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_LIKELYCONVSTATE_LIKELYCONVSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_LIKELYCONVSTATE_LIKELYCONVSTATE, self).__init__(register,
            'LIKELYCONVSTATE', 'FRC_S.LIKELYCONVSTATE.LIKELYCONVSTATE', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENTNEXT_INTELEMENTNEXT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENTNEXT_INTELEMENTNEXT, self).__init__(register,
            'INTELEMENTNEXT', 'FRC_S.INTELEMENTNEXT.INTELEMENTNEXT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTWRITEPOINT_INTWRITEPOINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTWRITEPOINT_INTWRITEPOINT, self).__init__(register,
            'INTWRITEPOINT', 'FRC_S.INTWRITEPOINT.INTWRITEPOINT', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTREADPOINT_INTREADPOINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTREADPOINT_INTREADPOINT, self).__init__(register,
            'INTREADPOINT', 'FRC_S.INTREADPOINT.INTREADPOINT', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_AUTOCG_AUTOCGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_AUTOCG_AUTOCGEN, self).__init__(register,
            'AUTOCGEN', 'FRC_S.AUTOCG.AUTOCGEN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CGCLKSTOP_FORCEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CGCLKSTOP_FORCEOFF, self).__init__(register,
            'FORCEOFF', 'FRC_S.CGCLKSTOP.FORCEOFF', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RAMBASEADDR_RAMBASEADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RAMBASEADDR_RAMBASEADDR, self).__init__(register,
            'RAMBASEADDR', 'FRC_S.RAMBASEADDR.RAMBASEADDR', 'read-write',
            u"",
            12, 20)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD0_WORDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD0_WORDS, self).__init__(register,
            'WORDS', 'FRC_S.FCD0.WORDS', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD0_BUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD0_BUFFER, self).__init__(register,
            'BUFFER', 'FRC_S.FCD0.BUFFER', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD0_INCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD0_INCLUDECRC, self).__init__(register,
            'INCLUDECRC', 'FRC_S.FCD0.INCLUDECRC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD0_CALCCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD0_CALCCRC, self).__init__(register,
            'CALCCRC', 'FRC_S.FCD0.CALCCRC', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD0_SKIPCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD0_SKIPCRC, self).__init__(register,
            'SKIPCRC', 'FRC_S.FCD0.SKIPCRC', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD0_SKIPWHITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD0_SKIPWHITE, self).__init__(register,
            'SKIPWHITE', 'FRC_S.FCD0.SKIPWHITE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD0_ADDTRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD0_ADDTRAILTXDATA, self).__init__(register,
            'ADDTRAILTXDATA', 'FRC_S.FCD0.ADDTRAILTXDATA', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD0_EXCLUDESUBFRAMEWCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD0_EXCLUDESUBFRAMEWCNT, self).__init__(register,
            'EXCLUDESUBFRAMEWCNT', 'FRC_S.FCD0.EXCLUDESUBFRAMEWCNT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD1_WORDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD1_WORDS, self).__init__(register,
            'WORDS', 'FRC_S.FCD1.WORDS', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD1_BUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD1_BUFFER, self).__init__(register,
            'BUFFER', 'FRC_S.FCD1.BUFFER', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD1_INCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD1_INCLUDECRC, self).__init__(register,
            'INCLUDECRC', 'FRC_S.FCD1.INCLUDECRC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD1_CALCCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD1_CALCCRC, self).__init__(register,
            'CALCCRC', 'FRC_S.FCD1.CALCCRC', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD1_SKIPCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD1_SKIPCRC, self).__init__(register,
            'SKIPCRC', 'FRC_S.FCD1.SKIPCRC', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD1_SKIPWHITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD1_SKIPWHITE, self).__init__(register,
            'SKIPWHITE', 'FRC_S.FCD1.SKIPWHITE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD1_ADDTRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD1_ADDTRAILTXDATA, self).__init__(register,
            'ADDTRAILTXDATA', 'FRC_S.FCD1.ADDTRAILTXDATA', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD1_EXCLUDESUBFRAMEWCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD1_EXCLUDESUBFRAMEWCNT, self).__init__(register,
            'EXCLUDESUBFRAMEWCNT', 'FRC_S.FCD1.EXCLUDESUBFRAMEWCNT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD2_WORDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD2_WORDS, self).__init__(register,
            'WORDS', 'FRC_S.FCD2.WORDS', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD2_BUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD2_BUFFER, self).__init__(register,
            'BUFFER', 'FRC_S.FCD2.BUFFER', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD2_INCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD2_INCLUDECRC, self).__init__(register,
            'INCLUDECRC', 'FRC_S.FCD2.INCLUDECRC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD2_CALCCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD2_CALCCRC, self).__init__(register,
            'CALCCRC', 'FRC_S.FCD2.CALCCRC', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD2_SKIPCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD2_SKIPCRC, self).__init__(register,
            'SKIPCRC', 'FRC_S.FCD2.SKIPCRC', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD2_SKIPWHITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD2_SKIPWHITE, self).__init__(register,
            'SKIPWHITE', 'FRC_S.FCD2.SKIPWHITE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD2_ADDTRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD2_ADDTRAILTXDATA, self).__init__(register,
            'ADDTRAILTXDATA', 'FRC_S.FCD2.ADDTRAILTXDATA', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD2_EXCLUDESUBFRAMEWCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD2_EXCLUDESUBFRAMEWCNT, self).__init__(register,
            'EXCLUDESUBFRAMEWCNT', 'FRC_S.FCD2.EXCLUDESUBFRAMEWCNT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD3_WORDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD3_WORDS, self).__init__(register,
            'WORDS', 'FRC_S.FCD3.WORDS', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD3_BUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD3_BUFFER, self).__init__(register,
            'BUFFER', 'FRC_S.FCD3.BUFFER', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD3_INCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD3_INCLUDECRC, self).__init__(register,
            'INCLUDECRC', 'FRC_S.FCD3.INCLUDECRC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD3_CALCCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD3_CALCCRC, self).__init__(register,
            'CALCCRC', 'FRC_S.FCD3.CALCCRC', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD3_SKIPCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD3_SKIPCRC, self).__init__(register,
            'SKIPCRC', 'FRC_S.FCD3.SKIPCRC', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD3_SKIPWHITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD3_SKIPWHITE, self).__init__(register,
            'SKIPWHITE', 'FRC_S.FCD3.SKIPWHITE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD3_ADDTRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD3_ADDTRAILTXDATA, self).__init__(register,
            'ADDTRAILTXDATA', 'FRC_S.FCD3.ADDTRAILTXDATA', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_FCD3_EXCLUDESUBFRAMEWCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_FCD3_EXCLUDESUBFRAMEWCNT, self).__init__(register,
            'EXCLUDESUBFRAMEWCNT', 'FRC_S.FCD3.EXCLUDESUBFRAMEWCNT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT0_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT0_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT0.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT1_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT1_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT1.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT2_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT2_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT2.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT3_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT3_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT3.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT4_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT4_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT4.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT5_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT5_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT5.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT6_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT6_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT6.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT7_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT7_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT7.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT8_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT8_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT8.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT9_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT9_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT9.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT10_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT10_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT10.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT11_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT11_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT11.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT12_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT12_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT12.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT13_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT13_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT13.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT14_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT14_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT14.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_INTELEMENT15_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_INTELEMENT15_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_S.INTELEMENT15.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True




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


class RM_Field_FRC_S_STATUS_FSMSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_FSMSTATE, self).__init__(register,
            'FSMSTATE', 'FRC_S.STATUS.FSMSTATE', 'read-only',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_RXWCNTMATCHPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_RXWCNTMATCHPAUSED, self).__init__(register,
            'RXWCNTMATCHPAUSED', 'FRC_S.STATUS.RXWCNTMATCHPAUSED', 'read-only',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_STATUS_CRCERRORTOLERATED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_STATUS_CRCERRORTOLERATED, self).__init__(register,
            'CRCERRORTOLERATED', 'FRC_S.STATUS.CRCERRORTOLERATED', 'read-only',
            u"",
            26, 1)
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


class RM_Field_FRC_S_DFLCTRL_DFLBOIOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DFLCTRL_DFLBOIOFFSET, self).__init__(register,
            'DFLBOIOFFSET', 'FRC_S.DFLCTRL.DFLBOIOFFSET', 'read-write',
            u"",
            21, 4)
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


class RM_Field_FRC_S_CMD_RXPAUSERESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CMD_RXPAUSERESUME, self).__init__(register,
            'RXPAUSERESUME', 'FRC_S.CMD.RXPAUSERESUME', 'write-only',
            u"",
            13, 1)
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
            2, 30)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CONVRAMADDR_CONVRAMADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CONVRAMADDR_CONVRAMADDR, self).__init__(register,
            'CONVRAMADDR', 'FRC_S.CONVRAMADDR.CONVRAMADDR', 'read-write',
            u"",
            2, 30)
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


class RM_Field_FRC_S_CTRL_LSBFRTREVERT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_LSBFRTREVERT, self).__init__(register,
            'LSBFRTREVERT', 'FRC_S.CTRL.LSBFRTREVERT', 'read-write',
            u"",
            3, 1)
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


class RM_Field_FRC_S_CTRL_TXFETCHBLOCKING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_TXFETCHBLOCKING, self).__init__(register,
            'TXFETCHBLOCKING', 'FRC_S.CTRL.TXFETCHBLOCKING', 'read-write',
            u"",
            14, 1)
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


class RM_Field_FRC_S_CTRL_LPMODEDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_LPMODEDIS, self).__init__(register,
            'LPMODEDIS', 'FRC_S.CTRL.LPMODEDIS', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_WAITEOFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_WAITEOFEN, self).__init__(register,
            'WAITEOFEN', 'FRC_S.CTRL.WAITEOFEN', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_RXABORTIGNOREDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_RXABORTIGNOREDIS, self).__init__(register,
            'RXABORTIGNOREDIS', 'FRC_S.CTRL.RXABORTIGNOREDIS', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_FRAMEENDAHEADDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_FRAMEENDAHEADDIS, self).__init__(register,
            'FRAMEENDAHEADDIS', 'FRC_S.CTRL.FRAMEENDAHEADDIS', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_SKIPTXTRAILDATAWHITEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_SKIPTXTRAILDATAWHITEN, self).__init__(register,
            'SKIPTXTRAILDATAWHITEN', 'FRC_S.CTRL.SKIPTXTRAILDATAWHITEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_SKIPRXSUPSTATEWHITEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_SKIPRXSUPSTATEWHITEN, self).__init__(register,
            'SKIPRXSUPSTATEWHITEN', 'FRC_S.CTRL.SKIPRXSUPSTATEWHITEN', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_CTRL_HOLDTXTRAILDATAACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_CTRL_HOLDTXTRAILDATAACTIVE, self).__init__(register,
            'HOLDTXTRAILDATAACTIVE', 'FRC_S.CTRL.HOLDTXTRAILDATAACTIVE', 'read-write',
            u"",
            26, 1)
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


class RM_Field_FRC_S_RXCTRL_ACCEPTUARTERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_ACCEPTUARTERRORS, self).__init__(register,
            'ACCEPTUARTERRORS', 'FRC_S.RXCTRL.ACCEPTUARTERRORS', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_RXCTRL_IFINPUTWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_RXCTRL_IFINPUTWIDTH, self).__init__(register,
            'IFINPUTWIDTH', 'FRC_S.RXCTRL.IFINPUTWIDTH', 'read-write',
            u"",
            16, 2)
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


class RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXREPLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXREPLEN, self).__init__(register,
            'TRAILTXREPLEN', 'FRC_S.TRAILTXDATACTRL.TRAILTXREPLEN', 'read-write',
            u"",
            12, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILTXDATACTRL_TXSUPPLENOVERIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILTXDATACTRL_TXSUPPLENOVERIDE, self).__init__(register,
            'TXSUPPLENOVERIDE', 'FRC_S.TRAILTXDATACTRL.TXSUPPLENOVERIDE', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_TRAILTXDATACTRL_POSTAMBLEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_TRAILTXDATACTRL_POSTAMBLEEN, self).__init__(register,
            'POSTAMBLEEN', 'FRC_S.TRAILTXDATACTRL.POSTAMBLEEN', 'read-write',
            u"",
            23, 1)
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


class RM_Field_FRC_S_PAUSECTRL_RXWCNTMATCHPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_RXWCNTMATCHPAUSEEN, self).__init__(register,
            'RXWCNTMATCHPAUSEEN', 'FRC_S.PAUSECTRL.RXWCNTMATCHPAUSEEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_CONVPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_CONVPAUSECNT, self).__init__(register,
            'CONVPAUSECNT', 'FRC_S.PAUSECTRL.CONVPAUSECNT', 'read-write',
            u"",
            11, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_INTERLEAVEWRITEPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_INTERLEAVEWRITEPAUSECNT, self).__init__(register,
            'INTERLEAVEWRITEPAUSECNT', 'FRC_S.PAUSECTRL.INTERLEAVEWRITEPAUSECNT', 'read-write',
            u"",
            17, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PAUSECTRL_INTERLEAVEREADPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PAUSECTRL_INTERLEAVEREADPAUSECNT, self).__init__(register,
            'INTERLEAVEREADPAUSECNT', 'FRC_S.PAUSECTRL.INTERLEAVEREADPAUSECNT', 'read-write',
            u"",
            22, 5)
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


class RM_Field_FRC_S_IF_WCNTCMP3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_WCNTCMP3, self).__init__(register,
            'WCNTCMP3', 'FRC_S.IF.WCNTCMP3', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_WCNTCMP4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_WCNTCMP4, self).__init__(register,
            'WCNTCMP4', 'FRC_S.IF.WCNTCMP4', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_BOISET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_BOISET, self).__init__(register,
            'BOISET', 'FRC_S.IF.BOISET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_PKTBUFSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_PKTBUFSTART, self).__init__(register,
            'PKTBUFSTART', 'FRC_S.IF.PKTBUFSTART', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_S.IF.PKTBUFTHRESHOLD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_RXRAWOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_RXRAWOF, self).__init__(register,
            'RXRAWOF', 'FRC_S.IF.RXRAWOF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IF_WCNTCMP5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_WCNTCMP5, self).__init__(register,
            'WCNTCMP5', 'FRC_S.IF.WCNTCMP5', 'read-write',
            u"",
            23, 1)
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


class RM_Field_FRC_S_IF_UARTERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IF_UARTERROR, self).__init__(register,
            'UARTERROR', 'FRC_S.IF.UARTERROR', 'read-write',
            u"",
            31, 1)
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


class RM_Field_FRC_S_IEN_WCNTCMP3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_WCNTCMP3, self).__init__(register,
            'WCNTCMP3', 'FRC_S.IEN.WCNTCMP3', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_WCNTCMP4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_WCNTCMP4, self).__init__(register,
            'WCNTCMP4', 'FRC_S.IEN.WCNTCMP4', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_BOISET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_BOISET, self).__init__(register,
            'BOISET', 'FRC_S.IEN.BOISET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_PKTBUFSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_PKTBUFSTART, self).__init__(register,
            'PKTBUFSTART', 'FRC_S.IEN.PKTBUFSTART', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_S.IEN.PKTBUFTHRESHOLD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_RXRAWOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_RXRAWOF, self).__init__(register,
            'RXRAWOF', 'FRC_S.IEN.RXRAWOF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_IEN_WCNTCMP5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_WCNTCMP5, self).__init__(register,
            'WCNTCMP5', 'FRC_S.IEN.WCNTCMP5', 'read-write',
            u"",
            23, 1)
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


class RM_Field_FRC_S_IEN_UARTERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_IEN_UARTERROR, self).__init__(register,
            'UARTERROR', 'FRC_S.IEN.UARTERROR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_OTACNT_OTARXCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_OTACNT_OTARXCNT, self).__init__(register,
            'OTARXCNT', 'FRC_S.OTACNT.OTARXCNT', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_OTACNT_OTATXCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_OTACNT_OTATXCNT, self).__init__(register,
            'OTATXCNT', 'FRC_S.OTACNT.OTATXCNT', 'read-only',
            u"",
            16, 16)
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
            7, 2)
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


class RM_Field_FRC_S_SEQIF_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_S.SEQIF.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_S.SEQIF.TXAFTERFRAMEDONE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_S.SEQIF.TXABORTED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_TXUF, self).__init__(register,
            'TXUF', 'FRC_S.SEQIF.TXUF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_S.SEQIF.RXDONE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_S.SEQIF.RXABORTED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_S.SEQIF.FRAMEERROR', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_S.SEQIF.BLOCKERROR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_RXOF, self).__init__(register,
            'RXOF', 'FRC_S.SEQIF.RXOF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_WCNTCMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_WCNTCMP0, self).__init__(register,
            'WCNTCMP0', 'FRC_S.SEQIF.WCNTCMP0', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_WCNTCMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_WCNTCMP1, self).__init__(register,
            'WCNTCMP1', 'FRC_S.SEQIF.WCNTCMP1', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_WCNTCMP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_WCNTCMP2, self).__init__(register,
            'WCNTCMP2', 'FRC_S.SEQIF.WCNTCMP2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_S.SEQIF.ADDRERROR', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_S.SEQIF.BUSERROR', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_RXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_RXRAWEVENT, self).__init__(register,
            'RXRAWEVENT', 'FRC_S.SEQIF.RXRAWEVENT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_TXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_TXRAWEVENT, self).__init__(register,
            'TXRAWEVENT', 'FRC_S.SEQIF.TXRAWEVENT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_S.SEQIF.SNIFFOF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_WCNTCMP3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_WCNTCMP3, self).__init__(register,
            'WCNTCMP3', 'FRC_S.SEQIF.WCNTCMP3', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_WCNTCMP4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_WCNTCMP4, self).__init__(register,
            'WCNTCMP4', 'FRC_S.SEQIF.WCNTCMP4', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_BOISET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_BOISET, self).__init__(register,
            'BOISET', 'FRC_S.SEQIF.BOISET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_PKTBUFSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_PKTBUFSTART, self).__init__(register,
            'PKTBUFSTART', 'FRC_S.SEQIF.PKTBUFSTART', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_S.SEQIF.PKTBUFTHRESHOLD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_RXRAWOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_RXRAWOF, self).__init__(register,
            'RXRAWOF', 'FRC_S.SEQIF.RXRAWOF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_WCNTCMP5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_WCNTCMP5, self).__init__(register,
            'WCNTCMP5', 'FRC_S.SEQIF.WCNTCMP5', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_S.SEQIF.FRAMEDETPAUSED', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_S.SEQIF.INTERLEAVEWRITEPAUSED', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_S.SEQIF.INTERLEAVEREADPAUSED', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_S.SEQIF.TXSUBFRAMEPAUSED', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_S.SEQIF.CONVPAUSED', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_S.SEQIF.RXWORD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_S.SEQIF.TXWORD', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIF_UARTERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIF_UARTERROR, self).__init__(register,
            'UARTERROR', 'FRC_S.SEQIF.UARTERROR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_S.SEQIEN.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_S.SEQIEN.TXAFTERFRAMEDONE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_S.SEQIEN.TXABORTED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_TXUF, self).__init__(register,
            'TXUF', 'FRC_S.SEQIEN.TXUF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_S.SEQIEN.RXDONE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_S.SEQIEN.RXABORTED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_S.SEQIEN.FRAMEERROR', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_S.SEQIEN.BLOCKERROR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_RXOF, self).__init__(register,
            'RXOF', 'FRC_S.SEQIEN.RXOF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_WCNTCMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_WCNTCMP0, self).__init__(register,
            'WCNTCMP0', 'FRC_S.SEQIEN.WCNTCMP0', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_WCNTCMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_WCNTCMP1, self).__init__(register,
            'WCNTCMP1', 'FRC_S.SEQIEN.WCNTCMP1', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_WCNTCMP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_WCNTCMP2, self).__init__(register,
            'WCNTCMP2', 'FRC_S.SEQIEN.WCNTCMP2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_S.SEQIEN.ADDRERROR', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_S.SEQIEN.BUSERROR', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_RXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_RXRAWEVENT, self).__init__(register,
            'RXRAWEVENT', 'FRC_S.SEQIEN.RXRAWEVENT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_TXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_TXRAWEVENT, self).__init__(register,
            'TXRAWEVENT', 'FRC_S.SEQIEN.TXRAWEVENT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_S.SEQIEN.SNIFFOF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_WCNTCMP3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_WCNTCMP3, self).__init__(register,
            'WCNTCMP3', 'FRC_S.SEQIEN.WCNTCMP3', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_WCNTCMP4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_WCNTCMP4, self).__init__(register,
            'WCNTCMP4', 'FRC_S.SEQIEN.WCNTCMP4', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_BOISET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_BOISET, self).__init__(register,
            'BOISET', 'FRC_S.SEQIEN.BOISET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_PKTBUFSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_PKTBUFSTART, self).__init__(register,
            'PKTBUFSTART', 'FRC_S.SEQIEN.PKTBUFSTART', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_S.SEQIEN.PKTBUFTHRESHOLD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_RXRAWOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_RXRAWOF, self).__init__(register,
            'RXRAWOF', 'FRC_S.SEQIEN.RXRAWOF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_WCNTCMP5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_WCNTCMP5, self).__init__(register,
            'WCNTCMP5', 'FRC_S.SEQIEN.WCNTCMP5', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_S.SEQIEN.FRAMEDETPAUSED', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_S.SEQIEN.INTERLEAVEWRITEPAUSED', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_S.SEQIEN.INTERLEAVEREADPAUSED', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_S.SEQIEN.TXSUBFRAMEPAUSED', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_S.SEQIEN.CONVPAUSED', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_S.SEQIEN.RXWORD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_S.SEQIEN.TXWORD', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SEQIEN_UARTERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SEQIEN_UARTERROR, self).__init__(register,
            'UARTERROR', 'FRC_S.SEQIEN.UARTERROR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WCNTCMP3_SUPPLENFIELDLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WCNTCMP3_SUPPLENFIELDLOC, self).__init__(register,
            'SUPPLENFIELDLOC', 'FRC_S.WCNTCMP3.SUPPLENFIELDLOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_BOICTRL_BOIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_BOICTRL_BOIEN, self).__init__(register,
            'BOIEN', 'FRC_S.BOICTRL.BOIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_BOICTRL_BOIFIELDLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_BOICTRL_BOIFIELDLOC, self).__init__(register,
            'BOIFIELDLOC', 'FRC_S.BOICTRL.BOIFIELDLOC', 'read-write',
            u"",
            1, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_BOICTRL_BOIBITPOS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_BOICTRL_BOIBITPOS, self).__init__(register,
            'BOIBITPOS', 'FRC_S.BOICTRL.BOIBITPOS', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_BOICTRL_BOIMATCHVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_BOICTRL_BOIMATCHVAL, self).__init__(register,
            'BOIMATCHVAL', 'FRC_S.BOICTRL.BOIMATCHVAL', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_DSLMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_DSLMODE, self).__init__(register,
            'DSLMODE', 'FRC_S.DSLCTRL.DSLMODE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_DSLBITORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_DSLBITORDER, self).__init__(register,
            'DSLBITORDER', 'FRC_S.DSLCTRL.DSLBITORDER', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_DSLSHIFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_DSLSHIFT, self).__init__(register,
            'DSLSHIFT', 'FRC_S.DSLCTRL.DSLSHIFT', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_DSLOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_DSLOFFSET, self).__init__(register,
            'DSLOFFSET', 'FRC_S.DSLCTRL.DSLOFFSET', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_DSLBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_DSLBITS, self).__init__(register,
            'DSLBITS', 'FRC_S.DSLCTRL.DSLBITS', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_DSLMINLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_DSLMINLENGTH, self).__init__(register,
            'DSLMINLENGTH', 'FRC_S.DSLCTRL.DSLMINLENGTH', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_RXSUPRECEPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_RXSUPRECEPMODE, self).__init__(register,
            'RXSUPRECEPMODE', 'FRC_S.DSLCTRL.RXSUPRECEPMODE', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_STORESUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_STORESUP, self).__init__(register,
            'STORESUP', 'FRC_S.DSLCTRL.STORESUP', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_DSLCTRL_SUPSHFFACTOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_DSLCTRL_SUPSHFFACTOR, self).__init__(register,
            'SUPSHFFACTOR', 'FRC_S.DSLCTRL.SUPSHFFACTOR', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WCNTCMP4_SUPPLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WCNTCMP4_SUPPLENGTH, self).__init__(register,
            'SUPPLENGTH', 'FRC_S.WCNTCMP4.SUPPLENGTH', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_WCNTCMP5_RXPAUSELOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_WCNTCMP5_RXPAUSELOC, self).__init__(register,
            'RXPAUSELOC', 'FRC_S.WCNTCMP5.RXPAUSELOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUFCTRL_PKTBUFSTARTLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUFCTRL_PKTBUFSTARTLOC, self).__init__(register,
            'PKTBUFSTARTLOC', 'FRC_S.PKTBUFCTRL.PKTBUFSTARTLOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUFCTRL_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUFCTRL_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_S.PKTBUFCTRL.PKTBUFTHRESHOLD', 'read-write',
            u"",
            12, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUFCTRL_PKTBUFTHRESHOLDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUFCTRL_PKTBUFTHRESHOLDEN, self).__init__(register,
            'PKTBUFTHRESHOLDEN', 'FRC_S.PKTBUFCTRL.PKTBUFTHRESHOLDEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUFCTRL_PKTBUFSTOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUFCTRL_PKTBUFSTOP, self).__init__(register,
            'PKTBUFSTOP', 'FRC_S.PKTBUFCTRL.PKTBUFSTOP', 'write-only',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUFSTATUS_PKTBUFCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUFSTATUS_PKTBUFCOUNT, self).__init__(register,
            'PKTBUFCOUNT', 'FRC_S.PKTBUFSTATUS.PKTBUFCOUNT', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF0_PKTBUF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF0_PKTBUF0, self).__init__(register,
            'PKTBUF0', 'FRC_S.PKTBUF0.PKTBUF0', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF0_PKTBUF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF0_PKTBUF1, self).__init__(register,
            'PKTBUF1', 'FRC_S.PKTBUF0.PKTBUF1', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF0_PKTBUF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF0_PKTBUF2, self).__init__(register,
            'PKTBUF2', 'FRC_S.PKTBUF0.PKTBUF2', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF0_PKTBUF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF0_PKTBUF3, self).__init__(register,
            'PKTBUF3', 'FRC_S.PKTBUF0.PKTBUF3', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF1_PKTBUF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF1_PKTBUF4, self).__init__(register,
            'PKTBUF4', 'FRC_S.PKTBUF1.PKTBUF4', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF1_PKTBUF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF1_PKTBUF5, self).__init__(register,
            'PKTBUF5', 'FRC_S.PKTBUF1.PKTBUF5', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF1_PKTBUF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF1_PKTBUF6, self).__init__(register,
            'PKTBUF6', 'FRC_S.PKTBUF1.PKTBUF6', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF1_PKTBUF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF1_PKTBUF7, self).__init__(register,
            'PKTBUF7', 'FRC_S.PKTBUF1.PKTBUF7', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF2_PKTBUF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF2_PKTBUF8, self).__init__(register,
            'PKTBUF8', 'FRC_S.PKTBUF2.PKTBUF8', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF2_PKTBUF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF2_PKTBUF9, self).__init__(register,
            'PKTBUF9', 'FRC_S.PKTBUF2.PKTBUF9', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF2_PKTBUF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF2_PKTBUF10, self).__init__(register,
            'PKTBUF10', 'FRC_S.PKTBUF2.PKTBUF10', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF2_PKTBUF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF2_PKTBUF11, self).__init__(register,
            'PKTBUF11', 'FRC_S.PKTBUF2.PKTBUF11', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF3_PKTBUF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF3_PKTBUF12, self).__init__(register,
            'PKTBUF12', 'FRC_S.PKTBUF3.PKTBUF12', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF3_PKTBUF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF3_PKTBUF13, self).__init__(register,
            'PKTBUF13', 'FRC_S.PKTBUF3.PKTBUF13', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF3_PKTBUF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF3_PKTBUF14, self).__init__(register,
            'PKTBUF14', 'FRC_S.PKTBUF3.PKTBUF14', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF3_PKTBUF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF3_PKTBUF15, self).__init__(register,
            'PKTBUF15', 'FRC_S.PKTBUF3.PKTBUF15', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF4_PKTBUF16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF4_PKTBUF16, self).__init__(register,
            'PKTBUF16', 'FRC_S.PKTBUF4.PKTBUF16', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF4_PKTBUF17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF4_PKTBUF17, self).__init__(register,
            'PKTBUF17', 'FRC_S.PKTBUF4.PKTBUF17', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF4_PKTBUF18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF4_PKTBUF18, self).__init__(register,
            'PKTBUF18', 'FRC_S.PKTBUF4.PKTBUF18', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF4_PKTBUF19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF4_PKTBUF19, self).__init__(register,
            'PKTBUF19', 'FRC_S.PKTBUF4.PKTBUF19', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF5_PKTBUF20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF5_PKTBUF20, self).__init__(register,
            'PKTBUF20', 'FRC_S.PKTBUF5.PKTBUF20', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF5_PKTBUF21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF5_PKTBUF21, self).__init__(register,
            'PKTBUF21', 'FRC_S.PKTBUF5.PKTBUF21', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF5_PKTBUF22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF5_PKTBUF22, self).__init__(register,
            'PKTBUF22', 'FRC_S.PKTBUF5.PKTBUF22', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF5_PKTBUF23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF5_PKTBUF23, self).__init__(register,
            'PKTBUF23', 'FRC_S.PKTBUF5.PKTBUF23', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF6_PKTBUF24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF6_PKTBUF24, self).__init__(register,
            'PKTBUF24', 'FRC_S.PKTBUF6.PKTBUF24', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF6_PKTBUF25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF6_PKTBUF25, self).__init__(register,
            'PKTBUF25', 'FRC_S.PKTBUF6.PKTBUF25', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF6_PKTBUF26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF6_PKTBUF26, self).__init__(register,
            'PKTBUF26', 'FRC_S.PKTBUF6.PKTBUF26', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF6_PKTBUF27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF6_PKTBUF27, self).__init__(register,
            'PKTBUF27', 'FRC_S.PKTBUF6.PKTBUF27', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF7_PKTBUF28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF7_PKTBUF28, self).__init__(register,
            'PKTBUF28', 'FRC_S.PKTBUF7.PKTBUF28', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF7_PKTBUF29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF7_PKTBUF29, self).__init__(register,
            'PKTBUF29', 'FRC_S.PKTBUF7.PKTBUF29', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF7_PKTBUF30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF7_PKTBUF30, self).__init__(register,
            'PKTBUF30', 'FRC_S.PKTBUF7.PKTBUF30', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF7_PKTBUF31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF7_PKTBUF31, self).__init__(register,
            'PKTBUF31', 'FRC_S.PKTBUF7.PKTBUF31', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF8_PKTBUF32(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF8_PKTBUF32, self).__init__(register,
            'PKTBUF32', 'FRC_S.PKTBUF8.PKTBUF32', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF8_PKTBUF33(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF8_PKTBUF33, self).__init__(register,
            'PKTBUF33', 'FRC_S.PKTBUF8.PKTBUF33', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF8_PKTBUF34(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF8_PKTBUF34, self).__init__(register,
            'PKTBUF34', 'FRC_S.PKTBUF8.PKTBUF34', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF8_PKTBUF35(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF8_PKTBUF35, self).__init__(register,
            'PKTBUF35', 'FRC_S.PKTBUF8.PKTBUF35', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF9_PKTBUF36(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF9_PKTBUF36, self).__init__(register,
            'PKTBUF36', 'FRC_S.PKTBUF9.PKTBUF36', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF9_PKTBUF37(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF9_PKTBUF37, self).__init__(register,
            'PKTBUF37', 'FRC_S.PKTBUF9.PKTBUF37', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF9_PKTBUF38(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF9_PKTBUF38, self).__init__(register,
            'PKTBUF38', 'FRC_S.PKTBUF9.PKTBUF38', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF9_PKTBUF39(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF9_PKTBUF39, self).__init__(register,
            'PKTBUF39', 'FRC_S.PKTBUF9.PKTBUF39', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF10_PKTBUF40(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF10_PKTBUF40, self).__init__(register,
            'PKTBUF40', 'FRC_S.PKTBUF10.PKTBUF40', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF10_PKTBUF41(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF10_PKTBUF41, self).__init__(register,
            'PKTBUF41', 'FRC_S.PKTBUF10.PKTBUF41', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF10_PKTBUF42(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF10_PKTBUF42, self).__init__(register,
            'PKTBUF42', 'FRC_S.PKTBUF10.PKTBUF42', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF10_PKTBUF43(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF10_PKTBUF43, self).__init__(register,
            'PKTBUF43', 'FRC_S.PKTBUF10.PKTBUF43', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF11_PKTBUF44(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF11_PKTBUF44, self).__init__(register,
            'PKTBUF44', 'FRC_S.PKTBUF11.PKTBUF44', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF11_PKTBUF45(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF11_PKTBUF45, self).__init__(register,
            'PKTBUF45', 'FRC_S.PKTBUF11.PKTBUF45', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF11_PKTBUF46(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF11_PKTBUF46, self).__init__(register,
            'PKTBUF46', 'FRC_S.PKTBUF11.PKTBUF46', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_PKTBUF11_PKTBUF47(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_PKTBUF11_PKTBUF47, self).__init__(register,
            'PKTBUF47', 'FRC_S.PKTBUF11.PKTBUF47', 'read-only',
            u"",
            24, 8)
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


class RM_Field_FRC_S_AHBCONFIG_AHBHPROTBUFFERABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_AHBCONFIG_AHBHPROTBUFFERABLE, self).__init__(register,
            'AHBHPROTBUFFERABLE', 'FRC_S.AHBCONFIG.AHBHPROTBUFFERABLE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_S_SPARE_SPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_S_SPARE_SPARE, self).__init__(register,
            'SPARE', 'FRC_S.SPARE.SPARE', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True



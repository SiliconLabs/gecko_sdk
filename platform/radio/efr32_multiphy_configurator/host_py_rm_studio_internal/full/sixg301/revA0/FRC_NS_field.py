
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_FRC_NS_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'FRC_NS.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_EN_EN, self).__init__(register,
            'EN', 'FRC_NS.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_SNIFFDCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_SNIFFDCOUNT, self).__init__(register,
            'SNIFFDCOUNT', 'FRC_NS.STATUS.SNIFFDCOUNT', 'read-only',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_ACTIVETXFCD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_ACTIVETXFCD, self).__init__(register,
            'ACTIVETXFCD', 'FRC_NS.STATUS.ACTIVETXFCD', 'read-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_ACTIVERXFCD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_ACTIVERXFCD, self).__init__(register,
            'ACTIVERXFCD', 'FRC_NS.STATUS.ACTIVERXFCD', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_SNIFFDFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_SNIFFDFRAME, self).__init__(register,
            'SNIFFDFRAME', 'FRC_NS.STATUS.SNIFFDFRAME', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_RXRAWBLOCKED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_RXRAWBLOCKED, self).__init__(register,
            'RXRAWBLOCKED', 'FRC_NS.STATUS.RXRAWBLOCKED', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_FRAMEOK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_FRAMEOK, self).__init__(register,
            'FRAMEOK', 'FRC_NS.STATUS.FRAMEOK', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_RXABORTINPROGRESS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_RXABORTINPROGRESS, self).__init__(register,
            'RXABORTINPROGRESS', 'FRC_NS.STATUS.RXABORTINPROGRESS', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_NS.STATUS.TXWORD', 'read-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_NS.STATUS.RXWORD', 'read-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_NS.STATUS.CONVPAUSED', 'read-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_NS.STATUS.TXSUBFRAMEPAUSED', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_NS.STATUS.INTERLEAVEREADPAUSED', 'read-only',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_NS.STATUS.INTERLEAVEWRITEPAUSED', 'read-only',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_NS.STATUS.FRAMEDETPAUSED', 'read-only',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_FRAMELENGTHERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_FRAMELENGTHERROR, self).__init__(register,
            'FRAMELENGTHERROR', 'FRC_NS.STATUS.FRAMELENGTHERROR', 'read-only',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_DEMODERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_DEMODERROR, self).__init__(register,
            'DEMODERROR', 'FRC_NS.STATUS.DEMODERROR', 'read-only',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_FSMSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_FSMSTATE, self).__init__(register,
            'FSMSTATE', 'FRC_NS.STATUS.FSMSTATE', 'read-only',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_RXWCNTMATCHPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_RXWCNTMATCHPAUSED, self).__init__(register,
            'RXWCNTMATCHPAUSED', 'FRC_NS.STATUS.RXWCNTMATCHPAUSED', 'read-only',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_STATUS_CRCERRORTOLERATED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_STATUS_CRCERRORTOLERATED, self).__init__(register,
            'CRCERRORTOLERATED', 'FRC_NS.STATUS.CRCERRORTOLERATED', 'read-only',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DFLCTRL_DFLMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DFLCTRL_DFLMODE, self).__init__(register,
            'DFLMODE', 'FRC_NS.DFLCTRL.DFLMODE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DFLCTRL_DFLBITORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DFLCTRL_DFLBITORDER, self).__init__(register,
            'DFLBITORDER', 'FRC_NS.DFLCTRL.DFLBITORDER', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DFLCTRL_DFLSHIFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DFLCTRL_DFLSHIFT, self).__init__(register,
            'DFLSHIFT', 'FRC_NS.DFLCTRL.DFLSHIFT', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DFLCTRL_DFLOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DFLCTRL_DFLOFFSET, self).__init__(register,
            'DFLOFFSET', 'FRC_NS.DFLCTRL.DFLOFFSET', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DFLCTRL_DFLBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DFLCTRL_DFLBITS, self).__init__(register,
            'DFLBITS', 'FRC_NS.DFLCTRL.DFLBITS', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DFLCTRL_MINLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DFLCTRL_MINLENGTH, self).__init__(register,
            'MINLENGTH', 'FRC_NS.DFLCTRL.MINLENGTH', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DFLCTRL_DFLINCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DFLCTRL_DFLINCLUDECRC, self).__init__(register,
            'DFLINCLUDECRC', 'FRC_NS.DFLCTRL.DFLINCLUDECRC', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DFLCTRL_DFLBOIOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DFLCTRL_DFLBOIOFFSET, self).__init__(register,
            'DFLBOIOFFSET', 'FRC_NS.DFLCTRL.DFLBOIOFFSET', 'read-write',
            u"",
            21, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_MAXLENGTH_MAXLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_MAXLENGTH_MAXLENGTH, self).__init__(register,
            'MAXLENGTH', 'FRC_NS.MAXLENGTH.MAXLENGTH', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_MAXLENGTH_INILENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_MAXLENGTH_INILENGTH, self).__init__(register,
            'INILENGTH', 'FRC_NS.MAXLENGTH.INILENGTH', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_ADDRFILTCTRL_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_ADDRFILTCTRL_EN, self).__init__(register,
            'EN', 'FRC_NS.ADDRFILTCTRL.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_ADDRFILTCTRL_BRDCST00EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_ADDRFILTCTRL_BRDCST00EN, self).__init__(register,
            'BRDCST00EN', 'FRC_NS.ADDRFILTCTRL.BRDCST00EN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_ADDRFILTCTRL_BRDCSTFFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_ADDRFILTCTRL_BRDCSTFFEN, self).__init__(register,
            'BRDCSTFFEN', 'FRC_NS.ADDRFILTCTRL.BRDCSTFFEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_ADDRFILTCTRL_ADDRESS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_ADDRFILTCTRL_ADDRESS, self).__init__(register,
            'ADDRESS', 'FRC_NS.ADDRFILTCTRL.ADDRESS', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DATABUFFER_DATABUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DATABUFFER_DATABUFFER, self).__init__(register,
            'DATABUFFER', 'FRC_NS.DATABUFFER.DATABUFFER', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WCNT_WCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WCNT_WCNT, self).__init__(register,
            'WCNT', 'FRC_NS.WCNT.WCNT', 'read-only',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WCNTCMP0_FRAMELENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WCNTCMP0_FRAMELENGTH, self).__init__(register,
            'FRAMELENGTH', 'FRC_NS.WCNTCMP0.FRAMELENGTH', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WCNTCMP1_LENGTHFIELDLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WCNTCMP1_LENGTHFIELDLOC, self).__init__(register,
            'LENGTHFIELDLOC', 'FRC_NS.WCNTCMP1.LENGTHFIELDLOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WCNTCMP2_ADDRFIELDLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WCNTCMP2_ADDRFIELDLOC, self).__init__(register,
            'ADDRFIELDLOC', 'FRC_NS.WCNTCMP2.ADDRFIELDLOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_RXABORT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_RXABORT, self).__init__(register,
            'RXABORT', 'FRC_NS.CMD.RXABORT', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_FRAMEDETRESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_FRAMEDETRESUME, self).__init__(register,
            'FRAMEDETRESUME', 'FRC_NS.CMD.FRAMEDETRESUME', 'write-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_INTERLEAVEWRITERESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_INTERLEAVEWRITERESUME, self).__init__(register,
            'INTERLEAVEWRITERESUME', 'FRC_NS.CMD.INTERLEAVEWRITERESUME', 'write-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_INTERLEAVEREADRESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_INTERLEAVEREADRESUME, self).__init__(register,
            'INTERLEAVEREADRESUME', 'FRC_NS.CMD.INTERLEAVEREADRESUME', 'write-only',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_CONVRESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_CONVRESUME, self).__init__(register,
            'CONVRESUME', 'FRC_NS.CMD.CONVRESUME', 'write-only',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_CONVTERMINATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_CONVTERMINATE, self).__init__(register,
            'CONVTERMINATE', 'FRC_NS.CMD.CONVTERMINATE', 'write-only',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_TXSUBFRAMERESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_TXSUBFRAMERESUME, self).__init__(register,
            'TXSUBFRAMERESUME', 'FRC_NS.CMD.TXSUBFRAMERESUME', 'write-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_INTERLEAVEINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_INTERLEAVEINIT, self).__init__(register,
            'INTERLEAVEINIT', 'FRC_NS.CMD.INTERLEAVEINIT', 'write-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_INTERLEAVECNTCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_INTERLEAVECNTCLEAR, self).__init__(register,
            'INTERLEAVECNTCLEAR', 'FRC_NS.CMD.INTERLEAVECNTCLEAR', 'write-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_CONVINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_CONVINIT, self).__init__(register,
            'CONVINIT', 'FRC_NS.CMD.CONVINIT', 'write-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_BLOCKINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_BLOCKINIT, self).__init__(register,
            'BLOCKINIT', 'FRC_NS.CMD.BLOCKINIT', 'write-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_STATEINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_STATEINIT, self).__init__(register,
            'STATEINIT', 'FRC_NS.CMD.STATEINIT', 'write-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_RXRAWUNBLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_RXRAWUNBLOCK, self).__init__(register,
            'RXRAWUNBLOCK', 'FRC_NS.CMD.RXRAWUNBLOCK', 'write-only',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CMD_RXPAUSERESUME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CMD_RXPAUSERESUME, self).__init__(register,
            'RXPAUSERESUME', 'FRC_NS.CMD.RXPAUSERESUME', 'write-only',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WHITECTRL_FEEDBACKSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WHITECTRL_FEEDBACKSEL, self).__init__(register,
            'FEEDBACKSEL', 'FRC_NS.WHITECTRL.FEEDBACKSEL', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WHITECTRL_XORFEEDBACK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WHITECTRL_XORFEEDBACK, self).__init__(register,
            'XORFEEDBACK', 'FRC_NS.WHITECTRL.XORFEEDBACK', 'read-write',
            u"",
            5, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WHITECTRL_SHROUTPUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WHITECTRL_SHROUTPUTSEL, self).__init__(register,
            'SHROUTPUTSEL', 'FRC_NS.WHITECTRL.SHROUTPUTSEL', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WHITECTRL_BLOCKERRORCORRECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WHITECTRL_BLOCKERRORCORRECT, self).__init__(register,
            'BLOCKERRORCORRECT', 'FRC_NS.WHITECTRL.BLOCKERRORCORRECT', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WHITEPOLY_POLY(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WHITEPOLY_POLY, self).__init__(register,
            'POLY', 'FRC_NS.WHITEPOLY.POLY', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WHITEINIT_WHITEINIT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WHITEINIT_WHITEINIT, self).__init__(register,
            'WHITEINIT', 'FRC_NS.WHITEINIT.WHITEINIT', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_BLOCKWHITEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_BLOCKWHITEMODE, self).__init__(register,
            'BLOCKWHITEMODE', 'FRC_NS.FECCTRL.BLOCKWHITEMODE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_CONVMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_CONVMODE, self).__init__(register,
            'CONVMODE', 'FRC_NS.FECCTRL.CONVMODE', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_CONVDECODEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_CONVDECODEMODE, self).__init__(register,
            'CONVDECODEMODE', 'FRC_NS.FECCTRL.CONVDECODEMODE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_CONVTRACEBACKDISABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_CONVTRACEBACKDISABLE, self).__init__(register,
            'CONVTRACEBACKDISABLE', 'FRC_NS.FECCTRL.CONVTRACEBACKDISABLE', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_CONVINV(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_CONVINV, self).__init__(register,
            'CONVINV', 'FRC_NS.FECCTRL.CONVINV', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_INTERLEAVEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_INTERLEAVEMODE, self).__init__(register,
            'INTERLEAVEMODE', 'FRC_NS.FECCTRL.INTERLEAVEMODE', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_INTERLEAVEFIRSTINDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_INTERLEAVEFIRSTINDEX, self).__init__(register,
            'INTERLEAVEFIRSTINDEX', 'FRC_NS.FECCTRL.INTERLEAVEFIRSTINDEX', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_INTERLEAVEWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_INTERLEAVEWIDTH, self).__init__(register,
            'INTERLEAVEWIDTH', 'FRC_NS.FECCTRL.INTERLEAVEWIDTH', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_CONVBUSLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_CONVBUSLOCK, self).__init__(register,
            'CONVBUSLOCK', 'FRC_NS.FECCTRL.CONVBUSLOCK', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_CONVSUBFRAMETERMINATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_CONVSUBFRAMETERMINATE, self).__init__(register,
            'CONVSUBFRAMETERMINATE', 'FRC_NS.FECCTRL.CONVSUBFRAMETERMINATE', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_SINGLEBLOCK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_SINGLEBLOCK, self).__init__(register,
            'SINGLEBLOCK', 'FRC_NS.FECCTRL.SINGLEBLOCK', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_FORCE2FSK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_FORCE2FSK, self).__init__(register,
            'FORCE2FSK', 'FRC_NS.FECCTRL.FORCE2FSK', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FECCTRL_CONVHARDERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FECCTRL_CONVHARDERROR, self).__init__(register,
            'CONVHARDERROR', 'FRC_NS.FECCTRL.CONVHARDERROR', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_BLOCKRAMADDR_BLOCKRAMADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_BLOCKRAMADDR_BLOCKRAMADDR, self).__init__(register,
            'BLOCKRAMADDR', 'FRC_NS.BLOCKRAMADDR.BLOCKRAMADDR', 'read-write',
            u"",
            2, 30)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CONVRAMADDR_CONVRAMADDR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CONVRAMADDR_CONVRAMADDR, self).__init__(register,
            'CONVRAMADDR', 'FRC_NS.CONVRAMADDR.CONVRAMADDR', 'read-write',
            u"",
            2, 30)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_RANDOMTX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_RANDOMTX, self).__init__(register,
            'RANDOMTX', 'FRC_NS.CTRL.RANDOMTX', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_UARTMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_UARTMODE, self).__init__(register,
            'UARTMODE', 'FRC_NS.CTRL.UARTMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_BITORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_BITORDER, self).__init__(register,
            'BITORDER', 'FRC_NS.CTRL.BITORDER', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_LSBFRTREVERT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_LSBFRTREVERT, self).__init__(register,
            'LSBFRTREVERT', 'FRC_NS.CTRL.LSBFRTREVERT', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_TXFCDMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_TXFCDMODE, self).__init__(register,
            'TXFCDMODE', 'FRC_NS.CTRL.TXFCDMODE', 'read-write',
            u"",
            4, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_RXFCDMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_RXFCDMODE, self).__init__(register,
            'RXFCDMODE', 'FRC_NS.CTRL.RXFCDMODE', 'read-write',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_BITSPERWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_BITSPERWORD, self).__init__(register,
            'BITSPERWORD', 'FRC_NS.CTRL.BITSPERWORD', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_RATESELECT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_RATESELECT, self).__init__(register,
            'RATESELECT', 'FRC_NS.CTRL.RATESELECT', 'read-write',
            u"",
            11, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_TXPREFETCH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_TXPREFETCH, self).__init__(register,
            'TXPREFETCH', 'FRC_NS.CTRL.TXPREFETCH', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_TXFETCHBLOCKING(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_TXFETCHBLOCKING, self).__init__(register,
            'TXFETCHBLOCKING', 'FRC_NS.CTRL.TXFETCHBLOCKING', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_SEQHANDSHAKE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_SEQHANDSHAKE, self).__init__(register,
            'SEQHANDSHAKE', 'FRC_NS.CTRL.SEQHANDSHAKE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_PRBSTEST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_PRBSTEST, self).__init__(register,
            'PRBSTEST', 'FRC_NS.CTRL.PRBSTEST', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_LPMODEDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_LPMODEDIS, self).__init__(register,
            'LPMODEDIS', 'FRC_NS.CTRL.LPMODEDIS', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_WAITEOFEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_WAITEOFEN, self).__init__(register,
            'WAITEOFEN', 'FRC_NS.CTRL.WAITEOFEN', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_RXABORTIGNOREDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_RXABORTIGNOREDIS, self).__init__(register,
            'RXABORTIGNOREDIS', 'FRC_NS.CTRL.RXABORTIGNOREDIS', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_FRAMEENDAHEADDIS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_FRAMEENDAHEADDIS, self).__init__(register,
            'FRAMEENDAHEADDIS', 'FRC_NS.CTRL.FRAMEENDAHEADDIS', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_SKIPTXTRAILDATAWHITEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_SKIPTXTRAILDATAWHITEN, self).__init__(register,
            'SKIPTXTRAILDATAWHITEN', 'FRC_NS.CTRL.SKIPTXTRAILDATAWHITEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_SKIPRXSUPSTATEWHITEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_SKIPRXSUPSTATEWHITEN, self).__init__(register,
            'SKIPRXSUPSTATEWHITEN', 'FRC_NS.CTRL.SKIPRXSUPSTATEWHITEN', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_HOLDTXTRAILDATAACTIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_HOLDTXTRAILDATAACTIVE, self).__init__(register,
            'HOLDTXTRAILDATAACTIVE', 'FRC_NS.CTRL.HOLDTXTRAILDATAACTIVE', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CTRL_LPMODEEXTEND(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CTRL_LPMODEEXTEND, self).__init__(register,
            'LPMODEEXTEND', 'FRC_NS.CTRL.LPMODEEXTEND', 'read-write',
            u"",
            27, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_STORECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_STORECRC, self).__init__(register,
            'STORECRC', 'FRC_NS.RXCTRL.STORECRC', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_ACCEPTCRCERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_ACCEPTCRCERRORS, self).__init__(register,
            'ACCEPTCRCERRORS', 'FRC_NS.RXCTRL.ACCEPTCRCERRORS', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_ACCEPTBLOCKERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_ACCEPTBLOCKERRORS, self).__init__(register,
            'ACCEPTBLOCKERRORS', 'FRC_NS.RXCTRL.ACCEPTBLOCKERRORS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_TRACKABFRAME(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_TRACKABFRAME, self).__init__(register,
            'TRACKABFRAME', 'FRC_NS.RXCTRL.TRACKABFRAME', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_BUFCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_BUFCLEAR, self).__init__(register,
            'BUFCLEAR', 'FRC_NS.RXCTRL.BUFCLEAR', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_BUFRESTOREFRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_BUFRESTOREFRAMEERROR, self).__init__(register,
            'BUFRESTOREFRAMEERROR', 'FRC_NS.RXCTRL.BUFRESTOREFRAMEERROR', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_BUFRESTORERXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_BUFRESTORERXABORTED, self).__init__(register,
            'BUFRESTORERXABORTED', 'FRC_NS.RXCTRL.BUFRESTORERXABORTED', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_RXFRAMEENDAHEADBYTES(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_RXFRAMEENDAHEADBYTES, self).__init__(register,
            'RXFRAMEENDAHEADBYTES', 'FRC_NS.RXCTRL.RXFRAMEENDAHEADBYTES', 'read-write',
            u"",
            7, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_ACCEPTUARTERRORS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_ACCEPTUARTERRORS, self).__init__(register,
            'ACCEPTUARTERRORS', 'FRC_NS.RXCTRL.ACCEPTUARTERRORS', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXCTRL_IFINPUTWIDTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXCTRL_IFINPUTWIDTH, self).__init__(register,
            'IFINPUTWIDTH', 'FRC_NS.RXCTRL.IFINPUTWIDTH', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILTXDATACTRL_TRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILTXDATACTRL_TRAILTXDATA, self).__init__(register,
            'TRAILTXDATA', 'FRC_NS.TRAILTXDATACTRL.TRAILTXDATA', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILTXDATACTRL_TRAILTXDATACNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILTXDATACTRL_TRAILTXDATACNT, self).__init__(register,
            'TRAILTXDATACNT', 'FRC_NS.TRAILTXDATACTRL.TRAILTXDATACNT', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILTXDATACTRL_TRAILTXDATAFORCE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILTXDATACTRL_TRAILTXDATAFORCE, self).__init__(register,
            'TRAILTXDATAFORCE', 'FRC_NS.TRAILTXDATACTRL.TRAILTXDATAFORCE', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILTXDATACTRL_TRAILTXREPLEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILTXDATACTRL_TRAILTXREPLEN, self).__init__(register,
            'TRAILTXREPLEN', 'FRC_NS.TRAILTXDATACTRL.TRAILTXREPLEN', 'read-write',
            u"",
            12, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILTXDATACTRL_TXSUPPLENOVERIDE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILTXDATACTRL_TXSUPPLENOVERIDE, self).__init__(register,
            'TXSUPPLENOVERIDE', 'FRC_NS.TRAILTXDATACTRL.TXSUPPLENOVERIDE', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILTXDATACTRL_POSTAMBLEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILTXDATACTRL_POSTAMBLEEN, self).__init__(register,
            'POSTAMBLEEN', 'FRC_NS.TRAILTXDATACTRL.POSTAMBLEEN', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILRXDATA_RSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILRXDATA_RSSI, self).__init__(register,
            'RSSI', 'FRC_NS.TRAILRXDATA.RSSI', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILRXDATA_CRCOK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILRXDATA_CRCOK, self).__init__(register,
            'CRCOK', 'FRC_NS.TRAILRXDATA.CRCOK', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILRXDATA_PROTIMERCC0BASE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILRXDATA_PROTIMERCC0BASE, self).__init__(register,
            'PROTIMERCC0BASE', 'FRC_NS.TRAILRXDATA.PROTIMERCC0BASE', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILRXDATA_PROTIMERCC0WRAPL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILRXDATA_PROTIMERCC0WRAPL, self).__init__(register,
            'PROTIMERCC0WRAPL', 'FRC_NS.TRAILRXDATA.PROTIMERCC0WRAPL', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILRXDATA_PROTIMERCC0WRAPH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILRXDATA_PROTIMERCC0WRAPH, self).__init__(register,
            'PROTIMERCC0WRAPH', 'FRC_NS.TRAILRXDATA.PROTIMERCC0WRAPH', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_TRAILRXDATA_RTCSTAMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_TRAILRXDATA_RTCSTAMP, self).__init__(register,
            'RTCSTAMP', 'FRC_NS.TRAILRXDATA.RTCSTAMP', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SCNT_SCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SCNT_SCNT, self).__init__(register,
            'SCNT', 'FRC_NS.SCNT.SCNT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CONVGENERATOR_GENERATOR0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CONVGENERATOR_GENERATOR0, self).__init__(register,
            'GENERATOR0', 'FRC_NS.CONVGENERATOR.GENERATOR0', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CONVGENERATOR_GENERATOR1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CONVGENERATOR_GENERATOR1, self).__init__(register,
            'GENERATOR1', 'FRC_NS.CONVGENERATOR.GENERATOR1', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CONVGENERATOR_RECURSIVE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CONVGENERATOR_RECURSIVE, self).__init__(register,
            'RECURSIVE', 'FRC_NS.CONVGENERATOR.RECURSIVE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CONVGENERATOR_NONSYSTEMATIC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CONVGENERATOR_NONSYSTEMATIC, self).__init__(register,
            'NONSYSTEMATIC', 'FRC_NS.CONVGENERATOR.NONSYSTEMATIC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PUNCTCTRL_PUNCT0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PUNCTCTRL_PUNCT0, self).__init__(register,
            'PUNCT0', 'FRC_NS.PUNCTCTRL.PUNCT0', 'read-write',
            u"",
            0, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PUNCTCTRL_PUNCT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PUNCTCTRL_PUNCT1, self).__init__(register,
            'PUNCT1', 'FRC_NS.PUNCTCTRL.PUNCT1', 'read-write',
            u"",
            8, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_FRAMEDETPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_FRAMEDETPAUSEEN, self).__init__(register,
            'FRAMEDETPAUSEEN', 'FRC_NS.PAUSECTRL.FRAMEDETPAUSEEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_TXINTERLEAVEWRITEPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_TXINTERLEAVEWRITEPAUSEEN, self).__init__(register,
            'TXINTERLEAVEWRITEPAUSEEN', 'FRC_NS.PAUSECTRL.TXINTERLEAVEWRITEPAUSEEN', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_RXINTERLEAVEWRITEPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_RXINTERLEAVEWRITEPAUSEEN, self).__init__(register,
            'RXINTERLEAVEWRITEPAUSEEN', 'FRC_NS.PAUSECTRL.RXINTERLEAVEWRITEPAUSEEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_INTERLEAVEREADPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_INTERLEAVEREADPAUSEEN, self).__init__(register,
            'INTERLEAVEREADPAUSEEN', 'FRC_NS.PAUSECTRL.INTERLEAVEREADPAUSEEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_TXSUBFRAMEPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_TXSUBFRAMEPAUSEEN, self).__init__(register,
            'TXSUBFRAMEPAUSEEN', 'FRC_NS.PAUSECTRL.TXSUBFRAMEPAUSEEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_RXWCNTMATCHPAUSEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_RXWCNTMATCHPAUSEEN, self).__init__(register,
            'RXWCNTMATCHPAUSEEN', 'FRC_NS.PAUSECTRL.RXWCNTMATCHPAUSEEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_CONVPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_CONVPAUSECNT, self).__init__(register,
            'CONVPAUSECNT', 'FRC_NS.PAUSECTRL.CONVPAUSECNT', 'read-write',
            u"",
            11, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_INTERLEAVEWRITEPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_INTERLEAVEWRITEPAUSECNT, self).__init__(register,
            'INTERLEAVEWRITEPAUSECNT', 'FRC_NS.PAUSECTRL.INTERLEAVEWRITEPAUSECNT', 'read-write',
            u"",
            17, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSECTRL_INTERLEAVEREADPAUSECNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSECTRL_INTERLEAVEREADPAUSECNT, self).__init__(register,
            'INTERLEAVEREADPAUSECNT', 'FRC_NS.PAUSECTRL.INTERLEAVEREADPAUSECNT', 'read-write',
            u"",
            22, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_NS.IF.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_NS.IF.TXAFTERFRAMEDONE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_NS.IF.TXABORTED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_TXUF, self).__init__(register,
            'TXUF', 'FRC_NS.IF.TXUF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_NS.IF.RXDONE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_NS.IF.RXABORTED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_NS.IF.FRAMEERROR', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_NS.IF.BLOCKERROR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_RXOF, self).__init__(register,
            'RXOF', 'FRC_NS.IF.RXOF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_WCNTCMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_WCNTCMP0, self).__init__(register,
            'WCNTCMP0', 'FRC_NS.IF.WCNTCMP0', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_WCNTCMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_WCNTCMP1, self).__init__(register,
            'WCNTCMP1', 'FRC_NS.IF.WCNTCMP1', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_WCNTCMP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_WCNTCMP2, self).__init__(register,
            'WCNTCMP2', 'FRC_NS.IF.WCNTCMP2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_NS.IF.ADDRERROR', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_NS.IF.BUSERROR', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_RXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_RXRAWEVENT, self).__init__(register,
            'RXRAWEVENT', 'FRC_NS.IF.RXRAWEVENT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_TXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_TXRAWEVENT, self).__init__(register,
            'TXRAWEVENT', 'FRC_NS.IF.TXRAWEVENT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_NS.IF.SNIFFOF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_WCNTCMP3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_WCNTCMP3, self).__init__(register,
            'WCNTCMP3', 'FRC_NS.IF.WCNTCMP3', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_WCNTCMP4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_WCNTCMP4, self).__init__(register,
            'WCNTCMP4', 'FRC_NS.IF.WCNTCMP4', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_BOISET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_BOISET, self).__init__(register,
            'BOISET', 'FRC_NS.IF.BOISET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_PKTBUFSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_PKTBUFSTART, self).__init__(register,
            'PKTBUFSTART', 'FRC_NS.IF.PKTBUFSTART', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_NS.IF.PKTBUFTHRESHOLD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_RXRAWOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_RXRAWOF, self).__init__(register,
            'RXRAWOF', 'FRC_NS.IF.RXRAWOF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_WCNTCMP5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_WCNTCMP5, self).__init__(register,
            'WCNTCMP5', 'FRC_NS.IF.WCNTCMP5', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_NS.IF.FRAMEDETPAUSED', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_NS.IF.INTERLEAVEWRITEPAUSED', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_NS.IF.INTERLEAVEREADPAUSED', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_NS.IF.TXSUBFRAMEPAUSED', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_NS.IF.CONVPAUSED', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_NS.IF.RXWORD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_NS.IF.TXWORD', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IF_UARTERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IF_UARTERROR, self).__init__(register,
            'UARTERROR', 'FRC_NS.IF.UARTERROR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_NS.IEN.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_NS.IEN.TXAFTERFRAMEDONE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_NS.IEN.TXABORTED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_TXUF, self).__init__(register,
            'TXUF', 'FRC_NS.IEN.TXUF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_NS.IEN.RXDONE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_NS.IEN.RXABORTED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_NS.IEN.FRAMEERROR', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_NS.IEN.BLOCKERROR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_RXOF, self).__init__(register,
            'RXOF', 'FRC_NS.IEN.RXOF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_WCNTCMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_WCNTCMP0, self).__init__(register,
            'WCNTCMP0', 'FRC_NS.IEN.WCNTCMP0', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_WCNTCMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_WCNTCMP1, self).__init__(register,
            'WCNTCMP1', 'FRC_NS.IEN.WCNTCMP1', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_WCNTCMP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_WCNTCMP2, self).__init__(register,
            'WCNTCMP2', 'FRC_NS.IEN.WCNTCMP2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_NS.IEN.ADDRERROR', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_NS.IEN.BUSERROR', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_RXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_RXRAWEVENT, self).__init__(register,
            'RXRAWEVENT', 'FRC_NS.IEN.RXRAWEVENT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_TXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_TXRAWEVENT, self).__init__(register,
            'TXRAWEVENT', 'FRC_NS.IEN.TXRAWEVENT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_NS.IEN.SNIFFOF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_WCNTCMP3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_WCNTCMP3, self).__init__(register,
            'WCNTCMP3', 'FRC_NS.IEN.WCNTCMP3', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_WCNTCMP4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_WCNTCMP4, self).__init__(register,
            'WCNTCMP4', 'FRC_NS.IEN.WCNTCMP4', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_BOISET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_BOISET, self).__init__(register,
            'BOISET', 'FRC_NS.IEN.BOISET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_PKTBUFSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_PKTBUFSTART, self).__init__(register,
            'PKTBUFSTART', 'FRC_NS.IEN.PKTBUFSTART', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_NS.IEN.PKTBUFTHRESHOLD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_RXRAWOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_RXRAWOF, self).__init__(register,
            'RXRAWOF', 'FRC_NS.IEN.RXRAWOF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_WCNTCMP5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_WCNTCMP5, self).__init__(register,
            'WCNTCMP5', 'FRC_NS.IEN.WCNTCMP5', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_NS.IEN.FRAMEDETPAUSED', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_NS.IEN.INTERLEAVEWRITEPAUSED', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_NS.IEN.INTERLEAVEREADPAUSED', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_NS.IEN.TXSUBFRAMEPAUSED', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_NS.IEN.CONVPAUSED', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_NS.IEN.RXWORD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_NS.IEN.TXWORD', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_IEN_UARTERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_IEN_UARTERROR, self).__init__(register,
            'UARTERROR', 'FRC_NS.IEN.UARTERROR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_OTACNT_OTARXCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_OTACNT_OTARXCNT, self).__init__(register,
            'OTARXCNT', 'FRC_NS.OTACNT.OTARXCNT', 'read-only',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_OTACNT_OTATXCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_OTACNT_OTATXCNT, self).__init__(register,
            'OTATXCNT', 'FRC_NS.OTACNT.OTATXCNT', 'read-only',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_BUFFERMODE_TXBUFFERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_BUFFERMODE_TXBUFFERMODE, self).__init__(register,
            'TXBUFFERMODE', 'FRC_NS.BUFFERMODE.TXBUFFERMODE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_BUFFERMODE_RXBUFFERMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_BUFFERMODE_RXBUFFERMODE, self).__init__(register,
            'RXBUFFERMODE', 'FRC_NS.BUFFERMODE.RXBUFFERMODE', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_BUFFERMODE_RXFRCBUFMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_BUFFERMODE_RXFRCBUFMUX, self).__init__(register,
            'RXFRCBUFMUX', 'FRC_NS.BUFFERMODE.RXFRCBUFMUX', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFMODE, self).__init__(register,
            'SNIFFMODE', 'FRC_NS.SNIFFCTRL.SNIFFMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFBITS, self).__init__(register,
            'SNIFFBITS', 'FRC_NS.SNIFFCTRL.SNIFFBITS', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFRXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFRXDATA, self).__init__(register,
            'SNIFFRXDATA', 'FRC_NS.SNIFFCTRL.SNIFFRXDATA', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFTXDATA, self).__init__(register,
            'SNIFFTXDATA', 'FRC_NS.SNIFFCTRL.SNIFFTXDATA', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFRSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFRSSI, self).__init__(register,
            'SNIFFRSSI', 'FRC_NS.SNIFFCTRL.SNIFFRSSI', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFSTATE, self).__init__(register,
            'SNIFFSTATE', 'FRC_NS.SNIFFCTRL.SNIFFSTATE', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFAUXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFAUXDATA, self).__init__(register,
            'SNIFFAUXDATA', 'FRC_NS.SNIFFCTRL.SNIFFAUXDATA', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFBR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFBR, self).__init__(register,
            'SNIFFBR', 'FRC_NS.SNIFFCTRL.SNIFFBR', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFSLEEPCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFSLEEPCTRL, self).__init__(register,
            'SNIFFSLEEPCTRL', 'FRC_NS.SNIFFCTRL.SNIFFSLEEPCTRL', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFSYNCWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFSYNCWORD, self).__init__(register,
            'SNIFFSYNCWORD', 'FRC_NS.SNIFFCTRL.SNIFFSYNCWORD', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SNIFFCTRL_SNIFFRACSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SNIFFCTRL_SNIFFRACSTATE, self).__init__(register,
            'SNIFFRACSTATE', 'FRC_NS.SNIFFCTRL.SNIFFRACSTATE', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_AUXDATA_AUXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_AUXDATA_AUXDATA, self).__init__(register,
            'AUXDATA', 'FRC_NS.AUXDATA.AUXDATA', 'write-only',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RAWCTRL_TXRAWMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RAWCTRL_TXRAWMODE, self).__init__(register,
            'TXRAWMODE', 'FRC_NS.RAWCTRL.TXRAWMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RAWCTRL_RXRAWMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RAWCTRL_RXRAWMODE, self).__init__(register,
            'RXRAWMODE', 'FRC_NS.RAWCTRL.RXRAWMODE', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RAWCTRL_RXRAWRANDOM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RAWCTRL_RXRAWRANDOM, self).__init__(register,
            'RXRAWRANDOM', 'FRC_NS.RAWCTRL.RXRAWRANDOM', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RAWCTRL_RXRAWTRIGGER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RAWCTRL_RXRAWTRIGGER, self).__init__(register,
            'RXRAWTRIGGER', 'FRC_NS.RAWCTRL.RXRAWTRIGGER', 'read-write',
            u"",
            7, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RAWCTRL_DEMODRAWDATAMUX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RAWCTRL_DEMODRAWDATAMUX, self).__init__(register,
            'DEMODRAWDATAMUX', 'FRC_NS.RAWCTRL.DEMODRAWDATAMUX', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_RXRAWDATA_RXRAWDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_RXRAWDATA_RXRAWDATA, self).__init__(register,
            'RXRAWDATA', 'FRC_NS.RXRAWDATA.RXRAWDATA', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PAUSEDATA_PAUSEDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PAUSEDATA_PAUSEDATA, self).__init__(register,
            'PAUSEDATA', 'FRC_NS.PAUSEDATA.PAUSEDATA', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_LIKELYCONVSTATE_LIKELYCONVSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_LIKELYCONVSTATE_LIKELYCONVSTATE, self).__init__(register,
            'LIKELYCONVSTATE', 'FRC_NS.LIKELYCONVSTATE.LIKELYCONVSTATE', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENTNEXT_INTELEMENTNEXT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENTNEXT_INTELEMENTNEXT, self).__init__(register,
            'INTELEMENTNEXT', 'FRC_NS.INTELEMENTNEXT.INTELEMENTNEXT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTWRITEPOINT_INTWRITEPOINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTWRITEPOINT_INTWRITEPOINT, self).__init__(register,
            'INTWRITEPOINT', 'FRC_NS.INTWRITEPOINT.INTWRITEPOINT', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTREADPOINT_INTREADPOINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTREADPOINT_INTREADPOINT, self).__init__(register,
            'INTREADPOINT', 'FRC_NS.INTREADPOINT.INTREADPOINT', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_AUTOCG_AUTOCGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_AUTOCG_AUTOCGEN, self).__init__(register,
            'AUTOCGEN', 'FRC_NS.AUTOCG.AUTOCGEN', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_CGCLKSTOP_FORCEOFF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_CGCLKSTOP_FORCEOFF, self).__init__(register,
            'FORCEOFF', 'FRC_NS.CGCLKSTOP.FORCEOFF', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_NS.SEQIF.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_NS.SEQIF.TXAFTERFRAMEDONE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_NS.SEQIF.TXABORTED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_TXUF, self).__init__(register,
            'TXUF', 'FRC_NS.SEQIF.TXUF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_NS.SEQIF.RXDONE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_NS.SEQIF.RXABORTED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_NS.SEQIF.FRAMEERROR', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_NS.SEQIF.BLOCKERROR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_RXOF, self).__init__(register,
            'RXOF', 'FRC_NS.SEQIF.RXOF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_WCNTCMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_WCNTCMP0, self).__init__(register,
            'WCNTCMP0', 'FRC_NS.SEQIF.WCNTCMP0', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_WCNTCMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_WCNTCMP1, self).__init__(register,
            'WCNTCMP1', 'FRC_NS.SEQIF.WCNTCMP1', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_WCNTCMP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_WCNTCMP2, self).__init__(register,
            'WCNTCMP2', 'FRC_NS.SEQIF.WCNTCMP2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_NS.SEQIF.ADDRERROR', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_NS.SEQIF.BUSERROR', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_RXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_RXRAWEVENT, self).__init__(register,
            'RXRAWEVENT', 'FRC_NS.SEQIF.RXRAWEVENT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_TXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_TXRAWEVENT, self).__init__(register,
            'TXRAWEVENT', 'FRC_NS.SEQIF.TXRAWEVENT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_NS.SEQIF.SNIFFOF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_WCNTCMP3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_WCNTCMP3, self).__init__(register,
            'WCNTCMP3', 'FRC_NS.SEQIF.WCNTCMP3', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_WCNTCMP4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_WCNTCMP4, self).__init__(register,
            'WCNTCMP4', 'FRC_NS.SEQIF.WCNTCMP4', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_BOISET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_BOISET, self).__init__(register,
            'BOISET', 'FRC_NS.SEQIF.BOISET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_PKTBUFSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_PKTBUFSTART, self).__init__(register,
            'PKTBUFSTART', 'FRC_NS.SEQIF.PKTBUFSTART', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_NS.SEQIF.PKTBUFTHRESHOLD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_RXRAWOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_RXRAWOF, self).__init__(register,
            'RXRAWOF', 'FRC_NS.SEQIF.RXRAWOF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_WCNTCMP5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_WCNTCMP5, self).__init__(register,
            'WCNTCMP5', 'FRC_NS.SEQIF.WCNTCMP5', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_NS.SEQIF.FRAMEDETPAUSED', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_NS.SEQIF.INTERLEAVEWRITEPAUSED', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_NS.SEQIF.INTERLEAVEREADPAUSED', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_NS.SEQIF.TXSUBFRAMEPAUSED', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_NS.SEQIF.CONVPAUSED', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_NS.SEQIF.RXWORD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_NS.SEQIF.TXWORD', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIF_UARTERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIF_UARTERROR, self).__init__(register,
            'UARTERROR', 'FRC_NS.SEQIF.UARTERROR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_TXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_TXDONE, self).__init__(register,
            'TXDONE', 'FRC_NS.SEQIEN.TXDONE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_TXAFTERFRAMEDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_TXAFTERFRAMEDONE, self).__init__(register,
            'TXAFTERFRAMEDONE', 'FRC_NS.SEQIEN.TXAFTERFRAMEDONE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_TXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_TXABORTED, self).__init__(register,
            'TXABORTED', 'FRC_NS.SEQIEN.TXABORTED', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_TXUF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_TXUF, self).__init__(register,
            'TXUF', 'FRC_NS.SEQIEN.TXUF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_RXDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_RXDONE, self).__init__(register,
            'RXDONE', 'FRC_NS.SEQIEN.RXDONE', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_RXABORTED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_RXABORTED, self).__init__(register,
            'RXABORTED', 'FRC_NS.SEQIEN.RXABORTED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_FRAMEERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_FRAMEERROR, self).__init__(register,
            'FRAMEERROR', 'FRC_NS.SEQIEN.FRAMEERROR', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_BLOCKERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_BLOCKERROR, self).__init__(register,
            'BLOCKERROR', 'FRC_NS.SEQIEN.BLOCKERROR', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_RXOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_RXOF, self).__init__(register,
            'RXOF', 'FRC_NS.SEQIEN.RXOF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_WCNTCMP0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_WCNTCMP0, self).__init__(register,
            'WCNTCMP0', 'FRC_NS.SEQIEN.WCNTCMP0', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_WCNTCMP1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_WCNTCMP1, self).__init__(register,
            'WCNTCMP1', 'FRC_NS.SEQIEN.WCNTCMP1', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_WCNTCMP2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_WCNTCMP2, self).__init__(register,
            'WCNTCMP2', 'FRC_NS.SEQIEN.WCNTCMP2', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_ADDRERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_ADDRERROR, self).__init__(register,
            'ADDRERROR', 'FRC_NS.SEQIEN.ADDRERROR', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_BUSERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_BUSERROR, self).__init__(register,
            'BUSERROR', 'FRC_NS.SEQIEN.BUSERROR', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_RXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_RXRAWEVENT, self).__init__(register,
            'RXRAWEVENT', 'FRC_NS.SEQIEN.RXRAWEVENT', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_TXRAWEVENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_TXRAWEVENT, self).__init__(register,
            'TXRAWEVENT', 'FRC_NS.SEQIEN.TXRAWEVENT', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_SNIFFOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_SNIFFOF, self).__init__(register,
            'SNIFFOF', 'FRC_NS.SEQIEN.SNIFFOF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_WCNTCMP3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_WCNTCMP3, self).__init__(register,
            'WCNTCMP3', 'FRC_NS.SEQIEN.WCNTCMP3', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_WCNTCMP4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_WCNTCMP4, self).__init__(register,
            'WCNTCMP4', 'FRC_NS.SEQIEN.WCNTCMP4', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_BOISET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_BOISET, self).__init__(register,
            'BOISET', 'FRC_NS.SEQIEN.BOISET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_PKTBUFSTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_PKTBUFSTART, self).__init__(register,
            'PKTBUFSTART', 'FRC_NS.SEQIEN.PKTBUFSTART', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_NS.SEQIEN.PKTBUFTHRESHOLD', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_RXRAWOF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_RXRAWOF, self).__init__(register,
            'RXRAWOF', 'FRC_NS.SEQIEN.RXRAWOF', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_WCNTCMP5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_WCNTCMP5, self).__init__(register,
            'WCNTCMP5', 'FRC_NS.SEQIEN.WCNTCMP5', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_FRAMEDETPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_FRAMEDETPAUSED, self).__init__(register,
            'FRAMEDETPAUSED', 'FRC_NS.SEQIEN.FRAMEDETPAUSED', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_INTERLEAVEWRITEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_INTERLEAVEWRITEPAUSED, self).__init__(register,
            'INTERLEAVEWRITEPAUSED', 'FRC_NS.SEQIEN.INTERLEAVEWRITEPAUSED', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_INTERLEAVEREADPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_INTERLEAVEREADPAUSED, self).__init__(register,
            'INTERLEAVEREADPAUSED', 'FRC_NS.SEQIEN.INTERLEAVEREADPAUSED', 'read-write',
            u"",
            26, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_TXSUBFRAMEPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_TXSUBFRAMEPAUSED, self).__init__(register,
            'TXSUBFRAMEPAUSED', 'FRC_NS.SEQIEN.TXSUBFRAMEPAUSED', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_CONVPAUSED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_CONVPAUSED, self).__init__(register,
            'CONVPAUSED', 'FRC_NS.SEQIEN.CONVPAUSED', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_RXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_RXWORD, self).__init__(register,
            'RXWORD', 'FRC_NS.SEQIEN.RXWORD', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_TXWORD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_TXWORD, self).__init__(register,
            'TXWORD', 'FRC_NS.SEQIEN.TXWORD', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SEQIEN_UARTERROR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SEQIEN_UARTERROR, self).__init__(register,
            'UARTERROR', 'FRC_NS.SEQIEN.UARTERROR', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WCNTCMP3_SUPPLENFIELDLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WCNTCMP3_SUPPLENFIELDLOC, self).__init__(register,
            'SUPPLENFIELDLOC', 'FRC_NS.WCNTCMP3.SUPPLENFIELDLOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_BOICTRL_BOIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_BOICTRL_BOIEN, self).__init__(register,
            'BOIEN', 'FRC_NS.BOICTRL.BOIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_BOICTRL_BOIFIELDLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_BOICTRL_BOIFIELDLOC, self).__init__(register,
            'BOIFIELDLOC', 'FRC_NS.BOICTRL.BOIFIELDLOC', 'read-write',
            u"",
            1, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_BOICTRL_BOIBITPOS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_BOICTRL_BOIBITPOS, self).__init__(register,
            'BOIBITPOS', 'FRC_NS.BOICTRL.BOIBITPOS', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_BOICTRL_BOIMATCHVAL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_BOICTRL_BOIMATCHVAL, self).__init__(register,
            'BOIMATCHVAL', 'FRC_NS.BOICTRL.BOIMATCHVAL', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_DSLMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_DSLMODE, self).__init__(register,
            'DSLMODE', 'FRC_NS.DSLCTRL.DSLMODE', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_DSLBITORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_DSLBITORDER, self).__init__(register,
            'DSLBITORDER', 'FRC_NS.DSLCTRL.DSLBITORDER', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_DSLSHIFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_DSLSHIFT, self).__init__(register,
            'DSLSHIFT', 'FRC_NS.DSLCTRL.DSLSHIFT', 'read-write',
            u"",
            4, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_DSLOFFSET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_DSLOFFSET, self).__init__(register,
            'DSLOFFSET', 'FRC_NS.DSLCTRL.DSLOFFSET', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_DSLBITS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_DSLBITS, self).__init__(register,
            'DSLBITS', 'FRC_NS.DSLCTRL.DSLBITS', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_DSLMINLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_DSLMINLENGTH, self).__init__(register,
            'DSLMINLENGTH', 'FRC_NS.DSLCTRL.DSLMINLENGTH', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_RXSUPRECEPMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_RXSUPRECEPMODE, self).__init__(register,
            'RXSUPRECEPMODE', 'FRC_NS.DSLCTRL.RXSUPRECEPMODE', 'read-write',
            u"",
            24, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_STORESUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_STORESUP, self).__init__(register,
            'STORESUP', 'FRC_NS.DSLCTRL.STORESUP', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_DSLCTRL_SUPSHFFACTOR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_DSLCTRL_SUPSHFFACTOR, self).__init__(register,
            'SUPSHFFACTOR', 'FRC_NS.DSLCTRL.SUPSHFFACTOR', 'read-write',
            u"",
            28, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WCNTCMP4_SUPPLENGTH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WCNTCMP4_SUPPLENGTH, self).__init__(register,
            'SUPPLENGTH', 'FRC_NS.WCNTCMP4.SUPPLENGTH', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_WCNTCMP5_RXPAUSELOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_WCNTCMP5_RXPAUSELOC, self).__init__(register,
            'RXPAUSELOC', 'FRC_NS.WCNTCMP5.RXPAUSELOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUFCTRL_PKTBUFSTARTLOC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUFCTRL_PKTBUFSTARTLOC, self).__init__(register,
            'PKTBUFSTARTLOC', 'FRC_NS.PKTBUFCTRL.PKTBUFSTARTLOC', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUFCTRL_PKTBUFTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUFCTRL_PKTBUFTHRESHOLD, self).__init__(register,
            'PKTBUFTHRESHOLD', 'FRC_NS.PKTBUFCTRL.PKTBUFTHRESHOLD', 'read-write',
            u"",
            12, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUFCTRL_PKTBUFTHRESHOLDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUFCTRL_PKTBUFTHRESHOLDEN, self).__init__(register,
            'PKTBUFTHRESHOLDEN', 'FRC_NS.PKTBUFCTRL.PKTBUFTHRESHOLDEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUFCTRL_PKTBUFSTOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUFCTRL_PKTBUFSTOP, self).__init__(register,
            'PKTBUFSTOP', 'FRC_NS.PKTBUFCTRL.PKTBUFSTOP', 'write-only',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUFSTATUS_PKTBUFCOUNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUFSTATUS_PKTBUFCOUNT, self).__init__(register,
            'PKTBUFCOUNT', 'FRC_NS.PKTBUFSTATUS.PKTBUFCOUNT', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF0_PKTBUF0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF0_PKTBUF0, self).__init__(register,
            'PKTBUF0', 'FRC_NS.PKTBUF0.PKTBUF0', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF0_PKTBUF1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF0_PKTBUF1, self).__init__(register,
            'PKTBUF1', 'FRC_NS.PKTBUF0.PKTBUF1', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF0_PKTBUF2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF0_PKTBUF2, self).__init__(register,
            'PKTBUF2', 'FRC_NS.PKTBUF0.PKTBUF2', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF0_PKTBUF3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF0_PKTBUF3, self).__init__(register,
            'PKTBUF3', 'FRC_NS.PKTBUF0.PKTBUF3', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF1_PKTBUF4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF1_PKTBUF4, self).__init__(register,
            'PKTBUF4', 'FRC_NS.PKTBUF1.PKTBUF4', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF1_PKTBUF5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF1_PKTBUF5, self).__init__(register,
            'PKTBUF5', 'FRC_NS.PKTBUF1.PKTBUF5', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF1_PKTBUF6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF1_PKTBUF6, self).__init__(register,
            'PKTBUF6', 'FRC_NS.PKTBUF1.PKTBUF6', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF1_PKTBUF7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF1_PKTBUF7, self).__init__(register,
            'PKTBUF7', 'FRC_NS.PKTBUF1.PKTBUF7', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF2_PKTBUF8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF2_PKTBUF8, self).__init__(register,
            'PKTBUF8', 'FRC_NS.PKTBUF2.PKTBUF8', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF2_PKTBUF9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF2_PKTBUF9, self).__init__(register,
            'PKTBUF9', 'FRC_NS.PKTBUF2.PKTBUF9', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF2_PKTBUF10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF2_PKTBUF10, self).__init__(register,
            'PKTBUF10', 'FRC_NS.PKTBUF2.PKTBUF10', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF2_PKTBUF11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF2_PKTBUF11, self).__init__(register,
            'PKTBUF11', 'FRC_NS.PKTBUF2.PKTBUF11', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF3_PKTBUF12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF3_PKTBUF12, self).__init__(register,
            'PKTBUF12', 'FRC_NS.PKTBUF3.PKTBUF12', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF3_PKTBUF13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF3_PKTBUF13, self).__init__(register,
            'PKTBUF13', 'FRC_NS.PKTBUF3.PKTBUF13', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF3_PKTBUF14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF3_PKTBUF14, self).__init__(register,
            'PKTBUF14', 'FRC_NS.PKTBUF3.PKTBUF14', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF3_PKTBUF15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF3_PKTBUF15, self).__init__(register,
            'PKTBUF15', 'FRC_NS.PKTBUF3.PKTBUF15', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF4_PKTBUF16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF4_PKTBUF16, self).__init__(register,
            'PKTBUF16', 'FRC_NS.PKTBUF4.PKTBUF16', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF4_PKTBUF17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF4_PKTBUF17, self).__init__(register,
            'PKTBUF17', 'FRC_NS.PKTBUF4.PKTBUF17', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF4_PKTBUF18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF4_PKTBUF18, self).__init__(register,
            'PKTBUF18', 'FRC_NS.PKTBUF4.PKTBUF18', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF4_PKTBUF19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF4_PKTBUF19, self).__init__(register,
            'PKTBUF19', 'FRC_NS.PKTBUF4.PKTBUF19', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF5_PKTBUF20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF5_PKTBUF20, self).__init__(register,
            'PKTBUF20', 'FRC_NS.PKTBUF5.PKTBUF20', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF5_PKTBUF21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF5_PKTBUF21, self).__init__(register,
            'PKTBUF21', 'FRC_NS.PKTBUF5.PKTBUF21', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF5_PKTBUF22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF5_PKTBUF22, self).__init__(register,
            'PKTBUF22', 'FRC_NS.PKTBUF5.PKTBUF22', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF5_PKTBUF23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF5_PKTBUF23, self).__init__(register,
            'PKTBUF23', 'FRC_NS.PKTBUF5.PKTBUF23', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF6_PKTBUF24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF6_PKTBUF24, self).__init__(register,
            'PKTBUF24', 'FRC_NS.PKTBUF6.PKTBUF24', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF6_PKTBUF25(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF6_PKTBUF25, self).__init__(register,
            'PKTBUF25', 'FRC_NS.PKTBUF6.PKTBUF25', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF6_PKTBUF26(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF6_PKTBUF26, self).__init__(register,
            'PKTBUF26', 'FRC_NS.PKTBUF6.PKTBUF26', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF6_PKTBUF27(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF6_PKTBUF27, self).__init__(register,
            'PKTBUF27', 'FRC_NS.PKTBUF6.PKTBUF27', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF7_PKTBUF28(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF7_PKTBUF28, self).__init__(register,
            'PKTBUF28', 'FRC_NS.PKTBUF7.PKTBUF28', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF7_PKTBUF29(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF7_PKTBUF29, self).__init__(register,
            'PKTBUF29', 'FRC_NS.PKTBUF7.PKTBUF29', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF7_PKTBUF30(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF7_PKTBUF30, self).__init__(register,
            'PKTBUF30', 'FRC_NS.PKTBUF7.PKTBUF30', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF7_PKTBUF31(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF7_PKTBUF31, self).__init__(register,
            'PKTBUF31', 'FRC_NS.PKTBUF7.PKTBUF31', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF8_PKTBUF32(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF8_PKTBUF32, self).__init__(register,
            'PKTBUF32', 'FRC_NS.PKTBUF8.PKTBUF32', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF8_PKTBUF33(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF8_PKTBUF33, self).__init__(register,
            'PKTBUF33', 'FRC_NS.PKTBUF8.PKTBUF33', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF8_PKTBUF34(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF8_PKTBUF34, self).__init__(register,
            'PKTBUF34', 'FRC_NS.PKTBUF8.PKTBUF34', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF8_PKTBUF35(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF8_PKTBUF35, self).__init__(register,
            'PKTBUF35', 'FRC_NS.PKTBUF8.PKTBUF35', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF9_PKTBUF36(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF9_PKTBUF36, self).__init__(register,
            'PKTBUF36', 'FRC_NS.PKTBUF9.PKTBUF36', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF9_PKTBUF37(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF9_PKTBUF37, self).__init__(register,
            'PKTBUF37', 'FRC_NS.PKTBUF9.PKTBUF37', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF9_PKTBUF38(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF9_PKTBUF38, self).__init__(register,
            'PKTBUF38', 'FRC_NS.PKTBUF9.PKTBUF38', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF9_PKTBUF39(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF9_PKTBUF39, self).__init__(register,
            'PKTBUF39', 'FRC_NS.PKTBUF9.PKTBUF39', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF10_PKTBUF40(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF10_PKTBUF40, self).__init__(register,
            'PKTBUF40', 'FRC_NS.PKTBUF10.PKTBUF40', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF10_PKTBUF41(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF10_PKTBUF41, self).__init__(register,
            'PKTBUF41', 'FRC_NS.PKTBUF10.PKTBUF41', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF10_PKTBUF42(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF10_PKTBUF42, self).__init__(register,
            'PKTBUF42', 'FRC_NS.PKTBUF10.PKTBUF42', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF10_PKTBUF43(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF10_PKTBUF43, self).__init__(register,
            'PKTBUF43', 'FRC_NS.PKTBUF10.PKTBUF43', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF11_PKTBUF44(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF11_PKTBUF44, self).__init__(register,
            'PKTBUF44', 'FRC_NS.PKTBUF11.PKTBUF44', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF11_PKTBUF45(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF11_PKTBUF45, self).__init__(register,
            'PKTBUF45', 'FRC_NS.PKTBUF11.PKTBUF45', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF11_PKTBUF46(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF11_PKTBUF46, self).__init__(register,
            'PKTBUF46', 'FRC_NS.PKTBUF11.PKTBUF46', 'read-only',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_PKTBUF11_PKTBUF47(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_PKTBUF11_PKTBUF47, self).__init__(register,
            'PKTBUF47', 'FRC_NS.PKTBUF11.PKTBUF47', 'read-only',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD0_WORDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD0_WORDS, self).__init__(register,
            'WORDS', 'FRC_NS.FCD0.WORDS', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD0_BUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD0_BUFFER, self).__init__(register,
            'BUFFER', 'FRC_NS.FCD0.BUFFER', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD0_INCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD0_INCLUDECRC, self).__init__(register,
            'INCLUDECRC', 'FRC_NS.FCD0.INCLUDECRC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD0_CALCCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD0_CALCCRC, self).__init__(register,
            'CALCCRC', 'FRC_NS.FCD0.CALCCRC', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD0_SKIPCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD0_SKIPCRC, self).__init__(register,
            'SKIPCRC', 'FRC_NS.FCD0.SKIPCRC', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD0_SKIPWHITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD0_SKIPWHITE, self).__init__(register,
            'SKIPWHITE', 'FRC_NS.FCD0.SKIPWHITE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD0_ADDTRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD0_ADDTRAILTXDATA, self).__init__(register,
            'ADDTRAILTXDATA', 'FRC_NS.FCD0.ADDTRAILTXDATA', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD0_EXCLUDESUBFRAMEWCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD0_EXCLUDESUBFRAMEWCNT, self).__init__(register,
            'EXCLUDESUBFRAMEWCNT', 'FRC_NS.FCD0.EXCLUDESUBFRAMEWCNT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD1_WORDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD1_WORDS, self).__init__(register,
            'WORDS', 'FRC_NS.FCD1.WORDS', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD1_BUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD1_BUFFER, self).__init__(register,
            'BUFFER', 'FRC_NS.FCD1.BUFFER', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD1_INCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD1_INCLUDECRC, self).__init__(register,
            'INCLUDECRC', 'FRC_NS.FCD1.INCLUDECRC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD1_CALCCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD1_CALCCRC, self).__init__(register,
            'CALCCRC', 'FRC_NS.FCD1.CALCCRC', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD1_SKIPCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD1_SKIPCRC, self).__init__(register,
            'SKIPCRC', 'FRC_NS.FCD1.SKIPCRC', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD1_SKIPWHITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD1_SKIPWHITE, self).__init__(register,
            'SKIPWHITE', 'FRC_NS.FCD1.SKIPWHITE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD1_ADDTRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD1_ADDTRAILTXDATA, self).__init__(register,
            'ADDTRAILTXDATA', 'FRC_NS.FCD1.ADDTRAILTXDATA', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD1_EXCLUDESUBFRAMEWCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD1_EXCLUDESUBFRAMEWCNT, self).__init__(register,
            'EXCLUDESUBFRAMEWCNT', 'FRC_NS.FCD1.EXCLUDESUBFRAMEWCNT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD2_WORDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD2_WORDS, self).__init__(register,
            'WORDS', 'FRC_NS.FCD2.WORDS', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD2_BUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD2_BUFFER, self).__init__(register,
            'BUFFER', 'FRC_NS.FCD2.BUFFER', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD2_INCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD2_INCLUDECRC, self).__init__(register,
            'INCLUDECRC', 'FRC_NS.FCD2.INCLUDECRC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD2_CALCCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD2_CALCCRC, self).__init__(register,
            'CALCCRC', 'FRC_NS.FCD2.CALCCRC', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD2_SKIPCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD2_SKIPCRC, self).__init__(register,
            'SKIPCRC', 'FRC_NS.FCD2.SKIPCRC', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD2_SKIPWHITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD2_SKIPWHITE, self).__init__(register,
            'SKIPWHITE', 'FRC_NS.FCD2.SKIPWHITE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD2_ADDTRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD2_ADDTRAILTXDATA, self).__init__(register,
            'ADDTRAILTXDATA', 'FRC_NS.FCD2.ADDTRAILTXDATA', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD2_EXCLUDESUBFRAMEWCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD2_EXCLUDESUBFRAMEWCNT, self).__init__(register,
            'EXCLUDESUBFRAMEWCNT', 'FRC_NS.FCD2.EXCLUDESUBFRAMEWCNT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD3_WORDS(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD3_WORDS, self).__init__(register,
            'WORDS', 'FRC_NS.FCD3.WORDS', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD3_BUFFER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD3_BUFFER, self).__init__(register,
            'BUFFER', 'FRC_NS.FCD3.BUFFER', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD3_INCLUDECRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD3_INCLUDECRC, self).__init__(register,
            'INCLUDECRC', 'FRC_NS.FCD3.INCLUDECRC', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD3_CALCCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD3_CALCCRC, self).__init__(register,
            'CALCCRC', 'FRC_NS.FCD3.CALCCRC', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD3_SKIPCRC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD3_SKIPCRC, self).__init__(register,
            'SKIPCRC', 'FRC_NS.FCD3.SKIPCRC', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD3_SKIPWHITE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD3_SKIPWHITE, self).__init__(register,
            'SKIPWHITE', 'FRC_NS.FCD3.SKIPWHITE', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD3_ADDTRAILTXDATA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD3_ADDTRAILTXDATA, self).__init__(register,
            'ADDTRAILTXDATA', 'FRC_NS.FCD3.ADDTRAILTXDATA', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_FCD3_EXCLUDESUBFRAMEWCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_FCD3_EXCLUDESUBFRAMEWCNT, self).__init__(register,
            'EXCLUDESUBFRAMEWCNT', 'FRC_NS.FCD3.EXCLUDESUBFRAMEWCNT', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT0_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT0_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT0.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT1_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT1_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT1.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT2_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT2_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT2.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT3_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT3_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT3.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT4_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT4_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT4.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT5_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT5_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT5.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT6_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT6_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT6.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT7_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT7_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT7.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT8_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT8_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT8.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT9_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT9_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT9.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT10_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT10_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT10.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT11_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT11_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT11.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT12_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT12_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT12.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT13_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT13_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT13.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT14_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT14_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT14.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_INTELEMENT15_INTELEMENT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_INTELEMENT15_INTELEMENT, self).__init__(register,
            'INTELEMENT', 'FRC_NS.INTELEMENT15.INTELEMENT', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_AHBCONFIG_AHBHPROTBUFFERABLE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_AHBCONFIG_AHBHPROTBUFFERABLE, self).__init__(register,
            'AHBHPROTBUFFERABLE', 'FRC_NS.AHBCONFIG.AHBHPROTBUFFERABLE', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_FRC_NS_SPARE_SPARE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_FRC_NS_SPARE_SPARE, self).__init__(register,
            'SPARE', 'FRC_NS.SPARE.SPARE', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True



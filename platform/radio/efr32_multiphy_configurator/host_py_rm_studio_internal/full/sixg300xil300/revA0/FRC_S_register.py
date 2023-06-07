
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . FRC_S_field import *


class RM_Register_FRC_S_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_IPVERSION, self).__init__(rmio, label,
            0xa8004000, 0x000,
            'IPVERSION', 'FRC_S.IPVERSION', 'read-only',
            u"",
            0x00000006, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_FRC_S_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_EN, self).__init__(rmio, label,
            0xa8004000, 0x004,
            'EN', 'FRC_S.EN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_FRC_S_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_STATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_STATUS, self).__init__(rmio, label,
            0xa8004000, 0x008,
            'STATUS', 'FRC_S.STATUS', 'read-only',
            u"",
            0x00000000, 0x07FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SNIFFDCOUNT = RM_Field_FRC_S_STATUS_SNIFFDCOUNT(self)
        self.zz_fdict['SNIFFDCOUNT'] = self.SNIFFDCOUNT
        self.ACTIVETXFCD = RM_Field_FRC_S_STATUS_ACTIVETXFCD(self)
        self.zz_fdict['ACTIVETXFCD'] = self.ACTIVETXFCD
        self.ACTIVERXFCD = RM_Field_FRC_S_STATUS_ACTIVERXFCD(self)
        self.zz_fdict['ACTIVERXFCD'] = self.ACTIVERXFCD
        self.SNIFFDFRAME = RM_Field_FRC_S_STATUS_SNIFFDFRAME(self)
        self.zz_fdict['SNIFFDFRAME'] = self.SNIFFDFRAME
        self.RXRAWBLOCKED = RM_Field_FRC_S_STATUS_RXRAWBLOCKED(self)
        self.zz_fdict['RXRAWBLOCKED'] = self.RXRAWBLOCKED
        self.FRAMEOK = RM_Field_FRC_S_STATUS_FRAMEOK(self)
        self.zz_fdict['FRAMEOK'] = self.FRAMEOK
        self.RXABORTINPROGRESS = RM_Field_FRC_S_STATUS_RXABORTINPROGRESS(self)
        self.zz_fdict['RXABORTINPROGRESS'] = self.RXABORTINPROGRESS
        self.TXWORD = RM_Field_FRC_S_STATUS_TXWORD(self)
        self.zz_fdict['TXWORD'] = self.TXWORD
        self.RXWORD = RM_Field_FRC_S_STATUS_RXWORD(self)
        self.zz_fdict['RXWORD'] = self.RXWORD
        self.CONVPAUSED = RM_Field_FRC_S_STATUS_CONVPAUSED(self)
        self.zz_fdict['CONVPAUSED'] = self.CONVPAUSED
        self.TXSUBFRAMEPAUSED = RM_Field_FRC_S_STATUS_TXSUBFRAMEPAUSED(self)
        self.zz_fdict['TXSUBFRAMEPAUSED'] = self.TXSUBFRAMEPAUSED
        self.INTERLEAVEREADPAUSED = RM_Field_FRC_S_STATUS_INTERLEAVEREADPAUSED(self)
        self.zz_fdict['INTERLEAVEREADPAUSED'] = self.INTERLEAVEREADPAUSED
        self.INTERLEAVEWRITEPAUSED = RM_Field_FRC_S_STATUS_INTERLEAVEWRITEPAUSED(self)
        self.zz_fdict['INTERLEAVEWRITEPAUSED'] = self.INTERLEAVEWRITEPAUSED
        self.FRAMEDETPAUSED = RM_Field_FRC_S_STATUS_FRAMEDETPAUSED(self)
        self.zz_fdict['FRAMEDETPAUSED'] = self.FRAMEDETPAUSED
        self.FRAMELENGTHERROR = RM_Field_FRC_S_STATUS_FRAMELENGTHERROR(self)
        self.zz_fdict['FRAMELENGTHERROR'] = self.FRAMELENGTHERROR
        self.DEMODERROR = RM_Field_FRC_S_STATUS_DEMODERROR(self)
        self.zz_fdict['DEMODERROR'] = self.DEMODERROR
        self.FSMSTATE = RM_Field_FRC_S_STATUS_FSMSTATE(self)
        self.zz_fdict['FSMSTATE'] = self.FSMSTATE
        self.RXWCNTMATCHPAUSED = RM_Field_FRC_S_STATUS_RXWCNTMATCHPAUSED(self)
        self.zz_fdict['RXWCNTMATCHPAUSED'] = self.RXWCNTMATCHPAUSED
        self.CRCERRORTOLERATED = RM_Field_FRC_S_STATUS_CRCERRORTOLERATED(self)
        self.zz_fdict['CRCERRORTOLERATED'] = self.CRCERRORTOLERATED
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_DFLCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_DFLCTRL, self).__init__(rmio, label,
            0xa8004000, 0x00C,
            'DFLCTRL', 'FRC_S.DFLCTRL', 'read-write',
            u"",
            0x00000000, 0x01FFFF7F,
            0x00001000, 0x00002000,
            0x00003000)

        self.DFLMODE = RM_Field_FRC_S_DFLCTRL_DFLMODE(self)
        self.zz_fdict['DFLMODE'] = self.DFLMODE
        self.DFLBITORDER = RM_Field_FRC_S_DFLCTRL_DFLBITORDER(self)
        self.zz_fdict['DFLBITORDER'] = self.DFLBITORDER
        self.DFLSHIFT = RM_Field_FRC_S_DFLCTRL_DFLSHIFT(self)
        self.zz_fdict['DFLSHIFT'] = self.DFLSHIFT
        self.DFLOFFSET = RM_Field_FRC_S_DFLCTRL_DFLOFFSET(self)
        self.zz_fdict['DFLOFFSET'] = self.DFLOFFSET
        self.DFLBITS = RM_Field_FRC_S_DFLCTRL_DFLBITS(self)
        self.zz_fdict['DFLBITS'] = self.DFLBITS
        self.MINLENGTH = RM_Field_FRC_S_DFLCTRL_MINLENGTH(self)
        self.zz_fdict['MINLENGTH'] = self.MINLENGTH
        self.DFLINCLUDECRC = RM_Field_FRC_S_DFLCTRL_DFLINCLUDECRC(self)
        self.zz_fdict['DFLINCLUDECRC'] = self.DFLINCLUDECRC
        self.DFLBOIOFFSET = RM_Field_FRC_S_DFLCTRL_DFLBOIOFFSET(self)
        self.zz_fdict['DFLBOIOFFSET'] = self.DFLBOIOFFSET
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_MAXLENGTH(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_MAXLENGTH, self).__init__(rmio, label,
            0xa8004000, 0x010,
            'MAXLENGTH', 'FRC_S.MAXLENGTH', 'read-write',
            u"",
            0x00004FFF, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MAXLENGTH = RM_Field_FRC_S_MAXLENGTH_MAXLENGTH(self)
        self.zz_fdict['MAXLENGTH'] = self.MAXLENGTH
        self.INILENGTH = RM_Field_FRC_S_MAXLENGTH_INILENGTH(self)
        self.zz_fdict['INILENGTH'] = self.INILENGTH
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_ADDRFILTCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_ADDRFILTCTRL, self).__init__(rmio, label,
            0xa8004000, 0x014,
            'ADDRFILTCTRL', 'FRC_S.ADDRFILTCTRL', 'read-write',
            u"",
            0x00000000, 0x0000FF07,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_FRC_S_ADDRFILTCTRL_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.BRDCST00EN = RM_Field_FRC_S_ADDRFILTCTRL_BRDCST00EN(self)
        self.zz_fdict['BRDCST00EN'] = self.BRDCST00EN
        self.BRDCSTFFEN = RM_Field_FRC_S_ADDRFILTCTRL_BRDCSTFFEN(self)
        self.zz_fdict['BRDCSTFFEN'] = self.BRDCSTFFEN
        self.ADDRESS = RM_Field_FRC_S_ADDRFILTCTRL_ADDRESS(self)
        self.zz_fdict['ADDRESS'] = self.ADDRESS
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_DATABUFFER(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_DATABUFFER, self).__init__(rmio, label,
            0xa8004000, 0x018,
            'DATABUFFER', 'FRC_S.DATABUFFER', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DATABUFFER = RM_Field_FRC_S_DATABUFFER_DATABUFFER(self)
        self.zz_fdict['DATABUFFER'] = self.DATABUFFER
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WCNT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WCNT, self).__init__(rmio, label,
            0xa8004000, 0x01C,
            'WCNT', 'FRC_S.WCNT', 'read-only',
            u"",
            0x00000000, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.WCNT = RM_Field_FRC_S_WCNT_WCNT(self)
        self.zz_fdict['WCNT'] = self.WCNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WCNTCMP0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WCNTCMP0, self).__init__(rmio, label,
            0xa8004000, 0x020,
            'WCNTCMP0', 'FRC_S.WCNTCMP0', 'read-write',
            u"",
            0x00000000, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FRAMELENGTH = RM_Field_FRC_S_WCNTCMP0_FRAMELENGTH(self)
        self.zz_fdict['FRAMELENGTH'] = self.FRAMELENGTH
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WCNTCMP1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WCNTCMP1, self).__init__(rmio, label,
            0xa8004000, 0x024,
            'WCNTCMP1', 'FRC_S.WCNTCMP1', 'read-write',
            u"",
            0x00000000, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LENGTHFIELDLOC = RM_Field_FRC_S_WCNTCMP1_LENGTHFIELDLOC(self)
        self.zz_fdict['LENGTHFIELDLOC'] = self.LENGTHFIELDLOC
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WCNTCMP2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WCNTCMP2, self).__init__(rmio, label,
            0xa8004000, 0x028,
            'WCNTCMP2', 'FRC_S.WCNTCMP2', 'read-write',
            u"",
            0x00000000, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADDRFIELDLOC = RM_Field_FRC_S_WCNTCMP2_ADDRFIELDLOC(self)
        self.zz_fdict['ADDRFIELDLOC'] = self.ADDRFIELDLOC
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_CMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_CMD, self).__init__(rmio, label,
            0xa8004000, 0x02C,
            'CMD', 'FRC_S.CMD', 'write-only',
            u"",
            0x00000000, 0x00003FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXABORT = RM_Field_FRC_S_CMD_RXABORT(self)
        self.zz_fdict['RXABORT'] = self.RXABORT
        self.FRAMEDETRESUME = RM_Field_FRC_S_CMD_FRAMEDETRESUME(self)
        self.zz_fdict['FRAMEDETRESUME'] = self.FRAMEDETRESUME
        self.INTERLEAVEWRITERESUME = RM_Field_FRC_S_CMD_INTERLEAVEWRITERESUME(self)
        self.zz_fdict['INTERLEAVEWRITERESUME'] = self.INTERLEAVEWRITERESUME
        self.INTERLEAVEREADRESUME = RM_Field_FRC_S_CMD_INTERLEAVEREADRESUME(self)
        self.zz_fdict['INTERLEAVEREADRESUME'] = self.INTERLEAVEREADRESUME
        self.CONVRESUME = RM_Field_FRC_S_CMD_CONVRESUME(self)
        self.zz_fdict['CONVRESUME'] = self.CONVRESUME
        self.CONVTERMINATE = RM_Field_FRC_S_CMD_CONVTERMINATE(self)
        self.zz_fdict['CONVTERMINATE'] = self.CONVTERMINATE
        self.TXSUBFRAMERESUME = RM_Field_FRC_S_CMD_TXSUBFRAMERESUME(self)
        self.zz_fdict['TXSUBFRAMERESUME'] = self.TXSUBFRAMERESUME
        self.INTERLEAVEINIT = RM_Field_FRC_S_CMD_INTERLEAVEINIT(self)
        self.zz_fdict['INTERLEAVEINIT'] = self.INTERLEAVEINIT
        self.INTERLEAVECNTCLEAR = RM_Field_FRC_S_CMD_INTERLEAVECNTCLEAR(self)
        self.zz_fdict['INTERLEAVECNTCLEAR'] = self.INTERLEAVECNTCLEAR
        self.CONVINIT = RM_Field_FRC_S_CMD_CONVINIT(self)
        self.zz_fdict['CONVINIT'] = self.CONVINIT
        self.BLOCKINIT = RM_Field_FRC_S_CMD_BLOCKINIT(self)
        self.zz_fdict['BLOCKINIT'] = self.BLOCKINIT
        self.STATEINIT = RM_Field_FRC_S_CMD_STATEINIT(self)
        self.zz_fdict['STATEINIT'] = self.STATEINIT
        self.RXRAWUNBLOCK = RM_Field_FRC_S_CMD_RXRAWUNBLOCK(self)
        self.zz_fdict['RXRAWUNBLOCK'] = self.RXRAWUNBLOCK
        self.RXPAUSERESUME = RM_Field_FRC_S_CMD_RXPAUSERESUME(self)
        self.zz_fdict['RXPAUSERESUME'] = self.RXPAUSERESUME
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WHITECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WHITECTRL, self).__init__(rmio, label,
            0xa8004000, 0x030,
            'WHITECTRL', 'FRC_S.WHITECTRL', 'read-write',
            u"",
            0x00000000, 0x00001F7F,
            0x00001000, 0x00002000,
            0x00003000)

        self.FEEDBACKSEL = RM_Field_FRC_S_WHITECTRL_FEEDBACKSEL(self)
        self.zz_fdict['FEEDBACKSEL'] = self.FEEDBACKSEL
        self.XORFEEDBACK = RM_Field_FRC_S_WHITECTRL_XORFEEDBACK(self)
        self.zz_fdict['XORFEEDBACK'] = self.XORFEEDBACK
        self.SHROUTPUTSEL = RM_Field_FRC_S_WHITECTRL_SHROUTPUTSEL(self)
        self.zz_fdict['SHROUTPUTSEL'] = self.SHROUTPUTSEL
        self.BLOCKERRORCORRECT = RM_Field_FRC_S_WHITECTRL_BLOCKERRORCORRECT(self)
        self.zz_fdict['BLOCKERRORCORRECT'] = self.BLOCKERRORCORRECT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WHITEPOLY(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WHITEPOLY, self).__init__(rmio, label,
            0xa8004000, 0x034,
            'WHITEPOLY', 'FRC_S.WHITEPOLY', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POLY = RM_Field_FRC_S_WHITEPOLY_POLY(self)
        self.zz_fdict['POLY'] = self.POLY
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WHITEINIT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WHITEINIT, self).__init__(rmio, label,
            0xa8004000, 0x038,
            'WHITEINIT', 'FRC_S.WHITEINIT', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.WHITEINIT = RM_Field_FRC_S_WHITEINIT_WHITEINIT(self)
        self.zz_fdict['WHITEINIT'] = self.WHITEINIT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_FECCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_FECCTRL, self).__init__(rmio, label,
            0xa8004000, 0x03C,
            'FECCTRL', 'FRC_S.FECCTRL', 'read-write',
            u"",
            0x00000000, 0x003FFFF7,
            0x00001000, 0x00002000,
            0x00003000)

        self.BLOCKWHITEMODE = RM_Field_FRC_S_FECCTRL_BLOCKWHITEMODE(self)
        self.zz_fdict['BLOCKWHITEMODE'] = self.BLOCKWHITEMODE
        self.CONVMODE = RM_Field_FRC_S_FECCTRL_CONVMODE(self)
        self.zz_fdict['CONVMODE'] = self.CONVMODE
        self.CONVDECODEMODE = RM_Field_FRC_S_FECCTRL_CONVDECODEMODE(self)
        self.zz_fdict['CONVDECODEMODE'] = self.CONVDECODEMODE
        self.CONVTRACEBACKDISABLE = RM_Field_FRC_S_FECCTRL_CONVTRACEBACKDISABLE(self)
        self.zz_fdict['CONVTRACEBACKDISABLE'] = self.CONVTRACEBACKDISABLE
        self.CONVINV = RM_Field_FRC_S_FECCTRL_CONVINV(self)
        self.zz_fdict['CONVINV'] = self.CONVINV
        self.INTERLEAVEMODE = RM_Field_FRC_S_FECCTRL_INTERLEAVEMODE(self)
        self.zz_fdict['INTERLEAVEMODE'] = self.INTERLEAVEMODE
        self.INTERLEAVEFIRSTINDEX = RM_Field_FRC_S_FECCTRL_INTERLEAVEFIRSTINDEX(self)
        self.zz_fdict['INTERLEAVEFIRSTINDEX'] = self.INTERLEAVEFIRSTINDEX
        self.INTERLEAVEWIDTH = RM_Field_FRC_S_FECCTRL_INTERLEAVEWIDTH(self)
        self.zz_fdict['INTERLEAVEWIDTH'] = self.INTERLEAVEWIDTH
        self.CONVBUSLOCK = RM_Field_FRC_S_FECCTRL_CONVBUSLOCK(self)
        self.zz_fdict['CONVBUSLOCK'] = self.CONVBUSLOCK
        self.CONVSUBFRAMETERMINATE = RM_Field_FRC_S_FECCTRL_CONVSUBFRAMETERMINATE(self)
        self.zz_fdict['CONVSUBFRAMETERMINATE'] = self.CONVSUBFRAMETERMINATE
        self.SINGLEBLOCK = RM_Field_FRC_S_FECCTRL_SINGLEBLOCK(self)
        self.zz_fdict['SINGLEBLOCK'] = self.SINGLEBLOCK
        self.FORCE2FSK = RM_Field_FRC_S_FECCTRL_FORCE2FSK(self)
        self.zz_fdict['FORCE2FSK'] = self.FORCE2FSK
        self.CONVHARDERROR = RM_Field_FRC_S_FECCTRL_CONVHARDERROR(self)
        self.zz_fdict['CONVHARDERROR'] = self.CONVHARDERROR
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_BLOCKRAMADDR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_BLOCKRAMADDR, self).__init__(rmio, label,
            0xa8004000, 0x040,
            'BLOCKRAMADDR', 'FRC_S.BLOCKRAMADDR', 'read-write',
            u"",
            0x00004000, 0xFFFFFFFC,
            0x00001000, 0x00002000,
            0x00003000)

        self.BLOCKRAMADDR = RM_Field_FRC_S_BLOCKRAMADDR_BLOCKRAMADDR(self)
        self.zz_fdict['BLOCKRAMADDR'] = self.BLOCKRAMADDR
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_CONVRAMADDR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_CONVRAMADDR, self).__init__(rmio, label,
            0xa8004000, 0x044,
            'CONVRAMADDR', 'FRC_S.CONVRAMADDR', 'read-write',
            u"",
            0x00004000, 0xFFFFFFFC,
            0x00001000, 0x00002000,
            0x00003000)

        self.CONVRAMADDR = RM_Field_FRC_S_CONVRAMADDR_CONVRAMADDR(self)
        self.zz_fdict['CONVRAMADDR'] = self.CONVRAMADDR
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_CTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_CTRL, self).__init__(rmio, label,
            0xa8004000, 0x048,
            'CTRL', 'FRC_S.CTRL', 'read-write',
            u"",
            0x03000700, 0x073F7FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RANDOMTX = RM_Field_FRC_S_CTRL_RANDOMTX(self)
        self.zz_fdict['RANDOMTX'] = self.RANDOMTX
        self.UARTMODE = RM_Field_FRC_S_CTRL_UARTMODE(self)
        self.zz_fdict['UARTMODE'] = self.UARTMODE
        self.BITORDER = RM_Field_FRC_S_CTRL_BITORDER(self)
        self.zz_fdict['BITORDER'] = self.BITORDER
        self.LSBFRTREVERT = RM_Field_FRC_S_CTRL_LSBFRTREVERT(self)
        self.zz_fdict['LSBFRTREVERT'] = self.LSBFRTREVERT
        self.TXFCDMODE = RM_Field_FRC_S_CTRL_TXFCDMODE(self)
        self.zz_fdict['TXFCDMODE'] = self.TXFCDMODE
        self.RXFCDMODE = RM_Field_FRC_S_CTRL_RXFCDMODE(self)
        self.zz_fdict['RXFCDMODE'] = self.RXFCDMODE
        self.BITSPERWORD = RM_Field_FRC_S_CTRL_BITSPERWORD(self)
        self.zz_fdict['BITSPERWORD'] = self.BITSPERWORD
        self.RATESELECT = RM_Field_FRC_S_CTRL_RATESELECT(self)
        self.zz_fdict['RATESELECT'] = self.RATESELECT
        self.TXPREFETCH = RM_Field_FRC_S_CTRL_TXPREFETCH(self)
        self.zz_fdict['TXPREFETCH'] = self.TXPREFETCH
        self.TXFETCHBLOCKING = RM_Field_FRC_S_CTRL_TXFETCHBLOCKING(self)
        self.zz_fdict['TXFETCHBLOCKING'] = self.TXFETCHBLOCKING
        self.SEQHANDSHAKE = RM_Field_FRC_S_CTRL_SEQHANDSHAKE(self)
        self.zz_fdict['SEQHANDSHAKE'] = self.SEQHANDSHAKE
        self.PRBSTEST = RM_Field_FRC_S_CTRL_PRBSTEST(self)
        self.zz_fdict['PRBSTEST'] = self.PRBSTEST
        self.LPMODEDIS = RM_Field_FRC_S_CTRL_LPMODEDIS(self)
        self.zz_fdict['LPMODEDIS'] = self.LPMODEDIS
        self.WAITEOFEN = RM_Field_FRC_S_CTRL_WAITEOFEN(self)
        self.zz_fdict['WAITEOFEN'] = self.WAITEOFEN
        self.RXABORTIGNOREDIS = RM_Field_FRC_S_CTRL_RXABORTIGNOREDIS(self)
        self.zz_fdict['RXABORTIGNOREDIS'] = self.RXABORTIGNOREDIS
        self.FRAMEENDAHEADDIS = RM_Field_FRC_S_CTRL_FRAMEENDAHEADDIS(self)
        self.zz_fdict['FRAMEENDAHEADDIS'] = self.FRAMEENDAHEADDIS
        self.SKIPTXTRAILDATAWHITEN = RM_Field_FRC_S_CTRL_SKIPTXTRAILDATAWHITEN(self)
        self.zz_fdict['SKIPTXTRAILDATAWHITEN'] = self.SKIPTXTRAILDATAWHITEN
        self.SKIPRXSUPSTATEWHITEN = RM_Field_FRC_S_CTRL_SKIPRXSUPSTATEWHITEN(self)
        self.zz_fdict['SKIPRXSUPSTATEWHITEN'] = self.SKIPRXSUPSTATEWHITEN
        self.HOLDTXTRAILDATAACTIVE = RM_Field_FRC_S_CTRL_HOLDTXTRAILDATAACTIVE(self)
        self.zz_fdict['HOLDTXTRAILDATAACTIVE'] = self.HOLDTXTRAILDATAACTIVE
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_RXCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_RXCTRL, self).__init__(rmio, label,
            0xa8004000, 0x04C,
            'RXCTRL', 'FRC_S.RXCTRL', 'read-write',
            u"",
            0x00000000, 0x00030FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.STORECRC = RM_Field_FRC_S_RXCTRL_STORECRC(self)
        self.zz_fdict['STORECRC'] = self.STORECRC
        self.ACCEPTCRCERRORS = RM_Field_FRC_S_RXCTRL_ACCEPTCRCERRORS(self)
        self.zz_fdict['ACCEPTCRCERRORS'] = self.ACCEPTCRCERRORS
        self.ACCEPTBLOCKERRORS = RM_Field_FRC_S_RXCTRL_ACCEPTBLOCKERRORS(self)
        self.zz_fdict['ACCEPTBLOCKERRORS'] = self.ACCEPTBLOCKERRORS
        self.TRACKABFRAME = RM_Field_FRC_S_RXCTRL_TRACKABFRAME(self)
        self.zz_fdict['TRACKABFRAME'] = self.TRACKABFRAME
        self.BUFCLEAR = RM_Field_FRC_S_RXCTRL_BUFCLEAR(self)
        self.zz_fdict['BUFCLEAR'] = self.BUFCLEAR
        self.BUFRESTOREFRAMEERROR = RM_Field_FRC_S_RXCTRL_BUFRESTOREFRAMEERROR(self)
        self.zz_fdict['BUFRESTOREFRAMEERROR'] = self.BUFRESTOREFRAMEERROR
        self.BUFRESTORERXABORTED = RM_Field_FRC_S_RXCTRL_BUFRESTORERXABORTED(self)
        self.zz_fdict['BUFRESTORERXABORTED'] = self.BUFRESTORERXABORTED
        self.RXFRAMEENDAHEADBYTES = RM_Field_FRC_S_RXCTRL_RXFRAMEENDAHEADBYTES(self)
        self.zz_fdict['RXFRAMEENDAHEADBYTES'] = self.RXFRAMEENDAHEADBYTES
        self.ACCEPTUARTERRORS = RM_Field_FRC_S_RXCTRL_ACCEPTUARTERRORS(self)
        self.zz_fdict['ACCEPTUARTERRORS'] = self.ACCEPTUARTERRORS
        self.IFINPUTWIDTH = RM_Field_FRC_S_RXCTRL_IFINPUTWIDTH(self)
        self.zz_fdict['IFINPUTWIDTH'] = self.IFINPUTWIDTH
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_TRAILTXDATACTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_TRAILTXDATACTRL, self).__init__(rmio, label,
            0xa8004000, 0x050,
            'TRAILTXDATACTRL', 'FRC_S.TRAILTXDATACTRL', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TRAILTXDATA = RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATA(self)
        self.zz_fdict['TRAILTXDATA'] = self.TRAILTXDATA
        self.TRAILTXDATACNT = RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATACNT(self)
        self.zz_fdict['TRAILTXDATACNT'] = self.TRAILTXDATACNT
        self.TRAILTXDATAFORCE = RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXDATAFORCE(self)
        self.zz_fdict['TRAILTXDATAFORCE'] = self.TRAILTXDATAFORCE
        self.TRAILTXREPLEN = RM_Field_FRC_S_TRAILTXDATACTRL_TRAILTXREPLEN(self)
        self.zz_fdict['TRAILTXREPLEN'] = self.TRAILTXREPLEN
        self.TXSUPPLENOVERIDE = RM_Field_FRC_S_TRAILTXDATACTRL_TXSUPPLENOVERIDE(self)
        self.zz_fdict['TXSUPPLENOVERIDE'] = self.TXSUPPLENOVERIDE
        self.POSTAMBLEEN = RM_Field_FRC_S_TRAILTXDATACTRL_POSTAMBLEEN(self)
        self.zz_fdict['POSTAMBLEEN'] = self.POSTAMBLEEN
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_TRAILRXDATA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_TRAILRXDATA, self).__init__(rmio, label,
            0xa8004000, 0x054,
            'TRAILRXDATA', 'FRC_S.TRAILRXDATA', 'read-write',
            u"",
            0x00000000, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.RSSI = RM_Field_FRC_S_TRAILRXDATA_RSSI(self)
        self.zz_fdict['RSSI'] = self.RSSI
        self.CRCOK = RM_Field_FRC_S_TRAILRXDATA_CRCOK(self)
        self.zz_fdict['CRCOK'] = self.CRCOK
        self.PROTIMERCC0BASE = RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0BASE(self)
        self.zz_fdict['PROTIMERCC0BASE'] = self.PROTIMERCC0BASE
        self.PROTIMERCC0WRAPL = RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0WRAPL(self)
        self.zz_fdict['PROTIMERCC0WRAPL'] = self.PROTIMERCC0WRAPL
        self.PROTIMERCC0WRAPH = RM_Field_FRC_S_TRAILRXDATA_PROTIMERCC0WRAPH(self)
        self.zz_fdict['PROTIMERCC0WRAPH'] = self.PROTIMERCC0WRAPH
        self.RTCSTAMP = RM_Field_FRC_S_TRAILRXDATA_RTCSTAMP(self)
        self.zz_fdict['RTCSTAMP'] = self.RTCSTAMP
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_SCNT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_SCNT, self).__init__(rmio, label,
            0xa8004000, 0x058,
            'SCNT', 'FRC_S.SCNT', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SCNT = RM_Field_FRC_S_SCNT_SCNT(self)
        self.zz_fdict['SCNT'] = self.SCNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_CONVGENERATOR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_CONVGENERATOR, self).__init__(rmio, label,
            0xa8004000, 0x05C,
            'CONVGENERATOR', 'FRC_S.CONVGENERATOR', 'read-write',
            u"",
            0x00000000, 0x00037F7F,
            0x00001000, 0x00002000,
            0x00003000)

        self.GENERATOR0 = RM_Field_FRC_S_CONVGENERATOR_GENERATOR0(self)
        self.zz_fdict['GENERATOR0'] = self.GENERATOR0
        self.GENERATOR1 = RM_Field_FRC_S_CONVGENERATOR_GENERATOR1(self)
        self.zz_fdict['GENERATOR1'] = self.GENERATOR1
        self.RECURSIVE = RM_Field_FRC_S_CONVGENERATOR_RECURSIVE(self)
        self.zz_fdict['RECURSIVE'] = self.RECURSIVE
        self.NONSYSTEMATIC = RM_Field_FRC_S_CONVGENERATOR_NONSYSTEMATIC(self)
        self.zz_fdict['NONSYSTEMATIC'] = self.NONSYSTEMATIC
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PUNCTCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PUNCTCTRL, self).__init__(rmio, label,
            0xa8004000, 0x060,
            'PUNCTCTRL', 'FRC_S.PUNCTCTRL', 'read-write',
            u"",
            0x00000101, 0x00007F7F,
            0x00001000, 0x00002000,
            0x00003000)

        self.PUNCT0 = RM_Field_FRC_S_PUNCTCTRL_PUNCT0(self)
        self.zz_fdict['PUNCT0'] = self.PUNCT0
        self.PUNCT1 = RM_Field_FRC_S_PUNCTCTRL_PUNCT1(self)
        self.zz_fdict['PUNCT1'] = self.PUNCT1
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PAUSECTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PAUSECTRL, self).__init__(rmio, label,
            0xa8004000, 0x064,
            'PAUSECTRL', 'FRC_S.PAUSECTRL', 'read-write',
            u"",
            0x00000000, 0x07FFF83F,
            0x00001000, 0x00002000,
            0x00003000)

        self.FRAMEDETPAUSEEN = RM_Field_FRC_S_PAUSECTRL_FRAMEDETPAUSEEN(self)
        self.zz_fdict['FRAMEDETPAUSEEN'] = self.FRAMEDETPAUSEEN
        self.TXINTERLEAVEWRITEPAUSEEN = RM_Field_FRC_S_PAUSECTRL_TXINTERLEAVEWRITEPAUSEEN(self)
        self.zz_fdict['TXINTERLEAVEWRITEPAUSEEN'] = self.TXINTERLEAVEWRITEPAUSEEN
        self.RXINTERLEAVEWRITEPAUSEEN = RM_Field_FRC_S_PAUSECTRL_RXINTERLEAVEWRITEPAUSEEN(self)
        self.zz_fdict['RXINTERLEAVEWRITEPAUSEEN'] = self.RXINTERLEAVEWRITEPAUSEEN
        self.INTERLEAVEREADPAUSEEN = RM_Field_FRC_S_PAUSECTRL_INTERLEAVEREADPAUSEEN(self)
        self.zz_fdict['INTERLEAVEREADPAUSEEN'] = self.INTERLEAVEREADPAUSEEN
        self.TXSUBFRAMEPAUSEEN = RM_Field_FRC_S_PAUSECTRL_TXSUBFRAMEPAUSEEN(self)
        self.zz_fdict['TXSUBFRAMEPAUSEEN'] = self.TXSUBFRAMEPAUSEEN
        self.RXWCNTMATCHPAUSEEN = RM_Field_FRC_S_PAUSECTRL_RXWCNTMATCHPAUSEEN(self)
        self.zz_fdict['RXWCNTMATCHPAUSEEN'] = self.RXWCNTMATCHPAUSEEN
        self.CONVPAUSECNT = RM_Field_FRC_S_PAUSECTRL_CONVPAUSECNT(self)
        self.zz_fdict['CONVPAUSECNT'] = self.CONVPAUSECNT
        self.INTERLEAVEWRITEPAUSECNT = RM_Field_FRC_S_PAUSECTRL_INTERLEAVEWRITEPAUSECNT(self)
        self.zz_fdict['INTERLEAVEWRITEPAUSECNT'] = self.INTERLEAVEWRITEPAUSECNT
        self.INTERLEAVEREADPAUSECNT = RM_Field_FRC_S_PAUSECTRL_INTERLEAVEREADPAUSECNT(self)
        self.zz_fdict['INTERLEAVEREADPAUSECNT'] = self.INTERLEAVEREADPAUSECNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_IF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_IF, self).__init__(rmio, label,
            0xa8004000, 0x068,
            'IF', 'FRC_S.IF', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXDONE = RM_Field_FRC_S_IF_TXDONE(self)
        self.zz_fdict['TXDONE'] = self.TXDONE
        self.TXAFTERFRAMEDONE = RM_Field_FRC_S_IF_TXAFTERFRAMEDONE(self)
        self.zz_fdict['TXAFTERFRAMEDONE'] = self.TXAFTERFRAMEDONE
        self.TXABORTED = RM_Field_FRC_S_IF_TXABORTED(self)
        self.zz_fdict['TXABORTED'] = self.TXABORTED
        self.TXUF = RM_Field_FRC_S_IF_TXUF(self)
        self.zz_fdict['TXUF'] = self.TXUF
        self.RXDONE = RM_Field_FRC_S_IF_RXDONE(self)
        self.zz_fdict['RXDONE'] = self.RXDONE
        self.RXABORTED = RM_Field_FRC_S_IF_RXABORTED(self)
        self.zz_fdict['RXABORTED'] = self.RXABORTED
        self.FRAMEERROR = RM_Field_FRC_S_IF_FRAMEERROR(self)
        self.zz_fdict['FRAMEERROR'] = self.FRAMEERROR
        self.BLOCKERROR = RM_Field_FRC_S_IF_BLOCKERROR(self)
        self.zz_fdict['BLOCKERROR'] = self.BLOCKERROR
        self.RXOF = RM_Field_FRC_S_IF_RXOF(self)
        self.zz_fdict['RXOF'] = self.RXOF
        self.WCNTCMP0 = RM_Field_FRC_S_IF_WCNTCMP0(self)
        self.zz_fdict['WCNTCMP0'] = self.WCNTCMP0
        self.WCNTCMP1 = RM_Field_FRC_S_IF_WCNTCMP1(self)
        self.zz_fdict['WCNTCMP1'] = self.WCNTCMP1
        self.WCNTCMP2 = RM_Field_FRC_S_IF_WCNTCMP2(self)
        self.zz_fdict['WCNTCMP2'] = self.WCNTCMP2
        self.ADDRERROR = RM_Field_FRC_S_IF_ADDRERROR(self)
        self.zz_fdict['ADDRERROR'] = self.ADDRERROR
        self.BUSERROR = RM_Field_FRC_S_IF_BUSERROR(self)
        self.zz_fdict['BUSERROR'] = self.BUSERROR
        self.RXRAWEVENT = RM_Field_FRC_S_IF_RXRAWEVENT(self)
        self.zz_fdict['RXRAWEVENT'] = self.RXRAWEVENT
        self.TXRAWEVENT = RM_Field_FRC_S_IF_TXRAWEVENT(self)
        self.zz_fdict['TXRAWEVENT'] = self.TXRAWEVENT
        self.SNIFFOF = RM_Field_FRC_S_IF_SNIFFOF(self)
        self.zz_fdict['SNIFFOF'] = self.SNIFFOF
        self.WCNTCMP3 = RM_Field_FRC_S_IF_WCNTCMP3(self)
        self.zz_fdict['WCNTCMP3'] = self.WCNTCMP3
        self.WCNTCMP4 = RM_Field_FRC_S_IF_WCNTCMP4(self)
        self.zz_fdict['WCNTCMP4'] = self.WCNTCMP4
        self.BOISET = RM_Field_FRC_S_IF_BOISET(self)
        self.zz_fdict['BOISET'] = self.BOISET
        self.PKTBUFSTART = RM_Field_FRC_S_IF_PKTBUFSTART(self)
        self.zz_fdict['PKTBUFSTART'] = self.PKTBUFSTART
        self.PKTBUFTHRESHOLD = RM_Field_FRC_S_IF_PKTBUFTHRESHOLD(self)
        self.zz_fdict['PKTBUFTHRESHOLD'] = self.PKTBUFTHRESHOLD
        self.RXRAWOF = RM_Field_FRC_S_IF_RXRAWOF(self)
        self.zz_fdict['RXRAWOF'] = self.RXRAWOF
        self.WCNTCMP5 = RM_Field_FRC_S_IF_WCNTCMP5(self)
        self.zz_fdict['WCNTCMP5'] = self.WCNTCMP5
        self.FRAMEDETPAUSED = RM_Field_FRC_S_IF_FRAMEDETPAUSED(self)
        self.zz_fdict['FRAMEDETPAUSED'] = self.FRAMEDETPAUSED
        self.INTERLEAVEWRITEPAUSED = RM_Field_FRC_S_IF_INTERLEAVEWRITEPAUSED(self)
        self.zz_fdict['INTERLEAVEWRITEPAUSED'] = self.INTERLEAVEWRITEPAUSED
        self.INTERLEAVEREADPAUSED = RM_Field_FRC_S_IF_INTERLEAVEREADPAUSED(self)
        self.zz_fdict['INTERLEAVEREADPAUSED'] = self.INTERLEAVEREADPAUSED
        self.TXSUBFRAMEPAUSED = RM_Field_FRC_S_IF_TXSUBFRAMEPAUSED(self)
        self.zz_fdict['TXSUBFRAMEPAUSED'] = self.TXSUBFRAMEPAUSED
        self.CONVPAUSED = RM_Field_FRC_S_IF_CONVPAUSED(self)
        self.zz_fdict['CONVPAUSED'] = self.CONVPAUSED
        self.RXWORD = RM_Field_FRC_S_IF_RXWORD(self)
        self.zz_fdict['RXWORD'] = self.RXWORD
        self.TXWORD = RM_Field_FRC_S_IF_TXWORD(self)
        self.zz_fdict['TXWORD'] = self.TXWORD
        self.UARTERROR = RM_Field_FRC_S_IF_UARTERROR(self)
        self.zz_fdict['UARTERROR'] = self.UARTERROR
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_IEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_IEN, self).__init__(rmio, label,
            0xa8004000, 0x06C,
            'IEN', 'FRC_S.IEN', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXDONE = RM_Field_FRC_S_IEN_TXDONE(self)
        self.zz_fdict['TXDONE'] = self.TXDONE
        self.TXAFTERFRAMEDONE = RM_Field_FRC_S_IEN_TXAFTERFRAMEDONE(self)
        self.zz_fdict['TXAFTERFRAMEDONE'] = self.TXAFTERFRAMEDONE
        self.TXABORTED = RM_Field_FRC_S_IEN_TXABORTED(self)
        self.zz_fdict['TXABORTED'] = self.TXABORTED
        self.TXUF = RM_Field_FRC_S_IEN_TXUF(self)
        self.zz_fdict['TXUF'] = self.TXUF
        self.RXDONE = RM_Field_FRC_S_IEN_RXDONE(self)
        self.zz_fdict['RXDONE'] = self.RXDONE
        self.RXABORTED = RM_Field_FRC_S_IEN_RXABORTED(self)
        self.zz_fdict['RXABORTED'] = self.RXABORTED
        self.FRAMEERROR = RM_Field_FRC_S_IEN_FRAMEERROR(self)
        self.zz_fdict['FRAMEERROR'] = self.FRAMEERROR
        self.BLOCKERROR = RM_Field_FRC_S_IEN_BLOCKERROR(self)
        self.zz_fdict['BLOCKERROR'] = self.BLOCKERROR
        self.RXOF = RM_Field_FRC_S_IEN_RXOF(self)
        self.zz_fdict['RXOF'] = self.RXOF
        self.WCNTCMP0 = RM_Field_FRC_S_IEN_WCNTCMP0(self)
        self.zz_fdict['WCNTCMP0'] = self.WCNTCMP0
        self.WCNTCMP1 = RM_Field_FRC_S_IEN_WCNTCMP1(self)
        self.zz_fdict['WCNTCMP1'] = self.WCNTCMP1
        self.WCNTCMP2 = RM_Field_FRC_S_IEN_WCNTCMP2(self)
        self.zz_fdict['WCNTCMP2'] = self.WCNTCMP2
        self.ADDRERROR = RM_Field_FRC_S_IEN_ADDRERROR(self)
        self.zz_fdict['ADDRERROR'] = self.ADDRERROR
        self.BUSERROR = RM_Field_FRC_S_IEN_BUSERROR(self)
        self.zz_fdict['BUSERROR'] = self.BUSERROR
        self.RXRAWEVENT = RM_Field_FRC_S_IEN_RXRAWEVENT(self)
        self.zz_fdict['RXRAWEVENT'] = self.RXRAWEVENT
        self.TXRAWEVENT = RM_Field_FRC_S_IEN_TXRAWEVENT(self)
        self.zz_fdict['TXRAWEVENT'] = self.TXRAWEVENT
        self.SNIFFOF = RM_Field_FRC_S_IEN_SNIFFOF(self)
        self.zz_fdict['SNIFFOF'] = self.SNIFFOF
        self.WCNTCMP3 = RM_Field_FRC_S_IEN_WCNTCMP3(self)
        self.zz_fdict['WCNTCMP3'] = self.WCNTCMP3
        self.WCNTCMP4 = RM_Field_FRC_S_IEN_WCNTCMP4(self)
        self.zz_fdict['WCNTCMP4'] = self.WCNTCMP4
        self.BOISET = RM_Field_FRC_S_IEN_BOISET(self)
        self.zz_fdict['BOISET'] = self.BOISET
        self.PKTBUFSTART = RM_Field_FRC_S_IEN_PKTBUFSTART(self)
        self.zz_fdict['PKTBUFSTART'] = self.PKTBUFSTART
        self.PKTBUFTHRESHOLD = RM_Field_FRC_S_IEN_PKTBUFTHRESHOLD(self)
        self.zz_fdict['PKTBUFTHRESHOLD'] = self.PKTBUFTHRESHOLD
        self.RXRAWOF = RM_Field_FRC_S_IEN_RXRAWOF(self)
        self.zz_fdict['RXRAWOF'] = self.RXRAWOF
        self.WCNTCMP5 = RM_Field_FRC_S_IEN_WCNTCMP5(self)
        self.zz_fdict['WCNTCMP5'] = self.WCNTCMP5
        self.FRAMEDETPAUSED = RM_Field_FRC_S_IEN_FRAMEDETPAUSED(self)
        self.zz_fdict['FRAMEDETPAUSED'] = self.FRAMEDETPAUSED
        self.INTERLEAVEWRITEPAUSED = RM_Field_FRC_S_IEN_INTERLEAVEWRITEPAUSED(self)
        self.zz_fdict['INTERLEAVEWRITEPAUSED'] = self.INTERLEAVEWRITEPAUSED
        self.INTERLEAVEREADPAUSED = RM_Field_FRC_S_IEN_INTERLEAVEREADPAUSED(self)
        self.zz_fdict['INTERLEAVEREADPAUSED'] = self.INTERLEAVEREADPAUSED
        self.TXSUBFRAMEPAUSED = RM_Field_FRC_S_IEN_TXSUBFRAMEPAUSED(self)
        self.zz_fdict['TXSUBFRAMEPAUSED'] = self.TXSUBFRAMEPAUSED
        self.CONVPAUSED = RM_Field_FRC_S_IEN_CONVPAUSED(self)
        self.zz_fdict['CONVPAUSED'] = self.CONVPAUSED
        self.RXWORD = RM_Field_FRC_S_IEN_RXWORD(self)
        self.zz_fdict['RXWORD'] = self.RXWORD
        self.TXWORD = RM_Field_FRC_S_IEN_TXWORD(self)
        self.zz_fdict['TXWORD'] = self.TXWORD
        self.UARTERROR = RM_Field_FRC_S_IEN_UARTERROR(self)
        self.zz_fdict['UARTERROR'] = self.UARTERROR
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_OTACNT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_OTACNT, self).__init__(rmio, label,
            0xa8004000, 0x070,
            'OTACNT', 'FRC_S.OTACNT', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.OTARXCNT = RM_Field_FRC_S_OTACNT_OTARXCNT(self)
        self.zz_fdict['OTARXCNT'] = self.OTARXCNT
        self.OTATXCNT = RM_Field_FRC_S_OTACNT_OTATXCNT(self)
        self.zz_fdict['OTATXCNT'] = self.OTATXCNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_BUFFERMODE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_BUFFERMODE, self).__init__(rmio, label,
            0xa8004000, 0x078,
            'BUFFERMODE', 'FRC_S.BUFFERMODE', 'read-write',
            u"",
            0x00000000, 0x0000000F,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXBUFFERMODE = RM_Field_FRC_S_BUFFERMODE_TXBUFFERMODE(self)
        self.zz_fdict['TXBUFFERMODE'] = self.TXBUFFERMODE
        self.RXBUFFERMODE = RM_Field_FRC_S_BUFFERMODE_RXBUFFERMODE(self)
        self.zz_fdict['RXBUFFERMODE'] = self.RXBUFFERMODE
        self.RXFRCBUFMUX = RM_Field_FRC_S_BUFFERMODE_RXFRCBUFMUX(self)
        self.zz_fdict['RXFRCBUFMUX'] = self.RXFRCBUFMUX
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_SNIFFCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_SNIFFCTRL, self).__init__(rmio, label,
            0xa8004000, 0x084,
            'SNIFFCTRL', 'FRC_S.SNIFFCTRL', 'read-write',
            u"",
            0x000007FC, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SNIFFMODE = RM_Field_FRC_S_SNIFFCTRL_SNIFFMODE(self)
        self.zz_fdict['SNIFFMODE'] = self.SNIFFMODE
        self.SNIFFBITS = RM_Field_FRC_S_SNIFFCTRL_SNIFFBITS(self)
        self.zz_fdict['SNIFFBITS'] = self.SNIFFBITS
        self.SNIFFRXDATA = RM_Field_FRC_S_SNIFFCTRL_SNIFFRXDATA(self)
        self.zz_fdict['SNIFFRXDATA'] = self.SNIFFRXDATA
        self.SNIFFTXDATA = RM_Field_FRC_S_SNIFFCTRL_SNIFFTXDATA(self)
        self.zz_fdict['SNIFFTXDATA'] = self.SNIFFTXDATA
        self.SNIFFRSSI = RM_Field_FRC_S_SNIFFCTRL_SNIFFRSSI(self)
        self.zz_fdict['SNIFFRSSI'] = self.SNIFFRSSI
        self.SNIFFSTATE = RM_Field_FRC_S_SNIFFCTRL_SNIFFSTATE(self)
        self.zz_fdict['SNIFFSTATE'] = self.SNIFFSTATE
        self.SNIFFAUXDATA = RM_Field_FRC_S_SNIFFCTRL_SNIFFAUXDATA(self)
        self.zz_fdict['SNIFFAUXDATA'] = self.SNIFFAUXDATA
        self.SNIFFBR = RM_Field_FRC_S_SNIFFCTRL_SNIFFBR(self)
        self.zz_fdict['SNIFFBR'] = self.SNIFFBR
        self.SNIFFSLEEPCTRL = RM_Field_FRC_S_SNIFFCTRL_SNIFFSLEEPCTRL(self)
        self.zz_fdict['SNIFFSLEEPCTRL'] = self.SNIFFSLEEPCTRL
        self.SNIFFSYNCWORD = RM_Field_FRC_S_SNIFFCTRL_SNIFFSYNCWORD(self)
        self.zz_fdict['SNIFFSYNCWORD'] = self.SNIFFSYNCWORD
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_AUXDATA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_AUXDATA, self).__init__(rmio, label,
            0xa8004000, 0x088,
            'AUXDATA', 'FRC_S.AUXDATA', 'write-only',
            u"",
            0x00000000, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUXDATA = RM_Field_FRC_S_AUXDATA_AUXDATA(self)
        self.zz_fdict['AUXDATA'] = self.AUXDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_RAWCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_RAWCTRL, self).__init__(rmio, label,
            0xa8004000, 0x08C,
            'RAWCTRL', 'FRC_S.RAWCTRL', 'read-write',
            u"",
            0x00000000, 0x000021BF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXRAWMODE = RM_Field_FRC_S_RAWCTRL_TXRAWMODE(self)
        self.zz_fdict['TXRAWMODE'] = self.TXRAWMODE
        self.RXRAWMODE = RM_Field_FRC_S_RAWCTRL_RXRAWMODE(self)
        self.zz_fdict['RXRAWMODE'] = self.RXRAWMODE
        self.RXRAWRANDOM = RM_Field_FRC_S_RAWCTRL_RXRAWRANDOM(self)
        self.zz_fdict['RXRAWRANDOM'] = self.RXRAWRANDOM
        self.RXRAWTRIGGER = RM_Field_FRC_S_RAWCTRL_RXRAWTRIGGER(self)
        self.zz_fdict['RXRAWTRIGGER'] = self.RXRAWTRIGGER
        self.DEMODRAWDATAMUX = RM_Field_FRC_S_RAWCTRL_DEMODRAWDATAMUX(self)
        self.zz_fdict['DEMODRAWDATAMUX'] = self.DEMODRAWDATAMUX
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_RXRAWDATA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_RXRAWDATA, self).__init__(rmio, label,
            0xa8004000, 0x090,
            'RXRAWDATA', 'FRC_S.RXRAWDATA', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXRAWDATA = RM_Field_FRC_S_RXRAWDATA_RXRAWDATA(self)
        self.zz_fdict['RXRAWDATA'] = self.RXRAWDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PAUSEDATA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PAUSEDATA, self).__init__(rmio, label,
            0xa8004000, 0x094,
            'PAUSEDATA', 'FRC_S.PAUSEDATA', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PAUSEDATA = RM_Field_FRC_S_PAUSEDATA_PAUSEDATA(self)
        self.zz_fdict['PAUSEDATA'] = self.PAUSEDATA
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_LIKELYCONVSTATE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_LIKELYCONVSTATE, self).__init__(rmio, label,
            0xa8004000, 0x098,
            'LIKELYCONVSTATE', 'FRC_S.LIKELYCONVSTATE', 'read-only',
            u"",
            0x00000000, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.LIKELYCONVSTATE = RM_Field_FRC_S_LIKELYCONVSTATE_LIKELYCONVSTATE(self)
        self.zz_fdict['LIKELYCONVSTATE'] = self.LIKELYCONVSTATE
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENTNEXT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENTNEXT, self).__init__(rmio, label,
            0xa8004000, 0x09C,
            'INTELEMENTNEXT', 'FRC_S.INTELEMENTNEXT', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENTNEXT = RM_Field_FRC_S_INTELEMENTNEXT_INTELEMENTNEXT(self)
        self.zz_fdict['INTELEMENTNEXT'] = self.INTELEMENTNEXT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTWRITEPOINT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTWRITEPOINT, self).__init__(rmio, label,
            0xa8004000, 0x0A0,
            'INTWRITEPOINT', 'FRC_S.INTWRITEPOINT', 'read-write',
            u"",
            0x00000000, 0x0000001F,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTWRITEPOINT = RM_Field_FRC_S_INTWRITEPOINT_INTWRITEPOINT(self)
        self.zz_fdict['INTWRITEPOINT'] = self.INTWRITEPOINT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTREADPOINT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTREADPOINT, self).__init__(rmio, label,
            0xa8004000, 0x0A4,
            'INTREADPOINT', 'FRC_S.INTREADPOINT', 'read-write',
            u"",
            0x00000000, 0x0000001F,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTREADPOINT = RM_Field_FRC_S_INTREADPOINT_INTREADPOINT(self)
        self.zz_fdict['INTREADPOINT'] = self.INTREADPOINT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_AUTOCG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_AUTOCG, self).__init__(rmio, label,
            0xa8004000, 0x0A8,
            'AUTOCG', 'FRC_S.AUTOCG', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUTOCGEN = RM_Field_FRC_S_AUTOCG_AUTOCGEN(self)
        self.zz_fdict['AUTOCGEN'] = self.AUTOCGEN
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_CGCLKSTOP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_CGCLKSTOP, self).__init__(rmio, label,
            0xa8004000, 0x0AC,
            'CGCLKSTOP', 'FRC_S.CGCLKSTOP', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FORCEOFF = RM_Field_FRC_S_CGCLKSTOP_FORCEOFF(self)
        self.zz_fdict['FORCEOFF'] = self.FORCEOFF
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_SEQIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_SEQIF, self).__init__(rmio, label,
            0xa8004000, 0x0B4,
            'SEQIF', 'FRC_S.SEQIF', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXDONE = RM_Field_FRC_S_SEQIF_TXDONE(self)
        self.zz_fdict['TXDONE'] = self.TXDONE
        self.TXAFTERFRAMEDONE = RM_Field_FRC_S_SEQIF_TXAFTERFRAMEDONE(self)
        self.zz_fdict['TXAFTERFRAMEDONE'] = self.TXAFTERFRAMEDONE
        self.TXABORTED = RM_Field_FRC_S_SEQIF_TXABORTED(self)
        self.zz_fdict['TXABORTED'] = self.TXABORTED
        self.TXUF = RM_Field_FRC_S_SEQIF_TXUF(self)
        self.zz_fdict['TXUF'] = self.TXUF
        self.RXDONE = RM_Field_FRC_S_SEQIF_RXDONE(self)
        self.zz_fdict['RXDONE'] = self.RXDONE
        self.RXABORTED = RM_Field_FRC_S_SEQIF_RXABORTED(self)
        self.zz_fdict['RXABORTED'] = self.RXABORTED
        self.FRAMEERROR = RM_Field_FRC_S_SEQIF_FRAMEERROR(self)
        self.zz_fdict['FRAMEERROR'] = self.FRAMEERROR
        self.BLOCKERROR = RM_Field_FRC_S_SEQIF_BLOCKERROR(self)
        self.zz_fdict['BLOCKERROR'] = self.BLOCKERROR
        self.RXOF = RM_Field_FRC_S_SEQIF_RXOF(self)
        self.zz_fdict['RXOF'] = self.RXOF
        self.WCNTCMP0 = RM_Field_FRC_S_SEQIF_WCNTCMP0(self)
        self.zz_fdict['WCNTCMP0'] = self.WCNTCMP0
        self.WCNTCMP1 = RM_Field_FRC_S_SEQIF_WCNTCMP1(self)
        self.zz_fdict['WCNTCMP1'] = self.WCNTCMP1
        self.WCNTCMP2 = RM_Field_FRC_S_SEQIF_WCNTCMP2(self)
        self.zz_fdict['WCNTCMP2'] = self.WCNTCMP2
        self.ADDRERROR = RM_Field_FRC_S_SEQIF_ADDRERROR(self)
        self.zz_fdict['ADDRERROR'] = self.ADDRERROR
        self.BUSERROR = RM_Field_FRC_S_SEQIF_BUSERROR(self)
        self.zz_fdict['BUSERROR'] = self.BUSERROR
        self.RXRAWEVENT = RM_Field_FRC_S_SEQIF_RXRAWEVENT(self)
        self.zz_fdict['RXRAWEVENT'] = self.RXRAWEVENT
        self.TXRAWEVENT = RM_Field_FRC_S_SEQIF_TXRAWEVENT(self)
        self.zz_fdict['TXRAWEVENT'] = self.TXRAWEVENT
        self.SNIFFOF = RM_Field_FRC_S_SEQIF_SNIFFOF(self)
        self.zz_fdict['SNIFFOF'] = self.SNIFFOF
        self.WCNTCMP3 = RM_Field_FRC_S_SEQIF_WCNTCMP3(self)
        self.zz_fdict['WCNTCMP3'] = self.WCNTCMP3
        self.WCNTCMP4 = RM_Field_FRC_S_SEQIF_WCNTCMP4(self)
        self.zz_fdict['WCNTCMP4'] = self.WCNTCMP4
        self.BOISET = RM_Field_FRC_S_SEQIF_BOISET(self)
        self.zz_fdict['BOISET'] = self.BOISET
        self.PKTBUFSTART = RM_Field_FRC_S_SEQIF_PKTBUFSTART(self)
        self.zz_fdict['PKTBUFSTART'] = self.PKTBUFSTART
        self.PKTBUFTHRESHOLD = RM_Field_FRC_S_SEQIF_PKTBUFTHRESHOLD(self)
        self.zz_fdict['PKTBUFTHRESHOLD'] = self.PKTBUFTHRESHOLD
        self.RXRAWOF = RM_Field_FRC_S_SEQIF_RXRAWOF(self)
        self.zz_fdict['RXRAWOF'] = self.RXRAWOF
        self.WCNTCMP5 = RM_Field_FRC_S_SEQIF_WCNTCMP5(self)
        self.zz_fdict['WCNTCMP5'] = self.WCNTCMP5
        self.FRAMEDETPAUSED = RM_Field_FRC_S_SEQIF_FRAMEDETPAUSED(self)
        self.zz_fdict['FRAMEDETPAUSED'] = self.FRAMEDETPAUSED
        self.INTERLEAVEWRITEPAUSED = RM_Field_FRC_S_SEQIF_INTERLEAVEWRITEPAUSED(self)
        self.zz_fdict['INTERLEAVEWRITEPAUSED'] = self.INTERLEAVEWRITEPAUSED
        self.INTERLEAVEREADPAUSED = RM_Field_FRC_S_SEQIF_INTERLEAVEREADPAUSED(self)
        self.zz_fdict['INTERLEAVEREADPAUSED'] = self.INTERLEAVEREADPAUSED
        self.TXSUBFRAMEPAUSED = RM_Field_FRC_S_SEQIF_TXSUBFRAMEPAUSED(self)
        self.zz_fdict['TXSUBFRAMEPAUSED'] = self.TXSUBFRAMEPAUSED
        self.CONVPAUSED = RM_Field_FRC_S_SEQIF_CONVPAUSED(self)
        self.zz_fdict['CONVPAUSED'] = self.CONVPAUSED
        self.RXWORD = RM_Field_FRC_S_SEQIF_RXWORD(self)
        self.zz_fdict['RXWORD'] = self.RXWORD
        self.TXWORD = RM_Field_FRC_S_SEQIF_TXWORD(self)
        self.zz_fdict['TXWORD'] = self.TXWORD
        self.UARTERROR = RM_Field_FRC_S_SEQIF_UARTERROR(self)
        self.zz_fdict['UARTERROR'] = self.UARTERROR
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_SEQIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_SEQIEN, self).__init__(rmio, label,
            0xa8004000, 0x0B8,
            'SEQIEN', 'FRC_S.SEQIEN', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXDONE = RM_Field_FRC_S_SEQIEN_TXDONE(self)
        self.zz_fdict['TXDONE'] = self.TXDONE
        self.TXAFTERFRAMEDONE = RM_Field_FRC_S_SEQIEN_TXAFTERFRAMEDONE(self)
        self.zz_fdict['TXAFTERFRAMEDONE'] = self.TXAFTERFRAMEDONE
        self.TXABORTED = RM_Field_FRC_S_SEQIEN_TXABORTED(self)
        self.zz_fdict['TXABORTED'] = self.TXABORTED
        self.TXUF = RM_Field_FRC_S_SEQIEN_TXUF(self)
        self.zz_fdict['TXUF'] = self.TXUF
        self.RXDONE = RM_Field_FRC_S_SEQIEN_RXDONE(self)
        self.zz_fdict['RXDONE'] = self.RXDONE
        self.RXABORTED = RM_Field_FRC_S_SEQIEN_RXABORTED(self)
        self.zz_fdict['RXABORTED'] = self.RXABORTED
        self.FRAMEERROR = RM_Field_FRC_S_SEQIEN_FRAMEERROR(self)
        self.zz_fdict['FRAMEERROR'] = self.FRAMEERROR
        self.BLOCKERROR = RM_Field_FRC_S_SEQIEN_BLOCKERROR(self)
        self.zz_fdict['BLOCKERROR'] = self.BLOCKERROR
        self.RXOF = RM_Field_FRC_S_SEQIEN_RXOF(self)
        self.zz_fdict['RXOF'] = self.RXOF
        self.WCNTCMP0 = RM_Field_FRC_S_SEQIEN_WCNTCMP0(self)
        self.zz_fdict['WCNTCMP0'] = self.WCNTCMP0
        self.WCNTCMP1 = RM_Field_FRC_S_SEQIEN_WCNTCMP1(self)
        self.zz_fdict['WCNTCMP1'] = self.WCNTCMP1
        self.WCNTCMP2 = RM_Field_FRC_S_SEQIEN_WCNTCMP2(self)
        self.zz_fdict['WCNTCMP2'] = self.WCNTCMP2
        self.ADDRERROR = RM_Field_FRC_S_SEQIEN_ADDRERROR(self)
        self.zz_fdict['ADDRERROR'] = self.ADDRERROR
        self.BUSERROR = RM_Field_FRC_S_SEQIEN_BUSERROR(self)
        self.zz_fdict['BUSERROR'] = self.BUSERROR
        self.RXRAWEVENT = RM_Field_FRC_S_SEQIEN_RXRAWEVENT(self)
        self.zz_fdict['RXRAWEVENT'] = self.RXRAWEVENT
        self.TXRAWEVENT = RM_Field_FRC_S_SEQIEN_TXRAWEVENT(self)
        self.zz_fdict['TXRAWEVENT'] = self.TXRAWEVENT
        self.SNIFFOF = RM_Field_FRC_S_SEQIEN_SNIFFOF(self)
        self.zz_fdict['SNIFFOF'] = self.SNIFFOF
        self.WCNTCMP3 = RM_Field_FRC_S_SEQIEN_WCNTCMP3(self)
        self.zz_fdict['WCNTCMP3'] = self.WCNTCMP3
        self.WCNTCMP4 = RM_Field_FRC_S_SEQIEN_WCNTCMP4(self)
        self.zz_fdict['WCNTCMP4'] = self.WCNTCMP4
        self.BOISET = RM_Field_FRC_S_SEQIEN_BOISET(self)
        self.zz_fdict['BOISET'] = self.BOISET
        self.PKTBUFSTART = RM_Field_FRC_S_SEQIEN_PKTBUFSTART(self)
        self.zz_fdict['PKTBUFSTART'] = self.PKTBUFSTART
        self.PKTBUFTHRESHOLD = RM_Field_FRC_S_SEQIEN_PKTBUFTHRESHOLD(self)
        self.zz_fdict['PKTBUFTHRESHOLD'] = self.PKTBUFTHRESHOLD
        self.RXRAWOF = RM_Field_FRC_S_SEQIEN_RXRAWOF(self)
        self.zz_fdict['RXRAWOF'] = self.RXRAWOF
        self.WCNTCMP5 = RM_Field_FRC_S_SEQIEN_WCNTCMP5(self)
        self.zz_fdict['WCNTCMP5'] = self.WCNTCMP5
        self.FRAMEDETPAUSED = RM_Field_FRC_S_SEQIEN_FRAMEDETPAUSED(self)
        self.zz_fdict['FRAMEDETPAUSED'] = self.FRAMEDETPAUSED
        self.INTERLEAVEWRITEPAUSED = RM_Field_FRC_S_SEQIEN_INTERLEAVEWRITEPAUSED(self)
        self.zz_fdict['INTERLEAVEWRITEPAUSED'] = self.INTERLEAVEWRITEPAUSED
        self.INTERLEAVEREADPAUSED = RM_Field_FRC_S_SEQIEN_INTERLEAVEREADPAUSED(self)
        self.zz_fdict['INTERLEAVEREADPAUSED'] = self.INTERLEAVEREADPAUSED
        self.TXSUBFRAMEPAUSED = RM_Field_FRC_S_SEQIEN_TXSUBFRAMEPAUSED(self)
        self.zz_fdict['TXSUBFRAMEPAUSED'] = self.TXSUBFRAMEPAUSED
        self.CONVPAUSED = RM_Field_FRC_S_SEQIEN_CONVPAUSED(self)
        self.zz_fdict['CONVPAUSED'] = self.CONVPAUSED
        self.RXWORD = RM_Field_FRC_S_SEQIEN_RXWORD(self)
        self.zz_fdict['RXWORD'] = self.RXWORD
        self.TXWORD = RM_Field_FRC_S_SEQIEN_TXWORD(self)
        self.zz_fdict['TXWORD'] = self.TXWORD
        self.UARTERROR = RM_Field_FRC_S_SEQIEN_UARTERROR(self)
        self.zz_fdict['UARTERROR'] = self.UARTERROR
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WCNTCMP3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WCNTCMP3, self).__init__(rmio, label,
            0xa8004000, 0x0BC,
            'WCNTCMP3', 'FRC_S.WCNTCMP3', 'read-write',
            u"",
            0x00000000, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SUPPLENFIELDLOC = RM_Field_FRC_S_WCNTCMP3_SUPPLENFIELDLOC(self)
        self.zz_fdict['SUPPLENFIELDLOC'] = self.SUPPLENFIELDLOC
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_BOICTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_BOICTRL, self).__init__(rmio, label,
            0xa8004000, 0x0C0,
            'BOICTRL', 'FRC_S.BOICTRL', 'read-write',
            u"",
            0x00000000, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BOIEN = RM_Field_FRC_S_BOICTRL_BOIEN(self)
        self.zz_fdict['BOIEN'] = self.BOIEN
        self.BOIFIELDLOC = RM_Field_FRC_S_BOICTRL_BOIFIELDLOC(self)
        self.zz_fdict['BOIFIELDLOC'] = self.BOIFIELDLOC
        self.BOIBITPOS = RM_Field_FRC_S_BOICTRL_BOIBITPOS(self)
        self.zz_fdict['BOIBITPOS'] = self.BOIBITPOS
        self.BOIMATCHVAL = RM_Field_FRC_S_BOICTRL_BOIMATCHVAL(self)
        self.zz_fdict['BOIMATCHVAL'] = self.BOIMATCHVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_DSLCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_DSLCTRL, self).__init__(rmio, label,
            0xa8004000, 0x0C4,
            'DSLCTRL', 'FRC_S.DSLCTRL', 'read-write',
            u"",
            0x00000000, 0x7FFFFF7F,
            0x00001000, 0x00002000,
            0x00003000)

        self.DSLMODE = RM_Field_FRC_S_DSLCTRL_DSLMODE(self)
        self.zz_fdict['DSLMODE'] = self.DSLMODE
        self.DSLBITORDER = RM_Field_FRC_S_DSLCTRL_DSLBITORDER(self)
        self.zz_fdict['DSLBITORDER'] = self.DSLBITORDER
        self.DSLSHIFT = RM_Field_FRC_S_DSLCTRL_DSLSHIFT(self)
        self.zz_fdict['DSLSHIFT'] = self.DSLSHIFT
        self.DSLOFFSET = RM_Field_FRC_S_DSLCTRL_DSLOFFSET(self)
        self.zz_fdict['DSLOFFSET'] = self.DSLOFFSET
        self.DSLBITS = RM_Field_FRC_S_DSLCTRL_DSLBITS(self)
        self.zz_fdict['DSLBITS'] = self.DSLBITS
        self.DSLMINLENGTH = RM_Field_FRC_S_DSLCTRL_DSLMINLENGTH(self)
        self.zz_fdict['DSLMINLENGTH'] = self.DSLMINLENGTH
        self.RXSUPRECEPMODE = RM_Field_FRC_S_DSLCTRL_RXSUPRECEPMODE(self)
        self.zz_fdict['RXSUPRECEPMODE'] = self.RXSUPRECEPMODE
        self.STORESUP = RM_Field_FRC_S_DSLCTRL_STORESUP(self)
        self.zz_fdict['STORESUP'] = self.STORESUP
        self.SUPSHFFACTOR = RM_Field_FRC_S_DSLCTRL_SUPSHFFACTOR(self)
        self.zz_fdict['SUPSHFFACTOR'] = self.SUPSHFFACTOR
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WCNTCMP4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WCNTCMP4, self).__init__(rmio, label,
            0xa8004000, 0x0C8,
            'WCNTCMP4', 'FRC_S.WCNTCMP4', 'read-write',
            u"",
            0x00000000, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SUPPLENGTH = RM_Field_FRC_S_WCNTCMP4_SUPPLENGTH(self)
        self.zz_fdict['SUPPLENGTH'] = self.SUPPLENGTH
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_WCNTCMP5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_WCNTCMP5, self).__init__(rmio, label,
            0xa8004000, 0x0CC,
            'WCNTCMP5', 'FRC_S.WCNTCMP5', 'read-write',
            u"",
            0x00000000, 0x00000FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXPAUSELOC = RM_Field_FRC_S_WCNTCMP5_RXPAUSELOC(self)
        self.zz_fdict['RXPAUSELOC'] = self.RXPAUSELOC
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUFCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUFCTRL, self).__init__(rmio, label,
            0xa8004000, 0x0D0,
            'PKTBUFCTRL', 'FRC_S.PKTBUFCTRL', 'read-write',
            u"",
            0x00000000, 0x0303FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUFSTARTLOC = RM_Field_FRC_S_PKTBUFCTRL_PKTBUFSTARTLOC(self)
        self.zz_fdict['PKTBUFSTARTLOC'] = self.PKTBUFSTARTLOC
        self.PKTBUFTHRESHOLD = RM_Field_FRC_S_PKTBUFCTRL_PKTBUFTHRESHOLD(self)
        self.zz_fdict['PKTBUFTHRESHOLD'] = self.PKTBUFTHRESHOLD
        self.PKTBUFTHRESHOLDEN = RM_Field_FRC_S_PKTBUFCTRL_PKTBUFTHRESHOLDEN(self)
        self.zz_fdict['PKTBUFTHRESHOLDEN'] = self.PKTBUFTHRESHOLDEN
        self.PKTBUFSTOP = RM_Field_FRC_S_PKTBUFCTRL_PKTBUFSTOP(self)
        self.zz_fdict['PKTBUFSTOP'] = self.PKTBUFSTOP
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUFSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUFSTATUS, self).__init__(rmio, label,
            0xa8004000, 0x0D4,
            'PKTBUFSTATUS', 'FRC_S.PKTBUFSTATUS', 'read-only',
            u"",
            0x00000000, 0x0000003F,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUFCOUNT = RM_Field_FRC_S_PKTBUFSTATUS_PKTBUFCOUNT(self)
        self.zz_fdict['PKTBUFCOUNT'] = self.PKTBUFCOUNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF0, self).__init__(rmio, label,
            0xa8004000, 0x0D8,
            'PKTBUF0', 'FRC_S.PKTBUF0', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF0 = RM_Field_FRC_S_PKTBUF0_PKTBUF0(self)
        self.zz_fdict['PKTBUF0'] = self.PKTBUF0
        self.PKTBUF1 = RM_Field_FRC_S_PKTBUF0_PKTBUF1(self)
        self.zz_fdict['PKTBUF1'] = self.PKTBUF1
        self.PKTBUF2 = RM_Field_FRC_S_PKTBUF0_PKTBUF2(self)
        self.zz_fdict['PKTBUF2'] = self.PKTBUF2
        self.PKTBUF3 = RM_Field_FRC_S_PKTBUF0_PKTBUF3(self)
        self.zz_fdict['PKTBUF3'] = self.PKTBUF3
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF1, self).__init__(rmio, label,
            0xa8004000, 0x0DC,
            'PKTBUF1', 'FRC_S.PKTBUF1', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF4 = RM_Field_FRC_S_PKTBUF1_PKTBUF4(self)
        self.zz_fdict['PKTBUF4'] = self.PKTBUF4
        self.PKTBUF5 = RM_Field_FRC_S_PKTBUF1_PKTBUF5(self)
        self.zz_fdict['PKTBUF5'] = self.PKTBUF5
        self.PKTBUF6 = RM_Field_FRC_S_PKTBUF1_PKTBUF6(self)
        self.zz_fdict['PKTBUF6'] = self.PKTBUF6
        self.PKTBUF7 = RM_Field_FRC_S_PKTBUF1_PKTBUF7(self)
        self.zz_fdict['PKTBUF7'] = self.PKTBUF7
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF2, self).__init__(rmio, label,
            0xa8004000, 0x0E0,
            'PKTBUF2', 'FRC_S.PKTBUF2', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF8 = RM_Field_FRC_S_PKTBUF2_PKTBUF8(self)
        self.zz_fdict['PKTBUF8'] = self.PKTBUF8
        self.PKTBUF9 = RM_Field_FRC_S_PKTBUF2_PKTBUF9(self)
        self.zz_fdict['PKTBUF9'] = self.PKTBUF9
        self.PKTBUF10 = RM_Field_FRC_S_PKTBUF2_PKTBUF10(self)
        self.zz_fdict['PKTBUF10'] = self.PKTBUF10
        self.PKTBUF11 = RM_Field_FRC_S_PKTBUF2_PKTBUF11(self)
        self.zz_fdict['PKTBUF11'] = self.PKTBUF11
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF3, self).__init__(rmio, label,
            0xa8004000, 0x0E4,
            'PKTBUF3', 'FRC_S.PKTBUF3', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF12 = RM_Field_FRC_S_PKTBUF3_PKTBUF12(self)
        self.zz_fdict['PKTBUF12'] = self.PKTBUF12
        self.PKTBUF13 = RM_Field_FRC_S_PKTBUF3_PKTBUF13(self)
        self.zz_fdict['PKTBUF13'] = self.PKTBUF13
        self.PKTBUF14 = RM_Field_FRC_S_PKTBUF3_PKTBUF14(self)
        self.zz_fdict['PKTBUF14'] = self.PKTBUF14
        self.PKTBUF15 = RM_Field_FRC_S_PKTBUF3_PKTBUF15(self)
        self.zz_fdict['PKTBUF15'] = self.PKTBUF15
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF4, self).__init__(rmio, label,
            0xa8004000, 0x0E8,
            'PKTBUF4', 'FRC_S.PKTBUF4', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF16 = RM_Field_FRC_S_PKTBUF4_PKTBUF16(self)
        self.zz_fdict['PKTBUF16'] = self.PKTBUF16
        self.PKTBUF17 = RM_Field_FRC_S_PKTBUF4_PKTBUF17(self)
        self.zz_fdict['PKTBUF17'] = self.PKTBUF17
        self.PKTBUF18 = RM_Field_FRC_S_PKTBUF4_PKTBUF18(self)
        self.zz_fdict['PKTBUF18'] = self.PKTBUF18
        self.PKTBUF19 = RM_Field_FRC_S_PKTBUF4_PKTBUF19(self)
        self.zz_fdict['PKTBUF19'] = self.PKTBUF19
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF5, self).__init__(rmio, label,
            0xa8004000, 0x0EC,
            'PKTBUF5', 'FRC_S.PKTBUF5', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF20 = RM_Field_FRC_S_PKTBUF5_PKTBUF20(self)
        self.zz_fdict['PKTBUF20'] = self.PKTBUF20
        self.PKTBUF21 = RM_Field_FRC_S_PKTBUF5_PKTBUF21(self)
        self.zz_fdict['PKTBUF21'] = self.PKTBUF21
        self.PKTBUF22 = RM_Field_FRC_S_PKTBUF5_PKTBUF22(self)
        self.zz_fdict['PKTBUF22'] = self.PKTBUF22
        self.PKTBUF23 = RM_Field_FRC_S_PKTBUF5_PKTBUF23(self)
        self.zz_fdict['PKTBUF23'] = self.PKTBUF23
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF6, self).__init__(rmio, label,
            0xa8004000, 0x0F0,
            'PKTBUF6', 'FRC_S.PKTBUF6', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF24 = RM_Field_FRC_S_PKTBUF6_PKTBUF24(self)
        self.zz_fdict['PKTBUF24'] = self.PKTBUF24
        self.PKTBUF25 = RM_Field_FRC_S_PKTBUF6_PKTBUF25(self)
        self.zz_fdict['PKTBUF25'] = self.PKTBUF25
        self.PKTBUF26 = RM_Field_FRC_S_PKTBUF6_PKTBUF26(self)
        self.zz_fdict['PKTBUF26'] = self.PKTBUF26
        self.PKTBUF27 = RM_Field_FRC_S_PKTBUF6_PKTBUF27(self)
        self.zz_fdict['PKTBUF27'] = self.PKTBUF27
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF7, self).__init__(rmio, label,
            0xa8004000, 0x0F4,
            'PKTBUF7', 'FRC_S.PKTBUF7', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF28 = RM_Field_FRC_S_PKTBUF7_PKTBUF28(self)
        self.zz_fdict['PKTBUF28'] = self.PKTBUF28
        self.PKTBUF29 = RM_Field_FRC_S_PKTBUF7_PKTBUF29(self)
        self.zz_fdict['PKTBUF29'] = self.PKTBUF29
        self.PKTBUF30 = RM_Field_FRC_S_PKTBUF7_PKTBUF30(self)
        self.zz_fdict['PKTBUF30'] = self.PKTBUF30
        self.PKTBUF31 = RM_Field_FRC_S_PKTBUF7_PKTBUF31(self)
        self.zz_fdict['PKTBUF31'] = self.PKTBUF31
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF8, self).__init__(rmio, label,
            0xa8004000, 0x0F8,
            'PKTBUF8', 'FRC_S.PKTBUF8', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF32 = RM_Field_FRC_S_PKTBUF8_PKTBUF32(self)
        self.zz_fdict['PKTBUF32'] = self.PKTBUF32
        self.PKTBUF33 = RM_Field_FRC_S_PKTBUF8_PKTBUF33(self)
        self.zz_fdict['PKTBUF33'] = self.PKTBUF33
        self.PKTBUF34 = RM_Field_FRC_S_PKTBUF8_PKTBUF34(self)
        self.zz_fdict['PKTBUF34'] = self.PKTBUF34
        self.PKTBUF35 = RM_Field_FRC_S_PKTBUF8_PKTBUF35(self)
        self.zz_fdict['PKTBUF35'] = self.PKTBUF35
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF9, self).__init__(rmio, label,
            0xa8004000, 0x0FC,
            'PKTBUF9', 'FRC_S.PKTBUF9', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF36 = RM_Field_FRC_S_PKTBUF9_PKTBUF36(self)
        self.zz_fdict['PKTBUF36'] = self.PKTBUF36
        self.PKTBUF37 = RM_Field_FRC_S_PKTBUF9_PKTBUF37(self)
        self.zz_fdict['PKTBUF37'] = self.PKTBUF37
        self.PKTBUF38 = RM_Field_FRC_S_PKTBUF9_PKTBUF38(self)
        self.zz_fdict['PKTBUF38'] = self.PKTBUF38
        self.PKTBUF39 = RM_Field_FRC_S_PKTBUF9_PKTBUF39(self)
        self.zz_fdict['PKTBUF39'] = self.PKTBUF39
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF10, self).__init__(rmio, label,
            0xa8004000, 0x100,
            'PKTBUF10', 'FRC_S.PKTBUF10', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF40 = RM_Field_FRC_S_PKTBUF10_PKTBUF40(self)
        self.zz_fdict['PKTBUF40'] = self.PKTBUF40
        self.PKTBUF41 = RM_Field_FRC_S_PKTBUF10_PKTBUF41(self)
        self.zz_fdict['PKTBUF41'] = self.PKTBUF41
        self.PKTBUF42 = RM_Field_FRC_S_PKTBUF10_PKTBUF42(self)
        self.zz_fdict['PKTBUF42'] = self.PKTBUF42
        self.PKTBUF43 = RM_Field_FRC_S_PKTBUF10_PKTBUF43(self)
        self.zz_fdict['PKTBUF43'] = self.PKTBUF43
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_PKTBUF11(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_PKTBUF11, self).__init__(rmio, label,
            0xa8004000, 0x104,
            'PKTBUF11', 'FRC_S.PKTBUF11', 'read-only',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PKTBUF44 = RM_Field_FRC_S_PKTBUF11_PKTBUF44(self)
        self.zz_fdict['PKTBUF44'] = self.PKTBUF44
        self.PKTBUF45 = RM_Field_FRC_S_PKTBUF11_PKTBUF45(self)
        self.zz_fdict['PKTBUF45'] = self.PKTBUF45
        self.PKTBUF46 = RM_Field_FRC_S_PKTBUF11_PKTBUF46(self)
        self.zz_fdict['PKTBUF46'] = self.PKTBUF46
        self.PKTBUF47 = RM_Field_FRC_S_PKTBUF11_PKTBUF47(self)
        self.zz_fdict['PKTBUF47'] = self.PKTBUF47
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_FCD0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_FCD0, self).__init__(rmio, label,
            0xa8004000, 0x108,
            'FCD0', 'FRC_S.FCD0', 'read-write',
            u"",
            0x000000FF, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.WORDS = RM_Field_FRC_S_FCD0_WORDS(self)
        self.zz_fdict['WORDS'] = self.WORDS
        self.BUFFER = RM_Field_FRC_S_FCD0_BUFFER(self)
        self.zz_fdict['BUFFER'] = self.BUFFER
        self.INCLUDECRC = RM_Field_FRC_S_FCD0_INCLUDECRC(self)
        self.zz_fdict['INCLUDECRC'] = self.INCLUDECRC
        self.CALCCRC = RM_Field_FRC_S_FCD0_CALCCRC(self)
        self.zz_fdict['CALCCRC'] = self.CALCCRC
        self.SKIPCRC = RM_Field_FRC_S_FCD0_SKIPCRC(self)
        self.zz_fdict['SKIPCRC'] = self.SKIPCRC
        self.SKIPWHITE = RM_Field_FRC_S_FCD0_SKIPWHITE(self)
        self.zz_fdict['SKIPWHITE'] = self.SKIPWHITE
        self.ADDTRAILTXDATA = RM_Field_FRC_S_FCD0_ADDTRAILTXDATA(self)
        self.zz_fdict['ADDTRAILTXDATA'] = self.ADDTRAILTXDATA
        self.EXCLUDESUBFRAMEWCNT = RM_Field_FRC_S_FCD0_EXCLUDESUBFRAMEWCNT(self)
        self.zz_fdict['EXCLUDESUBFRAMEWCNT'] = self.EXCLUDESUBFRAMEWCNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_FCD1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_FCD1, self).__init__(rmio, label,
            0xa8004000, 0x10C,
            'FCD1', 'FRC_S.FCD1', 'read-write',
            u"",
            0x000000FF, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.WORDS = RM_Field_FRC_S_FCD1_WORDS(self)
        self.zz_fdict['WORDS'] = self.WORDS
        self.BUFFER = RM_Field_FRC_S_FCD1_BUFFER(self)
        self.zz_fdict['BUFFER'] = self.BUFFER
        self.INCLUDECRC = RM_Field_FRC_S_FCD1_INCLUDECRC(self)
        self.zz_fdict['INCLUDECRC'] = self.INCLUDECRC
        self.CALCCRC = RM_Field_FRC_S_FCD1_CALCCRC(self)
        self.zz_fdict['CALCCRC'] = self.CALCCRC
        self.SKIPCRC = RM_Field_FRC_S_FCD1_SKIPCRC(self)
        self.zz_fdict['SKIPCRC'] = self.SKIPCRC
        self.SKIPWHITE = RM_Field_FRC_S_FCD1_SKIPWHITE(self)
        self.zz_fdict['SKIPWHITE'] = self.SKIPWHITE
        self.ADDTRAILTXDATA = RM_Field_FRC_S_FCD1_ADDTRAILTXDATA(self)
        self.zz_fdict['ADDTRAILTXDATA'] = self.ADDTRAILTXDATA
        self.EXCLUDESUBFRAMEWCNT = RM_Field_FRC_S_FCD1_EXCLUDESUBFRAMEWCNT(self)
        self.zz_fdict['EXCLUDESUBFRAMEWCNT'] = self.EXCLUDESUBFRAMEWCNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_FCD2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_FCD2, self).__init__(rmio, label,
            0xa8004000, 0x110,
            'FCD2', 'FRC_S.FCD2', 'read-write',
            u"",
            0x000000FF, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.WORDS = RM_Field_FRC_S_FCD2_WORDS(self)
        self.zz_fdict['WORDS'] = self.WORDS
        self.BUFFER = RM_Field_FRC_S_FCD2_BUFFER(self)
        self.zz_fdict['BUFFER'] = self.BUFFER
        self.INCLUDECRC = RM_Field_FRC_S_FCD2_INCLUDECRC(self)
        self.zz_fdict['INCLUDECRC'] = self.INCLUDECRC
        self.CALCCRC = RM_Field_FRC_S_FCD2_CALCCRC(self)
        self.zz_fdict['CALCCRC'] = self.CALCCRC
        self.SKIPCRC = RM_Field_FRC_S_FCD2_SKIPCRC(self)
        self.zz_fdict['SKIPCRC'] = self.SKIPCRC
        self.SKIPWHITE = RM_Field_FRC_S_FCD2_SKIPWHITE(self)
        self.zz_fdict['SKIPWHITE'] = self.SKIPWHITE
        self.ADDTRAILTXDATA = RM_Field_FRC_S_FCD2_ADDTRAILTXDATA(self)
        self.zz_fdict['ADDTRAILTXDATA'] = self.ADDTRAILTXDATA
        self.EXCLUDESUBFRAMEWCNT = RM_Field_FRC_S_FCD2_EXCLUDESUBFRAMEWCNT(self)
        self.zz_fdict['EXCLUDESUBFRAMEWCNT'] = self.EXCLUDESUBFRAMEWCNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_FCD3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_FCD3, self).__init__(rmio, label,
            0xa8004000, 0x114,
            'FCD3', 'FRC_S.FCD3', 'read-write',
            u"",
            0x000000FF, 0x0001FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.WORDS = RM_Field_FRC_S_FCD3_WORDS(self)
        self.zz_fdict['WORDS'] = self.WORDS
        self.BUFFER = RM_Field_FRC_S_FCD3_BUFFER(self)
        self.zz_fdict['BUFFER'] = self.BUFFER
        self.INCLUDECRC = RM_Field_FRC_S_FCD3_INCLUDECRC(self)
        self.zz_fdict['INCLUDECRC'] = self.INCLUDECRC
        self.CALCCRC = RM_Field_FRC_S_FCD3_CALCCRC(self)
        self.zz_fdict['CALCCRC'] = self.CALCCRC
        self.SKIPCRC = RM_Field_FRC_S_FCD3_SKIPCRC(self)
        self.zz_fdict['SKIPCRC'] = self.SKIPCRC
        self.SKIPWHITE = RM_Field_FRC_S_FCD3_SKIPWHITE(self)
        self.zz_fdict['SKIPWHITE'] = self.SKIPWHITE
        self.ADDTRAILTXDATA = RM_Field_FRC_S_FCD3_ADDTRAILTXDATA(self)
        self.zz_fdict['ADDTRAILTXDATA'] = self.ADDTRAILTXDATA
        self.EXCLUDESUBFRAMEWCNT = RM_Field_FRC_S_FCD3_EXCLUDESUBFRAMEWCNT(self)
        self.zz_fdict['EXCLUDESUBFRAMEWCNT'] = self.EXCLUDESUBFRAMEWCNT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT0, self).__init__(rmio, label,
            0xa8004000, 0x140,
            'INTELEMENT0', 'FRC_S.INTELEMENT0', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT0_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT1, self).__init__(rmio, label,
            0xa8004000, 0x144,
            'INTELEMENT1', 'FRC_S.INTELEMENT1', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT1_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT2, self).__init__(rmio, label,
            0xa8004000, 0x148,
            'INTELEMENT2', 'FRC_S.INTELEMENT2', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT2_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT3, self).__init__(rmio, label,
            0xa8004000, 0x14C,
            'INTELEMENT3', 'FRC_S.INTELEMENT3', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT3_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT4, self).__init__(rmio, label,
            0xa8004000, 0x150,
            'INTELEMENT4', 'FRC_S.INTELEMENT4', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT4_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT5, self).__init__(rmio, label,
            0xa8004000, 0x154,
            'INTELEMENT5', 'FRC_S.INTELEMENT5', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT5_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT6, self).__init__(rmio, label,
            0xa8004000, 0x158,
            'INTELEMENT6', 'FRC_S.INTELEMENT6', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT6_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT7, self).__init__(rmio, label,
            0xa8004000, 0x15C,
            'INTELEMENT7', 'FRC_S.INTELEMENT7', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT7_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT8, self).__init__(rmio, label,
            0xa8004000, 0x160,
            'INTELEMENT8', 'FRC_S.INTELEMENT8', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT8_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT9, self).__init__(rmio, label,
            0xa8004000, 0x164,
            'INTELEMENT9', 'FRC_S.INTELEMENT9', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT9_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT10, self).__init__(rmio, label,
            0xa8004000, 0x168,
            'INTELEMENT10', 'FRC_S.INTELEMENT10', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT10_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT11(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT11, self).__init__(rmio, label,
            0xa8004000, 0x16C,
            'INTELEMENT11', 'FRC_S.INTELEMENT11', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT11_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT12(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT12, self).__init__(rmio, label,
            0xa8004000, 0x170,
            'INTELEMENT12', 'FRC_S.INTELEMENT12', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT12_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT13(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT13, self).__init__(rmio, label,
            0xa8004000, 0x174,
            'INTELEMENT13', 'FRC_S.INTELEMENT13', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT13_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT14(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT14, self).__init__(rmio, label,
            0xa8004000, 0x178,
            'INTELEMENT14', 'FRC_S.INTELEMENT14', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT14_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_INTELEMENT15(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_INTELEMENT15, self).__init__(rmio, label,
            0xa8004000, 0x17C,
            'INTELEMENT15', 'FRC_S.INTELEMENT15', 'read-only',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.INTELEMENT = RM_Field_FRC_S_INTELEMENT15_INTELEMENT(self)
        self.zz_fdict['INTELEMENT'] = self.INTELEMENT
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_AHBCONFIG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_AHBCONFIG, self).__init__(rmio, label,
            0xa8004000, 0x180,
            'AHBCONFIG', 'FRC_S.AHBCONFIG', 'read-write',
            u"",
            0x00000001, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.AHBHPROTBUFFERABLE = RM_Field_FRC_S_AHBCONFIG_AHBHPROTBUFFERABLE(self)
        self.zz_fdict['AHBHPROTBUFFERABLE'] = self.AHBHPROTBUFFERABLE
        self.__dict__['zz_frozen'] = True


class RM_Register_FRC_S_SPARE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_FRC_S_SPARE, self).__init__(rmio, label,
            0xa8004000, 0x184,
            'SPARE', 'FRC_S.SPARE', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SPARE = RM_Field_FRC_S_SPARE_SPARE(self)
        self.zz_fdict['SPARE'] = self.SPARE
        self.__dict__['zz_frozen'] = True



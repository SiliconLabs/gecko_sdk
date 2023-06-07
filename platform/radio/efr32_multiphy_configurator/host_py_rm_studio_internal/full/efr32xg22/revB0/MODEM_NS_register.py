
# -*- coding: utf-8 -*-

from . static import Base_RM_Register
from . MODEM_NS_field import *


class RM_Register_MODEM_NS_IPVERSION(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IPVERSION, self).__init__(rmio, label,
            0xb8014000, 0x000,
            'IPVERSION', 'MODEM_NS.IPVERSION', 'read-only',
            u"",
            0x00000001, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IPVERSION = RM_Field_MODEM_NS_IPVERSION_IPVERSION(self)
        self.zz_fdict['IPVERSION'] = self.IPVERSION
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_EN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_EN, self).__init__(rmio, label,
            0xb8014000, 0x004,
            'EN', 'MODEM_NS.EN', 'read-write',
            u"",
            0x00000000, 0x00000001,
            0x00001000, 0x00002000,
            0x00003000)

        self.EN = RM_Field_MODEM_NS_EN_EN(self)
        self.zz_fdict['EN'] = self.EN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS, self).__init__(rmio, label,
            0xb8014000, 0x008,
            'STATUS', 'MODEM_NS.STATUS', 'read-only',
            u"",
            0x00000000, 0xFFFF7FF7,
            0x00001000, 0x00002000,
            0x00003000)

        self.DEMODSTATE = RM_Field_MODEM_NS_STATUS_DEMODSTATE(self)
        self.zz_fdict['DEMODSTATE'] = self.DEMODSTATE
        self.FRAMEDETID = RM_Field_MODEM_NS_STATUS_FRAMEDETID(self)
        self.zz_fdict['FRAMEDETID'] = self.FRAMEDETID
        self.ANTSEL = RM_Field_MODEM_NS_STATUS_ANTSEL(self)
        self.zz_fdict['ANTSEL'] = self.ANTSEL
        self.TIMSEQINV = RM_Field_MODEM_NS_STATUS_TIMSEQINV(self)
        self.zz_fdict['TIMSEQINV'] = self.TIMSEQINV
        self.TIMLOSTCAUSE = RM_Field_MODEM_NS_STATUS_TIMLOSTCAUSE(self)
        self.zz_fdict['TIMLOSTCAUSE'] = self.TIMLOSTCAUSE
        self.DSADETECTED = RM_Field_MODEM_NS_STATUS_DSADETECTED(self)
        self.zz_fdict['DSADETECTED'] = self.DSADETECTED
        self.DSAFREQESTDONE = RM_Field_MODEM_NS_STATUS_DSAFREQESTDONE(self)
        self.zz_fdict['DSAFREQESTDONE'] = self.DSAFREQESTDONE
        self.VITERBIDEMODTIMDET = RM_Field_MODEM_NS_STATUS_VITERBIDEMODTIMDET(self)
        self.zz_fdict['VITERBIDEMODTIMDET'] = self.VITERBIDEMODTIMDET
        self.VITERBIDEMODFRAMEDET = RM_Field_MODEM_NS_STATUS_VITERBIDEMODFRAMEDET(self)
        self.zz_fdict['VITERBIDEMODFRAMEDET'] = self.VITERBIDEMODFRAMEDET
        self.STAMPSTATE = RM_Field_MODEM_NS_STATUS_STAMPSTATE(self)
        self.zz_fdict['STAMPSTATE'] = self.STAMPSTATE
        self.CORR = RM_Field_MODEM_NS_STATUS_CORR(self)
        self.zz_fdict['CORR'] = self.CORR
        self.WEAKSYMBOLS = RM_Field_MODEM_NS_STATUS_WEAKSYMBOLS(self)
        self.zz_fdict['WEAKSYMBOLS'] = self.WEAKSYMBOLS
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TIMDETSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TIMDETSTATUS, self).__init__(rmio, label,
            0xb8014000, 0x00C,
            'TIMDETSTATUS', 'MODEM_NS.TIMDETSTATUS', 'read-only',
            u"",
            0x00000000, 0x1F0FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMDETCORR = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETCORR(self)
        self.zz_fdict['TIMDETCORR'] = self.TIMDETCORR
        self.TIMDETFREQOFFEST = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETFREQOFFEST(self)
        self.zz_fdict['TIMDETFREQOFFEST'] = self.TIMDETFREQOFFEST
        self.TIMDETPREERRORS = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETPREERRORS(self)
        self.zz_fdict['TIMDETPREERRORS'] = self.TIMDETPREERRORS
        self.TIMDETPASS = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETPASS(self)
        self.zz_fdict['TIMDETPASS'] = self.TIMDETPASS
        self.TIMDETINDEX = RM_Field_MODEM_NS_TIMDETSTATUS_TIMDETINDEX(self)
        self.zz_fdict['TIMDETINDEX'] = self.TIMDETINDEX
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_FREQOFFEST(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_FREQOFFEST, self).__init__(rmio, label,
            0xb8014000, 0x010,
            'FREQOFFEST', 'MODEM_NS.FREQOFFEST', 'read-only',
            u"",
            0x00000000, 0xFFFF1FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FREQOFFEST = RM_Field_MODEM_NS_FREQOFFEST_FREQOFFEST(self)
        self.zz_fdict['FREQOFFEST'] = self.FREQOFFEST
        self.CORRVAL = RM_Field_MODEM_NS_FREQOFFEST_CORRVAL(self)
        self.zz_fdict['CORRVAL'] = self.CORRVAL
        self.SOFTVAL = RM_Field_MODEM_NS_FREQOFFEST_SOFTVAL(self)
        self.zz_fdict['SOFTVAL'] = self.SOFTVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AFCADJRX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AFCADJRX, self).__init__(rmio, label,
            0xb8014000, 0x014,
            'AFCADJRX', 'MODEM_NS.AFCADJRX', 'read-only',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCADJRX = RM_Field_MODEM_NS_AFCADJRX_AFCADJRX(self)
        self.zz_fdict['AFCADJRX'] = self.AFCADJRX
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AFCADJTX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AFCADJTX, self).__init__(rmio, label,
            0xb8014000, 0x018,
            'AFCADJTX', 'MODEM_NS.AFCADJTX', 'read-only',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCADJTX = RM_Field_MODEM_NS_AFCADJTX_AFCADJTX(self)
        self.zz_fdict['AFCADJTX'] = self.AFCADJTX
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_MIXCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_MIXCTRL, self).__init__(rmio, label,
            0xb8014000, 0x01C,
            'MIXCTRL', 'MODEM_NS.MIXCTRL', 'read-write',
            u"",
            0x00000000, 0x0000001F,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANAMIXMODE = RM_Field_MODEM_NS_MIXCTRL_ANAMIXMODE(self)
        self.zz_fdict['ANAMIXMODE'] = self.ANAMIXMODE
        self.DIGIQSWAPEN = RM_Field_MODEM_NS_MIXCTRL_DIGIQSWAPEN(self)
        self.zz_fdict['DIGIQSWAPEN'] = self.DIGIQSWAPEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL0, self).__init__(rmio, label,
            0xb8014000, 0x020,
            'CTRL0', 'MODEM_NS.CTRL0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FDM0DIFFDIS = RM_Field_MODEM_NS_CTRL0_FDM0DIFFDIS(self)
        self.zz_fdict['FDM0DIFFDIS'] = self.FDM0DIFFDIS
        self.MAPFSK = RM_Field_MODEM_NS_CTRL0_MAPFSK(self)
        self.zz_fdict['MAPFSK'] = self.MAPFSK
        self.CODING = RM_Field_MODEM_NS_CTRL0_CODING(self)
        self.zz_fdict['CODING'] = self.CODING
        self.MODFORMAT = RM_Field_MODEM_NS_CTRL0_MODFORMAT(self)
        self.zz_fdict['MODFORMAT'] = self.MODFORMAT
        self.DUALCORROPTDIS = RM_Field_MODEM_NS_CTRL0_DUALCORROPTDIS(self)
        self.zz_fdict['DUALCORROPTDIS'] = self.DUALCORROPTDIS
        self.OOKASYNCPIN = RM_Field_MODEM_NS_CTRL0_OOKASYNCPIN(self)
        self.zz_fdict['OOKASYNCPIN'] = self.OOKASYNCPIN
        self.DSSSLEN = RM_Field_MODEM_NS_CTRL0_DSSSLEN(self)
        self.zz_fdict['DSSSLEN'] = self.DSSSLEN
        self.DSSSSHIFTS = RM_Field_MODEM_NS_CTRL0_DSSSSHIFTS(self)
        self.zz_fdict['DSSSSHIFTS'] = self.DSSSSHIFTS
        self.DSSSDOUBLE = RM_Field_MODEM_NS_CTRL0_DSSSDOUBLE(self)
        self.zz_fdict['DSSSDOUBLE'] = self.DSSSDOUBLE
        self.DETDIS = RM_Field_MODEM_NS_CTRL0_DETDIS(self)
        self.zz_fdict['DETDIS'] = self.DETDIS
        self.DIFFENCMODE = RM_Field_MODEM_NS_CTRL0_DIFFENCMODE(self)
        self.zz_fdict['DIFFENCMODE'] = self.DIFFENCMODE
        self.SHAPING = RM_Field_MODEM_NS_CTRL0_SHAPING(self)
        self.zz_fdict['SHAPING'] = self.SHAPING
        self.DEMODRAWDATASEL = RM_Field_MODEM_NS_CTRL0_DEMODRAWDATASEL(self)
        self.zz_fdict['DEMODRAWDATASEL'] = self.DEMODRAWDATASEL
        self.FRAMEDETDEL = RM_Field_MODEM_NS_CTRL0_FRAMEDETDEL(self)
        self.zz_fdict['FRAMEDETDEL'] = self.FRAMEDETDEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL1, self).__init__(rmio, label,
            0xb8014000, 0x024,
            'CTRL1', 'MODEM_NS.CTRL1', 'read-write',
            u"",
            0x00000000, 0xFFFFDFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNCBITS = RM_Field_MODEM_NS_CTRL1_SYNCBITS(self)
        self.zz_fdict['SYNCBITS'] = self.SYNCBITS
        self.SYNCERRORS = RM_Field_MODEM_NS_CTRL1_SYNCERRORS(self)
        self.zz_fdict['SYNCERRORS'] = self.SYNCERRORS
        self.DUALSYNC = RM_Field_MODEM_NS_CTRL1_DUALSYNC(self)
        self.zz_fdict['DUALSYNC'] = self.DUALSYNC
        self.TXSYNC = RM_Field_MODEM_NS_CTRL1_TXSYNC(self)
        self.zz_fdict['TXSYNC'] = self.TXSYNC
        self.SYNCDATA = RM_Field_MODEM_NS_CTRL1_SYNCDATA(self)
        self.zz_fdict['SYNCDATA'] = self.SYNCDATA
        self.SYNC1INV = RM_Field_MODEM_NS_CTRL1_SYNC1INV(self)
        self.zz_fdict['SYNC1INV'] = self.SYNC1INV
        self.COMPMODE = RM_Field_MODEM_NS_CTRL1_COMPMODE(self)
        self.zz_fdict['COMPMODE'] = self.COMPMODE
        self.RESYNCPER = RM_Field_MODEM_NS_CTRL1_RESYNCPER(self)
        self.zz_fdict['RESYNCPER'] = self.RESYNCPER
        self.PHASEDEMOD = RM_Field_MODEM_NS_CTRL1_PHASEDEMOD(self)
        self.zz_fdict['PHASEDEMOD'] = self.PHASEDEMOD
        self.FREQOFFESTPER = RM_Field_MODEM_NS_CTRL1_FREQOFFESTPER(self)
        self.zz_fdict['FREQOFFESTPER'] = self.FREQOFFESTPER
        self.FREQOFFESTLIM = RM_Field_MODEM_NS_CTRL1_FREQOFFESTLIM(self)
        self.zz_fdict['FREQOFFESTLIM'] = self.FREQOFFESTLIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL2, self).__init__(rmio, label,
            0xb8014000, 0x028,
            'CTRL2', 'MODEM_NS.CTRL2', 'read-write',
            u"",
            0x00001000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SQITHRESH = RM_Field_MODEM_NS_CTRL2_SQITHRESH(self)
        self.zz_fdict['SQITHRESH'] = self.SQITHRESH
        self.RXFRCDIS = RM_Field_MODEM_NS_CTRL2_RXFRCDIS(self)
        self.zz_fdict['RXFRCDIS'] = self.RXFRCDIS
        self.RXPINMODE = RM_Field_MODEM_NS_CTRL2_RXPINMODE(self)
        self.zz_fdict['RXPINMODE'] = self.RXPINMODE
        self.TXPINMODE = RM_Field_MODEM_NS_CTRL2_TXPINMODE(self)
        self.zz_fdict['TXPINMODE'] = self.TXPINMODE
        self.DATAFILTER = RM_Field_MODEM_NS_CTRL2_DATAFILTER(self)
        self.zz_fdict['DATAFILTER'] = self.DATAFILTER
        self.BRDIVA = RM_Field_MODEM_NS_CTRL2_BRDIVA(self)
        self.zz_fdict['BRDIVA'] = self.BRDIVA
        self.BRDIVB = RM_Field_MODEM_NS_CTRL2_BRDIVB(self)
        self.zz_fdict['BRDIVB'] = self.BRDIVB
        self.DEVMULA = RM_Field_MODEM_NS_CTRL2_DEVMULA(self)
        self.zz_fdict['DEVMULA'] = self.DEVMULA
        self.DEVMULB = RM_Field_MODEM_NS_CTRL2_DEVMULB(self)
        self.zz_fdict['DEVMULB'] = self.DEVMULB
        self.RATESELMODE = RM_Field_MODEM_NS_CTRL2_RATESELMODE(self)
        self.zz_fdict['RATESELMODE'] = self.RATESELMODE
        self.DEVWEIGHTDIS = RM_Field_MODEM_NS_CTRL2_DEVWEIGHTDIS(self)
        self.zz_fdict['DEVWEIGHTDIS'] = self.DEVWEIGHTDIS
        self.DMASEL = RM_Field_MODEM_NS_CTRL2_DMASEL(self)
        self.zz_fdict['DMASEL'] = self.DMASEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL3, self).__init__(rmio, label,
            0xb8014000, 0x02C,
            'CTRL3', 'MODEM_NS.CTRL3', 'read-write',
            u"",
            0x00008000, 0xFFFFFF81,
            0x00001000, 0x00002000,
            0x00003000)

        self.PRSDINEN = RM_Field_MODEM_NS_CTRL3_PRSDINEN(self)
        self.zz_fdict['PRSDINEN'] = self.PRSDINEN
        self.RAMTESTEN = RM_Field_MODEM_NS_CTRL3_RAMTESTEN(self)
        self.zz_fdict['RAMTESTEN'] = self.RAMTESTEN
        self.ANTDIVMODE = RM_Field_MODEM_NS_CTRL3_ANTDIVMODE(self)
        self.zz_fdict['ANTDIVMODE'] = self.ANTDIVMODE
        self.ANTDIVREPEATDIS = RM_Field_MODEM_NS_CTRL3_ANTDIVREPEATDIS(self)
        self.zz_fdict['ANTDIVREPEATDIS'] = self.ANTDIVREPEATDIS
        self.TSAMPMODE = RM_Field_MODEM_NS_CTRL3_TSAMPMODE(self)
        self.zz_fdict['TSAMPMODE'] = self.TSAMPMODE
        self.TSAMPDEL = RM_Field_MODEM_NS_CTRL3_TSAMPDEL(self)
        self.zz_fdict['TSAMPDEL'] = self.TSAMPDEL
        self.TSAMPLIM = RM_Field_MODEM_NS_CTRL3_TSAMPLIM(self)
        self.zz_fdict['TSAMPLIM'] = self.TSAMPLIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL4, self).__init__(rmio, label,
            0xb8014000, 0x030,
            'CTRL4', 'MODEM_NS.CTRL4', 'read-write',
            u"",
            0x03000000, 0xBFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ISICOMP = RM_Field_MODEM_NS_CTRL4_ISICOMP(self)
        self.zz_fdict['ISICOMP'] = self.ISICOMP
        self.DEVOFFCOMP = RM_Field_MODEM_NS_CTRL4_DEVOFFCOMP(self)
        self.zz_fdict['DEVOFFCOMP'] = self.DEVOFFCOMP
        self.PREDISTGAIN = RM_Field_MODEM_NS_CTRL4_PREDISTGAIN(self)
        self.zz_fdict['PREDISTGAIN'] = self.PREDISTGAIN
        self.PREDISTDEB = RM_Field_MODEM_NS_CTRL4_PREDISTDEB(self)
        self.zz_fdict['PREDISTDEB'] = self.PREDISTDEB
        self.PREDISTAVG = RM_Field_MODEM_NS_CTRL4_PREDISTAVG(self)
        self.zz_fdict['PREDISTAVG'] = self.PREDISTAVG
        self.PREDISTRST = RM_Field_MODEM_NS_CTRL4_PREDISTRST(self)
        self.zz_fdict['PREDISTRST'] = self.PREDISTRST
        self.PHASECLICKFILT = RM_Field_MODEM_NS_CTRL4_PHASECLICKFILT(self)
        self.zz_fdict['PHASECLICKFILT'] = self.PHASECLICKFILT
        self.SOFTDSSSMODE = RM_Field_MODEM_NS_CTRL4_SOFTDSSSMODE(self)
        self.zz_fdict['SOFTDSSSMODE'] = self.SOFTDSSSMODE
        self.ADCSATLEVEL = RM_Field_MODEM_NS_CTRL4_ADCSATLEVEL(self)
        self.zz_fdict['ADCSATLEVEL'] = self.ADCSATLEVEL
        self.ADCSATDENS = RM_Field_MODEM_NS_CTRL4_ADCSATDENS(self)
        self.zz_fdict['ADCSATDENS'] = self.ADCSATDENS
        self.OFFSETPHASEMASKING = RM_Field_MODEM_NS_CTRL4_OFFSETPHASEMASKING(self)
        self.zz_fdict['OFFSETPHASEMASKING'] = self.OFFSETPHASEMASKING
        self.OFFSETPHASESCALING = RM_Field_MODEM_NS_CTRL4_OFFSETPHASESCALING(self)
        self.zz_fdict['OFFSETPHASESCALING'] = self.OFFSETPHASESCALING
        self.CLKUNDIVREQ = RM_Field_MODEM_NS_CTRL4_CLKUNDIVREQ(self)
        self.zz_fdict['CLKUNDIVREQ'] = self.CLKUNDIVREQ
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL5, self).__init__(rmio, label,
            0xb8014000, 0x034,
            'CTRL5', 'MODEM_NS.CTRL5', 'read-write',
            u"",
            0x00000000, 0x607007FE,
            0x00001000, 0x00002000,
            0x00003000)

        self.BRCALEN = RM_Field_MODEM_NS_CTRL5_BRCALEN(self)
        self.zz_fdict['BRCALEN'] = self.BRCALEN
        self.BRCALMODE = RM_Field_MODEM_NS_CTRL5_BRCALMODE(self)
        self.zz_fdict['BRCALMODE'] = self.BRCALMODE
        self.BRCALAVG = RM_Field_MODEM_NS_CTRL5_BRCALAVG(self)
        self.zz_fdict['BRCALAVG'] = self.BRCALAVG
        self.DETDEL = RM_Field_MODEM_NS_CTRL5_DETDEL(self)
        self.zz_fdict['DETDEL'] = self.DETDEL
        self.TDEDGE = RM_Field_MODEM_NS_CTRL5_TDEDGE(self)
        self.zz_fdict['TDEDGE'] = self.TDEDGE
        self.TREDGE = RM_Field_MODEM_NS_CTRL5_TREDGE(self)
        self.zz_fdict['TREDGE'] = self.TREDGE
        self.DEMODRAWDATASEL2 = RM_Field_MODEM_NS_CTRL5_DEMODRAWDATASEL2(self)
        self.zz_fdict['DEMODRAWDATASEL2'] = self.DEMODRAWDATASEL2
        self.RESYNCBAUDTRANS = RM_Field_MODEM_NS_CTRL5_RESYNCBAUDTRANS(self)
        self.zz_fdict['RESYNCBAUDTRANS'] = self.RESYNCBAUDTRANS
        self.RESYNCLIMIT = RM_Field_MODEM_NS_CTRL5_RESYNCLIMIT(self)
        self.zz_fdict['RESYNCLIMIT'] = self.RESYNCLIMIT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CTRL6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CTRL6, self).__init__(rmio, label,
            0xb8014000, 0x038,
            'CTRL6', 'MODEM_NS.CTRL6', 'read-write',
            u"",
            0x00000000, 0xF6000000,
            0x00001000, 0x00002000,
            0x00003000)

        self.CODINGB = RM_Field_MODEM_NS_CTRL6_CODINGB(self)
        self.zz_fdict['CODINGB'] = self.CODINGB
        self.RXRESTARTUPONRSSI = RM_Field_MODEM_NS_CTRL6_RXRESTARTUPONRSSI(self)
        self.zz_fdict['RXRESTARTUPONRSSI'] = self.RXRESTARTUPONRSSI
        self.RXRESTARTUPONSHORTRSSI = RM_Field_MODEM_NS_CTRL6_RXRESTARTUPONSHORTRSSI(self)
        self.zz_fdict['RXRESTARTUPONSHORTRSSI'] = self.RXRESTARTUPONSHORTRSSI
        self.RXBRCALCDIS = RM_Field_MODEM_NS_CTRL6_RXBRCALCDIS(self)
        self.zz_fdict['RXBRCALCDIS'] = self.RXBRCALCDIS
        self.DEMODRESTARTALL = RM_Field_MODEM_NS_CTRL6_DEMODRESTARTALL(self)
        self.zz_fdict['DEMODRESTARTALL'] = self.DEMODRESTARTALL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TXBR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TXBR, self).__init__(rmio, label,
            0xb8014000, 0x058,
            'TXBR', 'MODEM_NS.TXBR', 'read-write',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXBRNUM = RM_Field_MODEM_NS_TXBR_TXBRNUM(self)
        self.zz_fdict['TXBRNUM'] = self.TXBRNUM
        self.TXBRDEN = RM_Field_MODEM_NS_TXBR_TXBRDEN(self)
        self.zz_fdict['TXBRDEN'] = self.TXBRDEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_RXBR(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_RXBR, self).__init__(rmio, label,
            0xb8014000, 0x05C,
            'RXBR', 'MODEM_NS.RXBR', 'read-write',
            u"",
            0x00000000, 0x00001FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RXBRNUM = RM_Field_MODEM_NS_RXBR_RXBRNUM(self)
        self.zz_fdict['RXBRNUM'] = self.RXBRNUM
        self.RXBRDEN = RM_Field_MODEM_NS_RXBR_RXBRDEN(self)
        self.zz_fdict['RXBRDEN'] = self.RXBRDEN
        self.RXBRINT = RM_Field_MODEM_NS_RXBR_RXBRINT(self)
        self.zz_fdict['RXBRINT'] = self.RXBRINT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CF, self).__init__(rmio, label,
            0xb8014000, 0x060,
            'CF', 'MODEM_NS.CF', 'read-write',
            u"",
            0x00000000, 0xCFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DEC0 = RM_Field_MODEM_NS_CF_DEC0(self)
        self.zz_fdict['DEC0'] = self.DEC0
        self.DEC1 = RM_Field_MODEM_NS_CF_DEC1(self)
        self.zz_fdict['DEC1'] = self.DEC1
        self.DEC2 = RM_Field_MODEM_NS_CF_DEC2(self)
        self.zz_fdict['DEC2'] = self.DEC2
        self.CFOSR = RM_Field_MODEM_NS_CF_CFOSR(self)
        self.zz_fdict['CFOSR'] = self.CFOSR
        self.DEC1GAIN = RM_Field_MODEM_NS_CF_DEC1GAIN(self)
        self.zz_fdict['DEC1GAIN'] = self.DEC1GAIN
        self.ADCBITORDERI = RM_Field_MODEM_NS_CF_ADCBITORDERI(self)
        self.zz_fdict['ADCBITORDERI'] = self.ADCBITORDERI
        self.ADCBITORDERQ = RM_Field_MODEM_NS_CF_ADCBITORDERQ(self)
        self.zz_fdict['ADCBITORDERQ'] = self.ADCBITORDERQ
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PRE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PRE, self).__init__(rmio, label,
            0xb8014000, 0x064,
            'PRE', 'MODEM_NS.PRE', 'read-write',
            u"",
            0x00000000, 0xFFFF1FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BASE = RM_Field_MODEM_NS_PRE_BASE(self)
        self.zz_fdict['BASE'] = self.BASE
        self.BASEBITS = RM_Field_MODEM_NS_PRE_BASEBITS(self)
        self.zz_fdict['BASEBITS'] = self.BASEBITS
        self.PRESYMB4FSK = RM_Field_MODEM_NS_PRE_PRESYMB4FSK(self)
        self.zz_fdict['PRESYMB4FSK'] = self.PRESYMB4FSK
        self.PREERRORS = RM_Field_MODEM_NS_PRE_PREERRORS(self)
        self.zz_fdict['PREERRORS'] = self.PREERRORS
        self.DSSSPRE = RM_Field_MODEM_NS_PRE_DSSSPRE(self)
        self.zz_fdict['DSSSPRE'] = self.DSSSPRE
        self.SYNCSYMB4FSK = RM_Field_MODEM_NS_PRE_SYNCSYMB4FSK(self)
        self.zz_fdict['SYNCSYMB4FSK'] = self.SYNCSYMB4FSK
        self.TXBASES = RM_Field_MODEM_NS_PRE_TXBASES(self)
        self.zz_fdict['TXBASES'] = self.TXBASES
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYNC0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYNC0, self).__init__(rmio, label,
            0xb8014000, 0x068,
            'SYNC0', 'MODEM_NS.SYNC0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNC0 = RM_Field_MODEM_NS_SYNC0_SYNC0(self)
        self.zz_fdict['SYNC0'] = self.SYNC0
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYNC1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYNC1, self).__init__(rmio, label,
            0xb8014000, 0x06C,
            'SYNC1', 'MODEM_NS.SYNC1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNC1 = RM_Field_MODEM_NS_SYNC1_SYNC1(self)
        self.zz_fdict['SYNC1'] = self.SYNC1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TIMING(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TIMING, self).__init__(rmio, label,
            0xb8014000, 0x080,
            'TIMING', 'MODEM_NS.TIMING', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMTHRESH = RM_Field_MODEM_NS_TIMING_TIMTHRESH(self)
        self.zz_fdict['TIMTHRESH'] = self.TIMTHRESH
        self.TIMINGBASES = RM_Field_MODEM_NS_TIMING_TIMINGBASES(self)
        self.zz_fdict['TIMINGBASES'] = self.TIMINGBASES
        self.ADDTIMSEQ = RM_Field_MODEM_NS_TIMING_ADDTIMSEQ(self)
        self.zz_fdict['ADDTIMSEQ'] = self.ADDTIMSEQ
        self.TIMSEQINVEN = RM_Field_MODEM_NS_TIMING_TIMSEQINVEN(self)
        self.zz_fdict['TIMSEQINVEN'] = self.TIMSEQINVEN
        self.TIMSEQSYNC = RM_Field_MODEM_NS_TIMING_TIMSEQSYNC(self)
        self.zz_fdict['TIMSEQSYNC'] = self.TIMSEQSYNC
        self.FDM0THRESH = RM_Field_MODEM_NS_TIMING_FDM0THRESH(self)
        self.zz_fdict['FDM0THRESH'] = self.FDM0THRESH
        self.OFFSUBNUM = RM_Field_MODEM_NS_TIMING_OFFSUBNUM(self)
        self.zz_fdict['OFFSUBNUM'] = self.OFFSUBNUM
        self.OFFSUBDEN = RM_Field_MODEM_NS_TIMING_OFFSUBDEN(self)
        self.zz_fdict['OFFSUBDEN'] = self.OFFSUBDEN
        self.TSAGCDEL = RM_Field_MODEM_NS_TIMING_TSAGCDEL(self)
        self.zz_fdict['TSAGCDEL'] = self.TSAGCDEL
        self.FASTRESYNC = RM_Field_MODEM_NS_TIMING_FASTRESYNC(self)
        self.zz_fdict['FASTRESYNC'] = self.FASTRESYNC
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSSS0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSSS0, self).__init__(rmio, label,
            0xb8014000, 0x084,
            'DSSS0', 'MODEM_NS.DSSS0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DSSS0 = RM_Field_MODEM_NS_DSSS0_DSSS0(self)
        self.zz_fdict['DSSS0'] = self.DSSS0
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_MODINDEX(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_MODINDEX, self).__init__(rmio, label,
            0xb8014000, 0x088,
            'MODINDEX', 'MODEM_NS.MODINDEX', 'read-write',
            u"",
            0x00000000, 0x003F03FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MODINDEXM = RM_Field_MODEM_NS_MODINDEX_MODINDEXM(self)
        self.zz_fdict['MODINDEXM'] = self.MODINDEXM
        self.MODINDEXE = RM_Field_MODEM_NS_MODINDEX_MODINDEXE(self)
        self.zz_fdict['MODINDEXE'] = self.MODINDEXE
        self.FREQGAINE = RM_Field_MODEM_NS_MODINDEX_FREQGAINE(self)
        self.zz_fdict['FREQGAINE'] = self.FREQGAINE
        self.FREQGAINM = RM_Field_MODEM_NS_MODINDEX_FREQGAINM(self)
        self.zz_fdict['FREQGAINM'] = self.FREQGAINM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AFC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AFC, self).__init__(rmio, label,
            0xb8014000, 0x08C,
            'AFC', 'MODEM_NS.AFC', 'read-write',
            u"",
            0x00000000, 0x1FFFFDFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCSCALEM = RM_Field_MODEM_NS_AFC_AFCSCALEM(self)
        self.zz_fdict['AFCSCALEM'] = self.AFCSCALEM
        self.AFCSCALEE = RM_Field_MODEM_NS_AFC_AFCSCALEE(self)
        self.zz_fdict['AFCSCALEE'] = self.AFCSCALEE
        self.AFCRXMODE = RM_Field_MODEM_NS_AFC_AFCRXMODE(self)
        self.zz_fdict['AFCRXMODE'] = self.AFCRXMODE
        self.AFCTXMODE = RM_Field_MODEM_NS_AFC_AFCTXMODE(self)
        self.zz_fdict['AFCTXMODE'] = self.AFCTXMODE
        self.AFCRXCLR = RM_Field_MODEM_NS_AFC_AFCRXCLR(self)
        self.zz_fdict['AFCRXCLR'] = self.AFCRXCLR
        self.AFCDEL = RM_Field_MODEM_NS_AFC_AFCDEL(self)
        self.zz_fdict['AFCDEL'] = self.AFCDEL
        self.AFCAVGPER = RM_Field_MODEM_NS_AFC_AFCAVGPER(self)
        self.zz_fdict['AFCAVGPER'] = self.AFCAVGPER
        self.AFCLIMRESET = RM_Field_MODEM_NS_AFC_AFCLIMRESET(self)
        self.zz_fdict['AFCLIMRESET'] = self.AFCLIMRESET
        self.AFCONESHOT = RM_Field_MODEM_NS_AFC_AFCONESHOT(self)
        self.zz_fdict['AFCONESHOT'] = self.AFCONESHOT
        self.AFCENINTCOMP = RM_Field_MODEM_NS_AFC_AFCENINTCOMP(self)
        self.zz_fdict['AFCENINTCOMP'] = self.AFCENINTCOMP
        self.AFCDSAFREQOFFEST = RM_Field_MODEM_NS_AFC_AFCDSAFREQOFFEST(self)
        self.zz_fdict['AFCDSAFREQOFFEST'] = self.AFCDSAFREQOFFEST
        self.AFCDELDET = RM_Field_MODEM_NS_AFC_AFCDELDET(self)
        self.zz_fdict['AFCDELDET'] = self.AFCDELDET
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AFCADJLIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AFCADJLIM, self).__init__(rmio, label,
            0xb8014000, 0x090,
            'AFCADJLIM', 'MODEM_NS.AFCADJLIM', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AFCADJLIM = RM_Field_MODEM_NS_AFCADJLIM_AFCADJLIM(self)
        self.zz_fdict['AFCADJLIM'] = self.AFCADJLIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING0, self).__init__(rmio, label,
            0xb8014000, 0x094,
            'SHAPING0', 'MODEM_NS.SHAPING0', 'read-write',
            u"",
            0x22130A04, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF0 = RM_Field_MODEM_NS_SHAPING0_COEFF0(self)
        self.zz_fdict['COEFF0'] = self.COEFF0
        self.COEFF1 = RM_Field_MODEM_NS_SHAPING0_COEFF1(self)
        self.zz_fdict['COEFF1'] = self.COEFF1
        self.COEFF2 = RM_Field_MODEM_NS_SHAPING0_COEFF2(self)
        self.zz_fdict['COEFF2'] = self.COEFF2
        self.COEFF3 = RM_Field_MODEM_NS_SHAPING0_COEFF3(self)
        self.zz_fdict['COEFF3'] = self.COEFF3
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING1, self).__init__(rmio, label,
            0xb8014000, 0x098,
            'SHAPING1', 'MODEM_NS.SHAPING1', 'read-write',
            u"",
            0x4F4A4132, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF4 = RM_Field_MODEM_NS_SHAPING1_COEFF4(self)
        self.zz_fdict['COEFF4'] = self.COEFF4
        self.COEFF5 = RM_Field_MODEM_NS_SHAPING1_COEFF5(self)
        self.zz_fdict['COEFF5'] = self.COEFF5
        self.COEFF6 = RM_Field_MODEM_NS_SHAPING1_COEFF6(self)
        self.zz_fdict['COEFF6'] = self.COEFF6
        self.COEFF7 = RM_Field_MODEM_NS_SHAPING1_COEFF7(self)
        self.zz_fdict['COEFF7'] = self.COEFF7
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING2, self).__init__(rmio, label,
            0xb8014000, 0x09C,
            'SHAPING2', 'MODEM_NS.SHAPING2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF8 = RM_Field_MODEM_NS_SHAPING2_COEFF8(self)
        self.zz_fdict['COEFF8'] = self.COEFF8
        self.COEFF9 = RM_Field_MODEM_NS_SHAPING2_COEFF9(self)
        self.zz_fdict['COEFF9'] = self.COEFF9
        self.COEFF10 = RM_Field_MODEM_NS_SHAPING2_COEFF10(self)
        self.zz_fdict['COEFF10'] = self.COEFF10
        self.COEFF11 = RM_Field_MODEM_NS_SHAPING2_COEFF11(self)
        self.zz_fdict['COEFF11'] = self.COEFF11
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING3, self).__init__(rmio, label,
            0xb8014000, 0x0A0,
            'SHAPING3', 'MODEM_NS.SHAPING3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF12 = RM_Field_MODEM_NS_SHAPING3_COEFF12(self)
        self.zz_fdict['COEFF12'] = self.COEFF12
        self.COEFF13 = RM_Field_MODEM_NS_SHAPING3_COEFF13(self)
        self.zz_fdict['COEFF13'] = self.COEFF13
        self.COEFF14 = RM_Field_MODEM_NS_SHAPING3_COEFF14(self)
        self.zz_fdict['COEFF14'] = self.COEFF14
        self.COEFF15 = RM_Field_MODEM_NS_SHAPING3_COEFF15(self)
        self.zz_fdict['COEFF15'] = self.COEFF15
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING4, self).__init__(rmio, label,
            0xb8014000, 0x0A4,
            'SHAPING4', 'MODEM_NS.SHAPING4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF16 = RM_Field_MODEM_NS_SHAPING4_COEFF16(self)
        self.zz_fdict['COEFF16'] = self.COEFF16
        self.COEFF17 = RM_Field_MODEM_NS_SHAPING4_COEFF17(self)
        self.zz_fdict['COEFF17'] = self.COEFF17
        self.COEFF18 = RM_Field_MODEM_NS_SHAPING4_COEFF18(self)
        self.zz_fdict['COEFF18'] = self.COEFF18
        self.COEFF19 = RM_Field_MODEM_NS_SHAPING4_COEFF19(self)
        self.zz_fdict['COEFF19'] = self.COEFF19
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING5, self).__init__(rmio, label,
            0xb8014000, 0x0A8,
            'SHAPING5', 'MODEM_NS.SHAPING5', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF20 = RM_Field_MODEM_NS_SHAPING5_COEFF20(self)
        self.zz_fdict['COEFF20'] = self.COEFF20
        self.COEFF21 = RM_Field_MODEM_NS_SHAPING5_COEFF21(self)
        self.zz_fdict['COEFF21'] = self.COEFF21
        self.COEFF22 = RM_Field_MODEM_NS_SHAPING5_COEFF22(self)
        self.zz_fdict['COEFF22'] = self.COEFF22
        self.COEFF23 = RM_Field_MODEM_NS_SHAPING5_COEFF23(self)
        self.zz_fdict['COEFF23'] = self.COEFF23
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING6, self).__init__(rmio, label,
            0xb8014000, 0x0AC,
            'SHAPING6', 'MODEM_NS.SHAPING6', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF24 = RM_Field_MODEM_NS_SHAPING6_COEFF24(self)
        self.zz_fdict['COEFF24'] = self.COEFF24
        self.COEFF25 = RM_Field_MODEM_NS_SHAPING6_COEFF25(self)
        self.zz_fdict['COEFF25'] = self.COEFF25
        self.COEFF26 = RM_Field_MODEM_NS_SHAPING6_COEFF26(self)
        self.zz_fdict['COEFF26'] = self.COEFF26
        self.COEFF27 = RM_Field_MODEM_NS_SHAPING6_COEFF27(self)
        self.zz_fdict['COEFF27'] = self.COEFF27
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING7(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING7, self).__init__(rmio, label,
            0xb8014000, 0x0B0,
            'SHAPING7', 'MODEM_NS.SHAPING7', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF28 = RM_Field_MODEM_NS_SHAPING7_COEFF28(self)
        self.zz_fdict['COEFF28'] = self.COEFF28
        self.COEFF29 = RM_Field_MODEM_NS_SHAPING7_COEFF29(self)
        self.zz_fdict['COEFF29'] = self.COEFF29
        self.COEFF30 = RM_Field_MODEM_NS_SHAPING7_COEFF30(self)
        self.zz_fdict['COEFF30'] = self.COEFF30
        self.COEFF31 = RM_Field_MODEM_NS_SHAPING7_COEFF31(self)
        self.zz_fdict['COEFF31'] = self.COEFF31
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING8(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING8, self).__init__(rmio, label,
            0xb8014000, 0x0B4,
            'SHAPING8', 'MODEM_NS.SHAPING8', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF32 = RM_Field_MODEM_NS_SHAPING8_COEFF32(self)
        self.zz_fdict['COEFF32'] = self.COEFF32
        self.COEFF33 = RM_Field_MODEM_NS_SHAPING8_COEFF33(self)
        self.zz_fdict['COEFF33'] = self.COEFF33
        self.COEFF34 = RM_Field_MODEM_NS_SHAPING8_COEFF34(self)
        self.zz_fdict['COEFF34'] = self.COEFF34
        self.COEFF35 = RM_Field_MODEM_NS_SHAPING8_COEFF35(self)
        self.zz_fdict['COEFF35'] = self.COEFF35
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING9(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING9, self).__init__(rmio, label,
            0xb8014000, 0x0B8,
            'SHAPING9', 'MODEM_NS.SHAPING9', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF36 = RM_Field_MODEM_NS_SHAPING9_COEFF36(self)
        self.zz_fdict['COEFF36'] = self.COEFF36
        self.COEFF37 = RM_Field_MODEM_NS_SHAPING9_COEFF37(self)
        self.zz_fdict['COEFF37'] = self.COEFF37
        self.COEFF38 = RM_Field_MODEM_NS_SHAPING9_COEFF38(self)
        self.zz_fdict['COEFF38'] = self.COEFF38
        self.COEFF39 = RM_Field_MODEM_NS_SHAPING9_COEFF39(self)
        self.zz_fdict['COEFF39'] = self.COEFF39
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING10(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING10, self).__init__(rmio, label,
            0xb8014000, 0x0BC,
            'SHAPING10', 'MODEM_NS.SHAPING10', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF40 = RM_Field_MODEM_NS_SHAPING10_COEFF40(self)
        self.zz_fdict['COEFF40'] = self.COEFF40
        self.COEFF41 = RM_Field_MODEM_NS_SHAPING10_COEFF41(self)
        self.zz_fdict['COEFF41'] = self.COEFF41
        self.COEFF42 = RM_Field_MODEM_NS_SHAPING10_COEFF42(self)
        self.zz_fdict['COEFF42'] = self.COEFF42
        self.COEFF43 = RM_Field_MODEM_NS_SHAPING10_COEFF43(self)
        self.zz_fdict['COEFF43'] = self.COEFF43
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SHAPING11(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SHAPING11, self).__init__(rmio, label,
            0xb8014000, 0x0C0,
            'SHAPING11', 'MODEM_NS.SHAPING11', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.COEFF44 = RM_Field_MODEM_NS_SHAPING11_COEFF44(self)
        self.zz_fdict['COEFF44'] = self.COEFF44
        self.COEFF45 = RM_Field_MODEM_NS_SHAPING11_COEFF45(self)
        self.zz_fdict['COEFF45'] = self.COEFF45
        self.COEFF46 = RM_Field_MODEM_NS_SHAPING11_COEFF46(self)
        self.zz_fdict['COEFF46'] = self.COEFF46
        self.COEFF47 = RM_Field_MODEM_NS_SHAPING11_COEFF47(self)
        self.zz_fdict['COEFF47'] = self.COEFF47
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_RAMPCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_RAMPCTRL, self).__init__(rmio, label,
            0xb8014000, 0x0C4,
            'RAMPCTRL', 'MODEM_NS.RAMPCTRL', 'read-write',
            u"",
            0x00000555, 0xFF800FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RAMPRATE0 = RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE0(self)
        self.zz_fdict['RAMPRATE0'] = self.RAMPRATE0
        self.RAMPRATE1 = RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE1(self)
        self.zz_fdict['RAMPRATE1'] = self.RAMPRATE1
        self.RAMPRATE2 = RM_Field_MODEM_NS_RAMPCTRL_RAMPRATE2(self)
        self.zz_fdict['RAMPRATE2'] = self.RAMPRATE2
        self.RAMPDIS = RM_Field_MODEM_NS_RAMPCTRL_RAMPDIS(self)
        self.zz_fdict['RAMPDIS'] = self.RAMPDIS
        self.RAMPVAL = RM_Field_MODEM_NS_RAMPCTRL_RAMPVAL(self)
        self.zz_fdict['RAMPVAL'] = self.RAMPVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_RAMPLEV(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_RAMPLEV, self).__init__(rmio, label,
            0xb8014000, 0x0CC,
            'RAMPLEV', 'MODEM_NS.RAMPLEV', 'read-write',
            u"",
            0x009F9F9F, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.RAMPLEV0 = RM_Field_MODEM_NS_RAMPLEV_RAMPLEV0(self)
        self.zz_fdict['RAMPLEV0'] = self.RAMPLEV0
        self.RAMPLEV1 = RM_Field_MODEM_NS_RAMPLEV_RAMPLEV1(self)
        self.zz_fdict['RAMPLEV1'] = self.RAMPLEV1
        self.RAMPLEV2 = RM_Field_MODEM_NS_RAMPLEV_RAMPLEV2(self)
        self.zz_fdict['RAMPLEV2'] = self.RAMPLEV2
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DCCOMP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DCCOMP, self).__init__(rmio, label,
            0xb8014000, 0x0E0,
            'DCCOMP', 'MODEM_NS.DCCOMP', 'read-write',
            u"",
            0x00000030, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCESTIEN = RM_Field_MODEM_NS_DCCOMP_DCESTIEN(self)
        self.zz_fdict['DCESTIEN'] = self.DCESTIEN
        self.DCCOMPEN = RM_Field_MODEM_NS_DCCOMP_DCCOMPEN(self)
        self.zz_fdict['DCCOMPEN'] = self.DCCOMPEN
        self.DCRSTEN = RM_Field_MODEM_NS_DCCOMP_DCRSTEN(self)
        self.zz_fdict['DCRSTEN'] = self.DCRSTEN
        self.DCCOMPFREEZE = RM_Field_MODEM_NS_DCCOMP_DCCOMPFREEZE(self)
        self.zz_fdict['DCCOMPFREEZE'] = self.DCCOMPFREEZE
        self.DCCOMPGEAR = RM_Field_MODEM_NS_DCCOMP_DCCOMPGEAR(self)
        self.zz_fdict['DCCOMPGEAR'] = self.DCCOMPGEAR
        self.DCLIMIT = RM_Field_MODEM_NS_DCCOMP_DCLIMIT(self)
        self.zz_fdict['DCLIMIT'] = self.DCLIMIT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DCCOMPFILTINIT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DCCOMPFILTINIT, self).__init__(rmio, label,
            0xb8014000, 0x0E4,
            'DCCOMPFILTINIT', 'MODEM_NS.DCCOMPFILTINIT', 'read-write',
            u"",
            0x00000000, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCCOMPINITVALI = RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINITVALI(self)
        self.zz_fdict['DCCOMPINITVALI'] = self.DCCOMPINITVALI
        self.DCCOMPINITVALQ = RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINITVALQ(self)
        self.zz_fdict['DCCOMPINITVALQ'] = self.DCCOMPINITVALQ
        self.DCCOMPINIT = RM_Field_MODEM_NS_DCCOMPFILTINIT_DCCOMPINIT(self)
        self.zz_fdict['DCCOMPINIT'] = self.DCCOMPINIT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DCESTI(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DCESTI, self).__init__(rmio, label,
            0xb8014000, 0x0E8,
            'DCESTI', 'MODEM_NS.DCESTI', 'read-only',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DCCOMPESTIVALI = RM_Field_MODEM_NS_DCESTI_DCCOMPESTIVALI(self)
        self.zz_fdict['DCCOMPESTIVALI'] = self.DCCOMPESTIVALI
        self.DCCOMPESTIVALQ = RM_Field_MODEM_NS_DCESTI_DCCOMPESTIVALQ(self)
        self.zz_fdict['DCCOMPESTIVALQ'] = self.DCCOMPESTIVALQ
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SRCCHF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SRCCHF, self).__init__(rmio, label,
            0xb8014000, 0x0EC,
            'SRCCHF', 'MODEM_NS.SRCCHF', 'read-write',
            u"",
            0x00000000, 0xEFFFF8FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SRCRATIO1 = RM_Field_MODEM_NS_SRCCHF_SRCRATIO1(self)
        self.zz_fdict['SRCRATIO1'] = self.SRCRATIO1
        self.SRCENABLE1 = RM_Field_MODEM_NS_SRCCHF_SRCENABLE1(self)
        self.zz_fdict['SRCENABLE1'] = self.SRCENABLE1
        self.SRCRATIO2 = RM_Field_MODEM_NS_SRCCHF_SRCRATIO2(self)
        self.zz_fdict['SRCRATIO2'] = self.SRCRATIO2
        self.SRCENABLE2 = RM_Field_MODEM_NS_SRCCHF_SRCENABLE2(self)
        self.zz_fdict['SRCENABLE2'] = self.SRCENABLE2
        self.BWSEL = RM_Field_MODEM_NS_SRCCHF_BWSEL(self)
        self.zz_fdict['BWSEL'] = self.BWSEL
        self.INTOSR = RM_Field_MODEM_NS_SRCCHF_INTOSR(self)
        self.zz_fdict['INTOSR'] = self.INTOSR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD0, self).__init__(rmio, label,
            0xb8014000, 0x0F4,
            'DSATHD0', 'MODEM_NS.DSATHD0', 'read-write',
            u"",
            0x07830464, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SPIKETHD = RM_Field_MODEM_NS_DSATHD0_SPIKETHD(self)
        self.zz_fdict['SPIKETHD'] = self.SPIKETHD
        self.UNMODTHD = RM_Field_MODEM_NS_DSATHD0_UNMODTHD(self)
        self.zz_fdict['UNMODTHD'] = self.UNMODTHD
        self.FDEVMINTHD = RM_Field_MODEM_NS_DSATHD0_FDEVMINTHD(self)
        self.zz_fdict['FDEVMINTHD'] = self.FDEVMINTHD
        self.FDEVMAXTHD = RM_Field_MODEM_NS_DSATHD0_FDEVMAXTHD(self)
        self.zz_fdict['FDEVMAXTHD'] = self.FDEVMAXTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD1, self).__init__(rmio, label,
            0xb8014000, 0x0F8,
            'DSATHD1', 'MODEM_NS.DSATHD1', 'read-write',
            u"",
            0x3AC81388, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POWABSTHD = RM_Field_MODEM_NS_DSATHD1_POWABSTHD(self)
        self.zz_fdict['POWABSTHD'] = self.POWABSTHD
        self.POWRELTHD = RM_Field_MODEM_NS_DSATHD1_POWRELTHD(self)
        self.zz_fdict['POWRELTHD'] = self.POWRELTHD
        self.DSARSTCNT = RM_Field_MODEM_NS_DSATHD1_DSARSTCNT(self)
        self.zz_fdict['DSARSTCNT'] = self.DSARSTCNT
        self.RSSIJMPTHD = RM_Field_MODEM_NS_DSATHD1_RSSIJMPTHD(self)
        self.zz_fdict['RSSIJMPTHD'] = self.RSSIJMPTHD
        self.FREQLATDLY = RM_Field_MODEM_NS_DSATHD1_FREQLATDLY(self)
        self.zz_fdict['FREQLATDLY'] = self.FREQLATDLY
        self.PWRFLTBYP = RM_Field_MODEM_NS_DSATHD1_PWRFLTBYP(self)
        self.zz_fdict['PWRFLTBYP'] = self.PWRFLTBYP
        self.AMPFLTBYP = RM_Field_MODEM_NS_DSATHD1_AMPFLTBYP(self)
        self.zz_fdict['AMPFLTBYP'] = self.AMPFLTBYP
        self.PWRDETDIS = RM_Field_MODEM_NS_DSATHD1_PWRDETDIS(self)
        self.zz_fdict['PWRDETDIS'] = self.PWRDETDIS
        self.FREQSCALE = RM_Field_MODEM_NS_DSATHD1_FREQSCALE(self)
        self.zz_fdict['FREQSCALE'] = self.FREQSCALE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSACTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSACTRL, self).__init__(rmio, label,
            0xb8014000, 0x0FC,
            'DSACTRL', 'MODEM_NS.DSACTRL', 'read-write',
            u"",
            0x000A2090, 0xFFEFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DSAMODE = RM_Field_MODEM_NS_DSACTRL_DSAMODE(self)
        self.zz_fdict['DSAMODE'] = self.DSAMODE
        self.ARRTHD = RM_Field_MODEM_NS_DSACTRL_ARRTHD(self)
        self.zz_fdict['ARRTHD'] = self.ARRTHD
        self.ARRTOLERTHD0 = RM_Field_MODEM_NS_DSACTRL_ARRTOLERTHD0(self)
        self.zz_fdict['ARRTOLERTHD0'] = self.ARRTOLERTHD0
        self.ARRTOLERTHD1 = RM_Field_MODEM_NS_DSACTRL_ARRTOLERTHD1(self)
        self.zz_fdict['ARRTOLERTHD1'] = self.ARRTOLERTHD1
        self.SCHPRD = RM_Field_MODEM_NS_DSACTRL_SCHPRD(self)
        self.zz_fdict['SCHPRD'] = self.SCHPRD
        self.FREQAVGSYM = RM_Field_MODEM_NS_DSACTRL_FREQAVGSYM(self)
        self.zz_fdict['FREQAVGSYM'] = self.FREQAVGSYM
        self.TRANRSTDSA = RM_Field_MODEM_NS_DSACTRL_TRANRSTDSA(self)
        self.zz_fdict['TRANRSTDSA'] = self.TRANRSTDSA
        self.DSARSTON = RM_Field_MODEM_NS_DSACTRL_DSARSTON(self)
        self.zz_fdict['DSARSTON'] = self.DSARSTON
        self.GAINREDUCDLY = RM_Field_MODEM_NS_DSACTRL_GAINREDUCDLY(self)
        self.zz_fdict['GAINREDUCDLY'] = self.GAINREDUCDLY
        self.LOWDUTY = RM_Field_MODEM_NS_DSACTRL_LOWDUTY(self)
        self.zz_fdict['LOWDUTY'] = self.LOWDUTY
        self.RESTORE = RM_Field_MODEM_NS_DSACTRL_RESTORE(self)
        self.zz_fdict['RESTORE'] = self.RESTORE
        self.AGCBAUDEN = RM_Field_MODEM_NS_DSACTRL_AGCBAUDEN(self)
        self.zz_fdict['AGCBAUDEN'] = self.AGCBAUDEN
        self.AMPJUPTHD = RM_Field_MODEM_NS_DSACTRL_AMPJUPTHD(self)
        self.zz_fdict['AMPJUPTHD'] = self.AMPJUPTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VITERBIDEMOD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VITERBIDEMOD, self).__init__(rmio, label,
            0xb8014000, 0x100,
            'VITERBIDEMOD', 'MODEM_NS.VITERBIDEMOD', 'read-write',
            u"",
            0x00206100, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.VTDEMODEN = RM_Field_MODEM_NS_VITERBIDEMOD_VTDEMODEN(self)
        self.zz_fdict['VTDEMODEN'] = self.VTDEMODEN
        self.HARDDECISION = RM_Field_MODEM_NS_VITERBIDEMOD_HARDDECISION(self)
        self.zz_fdict['HARDDECISION'] = self.HARDDECISION
        self.VITERBIKSI1 = RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI1(self)
        self.zz_fdict['VITERBIKSI1'] = self.VITERBIKSI1
        self.VITERBIKSI2 = RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI2(self)
        self.zz_fdict['VITERBIKSI2'] = self.VITERBIKSI2
        self.VITERBIKSI3 = RM_Field_MODEM_NS_VITERBIDEMOD_VITERBIKSI3(self)
        self.zz_fdict['VITERBIKSI3'] = self.VITERBIKSI3
        self.SYNTHAFC = RM_Field_MODEM_NS_VITERBIDEMOD_SYNTHAFC(self)
        self.zz_fdict['SYNTHAFC'] = self.SYNTHAFC
        self.CORRCYCLE = RM_Field_MODEM_NS_VITERBIDEMOD_CORRCYCLE(self)
        self.zz_fdict['CORRCYCLE'] = self.CORRCYCLE
        self.CORRSTPSIZE = RM_Field_MODEM_NS_VITERBIDEMOD_CORRSTPSIZE(self)
        self.zz_fdict['CORRSTPSIZE'] = self.CORRSTPSIZE
        self.DISDEMODOF = RM_Field_MODEM_NS_VITERBIDEMOD_DISDEMODOF(self)
        self.zz_fdict['DISDEMODOF'] = self.DISDEMODOF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VTCORRCFG0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VTCORRCFG0, self).__init__(rmio, label,
            0xb8014000, 0x104,
            'VTCORRCFG0', 'MODEM_NS.VTCORRCFG0', 'read-write',
            u"",
            0x123556B7, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.EXPECTPATT = RM_Field_MODEM_NS_VTCORRCFG0_EXPECTPATT(self)
        self.zz_fdict['EXPECTPATT'] = self.EXPECTPATT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DIGMIXCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DIGMIXCTRL, self).__init__(rmio, label,
            0xb8014000, 0x10C,
            'DIGMIXCTRL', 'MODEM_NS.DIGMIXCTRL', 'read-write',
            u"",
            0x00000000, 0x007FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DIGMIXFREQ = RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXFREQ(self)
        self.zz_fdict['DIGMIXFREQ'] = self.DIGMIXFREQ
        self.DIGMIXMODE = RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXMODE(self)
        self.zz_fdict['DIGMIXMODE'] = self.DIGMIXMODE
        self.MIXERCONJ = RM_Field_MODEM_NS_DIGMIXCTRL_MIXERCONJ(self)
        self.zz_fdict['MIXERCONJ'] = self.MIXERCONJ
        self.DIGMIXFB = RM_Field_MODEM_NS_DIGMIXCTRL_DIGMIXFB(self)
        self.zz_fdict['DIGMIXFB'] = self.DIGMIXFB
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VTCORRCFG1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VTCORRCFG1, self).__init__(rmio, label,
            0xb8014000, 0x110,
            'VTCORRCFG1', 'MODEM_NS.VTCORRCFG1', 'read-write',
            u"",
            0x29043020, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CORRSHFTLEN = RM_Field_MODEM_NS_VTCORRCFG1_CORRSHFTLEN(self)
        self.zz_fdict['CORRSHFTLEN'] = self.CORRSHFTLEN
        self.VTFRQLIM = RM_Field_MODEM_NS_VTCORRCFG1_VTFRQLIM(self)
        self.zz_fdict['VTFRQLIM'] = self.VTFRQLIM
        self.EXPSYNCLEN = RM_Field_MODEM_NS_VTCORRCFG1_EXPSYNCLEN(self)
        self.zz_fdict['EXPSYNCLEN'] = self.EXPSYNCLEN
        self.BUFFHEAD = RM_Field_MODEM_NS_VTCORRCFG1_BUFFHEAD(self)
        self.zz_fdict['BUFFHEAD'] = self.BUFFHEAD
        self.EXPECTHT = RM_Field_MODEM_NS_VTCORRCFG1_EXPECTHT(self)
        self.zz_fdict['EXPECTHT'] = self.EXPECTHT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VTTRACK(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VTTRACK, self).__init__(rmio, label,
            0xb8014000, 0x114,
            'VTTRACK', 'MODEM_NS.VTTRACK', 'read-write',
            u"",
            0x4D80BB88, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FREQTRACKMODE = RM_Field_MODEM_NS_VTTRACK_FREQTRACKMODE(self)
        self.zz_fdict['FREQTRACKMODE'] = self.FREQTRACKMODE
        self.TIMTRACKTHD = RM_Field_MODEM_NS_VTTRACK_TIMTRACKTHD(self)
        self.zz_fdict['TIMTRACKTHD'] = self.TIMTRACKTHD
        self.TIMEACQUTHD = RM_Field_MODEM_NS_VTTRACK_TIMEACQUTHD(self)
        self.zz_fdict['TIMEACQUTHD'] = self.TIMEACQUTHD
        self.TIMCHK = RM_Field_MODEM_NS_VTTRACK_TIMCHK(self)
        self.zz_fdict['TIMCHK'] = self.TIMCHK
        self.TIMEOUTMODE = RM_Field_MODEM_NS_VTTRACK_TIMEOUTMODE(self)
        self.zz_fdict['TIMEOUTMODE'] = self.TIMEOUTMODE
        self.TIMGEAR = RM_Field_MODEM_NS_VTTRACK_TIMGEAR(self)
        self.zz_fdict['TIMGEAR'] = self.TIMGEAR
        self.FREQBIAS = RM_Field_MODEM_NS_VTTRACK_FREQBIAS(self)
        self.zz_fdict['FREQBIAS'] = self.FREQBIAS
        self.HIPWRTHD = RM_Field_MODEM_NS_VTTRACK_HIPWRTHD(self)
        self.zz_fdict['HIPWRTHD'] = self.HIPWRTHD
        self.SYNCTIMEOUTSEL = RM_Field_MODEM_NS_VTTRACK_SYNCTIMEOUTSEL(self)
        self.zz_fdict['SYNCTIMEOUTSEL'] = self.SYNCTIMEOUTSEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BREST(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BREST, self).__init__(rmio, label,
            0xb8014000, 0x118,
            'BREST', 'MODEM_NS.BREST', 'read-only',
            u"",
            0x00000000, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BRESTINT = RM_Field_MODEM_NS_BREST_BRESTINT(self)
        self.zz_fdict['BRESTINT'] = self.BRESTINT
        self.BRESTNUM = RM_Field_MODEM_NS_BREST_BRESTNUM(self)
        self.zz_fdict['BRESTNUM'] = self.BRESTNUM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_AUTOCG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_AUTOCG, self).__init__(rmio, label,
            0xb8014000, 0x124,
            'AUTOCG', 'MODEM_NS.AUTOCG', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.AUTOCGEN = RM_Field_MODEM_NS_AUTOCG_AUTOCGEN(self)
        self.zz_fdict['AUTOCGEN'] = self.AUTOCGEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CGCLKSTOP(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CGCLKSTOP, self).__init__(rmio, label,
            0xb8014000, 0x128,
            'CGCLKSTOP', 'MODEM_NS.CGCLKSTOP', 'read-write',
            u"",
            0x00000000, 0x0000FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FORCEOFF = RM_Field_MODEM_NS_CGCLKSTOP_FORCEOFF(self)
        self.zz_fdict['FORCEOFF'] = self.FORCEOFF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD2, self).__init__(rmio, label,
            0xb8014000, 0x130,
            'DSATHD2', 'MODEM_NS.DSATHD2', 'read-write',
            u"",
            0x0C660664, 0x7FFFFEFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POWABSTHDLOG = RM_Field_MODEM_NS_DSATHD2_POWABSTHDLOG(self)
        self.zz_fdict['POWABSTHDLOG'] = self.POWABSTHDLOG
        self.JUMPDETEN = RM_Field_MODEM_NS_DSATHD2_JUMPDETEN(self)
        self.zz_fdict['JUMPDETEN'] = self.JUMPDETEN
        self.FDADJTHD = RM_Field_MODEM_NS_DSATHD2_FDADJTHD(self)
        self.zz_fdict['FDADJTHD'] = self.FDADJTHD
        self.PMDETPASSTHD = RM_Field_MODEM_NS_DSATHD2_PMDETPASSTHD(self)
        self.zz_fdict['PMDETPASSTHD'] = self.PMDETPASSTHD
        self.FREQESTTHD = RM_Field_MODEM_NS_DSATHD2_FREQESTTHD(self)
        self.zz_fdict['FREQESTTHD'] = self.FREQESTTHD
        self.INTERFERDET = RM_Field_MODEM_NS_DSATHD2_INTERFERDET(self)
        self.zz_fdict['INTERFERDET'] = self.INTERFERDET
        self.PMDETFORCE = RM_Field_MODEM_NS_DSATHD2_PMDETFORCE(self)
        self.zz_fdict['PMDETFORCE'] = self.PMDETFORCE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DIRECTMODE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DIRECTMODE, self).__init__(rmio, label,
            0xb8014000, 0x134,
            'DIRECTMODE', 'MODEM_NS.DIRECTMODE', 'read-write',
            u"",
            0x0000010C, 0x00001F0F,
            0x00001000, 0x00002000,
            0x00003000)

        self.DMENABLE = RM_Field_MODEM_NS_DIRECTMODE_DMENABLE(self)
        self.zz_fdict['DMENABLE'] = self.DMENABLE
        self.SYNCASYNC = RM_Field_MODEM_NS_DIRECTMODE_SYNCASYNC(self)
        self.zz_fdict['SYNCASYNC'] = self.SYNCASYNC
        self.SYNCPREAM = RM_Field_MODEM_NS_DIRECTMODE_SYNCPREAM(self)
        self.zz_fdict['SYNCPREAM'] = self.SYNCPREAM
        self.CLKWIDTH = RM_Field_MODEM_NS_DIRECTMODE_CLKWIDTH(self)
        self.zz_fdict['CLKWIDTH'] = self.CLKWIDTH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE, self).__init__(rmio, label,
            0xb8014000, 0x138,
            'LONGRANGE', 'MODEM_NS.LONGRANGE', 'read-write',
            u"",
            0x00FA53E8, 0x7FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCORRTHD = RM_Field_MODEM_NS_LONGRANGE_LRCORRTHD(self)
        self.zz_fdict['LRCORRTHD'] = self.LRCORRTHD
        self.LRCORRSCHWIN = RM_Field_MODEM_NS_LONGRANGE_LRCORRSCHWIN(self)
        self.zz_fdict['LRCORRSCHWIN'] = self.LRCORRSCHWIN
        self.LRBLE = RM_Field_MODEM_NS_LONGRANGE_LRBLE(self)
        self.zz_fdict['LRBLE'] = self.LRBLE
        self.LRTIMCORRTHD = RM_Field_MODEM_NS_LONGRANGE_LRTIMCORRTHD(self)
        self.zz_fdict['LRTIMCORRTHD'] = self.LRTIMCORRTHD
        self.LRBLEDSA = RM_Field_MODEM_NS_LONGRANGE_LRBLEDSA(self)
        self.zz_fdict['LRBLEDSA'] = self.LRBLEDSA
        self.LRDEC = RM_Field_MODEM_NS_LONGRANGE_LRDEC(self)
        self.zz_fdict['LRDEC'] = self.LRDEC
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE1, self).__init__(rmio, label,
            0xb8014000, 0x13C,
            'LONGRANGE1', 'MODEM_NS.LONGRANGE1', 'read-write',
            u"",
            0x00000000, 0x3FFF7FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRSS = RM_Field_MODEM_NS_LONGRANGE1_LRSS(self)
        self.zz_fdict['LRSS'] = self.LRSS
        self.LRTIMEOUTTHD = RM_Field_MODEM_NS_LONGRANGE1_LRTIMEOUTTHD(self)
        self.zz_fdict['LRTIMEOUTTHD'] = self.LRTIMEOUTTHD
        self.CHPWRACCUDEL = RM_Field_MODEM_NS_LONGRANGE1_CHPWRACCUDEL(self)
        self.zz_fdict['CHPWRACCUDEL'] = self.CHPWRACCUDEL
        self.HYSVAL = RM_Field_MODEM_NS_LONGRANGE1_HYSVAL(self)
        self.zz_fdict['HYSVAL'] = self.HYSVAL
        self.AVGWIN = RM_Field_MODEM_NS_LONGRANGE1_AVGWIN(self)
        self.zz_fdict['AVGWIN'] = self.AVGWIN
        self.LRSPIKETHADD = RM_Field_MODEM_NS_LONGRANGE1_LRSPIKETHADD(self)
        self.zz_fdict['LRSPIKETHADD'] = self.LRSPIKETHADD
        self.LOGICBASEDPUGATE = RM_Field_MODEM_NS_LONGRANGE1_LOGICBASEDPUGATE(self)
        self.zz_fdict['LOGICBASEDPUGATE'] = self.LOGICBASEDPUGATE
        self.LOGICBASEDLRDEMODGATE = RM_Field_MODEM_NS_LONGRANGE1_LOGICBASEDLRDEMODGATE(self)
        self.zz_fdict['LOGICBASEDLRDEMODGATE'] = self.LOGICBASEDLRDEMODGATE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE2, self).__init__(rmio, label,
            0xb8014000, 0x140,
            'LONGRANGE2', 'MODEM_NS.LONGRANGE2', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRTH1 = RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH1(self)
        self.zz_fdict['LRCHPWRTH1'] = self.LRCHPWRTH1
        self.LRCHPWRTH2 = RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH2(self)
        self.zz_fdict['LRCHPWRTH2'] = self.LRCHPWRTH2
        self.LRCHPWRTH3 = RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH3(self)
        self.zz_fdict['LRCHPWRTH3'] = self.LRCHPWRTH3
        self.LRCHPWRTH4 = RM_Field_MODEM_NS_LONGRANGE2_LRCHPWRTH4(self)
        self.zz_fdict['LRCHPWRTH4'] = self.LRCHPWRTH4
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE3, self).__init__(rmio, label,
            0xb8014000, 0x144,
            'LONGRANGE3', 'MODEM_NS.LONGRANGE3', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRTH5 = RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH5(self)
        self.zz_fdict['LRCHPWRTH5'] = self.LRCHPWRTH5
        self.LRCHPWRTH6 = RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH6(self)
        self.zz_fdict['LRCHPWRTH6'] = self.LRCHPWRTH6
        self.LRCHPWRTH7 = RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH7(self)
        self.zz_fdict['LRCHPWRTH7'] = self.LRCHPWRTH7
        self.LRCHPWRTH8 = RM_Field_MODEM_NS_LONGRANGE3_LRCHPWRTH8(self)
        self.zz_fdict['LRCHPWRTH8'] = self.LRCHPWRTH8
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE4, self).__init__(rmio, label,
            0xb8014000, 0x148,
            'LONGRANGE4', 'MODEM_NS.LONGRANGE4', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRTH9 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRTH9(self)
        self.zz_fdict['LRCHPWRTH9'] = self.LRCHPWRTH9
        self.LRCHPWRTH10 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRTH10(self)
        self.zz_fdict['LRCHPWRTH10'] = self.LRCHPWRTH10
        self.LRCHPWRSH1 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH1(self)
        self.zz_fdict['LRCHPWRSH1'] = self.LRCHPWRSH1
        self.LRCHPWRSH2 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH2(self)
        self.zz_fdict['LRCHPWRSH2'] = self.LRCHPWRSH2
        self.LRCHPWRSH3 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH3(self)
        self.zz_fdict['LRCHPWRSH3'] = self.LRCHPWRSH3
        self.LRCHPWRSH4 = RM_Field_MODEM_NS_LONGRANGE4_LRCHPWRSH4(self)
        self.zz_fdict['LRCHPWRSH4'] = self.LRCHPWRSH4
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE5(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE5, self).__init__(rmio, label,
            0xb8014000, 0x14C,
            'LONGRANGE5', 'MODEM_NS.LONGRANGE5', 'read-write',
            u"",
            0x00000000, 0x0FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRSH5 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH5(self)
        self.zz_fdict['LRCHPWRSH5'] = self.LRCHPWRSH5
        self.LRCHPWRSH6 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH6(self)
        self.zz_fdict['LRCHPWRSH6'] = self.LRCHPWRSH6
        self.LRCHPWRSH7 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH7(self)
        self.zz_fdict['LRCHPWRSH7'] = self.LRCHPWRSH7
        self.LRCHPWRSH8 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH8(self)
        self.zz_fdict['LRCHPWRSH8'] = self.LRCHPWRSH8
        self.LRCHPWRSH9 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH9(self)
        self.zz_fdict['LRCHPWRSH9'] = self.LRCHPWRSH9
        self.LRCHPWRSH10 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH10(self)
        self.zz_fdict['LRCHPWRSH10'] = self.LRCHPWRSH10
        self.LRCHPWRSH11 = RM_Field_MODEM_NS_LONGRANGE5_LRCHPWRSH11(self)
        self.zz_fdict['LRCHPWRSH11'] = self.LRCHPWRSH11
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LONGRANGE6(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LONGRANGE6, self).__init__(rmio, label,
            0xb8014000, 0x150,
            'LONGRANGE6', 'MODEM_NS.LONGRANGE6', 'read-write',
            u"",
            0x00000000, 0xFFF7FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.LRCHPWRSPIKETH = RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRSPIKETH(self)
        self.zz_fdict['LRCHPWRSPIKETH'] = self.LRCHPWRSPIKETH
        self.LRSPIKETHD = RM_Field_MODEM_NS_LONGRANGE6_LRSPIKETHD(self)
        self.zz_fdict['LRSPIKETHD'] = self.LRSPIKETHD
        self.LRCHPWRTH11 = RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRTH11(self)
        self.zz_fdict['LRCHPWRTH11'] = self.LRCHPWRTH11
        self.LRCHPWRSH12 = RM_Field_MODEM_NS_LONGRANGE6_LRCHPWRSH12(self)
        self.zz_fdict['LRCHPWRSH12'] = self.LRCHPWRSH12
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_LRFRC(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_LRFRC, self).__init__(rmio, label,
            0xb8014000, 0x154,
            'LRFRC', 'MODEM_NS.LRFRC', 'read-write',
            u"",
            0x00000101, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CI500 = RM_Field_MODEM_NS_LRFRC_CI500(self)
        self.zz_fdict['CI500'] = self.CI500
        self.FRCACKTIMETHD = RM_Field_MODEM_NS_LRFRC_FRCACKTIMETHD(self)
        self.zz_fdict['FRCACKTIMETHD'] = self.FRCACKTIMETHD
        self.LRCORRMODE = RM_Field_MODEM_NS_LRFRC_LRCORRMODE(self)
        self.zz_fdict['LRCORRMODE'] = self.LRCORRMODE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD3, self).__init__(rmio, label,
            0xb8014000, 0x168,
            'DSATHD3', 'MODEM_NS.DSATHD3', 'read-write',
            u"",
            0x07830464, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SPIKETHDLO = RM_Field_MODEM_NS_DSATHD3_SPIKETHDLO(self)
        self.zz_fdict['SPIKETHDLO'] = self.SPIKETHDLO
        self.UNMODTHDLO = RM_Field_MODEM_NS_DSATHD3_UNMODTHDLO(self)
        self.zz_fdict['UNMODTHDLO'] = self.UNMODTHDLO
        self.FDEVMINTHDLO = RM_Field_MODEM_NS_DSATHD3_FDEVMINTHDLO(self)
        self.zz_fdict['FDEVMINTHDLO'] = self.FDEVMINTHDLO
        self.FDEVMAXTHDLO = RM_Field_MODEM_NS_DSATHD3_FDEVMAXTHDLO(self)
        self.zz_fdict['FDEVMAXTHDLO'] = self.FDEVMAXTHDLO
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DSATHD4(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DSATHD4, self).__init__(rmio, label,
            0xb8014000, 0x16C,
            'DSATHD4', 'MODEM_NS.DSATHD4', 'read-write',
            u"",
            0x00821388, 0x07FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POWABSTHDLO = RM_Field_MODEM_NS_DSATHD4_POWABSTHDLO(self)
        self.zz_fdict['POWABSTHDLO'] = self.POWABSTHDLO
        self.ARRTOLERTHD0LO = RM_Field_MODEM_NS_DSATHD4_ARRTOLERTHD0LO(self)
        self.zz_fdict['ARRTOLERTHD0LO'] = self.ARRTOLERTHD0LO
        self.ARRTOLERTHD1LO = RM_Field_MODEM_NS_DSATHD4_ARRTOLERTHD1LO(self)
        self.zz_fdict['ARRTOLERTHD1LO'] = self.ARRTOLERTHD1LO
        self.SWTHD = RM_Field_MODEM_NS_DSATHD4_SWTHD(self)
        self.zz_fdict['SWTHD'] = self.SWTHD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_VTBLETIMING(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_VTBLETIMING, self).__init__(rmio, label,
            0xb8014000, 0x170,
            'VTBLETIMING', 'MODEM_NS.VTBLETIMING', 'read-write',
            u"",
            0x00000000, 0x0000FFF3,
            0x00001000, 0x00002000,
            0x00003000)

        self.VTBLETIMINGSEL = RM_Field_MODEM_NS_VTBLETIMING_VTBLETIMINGSEL(self)
        self.zz_fdict['VTBLETIMINGSEL'] = self.VTBLETIMINGSEL
        self.TIMINGDELAY = RM_Field_MODEM_NS_VTBLETIMING_TIMINGDELAY(self)
        self.zz_fdict['TIMINGDELAY'] = self.TIMINGDELAY
        self.FLENOFF = RM_Field_MODEM_NS_VTBLETIMING_FLENOFF(self)
        self.zz_fdict['FLENOFF'] = self.FLENOFF
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_IF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IF, self).__init__(rmio, label,
            0xb8014000, 0x208,
            'IF', 'MODEM_NS.IF', 'read-write',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXFRAMESENT = RM_Field_MODEM_NS_IF_TXFRAMESENT(self)
        self.zz_fdict['TXFRAMESENT'] = self.TXFRAMESENT
        self.TXSYNCSENT = RM_Field_MODEM_NS_IF_TXSYNCSENT(self)
        self.zz_fdict['TXSYNCSENT'] = self.TXSYNCSENT
        self.TXPRESENT = RM_Field_MODEM_NS_IF_TXPRESENT(self)
        self.zz_fdict['TXPRESENT'] = self.TXPRESENT
        self.TXRAMPDONE = RM_Field_MODEM_NS_IF_TXRAMPDONE(self)
        self.zz_fdict['TXRAMPDONE'] = self.TXRAMPDONE
        self.LDTNOARR = RM_Field_MODEM_NS_IF_LDTNOARR(self)
        self.zz_fdict['LDTNOARR'] = self.LDTNOARR
        self.PHDSADET = RM_Field_MODEM_NS_IF_PHDSADET(self)
        self.zz_fdict['PHDSADET'] = self.PHDSADET
        self.PHYUNCODEDET = RM_Field_MODEM_NS_IF_PHYUNCODEDET(self)
        self.zz_fdict['PHYUNCODEDET'] = self.PHYUNCODEDET
        self.PHYCODEDET = RM_Field_MODEM_NS_IF_PHYCODEDET(self)
        self.zz_fdict['PHYCODEDET'] = self.PHYCODEDET
        self.RXTIMDET = RM_Field_MODEM_NS_IF_RXTIMDET(self)
        self.zz_fdict['RXTIMDET'] = self.RXTIMDET
        self.RXPREDET = RM_Field_MODEM_NS_IF_RXPREDET(self)
        self.zz_fdict['RXPREDET'] = self.RXPREDET
        self.RXFRAMEDET0 = RM_Field_MODEM_NS_IF_RXFRAMEDET0(self)
        self.zz_fdict['RXFRAMEDET0'] = self.RXFRAMEDET0
        self.RXFRAMEDET1 = RM_Field_MODEM_NS_IF_RXFRAMEDET1(self)
        self.zz_fdict['RXFRAMEDET1'] = self.RXFRAMEDET1
        self.RXTIMLOST = RM_Field_MODEM_NS_IF_RXTIMLOST(self)
        self.zz_fdict['RXTIMLOST'] = self.RXTIMLOST
        self.RXPRELOST = RM_Field_MODEM_NS_IF_RXPRELOST(self)
        self.zz_fdict['RXPRELOST'] = self.RXPRELOST
        self.RXFRAMEDETOF = RM_Field_MODEM_NS_IF_RXFRAMEDETOF(self)
        self.zz_fdict['RXFRAMEDETOF'] = self.RXFRAMEDETOF
        self.RXTIMNF = RM_Field_MODEM_NS_IF_RXTIMNF(self)
        self.zz_fdict['RXTIMNF'] = self.RXTIMNF
        self.FRCTIMOUT = RM_Field_MODEM_NS_IF_FRCTIMOUT(self)
        self.zz_fdict['FRCTIMOUT'] = self.FRCTIMOUT
        self.ETS = RM_Field_MODEM_NS_IF_ETS(self)
        self.zz_fdict['ETS'] = self.ETS
        self.CFGANTPATTRD = RM_Field_MODEM_NS_IF_CFGANTPATTRD(self)
        self.zz_fdict['CFGANTPATTRD'] = self.CFGANTPATTRD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_IEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IEN, self).__init__(rmio, label,
            0xb8014000, 0x20C,
            'IEN', 'MODEM_NS.IEN', 'read-write',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXFRAMESENT = RM_Field_MODEM_NS_IEN_TXFRAMESENT(self)
        self.zz_fdict['TXFRAMESENT'] = self.TXFRAMESENT
        self.TXSYNCSENT = RM_Field_MODEM_NS_IEN_TXSYNCSENT(self)
        self.zz_fdict['TXSYNCSENT'] = self.TXSYNCSENT
        self.TXPRESENT = RM_Field_MODEM_NS_IEN_TXPRESENT(self)
        self.zz_fdict['TXPRESENT'] = self.TXPRESENT
        self.TXRAMPDONE = RM_Field_MODEM_NS_IEN_TXRAMPDONE(self)
        self.zz_fdict['TXRAMPDONE'] = self.TXRAMPDONE
        self.LDTNOARR = RM_Field_MODEM_NS_IEN_LDTNOARR(self)
        self.zz_fdict['LDTNOARR'] = self.LDTNOARR
        self.PHDSADET = RM_Field_MODEM_NS_IEN_PHDSADET(self)
        self.zz_fdict['PHDSADET'] = self.PHDSADET
        self.PHYUNCODEDET = RM_Field_MODEM_NS_IEN_PHYUNCODEDET(self)
        self.zz_fdict['PHYUNCODEDET'] = self.PHYUNCODEDET
        self.PHYCODEDET = RM_Field_MODEM_NS_IEN_PHYCODEDET(self)
        self.zz_fdict['PHYCODEDET'] = self.PHYCODEDET
        self.RXTIMDET = RM_Field_MODEM_NS_IEN_RXTIMDET(self)
        self.zz_fdict['RXTIMDET'] = self.RXTIMDET
        self.RXPREDET = RM_Field_MODEM_NS_IEN_RXPREDET(self)
        self.zz_fdict['RXPREDET'] = self.RXPREDET
        self.RXFRAMEDET0 = RM_Field_MODEM_NS_IEN_RXFRAMEDET0(self)
        self.zz_fdict['RXFRAMEDET0'] = self.RXFRAMEDET0
        self.RXFRAMEDET1 = RM_Field_MODEM_NS_IEN_RXFRAMEDET1(self)
        self.zz_fdict['RXFRAMEDET1'] = self.RXFRAMEDET1
        self.RXTIMLOST = RM_Field_MODEM_NS_IEN_RXTIMLOST(self)
        self.zz_fdict['RXTIMLOST'] = self.RXTIMLOST
        self.RXPRELOST = RM_Field_MODEM_NS_IEN_RXPRELOST(self)
        self.zz_fdict['RXPRELOST'] = self.RXPRELOST
        self.RXFRAMEDETOF = RM_Field_MODEM_NS_IEN_RXFRAMEDETOF(self)
        self.zz_fdict['RXFRAMEDETOF'] = self.RXFRAMEDETOF
        self.RXTIMNF = RM_Field_MODEM_NS_IEN_RXTIMNF(self)
        self.zz_fdict['RXTIMNF'] = self.RXTIMNF
        self.FRCTIMOUT = RM_Field_MODEM_NS_IEN_FRCTIMOUT(self)
        self.zz_fdict['FRCTIMOUT'] = self.FRCTIMOUT
        self.ETS = RM_Field_MODEM_NS_IEN_ETS(self)
        self.zz_fdict['ETS'] = self.ETS
        self.CFGANTPATTRD = RM_Field_MODEM_NS_IEN_CFGANTPATTRD(self)
        self.zz_fdict['CFGANTPATTRD'] = self.CFGANTPATTRD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CMD(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CMD, self).__init__(rmio, label,
            0xb8014000, 0x218,
            'CMD', 'MODEM_NS.CMD', 'write-only',
            u"",
            0x00000000, 0x00000039,
            0x00001000, 0x00002000,
            0x00003000)

        self.PRESTOP = RM_Field_MODEM_NS_CMD_PRESTOP(self)
        self.zz_fdict['PRESTOP'] = self.PRESTOP
        self.AFCTXLOCK = RM_Field_MODEM_NS_CMD_AFCTXLOCK(self)
        self.zz_fdict['AFCTXLOCK'] = self.AFCTXLOCK
        self.AFCTXCLEAR = RM_Field_MODEM_NS_CMD_AFCTXCLEAR(self)
        self.zz_fdict['AFCTXCLEAR'] = self.AFCTXCLEAR
        self.AFCRXCLEAR = RM_Field_MODEM_NS_CMD_AFCRXCLEAR(self)
        self.zz_fdict['AFCRXCLEAR'] = self.AFCRXCLEAR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_FSMSTATUS(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_FSMSTATUS, self).__init__(rmio, label,
            0xb8014000, 0x21C,
            'FSMSTATUS', 'MODEM_NS.FSMSTATUS', 'read-only',
            u"",
            0x00000000, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DETSTATE = RM_Field_MODEM_NS_FSMSTATUS_DETSTATE(self)
        self.zz_fdict['DETSTATE'] = self.DETSTATE
        self.DSASTATE = RM_Field_MODEM_NS_FSMSTATUS_DSASTATE(self)
        self.zz_fdict['DSASTATE'] = self.DSASTATE
        self.LRBLESTATE = RM_Field_MODEM_NS_FSMSTATUS_LRBLESTATE(self)
        self.zz_fdict['LRBLESTATE'] = self.LRBLESTATE
        self.NBBLESTATE = RM_Field_MODEM_NS_FSMSTATUS_NBBLESTATE(self)
        self.zz_fdict['NBBLESTATE'] = self.NBBLESTATE
        self.ANTDIVSTATE = RM_Field_MODEM_NS_FSMSTATUS_ANTDIVSTATE(self)
        self.zz_fdict['ANTDIVSTATE'] = self.ANTDIVSTATE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS2, self).__init__(rmio, label,
            0xb8014000, 0x220,
            'STATUS2', 'MODEM_NS.STATUS2', 'read-only',
            u"",
            0x00000000, 0xFFFCFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CHPWRACCUMUX = RM_Field_MODEM_NS_STATUS2_CHPWRACCUMUX(self)
        self.zz_fdict['CHPWRACCUMUX'] = self.CHPWRACCUMUX
        self.BBSSMUX = RM_Field_MODEM_NS_STATUS2_BBSSMUX(self)
        self.zz_fdict['BBSSMUX'] = self.BBSSMUX
        self.LRBLECI = RM_Field_MODEM_NS_STATUS2_LRBLECI(self)
        self.zz_fdict['LRBLECI'] = self.LRBLECI
        self.UNCODEDPHY = RM_Field_MODEM_NS_STATUS2_UNCODEDPHY(self)
        self.zz_fdict['UNCODEDPHY'] = self.UNCODEDPHY
        self.CODEDPHY = RM_Field_MODEM_NS_STATUS2_CODEDPHY(self)
        self.zz_fdict['CODEDPHY'] = self.CODEDPHY
        self.RTVTCORR = RM_Field_MODEM_NS_STATUS2_RTVTCORR(self)
        self.zz_fdict['RTVTCORR'] = self.RTVTCORR
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_STATUS3(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_STATUS3, self).__init__(rmio, label,
            0xb8014000, 0x224,
            'STATUS3', 'MODEM_NS.STATUS3', 'read-only',
            u"",
            0x00000000, 0x057FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BBPFOUTABS1 = RM_Field_MODEM_NS_STATUS3_BBPFOUTABS1(self)
        self.zz_fdict['BBPFOUTABS1'] = self.BBPFOUTABS1
        self.BBPFOUTABS = RM_Field_MODEM_NS_STATUS3_BBPFOUTABS(self)
        self.zz_fdict['BBPFOUTABS'] = self.BBPFOUTABS
        self.LRDSALIVE = RM_Field_MODEM_NS_STATUS3_LRDSALIVE(self)
        self.zz_fdict['LRDSALIVE'] = self.LRDSALIVE
        self.LRDSADET = RM_Field_MODEM_NS_STATUS3_LRDSADET(self)
        self.zz_fdict['LRDSADET'] = self.LRDSADET
        self.SYNCSECPEAKABTH = RM_Field_MODEM_NS_STATUS3_SYNCSECPEAKABTH(self)
        self.zz_fdict['SYNCSECPEAKABTH'] = self.SYNCSECPEAKABTH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_IRCAL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IRCAL, self).__init__(rmio, label,
            0xb8014000, 0x228,
            'IRCAL', 'MODEM_NS.IRCAL', 'read-write',
            u"",
            0x00000000, 0x0000FFBF,
            0x00001000, 0x00002000,
            0x00003000)

        self.IRCALEN = RM_Field_MODEM_NS_IRCAL_IRCALEN(self)
        self.zz_fdict['IRCALEN'] = self.IRCALEN
        self.MURSHF = RM_Field_MODEM_NS_IRCAL_MURSHF(self)
        self.zz_fdict['MURSHF'] = self.MURSHF
        self.MUISHF = RM_Field_MODEM_NS_IRCAL_MUISHF(self)
        self.zz_fdict['MUISHF'] = self.MUISHF
        self.IRCORREN = RM_Field_MODEM_NS_IRCAL_IRCORREN(self)
        self.zz_fdict['IRCORREN'] = self.IRCORREN
        self.IRCALCOEFRSTCMD = RM_Field_MODEM_NS_IRCAL_IRCALCOEFRSTCMD(self)
        self.zz_fdict['IRCALCOEFRSTCMD'] = self.IRCALCOEFRSTCMD
        self.IRCALIFADCDBG = RM_Field_MODEM_NS_IRCAL_IRCALIFADCDBG(self)
        self.zz_fdict['IRCALIFADCDBG'] = self.IRCALIFADCDBG
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_IRCALCOEF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IRCALCOEF, self).__init__(rmio, label,
            0xb8014000, 0x22C,
            'IRCALCOEF', 'MODEM_NS.IRCALCOEF', 'read-only',
            u"",
            0x00000000, 0x7FFF7FFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CRV = RM_Field_MODEM_NS_IRCALCOEF_CRV(self)
        self.zz_fdict['CRV'] = self.CRV
        self.CIV = RM_Field_MODEM_NS_IRCALCOEF_CIV(self)
        self.zz_fdict['CIV'] = self.CIV
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BLEIQDSA(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BLEIQDSA, self).__init__(rmio, label,
            0xb8014000, 0x230,
            'BLEIQDSA', 'MODEM_NS.BLEIQDSA', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.BLEIQDSAEN = RM_Field_MODEM_NS_BLEIQDSA_BLEIQDSAEN(self)
        self.zz_fdict['BLEIQDSAEN'] = self.BLEIQDSAEN
        self.BLEIQDSATH = RM_Field_MODEM_NS_BLEIQDSA_BLEIQDSATH(self)
        self.zz_fdict['BLEIQDSATH'] = self.BLEIQDSATH
        self.BLEIQDSAIIRCOEFPWR = RM_Field_MODEM_NS_BLEIQDSA_BLEIQDSAIIRCOEFPWR(self)
        self.zz_fdict['BLEIQDSAIIRCOEFPWR'] = self.BLEIQDSAIIRCOEFPWR
        self.BLEIQDSADIFFTH1 = RM_Field_MODEM_NS_BLEIQDSA_BLEIQDSADIFFTH1(self)
        self.zz_fdict['BLEIQDSADIFFTH1'] = self.BLEIQDSADIFFTH1
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BLEIQDSAEXT1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BLEIQDSAEXT1, self).__init__(rmio, label,
            0xb8014000, 0x234,
            'BLEIQDSAEXT1', 'MODEM_NS.BLEIQDSAEXT1', 'read-write',
            u"",
            0x0E000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.FREQSCALEIQDSA = RM_Field_MODEM_NS_BLEIQDSAEXT1_FREQSCALEIQDSA(self)
        self.zz_fdict['FREQSCALEIQDSA'] = self.FREQSCALEIQDSA
        self.CHPWRFIRAVGEN = RM_Field_MODEM_NS_BLEIQDSAEXT1_CHPWRFIRAVGEN(self)
        self.zz_fdict['CHPWRFIRAVGEN'] = self.CHPWRFIRAVGEN
        self.CHPWRFIRAVGVAL = RM_Field_MODEM_NS_BLEIQDSAEXT1_CHPWRFIRAVGVAL(self)
        self.zz_fdict['CHPWRFIRAVGVAL'] = self.CHPWRFIRAVGVAL
        self.CORRIIRAVGMULFACT = RM_Field_MODEM_NS_BLEIQDSAEXT1_CORRIIRAVGMULFACT(self)
        self.zz_fdict['CORRIIRAVGMULFACT'] = self.CORRIIRAVGMULFACT
        self.BLEIQDSAADDRBIAS = RM_Field_MODEM_NS_BLEIQDSAEXT1_BLEIQDSAADDRBIAS(self)
        self.zz_fdict['BLEIQDSAADDRBIAS'] = self.BLEIQDSAADDRBIAS
        self.BLEIQDSATHCOMB = RM_Field_MODEM_NS_BLEIQDSAEXT1_BLEIQDSATHCOMB(self)
        self.zz_fdict['BLEIQDSATHCOMB'] = self.BLEIQDSATHCOMB
        self.MAXCORRCNTIQDSA = RM_Field_MODEM_NS_BLEIQDSAEXT1_MAXCORRCNTIQDSA(self)
        self.zz_fdict['MAXCORRCNTIQDSA'] = self.MAXCORRCNTIQDSA
        self.IIRRST = RM_Field_MODEM_NS_BLEIQDSAEXT1_IIRRST(self)
        self.zz_fdict['IIRRST'] = self.IIRRST
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SYNCPROPERTIES(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SYNCPROPERTIES, self).__init__(rmio, label,
            0xb8014000, 0x238,
            'SYNCPROPERTIES', 'MODEM_NS.SYNCPROPERTIES', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SYNCCORRCLR = RM_Field_MODEM_NS_SYNCPROPERTIES_SYNCCORRCLR(self)
        self.zz_fdict['SYNCCORRCLR'] = self.SYNCCORRCLR
        self.SYNCSECPEAKTH = RM_Field_MODEM_NS_SYNCPROPERTIES_SYNCSECPEAKTH(self)
        self.zz_fdict['SYNCSECPEAKTH'] = self.SYNCSECPEAKTH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_DIGIGAINCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_DIGIGAINCTRL, self).__init__(rmio, label,
            0xb8014000, 0x23C,
            'DIGIGAINCTRL', 'MODEM_NS.DIGIGAINCTRL', 'read-write',
            u"",
            0x00000000, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DIGIGAINEN = RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINEN(self)
        self.zz_fdict['DIGIGAINEN'] = self.DIGIGAINEN
        self.DIGIGAINSEL = RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINSEL(self)
        self.zz_fdict['DIGIGAINSEL'] = self.DIGIGAINSEL
        self.DIGIGAINDOUBLE = RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINDOUBLE(self)
        self.zz_fdict['DIGIGAINDOUBLE'] = self.DIGIGAINDOUBLE
        self.DIGIGAINHALF = RM_Field_MODEM_NS_DIGIGAINCTRL_DIGIGAINHALF(self)
        self.zz_fdict['DIGIGAINHALF'] = self.DIGIGAINHALF
        self.DEC0GAIN = RM_Field_MODEM_NS_DIGIGAINCTRL_DEC0GAIN(self)
        self.zz_fdict['DEC0GAIN'] = self.DEC0GAIN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PRSCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PRSCTRL, self).__init__(rmio, label,
            0xb8014000, 0x240,
            'PRSCTRL', 'MODEM_NS.PRSCTRL', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.POSTPONESEL = RM_Field_MODEM_NS_PRSCTRL_POSTPONESEL(self)
        self.zz_fdict['POSTPONESEL'] = self.POSTPONESEL
        self.ADVANCESEL = RM_Field_MODEM_NS_PRSCTRL_ADVANCESEL(self)
        self.zz_fdict['ADVANCESEL'] = self.ADVANCESEL
        self.NEWWNDSEL = RM_Field_MODEM_NS_PRSCTRL_NEWWNDSEL(self)
        self.zz_fdict['NEWWNDSEL'] = self.NEWWNDSEL
        self.WEAKSEL = RM_Field_MODEM_NS_PRSCTRL_WEAKSEL(self)
        self.zz_fdict['WEAKSEL'] = self.WEAKSEL
        self.SYNCSENTSEL = RM_Field_MODEM_NS_PRSCTRL_SYNCSENTSEL(self)
        self.zz_fdict['SYNCSENTSEL'] = self.SYNCSENTSEL
        self.PRESENTSEL = RM_Field_MODEM_NS_PRSCTRL_PRESENTSEL(self)
        self.zz_fdict['PRESENTSEL'] = self.PRESENTSEL
        self.LOWCORRSEL = RM_Field_MODEM_NS_PRSCTRL_LOWCORRSEL(self)
        self.zz_fdict['LOWCORRSEL'] = self.LOWCORRSEL
        self.ANT0SEL = RM_Field_MODEM_NS_PRSCTRL_ANT0SEL(self)
        self.zz_fdict['ANT0SEL'] = self.ANT0SEL
        self.ANT1SEL = RM_Field_MODEM_NS_PRSCTRL_ANT1SEL(self)
        self.zz_fdict['ANT1SEL'] = self.ANT1SEL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_PADEBUG(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_PADEBUG, self).__init__(rmio, label,
            0xb8014000, 0x244,
            'PADEBUG', 'MODEM_NS.PADEBUG', 'read-write',
            u"",
            0x00000000, 0x00001E00,
            0x00001000, 0x00002000,
            0x00003000)

        self.MANPACLKAMPCTRL = RM_Field_MODEM_NS_PADEBUG_MANPACLKAMPCTRL(self)
        self.zz_fdict['MANPACLKAMPCTRL'] = self.MANPACLKAMPCTRL
        self.ENMANPACLKAMPCTRL = RM_Field_MODEM_NS_PADEBUG_ENMANPACLKAMPCTRL(self)
        self.zz_fdict['ENMANPACLKAMPCTRL'] = self.ENMANPACLKAMPCTRL
        self.ENMANPAPOWER = RM_Field_MODEM_NS_PADEBUG_ENMANPAPOWER(self)
        self.zz_fdict['ENMANPAPOWER'] = self.ENMANPAPOWER
        self.ENMANPASELSLICE = RM_Field_MODEM_NS_PADEBUG_ENMANPASELSLICE(self)
        self.zz_fdict['ENMANPASELSLICE'] = self.ENMANPASELSLICE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_REALTIMCFE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_REALTIMCFE, self).__init__(rmio, label,
            0xb8014000, 0x248,
            'REALTIMCFE', 'MODEM_NS.REALTIMCFE', 'read-write',
            u"",
            0x001F81F4, 0xE01FFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.MINCOSTTHD = RM_Field_MODEM_NS_REALTIMCFE_MINCOSTTHD(self)
        self.zz_fdict['MINCOSTTHD'] = self.MINCOSTTHD
        self.RTSCHWIN = RM_Field_MODEM_NS_REALTIMCFE_RTSCHWIN(self)
        self.zz_fdict['RTSCHWIN'] = self.RTSCHWIN
        self.RTSCHMODE = RM_Field_MODEM_NS_REALTIMCFE_RTSCHMODE(self)
        self.zz_fdict['RTSCHMODE'] = self.RTSCHMODE
        self.TRACKINGWIN = RM_Field_MODEM_NS_REALTIMCFE_TRACKINGWIN(self)
        self.zz_fdict['TRACKINGWIN'] = self.TRACKINGWIN
        self.SYNCACQWIN = RM_Field_MODEM_NS_REALTIMCFE_SYNCACQWIN(self)
        self.zz_fdict['SYNCACQWIN'] = self.SYNCACQWIN
        self.SINEWEN = RM_Field_MODEM_NS_REALTIMCFE_SINEWEN(self)
        self.zz_fdict['SINEWEN'] = self.SINEWEN
        self.VTAFCFRAME = RM_Field_MODEM_NS_REALTIMCFE_VTAFCFRAME(self)
        self.zz_fdict['VTAFCFRAME'] = self.VTAFCFRAME
        self.RTCFEEN = RM_Field_MODEM_NS_REALTIMCFE_RTCFEEN(self)
        self.zz_fdict['RTCFEEN'] = self.RTCFEEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SEQIF(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SEQIF, self).__init__(rmio, label,
            0xb8014000, 0x24C,
            'SEQIF', 'MODEM_NS.SEQIF', 'read-write',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXFRAMESENT = RM_Field_MODEM_NS_SEQIF_TXFRAMESENT(self)
        self.zz_fdict['TXFRAMESENT'] = self.TXFRAMESENT
        self.TXSYNCSENT = RM_Field_MODEM_NS_SEQIF_TXSYNCSENT(self)
        self.zz_fdict['TXSYNCSENT'] = self.TXSYNCSENT
        self.TXPRESENT = RM_Field_MODEM_NS_SEQIF_TXPRESENT(self)
        self.zz_fdict['TXPRESENT'] = self.TXPRESENT
        self.TXRAMPDONE = RM_Field_MODEM_NS_SEQIF_TXRAMPDONE(self)
        self.zz_fdict['TXRAMPDONE'] = self.TXRAMPDONE
        self.LDTNOARR = RM_Field_MODEM_NS_SEQIF_LDTNOARR(self)
        self.zz_fdict['LDTNOARR'] = self.LDTNOARR
        self.PHDSADET = RM_Field_MODEM_NS_SEQIF_PHDSADET(self)
        self.zz_fdict['PHDSADET'] = self.PHDSADET
        self.PHYUNCODEDET = RM_Field_MODEM_NS_SEQIF_PHYUNCODEDET(self)
        self.zz_fdict['PHYUNCODEDET'] = self.PHYUNCODEDET
        self.PHYCODEDET = RM_Field_MODEM_NS_SEQIF_PHYCODEDET(self)
        self.zz_fdict['PHYCODEDET'] = self.PHYCODEDET
        self.RXTIMDET = RM_Field_MODEM_NS_SEQIF_RXTIMDET(self)
        self.zz_fdict['RXTIMDET'] = self.RXTIMDET
        self.RXPREDET = RM_Field_MODEM_NS_SEQIF_RXPREDET(self)
        self.zz_fdict['RXPREDET'] = self.RXPREDET
        self.RXFRAMEDET0 = RM_Field_MODEM_NS_SEQIF_RXFRAMEDET0(self)
        self.zz_fdict['RXFRAMEDET0'] = self.RXFRAMEDET0
        self.RXFRAMEDET1 = RM_Field_MODEM_NS_SEQIF_RXFRAMEDET1(self)
        self.zz_fdict['RXFRAMEDET1'] = self.RXFRAMEDET1
        self.RXTIMLOST = RM_Field_MODEM_NS_SEQIF_RXTIMLOST(self)
        self.zz_fdict['RXTIMLOST'] = self.RXTIMLOST
        self.RXPRELOST = RM_Field_MODEM_NS_SEQIF_RXPRELOST(self)
        self.zz_fdict['RXPRELOST'] = self.RXPRELOST
        self.RXFRAMEDETOF = RM_Field_MODEM_NS_SEQIF_RXFRAMEDETOF(self)
        self.zz_fdict['RXFRAMEDETOF'] = self.RXFRAMEDETOF
        self.RXTIMNF = RM_Field_MODEM_NS_SEQIF_RXTIMNF(self)
        self.zz_fdict['RXTIMNF'] = self.RXTIMNF
        self.FRCTIMOUT = RM_Field_MODEM_NS_SEQIF_FRCTIMOUT(self)
        self.zz_fdict['FRCTIMOUT'] = self.FRCTIMOUT
        self.ETS = RM_Field_MODEM_NS_SEQIF_ETS(self)
        self.zz_fdict['ETS'] = self.ETS
        self.CFGANTPATTRD = RM_Field_MODEM_NS_SEQIF_CFGANTPATTRD(self)
        self.zz_fdict['CFGANTPATTRD'] = self.CFGANTPATTRD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SEQIEN(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SEQIEN, self).__init__(rmio, label,
            0xb8014000, 0x250,
            'SEQIEN', 'MODEM_NS.SEQIEN', 'read-write',
            u"",
            0x00000000, 0x0007FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TXFRAMESENT = RM_Field_MODEM_NS_SEQIEN_TXFRAMESENT(self)
        self.zz_fdict['TXFRAMESENT'] = self.TXFRAMESENT
        self.TXSYNCSENT = RM_Field_MODEM_NS_SEQIEN_TXSYNCSENT(self)
        self.zz_fdict['TXSYNCSENT'] = self.TXSYNCSENT
        self.TXPRESENT = RM_Field_MODEM_NS_SEQIEN_TXPRESENT(self)
        self.zz_fdict['TXPRESENT'] = self.TXPRESENT
        self.TXRAMPDONE = RM_Field_MODEM_NS_SEQIEN_TXRAMPDONE(self)
        self.zz_fdict['TXRAMPDONE'] = self.TXRAMPDONE
        self.LDTNOARR = RM_Field_MODEM_NS_SEQIEN_LDTNOARR(self)
        self.zz_fdict['LDTNOARR'] = self.LDTNOARR
        self.PHDSADET = RM_Field_MODEM_NS_SEQIEN_PHDSADET(self)
        self.zz_fdict['PHDSADET'] = self.PHDSADET
        self.PHYUNCODEDET = RM_Field_MODEM_NS_SEQIEN_PHYUNCODEDET(self)
        self.zz_fdict['PHYUNCODEDET'] = self.PHYUNCODEDET
        self.PHYCODEDET = RM_Field_MODEM_NS_SEQIEN_PHYCODEDET(self)
        self.zz_fdict['PHYCODEDET'] = self.PHYCODEDET
        self.RXTIMDET = RM_Field_MODEM_NS_SEQIEN_RXTIMDET(self)
        self.zz_fdict['RXTIMDET'] = self.RXTIMDET
        self.RXPREDET = RM_Field_MODEM_NS_SEQIEN_RXPREDET(self)
        self.zz_fdict['RXPREDET'] = self.RXPREDET
        self.RXFRAMEDET0 = RM_Field_MODEM_NS_SEQIEN_RXFRAMEDET0(self)
        self.zz_fdict['RXFRAMEDET0'] = self.RXFRAMEDET0
        self.RXFRAMEDET1 = RM_Field_MODEM_NS_SEQIEN_RXFRAMEDET1(self)
        self.zz_fdict['RXFRAMEDET1'] = self.RXFRAMEDET1
        self.RXTIMLOST = RM_Field_MODEM_NS_SEQIEN_RXTIMLOST(self)
        self.zz_fdict['RXTIMLOST'] = self.RXTIMLOST
        self.RXPRELOST = RM_Field_MODEM_NS_SEQIEN_RXPRELOST(self)
        self.zz_fdict['RXPRELOST'] = self.RXPRELOST
        self.RXFRAMEDETOF = RM_Field_MODEM_NS_SEQIEN_RXFRAMEDETOF(self)
        self.zz_fdict['RXFRAMEDETOF'] = self.RXFRAMEDETOF
        self.RXTIMNF = RM_Field_MODEM_NS_SEQIEN_RXTIMNF(self)
        self.zz_fdict['RXTIMNF'] = self.RXTIMNF
        self.FRCTIMOUT = RM_Field_MODEM_NS_SEQIEN_FRCTIMOUT(self)
        self.zz_fdict['FRCTIMOUT'] = self.FRCTIMOUT
        self.ETS = RM_Field_MODEM_NS_SEQIEN_ETS(self)
        self.zz_fdict['ETS'] = self.ETS
        self.CFGANTPATTRD = RM_Field_MODEM_NS_SEQIEN_CFGANTPATTRD(self)
        self.zz_fdict['CFGANTPATTRD'] = self.CFGANTPATTRD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ETSCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ETSCTRL, self).__init__(rmio, label,
            0xb8014000, 0x254,
            'ETSCTRL', 'MODEM_NS.ETSCTRL', 'read-write',
            u"",
            0x00000000, 0x3FFFF7FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ETSLOC = RM_Field_MODEM_NS_ETSCTRL_ETSLOC(self)
        self.zz_fdict['ETSLOC'] = self.ETSLOC
        self.CAPSIGONPRS = RM_Field_MODEM_NS_ETSCTRL_CAPSIGONPRS(self)
        self.zz_fdict['CAPSIGONPRS'] = self.CAPSIGONPRS
        self.CAPTRIG = RM_Field_MODEM_NS_ETSCTRL_CAPTRIG(self)
        self.zz_fdict['CAPTRIG'] = self.CAPTRIG
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTSWCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTSWCTRL, self).__init__(rmio, label,
            0xb8014000, 0x258,
            'ANTSWCTRL', 'MODEM_NS.ANTSWCTRL', 'read-write',
            u"",
            0x003C0000, 0x01FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTDFLTSEL = RM_Field_MODEM_NS_ANTSWCTRL_ANTDFLTSEL(self)
        self.zz_fdict['ANTDFLTSEL'] = self.ANTDFLTSEL
        self.ANTCOUNT = RM_Field_MODEM_NS_ANTSWCTRL_ANTCOUNT(self)
        self.zz_fdict['ANTCOUNT'] = self.ANTCOUNT
        self.ANTSWTYPE = RM_Field_MODEM_NS_ANTSWCTRL_ANTSWTYPE(self)
        self.zz_fdict['ANTSWTYPE'] = self.ANTSWTYPE
        self.ANTSWRST = RM_Field_MODEM_NS_ANTSWCTRL_ANTSWRST(self)
        self.zz_fdict['ANTSWRST'] = self.ANTSWRST
        self.CFGANTPATTEN = RM_Field_MODEM_NS_ANTSWCTRL_CFGANTPATTEN(self)
        self.zz_fdict['CFGANTPATTEN'] = self.CFGANTPATTEN
        self.ANTSWENABLE = RM_Field_MODEM_NS_ANTSWCTRL_ANTSWENABLE(self)
        self.zz_fdict['ANTSWENABLE'] = self.ANTSWENABLE
        self.EXTDSTOPPULSECNT = RM_Field_MODEM_NS_ANTSWCTRL_EXTDSTOPPULSECNT(self)
        self.zz_fdict['EXTDSTOPPULSECNT'] = self.EXTDSTOPPULSECNT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTSWSTART(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTSWSTART, self).__init__(rmio, label,
            0xb8014000, 0x25C,
            'ANTSWSTART', 'MODEM_NS.ANTSWSTART', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTSWSTARTTIM = RM_Field_MODEM_NS_ANTSWSTART_ANTSWSTARTTIM(self)
        self.zz_fdict['ANTSWSTARTTIM'] = self.ANTSWSTARTTIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTSWEND(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTSWEND, self).__init__(rmio, label,
            0xb8014000, 0x260,
            'ANTSWEND', 'MODEM_NS.ANTSWEND', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ANTSWENDTIM = RM_Field_MODEM_NS_ANTSWEND_ANTSWENDTIM(self)
        self.zz_fdict['ANTSWENDTIM'] = self.ANTSWENDTIM
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TRECPMPATT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TRECPMPATT, self).__init__(rmio, label,
            0xb8014000, 0x264,
            'TRECPMPATT', 'MODEM_NS.TRECPMPATT', 'read-write',
            u"",
            0x55555555, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PMEXPECTPATT = RM_Field_MODEM_NS_TRECPMPATT_PMEXPECTPATT(self)
        self.zz_fdict['PMEXPECTPATT'] = self.PMEXPECTPATT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_TRECPMDET(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_TRECPMDET, self).__init__(rmio, label,
            0xb8014000, 0x268,
            'TRECPMDET', 'MODEM_NS.TRECPMDET', 'read-write',
            u"",
            0x00000017, 0xBFFFC3FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.PMACQUINGWIN = RM_Field_MODEM_NS_TRECPMDET_PMACQUINGWIN(self)
        self.zz_fdict['PMACQUINGWIN'] = self.PMACQUINGWIN
        self.PMCOSTVALTHD = RM_Field_MODEM_NS_TRECPMDET_PMCOSTVALTHD(self)
        self.zz_fdict['PMCOSTVALTHD'] = self.PMCOSTVALTHD
        self.PMTIMEOUTSEL = RM_Field_MODEM_NS_TRECPMDET_PMTIMEOUTSEL(self)
        self.zz_fdict['PMTIMEOUTSEL'] = self.PMTIMEOUTSEL
        self.PHSCALE = RM_Field_MODEM_NS_TRECPMDET_PHSCALE(self)
        self.zz_fdict['PHSCALE'] = self.PHSCALE
        self.PMMINCOSTTHD = RM_Field_MODEM_NS_TRECPMDET_PMMINCOSTTHD(self)
        self.zz_fdict['PMMINCOSTTHD'] = self.PMMINCOSTTHD
        self.VTPMDETSEL = RM_Field_MODEM_NS_TRECPMDET_VTPMDETSEL(self)
        self.zz_fdict['VTPMDETSEL'] = self.VTPMDETSEL
        self.COSTHYST = RM_Field_MODEM_NS_TRECPMDET_COSTHYST(self)
        self.zz_fdict['COSTHYST'] = self.COSTHYST
        self.PREAMSCH = RM_Field_MODEM_NS_TRECPMDET_PREAMSCH(self)
        self.zz_fdict['PREAMSCH'] = self.PREAMSCH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_CFGANTPATT(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_CFGANTPATT, self).__init__(rmio, label,
            0xb8014000, 0x26C,
            'CFGANTPATT', 'MODEM_NS.CFGANTPATT', 'read-write',
            u"",
            0x00000000, 0x3FFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CFGANTPATTVAL = RM_Field_MODEM_NS_CFGANTPATT_CFGANTPATTVAL(self)
        self.zz_fdict['CFGANTPATTVAL'] = self.CFGANTPATTVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ETSTIM(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ETSTIM, self).__init__(rmio, label,
            0xb8014000, 0x270,
            'ETSTIM', 'MODEM_NS.ETSTIM', 'read-write',
            u"",
            0x00000000, 0x0003FFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ETSTIMVAL = RM_Field_MODEM_NS_ETSTIM_ETSTIMVAL(self)
        self.zz_fdict['ETSTIMVAL'] = self.ETSTIMVAL
        self.ETSCOUNTEREN = RM_Field_MODEM_NS_ETSTIM_ETSCOUNTEREN(self)
        self.zz_fdict['ETSCOUNTEREN'] = self.ETSCOUNTEREN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTSWCTRL1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTSWCTRL1, self).__init__(rmio, label,
            0xb8014000, 0x274,
            'ANTSWCTRL1', 'MODEM_NS.ANTSWCTRL1', 'read-write',
            u"",
            0x0006AAAA, 0x00FFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.TIMEPERIOD = RM_Field_MODEM_NS_ANTSWCTRL1_TIMEPERIOD(self)
        self.zz_fdict['TIMEPERIOD'] = self.TIMEPERIOD
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_COCURRMODE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_COCURRMODE, self).__init__(rmio, label,
            0xb8014000, 0x278,
            'COCURRMODE', 'MODEM_NS.COCURRMODE', 'read-write',
            u"",
            0x00000000, 0x80000000,
            0x00001000, 0x00002000,
            0x00003000)

        self.CONCURRENT = RM_Field_MODEM_NS_COCURRMODE_CONCURRENT(self)
        self.zz_fdict['CONCURRENT'] = self.CONCURRENT
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_ANTDIVCTRL(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_ANTDIVCTRL, self).__init__(rmio, label,
            0xb8014000, 0x27C,
            'ANTDIVCTRL', 'MODEM_NS.ANTDIVCTRL', 'read-write',
            u"",
            0x00000000, 0x000001FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.ADPRETHRESH = RM_Field_MODEM_NS_ANTDIVCTRL_ADPRETHRESH(self)
        self.zz_fdict['ADPRETHRESH'] = self.ADPRETHRESH
        self.ENADPRETHRESH = RM_Field_MODEM_NS_ANTDIVCTRL_ENADPRETHRESH(self)
        self.zz_fdict['ENADPRETHRESH'] = self.ENADPRETHRESH
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_BLEIQDSAEXT2(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_BLEIQDSAEXT2, self).__init__(rmio, label,
            0xb8014000, 0x280,
            'BLEIQDSAEXT2', 'MODEM_NS.BLEIQDSAEXT2', 'read-write',
            u"",
            0x00000000, 0x000007FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.DISMAXPEAKTRACKMODE = RM_Field_MODEM_NS_BLEIQDSAEXT2_DISMAXPEAKTRACKMODE(self)
        self.zz_fdict['DISMAXPEAKTRACKMODE'] = self.DISMAXPEAKTRACKMODE
        self.BBSSDEBOUNCETIM = RM_Field_MODEM_NS_BLEIQDSAEXT2_BBSSDEBOUNCETIM(self)
        self.zz_fdict['BBSSDEBOUNCETIM'] = self.BBSSDEBOUNCETIM
        self.BBSSDIFFCHVAL = RM_Field_MODEM_NS_BLEIQDSAEXT2_BBSSDIFFCHVAL(self)
        self.zz_fdict['BBSSDIFFCHVAL'] = self.BBSSDIFFCHVAL
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_SPARE(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_SPARE, self).__init__(rmio, label,
            0xb8014000, 0x284,
            'SPARE', 'MODEM_NS.SPARE', 'read-write',
            u"",
            0x00000000, 0x000000FF,
            0x00001000, 0x00002000,
            0x00003000)

        self.SPARE = RM_Field_MODEM_NS_SPARE_SPARE(self)
        self.zz_fdict['SPARE'] = self.SPARE
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_IRCALCOEFWR0(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IRCALCOEFWR0, self).__init__(rmio, label,
            0xb8014000, 0x288,
            'IRCALCOEFWR0', 'MODEM_NS.IRCALCOEFWR0', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CRVWD = RM_Field_MODEM_NS_IRCALCOEFWR0_CRVWD(self)
        self.zz_fdict['CRVWD'] = self.CRVWD
        self.CRVWEN = RM_Field_MODEM_NS_IRCALCOEFWR0_CRVWEN(self)
        self.zz_fdict['CRVWEN'] = self.CRVWEN
        self.CIVWD = RM_Field_MODEM_NS_IRCALCOEFWR0_CIVWD(self)
        self.zz_fdict['CIVWD'] = self.CIVWD
        self.CIVWEN = RM_Field_MODEM_NS_IRCALCOEFWR0_CIVWEN(self)
        self.zz_fdict['CIVWEN'] = self.CIVWEN
        self.__dict__['zz_frozen'] = True


class RM_Register_MODEM_NS_IRCALCOEFWR1(Base_RM_Register):
    def __init__(self, rmio, label):
        self.__dict__['zz_frozen'] = False
        super(RM_Register_MODEM_NS_IRCALCOEFWR1, self).__init__(rmio, label,
            0xb8014000, 0x28C,
            'IRCALCOEFWR1', 'MODEM_NS.IRCALCOEFWR1', 'read-write',
            u"",
            0x00000000, 0xFFFFFFFF,
            0x00001000, 0x00002000,
            0x00003000)

        self.CRVWD = RM_Field_MODEM_NS_IRCALCOEFWR1_CRVWD(self)
        self.zz_fdict['CRVWD'] = self.CRVWD
        self.CRVWEN = RM_Field_MODEM_NS_IRCALCOEFWR1_CRVWEN(self)
        self.zz_fdict['CRVWEN'] = self.CRVWEN
        self.CIVWD = RM_Field_MODEM_NS_IRCALCOEFWR1_CIVWD(self)
        self.zz_fdict['CIVWD'] = self.CIVWD
        self.CIVWEN = RM_Field_MODEM_NS_IRCALCOEFWR1_CIVWEN(self)
        self.zz_fdict['CIVWEN'] = self.CIVWEN
        self.__dict__['zz_frozen'] = True



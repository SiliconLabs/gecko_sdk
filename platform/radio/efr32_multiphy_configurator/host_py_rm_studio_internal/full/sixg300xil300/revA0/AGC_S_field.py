
# -*- coding: utf-8 -*-

from . static import Base_RM_Field


class RM_Field_AGC_S_IPVERSION_IPVERSION(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IPVERSION_IPVERSION, self).__init__(register,
            'IPVERSION', 'AGC_S.IPVERSION.IPVERSION', 'read-only',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_EN_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_EN_EN, self).__init__(register,
            'EN', 'AGC_S.EN.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_GAININDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_GAININDEX, self).__init__(register,
            'GAININDEX', 'AGC_S.STATUS0.GAININDEX', 'read-only',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_RFPKDLOWLAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_RFPKDLOWLAT, self).__init__(register,
            'RFPKDLOWLAT', 'AGC_S.STATUS0.RFPKDLOWLAT', 'read-only',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_RFPKDHILAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_RFPKDHILAT, self).__init__(register,
            'RFPKDHILAT', 'AGC_S.STATUS0.RFPKDHILAT', 'read-only',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_IFPKDLOLAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_IFPKDLOLAT, self).__init__(register,
            'IFPKDLOLAT', 'AGC_S.STATUS0.IFPKDLOLAT', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_IFPKDHILAT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_IFPKDHILAT, self).__init__(register,
            'IFPKDHILAT', 'AGC_S.STATUS0.IFPKDHILAT', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_CCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_CCA, self).__init__(register,
            'CCA', 'AGC_S.STATUS0.CCA', 'read-only',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_GAINOK(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_GAINOK, self).__init__(register,
            'GAINOK', 'AGC_S.STATUS0.GAINOK', 'read-only',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_PGAINDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_PGAINDEX, self).__init__(register,
            'PGAINDEX', 'AGC_S.STATUS0.PGAINDEX', 'read-only',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_LNAINDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_LNAINDEX, self).__init__(register,
            'LNAINDEX', 'AGC_S.STATUS0.LNAINDEX', 'read-only',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_PNINDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_PNINDEX, self).__init__(register,
            'PNINDEX', 'AGC_S.STATUS0.PNINDEX', 'read-only',
            u"",
            20, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS0_ADCINDEX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS0_ADCINDEX, self).__init__(register,
            'ADCINDEX', 'AGC_S.STATUS0.ADCINDEX', 'read-only',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS1_CHPWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS1_CHPWR, self).__init__(register,
            'CHPWR', 'AGC_S.STATUS1.CHPWR', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS1_FASTLOOPSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS1_FASTLOOPSTATE, self).__init__(register,
            'FASTLOOPSTATE', 'AGC_S.STATUS1.FASTLOOPSTATE', 'read-only',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS1_CFLOOPSTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS1_CFLOOPSTATE, self).__init__(register,
            'CFLOOPSTATE', 'AGC_S.STATUS1.CFLOOPSTATE', 'read-only',
            u"",
            13, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS1_RSSISTATE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS1_RSSISTATE, self).__init__(register,
            'RSSISTATE', 'AGC_S.STATUS1.RSSISTATE', 'read-only',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS1_RFPKDLOWLATCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS1_RFPKDLOWLATCNT, self).__init__(register,
            'RFPKDLOWLATCNT', 'AGC_S.STATUS1.RFPKDLOWLATCNT', 'read-only',
            u"",
            18, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS2_RFPKDHILATCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS2_RFPKDHILATCNT, self).__init__(register,
            'RFPKDHILATCNT', 'AGC_S.STATUS2.RFPKDHILATCNT', 'read-only',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS2_PNDWNUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS2_PNDWNUP, self).__init__(register,
            'PNDWNUP', 'AGC_S.STATUS2.PNDWNUP', 'read-only',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STATUS2_RFPKDPRDCNT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STATUS2_RFPKDPRDCNT, self).__init__(register,
            'RFPKDPRDCNT', 'AGC_S.STATUS2.RFPKDPRDCNT', 'read-only',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSI_RSSIFRAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSI_RSSIFRAC, self).__init__(register,
            'RSSIFRAC', 'AGC_S.RSSI.RSSIFRAC', 'read-only',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSI_RSSIINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSI_RSSIINT, self).__init__(register,
            'RSSIINT', 'AGC_S.RSSI.RSSIINT', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FRAMERSSI_FRAMERSSIFRAC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FRAMERSSI_FRAMERSSIFRAC, self).__init__(register,
            'FRAMERSSIFRAC', 'AGC_S.FRAMERSSI.FRAMERSSIFRAC', 'read-only',
            u"",
            6, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FRAMERSSI_FRAMERSSIINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FRAMERSSI_FRAMERSSIINT, self).__init__(register,
            'FRAMERSSIINT', 'AGC_S.FRAMERSSI.FRAMERSSIINT', 'read-only',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_PWRTARGET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_PWRTARGET, self).__init__(register,
            'PWRTARGET', 'AGC_S.CTRL0.PWRTARGET', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_MODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_MODE, self).__init__(register,
            'MODE', 'AGC_S.CTRL0.MODE', 'read-write',
            u"",
            8, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_RSSISHIFT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_RSSISHIFT, self).__init__(register,
            'RSSISHIFT', 'AGC_S.CTRL0.RSSISHIFT', 'read-write',
            u"",
            11, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_DISCFLOOPADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_DISCFLOOPADJ, self).__init__(register,
            'DISCFLOOPADJ', 'AGC_S.CTRL0.DISCFLOOPADJ', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_CFLOOPNFADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_CFLOOPNFADJ, self).__init__(register,
            'CFLOOPNFADJ', 'AGC_S.CTRL0.CFLOOPNFADJ', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_CFLOOPNEWCALC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_CFLOOPNEWCALC, self).__init__(register,
            'CFLOOPNEWCALC', 'AGC_S.CTRL0.CFLOOPNEWCALC', 'read-write',
            u"",
            21, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_DISRESETCHPWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_DISRESETCHPWR, self).__init__(register,
            'DISRESETCHPWR', 'AGC_S.CTRL0.DISRESETCHPWR', 'read-write',
            u"",
            22, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_ADCATTENMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_ADCATTENMODE, self).__init__(register,
            'ADCATTENMODE', 'AGC_S.CTRL0.ADCATTENMODE', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_ADCATTENCODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_ADCATTENCODE, self).__init__(register,
            'ADCATTENCODE', 'AGC_S.CTRL0.ADCATTENCODE', 'read-write',
            u"",
            25, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_ENRSSIRESET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_ENRSSIRESET, self).__init__(register,
            'ENRSSIRESET', 'AGC_S.CTRL0.ENRSSIRESET', 'read-write',
            u"",
            27, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_DSADISCFLOOP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_DSADISCFLOOP, self).__init__(register,
            'DSADISCFLOOP', 'AGC_S.CTRL0.DSADISCFLOOP', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_DISPNGAINUP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_DISPNGAINUP, self).__init__(register,
            'DISPNGAINUP', 'AGC_S.CTRL0.DISPNGAINUP', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_DISPNDWNCOMP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_DISPNDWNCOMP, self).__init__(register,
            'DISPNDWNCOMP', 'AGC_S.CTRL0.DISPNDWNCOMP', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL0_AGCRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_AGCRST, self).__init__(register,
            'AGCRST', 'AGC_S.CTRL0.AGCRST', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL1_CCATHRSH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL1_CCATHRSH, self).__init__(register,
            'CCATHRSH', 'AGC_S.CTRL1.CCATHRSH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL1_RSSIPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL1_RSSIPERIOD, self).__init__(register,
            'RSSIPERIOD', 'AGC_S.CTRL1.RSSIPERIOD', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL1_PWRPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL1_PWRPERIOD, self).__init__(register,
            'PWRPERIOD', 'AGC_S.CTRL1.PWRPERIOD', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL1_CCAMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL1_CCAMODE, self).__init__(register,
            'CCAMODE', 'AGC_S.CTRL1.CCAMODE', 'read-write',
            u"",
            15, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL1_CCAMODE3LOGIC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL1_CCAMODE3LOGIC, self).__init__(register,
            'CCAMODE3LOGIC', 'AGC_S.CTRL1.CCAMODE3LOGIC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL1_CCASWCTRL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL1_CCASWCTRL, self).__init__(register,
            'CCASWCTRL', 'AGC_S.CTRL1.CCASWCTRL', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL1_DISRSTONPREDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL1_DISRSTONPREDET, self).__init__(register,
            'DISRSTONPREDET', 'AGC_S.CTRL1.DISRSTONPREDET', 'read-write',
            u"",
            19, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL1_CFLOOPINCREQMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL1_CFLOOPINCREQMODE, self).__init__(register,
            'CFLOOPINCREQMODE', 'AGC_S.CTRL1.CFLOOPINCREQMODE', 'read-write',
            u"",
            20, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_DMASEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_DMASEL, self).__init__(register,
            'DMASEL', 'AGC_S.CTRL2.DMASEL', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_SAFEMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_SAFEMODE, self).__init__(register,
            'SAFEMODE', 'AGC_S.CTRL2.SAFEMODE', 'read-write',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_SAFEMODETHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_SAFEMODETHD, self).__init__(register,
            'SAFEMODETHD', 'AGC_S.CTRL2.SAFEMODETHD', 'read-write',
            u"",
            2, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_REHICNTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_REHICNTTHD, self).__init__(register,
            'REHICNTTHD', 'AGC_S.CTRL2.REHICNTTHD', 'read-write',
            u"",
            5, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_RELOTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_RELOTHD, self).__init__(register,
            'RELOTHD', 'AGC_S.CTRL2.RELOTHD', 'read-write',
            u"",
            13, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_RELBYCHPWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_RELBYCHPWR, self).__init__(register,
            'RELBYCHPWR', 'AGC_S.CTRL2.RELBYCHPWR', 'read-write',
            u"",
            16, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_RELTARGETPWR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_RELTARGETPWR, self).__init__(register,
            'RELTARGETPWR', 'AGC_S.CTRL2.RELTARGETPWR', 'read-write',
            u"",
            18, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_RSSICCASUB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_RSSICCASUB, self).__init__(register,
            'RSSICCASUB', 'AGC_S.CTRL2.RSSICCASUB', 'read-write',
            u"",
            26, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_DEBCNTRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_DEBCNTRST, self).__init__(register,
            'DEBCNTRST', 'AGC_S.CTRL2.DEBCNTRST', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_PRSDEBUGEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_PRSDEBUGEN, self).__init__(register,
            'PRSDEBUGEN', 'AGC_S.CTRL2.PRSDEBUGEN', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL2_DISRFPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL2_DISRFPKD, self).__init__(register,
            'DISRFPKD', 'AGC_S.CTRL2.DISRFPKD', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL3_IFPKDDEB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL3_IFPKDDEB, self).__init__(register,
            'IFPKDDEB', 'AGC_S.CTRL3.IFPKDDEB', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL3_IFPKDDEBTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL3_IFPKDDEBTHD, self).__init__(register,
            'IFPKDDEBTHD', 'AGC_S.CTRL3.IFPKDDEBTHD', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL3_IFPKDDEBPRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL3_IFPKDDEBPRD, self).__init__(register,
            'IFPKDDEBPRD', 'AGC_S.CTRL3.IFPKDDEBPRD', 'read-write',
            u"",
            3, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL3_IFPKDDEBRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL3_IFPKDDEBRST, self).__init__(register,
            'IFPKDDEBRST', 'AGC_S.CTRL3.IFPKDDEBRST', 'read-write',
            u"",
            9, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL3_RFPKDDEB(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL3_RFPKDDEB, self).__init__(register,
            'RFPKDDEB', 'AGC_S.CTRL3.RFPKDDEB', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL3_RFPKDDEBTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL3_RFPKDDEBTHD, self).__init__(register,
            'RFPKDDEBTHD', 'AGC_S.CTRL3.RFPKDDEBTHD', 'read-write',
            u"",
            14, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL3_RFPKDDEBPRD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL3_RFPKDDEBPRD, self).__init__(register,
            'RFPKDDEBPRD', 'AGC_S.CTRL3.RFPKDDEBPRD', 'read-write',
            u"",
            19, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL3_RFPKDDEBRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL3_RFPKDDEBRST, self).__init__(register,
            'RFPKDDEBRST', 'AGC_S.CTRL3.RFPKDDEBRST', 'read-write',
            u"",
            27, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL4_PERIODRFPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL4_PERIODRFPKD, self).__init__(register,
            'PERIODRFPKD', 'AGC_S.CTRL4.PERIODRFPKD', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL4_DISRFPKDCNTRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL4_DISRFPKDCNTRST, self).__init__(register,
            'DISRFPKDCNTRST', 'AGC_S.CTRL4.DISRFPKDCNTRST', 'read-write',
            u"",
            23, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL4_DISRSTCONDI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL4_DISRSTCONDI, self).__init__(register,
            'DISRSTCONDI', 'AGC_S.CTRL4.DISRSTCONDI', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL4_RFPKDPRDGEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL4_RFPKDPRDGEAR, self).__init__(register,
            'RFPKDPRDGEAR', 'AGC_S.CTRL4.RFPKDPRDGEAR', 'read-write',
            u"",
            25, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL4_RFPKDSYNCSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL4_RFPKDSYNCSEL, self).__init__(register,
            'RFPKDSYNCSEL', 'AGC_S.CTRL4.RFPKDSYNCSEL', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL4_RFPKDSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL4_RFPKDSEL, self).__init__(register,
            'RFPKDSEL', 'AGC_S.CTRL4.RFPKDSEL', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL4_FRZPKDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL4_FRZPKDEN, self).__init__(register,
            'FRZPKDEN', 'AGC_S.CTRL4.FRZPKDEN', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL4_RFPKDCNTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL4_RFPKDCNTEN, self).__init__(register,
            'RFPKDCNTEN', 'AGC_S.CTRL4.RFPKDCNTEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL5_PNUPDISTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL5_PNUPDISTHD, self).__init__(register,
            'PNUPDISTHD', 'AGC_S.CTRL5.PNUPDISTHD', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL5_PNUPRELTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL5_PNUPRELTHD, self).__init__(register,
            'PNUPRELTHD', 'AGC_S.CTRL5.PNUPRELTHD', 'read-write',
            u"",
            12, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL5_SEQPNUPALLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL5_SEQPNUPALLOW, self).__init__(register,
            'SEQPNUPALLOW', 'AGC_S.CTRL5.SEQPNUPALLOW', 'read-write',
            u"",
            30, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL5_SEQRFPKDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL5_SEQRFPKDEN, self).__init__(register,
            'SEQRFPKDEN', 'AGC_S.CTRL5.SEQRFPKDEN', 'read-write',
            u"",
            31, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL6_DUALRFPKDDEC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL6_DUALRFPKDDEC, self).__init__(register,
            'DUALRFPKDDEC', 'AGC_S.CTRL6.DUALRFPKDDEC', 'read-write',
            u"",
            0, 18)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL6_ENDUALRFPKD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL6_ENDUALRFPKD, self).__init__(register,
            'ENDUALRFPKD', 'AGC_S.CTRL6.ENDUALRFPKD', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL6_GAINDETTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL6_GAINDETTHD, self).__init__(register,
            'GAINDETTHD', 'AGC_S.CTRL6.GAINDETTHD', 'read-write',
            u"",
            19, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL7_SUBDEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL7_SUBDEN, self).__init__(register,
            'SUBDEN', 'AGC_S.CTRL7.SUBDEN', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL7_SUBINT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL7_SUBINT, self).__init__(register,
            'SUBINT', 'AGC_S.CTRL7.SUBINT', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL7_SUBNUM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL7_SUBNUM, self).__init__(register,
            'SUBNUM', 'AGC_S.CTRL7.SUBNUM', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CTRL7_SUBPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL7_SUBPERIOD, self).__init__(register,
            'SUBPERIOD', 'AGC_S.CTRL7.SUBPERIOD', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSISTEPTHR_POSSTEPTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSISTEPTHR_POSSTEPTHR, self).__init__(register,
            'POSSTEPTHR', 'AGC_S.RSSISTEPTHR.POSSTEPTHR', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSISTEPTHR_NEGSTEPTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSISTEPTHR_NEGSTEPTHR, self).__init__(register,
            'NEGSTEPTHR', 'AGC_S.RSSISTEPTHR.NEGSTEPTHR', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSISTEPTHR_STEPPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSISTEPTHR_STEPPER, self).__init__(register,
            'STEPPER', 'AGC_S.RSSISTEPTHR.STEPPER', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSISTEPTHR_DEMODRESTARTPER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSISTEPTHR_DEMODRESTARTPER, self).__init__(register,
            'DEMODRESTARTPER', 'AGC_S.RSSISTEPTHR.DEMODRESTARTPER', 'read-write',
            u"",
            17, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSISTEPTHR_DEMODRESTARTTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSISTEPTHR_DEMODRESTARTTHR, self).__init__(register,
            'DEMODRESTARTTHR', 'AGC_S.RSSISTEPTHR.DEMODRESTARTTHR', 'read-write',
            u"",
            21, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSISTEPTHR_RSSIFAST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSISTEPTHR_RSSIFAST, self).__init__(register,
            'RSSIFAST', 'AGC_S.RSSISTEPTHR.RSSIFAST', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MANGAIN_MANGAINEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MANGAIN_MANGAINEN, self).__init__(register,
            'MANGAINEN', 'AGC_S.MANGAIN.MANGAINEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MANGAIN_MANGAINIFPGA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MANGAIN_MANGAINIFPGA, self).__init__(register,
            'MANGAINIFPGA', 'AGC_S.MANGAIN.MANGAINIFPGA', 'read-write',
            u"",
            1, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MANGAIN_MANGAINLNA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MANGAIN_MANGAINLNA, self).__init__(register,
            'MANGAINLNA', 'AGC_S.MANGAIN.MANGAINLNA', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MANGAIN_MANGAINPN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MANGAIN_MANGAINPN, self).__init__(register,
            'MANGAINPN', 'AGC_S.MANGAIN.MANGAINPN', 'read-write',
            u"",
            9, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MANGAIN_MANRFLATRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MANGAIN_MANRFLATRST, self).__init__(register,
            'MANRFLATRST', 'AGC_S.MANGAIN.MANRFLATRST', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MANGAIN_MANIFLOLATRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MANGAIN_MANIFLOLATRST, self).__init__(register,
            'MANIFLOLATRST', 'AGC_S.MANGAIN.MANIFLOLATRST', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MANGAIN_MANIFHILATRST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MANGAIN_MANIFHILATRST, self).__init__(register,
            'MANIFHILATRST', 'AGC_S.MANGAIN.MANIFHILATRST', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_RSSIVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_RSSIVALID, self).__init__(register,
            'RSSIVALID', 'AGC_S.IF.RSSIVALID', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_CCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_CCA, self).__init__(register,
            'CCA', 'AGC_S.IF.CCA', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_RSSIPOSSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_RSSIPOSSTEP, self).__init__(register,
            'RSSIPOSSTEP', 'AGC_S.IF.RSSIPOSSTEP', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_RSSINEGSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_RSSINEGSTEP, self).__init__(register,
            'RSSINEGSTEP', 'AGC_S.IF.RSSINEGSTEP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_RSSIDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_RSSIDONE, self).__init__(register,
            'RSSIDONE', 'AGC_S.IF.RSSIDONE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_SHORTRSSIPOSSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_SHORTRSSIPOSSTEP, self).__init__(register,
            'SHORTRSSIPOSSTEP', 'AGC_S.IF.SHORTRSSIPOSSTEP', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_RFPKDPRDDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_RFPKDPRDDONE, self).__init__(register,
            'RFPKDPRDDONE', 'AGC_S.IF.RFPKDPRDDONE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_RFPKDCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_RFPKDCNTDONE, self).__init__(register,
            'RFPKDCNTDONE', 'AGC_S.IF.RFPKDCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_RSSIHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_RSSIHIGH, self).__init__(register,
            'RSSIHIGH', 'AGC_S.IF.RSSIHIGH', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_RSSILOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_RSSILOW, self).__init__(register,
            'RSSILOW', 'AGC_S.IF.RSSILOW', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_CCANODET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_CCANODET, self).__init__(register,
            'CCANODET', 'AGC_S.IF.CCANODET', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_GAINBELOWGAINTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_GAINBELOWGAINTHD, self).__init__(register,
            'GAINBELOWGAINTHD', 'AGC_S.IF.GAINBELOWGAINTHD', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_GAINUPDATEFRZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_GAINUPDATEFRZ, self).__init__(register,
            'GAINUPDATEFRZ', 'AGC_S.IF.GAINUPDATEFRZ', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_PNATTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_PNATTEN, self).__init__(register,
            'PNATTEN', 'AGC_S.IF.PNATTEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_COLLDETRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_COLLDETRSSIMAPRE, self).__init__(register,
            'COLLDETRSSIMAPRE', 'AGC_S.IF.COLLDETRSSIMAPRE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IF_COLLDETRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IF_COLLDETRSSIMASYNC, self).__init__(register,
            'COLLDETRSSIMASYNC', 'AGC_S.IF.COLLDETRSSIMASYNC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_RSSIVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_RSSIVALID, self).__init__(register,
            'RSSIVALID', 'AGC_S.IEN.RSSIVALID', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_CCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_CCA, self).__init__(register,
            'CCA', 'AGC_S.IEN.CCA', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_RSSIPOSSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_RSSIPOSSTEP, self).__init__(register,
            'RSSIPOSSTEP', 'AGC_S.IEN.RSSIPOSSTEP', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_RSSINEGSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_RSSINEGSTEP, self).__init__(register,
            'RSSINEGSTEP', 'AGC_S.IEN.RSSINEGSTEP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_RSSIDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_RSSIDONE, self).__init__(register,
            'RSSIDONE', 'AGC_S.IEN.RSSIDONE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_SHORTRSSIPOSSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_SHORTRSSIPOSSTEP, self).__init__(register,
            'SHORTRSSIPOSSTEP', 'AGC_S.IEN.SHORTRSSIPOSSTEP', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_RFPKDPRDDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_RFPKDPRDDONE, self).__init__(register,
            'RFPKDPRDDONE', 'AGC_S.IEN.RFPKDPRDDONE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_RFPKDCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_RFPKDCNTDONE, self).__init__(register,
            'RFPKDCNTDONE', 'AGC_S.IEN.RFPKDCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_RSSIHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_RSSIHIGH, self).__init__(register,
            'RSSIHIGH', 'AGC_S.IEN.RSSIHIGH', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_RSSILOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_RSSILOW, self).__init__(register,
            'RSSILOW', 'AGC_S.IEN.RSSILOW', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_CCANODET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_CCANODET, self).__init__(register,
            'CCANODET', 'AGC_S.IEN.CCANODET', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_GAINBELOWGAINTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_GAINBELOWGAINTHD, self).__init__(register,
            'GAINBELOWGAINTHD', 'AGC_S.IEN.GAINBELOWGAINTHD', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_GAINUPDATEFRZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_GAINUPDATEFRZ, self).__init__(register,
            'GAINUPDATEFRZ', 'AGC_S.IEN.GAINUPDATEFRZ', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_PNATTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_PNATTEN, self).__init__(register,
            'PNATTEN', 'AGC_S.IEN.PNATTEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_COLLDETRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_COLLDETRSSIMAPRE, self).__init__(register,
            'COLLDETRSSIMAPRE', 'AGC_S.IEN.COLLDETRSSIMAPRE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_IEN_COLLDETRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_IEN_COLLDETRSSIMASYNC, self).__init__(register,
            'COLLDETRSSIMASYNC', 'AGC_S.IEN.COLLDETRSSIMASYNC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CMD_RSSISTART(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CMD_RSSISTART, self).__init__(register,
            'RSSISTART', 'AGC_S.CMD.RSSISTART', 'write-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINRANGE_LNAINDEXBORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINRANGE_LNAINDEXBORDER, self).__init__(register,
            'LNAINDEXBORDER', 'AGC_S.GAINRANGE.LNAINDEXBORDER', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINRANGE_PGAINDEXBORDER(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINRANGE_PGAINDEXBORDER, self).__init__(register,
            'PGAINDEXBORDER', 'AGC_S.GAINRANGE.PGAINDEXBORDER', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINRANGE_GAININCSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINRANGE_GAININCSTEP, self).__init__(register,
            'GAININCSTEP', 'AGC_S.GAINRANGE.GAININCSTEP', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINRANGE_PNGAINSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINRANGE_PNGAINSTEP, self).__init__(register,
            'PNGAINSTEP', 'AGC_S.GAINRANGE.PNGAINSTEP', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINRANGE_LATCHEDHISTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINRANGE_LATCHEDHISTEP, self).__init__(register,
            'LATCHEDHISTEP', 'AGC_S.GAINRANGE.LATCHEDHISTEP', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINRANGE_HIPWRTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINRANGE_HIPWRTHD, self).__init__(register,
            'HIPWRTHD', 'AGC_S.GAINRANGE.HIPWRTHD', 'read-write',
            u"",
            20, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_AGCPERIOD0_PERIODHI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_AGCPERIOD0_PERIODHI, self).__init__(register,
            'PERIODHI', 'AGC_S.AGCPERIOD0.PERIODHI', 'read-write',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_AGCPERIOD0_MAXHICNTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_AGCPERIOD0_MAXHICNTTHD, self).__init__(register,
            'MAXHICNTTHD', 'AGC_S.AGCPERIOD0.MAXHICNTTHD', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_AGCPERIOD0_SETTLETIMEIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_AGCPERIOD0_SETTLETIMEIF, self).__init__(register,
            'SETTLETIMEIF', 'AGC_S.AGCPERIOD0.SETTLETIMEIF', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_AGCPERIOD0_SETTLETIMERF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_AGCPERIOD0_SETTLETIMERF, self).__init__(register,
            'SETTLETIMERF', 'AGC_S.AGCPERIOD0.SETTLETIMERF', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_AGCPERIOD1_PERIODLOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_AGCPERIOD1_PERIODLOW, self).__init__(register,
            'PERIODLOW', 'AGC_S.AGCPERIOD1.PERIODLOW', 'read-write',
            u"",
            0, 32)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_HICNTREGION0_HICNTREGION0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_HICNTREGION0_HICNTREGION0, self).__init__(register,
            'HICNTREGION0', 'AGC_S.HICNTREGION0.HICNTREGION0', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_HICNTREGION0_HICNTREGION1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_HICNTREGION0_HICNTREGION1, self).__init__(register,
            'HICNTREGION1', 'AGC_S.HICNTREGION0.HICNTREGION1', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_HICNTREGION0_HICNTREGION2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_HICNTREGION0_HICNTREGION2, self).__init__(register,
            'HICNTREGION2', 'AGC_S.HICNTREGION0.HICNTREGION2', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_HICNTREGION0_HICNTREGION3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_HICNTREGION0_HICNTREGION3, self).__init__(register,
            'HICNTREGION3', 'AGC_S.HICNTREGION0.HICNTREGION3', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_HICNTREGION1_HICNTREGION4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_HICNTREGION1_HICNTREGION4, self).__init__(register,
            'HICNTREGION4', 'AGC_S.HICNTREGION1.HICNTREGION4', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWN_STEPDWN0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWN_STEPDWN0, self).__init__(register,
            'STEPDWN0', 'AGC_S.STEPDWN.STEPDWN0', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWN_STEPDWN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWN_STEPDWN1, self).__init__(register,
            'STEPDWN1', 'AGC_S.STEPDWN.STEPDWN1', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWN_STEPDWN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWN_STEPDWN2, self).__init__(register,
            'STEPDWN2', 'AGC_S.STEPDWN.STEPDWN2', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWN_STEPDWN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWN_STEPDWN3, self).__init__(register,
            'STEPDWN3', 'AGC_S.STEPDWN.STEPDWN3', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWN_STEPDWN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWN_STEPDWN4, self).__init__(register,
            'STEPDWN4', 'AGC_S.STEPDWN.STEPDWN4', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWN_STEPDWN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWN_STEPDWN5, self).__init__(register,
            'STEPDWN5', 'AGC_S.STEPDWN.STEPDWN5', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINSTEPLIM0_CFLOOPSTEPMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINSTEPLIM0_CFLOOPSTEPMAX, self).__init__(register,
            'CFLOOPSTEPMAX', 'AGC_S.GAINSTEPLIM0.CFLOOPSTEPMAX', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINSTEPLIM0_CFLOOPDEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINSTEPLIM0_CFLOOPDEL, self).__init__(register,
            'CFLOOPDEL', 'AGC_S.GAINSTEPLIM0.CFLOOPDEL', 'read-write',
            u"",
            5, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINSTEPLIM0_HYST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINSTEPLIM0_HYST, self).__init__(register,
            'HYST', 'AGC_S.GAINSTEPLIM0.HYST', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINSTEPLIM0_MAXPWRVAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINSTEPLIM0_MAXPWRVAR, self).__init__(register,
            'MAXPWRVAR', 'AGC_S.GAINSTEPLIM0.MAXPWRVAR', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINSTEPLIM0_TRANRSTAGC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINSTEPLIM0_TRANRSTAGC, self).__init__(register,
            'TRANRSTAGC', 'AGC_S.GAINSTEPLIM0.TRANRSTAGC', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINSTEPLIM1_LNAINDEXMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINSTEPLIM1_LNAINDEXMAX, self).__init__(register,
            'LNAINDEXMAX', 'AGC_S.GAINSTEPLIM1.LNAINDEXMAX', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINSTEPLIM1_PGAINDEXMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINSTEPLIM1_PGAINDEXMAX, self).__init__(register,
            'PGAINDEXMAX', 'AGC_S.GAINSTEPLIM1.PGAINDEXMAX', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_GAINSTEPLIM1_PNINDEXMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_GAINSTEPLIM1_PNINDEXMAX, self).__init__(register,
            'PNINDEXMAX', 'AGC_S.GAINSTEPLIM1.PNINDEXMAX', 'read-write',
            u"",
            8, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT0_LNAMIXRFATT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT0_LNAMIXRFATT1, self).__init__(register,
            'LNAMIXRFATT1', 'AGC_S.PNRFATT0.LNAMIXRFATT1', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT0_LNAMIXRFATT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT0_LNAMIXRFATT2, self).__init__(register,
            'LNAMIXRFATT2', 'AGC_S.PNRFATT0.LNAMIXRFATT2', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT3, self).__init__(register,
            'LNAMIXRFATT3', 'AGC_S.PNRFATT1.LNAMIXRFATT3', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT4, self).__init__(register,
            'LNAMIXRFATT4', 'AGC_S.PNRFATT1.LNAMIXRFATT4', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT5, self).__init__(register,
            'LNAMIXRFATT5', 'AGC_S.PNRFATT2.LNAMIXRFATT5', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT6, self).__init__(register,
            'LNAMIXRFATT6', 'AGC_S.PNRFATT2.LNAMIXRFATT6', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT7, self).__init__(register,
            'LNAMIXRFATT7', 'AGC_S.PNRFATT3.LNAMIXRFATT7', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT8, self).__init__(register,
            'LNAMIXRFATT8', 'AGC_S.PNRFATT3.LNAMIXRFATT8', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT9, self).__init__(register,
            'LNAMIXRFATT9', 'AGC_S.PNRFATT4.LNAMIXRFATT9', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT10, self).__init__(register,
            'LNAMIXRFATT10', 'AGC_S.PNRFATT4.LNAMIXRFATT10', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT11, self).__init__(register,
            'LNAMIXRFATT11', 'AGC_S.PNRFATT5.LNAMIXRFATT11', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT12, self).__init__(register,
            'LNAMIXRFATT12', 'AGC_S.PNRFATT5.LNAMIXRFATT12', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT13, self).__init__(register,
            'LNAMIXRFATT13', 'AGC_S.PNRFATT6.LNAMIXRFATT13', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT14, self).__init__(register,
            'LNAMIXRFATT14', 'AGC_S.PNRFATT6.LNAMIXRFATT14', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT15, self).__init__(register,
            'LNAMIXRFATT15', 'AGC_S.PNRFATT7.LNAMIXRFATT15', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT16, self).__init__(register,
            'LNAMIXRFATT16', 'AGC_S.PNRFATT7.LNAMIXRFATT16', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT8_LNAMIXRFATT17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT8_LNAMIXRFATT17, self).__init__(register,
            'LNAMIXRFATT17', 'AGC_S.PNRFATT8.LNAMIXRFATT17', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT8_LNAMIXRFATT18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT8_LNAMIXRFATT18, self).__init__(register,
            'LNAMIXRFATT18', 'AGC_S.PNRFATT8.LNAMIXRFATT18', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT9_LNAMIXRFATT19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT9_LNAMIXRFATT19, self).__init__(register,
            'LNAMIXRFATT19', 'AGC_S.PNRFATT9.LNAMIXRFATT19', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT9_LNAMIXRFATT20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT9_LNAMIXRFATT20, self).__init__(register,
            'LNAMIXRFATT20', 'AGC_S.PNRFATT9.LNAMIXRFATT20', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT10_LNAMIXRFATT21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT10_LNAMIXRFATT21, self).__init__(register,
            'LNAMIXRFATT21', 'AGC_S.PNRFATT10.LNAMIXRFATT21', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT10_LNAMIXRFATT22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT10_LNAMIXRFATT22, self).__init__(register,
            'LNAMIXRFATT22', 'AGC_S.PNRFATT10.LNAMIXRFATT22', 'read-write',
            u"",
            16, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT11_LNAMIXRFATT23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT11_LNAMIXRFATT23, self).__init__(register,
            'LNAMIXRFATT23', 'AGC_S.PNRFATT11.LNAMIXRFATT23', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATTALT_LNAMIXRFATTALT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATTALT_LNAMIXRFATTALT, self).__init__(register,
            'LNAMIXRFATTALT', 'AGC_S.PNRFATTALT.LNAMIXRFATTALT', 'read-write',
            u"",
            0, 14)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE1, self).__init__(register,
            'LNAMIXSLICE1', 'AGC_S.LNAMIXCODE0.LNAMIXSLICE1', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE2, self).__init__(register,
            'LNAMIXSLICE2', 'AGC_S.LNAMIXCODE0.LNAMIXSLICE2', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE3, self).__init__(register,
            'LNAMIXSLICE3', 'AGC_S.LNAMIXCODE0.LNAMIXSLICE3', 'read-write',
            u"",
            12, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE4, self).__init__(register,
            'LNAMIXSLICE4', 'AGC_S.LNAMIXCODE0.LNAMIXSLICE4', 'read-write',
            u"",
            18, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE0_LNAMIXSLICE5, self).__init__(register,
            'LNAMIXSLICE5', 'AGC_S.LNAMIXCODE0.LNAMIXSLICE5', 'read-write',
            u"",
            24, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE6, self).__init__(register,
            'LNAMIXSLICE6', 'AGC_S.LNAMIXCODE1.LNAMIXSLICE6', 'read-write',
            u"",
            0, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE7, self).__init__(register,
            'LNAMIXSLICE7', 'AGC_S.LNAMIXCODE1.LNAMIXSLICE7', 'read-write',
            u"",
            6, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE8, self).__init__(register,
            'LNAMIXSLICE8', 'AGC_S.LNAMIXCODE1.LNAMIXSLICE8', 'read-write',
            u"",
            12, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE9, self).__init__(register,
            'LNAMIXSLICE9', 'AGC_S.LNAMIXCODE1.LNAMIXSLICE9', 'read-write',
            u"",
            18, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNAMIXCODE1_LNAMIXSLICE10, self).__init__(register,
            'LNAMIXSLICE10', 'AGC_S.LNAMIXCODE1.LNAMIXSLICE10', 'read-write',
            u"",
            24, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE0_PGAGAIN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE0_PGAGAIN1, self).__init__(register,
            'PGAGAIN1', 'AGC_S.PGACODE0.PGAGAIN1', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE0_PGAGAIN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE0_PGAGAIN2, self).__init__(register,
            'PGAGAIN2', 'AGC_S.PGACODE0.PGAGAIN2', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE0_PGAGAIN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE0_PGAGAIN3, self).__init__(register,
            'PGAGAIN3', 'AGC_S.PGACODE0.PGAGAIN3', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE0_PGAGAIN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE0_PGAGAIN4, self).__init__(register,
            'PGAGAIN4', 'AGC_S.PGACODE0.PGAGAIN4', 'read-write',
            u"",
            12, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE0_PGAGAIN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE0_PGAGAIN5, self).__init__(register,
            'PGAGAIN5', 'AGC_S.PGACODE0.PGAGAIN5', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE0_PGAGAIN6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE0_PGAGAIN6, self).__init__(register,
            'PGAGAIN6', 'AGC_S.PGACODE0.PGAGAIN6', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE0_PGAGAIN7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE0_PGAGAIN7, self).__init__(register,
            'PGAGAIN7', 'AGC_S.PGACODE0.PGAGAIN7', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE0_PGAGAIN8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE0_PGAGAIN8, self).__init__(register,
            'PGAGAIN8', 'AGC_S.PGACODE0.PGAGAIN8', 'read-write',
            u"",
            28, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE1_PGAGAIN9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE1_PGAGAIN9, self).__init__(register,
            'PGAGAIN9', 'AGC_S.PGACODE1.PGAGAIN9', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE1_PGAGAIN10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE1_PGAGAIN10, self).__init__(register,
            'PGAGAIN10', 'AGC_S.PGACODE1.PGAGAIN10', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PGACODE1_PGAGAIN11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PGACODE1_PGAGAIN11, self).__init__(register,
            'PGAGAIN11', 'AGC_S.PGACODE1.PGAGAIN11', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LBT_CCARSSIPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LBT_CCARSSIPERIOD, self).__init__(register,
            'CCARSSIPERIOD', 'AGC_S.LBT.CCARSSIPERIOD', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LBT_ENCCARSSIPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LBT_ENCCARSSIPERIOD, self).__init__(register,
            'ENCCARSSIPERIOD', 'AGC_S.LBT.ENCCARSSIPERIOD', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LBT_ENCCAGAINREDUCED(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LBT_ENCCAGAINREDUCED, self).__init__(register,
            'ENCCAGAINREDUCED', 'AGC_S.LBT.ENCCAGAINREDUCED', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LBT_ENCCARSSIMAX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LBT_ENCCARSSIMAX, self).__init__(register,
            'ENCCARSSIMAX', 'AGC_S.LBT.ENCCARSSIMAX', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MIRRORIF_RSSIPOSSTEPM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MIRRORIF_RSSIPOSSTEPM, self).__init__(register,
            'RSSIPOSSTEPM', 'AGC_S.MIRRORIF.RSSIPOSSTEPM', 'read-only',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MIRRORIF_RSSINEGSTEPM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MIRRORIF_RSSINEGSTEPM, self).__init__(register,
            'RSSINEGSTEPM', 'AGC_S.MIRRORIF.RSSINEGSTEPM', 'read-only',
            u"",
            1, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MIRRORIF_SHORTRSSIPOSSTEPM(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MIRRORIF_SHORTRSSIPOSSTEPM, self).__init__(register,
            'SHORTRSSIPOSSTEPM', 'AGC_S.MIRRORIF.SHORTRSSIPOSSTEPM', 'read-only',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_MIRRORIF_IFMIRRORCLEAR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_MIRRORIF_IFMIRRORCLEAR, self).__init__(register,
            'IFMIRRORCLEAR', 'AGC_S.MIRRORIF.IFMIRRORCLEAR', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_RSSIVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_RSSIVALID, self).__init__(register,
            'RSSIVALID', 'AGC_S.SEQIF.RSSIVALID', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_CCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_CCA, self).__init__(register,
            'CCA', 'AGC_S.SEQIF.CCA', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_RSSIPOSSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_RSSIPOSSTEP, self).__init__(register,
            'RSSIPOSSTEP', 'AGC_S.SEQIF.RSSIPOSSTEP', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_RSSINEGSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_RSSINEGSTEP, self).__init__(register,
            'RSSINEGSTEP', 'AGC_S.SEQIF.RSSINEGSTEP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_RSSIDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_RSSIDONE, self).__init__(register,
            'RSSIDONE', 'AGC_S.SEQIF.RSSIDONE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_SHORTRSSIPOSSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_SHORTRSSIPOSSTEP, self).__init__(register,
            'SHORTRSSIPOSSTEP', 'AGC_S.SEQIF.SHORTRSSIPOSSTEP', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_RFPKDPRDDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_RFPKDPRDDONE, self).__init__(register,
            'RFPKDPRDDONE', 'AGC_S.SEQIF.RFPKDPRDDONE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_RFPKDCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_RFPKDCNTDONE, self).__init__(register,
            'RFPKDCNTDONE', 'AGC_S.SEQIF.RFPKDCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_RSSIHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_RSSIHIGH, self).__init__(register,
            'RSSIHIGH', 'AGC_S.SEQIF.RSSIHIGH', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_RSSILOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_RSSILOW, self).__init__(register,
            'RSSILOW', 'AGC_S.SEQIF.RSSILOW', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_CCANODET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_CCANODET, self).__init__(register,
            'CCANODET', 'AGC_S.SEQIF.CCANODET', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_GAINBELOWGAINTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_GAINBELOWGAINTHD, self).__init__(register,
            'GAINBELOWGAINTHD', 'AGC_S.SEQIF.GAINBELOWGAINTHD', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_GAINUPDATEFRZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_GAINUPDATEFRZ, self).__init__(register,
            'GAINUPDATEFRZ', 'AGC_S.SEQIF.GAINUPDATEFRZ', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_PNATTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_PNATTEN, self).__init__(register,
            'PNATTEN', 'AGC_S.SEQIF.PNATTEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_COLLDETRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_COLLDETRSSIMAPRE, self).__init__(register,
            'COLLDETRSSIMAPRE', 'AGC_S.SEQIF.COLLDETRSSIMAPRE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIF_COLLDETRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIF_COLLDETRSSIMASYNC, self).__init__(register,
            'COLLDETRSSIMASYNC', 'AGC_S.SEQIF.COLLDETRSSIMASYNC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_RSSIVALID(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_RSSIVALID, self).__init__(register,
            'RSSIVALID', 'AGC_S.SEQIEN.RSSIVALID', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_CCA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_CCA, self).__init__(register,
            'CCA', 'AGC_S.SEQIEN.CCA', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_RSSIPOSSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_RSSIPOSSTEP, self).__init__(register,
            'RSSIPOSSTEP', 'AGC_S.SEQIEN.RSSIPOSSTEP', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_RSSINEGSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_RSSINEGSTEP, self).__init__(register,
            'RSSINEGSTEP', 'AGC_S.SEQIEN.RSSINEGSTEP', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_RSSIDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_RSSIDONE, self).__init__(register,
            'RSSIDONE', 'AGC_S.SEQIEN.RSSIDONE', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_SHORTRSSIPOSSTEP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_SHORTRSSIPOSSTEP, self).__init__(register,
            'SHORTRSSIPOSSTEP', 'AGC_S.SEQIEN.SHORTRSSIPOSSTEP', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_RFPKDPRDDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_RFPKDPRDDONE, self).__init__(register,
            'RFPKDPRDDONE', 'AGC_S.SEQIEN.RFPKDPRDDONE', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_RFPKDCNTDONE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_RFPKDCNTDONE, self).__init__(register,
            'RFPKDCNTDONE', 'AGC_S.SEQIEN.RFPKDCNTDONE', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_RSSIHIGH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_RSSIHIGH, self).__init__(register,
            'RSSIHIGH', 'AGC_S.SEQIEN.RSSIHIGH', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_RSSILOW(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_RSSILOW, self).__init__(register,
            'RSSILOW', 'AGC_S.SEQIEN.RSSILOW', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_CCANODET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_CCANODET, self).__init__(register,
            'CCANODET', 'AGC_S.SEQIEN.CCANODET', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_GAINBELOWGAINTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_GAINBELOWGAINTHD, self).__init__(register,
            'GAINBELOWGAINTHD', 'AGC_S.SEQIEN.GAINBELOWGAINTHD', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_GAINUPDATEFRZ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_GAINUPDATEFRZ, self).__init__(register,
            'GAINUPDATEFRZ', 'AGC_S.SEQIEN.GAINUPDATEFRZ', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_PNATTEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_PNATTEN, self).__init__(register,
            'PNATTEN', 'AGC_S.SEQIEN.PNATTEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_COLLDETRSSIMAPRE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_COLLDETRSSIMAPRE, self).__init__(register,
            'COLLDETRSSIMAPRE', 'AGC_S.SEQIEN.COLLDETRSSIMAPRE', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SEQIEN_COLLDETRSSIMASYNC(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SEQIEN_COLLDETRSSIMASYNC, self).__init__(register,
            'COLLDETRSSIMASYNC', 'AGC_S.SEQIEN.COLLDETRSSIMASYNC', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSIABSTHR_RSSIHIGHTHRSH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSIABSTHR_RSSIHIGHTHRSH, self).__init__(register,
            'RSSIHIGHTHRSH', 'AGC_S.RSSIABSTHR.RSSIHIGHTHRSH', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSIABSTHR_RSSILOWTHRSH(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSIABSTHR_RSSILOWTHRSH, self).__init__(register,
            'RSSILOWTHRSH', 'AGC_S.RSSIABSTHR.RSSILOWTHRSH', 'read-write',
            u"",
            8, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSIABSTHR_SIRSSIHIGHTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSIABSTHR_SIRSSIHIGHTHR, self).__init__(register,
            'SIRSSIHIGHTHR', 'AGC_S.RSSIABSTHR.SIRSSIHIGHTHR', 'read-write',
            u"",
            16, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_RSSIABSTHR_SIRSSINEGSTEPTHR(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_RSSIABSTHR_SIRSSINEGSTEPTHR, self).__init__(register,
            'SIRSSINEGSTEPTHR', 'AGC_S.RSSIABSTHR.SIRSSINEGSTEPTHR', 'read-write',
            u"",
            24, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNABOOST_BOOSTLNA(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNABOOST_BOOSTLNA, self).__init__(register,
            'BOOSTLNA', 'AGC_S.LNABOOST.BOOSTLNA', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNABOOST_LNABWADJ(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNABOOST_LNABWADJ, self).__init__(register,
            'LNABWADJ', 'AGC_S.LNABOOST.LNABWADJ', 'read-write',
            u"",
            1, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNABOOST_LNABWADJBOOST(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNABOOST_LNABWADJBOOST, self).__init__(register,
            'LNABWADJBOOST', 'AGC_S.LNABOOST.LNABWADJBOOST', 'read-write',
            u"",
            5, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_LNABOOST_LNABOOSTGAIN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_LNABOOST_LNABOOSTGAIN, self).__init__(register,
            'LNABOOSTGAIN', 'AGC_S.LNABOOST.LNABOOSTGAIN', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_ANTDIV_GAINMODE(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_ANTDIV_GAINMODE, self).__init__(register,
            'GAINMODE', 'AGC_S.ANTDIV.GAINMODE', 'read-write',
            u"",
            0, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_ANTDIV_DEBOUNCECNTTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_ANTDIV_DEBOUNCECNTTHD, self).__init__(register,
            'DEBOUNCECNTTHD', 'AGC_S.ANTDIV.DEBOUNCECNTTHD', 'read-write',
            u"",
            2, 7)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_ANTDIV_DISRSSIANTDIVFIX(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_ANTDIV_DISRSSIANTDIVFIX, self).__init__(register,
            'DISRSSIANTDIVFIX', 'AGC_S.ANTDIV.DISRSSIANTDIVFIX', 'read-write',
            u"",
            9, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_DUALRFPKDTHD0_RFPKDLOWTHD0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_DUALRFPKDTHD0_RFPKDLOWTHD0, self).__init__(register,
            'RFPKDLOWTHD0', 'AGC_S.DUALRFPKDTHD0.RFPKDLOWTHD0', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_DUALRFPKDTHD0_RFPKDLOWTHD1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_DUALRFPKDTHD0_RFPKDLOWTHD1, self).__init__(register,
            'RFPKDLOWTHD1', 'AGC_S.DUALRFPKDTHD0.RFPKDLOWTHD1', 'read-write',
            u"",
            16, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_DUALRFPKDTHD1_RFPKDHITHD0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_DUALRFPKDTHD1_RFPKDHITHD0, self).__init__(register,
            'RFPKDHITHD0', 'AGC_S.DUALRFPKDTHD1.RFPKDHITHD0', 'read-write',
            u"",
            0, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_DUALRFPKDTHD1_RFPKDHITHD1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_DUALRFPKDTHD1_RFPKDHITHD1, self).__init__(register,
            'RFPKDHITHD1', 'AGC_S.DUALRFPKDTHD1.RFPKDHITHD1', 'read-write',
            u"",
            16, 12)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SPARE_SPAREREG(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SPARE_SPAREREG, self).__init__(register,
            'SPAREREG', 'AGC_S.SPARE.SPAREREG', 'read-write',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FLARE_PNATTENTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FLARE_PNATTENTHD, self).__init__(register,
            'PNATTENTHD', 'AGC_S.FLARE.PNATTENTHD', 'read-write',
            u"",
            0, 5)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE0(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE0, self).__init__(register,
            'STEPDWNSAFE0', 'AGC_S.STEPDWNSAFE.STEPDWNSAFE0', 'read-write',
            u"",
            0, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE1, self).__init__(register,
            'STEPDWNSAFE1', 'AGC_S.STEPDWNSAFE.STEPDWNSAFE1', 'read-write',
            u"",
            3, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE2, self).__init__(register,
            'STEPDWNSAFE2', 'AGC_S.STEPDWNSAFE.STEPDWNSAFE2', 'read-write',
            u"",
            6, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE3, self).__init__(register,
            'STEPDWNSAFE3', 'AGC_S.STEPDWNSAFE.STEPDWNSAFE3', 'read-write',
            u"",
            9, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE4, self).__init__(register,
            'STEPDWNSAFE4', 'AGC_S.STEPDWNSAFE.STEPDWNSAFE4', 'read-write',
            u"",
            12, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFE5, self).__init__(register,
            'STEPDWNSAFE5', 'AGC_S.STEPDWNSAFE.STEPDWNSAFE5', 'read-write',
            u"",
            15, 3)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFEEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_STEPDWNSAFE_STEPDWNSAFEEN, self).__init__(register,
            'STEPDWNSAFEEN', 'AGC_S.STEPDWNSAFE.STEPDWNSAFEEN', 'read-write',
            u"",
            18, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CCADEBUG_DEBUGCCARSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CCADEBUG_DEBUGCCARSSI, self).__init__(register,
            'DEBUGCCARSSI', 'AGC_S.CCADEBUG.DEBUGCCARSSI', 'read-only',
            u"",
            0, 8)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CCADEBUG_DEBUGCCAM1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CCADEBUG_DEBUGCCAM1, self).__init__(register,
            'DEBUGCCAM1', 'AGC_S.CCADEBUG.DEBUGCCAM1', 'read-only',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_CCADEBUG_DEBUGCCASIGDET(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CCADEBUG_DEBUGCCASIGDET, self).__init__(register,
            'DEBUGCCASIGDET', 'AGC_S.CCADEBUG.DEBUGCCASIGDET', 'read-only',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_UPONMARSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_UPONMARSSI, self).__init__(register,
            'UPONMARSSI', 'AGC_S.COLLDETCTRL.UPONMARSSI', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_INPUTSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_INPUTSEL, self).__init__(register,
            'INPUTSEL', 'AGC_S.COLLDETCTRL.INPUTSEL', 'read-write',
            u"",
            1, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_RSSIINSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_RSSIINSEL, self).__init__(register,
            'RSSIINSEL', 'AGC_S.COLLDETCTRL.RSSIINSEL', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_OVRTHDSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_OVRTHDSEL, self).__init__(register,
            'OVRTHDSEL', 'AGC_S.COLLDETCTRL.OVRTHDSEL', 'read-write',
            u"",
            7, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_MALATCHSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_MALATCHSEL, self).__init__(register,
            'MALATCHSEL', 'AGC_S.COLLDETCTRL.MALATCHSEL', 'read-write',
            u"",
            8, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_MACOMPENSEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_MACOMPENSEL, self).__init__(register,
            'MACOMPENSEL', 'AGC_S.COLLDETCTRL.MACOMPENSEL', 'read-write',
            u"",
            10, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_MATAP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_MATAP, self).__init__(register,
            'MATAP', 'AGC_S.COLLDETCTRL.MATAP', 'read-write',
            u"",
            12, 2)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_FLTBYP(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_FLTBYP, self).__init__(register,
            'FLTBYP', 'AGC_S.COLLDETCTRL.FLTBYP', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_LATCHRSSIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_LATCHRSSIEN, self).__init__(register,
            'LATCHRSSIEN', 'AGC_S.COLLDETCTRL.LATCHRSSIEN', 'read-write',
            u"",
            24, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETCTRL_LATCHRSSI(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETCTRL_LATCHRSSI, self).__init__(register,
            'LATCHRSSI', 'AGC_S.COLLDETCTRL.LATCHRSSI', 'read-write',
            u"",
            25, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETTHD_MATHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETTHD_MATHRESHOLD, self).__init__(register,
            'MATHRESHOLD', 'AGC_S.COLLDETTHD.MATHRESHOLD', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETTHD_MINTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETTHD_MINTHRESHOLD, self).__init__(register,
            'MINTHRESHOLD', 'AGC_S.COLLDETTHD.MINTHRESHOLD', 'read-write',
            u"",
            8, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETTHD_OVRTHRESHOLD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETTHD_OVRTHRESHOLD, self).__init__(register,
            'OVRTHRESHOLD', 'AGC_S.COLLDETTHD.OVRTHRESHOLD', 'read-write',
            u"",
            18, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_COLLDETSTATUS_MAFLTDOUT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_COLLDETSTATUS_MAFLTDOUT, self).__init__(register,
            'MAFLTDOUT', 'AGC_S.COLLDETSTATUS.MAFLTDOUT', 'read-only',
            u"",
            0, 9)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SETTLINGINDCTRL_EN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SETTLINGINDCTRL_EN, self).__init__(register,
            'EN', 'AGC_S.SETTLINGINDCTRL.EN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SETTLINGINDCTRL_POSTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SETTLINGINDCTRL_POSTHD, self).__init__(register,
            'POSTHD', 'AGC_S.SETTLINGINDCTRL.POSTHD', 'read-write',
            u"",
            8, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SETTLINGINDCTRL_NEGTHD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SETTLINGINDCTRL_NEGTHD, self).__init__(register,
            'NEGTHD', 'AGC_S.SETTLINGINDCTRL.NEGTHD', 'read-write',
            u"",
            16, 6)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SETTLINGINDPER_SETTLEDPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SETTLINGINDPER_SETTLEDPERIOD, self).__init__(register,
            'SETTLEDPERIOD', 'AGC_S.SETTLINGINDPER.SETTLEDPERIOD', 'read-write',
            u"",
            0, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SETTLINGINDPER_DELAYPERIOD(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SETTLINGINDPER_DELAYPERIOD, self).__init__(register,
            'DELAYPERIOD', 'AGC_S.SETTLINGINDPER.DELAYPERIOD', 'read-write',
            u"",
            16, 16)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_RSSIVALIDSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_RSSIVALIDSFMIF, self).__init__(register,
            'RSSIVALIDSFMIF', 'AGC_S.SMFIF.RSSIVALIDSFMIF', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_CCASFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_CCASFMIF, self).__init__(register,
            'CCASFMIF', 'AGC_S.SMFIF.CCASFMIF', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_RSSIPOSSTEPSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_RSSIPOSSTEPSFMIF, self).__init__(register,
            'RSSIPOSSTEPSFMIF', 'AGC_S.SMFIF.RSSIPOSSTEPSFMIF', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_RSSINEGSTEPSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_RSSINEGSTEPSFMIF, self).__init__(register,
            'RSSINEGSTEPSFMIF', 'AGC_S.SMFIF.RSSINEGSTEPSFMIF', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_RSSIDONESFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_RSSIDONESFMIF, self).__init__(register,
            'RSSIDONESFMIF', 'AGC_S.SMFIF.RSSIDONESFMIF', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_SHORTRSSIPOSSTEPSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_SHORTRSSIPOSSTEPSFMIF, self).__init__(register,
            'SHORTRSSIPOSSTEPSFMIF', 'AGC_S.SMFIF.SHORTRSSIPOSSTEPSFMIF', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_RFPKDPRDDONESFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_RFPKDPRDDONESFMIF, self).__init__(register,
            'RFPKDPRDDONESFMIF', 'AGC_S.SMFIF.RFPKDPRDDONESFMIF', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_RFPKDCNTDONESFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_RFPKDCNTDONESFMIF, self).__init__(register,
            'RFPKDCNTDONESFMIF', 'AGC_S.SMFIF.RFPKDCNTDONESFMIF', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_RSSIHIGHSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_RSSIHIGHSFMIF, self).__init__(register,
            'RSSIHIGHSFMIF', 'AGC_S.SMFIF.RSSIHIGHSFMIF', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_RSSILOWSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_RSSILOWSFMIF, self).__init__(register,
            'RSSILOWSFMIF', 'AGC_S.SMFIF.RSSILOWSFMIF', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_CCANODETSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_CCANODETSFMIF, self).__init__(register,
            'CCANODETSFMIF', 'AGC_S.SMFIF.CCANODETSFMIF', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_GAINBELOWGAINTHDSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_GAINBELOWGAINTHDSFMIF, self).__init__(register,
            'GAINBELOWGAINTHDSFMIF', 'AGC_S.SMFIF.GAINBELOWGAINTHDSFMIF', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_GAINUPDATEFRZSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_GAINUPDATEFRZSFMIF, self).__init__(register,
            'GAINUPDATEFRZSFMIF', 'AGC_S.SMFIF.GAINUPDATEFRZSFMIF', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_PNATTENSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_PNATTENSFMIF, self).__init__(register,
            'PNATTENSFMIF', 'AGC_S.SMFIF.PNATTENSFMIF', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_COLLDETRSSIMAPRESFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_COLLDETRSSIMAPRESFMIF, self).__init__(register,
            'COLLDETRSSIMAPRESFMIF', 'AGC_S.SMFIF.COLLDETRSSIMAPRESFMIF', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SMFIF_COLLDETRSSIMASYNCSFMIF(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SMFIF_COLLDETRSSIMASYNCSFMIF, self).__init__(register,
            'COLLDETRSSIMASYNCSFMIF', 'AGC_S.SMFIF.COLLDETRSSIMASYNCSFMIF', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_RSSIVALIDSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_RSSIVALIDSFMIEN, self).__init__(register,
            'RSSIVALIDSFMIEN', 'AGC_S.SFMIEN.RSSIVALIDSFMIEN', 'read-write',
            u"",
            0, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_CCASFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_CCASFMIEN, self).__init__(register,
            'CCASFMIEN', 'AGC_S.SFMIEN.CCASFMIEN', 'read-write',
            u"",
            2, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_RSSIPOSSTEPSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_RSSIPOSSTEPSFMIEN, self).__init__(register,
            'RSSIPOSSTEPSFMIEN', 'AGC_S.SFMIEN.RSSIPOSSTEPSFMIEN', 'read-write',
            u"",
            3, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_RSSINEGSTEPSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_RSSINEGSTEPSFMIEN, self).__init__(register,
            'RSSINEGSTEPSFMIEN', 'AGC_S.SFMIEN.RSSINEGSTEPSFMIEN', 'read-write',
            u"",
            4, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_RSSIDONESFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_RSSIDONESFMIEN, self).__init__(register,
            'RSSIDONESFMIEN', 'AGC_S.SFMIEN.RSSIDONESFMIEN', 'read-write',
            u"",
            5, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_SHORTRSSIPOSSTEPSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_SHORTRSSIPOSSTEPSFMIEN, self).__init__(register,
            'SHORTRSSIPOSSTEPSFMIEN', 'AGC_S.SFMIEN.SHORTRSSIPOSSTEPSFMIEN', 'read-write',
            u"",
            6, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_RFPKDPRDDONESFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_RFPKDPRDDONESFMIEN, self).__init__(register,
            'RFPKDPRDDONESFMIEN', 'AGC_S.SFMIEN.RFPKDPRDDONESFMIEN', 'read-write',
            u"",
            8, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_RFPKDCNTDONESFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_RFPKDCNTDONESFMIEN, self).__init__(register,
            'RFPKDCNTDONESFMIEN', 'AGC_S.SFMIEN.RFPKDCNTDONESFMIEN', 'read-write',
            u"",
            9, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_RSSIHIGHSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_RSSIHIGHSFMIEN, self).__init__(register,
            'RSSIHIGHSFMIEN', 'AGC_S.SFMIEN.RSSIHIGHSFMIEN', 'read-write',
            u"",
            10, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_RSSILOWSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_RSSILOWSFMIEN, self).__init__(register,
            'RSSILOWSFMIEN', 'AGC_S.SFMIEN.RSSILOWSFMIEN', 'read-write',
            u"",
            11, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_CCANODETSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_CCANODETSFMIEN, self).__init__(register,
            'CCANODETSFMIEN', 'AGC_S.SFMIEN.CCANODETSFMIEN', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_GAINBELOWGAINTHDSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_GAINBELOWGAINTHDSFMIEN, self).__init__(register,
            'GAINBELOWGAINTHDSFMIEN', 'AGC_S.SFMIEN.GAINBELOWGAINTHDSFMIEN', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_GAINUPDATEFRZSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_GAINUPDATEFRZSFMIEN, self).__init__(register,
            'GAINUPDATEFRZSFMIEN', 'AGC_S.SFMIEN.GAINUPDATEFRZSFMIEN', 'read-write',
            u"",
            14, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_PNATTENSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_PNATTENSFMIEN, self).__init__(register,
            'PNATTENSFMIEN', 'AGC_S.SFMIEN.PNATTENSFMIEN', 'read-write',
            u"",
            15, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_COLLDETRSSIMAPRESFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_COLLDETRSSIMAPRESFMIEN, self).__init__(register,
            'COLLDETRSSIMAPRESFMIEN', 'AGC_S.SFMIEN.COLLDETRSSIMAPRESFMIEN', 'read-write',
            u"",
            16, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_SFMIEN_COLLDETRSSIMASYNCSFMIEN(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_SFMIEN_COLLDETRSSIMASYNCSFMIEN, self).__init__(register,
            'COLLDETRSSIMASYNCSFMIEN', 'AGC_S.SFMIEN.COLLDETRSSIMASYNCSFMIEN', 'read-write',
            u"",
            17, 1)
        self.__dict__['zz_frozen'] = True



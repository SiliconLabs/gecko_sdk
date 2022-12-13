
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


class RM_Field_AGC_S_CTRL0_FENOTCHMODESEL(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_CTRL0_FENOTCHMODESEL, self).__init__(register,
            'FENOTCHMODESEL', 'AGC_S.CTRL0.FENOTCHMODESEL', 'read-write',
            u"",
            24, 1)
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
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT0_LNAMIXRFATT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT0_LNAMIXRFATT2, self).__init__(register,
            'LNAMIXRFATT2', 'AGC_S.PNRFATT0.LNAMIXRFATT2', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT0_LNAMIXRFATT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT0_LNAMIXRFATT3, self).__init__(register,
            'LNAMIXRFATT3', 'AGC_S.PNRFATT0.LNAMIXRFATT3', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT4, self).__init__(register,
            'LNAMIXRFATT4', 'AGC_S.PNRFATT1.LNAMIXRFATT4', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT5, self).__init__(register,
            'LNAMIXRFATT5', 'AGC_S.PNRFATT1.LNAMIXRFATT5', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT1_LNAMIXRFATT6, self).__init__(register,
            'LNAMIXRFATT6', 'AGC_S.PNRFATT1.LNAMIXRFATT6', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT7, self).__init__(register,
            'LNAMIXRFATT7', 'AGC_S.PNRFATT2.LNAMIXRFATT7', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT8, self).__init__(register,
            'LNAMIXRFATT8', 'AGC_S.PNRFATT2.LNAMIXRFATT8', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT2_LNAMIXRFATT9, self).__init__(register,
            'LNAMIXRFATT9', 'AGC_S.PNRFATT2.LNAMIXRFATT9', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT10, self).__init__(register,
            'LNAMIXRFATT10', 'AGC_S.PNRFATT3.LNAMIXRFATT10', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT11, self).__init__(register,
            'LNAMIXRFATT11', 'AGC_S.PNRFATT3.LNAMIXRFATT11', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT3_LNAMIXRFATT12, self).__init__(register,
            'LNAMIXRFATT12', 'AGC_S.PNRFATT3.LNAMIXRFATT12', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT13, self).__init__(register,
            'LNAMIXRFATT13', 'AGC_S.PNRFATT4.LNAMIXRFATT13', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT14, self).__init__(register,
            'LNAMIXRFATT14', 'AGC_S.PNRFATT4.LNAMIXRFATT14', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT4_LNAMIXRFATT15, self).__init__(register,
            'LNAMIXRFATT15', 'AGC_S.PNRFATT4.LNAMIXRFATT15', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT16, self).__init__(register,
            'LNAMIXRFATT16', 'AGC_S.PNRFATT5.LNAMIXRFATT16', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT17, self).__init__(register,
            'LNAMIXRFATT17', 'AGC_S.PNRFATT5.LNAMIXRFATT17', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT5_LNAMIXRFATT18, self).__init__(register,
            'LNAMIXRFATT18', 'AGC_S.PNRFATT5.LNAMIXRFATT18', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT19, self).__init__(register,
            'LNAMIXRFATT19', 'AGC_S.PNRFATT6.LNAMIXRFATT19', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT20, self).__init__(register,
            'LNAMIXRFATT20', 'AGC_S.PNRFATT6.LNAMIXRFATT20', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT6_LNAMIXRFATT21, self).__init__(register,
            'LNAMIXRFATT21', 'AGC_S.PNRFATT6.LNAMIXRFATT21', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT22, self).__init__(register,
            'LNAMIXRFATT22', 'AGC_S.PNRFATT7.LNAMIXRFATT22', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT23, self).__init__(register,
            'LNAMIXRFATT23', 'AGC_S.PNRFATT7.LNAMIXRFATT23', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATT7_LNAMIXRFATT24, self).__init__(register,
            'LNAMIXRFATT24', 'AGC_S.PNRFATT7.LNAMIXRFATT24', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFATTALT_LNAMIXRFATTALT(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFATTALT_LNAMIXRFATTALT, self).__init__(register,
            'LNAMIXRFATTALT', 'AGC_S.PNRFATTALT.LNAMIXRFATTALT', 'read-write',
            u"",
            0, 10)
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


class RM_Field_AGC_S_PNRFFILT0_LNAMIXRFATT1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT0_LNAMIXRFATT1, self).__init__(register,
            'LNAMIXRFATT1', 'AGC_S.PNRFFILT0.LNAMIXRFATT1', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT0_LNAMIXRFATT2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT0_LNAMIXRFATT2, self).__init__(register,
            'LNAMIXRFATT2', 'AGC_S.PNRFFILT0.LNAMIXRFATT2', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT0_LNAMIXRFATT3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT0_LNAMIXRFATT3, self).__init__(register,
            'LNAMIXRFATT3', 'AGC_S.PNRFFILT0.LNAMIXRFATT3', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT1_LNAMIXRFATT4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT1_LNAMIXRFATT4, self).__init__(register,
            'LNAMIXRFATT4', 'AGC_S.PNRFFILT1.LNAMIXRFATT4', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT1_LNAMIXRFATT5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT1_LNAMIXRFATT5, self).__init__(register,
            'LNAMIXRFATT5', 'AGC_S.PNRFFILT1.LNAMIXRFATT5', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT1_LNAMIXRFATT6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT1_LNAMIXRFATT6, self).__init__(register,
            'LNAMIXRFATT6', 'AGC_S.PNRFFILT1.LNAMIXRFATT6', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT2_LNAMIXRFATT7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT2_LNAMIXRFATT7, self).__init__(register,
            'LNAMIXRFATT7', 'AGC_S.PNRFFILT2.LNAMIXRFATT7', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT2_LNAMIXRFATT8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT2_LNAMIXRFATT8, self).__init__(register,
            'LNAMIXRFATT8', 'AGC_S.PNRFFILT2.LNAMIXRFATT8', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT2_LNAMIXRFATT9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT2_LNAMIXRFATT9, self).__init__(register,
            'LNAMIXRFATT9', 'AGC_S.PNRFFILT2.LNAMIXRFATT9', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT3_LNAMIXRFATT10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT3_LNAMIXRFATT10, self).__init__(register,
            'LNAMIXRFATT10', 'AGC_S.PNRFFILT3.LNAMIXRFATT10', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT3_LNAMIXRFATT11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT3_LNAMIXRFATT11, self).__init__(register,
            'LNAMIXRFATT11', 'AGC_S.PNRFFILT3.LNAMIXRFATT11', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT3_LNAMIXRFATT12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT3_LNAMIXRFATT12, self).__init__(register,
            'LNAMIXRFATT12', 'AGC_S.PNRFFILT3.LNAMIXRFATT12', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT4_LNAMIXRFATT13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT4_LNAMIXRFATT13, self).__init__(register,
            'LNAMIXRFATT13', 'AGC_S.PNRFFILT4.LNAMIXRFATT13', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT4_LNAMIXRFATT14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT4_LNAMIXRFATT14, self).__init__(register,
            'LNAMIXRFATT14', 'AGC_S.PNRFFILT4.LNAMIXRFATT14', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT4_LNAMIXRFATT15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT4_LNAMIXRFATT15, self).__init__(register,
            'LNAMIXRFATT15', 'AGC_S.PNRFFILT4.LNAMIXRFATT15', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT5_LNAMIXRFATT16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT5_LNAMIXRFATT16, self).__init__(register,
            'LNAMIXRFATT16', 'AGC_S.PNRFFILT5.LNAMIXRFATT16', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT5_LNAMIXRFATT17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT5_LNAMIXRFATT17, self).__init__(register,
            'LNAMIXRFATT17', 'AGC_S.PNRFFILT5.LNAMIXRFATT17', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT5_LNAMIXRFATT18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT5_LNAMIXRFATT18, self).__init__(register,
            'LNAMIXRFATT18', 'AGC_S.PNRFFILT5.LNAMIXRFATT18', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT6_LNAMIXRFATT19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT6_LNAMIXRFATT19, self).__init__(register,
            'LNAMIXRFATT19', 'AGC_S.PNRFFILT6.LNAMIXRFATT19', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT6_LNAMIXRFATT20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT6_LNAMIXRFATT20, self).__init__(register,
            'LNAMIXRFATT20', 'AGC_S.PNRFFILT6.LNAMIXRFATT20', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT6_LNAMIXRFATT21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT6_LNAMIXRFATT21, self).__init__(register,
            'LNAMIXRFATT21', 'AGC_S.PNRFFILT6.LNAMIXRFATT21', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT7_LNAMIXRFATT22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT7_LNAMIXRFATT22, self).__init__(register,
            'LNAMIXRFATT22', 'AGC_S.PNRFFILT7.LNAMIXRFATT22', 'read-write',
            u"",
            0, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT7_LNAMIXRFATT23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT7_LNAMIXRFATT23, self).__init__(register,
            'LNAMIXRFATT23', 'AGC_S.PNRFFILT7.LNAMIXRFATT23', 'read-write',
            u"",
            10, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_PNRFFILT7_LNAMIXRFATT24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_PNRFFILT7_LNAMIXRFATT24, self).__init__(register,
            'LNAMIXRFATT24', 'AGC_S.PNRFFILT7.LNAMIXRFATT24', 'read-write',
            u"",
            20, 10)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHATTNSEL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHATTNSEL1, self).__init__(register,
            'FENOTCHATTNSEL1', 'AGC_S.FENOTCHATT0.FENOTCHATTNSEL1', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHCAPCRSE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHCAPCRSE1, self).__init__(register,
            'FENOTCHCAPCRSE1', 'AGC_S.FENOTCHATT0.FENOTCHCAPCRSE1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHCAPFINE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHCAPFINE1, self).__init__(register,
            'FENOTCHCAPFINE1', 'AGC_S.FENOTCHATT0.FENOTCHCAPFINE1', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHRATTNEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHRATTNEN1, self).__init__(register,
            'FENOTCHRATTNEN1', 'AGC_S.FENOTCHATT0.FENOTCHRATTNEN1', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHEN1, self).__init__(register,
            'FENOTCHEN1', 'AGC_S.FENOTCHATT0.FENOTCHEN1', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHATTNSEL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHATTNSEL2, self).__init__(register,
            'FENOTCHATTNSEL2', 'AGC_S.FENOTCHATT0.FENOTCHATTNSEL2', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHCAPCRSE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHCAPCRSE2, self).__init__(register,
            'FENOTCHCAPCRSE2', 'AGC_S.FENOTCHATT0.FENOTCHCAPCRSE2', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHCAPFINE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHCAPFINE2, self).__init__(register,
            'FENOTCHCAPFINE2', 'AGC_S.FENOTCHATT0.FENOTCHCAPFINE2', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHRATTNEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHRATTNEN2, self).__init__(register,
            'FENOTCHRATTNEN2', 'AGC_S.FENOTCHATT0.FENOTCHRATTNEN2', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT0_FENOTCHEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT0_FENOTCHEN2, self).__init__(register,
            'FENOTCHEN2', 'AGC_S.FENOTCHATT0.FENOTCHEN2', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHATTNSEL3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHATTNSEL3, self).__init__(register,
            'FENOTCHATTNSEL3', 'AGC_S.FENOTCHATT1.FENOTCHATTNSEL3', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHCAPCRSE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHCAPCRSE3, self).__init__(register,
            'FENOTCHCAPCRSE3', 'AGC_S.FENOTCHATT1.FENOTCHCAPCRSE3', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHCAPFINE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHCAPFINE3, self).__init__(register,
            'FENOTCHCAPFINE3', 'AGC_S.FENOTCHATT1.FENOTCHCAPFINE3', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHRATTNEN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHRATTNEN3, self).__init__(register,
            'FENOTCHRATTNEN3', 'AGC_S.FENOTCHATT1.FENOTCHRATTNEN3', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHEN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHEN3, self).__init__(register,
            'FENOTCHEN3', 'AGC_S.FENOTCHATT1.FENOTCHEN3', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHATTNSEL4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHATTNSEL4, self).__init__(register,
            'FENOTCHATTNSEL4', 'AGC_S.FENOTCHATT1.FENOTCHATTNSEL4', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHCAPCRSE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHCAPCRSE4, self).__init__(register,
            'FENOTCHCAPCRSE4', 'AGC_S.FENOTCHATT1.FENOTCHCAPCRSE4', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHCAPFINE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHCAPFINE4, self).__init__(register,
            'FENOTCHCAPFINE4', 'AGC_S.FENOTCHATT1.FENOTCHCAPFINE4', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHRATTNEN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHRATTNEN4, self).__init__(register,
            'FENOTCHRATTNEN4', 'AGC_S.FENOTCHATT1.FENOTCHRATTNEN4', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT1_FENOTCHEN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT1_FENOTCHEN4, self).__init__(register,
            'FENOTCHEN4', 'AGC_S.FENOTCHATT1.FENOTCHEN4', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHATTNSEL5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHATTNSEL5, self).__init__(register,
            'FENOTCHATTNSEL5', 'AGC_S.FENOTCHATT2.FENOTCHATTNSEL5', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHCAPCRSE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHCAPCRSE5, self).__init__(register,
            'FENOTCHCAPCRSE5', 'AGC_S.FENOTCHATT2.FENOTCHCAPCRSE5', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHCAPFINE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHCAPFINE5, self).__init__(register,
            'FENOTCHCAPFINE5', 'AGC_S.FENOTCHATT2.FENOTCHCAPFINE5', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHRATTNEN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHRATTNEN5, self).__init__(register,
            'FENOTCHRATTNEN5', 'AGC_S.FENOTCHATT2.FENOTCHRATTNEN5', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHEN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHEN5, self).__init__(register,
            'FENOTCHEN5', 'AGC_S.FENOTCHATT2.FENOTCHEN5', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHATTNSEL6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHATTNSEL6, self).__init__(register,
            'FENOTCHATTNSEL6', 'AGC_S.FENOTCHATT2.FENOTCHATTNSEL6', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHCAPCRSE6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHCAPCRSE6, self).__init__(register,
            'FENOTCHCAPCRSE6', 'AGC_S.FENOTCHATT2.FENOTCHCAPCRSE6', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHCAPFINE6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHCAPFINE6, self).__init__(register,
            'FENOTCHCAPFINE6', 'AGC_S.FENOTCHATT2.FENOTCHCAPFINE6', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHRATTNEN6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHRATTNEN6, self).__init__(register,
            'FENOTCHRATTNEN6', 'AGC_S.FENOTCHATT2.FENOTCHRATTNEN6', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT2_FENOTCHEN6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT2_FENOTCHEN6, self).__init__(register,
            'FENOTCHEN6', 'AGC_S.FENOTCHATT2.FENOTCHEN6', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHATTNSEL7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHATTNSEL7, self).__init__(register,
            'FENOTCHATTNSEL7', 'AGC_S.FENOTCHATT3.FENOTCHATTNSEL7', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHCAPCRSE7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHCAPCRSE7, self).__init__(register,
            'FENOTCHCAPCRSE7', 'AGC_S.FENOTCHATT3.FENOTCHCAPCRSE7', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHCAPFINE7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHCAPFINE7, self).__init__(register,
            'FENOTCHCAPFINE7', 'AGC_S.FENOTCHATT3.FENOTCHCAPFINE7', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHRATTNEN7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHRATTNEN7, self).__init__(register,
            'FENOTCHRATTNEN7', 'AGC_S.FENOTCHATT3.FENOTCHRATTNEN7', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHEN7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHEN7, self).__init__(register,
            'FENOTCHEN7', 'AGC_S.FENOTCHATT3.FENOTCHEN7', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHATTNSEL8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHATTNSEL8, self).__init__(register,
            'FENOTCHATTNSEL8', 'AGC_S.FENOTCHATT3.FENOTCHATTNSEL8', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHCAPCRSE8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHCAPCRSE8, self).__init__(register,
            'FENOTCHCAPCRSE8', 'AGC_S.FENOTCHATT3.FENOTCHCAPCRSE8', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHCAPFINE8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHCAPFINE8, self).__init__(register,
            'FENOTCHCAPFINE8', 'AGC_S.FENOTCHATT3.FENOTCHCAPFINE8', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHRATTNEN8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHRATTNEN8, self).__init__(register,
            'FENOTCHRATTNEN8', 'AGC_S.FENOTCHATT3.FENOTCHRATTNEN8', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT3_FENOTCHEN8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT3_FENOTCHEN8, self).__init__(register,
            'FENOTCHEN8', 'AGC_S.FENOTCHATT3.FENOTCHEN8', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHATTNSEL9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHATTNSEL9, self).__init__(register,
            'FENOTCHATTNSEL9', 'AGC_S.FENOTCHATT4.FENOTCHATTNSEL9', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHCAPCRSE9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHCAPCRSE9, self).__init__(register,
            'FENOTCHCAPCRSE9', 'AGC_S.FENOTCHATT4.FENOTCHCAPCRSE9', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHCAPFINE9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHCAPFINE9, self).__init__(register,
            'FENOTCHCAPFINE9', 'AGC_S.FENOTCHATT4.FENOTCHCAPFINE9', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHRATTNEN9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHRATTNEN9, self).__init__(register,
            'FENOTCHRATTNEN9', 'AGC_S.FENOTCHATT4.FENOTCHRATTNEN9', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHEN9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHEN9, self).__init__(register,
            'FENOTCHEN9', 'AGC_S.FENOTCHATT4.FENOTCHEN9', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHATTNSEL10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHATTNSEL10, self).__init__(register,
            'FENOTCHATTNSEL10', 'AGC_S.FENOTCHATT4.FENOTCHATTNSEL10', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHCAPCRSE10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHCAPCRSE10, self).__init__(register,
            'FENOTCHCAPCRSE10', 'AGC_S.FENOTCHATT4.FENOTCHCAPCRSE10', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHCAPFINE10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHCAPFINE10, self).__init__(register,
            'FENOTCHCAPFINE10', 'AGC_S.FENOTCHATT4.FENOTCHCAPFINE10', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHRATTNEN10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHRATTNEN10, self).__init__(register,
            'FENOTCHRATTNEN10', 'AGC_S.FENOTCHATT4.FENOTCHRATTNEN10', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT4_FENOTCHEN10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT4_FENOTCHEN10, self).__init__(register,
            'FENOTCHEN10', 'AGC_S.FENOTCHATT4.FENOTCHEN10', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHATTNSEL11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHATTNSEL11, self).__init__(register,
            'FENOTCHATTNSEL11', 'AGC_S.FENOTCHATT5.FENOTCHATTNSEL11', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHCAPCRSE11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHCAPCRSE11, self).__init__(register,
            'FENOTCHCAPCRSE11', 'AGC_S.FENOTCHATT5.FENOTCHCAPCRSE11', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHCAPFINE11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHCAPFINE11, self).__init__(register,
            'FENOTCHCAPFINE11', 'AGC_S.FENOTCHATT5.FENOTCHCAPFINE11', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHRATTNEN11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHRATTNEN11, self).__init__(register,
            'FENOTCHRATTNEN11', 'AGC_S.FENOTCHATT5.FENOTCHRATTNEN11', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHEN11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHEN11, self).__init__(register,
            'FENOTCHEN11', 'AGC_S.FENOTCHATT5.FENOTCHEN11', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHATTNSEL12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHATTNSEL12, self).__init__(register,
            'FENOTCHATTNSEL12', 'AGC_S.FENOTCHATT5.FENOTCHATTNSEL12', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHCAPCRSE12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHCAPCRSE12, self).__init__(register,
            'FENOTCHCAPCRSE12', 'AGC_S.FENOTCHATT5.FENOTCHCAPCRSE12', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHCAPFINE12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHCAPFINE12, self).__init__(register,
            'FENOTCHCAPFINE12', 'AGC_S.FENOTCHATT5.FENOTCHCAPFINE12', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHRATTNEN12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHRATTNEN12, self).__init__(register,
            'FENOTCHRATTNEN12', 'AGC_S.FENOTCHATT5.FENOTCHRATTNEN12', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT5_FENOTCHEN12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT5_FENOTCHEN12, self).__init__(register,
            'FENOTCHEN12', 'AGC_S.FENOTCHATT5.FENOTCHEN12', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHATTNSEL13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHATTNSEL13, self).__init__(register,
            'FENOTCHATTNSEL13', 'AGC_S.FENOTCHATT6.FENOTCHATTNSEL13', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHCAPCRSE13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHCAPCRSE13, self).__init__(register,
            'FENOTCHCAPCRSE13', 'AGC_S.FENOTCHATT6.FENOTCHCAPCRSE13', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHCAPFINE13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHCAPFINE13, self).__init__(register,
            'FENOTCHCAPFINE13', 'AGC_S.FENOTCHATT6.FENOTCHCAPFINE13', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHRATTNEN13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHRATTNEN13, self).__init__(register,
            'FENOTCHRATTNEN13', 'AGC_S.FENOTCHATT6.FENOTCHRATTNEN13', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHEN13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHEN13, self).__init__(register,
            'FENOTCHEN13', 'AGC_S.FENOTCHATT6.FENOTCHEN13', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHATTNSEL14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHATTNSEL14, self).__init__(register,
            'FENOTCHATTNSEL14', 'AGC_S.FENOTCHATT6.FENOTCHATTNSEL14', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHCAPCRSE14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHCAPCRSE14, self).__init__(register,
            'FENOTCHCAPCRSE14', 'AGC_S.FENOTCHATT6.FENOTCHCAPCRSE14', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHCAPFINE14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHCAPFINE14, self).__init__(register,
            'FENOTCHCAPFINE14', 'AGC_S.FENOTCHATT6.FENOTCHCAPFINE14', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHRATTNEN14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHRATTNEN14, self).__init__(register,
            'FENOTCHRATTNEN14', 'AGC_S.FENOTCHATT6.FENOTCHRATTNEN14', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT6_FENOTCHEN14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT6_FENOTCHEN14, self).__init__(register,
            'FENOTCHEN14', 'AGC_S.FENOTCHATT6.FENOTCHEN14', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHATTNSEL15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHATTNSEL15, self).__init__(register,
            'FENOTCHATTNSEL15', 'AGC_S.FENOTCHATT7.FENOTCHATTNSEL15', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHCAPCRSE15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHCAPCRSE15, self).__init__(register,
            'FENOTCHCAPCRSE15', 'AGC_S.FENOTCHATT7.FENOTCHCAPCRSE15', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHCAPFINE15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHCAPFINE15, self).__init__(register,
            'FENOTCHCAPFINE15', 'AGC_S.FENOTCHATT7.FENOTCHCAPFINE15', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHRATTNEN15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHRATTNEN15, self).__init__(register,
            'FENOTCHRATTNEN15', 'AGC_S.FENOTCHATT7.FENOTCHRATTNEN15', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHEN15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHEN15, self).__init__(register,
            'FENOTCHEN15', 'AGC_S.FENOTCHATT7.FENOTCHEN15', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHATTNSEL16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHATTNSEL16, self).__init__(register,
            'FENOTCHATTNSEL16', 'AGC_S.FENOTCHATT7.FENOTCHATTNSEL16', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHCAPCRSE16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHCAPCRSE16, self).__init__(register,
            'FENOTCHCAPCRSE16', 'AGC_S.FENOTCHATT7.FENOTCHCAPCRSE16', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHCAPFINE16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHCAPFINE16, self).__init__(register,
            'FENOTCHCAPFINE16', 'AGC_S.FENOTCHATT7.FENOTCHCAPFINE16', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHRATTNEN16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHRATTNEN16, self).__init__(register,
            'FENOTCHRATTNEN16', 'AGC_S.FENOTCHATT7.FENOTCHRATTNEN16', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT7_FENOTCHEN16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT7_FENOTCHEN16, self).__init__(register,
            'FENOTCHEN16', 'AGC_S.FENOTCHATT7.FENOTCHEN16', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHATTNSEL17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHATTNSEL17, self).__init__(register,
            'FENOTCHATTNSEL17', 'AGC_S.FENOTCHATT8.FENOTCHATTNSEL17', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHCAPCRSE17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHCAPCRSE17, self).__init__(register,
            'FENOTCHCAPCRSE17', 'AGC_S.FENOTCHATT8.FENOTCHCAPCRSE17', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHCAPFINE17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHCAPFINE17, self).__init__(register,
            'FENOTCHCAPFINE17', 'AGC_S.FENOTCHATT8.FENOTCHCAPFINE17', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHRATTNEN17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHRATTNEN17, self).__init__(register,
            'FENOTCHRATTNEN17', 'AGC_S.FENOTCHATT8.FENOTCHRATTNEN17', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHEN17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHEN17, self).__init__(register,
            'FENOTCHEN17', 'AGC_S.FENOTCHATT8.FENOTCHEN17', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHATTNSEL18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHATTNSEL18, self).__init__(register,
            'FENOTCHATTNSEL18', 'AGC_S.FENOTCHATT8.FENOTCHATTNSEL18', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHCAPCRSE18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHCAPCRSE18, self).__init__(register,
            'FENOTCHCAPCRSE18', 'AGC_S.FENOTCHATT8.FENOTCHCAPCRSE18', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHCAPFINE18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHCAPFINE18, self).__init__(register,
            'FENOTCHCAPFINE18', 'AGC_S.FENOTCHATT8.FENOTCHCAPFINE18', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHRATTNEN18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHRATTNEN18, self).__init__(register,
            'FENOTCHRATTNEN18', 'AGC_S.FENOTCHATT8.FENOTCHRATTNEN18', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT8_FENOTCHEN18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT8_FENOTCHEN18, self).__init__(register,
            'FENOTCHEN18', 'AGC_S.FENOTCHATT8.FENOTCHEN18', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHATTNSEL19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHATTNSEL19, self).__init__(register,
            'FENOTCHATTNSEL19', 'AGC_S.FENOTCHATT9.FENOTCHATTNSEL19', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHCAPCRSE19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHCAPCRSE19, self).__init__(register,
            'FENOTCHCAPCRSE19', 'AGC_S.FENOTCHATT9.FENOTCHCAPCRSE19', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHCAPFINE19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHCAPFINE19, self).__init__(register,
            'FENOTCHCAPFINE19', 'AGC_S.FENOTCHATT9.FENOTCHCAPFINE19', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHRATTNEN19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHRATTNEN19, self).__init__(register,
            'FENOTCHRATTNEN19', 'AGC_S.FENOTCHATT9.FENOTCHRATTNEN19', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHEN19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHEN19, self).__init__(register,
            'FENOTCHEN19', 'AGC_S.FENOTCHATT9.FENOTCHEN19', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHATTNSEL20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHATTNSEL20, self).__init__(register,
            'FENOTCHATTNSEL20', 'AGC_S.FENOTCHATT9.FENOTCHATTNSEL20', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHCAPCRSE20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHCAPCRSE20, self).__init__(register,
            'FENOTCHCAPCRSE20', 'AGC_S.FENOTCHATT9.FENOTCHCAPCRSE20', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHCAPFINE20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHCAPFINE20, self).__init__(register,
            'FENOTCHCAPFINE20', 'AGC_S.FENOTCHATT9.FENOTCHCAPFINE20', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHRATTNEN20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHRATTNEN20, self).__init__(register,
            'FENOTCHRATTNEN20', 'AGC_S.FENOTCHATT9.FENOTCHRATTNEN20', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT9_FENOTCHEN20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT9_FENOTCHEN20, self).__init__(register,
            'FENOTCHEN20', 'AGC_S.FENOTCHATT9.FENOTCHEN20', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHATTNSEL21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHATTNSEL21, self).__init__(register,
            'FENOTCHATTNSEL21', 'AGC_S.FENOTCHATT10.FENOTCHATTNSEL21', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHCAPCRSE21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHCAPCRSE21, self).__init__(register,
            'FENOTCHCAPCRSE21', 'AGC_S.FENOTCHATT10.FENOTCHCAPCRSE21', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHCAPFINE21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHCAPFINE21, self).__init__(register,
            'FENOTCHCAPFINE21', 'AGC_S.FENOTCHATT10.FENOTCHCAPFINE21', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHRATTNEN21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHRATTNEN21, self).__init__(register,
            'FENOTCHRATTNEN21', 'AGC_S.FENOTCHATT10.FENOTCHRATTNEN21', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHEN21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHEN21, self).__init__(register,
            'FENOTCHEN21', 'AGC_S.FENOTCHATT10.FENOTCHEN21', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHATTNSEL22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHATTNSEL22, self).__init__(register,
            'FENOTCHATTNSEL22', 'AGC_S.FENOTCHATT10.FENOTCHATTNSEL22', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHCAPCRSE22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHCAPCRSE22, self).__init__(register,
            'FENOTCHCAPCRSE22', 'AGC_S.FENOTCHATT10.FENOTCHCAPCRSE22', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHCAPFINE22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHCAPFINE22, self).__init__(register,
            'FENOTCHCAPFINE22', 'AGC_S.FENOTCHATT10.FENOTCHCAPFINE22', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHRATTNEN22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHRATTNEN22, self).__init__(register,
            'FENOTCHRATTNEN22', 'AGC_S.FENOTCHATT10.FENOTCHRATTNEN22', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT10_FENOTCHEN22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT10_FENOTCHEN22, self).__init__(register,
            'FENOTCHEN22', 'AGC_S.FENOTCHATT10.FENOTCHEN22', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHATTNSEL23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHATTNSEL23, self).__init__(register,
            'FENOTCHATTNSEL23', 'AGC_S.FENOTCHATT11.FENOTCHATTNSEL23', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHCAPCRSE23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHCAPCRSE23, self).__init__(register,
            'FENOTCHCAPCRSE23', 'AGC_S.FENOTCHATT11.FENOTCHCAPCRSE23', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHCAPFINE23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHCAPFINE23, self).__init__(register,
            'FENOTCHCAPFINE23', 'AGC_S.FENOTCHATT11.FENOTCHCAPFINE23', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHRATTNEN23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHRATTNEN23, self).__init__(register,
            'FENOTCHRATTNEN23', 'AGC_S.FENOTCHATT11.FENOTCHRATTNEN23', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHEN23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHEN23, self).__init__(register,
            'FENOTCHEN23', 'AGC_S.FENOTCHATT11.FENOTCHEN23', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHATTNSEL24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHATTNSEL24, self).__init__(register,
            'FENOTCHATTNSEL24', 'AGC_S.FENOTCHATT11.FENOTCHATTNSEL24', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHCAPCRSE24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHCAPCRSE24, self).__init__(register,
            'FENOTCHCAPCRSE24', 'AGC_S.FENOTCHATT11.FENOTCHCAPCRSE24', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHCAPFINE24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHCAPFINE24, self).__init__(register,
            'FENOTCHCAPFINE24', 'AGC_S.FENOTCHATT11.FENOTCHCAPFINE24', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHRATTNEN24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHRATTNEN24, self).__init__(register,
            'FENOTCHRATTNEN24', 'AGC_S.FENOTCHATT11.FENOTCHRATTNEN24', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHATT11_FENOTCHEN24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHATT11_FENOTCHEN24, self).__init__(register,
            'FENOTCHEN24', 'AGC_S.FENOTCHATT11.FENOTCHEN24', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHATTNSEL1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHATTNSEL1, self).__init__(register,
            'FENOTCHATTNSEL1', 'AGC_S.FENOTCHFILT0.FENOTCHATTNSEL1', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHCAPCRSE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHCAPCRSE1, self).__init__(register,
            'FENOTCHCAPCRSE1', 'AGC_S.FENOTCHFILT0.FENOTCHCAPCRSE1', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHCAPFINE1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHCAPFINE1, self).__init__(register,
            'FENOTCHCAPFINE1', 'AGC_S.FENOTCHFILT0.FENOTCHCAPFINE1', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHRATTNEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHRATTNEN1, self).__init__(register,
            'FENOTCHRATTNEN1', 'AGC_S.FENOTCHFILT0.FENOTCHRATTNEN1', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHEN1(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHEN1, self).__init__(register,
            'FENOTCHEN1', 'AGC_S.FENOTCHFILT0.FENOTCHEN1', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHATTNSEL2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHATTNSEL2, self).__init__(register,
            'FENOTCHATTNSEL2', 'AGC_S.FENOTCHFILT0.FENOTCHATTNSEL2', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHCAPCRSE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHCAPCRSE2, self).__init__(register,
            'FENOTCHCAPCRSE2', 'AGC_S.FENOTCHFILT0.FENOTCHCAPCRSE2', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHCAPFINE2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHCAPFINE2, self).__init__(register,
            'FENOTCHCAPFINE2', 'AGC_S.FENOTCHFILT0.FENOTCHCAPFINE2', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHRATTNEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHRATTNEN2, self).__init__(register,
            'FENOTCHRATTNEN2', 'AGC_S.FENOTCHFILT0.FENOTCHRATTNEN2', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT0_FENOTCHEN2(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT0_FENOTCHEN2, self).__init__(register,
            'FENOTCHEN2', 'AGC_S.FENOTCHFILT0.FENOTCHEN2', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHATTNSEL3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHATTNSEL3, self).__init__(register,
            'FENOTCHATTNSEL3', 'AGC_S.FENOTCHFILT1.FENOTCHATTNSEL3', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHCAPCRSE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHCAPCRSE3, self).__init__(register,
            'FENOTCHCAPCRSE3', 'AGC_S.FENOTCHFILT1.FENOTCHCAPCRSE3', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHCAPFINE3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHCAPFINE3, self).__init__(register,
            'FENOTCHCAPFINE3', 'AGC_S.FENOTCHFILT1.FENOTCHCAPFINE3', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHRATTNEN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHRATTNEN3, self).__init__(register,
            'FENOTCHRATTNEN3', 'AGC_S.FENOTCHFILT1.FENOTCHRATTNEN3', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHEN3(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHEN3, self).__init__(register,
            'FENOTCHEN3', 'AGC_S.FENOTCHFILT1.FENOTCHEN3', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHATTNSEL4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHATTNSEL4, self).__init__(register,
            'FENOTCHATTNSEL4', 'AGC_S.FENOTCHFILT1.FENOTCHATTNSEL4', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHCAPCRSE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHCAPCRSE4, self).__init__(register,
            'FENOTCHCAPCRSE4', 'AGC_S.FENOTCHFILT1.FENOTCHCAPCRSE4', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHCAPFINE4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHCAPFINE4, self).__init__(register,
            'FENOTCHCAPFINE4', 'AGC_S.FENOTCHFILT1.FENOTCHCAPFINE4', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHRATTNEN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHRATTNEN4, self).__init__(register,
            'FENOTCHRATTNEN4', 'AGC_S.FENOTCHFILT1.FENOTCHRATTNEN4', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT1_FENOTCHEN4(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT1_FENOTCHEN4, self).__init__(register,
            'FENOTCHEN4', 'AGC_S.FENOTCHFILT1.FENOTCHEN4', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHATTNSEL5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHATTNSEL5, self).__init__(register,
            'FENOTCHATTNSEL5', 'AGC_S.FENOTCHFILT2.FENOTCHATTNSEL5', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHCAPCRSE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHCAPCRSE5, self).__init__(register,
            'FENOTCHCAPCRSE5', 'AGC_S.FENOTCHFILT2.FENOTCHCAPCRSE5', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHCAPFINE5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHCAPFINE5, self).__init__(register,
            'FENOTCHCAPFINE5', 'AGC_S.FENOTCHFILT2.FENOTCHCAPFINE5', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHRATTNEN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHRATTNEN5, self).__init__(register,
            'FENOTCHRATTNEN5', 'AGC_S.FENOTCHFILT2.FENOTCHRATTNEN5', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHEN5(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHEN5, self).__init__(register,
            'FENOTCHEN5', 'AGC_S.FENOTCHFILT2.FENOTCHEN5', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHATTNSEL6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHATTNSEL6, self).__init__(register,
            'FENOTCHATTNSEL6', 'AGC_S.FENOTCHFILT2.FENOTCHATTNSEL6', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHCAPCRSE6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHCAPCRSE6, self).__init__(register,
            'FENOTCHCAPCRSE6', 'AGC_S.FENOTCHFILT2.FENOTCHCAPCRSE6', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHCAPFINE6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHCAPFINE6, self).__init__(register,
            'FENOTCHCAPFINE6', 'AGC_S.FENOTCHFILT2.FENOTCHCAPFINE6', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHRATTNEN6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHRATTNEN6, self).__init__(register,
            'FENOTCHRATTNEN6', 'AGC_S.FENOTCHFILT2.FENOTCHRATTNEN6', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT2_FENOTCHEN6(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT2_FENOTCHEN6, self).__init__(register,
            'FENOTCHEN6', 'AGC_S.FENOTCHFILT2.FENOTCHEN6', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHATTNSEL7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHATTNSEL7, self).__init__(register,
            'FENOTCHATTNSEL7', 'AGC_S.FENOTCHFILT3.FENOTCHATTNSEL7', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHCAPCRSE7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHCAPCRSE7, self).__init__(register,
            'FENOTCHCAPCRSE7', 'AGC_S.FENOTCHFILT3.FENOTCHCAPCRSE7', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHCAPFINE7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHCAPFINE7, self).__init__(register,
            'FENOTCHCAPFINE7', 'AGC_S.FENOTCHFILT3.FENOTCHCAPFINE7', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHRATTNEN7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHRATTNEN7, self).__init__(register,
            'FENOTCHRATTNEN7', 'AGC_S.FENOTCHFILT3.FENOTCHRATTNEN7', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHEN7(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHEN7, self).__init__(register,
            'FENOTCHEN7', 'AGC_S.FENOTCHFILT3.FENOTCHEN7', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHATTNSEL8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHATTNSEL8, self).__init__(register,
            'FENOTCHATTNSEL8', 'AGC_S.FENOTCHFILT3.FENOTCHATTNSEL8', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHCAPCRSE8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHCAPCRSE8, self).__init__(register,
            'FENOTCHCAPCRSE8', 'AGC_S.FENOTCHFILT3.FENOTCHCAPCRSE8', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHCAPFINE8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHCAPFINE8, self).__init__(register,
            'FENOTCHCAPFINE8', 'AGC_S.FENOTCHFILT3.FENOTCHCAPFINE8', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHRATTNEN8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHRATTNEN8, self).__init__(register,
            'FENOTCHRATTNEN8', 'AGC_S.FENOTCHFILT3.FENOTCHRATTNEN8', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT3_FENOTCHEN8(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT3_FENOTCHEN8, self).__init__(register,
            'FENOTCHEN8', 'AGC_S.FENOTCHFILT3.FENOTCHEN8', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHATTNSEL9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHATTNSEL9, self).__init__(register,
            'FENOTCHATTNSEL9', 'AGC_S.FENOTCHFILT4.FENOTCHATTNSEL9', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHCAPCRSE9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHCAPCRSE9, self).__init__(register,
            'FENOTCHCAPCRSE9', 'AGC_S.FENOTCHFILT4.FENOTCHCAPCRSE9', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHCAPFINE9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHCAPFINE9, self).__init__(register,
            'FENOTCHCAPFINE9', 'AGC_S.FENOTCHFILT4.FENOTCHCAPFINE9', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHRATTNEN9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHRATTNEN9, self).__init__(register,
            'FENOTCHRATTNEN9', 'AGC_S.FENOTCHFILT4.FENOTCHRATTNEN9', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHEN9(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHEN9, self).__init__(register,
            'FENOTCHEN9', 'AGC_S.FENOTCHFILT4.FENOTCHEN9', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHATTNSEL10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHATTNSEL10, self).__init__(register,
            'FENOTCHATTNSEL10', 'AGC_S.FENOTCHFILT4.FENOTCHATTNSEL10', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHCAPCRSE10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHCAPCRSE10, self).__init__(register,
            'FENOTCHCAPCRSE10', 'AGC_S.FENOTCHFILT4.FENOTCHCAPCRSE10', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHCAPFINE10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHCAPFINE10, self).__init__(register,
            'FENOTCHCAPFINE10', 'AGC_S.FENOTCHFILT4.FENOTCHCAPFINE10', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHRATTNEN10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHRATTNEN10, self).__init__(register,
            'FENOTCHRATTNEN10', 'AGC_S.FENOTCHFILT4.FENOTCHRATTNEN10', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT4_FENOTCHEN10(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT4_FENOTCHEN10, self).__init__(register,
            'FENOTCHEN10', 'AGC_S.FENOTCHFILT4.FENOTCHEN10', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHATTNSEL11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHATTNSEL11, self).__init__(register,
            'FENOTCHATTNSEL11', 'AGC_S.FENOTCHFILT5.FENOTCHATTNSEL11', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHCAPCRSE11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHCAPCRSE11, self).__init__(register,
            'FENOTCHCAPCRSE11', 'AGC_S.FENOTCHFILT5.FENOTCHCAPCRSE11', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHCAPFINE11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHCAPFINE11, self).__init__(register,
            'FENOTCHCAPFINE11', 'AGC_S.FENOTCHFILT5.FENOTCHCAPFINE11', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHRATTNEN11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHRATTNEN11, self).__init__(register,
            'FENOTCHRATTNEN11', 'AGC_S.FENOTCHFILT5.FENOTCHRATTNEN11', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHEN11(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHEN11, self).__init__(register,
            'FENOTCHEN11', 'AGC_S.FENOTCHFILT5.FENOTCHEN11', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHATTNSEL12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHATTNSEL12, self).__init__(register,
            'FENOTCHATTNSEL12', 'AGC_S.FENOTCHFILT5.FENOTCHATTNSEL12', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHCAPCRSE12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHCAPCRSE12, self).__init__(register,
            'FENOTCHCAPCRSE12', 'AGC_S.FENOTCHFILT5.FENOTCHCAPCRSE12', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHCAPFINE12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHCAPFINE12, self).__init__(register,
            'FENOTCHCAPFINE12', 'AGC_S.FENOTCHFILT5.FENOTCHCAPFINE12', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHRATTNEN12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHRATTNEN12, self).__init__(register,
            'FENOTCHRATTNEN12', 'AGC_S.FENOTCHFILT5.FENOTCHRATTNEN12', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT5_FENOTCHEN12(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT5_FENOTCHEN12, self).__init__(register,
            'FENOTCHEN12', 'AGC_S.FENOTCHFILT5.FENOTCHEN12', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHATTNSEL13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHATTNSEL13, self).__init__(register,
            'FENOTCHATTNSEL13', 'AGC_S.FENOTCHFILT6.FENOTCHATTNSEL13', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHCAPCRSE13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHCAPCRSE13, self).__init__(register,
            'FENOTCHCAPCRSE13', 'AGC_S.FENOTCHFILT6.FENOTCHCAPCRSE13', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHCAPFINE13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHCAPFINE13, self).__init__(register,
            'FENOTCHCAPFINE13', 'AGC_S.FENOTCHFILT6.FENOTCHCAPFINE13', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHRATTNEN13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHRATTNEN13, self).__init__(register,
            'FENOTCHRATTNEN13', 'AGC_S.FENOTCHFILT6.FENOTCHRATTNEN13', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHEN13(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHEN13, self).__init__(register,
            'FENOTCHEN13', 'AGC_S.FENOTCHFILT6.FENOTCHEN13', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHATTNSEL14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHATTNSEL14, self).__init__(register,
            'FENOTCHATTNSEL14', 'AGC_S.FENOTCHFILT6.FENOTCHATTNSEL14', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHCAPCRSE14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHCAPCRSE14, self).__init__(register,
            'FENOTCHCAPCRSE14', 'AGC_S.FENOTCHFILT6.FENOTCHCAPCRSE14', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHCAPFINE14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHCAPFINE14, self).__init__(register,
            'FENOTCHCAPFINE14', 'AGC_S.FENOTCHFILT6.FENOTCHCAPFINE14', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHRATTNEN14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHRATTNEN14, self).__init__(register,
            'FENOTCHRATTNEN14', 'AGC_S.FENOTCHFILT6.FENOTCHRATTNEN14', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT6_FENOTCHEN14(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT6_FENOTCHEN14, self).__init__(register,
            'FENOTCHEN14', 'AGC_S.FENOTCHFILT6.FENOTCHEN14', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHATTNSEL15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHATTNSEL15, self).__init__(register,
            'FENOTCHATTNSEL15', 'AGC_S.FENOTCHFILT7.FENOTCHATTNSEL15', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHCAPCRSE15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHCAPCRSE15, self).__init__(register,
            'FENOTCHCAPCRSE15', 'AGC_S.FENOTCHFILT7.FENOTCHCAPCRSE15', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHCAPFINE15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHCAPFINE15, self).__init__(register,
            'FENOTCHCAPFINE15', 'AGC_S.FENOTCHFILT7.FENOTCHCAPFINE15', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHRATTNEN15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHRATTNEN15, self).__init__(register,
            'FENOTCHRATTNEN15', 'AGC_S.FENOTCHFILT7.FENOTCHRATTNEN15', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHEN15(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHEN15, self).__init__(register,
            'FENOTCHEN15', 'AGC_S.FENOTCHFILT7.FENOTCHEN15', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHATTNSEL16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHATTNSEL16, self).__init__(register,
            'FENOTCHATTNSEL16', 'AGC_S.FENOTCHFILT7.FENOTCHATTNSEL16', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHCAPCRSE16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHCAPCRSE16, self).__init__(register,
            'FENOTCHCAPCRSE16', 'AGC_S.FENOTCHFILT7.FENOTCHCAPCRSE16', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHCAPFINE16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHCAPFINE16, self).__init__(register,
            'FENOTCHCAPFINE16', 'AGC_S.FENOTCHFILT7.FENOTCHCAPFINE16', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHRATTNEN16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHRATTNEN16, self).__init__(register,
            'FENOTCHRATTNEN16', 'AGC_S.FENOTCHFILT7.FENOTCHRATTNEN16', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT7_FENOTCHEN16(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT7_FENOTCHEN16, self).__init__(register,
            'FENOTCHEN16', 'AGC_S.FENOTCHFILT7.FENOTCHEN16', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHATTNSEL17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHATTNSEL17, self).__init__(register,
            'FENOTCHATTNSEL17', 'AGC_S.FENOTCHFILT8.FENOTCHATTNSEL17', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHCAPCRSE17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHCAPCRSE17, self).__init__(register,
            'FENOTCHCAPCRSE17', 'AGC_S.FENOTCHFILT8.FENOTCHCAPCRSE17', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHCAPFINE17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHCAPFINE17, self).__init__(register,
            'FENOTCHCAPFINE17', 'AGC_S.FENOTCHFILT8.FENOTCHCAPFINE17', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHRATTNEN17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHRATTNEN17, self).__init__(register,
            'FENOTCHRATTNEN17', 'AGC_S.FENOTCHFILT8.FENOTCHRATTNEN17', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHEN17(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHEN17, self).__init__(register,
            'FENOTCHEN17', 'AGC_S.FENOTCHFILT8.FENOTCHEN17', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHATTNSEL18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHATTNSEL18, self).__init__(register,
            'FENOTCHATTNSEL18', 'AGC_S.FENOTCHFILT8.FENOTCHATTNSEL18', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHCAPCRSE18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHCAPCRSE18, self).__init__(register,
            'FENOTCHCAPCRSE18', 'AGC_S.FENOTCHFILT8.FENOTCHCAPCRSE18', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHCAPFINE18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHCAPFINE18, self).__init__(register,
            'FENOTCHCAPFINE18', 'AGC_S.FENOTCHFILT8.FENOTCHCAPFINE18', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHRATTNEN18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHRATTNEN18, self).__init__(register,
            'FENOTCHRATTNEN18', 'AGC_S.FENOTCHFILT8.FENOTCHRATTNEN18', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT8_FENOTCHEN18(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT8_FENOTCHEN18, self).__init__(register,
            'FENOTCHEN18', 'AGC_S.FENOTCHFILT8.FENOTCHEN18', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHATTNSEL19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHATTNSEL19, self).__init__(register,
            'FENOTCHATTNSEL19', 'AGC_S.FENOTCHFILT9.FENOTCHATTNSEL19', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHCAPCRSE19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHCAPCRSE19, self).__init__(register,
            'FENOTCHCAPCRSE19', 'AGC_S.FENOTCHFILT9.FENOTCHCAPCRSE19', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHCAPFINE19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHCAPFINE19, self).__init__(register,
            'FENOTCHCAPFINE19', 'AGC_S.FENOTCHFILT9.FENOTCHCAPFINE19', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHRATTNEN19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHRATTNEN19, self).__init__(register,
            'FENOTCHRATTNEN19', 'AGC_S.FENOTCHFILT9.FENOTCHRATTNEN19', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHEN19(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHEN19, self).__init__(register,
            'FENOTCHEN19', 'AGC_S.FENOTCHFILT9.FENOTCHEN19', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHATTNSEL20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHATTNSEL20, self).__init__(register,
            'FENOTCHATTNSEL20', 'AGC_S.FENOTCHFILT9.FENOTCHATTNSEL20', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHCAPCRSE20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHCAPCRSE20, self).__init__(register,
            'FENOTCHCAPCRSE20', 'AGC_S.FENOTCHFILT9.FENOTCHCAPCRSE20', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHCAPFINE20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHCAPFINE20, self).__init__(register,
            'FENOTCHCAPFINE20', 'AGC_S.FENOTCHFILT9.FENOTCHCAPFINE20', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHRATTNEN20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHRATTNEN20, self).__init__(register,
            'FENOTCHRATTNEN20', 'AGC_S.FENOTCHFILT9.FENOTCHRATTNEN20', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT9_FENOTCHEN20(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT9_FENOTCHEN20, self).__init__(register,
            'FENOTCHEN20', 'AGC_S.FENOTCHFILT9.FENOTCHEN20', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHATTNSEL21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHATTNSEL21, self).__init__(register,
            'FENOTCHATTNSEL21', 'AGC_S.FENOTCHFILT10.FENOTCHATTNSEL21', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHCAPCRSE21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHCAPCRSE21, self).__init__(register,
            'FENOTCHCAPCRSE21', 'AGC_S.FENOTCHFILT10.FENOTCHCAPCRSE21', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHCAPFINE21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHCAPFINE21, self).__init__(register,
            'FENOTCHCAPFINE21', 'AGC_S.FENOTCHFILT10.FENOTCHCAPFINE21', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHRATTNEN21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHRATTNEN21, self).__init__(register,
            'FENOTCHRATTNEN21', 'AGC_S.FENOTCHFILT10.FENOTCHRATTNEN21', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHEN21(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHEN21, self).__init__(register,
            'FENOTCHEN21', 'AGC_S.FENOTCHFILT10.FENOTCHEN21', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHATTNSEL22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHATTNSEL22, self).__init__(register,
            'FENOTCHATTNSEL22', 'AGC_S.FENOTCHFILT10.FENOTCHATTNSEL22', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHCAPCRSE22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHCAPCRSE22, self).__init__(register,
            'FENOTCHCAPCRSE22', 'AGC_S.FENOTCHFILT10.FENOTCHCAPCRSE22', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHCAPFINE22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHCAPFINE22, self).__init__(register,
            'FENOTCHCAPFINE22', 'AGC_S.FENOTCHFILT10.FENOTCHCAPFINE22', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHRATTNEN22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHRATTNEN22, self).__init__(register,
            'FENOTCHRATTNEN22', 'AGC_S.FENOTCHFILT10.FENOTCHRATTNEN22', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT10_FENOTCHEN22(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT10_FENOTCHEN22, self).__init__(register,
            'FENOTCHEN22', 'AGC_S.FENOTCHFILT10.FENOTCHEN22', 'read-write',
            u"",
            29, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHATTNSEL23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHATTNSEL23, self).__init__(register,
            'FENOTCHATTNSEL23', 'AGC_S.FENOTCHFILT11.FENOTCHATTNSEL23', 'read-write',
            u"",
            0, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHCAPCRSE23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHCAPCRSE23, self).__init__(register,
            'FENOTCHCAPCRSE23', 'AGC_S.FENOTCHFILT11.FENOTCHCAPCRSE23', 'read-write',
            u"",
            4, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHCAPFINE23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHCAPFINE23, self).__init__(register,
            'FENOTCHCAPFINE23', 'AGC_S.FENOTCHFILT11.FENOTCHCAPFINE23', 'read-write',
            u"",
            8, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHRATTNEN23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHRATTNEN23, self).__init__(register,
            'FENOTCHRATTNEN23', 'AGC_S.FENOTCHFILT11.FENOTCHRATTNEN23', 'read-write',
            u"",
            12, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHEN23(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHEN23, self).__init__(register,
            'FENOTCHEN23', 'AGC_S.FENOTCHFILT11.FENOTCHEN23', 'read-write',
            u"",
            13, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHATTNSEL24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHATTNSEL24, self).__init__(register,
            'FENOTCHATTNSEL24', 'AGC_S.FENOTCHFILT11.FENOTCHATTNSEL24', 'read-write',
            u"",
            16, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHCAPCRSE24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHCAPCRSE24, self).__init__(register,
            'FENOTCHCAPCRSE24', 'AGC_S.FENOTCHFILT11.FENOTCHCAPCRSE24', 'read-write',
            u"",
            20, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHCAPFINE24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHCAPFINE24, self).__init__(register,
            'FENOTCHCAPFINE24', 'AGC_S.FENOTCHFILT11.FENOTCHCAPFINE24', 'read-write',
            u"",
            24, 4)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHRATTNEN24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHRATTNEN24, self).__init__(register,
            'FENOTCHRATTNEN24', 'AGC_S.FENOTCHFILT11.FENOTCHRATTNEN24', 'read-write',
            u"",
            28, 1)
        self.__dict__['zz_frozen'] = True


class RM_Field_AGC_S_FENOTCHFILT11_FENOTCHEN24(Base_RM_Field):
    def __init__(self, register):
        self.__dict__['zz_frozen'] = False
        super(RM_Field_AGC_S_FENOTCHFILT11_FENOTCHEN24, self).__init__(register,
            'FENOTCHEN24', 'AGC_S.FENOTCHFILT11.FENOTCHEN24', 'read-write',
            u"",
            29, 1)
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



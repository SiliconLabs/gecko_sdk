
from py_2_and_3_compatibility import *
from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr


class profile_MBus_modes(object):


    #
    # I have no idea what this does but all of the phys below set these agc registers to these
    # values.  Do we really need to do this manually like this?  If all Mbus phys want these
    # register values set this way, is it something we can put in the calculations instead?
    #
    # These really need to be removed from these phys.  I have created a Jira issue to track this work:
    #   https://jira.silabs.com/browse/MCUW_RADIO_CFG-505
    #
    @staticmethod
    def set_agc_to_some_mysterious_values(model, family):
        model.vars.AGC_MININDEX_INDEXMINPGA.value_forced = 9
        model.vars.AGC_MININDEX_INDEXMINDEGEN.value_forced = 6
        model.vars.AGC_MININDEX_INDEXMINSLICES.value_forced = 0
        model.vars.AGC_MININDEX_INDEXMINATTEN.value_forced = 21

        # Enable the Low-bandwidth mode in LNA and PGA
        model.vars.RAC_SGLNAMIXCTRL1_TRIMNPATHBW.value_forced = 3
        model.vars.RAC_IFPGACTRL1_LBWMODE.value_forced = 1
        # Enable fast-attack, slow-decay feature in the AGC
        model.vars.AGC_GAINSTEPLIM_SLOWDECAYCNT.value_forced = 30

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-184
    @staticmethod
    def profile_wMbus_ModeT_M2O_100k(model, family):

        #Settings that are not profile inputs for Mbus
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.bitrate.value_forced = 66666
        model.vars.baudrate_tol_ppm.value_forced = 120000
        model.vars.deviation.value_forced = 50000
        model.vars.preamble_detection_length.value_forced = 38
        model.vars.rx_xtal_error_ppm.value_forced = 25
        model.vars.tx_xtal_error_ppm.value_forced = 60
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.NONE
        model.vars.shaping_filter_param.value_forced = 0.0

        # Value optimized to meet frequency offset spec with deviation tolerance of 40kHz and 112 kcps baidrate
        # Details https://jira.silabs.com/browse/MCUW_RADIO_CFG-1505
        model.vars.bandwidth_hz.value_forced = 330000

        #The deviation requirements for this PHY are not symmetrical, thes inputs help on the calculation to accoutn for that
        model.vars.freq_dev_max.value_forced = 80000
        model.vars.freq_dev_min.value_forced = 40000
        #This override helps clean up PER floor reducing probabiliy of ocurrance from 5/10 to 1/10, investigation available:
        # https://jira.silabs.com/browse/MCUW_RADIO_CFG-1447
        model.vars.MODEM_BCRDEMODKSI_BCRKSI3.value_forced = 30
        #This override reverts the changes to improve floor issues for low modulation index BCR PHYs. Since modeT phy
        #is meeting spec without this change, use the override to keep the phy the same
        model.vars.MODEM_BCRDEMODCTRL_BBPMDETEN.value_forced = 1
        #These overrides are used to support performance with long preamble lengths on WMBUS
        # Details available in https://jira.silabs.com/browse/MCUW_RADIO_CFG-1752
        model.vars.MODEM_FRMSCHTIME_PMENDSCHEN.value_forced = 1
        model.vars.MODEM_FRMSCHTIME_FRMSCHTIME.value_forced = 65535

    @staticmethod
    def profile_wMbus_ModeTC_M2O_100k(model, family):

        #Settings that are not profile inputs for Mbus

        # These values are the same as ModeT_M2O_100k
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.bitrate.value_forced = 66666
        model.vars.baudrate_tol_ppm.value_forced = 120000
        model.vars.deviation.value_forced = 50000
        model.vars.preamble_detection_length.value_forced = 38
        model.vars.rx_xtal_error_ppm.value_forced = 25
        model.vars.tx_xtal_error_ppm.value_forced = 60
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.NONE
        model.vars.shaping_filter_param.value_forced = 0.0
        model.vars.bandwidth_hz.value_forced = 330000
        model.vars.freq_dev_max.value_forced = 80000
        model.vars.MODEM_BCRDEMODCTRL_BBPMDETEN.value_forced = 1
        model.vars.MODEM_FRMSCHTIME_PMENDSCHEN.value_forced = 1
        model.vars.MODEM_FRMSCHTIME_FRMSCHTIME.value_forced = 65535

        # These values are different from ModeT_M2O_100k, see https://jira.silabs.com/browse/MCUW_RADIO_CFG-2150
        model.vars.freq_dev_min.value_forced = 33750                        # To accomodate C Mode M2O Specs
        model.vars.MODEM_BCRDEMODPMEXP_BCRCFECOSTTHD.value_forced = 168     # To resolve sensitivity issue at corner case (868.95MHz / 88kcps / 80kHz freqdev)
        # model.vars.MODEM_BCRDEMODKSI_BCRKSI3.value_forced = 30            # Commented out as packet loss not observed any more





    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-31
    @staticmethod
    def profile_wMbus_ModeN2g_19p2k(model, family):

        # Basic PHY definition (from standard)
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK4
        model.vars.bitrate.value_forced = 19200
        model.vars.deviation.value_forced = 2400
        model.vars.preamble_detection_length.value_forced = 16

        #Xtal tolerance form spec is 15. The tolerance is reduced top optimize sensitivity and performance
        #Details available in https://jira.silabs.com/browse/MCUW_RADIO_CFG-1486
        model.vars.rx_xtal_error_ppm.value_forced = 15
        model.vars.tx_xtal_error_ppm.value_forced = 15
        # Baudrate from spec
        model.vars.baudrate_tol_ppm.value_forced = 100

        #Shaping filter is BT=0.5 Gaussian
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.Gaussian
        model.vars.shaping_filter_param.value_forced = 0.5


        # Switching to BCR to resolve false detects on OTA testing (see https://jira.silabs.com/browse/MCUW_RADIO_CFG-2230)
        model.vars.demod_select.value_forced = model.vars.demod_select.var_enum.BCR
        model.vars.MODEM_BCRDEMODARR0_SCHPRDHI.value_forced = 2     # Empirically improves performance for 130% fdev
        model.vars.MODEM_BCRDEMODAFC1_GEARSW.value_forced = 2       # Reduces inoperable regions across center frequency sweep at 70/130% fdev

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-179
    @staticmethod
    def profile_wMbus_ModeC_M2O_100k(model, family):

        #Basic PHY parameters (from Mbus spec)
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.bitrate.value_forced = 100000
        model.vars.deviation.value_forced = 45000
        model.vars.preamble_detection_length.value_forced = 38

        #Shaping filter
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.NONE
        model.vars.shaping_filter_param.value_forced = 0.0

        #Tolerance requirements
        model.vars.rx_xtal_error_ppm.value_forced = 25
        model.vars.tx_xtal_error_ppm.value_forced = 25
        model.vars.baudrate_tol_ppm.value_forced = 0
        model.vars.deviation_tol_ppm.value_forced = 250000

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-181
    @staticmethod
    def profile_wMbus_ModeC_O2M_50k(model, family):

        model.vars.baudrate_tol_ppm.value_forced = 0
        model.vars.bitrate.value_forced = 50000
        model.vars.deviation.value_forced = 25000
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.preamble_detection_length.value_forced = 38
        model.vars.rx_xtal_error_ppm.value_forced = 25
        model.vars.tx_xtal_error_ppm.value_forced = 25
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.Gaussian
        model.vars.shaping_filter_param.value_forced = 0.5

        #Register override to improve PER floor, refer to jira ticekt PGOCELOTVALTEST-181
        model.vars.MODEM_TRECPMDET_PMMINCOSTTHD.value_forced = 350

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/MCUW_RADIO_CFG-1414
    @staticmethod
    def profile_wMbus_ModeT_O2M_32p768k(model, family):
        #Settings that are not profile inputs for Mbus
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.bitrate.value_forced = 16384
        model.vars.baudrate_tol_ppm.value_forced = 20000
        model.vars.deviation.value_forced = 50000
        model.vars.preamble_detection_length.value_forced = 30
        model.vars.rx_xtal_error_ppm.value_forced = 60
        model.vars.tx_xtal_error_ppm.value_forced = 25
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.NONE
        model.vars.shaping_filter_param.value_forced = 0.0

        # : TODO update calculation. This is required to achieve the required sensitivity at 80000 deviation
        model.vars.MODEM_BCRDEMODPMEXP_BCRCFECOSTTHD.value_forced = 200

        # The deviation requirements for this PHY are not symmetrical, thes inputs help on the calculation to accoutn for that
        model.vars.freq_dev_max.value_forced = 80000
        model.vars.freq_dev_min.value_forced = 40000

        #These overrides are used to support performance with long preamble lengths on WMBUS
        # Details available in https://jira.silabs.com/browse/MCUW_RADIO_CFG-1752
        model.vars.MODEM_FRMSCHTIME_PMENDSCHEN.value_forced = 1
        model.vars.MODEM_FRMSCHTIME_FRMSCHTIME.value_forced = 65535

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-183
    @staticmethod
    def profile_wMbus_ModeS_32p768k(model, family):

        #Settings that are not profile inputs for Mbus
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.bitrate.value_forced = 16384
        model.vars.baudrate_tol_ppm.value_forced = 20000
        model.vars.deviation.value_forced = 50000
        model.vars.preamble_detection_length.value_forced = 30
        model.vars.rx_xtal_error_ppm.value_forced = 60
        model.vars.tx_xtal_error_ppm.value_forced = 25
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.NONE
        model.vars.shaping_filter_param.value_forced = 0.0

        # : TODO update calculation. This is required to achieve the required sensitivity at 80000 deviation
        model.vars.MODEM_BCRDEMODPMEXP_BCRCFECOSTTHD.value_forced = 200

        # The deviation requirements for this PHY are not symmetrical, thes inputs help on the calculation to accoutn for that
        model.vars.freq_dev_max.value_forced = 80000
        model.vars.freq_dev_min.value_forced = 40000

        #These overrides are used to support performance with long preamble lengths on WMBUS
        # Details available in https://jira.silabs.com/browse/MCUW_RADIO_CFG-1752
        model.vars.MODEM_FRMSCHTIME_PMENDSCHEN.value_forced = 1
        model.vars.MODEM_FRMSCHTIME_FRMSCHTIME.value_forced = 65535

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-30
    @staticmethod
    def profile_wMbus_ModeN1a_4p8K(model, family):
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.baudrate_tol_ppm.value_forced = 100
        model.vars.bitrate.value_forced = 4800
        model.vars.deviation.value_forced = 2400
        model.vars.preamble_detection_length.value_forced = 16
        model.vars.rx_xtal_error_ppm.value_forced = 9
        model.vars.tx_xtal_error_ppm.value_forced = 9
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.Gaussian
        model.vars.shaping_filter_param.value_forced = 0.5

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-33
    @staticmethod
    def profile_wMbus_ModeN1c_2p4K(model, family):
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.baudrate_tol_ppm.value_forced = 100
        model.vars.bitrate.value_forced = 2400
        model.vars.deviation.value_forced = 2400
        model.vars.preamble_detection_length.value_forced = 16
        model.vars.rx_xtal_error_ppm.value_forced = 12
        model.vars.tx_xtal_error_ppm.value_forced = 12
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.Gaussian
        model.vars.shaping_filter_param.value_forced = 0.5

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-182
    @staticmethod
    def profile_wMbus_ModeR_4p8k(model, family):
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.baudrate_tol_ppm.value_forced = 20000
        model.vars.bitrate.value_forced = 2400
        model.vars.deviation.value_forced = 6000
        model.vars.preamble_detection_length.value_forced = 78
        model.vars.rx_xtal_error_ppm.value_forced = 10
        model.vars.tx_xtal_error_ppm.value_forced = 10
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.NONE
        model.vars.shaping_filter_param.value_forced = 0.0

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-64
    @staticmethod
    def profile_wMbus_ModeF_2p4k(model, family):
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK2
        model.vars.baudrate_tol_ppm.value_forced = 0
        model.vars.bitrate.value_forced = 2400
        model.vars.deviation.value_forced = 5500
        model.vars.preamble_detection_length.value_forced = 78
        model.vars.rx_xtal_error_ppm.value_forced = 16
        model.vars.tx_xtal_error_ppm.value_forced = 16
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.NONE
        model.vars.shaping_filter_param.value_forced = 0.0

    # Owner: Efrain Gaxiola
    # JIRA Link: https://jira.silabs.com/browse/PGOCELOTVALTEST-1131
    @staticmethod
    def profile_wMbus_ModeN_6p4k(model, family):

        # Basic PHY definition (from standard)
        model.vars.modulation_type.value_forced = model.vars.modulation_type.var_enum.FSK4
        model.vars.bitrate.value_forced = 6400
        model.vars.deviation.value_forced = 1060
        model.vars.preamble_detection_length.value_forced = 16

        # Baudrate and xtal tol from spec
        model.vars.baudrate_tol_ppm.value_forced = 100
        model.vars.rx_xtal_error_ppm.value_forced = 9
        model.vars.tx_xtal_error_ppm.value_forced = 9

        # Shaping filter is BT=0.5 Gaussian
        model.vars.shaping_filter.value_forced = model.vars.shaping_filter.var_enum.Gaussian
        model.vars.shaping_filter_param.value_forced = 0.5

        # Switching to BCR to resolve false detects on OTA testing (see https://jira.silabs.com/browse/MCUW_RADIO_CFG-2230)
        model.vars.demod_select.value_forced = model.vars.demod_select.var_enum.BCR
        model.vars.bandwidth_hz.value_forced = 23000                # Widens sensitivity bathtub curve for 130% fdev to meet spec
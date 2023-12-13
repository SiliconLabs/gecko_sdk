from pyradioconfig.parts.bobcat.targets.Target_Sim import Target_Sim_Bobcat
from pyradioconfig.calculator_model_framework.CalcManager import CalcManager
from os.path import join
from copy import deepcopy


class TargetSimRainier(Target_Sim_Bobcat):

    _targetName = "Sim"
    _description = "Supports the wired FPGA and other targets of sim PHYs"
    _store_config_output = True
    _cfg_location = join('target_sim','rainier')
    _tag = "SIM"

    def MODEM_SHAPING_OVERRIDE(self, model):
        # always overwrite the calculator shaping for BLE PHYs
        model.vars.MODEM_CTRL0_SHAPING.value_forced = 2

        model.vars.MODEM_SHAPING0_COEFF0.value_forced = 6
        model.vars.MODEM_SHAPING0_COEFF1.value_forced = 15
        model.vars.MODEM_SHAPING0_COEFF2.value_forced = 30
        model.vars.MODEM_SHAPING0_COEFF3.value_forced = 52

        model.vars.MODEM_SHAPING1_COEFF4.value_forced = 76
        model.vars.MODEM_SHAPING1_COEFF5.value_forced = 97
        model.vars.MODEM_SHAPING1_COEFF6.value_forced = 112
        model.vars.MODEM_SHAPING1_COEFF7.value_forced = 120

    def SYIF_LMS_OVERRIDE(self, model):
        # RF model do NOT model TDC, so force GLMS and PLMS value for QNC path
        model.vars.SYNTH_LMSOVERRIDE_GLMSOVERRIDEEN.value_forced  = 1
        model.vars.SYNTH_LMSOVERRIDE_GLMSOVERRIDEVAL.value_forced = 2048
        model.vars.SYNTH_LMSOVERRIDE_PLMSOVERRIDEEN.value_forced  = 1
        model.vars.SYNTH_LMSOVERRIDE_PLMSOVERRIDEVAL.value_forced = 0

    def target_calculate(self, model):

        #Always use fixed length in sim results
        model.vars.frame_length_type.value_forced = model.vars.frame_length_type.var_enum.FIXED_LENGTH

        #Force MMD LDO TRIM values
        #model.vars.RAC_SYNTHREGCTRL_MMDLDOVREFTRIM.value_forced = 3

        # Not supported by Wired FPGA
        # self.FRC_DFLCTRL_DISABLE(model)
        # self.FRC_FCD_DISABLE(model)

        # force lms value for target sim, since no TDC modelled.
        self.SYIF_LMS_OVERRIDE(model)

        # Fast switching overrides
        if any(word in model.phy.name.lower() for word in ['hop', 'scan', 'signify']):
            # For fast switching simulation, since we will be changing the channel we can not use
            # divided down VCO clocking (FPGA requires integer mult of HFXO)
            model.vars.adc_clock_mode.value_forced = model.vars.adc_clock_mode.var_enum.HFXOMULT

        # : PHY-specific rules (to be replaced globally once we figure out how calculate where they need to apply)
        # : Bluetooth PHY Specific overrides
        if model.phy.name == 'PHY_Bluetooth_LE_1M_Viterbi_917M_noDSA' or \
                        model.phy.name == 'PHY_Bluetooth_LE_2M_Viterbi_noDSA_fullrate' or \
                        model.phy.name == 'PHY_Bluetooth_LE_2M_Viterbi_noDSA_fullrate_phmod' or \
                        model.phy.name == 'PHY_Bluetooth_LE_2M_Viterbi' or \
                        model.phy.name == 'PHY_Bluetooth_LE' or \
                        model.phy.name == 'PHY_Bluetooth_LE_Viterbi_noDSA_fullrate' or \
                        model.phy.name == 'PHY_Bluetooth_LE_Viterbi_noDSA_fullrate_phmod' or \
                        model.phy.name == 'PHY_Bluetooth_LE_Viterbi_noDSA' or \
                        model.phy.name == 'PHY_Bluetooth_LE_Viterbi' or \
                        model.phy.name == 'PHY_Bluetooth_1M_prod' or \
                        model.phy.name == 'PHY_Bluetooth_2M_prod':

            self.MODEM_SHAPING_OVERRIDE(model)
            self.FRC_DFLCTRL_DISABLE(model)
            self.FRC_FCD_DISABLE(model)

        # : Bluetooth Longrange PHY Specific Overrides
        elif model.phy.name == 'PHY_Bluetooth_LongRange_dsa_125kbps' or \
                        model.phy.name == 'PHY_Bluetooth_LongRange_dsa_500kbps' or \
                        model.phy.name == 'PHY_Bluetooth_LongRange_NOdsa_125kbps' or \
                        model.phy.name == 'PHY_Bluetooth_LongRange_NOdsa_500kbps' or \
                        model.phy.name == 'PHY_Bluetooth_LongRange_NOdsa_125kbps_phmod' or \
                        model.phy.name == 'PHY_Bluetooth_LongRange_NOdsa_500kbps_phmod' or \
                        model.phy.name == 'PHY_Bluetooth_LR_125k_prod' or \
                        model.phy.name == 'PHY_Bluetooth_LR_500k_prod' or \
                        model.phy.name == 'PHY_Bluetooth_1M_Concurrent':

            # Bluetooth ideal gaussian filter
            self.MODEM_SHAPING_OVERRIDE(model)
            self.FRC_DFLCTRL_DISABLE(model)
            self.FRC_FCD_DISABLE(model)

            # : Longrange specific overrides
            self.FRC_LONGRANGE_OVERRIDE(model)

        elif model.phy.name == 'PHY_Signify_SUN_FSK_2Mbps_500kHz':

            # if_frequency_hz = 1369995
            model.vars.base_frequency_hz.value_forced = 2494630023

            # template - put correct calls here
            self.FRC_DFLCTRL_DISABLE(model)
            self.FRC_FCD_DISABLE(model)
            self.MODEM_SHAPING_OVERRIDE(model)

        elif model.phy.name == 'PHY_Signify_SUN_FSK_1Mbps_500kHz':
            # if_frequency_hz = 1369995
            model.vars.base_frequency_hz.value_forced = 2494630023
            # template - put correct calls here
            self.FRC_DFLCTRL_DISABLE(model)
            self.FRC_FCD_DISABLE(model)
            self.MODEM_SHAPING_OVERRIDE(model)

        elif model.phy.name == 'PHY_Signify_Concurrent':

            # if_frequency_hz = 1369995
            model.vars.base_frequency_hz.value_forced = 2494630023

            # template - put correct calls here
            self.FRC_DFLCTRL_DISABLE(model)
            self.FRC_FCD_DISABLE(model)

            self.MODEM_SHAPING_OVERRIDE(model)

        elif model.phy.name == 'PHY_IEEE802154_2p4GHz_Enhanced':

            # if_frequency_hz = 1369995
            model.vars.base_frequency_hz.value_forced = 2494630023

            # template - put correct calls here
            # self.MODEM_SHAPING_OVERRIDE(model)
            self.FRC_DFLCTRL_DISABLE(model)
            self.FRC_FCD_DISABLE(model)

        #For many 2.4GHz PHYs, we want to use divided down synth VCO for ADC clocking
        #Need to carefully set base frequency so that the ADC clock is an integer multiple of
        #HFXO rate (Wired FPGA limitation)
        if model.vars.base_frequency_hz.value < 2.3e9:
            #When testing SubG PHYs, shift to 2.4G band for simulation
            model.vars.base_frequency_hz.value_forced = 2494630023

        if model.vars.adc_constrain_xomult.value_forced is None:
            #Constrain for all 2.4G PHYs, which is everything after we shift SubG PHYs up
            model.vars.adc_constrain_xomult.value_forced = True

        if model.vars.adc_constrain_xomult.value == True:
            self._force_fadc_xomult(model)

    def _force_fadc_xomult(self, model):

        #First, pre-calculate the PHY once to see how the ADC clock mode, ADC clock rate, and IF are set
        #When pre-calculating, do not force the ADC clock to be an integer multiple of HFXO rate
        calc_manager = CalcManager(part_family=model.part_family, part_rev='ANY', target='Sim')
        model_instance_copy = deepcopy(model)
        model_instance_copy.vars.adc_constrain_xomult.value_forced = False
        calc_manager.calculate(model_instance_copy)

        #Read the variables out of the pre-calculated model
        xtal_frequency_hz = model_instance_copy.vars.xtal_frequency_hz.value
        if_frequency_hz = model_instance_copy.vars.if_frequency_hz_actual.value
        adc_clock_mode_actual = model_instance_copy.vars.adc_clock_mode_actual.value
        adc_rate_mode_actual = model_instance_copy.vars.adc_rate_mode_actual.value
        adc_vco_div = model_instance_copy.vars.adc_vco_div.value
        lo_injection_side = model_instance_copy.vars.lo_injection_side.value

        #For VCODIV PHYs, force base freq so that the ADC clock is a multiple of HFXO
        if adc_clock_mode_actual == model.vars.adc_clock_mode.var_enum.VCODIV:

            if adc_rate_mode_actual == model.vars.adc_rate_mode.var_enum.FULLRATE:
                fadc_target = 8 * xtal_frequency_hz
            elif adc_rate_mode_actual == model.vars.adc_rate_mode.var_enum.HALFRATE:
                fadc_target = 4 * xtal_frequency_hz
            else:
                fadc_target = xtal_frequency_hz

            fsynth_target = fadc_target * adc_vco_div
            if lo_injection_side == model.vars.lo_injection_side.var_enum.HIGH_SIDE:
                base_frequency_target = fsynth_target - if_frequency_hz
            else:
                base_frequency_target = fsynth_target + if_frequency_hz

            model.vars.base_frequency_hz.value_forced = base_frequency_target
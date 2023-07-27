from pyradioconfig.parts.ocelot.calculators.calc_wisun import CALC_WiSUN_Ocelot
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum
from pyradioconfig.calculator_model_framework.CalcManager import CalcManager
from pycalcmodel.core.output import ModelOutputType
import re

class CALC_WiSUN_Sol(CALC_WiSUN_Ocelot):

    def buildVariables(self, model):
        super().buildVariables(model)

        var = self._addModelVariable(model, 'conc_ofdm_option', Enum, ModelVariableFormat.DECIMAL,
                                     'Concurrent OFDM Option')
        member_data = [
            ['NONE', 0, 'No Concurrent OFDM'],
            ['OPT1', 1, 'Wi-SUN OFDM OPT1'],
            ['OPT2', 2, 'Wi-SUN OFDM OPT2'],
            ['OPT3', 3, 'Wi-SUN OFDM OPT3'],
            ['OPT4', 4, 'Wi-SUN OFDM OPT4'],
        ]
        var.var_enum = CreateModelVariableEnum(
            'ConcOfdmOptEnum',
            'List of concurrent OFDM Options',
            member_data)

        self._addModelVariable(model, 'alt_wisun_mode_switch_phr', int, ModelVariableFormat.ASCII,
                               desc='WiSUN Mode Switch PHR for alternate PHY', is_array=True)
        self._addModelVariable(model, 'alt_wisun_phy_mode_id', int, ModelVariableFormat.ASCII,
                               desc='WiSUN PhyModeID for alternate PHY', is_array=True)
        self._addModelVariable(model, 'ofdm_stf_length', int, ModelVariableFormat.DECIMAL,
                               desc='OFDM STF length (1 unit = 120us)')
        self._addModelVariable(model, 'alt_rssi_adjust_db', float, ModelVariableFormat.DECIMAL,
                               desc='RSSI compensation value for alternate PHY')

    def calc_wisun_phy_mode_id(self, model):
        # This function calculates the PhyModeID for Wi-SUN OFDM and Wi-SUN FSK PHYs
        # For OFDM, the variable contains an array of MCS0-7 values
        # For FSK, the variable contains an array of FSK off/on values

        profile_name = model.profile.name.lower()
        modulation_type = model.vars.modulation_type.value

        if profile_name in ["wisun_fan_1_0","wisun_han"]:
            #Call method from Ocelot
            super().calc_wisun_phy_mode_id(model)
        elif profile_name == "wisun_fan_1_1":
            if modulation_type == model.vars.modulation_type.var_enum.FSK2:
                # Call method from Ocelot
                super().calc_wisun_phy_mode_id(model)
            else:
                # This case is for Wi-SUN OFDM
                ofdm_option = model.vars.ofdm_option.value
                wisun_phy_mode_id = [0] * 8
                phy_type = int(ofdm_option) + 2
                wisun_phy_mode_id[0] = (phy_type << 4) + 0
                wisun_phy_mode_id[1] = (phy_type << 4) + 1
                wisun_phy_mode_id[2] = (phy_type << 4) + 2
                wisun_phy_mode_id[3] = (phy_type << 4) + 3
                wisun_phy_mode_id[4] = (phy_type << 4) + 4
                wisun_phy_mode_id[5] = (phy_type << 4) + 5
                wisun_phy_mode_id[6] = (phy_type << 4) + 6
                wisun_phy_mode_id[7] = (phy_type << 4) + 7

                #Write the variable
                model.vars.wisun_phy_mode_id.value = wisun_phy_mode_id

    def calc_conc_ofdm_option(self, model):
        #By default set this model variable to NONE
        model.vars.conc_ofdm_option.value = model.vars.conc_ofdm_option.var_enum.NONE

    def calc_ofdm_stf_length(self, model):
        #By default set this model variable to 4
        modulation_type = model.vars.modulation_type.value
        antdivmode = model.vars.antdivmode.value

        # Note that ofdm_stf_length is only set and used for OFDM PHYs (avoid clutter)
        if modulation_type == model.vars.modulation_type.var_enum.OFDM:
            if antdivmode == model.vars.antdivmode.var_enum.DISABLE:
                # 4 * 120 us symbol
                ofdm_stf_length = 4
            else:
                # Antenna diversity mode need longer STF length
                ofdm_stf_length = 10

            model.vars.ofdm_stf_length.value = ofdm_stf_length

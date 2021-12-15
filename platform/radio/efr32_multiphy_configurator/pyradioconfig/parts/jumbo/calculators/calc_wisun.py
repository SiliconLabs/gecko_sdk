from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from enum import Enum

class CALC_WiSUN_Jumbo(ICalculator):

    def buildVariables(self, model):
        var = self._addModelVariable(model, 'wisun_mode', Enum, ModelVariableFormat.DECIMAL, 'Wi-SUN Operating Mode (PhyMode)')
        member_data = [
            ['Mode1a', 0, '2FSK 50kbps mi=0.5'],
            ['Mode1b', 1, '2FSK 50kbps mi=1.0'],
            ['Mode2a', 2, '2FSK 100kbps mi=0.5'],
            ['Mode2b', 3, '2FSK 100kbps mi=1.0'],
            ['Mode3',  4, '2FSK 150kbps mi=0.5'],
            ['Mode4a', 5, '2FSK 200kbps mi=0.5'],
            ['Mode4b', 6, '2FSK 200kbps mi=1.0'],
            ['Mode5',  7, '2FSK 300kbps mi=0.5']
            ]
        var.var_enum = CreateModelVariableEnum(
            'WiSUNModeEnum',
            'List of supported WiSUN Modes',
            member_data)

        self._addModelVariable(model, 'wisun_phy_mode_id', int, ModelVariableFormat.DECIMAL, desc='WiSUN PhyModeID', is_array=True)
        self._addModelVariable(model, 'wisun_mode_switch_phr', int, ModelVariableFormat.DECIMAL, desc='WiSUN Mode Switch PHR', is_array=True)


    def calc_wisun_phy_mode_id(self, model):
        # This function calculates the PhyModeID for Wi-SUN OFDM and Wi-SUN FSK PHYs
        # For OFDM, the variable contains an array of MCS0-6 values
        # For FSK, the variable contains an array of FEC off/on values

        profile_name = model.profile.name.lower()

        if profile_name == "wisun":
            wisun_mode = model.vars.wisun_mode.value
            wisun_phy_mode_id = [0] * 2
            phy_mode =  int(wisun_mode) + 1
            wisun_phy_mode_id[0] = (0 << 4) | phy_mode
            wisun_phy_mode_id[1] = (1 << 4) | phy_mode

            #Write the variable
            model.vars.wisun_phy_mode_id.value = wisun_phy_mode_id

    def calc_wisun_mode_switch_phr(self, model):
        #This function calculates the PHR associated with the calculated PhyModeID
        #For OFDM, the variable contains an array of MCS0-6 values
        #For FSK, the variable contains an array of FEC off/on values

        profile_name = model.profile.name.lower()

        if "wisun" in profile_name:
            wisun_phy_mode_id = model.vars.wisun_phy_mode_id.value
            wisun_mode_switch_phr = []
            for phy_mode_id in wisun_phy_mode_id:
                wisun_mode_switch_phr.append(self._make_phr(phy_mode_id))

            #Write the variable
            model.vars.wisun_mode_switch_phr.value = wisun_mode_switch_phr

    def _make_phr(self, phy_mode_id):

        wisun_bch_gen_poly = 0b10011

        mode_switch_field = 0b1
        mode_switch_shift = 15

        reserved_field = 0b00
        reserved_shift = 13

        phy_mode_id_field = phy_mode_id
        phy_mode_id_shift = 5

        first_11_bits = ((mode_switch_field << mode_switch_shift) | (reserved_field << reserved_shift) | (phy_mode_id_field << phy_mode_id_shift)) >> 5
        checksum_field = self._get_bch_15_11_checksum(first_11_bits, wisun_bch_gen_poly)
        checksum_shift = 1

        first_15_bits = ((first_11_bits << 5) | (checksum_field << checksum_shift)) >> 1
        parity_field = self._get_parity(first_15_bits)
        parity_shift = 0

        phr = (first_15_bits << 1) | (parity_field << parity_shift)

        #Now we need to reverse the order of bits for transmission
        phr = int(format(phr, '016b')[::-1],2)

        return phr

    def _get_bch_15_11_checksum(self, data, gen_poly):
        #This function calculates the BCH checksum, which is the shifted data divided by the generator polynomial

        data_shifted = data << 4 #The 4 here comes from the BCH(15,11) definition as 4 = 15-11

        data_bits = len("{0:b}".format(data_shifted))
        gen_poly_bits = len("{0:b}".format(gen_poly))

        #Initialize checksum
        checksum = data_shifted

        #Shift gen polynomial to left align with data
        gen_poly_shifted = gen_poly << (data_bits - gen_poly_bits)

        for bit_position in range (data_bits-gen_poly_bits+1):
            if (checksum & (1<<(data_bits-bit_position-1))) != 0:
                #Only XOR if there is a 1 in the MSB of the current checksum
                checksum = checksum ^ (gen_poly_shifted >> bit_position)

        return checksum

    def _get_parity(self, data):

        #Optimized algorithm from Sophie Gault
        parity = 0
        while (data != 0):
            parity ^= 1  # toggle parity bit
            data = data & (data - 1)
        return parity

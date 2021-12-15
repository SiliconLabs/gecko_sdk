from pyradioconfig.parts.ocelot.calculators.calc_modulator import CALC_Modulator_Ocelot
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from math import ceil,log2
from enum import Enum

class Calc_Modulator_Sol(CALC_Modulator_Ocelot):

    def buildVariables(self, model):
        super().buildVariables(model)
        self._addModelVariable(model, 'ofdm_rate_hz', float, ModelVariableFormat.DECIMAL,
                               desc='OFDM rate for softmodem')
        self._addModelVariable(model, 'softmodem_tx_interpolation1',int,ModelVariableFormat.DECIMAL,desc='interpolation rate 1 for softmodem TX')
        self._addModelVariable(model, 'softmodem_tx_interpolation2', int, ModelVariableFormat.DECIMAL,
                               desc='interpolation rate 2 for softmodem TX')
        self._addModelVariable(model, 'softmodem_modulator_select', Enum, ModelVariableFormat.DECIMAL,
                               desc='determines modulator path for softmodem PHYs')
        model.vars.softmodem_modulator_select.var_enum = CreateModelVariableEnum(
            'SoftmodemModSelEnum',
            'List of softmodem modulator paths',
            [['IQ_MOD',0,'OFDM modulator'],
            ['LEGACY_MOD',1,'Legacy modulator'],
             ['NONE',2,'Not using softmodem']])

    def calc_softmodem_modulator_select(self, model):

        softmodem_modulation_type = model.vars.softmodem_modulation_type.value

        if (softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM) or \
            (softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.CW):
            softmodem_modulator_select = model.vars.softmodem_modulator_select.var_enum.IQ_MOD
        elif softmodem_modulation_type != model.vars.softmodem_modulation_type.var_enum.NONE:
            softmodem_modulator_select =  model.vars.softmodem_modulator_select.var_enum.LEGACY_MOD
        else:
            softmodem_modulator_select = model.vars.softmodem_modulator_select.var_enum.NONE

        #Write the model var
        model.vars.softmodem_modulator_select.value = softmodem_modulator_select

    def calc_txmodsel_reg(self, model):

        #Read in model vars
        softmodem_modulator_select = model.vars.softmodem_modulator_select.value

        if softmodem_modulator_select == model.vars.softmodem_modulator_select.var_enum.IQ_MOD:
            txmodsel = 0
        elif softmodem_modulator_select == model.vars.softmodem_modulator_select.var_enum.LEGACY_MOD:
            txmodsel = 1
        else:
            txmodsel = 0

        #Write the register
        self._reg_write(model.vars.RAC_SOFTMCTRL_TXMODSEL, txmodsel)

    def calc_softmodem_tx_interpolation(self, model):
        #This method calculates the interpolation rates for softmodem PHYs

        #Read in model vars
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        ofdm_option = model.vars.ofdm_option.value
        softmodem_modulator_select = model.vars.softmodem_modulator_select.value

        #Only need to set interpolation values for OFDM MOD
        if softmodem_modulator_select == model.vars.softmodem_modulator_select.var_enum.IQ_MOD:
            if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
                softmodem_tx_interpolation1 = 7 #Static for now
                if ofdm_option == model.vars.ofdm_option.var_enum.OPT1:
                    softmodem_tx_interpolation2 = 2
                elif ofdm_option == model.vars.ofdm_option.var_enum.OPT2:
                    softmodem_tx_interpolation2 = 4
                elif ofdm_option == model.vars.ofdm_option.var_enum.OPT3:
                    softmodem_tx_interpolation2 = 8
                else:
                    softmodem_tx_interpolation2 = 16
            else:
                softmodem_tx_interpolation1 = 1
                softmodem_tx_interpolation2 = 5
        else:
            softmodem_tx_interpolation1 = 0
            softmodem_tx_interpolation2 = 0

        #Write the model vars
        model.vars.softmodem_tx_interpolation1.value = softmodem_tx_interpolation1
        model.vars.softmodem_tx_interpolation2.value = softmodem_tx_interpolation2


    def calc_int1cfg_reg(self, model):
        #This method calculates the int1cfg register fields

        #Read in model vars
        softmodem_modulator_select = model.vars.softmodem_modulator_select.value
        softmodem_tx_interpolation1 = model.vars.softmodem_tx_interpolation1.value

        # Set only when OFDM modulator is used
        if softmodem_modulator_select == model.vars.softmodem_modulator_select.var_enum.IQ_MOD:
            ratio = softmodem_tx_interpolation1-1
            gainshift = 12 #Static for now
        else:
            ratio=0
            gainshift=0

        #Write the registers
        self._reg_write(model.vars.TXFRONT_INT1CFG_RATIO,ratio)
        self._reg_write(model.vars.TXFRONT_INT1CFG_GAINSHIFT, gainshift)

    def calc_int2cfg_reg(self, model):
        #This method calculates the int2cfg register fields

        #Read in model vars
        softmodem_modulator_select = model.vars.softmodem_modulator_select.value
        softmodem_tx_interpolation2 = model.vars.softmodem_tx_interpolation2.value

        # Set only when OFDM modulator is used
        if softmodem_modulator_select == model.vars.softmodem_modulator_select.var_enum.IQ_MOD:
            ratio = softmodem_tx_interpolation2-1
            gainshift = ceil(log2(softmodem_tx_interpolation2**2))
        else:
            ratio = 0
            gainshift = 0

        #Write the registers
        self._reg_write(model.vars.TXFRONT_INT2CFG_RATIO, ratio)
        self._reg_write(model.vars.TXFRONT_INT2CFG_GAINSHIFT, gainshift)

    def calc_srccfg_ratio_reg(self, model):
        #This method calulates the softmodem SRCCFG RATIO value

        #Read in model vars
        softmodem_modulator_select = model.vars.softmodem_modulator_select.value
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        dac_freq_actual = model.vars.dac_freq_actual.value
        baudrate = model.vars.baudrate.value
        softmodem_tx_interpolation1 = model.vars.softmodem_tx_interpolation1.value
        softmodem_tx_interpolation2 = model.vars.softmodem_tx_interpolation2.value

        # Set only when OFDM modulator is used
        if softmodem_modulator_select == model.vars.softmodem_modulator_select.var_enum.IQ_MOD:
            if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
                ratio = (2**18) * (2.0*baudrate*softmodem_tx_interpolation1*softmodem_tx_interpolation2)/dac_freq_actual #2^18 * (2*OFDM_RATE*INT1*INT2)/DAC_FREQ
            else:
                ratio = (2**18) #Ratio of 1 for CW
        else:
            ratio = 0

        #Write the reg
        self._reg_write(model.vars.TXFRONT_SRCCFG_RATIO, int(ratio))

    def calc_txmix_regs(self, model):
        #This method calculates the RAC_TXMIX fields as well as the RAC_PATRIM6_TXTRIMFILGAIN field

        softmodem_modulator_select = model.vars.softmodem_modulator_select.value
        base_frequency_hz = model.vars.base_frequency_hz.value

        #Choose regsiter settings based on RF band
        if softmodem_modulator_select == model.vars.softmodem_modulator_select.var_enum.IQ_MOD:

            if base_frequency_hz < 450e6:
                #430M Band
                txtrimfilgain = 1
                txselmixctune = 43
                txselmixgmslicei = 9
                txselmixgmsliceq = 9
                txselmixrload = 0
                txselmixband = 0

            elif base_frequency_hz < 520e6:
                # 470M Band
                txtrimfilgain = 1
                txselmixctune = 31
                txselmixgmslicei = 8
                txselmixgmsliceq = 8
                txselmixrload = 0
                txselmixband = 0

            elif base_frequency_hz < 625e6:
                # 570M Band
                txtrimfilgain = 1
                txselmixctune = 13
                txselmixgmslicei = 6
                txselmixgmsliceq = 6
                txselmixrload = 2
                txselmixband = 0

            elif base_frequency_hz < 730e6:
                # 680M Band
                txtrimfilgain = 1
                txselmixctune = 3
                txselmixgmslicei = 6
                txselmixgmsliceq = 6
                txselmixrload = 5
                txselmixband = 0

            elif base_frequency_hz < 825e6:
                # 780M Band
                txtrimfilgain = 1
                txselmixctune = 24
                txselmixgmslicei = 7
                txselmixgmsliceq = 7
                txselmixrload = 1
                txselmixband = 1

            elif base_frequency_hz < 895e6:
                # 870M Band
                txtrimfilgain = 1
                txselmixctune = 14
                txselmixgmslicei = 6
                txselmixgmsliceq = 6
                txselmixrload = 2
                txselmixband = 1

            elif base_frequency_hz < 940e6:
                # 920M Band (settings from Eric Vapillon)
                txtrimfilgain = 2
                txselmixctune = 11
                txselmixgmslicei = 4
                txselmixgmsliceq = 4
                txselmixrload = 4
                txselmixband = 1

            else:
                # 960M Band
                txtrimfilgain = 1
                txselmixctune = 5
                txselmixgmslicei = 6
                txselmixgmsliceq = 6
                txselmixrload = 5
                txselmixband = 1

        else:
            #Use POR values
            txtrimfilgain = 1
            txselmixctune = 0
            txselmixgmslicei = 4
            txselmixgmsliceq = 4
            txselmixrload = 0
            txselmixband = 0

        #Write the register fields
        self._reg_write(model.vars.RAC_PATRIM6_TXTRIMFILGAIN, txtrimfilgain)
        self._reg_write(model.vars.RAC_TXMIX_TXSELMIXCTUNE, txselmixctune)
        self._reg_write(model.vars.RAC_TXMIX_TXSELMIXGMSLICEI, txselmixgmslicei)
        self._reg_write(model.vars.RAC_TXMIX_TXSELMIXGMSLICEQ, txselmixgmsliceq)
        self._reg_write(model.vars.RAC_TXMIX_TXSELMIXRLOAD, txselmixrload)
        self._reg_write(model.vars.RAC_TXMIX_TXSELMIXBAND, txselmixband)
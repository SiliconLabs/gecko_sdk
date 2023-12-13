from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from pyradioconfig.parts.bobcat.calculators.calc_synth import Calc_Synth_Bobcat


class CalcSynthRainier(Calc_Synth_Bobcat):

    def buildVariables(self, model):
        """Populates a list of needed variables for this calculator
        Args:
            model (ModelRoot) : Builds the variables specific to this calculator
        """

        # Build variables from Lynx
        calc_synth_Bobcat_obj = Calc_Synth_Bobcat()
        calc_synth_Bobcat_obj.buildVariables(model)

        self._addModelVariable(model, 'adc_constrain_xomult', bool, ModelVariableFormat.DECIMAL,
                               desc='Flag used internally to constrain ADC clock to multiple of HFXO')

        # : Modify tx synth modes from Bobcat
        model.vars.synth_tx_mode.var_enum = CreateModelVariableEnum(
            enum_name='SynthTxModeEnum',
            enum_desc='Defined Synth TX Mode',
            member_data=[
                ['MODE1', 0, 'TX Mode 1'],           # IQMOD
                ['MODE2', 1, 'TX Mode 2'],           # 1MHZ
                ['MODE3', 2, 'TX Mode 3'],           # 2MHZ
                ['MODE4', 3, 'TX Mode 4'],
                ['MODE_BLE', 1, 'TX BLE Mode'],
                ['MODE_BLE_FULLRATE', 1, 'TX BLE Fullrate Mode'],
                ['MODE_IEEE802154', 2, 'TX IEEE802154 Mode'],
            ])
        model.vars.synth_tx_mode_actual.var_enum = model.vars.synth_tx_mode.var_enum
    def calc_adcenhalfmode_reg(self, model):

        adc_rate_mode = model.vars.adc_rate_mode.value

        if adc_rate_mode == model.vars.adc_rate_mode.var_enum.HALFRATE:
            reg = 1
        else:
            reg = 0

        self._reg_write(model.vars.RAC_ADCCTRL1_ADCENHALFMODE, reg)

    def calc_adcclksel_reg(self, model):
        adc_clock_mode_actual = model.vars.adc_clock_mode_actual.value

        if adc_clock_mode_actual == model.vars.adc_clock_mode.var_enum.VCODIV:
            reg = 0
        else:
            reg = 1
        self._reg_write(model.vars.RAC_ADCCTRL0_ADCCLKSEL, reg)

    def calc_clkmult_div_reg(self, model):
        adc_clock_mode_actual = model.vars.adc_clock_mode_actual.value
        ifadc_halfrate = model.vars.RAC_ADCCTRL1_ADCENHALFMODE.value

        if adc_clock_mode_actual == model.vars.adc_clock_mode.var_enum.HFXOMULT:
            if ifadc_halfrate == 0:
                # adc_full_speed from dpll_utils.py (xo * 8); 8 = 48 / (3 * 2)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTDIVR, 1)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTDIVN, 48)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTDIVX, 3)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTFREQCAL, 1)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTBWCAL, 1)
            else:
                # adc_half_speed from dpll_utils.py (xo * 4); 4 = 40 / (5 * 2)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTDIVR, 1)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTDIVN, 40)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTDIVX, 5)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTFREQCAL, 0)
                self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTBWCAL, 0)
        else:
            # reset values
            self._reg_write_default(model.vars.RAC_CLKMULTEN1_CLKMULTDIVR)
            self._reg_write_default(model.vars.RAC_CLKMULTEN1_CLKMULTDIVN)
            self._reg_write_default(model.vars.RAC_CLKMULTEN1_CLKMULTDIVX)
            self._reg_write_default(model.vars.RAC_CLKMULTEN1_CLKMULTFREQCAL)
            self._reg_write_default(model.vars.RAC_CLKMULTEN1_CLKMULTBWCAL)

    def calc_clkmulten_reg(self, model):
        adc_clock_mode_actual = model.vars.adc_clock_mode_actual.value

        # To enable clkmult the following additional registers must also be set, but are handled in RAIL
        # SYXO0.INTERNALCTRL.ENCLKMULTANA = 1 # enable XO output to CLKMULT
        # RAC.SYLOEN.SYLODIVRLO2P4GENEN = 0 # disable LODIV output buffer from SYLODIV (power saving)

        if adc_clock_mode_actual == model.vars.adc_clock_mode.var_enum.HFXOMULT:
            # unless otherwise specified, the values are taken from dualbclk_mult_validation_20190516_lynx_revA0.pptx > dpll_utils.py > dualbclk_mult spec sheet
            # based on the common settings for adc_full_speed, adc_full_speed_lp, adc_half_speed, adc_half_speed_lp
            # in dpll_utils.py
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTDISICO, 0) # 0 = ENABLE ICO, 1 = DISABLE ICO
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENBBDET, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENBBXLDET, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENBBXMDET, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENCFDET, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENDITHER, 0)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVADC, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVN, 0)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVP, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G, 0)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVRXSUBG, 0)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVTXDUALB, 0)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENFBDIV, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENREFDIV, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENREG1, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENREG2, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENREG3, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENROTDET, 1)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ, 0)

            # regulators set to max voltage, current for hot temp performance EFRPTE-6618
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTREG1ADJV, 3)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTREG2ADJV, 3)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTREG2ADJI, 3)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTREG3ADJV, 3)

            self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTINNIBBLE, 8)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTLDFNIB, 0)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTLDMNIB, 0)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTRDNIBBLE, 3)
            self._reg_write(model.vars.RAC_CLKMULTEN0_CLKMULTLDCNIB, 0)
            self._reg_write(model.vars.RAC_CLKMULTEN1_CLKMULTDRVAMPSEL, 7) # based on dpll_utils.py

            self._reg_write(model.vars.RAC_CLKMULTCTRL_CLKMULTENRESYNC, 0)
            self._reg_write(model.vars.RAC_CLKMULTCTRL_CLKMULTVALID, 0)
        else:
            # when using lodiv, turn off dualbclk_mult to reset values
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTDISICO)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENBBDET)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENBBXLDET)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENBBXMDET)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENCFDET)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENDITHER)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVADC)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVN)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVP)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVRXSUBG)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENDRVTXDUALB)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENFBDIV)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENREFDIV)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENREG1)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENREG2)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENREG3)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENROTDET)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTREG1ADJV)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTREG2ADJV)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTREG2ADJI)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTREG3ADJV)

            self._reg_write_default(model.vars.RAC_CLKMULTEN1_CLKMULTINNIBBLE)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTLDFNIB)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTLDMNIB)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTRDNIBBLE)
            self._reg_write_default(model.vars.RAC_CLKMULTEN0_CLKMULTLDCNIB)
            self._reg_write_default(model.vars.RAC_CLKMULTEN1_CLKMULTDRVAMPSEL)

            self._reg_write_default(model.vars.RAC_CLKMULTCTRL_CLKMULTENRESYNC)
            self._reg_write_default(model.vars.RAC_CLKMULTCTRL_CLKMULTVALID)

    def calc_rx_mode_reg(self, model):

        rx_mode = model.vars.synth_rx_mode.value
        ind = rx_mode.value

        # Synth settings https://jira.silabs.com/browse/MCUW_RADIO_CFG-1529
        # Settings copied over from Lynx Assert
        # {workspace}\shared_files\lynx\radio_validation\ASSERTS
        # BLK_SYNTH_RX_LP_BW_200KHZ.csv (BLE_LR mode)
        # BLK_SYNTH_RX_LP_BW_250KHZ.csv (NORMAL mode)

        rx_mode_settings = {
            'SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR2': [15, 15],
            'SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR3': [11, 11],
            'SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR4': [11, 11],
            'SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR5': [11, 11],
            'SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR6': [7, 7],
            'SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR7': [7, 7],
            'SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR8': [7, 7],
            'SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR9': [6, 6],
            'SYNTH.DSMCTRLRX.LSBFORCERX': [1, 1],
            'SYNTH.DSMCTRLRX.DEMMODERX': [1, 1],
            'RAC.SYMMDCTRL.SYMMDMODERX': [4, 4],
            'RAC.SYTRIM1.SYLODIVLDOTRIMNDIORX': [1, 1],

        }
        self._reg_write(model.vars.SYNTH_DLFCTRLRX_RXLOCKLPFBWGEAR2,
                        rx_mode_settings['SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR2'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLRX_RXLOCKLPFBWGEAR3,
                        rx_mode_settings['SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR3'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLRX_RXLOCKLPFBWGEAR4,
                        rx_mode_settings['SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR4'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLRX_RXLOCKLPFBWGEAR5,
                        rx_mode_settings['SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR5'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLRX_RXLOCKLPFBWGEAR6,
                        rx_mode_settings['SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR6'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLRX_RXLOCKLPFBWGEAR7,
                        rx_mode_settings['SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR7'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLRX_RXLOCKLPFBWGEAR8,
                        rx_mode_settings['SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR8'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLRX_RXLOCKLPFBWGEAR9,
                        rx_mode_settings['SYNTH.DLFCTRLRX.RXLOCKLPFBWGEAR9'][ind])

        # : Following registers are PTE Set & Forget but needs to be set by RC since they are different from reset value
        # : See https://jira.silabs.com/browse/MCUW_RADIO_CFG-1610
        self._reg_write(model.vars.SYNTH_DSMCTRLRX_LSBFORCERX, rx_mode_settings['SYNTH.DSMCTRLRX.LSBFORCERX'][ind])
        self._reg_write(model.vars.SYNTH_DSMCTRLRX_DEMMODERX, rx_mode_settings['SYNTH.DSMCTRLRX.DEMMODERX'][ind])

        # self._reg_write(model.vars.RAC_SYMMDCTRL_SYMMDMODERX,         rx_mode_settings['RAC.SYMMDCTRL.SYMMDMODERX'][ind])
        self._reg_write(model.vars.RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX,
                        rx_mode_settings['RAC.SYTRIM1.SYLODIVLDOTRIMNDIORX'][ind])

    def calc_tx_mode(self, model):
        modulator_select = model.vars.modulator_select.value
        baudrate = model.vars.baudrate.value
        modulation_type = model.vars.modulation_type.value

        if modulator_select == model.vars.modulator_select.var_enum.IQ_MOD:
            model.vars.synth_tx_mode.value = model.vars.synth_tx_mode.var_enum.MODE1
        # Set FSK and OQPSK settings based on baudrate
        else:
            if baudrate > 1000e3:
                model.vars.synth_tx_mode.value = model.vars.synth_tx_mode.var_enum.MODE3  # 2.5 MHz
            elif baudrate > 500e3:
                model.vars.synth_tx_mode.value = model.vars.synth_tx_mode.var_enum.MODE2  # 1.5 MHz
            else:
                model.vars.synth_tx_mode.value = model.vars.synth_tx_mode.var_enum.MODE1  # 1 MHz

    def calc_tx_mode_reg(self, model):
        ind = model.vars.synth_tx_mode.value

        # Synth settings https://jira.silabs.com/browse/MCUW_RADIO_CFG-1529
        # Settings copied over from Lynx Assert
        # {workspace}\shared_files\lynx\radio_validation\ASSERTS
        # BLK_SYNTH_TX_BW_1000KHZ.csv (MODE 1)
        # BLK_SYNTH_TX_BW_2000KHZ.csv (MODE 2)
        # BLK_SYNTH_TX_BW_2500KHZ.csv (MODE 3)
        # BLK_SYNTh_TX_BW_3000KHZ.csv (MODE 4)

        tx_mode_settings = {
            'SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR2': [15, 15, 15, 15],
            'SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR3': [12, 12, 14, 14],
            'SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR4': [12, 12, 14, 14],
            'SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR5': [12, 12, 14, 14],
            'SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR6': [10, 10, 13, 13],
            'SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR7': [10, 10, 13, 13],
            'SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR8': [10, 10, 13, 13],
            'SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR9': [8, 9, 12, 13],
            'SYNTH.DLFCTRL.LOCKLPFBWGEARSLOT': [1, 1, 1, 1],
            'SYNTH.DLFCTRL.LPFBWLOADDEL': [1, 1, 1, 1],

            'SYNTH.DSMCTRLTX.LSBFORCETX': [1, 1, 1, 1],
            'SYNTH.DSMCTRLTX.DEMMODETX': [1, 1, 1, 1],
        }

        self._reg_write(model.vars.SYNTH_DLFCTRLTX_TXLOCKLPFBWGEAR2,
                        tx_mode_settings['SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR2'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLTX_TXLOCKLPFBWGEAR3,
                        tx_mode_settings['SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR3'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLTX_TXLOCKLPFBWGEAR5,
                        tx_mode_settings['SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR5'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLTX_TXLOCKLPFBWGEAR6,
                        tx_mode_settings['SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR6'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLTX_TXLOCKLPFBWGEAR7,
                        tx_mode_settings['SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR7'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLTX_TXLOCKLPFBWGEAR8,
                        tx_mode_settings['SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR8'][ind])
        self._reg_write(model.vars.SYNTH_DLFCTRLTX_TXLOCKLPFBWGEAR9,
                        tx_mode_settings['SYNTH.DLFCTRLTX.TXLOCKLPFBWGEAR9'][ind])

        # : Following registers are PTE Set & Forget but needs to be set by RC since they are different from reset value
        # : See https://jira.silabs.com/browse/MCUW_RADIO_CFG-1610
        self._reg_write(model.vars.SYNTH_DSMCTRLTX_LSBFORCETX, tx_mode_settings['SYNTH.DSMCTRLTX.LSBFORCETX'][ind])
        self._reg_write(model.vars.SYNTH_DSMCTRLTX_DEMMODETX, tx_mode_settings['SYNTH.DSMCTRLTX.DEMMODETX'][ind])

    def calc_dlf_ctrl(self, model):
        self._reg_write(model.vars.SYNTH_DLFCTRL_LOCKLPFBWGEARSLOT, 1)
        self._reg_write(model.vars.SYNTH_DLFCTRL_LPFBWLOADDEL, 1)
        self._reg_write(model.vars.SYNTH_DLFCTRL_LPFBWDURINGHOP, 15)
        self._reg_write(model.vars.SYNTH_DLFCTRL_LPFBWAFTERHOP, 8)
        self._reg_write(model.vars.SYNTH_HOPPING_HOPLPFBWGEARSLOT, 3)
        self._reg_write(model.vars.SYNTH_HOPPING_HOPHCAPDELAY, 4)
        self._reg_write(model.vars.SYNTH_HOPPING_HCAPRETIMESEL, 2)

    def calc_fcal_reg(self, model):
        self._reg_write(model.vars.SYNTH_FCALCTRL_FCALMODE, 1)
        ## NUMCYCLE
        self._reg_write(model.vars.SYNTH_LOCNTCTRL_NUMCYCLE, 5)
        self._reg_write(model.vars.SYNTH_LOCNTCTRL_NUMCYCLE1, 5)
        self._reg_write(model.vars.SYNTH_LOCNTCTRL_NUMCYCLE2, 5)
        self._reg_write(model.vars.SYNTH_LOCNTCTRL_NUMCYCLE3, 4)
        self._reg_write(model.vars.SYNTH_LOCNTCTRL_NUMCYCLE4, 4)
        self._reg_write(model.vars.SYNTH_LOCNTCTRL_NUMCYCLE5, 3)
        self._reg_write(model.vars.SYNTH_FCALCTRL_NUMCYCLE6, 3)
        self._reg_write(model.vars.SYNTH_FCALCTRL_NUMCYCLE7, 3)
        self._reg_write(model.vars.SYNTH_FCALCTRL_NUMCYCLE8, 2)
        self._reg_write(model.vars.SYNTH_FCALCTRL_NUMCYCLE9, 2)
        self._reg_write(model.vars.SYNTH_FCALCTRL_NUMCYCLE10, 2)
        ## COMPANION
        self._reg_write(model.vars.SYNTH_COMPANION_COMPANION0, 1)
        self._reg_write(model.vars.SYNTH_COMPANION_COMPANION1, 1)
        self._reg_write(model.vars.SYNTH_COMPANION_COMPANION2, 2)
        self._reg_write(model.vars.SYNTH_COMPANION_COMPANION3, 2)
        self._reg_write(model.vars.SYNTH_COMPANION_COMPANION4, 2)
        self._reg_write(model.vars.SYNTH_COMPANION_COMPANION5, 4)
        self._reg_write(model.vars.SYNTH_COMPANION_COMPANION6, 4)
        self._reg_write(model.vars.SYNTH_COMPANION_COMPANION7, 5)
        ## STEPWAIT
        self._reg_write(model.vars.SYNTH_FCALCTRL_STEPWAIT, 0)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT1, 0)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT2, 0)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT3, 1)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT4, 1)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT5, 2)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT6, 2)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT7, 3)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT8, 3)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT9, 4)
        self._reg_write(model.vars.SYNTH_FCALSTEPWAIT_STEPWAIT10, 4)

    def calc_lms_reg(self, model):
        self._reg_write(model.vars.SYNTH_GLMS_GLMSENABLEDELAY, 7)
        self._reg_write(model.vars.SYNTH_GLMS_GLMSGEAR0, 10)
        self._reg_write(model.vars.SYNTH_GLMS_GLMSGEAR1, 10)
        self._reg_write(model.vars.SYNTH_GLMS_GLMSGEAR2, 9)
        self._reg_write(model.vars.SYNTH_GLMS_GLMSGEAR3, 7)
        self._reg_write(model.vars.SYNTH_GLMS_GLMSGEAR4, 6)
        self._reg_write(model.vars.SYNTH_GLMS_GLMSGEARSLOT, 0)
        self._reg_write(model.vars.SYNTH_PLMS_PLMSENABLEDELAY, 7)
        self._reg_write(model.vars.SYNTH_PLMS_PLMSGEAR0, 11)
        self._reg_write(model.vars.SYNTH_PLMS_PLMSGEAR1, 10)
        self._reg_write(model.vars.SYNTH_PLMS_PLMSGEAR2, 9)
        self._reg_write(model.vars.SYNTH_PLMS_PLMSGEAR3, 8)
        self._reg_write(model.vars.SYNTH_PLMS_PLMSGEAR4, 6)
        self._reg_write(model.vars.SYNTH_PLMS_PLMSGEARSLOT, 0)

    def calc_s3_reg(self, model):
        self._reg_write(model.vars.SYNTH_MMDDENOMINIT_DENOMINIT0, 63)
        self._reg_write(model.vars.SYNTH_MMDDENOMINIT_DENOMINIT1, 64)
        self._reg_write(model.vars.SYNTH_QNCCTRL_ENABLEDQNCTIME, 5)

    def calc_synth_misc(self, model):
        pass

    def calc_pga_lna_bw_reg(self, model):
        # Removed LNABWADJ and LNABWADJBOOST (IPMCUSRW-1189)
        pgabwmode = 1
        self._reg_write(model.vars.RAC_PGACTRL_PGABWMODE, pgabwmode)

    def calc_fasthopping_regs(self, model):
        # Disable by default, probably remove these for RAIL control at some point
        self._reg_write(model.vars.MODEM_PHDMODCTRL_FASTHOPPINGEN, 0)
        self._reg_write(model.vars.MODEM_CMD_HOPPINGSTART, 0)
        self._reg_write(model.vars.MODEM_DIGMIXCTRL_FWHOPPING, 0)

    def calc_adc_rate_mode_actual(self, model):
        # This function calculates the actual value of the adc rate mode based on the reg value used
        ifadcenhalfmode = model.vars.RAC_IFADCTRIM0_IFADCENHALFMODE.value

        if ifadcenhalfmode == 1:
            adc_rate_mode_actual = model.vars.adc_rate_mode.var_enum.HALFRATE
        else:
            adc_rate_mode_actual = model.vars.adc_rate_mode.var_enum.FULLRATE

        # Write the variable
        model.vars.adc_rate_mode_actual.value = adc_rate_mode_actual
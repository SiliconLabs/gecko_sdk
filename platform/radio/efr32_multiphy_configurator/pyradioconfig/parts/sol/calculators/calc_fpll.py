from pyradioconfig.calculator_model_framework.Utils.CustomExceptions import CalculationException
from pyradioconfig.parts.ocelot.calculators.calc_fpll import calc_fpll_ocelot
from pycalcmodel.core.variable import ModelVariableFormat

class calc_fpll_sol(calc_fpll_ocelot):

    def buildVariables(self, model):

        #Build variables from Ocelot
        super().buildVariables(model)

        #Add calculator model variables
        self._addModelVariable(model, 'fpll_vco_freq_actual', float, ModelVariableFormat.DECIMAL, units='Hz', desc='VCO frequency')
        self._addModelVariable(model, 'dac_freq_actual', float, ModelVariableFormat.DECIMAL, units='Hz', desc='DAC frequency')

    def calc_fpll_dividers(self, model):

        rf_freq = model.vars.base_frequency_hz.value
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        if xtal_frequency_hz == 38e6:
            if ( rf_freq < 200e6 ):        # band_169
                divx = 6
                divy = 20
                divn = 101
            elif (rf_freq < 470e6):        # band_450
                divx = 7
                divy = 23
                divn = 118
            elif (rf_freq < 600e6):        # band_470
                divx = 6
                divy = 19
                divn = 98
            elif (rf_freq < 800e6):         # band_780
                divx = 7
                divy = 23
                divn = 118
            elif (rf_freq < 880e6 ):        # band_863
                divx = 6
                divy = 20
                divn = 101
            elif (rf_freq < 901e6):        # band_896
                divx = 7
                divy = 23
                divn = 118
            elif (rf_freq < 928e6 ):        # band_9xx
                divx = 6
                divy = 20
                divn = 103
            else:                           # band_928
                divx = 7
                divy = 23
                divn = 118
        elif xtal_frequency_hz == 38.4e6:
            if ( rf_freq < 200e6 ):        # band_169
                divx = 6
                divy = 20
                divn = 100
            elif (rf_freq < 470e6):        # band_450
                divx = 6
                divy = 20
                divn = 100
            elif (rf_freq < 600e6):        # band_470
                divx = 6
                divy = 19
                divn = 97
            elif (rf_freq < 800e6):         # band_780
                divx = 6
                divy = 20
                divn = 100
            elif (rf_freq < 880e6 ):        # band_863
                divx = 6
                divy = 20
                divn = 100
            elif (rf_freq < 901e6):        # band_896
                divx = 6
                divy = 20
                divn = 100
            elif (rf_freq < 928e6 ):        # band_9xx
                divx = 5
                divy = 17
                divn = 85
            else:                           # band_928
                divx = 7
                divy = 23
                divn = 117
        elif xtal_frequency_hz == 39e6:
            if ( rf_freq < 200e6 ):        # band_169
                divx = 6
                divy = 20
                divn = 98
            elif (rf_freq < 470e6):        # band_450
                divx = 7
                divy = 23
                divn = 114
            elif (rf_freq < 600e6):        # band_470
                divx = 7
                divy = 22
                divn = 111
            elif (rf_freq < 800e6):         # band_780
                divx = 7
                divy = 23
                divn = 115
            elif (rf_freq < 880e6 ):        # band_863
                divx = 6
                divy = 20
                divn = 98
            elif (rf_freq < 901e6):        # band_896
                divx = 7
                divy = 23
                divn = 115
            elif (rf_freq < 928e6 ):        # band_9xx
                divx = 6
                divy = 20
                divn = 100
            else:                           # band_928
                divx = 6
                divy = 20
                divn = 99
        elif xtal_frequency_hz == 40e6:
            if ( rf_freq < 200e6 ):        # band_169
                divx = 5
                divy = 16
                divn = 80
            elif (rf_freq < 470e6):        # band_450
                divx = 5
                divy = 16
                divn = 80
            elif (rf_freq < 600e6):        # band_470
                divx = 6
                divy = 19
                divn = 93
            elif (rf_freq < 800e6):         # band_780
                divx = 5
                divy = 16
                divn = 80
            elif (rf_freq < 880e6 ):        # band_863
                divx = 5
                divy = 16
                divn = 80
            elif (rf_freq < 901e6):        # band_896
                divx = 5
                divy = 16
                divn = 80
            elif (rf_freq < 928e6 ):        # band_9xx
                divx = 5
                divy = 17
                divn = 81
            else:                           # band_928
                divx = 5
                divy = 16
                divn = 80
        else:
            raise CalculationException('XTAL frequency not supported in calc_xtal_pll.py')

        self._reg_write(model.vars.RFFPLL0_RFFPLLCTRL1_DIVX, divx)
        self._reg_write(model.vars.RFFPLL0_RFFPLLCTRL1_DIVY, divy)
        self._reg_write(model.vars.RFFPLL0_RFFPLLCTRL1_DIVN, divn)
        self._reg_write(model.vars.RFFPLL0_RFFPLLCTRL1_DIVXMODEMSEL, 1) #Corresponds to divider of 2
        self._reg_write(model.vars.RFFPLL0_RFFPLLCTRL1_DIVXDACSEL, 7) #Corresponds to divider of 8

    def calc_fpll_vco_freq_actual(self, model):

        #Read in model variables
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value
        divn = model.vars.RFFPLL0_RFFPLLCTRL1_DIVN.value
        divr = 2 #Make assumption here

        #Calculate the VCO frequency given PLL settings
        fvco = xtal_frequency_hz * divn / divr #Pull range 1.6 - 2.25GHz

        #Write the model variable
        model.vars.fpll_vco_freq_actual.value = fvco

    def calc_adc_freq_actual(self, model):

        #Read in model variables
        fvco = model.vars.fpll_vco_freq_actual.value
        divx = model.vars.RFFPLL0_RFFPLLCTRL1_DIVX.value
        divxadcsel = model.vars.RFFPLL0_RFFPLLCTRL1_DIVXADCSEL.value + 1
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value
        rx_ifadc_en_xo_bypass = model.vars.RAC_IFADCTRIM1_IFADCENXOBYPASS.value
        fadc_target = model.vars.adc_target_freq.value
        fsynth = model.vars.rx_synth_freq_actual.value
        adc_vco_div_actual = model.vars.adc_vco_div_actual.value
        adc_clock_mode_actual = model.vars.adc_clock_mode_actual.value

        # Calculate ADC rate based on xtal PLL settings
        fadc = fvco / divx / divxadcsel         # ADC clock frequency

        # If using XO bypass, then calculate ADC rate based on xtal only
        if adc_clock_mode_actual == model.vars.adc_clock_mode.var_enum.HFXOMULT:
            if 1 == rx_ifadc_en_xo_bypass:
                adc_freq_actual = xtal_frequency_hz
            else:
                adc_freq_actual = int(fadc)
        else:
            adc_freq_actual = int(fsynth / adc_vco_div_actual)

        # Compute the final ADC frequency percent error
        ferror = 100 * (fadc_target - adc_freq_actual) / float(fadc_target)

        # Load local variables back into model variables
        model.vars.adc_freq_actual.value = adc_freq_actual
        model.vars.adc_freq_error.value = ferror

        return

    def calc_dac_freq_actual(self, model):

        # Read in model variables
        fvco = model.vars.fpll_vco_freq_actual.value
        divx = model.vars.RFFPLL0_RFFPLLCTRL1_DIVX.value
        divxdacsel = model.vars.RFFPLL0_RFFPLLCTRL1_DIVXDACSEL.value + 1

        # Calculate the DAC frequency given PLL settings
        fdac = fvco / divx / divxdacsel  # DAC clock frequency

        # Write model variables
        model.vars.dac_freq_actual.value = fdac

    def calc_modem_freq_actual(self, model):

        # Read in model variables
        fvco = model.vars.fpll_vco_freq_actual.value
        divx = model.vars.RFFPLL0_RFFPLLCTRL1_DIVX.value
        divmodemsel = model.vars.RFFPLL0_RFFPLLCTRL1_DIVXMODEMSEL.value + 1

        # Calculate the softmodem rate given the xtal pll settings
        fmodem = fvco / divx / divmodemsel  # modem clock frequency

        # Write model variables
        model.vars.hardmodem_freq_actual.value = fmodem/4 #Assuming a divider of 4 for now even though this is programmable in FW
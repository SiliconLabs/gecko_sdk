from pyradioconfig.calculator_model_framework.interfaces.icalculator import ICalculator
from pycalcmodel.core.variable import ModelVariableFormat

class calc_fpll_ocelot(ICalculator):

    def buildVariables(self, model):

        # Add calculator model variables
        self._addModelVariable(model, 'hardmodem_freq_actual', float, ModelVariableFormat.DECIMAL, units='Hz', desc='Hard MODEM frequency')

    def calc_modem_freq_actual(self, model):

        #Read in model variables
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value

        #For Ocelot, the hard demod rate is simply the xtal frequency
        hardmodem_freq_actual = float(xtal_frequency_hz)

        #Write the model variable
        model.vars.hardmodem_freq_actual.value = hardmodem_freq_actual
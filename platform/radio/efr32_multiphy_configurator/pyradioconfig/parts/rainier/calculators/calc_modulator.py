from pyradioconfig.parts.common.calculators.calc_utilities import CALC_Utilities
from enum import Enum
from pycalcmodel.core.variable import ModelVariableFormat, CreateModelVariableEnum
from pyradioconfig.parts.bobcat.calculators.calc_modulator import Calc_Modulator_Bobcat


class CalcModulatorRainier(Calc_Modulator_Bobcat):

    def buildVariables(self, model):
        super().buildVariables(model)

        self._addModelVariable(model, 'modulator_select', Enum, ModelVariableFormat.DECIMAL,
                               desc='determines modulator path')
        self._addModelVariable(model, 'br2m', int, ModelVariableFormat.DECIMAL)
        model.vars.modulator_select.var_enum = CreateModelVariableEnum(
            'ModSelEnum',
            'List of supported modulator paths',
            [['PH_MOD', 0, 'Phase modulator'],
             ['IQ_MOD', 1, 'IQ modulator (direct upconversion)']])

    def calc_tx_mode(self, model):
        # IQ UPCONV by default
        model.vars.modulator_select.value = model.vars.modulator_select.var_enum.IQ_MOD

    def calc_txmod_reg(self, model):
        modulator_select = model.vars.modulator_select.value

        self._reg_write(model.vars.MODEM_TXMISC_TXMOD, int(modulator_select))

    def calc_tx_baud_rate_actual(self, model):
        """
        calculate actual TX baud rate from register settings

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        fxo = model.vars.xtal_frequency.value
        txbr_ratio = model.vars.txbr_ratio_actual.value
        interp_factor = 2.0 if model.vars.br2m.value else 4.0

        tx_baud_rate = fxo / interp_factor / 8.0 * txbr_ratio

        model.vars.tx_baud_rate_actual.value = tx_baud_rate

    def calc_tx_br2m(self, model):
        """
        calculate br2m value

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """
        baudrate = model.vars.baudrate.value
        if baudrate >= 2000000:
            br2m = 1
        else:
            br2m = 0

        model.vars.br2m.value = br2m
        self._reg_write(model.vars.MODEM_TXMISC_BR2M, int(br2m))

    def calc_modindex_value(self, model):
        """
        calculate MODINDEX value
        Equations from Table 5.25 in EFR32 Reference Manual (internal.pdf)

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        fxo = model.vars.xtal_frequency.value * 1.0
        modformat = model.vars.modulation_type.value
        freq_dev_hz = model.vars.deviation.value * 1.0
        shaping_filter_gain = model.vars.shaping_filter_gain_iqmod_actual.value
        baudrate = model.vars.baudrate.value
        modulator_select = model.vars.modulator_select.value

        if modformat == model.vars.modulation_type.var_enum.OQPSK:
            # (1 / 2 * 0.5 * baud) / (shape_gain * conv_gain * freq_resoluion),
            # conv_gain = (T_fxo * 2 / T_shape), freq --> phase --> freq
            modindex = 0.5 / 2.0 / shaping_filter_gain / 8.0
        elif baudrate >= 2000000:
            modindex = freq_dev_hz / shaping_filter_gain / (fxo / 2.0)
        else:
            modindex = freq_dev_hz / shaping_filter_gain / (fxo / 4.0)

        # gain adjustment for different modulation
        if modulator_select == model.vars.modulator_select.var_enum.IQ_MOD:
            if modformat == model.vars.modulation_type.var_enum.OQPSK:
                gain_adj = 1.0
            elif baudrate >= 2000000:
                gain_adj = 0.5 / 0.4830  # for better mean value of DF1
            else:
                gain_adj = 0.5 / 0.4858

        else:  # PHMOD
            if baudrate == 1000000:
                gain_adj = 1.0 / 4.0
            else:
                gain_adj = 0.5  # conversion gain adjustment since phmod modindex multiplier @ fxo

        model.vars.modindex.value = modindex * gain_adj

    def calc_modindex_field(self, model):
        """
        convert desired modindex fractional value to MODINDEXM * 2^MODINDEXE
        Equations (5.13) of EFR32 Reference Manual (internal.pdf)

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        modindex = model.vars.modindex.value

        # convert fractional modindex into m * 2^e format
        m, e = CALC_Utilities().frac2exp(31, modindex, up=True)
        # flip sign of e for iqmod implementation
        # e = -e

        # src_out frac 11 bits to 19 frac for fixed point implementation.
        e = e + 8

        # MODEINDEXE is a signed value
        if e < 0:
            e += 32

        # verify number fits into register
        if m > 255:
            m = 255

        if e > 31:
            e = 31

        if m < 0:
            m = 0

        self._reg_write(model.vars.MODEM_MODINDEX_MODINDEXM, int(m))
        self._reg_write(model.vars.MODEM_MODINDEX_MODINDEXE, int(e))

    def calc_modindex_actual(self, model):
        """
        given register settings return actual MODINDEX as fraction
        Equations (5.13) of EFR32 Reference Manual (internal.pdf)

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        m = model.vars.MODEM_MODINDEX_MODINDEXM.value
        e = model.vars.MODEM_MODINDEX_MODINDEXE.value

        # MODEINDEXE is a signed value
        if e > 15:
            e -= 32

        model.vars.modindex_actual.value = 1.0 * m / 2 ** (19 - 11) * 2 ** e

    def calc_tx_freq_dev_actual(self, model):
        """
        given register setting return actual frequency deviation used in the modulator
        Using Equations in Table 5.25 of EFR32 Reference Manual (internal.pdf)

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """
        fxo = model.vars.xtal_frequency.value * 1.0
        modformat = model.vars.modulation_type.value
        modindex = model.vars.modindex_actual.value
        shaping_filter_gain = model.vars.shaping_filter_gain_iqmod_actual.value
        br2m = model.vars.br2m.value
        modulator_select = model.vars.modulator_select.value

        if modulator_select == model.vars.modulator_select.var_enum.IQ_MOD:
            mod_samp_rate = fxo / 2  # IQMOD
        else:
            mod_samp_rate = fxo  # PHMOD

        if modformat == model.vars.modulation_type.var_enum.FSK2 or \
                modformat == model.vars.modulation_type.var_enum.FSK4:
            freq_dev_hz = modindex * (mod_samp_rate * shaping_filter_gain) / 2 ** (1.0 - br2m)
        else:
            freq_dev_hz = 0.0

        model.vars.tx_deviation_actual.value = freq_dev_hz

    def calc_txbr_value(self, model):
        # Overriding this function due to variable name change

        # Load model values into local variables
        xtal_frequency_hz = model.vars.xtal_frequency_hz.value
        baudrate = model.vars.baudrate.value

        # calculate baudrate to fxo ratio
        # For the phase modulator this should always be based on xtal rate (https://jira.silabs.com/browse/MCUW_RADIO_CFG-1626)
        interp_factor = 2.0 if model.vars.br2m.value else 4.0
        ratio = (8.0 * baudrate) / (xtal_frequency_hz / interp_factor)
        # Load local variables back into model variables
        model.vars.txbr_ratio.value = ratio

    def calc_txbr_reg(self, model):
        """
        given desired TX baudrate ratio calculate TXBRNUM and TXBRDEN
        that gets as close as possible to the ratio.
        Note that we start from the highest possible value for TXBRDEN
        and go down since having largest possible values in these register
        to have better phase resolution in OQPSK and MSK (see end of section
        5.6.5 in the manual)

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        ratio = model.vars.txbr_ratio.value
        self._reg_write(model.vars.MODEM_TXBR_TXBRNUM, int(round(ratio * 2 ** 16)))

    def calc_txbr_actual(self, model):
        """
        given register values calculate actual TXBR ratio implemented

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        num = model.vars.MODEM_TXBR_TXBRNUM.value * 1.0
        ratio = num / (2 ** 16)
        model.vars.txbr_ratio_actual.value = ratio

from pyradioconfig.parts.common.calculators.frame_coding import CALC_Whitening

class CALC_Frame_Coding_Ocelot(CALC_Whitening):

    def calc_frame_coding_var(self, model):
        #On Ocelot, we removed frame_coding as a Profile Input, so we need to calculate the variable from symbol_encoding

        symbol_encoding = model.vars.symbol_encoding.value

        if symbol_encoding == model.vars.symbol_encoding.var_enum.UART_NO_VAL:
            frame_coding = model.vars.frame_coding.var_enum.UART_NO_VAL
        elif symbol_encoding == model.vars.symbol_encoding.var_enum.UART_VAL:
            frame_coding = model.vars.frame_coding.var_enum.UART_VAL
        elif symbol_encoding == model.vars.symbol_encoding.var_enum.MBUS_3OF6:
            frame_coding = model.vars.frame_coding.var_enum.MBUS_3OF6
        else:
            frame_coding = model.vars.frame_coding.var_enum.NONE

        #Write the model variable
        model.vars.frame_coding.value = frame_coding

    def _frame_coding_manchester(self):
        # List the lookup data with 1-bit sequence as keys, 2-bit sequence as values.
        # From https://jira.silabs.com/browse/MCUW_RADIO_CFG-2046
        coding_table = {
            0b0: 0b01,
            0b1: 0b10
        }

        message_bits = 1
        coded_bits = 2
        array_width = 8
        coding_table_is_msb_first = True  # Presented as msb, but coded into the RAM as lsb

        return self._create_content_table(message_bits, coded_bits, array_width,
                                             coding_table_is_msb_first, coding_table)

    def calc_frame_coding(self, model):
        # In TRECS_VITERBI demod, the encoding of the data must be performed using the hardware block coder.

        symbol_encoding = model.vars.symbol_encoding.value
        demod_select = model.vars.demod_select.value

        FRAME_CODING_LOOKUP = {
            model.vars.symbol_encoding.var_enum.Manchester.value: (1, 2, 8, self._frame_coding_manchester),
            model.vars.symbol_encoding.var_enum.Inv_Manchester.value: (1, 2, 8, self._frame_coding_manchester)
        }

        if (symbol_encoding == model.vars.symbol_encoding.var_enum.Manchester or
            symbol_encoding == model.vars.symbol_encoding.var_enum.Inv_Manchester) and \
                demod_select == model.vars.demod_select.var_enum.TRECS_VITERBI:
            frameCodingParams = FRAME_CODING_LOOKUP[symbol_encoding]
            model.vars.frame_coding_message_bits.value = frameCodingParams[0]
            model.vars.frame_coding_coded_bits.value = frameCodingParams[1]
            model.vars.frame_coding_array_width.value = frameCodingParams[2]
            model.vars.frame_coding_array.value = frameCodingParams[3]()
        else:
            super().calc_frame_coding(model)

    def calc_frame_coding_array_packed(self, model):
        # Pack the frame coding values into 32 bits integers

        symbol_encoding = model.vars.symbol_encoding.value
        demod_select = model.vars.demod_select.value

        if (symbol_encoding == model.vars.symbol_encoding.var_enum.Manchester or
            symbol_encoding == model.vars.symbol_encoding.var_enum.Inv_Manchester) and \
                demod_select == model.vars.demod_select.var_enum.TRECS_VITERBI:

            coding_array = model.vars.frame_coding_array.value
            width = model.vars.frame_coding_array_width.value
            model.vars.frame_coding_array_packed.value = self.pack_list(coding_array, width)
        else:
            super().calc_frame_coding_array_packed(model)

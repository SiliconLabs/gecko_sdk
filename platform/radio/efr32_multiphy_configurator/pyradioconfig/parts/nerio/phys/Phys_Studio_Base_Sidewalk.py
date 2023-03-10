from pyradioconfig.calculator_model_framework.interfaces.iphy import IPhy

# Though this file/class is named "Studio", we actually only expose for later parts at this time
class Phys_Studio_Base_Sidewalk_Nerio(IPhy):

    def sidewalk_2fsk_base(self, model, phy):

        self._set_sidewalk_tolerances(model, phy)

        #Modulation
        phy.profile_inputs.modulation_type.value = model.vars.modulation_type.var_enum.FSK2
        phy.profile_inputs.fsk_symbol_map.value = model.vars.fsk_symbol_map.var_enum.MAP0

        #Preamble
        phy.profile_inputs.preamble_pattern.value = 1
        phy.profile_inputs.preamble_pattern_len.value = 2
        phy.profile_inputs.preamble_length.value = 8*8 #Planning for 8-octets at this point, may need to change

        #Syncword
        phy.profile_inputs.syncword_0.value = 0b1001000001001110
        phy.profile_inputs.syncword_1.value = 0x0
        phy.profile_inputs.syncword_length.value = 16

        #Xtal
        phy.profile_inputs.xtal_frequency_hz.value = 39000000

        #Encoding
        phy.profile_inputs.diff_encoding_mode.value = model.vars.diff_encoding_mode.var_enum.DISABLED
        phy.profile_inputs.dsss_chipping_code.value = 0
        phy.profile_inputs.dsss_len.value = 0
        phy.profile_inputs.dsss_spreading_factor.value = 0

        #Whitening
        phy.profile_inputs.white_poly.value = model.vars.white_poly.var_enum.PN9_802154
        phy.profile_inputs.white_seed.value = 0xFF  # This has been tested, need a 0 in position 8 due to EFR32 whitening architecture
        phy.profile_inputs.white_output_bit.value = 8

        #CRC
        phy.profile_inputs.payload_crc_en.value = True
        phy.profile_inputs.crc_poly.value = model.vars.crc_poly.var_enum.CCITT_16 #Assuming 2-octet FCS is default
        phy.profile_inputs.crc_invert.value = False
        phy.profile_inputs.crc_pad_input.value = False
        phy.profile_inputs.crc_seed.value = 0x00000000
        phy.profile_inputs.crc_bit_endian.value = model.vars.crc_bit_endian.var_enum.MSB_FIRST
        phy.profile_inputs.crc_byte_endian.value = model.vars.crc_byte_endian.var_enum.MSB_FIRST
        phy.profile_inputs.crc_input_order.value = model.vars.crc_input_order.var_enum.LSB_FIRST

        #Variable Length
        phy.profile_inputs.frame_length_type.value = model.vars.frame_length_type.var_enum.VARIABLE_LENGTH
        phy.profile_inputs.var_length_numbits.value = 11
        phy.profile_inputs.var_length_shift.value = 0
        phy.profile_inputs.var_length_maxlength.value = 2047
        phy.profile_inputs.var_length_minlength.value = 0
        phy.profile_inputs.var_length_includecrc.value = True
        phy.profile_inputs.var_length_adjust.value = 0
        phy.profile_inputs.var_length_bitendian.value = model.vars.var_length_bitendian.var_enum.MSB_FIRST
        phy.profile_inputs.var_length_byteendian.value = model.vars.var_length_byteendian.var_enum.MSB_FIRST

        #Header
        phy.profile_inputs.header_calc_crc.value = False
        phy.profile_inputs.header_en.value = True
        phy.profile_inputs.header_size.value = 2
        phy.profile_inputs.header_white_en.value = False

        #Additional Framing Details
        phy.profile_inputs.frame_bitendian.value = model.vars.frame_bitendian.var_enum.LSB_FIRST

    def _set_sidewalk_tolerances(self, model, phy):
        # These tolerances are from the initial PHY definition and are updated for later parts
        # Leaving alone for Nerio definition due to optimized timing detection threshold
        phy.profile_inputs.baudrate_tol_ppm.value = 0
        phy.profile_inputs.rx_xtal_error_ppm.value = 10
        phy.profile_inputs.tx_xtal_error_ppm.value = 10

    def PHY_Sidewalk_2GFSK_50Kbps(self, model):
        phy = self._makePhy(model, model.profiles.Base, phy_description='Sidewalk 50kbps 2GFSK mi=1.0')

        #Start with the common Amazon Sidewalk 2FSK base function
        self.sidewalk_2fsk_base(model, phy)

        #Define major PHY parameters
        phy.profile_inputs.base_frequency_hz.value = 902200000
        phy.profile_inputs.channel_spacing_hz.value = 200000
        phy.profile_inputs.bitrate.value = 50000
        phy.profile_inputs.deviation.value = 25000
        phy.profile_inputs.shaping_filter.value = model.vars.shaping_filter.var_enum.Gaussian
        phy.profile_inputs.shaping_filter_param.value = 1.0

        #Whitening on by default
        phy.profile_inputs.payload_white_en.value = True

    def PHY_Sidewalk_2GFSK_150Kbps(self, model):
        phy = self._makePhy(model, model.profiles.Base, phy_description='Sidewalk 150kbps 2GFSK mi=0.5')

        # Start with the common Amazon Sidewalk 2FSK base function
        self.sidewalk_2fsk_base(model, phy)

        # Define major PHY parameters
        phy.profile_inputs.base_frequency_hz.value = 902200000
        phy.profile_inputs.channel_spacing_hz.value = 406349
        phy.profile_inputs.bitrate.value = 150000
        phy.profile_inputs.deviation.value = 37500
        phy.profile_inputs.shaping_filter.value = model.vars.shaping_filter.var_enum.Gaussian
        phy.profile_inputs.shaping_filter_param.value = 0.5

        # Whitening on by default
        phy.profile_inputs.payload_white_en.value = True

        self._timing_detection_optimization(phy)

    def PHY_Sidewalk_2GFSK_250Kbps(self, model):
        phy = self._makePhy(model, model.profiles.Base, phy_description='Sidewalk 250kbps 2GFSK mi=0.5')

        # Start with the common Amazon Sidewalk 2FSK base function
        self.sidewalk_2fsk_base(model, phy)

        # Define major PHY parameters
        phy.profile_inputs.base_frequency_hz.value = 902200000
        phy.profile_inputs.channel_spacing_hz.value = 512000
        phy.profile_inputs.bitrate.value = 250000
        phy.profile_inputs.deviation.value = 62500
        phy.profile_inputs.shaping_filter.value = model.vars.shaping_filter.var_enum.Gaussian
        phy.profile_inputs.shaping_filter_param.value = 0.5

        # Whitening on by default
        phy.profile_inputs.payload_white_en.value = True

        # Optimizations
        self._timing_detection_optimization(phy)

    def _timing_detection_optimization(self, phy):
        phy.profile_inputs.timing_detection_threshold.value = 20
from pyradioconfig.parts.ocelot.phys.Phys_Studio_Connect import PHYS_connect_Ocelot
from pyradioconfig.calculator_model_framework.decorators.phy_decorators import do_not_inherit_phys
from pyradioconfig.parts.ocelot.profiles.profile_wisun_fan_1_0 import ProfileWisunFanOcelot


@do_not_inherit_phys
class PHYS_Studio_Connect_Sol(PHYS_connect_Ocelot):

    def Connect_base(self, phy, model):
        super().Connect_base(phy, model)
        phy.profile_inputs.header_size.value = 1
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.TWO_BYTE

        # : Exposed whitening inputs for Sol Connect Profile
        phy.profile_inputs.payload_white_en.value = False
        phy.profile_inputs.white_poly.value = model.vars.white_poly.var_enum.PN9
        phy.profile_inputs.white_seed.value = 0
        phy.profile_inputs.white_output_bit.value = 0

    def Connect_SUN_FSK_base(self, phy, model):
        #Standard modulation, shaping, and framing settings for Connect PHYs based on SUN-FSK

        #Modulation format and symbol mapping
        phy.profile_inputs.modulation_type.value = model.vars.modulation_type.var_enum.FSK2
        phy.profile_inputs.fsk_symbol_map.value = model.vars.fsk_symbol_map.var_enum.MAP0

        # Preamble
        phy.profile_inputs.preamble_pattern_len.value = 2
        phy.profile_inputs.preamble_length.value = 64
        phy.profile_inputs.preamble_pattern.value = 1

        # set syncword to uncoded version. Set sync0 == sync1 since dynamic fec is disabled
        phy.profile_inputs.syncword_0.value = ProfileWisunFanOcelot.phySunFskSfd_0_uncoded
        phy.profile_inputs.syncword_1.value = ProfileWisunFanOcelot.phySunFskSfd_0_uncoded
        phy.profile_inputs.syncword_length.value = 16
        phy.profile_inputs.syncword_tx_skip.value = False

        #Shaping filter
        phy.profile_inputs.shaping_filter.value = model.vars.shaping_filter.var_enum.Gaussian
        phy.profile_inputs.shaping_filter_param.value = 2.0

        #Xtal frequency and tolerance
        phy.profile_inputs.xtal_frequency_hz.value = 39000000
        phy.profile_inputs.rx_xtal_error_ppm.value = 7
        phy.profile_inputs.tx_xtal_error_ppm.value = 7
        phy.profile_inputs.baudrate_tol_ppm.value = 300
        phy.profile_inputs.deviation_tol_ppm.value = 300000

        #Header settings
        phy.profile_inputs.header_size.value = 2

        #CRC settings
        phy.profile_inputs.fcs_type_802154.value = model.vars.fcs_type_802154.var_enum.FOUR_BYTE
        phy.profile_inputs.crc_byte_endian.value = model.vars.crc_byte_endian.var_enum.MSB_FIRST
        phy.profile_inputs.crc_bit_endian.value = model.vars.crc_bit_endian.var_enum.MSB_FIRST

        #Encoding
        phy.profile_inputs.symbol_encoding.value = model.vars.symbol_encoding.var_enum.NRZ
        phy.profile_inputs.diff_encoding_mode.value = model.vars.diff_encoding_mode.var_enum.DISABLED
        phy.profile_inputs.dsss_chipping_code.value = 0
        phy.profile_inputs.dsss_len.value = 0
        phy.profile_inputs.dsss_spreading_factor.value = 0
        phy.profile_inputs.fec_en.value = model.vars.fec_en.var_enum.FEC_154G_NRNSC_INTERLEAVING
        phy.profile_inputs.fec_tx_enable.value = model.vars.fec_tx_enable.var_enum.DISABLED

        #Whitening
        phy.profile_inputs.payload_white_en.value = True
        phy.profile_inputs.white_poly.value = model.vars.white_poly.var_enum.PN9_802154
        phy.profile_inputs.white_seed.value = 0xFF
        phy.profile_inputs.white_output_bit.value = 8

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-45
    def PHY_Studio_Connect_920MHz_2GFSK_100kbps(self, model, phy_name=None):
        phy = super().PHY_Studio_Connect_920MHz_2GFSK_100kbps(model)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-2192
    def PHY_Studio_Connect_915mhz_oqpsk_2Mcps_250kbps(self, model, phy_name=None):
        phy = super().PHY_Studio_Connect_915mhz_oqpsk_2Mcps_250kbps(model)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-43
    def PHY_Studio_Connect_915MHz_2GFSK_500kbps(self, model, phy_name=None):
        phy = super().PHY_Studio_Connect_915MHz_2GFSK_500kbps(model)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-44
    def PHY_Studio_Connect_863MHz_2GFSK_100kbps(self, model, phy_name=None):
        phy = super().PHY_Studio_Connect_863MHz_2GFSK_100kbps(model)
        return phy

    # Owner: Casey Weltzin
    # Jira Link: https://jira.silabs.com/browse/PGSOLVALTEST-42
    def PHY_Studio_Connect_490MHz_2GFSK_200kbps(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.Connect, phy_description='China 490',
                      readable_name="Connect 490MHz 2GFSK 200kbps", phy_name=phy_name)

        # Common base function for all connect PHYs
        self.Connect_base(phy, model)

        # Add data-rate specific parameters
        phy.profile_inputs.bitrate.value = 200000
        phy.profile_inputs.deviation.value = 100000

        # Add band-specific parameters
        phy.profile_inputs.base_frequency_hz.value = 490000000
        phy.profile_inputs.channel_spacing_hz.value = 500000

        return phy

    # Owner: Young-Joon Choi
    def PHY_Studio_Connect_915MHz_SUN_FSK_10kbps(self, model, phy_name=None):
        phy = self._makePhy(model, model.profiles.Connect,
                            readable_name='Connect 915 MHz SUN-FSK 2FSK 10 kbps, MI=1.0, 2 Byte PHR',
                            phy_name=phy_name)

        # Start with the SUN FSK base function
        self.Connect_SUN_FSK_base(phy, model)

        # Select the modulation type
        phy.profile_inputs.modulation_type.value = model.vars.modulation_type.var_enum.FSK2

        # Select the unique parameters for this PHY
        phy.profile_inputs.base_frequency_hz.value = 902200000  # Ch0 Frequency
        phy.profile_inputs.bitrate.value = 10000
        phy.profile_inputs.deviation.value = 5000
        phy.profile_inputs.channel_spacing_hz.value = 50000

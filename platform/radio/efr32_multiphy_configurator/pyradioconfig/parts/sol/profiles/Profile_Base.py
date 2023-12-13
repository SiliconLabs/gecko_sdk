from pyradioconfig.parts.ocelot.profiles.Profile_Base import Profile_Base_Ocelot
from pyradioconfig.parts.sol.profiles.frame_profile_inputs_common import frame_profile_inputs_common_sol
from pyradioconfig.parts.sol.profiles.sw_profile_outputs_common import sw_profile_outputs_common_sol
from pyradioconfig.calculator_model_framework.interfaces.iprofile import IProfile

class Profile_Base_Sol(Profile_Base_Ocelot):

    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs"
        self._family = "sol"
        self._sw_profile_outputs_common = sw_profile_outputs_common_sol()
        self._frame_profile_inputs_common_sol = frame_profile_inputs_common_sol()

    def profile_calculate(self, model):

        #Call existing profile calculations
        super().profile_calculate(model)

        #Fixed variables (required inputs for other Profiles)
        #Using .value only so that we can force this in internal test PHYs
        model.vars.ofdm_option.value = model.vars.ofdm_option.var_enum.OPT1_OFDM_BW_1p2MHz

    def build_optional_profile_inputs(self, model, profile):
        IProfile.make_optional_input(profile, model.vars.syncword_tx_skip, "syncword",
                                     readable_name="Sync Word TX Skip", default=False)
        IProfile.make_optional_input(profile, model.vars.symbol_encoding, "symbol_coding",
                                     readable_name="Symbol Encoding", default=model.vars.symbol_encoding.var_enum.NRZ)
        IProfile.make_optional_input(profile, model.vars.test_ber, "testing",
                                     readable_name="Reconfigure for BER testing", default=False)
        IProfile.make_optional_input(profile, model.vars.deviation_tol_ppm, 'modem', default=0,
                                     readable_name="Maximum deviation offset expected in ppm", value_limit_min=0,
                                     value_limit_max=500000)
        self.make_optional_input(profile, model.vars.shaping_filter_param, "modem",
                                 readable_name="Shaping Filter Parameter (BT or R)", value_limit_min=0.3,
                                 value_limit_max=2.0, fractional_digits=2, default=0.5)

    def build_advanced_profile_inputs(self, model, profile):
        super().build_advanced_profile_inputs(model, profile)
        self.make_linked_io(profile, model.vars.fpll_band, 'crystal', readable_name="RF Frequency Planning Band")

    def build_hidden_profile_inputs(self, model, profile):
        super().build_hidden_profile_inputs(model, profile)
        IProfile.make_hidden_input(profile, model.vars.directmode_rx, "modem",
                                     readable_name="RX Direct Mode")
        self.make_hidden_input(profile, model.vars.dual_fefilt, "Advanced",
                                   readable_name="Dual front-end filter enable")

from pyradioconfig.parts.ocelot.profiles.Profile_Base import Profile_Base_Ocelot
from pyradioconfig.parts.margay.profiles.sw_profile_outputs_common import sw_profile_outputs_common_margay
from pyradioconfig.parts.margay.profiles.frame_profile_inputs_common import frame_profile_inputs_common_margay
from pyradioconfig.parts.common.profiles.margay_regs import build_modem_regs_margay
from pyradioconfig.calculator_model_framework.interfaces.iprofile import IProfile


class Profile_Base_Margay(Profile_Base_Ocelot):

    """
    Init internal variables
    """
    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs on EFR32xG23 parts"
        self._family = "margay"
        self._sw_profile_outputs_common = sw_profile_outputs_common_margay()
        self._frame_profile_inputs_common = frame_profile_inputs_common_margay()

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

    def build_hidden_profile_inputs(self, model, profile):
        super().build_hidden_profile_inputs(model, profile)
        IProfile.make_hidden_input(profile, model.vars.directmode_rx, "modem",
                                     readable_name="RX Direct Mode")

    def buildRegisterOutputs(self, model, profile):
        build_modem_regs_margay(model, profile)


from pyradioconfig.parts.ocelot.profiles.Profile_Base import Profile_Base_Ocelot
from pyradioconfig.parts.common.profiles.bobcat_regs import build_modem_regs_bobcat
from pyradioconfig.calculator_model_framework.interfaces.iprofile import IProfile

class Profile_Base_Bobcat(Profile_Base_Ocelot):

    def __init__(self):
        super().__init__()
        self._description = "Profile used for most PHYs"
        self._family = "bobcat"

    def buildRegisterOutputs(self, model, profile, family):
        build_modem_regs_bobcat(model, profile, family)

    def build_advanced_profile_inputs(self, model, profile):
        IProfile.make_linked_io(profile, model.vars.fec_tx_enable, 'Channel_Coding', readable_name="Enable FEC")
        IProfile.make_linked_io(profile, model.vars.skip2ant, 'Advanced',
                                'Skip 2nd antenna check with phase demod antenna diversity')
        IProfile.make_linked_io(profile, model.vars.preamble_detection_length, "preamble",
                                'Preamble Detection Length', value_limit_min=0, value_limit_max=2097151)
        IProfile.make_linked_io(profile, model.vars.lo_injection_side, "Advanced",
                                readable_name="Injection side")

    def build_hidden_profile_inputs(self, model, profile):
        IProfile.make_hidden_input(profile, model.vars.src1_range_available_minimum, "modem",
                                   readable_name="SRC range minimum", value_limit_min=125, value_limit_max=155)
        IProfile.make_hidden_input(profile, model.vars.input_decimation_filter_allow_dec3, "modem",
                                   readable_name="1=Allow input decimation filter decimate by 3 in cost function",
                                   value_limit_min=0, value_limit_max=1)
        IProfile.make_hidden_input(profile, model.vars.input_decimation_filter_allow_dec8, "modem",
                                   readable_name="1=Allow input decimation filter decimate by 8 in cost function",
                                   value_limit_min=0, value_limit_max=1)
        IProfile.make_hidden_input(profile, model.vars.demod_select, 'Advanced', readable_name="Demod Selection")
        IProfile.make_hidden_input(profile, model.vars.adc_clock_mode, "modem",
                                   readable_name="ADC Clock Mode (XO vs VCO)")
        IProfile.make_hidden_input(profile, model.vars.adc_rate_mode, 'Advanced', readable_name="ADC Rate Mode")
        IProfile.make_hidden_input(profile, model.vars.bcr_demod_en, 'Advanced',
                                   readable_name="Force BCR demod calculation", value_limit_min=0, value_limit_max=1)
        IProfile.make_hidden_input(profile, model.vars.synth_settling_mode, 'modem',
                                   readable_name="Synth Settling Mode")

        IProfile.make_hidden_input(profile, model.vars.fast_detect_enable, 'Advanced',
                                   readable_name="Fast preamble detect enable")
        IProfile.make_hidden_input(profile, model.vars.aox_enable, 'modem', readable_name="Enable AoX")
        IProfile.make_hidden_input(profile, model.vars.antdiv_switch_delay_us, 'Advanced', readable_name='Antdiv Delay in us', value_limit_min=0.0, value_limit_max=1e6)
        IProfile.make_hidden_input(profile, model.vars.antdiv_switch_skip_us, 'Advanced', readable_name='Antdiv Skip in us', value_limit_min=0.0, value_limit_max=1e6)
        IProfile.make_hidden_input(profile, model.vars.antdiv_adprethresh_scale, 'Advanced', readable_name='Antdiv preamble threshold scaling', value_limit_min=0.0, value_limit_max=1.0)
        IProfile.make_hidden_input(profile, model.vars.antdiv_enable_parallel_correlation, 'Advanced', readable_name='Antdiv Enable Parallel Correlation')
        IProfile.make_hidden_input(profile, model.vars.antdiv_adpcsigampthr, 'Advanced', readable_name='Antdiv Signal Amplitude Threshold', value_limit_min=0, value_limit_max=491520)
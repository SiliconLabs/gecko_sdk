from pyradioconfig.calculator_model_framework.interfaces.itarget import ITarget


class Target_IC_Ocelot(ITarget):

    _targetName = ITarget.IC_str
    _description = ""
    _store_config_output = True
    _cfg_location = "ocelot"
    _tag = ITarget.IC_str

    def target_calculate(self, model):
        pass

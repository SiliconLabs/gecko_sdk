from pyradioconfig.parts.viper.targets.Target_IC import target_IC_viper
from pyradioconfig.calculator_model_framework.interfaces.itarget import ITarget

class TargetIcRainier(target_IC_viper):

    _targetName = ITarget.IC_str
    _description = ""
    _store_config_output = True
    _cfg_location = "rainier"
    _tag = ITarget.IC_str

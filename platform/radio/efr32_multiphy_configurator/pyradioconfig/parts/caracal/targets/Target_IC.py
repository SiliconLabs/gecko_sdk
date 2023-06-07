from pyradioconfig.parts.bobcat.targets.Target_IC import Target_IC_Bobcat
from pyradioconfig.calculator_model_framework.interfaces.itarget import ITarget


class Target_IC_Caracal(Target_IC_Bobcat):

    _targetName = ITarget.IC_str
    _description = ""
    _store_config_output = True
    _cfg_location = "caracal"
    _tag = ITarget.IC_str

    # Inherit all target methods for now
    pass

from pyradioconfig.parts.viper.targets.Target_Sim import Target_Sim_Viper
from os.path import join

class TargetSimRainier(Target_Sim_Viper):

    _targetName = "Sim"
    _description = "Supports the wired FPGA and other targets of sim PHYs"
    _store_config_output = True
    _cfg_location = join('target_sim','rainier')
    _tag = "SIM"

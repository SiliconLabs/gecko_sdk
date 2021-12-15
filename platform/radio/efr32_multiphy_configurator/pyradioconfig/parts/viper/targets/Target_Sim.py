from pyradioconfig.parts.bobcat.targets.Target_Sim import Target_Sim_Bobcat
from os.path import join

class target_sim_viper(Target_Sim_Bobcat):

    _targetName = "Sim"
    _description = "Supports the wired FPGA and other targets of sim PHYs"
    _store_config_output = True
    _cfg_location = join('target_sim','viper')
    _tag = "SIM"
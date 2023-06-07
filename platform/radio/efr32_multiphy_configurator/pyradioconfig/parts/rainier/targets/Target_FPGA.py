from pyradioconfig.parts.viper.targets.Target_FPGA import target_fpga_viper
from os.path import join


class TargetFpgaRainier(target_fpga_viper):

    _targetName = "FPGA"
    _description = "Supports the OTA FPGA"
    _store_config_output = False
    _cfg_location = join('target_fpga','rainier')
    _tag = "FPGA"

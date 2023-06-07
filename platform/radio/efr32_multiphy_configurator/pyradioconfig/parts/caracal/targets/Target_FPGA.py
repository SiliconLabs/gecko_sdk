from pyradioconfig.parts.bobcat.targets.Target_FPGA import Target_FPGA_Bobcat
from os.path import join


class Target_FPGA_Caracal(Target_FPGA_Bobcat):

    _targetName = "FPGA"
    _description = "Supports the OTA FPGA"
    _store_config_output = False
    _cfg_location = join('target_fpga','caracal')
    _tag = "FPGA"

    # Inherit all target methods for now
    pass

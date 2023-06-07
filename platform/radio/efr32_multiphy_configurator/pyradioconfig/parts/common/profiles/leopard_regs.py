from pyradioconfig.parts.common.profiles.lynx_regs import build_modem_regs_lynx
from pycalcmodel.core.output import ModelOutput, ModelOutputType

def build_modem_regs_leopard(model,profile):
    build_modem_regs_lynx(model, profile)

    profile.outputs.append(ModelOutput(model.vars.RAC_IFADCTRIM0_IFADCCLKSEL, '', ModelOutputType.SVD_REG_FIELD,
                                       readable_name='RAC.IFADCTRIM0.IFADCCLKSEL'))
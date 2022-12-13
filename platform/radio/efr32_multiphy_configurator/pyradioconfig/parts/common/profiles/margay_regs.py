from pyradioconfig.parts.common.profiles.ocelot_regs import build_modem_regs_ocelot
from pycalcmodel.core.output import ModelOutput, ModelOutputType

def build_modem_regs_margay(model,profile):

    #Start with Ocelot regs
    family = model.part_family.lower()
    build_modem_regs_ocelot(model, profile, family)

    #Additional Margay regs
    profile.outputs.append(ModelOutput(model.vars.RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1, '', ModelOutputType.SVD_REG_FIELD,
                                       readable_name='RAC.LNAMIXTRIM1.LNAMIXMXRBIAS1'))
    profile.outputs.append(ModelOutput(model.vars.RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0, '', ModelOutputType.SVD_REG_FIELD,
                                       readable_name='RAC.LNAMIXTRIM0.LNAMIXMXRBIAS0'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_LOG2X4_LOG2X4FWSEL, '', ModelOutputType.SVD_REG_FIELD,
                                       readable_name='MODEM.LOG2X4.LOG2X4FWSEL'))
    profile.outputs.append(ModelOutput(model.vars.MODEM_LOG2X4_LOG2X4, '', ModelOutputType.SVD_REG_FIELD,
                                       readable_name='MODEM.LOG2X4.LOG2X4'))
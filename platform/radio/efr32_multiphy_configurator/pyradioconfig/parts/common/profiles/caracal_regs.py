from pyradioconfig.parts.common.profiles.bobcat_regs import build_modem_regs_bobcat


def build_momem_regs_caracal(model, profile):
    # Inherit all regs for now
    build_modem_regs_bobcat(model, profile)

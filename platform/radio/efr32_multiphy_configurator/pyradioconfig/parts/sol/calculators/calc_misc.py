from pyradioconfig.parts.ocelot.calculators.calc_misc import CALC_Misc_ocelot
from pycalcmodel.core.variable import ModelVariableFormat

class Calc_Misc_Sol(CALC_Misc_ocelot):

    def buildVariables(self, model):
        super().buildVariables(model)

        self._addModelVariable(model, 'alt_stack_info', int, ModelVariableFormat.DECIMAL,
                               desc='information dedicated to stack for alternate PHY', is_array=True)

    def calc_misc_Ocelot(self, model):
        pass

    def calc_misc_Sol(self, model):
        """
        These aren't really calculating right now.  Just using defaults or forced values.
       fefilt_selected = model.vars.fefilt_selected.value
        Args:
             model (ModelRoot) : Data model to read and write variables from
        """
        fefilt_selected = model.vars.fefilt_selected.value

        # FIXME: This was not calculated on Ocelot
        #self._reg_write(model.vars.FEFILT0_CF_CFOSR, 0)
        
        self._reg_write_by_name_concat(model, fefilt_selected, 'CF_ADCBITORDERI', 0)
        self._reg_write_by_name_concat(model, fefilt_selected, 'CF_ADCBITORDERQ', 0)
        
        # FIXME: This was not calculated on Ocelot
        #self._reg_write(model.vars.FEFILT0_SRCCHF_SRCDECEN2, 0)                
        
        # Digital Gain Control
        self._reg_write_by_name_concat(model, fefilt_selected, 'DIGIGAINCTRL_DEC0GAIN', 0)
        self._reg_write_by_name_concat(model, fefilt_selected, 'DIGIGAINCTRL_DIGIGAINEN', 0)
        self._reg_write_by_name_concat(model, fefilt_selected, 'DIGIGAINCTRL_DIGIGAIN', 0)

        ## New registers
        # FIXME: how to calculate these?
        self._reg_write_by_name_concat(model, fefilt_selected, 'CHFCTRL_FWSELCOEFF', 0)
        self._reg_write_by_name_concat(model, fefilt_selected, 'CHFCTRL_FWSWCOEFFEN', 0)
        self._reg_write_by_name_concat(model, fefilt_selected, 'CHFCTRL_CHFLATENCY', 0)

        self._reg_write_by_name_concat(model, fefilt_selected, 'DCCOMPFILTINIT_DCCOMPINIT', 0)
        self._reg_write_by_name_concat(model, fefilt_selected, 'DCCOMPFILTINIT_DCCOMPINITVALI', 0)
        self._reg_write_by_name_concat(model, fefilt_selected, 'DCCOMPFILTINIT_DCCOMPINITVALQ', 0)

        self._reg_write(model.vars.MODEM_PHDMODANTDIV_ANTDECRSTBYP, 1)
        self._reg_write(model.vars.MODEM_PHDMODANTDIV_RECHKCORREN,  0)
        self._reg_write(model.vars.MODEM_PHDMODANTDIV_SKIPTHDSEL,   1)

        self._reg_write(model.vars.RAC_PATRIM6_TXTRIMBBREGFB, 8)

        # For now, set to max amplitude of 3
        # See findings in https://jira.silabs.com/browse/MCUW_RADIO_CFG-1800
        self._reg_write(model.vars.RAC_IFADCTRIM0_IFADCSIDETONEAMP, 3)

    def calc_stack_info(self, model):
        # Get parameters common to all protocols
        protocol_id = model.vars.protocol_id.value
        softmodem_modulation_type = model.vars.softmodem_modulation_type.value
        wisun_channel_plan_id = getattr(model.profile.inputs, "wisun_channel_plan_id", None)
        wisun_reg_domain = getattr(model.profile.inputs, "wisun_reg_domain", None)

        # Other parameters are stored in this list
        specific_parameters = []

        if softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OQPSK:
            # : For SUN-OQPSK, follow Wi-SUN Fan 1v1 format for defining stack_info
            # Get WiSUN specific parameters
            version = 1  # FAN1.1 version
            phy_id = model.vars.wisun_phy_mode_id.value[0]
            # : if channel plan id is not defined, set to 255
            if wisun_channel_plan_id is None:
                wisun_channel_plan_id = 255
            # : if reg domain is not defined, set to 255
            if wisun_reg_domain is None:
                wisun_reg_domain = 255
            specific_parameters.extend([version, wisun_channel_plan_id, wisun_reg_domain])

            model.vars.stack_info.value = [int(protocol_id), int(phy_id)]
            model.vars.stack_info.value.extend(specific_parameters)
        elif protocol_id == model.vars.protocol_id.var_enum.Connect and \
            softmodem_modulation_type == model.vars.softmodem_modulation_type.var_enum.SUN_OFDM:
            # : Connect OFDM case
            phy_id = model.vars.wisun_phy_mode_id.value[0]
            model.vars.stack_info.value = [int(protocol_id), int(phy_id)]
        else:
            super().calc_stack_info(model)
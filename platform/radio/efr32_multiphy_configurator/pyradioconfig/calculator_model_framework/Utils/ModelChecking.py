"""
ModelChecking() implements methods to check a calculated model
All Sim PHYs and all PHYs of some parts are excluded to match previous unit test coverage
Checks done:
    check_regs(): Check for register overflow in model outputs. Implicitly checks of regmap matching
    check_all_profile_inputs_populated(): Check if all required profile inputs are populated
    check_all_profile_outputs_calculated(): Check if all profile outputs have calculated values
    check_all_calcs_ran(): Check if all calculations ran
"""


from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr
from pycalcmodel.core.input import ModelInputType, ModelInputDefaultVisibilityType
from host_py_rm_studio_internal.factory import RM_Factory
from pycalcmodel.core.output import ModelOutputType

exclude_inputVal_parts = ['nerio', 'nixi', 'dumbo', 'jumbo', 'panther', 'unit_test_part']
exclude_outputVal_parts = ['nerio', 'nixi', 'dumbo', 'jumbo', 'panther', 'unit_test_part']
exclude_calcsVal_parts = ['nerio', 'nixi', 'dumbo', 'jumbo', 'panther', 'unit_test_part']
exclude_regVal_parts = ['unit_test_part']

class ModelCheckingError(Exception):
    pass

class ModelChecking:
    """Class object to store model checking methods"""

    @staticmethod
    def _check_val_vs_bit_width(value, bit_width):

        if bit_width is not None and value is not None:

            missing_info = False

            #We don't know which registers are signed, so for positive values all we can do is make sure
            #they fit in an unsigned reg
            most_positive_allowed = (1 << bit_width) - 1
            most_negative_allowed = -1*(1 << (bit_width - 1))

            if value >= 0:
                reg_overflow_error = value > most_positive_allowed
            else:
                reg_overflow_error = value < most_negative_allowed

        else:
            missing_info = True
            reg_overflow_error = False

        return missing_info, reg_overflow_error

    @staticmethod
    def _check_skip_condition(model, exclude_list, teststr):
        """
        Filter model checking according to previous unittest coverage and CalcManager.calculate_phy conditional
            We do not check for unit_test_part because it intentionally does not follow this rule
            Also skip sim PHYs as they are generally not well formed (just pokes)
        """
        skip = False
        part_family = model.part_family.lower()
        target = model.target.lower()
        if part_family in exclude_list:
            # Skip model checking for legacy parts (Unit test coverage started from >lynx)
            LogMgr.Debug(f'Excluding {teststr} for {part_family}')
            skip = True
        elif target == 'sim' \
                or (model.phy is not None and model.phy.group_name == 'Phys_sim_tests'):       # Edge case for Lynx and Leopard (no "Sim"-type target)
            # Skip model checking for Sim parts (imperfect models expected)
            LogMgr.Debug(f'Excluding {teststr} for simulation PHYs')
            skip = True

        return skip

    @staticmethod
    def check_regs(model, ignore_missing_info=True):
        regexist_error_list = []
        bitwidth_error_list = []
        errorstr = ""

        if ModelChecking._check_skip_condition(model, exclude_regVal_parts, "reg overflow check"):
            return regexist_error_list, bitwidth_error_list, errorstr

        part_family = model.part_family
        if model.phy is None:
            phy_name = f"unnamed_phy_from_profile_{model.profile.name}"
        else:
            phy_name = model.phy.name
        #Get the regmap object just once for the part (much more efficient than looping)
        regmap_obj = RM_Factory(part_family.upper())()



        # Loop through every profile output looking for registers
        for profile_output in model.profile.outputs:
            if profile_output.output_type == ModelOutputType.SVD_REG_FIELD:
                register_name = profile_output.var.svd_mapping
                ## First, check if register exists
                try:
                    reg = regmap_obj.getObjectByName(register_name)
                except: # It does not
                    regexist_error_list.append((register_name))
                    continue        # Skip bitwidth validation

                #Now that we found a register, we need to look at the current assigned value plus the
                #field width in the register model
                current_reg_value = profile_output.var_value
                bit_width = reg.bitWidth

                missing_info, reg_overflow_err = ModelChecking._check_val_vs_bit_width(current_reg_value, bit_width)

                if not ignore_missing_info:
                    if current_reg_value is None:
                        assert missing_info, "Test Failed! Can not run because missing value " \
                                             "for reg %s in %s" %(profile_output.var_name, phy_name)
                    else:
                        assert missing_info, "Test Failed! Can not run because can not access bit width " \
                                             "for reg %s in %s" %(profile_output.var_name, phy_name)

                if reg_overflow_err:
                    bitwidth_error_list.append((profile_output.var_name, current_reg_value, bit_width, phy_name))

        # Print all of the errors
        if len(regexist_error_list) > 0:
            errorstr += "Failed register check for %s\n\n" % (part_family)
            for error in regexist_error_list:
                errorstr += "Did not find a match in reg model for %s register %s\n" % (part_family, error)
        if len(bitwidth_error_list) > 0:
            errorstr += "Found at least one register value that exceeds reg model bit width\n\n"
            for error in bitwidth_error_list:
                errorstr += 'Error: Variable %s has a value of %d which exceeds reg model bit width of %d (%s)\n' \
                      %(error[0],error[1],error[2],error[3])
            errorstr += '\nReg checking completed with %d total errors' % (len(regexist_error_list) + len(bitwidth_error_list))

        return regexist_error_list, bitwidth_error_list, errorstr

    @staticmethod
    def check_all_profile_inputs_populated(model):
        error_list = []
        errorstr = ""
        if ModelChecking._check_skip_condition(model, exclude_inputVal_parts, "input regs check"):
            return error_list, errorstr

        if model.phy is None:
            phy_name = f"unnamed_phy_from_profile_{model.profile.name}"
        else:
            phy_name = model.phy.name
        for profile_input in model.profile.inputs:
            if profile_input.deprecated == False:
                if profile_input.var_value == None:
                    if profile_input.default == None:
                        if profile_input.input_type != ModelInputType.LINKED_IO:
                            if profile_input.default_visibility != ModelInputDefaultVisibilityType.HIDDEN:
                                error_list.append((profile_input.var_name, phy_name))

        errorstr += "PHY profile inputs do not have values or defaults\n\n"
        for error in error_list:
            errorstr += "ERROR: PHY profile input {0} for phy: {1}, has no value or default\n\n".format(
                                            error[0], error[1])
        errorstr += '\nTest completed with %d errors' % len(error_list)

        return error_list, errorstr

    @staticmethod
    def check_all_profile_outputs_calculated(model, check_non_reg=False, exclude_legacy_parts=True):
        """
        Check if all calculations ran, raises exception if a calculation is not ran.
        Ported from unit tests
        """
        error_list = []
        errorstr = ""
        if ModelChecking._check_skip_condition(model, exclude_outputVal_parts, "profile output check") \
                and exclude_legacy_parts:
            return error_list, errorstr

        if model.phy is None:
            phy_name = f"unnamed_phy_from_profile_{model.profile.name}"
        else:
            phy_name = model.phy.name
        # Loop through every profile output and make sure a value is assigned
        for profile_output in model.profile.outputs:
            if profile_output.output_type.name == 'SVD_REG_FIELD' or check_non_reg == True:
                if profile_output.var_value is None and not profile_output.var.value_do_not_care:
                        # We found a profile output that we care about that has no value
                        error_list.append((profile_output.var_name, phy_name))

                elif profile_output.value_limit_min is not None:
                    if profile_output.var_value < profile_output.value_limit_min:
                        # We found a value that exists but is out of range
                        LogMgr.Warning("Warning! Profile output %s has value %d that is below min %d"
                              %(profile_output.var_name,profile_output.var_value,profile_output.value_limit_min))

                elif profile_output.value_limit_max is not None:
                    if profile_output.var_value > profile_output.value_limit_max:
                        # We found a value that exists but is out of range
                        LogMgr.Warning("Warning! Profile output %s has value %d that is above max %d"
                            % (profile_output.var_name, profile_output.var_value, profile_output.value_limit_max))

        errorstr += 'Test failed because some profile outputs are not being calculated\n\n'
        for error in error_list:
           errorstr += 'Error: found profile output %s is not calculated for %s\n' %error
        errorstr += '\nTest completed with %d failures' %len(error_list)

        return error_list, errorstr

    @staticmethod
    def check_all_calcs_ran(model, exclude_legacy_parts=True):
        """
        Check if all calculations ran, raises exception if a calculation is not ran.
        Ported from unit tests
        """

        error_list = []
        errorstr = ""
        if ModelChecking._check_skip_condition(model, exclude_calcsVal_parts, "all-calcs-ran check") \
                and exclude_legacy_parts:
            return error_list, errorstr

        if model.phy is None:
            phy_name = f"unnamed_phy_from_profile_{model.profile.name}"
        else:
            phy_name = model.phy.name
        # Check if any calculations failed
        calc_error_list = []

        if model.phy is not None and model.phy.locked:
            LogMgr.Debug('Skipping phy:{} for all-calcs-ran check because it is locked.'.format(phy_name))
        else:
            total_calcs = len(model.calc_routine_execution)
            # failure_count = sum(value == False for value in model.calc_routine_execution.values())

            for calc_routine in model.calc_routine_execution:
                if model.calc_routine_execution[calc_routine] == False:
                    errorstr += 'Missed calculation %s for PHY %s\n' % (calc_routine, phy_name)
                    calc_error_list.append(calc_routine)

            errorstr += '\nCalculation coverage test concluded with %d missed calcs out of %d' % (len(calc_error_list),
                                                                                                    total_calcs)
            if len(calc_error_list) > 0:
                errorstr += '\nFailed to execute some calculations\n\n'

        return calc_error_list, errorstr
--[[
    This script validates that apps meant to run on an EFR do not include the
    AES (Software) component, as the Zigbee Key Storage components provide
    hardware AES support.
--]]
local zigbee_pro_stack_selected = slc.is_selected("zigbee_pro_stack")
local zigbee_pro_router_stack_selected = slc.is_selected("zigbee_pro_router_stack")
local zigbee_pro_leaf_stack_selected = slc.is_selected("zigbee_pro_leaf_stack")
local app_is_for_efr = slc.is_provided("device_cortexm")

if app_is_for_efr == true then
    if zigbee_pro_stack_selected == true or zigbee_pro_router_stack_selected == true or zigbee_pro_leaf_stack_selected == true then
        validation.error(
            "The Zigbee AES (Software) component is not compatible with projects that are meant to run on an EFR. The Zigbee Secure Key Storage or Classic Key Storage components, which are brought in via dependencies, will bring in hardware support for AES.",
            validation.target_for_project(),
            "Remove the Zigbee AES (Software) component.",
            nil
        )
    end
end

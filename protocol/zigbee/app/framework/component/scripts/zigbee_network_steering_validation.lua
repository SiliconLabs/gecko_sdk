-- This validation script checks following:
-- 1. In case of Optimized Scans is disabled, Try All Keys can not be enabled
 
local optimized_scans_enabled = slc.config("EMBER_AF_PLUGIN_NETWORK_STEERING_OPTIMIZE_SCANS").value == "1"
local try_all_keys_enabled = slc.config("EMBER_AF_PLUGIN_NETWORK_STEERING_TRY_ALL_KEYS").value == "1"

if not optimized_scans_enabled and try_all_keys_enabled then
    validation.error("Try All Keys can not be enabled when Optimized Scans is disabled",
        validation.target_for_defines({"EMBER_AF_PLUGIN_NETWORK_STEERING_TRY_ALL_KEYS"}),
        nil,
        nil)
end
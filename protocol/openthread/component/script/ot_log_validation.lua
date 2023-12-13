--[[
    This script validates that apps which configure platform defined logging
    include the necessary logging component (ot_rtt_log) to include the platform
    logging API definitions and associated utility interfaces.
--]]
local platform_logging_enabled = slc.config("OPENTHREAD_CONFIG_LOG_OUTPUT").value == "OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED"

if platform_logging_enabled and not slc.is_selected("ot_rtt_log") then
    validation.error("ot_rtt_log must be included when OPENTHREAD_CONFIG_LOG_OUTPUT is configured to PLATFORM_DEFINED.",
                      validation.target_for_project(),
                      "Include the ot_rtt_log component, or select a different log output configuration value.",
                      nil
    )
end

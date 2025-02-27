--[[
    This script validates that OpenThread multiple static instance config options are
    enabled for multipan applications.
--]]

local multipan_enable_config = slc.config("OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE")
local multple_instance_enable_config = slc.config("OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE")
local multiple_static_instance_enable_config = slc.config("OPENTHREAD_CONFIG_MULTIPLE_STATIC_INSTANCE_ENABLE")

if multipan_enable_config ~= nil and multipan_enable_config.value == "1" then
  if multple_instance_enable_config == nil or multple_instance_enable_config.value ~= "1" then
    validation.error("Enable OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE option.",
                      validation.target_for_defines({"OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE"}),
                      "MultiPAN application needs OpenThread multiple instances support.",
                      nil
    )
  end
  if multiple_static_instance_enable_config == nil or multiple_static_instance_enable_config.value ~= "1" then
    validation.error("Enable OPENTHREAD_CONFIG_MULTIPLE_STATIC_INSTANCE_ENABLE option.",
                      validation.target_for_defines({"OPENTHREAD_CONFIG_MULTIPLE_STATIC_INSTANCE_ENABLE"}),
                      "MultiPAN application needs OpenThread multiple static instances support.",
                      nil
    )
  end
end

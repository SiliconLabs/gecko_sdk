local changeset = {}

local platform_logging_enabled = slc.config("OPENTHREAD_CONFIG_LOG_OUTPUT") ~= nil and 
      slc.config("OPENTHREAD_CONFIG_LOG_OUTPUT").value == "OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED"

if platform_logging_enabled and not slc.is_selected("ot_rtt_log") then
  table.insert(changeset, {
    ['component'] = 'ot_rtt_log',
    ['action'] = 'add'
  })
end
return changeset

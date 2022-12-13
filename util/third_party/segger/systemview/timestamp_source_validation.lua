local timestamp_source = slc.config("SEGGER_SYSVIEW_TIMESTAMP_SOURCE").value

if (timestamp_source == "SEGGER_SYSVIEW_TIMESTAMP_SOURCE_DWT" and slc.is_provided("cortexm0plus")) then
  validation.error("SEGGER_SYSVIEW_TIMESTAMP_SOURCE cannot be set to SEGGER_SYSVIEW_TIMESTAMP_SOURCE_DWT on this device", validation.target_for_defines({"SEGGER_SYSVIEW_TIMESTAMP_SOURCE"}))
end
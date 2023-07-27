local config_dbg_core = slc.config("SL_CPC_DEBUG_SYSTEM_VIEW_LOG_CORE_EVENT")
local config_dbg_endpoint = slc.config("SL_CPC_DEBUG_SYSTEM_VIEW_LOG_ENDPOINT_EVENT")
if config_dbg_core.value == "1" and not slc.is_provided("segger_systemview") then
  validation.error(
  "Segger System View is required when SL_CPC_DEBUG_SYSTEM_VIEW_LOG_CORE_EVENT is enabled",
  validation.target_for_defines({"SL_CPC_DEBUG_SYSTEM_VIEW_LOG_CORE_EVENT"}),
  nil,
  nil)
elseif config_dbg_endpoint.value == "1" and not slc.is_provided("segger_systemview") then
  validation.error(
  "Segger System View is required when SL_CPC_DEBUG_SYSTEM_VIEW_LOG_ENDPOINT_EVENT is enabled",
  validation.target_for_defines({"SL_CPC_DEBUG_SYSTEM_VIEW_LOG_ENDPOINT_EVENT"}),
  nil,
  nil)
end

if slc.config("SL_BOARD_ENABLE_VCOM").value ~= "1" and slc.is_provided("cpc_config_vcom") then
  validation.error(
  "CPC uses VCOM instance but VCOM is not enabled.",
  validation.target_for_defines({"SL_BOARD_ENABLE_VCOM"}),
  "Please enable VCOM in the Board Control component, or add \"--configuration SL_BOARD_ENABLE_VCOM:1\" to your project generation command.",
  nil)
end
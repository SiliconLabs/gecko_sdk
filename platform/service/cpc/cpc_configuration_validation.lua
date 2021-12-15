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


local config_security = slc.config("SL_CPC_ENDPOINT_SECURITY_ENABLED")
if config_security.value == "1" then
  local config_binding_key = slc.config("SL_CPC_SECURITY_BINDING_KEY_METHOD")
  if config_binding_key.value == "SL_CPC_SECURITY_BINDING_KEY_NONE" then
    validation.error(
    "CPC encryption is enabled but binding method is selected as none",
    validation.target_for_defines({"SL_CPC_SECURITY_BINDING_KEY_METHOD"}),
    nil,
    nil)
  end
end
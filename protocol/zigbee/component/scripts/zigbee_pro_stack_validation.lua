--[[   This validation script checks following:
    1. Primary device has to be either coordinator or router if secondary network is not enabled for multi network feature.
    2. Validates the selected primary device type is a coordinator in case of simultaneous dual band application.
    3. Either primary or secondary device type has to be coordinator or router if secondary network is enabled.
]]--
local device_type_primary_val = slc.config("SLI_ZIGBEE_PRIMARY_NETWORK_DEVICE_TYPE").value
local device_type_secondary_val = slc.config("SLI_ZIGBEE_SECONDARY_NETWORK_DEVICE_TYPE").value
local coordinator_device_type_val = "SLI_ZIGBEE_NETWORK_DEVICE_TYPE_COORDINATOR_OR_ROUTER"
local secondary_network_enabled = slc.config("SLI_ZIGBEE_SECONDARY_NETWORK_ENABLED").value == "1"
local transient_key_timeout = slc.config("EMBER_TRANSIENT_KEY_TIMEOUT_S").value
local network_creator_security = slc.is_selected("zigbee_network_creator_security")

--- ffd stands for full functional devices such as coordinator and router.
local ffd_device_list_val = Set("SLI_ZIGBEE_NETWORK_DEVICE_TYPE_COORDINATOR_OR_ROUTER", "SLI_ZIGBEE_NETWORK_DEVICE_TYPE_ROUTER")
if not secondary_network_enabled then 
    if ffd_device_list_val[device_type_primary_val] == nil then
        validation.error("Zigbee Pro Stack component supports only coordinator and router device types.",
        validation.target_for_defines({"SLI_ZIGBEE_PRIMARY_NETWORK_DEVICE_TYPE"}),
        "Select Zigbee Pro Leaf Stack component for end device or sleepy end device.",
        nil)
    elseif device_type_primary_val ~= coordinator_device_type_val and slc.is_selected("zigbee_phy_2_4_subghz_switch_coordinator") then
        validation.error("Only a coordinator type is supported for simultaneous dual band operations.",
        validation.target_for_defines({"SLI_ZIGBEE_PRIMARY_NETWORK_DEVICE_TYPE"}),
        nil,
        nil)
    end
else 
    if ffd_device_list_val[device_type_primary_val] == nil and ffd_device_list_val[device_type_secondary_val] == nil then
        validation.error("Zigbee Pro Stack component supports only coordinator and router device types.",
        validation.target_for_defines({"SLI_ZIGBEE_PRIMARY_NETWORK_DEVICE_TYPE"}, {"SLI_ZIGBEE_SECONDARY_NETWORK_DEVICE_TYPE"}),
        "Select Zigbee Pro Leaf Stack component if both device types are either end device or sleepy end device.",
        nil)
    end
--- When secondary network is enabled, that is multi network configuration, then the dual phy is not supported in that configuration.
    if slc.is_selected("zigbee_phy_2_4_subghz_switch_coordinator") then
        validation.error("Dual phy switch corordinator is not supported in multi-network configuration",
                         validation.target_for_defines({"SLI_ZIGBEE_SECONDARY_NETWORK_ENABLED",
                                                        "SL_CATALOG_ZIGBEE_PHY_2_4_SUBGHZ_SWITCH_COORDINATOR_PRESENT"}),
                                                       "zigbee_phy_2_4_subghz_switch_coordinator component can not be part of multi network.",
                                                       nil
                        )
    end
end

if network_creator_security == true then
    local network_open_time = slc.config("EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_NETWORK_OPEN_TIME_S").value
    if device_type_primary_val == coordinator_device_type_val or device_type_secondary_val == coordinator_device_type_val then
        if transient_key_timeout ~= network_open_time then
            validation.warning("Transient Key Timeout and Open Network Time should be configured with same value",
            validation.target_for_defines({"EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_NETWORK_OPEN_TIME_S"}, {"EMBER_TRANSIENT_KEY_TIMEOUT_S"}),
            nil,
            nil)
        end
    end
end
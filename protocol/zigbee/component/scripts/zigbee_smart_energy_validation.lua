-- This script validates if EMBER_AF_PLUGIN_NETWORK_FIND_ENABLE_ALL_CHANNELS is set to true for SmartEnergy apps.

local security_type = slc.config("SLI_ZIGBEE_PRIMARY_NETWORK_SECURITY_TYPE").value
local channels_enabled = slc.config("EMBER_AF_PLUGIN_NETWORK_FIND_ENABLE_ALL_CHANNELS").value

local se_securtiy_types = Set("SLI_ZIGBEE_NETWORK_SECURITY_TYPE_SE_TEST","SLI_ZIGBEE_NETWORK_SECURITY_TYPE_SE_FULL")

if (se_securtiy_types[security_type] ~= nil) and (channels_enabled ~= "1") then
    print("SE Smart Energy Validation Script.")
    validation.warning("It is recommended to enable all channels in the Network Find component in a Smart Energy Application.",
                        validation.target_for_defines({"EMBER_AF_PLUGIN_NETWORK_FIND_ENABLE_ALL_CHANNELS"}),
                        nil,
                        nil)
end
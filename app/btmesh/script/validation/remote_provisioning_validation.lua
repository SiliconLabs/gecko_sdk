-- Remote provisioning validation script

local remote_prov_server_present = slc.is_selected('btmesh_remote_provisioning_server')
local remote_prov_client_present = slc.is_selected('btmesh_remote_provisioning_client')
local max_prov_bearers_config = slc.config("SL_BTMESH_CONFIG_MAX_PROV_BEARERS").value

-- remove '(' and ')' characters used in some configuration headers "(3)" -> "3"
max_prov_bearers_config = string.gsub(max_prov_bearers_config, '%p', '')
local max_prov_bearers_config_value = tonumber(max_prov_bearers_config)

if (remote_prov_server_present or remote_prov_client_present) and (max_prov_bearers_config_value < 3) then
    validation.warning(
        'Reconfiguration of BT Mesh Stack is mandatory for remote provisioning server or client usage',
        validation.target_for_defines({"SL_BTMESH_CONFIG_MAX_PROV_BEARERS"}),
        'Set the "Maximum number of provisioning bearers allowed" value to at least 3 in "Bluetooth Mesh Stack Configuration" page, current value: '.. tostring(max_prov_bearers_config_value)
    )
end

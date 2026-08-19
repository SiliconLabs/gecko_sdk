local changeset = {}

local zigbee_tunneling_server_configuration = slc.is_provided('zigbee_tunneling_server')

if (zigbee_tunneling_server_configuration == true) then
  local config = slc.config('EMBER_AF_PLUGIN_TUNNELING_SERVER_PERSIST_TUNNELS_TO_TOKEN')
  if (config == nil) then
    -- gecko_sdk-4.5.1 introduced this config; inject the default (disabled) so
    -- the project-space tunneling-server-config.h gains the new option.
    table.insert(changeset, {
      ['option'] = 'EMBER_AF_PLUGIN_TUNNELING_SERVER_PERSIST_TUNNELS_TO_TOKEN',
      ['value'] = tostring(0)
    })
  end
end

return changeset

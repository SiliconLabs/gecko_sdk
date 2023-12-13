local changeset = {}

local old_config_gp_proxy = slc.config('EMBER_GP_PROXY_TABLE_TOKEN_SIZE')
local old_config_gp_sink = slc.config('EMBER_GP_SINK_TABLE_TOKEN_SIZE')

if (old_config_gp_proxy ~= nil) then
  table.insert(changeset, {
    ['option'] = 'EMBER_GP_PROXY_TABLE_TOKEN_SIZE',
    ['action'] = 'remove'
  })
end
if (old_config_gp_sink ~= nil) then
    table.insert(changeset, {
      ['option'] = 'EMBER_GP_SINK_TABLE_TOKEN_SIZE',
      ['action'] = 'remove'
    })
end

return changeset
local changeset = {}

local is_multipan_enabled = slc.config("OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE") ~= nil and
      slc.config("OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE").value == "1"

if is_multipan_enabled then
  table.insert(changeset, {
    ['option'] = 'OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE',
    ['value'] = '1'
  })

  table.insert(changeset, {
    ['option'] = 'OPENTHREAD_CONFIG_MULTIPLE_STATIC_INSTANCE_ENABLE',
    ['value'] = '1'
  })
end
return changeset
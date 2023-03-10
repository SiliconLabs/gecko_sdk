local changeset = {}

local old_config = slc.config('SL_ZIGBEE_OS_STACK_TASK_SIZE')

if (old_config ~= nil) then
  -- The project had a configuration option for ZIGBEE RTOS TASK SIZE
  -- Remove prior setting for ZIGBEE RTOS TASK SIZE (was in words)
  table.insert(changeset, {
    ['option'] = 'SL_ZIGBEE_OS_STACK_TASK_SIZE',
    ['action'] = 'remove'
  })
  -- Re-add setting for ZIGBEE RTOS TASK SIZE (in bytes)
  table.insert(changeset, {
    ['option'] = 'SL_ZIGBEE_OS_STACK_TASK_SIZE',
    ['value'] = tostring(tonumber(old_config.value) * 4)
  })
end

return changeset
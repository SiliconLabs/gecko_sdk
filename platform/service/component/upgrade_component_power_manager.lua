local changeset = {}

if slc.is_provided("power_manager") then
  local old_config = slc.config('SL_POWER_MANAGER_LOWEST_EM_ALLOWED')

  if (old_config.value == '1') then
    table.insert(changeset, {
      ['component'] = 'power_manager_no_deepsleep',
      ['action'] = 'add'
    })
  else 
    if ((old_config.value == '2') or (old_config.value == '3')) then
      table.insert(changeset, {
        ['component'] = 'power_manager_deepsleep',
        ['action'] = 'add'
      })
    end
  end
end

return changeset
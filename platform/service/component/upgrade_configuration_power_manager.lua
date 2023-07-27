local changeset = {}

if slc.is_provided("power_manager") then
  local lowest_em_config = slc.config('SL_POWER_MANAGER_LOWEST_EM_ALLOWED')

  if (lowest_em_config ~= nil) then
    table.insert(changeset, {
      ['option'] = 'SL_POWER_MANAGER_LOWEST_EM_ALLOWED',
      ['action'] = 'remove'
    })
  end
end

return changeset
-- Ncp component to soc application compatibility check

local ncp = slc.is_selected('ncp')

if (ncp == false) then
  validation.error(
    'NCP components are not prepared for integration in SOC applications',
    validation.target_for_project(),
    'Remove NCP components',
    nil
  )
end

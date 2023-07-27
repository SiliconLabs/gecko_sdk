-- Soc component to ncp application compatibility check

local ncp = slc.is_selected('ncp')

if (ncp == true) then
  validation.error(
    'SOC components are not prepared for integration in NCP applications',
    validation.target_for_project(),
    'Remove SoC components',
    nil
  )
end

local no_deepsleep = slc.is_selected("power_manager_no_deepsleep")
local deepsleep = slc.is_selected("power_manager_deepsleep")
if no_deepsleep and deepsleep then
    validation.error('power_manager_no_deepsleep and power_manager_deepsleep are mutually exclusive. Select one or the other based on the desired lowest energy mode.',
    validation.target_for_project())
end
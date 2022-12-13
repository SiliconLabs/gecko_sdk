local config_powermanager_lowest_energy_mode = slc.config("SL_POWER_MANAGER_LOWEST_EM_ALLOWED")
local config_peripheral = slc.config("SL_SLEEPTIMER_PERIPHERAL")

if config_peripheral.value == "SL_SLEEPTIMER_PERIPHERAL_WTIMER" or config_peripheral.value == "SL_SLEEPTIMER_PERIPHERAL_TIMER" then
    if config_powermanager_lowest_energy_mode.value ~= "1" then
        validation.error(
        "Lowest energy mode possible is EM1 when WTIMER/TIMER peripheral is selected",
        validation.target_for_defines({"SL_POWER_MANAGER_LOWEST_EM_ALLOWED"}),
        nil,
        nil)
    end
end
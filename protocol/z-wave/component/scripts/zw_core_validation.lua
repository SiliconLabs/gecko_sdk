-- This validation script checks following:
-- 1. FreeRTOS requires settings
--  1. configUSE_IDLE_HOOK must be set to 1 in Z-Wave application
--  2. configTIMER_TASK_PRIORITY must be set to 55 in Z-Wave application
--  3.1 configMAX_SYSCALL_INTERRUPT_PRIORITY must be set to 32 in Z-Wave application for Series 1
--  3.2 configMAX_SYSCALL_INTERRUPT_PRIORITY must be set to 16 in Z-Wave application for Series 2
--  4.1 configKERNEL_INTERRUPT_PRIORITY must be set to 224 in Z-Wave application for Series 1
--  4.2 configKERNEL_INTERRUPT_PRIORITY must be set to 112 in Z-Wave application for Series 2
--  5. configTIMER_QUEUE_LENGTH must be set to 8 in Z-Wave application
-- 2. sl_device required settings
--  1. SL_DEVICE_INIT_DCDC_BYPASS must be set to 1 in Z_Wave applications
-- 3. sl_psa required settings
--  1. SL_PSA_ITS_USER_MAX_FILES must be set to 32 in Z_Wave applications for Series 2 with Security Vault
--  2. SL_PSA_KEY_USER_SLOT_COUNT must be set to 12 in Z_Wave applications for Series 2 with Security Vault
-- 4. sl_sleeptimer required settings
--  1. SL_SLEEPTIMER_PERIPHERAL must be set to SL_SLEEPTIMER_PERIPHERAL_BURTC in Z_Wave applications for Series 2
-- 5. sl_power_manager
--  1. SL_POWER_MANAGER_LOWEST_EM_ALLOWED must be set to 3 in Z_Wave applications
local device_series_1 = slc.is_provided("device_series_1")
local device_series_2 = slc.is_provided("device_series_2")
local device_security_vault = slc.is_provided("device_security_vault")
local configUSE_IDLE_HOOK = slc.config("configUSE_IDLE_HOOK")
local configTIMER_TASK_PRIORITY = slc.config("configTIMER_TASK_PRIORITY")
local configMAX_SYSCALL_INTERRUPT_PRIORITY = slc.config(
                                                 "configMAX_SYSCALL_INTERRUPT_PRIORITY")
local configKERNEL_INTERRUPT_PRIORITY = slc.config(
                                            "configKERNEL_INTERRUPT_PRIORITY")
local configTIMER_QUEUE_LENGTH = slc.config("configTIMER_QUEUE_LENGTH")
local SL_DEVICE_INIT_DCDC_BYPASS = slc.config("SL_DEVICE_INIT_DCDC_BYPASS")
local SL_PSA_ITS_USER_MAX_FILES = slc.config("SL_PSA_ITS_USER_MAX_FILES")
local SL_PSA_KEY_USER_SLOT_COUNT = slc.config("SL_PSA_KEY_USER_SLOT_COUNT")
local SL_SLEEPTIMER_PERIPHERAL = slc.config("SL_SLEEPTIMER_PERIPHERAL")
local SL_SLEEPTIMER_FREQ_DIVIDER = slc.config("SL_SLEEPTIMER_FREQ_DIVIDER")
local SL_POWER_MANAGER_LOWEST_EM_ALLOWED = slc.config("SL_POWER_MANAGER_LOWEST_EM_ALLOWED")

function validate_config_component(config, value)
    if config.value ~= value then
        validation.error('Z-Wave requires ' .. config.id .. ' to be set to ' ..
                             value .. '.',
                         validation.target_for_defines({config.id}), nil, nil)
    end
end

validate_config_component(configUSE_IDLE_HOOK, "1")
validate_config_component(configTIMER_TASK_PRIORITY, "55")

if device_series_1 then
    validate_config_component(configMAX_SYSCALL_INTERRUPT_PRIORITY, "32")
    validate_config_component(configKERNEL_INTERRUPT_PRIORITY, "224")
end

if device_series_2 then
    validate_config_component(configMAX_SYSCALL_INTERRUPT_PRIORITY, "16")
    validate_config_component(configKERNEL_INTERRUPT_PRIORITY, "112")
end

validate_config_component(configTIMER_QUEUE_LENGTH, "8")

-- sl_device
validate_config_component(SL_DEVICE_INIT_DCDC_BYPASS, "1")

-- sl_psa
if device_series_2 and device_security_vault then
    validate_config_component(SL_PSA_ITS_USER_MAX_FILES, "32")
    validate_config_component(SL_PSA_KEY_USER_SLOT_COUNT, "12")
end

-- sl_sleeptimer
if device_series_2 then
    validate_config_component(SL_SLEEPTIMER_PERIPHERAL, "SL_SLEEPTIMER_PERIPHERAL_BURTC")
end

-- sl_board
validate_config_component(SL_POWER_MANAGER_LOWEST_EM_ALLOWED, "3")

--
-- EOF
-- 

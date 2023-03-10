-- Validation script for bootlaoder debug

local debug_print_enable = slc.config('SL_DEBUG_PRINT')
local debug_peripheral   = slc.config('SL_DEBUG_PERIPHERAL')
local debug_port         = slc.config('SL_DEBUG_SWV_PORT')
local debug_pin          = slc.config('SL_DEBUG_SWV_PIN')

if debug_print_enable.value == "1" then
    if (not debug_peripheral) or (not debug_port) or (not debug_pin) then
        validation.error('Please Configure GPIO peripheral for SWO', validation.target_for_project())
    end
end

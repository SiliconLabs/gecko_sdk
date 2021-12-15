-- automatic conversion of input parameters
function autonumber(input)
    local base = 10
    local orig_input = input
    if (type(input) == "string") then
        input = input:gsub("[\(\)\"uUlL]", "")
        if string.find(input,"[bxhBXH]") ~= nil then
            if string.find(string.lower(input), "0b") == 1 then
                input = input:gsub("[bB]","")
                base = 2
            elseif string.find(string.lower(input), "0x") == 1 then
                input = input:gsub("[xXhH]","")
                base = 16
            end
        elseif string.find(input, "0") == 1 then
            base = 8
        end
    elseif (type(input) == "number") then
        return input
    else
        logit("autonumber() expects either a string or a number!")
        return nil
    end
    local result = tonumber(input, base)
    if result == nil then
        logit("Configured value is not valid: \"" .. tostring(orig_input) .. "\" - modify it to a numeric value!")
    end
    return result
end

-- simple_timer_freertos_static validation for configUSE_TIMERS and configSUPPORT_STATIC_ALLOCATION
local timer_enable = autonumber(slc.config('configUSE_TIMERS').value)
local enable_static = autonumber(slc.config('configSUPPORT_STATIC_ALLOCATION').value)

if timer_enable ~= nil and timer_enable == 0 then
        validation.error("Kernel configUSE_TIMERS config needs to be enabled",
        validation.target_for_defines({"configUSE_TIMERS"}),
        nil,
        nil)
    end

if enable_static ~= nil and enable_static == 0 then
        validation.error("Kernel configSUPPORT_STATIC_ALLOCATION config needs to be enabled",
        validation.target_for_defines({"configSUPPORT_STATIC_ALLOCATION"}),
        nil,
        nil)
    end



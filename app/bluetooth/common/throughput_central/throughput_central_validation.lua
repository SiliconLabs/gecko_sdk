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

-- throughput central validation script for checking MAC adress formats in allowlist
local slots = { 
    {
        name = "Slot 1",
        enable = "THROUGHPUT_CENTRAL_ALLOWLIST_SLOT_1_ENABLE",
        slot = "THROUGHPUT_CENTRAL_ALLOWLIST_SLOT_1"
    },
    {
        name = "Slot 2",
        enable = "THROUGHPUT_CENTRAL_ALLOWLIST_SLOT_2_ENABLE",
        slot = "THROUGHPUT_CENTRAL_ALLOWLIST_SLOT_2"
    },
    {
        name = "Slot 3",
        enable = "THROUGHPUT_CENTRAL_ALLOWLIST_SLOT_3_ENABLE",
        slot = "THROUGHPUT_CENTRAL_ALLOWLIST_SLOT_3"
    },
    {
        name = "Slot 4",
        enable = "THROUGHPUT_CENTRAL_ALLOWLIST_SLOT_4_ENABLE",
        slot = "THROUGHPUT_CENTRAL_ALLOWLIST_SLOT_4"
    }
}

local mac_pattern = "(%x%x:%x%x:%x%x:%x%x:%x%x:%x%x)"

function check_mac(address)
    local maclist = string.match(address,mac_pattern)
    if maclist ~= nil then
        if maclist == address then
            return true
        end
    end
    return false
end

local wl_enabled = autonumber(slc.config("THROUGHPUT_CENTRAL_ALLOWLIST_ENABLE").value)

if wl_enabled ~= nil and wl_enabled == 1 then
    for k,v in pairs(slots) do
        local slot_enabled = autonumber(slc.config(v.enable).value)
        if slot_enabled ~= nil and slot_enabled == 1 then
                local slot = slc.config(v.slot)
                local slot_formatted = slot.value:gsub("\""," "):gsub("%s","")
            if slot ~= nil then
                local result = check_mac(slot_formatted)
                if not result then
                    validation.error("MAC address " .. slot_formatted .. " for " .. v.name .. " is not valid! ",
                    validation.target_for_defines({v.slot}),
                    "MAC address shall be in FF:FF:FF:FF:FF:FF hexadecimal format.",
                    nil)
                end
            end
        end
    end
end

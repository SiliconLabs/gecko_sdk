-- validation script for proper component configuration
local config_minval = slc.config("ESL_TAG_ADVERTISING_INTERVAL_MIN")
local config_maxval = slc.config("ESL_TAG_ADVERTISING_INTERVAL_MAX")
local config_scheduler_queue_size = slc.config("APP_SCHEDULER_MAX_QUEUE_SIZE")
local config_scheduler_data_size = slc.config("APP_SCHEDULER_MAX_DATA_SIZE")
local config_displays = slc.config("ESL_TAG_MAX_DISPLAYS")
local config_leds = slc.config("ESL_TAG_MAX_LEDS")
local const_min_scheduler_queue = 1
local const_min_data_size = 18

if config_displays ~= nil then
  const_min_scheduler_queue = const_min_scheduler_queue + autonumber_common.autonumber(config_displays.value)
end

if config_leds ~= nil then
  const_min_scheduler_queue = const_min_scheduler_queue + autonumber_common.autonumber(config_leds.value)
end

if const_min_scheduler_queue < 2 then
  const_min_scheduler_queue = 2
end

if config_scheduler_queue_size ~= nil then
  if autonumber_common.autonumber(config_scheduler_queue_size.value) < const_min_scheduler_queue then
    validation.error(
      "The scheduler queue min size (" .. config_scheduler_queue_size.value .. ") shall be greater than or equal to " .. tostring(const_min_scheduler_queue), 
      validation.target_for_defines({"APP_SCHEDULER_MAX_QUEUE_SIZE", "ESL_TAG_MAX_DISPLAYS", "ESL_TAG_MAX_LEDS"}),
      "Please set the APP_SCHEDULER_MAX_QUEUE_SIZE to at least " .. tostring(const_min_scheduler_queue) .. "!",
      nil)
  end
end

if config_scheduler_data_size ~= nil then
  if autonumber_common.autonumber(config_scheduler_data_size.value) < const_min_data_size then
    validation.error(
      "The scheduler min data size (" .. config_scheduler_data_size.value .. ") shall be greater than or equal to " .. tostring(const_min_data_size), 
      validation.target_for_defines({"APP_SCHEDULER_MAX_DATA_SIZE"}),
      "Please set the APP_SCHEDULER_MAX_DATA_SIZE to at least " .. tostring(const_min_data_size) .. "!",
      nil)
  end
end

if config_minval ~= nil and config_maxval ~= nil then
  if autonumber_common.autonumber(config_minval.value) > autonumber_common.autonumber(config_maxval.value) then
    validation.error(
      "The minimum value " .. config_minval.value .. " shall be less than or equal to the maximum value: " .. config_maxval.value, 
      validation.target_for_defines({"ESL_TAG_ADVERTISING_INTERVAL_MIN", "ESL_TAG_ADVERTISING_INTERVAL_MAX"}),
      "Please set these values properly!",
      nil)
  end
end

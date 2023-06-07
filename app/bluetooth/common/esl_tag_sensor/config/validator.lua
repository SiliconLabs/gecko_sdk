-- validation script for proper component configuration
local config_temp_range_enabled = slc.config("ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_ENABLE")
local config_temp_range_minval = slc.config("ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MIN")
local config_temp_range_maxval = slc.config("ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MAX")
local config_manufacturing_date_enabled = slc.config("ESL_SENSOR_MANUFACTURING_DATE_ENABLE")
local config_manufacturing_date_year = slc.config("ESL_SENSOR_MANUFACTURING_YEAR")
local config_manufacturing_date_month = slc.config("ESL_SENSOR_MANUFACTURING_MONTH")
local config_manufacturing_date_day = slc.config("ESL_SENSOR_MANUFACTURING_DAY")

if config_temp_range_enabled ~= nil and autonumber_common.autonumber(config_temp_range_enabled.value) > 0 then
  local error_message = ""
  if config_temp_range_minval == nil or config_temp_range_maxval == nil then
    error_message = "Minimum and maximum values shall be given if the temperature range sensor is enabled!"
  elseif autonumber_common.autonumber(config_temp_range_minval.value) > autonumber_common.autonumber(config_temp_range_maxval.value) then
    error_message = "The minimum value: " .. config_temp_range_minval.value .. " shall be less than the maximum value: " .. config_temp_range_maxval.value
  end
  if error_message ~= "" then
    validation.error(
      error_message,
      validation.target_for_defines({"ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MIN", "ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MAX"}),
      "Please set these values properly!",
      nil)
   end
end

if config_manufacturing_date_enabled ~= nil and autonumber_common.autonumber(config_manufacturing_date_enabled.value) > 0 then
  local config_wallclock_enabled = slc.config("SL_SLEEPTIMER_WALLCLOCK_CONFIG")
  local month_days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
  local months = { "January", "February", "March",  "April", "May", "June", "July",
                   "August", "September", "October", "November", "December"}
  local suffixes = { "th", "st", "nd", "rd" }
  local ordinal = suffixes[1]
  local error_message = ""
  local dependency_error = nil
  if config_wallclock_enabled == nil or autonumber_common.autonumber(config_wallclock_enabled.value) < 1 then
    dependency_error = 1
    error_message = "The Manufacturing Date ESL Sensor feature needs the Sleeptimer wallclock functionality."
  elseif config_manufacturing_date_year == nil or config_manufacturing_date_month == nil or config_manufacturing_date_day == nil then
    error_message = "Manufacturing year, month and day shall be given if the manufacturing date sensor is enabled!"
  else
    local year = autonumber_common.autonumber(config_manufacturing_date_year.value)
    local month = autonumber_common.autonumber(config_manufacturing_date_month.value)
    local day = autonumber_common.autonumber(config_manufacturing_date_day.value)
    local ones = day % 10
    if year % 4 == 0 and (year % 100 ~= 0 or year % 400 == 0) then
      month_days[2] = 29;
    end
    if ones < 4 and ones ~= 0 and (day < 10 or day > 20) then
      ordinal = suffixes[ones + 1]
    end
    if month < 1 or month > 12 then
      error_message = "The given month (" .. month .. ") is invalid."
    elseif year < 2022 then
      error_message = "The given year (" .. year .. ") can't be set."
    elseif day > month_days[month] then
      error_message = "The given date " .. day .. ordinal .." " .. months[month] .. " " .. year ..". is invalid" .. (day == 29 and " (probably " .. year .. " is not a leap year)." or ".")
    end
  end
  if error_message ~= "" then
    if dependency_error == nil then
      validation.error(
        error_message,
        validation.target_for_defines({"ESL_SENSOR_MANUFACTURING_YEAR", "ESL_SENSOR_MANUFACTURING_MONTH", "ESL_SENSOR_MANUFACTURING_DAY"}),
        "Please set manufacturing date properly.",
        nil)
    else
      validation.error(
        error_message,
        validation.target_for_defines({"SL_SLEEPTIMER_WALLCLOCK_CONFIG", "ESL_SENSOR_MANUFACTURING_DATE_ENABLE"}),
        "Please enable the wallclock feature or disable the Date of manufacturing option of the ESL Sensor component.",
        nil)
      validation.error(
        error_message,
        validation.target_for_defines({"ESL_SENSOR_MANUFACTURING_DATE_ENABLE", "ESL_SENSOR_MANUFACTURING_YEAR", "ESL_SENSOR_MANUFACTURING_MONTH", "ESL_SENSOR_MANUFACTURING_DAY"}),
        "Please enable the wallclock option of the Sleeptimer component or disable the Date of manufacturing.",
        nil)
    end
   end
end

/**
 * @file
 * Configuration file for the CC Battery Config
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <cc_battery_config.h>
#include <CC_Battery.h>

uint8_t cc_battery_config_get_reporting_decrements(void)
{
  return CC_BATTERY_REPORTING_DECREMENTS;
}

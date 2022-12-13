/**
 * @file
 * Command Class Wakeup Config
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include "cc_wake_up_config.h"
#include "cc_wake_up_config_api.h"

uint32_t cc_wake_up_config_get_default_sleep_time_sec(void)
{
  return CC_WAKE_UP_CONFIG_DEFAULT_SLEEP_TIME_SEC;
}

uint32_t cc_wake_up_config_get_minimum_sleep_time_sec(void)
{
  return CC_WAKE_UP_CONFIG_MINIMUM_SLEEP_TIME_SEC;
}

uint32_t cc_wake_up_config_get_maximum_sleep_time_sec(void)
{
  return CC_WAKE_UP_CONFIG_MAXIMUM_SLEEP_TIME_SEC;
}

uint32_t cc_wake_up_config_get_sleep_step_time_sec(void)
{
  return CC_WAKE_UP_CONFIG_SLEEP_STEP_TIME_SEC;
}

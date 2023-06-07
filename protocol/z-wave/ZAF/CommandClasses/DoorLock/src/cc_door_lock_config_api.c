/**
 * @file
 * Configuration file for the ZAF
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <cc_door_lock_config_api.h>
#include <cc_door_lock_config.h>
#include <CC_DoorLock.h>

cc_door_lock_operation_type_t
cc_door_lock_get_operation_type(void)
{
  return CC_DOOR_LOCK_OPERATION_TYPE;
}

cc_door_lock_handle_t
cc_door_lock_get_supported_inside_handles(void)
{
  return CC_DOOR_LOCK_SUPPORTED_INSIDE_HANDLES;
}

cc_door_lock_handle_t
cc_door_lock_get_supported_outside_handles(void)
{
  return CC_DOOR_LOCK_SUPPORTED_OUTSIDE_HANDLES;
}

uint8_t
cc_door_lock_get_options_flags(void)
{
  return CC_DOOR_LOCK_OPTIONS_FLAGS;
}

uint16_t
cc_door_lock_get_max_auto_relock_time(void)
{
  return CC_DOOR_LOCK_MAX_AUTO_RELOCK_TIME;
}

uint16_t
cc_door_lock_get_max_hold_and_release_time(void)
{
  return CC_DOOR_LOCK_MAX_HOLD_AND_RELEASE_TIME;
}

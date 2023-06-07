/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef CC_DOOR_LOCK_CONFIG_API_H
#define CC_DOOR_LOCK_CONFIG_API_H

#include <CC_DoorLock.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup DoorLock
 * @{
 */

cc_door_lock_operation_type_t cc_door_lock_get_operation_type(void);

cc_door_lock_handle_t cc_door_lock_get_supported_inside_handles(void);

cc_door_lock_handle_t cc_door_lock_get_supported_outside_handles(void);

uint8_t cc_door_lock_get_options_flags(void);

uint16_t cc_door_lock_get_max_auto_relock_time(void);

uint16_t cc_door_lock_get_max_hold_and_release_time(void);

/**
 * @}
 * @}
 */ 

#endif /* CC_DOOR_LOCK_CONFIG_API_H */

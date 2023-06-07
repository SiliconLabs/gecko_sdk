/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef CC_DOOR_LOCK_IO_H
#define CC_DOOR_LOCK_IO_H

#include <CC_DoorLock.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup DoorLock
 * @{
 */
bool cc_door_lock_write(cc_door_lock_data_t *door_lock_data);
bool cc_door_lock_read(cc_door_lock_data_t *door_lock_data);
void cc_door_lock_migrate(void);

/**
 * @}
 * @}
 */ 

#endif /* CC_DOOR_LOCK_IO_H */


/**
 * @file
 * Command Class Notification I/O interface
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef CC_NOTIFICATION_IO_H
#define CC_NOTIFICATION_IO_H

#include <stdbool.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup Notification
 * @{
 * @addtogroup cc_notification_storage Storage for CC Notification
 * @{
 */

/**
 * Writes CC Notification data.
 * @return true on success, false otherwise.
 */
bool cc_notification_write(void);

/**
 * Reads CC Notification data.
 * @return true on success, false otherwise.
 */
bool cc_notification_read(void);

/**
 * @}
 * @}
 * @}
 */ 

#endif /* CC_NOTIFICATION_IO_H */

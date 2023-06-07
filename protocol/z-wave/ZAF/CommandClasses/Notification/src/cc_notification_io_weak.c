/**
 * @file
 * Command Class Notification I/O handling weak
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include "cc_notification_io.h"
#include "ZW_typedefs.h"

ZW_WEAK bool cc_notification_write (void) {
  return true;
}

ZW_WEAK bool cc_notification_read (void) {
  return false;
}

/**
 * @file
 * Command Class User Code I/O handling
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <cc_door_lock_io.h>
#include <ZW_typedefs.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

ZW_WEAK bool
cc_door_lock_write(__attribute__((unused)) cc_door_lock_data_t *door_lock_data)
{
  return true;
}

ZW_WEAK bool
cc_door_lock_read(__attribute__((unused)) cc_door_lock_data_t *door_lock_data)
{
  return false;
}

ZW_WEAK void
cc_door_lock_migrate(void)
{
}

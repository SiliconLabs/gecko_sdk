/**
 * @file
 * Command Class Battery I/O handling
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include "cc_battery_io.h"
#include <ZW_typedefs.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

ZW_WEAK bool
cc_battery_write(SBatteryData* battery_data)
{
  UNUSED(battery_data);

  return true;
}

ZW_WEAK bool
cc_battery_read(SBatteryData* battery_data)
{
  UNUSED(battery_data);

  return false;
}

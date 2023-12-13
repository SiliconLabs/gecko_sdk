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
cc_battery_write(__attribute__((unused)) SBatteryData* battery_data)
{
  return true;
}

ZW_WEAK bool
cc_battery_read(__attribute__((unused)) SBatteryData* battery_data)
{
  return false;
}

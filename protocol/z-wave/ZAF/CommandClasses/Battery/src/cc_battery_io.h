/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef CC_BATTERY_IO_H
#define CC_BATTERY_IO_H

#include <CC_Battery.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup Battery
 * @{
 */

bool cc_battery_write(SBatteryData* battery_data);
bool cc_battery_read(SBatteryData* battery_data);

/**
 * @}
 * @}
 */
#endif /* CC_BATTERY_IO_H */

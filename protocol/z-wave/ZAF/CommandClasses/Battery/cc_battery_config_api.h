/**
 * @file
 * Configuration file for the CC Battery Config
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef _CC_BATTERY_CONFIG_API_H_
#define _CC_BATTERY_CONFIG_API_H_

#include <stdint.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup Battery
 * @{
 */

/**
 * Gets the reporting decrements value
 *
 * @return uint8_t reporting decrements value
 */
uint8_t cc_battery_config_get_reporting_decrements(void);

/**
 * @}
 * @}
 */
#endif /* _CC_BATTERY_CONFIG_API_H_ */

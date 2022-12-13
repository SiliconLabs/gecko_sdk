/**
 * @file
 * Command Class WakeUp Configuration
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_WAKEUP_CONFIG_H
#define CC_WAKEUP_CONFIG_H

#include <stdint.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup WakeUp
 * @{
 */

/**
 * @brief Used by the WakeUp Command Class configuration
 * Returns with the default sleep time in second between Wake Up Notifications.
 * 
 * @return Default sleep time in second between Wake Up Notifications
 */
uint32_t cc_wake_up_config_get_default_sleep_time_sec(void);

/**
 * @brief Used by the WakeUp Command Class configuration
 * Returns with the minimum sleep time in second between Wake Up Notifications.
 * 
 * @return Minimum sleep time in second
 */
uint32_t cc_wake_up_config_get_minimum_sleep_time_sec(void);

/**
 * @brief Used by the WakeUp Command Class configuration
 * Returns with the maximum sleep time in second between Wake Up Notifications.
 * 
 * @return Maximum sleep time in second
 */
uint32_t cc_wake_up_config_get_maximum_sleep_time_sec(void);

/**
 * @brief Used by the WakeUp Command Class configuration
 * Returns with the sleep step time in second.
 * 
 * @return sleep step time in second
 */
uint32_t cc_wake_up_config_get_sleep_step_time_sec(void);

/**
 * @}
 * @}
 */ 

#endif /* CC_WAKEUP_CONFIG_H */

/**
 * @file
 * Platform abstraction for Z-Wave Applications
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */
#ifndef APP_HW_H_
#define APP_HW_H_

/**
 * Initialize hardware modules specific to a given z-wave application.
 *
 * @note Each application/port combination MUST implement this function
 */
extern void app_hw_init(void);

/**
 * Deep sleep wakeup handler. Called after application wakes up from deep sleep.
 *
 * @note Each application/port combination CAN implement this function
 */
void app_hw_deep_sleep_wakeup_handler(void);

#endif /* APP_HW_H_ */

/**
 * @file
 * Platform abstraction for Multilevel Sensor application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#ifndef MULTILEVELSENSOR_HW_H_
#define MULTILEVELSENSOR_HW_H_

#include <ZW_basis_api.h>

/**
 * Initialize hardware modules specific to Multilevel Sensor application.
 */
void MultilevelSensor_hw_init(void);

/**
 * Deep sleep wakeup handler. Called after application wakes up from deep sleep.
 */
void MultilevelSensor_hw_deep_sleep_wakeup_handler(void);

#endif /* MULTILEVELSENSOR_HW_H_ */

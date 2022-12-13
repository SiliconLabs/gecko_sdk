/**
 * @file
 * Platform abstraction for Sensor PIR application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#ifndef SENSORPIR_HW_H_
#define SENSORPIR_HW_H_

#include <stdint.h>
#include <ZW_basis_api.h>

/**
 * Initialize hardware modules specific to Sensor PIR application.
 */
void SensorPIR_hw_init(void);

/**
 * Deep sleep wakeup handler. Called after application wakes up from deep sleep.
 */
void SensorPIR_hw_deep_sleep_wakeup_handler(void);

#endif /* SENSORPIR_HW_H_ */

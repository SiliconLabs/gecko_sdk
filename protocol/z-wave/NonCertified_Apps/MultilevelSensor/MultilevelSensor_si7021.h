/***************************************************************************//**
 * @file MultilevelSensor_interface.h
 * @brief MultilevelSensor_si7021_config.h
 * @copyright 2020 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef MULTILEVELSENSOR_SI7021_H
#define MULTILEVELSENSOR_SI7021_H
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdbool.h>
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define SL_I2CSPM_SENSOR_PERIPHERAL              I2C0
#define SL_I2CSPM_SENSOR_PERIPHERAL_NO           0
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
bool Sensor_si7021_init(void);
bool Sensor_si7021_read_humidity(uint32_t* o_humidity);
bool Sensor_si7021_read_temperature(int32_t* o_temperature);
bool Enable_si7021_temperature_and_humidity_sensor(bool new_state);
// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

#endif  // MULTILEVELSENSOR_SI7021_H

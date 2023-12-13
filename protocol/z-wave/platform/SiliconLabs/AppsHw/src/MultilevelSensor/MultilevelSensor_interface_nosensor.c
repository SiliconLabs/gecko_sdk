/***************************************************************************//**
 * @file MultilevelSensor_interface_no_sensor.c
 * @brief MultilevelSensor_interface_no_sensor.c
 * @copyright 2023 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

// -----------------------------------------------------------------------------
//                   Includes
// -----------------------------------------------------------------------------
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
//#define DEBUGPRINT
#include "DebugPrint.h"
#include <cc_multilevel_sensor_config.h>
#include "ZW_typedefs.h"
#include "sl_status.h"
// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//              Public Function Definitions
// -----------------------------------------------------------------------------

bool
cc_multilevel_sensor_humidity_interface_init(void)
{
  return true;
}

bool
cc_multilevel_sensor_air_temperature_interface_init(void)
{
  return true;
}

bool
cc_multilevel_sensor_ambient_light_interface_init(void)
{
  return true;
}

bool
cc_multilevel_sensor_humidity_interface_deinit(void)
{
  return true;
}

bool
cc_multilevel_sensor_air_temperature_interface_deinit(void)
{
  return true;
}

bool
cc_multilevel_sensor_ambient_light_interface_deinit(void)
{
  return true;
}

bool
cc_multilevel_sensor_humidity_interface_read_value(sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  uint32_t rh_data = 32;

  DPRINTF("Humidity: %d\n", rh_data);

  memset(o_result, 0, sizeof(sensor_read_result_t));
  o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
  o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;
  o_result->raw_result[3] = (uint8_t)(rh_data   & 0xFF);
  o_result->raw_result[2] = (uint8_t)((rh_data >> 8) & 0xFF);
  o_result->raw_result[1] = (uint8_t)((rh_data >> 16) & 0xFF);
  o_result->raw_result[0] = (uint8_t)((rh_data >> 24) & 0xFF);

  return true;
}

bool
cc_multilevel_sensor_air_temperature_interface_read_value(sensor_read_result_t* o_result, uint8_t i_scale)
{
  int32_t temp_data = 32;
  int32_t temperature_fahrenheit;
  float temperature_celsius_divided;

  memset(o_result, 0, sizeof(sensor_read_result_t));
  o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
  o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;

  DPRINTF("Temperature: %d\n", rh_data);

  if (i_scale == SENSOR_SCALE_FAHRENHEIT) {
    temperature_celsius_divided = (float)temp_data / (float)1000;
    temperature_fahrenheit = (int32_t)((temperature_celsius_divided * ((float)9 / (float)5) + (float)32) * 1000);

    o_result->raw_result[3] = (uint8_t)(temperature_fahrenheit & 0xFF);
    o_result->raw_result[2] = (uint8_t)((temperature_fahrenheit >> 8) & 0xFF);
    o_result->raw_result[1] = (uint8_t)((temperature_fahrenheit >> 16) & 0xFF);
    o_result->raw_result[0] = (uint8_t)((temperature_fahrenheit >> 24) & 0xFF);
  } else {
    o_result->raw_result[3] = (uint8_t)(temp_data & 0xFF);
    o_result->raw_result[2] = (uint8_t)((temp_data >> 8) & 0xFF);
    o_result->raw_result[1] = (uint8_t)((temp_data >> 16) & 0xFF);
    o_result->raw_result[0] = (uint8_t)((temp_data >> 24) & 0xFF);
  }

  return true;
}

bool
cc_multilevel_sensor_ambient_light_interface_read_value(sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  uint32_t al_data_int = 32000;

  memset(o_result, 0, sizeof(sensor_read_result_t));
  o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
  o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;

  DPRINTF("Ambient light: %d\n", al_data_int);

  o_result->raw_result[3] = (uint8_t)(al_data_int & 0xFF);
  o_result->raw_result[2] = (uint8_t)((al_data_int >> 8) & 0xFF);
  o_result->raw_result[1] = (uint8_t)((al_data_int >> 16) & 0xFF);
  o_result->raw_result[0] = (uint8_t)((al_data_int >> 24) & 0xFF);

  return true;
}

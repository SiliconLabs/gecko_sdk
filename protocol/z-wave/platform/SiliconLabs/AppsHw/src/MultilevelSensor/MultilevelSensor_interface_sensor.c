/***************************************************************************//**
 * @file MultilevelSensor_interface_sensor.c
 * @brief MultilevelSensor_interface_sensor.c
 * @copyright 2022 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sl_i2cspm.h"
#include "sl_i2cspm_instances.h"
#include "sl_si70xx.h"
#include "sl_veml6035.h"
#include <cc_multilevel_sensor_config.h>
#include "ZW_typedefs.h"
// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                Static Variables
// -----------------------------------------------------------------------------
static bool temperature_humidity_sensor_initialized = false;
static bool ambient_light_sensor_initialized = false;

// -----------------------------------------------------------------------------
//              Static Function
// -----------------------------------------------------------------------------
static bool 
MultilevelSensor_temperature_humidity_sensor_init(void)
{
  sl_status_t sc;

  if(temperature_humidity_sensor_initialized) {
    return true;
  }

  sc = sl_si70xx_init(sl_i2cspm_sensor, SI7021_ADDR);
  
  temperature_humidity_sensor_initialized = (sc == SL_STATUS_OK);

  return temperature_humidity_sensor_initialized;
}

static bool 
MultilevelSensor_temperature_humidity_sensor_deinit(void)
{
  if(!temperature_humidity_sensor_initialized) {
    return true;
  }

  temperature_humidity_sensor_initialized = false;

  return true;
}

static bool
MultilevelSensor_ambient_light_sensor_init(void)
{
  sl_status_t sc;

  if (ambient_light_sensor_initialized)
  {
      return true;
  }

  sc = sl_veml6035_init(sl_i2cspm_sensor, false);

  ambient_light_sensor_initialized = (sc == SL_STATUS_OK);

  return ambient_light_sensor_initialized;

}

static bool
MultilevelSensor_ambient_light_sensor_deinit(void)
{
  if(!ambient_light_sensor_initialized)
  {
      return true;
  }

  ambient_light_sensor_initialized = false;

  return true;
}

static bool 
MultilevelSensor_temperature_humidity_sensor_read(uint32_t *rh_data, int32_t *temp_data)
{
  if(!temperature_humidity_sensor_initialized) {
    return false;
  }

  return (sl_si70xx_measure_rh_and_temp(sl_i2cspm_sensor, SI7021_ADDR, rh_data, temp_data) == SL_STATUS_OK);
}

static bool
MultilevelSensor_ambient_light_sensor_read(float *al_data)
{
  if(!ambient_light_sensor_initialized) {
      return false;
  }

  return (sl_veml6035_get_als_lux(sl_i2cspm_sensor, al_data));
}

// -----------------------------------------------------------------------------
//              Public Function Definitions
// -----------------------------------------------------------------------------

bool 
cc_multilevel_sensor_humidity_interface_init(void)
{
  return MultilevelSensor_temperature_humidity_sensor_init();
}

bool 
cc_multilevel_sensor_air_temperature_interface_init(void)
{
  return MultilevelSensor_temperature_humidity_sensor_init();
}

bool
cc_multilevel_sensor_ambient_light_interface_init(void)
{
  return MultilevelSensor_ambient_light_sensor_init();
}

bool 
cc_multilevel_sensor_humidity_interface_deinit(void)
{
  return MultilevelSensor_temperature_humidity_sensor_deinit();
}

bool 
cc_multilevel_sensor_air_temperature_interface_deinit(void)
{
  return MultilevelSensor_temperature_humidity_sensor_deinit();
}

bool
cc_multilevel_sensor_ambient_light_interface_deinit(void)
{
  return MultilevelSensor_ambient_light_sensor_deinit();
}

bool
cc_multilevel_sensor_humidity_interface_read_value(sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{

  uint32_t rh_data;
  int32_t temp_data;

  if(o_result != NULL)
  {
    memset(o_result, 0, sizeof(sensor_read_result_t));
    o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
    o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;
    
    MultilevelSensor_temperature_humidity_sensor_read(&rh_data, &temp_data);

    DPRINTF("Humidity: %d\n", rh_data);

    o_result->raw_result[3] = (uint8_t)(rh_data   &0xFF);
    o_result->raw_result[2] = (uint8_t)((rh_data>>8 )&0xFF);
    o_result->raw_result[1] = (uint8_t)((rh_data>>16)&0xFF);
    o_result->raw_result[0] = (uint8_t)((rh_data>>24)&0xFF);
  }

  return true;
}

bool 
cc_multilevel_sensor_air_temperature_interface_read_value(sensor_read_result_t* o_result, uint8_t i_scale)
{
  uint32_t rh_data;
  int32_t temp_data, temperature_fahrenheit;
  float temperature_celsius_divided;

  if(o_result != NULL)
  {
    memset(o_result, 0, sizeof(sensor_read_result_t));
    o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
    o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;
    
    MultilevelSensor_temperature_humidity_sensor_read(&rh_data, &temp_data);

    DPRINTF("Temperature: %d\n", rh_data);

    if(i_scale == SENSOR_SCALE_FAHRENHEIT)
    {
      temperature_celsius_divided = (float)temp_data/(float)1000;
      temperature_fahrenheit = (int32_t)((temperature_celsius_divided * ((float)9/(float)5) + (float)32)*1000);

      o_result->raw_result[3] = (uint8_t)(temperature_fahrenheit & 0xFF);
      o_result->raw_result[2] = (uint8_t)((temperature_fahrenheit >> 8 ) & 0xFF);
      o_result->raw_result[1] = (uint8_t)((temperature_fahrenheit >> 16) & 0xFF);
      o_result->raw_result[0] = (uint8_t)((temperature_fahrenheit >> 24) & 0xFF);
    }
    else
    {
      o_result->raw_result[3] = (uint8_t)(temp_data & 0xFF);
      o_result->raw_result[2] = (uint8_t)((temp_data >> 8 ) & 0xFF);
      o_result->raw_result[1] = (uint8_t)((temp_data >> 16) & 0xFF);
      o_result->raw_result[0] = (uint8_t)((temp_data >> 24) & 0xFF);
    }
  }

  return true;
}

bool
cc_multilevel_sensor_ambient_light_interface_read_value(sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  float al_data;
  uint32_t al_data_int;

  if (o_result != NULL)
  {
    memset(o_result, 0, sizeof(sensor_read_result_t));
    o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
    o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;

    MultilevelSensor_ambient_light_sensor_read(&al_data);

    al_data_int = (uint32_t) (al_data * 1000);

    DPRINTF("Ambient light: %d\n", al_data_int);

    o_result->raw_result[3] = (uint8_t)(al_data_int & 0xFF);
    o_result->raw_result[2] = (uint8_t)((al_data_int >> 8 ) & 0xFF);
    o_result->raw_result[1] = (uint8_t)((al_data_int >> 16) & 0xFF);
    o_result->raw_result[0] = (uint8_t)((al_data_int >> 24) & 0xFF);
  }

  return true;
}

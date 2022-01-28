/***************************************************************************//**
 * @file MultilevelSensor_si7021.c
 * @brief MultilevelSensor_si7021.c
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

// -----------------------------------------------------------------------------
//                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "sl_si70xx.h"
#include "MultilevelSensor_si7021.h"

#if defined(BUILDING_WITH_UC)
#include "sl_i2cspm_instances.h"
#else
#include "sl_i2cspm_instances_nonuc.h"
#endif 

// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------
#define SL_I2CSPM_SENSOR_REFERENCE_CLOCK     0
#define SL_I2CSPM_SENSOR_SPEED_MODE          0

#define SL_BOARD_ENABLE_SENSOR_RHT_PORT      gpioPortB
#define SL_BOARD_ENABLE_SENSOR_RHT_PIN       10

#define SL_SENSOR_ENABLE_PORT      gpioPortD
#define SL_SENSOR_ENABLE_PIN       15


#if SL_I2CSPM_SENSOR_SPEED_MODE == 0
#define SL_I2CSPM_SENSOR_HLR i2cClockHLRStandard
#define SL_I2CSPM_SENSOR_MAX_FREQ I2C_FREQ_STANDARD_MAX
#elif SL_I2CSPM_SENSOR_SPEED_MODE == 1
#define SL_I2CSPM_SENSOR_HLR i2cClockHLRAsymetric
#define SL_I2CSPM_SENSOR_MAX_FREQ I2C_FREQ_FAST_MAX
#elif SL_I2CSPM_SENSOR_SPEED_MODE == 2
#define SL_I2CSPM_SENSOR_HLR i2cClockHLRFast
#define SL_I2CSPM_SENSOR_MAX_FREQ I2C_FREQ_FASTPLUS_MAX
#endif
// -----------------------------------------------------------------------------
//              Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                Global Variables
// -----------------------------------------------------------------------------
#ifndef BUILDING_WITH_UC

sl_i2cspm_t *sl_i2cspm_sensor = SL_I2CSPM_SENSOR_PERIPHERAL;

#endif

// -----------------------------------------------------------------------------
//                Static Variables
// -----------------------------------------------------------------------------

static bool is_sensor_inited = false;
// -----------------------------------------------------------------------------
//              Public Function Definitions
// -----------------------------------------------------------------------------

bool Enable_si7021_temperature_and_humidity_sensor(bool new_state)
{
  if(true == new_state)
  {
    GPIO_PinOutSet(SL_SENSOR_ENABLE_PORT, SL_SENSOR_ENABLE_PIN);
  }
  else 
  {
    GPIO_PinOutClear(SL_SENSOR_ENABLE_PORT, SL_SENSOR_ENABLE_PIN);
  }
  return true;
}

bool Sensor_si7021_init(void)
{
  if(is_sensor_inited == false)
  {
    GPIO_PinModeSet(SL_BOARD_ENABLE_SENSOR_RHT_PORT, SL_BOARD_ENABLE_SENSOR_RHT_PIN, gpioModePushPull, 1);
    is_sensor_inited = true;

    if( SL_STATUS_OK != sl_si70xx_init(sl_i2cspm_sensor, SI7021_ADDR))
    {
      return false;
    }
  }
  return true;
}

bool Sensor_si7021_read_temperature(int32_t* o_temperature)
{
  uint32_t humidity  = 0;

  if( SL_STATUS_OK == sl_si70xx_measure_rh_and_temp(SL_I2CSPM_SENSOR_PERIPHERAL, SI7021_ADDR, &humidity, o_temperature))
  {
    return true;    
  }
  return false;
}

bool Sensor_si7021_read_humidity(uint32_t* o_humidity)
{
  int32_t  temperature_celsius = 0;

  if( SL_STATUS_OK == sl_si70xx_measure_rh_and_temp(SL_I2CSPM_SENSOR_PERIPHERAL, SI7021_ADDR, o_humidity, &temperature_celsius))
  {
    return true;    
  }
  return false;
}
// -----------------------------------------------------------------------------
//              Static Function Definitions
// -----------------------------------------------------------------------------

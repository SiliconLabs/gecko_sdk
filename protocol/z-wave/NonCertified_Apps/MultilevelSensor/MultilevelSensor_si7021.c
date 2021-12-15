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
// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------
#define SL_I2CSPM_SENSOR_REFERENCE_CLOCK     0
#define SL_I2CSPM_SENSOR_SPEED_MODE          0

// I2C0 SCL on PC10
#define SL_I2CSPM_SENSOR_SCL_PORT        gpioPortC
#define SL_I2CSPM_SENSOR_SCL_PIN         10
#define SL_I2CSPM_SENSOR_SCL_LOC         14

// I2C0 SDA on PC11
#define SL_I2CSPM_SENSOR_SDA_PORT        gpioPortC
#define SL_I2CSPM_SENSOR_SDA_PIN         11
#define SL_I2CSPM_SENSOR_SDA_LOC         16

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

// -----------------------------------------------------------------------------
//                Static Variables
// -----------------------------------------------------------------------------
sl_i2cspm_t *sl_i2cspm_sensor = SL_I2CSPM_SENSOR_PERIPHERAL;

static I2CSPM_Init_TypeDef init_sensor = {
  .port  = SL_I2CSPM_SENSOR_PERIPHERAL,
  .sclPort = SL_I2CSPM_SENSOR_SCL_PORT,
  .sclPin  = SL_I2CSPM_SENSOR_SCL_PIN,
  .sdaPort = SL_I2CSPM_SENSOR_SDA_PORT,
  .sdaPin  = SL_I2CSPM_SENSOR_SDA_PIN,
#if defined(_SILICON_LABS_32B_SERIES_1)
  .portLocationScl = SL_I2CSPM_SENSOR_SCL_LOC,
  .portLocationSda = SL_I2CSPM_SENSOR_SDA_LOC,
#endif
  .i2cRefFreq = 0,
  .i2cMaxFreq = SL_I2CSPM_SENSOR_MAX_FREQ,
  .i2cClhr = SL_I2CSPM_SENSOR_HLR
};

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
    I2CSPM_Init(&init_sensor);
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

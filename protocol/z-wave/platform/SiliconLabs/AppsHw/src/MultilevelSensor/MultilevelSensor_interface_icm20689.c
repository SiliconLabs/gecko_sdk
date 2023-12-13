/***************************************************************************//**
 * @file MultilevelSensor_interface_icm20689.c
 * @brief MultilevelSensor_interface_icm20689.c
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
#include "sl_imu.h"
#include "CC_MultilevelSensor_SensorHandlerTypes.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "ZW_typedefs.h"

#define IMU_SAMPLE_RATE    10.0f // [Hz]

// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                Global Variables
// -----------------------------------------------------------------------------
bool motion_sensor_initialized = false;
// -----------------------------------------------------------------------------
//                Static Variables
// -----------------------------------------------------------------------------

static bool
get_acceleration_axis_x(int16_t*);

static bool
get_acceleration_axis_y(int16_t*);

static bool
get_acceleration_axis_z(int16_t*);

static bool
acceleration_sensor_init(void);

static bool
acceleration_sensor_deinit(void);

static void
extract_sensor_data(sensor_read_result_t*, int16_t);

//Initialization of the IMU sensor
sl_status_t Multilevel_sensor_imu_init(void)
{
  sl_imu_init();
  sl_imu_configure(IMU_SAMPLE_RATE);
  return SL_STATUS_OK;
}

// Disabling the accelerometer in the IMU sensor
sl_status_t Multilevel_sensor_imu_deinit(void)
{
  return sl_imu_deinit();
}

// Reading the accelerometer data from the IMU sensor
sl_status_t read_xyz_acceleration(int16_t *xyz_acceleration)
{
  int16_t acceleration_vector[3];

  sl_imu_update();
  while (!sl_imu_is_data_ready()) {
    // wait for data ready
  }

  sl_imu_get_acceleration(acceleration_vector);
  memcpy(xyz_acceleration, acceleration_vector, sizeof(int16_t) * 3);

  return SL_STATUS_OK;
}

bool
cc_multilevel_sensor_motion_axis_x_interface_read_value(sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  int16_t ma_x_data = 0;

  if (o_result != NULL) {
    memset(o_result, 0, sizeof(sensor_read_result_t));
    o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
    o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;

    get_acceleration_axis_x(&ma_x_data);
    extract_sensor_data(o_result, ma_x_data);
    DPRINTF("Motion x-axis: %d\n", ma_x_data);
  }

  return true;
}

bool
cc_multilevel_sensor_motion_axis_y_interface_read_value(sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  int16_t ma_y_data = 0;

  if (o_result != NULL) {
    memset(o_result, 0, sizeof(sensor_read_result_t));
    o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
    o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;

    get_acceleration_axis_y(&ma_y_data);
    extract_sensor_data(o_result, ma_y_data);
    DPRINTF("Motion y-axist: %d\n", ma_y_data);
  }

  return true;
}

bool
cc_multilevel_sensor_motion_axis_z_interface_read_value(sensor_read_result_t* o_result, __attribute__((unused)) uint8_t i_scale)
{
  int16_t ma_z_data = 0;

  if (o_result != NULL) {
    memset(o_result, 0, sizeof(sensor_read_result_t));
    o_result->precision  = SENSOR_READ_RESULT_PRECISION_3;
    o_result->size_bytes = SENSOR_READ_RESULT_SIZE_4;

    get_acceleration_axis_z(&ma_z_data);
    extract_sensor_data(o_result, ma_z_data);
    DPRINTF("Motion z-axis: %d\n", ma_z_data);
  }

  return true;
}

bool
cc_multilevel_sensor_motion_axis_x_interface_init(void)
{
  return acceleration_sensor_init();
}

bool
cc_multilevel_sensor_motion_axis_y_interface_init(void)
{
  return acceleration_sensor_init();
}

bool
cc_multilevel_sensor_motion_axis_z_interface_init(void)
{
  return acceleration_sensor_init();
}

bool
cc_multilevel_sensor_motion_axis_x_interface_deinit(void)
{
  return acceleration_sensor_deinit();
}

bool
cc_multilevel_sensor_motion_axis_y_interface_deinit(void)
{
  return acceleration_sensor_deinit();
}

bool
cc_multilevel_sensor_motion_axis_z_interface_deinit(void)
{
  return acceleration_sensor_deinit();
}
// -----------------------------------------------------------------------------
//              Static Function
// -----------------------------------------------------------------------------

static bool
get_acceleration_axis_x(int16_t* ma_x)
{
  int16_t xyz_acceleration[3] = { 0, 0, 0 };
  sl_status_t sc = SL_STATUS_OK;

  // This is a workaround for the fact that the sensor lost its calibration after waking up from EM4 sleep
  Multilevel_sensor_imu_init();
  if (!motion_sensor_initialized) {
    return false;
  }

  read_xyz_acceleration(xyz_acceleration);

  *ma_x = xyz_acceleration[0];

  return sc;
}

static bool
get_acceleration_axis_y(int16_t* ma_y)
{
  int16_t xyz_acceleration[3] = { 0, 0, 0 };
  sl_status_t sc = SL_STATUS_OK;

  if (!motion_sensor_initialized) {
    return false;
  }

  read_xyz_acceleration(xyz_acceleration);

  *ma_y = xyz_acceleration[1];

  return sc;
}

static bool
get_acceleration_axis_z(int16_t* ma_z)
{
  int16_t xyz_acceleration[3] = { 0, 0, 0 };
  sl_status_t sc = SL_STATUS_OK;

  if (!motion_sensor_initialized) {
    return false;
  }

  read_xyz_acceleration(xyz_acceleration);

  *ma_z = xyz_acceleration[2];

  return sc;
}

static bool
acceleration_sensor_init(void)
{
  sl_status_t sc;

  if (motion_sensor_initialized) {
    return true;
  }

  sc = Multilevel_sensor_imu_init();

  motion_sensor_initialized = (sc == SL_STATUS_OK);

  if (!motion_sensor_initialized) {
    return false;
  }

  return motion_sensor_initialized;
}

static bool
acceleration_sensor_deinit(void)
{
  sl_status_t sc;

  if (!motion_sensor_initialized) {
    return true;
  }

  sc = Multilevel_sensor_imu_deinit();

  motion_sensor_initialized = !(sc == SL_STATUS_OK);

  return true;
}

static void
extract_sensor_data(sensor_read_result_t* o_result, int16_t raw_axis_data)
{
  int32_t extracted_data  = (int32_t)(raw_axis_data * 1000);
  o_result->raw_result[3] = (uint8_t)(extracted_data & 0xFF);
  o_result->raw_result[2] = (uint8_t)((extracted_data >> 8) & 0xFF);
  o_result->raw_result[1] = (uint8_t)((extracted_data >> 16) & 0xFF);
  o_result->raw_result[0] = (uint8_t)((extracted_data >> 24) & 0xFF);
}

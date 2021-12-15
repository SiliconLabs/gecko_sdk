/***************************************************************************//**
 * @file
 * @brief Inertial Measurement Unit sensor
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "sl_board_control.h"
#include "sl_imu.h"
#include "app_assert.h"
#include "sl_sensor_imu.h"

// -----------------------------------------------------------------------------
// Configuration

#define IMU_SAMPLE_RATE    5.0f /* Hz */

// -----------------------------------------------------------------------------
// Public function definitions

void sl_sensor_imu_init(void)
{
  (void)sl_board_enable_sensor(SL_BOARD_SENSOR_IMU);
}

void sl_sensor_imu_deinit(void)
{
  (void)sl_board_disable_sensor(SL_BOARD_SENSOR_IMU);
}

void sl_sensor_imu_enable(bool enable)
{
  sl_status_t sc;
  uint8_t state = sl_imu_get_state();
  if (enable && (IMU_STATE_DISABLED == state)) {
    sc = sl_imu_init();
    app_assert_status(sc);
    sl_imu_configure(IMU_SAMPLE_RATE);
  } else if (!enable && (IMU_STATE_READY == state)) {
    sl_imu_deinit();
  }
}

sl_status_t sl_sensor_imu_get(int16_t ovec[3], int16_t avec[3])
{
  sl_status_t sc = SL_STATUS_NOT_READY;
  if (sl_imu_is_data_ready()) {
    sl_imu_update();
    sl_imu_get_orientation(ovec);
    sl_imu_get_acceleration(avec);
    sc = SL_STATUS_OK;
  }
  return sc;
}

sl_status_t sl_sensor_imu_calibrate(void)
{
  return sl_imu_calibrate_gyro();
}

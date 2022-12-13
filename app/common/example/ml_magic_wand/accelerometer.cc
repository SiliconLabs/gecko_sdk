/***************************************************************************//**
 * @file
 * @brief Functionality for reading accelerometer data from IMU
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

#include "accelerometer.h"
#include "constants.h"
#include "sl_imu.h"
#include "gpiointerrupt.h"
#include "em_gpio.h"
#include "em_core.h"
#include <cstdio>

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if defined (SL_CATALOG_ICM20689_DRIVER_PRESENT)
#include "sl_icm20689_config.h"
#define  SL_IMU_INT_PORT SL_ICM20689_INT_PORT
#define  SL_IMU_INT_PIN  SL_ICM20689_INT_PIN
#elif defined (SL_CATALOG_ICM20648_DRIVER_PRESENT)
#include "sl_icm20648_config.h"
#define  SL_IMU_INT_PORT SL_ICM20648_INT_PORT
#define  SL_IMU_INT_PIN  SL_ICM20648_INT_PIN
#else
#error "No IMU driver defined"
#endif

// Size of the IMU data buffer in elements
#define IMU_BUFFER_SIZE   200

// Accelerometer data from sensor
typedef struct imu_data {
  int16_t x;
  int16_t y;
  int16_t z;
} imu_data_t;

// IMU data buffer
static imu_data_t buffer[IMU_BUFFER_SIZE];

// Current head pointer of the buffer
static int head_ptr = 0;

// Wait for buffer to be filled first time
static bool init_done = false;

// Called when the IMU has data available using gpio interrupt.
static void on_data_available(uint8_t int_id, void *ctx)
{
  (void) int_id;
  (void) ctx;

  if (!sl_imu_is_data_ready()) {
    return;
  }
  sl_imu_update();

  int16_t m[3];
  sl_imu_get_acceleration(m);

  buffer[head_ptr].x = m[0];
  buffer[head_ptr].y = m[1];
  buffer[head_ptr].z = m[2];
  head_ptr += 1;

  if (head_ptr >= SEQUENCE_LENGTH) {
    init_done = true;
  }

  if (head_ptr >= IMU_BUFFER_SIZE) {
    head_ptr = 0;
    init_done = true;
  }
}

sl_status_t accelerometer_setup(void)
{
  sl_status_t status = SL_STATUS_OK;
  int int_id;

  // Initialize accelerometer sensor
  status = sl_imu_init();
  if (status != SL_STATUS_OK) {
    return status;
  }
  sl_imu_configure(ACCELEROMETER_FREQ);
  // Setup interrupt from accelerometer on falling edge
  GPIO_PinModeSet(SL_IMU_INT_PORT, SL_IMU_INT_PIN, gpioModeInput, 0);
  int_id = GPIOINT_CallbackRegisterExt(SL_IMU_INT_PIN, on_data_available, NULL);
  if (int_id != INTERRUPT_UNAVAILABLE) {
    GPIO_ExtIntConfig(SL_IMU_INT_PORT, SL_IMU_INT_PIN, int_id, false, true, true);
  } else {
    status = SL_STATUS_FAIL;
  }
  return status;
}

sl_status_t accelerometer_read(acc_data_t* dst, int n)
{
  if (init_done == false) {
    return SL_STATUS_FAIL;
  }

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();

  for (int i = 0; i < n; i++) {
    int index = head_ptr - n + i;
    if (index < 0 ) {
      index += IMU_BUFFER_SIZE;
    }
    imu_data_t src = buffer[index];

    dst[i].x = src.x;
    dst[i].y = src.y;
    dst[i].z = src.z;
  }
  CORE_EXIT_CRITICAL();
  return SL_STATUS_OK;
}


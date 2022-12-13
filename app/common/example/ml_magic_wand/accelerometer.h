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

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "sl_status.h"

// Accelerometer data structure used by the model
typedef struct acc_data {
  float x;
  float y;
  float z;
} acc_data_t;

/***************************************************************************//**
 * @brief
 *   Configure accelerometer to read data regularly to an internal buffer.
 *
 * @return
 *   SL_STATUS_OK on success, other value on failure.
 ******************************************************************************/
sl_status_t accelerometer_setup(void);

/***************************************************************************//**
 * @brief
 *   Read data from accelerometer buffer into the machine model input buffer.
 *
 * @param dst
 *   Machine learning model input buffer.
 *
 * @param n
 *   Number of elements to read
 *
 * @return
 *   SL_STATUS_OK on success, other value on failure.
 ******************************************************************************/
sl_status_t accelerometer_read(acc_data_t* dst, int n);

#endif // ACCELEROMETER_H

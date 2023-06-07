/***************************************************************************//**
 * @file
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "cslib_hwconfig.h"
#include "hardware_routines.h"
#include "cslib_config.h"

/// @brief Derive thresholds at init based on config profile settings
uint16_t active_thresh[DEF_NUM_SENSORS];
uint16_t inactive_thresh[DEF_NUM_SENSORS];

/// @brief analog mux setting for sensor
const uint16_t CSLIB_muxInput[DEF_NUM_SENSORS] =
{
  CSLIB_MUX_INPUT
};

/// @brief Mapping between sensors and pins
const uint8_t CSLIB_muxValues[DEF_NUM_SENSORS] =
{
  MUX_VALUE_ARRAY
};

/// @brief inactive->active threshold for sensors
const uint8_t CSLIB_activeThreshold[DEF_NUM_SENSORS] =
{
  ACTIVE_THRESHOLD_ARRAY
};

/// @brief active->inactive threshold for sensors
const uint8_t CSLIB_inactiveThreshold[DEF_NUM_SENSORS] =
{
  INACTIVE_THRESHOLD_ARRAY
};

/// @brief describes expected |raw touch - raw untouch| value
const uint8_t CSLIB_averageTouchDelta[DEF_NUM_SENSORS] =
{
  AVERAGE_TOUCH_DELTA_ARRAY
};

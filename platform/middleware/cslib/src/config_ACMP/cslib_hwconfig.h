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

#ifndef CSLIB_HW_CONFIG_H
#define CSLIB_HW_CONFIG_H

#include "em_lesense.h"
#include "em_gpio.h"

/**************************************************************************//**
 *
 * @addtogroup cslib_HWconfig CSLIB library hardware configuration
 * @{
 *
 * @brief Hardware configuration for CSLIB
 *
 * These definitions configure the capacitive sensing hardware in
 * active and sleep mode scans.  They also configure channel-by-channel
 * thresholds and expected touchd deltas.
 *
 *****************************************************************************/

/// @brief Defines the size of the sensor node array.
/// Also defines volatile arrays that have a one-to-one correspondence
/// to the number of sensors in the project.
/// @note Minimum value is 1, maximum value is the number of capacitive
/// sensing-enabled pins on the device
#define DEF_NUM_SENSORS                           2

/// @brief Cross reference between sensor number ordering and pin
/// ordering.  This allows for using pins that are not in order when
/// doing layout.
#define MUX_VALUE_ARRAY 0, 1

/// @brief Per channel active threshold setting
/// @note Minimum threshold used is @ref INACTIVE_THRESHOLD_ARRAY value,
/// maximum value is 100
#define ACTIVE_THRESHOLD_ARRAY 70, 70

/// @brief Per channel inactive threshold setting
/// @note Minimum threshold used is 1, maximum value is @ref ACTIVE_THRESHOLD_ARRAY
#define INACTIVE_THRESHOLD_ARRAY 30, 30

/// @brief Per-channel expected touch delta.  This value describes the difference
/// in capacitive sensing output codes between the inactive/baseline of the sensor,
/// and the output of the sensor when active(touched).
/// @note These values should be defined in terms of X/16, or X>>4, as they are stored
/// in a packed byte array
#define AVERAGE_TOUCH_DELTA_ARRAY 64 >> 4, 64 >> 4

/// @brief Per channel ACMP_CAPSENSE channel value for each enabled sensor
#define CSLIB_MUX_INPUT 3, 4

/// @brief Array stores ACMP input settings
extern const uint16_t CSLIB_muxInput[];

/// @brief Array of cross-references between sensor number and actual pin number
extern const uint8_t CSLIB_muxValues[];

/// @brief Only send comms after new values
extern uint8_t sendComms;

/** @} (end cslib_HWconfig) */
#endif // __CSLIB_HW_CONFIG_H__

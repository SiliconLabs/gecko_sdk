/***************************************************************************//**
 * @file
 * @brief In-Place Over-the-Air Device Firmware Update Configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BT_IN_PLACE_OTA_DFU_CONFIG_H
#define SL_BT_IN_PLACE_OTA_DFU_CONFIG_H

/***********************************************************************************************//**
 * @addtogroup in_place_ota_dfu
 * @{
 **************************************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h> In-Place OTA DFU Security

// <q SL_BT_IN_PLACE_OTA_DFU_BONDING_REQUIRED> Bonding required for OTA transfer

// <i> Bonding required to proceed with the in-place OTA transfer.
// <i> User must realize bonding process and shall implement a strong
// <i> 'sl_bt_in_place_ota_dfu_security_status' callback to decide if
// <i> it is safe to start the OTA transfer or not.
// <i> Default: 0
#define SL_BT_IN_PLACE_OTA_DFU_BONDING_REQUIRED            0

// </h>

// <h> In-Place OTA DFU Transfer

// <o SL_BT_IN_PLACE_OTA_DFU_CALC_DELAY_MULTIPLIER> Calculated delay multiplier <3-20>

// <i> 'Connection interval x 1.25 msec x (1 + latency)' will be multiplied by this configurable value.
// <i> Default: 5
#define SL_BT_IN_PLACE_OTA_DFU_CALC_DELAY_MULTIPLIER       5

// <o SL_BT_IN_PLACE_OTA_DFU_MIN_DELAY_TO_DISCONNECT> Minimum delay [msec] <10-5000>

// <i> Closing the connection after a calculated millisecond delay.
// <i> The length of the delay is calculated from the connection interval and latency with a configurable multiplier
// <i> and it has to be greater than a minimum value. This configuration parameter sets the minimum value.
// <i> Default: 1000
#define SL_BT_IN_PLACE_OTA_DFU_MIN_DELAY_TO_DISCONNECT     1000

// </h>

// <<< end of configuration section >>>

/** @} (end addtogroup in_place_ota_dfu) */
#endif // SL_BT_IN_PLACE_OTA_DFU_CONFIG_H

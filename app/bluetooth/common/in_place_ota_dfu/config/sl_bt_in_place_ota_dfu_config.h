/***************************************************************************//**
 * @file
 * @brief In-Place Over-the-Air Device Firmware Update Configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

// <<< Use Configuration Wizard in Context Menu >>>

// <h> In-Place OTA DFU Security Configuration

// <q SL_BT_IN_PLACE_OTA_DFU_BONDING_REQUIRED> Bonding required for OTA transfer

// <i> Bonding required to proceed with the in-place OTA transfer.
// <i> User must realize bonding process and shall implement a strong
// <i> 'sl_bt_in_place_ota_dfu_security_status' callback to decide if
// <i> it is safe to start the OTA transfer or not.
// <i> Default: 0
#define SL_BT_IN_PLACE_OTA_DFU_BONDING_REQUIRED 0

// </h>

// <<< end of configuration section >>>

#endif // SL_BT_IN_PLACE_OTA_DFU_CONFIG_H

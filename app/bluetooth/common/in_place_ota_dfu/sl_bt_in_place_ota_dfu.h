/***************************************************************************//**
 * @file
 * @brief In-Place Over-the-Air Device Firmware Update
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

#ifndef SL_BT_IN_PLACE_OTA_DFU_H
#define SL_BT_IN_PLACE_OTA_DFU_H

/***********************************************************************************************//**
 * @addtogroup in_place_ota_dfu
 * @{
 **************************************************************************************************/

#include "sl_bt_api.h"
#include "sl_bt_in_place_ota_dfu_config.h"

// In-place OTA DFU security status enumerator
typedef enum {
  SL_BT_IN_PLACE_OTA_DFU_SECURITY_DENY = 0,
  SL_BT_IN_PLACE_OTA_DFU_SECURITY_ACCEPT
} sl_bt_in_place_ota_dfu_security_sts_t;
/**************************************************************************//**
 * Bluetooth stack event handler.
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_in_place_ota_dfu_on_event(sl_bt_msg_t *evt);

/**************************************************************************//**
 * Callback function to check security requirements before starting the
 * in-place OTA DFU transfer.
 * At least bonding is mandatory for a secure In-Place OTA DFU transfer.
 * The device parameters are provided:
 * @param[in] address Bluetooth address of the device.
 * @param[in] connection Connection handle.
 * @param[in] bonding Bonding handle.
 * @note To be implemented in user code.
 *****************************************************************************/
sl_bt_in_place_ota_dfu_security_sts_t sl_bt_in_place_ota_dfu_security_status(bd_addr address,
                                                                             uint8_t connection,
                                                                             uint8_t bonding);
/** @} (end addtogroup in_place_ota_dfu) */
#endif // SL_BT_IN_PLACE_OTA_DFU_H

/***************************************************************************//**
 * @file
 * @brief In-Place Over-the-Air Device Firmware Update
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

#include <math.h>
#include <stddef.h>
#include "em_common.h"
#include "gatt_db.h"
#include "app_assert.h"
#include "sl_apploader_util.h"
#include "sl_bt_in_place_ota_dfu.h"
#include "sl_bt_in_place_ota_dfu_config.h"
#include "app_timer.h"

// Connection interval time resolution. Time = interval x 1.25 ms
#define CONN_INTERVAL_TIME_RESOLUTION_MS  1.25f

// Flag for indicating DFU reset must be performed.
static bool boot_to_dfu = false;
static app_timer_t connection_close_delay;
static uint32_t delay_additional_ms = SL_BT_IN_PLACE_OTA_DFU_MIN_DELAY_TO_DISCONNECT;

static void delay_timer_cb(app_timer_t *handle, void *data);
static uint32_t calculate_delay_ms(uint16_t conn_interval, uint16_t latency);

/**************************************************************************//**
 * Bluetooth stack event handler.
 *****************************************************************************/
void sl_bt_in_place_ota_dfu_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  sl_status_t attr_status = SL_STATUS_OK;

  bd_addr addr = { { 0 } };
  uint8_t conn_hdl = SL_BT_INVALID_CONNECTION_HANDLE;
  uint8_t bond_hdl = SL_BT_INVALID_BONDING_HANDLE;

  // Handle stack events
  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates that a remote GATT client is attempting to write
    // a value of a user type attribute in to the local GATT database.
    case sl_bt_evt_gatt_server_user_write_request_id:
      // If user-type OTA Control Characteristic was written, boot the device
      // into Device Firmware Upgrade (DFU) mode. Written value is ignored.
      if (evt->data.evt_gatt_server_user_write_request.characteristic
          == gattdb_ota_control) {
        // Always check security status before the transfer.
        if (sl_bt_in_place_ota_dfu_security_status(addr, conn_hdl, bond_hdl)
            != SL_BT_IN_PLACE_OTA_DFU_SECURITY_ACCEPT) {
          // Security requirements not fulfilled. Reject the request.
          attr_status = SL_STATUS_BT_ATT_WRITE_REQUEST_REJECTED;
        } else {
          // Boot into DFU mode.
          boot_to_dfu = true;
        }

        // Send response to user write request.
        sc = sl_bt_gatt_server_send_user_write_response(
          evt->data.evt_gatt_server_user_write_request.connection,
          gattdb_ota_control,
          (uint8_t)attr_status);
        app_assert_status(sc);

        // Start delay timer before closing connection.
        // Forward connection ID to the timer callback.
        sc = app_timer_start(&connection_close_delay,
                             delay_additional_ms,
                             delay_timer_cb,
                             (void *)((uint32_t) evt->data.evt_gatt_server_user_write_request.connection),
                             false);
        app_assert_status(sc);
      }
      break;

    // -------------------------------
    // This event indicates that a connection was opened.
    case sl_bt_evt_connection_parameters_id:
      delay_additional_ms = calculate_delay_ms(evt->data.evt_connection_parameters.interval,
                                               evt->data.evt_connection_parameters.latency);
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // Check if need to boot to OTA DFU mode.
      if (boot_to_dfu) {
        sl_apploader_util_reset_to_ota_dfu();
      }
      break;

    default:
      break;
  }
}

/**************************************************************************//**
 * Private delay timer callback function.
 *****************************************************************************/
static void delay_timer_cb(app_timer_t *handle, void *data)
{
  sl_status_t sc;
  uint32_t conn_handle = (uint32_t)data;
  if (handle == &connection_close_delay && boot_to_dfu) {
    // Close connection before booting into DFU mode.
    sc = sl_bt_connection_close((uint8_t)conn_handle);
    app_assert_status(sc);
  }
}

/**************************************************************************//**
 * Calculate delay function.
 * Takes the connection interval and the latency, and multiplies it
 * with a configurable multiplier.
 * The calculated value must be greater than the minimum delay value that is
 * also configurable in component config.
 *****************************************************************************/
static uint32_t calculate_delay_ms(uint16_t conn_interval, uint16_t latency)
{
  float raw_delay = 0.0f;
  uint32_t delay = 0;

  raw_delay = (float)conn_interval * CONN_INTERVAL_TIME_RESOLUTION_MS * (float)(1 + latency);
  raw_delay *= SL_BT_IN_PLACE_OTA_DFU_CALC_DELAY_MULTIPLIER;

  delay = (uint32_t)ceilf(raw_delay);

  if (delay < SL_BT_IN_PLACE_OTA_DFU_MIN_DELAY_TO_DISCONNECT) {
    delay = SL_BT_IN_PLACE_OTA_DFU_MIN_DELAY_TO_DISCONNECT;
  }

  return delay;
}

/**************************************************************************//**
 * Weak implementation for checking security requirements before starting
 * the in-place OTA DFU transfer.
 * Since entering OTA DFU mode requires a restart, at least the bonding handle
 * has to be checked here.
 *****************************************************************************/
SL_WEAK sl_bt_in_place_ota_dfu_security_sts_t sl_bt_in_place_ota_dfu_security_status(bd_addr address,
                                                                                     uint8_t connection,
                                                                                     uint8_t bonding)
{
  sl_bt_in_place_ota_dfu_security_sts_t ret_val = SL_BT_IN_PLACE_OTA_DFU_SECURITY_ACCEPT;
  (void) address;
  (void) connection;

  /////////////////////////////////////////////////////////////////////////////
  // Implement as a strong function in user code to realize additional       //
  // security measures before starting the In-place OTA DFU transfer.        //
  /////////////////////////////////////////////////////////////////////////////
#if (SL_BT_IN_PLACE_OTA_DFU_BONDING_REQUIRED)
  if (bonding == SL_BT_INVALID_BONDING_HANDLE) {
    ret_val = SL_BT_IN_PLACE_OTA_DFU_SECURITY_DENY;
  }
#else
  (void) bonding;
#endif
  return ret_val;
}

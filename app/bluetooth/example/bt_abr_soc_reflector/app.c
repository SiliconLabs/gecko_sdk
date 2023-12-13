/***************************************************************************//**
 * @file
 * @brief Accurate Bluetooth Ranging - reflector example
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
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "app_log.h"
#include "app.h"

#include "abr_reflector.h"
#include "sl_rail_util_hadm_antenna_offset_config.h"

// This number comes from the matching network group delay + pcb trace delay +
// antenna delay.
// The offset is interpreted in cm (centimeters)
static int16_t *ant_offset_cm;
static int16_t ant_offset_cm_wireless[SL_RAIL_UTIL_HADM_ANTENNA_COUNT] = SL_RAIL_UTIL_HADM_ANTENNA_OFFSET_WIRELESS_CM;
static int16_t ant_offset_cm_wired[SL_RAIL_UTIL_HADM_ANTENNA_COUNT] = SL_RAIL_UTIL_HADM_ANTENNA_OFFSET_WIRED_CM;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  app_log_filter_threshold_set(APP_LOG_LEVEL_INFO);

  app_log_info(APP_LOG_NL);
  app_log_append_info("Silicon Labs ABR Reflector" APP_LOG_NL);
  app_log_append_info("--------------------------" APP_LOG_NL);
  app_log_append_info("Maximum concurrent connections: %u" APP_LOG_NL, ABR_REFLECTOR_MAX_CONNECTIONS);
  app_log_append_info("Channel Sounding event buffer size: %u" APP_LOG_NL, ABR_REFLECTOR_CS_EVENT_BUF_SIZE);
  app_log_append_info("Minimum transmit power: %d dBm" APP_LOG_NL, ABR_REFLECTOR_MIN_TX_POWER_DBM);
  app_log_append_info("Maximum transmit power: %d dBm" APP_LOG_NL, ABR_REFLECTOR_MAX_TX_POWER_DBM);

  if (!ABR_REFLECTOR_ANTENNA_OFFSET) {
    ant_offset_cm = ant_offset_cm_wireless;
    app_log_info("Wireless antenna offset will be used." APP_LOG_NL);
  } else {
    ant_offset_cm = ant_offset_cm_wired;
    app_log_info("Wired antenna offset will be used." APP_LOG_NL);
  }

  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);

      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];

      sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                   0,
                                                   sizeof(system_id),
                                                   system_id);
      app_assert_status(sc);

      // Set antenna offset on the SoC
      // This can be called any time after booting.
      sc = sl_bt_cs_set_antenna_configuration(SL_RAIL_UTIL_HADM_ANTENNA_COUNT * 2,
                                              (uint8_t *) ant_offset_cm);
      app_assert_status(sc);

      abr_reflector_advertise();
      break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

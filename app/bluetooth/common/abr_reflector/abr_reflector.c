/***************************************************************************//**
 * @file
 * @brief ABR reflector.
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

#include "sl_bt_api.h"
#include "gatt_db.h"
#include "app_assert.h"
#include "abr_reflector.h"

#define EVENT_BUFF_LEN 256
#define EVENT_MAX 4
#define MAX_POWER_DBM 20

typedef struct {
  uint8_t data[EVENT_BUFF_LEN];
  uint8_t len;
  bool empty;
} event_data_t;

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;
static uint8_t connection;
static event_data_t response_buffer[EVENT_MAX];
static uint8_t rx_slot;
static uint8_t tx_slot;
static bool busy;

static void abr_reflector_send_results(void);

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void abr_reflector_on_bt_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  size_t result_len;
  uint8_t event_iter;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      connection = evt->data.evt_connection_opened.connection;
      sc = sl_bt_cs_set_default_settings(connection,
                                         sl_bt_cs_role_status_disable,
                                         sl_bt_cs_role_status_enable,
                                         1,
                                         MAX_POWER_DBM);
      app_assert_status(sc);

      for (event_iter = 0; event_iter < EVENT_MAX; event_iter++) {
        response_buffer[event_iter].empty = true;
      }

      busy = false;

      rx_slot = 0;
      tx_slot = 0;

      break;

    // -------------------------------
    // This event indicates that a new result is available.
    case sl_bt_evt_cs_result_id:
      result_len = sizeof(evt->data.evt_cs_result) + evt->data.evt_cs_result.data.len;

      memcpy(response_buffer[rx_slot].data, (uint8_t *)&evt->data.evt_cs_result, result_len);
      response_buffer[rx_slot].len = result_len;
      response_buffer[rx_slot].empty = false;
      rx_slot++;
      if (rx_slot >= EVENT_MAX) {
        rx_slot = 0;
      }

      abr_reflector_send_results();
      break;
    case sl_bt_evt_gatt_server_characteristic_status_id:
      if (evt->data.evt_gatt_server_characteristic_status.status_flags & sl_bt_gatt_server_confirmation) {
        busy = false;
        abr_reflector_send_results();
      }
      break;

    case sl_bt_evt_gatt_mtu_exchanged_id:
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // -------------------------------
      // Restart advertisement.
      abr_reflector_restart_advertise();
      break;
  }
}

static void abr_reflector_send_results(void)
{
  sl_status_t sc;

  if (busy) {
    return;
  }

  if (response_buffer[tx_slot].empty == false) {
    sc = sl_bt_gatt_server_send_indication(connection,
                                           gattdb_abr_result,
                                           response_buffer[tx_slot].len,
                                           response_buffer[tx_slot].data);
    app_assert_status(sc);
    response_buffer[tx_slot].empty = true;
    tx_slot++;
    if (tx_slot >= EVENT_MAX) {
      tx_slot = 0;
    }
    busy = true;
  }
}

void abr_reflector_advertise(void)
{
  sl_status_t sc;

  // Stop running advertising.
  sl_bt_advertiser_stop(advertising_set_handle);
  // Delete advertiser set
  sl_bt_advertiser_delete_set(advertising_set_handle);

  sc = sl_bt_advertiser_create_set(&advertising_set_handle);
  app_assert_status(sc);

  // Generate data for advertising
  sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                             sl_bt_advertiser_general_discoverable);
  app_assert_status(sc);

  // Set advertising interval to 100ms.
  sc = sl_bt_advertiser_set_timing(
    advertising_set_handle,
    160, // min. adv. interval (milliseconds * 1.6)
    160, // max. adv. interval (milliseconds * 1.6)
    0,   // adv. duration
    0);  // max. num. adv. events
  app_assert_status(sc);

  abr_reflector_restart_advertise();
}

void abr_reflector_restart_advertise(void)
{
  sl_status_t sc;

  // Start advertising and enable connections.
  sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                     sl_bt_advertiser_connectable_scannable);
  app_assert_status(sc);
}

/***************************************************************************//**
 * @file
 * @brief ESL Host Library - Access Point Control source
 *
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

#include <string.h>
#include <stdbool.h>
#include "esl_lib.h"
#include "esl_lib_ap_control.h"
#include "sl_bt_api.h"
#include "esl_lib_event_list.h"
#include "esl_lib_core.h"
#include "esl_lib_storage.h"
#include "esl_lib_log.h"
#include "esl_lib_memory.h"

// -----------------------------------------------------------------------------
// Definitions

#define ESL_LIB_AP_CONTROL_SERVICE_UUID             { 0x0d, 0xf0, 0xad, 0x8b, 0x01, 0x35, 0xb1, 0x00, 0x6b, 0xb1, 0x1d, 0x4b, 0x01, 0x00, 0x10, 0x35 }
#define ESL_LIB_AP_CONTROL_CONTROL_POINT_UUID       { 0x0d, 0xf0, 0xad, 0x8b, 0x01, 0x35, 0xb1, 0x00, 0x6b, 0xb1, 0x1d, 0x4b, 0x02, 0x00, 0x10, 0x35 }
#define ESL_LIB_AP_CONTROL_INAGE_TRANSFER_UUID      { 0xc3, 0x6f, 0x4c, 0xac, 0xa4, 0x52, 0xcc, 0xa6, 0xbb, 0x47, 0xb6, 0x18, 0x53, 0x52, 0x0b, 0xc4 }

#define ESL_LIB_AP_CONTROL_DEVICE_NAME              "ESL AP"
#define ESL_LIB_AP_CONTROL_MANUFACTURER_NAME_STRING "Silicon Labs"

#define ESL_LIB_AP_CONTROL_READ_RESPONSE            "Waiting for command..."

#define ESL_LIB_AP_CONTROL_EVT_OVERHEAD             sizeof(esl_lib_ap_control_evt_type_t)

#define PERIPHERAL_ROLE                             0

#define CHECK(sc)                                                          \
  if (sc != SL_STATUS_OK) {                                                \
    esl_lib_log_ap_control_error("AP control error: %04x" APP_LOG_NL, sc); \
    return sc;                                                             \
  }

#define CHECK_IN_SESSION(sc, ptr)                                          \
  if (sc != SL_STATUS_OK) {                                                \
    esl_lib_log_ap_control_error("AP control error: %04x" APP_LOG_NL, sc); \
    (void)sl_bt_gattdb_abort(session);                                     \
    esl_lib_memory_free(ptr);                                              \
    return sc;                                                             \
  }

typedef struct {
  bool                       enabled;       // ESL AP Control Point enabked
  uint16_t                   cp_handle;     // ESL AP Control Point handle
  uint16_t                   it_handle;     // ESL AP Image transfer handle
  esl_lib_ap_control_state_t state;         // ESL AP State
  uint8_t                    conn_handle;   // ESL AP Control connection handle
  uint8_t                    adv_handle;    // ESL AP Control advertising handle
  bool                       subscribed_cp; // ESL AP Control subscription status
  bool                       subscribed_it; // ESL AP Control subscription status
  esl_lib_storage_handle_t   cp_storage;    // Storage for control point
} ap_control_t;

// -----------------------------------------------------------------------------
// Forward declaration of private functions

static sl_status_t send_event(esl_lib_ap_control_evt_type_t evt_type,
                              uint8_t                       len,
                              uint8_t                       *data);
static sl_status_t send_event_from_storage(esl_lib_ap_control_evt_type_t evt_type,
                                           esl_lib_storage_handle_t      storage);

// -----------------------------------------------------------------------------
// Private variables

static ap_control_t ap_control = {
  .enabled      = false,
  .cp_handle    = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE,
  .it_handle    = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE,
  .state        = ESL_LIB_AP_CONTROL_STATE_DISCONNECTED,
  .conn_handle  = SL_BT_INVALID_CONNECTION_HANDLE,
  .subscribed_cp = false,
  .subscribed_it = false,
  .adv_handle   = SL_BT_INVALID_ADVERTISING_SET_HANDLE,
  .cp_storage   = ESL_LIB_INVALID_HANDLE
};

// -----------------------------------------------------------------------------
// Public functions

sl_status_t esl_lib_ap_control_cleanup(void)
{
  if (ap_control.conn_handle != SL_BT_INVALID_CONNECTION_HANDLE) {
    (void)sl_bt_connection_close(ap_control.conn_handle);
  }
  (void)esl_lib_storage_delete(&ap_control.cp_storage);
  (void)esl_lib_ap_control_adv_enable(false);
  esl_lib_log_ap_control_debug("AP Control cleanup complete" APP_LOG_NL);
  return SL_STATUS_OK;
}

sl_status_t esl_lib_ap_control_init(void)
{
  sl_status_t sc = SL_STATUS_OK;

  bd_addr  address;
  uint8_t  address_type;
  uint8_t  system_id[8];
  uint16_t session;
  uint16_t service_custom;
  uint16_t service_ga;
  uint16_t service_di;
  uint16_t characteristic;

  esl_lib_log_ap_control_debug("Initializing AP Control" APP_LOG_NL);

  ap_control.conn_handle = SL_BT_INVALID_CONNECTION_HANDLE;
  ap_control.cp_handle   = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE;
  ap_control.it_handle   = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE;
  ap_control.state       = ESL_LIB_AP_CONTROL_STATE_DISCONNECTED;

  sc = esl_lib_storage_create(&ap_control.cp_storage);
  CHECK(sc);

  esl_lib_log_ap_control_debug("AP control storage created" APP_LOG_NL);

  sc = sl_bt_gattdb_new_session(&session);

  if (sc != SL_STATUS_OK) {
    esl_lib_log_ap_control_error("AP control GATT session create failed: %04x" APP_LOG_NL, sc);
    esl_lib_memory_free(ap_control.cp_storage);
    return sc;
  }

  esl_lib_log_ap_control_debug("AP control GATT session created" APP_LOG_NL);

  // ESL AP control service
  uint8_t service_uuid[] = ESL_LIB_AP_CONTROL_SERVICE_UUID;
  sc = sl_bt_gattdb_add_service(session,
                                sl_bt_gattdb_primary_service,
                                SL_BT_GATTDB_ADVERTISED_SERVICE,
                                16,
                                service_uuid,
                                &service_custom);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  // ESL AP control point
  uuid_128 ap_control_cp_uuid = {
    .data = ESL_LIB_AP_CONTROL_CONTROL_POINT_UUID
  };
  sc = sl_bt_gattdb_add_uuid128_characteristic(session,
                                               service_custom,
                                               SL_BT_GATTDB_CHARACTERISTIC_READ
                                               | SL_BT_GATTDB_CHARACTERISTIC_WRITE
                                               | SL_BT_GATTDB_CHARACTERISTIC_NOTIFY,
                                               0,
                                               0,
                                               ap_control_cp_uuid,
                                               sl_bt_gattdb_user_managed_value,
                                               0,
                                               0,
                                               NULL,
                                               &ap_control.cp_handle);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  // ESL AP Control Image Transfer
  uuid_128 ap_control_it_uuid = {
    .data = ESL_LIB_AP_CONTROL_INAGE_TRANSFER_UUID
  };
  sc = sl_bt_gattdb_add_uuid128_characteristic(session,
                                               service_custom,
                                               SL_BT_GATTDB_CHARACTERISTIC_READ
                                               | SL_BT_GATTDB_CHARACTERISTIC_WRITE
                                               | SL_BT_GATTDB_CHARACTERISTIC_NOTIFY,
                                               0,
                                               0,
                                               ap_control_it_uuid,
                                               sl_bt_gattdb_user_managed_value,
                                               0,
                                               0,
                                               NULL,
                                               &ap_control.it_handle);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  sc = sl_bt_gattdb_start_service(session, service_custom);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);
  esl_lib_log_ap_control_debug("AP control custom service created" APP_LOG_NL);

  // Generic Access
  uint8_t ga_uuid[] = { 0x00, 0x18 };
  sc = sl_bt_gattdb_add_service(session,
                                sl_bt_gattdb_primary_service,
                                0,
                                2,
                                ga_uuid,
                                &service_ga);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  // Device Name
  sl_bt_uuid_16_t device_name_uuid = {
    .data = { 0x00, 0x2A }
  };
  sc = sl_bt_gattdb_add_uuid16_characteristic(session,
                                              service_ga,
                                              SL_BT_GATTDB_CHARACTERISTIC_READ,
                                              0,
                                              0,
                                              device_name_uuid,
                                              sl_bt_gattdb_fixed_length_value,
                                              strlen(ESL_LIB_AP_CONTROL_DEVICE_NAME),
                                              strlen(ESL_LIB_AP_CONTROL_DEVICE_NAME),
                                              (uint8_t *)ESL_LIB_AP_CONTROL_DEVICE_NAME,
                                              &characteristic);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  // Appearance
  sl_bt_uuid_16_t apperance_uuid = {
    .data = { 0x01, 0x2A }
  };
  sc = sl_bt_gattdb_add_uuid16_characteristic(session,
                                              service_ga,
                                              SL_BT_GATTDB_CHARACTERISTIC_READ,
                                              0,
                                              0,
                                              apperance_uuid,
                                              sl_bt_gattdb_fixed_length_value,
                                              2,
                                              2,
                                              (uint8_t *)"\x01\x05",
                                              &characteristic);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  sc = sl_bt_gattdb_start_service(session, service_ga);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);
  esl_lib_log_ap_control_debug("AP control Generic Access Service created" APP_LOG_NL);

  // Device Information
  uint8_t di_uuid[] = { 0x0A, 0x18 };
  sc = sl_bt_gattdb_add_service(session,
                                sl_bt_gattdb_primary_service,
                                0,
                                2,
                                di_uuid,
                                &service_di);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  // Manufacturer Name String
  sl_bt_uuid_16_t mns_uuid = {
    .data = { 0x29, 0x2A }
  };
  sc = sl_bt_gattdb_add_uuid16_characteristic(session,
                                              service_di,
                                              SL_BT_GATTDB_CHARACTERISTIC_READ,
                                              0,
                                              0,
                                              mns_uuid,
                                              sl_bt_gattdb_fixed_length_value,
                                              strlen(ESL_LIB_AP_CONTROL_MANUFACTURER_NAME_STRING),
                                              strlen(ESL_LIB_AP_CONTROL_MANUFACTURER_NAME_STRING),
                                              (uint8_t *)ESL_LIB_AP_CONTROL_MANUFACTURER_NAME_STRING,
                                              &characteristic);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  // System ID
  // Extract unique ID from BT Address.
  sc = sl_bt_system_get_identity_address(&address, &address_type);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  // Pad and reverse unique ID to get System ID.
  system_id[0] = address.addr[5];
  system_id[1] = address.addr[4];
  system_id[2] = address.addr[3];
  system_id[3] = 0xFF;
  system_id[4] = 0xFE;
  system_id[5] = address.addr[2];
  system_id[6] = address.addr[1];
  system_id[7] = address.addr[0];

  sl_bt_uuid_16_t system_id_uuid = {
    .data = { 0x23, 0x2A }
  };
  sc = sl_bt_gattdb_add_uuid16_characteristic(session,
                                              service_di,
                                              SL_BT_GATTDB_CHARACTERISTIC_READ,
                                              0,
                                              0,
                                              system_id_uuid,
                                              sl_bt_gattdb_fixed_length_value,
                                              8,
                                              8,
                                              system_id,
                                              &characteristic);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  sc = sl_bt_gattdb_start_service(session, service_di);
  CHECK_IN_SESSION(sc, ap_control.cp_storage);

  esl_lib_log_ap_control_debug("AP control Device Information Service created" APP_LOG_NL);

  sc = sl_bt_gattdb_commit(session);

  if (sc == SL_STATUS_OK) {
    ap_control.enabled = true;
    esl_lib_log_ap_control_debug("AP control initialized " APP_LOG_NL);
  } else {
    esl_lib_log_ap_control_error("AP control GATTDB commit failed = 0x%04x" APP_LOG_NL, sc);
  }

  return sc;
}

sl_status_t esl_lib_ap_control_adv_enable(bool enable)
{
  sl_status_t sc = SL_STATUS_OK;

  if (!ap_control.enabled && enable) {
    sc = esl_lib_ap_control_init();
  }

  CHECK(sc);

  if (enable) {
    esl_lib_log_ap_control_debug("Enabling advertising = %d" APP_LOG_NL, enable);

    sc = sl_bt_advertiser_create_set(&ap_control.adv_handle);
    CHECK(sc);

    sc = sl_bt_legacy_advertiser_generate_data(ap_control.adv_handle,
                                               sl_bt_advertiser_general_discoverable);
    CHECK(sc);

    sc = sl_bt_advertiser_set_timing(ap_control.adv_handle,
                                     160,
                                     160,
                                     0,
                                     0);
    CHECK(sc);

    sc = sl_bt_legacy_advertiser_start(ap_control.adv_handle,
                                       sl_bt_legacy_advertiser_connectable);
    CHECK(sc);
  } else {
    esl_lib_log_ap_control_debug("Disabling advertising = %d" APP_LOG_NL, enable);
    if (ap_control.adv_handle != SL_BT_INVALID_ADVERTISING_SET_HANDLE) {
      sc = sl_bt_advertiser_stop(ap_control.adv_handle);
      CHECK(sc);
      sc = sl_bt_advertiser_delete_set(ap_control.adv_handle);
      CHECK(sc);
      ap_control.adv_handle = SL_BT_INVALID_ADVERTISING_SET_HANDLE;
    }
  }
  esl_lib_log_ap_control_debug("Advertising = %d" APP_LOG_NL, enable);

  return sc;
}

sl_status_t esl_lib_ap_control_response(esl_lib_long_array_t *data)
{
  sl_status_t sc;

  if (!ap_control.enabled) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (ap_control.conn_handle == SL_BT_INVALID_CONNECTION_HANDLE) {
    return SL_STATUS_NOT_AVAILABLE;
  }
  if (ap_control.cp_handle == ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
    return SL_STATUS_NOT_INITIALIZED;
  }

  sc = sl_bt_gatt_server_send_notification(ap_control.conn_handle,
                                           ap_control.cp_handle,
                                           data->len,
                                           data->data);
  if (sc == SL_STATUS_OK) {
    esl_lib_log_ap_control_debug("Notification sent" APP_LOG_NL);
  }
  return sc;
}

sl_status_t esl_lib_ap_control_image_transfer_response(esl_lib_long_array_t *data)
{
  sl_status_t sc;

  if (!ap_control.enabled) {
    return SL_STATUS_NOT_INITIALIZED;
  }

  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (ap_control.it_handle == SL_BT_INVALID_CONNECTION_HANDLE) {
    return SL_STATUS_NOT_AVAILABLE;
  }
  if (ap_control.cp_handle == ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  sc = sl_bt_gatt_server_send_notification(ap_control.conn_handle,
                                           ap_control.it_handle,
                                           data->len,
                                           data->data);
  if (sc == SL_STATUS_OK) {
    esl_lib_log_ap_control_debug("IT notification sent" APP_LOG_NL);
  }
  return sc;
}

void esl_lib_ap_control_on_bt_event(sl_bt_msg_t *evt)
{
  esl_lib_ap_control_evt_type_t evt_code  = ESL_LIB_AP_CONTROL_EVT_REQUEST;
  uint16_t size_sent = 0;
  bool subscribe = false;

  if (!ap_control.enabled) {
    return;
  }

  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_gatt_server_user_read_request_id:
      if (evt->data.evt_gatt_server_user_read_request.characteristic == ap_control.cp_handle) {
        esl_lib_log_ap_control_debug("CP read" APP_LOG_NL);
        // Send back the read response
        (void)sl_bt_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,
                                                        evt->data.evt_gatt_server_user_read_request.characteristic,
                                                        0,
                                                        strlen(ESL_LIB_AP_CONTROL_READ_RESPONSE),
                                                        (uint8_t *)ESL_LIB_AP_CONTROL_READ_RESPONSE,
                                                        &size_sent);
      }
      break;
    case sl_bt_evt_gatt_server_user_write_request_id:
      if (evt->data.evt_gatt_server_user_write_request.characteristic == ap_control.cp_handle
          || evt->data.evt_gatt_server_user_write_request.characteristic == ap_control.it_handle) {
        if (evt->data.evt_gatt_server_user_write_request.characteristic == ap_control.it_handle) {
          // Set code for AP image transfer only, already set for control point
          evt_code = ESL_LIB_AP_CONTROL_EVT_IMAGE_TRANSFER;
          esl_lib_log_ap_control_debug("IT write opcode = %d" APP_LOG_NL,
                                       evt->data.evt_gatt_server_user_write_request.att_opcode);
        } else {
          esl_lib_log_ap_control_debug("CP write opcode = %d" APP_LOG_NL,
                                       evt->data.evt_gatt_server_user_write_request.att_opcode);
        }
        // Check ATT opcode
        if (evt->data.evt_gatt_server_user_write_request.att_opcode
            == sl_bt_gatt_prepare_write_request) {
          // Write prepare requested, just append to internal storage
          (void)esl_lib_storage_append(ap_control.cp_storage,
                                       &evt->data.evt_gatt_server_user_write_request.value);
          // Send out response for prepare request
          (void)sl_bt_gatt_server_send_user_prepare_write_response(evt->data.evt_gatt_server_user_write_request.connection,
                                                                   evt->data.evt_gatt_server_user_write_request.characteristic,
                                                                   0,
                                                                   evt->data.evt_gatt_server_user_write_request.offset,
                                                                   evt->data.evt_gatt_server_user_write_request.value.len,
                                                                   evt->data.evt_gatt_server_user_write_request.value.data);
        } else if (evt->data.evt_gatt_server_user_write_request.att_opcode
                   == sl_bt_gatt_execute_write_request) {
          // Execute write requested, append residue to internal storage first
          (void)esl_lib_storage_append(ap_control.cp_storage,
                                       &evt->data.evt_gatt_server_user_write_request.value);
          // Emit event using the data in the storage with the event code
          (void)send_event_from_storage(evt_code, ap_control.cp_storage);
          // Clear the control point storage
          (void)esl_lib_storage_clean(ap_control.cp_storage);
          // Send out response
          (void)sl_bt_gatt_server_send_user_write_response(evt->data.evt_gatt_server_user_write_request.connection,
                                                           evt->data.evt_gatt_server_user_write_request.characteristic,
                                                           0);
        } else if (evt->data.evt_gatt_server_user_write_request.att_opcode
                   == sl_bt_gatt_write_request) {
          // Write requested
          // Emit event with the data in the event and the event code
          (void)send_event(evt_code,
                           evt->data.evt_gatt_server_user_write_request.value.len,
                           evt->data.evt_gatt_server_user_write_request.value.data);
          // Send response to write event
          (void)sl_bt_gatt_server_send_user_write_response(evt->data.evt_gatt_server_user_write_request.connection,
                                                           evt->data.evt_gatt_server_user_write_request.characteristic,
                                                           0);
        }
      }
      break;

    case sl_bt_evt_connection_opened_id:
      if (evt->data.evt_connection_opened.master == PERIPHERAL_ROLE) {
        esl_lib_log_ap_control_debug("Connection opened as peripheral: %d" APP_LOG_NL,
                                     evt->data.evt_connection_opened.connection);
        if (ap_control.conn_handle != SL_BT_INVALID_CONNECTION_HANDLE) {
          // Close second connection
          esl_lib_log_ap_control_warning("Closing second connection" APP_LOG_NL);
          (void)sl_bt_connection_close(evt->data.evt_connection_opened.connection);
        } else {
          // Save connection
          ap_control.conn_handle = evt->data.evt_connection_opened.connection;
          ap_control.state = ESL_LIB_AP_CONTROL_STATE_CONNECTED;
          (void)send_event(ESL_LIB_AP_CONTROL_EVT_STATUS,
                           sizeof(ap_control.state),
                           (uint8_t *)&ap_control.state);
          esl_lib_log_ap_control_debug("Connection saved as AP controller: %d" APP_LOG_NL,
                                       evt->data.evt_connection_opened.connection);
        }
      }
      break;
    case sl_bt_evt_gatt_server_characteristic_status_id:
      if (evt->data.evt_gatt_server_characteristic_status.connection == ap_control.conn_handle
          && (evt->data.evt_gatt_server_characteristic_status.status_flags & sl_bt_gatt_server_client_config)) {
        subscribe = (evt->data.evt_gatt_server_characteristic_status.client_config_flags & sl_bt_gatt_notification) > 0;
        if (evt->data.evt_gatt_server_characteristic_status.characteristic == ap_control.cp_handle) {
          ap_control.subscribed_cp = subscribe;
          esl_lib_log_ap_control_debug("CP Subscribe = %d" APP_LOG_NL, subscribe);
        } else if (evt->data.evt_gatt_server_characteristic_status.characteristic == ap_control.it_handle) {
          ap_control.subscribed_it = subscribe;
          esl_lib_log_ap_control_debug("IT Subscribe = %d" APP_LOG_NL, subscribe);
        }
        if (ap_control.subscribed_it && ap_control.subscribed_cp) {
          if (ap_control.state != ESL_LIB_AP_CONTROL_STATE_SUBSCRIBED) {
            ap_control.state = ESL_LIB_AP_CONTROL_STATE_SUBSCRIBED;
            (void)send_event(ESL_LIB_AP_CONTROL_EVT_STATUS,
                             sizeof(ap_control.state),
                             (uint8_t *)&ap_control.state);
          }
        } else {
          if (ap_control.state != ESL_LIB_AP_CONTROL_STATE_CONNECTED) {
            ap_control.state = ESL_LIB_AP_CONTROL_STATE_CONNECTED;
            (void)send_event(ESL_LIB_AP_CONTROL_EVT_STATUS,
                             sizeof(ap_control.state),
                             (uint8_t *)&ap_control.state);
          }
        }
      }
      break;

    case sl_bt_evt_connection_closed_id:
      if (evt->data.evt_connection_closed.connection == ap_control.conn_handle) {
        esl_lib_log_ap_control_debug("Connection closed: %d" APP_LOG_NL,
                                     ap_control.conn_handle);
        ap_control.conn_handle = SL_BT_INVALID_CONNECTION_HANDLE;
        ap_control.state = ESL_LIB_AP_CONTROL_STATE_DISCONNECTED;
        (void)send_event(ESL_LIB_AP_CONTROL_EVT_STATUS,
                         sizeof(ap_control.state),
                         (uint8_t *)&ap_control.state);
      }
      break;

    default:
      break;
  }
}

// -----------------------------------------------------------------------------
// Private functions

static sl_status_t send_event(esl_lib_ap_control_evt_type_t evt_type,
                              uint8_t                       len,
                              uint8_t                       *data)
{
  sl_status_t   sc;
  esl_lib_evt_t *lib_event  = NULL;
  // Add overhead to the length
  uint32_t      size        = sizeof(esl_lib_ap_control_evt_data_t) + len;

  sc = esl_lib_event_list_allocate(ESL_LIB_EVT_GENERAL,
                                   size,
                                   &lib_event);
  if (sc == SL_STATUS_OK) {
    esl_lib_log_ap_control_debug("Sending event = 0x%02x" APP_LOG_NL,
                                 evt_type);
    lib_event->evt_code = ESL_LIB_EVT_GENERAL;

    lib_event->data.evt_general.len = size;
    // Get header and payload for the AP control event
    esl_lib_ap_control_evt_data_t *ap_control_evt_data
      = (esl_lib_ap_control_evt_data_t *)(lib_event->data.evt_general.data);
    // Set event subtype
    ap_control_evt_data->evt_type = (uint8_t)evt_type;
    memcpy(ap_control_evt_data->payload,
           data,
           len);
    sc = esl_lib_event_list_push_back(lib_event);
    if (sc == SL_STATUS_OK) {
      esl_lib_log_ap_control_debug("Event sent = 0x%02x" APP_LOG_NL, evt_type);
    } else {
      esl_lib_memory_free(lib_event);
    }
  }
  if (sc != SL_STATUS_OK) {
    esl_lib_log_ap_control_error("Event send failed = 0x%04x" APP_LOG_NL, sc);
  }

  return sc;
}

static sl_status_t send_event_from_storage(esl_lib_ap_control_evt_type_t evt_type,
                                           esl_lib_storage_handle_t      storage)
{
  sl_status_t   sc;
  size_t        size;
  esl_lib_evt_t *lib_event = NULL;

  sc = esl_lib_storage_get_size(storage, &size);

  if (sc == SL_STATUS_OK) {
    // Increment size with the overhead
    size += ESL_LIB_AP_CONTROL_EVT_OVERHEAD;
    sc = esl_lib_event_list_allocate(ESL_LIB_EVT_GENERAL,
                                     (uint32_t)size,
                                     &lib_event);

    if (sc == SL_STATUS_OK) {
      esl_lib_log_ap_control_debug("Sending event from storage = 0x%02x" APP_LOG_NL, evt_type);
      lib_event->evt_code = ESL_LIB_EVT_GENERAL;
      lib_event->data.evt_general.len = (uint32_t)size;
      // Get header and payload for the AP control event
      esl_lib_ap_control_evt_data_t *data
        = (esl_lib_ap_control_evt_data_t *)lib_event->data.evt_general.data;
      // Set event subtype
      data->evt_type = (uint8_t)evt_type;
      // Copy data from storage to the payload
      sc = esl_lib_storage_copy(storage, data->payload);
      if (sc == SL_STATUS_OK) {
        sc = esl_lib_event_list_push_back(lib_event);
        if (sc == SL_STATUS_OK) {
          esl_lib_log_ap_control_debug("Event sent from storage = 0x%02x" APP_LOG_NL, evt_type);
        }
      }
    }
  }
  if (sc != SL_STATUS_OK) {
    esl_lib_log_ap_control_error("Event send from storage failed = 0x%04x" APP_LOG_NL, sc);
  }

  return sc;
}

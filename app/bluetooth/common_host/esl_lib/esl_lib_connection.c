/***************************************************************************//**
 * @file
 * @brief ESL Access Point Connection source file.
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
#include <stdint.h>
#include <stdbool.h>
#include "sl_status.h"
#include "sl_slist.h"
#include "esl_lib.h"
#include "esl_lib_core.h"
#include "esl_lib_connection.h"
#include "esl_lib_event_list.h"
#include "esl_lib_command_list.h"
#include "esl_lib_image_transfer.h"
#include "esl_lib_pawr.h"
#include "esl_lib_storage.h"
#include "esl_lib_memory.h"

// -----------------------------------------------------------------------------
// Definitions

#define CENTRAL_ROLE          1
#define GATT_OVERHEAD         7
#define PREFERRED_PHY         sl_bt_gap_phy_2m
#define ACCEPTED_PHY          sl_bt_gap_phy_any
#define CLOSE_TIMEOUT_MS      2000
#define CONNECTION_TIMEOUT_MS 10000
#define BONDING_TIMEOUT_MS    15000
#define RECONNECT_TIMEOUT_MS  250
#define GATT_TIMEOUT_MS       10000

// connection parameters for PAST
#define PAST_CONN_INTERVAL_MIN       0x0006 // given in 1.25ms units, 6 * 1.25 = 7.5ms, limited by Core specification
#define PAST_CONN_INTERVAL_MAX       0x0c80 // limited by Core specification to 4 seconds
#define PAST_CONN_PERIPHERAL_LATENCY 1      // allow to skip one connection interval during PAST if there's no data
#define PAST_CONN_DEFAULT_TIMEOUT    1000   // value * 10ms, this is 10 seconds
#define PAST_CONN_MIN_TIMEOUT        0x000a // min 100ms according to COre specification
#define PAST_CONN_MAX_TIMEOUT        0x0c80 // max 32 seconds according to COre specification
#define PAST_CONN_MIN_CE_LENGTH      0
#define PAST_CONN_MAX_CE_LENGTH      0xffff
#define PAST_GRACE_INTERVAL_COUNT    6

#define PAWR_SERVICE_DATA            42

#define CONN_FMT                     ESL_LIB_LOG_HANDLE_FORMAT

/// GATT Database handles
typedef struct {
  struct {
    sl_bt_uuid_16_t esl;
    sl_bt_uuid_16_t ots;
    sl_bt_uuid_16_t dis;
  } services;
  sl_bt_uuid_16_t esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_SIZE];
  sl_bt_uuid_16_t dis_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_DIS_SIZE];
} esl_lib_connection_uuids_t;

// -----------------------------------------------------------------------------
// Forward declaration of private functions

static void esl_lib_connection_safe_remove_ptr(esl_lib_connection_t *ptr);
static void run_command(esl_lib_command_list_cmd_t *cmd);
static sl_status_t close_connection(esl_lib_connection_t *conn);
static sl_status_t send_connection_status(esl_lib_connection_t *conn,
                                          esl_lib_bool_t       status,
                                          sl_status_t          reason);
static sl_status_t send_cp_notification_event(esl_lib_connection_t *conn,
                                              uint8_t              len,
                                              uint8_t              *data);
static sl_status_t send_bonding_data(esl_lib_connection_t *conn,
                                     uint8_t              *data);
static sl_status_t send_bonding_finished(esl_lib_connection_t *conn);
static sl_status_t send_att_response(esl_lib_connection_t *conn,
                                     esl_lib_evt_type_t   type,
                                     sl_status_t          status);
static sl_status_t send_connection_error(esl_lib_connection_t        *conn,
                                         esl_lib_status_t            lib_status,
                                         sl_status_t                 status,
                                         esl_lib_connection_state_t  data);

static void gatt_timeout(app_timer_t *timer,
                         void        *data);
static void connection_timeout(app_timer_t *timer,
                               void *data);
static void reconnect_timeout(app_timer_t *timer,
                              void        *data);
static bool uuid_16_match(uint8_t *uuid_a, uint8_t *uuid_b);
static void connection_complete(esl_lib_connection_t *conn);
static bool check_connected(esl_lib_connection_t *conn);
static bool check_image_transfer(esl_lib_connection_t *conn);
static void on_image_transfer_type_arrived(esl_lib_image_transfer_handle_t handle,
                                           uint8_t                         connection,
                                           sl_status_t                     result,
                                           uint8_t                         image_index,
                                           uint8_t                         *object_type,
                                           uint8_t                         len);
static void on_image_transfer_finished(esl_lib_image_transfer_handle_t handle,
                                       uint8_t                         connection,
                                       sl_status_t                     result,
                                       uint8_t                         image_index);
static void on_image_transfer_status(esl_lib_image_transfer_handle_t handle,
                                     uint8_t                         connection,
                                     esl_image_transfer_state_t      state,
                                     sl_status_t                     result,
                                     esl_lib_ots_gattdb_handles_t    *gattdb_handles);
static sl_status_t get_next_tag_info(esl_lib_connection_t *conn);
static sl_status_t get_tag_info_finish(esl_lib_connection_t *conn, sl_status_t status);
static esl_lib_data_type_t get_next_type(esl_lib_data_type_t type);
static uint16_t get_handle_for_type(esl_lib_connection_t *conn,
                                    esl_lib_data_type_t  tag_info_type);
static void clean_tag_info(esl_lib_connection_t *conn);
static sl_status_t save_tag_info(esl_lib_connection_t *conn);
static sl_status_t write_value(esl_lib_connection_t *conn,
                               esl_lib_bool_t       response,
                               esl_lib_data_type_t  type,
                               uint32_t             len,
                               uint8_t              *data);
static sl_status_t write_next_config_value(esl_lib_connection_t *conn);
static bool find_tlv(esl_lib_command_list_cmd_t  *cmd,
                     esl_lib_connect_data_type_t type,
                     esl_lib_connect_tlv_t       **tlv_out);
static void close_broken_connection(esl_lib_connection_t **conn);
// -----------------------------------------------------------------------------
// Private variables

// List of connections
static sl_slist_node_t *connection_list = NULL;

// Service UUIDs
static const esl_lib_connection_uuids_t uuid_map = {
  .services.esl.data = ESL_SERVICE_UUID,   // ESL Service UUID
  .services.ots.data = { 0x25, 0x18 },     // OTS Service UUID
  .services.dis.data = { 0x0A, 0x18 },     // Device Information Service UUID
  .esl_characteristics = {
    { .data = { 0xF6, 0x2B } },            // ESL_LIB_CHARACTERISTIC_INDEX_ESL_ADDRESS
    { .data = { 0xF7, 0x2B } },            // ESL_LIB_CHARACTERISTIC_INDEX_AP_SYNC_KEY_MATERIAL
    { .data = { 0xF8, 0x2B } },            // ESL_LIB_CHARACTERISTIC_INDEX_ESL_RESPONSE_KEY_MATERIAL
    { .data = { 0xF9, 0x2B } },            // ESL_LIB_CHARACTERISTIC_INDEX_ESL_CURRENT_ABSOLUTE_TIME
    { .data = { 0xFA, 0x2B } },            // ESL_LIB_CHARACTERISTIC_INDEX_ESL_DISPLAY_INFORMATION
    { .data = { 0xFB, 0x2B } },            // ESL_LIB_CHARACTERISTIC_INDEX_ESL_IMAGE_INFORMATION
    { .data = { 0xFC, 0x2B } },            // ESL_LIB_CHARACTERISTIC_INDEX_ESL_SENSOR_INFORMATION
    { .data = { 0xFD, 0x2B } },            // ESL_LIB_CHARACTERISTIC_INDEX_ESL_LED_INFORMATION
    { .data = { 0xFE, 0x2B } }             // ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT
  },
  .dis_characteristics = {
    { .data = { 0x50, 0x2A } },            // ESL_LIB_CHARACTERISTIC_INDEX_DIS_PNP_ID
    { .data = { 0x25, 0x2A } }             // ESL_LIB_CHARACTERISTIC_INDEX_DIS_SN
  }
};

// -----------------------------------------------------------------------------
// Public functions

sl_status_t esl_lib_connection_check_gattdb_handles(esl_lib_gattdb_handles_t *gattdb_handles)
{
  if (gattdb_handles != NULL) {
    if (gattdb_handles->services.esl == ESL_LIB_INVALID_SERVICE_HANDLE) {
      return SL_STATUS_INVALID_HANDLE;
    } else {
      // ESL service present, check mandatory fields
      if (gattdb_handles->esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_ADDRESS]
          == ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
        return SL_STATUS_INVALID_HANDLE;
      }
      if (gattdb_handles->esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_AP_SYNC_KEY_MATERIAL]
          == ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
        return SL_STATUS_INVALID_HANDLE;
      }
      if (gattdb_handles->esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_RESPONSE_KEY_MATERIAL]
          == ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
        return SL_STATUS_INVALID_HANDLE;
      }
      if (gattdb_handles->esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CURRENT_ABSOLUTE_TIME]
          == ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
        return SL_STATUS_INVALID_HANDLE;
      }
      if (gattdb_handles->esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT]
          == ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
        return SL_STATUS_INVALID_HANDLE;
      }
    }
  } else {
    return SL_STATUS_NULL_POINTER;
  }
  return SL_STATUS_OK;
}

sl_status_t esl_lib_connection_open(esl_lib_command_list_cmd_t *cmd)
{
  sl_status_t             sc                = SL_STATUS_OK;
  esl_lib_address_t       *identity         = NULL;
  bd_addr                 *identity_addr    = NULL;
  esl_lib_connection_t    *conn             = cmd->data.cmd_connect.conn_hnd;
  uint8_t                 connection_handle = SL_BT_INVALID_CONNECTION_HANDLE;
  bd_addr                 *addr             = NULL;
  uint8_t                 address_type      = 0;
  esl_lib_connect_tlv_t   *tlv              = NULL;
  esl_lib_pawr_t          *pawr             = NULL;
  uint8_t                 flags             = 0;
  uint8_t                 io_capabilities   = sl_bt_sm_io_capability_noinputnooutput;
  esl_lib_address_t       *address;

  if (cmd == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (cmd->cmd_code != ESL_LIB_CMD_CONNECT) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (conn != ESL_LIB_INVALID_HANDLE) {
    // it's a retry attempt
    uint8_t retry_count = 1 + ESL_LIB_CONNECTION_RETRY_COUNT_MAX - cmd->data.cmd_connect.retries_left;

    esl_lib_log_connection_warning("Retry %d / %d connect to " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                   retry_count,
                                   ESL_LIB_CONNECTION_RETRY_COUNT_MAX,
                                   ESL_LIB_LOG_ADDR(cmd->data.cmd_connect.address));
    conn->command = cmd; // re-assign command because retry timer cleared it
    conn->command_complete = false;
  } else {
    esl_lib_log_connection_debug("Initiate new connection" APP_LOG_NL);
  }

  if (cmd->data.cmd_connect.retries_left) {
    // Set address
    address = &cmd->data.cmd_connect.address;
    addr = (bd_addr *)address->addr;
    address_type = address->address_type;

    // Check for identity
    if (find_tlv(cmd, ESL_LIB_CONNECT_DATA_TYPE_IDENTITY_ADDRESS, &tlv)) {
      identity = (esl_lib_address_t*)tlv->data.data;
      esl_lib_log_connection_debug("Setting identity to " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                   ESL_LIB_LOG_ADDR(*identity));
      identity_addr = (bd_addr *)identity;
      sc = sl_bt_gap_set_identity_address(*identity_addr, identity->address_type);
      if (sc != SL_STATUS_OK) {
        esl_lib_log_connection_error("Failed to set identity address, sc = 0x%04x" APP_LOG_NL, sc);
        return sc;
      }
    }

    // Check key specified
    if (find_tlv(cmd, ESL_LIB_CONNECT_DATA_TYPE_PASSKEY, &tlv)) {
      esl_lib_log_connection_debug("Use passkey for pairing with " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                   ESL_LIB_LOG_ADDR(*address));
      io_capabilities = sl_bt_sm_io_capability_keyboardonly;
      flags |= SL_BT_SM_CONFIGURATION_MITM_REQUIRED;
    }
    if (find_tlv(cmd, ESL_LIB_CONNECT_DATA_TYPE_OOB_DATA, &tlv)) {
      // No action, use remote OOB data only
      esl_lib_log_connection_debug("Use OOB data for pairing with " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                   ESL_LIB_LOG_ADDR(*address));
    }
    if (find_tlv(cmd, ESL_LIB_CONNECT_DATA_TYPE_LTK, &tlv)) {
      // No new bonding required
      esl_lib_log_connection_debug("Use LTK for connection with " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                   ESL_LIB_LOG_ADDR(*address));
    } else {
      esl_lib_log_connection_debug("Create new bond with " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                   ESL_LIB_LOG_ADDR(*address));
    }

    sc = sl_bt_sm_configure(flags, io_capabilities);

    if (sc != SL_STATUS_OK) {
      esl_lib_log_connection_error("Failed to configure SM, sc = 0x%04x" APP_LOG_NL, sc);
      return sc;
    }

    // Check PAwR presense to decide connection method
    if (find_tlv(cmd, ESL_LIB_CONNECT_DATA_TYPE_PAWR, &tlv)) {
      // Connect using PAwR
      esl_lib_pawr_subevent_t *pawr_sub = (esl_lib_pawr_subevent_t *)tlv->data.data;
      pawr = (esl_lib_pawr_t *)pawr_sub->handle;
      esl_lib_log_connection_debug("Opening connection via PAwR handle %d subevent %d to " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                   pawr->pawr_handle,
                                   pawr_sub->subevent,
                                   ESL_LIB_LOG_ADDR(*address));
      sc = sl_bt_pawr_advertiser_create_connection(pawr->pawr_handle,
                                                   pawr_sub->subevent,
                                                   *addr,
                                                   address_type,
                                                   &connection_handle);
    } else {
      // Connect using the address only
      esl_lib_log_connection_debug("Opening connection to " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                   ESL_LIB_LOG_ADDR(*address));
      sc = sl_bt_connection_open(*addr,
                                 address_type,
                                 sl_bt_gap_phy_1m,
                                 &connection_handle);
    }
    if (sc == SL_STATUS_OK) {
      // If not retry, add a new connection
      if (conn == ESL_LIB_INVALID_HANDLE) {
        // Allocate and add the connection to the connection list.
        sc = esl_lib_connection_add(connection_handle, &conn);
        if (sc == SL_STATUS_OK) {
          // Move to connecting state with no error present.
          conn->state = ESL_LIB_CONNECTION_STATE_CONNECTING;
          // Save address and type
          memcpy(conn->address.addr,
                 addr->addr,
                 sizeof(conn->address.addr));
          conn->address_type = address_type;
          conn->gattdb_known = ESL_LIB_FALSE;
          // Check for gattdb
          if (find_tlv(cmd, ESL_LIB_CONNECT_DATA_TYPE_GATTDB_HANDLES, &tlv)) {
            conn->gattdb_known = ESL_LIB_TRUE;
            // Copy GATT database
            memcpy(&conn->gattdb_handles,
                   tlv->data.data,
                   sizeof(conn->gattdb_handles));
            for (uint8_t i = 0; i < sizeof(conn->gattdb_handles.esl_characteristics) / sizeof(uint16_t); i++) {
              esl_lib_log_connection_debug(CONN_FMT "ESL %u characteristic handle = 0x%02x" APP_LOG_NL,
                                           conn,
                                           i,
                                           conn->gattdb_handles.esl_characteristics[i]);
            }
            for (uint8_t i = 0; i < sizeof(conn->gattdb_handles.dis_characteristics) / sizeof(uint16_t); i++) {
              esl_lib_log_connection_debug(CONN_FMT "DIS %u characteristic handle = 0x%02x" APP_LOG_NL,
                                           conn,
                                           i,
                                           conn->gattdb_handles.dis_characteristics[i]);
            }
          } else {
            // Clean handles if not specified
            conn->gattdb_handles.services.dis = ESL_LIB_INVALID_SERVICE_HANDLE;
            conn->gattdb_handles.services.esl = ESL_LIB_INVALID_SERVICE_HANDLE;
            conn->gattdb_handles.services.ots = ESL_LIB_INVALID_SERVICE_HANDLE;
            for (uint8_t i = 0; i < sizeof(conn->gattdb_handles.dis_characteristics) / sizeof(uint16_t); i++) {
              conn->gattdb_handles.dis_characteristics[i] = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE;
            }
            for (uint8_t i = 0; i < sizeof(conn->gattdb_handles.esl_characteristics) / sizeof(uint16_t); i++) {
              conn->gattdb_handles.esl_characteristics[i] = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE;
            }
            for (uint8_t i = 0; i < sizeof(conn->gattdb_handles.ots_characteristics) / sizeof(uint16_t); i++) {
              conn->gattdb_handles.ots_characteristics[i] = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE;
            }
          }

          // Pass the ownership of initial connect command to conn. handle on success - otherwise ap_core will free it
          conn->command = cmd;
          conn->command->data.cmd_connect.conn_hnd = conn;
          conn->command_complete = false;
          esl_lib_log_connection_debug(CONN_FMT "Pending new connection to " ESL_LIB_LOG_ADDR_FORMAT APP_LOG_NL,
                                       conn,
                                       ESL_LIB_LOG_ADDR(*address));
        }
      } else {
        --cmd->data.cmd_connect.retries_left;
        conn->connection_handle = connection_handle;
        conn->state = ESL_LIB_CONNECTION_STATE_RECONNECTING;

        sc = app_timer_start(&conn->timer,
                             CONNECTION_TIMEOUT_MS,
                             connection_timeout,
                             conn,
                             false);
        if (sc != SL_STATUS_OK) {
          esl_lib_log_connection_error("Connection timeout reinit failed, handle = %u as 0x%p. Closing." APP_LOG_NL,
                                       conn->connection_handle,
                                       conn);
          (void)close_connection(conn);
        }
      }
    } else {
      esl_lib_log(((sc == SL_STATUS_BT_CTRL_CONNECTION_LIMIT_EXCEEDED) \
                   ? ESL_LIB_LOG_LEVEL_WARNING : ESL_LIB_LOG_LEVEL_ERROR),
                  ESL_LIB_LOG_MODULE_CONNECTION,
                  "Connection failed to " ESL_LIB_LOG_ADDR_FORMAT ", sc = 0x%02x" APP_LOG_NL,
                  ESL_LIB_LOG_ADDR(*address),
                  sc);
      if (conn != NULL) {
        (void)esl_lib_connection_remove_ptr(conn);
        cmd->data.cmd_connect.conn_hnd = ESL_LIB_INVALID_HANDLE;
      }
    }
  } else {
    esl_lib_log_connection_error("Connection failure, no more retry attempts" APP_LOG_NL);
    sc = SL_STATUS_BT_CTRL_CONNECTION_FAILED_TO_BE_ESTABLISHED;
    // Force removal of connection handle in case of no more retry
    (void)esl_lib_connection_remove_ptr(conn);
    cmd->data.cmd_connect.conn_hnd = ESL_LIB_INVALID_HANDLE;
  }
  return sc;
}

sl_status_t esl_lib_connection_add(uint8_t                  conn,
                                   esl_lib_connection_t     **ptr_out)
{
  sl_status_t sc;
  esl_lib_connection_t *ptr;

  if (ptr_out == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  esl_lib_log_connection_debug("Add ESL library handle for BLE connection handle = %d" APP_LOG_NL, conn);

  // Check if it exists
  sc = esl_lib_connection_find(conn, &ptr);
  if (sc == SL_STATUS_OK) {
    sc = SL_STATUS_ALREADY_EXISTS;
    *ptr_out = ptr;
  } else {
    ptr = (esl_lib_connection_t *)esl_lib_memory_allocate(sizeof(esl_lib_connection_t));
    if (ptr != NULL) {
      *ptr_out = ptr;
      memset(ptr, 0, sizeof(*ptr));
      ptr->connection_handle = conn;
      ptr->command_complete = true;
      sl_slist_push_back(&connection_list, &ptr->node);

      sc = app_timer_start(&ptr->timer,
                           CONNECTION_TIMEOUT_MS,
                           connection_timeout,
                           ptr,
                           false);
      if (sc == SL_STATUS_OK) {
        esl_lib_log_connection_debug("Added ESL library handle at 0x%p for connection handle = %u" APP_LOG_NL, ptr, conn);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
      // Close connection
      (void)sl_bt_connection_close(conn);
    }
  }
  if (sc != SL_STATUS_OK) {
    esl_lib_log_connection_error("Add connection handle = %u failed = 0x%04x" APP_LOG_NL, conn, sc);
  }

  return sc;
}

sl_status_t esl_lib_connection_find(uint8_t              conn,
                                    esl_lib_connection_t **ptr_out)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  esl_lib_connection_t *ptr;

  if (ptr_out == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  SL_SLIST_FOR_EACH_ENTRY(connection_list, ptr, esl_lib_connection_t, node) {
    if (conn == ptr->connection_handle) {
      *ptr_out = ptr;
      return SL_STATUS_OK;
    }
  }

  *ptr_out = NULL;
  return sc;
}

sl_status_t esl_lib_connection_remove_ptr(esl_lib_connection_t *ptr)
{
  if (esl_lib_connection_contains(ptr)) {
    esl_lib_connection_safe_remove_ptr(ptr);
  } else {
    esl_lib_log_connection_warning(CONN_FMT "Failed to remove the connection: handle not found" APP_LOG_NL, ptr);
  }

  return SL_STATUS_OK;
}

bool esl_lib_connection_contains(esl_lib_connection_t *ptr)
{
  bool ret = false;
  esl_lib_connection_t *iterator;

  SL_SLIST_FOR_EACH_ENTRY(connection_list, iterator, esl_lib_connection_t, node) {
    if (iterator == ptr) {
      return true;
    }
  }

  return ret;
}

void esl_lib_connection_cleanup(void)
{
  esl_lib_connection_t *conn;
  // Clean connection list
  while ((conn = (esl_lib_connection_t *)sl_slist_pop(&connection_list)) != NULL) {
    // Close connection
    (void)close_connection(conn);
    (void)esl_lib_connection_safe_remove_ptr(conn);
  }
  esl_lib_log_connection_debug("Connection cleanup complete" APP_LOG_NL);
}

sl_status_t esl_lib_connection_add_command(esl_lib_connection_t       *conn,
                                           esl_lib_command_list_cmd_t *cmd)
{
  sl_status_t sc;
  if (conn == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (!esl_lib_connection_contains(conn)) {
    return SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER;
  }
  sc = esl_lib_command_list_put(&conn->command_list, cmd);
  if (sc == SL_STATUS_OK) {
    esl_lib_log_connection_debug(CONN_FMT "Added command %d" APP_LOG_NL,
                                 conn,
                                 cmd->cmd_code);
  } else {
    esl_lib_log_connection_error(CONN_FMT "Add command %d failed, sc = 0x%04x" APP_LOG_NL,
                                 conn,
                                 cmd->cmd_code,
                                 sc);
  }
  return sc;
}

void esl_lib_connection_step(void)
{
  esl_lib_connection_t       *conn;
  esl_lib_command_list_cmd_t *cmd;

  SL_SLIST_FOR_EACH_ENTRY(connection_list, conn, esl_lib_connection_t, node) {
    if (conn->command_complete) {
      // If there is a running but complete command, remove it - except for ESL_LIB_CMD_CONNECT requests,
      // which are inherited from esl_lib_core and are therefore handled slightly differently.
      if ((conn->command != NULL) && (conn->command->cmd_code != ESL_LIB_CMD_CONNECT)) {
        esl_lib_command_list_remove(&conn->command_list, conn->command);
        conn->command = NULL;
      }
      // Move and execute next command.
      cmd = esl_lib_command_list_get(&conn->command_list);
      if (cmd != NULL) {
        esl_lib_log_connection_debug(CONN_FMT "Running next command = %d" APP_LOG_NL,
                                     conn,
                                     cmd->cmd_code);
        conn->command = cmd;
        conn->command_complete = false;
        run_command(conn->command);
      }
    }
  }
}

void esl_lib_connection_on_bt_event(sl_bt_msg_t *evt)
{
  sl_status_t           sc               = SL_STATUS_OK;
  esl_lib_connection_t  *conn            = NULL;
  uint8_t               *bonding_data    = NULL;
  uint8_t               bonding_data_len = 0;
  esl_lib_status_t      lib_status       = ESL_LIB_STATUS_UNSPECIFIED_ERROR;
  esl_lib_address_t     *addr            = NULL;
  esl_lib_pawr_t        *pawr            = NULL;
  esl_lib_connect_tlv_t *tlv             = NULL;

  switch (SL_BT_MSG_ID(evt->header)) {
    // Connection
    case sl_bt_evt_connection_opened_id:
      // Filter for central role
      if (evt->data.evt_connection_opened.master == CENTRAL_ROLE) {
        esl_lib_log_connection_debug("Connection opened in central role, connection handle = %u" APP_LOG_NL,
                                     evt->data.evt_connection_opened.connection);
        sc = esl_lib_connection_find(evt->data.evt_connection_opened.connection,
                                     &conn);
        if (sc == SL_STATUS_OK) {
          (void)app_timer_stop(&conn->timer);
          esl_lib_log_connection_debug(CONN_FMT "Connection found, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle);
          conn->last_error   = sc;
          conn->address_type = evt->data.evt_connection_opened.address_type;
          memcpy(conn->address.addr,
                 evt->data.evt_connection_opened.address.addr,
                 sizeof(conn->address.addr));
          // Try to set PHY for the connection
          (void)sl_bt_connection_set_preferred_phy(conn->connection_handle,
                                                   PREFERRED_PHY,
                                                   ACCEPTED_PHY);
          // Check OOB
          if (find_tlv(conn->command, ESL_LIB_CONNECT_DATA_TYPE_OOB_DATA, &tlv)) {
            aes_key_128 *remote_random = (aes_key_128 *)&tlv->data.data[0];
            aes_key_128 *remote_confirm = (aes_key_128 *)&tlv->data.data[sizeof(aes_key_128)];
            // Use remote OOB
            sc = sl_bt_sm_set_remote_oob(1, *remote_random, *remote_confirm);
            esl_lib_log_connection_debug(CONN_FMT "Entering OOB data, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);
            if (sc != SL_STATUS_OK) {
              lib_status = ESL_LIB_STATUS_BONDING_FAILED;
              esl_lib_log_connection_error(CONN_FMT "Failed to set remote OOB data, connection handle = %u" APP_LOG_NL,
                                           conn,
                                           conn->connection_handle);
            }
          }
          // Restart timer to guard the bonding procedure
          (void)app_timer_start(&conn->timer,
                                BONDING_TIMEOUT_MS,
                                connection_timeout,
                                conn,
                                false);
        } else {
          // Suppress error event for unknown connections
          sc = SL_STATUS_OK;
        }
        esl_lib_core_connection_complete();
        conn->state = ESL_LIB_CONNECTION_STATE_CONNECTION_OPENED;
      }
      break;
    case sl_bt_evt_connection_closed_id:
      esl_lib_log_connection_debug("Connection close evt, reason = 0x%04x, connection handle = %u" APP_LOG_NL,
                                   evt->data.evt_connection_closed.reason,
                                   evt->data.evt_connection_closed.connection);
      sc = esl_lib_connection_find(evt->data.evt_connection_closed.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        sl_status_t reason = evt->data.evt_connection_closed.reason;
        // Stop connection / reconnection timer
        (void)app_timer_stop(&conn->timer);
        (void)app_timer_stop(&conn->gatt_timer);
        esl_lib_log_connection_debug(CONN_FMT "Connection closing, connection handle = %u" APP_LOG_NL,
                                     conn,
                                     conn->connection_handle);
        if (check_connected(conn)) {
          esl_lib_log_connection_debug(CONN_FMT "Removing connection, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle);
          // Send status if connected.
          (void)send_connection_status(conn,
                                       ESL_LIB_FALSE,
                                       reason);
          // If close connection command is active
          if ((conn->command != NULL)
              && (conn->command->cmd_code == ESL_LIB_CMD_CLOSE_CONNECTION)) {
            conn->command_complete = true;
          }
          // And also remove connection from the list.
          (void)esl_lib_connection_remove_ptr(conn);
          conn = NULL;
        } else if (conn->command != NULL) {
          // Not connected, check if a retry is required (link issue or bonding issue)
          if ((conn->command->cmd_code == ESL_LIB_CMD_CONNECT)
              && (conn->command->data.cmd_connect.retries_left)
              && ((reason == SL_STATUS_BT_CTRL_CONNECTION_FAILED_TO_BE_ESTABLISHED)
                  || (conn->state == ESL_LIB_CONNECTION_STATE_BONDING_FAIL_RECONNECT))) {
            esl_lib_log_connection_debug(CONN_FMT "Connection retry scheduled, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);
            uint32_t timeout = RECONNECT_TIMEOUT_MS;
            // Check for PAwR connect request to set correct timeout
            if (find_tlv(conn->command, ESL_LIB_CONNECT_DATA_TYPE_PAWR, &tlv)) {
              esl_lib_pawr_subevent_t *pawr_sub = (esl_lib_pawr_subevent_t *)tlv->data.data;
              esl_lib_pawr_t *pawr = (esl_lib_pawr_t *)pawr_sub->handle;
              timeout = (pawr->config.adv_interval.max << 1) - (pawr->config.adv_interval.max >> 3); // = 1.5f * (pawr->config.adv_interval.max * 1.25f) [ms]
            }

            if (reason == SL_STATUS_BT_CTRL_CONNECTION_FAILED_TO_BE_ESTABLISHED
                && (conn->state == ESL_LIB_CONNECTION_STATE_CONNECTING
                    || conn->state == ESL_LIB_CONNECTION_STATE_RECONNECTING)) {
              // If a connection request via PAwR times out, the sl_bt_evt_connection_closed_id
              // event occurs without the preceding sl_bt_evt_connection_opened_id event!
              conn->command_complete = true;
              esl_lib_core_connection_complete();
            }
            // Schedule a reconnection to let tag process previous operation
            sc = app_timer_start(&conn->timer,
                                 timeout,
                                 reconnect_timeout,
                                 conn,
                                 false);
            if (sc != SL_STATUS_OK) {
              (void)send_connection_error(conn,
                                          ESL_LIB_STATUS_CONN_FAILED,
                                          evt->data.evt_connection_closed.reason,
                                          conn->state);
              esl_lib_log_connection_error(CONN_FMT "Failed to start retry timer, connection handle = %u" APP_LOG_NL,
                                           conn,
                                           conn->connection_handle);
              conn->command_complete = true;
            } else {
              break;
            }
          } else {
            // check again for the out-of-retries reason - set SL_STATUS_ABORT in case
            if (conn->command->cmd_code == ESL_LIB_CMD_CONNECT && conn->command->data.cmd_connect.retries_left == 0) {
              reason = SL_STATUS_ABORT;
              esl_lib_log_connection_debug(CONN_FMT "No more connect retry for " ESL_LIB_LOG_ADDR_FORMAT ", last handle = %u" APP_LOG_NL,
                                           conn,
                                           conn->address_type,
                                           (conn->address_type ? "random" : "public"),
                                           ESL_LIB_LOG_BD_ADDR(conn->address),
                                           conn->connection_handle);
            }
            (void)send_connection_error(conn,
                                        ESL_LIB_STATUS_CONN_FAILED,
                                        reason,
                                        conn->state);
            if ((conn->state == ESL_LIB_CONNECTION_STATE_CONNECTING
                 || conn->state == ESL_LIB_CONNECTION_STATE_RECONNECTING)
                && find_tlv(conn->command, ESL_LIB_CONNECT_DATA_TYPE_PAWR, &tlv)) {
              // If a connection request via PAwR times out, the sl_bt_evt_connection_closed_id
              // event occurs without the preceding sl_bt_evt_connection_opened_id event!
              conn->command_complete = true;
              esl_lib_core_connection_complete();
            }
          }
          // And also remove connection from the list in the end.
          (void)esl_lib_connection_remove_ptr(conn);
          conn = NULL;
        }
      } else {
        // Suppress error event for unknown connections
        sc = SL_STATUS_OK;
      }
      break;
    case sl_bt_evt_connection_parameters_id:
      sc = esl_lib_connection_find(evt->data.evt_connection_parameters.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        conn->security    = evt->data.evt_connection_parameters.security_mode;
        conn->max_payload = evt->data.evt_connection_parameters.txsize - GATT_OVERHEAD;
        esl_lib_log_connection_debug(CONN_FMT "Connection parameters, connection handle = %u, security = %u, payload = %u" APP_LOG_NL,
                                     conn,
                                     conn->connection_handle,
                                     conn->security,
                                     conn->max_payload);
        // Bonding is considered finished when security has elevated.
        if (evt->data.evt_connection_parameters.security_mode > sl_bt_connection_mode1_level1) {
          if (conn->state == ESL_LIB_CONNECTION_STATE_BONDING
              || conn->state == ESL_LIB_CONNECTION_STATE_APPLYING_LTK) {
            (void)app_timer_stop(&conn->timer);
            (void)send_bonding_finished(conn);
            if (conn->gattdb_known == ESL_LIB_TRUE) {
              esl_lib_log_connection_debug(CONN_FMT "GATTDB known, skipping discovery, connection handle = %u" APP_LOG_NL,
                                           conn,
                                           conn->connection_handle);
              // Subscribe to characteristics
              if (conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT]
                  != ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
                esl_lib_log_connection_debug(CONN_FMT "Subscribe to ESL CP notifications, connection handle = %u" APP_LOG_NL,
                                             conn,
                                             conn->connection_handle);
                sc = sl_bt_gatt_set_characteristic_notification(conn->connection_handle,
                                                                conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT],
                                                                sl_bt_gatt_notification);
              } else {
                sc = SL_STATUS_INVALID_HANDLE;
              }
              if (sc == SL_STATUS_OK) {
                (void)app_timer_stop(&conn->gatt_timer);
                conn->state = ESL_LIB_CONNECTION_STATE_ESL_SUBSCRIBE;
                sc = app_timer_start(&conn->gatt_timer,
                                     GATT_TIMEOUT_MS,
                                     gatt_timeout,
                                     conn,
                                     false);
              } else {
                esl_lib_log_connection_error(CONN_FMT "ESL CP subscribe failed, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                             conn,
                                             conn->connection_handle,
                                             sc);
                // Close connection
                (void)sl_bt_connection_close(conn->connection_handle);
                lib_status = ESL_LIB_STATUS_CONN_SUBSCRIBE_FAILED;
              }
            } else {
              esl_lib_log_connection_debug(CONN_FMT "Starting service discovery, connection handle = %u" APP_LOG_NL,
                                           conn,
                                           conn->connection_handle);

              // No predefined GATT database, start service discovery
              sc = sl_bt_gatt_discover_primary_services(conn->connection_handle);
              if (sc == SL_STATUS_OK) {
                (void)app_timer_stop(&conn->gatt_timer);
                conn->state = ESL_LIB_CONNECTION_STATE_SERVICE_DISCOVERY;
                sc = app_timer_start(&conn->gatt_timer,
                                     GATT_TIMEOUT_MS,
                                     gatt_timeout,
                                     conn,
                                     false);
              } else {
                esl_lib_log_connection_error(CONN_FMT "Error starting service discovery, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                             conn,
                                             conn->connection_handle,
                                             sc);
                // Close connection
                (void)sl_bt_connection_close(conn->connection_handle);
                lib_status = ESL_LIB_STATUS_CONN_DISCOVERY_FAILED;
              }
            }
          } else if (conn->state == ESL_LIB_CONNECTION_STATE_PAST_INIT) {
            (void)app_timer_stop(&conn->timer);
            esl_lib_log_connection_debug(CONN_FMT "PAST init, handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);
            pawr = (esl_lib_pawr_t *)conn->command->data.cmd_init_past.pawr_handle;
            if (esl_lib_pawr_contains(pawr)) {
              // Connection parameters changed by PAST init
              sc = sl_bt_advertiser_past_transfer(conn->connection_handle,
                                                  PAWR_SERVICE_DATA,
                                                  pawr->pawr_handle);
              if (sc == SL_STATUS_OK) {
                // calculate timeout as follows: tmeout_value_ms = 6 * (pawr->config.adv_interval.max * 1.25f) [ms]
                uint32_t past_timeout = PAST_GRACE_INTERVAL_COUNT \
                                        * ((pawr->config.adv_interval.max) + (pawr->config.adv_interval.max >> 2));
                conn->state = ESL_LIB_CONNECTION_STATE_PAST_CLOSE_CONNECTION;
                sc = app_timer_start(&conn->timer,
                                     past_timeout,
                                     connection_timeout,
                                     conn,
                                     false);
              }
              if (sc != SL_STATUS_OK) {
                lib_status = ESL_LIB_STATUS_PAST_INIT_FAILED;
              }
            } else {
              sc = SL_STATUS_NOT_FOUND;
              lib_status = ESL_LIB_STATUS_PAST_INIT_FAILED;
            }

            if (sc != SL_STATUS_OK) {
              esl_lib_log_connection_warning(CONN_FMT "PAST init unsuccesful, connection handle = %u, PAwR = [0x%p] sc = 0x%04x" APP_LOG_NL,
                                             conn,
                                             conn->connection_handle,
                                             conn->command->data.cmd_init_past.pawr_handle,
                                             sc);
              close_broken_connection(&conn);
            }
          }
        }
      } else {
        // Suppress error event for unknown connections
        sc = SL_STATUS_OK;
      }
      break;
    // Bonding
    case sl_bt_evt_external_bondingdb_data_request_id:
      sc = esl_lib_connection_find(evt->data.evt_external_bondingdb_data_request.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        if (evt->data.evt_external_bondingdb_data_request.type
            == sl_bt_external_bondingdb_data_remote_ltk) {
          esl_lib_log_connection_debug(CONN_FMT "Bonding LTK requested, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle);
          if (conn->state == ESL_LIB_CONNECTION_STATE_CONNECTION_OPENED) {
            // Check if LTK is set for the request
            if (find_tlv(conn->command, ESL_LIB_CONNECT_DATA_TYPE_LTK, &tlv)) {
              bonding_data = tlv->data.data;
              bonding_data_len = ESL_LIB_LTK_SIZE;
              conn->state = ESL_LIB_CONNECTION_STATE_APPLYING_LTK;
              lib_status = ESL_LIB_STATUS_CONN_FAILED;
              esl_lib_log_connection_debug(CONN_FMT "Applying LTK, connection handle = %u" APP_LOG_NL,
                                           conn,
                                           conn->connection_handle);
            } else {
              // New bond require if we do not have the LTK.
              conn->state = ESL_LIB_CONNECTION_STATE_NEW_BOND_REQUIRED;
              lib_status = ESL_LIB_STATUS_BONDING_FAILED;
              esl_lib_log_connection_debug(CONN_FMT "Creating new bond, connection handle = %u" APP_LOG_NL,
                                           conn,
                                           conn->connection_handle);
            }
          }
        }
      }
      sc = sl_bt_external_bondingdb_set_data(evt->data.evt_external_bondingdb_data_request.connection,
                                             evt->data.evt_external_bondingdb_data_request.type,
                                             bonding_data_len,
                                             bonding_data);
      if (sc == SL_STATUS_OK) {
        lib_status = ESL_LIB_STATUS_NO_ERROR;
      } else {
        // Defer forced close on error - normally the close event should come, this is just a watchdog
        (void)app_timer_stop(&conn->timer);
        (void)app_timer_start(&conn->timer,
                              CLOSE_TIMEOUT_MS,
                              connection_timeout,
                              conn,
                              false);
        esl_lib_log_connection_error(CONN_FMT "Bonding procedure disrupted, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                     conn,
                                     conn->connection_handle,
                                     sc);
      }
      break;
    case sl_bt_evt_sm_passkey_request_id:
      sc = esl_lib_connection_find(evt->data.evt_sm_passkey_request.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        esl_lib_log_connection_debug(CONN_FMT "Passkey requested, connection handle = %u" APP_LOG_NL,
                                     conn,
                                     conn->connection_handle);

        if (find_tlv(conn->command, ESL_LIB_CONNECT_DATA_TYPE_PASSKEY, &tlv)) {
          sc = sl_bt_sm_enter_passkey(conn->connection_handle,
                                      *((uint32_t*)tlv->data.data));
          esl_lib_log_connection_debug(CONN_FMT "Entering passkey, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle);
          if (sc != SL_STATUS_OK) {
            lib_status = ESL_LIB_STATUS_BONDING_FAILED;
            esl_lib_log_connection_error(CONN_FMT "Failed to set passkey, connection handle = %u. Closing." APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);
            // Close the connection in case of error.
            (void)sl_bt_connection_close(conn->connection_handle);
          }
        } else {
          esl_lib_log_connection_error(CONN_FMT "No passkey available but requested, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle);
        }
      } else {
        // Suppress error event for unknown connections
        sc = SL_STATUS_OK;
      }
      break;
    case sl_bt_evt_external_bondingdb_data_ready_id:
      sc = esl_lib_connection_find(evt->data.evt_external_bondingdb_data_ready.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        esl_lib_log_connection_debug(CONN_FMT "Bonding data ready, connection handle = %u" APP_LOG_NL,
                                     conn,
                                     conn->connection_handle);
        sc = sl_bt_sm_increase_security(conn->connection_handle);
        if (sc == SL_STATUS_OK) {
          conn->state = ESL_LIB_CONNECTION_STATE_BONDING;
        } else {
          // Close the connection in case of error.
          (void)sl_bt_connection_close(conn->connection_handle);
          lib_status = ESL_LIB_STATUS_BONDING_FAILED;
          esl_lib_log_connection_error(CONN_FMT "Increase security failed, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle,
                                       sc);
        }
      } else {
        // Suppress error event for unknown connections
        sc = SL_STATUS_OK;
      }
      break;
    case sl_bt_evt_external_bondingdb_data_id:
      // Check type of the bonding data first.
      if (evt->data.evt_external_bondingdb_data_request.type
          == sl_bt_external_bondingdb_data_remote_ltk) {
        // Find connection in the list.
        sc = esl_lib_connection_find(evt->data.evt_external_bondingdb_data.connection,
                                     &conn);
        if (sc == SL_STATUS_OK) {
          esl_lib_log_connection_debug(CONN_FMT "Bonding LTK arrived, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle);

          // Send LTK to the application.
          (void)send_bonding_data(conn,
                                  evt->data.evt_external_bondingdb_data.data.data);
        } else {
          sc = SL_STATUS_OK;
        }
      }
      break;
    case sl_bt_evt_sm_bonding_failed_id:
      sc = esl_lib_connection_find(evt->data.evt_sm_bonding_failed.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        if ((conn->command != NULL && conn->command->data.cmd_connect.retries_left)
            && ((evt->data.evt_sm_bonding_failed.reason == SL_STATUS_BT_CTRL_PIN_OR_KEY_MISSING)
                || (evt->data.evt_sm_bonding_failed.reason == SL_STATUS_BT_SMP_PAIRING_NOT_SUPPORTED))) {
          esl_lib_log_connection_warning(CONN_FMT "Bonding failed, reconnecting, connection handle = %u, reason = 0x%04x" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle,
                                         evt->data.evt_sm_bonding_failed.reason);
          if (evt->data.evt_sm_bonding_failed.reason == SL_STATUS_BT_CTRL_PIN_OR_KEY_MISSING) {
            // Remove LTK if present
            esl_lib_connect_tlv_t *tlv;
            if (find_tlv(conn->command, ESL_LIB_CONNECT_DATA_TYPE_LTK, &tlv)) {
              tlv->type = ESL_LIB_CONNECT_DATA_TYPE_INVALID_TYPE;
              esl_lib_log_connection_warning(CONN_FMT "LTK dropped, connection handle = %u" APP_LOG_NL,
                                             conn,
                                             conn->connection_handle);
            }
          }
          // Set connection state to match this
          conn->state = ESL_LIB_CONNECTION_STATE_BONDING_FAIL_RECONNECT;
          // Bypass event
          sc = SL_STATUS_OK;
          lib_status = ESL_LIB_STATUS_NO_ERROR;
        } else {
          esl_lib_log_connection_error(CONN_FMT "Bonding failed, disconnecting, connection handle = %u, reason = 0x%04x" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle,
                                       evt->data.evt_sm_bonding_failed.reason);
          // Set library status accordingly.
          lib_status = ESL_LIB_STATUS_BONDING_FAILED;
          // Save reason to the status variable.
          sc = evt->data.evt_sm_bonding_failed.reason;
        }
        // Try to close connection
        (void)close_connection(conn);
      } else {
        // Suppress error event for unknown connections
        sc = SL_STATUS_OK;
      }
      break;
    // GATT
    case sl_bt_evt_gatt_service_id:
      sc = esl_lib_connection_find(evt->data.evt_gatt_service.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        // Check size for UUID if in proper state - send error otherwise
        if (conn->state != ESL_LIB_CONNECTION_STATE_SERVICE_DISCOVERY) {
          sc = SL_STATUS_INVALID_STATE;
          lib_status = conn->state;
          esl_lib_log_connection_error(CONN_FMT "Service discovery failed, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle,
                                       sc);
          (void)sl_bt_connection_close(conn->connection_handle);
        } else if (evt->data.evt_gatt_service.uuid.len == sizeof(sl_bt_uuid_16_t)) {
          // Check for service UUIDs
          if (uuid_16_match(evt->data.evt_gatt_service.uuid.data, (uint8_t *)uuid_map.services.dis.data)) {
            esl_lib_log_connection_debug(CONN_FMT "DIS service found, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);
            // Copy DIS handle
            conn->gattdb_handles.services.dis = evt->data.evt_gatt_service.service;
          } else if (uuid_16_match(evt->data.evt_gatt_service.uuid.data, (uint8_t *)uuid_map.services.esl.data)) {
            esl_lib_log_connection_debug(CONN_FMT "ESL service found, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);
            // Copy ESL handle
            conn->gattdb_handles.services.esl = evt->data.evt_gatt_service.service;
          } else if (uuid_16_match(evt->data.evt_gatt_service.uuid.data, (uint8_t *)uuid_map.services.ots.data)) {
            esl_lib_log_connection_debug(CONN_FMT "OTS service found, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);

            // Copy OTS handle
            conn->gattdb_handles.services.ots = evt->data.evt_gatt_service.service;
          }
        }
      } else {
        sc = SL_STATUS_OK;
      }
      break;
    case sl_bt_evt_gatt_characteristic_id:
      sc = esl_lib_connection_find(evt->data.evt_gatt_characteristic.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        // Check size
        if (evt->data.evt_gatt_characteristic.uuid.len == sizeof(sl_bt_uuid_16_t)) {
          // Iterate over ESL characteristic UUIDs
          // ESL characteristics
          for (uint8_t i = 0; i < ESL_LIB_CHARACTERISTIC_INDEX_SIZE; i++) {
            if (uuid_16_match(evt->data.evt_gatt_characteristic.uuid.data, (uint8_t *)uuid_map.esl_characteristics[i].data)) {
              esl_lib_log_connection_debug(CONN_FMT "ESL characteristic %d found, connection handle = %u" APP_LOG_NL,
                                           conn,
                                           i,
                                           conn->connection_handle);

              // Assign GATT database handle
              conn->gattdb_handles.esl_characteristics[i] = evt->data.evt_gatt_characteristic.characteristic;
            }
          }
          // DIS characteristic
          for (uint8_t i = 0; i < ESL_LIB_CHARACTERISTIC_INDEX_DIS_SIZE; i++) {
            if (uuid_16_match(evt->data.evt_gatt_characteristic.uuid.data,
                              (uint8_t *)uuid_map.dis_characteristics[i].data)) {
              esl_lib_log_connection_debug(CONN_FMT "DIS characteristic %u found, connection handle = %u" APP_LOG_NL,
                                           conn,
                                           i,
                                           conn->connection_handle);
              conn->gattdb_handles.dis_characteristics[i] = evt->data.evt_gatt_characteristic.characteristic;
            }
          }
        }
      } else {
        // Suppress error event for unknown connections
        sc = SL_STATUS_OK;
      }
      break;
    case sl_bt_evt_gatt_characteristic_value_id:
      esl_lib_log_connection_debug("Char value, opcode: %u" APP_LOG_NL, evt->data.evt_gatt_characteristic_value.att_opcode);
      sc = esl_lib_connection_find(evt->data.evt_gatt_characteristic_value.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        if (evt->data.evt_gatt_characteristic_value.att_opcode == sl_bt_gatt_read_response) {
          esl_lib_log_connection_debug(CONN_FMT "Read response, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle);
          if (conn->state == ESL_LIB_CONNECTION_STATE_GET_TAG_INFO) {
            lib_status = ESL_LIB_STATUS_CONN_READ_FAILED;
            sc = esl_lib_storage_append(conn->tag_info_data,
                                        &evt->data.evt_gatt_characteristic_value.value);
            if (sc == SL_STATUS_OK) {
              lib_status = ESL_LIB_STATUS_NO_ERROR;
            }
          }
        } else if (evt->data.evt_gatt_characteristic_value.att_opcode == sl_bt_gatt_handle_value_notification) {
          // Notification arrived
          if (evt->data.evt_gatt_characteristic_value.characteristic
              == conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT]) {
            esl_lib_log_connection_debug(CONN_FMT "CP notification received, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);
            (void)send_cp_notification_event(conn,
                                             evt->data.evt_gatt_characteristic_value.value.len,
                                             evt->data.evt_gatt_characteristic_value.value.data);
          }
        }
      } else {
        // Suppress error event for unknown connections
        sc = SL_STATUS_OK;
      }
      break;
    case sl_bt_evt_gatt_procedure_completed_id:
      sc = esl_lib_connection_find(evt->data.evt_gatt_procedure_completed.connection,
                                   &conn);
      if (sc == SL_STATUS_OK) {
        if (conn->state == ESL_LIB_CONNECTION_STATE_WRITE_CONTROL_POINT) {
          // This state is active only if write with response requested
          // Send response with the result
          (void)send_att_response(conn,
                                  ESL_LIB_EVT_CONTROL_POINT_RESPONSE,
                                  evt->data.evt_gatt_procedure_completed.result);
          conn->command_complete = true;
          esl_lib_log_connection_debug(CONN_FMT "Control point written, result = 0x%04x, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       evt->data.evt_gatt_procedure_completed.result,
                                       conn->connection_handle);
        } else if (conn->state == ESL_LIB_CONNECTION_STATE_CONFIGURE_TAG) {
          // This state is active only if write with response requested
          esl_lib_log_connection_debug(CONN_FMT "Configure tag - Writing next value, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       conn->connection_handle);
          // Send response with the result
          (void)send_att_response(conn,
                                  ESL_LIB_EVT_CONFIGURE_TAG_RESPONSE,
                                  evt->data.evt_gatt_procedure_completed.result);
          // Write next configuration value
          write_next_config_value(conn);
        } else {
          // Check result first for all other cases
          if (evt->data.evt_gatt_procedure_completed.result == SL_STATUS_OK) {
            esl_lib_log_connection_debug(CONN_FMT "Procedure completed, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->connection_handle);
            switch (conn->state) {
              case ESL_LIB_CONNECTION_STATE_GET_TAG_INFO:
                lib_status = ESL_LIB_STATUS_CONN_READ_FAILED;
                esl_lib_log_connection_debug(CONN_FMT "Tag info %u arrived, connection handle = %u" APP_LOG_NL,
                                             conn,
                                             conn->tag_info_type,
                                             conn->connection_handle);
                // Save tag info, completed
                sc = save_tag_info(conn);
                if (sc == SL_STATUS_OK) {
                  esl_lib_log_connection_debug(CONN_FMT "Read next tag info, connection handle = %u" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle);
                  // Move to next one
                  sc = get_next_tag_info(conn);
                  if (sc == SL_STATUS_OK) {
                    lib_status = ESL_LIB_STATUS_NO_ERROR;
                  }
                } else {
                  sc = get_tag_info_finish(conn, sc);
                }
                break;
              case ESL_LIB_CONNECTION_STATE_SERVICE_DISCOVERY:
                (void)app_timer_stop(&conn->gatt_timer);
                // If DIS found
                if (conn->gattdb_handles.services.dis != ESL_LIB_INVALID_SERVICE_HANDLE) {
                  esl_lib_log_connection_debug(CONN_FMT "Service discovery finished, start DIS discovery, connection handle = %u" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle);
                  // Discover Device Information Service service characteristics
                  sc = sl_bt_gatt_discover_characteristics(conn->connection_handle,
                                                           conn->gattdb_handles.services.dis);
                  if (sc == SL_STATUS_OK) {
                    conn->state = ESL_LIB_CONNECTION_STATE_DIS_DISCOVERY;
                    sc = app_timer_start(&conn->gatt_timer,
                                         GATT_TIMEOUT_MS,
                                         gatt_timeout,
                                         conn,
                                         false);
                  }
                  if (sc != SL_STATUS_OK) {
                    // Close connection
                    (void)sl_bt_connection_close(conn->connection_handle);
                    lib_status = ESL_LIB_STATUS_CONN_DISCOVERY_FAILED;
                    esl_lib_log_connection_error(CONN_FMT "DIS discovery failed, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                                 conn,
                                                 conn->connection_handle,
                                                 sc);
                  }
                } else if (conn->gattdb_handles.services.esl != ESL_LIB_INVALID_SERVICE_HANDLE) {
                  esl_lib_log_connection_debug(CONN_FMT "Service discovery finished, start ESL discovery, connection handle = %u" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle);
                  // Discover ESL service characteristics
                  sc = sl_bt_gatt_discover_characteristics(conn->connection_handle,
                                                           conn->gattdb_handles.services.esl);
                  if (sc == SL_STATUS_OK) {
                    conn->state = ESL_LIB_CONNECTION_STATE_ESL_DISCOVERY;
                    sc = app_timer_start(&conn->gatt_timer,
                                         GATT_TIMEOUT_MS,
                                         gatt_timeout,
                                         conn,
                                         false);
                  }
                } else {
                  sc = SL_STATUS_BT_ATT_INVALID_HANDLE;
                }
                if (sc != SL_STATUS_OK) {
                  // Close connection
                  (void)sl_bt_connection_close(conn->connection_handle);
                  lib_status = ESL_LIB_STATUS_CONN_DISCOVERY_FAILED;
                  esl_lib_log_connection_error(CONN_FMT "Discovery failed, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle,
                                               sc);
                }
                break;
              case ESL_LIB_CONNECTION_STATE_DIS_DISCOVERY:
                (void)app_timer_stop(&conn->gatt_timer);
                if (conn->gattdb_handles.services.esl != ESL_LIB_INVALID_SERVICE_HANDLE) {
                  // Discover ESL service characteristics
                  esl_lib_log_connection_debug(CONN_FMT "Device information discovery finished, start ESL discovery, connection handle = %u" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle);

                  sc = sl_bt_gatt_discover_characteristics(conn->connection_handle,
                                                           conn->gattdb_handles.services.esl);
                  if (sc == SL_STATUS_OK) {
                    conn->state = ESL_LIB_CONNECTION_STATE_ESL_DISCOVERY;
                    sc = app_timer_start(&conn->gatt_timer,
                                         GATT_TIMEOUT_MS,
                                         gatt_timeout,
                                         conn,
                                         false);
                  }
                  if (sc != SL_STATUS_OK) {
                    // Close connection
                    (void)sl_bt_connection_close(conn->connection_handle);
                    lib_status = ESL_LIB_STATUS_CONN_DISCOVERY_FAILED;
                    esl_lib_log_connection_error(CONN_FMT "DIS discovery failed, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                                 conn,
                                                 conn->connection_handle,
                                                 sc);
                  }
                } else {
                  // Set the cause of the error
                  sc = SL_STATUS_INVALID_HANDLE;
                  // Close connection
                  (void)sl_bt_connection_close(conn->connection_handle);
                  lib_status = ESL_LIB_STATUS_CONN_DISCOVERY_FAILED;
                  esl_lib_log_connection_error(CONN_FMT "ESL Service not found, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle,
                                               sc);
                }
                break;
              case ESL_LIB_CONNECTION_STATE_ESL_DISCOVERY:
                (void)app_timer_stop(&conn->gatt_timer);
                // Subscribe to characteristics
                if (conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT]
                    != ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
                  esl_lib_log_connection_debug(CONN_FMT "Feature discovery complete, subscribe to ESL CP notifications, connection handle = %u" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle);
                  // Check validity of the handles.
                  sc = esl_lib_connection_check_gattdb_handles(&(conn->gattdb_handles));
                  if (sc == SL_STATUS_OK) {
                    conn->gattdb_known = ESL_LIB_TRUE;
                    sc = sl_bt_gatt_set_characteristic_notification(conn->connection_handle,
                                                                    conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT],
                                                                    sl_bt_gatt_notification);
                    if (sc == SL_STATUS_OK) {
                      conn->state = ESL_LIB_CONNECTION_STATE_ESL_SUBSCRIBE;
                      sc = app_timer_start(&conn->gatt_timer,
                                           GATT_TIMEOUT_MS,
                                           gatt_timeout,
                                           conn,
                                           false);
                    }
                  } else {
                    sc = SL_STATUS_BT_ATT_CLIENT_CHARACTERISTIC_CONFIGURATION_DESCRIPTOR_IMPROPERLY_CONFIGURED; // ESL does not meet Profile / Service specification!
                  }
                  if (sc != SL_STATUS_OK) {
                    // Close connection
                    (void)sl_bt_connection_close(conn->connection_handle);
                    lib_status = ESL_LIB_STATUS_CONN_SUBSCRIBE_FAILED;
                    esl_lib_log_connection_error(CONN_FMT "Subscribe failed, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                                 conn,
                                                 conn->connection_handle,
                                                 sc);
                  }
                } else {
                  // Set the cause of the error
                  sc = SL_STATUS_INVALID_HANDLE;
                  // Close connection
                  (void)sl_bt_connection_close(conn->connection_handle);
                  lib_status = ESL_LIB_STATUS_CONN_SUBSCRIBE_FAILED;
                  esl_lib_log_connection_error(CONN_FMT "ESL CP not found, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle,
                                               sc);
                }
                break;
              case ESL_LIB_CONNECTION_STATE_ESL_SUBSCRIBE:
                (void)app_timer_stop(&conn->gatt_timer);
                // Check presense of OTS service
                if (conn->gattdb_handles.services.ots != ESL_LIB_INVALID_SERVICE_HANDLE) {
                  esl_lib_log_connection_debug(CONN_FMT "Initializing Image Transfer - OTS, connection handle = %u" APP_LOG_NL,
                                               conn,
                                               conn->connection_handle);
                  // Initialize Image transfer
                  sc = esl_lib_image_transfer_init(conn->connection_handle,
                                                   conn->gattdb_handles.services.ots,
                                                   on_image_transfer_status,
                                                   on_image_transfer_type_arrived,
                                                   on_image_transfer_finished,
                                                   NULL,
                                                   &conn->ots_handle);
                  if (sc == SL_STATUS_OK) {
                    conn->state = ESL_LIB_CONNECTION_STATE_OTS_INIT;
                  } else {
                    // Close connection
                    (void)sl_bt_connection_close(conn->connection_handle);
                    lib_status = ESL_LIB_STATUS_OTS_INIT_FAILED;
                    esl_lib_log_connection_error(CONN_FMT "Image Transfer - OTS init failed, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                                 conn,
                                                 conn->connection_handle,
                                                 sc);
                  }
                } else {
                  // If no OTS present, consider complete
                  connection_complete(conn);
                }
                break;
              default:
                break;
            }
          } else {
            // If not in image transfer, procedures handled by this module
            if (!check_image_transfer(conn)) {
              // Close connection on procedure failure
              (void)sl_bt_connection_close(conn->connection_handle);
              lib_status = ESL_LIB_STATUS_CONN_LOST;
              sc = evt->data.evt_gatt_procedure_completed.result;
              esl_lib_log_connection_error(CONN_FMT "Procedure failure, connection handle = %u, result = 0x%04x" APP_LOG_NL,
                                           conn,
                                           conn->connection_handle,
                                           sc);
            }
          }
        }
      } else {
        // Suppress error event for unknown connections
        sc = SL_STATUS_OK;
      }
      break;
    default:
      break;
  }
  if (sc != SL_STATUS_OK) {
    esl_lib_status_data_t state;

    if (conn != NULL) {
      state.connection_state = conn->state;
      // Send connection error if connection is present.
      (void)send_connection_error(conn,
                                  lib_status,
                                  sc,
                                  conn->state);
      conn->command_complete = true;
    } else {
      esl_lib_node_id_t node_id;
      state.core_state = ESL_LIB_CORE_STATE_CONNECTING;
      if (addr != NULL) {
        // Send address if present.
        node_id.type = ESL_LIB_NODE_ID_TYPE_ADDRESS;
        node_id.id.address.address_type = addr->address_type;
        memcpy(node_id.id.address.addr, addr->addr, sizeof(bd_addr));
      } else {
        node_id.type = ESL_LIB_NODE_ID_TYPE_NONE;
      }

      // Send available data in the error message
      (void)esl_lib_event_push_error(lib_status,
                                     &node_id,
                                     sc,
                                     state);
    }
  }
}

// -----------------------------------------------------------------------------
// Private functions
static void esl_lib_connection_safe_remove_ptr(esl_lib_connection_t *ptr)
{
  (void)app_timer_stop(&ptr->timer);
  (void)app_timer_stop(&ptr->gatt_timer);
  sl_slist_remove(&connection_list, &ptr->node);
  esl_lib_command_list_cleanup(&ptr->command_list);

  if (ptr->command != NULL) {
    if (ptr->command->cmd_code == ESL_LIB_CMD_WRITE_IMAGE
        && ptr->command->data.cmd_write_image.img_data_copied != NULL) {
      esl_lib_memory_free(ptr->command->data.cmd_write_image.img_data_copied);
    }
    esl_lib_memory_free(ptr->command);
  }
  clean_tag_info(ptr);
  esl_lib_log_connection_debug(CONN_FMT "Removed connection handle = %u" APP_LOG_NL,
                               ptr,
                               ptr->connection_handle);
  // Sanitize handles in memory area to avoid possible corruption later due to garbage
  ptr->connection_handle = SL_BT_INVALID_CONNECTION_HANDLE;
  ptr->ots_handle        = ESL_LIB_INVALID_HANDLE;
  esl_lib_memory_free(ptr);
}

static void run_command(esl_lib_command_list_cmd_t *cmd)
{
  sl_status_t          sc         = SL_STATUS_OK;
  esl_lib_connection_t *conn      = NULL;
  esl_lib_status_t     lib_status = ESL_LIB_STATUS_NO_ERROR;

  switch (cmd->cmd_code) {
    case ESL_LIB_CMD_CLOSE_CONNECTION:
      conn = (esl_lib_connection_t *)cmd->data.cmd_close_connection;
      esl_lib_log_connection_debug(CONN_FMT "Close connection command, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      if (esl_lib_connection_contains(conn)) {
        sc = close_connection(conn);
      } else {
        sc         = SL_STATUS_DELETED;
        lib_status = ESL_LIB_STATUS_CONN_FAILED;
        conn->command_complete = true;
      }
      esl_lib_log_connection_debug(CONN_FMT "After Close connection command, connection handle = %u , sc = 0x%04x" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle,
                                   sc);
      break;
    case ESL_LIB_CMD_GET_TAG_INFO:
      conn = (esl_lib_connection_t *)cmd->data.cmd_write_image.connection_handle;
      esl_lib_log_connection_debug(CONN_FMT "Get tag info command, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      lib_status = ESL_LIB_STATUS_CONN_READ_FAILED;
      if (esl_lib_connection_contains(conn)) {
        // Check OTS features
        if (conn->ots_handle != ESL_LIB_INVALID_HANDLE) {
          conn->tag_info_type = ESL_LIB_DATA_TYPE_GATT_OTS_FEATURE;
          // Allocate an array
          uint8_t data[sizeof(uint8array) + sizeof(esl_lib_ots_features_t)];
          // Refer to the data as an uint8 array
          uint8array *data_send = (uint8array*)&data;
          // Set pointer to data part of the array as OTS features
          esl_lib_ots_features_t *features = (esl_lib_ots_features_t *)&data_send->data;
          // Set size of the data
          data_send->len = sizeof(esl_lib_ots_features_t);
          // Get data
          sc = esl_lib_image_transfer_get_features(conn->ots_handle, features);
          if (sc == SL_STATUS_OK) {
            // Create storage
            sc = esl_lib_storage_create(&conn->tag_info_data);
            if (sc == SL_STATUS_OK) {
              // Append data
              sc = esl_lib_storage_append(conn->tag_info_data, data_send);
              if (sc == SL_STATUS_OK) {
                // Save data to the list
                sc = save_tag_info(conn);
              }
            }
          }
          if (sc != SL_STATUS_OK) {
            esl_lib_log_connection_error(CONN_FMT "Failed to get OTS features %u, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->tag_info_type,
                                         conn->connection_handle);
            sc = get_tag_info_finish(conn, sc);
          }
        }
        if (sc == SL_STATUS_OK) {
          sc = get_next_tag_info(conn);
          if (sc == SL_STATUS_OK) {
            conn->state = ESL_LIB_CONNECTION_STATE_GET_TAG_INFO;
            lib_status = ESL_LIB_STATUS_NO_ERROR;
          }
        }
      } else {
        sc = SL_STATUS_DELETED;
        conn->command_complete = true;
      }
      break;
    case ESL_LIB_CMD_CONFIGURE_TAG:
      conn = (esl_lib_connection_t *)cmd->data.cmd_configure_tag.connection_handle;
      esl_lib_log_connection_debug(CONN_FMT "Configure tag command, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      lib_status = ESL_LIB_STATUS_CONN_CONFIG_FAILED;
      if (esl_lib_connection_contains(conn)) {
        // Clear index and type
        conn->config_index = 0;
        conn->config_type = ESL_LIB_DATA_TYPE_UNINITIALIZED;
        // Start write process using TLV(s)
        (void)write_next_config_value(conn);
      } else {
        sc = SL_STATUS_DELETED;
        conn->command_complete = true;
      }
      break;
    case ESL_LIB_CMD_WRITE_CONTROL_POINT:
      conn = (esl_lib_connection_t *)cmd->data.cmd_write_control_point.connection_handle;
      esl_lib_log_connection_debug(CONN_FMT "Write control point command, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      lib_status = ESL_LIB_STATUS_CONN_WRITE_CP_FAILED;
      if (esl_lib_connection_contains(conn) && conn->command != NULL) {
        // Write characteristic value (with or without response)
        sc = write_value(conn,
                         conn->command->data.cmd_write_control_point.att_response,
                         ESL_LIB_DATA_TYPE_GATT_CONTROL_POINT,
                         conn->command->data.cmd_write_control_point.data.len,
                         conn->command->data.cmd_write_control_point.data.data);
        if (sc == SL_STATUS_OK) {
          if (conn->command->data.cmd_write_control_point.att_response == ESL_LIB_TRUE) {
            // Set state
            conn->state = ESL_LIB_CONNECTION_STATE_WRITE_CONTROL_POINT;
          } else {
            (void)send_att_response(conn,
                                    ESL_LIB_EVT_CONTROL_POINT_RESPONSE,
                                    sc);
            conn->command_complete = true;
          }
          lib_status = ESL_LIB_STATUS_NO_ERROR;
        } else {
          (void)send_att_response(conn,
                                  ESL_LIB_EVT_CONTROL_POINT_RESPONSE,
                                  sc);
          conn->command_complete = true;
          // Do not generate error event
          sc = SL_STATUS_OK;
        }
      } else {
        sc = SL_STATUS_DELETED;
        conn->command_complete = true;
      }
      break;
    case ESL_LIB_CMD_WRITE_IMAGE:
      conn = (esl_lib_connection_t *)cmd->data.cmd_write_image.connection_handle;
      esl_lib_log_connection_debug(CONN_FMT "Write image command, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      if (esl_lib_connection_contains(conn)) {
        esl_lib_image_transfer_handle_t it_handle = conn->ots_handle;
        if (it_handle != ESL_LIB_INVALID_HANDLE) {
          sc = esl_lib_image_transfer_start(it_handle,
                                            cmd->data.cmd_write_image.img_index,
                                            0,
                                            cmd->data.cmd_write_image.img_size,
                                            cmd->data.cmd_write_image.img_data_copied);
          if (sc == SL_STATUS_OK) {
            conn->state = ESL_LIB_CONNECTION_STATE_OTS_IMAGE_TRANSFER;
          } else {
            lib_status = ESL_LIB_STATUS_OTS_ERROR;
            conn->command_complete = true;
          }
        } else {
          sc         = SL_STATUS_NOT_INITIALIZED;
          lib_status = ESL_LIB_STATUS_OTS_ERROR;
          conn->command_complete = true;
        }
      } else {
        sc         = SL_STATUS_DELETED;
        lib_status = ESL_LIB_STATUS_OTS_ERROR;
        conn->command_complete = true;
      }
      break;
    case ESL_LIB_CMD_GET_IMAGE_TYPE:
      conn = (esl_lib_connection_t *)cmd->data.cmd_get_image_type.connection_handle;
      esl_lib_log_connection_debug(CONN_FMT "Get image type command, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      if (esl_lib_connection_contains(conn)) {
        esl_lib_image_transfer_handle_t it_handle = conn->ots_handle;
        if (it_handle != ESL_LIB_INVALID_HANDLE) {
          sc = esl_lib_image_transfer_get_type(it_handle,
                                               cmd->data.cmd_get_image_type.img_index);
          if (sc == SL_STATUS_OK) {
            conn->state = ESL_LIB_CONNECTION_STATE_OTS_GET_TYPE;
          } else {
            lib_status = ESL_LIB_STATUS_OTS_ERROR;
            conn->command_complete = true;
          }
        } else {
          sc         = SL_STATUS_NOT_INITIALIZED;
          lib_status = ESL_LIB_STATUS_OTS_ERROR;
          conn->command_complete = true;
        }
      } else {
        sc         = SL_STATUS_DELETED;
        lib_status = ESL_LIB_STATUS_OTS_ERROR;
        conn->command_complete = true;
      }
      break;
    case ESL_LIB_CMD_INITIATE_PAST: {
      uint32_t supervison_timeout = PAST_CONN_DEFAULT_TIMEOUT;
      uint16_t min_interval = 2 * PAST_CONN_INTERVAL_MIN;
      uint16_t max_interval = PAST_CONN_INTERVAL_MAX;

      conn = (esl_lib_connection_t *)cmd->data.cmd_init_past.connection_handle;
      esl_lib_pawr_t *pawr = NULL;
      esl_lib_log_connection_debug(CONN_FMT "Initiate PAST command, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      if (conn->command != NULL) {
        pawr = (esl_lib_pawr_t *)conn->command->data.cmd_init_past.pawr_handle;
      }

      if (esl_lib_connection_contains(conn) && esl_lib_pawr_contains(pawr)) {
        supervison_timeout = pawr->config.adv_interval.max + pawr->config.adv_interval.max / 4; // * 1.25ms
        min_interval = pawr->config.adv_interval.min / 8;
        max_interval = pawr->config.adv_interval.max / 4;

        if (max_interval > PAST_CONN_INTERVAL_MAX) {
          max_interval = PAST_CONN_INTERVAL_MAX;
        }

        supervison_timeout *= (PAST_CONN_PERIPHERAL_LATENCY + 1); // Core spec. 5.4 Vol 4, Part E, 7.8.31.
        supervison_timeout = (supervison_timeout / 10) + 1;

        if (supervison_timeout > PAST_CONN_MAX_TIMEOUT) {
          supervison_timeout = PAST_CONN_MAX_TIMEOUT;
        } else if (supervison_timeout < PAST_CONN_MIN_TIMEOUT) {
          supervison_timeout = PAST_CONN_MIN_TIMEOUT;
        }

        if (min_interval < PAST_CONN_INTERVAL_MIN) {
          min_interval = PAST_CONN_INTERVAL_MIN;
        } else if (min_interval > max_interval / 2) {
          min_interval = max_interval / 2;
        }

        sc = sl_bt_connection_set_parameters(conn->connection_handle,
                                             min_interval,
                                             max_interval,
                                             PAST_CONN_PERIPHERAL_LATENCY,
                                             (uint16_t)supervison_timeout,
                                             PAST_CONN_MIN_CE_LENGTH,
                                             PAST_CONN_MAX_CE_LENGTH);
        if (sc == SL_STATUS_OK) {
          conn->state = ESL_LIB_CONNECTION_STATE_PAST_INIT;
        } else {
          lib_status = ESL_LIB_STATUS_PAST_INIT_FAILED;
          conn->command_complete = true;
          // Ignore the warning if the connection is already closed by a remote node still in sync
          if (sc != SL_STATUS_BT_CTRL_COMMAND_DISALLOWED) {
            esl_lib_log_connection_warning(CONN_FMT "PAST init fail with connection interval[%u - %u] and timeout: %u, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                           conn,
                                           min_interval,
                                           max_interval,
                                           supervison_timeout,
                                           conn->connection_handle,
                                           sc);
          }
        }
        // Start timeout anyway: the ESL may close/closing/closed the connection because it can be already in sync
        sc = app_timer_start(&conn->timer,
                             10 * supervison_timeout,
                             connection_timeout,
                             conn,
                             false);
      } else {
        sc         = SL_STATUS_DELETED;
        lib_status = ESL_LIB_STATUS_PAST_INIT_FAILED;
        conn->command_complete = true;
      }
    } break;
    default:
      break;
  }
  if (sc != SL_STATUS_OK && conn != NULL) {
    esl_lib_log_connection_warning(CONN_FMT "Command failure, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle,
                                   sc);
    // Send connection error if connection is present.
    (void)send_connection_error(conn,
                                lib_status,
                                sc,
                                conn->state);
  }
}

static sl_status_t send_cp_notification_event(esl_lib_connection_t *conn,
                                              uint8_t              len,
                                              uint8_t              *data)
{
  sl_status_t   sc;
  esl_lib_evt_t *lib_evt;

  sc = esl_lib_event_list_allocate(ESL_LIB_EVT_CONTROL_POINT_NOTIFICATION,
                                   len,
                                   &lib_evt);
  if (sc == SL_STATUS_OK) {
    lib_evt->evt_code = ESL_LIB_EVT_CONTROL_POINT_NOTIFICATION;
    lib_evt->data.evt_control_point_notification.connection_handle
      = (esl_lib_connection_handle_t)conn;
    lib_evt->data.evt_control_point_notification.data.len = len;
    memcpy(lib_evt->data.evt_control_point_notification.data.data,
           data,
           len);
    sc = esl_lib_event_list_push_back(lib_evt);
    if (sc != SL_STATUS_OK) {
      // Free up memory on failure
      esl_lib_memory_free(lib_evt);
    }
  }

  return sc;
}

static sl_status_t send_bonding_finished(esl_lib_connection_t *conn)
{
  sl_status_t   sc;
  esl_lib_evt_t *lib_evt;

  sc = esl_lib_event_list_allocate(ESL_LIB_EVT_BONDING_FINISHED,
                                   0,
                                   &lib_evt);
  if (sc == SL_STATUS_OK) {
    lib_evt->evt_code = ESL_LIB_EVT_BONDING_FINISHED;
    lib_evt->data.evt_bonding_finished.connection_handle
      = (esl_lib_connection_handle_t)conn;
    // Copy address
    lib_evt->data.evt_bonding_finished.address.address_type
      = conn->address_type;
    memcpy(lib_evt->data.evt_bonding_finished.address.addr,
           conn->address.addr,
           sizeof(conn->address.addr));
    sc = esl_lib_event_list_push_back(lib_evt);
    if (sc != SL_STATUS_OK) {
      // Free up memory on failure
      esl_lib_memory_free(lib_evt);
    }
  }
  return sc;
}

static sl_status_t send_bonding_data(esl_lib_connection_t *conn,
                                     uint8_t              *data)
{
  sl_status_t   sc;
  esl_lib_evt_t *lib_evt;

  sc = esl_lib_event_list_allocate(ESL_LIB_EVT_BONDING_DATA,
                                   0,
                                   &lib_evt);
  if (sc == SL_STATUS_OK) {
    lib_evt->evt_code = ESL_LIB_EVT_BONDING_DATA;
    lib_evt->data.evt_bonding_data.connection_handle
      = (esl_lib_connection_handle_t)conn;
    // Copy address
    lib_evt->data.evt_bonding_data.address.address_type
      = conn->address_type;
    memcpy(lib_evt->data.evt_bonding_data.address.addr,
           conn->address.addr,
           sizeof(conn->address.addr));
    memcpy(lib_evt->data.evt_bonding_data.ltk,
           data,
           ESL_LIB_LTK_SIZE);
    sc = esl_lib_event_list_push_back(lib_evt);
    if (sc != SL_STATUS_OK) {
      // Free up memory on failure
      esl_lib_memory_free(lib_evt);
    }
  }
  return sc;
}

static sl_status_t send_connection_status(esl_lib_connection_t *conn,
                                          esl_lib_bool_t       status,
                                          sl_status_t          reason)
{
  sl_status_t sc;
  esl_lib_evt_t *lib_evt;
  esl_lib_evt_type_t type = ESL_LIB_EVT_CONNECTION_CLOSED;

  // Detect event type (extended if connected)
  if (status == ESL_LIB_TRUE) {
    type = ESL_LIB_EVT_CONNECTION_OPENED;
  }

  sc = esl_lib_event_list_allocate(type,
                                   0,
                                   &lib_evt);
  if (sc == SL_STATUS_OK) {
    // Set event type
    lib_evt->evt_code = type;
    // Get pointer to status data in general
    if (status == ESL_LIB_TRUE) {
      // Set handle
      lib_evt->data.evt_connection_opened.connection_handle
        = (esl_lib_connection_handle_t)conn;
      // Copy address
      lib_evt->data.evt_connection_opened.address.address_type = conn->address_type;
      memcpy(lib_evt->data.evt_connection_opened.address.addr,
             conn->address.addr,
             sizeof(conn->address.addr));
      // Copy GATT database handles
      memcpy(&lib_evt->data.evt_connection_opened.gattdb_handles,
             &conn->gattdb_handles,
             sizeof(conn->gattdb_handles));
      for (uint8_t i = 0; i < sizeof(conn->gattdb_handles.esl_characteristics) / sizeof(uint16_t); i++) {
        esl_lib_log_connection_debug(CONN_FMT "Sending ESL %u characteristic handle = 0x%02x" APP_LOG_NL,
                                     conn,
                                     i,
                                     conn->gattdb_handles.esl_characteristics[i]);
      }
      for (uint8_t i = 0; i < sizeof(conn->gattdb_handles.dis_characteristics) / sizeof(uint16_t); i++) {
        esl_lib_log_connection_debug(CONN_FMT "Sending DIS %u characteristic handle = 0x%02x" APP_LOG_NL,
                                     conn,
                                     i,
                                     conn->gattdb_handles.dis_characteristics[i]);
      }
    } else {
      // Set handle
      lib_evt->data.evt_connection_closed.connection_handle
        = (esl_lib_connection_handle_t)conn;
      // Set reason for disconnection event
      lib_evt->data.evt_connection_closed.reason = reason;
      // Copy address
      lib_evt->data.evt_connection_closed.address.address_type = conn->address_type;
      memcpy(lib_evt->data.evt_connection_closed.address.addr,
             conn->address.addr,
             sizeof(conn->address.addr));
    }

    sc = esl_lib_event_list_push_back(lib_evt);
    if (sc != SL_STATUS_OK) {
      // Free up memory on failure
      esl_lib_memory_free(lib_evt);
    }
  }
  return sc;
}

static sl_status_t send_att_response(esl_lib_connection_t *conn,
                                     esl_lib_evt_type_t   type,
                                     sl_status_t          status)
{
  sl_status_t sc = SL_STATUS_NULL_POINTER;
  esl_lib_evt_t *lib_evt;

  // Stop timer
  (void)app_timer_stop(&conn->gatt_timer);

  if (type == ESL_LIB_EVT_CONFIGURE_TAG_RESPONSE) {
    sc = esl_lib_event_list_allocate(type, 0, &lib_evt);
    if (sc == SL_STATUS_OK) {
      lib_evt->evt_code = type;
      // Tag config response
      lib_evt->data.evt_configure_tag_response.connection_handle
        = (esl_lib_connection_handle_t)conn;
      lib_evt->data.evt_configure_tag_response.status = status;
      // Set current config type
      lib_evt->data.evt_configure_tag_response.type = conn->config_type;
    }
  } else if (conn->command != NULL) {
    sc = esl_lib_event_list_allocate(type,
                                     conn->command->data.cmd_write_control_point.data.len,
                                     &lib_evt);
    if (sc == SL_STATUS_OK) {
      lib_evt->evt_code = type;
      // Control Point response
      lib_evt->data.evt_control_point_response.connection_handle
        = (esl_lib_connection_handle_t)conn;
      lib_evt->data.evt_control_point_response.status = status;
      // Copy original data
      lib_evt->data.evt_control_point_response.data_sent.len
        = conn->command->data.cmd_write_control_point.data.len;
      memcpy(lib_evt->data.evt_control_point_response.data_sent.data,
             conn->command->data.cmd_write_control_point.data.data,
             conn->command->data.cmd_write_control_point.data.len);
    }
  } else {
    (void)send_connection_error(conn,
                                ESL_LIB_STATUS_CONN_WRITE_CP_FAILED,
                                sc,
                                conn->state);
  }

  // Push event
  if (sc == SL_STATUS_OK) {
    sc = esl_lib_event_list_push_back(lib_evt);
  } else {
    esl_lib_memory_free(lib_evt);
  }

  return sc;
}

static sl_status_t send_connection_error(esl_lib_connection_t        *conn,
                                         esl_lib_status_t            lib_status,
                                         sl_status_t                 status,
                                         esl_lib_connection_state_t  data)
{
  sl_status_t sc;
  esl_lib_node_id_t node_id;

  if (check_connected(conn) && conn->state != ESL_LIB_CONNECTION_STATE_PAST_CLOSE_CONNECTION) {
    node_id.type = ESL_LIB_NODE_ID_TYPE_CONNECTION;
    node_id.id.connection_handle = (esl_lib_connection_handle_t)conn;
  } else {
    node_id.type = ESL_LIB_NODE_ID_TYPE_ADDRESS;
    node_id.id.address.address_type = conn->address_type;
    memcpy(node_id.id.address.addr,
           conn->address.addr,
           sizeof(conn->address.addr));
  }

  sc = esl_lib_event_push_error(lib_status,
                                &node_id,
                                status,
                                (esl_lib_status_data_t)data);
  return sc;
}

static sl_status_t close_connection(esl_lib_connection_t *conn)
{
  sl_status_t sc;
  sc = sl_bt_connection_close(conn->connection_handle);
  return sc;
}

static bool uuid_16_match(uint8_t *uuid_a, uint8_t *uuid_b)
{
  return (memcmp(uuid_a, uuid_b, sizeof(sl_bt_uuid_16_t)) == 0);
}

static void connection_complete(esl_lib_connection_t *conn)
{
  (void)send_connection_status(conn, ESL_LIB_TRUE, SL_STATUS_OK);
  conn->state = ESL_LIB_CONNECTION_STATE_CONNECTED;
  // Open command has been completed.
  if (conn->command->cmd_code == ESL_LIB_CMD_CONNECT) {
    esl_lib_memory_free(conn->command);
  }
  conn->command_complete = true;
}

static bool check_image_transfer(esl_lib_connection_t *conn)
{
  switch (conn->state) {
    case ESL_LIB_CONNECTION_STATE_OTS_INIT:
    case ESL_LIB_CONNECTION_STATE_OTS_GET_TYPE:
    case ESL_LIB_CONNECTION_STATE_OTS_IMAGE_TRANSFER:
      return true;
    default:
      // Other cases it is connected
      return false;
  }
}

static bool check_connected(esl_lib_connection_t *conn)
{
  switch (conn->state) {
    // Not connected in connecting phases
    case ESL_LIB_CONNECTION_STATE_OFF:
    case ESL_LIB_CONNECTION_STATE_CONNECTING:
    case ESL_LIB_CONNECTION_STATE_RECONNECTING:
    case ESL_LIB_CONNECTION_STATE_APPLYING_LTK:
    case ESL_LIB_CONNECTION_STATE_NEW_BOND_REQUIRED:
    case ESL_LIB_CONNECTION_STATE_BONDING:
    case ESL_LIB_CONNECTION_STATE_BONDING_FAIL_RECONNECT:
    case ESL_LIB_CONNECTION_STATE_SERVICE_DISCOVERY:
    case ESL_LIB_CONNECTION_STATE_DIS_DISCOVERY:
    case ESL_LIB_CONNECTION_STATE_ESL_DISCOVERY:
    case ESL_LIB_CONNECTION_STATE_ESL_SUBSCRIBE:
    case ESL_LIB_CONNECTION_STATE_OTS_INIT:
      return false;
    default:
      // Other cases it is connected
      return true;
  }
}

static void on_image_transfer_status(esl_lib_image_transfer_handle_t handle,
                                     uint8_t                         connection,
                                     esl_image_transfer_state_t      state,
                                     sl_status_t                     result,
                                     esl_lib_ots_gattdb_handles_t    *gattdb_handles)
{
  (void)handle;
  esl_lib_connection_t *conn = NULL;
  sl_status_t sc = esl_lib_connection_find(connection, &conn);
  if (sc == SL_STATUS_OK) {
    if (conn->state == ESL_LIB_CONNECTION_STATE_OTS_INIT) {
      // Copy handles if present
      if (gattdb_handles != NULL) {
        memcpy(conn->gattdb_handles.ots_characteristics,
               *gattdb_handles,
               sizeof(conn->gattdb_handles.ots_characteristics));
      }

      if (state == ESL_LIB_IMAGE_TRANSFER_STATE_IDLE) {
        // init succeeded
        connection_complete(conn);
      }
    }

    if (state == ESL_LIB_IMAGE_TRANSFER_REMOVED && check_image_transfer(conn)) {
      // Removed since there were an error during init or transfer
      (void)send_connection_error(conn,
                                  ESL_LIB_STATUS_OTS_INIT_FAILED,
                                  result,
                                  conn->state);
      // Close connection as OTS errors are mostly unrecoverable
      esl_lib_log_connection_debug(CONN_FMT "Close connection due image transfer status 0x%04x, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                   conn,
                                   result,
                                   sc,
                                   conn->connection_handle);
      close_broken_connection(&conn);

      if (conn != NULL) {
        // Note that conn might have been deleted already due an error case!
        conn->command_complete = true;
      }
    }
  } else {
    esl_lib_log_connection_debug("[Unknown] Image transfer status changed for a forcibly closed connection, no handle available anymore." APP_LOG_NL);
  }
}

static void on_image_transfer_finished(esl_lib_image_transfer_handle_t handle,
                                       uint8_t                         connection,
                                       sl_status_t                     result,
                                       uint8_t                         image_index)
{
  (void)handle;
  esl_lib_connection_t *conn = NULL;
  esl_lib_evt_t        *lib_evt;

  sl_status_t sc = esl_lib_connection_find(connection, &conn);
  if (sc == SL_STATUS_OK) {
    esl_lib_log_connection_debug(CONN_FMT "Image %u transfer finished, result = %u, connection handle = %u" APP_LOG_NL,
                                 conn,
                                 image_index,
                                 result,
                                 conn->connection_handle);

    if (result == SL_STATUS_OK) {
      sc = esl_lib_event_list_allocate(ESL_LIB_EVT_IMAGE_TRANSFER_FINISHED, 0, &lib_evt);
      if (sc == SL_STATUS_OK) {
        lib_evt->evt_code = ESL_LIB_EVT_IMAGE_TRANSFER_FINISHED;
        lib_evt->data.evt_image_transfer_finished.connection_handle = conn;
        lib_evt->data.evt_image_type.img_index = image_index;
        lib_evt->data.evt_image_transfer_finished.status = result;
        (void)esl_lib_event_list_push_back(lib_evt);
      }
    } else {
      (void)send_connection_error(conn,
                                  ESL_LIB_STATUS_OTS_TRANSFER_FAILED,
                                  result,
                                  conn->state);
      esl_lib_log_connection_debug(CONN_FMT "Close connection due image transfer finished result: 0x%04x, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                   conn,
                                   result,
                                   conn->connection_handle,
                                   sc);
      if (result == SL_STATUS_TIMEOUT
          || result == SL_STATUS_NO_MORE_RESOURCE
          || result == SL_STATUS_FAIL
          || result == SL_STATUS_BT_CTRL_CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND) {
        // Close connection as some OTS errors are unrecoverable
        close_broken_connection(&conn);
      }
    }

    if (conn != NULL && conn->command != NULL) {
      // Note that conn might have been deleted already due an error case!
      // Free up image data if still there
      if (conn->command->data.cmd_write_image.img_data_copied != NULL) {
        esl_lib_memory_free(conn->command->data.cmd_write_image.img_data_copied);
      }
      conn->command_complete = true;
      conn->state = ESL_LIB_CONNECTION_STATE_CONNECTED;
    }
  }
}

static void on_image_transfer_type_arrived(esl_lib_image_transfer_handle_t handle,
                                           uint8_t                         connection,
                                           sl_status_t                     result,
                                           uint8_t                         image_index,
                                           uint8_t                         *object_type,
                                           uint8_t                         len)
{
  (void)handle;
  esl_lib_connection_t *conn = NULL;
  esl_lib_evt_t        *lib_evt;
  sl_status_t sc = esl_lib_connection_find(connection, &conn);
  if (sc == SL_STATUS_OK) {
    esl_lib_log_connection_debug(CONN_FMT "Read image %u type finished, result = %u, connection handle = %u" APP_LOG_NL,
                                 conn,
                                 image_index,
                                 result,
                                 conn->connection_handle);
    if (result == SL_STATUS_OK) {
      sc = esl_lib_event_list_allocate(ESL_LIB_EVT_IMAGE_TYPE, len, &lib_evt);
      if (sc == SL_STATUS_OK) {
        lib_evt->evt_code = ESL_LIB_EVT_IMAGE_TYPE;
        lib_evt->data.evt_image_type.connection_handle = conn;
        lib_evt->data.evt_image_type.img_index = image_index;
        lib_evt->data.evt_image_type.type_data.len = len;
        // Copy data
        memcpy(lib_evt->data.evt_image_type.type_data.data,
               object_type,
               len);
        // Push event
        (void)esl_lib_event_list_push_back(lib_evt);
      }
    } else {
      (void)send_connection_error(conn,
                                  ESL_LIB_STATUS_OTS_META_READ_FAILED,
                                  result,
                                  conn->state);
      esl_lib_log_connection_debug(CONN_FMT "Close connection due image get type fail 0x%04x, connection handle = %u, sc = 0x%04x" APP_LOG_NL,
                                   conn,
                                   result,
                                   sc,
                                   conn->connection_handle);
      // Close connection as OTS errors are mostly unrecoverable
      close_broken_connection(&conn);
    }
    if (conn != NULL) {
      // Note that conn might have been deleted already due an error case!
      conn->command_complete = true;
      conn->state = ESL_LIB_CONNECTION_STATE_CONNECTED;
    }
  }
}

static void gatt_timeout(app_timer_t *timer,
                         void        *data)
{
  (void)timer;
  esl_lib_connection_t *conn = (esl_lib_connection_t *)data;
  // Check if it exists
  if (esl_lib_connection_contains(conn)) {
    esl_lib_log_connection_error(CONN_FMT "GATT timeout, connection handle = %u" APP_LOG_NL,
                                 conn,
                                 conn->connection_handle);
    if (conn->command == NULL) {
      esl_lib_log_connection_debug(CONN_FMT "Close connection due GATT timout during discovery phase!" APP_LOG_NL, conn);
    } else if (conn->command->cmd_code == ESL_LIB_CMD_WRITE_CONTROL_POINT) {
      // Send event
      (void)send_att_response(conn,
                              ESL_LIB_EVT_CONTROL_POINT_RESPONSE,
                              SL_STATUS_TIMEOUT);
      conn->command_complete = true;
    } else if (conn->command->cmd_code == ESL_LIB_CMD_CONFIGURE_TAG) {
      // Send event
      (void)send_att_response(conn,
                              ESL_LIB_EVT_CONFIGURE_TAG_RESPONSE,
                              SL_STATUS_TIMEOUT);
      esl_lib_log_connection_debug(CONN_FMT "Close connection due GATT timout during configuring phase!" APP_LOG_NL, conn);
    }
    // Close connection as GATT errors during configuration phase are unrecoverable
    close_broken_connection(&conn);
  } else {
    esl_lib_log_connection_warning(CONN_FMT "GATT timeout for unknown connection!" APP_LOG_NL,
                                   data);
  }
}

static void reconnect_timeout(app_timer_t *timer,
                              void        *data)
{
  (void)timer;
  sl_status_t sc;
  esl_lib_connection_t *conn = (esl_lib_connection_t *)data;

  esl_lib_log_connection_debug(CONN_FMT "Reconnect timer rised" APP_LOG_NL,
                               conn);

  if (esl_lib_connection_contains(conn)) {
    esl_lib_log_connection_debug(CONN_FMT "Connection retry to " ESL_LIB_LOG_ADDR_FORMAT ", expired handle = %u" APP_LOG_NL,
                                 conn,
                                 ESL_LIB_LOG_ADDR(conn->command->data.cmd_connect.address),
                                 conn->connection_handle);
    // Resend command to core queue
    sc = esl_lib_core_add_command(conn->command);

    if (sc != SL_STATUS_OK) {
      (void)send_connection_error(conn,
                                  ESL_LIB_STATUS_CONN_FAILED,
                                  sc,
                                  conn->state);
      esl_lib_log_connection_error(CONN_FMT "Failed to reopen connection, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      // And also remove connection from the list.
      (void)esl_lib_connection_remove_ptr(conn);
      conn = NULL;
    } else {
      conn->command = NULL;
      conn->command_complete = true;
    }
  } else {
    esl_lib_log_connection_warning(CONN_FMT "Reconnect handle not found (possibly has already been removed)" APP_LOG_NL,
                                   conn);
  }
}

static void connection_timeout(app_timer_t *timer,
                               void        *data)
{
  (void)timer;
  sl_status_t sc;
  esl_lib_status_t status;
  esl_lib_connection_t *conn = (esl_lib_connection_t *)data;
  // Check if it exists
  if (esl_lib_connection_contains(conn)) {
    esl_lib_log_connection_warning(CONN_FMT "Connection timeout, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
    // Try to close the connection
    sc = close_connection(conn);
    if (sc == SL_STATUS_OK) {
      // Send timeout
      status = ESL_LIB_STATUS_CONN_TIMEOUT;
    } else {
      // Send error for closing
      status = ESL_LIB_STATUS_CONN_CLOSE_FAILED;
    }

    (void)send_connection_error(conn,
                                status,
                                SL_STATUS_TIMEOUT,
                                conn->state);

    if (conn->state == ESL_LIB_CONNECTION_STATE_CONNECTING
        || conn->state == ESL_LIB_CONNECTION_STATE_RECONNECTING) {
      esl_lib_core_connection_complete();
    }

    if (status == ESL_LIB_STATUS_CONN_CLOSE_FAILED) {
      // Remove connection
      (void)esl_lib_connection_remove_ptr(conn);
    }
  } else {
    esl_lib_log_connection_warning(CONN_FMT "Connection timeout for unknown connection" APP_LOG_NL,
                                   conn);
  }
}

static uint16_t get_handle_for_type(esl_lib_connection_t *conn,
                                    esl_lib_data_type_t  tag_info_type)
{
  uint16_t char_handle = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE;
  switch (tag_info_type) {
    case ESL_LIB_DATA_TYPE_GATT_DISPLAY_INFO:
      char_handle = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_DISPLAY_INFORMATION];
      break;
    case ESL_LIB_DATA_TYPE_GATT_IMAGE_INFO:
      char_handle = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_IMAGE_INFORMATION];
      break;
    case ESL_LIB_DATA_TYPE_GATT_SENSOR_INFO:
      char_handle = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_SENSOR_INFORMATION];
      break;
    case ESL_LIB_DATA_TYPE_GATT_LED_INFO:
      char_handle = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_LED_INFORMATION];
      break;
    case ESL_LIB_DATA_TYPE_GATT_PNP_ID:
      char_handle = conn->gattdb_handles.dis_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_DIS_PNP_ID];
      break;
    case ESL_LIB_DATA_TYPE_GATT_SERIAL_NUMBER:
      char_handle = conn->gattdb_handles.dis_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_DIS_SN];
      break;
    default:
      break;
  }
  return char_handle;
}

static esl_lib_data_type_t get_next_type(esl_lib_data_type_t type)
{
  esl_lib_data_type_t next_type = ESL_LIB_DATA_TYPE_UNINITIALIZED;
  switch (type) {
    case ESL_LIB_DATA_TYPE_UNINITIALIZED:
      next_type = ESL_LIB_DATA_TYPE_GATT_DISPLAY_INFO;
      break;
    case ESL_LIB_DATA_TYPE_GATT_DISPLAY_INFO:
      next_type = ESL_LIB_DATA_TYPE_GATT_IMAGE_INFO;
      break;
    case ESL_LIB_DATA_TYPE_GATT_IMAGE_INFO:
      next_type = ESL_LIB_DATA_TYPE_GATT_SENSOR_INFO;
      break;
    case ESL_LIB_DATA_TYPE_GATT_SENSOR_INFO:
      next_type = ESL_LIB_DATA_TYPE_GATT_LED_INFO;
      break;
    case ESL_LIB_DATA_TYPE_GATT_LED_INFO:
      next_type = ESL_LIB_DATA_TYPE_GATT_PNP_ID;
      break;
    case ESL_LIB_DATA_TYPE_GATT_PNP_ID:
      next_type = ESL_LIB_DATA_TYPE_GATT_SERIAL_NUMBER;
      break;
    case ESL_LIB_DATA_TYPE_GATT_SERIAL_NUMBER:
      next_type = ESL_LIB_DATA_TYPE_GATT_CONTROL_POINT;
      break;
    default:
      break;
  }
  return next_type;
}

static sl_status_t get_tag_info_finish(esl_lib_connection_t *conn, sl_status_t status)
{
  uint32_t data_size = 0;
  size_t current_size = 0;
  esl_lib_connection_tag_info_storage_t *current;
  esl_lib_evt_t *event;
  uint8_t *ptr;
  esl_lib_tlv_t *tlv;
  sl_status_t sc = status;

  // Stop GATT watchdog timer
  (void)app_timer_stop(&conn->gatt_timer);
  // Calculate event size from storage list
  SL_SLIST_FOR_EACH_ENTRY(conn->tag_info_list, current, esl_lib_connection_tag_info_storage_t, node) {
    // Get current size
    esl_lib_storage_get_size(current->storage, &current_size);
    // Append required size
    data_size += (current_size + ESL_LIB_TLV_HEADER_LEN);
  }

  esl_lib_log_connection_debug(CONN_FMT "Tag info TLV data size = %u , TLV header size= %u, connection handle = %u" APP_LOG_NL,
                               conn,
                               data_size,
                               (unsigned int)ESL_LIB_TLV_HEADER_LEN,
                               conn->connection_handle);

  // Create event
  esl_lib_event_list_allocate(ESL_LIB_EVT_TAG_INFO, data_size, &event);

  // Set event code
  event->evt_code = ESL_LIB_EVT_TAG_INFO;
  // Set habdke
  event->data.evt_tag_info.connection_handle = (esl_lib_connection_handle_t)conn;
  // Set size
  event->data.evt_tag_info.tlv_data.len = data_size;

  // Get pointer to the TLV data content
  ptr = event->data.evt_tag_info.tlv_data.data;

  // Compose TLVs from storages in the list
  // Iterate over the list
  while ((current = (esl_lib_connection_tag_info_storage_t *)sl_slist_pop(&conn->tag_info_list)) != NULL) {
    // TLV pointer
    tlv = (esl_lib_tlv_t *)ptr;
    // Set up type for TLV
    tlv->type = current->type;
    // Get current size
    esl_lib_storage_get_size(current->storage, &current_size);
    // Set up length for TLV
    tlv->data.len = (uint32_t)current_size;
    // Get value for TLV
    esl_lib_storage_copy(current->storage, tlv->data.data);
    // Free up storage
    esl_lib_storage_delete(&current->storage);
    // Free list item also
    esl_lib_memory_free(current);
    // Move pointer to the next TLV
    ptr += (current_size + ESL_LIB_TLV_HEADER_LEN);

    esl_lib_log_connection_debug(CONN_FMT "TLV type %u copied with data size = %u, connection handle = %u" APP_LOG_NL,
                                 conn,
                                 tlv->type,
                                 tlv->data.len,
                                 conn->connection_handle);
  }

  if (sc != SL_STATUS_OK) {
    esl_lib_log_connection_error(CONN_FMT "Get tag info finished with error status: 0x%04x, connection handle = %u" APP_LOG_NL,
                                 conn,
                                 sc,
                                 conn->connection_handle);
    // Force close as keeping connected would break the AP procedure flow
    close_broken_connection(&conn);
  } else {
    // Send event
    sc = esl_lib_event_list_push_back(event);

    if (sc == SL_STATUS_OK) {
      esl_lib_log_connection_debug(CONN_FMT "Get tag info finished, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
    } else {
      esl_lib_log_connection_error(CONN_FMT "Get tag info finished but failed to send tag info, connection handle = %u." APP_LOG_NL,
                                   conn,
                                   conn->connection_handle);
      // Force close as keeping connected would break the AP procedure flow
      close_broken_connection(&conn);
    }
  }

  if (conn != NULL) {
    // Clear type
    conn->tag_info_type = ESL_LIB_DATA_TYPE_UNINITIALIZED;

    // Set command complete
    conn->command_complete = true;
  } else {
    esl_lib_log_connection_debug("[Unknown] Get tag info finished for a forcibly closed broken connection, no handle available anymore." APP_LOG_NL);
  }

  return sc;
}

static sl_status_t get_next_tag_info(esl_lib_connection_t *conn)
{
  sl_status_t sc = SL_STATUS_OK;
  uint16_t char_handle = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE;
  esl_lib_data_type_t type = conn->tag_info_type;

  (void)app_timer_stop(&conn->gatt_timer);
  esl_lib_log_connection_debug(CONN_FMT "Get next tag info, connection handle = %u" APP_LOG_NL,
                               conn,
                               conn->connection_handle);

  // Find a valid handle for next read
  while ( !(char_handle != ESL_LIB_INVALID_CHARACTERISTIC_HANDLE
            || type == ESL_LIB_DATA_TYPE_GATT_CONTROL_POINT)) {
    type = get_next_type(type);
    char_handle = get_handle_for_type(conn, type);
    esl_lib_log_connection_debug(CONN_FMT "Next tag info type is %u (0x%02x), connection handle = %u" APP_LOG_NL,
                                 conn,
                                 type,
                                 char_handle,
                                 conn->connection_handle);
  }

  if (char_handle != ESL_LIB_INVALID_CHARACTERISTIC_HANDLE && type != ESL_LIB_DATA_TYPE_GATT_CONTROL_POINT) {
    // Found a valid handle, create storage
    sc = sl_bt_gatt_read_characteristic_value(conn->connection_handle,
                                              char_handle);
    if (sc == SL_STATUS_OK) {
      esl_lib_log_connection_debug(CONN_FMT "Next tag info type %u read requested, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   type,
                                   conn->connection_handle);
      // Move to next type
      conn->tag_info_type = type;
      // Create storage for storing data
      sc = esl_lib_storage_create(&conn->tag_info_data);

      if (sc == SL_STATUS_OK) {
        sc = app_timer_start(&conn->gatt_timer,
                             GATT_TIMEOUT_MS,
                             gatt_timeout,
                             conn,
                             false);
      }
    }
    if (sc != SL_STATUS_OK) {
      esl_lib_log_connection_error(CONN_FMT "Failed to read tag info type %u, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   type,
                                   conn->connection_handle);
      sc = get_tag_info_finish(conn, sc);
    }
  } else {
    // No valid handle found, finish
    sc = get_tag_info_finish(conn, sc);
  }

  return sc;
}

static void clean_tag_info(esl_lib_connection_t *conn)
{
  esl_lib_connection_tag_info_storage_t *current;

  // Delete temporary data
  esl_lib_storage_delete(&conn->tag_info_data);

  // Delete saved data
  while ((current = (esl_lib_connection_tag_info_storage_t *)sl_slist_pop(&conn->tag_info_list)) != NULL) {
    esl_lib_storage_delete(&current->storage);
    esl_lib_memory_free(current);
  }
}

static sl_status_t save_tag_info(esl_lib_connection_t *conn)
{
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  esl_lib_connection_tag_info_storage_t *tag_info;

  // Allocate memory for the list item
  tag_info = (esl_lib_connection_tag_info_storage_t *)esl_lib_memory_allocate(sizeof(esl_lib_connection_tag_info_storage_t));
  if (tag_info != NULL) {
    // Save type
    tag_info->type = conn->tag_info_type;
    // Save storage handle
    tag_info->storage = conn->tag_info_data;
    // Clear storage handle from connection
    conn->tag_info_data = NULL;
    // Add to the list
    sl_slist_push_back(&conn->tag_info_list, &tag_info->node);
    // Set positive result
    sc = SL_STATUS_OK;
  }
  return sc;
}

static sl_status_t write_next_config_value(esl_lib_connection_t *conn)
{
  sl_status_t sc = SL_STATUS_NULL_POINTER;

  if (conn != NULL && conn->command != NULL) {
    esl_lib_tlv_t *tlv
      = (esl_lib_tlv_t *)&conn->command->data.cmd_configure_tag.tlv_data.data[conn->config_index];

    bool move_to_next = true;

    while (move_to_next) {
      esl_lib_log_connection_debug(CONN_FMT "Next configure tag TLV data %u / %u, connection handle = %u" APP_LOG_NL,
                                   conn,
                                   conn->config_index,
                                   conn->command->data.cmd_configure_tag.tlv_data.len,
                                   conn->connection_handle);

      // Check if it was the last TLV
      if (conn->config_index >= conn->command->data.cmd_configure_tag.tlv_data.len) {
        // This was the last TLV
        move_to_next = false;
        // Consider command completed
        conn->command_complete = true;
        // Reset the state
        conn->state = ESL_LIB_CONNECTION_STATE_CONNECTED;
        sc = SL_STATUS_OK;
        esl_lib_log_connection_debug(CONN_FMT "Finished configure tag, connection handle = %u" APP_LOG_NL,
                                     conn,
                                     conn->connection_handle);
      } else {
        // Set TLV
        tlv = (esl_lib_tlv_t *)&(conn->command->data.cmd_configure_tag.tlv_data.data[conn->config_index]);

        // Set current type for the connection
        conn->config_type = tlv->type;

        esl_lib_log_connection_debug(CONN_FMT "Write next value from index %u, type %u, connection handle = %u" APP_LOG_NL,
                                     conn,
                                     conn->config_index,
                                     (uint8_t)conn->config_type,
                                     conn->connection_handle);

        // Try to write the current value
        sc = write_value(conn,
                         conn->command->data.cmd_configure_tag.att_response,
                         tlv->type,
                         tlv->data.len,
                         tlv->data.data);
        if (sc == SL_STATUS_OK) {
          // Set state or send response
          if (conn->command->data.cmd_configure_tag.att_response == ESL_LIB_TRUE) {
            // Set state, check for this later in procedure completed event
            conn->state = ESL_LIB_CONNECTION_STATE_CONFIGURE_TAG;
            // Return and wait for procedure completed event
            move_to_next = false;
            esl_lib_log_connection_debug(CONN_FMT "Wait for response to index %u, type %u, connection handle = %u" APP_LOG_NL,
                                         conn,
                                         conn->config_index,
                                         (uint8_t)conn->config_type,
                                         conn->connection_handle);
          } else {
            // Send response if written without response
            (void)send_att_response(conn,
                                    ESL_LIB_EVT_CONFIGURE_TAG_RESPONSE,
                                    sc);
          }
        } else {
          // Send back the response in case of error
          (void)send_att_response(conn,
                                  ESL_LIB_EVT_CONFIGURE_TAG_RESPONSE,
                                  sc);
        }
      }

      // Move to next TLV
      conn->config_index += (sizeof(esl_lib_tlv_t) + tlv->data.len);
    }
  }
  return sc;
}

static sl_status_t write_value(esl_lib_connection_t *conn,
                               esl_lib_bool_t       response,
                               esl_lib_data_type_t  type,
                               uint32_t             len,
                               uint8_t              *data)
{
  sl_status_t sc = SL_STATUS_INVALID_TYPE;
  uint16_t characteristic = ESL_LIB_INVALID_CHARACTERISTIC_HANDLE;
  uint16_t sent_len = 0;

  switch (type) {
    case ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS:
      characteristic = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_ADDRESS];
      break;
    case ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY:
      characteristic = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_AP_SYNC_KEY_MATERIAL];
      break;
    case ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY:
      characteristic = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_RESPONSE_KEY_MATERIAL];
      break;
    case ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME:
      characteristic = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CURRENT_ABSOLUTE_TIME];
      break;
    case ESL_LIB_DATA_TYPE_GATT_CONTROL_POINT:
      characteristic = conn->gattdb_handles.esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT];
      break;
    default:
      break;
  }
  if (characteristic != ESL_LIB_INVALID_CHARACTERISTIC_HANDLE) {
    esl_lib_log_connection_debug(CONN_FMT "Writing value type %u (0x%02x), connection handle = %u" APP_LOG_NL,
                                 conn,
                                 type,
                                 characteristic,
                                 conn->connection_handle);
    if (response == ESL_LIB_TRUE) {
      (void)app_timer_stop(&conn->gatt_timer);
      sc = app_timer_start(&conn->gatt_timer,
                           GATT_TIMEOUT_MS,
                           gatt_timeout,
                           conn,
                           false);
      if (sc == SL_STATUS_OK) {
        sc = sl_bt_gatt_write_characteristic_value(conn->connection_handle,
                                                   characteristic,
                                                   len,
                                                   data);
        if (sc != SL_STATUS_OK) {
          (void)app_timer_stop(&conn->gatt_timer);
        } else {
          esl_lib_log_connection_debug(CONN_FMT "Writing value type %u (0x%02x) succeeded, waiting for response, connection handle = %u" APP_LOG_NL,
                                       conn,
                                       type,
                                       characteristic,
                                       conn->connection_handle);
        }
      }
    } else {
      sc = sl_bt_gatt_write_characteristic_value_without_response(conn->connection_handle,
                                                                  characteristic,
                                                                  len,
                                                                  data,
                                                                  &sent_len);
      if (sc == SL_STATUS_OK) {
        esl_lib_log_connection_debug(CONN_FMT "Writing value type %u (0x%02x) succeeded, connection handle = %u" APP_LOG_NL,
                                     conn,
                                     type,
                                     characteristic,
                                     conn->connection_handle);
      }
    }
  } else {
    esl_lib_log_connection_error(CONN_FMT "Invalid GATT handle for value type %u, connection handle = %u" APP_LOG_NL,
                                 conn,
                                 type,
                                 conn->connection_handle);
    sc = SL_STATUS_INVALID_HANDLE;
  }
  return sc;
}

static bool find_tlv(esl_lib_command_list_cmd_t  *cmd,
                     esl_lib_connect_data_type_t type,
                     esl_lib_connect_tlv_t       **tlv_out)
{
  int data_index = 0;
  esl_lib_connect_tlv_t *tlv;

  if (cmd == NULL || tlv_out == NULL) {
    return false;
  }

  while (data_index < cmd->data.cmd_connect.tlv_data.len) {
    // Get TLV at data index
    tlv = (esl_lib_connect_tlv_t *)&cmd->data.cmd_connect.tlv_data.data[data_index];
    // Check type
    if (tlv->type == type) {
      // Set output pointer and return
      *tlv_out = tlv;
      return true;
    }
    // Move data index
    data_index += sizeof(esl_lib_tlv_t) + tlv->data.len;
  }

  return false;
}

static void close_broken_connection(esl_lib_connection_t **conn)
{
  if (conn == NULL || *conn == NULL || (*conn)->connection_handle == SL_BT_INVALID_CONNECTION_HANDLE) {
    // Nothing left to close (second invocation can happen on the same connection in edge cases, especially in case of various OTS errors)
    return;
  }

  sl_status_t sc = sl_bt_connection_close((*conn)->connection_handle);
  if (sc != SL_STATUS_OK) {
    esl_lib_log_connection_error(CONN_FMT "Closing request failed with status: 0x%04x on connection handle = %u during close on error" APP_LOG_NL,
                                 *conn,
                                 sc,
                                 (*conn)->connection_handle);
    // Send error event about the deletion of the connection pointer
    send_connection_status(*conn, ESL_LIB_FALSE, SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER);
    // Force removal of connection handle in case of error on sl_bt_connection_close request
    (void)esl_lib_connection_remove_ptr(*conn);
    *conn = NULL;
  } else {
    esl_lib_log_connection_debug(CONN_FMT "Requested closing connection with handle = %u on error" APP_LOG_NL,
                                 *conn,
                                 (*conn)->connection_handle);
    (void)app_timer_stop(&(*conn)->timer);
    (void)app_timer_start(&(*conn)->timer,
                          CLOSE_TIMEOUT_MS,
                          connection_timeout,
                          *conn,
                          false);
  }
}

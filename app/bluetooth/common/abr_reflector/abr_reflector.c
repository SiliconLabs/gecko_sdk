/***************************************************************************//**
 * @file
 * @brief ABR reflector
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
#include "app_log.h"
#include "abr_ras.h"
#include "abr_reflector.h"
#include "abr_reflector_connmanager.h"
#include "abr_reflector_event_buf.h"

static bool ble_advertisement_active = false;
static uint8_t advertising_set_handle = 0xff;

static bool abr_reflector_send_next_available(const uint8_t conn_handle);
static void abr_indicate_ranging_data_ready(const uint8_t conn_handle);
static void abr_reflector_find_and_send_cs_result(const uint8_t conn_handle,
                                                  const uint16_t procedure_index,
                                                  const uint16_t subevent_index);

void abr_reflector_on_bt_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates that the BT stack has booted successfully
    case sl_bt_evt_system_boot_id:
    {
      int16_t min_tx_power_x10 = ABR_REFLECTOR_MIN_TX_POWER_DBM * 10;
      int16_t max_tx_power_x10 = ABR_REFLECTOR_MAX_TX_POWER_DBM * 10;
      sc = sl_bt_system_set_tx_power(ABR_REFLECTOR_MIN_TX_POWER_DBM,
                                     ABR_REFLECTOR_MAX_TX_POWER_DBM,
                                     &min_tx_power_x10,
                                     &max_tx_power_x10);
      app_assert_status(sc);
      abr_cs_event_buf_clear();
      ble_advertisement_active = false;
    }
    break;

    // -------------------------------
    // This event indicates that a new connection was opened
    case sl_bt_evt_connection_opened_id:
    {
      uint8_t connection_handle = evt->data.evt_connection_opened.connection;
      app_log_info("#%u - Connection opened; conn_handle='%u'" APP_LOG_NL, connection_handle, connection_handle);
      sc = sl_bt_cs_set_default_settings(connection_handle,
                                         sl_bt_cs_role_status_disable,
                                         sl_bt_cs_role_status_enable,
                                         1,
                                         ABR_REFLECTOR_MAX_TX_POWER_DBM);
      app_assert_status(sc);

      // Add the new connection
      if (!abr_rcm_add_new_initiator_connection(connection_handle)) {
        // New connection cannot be added - we're at capacity - disconnect immediately
        app_log_warning("#%u - Cannot add new reflector connection, disconnecting" APP_LOG_NL, connection_handle);
        sc = sl_bt_connection_close(connection_handle);
        app_assert_status(sc);
      }

      app_log_info("Connections: %lu/%u" APP_LOG_NL,
                   abr_rcm_get_number_of_connections(),
                   ABR_REFLECTOR_MAX_CONNECTIONS);

      // If we can accept addtional connections - restart the advertisement
      ble_advertisement_active = false;
      if (abr_rcm_can_accept_new_connection()) {
        abr_reflector_restart_advertise();
      }
    }
    break;

    // -------------------------------
    // This event indicates that a CS procedure was started by the initiator
    case sl_bt_evt_cs_procedure_enable_complete_id:
    {
      uint8_t conn_handle = evt->data.evt_cs_procedure_enable_complete.connection;
      app_log_info("-------------------------------------------------------" APP_LOG_NL);
      app_log_info("#%u - CS procedure started" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that a new Channel Sounding result is available
    case sl_bt_evt_cs_result_id:
    {
      uint8_t conn_handle = evt->data.evt_cs_result.connection;
      connection_ctx_t *conn_ctx = abr_rcm_get_connection_ctx(conn_handle);
      if (conn_ctx == NULL) {
        app_log_warning("#%u - Couldn't find registered connection for handle '%u'" APP_LOG_NL,
                        conn_handle,
                        conn_handle);
        break;
      }

      uint16_t current_procedure_index = conn_ctx->current_procedure_index;
      uint16_t current_cs_subevent_index = conn_ctx->current_cs_subevent_index;
      uint16_t received_procedure_index = 0u;

      received_procedure_index = evt->data.evt_cs_result.procedure_counter;
      app_log_debug("#%u - CS procedure result; idx_original='%u'" APP_LOG_NL,
                    conn_handle, evt->data.evt_cs_result.procedure_counter);

      // Count the real procedure index (stack returns 0 for consecutive subevents)
      // If the current index is not zero and we receive a zero that means
      // that it's a consecutive event
      if (current_procedure_index != 0 && received_procedure_index == 0) {
        received_procedure_index = current_procedure_index;
      } else {
        current_procedure_index = received_procedure_index;
      }

      app_log_info("#%u - CS procedure result available; procedure_index='%u' se_idx='%u' se_done='%02x'" APP_LOG_NL,
                   conn_handle,
                   current_procedure_index,
                   current_cs_subevent_index,
                   evt->data.evt_cs_result.subevent_done_status);

      // Get a free space in the event buffer we can write
      cs_event_data_t *cs_event_buf_entry = abr_cs_event_buf_get_element_for_write();
      if (cs_event_buf_entry == NULL) {
        app_log_error("CS event buffer overflown! No more space for new events!" APP_LOG_NL);
        break;
      }

      // Get the size of the CS result data
      size_t result_len = sizeof(evt->data.evt_cs_result) + evt->data.evt_cs_result.data.len;
      // Check if we can copy the whole result data
      app_assert((result_len <= CS_EVENT_BUF_DATA_MAX_LEN),
                 "Event data exceeds the event buffer size, possible data loss, aborting; "
                 "result_len='%u' cs_event_buf_data_len='%u'",
                 result_len, CS_EVENT_BUF_DATA_MAX_LEN);

      // Copy the result to the event buffer element
      memcpy(cs_event_buf_entry->data, (uint8_t *)&evt->data.evt_cs_result, result_len);
      // Fill the rest of the results
      cs_event_buf_entry->data_len = result_len;
      cs_event_buf_entry->procedure_index = current_procedure_index;
      cs_event_buf_entry->subevent_index = current_cs_subevent_index;
      cs_event_buf_entry->empty = false;
      cs_event_buf_entry->indication_sent = false;
      cs_event_buf_entry->conn_handle = evt->data.evt_cs_result.connection;

      app_log_debug("CS event buf: %lu/%u" APP_LOG_NL,
                    ABR_REFLECTOR_CS_EVENT_BUF_SIZE - abr_cs_event_buf_get_free_space(),
                    ABR_REFLECTOR_CS_EVENT_BUF_SIZE);

      // Count the subevent in the current procedure
      if (current_procedure_index == received_procedure_index) {
        current_cs_subevent_index++;
      } else {
        current_cs_subevent_index = 0u;
      }

      conn_ctx->current_procedure_index = current_procedure_index;
      conn_ctx->current_cs_subevent_index = current_cs_subevent_index;

      abr_indicate_ranging_data_ready(conn_ctx->conn_handle);

      // If the periodic RAS Periodic Notification mode is enabled send the results immediately
      if (conn_ctx->ras_periodic_notification_mode_enabled) {
        abr_reflector_send_next_available(conn_ctx->conn_handle);
      }

      uint8_t cs_procedure_status = evt->data.evt_cs_result.procedure_done_status;
      if (cs_procedure_status == 0x00) {
        app_log_info("#%u - CS procedure finished" APP_LOG_NL, conn_handle);
      } else if (cs_procedure_status == 0x01) {
        app_log_info("#%u - CS procedure ongoing, waiting for further results..." APP_LOG_NL, conn_handle);
      } else {
        app_log_error("#%u - CS procedure failed; error='0x%02x" APP_LOG_NL, conn_handle, cs_procedure_status);
      }
    }
    break;

    // -------------------------------
    // This event indicates that a value was changed in the local GATT by a remote device
    case sl_bt_evt_gatt_server_attribute_value_id:
    {
      uint8_t conn_handle = evt->data.evt_gatt_characteristic_value.connection;
      app_log_info("#%u - Received new GATT data" APP_LOG_NL, conn_handle);

      connection_ctx_t *conn_ctx = abr_rcm_get_connection_ctx(conn_handle);
      if (conn_ctx == NULL) {
        app_log_warning("#%u - Couldn't find registered connection for handle '%u'" APP_LOG_NL,
                        conn_handle,
                        conn_handle);
        break;
      }

      // If the RAS Control Point was written
      if (evt->data.evt_gatt_characteristic_value.characteristic == gattdb_ras_control_point) {
        app_log_info("#%u - Received new RAS Control Point message" APP_LOG_NL, conn_handle);
        // Parse the incoming RAS message
        // The result - if valid - will tell the opcode and whether the
        // periodic notification mode was enabled / disabled
        ras_control_point_parse_result ras_result = abr_ras_parse_control_point_message(
          evt->data.evt_gatt_characteristic_value.value.data,
          evt->data.evt_gatt_characteristic_value.value.len);

        ras_opcode_t ras_opcode = ras_result.opcode;
        conn_ctx->ras_periodic_notification_mode_enabled = ras_result.periodic_notification_mode_set_enabled;

        // Initiator requesting a certain measurement
        // The initiator can optionally turn on the 'Periodic Notification Mode' while issuing this command
        if (ras_opcode == ABR_RAS_OPCODE_RANGING_DATA_GET_COMMAND) {
          ras_ranging_data_get_command_t rx_cmd =
            *((ras_ranging_data_get_command_t*)(evt->data.evt_gatt_characteristic_value.value.data));
          abr_reflector_find_and_send_cs_result(conn_handle, rx_cmd.procedure_index, rx_cmd.subevent_index);

          // If the RAS Periodic Notification was enabled
          if (conn_ctx->ras_periodic_notification_mode_enabled) {
            app_log_info("#%u - RAS Periodic Notification mode enabled" APP_LOG_NL, conn_handle);
            // Send out all the results we have
            while (abr_reflector_send_next_available(conn_handle)) ;
          } else {
            app_log_info("#%u - RAS Periodic Notification mode disabled" APP_LOG_NL, conn_handle);
          }
        }
      }
    }
    break;

    // -------------------------------
    // This event is received when a GATT characteristic status changes
    case sl_bt_evt_gatt_server_characteristic_status_id:
    {
      // Check for the RAS control point characteristic status changes
      if (evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_ras_control_point) {
        uint8_t conn_handle = evt->data.evt_gatt_characteristic_value.connection;
        connection_ctx_t *conn_ctx = abr_rcm_get_connection_ctx(conn_handle);
        if (conn_ctx == NULL) {
          app_log_warning("#%u - Couldn't find registered connection for handle '%u'" APP_LOG_NL,
                          conn_handle,
                          conn_handle);
          break;
        }

        if ((evt->data.evt_gatt_server_characteristic_status.client_config_flags == 0x02)
            && (evt->data.evt_gatt_server_characteristic_status.status_flags == 0x01)) {
          app_log_info("#%u - RAS control point indication enabled" APP_LOG_NL, conn_handle);
          conn_ctx->ras_control_point_indication_enabled = true;
        } else if ((evt->data.evt_gatt_server_characteristic_status.client_config_flags == 0x00)
                   && (evt->data.evt_gatt_server_characteristic_status.status_flags == 0x01)) {
          app_log_info("#%u - RAS control point indication disabled" APP_LOG_NL, conn_handle);
          conn_ctx->ras_control_point_indication_enabled = false;
        } else if (evt->data.evt_gatt_server_characteristic_status.status_flags == 0x02) {
          app_log_info("#%u - RAS control point confirmation received" APP_LOG_NL, conn_handle);
          conn_ctx->indication_in_progress = false;
          abr_indicate_ranging_data_ready(conn_handle);
        }
      }
    }
    break;

    // -------------------------------
    // This event indicates that a connection was closed
    case sl_bt_evt_connection_closed_id:
    {
      uint8_t conn_handle = evt->data.evt_connection_closed.connection;
      app_log_info("#%u - Connection closed" APP_LOG_NL, conn_handle);
      abr_rcm_remove_initiator_connection(conn_handle);
      abr_cs_event_buf_purge_data(conn_handle);
      app_log_info("Connections: %lu/%u" APP_LOG_NL,
                   abr_rcm_get_number_of_connections(),
                   ABR_REFLECTOR_MAX_CONNECTIONS);
      abr_reflector_restart_advertise();
    }
    break;

    // -------------------------------
    // This event indicates that a MTU excahnge has finished
    case sl_bt_evt_gatt_mtu_exchanged_id:
    {
      uint8_t conn_handle = evt->data.evt_gatt_mtu_exchanged.connection;
      app_log_info("#%u - MTU exchange completed" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that the connection parameters were changed
    case sl_bt_evt_connection_parameters_id:
    {
      uint8_t conn_handle = evt->data.evt_connection_parameters.connection;
      app_log_info("#%u - Connection parameters changed" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that a PHY update procedure has finished
    case sl_bt_evt_connection_phy_status_id:
    {
      uint8_t conn_handle = evt->data.evt_connection_phy_status.connection;
      app_log_info("#%u - PHY update procedure completed" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that the features supported by the remote device's LL were updated
    case sl_bt_evt_connection_remote_used_features_id:
    {
      uint8_t conn_handle = evt->data.evt_connection_remote_used_features.connection;
      app_log_info("#%u - Remote LL supported features updated" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that the maximum Rx/Tx data length was changed
    case sl_bt_evt_connection_data_length_id:
    {
      uint8_t conn_handle = evt->data.evt_connection_data_length.connection;
      app_log_info("#%u - Maximum payload length changed" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that a bonding procedure has successfully finished
    case sl_bt_evt_sm_bonded_id:
    {
      uint8_t conn_handle = evt->data.evt_sm_bonded.connection;
      app_log_info("#%u - Bonding procedure successfully completed" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that the radio transmit power was changed
    case sl_bt_evt_connection_tx_power_id:
    {
      uint8_t conn_handle = evt->data.evt_connection_tx_power.connection;
      int8_t tx_power = evt->data.evt_connection_tx_power.power_level;
      app_log_info("#%u - Transmit power changed; tx_power='%d'" APP_LOG_NL, conn_handle, tx_power);
    }
    break;

    // -------------------------------
    // This event indicates that the Channel Sounding Security Enable procedure has completed
    case sl_bt_evt_cs_security_enable_complete_id:
    {
      uint8_t conn_handle = evt->data.evt_cs_security_enable_complete.connection;
      app_log_info("#%u - CS Security Enable completed" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that the Channel Sounding configuration was completed
    case sl_bt_evt_cs_config_complete_id:
    {
      uint8_t conn_handle = evt->data.evt_cs_config_complete.connection;
      app_log_info("#%u - CS configuration completed" APP_LOG_NL, conn_handle);
    }
    break;

    // -------------------------------
    // This event indicates that the BT stack buffer resources were exhausted
    case sl_bt_evt_system_resource_exhausted_id:
    {
      uint8_t num_buffers_discarded = evt->data.evt_system_resource_exhausted.num_buffers_discarded;
      uint8_t num_buffer_allocation_failures = evt->data.evt_system_resource_exhausted.num_buffer_allocation_failures;
      uint8_t num_heap_allocation_failures = evt->data.evt_system_resource_exhausted.num_heap_allocation_failures;
      app_log_error("BT stack buffers exhausted, data loss may have occurred! "
                    "buf_discarded='%u' buf_alloc_fail='%u' heap_alloc_fail='%u'" APP_LOG_NL,
                    num_buffers_discarded,
                    num_buffer_allocation_failures,
                    num_heap_allocation_failures);
    }
    break;

    // -------------------------------
    // This event is received when a BT stack system error occurs
    case sl_bt_evt_system_error_id:
      app_log_error("System error occurred; reason='0x%02x'" APP_LOG_NL, evt->data.evt_system_error.reason);
      break;

    // -------------------------------
    // This event is received when a bonding procedure fails
    case sl_bt_evt_sm_bonding_failed_id:
    {
      uint8_t conn_handle = evt->data.evt_sm_bonding_failed.connection;
      app_log_error("#%d - Bonding failed; reason='0x%02x'" APP_LOG_NL,
                    conn_handle,
                    evt->data.evt_sm_bonding_failed.reason);
      sc = sl_bt_connection_close(conn_handle);
      app_assert_status(sc);
    }
    break;

    // -------------------------------
    // This event is received when an advertisement times out
    case sl_bt_evt_advertiser_timeout_id:
      ble_advertisement_active = false;
      app_log_info("Advertisement timed out" APP_LOG_NL);
      break;

    // -------------------------------
    // Default event handler
    default:
      app_log_info("BLE event: 0x%02lx" APP_LOG_NL, SL_BT_MSG_ID(evt->header));
      break;
  }
}

// Finds the next available CS result and sends it to the initiator
static bool abr_reflector_send_next_available(const uint8_t conn_handle)
{
  cs_event_data_t *cs_event_buf_entry = abr_cs_event_buf_get_next_element(conn_handle);
  if (cs_event_buf_entry == NULL) {
    app_log_warning("#%u - No results left to transfer for this connection" APP_LOG_NL, conn_handle);
    return false;
  }

  app_log_info("#%u - Transferring next CS result to the initiator; index='%u' subevent_index='%u' len='%u'" APP_LOG_NL,
               conn_handle,
               cs_event_buf_entry->procedure_index,
               cs_event_buf_entry->subevent_index,
               cs_event_buf_entry->data_len);

  struct sl_bt_evt_cs_result_s* result_ptr = (struct sl_bt_evt_cs_result_s*)cs_event_buf_entry->data;
  app_log_info("#%u - CS packet details; proc_cnt='%u' proc_done='%u' se_done='%u' len='%u'" APP_LOG_NL,
               conn_handle,
               result_ptr->procedure_counter,
               result_ptr->procedure_done_status,
               result_ptr->subevent_done_status,
               cs_event_buf_entry->data_len);

  sl_status_t sc = sl_bt_gatt_server_send_notification(conn_handle,
                                                       gattdb_ras_subevent_ranging_data,
                                                       cs_event_buf_entry->data_len,
                                                       cs_event_buf_entry->data);
  // Give warning that we couldn't transfer the data
  // Data will be discarded anyways
  if (sc != SL_STATUS_OK) {
    app_log_warning("#%u - Cannot transfer CS result, discarding; idx='%u' sc='0x%02lx'" APP_LOG_NL,
                    conn_handle,
                    cs_event_buf_entry->procedure_index,
                    sc);
  }
  // Mark the event buffer element as consumed
  cs_event_buf_entry->empty = true;
  return true;
}

// Finds and sends the requested CS result (if available) to the initiator
static void abr_reflector_find_and_send_cs_result(const uint8_t conn_handle,
                                                  const uint16_t procedure_index,
                                                  const uint16_t subevent_index)
{
  cs_event_data_t *cs_event_buf_entry = abr_cs_event_buf_find(conn_handle, procedure_index, subevent_index);
  if (cs_event_buf_entry == NULL) {
    app_log_warning("#%u - Requested CS result cannot be found; index='%u' subevent_index='%u'" APP_LOG_NL,
                    conn_handle, procedure_index, subevent_index);
    return;
  }

  app_log_info("#%u - Transferring CS result to the initiator; index='%u' subevent_index='%u'" APP_LOG_NL,
               conn_handle,
               procedure_index,
               subevent_index);
  sl_status_t sc = sl_bt_gatt_server_send_notification(conn_handle,
                                                       gattdb_ras_subevent_ranging_data,
                                                       cs_event_buf_entry->data_len,
                                                       cs_event_buf_entry->data);
  app_assert_status(sc);
  // Mark the event buffer element as consumed
  cs_event_buf_entry->empty = true;
}

// Looks for the first result we haven't sent an indication about and sends it
void abr_indicate_ranging_data_ready(const uint8_t conn_handle)
{
  connection_ctx_t *conn_ctx = abr_rcm_get_connection_ctx(conn_handle);
  if (conn_ctx == NULL) {
    app_log_warning("#%u - Couldn't find registered connection for handle '%u'" APP_LOG_NL, conn_handle, conn_handle);
    return;
  }
  // If the RAS Control Point notifications/indications are enabled and not busy,
  // and the RAS Periodic Notification was not requested
  if (!conn_ctx->ras_control_point_indication_enabled
      || conn_ctx->indication_in_progress
      || conn_ctx->ras_periodic_notification_mode_enabled) {
    return;
  }

  // Get the next result we haven't indicated about
  cs_event_data_t *current_event = abr_cs_event_buf_get_next_unindicated(conn_handle);
  // Return if there's no result we haven't indicated about
  if (current_event == NULL) {
    return;
  }

  // Prepare the indication data
  ras_ranging_data_ready_indication_t cmd;
  cmd.opcode = ABR_RAS_OPCODE_RANGING_DATA_READY_INDICATION;
  cmd.procedure_index = current_event->procedure_index;
  cmd.number_of_subevents = 1u;
  cmd.subevent_index = current_event->subevent_index;
  cmd.subevent_index_data_size = current_event->data_len;
  app_log_info("#%u - Sending RAS Ranging Data Ready indication; "
               "index='%u' num_se='%u' se_idx='%u' size='%u'" APP_LOG_NL,
               conn_handle,
               cmd.procedure_index,
               cmd.number_of_subevents,
               cmd.subevent_index,
               cmd.subevent_index_data_size);

  // Send the notification
  sl_status_t sc = sl_bt_gatt_server_send_indication(conn_handle, gattdb_ras_control_point,
                                                     sizeof(ras_ranging_data_ready_indication_t),
                                                     (uint8_t*)&cmd);
  if (sc != SL_STATUS_OK) {
    app_log_warning("#%u - Failed to send RAS Ranging Data Ready indication" APP_LOG_NL, conn_handle);
  } else {
    current_event->indication_sent = true;
    conn_ctx->indication_in_progress = true;
  }
}

void abr_reflector_advertise(void)
{
  sl_status_t sc;

  // Stop running advertising
  sl_bt_advertiser_stop(advertising_set_handle);
  // Delete advertiser set
  sl_bt_advertiser_delete_set(advertising_set_handle);

  sc = sl_bt_advertiser_create_set(&advertising_set_handle);
  app_assert_status(sc);

  // Generate data for advertising
  sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                             sl_bt_advertiser_general_discoverable);
  app_assert_status(sc);

  // Set advertising interval to 100ms
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
  if (ble_advertisement_active) {
    app_log_info("Advertisement already active..." APP_LOG_NL);
    return;
  }

  // Start advertising and enable connections
  sl_status_t sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                                 sl_bt_legacy_advertiser_connectable);
  app_assert_status(sc);
  ble_advertisement_active = true;
  app_log_info("Started advertising..." APP_LOG_NL);
}

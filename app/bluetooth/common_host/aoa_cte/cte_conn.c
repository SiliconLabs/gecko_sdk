/***************************************************************************//**
 * @file
 * @brief Bluetooth event handler for Connection CTE mode.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "aoa_cte.h"
#include "aoa_util.h"
#include "aoa_cte_config.h"

// Module shared variables.
extern uint8_t cte_switch_pattern[ANTENNA_ARRAY_MAX_PIN_PATTERN_SIZE];
extern uint8_t cte_switch_pattern_size;

// connection parameters
#define CONN_INTERVAL_MIN 80     //100ms
#define CONN_INTERVAL_MAX 80     //100ms
#define CONN_RESPONDER_LATENCY 0 //no latency
#define CONN_TIMEOUT 100         //1000ms
#define CONN_MIN_CE_LENGTH 0
#define CONN_MAX_CE_LENGTH 0xffff

#define CTE_TYPE_AOA 0

// UUIDs defined by Bluetooth SIG
static const uint8_t cte_service[] = { 0x4A, 0x18 };
static const uint8_t cte_enable_char[] = { 0xAD, 0x2B };

/**************************************************************************//**
 * CTE specific Bluetooth event handler.
 *****************************************************************************/
sl_status_t cte_bt_on_event_conn(sl_bt_msg_t *evt)
{
  sl_status_t sc = SL_STATUS_OK;
  aoa_db_entry_t *tag;
  uint8_t data;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      // Set passive scanning on 1Mb PHY
      sc = sl_bt_scanner_set_mode(sl_bt_gap_1m_phy, AOA_CTE_SCAN_MODE);
      if (SL_STATUS_OK != sc) {
        break;
      }

      // Set scan interval and scan window
      sc = sl_bt_scanner_set_timing(sl_bt_gap_1m_phy, AOA_CTE_SCAN_INTERVAL, AOA_CTE_SCAN_WINDOW);
      if (SL_STATUS_OK != sc) {
        break;
      }

      // Set the default connection parameters for subsequent connections
      sc = sl_bt_connection_set_default_parameters(CONN_INTERVAL_MIN,
                                                   CONN_INTERVAL_MAX,
                                                   CONN_RESPONDER_LATENCY,
                                                   CONN_TIMEOUT,
                                                   CONN_MIN_CE_LENGTH,
                                                   CONN_MAX_CE_LENGTH);
      if (SL_STATUS_OK != sc) {
        break;
      }

      // Start scanning - looking for tags
      sc = sl_bt_scanner_start(sl_bt_gap_1m_phy, sl_bt_scanner_discover_generic);
      break;

    case sl_bt_evt_scanner_scan_report_id:
      // Check if the tag is allowlisted
      if (SL_STATUS_NOT_FOUND == aoa_db_allowlist_find(evt->data.evt_scanner_scan_report.address.addr)) {
        // Tag is not on the allowlist, ignoring. Not an error.
        break;
      }

      // Check for connectable advertising type
      if ((evt->data.evt_scanner_scan_report.packet_type & 0x06) != 0x0) {
        break;
      }
      // If a CTE service is found...
      if (find_service_in_advertisement(evt->data.evt_scanner_scan_report.data.data,
                                        evt->data.evt_scanner_scan_report.data.len,
                                        cte_service,
                                        sizeof(cte_service))) {
        sc = aoa_db_get_tag_by_address(&evt->data.evt_scanner_scan_report.address, &tag);
        if (sc == SL_STATUS_NOT_FOUND) {
          uint8_t conn_handle;
          sc = sl_bt_connection_open(evt->data.evt_scanner_scan_report.address,
                                     evt->data.evt_scanner_scan_report.address_type,
                                     sl_bt_gap_1m_phy, &conn_handle);
          if (SL_STATUS_INVALID_STATE == sc) {
            // The maximum number of connections have been reached, continue execution.
            sc = SL_STATUS_OK;
          }
        }
      }
      break;

    case sl_bt_evt_connection_opened_id:
      // Add connection to the connection_properties array
      sc = aoa_db_add_tag((uint16_t)evt->data.evt_connection_opened.connection,
                          &evt->data.evt_connection_opened.address,
                          evt->data.evt_connection_opened.address_type,
                          &tag);
      if (SL_STATUS_OK != sc) {
        break;
      }
      // Discover CTE service on the responder device
      sc = sl_bt_gatt_discover_primary_services_by_uuid(evt->data.evt_connection_opened.connection,
                                                        sizeof(cte_service),
                                                        cte_service);
      break;
    // This event is generated when a new service is discovered
    case sl_bt_evt_gatt_service_id:
      // Find connection
      if (aoa_db_get_tag_by_handle(evt->data.evt_gatt_service.connection, &tag) == SL_STATUS_NOT_FOUND) {
        break;
      }
      // Save service handle for future reference
      if (memcmp(evt->data.evt_gatt_service.uuid.data,
                 cte_service,
                 sizeof(cte_service)) == 0) {
        tag->cte_service_handle = evt->data.evt_gatt_service.service;
      }
      break;

    // This event is generated when a new characteristic is discovered
    case sl_bt_evt_gatt_characteristic_id:
      // Find connection
      if (aoa_db_get_tag_by_handle(evt->data.evt_gatt_characteristic.connection, &tag) == SL_STATUS_NOT_FOUND) {
        break;
      }
      // Save characteristic handle for future reference
      if (memcmp(evt->data.evt_gatt_characteristic.uuid.data,
                 cte_enable_char,
                 sizeof(cte_enable_char)) == 0) {
        tag->cte_enable_char_handle = evt->data.evt_gatt_characteristic.characteristic;
      }
      tag->connection_state = DISCOVER_CHARACTERISTICS;
      break;

    // This event is generated for various procedure completions, e.g. when a
    // write procedure is completed, or service discovery is completed
    case sl_bt_evt_gatt_procedure_completed_id:
      // Find connection
      if (aoa_db_get_tag_by_handle(evt->data.evt_gatt_procedure_completed.connection, &tag) == SL_STATUS_NOT_FOUND) {
        break;
      }

      switch (tag->connection_state) {
        // If service discovery finished
        case DISCOVER_SERVICES:
          // Discover CTE enable characteristic on the responder device
          sc = sl_bt_gatt_discover_characteristics_by_uuid(evt->data.evt_gatt_procedure_completed.connection,
                                                           tag->cte_service_handle,
                                                           sizeof(cte_enable_char),
                                                           cte_enable_char);
          break;
        // If characteristic discovery finished
        case DISCOVER_CHARACTERISTICS:
          data = 0x01;
          // enable CTE on responder device (by writing 0x01 into the CTE enable characteristic)
          sc = sl_bt_gatt_write_characteristic_value(evt->data.evt_gatt_procedure_completed.connection,
                                                     tag->cte_enable_char_handle,
                                                     1,
                                                     &data);
          if (SL_STATUS_OK != sc) {
            break;
          }
          tag->connection_state = ENABLE_CTE;
          break;
        case ENABLE_CTE:
          // If CTE was enabled
          // The tag has started sending CTE packets. Start IQ sampling on the receiver side
          sc = sl_bt_cte_receiver_enable_connection_cte(evt->data.evt_gatt_procedure_completed.connection,
                                                        aoa_cte_config.cte_sampling_interval,
                                                        aoa_cte_config.cte_min_length,
                                                        CTE_TYPE_AOA,
                                                        aoa_cte_config.cte_slot_duration,
                                                        cte_switch_pattern_size,
                                                        cte_switch_pattern);
          if (SL_STATUS_OK != sc) {
            break;
          }
          // Restart the scanner to discover new tags
          sc = sl_bt_scanner_start(sl_bt_gap_1m_phy, sl_bt_scanner_discover_generic);
          if (SL_STATUS_INVALID_STATE == sc) {
            // Scanning is already running, continue execution.
            sc = SL_STATUS_OK;
          }

          if (SL_STATUS_OK != sc) {
            // Failed to start scanner
            break;
          }
          tag->connection_state = RUNNING;
          break;
        default:
          break;
      }
      break;
    // This event is generated when a connection is dropped
    case sl_bt_evt_connection_closed_id:
      // Remove connection from active connections
      aoa_db_remove_tag((uint16_t)evt->data.evt_connection_closed.connection);

      // Restart the scanner to discover new tags
      sc = sl_bt_scanner_start(sl_bt_gap_1m_phy, sl_bt_scanner_discover_generic);

      if (SL_STATUS_INVALID_STATE == sc) {
        // Scanning is already running, continue execution.
        sc = SL_STATUS_OK;
      }
      break;
    case sl_bt_evt_cte_receiver_connection_iq_report_id:
    {
      aoa_iq_report_t iq_report;

      if (evt->data.evt_cte_receiver_connection_iq_report.samples.len == 0) {
        // Nothing to be processed.
        break;
      }

      // Check if asset tag is known.
      if (aoa_db_get_tag_by_handle(evt->data.evt_cte_receiver_connection_iq_report.connection, &tag) == SL_STATUS_NOT_FOUND) {
        // Unknown tag, proceed with execution.
        break;
      }

      // Convert event to common IQ report format.
      iq_report.channel = evt->data.evt_cte_receiver_connection_iq_report.channel;
      iq_report.rssi = evt->data.evt_cte_receiver_connection_iq_report.rssi;
      iq_report.event_counter = evt->data.evt_cte_receiver_connection_iq_report.event_counter;
      iq_report.length = evt->data.evt_cte_receiver_connection_iq_report.samples.len;
      iq_report.samples = (int8_t *)evt->data.evt_cte_receiver_connection_iq_report.samples.data;

      aoa_cte_on_iq_report(tag, &iq_report);
    }
    break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }

  return sc;
}

/***************************************************************************//**
 * @file
 * @brief Bluetooth event handler for Connectionless CTE mode.
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

// UUID defined by Bluetooth SIG
static const uint8_t cte_service[] = { 0x4A, 0x18 };

/**************************************************************************//**
 * CTE specific Bluetooth event handler.
 *****************************************************************************/
sl_status_t cte_bt_on_event_conn_less(sl_bt_msg_t *evt)
{
  sl_status_t sc = SL_STATUS_OK;
  aoa_db_entry_t *tag;

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

      // Start scanning - looking for tags
      sc = sl_bt_scanner_start(sl_bt_gap_1m_phy, sl_bt_scanner_discover_observation);
      break;
    case sl_bt_evt_scanner_scan_report_id:
    {
      // Check if the tag is allowlisted
      if (SL_STATUS_NOT_FOUND == aoa_db_allowlist_find(evt->data.evt_scanner_scan_report.address.addr)) {
        // Tag is not on the allowlist, ignoring. Not an error.
        break;
      }

      // Parse extended advertisement packets
      if (evt->data.evt_scanner_scan_report.packet_type & 0x80) {
        // If a CTE service is found...
        uint16_t sync_handle;
        if (find_service_in_advertisement(evt->data.evt_scanner_scan_report.data.data,
                                          evt->data.evt_scanner_scan_report.data.len,
                                          cte_service,
                                          sizeof(cte_service))) {
          // ...then sync on the periodic advertisement
          sc = sl_bt_sync_open(evt->data.evt_scanner_scan_report.address,
                               evt->data.evt_scanner_scan_report.address_type,
                               evt->data.evt_scanner_scan_report.adv_sid,
                               &sync_handle);
          if (SL_STATUS_OK != sc) {
            //Failed to synchronize to tag
            break;
          }
          sc = aoa_db_get_tag_by_handle(sync_handle, &tag);
          if (sc == SL_STATUS_NOT_FOUND) {
            sc = aoa_db_add_tag(sync_handle,
                                &evt->data.evt_scanner_scan_report.address,
                                evt->data.evt_scanner_scan_report.address_type,
                                &tag);
          }
        }
      }
      break;
    }
    case sl_bt_evt_sync_opened_id:
      // Stop scanning
      sc = sl_bt_scanner_stop();
      if ((SL_STATUS_OK != sc) && (SL_STATUS_INVALID_STATE != sc)) {
        break;
      }

      // Start listening CTE on extended advertisements
      sc = sl_bt_cte_receiver_enable_connectionless_cte(evt->data.evt_sync_opened.sync,
                                                        aoa_cte_config.cte_slot_duration,
                                                        aoa_cte_config.cte_count,
                                                        cte_switch_pattern_size,
                                                        cte_switch_pattern);
      if (SL_STATUS_OK != sc) {
        break;
      }

      // Start scanning again for new devices
      sc = sl_bt_scanner_start(sl_bt_gap_1m_phy, sl_bt_scanner_discover_generic);
      if (SL_STATUS_INVALID_STATE == sc) {
        // Scanning is already running, continue execution.
        sc = SL_STATUS_OK;
      }

      break;
    case sl_bt_evt_sync_closed_id:
      aoa_db_remove_tag(evt->data.evt_cte_receiver_connectionless_iq_report.sync);
      // Start scanning again to find new devices
      sc = sl_bt_scanner_start(sl_bt_gap_1m_phy, sl_bt_scanner_discover_generic);
      if (SL_STATUS_INVALID_STATE == sc) {
        // Scanning is already running, continue execution.
        sc = SL_STATUS_OK;
      }

      break;
    case sl_bt_evt_cte_receiver_connectionless_iq_report_id:
    {
      aoa_iq_report_t iq_report;

      if (evt->data.evt_cte_receiver_connectionless_iq_report.samples.len == 0) {
        // Nothing to be processed.
        break;
      }
      // Check if asset tag is known.
      if (aoa_db_get_tag_by_handle(evt->data.evt_cte_receiver_connectionless_iq_report.sync, &tag) == SL_STATUS_NOT_FOUND) {
        // Unknown tag, proceed with execution.
        break;
      }
      // Convert event to common IQ report format.
      iq_report.channel = evt->data.evt_cte_receiver_connectionless_iq_report.channel;
      iq_report.rssi = evt->data.evt_cte_receiver_connectionless_iq_report.rssi;
      iq_report.event_counter = evt->data.evt_cte_receiver_connectionless_iq_report.event_counter;
      iq_report.length = evt->data.evt_cte_receiver_connectionless_iq_report.samples.len;
      iq_report.samples = (int8_t *)evt->data.evt_cte_receiver_connectionless_iq_report.samples.data;

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

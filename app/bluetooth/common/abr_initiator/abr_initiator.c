/*******************************************************************************
 * @file
 * @brief ABR initiator
 *******************************************************************************
 * # License
 * <b>Copyright 2022-2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "sl_bt_api.h"
#include "sl_common.h"
#include "abr_initiator.h"
#include "app_log.h"
#include "app_assert.h"
#include "abr_cs_parser.h"
#include "abr_initiator_interface.h"
#include "abr_initiator_config.h"

#include "sl_rtl_clib_api.h"

/// Discovering services/characteristics and subscribing raises procedure_complete events
/// Actions are used to indicate which procedure was completed.
typedef enum {
  act_none = 0,
  act_discover_service,
  act_discover_characteristics,
  act_subscribe_result
} action_t;

static abr_initiator_config_t *initiator_config;
static const char *device_name = INITIATOR_DEVICE_NAME; // Device name to match against scan results.

static bool characteristic_found;
static sl_bt_cs_channel_map_t channel_map;

static uint8_t connection_handle = SL_BT_INVALID_CONNECTION_HANDLE;
static uint32_t service_handle = 0xFFFFFFFF;
static uint16_t result_handle = 0xFFFF;
static action_t action = act_none;

// bbb99e70-fff7-46cf-abc7-2d32c71820f2
const uint8_t service_uuid[] = INITIATOR_SERVICE_UUID;

// 929f95ec-1391-4303-9b49-3c22a418be91
const uint8_t result_characteristic_uuid[] = INITIATOR_CHARACTERISTIC_UUID;

static bool initiator_process_scan_response(sl_bt_evt_scanner_scan_report_t *response);
static void initiator_scanning_start(void);
static void check_characteristic_uuid(sl_bt_msg_t *evt);
static void process_procedure_complete_event(sl_bt_msg_t *evt);
static void initiator_calculate_distance(uint8_t connection);
static void abr_initiator_perform_procedure(void);
static void abr_initiator_create_config(void);
static void rtl_library_init(sl_rtl_abr_libitem *handle, uint8_t abr_mode);

#ifdef DEBUG_MODE
FILE *initiator_statistics_file, *reflector_statistics_file;
struct timespec bt_event_timestamp;
#endif

/******************************************************************************
 * ABR initiator set initial config.
 *****************************************************************************/
void abr_initiator_set_initial_state(abr_initiator_config_t *config)
{
  initiator_config = config;
  initiator_config->discovery_state = ABR_DISCOVERY_STATE_IDLE;
}

/******************************************************************************
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *****************************************************************************/
void bt_on_event_initiator(sl_bt_msg_t *evt)
{
  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_scanner_scan_report_id:
      if (initiator_process_scan_response(&(evt->data.evt_scanner_scan_report))) {
        // Stop scanning
        sc = sl_bt_scanner_stop();
        app_assert_status(sc);

        initiator_config->discovery_state = ABR_DISCOVERY_STATE_CONN;

        if (initiator_config->phy != sl_bt_gap_phy_coding_1m_uncoded) {
          app_log_warning("Connection PHY is not supported and set to 1M PHY" APP_LOG_NL);
          initiator_config->phy = sl_bt_gap_phy_coding_1m_uncoded;
        }

        if (connection_handle == SL_BT_INVALID_CONNECTION_HANDLE) {
          app_log_info("Opening connection to Reflector" APP_LOG_NL);
          sc = sl_bt_connection_open(evt->data.evt_scanner_scan_report.address,
                                     evt->data.evt_scanner_scan_report.address_type,
                                     initiator_config->phy,
                                     &connection_handle);
          app_assert_status(sc);
        }
      } else {
        waiting_indication();
      }
      break;
    case sl_bt_evt_connection_opened_id:
      app_log_info("Connection opened to the Reflector" APP_LOG_NL);
      platform_display_state(ABR_STATE_CONNECTED);
      //Encrypt link
      app_log_info("Encrypting connection" APP_LOG_NL);
      sc = sl_bt_sm_increase_security(connection_handle);
      app_assert_status(sc);

      // Request connection parameter update.
      sc = sl_bt_connection_set_parameters(connection_handle,
                                           initiator_config->min_connection_interval,
                                           initiator_config->max_connection_interval,
                                           initiator_config->latency,
                                           initiator_config->timeout,
                                           initiator_config->min_ce_length,
                                           initiator_config->max_ce_length);

      app_assert_status(sc);

      break;
    case sl_bt_evt_connection_parameters_id:
      if (evt->data.evt_connection_parameters.security_mode == 1) {
        app_log_info("Connection encrypted" APP_LOG_NL);
        sc = sl_bt_gatt_discover_primary_services_by_uuid(connection_handle,
                                                          UUID_LEN,
                                                          service_uuid);
        app_assert_status(sc);
        characteristic_found = false;
      }
      break;
    case sl_bt_evt_gatt_procedure_completed_id:
      process_procedure_complete_event(evt);
      break;
    case sl_bt_evt_gatt_characteristic_id:
      check_characteristic_uuid(evt);
      break;
    case sl_bt_evt_gatt_service_id:
      if (evt->data.evt_gatt_service.uuid.len == UUID_LEN) {
        if (memcmp(service_uuid, evt->data.evt_gatt_service.uuid.data, UUID_LEN) == 0) {
          service_handle = evt->data.evt_gatt_service.service;
          action = act_discover_service;
          app_log_info("Service found" APP_LOG_NL);
        }
      }
      break;
    case sl_bt_evt_gatt_characteristic_value_id:
      app_log_debug("Received new measurement data from the reflector" APP_LOG_NL);

#ifdef DEBUG_MODE
      reflector_statistics_file = fopen("reflector_stats.txt", "w");
      app_assert(reflector_statistics_file != NULL, "Failed opening file");
      clock_gettime(CLOCK_MONOTONIC, &bt_event_timestamp);
      fprintf(reflector_statistics_file, "%li:%li %s\n", bt_event_timestamp.tv_sec, bt_event_timestamp.tv_nsec, "new result");
      fclose(reflector_statistics_file);
#endif

      if (evt->data.evt_gatt_characteristic_value.att_opcode == gatt_handle_value_indication) {
        // Reflector sends indication about result after each test. Data is uint8array LSB first.

        sc = sl_bt_gatt_send_characteristic_confirmation(evt->data.evt_gatt_characteristic_value.connection);
        app_assert_status(sc);

        app_log_debug("Reflector packet %hhu" APP_LOG_NL, evt->data.evt_gatt_characteristic_value.value.len);

        struct sl_bt_evt_cs_result_s* result_ptr = (struct sl_bt_evt_cs_result_s*)evt->data.evt_gatt_characteristic_value.value.data;

        sl_status_t parse_status = abr_cs_parser_parse_event_result_data(result_ptr,
                                                                         ABR_DEVICE_REFLECTOR);
        if (parse_status != SL_STATUS_OK) {
          app_log_info("Incorrect cs_event_result reflector" APP_LOG_NL);
        }

        initiator_calculate_distance(result_ptr->connection);

        if (abr_cs_parser_procedure_restart_needed(result_ptr->connection)) {
          abr_initiator_perform_procedure();
        }
      }
      break;
    case  sl_bt_evt_cs_procedure_enable_complete_id:
      app_log_debug("Procedure enable complete" APP_LOG_NL);
      break;
    case sl_bt_evt_cs_config_complete_id:
      app_log_info("Config created" APP_LOG_NL);
      abr_initiator_perform_procedure();
      break;
    case sl_bt_evt_cs_result_id:
      app_log_debug("Initiator packet %hhu" APP_LOG_NL, evt->data.evt_cs_result.data.len);

#ifdef DEBUG_MODE
      initiator_statistics_file = fopen("initiator_stats.txt", "w");
      app_assert(initiator_statistics_file != NULL, "Failed opening file");
      clock_gettime(CLOCK_MONOTONIC, &bt_event_timestamp);
      fprintf(initiator_statistics_file, "%li:%li %s\n", bt_event_timestamp.tv_sec, bt_event_timestamp.tv_nsec, "new result");
      fclose(initiator_statistics_file);
#endif

      sl_status_t parse_status = abr_cs_parser_parse_event_result_data(&evt->data.evt_cs_result,
                                                                       ABR_DEVICE_INITIATOR);
      if (parse_status != SL_STATUS_OK) {
        app_log_info("Incorrect cs_event_result initiator" APP_LOG_NL);
      }

      initiator_calculate_distance(evt->data.evt_cs_result.connection);

      if (abr_cs_parser_procedure_restart_needed(evt->data.evt_cs_result.connection)) {
        abr_initiator_perform_procedure();
      }

      break;
    case sl_bt_evt_connection_closed_id:
      initiator_config->discovery_state = ABR_DISCOVERY_STATE_IDLE;

      uint16_t reason = evt->data.evt_connection_closed.reason;
      app_log_info("Connection closed to the Reflector %02X" APP_LOG_NL, reason);
      platform_display_state(ABR_STATE_DISCONNECTED);
      connection_handle = SL_BT_INVALID_CONNECTION_HANDLE;
#ifdef DEBUG_MODE
      char log_message[100];
      sprintf(log_message, "Connection closed to the Reflector %02X", reason);
      add_debug_message(log_message);
#endif
      initiator_scanning_start();
      break;
    default:
      break;
  }
}

/******************************************************************************
 * ABR initiator create channel-sounding and radio configuration.
 *****************************************************************************/
static void abr_initiator_create_config(void)
{
  sl_status_t sc;

  app_log_info("Creating ABR config..." APP_LOG_NL);

  memset(channel_map.data, 0x55, 10);

  // Set role
  sc = sl_bt_cs_set_default_settings(connection_handle,
                                     sl_bt_cs_role_status_enable,
                                     sl_bt_cs_role_status_disable,
                                     initiator_config->cs_sync_antenna,
                                     initiator_config->max_tx_power_dbm);
  app_assert_status(sc);

  // Enable security.
  sc = sl_bt_cs_security_enable(connection_handle);
  app_assert_status(sc);

  sc = sl_bt_cs_create_config(connection_handle,
                              initiator_config->config_id,
                              initiator_config->create_context,
                              initiator_config->mode,
                              initiator_config->submode,
                              initiator_config->min_main_mode_steps,
                              initiator_config->max_main_mode_steps,
                              initiator_config->main_mode_repetition,
                              initiator_config->mode0_step,
                              sl_bt_cs_role_initiator,
                              initiator_config->rtt_type,
                              initiator_config->phy,
                              &channel_map,
                              initiator_config->channel_map_repetition,
                              initiator_config->channel_selection_type,
                              initiator_config->ch3c_shape,
                              initiator_config->ch3c_jump,
                              initiator_config->companion_signal_enable);
  app_assert_status(sc);

  sc = abr_cs_parser_configure(channel_map.data,
                               sizeof(channel_map.data) / sizeof(channel_map.data[0]),
                               initiator_config->mode0_step);
  app_assert_status(sc);
}

/******************************************************************************
 * ABR initiator trigger channel-sounding procedure
 *****************************************************************************/
static void abr_initiator_perform_procedure(void)
{
  sl_status_t sc;

  app_log_debug("Starting CS measurement..." APP_LOG_NL);
  sc = sl_bt_cs_set_procedure_parameters(connection_handle,
                                         initiator_config->config_id,
                                         initiator_config->max_procedure_duration,
                                         initiator_config->min_interval,
                                         initiator_config->max_interval,
                                         initiator_config->max_procedure_count,
                                         initiator_config->min_subevent_len,
                                         initiator_config->max_subevent_len,
                                         initiator_config->antenna_config,
                                         initiator_config->phy,
                                         initiator_config->tx_pwr_delta,
                                         initiator_config->preferred_peer_antenna);
  app_log_status_warning_f(sc, "Set procedure parameters failed" APP_LOG_NL);

  sc = abr_cs_parser_cleanup_measurement(connection_handle);
  app_assert_status(sc);
  sc = sl_bt_cs_procedure_enable(connection_handle, sl_bt_cs_procedure_state_enabled, initiator_config->config_id);
  app_log_status_warning_f(sc, "Procedure enable failed" APP_LOG_NL);
  app_assert_status(sc);
}

/******************************************************************************
 * Init function that sets the first discovery and initiator config
 * and register the selected callback function pointer as a
 * callback for the distance measurement.
 *****************************************************************************/
void abr_initiator_init(abr_result_cb_t result_cb,
                        abr_initiator_config_t *initiator_config)
{
  sl_status_t sc;
  abr_cs_parser_configuration_t parser_config;
  abr_initiator_set_initial_state(initiator_config);
  platform_display_state(ABR_STATE_DISCONNECTED);
  initiator_config->discovery_state = ABR_DISCOVERY_STATE_IDLE;
  initiator_config->result_cb = result_cb;

  if (initiator_config->filter_address != NULL) {
    app_log_info("Filtering reflectors. Accepting %02x:%02x:%02x:%02x:%02x:%02x" APP_LOG_NL,
                 initiator_config->filter_address[5],
                 initiator_config->filter_address[4],
                 initiator_config->filter_address[3],
                 initiator_config->filter_address[2],
                 initiator_config->filter_address[1],
                 initiator_config->filter_address[0]);
  }
  rtl_library_init(&initiator_config->rtl_handle, initiator_config->mode);
  parser_config.measurement_mode = initiator_config->mode;
  parser_config.rssi_measurement_enabled = initiator_config->rssi_measurement_enabled;
  parser_config.rssi_tx_power = initiator_config->rssi_tx_power;

  sc = abr_cs_parser_init(&parser_config);
  app_assert_status(sc);
}

/******************************************************************************
 * ABR initiator enable functionality
 *****************************************************************************/
void abr_initiator_enable(void)
{
  sl_status_t sc;
  int16_t tx_power_min_dbm, tx_power_max_dbm;

  // Convert power to mdBm
  int16_t max_power = ( ((int16_t)initiator_config->tx_power_requested_max_dbm) * 10);
  int16_t min_power = ( ((int16_t)initiator_config->tx_power_requested_max_dbm) * 10);
  sc = sl_bt_system_set_tx_power(min_power,
                                 max_power,
                                 &tx_power_min_dbm,
                                 &tx_power_max_dbm);
  app_assert_status(sc);

  // Store the actual power level for later use
  initiator_config->tx_power_max_dbm = tx_power_max_dbm / 10;
  initiator_config->tx_power_min_dbm = tx_power_min_dbm / 10;

  // Check if the PHY is set to 1M. Currently, this is the only supported PHY
  if (initiator_config->scan_phy != sl_bt_gap_phy_coding_1m_uncoded) {
    initiator_config->scan_phy = sl_bt_gap_phy_coding_1m_uncoded;
    app_log_warning("Scanning PHY is not supported and set to 1M PHY" APP_LOG_NL);
  }

  // Start scanning
  sc = sl_bt_scanner_set_parameters(sl_bt_scanner_scan_mode_passive, initiator_config->scan_interval, initiator_config->scan_window);
  app_assert_status(sc);

  initiator_scanning_start();
}

/******************************************************************************
 * Start scanning for the reflector device
 *****************************************************************************/
static void initiator_scanning_start(void)
{
  sl_status_t sc;

  app_log_info("Scanning..." APP_LOG_NL);
  platform_display_state(ABR_STATE_SCANNING);

  // Check if the PHY is set to 1M. Currently, this is the only supported PHY
  if (initiator_config->scan_phy != sl_bt_gap_phy_coding_1m_uncoded) {
    initiator_config->scan_phy = sl_bt_gap_phy_coding_1m_uncoded;
    app_log_warning("Scanning PHY is not supported and set to 1M PHY" APP_LOG_NL);
  }

  // Start scanning
  sc = sl_bt_scanner_set_parameters(sl_bt_scanner_scan_mode_passive, initiator_config->scan_interval, initiator_config->scan_window);
  app_assert_status(sc);

  // Start scanning - looking for peripheral devices
  sc = sl_bt_scanner_start(initiator_config->scan_phy, scanner_discover_generic);
  app_assert_status(sc);
  initiator_config->discovery_state = ABR_DISCOVERY_STATE_SCAN;
}

/******************************************************************************
 * Stop scanning for the reflector device
 *****************************************************************************/
void initiator_scanning_stop(void)
{
  sl_status_t sc;
  if (initiator_config->discovery_state == ABR_DISCOVERY_STATE_SCAN) {
    sc = sl_bt_scanner_stop();
    app_assert_status(sc);
    initiator_config->discovery_state = ABR_DISCOVERY_STATE_IDLE;
  }
}

/******************************************************************************
 * Cycle through advertisement contents and look for the matching device name
 *****************************************************************************/
static bool initiator_process_scan_response(sl_bt_evt_scanner_scan_report_t *response)
{
  int i = 0;
  bool reflector_match = false;
  uint8_t advertisement_length;
  uint8_t advertisement_type;

  while (i < (response->data.len - 1)) {
    advertisement_length = response->data.data[i];
    advertisement_type = response->data.data[i + 1];

    // Type 0x09 = Complete Local Name, 0x08 Shortened Name
    if (advertisement_type == INITIATOR_LOCAL_NAME) {
      // Check if device name is a mach to device_name
      if (memcmp(response->data.data + i + 2, device_name, strlen(device_name)) == 0) {
        reflector_match = true;
        break;
      }
    }
    // Jump to next AD record
    i = i + advertisement_length + 1;
  }

  //  Filter reflector
  if (initiator_config->filter_address != NULL && 0 != memcmp(initiator_config->filter_address, response->address.addr, ADR_LEN)) {
    reflector_match = false;
  }

  return (reflector_match);
}

/******************************************************************************
 * Check if the detected characteristic matches the UUIDs that
 * is required for the ABR functionality
 *****************************************************************************/
static void check_characteristic_uuid(sl_bt_msg_t *evt)
{
  if (evt->data.evt_gatt_characteristic.uuid.len == UUID_LEN) {
    if (memcmp(result_characteristic_uuid, evt->data.evt_gatt_characteristic.uuid.data, UUID_LEN) == 0) {
      result_handle = evt->data.evt_gatt_characteristic.characteristic;
      characteristic_found = true;
      app_log_info("Found remote value characteristic" APP_LOG_NL);
    }
  }
}

/******************************************************************************
 * Event handler dedicated for the discovery process:
 * discovering services on reflector side and checking the characteristics.
 * Once everything is compatible, triggers the configuration of this initiator
 * device.
 *****************************************************************************/
static void process_procedure_complete_event(sl_bt_msg_t *evt)
{
  uint16_t procedure_result =  evt->data.evt_gatt_procedure_completed.result;
  sl_status_t sc;

  switch (action) {
    case act_discover_service:
      action = act_none;
      app_assert_status(procedure_result);
      if (!procedure_result) {
        // Discover successful, start characteristic discovery.
        sc = sl_bt_gatt_discover_characteristics(connection_handle, service_handle);
        app_assert_status(sc);
        action = act_discover_characteristics;
        app_log_info("Service discovered" APP_LOG_NL);
      }
      break;
    case act_discover_characteristics:
      action = act_none;
      app_assert_status(procedure_result);
      if (!procedure_result) {
        if (characteristic_found) {
          initiator_config->discovery_state = ABR_DISCOVERY_STATE_FINISHED;
          sc = sl_bt_gatt_set_characteristic_notification(connection_handle, result_handle, sl_bt_gatt_indication);
          app_assert_status(sc);
          action = act_subscribe_result;
          app_log_info("Characteristic discovered" APP_LOG_NL);
        }
      }
      break;
    case act_subscribe_result:
      action = act_none;
      app_assert_status(procedure_result);
      abr_initiator_create_config();
      break;
    case act_none:
      break;
    default:
      break;
  }
}

/******************************************************************************
 * Calculate distance between initiator and reflector using RTL library.
 *
 * @param[in] connection Connection handle from BLE stack.
 *****************************************************************************/
static void initiator_calculate_distance(uint8_t connection)
{
  sl_status_t sc;
  abr_rtl_result_t result;
  enum sl_rtl_error_code rtl_err;
  abr_cs_parser_meas_data_t cs_meas_data;
  bool restart_procedure = false;
  result.distance = 0.0;
  result.rssi_distance = 0.0;
  memset(&cs_meas_data, 0, sizeof(abr_cs_parser_meas_data_t));

  switch (initiator_config->mode) {
    case sl_bt_cs_mode_rtt:
      sc = abr_cs_parser_get_measurement_data(connection,
                                              initiator_config->mode,
                                              &cs_meas_data);
      if (sc == SL_STATUS_OK) {
        // RTT measurement can be processed by RTL lib.
        rtl_err = sl_rtl_abr_process_rtt(&initiator_config->rtl_handle,
                                         &cs_meas_data.rtt_data);
        if (rtl_err == SL_RTL_ERROR_SUCCESS) {
          rtl_err = sl_rtl_abr_get_distance(&initiator_config->rtl_handle,
                                            &result.distance);
        } else {
          app_log_warning("Failed to call RTL library!" APP_LOG_NL);
        }

        if (rtl_err == SL_RTL_ERROR_SUCCESS) {
          abr_cs_parser_store_distance(&result.distance);

          rtl_err = sl_rtl_util_rssi2distance(initiator_config->rssi_tx_power,
                                              cs_meas_data.initiator_calibration_rssi,
                                              &result.rssi_distance);
          if (rtl_err != SL_RTL_ERROR_SUCCESS) {
            app_log_error("Failed to calculate RSSI distance!" APP_LOG_NL);
          }

          if (initiator_config->result_cb != NULL) {
            initiator_config->result_cb(&result, NULL);
          }
        }
        sc = abr_cs_parser_cleanup_measurement(connection);
        app_assert_status(sc);

        if (initiator_config->max_procedure_count != 0) {
          restart_procedure = true;
        }
      }
      break;
    case sl_bt_cs_mode_pbr:
      sc = abr_cs_parser_get_measurement_data(connection,
                                              initiator_config->mode,
                                              &cs_meas_data);
      if (sc == SL_STATUS_OK) {
        // RTP measurement can be processed by RTL lib.
        rtl_err = sl_rtl_abr_process_rtp(&initiator_config->rtl_handle,
                                         &cs_meas_data.rtp_data);
        if (rtl_err == SL_RTL_ERROR_SUCCESS) {
          rtl_err = sl_rtl_abr_get_distance(&initiator_config->rtl_handle,
                                            &result.distance);
        } else {
          app_log_warning("Failed to call RTL library!" APP_LOG_NL);
        }

        if (rtl_err == SL_RTL_ERROR_SUCCESS) {
          abr_cs_parser_store_distance(&result.distance);

          rtl_err = sl_rtl_util_rssi2distance(initiator_config->rssi_tx_power,
                                              cs_meas_data.initiator_calibration_rssi,
                                              &result.rssi_distance);
          if (rtl_err != SL_RTL_ERROR_SUCCESS) {
            app_log_error("Failed to calculate RSSI distance!" APP_LOG_NL);
          }

          if (initiator_config->result_cb != NULL) {
            initiator_config->result_cb(&result, NULL);
          }
        }

        sc = abr_cs_parser_cleanup_measurement(connection);
        app_assert_status(sc);

        if (initiator_config->max_procedure_count != 0) {
          restart_procedure = true;
        }
      }
      break;
    case sl_bt_cs_mode_pbr_and_rtt:
      break;
    default:
      break;
  }

  if (restart_procedure) {
    abr_initiator_perform_procedure();
  }
}

/**************************************************************************//**
 * Initialize RTL library.
 * @param[in] handle RTL library item handle.
 * @param[in] abr_mode Specifying ABR method.
 *****************************************************************************/
static void rtl_library_init(sl_rtl_abr_libitem *handle, uint8_t abr_mode)
{
  enum sl_rtl_error_code rtl_err;

  app_log_info("Initialising RTL..." APP_LOG_NL);
  rtl_err = sl_rtl_abr_init(handle);
  app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
             "Failed to initialize RTL library!" APP_LOG_NL);

  rtl_err = sl_rtl_abr_set_algo_mode(handle, SL_RTL_ABR_ALGO_MODE_REAL_TIME_BASIC);
  app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
             "RTL library set mode failed!" APP_LOG_NL);

  switch (abr_mode) {
    case sl_bt_cs_mode_rtt:
      rtl_err = sl_rtl_abr_set_cs_mode(handle, SL_RTL_ABR_CS_MODE_RTT);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set method failed!" APP_LOG_NL);
      break;
    case sl_bt_cs_mode_pbr:
      rtl_err = sl_rtl_abr_set_cs_mode(handle, SL_RTL_ABR_CS_MODE_RTP);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set method failed!" APP_LOG_NL);
      break;
    case sl_bt_cs_mode_pbr_and_rtt:
      // This shall be changed in future.
      // There's no combined mode support in RTL now
      rtl_err = sl_rtl_abr_set_cs_mode(handle, SL_RTL_ABR_CS_MODE_RTP);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set method failed!" APP_LOG_NL);
      break;
    default:
      rtl_err = sl_rtl_abr_set_cs_mode(handle, SL_RTL_ABR_CS_MODE_RTP);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set method failed!" APP_LOG_NL);
      break;
  }

  rtl_err = sl_rtl_abr_create_estimator(handle);
  app_assert(rtl_err == SL_RTL_ERROR_SUCCESS, "Failed to create estimator!"
             APP_LOG_NL);
}

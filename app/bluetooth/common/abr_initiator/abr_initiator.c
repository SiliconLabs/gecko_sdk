/*******************************************************************************
 * @file
 * @brief ABR initiator
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "abr_file_log.h"
#include "abr_ras.h"
#include "abr_initiator_interface.h"
#include "abr_initiator_config.h"
#include "abr_ans.h"

#include "sl_rtl_clib_api.h"

// Discovering services/characteristics and subscribing raises procedure_complete events
// Actions are used to indicate which procedure was completed.
#define CONFIG_TX_POWER_MIN         -100
#define ABR_CENTRAL_TX_POWER        10
#define ADR_LEN                     6
#define UUID_LEN                    16
#define COMPLETE_LOCAL_NAME         0x09
#define CONFIG_RAS_REQUEST_PERIODIC_NOTIFICATION_MODE true
#define BYTE_LEN                    8             // Byte length in bits
#define DEFAULT_NUM_TONES           79            // Number of tones
#define DEFAULT_FREQUENCY_DELTA     1e6f          // Channel frequency delta
#define CS_ALL_SUBEVENTS_ABORTED    0x0F          // All subsequent CS subevents aborted
#define PROCEDURE_DONE_STATUS_MASK  0x0F          // Procedure done status mask
#define MODE_PBR_STR                "PBR"
#define MODE_RTT_STR                "RTT"
#define MODE_PBR_RTT_STR            "PBR and RTT"
#define MODE_UNKNOWN_STR            "UNKNOWN"
#define CS_CHANNEL_MAP_MIN_CHANNELS 15
#define CS_CHANNEL_MAP_MAX_CHANNELS 76
#define USER_CMD_GET_ANTENNA_OFFSET_ID 7
#define OFFSET_RESPONSE_MAX_LENGHT     9

typedef enum {
  act_none = 0,
  act_discover_service,
  act_discover_characteristics,
  act_subscribe_result_1,
  act_subscribe_result_2,
} action_t;

static abr_initiator_config_t *initiator_config;
static const char *device_name = INITIATOR_DEVICE_NAME; // Device name to match against scan results.

static bool ras_control_point_characteristic_found = false;
static bool ras_procedure_enable_data_characteristic_found = false;
static bool ras_se_ranging_data_characteristic_found = false;
static bool ras_characteristics_discovered = false;

static uint8_t connection_handle = SL_BT_INVALID_CONNECTION_HANDLE;
static uint32_t ras_service_handle = UINT32_MAX;
static uint16_t ras_control_point_characteristic_handle = UINT16_MAX;
static uint16_t ras_procedure_enable_data_characteristic_handle = UINT16_MAX;
static uint16_t ras_se_ranging_data_characteristic_handle = UINT16_MAX;
static action_t action = act_none;

const uint8_t ras_service_uuid[] = RAS_SERVICE_UUID;
const uint8_t ras_control_point_characteristic_uuid[] = RAS_CONTROL_POINT_CHARACTERISTIC_UUID;
const uint8_t ras_procedure_enable_data_characteristic_uuid[] = RAS_PROCEDURE_ENABLE_DATA_CHARACTERISTIC_UUID;
const uint8_t result_characteristic_uuid[] = INITIATOR_CHARACTERISTIC_UUID;
const uint8_t ras_se_ranging_data_characteristic_uuid[] = RAS_SE_RANGING_DATA_CHARACTERISTIC_UUID;

static volatile bool procedure_enable_retry = false;
#ifdef HOST_TOOLCHAIN
static volatile bool antenna_switching = false;
#endif //HOST_TOOLCHAIN

static void initiator_scanning_start(void);
static void check_characteristic_uuid(sl_bt_msg_t *evt);
static bool initiator_calculate_distance(uint8_t connection);
static void abr_initiator_start_cs_procedure(void);
static void abr_initiator_restart_cs_procedure(void);
static void abr_initiator_create_config(void);
static void initiator_process_scan_response(bd_addr *address, uint8_t address_type, const uint8array *adv_data);
static void process_procedure_complete_event(sl_bt_msg_t *evt);
static uint32_t get_num_tones_from_channel_map(const uint8_t *channel_map, const uint32_t channel_map_len);
static sl_status_t check_cs_result_event_flags(sl_bt_evt_cs_result_t *cs_res);

/******************************************************************************
 * ABR initiator set initial config.
 *****************************************************************************/
void abr_initiator_set_initial_state(abr_initiator_config_t *config)
{
  initiator_config = config;
  initiator_config->discovery_state = ABR_DISCOVERY_STATE_IDLE;
  // Antenna switching is only available for host initiator
  #ifndef ABR_CPP_MODE
  #ifdef HOST_TOOLCHAIN
  abr_set_antenna_offset();
  if (ans_initiator_decide_antenna_switching(initiator_config->use_antenna_wired_offset)) {
    antenna_switching = true;
    initiator_config->max_procedure_count = 1;
    initiator_config->antenna_config = 3;
    ans_set_antenna_offset(initiator_config->antenna_offset.offset_value,
                           initiator_config->antenna_offset.offset_count);
  }
  #endif // HOST_TOOLCHAIN
  #endif // ABR_CPP_MODE
}

/******************************************************************************
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *****************************************************************************/
void bt_on_event_initiator(sl_bt_msg_t *evt)
{
  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_scanner_legacy_advertisement_report_id:
      initiator_process_scan_response(&(evt->data.evt_scanner_legacy_advertisement_report.address),
                                      evt->data.evt_scanner_legacy_advertisement_report.address_type,
                                      &(evt->data.evt_scanner_legacy_advertisement_report.data));
      break;

    case sl_bt_evt_scanner_extended_advertisement_report_id:
      initiator_process_scan_response(&(evt->data.evt_scanner_extended_advertisement_report.address),
                                      evt->data.evt_scanner_extended_advertisement_report.address_type,
                                      &(evt->data.evt_scanner_extended_advertisement_report.data));
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
      app_log_info("Set connection parameters..." APP_LOG_NL);
      ras_control_point_characteristic_found = false;
      ras_procedure_enable_data_characteristic_found = false;
      ras_se_ranging_data_characteristic_found = false;
      ras_characteristics_discovered = false;
      break;

    case sl_bt_evt_connection_parameters_id:
      if (evt->data.evt_connection_parameters.security_mode == 1) {
        app_log_info("Connection parameters set. Connection encrypted" APP_LOG_NL);
        sc = sl_bt_gatt_discover_primary_services_by_uuid(connection_handle,
                                                          UUID_LEN,
                                                          ras_service_uuid);
        app_assert_status(sc);
        abr_initiator_create_config();
      }
      break;

    case sl_bt_evt_gatt_procedure_completed_id:
      process_procedure_complete_event(evt);
      break;

    case sl_bt_evt_gatt_characteristic_id:
      app_log_info("Discovered new characteristic" APP_LOG_NL);
      check_characteristic_uuid(evt);
      break;

    case sl_bt_evt_gatt_service_id:
      if (evt->data.evt_gatt_service.uuid.len == UUID_LEN) {
        if (memcmp(ras_service_uuid, evt->data.evt_gatt_service.uuid.data, UUID_LEN) == 0) {
          ras_service_handle = evt->data.evt_gatt_service.service;
          action = act_discover_service;
          app_log_info("RAS service found" APP_LOG_NL);
        }
      }
      break;

    case sl_bt_evt_gatt_characteristic_value_id:
      app_log_info("Received new GATT data" APP_LOG_NL);

      if (evt->data.evt_gatt_characteristic_value.characteristic == ras_control_point_characteristic_handle) {
        app_log_info("Received new RAS Control Point data" APP_LOG_NL);

        ras_ranging_data_get_command_t cmd;
        sc = abr_ras_create_control_point_response(evt->data.evt_gatt_characteristic_value.value.data,
                                                   evt->data.evt_gatt_characteristic_value.value.len,
                                                   CONFIG_RAS_REQUEST_PERIODIC_NOTIFICATION_MODE,
                                                   &cmd);
        if (sc == SL_STATUS_OK) {
          sc = sl_bt_gatt_write_characteristic_value(connection_handle,
                                                     ras_control_point_characteristic_handle,
                                                     sizeof(ras_ranging_data_get_command_t),
                                                     (uint8_t*)&cmd);
          app_assert_status(sc);
        }

        sc = sl_bt_gatt_send_characteristic_confirmation(connection_handle);
        app_assert_status(sc);
      }

      if (evt->data.evt_gatt_characteristic_value.characteristic != ras_se_ranging_data_characteristic_handle) {
        return;
      }
      app_log_info("Received new measurement data from the reflector" APP_LOG_NL);

      if (evt->data.evt_gatt_characteristic_value.att_opcode == sl_bt_gatt_handle_value_notification) {
        struct sl_bt_evt_cs_result_s* result_ptr =
          (struct sl_bt_evt_cs_result_s*)evt->data.evt_gatt_characteristic_value.value.data;

        app_log_debug("Reflector CS packet received; proc_cnt='%u' proc_done='%u' se_done='%u' len='%u'" APP_LOG_NL,
                      result_ptr->procedure_counter,
                      result_ptr->procedure_done_status,
                      result_ptr->subevent_done_status,
                      evt->data.evt_gatt_characteristic_value.value.len);

        if (abr_process_reflector_cs_result(result_ptr, evt->data.evt_gatt_characteristic_value.connection)) {
          abr_initiator_restart_cs_procedure();
        }
      }
      break;

    case sl_bt_evt_cs_procedure_enable_complete_id:
      sc = abr_file_log_procedure_config_complete_event(&evt->data.evt_cs_procedure_enable_complete);
      app_assert_status(sc);
      app_log_debug("Procedure enable complete" APP_LOG_NL);
      break;

    case sl_bt_evt_cs_config_complete_id:
      app_log_info("ABR config created. Set procedure parameters ..." APP_LOG_NL);
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
      app_assert_status(sc);
      app_log_info("Procedure parameters set" APP_LOG_NL);
      sc = abr_file_log_config_complete_event(&evt->data.evt_cs_config_complete);
      app_assert_status(sc);
      abr_initiator_start_cs_procedure();
      break;

    case sl_bt_evt_cs_result_id:
      if (abr_process_initiator_cs_result(&evt->data.evt_cs_result)) {
        abr_initiator_restart_cs_procedure();
      }
      break;

    case sl_bt_evt_connection_closed_id:
      initiator_config->discovery_state = ABR_DISCOVERY_STATE_IDLE;

      uint16_t reason = evt->data.evt_connection_closed.reason;
      app_log_info("Connection closed to the Reflector reason='%02X'" APP_LOG_NL,
                   reason);
      platform_display_state(ABR_STATE_DISCONNECTED);
      connection_handle = SL_BT_INVALID_CONNECTION_HANDLE;
      initiator_scanning_start();
      break;

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

    default:
      app_log_info("BLE event: 0x%02lx" APP_LOG_NL,
                   (unsigned long)SL_BT_MSG_ID(evt->header));
      break;
  }
}

void abr_set_antenna_offset()
{
  sl_status_t sc;
  uint8_t user_data_to_target = USER_CMD_GET_ANTENNA_OFFSET_ID;
  // Max 9 data: number of antenna + max 4 wired offset value + max 4 wireless offset value
  int16_t response_data_offset[OFFSET_RESPONSE_MAX_LENGHT];
  size_t response_data_len;
  sc = sl_bt_user_message_to_target(sizeof(user_data_to_target),
                                    &user_data_to_target,
                                    sizeof(response_data_offset),
                                    &response_data_len,
                                    (uint8_t *)response_data_offset);
  if (sc != SL_STATUS_OK) {
    app_log_warning("User message to target failed: %u" APP_LOG_NL, sc);
  } else {
    app_log_info("Received antenna offset parameters" APP_LOG_NL);
    // First data is the number of antennas
    initiator_config->antenna_offset.offset_count = response_data_offset[0];
    if (initiator_config->antenna_offset.offset_count > MAX_ANTENNA_NUMBER) {
      app_log_error("Antenna count exceeds max antenna number: %u" APP_LOG_NL, MAX_ANTENNA_NUMBER);
      return;
    }
    if (initiator_config->use_antenna_wired_offset) {
      memcpy(initiator_config->antenna_offset.offset_value,
             response_data_offset + 1,
             sizeof(initiator_config->antenna_offset.offset_value));
    } else {
      memcpy(initiator_config->antenna_offset.offset_value,
             response_data_offset + 1 + initiator_config->antenna_offset.offset_count,
             sizeof(initiator_config->antenna_offset.offset_value));
    }
    app_log_info("Offset: %d" APP_LOG_NL, initiator_config->antenna_offset.offset_value[0]);
    // Use the offset of the first antenna
    int16_t ant_offset_cm_origin[1] = { (int16_t)initiator_config->antenna_offset.offset_value[0] };
    sc = sl_bt_cs_set_antenna_configuration(sizeof(initiator_config->antenna_offset.offset_value[0]), (uint8_t *) ant_offset_cm_origin);
    if (sc != SL_STATUS_OK) {
      app_log_warning("Set antenna config failed: %u" APP_LOG_NL, sc);
    }
  }
}

bool abr_process_reflector_cs_result(sl_bt_evt_cs_result_t *evt_cs_result, uint8_t initiator_connection)
{
  sl_status_t sc = check_cs_result_event_flags(evt_cs_result);
  if (sc != SL_STATUS_OK) {
    app_log_info("Performing new procedure, current one aborted" APP_LOG_NL);
    return true;
  }

  sl_status_t parse_status = abr_cs_parser_parse_event_result_data(evt_cs_result,
                                                                   ABR_DEVICE_REFLECTOR);
  if (parse_status != SL_STATUS_OK) {
    app_log_info("Incorrect cs_event_result reflector" APP_LOG_NL);
  }

  bool restart_needed = initiator_calculate_distance(initiator_connection);

  if (abr_cs_parser_procedure_restart_needed(initiator_connection)
      || (initiator_config->max_procedure_count != 0
          && evt_cs_result->subevent_done_status == 0
          && restart_needed)) {
    app_log_info("Performing new procedure" APP_LOG_NL);
    return true;
  }
  return false;
}

bool abr_process_initiator_cs_result(sl_bt_evt_cs_result_t *evt_cs_result)
{
  app_log_info("Initiator CS packet received; len='%u'" APP_LOG_NL, evt_cs_result->data.len);

  sl_status_t sc = check_cs_result_event_flags(evt_cs_result);
  if (sc != SL_STATUS_OK) {
    if (initiator_config->max_procedure_count != 0) {
      app_log_info("Performing new procedure" APP_LOG_NL);
      return true;
    }
    abr_cs_parser_cleanup_measurement(evt_cs_result->connection);
    return false;
  }

  sl_status_t parse_status = abr_cs_parser_parse_event_result_data(evt_cs_result,
                                                                   ABR_DEVICE_INITIATOR);
  if (parse_status != SL_STATUS_OK) {
    app_log_info("Incorrect cs_event_result initiator" APP_LOG_NL);
  }

  // Calculate distance
  bool restart_needed = initiator_calculate_distance(evt_cs_result->connection);

  // Perform a new ABR measurement procedure
  // Currently, subevent_done_status = 0 when we iterated through all channel and = 1 if not.
  if (abr_cs_parser_procedure_restart_needed(evt_cs_result->connection)
      || (initiator_config->max_procedure_count != 0
          && evt_cs_result->subevent_done_status == 0
          && restart_needed)) {
    app_log_info("Performing new procedure" APP_LOG_NL);
    return true;
  }
  return false;
}

void abr_initiator_deinit(void)
{
  sl_status_t sc;

  if (connection_handle != SL_BT_INVALID_CONNECTION_HANDLE) {
    app_log_info("Closing connection" APP_LOG_NL);
    sc = sl_bt_connection_close(connection_handle);
    app_assert_status(sc);
  }
}

/******************************************************************************
 * ABR initiator create channel-sounding and radio configuration.
 *****************************************************************************/
static void abr_initiator_create_config(void)
{
  sl_status_t sc;
  char *mode_string;

  app_log_info("Creating ABR config..." APP_LOG_NL);

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
                              &initiator_config->channel_map,
                              initiator_config->channel_map_repetition,
                              initiator_config->channel_selection_type,
                              initiator_config->ch3c_shape,
                              initiator_config->ch3c_jump,
                              initiator_config->companion_signal_enable);
  app_assert_status(sc);

  abr_rtl_library_init(&initiator_config->rtl_handle, initiator_config->mode);

  sc = abr_cs_parser_configure(initiator_config->channel_map.data,
                               initiator_config->channel_map_len,
                               initiator_config->mode0_step);
  app_assert_status(sc);

  switch (initiator_config->mode) {
    case ABR_INITIATOR_MODE_PBR:
      mode_string = MODE_PBR_STR;
      break;
    case ABR_INITIATOR_MODE_RTT:
      mode_string = MODE_RTT_STR;
      break;
    default:
      mode_string = MODE_UNKNOWN_STR;
      break;
  }
  app_log_info("Mode: %s"APP_LOG_NL, mode_string);
}

/******************************************************************************
 * ABR initiator trigger channel-sounding procedure
 *****************************************************************************/
static void abr_initiator_start_cs_procedure(void)
{
  sl_status_t sc;

  app_log_info("-------------------------------------------------------" APP_LOG_NL);
  #ifdef HOST_TOOLCHAIN
  if (antenna_switching) {
    ans_antenna_switching();
  }
  #endif // HOST_TOOLCHAIN

  app_log_info("Starting CS procedure..." APP_LOG_NL);
  sc = abr_cs_parser_cleanup_measurement(connection_handle);
  app_assert_status(sc);
  sc = sl_bt_cs_procedure_enable(connection_handle,
                                 sl_bt_cs_procedure_state_enabled,
                                 initiator_config->config_id);
  if (sc != SL_STATUS_OK) {
    app_log_warning("Procedure enable failed" APP_LOG_NL);
    procedure_enable_retry = true;
  }
}

static void abr_initiator_restart_cs_procedure(void)
{
  // If the application controls the procedure start (max_procedure_count != 0) we need to restart it manually,
  // otherwise the stack will take care of it
  if (initiator_config->max_procedure_count != 0) {
    abr_initiator_start_cs_procedure();
  } else {
    sl_status_t sc = abr_cs_parser_cleanup_measurement(connection_handle);
    app_assert_status(sc);
  }
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

  // Validate channel map
  uint32_t enabled_channels = get_num_tones_from_channel_map(initiator_config->channel_map.data,
                                                             initiator_config->channel_map_len);
  app_log_info("CS channel count: %lu" APP_LOG_NL, (unsigned long)enabled_channels);
  app_assert(enabled_channels >= CS_CHANNEL_MAP_MIN_CHANNELS, "CS channel map does not have enough channels enabled");
  app_assert(enabled_channels <= CS_CHANNEL_MAP_MAX_CHANNELS, "CS channel map has too many channels enabled");

  if (initiator_config->filter_address != NULL) {
    app_log_info("Filtering reflectors. Accepting %02x:%02x:%02x:%02x:%02x:%02x" APP_LOG_NL,
                 initiator_config->filter_address[5],
                 initiator_config->filter_address[4],
                 initiator_config->filter_address[3],
                 initiator_config->filter_address[2],
                 initiator_config->filter_address[1],
                 initiator_config->filter_address[0]);
  }
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
  int16_t min_power = ( ((int16_t)initiator_config->tx_power_requested_min_dbm) * 10);
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
  sc = sl_bt_scanner_set_parameters(sl_bt_scanner_scan_mode_passive,
                                    initiator_config->scan_interval,
                                    initiator_config->scan_window);
  app_assert_status(sc);

  // Start scanning - looking for peripheral devices
  sc = sl_bt_scanner_start(initiator_config->scan_phy, sl_bt_scanner_discover_generic);
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
 * Cycle through advertisement contents and look for the matching device name.
 * Initiate a connection if the name matches.
 *****************************************************************************/
static void initiator_process_scan_response(bd_addr *address,
                                            uint8_t address_type,
                                            const uint8array *adv_data)
{
  int i = 0;
  bool reflector_match = false;
  uint8_t advertisement_length;
  uint8_t advertisement_type;
  sl_status_t sc;

  while (i < (adv_data->len - 1)) {
    advertisement_length = adv_data->data[i];
    advertisement_type = adv_data->data[i + 1];

    // Type 0x09 = Complete Local Name, 0x08 Shortened Name
    if (advertisement_type == INITIATOR_LOCAL_NAME) {
      // Check if device name is a mach to device_name
      if (memcmp(adv_data->data + i + 2, device_name, strlen(device_name)) == 0) {
        reflector_match = true;
        break;
      }
    }
    // Jump to next AD record
    i = i + advertisement_length + 1;
  }

  //  Filter reflector
  if (initiator_config->filter_address != NULL && 0 != memcmp(initiator_config->filter_address,
                                                              address->addr,
                                                              ADR_LEN)) {
    reflector_match = false;
  }

  if (reflector_match) {
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
      sc = sl_bt_connection_open(*address,
                                 address_type,
                                 initiator_config->phy,
                                 &connection_handle);
      app_assert_status(sc);
    }
  } else {
    waiting_indication();
  }
}

/******************************************************************************
 * Check if the detected characteristic matches the UUIDs that
 * is required for the ABR functionality
 *****************************************************************************/
static void check_characteristic_uuid(sl_bt_msg_t *evt)
{
  if (evt->data.evt_gatt_characteristic.uuid.len == UUID_LEN) {
    if (memcmp(ras_control_point_characteristic_uuid,
               evt->data.evt_gatt_characteristic.uuid.data,
               UUID_LEN) == 0) {
      ras_control_point_characteristic_handle =
        evt->data.evt_gatt_characteristic.characteristic;
      ras_control_point_characteristic_found = true;
      app_log_info("Discovered RAS Control Point characteristic" APP_LOG_NL);
    }

    if (memcmp(ras_procedure_enable_data_characteristic_uuid,
               evt->data.evt_gatt_characteristic.uuid.data,
               UUID_LEN) == 0) {
      ras_procedure_enable_data_characteristic_handle =
        evt->data.evt_gatt_characteristic.characteristic;
      ras_procedure_enable_data_characteristic_found = true;
      app_log_info("Discovered RAS Procedure Enable Data characteristic" APP_LOG_NL);
    }

    if (memcmp(ras_se_ranging_data_characteristic_uuid,
               evt->data.evt_gatt_characteristic.uuid.data,
               UUID_LEN) == 0) {
      ras_se_ranging_data_characteristic_handle =
        evt->data.evt_gatt_characteristic.characteristic;
      ras_se_ranging_data_characteristic_found = true;
      app_log_info("Discovered RAS Subevent Ranging Data characteristic" APP_LOG_NL);
    }

    if (ras_control_point_characteristic_found
        && ras_procedure_enable_data_characteristic_found
        && ras_se_ranging_data_characteristic_found) {
      ras_characteristics_discovered = true;
      app_log_info("All RAS characteristics have been discovered successfully" APP_LOG_NL);
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
  if (procedure_result != SL_STATUS_OK) {
    action = act_none;
    app_log_error("GATT procedure failed" APP_LOG_NL);
    app_assert_status(procedure_result);
    return;
  }

  switch (action) {
    case act_discover_service:
      app_log_info("Service discovery finished" APP_LOG_NL);
      // Service discovery successful, start characteristic discovery
      sc = sl_bt_gatt_discover_characteristics(connection_handle, ras_service_handle);
      app_assert_status(sc);
      action = act_discover_characteristics;
      break;

    case act_discover_characteristics:
      if (!ras_characteristics_discovered) {
        return;
      }
      initiator_config->discovery_state = ABR_DISCOVERY_STATE_FINISHED;
      app_log_info("Characteristics discovery finished" APP_LOG_NL);
      // Subscribe for notifications on the RAS Subevent Ranging Data
      sc = sl_bt_gatt_set_characteristic_notification(connection_handle,
                                                      ras_se_ranging_data_characteristic_handle,
                                                      sl_bt_gatt_notification);
      app_assert_status(sc);
      action = act_subscribe_result_1;
      break;

    case act_subscribe_result_1:
      app_log_info("Subscribed to RAS Subevent Ranging Data notifications" APP_LOG_NL);
      // Subscribe for indications on the RAS Control Point
      sc = sl_bt_gatt_set_characteristic_notification(connection_handle,
                                                      ras_control_point_characteristic_handle,
                                                      sl_bt_gatt_indication);
      app_assert_status(sc);
      action = act_subscribe_result_2;
      break;

    case act_subscribe_result_2:
      app_log_info("Subscribed to RAS Control Point indications" APP_LOG_NL);
      action = act_none;
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
 * @return A boolean value if restart is needed.
 *****************************************************************************/
static bool initiator_calculate_distance(uint8_t connection)
{
  sl_status_t sc;
  abr_rtl_result_t result;
  enum sl_rtl_error_code rtl_err = SL_RTL_ERROR_NOT_INITIALIZED;
  enum sl_rtl_error_code rtl_process_err = SL_RTL_ERROR_NOT_INITIALIZED;
  abr_cs_parser_meas_data_t cs_meas_data;
  bool restart_procedure = false;
  result.connection = connection;
  result.distance = 0.0f;
  result.likeliness = 0.0f;
  result.rssi_distance = 0.0f;
  result.cs_bit_error_rate = 0u;
  memset(&cs_meas_data, 0, sizeof(abr_cs_parser_meas_data_t));

  sc = abr_cs_parser_get_measurement_data(connection,
                                          initiator_config->mode,
                                          &cs_meas_data);
  if (sc == SL_STATUS_OK) {
    switch (initiator_config->mode) {
      case ABR_INITIATOR_MODE_RTT:
        // RTT measurement can be processed by RTL lib.
        rtl_err = sl_rtl_abr_process_rtt(&initiator_config->rtl_handle,
                                         &cs_meas_data.rtt_data);
        break;

      case ABR_INITIATOR_MODE_PBR:
        // PBR measurement can be processed by RTL lib.
        rtl_err = sl_rtl_abr_process_rtp(&initiator_config->rtl_handle,
                                         &cs_meas_data.pbr_data);
        break;

      default:
        break;
    }

    // Store RTL process return code
    rtl_process_err = rtl_err;

    if (rtl_err == SL_RTL_ERROR_SUCCESS || rtl_err == SL_RTL_ERROR_ESTIMATION_IN_PROGRESS) {
      rtl_err = sl_rtl_abr_get_distance(&initiator_config->rtl_handle,
                                        &result.distance);
    } else {
      app_log_warning("Failed to call RTL library!" APP_LOG_NL);
    }

    if (rtl_err == SL_RTL_ERROR_SUCCESS || rtl_err == SL_RTL_ERROR_ESTIMATION_IN_PROGRESS) {
      rtl_err = sl_rtl_util_rssi2distance(initiator_config->rssi_tx_power,
                                          cs_meas_data.initiator_calibration_rssi,
                                          &result.rssi_distance);
      if (rtl_err != SL_RTL_ERROR_SUCCESS) {
        app_log_error("Failed to calculate RSSI distance!" APP_LOG_NL);
      }

      rtl_err = sl_rtl_abr_get_distance_likeliness(&initiator_config->rtl_handle,
                                                   &result.likeliness);
      if (rtl_err != SL_RTL_ERROR_SUCCESS) {
        app_log_error("Failed to calculate distance likeliness!" APP_LOG_NL);
      } else {
        abr_cs_parser_store_distance(&result.distance, &result.likeliness, &result.rssi_distance);
      }

      result.cs_bit_error_rate = abr_cs_parser_get_cs_bit_error_rate();

      if (initiator_config->result_cb != NULL) {
        // Call result callback in case of successful process call
        if (rtl_process_err == SL_RTL_ERROR_SUCCESS) {
          initiator_config->result_cb(&result, NULL);
        }
      }
    }
    sc = abr_cs_parser_cleanup_measurement(connection);
    app_assert_status(sc);

    if (initiator_config->max_procedure_count != 0) {
      restart_procedure = true;
    }
  }
  return restart_procedure;
}

/**************************************************************************//**
 * Initialize RTL library.
 * @param[in] handle RTL library item handle.
 * @param[in] abr_mode Specifying ABR method.
 *****************************************************************************/
void abr_rtl_library_init(sl_rtl_abr_libitem *handle, uint8_t abr_mode)
{
  enum sl_rtl_error_code rtl_err;

  if (handle != NULL && *handle != NULL) {
    rtl_err = sl_rtl_abr_deinit(handle);
    app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
               "Failed to deinitialize RTL library!" APP_LOG_NL);
    *handle = NULL;
  }

  app_log_info("Initialising RTL..." APP_LOG_NL);
  rtl_err = sl_rtl_abr_init(handle);
  app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
             "Failed to initialize RTL library!" APP_LOG_NL);

  rtl_err = sl_rtl_abr_set_algo_mode(handle, SL_RTL_ABR_ALGO_MODE_REAL_TIME_BASIC);
  app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
             "RTL library set mode failed!" APP_LOG_NL);

  switch (abr_mode) {
    case ABR_INITIATOR_MODE_RTT:
      rtl_err = sl_rtl_abr_set_cs_mode(handle, SL_RTL_ABR_CS_MODE_RTT);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set method failed!" APP_LOG_NL);
      break;
    case ABR_INITIATOR_MODE_PBR:
    {
      uint32_t num_tones = DEFAULT_NUM_TONES;
      sl_rtl_abr_parameters cs_params = {
        .num_tones = num_tones,
        .tones_frequency_delta_hz = DEFAULT_FREQUENCY_DELTA
      };
      rtl_err = sl_rtl_abr_set_cs_mode(handle, SL_RTL_ABR_CS_MODE_RTP);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set method failed!" APP_LOG_NL);
      rtl_err = sl_rtl_abr_set_parameters(handle, &cs_params);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set parameters method failed!" APP_LOG_NL);
    }
    break;
    default:
    {
      uint32_t num_tones = DEFAULT_NUM_TONES;
      sl_rtl_abr_parameters cs_params = {
        .num_tones = num_tones,
        .tones_frequency_delta_hz = DEFAULT_FREQUENCY_DELTA
      };
      rtl_err = sl_rtl_abr_set_cs_mode(handle, SL_RTL_ABR_CS_MODE_RTP);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set method failed!" APP_LOG_NL);
      rtl_err = sl_rtl_abr_set_parameters(handle, &cs_params);
      app_assert(rtl_err == SL_RTL_ERROR_SUCCESS,
                 "RTL library set parameters method failed!" APP_LOG_NL);
    }
    break;
  }

  rtl_err = sl_rtl_abr_create_estimator(handle);
  app_assert(rtl_err == SL_RTL_ERROR_SUCCESS, "Failed to create estimator!"
             APP_LOG_NL);
}

/******************************************************************************
 * Get number of tones in channel map
 *
 * @param channel_map is the channel_map data
 * @param channel_map_len is the channel_map data length
 *****************************************************************************/
static uint32_t get_num_tones_from_channel_map(const uint8_t *channel_map, const uint32_t channel_map_len)
{
  uint8_t current_channel_map;
  uint32_t num_hadm_channels = 0;

  if (channel_map != NULL) {
    for (uint32_t channel_map_index = 0;
         channel_map_index < channel_map_len;
         channel_map_index++) {
      current_channel_map = channel_map[channel_map_index];
      for (uint8_t current_bit_index = 0;
           current_bit_index < sizeof(uint8_t) * BYTE_LEN;
           current_bit_index++) {
        if (current_channel_map & (1 << current_bit_index)) {
          num_hadm_channels++;
        }
      }
    }
  }
  return num_hadm_channels;
}

/**************************************************************************//**
 * Check CS result event flags.
 * @param[in] cs_res Channel sounding result event pointer.
 *
 * @return SL_STATUS_OK: No actions needed.
 * @return SL_STATUS_ABORT: Procedure is aborted and new procedure should be started.
 * @return SL_STATUS_NULL_POINTER: Invalid null pointer received as argument.
 *****************************************************************************/
static sl_status_t check_cs_result_event_flags(sl_bt_evt_cs_result_t *cs_res)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER;

  if (cs_res != NULL) {
    if ((cs_res->procedure_done_status & PROCEDURE_DONE_STATUS_MASK) == CS_ALL_SUBEVENTS_ABORTED) {
      app_log_info("Procedure aborted!" APP_LOG_NL);
      ret = SL_STATUS_ABORT;
    } else {
      ret = SL_STATUS_OK;
    }
  }
  return ret;
}

void abr_initiator_step(void)
{
  // Try to initialize the CS procedure again if it has failed
  if (procedure_enable_retry) {
    procedure_enable_retry = false;
    abr_initiator_start_cs_procedure();
  }
}

/***************************************************************************//**
 * @file
 * @brief AoA locator application.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sl_bt_api.h"
#include "ncp_host.h"
#include "app_log.h"
#include "app_log_cli.h"
#include "app_assert.h"
#include "app.h"
#include "mqtt.h"

#include "aoa_db.h"
#include "aoa_topics.h"
#include "aoa_parse.h"
#include "aoa_serdes.h"
#include "aoa_util.h"
#include "aoa_cte.h"
#include "aoa_angle.h"
#include "aoa_angle_config.h"

// Optstring argument for getopt.
#define OPTSTRING      NCP_HOST_OPTSTRING APP_LOG_OPTSTRING "m:c:h"

// Usage info.
#define USAGE          APP_LOG_NL "%s " NCP_HOST_USAGE APP_LOG_USAGE "[-m <mqtt_address>[:<port>]] [-c <config>] [-h]" APP_LOG_NL

// Options info.
#define OPTIONS                                                                \
  "\nOPTIONS\n"                                                                \
  NCP_HOST_OPTIONS                                                             \
  APP_LOG_OPTIONS                                                              \
  "    -m  MQTT broker connection parameters.\n"                               \
  "        <mqtt_address>   Address of the MQTT broker (default: localhost)\n" \
  "        <port>           Port of the MQTT broker (default: 1883)\n"         \
  "    -c  Locator configuration file.\n"                                      \
  "        <config>         Path to the configuration file\n"                  \
  "    -h  Print this help message.\n"

static void parse_config_file(const char *file_name);
static void parse_config(const char *config);

static void on_message(mqtt_handle_t *handle,
                       const char *topic,
                       const char *payload);

static void subscribe_correction(void);
static void subscribe_config(void);

static sl_status_t check_config_topic(const char* topic_literal,
                                      const char* topic,
                                      size_t topic_size);

// report mode config
static aoa_report_mode_t report_mode;

// Locator ID
static aoa_id_t locator_id;

// MQTT variables
static mqtt_handle_t mqtt_handle = MQTT_DEFAULT_HANDLE;
static char *mqtt_host = NULL;

// Config file path
static char *config_file = NULL;

// CTE Mode strings
static const char *cte_mode_string[] = {
  "Silabs",
  "connection",
  "connectionless"
};

// AoX Mode strings
static const char *aox_mode_string[] = {
  "PLACEHOLDER",
  "PLACEHOLDER",
  "PLACEHOLDER",
  "SL_RTL_AOX_MODE_ONE_SHOT_BASIC",
  "SL_RTL_AOX_MODE_ONE_SHOT_BASIC_LIGHTWEIGHT",
  "SL_RTL_AOX_MODE_ONE_SHOT_FAST_RESPONSE",
  "SL_RTL_AOX_MODE_ONE_SHOT_HIGH_ACCURACY",
  "SL_RTL_AOX_MODE_ONE_SHOT_BASIC_AZIMUTH_ONLY",
  "SL_RTL_AOX_MODE_ONE_SHOT_FAST_RESPONSE_AZIMUTH_ONLY",
  "SL_RTL_AOX_MODE_ONE_SHOT_HIGH_ACCURACY_AZIMUTH_ONLY",
  "SL_RTL_AOX_MODE_REAL_TIME_FAST_RESPONSE",
  "SL_RTL_AOX_MODE_REAL_TIME_BASIC",
  "SL_RTL_AOX_MODE_REAL_TIME_HIGH_ACCURACY",
};

// AoX antenna array type strings
static const char *antenna_type_string[] = {
  "SL_RTL_AOX_ARRAY_TYPE_4x4_URA",
  "SL_RTL_AOX_ARRAY_TYPE_3x3_URA",
  "SL_RTL_AOX_ARRAY_TYPE_1x4_ULA",
  "SL_RTL_AOX_ARRAY_TYPE_4x4_DP_URA",
  "SL_RTL_AOX_ARRAY_TYPE_COREHW_15x15_DP",
  "SL_RTL_AOX_ARRAY_TYPE_COREHW_12x12_DP",
};

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(int argc, char *argv[])
{
  sl_status_t sc;
  int opt;
  char *port_str;

  report_mode = ANGLE;

  // Process command line options.
  while ((opt = getopt(argc, argv, OPTSTRING)) != -1) {
    switch (opt) {
      // MQTT broker connection parameters.
      case 'm':
        strtok(optarg, ":");
        mqtt_host = malloc(strlen(optarg) + 1);
        app_assert(NULL != mqtt_host,
                   "Failed to allocate memory for the MQTT address.");
        strcpy(mqtt_host, optarg);
        mqtt_handle.host = mqtt_host;
        port_str = strtok(NULL, ":");
        if (port_str != NULL) {
          mqtt_handle.port = atoi(port_str);
        }
        break;
      // Locator configuration file.
      case 'c':
        config_file = malloc(strlen(optarg) + 1);
        app_assert(NULL != config_file,
                   "Failed to allocate memory for the config file.");
        strcpy(config_file, optarg);
        break;
      // Print help.
      case 'h':
        app_log(USAGE, argv[0]);
        app_log(OPTIONS);
        exit(EXIT_SUCCESS);

      // Process options for other modules.
      default:
        sc = ncp_host_set_option((char)opt, optarg);
        if (sc == SL_STATUS_NOT_FOUND) {
          sc = app_log_set_option((char)opt, optarg);
        }
        if (sc != SL_STATUS_OK) {
          app_log(USAGE, argv[0]);
          exit(EXIT_FAILURE);
        }
        break;
    }
  }

  aoa_cte_init();

  // Initialize NCP connection.
  sc = ncp_host_init();
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  app_assert_status(sc);

  app_log_info("NCP host initialised." APP_LOG_NL);
  app_log_info("Resetting NCP target..." APP_LOG_NL);
  // Reset NCP to ensure it gets into a defined state.
  // Once the chip successfully boots, boot event should be received.
  sl_bt_system_reset(sl_bt_system_boot_mode_normal);

  sc = ncp_host_flush_data();
  app_assert_status(sc);

  app_log_info("Selected CTE mode: %s" APP_LOG_NL,
               cte_mode_string[aoa_cte_get_mode()]);
  app_log_info("Press Crtl+C to quit" APP_LOG_NL APP_LOG_NL);
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void)
{
  mqtt_step(&mqtt_handle);
}

/**************************************************************************//**
 * Application Deinit.
 *****************************************************************************/
void app_deinit(void)
{
  sl_status_t sc;
  sl_bt_system_reset(sl_bt_system_boot_mode_normal);
  app_log("Shutting down." APP_LOG_NL);
  ncp_host_deinit();
  sc = mqtt_deinit(&mqtt_handle);
  app_assert_status(sc);

  if (mqtt_host != NULL) {
    free(mqtt_host);
  }
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

  // Track bt system reset
  static bool first_bt_system_reset = true;

  // Catch boot event...
  if (SL_BT_MSG_ID(evt->header) == sl_bt_evt_system_boot_id) {
    // Print boot message.
    app_log("Bluetooth stack booted: v%d.%d.%d-b%d" APP_LOG_NL,
            evt->data.evt_system_boot.major,
            evt->data.evt_system_boot.minor,
            evt->data.evt_system_boot.patch,
            evt->data.evt_system_boot.build);
    // Extract unique ID from BT Address.
    sc = sl_bt_system_get_identity_address(&address, &address_type);
    app_assert_status(sc);
    app_log("Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X" APP_LOG_NL,
            address_type ? "static random" : "public device",
            address.addr[5],
            address.addr[4],
            address.addr[3],
            address.addr[2],
            address.addr[1],
            address.addr[0]);

    if (first_bt_system_reset == true) {
      // Execute this part only after first reset
      first_bt_system_reset = false;

      aoa_address_to_id(address.addr, address_type, locator_id);

      // Connect to the MQTT broker
      mqtt_handle.client_id = locator_id;
      sc = mqtt_init(&mqtt_handle);
      app_assert_status(sc);

      mqtt_handle.on_message = on_message;

      aoa_angle_add_config(locator_id, NULL);

      // Parse config file if given
      if (config_file != NULL) {
        parse_config_file(config_file);
      }

      subscribe_correction();
      subscribe_config();
    }
  }
  // ...then call the CTE specific event handler.
  sc = aoa_cte_bt_on_event(evt);
  app_assert_status(sc);
}

/**************************************************************************//**
 * Subscribe for config topic.
 *****************************************************************************/
static void subscribe_config(void)
{
  const char topic_template[] = AOA_TOPIC_CONFIG_PRINT;
  char topic[sizeof(topic_template) + sizeof(aoa_id_t) + 1];
  sl_status_t sc;

  snprintf(topic, sizeof(topic), topic_template, locator_id);

  app_log("Subscribing to topic '%s'." APP_LOG_NL, topic);

  sc = mqtt_subscribe(&mqtt_handle, topic);
  app_assert_status(sc);
}

/**************************************************************************//**
 * Subscribe for angle feedback messages from the positioning node.
 *****************************************************************************/
static void subscribe_correction(void)
{
  const char topic_template[] = AOA_TOPIC_CORRECTION_PRINT;
  char topic[sizeof(topic_template) + sizeof(aoa_id_t) + 1];
  sl_status_t sc;

  snprintf(topic, sizeof(topic), topic_template, locator_id, "+");

  app_log("Subscribing to topic '%s'." APP_LOG_NL, topic);

  sc = mqtt_subscribe(&mqtt_handle, topic);
  app_assert_status(sc);
}

/**************************************************************************//**
 * Check the received topic
 *****************************************************************************/
static sl_status_t check_config_topic(const char* topic_literal,
                                      const char* topic,
                                      size_t topic_size)
{
  char topic_buffer[sizeof(topic_literal) + sizeof(aoa_id_t)];

  snprintf(topic_buffer, sizeof(topic_buffer), topic_literal, locator_id);

  if (strncmp(topic_buffer, topic, topic_size) == 0) {
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_NOT_FOUND;
  }
}

/**************************************************************************//**
 * MQTT message arrived callback.
 *****************************************************************************/
static void on_message(mqtt_handle_t *handle,
                       const char *topic,
                       const char *payload)
{
  int result;
  aoa_id_t loc_id, tag_id;
  aoa_correction_t correction;
  bd_addr tag_addr;
  uint8_t tag_addr_type;
  aoa_db_entry_t *tag = NULL;
  enum sl_rtl_error_code ec;
  sl_status_t sc;
  aoa_angle_config_t *angle_config = NULL;

  sc = aoa_angle_get_config(locator_id, &angle_config);
  app_assert_status(sc);

  (void)handle;

  if (check_config_topic(AOA_TOPIC_CONFIG_PRINT,
                         topic,
                         sizeof(AOA_TOPIC_CONFIG_PRINT)) == SL_STATUS_OK) {
    parse_config(payload);

    app_log_info("Resetting NCP target..." APP_LOG_NL);
    app_log_nl();

    sl_bt_system_reset(sl_bt_system_boot_mode_normal);
  } else if (report_mode == ANGLE) {
    // Parse topic
    result = sscanf(topic, AOA_TOPIC_CORRECTION_SCAN, loc_id, tag_id);
    app_assert(result == 2,
               "Failed to parse correction topic: %d." APP_LOG_NL,
               result);

    if (aoa_id_compare(loc_id, locator_id) != 0) {
      // Accidentally got a wrong message
      return;
    }
    // Find asset tag in the database
    sc = aoa_id_to_address(tag_id, tag_addr.addr, &tag_addr_type);
    if (SL_STATUS_OK == sc) {
      sc = aoa_db_get_tag_by_address(&tag_addr, &tag);
    }
    if (SL_STATUS_OK == sc) {
      // Parse payload
      sc = aoa_deserialize_correction((char *)payload, &correction);
      app_assert_status(sc);

      if (aoa_sequence_compare(tag->sequence, correction.sequence)
          <= angle_config->angle_correction_delay) {
        app_log("Apply correction #%d for asset tag '%s'" APP_LOG_NL,
                correction.sequence,
                tag_id);
        ec = aoa_set_correction((aoa_state_t *)tag->user_data,
                                &correction,
                                locator_id);
        app_assert(ec == SL_RTL_ERROR_SUCCESS,
                   "[E: %d] Failed to set correction values" APP_LOG_NL,
                   ec);
      } else {
        app_log("Omit correction #%d for asset tag '%s'" APP_LOG_NL,
                correction.sequence,
                tag_id);
      }
    }
  }
}

/**************************************************************************//**
 * IQ report callback.
 *****************************************************************************/
void aoa_cte_on_iq_report(aoa_db_entry_t *tag, aoa_iq_report_t *iq_report)
{
  aoa_id_t tag_id;
  sl_status_t sc;
  char *payload;
  char *topic_template;
  char *topic;
  size_t size;
  enum sl_rtl_error_code ec;
  aoa_angle_t angle;

  if (report_mode == IQ_REPORT) {
    size = sizeof(AOA_TOPIC_IQ_REPORT_PRINT);
    topic_template = AOA_TOPIC_IQ_REPORT_PRINT;

    // Compile payload
    sc = aoa_serialize_iq_report(iq_report, &payload);
  } else {
    size = sizeof(AOA_TOPIC_ANGLE_PRINT);
    topic_template = AOA_TOPIC_ANGLE_PRINT;

    ec = aoa_calculate((aoa_state_t *)tag->user_data,
                       iq_report,
                       &angle,
                       locator_id);

    if (ec == SL_RTL_ERROR_ESTIMATION_IN_PROGRESS) {
      // No valid angles are available yet.
      return;
    }
    app_assert(ec == SL_RTL_ERROR_SUCCESS,
               "[E: %d] Failed to calculate angle." APP_LOG_NL,
               ec);

    // Store the latest sequence number for the tag.
    tag->sequence = iq_report->event_counter;

    // Compile payload
    sc = aoa_serialize_angle(&angle, &payload);
  }
  app_assert(sc == SL_STATUS_OK,
             "[E: 0x%04x] Failed to serialize the payload." APP_LOG_NL,
             (int)sc);

  // Compile topic
  size += (2 * sizeof(aoa_id_t));
  topic = malloc(size);
  app_assert(NULL != topic, "Failed to allocate memory for the MQTT topic.");
  aoa_address_to_id(tag->address.addr, tag->address_type, tag_id);
  snprintf(topic, size, topic_template, locator_id, tag_id);

  // Send message
  sc = mqtt_publish(&mqtt_handle, topic, payload, false);
  app_assert_status(sc);

  // Clean up
  free(payload);
  free(topic);
}

/**************************************************************************//**
 * Configuration file parser
 *****************************************************************************/
static void parse_config_file(const char *file_name)
{
  char *buffer;
  buffer = aoa_parse_load_file(file_name);
  app_assert(buffer != NULL, "Failed to load file: %s\n", file_name);
  parse_config(buffer);
  free(buffer);
}

/**************************************************************************//**
 * Configuration parser
 *****************************************************************************/
static void parse_config(const char *config)
{
  aoa_id_t allow_id;
  sl_status_t sc;
  uint8_t address[ADR_LEN];
  uint8_t address_type;
  aoa_angle_config_t *angle_config = NULL;
  float mask_min = 0;
  float mask_max = 0;
  aoa_cte_type_t cte_mode;

  sc = aoa_angle_get_config(locator_id,
                            &angle_config);

  if (SL_STATUS_OK != sc) {
    return;
  }

  // Remove all tags from the db.
  // It will be reinitialized when
  // new data arrives.
  aoa_db_remove_all();

  sc = aoa_parse_init(config);
  app_assert_status(sc);

  app_log(APP_LOG_NEW_LINE);
  app_log_info("Start parsing configuration..." APP_LOG_NL);

  sc = aoa_parse_aox_mode(&angle_config->aox_mode, locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("AoX mode set to: %s" APP_LOG_NL,
                 aox_mode_string[angle_config->aox_mode]);
  }

  sc = aoa_parse_antenna_mode(&angle_config->array_type, locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("Antenna mode set to: %s" APP_LOG_NL,
                 antenna_type_string[angle_config->array_type]);
  }

  sc = aoa_parse_antenna_array(&aoa_cte_config.switching_pattern,
                               &aoa_cte_config.switching_pattern_length,
                               locator_id);

  if (sc == SL_STATUS_OK) {
    sc = aoa_parse_antenna_array(&angle_config->switching_pattern,
                                 &angle_config->switching_pattern_length,
                                 locator_id);
    if (sc == SL_STATUS_OK) {
      app_log_info("Antenna array set to:{");
      for (uint8_t i = 0; i < aoa_cte_config.switching_pattern_length; i++) {
        app_log("%d,", aoa_cte_config.switching_pattern[i]);
      }
      app_log("}" APP_LOG_NL);
    }
  }

  sc = aoa_parse_angle_filtering(&angle_config->angle_filtering, locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("Angle filtering set to: %s" APP_LOG_NL,
                 angle_config->angle_filtering ? "enabled" : "disabled");
  }

  sc = aoa_parse_angle_filtering_weight(&angle_config->angle_filtering_weight,
                                        locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("Angle filtering weight set to: %f" APP_LOG_NL,
                 angle_config->angle_filtering_weight);
  }

  sc = aoa_parse_simple_config(&angle_config->period_samples,
                               "periodSamples",
                               locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("Sample period set to: %d" APP_LOG_NL,
                 angle_config->period_samples);
  }

  sc = aoa_parse_simple_config(&angle_config->angle_correction_timeout,
                               "angleCorrectionTimeout",
                               locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("Angle correction timeout set to: %d" APP_LOG_NL,
                 angle_config->angle_correction_timeout);
  }

  sc = aoa_parse_simple_config(&angle_config->angle_correction_delay,
                               "angleCorrectionDelay",
                               locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("Angle correction delay set to: %d" APP_LOG_NL,
                 angle_config->angle_correction_delay);
  }

  sc = aoa_parse_cte_mode(&cte_mode, locator_id);
  if (sc == SL_STATUS_OK) {
    aoa_cte_set_mode(cte_mode);
    app_log_info("CTE mode set to: %s" APP_LOG_NL,
                 cte_mode == AOA_CTE_TYPE_SILABS
                 ? "SILABS" : cte_mode == AOA_CTE_TYPE_CONN
                 ? "CONN" : "CONNLESS");
  }

  sc = aoa_parse_simple_config(&aoa_cte_config.cte_sampling_interval,
                               "cteSamplingInterval",
                               locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("CTE sampling interval set to: %d" APP_LOG_NL,
                 aoa_cte_config.cte_sampling_interval);
  }

  sc = aoa_parse_simple_config(&aoa_cte_config.cte_min_length,
                               "cteLength",
                               locator_id);
  if (sc == SL_STATUS_OK) {
    angle_config->cte_min_length = aoa_cte_config.cte_min_length;
    app_log_info("CTE length set to: %d" APP_LOG_NL,
                 aoa_cte_config.cte_min_length);
  }

  sc = aoa_parse_simple_config(&aoa_cte_config.cte_slot_duration,
                               "slotDuration",
                               locator_id);
  if (sc == SL_STATUS_OK) {
    angle_config->cte_slot_duration = aoa_cte_config.cte_slot_duration;
    app_log_info("CTE slot duration set to: %d" APP_LOG_NL,
                 aoa_cte_config.cte_slot_duration);
  }

  sc = aoa_parse_report_mode(&report_mode, locator_id);
  if (sc == SL_STATUS_OK) {
    app_log_info("Report mode set to: %s" APP_LOG_NL,
                 report_mode == ANGLE ? "ANGLE" : "IQ_REPORT");
  }

  if (SL_STATUS_OK == aoa_parse_check_config_exist("allowlist", locator_id)) {
    aoa_db_allowlist_reset();
    do {
      sc = aoa_parse_allowlist(address, &address_type, locator_id);
      if (sc == SL_STATUS_OK) {
        aoa_address_to_id(address, address_type, allow_id);
        app_log_info("Adding tag id '%s' to the allowlist." APP_LOG_NL,
                     allow_id);
        sc = aoa_db_allowlist_add(address);
      } else {
        app_assert(sc == SL_STATUS_NOT_FOUND,
                   "[E: 0x%04x] aoa_parse_allowlist failed\n",
                   (int)sc);
      }
    } while (sc == SL_STATUS_OK);
  }

  if (SL_STATUS_OK == aoa_parse_check_config_exist("azimuthMask", locator_id)) {
    aoa_angle_reset_azimuth_masks(locator_id);
    do {
      sc = aoa_parse_azimuth(&mask_min,
                             &mask_max,
                             locator_id);
      if (sc == SL_STATUS_OK) {
        sc = aoa_angle_add_azimuth_mask(locator_id, mask_min, mask_max);
        app_assert_status(sc);
        app_log_info("Azimuth mask added: min: %f, max: %f" APP_LOG_NL,
                     mask_min, mask_max);
      }
    } while (sc == SL_STATUS_OK);
  }

  if (SL_STATUS_OK == aoa_parse_check_config_exist("elevationMask", locator_id)) {
    aoa_angle_reset_elevation_masks(locator_id);
    do {
      sc = aoa_parse_elevation(&mask_min,
                               &mask_max,
                               locator_id);
      if (sc == SL_STATUS_OK) {
        sc = aoa_angle_add_elevation_mask(locator_id, mask_min, mask_max);
        app_assert_status(sc);
        app_log_info("Elevation mask added: min: %f, max: %f" APP_LOG_NL,
                     mask_min,
                     mask_max);
      }
    } while (sc == SL_STATUS_OK);
  }

  sc = aoa_angle_finalize_config(locator_id);
  app_assert_status(sc);

  sc = aoa_parse_deinit();
  app_assert_status(sc);
}

/**************************************************************************//**
 * Tag added callback.
 *****************************************************************************/
void aoa_db_on_tag_added(aoa_db_entry_t *tag)
{
  size_t tags = 0;
  tags = aoa_db_get_number_of_tags();

  tag->user_data = malloc(sizeof(aoa_state_t));
  app_assert(NULL != tag->user_data,
             "Failed to allocate memory for aoa state.");

  enum sl_rtl_error_code ec = aoa_init_rtl((aoa_state_t *)tag->user_data,
                                           locator_id);

  app_assert(ec == SL_RTL_ERROR_SUCCESS,
             "[E: %d] aoa_init_rtl failed" APP_LOG_NL,
             ec);

  app_log("New tag added (%zu): %02X:%02X:%02X:%02X:%02X:%02X" APP_LOG_NL,
          tags,
          tag->address.addr[5],
          tag->address.addr[4],
          tag->address.addr[3],
          tag->address.addr[2],
          tag->address.addr[1],
          tag->address.addr[0]);
}

/**************************************************************************//**
 * Tag removed callback.
 *****************************************************************************/
void aoa_db_on_tag_removed(aoa_db_entry_t *tag)
{
  enum sl_rtl_error_code ec = aoa_deinit_rtl((aoa_state_t *)tag->user_data,
                                             locator_id);
  app_assert(ec == SL_RTL_ERROR_SUCCESS,
             "[E: %d] aoa_deinit_rtl failed" APP_LOG_NL, ec);
  free(tag->user_data);
  app_log("Tag removed: %02X:%02X:%02X:%02X:%02X:%02X" APP_LOG_NL,
          tag->address.addr[5],
          tag->address.addr[4],
          tag->address.addr[3],
          tag->address.addr[2],
          tag->address.addr[1],
          tag->address.addr[0]);
}

/***************************************************************************//**
 * @file
 * @brief AoA positioning.
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

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "app.h"
#include "app_log.h"
#include "app_log_cli.h"
#include "app_assert.h"
#include "mqtt.h"

#include "aoa_util.h"
#include "aoa_topics.h"
#include "aoa_parse.h"
#include "aoa_serdes.h"
#include "aoa_loc.h"
#include "angle_queue.h"
#include "aoa_angle.h"
#include "aoa_angle_config.h"

// -----------------------------------------------------------------------------
// Private macros

// Optstring argument for getopt.
#define OPTSTRING APP_LOG_OPTSTRING "m:c:nh"

// Usage info.
#define USAGE          APP_LOG_NL "%s [-m <mqtt_address>[:<port>]] [-c <config>] [-n] [-h]" APP_LOG_USAGE APP_LOG_NL

// Options info.
#define OPTIONS                                                                \
  "\nOPTIONS\n"                                                                \
  "    -m  MQTT broker connection parameters.\n"                               \
  "        <mqtt_address>   Address of the MQTT broker (default: localhost)\n" \
  "        <port>           Port of the MQTT broker (default: 1883)\n"         \
  "    -c  Positioning configuration file.\n"                                  \
  "        <config>         Path to the configuration file\n"                  \
  "    -n  Turn off the bad angle feedback feature.\n"                         \
  APP_LOG_OPTIONS                                                              \
  "    -h  Print this help message.\n"

// -----------------------------------------------------------------------------
// Private variables
static mqtt_handle_t mqtt_handle = MQTT_DEFAULT_HANDLE;
static aoa_id_t positioning_id = "";
static aoa_report_mode_t *loc_report_mode = NULL;

// Location estimation mode strings
static const char *loc_est_mode_string[] = {
  "SL_RTL_LOC_ESTIMATION_MODE_TWO_DIM_FAST_RESPONSE",
  "SL_RTL_LOC_ESTIMATION_MODE_THREE_DIM_FAST_RESPONSE",
  "SL_RTL_LOC_ESTIMATION_MODE_TWO_DIM_HIGH_ACCURACY",
  "SL_RTL_LOC_ESTIMATION_MODE_THREE_DIM_HIGH_ACCURACY"
};

// Location validation mode strings
static const char *loc_val_mode_string[] = {
  "SL_RTL_LOC_MEASUREMENT_VALIDATION_MINIMUM",
  "SL_RTL_LOC_MEASUREMENT_VALIDATION_MEDIUM",
  "SL_RTL_LOC_MEASUREMENT_VALIDATION_FULL"
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

// -----------------------------------------------------------------------------
// Private function declarations
static void parse_config_file(const char *filename);
static void parse_config(const char *payload);
static void on_message(mqtt_handle_t *handle,
                       const char *topic,
                       const char *payload);
static void subscribe_topic(char *topic_template,
                            size_t topic_size,
                            aoa_locator_t *loc);
static void subscribe_config(void);
static sl_status_t check_config_topic(const char* topic);
static void angle_queue_on_angles_ready(aoa_id_t tag_id,
                                        uint32_t angle_count,
                                        aoa_angle_t *angle_list,
                                        aoa_id_t *locator_list);

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(int argc, char *argv[])
{
  sl_status_t sc;
  int opt;
  char *port_str = NULL;
  char *config_file = NULL;

  // Process command line options.
  while ((opt = getopt(argc, argv, OPTSTRING)) != -1) {
    switch (opt) {
      // Configuration file.
      case 'c':
        config_file = optarg;
        break;

      // MQTT broker connection parameters.
      case 'm':
        mqtt_handle.host = strtok(optarg, ":");
        port_str = strtok(NULL, ":");
        if (port_str != NULL) {
          mqtt_handle.port = atoi(port_str);
        }
        break;

      // Turn off the bad angle feedback feature.
      case 'n':
        aoa_loc_config.is_feedback_enabled = false;
        break;

      // Print help.
      case 'h':
        app_log(USAGE, argv[0]);
        app_log(OPTIONS);
        exit(EXIT_SUCCESS);

      // Process options for other modules.
      default:
        sc = app_log_set_option((char)opt, optarg);
        if (sc != SL_STATUS_OK) {
          app_log(USAGE, argv[0]);
          exit(EXIT_FAILURE);
        }
    }
  }

  // Configuration file is mandatory.
  if (config_file == NULL) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  parse_config_file(config_file);

  app_log("Press Crtl+C to quit" APP_LOG_NL APP_LOG_NL);
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void)
{
  sl_status_t sc;
  sc = mqtt_step(&mqtt_handle);
  app_assert_status(sc);
}

/**************************************************************************//**
 * Application Deinit.
 *****************************************************************************/
void app_deinit(void)
{
  sl_status_t sc;
  sc = mqtt_deinit(&mqtt_handle);
  app_assert_status(sc);

  aoa_loc_destroy();
  angle_queue_deinit();
}

/**************************************************************************//**
 * Configuration file parser
 *****************************************************************************/
static void parse_config_file(const char *filename)
{
  char *buffer;
  buffer = aoa_parse_load_file(filename);
  app_assert(buffer != NULL, "Failed to load file: %s" APP_LOG_NL, filename);
  parse_config(buffer);
  free(buffer);
}

/**************************************************************************//**
 * Configuration parser.
 *****************************************************************************/
static void parse_config(const char *payload)
{
  sl_status_t sc;
  aoa_locator_t *loc;
  aoa_id_t locator_id;
  struct sl_rtl_loc_locator_item item;
  aoa_angle_config_t *angle_config;
  angle_queue_config_t angle_queue_config = ANGLE_QUEUE_DEFAULT_CONFIG;
  float mask_min = 0;
  float mask_max = 0;
  uint8_t *antenna_switch_pattern = NULL;
  uint8_t antenna_switch_pattern_size = 0;
  enum sl_rtl_aox_array_type antenna_array_type;

  sc = aoa_parse_init(payload);
  app_assert_status(sc);

  sc = aoa_parse_positioning(positioning_id);
  app_assert_status(sc);

  if (positioning_id != mqtt_handle.client_id) {
    mqtt_handle.on_message = on_message;
    mqtt_handle.client_id = positioning_id;

    sc = mqtt_init(&mqtt_handle);
    app_assert_status(sc);
    app_log_nl();
  }
  subscribe_config();

  aoa_loc_destroy();
  aoa_angle_reset_configs();
  angle_queue_deinit();

  sc = aoa_loc_init();
  app_assert_status(sc);

  angle_queue_config.on_angles_ready = &angle_queue_on_angles_ready;

  app_log_info("Parsing positioning configuration:"  APP_LOG_NL);
  app_log_nl();
  sc = aoa_parse_loc_estimation_mode(&aoa_loc_config.estimation_mode);
  if (sc == SL_STATUS_OK) {
    app_log_info("Location estimation mode set to: %s" APP_LOG_NL,
                 loc_est_mode_string[aoa_loc_config.estimation_mode]);
  }

  sc = aoa_parse_loc_validation_mode(&aoa_loc_config.validation_method);
  if (sc == SL_STATUS_OK) {
    app_log_info("Location validation mode set to: %s" APP_LOG_NL,
                 loc_val_mode_string[aoa_loc_config.validation_method]);
  }

  sc = aoa_parse_float_config(&aoa_loc_config.estimation_interval_sec,
                              "estimationIntervalSec");
  if (sc == SL_STATUS_OK) {
    app_log_info("Location estimation interval set to: %f" APP_LOG_NL,
                 aoa_loc_config.estimation_interval_sec);
  }

  sc = aoa_parse_bool_config(&aoa_loc_config.filtering_enabled,
                             "locationFiltering");
  if (sc == SL_STATUS_OK) {
    app_log_info("Location filtering filtering set to: %s" APP_LOG_NL,
                 aoa_loc_config.filtering_enabled ? "enabled" : "disabled");
  }

  sc = aoa_parse_float_config(&aoa_loc_config.filtering_amount,
                              "locationFilteringWeight");
  if (sc == SL_STATUS_OK) {
    app_log_info("Location filtering weight set to: %f" APP_LOG_NL,
                 aoa_loc_config.filtering_amount);
  }

  sc = aoa_parse_uint32_config(&angle_queue_config.sequence_ids,
                               "numberOfSequenceIds");
  if (sc == SL_STATUS_OK) {
    app_log_info("Sequence id slots set to: %d" APP_LOG_NL,
                 angle_queue_config.sequence_ids);
  }

  sc = aoa_parse_uint32_config(&angle_queue_config.max_sequence_diff,
                               "maximumSequenceIdDiffs");
  if (sc == SL_STATUS_OK) {
    app_log_info("Maximum sequence id difference set to: %d" APP_LOG_NL,
                 angle_queue_config.max_sequence_diff);
  }

  aoa_loc_config.max_sequence_diff = angle_queue_config.max_sequence_diff;

  app_log_nl();
  app_log_info("Parsing locator configurations:" APP_LOG_NL);
  while (aoa_parse_locator(locator_id, &item) == SL_STATUS_OK) {
    app_log_nl();
    sc = aoa_loc_add_locator(locator_id, item, &loc);
    app_assert_status_f(sc, "Failed to allocate memory for locator");
    sc = aoa_angle_add_config(locator_id, &angle_config);
    app_assert_status_f(sc, "Failed to allocate memory for locator");
    app_log_info("Locator added:" APP_LOG_NL);
    app_log_info("id: %s," APP_LOG_NL, loc->id);
    app_log_info("coordinate: %f %f %f" APP_LOG_NL,
                 loc->item.coordinate_x,
                 loc->item.coordinate_y,
                 loc->item.coordinate_z);
    app_log_info("orientation: %f %f %f" APP_LOG_NL,
                 loc->item.orientation_x_axis_degrees,
                 loc->item.orientation_y_axis_degrees,
                 loc->item.orientation_z_axis_degrees);

    app_log_nl();
    sc = aoa_parse_aox_mode(&angle_config->aox_mode, locator_id);
    if (sc == SL_STATUS_OK) {
      app_log_info("AoX mode set to: %s" APP_LOG_NL,
                   aox_mode_string[angle_config->aox_mode]);
    }

    sc = aoa_parse_antenna_mode(&antenna_array_type, locator_id);
    if (sc == SL_STATUS_OK) {
      app_log_info("Antenna mode set to: %s" APP_LOG_NL,
                   antenna_type_string[antenna_array_type]);
      sc = antenna_array_init(&angle_config->antenna_array, antenna_array_type);
      if (sc != SL_STATUS_OK) {
        app_log_status_error_f(sc,
                               "antenna_array_init failed for %s" APP_LOG_NL,
                               antenna_type_string[antenna_array_type]);
      }
    }

    sc = aoa_parse_antenna_array(&antenna_switch_pattern,
                                 &antenna_switch_pattern_size,
                                 locator_id);
    if (sc == SL_STATUS_OK) {
      sc = antenna_array_set_pattern(&angle_config->antenna_array,
                                     antenna_switch_pattern,
                                     antenna_switch_pattern_size);
      if (sc == SL_STATUS_OK) {
        app_log_info("Antenna array set to:");
        if (_app_log_check_level(APP_LOG_LEVEL_INFO)) {
          for (uint8_t i = 0; i < antenna_switch_pattern_size; i++) {
            app_log(" %d", antenna_switch_pattern[i]);
          }
          app_log_nl();
        }
      } else {
        app_log_status_error_f(sc,
                               "antenna_array_set_pattern failed with size %d" APP_LOG_NL,
                               antenna_switch_pattern_size);
      }
      free(antenna_switch_pattern);
    }

    sc = aoa_parse_simple_config(&angle_config->cte_min_length,
                                 "cteLength",
                                 locator_id);
    if (sc == SL_STATUS_OK) {
      app_log_info("CTE length set to: %d" APP_LOG_NL,
                   angle_config->cte_min_length);
    }

    sc = aoa_parse_simple_config(&angle_config->cte_slot_duration,
                                 "slotDuration",
                                 locator_id);
    if (sc == SL_STATUS_OK) {
      app_log_info("CTE slot duration set to: %d" APP_LOG_NL,
                   angle_config->cte_slot_duration);
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
  }
  app_log_nl();
  aoa_loc_config.locator_count = aoa_loc_get_number_of_locators();

  // If no locator configured, just wait for MQTT config
  if (0 != aoa_loc_config.locator_count) {
    angle_queue_config.locator_count = aoa_loc_config.locator_count;
    loc_report_mode = (aoa_report_mode_t *)realloc(loc_report_mode,
                                                   aoa_loc_config.locator_count
                                                   * sizeof(aoa_report_mode_t));
    sc = aoa_loc_finalize_config();
    app_assert_status(sc);

    for (uint32_t i = 0; i < aoa_loc_config.locator_count; i++) {
      aoa_loc_get_locator_by_index(i, &loc);
      sc = aoa_parse_report_mode(&loc_report_mode[i], loc->id);

      subscribe_topic(AOA_TOPIC_ANGLE_PRINT,
                      sizeof(AOA_TOPIC_ANGLE_PRINT),
                      loc);

      subscribe_topic(AOA_TOPIC_IQ_REPORT_PRINT,
                      sizeof(AOA_TOPIC_IQ_REPORT_PRINT),
                      loc);
    }
    sc = angle_queue_init(&angle_queue_config);
    app_assert_status(sc);
  }

  app_log_nl();
  app_log_info("Locator count: %d" APP_LOG_NL, aoa_loc_config.locator_count);

  sc = aoa_parse_deinit();
  app_assert_status(sc);
}

/**************************************************************************//**
 * Subscribe for a topic.
 *****************************************************************************/
static void subscribe_topic(char *topic_template,
                            size_t topic_size,
                            aoa_locator_t *loc)
{
  sl_status_t sc;
  size_t size = (topic_size + sizeof(aoa_id_t) + 1);
  char *topic = malloc(size);
  app_assert(NULL != topic, "Failed to allocate memory for MQTT topic.");

  snprintf(topic, size, topic_template, loc->id, "+");

  app_log_info("Subscribing to topic '%s'." APP_LOG_NL, topic);

  sc = mqtt_subscribe(&mqtt_handle, topic);
  app_assert_status(sc);
  free(topic);
}

/**************************************************************************//**
 * Subscribe for config topic.
 *****************************************************************************/
static void subscribe_config(void)
{
  const char topic_template[] = AOA_TOPIC_CONFIG_PRINT;
  char topic[sizeof(topic_template) + sizeof(aoa_id_t) + 1];
  sl_status_t sc;

  snprintf(topic, sizeof(topic), topic_template, positioning_id);

  app_log_info("Subscribing to topic '%s'." APP_LOG_NL, topic);

  sc = mqtt_subscribe(&mqtt_handle, topic);
  app_assert_status(sc);
}

/**************************************************************************//**
 * Check the received topic
 *****************************************************************************/
static sl_status_t check_config_topic(const char* topic)
{
  char topic_buffer[sizeof(AOA_TOPIC_CONFIG_PRINT) + sizeof(aoa_id_t)];

  snprintf(topic_buffer,
           sizeof(topic_buffer),
           AOA_TOPIC_CONFIG_PRINT,
           positioning_id);

  if (strncmp(topic_buffer, topic, sizeof(AOA_TOPIC_CONFIG_PRINT)) == 0) {
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
  aoa_id_t loc_id;
  aoa_id_t tag_id;
  uint32_t locator_idx;
  aoa_asset_tag_t *tag;
  aoa_locator_t *locator;
  aoa_angle_t angle;
  sl_status_t sc;
  aoa_iq_report_t iq_report;
  int8_t samples[256];
  aoa_report_mode_t report_mode = ANGLE;

  (void)handle;

  if (check_config_topic(topic) == SL_STATUS_OK) {
    // Unsubscribe from all topics
    sc = mqtt_unsubscribe_all(&mqtt_handle);
    app_assert_status(sc);
    parse_config(payload);
    return;
  }

  // Parse topic.
  if (2 != sscanf(topic, AOA_TOPIC_ANGLE_SCAN, loc_id, tag_id)) {
    result = sscanf(topic, AOA_TOPIC_IQ_REPORT_SCAN, loc_id, tag_id);
    app_assert(result == 2, "Failed to parse topic: %d." APP_LOG_NL, result);
    report_mode = IQ_REPORT;
  }

  // Find locator.
  sc = aoa_loc_get_locator_by_id(loc_id, &locator_idx, &locator);
  if (sc != SL_STATUS_OK) {
    // Locator not found.
    return;
  }

  // Update the report mode.
  loc_report_mode[locator_idx] = report_mode;

  // Find asset tag.
  sc = aoa_loc_get_tag_by_id(tag_id, &tag);
  if (SL_STATUS_NOT_FOUND == sc) {
    // Add new tag
    sc = aoa_loc_add_asset_tag(tag_id, &tag);
    app_assert_status_f(sc,
                        "[E: 0x%04x] Failed to add tag %s." APP_LOG_NL,
                        sc,
                        tag_id);

    app_log_info("New tag added : %s \n", tag_id);
  }

  if (IQ_REPORT == loc_report_mode[locator_idx]) {
    iq_report.samples = samples;

    // Parse payload.
    sc = aoa_deserialize_iq_report((char *)payload, &iq_report);
    app_assert_status(sc);

    // Convert IQ report to angle.
    enum sl_rtl_error_code ec = aoa_calculate((aoa_state_t *)tag->aoa_state
                                              + locator_idx,
                                              &iq_report,
                                              &angle,
                                              loc_id);
    if (ec == SL_RTL_ERROR_ESTIMATION_IN_PROGRESS) {
      // No valid angles are available yet.
      return;
    }
    app_assert_s(ec == SL_RTL_ERROR_SUCCESS);
  } else {
    // Parse payload.
    sc = aoa_deserialize_angle((char *)payload, &angle);
    app_assert_status(sc);
  }

  // Add new data to the angle queue
  sc = angle_queue_push(tag->id,
                        locator->id,
                        &angle);

  app_assert_status_f(sc,
                      "[E: 0x%04x] Failed to add data \
                      to the angle queue %s." APP_LOG_NL,
                      sc,
                      tag_id);
}

/**************************************************************************//**
 * Angles ready callback for angle queue.
 *****************************************************************************/
static void angle_queue_on_angles_ready(aoa_id_t tag_id,
                                        uint32_t angle_count,
                                        aoa_angle_t *angle_list,
                                        aoa_id_t *locator_list)
{
  sl_status_t sc;

  sc = aoa_loc_calc_position(tag_id,
                             angle_count,
                             angle_list,
                             locator_list);

  app_assert_status(sc);
}

/**************************************************************************//**
 * Callback from the locator engine, position calculation done.
 *****************************************************************************/
void aoa_loc_on_position_ready(aoa_asset_tag_t *tag)
{
  sl_status_t sc;
  char *payload;
  const char topic_template[] = AOA_TOPIC_POSITION_PRINT;
  char topic[sizeof(topic_template) + sizeof(aoa_id_t) + sizeof(aoa_id_t)];

  // Compile topic.
  snprintf(topic, sizeof(topic), topic_template, positioning_id, tag->id);

  // Compile payload.
  sc = aoa_serialize_position(&tag->position, &payload);
  app_assert_status(sc);

  sc = mqtt_publish(&mqtt_handle, topic, payload, false);
  app_assert_status(sc);

  // Clean up.
  free(payload);
}

/**************************************************************************//**
 * Initializes the angle calculation for the tag.
 *****************************************************************************/
void aoa_loc_angle_init(aoa_asset_tag_t *tag, uint32_t locator_count)
{
  enum sl_rtl_error_code ec;
  aoa_locator_t *locator;
  sl_status_t sc;

  tag->aoa_state = (aoa_state_t *)malloc(locator_count * sizeof(aoa_state_t));
  app_assert(NULL != tag->aoa_state,
             "Failed to allocate memory for tag AoA state.");
  for (uint32_t i = 0; i < locator_count; i++) {
    sc = aoa_loc_get_locator_by_index(i, &locator);
    app_assert_status(sc);
    ec = aoa_init_rtl((aoa_state_t *)tag->aoa_state + i, locator->id);
    app_assert(ec == SL_RTL_ERROR_SUCCESS,
               "[E: %d] Failed to init angle calculation." APP_LOG_NL,
               ec);
  }
}

/**************************************************************************//**
 * Deinitializes the angle calculation for the tag.
 *****************************************************************************/
void aoa_loc_angle_deinit(aoa_asset_tag_t *tag, uint32_t locator_count)
{
  enum sl_rtl_error_code ec;
  aoa_locator_t *locator;
  sl_status_t sc;

  for (uint32_t i = 0; i < locator_count; i++) {
    sc = aoa_loc_get_locator_by_index(i, &locator);
    app_assert_status(sc);
    ec = aoa_deinit_rtl((aoa_state_t *)tag->aoa_state + i, locator->id);
    app_assert(ec == SL_RTL_ERROR_SUCCESS,
               "[E: %d] Failed to deinit angle calculation." APP_LOG_NL,
               ec);
  }
  free(tag->aoa_state);
}

/**************************************************************************//**
 * Callback from the locator engine, correction calculation done.
 *****************************************************************************/
void aoa_loc_on_correction_ready(aoa_asset_tag_t *tag,
                                 int32_t sequence,
                                 aoa_id_t loc_id,
                                 uint32_t loc_idx,
                                 aoa_correction_t *correction)
{
  enum sl_rtl_error_code ec;
  sl_status_t sc;
  char *payload;
  const char topic_template[] = AOA_TOPIC_CORRECTION_PRINT;
  char topic[sizeof(topic_template) + sizeof(aoa_id_t) + sizeof(aoa_id_t)];

  if (IQ_REPORT == loc_report_mode[loc_idx]) {
    // The first angle in the correlated angle list is the most recent one.
    if (aoa_sequence_compare(sequence, correction->sequence)
        <= AOA_ANGLE_MAX_CORRECTION_DELAY) {
      app_log_info("Apply correction #%d for asset tag '%s', locator '%s'" APP_LOG_NL,
                   correction->sequence,
                   tag->id,
                   loc_id);
      ec = aoa_set_correction((aoa_state_t *)tag->aoa_state + loc_idx,
                              correction,
                              loc_id);
      app_assert(ec == SL_RTL_ERROR_SUCCESS,
                 "[E: %d] Failed to set correction values" APP_LOG_NL, ec);
    } else {
      app_log_info("Omit correction #%d for asset tag '%s'" APP_LOG_NL,
                   correction->sequence,
                   tag->id);
    }
  } else {
    // Compile topic
    snprintf(topic, sizeof(topic), topic_template, loc_id, tag->id);

    // Compile payload
    sc = aoa_serialize_correction(correction, &payload);
    app_assert_status(sc);

    sc = mqtt_publish(&mqtt_handle, topic, payload, false);
    app_assert_status(sc);

    // Clean up
    free(payload);
  }
}

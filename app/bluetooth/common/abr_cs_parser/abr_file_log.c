/***************************************************************************//**
 * @file
 * @brief ABR file logger
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
#if defined(HOST_TOOLCHAIN) && (ABR_FILE_LOG_ENABLED == 1)

#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "cJSON.h"
#include "abr_file_log.h"
#include "abr_file_log_config.h"
#include "sl_malloc.h"
#include "sl_status.h"
#include "app_log.h"
#include "abr_cs_parser_types.h"
#include "abr_cs_parser_config.h"
#include <sys/stat.h>
// Multiplatform getcwd function
#ifdef _WIN32
#include <direct.h>
#define get_current_dir                      _getcwd
#else
#include <unistd.h>
#define get_current_dir                      getcwd
#endif

// -----------------------------------------------------------------------------
// Defines

#define LOG_FILE_VERSION                     1
#define FILENAME_STRLEN                      1024
#define DIR_STRLEN                           FILENAME_STRLEN
#define PATH_STRLEN                          (FILENAME_STRLEN * 2)
#define MAX_STRLEN                           FILENAME_STRLEN
#define TIME_STRLEN                          50UL
#define NANOSEC_DIVIDER                      (double)0.000000001
#define CHANNEL_MAP_LEN                      10

// File section literals
// *INDENT-OFF*
#define FILE_EXTENSION                       ".jsonl"

#define LOGGER_TITLE                         "JSON logger"

// jsonl fields
#define HDR_LOG_FILE_VER                     "log_file_version"
#define HDR_CH_MAP                           "channel_map"
#define HDR_MODE0_STEPS                      "mode_0_steps"
#define HDR_TIMESTAMP                        "timestamp"
#define HDR_TIMESTAMP_REALTIME               "timestamp_realtime"
#define HDR_SDKVERSION                       "sdk_version"
#define HDR_MAIN_MODE_TYPE                   "main_mode_type"
#define HDR_SUB_MODE_TYPE                    "sub_mode_type"
#define HDR_MIN_MAIN_MODE_STEPS              "min_main_mode_steps"
#define HDR_MAX_MAIN_MODE_STEPS              "max_main_mode_steps"
#define HDR_MAIN_MODE_REPETITION             "main_mode_repetition"
#define HDR_ROLE                             "role"
#define HDR_RTT_TYPE                         "RTT_type"
#define HDR_CS_SYNC_PHY                      "cs_sync_phy"
#define HDR_CHANNEL_MAP                      "channel_map"
#define HDR_CHANNEL_MAP_REPETITION           "channel_map_repetition"
#define HDR_CHANNEL_SEL_TYPE                 "channel_sel_type"
#define HDR_CH3C_SHAPE                       "ch3c_shape"
#define HDR_CH3C_JUMP                        "ch3c_jump"
#define HDR_COMPANION_SIGNAL_ENABLE          "companion_signal_enable"
#define HDR_T_IP1_TIME                       "t_ip1_time"
#define HDR_T_IP2_TIME                       "t_ip2_time"
#define HDR_T_FCS_TIME                       "t_fcs_time"
#define HDR_T_PM_Time                        "t_pm_time"

#define HDR_ANTENNA_CONFIG                   "antenna_config"
#define HDR_TX_POWER                         "tx_power"
#define HDR_SUBEVENT_LEN                     "subevent_len"
#define HDR_SUBEVENT_INTERVAL                "subevent_interval"
#define HDR_EVENT_INTERVAL                   "event_interval"
#define HDR_PROCEDURE_INTERVAL               "procedure_interval"
#define HDR_PROCEDURE_COUNT                  "procedure_count"

#define MEAS_ESTIMATED_DISTANCE              "estimated_distance"
#define MEAS_DISTANCE_LIKELINESS             "likeliness"
#define MEAS_INITIATOR_BEGIN                 "initiator_cs_subevent_result_events"
#define MEAS_REFLECTOR_BEGIN                 "reflector_cs_subevent_result_events"
#define MEAS_NUM_EVENTS                      "num_events"
#define MEAS_EVENTS_ARRAY                    "events"

#define MEAS_EVENT_ID                        "start_acl_conn_event"
#define MEAS_EVENT_PROC_CNT                  "procedure_counter"
#define MEAS_EVENT_FREQ_COMP                 "frequency_compensation"
#define MEAS_EVENT_PROC_DONE_STS             "procedure_done_status"
#define MEAS_SUBEVENT_DONE_STS               "subevent_done_status"
#define MEAS_EVENT_ABORT_REASON              "abort_reason"
#define MEAS_EVENT_REF_POWER_LVL             "reference_power_level"
#define MEAS_EVENT_NUM_ANT_PATHS             "num_antenna_paths"
#define MEAS_NUM_STEPS                       "num_steps"
#define MEAS_STEPS_ARRAY                     "steps"

#define CAL_STEP_MODE                        "step_mode"
#define CAL_STEP_CHANNEL                     "step_channel"
#define CAL_STEP_RSSI                        "rssi"
#define CAL_STEP_FREQ_OFFSET                 "freq_offset"
#define CAL_STEP_PACKET_QUALITY              "packet_quality"
#define CAL_STEP_PACKET_ANTENNA              "antenna"

#define RTT_STEP_MODE                        CAL_STEP_MODE
#define RTT_STEP_CHANNEL                     CAL_STEP_CHANNEL
#define RTT_STEP_PACKET_QUALITY              CAL_STEP_PACKET_QUALITY
#define RTT_STEP_NADM                        "nadm"
#define RTT_STEP_RSSI                        CAL_STEP_RSSI
#define RTT_STEP_TOD_TOA                     "rtt"
#define RTT_STEP_ANTENNA                     "antenna"

#define PBR_STEP_MODE                        CAL_STEP_MODE
#define PBR_STEP_CHANNEL                     CAL_STEP_CHANNEL
#define PBR_STEP_ANTENNA_PERMUTATION_INDEX   "antenna_permutation_index"
#define PBR_STEP_PCT_I                       "PCT_I"
#define PBR_STEP_PCT_Q                       "PCT_Q"
#define PBR_STEP_TONE_QUALITY                "tone_quality"

// Application log messages
#define FAILED_TO_ADD_CJSON_OBJECT           "Failed to add cJSON object!" APP_LOG_NL
#define FAILED_TO_CREATE_CJSON_OBJECT        "Failed to create cJSON object!" APP_LOG_NL
// *INDENT-ON*

// Selector for timestamps
typedef enum {
  realtime_clock = 0,
  monotonic_clock,
  both_clocks = 0xff
} abr_file_log_clocktype_t;

/// Check pointer to NULL, log error and return
#define CHECK_NULL_RETURN(p, sc, ...) \
  do {                                \
    if ((p) == NULL) {                \
      app_log_error(__VA_ARGS__);     \
      return (sc);                    \
    }                                 \
  } while (0)

/// Check pointer to NULL, goto label
#define CHECK_NULL_GOTO(p, label, ...) \
  do {                                 \
    if ((p) == NULL) {                 \
      app_log_error(__VA_ARGS__);      \
      goto label;                      \
    }                                  \
  } while (0)

// -----------------------------------------------------------------------------
// Module variables.

static FILE *jsonl_file = NULL;
static char jsonl_filename[FILENAME_STRLEN] = "\0";
static char jsonl_dir[DIR_STRLEN] = "\0";
static char jsonl_filepath[PATH_STRLEN] = "\0";
static bool file_conflict = false;
static bool file_log_runnable = false;
static uint8_t null_reference_display = 0;

// Header section
static uint16_t sw_major;
static uint16_t sw_minor;
static uint16_t sw_patch;
static uint16_t sw_build;

// Measurement section
static uint32_t initiator_num_events = 0;
static uint32_t reflector_num_events = 0;
static cJSON *jsonl_initiator_events[ABR_FILE_LOG_CFG_MAX_EVENTS];
static cJSON *jsonl_reflector_events[ABR_FILE_LOG_CFG_MAX_EVENTS];

static uint32_t initiator_num_steps = 0;
static uint32_t reflector_num_steps = 0;
static cJSON *jsonl_initiator_steps[ABR_FILE_LOG_CFG_MAX_STEPS];
static cJSON *jsonl_reflector_steps[ABR_FILE_LOG_CFG_MAX_STEPS];
static uint32_t measurement_cycle = 0;

// -----------------------------------------------------------------------------
// Private function declarations
static sl_status_t initialize_cjson_buffers(abr_role_t role);
static sl_status_t append_channel_map(cJSON *const jsonl,
                                      const uint8_t *data,
                                      const uint32_t data_len);
static sl_status_t append_steps_to_event_header(cJSON **actual_event, const uint32_t num_steps,
                                                cJSON **steps_array, const uint32_t array_size);
sl_status_t append_current_time(cJSON *const jsonl, abr_file_log_clocktype_t clock);
static sl_status_t abr_file_log_append_device_section(abr_role_t role, cJSON *target_section);

#if (ABR_FILE_LOG_CFG_KEEP_OLD_FILES)
static bool fexist(const char *filename);
#endif
static sl_status_t set_filename(uint8_t measurement_mode);

static sl_status_t store_calib_step(abr_role_t role, cs_step_t *step);
static sl_status_t store_rtt_step(abr_role_t role, cs_step_t *step);
static sl_status_t store_pbr_step(abr_role_t role, cs_step_t *step);
static void disable_file_log(void);
static void enable_file_log(void);
static inline bool is_file_log_enabled(void);
static void replace_char(char *str, char target_char, char new_char);
static void cleanup_path(char *str);
static void concat_path(char *dest, char *src, size_t dest_buffsize);
static sl_status_t set_path(char *str_buff, size_t orig_str_buffsize, const char *format, ...);

// -----------------------------------------------------------------------------
// Public function definitions

/******************************************************************************
 * ABR file logger initialization
 * This function sets the target filename and gets the measurement mode.
 *****************************************************************************/
sl_status_t abr_file_log_init(uint8_t abr_mode)
{
  sl_status_t sc = SL_STATUS_OK;
  jsonl_file = NULL;
  disable_file_log();

  sc = initialize_cjson_buffers(ABR_DEVICE_INITIATOR);
  if (sc != SL_STATUS_OK) {
    return sc;
  }

  sc = initialize_cjson_buffers(ABR_DEVICE_REFLECTOR);
  if (sc != SL_STATUS_OK) {
    return sc;
  }

  // abr_file_log_set_dir() not called before, jsonl_filepath is untouched
  if (jsonl_filepath[0] == '\0') {
    app_log_info(LOGGER_TITLE " directory not specified, using current working directory instead." APP_LOG_NL);
    jsonl_filepath[0] = '.';
    get_current_dir(jsonl_filepath, PATH_STRLEN);
  }

  sc = set_filename(abr_mode);
  if (sc != SL_STATUS_OK) {
    file_conflict = true;
  }

  // Allow only forward-slash separator since both win32 and non-win32 systems
  // recognize it.
  cleanup_path(jsonl_filepath);
  app_log_info("Opening file \'%s\' to write" APP_LOG_NL, jsonl_filepath);
  jsonl_file = fopen(jsonl_filepath, "w");
  if (jsonl_file == NULL) {
    app_log_critical("Failed to open file! Check permissions!" APP_LOG_NL);
    sc = SL_STATUS_FAIL;
  }

  if (sc == SL_STATUS_OK) {
    app_log_info(LOGGER_TITLE " initialized." APP_LOG_NL);
    enable_file_log();
  }
  return sc;
}

/******************************************************************************
 * ABR file logger set directory path
 *****************************************************************************/
sl_status_t abr_file_log_set_dir(char *value)
{
  sl_status_t ret_val = SL_STATUS_OK;
  struct stat path_stat;

  CHECK_NULL_RETURN(value, SL_STATUS_NULL_POINTER, "empty argument.");
  strncpy(jsonl_dir, value, sizeof(jsonl_dir));

  stat(jsonl_dir, &path_stat);
  if (!S_ISDIR(path_stat.st_mode)) {
    app_log_warning("Invalid directory path: %s" APP_LOG_NL, jsonl_dir);
    get_current_dir(jsonl_dir, DIR_STRLEN);
    app_log_info("Using current working directory instead." APP_LOG_NL);
  } else if (strlen(jsonl_dir) == 1 && jsonl_dir[0] == '/') {
    app_log_warning("Will not log to ROOT!" APP_LOG_NL);
    get_current_dir(jsonl_dir, DIR_STRLEN);
    app_log_info("Using current working directory instead." APP_LOG_NL);
  } else {
    app_log_info("Valid " LOGGER_TITLE " directory selected." APP_LOG_NL);
  }

  // Fill filepath directory part
  ret_val = set_path(jsonl_filepath, PATH_STRLEN, "%s", jsonl_dir);
  cleanup_path(jsonl_filepath);
  app_log_info(LOGGER_TITLE " directory set to: %s" APP_LOG_NL, jsonl_filepath);

  return ret_val;
}

/******************************************************************************
 * ABR file logger deinitialization
 * Closing file if its still open.
 *****************************************************************************/
sl_status_t abr_file_log_deinit(void)
{
  sl_status_t sc = SL_STATUS_OK;

  disable_file_log();

  if (jsonl_file != NULL) {
    int fs = fclose(jsonl_file);
    if (fs != 0) {
      app_log_critical("Failed to close JSON log file!" APP_LOG_NL);
      sc = SL_STATUS_FAIL;
    }
    jsonl_file = NULL;
  }
  return sc;
}

/******************************************************************************
 * ABR file logger get application version
 * Gets application version info for loggin.
 *****************************************************************************/
sl_status_t abr_file_log_app_version(uint16_t major, uint16_t minor,
                                     uint16_t patch, uint16_t build)
{
  sl_status_t sc = SL_STATUS_OK;
  if (is_file_log_enabled()) {
    sw_major = major;
    sw_minor = minor;
    sw_patch = patch;
    sw_build = build;
  } else {
    sc = SL_STATUS_NOT_AVAILABLE;
  }
  return sc;
}

/******************************************************************************
 * ABR file log append header section
 * This function gathers all the information the file header must contain
 * such as:
 * - timestamp: the start time of the initiator feature
 * - sdk_version: base GSDK version in format "major.minor.patch.build"
 * - channel_map: channel map string
 * - mode0_steps: number of mode0 steps (calibration) in every event
 * The jsonl object is also appended to the target file and it will be closed
 * until the first distance measurement finished.
 *****************************************************************************/
sl_status_t abr_file_log_append_header_section(const uint8_t *ch_data,
                                               const uint32_t ch_data_len,
                                               const uint8_t mode0_steps_count)
{
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  cJSON *obj = NULL, *jsonl_header = NULL;
  char sdk_version_string[MAX_STRLEN];
  char *header_string = NULL;
  int printed_bytes = 0, i = 0, max_iteration = 1;

  if (!is_file_log_enabled()) {
    return SL_STATUS_NOT_AVAILABLE;
  }

#if (ABR_FILE_LOG_CFG_RETRY_FPRINTF && (ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT > 1))
  max_iteration = ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT;
#endif // (ABR_FILE_LOG_CFG_RETRY_FPRINTF && (ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT > 0))

  jsonl_header = cJSON_CreateObject();
  if (jsonl_header == NULL) {
    goto out;
  }

  obj = cJSON_AddNumberToObject(jsonl_header, HDR_LOG_FILE_VER, LOG_FILE_VERSION);
  if (obj == NULL) {
    sc = SL_STATUS_ALLOCATION_FAILED;
    goto out;
  }

  sc = append_current_time(jsonl_header, both_clocks);
  if (sc != SL_STATUS_OK) {
    goto out;
  }

  sprintf(sdk_version_string, "%d.%d.%d.%d", sw_major, sw_minor, sw_patch, sw_build);

  obj = cJSON_AddStringToObject(jsonl_header, HDR_SDKVERSION, sdk_version_string);
  if (obj == NULL) {
    sc = SL_STATUS_ALLOCATION_FAILED;
    goto out;
  }

  sc = append_channel_map(jsonl_header, ch_data, ch_data_len);
  if (sc != SL_STATUS_OK) {
    goto out;
  }

  obj = cJSON_AddNumberToObject(jsonl_header, HDR_MODE0_STEPS, mode0_steps_count);
  if (obj == NULL) {
    sc = SL_STATUS_ALLOCATION_FAILED;
    goto out;
  }

  if (!file_conflict) {
    if (ABR_FILE_LOG_CFG_FORMATTED_PRINT) {
      header_string = cJSON_Print(jsonl_header);
    } else {
      header_string = cJSON_PrintUnformatted(jsonl_header);
    }
    if (header_string == NULL) {
      sc = SL_STATUS_ALLOCATION_FAILED;
      app_log_warning("Failed to render JSON structure!" APP_LOG_NL);
      goto out;
    }
    if (jsonl_file != NULL) {
      app_log_debug("Appending file header..." APP_LOG_NL);

      for (i = 0; i < max_iteration; i++) {
        if (ABR_FILE_LOG_CFG_FORCE_ADD_NEWLINE == 1) {
          printed_bytes = fprintf(jsonl_file, "%s" ABR_FILE_LOG_CFG_NL, header_string);
        } else {
          printed_bytes = fprintf(jsonl_file, "%s", header_string);
        }
        if (printed_bytes >= 0) {
          app_log_debug("Written %d bytes to the file." APP_LOG_NL, printed_bytes);
          sc = SL_STATUS_OK;
          break;
        } else {
          app_log_warning(LOGGER_TITLE ": failed to write file!");
          if (max_iteration > 1) {
            app_log_append_warning("Retrying ..." APP_LOG_NL);
          }
          sc = SL_STATUS_FAIL;
        }
      } // end for(...)
      if (sc == SL_STATUS_FAIL) {
        app_log_critical("Appending header failed, retried %d times. (code: 0x%x)" APP_LOG_NL,
                         max_iteration, printed_bytes);
      } else {
        app_log_debug("Appended header, closing file..." APP_LOG_NL);
      }
      // sl_free() is a necessary step here because of cJSON_Print()
      // usage above
      sl_free(header_string);
      header_string = NULL;
    } else {
      app_log_critical("Cannot open file %s!" APP_LOG_NL, jsonl_filename);
      sc = SL_STATUS_NULL_POINTER;
    }
  } else {
    app_log_critical("Cannot open file to avoid data loss!" APP_LOG_NL);
    sc = SL_STATUS_FAIL;
  }

  app_log_debug("Measurement cycle %04u starts." APP_LOG_NL, measurement_cycle);
  initiator_num_events = 0;
  reflector_num_events = 0;

  out:
  if (sc != SL_STATUS_OK) {
    disable_file_log();
  }
  return sc;
}

/******************************************************************************
 * ABR file log append CS config complete event fields
 *****************************************************************************/
sl_status_t abr_file_log_config_complete_event(sl_bt_evt_cs_config_complete_t *l2_config)
{
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  cJSON *obj = NULL, *cs_config = NULL;
  cJSON *channel_map_array;
  cJSON *channel_map_item;
  bool ret;
  char *raw_content;
  int i;
  int written_bytes;

  if (l2_config == NULL) {
    sc = SL_STATUS_NOT_AVAILABLE;
    return sc;
  }

  cs_config = cJSON_CreateObject();
  if (cs_config == NULL) {
    return sc;
  }

  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_MAIN_MODE_TYPE,
                                l2_config->main_mode_type);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_SUB_MODE_TYPE,
                                l2_config->sub_mode_type);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_MIN_MAIN_MODE_STEPS,
                                l2_config->min_main_mode_steps);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_MAX_MAIN_MODE_STEPS,
                                l2_config->max_main_mode_steps);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_MAIN_MODE_REPETITION,
                                l2_config->main_mode_repetition);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_MODE0_STEPS,
                                l2_config->mode_calibration_steps);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_ROLE,
                                l2_config->role);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_RTT_TYPE,
                                l2_config->rtt_type);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_CS_SYNC_PHY,
                                l2_config->cs_sync_phy);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_CH3C_JUMP,
                                l2_config->ch3c_jump);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);

  channel_map_array = cJSON_CreateArray();
  CHECK_NULL_GOTO(channel_map_array, out, FAILED_TO_ADD_CJSON_OBJECT);

  for (i = 0; i < CHANNEL_MAP_LEN; i++) {
    channel_map_item = cJSON_CreateNumber(l2_config->channel_map.data[i]);
    if (channel_map_item == NULL) {
      goto out;
    }
    ret = cJSON_AddItemToArray(channel_map_array, channel_map_item);
    if (ret == false) {
      goto out;
    }
  }

  ret = cJSON_AddItemToObject(cs_config, HDR_CHANNEL_MAP, channel_map_array);
  if (ret == false) {
    goto out;
  }
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_CHANNEL_MAP_REPETITION,
                                l2_config->channel_map_repetition);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_CHANNEL_SEL_TYPE,
                                l2_config->channel_selection_type);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_CH3C_SHAPE,
                                l2_config->ch3c_shape);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_COMPANION_SIGNAL_ENABLE,
                                l2_config->companion_signal_enable);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_T_IP1_TIME,
                                l2_config->ip1_time_us);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_T_IP2_TIME,
                                l2_config->ip2_time_us);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_T_FCS_TIME,
                                l2_config->fcs_time_us);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(cs_config,
                                HDR_T_PM_Time,
                                l2_config->pm_time_us);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);

  sc = SL_STATUS_OK;

  if (jsonl_file != NULL) {
    if (ABR_FILE_LOG_CFG_FORMATTED_PRINT) {
      raw_content = cJSON_Print(cs_config);
    } else {
      raw_content = cJSON_PrintUnformatted(cs_config);
    }
    if (raw_content == NULL) {
      sc = SL_STATUS_ALLOCATION_FAILED;
      app_log_warning("Failed to render JSON structure!" APP_LOG_NL);
      goto out;
    }

    if (ABR_FILE_LOG_CFG_FORCE_ADD_NEWLINE == 1) {
      written_bytes = fprintf(jsonl_file, "%s" ABR_FILE_LOG_CFG_NL, raw_content);
    } else {
      written_bytes = fprintf(jsonl_file, "%s", raw_content);
    }

    if (written_bytes <= 0) {
      sc = SL_STATUS_FAIL;
      goto out;
    } else {
      app_log_debug("Printed %d bytes to the filestream." APP_LOG_NL,
                    written_bytes);
    }
  } else {
    sc = SL_STATUS_NULL_POINTER;
  }

  out:
  if (cs_config != NULL) {
    cJSON_Delete(cs_config);
  }

  return sc;
}

/******************************************************************************
 * ABR file log append CS procedure complete event fields
 *****************************************************************************/
sl_status_t abr_file_log_procedure_config_complete_event(sl_bt_evt_cs_procedure_enable_complete_t *procedure_config)
{
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  cJSON *obj = NULL, *config_object = NULL;
  char *raw_content;
  int written_bytes;

  if (procedure_config == NULL) {
    sc = SL_STATUS_NOT_AVAILABLE;
    return sc;
  }

  config_object = cJSON_CreateObject();
  if (config_object == NULL) {
    return sc;
  }

  obj = cJSON_AddNumberToObject(config_object,
                                HDR_ANTENNA_CONFIG,
                                procedure_config->antenna_config);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(config_object,
                                HDR_TX_POWER,
                                procedure_config->tx_power);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(config_object,
                                HDR_SUBEVENT_LEN,
                                procedure_config->subevent_len);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(config_object,
                                HDR_SUBEVENT_INTERVAL,
                                procedure_config->subevent_interval);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(config_object,
                                HDR_EVENT_INTERVAL,
                                procedure_config->event_interval);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(config_object,
                                HDR_PROCEDURE_INTERVAL,
                                procedure_config->procedure_interval);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(config_object,
                                HDR_PROCEDURE_COUNT,
                                procedure_config->procedure_count);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);

  sc = SL_STATUS_OK;

  if (jsonl_file != NULL) {
    if (ABR_FILE_LOG_CFG_FORMATTED_PRINT) {
      raw_content = cJSON_Print(config_object);
    } else {
      raw_content = cJSON_PrintUnformatted(config_object);
    }
    if (raw_content == NULL) {
      sc = SL_STATUS_ALLOCATION_FAILED;
      app_log_warning("Failed to render JSON structure!" APP_LOG_NL);
      goto out;
    }

    if (ABR_FILE_LOG_CFG_FORCE_ADD_NEWLINE == 1) {
      written_bytes = fprintf(jsonl_file, "%s" ABR_FILE_LOG_CFG_NL,
                              raw_content);
    } else {
      written_bytes = fprintf(jsonl_file, "%s", raw_content);
    }

    if (written_bytes <= 0) {
      sc = SL_STATUS_FAIL;
      goto out;
    } else {
      app_log_debug("Printed %d bytes to the filestream." APP_LOG_NL,
                    written_bytes);
    }
  } else {
    sc = SL_STATUS_NULL_POINTER;
  }

  out:
  if (config_object != NULL) {
    cJSON_Delete(config_object);
  }

  return sc;
}

/******************************************************************************
 * Append new event header to the new event jsonl objects
 * This event header appended on the beginning of every measurement cycle!
 * It checks the actual event role (device) and fill up
 * the header for it with the already known information:
 * - start_acl_conn_event: the event identifier
 * - timestamp
 * The jsonl object will be extended the additional information later on.
 *****************************************************************************/
sl_status_t abr_file_log_append_event_header(abr_role_t role,
                                             sl_bt_evt_cs_result_t *cs_res)
{
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  cJSON *obj = NULL;

  if (!is_file_log_enabled()) {
    return SL_STATUS_NOT_AVAILABLE;
  }
  // Check input parameters
  if (cs_res != NULL) {
    // At this point it is not known how many events may come yet so
    // we can only add the following elements to the event object:
    // - start_acl_conn_event
    // - timestamp (the moment when the event detected here)
    if (role == ABR_DEVICE_INITIATOR) {
      initiator_num_steps = 0;

      if (initiator_num_events >= ABR_FILE_LOG_CFG_MAX_EVENTS) {
        app_log_error("Maximum number of initiator events exceeded! max='%u' curr='%u'" APP_LOG_NL,
                      ABR_FILE_LOG_CFG_MAX_EVENTS,
                      initiator_num_events);
        disable_file_log();
        return SL_STATUS_INVALID_COUNT;
      }

      obj = cJSON_AddNumberToObject(jsonl_initiator_events[initiator_num_events],
                                    MEAS_EVENT_ID,
                                    cs_res->start_acl_conn_event);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_initiator_events[initiator_num_events],
                                    MEAS_EVENT_PROC_CNT,
                                    cs_res->procedure_counter);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_initiator_events[initiator_num_events],
                                    MEAS_EVENT_FREQ_COMP,
                                    cs_res->frequency_compensation);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_initiator_events[initiator_num_events],
                                    MEAS_EVENT_PROC_DONE_STS,
                                    cs_res->procedure_done_status);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_initiator_events[initiator_num_events],
                                    MEAS_SUBEVENT_DONE_STS,
                                    cs_res->subevent_done_status);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_initiator_events[initiator_num_events],
                                    MEAS_EVENT_ABORT_REASON,
                                    cs_res->abort_reason);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_initiator_events[initiator_num_events],
                                    MEAS_EVENT_REF_POWER_LVL,
                                    cs_res->reference_power_level);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_initiator_events[initiator_num_events],
                                    MEAS_EVENT_NUM_ANT_PATHS,
                                    cs_res->num_antenna_paths);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      sc = append_current_time(jsonl_initiator_events[initiator_num_events], both_clocks);
      if (sc != SL_STATUS_OK) {
        goto out;
      }
      sc = SL_STATUS_OK;
      app_log_debug("<<< %02d. initiator EVENT processing begin >>>" APP_LOG_NL,
                    initiator_num_events);
    } else {
      reflector_num_steps = 0;

      if (reflector_num_events >= ABR_FILE_LOG_CFG_MAX_EVENTS) {
        app_log_error("Maximum number of reflector events exceeded! max='%u' curr='%u'" APP_LOG_NL,
                      ABR_FILE_LOG_CFG_MAX_EVENTS,
                      reflector_num_events);
        disable_file_log();
        return SL_STATUS_INVALID_COUNT;
      }

      obj = cJSON_AddNumberToObject(jsonl_reflector_events[reflector_num_events],
                                    MEAS_EVENT_ID,
                                    cs_res->start_acl_conn_event);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_reflector_events[reflector_num_events],
                                    MEAS_EVENT_PROC_CNT,
                                    cs_res->procedure_counter);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_reflector_events[reflector_num_events],
                                    MEAS_EVENT_FREQ_COMP,
                                    cs_res->frequency_compensation);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_reflector_events[reflector_num_events],
                                    MEAS_EVENT_PROC_DONE_STS,
                                    cs_res->procedure_done_status);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_reflector_events[reflector_num_events],
                                    MEAS_SUBEVENT_DONE_STS,
                                    cs_res->subevent_done_status);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_reflector_events[reflector_num_events],
                                    MEAS_EVENT_ABORT_REASON,
                                    cs_res->abort_reason);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_reflector_events[reflector_num_events],
                                    MEAS_EVENT_REF_POWER_LVL,
                                    cs_res->reference_power_level);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      obj = cJSON_AddNumberToObject(jsonl_reflector_events[reflector_num_events],
                                    MEAS_EVENT_NUM_ANT_PATHS,
                                    cs_res->num_antenna_paths);
      CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
      sc = append_current_time(jsonl_reflector_events[reflector_num_events], both_clocks);
      if (sc != SL_STATUS_OK) {
        goto out;
      }
      sc = SL_STATUS_OK;
      app_log_debug("<<< %02d. reflector EVENT processing begin >>>" APP_LOG_NL,
                    reflector_num_events);
    }
  } else {
    app_log_error("Invalid input parameter!" APP_LOG_NL);
    sc = SL_STATUS_NULL_POINTER;
  }

  out:
  if (sc != SL_STATUS_OK) {
    disable_file_log();
  }
  return sc;
}

/******************************************************************************
 * Assign steps to event
 * Once every steps is processed in 1 event, assign their array to that event
 * and finalize.
 *****************************************************************************/
sl_status_t abr_file_log_assign_steps_to_event(abr_role_t role, uint16_t num_steps)
{
  sl_status_t sc = SL_STATUS_OK;
  app_log_debug("Assign steps to event" APP_LOG_NL);

  if (!is_file_log_enabled()) {
    return SL_STATUS_NOT_AVAILABLE;
  }

  if (num_steps != 0) {
    if (role == ABR_DEVICE_INITIATOR) {
      sc = append_steps_to_event_header(&jsonl_initiator_events[initiator_num_events],
                                        num_steps,
                                        jsonl_initiator_steps,
                                        initiator_num_steps);
      app_log_debug("%s" APP_LOG_NL,
                    cJSON_PrintUnformatted(jsonl_initiator_events[initiator_num_events]));
      if (sc == SL_STATUS_OK) {
        app_log_debug("<<< %02d. initiator EVENT processing end >>>" APP_LOG_NL, initiator_num_events);
        initiator_num_events++;
      } else {
        app_log_error("%02d. initiator event is corrupted!" APP_LOG_NL, initiator_num_events);
      }
    } else {
      sc = append_steps_to_event_header(&jsonl_reflector_events[reflector_num_events],
                                        num_steps,
                                        jsonl_reflector_steps,
                                        reflector_num_steps);
      app_log_debug("%s" APP_LOG_NL, cJSON_Print(jsonl_reflector_events[reflector_num_events]));
      if (sc == SL_STATUS_OK) {
        app_log_debug("<<< %02d. reflector EVENT processing end >>>" APP_LOG_NL, reflector_num_events);
        reflector_num_events++;
      } else {
        app_log_error("%02d. reflector event is corrupted!" APP_LOG_NL, reflector_num_events);
      }
    }
  }

  if (sc != SL_STATUS_OK) {
    disable_file_log();
  }
  return sc;
}

/******************************************************************************
 * Store step data
 * Parsed and saved properties according to the actual mode and role.
 * There is also an option to keep the old jsonl format of the steps or extend
 * them with additional properties.
 * The function also increments the step counters.
 *****************************************************************************/
sl_status_t abr_file_log_store_step(abr_role_t role, cs_step_t *step_data)
{
  sl_status_t sc = SL_STATUS_OK;

  if (!is_file_log_enabled()) {
    return SL_STATUS_NOT_AVAILABLE;
  }

  if (step_data != NULL) {
    switch (step_data->step_mode) {
      case ABR_MODE_CALIBRATION:
        sc = store_calib_step(role, step_data);
        break;

      case ABR_MODE_RTT:
        sc = store_rtt_step(role, step_data);
        break;

      case ABR_MODE_PBR:
        sc = store_pbr_step(role, step_data);
        break;

      default:
        break;
    }
  } else {
    app_log_error("No step data detected!" APP_LOG_NL);
    sc = SL_STATUS_NULL_POINTER;
  }

  if (sc != SL_STATUS_OK) {
    disable_file_log();
  }
  return sc;
}

static void replace_char(char *str, char target_char, char new_char)
{
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == target_char) {
      str[i] = new_char;
    }
  }
}

static void cleanup_path(char *str)
{
  size_t str_len;
  replace_char(str, '\\', '/');
  // remove trailing slash if necessary to avoid consecutive //s
  str_len = strlen(str);
  if (str_len > 0 && str[str_len - 1] == '/') {
    str[str_len - 1] = '\0';
  }
}

static void concat_path(char *dest, char *src, size_t dest_buffsize)
{
  // no need to return the pointer to dest again so voided.
  (void)strncat(dest, src, dest_buffsize - strlen(dest));
}

static sl_status_t set_path(char *str_buff, size_t orig_str_buffsize, const char *format, ...)
{
  sl_status_t ret = SL_STATUS_OK;
  int result = 0;
  va_list args;

  app_log_debug("set_path: before va_start(): %s" APP_LOG_NL, str_buff);
  va_start(args, format);
  result = vsnprintf(str_buff, orig_str_buffsize - strlen(str_buff), format, args);
  va_end(args);
  app_log_debug("set_path: after va_end(): %s" APP_LOG_NL, str_buff);

  if (result >= (orig_str_buffsize - strlen(str_buff))) {
    app_log_error(LOGGER_TITLE " path truncated! See: %s" APP_LOG_NL, str_buff);
    ret = SL_STATUS_FAIL;
  } else if (result < 0) {
    app_log_error("Output error while setting path! (Err: 0x%x)" APP_LOG_NL, result);
  } else {
    app_log_debug("Path set: %s" APP_LOG_NL, str_buff);
  }

  return ret;
}

static sl_status_t store_calib_step(abr_role_t role, cs_step_t *step)
{
  cJSON *obj = NULL;
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;

  if (role == ABR_DEVICE_INITIATOR) {
    jsonl_initiator_steps[initiator_num_steps] = cJSON_CreateObject();
    CHECK_NULL_RETURN(jsonl_initiator_steps[initiator_num_steps],
                      sc,
                      FAILED_TO_CREATE_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  CAL_STEP_MODE, step->step_mode);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  CAL_STEP_CHANNEL, step->step_channel);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  CAL_STEP_RSSI, step->data.initiator_calib.rssi);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  CAL_STEP_FREQ_OFFSET,
                                  step->data.initiator_calib.freq_offset);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  CAL_STEP_PACKET_ANTENNA,
                                  step->data.initiator_calib.packet_antenna);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  CAL_STEP_PACKET_QUALITY,
                                  step->data.initiator_calib.packet_quality);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    app_log_debug(" %02d: initiator calib.step stored." APP_LOG_NL, initiator_num_steps);
    initiator_num_steps++;
  } else {
    jsonl_reflector_steps[reflector_num_steps] = cJSON_CreateObject();
    CHECK_NULL_RETURN(jsonl_reflector_steps[reflector_num_steps],
                      sc,
                      FAILED_TO_CREATE_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  CAL_STEP_MODE,
                                  step->step_mode);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  CAL_STEP_CHANNEL,
                                  step->step_channel);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  CAL_STEP_RSSI,
                                  step->data.reflector_calib.rssi);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  CAL_STEP_PACKET_ANTENNA,
                                  step->data.reflector_calib.packet_antenna);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  CAL_STEP_PACKET_QUALITY,
                                  step->data.reflector_calib.packet_quality);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    app_log_debug(" %02d: reflector calib.step stored." APP_LOG_NL, reflector_num_steps);
    reflector_num_steps++;
  }
  return SL_STATUS_OK;
}

static sl_status_t store_rtt_step(abr_role_t role, cs_step_t *step)
{
  cJSON *obj = NULL;
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;

  if (role == ABR_DEVICE_INITIATOR) {
    jsonl_initiator_steps[initiator_num_steps] = cJSON_CreateObject();
    CHECK_NULL_RETURN(jsonl_initiator_steps[initiator_num_steps],
                      sc,
                      FAILED_TO_CREATE_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  RTT_STEP_MODE,
                                  step->step_mode);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  RTT_STEP_CHANNEL,
                                  step->step_channel);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  RTT_STEP_NADM,
                                  step->data.meas_rtt.nadm);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  RTT_STEP_RSSI,
                                  step->data.meas_rtt.rssi);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  RTT_STEP_TOD_TOA,
                                  step->data.meas_rtt.tod_toa);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  RTT_STEP_ANTENNA,
                                  step->data.meas_rtt.antenna);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  RTT_STEP_PACKET_QUALITY,
                                  step->data.meas_rtt.packet_quality);
    app_log_debug(" %02d: initiator rtt step stored." APP_LOG_NL, initiator_num_steps);
    initiator_num_steps++;
  } else {
    jsonl_reflector_steps[reflector_num_steps] = cJSON_CreateObject();
    CHECK_NULL_RETURN(jsonl_reflector_steps[reflector_num_steps],
                      sc,
                      FAILED_TO_CREATE_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  RTT_STEP_MODE,
                                  step->step_mode);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  RTT_STEP_CHANNEL,
                                  step->step_channel);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  RTT_STEP_NADM,
                                  step->data.meas_rtt.nadm);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  RTT_STEP_RSSI,
                                  step->data.meas_rtt.rssi);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  RTT_STEP_TOD_TOA,
                                  step->data.meas_rtt.tod_toa);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  RTT_STEP_ANTENNA,
                                  step->data.meas_rtt.antenna);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  RTT_STEP_PACKET_QUALITY,
                                  step->data.meas_rtt.packet_quality);
    app_log_debug(" %02d: reflector rtt step stored." APP_LOG_NL,
                  reflector_num_steps);
    reflector_num_steps++;
  }
  return SL_STATUS_OK;
}

static sl_status_t store_pbr_step(abr_role_t role, cs_step_t *step)
{
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  cJSON *obj = NULL;
  cJSON_bool cjson_status;

  cJSON *pct_i_array = cJSON_CreateFloatArray(step->data.meas_pbr.pct_i,
                                              ANTENNA_PERMUTATION_MAX);
  CHECK_NULL_RETURN(pct_i_array, sc, FAILED_TO_CREATE_CJSON_OBJECT);
  cJSON *pct_q_array = cJSON_CreateFloatArray(step->data.meas_pbr.pct_q,
                                              ANTENNA_PERMUTATION_MAX);
  CHECK_NULL_RETURN(pct_q_array, sc, FAILED_TO_CREATE_CJSON_OBJECT);

  int tone_quality_iter;
  int tone_quality[ANTENNA_PERMUTATION_MAX];

  for (tone_quality_iter = 0; tone_quality_iter < ANTENNA_PERMUTATION_MAX; tone_quality_iter++) {
    tone_quality[tone_quality_iter] = step->data.meas_pbr.tone_quality[tone_quality_iter];
  }

  cJSON *tone_quality_array = cJSON_CreateIntArray(tone_quality, ANTENNA_PERMUTATION_MAX);
  CHECK_NULL_RETURN(tone_quality_array, sc, FAILED_TO_CREATE_CJSON_OBJECT);

  if (role == ABR_DEVICE_INITIATOR) {
    jsonl_initiator_steps[initiator_num_steps] = cJSON_CreateObject();
    CHECK_NULL_RETURN(jsonl_initiator_steps[initiator_num_steps], sc,
                      FAILED_TO_CREATE_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  PBR_STEP_MODE,
                                  step->step_mode);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  PBR_STEP_CHANNEL,
                                  step->step_channel);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_initiator_steps[initiator_num_steps],
                                  PBR_STEP_ANTENNA_PERMUTATION_INDEX,
                                  step->data.meas_pbr.antenna_permutation_index);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    cjson_status = cJSON_AddItemToObject(jsonl_initiator_steps[initiator_num_steps],
                                         PBR_STEP_PCT_I,
                                         pct_i_array);
    if (!cjson_status) {
      app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
      return SL_STATUS_FAIL;
    }
    cjson_status = cJSON_AddItemToObject(jsonl_initiator_steps[initiator_num_steps],
                                         PBR_STEP_PCT_Q,
                                         pct_q_array);
    if (!cjson_status) {
      app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
      return SL_STATUS_FAIL;
    }
    cjson_status = cJSON_AddItemToObject(jsonl_initiator_steps[initiator_num_steps],
                                         PBR_STEP_TONE_QUALITY,
                                         tone_quality_array);
    if (!cjson_status) {
      app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
      return SL_STATUS_FAIL;
    }
    app_log_debug(" %02d: initiator pbr step stored." APP_LOG_NL, initiator_num_steps);
    initiator_num_steps++;
  } else {
    jsonl_reflector_steps[reflector_num_steps] = cJSON_CreateObject();
    CHECK_NULL_RETURN(jsonl_reflector_steps[reflector_num_steps],
                      sc,
                      FAILED_TO_CREATE_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  PBR_STEP_MODE,
                                  step->step_mode);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  PBR_STEP_CHANNEL,
                                  step->step_channel);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    obj = cJSON_AddNumberToObject(jsonl_reflector_steps[reflector_num_steps],
                                  PBR_STEP_ANTENNA_PERMUTATION_INDEX,
                                  step->data.meas_pbr.antenna_permutation_index);
    CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    cjson_status = cJSON_AddItemToObject(jsonl_reflector_steps[reflector_num_steps],
                                         PBR_STEP_PCT_I,
                                         pct_i_array);
    if (!cjson_status) {
      app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
      return SL_STATUS_FAIL;
    }
    cjson_status = cJSON_AddItemToObject(jsonl_reflector_steps[reflector_num_steps],
                                         PBR_STEP_PCT_Q,
                                         pct_q_array);
    if (!cjson_status) {
      app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
      return SL_STATUS_FAIL;
    }
    cjson_status = cJSON_AddItemToObject(jsonl_reflector_steps[reflector_num_steps],
                                         PBR_STEP_TONE_QUALITY,
                                         tone_quality_array);
    if (!cjson_status) {
      app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
      return SL_STATUS_FAIL;
    }
    app_log_debug(" %02d: reflector pbr step stored." APP_LOG_NL, reflector_num_steps);
    reflector_num_steps++;
  }
  return SL_STATUS_OK;
}

/******************************************************************************
 * ABR file log finalize measurement section
 * Gets all the initiator and reflector data and stores in together with the
 * estimated distance to the target log file.
 *****************************************************************************/
sl_status_t abr_file_log_finalize_measurement_section(float *estimated_distance,
                                                      float *distance_likeliness,
                                                      float *rssi_distance)
{
  (void)rssi_distance;
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  char *raw_content = NULL;
  int written_bytes = 0;
  int i = 0, max_iteration = 1;
  cJSON *obj = NULL;
  cJSON_bool cjson_status;

  if (!is_file_log_enabled()) {
    return SL_STATUS_NOT_AVAILABLE;
  }

#if (ABR_FILE_LOG_CFG_RETRY_FPRINTF && (ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT > 1))
  max_iteration = ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT;
#endif // (ABR_FILE_LOG_CFG_RETRY_FPRINTF && (ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT > 0))

  cJSON *initiator_section = cJSON_CreateObject();
  CHECK_NULL_GOTO(initiator_section, out,
                  FAILED_TO_CREATE_CJSON_OBJECT);
  cJSON *reflector_section = cJSON_CreateObject();
  CHECK_NULL_GOTO(reflector_section, out,
                  FAILED_TO_CREATE_CJSON_OBJECT);
  cJSON *measurement_section = cJSON_CreateObject();
  CHECK_NULL_GOTO(measurement_section, out,
                  FAILED_TO_CREATE_CJSON_OBJECT);

  app_log_info("Log measurement cycle %04u ..." APP_LOG_NL, measurement_cycle);

  sc = abr_file_log_append_device_section(ABR_DEVICE_INITIATOR, initiator_section);
  if (sc != SL_STATUS_OK) {
    goto out;
  }
  sc = abr_file_log_append_device_section(ABR_DEVICE_REFLECTOR, reflector_section);
  if (sc != SL_STATUS_OK) {
    goto out;
  }

  obj = cJSON_AddNumberToObject(measurement_section,
                                MEAS_ESTIMATED_DISTANCE,
                                *estimated_distance);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  obj = cJSON_AddNumberToObject(measurement_section,
                                MEAS_DISTANCE_LIKELINESS,
                                *distance_likeliness);
  CHECK_NULL_GOTO(obj, out, FAILED_TO_ADD_CJSON_OBJECT);
  cjson_status = cJSON_AddItemToObject(measurement_section,
                                       MEAS_INITIATOR_BEGIN,
                                       initiator_section);
  if (!cjson_status) {
    app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
    sc = SL_STATUS_FAIL;
    goto out;
  }
  cjson_status = cJSON_AddItemToObject(measurement_section,
                                       MEAS_REFLECTOR_BEGIN,
                                       reflector_section);
  if (!cjson_status) {
    app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
    sc = SL_STATUS_FAIL;
    goto out;
  }

  sc = SL_STATUS_OK;
  if (ABR_FILE_LOG_CFG_FORMATTED_PRINT) {
    raw_content = cJSON_Print(measurement_section);
  } else {
    raw_content = cJSON_PrintUnformatted(measurement_section);
  }
  if (raw_content == NULL) {
    sc = SL_STATUS_ALLOCATION_FAILED;
    app_log_warning("Failed to render JSON structure!" APP_LOG_NL);
    goto out;
  }
  // Free up the memory - kill all the subsections to start fresh
  cJSON_Delete(measurement_section);

  if (!file_conflict) {
    if (jsonl_file == NULL) {
      if (null_reference_display < ABR_FILE_LOG_MAX_CRITICAL_MESSAGE_DISPLAY) {
        app_log_error("Unable to open file for write." APP_LOG_NL);
        app_log_critical(LOGGER_TITLE " not functional! Null reference for logfile! (%02u)" APP_LOG_NL,
                         null_reference_display);
        null_reference_display++;
      }

      sc = SL_STATUS_NULL_POINTER;
    } else {
      app_log_debug("Trying to print raw content into file..." APP_LOG_NL);
      for (i = 0; i < max_iteration; i++) {
        if (ABR_FILE_LOG_CFG_FORCE_ADD_NEWLINE == 1) {
          written_bytes = fprintf(jsonl_file, "%s" ABR_FILE_LOG_CFG_NL, raw_content);
        } else {
          written_bytes = fprintf(jsonl_file, "%s", raw_content);
        }
        if (written_bytes >= 0) {
          app_log_debug("Printed %d bytes to the filestream." APP_LOG_NL,
                        written_bytes);
          break;
        } else {
          if (max_iteration > 1) {
            app_log_warning("Retrying..." APP_LOG_NL);
          }
          sc = SL_STATUS_FAIL;
        }
      }
      if (sc == SL_STATUS_FAIL) {
        app_log_error("Retried %d times. Check file write permissions or",
                      ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT);
        app_log_error("that the file is not in use anywhere else!" APP_LOG_NL);
      }
    }
  }

  // Prepare for the next measurement cycle
  if (sc == SL_STATUS_OK) {
    measurement_cycle++;
    app_log_debug("Measurement cycle %04u starts" APP_LOG_NL, measurement_cycle);
    initiator_num_events = 0;
    reflector_num_events = 0;
    sc = initialize_cjson_buffers(ABR_DEVICE_INITIATOR);
    if (sc != SL_STATUS_OK) {
      goto out;
    }
    sc = initialize_cjson_buffers(ABR_DEVICE_REFLECTOR);
    if (sc != SL_STATUS_OK) {
      goto out;
    }
  }

  out:
  if (sc != SL_STATUS_OK) {
    disable_file_log();
  }
  return sc;
}

// -----------------------------------------------------------------------------
// Private function definitions

static sl_status_t initialize_cjson_buffers(abr_role_t role)
{
  int i;
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;

  if (role == ABR_DEVICE_INITIATOR) {
    for (i = 0; i < ABR_FILE_LOG_CFG_MAX_EVENTS; i++) {
      jsonl_initiator_events[i] = cJSON_CreateObject();
      CHECK_NULL_RETURN(jsonl_initiator_events[i], sc,
                        FAILED_TO_CREATE_CJSON_OBJECT);
    }
    for (i = 0; i < ABR_FILE_LOG_CFG_MAX_STEPS; i++) {
      jsonl_initiator_steps[i] = cJSON_CreateObject();
      CHECK_NULL_RETURN(jsonl_initiator_steps[i], sc,
                        FAILED_TO_CREATE_CJSON_OBJECT);
    }
  } else {
    for (i = 0; i < ABR_FILE_LOG_CFG_MAX_EVENTS; i++) {
      jsonl_reflector_events[i] = cJSON_CreateObject();
      CHECK_NULL_RETURN(jsonl_reflector_events[i], sc,
                        FAILED_TO_CREATE_CJSON_OBJECT);
    }
    for (i = 0; i < ABR_FILE_LOG_CFG_MAX_STEPS; i++) {
      jsonl_reflector_steps[i] = cJSON_CreateObject();
      CHECK_NULL_RETURN(jsonl_reflector_steps[i], sc,
                        FAILED_TO_CREATE_CJSON_OBJECT);
    }
  }
  sc = SL_STATUS_OK;
  return sc;
}

/******************************************************************************
 * Append the channel_map to the header
 *****************************************************************************/
static sl_status_t append_channel_map(cJSON *const jsonl,
                                      const uint8_t *data,
                                      const uint32_t data_len)
{
  sl_status_t sc = SL_STATUS_OK;
  char *channel_map_string;
  uint32_t string_memsize;
  int memory_position = 0, written_bytes = 0;
  cJSON *obj = NULL;

  string_memsize = (data_len * 2) + 1;

  if ((string_memsize > 0) && (string_memsize < UINT32_MAX)) {
    app_log_debug("Allocate %d bytes for the channel map." APP_LOG_NL, string_memsize);
    // Avoiding resonance cascase λ
    channel_map_string = sl_calloc(string_memsize, sizeof(char));
    if (channel_map_string != NULL) {
      app_log_debug("Allocated %d bytes of heap." APP_LOG_NL, string_memsize);
      // Copy channel map to the string
      for (uint32_t i = 0; i < data_len; i++) {
        written_bytes = sprintf(&channel_map_string[memory_position], "%02x", data[i]);
        memory_position += written_bytes;
      }
      obj = cJSON_AddStringToObject(jsonl, HDR_CH_MAP, channel_map_string);
      if (obj == NULL) {
        sc = SL_STATUS_ALLOCATION_FAILED;
      }
      // Free memory only if allocated before
      sl_free(channel_map_string);
    } else {
      app_log_critical("Channel map memory allocation failed! Cannot proceed!" APP_LOG_NL);
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  } else {
    app_log_error("Channel map invalid parameter for data_len=%d!" APP_LOG_NL, data_len);
    sc = SL_STATUS_ALLOCATION_FAILED;
  }
  return sc;
}

/******************************************************************************
 * Append the steps info to the event jsonl object
 * Such as:
 * - num_steps: size of the steps array
 * - steps: the steps array reference itself
 *****************************************************************************/
static sl_status_t append_steps_to_event_header(cJSON **actual_event,
                                                const uint32_t num_steps,
                                                cJSON **steps_array,
                                                const uint32_t array_size)
{
  sl_status_t sc = SL_STATUS_OK;
  cJSON *obj = NULL;
  cJSON_bool cjson_status;
  uint32_t i;

  if ((*actual_event != NULL) && (*steps_array != NULL) && (actual_event != NULL) && (steps_array != NULL) && (num_steps != 0) && (array_size != 0)) {
    obj = cJSON_AddNumberToObject(*actual_event, MEAS_NUM_STEPS, num_steps);
    CHECK_NULL_RETURN(obj,
                      SL_STATUS_ALLOCATION_FAILED,
                      FAILED_TO_ADD_CJSON_OBJECT);
    // Copy all non-empty steps into a temporary array and add it to the actual
    // event
    cJSON *temp_array = cJSON_CreateArray();
    for (i = 0; i < array_size; i++) {
      if (steps_array[i] != NULL) {
        cjson_status = cJSON_AddItemToArray(temp_array, steps_array[i]);
        if (!cjson_status) {
          app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
          return SL_STATUS_FAIL;
        }
        app_log_debug("step %02d/%02d: %s" APP_LOG_NL,
                      i,
                      num_steps,
                      cJSON_PrintUnformatted(steps_array[i]));
      } else {
        app_log_error("step %02d is null-pointer!" APP_LOG_NL, i);
      }
    }
    cjson_status = cJSON_AddItemToObject(*actual_event, MEAS_STEPS_ARRAY, temp_array);
    if (!cjson_status) {
      app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
      return SL_STATUS_FAIL;
    }
    app_log_debug("new event: %s" APP_LOG_NL, cJSON_PrintUnformatted(*actual_event));
  } else {
    app_log_error("Invalid input parameter!" APP_LOG_NL);
    sc = SL_STATUS_NULL_POINTER;
  }
  app_log_debug("%02d steps assigned." APP_LOG_NL, num_steps);
  return sc;
}

/******************************************************************************
 * Append the current time string to a cjson object
 *****************************************************************************/
sl_status_t append_current_time(cJSON *const jsonl, abr_file_log_clocktype_t clock)
{
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  cJSON *obj = NULL;
  struct timespec current_timestamp, current_timestamp_rt;
  double tstamp = 0.0, tstamp_realtime = 0.0;
  char timestamp_string[TIME_STRLEN] = "\0", timestamp_string_rt[TIME_STRLEN] = "\0";

  if (clock == both_clocks || clock == monotonic_clock) {
    clock_gettime(CLOCK_MONOTONIC, &current_timestamp);
    if (ABR_FILE_LOG_CFG_NUMERIC_TIMESTAMPS == 1) {
      tstamp = ((double)current_timestamp.tv_sec + (double)current_timestamp.tv_nsec * NANOSEC_DIVIDER);
      obj = cJSON_AddNumberToObject(jsonl, HDR_TIMESTAMP, tstamp);
      CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    } else {
      sc = set_path(timestamp_string, TIME_STRLEN, "%lld.%.9ld",
                    (long long)current_timestamp.tv_sec, current_timestamp.tv_nsec);
      if (sc == SL_STATUS_OK) {
        obj = cJSON_AddStringToObject(jsonl, HDR_TIMESTAMP, timestamp_string);
        CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
      } else {
        app_log_error("Could not append monotonic timestamp!" APP_LOG_NL);
      }
    }
  }

  if (clock == both_clocks || clock == realtime_clock) {
    clock_gettime(CLOCK_REALTIME, &current_timestamp_rt);
    if (ABR_FILE_LOG_CFG_NUMERIC_TIMESTAMPS == 1) {
      tstamp_realtime = ((double)current_timestamp_rt.tv_sec + (double)current_timestamp_rt.tv_nsec * NANOSEC_DIVIDER);
      obj = cJSON_AddNumberToObject(jsonl, HDR_TIMESTAMP_REALTIME, tstamp_realtime);
      CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
    } else {
      sc = set_path(timestamp_string_rt, TIME_STRLEN, "%lld.%.9ld",
                    (long long)current_timestamp_rt.tv_sec, current_timestamp_rt.tv_nsec);
      if (sc == SL_STATUS_OK) {
        obj = cJSON_AddStringToObject(jsonl, HDR_TIMESTAMP_REALTIME, timestamp_string_rt);
        CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
      } else {
        app_log_error("Could not append realtime timestamp!" APP_LOG_NL);
      }
    }
  }
  return SL_STATUS_OK;
}

/******************************************************************************
 * ABR file log append device section
 * This function gathers all the information required for the selected device.
 * Such as:
 * - initiator subevents:
 *   \_num_events: number of elements the 'events ' array has
 *   \_events[]: events array
 *     \_start_acl_conn_event: event identifier
 *     \_timestamp: when the event processed
 *     \_num_steps: number of elements the 'steps ' array has
 *     \_steps[]: actual steps in the event
 *****************************************************************************/
static sl_status_t abr_file_log_append_device_section(abr_role_t role, cJSON *target_section)
{
  sl_status_t sc = SL_STATUS_ALLOCATION_FAILED;
  cJSON *obj = NULL;
  cJSON_bool cjson_status;
  uint32_t i;

  if (role == ABR_DEVICE_INITIATOR) {
    if ((target_section == NULL) || (jsonl_initiator_events[initiator_num_events] == NULL)) {
      app_log_critical("Can not create initiator device JSON object!" APP_LOG_NL);
      app_log_critical(LOGGER_TITLE " is not functional!" APP_LOG_NL);
      sc = SL_STATUS_NULL_POINTER;
    } else {
      cJSON *final_initiator_events = cJSON_CreateArray();
      CHECK_NULL_RETURN(final_initiator_events, sc, FAILED_TO_CREATE_CJSON_OBJECT);
      for (i = 0; i < initiator_num_events; i++) {
        if (jsonl_initiator_events[i] != NULL) {
          cjson_status = cJSON_AddItemToArray(final_initiator_events, jsonl_initiator_events[i]);
          if (!cjson_status) {
            app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
            return SL_STATUS_FAIL;
          }
        } else {
          app_log_error("initiator EVENT %02d lost!" APP_LOG_NL, i);
        }
      }
      obj = cJSON_AddNumberToObject(target_section, MEAS_NUM_EVENTS, initiator_num_events);
      CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
      cjson_status = cJSON_AddItemToObject(target_section,
                                           MEAS_EVENTS_ARRAY,
                                           final_initiator_events);
      if (!cjson_status) {
        app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
        return SL_STATUS_FAIL;
      }
      app_log_debug("Appended %d events to initiator section successfully:" APP_LOG_NL,
                    initiator_num_events);
      app_log_debug("%s" APP_LOG_NL, cJSON_PrintUnformatted(final_initiator_events));
    }
  } else {
    if ((target_section == NULL) || (jsonl_reflector_events[reflector_num_events] == NULL)) {
      app_log_critical("Can not create reflector device JSON object!" APP_LOG_NL);
      app_log_critical(LOGGER_TITLE " is not functional!" APP_LOG_NL);
      sc = SL_STATUS_NULL_POINTER;
    } else {
      cJSON *final_reflector_events = cJSON_CreateArray();
      CHECK_NULL_RETURN(final_reflector_events, sc, FAILED_TO_CREATE_CJSON_OBJECT);
      for (i = 0; i < reflector_num_events; i++) {
        if (jsonl_reflector_events[i] != NULL) {
          cjson_status = cJSON_AddItemToArray(final_reflector_events, jsonl_reflector_events[i]);
          if (!cjson_status) {
            app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
            return SL_STATUS_FAIL;
          }
        } else {
          app_log_error("reflector EVENT %02d lost!" APP_LOG_NL, i);
        }
      }
      obj = cJSON_AddNumberToObject(target_section, MEAS_NUM_EVENTS, reflector_num_events);
      CHECK_NULL_RETURN(obj, sc, FAILED_TO_ADD_CJSON_OBJECT);
      cjson_status = cJSON_AddItemToObject(target_section,
                                           MEAS_EVENTS_ARRAY,
                                           final_reflector_events);
      if (!cjson_status) {
        app_log_error(FAILED_TO_ADD_CJSON_OBJECT);
        return SL_STATUS_FAIL;
      }
      app_log_debug("Appended %d events to reflector section successfully:" APP_LOG_NL,
                    reflector_num_events);
      app_log_debug("%s" APP_LOG_NL, cJSON_PrintUnformatted(final_reflector_events));
    }
  }
  sc = SL_STATUS_OK;
  return sc;
}

/******************************************************************************
 * Disable file logging.
 *****************************************************************************/
static void disable_file_log(void)
{
  file_log_runnable = false;
  if (jsonl_file != NULL) {
    int fs = fclose(jsonl_file);
    if (fs != 0) {
      app_log_error("Failed to close json log file!" APP_LOG_NL);
    }
    jsonl_file = NULL;
  }
}

/******************************************************************************
 * Enable file logging.
 *****************************************************************************/
static void enable_file_log(void)
{
  file_log_runnable = true;
}

/******************************************************************************
 * Return with file logging status.
 *****************************************************************************/
static inline bool is_file_log_enabled(void)
{
  return file_log_runnable;
}

#if (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)
/******************************************************************************
 * Check file existance
 * Opens the target file to read, and if it can be opened it does exist.
 *****************************************************************************/
static bool fexist(const char *filename)
{
  bool r = true;
  FILE *file;

  file = fopen(filename, "r");
  if (file == NULL) {
    r = false;
  } else {
    fclose(file);
  }
  return r;
}
#endif // (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)

/******************************************************************************
 * Setter for the json filename
 * Function considers the measurement mode and if configured appends a postfix
 * accordingly. In case the file already exist the function handles the
 * conflict according to the configuration too:
 * - if the old file must be kept instead of overwriting, the function will
 *   append a postfix to the file-extension according to the configuration
 * - if the old file cannot be renamed the function indicates by text
 *   message (app_log call) and with the return value the logger should
 *   not function to avoid the data loss
 * - if old files should not be considered it will overwrite an existing file
 *****************************************************************************/
static sl_status_t set_filename(uint8_t measurement_mode)
{
  sl_status_t sc = SL_STATUS_OK;
#if (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)
  bool already_exist = false;
  int ret = 1;
  time_t raw_time;
  struct tm *time_info;
  char time_string[TIME_STRLEN] = "\0";
  char backup_filepath[PATH_STRLEN] = "\0";
  char tmp_buffer[PATH_STRLEN] = "\0";
#endif // (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)

  // initialize the filename string before any action
  memset(jsonl_filename, '\0', FILENAME_STRLEN);
  concat_path(jsonl_filename, ABR_FILE_LOG_CFG_FILENAME, FILENAME_STRLEN);

  // append postfix if configured and the measurement mode is known
  if (ABR_FILE_LOG_CFG_MEAS_TYPE_POSTFIX_ENABLE) {
    if (measurement_mode == sl_bt_cs_mode_pbr) {
      concat_path(jsonl_filename, ABR_FILE_LOG_CFG_PBS_POSTFIX, FILENAME_STRLEN);
    } else if (measurement_mode == sl_bt_cs_mode_rtt) {
      concat_path(jsonl_filename, ABR_FILE_LOG_CFG_RTT_POSTFIX, FILENAME_STRLEN);
    } else {
      app_log_warning("Unknown measurement mode: 0x%x" APP_LOG_NL, measurement_mode);
      app_log_append_warning("Could not append mode postfix to filename!" APP_LOG_NL);
    }
  }

  // append extension to filename
  concat_path(jsonl_filename, FILE_EXTENSION, FILENAME_STRLEN);

  // build absolute path
  (void)strncpy(tmp_buffer, jsonl_filepath, sizeof(tmp_buffer));
  // use an intermittent buffer here because it seems if the same array used,
  // the original could be erased before update in some distros
  sc = set_path(jsonl_filepath, PATH_STRLEN, "%s/%s", tmp_buffer, jsonl_filename);
  cleanup_path(jsonl_filepath);

#if (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)
  already_exist = fexist(jsonl_filepath);
  if (already_exist) {
    app_log_warning("%s already exist!" APP_LOG_NL, jsonl_filepath);

    // backup original abs. path string
    (void)strncpy(backup_filepath, jsonl_filepath, sizeof(backup_filepath));

    // append backup postfix
    concat_path(backup_filepath, ABR_FILE_LOG_CFG_BACKUP_POSTFIX, PATH_STRLEN);

    // append datetime in format: 09-11-2023-12_45_34
    time(&raw_time);
    time_info = localtime(&raw_time);

    sc = set_path(time_string, TIME_STRLEN, "%01d-%01d-%d-%01d_%01d_%01d", time_info->tm_mday, time_info->tm_mon + 1,
                  time_info->tm_year + 1900, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);

    // example: */old.jsonl --> */old.jsonl_bkp09-11-2023-12:45:34
    concat_path(backup_filepath, time_string, PATH_STRLEN);
    app_log_warning("Renaming %s --> %s" APP_LOG_NL, jsonl_filepath, backup_filepath);
    // try to rename the old file
    ret = rename(jsonl_filepath, backup_filepath);
    if (ret == 0) {
      app_log_info("Renamed successfully." APP_LOG_NL);
    } else {
      app_log_critical("Unable to rename file! (code: 0x%x)" APP_LOG_NL, ret);
      app_log_critical(LOGGER_TITLE " WILL NOT START to avoid data loss!" APP_LOG_NL);
      sc = SL_STATUS_FAIL;
    }
  }
#endif // (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)

  return sc;
}

#endif // defined(HOST_TOOLCHAIN) && (ABR_FILE_LOG_ENABLED == 1)

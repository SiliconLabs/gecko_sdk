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
#include "cJSON.h"
#include "abr_file_log.h"
#include "abr_file_log_config.h"
#include "sl_malloc.h"
#include "sl_status.h"
#include "app_log.h"
#include "abr_cs_parser_types.h"
#include "abr_cs_parser_config.h"

// -----------------------------------------------------------------------------
// Defines

#define FILENAME_STRLEN                      1024
#define MAX_STRLEN                           FILENAME_STRLEN
#define TIME_STRLEN                          20UL
#define NANOSEC_DIVIDER                      (double)0.000000001

// File section literals
// *INDENT-OFF*
#define FILE_EXTENSION                       ".jsonl"

// jsonl fields
#define HDR_CH_MAP                           "channel_map"
#define HDR_MODE0_STEPS                      "mode_0_steps"
#define HDR_TIMESTAMP                        "timestamp"
#define HDR_TIMESTAMP_REALTIME               "timestamp_realtime"
#define HDR_SDKVERSION                       "sdk_version"

#define MEAS_ESTIMATED_DISTANCE              "estimated_distance"
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

#define RTP_STEP_MODE                        CAL_STEP_MODE
#define RTP_STEP_CHANNEL                     CAL_STEP_CHANNEL
#define RTP_STEP_ANTENNA_PERMUTATION_INDEX   "antenna_permutation_index"
#define RTP_STEP_PCT_I                       "PCT_I"
#define RTP_STEP_PCT_Q                       "PCT_Q"
#define RTP_STEP_TONE_QUALITY                "tone_quality"
// *INDENT-ON*

// Selector for timestamps
typedef enum {
  realtime_clock = 0,
  monotonic_clock,
  both_clocks = 0xff
} abr_file_log_clocktype_t;

// -----------------------------------------------------------------------------
// Module variables.

static FILE * jsonl_file = NULL;
static char jsonl_filename[FILENAME_STRLEN] = " ";
static bool file_conflict = false;

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
static void initialize_cjson_buffers(abr_role_t role);
static sl_status_t append_channel_map(cJSON* const jsonl, const uint8_t *data, const uint32_t data_len);
static sl_status_t append_steps_to_event_header(cJSON **actual_event, const uint32_t num_steps,
                                                cJSON **steps_array, const uint32_t array_size);
static void append_current_time(cJSON * const jsonl, abr_file_log_clocktype_t clock);
static sl_status_t abr_file_log_append_device_section(abr_role_t role, cJSON *target_section);

#if (ABR_FILE_LOG_CFG_KEEP_OLD_FILES)
static bool fexist(const char* filename);
#endif
static sl_status_t set_filename(uint8_t measurement_mode);

static void store_calib_step(abr_role_t role, cs_step_t *step);
static void store_rtt_step(abr_role_t role, cs_step_t *step);
static void store_rtp_step(abr_role_t role, cs_step_t *step);

// -----------------------------------------------------------------------------
// Public function definitions

/******************************************************************************
 * ABR file logger initialization
 * This function sets the target filename and gets the measurement mode.
 *****************************************************************************/
sl_status_t abr_file_log_init(uint8_t abr_mode)
{
  sl_status_t sc = SL_STATUS_OK;

  initialize_cjson_buffers(ABR_DEVICE_INITIATOR);
  initialize_cjson_buffers(ABR_DEVICE_REFLECTOR);

  sc = set_filename(abr_mode);
  if (sc != SL_STATUS_OK) {
    file_conflict = true;
  }

  app_log_info("File logger initiatized." APP_LOG_NL);
  return sc;
}

/******************************************************************************
 * ABR file logger deinitialization
 * Closing file if its still open.
 *****************************************************************************/
sl_status_t abr_file_log_deinit(void)
{
  sl_status_t sc = SL_STATUS_OK;
  FILE *f;

  // *INDENT-OFF*
  f = fopen(jsonl_filename,"w+");
  if (f != NULL) {
    fclose(f);
    app_log_warning("%s was still open. Closed file." APP_LOG_NL, jsonl_filename);
  }
  // *INDENT-ON*

  return sc;
}

/******************************************************************************
 * ABR file logger get application version
 * Gets application version info for loggin.
 *****************************************************************************/
void abr_file_log_app_version(uint16_t major, uint16_t minor,
                              uint16_t patch, uint16_t build)
{
  sw_major = major;
  sw_minor = minor;
  sw_patch = patch;
  sw_build = build;
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
  sl_status_t sc = SL_STATUS_OK;
  cJSON *jsonl_header = cJSON_CreateObject();
  char sdk_version_string[MAX_STRLEN];
  char *header_string;
  int printed_bytes = 0, i = 0, max_iteration = 1;

#if (ABR_FILE_LOG_CFG_RETRY_FPRINTF && (ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT > 1))
  max_iteration = ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT;
#endif // (ABR_FILE_LOG_CFG_RETRY_FPRINTF && (ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT > 0))

  append_current_time(jsonl_header, both_clocks);

  sprintf(sdk_version_string, "%d.%d.%d.%d", sw_major, sw_minor, sw_patch, sw_build);

  cJSON_AddStringToObject(jsonl_header, HDR_SDKVERSION, sdk_version_string);

  sc = append_channel_map(jsonl_header, ch_data, ch_data_len);

  cJSON_AddIntegerToObject(jsonl_header, HDR_MODE0_STEPS, mode0_steps_count);

  if (!file_conflict) {
    if (ABR_FILE_LOG_CFG_FORMATTED_PRINT) {
      header_string = cJSON_Print(jsonl_header);
    } else {
      header_string = cJSON_PrintUnformatted(jsonl_header);
    }
    app_log_info("Open file %s to write header..." APP_LOG_NL, jsonl_filename);
    jsonl_file = fopen(jsonl_filename, "w");
    if (jsonl_file != NULL) {
      app_log_debug("Appending file header..." APP_LOG_NL);

      for (i = 0; i < max_iteration; i++) {
        if (ABR_FILE_LOG_CFG_FORCE_ADD_NEWLINE == 1) {
          printed_bytes = fprintf(jsonl_file, "%s" ABR_FILE_LOG_CFG_NL, header_string);
        } else {
          printed_bytes = fprintf(jsonl_file, "%s", header_string);
        }
        if (printed_bytes >= 0) {
          app_log_debug("Written %d bytes into the file." APP_LOG_NL, printed_bytes);
          sc = SL_STATUS_OK;
          break;
        } else {
          app_log_warning("Failed to write file.");
          if (max_iteration > 1) {
            app_log_append_warning("Retrying ..." APP_LOG_NL);
          }
          sc = SL_STATUS_FAIL;
        }
      }
      if (sc == SL_STATUS_FAIL) {
        app_log_error("Appending header failed, retried %d times. (code: 0x%x)" APP_LOG_NL,
                      max_iteration, printed_bytes);
      } else {
        app_log_debug("Appended header, closing file..." APP_LOG_NL);
      }
      fclose(jsonl_file);
      // sl_free() is a necessary step here because of cJSON_Print()
      // usage above
      sl_free(header_string);
      header_string = NULL;
    } else {
      app_log_error("Cannot open file %s!" APP_LOG_NL, jsonl_filename);
      sc = SL_STATUS_NULL_POINTER;
    }
  } else {
    app_log_error("Cannot open file to avoid data loss!" APP_LOG_NL);
    sc = SL_STATUS_FAIL;
  }

  app_log_debug("Measurement cycle %04u starts." APP_LOG_NL, measurement_cycle);
  initiator_num_events = 0;
  reflector_num_events = 0;

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
  sl_status_t sc = SL_STATUS_OK;

  // Check input parameters
  if (cs_res != NULL) {
    // At this point it is not known how many events may come yet so
    // we can only add the following elements to the event object:
    // - start_acl_conn_event
    // - timestamp (the moment when the event detected here)
    if (role == ABR_DEVICE_INITIATOR) {
      initiator_num_steps = 0;
      cJSON_AddIntegerToObject(jsonl_initiator_events[initiator_num_events],
                               MEAS_EVENT_ID,
                               cs_res->start_acl_conn_event);
      cJSON_AddIntegerToObject(jsonl_initiator_events[initiator_num_events],
                               MEAS_EVENT_PROC_CNT,
                               cs_res->procedure_counter);
      cJSON_AddIntegerToObject(jsonl_initiator_events[initiator_num_events],
                               MEAS_EVENT_FREQ_COMP,
                               cs_res->frequency_compensation);
      cJSON_AddIntegerToObject(jsonl_initiator_events[initiator_num_events],
                               MEAS_EVENT_PROC_DONE_STS,
                               cs_res->procedure_done_status);
      cJSON_AddIntegerToObject(jsonl_initiator_events[initiator_num_events],
                               MEAS_SUBEVENT_DONE_STS,
                               cs_res->subevent_done_status);
      cJSON_AddIntegerToObject(jsonl_initiator_events[initiator_num_events],
                               MEAS_EVENT_ABORT_REASON,
                               cs_res->abort_reason);
      cJSON_AddIntegerToObject(jsonl_initiator_events[initiator_num_events],
                               MEAS_EVENT_REF_POWER_LVL,
                               cs_res->reference_power_level);
      cJSON_AddIntegerToObject(jsonl_initiator_events[initiator_num_events],
                               MEAS_EVENT_NUM_ANT_PATHS,
                               cs_res->num_antenna_paths);
      append_current_time(jsonl_initiator_events[initiator_num_events], both_clocks);
      app_log_debug("<<< %02d. initiator EVENT processing begin >>>" APP_LOG_NL, initiator_num_events);
    } else {
      reflector_num_steps = 0;
      cJSON_AddIntegerToObject(jsonl_reflector_events[reflector_num_events],
                               MEAS_EVENT_ID,
                               cs_res->start_acl_conn_event);
      cJSON_AddIntegerToObject(jsonl_reflector_events[reflector_num_events],
                               MEAS_EVENT_PROC_CNT,
                               cs_res->procedure_counter);
      cJSON_AddIntegerToObject(jsonl_reflector_events[reflector_num_events],
                               MEAS_EVENT_FREQ_COMP,
                               cs_res->frequency_compensation);
      cJSON_AddIntegerToObject(jsonl_reflector_events[reflector_num_events],
                               MEAS_EVENT_PROC_DONE_STS,
                               cs_res->procedure_done_status);
      cJSON_AddIntegerToObject(jsonl_reflector_events[reflector_num_events],
                               MEAS_SUBEVENT_DONE_STS,
                               cs_res->subevent_done_status);
      cJSON_AddIntegerToObject(jsonl_reflector_events[reflector_num_events],
                               MEAS_EVENT_ABORT_REASON,
                               cs_res->abort_reason);
      cJSON_AddIntegerToObject(jsonl_reflector_events[reflector_num_events],
                               MEAS_EVENT_REF_POWER_LVL,
                               cs_res->reference_power_level);
      cJSON_AddIntegerToObject(jsonl_reflector_events[reflector_num_events],
                               MEAS_EVENT_NUM_ANT_PATHS,
                               cs_res->num_antenna_paths);
      append_current_time(jsonl_reflector_events[reflector_num_events], both_clocks);
      app_log_debug("<<< %02d. reflector EVENT processing begin >>>" APP_LOG_NL, reflector_num_events);
    }
  } else {
    app_log_error("Invalid input parameter!" APP_LOG_NL);
    sc = SL_STATUS_NULL_POINTER;
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
  if (num_steps != 0) {
    if (role == ABR_DEVICE_INITIATOR) {
      sc = append_steps_to_event_header(&jsonl_initiator_events[initiator_num_events],
                                        num_steps,
                                        jsonl_initiator_steps,
                                        initiator_num_steps);
      app_log_debug("%s" APP_LOG_NL, cJSON_PrintUnformatted(jsonl_initiator_events[initiator_num_events]));
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

  return sc;
}

/******************************************************************************
 * Store step data
 * Parsed and saved properties according to the actual mode and role.
 * There is also an option to keep the old jsonl format of the steps or extend
 * them with additional properties.
 * The function also increments the step counters.
 *****************************************************************************/
sl_status_t abr_file_log_store_step(abr_role_t role, cs_step_t * step_data)
{
  sl_status_t sc = SL_STATUS_OK;
  if (step_data != NULL) {
    switch (step_data->step_mode) {
      case sl_bt_cs_mode_calibration:
        store_calib_step(role, step_data);
        break;

      case sl_bt_cs_mode_rtt:
        store_rtt_step(role, step_data);
        break;

      case sl_bt_cs_mode_pbr:
        store_rtp_step(role, step_data);
        break;

      case sl_bt_cs_mode_pbr_and_rtt:       // Reserved for the future
        break;

      default:
        break;
    }
  } else {
    app_log_error("No step data detected!" APP_LOG_NL);
    sc = SL_STATUS_NULL_POINTER;
  }

  return sc;
}

static void store_calib_step(abr_role_t role, cs_step_t * step)
{
  if (role == ABR_DEVICE_INITIATOR) {
    jsonl_initiator_steps[initiator_num_steps] = cJSON_CreateObject();
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], CAL_STEP_MODE, step->step_mode);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], CAL_STEP_CHANNEL, step->step_channel);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], CAL_STEP_RSSI,
                             step->data.initiator_calib.rssi);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], CAL_STEP_FREQ_OFFSET,
                             step->data.initiator_calib.freq_offset);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], CAL_STEP_PACKET_ANTENNA,
                             step->data.initiator_calib.packet_antenna);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], CAL_STEP_PACKET_QUALITY,
                             step->data.initiator_calib.packet_quality);
    app_log_debug(" %02d: initiator calib.step stored." APP_LOG_NL, initiator_num_steps);
    initiator_num_steps++;
  } else {
    jsonl_reflector_steps[reflector_num_steps] = cJSON_CreateObject();
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], CAL_STEP_MODE, step->step_mode);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], CAL_STEP_CHANNEL, step->step_channel);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], CAL_STEP_RSSI,
                             step->data.reflector_calib.rssi);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], CAL_STEP_PACKET_ANTENNA,
                             step->data.reflector_calib.packet_antenna);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], CAL_STEP_PACKET_QUALITY,
                             step->data.reflector_calib.packet_quality);
    app_log_debug(" %02d: reflector calib.step stored." APP_LOG_NL, reflector_num_steps);
    reflector_num_steps++;
  }
}

static void store_rtt_step(abr_role_t role, cs_step_t * step)
{
  if (role == ABR_DEVICE_INITIATOR) {
    jsonl_initiator_steps[initiator_num_steps] = cJSON_CreateObject();
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTT_STEP_MODE, step->step_mode);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTT_STEP_CHANNEL, step->step_channel);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTT_STEP_NADM, step->data.meas_rtt.nadm);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTT_STEP_RSSI, step->data.meas_rtt.rssi);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTT_STEP_TOD_TOA, step->data.meas_rtt.tod_toa);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTT_STEP_ANTENNA, step->data.meas_rtt.antenna);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTT_STEP_PACKET_QUALITY,
                             step->data.meas_rtt.packet_quality);
    app_log_debug(" %02d: initiator rtt step stored." APP_LOG_NL, initiator_num_steps);
    initiator_num_steps++;
  } else {
    jsonl_reflector_steps[reflector_num_steps] = cJSON_CreateObject();
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTT_STEP_MODE, step->step_mode);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTT_STEP_CHANNEL, step->step_channel);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTT_STEP_NADM, step->data.meas_rtt.nadm);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTT_STEP_RSSI, step->data.meas_rtt.rssi);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTT_STEP_TOD_TOA, step->data.meas_rtt.tod_toa);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTT_STEP_ANTENNA, step->data.meas_rtt.antenna);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTT_STEP_PACKET_QUALITY,
                             step->data.meas_rtt.packet_quality);
    app_log_debug(" %02d: reflector rtt step stored." APP_LOG_NL, reflector_num_steps);
    reflector_num_steps++;
  }
}

static void store_rtp_step(abr_role_t role, cs_step_t * step)
{
  cJSON *pct_i_array = cJSON_CreateFloatArray(step->data.meas_rtp.pct_i, ANTENNA_PERMUTATION_MAX);
  cJSON *pct_q_array = cJSON_CreateFloatArray(step->data.meas_rtp.pct_q, ANTENNA_PERMUTATION_MAX);

  int tone_quality_iter;
  int tone_quality[ANTENNA_PERMUTATION_MAX];

  for (tone_quality_iter = 0; tone_quality_iter < ANTENNA_PERMUTATION_MAX; tone_quality_iter++) {
    tone_quality[tone_quality_iter] = step->data.meas_rtp.tone_quality[tone_quality_iter];
  }

  cJSON *tone_quality_array = cJSON_CreateIntArray(tone_quality, ANTENNA_PERMUTATION_MAX);

  if (role == ABR_DEVICE_INITIATOR) {
    jsonl_initiator_steps[initiator_num_steps] = cJSON_CreateObject();
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTP_STEP_MODE, step->step_mode);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTP_STEP_CHANNEL, step->step_channel);
    cJSON_AddIntegerToObject(jsonl_initiator_steps[initiator_num_steps], RTP_STEP_ANTENNA_PERMUTATION_INDEX, step->data.meas_rtp.antenna_permutation_index);
    cJSON_AddItemToObject(jsonl_initiator_steps[initiator_num_steps], RTP_STEP_PCT_I, pct_i_array);
    cJSON_AddItemToObject(jsonl_initiator_steps[initiator_num_steps], RTP_STEP_PCT_Q, pct_q_array);
    cJSON_AddItemToObject(jsonl_initiator_steps[initiator_num_steps], RTP_STEP_TONE_QUALITY, tone_quality_array);
    app_log_debug(" %02d: initiator rtp step stored." APP_LOG_NL, initiator_num_steps);
    initiator_num_steps++;
  } else {
    jsonl_reflector_steps[reflector_num_steps] = cJSON_CreateObject();
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTP_STEP_MODE, step->step_mode);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTP_STEP_CHANNEL, step->step_channel);
    cJSON_AddIntegerToObject(jsonl_reflector_steps[reflector_num_steps], RTP_STEP_ANTENNA_PERMUTATION_INDEX, step->data.meas_rtp.antenna_permutation_index);
    cJSON_AddItemToObject(jsonl_reflector_steps[reflector_num_steps], RTP_STEP_PCT_I, pct_i_array);
    cJSON_AddItemToObject(jsonl_reflector_steps[reflector_num_steps], RTP_STEP_PCT_Q, pct_q_array);
    cJSON_AddItemToObject(jsonl_reflector_steps[reflector_num_steps], RTP_STEP_TONE_QUALITY, tone_quality_array);
    app_log_debug(" %02d: reflector rtp step stored." APP_LOG_NL, reflector_num_steps);
    reflector_num_steps++;
  }
}

/******************************************************************************
 * ABR file log finalize measurement section
 * Gets all the initiator and reflector data and stores in together with the
 * estimated distance to the target log file.
 *****************************************************************************/
sl_status_t abr_file_log_finalize_measurement_section(float *estimated_distance)
{
  sl_status_t sc = SL_STATUS_OK;
  char *raw_content = NULL;
  int written_bytes = 0;
  int i = 0, max_iteration = 1;

#if (ABR_FILE_LOG_CFG_RETRY_FPRINTF && (ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT > 1))
  max_iteration = ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT;
#endif // (ABR_FILE_LOG_CFG_RETRY_FPRINTF && (ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT > 0))

  cJSON *initiator_section = cJSON_CreateObject();
  cJSON *reflector_section = cJSON_CreateObject();
  cJSON *measurement_section = cJSON_CreateObject();

  app_log_info("Log measurement cycle %04u ..." APP_LOG_NL, measurement_cycle);

  sc = abr_file_log_append_device_section(ABR_DEVICE_INITIATOR, initiator_section);
  sc = abr_file_log_append_device_section(ABR_DEVICE_REFLECTOR, reflector_section);

  cJSON_AddDoubleToObject(measurement_section, MEAS_ESTIMATED_DISTANCE, *estimated_distance);
  cJSON_AddItemToObject(measurement_section, MEAS_INITIATOR_BEGIN, initiator_section);
  cJSON_AddItemToObject(measurement_section, MEAS_REFLECTOR_BEGIN, reflector_section);

  if (sc == SL_STATUS_OK) {
    if (ABR_FILE_LOG_CFG_FORMATTED_PRINT) {
      raw_content = cJSON_Print(measurement_section);
    } else {
      raw_content = cJSON_PrintUnformatted(measurement_section);
    }
    // Free up the memory - kill all the subsections to start fresh
    cJSON_Delete(measurement_section);

    if (!file_conflict) {
      app_log_debug("Opening file \'%s\' to write" APP_LOG_NL, jsonl_filename);
      jsonl_file = fopen(jsonl_filename, "a");
      if (jsonl_file == NULL) {
        app_log_error("Unable to open file for write." APP_LOG_NL);
        app_log_error("Logger non-functional!" APP_LOG_NL);
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
            app_log_debug("Printed %d bytes to the filestream." APP_LOG_NL, written_bytes);
            fclose(jsonl_file);
            break;
          } else {
            if (max_iteration > 1) {
              app_log_warning("Retrying..." APP_LOG_NL);
            }
            sc = SL_STATUS_FAIL;
          }
        }
        if (sc == SL_STATUS_FAIL) {
          app_log_error("Retried %d times. Check file write permissions or", ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT);
          app_log_error("that the file is not in use anywhere else!" APP_LOG_NL);
        }
      }
    }
  } else {
    app_log_error("Cannot open file to avoid data loss!" APP_LOG_NL);
    app_log_error("Logger non-functional!" APP_LOG_NL);
    sc = SL_STATUS_FAIL;
  }

  // Prepare for the next measurement cycle
  if (sc == SL_STATUS_OK) {
    measurement_cycle++;
    app_log_debug("Measurement cycle %04u starts" APP_LOG_NL, measurement_cycle);
    initiator_num_events = 0;
    reflector_num_events = 0;
    initialize_cjson_buffers(ABR_DEVICE_INITIATOR);
    initialize_cjson_buffers(ABR_DEVICE_REFLECTOR);
  }

  return sc;
}

// -----------------------------------------------------------------------------
// Private function definitions

static void initialize_cjson_buffers(abr_role_t role)
{
  int i;
  if (role == ABR_DEVICE_INITIATOR) {
    for (i = 0; i < ABR_FILE_LOG_CFG_MAX_EVENTS; i++) {
      jsonl_initiator_events[i] = cJSON_CreateObject();
    }
    for (i = 0; i < ABR_FILE_LOG_CFG_MAX_STEPS; i++) {
      jsonl_initiator_steps[i] = cJSON_CreateObject();
    }
  } else {
    for (i = 0; i < ABR_FILE_LOG_CFG_MAX_EVENTS; i++) {
      jsonl_reflector_events[i] = cJSON_CreateObject();
    }
    for (i = 0; i < ABR_FILE_LOG_CFG_MAX_STEPS; i++) {
      jsonl_reflector_steps[i] = cJSON_CreateObject();
    }
  }
}

/******************************************************************************
 * Append the channel_map to the header
 *****************************************************************************/
static sl_status_t append_channel_map(cJSON * const jsonl,
                                      const uint8_t * data,
                                      const uint32_t data_len)
{
  sl_status_t sc = SL_STATUS_OK;
  char *channel_map_string;
  uint32_t string_memsize;
  int memory_position = 0, written_bytes = 0;

  string_memsize = (data_len * 2) + 1;

  if ((string_memsize > 0) && (string_memsize < UINT32_MAX)) {
    app_log_debug("Allocate %d bytes for the channel map." APP_LOG_NL, string_memsize);
    // Avoiding resonance cascase λ
    channel_map_string = sl_calloc(string_memsize, sizeof(char));
    if (channel_map_string != NULL) {
      app_log_debug("Allocated %d bytes of heap." APP_LOG_NL, string_memsize);
      // Copy channel map to the string
      for (int i = 0; i < data_len; i++) {
        written_bytes = sprintf(&channel_map_string[memory_position], "%02x", data[i]);
        memory_position += written_bytes;
      }
      cJSON_AddStringToObject(jsonl, HDR_CH_MAP, channel_map_string);
      // Free memory only if allocated before
      sl_free(channel_map_string);
      channel_map_string = NULL;
    } else {
      app_log_critical("Memory allocation failed! Cannot proceed!" APP_LOG_NL);
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  } else {
    app_log_error("Invalid parameter for data_len=%d!" APP_LOG_NL, data_len);
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
  int i;
  if ((*actual_event != NULL) && (*steps_array != NULL)  \
      && (actual_event != NULL) && (steps_array != NULL) \
      && (num_steps != 0) && (array_size != 0)) {
    cJSON_AddIntegerToObject(*actual_event, MEAS_NUM_STEPS, num_steps);
    // Copy all non-empty steps into a temporary array and add it to the actual
    // event
    cJSON *temp_array = cJSON_CreateArray();
    for (i = 0; i < array_size; i++) {
      if (steps_array[i] != NULL) {
        cJSON_AddItemToArray(temp_array, steps_array[i]);
        app_log_debug("step %02d/%02d: %s" APP_LOG_NL, i, num_steps, cJSON_PrintUnformatted(steps_array[i]));
      } else {
        app_log_error("step %02d is null-pointer!" APP_LOG_NL, i);
      }
    }
    cJSON_AddItemToObject(*actual_event, MEAS_STEPS_ARRAY, temp_array);
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
static void append_current_time(cJSON * const jsonl, abr_file_log_clocktype_t clock)
{
  struct timespec current_timestamp, current_timestamp_rt;

  double tstamp = 0.0, tstamp_realtime = 0.0;
  char timestamp_string[TIME_STRLEN], timestamp_string_rt[TIME_STRLEN];

  if (clock == both_clocks || clock == monotonic_clock) {
    clock_gettime(CLOCK_MONOTONIC, &current_timestamp);
    if (ABR_FILE_LOG_CFG_NUMERIC_TIMESTAMPS == 1) {
      tstamp = ((double)current_timestamp.tv_sec + (double)current_timestamp.tv_nsec * NANOSEC_DIVIDER);
      cJSON_AddDoubleToObject(jsonl, HDR_TIMESTAMP, tstamp);
    } else {
      snprintf(timestamp_string, TIME_STRLEN, "%lld.%.9ld",
               (long long)current_timestamp.tv_sec, current_timestamp.tv_nsec);
      cJSON_AddStringToObject(jsonl, HDR_TIMESTAMP, timestamp_string);
    }
  }

  if (clock == both_clocks || clock == realtime_clock) {
    clock_gettime(CLOCK_REALTIME, &current_timestamp_rt);
    if (ABR_FILE_LOG_CFG_NUMERIC_TIMESTAMPS == 1) {
      tstamp_realtime = ((double)current_timestamp_rt.tv_sec + (double)current_timestamp_rt.tv_nsec * NANOSEC_DIVIDER);
      cJSON_AddDoubleToObject(jsonl, HDR_TIMESTAMP_REALTIME, tstamp_realtime);
    } else {
      snprintf(timestamp_string_rt, TIME_STRLEN, "%lld.%.9ld",
               (long long)current_timestamp_rt.tv_sec, current_timestamp_rt.tv_nsec);
      cJSON_AddStringToObject(jsonl, HDR_TIMESTAMP_REALTIME, timestamp_string_rt);
    }
  }
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
static sl_status_t abr_file_log_append_device_section(abr_role_t role, cJSON * target_section)
{
  sl_status_t sc = SL_STATUS_OK;
  int i;
  if (role == ABR_DEVICE_INITIATOR) {
    if ((target_section == NULL) || (jsonl_initiator_events[initiator_num_events] == NULL)) {
      app_log_critical("Can not create initiator device cJSON object!" APP_LOG_NL);
      app_log_critical("ABR file logger is not functional!" APP_LOG_NL);
      sc = SL_STATUS_NULL_POINTER;
    } else {
      cJSON * final_initiator_events = cJSON_CreateArray();
      for (i = 0; i < initiator_num_events; i++) {
        if (jsonl_initiator_events[i] != NULL) {
          cJSON_AddItemToArray(final_initiator_events, jsonl_initiator_events[i]);
        } else {
          app_log_error("initiator EVENT %02d lost!" APP_LOG_NL, i);
        }
      }
      cJSON_AddIntegerToObject(target_section, MEAS_NUM_EVENTS, initiator_num_events);
      cJSON_AddItemToObject(target_section, MEAS_EVENTS_ARRAY, final_initiator_events);
      app_log_debug("Appended %d events to initiator section successfully:" APP_LOG_NL, initiator_num_events);
      app_log_debug("%s" APP_LOG_NL, cJSON_PrintUnformatted(final_initiator_events));
    }
  } else {
    if ((target_section == NULL) || (jsonl_reflector_events[reflector_num_events] == NULL)) {
      app_log_critical("Can not create reflector device cJSON object!" APP_LOG_NL);
      app_log_critical("ABR file logger is not functional!" APP_LOG_NL);
      sc = SL_STATUS_NULL_POINTER;
    } else {
      cJSON * final_reflector_events = cJSON_CreateArray();
      for (i = 0; i < reflector_num_events; i++) {
        if (jsonl_reflector_events[i] != NULL) {
          cJSON_AddItemToArray(final_reflector_events, jsonl_reflector_events[i]);
        } else {
          app_log_error("reflector EVENT %02d lost!" APP_LOG_NL, i);
        }
      }
      cJSON_AddIntegerToObject(target_section, MEAS_NUM_EVENTS, reflector_num_events);
      cJSON_AddItemToObject(target_section, MEAS_EVENTS_ARRAY, final_reflector_events);
      app_log_debug("Appended %d events to reflector section successfully:" APP_LOG_NL, reflector_num_events);
      app_log_debug("%s" APP_LOG_NL, cJSON_PrintUnformatted(final_reflector_events));
    }
  }
  return sc;
}

#if (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)
/******************************************************************************
 * Check file existance
 * Opens the target file to read, and if it can be opened it does exist.
 *****************************************************************************/
static bool fexist(const char* filename)
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
  char time_string[TIME_STRLEN] = "";
  char backup_filename[FILENAME_STRLEN] = "";
#endif // (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)

  // initialize the filename string before any action
  memset(jsonl_filename, '\0', FILENAME_STRLEN);
  // return value ignored by strcat() calls because only the pointer to
  // the first parameter is retured - that is already known
  (void)strcat(jsonl_filename, ABR_FILE_LOG_CFG_FILENAME);

  if (ABR_FILE_LOG_CFG_MEAS_TYPE_POSTFIX_ENABLE) {
    if (measurement_mode == sl_bt_cs_mode_pbr) {
      (void)strcat(jsonl_filename, ABR_FILE_LOG_CFG_PBS_POSTFIX);
    } else if (measurement_mode == sl_bt_cs_mode_rtt) {
      (void)strcat(jsonl_filename, ABR_FILE_LOG_CFG_RTT_POSTFIX);
    } else {
      app_log_warning("Unknown measurement mode: 0x%x" APP_LOG_NL, measurement_mode);
      app_log_warning("Could not append mode postfix to filename!" APP_LOG_NL);
    }
  }
  // append extension
  (void)strcat(jsonl_filename, FILE_EXTENSION);

#if (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)
  already_exist = fexist(jsonl_filename);
  if (already_exist) {
    app_log_warning("%s already exist!" APP_LOG_NL, jsonl_filename);

    // load filename & append backup postfix
    (void)snprintf(backup_filename, sizeof(jsonl_filename), "%s", jsonl_filename);
    (void)strcat(backup_filename, ABR_FILE_LOG_CFG_BACKUP_POSTFIX);

    // append datetime in format: 09-11-2023-12_45_34
    time(&raw_time);
    time_info = localtime(&raw_time);

    sprintf(time_string, "%01d-%01d-%d-%01d_%01d_%01d",
            time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec);

    //example: old.jsnl --> old.jsonl_bkp09-11-2023-12:45:34
    (void)strcat(backup_filename, time_string);

    app_log_warning("Renaming %s --> %s" APP_LOG_NL, jsonl_filename, backup_filename);
    // try to rename the old file
    ret = rename(jsonl_filename, backup_filename);
    if (ret == 0) {
      app_log_info("Renamed successfully." APP_LOG_NL);
    } else {
      app_log_error("Unable to rename file! (code: 0x%x)" APP_LOG_NL, ret);
      app_log_error("Logger WILL NOT START to avoid data loss!" APP_LOG_NL);
      sc = SL_STATUS_FAIL;
    }
  }
#endif // (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)

  return sc;
}

#endif // defined(HOST_TOOLCHAIN) && (ABR_FILE_LOG_ENABLED == 1)

/***************************************************************************//**
 * @file
 * @brief ABR CS Parser component.
 *
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
#include <stdlib.h>
#include <unistd.h>
#include "sl_status.h"
#include "app_log.h"
#include "abr_cs_parser.h"
#include "abr_cs_parser_config.h"
#include "abr_file_log.h"

// -----------------------------------------------------------------------------
// Definitions

#define MAX_NUM_CHANNELS      80                // Maximum CS channel number
#define CS_MODE_CALIBRATION   0                 // Calibration CS mode
#define CS_MODE_RTT           sl_bt_cs_mode_rtt   // RTT CS mode
#define CS_MODE_RTP           sl_bt_cs_mode_pbr   // RTP CS mode
#define CS_MODE_COMBINED      sl_bt_cs_mode_pbr_and_rtt   // Combined CS mode
#define RTT_VALUE_LEN         6                 // RTT data field length
#define LL_INVALID_TOA        0x800             // Invalid time value from LL
#define PCT_DATA_MASK_LOW     0x00000FFF        // Tone PCT mask low
#define PCT_DATA_MASK_HIGH    0x00FFF000        // Tone PCT mask high
#define PCT_IQ_LEN            12                // PCT IQ sample length
#define PCT_BYTE_COUNT        3                 // Tone PCT byte count in data field
#define CS_PROCEDURE_ABORTED  0x0F              // All subsequent CS procedures aborted
#define CS_SUBEVENT_ABORTED   0x0F              // Current CS subevent aborted
#define BYTE_LEN              8                 // Byte length in bits
#define INVALID_TIME_VALUE    0x80000000        // Invalid RTL library time value
#define INVALID_RSSI_VALUE    0x80000000        // Invalid RTL library RSSI value
#define TONE_PCT_INVALID      ((uint32_t)0xFFFFFF)      // Invalid tone PCT value
#define MIN(a, b)             (((a) < (b)) ? (a) : (b)) // Minimum calculation
#define DEFAULT_FREQUENCY_DELTA 2e6f                    // Channel frequency delta

/// Check status code, log warning and return
#define CHECK_STATUS_RETURN(sc, ...) \
  do {                               \
    if ((sc) != SL_STATUS_OK) {      \
      app_log_warning(__VA_ARGS__);  \
      return (sc);                   \
    }                                \
  } while (0)

// -----------------------------------------------------------------------------
// Enums, structs, typedefs

/// RTT measurement related data
typedef struct {
  sl_rtl_abr_rtt_data   rtl_input;                        ///< RTT data for RTL library
  uint8_t               initiator_idx;                    ///< Initiator data index
  uint8_t               reflector_idx;                    ///< Reflector data index
  int32_t               rssi_initiator[MAX_NUM_CHANNELS]; ///< Initiator RSSI measurements
  int32_t               rssi_reflector[MAX_NUM_CHANNELS]; ///< Reflector RSSI measurements
  int32_t               time_initiator[MAX_NUM_CHANNELS]; ///< Initiator time measurements
  int32_t               time_reflector[MAX_NUM_CHANNELS]; ///< Reflector time measurements
} rtt_measurement_t;

/// RTP measurement related data
typedef struct {
  sl_rtl_abr_rtp_data rtl_input;                ///< RTP data for RTL library
  float initiator_i_samples[MAX_NUM_CHANNELS];  ///< IQ-data I-components from initiator
  float initiator_q_samples[MAX_NUM_CHANNELS];  ///< IQ-data Q-components from initiator
  float reflector_i_samples[MAX_NUM_CHANNELS];  ///< IQ-data I-components from reflector
  float reflector_q_samples[MAX_NUM_CHANNELS];  ///< IQ-data Q-components from reflector
} rtp_measurement_t;

/// CS measurement data
typedef struct {
  uint8_t                 connection;               ///< Connection handle
  bool                    restart_needed;           ///< CS measurement restart needed
  bool                    initiator_ready;          ///< Initiator ready flag
  bool                    reflector_ready;          ///< Reflector ready flag
  bool                    ready_to_process;         ///< CS measurement data is ready to processed
  uint32_t                initiator_procedure_cnt;  ///< Initiator procedure count
  uint32_t                reflector_procedure_cnt;  ///< Reflector procedure count
  cs_step_t               step_data;                ///< Step data container
  rtt_measurement_t       rtt_data;                 ///< RTT measurement data
  rtp_measurement_t       rtp_data;                 ///< RTP measurement data
  reflector_calibration_t reflector_calib;          ///< Reflector calibration data
  initiator_calibration_t initiator_calib;          ///< Initiator claibration data
} cs_measurement_t;

/// CS parser structure
typedef struct {
  uint32_t                      channels_number;                      ///< Number of channels
  uint32_t                      num_tones;                            ///< Number of tones (frequencies)
  uint32_t                      blank_tone_channels[MAX_NUM_CHANNELS];///< Blank tone channels
  uint32_t                      num_blank_tone_indices;               ///< Number of blank tones
  uint8_t                       mode_0_steps;                         ///< Number of mode 0 steps included
  cs_measurement_t              measurements[NUM_OF_REFLECTORS];      ///< CS measurements
  uint8_t                       initialized;                          ///< Parser initialized flag
  abr_cs_parser_configuration_t config;                               ///< CS parser configuration
} abr_cs_parser_t;

// -----------------------------------------------------------------------------
// Forward declaration of private functions
static sl_status_t set_channel_map(const uint8_t *channel_map,
                                   const uint32_t channel_map_len);
static sl_status_t parse_event_result_data(sl_bt_evt_cs_result_t *cs_res,
                                           abr_role_t             role);
static sl_status_t parse_steps(sl_bt_evt_cs_result_t *cs_res,
                               abr_role_t             role,
                               cs_measurement_t      *meas);
static sl_status_t parse_one_step(uint8_t   *data,
                                  uint32_t   data_size,
                                  abr_role_t role,
                                  uint32_t  *read_cnt,
                                  cs_step_t *out);
static sl_status_t read_byte(const uint8_t *data,
                             uint32_t data_size,
                             uint32_t *read_cnt,
                             uint8_t *out);
static sl_status_t check_cs_event_flags(sl_bt_evt_cs_result_t *cs_res,
                                        cs_measurement_t *meas);
static void update_measurement_flags(cs_measurement_t *meas,
                                     abr_role_t role);
static void check_measurement_completed(cs_measurement_t *meas);
static sl_status_t parse_calibration_initiator(const uint8_t* data,
                                               uint32_t       data_size,
                                               uint32_t      *read_cnt,
                                               cs_step_t     *out);
static sl_status_t parse_calibration_reflector(const uint8_t* data,
                                               uint32_t       data_size,
                                               uint32_t      *read_cnt,
                                               cs_step_t     *out);
static sl_status_t parse_rtt_step(const uint8_t *data,
                                  uint32_t       data_size,
                                  uint32_t      *read_cnt,
                                  cs_step_t     *step_data);
static int16_t tone_pct_to_int(uint32_t tone_pct);
static sl_status_t parse_rtp_step(const uint8_t *data,
                                  uint32_t       data_size,
                                  uint32_t      *read_cnt,
                                  cs_step_t     *step_data);
static sl_status_t get_measurement_index_from_connection(uint8_t connection,
                                                         uint8_t *index);
static sl_status_t get_measurement_from_connection(cs_measurement_t **meas,
                                                   uint8_t            conn);
static void clear_measurement_buffers(void);
static void clear_measurement_buffer(cs_measurement_t *meas);
static void set_restart_needed(cs_measurement_t *meas, bool needed);
static sl_status_t add_rtt_data_to_measurement(rtt_measurement_t *meas,
                                               cs_step_t         *step_data,
                                               abr_role_t         role);
static sl_status_t add_rtp_data_to_measurement(rtp_measurement_t *meas,
                                               cs_step_t         *step_data,
                                               abr_role_t         role);
static sl_status_t add_calibration_data_to_measurement(cs_measurement_t  *meas,
                                                       cs_step_t         *step_data,
                                                       abr_role_t         role);

// -----------------------------------------------------------------------------
// Private variables

/// CS parser state
static abr_cs_parser_t cs_parser;

// -----------------------------------------------------------------------------
// Public functions

sl_status_t abr_cs_parser_init(abr_cs_parser_configuration_t *config)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER;
  sl_status_t ret_log = SL_STATUS_OK;

  if (config != NULL) {
    cs_parser.channels_number = MAX_NUM_CHANNELS;
    cs_parser.mode_0_steps = 1;
    cs_parser.config = *config;
    for (uint8_t i = 0; i < NUM_OF_REFLECTORS; i++) {
      cs_parser.measurements[i].connection = SL_BT_INVALID_CONNECTION_HANDLE;
    }
    clear_measurement_buffers();
    cs_parser.initialized = 1;
    ret = SL_STATUS_OK;
  }
  ret_log = abr_file_log_init(config->measurement_mode);
  if (ret_log != SL_STATUS_OK) {
    app_log_error("abr_file_log is not functional! No valid logs will be produced! (code: 0x%x)" APP_LOG_NL, ret_log);
  }
  return ret;
}

sl_status_t abr_cs_parser_configure(const uint8_t  *ch_data,
                                    uint32_t        ch_data_len,
                                    uint8_t         mode0_step_count)
{
  sl_status_t ret, ret_log = SL_STATUS_OK;
  ret = set_channel_map(ch_data, ch_data_len);

  if (ret == SL_STATUS_OK) {
    cs_parser.mode_0_steps = mode0_step_count;
    ret_log = abr_file_log_append_header_section(ch_data,
                                                 ch_data_len,
                                                 cs_parser.mode_0_steps);
    if (ret_log != SL_STATUS_OK) {
      app_log_error("abr_file_log is not functional! No valid logs will be produced! (code: 0x%x)" APP_LOG_NL, ret_log);
    }
  } else {
    app_log_warning("Failed to set channel map!" APP_LOG_NL);
  }
  return ret;
}

sl_status_t abr_cs_parser_parse_event_result_data(sl_bt_evt_cs_result_t *cs_res,
                                                  abr_role_t             role)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER;
  if (cs_res != NULL) {
    if (cs_parser.initialized) {
      ret = parse_event_result_data(cs_res, role);
    } else {
      ret = SL_STATUS_NOT_INITIALIZED;
    }
  }
  return ret;
}

bool abr_cs_parser_procedure_restart_needed(uint8_t connection)
{
  cs_measurement_t *measurement = NULL;
  sl_status_t sc;
  bool restart_needed = false;

  sc = get_measurement_from_connection(&measurement, connection);
  if (sc == SL_STATUS_OK) {
    restart_needed = measurement->restart_needed;
  } else {
    app_log_warning("Invalid connection handle!" APP_LOG_NL);
  }
  return restart_needed;
}

sl_status_t abr_cs_parser_deinit(void)
{
  cs_parser.initialized = 0;
  sl_status_t ret = SL_STATUS_OK;
  return ret;
}

sl_status_t
abr_cs_parser_get_measurement_data(uint8_t connection,
                                   uint8_t mode,
                                   abr_cs_parser_meas_data_t *meas_data)
{
  sl_status_t ret = SL_STATUS_INVALID_PARAMETER;
  cs_measurement_t *meas = NULL;

  if (meas_data != NULL && connection != SL_BT_INVALID_CONNECTION_HANDLE) {
    ret = get_measurement_from_connection(&meas, connection);
    CHECK_STATUS_RETURN(ret, "Invalid connection handle!" APP_LOG_NL);

    ret = SL_STATUS_NOT_READY;
    if (meas->ready_to_process) {
      switch (mode) {
        case sl_bt_cs_mode_rtt: // Get RTT data
          memcpy(&meas_data->rtt_data,
                 (void *)&meas->rtt_data.rtl_input,
                 sizeof(sl_rtl_abr_rtt_data));
          ret = SL_STATUS_OK;
          break;
        case sl_bt_cs_mode_pbr: // Get RTP data
          memcpy(&meas_data->rtp_data,
                 (void *)&meas->rtp_data.rtl_input,
                 sizeof(sl_rtl_abr_rtp_data));
          ret = SL_STATUS_OK;
          break;
        case sl_bt_cs_mode_pbr_and_rtt:
          break;
        default:
          ret = SL_STATUS_INVALID_PARAMETER;
          break;
      }
      meas_data->initiator_calibration_rssi = (float)meas->initiator_calib.rssi;
      meas_data->reflector_calibration_rssi = (float)meas->reflector_calib.rssi;
    }
  }
  return ret;
}

sl_status_t abr_cs_parser_cleanup_measurement(uint8_t connection)
{
  sl_status_t ret = SL_STATUS_FAIL;
  cs_measurement_t *meas = NULL;
  ret = get_measurement_from_connection(&meas, connection);

  if (ret == SL_STATUS_OK) {
    clear_measurement_buffer(meas);
  }
  return ret;
}

void abr_cs_parser_store_distance(float *distance)
{
  sl_status_t ret_log = SL_STATUS_OK;
  app_log_debug("Store distance for logging" APP_LOG_NL);
  ret_log = abr_file_log_finalize_measurement_section(distance);
  if (ret_log != SL_STATUS_OK) {
    app_log_error("abr_file_log is not functional! No valid logs will be produced! (code: 0x%x)" APP_LOG_NL, ret_log);
  }
}

// -----------------------------------------------------------------------------
// Private functions

/***************************************************************************//**
 * Parse CS result event data.
 * @param[in] cs_res CS event result struct pointer.
 * @param[in] role ABR role.
 *
 * Parse and collect CS result event data according to ABR role.
 * @return Status code.
 ******************************************************************************/
static sl_status_t parse_event_result_data(sl_bt_evt_cs_result_t *cs_res,
                                           abr_role_t             role)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER, ret_log = SL_STATUS_OK;
  cs_measurement_t *measurement = NULL;

  if (cs_res == NULL) {
    return ret;
  }

  ret = get_measurement_from_connection(&measurement, cs_res->connection);
  CHECK_STATUS_RETURN(ret, "Invalid connection handle!" APP_LOG_NL);

  ret = check_cs_event_flags(cs_res, measurement);
  if (ret != SL_STATUS_OK) {
    return ret;
  }
  // Log the event header
  ret_log = abr_file_log_append_event_header(role, cs_res);
  if (ret_log != SL_STATUS_OK) {
    app_log_error("abr_file_log is not functional! No valid logs will be produced! (code: 0x%x)" APP_LOG_NL, ret_log);
  }

  ret = parse_steps(cs_res, role, measurement);
  if (ret == SL_STATUS_OK) {
    if (cs_res->subevent_done_status == 0) {
      update_measurement_flags(measurement, role);
    }
    check_measurement_completed(measurement);
    ret_log = abr_file_log_assign_steps_to_event(role, cs_res->num_steps);
    if (ret_log != SL_STATUS_OK) {
      app_log_error("abr_file_log is not functional! No valid logs will be produced! (code: 0x%x)" APP_LOG_NL, ret_log);
    }
  } else {
    app_log_info("Failed to parse steps, clearing measurement buffers." APP_LOG_NL);
    clear_measurement_buffer(measurement);
    set_restart_needed(measurement, true);
  }

  return ret;
}

/***************************************************************************//**
 * Parse steps in CS subevent.
 * @param[in] cs_res CS event result struct pointer.
 * @param[in] role ABR role.
 * @param[in,out] meas CS measurement data.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t parse_steps(sl_bt_evt_cs_result_t *cs_res,
                               abr_role_t             role,
                               cs_measurement_t      *meas)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER;
  uint32_t read_count = 0;

  if (cs_res == NULL || meas == NULL) {
    return ret;
  }

  for (uint8_t step = 0; step < cs_res->num_steps; step++) {
    memset(&meas->step_data, 0, sizeof(cs_step_t));
    ret = parse_one_step(cs_res->data.data,
                         cs_res->data.len,
                         role,
                         &read_count,
                         &meas->step_data);

    if (ret == SL_STATUS_OK) {
      switch (meas->step_data.type) {
        case MEASUREMENT_RTP:
          if (role == ABR_DEVICE_INITIATOR) {
            if (!meas->initiator_ready) {
              ret = add_rtp_data_to_measurement(&meas->rtp_data,
                                                &meas->step_data,
                                                role);
              if (cs_res->procedure_counter != 0) {
                meas->initiator_procedure_cnt = cs_res->procedure_counter;
              }
            }
          } else { // Reflector
            if (!meas->reflector_ready) {
              ret = add_rtp_data_to_measurement(&meas->rtp_data,
                                                &meas->step_data,
                                                role);
              if (cs_res->procedure_counter != 0) {
                meas->reflector_procedure_cnt = cs_res->procedure_counter;
              }
            }
          }
          break;

        case MEASUREMENT_RTT:
          if (role == ABR_DEVICE_INITIATOR) {
            if (!meas->initiator_ready) {
              ret = add_rtt_data_to_measurement(&meas->rtt_data,
                                                &meas->step_data,
                                                role);
              if (cs_res->procedure_counter != 0) {
                meas->initiator_procedure_cnt = cs_res->procedure_counter;
              }
            }
          } else { // Reflector
            if (!meas->reflector_ready) {
              ret = add_rtt_data_to_measurement(&meas->rtt_data,
                                                &meas->step_data,
                                                role);
              if (cs_res->procedure_counter != 0) {
                meas->reflector_procedure_cnt = cs_res->procedure_counter;
              }
            }
          }
          break;

        case CALIBRATION_INITIATOR:
          ret = add_calibration_data_to_measurement(meas,
                                                    &meas->step_data,
                                                    role);
          break;

        case CALIBRATION_REFLECTOR:
          ret = add_calibration_data_to_measurement(meas,
                                                    &meas->step_data,
                                                    role);
          break;

        default:
          break;
      }
    } else {
      break; // Finish parsing, return with error code
    }
  } // end for(...)
  return ret;
}

/***************************************************************************//**
 * Parse one CS step.
 * @param[in] data Step data field pointer.
 * @param[in] data_size Step data field size.
 * @param[in] role ABR role.
 * @param[in,out] read_cnt Data field byte read count.
 * @param[out] out Parsed step data.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t parse_one_step(uint8_t   *data,
                                  uint32_t   data_size,
                                  abr_role_t role,
                                  uint32_t  *read_cnt,
                                  cs_step_t *out)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER, ret_log = SL_STATUS_OK;
  if (data == NULL || read_cnt == NULL || out == NULL) {
    return ret;
  }
  // Step mode
  ret = read_byte(data, data_size, read_cnt, &out->step_mode);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
  // Step channel
  ret = read_byte(data, data_size, read_cnt, &out->step_channel);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
  // Step data length
  ret = read_byte(data, data_size, read_cnt, &out->step_data_length);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);

  // Step data
  switch (out->step_mode) {
    case CS_MODE_CALIBRATION:
      if (role == ABR_DEVICE_INITIATOR) {
        ret = parse_calibration_initiator(data, data_size, read_cnt, out);
      } else {
        ret = parse_calibration_reflector(data, data_size, read_cnt, out);
      }
      break;

    case sl_bt_cs_mode_rtt: // RTT
      ret = parse_rtt_step(data, data_size, read_cnt, out);
      break;
    case sl_bt_cs_mode_pbr: // RTP
      ret = parse_rtp_step(data, data_size, read_cnt, out);
      break;
    case sl_bt_cs_mode_pbr_and_rtt: // Combined
      break;

    default:
      break;
  } // end switch

  ret_log = abr_file_log_store_step(role, out);
  if (ret_log != SL_STATUS_OK) {
    app_log_error("abr_file_log is not functional! No valid logs will be produced! (code: 0x%x)" APP_LOG_NL, ret_log);
  }
  return ret;
}

/***************************************************************************//**
 * Read byte from step data field and increment read count.
 * @param[in] data Step data field pointer.
 * @param[in] data_size Step data field size.
 * @param[in,out] read_cnt Data field byte read count.
 * @param[out] out Byte read.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t read_byte(const uint8_t *data,
                             uint32_t       data_size,
                             uint32_t      *read_cnt,
                             uint8_t       *out)
{
  sl_status_t ret = SL_STATUS_FAIL;
  if (*read_cnt < data_size) {
    *out = data[*read_cnt];
    (*read_cnt)++;
    ret = SL_STATUS_OK;
  } else {
    app_log_warning("CS step data reading failed!" APP_LOG_NL);
  }
  return ret;
}

/***************************************************************************//**
 * Check CS event flags.
 * @param[in] cs_res CS event result struct pointer.
 * @param[in,out] meas CS measurement data.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t check_cs_event_flags(sl_bt_evt_cs_result_t *cs_res,
                                        cs_measurement_t *meas)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER;
  if (cs_res == NULL || meas == NULL) {
    return ret;
  }

  // Empty event occured
  if (cs_res->num_steps == 0) {
    app_log_info("Empty CS result event occured!" APP_LOG_NL);
    clear_measurement_buffer(meas);
    set_restart_needed(meas, true);
    ret = SL_STATUS_FAIL;
  } // Procedure aborted
  else if ((cs_res->procedure_done_status & CS_PROCEDURE_ABORTED)
           == CS_PROCEDURE_ABORTED) {
    app_log_info("Procedure aborted" APP_LOG_NL);
    clear_measurement_buffer(meas);
    set_restart_needed(meas, true);
    ret = SL_STATUS_OK;
  } // Subevent aborted, no restart needed just clear the buffer
  else if ((cs_res->subevent_done_status & CS_SUBEVENT_ABORTED)
           == CS_SUBEVENT_ABORTED) {
    app_log_info("Subevent aborted" APP_LOG_NL);
    clear_measurement_buffer(meas);
    ret = SL_STATUS_OK;
  } else {
    ret = SL_STATUS_OK;
  }
  return ret;
}

/***************************************************************************//**
 * Update CS measurement flags.
 * @param[in,out] meas CS measurement data.
 * @param[in] role ABR role.
 ******************************************************************************/
static void update_measurement_flags(cs_measurement_t *meas,
                                     abr_role_t role)
{
  if (meas != NULL) {
    if (role == ABR_DEVICE_INITIATOR) {
      if ((meas->initiator_procedure_cnt > 0)
          && (meas->initiator_procedure_cnt
              >= meas->reflector_procedure_cnt)) {
        meas->initiator_ready = true;
      }
    } else { // Reflector
      if ((meas->reflector_procedure_cnt > 0)
          && (meas->reflector_procedure_cnt
              >= meas->initiator_procedure_cnt)) {
        meas->reflector_ready = true;
      }
    }

    // Check ready state according to procedure counters
    if (meas->initiator_ready
        && (meas->initiator_procedure_cnt
            < meas->reflector_procedure_cnt)) {
      meas->initiator_ready = false;
      meas->rtt_data.initiator_idx = 0;
    }
    if (meas->reflector_ready
        && (meas->reflector_procedure_cnt
            < meas->initiator_procedure_cnt)) {
      meas->reflector_ready = false;
      meas->rtt_data.reflector_idx = 0;
    }
  }
}

/***************************************************************************//**
 * Check if parsing of the CS samples is completed and update output.
 * @param[in,out] meas CS measurement data.
 ******************************************************************************/
static void check_measurement_completed(cs_measurement_t *meas)
{
  if (meas != NULL) {
    if (meas->initiator_ready && meas->reflector_ready) {
      if (meas->reflector_procedure_cnt == meas->initiator_procedure_cnt) {
        // RTT measurement
        meas->rtt_data.rtl_input.num_time_stamps = MIN(meas->rtt_data.reflector_idx, \
                                                       meas->rtt_data.initiator_idx);
        meas->rtt_data.rtl_input.rssi_d1 = meas->rtt_data.rssi_initiator;
        meas->rtt_data.rtl_input.rssi_d2 = meas->rtt_data.rssi_reflector;
        meas->rtt_data.rtl_input.time_d1 = meas->rtt_data.time_initiator;
        meas->rtt_data.rtl_input.time_d2 = meas->rtt_data.time_reflector;
        // RTP measurement
        meas->rtp_data.rtl_input.num_tones = cs_parser.num_tones;
        meas->rtp_data.rtl_input.tones_frequency_delta_hz = DEFAULT_FREQUENCY_DELTA;
        meas->rtp_data.rtl_input.blank_tone_indices = cs_parser.blank_tone_channels;
        meas->rtp_data.rtl_input.num_blank_tone_indices
          = cs_parser.num_blank_tone_indices;
        meas->rtp_data.rtl_input.tone_qualities_d1 = NULL;
        meas->rtp_data.rtl_input.tone_qualities_d2 = NULL;
        meas->rtp_data.rtl_input.i_samples_d1 = meas->rtp_data.initiator_i_samples;
        meas->rtp_data.rtl_input.q_samples_d1 = meas->rtp_data.initiator_q_samples;
        meas->rtp_data.rtl_input.i_samples_d2 = meas->rtp_data.reflector_i_samples;
        meas->rtp_data.rtl_input.q_samples_d2 = meas->rtp_data.reflector_q_samples;
        meas->ready_to_process = true;
        app_log_debug("Measurement ready to process" APP_LOG_NL);
      } else {
        clear_measurement_buffer(meas);
      }
    }
  }
}

/***************************************************************************//**
 * Parse CS RTT step data.
 * @param[in] data Step data field pointer.
 * @param[in] data_size Step data field size.
 * @param[in,out] read_cnt Data field byte read count.
 * @param[out] step_data Parsed step data.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t parse_rtt_step(const uint8_t *data,
                                  uint32_t       data_size,
                                  uint32_t      *read_cnt,
                                  cs_step_t     *step_data)
{
  sl_status_t ret = SL_STATUS_FAIL;
  uint8_t data_octet;

  if (step_data->step_data_length >= RTT_VALUE_LEN) {
    ret = read_byte(data,
                    data_size,
                    read_cnt,
                    &step_data->data.meas_rtt.packet_quality);
    CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);

    ret = read_byte(data,
                    data_size,
                    read_cnt,
                    &step_data->data.meas_rtt.nadm);
    CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);

    ret = read_byte(data,
                    data_size,
                    read_cnt,
                    &data_octet);
    CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
    step_data->data.meas_rtt.rssi = (int8_t)data_octet;

    ret = read_byte(data, data_size, read_cnt, &data_octet);
    CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
    step_data->data.meas_rtt.tod_toa = data_octet;

    ret = read_byte(data, data_size, read_cnt, &data_octet);
    CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
    step_data->data.meas_rtt.tod_toa |= (uint16_t)data_octet << 8;

    ret = read_byte(data,
                    data_size,
                    read_cnt,
                    &step_data->data.meas_rtt.antenna);
    CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
    step_data->type = MEASUREMENT_RTT;
  }
  return ret;
}

/***************************************************************************//**
 * Convert raw RTP tone PCT value to integer
 * @param[in] tone_pct Raw tone PCT value.
 *
 * @return Converted tone PCT integer value.
 ******************************************************************************/
static int16_t tone_pct_to_int(uint32_t tone_pct)
{
  // Tone PCT value is aligned into the lower 12 bit of tone_pct
  int16_t tone_pct_int16 = (tone_pct & 0xfff) << 4;
  return tone_pct_int16 >> 4;
}

/***************************************************************************//**
 * Parse CS RTP step data.
 * @param[in] data Step data field pointer.
 * @param[in] data_size Step data field size.
 * @param[in,out] read_cnt Data field byte read count.
 * @param[out] step_data Parsed step data.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t parse_rtp_step(const uint8_t *data,
                                  uint32_t       data_size,
                                  uint32_t      *read_cnt,
                                  cs_step_t     *step_data)
{
  sl_status_t ret = SL_STATUS_OK;
  sl_status_t sc = SL_STATUS_FAIL;
  uint8_t pct_octet[3];

  sc = read_byte(data,
                 data_size,
                 read_cnt,
                 &step_data->data.meas_rtp.antenna_permutation_index);
  CHECK_STATUS_RETURN(sc, "Failed to read CS data!" APP_LOG_NL);
  app_log_debug("antenna_permutation_index %hhu"APP_LOG_NL,
                step_data->data.meas_rtp.antenna_permutation_index);

  // Calculate tone pct count based on step data size
  const uint32_t tone_pct_count =
    (step_data->step_data_length
     - sizeof(step_data->data.meas_rtp.antenna_permutation_index))
    / (sizeof(pct_octet) + sizeof(step_data->data.meas_rtp.tone_quality[0]));

  for (uint8_t i = 0; i < ANTENNA_PERMUTATION_MAX; i++) {
    // Check exit condition
    if (i >= tone_pct_count) {
      break;
    }

    // Parsing 3 byte PCT field
    for (uint8_t pct_octet_num = 0; pct_octet_num < PCT_BYTE_COUNT; pct_octet_num++) {
      sc = read_byte(data,
                     data_size,
                     read_cnt,
                     &pct_octet[pct_octet_num]);
      CHECK_STATUS_RETURN(sc, "Failed to read CS data!" APP_LOG_NL);
    }
    uint32_t tone_pct = (uint32_t)pct_octet[0]
                        + ((uint32_t)pct_octet[1] << 8)
                        + ((uint32_t)pct_octet[2] << 16);

    // Check if tone_pct is invalid from the non extension slot
    if ((tone_pct == TONE_PCT_INVALID) && (i == 0)) {
      app_log_warning("incorrect pct %04x" APP_LOG_NL, tone_pct);
      ret = SL_STATUS_FAIL;
    } else {
      app_log_debug("pct %04x"APP_LOG_NL, tone_pct);
    }

    step_data->data.meas_rtp.pct_i[i] =
      (float)tone_pct_to_int((tone_pct) & PCT_DATA_MASK_LOW);
    step_data->data.meas_rtp.pct_q[i] =
      (float)tone_pct_to_int(((tone_pct) & PCT_DATA_MASK_HIGH) >> PCT_IQ_LEN);

    app_log_debug("pcti %f, pctq %f"APP_LOG_NL, step_data->data.meas_rtp.pct_i[i],
                  step_data->data.meas_rtp.pct_q[i]);

    // Parsing tone quality
    sc = read_byte(data,
                   data_size,
                   read_cnt,
                   &step_data->data.meas_rtp.tone_quality[i]);
    CHECK_STATUS_RETURN(sc, "Failed to read CS data!" APP_LOG_NL);
  } // end for(... ANTENNA_PERMUTATION_MAX)
  step_data->data.meas_rtp.pct_sample_num = tone_pct_count;
  step_data->type = MEASUREMENT_RTP;
  return ret;
}

/***************************************************************************//**
 * Parse reflector calibration step.
 * @param[in] data Step data field pointer.
 * @param[in] data_size Step data field size.
 * @param[in,out] read_cnt Data field byte read count.
 * @param[out] out Parsed step data.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t parse_calibration_reflector(const uint8_t* data,
                                               uint32_t       data_size,
                                               uint32_t      *read_cnt,
                                               cs_step_t     *out)
{
  sl_status_t ret = SL_STATUS_OK;
  uint8_t data_octet;
  ret = read_byte(data, data_size, read_cnt, &out->data.reflector_calib.packet_quality);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);

  ret = read_byte(data, data_size, read_cnt, &data_octet);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
  out->data.reflector_calib.rssi = (int8_t)data_octet;

  ret = read_byte(data, data_size, read_cnt, &out->data.reflector_calib.packet_antenna);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
  out->type = CALIBRATION_REFLECTOR;
  return ret;
}

/***************************************************************************//**
 * Parse initiator calibration step.
 * @param[in] data Step data field pointer.
 * @param[in] data_size Step data field size.
 * @param[in,out] read_cnt Data field byte read count.
 * @param[out] out Parsed step data.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t parse_calibration_initiator(const uint8_t* data,
                                               uint32_t       data_size,
                                               uint32_t      *read_cnt,
                                               cs_step_t     *out)
{
  sl_status_t ret = SL_STATUS_OK;
  uint8_t data_octet;
  ret = read_byte(data, data_size, read_cnt, &out->data.initiator_calib.packet_quality);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);

  ret = read_byte(data, data_size, read_cnt, &data_octet);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
  out->data.initiator_calib.rssi = (int8_t)data_octet;

  ret = read_byte(data, data_size, read_cnt, &out->data.initiator_calib.packet_antenna);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);

  uint8_t freq_offset_lsb;
  uint8_t freq_offset_msb;
  ret = read_byte(data, data_size, read_cnt, &freq_offset_lsb);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);

  ret = read_byte(data, data_size, read_cnt, &freq_offset_msb);
  CHECK_STATUS_RETURN(ret, "Failed to read CS data!" APP_LOG_NL);
  int16_t freq_offset = (uint16_t)freq_offset_lsb + (((uint16_t)freq_offset_msb) << 8);
  out->data.initiator_calib.freq_offset = freq_offset;
  out->type = CALIBRATION_INITIATOR;
  return ret;
}

/***************************************************************************//**
 * Add parsed RTT data to measurement data.
 * @param[out] meas CS measurement data.
 * @param[in] step_data Parsed step data.
 * @param[in] role ABR role.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t add_rtt_data_to_measurement(rtt_measurement_t *meas,
                                               cs_step_t         *step_data,
                                               abr_role_t         role)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER;

  if (meas != NULL && step_data != NULL) {
    int32_t rssi = (int32_t)step_data->data.meas_rtt.rssi;
    int32_t time = step_data->data.meas_rtt.tod_toa != LL_INVALID_TOA
                   ? step_data->data.meas_rtt.tod_toa
                   : (int32_t)INVALID_TIME_VALUE;

    if (role == ABR_DEVICE_INITIATOR) {
      if (meas->initiator_idx >= MAX_NUM_CHANNELS) {
        meas->initiator_idx = 0;
      }
      meas->rssi_initiator[meas->initiator_idx] = rssi;
      meas->time_initiator[meas->initiator_idx] = time;
      meas->initiator_idx++;
    } else { // Reflector
      if (meas->reflector_idx >= MAX_NUM_CHANNELS) {
        meas->reflector_idx = 0;
      }
      meas->rssi_reflector[meas->reflector_idx] = rssi;
      meas->time_reflector[meas->reflector_idx] = time;
      meas->reflector_idx++;
    }
    ret = SL_STATUS_OK;
  }
  return ret;
}

/***************************************************************************//**
 * Add parsed RTP data to measurement data.
 * @param[out] meas CS measurement data.
 * @param[in] step_data Parsed step data.
 * @param[in] role ABR role.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t add_rtp_data_to_measurement(rtp_measurement_t *meas,
                                               cs_step_t         *step_data,
                                               abr_role_t         role)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER;
  uint8_t channel_idx = 0;

  if (meas != NULL && step_data != NULL) {
    channel_idx = step_data->step_channel / 2; // Calculate channel index from step_channel
    if (channel_idx > MAX_NUM_CHANNELS) {
      app_log_warning("Incorrect PCT channel!" APP_LOG_NL);
      ret = SL_STATUS_FAIL;
    } else {
      if (role == ABR_DEVICE_INITIATOR) {
        meas->initiator_i_samples[channel_idx] = step_data->data.meas_rtp.pct_i[0];
        meas->initiator_q_samples[channel_idx] = step_data->data.meas_rtp.pct_q[0];
      } else { // Reflector
        meas->reflector_i_samples[channel_idx] = step_data->data.meas_rtp.pct_i[0];
        meas->reflector_q_samples[channel_idx] = step_data->data.meas_rtp.pct_q[0];
      }
      ret = SL_STATUS_OK;
    }
  }
  return ret;
}

/***************************************************************************//**
 * Add parsed calibration data to measurement data.
 * @param[out] meas CS measurement data.
 * @param[in] step_data Parsed step data.
 * @param[in] role ABR role.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t add_calibration_data_to_measurement(cs_measurement_t  *meas,
                                                       cs_step_t         *step_data,
                                                       abr_role_t         role)
{
  sl_status_t ret = SL_STATUS_NULL_POINTER;

  if (meas != NULL && step_data != NULL) {
    if (role == ABR_DEVICE_INITIATOR) {
      meas->initiator_calib = step_data->data.initiator_calib;
    } else { // Reflector
      meas->reflector_calib = step_data->data.reflector_calib;
    }
    ret = SL_STATUS_OK;
  }
  return ret;
}

/***************************************************************************//**
 * Get measurement index according to connection handle.
 *
 * @param[in] connection Connection handle from BLE stack.
 * @param[out] index Pointer to calculated index.
 *
 * Note:
 * Currently one reflector connection is supported and this function
 * always returns with index 0.
 * @return Status code.
 ******************************************************************************/
static sl_status_t get_measurement_index_from_connection(uint8_t connection,
                                                         uint8_t *index)
{
  // Only one reflector connection is supported with measurement index 0
  (void)connection;
  *index = 0;
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Get measurement pointer based on connection handle.
 * @param[out] meas CS measurement data stucture pointer.
 * @param[in] conn Connection handle from BLE stack.
 *
 * @return Status code.
 ******************************************************************************/
static sl_status_t get_measurement_from_connection(cs_measurement_t **meas,
                                                   uint8_t            conn)
{
  sl_status_t ret = SL_STATUS_NOT_FOUND;
  uint8_t meas_idx = 0;

  if (meas != NULL) {
    ret = get_measurement_index_from_connection(conn, &meas_idx);

    if (ret == SL_STATUS_OK) {
      *meas = &cs_parser.measurements[meas_idx];
      (*meas)->connection = conn;
    }
  }
  return ret;
}

/***************************************************************************//**
 * Clear CS measurement buffers.
 ******************************************************************************/
static void clear_measurement_buffers(void)
{
  for (uint8_t i = 0; i < NUM_OF_REFLECTORS; i++) {
    clear_measurement_buffer(&cs_parser.measurements[i]);
  }
}

/***************************************************************************//**
 * Clear measurement buffer and restore initial state.
 * @param[in] meas CS measurement data.
 ******************************************************************************/
static void clear_measurement_buffer(cs_measurement_t *meas)
{
  if (meas != NULL) {
    uint8_t conn = meas->connection; // Preserve connection handle
    memset(meas, 0, sizeof(cs_measurement_t));
    // Set RTT invalid data as empty values for RTL lib.
    for (uint8_t c = 0; c < MAX_NUM_CHANNELS; c++) {
      meas->rtt_data.time_initiator[c] = INVALID_TIME_VALUE;
      meas->rtt_data.time_reflector[c] = INVALID_TIME_VALUE;
      meas->rtt_data.rssi_initiator[c] = INVALID_RSSI_VALUE;
      meas->rtt_data.rssi_reflector[c] = INVALID_RSSI_VALUE;
    }
    meas->connection = conn;
  }
}

/***************************************************************************//**
 * Set restart needed for a particular measurement.
 * @param[in] meas CS measurement data.
 * @param[in] needed Restart needed boolean.
 ******************************************************************************/
static void set_restart_needed(cs_measurement_t *meas, bool needed)
{
  if (meas != NULL) {
    meas->restart_needed = needed;
  }
}

/******************************************************************************
 * Set the channel_map
 *
 * @param channel_map is the channel_map data
 * @param channel_map_len is the channel_map data length
 *****************************************************************************/
static sl_status_t set_channel_map(const uint8_t *channel_map,
                                   const uint32_t channel_map_len)
{
  uint8_t current_channel_map;

  uint32_t num_channels = 0;
  uint32_t blank_tone_channels_index = 0;
  uint32_t num_hadm_channels = 0;
  sl_status_t ret = SL_STATUS_NULL_POINTER;

  if (channel_map != NULL) {
    cs_parser.num_blank_tone_indices = 0;

    for (uint32_t channel_map_index = 0;
         channel_map_index < channel_map_len;
         channel_map_index++) {
      current_channel_map = channel_map[channel_map_index];
      for (uint8_t current_bit_index = 0;
           current_bit_index < sizeof(uint8_t) * BYTE_LEN;
           current_bit_index++) {
        if (current_channel_map & (1 << current_bit_index)) {
          num_hadm_channels++;
        } else {
          cs_parser.blank_tone_channels[blank_tone_channels_index]
            = num_channels;
          blank_tone_channels_index++;
        }
        num_channels++;
      }
    }

    cs_parser.num_tones = num_hadm_channels;
    app_log_info("RTL process %u channels" APP_LOG_NL, cs_parser.num_tones);
    ret = SL_STATUS_OK;
  }
  return ret;
}

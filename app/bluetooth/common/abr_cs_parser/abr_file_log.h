/***************************************************************************//**
 * @file
 * @brief ABR file log public API
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

#ifndef ABR_FILE_LOG_H
#define ABR_FILE_LOG_H

#if defined(HOST_TOOLCHAIN) && (ABR_FILE_LOG_ENABLED == 1)

#include <stdint.h>
#include "sl_bt_api.h"
#include "abr_cs_parser_types.h"

/**************************************************************************//**
 * ABR file logger initialization
 * This function sets the target filename
 *
 * @param[in] abr_mode measurement mode
 *
 * @return status code
 *****************************************************************************/
sl_status_t abr_file_log_init(uint8_t abr_mode);

/**************************************************************************//**
 * ABR file logger deinitialization
 * Closing file if its still open.
 *
 * @return status code
 *****************************************************************************/
sl_status_t abr_file_log_deinit(void);

/**************************************************************************//**
 * ABR file logger get application version
 * Gets application version info for loggin.
 * @param[in] major application major version
 * @param[in] minor application minor version
 * @param[in] patch application patch version
 * @param[in] build application build version
 *****************************************************************************/
void abr_file_log_app_version(uint16_t major, uint16_t minor,
                              uint16_t patch, uint16_t build);

/**************************************************************************//**
 * ABR file log append header section
 * Gathers all the information the file header must contain
 * such as:
 * - timestamp: the start time of the initiator feature
 * - sdk_version: base GSDK version in format "major.minor.patch.build"
 * - channel_map: channel map string
 * - mode0_steps: number of mode0 steps (calibration) in every event
 * The jsonl object is also appended to the target file if possible and it will
 * be closed until the first distance measurement finished.
 *
 * @param[in] ch_data - channel data for channel map
 * @param[in] ch_data_len - channel data length for channel map
 * @param[in] mode0_steps_count - number of calibration steps for header
 *
 * @return status code
 *****************************************************************************/
sl_status_t abr_file_log_append_header_section(const uint8_t *ch_data,
                                               const uint32_t ch_data_len,
                                               const uint8_t mode0_steps_count);

/**************************************************************************//**
 * Append new event header to the jsonl object
 * Checks the actual event role (device) and fill up the header for it with the
 * known information:
 * - start_acl_conn_event: the event identifier
 * - timestamp
 * The jsonl object will be extended with the additional information later on.
 *
 * @param[in] role device role
 * @param[in] cs_res channel sounding parser results of event data
 *
 * @return status code
 *****************************************************************************/
sl_status_t abr_file_log_append_event_header(abr_role_t role,
                                             sl_bt_evt_cs_result_t *cs_res);

/**************************************************************************//**
 * Assign steps to event
 * Once every steps is processed in 1 event, assign their array to that event
 * and finalize.
 *
 * @param[in] role device role
 * @param[in] num_steps number of steps in the processed event
 *
 * @return status code
 *****************************************************************************/
sl_status_t abr_file_log_assign_steps_to_event(abr_role_t role,
                                               uint16_t num_steps);

/**************************************************************************//**
 * Store step data
 * Parsed and saved step data according to the actual mode and role.
 * There is also an option to keep the old jsonl format of the steps or extend
 * them with additional properties.
 * The function also increments the step counters for the event data later on.
 *
 * @param[in] role device role
 * @param[in] step_data actual step data from channel sounding parser module
 *
 * @return status code
 *****************************************************************************/
sl_status_t abr_file_log_store_step(abr_role_t role, cs_step_t *step_data);
/**************************************************************************//**
 * ABR file log finalize measurement section
 * Gets all the initiator and reflector data and stores them together with the
 * estimated distance to the target log file.
 * This is the only step where the file operation called outside the file
 * header append function 'abr_file_log_append_header_section'.
 *
 * @param[in] estimated_distance estimated distance taken from the cs parser
 *                               module
 *
 * @return status code
 *****************************************************************************/
sl_status_t abr_file_log_finalize_measurement_section(float *estimated_distance);

#else // defined(HOST_TOOLCHAIN) && (ABR_FILE_LOG_ENABLED == 1)

#define abr_file_log_init(...) SL_STATUS_OK
#define abr_file_log_deinit(...) SL_STATUS_OK
#define abr_file_log_app_version(...) SL_STATUS_OK
#define abr_file_log_get_measurement_mode(...) SL_STATUS_OK
#define abr_file_log_append_header_section(...) SL_STATUS_OK
#define abr_file_log_append_event_header(...) SL_STATUS_OK
#define abr_file_log_assign_steps_to_event(...) SL_STATUS_OK
#define abr_file_log_store_step(...) SL_STATUS_OK
#define abr_file_log_finalize_measurement_section(...) SL_STATUS_OK

#endif // defined(HOST_TOOLCHAIN) && (ABR_FILE_LOG_ENABLED == 1)
#endif // ABR_FILE_LOG_H

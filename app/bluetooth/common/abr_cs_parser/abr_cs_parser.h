/***************************************************************************//**
 * @file
 * @brief ABR CS Parser header.
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

#ifndef ABR_CS_PARSER_H
#define ABR_CS_PARSER_H

#include <stdbool.h>
#include <stdint.h>
#include "sl_bt_api.h"
#include "sl_rtl_clib_api.h"
#include "abr_cs_parser_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Definitions
#define LL_INVALID_TOA        0x800             // Invalid time value from LL
#define ABR_CS_PARSER_INVALID_TIME_VALUE    0x80000000        // Invalid RTL library time value
#define ABR_CS_PARSER_INVALID_RSSI_VALUE    0x80000000        // Invalid RTL library RSSI value
#define ABR_CS_PARSER_TONE_QUALITY_MASK_LOW 0x0F              // Tone quality indicator low bitmask
// -------------------------------
// Enums, structs, typedefs

/// CS measurement data for RTL library
typedef struct {
  sl_rtl_abr_rtt_data rtt_data;                   ///< RTT measurement data
  sl_rtl_abr_rtp_data pbr_data;                   ///< PBR measurement data
  float               initiator_calibration_rssi; ///< Initiator RSSI from calibration
  float               reflector_calibration_rssi; ///< Reflector RSSI from calibration
} abr_cs_parser_meas_data_t;

/// CS parser configuration structure
typedef struct {
  uint8_t measurement_mode;             ///< ABR measurement mode
  float   rssi_tx_power;                ///< Configured RSSI transmit power
  bool    rssi_measurement_enabled;     ///< RSSI based distance calculation is enabled
} abr_cs_parser_configuration_t;
/// CS measurement data pointer
typedef void * abr_cs_parser_meas_data_handle_t;

// -------------------------------
// Callback types

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * Initialize CS parser.
 * @param[in] config Configuration structure pointer.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t abr_cs_parser_init(abr_cs_parser_configuration_t *config);

/**************************************************************************//**
 * Configure CS parser.
 * @param[in] ch_data Channel map data.
 * @param[in] ch_data_len Channel map data length.
 * @param[in] mode0_step_count Mode 0 steps to be included at the beginning
 *                             of the test ABR subevent. (Ignored if not
 *                             in mode 0)
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t abr_cs_parser_configure(const uint8_t  *ch_data,
                                    uint32_t        ch_data_len,
                                    uint8_t         mode0_step_count);

/**************************************************************************//**
 * Parse CS event data.
 * @param[in] cs_res CS event result struct pointer.
 * @param[in] role ABR role.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t abr_cs_parser_parse_event_result_data(sl_bt_evt_cs_result_t *cs_res,
                                                  abr_role_t             role);

/**************************************************************************//**
 * CS procedure should be restarted.
 * @param[in] connection Connection handle from BLE stack.
 *
 * @return true CS procedure should be restarted.
 * @return false CS procedure should not be restarted.
 *****************************************************************************/
bool abr_cs_parser_procedure_restart_needed(uint8_t connection);

/**************************************************************************//**
 * Get CS measurement data pointer.
 * @param[in] connection Connection handle from BLE stack.
 * @param[in] mode ABR mode.
 * @param[out] meas_data CS measurement data pointer.
 *
 * @return SL_STATUS_OK: Distance can be calculated with RTL library.
 * @return SL_STATUS_NOT_READY: CS data parsing is not yet ready.
 * @return SL_STATUS_INVALID_PARAMETER: SL_STATUS_OK: Invalid function parameter.
 *****************************************************************************/
sl_status_t
abr_cs_parser_get_measurement_data(uint8_t connection,
                                   uint8_t mode,
                                   abr_cs_parser_meas_data_t *meas_data);

/**************************************************************************//**
 * Clean up CS measurement buffers after RTL distance calculation.
 * @param[in] connection Connection handle from BLE stack.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t abr_cs_parser_cleanup_measurement(uint8_t connection);

/**************************************************************************//**
 * Store distance for logging.
 * @param[in] distance calculated distance in mm
 * @param[in] likeliness calculated distance likeliness
 * @param[in] rssi_distance distance calculated with RSSI values
 *
 *****************************************************************************/
void abr_cs_parser_store_distance(float *distance, float *likeliness, float *rssi_distance);

/**************************************************************************//**
 * Get the current CS bit error rate.
 *
 * @return the current bit error rate
 *****************************************************************************/
uint8_t abr_cs_parser_get_cs_bit_error_rate();

/**************************************************************************//**
 * Deinitialize CS parser.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t abr_cs_parser_deinit(void);

#ifdef __cplusplus
};
#endif

#endif // ABR_CS_PARSER_H

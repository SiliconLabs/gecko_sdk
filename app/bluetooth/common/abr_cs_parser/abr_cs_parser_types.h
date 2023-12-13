/***************************************************************************//**
 * @file
 * @brief ABR CS Parser types.
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

#ifndef ABR_CS_PARSER_TYPES_H
#define ABR_CS_PARSER_TYPES_H

#include <stdint.h>
// -----------------------------------------------------------------------------
// Definitions

// -------------------------------
// Enums, structs, typedefs

/// Maximum value of Num_Antenna_Paths parameter.
/// See Bluetooth Core specification, HCI chapter.
#define NUM_ANTENNA_PATHS_MAX   4
/// Maximum number of antenna permutation array elements
#define ANTENNA_PERMUTATION_MAX (NUM_ANTENNA_PATHS_MAX + 1)

/// ABR role
typedef enum {
  ABR_DEVICE_REFLECTOR       = 0,       ///< Reflector
  ABR_DEVICE_INITIATOR       = 1        ///< Initiator
} abr_role_t;

///ABR mode
typedef enum {
  ABR_MODE_CALIBRATION   = 0,                   // Calibration CS mode
  ABR_MODE_RTT           = sl_bt_cs_mode_rtt,   // RTT CS mode
  ABR_MODE_PBR           = sl_bt_cs_mode_pbr    // PBR CS mode
} abr_mode_t;

/// Initiator claibration step
typedef struct {
  uint8_t packet_quality;           ///< Packet quality
  int8_t  rssi;                     ///< Packet RSSI value
  uint8_t packet_antenna;           ///< Antenna identifier used for the RTT packet
  int16_t freq_offset;              ///< Measured frequency offset
} initiator_calibration_t;

/// Reflector claibration step
typedef struct {
  uint8_t packet_quality;           ///< Packet quality
  int8_t  rssi;                     ///< Packet RSSI value
  uint8_t packet_antenna;           ///< Antenna identifier used for the RTT packet
} reflector_calibration_t;

/// CS RTT step result
typedef struct {
  uint8_t  packet_quality;          ///< Packet quality raw value
  uint8_t  nadm;                    ///< Packet NADM
  int8_t   rssi;                    ///< Packet RSSI
  int16_t tod_toa;                  ///< Time difference between arrival and departure time of the CS packets
  uint8_t  antenna;                 ///< Antenna identifier used for the RTT packet
} rtt_result_t;

/// CS PBR step result
typedef struct {
  uint8_t  antenna_permutation_index;             ///< Antenna Permutation Index for the chosen
                                                  ///  Num_Antenna_Paths parameter used during the phase measurement stage
  float    pct_q[ANTENNA_PERMUTATION_MAX];        ///< Phase Correction Term Q sample
  float    pct_i[ANTENNA_PERMUTATION_MAX];        ///< Phase Correction Term I sample
  uint8_t  tone_quality[ANTENNA_PERMUTATION_MAX]; ///< PCT quality indicator raw value
  uint8_t  pct_sample_num;                        ///< Number of PCT samples
  uint32_t channel;                               ///< Channel
} pbr_result_t;

/// CS Step data type
typedef enum {
  CALIBRATION_INITIATOR       = 0,  ///< Initiator calibration data
  CALIBRATION_REFLECTOR       = 1,  ///< Reflector calibration data
  MEASUREMENT_RTT             = 2,  ///< RTT measurement data
  MEASUREMENT_PBR             = 3,  ///< PBR measurement data
} cs_step_data_type_t;

/// CS step structure
typedef struct {
  uint8_t step_mode;              ///< Step mode type
  uint8_t step_channel;           ///< CS channel index
  uint8_t step_data_length;       ///< Length of mode- and role-specific information being reported
  cs_step_data_type_t type;       ///< Step data type
  union {
    reflector_calibration_t reflector_calib;  ///< Reflector calibration step
    initiator_calibration_t initiator_calib;  ///< Initiator claibration step
    rtt_result_t            meas_rtt;         ///< RTT step
    pbr_result_t            meas_pbr;         ///< PBR step
  } data;                                     ///< Step data
} cs_step_t;

#endif // ABR_CS_PARSER_TYPES_H

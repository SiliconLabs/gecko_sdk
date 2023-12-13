/***************************************************************************//**
 * @file
 * @brief ABR initiator configuration
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

#ifndef ABR_INITIATOR_CONFIG_H
#define ABR_INITIATOR_CONFIG_H

#include <stdbool.h>
#include "sl_bt_api.h"
#include "sl_rtl_clib_api.h"
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *********************************  MACROS  ************************************
 ******************************************************************************/

#define UUID_LEN              16
#define INITIATOR_LOCAL_NAME 0x09
#define INITIATOR_SERVICE_UUID { 0xf2, 0x20, 0x18, 0xc7, 0x32, 0x2d, 0xc7, 0xab, 0xcf, \
                                 0x46, 0xf7, 0xff, 0x70, 0x9e, 0xb9, 0xbb };
#define INITIATOR_CHARACTERISTIC_UUID { 0x91, 0xbe, 0x18, 0xa4, 0x22, 0x3c, 0x49, 0x9b, \
                                        0x03, 0x43, 0x91, 0x13, 0xec, 0x95, 0x9f, 0x92 };
// RAS Service
// bbb99e70-fff7-46cf-abc7-2d32c71820f3
#define RAS_SERVICE_UUID { 0xf3, 0x20, 0x18, 0xc7, 0x32, 0x2d, 0xc7, 0xab, 0xcf, \
                           0x46, 0xf7, 0xff, 0x70, 0x9e, 0xb9, 0xbb };
// RAS Control Point Characteristic
// 929f95ec-1391-4303-9b49-3c22a418be89
#define RAS_CONTROL_POINT_CHARACTERISTIC_UUID { 0x89, 0xbe, 0x18, 0xa4, 0x22, 0x3c, 0x49, 0x9b, \
                                                0x03, 0x43, 0x91, 0x13, 0xec, 0x95, 0x9f, 0x92 };
// RAS Procedure Enable Data Characteristic
// 929f95ec-1391-4303-9b49-3c22a418be90
#define RAS_PROCEDURE_ENABLE_DATA_CHARACTERISTIC_UUID { 0x90, 0xbe, 0x18, 0xa4, 0x22, 0x3c, 0x49, 0x9b, \
                                                        0x03, 0x43, 0x91, 0x13, 0xec, 0x95, 0x9f, 0x92 };
// RAS Subevent Ranging Data Characteristic
// 929f95ec-1391-4303-9b49-3c22a418be91
#define RAS_SE_RANGING_DATA_CHARACTERISTIC_UUID { 0x91, 0xbe, 0x18, 0xa4, 0x22, 0x3c, 0x49, 0x9b, \
                                                  0x03, 0x43, 0x91, 0x13, 0xec, 0x95, 0x9f, 0x92 };
#define INITIATOR_DEVICE_NAME "ABR Example"

#define SUBMODE_NOT_USED 0xff

#define ABR_MAX_ANT_COUNT    4

/*******************************************************************************
 ********************************  TYPEDEFS  ***********************************
 ******************************************************************************/

// TX power type
typedef int8_t abr_tx_power_t;

// PHY type
typedef sl_bt_gap_phy_coding_t abr_phy_t;

// UI modes
typedef enum {
  ABR_INITIATOR_MODE_DYNAMIC = 0,
  ABR_INITIATOR_MODE_RTT = sl_bt_cs_mode_rtt,
  ABR_INITIATOR_MODE_PBR = sl_bt_cs_mode_pbr
} abr_initiator_mode_t;

// Discovery state
typedef enum {
  ABR_DISCOVERY_STATE_IDLE,
  ABR_DISCOVERY_STATE_CONN,
  ABR_DISCOVERY_STATE_SCAN,
  ABR_DISCOVERY_STATE_FINISHED
} abr_discovery_state_t;

/// RTL library calculation result type
typedef struct {
  uint8_t connection;                   ///< Connection handle
  float distance;                       ///< Calculated distance
  float likeliness;                     ///< Calculated distance likeliness
  float rssi_distance;                  ///< Distance calculated with RSSI values
  uint8_t cs_bit_error_rate;            ///< CS bit error rate
} abr_rtl_result_t;

typedef struct {
  uint8_t offset_count;
  int16_t offset_value[ABR_MAX_ANT_COUNT];
} abr_antenna_offset_t;

/***************************************************************************//**
 * Initiator result callback type
 * @param[in] result Pointer to the result structure.
 * @param[in] user_data Pointer to additional user data.
 ******************************************************************************/
typedef void (*abr_result_cb_t)(abr_rtl_result_t *result,
                                void             *user_data);

typedef struct {
  float rssi_tx_power;
  uint32_t min_subevent_len;
  uint32_t max_subevent_len;
  uint16_t min_connection_interval;
  uint16_t max_connection_interval;
  uint16_t scan_interval;
  uint16_t scan_window;
  uint16_t max_procedure_duration;
  uint16_t min_interval;
  uint16_t max_interval;
  uint16_t max_procedure_count;
  uint16_t latency;
  uint16_t timeout;
  uint16_t min_ce_length;
  uint16_t max_ce_length;
  uint8_t mode;
  uint8_t submode;
  uint8_t max_main_mode_steps;
  uint8_t min_main_mode_steps;
  uint8_t main_mode_repetition;
  uint8_t mode0_step;
  uint8_t channel_map_repetition;
  uint8_t ch3c_jump;
  uint8_t ch3c_shape;
  uint8_t antenna_config;
  uint8_t rtt_type;
  uint8_t channel_selection_type;
  uint8_t cs_sync_antenna;
  uint8_t companion_signal_enable;
  int8_t tx_pwr_delta;
  uint8_t config_id;
  abr_tx_power_t tx_power_max_dbm;
  abr_tx_power_t tx_power_min_dbm;
  abr_tx_power_t tx_power_requested_max_dbm;
  abr_tx_power_t tx_power_requested_min_dbm;
  int8_t max_tx_power_dbm;
  abr_phy_t phy;
  abr_phy_t scan_phy;
  abr_discovery_state_t discovery_state;
  uint8_t preferred_peer_antenna;
  uint8_t *filter_address;
  uint8_t create_context;
  sl_rtl_abr_libitem rtl_handle;
  abr_result_cb_t result_cb;
  bool rssi_measurement_enabled;
  sl_bt_cs_channel_map_t channel_map;
  uint32_t channel_map_len;
  bool use_antenna_wired_offset;
  abr_antenna_offset_t antenna_offset;
} abr_initiator_config_t;

/*******************************************************************************
 ****************************   PUBLIC FUNCTIONS   *****************************
 ******************************************************************************/

/******************************************************************************
 * Set default config values for initiator.
 * @param[out] config Pointer to an initiator config structure.
 *****************************************************************************/
sl_status_t abr_initiator_config_set_default(abr_initiator_config_t *config);

#ifdef __cplusplus
};
#endif

#endif // ABR_INITIATOR_CONFIG_H

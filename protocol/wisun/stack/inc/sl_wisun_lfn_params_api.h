/***************************************************************************//**
 * @file sl_wisun_lfn_params_api.h
 * @brief Wi-SUN LFN Connection Params API
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

#ifndef SL_WISUN_LFN_PARAMS_API_H
#define SL_WISUN_LFN_PARAMS_API_H

#include <stdint.h>
#include "sl_wisun_common.h"
#include "sl_common.h"
#include "sl_status.h"

// TODO: move this header in the stack and export it to avoid dependency loop

/// API version used to check compatibility (do not edit when using this header)
#define SL_WISUN_LFN_PARAMS_API_VERSION 0x0001

/***************************************************************************//**
 * @addtogroup SL_WISUN_TYPES
 * @{
 ******************************************************************************/

/// LFN connection parameters
SL_PACK_START(1)
typedef struct {
  /// Duration of LPA listening slot (millisecond)
  /// Specification range [15, 255]
  uint8_t discovery_slot_time_ms;
  /// Number of slots for which an LFN shall listen for LPA frames
  /// Specification range [1, 255]
  uint8_t discovery_slots;
} sl_wisun_lfn_params_connection_t;
SL_PACK_END()

/// LFN data layer parameters
SL_PACK_START(1)
typedef struct {
  /// Time between LFN sampled listening points (milliseconds)
  uint32_t unicast_interval_ms;
  /// Minimum acceptable LFN unicast interval (milliseconds)
  uint32_t unicast_interval_min_ms;
  /// Maximum acceptable LFN unicast interval (milliseconds)
  uint32_t unicast_interval_max_ms;
  /// The number of LFN Broadcast Sync Period (parent defined) after which,
  /// having not received any messaging from its parent, an LFN assumes
  /// the parent is lost.
  /// Specification range [1, 60]
  uint8_t lfn_maintain_parent_time;
} sl_wisun_lfn_params_data_layer_t;
SL_PACK_END()

/// LFN network parameters
SL_PACK_START(1)
typedef struct {
  /// Recommended address registration lifetime to be used by an LFN (minutes)
  /// Specification range [1440, 5040]
  uint16_t lfn_registration_lifetime_m;
  /// Interval during which an LFN waits for an FFN NA(EARO) response (minutes)
  /// Specification range [30, 120]
  uint8_t lfn_na_wait_duration_m;
} sl_wisun_lfn_params_network_t;
SL_PACK_END()

/// LFN power parameters
SL_PACK_START(1)
typedef struct {
  /// Minimum sampled listen width (microseconds)
  /// Sampled listen is calculated with PHY parameters.
  /// Set to force sampled listen duration above this value.
  uint16_t listening_window_min_us;
  /// Minimum listening window margin (microseconds)
  /// Window Margin is calculated dynamically with aging synchronization info.
  /// Set to force margin above this value.
  uint16_t window_margin_min_us;
  /// If true, the node limits LFN broadcast interval wakeups to minimum
  /// while still maintaining time synchronization with the parent.
  /// If false, the node wakes up on every LFN broadcast interval.
  bool broadcast_lts_only:1;
} sl_wisun_lfn_params_power_t;
SL_PACK_END()

/// LFN parameter set
SL_PACK_START(1)
typedef struct {
  /**
   * Version of this API.
   *
   * This field allows to store the parameters in an NVM and check on reload
   * that they are compatible with the stack if there was an update.
   */
  uint16_t version;
  /// LFN connection parameters
  sl_wisun_lfn_params_connection_t connection;
  /// LFN data layer parameters
  sl_wisun_lfn_params_data_layer_t data_layer;
  /// LFN network parameters
  sl_wisun_lfn_params_network_t network;
  /// LFN power parameters
  sl_wisun_lfn_params_power_t power;
} sl_wisun_lfn_params_t;
SL_PACK_END()

/***************************************************************************//**
 * @addtogroup SL_WISUN_LFN_PARAMETER_SETS Predefined LFN parameter sets
 *
 * Predefined LFN parameter sets for sl_wisun_set_lfn_parameters().
 *
 * These parameter sets can be used either as-is or used as an initialization value
 * for an application-specific parameter set.
 *
 * @{
 ******************************************************************************/

/// Profile for test usage, best performance but highest power consumption
static const sl_wisun_lfn_params_t SL_WISUN_PARAMS_LFN_TEST = {
  .version = SL_WISUN_LFN_PARAMS_API_VERSION,
  .connection = {
    .discovery_slot_time_ms = 60,
    .discovery_slots = 40
  },
  .data_layer = {
    .unicast_interval_ms = SEC_TO_MS(6),
    .unicast_interval_min_ms = SEC_TO_MS(5),
    .unicast_interval_max_ms = SEC_TO_MS(60),
    .lfn_maintain_parent_time = 5
  },
  .network = {
    .lfn_registration_lifetime_m = HOUR_TO_MIN(36),
    .lfn_na_wait_duration_m = 30
  },
  .power = {
    .listening_window_min_us = 5000,
    .window_margin_min_us = 5000,
    .broadcast_lts_only = 0
  }
};

/// Profile providing balance between power consumption and performance
static const sl_wisun_lfn_params_t SL_WISUN_PARAMS_LFN_BALANCED = {
  .version = SL_WISUN_LFN_PARAMS_API_VERSION,
  .connection = {
    .discovery_slot_time_ms = 60,
    .discovery_slots = 40
  },
  .data_layer = {
    .unicast_interval_ms = SEC_TO_MS(60),
    .unicast_interval_min_ms = SEC_TO_MS(30),
    .unicast_interval_max_ms = SEC_TO_MS(300),
    .lfn_maintain_parent_time = 20
  },
  .network = {
    .lfn_registration_lifetime_m = HOUR_TO_MIN(60),
    .lfn_na_wait_duration_m = HOUR_TO_MIN(1)
  },
  .power = {
    .listening_window_min_us = 5000,
    .window_margin_min_us = 5000,
    .broadcast_lts_only = 0
  }
};

/// Profile optimized for low power consumption
static const sl_wisun_lfn_params_t SL_WISUN_PARAMS_LFN_ECO = {
  .version = SL_WISUN_LFN_PARAMS_API_VERSION,
  .connection = {
    .discovery_slot_time_ms = 60,
    .discovery_slots = 40
  },
  .data_layer = {
    .unicast_interval_ms = SEC_TO_MS(300),
    .unicast_interval_min_ms = SEC_TO_MS(60),
    .unicast_interval_max_ms = SEC_TO_MS(16776), /// 4.660 hours per spec
    .lfn_maintain_parent_time = 60
  },
  .network = {
    .lfn_registration_lifetime_m = HOUR_TO_MIN(84),
    .lfn_na_wait_duration_m = HOUR_TO_MIN(2)
  },
  .power = {
    .listening_window_min_us = 5000,
    .window_margin_min_us = 5000,
    .broadcast_lts_only = 1
  }
};

/** @} */

/** @} (end SL_WISUN_TYPES) */

#endif

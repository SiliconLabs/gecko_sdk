/***************************************************************************//**
 * @file sl_wisun_connection_params_api.h
 * @brief Wi-SUN Connection Params API
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_WISUN_CONNECTION_PARAMS_API_H
#define SL_WISUN_CONNECTION_PARAMS_API_H

#include <stdint.h>
#include "sl_wisun_common.h"
#include "sl_common.h"
#include "sl_status.h"

// TODO: move this header in the stack and export it to avoid dependency loop

/// API version used to check compatibility (do not edit when using this header)
#define SL_WISUN_PARAMS_API_VERSION 0x0001

/**************************************************************************//**
 * @addtogroup SL_WISUN_TYPES
 * @{
 *****************************************************************************/

/// Trickle parameters set
SL_PACK_START(1)
typedef struct {
  /// Minimum interval size (seconds)
  uint16_t imin_s;
  /// Maximum interval size (seconds)
  uint16_t imax_s;
  /// Redundancy constant (0 for infinity)
  uint8_t k;
} sl_wisun_trickle_params_t;
SL_PACK_END()

/// PAN discovery parameter set
SL_PACK_START(1)
typedef struct {
  /// PAN Advertisement trickle timer
  sl_wisun_trickle_params_t trickle_pa;
  /// PAN Advertisement Solicit trickle timer
  sl_wisun_trickle_params_t trickle_pas;
  /// Minimum signal level for a node to be selected as the EAPOL target for
  /// authentication immediately after a PAN Advertisement reception.
  /// Range from -174 (0) to +80 (254) dBm, 255 to disable feature.
  uint8_t eapol_target_min_sens;
  /// If true, allow join state 1 to be skipped using cached information
  /// from the previous connection.
  bool allow_skip:1;
} sl_wisun_params_discovery;
SL_PACK_END()

/// Authentication parameter set
SL_PACK_START(1)
typedef struct {
  /// Security protocol trickle timer
  sl_wisun_trickle_params_t sec_prot_trickle;
  /// Security protocol trickle timer expirations
  uint8_t sec_prot_trickle_expirations;
  /// Security protocol retry timeout (seconds)
  uint16_t sec_prot_retry_timeout_s;

  /// Initial EAPOL-Key first Tx min delay (seconds)
  uint16_t initial_key_min_s;
  /// Initial EAPOL-Key first Tx max delay (seconds)
  uint16_t initial_key_max_s;
  /// Initial EAPOL-Key retry exponential backoff min (seconds)
  uint16_t initial_key_retry_min_s;
  /// Initial EAPOL-Key retry exponential backoff max (seconds)
  uint16_t initial_key_retry_max_s;
  /// Initial EAPOL-Key retry exponential backoff max limit (seconds)
  uint16_t initial_key_retry_max_limit_s;
  /// Initial EAPOL-Key retry limit
  uint8_t initial_key_retry_limit;

  /// Temporary neighbor link minimum timeout (seconds)
  uint16_t temp_min_timeout_s;

  /// PMK lifetime (minutes)
  uint32_t pmk_lifetime_m;
  /// PTK lifetime (minutes)
  uint32_t ptk_lifetime_m;
  /// GTK_REQUEST_IMIN (minutes)
  uint16_t gtk_request_imin_m;
  /// GTK_REQUEST_IMAX (minutes)
  uint16_t gtk_request_imax_m;
  /// GTK_MAX_MISMATCH (minutes)
  uint16_t gtk_max_mismatch_m;
  /// LGTK_MAX_MISMATCH (minutes)
  uint16_t lgtk_max_mismatch_m;
  /// If true, allow join state 2 to be skipped using cached credentials
  /// from the previous connection.
  bool allow_skip:1;
} sl_wisun_params_eapol;
SL_PACK_END()

/// PAN configuration parameter set
SL_PACK_START(1)
typedef struct {
  /// PAN Configuration trickle timer
  sl_wisun_trickle_params_t trickle_pc;
  /// PAN Configuration Solicit trickle timer
  sl_wisun_trickle_params_t trickle_pcs;
} sl_wisun_params_configuration;
SL_PACK_END()

/// RPL parameters set
SL_PACK_START(1)
typedef struct {
  /// RPL first DIS maximum delay (seconds)
  uint16_t dis_max_delay_first_s;
  /// RPL DIS maximum delay (seconds)
  uint16_t dis_max_delay_s;
  /// Delay for preferred parent selection after first DIO reception (seconds)
  uint16_t init_parent_selection_s;
  /// Maximum period of NS probes used to get samples for ETX calculation (seconds)
  uint16_t etx_probe_period_max_s;
  /// Number of samples used to calculate ETX during join state 4
  uint8_t etx_samples_init;
  /// Number of samples used to refresh ETX
  uint8_t etx_samples_refresh;
  /// RPL max candidate parents
  uint8_t candidate_parents_max;
  /// RPL max parents
  uint8_t parents_max;
} sl_wisun_params_rpl;
SL_PACK_END()

/// MPL parameter set
SL_PACK_START(1)
typedef struct {
  /// MPL trickle timer
  sl_wisun_trickle_params_t trickle;
  /// MPL trickle timer expirations
  uint8_t trickle_expirations;
  /// MPL seed set entry lifetime (seconds)
  uint16_t seed_set_entry_lifetime_s;
} sl_wisun_params_mpl;
SL_PACK_END()

/// Misc parameter set
SL_PACK_START(1)
typedef struct {
  /// Border router communication timeout PAN_TIMEOUT
  uint8_t pan_timeout_m;
  /// Temporary neighbor link minimum timeout
  uint16_t temp_link_min_timeout_s;
} sl_wisun_params_misc;
SL_PACK_END()

/// FFN parameter set
SL_PACK_START(1)
typedef struct {
  /**
   * Version of this API.
   *
   * This field allows to store the parameters in an NVM and check on reload
   * that they are compatible with the stack if there was an update.
   */
  uint16_t version;
  /// PAN discovery parameter set
  sl_wisun_params_discovery discovery;
  /// PAN configuration parameter set
  sl_wisun_params_configuration configuration;
  /// Authentication parameter set
  sl_wisun_params_eapol eapol;
  /// RPL parameters set
  sl_wisun_params_rpl rpl;
  /// MPL parameter set
  sl_wisun_params_mpl mpl;
  /// Misc parameter set
  sl_wisun_params_misc misc;
} sl_wisun_connection_params_t;
SL_PACK_END()

/***************************************************************************//**
 * @addtogroup SL_WISUN_FFN_PARAMETER_SETS Predefined FFN parameter sets
 *
 * Predefined FFN parameter sets for sl_wisun_set_connection_parameters().
 *
 * These parameter sets can be used either as-is to replicate the behavior of
 * sl_wisun_set_network_size(), or used as an initialization value for an
 * application-specific parameter set.
 *
 * @{
 ******************************************************************************/

/// Profile for development (shorter connection time)
static const sl_wisun_connection_params_t SL_WISUN_PARAMS_PROFILE_TEST = {
  .version = SL_WISUN_PARAMS_API_VERSION,
  .discovery = {
    .trickle_pa = {
      .imin_s = 5,
      .imax_s = 60,
      .k = 1
    },
    .trickle_pas = {
      .imin_s = 5,
      .imax_s = 15,
      .k = 1
    },
    .eapol_target_min_sens = DBM_TO_RSL_RANGE(-60),
    .allow_skip = true
  },
  .configuration = {
    .trickle_pc = {
      .imin_s = 5,
      .imax_s = 60,
      .k = 1
    },
    .trickle_pcs = {
      .imin_s = 5,
      .imax_s = 15,
      .k = 1
    }
  },
  .eapol = {
    .sec_prot_trickle = {
      .imin_s = 60,
      .imax_s = 120,
      .k = 0,
    },
    .sec_prot_trickle_expirations = 4,
    .sec_prot_retry_timeout_s = 450,
    .initial_key_min_s = 2,
    .initial_key_max_s = 3,
    .initial_key_retry_min_s = 180,
    .initial_key_retry_max_s = 420,
    .initial_key_retry_max_limit_s = 420,
    .initial_key_retry_limit = 2,
    .temp_min_timeout_s = 330,
    .pmk_lifetime_m = MONTH_TO_MIN(4),
    .ptk_lifetime_m = MONTH_TO_MIN(2),
    .gtk_request_imin_m = 1,
    .gtk_request_imax_m = 4,
    .gtk_max_mismatch_m = 64,
    .lgtk_max_mismatch_m = 60,
    .allow_skip = true
  },
  .rpl = {
    .dis_max_delay_first_s = 1,
    .dis_max_delay_s = 5,
    .init_parent_selection_s = 1,
    .etx_probe_period_max_s = 1,
    .etx_samples_init = 1,
    .etx_samples_refresh = 4,
    .candidate_parents_max = 5,
    .parents_max = 2,
  },
  .mpl = {
    .trickle = {
      .imin_s = 1,
      .imax_s = 10,
      .k = 8,
    },
    .trickle_expirations = 2,
    .seed_set_entry_lifetime_s = 180,
  },
  .misc = {
    .pan_timeout_m = 30,
    .temp_link_min_timeout_s = 260,
  }
};

/// Profile for certification testing
static const sl_wisun_connection_params_t SL_WISUN_PARAMS_PROFILE_CERTIF = {
  .version = SL_WISUN_PARAMS_API_VERSION,
  .discovery = {
    .trickle_pa = {
      .imin_s = 15,
      .imax_s = 60,
      .k = 1
    },
    .trickle_pas = {
      .imin_s = 15,
      .imax_s = 60,
      .k = 1
    },
    .eapol_target_min_sens = 255,
    .allow_skip = false
  },
  .configuration = {
    .trickle_pc = {
      .imin_s = 15,
      .imax_s = 60,
      .k = 1
    },
    .trickle_pcs = {
      .imin_s = 15,
      .imax_s = 60,
      .k = 1
    }
  },
  .eapol = {
    .sec_prot_trickle = {
      .imin_s = 60,
      .imax_s = 120,
      .k = 0,
    },
    .sec_prot_trickle_expirations = 4,
    .sec_prot_retry_timeout_s = 450,
    .initial_key_min_s = 3,
    .initial_key_max_s = 30,
    .initial_key_retry_min_s = 180,
    .initial_key_retry_max_s = 420,
    .initial_key_retry_max_limit_s = 420,
    .initial_key_retry_limit = 2,
    .temp_min_timeout_s = 330,
    .pmk_lifetime_m = MONTH_TO_MIN(4),
    .ptk_lifetime_m = MONTH_TO_MIN(2),
    .gtk_request_imin_m = 4,
    .gtk_request_imax_m = 64,
    .gtk_max_mismatch_m = 1,
    .lgtk_max_mismatch_m = 60,
    .allow_skip = false
  },
  .rpl = {
    .dis_max_delay_first_s = 1,
    .dis_max_delay_s = 180,
    .init_parent_selection_s = 10,
    .etx_probe_period_max_s = 4,
    .etx_samples_init = 1,
    .etx_samples_refresh = 4,
    .candidate_parents_max = 8,
    .parents_max = 4,
  },
  .mpl = {
    .trickle = {
      .imin_s = 5,
      .imax_s = 40,
      .k = 8,
    },
    .trickle_expirations = 2,
    .seed_set_entry_lifetime_s = 720,
  },
  .misc = {
    .pan_timeout_m = 30,
    .temp_link_min_timeout_s = 260,
  }
};

/// Profile for a small network
static const sl_wisun_connection_params_t SL_WISUN_PARAMS_PROFILE_SMALL = {
  .version = SL_WISUN_PARAMS_API_VERSION,
  .discovery = {
    .trickle_pa = {
      .imin_s = 15,
      .imax_s = 60,
      .k = 1
    },
    .trickle_pas = {
      .imin_s = 15,
      .imax_s = 60,
      .k = 1
    },
    .eapol_target_min_sens = DBM_TO_RSL_RANGE(-60),
    .allow_skip = true
  },
  .configuration = {
    .trickle_pc = {
      .imin_s = 15,
      .imax_s = 60,
      .k = 1
    },
    .trickle_pcs = {
      .imin_s = 15,
      .imax_s = 60,
      .k = 1
    }
  },
  .eapol = {
    .sec_prot_trickle = {
      .imin_s = 60,
      .imax_s = 120,
      .k = 0,
    },
    .sec_prot_trickle_expirations = 4,
    .sec_prot_retry_timeout_s = 450,
    .initial_key_min_s = 3,
    .initial_key_max_s = 30,
    .initial_key_retry_min_s = 180,
    .initial_key_retry_max_s = 420,
    .initial_key_retry_max_limit_s = 420,
    .initial_key_retry_limit = 2,
    .temp_min_timeout_s = 330,
    .pmk_lifetime_m = MONTH_TO_MIN(4),
    .ptk_lifetime_m = MONTH_TO_MIN(2),
    .gtk_request_imin_m = 1,
    .gtk_request_imax_m = 4,
    .gtk_max_mismatch_m = 64,
    .lgtk_max_mismatch_m = 60,
    .allow_skip = true
  },
  .rpl = {
    .dis_max_delay_first_s = 1,
    .dis_max_delay_s = 180,
    .init_parent_selection_s = 10,
    .etx_probe_period_max_s = 4,
    .etx_samples_init = 1,
    .etx_samples_refresh = 4,
    .candidate_parents_max = 5,
    .parents_max = 2,
  },
  .mpl = {
    .trickle = {
      .imin_s = 1,
      .imax_s = 10,
      .k = 8,
    },
    .trickle_expirations = 2,
    .seed_set_entry_lifetime_s = 180,
  },
  .misc = {
    .pan_timeout_m = 30,
    .temp_link_min_timeout_s = 260,
  }
};

/// Profile for a medium network
static const sl_wisun_connection_params_t SL_WISUN_PARAMS_PROFILE_MEDIUM = {
  .version = SL_WISUN_PARAMS_API_VERSION,
  .discovery = {
    .trickle_pa = {
      .imin_s = 60,
      .imax_s = 960,
      .k = 1
    },
    .trickle_pas = {
      .imin_s = 60,
      .imax_s = 960,
      .k = 1
    },
    .eapol_target_min_sens = DBM_TO_RSL_RANGE(-60),
    .allow_skip = true
  },
  .configuration = {
    .trickle_pc = {
      .imin_s = 60,
      .imax_s = 960,
      .k = 1
    },
    .trickle_pcs = {
      .imin_s = 60,
      .imax_s = 960,
      .k = 1
    }
  },
  .eapol = {
    .sec_prot_trickle = {
      .imin_s = 60,
      .imax_s = 120,
      .k = 0,
    },
    .sec_prot_trickle_expirations = 4,
    .sec_prot_retry_timeout_s = 450,
    .initial_key_min_s = 3,
    .initial_key_max_s = 30,
    .initial_key_retry_min_s = 180,
    .initial_key_retry_max_s = 420,
    .initial_key_retry_max_limit_s = 720,
    .initial_key_retry_limit = 4,
    .temp_min_timeout_s = 330,
    .pmk_lifetime_m = MONTH_TO_MIN(4),
    .ptk_lifetime_m = MONTH_TO_MIN(2),
    .gtk_request_imin_m = 4,
    .gtk_request_imax_m = 64,
    .gtk_max_mismatch_m = 64,
    .lgtk_max_mismatch_m = 60,
    .allow_skip = true
  },
  .rpl = {
    .dis_max_delay_first_s = 60,
    .dis_max_delay_s = 180,
    .init_parent_selection_s = 10,
    .etx_probe_period_max_s = 8,
    .etx_samples_init = 1,
    .etx_samples_refresh = 4,
    .candidate_parents_max = 5,
    .parents_max = 2,
  },
  .mpl = {
    .trickle = {
      .imin_s = 1,
      .imax_s = 32,
      .k = 8,
    },
    .trickle_expirations = 2,
    .seed_set_entry_lifetime_s = 576,
  },
  .misc = {
    .pan_timeout_m = 60,
    .temp_link_min_timeout_s = 260,
  }
};

/// Profile for a large network
static const sl_wisun_connection_params_t SL_WISUN_PARAMS_PROFILE_LARGE = {
  .version = SL_WISUN_PARAMS_API_VERSION,
  .discovery = {
    .trickle_pa = {
      .imin_s = 120,
      .imax_s = 1536,
      .k = 1
    },
    .trickle_pas = {
      .imin_s = 120,
      .imax_s = 1536,
      .k = 1
    },
    .eapol_target_min_sens = DBM_TO_RSL_RANGE(-60),
    .allow_skip = true
  },
  .configuration = {
    .trickle_pc = {
      .imin_s = 120,
      .imax_s = 1536,
      .k = 1
    },
    .trickle_pcs = {
      .imin_s = 120,
      .imax_s = 1536,
      .k = 1
    }
  },
  .eapol = {
    .sec_prot_trickle = {
      .imin_s = 60,
      .imax_s = 240,
      .k = 0,
    },
    .sec_prot_trickle_expirations = 4,
    .sec_prot_retry_timeout_s = 750,
    .initial_key_min_s = 3,
    .initial_key_max_s = 30,
    .initial_key_retry_min_s = 300,
    .initial_key_retry_max_s = 600,
    .initial_key_retry_max_limit_s = 900,
    .initial_key_retry_limit = 4,
    .temp_min_timeout_s = 750,
    .pmk_lifetime_m = MONTH_TO_MIN(4),
    .ptk_lifetime_m = MONTH_TO_MIN(2),
    .gtk_request_imin_m = 4,
    .gtk_request_imax_m = 64,
    .gtk_max_mismatch_m = 64,
    .lgtk_max_mismatch_m = 60,
    .allow_skip = true
  },
  .rpl = {
    .dis_max_delay_first_s = 60,
    .dis_max_delay_s = 180,
    .init_parent_selection_s = 10,
    .etx_probe_period_max_s = 8,
    .etx_samples_init = 1,
    .etx_samples_refresh = 4,
    .candidate_parents_max = 5,
    .parents_max = 2,
  },
  .mpl = {
    .trickle = {
      .imin_s = 5,
      .imax_s = 40,
      .k = 8,
    },
    .trickle_expirations = 2,
    .seed_set_entry_lifetime_s = 720,
  },
  .misc = {
    .pan_timeout_m = 90,
    .temp_link_min_timeout_s = 520,
  }
};

/** @} */

/** @} (end SL_WISUN_TYPES) */

#endif

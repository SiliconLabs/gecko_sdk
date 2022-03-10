/***************************************************************************//**
 * @file
 * @brief This file contains the type definitions for RAIL structures, enums,
 *   and other types.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "pa_auto_mode.h"

#if _SILICON_LABS_32B_SERIES_1_CONFIG != 0
static RAIL_PaAutoModeConfigEntry_t RAIL_PaAutoModeConfigDefault[] = {
  // LP PA's range is from -12.5 to 0 dBm
  // Because the default algorithm stops at the
  // first matching entry, specify LP for its range
  // then HP for everything else.
  {
    .min = -125,
    .max = 0,
    .mode = RAIL_TX_POWER_MODE_2P4_LP,
    .band = RAIL_PA_BAND_2P4GIG
  },
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = RAIL_TX_POWER_MODE_2P4_HP,
    .band = RAIL_PA_BAND_2P4GIG
  },
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = RAIL_TX_POWER_MODE_SUBGIG,
    .band = RAIL_PA_BAND_SUBGIG
  }
};
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 1
static RAIL_PaAutoModeConfigEntry_t RAIL_PaAutoModeConfigDefault[] = {
  // While EFR32XG21 does have a low power PA, matching networks can only
  // perform well for the HP and MP PA's, or the LP PA alone.
  {
    .min = INT16_MIN,
    .max = 100,
    .mode = RAIL_TX_POWER_MODE_2P4_MP,
    .band = RAIL_PA_BAND_2P4GIG
  },
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = RAIL_TX_POWER_MODE_2P4_HP,
    .band = RAIL_PA_BAND_2P4GIG
  }
};
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 2
static RAIL_PaAutoModeConfigEntry_t RAIL_PaAutoModeConfigDefault[] = {
  {
    .min = -287,
    .max = 0,
    .mode = RAIL_TX_POWER_MODE_2P4_LP,
    .band = RAIL_PA_BAND_2P4GIG
  },
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = RAIL_TX_POWER_MODE_2P4_HP,
    .band = RAIL_PA_BAND_2P4GIG
  }
};
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 3
static RAIL_PaAutoModeConfigEntry_t RAIL_PaAutoModeConfigDefault[] = {
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = RAIL_TX_POWER_MODE_SUBGIG_HP,
    .band = RAIL_PA_BAND_SUBGIG
  }
};
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 4
static RAIL_PaAutoModeConfigEntry_t RAIL_PaAutoModeConfigDefault10dBm[] = {
  {
    .min = -250,
    .max = 0,
    .mode = RAIL_TX_POWER_MODE_2P4_LP,
    .band = RAIL_PA_BAND_2P4GIG
  },
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = RAIL_TX_POWER_MODE_2P4_HP,
    .band = RAIL_PA_BAND_2P4GIG
  }
};
static RAIL_PaAutoModeConfigEntry_t RAIL_PaAutoModeConfigDefault[] = {
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = RAIL_TX_POWER_MODE_2P4_HP,
    .band = RAIL_PA_BAND_2P4GIG
  }
};
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 5
static RAIL_PaAutoModeConfigEntry_t RAIL_PaAutoModeConfigDefault[] = {
// todo_sol: PA auto mode
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = 0,
    .band = RAIL_PA_BAND_SUBGIG
  }
};
#else
static RAIL_PaAutoModeConfigEntry_t RAIL_PaAutoModeConfigDefault[] = {
  {
    .min = INT16_MIN,
    .max = INT16_MAX,
    .mode = 0,
    .band = RAIL_PA_BAND_2P4GIG
  }
};
#endif

#ifdef RAIL_PA_AUTO_MODE_WEAK
__WEAK
#endif
#if (defined(RAIL_PA_AUTO_MODE_WEAK)) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 4)
RAIL_PaAutoModeConfigEntry_t * RAIL_PaAutoModeConfig = RAIL_PaAutoModeConfigDefault;
#else
RAIL_PaAutoModeConfigEntry_t * const RAIL_PaAutoModeConfig = RAIL_PaAutoModeConfigDefault;
#endif

#ifdef RAIL_PA_AUTO_MODE_WEAK
__WEAK
#endif
RAIL_Status_t RAILCb_PaAutoModeDecision(RAIL_Handle_t railHandle,
                                        RAIL_TxPower_t *power,
                                        RAIL_TxPowerMode_t *mode,
                                        const RAIL_ChannelConfigEntry_t *chCfgEntry)
{
  // railHandle isn't used in the default implementation, but
  // provide it in case a custom implementation does.
  (void)railHandle;
  *mode = RAIL_TX_POWER_MODE_NONE;

  // We need to consider both bands on all chips which can support both bands.
#if RAIL_FEAT_DUAL_BAND_RADIO
  RAIL_PaBand_t band = RAIL_PA_BAND_2P4GIG;
  if ((chCfgEntry != NULL) && (chCfgEntry->baseFrequency < 1000000000UL)) {
    band = RAIL_PA_BAND_SUBGIG;
  }
#else
  (void)chCfgEntry;
#endif

#if _SILICON_LABS_32B_SERIES_2_CONFIG == 4
  if (RAIL_SupportsTxPowerMode(railHandle,
                               RAIL_TX_POWER_MODE_2P4GIG_LP,
                               NULL)) {
    RAIL_PaAutoModeConfig = RAIL_PaAutoModeConfigDefault10dBm;
  }
#endif

  // Find the index of the configuration entry that contains
  // the desired power.
  // Note: Code assumes there must be a catch-all entry for each band
  // else the loop will wander into uncharted RAM
  for (uint8_t index = 0U; RAIL_PaAutoModeConfig[index].band < RAIL_PA_BAND_COUNT; index++) {
    RAIL_PaAutoModeConfigEntry_t entry = RAIL_PaAutoModeConfig[index];
    bool validBand = true;
#if RAIL_FEAT_DUAL_BAND_RADIO
    validBand = (entry.band == band);
#endif
    if (validBand && (entry.min <= *power) && (entry.max >= *power)) {
      *mode = entry.mode;
      break;
    }
  }

  // If we still haven't found anything, just error out.
  if (*mode == RAIL_TX_POWER_MODE_NONE) {
    return RAIL_STATUS_INVALID_PARAMETER;
  }

  return RAIL_STATUS_NO_ERROR;
}

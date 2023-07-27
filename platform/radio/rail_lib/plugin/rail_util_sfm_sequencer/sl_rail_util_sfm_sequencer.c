/***************************************************************************//**
 * @file
 * @brief
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
#include "sl_rail_util_sfm_sequencer_config.h"
#include "rail.h"

#ifdef SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_SELECTION
RAIL_Status_t RAILCb_LoadSfmSequencer(void)
{
#if (SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_SELECTION == SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_FSK_OFDM_OQPSK)
  return RAIL_LoadSfmSunFskOfdmOqpsk(RAIL_EFR32_HANDLE);
#elif (SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_SELECTION == SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_OFDM_OQPSK)
  return RAIL_LoadSfmSunOfdmOqpsk(RAIL_EFR32_HANDLE);
#elif (SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_SELECTION == SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_OFDM)
  return RAIL_LoadSfmSunOfdm(RAIL_EFR32_HANDLE);
#elif (SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_SELECTION == SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_EMPTY)
  return RAIL_LoadSfmEmpty(RAIL_EFR32_HANDLE);
#else
  return RAIL_STATUS_INVALID_CALL;
#endif
}
#endif

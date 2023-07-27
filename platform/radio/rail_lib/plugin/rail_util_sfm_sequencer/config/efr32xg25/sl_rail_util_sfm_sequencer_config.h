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

#ifndef SL_RAIL_UTIL_SFM_SEQUENCER_CONFIG_H
#define SL_RAIL_UTIL_SFM_SEQUENCER_CONFIG_H

#define SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_FSK_OFDM_OQPSK   0
#define SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_OFDM_OQPSK       1
#define SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_OFDM             2
#define SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_EMPTY            3

// <<< Use Configuration Wizard in Context Menu >>>

// <h> SFM Image Selection
// <o SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_SELECTION> Modulations supported by SFM image
// <SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_FSK_OFDM_OQPSK=> SUN FSK + SUN OFDM + SUN OQPSK
// <SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_OFDM_OQPSK=> SUN OFDM + SUN OQPSK
// <SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_OFDM=> SUN OFDM
// <SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_EMPTY=> NONE
// <i> Default: SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_FSK_OFDM_OQPSK
#define SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_SELECTION SL_RAIL_UTIL_SFM_SEQUENCER_SUN_MODULATIONS_FSK_OFDM_OQPSK
// </h>

// <<< end of configuration section >>>

#endif // SL_RAIL_UTIL_SFM_SEQUENCER_CONFIG_H

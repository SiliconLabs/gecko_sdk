/***************************************************************************//**
 * @file
 * @brief
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

#ifndef SL_FLEX_RAIL_PACKAGE_ASSISTANT_CONFIG_H_
#define SL_FLEX_RAIL_PACKAGE_ASSISTANT_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Assistant print settings
// <o PRINT_PACKAGE_INFO> Enable assistant log prints
// <i> Default: 0
// <i> 1 enabled, 0 disabled
#define PRINT_PACKAGE_INFO      (0)

// </h> Assistant print settings

// <h> WISUN FSK header settings
// <o WISUN_FSK_FCS_TYPE> FCS is on/off
// <i> Default: 0
// <i> FCS is on/off.
#define WISUN_FSK_FCS_TYPE      (0)

// <o WISUN_FSK_WHITENING> Whitening is on/off
// <i> Default: 1
// <i> Whitening is on/off
#define WISUN_FSK_WHITENING      (1)

// </h> WISUN FSK header settings

// <h> WISUN OFDM header settings
// <o WISUN_OFDM_RATE> Default Radio Configuration
// <i> Default: 6
#define WISUN_OFDM_RATE  (6)

// <o WISUN_OFDM_SCRAMBLER> 2 bits wide, The Scrambler field (S1-S0) specifies the scrambling seed
// <i> Default: 0
// <i> 2 bits wide, The Scrambler field (S1-S0) specifies the scrambling seed
#define WISUN_OFDM_SCRAMBLER      (0)

// </h> WISUN OFDM header settings

// <h> WISUN OQPSK header settings
// <o SUN_OQPSK_SPREADINGMODE> spreading mode
// <i> Default: 0
// <i> spreading mode
#define SUN_OQPSK_SPREADINGMODE      (0)

// <o SUN_OQPSK_RATEMODE> rate mode: 2 bits wide
// <i> Default: 1
// <i> rate mode: 2 bits wide
#define SUN_OQPSK_RATEMODE      (0)

// </h> WISUN OQPSK header settings

// <h> SideWalk FSK header settings
// <o  SIDEWALK_FSK_FCS_TYPE> FCS is on/off
// <i> Default: 0
// <i> FCS is on/off.
#define SIDEWALK_FSK_FCS_TYPE      (1)

// <o  SIDEWALK_FSK_WHITENING> Whitening is on/off
// <i> Default: 1
// <i> Whitening is on/off
#define  SIDEWALK_FSK_WHITENING      (1)

// </h> SideWalk FSK header settings

// <<< end of configuration section >>>

#endif // SL_FLEX_RAIL_PACKAGE_ASSISTANT_CONFIG_H_

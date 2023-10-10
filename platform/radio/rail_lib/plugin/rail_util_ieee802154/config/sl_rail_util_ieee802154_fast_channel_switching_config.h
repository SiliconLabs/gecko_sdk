/***************************************************************************//**
 * @file
 * @brief IEEE802.15.4 fast channel switching configuration file.
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

#ifndef SL_RAIL_UITL_IEEE802154_FAST_CHANNEL_SWITCHING_CONFIG_H
#define SL_RAIL_UITL_IEEE802154_FAST_CHANNEL_SWITCHING_CONFIG_H

#include "rail_features.h"

#if RAIL_IEEE802154_SUPPORTS_RX_CHANNEL_SWITCHING == 0
#error "IEEE.802.15.4 RX channel switching unsupported on this platform!"
#endif //RAIL_IEEE802154_SUPPORTS_RX_CHANNEL_SWITCHING

#define sl_rail_util_ieee802154_is_fast_channel_switching_phy_selected() SL_RAIL_UTIL_IEEE802154_FAST_CHANNEL_SWITCHING_ENABLED

// <<< Use Configuration Wizard in Context Menu >>>
// <h> IEEE802.15.4 Fast Channel Switching Configuration
// <q SL_RAIL_UTIL_IEEE802154_FAST_CHANNEL_SWITCHING_ENABLED> Enable fast channel switching
// <i> Default: 1
#define SL_RAIL_UTIL_IEEE802154_FAST_CHANNEL_SWITCHING_ENABLED   1
// </h>
// <<< end of configuration section >>>
#endif //SL_RAIL_UITL_IEEE802154_FAST_CHANNEL_SWITCHING_CONFIG_H

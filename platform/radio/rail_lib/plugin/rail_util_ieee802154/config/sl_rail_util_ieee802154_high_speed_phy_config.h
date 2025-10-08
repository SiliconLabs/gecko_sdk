/***************************************************************************//**
 * @file
 * @brief IEEE802.15.4 High Speed PHY configuration file.
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

#ifndef SL_RAIL_UITL_IEEE802154_HIGH_SPEED_PHY_CONFIG_H
#define SL_RAIL_UITL_IEEE802154_HIGH_SPEED_PHY_CONFIG_H

#define SL_RAIL_UTIL_IEEE802154_ACTIVE_RADIO_CONFIG_2P4_2MBPS (sl_rail_util_ieee802154_get_high_speed_phy_config())

// <<< Use Configuration Wizard in Context Menu >>>
// <h> IEEE802.15.4 High Speed PHY Configuration
// <q SL_RAIL_UTIL_IEEE802154_RADIO_CONFIG_2P4_1MBPS_FEC_SUPPORTED> Enable 1Mbps FEC PHY
// <i> (Enable)1Mbps high speed PHY with forward error correction is supported.
// <i> (Disable)1Mbps high speed PHY with forward error correction is unsupported.
// <i> Default: 0
#define SL_RAIL_UTIL_IEEE802154_RADIO_CONFIG_2P4_1MBPS_FEC_SUPPORTED 0
// <q SL_RAIL_UTIL_IEEE802154_RADIO_CONFIG_2P4_2MBPS_SUPPORTED> Enable 2Mbps PHY
// <i> (Enable)2Mbps high speed PHY without forward error correction is supported.
// <i> (Disable)2Mbps high speed PHY without forward error correction is unsupported.
// <i> Default: 1
#define SL_RAIL_UTIL_IEEE802154_RADIO_CONFIG_2P4_2MBPS_SUPPORTED 1
// </h>
// <<< end of configuration section >>>

#define sl_rail_util_ieee802154_is_high_speed_phy_selected() (0                                                               \
                                                              || SL_RAIL_UTIL_IEEE802154_RADIO_CONFIG_2P4_1MBPS_FEC_SUPPORTED \
                                                              || SL_RAIL_UTIL_IEEE802154_RADIO_CONFIG_2P4_2MBPS_SUPPORTED)

#define SL_RAIL_UTIL_IEEE802154_2P4_2MBPS_RUNTIME_PHY_SELECT (1                                                               \
                                                              && SL_RAIL_UTIL_IEEE802154_RADIO_CONFIG_2P4_1MBPS_FEC_SUPPORTED \
                                                              && SL_RAIL_UTIL_IEEE802154_RADIO_CONFIG_2P4_2MBPS_SUPPORTED)

#define SL_RAIL_UTIL_IEEE802154_2P4_2MBPS_PHY_ENABLED (sl_rail_util_ieee802154_is_high_speed_phy_selected())

#endif //SL_RAIL_UITL_IEEE802154_HIGH_SPEED_PHY_CONFIG_H

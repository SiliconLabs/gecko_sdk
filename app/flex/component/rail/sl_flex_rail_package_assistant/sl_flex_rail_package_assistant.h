/***************************************************************************//**
 * @file
 * @brief Pacgaking Assitent file.
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

#ifndef SL_FLEX_RAIL_PACKAGE_ASSISTANT_H_
#define SL_FLEX_RAIL_PACKAGE_ASSISTANT_H_

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_component_catalog.h"
#include "sl_flex_packet_asm.h"
#include "sl_rail_util_init_inst0_config.h"
#include "sl_rail_util_protocol_types.h"
#include "sl_rail_util_pa_config.h"
#include "rail.h"

#if defined(SL_CATALOG_APP_LOG_PRESENT)
#include "app_log.h"
#endif
#if defined(SL_CATALOG_APP_ASSERT_PRESENT)
#include "app_assert.h"
#endif

#if defined(SL_CATALOG_RADIO_CONFIG_SIMPLE_RAIL_SINGLEPHY_PRESENT)
#include "rail_config.h"
#include "rail_chip_specific.h"
#include "sl_rail_util_pa_config.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#if defined(RAIL0_CHANNEL_GROUP_1_PHY_IEEE802154_SUN_FSK_169MHZ_4FSK_9P6KBPS)  \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_IEEE802154_SUN_FSK_169MHZ_2FSK_4P8KBPS) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_IEEE802154_SUN_FSK_169MHZ_2FSK_2P4KBPS) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_IEEE802154_SUN_FSK_450MHZ_2FSK_4P8KBPS) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_IEEE802154_SUN_FSK_450MHZ_4FSK_9P6KBPS) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_IEEE802154_SUN_FSK_896MHZ_2FSK_40KBPS)  \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_IEEE802154_SUN_FSK_915MHZ_2FSK_10KBPS)  \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_IEEE802154_SUN_FSK_920MHZ_4FSK_400KBPS)
#undef RAIL0_CHANNEL_GROUP_1_PROFILE_BASE
#define RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_FSK
#endif

#if defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_863MHZ_PLAN33_OFDM_OPT4_EU)  \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_863MHZ_PLAN37_OFDM_OPT4_EU) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_870MHZ_PLAN35_OFDM_OPT4_EU)
#define RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_OFDM
#endif

#if defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_915MHZ_PLAN2_OFDM_OPT3_NA)  \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_915MHZ_PLAN1_OFDM_OPT4_NA) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_915MHZ_PLAN4_OFDM_OPT2_NA) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_915MHZ_PLAN5_OFDM_OPT1_NA)
#define RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_OFDM
#endif

#if defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_915MHZ_PLAN1_OFDM_OPT4_BZ)  \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_915MHZ_PLAN2_OFDM_OPT3_BZ) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_915MHZ_PLAN4_OFDM_OPT2_BZ) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_915MHZ_PLAN5_OFDM_OPT1_BZ)
#define RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_OFDM
#endif

#if defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_920MHZ_PLAN21_OFDM_OPT4_JP)  \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_920MHZ_PLAN24_OFDM_OPT2_JP) \
  || defined(RAIL0_CHANNEL_GROUP_1_PHY_WISUN_FAN_1V1_920MHZ_PLAN22_OFDM_OPT3_JP)
#define RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_OFDM
#endif

// RAIL0_CHANNELS_FOR_915_

#if defined(RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_HAN)       \
  || defined(RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_FAN_1_0)  \
  || defined(RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_FAN_1_1)  \
  || defined(RAIL0_CHANNELS_FOR_915_PROFILE_WISUN_HAN)     \
  || defined(RAIL0_CHANNELS_FOR_915_PROFILE_WISUN_FAN_1_0) \
  || defined(RAIL0_CHANNELS_FOR_915_PROFILE_WISUN_FAN_1_1)
#ifndef RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_OFDM
#define RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_FSK
#endif
#endif

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------
/*****************************************************************************
* Checks phy setting to avoid errors at packet sending
*****************************************************************************/
void validation_check(void);

/******************************************************************************
 * The API helps to unpack the received packet, point to the payload and returns the length.
 *
 * @param rx_destination Where should the full packet be unpacked
 * @param packet_information Where should all the information of the packet stored
 * @param start_of_payload Pointer where the payload starts
 * @return The length of the received payload
 *****************************************************************************/
uint16_t unpack_packet(uint8_t *rx_destination, const RAIL_RxPacketInfo_t *packet_information, uint8_t **start_of_payload);

/******************************************************************************
 * The API prepares the packet for sending and load it in the RAIL TX FIFO
 *
 * @param rail_handle Which rail handlers should be used for the TX FIFO writing
 * @param out_data The payload buffer
 * @param length The length of the payload
 *****************************************************************************/
void prepare_package(RAIL_Handle_t rail_handle, uint8_t *out_data, uint16_t length);

/******************************************************************************
 * CLI - get_print_package_info message: Get the print setting
 *****************************************************************************/
uint8_t get_print_packet_info(void);

/******************************************************************************
 * CLI - set_print_package_info message: Get the print setting
 *****************************************************************************/
void set_print_packet_info(uint8_t new_print_packet_info);

/******************************************************************************
 * The API helps to print out the received packet
 *
 * @param rx_destination where is the packet stored
 * @param length how long is the packet
 *****************************************************************************/
void printf_rx_packet(const uint8_t * const rx_buffer, uint16_t length);

#endif /* SL_FLEX_RAIL_PACKAGE_ASSISTANT_H_ */

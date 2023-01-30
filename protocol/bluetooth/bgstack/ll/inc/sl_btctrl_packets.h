/***************************************************************************//**
 * @brief Packet API provides several functions to read detailed information from
 * the received packet.
 *
 * Currently only RSSI reading is supported.
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

#ifndef SL_BTCTRL_PACKETS_H
#define SL_BTCTRL_PACKETS_H

#include <stdint.h>

typedef const void * sl_btctrl_packet_t;

/***************************************************************************//**
 * @addtogroup sl_btctrl_packets API to get detailed information of received packet
 * @{
 ******************************************************************************/

/**
 * Get RSSI of received packet
 *
 * @param packet Packet where the RSSI value is read from.
 * @return Signed RSSI value of the given packet in dBm.
 */
int8_t sl_btctrl_get_packet_rssi(sl_btctrl_packet_t packet);

/** @} sl_btctrl_packets */
#endif

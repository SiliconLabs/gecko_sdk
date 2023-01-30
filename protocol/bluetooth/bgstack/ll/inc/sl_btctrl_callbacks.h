/***************************************************************************//**
 * @brief Bluetooth controller callback API
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

#ifndef SL_BTCTRL_EVENTS_H
#define SL_BTCTRL_EVENTS_H

#include <stdbool.h>
#include "sl_btctrl_packets.h"

/**
 * @addtogroup sl_btctrl_callbacks Bluetooth Controller Callbacks
 *
 * This API can be used to change the behaviour of Bluetooth controller.
 *
 * Example usage: RSSI based scan request transmission can be implented by
 * adding following callback function into application code. Following
 * examples adds logic to transmit scan request packet only to the devices
 * which advertising packet RSSI is over -60.
 *
 * \code{.c}
 *  #include <sl_btctrl_callbacks.h>
 *  #include <sl_btctrl_packets.h>
 *
 *  bool sl_btctrl_filter_scan_request_transmission_cb(sl_btctrl_packet_t packet)
 *  {
 *    int8_t rssi = sl_btctrl_get_packet_rssi(packet);
 *    return rssi > -60;
 *  }
 * \endcode
 *
 * \note All callback functions are called from critical section which
 *       means that they should return immediately and should not do any
 *       time consuming operations.
 *
 * \note It is NOT allowed to
 *         - call more that few instructions, which consume less than one micro second
 *         - call any BGAPI functions or other time consuming operations
 *
 * \note Only APIs from sl_btctrl_packets.h can be used in callback functions.
 * @{
 */

/**
 * This callback function is called before scan request transmission. The
 * return value of callback function is used as a guidance for controller
 * to decide whether or not to transmit scan request packet.
 *
 * @param packet Received advertising packet from peripheral.
 * @return Scan request is sent if true is returned.
 */
bool sl_btctrl_filter_scan_request_transmission_cb(sl_btctrl_packet_t packet);

/** @} sl_btctrl_callbacks */
#endif

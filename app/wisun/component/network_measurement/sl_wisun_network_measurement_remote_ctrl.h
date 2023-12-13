/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Core Component
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __SL_WISUN_NETWORK_MEASUREMENT_REMOTE_CTRL_H__
#define __SL_WISUN_NETWORK_MEASUREMENT_REMOTE_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "sl_wisun_coap.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Network Measurement Remote Control CoAP CLI ping measurement callback.
 * @details Handle incoming CLI command from CoAP message.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_ping_cb(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Network Measurement Remote Control CoAP CLI iPerf measurement callback.
 * @details Handle incoming CLI command from CoAP message.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_iperf_cb(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Network Measurement Remote Control CoAP CLI neighbour callback.
 * @details Handle incoming CLI command from CoAP message.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_nbr_cb(const sl_wisun_coap_packet_t * const req_packet);

#ifdef __cplusplus
}
#endif

#endif

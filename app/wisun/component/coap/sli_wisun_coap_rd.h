/***************************************************************************//**
 * @file
 * @brief Wi-SUN CoAP resource discovery
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

#ifndef SLI_WISUN_COAP_RD_H_
#define SLI_WISUN_COAP_RD_H_

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "sl_wisun_coap.h"
#include "sl_wisun_coap_rhnd.h"
#include "sl_wisun_coap_config.h"
#include "sli_wisun_coap_rd.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// Resource discovery standard request
#define SLI_WISUN_COAP_RD_CORE_STR       "/.well-known/core"

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Parses the URI path and optional query of the resource discovery
 * @details It parse the incoming CoAP packet considering the URI path and the query.
 * @param[in] resources is the pointer to resources' table.
 * @param[in] packet is the parsed by embedded CoAP packet.
 * @param[out] rd_length is the length of the resource discovery message string.
 * @return string is the response payload of resource discovery.
 * @return NULL if the CoAP message is a resource handling request. (PUT or GET)
 *****************************************************************************/
char *sli_wisun_coap_rd_parser(const sl_wisun_coap_rhnd_resource_t * const resources,
                               const sl_wisun_coap_packet_t * const packet,
                               uint16_t * const rd_length);

/**************************************************************************//**
 * @brief Builds the CoAP packet for resource discovery.
 * @details It builds the packet that contains the resource discovery response
 *          payload and sets other parameters for CoAP.
 * @param[in] payload is the pointer to resource discovery response payload.
 * @param[in] payload_len is length of the payload.
 * @param[in] req_packet is request packet.
 * @return packet is the packet of the CoAP message.
 * @return NULL if an error occurred, otherwise the payload coap packet ptr.
 *****************************************************************************/
sl_wisun_coap_packet_t *sli_wisun_coap_rd_build_response(const char * const payload,
                                                         const uint16_t payload_len,
                                                         const sl_wisun_coap_packet_t * const req_packet);

#ifdef __cplusplus
}
#endif

#endif /* SLI_WISUN_COAP_RD_H_ */

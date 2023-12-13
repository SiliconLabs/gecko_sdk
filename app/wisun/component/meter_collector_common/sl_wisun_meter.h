/***************************************************************************//**
 * @file
 * @brief
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

#ifndef __SL_WISUN_METER_H__
#define __SL_WISUN_METER_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <inttypes.h>
#include "socket/socket.h"
#include "sli_wisun_meter_collector.h"
#include "sl_wisun_meter_collector_config.h"
#include "sl_component_catalog.h"

#if defined(SL_CATALOG_WISUN_COAP_PRESENT)
#include "sl_wisun_coap_config.h"
#endif
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#ifndef SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
#if defined(SL_CATALOG_WISUN_COAP_PRESENT)
  #define SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE !SL_WISUN_COAP_RESOURCE_HND_SERVICE_ENABLE
#else
  #define SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE 1
#endif
#endif

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Generate packet id for packet.
 * @details Weak implementation, user can override it
 * @param[out] packet packet
 *****************************************************************************/
void sl_wisun_meter_gen_packet_id(sl_wisun_meter_packet_t *packet);

/**************************************************************************//**
 * @brief Measure temperature and put it to the packet.
 * @details Weak implementation, user can override it
 * @param[out] packet packet
 *****************************************************************************/
void sl_wisun_meter_get_temperature(sl_wisun_meter_packet_t *packet);

/**************************************************************************//**
 * @brief Measure relative humidity and put it to the packet.
 * @details Weak implementation, user can override it
 * @param[out] packet packet
 *****************************************************************************/
void sl_wisun_meter_get_humidity(sl_wisun_meter_packet_t *packet);

/**************************************************************************//**
 * @brief Measure light and put it to the packet.
 * @details Weak implementation, user can override it
 * @param[out] packet packet
 *****************************************************************************/
void sl_wisun_meter_get_light(sl_wisun_meter_packet_t *packet);

#if SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
/**************************************************************************//**
 * @brief Init meter component.
 * @details Init meter collector common component and RHT measurement
 *****************************************************************************/
void sl_wisun_meter_init(void);

/**************************************************************************//**
 * @brief Init common resources.
 * @details Function should be called in CoAP Meter init
 * @param[in] parser Parser callback
 * @param[in] build Build Callback
 *****************************************************************************/
void sl_wisun_meter_init_common_resources(sl_wisun_meter_parse_t parser,
                                          sl_wisun_meter_build_hnd_t build);

/**************************************************************************//**
 * @brief Register Collector.
 * @details Add collector to the collector storage to handle in measurement loop
 * @param[in] coll_addr meter address structure
 * @return SL_STATUS_OK meter has been successfully added
 * @return SL_STATUS_ALREADY_EXISTS collector had already been added
 * @return SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t sl_wisun_meter_register_collector(const sockaddr_in6_t * const coll_addr);

/**************************************************************************//**
 * @brief Remove Collector.
 * @details Remove registered collector from the registered collector storage
 * @param[in] coll_addr collector address structure
 * @return SL_STATUS_OK collector has been successfully removed
 * @return SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t sl_wisun_meter_remove_collector(const sockaddr_in6_t * const coll_addr);

/**************************************************************************//**
 * @brief Error handler
 * @details Weak implementation, user can override it
 * @param[in] status Return code of the previous function
 * @param[in] socket_id Socket used for data transmission
 * @param[in] storage Pointer to the measurement data storage
 *****************************************************************************/
void sl_wisun_meter_error_handler(const sl_status_t status,
                                  const int32_t socket_id,
                                  sl_wisun_meter_packet_storage_t *storage);

/**************************************************************************//**
 * @brief Meter functional process
 * @details It processes the functionality of meter application.
 *****************************************************************************/
void sl_wisun_meter_process(void);
#endif

#ifdef __cplusplus
}
#endif

#endif

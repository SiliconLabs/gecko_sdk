/***************************************************************************//**
 * @file
 * @brief Wi-SUN CoAP resource handler
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

#ifndef __SL_WISUN_COAP_RHND_H__
#define __SL_WISUN_COAP_RHND_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "sl_status.h"
#include "sl_wisun_coap.h"
#include "sl_wisun_coap_config.h"

/**************************************************************************//**
 * @addtogroup SL_WISUN_COAP_API CoAP
 * @ingroup SL_WISUN_COAP
 * @{
 *****************************************************************************/

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @defgroup SL_WISUN_COAP_RESOURCE_TYPES CoAP type definitions
 * @ingroup SL_WISUN_COAP
 * @{
 *****************************************************************************/

/// Auto-Response callback for resorces
typedef sl_wisun_coap_packet_t * (*sl_wisun_coap_rhnd_auto_resp_t)(const sl_wisun_coap_packet_t * const req_packet);

/// Resource table data
typedef struct sl_wisun_coap_rhnd_resource_data {
  /// resource URI path string
  const char * uri_path;
  /// resource type string
  const char * resource_type;
  /// inteface type string
  const char * interface;
} sl_wisun_coap_rhnd_resource_data_t;

/// Resource table entry
typedef struct sl_wisun_coap_rhnd_resource {
  /// Resource data
  sl_wisun_coap_rhnd_resource_data_t data;
  /// Resource discoverable
  bool discoverable;
  /// Auto response
  sl_wisun_coap_rhnd_auto_resp_t auto_response;
  /// Next pointer
  struct sl_wisun_coap_rhnd_resource * next;
} sl_wisun_coap_rhnd_resource_t;

/** @} (end SL_WISUN_COAP_RESOURCE_TYPES) */

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Initialization of the CoAP Resource Discovery internals.
 *****************************************************************************/
void sl_wisun_coap_rhnd_init(void);

/**************************************************************************//**
 * @brief Register a new resource into the CoAP Resource table
 * @param[in] src_resource the new resource's descriptor
 * @return True if the registration is successful
 *****************************************************************************/
sl_status_t sl_wisun_coap_rhnd_resource_add(const sl_wisun_coap_rhnd_resource_t * const src_resource);

/**************************************************************************//**
 * @brief Remove a resource from the CoAP Resource table referenced by name
 * @param[in] uri_path URI path of the resource to be removed
 * @return True if removal is successful
 *****************************************************************************/
sl_status_t sl_wisun_coap_rhnd_resource_remove_by_uri(const char * uri_path);

/**************************************************************************//**
 * @brief Get resources
 * @details Getting linked list of resources
 * @return const sl_wisun_coap_rhnd_resource_t* Resource list, on error is NULL ptr
 *****************************************************************************/
const sl_wisun_coap_rhnd_resource_t * sl_wisun_coap_rhnd_get_resources(void);

/**************************************************************************//**
 * @brief Set auto-response callback
 * @details Set callback for resource
 * @param[in] uri_path URI path
 * @param[in] response Response callback
 * @return sl_status_t SL_STATUS_OK on succes, SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t sl_wisun_coap_rhnd_set_auto_response(const char*  uri_path,
                                                 sl_wisun_coap_rhnd_auto_resp_t response);

/**************************************************************************//**
 * @brief Reset auto-response callback
 * @details Set callback ptr to NULL in resource descriptor
 * @param[in] uri_path URI path
 * @return sl_status_t SL_STATUS_OK on succes, SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t sl_wisun_coap_rhnd_reset_auto_response(const char * uri_path);

/**************************************************************************//**
 * @brief Print resources
 * @details Print resource URI paths
 *****************************************************************************/
void sl_wisun_coap_rhnd_print_resources(void);

#if SL_WISUN_COAP_RESOURCE_HND_SERVICE_ENABLE

/**************************************************************************//**
 * @brief ACK packet received handler
 * @details Weak function, used in the service
 * @param[in,out] req_packet Request packet
 *****************************************************************************/
void sl_wisun_coap_rhnd_service_resp_received_hnd(sl_wisun_coap_packet_t * req_packet);

/**************************************************************************//**
 * @brief URI path string error handler
 * @details Weak function, used in the service
 * @param[in,out] req_packet Request packet
 *****************************************************************************/
void sl_wisun_coap_rhnd_service_uri_path_error_hnd(sl_wisun_coap_packet_t * req_packet);

/**************************************************************************//**
 * @brief Response message buffer overflow error handler
 * @details Weak function, used in the service
 * @param[in,out] req_packet Request packet
 * @param[in,out] resp_packet Response packet
 *****************************************************************************/
void sl_wisun_coap_rhnd_service_buff_ovflow_error_hnd(sl_wisun_coap_packet_t * req_packet,
                                                      sl_wisun_coap_packet_t * resp_packet);

/**************************************************************************//**
 * @brief Response message build error handler
 * @details Weak function, used in the service
 * @param[in,out] req_packet Request packet
 * @param[in,out] resp_packet Response packet
 *****************************************************************************/
void sl_wisun_coap_rhnd_service_packet_build_error_hnd(sl_wisun_coap_packet_t * req_packet,
                                                       sl_wisun_coap_packet_t * resp_packet);

/**************************************************************************//**
 * @brief Response message senderror handler
 * @details Weak function, used in the service
 * @param[in,out] req_packet Request packet
 * @param[in,out] resp_packet Response packet
 *****************************************************************************/
void sl_wisun_coap_rhnd_service_resp_send_error_hnd(sl_wisun_coap_packet_t * req_packet,
                                                    sl_wisun_coap_packet_t * resp_packet);

#endif
/** @}*/

#ifdef __cplusplus
}
#endif

#endif

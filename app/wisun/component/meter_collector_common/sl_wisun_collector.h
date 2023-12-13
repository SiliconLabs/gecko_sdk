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

#ifndef __SL_WISUN_COLLECTOR_H__
#define __SL_WISUN_COLLECTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "socket/socket.h"
#include "sli_wisun_meter_collector.h"
#include "sl_wisun_collector_config.h"
#include "sl_status.h"

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
 * @brief Gets the socket used by the (CoAP) Collector app
 *****************************************************************************/
int32_t sl_wisun_collector_get_shared_socket(void);

/**************************************************************************//**
 * @brief Init collector component.
 * @details Call the common meter-collector init and set collector callback
 *****************************************************************************/
void sl_wisun_collector_init(void);

/**************************************************************************//**
 * @brief Inherit common handler.
 * @details Function should be called in CoAP Collector init to inherit callbacks
 * @param[in,out] hnd Handler
 *****************************************************************************/
void sl_wisun_collector_inherit_common_hnd(sl_wisun_collector_hnd_t * const hnd);

/**************************************************************************//**
 * @brief Init common resources.
 * @details Function should be called in CoAP Collector init
 *****************************************************************************/
void sl_wisun_collector_init_common_resources(void);

/**************************************************************************//**
 * @brief Register Meter.
 * @details Add meter to the meter storage
 * @param[in] meter_addr meter address structure
 * @return SL_STATUS_OK meter has been successfully added
 * @return SL_STATUS_ALREADY_EXISTS meter had already been added
 * @return SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t sl_wisun_collector_register_meter(const sockaddr_in6_t * const meter_addr);

/**************************************************************************//**
 * @brief Remove Meter.
 * @details Remove registered meter from the registered meter storage
 * @param[in] meter_addr meter address structure
 * @return SL_STATUS_OK meter has been successfully removed
 * @return SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t sl_wisun_collector_remove_meter(const sockaddr_in6_t * const meter_addr);

/**************************************************************************//**
 * @brief Send async request.
 * @details Send async request to the given Meter
 * @param[in] meter_addr meter address structure
 * @return SL_STATUS_OK async request has been successfully sent
 * @return SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t sl_wisun_send_async_request(const sockaddr_in6_t * const meter_addr);

/**************************************************************************//**
* @brief Set async measurement request.
* @details This request is sent to get
*          measurement data from the meter
* @param[in] req  Measurement request
******************************************************************************/
void sl_wisun_collector_set_async_measurement_request(const sl_wisun_meter_request_t * const req);

/**************************************************************************//**
* @brief Set registration request.
* @details This request is sent to register the collector to a meter
* @param[in] req  Registration request
******************************************************************************/
void sl_wisun_collector_set_registration_request(const sl_wisun_meter_request_t * const req);

/**************************************************************************//**
* @brief Set remove request.
* @details This request is sent to remove the collector from a meter
* @param[in] req  Registration request
******************************************************************************/
void sl_wisun_collector_set_removal_request(const sl_wisun_meter_request_t * const req);

/**************************************************************************//**
 * @brief Print Meters.
 * @details Print registered and async meters
 *****************************************************************************/
void sl_wisun_collector_print_meters(void);

/**************************************************************************//**
 * @brief Get async meter by address.
 * @details Returns a pointer to the meter entry with the given address
 * @param[in] meter_addr meter address structure
 * @return Pointer to the meter entry with the given address
 *****************************************************************************/
sl_wisun_meter_entry_t *sl_wisun_collector_get_async_meter_entry_by_address(const sockaddr_in6_t * const meter_addr);

/**************************************************************************//**
 * @brief Get registered meter by address.
 * @details Returns a pointer to the meter entry with the given address
 * @param[in] meter_addr meter address structure
 * @return Pointer to the meter entry with the given address
 *****************************************************************************/
sl_wisun_meter_entry_t *sl_wisun_collector_get_registered_meter_entry_by_address(const sockaddr_in6_t * const meter_addr);

/**************************************************************************//**
 * @brief Get Meter by address.
 * @details Returns a pointer to the meter entry with the given address
 * @param[in] meter_addr meter address structure
 * @return Pointer to the meter entry with the given address
 *****************************************************************************/
sl_wisun_meter_entry_t *sl_wisun_collector_get_meter(const sockaddr_in6_t * const meter_addr);

/**************************************************************************//**
 * @brief Collector send request
 * @details Collector send request
 * @param[in] sockid The socket used for sending
 * @param[in] addr Meter address
 * @param[in] req The request to send
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
sl_status_t sl_wisun_collector_send_request(const int32_t sockid,
                                            const sockaddr_in6_t *addr,
                                            const sl_wisun_meter_request_t * const req);
#ifdef __cplusplus
}
#endif

#endif

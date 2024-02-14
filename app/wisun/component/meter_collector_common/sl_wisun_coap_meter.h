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
#ifndef __SL_WISUN_COAP_METER_H__
#define __SL_WISUN_COAP_METER_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "sl_wisun_app_core.h"
#include "sl_wisun_coap.h"
#include "sli_wisun_meter_collector.h"
#include "sl_wisun_meter.h"
#include "sl_wisun_coap_meter_collector_config.h"


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
 * @brief Init CoAP meter component.
 * @details Init common collector meter component and rht measurement
 *****************************************************************************/
void sl_wisun_coap_meter_init(void);

#if !SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
/**************************************************************************//**
 * @brief Prepare measurement response packet from all sensor values
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t *sl_wisun_coap_meter_measurement_response_cb(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Prepare Temperature measurement response packet
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t *sl_wisun_coap_meter_temperature_response_cb(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Prepare Humidity measurement response packet
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t *sl_wisun_coap_meter_humidity_response_cb(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Prepare Light measurement response packet
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t *sl_wisun_coap_meter_light_response_cb(const sl_wisun_coap_packet_t * const req_packet);

#if !defined(SL_CATALOG_POWER_MANAGER_PRESENT)
/**************************************************************************//**
 * @brief Prepare measurement response packet
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t *sl_wisun_coap_meter_led_toggle_response_cb(const sl_wisun_coap_packet_t * const req_packet);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

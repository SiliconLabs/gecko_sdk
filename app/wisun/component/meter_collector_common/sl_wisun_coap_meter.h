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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "sl_wisun_app_core.h"
#include "sl_wisun_coap.h"
#include "sli_wisun_meter_collector.h"
#include "sl_wisun_meter.h"
#include "sl_wisun_coap_meter_collector_config.h"
#include "sl_wisun_led_driver.h"

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

/**************************************************************************//**
 * @brief Prepare measurement response packet from all sensor values
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @param[out] resp_packet Response packet
 *****************************************************************************/
void sl_wisun_coap_meter_measurement_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                                 sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief Prepare Temperature measurement response packet
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @param[out] resp_packet Response packet
 *****************************************************************************/
void sl_wisun_coap_meter_temperature_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                                 sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief Prepare Humidity measurement response packet
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @param[out] resp_packet Response packet
 *****************************************************************************/
void sl_wisun_coap_meter_humidity_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                              sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief Prepare Light measurement response packet
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @param[out] resp_packet Response packet
 *****************************************************************************/
void sl_wisun_coap_meter_light_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                           sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief Prepare measurement response packet
 * @details Callback for CoAP Resource Handler Service. It should be registered.
 * @param[in] req_packet Request packet
 * @param[out] resp_packet Response packet
 *****************************************************************************/
void sl_wisun_coap_meter_led_toggle_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                                sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief Convert LED ID.
 * @details Helper function to convert uint8_t LED ID to sl_wisun_led_id_t
 * @param[in] led_id LED ID raw value
 * @return sl_wisun_led_id_t converted LED ID
 *****************************************************************************/
sl_wisun_led_id_t sl_wisun_coap_meter_convert_led_id(const uint8_t led_id);

#endif

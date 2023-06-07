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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <inttypes.h>
#include "socket.h"
#include "sli_wisun_meter_collector.h"
#include "sl_wisun_meter_collector_config.h"
#include "sl_component_catalog.h"
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
 * @brief Init meter component.
 * @details Init meter collector common component and RHT measurement
 *****************************************************************************/
void sl_wisun_meter_init(void);

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

#if !defined(SL_CATALOG_WISUN_COAP_PRESENT)
/**************************************************************************//**
 * @brief Meter functional process
 * @details It processes the functionality of meter application.
 *****************************************************************************/
void sl_wisun_meter_process(void);
#endif
#endif

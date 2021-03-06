/***************************************************************************//**
 * @file
 * @brief Application init
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

#ifndef APP_INIT_H
#define APP_INIT_H

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// common interface and resource type definitions for use with resources
#define SL_WISUN_COAP_METER_RESOURCE_RT_TEMP            "sensor"
#define SL_WISUN_COAP_METER_RESOURCE_IF_TEMP_SENSOR     "tempsensor"
#define SL_WISUN_COAP_METER_RESOURCE_RT_LED             "led"
#define SL_WISUN_COAP_METER_RESOURCE_IF_LED             "toggle"

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------
/**************************************************************************//**
 * @brief Application init
 * @details This function initializes the application tasks, mutexes and
 *          register the custom callbacks
 *****************************************************************************/
void app_init(void);

#endif // APP_INIT_H

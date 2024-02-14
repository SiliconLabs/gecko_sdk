/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Status CoAP notfication
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

#ifndef __SL_WISUN_APP_STATUS_H__
#define __SL_WISUN_APP_STATUS_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include "sl_status.h"
#include "sl_wisun_coap_notify.h"
#include "socket.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Init Application Status notification content
 * @details Init notification content and callbacks.
 *****************************************************************************/
void sl_wisun_app_status_init(void);

/**************************************************************************//**
 * @brief Application Status notification callback
 * @details The function provides an implementable callback to create custom
 *          condition check to send notification. It's a weak implementation,
 *          by default it returns true always.
 * @param notify Notification context.
 * @return bool The result of the condition check.
 *****************************************************************************/
bool sl_wisun_app_status_condition_cb(const sl_wisun_coap_notify_t * notify);

/**************************************************************************//**
 * @brief Application Status notification remote address and port getter
 * @details The function provides a getter function for the address and port
 *          parameters that are static for the file
 * @return sockaddr_in6_t The pointer to the address setting structure
 *****************************************************************************/
sockaddr_in6_t* sl_wisun_app_status_get_remote_address(void);

/**************************************************************************//**
 * @brief Application Status notification schedule time getter
 * @details The function provides a getter function for the schedule time
 *          parameters that are static for the file
 * @return uint32_t The schedule time in ms
 *****************************************************************************/
uint32_t sl_wisun_app_status_get_schedule_time_ms(void);

/**************************************************************************//**
 * @brief Application Status notification remote address and port setter
 * @details The function provides a setter function for the address and port
 *          parameters that are static for the file
 * @param remote_address remote address to be selected
 * @param port remote port to be selected
 * @return sl_status_t SL_STATUS_OK if setting was success or the proper
 *                     sl_status enum of the error
 *****************************************************************************/
sl_status_t sl_wisun_app_status_set_remote_address(const char *remote_address, const uint16_t port);

/**************************************************************************//**
 * @brief Application Status notification schedule time setter
 * @details The function provides a setter function for the schedule time
 *          parameters that are static for the file
 * @param new_schedule_time_ms The schedule time in ms
 *****************************************************************************/
void sl_wisun_app_status_set_schedule_time_ms(const uint32_t new_schedule_time_ms);

#ifdef __cplusplus
}
#endif

#endif

/***************************************************************************//**
 * @file
 * @brief Wi-SUN CoAP notfication service
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

#ifndef __SL_WISUN_COAP_NOTIFY_H__
#define __SL_WISUN_COAP_NOTIFY_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

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

/**************************************************************************//**
 * @defgroup SL_WISUN_COAP_NOTIFICATION_TYPES CoAP Notification type definitions
 * @ingroup SL_WISUN_COAP
 * @{
 *****************************************************************************/

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// CoAP Notify type definition
typedef struct sl_wisun_coap_notify {
  /// ID string
  const char *id;
  /// Remote address
  sockaddr_in6_t remote_addr;
  /// Packet handler callback,
  /// it returns with the built CoAP packet
  sl_wisun_coap_packet_t * (*hnd_cb)(const struct sl_wisun_coap_notify *notify);
  /// Condition check callback,
  /// it returns with the result of send condition (true: send, false: not send)
  bool (* condition_cb)(const struct sl_wisun_coap_notify *notify);
  /// Schedule time (ms)
  uint32_t schedule_time_ms;
  /// Tick counter (ms)
  uint32_t tick_ms;
} sl_wisun_coap_notify_t;

/** @} (end SL_WISUN_COAP_NOTIFICATION_TYPES) */

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Initialization of the CoAP notification service.
 * @details If the service is enabled, the notification thread is
 *          initialized also.
 *****************************************************************************/
void sl_wisun_coap_notify_init(void);

/**************************************************************************//**
 * @brief Init default notification instance.
 * @details Default remote address and port are defined in the config file.
 * @param[in] notify notify descriptor for init
 * @param[in] id unique ID of the notification (custom string)
 * @return sl_status_t SL_STATUS_OK if the initialization is succeeded,
 *         otherwise SL_STATUS_FAIL
 *****************************************************************************/
sl_status_t sl_wisun_coap_notify_init_default_inst(sl_wisun_coap_notify_t * const notify,
                                                   const char *id);

/**************************************************************************//**
 * @brief Register a new notification.
 * @details Notification is added to the internal storage.
 * @param[in] src_notify the new notifcation's descriptor to add
 * @return sl_status_t SL_STATUS_OK if the notification is added successfully,
 *         otherwise SL_STATUS_FAIL
 *****************************************************************************/
sl_status_t sl_wisun_coap_notify_add(const sl_wisun_coap_notify_t * const src_notify);

/**************************************************************************//**
 * @brief Get notification by ID.
 * @details Get pointer to the notification instance in the storage.
 * @param[in] id unique ID of the notification (custom string)
 * @return sl_wisun_coap_notify_t * pointer to notify instance
 *         if succeeded, otherwise NULL ptr
 *****************************************************************************/
const sl_wisun_coap_notify_t *sl_wisun_coap_notify_get_by_id(const char* id);

/**************************************************************************//**
 * @brief Remove notification from the CoAP notification table referenced by name.
 * @details Remove notification from the internal storage.
 * @param[in] id Notification ID
 * @return sl_status_t SL_STATUS_OK if the notification is removed successfully,
 *         otherwise SL_STATUS_FAIL
 *****************************************************************************/
sl_status_t sl_wisun_coap_notify_remove_by_id(const char * id);

/**************************************************************************//**
 * @brief Print notifications.
 * @details Print content of the internal storage.
 * @details Print resource URI paths
 *****************************************************************************/
void sl_wisun_coap_notify_print_notifications(void);

/**************************************************************************//**
 * @brief Send notification.
 * @details Notification should be initialised properly before sending.
 * @param[in] notify Notification instance.
 *            It includes all the necessary information about destination.
 * @return sl_status_t SL_STATUS_OK if the notification is sent successfully,
 *         otherwise SL_STATUS_FAIL
 *****************************************************************************/
sl_status_t sl_wisun_coap_notify_send_notification(const sl_wisun_coap_notify_t * const notify);

#if SL_WISUN_COAP_NOTIFY_SERVICE_ENABLE
/**************************************************************************//**
 * @brief Error handler if the notification is failed
 * @details Weak implementation, it can be implemented by the User.
 *          Default implementation is printing the notification which was failed.
 * @param[in] notify Notification instance.
 *            It includes all the necessary information about destination.
 *****************************************************************************/
void sl_wisun_coap_notify_error_hnd(const sl_wisun_coap_notify_t * const notify);
#endif

/** @}*/

#ifdef __cplusplus
}
#endif

#endif

/***************************************************************************//**
 * @file
 * @brief Low Power Node feature header
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_LPN_H
#define SL_BTMESH_LPN_H

#include "sl_btmesh_api.h"

/***************************************************************************//**
 * @defgroup lpn Low Power Node Component
 * @brief Low Power Node feature Implementation
 * This component implements Low Power Node feature.
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup lpn
 * @{
 ******************************************************************************/

/// Operational modes for the high throughput timer
typedef enum {
  /// Normal, periodic operation with the provided value
  SL_BTMESH_LPN_HIGH_THROUGHPUT_NORMAL,
  /// Slows down over time, doubling its timeout after every expiration
  SL_BTMESH_LPN_HIGH_THROUGHPUT_SLOWING
} sl_btmesh_lpn_high_throughput_operation_mode_t;

/// Handler structure for the high throughput timer
typedef struct sl_btmesh_lpn_high_throughput_timer_s {
  /// The timeout in milliseconds
  uint32_t timeout;
  /// The operational mode
  sl_btmesh_lpn_high_throughput_operation_mode_t mode;
  /// Pointer to the next registered handler
  struct sl_btmesh_lpn_high_throughput_timer_s *next;
} sl_btmesh_lpn_high_throughput_timer_t;
/***************************************************************************//**
 * Initialize LPN functionality. This function is called automatically by the
 * LPN component.
 *
 ******************************************************************************/
void sl_btmesh_lpn_feature_init(void);

/***************************************************************************//**
 * Deinitialize LPN functionality. This function is called automatically by the
 * LPN component.
 ******************************************************************************/
void sl_btmesh_lpn_feature_deinit(void);

/***************************************************************************//**
 * Return if the friendship is active between LPN and friend node
 *
 * @return Friendship active state
 * @retval true If friendship is active with a friend node
 * @retval false If friendship is not established with any friend node
 ******************************************************************************/
bool sl_btmesh_lpn_is_friendship_active(void);

/***************************************************************************//**
 * Poll the Friend node for stored messages and security updates
 *
 * This command may be used if the application is expecting to receive messages
 * at a specific time. However, it is not required for correct operation,
 * because the procedure will be performed autonomously before the poll timeout
 * expires.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_btmesh_lpn_poll_request(void);

/***************************************************************************//**
 *  Handling of mesh lpn events.
 *
 *  @param[in] pEvt  Pointer to incoming lpn event.
 ******************************************************************************/
void sl_btmesh_lpn_on_event(sl_btmesh_msg_t *pEvt);

/***************************************************************************//**
 * Registers high throughput request
 *
 * @param[in] handle Pointer to the handler of the high throughput timer
 *                   structure, provided by the user
 * @param[in] timeout The timeout of this timer, in milliseconds
 * @param[in] mode The mode of operation
 *
 * @return Status code
 * @retval SL_STATUS_OK Timer successfully registered
 * @retval SL_STATUS_ALREADY_EXISTS Timer is already present, list unchanged
 ******************************************************************************/
sl_status_t sl_btmesh_lpn_high_throughput_register(sl_btmesh_lpn_high_throughput_timer_t *handle,
                                                   uint32_t timeout,
                                                   sl_btmesh_lpn_high_throughput_operation_mode_t mode);

/***************************************************************************//**
 * Unregisters high throughput request
 *
 * @note Will not stop the already running timer if it belongs to the handler
 *       passed.
 *
 * @param[in] handle Pointer to the handler to be unregistered
 *
 * @return Status code
 * @retval SL_STATUS_OK Timer successfully unregistered
 * @retval SL_STATUS_ALREADY_EXISTS Timer was not present in the list
 ******************************************************************************/
sl_status_t sl_btmesh_lpn_high_throughput_unregister(sl_btmesh_lpn_high_throughput_timer_t *handle);

/***************************************************************************//**
 * Called when the Low Power Node is initialized.
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 ******************************************************************************/
void sl_btmesh_lpn_on_init(void);

/***************************************************************************//**
 * Called when the Low Power Node is deinitialized.
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 ******************************************************************************/
void sl_btmesh_lpn_on_deinit(void);

/***************************************************************************//**
 * Called when the Low Power Node establishes friendship with another node
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] friend_address Node address of the new friend
 ******************************************************************************/
void sl_btmesh_lpn_on_friendship_established(uint16_t friend_address);

/***************************************************************************//**
 * Called when the friendship establishment attempt of Low Power Node fails
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] reason Reason for friendship establishment failure
 ******************************************************************************/
void sl_btmesh_lpn_on_friendship_failed(uint16_t reason);

/***************************************************************************//**
 * Called when friendship that was successfully established has been terminated
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] reason Reason for friendship termination
 ******************************************************************************/
void sl_btmesh_lpn_on_friendship_terminated(uint16_t reason);

/** @} (end addtogroup lpn) */

#endif /* SL_BTMESH_LPN_H */

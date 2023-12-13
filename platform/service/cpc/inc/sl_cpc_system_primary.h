/***************************************************************************/ /**
 * @file
 * @brief CPC system endpoint primary part
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_CPC_SYSTEM_PRIMARY_H
#define SL_CPC_SYSTEM_PRIMARY_H

#include "sl_status.h"
#include "sli_cpc_system_common.h"
#include "sli_cpc_timer.h"
#include "sl_slist.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************/ /**
 * @addtogroup cpc_system_primary
 * @brief CPC System Endpoint Primary
 * @details
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief Structure to store a callback to be called when the secondary resets
 ******************************************************************************/
typedef struct {
  sl_slist_node_t node;
  void (*on_reset_callback)(sl_cpc_system_status_t reset_reason);
} sl_cpc_system_event_listener_t;

/***************************************************************************//**
 * Callback for when receiving an unsolicited PROP_LAST_STATUS.
 *
 * This is a weak stub meant to be re-implemented as a strong function by the
 * user in order to act upon unsolicited PROP_LAST_STATUS.
 *
 * @note
 *   When the PRIMARY issues a property-get/set command, the SECONDARY responds
 *   with the value requested. Upon receiving this reply, the PRIMARY executes
 *   the callback that was registered when issuing the command. If the PRIMARY
 *   receives a PROPERTY-IS command with PROP_LAST_STATUS property when no
 *   callback is registered (ie, the PRIMARY didn't asked anything), then this
 *   callback type will be called if registered.
 *
 * @param
 *   [in] status
 *     The unsolicited PROP_LAST_STATUS value.
 *
 ******************************************************************************/
SL_WEAK void sl_cpc_system_unsolicited_last_status_callback(sl_cpc_system_status_t status);

/***************************************************************************//**
 * Initialize an event listener
 *
 * @param
 *   [in] listener
 ******************************************************************************/
void sl_cpc_system_event_listener_init(sl_cpc_system_event_listener_t *listener);

/***************************************************************************//**
 * Add an event listener that will be called when the secondary events occur.
 *
 * @param
 *   [in] listener
 ******************************************************************************/
sl_status_t sl_cpc_system_event_listener_subscribe(sl_cpc_system_event_listener_t *listener);

/***************************************************************************//**
 * Remove an event listener that was previously added.
 *
 * @param
 *   [in] listener
 ******************************************************************************/
sl_status_t sl_cpc_system_event_listener_unsubscribe(sl_cpc_system_event_listener_t *listener);

/** @} (end addtogroup cpc_system_primary) */

#ifdef __cplusplus
}
#endif

#endif /* SL_CPC_SYSTEM_PRIMARY_H_ */

/***************************************************************************//**
 * @file
 * @brief ABR reflector connection manager
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

#ifndef ABR_REFLECTOR_CONNMANAGER_H
#define ABR_REFLECTOR_CONNMANAGER_H

// 'rcm' stands for 'reflector connection manager'

#include "sl_common.h"
#include "abr_reflector_config.h"

// Connection context
typedef struct {
  uint8_t conn_handle;                            // Handle of the connection uniquely identifying it
  bool in_use;                                    // Shows whether the slot is in use or it can be overwritten
  bool ras_control_point_indication_enabled;      // Shows whether the initiator has enabled notifications for the RAS control point
  bool ras_periodic_notification_mode_enabled;    // Shows whether the initiator has enabled the periodic notification mode
  bool indication_in_progress;                    // Shows whether we have an indication sent for which we haven't received a confirmation
  uint16_t current_cs_subevent_index;             // The subevent index associated with the ongoing CS measurement
  uint16_t current_procedure_index;               // The procedure index associated with the ongoing CS measurement
} connection_ctx_t;

/**************************************************************************//**
 * Find the pointer to a connection context which belongs to the
 * provided connection handle.
 *
 * @param[in] conn_handle the connection handle to search for
 *
 * @return the pointer of the context corresponding to the provided
 *         connection handle, NULL if not found
 *****************************************************************************/
connection_ctx_t *abr_rcm_get_connection_ctx(const uint8_t conn_handle);

/**************************************************************************//**
 * Register a new initiator connection with the provided handle.
 *
 * @param[in] conn_handle the connection handle to register
 *
 * @return true if registration was successful, false otherwise
 *****************************************************************************/
bool abr_rcm_add_new_initiator_connection(const uint8_t conn_handle);

/**************************************************************************//**
 * Remove an initiator connection with the provided handle.
 *
 * @param[in] conn_handle the connection handle to remove
 *
 * @return true if removal was successful, false otherwise
 *****************************************************************************/
void abr_rcm_remove_initiator_connection(const uint8_t conn_handle);

/**************************************************************************//**
 * Tell whether an additional connection can be accepted.
 *
 * @return true if an additional connection can be accepted, false otherwise
 *****************************************************************************/
bool abr_rcm_can_accept_new_connection(void);

/**************************************************************************//**
 * Show the number of active connections.
 *
 * @return the number of active connections
 *****************************************************************************/
uint32_t abr_rcm_get_number_of_connections(void);

#endif // ABR_REFLECTOR_CONNMANAGER_H

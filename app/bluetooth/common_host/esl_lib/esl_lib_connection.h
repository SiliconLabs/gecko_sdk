/***************************************************************************//**
 * @file
 * @brief ESL Access Point Connection header.
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

#ifndef ESL_LIB_CONNECTION_H
#define ESL_LIB_CONNECTION_H

#include <stdint.h>
#include <stdbool.h>
#include "sl_status.h"
#include "sl_bt_api.h"
#include "esl_lib.h"
#include "esl_lib_image_transfer.h"
#include "esl_lib_command_list.h"
#include "app_timer.h"
#include "esl_lib_storage.h"
#include "esl_lib_log.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Definitions

#define ESL_LIB_CONNECTION_RETRY_COUNT_MAX          3

/// Tag info storage type
typedef struct {
  sl_slist_node_t          node;    ///< Node for the list
  esl_lib_data_type_t      type;    ///< Type of the data
  esl_lib_storage_handle_t storage; ///< Data storage
} esl_lib_connection_tag_info_storage_t;

/// Connection list item type
typedef struct {
  sl_slist_node_t                 node;              ///< List node pointer
  esl_lib_command_list_cmd_t      *command;          ///< Command in progress
  sl_slist_node_t                 *command_list;     ///< Command list
  sl_slist_node_t                 *tag_info_list;    ///< Tag info storage list
  bool                            command_complete;  ///< Finished command
  uint8_t                         connection_handle; ///< Connection handle
  uint8_t                         address_type;      ///< Address type
  uint8_t                         max_payload;       ///< Max payload
  uint8_t                         security;          ///< Security level
  uint8_t                         config_index;      ///< Current config index
  esl_lib_connection_state_t      state;             ///< State of the connection
  esl_lib_image_transfer_handle_t ots_handle;        ///< OTS handle
  aes_key_128                     ltk;               ///< LTK for the connection
  bd_addr                         address;           ///< Address
  app_timer_t                     timer;             ///< Connection timer
  app_timer_t                     gatt_timer;        ///< GATT timer
  sl_status_t                     last_error;        ///< Last error
  esl_lib_bool_t                  gattdb_known;      ///< Predefined GATT database
  esl_lib_gattdb_handles_t        gattdb_handles;    ///< List of UUIDs
  esl_lib_data_type_t             tag_info_type;     ///< Current tag info type
  esl_lib_storage_handle_t        tag_info_data;     ///< Current tag info data
  esl_lib_data_type_t             config_type;       ///< Current config type
} esl_lib_connection_t;

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * Add a connection to the list.
 * @param[in]  conn    Connection handle.
 * @param[out] ptr_out Pointer output.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_connection_add(uint8_t              conn,
                                   esl_lib_connection_t **ptr_out);

/**************************************************************************//**
 * Find a connection in the list.
 * @param[in]  conn    Connection handle.
 * @param[out] ptr_out Pointer output.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_connection_find(uint8_t              conn,
                                    esl_lib_connection_t **ptr_out);

/**************************************************************************//**
 * Remove a connection from the list.
 * @param[in] ptr Connection pointer.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_connection_remove_ptr(esl_lib_connection_t *ptr);

/**************************************************************************//**
 * Check connection list for the given item.
 * @param[in] ptr Pointer to the connection list item.
 *
 * @return true if the list contains the item.
 *****************************************************************************/
bool esl_lib_connection_contains(esl_lib_connection_t *ptr);

/**************************************************************************//**
 * Clean all relationship data.
 *****************************************************************************/
void esl_lib_connection_cleanup(void);

/**************************************************************************//**
 * Add a command to the command list of the connection.
 *
 * @param[in] conn Pointer to the connection list item.
 * @param[in] cmd  Pointer to the command to add.
 *
 * @return true if the list contains the item.
 *****************************************************************************/
sl_status_t esl_lib_connection_add_command(esl_lib_connection_t       *conn,
                                           esl_lib_command_list_cmd_t *cmd);

/**************************************************************************//**
 * Connection step.
 *****************************************************************************/
void esl_lib_connection_step(void);

/**************************************************************************//**
 * Bluetooth event handler.
 *
 * @param[in] evt Bluetooth event.
 *
 *****************************************************************************/
void esl_lib_connection_on_bt_event(sl_bt_msg_t *evt);

/**************************************************************************//**
 * Check for the validity of the GATT database handles.
 *
 * @param[in] conn Pointer to the GATT database handles.
 *
 * @return SL_STATUS_OK if the configuration is valid.
 *****************************************************************************/
sl_status_t esl_lib_connection_check_gattdb_handles(esl_lib_gattdb_handles_t *gattdb_handles);

/**************************************************************************//**
 * Open a connection.
 *
 * @param[in] cmd    Connection open library command.
 * @param[in] handle Valid connection handle in case of retry or
 *                   NULL for new connection requests.
 *
 * @return SL_STATUS_OK if the configuration is valid.
 *****************************************************************************/
sl_status_t esl_lib_connection_open(esl_lib_command_list_cmd_t *cmd);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_CONNECTION_H

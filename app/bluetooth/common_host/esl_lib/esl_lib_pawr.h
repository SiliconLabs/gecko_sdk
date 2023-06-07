/***************************************************************************//**
 * @file
 * @brief ESL Access Point PAwR header.
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

#ifndef ESL_LIB_PAWR_H
#define ESL_LIB_PAWR_H

#include <stdint.h>
#include <stdbool.h>
#include "sl_status.h"
#include "sl_bt_api.h"
#include "esl_lib.h"
#include "esl_lib_image_transfer.h"
#include "esl_lib_command_list.h"
#include "esl_lib_storage.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Definitions

/// PAwR list item type
typedef struct {
  sl_slist_node_t            node;             ///< List node pointer
  esl_lib_pawr_state_t       state;            ///< PAwR state
  esl_lib_command_list_cmd_t *command;         ///< Command in progress
  bool                       command_complete; ///< Finished command
  sl_slist_node_t            *command_list;    ///< Command list
  uint8_t                    pawr_handle;      ///< PAwR handle
  esl_lib_storage_handle_t   storage_handle;   ///< Storage handle
  esl_lib_bool_t             enabled;          ///< Enabled or disabled
  esl_lib_bool_t             configured;       ///< Configuration state
  esl_lib_pawr_config_t      config;           ///< Configuration
} esl_lib_pawr_t;

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * Add new PAwR to the list.
 * @param[out] ptr_out Pointer output.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_pawr_add(esl_lib_pawr_t **ptr_out);

/**************************************************************************//**
 * Find PAwR in the list.
 * @param[in]  pawr    PAwR handle.
 * @param[out] ptr_out Pointer output.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_pawr_find(uint8_t        pawr,
                              esl_lib_pawr_t **ptr_out);

/**************************************************************************//**
 * Remove PAwR from the list.
 * @param[in]  pawr    PAwR handle.
 * @param[out] ptr_out Pointer output.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_pawr_remove_handle(uint8_t        pawr,
                                       esl_lib_pawr_t **ptr_out);

/**************************************************************************//**
 * Remove PAwR from the list by its pointer.
 * @param[in] ptr Pointer to the PAwR list item.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_pawr_remove_ptr(esl_lib_pawr_t *ptr);

/**************************************************************************//**
 * Check PAwR list for the given item.
 * @param[in] ptr Pointer to the PAwR list item.
 *
 * @return true if the list contains the item.
 *****************************************************************************/
bool esl_lib_pawr_contains(esl_lib_pawr_t *ptr);

/**************************************************************************//**
 * Clean all relationship data.
 *****************************************************************************/
void esl_lib_pawr_cleanup(void);

/**************************************************************************//**
 * Add a command to the command list of the PAwR.
 * @param[in] pawr Pointer to the PAwR list item.
 * @param[in] cmd  Pointer to the command to add.
 *
 * @return true if the list contains the item.
 *****************************************************************************/
sl_status_t esl_lib_pawr_add_command(esl_lib_pawr_t             *pawr,
                                     esl_lib_command_list_cmd_t *cmd);

/**************************************************************************//**
 * PAwR step.
 *****************************************************************************/
void esl_lib_pawr_step(void);

/**************************************************************************//**
 * Bluetooth event handler.
 *
 * @param[in] evt Bluetooth event.
 *
 *****************************************************************************/
void esl_lib_pawr_on_bt_event(sl_bt_msg_t *evt);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_PAWR_H

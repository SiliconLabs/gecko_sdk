/***************************************************************************//**
 * @file
 * @brief Definitions for FW Update Server application level functionality
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

#ifndef DFU_H
#define DFU_H

#include "sl_status.h"

// User sub-command to write FW URI
#define USER_SUB_CMD_URI_ID_WRT '0'
// User sub-command to append to FW URI
#define USER_SUB_CMD_URI_ID_APP '1'

/***************************************************************************//**
 * Sets the Firmware ID for the given index, as part of the FW information
 *
 * @param idx Index of the FW
 * @param len Length of the data
 * @param data Firmware ID data; containing CID and version information
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_INVALID_PARAMETER If length is less than 2 or greater
                                       than 108
 * @retval SL_STATUS_NO_MORE_RESOURCE In case memory allocation error
 ******************************************************************************/
sl_status_t sl_btmesh_ncp_dfu_set_fwid(uint8_t idx, uint8_t len, uint8_t *data);

/***************************************************************************//**
 * Sets the URI for given index, as part of the FW information
 *
 * @param idx Index of the FW
 * @param type Type of the command; '0' erases and writes new URI,
 *             '1' appends to existing URI.
 * @param len Length of the data
 * @param data The data to write or append
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NO_MORE_RESOURCE In case of memory allocation error
 * @retval SL_STATUS_INVALID_PARAMETER In case the combined length of the URI
 *                                     is longer than 255 bytes
 ******************************************************************************/
sl_status_t sl_btmesh_ncp_dfu_set_uri(uint8_t idx,
                                      uint8_t type,
                                      uint8_t len,
                                      uint8_t *data);
/**************************************************************************//**
 * User command (message_to_target) handler callback.
 * Handles user defined commands received from NCP host.
 *
 * @param[in] cmd  Pointer to the command.
 * @param[inout] cmd_handled  Status of tehe command:
 *                            true - cmd handled, no further interpretation is required
 *                            false - cmd unhandled, interpretation is required
 * @note If the value of the parameter 'cmd_handled' is false, the incoming
 *       command needs to be interpreted. If the command is recognized and
 *       handled, the 'cmd_handled' flag should be set to true. If the value of
 *       the 'cmd_handled' parameter is already true, the function will return
 *       without executing any further operations.
 *****************************************************************************/
void sl_btmesh_ncp_dfu_handle_cmd(void *data, bool *cmd_handled);
#endif // DFU_H

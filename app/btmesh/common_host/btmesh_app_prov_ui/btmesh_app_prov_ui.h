/**************************************************************************//**
 * @file
 * @brief BT Mesh Host Provisioner Example Project.
 ******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/

#ifndef BTMESH_APP_PROV_UI_H
#define BTMESH_APP_PROV_UI_H

#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EXIT_COMMAND            'q'
#define SCAN_COMMAND            's'
#define PROVISION_COMMAND       'p'
#define NODELIST_COMMAND        'l'
#define NODEINFO_COMMAND        'i'
#define REMOVE_NODE_COMMAND     'r'
#define KEY_REFRESH_COMMAND     'k'
#define KEY_EXPORT_COMMAND      'x'
#define RESET_COMMAND           'e'

#ifndef SL_CATALOG_APP_REMOTE_PROV_PRESENT
#define PROV_UI_MENU                                        \
  "Please select a functionality\n\n"                       \
  "s - Scan available nodes\n"                              \
  "p - Provision a beaconing node\n"                        \
  "l - List nodes in the network\n"                         \
  "i - Information about a node in the network\n"           \
  "r - Remove node from the network\n"                      \
  "k - Refresh the network key and app key\n"               \
  "x - Export the network keys, app keys and device keys\n" \
  "e - Reset provisioner node and exit application\n"       \
  "q - Exit application\n\n"
#endif

/// UI state
typedef enum ui_state_e{
  UI_MENU,
  UI_WAITING_FOR_CMD,
  UI_CMD_PROCESSING,
  UI_WAITING_FOR_INPUT,
  UI_EXIT
} sl_ui_state;

/**************************************************************************//**
 * Remote provisioning related command handler
 *
 * @param[in] cmd_id Command id
 * @retval SL_STATUS_NOT_FOUND for unknown command id
 *         SL_STATUS_OK for handled command id
 *****************************************************************************/
sl_status_t btmesh_app_prov_ui_handle_remote_prov_cmd(char cmd_id);

/**************************************************************************//**
 * Get UI state
 *
 * @retval Current state of the ui (sl_ui_state)
 *****************************************************************************/
sl_ui_state btmesh_app_prov_ui_get_ui_state(void);

/**************************************************************************//**
 * Get buffer with input console content
 *
 * @param[out] ui_input_buffer data read from input console
 * @retval Current state of the ui
 * @retval false if buffer is empty or content is invalid
 *         true if buffer content vas updated with is valid data
 *****************************************************************************/
bool btmesh_app_prov_ui_get_input_buffer(char **ui_input_buffer);

#ifdef __cplusplus
};
#endif

#endif // BTMESH_APP_PROV_UI_H

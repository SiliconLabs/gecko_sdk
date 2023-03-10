/**************************************************************************//**
 * @file
 * @brief BT Mesh Provisioner Application component - CLI handler
 ******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef BTMESH_APP_PROV_H
#define BTMESH_APP_PROV_H

#include <stdint.h>
#include <getopt.h>
#include "sl_status.h"
#include "sl_btmesh_api.h"
#include "app.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Optstring argument for getopt
#define PROV_OPTLENGTH                8

/// NCP node address
#define BTMESH_APP_PROV_NCP_ADDRESS   0x2001

/// Array terminate element length
#define LAST_OPTION_ELEMENT           1

/// Optstring argument for getopt
#define PROV_OPTSTRING                "ei:lp:k:x:r:s"

/// Usage info
#define PROV_USAGE             \
  " [--nodeinfo <UUID>]"       \
  " [--nodelist]"              \
  " [--provision <UUID>]"      \
  " [--remove <UUID>]"         \
  " [--key-refresh <timeout>]" \
  " [--key-export <filename>]" \
  " [--reset]"                 \
  " [--scan]"

// Options info
#define PROV_OPTIONS                                                             \
  "\nHost Provisioner-related options:\n"                                        \
  "    -i --nodeinfo    Print DCD information about a node in the network\n"     \
  "                     <UUID>     The unique identifier of the node.\n"         \
  "    -l --nodelist    List all nodes present in the provisioner's device "     \
  "database (DDB)\n"                                                             \
  "    -p --provision   Provision a node\n"                                      \
  "                     <UUID>     The UUID of the node to be provisioned. "     \
  "Can be acquired by --scan.\n"                                                 \
  "    -r --remove      Remove the given node from the Mesh network\n"           \
  "                     <UUID>     The UUID of the node to be removed\n"         \
  "    -k --key-refresh Refresh the network key and app key\n"                   \
  "                     <timeout>  Phase timeout in seconds\n"                   \
  "    -x --key-export  Export the network, app, and device keys in JSON\n"      \
  "                     <filename> Output file name"                             \
  "    -e --reset       Factory reset the provisioner. Note: This command does " \
  "not remove existing devices from the network.\n"                              \
  "    -s --scan        Scan and list unprovisioned beaconing nodes\n"           \
  "\nUUID shall be a string containing 16 separate octets, e.g. "                \
  "\"00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff\"\n"                        \
  "The separator can be any character, but in case of a whitespace character "   \
  "this example requires quotation marks around the string.\n\n"

// ----------------------------------------------------------------------------
// Enums

/// Current provisioner mode, either single run command line mode or ui, menu mode
typedef enum {
  PROV_CMD_LINE_MODE,
  PROV_UI_MODE
}prov_mode_t;

/**************************************************************************//**
 * Provisioner Command Line Application Init
 *
 * @param[in] opt Command option
 * @param[in] optarg Command argument
 * @retval SL_STATUS_OK if command started successfully
 *         SL_STATUS_NOT_FOUND if command is unknown
 *****************************************************************************/
sl_status_t btmesh_app_prov_init(int opt, char *optarg);

/**************************************************************************//**
 * Provisioner Application Process Action
 *
 *****************************************************************************/
void btmesh_app_prov_process_action(void);

/**************************************************************************//**
 * Bluetooth Mesh stack event handler
 *
 * @param[in] evt Event coming from the Bluetooth Mesh stack
 *****************************************************************************/
void btmesh_app_prov_on_event(sl_btmesh_msg_t *evt);

/**************************************************************************//**
 * Get the provisioner command and command status
 *
 * @param[out] prov_command       Current command
 * @param[out] prov_command_state Current command status
 *****************************************************************************/
void btmesh_app_prov_get_command(command_t *prov_command, command_state_t *prov_command_state);

/**************************************************************************//**
 * Set the provisioner command
 *
 * @param[in] prov_command       New command
 *****************************************************************************/
void btmesh_app_prov_set_command(command_t prov_command);

/**************************************************************************//**
 * Set the provisioner command status
 *
 * @param[out] prov_command_state New command status
 *****************************************************************************/
void btmesh_app_prov_set_command_state(command_state_t prov_command_state);

/**************************************************************************//**
 * Get the command options struct array address
 *
 * @param[out] prov_options Options struct array address
 *****************************************************************************/
void btmesh_app_prov_get_cmd_options(struct option **prov_options);

/**************************************************************************//**
 * Get the command options struct array address for CBP
 *
 * @param[out] prov_options Options struct array address
 *****************************************************************************/
void btmesh_cbp_prov_get_cmd_options(struct option **prov_options);

/**************************************************************************//**
 * Handle the main menu in UI mode
 *
 *****************************************************************************/
void btmesh_app_prov_handle_ui(void);

/**************************************************************************//**
 * Get UUID from UI for provisioning
 *
 * @param[out] command_uuid The variable to fill with the parsed data
 * @retval false the returned uuid is not valid yet
 *         true if valid uuid was returned
 *****************************************************************************/
bool btmesh_app_prov_get_uuid_from_unprov_list(uuid_128 *command_uuid);

/**************************************************************************//**
 * Get UUID from UI from rovisioned node list
 *
 * @param[out] command_uuid The variable to fill with UUID
 * @retval false the returned uuid is not valid yet
 *         true if valid uuid was returned
 *****************************************************************************/
bool btmesh_app_prov_get_uuid_from_prov_list(uuid_128 *command_uuid);

/**************************************************************************//**
 * Get ddb status after startup
 *
 * @retval ddb status
 *         false if ddb is not ready yet after startup
 *         true  if ddb is ready after startup
 *****************************************************************************/
bool btmesh_app_prov_get_ddb_status(void);

/**************************************************************************//**
 * Set provisioner mode, command line or ui mode
 *
 *  @param[in] prov_mode       New provisioner mode
 *****************************************************************************/
void btmesh_app_prov_set_mode(prov_mode_t prov_mode);

/**************************************************************************//**
 * Get provisioner mode command line or menu UI mode
 *
 * @retval   PROV_CMD_LINE_MODE command line mode
 *           PROV_UI_MODE menu UI mode mode
 *****************************************************************************/
prov_mode_t btmesh_app_prov_get_mode(void);

/**************************************************************************//**
 * Callback to inform when the nodeinfo query ends
 *
 *****************************************************************************/
void btmesh_app_prov_on_nodeinfo_end(void);

/**************************************************************************//**
 * Callback to inform when the command ends
 *
 *****************************************************************************/
void btmesh_app_prov_end_of_cmd(void);

/**************************************************************************//**
 * Helper script to print a given UUID
 *
 * @param[in] uuid Pointer to the UUID
 *****************************************************************************/
void btmesh_app_prov_append_uuid(uuid_128 *uuid);

/**************************************************************************//**
 * Get ddb status after startup
 *
 * @retval networks number
 *****************************************************************************/
uint16_t btmesh_app_prov_get_networks_number(void);

/***************************************************************************//**
* Handle certificate-based provisioning
*
* @param[in] netkey_index Netkey index of the network
* @param[in] uuid UUID of the device to be provisioned
* @param[in] mac_address MAC address of the device to be provisioned
* @param[in] bearer_type Type of the provisioning bearer layer. Can be
*                        PB-ADV (0) or PB-GATT (1).
*******************************************************************************/
void btmesh_app_prov_handle_cbp(uint16_t netkey_index,
                                uuid_128 uuid,
                                bd_addr mac_address,
                                uint8_t bearer_type);

/***************************************************************************//**
* Inform the CBP handler if the provisioned node is capable of CBP or not
*
* @param[in] capability true if the node is CBP-capable, false otherwise
*******************************************************************************/
void btmesh_app_prov_set_cbp_capability(bool capability);

#ifdef __cplusplus
};
#endif

#endif // BTMESH_APP_PROV_H

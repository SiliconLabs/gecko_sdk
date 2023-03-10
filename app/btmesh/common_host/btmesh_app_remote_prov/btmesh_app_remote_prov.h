/**************************************************************************//**
 * @file
 * @brief BT Mesh Remote Provisioner Application component - CLI handler
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

#ifndef BTMESH_APP_REMOTE_PROV_H
#define BTMESH_APP_REMOTE_PROV_H

#include <getopt.h>
#include "sl_status.h"
#include "btmesh_app_prov.h"
#include "ncp_host.h"

#ifdef SL_CATALOG_APP_PROV_CBP_PRESENT
#include "btmesh_app_prov_cbp.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
/// Optstring argument for getopt
#define REMOTE_PROV_OPTLENGTH                4

/// Optstring argument for getopt
#define REMOTE_PROV_OPTSTRING                "a:mo:v:"

/// Usage info
#define REMOTE_PROV_USAGE                                         \
  " [--remote_provision <UUID> --remote_server <server address>]" \
  " [--remote_scan <server address>]"                             \
  " [--remote_serverlist]"                                        \

// Options info
#define REMOTE_PROV_OPTIONS                                                     \
  "\nRemote Provisioner-related options:\n"                                     \
  "    -v --remote_provision <UUID> -a --remote_server <Address>\n"             \
  "                    Remote provision an unprovisioned node\n"                \
  "                    <UUID>     The UUID of the node to be provisioned.\n"    \
  "                    Can be acquired by --remote_scan.\n"                     \
  "                    <Address>  The server addres for remote provisioning\n"  \
  "                    Can be acquired by --remote_serverlist.\n"               \
  "    -o --remote_scan <Address>\n"                                            \
  "                    Scan and list remote unprovisioned nodes\n"              \
  "                    <Address>  The server addres used for executing the "    \
  "remote scan operation\n"                                                     \
  "                    Can be acquired by --remote_serverlist command.\n"       \
  "    -m --remote_serverlist   List all available remote servers for further " \
  "remote operations\n\n"                                                       \
  "The <Address> parameter should be a 16 bit hexadecimal number, the usage "   \
  "of the 0x before the number is optional\n\n"

// If CBP is not used, define its macros
#ifndef SL_CATALOG_APP_PROV_CBP_PRESENT
#define CBP_OPTLENGTH 0
#define CBP_OPTSTRING
#define CBP_USAGE
#define CBP_OPTIONS
#endif // SL_CATALOG_APP_PROV_CBP_PRESENT

// Size of long options struct array size
#define LONG_OPT_SIZE       PROV_OPTLENGTH + REMOTE_PROV_OPTLENGTH + CBP_OPTLENGTH + LAST_OPTION_ELEMENT
// Optstring argument for getopt.
#define OPTSTRING           NCP_HOST_OPTSTRING PROV_OPTSTRING REMOTE_PROV_OPTSTRING CBP_OPTSTRING "h"

// Usage info.
#define USAGE               "\n%s " NCP_HOST_USAGE PROV_USAGE REMOTE_PROV_USAGE CBP_USAGE " [-h]\n"

// Options info.
#define OPTIONS            \
  "\nConnection options\n" \
  NCP_HOST_OPTIONS         \
  PROV_OPTIONS             \
  REMOTE_PROV_OPTIONS      \
  CBP_OPTIONS              \
  "    -h  Print this help message.\n"

/**************************************************************************//**
* Remote Provisioner Command Line Application Init
*
* @param[in] cmd_opt Command option
* @param[in] cmd_optarg Command argument
* @retval SL_STATUS_OK if command started successfully
*         SL_STATUS_NOT_FOUND if command is unknown
******************************************************************************/
sl_status_t btmesh_app_remote_prov_init(int cmd_opt, char *cmd_optarg);

/**************************************************************************//**
* Remote Provisioner Application Process Action
*
******************************************************************************/
void btmesh_app_remote_prov_process_action(void);

/**************************************************************************//**
 * Bluetooth Mesh stack event handler
 *
 * @param[in] evt Event coming from the Bluetooth Mesh stack
 *****************************************************************************/
void btmesh_app_remote_prov_on_event(sl_btmesh_msg_t *evt);

/**************************************************************************//**
 * Get the remote provisioner command and command status
 *
 * @param[out] remote_prov_command       Current command
 * @param[out] remote_prov_command_state Current command status
 *****************************************************************************/
void btmesh_app_remote_prov_get_command(command_t *remote_prov_command, command_state_t *remote_prov_command_state);

/**************************************************************************//**
 * Set the remote provisioner command
 *
 * @param[in] remote_prov_command       New command
 *****************************************************************************/
void btmesh_app_remote_prov_set_command(command_t remote_prov_command);

/**************************************************************************//**
 * Set the remote provisioner command status
 *
 * @param[out] remote_prov_command_state New command status
 *****************************************************************************/
void btmesh_app_remote_prov_set_command_state(command_state_t remote_prov_command_state);

/**************************************************************************//**
 * Callback to inform when the command ends
 *
 *****************************************************************************/
void btmesh_app_remote_prov_end_of_cmd(void);

/**************************************************************************//**
 * Get remote provisioning server address from UI
 *
 * @param[out] ui_server_address The variable to fill with server address
 * @retval false the returned server address is not valid
 *         true if valid server address was returned
 *****************************************************************************/
bool btmesh_app_remote_prov_get_server_address(uint16_t *ui_server_address);

/**************************************************************************//**
 * Get remote provisioning server address and unprovisioned node uuid from UI
 *
 * @param[out] remote_prov_server_addr The variable to fill with server address
 * @param[out] remote_prov_uuid The variable to fill with unprovisioned node uuid
 * @param[out] remote_prov_oob_capabilities The variable to fill with unprovisioned
 *                                          node OOB capability bitmask
 * @retval false the returned provisioning data is not valid
 *         true if valid provisioning data was returned
 *****************************************************************************/
bool btmesh_app_remote_prov_get_prov_data(uint16_t *remote_prov_server_addr,
                                          uuid_128 *remote_prov_uuid,
                                          uint16_t *remote_prov_oob_capabilities);

#ifdef __cplusplus
};
#endif

#endif // BTMESH_APP_REMOTE_PROV_H

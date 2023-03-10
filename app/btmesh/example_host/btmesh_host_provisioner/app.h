/***************************************************************************//**
 * @file
 * @brief BT Mesh Host Provisioner Example Project.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef APP_H
#define APP_H

#include <stdint.h>
#include <getopt.h>
#include "sl_btmesh_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Default netkey index
#define APP_NETKEY_IDX                0
/// UUID length in AABBCCDD format
#define UUID_LEN_WITHOUT_SEPARATORS   32
/// UUID length in AA:BB:CC:DD format
#define UUID_LEN_WITH_SEPARATORS      47
/// Address length in 1234 format
#define ADDRESS_LEN_WITHOUT_PREFIX    4
/// Address length in 0x1234 format
#define ADDRESS_LEN_WITH_PREFIX       6
/// 2 seconds timer for provisioner reset
#define RESET_TIMER_MS                2000
/// 5 seconds timer for scanning unprovisioned devices
#define SCAN_TIMER_MS                 5000
/// 5 seconds timer for remote scanning unprovisioned devices
#define REMOTE_PROV_SCANNING_TIMEOUT  (uint8_t)5
/// Attention timer value, in seconds
#define REMOTE_PROV_ATTENTION_TIMER   (uint8_t)0
/// Default phase timeout for key refresh in seconds used in UI mode
#define DEFAULT_PHASE_TIMEOUT_S 120
/// Advertising Provisioning Bearer
#define HOST_PROV_PB_ADV              0x1
/// GATT Provisioning Bearer
#define HOST_PROV_PB_GATT             0x2
/// Remote Provisioning Bearer
#define HOST_PROV_PB_REMOTE           0x3

typedef enum command_e{
  NONE,
  SCAN,
  PROVISION,
  NODELIST,
  NODEINFO,
  REMOVE_NODE,
  KEY_REFRESH,
  KEY_EXPORT,
  RESET,
  REMOTE_SERVERLIST,
  REMOTE_SCAN,
  REMOTE_PROVISION
} command_t;

typedef enum command_state_e{
  INIT,
  START,
  IN_PROGRESS,
  FINISHED
} command_state_t;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(int argc, char *argv[]);

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void);

/**************************************************************************//**
 * Application Deinit.
 *****************************************************************************/
void app_deinit(void);

/***************************************************************************//**
 * Callback to inform when the node configuration process ends
 *
 * @param[in] netkey_index Netkey index of the configured node
 * @param[in] server_address Primary subnet address of the configured node
 ******************************************************************************/
void app_on_node_configuration_end(uint16_t netkey_index,
                                   uint16_t server_address);

/***************************************************************************//**
 * Parse UUID from the given string
 *
 * @param[in] input The string to parse
 * @param[in] length Length of the string
 * @param[out] parsed_uuid The struct to fill with the parsed data
 ******************************************************************************/
void app_parse_uuid(char *input, size_t length, uuid_128 *parsed_uuid);

/***************************************************************************//**
 * Parse primary element address from the given string
 *
 * @param[in] input The string to parse
 * @param[in] length Length of the string
 * @param[out] address The variable to fill with the parsed data
 ******************************************************************************/
void app_parse_address(char *input, size_t length, uint16_t *address);

/**************************************************************************//**
 * Callback to inform about provisioning failed event
 *
 *******************************************************************************/
void btmesh_app_on_provision_failed(void);

/**************************************************************************//**
 * Callback to inform about configuration end event
 *
 *******************************************************************************/
void btmesh_app_on_node_configuration_end(void);

/**************************************************************************//**
 * Callback to copy options array
 *
 * @param[out] long_options Destination addres for options array
 *******************************************************************************/
void btmesh_app_on_build_cmd_options(struct option *long_options);

/**************************************************************************//**
 * Callback to copy options array for CBP
 *
 * @param[out] long_options Destination addres for options array
 *******************************************************************************/
void btmesh_cbp_on_build_cmd_options(struct option *long_options);

/**************************************************************************//**
 * Callback to check unknown command options
 *
 * @param[in] cmd_opt Command option
 * @param[in] cmd_optarg Command argument
 * @retval SL_STATUS_OK if command option was recognized
 *         SL_STATUS_NOT_FOUND if command is unknown
 *******************************************************************************/
sl_status_t btmesh_app_on_check_cmd_options(int cmd_opt, char *cmd_optarg);

/**************************************************************************//**
 * Callback to check CBP-related command options
 *
 * @param[in] cmd_opt Command option
 * @param[in] cmd_optarg Command argument
 * @retval SL_STATUS_OK if command option was recognized
 *         SL_STATUS_NOT_FOUND if command is unknown
 *******************************************************************************/
sl_status_t btmesh_cbp_on_check_cmd_options(int cmd_opt, char *cmd_optarg);

#ifdef __cplusplus
};
#endif

#endif // APP_H

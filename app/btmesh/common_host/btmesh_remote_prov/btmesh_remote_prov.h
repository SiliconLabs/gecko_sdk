/**************************************************************************//**
 * @file
 * @brief BT Mesh Remote Provisioner Component
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

#ifndef BTMESH_REMOTE_PROV_H
#define BTMESH_REMOTE_PROV_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "sl_btmesh_api.h"

/// Unassociated remote provisioning server or unprovisioned node ID
#define REMOTE_PROV_UNUSED_ID               0xffff

/**************************************************************************//**
 * Provisioner Process Action
 *
 * @param[in] evt Received BT Mesh event
 *****************************************************************************/
void btmesh_remote_prov_on_event(const sl_btmesh_msg_t *evt);

/**************************************************************************//**
* Start scanning for available remote provisioning servers
*
* @param[in] netkey_index Netkey index of the network
* @return Status of the remote provisioning server scan
* @retval SL_STATUS_OK if scan started successfully
*         Error value otherwise
******************************************************************************/
sl_status_t btmesh_remote_prov_start_server_capabilities_scan(uint16_t netkey_index);

/**************************************************************************//**
* Start scanning for remote unprovisioned devices by server address
*
* @param[in] netkey_index Netkey index of the network
* @param[in] server       Address of the server used for remote scan
* @param[in] timeout      Time limit for a scan (in seconds)
* @return Status of the remote provisioning scan
* @retval SL_STATUS_OK if scan started successfully
*         Error value otherwise
******************************************************************************/
sl_status_t btmesh_remote_prov_start_device_scan_by_address(uint16_t netkey_index,
                                                            uint16_t server,
                                                            uint8_t timeout);

/**************************************************************************//**
* Start remote provisioning an unprovisioned node
*
* @param[in] netkey_index Netkey index of the network
* @param[in] server       Address of the server used for remote provisioning
* @param[in] uuid         UUID of the unprovisioned node
* @param[in] bearer_type  Provisioning bearer type, PB_ADV or PB_GATT
* @param[in] attention_timer_sec Attention timer value in seconds
* @return Status of the provisioning
* @retval SL_STATUS_OK If the provisioning started successfully
*         Error code otherwise
******************************************************************************/
sl_status_t btmesh_remote_prov_start_provisioning(uint16_t netkey_index,
                                                  uint16_t server,
                                                  uuid_128 uuid,
                                                  uint8_t bearer_type,
                                                  uint8_t attention_timer_sec);

/**************************************************************************//**
* Callback to inform the application that a new active remote provisioning
* server was found
*
* @param[in] server     Address of the found server
* @param[in] max_items  The maximum number of UUIDs that can be reported
*                       by the server during scanning
******************************************************************************/
void btmesh_remote_prov_on_client_scan_capabilities(uint16_t server,
                                                    uint8_t  max_items);

/**************************************************************************//**
* Callback to inform the application that remote provisioning server capabilities
* scannig of all known nodes from network is finished
*
******************************************************************************/
void btmesh_remote_prov_on_client_scan_capabilities_finished(void);

/**************************************************************************//**
* Callback to inform the application that a new unprovisioned node was found
*
* @param[in] uuid UUID of the node
******************************************************************************/
void btmesh_remote_prov_on_client_scan_report(uuid_128 uuid);

/**************************************************************************//**
* Callback to inform the application that the remote scanning of unprovisioned
* nodes is finished
*
******************************************************************************/
void btmesh_remote_prov_on_client_scan_finished(void);

/**************************************************************************//**
* Callback to inform the application of an unprovisioned node
*
* @param[in] id   List ID of the unprovisioned node
* @param[in] uuid UUID of the unprovisioned node
******************************************************************************/
void btmesh_remote_prov_on_unprovisioned_node_list(uint16_t id, uuid_128 uuid);

/**************************************************************************//**
* Callback to inform the application of an active remote provisioning server
*
* @param[in] id     List ID of the remote provisioning server
* @param[in] server Address of the remote provisioning server
******************************************************************************/
void btmesh_remote_prov_on_serverlist(uint16_t id, uint16_t server);

/**************************************************************************//**
* Callback to inform the application that the remote scan command was received
* by the addressed remote provisioning server
*
* @param[in] server Server address
* @param[in] status Server status
* @param[in] state  Scan state
******************************************************************************/
void btmesh_remote_prov_on_client_scan_status(uint16_t server,
                                              uint8_t status,
                                              uint8_t state);

/**************************************************************************//**
* Callback to inform the application that the open link command was received
* by the addressed remote provisioning server
*
* @param[in] server Server address
* @param[in] status Server status
* @param[in] state  Scan state
******************************************************************************/
void btmesh_remote_prov_on_client_link_status(uint16_t server,
                                              uint8_t status,
                                              uint8_t state);

/**************************************************************************//**
* List all active remote provisioning servers found in a previous
* server capabilities scan
*
* @return Status of the command
* @retval SL_STATUS_OK If all known servers are listed
* @retval SL_STATUS_EMPTY If no remote provisioning servers are known
******************************************************************************/
sl_status_t btmesh_remote_prov_list_active_servers(void);

/**************************************************************************//**
* List all unprovisioned nodes found in a previous remote scan using a
* server address
*
* @param[in] server Address of the remote server used during previous remote scan
* @return Status of the command
* @retval SL_STATUS_OK If all known unprovisioned nodes are listed
* @retval SL_STATUS_EMPTY If no unprovisioned nodes are known by this server
******************************************************************************/
sl_status_t btmesh_remote_prov_list_unprovisioned_nodes_by_addr(uint16_t server);

/**************************************************************************//**
* Get the server address associated to a server list ID
* Remote provisioning server capabilities scan is necessary earlier
*
* @param[in]  id     List ID to which the associated address is requested
* @param[out] server Address of the server associated to the list ID
* @return Status of the command
* @retval SL_STATUS_OK If server was found
* @retval SL_STATUS_EMPTY If server not found
******************************************************************************/
sl_status_t btmesh_remote_prov_get_server_address_by_id(uint16_t id,
                                                        uint16_t *server);

/**************************************************************************//**
* Get the uuid of an unprovisioned node associated to a list ID
* Remote provisioning server capabilities scan and remote scan is necessary earlier
*
* @param[in]  id               List ID to which the associated uuid is requested
* @param[in]  server           Address of the server which was used during remote scan
* @param[out] uuid             uuid of the unprovisioned node associated to the list ID
* @param[out] oob_capabilities OOB capability bitmask of the unprovisioned node
* @return Status of the command
* @retval SL_STATUS_OK If server was found
* @retval SL_STATUS_EMPTY If server not found
******************************************************************************/
sl_status_t btmesh_remote_prov_get_unprov_uuid_by_id(uint16_t id,
                                                     uint16_t server,
                                                     uuid_128 *uuid,
                                                     uint16_t *oob_capabilities);

/**************************************************************************//**
* Clear all remote provisioning server related lists
*
******************************************************************************/
void btmesh_remote_prov_free_serverlist(void);

#ifdef __cplusplus
};
#endif

#endif /* BTMESH_REMOTE_PROV_H */

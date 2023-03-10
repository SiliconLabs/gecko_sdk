/**************************************************************************//**
* @file
* @brief BT Mesh Provisioner component
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
******************************************************************************/
#ifndef BTMESH_PROV_H
#define BTMESH_PROV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sl_btmesh_api.h"
#include "btmesh_conf.h"

// Bits 7 and 8 of the oob_capabilities flag indicate that the node
// supports CBP
#define BTMESH_OOB_FLAG_CBP_CAPABLE 0x180

/***************************************************************************//**
* Provisioner Process Action.
*
* @param[in] evt Received BT Mesh event
*******************************************************************************/
void btmesh_prov_on_event(sl_btmesh_msg_t *evt);

/***************************************************************************//**
* Start scanning for unprovisioned beaconing nodes
*
* @return Status of the scan.
* @retval SL_STATUS_OK if scan started successfully.
*         Error value otherwise.
*******************************************************************************/
sl_status_t btmesh_prov_start_scanning(void);

/***************************************************************************//**
* Stop scanning of unprovisioned beaconing nodes
*
* @return Status of the scan.
* @retval SL_STATUS_OK if scan stopped successfully.
*         Error value otherwise.
*******************************************************************************/
sl_status_t btmesh_prov_stop_scanning(void);

/***************************************************************************//**
* Setup provisioning
*
* @param[in] netkey_index Netkey index of the network
* @param[in] uuid UUID of the node
* @param[in] bearer_type Provisioning bearer type. Either PB-ADV or PB-GATT
* @param[in] attention_timer_sec Attention timer value in seconds
* @return Status of the provisioning.
* @retval SL_STATUS_OK If provisioning is set up successfully.
*         Error code otherwise.
*******************************************************************************/
sl_status_t btmesh_prov_setup_provisioning(uint16_t netkey_index,
                                           uuid_128 uuid,
                                           uint8_t bearer_type,
                                           uint8_t attention_timer_sec);

/***************************************************************************//**
* Provision device into network
*
* @param[in] netkey_index Netkey index of the network
* @param[in] uuid UUID of the node
* @param[in] mac_address Bluetooth address of the node
* @param[in] bearer_type Provisioning bearer type. Either PB-ADV or PB-GATT
* @param[in] attention_timer_sec Attention timer value in seconds
* @return Status of the provisioning.
* @retval SL_STATUS_OK If provisioning is \a started successfully.
*         Error code otherwise.
*******************************************************************************/
sl_status_t btmesh_prov_provision_adv_device(uint16_t netkey_index,
                                             uuid_128 uuid,
                                             bd_addr mac_address,
                                             uint8_t bearer_type,
                                             uint8_t attention_timer_sec);

/**************************************************************************//**
* Get UUID based on the ID of an unprovisioned node
*
* @param[in] id ID for which the UUID was requested
* @param[out] uuid UUID of the node
* @return Status of the provisioning.
* @retval SL_STATUS_OK If the ID is valid and the related UUID was copied
*         to the output parameter
*         Error code otherwise.
******************************************************************************/
sl_status_t btmesh_prov_get_unprov_uuid_by_id(uint16_t id, uuid_128 *uuid);

/**************************************************************************//**
* Get UUID based on the ID of a provisioned node
*
* @param[in] id ID for which the UUID was requested
* @param[out] uuid UUID of the node
* @return Status of the provisioning.
* @retval SL_STATUS_OK If the ID is valid and the related UUID was copied
*         to the output parameter
*         Error code otherwise.
******************************************************************************/
sl_status_t btmesh_prov_get_prov_uuid_by_id(uint16_t id, uuid_128 *uuid);

/**************************************************************************//**
* Get UUID based on the primary address of a node
*
* @param[in] primary_address primary address for which UUID was requested
* @param[out] uuid UUID of the node
* @return Status of the provisioning.
* @retval SL_STATUS_OK If the address is valid and the related UUID was copied
*         to the output parameter
*         Error code otherwise.
******************************************************************************/
sl_status_t btmesh_prov_get_prov_uuid_by_address(uint16_t primary_address, uuid_128 *uuid);

/**************************************************************************//**
* Remove a node from a network by UUID
*
* @param[in] uuid UUID of the node
* @param[in] on_job_notification Job status notification callback
* @return Status of the node removal.
* @retval SL_STATUS_OK if node removal \a started successfully.
*         Error code otherwise.
*
* Node removal success or failure is reported in on_job_notification callback.
******************************************************************************/
sl_status_t btmesh_prov_remove_node_by_uuid(uuid_128 uuid,
                                            btmesh_conf_on_job_notification_t on_job_notification);

/**************************************************************************//**
* List all unprovisioned nodes found in a previous scan
*
* @return Status of the command.
* @retval SL_STATUS_OK If all known nodes are listed.
* @retval SL_STATUS_EMPTY If no unprovisioned nodes are known.
******************************************************************************/
sl_status_t btmesh_prov_list_unprovisioned_nodes(void);

/**************************************************************************//**
* List all provisioned nodes present
*
* @return Status of the command.
* @retval SL_STATUS_OK If all known nodes are listed.
* @retval SL_STATUS_EMPTY If no provisioned nodes are known.
******************************************************************************/
sl_status_t btmesh_prov_list_provisioned_nodes(void);

/**************************************************************************//**
* List all entries in the device database of the provisioner node
*
* @param[out] count Number of nodes in the DDB
* @return Status of the list command.
* @retval SL_STATUS_OK If the listing started successfully.
*         Error code otherwise.
*
* The provisioner will trigger \a count sl_btmesh_evt_prov_ddb_list events.
******************************************************************************/
sl_status_t btmesh_prov_list_ddb_entries(uint16_t *count);

/**************************************************************************//**
* Delete a node from the device database of the provisioner node
*
* @param[in] uuid UUID of the node to be deleted
* @return  Status of the command.
* @retval SL_STATUS_OK If deletion started successfully.
*         Error code otherwise.
*
* The provisioner will trigger an sl_btmesh_evt_prov_delete_ddb_entry_complete
* event when the deletion is finished.
******************************************************************************/
sl_status_t btmesh_prov_delete_ddb_entry(uuid_128 uuid);

/**************************************************************************//**
* Create a new application key on the provisioner node
*
* @param[in] netkey_index Netkey index of the network.
* @param[in] appkey_index Appkey index to use.
* @param[in] key_len Length of the appkey data.
* @param[in] key Key value to use. Set to zero-length to generate random key.
* @param[in] max_application_key_size Size of output buffer passed in application_key.
* @param[out] application_key_len The length of output data written to application_key.
* @param[out] application_key New application key. Ignore it if the result was non-zero.
* @return Status of the key creation procedure.
* @retval SL_STATUS_OK If successful.
*         Error code otherwise.
******************************************************************************/
sl_status_t btmesh_prov_create_appkey(uint16_t netkey_index,
                                      uint16_t appkey_index,
                                      size_t key_len,
                                      const uint8_t *key,
                                      size_t max_application_key_size,
                                      size_t *application_key_len,
                                      uint8_t *application_key);

/**************************************************************************//**
* Create a new network on the provisioner node
*
* @param[in] netkey_index Netkey index to use.
* @param[in] key_len Length of the netkey data.
* @param[in] key Key value to use. Set to zero-length array to generate a random key.
* @return Status of the network creation.
* @retval SL_STATUS_OK If successful.
*         Error code otherwise.
******************************************************************************/
sl_status_t btmesh_prov_create_network(uint16_t netkey_index,
                                       size_t key_len,
                                       const uint8_t *key);

/**************************************************************************//**
* Callback to inform the application that a new node was provisioned
*
* @param[in] address Primary element address of the node
* @param[in] uuid UUID of the node
******************************************************************************/
void btmesh_prov_on_device_provisioned_evt(uint16_t address, uuid_128 uuid);

/**************************************************************************//**
* Callback to inform the application that a provisioning session failed
*
* @param[in] reason Reason of the failure
* @param[in] uuid UUID of the node
******************************************************************************/
void btmesh_prov_on_provision_failed_evt(uint8_t reason, uuid_128 uuid);

/**************************************************************************//**
* Callback to inform the application of an unprovisioned node
*
* @param[in] id List ID of the node
* @param[in] uuid UUID of the node
* @param[in] oob_capabilities OOB capability bitmask
******************************************************************************/
void btmesh_prov_on_unprovisioned_node_list_evt(uint16_t id,
                                                uuid_128 uuid,
                                                uint16_t oob_capabilities);

/**************************************************************************//**
* Callback to inform the application of a provisioned node
*
* @param[in] id List ID of the node
* @param[in] uuid UUID of the node
* @param[in] primary_address Primary element address of the node
******************************************************************************/
void btmesh_prov_on_provisioned_node_list_evt(uint16_t id,
                                              uuid_128 uuid,
                                              uint16_t primary_address);

/**************************************************************************//**
* Callback to inform the application that the DDB list is ready
*
* @param[in] count Number of nodes in the DDB
******************************************************************************/
void btmesh_prov_on_ddb_list_ready(uint16_t count);

/**************************************************************************//**
 * Free remote provisioner internal server lists
 *
 *****************************************************************************/
void btmesh_prov_free_remote_serverlist(void);

/***************************************************************************//**
* Setup certificate-based provisioning
*
* @param[in] uuid UUID of the device to be provisioned
* @return Status of the setup sequence
* @retval SL_STATUS_OK If successful
*         Error code otherwise
*******************************************************************************/
sl_status_t btmesh_prov_setup_cbp(uuid_128 uuid);

/***************************************************************************//**
* Wrapper for provisioning records initialization
*
* @return Status of the initialization sequence
*******************************************************************************/
sl_status_t btmesh_prov_init_provisioning_records(void);

/***************************************************************************//**
* BT Mesh event handler for CBP
*
* @param[in] evt The received event
*******************************************************************************/
void btmesh_cbp_on_event(sl_btmesh_msg_t *evt);

#ifdef __cplusplus
}
#endif

#endif // BTMESH_PROV_H

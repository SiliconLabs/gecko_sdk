/***************************************************************************//**
 * @file
 * @brief BT Mesh Firmware Distribution Server
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

#ifndef SL_BTMESH_FW_DISTRIBUTION_SERVER_H
#define SL_BTMESH_FW_DISTRIBUTION_SERVER_H

#include "sl_btmesh_api.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * @addtogroup dist_server BT Mesh Firmware Distribution Server
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Set the multicast threshold value
 *
 * The FW Distribution Server BT Mesh stack model caches the value of multicast
 * threshold when the distribution is started and it passes the value to the MBT
 * Client model (BLOB Transfer Client) in BT Mesh stack when the BLOB transfer
 * is started. If the number of servers for any step exceeds or equal to this
 * number then the group address will be used, otherwise the servers will be
 * looped through one by one. Value of 0 disables the feature.
 *
 * The MBT Client BT Mesh stack model tracks the number of servers which it needs
 * to send specific messages to.
 * It tracks for each server if the proper status message is received from the
 * server in case of BLOB Information Get, BLOB Transfer Start, BLOB Block Start
 * and BLOB Block Get messages. If some servers don't receive these BLOB messages
 * or the response status messages are lost due to interference then the retry
 * logic in BLOB Transfer Client SDK component requests to send the necessary
 * BLOB messages to the servers by calling the proper MBT Client API again.
 * If number of servers with missing status messages exceeds or equal to the
 * multicast threshold value then the mentioned messages are sent to the group
 * address, otherwise servers will be looped through one by one.
 *
 * The tracking of successful reception of Chunk Transfer Messages are different
 * because these are tracked by block status procedure in case of push transfer
 * mode or by partial block report procedure in case of pull transfer mode.
 *
 * The advantage of multicast messages is that the client needs to send one
 * message only to the servers which is much faster if the number of servers
 * which haven't received the message is high. This is especially true for chunk
 * transfer because Chunk Transfer messages can be quite big and there are
 * quite many of them in the BLOB Transfer.
 *
 * The advantage of unicast addressing in case of non-chunk messages is that only
 * those server respond with status messages which really need to. This can have
 * significant effect when the node count is high.
 * For example if there are hundreds of nodes in the BLOB transfer then each
 * group message triggers hundreds of status messages even when only some status
 * messages from specific servers are missing on the client side.
 * The transport layer uses segment acknowledgment for segmented unicast mesh
 * messages which improves the reliability of segmented message transfer
 * especially when the number of segments are high but it tends to be slower
 * because the segment acknowledgment messages needs to be waited.
 *
 * @warning The MBT client stack model allocates and sends all unicast BLOB
 *   messages to each server at the same time below the multicast threshold.
 *   This could lead to exhaustive buffer allocation and the maximum number of
 *   parallel segmented messages can be exceeded as well in case of high
 *   multicast threshold level. The multicast threshold shall not be greater
 *   than SL_BTMESH_CONFIG_MAX_SEND_SEGS from sl_btmesh_config.h.
 *
 * @note The multicast threshold shall be set when the distribution is started
 *   (or before) in order to have an effect on the BLOB transfer otherwise it
 *   affects the next transfer only. The multicast threshold can be set in
 *   @ref sl_btmesh_fw_distribution_server_on_distribution_started callback as
 *   well to tune it to the specific FW distribution.
 *
 * @param elem_index Distribution Server model element index
 * @param multicast_threshold If the number of servers for any step exceeds or
 *   is equal to this number then the group address will be used, otherwise
 *   servers will be looped through one by one.
 *   Value of 0 disables the feature.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 *
 ******************************************************************************/
sl_status_t sl_btmesh_fw_distribution_server_set_multicast_threshold(uint16_t elem_index,
                                                                     uint16_t multicast_threshold);

/***************************************************************************//**
 * Handle Firmware Distribution Server events
 *
 * This function is called automatically after enabling the component.
 *
 * @param[in] evt  Pointer to incoming event.
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_event(const sl_btmesh_msg_t *const evt);

/***************************************************************************//**
 * Provides string representations of Distribution states
 *
 * @param[in] state Distribution state
 *
 * @return String representation of distribution state
 * @retval "INVALID" if the state is invalid
 ******************************************************************************/
const char* sl_btmesh_fw_distribution_server_distribution_state_to_string(sl_btmesh_fw_dist_server_dist_step_t state);

/***************************************************************************//**
 * Provides string representations of Firmware Update phase
 *
 * @param[in] node_phase Phase of Firmware Update Server on Target Node
 *
 * @return String representation of node update phase
 * @retval "INVALID" if the node_phase is invalid
 ******************************************************************************/
const char* sl_btmesh_fw_distribution_server_node_phase_to_string(sl_btmesh_fw_dist_server_dist_node_phase_t node_phase);

/***************************************************************************//**
 * Provides string representations of Firmware Update status
 *
 * @param[in] node_status Status of Firmware Update Server on Target Node
 *
 * @return String representation of node's firmware update status
 * @retval "INVALID" if the node_status is invalid
 ******************************************************************************/
const char* sl_btmesh_fw_distribution_server_firmware_update_status_to_string(sl_btmesh_fw_update_server_update_status_t node_status);

// -----------------------------------------------------------------------------
//                        Overridable Callback Functions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Called to generate BLOB ID for firmware distribution
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which uses the sl_bt_system_get_random_data
 *       BT stack API to generate random bytes for BLOB identifier.
 *
 * @param[out] blob_id Pointer to blob_id where the generated bytes shall be stored
 *
 * @return Status of BLOB id generation. If it is not SL_STATUS_OK then the
 *   firmware distribution server component uses the storage BLOB id for the
 *   firmware distribution. The storage BLOB id was used during firmware upload.
 *
 ******************************************************************************/
sl_status_t sl_btmesh_fw_distribution_server_generate_blob_id(sl_bt_uuid_64_t *blob_id);

/***************************************************************************//**
 * Called when a receiver target node is added to the firmware distribution
 * list
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] server_address Unicast address of the added target node
 * @param[in] update_fw_image_idx Firmware image index on target node to be
 *   updated during the distribution
 * @param[in] node_count Total number of target nodes which participates in
 *   the firmware distribution (including this new one)
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_node_added(uint16_t elem_index,
                                                    uint16_t server_address,
                                                    uint8_t update_fw_image_idx,
                                                    uint16_t node_count);

/***************************************************************************//**
 * Called when all receiver target nodes are deleted from the firmware
 * distribution list
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_all_nodes_deleted(uint16_t elem_index);

/***************************************************************************//**
 * Called when firmware distribution is started
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * The @ref sl_btmesh_fw_distribution_server_set_multicast_threshold function
 * can be called from this callback to set the multicast threshold value for
 * the current distribution.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] client_address Address of the Distribution Client
 * @param[in] group_address Group address of the distribution
 * @param[in] ttl Distribution TTL
 * @param[in] update_policy 1 if the Update Policy is Verify and Apply, otherwise 0
 * @param[in] fw_list_index Index of the firmware in the Distributor's FW List
 * @param[in] timeout_base Timeout base
 * @param[in] transfer_mode Transfer Mode to use in the distribution
 * @param[in] node_count Total number of target nodes which participates in
 *   the firmware distribution
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_distribution_started(uint16_t elem_index,
                                                              uint16_t client_address,
                                                              uint16_t group_address,
                                                              uint8_t ttl,
                                                              sl_btmesh_fw_dist_server_dfu_policy_t update_policy,
                                                              uint16_t fw_list_index,
                                                              uint16_t timeout_base,
                                                              sl_btmesh_mbt_client_transfer_mode_t transfer_mode,
                                                              uint16_t node_count);

/***************************************************************************//**
 * Called when firmware distribution is canceled
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] client_address Address of the Distribution Client
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_distribution_canceled(uint16_t elem_index,
                                                               uint16_t client_address);

/***************************************************************************//**
 * Called when firmware distribution is suspended
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] client_address Address of the Distribution Client
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_distribution_suspended(uint16_t elem_index,
                                                                uint16_t client_address);

/***************************************************************************//**
 * Called when firmware distribution is suspended
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] client_address Address of the Distribution Client
 * @param[in] group_address Group address of the distribution
 * @param[in] ttl Distribution TTL
 * @param[in] update_policy 1 if the Update Policy is Verify and Apply, otherwise 0
 * @param[in] fw_list_index Index of the firmware in the Distributor's FW List
 * @param[in] timeout_base Timeout base
 * @param[in] transfer_mode Transfer Mode to use in the distribution
 * @param[in] node_count Total number of target nodes which participates in
 *   the firmware distribution
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_distribution_resumed(uint16_t elem_index,
                                                              uint16_t client_address,
                                                              uint16_t group_address,
                                                              uint8_t  ttl,
                                                              sl_btmesh_fw_dist_server_dfu_policy_t update_policy,
                                                              uint16_t fw_list_index,
                                                              uint16_t timeout_base,
                                                              sl_btmesh_mbt_client_transfer_mode_t transfer_mode,
                                                              uint16_t node_count);

/***************************************************************************//**
 * Called when firmware distribution state has changed
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] state Distribution state
 * @param[in] num_active_nodes Number of target nodes which are still active
 * @param[in] node_count Total number of target nodes
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_distribution_state_changed(uint16_t elem_index,
                                                                    sl_btmesh_fw_dist_server_dist_step_t state,
                                                                    uint16_t num_active_nodes,
                                                                    uint16_t node_count);

/***************************************************************************//**
 * Called when progress of BLOB transfer step during the firmware distribution
 * has changed
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] confirmed_tx_bytes Number of BLOB bytes which are received by
 *   every active BLOB Transfer Server. The progress is calculated at the end
 *   of the blocks because in a block some chunks could be retransmitted
 *   multiple times.
 * @param[in] blob_size Size of the BLOB
 * @param[in] node_count Number of target nodes
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_distribution_blob_progress_changed(uint16_t elem_index,
                                                                            uint32_t confirmed_tx_bytes,
                                                                            uint32_t blob_size,
                                                                            uint16_t node_count);

/***************************************************************************//**
 * Called when a Target Node fails during the distribution
 *
 * If one node fails during the distribution, it does not mean, that the
 * distribution fails as well. The distribution only fails, when every Target
 * Node fails.
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] server_address Unicast address of the failed Target Node
 * @param[in] update_phase Update Phase of Firmware Update Server on Target Node
 * @param[in] update_status Update Status of Firmware Update Server on Target Node
 *   If the firmware update of the node fails due to Firmware Update Server related
 *   error then this field isn't zero and it has sl_btmesh_fw_update_server_update_status_t
 *   value.
 * @param[in] mbt_status Transfer status of BLOB Transfer server on Target Node.
 *   If the firmware update of a node fails due to BLOB Transfer error then this
 *   field won't be zero.
 * @param[in] progress 0-100, percentage of BLOB Transfer octets
 * @param[in] fw_index Firmware image index on Target node which is updated
 *   during the distribution
 * @param[in] num_active_nodes Number of target nodes which are still active
 * @param[in] node_count Total number of target nodes
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_distribution_node_failed(uint16_t elem_index,
                                                                  uint16_t server_address,
                                                                  sl_btmesh_fw_dist_server_dist_node_phase_t update_phase,
                                                                  sl_btmesh_fw_update_server_update_status_t update_status,
                                                                  uint8_t mbt_status,
                                                                  uint8_t progress,
                                                                  uint8_t fw_index,
                                                                  uint16_t num_active_nodes,
                                                                  uint16_t node_count);

/***************************************************************************//**
 * Called when firmware has been added to the Distributor
 *   - Called when a new firmware has been uploaded to the Distributor
 *   - Called when the firmware has been added based on the NVM content at
 *     initialization time
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] client_address Address of the Distribution Client
 *   Set to unassigned address (0x0000) when the firmware is added at init time.
 * @param[in] fw_size Size of the firmware binary image
 * @param[in] fw_list_idx Index of the stored firmware in the firmware list
 * @param[in] current_fw_list_length Current number of stored firmware including
 *   this uploaded firmware as well.
 * @param[in] max_fw_list_length Maximum number of firmwares which can be stored
 *   on the Distributor
 * @param[in] fwid Firmware identifier with 2-byte Company ID which is
 *   followed by 0-106 bytes of Version Information
 * @param[in] fwid_length Length of the Firmware identifier data
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_firmware_added(uint16_t elem_index,
                                                        uint16_t client_address,
                                                        uint32_t fw_size,
                                                        uint16_t fw_list_idx,
                                                        uint16_t current_fw_list_length,
                                                        uint16_t max_fw_list_length,
                                                        const uint8_t *fwid,
                                                        uint8_t fwid_length);

/***************************************************************************//**
 * Called when a firmware has been deleted from the Distributor
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] client_address Address of the Distribution Client
 * @param[in] current_fw_list_length Current number of stored firmwares after the
 *   firmware is deleted from the Distributor
 * @param[in] max_fw_list_length Maximum number of firmwares which can be stored
 *   on the Distributor
 * @param[in] fwid Firmware identifier with 2-byte Company ID which is
 *   followed by 0-106 bytes of Version Information
 * @param[in] fwid_length Length of the Firmware identifier data
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_firmware_deleted(uint16_t elem_index,
                                                          uint16_t client_address,
                                                          uint16_t current_fw_list_length,
                                                          uint16_t max_fw_list_length,
                                                          const uint8_t *fwid,
                                                          uint8_t fwid_length);

/***************************************************************************//**
 * Called when ALL firmwares are deleted from the Distributor
 *
 * This is a callback which can be implemented in the application
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 *
 * @param[in] elem_index Distribution server model element index
 * @param[in] client_address Address of the Distribution Client
 *   It is set to MESH_ADDR_UNASSIGNED when it is caused by an internal event.
 * @param[in] max_fw_list_length Maximum number of firmwares which can be stored
 *   on the Distributor
 *
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_on_all_firmware_deleted(uint16_t elem_index,
                                                              uint16_t client_address,
                                                              uint16_t max_fw_list_length);

/***************************************************************************//**
 * Used for asynchronously deleting firmware images from BLOB storage
 ******************************************************************************/
void sl_btmesh_fw_distribution_server_delete_step_handle(void);

/** @} end dist_server */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SL_BTMESH_FW_DISTRIBUTION_SERVER_H

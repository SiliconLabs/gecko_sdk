/***************************************************************************//**
 * @file
 * @brief Definition of BLOB Transfer Server interface
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SL_BTMESH_BLOB_TRANSFER_SERVER_H
#define SL_BTMESH_BLOB_TRANSFER_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * @addtogroup mesh_blob_transfer_server BT Mesh BLOB Transfer Server
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Initializes the BLOB Transfer Server application
 ******************************************************************************/
extern void sl_btmesh_blob_transfer_server_init(void);

/***************************************************************************//**
 * Processes BT Mesh stack events related to BLOB Trasnfer Server
 *
 * @param[in] evt BT Mesh stack event
 ******************************************************************************/
extern void sl_btmesh_blob_transfer_server_on_event(sl_btmesh_msg_t const *evt);

/***************************************************************************//**
 * Let BLOB Transfer Server accept an incoming BLOB with given ID
 *
 * This function needs to be called from other application components, that can
 * determine incoming BLOB ID's, before any transfer can be done.
 *
 * @note Firmware Update Server automatically handles this operation when it
 * receives a firmware update start message
 * (@ref sl_btmesh_evt_fw_update_server_update_start_req_id).
 *
 * @param blob_id Identifier of BLOB to be received
 * @param timeout_10s Timeout of reception in 10 seconds. If no data is received
 *                    for this time, the transfer will be suspended. The actual
 *                    timeout is calculated as (1 + @p timeout_10s) × 10 s
 * @param ttl The TTL used for communicating with the client
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_INVALID_STATE In case transmission is already ongoing
 ******************************************************************************/
extern sl_status_t sl_btmesh_blob_transfer_server_start(sl_bt_uuid_64_t const * const blob_id,
                                                        const uint16_t timeout_10s,
                                                        const uint8_t ttl);

/***************************************************************************//**
 * Set PULL transfer retry parameters
 *
 * The new values will take effect at the next transfer start. The command does
 * not modify parameters of the ongoing transfer.
 *
 * @param pull_mode_retry_interval_ms Retry interval in milliseconds
 * @param pull_mode_retry_count Number of times to retry
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_INVALID_STATE In case state is invalid
 ******************************************************************************/
extern sl_status_t sl_btmesh_blob_transfer_server_set_pull_mode_parameters(uint16_t pull_mode_retry_interval_ms,
                                                                           uint16_t pull_mode_retry_count);

/***************************************************************************//**
 * Handles the BLOB transfer state machine
 *
 * Used for asynchronously erasing BLOBs
 ******************************************************************************/
void sl_btmesh_blob_transfer_server_step_handle(void);

/** @} end mesh_blob_transfer_server */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SL_BTMESH_BLOB_TRANSFER_SERVER_H

/***************************************************************************//**
 * @file
 * @brief Definitions of user API features
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
#ifndef SL_BTMESH_FIRMWARE_UPDATE_SERVER_API_H
#define SL_BTMESH_FIRMWARE_UPDATE_SERVER_API_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * @addtogroup mesh_fw_update_server
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup mesh_fw_update_server_api
 *
 * BT Mesh Firmware Update Server user-overridable API
 * @{
 ******************************************************************************/

/// Verification step results
typedef enum sl_btmesh_fw_update_server_verify_state_e {
  /// Verification pending
  BTMESH_FW_UPDATE_SERVER_VERIFY_PENDING,
  /// Verification error
  BTMESH_FW_UPDATE_SERVER_VERIFY_ERROR,
  /// Verification successful
  BTMESH_FW_UPDATE_SERVER_VERIFY_SUCCESS
} sl_btmesh_fw_update_server_verify_state_t;

/// Metadata check step result
typedef enum sl_btmesh_fw_update_server_metadata_check_state_e {
  /// Metadata check pedning
  BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_PENDING,
  /// Metadata check error
  BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_ERROR,
  /// Metadata check successful
  BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_SUCCESS
} sl_btmesh_fw_update_server_metadata_check_state_t;

/// Definitions taken from BT Mesh Specification v1.1
typedef enum sl_btmesh_fw_update_server_additional_information_e {
  /// No changes to node composition data.
  BTMESH_FW_UPDATE_SERVER_ADDITIONAL_INFORMATION_NO_CHANGE = 0x0,
  /// Node composition data changed. The node does not support remote
  /// provisioning.
  BTMESH_FW_UPDATE_SERVER_ADDITIONAL_INFORMATION_COMP_DATA_CHANGE_NO_REMOTE_PROV = 0x1,
  /// Node composition data changed, and remote provisioning is supported. The
  /// node supports remote provisioning and composition data page 0x80. Page
  /// 0x80 contains different composition data than page 0x0.
  BTMESH_FW_UPDATE_SERVER_ADDITIONAL_INFORMATION_COMP_DATA_CHANGE_REMOTE_PROV = 0x2,
  /// Node unprovisioned. The node is unprovisioned after successful application
  /// of a verified firmware image.
  BTMESH_FW_UPDATE_SERVER_ADDITIONAL_INFORMATION_UNPROVISION = 0x3,
  /// Start of reserved values
  BTMESH_FW_UPDATE_SERVER_ADDITIONAL_INFORMATION_RESERVED_START = 0x4
} sl_btmesh_fw_update_server_additional_information_t;

/***************************************************************************//**
 * User callback for determining the maximum chunk size of verification
 *
 * Used to determine how big chunks can be for
 * @ref sl_btmesh_fw_update_server_verify_step
 *
 * @param[in] blob_id Identifier of the BLOB to be verified
 * @param[out] verify_chunk_buffer Verification buffer. User needs to pass the
 *                                 verification buffer to the framework. User
 *                                 also needs to free memory if it was allocated
 *                                 on heap, which could be done in
 *                                 @ref sl_btmesh_fw_update_server_apply.
 *                                 If it's set to NULL, than no data is read
 *                                 from storage automatically during
 *                                 verification.
 * @param[out] verify_chunk_size Size of verification chunk. Progress
 *                               calculation is based on this value.
 * @param[in] blob_size Size of the BLOB to be verified
 *
 * @return Current state of verification
 * @retval BTMESH_FW_UPDATE_SERVER_VERIFY_PENDING If further processing required
 * @retval BTMESH_FW_UPDATE_SERVER_VERIFY_ERROR In case of an error
 * @retval BTMESH_FW_UPDATE_SERVER_VERIFY_SUCCESS In case verification is done and
 *                                        successful
 ******************************************************************************/
sl_btmesh_fw_update_server_verify_state_t
sl_btmesh_fw_update_server_verify_start(sl_bt_uuid_64_t const *const blob_id,
                                        uint8_t **const verify_chunk_buffer,
                                        uint32_t *const verify_chunk_size,
                                        const uint32_t blob_size);

/***************************************************************************//**
 * User callback to execute one step of the verification
 *
 * Receives a chunk of data equal to or less in size defined with
 * @ref sl_btmesh_fw_update_server_verify_start
 *
 * @param[in] data Buffered data
 * @param[in] len Length of the buffer
 *
 * @return Current state of verification
 * @retval BTMESH_FW_UPDATE_SERVER_VERIFY_PENDING If further processing required
 * @retval BTMESH_FW_UPDATE_SERVER_VERIFY_ERROR In case of an error
 * @retval BTMESH_FW_UPDATE_SERVER_VERIFY_SUCCESS In case verification is done and
 *                                        successful
 ******************************************************************************/
sl_btmesh_fw_update_server_verify_state_t
sl_btmesh_fw_update_server_verify_step(void const *data, const uint32_t len);

/***************************************************************************//**
 * User callback to update the user interface with verification progress
 *
 * @param[in] status Verification status
 * @param[in] progress Number of verified bytes
 * @param[in] size Total number of bytes which shall be verified
 *
 * If @p FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD is not zero then it
 * specifies the period of this function call in order to limit the user
 * interface update rate. If the macro is zero then this function is called
 * whenever verification is active and progress is made.
 ******************************************************************************/
extern void
sl_btmesh_fw_update_server_verify_progress_ui_update(sl_btmesh_fw_update_server_verify_state_t status,
                                                     uint32_t progress,
                                                     uint32_t size);

/***************************************************************************//**
 * User callback indicating start of metadata check
 *
 * @param[in] metadata Buffered metadata
 * @param[in] len Metadata length
 * @param[out] additional_information Used in BT Mesh response to metadata check
 *
 * @return Current state of metadata check
 * @retval BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_PENDING If further processing required
 * @retval BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_ERROR In case of an error
 * @retval BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_SUCCESS In case metadata check is done
 *                                                and successful
 ******************************************************************************/
sl_btmesh_fw_update_server_metadata_check_state_t
sl_btmesh_fw_update_server_metadata_check_start(void const *metadata,
                                                const uint8_t len,
                                                sl_btmesh_fw_update_server_additional_information_t *const additional_information);

/***************************************************************************//**
 * User callback executing one step of metadata check
 *
 * @param[out] additional_information Used in BT Mesh response to metadata check
 *
 * @return Current state of metadata check
 * @retval BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_PENDING If further processing required
 * @retval BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_ERROR In case of an error
 * @retval BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_SUCCESS In case metadata check is done
 *                                                and successful
 ******************************************************************************/
sl_btmesh_fw_update_server_metadata_check_state_t
sl_btmesh_firmware_update_server_metadata_check_step(sl_btmesh_fw_update_server_additional_information_t *additional_information);

/***************************************************************************//**
 * User callback indicating update start
 *
 * Called after metadata check is done.
 *
 * Can be redefined to accommodate user application functionality.
 *
 * @param[in] blob_id Identifier of the BLOB containing firmware
 ******************************************************************************/
void sl_btmesh_fw_update_server_update_start(sl_bt_uuid_64_t const *const blob_id);

/***************************************************************************//**
 * User callback indicating update cancellation
 *
 * Can be redefined to accommodate user application functionality.
 ******************************************************************************/
void sl_btmesh_fw_update_server_update_canceled(void);

/***************************************************************************//**
 * User callback indicating update abort
 *
 * Can be redefined to accommodate user application functionality.
 ******************************************************************************/
void sl_btmesh_fw_update_server_update_aborted(void);

/***************************************************************************//**
 * User callback indicating firmware apply request
 *
 * Can be redefined to accommodate user application functionality.
 ******************************************************************************/
void sl_btmesh_fw_update_server_apply(void);

/***************************************************************************//**
 * Used to retrieve information about firmware stored on the device for DFU
 ******************************************************************************/
sl_status_t mesh_platform_get_installed_firmware_information(uint8_t index,
                                                             uint8_t *fwid_len,
                                                             const uint8_t **fwid_ptr,
                                                             uint8_t *uri_len,
                                                             const uint8_t **uri_ptr);

/** @} end mesh_fw_update_server_api */

/** @} end mesh_fw_update_server */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SL_BTMESH_FIRMWARE_UPDATE_SERVER_API_H

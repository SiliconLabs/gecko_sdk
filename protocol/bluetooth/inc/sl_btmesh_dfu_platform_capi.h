/***************************************************************************//**
 * @file sl_btmesh_dfu_platform_capi.h
 * @brief Silicon Labs Bluetooth Mesh DFU Model Platform API
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_BTMESH_DFU_PLATFORM_CAPI_H
#define SL_BTMESH_DFU_PLATFORM_CAPI_H

#include <stddef.h>
#include <stdint.h>

#include <sl_status.h>

/**
 * @defgroup fw_dist_server_platform Firmware Distribution Server Platform API
 *
 * @{
 */

/**
 * Firmware information
 */
typedef struct {
  uint32_t size; // Actual over-the-air size, not including any flash / bootloader slot overhead etc.
  const uint8_t *p_blob_id;
  uint8_t metadata_len;
  const uint8_t *p_metadata;
  uint8_t fwid_len;
  const uint8_t *p_fwid;
  uint16_t index;
} mesh_dfu_dist_server_fw_info_t;

/**
 * @brief Get current number of images stored
 *
 * Get current number of images stored.
 *
 * The platform must provide an implementation of the api for Mesh stack.
 *
 * @param element_index The index of the element of Distribution Server
 * @param count Pointer to output variable for current number of images stored
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 */
sl_status_t mesh_platform_dfu_dist_server_get_fw_count(size_t element_index, uint16_t *count);

/**
 * @brief Get current number of free bytes
 *
 * Get current number of free bytes.
 *
 * The platform must provide an implementation of the api for Mesh stack.
 *
 * @param element_index The index of the element of Distribution Server
 * @param bytes Pointer to output variable for current number of free bytes
 *
 * @return SL_STATUS_OK if successful, SL_STATUS_NOT_INITIALIZED if FW list was not initialized.
 */
sl_status_t mesh_platform_dfu_dist_server_get_remaining_space(size_t element_index, uint32_t *bytes);

/**
 * @brief Get firmware with Firmware List index
 *
 * Get firmware with Firmware List index.
 *
 * The platform must provide an implementation of the api for Mesh stack.
 *
 * All output parameter pointers are optional to provide; any NULL pointers will be ignored.
 *
 * @param element_index The index of the element of the Distribution Server
 * @param fw_index The firmware index from which the info metadata is retuned
 * @param info Pointer to firmware information to be returned ::mesh_dfu_dist_server_fw_info_t.
 *             Data shall be valid as long as the the firmware is present in the Firmware List.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 */
sl_status_t mesh_platform_dfu_dist_server_get_fw_by_index(size_t element_index,
                                                          uint16_t fw_index, mesh_dfu_dist_server_fw_info_t *info);

/**
 * @brief Get firmware with FWID
 *
 * Get firmware with FWID.
 *
 * The platform must provide an implementation of the api for Mesh stack.
 *
 * All output parameter pointers are optional to provide; any NULL pointers will be ignored.
 *
 * @param element_index The index of the element of the Distribution Server
 * @param fwid_len Length of firmware id
 * @param fwid Pointer to firmware id
 * @param info Pointer to firmware information to be returned ::mesh_dfu_dist_server_fw_info_t
 *             Data shall be valid as long as the the firmware is present in the Firmware List.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 */
sl_status_t mesh_platform_dfu_dist_server_get_fw_by_fwid(size_t element_index,
                                                         uint8_t fwid_len,
                                                         const uint8_t *fwid,
                                                         mesh_dfu_dist_server_fw_info_t *info);

/** @} */

#endif

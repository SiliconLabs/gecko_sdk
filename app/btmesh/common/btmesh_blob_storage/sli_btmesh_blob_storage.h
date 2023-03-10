/***************************************************************************//**
 * @file
 * @brief Interface header for BLOB storage component internal interfaces
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

#ifndef SLI_BTMESH_BLOB_STORAGE_H
#define SLI_BTMESH_BLOB_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * Initializes the storage erase functionality
 ******************************************************************************/
void sli_btmesh_blob_storage_erase_init(void);

/***************************************************************************//**
 * Read data from bootloader and stores it in the cache
 ******************************************************************************/
void sli_btmesh_blob_storage_sync(void);

/***************************************************************************//**
 * Query status of the slot
 *
 * @param[in] slot_id Index of the slot
 *
 * @return Status of the slot
 * @retval SL_BTMESH_BLOB_STORAGE_STATUS_EMPTY If slot is empty
 * @retval SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED If data is present and invalid
 * @retval SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED If data is present and valid
 * @retval SL_BTMESH_BLOB_STORAGE_STATUS_INTERNAL_ERROR Some internal error occurred
 */
sl_btmesh_blob_storage_status_t sli_btmesh_blob_storage_get_slot_status(uint32_t slot_id);

/***************************************************************************//**
 * Check if BLOB ID is stored in any of the slots and identifies it.
 *
 * @param[in] blob_id BLOB ID inquired about
 *
 * @return Identifier of the slot containing the identified BLOB
 * @retval UINT32_MAX In case no slot is found
 ******************************************************************************/
uint32_t sli_btmesh_blob_storage_get_slot_id(sl_bt_uuid_64_t const *blob_id);

/***************************************************************************//**
 * Extracts footer information assigned to a given slot, belonging to an
 * application identifier.
 *
 * @param slot_id Index of the slot
 * @param[in] app_id Identifier of the application layer user
 * @param[out] buffer Pointer to footer buffer
 * @param[inout] length Length of the buffer; contains the length of the data
 *                      read in case of success
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of successful reading
 * @retval SL_STATUS_NOT_FOUND If app_id and blob_id don't identify a footer
 * @retval SL_STATUS_INVALID_PARAMETER If buffer is too short
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
sl_status_t sli_btmesh_blob_storage_get_app_footer(uint32_t slot_id,
                                                   uint16_t app_id,
                                                   void *buffer,
                                                   uint16_t *length);
/***************************************************************************//**
 * Check if BLOB is managed.
 *
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @param[in] slot_id Index of the slot
 *
 * @return Boolean value
 * @retval true BLOB is managed
 * @retval false Slot isn't managed
 ******************************************************************************/
bool sli_btmesh_blob_storage_is_managed(uint32_t slot_id);

/***************************************************************************//**
 * Check if slot is managed by a specific owner.
 *
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @param[in] slot_id Index of the slot
 * @param[in] owner_id Identifier of expected owner
 *
 * @return Boolean value
 * @retval true BLOB belongs to the specified owner
 * @retval false Slot belongs to another owner or Slot is not managed or
 *   BLOB does not exist
 ******************************************************************************/
bool sli_btmesh_blob_storage_is_managed_by_owner(uint32_t slot_id,
                                                 uint16_t owner_id);

/***************************************************************************//**
 * Invalidate BLOB footer in the requested slot
 *
 * @param[in] slot_id Identifier of slot where BLOB footer shall be invalidated
 * @param[in] force If false then invalidation fails in case of any active
 *   asynchronous delete operation otherwise it is executed unconditionally.
 *
 * @return Result code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_BUSY In case of active delete operation (if force is false)
 * @retval SL_STATUS_FAIL In case of internal API error
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case storage writing has failed
 ******************************************************************************/
sl_status_t sli_blob_storage_invalidate_slot(uint32_t slot_id,
                                             bool force);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* SLI_BTMESH_BLOB_STORAGE_H */

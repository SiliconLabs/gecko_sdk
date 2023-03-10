/***************************************************************************//**
 * @file
 * @brief Interface header for BLOB storage component intended for general use
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
#ifndef SL_BTMESH_BLOB_STORAGE_H
#define SL_BTMESH_BLOB_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * @addtogroup blob_storage BLOB Storage
 * @{
 ******************************************************************************/

typedef enum sl_btmesh_blob_storage_status_e {
  /// Slot is empty
  SL_BTMESH_BLOB_STORAGE_STATUS_EMPTY,
  /// Slot data is corrupted
  ///
  /// \li Data present, but no footer
  /// \li Footer present, but no data
  /// \li Footer invalid
  SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED,
  /// Slot has data and is valid
  SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED,
  /// Internal API error
  SL_BTMESH_BLOB_STORAGE_STATUS_INTERNAL_ERROR
} sl_btmesh_blob_storage_status_t;

typedef enum sl_btmesh_blob_storage_delete_state_e {
  /// Asynchronous delete inactive
  SL_BTMESH_BLOB_STORAGE_DELETE_INACTIVE,
  /// Asynchronous delete active and busy
  SL_BTMESH_BLOB_STORAGE_DELETE_BUSY,
  /// Asynchronous delete has failed
  SL_BTMESH_BLOB_STORAGE_DELETE_FAILED,
  /// Asynchronous delete has succeeded
  SL_BTMESH_BLOB_STORAGE_DELETE_SUCCESS
} sl_btmesh_blob_storage_delete_state_t;

/// Cached data about a certain slot
typedef struct {
  /// BLOB ID contained in the slot
  sl_bt_uuid_64_t blob_id;
  /// Size of the BLOB residing in the slot
  uint32_t blob_size;
  /// Status of the slot (empty or otherwise)
  sl_btmesh_blob_storage_status_t status;
} sl_btmesh_blob_storage_slot_metadata_cache_t;

/***************************************************************************//**
 * Initializes the storage wrapper
 ******************************************************************************/
void sl_btmesh_blob_storage_init(void);

/***************************************************************************//**
 * Deinitializes the storage wrapper
 ******************************************************************************/
void sl_btmesh_blob_storage_deinit(void);

/***************************************************************************//**
 * Reads data from the identified BLOB into a buffer
 *
 * @param[in] blob_id Identifier of the BLOB
 * @param[in] offset Offset relative to BLOB start, where read should start
 * @param[inout] len Length of the buffer; modified if there's less data then
 *                   buffer could fit
 * @param[out] buffer Buffer in which data is read
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND In case BLOB has not been find
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_read(sl_bt_uuid_64_t const *blob_id,
                                        uint32_t offset,
                                        uint32_t *len,
                                        void *buffer);

/***************************************************************************//**
 * Starts writing procedure
 *
 * Sets internal state variables to correspond to writing a BLOB.
 * @param[in] blob_id Identifier of the BLOB about to be written into storage
 * @param[in] size Size of the BLOB about to be written into storage
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_ALREADY_EXISTS In case BLOB ID already exists in storage
 * @retval SL_STATUS_WOULD_OVERFLOW In case BLOB is too big to fit
 * @retval SL_STATUS_NO_MORE_RESOURCE In case no slot is available
 * @retval SL_STATUS_BUSY In case BLOB Storage is processing an async. request
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_write_start(sl_bt_uuid_64_t const *blob_id,
                                               uint32_t size);

/***************************************************************************//**
 * Writes data into storage.
 *
 * @pre @ref sl_btmesh_blob_storage_write_start must be called first.
 * @param[in] offset Offset of the data inside the BLOB. Must be
 *                   @ref SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL aligned.
 * @param[in] len Length of the data
 * @param[in] data Pointer to the data
 *
 * @return Result of write operation
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FLASH_WRITE_INHIBITED In case of non-word aligned offset
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case storage programming failed
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_write(uint32_t offset,
                                         uint32_t len,
                                         void *data);

/***************************************************************************//**
 * Retrieves a pointer to the cache
 *
 * @param cache[out] Pointer to the buffer of a pointer for cache start
 * @param len[out] Pointer to the length cache
 ******************************************************************************/
void sl_btmesh_blob_storage_get_cache(sl_btmesh_blob_storage_slot_metadata_cache_t const **cache,
                                      uint32_t *len);

/***************************************************************************//**
 * Verifies the BLOB to be considered consistent
 *
 * @return Verification result
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_INVALID_STATE In case less data has been written than
 *                                 indicated with
 *                                 @ref sl_btmesh_blob_storage_write_start or
 *                                 writing has not been started properly
 * @retval SL_STATUS_FAIL In case of internal API error
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case writing validity info into
 *                                        storage has failed
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_verify(void);

/***************************************************************************//**
 * Invalidates BLOB footer
 *
 * @param[in] blob_id Identifier of the BLOB to invalidate
 *
 * @return Result code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND In case BLOB identifier is not found
 * @retval SL_STATUS_FAIL In case of internal API error
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case storage writing has failed
 * @retval SL_STATUS_BUSY In case BLOB Storage is processing an async. request
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_invalidate(sl_bt_uuid_64_t const *blob_id);

/***************************************************************************//**
 * Invalidates all valid BLOB footer which belongs to a specific owner
 *
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @param[in] owner_id Identifier of owner
 *
 * @return Result code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FAIL In case of internal API error
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case storage writing has failed
 * @retval SL_STATUS_BUSY In case BLOB Storage is processing an async. request
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_invalidate_by_owner(uint16_t owner_id);

/***************************************************************************//**
 * Invalidates all valid BLOB footer
 *
 * @return Result code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FAIL In case of internal API error
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case storage writing has failed
 * @retval SL_STATUS_BUSY In case BLOB Storage is processing an async. request
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_invalidate_all(void);

/***************************************************************************//**
 * Deletes a BLOB from storage
 *
 * @param[in] blob_id Identifier of the BLOB to be deleted
 *
 * @return Result of erase
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND In case no BLOB has been identified in storage
 * @retval SL_STATUS_FLASH_ERASE_FAILED In case erase has failed
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete(sl_bt_uuid_64_t const *blob_id);

/***************************************************************************//**
 * Start asynchronous delete of a BLOB
 *
 * @param[in] blob_id Identifier of the BLOB to be deleted
 *
 * @see sl_btmesh_blob_storage_get_erase_error_code
 *
 * @return Request status
 * @retval SL_BTMESH_OK Request successful
 * @retval SL_BTMESH_BUSY Erase handler busy
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_start(sl_bt_uuid_64_t const *blob_id);

/***************************************************************************//**
 * Deletes all BLOB from storage which belongs to a specific owner
 *
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @param[in] owner_id Identifier of owner
 *
 * @return Result of erase
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND No managed slot was found which belongs to the owner
 * @retval SL_STATUS_FLASH_ERASE_FAILED In case erase has failed
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_managed_by_owner(uint16_t owner_id);

/***************************************************************************//**
 * Start asynchronous delete of BLOBs that are unmanaged
 *
 * @see sl_btmesh_blob_storage_get_erase_error_code
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @param[in] owner_id Identifier of owner
 *
 * @return Request status
 * @retval SL_BTMESH_OK Request successful
 * @retval SL_BTMESH_BUSY Erase handler busy
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_managed_by_owner_start(uint16_t owner_id);

/***************************************************************************//**
 * Deletes all BLOBs from storage
 *
 * @return Result of erase
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FLASH_ERASE_FAILED In case erase has failed
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_all(void);

/***************************************************************************//**
 * Start asynchronous delete of all BLOBs
 *
 * @see sl_btmesh_blob_storage_get_erase_error_code
 *
 * @return Request status
 * @retval SL_BTMESH_OK Request successful
 * @retval SL_BTMESH_BUSY Erase handler busy
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_all_start(void);

/***************************************************************************//**
 * Clear slots with invalid data
 *
 * @return Result of erase
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND No invalid slot was found
 * @retval SL_STATUS_FLASH_ERASE_FAILED In case erase has failed
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_invalid_slots(void);

/***************************************************************************//**
 * Start asynchronous delete of invalid BLOBs
 *
 * @see sl_btmesh_blob_storage_get_erase_error_code
 *
 * @return Request status
 * @retval SL_BTMESH_OK Request successful
 * @retval SL_BTMESH_BUSY Erase handler busy
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_invalid_slots_start(void);

/***************************************************************************//**
 * Clear slots that are unmanaged
 *
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @return Result of erase
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND No unmanaged slot was found
 * @retval SL_STATUS_FLASH_ERASE_FAILED In case erase has failed
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_unmanaged_slots(void);

/***************************************************************************//**
 * Start asynchronous delete of BLOBs that are unmanaged
 *
 * @see sl_btmesh_blob_storage_get_erase_error_code
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @return Request status
 * @retval SL_BTMESH_OK Request successful
 * @retval SL_BTMESH_BUSY Erase handler busy
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_delete_unmanaged_slots_start(void);

/***************************************************************************//**
 * Set asynchronous delete separation time
 *
 * Asynchronous delete separation time is measured in milliseconds between two
 * asynchronous delete steps. The BLOB storage async delete is performed in
 * multiple steps and each delete step blocks the code execution.
 * If delete steps are executed too often then it could starve other timing
 * sensitive SW components so delete separation time feature can be used to
 * prevent this scenario.
 *
 * @param[in] separation_time_ms Separation time between two async erase steps
 *
 * @return Request status
 * @retval SL_STATUS_OK In case of success
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_set_delete_separation_time(uint16_t separation_time_ms);

/***************************************************************************//**
 * Checks whether BLOB identified is present in storage
 *
 * @param[in] blob_id
 *
 * @return Boolean value
 * @retval true BLOB is present
 * @retval false BLOB is not present
 ******************************************************************************/
bool sl_btmesh_blob_storage_is_present(sl_bt_uuid_64_t const *blob_id);

/***************************************************************************//**
 * Queries the BLOB size
 *
 * @param[in] blob_id Identifier of the BLOB inquired about
 * @param[out] blob_size Length of the BLOB
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND In case no BLOB has been identified
 * @retval SL_STATUS_INVALID_SIGNATURE In case invalid internal BLOB signature
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_get_blob_size(sl_bt_uuid_64_t const *blob_id,
                                                 uint32_t *blob_size);

/***************************************************************************//**
 * Calculates the size of application specific footer on BLOB storage medium.
 *
 * @note BLOB storage stores some additional metadata (id, length) with the
 *   footer data and it takes into consideration the alignment requirements of
 *   the underlying medium.
 *
 * @param[in] footer_data_length Length of the application specific footer data
 *
 * @return Size of application specific footer on BLOB storage medium.
 ******************************************************************************/
uint32_t sl_btmesh_blob_storage_calc_app_footer_size(uint16_t footer_data_length);

/***************************************************************************//**
 * Writes application specific footer into storage belonging to identified the
 * BLOB and application
 *
 * @param[in] blob_id Identifier of the BLOB
 * @param[in] footer Footer data
 * @param[in] app_id Identifier of the application data. Must be unique to the
 *                   application layer user in the compiled software. Used to
 *                   identify footer.
 * @param[in] length Length of the data
 *
 * @return Result of footer write
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case write failed
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_write_app_footer(sl_bt_uuid_64_t const *blob_id,
                                                    void const *footer,
                                                    uint16_t app_id,
                                                    uint16_t length);

/***************************************************************************//**
 * Queries footer information length assigned to a given BLOB, belonging to an
 * application identifier.
 *
 * @param[in] blob_id Identifier of the BLOB
 * @param[in] app_id Identifier of the application data
 * @param[out] length Length of application data in case of success
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of successful query
 * @retval SL_STATUS_NOT_FOUND If app_id and blob_id don't identify a footer
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_get_app_footer_length(sl_bt_uuid_64_t const *blob_id,
                                                         uint16_t app_id,
                                                         uint16_t *length);

/***************************************************************************//**
 * Extracts footer information assigned to a given BLOB, belonging to an
 * application identifier.
 *
 * @param[in] blob_id Identifier of the BLOB
 * @param[in] app_id Identifier of the application data
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
sl_status_t sl_btmesh_blob_storage_get_app_footer(sl_bt_uuid_64_t const *blob_id,
                                                  uint16_t app_id,
                                                  void *buffer,
                                                  uint16_t *length);

/***************************************************************************//**
 * Set BLOB to be managed, meaning it won't be deleted.
 *
 * Each managed BLOB is managed by a specific owner which is stored with BLOB.
 * Unmanaged BLOBs will be deleted when out of available space.
 *
 * @param[in] blob_id Identifier of the BLOB
 * @param[in] owner_id Identifier of owner which the BLOB belongs to
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case write failed
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_set_managed(sl_bt_uuid_64_t const *blob_id,
                                               uint16_t owner_id);

/***************************************************************************//**
 * Check if BLOB is managed.
 *
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @param[in] blob_id Identifier of the BLOB
 *
 * @return Boolean value
 * @retval true BLOB is managed
 * @retval false BLOB isn't managed or BLOB does not exist
 ******************************************************************************/
bool sl_btmesh_blob_storage_is_managed(sl_bt_uuid_64_t const *blob_id);

/***************************************************************************//**
 * Check if BLOB is managed by a specific owner.
 *
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @param[in] blob_id Identifier of the BLOB
 * @param[in] owner_id Identifier of expected owner
 *
 * @return Boolean value
 * @retval true BLOB belongs to the specified owner
 * @retval false BLOB belongs to another owner or BLOB is not managed or
 *   BLOB does not exist
 ******************************************************************************/
bool sl_btmesh_blob_storage_is_managed_by_owner(sl_bt_uuid_64_t const *blob_id,
                                                uint16_t owner_id);

/***************************************************************************//**
 * Return the size of managed flag on BLOB storage medium.
 *
 * BLOB storage needs to distinguish managed and unmanaged BLOBs so it marks
 * managed BLOBs as such which requires some space on the medium.
 *
 * @return Size of managed flag on BLOB storage medium
 ******************************************************************************/
uint32_t sl_btmesh_blob_storage_get_managed_flag_size(void);

/***************************************************************************//**
 * Searches BLOBs managed by a specific owner and provides the BLOB ID of the
 * requested occurrence.
 *
 * The search order for managed BLOBs of an owner is not specified but it is
 * guaranteed that the order does not change unless new BLOB is added or an
 * existing BLOB of the same owner is removed (delete, invalidate) from the
 * BLOB storage.
 *
 * When a managed BLOB belonging to an owner is removed from BLOB storage then
 * occurrence_idx of BLOBs with same owner is decremented if the occurrence_idx
 * of the BLOB was greater than the occurrence_idx of the removed BLOB otherwise
 * the occurrence_idx does not change. In other words the BLOBs are shifted to
 * lower indexes.
 *
 * If a new managed BLOB is added by an owner to the BLOB storage then the
 * search order of BLOBs with the same owner may change arbitrarily because
 * it is not guaranteed which occurrence_idx the added BLOB is assigned to.
 *
 * @see sl_btmesh_blob_storage_set_managed
 *
 * @param[in] owner_id Identifier of owner which the BLOB belongs to
 * @param[in] occurrence_idx Selects a BLOB from BLOBs managed by the same owner.
 *   Zero means the first BLOB with matching owner found during the search.
 * @param[out] blob_id Identifier of the BLOB
 *
 * @return Result of managed BLOB ID get operation
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND If no BLOBs are found with owner_id or the
 *   occurrence_idx is greater or equal to the number of BLOBs managed by owner
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_get_blob_id_by_owner(uint16_t owner_id,
                                                        uint32_t occurrence_idx,
                                                        sl_bt_uuid_64_t *blob_id);

/***************************************************************************//**
 * Searches for a specific app_id and data in the footer of each valid BLOB and
 * returns the BLOB ID of the first match
 *
 * @param[in] app_id Identifier of the application data
 * @param[in] expected_footer Expected footer data for comparison
 * @param[in] length Length of the data
 * @param[out] blob_id Identifier of the BLOB of the first match
 *
 * @return Result of footer based BLOB ID query (propagates other internal
 *         errors)
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND If app_id is not found or the data is different
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
sl_status_t sl_btmesh_blob_storage_get_blob_id_by_footer(uint16_t app_id,
                                                         const void *expected_footer,
                                                         uint16_t length,
                                                         sl_bt_uuid_64_t *blob_id);

/***************************************************************************//**
 * Queries total space for BLOB data storage in bytes (used + empty)
 *
 * @return Total space in bytes
 ******************************************************************************/
uint32_t sl_btmesh_blob_storage_get_total_space(void);

/***************************************************************************//**
 * Queries remaining empty bytes in the BLOB storage
 *
 * @param[in] include_unmanaged_blobs If true then unmanaged blobs are calculated
 *   into the remaining empty space.
 *
 * @return Remaining empty bytes
 ******************************************************************************/
uint32_t sl_btmesh_blob_storage_get_remaining_space(bool include_unmanaged_blobs);

/***************************************************************************//**
 * Queries maximum BLOB size which can be stored if the whole BLOB storage is
 * empty
 *
 * @note This might not be available even if one BLOB is stored
 *
 * @return Maximum BLOB size
 ******************************************************************************/
uint32_t sl_btmesh_blob_storage_get_max_blob_size(void);

/***************************************************************************//**
 * Queries maximum BLOB size which can be stored in the free space of BLOB
 * storage
 *
 * @param[in] include_unmanaged_blobs If true then unmanaged blobs are calculated
 *   into the maximum free BLOB size.
 *
 * @return Maximum supported BLOB size in free part of the BLOB storage
 ******************************************************************************/
uint32_t sl_btmesh_blob_storage_get_max_blob_size_free(bool include_unmanaged_blobs);

/***************************************************************************//**
 * Queries maximum number of BLOBs which can be stored
 *
 * @return Maximum number of BLOBs
 ******************************************************************************/
uint32_t sl_btmesh_blob_storage_get_max_blob_count(void);

/***************************************************************************//**
 * Queries the error code/state of the asynchronous erase
 *
 * @return State of asynchronous erase
 * @retval SL_BTMESH_BLOB_STORAGE_DELETE_INACTIVE If erase is inactive
 * @retval SL_BTMESH_BLOB_STORAGE_DELETE_BUSY If erase is ongoing
 * @retval SL_BTMESH_BLOB_STORAGE_DELETE_FAILED If erase has failed
 * @retval SL_BTMESH_BLOB_STORAGE_DELETE_SUCCESS If erase is successful
 ******************************************************************************/
sl_btmesh_blob_storage_delete_state_t sl_btmesh_blob_storage_get_erase_error_code(void);

/***************************************************************************//**
 * Handles the asynchronous erase state machine
 ******************************************************************************/
void sl_btmesh_blob_storage_delete_step_handle(void);

/***************************************************************************//**
 * Check if BLOB Storage allows the system to sleep
 *
 * @return If it is ok to sleep
 * @retval true The system is allowed to sleep
 * @retval false The system shall be kept awake
 *
 * Asynchronous erase requires the device to stay awake to finish.
 ******************************************************************************/
bool sl_btmesh_blob_storage_is_ok_to_sleep();

/** @} end blob_storage */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //SL_BTMESH_BLOB_STORAGE_H

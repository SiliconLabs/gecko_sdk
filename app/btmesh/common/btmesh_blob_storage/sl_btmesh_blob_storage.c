/***************************************************************************//**
 * @file
 * @brief Implementation of BLOB storage component
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

#include <stdint.h>
#include <string.h>

#include "sl_common.h"

#include "sl_malloc.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT
#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT
#include "app_assert.h"

#include "btl_interface.h"
#include "btl_interface_storage.h"
#include "sl_bgapi.h"
#include "sl_status.h"

#include "sl_btmesh_blob_storage.h"
#include "sl_btmesh_blob_storage_app_id.h"
#include "sl_btmesh_blob_storage_config.h"
#include "sli_btmesh_blob_storage.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup blob_storage BLOB Storage
 * @{
 ******************************************************************************/

/// Align the input value to the following word barrier
#define sli_blob_storage_align_to_next_word(_val)          \
  (((_val) + SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL - 1) \
   & (~(SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL - 1)))
/// Align the input value to the previous word barrier
#define sli_blob_storage_align_to_prev_word(_val) \
  ((_val) & (~(SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL - 1)))
/// Calculates the number of bytes over alignment
#define sli_blob_storage_word_align_remainder(_val) \
  ((_val) % SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL)
/// Calculates the number of bytes remaining until the next aligned value
#define sli_blob_storage_word_align_pad_length(_val) \
  (SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL          \
   - sli_blob_storage_word_align_remainder(_val))

#define sli_calc_max_blob_size(slot_size)       \
  (sizeof(blob_storage_footer_t) < (slot_size)) \
  ? ((slot_size) - sizeof(blob_storage_footer_t)) : 0

/// Version of the storage implementation, stored in footer as validity flag
#define STORAGE_VERSION                 2
/// Value to be used as padding for application specific footers
#define APP_FOOTER_PADDING_PATTERN      0xAA
/// Buffer size for @ref blob_storage_compare
#define COMPARE_BUFFER_SIZE             64
/// The biggest alignment supported
#define MAX_ALIGNMENT                   8

/// Structure of the application specific footer metadata
PACKSTRUCT(typedef struct {
  /// Application identifier to identify footer user
  uint16_t app_id;
  /// Length of the footer and this metadata
  uint16_t length;
}) blob_storage_app_footer_metadata_t;

/// Footer of a BLOB stored at the end of the slot
PACKSTRUCT(typedef struct {
  /// Validity flag
  uint8_t validity_flag[MAX_ALIGNMENT];
  /// Identifier of BLOB in storage slot
  sl_bt_uuid_64_t blob_id;
  /// Size of BLOB in storage slot
  uint32_t blob_size;
  /// Reserved
  uint8_t rfu0;
  /// Reserved
  uint8_t rfu1;
  /// Reserved
  uint8_t rfu2;
  /// Footer version
  uint8_t version;
}) blob_storage_footer_t;

static struct {
  /// Index of the currently written slot (i.e. Slot ID)
  uint32_t current_index;
  /// Number of bytes written during the current write process
  uint32_t written_bytes;
  /// Flag indicating whether padding has already been done
  ///
  /// Padding is used to align written data to needed length. Can occur only once
  /// during writing into one slot.
  bool padding;
  /// Length of the cache
  uint32_t cache_length;
  /// Pointer to the slot data cache
  sl_btmesh_blob_storage_slot_metadata_cache_t *slot_cache;
} blob_storage = { .slot_cache = NULL }; ///< Storage API state representation

/***************************************************************************//**
 * Check the current status of a slot identified by Slot ID
 *
 * @param[in] slot_id The ID of the slot inquired about
 *
 * @return Status of the slot
 * @retval EMPTY In case the slot doesn't have any data
 * @retval CORRUPTED In case data is present but footer is invalid or data is
 *                   not present, but footer is not empty.
 * @retval OCCUPIED In case data is present and footer is valid.
 * @retval INTERNAL_ERROR In case of error in underlying API
 ******************************************************************************/
static sl_btmesh_blob_storage_status_t blob_storage_check_slot_status(uint32_t slot_id);

/***************************************************************************//**
 * Read the footer into the buffer.
 *
 * @note The footer need not be valid for the function to return with a valid
 * footer position.
 *
 * @param[out] footer Buffer for the footer
 * @param[in] slot_id The ID of the slot holding the footer
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FAIL In case of internal error
 * @retval SL_STATUS_INVALID_SIGNATURE In case version is invalid
 ******************************************************************************/
static sl_status_t blob_storage_get_footer(blob_storage_footer_t *footer,
                                           uint32_t slot_id);

/***************************************************************************//**
 * Retrieve a pointer to the footer metadata contained in the slot identified
 * and having the given application identifier.
 *
 * @param[in] slot_id The ID of a BLOB corresponding to the footer
 * @param[in] app_id The ID of the application corresponding to the footer
 * @param[out] metadata Buffer for the metadata
 * @param[out] offset Offset of the metadata
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND If app_id and slot_id doesn't identify any footer
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
static sl_status_t blob_storage_get_app_footer_metadata(uint32_t slot_id,
                                                        uint16_t app_id,
                                                        blob_storage_app_footer_metadata_t *metadata,
                                                        uint32_t *offset);

/***************************************************************************//**
 * Provide the supported maximum BLOB size in the slot
 *
 * @param[in] slot_id The ID of the slot inquired about
 *
 * @return Maximum supported BLOB size in the slot
 ******************************************************************************/
static uint32_t blob_storage_get_max_blob_size_in_slot(uint32_t slot_id);

/***************************************************************************//**
 * Compare specific part of a bootloader storage slot with a RAM buffer
 *
 * @param[in] slot_id Identifier of the storage slot to be compared
 * @param[in] slot_offset Offset in the slot where the comparison shall be started
 * @param[in] expected_data Expected data which shall be compared to storage slot data
 * @param[in] length Number of compared bytes
 * @param[out] comparison_result Comparison result shall be interpreted as memcmp
 *
 * @return Status of the comparison
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
static sl_status_t blob_storage_compare(uint32_t slot_id,
                                        uint32_t slot_offset,
                                        uint8_t const *expected_data,
                                        uint32_t length,
                                        int32_t *comparison_result);

void sl_btmesh_blob_storage_init(void)
{
  BootloaderStorageInformation_t info;
  // Initialize Bootloader
  int32_t bootloader_status = bootloader_init();
  app_assert(bootloader_status == BOOTLOADER_OK,
             "Bootloader initialization failed, error code %ld!",
             bootloader_status);
  // Read storage information from Bootloader
  bootloader_getStorageInfo(&info);

  // Extract number of slots
  blob_storage.cache_length = info.numStorageSlots;

  if (NULL == blob_storage.slot_cache) {
    // Allocate memory to store cached data about slots
    blob_storage.slot_cache =
      sl_calloc(blob_storage.cache_length,
                sizeof(sl_btmesh_blob_storage_slot_metadata_cache_t));
  } else {
    // Free and reallocate
    // Using free and calloc instead of realloc, because calloc clears memory
    sl_free(blob_storage.slot_cache);
    blob_storage.slot_cache =
      sl_calloc(blob_storage.cache_length,
                sizeof(sl_btmesh_blob_storage_slot_metadata_cache_t));
  }

  app_assert(blob_storage.slot_cache != NULL, "Allocation error!");

  // Set write related status parameters to unknown, i.e. 0xFFFFFFFF
  blob_storage.current_index = UINT32_MAX;
  blob_storage.written_bytes = UINT32_MAX;

  // Sync
  sli_btmesh_blob_storage_sync();

  sli_btmesh_blob_storage_erase_init();
}

void sl_btmesh_blob_storage_deinit(void)
{
  // Free allocated memory
  sl_free(blob_storage.slot_cache);
  // Clear status variables
  memset(&blob_storage, 0, sizeof(blob_storage));
}

sl_status_t sl_btmesh_blob_storage_write_start(sl_bt_uuid_64_t const *blob_id,
                                               uint32_t size)
{
  if (sl_btmesh_blob_storage_get_erase_error_code()
      == SL_BTMESH_BLOB_STORAGE_DELETE_BUSY) {
    return SL_STATUS_BUSY;
  }

  sl_status_t ret_val = SL_STATUS_NO_MORE_RESOURCE;

  // Check if BLOB with same ID exists
  if (UINT32_MAX != sli_btmesh_blob_storage_get_slot_id(blob_id)) {
    return SL_STATUS_ALREADY_EXISTS;
  }

  BootloaderStorageSlot_t slot;
  for (uint32_t i = 0; i < blob_storage.cache_length; ++i) {
    if (SL_BTMESH_BLOB_STORAGE_STATUS_EMPTY
        == blob_storage.slot_cache[i].status) {
      bootloader_getStorageSlotInfo(i, &slot);
      // Check if footer and data would fit
      if (size > (slot.length - sizeof(blob_storage_footer_t))) {
        ret_val = SL_STATUS_WOULD_OVERFLOW;
        continue;
      }
      // Copy BLOB ID into cache
      memcpy(&blob_storage.slot_cache[i].blob_id,
             blob_id,
             sizeof(sl_bt_uuid_64_t));
      // Store BLOB size
      blob_storage.slot_cache[i].blob_size = size;
      // Initialize write variables
      blob_storage.written_bytes = 0;
      blob_storage.current_index = i;
      blob_storage.padding = false;
      ret_val = SL_STATUS_OK;
      log_debug("BLOB Storage write start; slot %lu, address 0x%08lX, "
                "length 0x%08lX" NL,
                blob_storage.current_index,
                slot.address,
                slot.length);
      break;
    }
  }
  if (ret_val != SL_STATUS_OK) {
    log_warning("BLOB Storage write start, empty slot not available"NL);
  }

  return ret_val;
}

sl_status_t sl_btmesh_blob_storage_write(uint32_t offset,
                                         uint32_t len,
                                         void *data)
{
  log_debug("BLOB Storage write; offset 0x%08lX, "
            "length %lu cache status %d" NL,
            offset,
            len, blob_storage.slot_cache[blob_storage.current_index].status);
  // Write data into flash
  if (BOOTLOADER_OK
      != bootloader_writeStorage(blob_storage.current_index,
                                 offset,
                                 data,
                                 // Truncate length to alignment (if needed)
                                 sli_blob_storage_align_to_prev_word(len))) {
    return SL_STATUS_FLASH_PROGRAM_FAILED;
  }
  // Check whether length had to be truncated
  if (0 != sli_blob_storage_word_align_remainder(len)) {
    uint8_t buffer[SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL];
    // Padding is only done once at the end of a BLOB. If already padded,
    // inputs are wrong.
    app_assert_s(!blob_storage.padding);
    // Indicate padding
    blob_storage.padding = true;
    // Fill buffer with padding
    memset(buffer, UINT8_MAX, SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL);
    // Copy remainder data into buffer
    memcpy(buffer,
           &((uint8_t *)data)[sli_blob_storage_align_to_prev_word(len)],
           sli_blob_storage_word_align_remainder(len));
    // Write (padded) data into flash
    if (BOOTLOADER_OK
        != bootloader_writeStorage(blob_storage.current_index,
                                   offset
                                   + sli_blob_storage_align_to_prev_word(len),
                                   buffer,
                                   SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL)) {
      return SL_STATUS_FLASH_PROGRAM_FAILED;
    }
  }
  blob_storage.written_bytes += len;
  blob_storage.slot_cache[blob_storage.current_index].status = SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED;
  return SL_STATUS_OK;
}

void sl_btmesh_blob_storage_get_cache(sl_btmesh_blob_storage_slot_metadata_cache_t const **cache,
                                      uint32_t *len)
{
  *cache = blob_storage.slot_cache;
  *len = blob_storage.cache_length;
}

sl_status_t sl_btmesh_blob_storage_verify(void)
{
  if (UINT32_MAX == blob_storage.current_index) {
    return SL_STATUS_INVALID_STATE;
  }
  // Check whether written length equals the received size of BLOB
  if (blob_storage.written_bytes
      != blob_storage.slot_cache[blob_storage.current_index].blob_size) {
    return SL_STATUS_INVALID_STATE;
  }

  blob_storage_footer_t footer;
  memset(&footer, UINT8_MAX, sizeof(blob_storage_footer_t));

  // Copy BLOB ID into footer
  memcpy(&footer.blob_id,
         &blob_storage.slot_cache[blob_storage.current_index].blob_id,
         sizeof(sl_bt_uuid_64_t));

  footer.blob_size =
    blob_storage.slot_cache[blob_storage.current_index].blob_size;
  footer.version = STORAGE_VERSION;

  BootloaderStorageSlot_t slot;
  if (BOOTLOADER_OK
      != bootloader_getStorageSlotInfo(blob_storage.current_index, &slot)) {
    return SL_STATUS_FAIL;
  }

  if (BOOTLOADER_OK != bootloader_writeStorage(blob_storage.current_index,
                                               slot.length - sizeof(blob_storage_footer_t),
                                               (uint8_t*)&footer,
                                               sizeof(blob_storage_footer_t)) ) {
    return SL_STATUS_FLASH_PROGRAM_FAILED;
  }
  // Resync
  sli_btmesh_blob_storage_sync();
  log_debug("BLOB Storage write verified status: %d"NL, blob_storage.slot_cache[blob_storage.current_index].status);
  // Clear status
  blob_storage.current_index = UINT32_MAX;
  blob_storage.written_bytes = UINT32_MAX;
  return SL_STATUS_OK;
}

bool sl_btmesh_blob_storage_is_present(sl_bt_uuid_64_t const *blob_id)
{
  return (UINT32_MAX != sli_btmesh_blob_storage_get_slot_id(blob_id));
}

sl_status_t sl_btmesh_blob_storage_get_blob_size(sl_bt_uuid_64_t const *blob_id,
                                                 uint32_t *blob_size)
{
  uint32_t slot_id = sli_btmesh_blob_storage_get_slot_id(blob_id);
  if (UINT32_MAX == slot_id) {
    return SL_STATUS_NOT_FOUND;
  }

  *blob_size = blob_storage.slot_cache[slot_id].blob_size;

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_storage_read(sl_bt_uuid_64_t const *blob_id,
                                        uint32_t offset,
                                        uint32_t *len,
                                        void *buffer)
{
  uint32_t slot_id = sli_btmesh_blob_storage_get_slot_id(blob_id);
  int32_t r; // Bootloader result

  // If read operation would read over BLOB data, truncate length
  if (blob_storage.slot_cache[slot_id].blob_size < offset + *len) {
    *len = blob_storage.slot_cache[slot_id].blob_size - offset;
  }

  r = bootloader_readStorage(slot_id, offset, buffer, *len);

  switch (r) {
    case BOOTLOADER_OK:
      return SL_STATUS_OK;
    case BOOTLOADER_ERROR_STORAGE_INVALID_SLOT:
      return SL_STATUS_NOT_FOUND;
    default:
      return SL_STATUS_FAIL;
  }
}

sl_status_t sl_btmesh_blob_storage_invalidate(sl_bt_uuid_64_t const *blob_id)
{
  uint32_t slot_id;
  sl_status_t sc;
  slot_id = sli_btmesh_blob_storage_get_slot_id(blob_id);

  if (UINT32_MAX == slot_id) {
    return SL_STATUS_NOT_FOUND;
  }

  sc = sli_blob_storage_invalidate_slot(slot_id, false);

  return sc;
}

sl_status_t sl_btmesh_blob_storage_invalidate_by_owner(uint16_t owner_id)
{
  sl_btmesh_blob_storage_status_t slot_status;
  sl_status_t sc_all = SL_STATUS_OK;

  for (uint32_t slot_id = 0; slot_id < blob_storage.cache_length; ++slot_id) {
    slot_status = blob_storage.slot_cache[slot_id].status;
    if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED == slot_status) {
      sl_bt_uuid_64_t *blob_id = &blob_storage.slot_cache[slot_id].blob_id;
      // Invalidate only those BLOBs which belongs to the specific owner
      if (sl_btmesh_blob_storage_is_managed_by_owner(blob_id, owner_id)) {
        sl_status_t sc = sli_blob_storage_invalidate_slot(slot_id, false);
        // The first error code is returned but all storage slot invalidation
        // is requested because other slot invalidation might succeed
        if ((SL_STATUS_OK != sc) && (SL_STATUS_OK == sc_all)) {
          sc_all = sc;
        }
      }
    }
  }
  return sc_all;
}

sl_status_t sl_btmesh_blob_storage_invalidate_all(void)
{
  sl_btmesh_blob_storage_status_t slot_status;
  sl_status_t sc_all = SL_STATUS_OK;

  for (uint32_t slot_id = 0; slot_id < blob_storage.cache_length; ++slot_id) {
    slot_status = blob_storage.slot_cache[slot_id].status;
    if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED == slot_status) {
      sl_status_t sc = sli_blob_storage_invalidate_slot(slot_id, false);
      // The first error code is returned but all storage slot invalidation
      // is requested because other slot invalidation might succeed
      if ((SL_STATUS_OK != sc) && (SL_STATUS_OK == sc_all)) {
        sc_all = sc;
      }
    }
  }
  return sc_all;
}

uint32_t sl_btmesh_blob_storage_calc_app_footer_size(uint16_t footer_data_length)
{
  return sli_blob_storage_align_to_next_word((uint32_t) footer_data_length
                                             + sizeof(blob_storage_app_footer_metadata_t));
}

sl_status_t sl_btmesh_blob_storage_write_app_footer(sl_bt_uuid_64_t const * blob_id,
                                                    void const * footer,
                                                    uint16_t app_id,
                                                    uint16_t length)
{
  uint32_t slot_id = sli_btmesh_blob_storage_get_slot_id(blob_id);
  BootloaderStorageSlot_t slot;
  uint32_t offset;
  SL_ATTRIBUTE_ALIGN(SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL) blob_storage_app_footer_metadata_t metadata;
  uint16_t write_length;
  const uint16_t remainder_length =
    sli_blob_storage_word_align_remainder(length);
  const uint16_t aligned_length = sli_blob_storage_align_to_prev_word(length);
  const uint16_t padded_length = sli_blob_storage_align_to_next_word(length);

  // Buffer to be used for padding the data, so no allocation is required
  SL_ATTRIBUTE_ALIGN(SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL) uint8_t buffer[SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL];

  if (length == UINT16_MAX) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (BOOTLOADER_OK != bootloader_getStorageSlotInfo(slot_id, &slot)) {
    return SL_STATUS_FAIL;
  }

  // Get offset of first possible footer metadata
  offset = slot.length
           - sizeof(blob_storage_footer_t)
           - sizeof(blob_storage_app_footer_metadata_t);

  bootloader_readStorage(slot_id,
                         offset,
                         (uint8_t*)&metadata,
                         sizeof(blob_storage_app_footer_metadata_t));

  // Length is at the end of the footer. If flash is clear it'll be all ones.
  while (metadata.length != UINT16_MAX) {
    // Offset must be word aligned
    offset -= sl_btmesh_blob_storage_calc_app_footer_size(metadata.length);
    // Read out footer metadata
    bootloader_readStorage(slot_id,
                           offset,
                           (uint8_t*)&metadata,
                           sizeof(blob_storage_app_footer_metadata_t));
    // Check if we happen to venture into the BLOB itself
    if (offset < blob_storage.slot_cache[slot_id].blob_size) {
      return SL_STATUS_WOULD_OVERFLOW;
    }
  }

  // Calculate full length of data to be written
  write_length = sl_btmesh_blob_storage_calc_app_footer_size(length);

  // Calculate offset relative to the start of the empty footer metadata slot
  offset -= write_length - sizeof(blob_storage_app_footer_metadata_t);

  // If write start offset is inside BLOB
  if (offset < blob_storage.slot_cache[slot_id].blob_size) {
    return SL_STATUS_WOULD_OVERFLOW;
  }

  // Assemble footer metadata
  metadata.app_id = app_id;
  metadata.length = length;

  // If pointer is aligned, write it right away
  if (((uintptr_t)footer) % SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL == 0) {
    if (BOOTLOADER_OK
        != bootloader_writeStorage(slot_id, offset, (uint8_t*)footer, aligned_length)) {
      return SL_STATUS_FLASH_PROGRAM_FAILED;
    }
  } else {
    // If pointer is unaligned, use intermediary buffer, which is aligned
    for (uint32_t written = 0; written < aligned_length; written +=
           SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL) {
      memcpy(buffer,
             &((uint8_t*)footer)[written],
             SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL);

      if (BOOTLOADER_OK
          != bootloader_writeStorage(slot_id, offset + written, buffer,
                                     SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL)) {
        return SL_STATUS_FLASH_PROGRAM_FAILED;
      }
    }
  }

  // Initialize padded buffer
  memset(buffer,
         APP_FOOTER_PADDING_PATTERN,
         SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL);

  // Copy data into padded buffer
  memcpy(buffer,
         ((uint8_t *)footer) + aligned_length,
         remainder_length);

  // If alignment is shorter than the metadata, just write the padded data
  if ((SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL
       < sizeof(blob_storage_app_footer_metadata_t))
      // If metadata wouldn't fit into the padded buffer, write padded data
      || (remainder_length > SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL
          - sizeof(blob_storage_app_footer_metadata_t))) {
    if (BOOTLOADER_OK != bootloader_writeStorage(slot_id,
                                                 offset + aligned_length,
                                                 buffer,
                                                 SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL)) {
      return SL_STATUS_FLASH_PROGRAM_FAILED;
    }

    // Reinitialize padded buffer
    memset(buffer,
           APP_FOOTER_PADDING_PATTERN,
           SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL);
  }

  // If metadata wouldn't fit into the buffer, it's sure to be aligned, just write it
  if (SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL
      <= sizeof(blob_storage_app_footer_metadata_t)) {
    if (BOOTLOADER_OK != bootloader_writeStorage(slot_id,
                                                 offset + padded_length,
                                                 (uint8_t *)&metadata,
                                                 sizeof(blob_storage_app_footer_metadata_t))) {
      return SL_STATUS_FLASH_PROGRAM_FAILED;
    }
  } else {
    memcpy(&buffer[SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL
                   - sizeof(blob_storage_app_footer_metadata_t)],
           &metadata,
           sizeof(blob_storage_app_footer_metadata_t));

    if (BOOTLOADER_OK != bootloader_writeStorage(slot_id,
                                                 offset + (padded_length == write_length ? aligned_length : padded_length),
                                                 buffer,
                                                 SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL)) {
      return SL_STATUS_FLASH_PROGRAM_FAILED;
    }
  }

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_storage_set_managed(sl_bt_uuid_64_t const *blob_id, uint16_t owner_id)
{
  return sl_btmesh_blob_storage_write_app_footer(blob_id,
                                                 &owner_id,
                                                 BLOB_STORAGE_APP_ID_MANAGED_FLAG,
                                                 sizeof(owner_id));
}

bool sl_btmesh_blob_storage_is_managed(sl_bt_uuid_64_t const *blob_id)
{
  uint16_t owner_id;
  uint16_t length = sizeof(owner_id);

  sl_status_t sc = sl_btmesh_blob_storage_get_app_footer(blob_id,
                                                         BLOB_STORAGE_APP_ID_MANAGED_FLAG,
                                                         &owner_id,
                                                         &length);
  (void) length;
  if (SL_STATUS_OK == sc) {
    return true;
  }
  return false;
}

bool sli_btmesh_blob_storage_is_managed(uint32_t slot_id)
{
  uint16_t owner_id;
  uint16_t length = sizeof(owner_id);

  sl_status_t sc = sli_btmesh_blob_storage_get_app_footer(slot_id,
                                                          BLOB_STORAGE_APP_ID_MANAGED_FLAG,
                                                          &owner_id,
                                                          &length);
  (void) length;
  if (SL_STATUS_OK == sc) {
    return true;
  }
  return false;
}

bool sl_btmesh_blob_storage_is_managed_by_owner(sl_bt_uuid_64_t const *blob_id,
                                                uint16_t owner_id)
{
  uint16_t blob_owner_id;
  uint16_t length = sizeof(blob_owner_id);
  sl_status_t sc = sl_btmesh_blob_storage_get_app_footer(blob_id,
                                                         BLOB_STORAGE_APP_ID_MANAGED_FLAG,
                                                         &blob_owner_id,
                                                         &length);

  if ((SL_STATUS_OK == sc) && (length == sizeof(blob_owner_id))) {
    return (blob_owner_id == owner_id);
  }
  return false;
}

bool sli_btmesh_blob_storage_is_managed_by_owner(uint32_t slot_id,
                                                 uint16_t owner_id)
{
  uint16_t blob_owner_id;
  uint16_t length = sizeof(blob_owner_id);
  sl_status_t sc = sli_btmesh_blob_storage_get_app_footer(slot_id,
                                                          BLOB_STORAGE_APP_ID_MANAGED_FLAG,
                                                          &blob_owner_id,
                                                          &length);

  if ((SL_STATUS_OK == sc) && (length == sizeof(blob_owner_id))) {
    return (blob_owner_id == owner_id);
  }
  return false;
}

uint32_t sl_btmesh_blob_storage_get_managed_flag_size(void)
{
  return sl_btmesh_blob_storage_calc_app_footer_size(sizeof(uint16_t));
}

sl_status_t sl_btmesh_blob_storage_get_blob_id_by_owner(uint16_t owner_id,
                                                        uint32_t occurrence_idx,
                                                        sl_bt_uuid_64_t *blob_id)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  uint32_t current_occurrence_idx = 0;
  uint32_t cache_length = blob_storage.cache_length;

  for (uint32_t slot_id = 0; slot_id < cache_length; ++slot_id) {
    sl_btmesh_blob_storage_status_t slot_status =
      blob_storage.slot_cache[slot_id].status;
    if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED == slot_status
        && sli_btmesh_blob_storage_is_managed_by_owner(slot_id, owner_id)) {
      if (occurrence_idx <= current_occurrence_idx) {
        sc = SL_STATUS_OK;
        memcpy(blob_id,
               &blob_storage.slot_cache[slot_id].blob_id,
               sizeof(sl_bt_uuid_64_t));
        break;
      } else {
        current_occurrence_idx++;
      }
    }
  }
  return sc;
}

sl_status_t sl_btmesh_blob_storage_get_app_footer_length(sl_bt_uuid_64_t const *blob_id,
                                                         uint16_t app_id,
                                                         uint16_t *length)
{
  blob_storage_app_footer_metadata_t metadata;
  uint32_t slot_id, offset;
  sl_status_t sc;

  // Retrieve slot ID belonging to BLOB
  slot_id = sli_btmesh_blob_storage_get_slot_id(blob_id);
  sc = blob_storage_get_app_footer_metadata(slot_id,
                                            app_id,
                                            &metadata,
                                            &offset);
  if (sc == SL_STATUS_OK) {
    *length = metadata.length;
  }
  return sc;
}

sl_status_t sl_btmesh_blob_storage_get_app_footer(sl_bt_uuid_64_t const *blob_id,
                                                  uint16_t app_id,
                                                  void *buffer,
                                                  uint16_t *length)
{
  uint32_t slot_id;
  // Retrieve slot ID belonging to BLOB
  slot_id = sli_btmesh_blob_storage_get_slot_id(blob_id);
  return sli_btmesh_blob_storage_get_app_footer(slot_id, app_id, buffer, length);
}

sl_status_t sli_btmesh_blob_storage_get_app_footer(uint32_t slot_id,
                                                   uint16_t app_id,
                                                   void *buffer,
                                                   uint16_t *length)
{
  blob_storage_app_footer_metadata_t metadata;
  uint32_t offset;
  sl_status_t sc;
  sc = blob_storage_get_app_footer_metadata(slot_id,
                                            app_id,
                                            &metadata,
                                            &offset);
  if (SL_STATUS_OK != sc) {
    return sc;
  }
  // Buffer is too short for this footer
  if (metadata.length > *length) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  *length = metadata.length;
  if (BOOTLOADER_OK
      != bootloader_readStorage(slot_id, offset, buffer, *length)) {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_storage_get_blob_id_by_footer(uint16_t app_id,
                                                         const void *expected_footer,
                                                         uint16_t length,
                                                         sl_bt_uuid_64_t *blob_id)
{
  sl_status_t sc;
  blob_storage_app_footer_metadata_t metadata = { UINT16_MAX, UINT16_MAX };
  uint32_t offset;

  for (uint32_t slot_id = 0; slot_id < blob_storage.cache_length; ++slot_id) {
    if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED
        == blob_storage.slot_cache[slot_id].status) {
      sc = blob_storage_get_app_footer_metadata(slot_id,
                                                app_id,
                                                &metadata,
                                                &offset);

      // Nothing is found or the length of the footer is different then expected
      // continue with the next slot
      if ((SL_STATUS_NOT_FOUND == sc) || (metadata.length != length)) {
        continue;
      } else if (SL_STATUS_OK != sc) {
        // Return with error code in case other error occurs
        return sc;
      }

      int32_t comparison_result;
      sc = blob_storage_compare(slot_id,
                                offset,
                                expected_footer,
                                length,
                                &comparison_result);
      if (SL_STATUS_OK != sc) {
        // If comparison operation failed, return error code
        return sc;
      }

      if (0 == comparison_result) {
        memcpy(blob_id,
               &blob_storage.slot_cache[slot_id].blob_id,
               sizeof(sl_bt_uuid_64_t));
        return SL_STATUS_OK;
      }
    }
  }
  return SL_STATUS_NOT_FOUND;
}

uint32_t sl_btmesh_blob_storage_get_total_space(void)
{
  uint32_t total_space = 0;

  for (uint32_t i = 0; i < blob_storage.cache_length; ++i) {
    total_space += blob_storage_get_max_blob_size_in_slot(i);
  }
  return total_space;
}

uint32_t sl_btmesh_blob_storage_get_remaining_space(bool include_unmanaged_blobs)
{
  sl_btmesh_blob_storage_status_t slot_status;
  uint32_t max_blob_size_in_slot;
  uint32_t remaining_space = 0;

  for (uint32_t i = 0; i < blob_storage.cache_length; ++i) {
    slot_status = blob_storage.slot_cache[i].status;
    bool is_slot_available = false;

    if ((SL_BTMESH_BLOB_STORAGE_STATUS_EMPTY == slot_status)
        || (SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED == slot_status)) {
      // If the slot is empty or corrupted then it can be used to store BLOBs
      // without any restrictions
      is_slot_available = true;
    } else if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED == slot_status) {
      // The unmanaged BLOBs can be deleted on demand when space is required
      // for new BLOBs which makes it necessary to include it in the remaining
      // space calculation in some cases (application dependent)
      is_slot_available = include_unmanaged_blobs
                          && !sli_btmesh_blob_storage_is_managed(i);
    }

    if (is_slot_available) {
      max_blob_size_in_slot = blob_storage_get_max_blob_size_in_slot(i);
      remaining_space += max_blob_size_in_slot;
    }
  }
  return remaining_space;
}

uint32_t sl_btmesh_blob_storage_get_max_blob_size(void)
{
  uint32_t max_blob_size = 0;
  uint32_t max_blob_size_in_slot;

  for (uint32_t i = 0; i < blob_storage.cache_length; ++i) {
    max_blob_size_in_slot = blob_storage_get_max_blob_size_in_slot(i);
    if (max_blob_size < max_blob_size_in_slot) {
      max_blob_size = max_blob_size_in_slot;
    }
  }
  return max_blob_size;
}

uint32_t sl_btmesh_blob_storage_get_max_blob_size_free(bool include_unmanaged_blobs)
{
  sl_btmesh_blob_storage_status_t slot_status;
  uint32_t max_blob_size_in_slot;
  uint32_t max_blob_size_free = 0;

  for (uint32_t i = 0; i < blob_storage.cache_length; ++i) {
    slot_status = blob_storage.slot_cache[i].status;
    bool is_slot_available = false;

    if ((SL_BTMESH_BLOB_STORAGE_STATUS_EMPTY == slot_status)
        || (SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED == slot_status)) {
      // If the slot is empty or corrupted then it can be used to store BLOBs
      // without any restrictions
      is_slot_available = true;
    } else if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED == slot_status) {
      // The unmanaged BLOBs can be deleted on demand when space is required
      // for new BLOBs which makes it necessary to include it in the maximum
      // free BLOB size calculation in some cases (application dependent)
      is_slot_available = include_unmanaged_blobs
                          && !sli_btmesh_blob_storage_is_managed(i);
    }

    if (is_slot_available) {
      max_blob_size_in_slot = blob_storage_get_max_blob_size_in_slot(i);
      if (max_blob_size_free < max_blob_size_in_slot) {
        max_blob_size_free = max_blob_size_in_slot;
      }
    }
  }
  return max_blob_size_free;
}

uint32_t sl_btmesh_blob_storage_get_max_blob_count(void)
{
  return blob_storage.cache_length;
}

sl_btmesh_blob_storage_status_t sli_btmesh_blob_storage_get_slot_status(uint32_t slot_id)
{
  return blob_storage.slot_cache[slot_id].status;
}

void sli_btmesh_blob_storage_sync(void)
{
  for (uint32_t i = 0; i < blob_storage.cache_length; ++i) {
    blob_storage.slot_cache[i].status = blob_storage_check_slot_status(i);
    if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED
        == blob_storage.slot_cache[i].status) {
      blob_storage_footer_t footer;
      sl_status_t sc = blob_storage_get_footer(&footer, i);
      if (SL_STATUS_OK == sc) {
        memcpy(&blob_storage.slot_cache[i].blob_id,
               &footer.blob_id,
               sizeof(sl_bt_uuid_64_t));
        blob_storage.slot_cache[i].blob_size = footer.blob_size;
      } else {
        // This should not happen because this code is executed only if the same
        // blob_storage_get_footer call was successful in blob_storage_check_slot_status
        // function but to be on the safe side it is handled here.
        blob_storage.slot_cache[i].status =
          SL_BTMESH_BLOB_STORAGE_STATUS_INTERNAL_ERROR;
      }
    }
  }
}

static sl_status_t blob_storage_get_footer(blob_storage_footer_t *footer,
                                           uint32_t slot_id)
{
  BootloaderStorageSlot_t slot;
  if (BOOTLOADER_OK != bootloader_getStorageSlotInfo(slot_id, &slot)) {
    return SL_STATUS_FAIL;
  }

  // Read footer from the end of slot
  if (BOOTLOADER_OK
      != bootloader_readStorage(slot_id,
                                slot.length - sizeof(blob_storage_footer_t),
                                (uint8_t*)footer,
                                sizeof(blob_storage_footer_t))) {
    return SL_STATUS_FAIL;
  }

  if (footer->version != STORAGE_VERSION) {
    return SL_STATUS_INVALID_SIGNATURE;
  }

  return SL_STATUS_OK;
}

static sl_btmesh_blob_storage_status_t blob_storage_check_slot_status(uint32_t slot_id)
{
  BootloaderStorageSlot_t slot;
  sl_btmesh_blob_storage_status_t ret_val = SL_BTMESH_BLOB_STORAGE_STATUS_EMPTY;
  blob_storage_footer_t footer;

  if (BOOTLOADER_OK != bootloader_getStorageSlotInfo(slot_id, &slot)) {
    return SL_BTMESH_BLOB_STORAGE_STATUS_INTERNAL_ERROR;
  }

  // Read footer associated with slot
  if (SL_STATUS_FAIL == blob_storage_get_footer(&footer, slot_id)) {
    return SL_BTMESH_BLOB_STORAGE_STATUS_INTERNAL_ERROR;
  }

  // Check validity flag. It's enough to check the first byte, since it's
  // written as a whole.
  if (footer.validity_flag[0] != UINT8_MAX) {
    return SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED;
  }

  // Check if non-footer data is empty.
  // Since checking every byte would take long, use a heuristic approach of
  // checking only certain bytes.
  for (uint32_t i = 0; i < (slot.length - sizeof(blob_storage_footer_t));
       i += SL_BTMESH_BLOB_STORAGE_DATA_CHECK_JUMP_CFG_VAL) {
    uint8_t check;
    if (BOOTLOADER_OK != bootloader_readStorage(slot_id, i, &check, 1)) {
      return SL_BTMESH_BLOB_STORAGE_STATUS_INTERNAL_ERROR;
    }
    if (UINT8_MAX != check) {
      ret_val = SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED;
      break;
    }
  }

  // If data is found, check validity by reading the version
  if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED == ret_val) {
    if (STORAGE_VERSION != footer.version) {
      ret_val = SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED;
    }
  } else {
    // Check if footer is empty
    for (uint32_t i = 0; i < sizeof(blob_storage_footer_t); ++i) {
      uint8_t check = *(((uint8_t*)&footer) + i);
      if (UINT8_MAX != check) {
        ret_val = SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED;
        break;
      }
    }
  }

  return ret_val;
}

uint32_t sli_btmesh_blob_storage_get_slot_id(sl_bt_uuid_64_t const *blob_id)
{
  for (uint32_t i = 0; i < blob_storage.cache_length; ++i) {
    // Don't bother with invalid or empty slots
    if (blob_storage.slot_cache[i].status
        != SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED) {
      continue;
    }
    // Compare BLOB ID
    if (0 == memcmp(blob_id,
                    &blob_storage.slot_cache[i].blob_id,
                    sizeof(sl_bt_uuid_64_t))) {
      // Return slot ID
      return i;
    }
  }
  return UINT32_MAX;
}

sl_status_t sli_blob_storage_invalidate_slot(uint32_t slot_id, bool force)
{
  if ((force == false)
      && (sl_btmesh_blob_storage_get_erase_error_code()
          == SL_BTMESH_BLOB_STORAGE_DELETE_BUSY)) {
    return SL_STATUS_BUSY;
  }

  BootloaderStorageSlot_t slot;
  uint8_t invalid_flag[MAX_ALIGNMENT];

  // Clear all fields which results in invalid footer
  memset(invalid_flag, 0, MAX_ALIGNMENT);
  if (BOOTLOADER_OK != bootloader_getStorageSlotInfo(slot_id, &slot)) {
    return SL_STATUS_FAIL;
  }
  // Write invalidity flag at the start of the footer
  if (BOOTLOADER_OK
      != bootloader_writeStorage(slot_id,
                                 slot.length - sizeof(blob_storage_footer_t),
                                 invalid_flag,
                                 MAX_ALIGNMENT)) {
    return SL_STATUS_FLASH_PROGRAM_FAILED;
  }
  blob_storage.slot_cache[slot_id].status = SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED;
  return SL_STATUS_OK;
}

static sl_status_t blob_storage_get_app_footer_metadata(uint32_t slot_id,
                                                        uint16_t app_id,
                                                        blob_storage_app_footer_metadata_t *metadata,
                                                        uint32_t *offset)
{
  BootloaderStorageSlot_t slot;
  if (BOOTLOADER_OK != bootloader_getStorageSlotInfo(slot_id, &slot)) {
    return SL_STATUS_FAIL;
  }
  // Set offset to the first possible position for footer metadata
  *offset = slot.length
            - sizeof(blob_storage_footer_t)
            - sizeof(blob_storage_app_footer_metadata_t);

  do {
    if (BOOTLOADER_OK != bootloader_readStorage(slot_id,
                                                *offset,
                                                (uint8_t*)metadata,
                                                sizeof(blob_storage_app_footer_metadata_t))) {
      return SL_STATUS_FAIL;
    }
    if (app_id == metadata->app_id) {
      // Point to footer start
      *offset -= sl_btmesh_blob_storage_calc_app_footer_size(metadata->length)
                 - sizeof(blob_storage_app_footer_metadata_t);

      return SL_STATUS_OK;
    }
    // Try to find next metadata
    *offset -= sl_btmesh_blob_storage_calc_app_footer_size(metadata->length);
  } while (metadata->length != UINT16_MAX); // Length of 0xFFFF signifies invalid field
  return SL_STATUS_NOT_FOUND;
}

static uint32_t blob_storage_get_max_blob_size_in_slot(uint32_t slot_id)
{
  BootloaderStorageSlot_t slot;

  // If it is not possible to query the storage slot then no blob can be stored
  // in it therefore 0 is returned as the supported max blob size in the slot.
  if (BOOTLOADER_OK != bootloader_getStorageSlotInfo(slot_id, &slot)) {
    return 0;
  }

  return sli_calc_max_blob_size(slot.length);
}

static sl_status_t blob_storage_compare(uint32_t slot_id,
                                        uint32_t slot_offset,
                                        uint8_t const * expected_data,
                                        uint32_t length,
                                        int32_t *comparison_result)
{
  uint8_t compare_chunk_buf[COMPARE_BUFFER_SIZE];
  uint32_t remaining_length = length;
  uint32_t chunk_offset = 0;
  int chunk_compare_result;

  while (0 < remaining_length) {
    uint32_t chunk_size = (remaining_length < COMPARE_BUFFER_SIZE)
                          ? remaining_length : COMPARE_BUFFER_SIZE;

    if (BOOTLOADER_OK != bootloader_readStorage(slot_id,
                                                slot_offset + chunk_offset,
                                                &compare_chunk_buf[0],
                                                chunk_size)) {
      return SL_STATUS_FAIL;
    }

    chunk_compare_result = memcmp(&compare_chunk_buf[0],
                                  &expected_data[chunk_offset],
                                  chunk_size);

    if (0 != chunk_compare_result) {
      *comparison_result = chunk_compare_result;
      return SL_STATUS_OK;
    }

    remaining_length -= chunk_size;
    chunk_offset += chunk_size;
  }

  *comparison_result = 0;
  return SL_STATUS_OK;
}

/** @} end blob_storage */

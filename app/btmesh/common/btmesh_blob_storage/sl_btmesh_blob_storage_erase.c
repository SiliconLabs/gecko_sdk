/***************************************************************************//**
 * @file
 * @brief Implementation of BLOB storage component erase functionality
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

#include "btl_interface.h"
#include "sl_status.h"
#include "sl_bgapi.h"

#include "app_assert.h"
#include "sl_simple_timer.h"

#include "sl_btmesh_blob_storage.h"
#include "sl_btmesh_blob_storage_config.h"
#include "sli_btmesh_blob_storage.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

struct {
  struct sl_simple_timer timer; ///< Timer to separate two erase steps (chunk)
  BootloaderEraseStatus_t status; ///< Erase status for chunked erase
  uint32_t slot_id; ///< Currently erasing slot's identifier
  int32_t error_code; ///< Bootloader error code
  uint16_t owner; ///< Erase by Owner flag and owner identifier
  uint16_t separation_time_ms; ///< Separation time between two erase steps (chunk)
  bool separation_time_elapsed : 1; ///< Separation time elapsed flag
  bool erasing : 1; ///< Erasing state flag
  bool erase_started : 1;   ///< Erase started state flag
  bool invalid : 1; ///< Erase Invalid Slots state flag
  bool unmanaged : 1; ///< Erase Unmanaged Slots state flag
  bool all : 1; ///< Erase All Slots state flag
} blob_storage_erase;

/***************************************************************************//**
 * Starts erase separation timer
 ******************************************************************************/
static void blob_storage_start_delete_separation_timer(void);

/***************************************************************************//**
 * Erase separation time elapsed callback
 ******************************************************************************/
static void blob_storage_on_delete_separation_time_elapsed(sl_simple_timer_t *timer,
                                                           void *data);

/***************************************************************************//**
 * Forcibly delete a erase data from slot identified
 *
 * @param[in] slot_id Identifier of the slot to be erased
 *
 * @return Result of erase
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NOT_FOUND Slot identifier invalid
 * @retval SL_STATUS_FAIL In case of internal API error
 ******************************************************************************/
static sl_status_t blob_storage_force_delete_slot(uint32_t slot_id);

/***************************************************************************//**
 * Starts deleting slot identified
 *
 * @param[in] slot_id Identifier of the slot to be erased
 ******************************************************************************/
static void blob_storage_force_delete_slot_start(uint32_t slot_id);

/***************************************************************************//**
 * Helper function for delete functions to reduce code duplication
 *
 * @param[in] slot_id Identifier of the slot to be erased
 * @param[inout] status Status of the earlier erases. Should be initialized to
 *                      SL_STATUS_NOT_FOUND
 ******************************************************************************/
static inline void blob_storage_delete_helper(uint32_t slot_id,
                                              sl_status_t *status);

void sli_btmesh_blob_storage_erase_init(void)
{
  blob_storage_erase.erasing = false;
  blob_storage_erase.erase_started = false;
  blob_storage_erase.invalid = false;
  blob_storage_erase.unmanaged = false;
  blob_storage_erase.all = false;
  blob_storage_erase.error_code = INT32_MAX;
  blob_storage_erase.owner = UINT16_MAX;
  blob_storage_erase.separation_time_elapsed = true;
  blob_storage_erase.separation_time_ms =
    SL_BTMESH_BLOB_STORAGE_ASYNC_DELETE_SEPARATION_TIME_MS_CFG_VAL;
}

sl_status_t sl_btmesh_blob_storage_delete(sl_bt_uuid_64_t const *blob_id)
{
  sl_status_t sc;
  uint32_t slot_id = sli_btmesh_blob_storage_get_slot_id(blob_id);

  sc = blob_storage_force_delete_slot(slot_id);
  return sc;
}

sl_status_t sl_btmesh_blob_storage_delete_invalid_slots(void)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  for (uint32_t slot_id = 0;
       slot_id < sl_btmesh_blob_storage_get_max_blob_count();
       ++slot_id) {
    if (SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED
        == sli_btmesh_blob_storage_get_slot_status(slot_id)) {
      blob_storage_delete_helper(slot_id, &sc);
    }
  }
  return sc;
}

sl_status_t sl_btmesh_blob_storage_delete_unmanaged_slots(void)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  sl_btmesh_blob_storage_slot_metadata_cache_t const *cache;
  uint32_t cache_length;
  sl_btmesh_blob_storage_get_cache(&cache, &cache_length);
  for (uint32_t slot_id = 0; slot_id < cache_length; ++slot_id) {
    if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED == cache[slot_id].status
        && !sl_btmesh_blob_storage_is_managed(&cache[slot_id].blob_id)) {
      blob_storage_delete_helper(slot_id, &sc);
    }
  }
  return sc;
}

sl_status_t sl_btmesh_blob_storage_delete_managed_by_owner(uint16_t owner_id)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  sl_btmesh_blob_storage_slot_metadata_cache_t const *cache;
  uint32_t cache_length;
  sl_btmesh_blob_storage_get_cache(&cache, &cache_length);

  for (uint32_t slot_id = 0; slot_id < cache_length; ++slot_id) {
    // Only attempt erase when slot is not empty
    if (SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED == cache[slot_id].status
        && sl_btmesh_blob_storage_is_managed_by_owner(&cache[slot_id].blob_id,
                                                      owner_id)) {
      blob_storage_delete_helper(slot_id, &sc);
    }
  }
  return sc;
}

sl_status_t sl_btmesh_blob_storage_delete_all(void)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  uint32_t slot_cnt = sl_btmesh_blob_storage_get_max_blob_count();
  for (uint32_t slot_id = 0; slot_id < slot_cnt; ++slot_id) {
    blob_storage_delete_helper(slot_id, &sc);
  }
  return sc;
}

sl_status_t sl_btmesh_blob_storage_delete_start(sl_bt_uuid_64_t const *blob_id)
{
  if (blob_storage_erase.erasing) {
    return SL_STATUS_BUSY;
  }

  blob_storage_erase.erasing = true;
  blob_storage_erase.slot_id = sli_btmesh_blob_storage_get_slot_id(blob_id);
  blob_storage_force_delete_slot_start(blob_storage_erase.slot_id);
  log_debug("Starting BLOB erase in slot %lu!" NL, blob_storage_erase.slot_id);

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_storage_delete_invalid_slots_start(void)
{
  if (blob_storage_erase.erasing) {
    return SL_STATUS_BUSY;
  }

  blob_storage_erase.invalid = true;
  blob_storage_erase.erasing = true;
  blob_storage_erase.slot_id = 0;
  blob_storage_erase.error_code = INT32_MAX;

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_storage_delete_unmanaged_slots_start(void)
{
  if (blob_storage_erase.erasing) {
    return SL_STATUS_BUSY;
  }

  blob_storage_erase.unmanaged = true;
  blob_storage_erase.erasing = true;
  blob_storage_erase.slot_id = 0;
  blob_storage_erase.error_code = INT32_MAX;

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_storage_delete_managed_by_owner_start(uint16_t owner_id)
{
  if (blob_storage_erase.erasing) {
    return SL_STATUS_BUSY;
  }

  blob_storage_erase.owner = owner_id;
  blob_storage_erase.erasing = true;
  blob_storage_erase.slot_id = 0;
  blob_storage_erase.error_code = INT32_MAX;

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_storage_delete_all_start(void)
{
  if (blob_storage_erase.erasing) {
    return SL_STATUS_BUSY;
  }

  blob_storage_erase.all = true;
  blob_storage_erase.erasing = true;
  blob_storage_erase.slot_id = 0;
  blob_storage_erase.error_code = INT32_MAX;

  return SL_STATUS_OK;
}

sl_btmesh_blob_storage_delete_state_t sl_btmesh_blob_storage_get_erase_error_code(void)
{
  if (!blob_storage_erase.erasing) {
    if (INT32_MAX == blob_storage_erase.error_code) {
      return SL_BTMESH_BLOB_STORAGE_DELETE_INACTIVE;
    }
    if (BOOTLOADER_OK == blob_storage_erase.error_code) {
      return SL_BTMESH_BLOB_STORAGE_DELETE_SUCCESS;
    } else {
      return SL_BTMESH_BLOB_STORAGE_DELETE_FAILED;
    }
  }
  return SL_BTMESH_BLOB_STORAGE_DELETE_BUSY;
}

void sl_btmesh_blob_storage_delete_step_handle(void)
{
  if (!blob_storage_erase.erasing) {
    return;
  }
  if (blob_storage_erase.erase_started) {
    if (BOOTLOADER_ERROR_STORAGE_CONTINUE == blob_storage_erase.error_code) {
      if (blob_storage_erase.separation_time_elapsed) {
        blob_storage_erase.error_code =
          bootloader_chunkedEraseStorageSlot(&blob_storage_erase.status);
        // The async delete separation timer shall be started to introduce a
        // delay between two consecutive async delete steps. It is important to
        // start the timer even if the last chunk of the storage slot is erased
        // because other slots may be deleted as well after this one.
        if ((BOOTLOADER_ERROR_STORAGE_CONTINUE == blob_storage_erase.error_code)
            || (BOOTLOADER_OK == blob_storage_erase.error_code)) {
          blob_storage_start_delete_separation_timer();
        }
      }
    }
    if (BOOTLOADER_ERROR_STORAGE_CONTINUE != blob_storage_erase.error_code) {
      blob_storage_erase.erase_started = false;
      // Resync
      sli_btmesh_blob_storage_sync();
    }
  } else {
    if (blob_storage_erase.invalid) {
      if (sl_btmesh_blob_storage_get_max_blob_count()
          == blob_storage_erase.slot_id) {
        // clear flags
        blob_storage_erase.erasing = false;
        blob_storage_erase.invalid = false;
      } else if (SL_BTMESH_BLOB_STORAGE_STATUS_CORRUPTED
                 == sli_btmesh_blob_storage_get_slot_status(blob_storage_erase.slot_id)) {
        blob_storage_force_delete_slot_start(blob_storage_erase.slot_id++);
      } else {
        blob_storage_erase.slot_id++;
      }
    } else if (blob_storage_erase.unmanaged) {
      if (sl_btmesh_blob_storage_get_max_blob_count()
          == blob_storage_erase.slot_id) {
        // clear flags
        blob_storage_erase.erasing = false;
        blob_storage_erase.unmanaged = false;
      } else if (!sli_btmesh_blob_storage_is_managed(blob_storage_erase.slot_id)) {
        blob_storage_force_delete_slot_start(blob_storage_erase.slot_id++);
      } else {
        blob_storage_erase.slot_id++;
      }
    } else if (blob_storage_erase.owner != UINT16_MAX) {
      if (sl_btmesh_blob_storage_get_max_blob_count()
          == blob_storage_erase.slot_id) {
        // clear flags
        blob_storage_erase.erasing = false;
        blob_storage_erase.owner = UINT16_MAX;
      } else if (sli_btmesh_blob_storage_is_managed_by_owner(blob_storage_erase.slot_id,
                                                             blob_storage_erase.owner)) {
        blob_storage_force_delete_slot_start(blob_storage_erase.slot_id++);
      } else {
        blob_storage_erase.slot_id++;
      }
    } else if (blob_storage_erase.all) {
      if (sl_btmesh_blob_storage_get_max_blob_count()
          == blob_storage_erase.slot_id) {
        // clear flags
        blob_storage_erase.erasing = false;
        blob_storage_erase.all = false;
      } else {
        blob_storage_force_delete_slot_start(blob_storage_erase.slot_id++);
      }
    } else {
      blob_storage_erase.erasing = false;
    }
  }
}

bool sl_btmesh_blob_storage_is_ok_to_sleep()
{
  return !blob_storage_erase.erasing;
}

sl_status_t sl_btmesh_blob_storage_set_delete_separation_time(uint16_t separation_time_ms)
{
  blob_storage_erase.separation_time_ms = separation_time_ms;
  return SL_STATUS_OK;
}

static void blob_storage_start_delete_separation_timer(void)
{
  blob_storage_erase.separation_time_elapsed = false;
  if (blob_storage_erase.separation_time_ms == 0) {
    // If the delete separation time is zero then the timer elapses immediately
    // so the timer callback shall be called directly
    blob_storage_on_delete_separation_time_elapsed(&blob_storage_erase.timer, NULL);
  } else {
    sl_status_t sc;
    sc = sl_simple_timer_start(&blob_storage_erase.timer,
                               blob_storage_erase.separation_time_ms,
                               blob_storage_on_delete_separation_time_elapsed,
                               NULL,
                               false);
    app_assert_status(sc);
  }
}

static void blob_storage_on_delete_separation_time_elapsed(sl_simple_timer_t *timer,
                                                           void *data)
{
  (void) timer;
  (void) data;
  blob_storage_erase.separation_time_elapsed = true;
}

static sl_status_t blob_storage_force_delete_slot(uint32_t slot_id)
{
  sl_btmesh_blob_storage_status_t slot_status;

  // If the slot is occupied then it shall be invalidated first because the
  // bootloader_eraseStorageSlot erases the pages of the storage slot from
  // lower address to higher address which means the data is erased sooner than
  // the footer. This is essential because the BLOB in the slot would appear
  // valid due to the intact footer while the BLOB data was deleted partially
  // without invalidation.
  slot_status = sli_btmesh_blob_storage_get_slot_status(slot_id);

  if (slot_status == SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED) {
    // The invalidation shall be forced because the invalidated slot will be
    // deleted immediately so an ongoing erase should not cause any issues.
    sl_status_t sc_invalidate = sli_blob_storage_invalidate_slot(slot_id, true);

    // If the invalidation fails then it does not mean that an error will occur
    // during the storage slot erase. An issue may occur with failed invalidation
    // if there is a reset during erase.
    // If the invalidation fails then a warning is logged and the storage slot
    // is erased anyway because it might have more negative consequences if a
    // storage slot is not erased. (e.g. no new BLOB can be written)
    log_status_warning_f(sc_invalidate,
                         "Failed to invalidate occupied slot before delete (slot=%lu)" NL,
                         (unsigned long) slot_id);
  }

  switch (bootloader_eraseStorageSlot(slot_id)) {
    case BOOTLOADER_ERROR_STORAGE_INVALID_SLOT:
      return SL_STATUS_NOT_FOUND;
    case BOOTLOADER_OK:
      break;
    default:
      return SL_STATUS_FAIL;
  }
  // Resync
  sli_btmesh_blob_storage_sync();
  return SL_STATUS_OK;
}

static void blob_storage_force_delete_slot_start(uint32_t slot_id)
{
  sl_btmesh_blob_storage_status_t slot_status;

  // If the slot is occupied then it shall be invalidated first because the
  // bootloader_initChunkedEraseStorageSlot and bootloader_chunkedEraseStorageSlot
  // erase the pages of the storage slot from lower address to higher address
  // which means the data is erased sooner than the footer.
  // This is essential because the BLOB in the slot would appear valid due to the
  // intact footer while the BLOB data was deleted partially without invalidation.
  slot_status = sli_btmesh_blob_storage_get_slot_status(slot_id);

  if (slot_status == SL_BTMESH_BLOB_STORAGE_STATUS_OCCUPIED) {
    // The invalidation shall be forced because this function is also called when
    // multiple storage slots are deleted one by one.
    // For example: sl_btmesh_blob_storage_delete_all_start
    sl_status_t sc_invalidate = sli_blob_storage_invalidate_slot(slot_id, true);

    // If the invalidation fails then it does not mean that an error will occur
    // during the storage slot erase. An issue may occur with failed invalidation
    // if there is a reset during erase or the BLOB data in the storage slot is
    // read while it is being erased.
    // If the invalidation fails then a warning is logged and the storage slot
    // is erased anyway because it might have more negative consequences if a
    // storage slot is not erased. (e.g. no new BLOB can be written)
    log_status_warning_f(sc_invalidate,
                         "Failed to invalidate occupied slot before delete (slot=%lu)" NL,
                         (unsigned long) slot_id);
  }

  blob_storage_erase.error_code =
    bootloader_initChunkedEraseStorageSlot(slot_id,
                                           &blob_storage_erase.status);
  if (BOOTLOADER_OK == blob_storage_erase.error_code) {
    // Signal ongoing erase
    blob_storage_erase.error_code = BOOTLOADER_ERROR_STORAGE_CONTINUE;
    blob_storage_erase.erase_started = true;
  }
}

static inline void blob_storage_delete_helper(uint32_t slot_id,
                                              sl_status_t *status)
{
  sl_status_t temp_sc = blob_storage_force_delete_slot(slot_id);

  app_assert(temp_sc != SL_STATUS_NOT_FOUND, "Invalid slot ID!");

  // status should point to a value of SL_STATUS_NOT_FOUND initially
  if (*status == SL_STATUS_NOT_FOUND && SL_STATUS_OK == temp_sc) {
    *status = SL_STATUS_OK;
  }

  if (SL_STATUS_OK != temp_sc) {
    // Erase is requested for all storage slots even if the erase of previous
    // storage slots have failed. However, if at least one erase fails then
    // the return value is set to SL_STATUS_FLASH_ERASE_FAILED.
    *status = SL_STATUS_FLASH_ERASE_FAILED;
  }
}

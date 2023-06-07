/***************************************************************************//**
 * @file
 * @brief Weak implementations of user API functions
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
#include <string.h>
#include "sl_btmesh.h"
#include "sl_malloc.h"
#include "app_assert.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
#include "sl_btmesh_wstk_lcd.h"
#include <stdio.h>
// No verification progress is written to the LCD
#define FW_VERIFY_PRG_KB_ON_LCD_UNKNOWN 0xFFFFFFFF
// Last verification progress written to the LCD
static uint32_t fw_verify_prg_kb_on_lcd = FW_VERIFY_PRG_KB_ON_LCD_UNKNOWN;
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

#include "app_timer.h"

#include "btl_interface.h"
#include "sl_btmesh_blob_storage.h"

#include "sl_btmesh_firmware_update_server_api.h"
#include "sl_btmesh_firmware_update_server_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/// Delay between NVM erase and node reset initiated by apply,
/// and installation of firmware
#define APPLY_DELAY                         5

/// Verification chunk size of the bootloader implementation
#define BOOTLOADER_VERIFICATION_CHUNK_SIZE  128

/// Returns the string representation of BLOB ID in a compound literal.
/// WARNING! This macro shall be used as a parameter of log calls only due to the
/// lifetime of underlying compound literal in APP_BTMESH_UUID_64_TO_STRING.
#define BLOB_ID_TO_STRING(blob_id) APP_BTMESH_UUID_64_TO_STRING(blob_id, ' ', true)

/// Context pointer for verification
static void *context;

/// Countdown for apply delay
static uint8_t apply_cntdwn;

/// Cache for the ID of the BLOB used for the update
///
/// Initialized to all ones indicating unknown.
static sl_bt_uuid_64_t blob_id_cache = { .data = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                   0xFF, 0xFF, 0xFF } };

/***************************************************************************//**
 * Used to delay bootloader initiation, as NVM erase needs time.
 *
 * @param handle Timer handler
 * @param data Callback data
 ******************************************************************************/
static void apply_step(app_timer_t *handle, void *data);

SL_WEAK sl_btmesh_fw_update_server_verify_state_t
sl_btmesh_fw_update_server_verify_start(sl_bt_uuid_64_t const *const blob_id,
                                        uint8_t ** const verify_chunk_buffer,
                                        uint32_t *const verify_chunk_size,
                                        const uint32_t blob_size)
{
  (void)blob_size;
  uint32_t slot_id;
  sl_btmesh_blob_storage_slot_metadata_cache_t const *cache;
  uint32_t len;

  // No verification buffer is used
  *verify_chunk_buffer = NULL;
  // Progress calculation is based on chunk size
  *verify_chunk_size = BOOTLOADER_VERIFICATION_CHUNK_SIZE;
  sl_btmesh_blob_storage_get_cache(&cache, &len);

  for (slot_id = 0; slot_id < len; ++slot_id) {
    if (0 == memcmp(blob_id, &cache->blob_id, sizeof(sl_bt_uuid_64_t))) {
      break;
    }
  }
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("FW Update Verify", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_STATUS_CFG_VAL);
  fw_verify_prg_kb_on_lcd = FW_VERIFY_PRG_KB_ON_LCD_UNKNOWN;
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

  if (slot_id == len) {
    return BTMESH_FW_UPDATE_SERVER_VERIFY_ERROR;
  }

  context = sl_malloc(BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE);

  app_assert(context != NULL, "No verification buffer could be allocated!");

  if (BOOTLOADER_OK
      != bootloader_initVerifyImage(slot_id,
                                    context,
                                    BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE)) {
    sl_free(context);
    return BTMESH_FW_UPDATE_SERVER_VERIFY_ERROR;
  }
  return BTMESH_FW_UPDATE_SERVER_VERIFY_PENDING;
}

SL_WEAK sl_btmesh_fw_update_server_verify_state_t
sl_btmesh_fw_update_server_verify_step(void const *data,
                                       const uint32_t len)
{
  (void)data;
  (void)len;
  int32_t sc = bootloader_continueVerifyImage(context, NULL);
  switch (sc) {
    case BOOTLOADER_ERROR_PARSE_SUCCESS:
      sl_free(context);
      return BTMESH_FW_UPDATE_SERVER_VERIFY_SUCCESS;
    case BOOTLOADER_ERROR_PARSE_CONTINUE: {
      return BTMESH_FW_UPDATE_SERVER_VERIFY_PENDING;
    }
    default:
      sl_free(context);

      bool blob_managed = sl_btmesh_blob_storage_is_managed(&blob_id_cache);
      if (blob_managed == false) {
        // Verification failed, unmanaged BLOB is not useful any more
        sl_btmesh_blob_storage_invalidate(&blob_id_cache);
      } else {
        // If the node is a Distributor and an Updating Node as well then the
        // BLOB shall not be invalidated because it is part of the firmware list
        // of the Distributor and therefore it can be invalidated by the Initiator
        // only (explicitly)
      }
      log_error("Verification failed (0x%lX)!" NL, sc);
      return BTMESH_FW_UPDATE_SERVER_VERIFY_ERROR;
  }
}

SL_WEAK void sl_btmesh_fw_update_server_verify_progress_ui_update(sl_btmesh_fw_update_server_verify_state_t status,
                                                                  uint32_t progress,
                                                                  uint32_t size)
{
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  switch (status) {
    case BTMESH_FW_UPDATE_SERVER_VERIFY_PENDING:
    {
      char str[LCD_ROW_LEN] = { 0 };
      uint32_t fw_verify_prg_kb = (progress + 512) >> 10;
      uint32_t fw_verify_size_kb = (size + 512) >> 10;
      if ((FW_VERIFY_PRG_KB_ON_LCD_UNKNOWN == fw_verify_prg_kb_on_lcd)
          || (fw_verify_size_kb == fw_verify_prg_kb)
          || (fw_verify_prg_kb_on_lcd < fw_verify_prg_kb)) {
        snprintf(str,
                 LCD_ROW_LEN,
                 "%u kB / %u kB",
                 (uint16_t)fw_verify_prg_kb,
                 (uint16_t)fw_verify_size_kb);
        sl_btmesh_LCD_write(str, SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL);
        fw_verify_prg_kb_on_lcd = fw_verify_prg_kb;
      }
      break;
    }

    case BTMESH_FW_UPDATE_SERVER_VERIFY_SUCCESS:
      sl_btmesh_LCD_write("Done", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL);
      break;

    default:
      sl_btmesh_LCD_write("Error", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL);
      break;
  }
#else
  (void) status;
  (void) progress;
  (void) size;
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
}

SL_WEAK sl_btmesh_fw_update_server_metadata_check_state_t
sl_btmesh_fw_update_server_metadata_check_start(void const *metadata,
                                                const uint8_t len,
                                                sl_btmesh_fw_update_server_additional_information_t *const additional_information)
{
  (void)metadata;
  (void)len;
  *additional_information = BTMESH_FW_UPDATE_SERVER_ADDITIONAL_INFORMATION_UNPROVISION;
  return BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_PENDING;
}

SL_WEAK sl_btmesh_fw_update_server_metadata_check_state_t
sl_btmesh_firmware_update_server_metadata_check_step(sl_btmesh_fw_update_server_additional_information_t *const additional_information)
{
  *additional_information = BTMESH_FW_UPDATE_SERVER_ADDITIONAL_INFORMATION_UNPROVISION;
  return BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_SUCCESS;
}

SL_WEAK void sl_btmesh_fw_update_server_update_start(sl_bt_uuid_64_t const *const blob_id)
{
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("Firmware Update", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_STATUS_CFG_VAL);
  sl_btmesh_LCD_write("Started", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  memcpy(&blob_id_cache, blob_id, sizeof(blob_id_cache));
  return;
}

SL_WEAK void sl_btmesh_fw_update_server_update_canceled(void)
{
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("Canceled", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  return;
}

SL_WEAK void sl_btmesh_fw_update_server_update_aborted(void)
{
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("Aborted", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  return;
}

SL_WEAK void sl_btmesh_fw_update_server_apply(void)
{
  sl_btmesh_blob_storage_slot_metadata_cache_t const *cache;
  uint32_t len;
  uint32_t idx;
  static app_timer_t timer;

  sl_btmesh_blob_storage_get_cache(&cache, &len);

  // Find index corresponding to input BLOB ID
  for (idx = 0;
       (idx < len) && (0 != memcmp(&blob_id_cache,
                                   &cache[idx].blob_id,
                                   sizeof(sl_bt_uuid_64_t)));
       ++idx) {
    ;
  }

  if (idx != len) {
    // Invalidate slot, as it's not useful anymore
    sl_status_t sc = sl_btmesh_blob_storage_invalidate(&cache[idx].blob_id);
    log_status_error_f(sc,
                       "Could not invalidate BLOB %s" NL,
                       BLOB_ID_TO_STRING(&cache[idx].blob_id));
  }

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("FW Update Applying", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_STATUS_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  if (BOOTLOADER_OK == bootloader_setImageToBootload(idx)) {
    // Reset node
    sl_btmesh_node_reset();
    // Erase NVM data
    sl_bt_nvm_erase_all();
    // Delay install
    app_timer_start(&timer, 1000, apply_step, NULL, true);
    apply_cntdwn = APPLY_DELAY;
  }
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  else {
    sl_btmesh_LCD_write("Failed", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL);
  }
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
}

static void apply_step(app_timer_t *handle, void *data)
{
  (void)handle;
  (void)data;
  if (--apply_cntdwn > 0) {
    log_info("%d..." NL, apply_cntdwn);
    return;
  }
  log_info("0" NL);
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("Restarting...", SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  // Initiate reboot with new firmware
  bootloader_rebootAndInstall();
}

/*******************************************************************************
 * Used to retrieve information about firmware stored on the device for DFU
 ******************************************************************************/
SL_WEAK sl_status_t mesh_platform_get_installed_firmware_information(uint8_t index,
                                                                     uint8_t *fwid_len,
                                                                     const uint8_t **fwid_ptr,
                                                                     uint8_t *uri_len,
                                                                     const uint8_t **uri_ptr)
{
  if (index > 0) {
    return SL_STATUS_BT_MESH_DOES_NOT_EXIST;
  }
  *fwid_ptr = (const uint8_t*) SL_BTMESH_FW_UPDATE_SERVER_CID_LSB_CFG_VAL
              SL_BTMESH_FW_UPDATE_SERVER_CID_MSB_CFG_VAL
              SL_BTMESH_FW_UPDATE_SERVER_FWID_CFG_VAL;
  *fwid_len = strlen((char*)*fwid_ptr);
  *uri_ptr = (const uint8_t*) SL_BTMESH_FW_UPDATE_SERVER_UPDATE_URI_CFG_VAL;
  *uri_len = strlen((char*)*uri_ptr);
  return SL_STATUS_OK;
}

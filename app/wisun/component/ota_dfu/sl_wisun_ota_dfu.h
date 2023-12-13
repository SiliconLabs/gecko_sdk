/***************************************************************************//**
 * @file
 * @brief Wi-SUN OTA DFU Service header
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

#ifndef __SL_WISUN_OTA_DFU_H__
#define __SL_WISUN_OTA_DFU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "sl_status.h"
#include "em_common.h"

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

#if  defined(SL_WISUN_UNIT_TEST)
#warning Unit test enabled
/// OTA DFU Service loop for unit tests
#define SL_WISUN_OTA_DFU_SERVICE_LOOP()       for (uint8_t i = 0U; i < SL_WISUN_OTA_DFU_SERVICE_LOOP_EXPECTED_CNT; ++i)
#else
/// OTA DFU Service loop
#define SL_WISUN_OTA_DFU_SERVICE_LOOP()       while (1)
#endif

/**************************************************************************//**
 * @addtogroup SL_WISUN_OTA_DFU_API Over-The-Air Device Firmware Upgrade (Alpha)
 * @{
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup SL_WISUN_OTA_DFU_TYPES Type definitions
 * @ingroup SL_WISUN_OTA_DFU_API
 * @{
 *****************************************************************************/

/// Wi-SUN OTA DFU Status enumeration
typedef enum sl_wisun_ota_dfu_status {
  /// Firmware update started
  SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STARTED = 0,
  /// Firmware downloaded
  SL_WISUN_OTA_DFU_STATUS_FW_DOWNLOADED,
  /// Firmware verified
  SL_WISUN_OTA_DFU_STATUS_FW_VERIFIED,
  /// Firmware set
  SL_WISUN_OTA_DFU_STATUS_FW_SET,
  // Firmware update finished/stopped
  SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STOPPED,
  /// Firmware Download error
  SL_WISUN_OTA_DFU_STATUS_FW_DOWNLOAD_ERROR,
  /// Firmware Verify error
  SL_WISUN_OTA_DFU_STATUS_FW_VERIFY_ERROR,
  /// Firmware Set error
  SL_WISUN_OTA_DFU_STATUS_FW_SET_ERROR
} sl_wisun_ota_dfu_status_t;

/// Wi-SUN OTA DFU error code enumeration
typedef enum sl_wisun_ota_dfu_error_code {
  /// Firmware downloaded error code
  SL_WISUN_OTA_DFU_ERROR_FW_DOWNLOAD = 1001UL,
  /// Firmware verify error code
  SL_WISUN_OTA_DFU_ERROR_FW_VERIFY,
  /// Firmware set error code
  SL_WISUN_OTA_DFU_ERROR_FW_SET
} sl_wisun_ota_dfu_error_code_t;

/// Wi-SUN OTA DFU download error context definition
typedef struct sl_wisun_ota_dfu_error_ctx_fw_download {
  /// Return value of API call
  int32_t ret_val;
  /// Offset of GBL file
  uint32_t offset;
  /// Data size
  uint16_t data_size;
} sl_wisun_ota_dfu_error_ctx_fw_download_t;

/// Wi-SUN OTA DFU verify error context definition
typedef struct sl_wisun_ota_dfu_error_ctx_btl_fw_verify {
  /// Return value of API call
  int32_t ret_val;
} sl_wisun_ota_dfu_error_ctx_btl_fw_verify_t;

/// Wi-SUN OTA DFU set error context definition
typedef struct sl_wisun_ota_dfu_error_ctx_btl_fw_set {
  /// Return value of API call
  int32_t ret_val;
} sl_wisun_ota_dfu_error_ctx_btl_fw_set_t;

/// Wi-SUN OTA DFU error context definition
typedef union sl_wisun_ota_dfu_error_ctx {
  /// Download error context
  sl_wisun_ota_dfu_error_ctx_fw_download_t download;
  /// Verify error context
  sl_wisun_ota_dfu_error_ctx_btl_fw_verify_t verify;
  /// Set error context
  sl_wisun_ota_dfu_error_ctx_btl_fw_set_t set;
} sl_wisun_ota_dfu_error_ctx_t;

/** @} (end SL_WISUN_OTA_DFU_TYPES) */

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief Initialize the device firmware upgrade service.
 * @details Initialize Wi-SUN OTA Device Firmware Upgrade service.
 ******************************************************************************/
void sl_wisun_ota_dfu_init(void);

/**************************************************************************//**
 * @brief Start firmware update.
 * @details Start firmware update by setting
 *          SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STARTED flag
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
sl_status_t sl_wisun_ota_dfu_start_fw_update(void);

/**************************************************************************//**
 * @brief Stop firmware update.
 * @details Stop firmware update by setting
 *          SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STOPPED flag
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
sl_status_t sl_wisun_ota_dfu_stop_fw_update(void);

#if !SL_WISUN_OTA_DFU_AUTO_INSTALL_ENABLED
/**************************************************************************//**
 * @brief Reboot device.
 * @details Reboot device with calling corresponding gecko bootloader
 *          'bootloader_rebootAndInstall' API
 *          This functions is available if auto-reboot mode is disabled.
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
sl_status_t sl_wisun_ota_dfu_reboot_and_install(void);
#endif

/**************************************************************************//**
 * @brief Get the status value.
 * @details Returning the value of event flags
 * @return uint32_t Status
 *****************************************************************************/
uint32_t sl_wisun_ota_dfu_get_fw_update_status(void);

/**************************************************************************//**
 * @brief Get the status string in JSON format.
 * @details String buffer is allocated in heap by CoAP allocator
 * @return const char * Allocated string pointer on success, otherwise NULL
 *****************************************************************************/
const char* sl_wisun_ota_dfu_get_fw_update_status_json_str(void);

/**************************************************************************//**
* @brief Free the status string buffer.
* @details Call CoAP free to release allocated memory
* @param[in] str String ptr
******************************************************************************/
void sl_wisun_ota_dfu_free_fw_update_status_json_str(const char * str);

/**************************************************************************//**
* @brief Get the status flag value.
* @details Bool representation of status variable bit value
* @param[in] status_flag Status flag enum
* @return bool true if the flag is set, otherwise false
******************************************************************************/
bool sl_wisun_ota_dfu_get_fw_update_status_flag(const sl_wisun_ota_dfu_status_t status_flag);

/***************************************************************************//**
 * @brief OTA DFU error handler (weak implementation)
 * @details Catch error in different stages of boot load.
 * @param[in] error_code Error code
 * @param[in] ctx  Error context with error details
 ******************************************************************************/
void sl_wisun_ota_dfu_error_hnd(const sl_wisun_ota_dfu_error_code_t error_code,
                                sl_wisun_ota_dfu_error_ctx_t * const ctx);

/** @}*/

#ifdef __cplusplus
}
#endif
#endif

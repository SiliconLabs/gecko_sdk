/***************************************************************************//**
 * @file
 * @brief ESL Access Point Storage header.
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

#ifndef ESL_LIB_STORAGE_H
#define ESL_LIB_STORAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "sl_status.h"
#include "sl_bt_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Definitions

typedef void *esl_lib_storage_handle_t;

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * Create storage.
 *
 * @param[out] handle_out Handle output.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_storage_create(esl_lib_storage_handle_t *handle_out);

/**************************************************************************//**
 * Append to a storage.
 *
 * @param[in] handle Storage handle.
 * @param[in] data   Pointer to data input.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_storage_append(esl_lib_storage_handle_t handle,
                                   uint8array               *data);

/**************************************************************************//**
 * Get the size of the storage.
 *
 * @param[in]  handle Storage handle.
 * @param[out] size   Actual total size of the size.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_storage_get_size(esl_lib_storage_handle_t handle,
                                     size_t                   *size_out);

/**************************************************************************//**
 * Copy the entire content of the storage.
 *
 * @param[in]  handle   Storage handle.
 * @param[out] data_out Location to copy the content to.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_storage_copy(esl_lib_storage_handle_t handle,
                                 uint8_t                  *data_out);

/**************************************************************************//**
 * Clean storage.
 *
 * @param[in]  handle Storage handle.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_storage_clean(esl_lib_storage_handle_t handle);

/**************************************************************************//**
 * Delete storage.
 *
 * @param[in]  handle Storage handle.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_storage_delete(esl_lib_storage_handle_t handle);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_STORAGE_H

/***************************************************************************//**
 * @file
 * @brief ESL AP Library - Image Transfer header
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

#ifndef ESL_LIB_IMAGE_TRANSFER_H
#define ESL_LIB_IMAGE_TRANSFER_H

#include <stdint.h>
#include "sl_status.h"
#include "esl_lib.h"
#include "sl_bt_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Definitions

#define ESL_LIB_IMAGE_TRANSFER_INVALID_HANDLE    NULL

/// Type stores the image transfer handle
typedef void *esl_lib_image_transfer_handle_t;

/// Type for registering the transfer state
typedef enum {
  ESL_LIB_IMAGE_TRANSFER_STATE_NOT_INITIALIZED,
  ESL_LIB_IMAGE_TRANSFER_STATE_INIT_IN_PROGRESS,
  ESL_LIB_IMAGE_TRANSFER_STATE_IDLE,
  ESL_LIB_IMAGE_TRANSFER_STATE_BUSY,
  ESL_LIB_IMAGE_TRANSFER_REMOVED
} esl_image_transfer_state_t;

// -----------------------------------------------------------------------------
// Callback types

/***************************************************************************//**
 * Callback for the transfer status.
 * @param[in] handle         Image transfer handle.
 * @param[in] connnection    Connection handle.
 * @param[in] state          New state of the transfer.
 * @param[in] result         Result of the state change.
 * @param[in] gattdb_handles GATT databse handles or NULL if not set.
 ******************************************************************************/
typedef void (*esl_lib_image_transfer_status_callback_t)(esl_lib_image_transfer_handle_t handle,
                                                         uint8_t                         connection,
                                                         esl_image_transfer_state_t      state,
                                                         sl_status_t                     result,
                                                         esl_lib_ots_gattdb_handles_t    *gattdb_handles);

/***************************************************************************//**
 * Callback that indicates the end of the transfer.
 * @param[in] handle      Image transfer handle.
 * @param[in] connnection Connection handle.
 * @param[in] result      Result of the image transfer.
 * @param[in] image_index Image index.
 ******************************************************************************/
typedef void (*esl_lib_image_transfer_finished_callback_t)(esl_lib_image_transfer_handle_t handle,
                                                           uint8_t                         connection,
                                                           sl_status_t                     result,
                                                           uint8_t                         image_index);

/***************************************************************************//**
 * Callback for the object type
 * @param[in] handle      Image transfer handle.
 * @param[in] connnection Connection handle.
 * @param[in] result      Result of the type read.
 * @param[in] image_index Image index.
 * @param[in] object_type Object type, valid if the result is SL_STATUS_OK.
 * @param[in] len         Length of the Object type
 ******************************************************************************/
typedef void (*esl_lib_image_transfer_type_callback_t)(esl_lib_image_transfer_handle_t handle,
                                                       uint8_t                         connection,
                                                       sl_status_t                     result,
                                                       uint8_t                         image_index,
                                                       uint8_t                         *object_type,
                                                       uint8_t                         len);

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * Clean all imagetransfer data.
 *****************************************************************************/
void esl_lib_image_transfer_cleanup(void);

/***************************************************************************//**
 * Initialize ESL AP Image Transfer.
 * @param[in]  connection          Connection handle.
 * @param[in]  ots_service_handle  OTS service handle.
 * @param[in]  status_callback     Callback function for state changes.
 * @param[in]  type_callback       Callback function for object/image type.
 * @param[in]  finish_callback     Callback for data transmit finish event.
 * @param[in]  gattdb_handles      GATT database handle array.
 * @param[out] handle_out          Resulting ESL Image Transfer handle.
 * @return Status of the operation
 ******************************************************************************/
sl_status_t esl_lib_image_transfer_init(uint8_t                                    connection,
                                        uint32_t                                   ots_service_handle,
                                        esl_lib_image_transfer_status_callback_t   status_callback,
                                        esl_lib_image_transfer_type_callback_t     type_callback,
                                        esl_lib_image_transfer_finished_callback_t finish_callback,
                                        esl_lib_ots_gattdb_handles_t               *gattdb_handles,
                                        esl_lib_image_transfer_handle_t            *handle_out);

/***************************************************************************//**
 * Read object type
 * @param[in] handle          ESL Image Transfer handle.
 * @param[in] image_index     ESL image index.
 * @return Status of the operation
 ******************************************************************************/
sl_status_t esl_lib_image_transfer_get_type(esl_lib_image_transfer_handle_t handle,
                                            uint8_t                         image_index);

/***************************************************************************//**
 * Start an image transfer.
 * @param[in] handle               ESL Image Transfer handle.
 * @param[in] image_index          ESL image index.
 * @param[in] image_offset         Offset to write from.
 * @param[in] image_size           Size of the image data to write.
 * @param[in] allocated_image_data Data for the image transfer (data will be copied).
 * @return Status of the operation
 ******************************************************************************/
sl_status_t esl_lib_image_transfer_start(esl_lib_image_transfer_handle_t handle,
                                         uint8_t                         image_index,
                                         size_t                          image_offset,
                                         size_t                          image_size,
                                         uint8_t                         *allocated_image_data);

/***************************************************************************//**
 * Abort an image transfer in progress.
 * @param[in] handle          ESL Image Transfer handle.
 * @return Status of the operation
 ******************************************************************************/
sl_status_t esl_lib_image_transfer_abort(esl_lib_image_transfer_handle_t handle);

/***************************************************************************//**
 * Get OTS features of an image transfer.
 * @param[in]  handle          ESL Image Transfer handle.
 * @param[out] features        OTS features.
 * @return Status of the operation
 ******************************************************************************/
sl_status_t esl_lib_image_transfer_get_features(esl_lib_image_transfer_handle_t handle,
                                                esl_lib_ots_features_t          *features);

// -----------------------------------------------------------------------------
// Internal functions

/***************************************************************************//**
 * Internal Bluetooth event handler
 * @param[in] evt Bluetooth event.
 ******************************************************************************/
void esl_lib_image_transfer_on_bt_event(sl_bt_msg_t *evt);

/***************************************************************************//**
 * Internal step function
 ******************************************************************************/
void esl_lib_image_transfer_step(void);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_IMAGE_TRANSFER_H

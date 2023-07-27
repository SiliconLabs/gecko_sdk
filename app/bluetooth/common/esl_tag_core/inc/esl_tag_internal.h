/***************************************************************************//**
 * @file
 * @brief ESL Tag core interface declarations for internal use, only.
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
#ifndef ESL_TAG_INTERNAL_H
#define ESL_TAG_INTERNAL_H

/**************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 *****************************************************************************/
#include <stdint.h>
#include "sl_status.h"
#include "esl_tag_display_core.h"

/**************************************************************************//**
 * Get a display width based on display index.
 * @param[in]  display_index Selects the display to get width of [pixels].
 * @param[out] width Returns width if given display exists.
 * @return sl_status_t SL_STATUS_OK if display_index is valid, error otherwise.
 * @note: The function is only defined in esl_tag_display component (if added)
 *****************************************************************************/
extern sl_status_t esl_display_get_width(uint8_t display_index,
                                         uint16_t *width);

/**************************************************************************//**
 * Get a display height based on display index.
 * @param[in]  display_index Selects the display to get height of [pixels].
 * @param[out] height Returns height if given display exists.
 * @return sl_status_t SL_STATUS_OK if display_index is valid, error otherwise.
 * @note: The function is only defined in esl_tag_display component (if added)
 *****************************************************************************/
extern sl_status_t esl_display_get_height(uint8_t display_index,
                                          uint16_t *height);

/**************************************************************************//**
 * Get a display type based on display index.
 * @param[in]  display_index The display to get the type of [Assigned Number].
 * @param[out] type Returns type if given display exists.
 * @return sl_status_t SL_STATUS_OK if display_index is valid, error otherwise.
 * @note: The function is only defined in esl_tag_display component (if added)
 *****************************************************************************/
extern sl_status_t esl_display_get_type(uint8_t display_index,
                                        esl_display_type_t *type);

/**************************************************************************//**
 * Select an image storage OTS object.
 * @param[in] data Pointer to ESL OTS object ID 48 bit value in little endian.
 * @param[in] length Must be sizeof(esl_image_object_id_t)
 * @return sl_status_t SL_STATUS_OK if select successful, error code otherwise.
 * @note: The function is only defined in esl_tag_image component (if added)
 *****************************************************************************/
extern sl_status_t esl_image_select_object(void const *data,
                                           uint16_t length);

/**************************************************************************//**
 * Callback on image chunk received event.
 * @param[in] data Pointer to image chunk data.
 * @param[in] offset Start offset of received chunk.
 * @param[in] length Actual length of received chunk.
 * @return sl_status_t SL_STATUS_OK if stored successfully, error otherwise.
 * @note: The function is defined in esl_tag_image component (if added), and is
 * used externally only by esl_tag_cli_test_harness to mimic the image transfer
 * during ESL PTS tests where OTS data transfer itself is far out of scope.
 *****************************************************************************/
extern sl_status_t esl_image_chunk_received(uint8_t const *data,
                                            uint32_t offset,
                                            uint16_t length);

/**************************************************************************//**
 * Request ESL to return the Synchronized state from a connection if it's
 * already synchronized to the AP's PAwR train.
 * @note: Defined in esl_core but not exposed to the public ESL API
 *****************************************************************************/
extern sl_status_t esl_core_update_complete(void);

/**************************************************************************//**
 * Start ESL service advertisement.
 * @note: Defined in esl_core but not exposed to the public ESL API
 *****************************************************************************/
extern sl_status_t esl_core_start_advertising(void);

/**************************************************************************//**
 * Purge any pending responses that aren't sent yet.
 * @note: Defined in esl_tag_response.c but not exposed to the public ESL API
 *****************************************************************************/
extern void esl_core_purge_responses(void);

/**************************************************************************//**
 * Re-schedule pending commands if there're any.
 * @param[in] uint32_t current_absolute_time New ESL Current Absolute Time value
                                             after the clock drift adjustment.
 * @note: Called by esl core internally after absolute time has been adjusted.
 *        The function is defined in esl_tag_opcodes.c
 *****************************************************************************/
extern void esl_reschedule_delayed_commands(uint32_t current_absolute_time);

/**************************************************************************//**
 * Get sync handle.
 * @return The PAwR sync hanle or @ref SL_BT_INVALID_SYNC_HANDLE if ESL is
 *         out of sync.
 * @note: Called by esl core internally on opcodes parsing.
 *        The function is defined in esl_tag_core.c
 *****************************************************************************/
extern uint16_t esl_core_get_sync_handle(void);

/**************************************************************************//**
 * Get request event value for PAwR response.
 * @return The most recent PAwR sync request event value.
 * @note: Called by esl core internally on opcodes parsing.
 *        The function is defined in esl_tag_core.c
 *****************************************************************************/
extern uint16_t esl_core_get_request_event(void);

/**************************************************************************//**
 * Get request subevent value for PAwR response.
 * @return The most recent PAwR sync request subevent value.
 * @note: Called by esl core internally on opcodes parsing.
 *        The function is defined in esl_tag_core.c
 *****************************************************************************/
extern uint8_t esl_core_get_request_subevent(void);

/**************************************************************************//**
 * Invalidate entire ESL configuration to prevent later opcode processing.
 * @note: Called by esl core internally on factory reset opcode execution.
 *        The function is defined in esl_tag_core.c
 *****************************************************************************/
extern void esl_core_invalidate_config(void);

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_INTERNAL_H

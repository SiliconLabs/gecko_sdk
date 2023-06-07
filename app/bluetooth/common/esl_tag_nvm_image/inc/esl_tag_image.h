/***************************************************************************//**
 * @file
 * @brief ESL Tag interface declarations for NVM image functionalities.
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
#ifndef ESL_TAG_RAM_IMAGE_H
#define ESL_TAG_RAM_IMAGE_H
#include <stdint.h>
#include "sl_bt_api.h"
#include "esl_tag_image_core.h"

/**************************************************************************//**
 * Add an ESL Tag image to the list of available images. Any images on a Tag
 * can be only used after adding it to the image registry. This function to be
 * called from @ref esl_core_boot_event.
 *
 * @param[in] uint16_t width Image width in pixels
 * @param[in] uint16_t height Image height in pixels
 * @param[in] uint8_t bits_per_pixel Number of bits representing single pixel of
 *                                   the image.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_image_add(uint16_t width,
                          uint16_t height,
                          uint8_t bits_per_pixel);

/**************************************************************************//**
 * Select an ESL Tag image object to write.
 *
 * @param[in] void const *data pointer to object id
 * @param[in] uint16_t lenght data length in bytes
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_image_select_object(void const *data, uint16_t length);

/**************************************************************************//**
 * Receive one chunk of ESL image data.
 * Current implementation utilizes the NVM as storage target. This function is
 * called by ESL OTS Server subcomponent on receiving partial image data.
 *
 * @param[in] uint8_t const *data pointer to incoming data (e.g. to be put to
 *                                its final storage place by copy)
 * @param[in] uint16_t length Image chunk length in bytes
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_image_chunk_received(uint8_t const *data, uint16_t length);

/**************************************************************************//**
 * User callback called automatically after an image fully received.
 * Can be used e.g. to initiate data transfer to the custom display.
 *****************************************************************************/
void esl_image_receive_finished(void);

#endif // ESL_TAG_RAM_IMAGE_H

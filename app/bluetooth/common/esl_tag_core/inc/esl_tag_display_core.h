/***************************************************************************//**
 * @file
 * @brief ESL Tag core interface declarations for abstract display
 *        functionalities.
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
#ifndef ESL_TAG_DISPLAY_CORE_H
#define ESL_TAG_DISPLAY_CORE_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>
#include "esl_tag_core.h"

/// ESL Display Type Assigned Numbers
#define ESL_DISPLAY_TYPE_BLACK_WHITE            0x01
#define ESL_DISPLAY_TYPE_3_GRAY_SCALE           0x02
#define ESL_DISPLAY_TYPE_4_GRAY_SCALE           0x03
#define ESL_DISPLAY_TYPE_8_GRAY_SCALE           0x04
#define ESL_DISPLAY_TYPE_16_GRAY_SCALE          0x05
#define ESL_DISPLAY_TYPE_RED_BLACK_WHITE        0x06
#define ESL_DISPLAY_TYPE_YELLOW_BLACK_WHITE     0x07
#define ESL_DISPLAY_TYPE_RED_YELLOW_BLACK_WHITE 0x08
#define ESL_DISPLAY_TYPE_7_COLOR                0x09
#define ESL_DISPLAY_TYPE_16_COLOR               0x0A
#define ESL_DISPLAY_TYPE_FULL_RGB               0x0B

/// ESL Display Info Display Type
typedef uint8_t                                 esl_display_type_t;

/// ESL Display Info first class abstract data pointer type
typedef struct esl_display_info_t               *esl_display_info_p;

/**************************************************************************//**
 * ESL Tag display component init function. ESL Core component will call this
 * during the initialization of application. This call is hidden and happens
 * automatically.
 *****************************************************************************/
void esl_display_init(void);

/**************************************************************************//**
 * Refresh the content of the ESL Tag Display.
 * Re-displays the image which was previously set on the given screen.
 * @param[in]  display_index Selects the display to show the image on.
 * @param[out] image_index Returns last image set on the refreshed display.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_display_refresh(uint8_t display_index, uint8_t *image_index);

/**************************************************************************//**
 * Update image data on ESL Tag Display.
 * @param[in] display_index Selects the display to show the image on.
 * @param[in] image_index Selects the image to be shown on the display.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_display_update(uint8_t display_index, uint8_t image_index);

/**************************************************************************//**
 * ESL Display: display count getter
 * @return Number of available displays
 *****************************************************************************/
uint8_t esl_display_get_count();

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_DISPLAY_CORE_H

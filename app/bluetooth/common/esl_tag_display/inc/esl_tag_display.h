/***************************************************************************//**
 * @file
 * @brief ESL Tag interface declarations for abstract display functionalities.
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
#ifndef ESL_TAG_DISPLAY_H
#define ESL_TAG_DISPLAY_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>
#include "esl_tag_core.h"
#include "esl_tag_display_core.h"
#include "esl_tag_display_config.h"

/// ESL Display extra parameters count for init_func esl_va_method function
#define ESL_DISPLAY_INIT_FUNC_PARAMETERS_COUNT    (1)

/// ESL Display extra parameters count for write_func esl_va_method function
#define ESL_DISPLAY_WRITE_FUNC_PARAMETERS_COUNT   (2)

/**************************************************************************//**
 * Create an ESL Tag display. Any display which a Tag wants to implement needs
 * to becreated properly in the first place.
 *
 * @param[in] width Display horizontal pixel count.
 * @param[in] height Display vertical pixel count.
 * @param[in] type Display type defined in BT SIG Assigned Numbers.
 * @param[out] *info esl_display_info_p type pointer to the newly created
 *                   display info data. This value needs to pass to @ref
 *                   esl_display_add call, which has to follow the invocation
 *                   of esl_display_create for any new display to be created,
 *                   fully and properly.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_display_create(uint16_t width,
                               uint16_t height,
                               esl_display_type_t type,
                               esl_display_info_p *info);

/**************************************************************************//**
 * Add an ESL Tag display to the list of available displays after creation. Any
 * display on a Tag can be only used after adding it to the list.
 *
 * @param[in] info esl_display_info_p type pointer, can be get by calling @ref
 *                 esl_display_create previously.
 * @param[in] init_func  esl_va_method_p type pointer to the low-level init
 *                       function of the display driver. Driver implementation,
 *                       however, it's up to the user to implement it properly -
 *                       the only rule is to follow the interface specification
 *                       defined by the @ref esl_va_method_p type. If the 'init'
 *                       method is not necessary for the given display, then a
 *                       NULL pointer can be passed.
 * @param[in] write_func esl_va_method_p type pointer to the low-level write
 *                       function of the display driver. Has to be implemented
 *                       by the users, and it's mandatory (can't be NULL).
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_display_add(esl_display_info_p info,
                            esl_va_method_p init_func,
                            esl_va_method_p write_func);

/**************************************************************************//**
 * ESL display's bluetooth stack event handler.
 * This one runs by the user implementation (usually in app.c) in parallel.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void esl_display_bt_on_event(sl_bt_msg_t *evt);

/**************************************************************************//**
 * ESL Display: chose an image to show. Invokes the users write_func passed to
 * @ref esl_display_add as its 3rd parameter.
 * @param[in] display_index Selects the display to show the image on.
 * @param[in] image_index Selects the image to be shown on the display.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_display_set_image(uint8_t display_index,
                                  uint8_t image_index);

/**************************************************************************//**
 * Display width getter.
 * @param[in] display_index Selects the display to get the width of.
 * @param[out] width Horizontal pixel count of the selected display.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_display_get_width(uint8_t display_index, uint16_t *width);

/**************************************************************************//**
 * Display height getter
 * @param[in] display_index Selects the display to get the height of.
 * @param[out] height Vertical pixel count of the selected display.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_display_get_height(uint8_t display_index, uint16_t *height);

/**************************************************************************//**
 * Display type getter.
 * @param[in] display_index Selects the display to get the type of.
 * @param[out] type esl_display_type_t Display type defined in BT SIG.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_display_get_type(uint8_t display_index,
                                 esl_display_type_t *type);

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_DISPLAY_H

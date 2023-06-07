/***************************************************************************//**
 * @file
 * @brief ESL Tag interface declarations for WSTK LCD display functionalities.
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
#ifndef ESL_TAG_WSTK_LCD_DRIVER_H
#define ESL_TAG_WSTK_LCD_DRIVER_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_wstk_lcd_driver
 * @{
 **************************************************************************************************/
#include "esl_tag_core.h"

/**************************************************************************//**
 * ESL Tag display driver init function. ESL display component will call this
 * during the initialization of application. This call is hidden and happens
 * automatically on Bluetooth @ref sl_bt_evt_system_boot_id event.
 * @param[in] param_count Number of parameters following (mandatory, equals to
 *                        'ESL_DISPLAY_INIT_FUNC_PARAMETERS_COUNT' defined by
 *                        esl_tag_display component.
 * @param[in] index uint8_t type of the display index
 *****************************************************************************/
sl_status_t esl_wstk_lcd_init(int param_count, ...);

/**************************************************************************//**
 * ESL Tag display driver write function.
 * @param[in] param_count Number of parameters following (mandatory, equals to
 *                        'ESL_DISPLAY_WRITE_FUNC_PARAMETERS_COUNT' defined by
 *                        esl_tag_display component.
 * @param[in] display_index uint8_t type of the display index
 * @param[in] image_index uint8_t type of the image index
 *****************************************************************************/
sl_status_t esl_wstk_lcd_write(int param_count, ...);

/**************************************************************************//**
 * ESL WSTK LCD driver's bluetooth stack event handler.
 * This one runs by the user implementation (usually in app.c) in parallel.
 * Adds the WSTK display as the very first display, and initializes it silently.
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void esl_wstk_lcd_bt_on_event(sl_bt_msg_t *evt);

/******************************************************************************
 * ESL Tag WSTK LCD driver's Silabs logo checking function.
 * @return True if the Silabs logo is on the WSTK's display, False if other
 * data is on the display.
 * @note: Called and used by esl demo
 *****************************************************************************/
bool esl_wstk_lcd_is_logo(void);

/******************************************************************************
 * ESL Tag WSTK LCD driver's printing function's WEAK implementation
 * Displays the following message on the WSTK's display in after initialization:
 * "Please run the QRCode generator script"
 * Find the implementation in the ESL Tag Demo component.
 * @note: Called by esl wstk display driver, used by esl demo
 *****************************************************************************/
sl_status_t esl_tag_wstk_lcd_run_qrcode(void);

/** @} (end addtogroup esl_tag_wstk_lcd_driver) */
#endif // ESL_TAG_WSTK_LCD_DRIVER_H

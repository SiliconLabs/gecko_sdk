/***************************************************************************//**
 * @file
 * @brief ESL Tag interface declarations for LED functionalities.
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
#ifndef ESL_TAG_LED_H
#define ESL_TAG_LED_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>
#include "sl_status.h"
#include "esl_tag_core.h"
#include "esl_tag_led_core.h"
#include "esl_tag_led_config.h"

/**************************************************************************//**
 * Add an ESL Tag LED to the list of available LEDs after creation. Any LED
 * on a Tag can be only used after adding it to the internal LED registry.
 *
 * @param[in] type Possible ESL LED type defined by ESL standard
 * @param[in] red_value ESL LED (initial, in case of sRGB type) red color value.
 * @param[in] green_value ESL LED (initial, if sRGB) green color value.
 * @param[in] blue_value ESL LED (initial, if sRGB) blue color value.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_led_add(esl_led_type_t type,
                        uint8_t red_value,
                        uint8_t green_value,
                        uint8_t blue_value);

/**************************************************************************//**
 * ESL Tag LED on function.
 * Simple turn on function with given brightness and color values, to be
 * implemented by end users.
 * It's the users responsibility to actually turn given LED on with the given
 * brightness and color parameters (if applicable) and the function shall
 * return SL_STATUS_OK in case of success.
 * Return SL_STATUS_FAIL on any other case (e.g. index out of bound, detectable
 * HW error etc.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_led_on(uint8_t led_index, esl_led_gamut_control_t gamut);

/**************************************************************************//**
 * ESL Tag LED off function.
 * Simple turn off function, similar to @ref sl_esl_led_on method except it
 * omits the gamut parameter entirely. To be implemented by end users.
 * It's the users responsibility to actually turn given LED off and the
 * function shall return SL_STATUS_OK in case of success.
 * Return SL_STATUS_FAIL on any other case (e.g. index out of bound, detectable
 * HW error etc.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_led_off(uint8_t led_index);

/**************************************************************************//**
 * Assembly ESL Tag LED gamut value from input parameters for @ref
 * esl_led_gamut_control_t type
 * @param[in] red_value ESL LED red color level
 * @param[in] green_value ESL LED red color level
 * @param[in] blue_value ESL LED red color level
 * @param[in] brightness_value ESL LED red color level
 * @return esl_led_gamut_control_t Resulting ESL LED gamut value
 *****************************************************************************/
esl_led_gamut_control_t esl_led_create_color(uint8_t red_value,
                                             uint8_t green_value,
                                             uint8_t blue_value,
                                             uint8_t brightness);

/**************************************************************************//**
 * ESL LED's bluetooth stack event handler.
 * This one runs by the user implementation (usually in app.c) in parallel.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void esl_led_bt_on_event(sl_bt_msg_t *evt);

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_LED_H

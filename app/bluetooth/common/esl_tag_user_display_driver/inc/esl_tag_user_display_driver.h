/***************************************************************************//**
 * @file
 * @brief ESL Tag interface declarations for user defined display driver.
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
#ifndef ESL_TAG_USER_DISPLAY_DRIVER_H
#define ESL_TAG_USER_DISPLAY_DRIVER_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_user_display_driver
 * @{
 **************************************************************************************************/
#include "esl_tag_core.h"

/**************************************************************************//**
 * ESL Tag user defined display driver init function.
 * Function naming is for reference, only - any arbitrary function naming can be
 * used, freely. For more - and especially, different type of displays - there
 * might be a good approach to implement more init functions, also. Then, these
 * functions has to be assigned to the corresponding display during the @ref
 * esl_core_boot_event as follows:
 * @code
 * sl_status_t void esl_core_boot_event(void)
 * {
 *  sl_status_t sc;
 *  esl_display_info_p info;
 *
 *  sc = esl_display_create(<user_display_witdth>,
 *                          <user_display_height>,
 *                          <user_display_type>,
 *                          &info);
 *  app_assert_status(sc);
 *
 *  sc = esl_display_add(info,
 *                       <your_init_function>,      // can be NULL if not needed
 *                       <your_write_function>);    // mandatory!

 *  app_assert_status(sc);
 * }
 * @endcode
 * Note: please do not forget to add #include "esl_display.h", previously.
 * @param[in] param_count Number of parameters following (mandatory, equals to
 *                        'ESL_DISPLAY_INIT_FUNC_PARAMETERS_COUNT' defined by
 *                        esl_tag_display component.
 * @param[in] index uint8_t type of the display index
 *****************************************************************************/
sl_status_t esl_user_display_init(int param_count, ...);

/**************************************************************************//**
 * ESL Tag display user defined driver write function.
 * See the comments at @ref esl_user_display_init function on naming and usage.
 * @param[in] param_count Number of parameters following (mandatory, equals to
 *                        'ESL_DISPLAY_WRITE_FUNC_PARAMETERS_COUNT' defined by
 *                        esl_tag_display component.
 * @param[in] display_index uint8_t type of the display index
 * @param[in] image_index uint8_t type of the image index
 *****************************************************************************/
sl_status_t esl_user_display_write(int param_count, ...);

/** @} (end addtogroup esl_tag_user_display_driver) */
#endif // ESL_TAG_USER_DISPLAY_DRIVER_H

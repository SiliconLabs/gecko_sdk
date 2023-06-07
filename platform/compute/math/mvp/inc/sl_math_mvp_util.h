/***************************************************************************//**
 * @file
 * @brief MVP Math utility functions.
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
#ifndef SL_MATH_MVP_UTIL_H
#define SL_MATH_MVP_UTIL_H

#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup math_mvp_util Utility functions
 * @{
 ******************************************************************************/

/**
 * @brief
 *   Clear all Math exception and fault flags.
 */
void sl_math_mvp_clear_errors(void);

/**
 * @brief
 *   Get a Math exception or fault errorcode and optional descriptive
 *   error message.
 *
 * @details
 *   Intended use of this function is to call it repeatedly to iterate over
 *   existing errors and get errorcodes and optional error message strings.
 *
 * @param[out] error_code
 *   The assigned sl_status_t errorcode.
 *
 * @param[in,out] error_message
 *   A descriptive error message string. Input a NULL pointer to skip
 *   the error message.
 *
 * @param[in] buffer_length
 *   The size of the error_message buffer.
 *
 * @return
 *   Return SL_STATUS_OK when an error is present, this indicates that
 *   error_code and optionally error_message output parameters are valid.
 *   Return SL_STATUS_NOT_FOUND when no error to report.
 */
sl_status_t sl_math_mvp_get_error(sl_status_t *error_code, char *error_message, uint32_t buffer_length);

/** @} (end addtogroup math_mvp_util) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_UTIL_H

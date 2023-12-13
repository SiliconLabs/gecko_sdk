/***************************************************************************//**
 * @file
 * @brief MVP Math Vector Clamp function.
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
#ifndef SL_MATH_MVP_VECTOR_CLAMP_H
#define SL_MATH_MVP_VECTOR_CLAMP_H

#include "sl_status.h"
#include "sl_math_types.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup math_mvp_vector
 * @{
 ******************************************************************************/

/**
 * @brief
 *   Clamp all signed 8 bit integers in a vector to a certain range.
 *
 * @details
 *   Given a min/max value, this function will make sure that none of the element
 *   in the input vector will be < min or > max. If any elements are < min then
 *   the value will be modified to min. If any elements are > max then value will
 *   be modified to max.
 *
 * @param[inout] data Vector with data values.
 * @param[in] num_elements The number of elements in the vector.
 * @param[in] min Minimum value, after operation no elements will be < min.
 * @param[in] max Maximum value, after operation no elements will be > max.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_clamp_i8(int8_t *data, size_t num_elements, int8_t min, int8_t max);

/** @} (end addtogroup math_mvp_vector) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_VECTOR_CLAMP_H

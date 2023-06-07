/***************************************************************************//**
 * @file
 * @brief MVP Math vector dot product functions.
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
#ifndef SL_MATH_MVP_VECTOR_DOT_PRODUCT_H
#define SL_MATH_MVP_VECTOR_DOT_PRODUCT_H

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
 *   Computes the dot product of two vectors.
 *   The vectors are multiplied element-by-element and then summed.
 *
 * @details
 *   All vectors must be of equal length. If all vector buffers are 4-byte
 *   aligned, the function will operate twice as fast using MVP parallel
 *   processing.
 *   Maximum vector length is 1M (2^20), and 2M in the 4-byte aligned case.
 *
 * @note
 *   Depending on the function arguments, the MVP implementation can calculate
 *   the dot product in different ways that may effect the rounding errors.
 *   If the same input vectors are calculated with different memory alignmen,
 *   the results may not be identical.
 *
 * @param[in] input_a Input vector a.
 * @param[in] input_b Input vector b.
 * @param[in] num_elements The number of elements in the input vectors.
 * @param[out] output The result.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_vector_dot_product_f16(const float16_t *input_a,
                                               const float16_t *input_b,
                                               size_t num_elements,
                                               float16_t *output);

/** @} (end addtogroup math_mvp_vector) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_VECTOR_DOT_PRODUCT_H

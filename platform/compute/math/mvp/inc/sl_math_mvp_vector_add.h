/***************************************************************************//**
 * @file
 * @brief MVP Math Vector Add function.
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
#ifndef SL_MATH_MVP_VECTOR_ADD_H
#define SL_MATH_MVP_VECTOR_ADD_H

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
 *   Add two vectors of 16 bit floats.
 *
 * @details
 *   This function will perform the following operation: Z = A + B.
 *   All vectors must be of equal length. If all vector buffers are 4-byte
 *   aligned, the function will operate twice as fast using MVP parallel
 *   processing.
 *   Maximum vector length is 1M (2^20), and 2M in the 4-byte aligned case.
 *
 * @param[in] input_a First input vector, input A.
 * @param[in] input_b Second input vector, input B.
 * @param[out] output Output vector, output Z.
 * @param[in] num_elements The number of elements in the vectors.

 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_vector_add_f16(const float16_t *input_a,
                                       const float16_t *input_b,
                                       float16_t *output,
                                       size_t num_elements);

/**
 * @brief
 *   Add two vectors of signed 8 bit integers.
 *
 * @details
 *   All vectors must be of the same length. This function will perform the
 *   following operation: Z = A + B. The add operation is performing a saturation
 *   add, which means that the operation will never overflow or underflow.
 *   When adding two elements would overflow (>127) then the result
 *   will be 127. When adding two elements would underflow (<-128)
 *   then the result will be -128.
 *
 * @param[in] input_a First input vector, input A.
 * @param[in] input_b Second input vector, input B.
 * @param[out] output Output vector, output Z.
 * @param[in] num_elements The number of elements in the vectors.
 *
 * @return
 *   @ref SL_STATUS_OK.
 */
sl_status_t sl_math_mvp_vector_add_i8(const int8_t *input_a, const int8_t *input_b, int8_t *output, size_t num_elements);

/** @} (end addtogroup math_mvp_vector) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_VECTOR_ADD_H

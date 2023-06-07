/***************************************************************************//**
 * @file
 * @brief MVP Math Mult functions.
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
#ifndef SL_MATH_MVP_COMPLEX_VECTOR_MULT_H
#define SL_MATH_MVP_COMPLEX_VECTOR_MULT_H

#include "sl_status.h"
#include "sl_mvp_types.h"
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
 *   Multiply a vector of complex f16 by a vector of real f16.
 *
 * @details
 *   This function will perform the following operation: Z = A * B.
 *   Both vectors must be of same length. If both vector buffers are 4-byte
 *   aligned, the function will operate twice as fast using MVP complex
 *   processing.
 *   Maximum vector length is 1M (2^20) elements in the 4-byte aligned case,
 *   and 512K when oen or more of the complex vectors are 2-byte aligned.
 *
 * @param[in] input_a The complex vector, input A.
 * @param[in] input_b The real vector, input B.
 * @param[out] output The complex output vector, output Z.
 * @param[in] num_elements The number of elements in the input and output vectors.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_complex_vector_mult_real_f16(const float16_t *input_a,
                                                     const float16_t *input_b,
                                                     float16_t *output,
                                                     size_t num_elements);

/**
 * @brief
 *   Multiply complex f16 vectors.
 *
 * @details
 *   This function will multiply two complex vectors. It is assumed that both
 *   input vectors, and the output vector have same length. All input and output
 *   buffers must be 4-byte aligned.
 *   Maximum vector length is 1M (2^20) elements.
 *
 * @param[in] input_a Complex input vector A.
 * @param[in] input_b Complex input vector B.
 * @param[out] output Complex output vector.
 * @param[in] num_elements The number of complex elements in the input and output vectors.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_complex_vector_mult_f16(const float16_t *input_a,
                                                const float16_t *input_b,
                                                float16_t *output,
                                                size_t num_elements);

/** @} (end addtogroup mvp_math_vector) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_COMPLEX_VECTOR_MULT_H

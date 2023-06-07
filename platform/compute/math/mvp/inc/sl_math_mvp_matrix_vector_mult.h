/***************************************************************************//**
 * @file
 * @brief MVP Math Matrix Vector Mult functions.
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
#ifndef SL_MATH_MVP_MATRIX_VECTOR_MULT_H
#define SL_MATH_MVP_MATRIX_VECTOR_MULT_H

#include "sl_common.h"
#include "sl_math_matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup math_mvp_matrix
 * @{
 ******************************************************************************/

/**
 * @brief
 *   Multiply a matrix with a vector, both of 16 bit floats.
 *
 * @details
 *   This function will perform the following operation: Z = A * b (matrix vector multiplication).
 *   The vector must be equal in length to the number of columns in matrix A. The output vector will be equal in length to the number of rows in matrix A.
 *
 * @param[in] input_a The input matrix.
 * @param[in] input_b The input vector.
 * @param[out] output The output vector.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_matrix_vector_mult_f16(const sl_math_matrix_f16_t *input_a, const float16_t *input_b, float16_t *output);

/** @} (end addtogroup math_mvp_matrix) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_MATRIX_VECTOR_MULT_H

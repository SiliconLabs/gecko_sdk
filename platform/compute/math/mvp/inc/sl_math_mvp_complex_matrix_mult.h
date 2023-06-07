/***************************************************************************//**
 * @file
 * @brief MVP Math Mult functions.
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
#ifndef SL_MATH_MVP_COMPLEX_MATRIX_MULT_H
#define SL_MATH_MVP_COMPLEX_MATRIX_MULT_H

#include "sl_status.h"
#include "sl_math_matrix.h"
#include "sl_mvp_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup math_mvp_matrix
 * @{
 ******************************************************************************/

/**
 * @brief
 *   Multiply two matrices of complex 16 bit floats.
 *
 * @details
 *   The number of columns of the first matrix must be equal to the number of
 *   rows of the second matrix. Also the output matrix row count must match
 *   matrix A row count and output matrix column count must match matrix
 *   B column count.
 *   All input and output matrix data buffers must be 4-byte aligned (a complex
 *   f16 element occupies 4 bytes of storage).
 *   Maximum matrix size is 1024 x 1024 which is 1M (2^20) complex f16 elements.
 *   Maximum column and row size is 1024 elements.
 *
 * @param[in] input_a First input matrix, input A.
 * @param[in] input_b Second input matrix, input B.
 * @param[out] output Output matrix, output Z.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_complex_matrix_mult_f16(const sl_math_matrix_f16_t *input_a,
                                                const sl_math_matrix_f16_t *input_b,
                                                sl_math_matrix_f16_t *output);

/** @} (end addtogroup math_mvp_matrix) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_COMPLEX_MATRIX_MULT_H

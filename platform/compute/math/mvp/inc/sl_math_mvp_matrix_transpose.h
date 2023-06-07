/***************************************************************************//**
 * @file
 * @brief MVP Math Matrix Transpose functions.
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
#ifndef SL_MATH_MVP_MATRIX_TRANSPOSE_H
#define SL_MATH_MVP_MATRIX_TRANSPOSE_H

#include "sl_status.h"
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
 *   Transpose a matrix.
 *
 * @details
 *   This function will fill the output matrix with the transposed version of
 *   the input matrix.
 *   The maximum value for the rows and cols argument is 1024.
 *
 * @param[in] input Input matrix.
 * @param[out] output output matrix.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_matrix_transpose_f16(const sl_math_matrix_f16_t *input,
                                             sl_math_matrix_f16_t *output);

/**
 * @brief
 *   Transpose a complex f16 matrix.
 *
 * @details
 *   This function will fill the output matrix with the transposed version of
 *   the input matrix.
 *   The maximum value for the rows and cols argument is 1024.
 *   Matrix input and output data buffers must be 4-byte aligned.
 *
 * @param[in] input Input matrix.
 * @param[out] output output matrix.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_complex_matrix_transpose_f16(const sl_math_matrix_f16_t *input,
                                                     sl_math_matrix_f16_t *output);

/** @} (end addtogroup math_mvp_matrix) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_MATRIX_TRANSPOSE_H

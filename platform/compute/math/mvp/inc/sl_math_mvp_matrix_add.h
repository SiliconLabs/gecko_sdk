/***************************************************************************//**
 * @file
 * @brief MVP Math Matrix Add function.
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
#ifndef SL_MATH_MVP_MATRIX_ADD_H
#define SL_MATH_MVP_MATRIX_ADD_H

#include "sl_status.h"
#include "sl_mvp.h"
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
 *   Add two matrices of 16 bit floats.
 *
 * @details
 *   This function will perform the following operation: Z = A + B.
 *   All matrices must have equal dimensions. If all matrice buffers are 4-byte
 *   aligned, the function will operate twice as fast using MVP parallel
 *   processing.
 *   Maximum matrices size is 1M (2^20) elements, and 2M elements in the
 *   4-byte aligned case.
 *
 * @param[in] input_a First input matrix, input A.
 * @param[in] input_b Second input matrix, input B.
 * @param[out] output Output matrix, output Z.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_matrix_add_f16(const sl_math_matrix_f16_t *input_a,
                                       const sl_math_matrix_f16_t *input_b,
                                       sl_math_matrix_f16_t *output);

/**
 * @brief
 *   Add two matrices of 16 bit floats.
 *
 * @details
 *   This function will perform the following operation: Z = A + B.
 *   The function do not perform any parameter checking, is assumes that
 *   that has already been taken care of.
 *   If matrice buffers are 4-byte aligned, the function will operate twice as
 *   fast using MVP parallel processing.
 *   Maximum matrices size is 1M (2^20) elements, and 2M elements in the
 *   4-byte aligned case.
 *
 * @param[in] input_a First input matrix data pointer.
 * @param[in] input_b Second input matrix data pointer.
 * @param[out] output Output matrix data pointer.
 * @param[in] num_cols Number of matrix columns.
 * @param[in] num_rows Number of matrix rows.
 * @param[in] data_type @refSLI_MVP_DATATYPE_BINARY16 or @ref SLI_MVP_DATATYPE_COMPLEX_BINARY16.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sli_math_mvp_matrix_add_f16(const float16_t *input_a,
                                        const float16_t *input_b,
                                        float16_t *output,
                                        size_t num_rows,
                                        size_t num_cols,
                                        sli_mvp_datatype_t data_type);

/** @} (end addtogroup math_mvp_matrix) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_MATRIX_ADD_H

/***************************************************************************//**
 * @file
 * @brief Math matrix definitions.
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
#ifndef SL_MATH_MATRIX_H
#define SL_MATH_MATRIX_H

#include <stddef.h>
#include "sl_math_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *  Matrix data type.
 */
typedef struct {
  size_t    num_rows;   ///< The number of rows in the matrix.
  size_t    num_cols;   ///< The number of columns in the matrix.
  float16_t *data;      ///< Pointer to the matrix data.
} sl_math_matrix_f16_t;

/***************************************************************************//**
 * @addtogroup math_mvp_matrix
 * @{
 ******************************************************************************/

/**
 * @brief
 *  Matrix initialization.
 *
 * @param[in] matrix Pointer to a matrix.
 * @param[in] num_rows The number of rows in the matrix.
 * @param[in] num_cols The number of cols in the matrix.
 * @param[in] data A pointer to the matrix data.
 */
void sl_math_matrix_init_f16(sl_math_matrix_f16_t *matrix, size_t num_rows, size_t num_cols, float16_t *data);

/** @} (end addtogroup math_mvp_matrix) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MATRIX_H

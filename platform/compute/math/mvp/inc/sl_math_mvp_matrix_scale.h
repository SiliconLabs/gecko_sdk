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
#ifndef SL_MATH_MVP_MATRIX_SCALE_H
#define SL_MATH_MVP_MATRIX_SCALE_H

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
 *   Scale each element in a float16 matrix by a float16 scale.
 *
 * @details
 *   This function will multiply each element in the input matrix by a scale, and write the result to the output matrix.
 *   The input and output matrices must be the same size.
 * @param[in] input Input matrix.
 * @param[in] scale Scale value.
 * @param[out] output Output matrix.
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sl_math_mvp_matrix_scale_f16(const sl_math_matrix_f16_t *input, float16_t scale, sl_math_matrix_f16_t *output);

/** @} (end addtogroup math_mvp_matrix) */

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_MVP_MATRIX_SCALE_H

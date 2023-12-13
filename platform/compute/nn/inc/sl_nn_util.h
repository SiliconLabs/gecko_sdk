/***************************************************************************//**
 * @file
 * @brief MVP NN utilities.
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
#ifndef SL_NN_UTIL_H
#define SL_NN_UTIL_H

#include "em_device.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
/***************************************************************************//**
 * @addtogroup mvp MVP API
 * @{
 ******************************************************************************/

/// Tensor shape.
typedef struct {
  int dim[4];
} sli_nn_shape_t;

/**
 * @brief
 *   Calculate the offset of a given element in a NHWC formated array.
 *
 * @note
 *   NHWC: N = batch, H = height, W = width, C = channel.
 *   NHWC memory ordering is "row major" within each batch, and is the default
 *   memory ordering used in TensorFlow.
 *   Input parameters n, h, w and c are all zero indexed.
 *
 * @param[in] height Matrix height (rows).
 * @param[in] width  Matrix width (cols).
 * @param[in] depth  Matrix depth (vecs).
 * @param[in] n      batch.
 * @param[in] h      height (row).
 * @param[in] w      width (col).
 * @param[in] c      channel (vec).
 */
__INLINE int sli_nn_calc_offset_nhwc(int height,
                                     int width,
                                     int depth,
                                     int n,
                                     int h,
                                     int w,
                                     int c)
{
  return (((((n * height) + h) * width) + w) * depth) + c;
}

/**
 * @brief
 *   Perform ceiling division.
 *
 * @param[in] dividend Dividend.
 * @param[in] divisor  Divisor
 *
 * @return
 *   Result.
 */
__INLINE int sli_nn_div_ceil_int(const int dividend, const int divisor)
{
  return (dividend / divisor) + (((dividend % divisor) != 0) ? 1 : 0);
}

/**
 * @brief
 *   Perform floor division.
 *
 * @param[in] dividend Dividend.
 * @param[in] divisor  Divisor
 *
 * @return
 *   Result.
 */
__INLINE int sli_nn_div_floor_int(const int dividend, const int divisor)
{
  return dividend / divisor;
}

/** @} (end addtogroup mvp) */
/// @endcond

#ifdef __cplusplus
}
#endif

#endif // SL_NN_UTIL_H

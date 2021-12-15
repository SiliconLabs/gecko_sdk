/***************************************************************************//**
 * @file
 * @brief MVP Utility functions.
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
#ifndef SL_MVP_UTIL_H
#define SL_MVP_UTIL_H

#include "sl_mvp.h"

#define SLI_MVP_INCRDIM_DEPTH   SLI_MVP_INCRDIM_VEC
#define SLI_MVP_INCRDIM_HEIGHT  SLI_MVP_INCRDIM_ROW
#define SLI_MVP_INCRDIM_WIDTH   SLI_MVP_INCRDIM_COL

#define SLI_MVP_RESETDIM_DEPTH  SLI_MVP_RESETDIM_VEC
#define SLI_MVP_RESETDIM_HEIGHT SLI_MVP_RESETDIM_ROW
#define SLI_MVP_RESETDIM_WIDTH  SLI_MVP_RESETDIM_COL

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup mvp_util MVP utility functions.
 * @{
 ******************************************************************************/

/**
 * @brief
 *   Clear memory using MVP.
 *   Will clear 2 * batches * vecs * rows * cols bytes in memory.
 *   This function is a preliminary version of a general purpose function.
 *
 * @note
 *   The function will not wait for MVP execution to complete before exit.
 *
 * @param[in] p Pointer to an initialized program context.
 * @param[in] dst Base address of memory area to clear, must be 4-byte aligned.
 * @param[in] batches Batches.
 * @param[in] vecs Vector dimension size.
 * @param[in] rows Row dimension size.
 * @param[in] cols Column dimension size.
 */
sl_status_t sli_mvp_util_memclr_f16(sli_mvp_program_context_t *p,
                                    void *dst,
                                    unsigned short batches,
                                    unsigned short vecs,
                                    unsigned short rows,
                                    unsigned short cols);

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
__INLINE int sli_mvp_util_offset_nhwc(int height,
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
 *   Configure a MVP array in a program in NHWC or "row major" style.
 *
 * @note
 *   NHWC: N = batch, H = height, W = width, C = channel.
 *   NHWC memory ordering is "row major" within each batch, and is the default
 *   memory ordering used in TensorFlow.
 *   Since MVP handles only three dimensions, we silently treat n (batches)
 *   of nhwc as 1.
 *
 * @param[in] prog  The program to configure.
 * @param[in] index Array index. Values in the range 0-4
 * @param[in] addr  Base address of the array.
 * @param[in] datatype Datatype of each array element.
 * @param[in] h  Matrix height.
 * @param[in] w  Matrix width.
 * @param[in] c  Matrix depth (channels).
 */
__INLINE void sli_mvp_util_prog_set_array_nhwc(sli_mvp_program_t *prog,
                                               uint8_t index,
                                               void *addr,
                                               sli_mvp_datatype_t type,
                                               unsigned short h,
                                               unsigned short w,
                                               unsigned short c)
{
  sli_mvp_prog_set_array_full(prog, index, addr, type,
                              c,        // vecs (DIM0)
                              h,        // rows (DIM1)
                              w,        // cols (DIM2)
                              1,        // vecstride
                              w * c,    // rowstride
                              c);       // colstride
}

/** @} (end addtogroup mvp_util) */

#ifdef __cplusplus
}
#endif

#endif // SL_MVP_UTIL_H

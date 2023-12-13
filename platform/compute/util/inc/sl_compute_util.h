/***************************************************************************//**
 * @file
 * @brief Compute Utility functions.
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
#ifndef SL_COMPUTE_UTIL_H
#define SL_COMPUTE_UTIL_H

#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
/***************************************************************************//**
 * @addtogroup mvp MVP API
 * @{
 ******************************************************************************/

/**
 * @brief
 *   Factorize a number into factors that are not allowed to exceed a
 *   given maximum value.
 *
 * @param[in] number Number to factorize.
 * @param[in] max Maximum factor value allowed.
 * @param[out] m Factor.
 * @param[out] n Factor.
 *
 * @return
 *   @ref SL_STATUS_OK on success, SL_STATUS_FAIL when unable to factorize.
 */
sl_status_t sli_compute_util_factorize_number(uint32_t number,
                                              uint32_t max,
                                              uint32_t *m,
                                              uint32_t *n);

/**
 * @brief
 *   Factorize a number into factors that are optimized for use as loop
 *   iterator counts on a two dimensional array.
 *   Factorization is optimized for parallelisaztion factor 2.
 *
 * @param[in] size  Number to factorize.
 * @param[out] dim0  Factor for DIM0 (inner dimension).
 * @param[out] dim1  Factor for DIM1 (outer dimension).
 * @param[out] remainder  Remainder when factorization is incomplete.
 */
void sli_compute_util_factorize_parallel_2(uint32_t size, uint32_t *dim0, uint32_t *dim1, uint32_t *remainder);

/** @} (end addtogroup mvp) */
/// @endcond

#ifdef __cplusplus
}
#endif

#endif // SL_COMPUTE_UTIL_H

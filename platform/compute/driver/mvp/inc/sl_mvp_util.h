/***************************************************************************//**
 * @file
 * @brief MVP Driver Utility functions.
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
#ifndef SL_MVP_UTIL_H
#define SL_MVP_UTIL_H

#include "sl_mvp.h"

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
sl_status_t sli_mvp_util_factorize_number(uint32_t number,
                                          uint32_t max,
                                          uint32_t *m,
                                          uint32_t *n);

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
 *
 * @return
 *   @ref SL_STATUS_OK on success. On failure, an appropriate sl_status_t
 *   errorcode is returned.
 */
sl_status_t sli_mvp_util_memclr_f16(sli_mvp_program_context_t *p,
                                    void *dst,
                                    unsigned short batches,
                                    unsigned short vecs,
                                    unsigned short rows,
                                    unsigned short cols);

/**
 * @brief
 *   Find out if a pointer is word aligned.
 *
 * @param[in] pointer The pointer to check.
 *
 * @return
 *   True if the pointer is word aligned, false if not.
 */
__INLINE bool sli_mvp_util_is_pointer_word_aligned(const void *pointer)
{
  return ((size_t)pointer & 3) == 0;
}

/** @} (end addtogroup mvp) */
/// @endcond

#ifdef __cplusplus
}
#endif

#endif // SL_MVP_UTIL_H

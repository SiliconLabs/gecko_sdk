/***************************************************************************//**
 * @file
 * @brief MVP Utility functions.
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

#include "sl_compute_util.h"
#include "em_device.h"
#include <stddef.h>

#define SLI_COMPUTE_UTIL_MAX_ARRAY_DIM_SIZE ((_MVP_ARRAYDIM0CFG_SIZE_MASK >> _MVP_ARRAYDIM0CFG_SIZE_SHIFT)+ 1U)

/***************************************************************************//**
 *
 * sli_mvp_util_factorize_number() attempts to factorize a number into
 * factors that are not allowed to exceed a given max value.
 *
 ******************************************************************************/
sl_status_t sli_compute_util_factorize_number(uint32_t number, uint32_t max, uint32_t *m, uint32_t *n)
{
  static const uint8_t primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
  // Try to split the number into two factors that are less than or equal to max factor.
  uint32_t a = 1;
  uint32_t b = number;
  sl_status_t status = SL_STATUS_OK;

  while ((b > max) || (a > max)) {
    uint32_t b_prev = b;
    for (size_t i = 0; i < (sizeof(primes) / sizeof(primes[0])); i++) {
      uint32_t f = primes[i];
      if (b % f == 0) {
        a = a * f;
        b = b / f;
        break;
      }
    }
    if (b == b_prev) {
      // No more factors found
      status = SL_STATUS_FAIL;
      break;
    }
  }

  *m = a;
  *n = b;
  return status;
}

void sli_compute_util_factorize_parallel_2(uint32_t size, uint32_t *dim0, uint32_t *dim1, uint32_t *remainder)
{
  uint32_t tmp;

  *remainder = 0;

  if (size <= SLI_COMPUTE_UTIL_MAX_ARRAY_DIM_SIZE) {
    *dim0 = size;
    *dim1 = 1;

  } else {
    while (sli_compute_util_factorize_number(size, SLI_COMPUTE_UTIL_MAX_ARRAY_DIM_SIZE, dim1, dim0) != SL_STATUS_OK) {
      size--;
      (*remainder)++;
    }

    // Prefer even number for inner dimension.
    if ((*dim0 & 1) == 0) {
      return;
    }

    if ((*dim1 & 1) == 0) {
      tmp = *dim0;
      *dim0 = *dim1;
      *dim1 = tmp;
      return;
    }

    // Prefer largest number for inner dimension.
    if (*dim1 > *dim0) {
      tmp = *dim0;
      *dim0 = *dim1;
      *dim1 = tmp;
    }
  }
}

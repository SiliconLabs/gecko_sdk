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
#include "sl_mvp.h"
#include "sl_mvp_util.h"

extern __INLINE bool sli_mvp_util_is_pointer_word_aligned(const void *pointer);

extern __INLINE int sli_mvp_util_offset_nhwc(int height, int width, int depth,
                                             int n, int h, int w, int c);

/***************************************************************************//**
 *
 * sli_mvp_memclr_f16() clears 2 * batches * vecs * rows * cols bytes in memory.
 * This is a crude attempt at making a general purpose MVP based memclr()
 * function.
 * Assumes that *dst is 4 byte aligned.
 *
 ******************************************************************************/
sl_status_t sli_mvp_util_memclr_f16(sli_mvp_program_context_t *p,
                                    void *dst,
                                    unsigned short batches,
                                    unsigned short vecs,
                                    unsigned short rows,
                                    unsigned short cols)
{
  int depth = vecs;
  int height = rows;
  int width = cols;
  int8_t *dest = dst;
  bool parallel = false;
  sl_status_t status = SL_STATUS_OK;
  unsigned batch_size = 2 * vecs * rows * cols;

  if (depth % 2 == 0) {
    depth /= 2;
    parallel = true;
  } else if (height % 2 == 0) {
    height /= 2;
    parallel = true;
  } else if (width % 2 == 0) {
    width /= 2;
    parallel = true;
  }

  // Loop through batches which is usually only one.
  for (int batch = 0; batch < batches; ++batch) {
    sli_mvp_pb_begin_program(p);
    sli_mvp_prog_set_reg_f16c(p->p, SLI_MVP_R0, 0, 0);
    sli_mvp_pb_config_array_nhwc(p->p,
                                 SLI_MVP_ARRAY(0),
                                 dest,
                                 parallel == true
                                 ? SLI_MVP_DATATYPE_COMPLEX_BINARY16
                                 : SLI_MVP_DATATYPE_BINARY16,
                                 height,
                                 width,
                                 depth,
                                 &status);
    sli_mvp_pb_begin_loop(p, depth, NULL);
      sli_mvp_pb_begin_loop(p, width, NULL);
        sli_mvp_pb_begin_loop(p, height, NULL);
          sli_mvp_pb_compute(p,
                             SLI_MVP_OP(NOOP),
                             SLI_MVP_NONE,
                             SLI_MVP_NONE,
                             SLI_MVP_STORE(SLI_MVP_R0, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_HEIGHT),
                             NULL);
        sli_mvp_pb_end_loop(p);
        sli_mvp_pb_postloop_incr_dim(p, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_WIDTH);
      sli_mvp_pb_end_loop(p);
      sli_mvp_pb_postloop_incr_dim(p, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_DEPTH);
    sli_mvp_pb_end_loop(p);

    if (status == SL_STATUS_OK) {
      sli_mvp_pb_execute_program(p);
    } else {
      return status;
    }
    dest += batch_size;
  }
  return status;
}

/***************************************************************************//**
 *
 * sli_mvp_util_factorize_number() attempts to factorize a number into
 * factors that are not allowed to exceed a given max value.
 *
 ******************************************************************************/
sl_status_t sli_mvp_util_factorize_number(uint32_t number, uint32_t max, uint32_t *m, uint32_t *n)
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

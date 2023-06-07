/***************************************************************************//**
 * @file
 * @brief MVP Math Vector Sub function.
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
#include "sl_mvp.h"
#include "sl_mvp_util.h"
#include "sl_math_mvp_vector_sub.h"
#include "sl_math_mvp_matrix_sub.h"

#define MIN_VECTOR_LEN_FOR_PARALLEL_PROCESSING  480

sl_status_t sl_math_mvp_vector_sub_f16(const float16_t *input_a,
                                       const float16_t *input_b,
                                       float16_t *output,
                                       size_t num_elements)
{
  uint32_t len_vector;
  uint32_t len_remainder;
  size_t ofs_remainder;
  bool use_parallel;
  uint32_t len_parallel;
  uint32_t rows, cols;
  sli_mvp_datatype_t data_type;

  if (!input_a || !input_b || !output || !num_elements) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  len_vector = (uint32_t)num_elements;
  len_parallel = 1U;
  len_remainder = 0U;
  data_type = SLI_MVP_DATATYPE_BINARY16;

  // Check if MVP parallel processing is possible.
  use_parallel = sli_mvp_util_is_pointer_word_aligned(input_a)
                 && sli_mvp_util_is_pointer_word_aligned(input_b)
                 && sli_mvp_util_is_pointer_word_aligned(output)
                 && (len_vector >= 2)
                 && (((len_vector & 1U) == 0) || (len_vector > MIN_VECTOR_LEN_FOR_PARALLEL_PROCESSING));

  if (use_parallel) {
    data_type = SLI_MVP_DATATYPE_COMPLEX_BINARY16;
    len_parallel = 2U;
    if (len_vector & 1U ) {
      len_remainder++;
    }
    len_vector /= 2U;
  }

  // Factorize len_vector into rows * cols.
  if (len_vector <= SLI_MVP_MAX_ROW_LENGTH) {
    rows = 1U;
    cols = len_vector;
  } else {
    while (sli_mvp_util_factorize_number(len_vector, 1024U, &rows, &cols) != SL_STATUS_OK) {
      len_vector--;
      len_remainder += len_parallel;
    }
  }

  sli_math_mvp_matrix_sub_f16(input_a, input_b, output, rows, cols, data_type);
  sli_mvp_cmd_wait_for_completion();

  if (len_remainder > 0) {
    ofs_remainder = num_elements - len_remainder;
    sli_math_mvp_matrix_sub_f16(&input_a[ofs_remainder], &input_b[ofs_remainder], &output[ofs_remainder], 1, len_remainder, SLI_MVP_DATATYPE_BINARY16);
    sli_mvp_cmd_wait_for_completion();
  }

  return sli_mvp_fault_flag ? SL_STATUS_FAIL : SL_STATUS_OK;
}

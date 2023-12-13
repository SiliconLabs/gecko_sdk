/***************************************************************************//**
 * @file
 * @brief MVP Math Vector Add function.
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
#include "sl_mvp_program_area.h"
#include "sl_math_mvp_vector_add.h"
#include "sl_math_mvp_matrix_add.h"

#define MIN_VECTOR_LEN_FOR_PARALLEL_PROCESSING  480

sl_status_t sl_math_mvp_vector_add_f16(const float16_t *input_a,
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
  sl_status_t status;

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
    if (len_vector & 1U) {
      len_remainder++;
    }
    len_vector /= 2U;
  }

  // Factorize vector into rows * cols.
  if (len_vector <= SLI_MVP_MAX_ROW_LENGTH) {
    rows = 1U;
    cols = len_vector;
  } else {
    while (sli_mvp_util_factorize_number(len_vector, 1024U, &rows, &cols) != SL_STATUS_OK) {
      len_vector--;
      len_remainder += len_parallel;
    }
  }

  if ((status = sli_math_mvp_matrix_add_f16(input_a, input_b, output, rows, cols, data_type)) != SL_STATUS_OK) {
    return status;
  }

  if (len_remainder) {
    ofs_remainder = num_elements - len_remainder;
    status = sli_math_mvp_matrix_add_f16(&input_a[ofs_remainder], &input_b[ofs_remainder], &output[ofs_remainder], 1, len_remainder, SLI_MVP_DATATYPE_BINARY16);
  }

  return status;
}

sl_status_t sl_math_mvp_vector_add_i8(const int8_t *input_a, const int8_t *input_b, int8_t *output, size_t num_elements)
{
  sli_mvp_program_t *program = sli_mvp_get_program_area_single();

  // Configure 3 Arrays: Array0 = input_a Array1 = input_b Array2 = output
  sli_mvp_prog_set_vector(program, SLI_MVP_ARRAY(0), (void *)input_a, SLI_MVP_DATATYPE_INT8, (unsigned short)num_elements);
  sli_mvp_prog_set_vector(program, SLI_MVP_ARRAY(1), (void *)input_b, SLI_MVP_DATATYPE_INT8, (unsigned short)num_elements);
  sli_mvp_prog_set_vector(program, SLI_MVP_ARRAY(2), output, SLI_MVP_DATATYPE_INT8, (unsigned short)num_elements);

  // Instruction 0
  // LOAD(Array0,R1)
  // LOAD(Array1,R2)
  // R3 = ADDC(R1,_,R2)
  // STORE(Array2, R3)
  sli_mvp_prog_set_instr(program,
                         SLI_MVP_INSTR(0),
                         SLI_MVP_OP(ADDC),
                         SLI_MVP_ALU_X(SLI_MVP_R1)
                         | SLI_MVP_ALU_A(SLI_MVP_R2)
                         | SLI_MVP_ALU_Z(SLI_MVP_R3),
                         SLI_MVP_LOAD(0, SLI_MVP_R1, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_COL)
                         | SLI_MVP_LOAD(1, SLI_MVP_R2, SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_COL),
                         SLI_MVP_STORE(SLI_MVP_R3, SLI_MVP_ARRAY(2), SLI_MVP_INCRDIM_COL),
                         SLI_MVP_ENDPROG);

  // Loop 0 is the outer loop, counting down columns
  sli_mvp_prog_set_loop(program,
                        SLI_MVP_LOOP(0),
                        (unsigned short)num_elements, // iterate (once for each row)
                        SLI_MVP_INSTR(0),             // starts at Instruction 0
                        SLI_MVP_INSTR(0),             // ends at Instruction 0
                        SLI_MVP_NOINCR,               // No dimension increments
                        SLI_MVP_NORST);               // No dimension resets


  return sli_mvp_prog_execute(program, true);
}

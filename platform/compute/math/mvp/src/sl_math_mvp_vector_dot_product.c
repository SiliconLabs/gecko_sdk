/***************************************************************************//**
 * @file
 * @brief MVP Math vector fill functions.
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
#include "sl_math_mvp_vector_dot_product.h"

#define USE_MVP_PROGRAMBUILDER    0

// The local buffer is required when complex type is used.
// It must be large enough to hold two float16_t after alignment if complex
// type is used.
// This is because the output pointer points to a single float16_t.
static float16_t temporary_buffer[3];

sl_status_t sl_math_mvp_vector_dot_product_f16(const float16_t *input_a,
                                               const float16_t *input_b,
                                               size_t num_elements,
                                               float16_t *output)
{
  sli_mvp_datatype_t data_type;
  uint32_t len_vector;
  uint32_t len_remainder;
  size_t ofs_remainder;
  uint32_t len_parallel;
  uint32_t rows, cols;
  bool use_complex;
  float16_t *temporary_output;
  sl_status_t status = SL_STATUS_OK;

  if (!input_a || !input_b || !output || !num_elements) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  len_vector = (uint32_t)num_elements;
  len_parallel = 1;
  len_remainder = 0;
  data_type = SLI_MVP_DATATYPE_BINARY16;
  temporary_output = output;

  use_complex = sli_mvp_util_is_pointer_word_aligned(input_a)
      && sli_mvp_util_is_pointer_word_aligned(input_b)
      && (num_elements >= 2U);

  if (use_complex) {
    len_parallel = 2U;
    if (len_vector & 1U) {
      len_remainder++;
    }
    data_type = SLI_MVP_DATATYPE_COMPLEX_BINARY16;
    len_vector /= 2U;
    temporary_output = (float16_t *)(((size_t)temporary_buffer + 3) & ~3);
  }

  if (len_vector <= SLI_MVP_MAX_ROW_LENGTH) {
    rows = 1;
    cols = len_vector;
  } else {
    while (sli_mvp_util_factorize_number(len_vector, 1024U, &rows, &cols) != SL_STATUS_OK) {
      len_vector--;
      len_remainder += len_parallel;
    }
  }

  ofs_remainder = num_elements - len_remainder;

#if USE_MVP_PROGRAMBUILDER
  const int vector_x = SLI_MVP_ARRAY(0);
  const int vector_y = SLI_MVP_ARRAY(1);
  const int vector_z = SLI_MVP_ARRAY(2);
  const int vector_x1 = SLI_MVP_ARRAY(3);
  const int vector_y1 = SLI_MVP_ARRAY(4);

  sli_mvp_program_context_t *p = sli_mvp_get_program_area_context();
  sli_mvp_pb_init_program(p);
  sli_mvp_pb_begin_program(p);

  sli_mvp_pb_config_matrix(p->p, vector_x, (void *)input_a, data_type, rows, cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_y, (void *)input_b, data_type, rows, cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_z, temporary_output, data_type, 1, 1, &status);

  sli_mvp_prog_set_reg_f16c(p->p, SLI_MVP_R2, 0, 0);

  sli_mvp_pb_begin_loop(p, rows, &status); {
    sli_mvp_pb_begin_loop(p, cols, &status); {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(MACR2A),
                         SLI_MVP_ALU_X(SLI_MVP_R0)
                         | SLI_MVP_ALU_Y(SLI_MVP_R1)
                         | SLI_MVP_ALU_A(SLI_MVP_R2)
                         | SLI_MVP_ALU_Z(SLI_MVP_R2),
                         SLI_MVP_LOAD(0, SLI_MVP_R0, vector_x, SLI_MVP_INCRDIM_WIDTH)
                         | SLI_MVP_LOAD(1, SLI_MVP_R1, vector_y, SLI_MVP_INCRDIM_WIDTH),
                         0,
                         &status);
    }
    sli_mvp_pb_end_loop(p);
    sli_mvp_pb_postloop_incr_dim(p, vector_x, SLI_MVP_INCRDIM_HEIGHT);
    sli_mvp_pb_postloop_incr_dim(p, vector_y, SLI_MVP_INCRDIM_HEIGHT);
  }
  sli_mvp_pb_end_loop(p);

  if (len_remainder > 0) {
    sli_mvp_pb_config_vector(p->p, vector_x1, (void *)&input_a[ofs_remainder], SLI_MVP_DATATYPE_BINARY16, len_remainder, &status);
    sli_mvp_pb_config_vector(p->p, vector_y1, (void *)&input_b[ofs_remainder], SLI_MVP_DATATYPE_BINARY16, len_remainder, &status);

    sli_mvp_pb_begin_loop(p, len_remainder, &status); {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(MACR2A),
                         SLI_MVP_ALU_X(SLI_MVP_R0)
                         | SLI_MVP_ALU_Y(SLI_MVP_R1)
                         | SLI_MVP_ALU_A(SLI_MVP_R2)
                         | SLI_MVP_ALU_Z(SLI_MVP_R2),
                         SLI_MVP_LOAD(0, SLI_MVP_R0, vector_x1, SLI_MVP_INCRDIM_WIDTH)
                         | SLI_MVP_LOAD(1, SLI_MVP_R1, vector_y1, SLI_MVP_INCRDIM_WIDTH),
                         0,
                         &status);
    }
    sli_mvp_pb_end_loop(p);
  }

  sli_mvp_pb_compute(p,
                      SLI_MVP_OP(ADDR),
                      SLI_MVP_ALU_A(SLI_MVP_R2)
                      | SLI_MVP_ALU_Z(SLI_MVP_R3),
                      0,
                      SLI_MVP_STORE(SLI_MVP_R3, vector_z, SLI_MVP_NOINCR),
                      &status);

  // Check if any errors found during program generation.
  if (status != SL_STATUS_OK) {
    return status;
  }
  if ((status = sli_mvp_pb_execute_program(p)) != SL_STATUS_OK) {
    return status;
  }
#else

  sli_mvp_cmd_enable();

  // Handle the main part.
  // Program array controllers.
  MVP->ARRAY[0].DIM0CFG = MVP->ARRAY[1].DIM0CFG =
    data_type << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;
  MVP->ARRAY[0].DIM1CFG = MVP->ARRAY[1].DIM1CFG =
    ((rows - 1) << _MVP_ARRAYDIM1CFG_SIZE_SHIFT) | (cols << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT);
  MVP->ARRAY[0].DIM2CFG = MVP->ARRAY[1].DIM2CFG =
    ((cols - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT) | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
  MVP->ARRAY[2].DIM0CFG =
    data_type << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;
  MVP->ARRAY[2].DIM1CFG =
    (0 << _MVP_ARRAYDIM1CFG_SIZE_SHIFT)
    | (1 << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT);
  MVP->ARRAY[2].DIM2CFG =
    (0 << _MVP_ARRAYDIM2CFG_SIZE_SHIFT)
    | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
  MVP->ARRAY[0].ADDRCFG = (sli_mvp_addr_reg_t)input_a;
  MVP->ARRAY[1].ADDRCFG = (sli_mvp_addr_reg_t)input_b;
  MVP->ARRAY[2].ADDRCFG = (sli_mvp_addr_reg_t)temporary_output;

  // Clear the result register.
  MVP->ALU[2].REGSTATE = 0;

  // Program loop controllers.
  MVP->LOOP[1].RST = 0;
  MVP->LOOP[0].CFG = (rows - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT;
  MVP->LOOP[1].CFG = ((cols - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT)
                     | ((SLI_MVP_LOOP_INCRDIM(SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_HEIGHT)
                         | SLI_MVP_LOOP_INCRDIM(SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_HEIGHT))
                        << _MVP_LOOPCFG_ARRAY0INCRDIM0_SHIFT);

  // Program instruction.
  MVP->INSTR[0].CFG0 = SLI_MVP_ALU_X(SLI_MVP_R0)
                       | SLI_MVP_ALU_Y(SLI_MVP_R1)
                       | SLI_MVP_ALU_A(SLI_MVP_R2)
                       | SLI_MVP_ALU_Z(SLI_MVP_R2);
  MVP->INSTR[0].CFG1 = SLI_MVP_LOAD(0, SLI_MVP_R0, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_WIDTH)
                       | SLI_MVP_LOAD(1, SLI_MVP_R1, SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_WIDTH);
  MVP->INSTR[0].CFG2 = (SLI_MVP_OP(MACR2A) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                       | MVP_INSTRCFG2_LOOP0BEGIN
                       | MVP_INSTRCFG2_LOOP0END
                       | MVP_INSTRCFG2_LOOP1BEGIN
                       | MVP_INSTRCFG2_LOOP1END;

  size_t last_instruction_idx = 1;

  if (len_remainder > 0) {
    // Handle the remainder.
    // Program array controllers.
    MVP->ARRAY[3].DIM0CFG = MVP->ARRAY[4].DIM0CFG =
      //Note: The remainder can be any size, cannot utilize parallel execution.
      SLI_MVP_DATATYPE_BINARY16 << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;
    MVP->ARRAY[3].DIM1CFG = MVP->ARRAY[4].DIM1CFG =
      0;
    MVP->ARRAY[3].DIM2CFG = MVP->ARRAY[4].DIM2CFG =
      ((len_remainder - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT) | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
    MVP->ARRAY[3].ADDRCFG = (sli_mvp_addr_reg_t)&input_a[ofs_remainder];
    MVP->ARRAY[4].ADDRCFG = (sli_mvp_addr_reg_t)&input_b[ofs_remainder];

    // Program loop controllers.
    MVP->LOOP[2].CFG = (len_remainder - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT;

    // Program instructions.
    MVP->INSTR[1].CFG0 = SLI_MVP_ALU_X(SLI_MVP_R0)
                        | SLI_MVP_ALU_Y(SLI_MVP_R1)
                        | SLI_MVP_ALU_A(SLI_MVP_R2)
                        | SLI_MVP_ALU_Z(SLI_MVP_R2);
    MVP->INSTR[1].CFG1 = SLI_MVP_LOAD(0, SLI_MVP_R0, SLI_MVP_ARRAY(3), SLI_MVP_INCRDIM_WIDTH)
                        | SLI_MVP_LOAD(1, SLI_MVP_R1, SLI_MVP_ARRAY(4), SLI_MVP_INCRDIM_WIDTH);
    MVP->INSTR[1].CFG2 = (SLI_MVP_OP(MACR2A) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                        | MVP_INSTRCFG2_LOOP2BEGIN
                        | MVP_INSTRCFG2_LOOP2END;

    // Move the last instruction index
    last_instruction_idx += 1;
  }

  // And finally, store the result.
  // Program instruction.
  MVP->INSTR[last_instruction_idx].CFG0 = SLI_MVP_ALU_A(SLI_MVP_R2)
                                          | SLI_MVP_ALU_Z(SLI_MVP_R3);
  MVP->INSTR[last_instruction_idx].CFG1 = SLI_MVP_STORE(SLI_MVP_R3, SLI_MVP_ARRAY(2), SLI_MVP_NOINCR);
  MVP->INSTR[last_instruction_idx].CFG2 = (SLI_MVP_OP(ADDR) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                                          | MVP_INSTRCFG2_ENDPROG;

  // Start program.
  MVP->CMD = MVP_CMD_INIT | MVP_CMD_START;
#endif // USE_MVP_PROGRAMBUILDER

  status = sli_mvp_cmd_wait_for_completion();

  if (use_complex) {
    output[0] = temporary_output[0];
  }

  return status;
}

/***************************************************************************//**
 * @file
 * @brief MVP Math Matrix Vector Mult functions.
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
#include "sl_math_mvp.h"
#include "sl_mvp_util.h"
#include "sl_mvp_program_area.h"
#include "sl_common.h"

#define USE_MVP_PROGRAMBUILDER    0

sl_status_t sl_math_mvp_matrix_vector_mult_f16(const sl_math_matrix_f16_t *input_a, const float16_t *input_b, float16_t *output)
{
  // We could have used the normal matrix mult function, but it will not be able to parallelise when B is a vector (num_cols being 1 and not divisible by 2).
  // This function is a different version of the matrix mult function, aimed at transposing B (since B is a vector the transpose is free),
  // and then performing parallelisation of the inner loop gaining up to 2x speedup.

  if (!input_a || !input_b || !output) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  uint32_t a_rows = input_a->num_rows;
  uint32_t a_cols = input_a->num_cols;
  sli_mvp_datatype_t data_type = SLI_MVP_DATATYPE_BINARY16;
  bool parallel = false;

  // Check if all pointers are 4-byte aligned
  if (sli_mvp_util_is_pointer_word_aligned(input_a->data)
      && sli_mvp_util_is_pointer_word_aligned(input_b)
      && sli_mvp_util_is_pointer_word_aligned(output)) {
    // Check that the relevant dimensions are divisible by 2, only need to check input_b because we know output has the same number of columns.
    if ((a_cols % 2 == 0)) {
      // Enable parallel processing
      parallel = true;
      data_type = SLI_MVP_DATATYPE_COMPLEX_BINARY16;
      a_cols /= 2;
    }
  }

  const int matrix_x = SLI_MVP_ARRAY(0);
  const int vector_y = SLI_MVP_ARRAY(1);
  const int vector_z = SLI_MVP_ARRAY(2);
  #if USE_MVP_PROGRAMBUILDER

  sl_status_t status;
  sli_mvp_program_context_t *p = sli_mvp_get_program_area_context();
  sli_mvp_pb_init_program(p);
  sli_mvp_pb_begin_program(p);

  // Configure the matrices
  sli_mvp_pb_config_matrix(p->p, matrix_x, (void*)input_a->data, data_type, a_rows, a_cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_y, (void*)input_b, data_type, 1, a_cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_z, (void*)output, SLI_MVP_DATATYPE_BINARY16, 1, a_rows, &status);

  // This loop moves to the next row of matrix_x
  sli_mvp_pb_begin_loop(p, a_rows, &status); {
    sli_mvp_pb_compute(p,
                       SLI_MVP_OP(CLEAR),
                       SLI_MVP_ALU_Z(SLI_MVP_R3),
                       0,
                       0,
                       &status);
    // This loop calculates the dot product of a row of matrix_x and vector_y
    sli_mvp_pb_begin_loop(p, a_cols, &status); {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(MACR2A),
                         SLI_MVP_ALU_X(SLI_MVP_R1) | SLI_MVP_ALU_Y(SLI_MVP_R2) | SLI_MVP_ALU_A(SLI_MVP_R3) | SLI_MVP_ALU_Z(SLI_MVP_R3),
                         SLI_MVP_LOAD(0, SLI_MVP_R1, matrix_x, SLI_MVP_INCRDIM_COL) | SLI_MVP_LOAD(1, SLI_MVP_R2, vector_y, SLI_MVP_INCRDIM_COL),
                         0,
                         &status);
    }
    sli_mvp_pb_end_loop(p);
    if (parallel) {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(ADDR),
                         SLI_MVP_ALU_A(SLI_MVP_R3) | SLI_MVP_ALU_Z(SLI_MVP_R3),
                         0,
                         SLI_MVP_STORE(SLI_MVP_R3, vector_z, SLI_MVP_INCRDIM_COL),
                         &status);
    } else {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(NOOP),
                         0,
                         0,
                         SLI_MVP_STORE(SLI_MVP_R3, vector_z, SLI_MVP_INCRDIM_COL),
                         &status);
    }

    sli_mvp_pb_postloop_incr_dim(p, matrix_x, SLI_MVP_INCRDIM_ROW);
  }
  sli_mvp_pb_end_loop(p);

  sli_mvp_pb_execute_program(p);
  #else
  sli_mvp_cmd_enable();

  // Program array controllers.
  MVP->ARRAY[0].DIM0CFG = data_type << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;
  MVP->ARRAY[0].DIM1CFG = ((a_rows - 1) << _MVP_ARRAYDIM1CFG_SIZE_SHIFT) | (a_cols << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT);
  MVP->ARRAY[0].DIM2CFG = ((a_cols - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT) | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
  MVP->ARRAY[0].ADDRCFG = (size_t)input_a->data;

  MVP->ARRAY[1].DIM0CFG = data_type << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;
  MVP->ARRAY[1].DIM1CFG = ((1 - 1) << _MVP_ARRAYDIM1CFG_SIZE_SHIFT) | (a_cols << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT);
  MVP->ARRAY[1].DIM2CFG = ((a_cols - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT) | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
  MVP->ARRAY[1].ADDRCFG = (size_t)input_b;

  MVP->ARRAY[2].DIM0CFG = SLI_MVP_DATATYPE_BINARY16 << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;
  MVP->ARRAY[2].DIM1CFG = ((1 - 1) << _MVP_ARRAYDIM1CFG_SIZE_SHIFT) | (a_rows << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT);
  MVP->ARRAY[2].DIM2CFG = ((a_rows - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT) | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
  MVP->ARRAY[2].ADDRCFG = (size_t)output;

  // Program loop controllers.

  MVP->LOOP[1].RST = 0;

  MVP->LOOP[0].CFG = ((a_rows - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT);
  MVP->LOOP[1].CFG = ((a_cols - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT)
                     | ((SLI_MVP_LOOP_INCRDIM(matrix_x, SLI_MVP_INCRDIM_ROW)) << _MVP_LOOPCFG_ARRAY0INCRDIM0_SHIFT);

  // Program instruction.
  MVP->INSTR[0].CFG0 = SLI_MVP_ALU_Z(SLI_MVP_R3);
  MVP->INSTR[0].CFG1 = 0;
  MVP->INSTR[0].CFG2 = (SLI_MVP_OP(CLEAR) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                       | MVP_INSTRCFG2_LOOP0BEGIN;

  MVP->INSTR[1].CFG0 =  SLI_MVP_ALU_X(SLI_MVP_R1) | SLI_MVP_ALU_Y(SLI_MVP_R2) | SLI_MVP_ALU_A(SLI_MVP_R3) | SLI_MVP_ALU_Z(SLI_MVP_R3);
  MVP->INSTR[1].CFG1 = SLI_MVP_LOAD(0, SLI_MVP_R1, matrix_x, SLI_MVP_INCRDIM_COL) | SLI_MVP_LOAD(1, SLI_MVP_R2, vector_y, SLI_MVP_INCRDIM_COL);
  MVP->INSTR[1].CFG2 = (SLI_MVP_OP(MACR2A) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                       | MVP_INSTRCFG2_LOOP1BEGIN
                       | MVP_INSTRCFG2_LOOP1END;
  if (parallel) {
    MVP->INSTR[2].CFG0 = SLI_MVP_ALU_A(SLI_MVP_R3) | SLI_MVP_ALU_Z(SLI_MVP_R3);
    MVP->INSTR[2].CFG1 = SLI_MVP_STORE(SLI_MVP_R3, vector_z, SLI_MVP_INCRDIM_COL);
    MVP->INSTR[2].CFG2 = (SLI_MVP_OP(ADDR) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                         | MVP_INSTRCFG2_LOOP0END
                         | MVP_INSTRCFG2_ENDPROG;
  } else {
    MVP->INSTR[2].CFG0 = 0;
    MVP->INSTR[2].CFG1 = SLI_MVP_STORE(SLI_MVP_R3, vector_z, SLI_MVP_INCRDIM_COL);
    MVP->INSTR[2].CFG2 = (SLI_MVP_OP(NOOP) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                         | MVP_INSTRCFG2_LOOP0END
                         | MVP_INSTRCFG2_ENDPROG;
  }

  // Start program.
  MVP->CMD = MVP_CMD_INIT | MVP_CMD_START;

  #endif

  sli_mvp_cmd_wait_for_completion();

  return sli_mvp_fault_flag ? SL_STATUS_FAIL : SL_STATUS_OK;
}

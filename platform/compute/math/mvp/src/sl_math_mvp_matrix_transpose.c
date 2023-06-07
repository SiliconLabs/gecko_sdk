/***************************************************************************//**
 * @file
 * @brief MVP Math Transpose functions.
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
#include "sl_mvp_program_area.h"
#include "sl_math_mvp_matrix_transpose.h"

static sl_status_t matrix_transpose(const sl_math_matrix_f16_t *input,
                                    sl_math_matrix_f16_t *output,
                                    sli_mvp_datatype_t data_type);

sl_status_t sl_math_mvp_matrix_transpose_f16(const sl_math_matrix_f16_t *input,
                                             sl_math_matrix_f16_t *output)
{
  return matrix_transpose(input, output, SLI_MVP_DATATYPE_BINARY16);
}

sl_status_t sl_math_mvp_complex_matrix_transpose_f16(const sl_math_matrix_f16_t *input,
                                                     sl_math_matrix_f16_t *output)
{
  // We only process matrices that are word (4-byte) aligned.
  if (!sli_mvp_util_is_pointer_word_aligned(input->data)
      || !sli_mvp_util_is_pointer_word_aligned(output->data)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  return matrix_transpose(input, output, SLI_MVP_DATATYPE_COMPLEX_BINARY16);
}

static sl_status_t matrix_transpose(const sl_math_matrix_f16_t *input,
                                    sl_math_matrix_f16_t *output,
                                    sli_mvp_datatype_t data_type)
{
  if (!input || !output) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if ((input->num_cols == 0)
      || (input->num_rows == 0)
      || (output->num_cols == 0)
      || (output->num_rows == 0)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (input->num_rows != output->num_cols || input->num_cols != output->num_rows) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if ((input->num_rows > SLI_MVP_MAX_ROW_LENGTH)
      || (input->num_cols > SLI_MVP_MAX_COLUMN_LENGTH)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

#if 0
  // This is the reference MVP program for the optimized setup below.

  sl_status_t status = SL_STATUS_OK;
  const int vector_x = SLI_MVP_ARRAY(0);
  const int vector_z = SLI_MVP_ARRAY(1);

  sli_mvp_program_context_t *p = sli_mvp_get_program_area_context();
  sli_mvp_pb_init_program(p);
  sli_mvp_pb_begin_program(p);

  sli_mvp_pb_config_matrix(p->p, vector_x, input->data, data_type, input->num_rows, input->num_cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_z, output->data, data_type, output->num_rows, output->num_cols, &status);

  sli_mvp_pb_begin_loop(p, input->num_rows, &status); {
    sli_mvp_pb_begin_loop(p, input->num_cols, &status); {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(COPY),
                         SLI_MVP_ALU_A(SLI_MVP_R0)
                         | SLI_MVP_ALU_Z(SLI_MVP_R1),
                         SLI_MVP_LOAD(0, SLI_MVP_R0, vector_x, SLI_MVP_INCRDIM_WIDTH),
                         SLI_MVP_STORE(SLI_MVP_R1, vector_z, SLI_MVP_INCRDIM_HEIGHT),
                         &status);
    }
    sli_mvp_pb_end_loop(p);
    sli_mvp_pb_postloop_incr_dim(p, vector_x, SLI_MVP_INCRDIM_HEIGHT);
    sli_mvp_pb_postloop_incr_dim(p, vector_z, SLI_MVP_INCRDIM_WIDTH);
  }
  sli_mvp_pb_end_loop(p);

  // Check if any errors found during program generation.
  if (status != SL_STATUS_OK) {
    return status;
  }

  sli_mvp_pb_execute_program(p);
#else

  sli_mvp_cmd_enable();

  // Program array controllers.
  MVP->ARRAY[0].DIM0CFG = MVP->ARRAY[1].DIM0CFG =
    data_type << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;

  MVP->ARRAY[0].DIM1CFG =
    (((uint32_t)input->num_rows - 1) << _MVP_ARRAYDIM1CFG_SIZE_SHIFT)
    | ((uint32_t)input->num_cols << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT);
  MVP->ARRAY[0].DIM2CFG =
    (((uint32_t)input->num_cols - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT)
    | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
  MVP->ARRAY[0].ADDRCFG = (size_t)input->data;
  MVP->ARRAY[1].DIM1CFG =
    (((uint32_t)output->num_rows - 1) << _MVP_ARRAYDIM1CFG_SIZE_SHIFT)
    | ((uint32_t)output->num_cols << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT);
  MVP->ARRAY[1].DIM2CFG =
    (((uint32_t)output->num_cols - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT)
    | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
  MVP->ARRAY[1].ADDRCFG = (size_t)output->data;

  // Program loop controllers.
  MVP->LOOP[1].RST = 0;
  MVP->LOOP[0].CFG = ((uint32_t)input->num_rows - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT;
  MVP->LOOP[1].CFG = (((uint32_t)input->num_cols - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT)
                     | ((SLI_MVP_LOOP_INCRDIM(SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_HEIGHT)
                         | SLI_MVP_LOOP_INCRDIM(SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_WIDTH))
                        << _MVP_LOOPCFG_ARRAY0INCRDIM0_SHIFT);

  // Program instruction.
  MVP->INSTR[0].CFG0 = SLI_MVP_ALU_A(SLI_MVP_R0) | SLI_MVP_ALU_Z(SLI_MVP_R1);
  MVP->INSTR[0].CFG1 = SLI_MVP_LOAD(0, SLI_MVP_R0, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_WIDTH)
                       | SLI_MVP_STORE(SLI_MVP_R1, SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_HEIGHT);
  MVP->INSTR[0].CFG2 = (SLI_MVP_OP(COPY) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                       | MVP_INSTRCFG2_LOOP0BEGIN
                       | MVP_INSTRCFG2_LOOP0END
                       | MVP_INSTRCFG2_LOOP1BEGIN
                       | MVP_INSTRCFG2_LOOP1END
                       | MVP_INSTRCFG2_ENDPROG;

  // Start program.
  MVP->CMD = MVP_CMD_INIT | MVP_CMD_START;

#endif

  sli_mvp_cmd_wait_for_completion();

  return sli_mvp_fault_flag ? SL_STATUS_FAIL : SL_STATUS_OK;
}

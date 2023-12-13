/***************************************************************************//**
 * @file
 * @brief MVP Math Matrix Add function.
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
#include "sl_math_mvp_matrix_add.h"
#include "sl_math_mvp_vector_add.h"

#define USE_MVP_PROGRAMBUILDER    0

sl_status_t sl_math_mvp_matrix_add_f16(const sl_math_matrix_f16_t *input_a,
                                       const sl_math_matrix_f16_t *input_b,
                                       sl_math_matrix_f16_t *output)
{
  uint32_t rows, cols;
  sli_mvp_datatype_t data_type;

  if (!input_a || !input_b || !output) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (!((input_a->num_rows == input_b->num_rows) && (input_b->num_rows == output->num_rows))
      || !((input_a->num_cols == input_b->num_cols) && (input_b->num_cols == output->num_cols))) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  rows = (uint32_t)input_a->num_rows;
  cols = (uint32_t)input_a->num_cols;
  data_type = SLI_MVP_DATATYPE_BINARY16;

  // Is parallel processing possible ?
  if (sli_mvp_util_is_pointer_word_aligned(input_a->data)
      && sli_mvp_util_is_pointer_word_aligned(input_b->data)
      && sli_mvp_util_is_pointer_word_aligned(output->data)
      && ((rows * cols) >= 2U)) {
    if (((rows & 1U) == 0U) && ((cols & 1U) == 0U)) {
      if (rows > cols) {
        rows /= 2U;
      } else {
        cols /= 2U;
      }
      data_type = SLI_MVP_DATATYPE_COMPLEX_BINARY16;
    } else if ((rows & 1U) == 0U) {
      rows /= 2U;
      data_type = SLI_MVP_DATATYPE_COMPLEX_BINARY16;
    } else if ((cols & 1U) == 0U) {
      cols /= 2U;
      data_type = SLI_MVP_DATATYPE_COMPLEX_BINARY16;
    }
  }

  // Size outside of MVP dimension size limit ?
  if ((rows > SLI_MVP_MAX_ROW_LENGTH) || (cols > SLI_MVP_MAX_COLUMN_LENGTH)) {
    return sl_math_mvp_vector_add_f16(input_a->data,
                                      input_b->data,
                                      output->data,
                                      input_a->num_rows * input_a->num_cols);
  }

  if (!input_a->data || !input_b->data || !output->data
      || !input_a->num_rows || !input_a->num_cols) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  return sli_math_mvp_matrix_add_f16(input_a->data, input_b->data, output->data,
                                     rows, cols, data_type);
}

sl_status_t sli_math_mvp_matrix_add_f16(const float16_t *input_a,
                                        const float16_t *input_b,
                                        float16_t *output,
                                        size_t num_rows,
                                        size_t num_cols,
                                        sli_mvp_datatype_t data_type)
{
  uint32_t rows, cols;

  rows = (uint32_t)num_rows;
  cols = (uint32_t)num_cols;

#if USE_MVP_PROGRAMBUILDER
  // This is the reference MVP program for the optimized setup below.

  sl_status_t status = SL_STATUS_OK;
  const int vector_x = SLI_MVP_ARRAY(0);
  const int vector_y = SLI_MVP_ARRAY(1);
  const int vector_z = SLI_MVP_ARRAY(2);

  sli_mvp_program_context_t *p = sli_mvp_get_program_area_context();
  sli_mvp_pb_init_program(p);
  sli_mvp_pb_begin_program(p);

  sli_mvp_pb_config_matrix(p->p, vector_x, (void*)input_a, data_type, rows, cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_y, (void*)input_b, data_type, rows, cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_z, (void*)output,  data_type, rows, cols, &status);

  sli_mvp_pb_begin_loop(p, rows, &status); {
    sli_mvp_pb_begin_loop(p, cols, &status); {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(ADDC),
                         SLI_MVP_ALU_X(SLI_MVP_R1)
                         | SLI_MVP_ALU_A(SLI_MVP_R2)
                         | SLI_MVP_ALU_Z(SLI_MVP_R3),
                         SLI_MVP_LOAD(0, SLI_MVP_R1, vector_x, SLI_MVP_INCRDIM_WIDTH)
                         | SLI_MVP_LOAD(1, SLI_MVP_R2, vector_y, SLI_MVP_INCRDIM_WIDTH),
                         SLI_MVP_STORE(SLI_MVP_R3, vector_z, SLI_MVP_INCRDIM_WIDTH),
                         &status);
    }
    sli_mvp_pb_end_loop(p);
    sli_mvp_pb_postloop_incr_dim(p, vector_x, SLI_MVP_INCRDIM_HEIGHT);
    sli_mvp_pb_postloop_incr_dim(p, vector_y, SLI_MVP_INCRDIM_HEIGHT);
    sli_mvp_pb_postloop_incr_dim(p, vector_z, SLI_MVP_INCRDIM_HEIGHT);
  }
  sli_mvp_pb_end_loop(p);
  if ((status = sli_mvp_pb_execute_program(p)) != SL_STATUS_OK) {
    return status;
  }
#else

  sli_mvp_cmd_enable();

  // Program array controllers.
  MVP->ARRAY[0].DIM0CFG = MVP->ARRAY[1].DIM0CFG = MVP->ARRAY[2].DIM0CFG =
    data_type << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;
  MVP->ARRAY[0].DIM1CFG = MVP->ARRAY[1].DIM1CFG = MVP->ARRAY[2].DIM1CFG =
    ((rows - 1) << _MVP_ARRAYDIM1CFG_SIZE_SHIFT) | (cols << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT);
  MVP->ARRAY[0].DIM2CFG = MVP->ARRAY[1].DIM2CFG = MVP->ARRAY[2].DIM2CFG =
    ((cols - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT) | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
  MVP->ARRAY[0].ADDRCFG = (sli_mvp_addr_reg_t)input_a;
  MVP->ARRAY[1].ADDRCFG = (sli_mvp_addr_reg_t)input_b;
  MVP->ARRAY[2].ADDRCFG = (sli_mvp_addr_reg_t)output;

  // Program loop controllers.
  MVP->LOOP[1].RST = 0;
  MVP->LOOP[0].CFG = (rows - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT;
  MVP->LOOP[1].CFG = ((cols - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT)
                     | ((SLI_MVP_LOOP_INCRDIM(SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_HEIGHT)
                         | SLI_MVP_LOOP_INCRDIM(SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_HEIGHT)
                         | SLI_MVP_LOOP_INCRDIM(SLI_MVP_ARRAY(2), SLI_MVP_INCRDIM_HEIGHT))
                        << _MVP_LOOPCFG_ARRAY0INCRDIM0_SHIFT);

  // Program instruction.
  MVP->INSTR[0].CFG0 = SLI_MVP_ALU_X(SLI_MVP_R1) | SLI_MVP_ALU_A(SLI_MVP_R2) | SLI_MVP_ALU_Z(SLI_MVP_R3);
  MVP->INSTR[0].CFG1 = SLI_MVP_LOAD(0, SLI_MVP_R1, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_WIDTH)
                       | SLI_MVP_LOAD(1, SLI_MVP_R2, SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_WIDTH)
                       | SLI_MVP_STORE(SLI_MVP_R3, SLI_MVP_ARRAY(2), SLI_MVP_INCRDIM_WIDTH);
  MVP->INSTR[0].CFG2 = (SLI_MVP_OP(ADDC) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                       | MVP_INSTRCFG2_ENDPROG
                       | MVP_INSTRCFG2_LOOP0BEGIN
                       | MVP_INSTRCFG2_LOOP0END
                       | MVP_INSTRCFG2_LOOP1BEGIN
                       | MVP_INSTRCFG2_LOOP1END;

  // Start program.
  MVP->CMD = MVP_CMD_INIT | MVP_CMD_START;
#endif

  return sli_mvp_cmd_wait_for_completion();
}

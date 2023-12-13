/***************************************************************************//**
 * @file
 * @brief MVP Math Mul functions.
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
#include "sl_math_mvp.h"
#include "sl_mvp_util.h"
#include "sl_mvp_program_area.h"
#include "sl_common.h"

#define USE_MVP_PROGRAMBUILDER    0

#if USE_MVP_PROGRAMBUILDER
#define MIN_VECTOR_LEN_FOR_PARALLEL_PROCESSING  1000
#else
#define MIN_VECTOR_LEN_FOR_PARALLEL_PROCESSING  320
#endif

sl_status_t sl_math_mvp_vector_mult_f16(const float16_t *input_a, const float16_t *input_b, float16_t *output, size_t num_elements)
{
  uint32_t len_vector;
  uint32_t len_remainder;
  size_t ofs_remainder;
  bool use_parallel;
  uint32_t len_parallel;
  uint32_t rows, cols;
  sl_status_t status;
  sli_mvp_datatype_t data_type = SLI_MVP_DATATYPE_BINARY16;

  if (!input_a || !input_b || !output || !num_elements) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  len_vector = (uint32_t)num_elements;
  len_remainder = 0;
  len_parallel = 1;

  // Check if MVP parallel processing is possible and preferred.
  use_parallel = sli_mvp_util_is_pointer_word_aligned(input_a)
                 && sli_mvp_util_is_pointer_word_aligned(input_b)
                 && sli_mvp_util_is_pointer_word_aligned(output)
                 && (len_vector >= 2)
                 && (((len_vector & 1U) == 0) || (len_vector > MIN_VECTOR_LEN_FOR_PARALLEL_PROCESSING));

  if (use_parallel) {
    data_type = SLI_MVP_DATATYPE_COMPLEX_BINARY16;
    len_parallel = 2;
    if (len_vector & 1U) {
      len_remainder++;
    }
    len_vector /= 2;
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

  sli_mvp_program_context_t *p = sli_mvp_get_program_area_context();
  sli_mvp_pb_init_program(p);
  sli_mvp_pb_begin_program(p);

  sli_mvp_pb_config_matrix(p->p, vector_x, (void *)input_a, data_type, rows, cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_y, (void *)input_b, data_type, rows, cols, &status);
  sli_mvp_pb_config_matrix(p->p, vector_z, (void *)output, data_type, rows, cols, &status);
  sli_mvp_pb_begin_loop(p, rows, &status); {
    sli_mvp_pb_begin_loop(p, cols, &status); {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(MULR2A),
                         SLI_MVP_ALU_X(SLI_MVP_R1) | SLI_MVP_ALU_Y(SLI_MVP_R2) | SLI_MVP_ALU_Z(SLI_MVP_R3),
                         SLI_MVP_LOAD(0, SLI_MVP_R1, vector_x, SLI_MVP_INCRDIM_WIDTH) | SLI_MVP_LOAD(1, SLI_MVP_R2, vector_y, SLI_MVP_INCRDIM_WIDTH),
                         SLI_MVP_STORE(SLI_MVP_R3, vector_z, SLI_MVP_INCRDIM_WIDTH),
                         &status);
    }
    sli_mvp_pb_end_loop(p);
    sli_mvp_pb_postloop_incr_dim(p, vector_x, SLI_MVP_INCRDIM_HEIGHT);
    sli_mvp_pb_postloop_incr_dim(p, vector_y, SLI_MVP_INCRDIM_HEIGHT);
    sli_mvp_pb_postloop_incr_dim(p, vector_z, SLI_MVP_INCRDIM_HEIGHT);
  }
  sli_mvp_pb_end_loop(p);

  // Check if any errors found during program generation.
  if (status != SL_STATUS_OK) {
    return status;
  }
  if ((status = sli_mvp_pb_execute_program(p)) != SL_STATUS_OK) {
    return status;
  }

  if (len_remainder > 0) {
    sli_mvp_pb_config_vector(p->p, vector_x, (void *)&input_a[ofs_remainder], SLI_MVP_DATATYPE_BINARY16, len_remainder, &status);
    sli_mvp_pb_config_vector(p->p, vector_y, (void *)&input_b[ofs_remainder], SLI_MVP_DATATYPE_BINARY16, len_remainder, &status);
    sli_mvp_pb_config_vector(p->p, vector_z, (void *)&output[ofs_remainder], SLI_MVP_DATATYPE_BINARY16, len_remainder, &status);

    sli_mvp_pb_begin_loop(p, len_remainder, &status); {
      sli_mvp_pb_compute(p,
                         SLI_MVP_OP(MULR2A),
                         SLI_MVP_ALU_X(SLI_MVP_R1) | SLI_MVP_ALU_Y(SLI_MVP_R2) | SLI_MVP_ALU_Z(SLI_MVP_R3),
                         SLI_MVP_LOAD(0, SLI_MVP_R1, vector_x, SLI_MVP_INCRDIM_WIDTH) | SLI_MVP_LOAD(1, SLI_MVP_R2, vector_y, SLI_MVP_INCRDIM_WIDTH),
                         SLI_MVP_STORE(SLI_MVP_R3, vector_z, SLI_MVP_INCRDIM_WIDTH),
                         &status);
    }
    sli_mvp_pb_end_loop(p);

    // Check if any errors found during program generation.
    if (status != SL_STATUS_OK) {
      return status;
    }
    if ((status = sli_mvp_pb_execute_program(p)) != SL_STATUS_OK) {
      return status;
    }
  }
  status = sli_mvp_cmd_wait_for_completion();
#else

  sli_mvp_cmd_enable();

  // Handle the main part.
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
  MVP->INSTR[0].CFG0 = SLI_MVP_ALU_X(SLI_MVP_R1) | SLI_MVP_ALU_Y(SLI_MVP_R2) | SLI_MVP_ALU_Z(SLI_MVP_R3);
  MVP->INSTR[0].CFG1 = SLI_MVP_LOAD(0, SLI_MVP_R1, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_WIDTH)
                       | SLI_MVP_LOAD(1, SLI_MVP_R2, SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_WIDTH)
                       | SLI_MVP_STORE(SLI_MVP_R3, SLI_MVP_ARRAY(2), SLI_MVP_INCRDIM_WIDTH);
  MVP->INSTR[0].CFG2 = (SLI_MVP_OP(MULR2A) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                       | MVP_INSTRCFG2_ENDPROG
                       | MVP_INSTRCFG2_LOOP0BEGIN
                       | MVP_INSTRCFG2_LOOP0END
                       | MVP_INSTRCFG2_LOOP1BEGIN
                       | MVP_INSTRCFG2_LOOP1END;

  // Start program.
  MVP->CMD = MVP_CMD_INIT | MVP_CMD_START;

  // Wait for the program completion.
  if ((status = sli_mvp_cmd_wait_for_completion()) != SL_STATUS_OK) {
    return status;
  }

  if (len_remainder > 0) {
    // Handle the remainder.
    // Program array controllers.
    MVP->ARRAY[0].DIM0CFG = MVP->ARRAY[1].DIM0CFG = MVP->ARRAY[2].DIM0CFG =
      //Note: The remainder can be any size, cannot utilize parallel execution.
      SLI_MVP_DATATYPE_BINARY16 << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT;
    MVP->ARRAY[0].DIM1CFG = MVP->ARRAY[1].DIM1CFG = MVP->ARRAY[2].DIM1CFG =
      0;
    MVP->ARRAY[0].DIM2CFG = MVP->ARRAY[1].DIM2CFG = MVP->ARRAY[2].DIM2CFG =
      ((len_remainder - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT) | (1 << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT);
    MVP->ARRAY[0].ADDRCFG = (sli_mvp_addr_reg_t)&input_a[ofs_remainder];
    MVP->ARRAY[1].ADDRCFG = (sli_mvp_addr_reg_t)&input_b[ofs_remainder];
    MVP->ARRAY[2].ADDRCFG = (sli_mvp_addr_reg_t)&output[ofs_remainder];

    // Program loop controllers.
    MVP->LOOP[0].CFG = (len_remainder - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT;

    // Program instruction.
    MVP->INSTR[0].CFG0 = SLI_MVP_ALU_X(SLI_MVP_R1) | SLI_MVP_ALU_Y(SLI_MVP_R2) | SLI_MVP_ALU_Z(SLI_MVP_R3);
    MVP->INSTR[0].CFG1 = SLI_MVP_LOAD(0, SLI_MVP_R1, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_WIDTH)
                        | SLI_MVP_LOAD(1, SLI_MVP_R2, SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_WIDTH)
                        | SLI_MVP_STORE(SLI_MVP_R3, SLI_MVP_ARRAY(2), SLI_MVP_INCRDIM_WIDTH);
    MVP->INSTR[0].CFG2 = (SLI_MVP_OP(MULR2A) << _MVP_INSTRCFG2_ALUOP_SHIFT)
                        | MVP_INSTRCFG2_ENDPROG
                        | MVP_INSTRCFG2_LOOP0BEGIN
                        | MVP_INSTRCFG2_LOOP0END;

    // Start program.
    MVP->CMD = MVP_CMD_INIT | MVP_CMD_START;

    // Wait for the program completion.
    status = sli_mvp_cmd_wait_for_completion();
  }
  #endif

  return status;
}

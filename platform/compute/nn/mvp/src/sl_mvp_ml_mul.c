/***************************************************************************//**
 * @file
 * @brief MVP mul kernel driver.
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

#include "sl_mvp_ml_mul.h"
#include "sl_mvp.h"
#include "sl_math_mvp.h"
#include "sl_mvp_program_area.h"
#include "sl_common.h"
#include <stdbool.h>
#include <math.h>

sl_status_t sli_mvp_ml_mul_s8(const sli_mvp_ml_mul_s8_params_t *params)
{
  if (!params) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_status_t status;
  sli_mvp_program_t *prog = sli_mvp_get_program_area_single();

  int remaining = params->length;
  const int8_t *input1_data = params->input1;
  const int8_t *input2_data = params->input2;
  int8_t *output_data = params->output;

  // *INDENT-OFF*
  /*
     Software Reference:

     This is the reference algorithm for the mul operation.

     for (size_t i = 0; i < params->length; ++i) {
       float input1_val = input1[i] + input1_offset;
       float input2_val = input2[i] + input2_offset;
       float output_val = (input1_val * input2_val) * output_multiplier + output_offset;
       output_val = round(output_val);
       output[i] = clamp(output_val, activation_min, activation_max);
     }

     We can get the core loop without the clamp operation down to 4 instructions on
     the MVP hardware by implementing the following algorithm.

     for (size_t i = 0; i < params->length; ++i) {
       float16_t input1_val = input1[i] + input1_offset;
       float16_t input2_val = input2[i] + input2_offset;
       float16_t output_val = input1_val * input2_val;
       output[i] = output_val * output_multiplier + output_offset;
     }

     Here is a representation of the MVP program. We divide the
     input into batches that can fit within one MVP program.

     Arrays: {
       A0 = input1[batch_size]
       A1 = input2[batch_size]
       A2 = output[batch_size]
     }
     Regs: {
       R0 = input1_offset
       R1 = input2_offset
       R2 = output_offset
       R3 = output_multiplier
     }
     Loop0: cnt=batch_size {
       R4 = input1[A0.Dim2++]
       R4 = R4 + R0
       R5 = input2[A1.Dim2++]
       R5 = R5 + R1
       R6 = R4 * R5
       R6 = R6 * R3 + R2
       output[A2.Dim2++] = R6 // Store output
     }

   */
  // *INDENT-ON*

  sli_mvp_prog_set_reg_f32c(prog, SLI_MVP_R0, params->input1_offset, params->input1_offset);
  sli_mvp_prog_set_reg_f32c(prog, SLI_MVP_R1, params->input2_offset, params->input2_offset);
  sli_mvp_prog_set_reg_s32c(prog, SLI_MVP_R2, params->output_offset, params->output_offset);
  sli_mvp_prog_set_reg_f32c(prog, SLI_MVP_R3, params->output_multiplier, params->output_multiplier);

  //  R4 = input1[A0.Dim2++]
  //  R4 = R4 + R0
  sli_mvp_prog_set_instr(prog, SLI_MVP_INSTR(0),
                         SLI_MVP_OP(ADDC),
                         SLI_MVP_ALU_X(SLI_MVP_R4)
                         | SLI_MVP_ALU_A(SLI_MVP_R0)
                         | SLI_MVP_ALU_Z(SLI_MVP_R4),
                         SLI_MVP_LOAD(0, SLI_MVP_R4, SLI_MVP_ARRAY(0), SLI_MVP_INCRDIM_COL),
                         0, 0);

  //  R5 = input2[A1.Dim2++]
  //  R5 = R5 + R1
  sli_mvp_prog_set_instr(prog, SLI_MVP_INSTR(1),
                         SLI_MVP_OP(ADDC),
                         SLI_MVP_ALU_X(SLI_MVP_R5)
                         | SLI_MVP_ALU_A(SLI_MVP_R1)
                         | SLI_MVP_ALU_Z(SLI_MVP_R5),
                         SLI_MVP_LOAD(0, SLI_MVP_R5, SLI_MVP_ARRAY(1), SLI_MVP_INCRDIM_COL),
                         0, 0);

  //  R6 = R4 * R5
  sli_mvp_prog_set_instr(prog, SLI_MVP_INSTR(2),
                         SLI_MVP_OP(MULR2A),
                         SLI_MVP_ALU_X(SLI_MVP_R4)
                         | SLI_MVP_ALU_Y(SLI_MVP_R5)
                         | SLI_MVP_ALU_Z(SLI_MVP_R6),
                         0, 0, 0);

  // R6 = R6 * R3 + R2
  // output[A2.Dim2++] = R6
  sli_mvp_prog_set_instr(prog, SLI_MVP_INSTR(3),
                         SLI_MVP_OP(MACR2A),
                         SLI_MVP_ALU_X(SLI_MVP_R6)
                         | SLI_MVP_ALU_Y(SLI_MVP_R3)
                         | SLI_MVP_ALU_A(SLI_MVP_R2)
                         | SLI_MVP_ALU_Z(SLI_MVP_R6),
                         0,
                         SLI_MVP_STORE(SLI_MVP_R6, SLI_MVP_ARRAY(2), SLI_MVP_INCRDIM_COL),
                         SLI_MVP_ENDPROG);

  while (remaining >= 2) {
    // Process batch sizes of max 1024, this means 2048 actual values
    // since we operate on 2 elements on each loop iteration.
    int num_elements = SL_MIN(2048, remaining);
    int batch_size = num_elements / 2;
    num_elements = batch_size * 2;

    // Configure the input and output arrays
    sli_mvp_prog_set_vector(prog, SLI_MVP_ARRAY(0), (int8_t *)input1_data, SLI_MVP_DATATYPE_COMPLEX_INT8, batch_size);
    sli_mvp_prog_set_vector(prog, SLI_MVP_ARRAY(1), (int8_t *)input2_data, SLI_MVP_DATATYPE_COMPLEX_INT8, batch_size);
    sli_mvp_prog_set_vector(prog, SLI_MVP_ARRAY(2), output_data, SLI_MVP_DATATYPE_COMPLEX_INT8, batch_size);

    // Loop 0 is iterating over elements
    sli_mvp_prog_set_loop(prog, SLI_MVP_LOOP(0),
                          batch_size,
                          SLI_MVP_INSTR(0),
                          SLI_MVP_INSTR(3),
                          0, 0);

    if ((status = sli_mvp_prog_execute(prog, true)) != SL_STATUS_OK) {
      return status;
    }

    input1_data += num_elements;
    input2_data += num_elements;
    output_data += num_elements;
    remaining -= num_elements;
  }

  // When length is an odd number we will get 1 element left
  if (remaining == 1) {
    int input1 = *input1_data + params->input1_offset;
    int input2 = *input2_data + params->input2_offset;
    float16_t prod = input1 * input2;
    prod = prod * params->output_multiplier + params->output_offset;
    prod = round(prod);
    if (prod > 127.0f) {
      *output_data = 127;
    } else if (prod < -128.0f) {
      *output_data = -128;
    } else {
      *output_data = (int8_t) prod;
    }
  }

  return sl_math_mvp_clamp_i8(params->output, params->length, params->activation_min, params->activation_max);
}

bool sli_mvp_ml_mul_s8_is_supported(const sli_mvp_ml_mul_s8_params_t *params)
{
  if (!params) {
    return false;
  } else {
    return true; // everything is supported
  }
}

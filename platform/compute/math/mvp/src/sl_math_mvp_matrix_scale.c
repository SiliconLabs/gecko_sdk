/***************************************************************************//**
 * @file
 * @brief MVP Math Mul functions.
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

sl_status_t sl_math_mvp_matrix_scale_f16(const sl_math_matrix_f16_t *input, float16_t scale, sl_math_matrix_f16_t *output)
{
  if (input->num_cols != output->num_cols || input->num_rows != output->num_rows) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  return sl_math_mvp_vector_scale_f16(input->data, scale, output->data, input->num_rows * input->num_cols);
}

/***************************************************************************//**
 * @file
 * @brief MVP Math utility functions.
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
#include "sl_math_mvp.h"
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#if defined(SL_CATALOG_STATUS_STRING_PRESENT)
#include "sl_status_string_config.h"
#endif


void sl_math_mvp_clear_errors(void)
{
  sli_mvp_clear_error_flags(SLI_MVP_NUMERIC_EXCEPTION_FLAG_MASK | SLI_MVP_FAULT_FLAG);
}

sl_status_t sl_math_mvp_get_error(sl_status_t *error_code, char *error_message, uint32_t buffer_length)
{
  if (!error_code) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  uint32_t flag;
  uint32_t flags = sli_mvp_get_error_flags();

  if (flags & SLI_MVP_FAULT_FLAG) {
    *error_code = SL_STATUS_COMPUTE_MATH_FAULT;
    flag = SLI_MVP_FAULT_FLAG;
  } else if (flags & (MVP_IF_ALUNAN | MVP_IF_STORECONVERTNAN)) {
    *error_code = SL_STATUS_COMPUTE_MATH_NAN;
    flag = MVP_IF_ALUNAN | MVP_IF_STORECONVERTNAN;
  } else if (flags & MVP_IF_STORECONVERTINF) {
    *error_code = SL_STATUS_COMPUTE_MATH_INFINITY;
    flag = MVP_IF_STORECONVERTINF;
  } else if (flags & (MVP_IF_ALUOF | MVP_IF_STORECONVERTOF)) {
    *error_code = SL_STATUS_COMPUTE_MATH_OVERFLOW;
    flag = MVP_IF_ALUOF | MVP_IF_STORECONVERTOF;
  } else if (flags & (MVP_IF_ALUUF | MVP_IF_STORECONVERTUF)) {
    *error_code = SL_STATUS_COMPUTE_MATH_UNDERFLOW;
    flag = MVP_IF_ALUUF | MVP_IF_STORECONVERTUF;

  } else {
    return SL_STATUS_NOT_FOUND;
  }

  sli_mvp_clear_error_flags(flag);

#if defined(SL_CATALOG_STATUS_STRING_PRESENT) && (SL_STATUS_STRING_ENABLE_COMPUTE == 1)  
  if (error_message != NULL) {
    sl_status_get_string_n(*error_code, error_message, buffer_length);
  }
#else
  if ((error_message != NULL) && (buffer_length > 0)) {
    error_message[0] = '\0';
  }
#endif

  return SL_STATUS_OK;
}

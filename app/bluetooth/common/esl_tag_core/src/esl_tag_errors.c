/***************************************************************************//**
 * @file
 * @brief ESL Tag error report related functions.
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
#include "esl_tag_log.h"
#include "esl_tag_core.h"
#include "esl_tag_errors.h"

/// ESL Tag last error code internal store location
static esl_error_t last_error = ESL_ERROR_VENDOR_NOERROR;

esl_error_t esl_core_get_last_error(void)
{
  esl_error_t error = last_error;
  last_error = ESL_ERROR_VENDOR_NOERROR;

  return error;
}

void esl_core_set_last_error(esl_error_t error_code)
{
  // do not override any error not yet processed
  if (error_code == ESL_ERROR_VENDOR_NOERROR
      || last_error == ESL_ERROR_VENDOR_NOERROR) {
    last_error = error_code;
  } else {
    sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                  ESL_LOG_LEVEL_WARNING,
                  "Last error already set: 0x%02x, skipping 0x%02x",
                  last_error,
                  error_code);
  }
}

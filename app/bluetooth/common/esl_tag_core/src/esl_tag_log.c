/***************************************************************************//**
 * @file
 * @brief ESL Tag core logging weak implementation for keeping the code size low
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_common.h"
#include "esl_tag_log.h"

SL_WEAK void sli_bt_esl_logger(uint8_t    component,
                               uint8_t    level,
                               const char *fmt,
                               ...)
{
  (void)component;
  (void)level;
  (void)fmt;
}

SL_WEAK void sli_bt_esl_log_hex_dump(uint8_t component,
                                     uint8_t level,
                                     void    *p_data,
                                     uint8_t len)
{
  (void)component;
  (void)level;
  (void)p_data;
  (void)len;
}

SL_WEAK void sli_bt_esl_assert_func(const char *func,
                                    const char *file,
                                    const char *expr,
                                    int        line)
{
  (void)func;
  (void)file;
  (void)expr;
  (void)line;
  while (1) ; // Halt
}

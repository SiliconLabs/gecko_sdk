/***************************************************************************//**
 * @file
 * @brief ESL Tag core WEAK implementations of abstract image functionalities.
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
#include <stddef.h>
#include "em_common.h"
#include "esl_tag_core.h"
#include "esl_tag_image_core.h"

SL_WEAK void esl_image_init(void)
{
}

SL_WEAK void esl_image_characteristic_update(void)
{
}

SL_WEAK sl_status_t esl_image_get_data(uint8_t image_index, uint16_t* offset,
                                       uint16_t buf_size, uint8_t *target_buf)
{
  (void)image_index;
  (void)buf_size;
  (void)offset;
  (void)target_buf;

  esl_core_set_last_error(ESL_ERROR_IMAGE_NOT_AVAILABLE);

  return SL_STATUS_NOT_AVAILABLE;
}

SL_WEAK uint8_t esl_image_get_count(void)
{
  return 0;
}

SL_WEAK void esl_image_reset_storage(void)
{
}

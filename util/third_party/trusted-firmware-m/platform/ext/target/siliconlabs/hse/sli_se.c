/***************************************************************************//**
 * @file
 * @brief Silicon Labs Random Number Generator Implementation.
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

#include "sl_se_manager.h"
#include "sl_se_manager_entropy.h"
#include "tfm_hal_defs.h"
#include "tfm_hal_platform.h"

int32_t tfm_hal_random_init(void)
{
  return TFM_HAL_SUCCESS;
}

int32_t tfm_hal_random_generate(uint8_t *rand, size_t size)
{
  sl_status_t ret;
  sl_se_command_context_t cmd_ctx;

  // Initialize the SE manager.
  ret = sl_se_init();
  if (ret != SL_STATUS_OK) {
    return TFM_HAL_ERROR_GENERIC;
  }

  // Initialize command context
  ret = sl_se_init_command_context(&cmd_ctx);
  if (ret != SL_STATUS_OK) {
    return TFM_HAL_ERROR_GENERIC;
  }

  // Get entropy
  ret = sl_se_get_random(&cmd_ctx, rand, size);

  if (ret == SL_STATUS_OK) {
    return TFM_HAL_SUCCESS;
  }

  return TFM_HAL_ERROR_GENERIC;
}

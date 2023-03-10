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

#include "em_device.h"
#include "sx_trng.h"
#include "sx_primitives.h"
#include "sx_errors.h"
#include "cryptolib_types.h"

#include "tfm_hal_platform.h"
#include "tfm_hal_defs.h"

#include "cryptoacc_management.h"

int32_t tfm_hal_random_init(void)
{
  psa_status_t status;
  int32_t ret = TFM_HAL_ERROR_GENERIC;
  status = cryptoacc_trng_initialize();
  if (status == PSA_SUCCESS) {
    ret = TFM_HAL_SUCCESS;
  }
  return ret;
}

int32_t tfm_hal_random_generate(uint8_t *rand, size_t size)
{
  // Enable cryptoacc accelerator
  CMU->CLKEN1 |= CMU_CLKEN1_CRYPTOACC;
  CMU->CRYPTOACCCLKCTRL |= CMU_CRYPTOACCCLKCTRL_PKEN;
  CMU->CRYPTOACCCLKCTRL |= CMU_CRYPTOACCCLKCTRL_AESEN;

  sx_trng_get_rand_blk(block_t_convert(rand, size));

  // Disable cryptoacc accelerator
  CMU->CLKEN1 = (CMU->CLKEN1 & ~CMU_CLKEN1_CRYPTOACC);
  CMU->CRYPTOACCCLKCTRL = (CMU->CRYPTOACCCLKCTRL & ~CMU_CRYPTOACCCLKCTRL_PKEN);
  CMU->CRYPTOACCCLKCTRL = (CMU->CRYPTOACCCLKCTRL & ~CMU_CRYPTOACCCLKCTRL_AESEN);

  return TFM_HAL_SUCCESS;
}

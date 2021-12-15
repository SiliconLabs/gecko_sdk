/***************************************************************************//**
 * @file
 * @brief Silicon Labs CRYPTOACC device management interface.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "cryptoacc_management.h"

#if defined(CRYPTOACC_PRESENT)

#include "sx_trng.h"
#include "ba431_config.h"
#include "sx_errors.h"
#include "cryptolib_def.h"
#include "sli_se_manager_internal.h"
#include "mbedtls/threading.h"

#define DO_TRNG_COND_TEST  (1)

/* Get ownership of an available CRYPTOACC device */
psa_status_t cryptoacc_management_acquire(void)
{
#if defined(MBEDTLS_THREADING_C)
  if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // Take SE lock - wait/block if taken by another thread.
  sl_status_t ret = sli_se_lock_acquire();

  if (ret != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
#endif

  CMU->CLKEN1 |= CMU_CLKEN1_CRYPTOACC;
  CMU->CRYPTOACCCLKCTRL |= CMU_CRYPTOACCCLKCTRL_PKEN;
  CMU->CRYPTOACCCLKCTRL |= CMU_CRYPTOACCCLKCTRL_AESEN;

  return PSA_SUCCESS;
}

/* Release ownership of an available CRYPTOACC device */
psa_status_t cryptoacc_management_release(void)
{
  CMU->CLKEN1 = (CMU->CLKEN1 & ~CMU_CLKEN1_CRYPTOACC);
  CMU->CRYPTOACCCLKCTRL = (CMU->CRYPTOACCCLKCTRL & ~CMU_CRYPTOACCCLKCTRL_PKEN);
  CMU->CRYPTOACCCLKCTRL = (CMU->CRYPTOACCCLKCTRL & ~CMU_CRYPTOACCCLKCTRL_AESEN);

#if defined(MBEDTLS_THREADING_C)
  if (sli_se_lock_release() != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
#endif

  return PSA_SUCCESS;
}

psa_status_t cryptoacc_trng_initialize(void)
{
  psa_status_t status = cryptoacc_management_acquire();
  if (status != 0) {
    return status;
  }
  if ((ba431_read_controlreg() & BA431_CTRL_NDRNG_ENABLE) == 0u) {
    status = sx_trng_init(DO_TRNG_COND_TEST);
    if (status != CRYPTOLIB_SUCCESS) {
      cryptoacc_management_release(); // Ignore return value. Should end up with
                                      // HARDWARE_FAILURE regardless
      return PSA_ERROR_HARDWARE_FAILURE;
    }
  }
  return cryptoacc_management_release();
}

#endif /* CRYPTOACC_PRESENT */

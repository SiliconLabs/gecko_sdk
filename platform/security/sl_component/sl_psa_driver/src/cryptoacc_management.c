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

#include "sli_psa_driver_features.h"

#if defined(SLI_MBEDTLS_DEVICE_VSE)

#include "psa/crypto.h"

#include "sli_se_manager_internal.h"

#include "sli_cryptoacc_driver_trng.h"

#include "sx_aes.h"
#include "ba414ep_config.h"

//------------------------------------------------------------------------------
// RTOS Synchronization and Clocking Functions

// Get ownership of an available CRYPTOACC device.
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

  CMU->CLKEN1_SET = CMU_CLKEN1_CRYPTOACC;
  CMU->CRYPTOACCCLKCTRL_SET = (CMU_CRYPTOACCCLKCTRL_PKEN
                               | CMU_CRYPTOACCCLKCTRL_AESEN);

  return PSA_SUCCESS;
}

// Release ownership of a reserved CRYPTOACC device.
psa_status_t cryptoacc_management_release(void)
{
  CMU->CLKEN1_CLR = CMU_CLKEN1_CRYPTOACC;
  CMU->CRYPTOACCCLKCTRL_CLR = (CMU_CRYPTOACCCLKCTRL_PKEN
                               | CMU_CRYPTOACCCLKCTRL_AESEN);

  #if defined(MBEDTLS_THREADING_C)
  if (sli_se_lock_release() != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  #endif

  return PSA_SUCCESS;
}

//------------------------------------------------------------------------------
// Countermeasure Initialization Functions

#if defined(SLI_MBEDTLS_DEVICE_VSE_V2)

psa_status_t cryptoacc_initialize_countermeasures(void)
{
  // Set to true when CM has been initialized
  static bool cm_inited = false;

  // Note on the error handling: we want to try and set up the countermeasures
  // even if some of the steps fail. Hence, the first error code is stored and
  // returned in the end if something goes wrong.
  psa_status_t final_status = PSA_SUCCESS;
  if (!cm_inited) {
    // Set up the PK engine with a TRNG wrapper function to use for randomness
    // generation. This will be used for future ECC operations as well, not only
    // during the lifetime of this function.
    ba414ep_set_rng(sli_cryptoacc_trng_wrapper);

    // Seed the AES engine with a random mask. The highest bit must be set due
    // to hardware requirements.
    uint32_t mask = 0;
    psa_status_t temp_status = sli_cryptoacc_trng_get_random((uint8_t *)&mask,
                                                             sizeof(mask));
    if (temp_status != PSA_SUCCESS) {
      final_status = temp_status;
    }
    mask |= (1U << 31);

    temp_status = cryptoacc_management_acquire();
    if (temp_status != PSA_SUCCESS) {
      final_status = temp_status;
    }
    sx_aes_load_mask(mask);
    temp_status = cryptoacc_management_release();
    if ((temp_status != PSA_SUCCESS) && (final_status == PSA_SUCCESS)) {
      final_status = temp_status;
    }

    // Only track that init was successful if no error codes popped up.
    if (final_status == PSA_SUCCESS) {
      cm_inited = true;
    }
  }

  return final_status;
}

#endif // SLI_MBEDTLS_DEVICE_VSE_V2

#endif // SLI_MBEDTLS_DEVICE_VSE

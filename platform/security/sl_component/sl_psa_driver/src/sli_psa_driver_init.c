/***************************************************************************//**
 * @file
 * @brief PSA Driver initialization interface.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "psa/crypto.h"

#if defined(SLI_MBEDTLS_DEVICE_HSE)
  #include "sli_se_transparent_functions.h"
  #include "sl_se_manager.h"
  #include "sli_se_opaque_functions.h"
#endif // SLI_MBEDTLS_DEVICE_HSE

#if defined(SLI_MBEDTLS_DEVICE_VSE)
  #include "sli_cryptoacc_transparent_functions.h"
  #include "cryptoacc_management.h"
#endif // SLI_MBEDTLS_DEVICE_VSE

#if defined(SLI_MBEDTLS_DEVICE_S1)
  #include "sli_crypto_transparent_functions.h"
#endif // SLI_MBEDTLS_DEVICE_S1

// -----------------------------------------------------------------------------
// Driver entry points

#if defined(SLI_MBEDTLS_DEVICE_HSE)

psa_status_t sli_se_transparent_driver_init(void)
{
  sl_status_t sl_status = sl_se_init();
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_se_transparent_driver_deinit(void)
{
  sl_status_t sl_status = sl_se_deinit();
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return PSA_SUCCESS;
}

#if defined(SLI_PSA_DRIVER_FEATURE_OPAQUE_KEYS)

psa_status_t sli_se_opaque_driver_init(void)
{
  sl_status_t sl_status = sl_se_init();
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_se_opaque_driver_deinit(void)
{
  sl_status_t sl_status = sl_se_deinit();
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return PSA_SUCCESS;
}

#endif // SLI_PSA_DRIVER_FEATURE_OPAQUE_KEYS

#elif defined(SLI_MBEDTLS_DEVICE_VSE)

psa_status_t sli_cryptoacc_transparent_driver_init(void)
{
  // Consider moving the clock init and etc. here, which is performed by the
  // management functions.

  #if defined(SLI_MBEDTLS_DEVICE_VSE_V2)
  return cryptoacc_initialize_countermeasures();
  #else
  return PSA_SUCCESS;
  #endif
}

psa_status_t sli_cryptoacc_transparent_driver_deinit(void)
{
  return PSA_SUCCESS;
}

#elif defined(SLI_MBEDTLS_DEVICE_S1)

psa_status_t sli_crypto_transparent_driver_init(void)
{
  // Leave this function empty for now. Consider moving the clock init and etc.
  // here, which is performed by the management functions.
  return PSA_SUCCESS;
}

psa_status_t sli_crypto_transparent_driver_deinit(void)
{
  return PSA_SUCCESS;
}

#endif

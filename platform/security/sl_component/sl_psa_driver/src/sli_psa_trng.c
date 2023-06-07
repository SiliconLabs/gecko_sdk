/***************************************************************************//**
 * @file
 * @brief Default PSA TRNG hook for Silicon Labs devices.
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

#if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG) || defined(MBEDTLS_ENTROPY_HARDWARE_ALT)

#include "psa/crypto.h"
#include "psa/crypto_extra.h"
#include "psa/crypto_platform.h"

#if defined(SLI_MBEDTLS_DEVICE_HSE)
  #include "sl_se_manager.h"
  #include "sl_se_manager_entropy.h"
#elif defined(SLI_MBEDTLS_DEVICE_VSE)
  #include "sx_trng.h"
  #include "cryptolib_types.h"
  #include "cryptoacc_management.h"
#elif defined(SLI_MBEDTLS_DEVICE_S1) && defined(SLI_PSA_DRIVER_FEATURE_TRNG)
  #include "sli_crypto_trng_driver.h"
#endif

// -----------------------------------------------------------------------------
// Typedefs

#if !defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
typedef void mbedtls_psa_external_random_context_t;
#endif

// -----------------------------------------------------------------------------
// Static functions

#if defined(SLI_MBEDTLS_DEVICE_HSE)

static psa_status_t se_get_random(unsigned char *output,
                                  size_t len,
                                  size_t *out_len)
{
  sl_status_t ret;
  sl_se_command_context_t cmd_ctx;

  // Initialize the SE manager.
  ret = sl_se_init();
  if (ret != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // Initialize command context
  ret = sl_se_init_command_context(&cmd_ctx);
  if (ret != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // Get entropy
  ret = sl_se_get_random(&cmd_ctx, output, len);

  if (ret == SL_STATUS_OK) {
    *out_len = len;
    return PSA_SUCCESS;
  }

  *out_len = 0;
  return PSA_ERROR_HARDWARE_FAILURE;
}

#elif defined(SLI_MBEDTLS_DEVICE_VSE)

static psa_status_t cryptoacc_get_random(unsigned char *output,
                                         size_t len,
                                         size_t *out_len)
{
  psa_status_t trng_status = cryptoacc_trng_initialize();
  if (trng_status != PSA_SUCCESS) {
    return trng_status;
  }

  if (len > 0) {
    trng_status = cryptoacc_management_acquire();
    if (trng_status != PSA_SUCCESS) {
      return trng_status;
    }
    block_t data_out = block_t_convert(output, len);;
    sx_trng_get_rand_blk(data_out);
    trng_status = cryptoacc_management_release();
  }

  if (trng_status == PSA_SUCCESS) {
    *out_len = len;
  } else {
    *out_len = 0;
  }

  return trng_status;
}

#endif // SLI_MBEDTLS_DEVICE_HSE / SLI_MBEDTLS_DEVICE_VSE

// -----------------------------------------------------------------------------
// Global entry points

psa_status_t mbedtls_psa_external_get_random(
  mbedtls_psa_external_random_context_t *context,
  uint8_t *output,
  size_t output_size,
  size_t *output_length)
{
  (void)context;

  #if defined(SLI_PSA_DRIVER_FEATURE_TRNG)

  psa_status_t entropy_status = PSA_ERROR_CORRUPTION_DETECTED;
  size_t entropy_max_retries = 5;
  *output_length = 0;

  // Implement chunking support here, as the PSA core doesn't implement it (yet).

  while (entropy_max_retries > 0 && entropy_status != PSA_SUCCESS) {
    size_t offset = *output_length;

    #if defined(SLI_MBEDTLS_DEVICE_HSE)
    entropy_status = se_get_random(&output[offset],
                                   output_size - offset,
                                   output_length);
    #elif defined(SLI_MBEDTLS_DEVICE_VSE)
    entropy_status = cryptoacc_get_random(&output[offset],
                                          output_size - offset,
                                          output_length);
    #elif defined(SLI_MBEDTLS_DEVICE_S1) && defined(SLI_PSA_DRIVER_FEATURE_TRNG)
    entropy_status = sli_crypto_trng_get_random(&output[offset],
                                                output_size - offset,
                                                output_length);
    #endif

    *output_length += offset;

    if (*output_length >= output_size) {
      entropy_status = PSA_SUCCESS;
    }

    // Consume a retry before going through another loop
    entropy_max_retries--;
  }

  return entropy_status;

  #else // SLI_PSA_DRIVER_FEATURE_TRNG

  (void) output;
  (void) output_size;
  (void) output_length;

  return PSA_ERROR_HARDWARE_FAILURE;

  #endif // SLI_PSA_DRIVER_FEATURE_TRNG
}

#endif // MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG || MBEDTLS_ENTROPY_HARDWARE_ALT

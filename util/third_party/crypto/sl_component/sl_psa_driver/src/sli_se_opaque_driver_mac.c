/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Opaque Driver Mac functions.
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

#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)
#include "psa/crypto_platform.h"

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) \
  || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)

#include "psa/crypto.h"
#include "sli_se_driver_key_management.h"
#include "sli_se_opaque_types.h"
#include "sli_se_opaque_functions.h"
#include "sli_se_manager_internal.h"
#include "sli_psa_driver_common.h"

#include <string.h>

psa_status_t sli_se_opaque_mac_compute(const psa_key_attributes_t *attributes,
                                       const uint8_t *key_buffer,
                                       size_t key_buffer_size,
                                       psa_algorithm_t alg,
                                       const uint8_t *input,
                                       size_t input_length,
                                       uint8_t *mac,
                                       size_t mac_size,
                                       size_t *mac_length)
{
  if (key_buffer == NULL
      || attributes == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Ephemeral contexts
  sl_se_key_descriptor_t key_desc = { 0 };
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  return sli_se_driver_mac_compute(&key_desc,
                                   alg,
                                   input,
                                   input_length,
                                   mac,
                                   mac_size,
                                   mac_length);
}

psa_status_t sli_se_opaque_mac_verify(const psa_key_attributes_t *attributes,
                                      const uint8_t *key_buffer,
                                      size_t key_buffer_size,
                                      psa_algorithm_t alg,
                                      const uint8_t *input,
                                      size_t input_length,
                                      const uint8_t *mac,
                                      size_t mac_length)
{
  // There's no point in providing this functionality, since we'd do the same as the PSA core
  // either way: compute through mac_compute, and constant-time compare on the provided vs
  // calculated mac.
  (void)attributes;
  (void)key_buffer;
  (void)key_buffer_size;
  (void)alg;
  (void)input;
  (void)input_length;
  (void)mac;
  (void)mac_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_se_opaque_mac_sign_setup(sli_se_opaque_mac_operation_t *operation,
                                          const psa_key_attributes_t *attributes,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg)
{
  if (operation == NULL
      || attributes == NULL
      || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_status_t psa_status;

  // start by resetting context
  memset(operation, 0, sizeof(*operation));

  // Add support for one-shot HMAC through the multipart interface
  #if defined(PSA_WANT_ALG_HMAC)
  if (PSA_ALG_IS_HMAC(alg)) {
    // SEMAILBOX does not support multipart HMAC. Construct it from hashing instead.
    // Check key type and output size
    if (psa_get_key_type(attributes) != PSA_KEY_TYPE_HMAC) {
      // For HMAC, key type is strictly enforced
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    size_t output_size = 0;
    sl_se_hash_type_t hash = sli_se_hash_type_from_psa_hmac_alg(alg, &output_size);

    if (hash == SL_SE_HASH_NONE) {
      return PSA_ERROR_NOT_SUPPORTED;
    }

    if (output_size > sizeof(operation->operation.ctx.hmac.hmac_result)) {
      return PSA_ERROR_NOT_SUPPORTED;
    }

    operation->operation.alg = alg;
    psa_status = PSA_SUCCESS;
  } else
  #endif
  {
    psa_status = sli_se_driver_mac_sign_setup(&(operation->operation),
                                              attributes,
                                              alg);
  }
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  psa_status = sli_se_key_desc_from_input(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          &(operation->key_desc));
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  size_t padding = 0;
  operation->key_len = psa_get_key_bits(attributes) / 8;
  #if defined(SLI_SE_KEY_PADDING_REQUIRED)
  padding = sli_se_get_padding(operation->key_len);
  #endif

  #if defined(PSA_WANT_ALG_HMAC)
  if (PSA_ALG_IS_HMAC(alg)) {
    if (operation->key_len < sizeof(uint32_t) || (operation->key_len + padding) > sizeof(operation->key) - SLI_SE_WRAPPED_KEY_OVERHEAD) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  } else
  #endif
  {
    switch (operation->key_len) {
      case 16: // Fallthrough
      case 24: // Fallthrough
      case 32:
        break;
      default:
        return PSA_ERROR_INVALID_ARGUMENT;
    }
  }

  if (operation->key_desc.storage.location.buffer.size < (SLI_SE_WRAPPED_KEY_OVERHEAD + operation->key_len + padding)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  memcpy(operation->key,
         operation->key_desc.storage.location.buffer.pointer,
         SLI_SE_WRAPPED_KEY_OVERHEAD + operation->key_len + padding);

  // Point key_descriptor at internal copy of key
  operation->key_desc.storage.location.buffer.pointer = operation->key;

  return PSA_SUCCESS;
}

psa_status_t sli_se_opaque_mac_verify_setup(sli_se_opaque_mac_operation_t *operation,
                                            const psa_key_attributes_t *attributes,
                                            const uint8_t *key_buffer,
                                            size_t key_buffer_size,
                                            psa_algorithm_t alg)
{
  // Since the PSA Crypto core exposes the verify functionality of the drivers without
  // actually implementing the fallback to 'sign' when the driver doesn't support verify,
  // we need to do this ourselves for the time being.
  return sli_se_opaque_mac_sign_setup(operation,
                                      attributes,
                                      key_buffer,
                                      key_buffer_size,
                                      alg);
}

psa_status_t sli_se_opaque_mac_update(sli_se_opaque_mac_operation_t *operation,
                                      const uint8_t *input,
                                      size_t input_length)
{
  if (operation == NULL
      || (input == NULL && input_length > 0)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  #if defined(PSA_WANT_ALG_HMAC)
  if (PSA_ALG_IS_HMAC(operation->operation.alg)) {
    if ( operation->operation.ctx.hmac.hmac_len > 0 ) {
      return PSA_ERROR_BAD_STATE;
    }

    return sli_se_driver_mac_compute(&(operation->key_desc),
                                     operation->operation.alg,
                                     input,
                                     input_length,
                                     operation->operation.ctx.hmac.hmac_result,
                                     sizeof(operation->operation.ctx.hmac.hmac_result),
                                     &operation->operation.ctx.hmac.hmac_len);
  }
  #endif

  return sli_se_driver_mac_update(&(operation->operation),
                                  &(operation->key_desc),
                                  input,
                                  input_length);
}

psa_status_t sli_se_opaque_mac_sign_finish(sli_se_opaque_mac_operation_t *operation,
                                           uint8_t *mac,
                                           size_t mac_size,
                                           size_t *mac_length)
{
  if (operation == NULL
      || mac == NULL
      || mac_size == 0
      || mac_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  #if defined(PSA_WANT_ALG_HMAC)
  if (PSA_ALG_IS_HMAC(operation->operation.alg)) {
    if ( operation->operation.ctx.hmac.hmac_len == 0 ) {
      return PSA_ERROR_BAD_STATE;
    }

    if ( mac_size < operation->operation.ctx.hmac.hmac_len ) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(mac, operation->operation.ctx.hmac.hmac_result, operation->operation.ctx.hmac.hmac_len);
    *mac_length = operation->operation.ctx.hmac.hmac_len;
    return PSA_SUCCESS;
  }
  #endif

  return sli_se_driver_mac_sign_finish(&(operation->operation),
                                       &(operation->key_desc),
                                       mac,
                                       mac_size,
                                       mac_length);
}

psa_status_t sli_se_opaque_mac_verify_finish(sli_se_opaque_mac_operation_t *operation,
                                             const uint8_t *mac,
                                             size_t mac_length)
{
  // Since the PSA Crypto core exposes the verify functionality of the drivers without
  // actually implementing the fallback to 'sign' when the driver doesn't support verify,
  // we need to do this ourselves for the time being.
  uint8_t calculated_mac[PSA_MAC_MAX_SIZE] = { 0 };
  size_t calculated_length = PSA_MAC_MAX_SIZE;

  psa_status_t status = sli_se_opaque_mac_sign_finish(
    operation,
    calculated_mac, sizeof(calculated_mac), &calculated_length);
  if (status != PSA_SUCCESS) {
    return status;
  }

  if (mac_length > sizeof(calculated_mac)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (sli_psa_safer_memcmp(mac, calculated_mac, mac_length) != 0) {
    status = PSA_ERROR_INVALID_SIGNATURE;
  } else {
    status = PSA_SUCCESS;
  }

  memset(calculated_mac, 0, sizeof(calculated_mac));
  return status;
}

psa_status_t sli_se_opaque_mac_abort(sli_se_opaque_mac_operation_t *operation)
{
  // There's no state in hardware that we need to preserve, so zeroing out the context suffices.
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  memset(operation, 0, sizeof(*operation));
  return PSA_SUCCESS;
}

#endif // _SILICON_LABS_SECURITY_FEATURE_VAULT || MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS
#endif // defined(SEMAILBOX_PRESENT)

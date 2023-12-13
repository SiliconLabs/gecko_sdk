/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Transparent Driver Signature functions.
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

#if defined(SLI_MBEDTLS_DEVICE_VSE)

#include "sli_cryptoacc_transparent_types.h"
#include "sli_cryptoacc_transparent_functions.h"
#include "cryptoacc_management.h"
// Replace inclusion of psa/crypto_xxx.h with the new psa driver commong
// interface header file when it becomes available.
#include "psa/crypto_platform.h"
#include "psa/crypto_sizes.h"
#include "psa/crypto_struct.h"

#include "sx_ecdsa_alg.h"
#include "sx_ecc_keygen_alg.h"
#include "sx_trng.h"
#include "sx_errors.h"
#include "cryptolib_types.h"
#include <string.h>

// -----------------------------------------------------------------------------
// Driver entry points

psa_status_t sli_cryptoacc_transparent_sign_hash(
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *hash,
  size_t hash_length,
  uint8_t *signature,
  size_t signature_size,
  size_t *signature_length)
{
#if defined(SLI_PSA_DRIVER_FEATURE_ECDSA)

  // Argument check.
  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || hash == NULL
      || hash_length == 0
      || signature == NULL
      || signature_size == 0
      || signature_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check the requested algorithm is ECDSA with randomized k.
  if (!PSA_ALG_IS_RANDOMIZED_ECDSA(alg)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  psa_ecc_family_t curve_type = PSA_KEY_TYPE_ECC_GET_FAMILY(key_type);
  size_t key_bits = psa_get_key_bits(attributes);

  if (key_buffer_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (!PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
    // Not able to sign using non-ECC keys, or using public keys.
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  sx_ecc_curve_t *curve = NULL;

  switch (key_bits) {
    #if defined(SLI_PSA_DRIVER_FEATURE_P192R1)
    case 192:
      if (curve_type == PSA_ECC_FAMILY_SECP_R1) {
        curve = (sx_ecc_curve_t*)&sx_ecc_curve_p192;
      } else {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    #endif // SLI_PSA_DRIVER_FEATURE_P192R1
    #if defined(SLI_PSA_DRIVER_FEATURE_P224R1)
    case 224:
      if (curve_type == PSA_ECC_FAMILY_SECP_R1) {
        curve = (sx_ecc_curve_t*)&sx_ecc_curve_p224;
      } else {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    #endif // SLI_PSA_DRIVER_FEATURE_P224R1
    case 256:
      #if defined(SLI_PSA_DRIVER_FEATURE_P256R1)
      if (curve_type == PSA_ECC_FAMILY_SECP_R1) {
        curve = (sx_ecc_curve_t*)&sx_ecc_curve_p256;
      } else
      #endif // SLI_PSA_DRIVER_FEATURE_P256R1
      #if defined(SLI_PSA_DRIVER_FEATURE_P256K1)
      if (curve_type == PSA_ECC_FAMILY_SECP_K1) {
        curve = (sx_ecc_curve_t*)&sx_ecc_curve_p256k1;
      } else
      #endif // SLI_PSA_DRIVER_FEATURE_P256K1
      {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Check sufficient output buffer size.
  if (signature_size < PSA_ECDSA_SIGNATURE_SIZE(key_bits)) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  block_t priv = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
  block_t data_in = block_t_convert(hash, hash_length);
  block_t data_out = block_t_convert(signature, PSA_ECDSA_SIGNATURE_SIZE(key_bits));

  psa_status_t status = cryptoacc_management_acquire();
  if (status != PSA_SUCCESS) {
    return status;
  }
  struct sx_rng trng = { NULL, sx_trng_fill_blk };
  uint32_t sx_ret = ecdsa_generate_signature_digest(curve,
                                                    data_in,
                                                    priv,
                                                    data_out,
                                                    trng);
  status = cryptoacc_management_release();
  if (sx_ret != CRYPTOLIB_SUCCESS
      || status != PSA_SUCCESS) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  *signature_length = PSA_ECDSA_SIGNATURE_SIZE(key_bits);

  return PSA_SUCCESS;

#else // SLI_PSA_DRIVER_FEATURE_ECDSA

  (void) attributes;
  (void) key_buffer;
  (void) key_buffer_size;
  (void) alg;
  (void) hash;
  (void) hash_length;
  (void) signature;
  (void) signature_size;
  (void) signature_length;

  return PSA_ERROR_NOT_SUPPORTED;

#endif // SLI_PSA_DRIVER_FEATURE_ECDSA
}

psa_status_t sli_cryptoacc_transparent_verify_hash(
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *hash,
  size_t hash_length,
  const uint8_t *signature,
  size_t signature_length)
{
#if defined(SLI_PSA_DRIVER_FEATURE_ECDSA)

  // Argument check.
  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || hash == NULL
      || hash_length == 0
      || signature == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  psa_ecc_family_t curve_type = PSA_KEY_TYPE_ECC_GET_FAMILY(key_type);
  size_t key_bits = psa_get_key_bits(attributes);

  if (!PSA_KEY_TYPE_IS_ECC(key_type)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  if (PSA_ALG_IS_RSA_PSS(alg) || PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg)) {
    // We shouldn't have a RSA-type alg for a ECC key.
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (!PSA_ALG_IS_ECDSA(alg)) {
    // We only support ECDSA.
    return PSA_ERROR_NOT_SUPPORTED;
  }

  if (key_buffer_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (signature_length == 0) {
    return PSA_ERROR_INVALID_SIGNATURE;
  }

  uint32_t curve_flags = 0;
  sx_ecc_curve_t *curve_ptr = NULL;

  switch (key_bits) {
    #if defined(SLI_PSA_DRIVER_FEATURE_P192R1)
    case 192:
      if (curve_type == PSA_ECC_FAMILY_SECP_R1) {
        curve_ptr = (sx_ecc_curve_t*)&sx_ecc_curve_p192;
        curve_flags = sx_ecc_curve_p192.pk_flags;
      } else {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    #endif // SLI_PSA_DRIVER_FEATURE_P192R1
    #if defined(SLI_PSA_DRIVER_FEATURE_P224R1)
    case 224:
      if (curve_type == PSA_ECC_FAMILY_SECP_R1) {
        curve_ptr = (sx_ecc_curve_t*)&sx_ecc_curve_p224;
        curve_flags = sx_ecc_curve_p224.pk_flags;
      } else {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    #endif // SLI_PSA_DRIVER_FEATURE_P224R1
    case 256:
      #if defined(SLI_PSA_DRIVER_FEATURE_P256R1)
      if (curve_type == PSA_ECC_FAMILY_SECP_R1) {
        curve_ptr = (sx_ecc_curve_t*)&sx_ecc_curve_p256;
        curve_flags = sx_ecc_curve_p256.pk_flags;
      } else
      #endif // SLI_PSA_DRIVER_FEATURE_P256R1
      #if defined(SLI_PSA_DRIVER_FEATURE_P256K1)
      if (curve_type == PSA_ECC_FAMILY_SECP_K1) {
        curve_ptr = (sx_ecc_curve_t*)&sx_ecc_curve_p256k1;
        curve_flags = sx_ecc_curve_p256k1.pk_flags;
      } else
      #endif // SLI_PSA_DRIVER_FEATURE_P256K1
      {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  if (signature_length != PSA_ECDSA_SIGNATURE_SIZE(key_bits)) {
    return PSA_ERROR_INVALID_SIGNATURE;
  }

  // Export public key if necessary.
  psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
  uint32_t sx_ret = CRYPTOLIB_CRYPTO_ERR;
  block_t pub = NULL_blk;
  uint8_t pub_buf[64] = { 0 };
  if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
    block_t curve = block_t_convert(curve_ptr->params.addr, 6 * PSA_BITS_TO_BYTES(key_bits));
    block_t priv = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
    pub = block_t_convert(pub_buf, PSA_ECDSA_SIGNATURE_SIZE(key_bits));

    // Perform point multiplication in order to get public key.
    status = cryptoacc_management_acquire();
    if (status != PSA_SUCCESS) {
      return status;
    }
    sx_ret = ecc_generate_public_key(curve, pub, priv, PSA_BITS_TO_BYTES(key_bits), curve_flags);
    status = cryptoacc_management_release();
    if (sx_ret != CRYPTOLIB_SUCCESS
        || status != PSA_SUCCESS) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
  } else {
    pub = block_t_convert(key_buffer + 1, PSA_ECDSA_SIGNATURE_SIZE(key_bits));
  }

  block_t digest = block_t_convert(hash, hash_length);
  block_t signature_internal = block_t_convert(signature, PSA_ECDSA_SIGNATURE_SIZE(key_bits));

  status = cryptoacc_management_acquire();
  if (status != PSA_SUCCESS) {
    return status;
  }
  sx_ret = ecdsa_verify_signature_digest(curve_ptr,
                                         digest,
                                         pub,
                                         signature_internal);
  status = cryptoacc_management_release();
  if (sx_ret == CRYPTOLIB_INVALID_SIGN_ERR) {
    return PSA_ERROR_INVALID_SIGNATURE;
  }
  if (sx_ret != CRYPTOLIB_SUCCESS || status != PSA_SUCCESS) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return PSA_SUCCESS;

#else // SLI_PSA_DRIVER_FEATURE_ECDSA

  (void) attributes;
  (void) key_buffer;
  (void) key_buffer_size;
  (void) alg;
  (void) hash;
  (void) hash_length;
  (void) signature;
  (void) signature_length;

  return PSA_ERROR_NOT_SUPPORTED;

#endif // SLI_PSA_DRIVER_FEATURE_ECDSA
}

#endif // SLI_MBEDTLS_DEVICE_VSE

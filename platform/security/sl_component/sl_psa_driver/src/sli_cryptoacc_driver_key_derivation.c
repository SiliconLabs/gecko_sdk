/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Opaque Driver Key Derivation functions.
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
#include "psa/crypto.h"
#include "sli_mbedtls_omnipresent.h"
#include "sli_cryptoacc_opaque_types.h"
#include "sli_psa_driver_common.h"
#include "cryptoacc_management.h"
#include "cryptolib_def.h"
#include "sx_errors.h"
#include "sx_aes.h"

#include <string.h>

// -----------------------------------------------------------------------------
// Defines

#if defined(SLI_PSA_DRIVER_FEATURE_PBKDF2)
#define PBKDF2_COUNTER_ENCODING_SIZE  (4u)

// -----------------------------------------------------------------------------
// Static helper functions

/// @brief
///   Converting a value to a big endian octet string.
static void uint32_to_octet_string(uint32_t value, uint8_t buffer[4])
{
  for (uint8_t i = 0; i < 4; i++) {
    buffer[i] = (uint8_t)((value >> (8 * (3 - i))) & 0xFF);
  }
}

/// @brief
///   XOR the data pointed to by the two input blocks (of len 16 B). Result is
///   stored in dk.
///
/// @note
///   This function assumes that both block_t:s point to word-aligned addresses.
static void xorbuf(block_t dk, block_t u)
{
  for (uint32_t i = 0; i < u.len; i += 4) {
    *((uint32_t*)(dk.addr + i)) =
      *((uint32_t*)(dk.addr + i)) ^ (*(uint32_t*)(u.addr + i));
  }
}

// -----------------------------------------------------------------------------
// Custom implementation of PBKDF2 using AES-CMAC-128-PRF

/// @brief
///   Perform the PBKDF2 algorithm with AES-CMAC-128-PRF.
static psa_status_t derive_key_pbkdf2_aes_cmac_128_prf(
  block_t  *password,
  block_t  *salt,
  uint32_t iterations,
  uint32_t derived_key_length,
  block_t  *derived_key)
{
  psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
  // Buffers for storing temporary/partial results of the operation.
  uint8_t temp_buf_1[AES_MAC_SIZE];
  block_t temp_blk_1 = block_t_convert(temp_buf_1, AES_MAC_SIZE);
  uint8_t temp_buf_2[AES_MAC_SIZE];
  block_t temp_blk_2 = block_t_convert(temp_buf_2, AES_MAC_SIZE);

  // Make sure that we can handle the length of the salt input.
  if (salt->len > DERIV_MAX_SALT_SIZE) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Make sure that the output key length is sufficient.
  if (derived_key->len < derived_key_length) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Buffer for appending the iteration counter to the input salt before
  // applying the PRF.
  uint8_t internal_data_buf[DERIV_MAX_SALT_SIZE + PBKDF2_COUNTER_ENCODING_SIZE]
    = { 0 };
  block_t internal_data_blk =
    block_t_convert(internal_data_buf,
                    salt->len + PBKDF2_COUNTER_ENCODING_SIZE);

  uint8_t *counter_encoding = &internal_data_buf[salt->len];

  // Read the user provided salt into our internal buffer.
  memcpy(internal_data_buf, salt->addr, salt->len);

  // It is possible that the password provided is not of the expected size for
  // AES-128. In those cases, we will have to expand the password to 16 bytes;
  // this is done as described in RFC4615.
  uint8_t internal_password_buf[AES_KEYSIZE_128] = { 0 };
  if (password->len != AES_KEYSIZE_128) {
    block_t internal_password_blk =
      block_t_convert(internal_password_buf, sizeof(internal_password_buf));
    // Acquire hardware lock and execute CMAC operation
    status = cryptoacc_management_acquire();
    if (status != PSA_SUCCESS) {
      return status;
    }
    uint32_t sx_ret = sx_aes_cmac_generate(&internal_password_blk,
                                           password,
                                           &internal_password_blk);
    status = cryptoacc_management_release();
    if (status != PSA_SUCCESS) {
      return status;
    }
    if (sx_ret != CRYPTOLIB_SUCCESS) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
    *password = internal_password_blk;
  }

  uint32_t output_key_length = 0;
  uint32_t i = 1;
  while (output_key_length < derived_key_length) {
    // Encode counter value.
    uint32_to_octet_string(i, counter_encoding);

    // First Block (U_1).
    // Acquire hardware lock and execute CMAC operation
    status = cryptoacc_management_acquire();
    if (status != PSA_SUCCESS) {
      return status;
    }
    uint32_t sx_ret = sx_aes_cmac_generate(password,
                                           &internal_data_blk,
                                           &temp_blk_1);
    status = cryptoacc_management_release();
    if (status != PSA_SUCCESS) {
      return status;
    }
    if (sx_ret != CRYPTOLIB_SUCCESS) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
    memcpy(temp_blk_2.addr, temp_blk_1.addr, AES_MAC_SIZE);

    // Remaining blocks (U_j).
    for (uint32_t j = 1; j < iterations; j++) {
      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }
      sx_ret = sx_aes_cmac_generate(password, &temp_blk_1, &temp_blk_1);
      status = cryptoacc_management_release();
      if (status != PSA_SUCCESS) {
        return status;
      }
      if (sx_ret != CRYPTOLIB_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      xorbuf(temp_blk_2, temp_blk_1);
    }

    uint32_t partial_output_length =
      (derived_key_length - output_key_length >= AES_MAC_SIZE)
      ? (AES_MAC_SIZE) : (derived_key_length - output_key_length);

    output_key_length += partial_output_length;

    memcpy(derived_key->addr, temp_blk_2.addr, partial_output_length);
    derived_key->len -= partial_output_length;
    if (!(derived_key->flags & BLOCK_S_CONST_ADDR)) {
      derived_key->addr += partial_output_length;
    }

    i += 1;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_driver_single_shot_pbkdf2(
  psa_algorithm_t alg,
  const psa_key_attributes_t *key_in_attributes,
  const uint8_t *key_in_buffer,
  size_t key_in_buffer_size,
  const uint8_t* salt,
  size_t salt_length,
  const psa_key_attributes_t *key_out_attributes,
  uint32_t iterations,
  uint8_t *key_out_buffer,
  size_t key_out_buffer_size)
{
  if (key_in_buffer == NULL
      || key_in_attributes == NULL
      || salt == NULL
      || key_out_attributes == NULL
      || key_out_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  size_t key_out_size = PSA_BITS_TO_BYTES(psa_get_key_bits(key_out_attributes));

  if (key_out_buffer_size < key_out_size) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  if (iterations == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_lifetime_t lifetime = psa_get_key_lifetime(key_in_attributes);
  psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(lifetime);
  block_t key_block = NULL_blk;

  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
    {
#if defined(SLI_PSA_DRIVER_FEATURE_ECC)
      if (PSA_KEY_TYPE_IS_ECC(psa_get_key_type(key_in_attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
      }

#endif // SLI_PSA_DRIVER_FEATURE_ECC

      key_block = block_t_convert(key_in_buffer, key_in_buffer_size);
      break;
    }

#if defined(SLI_PSA_DRIVER_FEATURE_OPAQUE_KEYS)
    case PSA_KEY_LOCATION_SL_CRYPTOACC_OPAQUE:
    {
      if (key_in_buffer_size < sizeof(sli_cryptoacc_opaque_key_context_t)) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // The only opaque key that is currently supported is the PUF key
      sli_cryptoacc_opaque_key_context_t *key_context =
        (sli_cryptoacc_opaque_key_context_t *)key_in_buffer;
      if (key_context->builtin_key_id != 0) {
        switch (key_context->builtin_key_id) {
          case SLI_CRYPTOACC_BUILTIN_KEY_PUF_SLOT:
            // Using this key block as input will make the AES engine use the PUF-
            // derived key for the operation.
            // Make sure that the attributes and so on match our expectations
            if (psa_get_key_bits(key_in_attributes) != 256) {
              return PSA_ERROR_INVALID_ARGUMENT;
            }
            key_block = AES_KEY1_256;
            break;
          default:
            return PSA_ERROR_INVALID_ARGUMENT;
        }
      } else {
        return PSA_ERROR_NOT_SUPPORTED;
      }

      break;
    }
#endif // SLI_PSA_DRIVER_FEATURE_OPAQUE_KEYS

    default:
      return PSA_ERROR_DOES_NOT_EXIST;
  }

  switch (alg) {
    case PSA_ALG_PBKDF2_AES_CMAC_PRF_128:
    {
      #define AES_CMAC_PRF_128_BLOCK_SIZE 128
      // The out key length can atmost be 128 bits long.
      if ( !key_out_size || (key_out_size > PSA_BITS_TO_BYTES(AES_CMAC_PRF_128_BLOCK_SIZE)) ) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      block_t salt_block = block_t_convert(salt, salt_length);
      block_t key_out_block = block_t_convert(key_out_buffer, key_out_buffer_size);
      return derive_key_pbkdf2_aes_cmac_128_prf(&key_block, &salt_block, iterations, key_out_size, &key_out_block);
      break;
    }
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }
  return PSA_ERROR_CORRUPTION_DETECTED;
}

#endif // defined(SLI_PSA_DRIVER_FEATURE_PBKDF2)

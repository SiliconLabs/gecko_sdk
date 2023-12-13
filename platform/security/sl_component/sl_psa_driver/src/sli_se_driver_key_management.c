/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Driver Key Management functions.
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

#if defined(SLI_MBEDTLS_DEVICE_HSE)

#include "psa/crypto.h"

#include "sli_se_opaque_types.h"
#include "sli_se_opaque_functions.h"
#include "sli_se_driver_key_management.h"
#include "sli_psa_driver_common.h"  // sli_psa_zeroize()
#include "sli_se_version_dependencies.h"

#include "sl_se_manager_key_derivation.h"
#include "sl_se_manager_internal_keys.h"
#include "sl_se_manager_util.h"
#include "sli_se_manager_internal.h"

#include <string.h>

// -----------------------------------------------------------------------------
// Static constants

#if defined(SLI_PSA_DRIVER_FEATURE_P192R1)
static const uint8_t ecc_p192_n[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0xde, 0xf8, 0x36, 0x14, 0x6b, 0xc9, 0xb1, 0xb4, 0xd2, 0x28, 0x31
};
#endif

#if defined(SLI_PSA_DRIVER_FEATURE_P224R1)
static const uint8_t ecc_p224_n[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x16, 0xa2, 0xe0, 0xb8, 0xf0, 0x3e, 0x13, 0xdd, 0x29, 0x45, 0x5c, 0x5c, 0x2a, 0x3d
};
#endif

#if defined(SLI_PSA_DRIVER_FEATURE_P256R1)
static const uint8_t ecc_p256_n[] = {
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84, 0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63, 0x25, 0x51
};
#endif

#if defined(SLI_PSA_DRIVER_FEATURE_P384R1)
static const uint8_t ecc_p384_n[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x63, 0x4d, 0x81, 0xf4, 0x37, 0x2d, 0xdf, 0x58, 0x1a, 0x0d, 0xb2, 0x48, 0xb0, 0xa7, 0x7a, 0xec, 0xec, 0x19, 0x6a, 0xcc, 0xc5, 0x29, 0x73
};
#endif

#if defined(SLI_PSA_DRIVER_FEATURE_P521R1)
static const uint8_t ecc_p521_n[] = {
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0x51, 0x86, 0x87, 0x83, 0xbf, 0x2f, 0x96, 0x6b, 0x7f, 0xcc, 0x01, 0x48, 0xf7, 0x09, 0xa5, 0xd0, 0x3b, 0xb5, 0xc9, 0xb8, 0x89, 0x9c, 0x47, 0xae, 0xbb, 0x6f, 0xb7, 0x1e, 0x91, 0x38, 0x64, 0x09
};
#endif

// -----------------------------------------------------------------------------
// Static functions

/**
 * @brief
 *   Clamp if Montgomery or Twisted Edwards private key
 *
 * @param attributes
 *   The PSA attributes struct representing a key
 * @param key_data
 *   Key data
 * @param key_bits
 *   Key size in bits
 * @returns
 *   N/A
 */
static void clamp_private_key_if_needed(const psa_key_attributes_t* attributes,
                                        uint8_t *key_data,
                                        size_t key_bits)
{
  psa_key_type_t key_type = psa_get_key_type(attributes);

  // Apply clamping
  if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)
      && ((PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) == PSA_ECC_FAMILY_MONTGOMERY))) {
    switch (key_bits) {
      #if defined(SLI_PSA_DRIVER_FEATURE_CURVE25519)
      case 255:
        key_data[0] &= 248U;
        key_data[31] &= 127U;
        key_data[31] |= 64U;
        break;
      #endif // SLI_PSA_DRIVER_FEATURE_CURVE25519

      #if defined(SLI_PSA_DRIVER_FEATURE_CURVE448)
      case 448:
        key_data[0] &= 252U;
        key_data[55] |= 128U;
        break;
      #endif // SLI_PSA_DRIVER_FEATURE_CURVE448

      default:
        (void) attributes;
        (void) key_data;
        (void) key_bits;
        break;
    }
  }
}

/**
 * @brief
 *   Validate that the key descriptor mathces the PSA attributes struct.
 *
 * @param attributes
 *   The PSA attributes struct representing a key
 * @param key_size
 *   Size of the key
 * @param key_desc
 *   The SE manager key struct representing the same key
 * @returns
 *   PSA_SUCCESS if the structures match,
 *   PSA_ERROR_INVALID_ARGUMENT otherwise
 */
static psa_status_t validate_key_desc(const psa_key_attributes_t* attributes,
                                      size_t key_size,
                                      const sl_se_key_descriptor_t *key_desc)
{
  if (key_desc == NULL || attributes == NULL || key_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  // Build a new key descriptor from attributes and check that they match
  sl_se_key_descriptor_t new_key_desc = { 0 };
  psa_status_t status =
    sli_se_key_desc_from_psa_attributes(attributes, key_size, &new_key_desc);
  if (status != PSA_SUCCESS) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (new_key_desc.type != key_desc->type
      || new_key_desc.size != key_desc->size
      || new_key_desc.flags != key_desc->flags
      || new_key_desc.password != key_desc->password
      || new_key_desc.domain != key_desc->domain) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  return PSA_SUCCESS;
}

/**
 * @brief
 *   Set the number of bytes of key buffer used for storing the key.
 *
 * @param attributes[in]
 *   The PSA attributes struct representing a key
 * @param data_size[in]
 *   Size of the data that has been stored (excluding the 0x04 byte for public
 *   keys)
 * @param key_buffer_length[out]
 *   Actually used key buffer space
 * @returns
 *   PSA_SUCCESS if key_buffer_length can be set properly,
 *   PSA_ERROR_NOT_SUPPORTED if unsupported location is encountered.
 */
static psa_status_t set_key_buffer_length(
  const psa_key_attributes_t *attributes,
  size_t data_size,
  size_t *key_buffer_length)
{
  psa_key_location_t location =
    PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
  *key_buffer_length = 0;
  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
      if (sli_se_has_format_byte(psa_get_key_type(attributes))) {
        data_size++; // Add the format byte offset
      }
      *key_buffer_length =  data_size;
      break;

      #if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      #if defined(SLI_SE_KEY_PADDING_REQUIRED)
      data_size = sli_se_word_align(data_size);
      #endif
      *key_buffer_length = sizeof(sli_se_opaque_wrapped_key_context_t)
                           + data_size;
      break;
      #endif // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS

    default:
      return PSA_ERROR_NOT_SUPPORTED;
      break;
  }

  return PSA_SUCCESS;
}

#if defined(SLI_PSA_DRIVER_FEATURE_ECC)

static psa_status_t sli_se_driver_validate_ecc_key(
  const psa_key_attributes_t *attributes,
  const uint8_t *data,
  size_t data_length,
  size_t *bits)
{
  // Argument check.
  if (attributes == NULL
      || data == NULL
      || data_length == 0
      || bits == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_status_t return_status = PSA_ERROR_CORRUPTION_DETECTED;
  psa_key_type_t key_type = psa_get_key_type(attributes);

  psa_ecc_family_t curve_type = PSA_KEY_TYPE_ECC_GET_FAMILY(key_type);

  switch (curve_type) {
    #if defined(SLI_PSA_DRIVER_FEATURE_SECPR1)
    case PSA_ECC_FAMILY_SECP_R1: {
      if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {   // Private key.
        const void *modulus_ptr = NULL;
        *bits = psa_get_key_bits(attributes);

        // Determine key bit-size
        if (*bits == 0) {
          *bits = data_length * 8;
        } else {
          if (PSA_BITS_TO_BYTES(*bits) != data_length) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
        }

        switch (*bits) {
          #if defined(SLI_PSA_DRIVER_FEATURE_P192R1)
          case 192:
            modulus_ptr = ecc_p192_n;
            break;
          #endif   // SLI_PSA_DRIVER_FEATURE_P192R1

          #if defined(SLI_PSA_DRIVER_FEATURE_P224R1)
          // Series-2-config-1 devices do not support SECP224R1.
          case 224:
            modulus_ptr = ecc_p224_n;
            break;
          #endif   // SLI_PSA_DRIVER_FEATURE_P224R1

          #if defined(SLI_PSA_DRIVER_FEATURE_P256R1)
          case 256:
            modulus_ptr = ecc_p256_n;
            break;
          #endif   // SLI_PSA_DRIVER_FEATURE_P256R1

          #if defined(SLI_PSA_DRIVER_FEATURE_P384R1)
          case 384:
            modulus_ptr = ecc_p384_n;
            break;
          #endif   // SLI_PSA_DRIVER_FEATURE_P384R1

          #if defined(SLI_PSA_DRIVER_FEATURE_P521R1)
          case 521:
            modulus_ptr = ecc_p521_n;
            break;
          case 528:
            // Maybe a 521 bit long key which has been padded to 66 bytes.
            // Make sure the key size is not actually 528
            if (psa_get_key_bits(attributes) == 528) {
              return PSA_ERROR_NOT_SUPPORTED;
            }
            // Actually a 521 bit long key which has been padded to 66 bytes.
            *bits = 521;
            modulus_ptr = ecc_p521_n;
            break;
          #endif   // SLI_PSA_DRIVER_FEATURE_P521R1

          default:
            return PSA_ERROR_NOT_SUPPORTED;
            break;
        }

        // Validate the private key.
        return_status = sli_psa_validate_ecc_weierstrass_privkey(data,
                                                                 modulus_ptr,
                                                                 data_length);
      } else if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {   // Public key.
        // Check that uncompressed representation is given.
        if (data[0] != 0x04) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        // Create ephemeral SE command context.
        sl_se_command_context_t cmd_ctx = SL_SE_COMMAND_CONTEXT_INIT;
        sl_status_t sl_status = sl_se_init_command_context(&cmd_ctx);
        if (sl_status != SL_STATUS_OK) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        #if defined(SLI_SE_VERSION_ECDH_PUBKEY_VALIDATION_UNCERTAIN)
        // SE version 1.2.2 is first version with public key validation
        // inside of the SE.
        uint32_t se_version = 0;
        sl_status = sl_se_get_se_version(&cmd_ctx, &se_version);
        if (sl_status != SL_STATUS_OK) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        if ((se_version & 0x00FFFFFFU) < SLI_SE_OLDEST_VERSION_WITH_PUBLIC_KEY_VALIDATION) {
          #if defined(MBEDTLS_ECP_C)       \
          && defined(MBEDTLS_PSA_CRYPTO_C) \
          && SL_SE_SUPPORT_FW_PRIOR_TO_1_2_2
          return_status = sli_se_driver_validate_pubkey_with_fallback(
            key_type,
            psa_get_key_bits(attributes),
            data,
            data_length);
          #else
          // No fallback code is compiled in, cannot do public key validation
          return_status = PSA_ERROR_NOT_SUPPORTED;
          #endif
          break;
        }
        #endif   // SLI_SE_VERSION_ECDH_PUBKEY_VALIDATION_UNCERTAIN

        // Temporary buffer for storing ECDH input private key,
        // possibly padded input public key, and output shared key.
        #if defined(SLI_SE_KEY_PADDING_REQUIRED)

        // If input public key requires padding, it will be stored
        // starting from the third element. By doing this, and setting
        // the first half-word equal to 1, we are guaranteed to not end up
        // with a private key that is acidentally greater than the order
        // n of the curve group (since the fields size q is greater than n).
        uint8_t tmp_key_buffer[2 + SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
        #else   // SLI_SE_KEY_PADDING_REQUIRED
        uint8_t tmp_key_buffer[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
        #endif   // SLI_SE_KEY_PADDING_REQUIRED

        // Make sure that ECDH private key is non-zero.
        tmp_key_buffer[0] = 1;

        // Input public key descriptor.
        sl_se_key_descriptor_t input_public_key_desc = {
          .storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT,
          .storage.location.buffer.pointer = (uint8_t*)data + 1,
          .storage.location.buffer.size = data_length - 1,
        };

        // Temporary private key descriptor.
        sl_se_key_descriptor_t tmp_private_key_desc = {
          .storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT,
          .storage.location.buffer.pointer = tmp_key_buffer,
          .storage.location.buffer.size = sizeof(tmp_key_buffer),
        };

        // Temporary shared key descriptor.
        sl_se_key_descriptor_t tmp_shared_key_desc = {
          .type = SL_SE_KEY_TYPE_SYMMETRIC,
          .storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT,
          .storage.location.buffer.pointer = tmp_key_buffer,
          .storage.location.buffer.size = sizeof(tmp_key_buffer),
        };

        // Determine key bit size (including padding).
        *bits = (data_length - 1) * 8 / 2;

        uint8_t padding_bytes = 0;
        switch (*bits) {
          #if defined(SLI_PSA_DRIVER_FEATURE_P192R1)
          case 192:
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P192;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P192;
            break;
          #endif   // SLI_PSA_DRIVER_FEATURE_P192R1

          case 224:
            #if defined(SLI_MBEDTLS_DEVICE_HSE_V1)
            // Series-2-config-1 devices do not support SECP224R1.
            return PSA_ERROR_NOT_SUPPORTED;
            break;
            #elif defined(SLI_PSA_DRIVER_FEATURE_P224R1)
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P224;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P224;
            break;
            #endif

            #if defined(SLI_PSA_DRIVER_FEATURE_P256R1)
          case 256:
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P256;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P256;
            break;
            #endif // SLI_PSA_DRIVER_FEATURE_P256R1

            #if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)

            #if defined(SLI_PSA_DRIVER_FEATURE_P384R1)
          case 384:
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P384;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P384;
            break;
            #endif // SLI_PSA_DRIVER_FEATURE_P384R1

            #if defined(SLI_PSA_DRIVER_FEATURE_P521R1)
          case 528:
            // Actually a 521 bit long key which has been padded to 66 bytes.
            *bits = 521;
            padding_bytes = SLI_SE_P521_PADDING_BYTES;
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P521;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P521;
            break;
            #endif // SLI_PSA_DRIVER_FEATURE_P521R1

            #else // SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH

          case 384:     // fall through
          case 528:
            return PSA_ERROR_NOT_SUPPORTED;
            break;

            #endif // SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH

          default:
            return PSA_ERROR_INVALID_ARGUMENT;
            break;
        }

        // Set missing key descriptor attributes.
        input_public_key_desc.flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY;
        tmp_private_key_desc.flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY;
        tmp_shared_key_desc.size = (PSA_BITS_TO_BYTES(*bits) + padding_bytes) * 2;

        #if defined(SLI_SE_KEY_PADDING_REQUIRED)
        // Should currently only happen for curve P521.
        if (padding_bytes > 0) {
          // Pad public key. Offset +2 in order to avoid problem with invalid private key.
          sli_se_pad_curve_point(tmp_key_buffer + 2,
                                 (uint8_t*)data + 1,
                                 PSA_BITS_TO_BYTES(*bits));
          sli_se_key_descriptor_set_plaintext(&input_public_key_desc,
                                              tmp_key_buffer + 2,
                                              sizeof(tmp_key_buffer) - 2);
        }
        #endif   // SLI_SE_KEY_PADDING_REQUIRED

        // Perform key agreement algorithm (ECDH).
        sl_status = sl_se_ecdh_compute_shared_secret(&cmd_ctx,
                                                     &tmp_private_key_desc,
                                                     &input_public_key_desc,
                                                     &tmp_shared_key_desc);

        // Zero out intermediate results.
        if (padding_bytes == 0) {
          sli_psa_zeroize(tmp_key_buffer, (PSA_BITS_TO_BYTES(*bits)) * 2);
        }
        #if defined(SLI_SE_KEY_PADDING_REQUIRED)
        else {
          sli_psa_zeroize(tmp_key_buffer,
                          2 + (PSA_BITS_TO_BYTES(*bits) + padding_bytes) * 2);
        }
        #endif   // SLI_SE_KEY_PADDING_REQUIRED

        if (sl_status != SL_STATUS_OK) {
          return PSA_ERROR_INVALID_ARGUMENT;
        } else {
          return_status = PSA_SUCCESS;
        }
      }
      break;
    }
    #endif // SLI_PSA_DRIVER_FEATURE_SECPR1

    #if defined(SLI_PSA_DRIVER_FEATURE_MONTGOMERY) || defined(SLI_PSA_DRIVER_FEATURE_EDWARDS)
    case PSA_ECC_FAMILY_MONTGOMERY: // Explicit fallthrough
    case PSA_ECC_FAMILY_TWISTED_EDWARDS:
      // Determine key bit-size
      if (*bits == 0) {
        *bits = data_length * 8;
      } else {
        if (PSA_BITS_TO_BYTES(*bits) != data_length) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }
      }
      switch (*bits) {
        #if defined(SLI_PSA_DRIVER_FEATURE_CURVE25519) || defined(SLI_PSA_DRIVER_FEATURE_EDWARDS25519)
        case 255:
          return_status = PSA_SUCCESS;
          break;
        case 256:
          // Maybe a 255 bit long key which has been padded to 32 bytes.
          // Make sure the key size is not actually 256
          if (psa_get_key_bits(attributes) == 256) {
            return PSA_ERROR_NOT_SUPPORTED;
          }
          *bits = 255;
          return_status = PSA_SUCCESS;
          break;
        #endif // SLI_PSA_DRIVER_FEATURE_CURVE25519 || SLI_PSA_DRIVER_FEATURE_EDWARDS25519

        #if defined(SLI_PSA_DRIVER_FEATURE_CURVE448)
        case 448:
          return_status = PSA_SUCCESS;
          break;
        #endif // SLI_PSA_DRIVER_FEATURE_CURVE448

        default:
          return PSA_ERROR_NOT_SUPPORTED;
          break;
      }
      break;
    #endif  // SLI_PSA_DRIVER_FEATURE_MONTGOMERY || SLI_PSA_DRIVER_FEATURE_EDWARDS

    default:
      return PSA_ERROR_NOT_SUPPORTED;
      break;
  }

  return return_status;
}

#endif // SLI_PSA_DRIVER_FEATURE_ECC

// -----------------------------------------------------------------------------
// Global helper functions

// -------------------------------------
// Generic helper functions

/**
 * @brief
 *   Build a key descriptor from a PSA attributes struct
 *
 * @param attributes
 *   The PSA attributes struct representing a key
 * @param key_size
 *    Size of the key
 * @param key_desc
 *   The SE manager key struct representing the same key
 * @returns
 *   PSA_SUCCESS on success
 *   PSA_ERROR_INVALID_ARGUMENT on invalid attributes
 */
psa_status_t sli_se_key_desc_from_psa_attributes(
  const psa_key_attributes_t *attributes,
  size_t key_size,
  sl_se_key_descriptor_t *key_desc)
{
  size_t attributes_key_size =
    PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
  if (attributes_key_size != 0) {
    // If attributes key size is nonzero, it must be equal to key_size
    if (attributes_key_size != key_size) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  }
  psa_key_type_t type = psa_get_key_type(attributes);
  psa_key_usage_t usage = psa_get_key_usage_flags(attributes);
  psa_key_lifetime_t lifetime = psa_get_key_lifetime(attributes);
  psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(lifetime);

  memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));

  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
      key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT;
      break;

      #if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      // For the time being, volatile keys directly in SE internal RAM are not
      // supported. Once they are, use the persistence info from the key
      // lifetime to switch between EXTERNAL_WRAPPED and INTERNAL_VOLATILE.
      key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_WRAPPED;
      break;
      #endif // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS

    default:
      return PSA_ERROR_DOES_NOT_EXIST;
  }

  // Dont't accept zero-length keys
  if (key_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (type == PSA_KEY_TYPE_RAW_DATA
      || type == PSA_KEY_TYPE_HMAC
      || type == PSA_KEY_TYPE_DERIVE) {
    // Set attributes
    key_desc->type = SL_SE_KEY_TYPE_SYMMETRIC;
    key_desc->size = key_size;
  } else

  #if defined(SLI_PSA_DRIVER_FEATURE_AES)
  if (type == PSA_KEY_TYPE_AES) {
    switch (key_size) {
      case 16:
        key_desc->type = SL_SE_KEY_TYPE_AES_128;
        break;
      case 24:
        key_desc->type = SL_SE_KEY_TYPE_AES_192;
        break;
      case 32:
        key_desc->type = SL_SE_KEY_TYPE_AES_256;
        break;
      default:
        // SE doesn't support off-size AES keys
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    key_desc->size = key_size;
  } else
  #endif // SLI_PSA_DRIVER_FEATURE_AES

  #if defined(SLI_PSA_DRIVER_FEATURE_CHACHA20) \
  || defined(SLI_PSA_DRIVER_FEATURE_CHACHAPOLY)
  if (type == PSA_KEY_TYPE_CHACHA20) {
    if (key_size != 0x20) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
    // Set attributes
    key_desc->type = SL_SE_KEY_TYPE_CHACHA20;
    key_desc->size = 0x20;
  } else
  #endif // SLI_PSA_DRIVER_FEATURE_CHACHA20 || SLI_PSA_DRIVER_FEATURE_CHACHAPOLY

  #if defined(SLI_PSA_DRIVER_FEATURE_ECC)
  if (PSA_KEY_TYPE_IS_ECC(type)) {
    #if defined(SLI_PSA_DRIVER_FEATURE_SECPR1)
    if (PSA_KEY_TYPE_ECC_GET_FAMILY(type) == PSA_ECC_FAMILY_SECP_R1) {
      // Find key size and set key type
      switch (key_size) {
        #if defined(SLI_PSA_DRIVER_FEATURE_P192R1)
        case 24:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P192;
          break;
        #endif     // SLI_PSA_DRIVER_FEATURE_P192R1

        #if defined(SLI_PSA_DRIVER_FEATURE_P224R1)
        // Series-2-config-1 devices do not support SECP224R1.
        case 28:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P224;
          break;
        #endif     // SLI_PSA_DRIVER_FEATURE_P224R1

        #if defined(SLI_PSA_DRIVER_FEATURE_P256R1)
        case 32:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P256;
          break;
        #endif     // SLI_PSA_DRIVER_FEATURE_P256R1

        #if defined(SLI_PSA_DRIVER_FEATURE_P384R1)
        case 48:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P384;
          break;
        #endif     // SLI_PSA_DRIVER_FEATURE_P384R1

        #if defined(SLI_PSA_DRIVER_FEATURE_P521R1)
        case 66:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P521;
          break;
        #endif     // SLI_PSA_DRIVER_FEATURE_P521R1

        default:
          return PSA_ERROR_NOT_SUPPORTED;
      }
    } else
    #endif   // SLI_PSA_DRIVER_FEATURE_SECPR1

    #if defined(SLI_PSA_DRIVER_FEATURE_MONTGOMERY)
    if (PSA_KEY_TYPE_ECC_GET_FAMILY(type) == PSA_ECC_FAMILY_MONTGOMERY) {
      // Find key size and set key type
      switch (key_size) {
        #if defined(SLI_PSA_DRIVER_FEATURE_CURVE25519)
        case 32:
          key_desc->type = SL_SE_KEY_TYPE_ECC_X25519;
          break;
        #endif     // SLI_PSA_DRIVER_FEATURE_CURVE25519

        #if defined(SLI_PSA_DRIVER_FEATURE_CURVE448)
        case 56:
          key_desc->type = SL_SE_KEY_TYPE_ECC_X448;
          break;
        #endif     // SLI_PSA_DRIVER_FEATURE_CURVE448

        default:
          return PSA_ERROR_NOT_SUPPORTED;
      }
    } else
    #endif   // SLI_PSA_DRIVER_FEATURE_MONTGOMERY

    #if defined(SLI_PSA_DRIVER_FEATURE_EDWARDS)
    if (PSA_KEY_TYPE_ECC_GET_FAMILY(type) == PSA_ECC_FAMILY_TWISTED_EDWARDS) {
      // Find key size and set key type
      switch (key_size) {
        #if defined(SLI_PSA_DRIVER_FEATURE_EDWARDS25519)
        case 32:
          key_desc->type = SL_SE_KEY_TYPE_ECC_ED25519;
          break;
        #endif     // SLI_PSA_DRIVER_FEATURE_EDWARDS25519
        default:
          return PSA_ERROR_NOT_SUPPORTED;
      }
    } else
    #endif   // SLI_PSA_DRIVER_FEATURE_EDWARDS

    {
      return PSA_ERROR_NOT_SUPPORTED;
    }

    // Set asymmetric args
    if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(type)) {
      key_desc->flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY;
    } else if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(type)) {
      key_desc->flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY;
    } else {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    // Decide whether the key will be used for signing or derivation
    bool is_signing = (usage & (PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH | PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE)) != 0;
    bool is_deriving = (usage & (PSA_KEY_USAGE_DERIVE | PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT)) != 0;

    if (is_signing && !is_deriving) {
      key_desc->flags |= SL_SE_KEY_FLAG_ASYMMMETRIC_SIGNING_ONLY;
    } else if (!is_signing && is_deriving) {
      key_desc->flags = (key_desc->flags & ~SL_SE_KEY_FLAG_ASYMMMETRIC_SIGNING_ONLY);
    } else if (is_signing && is_deriving) {
      // SE does not support a key to be used for both signing and derivation operations.
      return PSA_ERROR_NOT_SUPPORTED;
    } else {
      // ECC key is not setup for either signing or deriving. Default to not setting
      // the 'sign' flag (legacy behaviour)
      key_desc->flags = (key_desc->flags & ~SL_SE_KEY_FLAG_ASYMMMETRIC_SIGNING_ONLY);
    }
  } else
  #endif // SLI_PSA_DRIVER_FEATURE_ECC
  {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  #if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)
  // Add key restrictions. Only relevant for opaque drivers. If these properties
  // are set for transparent drivers, key generation becomes illegal, as the SE
  // does not allow writing a protected key to a plaintext buffer.
  if (location != PSA_KEY_LOCATION_LOCAL_STORAGE) {
    bool can_export = usage & PSA_KEY_USAGE_EXPORT;
    bool can_copy = usage & PSA_KEY_USAGE_COPY;

    if (can_copy) {
      // We do not support copying opaque keys (currently).
      return PSA_ERROR_NOT_SUPPORTED;
    }
    if (!can_export) {
      key_desc->flags |= SL_SE_KEY_FLAG_NON_EXPORTABLE;
    }
  }
  #else // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS
  (void)usage;
  #endif // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS

  return PSA_SUCCESS;
}

/**
 * @brief
 *   Get the key descriptor from the key buffer and attributes
 */
psa_status_t sli_se_key_desc_from_input(const psa_key_attributes_t* attributes,
                                        const uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        sl_se_key_descriptor_t *key_desc)
{
  psa_key_lifetime_t lifetime = psa_get_key_lifetime(attributes);
  psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(lifetime);
  uint32_t key_size = 0; // Retrieved in different ways for different locations
  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
    {
      uint8_t *actual_key_buffer = (uint8_t *)key_buffer;
      size_t actual_key_buffer_size = key_buffer_size;

      #if defined(SLI_PSA_DRIVER_FEATURE_ECC)
      psa_key_type_t key_type = psa_get_key_type(attributes);
      if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
        // For ECC public keys, the attributes key size is always the factor
        // determining the curve size
        key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
        if (sli_se_has_format_byte(key_type)) {
          // Need to account for the format byte
          if (*key_buffer != 0x04) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
          actual_key_buffer += 1;
          actual_key_buffer_size -= 1;
          if (actual_key_buffer_size != 2 * key_size) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
          #if defined(SLI_PSA_DRIVER_FEATURE_MONTGOMERY) \
          || defined(SLI_PSA_DRIVER_FEATURE_EDWARDS)
        } else if ((PSA_KEY_TYPE_ECC_GET_FAMILY(key_type)
                    == PSA_ECC_FAMILY_MONTGOMERY)
                   || (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type)
                       == PSA_ECC_FAMILY_TWISTED_EDWARDS)) {
          if (actual_key_buffer_size != key_size) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
          #endif // SLI_PSA_DRIVER_FEATURE_MONTGOMERY || SLI_PSA_DRIVER_FEATURE_EDWARDS
        } else {
          // No other curves supported yet.
          return PSA_ERROR_NOT_SUPPORTED;
        }
      } else
      #endif // SLI_PSA_DRIVER_FEATURE_ECC

      {
        key_size = key_buffer_size;
      }

      // Fill the key desc from attributes
      psa_status_t psa_status = sli_se_key_desc_from_psa_attributes(attributes,
                                                                    key_size,
                                                                    key_desc);
      if (psa_status != PSA_SUCCESS) {
        return psa_status;
      }
      sli_se_key_descriptor_set_plaintext(key_desc,
                                          actual_key_buffer,
                                          actual_key_buffer_size);
      break;
    }

      #if defined(SLI_PSA_DRIVER_FEATURE_OPAQUE_KEYS)
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
    {
      if (key_buffer_size < sizeof(sli_se_opaque_key_context_header_t)) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      sli_se_opaque_key_context_header_t *key_context_header =
        (sli_se_opaque_key_context_header_t *)key_buffer;

      if (key_context_header->struct_version != SLI_SE_OPAQUE_KEY_CONTEXT_VERSION) {
        return PSA_ERROR_STORAGE_FAILURE;
      }

      if (key_context_header->builtin_key_id != 0) {
        sl_se_key_descriptor_t builtin_key_desc;
        switch (key_context_header->builtin_key_id) {
          case SL_SE_KEY_SLOT_APPLICATION_SECURE_BOOT_KEY:
            builtin_key_desc = (sl_se_key_descriptor_t) SL_SE_APPLICATION_SECURE_BOOT_KEY;
            break;
          case SL_SE_KEY_SLOT_APPLICATION_SECURE_DEBUG_KEY:
            builtin_key_desc = (sl_se_key_descriptor_t) SL_SE_APPLICATION_SECURE_DEBUG_KEY;
            break;
          case SL_SE_KEY_SLOT_APPLICATION_AES_128_KEY:
            builtin_key_desc = (sl_se_key_descriptor_t) SL_SE_APPLICATION_AES_128_KEY;
            break;
          case SL_SE_KEY_SLOT_TRUSTZONE_ROOT_KEY:
            builtin_key_desc = (sl_se_key_descriptor_t) SL_SE_TRUSTZONE_ROOT_KEY;
            break;
            #if defined(SLI_PSA_DRIVER_FEATURE_ATTESTATION)
          case SL_SE_KEY_SLOT_APPLICATION_ATTESTATION_KEY:
            builtin_key_desc = (sl_se_key_descriptor_t) SL_SE_APPLICATION_ATTESTATION_KEY;
            break;
          case SL_SE_KEY_SLOT_SE_ATTESTATION_KEY:
            builtin_key_desc = (sl_se_key_descriptor_t) SL_SE_SYSTEM_ATTESTATION_KEY;
            break;
            #endif // SLI_PSA_DRIVER_FEATURE_ATTESTATION
          default:
            return PSA_ERROR_DOES_NOT_EXIST;
        }
        memcpy(key_desc, &builtin_key_desc, sizeof(*key_desc));
        return PSA_SUCCESS;
      } else {
        #if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)
        if (key_buffer_size < sizeof(sli_se_opaque_wrapped_key_context_t)) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        // Reconstruct key_desc from the key context
        memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));

        // Refer to wrapped key context in input
        sli_se_opaque_wrapped_key_context_t key_context_temp;
        sli_se_opaque_wrapped_key_context_t *key_context =
          (sli_se_opaque_wrapped_key_context_t *)key_buffer;
        key_desc->storage.location.buffer.pointer =
          (uint8_t *)&(key_context->wrapped_buffer);

        // If the key buffer is unaligned, copy the content into a
        // temporary buffer in order to prevent hardfaults caused by
        // instructions that do not support unaligned words (e.g. LDRD, LDM).
        if ((uintptr_t)key_buffer & 0x3) {
          memcpy(&key_context_temp, key_buffer, sizeof(sli_se_opaque_wrapped_key_context_t));
          key_context = &key_context_temp;
        }

        key_desc->type = key_context->key_type;
        key_desc->size = key_context->key_size;
        key_desc->flags = key_context->key_flags;

        key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_WRAPPED;
        key_desc->storage.location.buffer.size =
          key_buffer_size - offsetof(sli_se_opaque_wrapped_key_context_t,
                                     wrapped_buffer);

        // Clear temporary key context
        if ((uintptr_t)key_buffer & 0x3) {
          memset(&key_context_temp, 0, sizeof(sli_se_opaque_wrapped_key_context_t));
        }

        if (sli_key_get_size(key_desc, &key_size) != SL_STATUS_OK) {
          memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        uint32_t key_full_size = key_size;

        #if defined(SLI_PSA_DRIVER_FEATURE_SECPR1)
        if (PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes))
            == PSA_ECC_FAMILY_SECP_R1
            && PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(psa_get_key_type(attributes))) {
          key_full_size = 2 * key_full_size;
        }
        #endif     // SLI_PSA_DRIVER_FEATURE_SECPR1

        if (key_desc->storage.location.buffer.size < key_full_size + SLI_SE_WRAPPED_KEY_OVERHEAD) {
          memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        #else   // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS
        return PSA_ERROR_NOT_SUPPORTED;
        #endif   // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS
      }
      break;
    }
      #endif // SLI_PSA_DRIVER_FEATURE_OPAQUE_KEYS

    default:
      return PSA_ERROR_DOES_NOT_EXIST;
  }

  // Run a general validation routine once the key desc has been populated
  psa_status_t status = validate_key_desc(attributes, key_size, key_desc);
  if (status != PSA_SUCCESS) {
    memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  return PSA_SUCCESS;
}

/**
 * @brief
 *   Set the relevant location field of the key descriptor
 */
psa_status_t sli_se_set_key_desc_output(const psa_key_attributes_t* attributes,
                                        uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        size_t key_size,
                                        sl_se_key_descriptor_t *key_desc)
{
  psa_key_location_t location =
    PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
      if (key_buffer_size < key_size) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
      }
      key_desc->storage.location.buffer.pointer = key_buffer;

      #if defined(SLI_SE_KEY_PADDING_REQUIRED)
      key_buffer_size = sli_se_word_align(key_buffer_size);
      #endif

      key_desc->storage.location.buffer.size = key_buffer_size;
      break;

      #if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      #if defined(SLI_SE_KEY_PADDING_REQUIRED)
      key_size = sli_se_word_align(key_size);
      #endif

      if (key_buffer_size < sizeof(sli_se_opaque_wrapped_key_context_t)
          + key_size) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
      }
      key_desc->storage.location.buffer.pointer =
        key_buffer + offsetof(sli_se_opaque_wrapped_key_context_t,
                              wrapped_buffer);
      key_desc->storage.location.buffer.size =
        key_size + SLI_SE_WRAPPED_KEY_OVERHEAD;
      break;
      #endif // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS

    default:
      return PSA_ERROR_DOES_NOT_EXIST;
  }
  return PSA_SUCCESS;
}

#if defined(SLI_SE_VERSION_ECDH_PUBKEY_VALIDATION_UNCERTAIN) \
  && defined(MBEDTLS_ECP_C)                                  \
  && defined(MBEDTLS_PSA_CRYPTO_C)                           \
  && SL_SE_SUPPORT_FW_PRIOR_TO_1_2_2

#include "mbedtls/ecp.h"
#include "psa_crypto_core.h"

psa_status_t sli_se_driver_validate_pubkey_with_fallback(psa_key_type_t key_type,
                                                         size_t key_bits,
                                                         const uint8_t *data,
                                                         size_t data_length)
{
  #if defined(SLI_PSA_DRIVER_FEATURE_ECC)

  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  mbedtls_ecp_group_id grp_id = MBEDTLS_ECP_DP_NONE;

  mbedtls_ecp_group pubkey_grp;
  mbedtls_ecp_point pubkey_point;

  mbedtls_ecp_group_init(&pubkey_grp);
  mbedtls_ecp_point_init(&pubkey_point);

  // Get software-defined curve structure
  grp_id = mbedtls_ecc_group_of_psa(PSA_KEY_TYPE_ECC_GET_FAMILY(key_type),
                                    key_bits,
                                    1);
  if (grp_id == MBEDTLS_ECP_DP_NONE) {
    goto exit;
  }

  psa_status = mbedtls_to_psa_error(mbedtls_ecp_group_load(&pubkey_grp,
                                                           grp_id));
  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }

  // Load public key into mbed TLS structure
  psa_status = mbedtls_to_psa_error(mbedtls_ecp_point_read_binary(
                                      &pubkey_grp,
                                      &pubkey_point,
                                      data,
                                      data_length) );
  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }

  // Validate key.
  psa_status = mbedtls_to_psa_error(mbedtls_ecp_check_pubkey(&pubkey_grp,
                                                             &pubkey_point));

  exit:
  mbedtls_ecp_group_free(&pubkey_grp);
  mbedtls_ecp_point_free(&pubkey_point);
  return psa_status;

  #else // SLI_PSA_DRIVER_FEATURE_ECC

  (void) key_type;
  (void) key_bits;
  (void) data;
  (void) data_length;

  return PSA_ERROR_NOT_SUPPORTED;

  #endif // SLI_PSA_DRIVER_FEATURE_ECC
}

#endif // SLI_SE_VERSION_ECDH_PUBKEY_VALIDATION_UNCERTAIN ...

// -------------------------------------
// Opaque helper functions

#if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)

/**
 * @brief
 *   Store the required parts of the key descriptor in the context placed the
 *   start of the given key buffer.
 */
psa_status_t store_key_desc_in_context(sl_se_key_descriptor_t *key_desc,
                                       uint8_t *key_buffer,
                                       size_t key_buffer_size)
{
  if (key_buffer_size < sizeof(sli_se_opaque_wrapped_key_context_t)) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  sli_se_opaque_wrapped_key_context_t *key_context =
    (sli_se_opaque_wrapped_key_context_t *)key_buffer;
  key_context->header.struct_version = SLI_SE_OPAQUE_KEY_CONTEXT_VERSION;
  key_context->header.builtin_key_id = 0;
  memset(&key_context->header.reserved, 0, sizeof(key_context->header.reserved));
  key_context->key_type = key_desc->type;
  key_context->key_size = key_desc->size;
  key_context->key_flags = key_desc->flags;

  return PSA_SUCCESS;
}

#endif // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS

// -----------------------------------------------------------------------------
// Driver entry points

// -------------------------------------
// Generic driver entry points

psa_status_t sli_se_driver_generate_key(const psa_key_attributes_t *attributes,
                                        uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        size_t *key_buffer_length)
{
  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  size_t key_bits = psa_get_key_bits(attributes);
  size_t key_size = PSA_BITS_TO_BYTES(key_bits);
  if (key_size == 0) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  if (PSA_KEY_TYPE_IS_UNSTRUCTURED(key_type)
      && ((key_bits & 0x7) != 0)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  } else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(key_type)) {
    // PSA Crypto defines generate_key to be an invalid call with a key type
    // of public key.
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Generate a key desc
  sl_se_key_descriptor_t key_desc = { 0 };
  psa_status_t psa_status =
    sli_se_key_desc_from_psa_attributes(attributes,
                                        key_size,
                                        &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  psa_status = sli_se_set_key_desc_output(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          key_size,
                                          &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Generate the key using SE manager
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status_t sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  sl_status = sl_se_generate_key(&cmd_ctx, &key_desc);
  if (sl_status != SL_STATUS_OK) {
    if (sl_status == SL_STATUS_COMMAND_IS_INVALID) {
      // This error will be returned if the key type isn't supported.
      psa_status = PSA_ERROR_NOT_SUPPORTED;
    } else {
      psa_status = PSA_ERROR_HARDWARE_FAILURE;
    }
    goto exit;
  } else {
    if (PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes))
        == PSA_KEY_LOCATION_LOCAL_STORAGE) {
      // Apply clamping if this is a Montgomery key.
      clamp_private_key_if_needed(attributes, key_buffer, key_bits);
    }

    #if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)
    else {
      // Add the key desc to the output array for opaque keys.
      psa_status = store_key_desc_in_context(&key_desc,
                                             key_buffer,
                                             key_buffer_size);
      if (psa_status != PSA_SUCCESS) {
        goto exit;
      }
    }
    #endif // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS

    psa_status = set_key_buffer_length(attributes, key_size, key_buffer_length);
  }
  // Cleanup
  exit:
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  return psa_status;
}

psa_status_t sli_se_driver_export_public_key(
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  uint8_t *data,
  size_t data_size,
  size_t *data_length)
{
  #if defined(SLI_PSA_DRIVER_FEATURE_ECC)

  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || data == NULL
      || data_size == 0
      || data_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Build key descs for the private key
  sl_se_key_descriptor_t priv_key_desc = { 0 };
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &priv_key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // ECC public keys are written in uncompressed format with a preceeding 0x04
  // format byte. This byte should however not be present for Montgomery keys
  uint32_t prepend_format_byte = 1;
  #if defined(SLI_PSA_DRIVER_FEATURE_MONTGOMERY) || defined(SLI_PSA_DRIVER_FEATURE_EDWARDS)
  if ((PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes))
       == PSA_ECC_FAMILY_MONTGOMERY)
      || (PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes))
          == PSA_ECC_FAMILY_TWISTED_EDWARDS)) {
    prepend_format_byte = 0;
  }
  #endif   // SLI_PSA_DRIVER_FEATURE_MONTGOMERY || SLI_PSA_DRIVER_FEATURE_EDWARDS

  sl_se_key_descriptor_t pub_key_desc = priv_key_desc;
  size_t padding = 0;

  #if defined(SLI_SE_KEY_PADDING_REQUIRED)
  // Since we were able to successfully build a key desc, we know that the key
  // is supported. However, we must also account for non-word-aligned keys
  uint8_t temp_pub_buffer[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
  uint8_t temp_priv_buffer[SLI_SE_MAX_PADDED_KEY_PAIR_SIZE] = { 0 };
  size_t priv_key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
  if (PSA_KEY_TYPE_IS_ECC(psa_get_key_type(attributes))) {
    padding = sli_se_get_padding(PSA_BITS_TO_BYTES(psa_get_key_bits(attributes)));
  }
  if (padding > 0) {
    if (priv_key_desc.storage.method == SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT) {
      // We must only fix the padding for plaintext private keys. Opaque padding
      // is already handled in import_key
      if (key_buffer_size < priv_key_size) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      sli_se_pad_big_endian(temp_priv_buffer, key_buffer, priv_key_size);
      sli_se_key_descriptor_set_plaintext(&priv_key_desc,
                                          temp_priv_buffer,
                                          sizeof(temp_priv_buffer));
    }
    // Point the key desc to the temp buffer
    sli_se_key_descriptor_set_plaintext(&pub_key_desc,
                                        temp_pub_buffer,
                                        sizeof(temp_pub_buffer));
  } else
  #endif   // SLI_SE_KEY_PADDING_REQUIRED

  {
    // Account for format byte where applicable
    sli_se_key_descriptor_set_plaintext(&pub_key_desc,
                                        data + prepend_format_byte,
                                        data_size - prepend_format_byte);
  }

  // Clear non exportable and private key flags from the public key desc,
  // And set the public flag
  pub_key_desc.flags &= ~(SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY
                          | SL_SE_KEY_FLAG_NON_EXPORTABLE);
  pub_key_desc.flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY;
  uint32_t storage_size = 0;
  sl_status_t sl_status =
    sli_key_get_storage_size(&pub_key_desc, &storage_size);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  // We must fit entire output key + possibly a format byte
  // We don't have to fit the padding bytes into the data buffer.
  storage_size = storage_size + prepend_format_byte - (2 * padding);
  if (data_size < storage_size) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  #if defined(SLI_SE_VERSION_ED25519_ERRATA_CHECK_REQUIRED)
  psa_status = sli_se_check_eddsa_errata(attributes, &cmd_ctx);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  #endif   // SLI_SE_VERSION_ED25519_ERRATA_CHECK_REQUIRED

  sl_status = sl_se_export_public_key(&cmd_ctx, &priv_key_desc, &pub_key_desc);
  if (sl_status == SL_STATUS_FAIL) {
    // This specific code maps to 'does not exist' for builtin keys
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
  } else if (sl_status != SL_STATUS_OK) {
    if (sl_status == SL_STATUS_COMMAND_IS_INVALID) {
      // This error will be returned if the key type isn't supported.
      psa_status = PSA_ERROR_NOT_SUPPORTED;
    } else {
      psa_status = PSA_ERROR_HARDWARE_FAILURE;
    }
  } else {
    psa_status = PSA_SUCCESS;

    #if defined(SLI_SE_KEY_PADDING_REQUIRED)
    if (padding > 0) {
      // Now it is time to copy the actual ket from the temp buffer to the
      // output buffer. Write to an offset if applicable, to account for the
      // format byte
      sli_se_unpad_curve_point(temp_pub_buffer,
                               data + prepend_format_byte,
                               (storage_size - prepend_format_byte) / 2);
      sli_psa_zeroize(temp_priv_buffer, priv_key_size);
    }
    #endif   // SLI_SE_KEY_PADDING_REQUIRED

    // Write the uncompressed format byte and actual data length
    if (prepend_format_byte == 1) {
      *data = 0x04;
    }
    *data_length = storage_size;
  }

  // Cleanup
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  return psa_status;

  #else // SLI_PSA_DRIVER_FEATURE_ECC

  (void) attributes;
  (void) key_buffer;
  (void) key_buffer_size;
  (void) data;
  (void) data_size;
  (void) data_length;

  return PSA_ERROR_NOT_SUPPORTED;

  #endif // SLI_PSA_DRIVER_FEATURE_ECC
}

// -------------------------------------
// Opaque driver entry points

psa_status_t sli_se_opaque_generate_key(const psa_key_attributes_t *attributes,
                                        uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        size_t *key_buffer_length)
{
  return sli_se_driver_generate_key(attributes,
                                    key_buffer,
                                    key_buffer_size,
                                    key_buffer_length);
}

psa_status_t sli_se_opaque_export_public_key(
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  uint8_t *data,
  size_t data_size,
  size_t *data_length)
{
  return sli_se_driver_export_public_key(attributes,
                                         key_buffer,
                                         key_buffer_size,
                                         data,
                                         data_size,
                                         data_length);
}

#if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)

psa_status_t sli_se_opaque_copy_key(const psa_key_attributes_t *attributes,
                                    const uint8_t *source_key,
                                    size_t source_key_length,
                                    uint8_t *target_key_buffer,
                                    size_t target_key_buffer_size,
                                    size_t *target_key_buffer_length)
{
  size_t bits = 0;
  return sli_se_opaque_import_key(attributes,
                                  source_key,
                                  source_key_length,
                                  target_key_buffer,
                                  target_key_buffer_size,
                                  target_key_buffer_length,
                                  &bits);
}

psa_status_t sli_se_opaque_import_key(const psa_key_attributes_t *attributes,
                                      const uint8_t *data,
                                      size_t data_length,
                                      uint8_t *key_buffer,
                                      size_t key_buffer_size,
                                      size_t *key_buffer_length,
                                      size_t *bits)
{
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;

  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || data == NULL
      || data_length == 0
      || key_buffer_length == NULL
      || bits == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  *key_buffer_length = 0;

  psa_key_type_t key_type = psa_get_key_type(attributes);

  // Store bits value for imported key
  *bits = 8 * data_length;

  switch (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type)) {
    #if defined(SLI_PSA_DRIVER_FEATURE_SECPR1)
    case PSA_ECC_FAMILY_SECP_R1:
      if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
        *bits -= 8;
        *bits /= 2;
      }
      if (*bits == PSA_BITS_TO_BYTES(521) * 8) {
        *bits = 521;
      }
      break;
    #endif // SLI_PSA_DRIVER_FEATURE_SECPR1

    #if defined(SLI_PSA_DRIVER_FEATURE_MONTGOMERY) || defined(SLI_PSA_DRIVER_FEATURE_EDWARDS)
    case PSA_ECC_FAMILY_MONTGOMERY:
    case PSA_ECC_FAMILY_TWISTED_EDWARDS:
      if (data_length == 32) {
        *bits = 255;
      }
      break;
    #endif // SLI_PSA_DRIVER_FEATURE_MONTGOMERY || SLI_PSA_DRIVER_FEATURE_EDWARDS

    default:
      break;
  }

  size_t offset = 0;
  size_t padding = 0;
  size_t key_size = 0;

  #if defined(SLI_PSA_DRIVER_FEATURE_ECC)
  if (PSA_KEY_TYPE_IS_ECC(key_type)) {
    // Validate key and get size.
    psa_status = sli_se_driver_validate_ecc_key(attributes,
                                                data,
                                                data_length,
                                                &key_size);
    if (psa_status != PSA_SUCCESS) {
      return psa_status;
    }
    key_size = PSA_BITS_TO_BYTES(key_size);
    if (sli_se_has_format_byte(key_type)) {
      data_length -= 1;
      data += 1;
    }

    #if defined(SLI_SE_KEY_PADDING_REQUIRED)
    if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) == PSA_ECC_FAMILY_SECP_R1) {
      // We must add some padding if offset is nonzero
      offset = sli_se_get_padding(key_size);
    }
    #endif   // SLI_SE_KEY_PADDING_REQUIRED
  } else
  #endif // SLI_PSA_DRIVER_FEATURE_ECC

  {
    key_size = data_length;
  }

  #if defined(SLI_SE_KEY_PADDING_REQUIRED)
  // Size must at least fit max ECC key size plus padding
  uint8_t temp_buffer[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
  #endif

  // Create a key desc that will represent the wrapped key
  sl_se_key_descriptor_t imported_key_desc = { 0 };
  psa_status =
    sli_se_key_desc_from_psa_attributes(attributes,
                                        key_size,
                                        &imported_key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  // Create a key desc representing the plaintext input key
  sl_se_key_descriptor_t plaintext_key_desc = imported_key_desc;

  #if defined(SLI_SE_KEY_PADDING_REQUIRED)
  if (offset == 0) {
    sli_se_key_descriptor_set_plaintext(&plaintext_key_desc, data, data_length);
  } else {
    // We must account for the offset.
    // Write the key data to offset position in temp buffer
    if (sizeof(temp_buffer) < data_length + 2 * offset) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    #if defined(SLI_PSA_DRIVER_FEATURE_ECC)
    if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) == PSA_ECC_FAMILY_SECP_R1) {
      if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
        sli_se_pad_big_endian(temp_buffer, data, key_size);
        padding = offset;
      } else {
        // Must be public key
        sli_se_pad_curve_point(temp_buffer, data, key_size);
        padding = 2 * offset;
      }
      sli_se_key_descriptor_set_plaintext(&plaintext_key_desc,
                                          temp_buffer,
                                          data_length + padding);
    } else
    #endif   // SLI_PSA_DRIVER_FEATURE_ECC
    {
      return PSA_ERROR_CORRUPTION_DETECTED;
    }
  }
  #else // SLI_SE_KEY_PADDING_REQUIRED
  (void)offset;
  sli_se_key_descriptor_set_plaintext(&plaintext_key_desc, data, data_length);
  #endif // SLI_SE_KEY_PADDING_REQUIRED

  sl_se_command_context_t cmd_ctx = SL_SE_COMMAND_CONTEXT_INIT;
  sl_status_t sl_status = SL_STATUS_OK;
  // Set location specific properties for the output key buffer
  psa_status = sli_se_set_key_desc_output(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          data_length + padding,
                                          &imported_key_desc);
  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }

  sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
    goto exit;
  }

  // Call SE manager to import the key
  sl_status = sl_se_import_key(&cmd_ctx,
                               &plaintext_key_desc,
                               &imported_key_desc);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  } else {
    // Add the key desc parameters to the output array
    psa_status = store_key_desc_in_context(&imported_key_desc,
                                           key_buffer,
                                           key_buffer_size);
    if (psa_status != PSA_SUCCESS) {
      goto exit;
    }

    psa_status = set_key_buffer_length(attributes,
                                       data_length + padding,
                                       key_buffer_length);
  }

  // Cleanup
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  }

  exit:

  #if defined(SLI_SE_KEY_PADDING_REQUIRED)
  sli_psa_zeroize(temp_buffer, sizeof(temp_buffer));
  #endif

  return psa_status;
}

psa_status_t sli_se_opaque_export_key(const psa_key_attributes_t *attributes,
                                      const uint8_t *key_buffer,
                                      size_t key_buffer_size,
                                      uint8_t *data,
                                      size_t data_size,
                                      size_t *data_length)
{
  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || data == NULL
      || data_size == 0
      || data_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  // Check that key can be exported
  if (!(psa_get_key_usage_flags(attributes) & PSA_KEY_USAGE_EXPORT)) {
    return PSA_ERROR_NOT_PERMITTED;
  }

  sl_se_key_descriptor_t imported_key = { 0 };
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &imported_key);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Create a plaintext key for the output
  sl_se_key_descriptor_t plaintext_key = imported_key;
  uint32_t storage_size = 0;
  psa_key_type_t key_type = psa_get_key_type(attributes);
  sl_status_t sl_status = sli_key_get_storage_size(&plaintext_key, &storage_size);
  uint32_t prepend_format_byte = sli_se_has_format_byte(key_type);
  if (prepend_format_byte == 1) {
    // Make room for the format byte
    *data = 0x04;
    data += 1;
    data_size -= 1;
  }

  size_t key_bits = psa_get_key_bits(attributes);

  #if defined(SLI_SE_KEY_PADDING_REQUIRED)
  // We must handle non-word-aligned keys with a temporary buffer
  uint8_t temp_key_buffer[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
  size_t padding = 0;

  #if defined(SLI_PSA_DRIVER_FEATURE_ECC)
  size_t key_size = PSA_BITS_TO_BYTES(key_bits);
  if (PSA_KEY_TYPE_IS_ECC(key_type)) {
    padding = sli_se_get_padding(key_size);
  }
  #endif   // SLI_PSA_DRIVER_FEATURE_ECC

  if (padding > 0) {
    if (storage_size > sizeof(temp_key_buffer)) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }
    sli_se_key_descriptor_set_plaintext(&plaintext_key,
                                        temp_key_buffer,
                                        sizeof(temp_key_buffer));
    storage_size -= padding;
    #if defined(SLI_PSA_DRIVER_FEATURE_ECC)
    if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
      // Padding must be applied twice for public keys
      storage_size -= padding;
    }
    #endif   // SLI_PSA_DRIVER_FEATURE_ECC
  } else {
    if ((storage_size - imported_key.size) < 4) {
      // SE manager has rounded the storage size up for word-alignment
      storage_size = imported_key.size;
    }
    sli_se_key_descriptor_set_plaintext(&plaintext_key, data, data_size);
  }
  #else // SLI_SE_KEY_PADDING_REQUIRED
  sli_se_key_descriptor_set_plaintext(&plaintext_key, data, data_size);
  #endif // SLI_SE_KEY_PADDING_REQUIRED

  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  if (storage_size > data_size) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  // Export key
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  sl_status = sl_se_export_key(&cmd_ctx, &imported_key, &plaintext_key);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  } else {
    psa_status = PSA_SUCCESS;

    #if defined(SLI_SE_KEY_PADDING_REQUIRED)
    // Handle padding.
    if (padding > 0) {
      #if defined(SLI_PSA_DRIVER_FEATURE_ECC)
      // Copy out the padded key
      if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
        sli_se_unpad_big_endian(temp_key_buffer, data, key_size);
        sli_psa_zeroize(temp_key_buffer, key_size);
      } else if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
        sli_se_unpad_curve_point(temp_key_buffer, data, key_size);
      } else
      #endif   // SLI_PSA_DRIVER_FEATURE_ECC
      {
        // This should never happen
        return PSA_ERROR_BAD_STATE;
      }
    }
    #endif // SLI_SE_KEY_PADDING_REQUIRED

    // Apply clamping if this is a Montgomery key.
    clamp_private_key_if_needed(attributes, data, key_bits);

    // Successful operation. Set ouput length
    *data_length = storage_size + prepend_format_byte;
  }

  // Cleanup
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  return psa_status;
}

#endif // SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS

// -------------------------------------
// Transparent driver entry points

psa_status_t sli_se_transparent_generate_key(
  const psa_key_attributes_t *attributes,
  uint8_t *key_buffer,
  size_t key_buffer_size,
  size_t *key_buffer_length)
{
  psa_key_type_t type = psa_get_key_type(attributes);

  // We don't support generating symmetric keys with transparent drivers;
  // it should be done by the core instead.
  if (PSA_KEY_TYPE_IS_UNSTRUCTURED(type)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  return sli_se_driver_generate_key(attributes,
                                    key_buffer,
                                    key_buffer_size,
                                    key_buffer_length);
}

psa_status_t sli_se_transparent_export_public_key(
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  uint8_t *data,
  size_t data_size,
  size_t *data_length)
{
  // If the key is stored transparently and is already a public key,
  // let the core handle it.
  if (PSA_KEY_TYPE_IS_PUBLIC_KEY(psa_get_key_type(attributes))) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  return sli_se_driver_export_public_key(attributes,
                                         key_buffer,
                                         key_buffer_size,
                                         data,
                                         data_size,
                                         data_length);
}

psa_status_t sli_se_transparent_import_key(const psa_key_attributes_t *attributes,
                                           const uint8_t *data,
                                           size_t data_length,
                                           uint8_t *key_buffer,
                                           size_t key_buffer_size,
                                           size_t *key_buffer_length,
                                           size_t *bits)
{
  #if defined(SLI_PSA_DRIVER_FEATURE_ECC)

  // Our driver only handles ECC keys (since they are better done accelerated).
  if (PSA_KEY_TYPE_IS_ECC(psa_get_key_type(attributes))) {
    psa_status_t status = sli_se_driver_validate_ecc_key(attributes,
                                                         data,
                                                         data_length,
                                                         bits);
    if (status != PSA_SUCCESS) {
      return status;
    }

    if ( key_buffer_size < data_length ) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(key_buffer, data, data_length);
    clamp_private_key_if_needed(attributes, key_buffer, *bits);
    *key_buffer_length = data_length;

    return PSA_SUCCESS;
  }

  #else // SLI_PSA_DRIVER_FEATURE_ECC

  (void)attributes;
  (void)data;
  (void)data_length;
  (void)key_buffer;
  (void)key_buffer_size;
  (void)key_buffer_length;
  (void)bits;

  #endif // SLI_PSA_DRIVER_FEATURE_ECC

  return PSA_ERROR_NOT_SUPPORTED;
}

#endif // SLI_MBEDTLS_DEVICE_HSE

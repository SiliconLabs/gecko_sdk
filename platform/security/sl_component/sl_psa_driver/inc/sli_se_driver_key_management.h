/***************************************************************************//**
 * @file
 * @brief SE Driver for Silicon Labs devices with an embedded SE, for use with
 *        PSA Crypto and Mbed TLS
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

#ifndef SLI_SE_DRIVER_KEY_MANAGEMENT_H
#define SLI_SE_DRIVER_KEY_MANAGEMENT_H

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

/***************************************************************************//**
 * \addtogroup sl_psa_drivers
 * \{
 ******************************************************************************/

/***************************************************************************//**
 * \addtogroup sl_psa_drivers_se
 * \{
 ******************************************************************************/

#include "sli_psa_driver_features.h"

#if defined(SLI_MBEDTLS_DEVICE_HSE)

#include "sli_se_opaque_types.h"
#include "sli_se_version_dependencies.h"

#include "sl_se_manager.h"

// Replace inclusion of crypto_driver_common.h with the new psa driver interface
// header file when it becomes available.
#include "psa/crypto_driver_common.h"

#include <string.h>

// -----------------------------------------------------------------------------
// Defines and macros

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
/// Max available curve size
  #define SLI_SE_MAX_CURVE_SIZE   (521)
#else
/// Max available curve size
  #define SLI_SE_MAX_CURVE_SIZE   (256)
#endif

/// Byte size of maximum available ECC private key padded to word-alignment
#define SLI_SE_MAX_PADDED_KEY_PAIR_SIZE     \
  (PSA_BITS_TO_BYTES(SLI_SE_MAX_CURVE_SIZE) \
   + sli_se_get_padding(PSA_BITS_TO_BYTES(SLI_SE_MAX_CURVE_SIZE)))

/// Byte size of maximum available ECDSA signature padded to word-alignment
#define SLI_SE_MAX_PADDED_SIGNATURE_SIZE           \
  (PSA_ECDSA_SIGNATURE_SIZE(SLI_SE_MAX_CURVE_SIZE) \
   + 2 * sli_se_get_padding(PSA_BITS_TO_BYTES(SLI_SE_MAX_CURVE_SIZE)))

/// Byte size of maximum available ECC public key padded to word-alignment
#define SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE (SLI_SE_MAX_PADDED_SIGNATURE_SIZE)

/** Determine the number of bytes necessary to pad size to a word-alignment
 * @param size
 *   Unsigend integer type.
 * @returns the number of padding bytes required
 */
#define sli_se_get_padding(size)  ((4 - (size & 3)) & 3)

/** Pad size to word alignment
 * @param size
 *   Unsigend integer type.
 * @returns the number of padding bytes required
 */
#define sli_se_word_align(size)   ((size + 3) & ~3)

// -----------------------------------------------------------------------------
// Static inline functions

/**
 * @brief
 *   Pad the big endian number in buffer with zeros
 * @param tmp_buffer
 *   A buffer to store the padded number
 * @param buffer
 *   The buffer containing the number
 * @param buffer_size
 *   Byte size of the number to pad
 * @note
 *   Buffer sizes must be pre-validated.
 */
static inline void sli_se_pad_big_endian(uint8_t *tmp_buffer,
                                         const uint8_t *buffer,
                                         size_t  buffer_size)
{
  size_t padding = sli_se_get_padding(buffer_size);
  memset(tmp_buffer, 0, padding); // Set the preceeding 0s
  memcpy(tmp_buffer + padding, buffer, buffer_size); // Copy actual content
}

/**
 * @brief
 *   Remove the padding from a zero-padded big endian number
 * @param tmp_buffer
 *   Buffer containing the padded number
 * @param buffer
 *   The buffer to write unpadded number to
 * @param buffer_size
 *   Byte size of unpadded number
 * @note
 *   Buffer sizes must be pre-validated.
 */
static inline void sli_se_unpad_big_endian(const uint8_t *tmp_buffer,
                                           uint8_t *buffer,
                                           size_t buffer_size)
{
  size_t padding = sli_se_get_padding(buffer_size);
  memcpy(buffer, tmp_buffer + padding, buffer_size);
}

/**
 * @brief
 *   Pad each coordinate of a big endian curve point
 * @param tmp_buffer
 *   A buffer to store the padded point
 * @param buffer
 *   The buffer containing the point
 * @param coord_size
 *   Byte size of each coordinate
 * @note
 *   Buffer sizes must be pre-validated.
 */
static inline void sli_se_pad_curve_point(uint8_t *tmp_buffer,
                                          const uint8_t *buffer,
                                          size_t coord_size)
{
  size_t padding = sli_se_get_padding(coord_size);
  sli_se_pad_big_endian(tmp_buffer, buffer, coord_size);
  sli_se_pad_big_endian(tmp_buffer + coord_size + padding,
                        buffer + coord_size,
                        coord_size);
}

/**
 * @brief
 *   Strip away the padding from each coordinate of a big endian curve point
 * @param tmp_buffer
 *   The buffer where the padded point is stored
 * @param buffer
 *   A buffer to store the unpadded point
 * @param coord_size
 *   Byte size of each coordinate
 * @note
 *   Buffer sizes must be pre-validated.
 */
static inline void sli_se_unpad_curve_point(const uint8_t *tmp_buffer,
                                            uint8_t *buffer,
                                            size_t coord_size)
{
  size_t padding = sli_se_get_padding(coord_size);
  sli_se_unpad_big_endian(tmp_buffer, buffer, coord_size);
  sli_se_unpad_big_endian(tmp_buffer + coord_size + padding,
                          buffer + coord_size,
                          coord_size);
}

/**
 * @brief
 *   Set the key desc to a plaintext key type pointing to data.
 * @param[out] key_desc
 *   The SE manager key struct representing a key
 * @param[in] data
 *   Buffer containing the key
 * @param[in] data_length
 *   Length of the buffer
 */
static inline
void sli_se_key_descriptor_set_plaintext(sl_se_key_descriptor_t *key_desc,
                                         const uint8_t *data,
                                         size_t data_length)
{
  key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT;
  key_desc->storage.location.buffer.pointer = (uint8_t *)data;
  // TODO: Improve SE manager alignment requirements
  key_desc->storage.location.buffer.size = sli_se_word_align(data_length);
}

/**
 * @brief
 *   Determine if a format byte is necessary for the key type
 * @param key_type
 *   PSA key type for the key in question
 * @returns
 *   1 if the key type requires a format byte,
 *   0 otherwise
 */
static inline uint32_t sli_se_has_format_byte(psa_key_type_t key_type)
{
  if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
    if ((PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) != PSA_ECC_FAMILY_MONTGOMERY)
        && (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) != PSA_ECC_FAMILY_TWISTED_EDWARDS)) {
      return 1U;
    }
  }
  return 0U;
}

// -----------------------------------------------------------------------------
// Function declarations

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *   Store the required parts of the key descriptor in the context placed the
 *   start of the given key buffer.
 *
 * @param key_desc[in]
 *   Key descriptor to export.
 * @param key_buffer[out]
 *   Pointer to the key buffer containing key context.
 * @param key_buffer_size[in]
 *   Size of key buffer.
 * @returns
 *   PSA_SUCCESS stored key desc in context
 *   PSA_ERROR_BUFFER_TOO_SMALL output buffer is too small to hold an opaque key context
 */
psa_status_t store_key_desc_in_context(sl_se_key_descriptor_t *key_desc,
                                       uint8_t *key_buffer,
                                       size_t key_buffer_size);

/**
 * @brief
 *   Get the key descriptor from the key buffer and attributes
 *
 * @param[in] attributes
 *   The PSA attributes struct representing a key
 * @param[in] key_buffer
 *   Buffer containing key context from PSA core
 * @param[in] key_buffer_size
 *   Size of key_buffer
 * @param[out] key_desc
 *   The SE manager key descriptor struct to populate
 * @returns
 *   PSA_SUCCESS if everything is OK
 *   PSA_ERROR_INVALID_ARGUMENT if key buffer does not mach a valid key context
 * @note
 *   The resulting key descriptor is only valid as long as the key_buffer
 *   array remains in scope. In practice, this is only guaranteed throughout a
 *   single driver function.
 */
psa_status_t sli_se_key_desc_from_input(const psa_key_attributes_t* attributes,
                                        const uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        sl_se_key_descriptor_t *key_desc);

/**
 * @brief
 *   Build a key descriptor from a PSA attributest struct
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
psa_status_t sli_se_key_desc_from_psa_attributes(const psa_key_attributes_t *attributes,
                                                 size_t key_size,
                                                 sl_se_key_descriptor_t *key_desc);

/**
 * @brief
 *   Set the relevant location field of the key descriptor
 *
 * @param[in] attributes
 *   The PSA attributes struct representing a key
 * @param[in] key_buffer
 *   Buffer containing key context from PSA core
 * @param[in] key_buffer_size
 *   Size of key_buffer
 * @param[in] key_size
 *    Size of the key
 * @param[out] key_desc
 *   The SE manager key descriptor struct to populate
 * @returns
 *   PSA_SUCCESS if everything is OK
 *   PSA_ERROR_INVALID_ARGUMENT if key buffer does not mach a valid key context
 */
psa_status_t sli_se_set_key_desc_output(const psa_key_attributes_t* attributes,
                                        uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        size_t key_size,
                                        sl_se_key_descriptor_t *key_desc);

// psa_generate_key entry point for both opaque and transparent drivers
psa_status_t sli_se_driver_generate_key(const psa_key_attributes_t *attributes,
                                        uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        size_t *output_length);

#if defined(SLI_SE_VERSION_ECDH_PUBKEY_VALIDATION_UNCERTAIN) \
  && defined(MBEDTLS_ECP_C)                                  \
  && defined(MBEDTLS_PSA_CRYPTO_C)                           \
  && SL_SE_SUPPORT_FW_PRIOR_TO_1_2_2
psa_status_t sli_se_driver_validate_pubkey_with_fallback(psa_key_type_t key_type,
                                                         size_t key_bits,
                                                         const uint8_t *data,
                                                         size_t data_length);
#endif // Software fallback for SE < 1.2.2

#ifdef __cplusplus
}
#endif

#endif // SLI_MBEDTLS_DEVICE_HSE

/** \} (end addtogroup sl_psa_drivers_se) */
/** \} (end addtogroup sl_psa_drivers) */

/// @endcond

#endif // SLI_SE_DRIVER_KEY_MANAGEMENT_H

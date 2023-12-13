/***************************************************************************//**
 * @file
 * @brief Silicon Labs internal PSA Crypto utility functions.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SLI_PSA_CRYPTO_H
#define SLI_PSA_CRYPTO_H

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#include "psa/crypto.h"

#include <stddef.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
// Defines and Macros

// Persistent key ID ranges.
#define SLI_PSA_KEY_ID_RANGE_THREAD_START (0x00020000)
#define SLI_PSA_KEY_ID_RANGE_THREAD_END   (0x0002FFFF)
#define SLI_PSA_KEY_ID_RANGE_ZIGBEE_START (0x00030000)
#define SLI_PSA_KEY_ID_RANGE_ZIGBEE_END   (0x0003FFFF)

// Convert a type name into an enum entry name, since enum entries and type
// names share the same C namespace.
#define SLI_PSA_CONTEXT_ENUM_NAME(NAME) \
  NAME ## _e
#define SLI_MBEDTLS_CONTEXT_ENUM_NAME(NAME) \
  NAME ## _e

// Convenience macros for getting the size of a context structure type
#define SLI_PSA_CONTEXT_GET_RUNTIME_SIZE(NAME) \
  (sli_psa_context_get_size(SLI_PSA_CONTEXT_ENUM_NAME(NAME)))
#define SLI_MBEDTLS_CONTEXT_GET_RUNTIME_SIZE(NAME) \
  (sli_mbedtls_context_get_size(SLI_MBEDTLS_CONTEXT_ENUM_NAME(NAME)))

// -----------------------------------------------------------------------------
// Type Definitions

// Type names supported by sli_psa_context_get_size.
typedef enum {
  SLI_PSA_CONTEXT_ENUM_NAME(psa_hash_operation_t),
  SLI_PSA_CONTEXT_ENUM_NAME(psa_cipher_operation_t),
  SLI_PSA_CONTEXT_ENUM_NAME(psa_pake_operation_t),
  SLI_PSA_CONTEXT_ENUM_NAME(psa_mac_operation_t),
  SLI_PSA_CONTEXT_ENUM_NAME(psa_aead_operation_t),
  SLI_PSA_CONTEXT_ENUM_NAME(psa_key_derivation_operation_t),
  SLI_PSA_CONTEXT_ENUM_NAME(psa_key_attributes_t)
} sli_psa_context_name_t;

// Type names supported by sli_mbedtls_context_get_size.
typedef enum {
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_aes_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_ccm_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_cipher_context_t),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_ctr_drbg_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_entropy_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_md_context_t),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_nist_kw_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_pk_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_sha1_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_sha256_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_ssl_config),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_ssl_context),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_ssl_cookie_ctx),
  SLI_MBEDTLS_CONTEXT_ENUM_NAME(mbedtls_x509_crt)
} sli_mbedtls_context_name_t;

// -----------------------------------------------------------------------------
// Function Declarations

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @brief
 *   Get the size of a named PSA context structure. This is valuable for code
 *   shipping as precompiled libraries and needing to link with a source version
 *   of PSA Crypto, since the context structures can change in size based on
 *   configuration options which might not have been present at library
 *   compilation time.
 *
 * @param ctx_type
 *   Which context structure to get the size of. Use
 *   #SLI_PSA_CONTEXT_ENUM_NAME(psa_xxx_operation_t) as argument.
 *
 * @return
 *   Size (in bytes) of the context structure as expected by the current build.
 ******************************************************************************/
size_t sli_psa_context_get_size(sli_psa_context_name_t ctx_type);

/***************************************************************************//**
 * @brief
 *   Get the size of a named Mbed TLS context structure. This is valuable for
 *   code shipping as precompiled libraries and needing to link with a source
 *   version of PSA Crypto, since the context structures can change in size
 *   based on configuration options which might not have been present at library
 *   compilation time.
 *
 * @param ctx_type
 *   Which context structure to get the size of. Use
 *   #SLI_MBEDTLS_CONTEXT_ENUM_NAME(<mbed-tls-type>) as argument.
 *
 * @return
 *   Size (in bytes) of the context structure as expected by the current build.
 ******************************************************************************/
size_t sli_mbedtls_context_get_size(sli_mbedtls_context_name_t ctx_type);

/***************************************************************************//**
 * @brief
 *   Check if a key is copyable even though the key attributes do not have the
 *   PSA_KEY_USAGE_COPY flag set.
 *
 * @param key_id
 *   The key ID of the key of interest.
 *
 * @return
 *   True if the key should be unconditionally copyable, otherwise false.
 ******************************************************************************/
bool sli_psa_key_is_unconditionally_copyable(psa_key_id_t key_id);

#ifdef __cplusplus
}
#endif

/// @endcond

#endif // SLI_PSA_CRYPTO_H

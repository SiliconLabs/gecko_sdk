/***************************************************************************//**
 * @file
 * @brief PSA Crypto driver feature enablement.
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

#ifndef SLI_PSA_DRIVER_FEATURES_H
#define SLI_PSA_DRIVER_FEATURES_H

#include "mbedtls/build_info.h"

// -----------------------------------------------------------------------------
// Feature inclusion (available AND requested)

// -------------------------------------
// Keys

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define SLI_PSA_DRIVER_FEATURE_OPAQUE_KEYS
  #define SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS
#endif

#if defined(SLI_MBEDTLS_DEVICE_VSE) && defined(SEPUF_PRESENT)
  #define SLI_PSA_DRIVER_FEATURE_PUF_KEY
#endif

#if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) \
  && (defined(SLI_MBEDTLS_DEVICE_HSE) || defined(SLI_PSA_DRIVER_FEATURE_PUF_KEY))
  #define SLI_PSA_DRIVER_FEATURE_OPAQUE_KEYS
  #define SLI_PSA_DRIVER_FEATURE_BUILTIN_KEYS
#endif

// -------------------------------------
// TRNG

#if defined(SLI_MBEDTLS_DEVICE_HSE)           \
  || defined(SLI_MBEDTLS_DEVICE_VSE)          \
  || defined(SLI_MBEDTLS_DEVICE_S1_WITH_TRNG) \
  || defined(SLI_MBEDTLS_DEVICE_SI91X)
  #define SLI_PSA_DRIVER_FEATURE_TRNG
#endif

#if defined(SLI_MBEDTLS_DEVICE_S1_WITH_TRNG_ERRATA)
  #define SLI_PSA_DRIVER_FEATURE_TRNG_ERRATA_HANDLING
#endif

// -------------------------------------
// Attestation

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define SLI_PSA_DRIVER_FEATURE_ATTESTATION
#endif

// -------------------------------------
// AEAD

#if defined(PSA_WANT_ALG_CCM) && defined(MBEDTLS_PSA_ACCEL_ALG_CCM)
  #define SLI_PSA_DRIVER_FEATURE_AEAD
  #define SLI_PSA_DRIVER_FEATURE_AEAD_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_CCM
#endif

#if defined(PSA_WANT_ALG_GCM) && defined(MBEDTLS_PSA_ACCEL_ALG_GCM)
  #define SLI_PSA_DRIVER_FEATURE_AEAD
  #define SLI_PSA_DRIVER_FEATURE_AEAD_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_GCM

// TODO: add public config option.
  #if defined(SLI_PSA_SUPPORT_GCM_IV_CALCULATION)
// Can use software implementation in order to compute IVs.
    #define SLI_PSA_DRIVER_FEATURE_GCM_IV_CALCULATION
  #endif
#endif

#if defined(PSA_WANT_ALG_CHACHA20_POLY1305) && defined(MBEDTLS_PSA_ACCEL_ALG_CHACHA20_POLY1305)
  #define SLI_PSA_DRIVER_FEATURE_AEAD
  #define SLI_PSA_DRIVER_FEATURE_CHACHAPOLY
#endif

// -------------------------------------
// Cipher

#if defined(PSA_WANT_KEY_TYPE_AES) && defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_AES)

  #define SLI_PSA_DRIVER_FEATURE_AES

  #if defined(PSA_WANT_ALG_ECB_NO_PADDING) && defined(MBEDTLS_PSA_ACCEL_ALG_ECB_NO_PADDING)
    #define SLI_PSA_DRIVER_FEATURE_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_BLOCK_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_AES_ECB
    #define SLI_PSA_DRIVER_FEATURE_CIPHER_MULTIPART
  #endif

  #if defined(PSA_WANT_ALG_CTR) && defined(MBEDTLS_PSA_ACCEL_ALG_CTR)
    #define SLI_PSA_DRIVER_FEATURE_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_BLOCK_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_AES_CTR
    #define SLI_PSA_DRIVER_FEATURE_AES_CTR_VARIANT
    #define SLI_PSA_DRIVER_FEATURE_CIPHER_MULTIPART
  #endif

  #if defined(PSA_WANT_ALG_CFB) && defined(MBEDTLS_PSA_ACCEL_ALG_CFB)
    #define SLI_PSA_DRIVER_FEATURE_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_BLOCK_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_AES_CFB
    #define SLI_PSA_DRIVER_FEATURE_CIPHER_MULTIPART
  #endif

  #if defined(PSA_WANT_ALG_OFB) && defined(MBEDTLS_PSA_ACCEL_ALG_OFB)
    #define SLI_PSA_DRIVER_FEATURE_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_BLOCK_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_AES_OFB
    #define SLI_PSA_DRIVER_FEATURE_CIPHER_MULTIPART
  #endif

  #if defined(PSA_WANT_ALG_CCM) && defined(MBEDTLS_PSA_ACCEL_ALG_CCM)
    #define SLI_PSA_DRIVER_FEATURE_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_BLOCK_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_AES_CCM_STAR_NO_TAG
    #define SLI_PSA_DRIVER_FEATURE_AES_CTR_VARIANT
    #define SLI_PSA_DRIVER_FEATURE_CIPHER_MULTIPART
  #endif

  #if defined(PSA_WANT_ALG_CBC_NO_PADDING) && defined(MBEDTLS_PSA_ACCEL_ALG_CBC_NO_PADDING)
    #define SLI_PSA_DRIVER_FEATURE_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_BLOCK_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_AES_CBC_NO_PADDING
    #define SLI_PSA_DRIVER_FEATURE_AES_CBC_VARIANT
    #define SLI_PSA_DRIVER_FEATURE_CIPHER_MULTIPART
  #endif

  #if defined(PSA_WANT_ALG_CBC_PKCS7) && defined(MBEDTLS_PSA_ACCEL_ALG_CBC_PKCS7)
    #define SLI_PSA_DRIVER_FEATURE_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_BLOCK_CIPHER
    #define SLI_PSA_DRIVER_FEATURE_AES_CBC_PKCS7
    #define SLI_PSA_DRIVER_FEATURE_AES_CBC_VARIANT
    #define SLI_PSA_DRIVER_FEATURE_CIPHER_MULTIPART
  #endif

#endif

#if defined(PSA_WANT_KEY_TYPE_CHACHA20) && defined(PSA_WANT_ALG_STREAM_CIPHER) \
  && defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_CHACHA20)
  #define SLI_PSA_DRIVER_FEATURE_CIPHER
  #define SLI_PSA_DRIVER_FEATURE_STREAM_CIPHER
  #define SLI_PSA_DRIVER_FEATURE_CHACHA20
  #define SLI_PSA_DRIVER_FEATURE_CIPHER_MULTIPART
#endif

// -------------------------------------
// Key derivation

#if defined(PSA_WANT_ALG_HKDF) && defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define SLI_PSA_DRIVER_FEATURE_KDF
  #define SLI_PSA_DRIVER_FEATURE_HKDF
#endif

#if defined(PSA_WANT_ALG_PBKDF2_HMAC) && defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define SLI_PSA_DRIVER_FEATURE_KDF
  #define SLI_PSA_DRIVER_FEATURE_PBKDF2
  #define SLI_PSA_DRIVER_FEATURE_PBKDF2_HMAC
#endif

#if defined(PSA_WANT_ALG_PBKDF2_AES_CMAC_PRF_128) && defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH) \
  && defined(SLI_MBEDTLS_DEVICE_HSE_V2)
  #define SLI_PSA_DRIVER_FEATURE_KDF
  #define SLI_PSA_DRIVER_FEATURE_PBKDF2
  #define SLI_PSA_DRIVER_FEATURE_PBKDF2_CMAC
#endif

#if defined(PSA_WANT_ALG_PBKDF2_AES_CMAC_PRF_128) && defined(SLI_PSA_DRIVER_FEATURE_PUF_KEY)
  #define SLI_PSA_DRIVER_FEATURE_KDF
  #define SLI_PSA_DRIVER_FEATURE_PBKDF2
  #define SLI_PSA_DRIVER_FEATURE_PBKDF2_CMAC
#endif

// -------------------------------------
// Hash

#if defined(PSA_WANT_ALG_SHA_1) && defined(MBEDTLS_PSA_ACCEL_ALG_SHA_1)
  #define SLI_PSA_DRIVER_FEATURE_HASH
  #define SLI_PSA_DRIVER_FEATURE_HASH_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_SHA1
  #define SLI_PSA_DRIVER_FEATURE_HASH_STATE_32
#endif

#if defined(PSA_WANT_ALG_SHA_224) && defined(MBEDTLS_PSA_ACCEL_ALG_SHA_224)
  #define SLI_PSA_DRIVER_FEATURE_HASH
  #define SLI_PSA_DRIVER_FEATURE_HASH_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_SHA224
  #define SLI_PSA_DRIVER_FEATURE_HASH_STATE_32
#endif

#if defined(PSA_WANT_ALG_SHA_256) && defined(MBEDTLS_PSA_ACCEL_ALG_SHA_256)
  #define SLI_PSA_DRIVER_FEATURE_HASH
  #define SLI_PSA_DRIVER_FEATURE_HASH_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_SHA256
  #define SLI_PSA_DRIVER_FEATURE_HASH_STATE_32
#endif

#if defined(PSA_WANT_ALG_SHA_384) && defined(MBEDTLS_PSA_ACCEL_ALG_SHA_384)
  #define SLI_PSA_DRIVER_FEATURE_HASH
  #define SLI_PSA_DRIVER_FEATURE_HASH_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_SHA384
  #define SLI_PSA_DRIVER_FEATURE_HASH_STATE_64
#endif

#if defined(PSA_WANT_ALG_SHA_512) && defined(MBEDTLS_PSA_ACCEL_ALG_SHA_512)
  #define SLI_PSA_DRIVER_FEATURE_HASH
  #define SLI_PSA_DRIVER_FEATURE_HASH_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_SHA512
  #define SLI_PSA_DRIVER_FEATURE_HASH_STATE_64
#endif

// -------------------------------------
// MAC

#if defined(PSA_WANT_ALG_HMAC) && defined(MBEDTLS_PSA_ACCEL_ALG_HMAC)
  #define SLI_PSA_DRIVER_FEATURE_MAC
  #define SLI_PSA_DRIVER_FEATURE_MAC_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_HMAC
#endif

#if defined(PSA_WANT_ALG_CMAC) && defined(MBEDTLS_PSA_ACCEL_ALG_CMAC)
  #define SLI_PSA_DRIVER_FEATURE_MAC
  #define SLI_PSA_DRIVER_FEATURE_MAC_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_CMAC
#endif

#if defined(PSA_WANT_ALG_CBC_MAC) && defined(MBEDTLS_PSA_ACCEL_ALG_CBC_MAC)
  #define SLI_PSA_DRIVER_FEATURE_MAC
  #define SLI_PSA_DRIVER_FEATURE_MAC_MULTIPART
  #define SLI_PSA_DRIVER_FEATURE_CBC_MAC
#endif

// -------------------------------------
// Elliptic curve cryptography

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_SECP_R1_192)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_SECPR1
  #define SLI_PSA_DRIVER_FEATURE_P192R1
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_SECP_R1_224)                 \
  && !defined(SLI_MBEDTLS_DEVICE_HSE_V1)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_SECPR1
  #define SLI_PSA_DRIVER_FEATURE_P224R1
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_SECP_R1_256)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_SECPR1
  #define SLI_PSA_DRIVER_FEATURE_P256R1
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_SECP_R1_384)                 \
  && defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_SECPR1
  #define SLI_PSA_DRIVER_FEATURE_P384R1
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_SECP_R1_521)                 \
  && defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_SECPR1
  #define SLI_PSA_DRIVER_FEATURE_P521R1
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_SECP_K1_256)                 \
  && defined(SLI_MBEDTLS_DEVICE_VSE)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_SECPK1
  #define SLI_PSA_DRIVER_FEATURE_P256K1
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_MONTGOMERY_255)              \
  && defined(SLI_MBEDTLS_DEVICE_HSE)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_MONTGOMERY
  #define SLI_PSA_DRIVER_FEATURE_CURVE25519
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_MONTGOMERY_448)              \
  && defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_MONTGOMERY
  #define SLI_PSA_DRIVER_FEATURE_CURVE448
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)     \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)   \
  || defined (PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) \
  || defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))        \
  && defined(PSA_WANT_ECC_TWISTED_EDWARDS_255)         \
  && defined(SLI_MBEDTLS_DEVICE_HSE)
  #define SLI_PSA_DRIVER_FEATURE_ECC
  #define SLI_PSA_DRIVER_FEATURE_EDWARDS
  #define SLI_PSA_DRIVER_FEATURE_EDWARDS25519
#endif

// -------------------------------------
// Key agreement

#if defined(PSA_WANT_ALG_ECDH) && defined(MBEDTLS_PSA_ACCEL_ALG_ECDH) \
  && defined(SLI_PSA_DRIVER_FEATURE_ECC)
  #define SLI_PSA_DRIVER_FEATURE_KEY_AGREEMENT
  #define SLI_PSA_DRIVER_FEATURE_ECDH
#endif

// -------------------------------------
// Signature

#if defined(PSA_WANT_ALG_ECDSA) && defined(MBEDTLS_PSA_ACCEL_ALG_ECDSA) \
  && (defined(SLI_PSA_DRIVER_FEATURE_SECPR1)                            \
  || defined(SLI_PSA_DRIVER_FEATURE_SECPK1))
  #define SLI_PSA_DRIVER_FEATURE_SIGNATURE
  #define SLI_PSA_DRIVER_FEATURE_ECDSA
#endif

#if defined(PSA_WANT_ALG_EDDSA) && defined(SLI_PSA_DRIVER_FEATURE_EDWARDS)
  #define SLI_PSA_DRIVER_FEATURE_SIGNATURE
  #define SLI_PSA_DRIVER_FEATURE_EDDSA
#endif

#endif // SLI_PSA_DRIVER_FEATURES_H

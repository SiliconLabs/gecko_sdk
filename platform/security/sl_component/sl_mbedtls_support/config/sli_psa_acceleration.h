/***************************************************************************//**
 * @file
 * @brief PSA Crypto device acceleration capabilities.
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

#ifndef SLI_PSA_ACCELERATION_H
#define SLI_PSA_ACCELERATION_H

// -------------------------------------
// Hash

#define MBEDTLS_PSA_ACCEL_ALG_SHA_1
#define MBEDTLS_PSA_ACCEL_ALG_SHA_224
#define MBEDTLS_PSA_ACCEL_ALG_SHA_256

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define MBEDTLS_PSA_ACCEL_ALG_SHA_384
  #define MBEDTLS_PSA_ACCEL_ALG_SHA_512
#endif

// -------------------------------------
// Cipher

#define MBEDTLS_PSA_ACCEL_KEY_TYPE_AES
#define MBEDTLS_PSA_ACCEL_ALG_ECB_NO_PADDING
#define MBEDTLS_PSA_ACCEL_ALG_CBC_NO_PADDING
#define MBEDTLS_PSA_ACCEL_ALG_CBC_PKCS7
#define MBEDTLS_PSA_ACCEL_ALG_CTR
#define MBEDTLS_PSA_ACCEL_ALG_CFB
#define MBEDTLS_PSA_ACCEL_ALG_OFB

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define MBEDTLS_PSA_ACCEL_KEY_TYPE_CHACHA20
#endif

// -------------------------------------
// AEAD

#define MBEDTLS_PSA_ACCEL_ALG_GCM
#define MBEDTLS_PSA_ACCEL_ALG_CCM

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define MBEDTLS_PSA_ACCEL_ALG_CHACHA20_POLY1305
#endif

// -------------------------------------
// MAC

#define MBEDTLS_PSA_ACCEL_ALG_CMAC

#if defined(SLI_MBEDTLS_DEVICE_S2)
  #define MBEDTLS_PSA_ACCEL_ALG_HMAC
#endif

#if defined(SLI_MBEDTLS_DEVICE_HSE_V1)
  #define MBEDTLS_PSA_ACCEL_ALG_CBC_MAC
#endif

// -------------------------------------
// Elliptic curves

#if defined(SLI_MBEDTLS_DEVICE_S2)
  #define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR
  #define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_PUBLIC_KEY
  #define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_192
  #define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_256
#endif

#if defined(SLI_MBEDTLS_DEVICE_S2) && !defined(SLI_MBEDTLS_DEVICE_HSE_V1)
  #define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_224
#endif

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_384
  #define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_521
#endif

#if defined(SLI_MBEDTLS_DEVICE_VSE)
  #define MBEDTLS_PSA_ACCEL_ECC_SECP_K1_256
#endif

#if defined(SLI_MBEDTLS_DEVICE_HSE_V1) && defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH) \
  || defined(SLI_MBEDTLS_DEVICE_HSE_V2)
  #define MBEDTLS_PSA_ACCEL_ECC_MONTGOMERY_255
#endif

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define MBEDTLS_PSA_ACCEL_ECC_MONTGOMERY_448
#endif

#if defined(SLI_MBEDTLS_DEVICE_HSE_V1) && defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH) \
  || defined(SLI_MBEDTLS_DEVICE_HSE_V2)
  #define MBEDTLS_PSA_ACCEL_ECC_MONTGOMERY_255
#endif

#if defined(SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH)
  #define MBEDTLS_PSA_ACCEL_ECC_MONTGOMERY_448
#endif

// -------------------------------------
// Key agreement

#if defined(SLI_MBEDTLS_DEVICE_S2)
  #define MBEDTLS_PSA_ACCEL_ALG_ECDH
#endif

// -------------------------------------
// Signature

#if defined(SLI_MBEDTLS_DEVICE_S2)
  #define MBEDTLS_PSA_ACCEL_ALG_ECDSA
#endif

#endif // SLI_PSA_ACCELERATION_H

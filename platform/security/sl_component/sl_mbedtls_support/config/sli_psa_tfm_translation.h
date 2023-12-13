/***************************************************************************//**
 * @file
 * @brief PSA Crypto to TFM config option translation.
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

#ifndef SLI_PSA_TFM_TRANSLATION_H
#define SLI_PSA_TFM_TRANSLATION_H

// Asymmetric Crypt module (RSA is not supported)
#define TFM_CRYPTO_ASYM_ENCRYPT_MODULE_DISABLED

// HASH module
#if !defined(PSA_WANT_ALG_SHA_1)    \
  && !defined(PSA_WANT_ALG_SHA_224) \
  && !defined(PSA_WANT_ALG_SHA_256) \
  && !defined(PSA_WANT_ALG_SHA_384) \
  && !defined(PSA_WANT_ALG_SHA_512) \
  && !defined(PSA_WANT_ALG_MD5)
  #define TFM_CRYPTO_HASH_MODULE_DISABLED
#endif

// AEAD module
#if !defined(PSA_WANT_ALG_CCM)  \
  && !defined(PSA_WANT_ALG_GCM) \
  && !defined(PSA_WANT_ALG_CHACHA20_POLY1305)
  #define TFM_CRYPTO_AEAD_MODULE_DISABLED
#endif

// Asymmetric Sign module
#if !defined(PSA_WANT_ALG_ECDSA)  \
  && !defined(PSA_WANT_ALG_EDDSA) \
  && !defined(PSA_WANT_ALG_DETERMINISTIC_ECDSA)
  #define TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED
#endif

// Cipher module
#if !defined(PSA_WANT_ALG_CFB)             \
  && !defined(PSA_WANT_ALG_CTR)            \
  && !defined(PSA_WANT_ALG_CBC_NO_PADDING) \
  && !defined(PSA_WANT_ALG_CBC_PKCS7)      \
  && !defined(PSA_WANT_ALG_ECB_NO_PADDING) \
  && !defined(PSA_WANT_ALG_XTS)            \
  && !defined(PSA_WANT_ALG_OFB)            \
  && !defined(PSA_WANT_ALG_STREAM_CIPHER)
  #define TFM_CRYPTO_CIPHER_MODULE_DISABLED
#endif

// MAC module
#if !defined(PSA_WANT_ALG_HMAC)  \
  && !defined(PSA_WANT_ALG_CMAC) \
  && !defined(PSA_WANT_ALG_CBC_MAC)
  #define TFM_CRYPTO_MAC_MODULE_DISABLED
#endif

// Key derivation module
#if !defined(PSA_WANT_ALG_PBKDF2_HMAC)              \
  && !defined(PSA_WANT_ALG_HKDF)                    \
  && !defined(PSA_WANT_ALG_PBKDF2_AES_CMAC_PRF_128) \
  && !defined(PSA_WANT_ALG_TLS12_PRF)               \
  && !defined(PSA_WANT_ALG_TLS12_PSK_TO_MS)         \
  && !defined(PSA_WANT_ALG_ECDH)
  #define TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
#endif

// PAKE module
#if !defined(PSA_WANT_ALG_JPAKE)
  #define TFM_CRYPTO_PAKE_MODULE_DISABLED
#endif

#endif // SLI_PSA_TFM_TRANSLATION_H

/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Transparent Driver API Types for CRYPTOACC.
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
#ifndef SLI_CRYPTOACC_TRANSPARENT_TYPES_H
#define SLI_CRYPTOACC_TRANSPARENT_TYPES_H

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

/***************************************************************************//**
 * \addtogroup sl_psa_drivers
 * \{
 ******************************************************************************/

/***************************************************************************//**
 * \addtogroup sl_psa_drivers_cryptoacc
 * \{
 ******************************************************************************/

#include "em_device.h"

#if defined(CRYPTOACC_PRESENT)

#include "sx_hash.h"
#include "sx_aes.h"
// Replace inclusion of crypto_driver_common.h with the new psa driver interface
// header file when it becomes available.
#include "psa/crypto_driver_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  sx_hash_fct_t hash_type;            ///< Hash type
  uint32_t total;                     ///< Number of bytes processed
  uint8_t state[32];                  ///< Intermediate digest state
  uint8_t buffer[64];                 ///< Data block being processed
} sli_cryptoacc_transparent_hash_operation_t;

typedef struct {
  sx_aes_mode_t direction;            ///< Cipher direction (encrypt/decrypt)
  psa_algorithm_t alg;                ///< Algorithm (cipher and mode of operation)
  uint8_t key[32];                    ///< Key buffer
  size_t key_len;                     ///< Length of key in bytes
  uint8_t iv[16];                     ///< IV buffer
  size_t iv_len;                      ///< Length of IV in bytes
  uint8_t streaming_block[16];        ///< Buffer for intermediate results
  size_t processed_length;            ///< Number of bytes processed
} sli_cryptoacc_transparent_cipher_operation_t;

typedef union {
  struct {
    psa_algorithm_t alg;                    ///< MAC type
    uint8_t key[32];                        ///< key buffer
    size_t  key_len;                        ///< key length
    uint8_t current_block[16];              ///< current and potentially last block
    size_t  current_block_len;              ///< current number of bytes in current block
    uint8_t cmac_ctx[BLK_CIPHER_CTX_SIZE];  ///< CMAC state context
  } cipher_mac;
  #if defined(PSA_WANT_ALG_HMAC)
  struct {
    psa_algorithm_t alg;                    ///< HMAC type
    sli_cryptoacc_transparent_hash_operation_t hash_ctx;  ///< Hash context for multipart HMAC
    uint8_t opad[64];                       ///< opad for use during finalisation
  } hmac;
  #endif
} sli_cryptoacc_transparent_mac_operation_t;

typedef struct { // Will possibly require an update once multi-part is implemented.
  sx_aes_mode_t direction;
  size_t ad_length;
  size_t pt_length;
  uint8_t nonce[16];
  size_t nonce_length;
} sli_cryptoacc_transparent_aead_preinit_t;

typedef struct { // Will possibly require an update once multi-part is implemented.
  psa_algorithm_t alg;
  uint8_t key[32];
  size_t key_len;
  size_t ad_len;
  size_t pt_len;
  union {
    sli_cryptoacc_transparent_aead_preinit_t preinit;
  } ctx;
} sli_cryptoacc_transparent_aead_operation_t;

#ifdef __cplusplus
}
#endif

#endif // CRYPTOACC_PRESENT

/** \} (end addtogroup sl_psa_drivers_cryptoacc) */
/** \} (end addtogroup sl_psa_drivers) */

/// @endcond

#endif // SLI_CRYPTOACC_TRANSPARENT_TYPES_H

/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto common driver functions.
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

#ifndef SLI_PSA_DRIVER_COMMON_H
#define SLI_PSA_DRIVER_COMMON_H

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#include "psa/crypto.h"

#include <stddef.h>

// -----------------------------------------------------------------------------
// Static inline functions

/*******************************************************************************
 * @brief
 *   Validate that a elliptic curve (in Weierstrass form) private key is valid.
 *   This fuction attempts to operate in constant time.
 *
 * @param[in] privkey
 *   A buffer containing the private key.
 *
 * @param padding_bytes
 *   A buffer containing the modulus (n) to compare the private key against.
 *
 * @return
 *   PSA_SUCCESS if the key is in [1, n-1], PSA_ERROR_INVALID_ARGUMENT otherwise.
 ******************************************************************************/
static inline psa_status_t sli_psa_validate_ecc_weierstrass_privkey(
  const void *privkey,
  const void *modulus,
  size_t privkey_size)
{
  // Compare private key to maximum allowed value, n - 1,
  // and also check that it is non-zero.

  // Initial values.
  uint8_t non_zero_accumulator = 0;
  int32_t memcmp_res = 0;
  int32_t diff = 0;

  // Loop over every byte in the private key. We start from the end so that
  // the final result we store reflects the first byte which differs between the
  // two numbers (privkey and modulus).
  for (size_t i = 0; i < privkey_size; ++i) {
    // Partial non-zero check operation.
    non_zero_accumulator |= ((uint8_t *)privkey)[privkey_size - 1 - i];

    // Compute the difference between the current bytes being compared.
    diff = ((uint8_t *)privkey)[privkey_size - 1 - i]
           - ((uint8_t *)modulus)[privkey_size - 1 - i];

    // This will only update memcmp_res if the difference is non-zero.
    memcmp_res = (memcmp_res & - !diff) | diff;
  }

  if ((non_zero_accumulator == 0) || (memcmp_res >= 0)) {
    // We have either failed because the private key turned out to be empty,
    // or because the result of the memcmp indicated that the privkey was not
    // smaller than the modulus.
    return PSA_ERROR_INVALID_ARGUMENT;
  } else {
    return PSA_SUCCESS;
  }
}

/***************************************************************************//**
 * @brief
 *   Clear a memory location in a way that is guaranteed not be optimized away
 *   by the compiler.
 *
 * @param[in]  v
 *   Pointer to memory location.
 *
 * @param[in] n
 *   Number of bytes to clear.
 ******************************************************************************/
static inline psa_status_t sli_psa_zeroize(void *v, size_t n)
{
  if (n == 0) {
    return PSA_SUCCESS;
  }

  volatile unsigned char *p = v;
  while (n--) {
    *p++ = 0;
  }
  return PSA_SUCCESS;
}

/***************************************************************************//**
 * @brief
 *   Perform a memcmp() in 'constant time'.
 *
 * @param[in]  a
 *   Pointer to the first memory location.
 *
 * @param[in]  a
 *   Pointer to the second memory location.
 *
 * @param[in] n
 *   Number of bytes to compare between the two memory locations.
 *
 * @return
 *   Zero if the buffer contents are equal, non-zero otherwise.
 ******************************************************************************/
static inline uint8_t sli_psa_safer_memcmp(const uint8_t *a,
                                           const uint8_t *b,
                                           size_t n)
{
  uint8_t diff = 0u;

  for (size_t i = 0; i < n; i++) {
    diff |= a[i] ^ b[i];
  }

  return diff;
}

// -----------------------------------------------------------------------------
// Function declarations

/*******************************************************************************
 * @brief
 *   Validate the PKCS#7 padding contained in the final block of plaintext
 *   in certain block cipher modes of operation. Based on the get_pkcs_padding()
 *   implementation in Mbed TLS.
 *
 * @param[in] padded_data
 *   A buffer of (at least) size 16 containing the padded final block.
 *
 * @param padded_data_length
 *   The length of the paddad data (should be 16). Parameter is mainly kept used
 *   in order to make it harder for the compiler to optimize out some of the
 *   "time-constantness".
 *
 * @param[out] padding_bytes
 *   The amount of padding bytes that the data contains.

 *
 * @return
 *   PSA_SUCCESS if the padding is valid, PSA_ERROR_INVALID_PADDING otherwise.
 ******************************************************************************/
psa_status_t sli_psa_validate_pkcs7_padding(uint8_t *padded_data,
                                            size_t padded_data_length,
                                            size_t *padding_bytes);

/**
 * \brief Initialize Galois field (2^128) multiplication table
 *
 * This function is used as part of a software-based GHASH (as defined in
 * AES-GCM) algorithm, and originates from the mbed TLS implementation in gcm.c
 *
 * It takes the in the 'H' value for the GHASH operation (which is a block of
 * zeroes encrypted using AES-ECB with the key to be used for GHASH/GCM), and
 * converts it into a multiplication table for later use by the multiplication
 * function.
 *
 * \param[in] Ek  'H' value for which to create the multiplication tables
 * \param[out] HL Lower multiplication table for 'H'
 * \param[out] HH Upper multiplication table for 'H'
 */
void sli_psa_software_ghash_setup(const uint8_t Ek[16],
                                  uint64_t HL[16],
                                  uint64_t HH[16]);

/**
 * \brief Galois field (2^128) multiplication operation
 *
 * This function is used as part of a software-based GHASH (as defined in
 * AES-GCM) algorithm, and originates from the mbed TLS implementation in gcm.c
 *
 * This function takes in a 128-bit scalar and multiplies it with H (Galois
 * field multiplication as defined in AES-GCM). H is not provided to this
 * function directly. Instead, multiplication tables for the specific H need to
 * be calculated first by \ref sli_psa_software_ghash_setup, and passed to this
 * function.
 *
 * \param[in]   HL      Lower multiplication table for 'H'
 * \param[in]   HH      Upper multiplication table for 'H'
 * \param[out]  output  Output buffer for the multiplication result
 * \param[in]   input   Input buffer for the scalar to multiply
 */
void sli_psa_software_ghash_multiply(const uint64_t HL[16],
                                     const uint64_t HH[16],
                                     uint8_t output[16],
                                     const uint8_t input[16]);

#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT) \
  && !defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)

// Declare the TRNG function prototype if it's not already declared by PSA
psa_status_t mbedtls_psa_external_get_random(void *context,
                                             uint8_t *output,
                                             size_t output_size,
                                             size_t *output_length);

#endif // MBEDTLS_ENTROPY_HARDWARE_ALT && MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG

/// @endcond

#endif // SLI_PSA_DRIVER_COMMON_H

/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone non-secure workarund.
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

#include "psa/crypto.h"
#include "psa/crypto_extra.h"
#include "mbedtls/build_info.h"

#if defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY)

psa_ecc_family_t mbedtls_ecc_group_to_psa(mbedtls_ecp_group_id grpid,
                                          size_t *bits)
{
  switch (grpid) {
    case MBEDTLS_ECP_DP_SECP192R1:
      *bits = 192;
      return PSA_ECC_FAMILY_SECP_R1;
    case MBEDTLS_ECP_DP_SECP224R1:
      *bits = 224;
      return PSA_ECC_FAMILY_SECP_R1;
    case MBEDTLS_ECP_DP_SECP256R1:
      *bits = 256;
      return PSA_ECC_FAMILY_SECP_R1;
    case MBEDTLS_ECP_DP_SECP384R1:
      *bits = 384;
      return PSA_ECC_FAMILY_SECP_R1;
    case MBEDTLS_ECP_DP_SECP521R1:
      *bits = 521;
      return PSA_ECC_FAMILY_SECP_R1;
    case MBEDTLS_ECP_DP_BP256R1:
      *bits = 256;
      return PSA_ECC_FAMILY_BRAINPOOL_P_R1;
    case MBEDTLS_ECP_DP_BP384R1:
      *bits = 384;
      return PSA_ECC_FAMILY_BRAINPOOL_P_R1;
    case MBEDTLS_ECP_DP_BP512R1:
      *bits = 512;
      return PSA_ECC_FAMILY_BRAINPOOL_P_R1;
    case MBEDTLS_ECP_DP_CURVE25519:
      *bits = 255;
      return PSA_ECC_FAMILY_MONTGOMERY;
    case MBEDTLS_ECP_DP_SECP192K1:
      *bits = 192;
      return PSA_ECC_FAMILY_SECP_K1;
    case MBEDTLS_ECP_DP_SECP224K1:
      *bits = 224;
      return PSA_ECC_FAMILY_SECP_K1;
    case MBEDTLS_ECP_DP_SECP256K1:
      *bits = 256;
      return PSA_ECC_FAMILY_SECP_K1;
    case MBEDTLS_ECP_DP_CURVE448:
      *bits = 448;
      return PSA_ECC_FAMILY_MONTGOMERY;
    default:
      *bits = 0;
      return 0;
  }
}

mbedtls_ecp_group_id mbedtls_ecc_group_of_psa(psa_ecc_family_t curve,
                                              size_t bits,
                                              int bits_is_sloppy)
{
  switch (curve) {
    case PSA_ECC_FAMILY_SECP_R1:
      switch (bits) {
#if defined(PSA_WANT_ECC_SECP_R1_192)
        case 192:
          return MBEDTLS_ECP_DP_SECP192R1;
#endif
#if defined(PSA_WANT_ECC_SECP_R1_224)
        case 224:
          return MBEDTLS_ECP_DP_SECP224R1;
#endif
#if defined(PSA_WANT_ECC_SECP_R1_256)
        case 256:
          return MBEDTLS_ECP_DP_SECP256R1;
#endif
#if defined(PSA_WANT_ECC_SECP_R1_384)
        case 384:
          return MBEDTLS_ECP_DP_SECP384R1;
#endif
#if defined(PSA_WANT_ECC_SECP_R1_521)
        case 521:
          return MBEDTLS_ECP_DP_SECP521R1;
        case 528:
          if (bits_is_sloppy) {
            return MBEDTLS_ECP_DP_SECP521R1;
          }
          break;
#endif
      }
      break;

    case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
      switch (bits) {
#if defined(PSA_WANT_ECC_BRAINPOOL_P_R1_256)
        case 256:
          return MBEDTLS_ECP_DP_BP256R1;
#endif
#if defined(PSA_WANT_ECC_BRAINPOOL_P_R1_384)
        case 384:
          return MBEDTLS_ECP_DP_BP384R1;
#endif
#if defined(PSA_WANT_ECC_BRAINPOOL_P_R1_512)
        case 512:
          return MBEDTLS_ECP_DP_BP512R1;
#endif
      }
      break;

    case PSA_ECC_FAMILY_MONTGOMERY:
      switch (bits) {
#if defined(PSA_WANT_ECC_MONTGOMERY_255)
        case 255:
          return MBEDTLS_ECP_DP_CURVE25519;
        case 256:
          if (bits_is_sloppy) {
            return MBEDTLS_ECP_DP_CURVE25519;
          }
          break;
#endif
#if defined(PSA_WANT_ECC_MONTGOMERY_448)
        case 448:
          return MBEDTLS_ECP_DP_CURVE448;
#endif
      }
      break;

    case PSA_ECC_FAMILY_SECP_K1:
      switch (bits) {
#if defined(PSA_WANT_ECC_SECP_K1_192)
        case 192:
          return MBEDTLS_ECP_DP_SECP192K1;
#endif
#if defined(PSA_WANT_ECC_SECP_K1_224)
        case 224:
          return MBEDTLS_ECP_DP_SECP224K1;
#endif
#if defined(PSA_WANT_ECC_SECP_K1_256)
        case 256:
          return MBEDTLS_ECP_DP_SECP256K1;
#endif
      }
      break;
  }

  (void) bits_is_sloppy;
  return MBEDTLS_ECP_DP_NONE;
}

#endif /* PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY */

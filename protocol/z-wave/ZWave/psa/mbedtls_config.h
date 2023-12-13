/***************************************************************************//**
 * @brief  Configuration for enabling CRYPTO hardware acceleration required for
 *         Z-Wave.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H
#include "em_device.h"

/* Setting this will enable polling
 * of TRNG (or radio) during seeding.
 * In our case we would like to use
 * TRNG on secure vault devices.
 **
  #define MBEDTLS_ENTROPY_HARDWARE_ALT
  #define MBEDTLS_ENTROPY_FORCE_SHA256
 */

#define MBEDTLS_CIPHER_C
#define MBEDTLS_SHA1_ALT
#define MBEDTLS_PSA_CRYPTO_C
#define MBEDTLS_USE_PSA_CRYPTO
#define MBEDTLS_PSA_CRYPTO_CONFIG
#define MBEDTLS_PSA_CRYPTO_DRIVERS
#define MBEDTLS_PSA_CRYPTO_STORAGE_C
#define MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS

/* Set these for enabling mutex usage , including
 for the CTR-DRBG context and SE mailbox access.
 */
#define MBEDTLS_THREADING_C
#define MBEDTLS_THREADING_ALT

/* Set this for CTR_CRBG (and disable TRNG related defs)
#define MBEDTLS_CTR_DRBG_C
*/

#if !defined(NO_CRYPTO_ACCELERATION)
#include "sli_mbedtls_omnipresent.h"
#include "sli_mbedtls_acceleration.h"
#endif /* NO_CRYPTO_ACCELERATION */

#include <stddef.h>

extern void vPortFree (void *pv);
extern void *pvCalloc (size_t xNumElements, size_t xSize);

#define MBEDTLS_PLATFORM_FREE_MACRO    vPortFree
#define MBEDTLS_PLATFORM_CALLOC_MACRO  pvCalloc

#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_PLATFORM_C

#include "mbedtls/config_psa.h"
#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */

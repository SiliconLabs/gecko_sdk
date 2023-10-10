/***************************************************************************//**
 * @file
 * @brief Mbed TLS 'omnipresent' config content.
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

#ifndef SLI_MBEDTLS_OMIPRESENT_H
#define SLI_MBEDTLS_OMIPRESENT_H

#if defined(SL_COMPONENT_CATALOG_PRESENT)
  #include "sl_component_catalog.h"
#endif

#if !defined(SL_CATALOG_SE_CPC_PRIMARY_PRESENT)
  #include "em_device.h"
#endif

// -----------------------------------------------------------------------------
// Non-volatile seed function headers

#if defined(MBEDTLS_PLATFORM_NV_SEED_ALT)

// Provide the NV seed function signatures since we have no specific header
// for them.

#include <stddef.h>

int sli_nv_seed_read(unsigned char *buf, size_t buf_len);
int sli_nv_seed_write(unsigned char *buf, size_t buf_len);

#endif // MBEDTLS_PLATFORM_NV_SEED_ALT

// -----------------------------------------------------------------------------
// Platform macros

#if defined(MBEDTLS_PLATFORM_CALLOC_MACRO) && defined(MBEDTLS_PLATFORM_FREE_MACRO)

// By default MBEDTLS_PLATFORM_CALLOC_MACRO and MBEDTLS_PLATFORM_FREE_MACRO are
// defined in mbedtls_platform_dynamic_memory_allocation_config_default.slcc.
// Alternative implementations can configure MBEDTLS_PLATFORM_CALLOC_MACRO and
// MBEDTLS_PLATFORM_FREE_MACRO to use other platform specific implementations.
// Alternatively some use cases may select runtime initialisation in the
// application by explicitly calling mbedtls_platform_set_calloc_free() by
// selecting mbedtls_platform_dynamic_memory_allocation_config_init_runtime.

#include <stddef.h>

extern void *MBEDTLS_PLATFORM_CALLOC_MACRO(size_t n, size_t size);
extern void MBEDTLS_PLATFORM_FREE_MACRO(void *ptr);

#endif // MBEDTLS_PLATFORM_CALLOC_MACRO && MBEDTLS_PLATFORM_FREE_MACRO

// -----------------------------------------------------------------------------
// Device differentiation logic

#if defined(CRYPTO_PRESENT)

  #define SLI_MBEDTLS_DEVICE_S1

  #if !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_95)
    #define SLI_MBEDTLS_DEVICE_S1_WITH_TRNG
  #endif

  #if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_89)
// The TRNG may possibly not work depending on the die revision.
    #define SLI_MBEDTLS_DEVICE_S1_WITH_TRNG_ERRATA
  #endif

#elif defined(SEMAILBOX_PRESENT)

  #define SLI_MBEDTLS_DEVICE_S2
  #define SLI_MBEDTLS_DEVICE_HSE

  #if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
    #define SLI_MBEDTLS_DEVICE_SE_V1
    #define SLI_MBEDTLS_DEVICE_HSE_V1
  #else
    #define SLI_MBEDTLS_DEVICE_SE_V2
    #define SLI_MBEDTLS_DEVICE_HSE_V2
  #endif

  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    #define SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH
  #else
    #define SLI_MBEDTLS_DEVICE_HSE_VAULT_MID
  #endif

#elif defined(CRYPTOACC_PRESENT)

  #define SLI_MBEDTLS_DEVICE_S2
  #define SLI_MBEDTLS_DEVICE_VSE

  #if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
    #define SLI_MBEDTLS_DEVICE_SE_V1
    #define SLI_MBEDTLS_DEVICE_VSE_V1
  #else
    #define SLI_MBEDTLS_DEVICE_SE_V2
    #define SLI_MBEDTLS_DEVICE_VSE_V2
  #endif

#elif defined(SL_CATALOG_SE_CPC_PRIMARY_PRESENT)

  #define SLI_MBEDTLS_DEVICE_S2
  #define SLI_MBEDTLS_DEVICE_HSE

// #define SLI_MBEDTLS_DEVICE_SE_V1
// #define SLI_MBEDTLS_DEVICE_SE_V2
// #define SLI_MBEDTLS_DEVICE_HSE_V1
// #define SLI_MBEDTLS_DEVICE_HSE_V2
// #define SLI_MBEDTLS_DEVICE_HSE_VAULT_HIGH
// #define SLI_MBEDTLS_DEVICE_HSE_VAULT_MID

#elif defined(SLI_CRYPTOACC_PRESENT_SI91X)
  #define SLI_MBEDTLS_DEVICE_SI91X
#endif

#endif // SLI_MBEDTLS_OMIPRESENT_H

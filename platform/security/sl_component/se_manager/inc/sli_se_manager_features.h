/***************************************************************************//**
 * @file
 * @brief Silicon Labs SE Manager macros representing features.
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

#ifndef SLI_SE_MANAGER_FEATURES_H
#define SLI_SE_MANAGER_FEATURES_H

#if !defined(__linux__)
  #include "em_device.h"
#endif // !__linux__

#if defined(DOXYGEN)

#undef _SILICON_LABS_SECURITY_FEATURE // Allow doxygen to include the SVH only features

#define _SILICON_LABS_SECURITY_FEATURE _SILICON_LABS_SECURITY_FEATURE_VAULT
#define SLI_MAILBOX_COMMAND_SUPPORTED
#define SLI_VSE_MAILBOX_COMMAND_SUPPORTED
#define SL_SE_MANAGER_YIELD_WHILE_WAITING_FOR_COMMAND_COMPLETION
#define SLI_SE_COMMAND_STATUS_READ_RSTCAUSE_AVAILABLE
#define SLI_SE_COMMAND_READ_TAMPER_RESET_CAUSE_AVAILABLE
#define SLI_SE_COMMAND_DERIVE_KEY_PBKDF2_CMAC_AVAILABLE

#else // DOXYGEN

#if defined(__linux__)
// ---------------------------- HOST ---------------------------- //

// The header is being used on a host system with Linux running on it,
// assume that the endpoint attached to the host system is a SVH type.

#define SLI_SE_MANAGER_HOST_SYSTEM
#define SLI_MAILBOX_COMMAND_SUPPORTED

#define _SILICON_LABS_SECURITY_FEATURE_SE    (0)
#define _SILICON_LABS_SECURITY_FEATURE_VAULT (1)
#define _SILICON_LABS_SECURITY_FEATURE_ROT   (2)
#define _SILICON_LABS_SECURITY_FEATURE       _SILICON_LABS_SECURITY_FEATURE_VAULT

#define SLI_SE_COMMAND_READ_TAMPER_RESET_CAUSE_AVAILABLE

#if defined(SLI_SE_MAJOR_VERSION_ONE)
  #define SLI_SE_COMMAND_STATUS_READ_RSTCAUSE_AVAILABLE

// EFR32xG23+ doesn't require padding of curve elements or other keys
  #define SLI_SE_KEY_PADDING_REQUIRED
  #define SLI_SE_P521_PADDING_BYTES (2u)

  #define SLI_MINIMUM_REQUIRED_NUMBER_PARAMS (0u)
#elif defined(SLI_SE_MAJOR_VERSION_TWO)
  #define SLI_SE_P521_PADDING_BYTES (0u)
// PBKDF2 with CMAC as the PRF was first supported on EFR32xG23.
  #define SLI_SE_COMMAND_DERIVE_KEY_PBKDF2_CMAC_AVAILABLE
  #define SLI_MINIMUM_REQUIRED_NUMBER_PARAMS (1u)
#endif

// Define the helper macros needed for the host system
#define __REV(num) (((num & 0xFF000000) >> 24)  \
                    | ((num & 0x00FF0000) >> 8) \
                    | ((num & 0x0000FF00) << 8) \
                    | ((num & 0x000000FF) << 24))

#elif defined(SEMAILBOX_PRESENT)
// --------------------------------- HSE --------------------------------- //

#define SLI_MAILBOX_COMMAND_SUPPORTED

#if (defined(_SILICON_LABS_SECURITY_FEATURE)                                  \
  && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) \
  && (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3))
// Reading the latest cached tamper reset cause requires SE version 2.2.1 or above.
  #define SLI_SE_COMMAND_READ_TAMPER_RESET_CAUSE_AVAILABLE
// The option to keep the tamper alive during sleep is only configurable for SE with major version 2
  #define SLI_SE_TAMPER_FLAG_KEEP_TAMPER_ALIVE_AVAILABLE
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
  #define SLI_SE_MAJOR_VERSION_ONE
#else
  #define SLI_SE_MAJOR_VERSION_TWO
#endif

#if defined(SLI_SE_MAJOR_VERSION_ONE)
  #define SLI_SE_COMMAND_STATUS_READ_RSTCAUSE_AVAILABLE

// EFR32xG23+ doesn't require padding of curve elements or other keys
  #define SLI_SE_KEY_PADDING_REQUIRED
  #define SLI_SE_P521_PADDING_BYTES (2u)

  #define SLI_MINIMUM_REQUIRED_NUMBER_PARAMS (0u)
#elif defined(SLI_SE_MAJOR_VERSION_TWO)
  #define SLI_SE_P521_PADDING_BYTES (0u)
// PBKDF2 with CMAC as the PRF was first supported on EFR32xG23.
  #define SLI_SE_COMMAND_DERIVE_KEY_PBKDF2_CMAC_AVAILABLE
  #define SLI_MINIMUM_REQUIRED_NUMBER_PARAMS (1u)
#endif

#elif defined(CRYPTOACC_PRESENT)
// --------------------------------- VSE --------------------------------- //

#define SLI_VSE_MAILBOX_COMMAND_SUPPORTED

#endif // __linux__

#endif // DOXYGEN

#endif // SLI_SE_MANAGER_FEATURES_H

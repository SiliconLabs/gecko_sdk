/***************************************************************************//**
 * @file
 * @brief ESL Tag Core component configuration macros
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
#ifndef EAD_CORE_CONFIG_H
#define EAD_CORE_CONFIG_H

#define SL_BT_EAD_CORE_USE_PSA_ACC  0

#define SL_BT_EAD_CORE_USE_RADIOAES 1

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Encrypted Advertiser Core configuration

// <o SL_BT_EAD_CORE_ACCELERATOR> Cryptographic engine
// <SL_BT_EAD_CORE_USE_PSA_ACC=> PSA Crypto
// <SL_BT_EAD_CORE_USE_RADIOAES=> Radio AES
// <i> Select cryptography accelerator type to use
// <i> Radio AES is highly experimental and therefore not recommended!
// <i> Default: PSA Crypto
#define SL_BT_EAD_CORE_ACCELERATOR                  SL_BT_EAD_CORE_USE_PSA_ACC
// </h>

// <<< end of configuration section >>>

#endif // EAD_CORE_CONFIG_H

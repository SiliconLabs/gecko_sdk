/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone configuration of peripheral secure attributes.
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

#ifndef SL_TRUSTZONE_SECURE_CONFIG_H
#define SL_TRUSTZONE_SECURE_CONFIG_H

#include "em_device.h"

#if defined(BOOTLOADER_APPLOADER)
#define SL_TRUSTZONE_PERIPHERAL_CMU_S (0)

#define SL_TRUSTZONE_PERIPHERAL_GPIO_S (0)
#endif // BOOTLOADER_APPLOADER

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5)
#define SL_TRUSTZONE_PERIPHERAL_GPIO_S (0)
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG_5

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_8)
#define SL_TRUSTZONE_PERIPHERAL_GPIO_S (0)
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG_8

#endif // SL_TRUSTZONE_SECURE_CONFIG_H

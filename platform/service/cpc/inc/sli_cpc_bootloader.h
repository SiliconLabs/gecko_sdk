/***************************************************************************/ /**
 * @file
 * @brief CPC Supported Bootloader
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

#ifndef SLI_CPC_BOOTLOADER_H
#define SLI_CPC_BOOTLOADER_H

#include <stdint.h>

#include "sl_enum.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if (defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT))
#include "btl_interface.h"
#elif (defined(SL_CATALOG_EMBER_BOOTLOADER_PRESENT))
#include "ember_btl_interface.h"

#define BOOTLOADER_RESET_REASON_GO        EMBER_BOOTLOADER_RESET_REASON_GO
#define BOOTLOADER_RESET_REASON_BOOTLOAD  EMBER_BOOTLOADER_RESET_REASON_BOOTLOAD
#define BOOTLOADER_RESET_SIGNATURE_VALID  EMBER_BOOTLOADER_RESET_SIGNATURE_VALID
#endif

#if (defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT) || defined(SL_CATALOG_EMBER_BOOTLOADER_PRESENT))
#define SL_CPC_HAS_BOOTLOADER_SUPPORT
#endif

SL_ENUM(sl_cpc_bootloader_t) {
  SL_CPC_BOOTLOADER_NONE                = 0,
  SL_CPC_BOOTLOADER_EMBER_APPLICATION   = 1,
  SL_CPC_BOOTLOADER_EMBER_STANDALONE    = 2,
  SL_CPC_BOOTLOADER_GECKO               = 3,
  SL_CPC_BOOTLOADER_UNKNOWN             = 4,
};

#endif // SLI_CPC_BOOTLOADER_H

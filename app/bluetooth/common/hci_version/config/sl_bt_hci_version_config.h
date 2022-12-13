/***************************************************************************//**
 * @file
 * @brief Bluetooth Version Specific Command Configuration
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

#ifndef SL_BT_HCI_VERSION_CONFIG_H
#define SL_BT_HCI_VERSION_CONFIG_H
#include <stdint.h>
#include "sl_bt_version.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth Version Vendor Specific API Configuration

// <o SL_BT_HCI_GET_VERSION_OPCODE> Opcode for vendor specific get version command <f.h>
// <d> 0xff10
// <i> Defines opcode that is used to identify Get Version command.
// <i> this must be chosen that it doesn't overlap with any other vendor specific command
// <i> Does take any parameters, will return version information as a parameter
#define SL_BT_HCI_GET_VERSION_OPCODE     0xff10

// </h> Bluetooth Version Vendor Specific API Configuration

// <<< end of configuration section >>>

// Structure that is returned in hci command complete event
struct sli_bt_hci_version_response{
  uint16_t major;
  uint16_t minor;
  uint16_t patch;
  uint16_t build;
};

#define SL_BT_HCI_VERSION_RESPONSE { BG_VERSION_MAJOR, BG_VERSION_MINOR, BG_VERSION_PATCH, BG_VERSION_BUILD }

#endif //SL_BT_HCI_VERSION_CONFIG_H

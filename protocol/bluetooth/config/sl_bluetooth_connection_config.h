/***************************************************************************//**
 * @file
 * @brief Bluetooth Connection configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in a
 *    product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_BT_CONNECTION_CONFIG_H
#define SL_BT_CONNECTION_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <o SL_BT_CONFIG_MAX_CONNECTIONS> Max number of connections reserved for user <0-32>
// <i> Default: 4
// <i> Define the number of connections the application needs.
#define SL_BT_CONFIG_MAX_CONNECTIONS     (4)

// <o SL_BT_CONFIG_CONNECTION_DATA_LENGTH> Preferred maximum TX payload octets <27-251>
// <i> Default: 251
// <i> Define the preferred maximum TX payload octets that will be used on connections.
// <i> This value is set to the controller as the default suggested data length when
// <i> Bluetooth stack is started.
#define SL_BT_CONFIG_CONNECTION_DATA_LENGTH     (251)

// <<< end of configuration section >>>
#endif

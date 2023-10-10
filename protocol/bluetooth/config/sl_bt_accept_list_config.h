/***************************************************************************//**
 * @file
 * @brief Bluetooth Accept List configuration
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

#ifndef SL_BT_ACCEPT_LIST_CONFIG_H
#define SL_BT_ACCEPT_LIST_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth Controller Configuration

// <o SL_BT_CONFIG_ACCEPT_LIST_SIZE> Bluetooth Controller Filter Accept List Size <0..32:1>
// <i> Default: 2
// <i> Define the number of Filter Accept List entries to be used in doing device address filtering when scanning
#define SL_BT_CONFIG_ACCEPT_LIST_SIZE     (2)

// </h> Bluetooth Controller Configuration

// <<< end of configuration section >>>

#endif // SL_BT_ACCEPT_LIST_CONFIG_H

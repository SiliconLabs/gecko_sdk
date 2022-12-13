/***************************************************************************//**
 * @file
 * @brief Constant Tone Extension GATT Service Configuration
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

#ifndef SL_GATT_SERVICE_CTE_CONFIG_H
#define SL_GATT_SERVICE_CTE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_GATT_SERVICE_CTE_TYPE> Slot length
//   <1=> AoD CTE with 1 us slots
//   <2=> AoD CTE with 2 us slots
// <i> Default: 1
#define SL_GATT_SERVICE_CTE_TYPE 1

// <a.16 SL_GATT_SERVICE_CTE_SWITCHING_PATTERN> Antenna switching pattern <0..255>
// <i> For a custom array length, edit this configuration file manually
#define SL_GATT_SERVICE_CTE_SWITCHING_PATTERN { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }

// <<< end of configuration section >>>

#endif // SL_GATT_SERVICE_CTE_H

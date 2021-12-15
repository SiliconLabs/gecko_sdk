/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application core component utility configuration header.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SL_WISUN_APPLICATION_UTIL_CONFIG_H
#define SL_WISUN_APPLICATION_UTIL_CONFIG_H

/**************************************************************************//**
 * @defgroup SL_WISUN_APP_CORE_UTIL_CONFIG Utility configuration
 * @ingroup SL_WISUN_APP_CORE
 * @{
 *****************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Heartbeat Enable

// <q HEARTBEAT_ENABLED> Enable
// <i> Enables The heartbeat character and section breaks on the console output.
#define HEARTBEAT_ENABLED      0

// </h> End Heartbeat Enable

// <h> Heartbeat section length

// <o HEARBEAT_SECTION_LENGTH> Length of one section is seconds where the heartbeat breaks line.
// <i> Default: 60
// <i> Define the number seconds which is printed on one line
#define HEARBEAT_SECTION_LENGTH      (60)

// </h> End Heartbeat section length

// <<< end of configuration section >>>

/** @}*/

#endif // SL_WISUN_APPLICATION_UTIL_CONFIG_H

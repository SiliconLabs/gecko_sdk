/***************************************************************************//**
 * @file
 * @brief Bluetooth Periodic Advertiser configuration
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

#ifndef SL_BT_PERIODIC_ADVERTISER_CONFIG_H
#define SL_BT_PERIODIC_ADVERTISER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth Periodic Advertiser Configuration

// <o SL_BT_CONFIG_MAX_PERIODIC_ADVERTISERS> Max number of advertising sets that support periodic advertising <0-255>
// <i> Default: 1
// <i> Define the number of periodic advertising sets that the application needs to use concurrently. This number must not exceed the total number of advertising sets configured by SL_BT_CONFIG_USER_ADVERTISERS in the component "bluetooth_feature_advertiser".
#define SL_BT_CONFIG_MAX_PERIODIC_ADVERTISERS     (1)

// </h> End Bluetooth Periodic Advertiser Configuration

// <<< end of configuration section >>>

#endif // SL_BT_PERIODIC_ADVERTISER_CONFIG_H

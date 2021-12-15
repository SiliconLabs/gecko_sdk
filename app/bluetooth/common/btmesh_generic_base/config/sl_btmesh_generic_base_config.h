/***************************************************************************//**
 * @file
 * @brief
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
#ifndef SL_BTMESH_GENERIC_BASE_CONFIG_H
#define SL_BTMESH_GENERIC_BASE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Generic Base configuration

// <o GENERIC_BASE_INCREMENT> Register size increment <0-10>
// <i> Default: 3
// <i> The dynamically reallocated array will grow in size by this value.
// <i> Setting this value to 0 will disable reallocation.
#define GENERIC_BASE_INCREMENT                       3

// </h>

// <h> Generic Models Initialization configuration

// <e GENERIC_BASE_SERVER> Enable Generic Server Models
// <i> Default: 0
// <i> Enable Generic Server functionality.
#define GENERIC_BASE_SERVER                          0

// <q GENERIC_ON_OFF_SERVER_INIT> Generic On/Off Server
// <i> Default: 0
// <i> Initialize Generic On/Off Server.
#define GENERIC_ON_OFF_SERVER_INIT                   0

// <q GENERIC_LEVEL_SERVER_INIT> Generic Level Server
// <i> Default: 0
// <i> Initialize Generic Level Server.
#define GENERIC_LEVEL_SERVER_INIT                    0

// <q GENERIC_DEFAULT_TRANSITION_TIME_SERVER_INIT> Generic Default Transition Time Server
// <i> Default: 0
// <i> Initialize Generic Default Transition Time Server.
#define GENERIC_DEFAULT_TRANSITION_TIME_SERVER_INIT  0

// <q GENERIC_POWER_ON_OFF_SERVER_INIT> Generic Power On/Off Server
// <i> Default: 0
// <i> Initialize Generic Power On/Off Server.
#define GENERIC_POWER_ON_OFF_SERVER_INIT             0

// <q GENERIC_POWER_LEVEL_SERVER_INIT> Generic Power Level Server
// <i> Default: 0
// <i> Initialize Generic Power Level Server.
#define GENERIC_POWER_LEVEL_SERVER_INIT              0

// <q GENERIC_BATTERY_SERVER_INIT> Generic Battery Server
// <i> Default: 0
// <i> Initialize Generic Battery Server.
#define GENERIC_BATTERY_SERVER_INIT                  0

// <q GENERIC_LOCATION_SERVER_INIT> Generic Location Server
// <i> Default: 0
// <i> Initialize Generic Location Server.
#define GENERIC_LOCATION_SERVER_INIT                 0

// <q GENERIC_PROPERTY_SERVER_INIT> Generic Property Server
// <i> Default: 0
// <i> Initialize Generic Property Server.
#define GENERIC_PROPERTY_SERVER_INIT                 0

// <q GENERIC_LIGHTNESS_SERVER_INIT> Light Lightness Server
// <i> Default: 0
// <i> Initialize Light Lightness Server.
#define GENERIC_LIGHTNESS_SERVER_INIT                0

// <q GENERIC_CTL_SERVER_INIT> Light CTL Server
// <i> Default: 0
// <i> Initialize Light CTL Server.
#define GENERIC_CTL_SERVER_INIT                      0

// <q GENERIC_HSL_SERVER_INIT> Light HSL Server
// <i> Default: 0
// <i> Initialize Light HSL Server.
#define GENERIC_HSL_SERVER_INIT                      0

// </e>

// <e GENERIC_BASE_CLIENT> Enable Generic Client Models
// <i> Default: 0
// <i> Enable Generic Client functionality.
#define GENERIC_BASE_CLIENT                          0

// <q GENERIC_ON_OFF_CLIENT_INIT> Generic On/Off Client
// <i> Default: 0
// <i> Initialize Generic On/Off Client.
#define GENERIC_ON_OFF_CLIENT_INIT                   0

// <q GENERIC_LEVEL_CLIENT_INIT> Generic Level Client
// <i> Default: 0
// <i> Initialize Generic Level Client.
#define GENERIC_LEVEL_CLIENT_INIT                    0

// <q GENERIC_DEFAULT_TRANSITION_TIME_CLIENT_INIT> Generic Default Transition Time Client
// <i> Default: 0
// <i> Initialize Generic Default Transition Time Client.
#define GENERIC_DEFAULT_TRANSITION_TIME_CLIENT_INIT  0

// <q GENERIC_POWER_ON_OFF_CLIENT_INIT> Generic Power On/Off Client
// <i> Default: 0
// <i> Initialize Generic Power On/Off Client.
#define GENERIC_POWER_ON_OFF_CLIENT_INIT             0

// <q GENERIC_POWER_LEVEL_CLIENT_INIT> Generic Power Level Client
// <i> Default: 0
// <i> Initialize Generic Power Level Client.
#define GENERIC_POWER_LEVEL_CLIENT_INIT              0

// <q GENERIC_BATTERY_CLIENT_INIT> Generic Battery Client
// <i> Default: 0
// <i> Initialize Generic Battery Client.
#define GENERIC_BATTERY_CLIENT_INIT                  0

// <q GENERIC_LOCATION_CLIENT_INIT> Generic Location Client
// <i> Default: 0
// <i> Initialize Generic Location Client.
#define GENERIC_LOCATION_CLIENT_INIT                 0

// <q GENERIC_PROPERTY_CLIENT_INIT> Generic Property Client
// <i> Default: 0
// <i> Initialize Generic Property Client.
#define GENERIC_PROPERTY_CLIENT_INIT                 0

// <q GENERIC_LIGHTNESS_CLIENT_INIT> Light Lightness Client
// <i> Default: 0
// <i> Initialize Lightness Client.
#define GENERIC_LIGHTNESS_CLIENT_INIT                0

// <q GENERIC_CTL_CLIENT_INIT> Light CTL Client
// <i> Default: 0
// <i> Initialize Light CTL Client.
#define GENERIC_CTL_CLIENT_INIT                      0

// <q GENERIC_HSL_CLIENT_INIT> Light HSL Client
// <i> Default: 0
// <i> Initialize Light HSL Client.
#define GENERIC_HSL_CLIENT_INIT                      0

// </e>

// </h>

// <<< end of configuration section >>>

#endif // SL_BTMESH_GENERIC_BASE_CONFIG_H

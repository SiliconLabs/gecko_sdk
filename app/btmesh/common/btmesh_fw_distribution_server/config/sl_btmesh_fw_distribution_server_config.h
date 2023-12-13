/***************************************************************************//**
 * @file
 * @brief BT Mesh Firmware Distribution Server Configuration
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

#ifndef SL_BTMESH_FW_DISTRIBUTION_SERVER_CONFIG_H
#define SL_BTMESH_FW_DISTRIBUTION_SERVER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> BT Mesh Firmware Distribution Server Configuration

// <e SL_BTMESH_FW_DIST_SERVER_LOGGING_CFG_VAL> Enable Logging
// <i> Default: 1
// <i> Enable / disable logging of Firmware Distribution Server model specific messages
#define SL_BTMESH_FW_DIST_SERVER_LOGGING_CFG_VAL   (1)

// <q SL_BTMESH_FW_DIST_SERVER_PLATFORM_CALLBACK_LOGGING_CFG_VAL> Enable BT Mesh Stack Platform Callback Logging
// <i> Default: 0
// <i> Enable / disable logging of BT Mesh Stack Firmware Distribution Server model platform callbacks.
// <i> The FW Distribution Server model in BT Mesh stack calls platform callback functions to query the remaining space, firmware count and firmware information.
#define SL_BTMESH_FW_DIST_SERVER_PLATFORM_CALLBACK_LOGGING_CFG_VAL   (0)

// <o SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX> Fwid and metadata log format
// <true=> Hex format
// <false=>Text format
// <i> Fwid and metada logging format, hex or text format is available
#define SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX false

// <s SL_BTMESH_FW_DIST_SERVER_LOG_PREFIX_CFG_VAL> Text prepended to every log message
// <i> Default: "FwDistributor"
// <i> Every log message in the component is started with this text.
#define SL_BTMESH_FW_DIST_SERVER_LOG_PREFIX_CFG_VAL "FwDistributor"

// </e>

// <o SL_BTMESH_FW_DIST_SERVER_MAX_NODE_LIST_SIZE_CFG_VAL> Max node list size
// <1-1008:1>
// <i> Default: 4
// <i> Maximum number of firmware update server nodes which can participate in the distribution
#define SL_BTMESH_FW_DIST_SERVER_MAX_NODE_LIST_SIZE_CFG_VAL   (4)

// <o SL_BTMESH_FW_DIST_SERVER_MULTICAST_THRESHOLD_DEFAULT_CFG_VAL> Default Multicast Threshold
// <1-65535:1>
// <i> Default: 1
// <i> If the number of servers for any step exceeds or is equal to this number then the group address will be used,
// <i> otherwise servers will be looped through one by one. Value of 0 disables the feature.
#define SL_BTMESH_FW_DIST_SERVER_MULTICAST_THRESHOLD_DEFAULT_CFG_VAL   (1)

// <o SL_BTMESH_FW_DIST_SERVER_RETRY_TIME_MS_CFG_VAL> Retry time of message transmissions
// <0-65535:1>
// <i> Default: 3000
// <i> Retry time of firmware update message transmissions
#define SL_BTMESH_FW_DIST_SERVER_RETRY_TIME_MS_CFG_VAL    (3000)

// <o SL_BTMESH_FW_DIST_SERVER_FW_LIST_NVM_KEY_CFG_VAL> NVM key of the firmware list
// <0x0000-0xFFFF>
// <i> Default: 0x4009
// <i> NVM key of the firmware list
#define SL_BTMESH_FW_DIST_SERVER_FW_LIST_NVM_KEY_CFG_VAL    (0x4009)

// </h>

// <<< end of configuration section >>>

 #endif // SL_BTMESH_FW_DISTRIBUTION_SERVER_CONFIG_H

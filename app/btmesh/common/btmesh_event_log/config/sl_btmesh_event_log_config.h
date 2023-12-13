/***************************************************************************//**
 * @file
 * @brief Mesh events logging configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_EVENT_LOG_CONFIG_H
#define SL_BTMESH_EVENT_LOG_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <q SL_BTMESH_EVENT_LOG_ENABLE_NODE> Enable Mesh Node events logging
// <i> Enables logging of Mesh Node events.
#define SL_BTMESH_EVENT_LOG_ENABLE_NODE  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_PROV> Enable Bluetooth Mesh Stack Provisioner events logging
// <i> Enables logging of Bluetooth Mesh Stack Provisioner events.
#define SL_BTMESH_EVENT_LOG_ENABLE_PROV  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_PROXY> Enable Bluetooth Mesh Proxy Connections events logging
// <i> Enables logging of Bluetooth Mesh Proxy Connections events.
#define SL_BTMESH_EVENT_LOG_ENABLE_PROXY  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SILABS_CONFIG_CLIENT> Enable Bluetooth Mesh Silabs Configuration Client Vendor Model events logging
// <i> Enables logging of Bluetooth Mesh Silabs Configuration Client Vendor Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SILABS_CONFIG_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_VENDOR_MODEL> Enable Bluetooth Mesh Vendor Model events logging
// <i> Enables logging of Bluetooth Mesh Vendor Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_VENDOR_MODEL  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_HEALTH_CLIENT> Enable Bluetooth Mesh Health Client Model events logging
// <i> Enables logging of Bluetooth Mesh Health Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_HEALTH_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_HEALTH_SERVER> Enable Bluetooth Mesh Health Server Model events logging
// <i> Enables logging of Bluetooth Mesh Health Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_HEALTH_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_GENERIC_CLIENT> Enable Bluetooth Mesh Generic Client Model events logging
// <i> Enables logging of Bluetooth Mesh Generic Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_GENERIC_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_GENERIC_SERVER> Enable Bluetooth Mesh Generic Server Model events logging
// <i> Enables logging of Bluetooth Mesh Generic Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_GENERIC_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_TEST> Enable Bluetooth Mesh Test Utilities events logging
// <i> Enables logging of Bluetooth Mesh Test Utilities events.
#define SL_BTMESH_EVENT_LOG_ENABLE_TEST  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_LPN> Enable Bluetooth Mesh Low Power Node API events logging
// <i> Enables logging of Bluetooth Mesh Low Power Node API events.
#define SL_BTMESH_EVENT_LOG_ENABLE_LPN  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_FRIEND> Enable Bluetooth Mesh Friend Node API events logging
// <i> Enables logging of Bluetooth Mesh Friend Node API events.
#define SL_BTMESH_EVENT_LOG_ENABLE_FRIEND  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_PROXY_CLIENT> Enable Bluetooth Mesh GATT Proxy Client events logging
// <i> Enables logging of Bluetooth Mesh GATT Proxy Client events.
#define SL_BTMESH_EVENT_LOG_ENABLE_PROXY_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_PROXY_SERVER> Enable Bluetooth Mesh GATT Proxy Server events logging
// <i> Enables logging of Bluetooth Mesh GATT Proxy Server events.
#define SL_BTMESH_EVENT_LOG_ENABLE_PROXY_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_CONFIG_CLIENT> Enable Bluetooth Mesh Configuration Client Model events logging
// <i> Enables logging of Bluetooth Mesh Configuration Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_CONFIG_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_MBT_CLIENT> Enable Bluetooth Mesh BLOB Transfer Client Model events logging
// <i> Enables logging of Bluetooth Mesh BLOB Transfer Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_MBT_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_MBT_SERVER> Enable Bluetooth Mesh BLOB Transfer Server Model events logging
// <i> Enables logging of Bluetooth Mesh BLOB Transfer Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_MBT_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SENSOR_SERVER> Enable Bluetooth Mesh Sensor Server Model events logging
// <i> Enables logging of Bluetooth Mesh Sensor Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SENSOR_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SENSOR_SETUP_SERVER> Enable Bluetooth Mesh Sensor Setup Server Model events logging
// <i> Enables logging of Bluetooth Mesh Sensor Setup Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SENSOR_SETUP_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SENSOR_CLIENT> Enable Bluetooth Mesh Sensor Client Model events logging
// <i> Enables logging of Bluetooth Mesh Sensor Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SENSOR_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_FW_UPDATE_CLIENT> Enable Bluetooth Mesh Firmware Update Client Model events logging
// <i> Enables logging of Bluetooth Mesh Firmware Update Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_FW_UPDATE_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_LC_CLIENT> Enable Bluetooth Mesh Light Control Client Model events logging
// <i> Enables logging of Bluetooth Mesh Light Control Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_LC_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_LC_SERVER> Enable Bluetooth Mesh Light Control Server Model events logging
// <i> Enables logging of Bluetooth Mesh Light Control Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_LC_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_LC_SETUP_SERVER> Enable Bluetooth Mesh Light Control Setup Server Model events logging
// <i> Enables logging of Bluetooth Mesh Light Control Setup Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_LC_SETUP_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SCENE_CLIENT> Enable Bluetooth Mesh Scene Client Model events logging
// <i> Enables logging of Bluetooth Mesh Scene Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SCENE_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SCENE_SERVER> Enable Bluetooth Mesh Scene Server Model events logging
// <i> Enables logging of Bluetooth Mesh Scene Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SCENE_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SCENE_SETUP_SERVER> Enable Bluetooth Mesh Scene Setup Server Model events logging
// <i> Enables logging of Bluetooth Mesh Scene Setup Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SCENE_SETUP_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SCHEDULER_CLIENT> Enable Bluetooth Mesh Scheduler Client Model events logging
// <i> Enables logging of Bluetooth Mesh Scheduler Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SCHEDULER_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SCHEDULER_SERVER> Enable Bluetooth Mesh Scheduler Server Model events logging
// <i> Enables logging of Bluetooth Mesh Scheduler Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SCHEDULER_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_FW_UPDATE_SERVER> Enable Bluetooth Mesh Firmware Update Server Model events logging
// <i> Enables logging of Bluetooth Mesh Firmware Update Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_FW_UPDATE_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_TIME_SERVER> Enable Bluetooth Mesh Time Server Model events logging
// <i> Enables logging of Bluetooth Mesh Time Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_TIME_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_TIME_CLIENT> Enable Bluetooth Mesh Time Client Model events logging
// <i> Enables logging of Bluetooth Mesh Time Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_TIME_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_FW_DIST_SERVER> Enable Bluetooth Mesh Firmware Distribution Server Model events logging
// <i> Enables logging of Bluetooth Mesh Firmware Distribution Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_FW_DIST_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_FW_DIST_CLIENT> Enable Bluetooth Mesh Firmware Distribution Client Model events logging
// <i> Enables logging of Bluetooth Mesh Firmware Distribution Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_FW_DIST_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_REMOTE_PROVISIONING_CLIENT> Enable Bluetooth Mesh Remote Provisioning Client Model events logging
// <i> Enables logging of Bluetooth Mesh Remote Provisioning Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_REMOTE_PROVISIONING_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_REMOTE_PROVISIONING_SERVER> Enable Bluetooth Mesh Remote Provisioning Server Model events logging
// <i> Enables logging of Bluetooth Mesh Remote Provisioning Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_REMOTE_PROVISIONING_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_FW_STANDALONE_UPDATER> Enable Bluetooth Mesh Standalone Updater events logging
// <i> Enables logging of Bluetooth Mesh Standalone Updater events.
#define SL_BTMESH_EVENT_LOG_ENABLE_FW_STANDALONE_UPDATER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_MIGRATION> Enable Bluetooth Mesh Key migration events logging
// <i> Enables logging of Bluetooth Mesh Key migration events.
#define SL_BTMESH_EVENT_LOG_ENABLE_MIGRATION  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_NCP_FW_LIST> Enable NCP firmware list cache events logging
// <i> Enables logging of NCP firmware list cache events.
#define SL_BTMESH_EVENT_LOG_ENABLE_NCP_FW_LIST  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SAR_CONFIG_CLIENT> Enable Bluetooth Mesh SAR Configuration Client Model events logging
// <i> Enables logging of Bluetooth Mesh SAR Configuration Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SAR_CONFIG_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SAR_CONFIG_SERVER> Enable Bluetooth Mesh SAR Configuration Server Model events logging
// <i> Enables logging of Bluetooth Mesh SAR Configuration Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SAR_CONFIG_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_PRIVATE_BEACON_CLIENT> Enable Bluetooth Mesh Private Beacon Client Model events logging
// <i> Enables logging of Bluetooth Mesh Private Beacon Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_PRIVATE_BEACON_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_PRIVATE_BEACON_SERVER> Enable Bluetooth Mesh Private Beacon Server Model events logging
// <i> Enables logging of Bluetooth Mesh Private Beacon Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_PRIVATE_BEACON_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_LCD_CLIENT> Enable Bluetooth Mesh Large Composition Data Client Model events logging
// <i> Enables logging of Bluetooth Mesh Large Composition Data Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_LCD_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_LCD_SERVER> Enable Bluetooth Mesh Large Composition Data Server Model events logging
// <i> Enables logging of Bluetooth Mesh Large Composition Data Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_LCD_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_ON_DEMAND_PRIVATE_PROXY_CLIENT> Enable Bluetooth Mesh On-demand Private Proxy Client Model events logging
// <i> Enables logging of Bluetooth Mesh On-demand Private Proxy Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_ON_DEMAND_PRIVATE_PROXY_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SOLICITATION_CONFIG_CLIENT> Enable Bluetooth Mesh Solicitation PDU RPL Config Client Model events logging
// <i> Enables logging of Bluetooth Mesh Solicitation PDU RPL Config Client Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SOLICITATION_CONFIG_CLIENT  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_ON_DEMAND_PRIVATE_PROXY_SERVER> Enable Bluetooth Mesh On-demand Private Proxy Server Model events logging
// <i> Enables logging of Bluetooth Mesh On-demand Private Proxy Server Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_ON_DEMAND_PRIVATE_PROXY_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_SILABS_CONFIG_SERVER> Enable Bluetooth Mesh Silabs Configuration Server Vendor Model events logging
// <i> Enables logging of Bluetooth Mesh Silabs Configuration Server Vendor Model events.
#define SL_BTMESH_EVENT_LOG_ENABLE_SILABS_CONFIG_SERVER  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_DIAGNOSTIC> Enable Bluetooth Mesh Diagnostic Utilities events logging
// <i> Enables logging of Bluetooth Mesh Diagnostic Utilities events.
#define SL_BTMESH_EVENT_LOG_ENABLE_DIAGNOSTIC  1

// <q SL_BTMESH_EVENT_LOG_ENABLE_UNKNOWN_CFG_VAL> Enable unknown events logging
// <i> Enables logging of unknown events.
#define SL_BTMESH_EVENT_LOG_ENABLE_UNKNOWN_CFG_VAL 1

// <s SL_BTMESH_EVENT_LOG_PREFIX_CFG_VAL> Prefix
// <i> Prefix of the logged events.
#define SL_BTMESH_EVENT_LOG_PREFIX_CFG_VAL "evt:"

// <<< end of configuration section >>>

#endif // SL_BTMESH_EVENT_LOG_CONFIG_H

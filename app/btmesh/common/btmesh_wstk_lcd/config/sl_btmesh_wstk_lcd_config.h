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
#ifndef SL_BTMESH_WSTK_LCD_CONFIG_H
#define SL_BTMESH_WSTK_LCD_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> LCD rows configuration

// <o SL_BTMESH_WSTK_LCD_ROW_NAME_CFG_VAL> Row for Device Name
// <i> Default: 1
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Device Name will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_NAME_CFG_VAL   (1)

// <o SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL> Row for Node Status
// <i> Default: 2
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Node Status will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL   (2)

// <o SL_BTMESH_WSTK_LCD_ROW_CONNECTION_CFG_VAL> Row for Connection Status
// <i> Default: 3
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Connection Status will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_CONNECTION_CFG_VAL   (3)

// <o SL_BTMESH_WSTK_LCD_ROW_FRIEND_CFG_VAL> Row for Friend status in a Friendship
// <i> Default: 4
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Friend status in a Friendship will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_FRIEND_CFG_VAL   (4)

// <o SL_BTMESH_WSTK_LCD_ROW_LPN_CFG_VAL> Row for LPN status in a Friendship
// <i> Default: 4
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the LPN status in a Friendship will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_LPN_CFG_VAL   (4)

// <h> Sensor Server

// <o SL_BTMESH_WSTK_LCD_ROW_PEOPLE_COUNT_CFG_VAL> Row for People Count
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the People Count will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_PEOPLE_COUNT_CFG_VAL   (5)

// <o SL_BTMESH_WSTK_LCD_ROW_TEMPERATURE_CFG_VAL> Row for Server Temperature
// <i> Default: 6
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Server Temperature will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_TEMPERATURE_CFG_VAL   (6)

// <o SL_BTMESH_WSTK_LCD_ROW_ILLUMINANCE_CFG_VAL> Row for Illuminance
// <i> Default: 7
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Illuminance will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_ILLUMINANCE_CFG_VAL   (7)

// </h>

// <h> Sensor Client

// <o SL_BTMESH_WSTK_LCD_ROW_SENSOR_DATA_CFG_VAL> Row for Sensor Data
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the First row of Sensor Data read by the client will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_SENSOR_DATA_CFG_VAL   (5)

// </h>

// <h> Lighting

// <o SL_BTMESH_WSTK_LCD_ROW_LIGHTNESS_CFG_VAL> Row for Lightness
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Lightness will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_LIGHTNESS_CFG_VAL   (5)

// <o SL_BTMESH_WSTK_LCD_ROW_COLOR_TEMPERATURE_CFG_VAL> Row for Color Temperature
// <i> Default: 6
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Color Temperature will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_COLOR_TEMPERATURE_CFG_VAL   (6)

// <o SL_BTMESH_WSTK_LCD_ROW_HUE_CFG_VAL> Row for Hue
// <i> Default: 6
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Hue will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_HUE_CFG_VAL   (6)

// <o SL_BTMESH_WSTK_LCD_ROW_DELTAUV_CFG_VAL> Row for Delta UV
// <i> Default: 7
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Delta UV will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_DELTAUV_CFG_VAL   (7)

// <o SL_BTMESH_WSTK_LCD_ROW_SATURATION_CFG_VAL> Row for Saturation
// <i> Default: 7
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Saturation will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_SATURATION_CFG_VAL   (7)

// </h>

// <h> Scene Client

// <o SL_BTMESH_WSTK_LCD_ROW_CURRENT_SCENE_CFG_VAL> Row for Current Scene
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Current Scene will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_CURRENT_SCENE_CFG_VAL   (5)

// </h>

// <h> Firmware Update

// <o SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_STATUS_CFG_VAL> Firmware Update Status
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Firmware Update Status will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_STATUS_CFG_VAL (5)

// <o SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL> Firmware Update Messages
// <i> Default: 6
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Firmware Update Messages will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_FW_UPDATE_MESSAGES_CFG_VAL (6)

// </h>

// <h> BLOB Transfer

// <o SL_BTMESH_WSTK_LCD_ROW_BLOB_STATUS_CFG_VAL> BLOB Transfer Status
// <i> Default: 7
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the BLOB Transfer Status will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_BLOB_STATUS_CFG_VAL (7)

// <o SL_BTMESH_WSTK_LCD_ROW_BLOB_ID_CFG_VAL> BLOB Transfer ID
// <i> Default: 8
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the BLOB Transfer ID will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_BLOB_ID_CFG_VAL (8)

// <o SL_BTMESH_WSTK_LCD_ROW_BLOB_PROGRESS_CFG_VAL> BLOB Transfer Progress
// <i> Default: 9
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the BLOB Transfer Progress will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_BLOB_PROGRESS_CFG_VAL (9)

// </h>

// <h> Distributor

// <o SL_BTMESH_WSTK_LCD_ROW_DIST_FW_LIST_CFG_VAL> Row for Fw Distribution Server Firmware List
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Firmware List will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_DIST_FW_LIST_CFG_VAL   (5)

// <o SL_BTMESH_WSTK_LCD_ROW_DIST_UPLOAD_PROGRESS_CFG_VAL> Row for Fw Distribution Server Upload Progress
// <i> Default: 6
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Upload Progress will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_DIST_UPLOAD_PROGRESS_CFG_VAL   (6)

// <o SL_BTMESH_WSTK_LCD_ROW_DIST_NODE_LIST_CFG_VAL> Row for Fw Distribution Server Node List
// <i> Default: 7
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Node List will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_DIST_NODE_LIST_CFG_VAL   (7)

// <o SL_BTMESH_WSTK_LCD_ROW_DIST_STATE_CFG_VAL> Row for Fw Distribution Server State
// <i> Default: 8
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the State will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_DIST_STATE_CFG_VAL   (8)

// <o SL_BTMESH_WSTK_LCD_ROW_DIST_DISTRIBUTION_PROGRESS_CFG_VAL> Row for Fw Distribution Server Distribution Progress
// <i> Default: 9
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Distribution Progress will be printed in the row specified here.
#define SL_BTMESH_WSTK_LCD_ROW_DIST_DISTRIBUTION_PROGRESS_CFG_VAL   (9)

// </h>

// </h>

// <h> LCD texts

// <s.128 SL_BTMESH_WSTK_LCD_GRAPH_INIT_TEXT_CFG_VAL> Text for initializing graphics.
// <i> Text for initializing graphics
#define SL_BTMESH_WSTK_LCD_GRAPH_INIT_TEXT_CFG_VAL "SILICON LABORATORIES\nBluetooth Mesh Demo\n\n"

// <s.128 SL_BTMESH_WSTK_LCD_INIT_TEXT_CFG_VAL> Text to be printed on the LCD when it is initialized.
// <i> Text to be printed on the LCD when it is initialized
#define SL_BTMESH_WSTK_LCD_INIT_TEXT_CFG_VAL "initializing"

// </h>

// <<< end of configuration section >>>

#endif // SL_BTMESH_WSTK_LCD_CONFIG_H

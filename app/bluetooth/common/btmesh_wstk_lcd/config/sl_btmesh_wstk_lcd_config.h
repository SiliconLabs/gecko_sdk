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

// <o BTMESH_WSTK_LCD_ROW_NAME> Row for Device Name
// <i> Default: 1
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Device Name will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_NAME   (1)

// <o BTMESH_WSTK_LCD_ROW_STATUS> Row for Node Status
// <i> Default: 2
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Node Status will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_STATUS   (2)

// <o BTMESH_WSTK_LCD_ROW_CONNECTION> Row for Connection Status
// <i> Default: 3
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Connection Status will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_CONNECTION   (3)

// <o BTMESH_WSTK_LCD_ROW_FRIEND> Row for Friend status in a Friendship
// <i> Default: 4
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Friend status in a Friendship will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_FRIEND   (4)

// <o BTMESH_WSTK_LCD_ROW_LPN> Row for LPN status in a Friendship
// <i> Default: 4
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the LPN status in a Friendship will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_LPN   (4)

// <o BTMESH_WSTK_LCD_ROW_LIGHTNESS> Row for Lightness
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Lightness will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_LIGHTNESS   (5)

// <o BTMESH_WSTK_LCD_ROW_SENSOR_DATA> Row for Sensor Data
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the First row of Sensor Data read by the client will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_SENSOR_DATA   (5)

// <o BTMESH_WSTK_LCD_ROW_PEOPLE_COUNT> Row for People Count
// <i> Default: 5
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the People Count will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_PEOPLE_COUNT   (5)

// <o BTMESH_WSTK_LCD_ROW_TEMPERATURE> Row for Color Temperature / Sensor Temperature
// <i> Default: 6
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Color Temperature / Sensor Temperature will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_TEMPERATURE   (6)

// <o BTMESH_WSTK_LCD_ROW_HUE> Row for Hue
// <i> Default: 6
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Hue will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_HUE   (6)

// <o BTMESH_WSTK_LCD_ROW_DELTAUV> Row for Delta UV
// <i> Default: 7
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Delta UV will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_DELTAUV   (7)

// <o BTMESH_WSTK_LCD_ROW_SATURATION> Row for Saturation
// <i> Default: 7
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Saturation will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_SATURATION   (7)

// <o BTMESH_WSTK_LCD_ROW_ILLUMINANCE> Row for Illuminance
// <i> Default: 7
// <1-9:1>
// <i> LCD on WSTKs have 9 rows. Out of these the Illuminance will be printed in the row specified here.
#define BTMESH_WSTK_LCD_ROW_ILLUMINANCE   (7)

// </h>

// <h> LCD texts

// <s.128 BTMESH_WSTK_LCD_GRAPH_INIT_TEXT> Text for initializting graphics.
// <i> Text for initializting graphics
#define BTMESH_WSTK_LCD_GRAPH_INIT_TEXT "SILICON LABORATORIES\nBluetooth Mesh Demo\n\n"

// <s.128 BTMESH_WSTK_LCD_INIT_TEXT> Text to be printed on the LCD when it is initialized.
// <i> Text to be printed on the LCD when it is initialized
#define BTMESH_WSTK_LCD_INIT_TEXT "initializing"

// </h>

// <<< end of configuration section >>>

#endif // SL_BTMESH_WSTK_LCD_CONFIG_H

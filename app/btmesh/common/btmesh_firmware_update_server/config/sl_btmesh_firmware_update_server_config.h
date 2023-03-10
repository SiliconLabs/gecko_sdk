/***************************************************************************//**
 * @file
 * @brief Firmware Update Server Configuration
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

#ifndef SL_BTMESH_FIRMWARE_UPDATE_SERVER_CONFIG_H
#define SL_BTMESH_FIRMWARE_UPDATE_SERVER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_BTMESH_FW_UPDATE_SERVER_NUM_OF_FW_CFG_VAL> Number of firmware on device <1-255>
#define SL_BTMESH_FW_UPDATE_SERVER_NUM_OF_FW_CFG_VAL 1

// <o SL_BTMESH_FW_UPDATE_SERVER_METADATA_LENGTH_CFG_VAL> Maximum length of metadata <0-255>
#define SL_BTMESH_FW_UPDATE_SERVER_METADATA_LENGTH_CFG_VAL 255

// <h> Firmware Information
// <h> Company Identifier
// <s.3 SL_BTMESH_FW_UPDATE_SERVER_CID_MSB_CFG_VAL> CID MSB
// <i> Hexadecimal string literal.
#define SL_BTMESH_FW_UPDATE_SERVER_CID_MSB_CFG_VAL "\x02"

// <s.3 SL_BTMESH_FW_UPDATE_SERVER_CID_LSB_CFG_VAL> CID LSB
// <i> Hexadecimal string literal.
#define SL_BTMESH_FW_UPDATE_SERVER_CID_LSB_CFG_VAL "\xFF"

// </h>

// <s.106 SL_BTMESH_FW_UPDATE_SERVER_FWID_CFG_VAL> Firmware identifier
#define SL_BTMESH_FW_UPDATE_SERVER_FWID_CFG_VAL "fwid"

// <s.255 SL_BTMESH_FW_UPDATE_SERVER_UPDATE_URI_CFG_VAL> Update URI
#define SL_BTMESH_FW_UPDATE_SERVER_UPDATE_URI_CFG_VAL "https://example.com/upd_uri"

// </h>

// <e SL_BTMESH_FW_UPDATE_SERVER_LOGGING_CFG_VAL> Logging
#define SL_BTMESH_FW_UPDATE_SERVER_LOGGING_CFG_VAL 1

// <o SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL> Period of verification progress logs [ms] <0-2000:100>
// <i> Setting it to 0 the user interface (log & display) is updated every time when progress is made.
#define SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL 200

// </e>

// <<< end of configuration section >>>

#endif // SL_BTMESH_FIRMWARE_UPDATE_SERVER_CONFIG_H

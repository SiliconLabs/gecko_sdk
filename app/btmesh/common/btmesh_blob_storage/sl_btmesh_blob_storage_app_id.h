/***************************************************************************//**
 * @file
 * @brief BT Mesh BLOB Storage Application Identifiers
 *
 * This file contains the list of reserved application identifiers (app_id) of
 * Silicon Laboratories software components. If the application needs to store
 * additional data in app footer then the usage of these application identifiers
 * shall be avoided.
 *
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

#ifndef SL_BTMESH_BLOB_STORAGE_APP_ID_H
#define SL_BTMESH_BLOB_STORAGE_APP_ID_H

/***************************************************************************//**
 * @addtogroup blob_storage
 * @{
 ******************************************************************************/

/// Reserved BLOB Storage owner ID of FW Distribution Server
#define BLOB_STORAGE_OWNER_ID_FW_DIST_SERVER  0x1000

/// Reserved BLOB Storage app ID of Firmware ID (BT Mesh DFU)
#define BLOB_STORAGE_APP_ID_DFU_FWID          0x1001

/// Reserved BLOB Storage app ID of Metadata (BT Mesh DFU)
#define BLOB_STORAGE_APP_ID_DFU_METADATA      0x1002

/// Reserved BLOB Storage app ID of managed flag
#define BLOB_STORAGE_APP_ID_MANAGED_FLAG      0x8000

/** @} end blob_storage */

#endif // SL_BTMESH_BLOB_STORAGE_APP_ID_H

/**************************************************************************//**
 * @file
 * @brief BT Mesh Host Remote Provisioner Example Project.
 ******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/

#ifndef BTMESH_APP_REMOTE_PROV_UI_H
#define BTMESH_APP_REMOTE_PROV_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#define REMOTE_SERVERLIST_COMMAND       'm'
#define REMOTE_SCAN_COMMAND             'o'
#define REMOTE_PROVISION_COMMAND        'v'

#define PROV_UI_MENU                                 \
  "Please select a functionality\n\n"                \
  "s - Scan available nodes\n"                       \
  "p - Provision a beaconing node\n"                 \
  "l - List nodes in the network\n"                  \
  "i - Information about a node in the network\n"    \
  "r - Remove node from the network\n"               \
  "k - Refresh the network key and app key\n"        \
  "m - List available remote provisioning servers\n" \
  "o - Remote scan unprovisioned nodes\n"            \
  "v - Remote provision an unprovisioned node\n"     \
  "e - Reset provisioner node\n"                     \
  "q - Exit application\n\n"

#ifdef __cplusplus
};
#endif

#endif // BTMESH_APP_REMOTE_PROV_UI_H

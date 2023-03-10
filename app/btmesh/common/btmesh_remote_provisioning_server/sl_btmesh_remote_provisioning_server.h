/***************************************************************************//**
 * @file
 * @brief BT Mesh Remote Provisioning Server Component
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_REMOTE_PROVISIONING_SERVER_H
#define SL_BTMESH_REMOTE_PROVISIONING_SERVER_H

#include "sl_btmesh_api.h"

/***************************************************************************//**
 * Handle Remote Provisioning Server events
 *
 * This function is called automatically by Universal Configurator after
 * enabling the component
 *
 * @param[in] evt Pointer to incoming event
 ******************************************************************************/
void sli_btmesh_handle_remote_provisioning_server_on_event(const sl_btmesh_msg_t *evt);

#endif // SL_BTMESH_REMOTE_PROVISIONING_SERVER_H

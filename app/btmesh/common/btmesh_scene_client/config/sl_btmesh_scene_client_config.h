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
#ifndef SL_BTMESH_SCENE_CLIENT_CONFIG_H
#define SL_BTMESH_SCENE_CLIENT_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Scene Client configuration

// <o SL_BTMESH_SCENE_CLIENT_RETRANSMISSION_COUNT_CFG_VAL> Scene model restransmission count
// <i> Default: 3
// <i> Scene model restransmission count (How many times Scene model messages are to be sent out for reliability).
#define SL_BTMESH_SCENE_CLIENT_RETRANSMISSION_COUNT_CFG_VAL   (3)

// <o SL_BTMESH_SCENE_CLIENT_RETRANSMISSION_TIMEOUT_CFG_VAL> Scene model restransmission timeout
// <i> Default: 50
// <i> Scene model restransmission timeout.
#define SL_BTMESH_SCENE_CLIENT_RETRANSMISSION_TIMEOUT_CFG_VAL   (50)

// <e SL_BTMESH_SCENE_CLIENT_LOGGING_CFG_VAL> Enable Logging
// <i> Default: 1
// <i> Enable / disable Logging for Scene Client model specific messages for this component.
#define SL_BTMESH_SCENE_CLIENT_LOGGING_CFG_VAL   (1)

// </e>

// </h>

// <<< end of configuration section >>>

#endif // SL_BTMESH_SCENE_CLIENT_CONFIG_H

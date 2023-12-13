/***************************************************************************/ /**
 * @file
 * @brief
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
#ifndef SL_BTMESH_GENERIC_LEVEL_CLIENT_EXT_CONFIG_H
#define SL_BTMESH_GENERIC_LEVEL_CLIENT_EXT_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Generic Level Client configuration

// <o SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_COUNT_CFG_VAL> Generic Level Delta retransmission count
// <d> 3
// <i> Generic Level Delta retransmission count (How many times model messages are to be sent out for reliability)
#define SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_COUNT_CFG_VAL   (3)

// <o SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_TIMEOUT_CFG_VAL> Generic Level Delta retransmission timeout
// <d> 50
// <i> Generic Level Delta retransmission timeout in ms
#define SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_TIMEOUT_CFG_VAL   (50)

// <o SL_BTMESH_GENERIC_LEVEL_EXT_MOVE_RETRANSMISSION_COUNT_CFG_VAL> Generic Level Move retransmission count
// <d> 3
// <i> Generic Level Move retransmission count (How many times model messages are to be sent out for reliability)
#define SL_BTMESH_GENERIC_LEVEL_EXT_MOVE_RETRANSMISSION_COUNT_CFG_VAL   (3)

// <o SL_BTMESH_GENERIC_LEVEL_EXT_MOVE_RETRANSMISSION_TIMEOUT_CFG_VAL> Generic Level Move retransmission timeout
// <d> 50
// <i> Generic Level Move retransmission timeout in ms
#define SL_BTMESH_GENERIC_LEVEL_EXT_MOVE_RETRANSMISSION_TIMEOUT_CFG_VAL   (50)

// <o SL_BTMESH_GENERIC_LEVEL_EXT_HALT_RETRANSMISSION_COUNT_CFG_VAL> Halt message retransmission count
// <d> 3
// <i> Halt retransmission count (How many times model messages are to be sent out for reliability)
#define SL_BTMESH_GENERIC_LEVEL_EXT_HALT_RETRANSMISSION_COUNT_CFG_VAL   (3)

// <o SL_BTMESH_GENERIC_LEVEL_EXT_HALT_RETRANSMISSION_TIMEOUT_CFG_VAL> Halt message retransmission timeout
// <d> 50
// <i> Halt retransmission timeout in ms
#define SL_BTMESH_GENERIC_LEVEL_EXT_HALT_RETRANSMISSION_TIMEOUT_CFG_VAL   (50)

// <e SL_BTMESH_GENERIC_LEVEL_CLIENT_EXT_LOGGING_CFG_VAL> Enable Logging
// <d> 1
// <i> Enable / disable Logging for Generic Level Client Ext model specific messages for this component
#define SL_BTMESH_GENERIC_LEVEL_CLIENT_EXT_LOGGING_CFG_VAL (1)
// </e>
// </h>

// <<< end of configuration section >>>

#endif // SL_BTMESH_GENERIC_LEVEL_CLIENT_EXT_CONFIG_H

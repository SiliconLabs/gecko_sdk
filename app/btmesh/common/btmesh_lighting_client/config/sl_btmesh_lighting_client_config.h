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
#ifndef SL_BTMESH_LIGHTING_CLIENT_CONFIG_H
#define SL_BTMESH_LIGHTING_CLIENT_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Light Lightness Client configuration

// <o SL_BTMESH_LIGHT_RETRANSMISSION_COUNT_CFG_VAL> Lighting model retransmission count
// <i> Default: 3
// <i> Lighting model retransmission count (How many times Lighting model messages are to be sent out for reliability).
#define SL_BTMESH_LIGHT_RETRANSMISSION_COUNT_CFG_VAL   (3)

// <o SL_BTMESH_LIGHT_RETRANSMISSION_TIMEOUT_CFG_VAL> Lighting model retransmission timeout
// <i> Default: 50
// <i> Lighting model retransmission timeout.
#define SL_BTMESH_LIGHT_RETRANSMISSION_TIMEOUT_CFG_VAL   (50)

// <o SL_BTMESH_ONOFF_RETRANSMISSION_COUNT_CFG_VAL> ONOFF model retransmission count
// <i> Default: 3
// <i> ONOFF model retransmission count (How many times ONOFF model messages are to be sent out for reliability).
#define SL_BTMESH_ONOFF_RETRANSMISSION_COUNT_CFG_VAL   (3)

// <o SL_BTMESH_ONOFF_RETRANSMISSION_TIMEOUT_CFG_VAL> ONOFF model retransmission timeout
// <i> Default: 50
// <i> ONOFF model retransmission timeout.
#define SL_BTMESH_ONOFF_RETRANSMISSION_TIMEOUT_CFG_VAL   (50)

// <e SL_BTMESH_LIGHTING_CLIENT_LOGGING_CFG_VAL> Enable Logging
// <i> Default: 1
// <i> Enable / disable Logging for Lighting Client model specific messages for this component.
#define SL_BTMESH_LIGHTING_CLIENT_LOGGING_CFG_VAL   (1)

// <s.128 SL_BTMESH_LIGHTING_ONOFF_LOGGING_CLIENT_PUBLISH_SUCCESS_CFG_VAL> Log text when sending a On/Off Model Message is successful.
// <i> Set Log text for successfully sending an On/Off Model Message.
#define SL_BTMESH_LIGHTING_ONOFF_LOGGING_CLIENT_PUBLISH_SUCCESS_CFG_VAL "CTL On/off request sent, trid = %u, delay = %u\r\n"

// </e>

// </h>

// <<< end of configuration section >>>

#endif // SL_BTMESH_LIGHTING_CLIENT_CONFIG_H

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

// <o LIGHT_RETRANSMISSION_COUNT> Lighting model restransmission count
// <i> Default: 3
// <i> Lighting model restransmission count (How many times Lighting model messages are to be sent out for reliability).
#define LIGHT_RETRANSMISSION_COUNT   (3)

// <o LIGHT_RETRANSMISSION_TIMEOUT> Lighting model restransmission timeout
// <i> Default: 50
// <i> Lighting model restransmission timeout.
#define LIGHT_RETRANSMISSION_TIMEOUT   (50)

// <o ONOFF_RETRANSMISSION_COUNT> ONOFF model restransmission count
// <i> Default: 3
// <i> ONOFF model restransmission count (How many times ONOFF model messages are to be sent out for reliability).
#define ONOFF_RETRANSMISSION_COUNT   (3)

// <o ONOFF_RETRANSMISSION_TIMEOUT> ONOFF model restransmission timeout
// <i> Default: 50
// <i> ONOFF model restransmission timeout.
#define ONOFF_RETRANSMISSION_TIMEOUT   (50)

// <q LIGHT_LIGHTNESS_WRAP_ENABLED> Enable lightness value wraparound
// <i> Default: 0
// <i> If the lightness reaches the max or min value then it wraps around.
#define LIGHT_LIGHTNESS_WRAP_ENABLED   (0)

// <e LIGHTING_CLIENT_LOGGING> Enable Logging
// <i> Default: 1
// <i> Enable / disable Logging for Lighting Client model specific messages for this component.
#define LIGHTING_CLIENT_LOGGING   (1)

// <s.128 ONOFF_LIGHTING_LOGGING_ON> Light should been switched on.
// <i> Set Log text when Light should been switched on
#define ONOFF_LIGHTING_LOGGING_ON "Turn light(s) on\r\n"

// <s.128 ONOFF_LIGHTING_LOGGING_OFF> Light should been switched off.
// <i> Set Log text when Light should been switched off
#define ONOFF_LIGHTING_LOGGING_OFF "Turn light(s) off\r\n"

// <s.128 LIGHTING_LOGGING_NEW_LIGHTNESS_SET> Log text when new lightness has been set.
// <i> Set Log text when new lightness has been set
#define LIGHTING_LOGGING_NEW_LIGHTNESS_SET "Set lightness to %u %% / level %u K\r\n"

// <s.128 LIGHTING_LOGGING_CLIENT_PUBLISH_FAIL> Log text when sending a lightness message fails.
// <i> Set Log text in case sending a lightness message fails
#define LIGHTING_LOGGING_CLIENT_PUBLISH_FAIL "Lightness Client Publish failed\r\n"

// <s.128 LIGHTING_LOGGING_CLIENT_PUBLISH_SUCCESS> Log text when sending a Lightness Model Message is successful.
// <i> Set Log text for sending a Lightness Model Message successfuly.
#define LIGHTING_LOGGING_CLIENT_PUBLISH_SUCCESS "Lightness request sent, trid = %u, delay = %u\r\n"

// <s.128 LIGHTING_ONOFF_LOGGING_CLIENT_PUBLISH_FAIL> Log text when sending a On/Off Model message fails.
// <i> Set Log text in case sending a On/Off Model message fails
#define LIGHTING_ONOFF_LOGGING_CLIENT_PUBLISH_FAIL "On/Off Client Publish failed\r\n"

// <s.128 LIGHTING_ONOFF_LOGGING_CLIENT_PUBLISH_SUCCESS> Log text when sending a On/Off Model Message is successful.
// <i> Set Log text for successfully sending an On/Off Model Message.
#define LIGHTING_ONOFF_LOGGING_CLIENT_PUBLISH_SUCCESS "CTL On/off request sent, trid = %u, delay = %u\r\n"

// </e>

// </h>

// <<< end of configuration section >>>

#endif // SL_BTMESH_LIGHTING_CLIENT_CONFIG_H

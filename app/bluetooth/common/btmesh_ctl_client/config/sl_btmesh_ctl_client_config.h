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
#ifndef SL_BTMESH_CTL_CLIENT_CONFIG_H
#define SL_BTMESH_CTL_CLIENT_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> CTL Client configuration

// <o CTL_CLIENT_RETRANSMISSION_COUNT> CTL model retransmission count
// <i> Default: 3
// <i> CTL model retransmission count (How many times CTL model messages are to be sent out for reliability).
#define CTL_CLIENT_RETRANSMISSION_COUNT   (3)

// <o CTL_CLIENT_RETRANSMISSION_TIMEOUT> CTL model retransmission timeout [ms] <0-1275:5>
// <i> Default: 50
// <i> CTL model retransmission timeout.
#define CTL_CLIENT_RETRANSMISSION_TIMEOUT   (50)

// <q CTL_CLIENT_TEMPERATURE_WRAP_ENABLED> Enable color temperature wraparound
// <i> Default: 0
// <i> If the color temperature reaches the max or min value then it wraps around.
#define CTL_CLIENT_TEMPERATURE_WRAP_ENABLED   (0)

// <e CTL_CLIENT_LOGGING> Enable Logging
// <i> Default: 1
// <i> Enable / disable Logging for CTL Client model specific messages for this component.
#define CTL_CLIENT_LOGGING   (1)

// <s.128 CTL_CLIENT_LOGGING_NEW_TEMP_SET> Log text when new color temperature has been set.
// <i> Set Log text when new color temperature has been set
#define CTL_CLIENT_LOGGING_NEW_TEMP_SET "Set temperature to %u %% / level %u K\r\n"

// <s.128 CTL_CLIENT_LOGGING_CLIENT_PUBLISH_FAIL> Log text when sending a CTL message fails.
// <i> Set Log text in case sending a CTL message fails
#define CTL_CLIENT_LOGGING_CLIENT_PUBLISH_FAIL "CTL Client Publish failed\r\n"

// <s.128 CTL_CLIENT_LOGGING_RECALL_SUCCESS> Log text when recalling a scene recall is successful.
// <i> Set Log text a scene recall is successful.
#define CTL_CLIENT_LOGGING_RECALL_SUCCESS "CTL request sent, trid = %u, delay = %u\r\n"

// </e>

// </h>

// <<< end of configuration section >>>

#endif // SL_BTMESH_CTL_CLIENT_CONFIG_H

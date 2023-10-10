/***************************************************************************//**
 * @file
 * @brief Bluetooth PAwR Advertiser configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in a
 *    product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_BT_PAWR_ADVERTISER_CONFIG_H
#define SL_BT_PAWR_ADVERTISER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth PAwR Advertiser Configuration

// <o SL_BT_CONFIG_MAX_PAWR_ADVERTISERS> Max number of PAwR advertisers <0-255>
// <i> Default: 0
// <i> Define the number of periodic advertising sets that the application needs to use concurrently for Periodic Advertising with Responses (PAwR). This number must not exceed the number of periodic advertising sets configured by SL_BT_CONFIG_MAX_PERIODIC_ADVERTISERS in the component "bluetooth_feature_periodic_adv" or the total number of advertising sets configured by SL_BT_CONFIG_USER_ADVERTISERS in the component "bluetooth_feature_advertiser".
#define SL_BT_CONFIG_MAX_PAWR_ADVERTISERS      (0)

// <o SL_BT_CONFIG_MAX_PAWR_ADVERTISED_DATA_LENGTH_HINT> Hint what will be the maximum length of advertised data in PAwR trains <0-251>
// <i> Default: 61 (suitable for ESL use)
// <i> Give a hint to the controller what is the maximum advertised data length in PAwR trains. The value is only a hint to the controller such that it can optimize task and concurrent connection scheduling. The value does not prevent using longer advertising data. The data length is restricted by the PAwR train parameters.
// <i> Value zero means that the maximum data equals to the length of <b>Response Slot Delay</b>.
#define SL_BT_CONFIG_MAX_PAWR_ADVERTISED_DATA_LENGTH_HINT (61)

// <o SL_BT_CONFIG_PAWR_PACKET_REQUEST_COUNT> Number of advertising packets requested from host at once <4-12>
// <i> Default: 4
// <i> Number of packets the controller requests from host in one LE Periodic Advertising Subevent Data Request event. The number is tradeoff between controller's memory consumption and number of HCI events sent by the controller. The given value is applied separately to each PAwR advertiser.
#define SL_BT_CONFIG_PAWR_PACKET_REQUEST_COUNT (4)

// <o SL_BT_CONFIG_PAWR_PACKET_REQUEST_ADVANCE> How much before airing a subevent, its data is requested from the host <1-6>
// <i> Default: 1
// <i> The controller asks the host to provide data for upcoming subevents before the subevents are to be sent to the air. The parameter can be used to configure how many subevents in advance the requests are sent to the host. The bigger the advance is, the more time the host has time to process the request, but the controller has to reserve more memory for buffering the subevent data. The smaller the advance is, the less time the host has time to process the request, but the controller has to reserve less memory for buffering subevent data.
#define SL_BT_CONFIG_PAWR_PACKET_REQUEST_ADVANCE    (1)

// </h> End Bluetooth PAwR Advertiser Configuration

// <<< end of configuration section >>>

#endif // SL_BT_PAWR_ADVERTISER_CONFIG_H

/***************************************************************************//**
 * @file
 * @brief Simple RAIL CPC for NCP projects Configuration
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

#ifndef SL_RAIL_SIMPLE_CPC_CONFIG_H
#define SL_RAIL_SIMPLE_CPC_CONFIG_H

#include "sli_cpc.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_RAIL_SIMPLE_CPC_RX_BUF_SIZE> Receive buffer size (bytes) <260-1024>
// <i> Default: 260
// <i> Define the size of the receive buffer in bytes.
#define SL_RAIL_SIMPLE_CPC_RX_BUF_SIZE        (260)

// <o SL_RAIL_SIMPLE_CPC_TX_BUF_SIZE> Transmit buffer size (bytes) <260-4096>
// <i> Default: 260
// <i> Define the size of the transmit buffer in bytes.
#define SL_RAIL_SIMPLE_CPC_TX_BUF_SIZE        (260)

// <o SL_RAIL_SIMPLE_CPC_CHANNEL> Selectable CPC channel for communication
// <SL_CPC_ENDPOINT_SYSTEM=> System control
// <SL_CPC_ENDPOINT_SECURITY=> Security - related functionality
// <SL_CPC_ENDPOINT_BLUETOOTH=> Bluetooth endpoint
// <SL_CPC_SLI_CPC_ENDPOINT_RAIL_DOWNSTREAM=> RAIL downstream endpoint
// <SL_CPC_SLI_CPC_ENDPOINT_RAIL_UPSTREAM=> RAIL upstream endpoint
// <SL_CPC_ENDPOINT_ZIGBEE=> ZigBee EZSP endpoint
// <SL_CPC_ENDPOINT_ZWAVE=> Z-Wave endpoint
// <SL_CPC_ENDPOINT_CONNECT=> Connect endpoint
// <SL_CPC_ENDPOINT_GPIO=> GPIO endpoint for controlling GPIOs on SECONDARYs
// <SL_CPC_ENDPOINT_OPENTHREAD=> Openthread Spinel endpoint
// <SL_CPC_ENDPOINT_WISUN=> WiSun endpoint
// <SL_CPC_ENDPOINT_WIFI=> WiFi endpoint(main control)
// <SL_CPC_ENDPOINT_15_4=> 802.15.4 endpoint
// <SL_CPC_ENDPOINT_CLI=> Ascii based CLI for stacks / applications
// <SL_CPC_ENDPOINT_BLUETOOTH_RCP=> Bluetooth RCP endpoint
// <SL_CPC_ENDPOINT_ACP=> ACP endpoint
// <SL_CPC_ENDPOINT_SE=> Secure Engine endpoint
// <i> Default: SL_CPC_SLI_CPC_ENDPOINT_RAIL_DOWNSTREAM
#define SL_RAIL_SIMPLE_CPC_CHANNEL        SL_CPC_SLI_CPC_ENDPOINT_RAIL_DOWNSTREAM

// <<< end of configuration section >>>

#endif // SL_RAIL_SIMPLE_CPC_CONFIG_H

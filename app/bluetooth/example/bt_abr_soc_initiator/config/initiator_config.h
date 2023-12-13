/***************************************************************************//**
 * @file
 * @brief ABR initiator example configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef ABR_INITIATOR_CONFIG
#define ABR_INITIATOR_CONFIG

#include "abr_initiator_config.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <e ABR_INITIATOR_MODE> Specify operation mode
// <i> Specify operation mode.
// <i> 0 - Button dependent
// <i> 1 - RTT
// <i> 2 - PBR
// <i> If this config is not set, PBR (2) is used.
#define ABR_INITIATOR_MODE     ABR_INITIATOR_MODE_DYNAMIC

// <o ABR_INITIATOR_DEFAULT_MODE> Ranging method
// <i> Default: 2 (PBR)
#define ABR_INITIATOR_DEFAULT_MODE     ABR_INITIATOR_MODE_PBR

// </e>

// <e ABR_RSSI_MEASUREMENT_ENABLED> Specifies whether distance should also be measured based on RSSI
// <i> Enable/disable RSSI distance measurement
// <i> 0 - RSSI distance measurement is disabled
// <i> 1 - RSSI distance measurement is enabled
#define ABR_RSSI_MEASUREMENT_ENABLED     (1)
// </e>

// <o ABR_RSSI_TX_POWER> Reference RSSI value of the Tx device at 1.0 m distance in dBm <-100-20>
// <i> Default: -40
// <i> Specifes Tx device RSSI at 1m in dBm
// <i> Default: -40 dBm
#define ABR_RSSI_TX_POWER               (-40)

// <<< end of configuration section >>>

#endif // ABR_INITIATOR_CONFIG

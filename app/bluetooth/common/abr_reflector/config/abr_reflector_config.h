/***************************************************************************//**
 * @file
 * @brief ABR reflector configuration
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

#ifndef ABR_REFLECTOR_CONFIG_H
#define ABR_REFLECTOR_CONFIG_H

#include "sl_bluetooth_config.h"

#define ABR_REFLECTOR_MAX_CONNECTIONS SL_BT_CONFIG_MAX_CONNECTIONS

// <<< Use Configuration Wizard in Context Menu >>>

// <h> ABR reflector configuration

// <o ABR_REFLECTOR_CS_EVENT_BUF_SIZE> Size of the Channel Sounding event buffer [elements] <1..255>
// <i> Default: 16
// <i> Size of the Channel Sounding event buffer
#define ABR_REFLECTOR_CS_EVENT_BUF_SIZE     (16)

// <o ABR_REFLECTOR_MIN_TX_POWER_DBM> Minimum transmit power of the reflector radio [dBm] <-127..20>
// <i> Default: -3
// <i> Minimum transmit power of the reflector radio
#define ABR_REFLECTOR_MIN_TX_POWER_DBM      (-3)

// <o ABR_REFLECTOR_MAX_TX_POWER_DBM> Maximum transmit power of the reflector radio [dBm] <-127..20>
// <i> Default: 20
// <i> Maximum transmit power of the reflector radio
#define ABR_REFLECTOR_MAX_TX_POWER_DBM      (20)

// <o ABR_REFLECTOR_ANTENNA_OFFSET> Specify antenna offset
// <0=> Wireless antenna offset
// <1=> Wired antenna offset
// <i> Default: 0
#define ABR_REFLECTOR_ANTENNA_OFFSET         0

// </h>

// <<< end of configuration section >>>
#endif // ABR_REFLECTOR_CONFIG_H

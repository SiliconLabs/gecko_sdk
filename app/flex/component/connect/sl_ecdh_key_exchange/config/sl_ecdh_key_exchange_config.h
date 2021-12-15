/***************************************************************************//**
 * @file
 * @brief Connect ECDH Key Exchange component configuration header.
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

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Connect Debug Print configuration

// <q SL_CONNECT_DEBUG_ECDH_PRINT_ENABLED> Prints enabled
// <i> Default: 0
// <i> If this option is enabled, all debug info is printed to the serial port
#define SL_CONNECT_DEBUG_ECDH_PRINT_ENABLED                              (0)

// <o SL_CONNECT_ECDH_PUBLIC_KEY_EXCHANGE_ENDPOINT> Public key exchange endpoint
// <i> Endpoint number of the public key exchange functionality
// <i> Default: 15
#define SL_CONNECT_ECDH_PUBLIC_KEY_EXCHANGE_ENDPOINT                     (15)

// <o SL_CONNECT_ECDH_NETWORK_KEY_EXCHANGE_ENDPOINT> Network key exchange endpoint
// <i> Endpoint number of the network key exchange functionality
// <i> Default: 14
#define SL_CONNECT_ECDH_NETWORK_KEY_EXCHANGE_ENDPOINT                    (14)

// <o SL_CONNECT_ECDH_DEFAULT_DATA_ENDPOINT> Default data endpoint
// <i> This endpoint handles the default data flow
// <i> Default: 13
#define SL_CONNECT_ECDH_DEFAULT_DATA_ENDPOINT                            (13)

// </h>

// <<< end of configuration section >>>

/***************************************************************************//**
 * @file
 * @brief ABR initiator component configuration
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

#ifndef ABR_INITIATOR_COMPONENT_CONFIG_H
#define ABR_INITIATOR_COMPONENT_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> ABR initiator component configuration

// <o ABR_INITIATOR_MIN_CS_INTERVAL> Minimum delay between CS measurements [connection events] <1..255>
// <i> Default: 15
// <i> Minimum duration in number of connection events between consecutive CS measurement procedures
#ifndef ABR_INITIATOR_MIN_CS_INTERVAL
#define ABR_INITIATOR_MIN_CS_INTERVAL     (15)
#endif

// <o ABR_INITIATOR_MAX_CS_INTERVAL> Maximum delay between CS measurements [connection events] <1..255>
// <i> Default: 15
// <i> Maximum duration in number of connection events between consecutive CS measurement procedures
#ifndef ABR_INITIATOR_MAX_CS_INTERVAL
#define ABR_INITIATOR_MAX_CS_INTERVAL     (15)
#endif

// <o ABR_INITIATOR_ANTENNA_OFFSET> Specify antenna offset
// <0=> Wireless antenna offset
// <1=> Wired antenna offset
// <i> Default: 0
#ifndef ABR_INITIATOR_ANTENNA_OFFSET
#define ABR_INITIATOR_ANTENNA_OFFSET       0
#endif

// </h>

// <<< end of configuration section >>>

#endif // ABR_INITIATOR_COMPONENT_CONFIG_H

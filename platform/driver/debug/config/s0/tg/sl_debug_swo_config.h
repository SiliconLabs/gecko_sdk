/***************************************************************************//**
 * @file
 * @brief SWO configuration
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

#ifndef SL_DEBUG_SWO_CONFIG_H
#define SL_DEBUG_SWO_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h>SWO Configuration

// <o SL_DEBUG_SWO_FREQ> SWO Frequency
// <i> Must be 875 kHz for communication with Silicon Labs debuggers
// <i> Default: 875000
#define SL_DEBUG_SWO_FREQ                       875000

// <q SL_DEBUG_SWO_SAMPLE_IRQ> Enable interrupt event trace
// <i> Default: 0
#define SL_DEBUG_SWO_SAMPLE_IRQ                 0

// <q SL_DEBUG_SWO_SAMPLE_PC> Enable Program Counter samples
// <i> Default: 0
#define SL_DEBUG_SWO_SAMPLE_PC                  0

// </h>

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <dbg signal=SWO> SL_DEBUG
// $[DBG_SL_DEBUG]
#define SL_DEBUG_PERIPHERAL                     DBG

#define SL_DEBUG_SWO_PORT                       gpioPortC
#define SL_DEBUG_SWO_PIN                        15
#define SL_DEBUG_ROUTE_LOC                      1
// [DBG_SL_DEBUG]$
// <<< sl:end pin_tool >>>

#endif // SL_DEBUG_SWO_CONFIG_H
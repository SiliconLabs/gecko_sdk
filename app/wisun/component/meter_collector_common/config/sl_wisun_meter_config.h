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
#ifndef SL_WISUN_METER_CONFIG_H
#define SL_WISUN_METER_CONFIG_H

#include "sl_component_catalog.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Wi-SUN Meter configuration
// <o SL_WISUN_METER_MAX_REG_COLLECTOR> Maximum count of registerable Collectors
// <i> Default: 3
#define SL_WISUN_METER_MAX_REG_COLLECTOR                                3U
// </h>

// <h>Wi-SUN Meter configuration
// <o SL_WISUN_METER_MEASUREMENT_BUFFER_SIZE> Maximum count of stored measurements
// <i> Default: 3
#define SL_WISUN_METER_MEASUREMENT_BUFFER_SIZE                          5U
// </h>

// <h>Wi-SUN Meter configuration
// <o SL_WISUN_METER_SCHEDULE_TIME> Time in ms between two measurement cyces
// <i> Default: 5000
#define SL_WISUN_METER_SCHEDULE_TIME                                    5000U
// </h>

// <<< end of configuration section >>>

#endif // SL_WISUN_METER_CONFIG_H

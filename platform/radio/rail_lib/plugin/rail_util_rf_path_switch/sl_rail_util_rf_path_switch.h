/***************************************************************************//**
 * @file sl_rail_util_rf_path_switch.h
 * @brief
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
#ifndef SL_RAIL_UTIL_RF_PATH_SWITCH_H
#define SL_RAIL_UTIL_RF_PATH_SWITCH_H

#include "rail.h"

#ifdef SL_CATALOG_RAIL_UTIL_RF_PATH_SWITCH_PRESENT
#include "sl_rail_util_rf_path_switch_config.h"
#endif // SL_CATALOG_RAIL_UTIL_RF_PATH_SWITCH_PRESENT

#if defined(SL_RAIL_UTIL_RF_PATH_SWITCH_CONTROL_PORT) \
  || defined(SL_RAIL_UTIL_RF_PATH_SWITCH_INVERTED_CONTROL_PORT)
#define SL_RAIL_UTIL_RF_PATH_SWITCH_PRESENT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the RAIL RF Path Switch Utility.
 *
 * @note: This function should be called during application initialization.
 */
void sl_rail_util_rf_path_switch_init(void);

#ifdef __cplusplus
}
#endif
#endif

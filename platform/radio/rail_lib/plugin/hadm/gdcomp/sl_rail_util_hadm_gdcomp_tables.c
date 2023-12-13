/***************************************************************************//**
 * @file
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

#include "rail.h"
#include "rail_ble.h"

#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 4)
#include "sl_rail_util_hadm_gdcomp_config.h"

// 0dBm PA LUTs
static const int16_t gdcompPbrPhaseLsb0Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_PBR_0DBM_PA;
static const int16_t gdcompRttSlope0Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_RTT_SLOPE_0DBM_PA;
static const int16_t gdcompRttOffset0Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_RTT_OFFSET_0DBM_PA;

const RAIL_BLE_HadmGdCompTables_t sl_rail_util_hadm_gdcomp_0dbm_tables = {
  .pPbrPhaseLsb = gdcompPbrPhaseLsb0Dbm,
  .pRttSlope = gdcompRttSlope0Dbm,
  .pRttOffset = gdcompRttOffset0Dbm,
  .length = SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH,
};

// 10dBm PA LUTs
static const int16_t gdcompPbrPhaseLsb10Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_PBR_10DBM_PA;
static const int16_t gdcompRttSlope10Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_RTT_SLOPE_10DBM_PA;
static const int16_t gdcompRttOffset10Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_RTT_OFFSET_10DBM_PA;

const RAIL_BLE_HadmGdCompTables_t sl_rail_util_hadm_gdcomp_10dbm_tables = {
  .pPbrPhaseLsb = gdcompPbrPhaseLsb10Dbm,
  .pRttSlope = gdcompRttSlope10Dbm,
  .pRttOffset = gdcompRttOffset10Dbm,
  .length = SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH,
};

// 20dBm PA LUTs
static const int16_t gdcompPbrPhaseLsb20Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_PBR_20DBM_PA;
static const int16_t gdcompRttSlope20Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_RTT_SLOPE_20DBM_PA;
static const int16_t gdcompRttOffset20Dbm[SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH] =
  SL_RAIL_UTIL_HADM_GDCOMP_RTT_OFFSET_20DBM_PA;

const RAIL_BLE_HadmGdCompTables_t sl_rail_util_hadm_gdcomp_20dbm_tables = {
  .pPbrPhaseLsb = gdcompPbrPhaseLsb20Dbm,
  .pRttSlope = gdcompRttSlope20Dbm,
  .pRttOffset = gdcompRttOffset20Dbm,
  .length = SL_RAIL_UTIL_HADM_GDCOMP_TABLE_LENGTH,
};

#endif // (_SILICON_LABS_32B_SERIES_2_CONFIG == 4)

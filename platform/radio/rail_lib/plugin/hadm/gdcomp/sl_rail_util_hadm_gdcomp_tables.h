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

#ifndef SL_RAIL_UTIL_HADM_GDCOMP_TABLES_H
#define SL_RAIL_UTIL_HADM_GDCOMP_TABLES_H

#ifdef __cplusplus
extern "C" {
#endif

#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 4)

extern const RAIL_BLE_HadmGdCompTables_t sl_rail_util_hadm_gdcomp_0dbm_tables;
extern const RAIL_BLE_HadmGdCompTables_t sl_rail_util_hadm_gdcomp_10dbm_tables;
extern const RAIL_BLE_HadmGdCompTables_t sl_rail_util_hadm_gdcomp_20dbm_tables;

#if SL_RAIL_UTIL_HADM_GDCOMP_LP_PA_DBM == 0
#define sl_rail_util_hadm_gdcomp_tables_lp_pa sl_rail_util_hadm_gdcomp_0dbm_tables
#else
#define sl_rail_util_hadm_gdcomp_tables_lp_pa NULL
#endif // SL_RAIL_UTIL_HADM_GDCOMP_LP_PA == 0

#if SL_RAIL_UTIL_HADM_GDCOMP_HP_PA_DBM == 10
#define sl_rail_util_hadm_gdcomp_tables_hp_pa sl_rail_util_hadm_gdcomp_10dbm_tables
#elif SL_RAIL_UTIL_HADM_GDCOMP_HP_PA_DBM == 20
#define sl_rail_util_hadm_gdcomp_tables_hp_pa sl_rail_util_hadm_gdcomp_20dbm_tables
#else
#define sl_rail_util_hadm_gdcomp_tables_hp_pa NULL
#endif // SL_RAIL_UTIL_HADM_GDCOMP_HP_PA == 10

#endif // (_SILICON_LABS_32B_SERIES_2_CONFIG == 4)

#ifdef __cplusplus
}
#endif

#endif // SL_RAIL_UTIL_HADM_GDCOMP_TABLES_H

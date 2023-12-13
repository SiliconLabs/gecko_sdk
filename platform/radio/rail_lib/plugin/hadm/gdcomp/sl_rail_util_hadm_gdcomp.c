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
#include "sl_rail_util_hadm_gdcomp_tables.h"

#if (!SL_RAIL_UTIL_HADM_GDCOMP_RUNTIME_PA_TABLE_SELECTION \
     && (defined(SL_RAIL_UTIL_HADM_GDCOMP_LP_PA_DBM)      \
  || defined(SL_RAIL_UTIL_HADM_GDCOMP_HP_PA_DBM)))
RAIL_Status_t RAILCb_BLE_HadmGdCompTableLoad(void)
{
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
#ifdef SL_RAIL_UTIL_HADM_GDCOMP_LP_PA_DBM
  status = RAIL_BLE_LoadHadmCompTables(RAIL_EFR32_HANDLE,
                                       &sl_rail_util_hadm_gdcomp_tables_lp_pa,
                                       RAIL_TX_POWER_MODE_2P4GIG_LP);
#endif
#ifdef SL_RAIL_UTIL_HADM_GDCOMP_HP_PA_DBM
  if (status == RAIL_STATUS_NO_ERROR) {
    status = RAIL_BLE_LoadHadmCompTables(RAIL_EFR32_HANDLE,
                                         &sl_rail_util_hadm_gdcomp_tables_hp_pa,
                                         RAIL_TX_POWER_MODE_2P4GIG_HP);
  }
#endif
  return status;
}
#endif

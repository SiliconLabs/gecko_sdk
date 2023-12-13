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
#include "sl_rail_util_hadm_antenna_offset_config.h"

const int16_t sl_rail_util_antenna_offset_cm[SL_RAIL_UTIL_HADM_ANTENNA_COUNT] =
#if SL_RAIL_UTIL_HADM_ANTENNA_WIRED_ENABLE
  SL_RAIL_UTIL_HADM_ANTENNA_OFFSET_WIRED_CM;
#else
  SL_RAIL_UTIL_HADM_ANTENNA_OFFSET_WIRELESS_CM;
#endif

void sl_rail_util_hadm_antenna_offset_init(void)
{
#if ((SL_RAIL_UTIL_HADM_ANTENNA_COUNT >= 1) \
  && (SL_RAIL_UTIL_HADM_ANTENNA_COUNT <= RAIL_BLE_HADM_MAX_ANTENNAS))
  RAIL_BLE_HadmAntennaConfig_t hadmAntennaConfig = {
    .antennaCount = SL_RAIL_UTIL_HADM_ANTENNA_COUNT,
    .pAntennaOffsetCm = sl_rail_util_antenna_offset_cm,
  };
  RAIL_BLE_ConfigHadmAntenna(RAIL_EFR32_HANDLE, &hadmAntennaConfig);
#endif
}

/***************************************************************************//**
 * @file
 * @brief Implements an API for initializing and controlling the EFF.
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

#include "sl_rail_util_eff_config.h"
#include "sl_rail_util_eff.h"

#ifndef SL_RAIL_UTIL_EFF_TEST_PORT
#error "SL_RAIL_UTIL_EFF_TEST undefined"
#endif //SL_RAIL_UTIL_EFF_TEST_PORT

#if ((SL_RAIL_UTIL_EFF_LNA_MODE_RURAL_ENABLE == 0) \
  && (SL_RAIL_UTIL_EFF_LNA_MODE_URBAN_ENABLE == 0) \
  && (SL_RAIL_UTIL_EFF_LNA_MODE_BYPASS_ENABLE == 0))
#error "At least one EFF LNA mode must be enabled"
#endif

#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_A
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_A 574
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_B
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_B -235763
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_C
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_C 38562724
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_D
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_D -1115923360L
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_DDBM 241
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_MV
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_MV 264
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_DDBM 291
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_MV
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_MV 451
#endif

#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_A
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_A 392
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_B
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_B -180237
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_C
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_C 32942736
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_D
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_D -1097941542L
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_DDBM 200
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_MV
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_MV 127
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_DDBM 241
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_MV
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_MV 170
#endif

#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_A
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_A 574
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_B
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_B -235763
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_C
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_C 38562724
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_D
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_D -1115923360L
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_DDBM 222
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_MV
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_MV 249
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_DDBM 290
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_MV
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_MV 507
#endif

#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_A
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_A 2178
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_B
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_B -1312415
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_C
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_C 271823274
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_D
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_D -17876500819L
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_DDBM 250
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_MV
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_MV 208
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_DDBM 289
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_MV
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_MV 366
#endif

RAIL_Status_t sl_rail_util_eff_init(void)
{
  RAIL_EffConfig_t effConfig = {
    .device = SL_RAIL_UTIL_EFF_DEVICE,
    .testPort = SL_RAIL_UTIL_EFF_TEST_PORT,
    .testPin = SL_RAIL_UTIL_EFF_TEST_PIN,
    .enabledLnaModes = (((SL_RAIL_UTIL_EFF_LNA_MODE_RURAL_ENABLE) ? RAIL_EFF_LNA_MODE_RURAL : 0U)
                        | ((SL_RAIL_UTIL_EFF_LNA_MODE_URBAN_ENABLE) ? RAIL_EFF_LNA_MODE_URBAN : 0U)
                        | ((SL_RAIL_UTIL_EFF_LNA_MODE_BYPASS_ENABLE) ? RAIL_EFF_LNA_MODE_BYPASS : 0U)),
    .ruralUrbanMv = SL_RAIL_UTIL_EFF_RURAL_URBAN_MV,
    .urbanBypassMv = SL_RAIL_UTIL_EFF_URBAN_BYPASS_MV,
    .urbanDwellTimeMs = SL_RAIL_UTIL_EFF_URBAN_DWELL_TIME_MS,
    .bypassDwellTimeMs = SL_RAIL_UTIL_EFF_BYPASS_DWELL_TIME_MS,
    .fskClpcConfig.antv.coefA = SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_A,
    .fskClpcConfig.antv.coefB = SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_B,
    .fskClpcConfig.antv.coefC = SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_C,
    .fskClpcConfig.antv.coefD = SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_D,
    .fskClpcConfig.antv.calData.cal1Ddbm = SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_DDBM,
    .fskClpcConfig.antv.calData.cal1Mv = SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_MV,
    .fskClpcConfig.antv.calData.cal2Ddbm = SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_DDBM,
    .fskClpcConfig.antv.calData.cal2Mv = SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_MV,

    .fskClpcConfig.saw2.coefA = SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_A,
    .fskClpcConfig.saw2.coefB = SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_B,
    .fskClpcConfig.saw2.coefC = SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_C,
    .fskClpcConfig.saw2.coefD = SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_D,
    .fskClpcConfig.saw2.calData.cal1Ddbm = SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_DDBM,
    .fskClpcConfig.saw2.calData.cal1Mv = SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_MV,
    .fskClpcConfig.saw2.calData.cal2Ddbm = SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_DDBM,
    .fskClpcConfig.saw2.calData.cal2Mv = SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_MV,

    .ofdmClpcConfig.antv.coefA = SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_A,
    .ofdmClpcConfig.antv.coefB = SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_B,
    .ofdmClpcConfig.antv.coefC = SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_C,
    .ofdmClpcConfig.antv.coefD = SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_D,
    .ofdmClpcConfig.antv.calData.cal1Ddbm = SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_DDBM,
    .ofdmClpcConfig.antv.calData.cal1Mv = SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_MV,
    .ofdmClpcConfig.antv.calData.cal2Ddbm = SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_DDBM,
    .ofdmClpcConfig.antv.calData.cal2Mv = SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_MV,

    .ofdmClpcConfig.saw2.coefA = SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_A,
    .ofdmClpcConfig.saw2.coefB = SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_B,
    .ofdmClpcConfig.saw2.coefC = SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_C,
    .ofdmClpcConfig.saw2.coefD = SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_D,
    .ofdmClpcConfig.saw2.calData.cal1Ddbm = SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_DDBM,
    .ofdmClpcConfig.saw2.calData.cal1Mv = SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_MV,
    .ofdmClpcConfig.saw2.calData.cal2Ddbm = SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_DDBM,
    .ofdmClpcConfig.saw2.calData.cal2Mv = SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_MV,

    .clpcEnable = SL_RAIL_UTIL_EFF_CLPC_ENABLE,
    .tempThresholdK = SL_RAIL_UTIL_EFF_TEMPERATURE_THRESHOLD_EFF_DEGREES_K,
  };

  return RAIL_ConfigEff(RAIL_EFR32_HANDLE, &effConfig);
}

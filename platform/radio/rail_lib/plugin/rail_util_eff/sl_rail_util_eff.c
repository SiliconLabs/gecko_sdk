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

#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_A
#define SL_RAIL_UTIL_EFF_CLPC_FSK_A 844
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_B
#define SL_RAIL_UTIL_EFF_CLPC_FSK_B -437473
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_C
#define SL_RAIL_UTIL_EFF_CLPC_FSK_C 87928015
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_D
#define SL_RAIL_UTIL_EFF_CLPC_FSK_D -5063115821L
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL1_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL1_DDBM 270
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL1
#define SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL1 340
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL2_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL2_DDBM 290
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL2
#define SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL2 423
#endif

#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_A
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_A 844
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_B
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_B -437473
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_C
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_C 87928015
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_D
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_D -5063115821L
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL1_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL1_DDBM 270
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL1
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL1 450
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL2_DDBM
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL2_DDBM 290
#endif
#ifndef SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL2
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL2 544
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
    .fskClpcConfig.antvA = SL_RAIL_UTIL_EFF_CLPC_FSK_A,
    .fskClpcConfig.antvB = SL_RAIL_UTIL_EFF_CLPC_FSK_B,
    .fskClpcConfig.antvC = SL_RAIL_UTIL_EFF_CLPC_FSK_C,
    .fskClpcConfig.antvD = SL_RAIL_UTIL_EFF_CLPC_FSK_D,

    .fskClpcConfig.calData.cal1Ddbm = SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL1_DDBM,
    .fskClpcConfig.calData.cal1 = SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL1,
    .fskClpcConfig.calData.cal2Ddbm = SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL2_DDBM,
    .fskClpcConfig.calData.cal2 = SL_RAIL_UTIL_EFF_CLPC_FSK_1_CAL2,

    .ofdmClpcConfig.antvA = SL_RAIL_UTIL_EFF_CLPC_OFDM_A,
    .ofdmClpcConfig.antvB = SL_RAIL_UTIL_EFF_CLPC_OFDM_B,
    .ofdmClpcConfig.antvC = SL_RAIL_UTIL_EFF_CLPC_OFDM_C,
    .ofdmClpcConfig.antvD = SL_RAIL_UTIL_EFF_CLPC_OFDM_D,
    .ofdmClpcConfig.calData.cal1Ddbm = SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL1_DDBM,
    .ofdmClpcConfig.calData.cal1 = SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL1,
    .ofdmClpcConfig.calData.cal2Ddbm = SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL2_DDBM,
    .ofdmClpcConfig.calData.cal2 = SL_RAIL_UTIL_EFF_CLPC_OFDM_1_CAL2,
    .clpcEnable = SL_RAIL_UTIL_EFF_CLPC_ENABLE,
    .maxTxContinuousPowerDbm = RAIL_UTIL_EFF_MAX_TX_CONTINUOUS_POWER_DBM,
    .maxTxDutyCycle = RAIL_UTIL_EFF_MAX_TX_DUTY_CYCLE,
    .tempThresholdK = SL_RAIL_UTIL_EFF_TEMPERATURE_THRESHOLD_EFF_DEGREES_K,
  };

  return RAIL_ConfigEff(RAIL_EFR32_HANDLE, &effConfig);
}

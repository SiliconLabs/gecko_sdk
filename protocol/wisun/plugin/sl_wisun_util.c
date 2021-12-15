/***************************************************************************//**
 * @file sl_wisun_util.c
 * @brief Wi-SUN utilities
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

#include <stddef.h>
#include <stdint.h>
#include "rail_config.h"
#include "sl_wisun_api.h"
#include "sl_wisun_util.h"
#include "sli_wisun_internal_api.h"
#include "SEGGER_RTT.h"

#define RTT_LogChannel ((unsigned int) 0)

#define SLI_WISUN_ERROR_CHECK_SET_STATUS(__result, __value)\
do {\
  if (!(__result)){\
    status = __value;\
    goto error_handler;\
  }\
} while(0)

#define SLI_WISUN_ERROR_SET_STATUS(__value)\
do {\
  status = __value;\
  goto error_handler;\
} while(0)

/** Matches a RAIL configuration with Wi-SUN frequency band settings. */
typedef struct sli_wisun_rf_settings {
  uint32_t channel_0_center_frequency;  ///< Center frequency
  uint32_t channel_spacing;             ///< Channel spacing
  uint32_t datarate;                    ///< Data rate
  uint16_t number_of_channels;          ///< Number of channels
  uint8_t reg_domain;                   ///< Regulatory domain
  uint8_t op_class;                     ///< Operating class
  uint16_t op_mode;                     ///< Operating mode
} sli_wisun_rf_settings_t;

static const sli_wisun_rf_settings_t rf_settings_CN_1_1b = {
  .channel_0_center_frequency=470200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=199, .reg_domain=4, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_CN_1_2a = {
  .channel_0_center_frequency=470200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=199, .reg_domain=4, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_CN_1_3 = {
  .channel_0_center_frequency=470200000, .channel_spacing=200000, .datarate=150000, .number_of_channels=199, .reg_domain=4, .op_class=1, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_CN_2_1b = {
  .channel_0_center_frequency=779200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=39, .reg_domain=4, .op_class=2, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_CN_2_2a = {
  .channel_0_center_frequency=779200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=39, .reg_domain=4, .op_class=2, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_CN_3_3 = {
  .channel_0_center_frequency=779400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=19, .reg_domain=4, .op_class=3, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_CN_3_4a = {
  .channel_0_center_frequency=779400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=19, .reg_domain=4, .op_class=3, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_CN_3_5 = {
  .channel_0_center_frequency=779400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=19, .reg_domain=4, .op_class=3, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_CN_4_1b = {
  .channel_0_center_frequency=920625000, .channel_spacing=250000, .datarate=50000, .number_of_channels=16, .reg_domain=4, .op_class=4, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_CN_4_2a = {
  .channel_0_center_frequency=920625000, .channel_spacing=250000, .datarate=100000, .number_of_channels=16, .reg_domain=4, .op_class=4, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_CN_4_3 = {
  .channel_0_center_frequency=920625000, .channel_spacing=250000, .datarate=150000, .number_of_channels=16, .reg_domain=4, .op_class=4, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_EU_1_1a = {
  .channel_0_center_frequency=863100000, .channel_spacing=100000, .datarate=50000, .number_of_channels=69, .reg_domain=3, .op_class=1, .op_mode=0x1a
};
static const sli_wisun_rf_settings_t rf_settings_EU_2_2a = {
  .channel_0_center_frequency=863100000, .channel_spacing=200000, .datarate=100000, .number_of_channels=35, .reg_domain=3, .op_class=2, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_EU_2_3 = {
  .channel_0_center_frequency=863100000, .channel_spacing=200000, .datarate=150000, .number_of_channels=35, .reg_domain=3, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_EU_3_1a = {
  .channel_0_center_frequency=870100000, .channel_spacing=100000, .datarate=50000, .number_of_channels=55, .reg_domain=3, .op_class=3, .op_mode=0x1a
};
static const sli_wisun_rf_settings_t rf_settings_EU_4_2a = {
  .channel_0_center_frequency=870200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=27, .reg_domain=3, .op_class=4, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_EU_4_3 = {
  .channel_0_center_frequency=870200000, .channel_spacing=200000, .datarate=150000, .number_of_channels=27, .reg_domain=3, .op_class=4, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_IN_1_1a = {
  .channel_0_center_frequency=865100000, .channel_spacing=100000, .datarate=50000, .number_of_channels=19, .reg_domain=5, .op_class=1, .op_mode=0x1a
};
static const sli_wisun_rf_settings_t rf_settings_IN_2_2a = {
  .channel_0_center_frequency=865100000, .channel_spacing=200000, .datarate=100000, .number_of_channels=10, .reg_domain=5, .op_class=2, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_IN_2_3 = {
  .channel_0_center_frequency=865100000, .channel_spacing=200000, .datarate=150000, .number_of_channels=10, .reg_domain=5, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_NA_1_1b = {
  .channel_0_center_frequency=902200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=129, .reg_domain=1, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_NA_1_2a = {
  .channel_0_center_frequency=902200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=129, .reg_domain=1, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_NA_2_3 = {
  .channel_0_center_frequency=902400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=64, .reg_domain=1, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_NA_2_4a = {
  .channel_0_center_frequency=902400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=64, .reg_domain=1, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_NA_3_5 = {
  .channel_0_center_frequency=902600000, .channel_spacing=600000, .datarate=300000, .number_of_channels=42, .reg_domain=1, .op_class=3, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_WW_1_1b = {
  .channel_0_center_frequency=2400200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=416, .reg_domain=0, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_WW_1_2a = {
  .channel_0_center_frequency=2400200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=416, .reg_domain=0, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_WW_2_3 = {
  .channel_0_center_frequency=2400400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=207, .reg_domain=0, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_WW_2_4a = {
  .channel_0_center_frequency=2400400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=207, .reg_domain=0, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_WW_2_5 = {
  .channel_0_center_frequency=2400400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=207, .reg_domain=0, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_JP_1_1b = {
  .channel_0_center_frequency=920600000, .channel_spacing=200000, .datarate=50000, .number_of_channels=38, .reg_domain=2, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_JP_3_4b = {
  .channel_0_center_frequency=920800000, .channel_spacing=600000, .datarate=200000, .number_of_channels=12, .reg_domain=2, .op_class=3, .op_mode=0x4b
};
static const sli_wisun_rf_settings_t rf_settings_JP_3_5 = {
  .channel_0_center_frequency=920800000, .channel_spacing=600000, .datarate=300000, .number_of_channels=12, .reg_domain=2, .op_class=3, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_JP_2_2b = {
  .channel_0_center_frequency=920900000, .channel_spacing=400000, .datarate=100000, .number_of_channels=18, .reg_domain=2, .op_class=2, .op_mode=0x2b
};
static const sli_wisun_rf_settings_t rf_settings_JP_2_3 = {
  .channel_0_center_frequency=920900000, .channel_spacing=400000, .datarate=150000, .number_of_channels=18, .reg_domain=2, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_MX_1_1b = {
  .channel_0_center_frequency=902200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=129, .reg_domain=6, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_MX_1_2a = {
  .channel_0_center_frequency=902200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=129, .reg_domain=6, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_MX_2_3 = {
  .channel_0_center_frequency=902400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=64, .reg_domain=6, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_MX_2_4a = {
  .channel_0_center_frequency=902400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=64, .reg_domain=6, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_MX_2_5 = {
  .channel_0_center_frequency=902400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=64, .reg_domain=6, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_BZ_1_1b = {
  .channel_0_center_frequency=902200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=129, .reg_domain=7, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_BZ_1_2a = {
  .channel_0_center_frequency=902200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=129, .reg_domain=7, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_BZ_2_3 = {
  .channel_0_center_frequency=902400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=64, .reg_domain=7, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_BZ_2_4a = {
  .channel_0_center_frequency=902400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=64, .reg_domain=7, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_BZ_3_5 = {
  .channel_0_center_frequency=902600000, .channel_spacing=600000, .datarate=300000, .number_of_channels=42, .reg_domain=7, .op_class=3, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_AZ_1_1b = {
  .channel_0_center_frequency=915200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=64, .reg_domain=8, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_AZ_1_2a = {
  .channel_0_center_frequency=915200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=64, .reg_domain=8, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_AZ_2_3 = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=32, .reg_domain=8, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_AZ_2_4a = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=32, .reg_domain=8, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_AZ_2_5 = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=32, .reg_domain=8, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_NZ_1_1b = {
  .channel_0_center_frequency=915200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=64, .reg_domain=8, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_NZ_1_2a = {
  .channel_0_center_frequency=915200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=64, .reg_domain=8, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_NZ_2_3 = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=32, .reg_domain=8, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_NZ_2_4a = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=32, .reg_domain=8, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_NZ_2_5 = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=32, .reg_domain=8, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_KR_1_1b = {
  .channel_0_center_frequency=917100000, .channel_spacing=200000, .datarate=50000, .number_of_channels=32, .reg_domain=9, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_KR_1_2a = {
  .channel_0_center_frequency=917100000, .channel_spacing=200000, .datarate=100000, .number_of_channels=32, .reg_domain=9, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_KR_2_3 = {
  .channel_0_center_frequency=917300000, .channel_spacing=400000, .datarate=150000, .number_of_channels=16, .reg_domain=9, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_KR_2_4a = {
  .channel_0_center_frequency=917300000, .channel_spacing=400000, .datarate=200000, .number_of_channels=16, .reg_domain=9, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_KR_2_5 = {
  .channel_0_center_frequency=917300000, .channel_spacing=400000, .datarate=300000, .number_of_channels=16, .reg_domain=9, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_PH_1_1b = {
  .channel_0_center_frequency=915200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=14, .reg_domain=10, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_PH_1_2a = {
  .channel_0_center_frequency=915200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=14, .reg_domain=10, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_PH_2_3 = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=7, .reg_domain=10, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_PH_2_4a = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=7, .reg_domain=10, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_PH_2_5 = {
  .channel_0_center_frequency=915400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=7, .reg_domain=10, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_MY_1_1b = {
  .channel_0_center_frequency=919200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=19, .reg_domain=11, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_MY_1_2a = {
  .channel_0_center_frequency=919200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=19, .reg_domain=11, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_MY_2_3 = {
  .channel_0_center_frequency=919400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=10, .reg_domain=11, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_MY_2_4a = {
  .channel_0_center_frequency=919400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=10, .reg_domain=11, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_MY_2_5 = {
  .channel_0_center_frequency=919400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=10, .reg_domain=11, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_HK_1_1b = {
  .channel_0_center_frequency=920200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=24, .reg_domain=12, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_HK_1_2a = {
  .channel_0_center_frequency=920200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=24, .reg_domain=12, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_HK_2_3 = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=12, .reg_domain=12, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_HK_2_4a = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=12, .reg_domain=12, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_HK_2_5 = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=12, .reg_domain=12, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_SG_1_1a = {
  .channel_0_center_frequency=866100000, .channel_spacing=100000, .datarate=50000, .number_of_channels=29, .reg_domain=13, .op_class=1, .op_mode=0x1a
};
static const sli_wisun_rf_settings_t rf_settings_SG_2_2a = {
  .channel_0_center_frequency=866100000, .channel_spacing=200000, .datarate=100000, .number_of_channels=15, .reg_domain=13, .op_class=2, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_SG_2_3 = {
  .channel_0_center_frequency=866100000, .channel_spacing=200000, .datarate=150000, .number_of_channels=15, .reg_domain=13, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_SG_3_4a = {
  .channel_0_center_frequency=866300000, .channel_spacing=400000, .datarate=200000, .number_of_channels=7, .reg_domain=13, .op_class=3, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_SG_3_5 = {
  .channel_0_center_frequency=866300000, .channel_spacing=400000, .datarate=300000, .number_of_channels=7, .reg_domain=13, .op_class=3, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_SG_4_1b = {
  .channel_0_center_frequency=920200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=24, .reg_domain=13, .op_class=4, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_SG_4_2a = {
  .channel_0_center_frequency=920200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=24, .reg_domain=13, .op_class=4, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_SG_5_3 = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=12, .reg_domain=13, .op_class=5, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_SG_5_4a = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=12, .reg_domain=13, .op_class=5, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_SG_5_5 = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=12, .reg_domain=13, .op_class=5, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_TH_1_1b = {
  .channel_0_center_frequency=920200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=24, .reg_domain=14, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_TH_1_2a = {
  .channel_0_center_frequency=920200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=24, .reg_domain=14, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_TH_2_3 = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=12, .reg_domain=14, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_TH_2_4a = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=12, .reg_domain=14, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_TH_2_5 = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=12, .reg_domain=14, .op_class=2, .op_mode=0x5
};
static const sli_wisun_rf_settings_t rf_settings_VN_1_1b = {
  .channel_0_center_frequency=920200000, .channel_spacing=200000, .datarate=50000, .number_of_channels=24, .reg_domain=15, .op_class=1, .op_mode=0x1b
};
static const sli_wisun_rf_settings_t rf_settings_VN_1_2a = {
  .channel_0_center_frequency=920200000, .channel_spacing=200000, .datarate=100000, .number_of_channels=24, .reg_domain=15, .op_class=1, .op_mode=0x2a
};
static const sli_wisun_rf_settings_t rf_settings_VN_2_3 = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=150000, .number_of_channels=12, .reg_domain=15, .op_class=2, .op_mode=0x3
};
static const sli_wisun_rf_settings_t rf_settings_VN_2_4a = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=200000, .number_of_channels=12, .reg_domain=15, .op_class=2, .op_mode=0x4a
};
static const sli_wisun_rf_settings_t rf_settings_VN_2_5 = {
  .channel_0_center_frequency=920400000, .channel_spacing=400000, .datarate=300000, .number_of_channels=12, .reg_domain=15, .op_class=2, .op_mode=0x5
};

/** Supported Wi-SUN frequency band settings. */
static const sli_wisun_rf_settings_t *rf_settings[] = {
  &rf_settings_CN_1_1b,
  &rf_settings_CN_1_2a,
  &rf_settings_CN_1_3,
  &rf_settings_CN_2_1b,
  &rf_settings_CN_2_2a,
  &rf_settings_CN_3_3,
  &rf_settings_CN_3_4a,
  &rf_settings_CN_3_5,
  &rf_settings_CN_4_1b,
  &rf_settings_CN_4_2a,
  &rf_settings_CN_4_3,
  &rf_settings_EU_1_1a,
  &rf_settings_EU_2_2a,
  &rf_settings_EU_2_3,
  &rf_settings_EU_3_1a,
  &rf_settings_EU_4_2a,
  &rf_settings_EU_4_3,
  &rf_settings_IN_1_1a,
  &rf_settings_IN_2_2a,
  &rf_settings_IN_2_3,
  &rf_settings_NA_1_1b,
  &rf_settings_NA_1_2a,
  &rf_settings_NA_2_3,
  &rf_settings_NA_2_4a,
  &rf_settings_NA_3_5,
  &rf_settings_WW_1_1b,
  &rf_settings_WW_1_2a,
  &rf_settings_WW_2_3,
  &rf_settings_WW_2_4a,
  &rf_settings_WW_2_5,
  &rf_settings_JP_1_1b,
  &rf_settings_JP_2_2b,
  &rf_settings_JP_2_3,
  &rf_settings_JP_3_4b,
  &rf_settings_JP_3_5,
  &rf_settings_MX_1_1b,
  &rf_settings_MX_1_2a,
  &rf_settings_MX_2_3,
  &rf_settings_MX_2_4a,
  &rf_settings_MX_2_5,
  &rf_settings_BZ_1_1b,
  &rf_settings_BZ_1_2a,
  &rf_settings_BZ_2_3,
  &rf_settings_BZ_2_4a,
  &rf_settings_BZ_3_5,
  &rf_settings_AZ_1_1b,
  &rf_settings_AZ_1_2a,
  &rf_settings_AZ_2_3,
  &rf_settings_AZ_2_4a,
  &rf_settings_AZ_2_5,
  &rf_settings_NZ_1_1b,
  &rf_settings_NZ_1_2a,
  &rf_settings_NZ_2_3,
  &rf_settings_NZ_2_4a,
  &rf_settings_NZ_2_5,
  &rf_settings_KR_1_1b,
  &rf_settings_KR_1_2a,
  &rf_settings_KR_2_3,
  &rf_settings_KR_2_4a,
  &rf_settings_KR_2_5,
  &rf_settings_PH_1_1b,
  &rf_settings_PH_1_2a,
  &rf_settings_PH_2_3,
  &rf_settings_PH_2_4a,
  &rf_settings_PH_2_5,
  &rf_settings_MY_1_1b,
  &rf_settings_MY_1_2a,
  &rf_settings_MY_2_3,
  &rf_settings_MY_2_4a,
  &rf_settings_MY_2_5,
  &rf_settings_HK_1_1b,
  &rf_settings_HK_1_2a,
  &rf_settings_HK_2_3,
  &rf_settings_HK_2_4a,
  &rf_settings_HK_2_5,
  &rf_settings_SG_1_1a,
  &rf_settings_SG_2_2a,
  &rf_settings_SG_2_3,
  &rf_settings_SG_3_4a,
  &rf_settings_SG_3_5,
  &rf_settings_SG_4_1b,
  &rf_settings_SG_4_2a,
  &rf_settings_SG_5_3,
  &rf_settings_SG_5_4a,
  &rf_settings_SG_5_5,
  &rf_settings_TH_1_1b,
  &rf_settings_TH_1_2a,
  &rf_settings_TH_2_3,
  &rf_settings_TH_2_4a,
  &rf_settings_TH_2_5,
  &rf_settings_VN_1_1b,
  &rf_settings_VN_1_2a,
  &rf_settings_VN_2_3,
  &rf_settings_VN_2_4a,
  &rf_settings_VN_2_5,
  NULL
};

sl_status_t sl_wisun_util_get_rf_settings(uint8_t *reg_domain, uint8_t *op_class, uint16_t *op_mode)
{
  sl_status_t status = SL_STATUS_OK;
  RAIL_Handle_t rail_handle;
  const RAIL_ChannelConfig_t *channel_config;
  RAIL_Status_t ret;
  uint32_t datarate;
  uint16_t number_of_channels;
  const sli_wisun_rf_settings_t *iter=NULL;
  int index = 0;
  SEGGER_RTT_printf(RTT_LogChannel, "sl_wisun_util_get_rf_settings()");

  status = sli_wisun_get_rail_handle(&rail_handle);
  SLI_WISUN_ERROR_CHECK_SET_STATUS(status == SL_STATUS_OK, SL_STATUS_FAIL);

  /* Take first RAIL configuration as reference. */
  channel_config = channelConfigs[0];
  ret = RAIL_ConfigChannels(rail_handle, channel_config, NULL);
  SLI_WISUN_ERROR_CHECK_SET_STATUS(ret == RAIL_STATUS_NO_ERROR, SL_STATUS_FAIL);

  datarate = RAIL_GetBitRate(rail_handle);
  SLI_WISUN_ERROR_CHECK_SET_STATUS(datarate, SL_STATUS_FAIL);
  number_of_channels = channel_config->configs->channelNumberEnd - channel_config->configs->channelNumberStart + 1;

  /* Iterate through supported Wi-SUN frequency band settings to find
    * the matching RAIL configuration. */
  iter = rf_settings[index];
  while (iter) {
    if ((channel_config->configs->baseFrequency == iter->channel_0_center_frequency) &&
        (channel_config->configs->channelSpacing == iter->channel_spacing) &&
        (datarate == iter->datarate) &&
        (number_of_channels == iter->number_of_channels)) {
      /* Matching Wi-SUN frequency band settings found. */
      *reg_domain = iter->reg_domain;
      *op_class = iter->op_class;
      *op_mode = iter->op_mode;
      SEGGER_RTT_printf(RTT_LogChannel, "Using reg_domain %u, op_class %u, op_mode %x", *reg_domain, *op_class, *op_mode);
      break;
    }
    iter = rf_settings[++index];
  }

  if (!iter) {
    SEGGER_RTT_printf(RTT_LogChannel, "No matching WI-SUN frequency band settings");
    SLI_WISUN_ERROR_SET_STATUS(SL_STATUS_FAIL);
  }

error_handler:

  return status;
}

sl_status_t sl_wisun_util_connect(const uint8_t * network_name)
{
  sl_status_t status;
  uint8_t reg_domain;
  uint8_t op_class;
  uint16_t op_mode;

  SEGGER_RTT_printf(RTT_LogChannel, "sl_wisun_util_connect()");

  status = sl_wisun_util_get_rf_settings(&reg_domain, &op_class, &op_mode);
  SLI_WISUN_ERROR_CHECK_SET_STATUS(status == SL_STATUS_OK, SL_STATUS_FAIL);

  status = sl_wisun_connect(network_name, (sl_wisun_regulatory_domain_t)reg_domain, (sl_wisun_operating_class_t)op_class, (sl_wisun_operating_mode_t)op_mode);

error_handler:

  return status;
}

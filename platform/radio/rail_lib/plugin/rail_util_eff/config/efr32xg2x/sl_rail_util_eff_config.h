/***************************************************************************//**
 * @file
 * @brief RAIL Util for EFF0 configuration file.
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

#ifndef SL_RAIL_UTIL_EFF_CONFIG_H
#define SL_RAIL_UTIL_EFF_CONFIG_H

#include "em_gpio.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <h> EFF Configuration
// <o SL_RAIL_UTIL_EFF_DEVICE> Select connected EFF device
// <RAIL_EFF_DEVICE_NONE=> No connected EFF device
// <RAIL_EFF_DEVICE_EFF01A11NMFA0=> +30 dBm,   LNA, QFN24, +105C max ambient
// <RAIL_EFF_DEVICE_EFF01B11NMFA0=> PA Bypass, LNA, QFN24, +105C max ambient
// <RAIL_EFF_DEVICE_EFF01A11IMFB0=> +30 dBm,   LNA, QFN24, +125C max ambient
// <RAIL_EFF_DEVICE_EFF01B11IMFB0=> PA Bypass, LNA, QFN24, +125C max ambient
// <i> Default: RAIL_EFF_DEVICE_EFF01A11IMFB0
#define SL_RAIL_UTIL_EFF_DEVICE   RAIL_EFF_DEVICE_EFF01A11IMFB0
// <q SL_RAIL_UTIL_EFF_LNA_MODE_RURAL_ENABLE> Enable Rural LNA Mode
// <i> Default: 1
#define SL_RAIL_UTIL_EFF_LNA_MODE_RURAL_ENABLE  1
// <q SL_RAIL_UTIL_EFF_LNA_MODE_URBAN_ENABLE> Enable Urban LNA Mode
// <i> Default: 1
#define SL_RAIL_UTIL_EFF_LNA_MODE_URBAN_ENABLE  1
// <q SL_RAIL_UTIL_EFF_LNA_MODE_BYPASS_ENABLE> Enable Bypass LNA Mode
// <i> Default: 1
#define SL_RAIL_UTIL_EFF_LNA_MODE_BYPASS_ENABLE 1
// <o SL_RAIL_UTIL_EFF_RURAL_URBAN_MV> Trip point between rural and urban modes, in millivolts.
// <5..1250:1>
// <i> Default: 120
#define SL_RAIL_UTIL_EFF_RURAL_URBAN_MV 120
// <o SL_RAIL_UTIL_EFF_URBAN_BYPASS_MV> Trip point between urban and bypass modes, in millivolts.
// <5..1250:1>
// <i> Default: 130
#define SL_RAIL_UTIL_EFF_URBAN_BYPASS_MV 130
// <o SL_RAIL_UTIL_EFF_URBAN_DWELL_TIME_MS> Length of time to stay in urban mode before transitioning to rural mode, in milliseconds.
// <1..105000:1>
// <i> Default: 30000
#define SL_RAIL_UTIL_EFF_URBAN_DWELL_TIME_MS 30000
// <o SL_RAIL_UTIL_EFF_BYPASS_DWELL_TIME_MS> Length of time to stay in bypass mode before transitioning to urban or rural mode, in milliseconds.
// <1..105000:1>
// <i> Default: 30000
#define SL_RAIL_UTIL_EFF_BYPASS_DWELL_TIME_MS 30000

// <o SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_A> Coefficient A for FSK ANTV sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: 574
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_A 574
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_B> Coefficient B for FSK ANTV sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: -235763
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_B -235763
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_C> Coefficient C for FSK ANTV sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: 38562724
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_C 38562724
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_D> Coefficient D for FSK ANTV sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: -1115923360
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_D -1115923360L
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_DDBM> Entry 1 measured FSK ANTV Output Power for CAL1 (nominally 270 ddBm).
// <180..350:1>
// <i> Default: 241
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_DDBM 241
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_MV> Entry 1 measured FSK ANTV sensor voltage at CAL1 ddBm, in millivolts.
// <1..65535:1>
// <i> Default: 264
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL1_MV 264
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_DDBM> Entry 1 measured FSK ANTV Output Power for CAL2 (nominally 290 ddBm).
// <180..350:1>
// <i> Default: 291
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_DDBM 291
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_MV> Entry 1 measured FSK ANTV sensor voltage at CAL2 ddBm, in millivolts.
// <1..65535:1>
// <i> Default: 451
#define SL_RAIL_UTIL_EFF_CLPC_FSK_ANTV_1_CAL2_MV 451

// <o SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_A> Coefficient A for FSK SAW2 sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: 392
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_A 392
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_B> Coefficient B for FSK SAW2 sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: -180237
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_B -180237
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_C> Coefficient C for FSK SAW2 sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: 32942736
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_C 32942736
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_D> Coefficient D for FSK SAW2 sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: -1097941542
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_D -1097941542L
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_DDBM> Entry 1 measured FSK SAW2 Output Power for CAL1 (nominally 270 ddBm).
// <180..350:1>
// <i> Default: 200
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_DDBM 200
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_MV> Entry 1 measured FSK SAW2 sensor voltage at CAL1 ddBm, in millivolts.
// <1..65535:1>
// <i> Default: 127
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL1_MV 127
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_DDBM> Entry 1 measured FSK SAW2 Output Power for CAL2 (nominally 290 ddBm).
// <180..350:1>
// <i> Default: 241
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_DDBM 241
// <o SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_MV> Entry 1 measured FSK SAW2 sensor voltage at CAL2 ddBm, in millivolts.
// <1..65535:1>
// <i> Default: 170
#define SL_RAIL_UTIL_EFF_CLPC_FSK_SAW2_1_CAL2_MV 170

// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_A> Coefficient A for OFDM ANTV sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: 574
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_A 574
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_B> Coefficient B for OFDM ANTV sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: -235763
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_B -235763
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_C> Coefficient C for OFDM ANTV sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: 38562724
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_C 38562724
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_D> Coefficient D for OFDM ANTV sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: -1115923360
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_D -1115923360L
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_DDBM> Entry 1 measured OFDM ANTV Output Power for CAL1 (nominally 270 ddBm).
// <180..350:1>
// <i> Default: 222
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_DDBM 222
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_MV> Entry 1 measured OFDM ANTV sensor voltage at CAL1 ddBm, in millivolts.
// <1..65535:1>
// <i> Default: 249
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL1_MV 249
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_DDBM> Entry 2 measured OFDM ANTV Output Power for CAL2 (nominally 290 ddBm).
// <180..350:1>
// <i> Default: 290
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_DDBM 290
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_MV> Entry 2 measured OFDM ANTV sensor voltage at CAL2 ddBm, in millivolts.
// <1..65535:1>
// <i> Default: 507
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_ANTV_1_CAL2_MV 507

// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_A> Coefficient A for OFDM SAW2 sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: 2178
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_A 2178
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_B> Coefficient B for OFDM SAW2 sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: -1312415
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_B -1312415
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_C> Coefficient C for OFDM SAW2 sensor voltage curve. Multiplied by 1e7.
// <-2147483647..2147483647:1>
// <i> Default: 271823274
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_C 271823274
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_D> Coefficient D for OFDM SAW2 sensor voltage curve. Multiplied by 1e7.
// <-20000000000..20000000000:1>
// <i> Default: -17876500819
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_D -17876500819L
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_DDBM> Entry 1 measured OFDM SAW2 Output Power for CAL1 (nominally 270 ddBm).
// <180..350:1>
// <i> Default: 250
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_DDBM 250
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_MV> Entry 1 measured OFDM SAW2 sensor voltage at CAL1 ddBm, in millivolts.
// <1..65535:1>
// <i> Default: 208
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL1_MV 208
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_DDBM> Entry 1 measured OFDM SAW2 Output Power for CAL2 (nominally 290 ddBm).
// <180..350:1>
// <i> Default: 289
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_DDBM 289
// <o SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_MV> Entry 1 measured OFDM SAW2 sensor voltage at CAL2 ddBm, in millivolts.
// <1..65535:1>
// <i> Default: 366
#define SL_RAIL_UTIL_EFF_CLPC_OFDM_SAW2_1_CAL2_MV 366

// <o SL_RAIL_UTIL_EFF_CLPC_ENABLE> Select CLPC mode
// <RAIL_EFF_CLPC_DISABLED=> Disable CLPC power control. Flare modes will only be transmit/receive.
// <RAIL_EFF_CLPC_MODE_CHANGE=> Allow mode changes/measurements, but no power changes
// <RAIL_EFF_CLPC_POWER_SLOW=> Allow only Slow loop power changes
// <RAIL_EFF_CLPC_POWER_FAST=> Allow only Fast loop power changes
// <RAIL_EFF_CLPC_POWER_BOTH=> Allow full power control
// <i> Default: RAIL_EFF_CLPC_MODE_CHANGE
#define SL_RAIL_UTIL_EFF_CLPC_ENABLE RAIL_EFF_CLPC_MODE_CHANGE
// <o SL_RAIL_UTIL_EFF_TEMPERATURE_THRESHOLD_EFF_DEGREES_K> Temperature of EFF above which transmit is not allowed, in degrees Kelvin. A security margin is subtracted before using it.
// <1..383:1>
// <i> Default: 383
#define SL_RAIL_UTIL_EFF_TEMPERATURE_THRESHOLD_EFF_DEGREES_K 383
// </h>

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// CTRL0 GPIO
// <gpio readonly=true> SL_RAIL_UTIL_EFF_CTRL0
// $[GPIO_SL_RAIL_UTIL_EFF_CTRL0]
#define SL_RAIL_UTIL_EFF_CTRL0_PORT              gpioPortC
#define SL_RAIL_UTIL_EFF_CTRL0_PIN               4
// [GPIO_SL_RAIL_UTIL_EFF_CTRL0]$

// CTRL1 GPIO
// <gpio readonly=true> SL_RAIL_UTIL_EFF_CTRL1
// $[GPIO_SL_RAIL_UTIL_EFF_CTRL1]
#define SL_RAIL_UTIL_EFF_CTRL1_PORT              gpioPortC
#define SL_RAIL_UTIL_EFF_CTRL1_PIN               5
// [GPIO_SL_RAIL_UTIL_EFF_CTRL1]$

// CTRL2 GPIO
// <gpio readonly=true> SL_RAIL_UTIL_EFF_CTRL2
// $[GPIO_SL_RAIL_UTIL_EFF_CTRL2]
#define SL_RAIL_UTIL_EFF_CTRL2_PORT              gpioPortC
#define SL_RAIL_UTIL_EFF_CTRL2_PIN               6
// [GPIO_SL_RAIL_UTIL_EFF_CTRL2]$

// CTRL3 GPIO
// <gpio readonly=true> SL_RAIL_UTIL_EFF_CTRL3
// $[GPIO_SL_RAIL_UTIL_EFF_CTRL3]
#define SL_RAIL_UTIL_EFF_CTRL3_PORT              gpioPortC
#define SL_RAIL_UTIL_EFF_CTRL3_PIN               7
// [GPIO_SL_RAIL_UTIL_EFF_CTRL3]$

// TEST GPIO
// <gpio optional=true> SL_RAIL_UTIL_EFF_TEST
// $[GPIO_SL_RAIL_UTIL_EFF_TEST]
#define SL_RAIL_UTIL_EFF_TEST_PORT               gpioPortC
#define SL_RAIL_UTIL_EFF_TEST_PIN                3
// [GPIO_SL_RAIL_UTIL_EFF_TEST]$

// SENSE GPIO
// <gpio readonly=true> SL_RAIL_UTIL_EFF_SENSE
// $[GPIO_SL_RAIL_UTIL_EFF_SENSE]
#define SL_RAIL_UTIL_EFF_SENSE_PORT              gpioPortC
#define SL_RAIL_UTIL_EFF_SENSE_PIN               8
// [GPIO_SL_RAIL_UTIL_EFF_SENSE]$

// <<< sl:end pin_tool >>>

#endif // SL_RAIL_UTIL_EFF_CONFIG_H

/***************************************************************************//**
 * @file
 * @brief PA power conversion curves used by Silicon Labs PA power conversion
 *   functions.
 * @details This file contains the curves needed convert PA power levels to
 *   dBm powers.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __PA_CURVES_H_
#define __PA_CURVES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RAIL_PA_CURVES_PIECEWISE_SEGMENTS (9U)

#define RAIL_PA_CURVES_2P4GIG_HP_VBAT_MAX_POWER      120
#define RAIL_PA_CURVES_2P4GIG_HP_VBAT_MIN_POWER      -200
#define RAIL_PA_CURVES_2P4GIG_HP_VBAT_CURVES \
  { { 255, 120, 18 },                        \
    { 240, 5685, -433447 },                  \
    { 125, 2477, -117719 },                  \
    { 81, 1270, -20235 },                    \
    { 59, 787, 10036 },                      \
    { 45, 672, 15204 },                      \
    { 34, 348, 24122 },                      \
    { 34, 351, 23924 },                      \
    { 16, 104, 18181 } }

#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_MAX_POWER      210
#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_MIN_POWER      -145
#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_CURVES \
  { { 255, 210, 40 },                        \
    { 240, 3483, -489047 },                  \
    { 101, 1167, -95813 },                   \
    { 54, 549, -16183 },                     \
    { 33, 332, 3251 },                       \
    { 19, 202, 9495 },                       \
    { 11, 112, 10152 },                      \
    { 6, 71, 8706 },                         \
    { 4, 42, 6620 } }

#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_MAX_POWER      130
#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_MIN_POWER      -310
#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_CURVES \
  { { 255, 130, 30 },                        \
    { 240, 2266, -49167 },                   \
    { 162, 1750, -1148 },                    \
    { 115, 1159, 38007 },                    \
    { 80, 817, 50579 },                      \
    { 55, 539, 52183 },                      \
    { 39, 410, 49060 },                      \
    { 27, 263, 41083 },                      \
    { 15, 81, 22763 } }

#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_MAX_POWER      30
#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_MIN_POWER      -420
#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_CURVES \
  { { 255, 30, 20 },                         \
    { 240, 1896, 199101 },                   \
    { 210, 2151, 197417 },                   \
    { 166, 1715, 191232 },                   \
    { 131, 1352, 178737 },                   \
    { 105, 1098, 164975 },                   \
    { 85, 856, 147488 },                     \
    { 65, 716, 133996 },                     \
    { 39, 189, 64240 } }

#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MAX_POWER      -60
#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MIN_POWER      -450
#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_CURVES \
  { { 255, -60, 30 },                         \
    { 240, 2052, 383354 },                    \
    { 168, 1832, 360412 },                    \
    { 134, 1296, 294295 },                    \
    { 94, 929, 237629 },                      \
    { 66, 652, 186604 },                      \
    { 46, 490, 151812 },                      \
    { 32, 315, 109198 },                      \
    { 19, 125, 54618 } }

// *INDENT-OFF*
// Macro to declare the variables needed to initialize RAIL_TxPowerCurvesConfig_t for use in
// RAIL_InitTxPowerCurves, assuming battery powered operation
#define RAIL_DECLARE_TX_POWER_VBAT_CURVES_ALT                      \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseData2p4gHp = { \
    RAIL_PA_CURVES_2P4GIG_HP_VBAT_MAX_POWER,                       \
    RAIL_PA_CURVES_2P4GIG_HP_VBAT_MIN_POWER,                       \
    RAIL_PA_CURVES_2P4GIG_HP_VBAT_CURVES,                          \
  };                                                               \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataHp = {     \
    RAIL_PA_CURVES_SUBGIG_HP_VBAT_MAX_POWER,                       \
    RAIL_PA_CURVES_SUBGIG_HP_VBAT_MIN_POWER,                       \
    RAIL_PA_CURVES_SUBGIG_HP_VBAT_CURVES,                          \
    };                                                             \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataMp = {     \
    RAIL_PA_CURVES_SUBGIG_MP_VBAT_MAX_POWER,                       \
    RAIL_PA_CURVES_SUBGIG_MP_VBAT_MIN_POWER,                       \
    RAIL_PA_CURVES_SUBGIG_MP_VBAT_CURVES,                          \
  };                                                               \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataLp = {     \
    RAIL_PA_CURVES_SUBGIG_LP_VBAT_MAX_POWER,                       \
    RAIL_PA_CURVES_SUBGIG_LP_VBAT_MIN_POWER,                       \
    RAIL_PA_CURVES_SUBGIG_LP_VBAT_CURVES,                          \
  };                                                               \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataLlp = {    \
    RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MAX_POWER,                      \
    RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MIN_POWER,                      \
    RAIL_PA_CURVES_SUBGIG_LLP_VBAT_CURVES,                         \
  };

// *INDENT-OFF*

// *INDENT-OFF*
// Macro to declare the variables needed to initialize RAIL_TxPowerCurvesConfig_t for use in
// RAIL_InitTxPowerCurves, assuming battery powered operation
#define RAIL_DECLARE_TX_POWER_CURVES_CONFIG_ALT                                \
  {                                                                            \
    .curves = {                                                                \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_2P4_HP_MIN,                                 \
        .max = RAIL_TX_POWER_LEVEL_2P4_HP_MAX,                                 \
        .conversion = { .powerCurve = &RAIL_piecewiseData2p4gHp },             \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_HP_MIN,                              \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_HP_MAX,                              \
        .conversion = { .powerCurve = &RAIL_piecewiseDataHp },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_MP_MIN,                              \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_MP_MAX,                              \
        .conversion = { .powerCurve = &RAIL_piecewiseDataMp },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_LP_MIN,                              \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_LP_MAX,                              \
        .conversion = { .powerCurve = &RAIL_piecewiseDataLp },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_LLP_MIN,                             \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_LLP_MAX,                             \
        .conversion = { .powerCurve = &RAIL_piecewiseDataLlp },                \
      },                                                                       \
    }                                                                          \
  }
// *INDENT-OFF*

#ifdef __cplusplus
}
#endif

#endif

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

#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_MAX_POWER      150
#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_MIN_POWER      -170
#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_CURVES \
  { { 255, 150, 30 },                        \
    { 240, 5319, -541229 },                  \
    { 90, 1329, -67033 },                    \
    { 50, 606, -3045 },                      \
    { 32, 363, 11198 },                      \
    { 21, 230, 14739 },                      \
    { 14, 153, 14415 },                      \
    { 9, 102, 12646 },                       \
    { 5, 49, 8910 } }

#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_MAX_POWER      110
#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_MIN_POWER      -300
#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_CURVES \
  { { 255, 110, 30 },                        \
    { 240, 2997, -85973 },                   \
    { 142, 1650, 16481 },                    \
    { 94, 1029, 45902 },                     \
    { 62, 660, 51879 },                      \
    { 43, 457, 49321 },                      \
    { 29, 295, 42079 },                      \
    { 20, 203, 35300 },                      \
    { 12, 72, 20187 } }

#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_MAX_POWER      30
#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_MIN_POWER      -370
#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_CURVES \
  { { 255, 30, 12 },                         \
    { 240, 1964, 195091 },                   \
    { 219, 2639, 186950 },                   \
    { 187, 2246, 187322 },                   \
    { 163, 1924, 184008 },                   \
    { 140, 1642, 177639 },                   \
    { 120, 1393, 168987 },                   \
    { 104, 1263, 162925 },                   \
    { 66, 319, 90541 } }

#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MAX_POWER      -50
#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MIN_POWER      -380
#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_CURVES \
  { { 255, -50, 12 },                         \
    { 240, 1739, 336707 },                    \
    { 216, 2292, 374331 },                    \
    { 191, 2152, 363198 },                    \
    { 168, 1869, 337656 },                    \
    { 145, 1619, 311965 },                    \
    { 124, 1376, 283953 },                    \
    { 108, 1255, 268548 },                    \
    { 73, 401, 135974 } }

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
  };                                                               \
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

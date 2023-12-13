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
#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_MIN_POWER      -169
#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_CURVES \
  { { 255, 150, 30 },                        \
    { 240, 5345, -548066 },                  \
    { 90, 1326, -68006 },                    \
    { 49, 596, -3161 },                      \
    { 31, 355, 10776 },                      \
    { 20, 228, 14132 },                      \
    { 14, 153, 13964 },                      \
    { 9, 102, 12362 },                       \
    { 5, 49, 8735 } }

#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_MAX_POWER      110
#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_MIN_POWER      -290
#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_CURVES \
  { { 255, 110, 30 },                        \
    { 240, 3052, -89970 },                   \
    { 140, 1689, 13584 },                    \
    { 93, 1015, 45378 },                     \
    { 62, 657, 51136 },                      \
    { 43, 444, 48445 },                      \
    { 28, 291, 41505 },                      \
    { 20, 202, 34938 },                      \
    { 11, 69, 19419 } }

#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_MAX_POWER      30
#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_MIN_POWER      -370
#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_CURVES \
  { { 255, 30, 8 },                          \
    { 240, 1710, 199588 },                   \
    { 228, 2289, 189575 },                   \
    { 208, 2767, 185506 },                   \
    { 189, 2305, 186234 },                   \
    { 168, 2046, 184348 },                   \
    { 154, 1851, 181547 },                   \
    { 139, 1702, 178124 },                   \
    { 91, 439, 113880 } }

#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MAX_POWER      -50
#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MIN_POWER      -380
#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_CURVES \
  { { 255, -50, 12 },                         \
    { 240, 1803, 339492 },                    \
    { 217, 2356, 377020 },                    \
    { 189, 2098, 356629 },                    \
    { 166, 1854, 334447 },                    \
    { 144, 1553, 303593 },                    \
    { 125, 1340, 279183 },                    \
    { 106, 1266, 269675 },                    \
    { 73, 395, 134216 } }

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

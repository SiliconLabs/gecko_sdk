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
#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_MIN_POWER      -147
#define RAIL_PA_CURVES_SUBGIG_HP_VBAT_CURVES \
  { { 255, 210, 40 },                        \
    { 240, 3539, -500017 },                  \
    { 103, 1140, -91298 },                   \
    { 55, 548, -15411 },                     \
    { 33, 330, 3949 },                       \
    { 19, 202, 9888 },                       \
    { 12, 125, 10563 },                      \
    { 7, 70, 8830 },                         \
    { 4, 42, 6763 } }

#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_MAX_POWER      130
#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_MIN_POWER      -310
#define RAIL_PA_CURVES_SUBGIG_MP_VBAT_CURVES \
  { { 255, 130, 28 },                        \
    { 240, 2272, -50131 },                   \
    { 166, 1768, -2214 },                    \
    { 120, 1210, 36744 },                    \
    { 88, 890, 50363 },                      \
    { 62, 614, 54093 },                      \
    { 46, 464, 52102 },                      \
    { 32, 332, 46382 },                      \
    { 18, 93, 25624 } }

#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_MAX_POWER      20
#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_MIN_POWER      -420
#define RAIL_PA_CURVES_SUBGIG_LP_VBAT_CURVES \
  { { 255, 20, 28 },                         \
    { 240, 2002, 201283 },                   \
    { 163, 1715, 195970 },                   \
    { 127, 1250, 177439 },                   \
    { 93, 891, 153280 },                     \
    { 66, 700, 134616 },                     \
    { 49, 478, 107369 },                     \
    { 34, 378, 92048 },                      \
    { 20, 101, 38895 } }

#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MAX_POWER      -70
#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_MIN_POWER      -450
#define RAIL_PA_CURVES_SUBGIG_LLP_VBAT_CURVES \
  { { 255, -70, 30 },                         \
    { 240, 2079, 391252 },                    \
    { 163, 1687, 348369 },                    \
    { 122, 1188, 281680 },                    \
    { 87, 843, 225133 },                      \
    { 61, 601, 178076 },                      \
    { 42, 440, 141578 },                      \
    { 30, 305, 107520 },                      \
    { 18, 126, 54821 } }

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
        .conversion = { .powerCurve = &RAIL_piecewiseDataLlp },                 \
      },                                                                       \
    }                                                                          \
  }
// *INDENT-OFF*

#ifdef __cplusplus
}
#endif

#endif

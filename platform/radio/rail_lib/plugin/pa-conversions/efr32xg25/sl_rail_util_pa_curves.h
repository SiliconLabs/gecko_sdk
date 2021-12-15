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

// @TODO: RAIL_LIB-6968: These numbers will be updated with more accurate numbers from validation.

#define RAIL_PA_CURVES_MAX_POWER_HP      150
#define RAIL_PA_CURVES_MIN_POWER_HP      -316
#define RAIL_PA_CURVES_CURVES_HP                                                                           \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, 150, 58 },                                                                                      \
    { 79, 613, -13594 },                                                                                   \
    { 42, 308, 14325 },                                                                                    \
    { 25, 156, 19406 },                                                                                    \
    { 15, 83, 17508 },                                                                                     \
    { 11, 54, 15181 },                                                                                     \
    { 7, 54, 15951 },                                                                                      \
    { 4, 39, 12638 },                                                                                      \
    { 3, 24, 8827 } }

#define RAIL_PA_CURVES_MAX_POWER_MP      83
#define RAIL_PA_CURVES_MIN_POWER_MP      -385
#define RAIL_PA_CURVES_CURVES_MP                                                                           \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, 83, 57 },                                                                                       \
    { 79, 583, 39050 },                                                                                    \
    { 53, 316, 45408 },                                                                                    \
    { 35, 189, 41329 },                                                                                    \
    { 25, 109, 34487 },                                                                                    \
    { 18, 129, 37468 },                                                                                    \
    { 10, 92, 29636 },                                                                                     \
    { 5, 41, 16142 },                                                                                      \
    { 3, 29, 12288 } }

#define RAIL_PA_CURVES_MAX_POWER_LP      -75
#define RAIL_PA_CURVES_MIN_POWER_LP      -458
#define RAIL_PA_CURVES_CURVES_LP                                                                           \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, -75, 40 },                                                                                      \
    { 79, 487, 116899 },                                                                                   \
    { 63, 522, 120762 },                                                                                   \
    { 37, 349, 93047 },                                                                                    \
    { 25, 228, 69346 },                                                                                    \
    { 17, 137, 48375 },                                                                                    \
    { 10, 99, 37681 },                                                                                     \
    { 6, 67, 27428 },                                                                                      \
    { 4, 27, 13376 } }

#define RAIL_PA_CURVES_MAX_POWER_LLP      -229
#define RAIL_PA_CURVES_MIN_POWER_LLP      -546
#define RAIL_PA_CURVES_CURVES_LLP                                                                          \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, -229, 39 },                                                                                     \
    { 79, 722, 244769 },                                                                                   \
    { 47, 499, 183887 },                                                                                   \
    { 29, 289, 118981 },                                                                                   \
    { 19, 161, 74607 },                                                                                    \
    { 12, 111, 55231 },                                                                                    \
    { 7, 78, 40962 },                                                                                      \
    { 4, 30, 18314 } }

#define RAIL_PA_CURVES_MAX_POWER_OFDM      170
#define RAIL_PA_CURVES_MIN_POWER_OFDM       25
#define RAIL_PA_CURVES_CURVES_OFDM                                                                         \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, 170, 18 },                                                                                      \
    { 204, 1806, -104236 },                                                                                \
    { 161, 1467, -54303 },                                                                                 \
    { 135, 1179, -16960 },                                                                                 \
    { 114, 957, 7860 },                                                                                    \
    { 93, 2061, -92136 },                                                                                  \
    { 57, 1280, -35171 },                                                                                  \
    { 40, 836, -8873 },                                                                                    \
    { 25, 714, -3983 } }

// *INDENT-OFF*
// Macro to declare the variables needed to initialize RAIL_TxPowerCurvesConfig_t for use in
// RAIL_InitTxPowerCurves, assuming battery powered operation
#define RAIL_DECLARE_TX_POWER_VBAT_CURVES_ALT                           \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataHP = {          \
    RAIL_PA_CURVES_MAX_POWER_HP,                                        \
    RAIL_PA_CURVES_MIN_POWER_HP,                                        \
    RAIL_PA_CURVES_CURVES_HP,                                           \
  };                                                                    \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataMP = {          \
    RAIL_PA_CURVES_MAX_POWER_MP,                                        \
    RAIL_PA_CURVES_MIN_POWER_MP,                                        \
    RAIL_PA_CURVES_CURVES_MP,                                           \
  };                                                                    \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataLP = {          \
    RAIL_PA_CURVES_MAX_POWER_LP,                                        \
    RAIL_PA_CURVES_MIN_POWER_LP,                                        \
    RAIL_PA_CURVES_CURVES_LP,                                           \
  };                                                                    \
 static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataLLP = {          \
    RAIL_PA_CURVES_MAX_POWER_LLP,                                       \
    RAIL_PA_CURVES_MIN_POWER_LLP,                                       \
    RAIL_PA_CURVES_CURVES_LLP,                                          \
  };                                                                    \
 static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataOFDM = {         \
    RAIL_PA_CURVES_MAX_POWER_OFDM,                                      \
    RAIL_PA_CURVES_MIN_POWER_OFDM,                                      \
    RAIL_PA_CURVES_CURVES_OFDM,                                         \
  }                                                                     \
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
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_HP_MIN,                              \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_HP_MAX,                              \
        .conversion = { .powerCurve = &RAIL_piecewiseDataHP },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_MP_MIN,                              \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_MP_MAX,                              \
        .conversion = { .powerCurve = &RAIL_piecewiseDataMP },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_LP_MIN,                              \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_LP_MAX,                              \
        .conversion = { .powerCurve = &RAIL_piecewiseDataLP },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_LLP_MIN,                             \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_LLP_MAX,                             \
        .conversion = { .powerCurve = &RAIL_piecewiseDataLLP },                \
      },                                                                       \
      { /* Dummy power settings for RAIL_TX_POWER_MODE_SUBGIG_HIGHEST */       \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_HP_MIN,                              \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_HP_MAX,                              \
        .conversion = { .powerCurve = &RAIL_piecewiseDataHP },                 \
      },                                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_OFDM_PA_MIN,                                \
        .max = RAIL_TX_POWER_LEVEL_OFDM_PA_MAX,                                \
        .conversion = { .powerCurve = &RAIL_piecewiseDataOFDM },               \
      },                                                                       \
    }                                                                          \
  }
// *INDENT-OFF*

#ifdef __cplusplus
}
#endif

#endif

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

#define RAIL_PA_CURVES_MAX_POWER_HP      157
#define RAIL_PA_CURVES_MIN_POWER_HP      -165
#define RAIL_PA_CURVES_CURVES_HP                                                                           \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, 150, 30 },                                                                                      \
    { 79, 794, -41545 },                                                                                   \
    { 51, 500, -7172 },                                                                                    \
    { 35, 381, 3027 },                                                                                     \
    { 25, 250, 10658 },                                                                                    \
    { 17, 173, 12705 },                                                                                    \
    { 12, 128, 12532 },                                                                                    \
    { 8, 86, 11101 },                                                                                      \
    { 5, 39, 7531 } }

#define RAIL_PA_CURVES_MAX_POWER_MP      68
#define RAIL_PA_CURVES_MIN_POWER_MP      -273
#define RAIL_PA_CURVES_CURVES_MP                                                                           \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, 70, 30 },                                                                                       \
    { 79, 780, 24191 },                                                                                    \
    { 53, 497, 34645 },                                                                                    \
    { 38, 404, 35252 },                                                                                    \
    { 26, 257, 31942 },                                                                                    \
    { 18, 157, 26461 },                                                                                    \
    { 13, 127, 23854 },                                                                                    \
    { 9, 75, 17590 },                                                                                      \
    { 5, 44, 12562 } }

#define RAIL_PA_CURVES_MAX_POWER_LP      -25
#define RAIL_PA_CURVES_MIN_POWER_LP      -342
#define RAIL_PA_CURVES_CURVES_LP                                                                           \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, -20, 30 },                                                                                      \
    { 79, 823, 97640 },                                                                                    \
    { 54, 496, 80371 },                                                                                    \
    { 37, 419, 73683 },                                                                                    \
    { 26, 248, 54323 },                                                                                    \
    { 18, 141, 38530 },                                                                                    \
    { 13, 127, 36031 },                                                                                    \
    { 9, 80, 26019 },                                                                                      \
    { 6, 54, 19620 } }

#define RAIL_PA_CURVES_MAX_POWER_LLP      -80
#define RAIL_PA_CURVES_MIN_POWER_LLP      -356
#define RAIL_PA_CURVES_CURVES_LLP                                                                          \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, -80, 30 },                                                                                      \
    { 79, 795, 140598 },                                                                                   \
    { 52, 479, 105591 },                                                                                   \
    { 35, 403, 94379 },                                                                                    \
    { 26, 247, 67927 },                                                                                    \
    { 17, 140, 45984 },                                                                                    \
    { 16, 137, 45353 },                                                                                    \
    { 9, 82, 30654 },                                                                                      \
    { 4, 78, 29348 } }

#define RAIL_PA_CURVES_MAX_POWER_OFDM      180
#define RAIL_PA_CURVES_MIN_POWER_OFDM      -42
#define RAIL_PA_CURVES_CURVES_OFDM                                                                         \
/* NOT a real power level, when set to 255 the first acts as an override for default max and step size. */ \
  { { 255, 180, 30 },                                                                                      \
    { 204, 2239, -205088 },                                                                                \
    { 124, 1315, -68859 },                                                                                 \
    { 84, 856, -15199 },                                                                                   \
    { 58, 577, 8776 },                                                                                     \
    { 41, 405, 18477 },                                                                                    \
    { 29, 285, 21666 },                                                                                    \
    { 21, 200, 21343 },                                                                                    \
    { 15, 152, 19784 } }

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

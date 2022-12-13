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
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_HP \
  { { 255, 150, 30 },            \
    { 79, 794, -41545 },         \
    { 51, 500, -7172 },          \
    { 35, 381, 3027 },           \
    { 25, 250, 10658 },          \
    { 17, 173, 12705 },          \
    { 12, 128, 12532 },          \
    { 8, 86, 11101 },            \
    { 5, 39, 7531 } }

#define RAIL_PA_CURVES_MAX_POWER_MP      68
#define RAIL_PA_CURVES_MIN_POWER_MP      -273
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_MP \
  { { 255, 70, 30 },             \
    { 79, 780, 24191 },          \
    { 53, 497, 34645 },          \
    { 38, 404, 35252 },          \
    { 26, 257, 31942 },          \
    { 18, 157, 26461 },          \
    { 13, 127, 23854 },          \
    { 9, 75, 17590 },            \
    { 5, 44, 12562 } }

#define RAIL_PA_CURVES_MAX_POWER_LP      -25
#define RAIL_PA_CURVES_MIN_POWER_LP      -342
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_LP \
  { { 255, -20, 30 },            \
    { 79, 823, 97640 },          \
    { 54, 496, 80371 },          \
    { 37, 419, 73683 },          \
    { 26, 248, 54323 },          \
    { 18, 141, 38530 },          \
    { 13, 127, 36031 },          \
    { 9, 80, 26019 },            \
    { 6, 54, 19620 } }

#define RAIL_PA_CURVES_MAX_POWER_LLP      -80
#define RAIL_PA_CURVES_MIN_POWER_LLP      -356
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_LLP \
  { { 255, -80, 30 },             \
    { 79, 795, 140598 },          \
    { 52, 479, 105591 },          \
    { 35, 403, 94379 },           \
    { 26, 247, 67927 },           \
    { 17, 140, 45984 },           \
    { 16, 137, 45353 },           \
    { 9, 82, 30654 },             \
    { 4, 78, 29348 } }

#if RAIL_SUPPORTS_EFF
#define RAIL_PA_CURVES_MAX_POWER_EFF_30DBM    310
#define RAIL_PA_CURVES_MIN_POWER_EFF_30DBM    40
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_EFF_30DBM \
  { { 255, 310, 25 },                   \
    { 79, 1449, -378511 },              \
    { 34, 423, -86266 },                \
    { 22, 272, -47420 },                \
    { 16, 168, -23004 },                \
    { 12, 140, -17171 },                \
    { 9, 105, -10728 },                 \
    { 5, 55, -3051 },                   \
    { 4, 34, -498 } }

#define RAIL_PA_CURVES_MAX_POWER_EFF_25DBM    290
#define RAIL_PA_CURVES_MIN_POWER_EFF_25DBM   -30
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_EFF_25DBM \
  { { 255, 290, 26 },                   \
    { 79, 1057, -225158 },              \
    { 52, 551, -92481 },                \
    { 36, 434, -65182 },                \
    { 26, 275, -31751 },                \
    { 18, 178, -14312 },                \
    { 13, 141, -8584 },                 \
    { 9, 89, -2107 },                   \
    { 6, 44, 1940 } }

#define RAIL_PA_CURVES_MAX_POWER_EFF_20DBM    250
#define RAIL_PA_CURVES_MIN_POWER_EFF_20DBM   -100
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_EFF_20DBM \
  { { 255, 250, 24 },                   \
    { 79, 879, -139390 },               \
    { 56, 579, -72670 },                \
    { 44, 485, -53699 },                \
    { 29, 318, -25108 },                \
    { 24, 258, -15770 },                \
    { 17, 141, -1025 },                 \
    { 11, 118, 916 },                   \
    { 8, 50, 4890 } }
#endif

#define RAIL_PA_CURVES_MAX_POWER_OFDM      174
#define RAIL_PA_CURVES_MIN_POWER_OFDM      -45
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_OFDM \
  { { 255, 180, 20 },              \
    { 204, 2490, -232491 },        \
    { 154, 1799, -125143 },        \
    { 118, 1313, -59224 },         \
    { 92, 1005, -23503 },          \
    { 72, 771, -1111 },            \
    { 57, 611, 11015 },            \
    { 45, 481, 18292 },            \
    { 32, 287, 24069 } }

#if RAIL_SUPPORTS_EFF
#define RAIL_PA_CURVES_MAX_POWER_OFDM_EFF_30DBM   305
#define RAIL_PA_CURVES_MIN_POWER_OFDM_EFF_30DBM   272
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_OFDM_EFF_30DBM \
  { { 255, 310, 5 },                         \
    { 120, 4829, -1357402 },                 \
    { 97, 3990, -1104171 },                  \
    { 74, 2364, -623462 },                   \
    { 62, 1642, -413779 },                   \
    { 53, 1267, -306963 },                   \
    { 47, 1030, -240709 },                   \
    { 44, 919, -210012 },                    \
    { 41, 833, -186500 } }

#define RAIL_PA_CURVES_MAX_POWER_OFDM_EFF_25DBM   283
#define RAIL_PA_CURVES_MIN_POWER_OFDM_EFF_25DBM   214
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_OFDM_EFF_25DBM \
  { { 255, 290, 8 },                         \
    { 120, 2343, -545064 },                  \
    { 104, 1955, -437409 },                  \
    { 89, 1466, -305683 },                   \
    { 77, 1155, -224419 },                   \
    { 67, 961, -175441 },                    \
    { 60, 795, -134657 },                    \
    { 55, 682, -107697 },                    \
    { 47, 581, -84729 } }

#define RAIL_PA_CURVES_MAX_POWER_OFDM_EFF_20DBM   232
#define RAIL_PA_CURVES_MIN_POWER_OFDM_EFF_20DBM   143
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_OFDM_EFF_20DBM \
  { { 255, 240, 10 },                        \
    { 120, 1458, -218123 },                  \
    { 109, 1319, -186882 },                  \
    { 97, 1147, -149798 },                   \
    { 84, 989, -117468 },                    \
    { 74, 868, -93930 },                     \
    { 68, 775, -76630 },                     \
    { 59, 683, -60500 },                     \
    { 51, 572, -42301 } }

#define RAIL_PA_CURVES_MAX_POWER_OFDM_EFF_MAXDBM   312
#define RAIL_PA_CURVES_MIN_POWER_OFDM_EFF_MAXDBM   298
// When set to 255 the first entry acts as an override for default max and step size.
#define RAIL_PA_CURVES_CURVES_OFDM_EFF_MAXDBM \
  { { 255, 320, 2 },                          \
    { 120, 12056, -3647779 },                 \
    { 91, 9887, -2973483 },                   \
    { 91, 8597, -2572850 },                   \
    { 85, 7491, -2230111 },                   \
    { 85, 6570, -1945399 },                   \
    { 60, 4155, -1207431 },                   \
    { 48, 3292, -946138 },                    \
    { 45, 2700, -767501 } }
#endif

// *INDENT-OFF*
// Macro to declare the variables needed to initialize RAIL_TxPowerCurvesConfig_t for use in
// RAIL_InitTxPowerCurves, assuming battery powered operation
#if RAIL_SUPPORTS_EFF
#define RAIL_DECLARE_TX_POWER_VBAT_CURVES_ALT                             \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataEFF30Dbm = {      \
    RAIL_PA_CURVES_MAX_POWER_EFF_30DBM,                                   \
    RAIL_PA_CURVES_MIN_POWER_EFF_30DBM,                                   \
    RAIL_PA_CURVES_CURVES_EFF_30DBM,                                      \
  };                                                                      \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataEFF25Dbm = {      \
    RAIL_PA_CURVES_MAX_POWER_EFF_25DBM,                                   \
    RAIL_PA_CURVES_MIN_POWER_EFF_25DBM,                                   \
    RAIL_PA_CURVES_CURVES_EFF_25DBM,                                      \
  };                                                                      \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataEFF20Dbm = {      \
    RAIL_PA_CURVES_MAX_POWER_EFF_20DBM,                                   \
    RAIL_PA_CURVES_MIN_POWER_EFF_20DBM,                                   \
    RAIL_PA_CURVES_CURVES_EFF_20DBM,                                      \
  };                                                                      \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataOFDMEFF30Dbm = {  \
    RAIL_PA_CURVES_MAX_POWER_OFDM_EFF_30DBM,                              \
    RAIL_PA_CURVES_MIN_POWER_OFDM_EFF_30DBM,                              \
    RAIL_PA_CURVES_CURVES_OFDM_EFF_30DBM,                                 \
  };                                                                      \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataOFDMEFF25Dbm = {  \
    RAIL_PA_CURVES_MAX_POWER_OFDM_EFF_25DBM,                              \
    RAIL_PA_CURVES_MIN_POWER_OFDM_EFF_25DBM,                              \
    RAIL_PA_CURVES_CURVES_OFDM_EFF_25DBM,                                 \
  };                                                                      \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataOFDMEFF20Dbm = {  \
    RAIL_PA_CURVES_MAX_POWER_OFDM_EFF_20DBM,                              \
    RAIL_PA_CURVES_MIN_POWER_OFDM_EFF_20DBM,                              \
    RAIL_PA_CURVES_CURVES_OFDM_EFF_20DBM,                                 \
  };                                                                      \
  static const RAIL_TxPowerCurveAlt_t RAIL_piecewiseDataOFDMEFFMaxDbm = { \
    RAIL_PA_CURVES_MAX_POWER_OFDM_EFF_MAXDBM,                             \
    RAIL_PA_CURVES_MIN_POWER_OFDM_EFF_MAXDBM,                             \
    RAIL_PA_CURVES_CURVES_OFDM_EFF_MAXDBM,                                \
  };
#else
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
  };
#endif
// *INDENT-OFF*

// *INDENT-OFF*
// Macro to declare the variables needed to initialize RAIL_TxPowerCurvesConfig_t for use in
// RAIL_InitTxPowerCurves, assuming battery powered operation
#define RAIL_DECLARE_TX_POWER_CURVES_CONFIG_ALT                                \
  {                                                                            \
    .curves = {                                                                \
      /* SUBGIG Mapping Table */                                               \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_DBM_POWERSETTING_MAPPING_TABLE,         \
        .segments = 0U,                                                        \
        .step = RAIL_PA_CURVES_SUBGIG_CURVES_STEP_DDBM,                        \
        .minPowerDbm = RAIL_PA_CURVES_SUBGIG_MIN_POWER_DDBM,                   \
        .maxPowerDbm = RAIL_PA_CURVES_SUBGIG_MAX_POWER_DDBM,                   \
        .conversion = { .mappingTable = &RAIL_curvesSubgig[0] },               \
      },                                                                       \
      { /* Dummy power settings for RAIL_TX_POWER_MODE_SUBGIG_HIGHEST */       \
        .algorithm = RAIL_PA_ALGORITHM_DBM_POWERSETTING_MAPPING_TABLE,         \
        .segments = 0U,                                                        \
        .step = RAIL_PA_CURVES_SUBGIG_CURVES_STEP_DDBM,                        \
        .minPowerDbm = RAIL_PA_CURVES_SUBGIG_MIN_POWER_DDBM,                   \
        .maxPowerDbm = RAIL_PA_CURVES_SUBGIG_MAX_POWER_DDBM,                   \
        .conversion = { .mappingTable = &RAIL_curvesSubgig[0] },               \
      },                                                                       \
      /* OFDM Mapping Table */                                                 \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_DBM_POWERSETTING_MAPPING_TABLE,         \
        .segments = 0U,                                                        \
        .step = RAIL_PA_CURVES_OFDM_CURVES_STEP_DDBM,                          \
        .minPowerDbm = RAIL_PA_CURVES_OFDM_MIN_POWER_DDBM,                     \
        .maxPowerDbm = RAIL_PA_CURVES_OFDM_MAX_POWER_DDBM,                     \
        .conversion = { .mappingTable = &RAIL_curvesOFDM[0] },                 \
      },                                                                       \
      { /* Dummy power settings for RAIL_TX_POWER_MODE_OFDM_PA */              \
        .algorithm = RAIL_PA_ALGORITHM_DBM_POWERSETTING_MAPPING_TABLE,         \
        .segments = 0U,                                                        \
        .step = RAIL_PA_CURVES_OFDM_CURVES_STEP_DDBM,                          \
        .minPowerDbm = RAIL_PA_CURVES_OFDM_MIN_POWER_DDBM,                     \
        .maxPowerDbm = RAIL_PA_CURVES_OFDM_MAX_POWER_DDBM,                     \
        .conversion = { .mappingTable = &RAIL_curvesOFDM[0] },                 \
      },                                                                       \
      /* SUBGIG EFF 30DBM */                                                   \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_EFF_30DBM_MIN,                       \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_EFF_30DBM_MAX,                       \
        .conversion = { .powerCurve = &RAIL_piecewiseDataEFF30Dbm },           \
      },                                                                       \
      /* SUBGIG EFF 25DBM */                                                   \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_EFF_25DBM_MIN,                       \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_EFF_25DBM_MAX,                       \
        .conversion = { .powerCurve = &RAIL_piecewiseDataEFF25Dbm },           \
      },                                                                       \
      /* SUBGIG EFF 20DBM */                                                   \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_SUBGIG_EFF_20DBM_MIN,                       \
        .max = RAIL_TX_POWER_LEVEL_SUBGIG_EFF_20DBM_MAX,                       \
        .conversion = { .powerCurve = &RAIL_piecewiseDataEFF20Dbm },           \
      },                                                                       \
      /* SUBGIG EFF Mapping Table */                                           \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_DBM_POWERSETTING_MAPPING_TABLE,         \
        .segments = 0U,                                                        \
        .step = RAIL_PA_CURVES_EFF_SUBGIG_CURVES_STEP_DDBM,                    \
        .minPowerDbm = RAIL_PA_CURVES_EFF_SUBGIG_MIN_POWER_DDBM,               \
        .maxPowerDbm = RAIL_PA_CURVES_EFF_SUBGIG_MAX_POWER_DDBM,               \
        .conversion = { .mappingTable = &RAIL_curvesEffSubgig[0] },            \
      },                                                                       \
      /* OFDM EFF 30DBM */                                                     \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_30DBM_MIN,                      \
        .max = RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_30DBM_MAX,                      \
        .conversion = { .powerCurve = &RAIL_piecewiseDataOFDMEFF30Dbm },       \
      },                                                                       \
      /* OFDM EFF 25DBM */                                                     \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_25DBM_MIN,                      \
        .max = RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_25DBM_MAX,                      \
        .conversion = { .powerCurve = &RAIL_piecewiseDataOFDMEFF25Dbm },       \
      },                                                                       \
      /* OFDM EFF 20DBM */                                                     \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_20DBM_MIN,                      \
        .max = RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_20DBM_MAX,                      \
        .conversion = { .powerCurve = &RAIL_piecewiseDataOFDMEFF20Dbm },       \
      },                                                                       \
      /* OFDM EFF MAX */                                                       \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_PIECEWISE_LINEAR,                       \
        .segments = RAIL_PA_CURVES_PIECEWISE_SEGMENTS,                         \
        .min = RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_MAXDBM_MIN,                     \
        .max = RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_MAXDBM_MAX,                     \
        .conversion = { .powerCurve = &RAIL_piecewiseDataOFDMEFFMaxDbm },      \
      },                                                                       \
      /* OFDM EFF Mapping Table */                                             \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_DBM_POWERSETTING_MAPPING_TABLE,         \
        .segments = 0U,                                                        \
        .step = RAIL_PA_CURVES_EFF_OFDM_CURVES_STEP_DDBM,                      \
        .minPowerDbm = RAIL_PA_CURVES_EFF_OFDM_MIN_POWER_DDBM,                 \
        .maxPowerDbm = RAIL_PA_CURVES_EFF_OFDM_MAX_POWER_DDBM,                 \
        .conversion = { .mappingTable = &RAIL_curvesEffOFDM[0] },              \
      },                                                                       \
    }                                                                          \
  }
// *INDENT-OFF*

#ifdef __cplusplus
}
#endif

#endif

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
      /* OFDM Mapping Table */                                                 \
      {                                                                        \
        .algorithm = RAIL_PA_ALGORITHM_DBM_POWERSETTING_MAPPING_TABLE,         \
        .segments = 0U,                                                        \
        .step = RAIL_PA_CURVES_OFDM_CURVES_STEP_DDBM,                          \
        .minPowerDbm = RAIL_PA_CURVES_OFDM_MIN_POWER_DDBM,                     \
        .maxPowerDbm = RAIL_PA_CURVES_OFDM_MAX_POWER_DDBM,                     \
        .conversion = { .mappingTable = &RAIL_curvesOFDM[0] },                 \
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

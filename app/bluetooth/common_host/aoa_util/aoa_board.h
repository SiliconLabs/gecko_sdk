/***************************************************************************//**
 * @file
 * @brief Antenna board configuration values.
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

#ifndef AOA_BOARD_H
#define AOA_BOARD_H

// AoA antenna array type
#define ARRAY_TYPE_4x4_URA             0
#define ARRAY_TYPE_3x3_URA             1
#define ARRAY_TYPE_1x4_ULA             2

#ifndef ARRAY_TYPE
#define ARRAY_TYPE                     ARRAY_TYPE_4x4_URA
#endif

#if (ARRAY_TYPE == ARRAY_TYPE_4x4_URA)
#define AOX_ARRAY_TYPE          SL_RTL_AOX_ARRAY_TYPE_4x4_URA
#define AOA_NUM_SNAPSHOTS       (4)
#define AOA_NUM_ARRAY_ELEMENTS  (4 * 4)
#define AOA_REF_PERIOD_SAMPLES  (7)
#define SWITCHING_PATTERN       { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
#elif (ARRAY_TYPE == ARRAY_TYPE_3x3_URA)
#define AOX_ARRAY_TYPE          SL_RTL_AOX_ARRAY_TYPE_3x3_URA
#define AOA_NUM_SNAPSHOTS       (4)
#define AOA_NUM_ARRAY_ELEMENTS  (3 * 3)
#define AOA_REF_PERIOD_SAMPLES  (7)
#define SWITCHING_PATTERN       { 1, 2, 3, 5, 6, 7, 9, 10, 11 }
#elif (ARRAY_TYPE == ARRAY_TYPE_1x4_ULA)
#define AOX_ARRAY_TYPE          SL_RTL_AOX_ARRAY_TYPE_1x4_ULA
#define AOA_NUM_SNAPSHOTS       (18)
#define AOA_NUM_ARRAY_ELEMENTS  (1 * 4)
#define AOA_REF_PERIOD_SAMPLES  (7)
#define SWITCHING_PATTERN       { 0, 1, 2, 3 }
#endif

#endif // AOA_BOARD_H

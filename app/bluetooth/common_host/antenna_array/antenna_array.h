/***************************************************************************//**
 * @file
 * @brief Antenna array handler for Silicon Labs boards.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef ANTENNA_ARRAY_H
#define ANTENNA_ARRAY_H

#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

// List of supported antenna array types. See also sl_rtl_aox_array_type.
#define ANTENNA_ARRAY_TYPE_4x4_URA    0 ///< Silicon Labs Ref. 4x4 Uniform Rectangular Array
#define ANTENNA_ARRAY_TYPE_3x3_URA    1 ///< Silicon Labs Ref. 3x3 Uniform Rectangular Array
#define ANTENNA_ARRAY_TYPE_1x4_ULA    2 ///< Silicon Labs Ref. 1x4 Uniform Linear Array
#define ANTENNA_ARRAY_TYPE_4x4_DP_URA 3 ///< Silicon Labs Ref. 4x4 Uniform Dual Polarized Rectangular Array
#define ANTENNA_ARRAY_TYPE_LAST       4 ///< Placeholder

/// Check if antenna is of dual polarized type.
#define antenna_array_type_is_dp(x)   ((x) == ANTENNA_ARRAY_TYPE_4x4_DP_URA)

/// Antenna array returned by antenna_array_get_continuous_pattern is guaranteed
/// to fit into this buffer size.
#define ANTENNA_ARRAY_MAX_PATTERN_SIZE        16

/// Antenna array returned by antenna_array_get_pin_pattern is guaranteed
/// to fit into this buffer size.
#define ANTENNA_ARRAY_MAX_PIN_PATTERN_SIZE    33

/// Antenna array storage type.
typedef struct antenna_array_s {
  uint8_t pattern[ANTENNA_ARRAY_MAX_PATTERN_SIZE];
  uint8_t size;
  uint8_t array_type;
} antenna_array_t;

/// List of supported boards.
typedef enum {
  BRD4185A,
  BRD4191A,
  ANTENNA_ARRAY_BOARD_UNKNOWN,
  ANTENNA_ARRAY_BOARD_COUNT
} antenna_array_board_t;

/***************************************************************************//**
 * Initialize antenna switch pattern with default values.
 *
 * @param[in] antenna_array Antenna array instance to operate on.
 * @param[in] array_type Antenna array type.
 ******************************************************************************/
sl_status_t antenna_array_init(antenna_array_t *antenna_array,
                               uint8_t array_type);

/***************************************************************************//**
 * Override antenna switch pattern.
 *
 * @param[in] antenna_array Antenna array instance to operate on.
 * @param[in] pattern New antenna switch pattern given as the antenna numbers
 *                    printed on the board minus 1. E.g., antenna 1 is given as
 *                    0.
 * @param[in] size Length of the pattern.
 ******************************************************************************/
sl_status_t antenna_array_set_pattern(antenna_array_t *antenna_array,
                                      uint8_t *pattern,
                                      uint8_t size);

/***************************************************************************//**
 * Get antenna switch pin sequence.
 *
 * @param[in] antenna_array Antenna array instance to operate on.
 * @param[out] pattern Pin sequence that implements the antenna switch pattern.
 *                     The first element in the sequence represents the
 *                     reference antenna. Optional argument, can be omitted
 *                     by passing NULL.
 * @param[in,out] size Buffer length as input, actual pattern length as output.
 ******************************************************************************/
sl_status_t antenna_array_get_pin_pattern(antenna_array_t *antenna_array,
                                          uint8_t *pattern,
                                          uint8_t *size);

/***************************************************************************//**
 * Convert antenna switch pattern to [0..n-1] interval without gaps.
 *
 * This function is relevant for reduced antenna boards like 3x3 URA or 1x4 ULA.
 * If all antennas on the boards are in use, then the pattern returned by this
 * function and the stored pattern are identical.
 *
 * @param[in] antenna_array Antenna array instance to operate on.
 * @param[out] pattern Buffer for the converted switch pattern.
 * @param[in,out] size Buffer length as input, actual pattern length as output.
 ******************************************************************************/
sl_status_t antenna_array_get_continuous_pattern(antenna_array_t *antenna_array,
                                                 uint32_t *pattern,
                                                 uint32_t *size);

/***************************************************************************//**
 * Shuffle the current antenna switch pattern.
 *
 * @param[in] antenna_array Antenna array instance to operate on.
 * @param[in] random Function generating random values.
 ******************************************************************************/
sl_status_t antenna_array_shuffle_pattern(antenna_array_t *antenna_array,
                                          int(random)(void));

/***************************************************************************//**
 * Assign a compatible board to an antenna array type.
 *
 * @param[in] array_type One of the supported antenna array types.
 * @param[out] board Antenna array board that matches the array type.
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t antenna_array_type_to_board(uint8_t array_type,
                                        antenna_array_board_t *board);

/***************************************************************************//**
 * Assign a default antenna array type to a board.
 *
 * @param[in] board One of the supported antenna array boards.
 * @param[out] array_type Default antenna array type that matches the board.
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t antenna_array_board_to_type(antenna_array_board_t board,
                                        uint8_t *array_type);

/***************************************************************************//**
 * Convert string to antenna array board.
 *
 * @param[in] str Input string.
 * @param[out] board Antenna array board.
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t antenna_array_string_to_board(const char *str,
                                          antenna_array_board_t *board);

/***************************************************************************//**
 * Convert antenna array board to string.
 *
 * @param[in] board Antenna array board.
 * @param[out] str Output string.
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t antenna_array_board_to_string(antenna_array_board_t board,
                                          char *str);

#ifdef __cplusplus
};
#endif

#endif // ANTENNA_ARRAY_H

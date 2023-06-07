/***************************************************************************//**
 * @file
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef CSLIB_CONFIG_H
#define CSLIB_CONFIG_H

/**************************************************************************//**
 *
 * @addtogroup cslib_config CSLIB library functional configuration
 * @{
 *
 * @brief Functional configuration for CSLIB
 *
 * The definitions provided in this file act as defaults in the functional
 * configuration of the capacitive sensing firmware library.
 *
 *****************************************************************************/

/// @brief Sets the number of samples crossing active/inactive thresh. before touch is qualified/disqualified.
/// @note Minimum value is 1, maximum value is 15.
#define DEF_BUTTON_DEBOUNCE                       2

/// @brief Sets the period of scanning in active mode.
/// Actual scan frequency is determined by this setting and by @ref DEF_FREE_RUN_SETTING
/// @note Minimum value is 1, maximum value is 5000.
#define DEF_ACTIVE_MODE_PERIOD                    100

/// @brief Sets the period of scanning when in sleep mode.
/// @note Minimum value is 1, maximum value is 5000.
#define DEF_SLEEP_MODE_PERIOD                     100

/// @brief Number of sequential periods of scanning in active mode with no qualified
/// touch detected before system enters sleep.
/// @note Minimum value is 1, maximum value is 255
#define DEF_COUNTS_BEFORE_SLEEP                   100

/// @brief Configures whether system does a single scan every @ref DEF_ACTIVE_MODE_PERIOD
/// and then enters sleep for the remainder of the period (when cleared to 0),
/// or if the system scans continuously (when set to 1).
/// @note Set to 0 to disable free run mode, 1 to enable free run mode
#define DEF_FREE_RUN_SETTING                      1

/// @brief Set this to 1 to enable sleep mode sensing, set this to 0 to always remain in
/// active mode
/// @note Set to 1 to allow system to enter sleep mode scanning state, 0 otherwise.
#define DEF_SLEEP_MODE_ENABLE                     1

/** @} (end cslib_config) */
#endif // CSLIB_CONFIG_H

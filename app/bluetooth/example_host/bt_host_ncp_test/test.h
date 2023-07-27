/***************************************************************************//**
 * @file
 * @brief Bluetooth Network Co-Processor test module.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdint.h>

/// Structure for the NCP test parameters
typedef struct {
  uint8_t command_id;   // Defines which test case shall be executed.
  uint8_t length;       // Length of the user event messages in bytes.
  uint8_t interval;     // Time interval between user events in milliseconds.
  uint32_t count_stop;  // Number of user event messages to wait for before the test terminates.
} test_config_t;

// Default values for the NCP test parameters
#define TEST_COMMAND_ID_NOT_SPECIFIED   0
#define TEST_LENGTH_DEFAULT             180
#define TEST_INTERVAL_DEFAULT           20
#define TEST_COUNT_STOP_DEFAULT         1000

/**************************************************************************//**
 * Initialize NCP test module.
 *
 * @param[in] config NCP test parameters.
 *****************************************************************************/
void test_init(test_config_t config);

#endif // TEST_H

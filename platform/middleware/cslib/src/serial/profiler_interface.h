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
#ifndef PROFILER_INTERFACE_H
#define PROFILER_INTERFACE_H

// NOTE these configurations are chosen in a compiler directive that assigns a
// value to OUTPUT_MODE.  The directive can be found and configurations
// changed using the pull-down menu in Project->Target Toolchain configuration.
#define RAW_ONLY 1
#define FULL_OUTPUT_RX_FROM_FILE 2
#define FULL_OUTPUT_RX_FROM_SENSOR 3
#define SLIDER_OUTPUT_RX_FROM_SENSOR 4
#define CUSTOM_OUTPUT      5

#define OUTPUT_MODE FULL_OUTPUT_RX_FROM_SENSOR
void CSLIB_commUpdate(void);

// FULL_OUTPUT_RX_FROM_SENSOR.  This setting uses real sensor data
// and outputs most algorithmic data for analysis.

#if OUTPUT_MODE == FULL_OUTPUT_RX_FROM_SENSOR
#define RECEIVE_DATA_SENSOR      1
#define RECEIVE_DATA_FILE        0

#define PRINT_OUTPUTBUFFER       1
#define PRINT_BUTTON_STATE       0
#define PRINT_BASELINES          1
#define PRINT_SLIDER             0
#define PRINT_RAW                1
#define PRINT_PROCESS            1
#define PRINT_SINGLE_ACTIVE      1
#define PRINT_DEBOUNCE_ACTIVE    1
#define PRINT_TOUCH_DELTA        1
#define PRINT_NOISE              1
#define PRINT_EXP_VALUE          1
#define PRINT_GLOBAL_NOISE_EST   1

#endif

#endif // PROFILER_INTERFACE_H

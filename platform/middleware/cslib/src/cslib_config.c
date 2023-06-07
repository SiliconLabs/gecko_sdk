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

#include "cslib_config.h"
#include "cslib.h"

// Struct defined in sensor_node_routines.h.  Contains all state data for a
// sensor.
SensorStruct_t CSLIB_node[DEF_NUM_SENSORS];
uint8_t CSLIB_numSensors = DEF_NUM_SENSORS;
uint8_t CSLIB_sensorBufferSize = DEF_SENSOR_BUFFER_SIZE;
uint8_t CSLIB_buttonDebounce = DEF_BUTTON_DEBOUNCE;
uint16_t CSLIB_activeModePeriod = DEF_ACTIVE_MODE_PERIOD;
uint16_t CSLIB_sleepModePeriod = DEF_SLEEP_MODE_PERIOD;
uint16_t CSLIB_countsBeforeSleep = DEF_COUNTS_BEFORE_SLEEP;
uint8_t CSLIB_freeRunSetting = DEF_FREE_RUN_SETTING;
uint8_t CSLIB_sleepModeEnable = DEF_SLEEP_MODE_ENABLE;

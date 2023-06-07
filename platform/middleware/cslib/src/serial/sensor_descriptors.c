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

#include "cslib_hwconfig.h"
#include <stdio.h>
#include <stdint.h>
#include "cslib_sensor_descriptors.h"

/// @brief Contains string names for each defined sensor
const char* sensorDescriptors[DEF_NUM_SENSORS] =
{
  SENSOR_DESCRIPTOR_LIST
};

/***************************************************************************//**
 * @brief
 *   Outputs a line to Capacitive Sensing Profiler naming each sensor
 *
 ******************************************************************************/
void outputsensorDescriptors(void)
{
  uint8_t index;
  // Output control word showing Profiler that line contains sensor names
  printf("*SENSOR_DESCRIPTORS ");

  for (index = 0; index < DEF_NUM_SENSORS; index++) {
    printf("%s | ", sensorDescriptors[index]);
  }
  printf("\n");
}

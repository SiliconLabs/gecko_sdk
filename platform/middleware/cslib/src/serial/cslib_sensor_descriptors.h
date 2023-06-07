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

#ifndef CSLIB_SENSOR_DESCRIPTORS_H
#define CSLIB_SENSOR_DESCRIPTORS_H

#include "cslib_hwconfig.h"

void outputsensorDescriptors(void);

#define HAS_SENSOR_DESCRIPTORS

#if (DEF_NUM_SENSORS == 2)
#define SENSOR_DESCRIPTOR_LIST "B0", "B1"
#elif (DEF_NUM_SENSORS == 3)
#define SENSOR_DESCRIPTOR_LIST "B0", "B1", "B2"
#elif (DEF_NUM_SENSORS == 4)
#define SENSOR_DESCRIPTOR_LIST "B0", "B1", "B2", "B3"
#else
#error "Unsupported CSLIB sensor count."
#endif

#endif // CSLIB_SENSOR_DESCRIPTORS_H

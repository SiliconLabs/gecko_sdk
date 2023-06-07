/***************************************************************************//**
 * @file
 * @brief ESL Tag core interface declarations for sensor functionalities.
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
#ifndef ESL_TAG_SENSOR_CORE_H
#define ESL_TAG_SENSOR_CORE_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>
#include "esl_tag_core.h"

/**************************************************************************//**
 * ESL Tag sensor init function. ESL Core component will call this during the
 * initialization of application. This call is hidden and happens automatically.
 *****************************************************************************/
void esl_sensor_init(void);

/**************************************************************************//**
 * Read interface (only) for ESL Sensor.
 * @return sl_status_t SL_NOT_SUPPORTED if the ESL Sensor component is missing.
 *****************************************************************************/
sl_status_t esl_sensor_read(uint8_t index);

/**************************************************************************//**
 * Get ESL Tag Sensor count
 * @return Number of available sensors
 *****************************************************************************/
uint8_t esl_sensor_get_count(void);
/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_SENSOR_CORE_H

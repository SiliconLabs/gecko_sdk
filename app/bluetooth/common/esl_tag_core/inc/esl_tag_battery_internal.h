/***************************************************************************//**
 * @file
 * @brief ESL Tag built-in battery measurement interface
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
#ifndef ESL_TAG_BATTERY_INTERNAL_H
#define ESL_TAG_BATTERY_INTERNAL_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>
#include "sl_status.h"
#ifdef IADC_PRESENT
#include "em_iadc.h"
#endif // IADC_PRESENT
#ifdef ADC_PRESENT
#include "em_adc.h"
#endif // ADC_PRESENT

/// Definition for unknown battery voltage level (an implausible value)
#define ESL_TAG_BATTERY_LEVEL_UNKNOWN   0

/******************************************************************************
 * Init built-in battery level measurement solution
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_sensor_battery_init(void);

/******************************************************************************
 * Start the built-in battery level measurement, single conversion
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_sensor_battery_read(void);

/******************************************************************************
 * Get battery voltage in milli Volts unit
 * @return uint32_t actual battery voltage if the built-in measurement is
 *                  is enabled, returns the fixed value of @ref
 *                  ESL_TAG_BATTERY_LEVEL_FULL_MILLIVOLTS, otherwise
 *****************************************************************************/
uint32_t esl_sensor_get_battery_voltage_mv(void);

/******************************************************************************
 * Check battery voltage against @ref ESL_TAG_BATTERY_LEVEL_LOW_MILLIVOLTS
 * Will change @ref ESL_BASIC_STATE_SERVICE_NEEDED_BIT state if battery low
 * voltage limit is reached.
 *****************************************************************************/
void esl_sensor_core_check_battery_level(void);

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_BATTERY_INTERNAL_H

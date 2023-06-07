/***************************************************************************//**
 * @file
 * @brief ESL Tag core WEAK implementations of sensor functionalities.
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
#include "em_common.h"
#include "esl_tag_core_config.h"
#include "esl_tag_sensor_core.h"
#include "esl_tag_battery_internal.h"

SL_WEAK sl_status_t esl_sensor_battery_read(void)
{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK sl_status_t  esl_sensor_battery_init(void)
{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK uint32_t esl_sensor_get_battery_voltage_mv(void)
{
  return ESL_TAG_BATTERY_LEVEL_FULL_MILLIVOLTS;
}

SL_WEAK void esl_sensor_init(void)
{
}

SL_WEAK uint8_t esl_sensor_get_count(void)
{
  return 0;
}

SL_WEAK sl_status_t esl_sensor_read(uint8_t index)
{
  (void)index;

  return SL_STATUS_NOT_AVAILABLE;
}

void esl_sensor_core_check_battery_level(void)
{
  uint32_t battery_level = esl_sensor_get_battery_voltage_mv();

  if (battery_level > ESL_TAG_BATTERY_LEVEL_UNKNOWN
      && battery_level <= ESL_TAG_BATTERY_LEVEL_LOW_MILLIVOLTS) {
    esl_core_set_basic_state_bit(ESL_BASIC_STATE_SERVICE_NEEDED_BIT, ESL_SET);
  }
}

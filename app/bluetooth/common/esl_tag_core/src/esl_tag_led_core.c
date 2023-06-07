/***************************************************************************//**
 * @file
 * @brief ESL Tag core WEAK implementations of LED functionalities.
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
#include "esl_tag_led_core.h"

SL_WEAK void esl_led_init(void)
{
}

SL_WEAK sl_status_t esl_led_control(esl_led_control_t *control_param)
{
  (void)control_param;
  // real implementation shall set ESL_BASIC_STATE_ACTIVE_LED_BIT according to
  // the cumulative status of all LEDs
  esl_core_set_basic_state_bit(ESL_BASIC_STATE_ACTIVE_LED_BIT, ESL_CLEAR);

  return SL_STATUS_NOT_AVAILABLE;
}

SL_WEAK uint8_t esl_led_get_count()
{
  return 0;
}

SL_WEAK bool esl_led_is_srgb(uint8_t led_index)
{
  (void)led_index;
  return false;
}

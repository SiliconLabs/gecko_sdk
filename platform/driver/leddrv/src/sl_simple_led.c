/***************************************************************************//**
 * @file
 * @brief Simple LED Driver
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_simple_led.h"

#include "em_cmu.h"

sl_status_t sl_simple_led_init(void *context)
{
  sl_simple_led_context_t *led = context;
  #if !defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_HFPER, true);
  #endif //!defined(_SILICON_LABS_32B_SERIES_2)

  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(led->port,
                  led->pin,
                  gpioModePushPull,
                  !led->polarity);

  return SL_STATUS_OK;
}

void sl_simple_led_turn_on(void *context)
{
  sl_simple_led_context_t *led = context;
  if (led->polarity == SL_SIMPLE_LED_POLARITY_ACTIVE_LOW) {
    GPIO_PinOutClear(led->port, led->pin);
  } else {
    GPIO_PinOutSet(led->port, led->pin);
  }
}

void sl_simple_led_turn_off(void *context)
{
  sl_simple_led_context_t *led = context;
  if (led->polarity == SL_SIMPLE_LED_POLARITY_ACTIVE_LOW) {
    GPIO_PinOutSet(led->port, led->pin);
  } else {
    GPIO_PinOutClear(led->port, led->pin);
  }
}

void sl_simple_led_toggle(void *context)
{
  sl_simple_led_context_t *led = context;
  GPIO_PinOutToggle(led->port, led->pin);
}

sl_led_state_t sl_simple_led_get_state(void *context)
{
  sl_simple_led_context_t *led = context;
  sl_led_state_t value = (sl_led_state_t)GPIO_PinOutGet(led->port, led->pin);

  if (led->polarity == SL_SIMPLE_LED_POLARITY_ACTIVE_LOW) {
    return !value;
  } else {
    return value;
  }
}

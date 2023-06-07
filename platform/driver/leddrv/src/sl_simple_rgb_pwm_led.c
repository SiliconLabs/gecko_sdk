/***************************************************************************//**
 * @file
 * @brief Simple RGB PWM LED Driver
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stddef.h>

#include "sl_pwm_led.h"
#include "sl_simple_rgb_pwm_led.h"

/*
 *  Public functions
 */
sl_status_t sl_simple_rgb_pwm_led_init(void *rgb)
{
  sl_status_t status;
  sl_simple_rgb_pwm_led_context_t *context = (sl_simple_rgb_pwm_led_context_t *)rgb;

  status = sl_pwm_led_init(context->red);
  if (status == SL_STATUS_FAIL) {
    return SL_STATUS_FAIL;
  }
  status = sl_pwm_led_init(context->green);
  if (status == SL_STATUS_FAIL) {
    return SL_STATUS_FAIL;
  }
  status = sl_pwm_led_init(context->blue);
  if (status == SL_STATUS_FAIL) {
    return SL_STATUS_FAIL;
  }

  context->state = SL_LED_CURRENT_STATE_OFF;

  return status;
}

void sl_simple_rgb_pwm_led_turn_on(void *rgb)
{
  sl_simple_rgb_pwm_led_context_t *context = (sl_simple_rgb_pwm_led_context_t *)rgb;

  sl_pwm_led_start(context->red);
  sl_pwm_led_start(context->green);
  sl_pwm_led_start(context->blue);

  context->state = SL_LED_CURRENT_STATE_ON;
}

void sl_simple_rgb_pwm_led_turn_off(void *rgb)
{
  sl_simple_rgb_pwm_led_context_t *context = (sl_simple_rgb_pwm_led_context_t *)rgb;

  sl_pwm_led_stop(context->red);
  sl_pwm_led_stop(context->green);
  sl_pwm_led_stop(context->blue);

  context->state = SL_LED_CURRENT_STATE_OFF;
}

void sl_simple_rgb_pwm_led_toggle(void *rgb)
{
  sl_simple_rgb_pwm_led_context_t *context = (sl_simple_rgb_pwm_led_context_t *)rgb;
  if (sl_simple_rgb_pwm_led_get_state(context) == SL_LED_CURRENT_STATE_OFF) {
    sl_simple_rgb_pwm_led_turn_on(context);
  } else {
    sl_simple_rgb_pwm_led_turn_off(context);
  }
}

sl_led_state_t sl_simple_rgb_pwm_led_get_state(void *rgb)
{
  sl_simple_rgb_pwm_led_context_t *context = (sl_simple_rgb_pwm_led_context_t *)rgb;

  return context->state;
}

void sl_simple_rgb_pwm_led_set_color(void *rgb, uint16_t red, uint16_t green, uint16_t blue)
{
  sl_simple_rgb_pwm_led_context_t *context = (sl_simple_rgb_pwm_led_context_t *)rgb;

  context->red->set_color(context->red, red);
  context->red->set_color(context->green, green);
  context->red->set_color(context->blue, blue);
}

void sl_simple_rgb_pwm_led_get_color(void *rgb, uint16_t *red, uint16_t *green, uint16_t *blue)
{
  sl_simple_rgb_pwm_led_context_t *context = (sl_simple_rgb_pwm_led_context_t *)rgb;

  context->red->get_color(context->red, red);
  context->red->get_color(context->green, green);
  context->red->get_color(context->blue, blue);
}

/*
 *  API functions (extentions to the Common LED Driver API)
 */
void sl_led_set_rgb_color(const sl_led_rgb_pwm_t *led_handle, uint16_t red, uint16_t green, uint16_t blue)
{
  led_handle->set_rgb_color(led_handle->led_common.context, red, green, blue);
}

void sl_led_get_rgb_color(const sl_led_rgb_pwm_t *led_handle, uint16_t *red, uint16_t *green, uint16_t *blue)
{
  led_handle->get_rgb_color(led_handle->led_common.context, red, green, blue);
}

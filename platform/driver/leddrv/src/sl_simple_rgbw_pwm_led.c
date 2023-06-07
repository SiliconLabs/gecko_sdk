/***************************************************************************//**
 * @file
 * @brief Simple RGBW PWM LED Driver
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
#include "sl_simple_rgbw_pwm_led.h"

/*
 *  Public functions
 */
sl_status_t sl_simple_rgbw_pwm_led_init(void *rgbw)
{
  sl_status_t status;
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;

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
  status = sl_pwm_led_init(context->white);
  if (status == SL_STATUS_FAIL) {
    return SL_STATUS_FAIL;
  }

  context->state = SL_LED_CURRENT_STATE_OFF;

  return status;
}

void sl_simple_rgbw_pwm_led_turn_on(void *rgbw)
{
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;

  sl_pwm_led_start(context->red);
  sl_pwm_led_start(context->green);
  sl_pwm_led_start(context->blue);
  sl_pwm_led_start(context->white);

  context->state = SL_LED_CURRENT_STATE_ON;
}

void sl_simple_rgbw_pwm_led_turn_off(void *rgbw)
{
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;

  sl_pwm_led_stop(context->red);
  sl_pwm_led_stop(context->green);
  sl_pwm_led_stop(context->blue);
  sl_pwm_led_stop(context->white);

  context->state = SL_LED_CURRENT_STATE_OFF;
}

void sl_simple_rgbw_pwm_led_toggle(void *rgbw)
{
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;
  if (sl_simple_rgbw_pwm_led_get_state(context) == SL_LED_CURRENT_STATE_OFF) {
    sl_simple_rgbw_pwm_led_turn_on(context);
  } else {
    sl_simple_rgbw_pwm_led_turn_off(context);
  }
}

sl_led_state_t sl_simple_rgbw_pwm_led_get_state(void *rgbw)
{
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;

  return context->state;
}

void sl_simple_rgbw_pwm_led_set_color(void *rgbw, uint16_t red, uint16_t green, uint16_t blue, uint16_t white)
{
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;

  context->red->set_color(context->red, red);
  context->red->set_color(context->green, green);
  context->red->set_color(context->blue, blue);
  context->red->set_color(context->white, white);
}

void sl_simple_rgbw_pwm_led_get_color(void *rgbw, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *white)
{
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;

  context->red->get_color(context->red, red);
  context->red->get_color(context->green, green);
  context->red->get_color(context->blue, blue);
  context->red->get_color(context->white, white);
}

/*
 *  API functions (extentions to the Common LED Driver API)
 */
void sl_led_set_rgbw_color(const sl_led_rgbw_pwm_t *led_handle, uint16_t red, uint16_t green, uint16_t blue, uint16_t white)
{
  led_handle->set_rgbw_color(led_handle->led_common.context, red, green, blue, white);
}

void sl_led_get_rgbw_color(const sl_led_rgbw_pwm_t *led_handle, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *white)
{
  led_handle->get_rgbw_color(led_handle->led_common.context, red, green, blue, white);
}

/***************************************************************************//**
 * @file
 * @brief Simple RGBW PWM LED Driver
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
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
  context->red->set_color(context->red, context->red->level);
  context->green->set_color(context->green, context->green->level);
  context->blue->set_color(context->blue, context->blue->level);
  context->white->set_color(context->white, context->white->level);

  context->state = SL_LED_CURRENT_STATE_ON;
}

void sl_simple_rgbw_pwm_led_turn_off(void *rgbw)
{
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;

  context->red->set_color(context->red, SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  context->green->set_color(context->green, SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  context->blue->set_color(context->blue, SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  context->white->set_color(context->white, SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);

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
  if (context->red->level == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF
      && context->green->level == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF
      && context->blue->level == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF
      && context->white->level == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF) {
    context->state = SL_LED_CURRENT_STATE_OFF;
    return context->state;
  } else {
    context->state = SL_LED_CURRENT_STATE_ON;
    return context->state;
  }
}

void sl_simple_rgbw_pwm_led_set_color(void *rgbw, uint16_t red, uint16_t green, uint16_t blue, uint16_t white)
{
  sl_simple_rgbw_pwm_led_context_t *context = (sl_simple_rgbw_pwm_led_context_t *)rgbw;
  context->red->set_color(context->red, red);
  context->red->set_color(context->green, green);
  context->red->set_color(context->blue, blue);
  context->red->set_color(context->white, white);

  if ((red == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF) && (green == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF)
      && (blue == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF) && (white == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF)) {
    // All colors set to OFF. I.e. the same as if the user issued a turn off command
    sl_simple_rgbw_pwm_led_turn_off(context);
  } else {
    sl_simple_rgbw_pwm_led_turn_on(context);
  }
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

/**
 * @file
 * Platform abstraction for LED Bulb application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#include <LEDBulb_hw.h>
#include <ZAF_Actuator.h>
#include <sl_simple_rgb_pwm_led.h>
#include <ev_man.h>
#include <events.h>
#include <board.h>
#include <zaf_event_helper.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

#if defined(BUILDING_WITH_UC)
#include "sl_simple_rgb_pwm_led_instances.h"
#else

#include "sl_simple_rgb_pwm_led_led_config.h"

sl_led_pwm_t red_led = {
  .port = SL_SIMPLE_RGB_PWM_LED_LED_RED_PORT,
  .pin = SL_SIMPLE_RGB_PWM_LED_LED_RED_PIN,
  .polarity = SL_SIMPLE_RGB_PWM_LED_LED_RED_POLARITY,
  .channel = SL_SIMPLE_RGB_PWM_LED_LED_RED_CHANNEL,
#if defined(SL_SIMPLE_RGB_PWM_LED_LED_RED_LOC)
  .location = SL_SIMPLE_RGB_PWM_LED_LED_RED_LOC,
#endif
  .timer = SL_SIMPLE_RGB_PWM_LED_LED_PERIPHERAL,
  .frequency = SL_SIMPLE_RGB_PWM_LED_LED_FREQUENCY,
  .resolution = SL_SIMPLE_RGB_PWM_LED_LED_RESOLUTION,
};

sl_led_pwm_t green_led = {
  .port = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_PORT,
  .pin = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_PIN,
  .polarity = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_POLARITY,
  .channel = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_CHANNEL,
#if defined(SL_SIMPLE_RGB_PWM_LED_LED_GREEN_LOC)
  .location = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_LOC,
#endif
  .timer = SL_SIMPLE_RGB_PWM_LED_LED_PERIPHERAL,
  .frequency = SL_SIMPLE_RGB_PWM_LED_LED_FREQUENCY,
  .resolution = SL_SIMPLE_RGB_PWM_LED_LED_RESOLUTION,
};

sl_led_pwm_t blue_led = {
  .port = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_PORT,
  .pin = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_PIN,
  .polarity = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_POLARITY,
  .channel = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_CHANNEL,
#if defined(SL_SIMPLE_RGB_PWM_LED_LED_BLUE_LOC)
  .location = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_LOC,
#endif
  .timer = SL_SIMPLE_RGB_PWM_LED_LED_PERIPHERAL,
  .frequency = SL_SIMPLE_RGB_PWM_LED_LED_FREQUENCY,
  .resolution = SL_SIMPLE_RGB_PWM_LED_LED_RESOLUTION,
};

sl_simple_rgb_pwm_led_context_t simple_rgb_pwm_led_context = {
  .red = &red_led,
  .green = &green_led,
  .blue = &blue_led,

  .timer = SL_SIMPLE_RGB_PWM_LED_LED_PERIPHERAL,
  .frequency = SL_SIMPLE_RGB_PWM_LED_LED_FREQUENCY,
  .resolution = SL_SIMPLE_RGB_PWM_LED_LED_RESOLUTION,
};

const sl_led_rgb_pwm_t sl_led = {
  .led_common.context = &simple_rgb_pwm_led_context,
  .led_common.init = sl_simple_rgb_pwm_led_init,
  .led_common.turn_on = sl_simple_rgb_pwm_led_turn_on,
  .led_common.turn_off = sl_simple_rgb_pwm_led_turn_off,
  .led_common.toggle = sl_simple_rgb_pwm_led_toggle,
  .led_common.get_state = sl_simple_rgb_pwm_led_get_state,
  .set_rgb_color = sl_simple_rgb_pwm_led_set_color,
  .get_rgb_color = sl_simple_rgb_pwm_led_get_color,
};

#endif // BUILDING_WITH_UC

static uint8_t multilevel_switch_max;
static uint8_t multilevel_switch_value;
static uint8_t color_switch_max;
static uint8_t color_switch_red_value;
static uint8_t color_switch_green_value;
static uint8_t color_switch_blue_value;

static void update_rgbw_led(void)
{
  DPRINTF("%s Setting RGB=(%u,%u,%u)\n", __func__,
          (color_switch_red_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_green_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max);
  sl_led_set_rgb_color(&sl_led,
                        (uint16_t)((color_switch_red_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_green_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max));
}

static void button_handler(BUTTON_EVENT event, bool is_called_from_isr)
{
  EVENT_APP app_event = EVENT_EMPTY;

  if (BTN_EVENT_LONG_PRESS(APP_BUTTON_LEARN_RESET) == event)
  {
    app_event = EVENT_APP_BUTTON_LEARN_RESET_LONG_PRESS;
  }
  else if (BTN_EVENT_SHORT_PRESS(APP_BUTTON_LEARN_RESET) == event)
  {
    app_event = EVENT_APP_BUTTON_LEARN_RESET_SHORT_PRESS;
  }

  if (app_event != EVENT_EMPTY)
  {
    if (is_called_from_isr)
    {
      ZAF_EventHelperEventEnqueueFromISR(app_event);
    }
    else
    {
      ZAF_EventHelperEventEnqueue(app_event);
    }
  }
}

void LEDBulb_hw_init(uint8_t multilevel_switch_max_, uint8_t color_switch_max_)
{
  DPRINT("--------------------------------\n");
  DPRINTF("%s: Toggle learn mode\n", Board_GetButtonLabel(APP_BUTTON_LEARN_RESET));
  DPRINT("      Hold 5 sec: Reset\n");
  DPRINTF("%s: Learn mode + identify\n", Board_GetLedLabel(APP_LED_INDICATOR));
  DPRINT("--------------------------------\n\n");

  Board_SetButtonCallback(button_handler);
  Board_EnableButton(APP_BUTTON_LEARN_RESET);

  multilevel_switch_max = multilevel_switch_max_;
  color_switch_max = color_switch_max_;

#if !defined(BUILDING_WITH_UC)
  sl_led_init((sl_led_t *)&sl_led);
#endif /* !defined(BUILDING_WITH_UC) */
}

void LEDBulb_hw_callback_RED(s_colorComponent * colorComponent)
{
  color_switch_red_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
  update_rgbw_led();
}

void LEDBulb_hw_callback_GREEN(s_colorComponent * colorComponent)
{
  color_switch_green_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
  update_rgbw_led();
}
void LEDBulb_hw_callback_BLUE(s_colorComponent * colorComponent)
{
  color_switch_blue_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
  update_rgbw_led();
}

void LEDBulb_hw_multilevel_switch_handler(cc_multilevel_switch_t * p_switch)
{
  multilevel_switch_value = cc_multilevel_switch_get_current_value(p_switch);
  update_rgbw_led();
}

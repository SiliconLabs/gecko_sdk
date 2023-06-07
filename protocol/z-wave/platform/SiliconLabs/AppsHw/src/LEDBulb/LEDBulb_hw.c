/**
 * @file
 * Platform abstraction for LED Bulb application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#include <app_hw.h>
#include <ZAF_Actuator.h>
#include "CC_ColorSwitch.h"
#include <CC_MultilevelSwitch_Support.h>
#include <sl_simple_rgb_pwm_led.h>
#include <sl_simple_rgb_pwm_led_instances.h>
#include <ev_man.h>
#include <events.h>
#include <board.h>
#include <zaf_event_distributor_soc.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

static uint8_t multilevel_switch_value;
static uint8_t color_switch_red_value;
static uint8_t color_switch_green_value;
static uint8_t color_switch_blue_value;

static void update_rgbw_led(void)
{
  uint8_t multilevel_switch_max;

  multilevel_switch_max = cc_multilevel_switch_get_max_value();

  DPRINTF("%s Setting RGB=(%u,%u,%u)\n", __func__,
          (color_switch_red_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_green_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max);
  sl_led_set_rgb_color(&sl_simple_rgb_pwm_led_led,
                        (uint16_t)((color_switch_red_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_green_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max));
}

static void button_handler(BUTTON_EVENT event, bool is_called_from_isr)
{
  uint8_t app_event = EVENT_EMPTY;

  if (BTN_EVENT_LONG_PRESS(APP_BUTTON_LEARN_RESET) == event)
  {
    app_event = EVENT_SYSTEM_RESET;
  }
  else if (BTN_EVENT_SHORT_PRESS(APP_BUTTON_LEARN_RESET) == event)
  {
    app_event = EVENT_SYSTEM_LEARNMODE_TOGGLE;
  }

  if (app_event != EVENT_EMPTY)
  {
    if (is_called_from_isr)
    {
      zaf_event_distributor_enqueue_app_event_from_isr(app_event);
    }
    else
    {
      zaf_event_distributor_enqueue_app_event(app_event);
    }
  }
}

void app_hw_init(void)
{
  DPRINT("--------------------------------\n");
  DPRINTF("%s: Toggle learn mode\n", Board_GetButtonLabel(APP_BUTTON_LEARN_RESET));
  DPRINT("      Hold 5 sec: Reset\n");
  DPRINTF("%s: Learn mode + identify\n", Board_GetLedLabel(APP_LED_INDICATOR));
  DPRINT("--------------------------------\n\n");

  Board_SetButtonCallback(button_handler);
  Board_EnableButton(APP_BUTTON_LEARN_RESET);
}

void cc_color_switch_cb(s_colorComponent * colorComponent)
{
  switch (colorComponent->colorId) {
    case ECOLORCOMPONENT_RED:
      color_switch_red_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
      break;
    case ECOLORCOMPONENT_GREEN:
      color_switch_green_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
      break;
    case ECOLORCOMPONENT_BLUE:
      color_switch_blue_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
      break;
    default:
      break;
  }
  update_rgbw_led();
}

void cc_multilevel_switch_support_cb(cc_multilevel_switch_t * p_switch)
{
  multilevel_switch_value = cc_multilevel_switch_get_current_value(p_switch);
  update_rgbw_led();
}

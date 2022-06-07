/**
 * @file
 * Platform abstraction for Power Strip application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#include <PowerStrip_hw.h>
#include <ZAF_Actuator.h>
#include <sl_simple_rgb_pwm_led.h>
#include <Assert.h>
#include <ev_man.h>
#include <events.h>
#include <board.h>
#include <zaf_event_helper.h>
//#define DEBUGPRINT
#include "DebugPrint.h"
#include <board.h>


#define OUTLET1_TOGGLE_BTN        APP_BUTTON_A
#define OUTLET2_DIMMER_BTN        APP_BUTTON_B
#define NOTIFICATION_TOGGLE_BTN   APP_BUTTON_C

#define OUTLET1_STATUS_LED   APP_LED_A

/* Ensure we did not allocate the same physical button or led to more than one function */
STATIC_ASSERT((APP_BUTTON_LEARN_RESET != OUTLET1_TOGGLE_BTN) &&
              (APP_BUTTON_LEARN_RESET != OUTLET2_DIMMER_BTN) &&
              (APP_BUTTON_LEARN_RESET != NOTIFICATION_TOGGLE_BTN) &&
              (OUTLET1_TOGGLE_BTN != OUTLET2_DIMMER_BTN) &&
              (OUTLET1_TOGGLE_BTN != NOTIFICATION_TOGGLE_BTN) &&
              (OUTLET2_DIMMER_BTN != NOTIFICATION_TOGGLE_BTN),
              STATIC_ASSERT_FAILED_button_overlap);
STATIC_ASSERT((APP_LED_INDICATOR != OUTLET1_STATUS_LED),
              STATIC_ASSERT_FAILED_led_overlap);


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
  else if ((BTN_EVENT_SHORT_PRESS(OUTLET1_TOGGLE_BTN) == event) ||
           (BTN_EVENT_UP(OUTLET1_TOGGLE_BTN) == event))
  {
    app_event = EVENT_APP_BUTTON_OUTLET1_TOGGLE;
  }
  else if (BTN_EVENT_SHORT_PRESS(OUTLET2_DIMMER_BTN) == event)
  {
    app_event = EVENT_APP_BUTTON_OUTLET2_DIMMER_SHORT_PRESS;
  }
  else if (BTN_EVENT_UP(OUTLET2_DIMMER_BTN) == event)
  {
    app_event = EVENT_APP_BUTTON_OUTLET2_DIMMER_RELEASE;
  }
  else if (BTN_EVENT_HOLD(OUTLET2_DIMMER_BTN) == event)
  {
    app_event = EVENT_APP_BUTTON_OUTLET2_DIMMER_HOLD;
  }
  else if ((BTN_EVENT_SHORT_PRESS(NOTIFICATION_TOGGLE_BTN) == event) ||
           (BTN_EVENT_UP(NOTIFICATION_TOGGLE_BTN) == event))
  {
    app_event = EVENT_APP_BUTTON_NOTIFICATION_TOGGLE;
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

void PowerStrip_hw_init(void)
{
  DPRINT("------------------------------\n");
  DPRINTF("%s: Outlet 1 toggle on/off\n", Board_GetButtonLabel(OUTLET1_TOGGLE_BTN));
  DPRINTF("%s: Outlet 2 dim/on/off\n", Board_GetButtonLabel(OUTLET2_DIMMER_BTN));
  DPRINT("      Hold: Dim up/down\n");
  DPRINTF("%s: Toggle notification every 30 sec\n", Board_GetButtonLabel(NOTIFICATION_TOGGLE_BTN));
  DPRINTF("%s: Toggle learn mode\n", Board_GetButtonLabel(APP_BUTTON_LEARN_RESET));
  DPRINT("      Hold 5 sec: Reset\n");
  DPRINTF("%s: Learn mode + identify\n", Board_GetLedLabel(APP_LED_INDICATOR));
  DPRINTF("%s: Outlet 1 status on/off\n", Board_GetLedLabel(OUTLET1_STATUS_LED));
  DPRINT("RGB: Outlet 2 level/intensity\n");
  DPRINT("------------------------------\n\n");

  Board_SetButtonCallback(button_handler);
  Board_EnableButton(APP_BUTTON_LEARN_RESET);
  Board_EnableButton(OUTLET1_TOGGLE_BTN);
  Board_EnableButton(OUTLET2_DIMMER_BTN);
  Board_EnableButton(NOTIFICATION_TOGGLE_BTN);

#if !defined(BUILDING_WITH_UC)
  sl_led_init((sl_led_t *)&sl_led);
#endif /* !defined(BUILDING_WITH_UC) */
}

void PowerStrip_hw_binary_switch_handler(bool on)
{
  Board_SetLed(OUTLET1_STATUS_LED, on ? LED_ON : LED_OFF);
}

void PowerStrip_hw_multilevel_switch_handler(cc_multilevel_switch_t * p_switch)
{
  const uint8_t level = ZAF_Actuator_GetCurrentValue(&p_switch->actuator);
  sl_led_set_rgb_color(&sl_led, (uint16_t)level, (uint16_t)level, (uint16_t)level);
}

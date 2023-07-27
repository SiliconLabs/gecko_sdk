/**
 * @file
 * Platform abstraction for Power Strip application
 * 
 * @copyright 2023 Silicon Laboratories Inc.
 */
#include <app_hw.h>
#include <ZAF_Actuator.h>
#if !defined(RADIO_BOARD_BRD2705A)
#include <sl_simple_rgb_pwm_led.h>
#include <sl_simple_rgb_pwm_led_instances.h>
#endif
#include <sl_pwm.h>
#include <sl_pwm_instances.h>
#include <Assert.h>
#include <ev_man.h>
#include <events.h>
#include <board.h>
#include <zaf_event_distributor_soc.h>
#include "CC_MultilevelSwitch_Support.h"
#include "CC_BinarySwitch.h"
#include "PowerStrip_buttons.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

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
  else if ((BTN_EVENT_SHORT_PRESS(OUTLET1_TOGGLE_BTN) == event) ||
           (BTN_EVENT_UP(OUTLET1_TOGGLE_BTN) == event))
  {
    app_event = EVENT_APP_OUTLET1_TOGGLE;
  }
  else if (BTN_EVENT_SHORT_PRESS(OUTLET2_DIMMER_BTN) == event)
  {
    app_event = EVENT_APP_OUTLET2_DIMMER_SHORT_PRESS;
  }
  else if (BTN_EVENT_UP(OUTLET2_DIMMER_BTN) == event)
  {
    app_event = EVENT_APP_OUTLET2_DIMMER_RELEASE;
  }
  else if (BTN_EVENT_HOLD(OUTLET2_DIMMER_BTN) == event)
  {
    app_event = EVENT_APP_OUTLET2_DIMMER_HOLD;
  }
  else if ((BTN_EVENT_SHORT_PRESS(NOTIFICATION_TOGGLE_BTN) == event) ||
           (BTN_EVENT_UP(NOTIFICATION_TOGGLE_BTN) == event))
  {
    app_event = EVENT_APP_NOTIFICATION_TOGGLE;
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
  #if defined(THUNDERBOARD)
  sl_pwm_init_instances();
  sl_pwm_start(&sl_pwm_led1);
  #endif
}

void cc_binary_switch_handler(cc_binary_switch_t * p_switch)
{
  uint8_t value = ZAF_Actuator_GetCurrentValue(&p_switch->actuator);
  Board_SetLed(OUTLET1_STATUS_LED, (value > 0) ? LED_ON : LED_OFF);
}

void cc_multilevel_switch_support_cb(cc_multilevel_switch_t * p_switch)
{
  const uint8_t level = ZAF_Actuator_GetCurrentValue(&p_switch->actuator);
  #if !defined(THUNDERBOARD)
  sl_led_set_rgb_color(&sl_simple_rgb_pwm_led_led, (uint16_t)level, (uint16_t)level, (uint16_t)level);
  #else
  sl_pwm_set_duty_cycle(&sl_pwm_led1, (uint8_t)level);
  #endif
}

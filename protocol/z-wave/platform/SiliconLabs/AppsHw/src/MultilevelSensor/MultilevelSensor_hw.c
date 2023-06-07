/**
 * @file
 * Platform abstraction for Multilevel Sensor application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#include <app_hw.h>
#include <Assert.h>
#include <ev_man.h>
#include <events.h>
#include <board.h>
#include <zaf_event_distributor_soc.h>
//#define DEBUGPRINT
#include "DebugPrint.h"
#include <CC_Battery.h>
#include <zpal_init.h>

#include <em_emu.h>
#include <ADC.h>

#define MY_BATTERY_SPEC_LEVEL_FULL         3000  // My battery's 100% level (millivolts)
#define MY_BATTERY_SPEC_LEVEL_EMPTY        2400  // My battery's 0% level (millivolts)

// Only use BTN PB1 and PB2 on Multilevel Sensor
// PB3 and PB4 from the extension board use the same 
// Ports and Pins that the I2C uses
#define EVENT_BTN             APP_BUTTON_LEARN_RESET
#define REPORT_BTN            APP_BUTTON_A         // This button cannot wake up the device from EM4

#define APP_LED_POWER_ON      APP_LED_A

/* Ensure we did not allocate the same physical button to more than one function */
STATIC_ASSERT((APP_BUTTON_LEARN_RESET != REPORT_BTN),
              STATIC_ASSERT_FAILED_button_overlap);

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
  else if (BTN_EVENT_SHORT_PRESS(REPORT_BTN) == event)
  {
    app_event = EVENT_APP_SEND_BATTERY_LEVEL_AND_SENSOR_REPORT;
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
  /* Init indicator LED */
  Board_SetLed(APP_LED_POWER_ON, LED_ON);

  /* hardware initialization */
  Board_SetButtonCallback(button_handler);
  Board_EnableButton(APP_BUTTON_LEARN_RESET);
  Board_EnableButton(REPORT_BTN);
  Board_EnableButton(EVENT_BTN);

  DPRINT("-----------------------------\n");
  DPRINTF("%s: Send battery and temperature report\n", Board_GetButtonLabel(REPORT_BTN));
  DPRINTF("%s: Toggle learn mode\n", Board_GetButtonLabel(APP_BUTTON_LEARN_RESET));
  DPRINT("      Hold 5 sec: Reset\n");
  DPRINTF("%s: Learn mode + identify\n", Board_GetLedLabel(APP_LED_INDICATOR));
  DPRINT("-----------------------------\n\n");
  DPRINTF("\r\nBoard_GetGpioEm4Flags()      = 0b%08x", Board_GetGpioEm4Flags());

  const zpal_reset_reason_t reset_reason = zpal_get_reset_reason();
  if (reset_reason == ZPAL_RESET_REASON_DEEP_SLEEP_WUT || reset_reason == ZPAL_RESET_REASON_DEEP_SLEEP_EXT_INT)
  {
    #ifdef DEBUGPRINT
      Board_DebugPrintEm4WakeupFlags(Board_GetGpioEm4Flags());
    #endif
  }

}

uint8_t
CC_Battery_BatteryGet_handler(uint8_t endpoint)
{
  uint32_t VBattery;
  uint8_t  accurateLevel;
  uint8_t  roundedLevel;
  uint8_t reporting_decrements;

  UNUSED(endpoint);

  /*
   * Simple example how to use the ADC to measure the battery voltage
   * and convert to a percentage battery level on a linear scale.
   */
  ADC_Enable();
  VBattery = ADC_Measure_VSupply();
  DPRINTF("\r\nBattery voltage: %dmV", VBattery);
  ADC_Disable();

  if (MY_BATTERY_SPEC_LEVEL_FULL <= VBattery)
  {
    // Level is full
    return (uint8_t)CMD_CLASS_BATTERY_LEVEL_FULL;
  }
  else if (MY_BATTERY_SPEC_LEVEL_EMPTY > VBattery)
  {
    // Level is empty (<0%)
    return (uint8_t)CMD_CLASS_BATTERY_LEVEL_WARNING;
  }
  else
  {
    reporting_decrements = cc_battery_config_get_reporting_decrements();
    // Calculate the percentage level from 0 to 100
    accurateLevel = (uint8_t)((100 * (VBattery - MY_BATTERY_SPEC_LEVEL_EMPTY)) / (MY_BATTERY_SPEC_LEVEL_FULL - MY_BATTERY_SPEC_LEVEL_EMPTY));

    // And round off to the nearest "reporting_decrements" level
    roundedLevel = (accurateLevel / reporting_decrements) * reporting_decrements; // Rounded down
    if ((accurateLevel % reporting_decrements) >= (reporting_decrements / 2))
    {
      roundedLevel += reporting_decrements; // Round up
    }
  }
  return roundedLevel;
}

void EMU_EM4PresleepHook(void)
{
  Board_SetLed(APP_LED_POWER_ON, LED_OFF);
}

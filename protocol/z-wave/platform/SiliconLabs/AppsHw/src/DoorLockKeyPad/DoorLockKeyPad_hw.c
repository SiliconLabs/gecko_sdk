/**
 * @file
 * Platform abstraction for Door Lock Key Pad application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#include <app_hw.h>
#include <board.h>
#include <ADC.h>
#include <events.h>
#include <Assert.h>
#include <zaf_event_distributor_soc.h>
//#define DEBUGPRINT
#include <DebugPrint.h>
#include <CC_Battery.h>
#include "CC_DoorLock.h"
#include "CC_UserCode.h"
#include "cc_user_code_config.h"
#include "AppTimer.h"

#define DOORHANDLE_BTN         APP_BUTTON_A
#define BATTERY_REPORT_BTN     APP_BUTTON_B
#define ENTER_USER_CODE        APP_BUTTON_C
#define DOOR_HANDLE_STATUS_LED APP_LED_A
#define BOLT_STATUS_LED        APP_LED_B

/* Ensure we did not allocate the same physical button or led to more than one function */
STATIC_ASSERT((APP_BUTTON_LEARN_RESET != DOORHANDLE_BTN) &&
              (APP_BUTTON_LEARN_RESET != BATTERY_REPORT_BTN) &&
              (APP_BUTTON_LEARN_RESET != ENTER_USER_CODE) &&
              (DOORHANDLE_BTN != BATTERY_REPORT_BTN) &&
              (DOORHANDLE_BTN != ENTER_USER_CODE) &&
              (BATTERY_REPORT_BTN != ENTER_USER_CODE),
              STATIC_ASSERT_FAILED_button_overlap);
STATIC_ASSERT((APP_LED_INDICATOR != DOOR_HANDLE_STATUS_LED) &&
              (APP_LED_INDICATOR != BOLT_STATUS_LED) &&
              (DOOR_HANDLE_STATUS_LED != BOLT_STATUS_LED),
              STATIC_ASSERT_FAILED_led_overlap);


#define MY_BATTERY_SPEC_LEVEL_FULL         3000  // My battery's 100% level (millivolts)
#define MY_BATTERY_SPEC_LEVEL_EMPTY        2400  // My battery's 0% level (millivolts)

/// Timeout simulates hardware action. Can be removed when the actual hardware is used.
#define CC_DOOR_LOCK_DEFAULT_OPERATION_SET_TIMEOUT 2000

static door_lock_hw_data_t door_lock_hw = {0};

/// Timer used by Supervision Get handler.
static SSwTimer door_lock_operation_set_timer;

static uint8_t user_code[] = CC_USER_CODE_DEFAULT;
static cc_user_code_event_validate_data_t user_code_event_validate_data;

static void door_lock_operation_set_callback(SSwTimer *pTimer);

static void button_handler(BUTTON_EVENT event, bool is_called_from_isr)
{
  uint8_t app_event = EVENT_EMPTY;
  uint16_t command_class = COMMAND_CLASS_NO_OPERATION;
  uint8_t cc_event;
  void *cc_data;

      /* Outside door handle #1 deactivated?
       * NB: If DOORHANDLE_BTN is held for more than 5 seconds then BTN_EVENT_LONG_PRESS
       *     will be received on DOORHANDLE_BTN release instead of BTN_EVENT_UP
       */
   
  if (BTN_EVENT_LONG_PRESS(APP_BUTTON_LEARN_RESET) == event)
  {
    app_event = EVENT_SYSTEM_RESET;
  }
  else if (BTN_EVENT_SHORT_PRESS(APP_BUTTON_LEARN_RESET) == event)
  {
    app_event = EVENT_SYSTEM_LEARNMODE_TOGGLE;
  }
  else if (BTN_EVENT_SHORT_PRESS(BATTERY_REPORT_BTN) == event)
  {
    app_event = EVENT_APP_BATTERY_REPORT;
  }
  else if (BTN_EVENT_SHORT_PRESS(ENTER_USER_CODE) == event)
  {
    /*
     * This events simulates entering a user code on a key pad.
     * The entered user code is hardcoded with the value of the default user
     * code of the application. Hence, the lock can be secured/unsecured by
     * default.
     *
     * If the user code for user ID 1 is changed to something else than the
     * default user code the lock can no longer be secured/unsecured by
     * this event.
     */
    DPRINT("\r\nUser code entered!\r\n");
    user_code_event_validate_data.id = 1;
    user_code_event_validate_data.data = user_code;
    user_code_event_validate_data.length = sizeof(user_code);
    command_class = COMMAND_CLASS_USER_CODE;
    cc_event = CC_USER_CODE_EVENT_VALIDATE;
    cc_data = &user_code_event_validate_data;
  }
  else if (BTN_EVENT_HOLD(DOORHANDLE_BTN) == event)
  {
    app_event = EVENT_APP_DOORHANDLE_ACTIVATED;
  }
  else if ((BTN_EVENT_UP(DOORHANDLE_BTN) == event) ||
           (BTN_EVENT_LONG_PRESS(DOORHANDLE_BTN) == event))
  {
    app_event = EVENT_APP_DOORHANDLE_DEACTIVATED;
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

  if(command_class != COMMAND_CLASS_NO_OPERATION) {
    if (is_called_from_isr) {
      zaf_event_distributor_enqueue_cc_event_from_isr(command_class, cc_event, cc_data);
    } else {
      zaf_event_distributor_enqueue_cc_event(command_class, cc_event, cc_data);
    }    
  }
}

void app_hw_init(void)
{
  DPRINT("-----------------------------------\n");
  DPRINTF("%s: Hold/release: Activate/deactivate outside door handle #1\n", Board_GetButtonLabel(DOORHANDLE_BTN));
  DPRINTF("%s: Send battery report\n", Board_GetButtonLabel(BATTERY_REPORT_BTN));
  DPRINTF("%s: Toggle learn mode\n", Board_GetButtonLabel(APP_BUTTON_LEARN_RESET));
  DPRINT("      Hold 5 sec: Reset\n");
  DPRINTF("%s: Enter user code\n", Board_GetButtonLabel(ENTER_USER_CODE));
  DPRINTF("%s: Learn mode + identify\n", Board_GetLedLabel(APP_LED_INDICATOR));
  DPRINTF("%s: Latch closed(off)/open(on)\n", Board_GetLedLabel(DOOR_HANDLE_STATUS_LED));
  DPRINTF("%s: Bolt locked(on)/unlocked(off)\n", Board_GetLedLabel(BOLT_STATUS_LED));
  DPRINT("-----------------------------------\n\n");

  Board_SetButtonCallback(button_handler);
  Board_EnableButton(APP_BUTTON_LEARN_RESET);
  Board_EnableButton(DOORHANDLE_BTN);
  Board_EnableButton(BATTERY_REPORT_BTN);
  Board_EnableButton(ENTER_USER_CODE);

  AppTimerRegister(&door_lock_operation_set_timer, false, door_lock_operation_set_callback);
}

void cc_door_lock_handle_set(bool pressed)
{
  door_lock_hw.handle_pressed = pressed;
  Board_SetLed(DOOR_HANDLE_STATUS_LED, pressed ? LED_ON : LED_OFF);
  DPRINTF("Handle %s\r\n", pressed ? "pressed":"not pressed");
}

void cc_door_lock_latch_set(bool opened)
{
  door_lock_hw.latch_closed = !opened;
  DPRINTF("Latch %s\r\n", opened ? "open":"false");
}

void cc_door_lock_bolt_set(bool locked)
{
  door_lock_hw.bolt_unlocked = !locked;
  Board_SetLed(BOLT_STATUS_LED, locked ? LED_ON : LED_OFF);
  DPRINTF("Bolt %s\r\n", locked ? "locked":"unlocked");
}


bool door_lock_hw_bolt_is_unlocked(void)
{
  return door_lock_hw.bolt_unlocked;
}

bool door_lock_hw_latch_is_closed(void)
{
  return door_lock_hw.latch_closed;
}

bool door_lock_hw_handle_is_pressed(void)
{
  return door_lock_hw.handle_pressed;
}

uint8_t
CC_Battery_BatteryGet_handler(__attribute__((unused)) uint8_t endpoint)
{
  uint32_t VBattery;
  uint8_t accurateLevel;
  uint8_t roundedLevel;
  uint8_t reporting_decrements;

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

uint8_t cc_door_lock_mode_hw_change(door_lock_mode_t mode)
{
  DPRINTF("%s(): Switch to %s mode %#02x\r\n",
          __func__,
          (DOOR_MODE_SECURED == mode) ? "Secured":"Unsecured",
          mode);
  // Timed change happened - simulate timed hardware operation
  // This will also stop any active session
  door_lock_operation_set_timer.dummy[0] = (uint8_t)mode;
  TimerStart(&door_lock_operation_set_timer,
             CC_DOOR_LOCK_DEFAULT_OPERATION_SET_TIMEOUT);

  // Return estimated duration
  return CC_DOOR_LOCK_DEFAULT_OPERATION_SET_TIMEOUT/1000;
}

void
door_lock_operation_set_callback(__attribute__((unused)) SSwTimer *pTimer)
{
  door_lock_mode_t mode = (door_lock_mode_t)pTimer->dummy[0];
  cc_door_lock_bolt_set((mode == DOOR_MODE_SECURED));

  zaf_event_distributor_enqueue_cc_event(
      COMMAND_CLASS_DOOR_LOCK,
      CC_DOOR_LOCK_EVENT_HW_OPERATION_DONE,
      NULL);
}


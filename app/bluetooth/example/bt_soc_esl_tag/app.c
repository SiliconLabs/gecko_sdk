/***************************************************************************//**
 * @file
 * @brief Core application logic.
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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "em_common.h"
#include "sl_bt_api.h"
#include "esl_tag_log.h"
#include "esl_tag_core.h"
#include "sl_bluetooth.h"
#include "sl_sleeptimer.h"
#include "sl_power_manager.h"
#include "sl_board_control.h"
#include "sl_component_catalog.h"
#ifdef SL_CATALOG_SIMPLE_LED_PRESENT
#include "sl_simple_led.h"
#include "sl_simple_led_instances.h"
#endif // SL_CATALOG_SIMPLE_LED_PRESENT
#ifdef SL_CATALOG_SIMPLE_BUTTON_PRESENT
#include "sl_simple_button_instances.h"
#endif // SL_CATALOG_SIMPLE_BUTTON_PRESENT
#ifdef SL_CATALOG_DMD_MEMLCD_PRESENT
#include "sl_memlcd_display.h"
#include "esl_tag_wstk_lcd_driver.h"
#endif // SL_CATALOG_DMD_MEMLCD_PRESENT
#ifdef SL_CATALOG_ESL_TAG_PD_EPD_DRIVER_PRESENT
#include "esl_tag_pd_epd_driver.h"
#include "esl_tag_pd_epd_interface.h"
#include "esl_tag_pd_epd_driver_config.h"
#endif // SL_CATALOG_ESL_TAG_PD_EPD_DRIVER_PRESENT

#include "gatt_db.h"
#ifdef gattdb_esl_led_info
#include "esl_tag_led.h"
#endif // gattdb_esl_led_info
#ifdef gattdb_esl_image_info
#include "esl_tag_image.h"
#include "esl_tag_image_config.h"
#endif // gattdb_esl_image_info
#ifdef gattdb_esl_display_info
#include "esl_tag_display.h"
#endif // gattdb_esl_display_info
#ifdef gattdb_esl_sensor_info
#include "esl_tag_sensor.h"
#ifdef SL_CATALOG_SENSOR_RHT_PRESENT
#include "sl_sensor_rht.h"
#endif // SL_CATALOG_SENSOR_RHT_PRESENT
#endif // gattdb_esl_sensor_info

// Our led1 will support ESL brightness settings utilizing SW PWM implementation
#define SW_PWM_MAX_DUTY_STEPS   4 // four step brightness due ESL specification
#define SW_PWM_MAX_DUTY_VALUE   (SW_PWM_MAX_DUTY_STEPS - 1)

// ESL Sensor ID for our custom, vendor specific text message sensor element
#define MY_ESL_SENSOR_MESSAGE_ID  0xCAFE

// ESL Sensor ID for our custom, vendor specific button state sensor element
#define MY_ESL_SENSOR_BUTTON_ID   0xC0DE

// Our led0 will not switched on and off directly by ESL LED Control command,
// rather we'll mask it's feedback function, only
#ifdef SL_CATALOG_SIMPLE_LED_LED0_PRESENT
static bool led0_feedback_enabled = false;
#endif // SL_CATALOG_SIMPLE_LED_LED0_PRESENT

// type definition for simple SW PWM control
typedef struct {
  sl_sleeptimer_timer_handle_t *sw_pwm_handle;  // sleep timer handle
  sl_led_t const               *led;            // led handle
  uint32_t                     pace;            // sleep timer time base
  uint32_t                     offset;          // brightness perception offset
  bool                         state;           // actual led state
  uint8_t                      duty;            // requested duty cycle
} led_sw_pwm_t;

#ifdef gattdb_esl_led_info

// sl_sleeptimer instance for SW PWM
static sl_sleeptimer_timer_handle_t sw_pwm_timer;

// simple SW PWM control instance for led1 (simple led!)
static led_sw_pwm_t led1_sw_pwm = {
  &sw_pwm_timer,
  &sl_led_led1,
  0,
  0,
  false,
  0
};

// SW PWM sleep timer callback
static void sw_pwm_callback(sl_sleeptimer_timer_handle_t *timer, void* data)
{
  led_sw_pwm_t *instance = (led_sw_pwm_t *)data;
  uint32_t duration = instance->pace;
  uint16_t timer_flag = SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG;

  // toggle led at uneven pace - depending on the required duty cycle
  if (instance->state) {
    sl_status_t status;

    duration *= (SW_PWM_MAX_DUTY_VALUE - instance->duty);
    // reduce average power consumption - also compensates perceived brightness
    duration += instance->offset;
    // check the result of timer start request
    status = sl_sleeptimer_start_timer(timer,
                                       duration,
                                       sw_pwm_callback,
                                       instance,
                                       0,
                                       timer_flag);

    if (status == SL_STATUS_OK) {
      // if the timer couldn't be started (the worst case) then the brightness
      // control will be ignored, the LED will lit at its maximum brightness
      sl_led_turn_off(instance->led);
      instance->state = false;
    }
  } else {
    // do "quite the opposite" as of above
    instance->state = true;
    duration *= (instance->duty + 1); // don't forget that the duty can be 0
    duration -= instance->offset;
    (void)sl_sleeptimer_start_timer(timer,
                                    duration,
                                    sw_pwm_callback,
                                    instance,
                                    0,
                                    timer_flag);
    sl_led_turn_on(instance->led);
  }
}

static void sw_pwm_led_on(led_sw_pwm_t *instance, uint8_t duty)
{
  uint32_t duration = (sl_sleeptimer_ms_to_tick(16) / SW_PWM_MAX_DUTY_STEPS);

  // set SW PWM time base
  instance->pace    = duration;
  // set an empirical offset to compensate the perceived brightness
  // vs. the actual duty cycle request
  instance->offset  = duration / 2;

  // only allow 4 step duty cycle (a.k.a brightness) settings according to the
  // ESL LED specification
  if (duty < SW_PWM_MAX_DUTY_STEPS) {
    instance->duty = duty;
    duration *= ++duty;
  } else {
    instance->duty = SW_PWM_MAX_DUTY_VALUE;
  }

  // always turn on the led for the beginning of the cycle
  sl_led_turn_on(instance->led);
  instance->state = true;

  // start the timer only if the duty cycle is below 100%
  if (instance->duty < SW_PWM_MAX_DUTY_VALUE) {
    uint16_t flag = SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG;
    // it is safe to ignore the result
    (void)sl_sleeptimer_restart_timer(instance->sw_pwm_handle,
                                      duration - instance->offset,
                                      sw_pwm_callback,
                                      instance,
                                      0,
                                      flag);
  } else {
    // stop the timer as it may running already due previous ESL LED ON request
    sl_sleeptimer_stop_timer(instance->sw_pwm_handle);
  }
}

static void sw_pwm_led_off(led_sw_pwm_t *instance)
{
  sl_sleeptimer_stop_timer(instance->sw_pwm_handle);
  sl_led_turn_off(instance->led);
  instance->state = false;
}
#endif // gattdb_esl_led_info

// Power manager callback with some LED feedback
static void pm_callback(sl_power_manager_em_t from,
                        sl_power_manager_em_t to)
{
  (void)from;

  #ifdef SL_CATALOG_SIMPLE_LED_LED0_PRESENT
  uint8_t basic_state = esl_core_get_basic_state_bit(ESL_BASIC_STATE_SYNCHRONIZED_BIT);
  switch (to) {
    case SL_POWER_MANAGER_EM0:
      if (led0_feedback_enabled) {
        esl_state_t status = esl_core_get_status();
        // led0 instance of WSTK is used for optical feedback of activity - only
        // if the feature is manually enabled by issuing LED Control command
        // with LED index of 0 ('led on <esl_id>') from the ESL Access point
        if (ESL_TRUE == basic_state
            || esl_state_configuring == status
            || esl_state_updating == status) {
          sl_led_turn_on(&sl_led_led0);
        }
      }
      break;

    case SL_POWER_MANAGER_EM2:
      // see comments in @ref esl_led_on implementation what all these lines do
      if (ESL_TRUE == basic_state || !led0_feedback_enabled) {
        sl_led_turn_off(&sl_led_led0);
      } else if (led0_feedback_enabled) {
        if (esl_core_has_notifications()) {
          sl_led_toggle(&sl_led_led0);
        }
      }
      break;

    default:
      break;
  }
  #else // SL_CATALOG_SIMPLE_LED_LED0_PRESENT
  (void)to;
  #endif // SL_CATALOG_SIMPLE_LED_LED0_PRESENT
}

static sl_power_manager_em_transition_event_handle_t event_handle;
static sl_power_manager_em_transition_event_info_t event_info = {
  .event_mask = SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2
                | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM0,
  .on_event = pm_callback,
};

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  sl_power_manager_init();
  sl_power_manager_subscribe_em_transition_event(&event_handle, &event_info);

  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      break;
    case sl_bt_evt_connection_opened_id: {
    #ifdef SL_CATALOG_SIMPLE_LED_LED0_PRESENT
      esl_state_t status = esl_core_get_status();

      // implements led0 optical feedback case b), see @ref esl_led_on
      if ((esl_state_updating == status || esl_state_configuring == status)
          && led0_feedback_enabled) {
        sl_led_turn_on(&sl_led_led0);
      }
    #endif // SL_CATALOG_SIMPLE_LED_LED0_PRESENT
    } break;
    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

void esl_core_boot_event(void)
{
  sl_status_t sc;
  sl_button_state_t button_state;

  // suppress the compiler warning if none of the optional ESL characteristics are present
  (void)sc;
#if defined(gattdb_esl_image_info) && defined(SL_CATALOG_DMD_MEMLCD_PRESENT)
  // Please don't forget to adjust max. image pool size if resolution increases!
  sc = esl_image_add(SL_MEMLCD_DISPLAY_WIDTH,
                     SL_MEMLCD_DISPLAY_HEIGHT,
                     SL_MEMLCD_DISPLAY_BPP);
  sl_bt_esl_assert(sc == SL_STATUS_OK);
  sc = esl_image_add(SL_MEMLCD_DISPLAY_WIDTH,
                     SL_MEMLCD_DISPLAY_HEIGHT,
                     SL_MEMLCD_DISPLAY_BPP);
  sl_bt_esl_assert(sc == SL_STATUS_OK);
#endif // gattdb_esl_image_info

#ifdef SL_CATALOG_ESL_TAG_PD_EPD_DRIVER_PRESENT
  #if PD_EPD_DISPLAY_COLOR_TYPE == PD_EPD_SPECTRA
  const uint8_t bpp = PD_EPD_THREE_COLOR_BPP;
  #else
  const uint8_t bpp = PD_EPD_MONOCHROME_BPP;
  #endif
  sc = esl_image_add(PD_EPD_DISPLAY_WIDTH,
                     PD_EPD_DISPLAY_HEIGHT,
                     bpp);
  sl_bt_esl_assert(sc == SL_STATUS_OK);
#endif // SL_CATALOG_ESL_TAG_PD_EPD_DRIVER_PRESENT

#ifdef gattdb_esl_led_info
  // add first abstract led instance, it will have index 0
  sc = esl_led_add(ESL_LED_TYPE_SRGB, // for testing, it'll be reported as sRGB
                   ESL_LED_LEVEL_3,   // our LED has a nice amber color
                   ESL_LED_LEVEL_2,
                   ESL_LED_LEVEL_0);
  sl_bt_esl_assert(sc == SL_STATUS_OK);

  #ifdef SL_CATALOG_SIMPLE_LED_LED0_PRESENT
  // add second abstract led instance, it will have index 1
  sc = esl_led_add(ESL_LED_TYPE_MONOCHROME,
                   ESL_LED_LEVEL_3,
                   ESL_LED_LEVEL_2,
                   ESL_LED_LEVEL_0);
  sl_bt_esl_assert(sc == SL_STATUS_OK);
  #endif // SL_CATALOG_SIMPLE_LED_LED0_PRESENT
#endif // gattdb_esl_led_info

#ifdef gattdb_esl_sensor_info
  // add custom sensor, index is dependent on built-in sensor configuration,
  // however it must be also irrelevant from the end users' perspective
  sc = esl_sensor_add(ESL_SENSOR_SILABS_DEVICE,
                      MY_ESL_SENSOR_MESSAGE_ID);
  sl_bt_esl_assert(sc == SL_STATUS_OK);

  // add another custom sensor with mesh property ID type
  sc = esl_sensor_add(ESL_SENSOR_MESH_DEVICE,
                      PRESENT_AMBIENT_TEMPERATURE);
  sl_bt_esl_assert(sc == SL_STATUS_OK);

  // add even more custom sensor with vendor ID
  sc = esl_sensor_add(ESL_SENSOR_SILABS_DEVICE,
                      MY_ESL_SENSOR_BUTTON_ID);
  sl_bt_esl_assert(sc == SL_STATUS_OK);
#endif // gattdb_esl_sensor_info

  sl_button_enable(&sl_button_btn0);
  button_state = sl_simple_button_get_state(&sl_button_btn0);
  sl_button_disable(&sl_button_btn0);

  if (button_state != 0) {
    sl_bt_esl_log(ESL_LOG_COMPONENT_APP,
                  ESL_LOG_LEVEL_INFO,
                  "Force delete all bondings at startup!");
    (void)sl_bt_sm_delete_bondings();
  }
}

#ifdef gattdb_esl_led_info
sl_status_t esl_led_on(uint8_t led_index, esl_led_gamut_control_t gamut)
{
  sl_status_t result = SL_STATUS_OK;

  switch (led_index) {
    #ifdef SL_CATALOG_SIMPLE_LED_LED0_PRESENT
    case 1:
      // This ESL LED example features masking function only to a LED instance
      // (led0) which is already in use to provide optical feedback about
      // various ESL Tag states:
      //   a) regular blinking at even pace: periodic advertising while unsynced
      //   b) continuous lighting: connected (configuring or updating state)
      //   c) slow pace short flashing: synchronized state, receiving packets
      //   d) fast, irregular flashing: synchronized state in connectable mode
      led0_feedback_enabled = true;
      break;
    #endif // SL_CATALOG_SIMPLE_LED_LED0_PRESENT

    case 0:
      // this ESL LED instance features SW PWM control of LED1 on the WSTK
      sw_pwm_led_on(&led1_sw_pwm, esl_led_get_brightness(gamut));
      break;

    default:
      result = SL_STATUS_FAIL;
      break;
  }

  return result;
}

sl_status_t esl_led_off(uint8_t led_index)
{
  sl_status_t result = SL_STATUS_OK;

  switch (led_index) {
    #ifdef SL_CATALOG_SIMPLE_LED_LED0_PRESENT
    case 1:
      led0_feedback_enabled = false;
      sl_led_turn_off(&sl_led_led0);
      break;
    #endif // SL_CATALOG_SIMPLE_LED_LED0_PRESENT

    case 0:
      sw_pwm_led_off(&led1_sw_pwm);
      break;

    default:
      result = SL_STATUS_FAIL;
      break;
  }

  return result;
}
#endif // gattdb_esl_led_info

#ifdef gattdb_esl_sensor_info
sl_status_t esl_sensor_custom_read(uint8_t index,
                                   esl_sensor_size_t size,
                                   esl_sensor_sensor_code_t sensor_id,
                                   esl_sensor_company_id_t company)
{
  // default answer shall be SL_STATUS_NOT_SUPPORTED
  sl_status_t result = SL_STATUS_NOT_SUPPORTED;
  // create a local buffer, leave enough space for the index and an optional
  // terminating null character - if it was needed
  char        report_data[ESL_SENSOR_MAX_REPORT_LENGTH + 2] = { index, 0 };
  char* const read_target = &report_data[1];

  if (size == ESL_SENSOR_SIZE_MESH_DEVICE) {
    switch (sensor_id) {
#ifdef SL_CATALOG_SENSOR_RHT_PRESENT
      case PRESENT_AMBIENT_TEMPERATURE: {
        static bool rht_present = false;
        if (rht_present) {
          int32_t temp_data = 0;
          uint32_t rh_data = 0;

          result = sl_sensor_rht_get(&rh_data,
                                     &temp_data);
          temp_data -= 4750; // do offset compensation before integer division
          temp_data /= 500;  // convert from milli degrees Celsius to 0.5 deg. C
          memcpy(read_target, &temp_data, sizeof(temperature_8_t));
          result = esl_sensor_set_report(sizeof(temperature_8_t), report_data);
          // disable in the end to alternate between ready and not ready states
          sl_sensor_rht_deinit();
          rht_present = false;
          esl_core_set_basic_state_bit(ESL_BASIC_STATE_SERVICE_NEEDED_BIT,
                                       ESL_SET);

          if (result != SL_STATUS_OK) {
            esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
          }
        } else {
          // simulate a "slow sensor" which sometimes reports "not ready" state
          // by just disabling it after every readout, then re-enable (only) on
          // every second read requests and sending ESL_ERROR_RETRY response
          esl_core_set_last_error(ESL_ERROR_RETRY);
          result = SL_STATUS_NOT_READY;
          sl_sensor_rht_init();
          rht_present = true;
        }
      } break;
#endif // SL_CATALOG_SENSOR_RHT_PRESENT

      default:
        break;
    }
  } else if (company == ESL_SENSOR_SILABS_DEVICE) {
    switch (sensor_id) {
      // our simple sensor example returns a message with a counter value which
      // increments on every readout
      case MY_ESL_SENSOR_MESSAGE_ID: {
        // keep in mind that there's a limit on the sensor response length!
        static uint8_t counter = 0;
        uint8_t length = snprintf(read_target,
                                  // we take the terminating null into account
                                  ESL_SENSOR_MAX_REPORT_LENGTH + 1,
                                  "Get count: %u",
                                  ++counter);
        // the following invocation needs the whole data including index,
        // but the length of the sensor payload only, according to the
        // ESL Service specification!
        result = esl_sensor_set_report(length,
                                       report_data);
      } break;

      case MY_ESL_SENSOR_BUTTON_ID: {
        // a very simple sensor device, sensing the temporary button state, only
        sl_button_enable(&sl_button_btn0);
        *read_target = (uint8_t)sl_simple_button_get_state(&sl_button_btn0);
        // the GPIO pin of the button might be shared with our ePD driver,
        // disable after the readout
        sl_button_disable(&sl_button_btn0);
        result = esl_sensor_set_report(1, report_data);
      } break;

      default:
        break;
    }
  }

  return result;
}
#endif // gattdb_esl_sensor_info

void esl_core_unassociate_callback(void)
{
  uint8_t device_index;

  sl_bt_esl_log(ESL_LOG_COMPONENT_APP,
                ESL_LOG_LEVEL_INFO,
                "Execute unassociate callback");

  #ifdef gattdb_esl_led_info
  device_index = esl_led_get_count();

  // disable all available LED on board
  while (device_index--) {
    (void)esl_led_off(device_index);
  }
  #endif // gattdb_esl_led_info

  #ifdef gattdb_esl_image_info
  esl_image_reset_storage();
  #endif // gattdb_esl_image_info

  #if defined (gattdb_esl_display_info) && defined (ESL_TAG_WSTK_LCD_DRIVER_H)
  // reset WSTK display - if present
  (void)esl_wstk_lcd_init(0);
  #endif // defined (gattdb_esl_display_info) && defined (ESL_TAG_WSTK_LCD_DRIVER_H)
}

#if ESL_TAG_VENDOR_OPCODES_ENABLED
// Vendor response helper
#define SILABS_LOW_ENERGY_MODE_FLAG       0x01
// Vendor opcode with one byte extra input
#define SILABS_LOW_ENERGY_ENABLE_OPCODE   0x1F
// Vendor response of a single byte
#define SILABS_LOW_ENERGY_ENABLE_RESPONSE 0x0F

// Some arbitrary high limit for the Silabs low energy enable parameter
#define SILABS_LOW_ENERGY_SKIP_LIMIT      10

// Implement example for the vendor specified opcodes - this is Silabs specific
sl_status_t esl_core_process_vendor_opcode(tlv_t opcode,
                                           uint8_t input_length,
                                           void *data)
{
  sl_status_t result = SL_STATUS_NOT_SUPPORTED; // default answer shall be this

  switch (opcode) {
    // this vendor specified opcode allows to skip N cycle of PAwR sync train
    // the ESL tag to save power during e.g. store closed hours
    case SILABS_LOW_ENERGY_ENABLE_OPCODE: {
      uint8_t settings = 0;
      // check the input length to make sure to avoid memory corruption by copy
      sl_bt_esl_assert(input_length == esl_core_get_tlv_len(SILABS_LOW_ENERGY_ENABLE_OPCODE));
      // get the input value to the settings variable
      memcpy(&settings, data, input_length);

      if (settings <= SILABS_LOW_ENERGY_SKIP_LIMIT) {
        result = esl_core_update_sync_parameters(0, settings);

        if (result == SL_STATUS_OK) {
          tlv_t response_tlv = SILABS_LOW_ENERGY_ENABLE_RESPONSE;
          // set response length for the TLV properly
          esl_core_set_tlv_len(response_tlv, sizeof(settings));
          // call response builder: on our case, the response is the new skip value
          esl_core_build_response(response_tlv, &settings);
        } else {
          // set desired error code
          esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
          // do some cleanup action according to the error response if needed
          sl_bt_esl_log(ESL_LOG_COMPONENT_APP,
                        ESL_LOG_LEVEL_ERROR,
                        "Vendor opcode process failed with status: %lx!",
                        result);
          // change result to generic fail according to API reference
          result = SL_STATUS_FAIL;
        }
      } else {
        // we can set any valid ESL error code we want: this time, the parameter
        // is out of its bounds
        esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
        // change result to generic fail according to API reference
        result = SL_STATUS_FAIL;
      }
    } break;

    default:
      // leave the default response
      break;
  }

  return result;
}
#endif // ESL_TAG_VENDOR_OPCODES_ENABLED

void esl_core_init_hook(void)
{
  // ESL Tag CLI Test Harness may enable VCOM later if added to the project
  sl_board_disable_vcom();
}

void esl_core_shutdown_hook(void)
{
  // Disabling display saves more energy in EM4
  sl_board_disable_display();
  // ESL Tag CLI Test Harness may enabled VCOM at runtime, disable it before go
  sl_board_disable_vcom();
}

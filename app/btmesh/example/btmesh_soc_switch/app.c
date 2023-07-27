/***************************************************************************//**
 * @file
 * @brief Application code
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdbool.h>
#include <stdio.h>
#include "em_common.h"
#include "sl_status.h"

#include "sl_btmesh.h"
#include "sl_bluetooth.h"
#include "app.h"

#include "gatt_db.h"

#include "app_assert.h"

/* Buttons and LEDs headers */
#include "app_button_press.h"
#include "sl_simple_button.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led.h"
#include "sl_simple_led_instances.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
#include "sl_btmesh_wstk_lcd.h"
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

#include "app_btmesh_util.h"

/* Switch app headers */
#include "app_timer.h"

#ifdef SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT
#include "sl_btmesh_factory_reset.h"
#endif // SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT

#include "sl_btmesh_lighting_client.h"
#include "sl_btmesh_ctl_client.h"

#ifdef SL_CATALOG_BTMESH_SCENE_CLIENT_PRESENT
#include "sl_btmesh_scene_client.h"
#endif // SL_CATALOG_BTMESH_SCENE_CLIENT_PRESENT

#ifdef SL_CATALOG_BTMESH_PROVISIONING_DECORATOR_PRESENT
#include "sl_btmesh_provisioning_decorator.h"
#endif // SL_CATALOG_BTMESH_PROVISIONING_DECORATOR_PRESENT

/// Suppress compiler warning of unused static function
#define SL_UNUSED  __attribute__((unused))

/// High Priority
#define HIGH_PRIORITY                  0
/// No Timer Options
#define NO_FLAGS                       0
/// Callback has no parameters
#define NO_CALLBACK_DATA               (void *)NULL
/// Timeout for Blinking LED during provisioning
#define APP_LED_BLINKING_TIMEOUT       250
/// Hundred percent
#define MAX_PERCENT 100
/// Increase step of physical values (lightness, color temperature)
#define INCREASE                       10
/// Decrease step of physical values (lightness, color temperature)
#define DECREASE                       (-10)
/// Length of the display name buffer
#define NAME_BUF_LEN                   20
/// Length of boot error message buffer
#define BOOT_ERR_MSG_BUF_LEN           30
/// Used button index
#define BUTTON_PRESS_BUTTON_0          0

#ifndef SL_CATALOG_APP_LOG_PRESENT
#define app_log(...)
#define app_log_status_error_f(...)
#endif // SL_CATALOG_APP_LOG_PRESENT

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
#define lcd_print(...) sl_btmesh_LCD_write(__VA_ARGS__)
#else
#define lcd_print(...)
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

/// periodic timer handle
static app_timer_t app_led_blinking_timer;

/// periodic timer callback
static void app_led_blinking_timer_cb(app_timer_t *handle, void *data);
// Handles button press and does a factory reset
static bool handle_reset_conditions(void);
// Set device name in the GATT database
static void set_device_name(uuid_128 *uuid);
// Clamp the sum of `a` and `b` to the given max value
SL_UNUSED static uint8_t clamp_add(int8_t a, int8_t b, uint8_t max);
// Wrap the sum of `a` and `b` around the given max value
SL_UNUSED static uint8_t wrap_add(int8_t a, int8_t b, uint8_t max);

/*******************************************************************************
 * Global variables
 ******************************************************************************/
/// number of active Bluetooth connections
static uint8_t num_connections = 0;

static bool init_done = false;

static uint8_t lightness_percent = 0;
static uint8_t temperature_percent = 0;

/***************************************************************************//**
 * Change buttons to LEDs in case of shared pin
 *
 ******************************************************************************/
void change_buttons_to_leds(void)
{
  app_button_press_disable();
  // Disable button and enable led
  sl_simple_button_disable(&sl_button_btn0);
  sl_simple_led_init(sl_led_led0.context);
  // Disable button and enable led
#if SL_SIMPLE_BUTTON_COUNT >= 2
  sl_simple_button_disable(&sl_button_btn1);
#endif
#if SL_SIMPLE_LED_COUNT >= 2
  sl_simple_led_init(sl_led_led1.context);
#endif
}

/***************************************************************************//**
 * Change LEDs to buttons in case of shared pin
 *
 ******************************************************************************/
void change_leds_to_buttons(void)
{
  // Enable buttons
  sl_simple_button_enable(&sl_button_btn0);
#if SL_SIMPLE_BUTTON_COUNT >= 2
  sl_simple_button_enable(&sl_button_btn1);
#endif
  // Wait
  sl_sleeptimer_delay_millisecond(1);
  // Enable button presses
  app_button_press_enable();
}

/***************************************************************************//**
 * Application Init.
 ******************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
  app_log("BT mesh Switch initialized" APP_LOG_NL);
  // Ensure right init order in case of shared pin for enabling buttons
  change_buttons_to_leds();
  // Change LEDs to buttons in case of shared pin
  change_leds_to_buttons();
  handle_reset_conditions();
}

/***************************************************************************//**
 * Application Process Action.
 ******************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

/***************************************************************************//**
 * Set device name in the GATT database. A unique name is generated using
 * the two last bytes from the UUID of this device. Name is also
 * displayed on the LCD.
 *
 * @param[in] uuid  Pointer to device UUID.
 ******************************************************************************/
static void set_device_name(uuid_128 *uuid)
{
  char name[NAME_BUF_LEN];
  sl_status_t result;

  // Create unique device name using the last two bytes of the device UUID
  snprintf(name, NAME_BUF_LEN, "switch node %02x%02x",
           uuid->data[14], uuid->data[15]);

  app_log("Device name: '%s'" APP_LOG_NL, name);

  result = sl_bt_gatt_server_write_attribute_value(gattdb_device_name,
                                                   0,
                                                   strlen(name),
                                                   (uint8_t *)name);
  app_log_status_error_f(result,
                         "sl_bt_gatt_server_write_attribute_value() failed" APP_LOG_NL);

  // Show device name on the LCD
  lcd_print(name, SL_BTMESH_WSTK_LCD_ROW_NAME_CFG_VAL);

  (void) result;
}

/***************************************************************************//**
 * Clamp the sum of two signed 8-bit integers to a given maximum value
 *
 * @param a The first signed 8-bit integer
 * @param b The second signed 8-bit integer
 * @param max The maximum value that the sum can take
 *
 * @return The sum of `a` and `b`, clamped to `max`
 ******************************************************************************/
static uint8_t clamp_add(int8_t a, int8_t b, uint8_t max)
{
  int16_t sum = a + b;
  if (sum > max) {
    return max;
  } else if (sum < 0) {
    return 0;
  } else {
    return sum;
  }
}

/***************************************************************************//**
 * Wrap the sum of two signed 8-bit integers to fit within a given maximum value
 *
 * @param a The first signed 8-bit integer
 * @param b The second signed 8-bit integer
 * @param max The maximum value that the sum can take
 *
 * @return The sum of `a` and `b`, wrapped around `max`
 ******************************************************************************/
static uint8_t wrap_add(int8_t a, int8_t b, uint8_t max)
{
  int16_t sum = a + b;
  while (sum > max) {
    sum -= max;
  }
  while (sum < 0 ) {
    sum += max;
  }
  return sum;
}

/***************************************************************************//**
 * Handles button press and does a factory reset
 *
 * @return true if there is no button press
 ******************************************************************************/
static bool handle_reset_conditions(void)
{
#ifdef SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT
  // If PB0 is held down then do full factory reset
  if (sl_simple_button_get_state(&sl_button_btn0)
      == SL_SIMPLE_BUTTON_PRESSED) {
    // Disable button presses
    app_button_press_disable();
    // Full factory reset
    sl_btmesh_initiate_full_reset();
    return false;
  }

#if SL_SIMPLE_BUTTON_COUNT >= 2
  // If PB1 is held down then do node factory reset
  if (sl_simple_button_get_state(&sl_button_btn1)
      == SL_SIMPLE_BUTTON_PRESSED) {
    // Disable button presses
    app_button_press_disable();
    // Node factory reset
    sl_btmesh_initiate_node_reset();
    return false;
  }
#endif
#endif // SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT
  return true;
}

/***************************************************************************//**
 * Handling of le stack events.
 * @param[in] evt     Pointer to incoming event.
 ******************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_connection_opened_id:
      num_connections++;
      lcd_print("connected", SL_BTMESH_WSTK_LCD_ROW_CONNECTION_CFG_VAL);
      app_log("Connected" APP_LOG_NL);
      break;

    case sl_bt_evt_connection_closed_id:
      if (num_connections > 0) {
        if (--num_connections == 0) {
          lcd_print("", SL_BTMESH_WSTK_LCD_ROW_CONNECTION_CFG_VAL);
          app_log("Disconnected" APP_LOG_NL);
        }
      }
      break;

    default:
      break;
  }
}

/***************************************************************************//**
 * Bluetooth Mesh stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Pointer to incoming event from the Bluetooth Mesh stack.
 ******************************************************************************/
void sl_btmesh_on_event(sl_btmesh_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    default:
      break;
  }
}

/*******************************************************************************
 * Callbacks
 ******************************************************************************/

/***************************************************************************//**
 * Handling of provisionee init result
 ******************************************************************************/
void sl_btmesh_provisionee_on_init(sl_status_t result)
{
  if (SL_STATUS_OK != result) {
    char buf[BOOT_ERR_MSG_BUF_LEN];
    snprintf(buf, sizeof(buf), "init failed (0x%lx)", result);
    lcd_print(buf, SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  } else {
    uuid_128 uuid;
    sl_status_t sc = sl_btmesh_node_get_uuid(&uuid);
    app_assert_status_f(sc, "Failed to get UUID");
    set_device_name(&uuid);
  }
}

/***************************************************************************//**
 * Button press Callbacks
 ******************************************************************************/
void app_button_press_cb(uint8_t button, uint8_t duration)
{
#if SL_SIMPLE_BUTTON_COUNT == 1
  if (button == BUTTON_PRESS_BUTTON_0) {
    switch (duration) {
      // Handling of button press less than 0.25s
      case APP_BUTTON_PRESS_DURATION_SHORT: {
        lightness_percent = wrap_add(lightness_percent, DECREASE, MAX_PERCENT);
        sl_btmesh_set_lightness(lightness_percent);
      } break;
      // Handling of button press greater than 0.25s and less than 1s
      case APP_BUTTON_PRESS_DURATION_MEDIUM: {
        temperature_percent = wrap_add(temperature_percent, DECREASE, MAX_PERCENT);
        sl_btmesh_set_temperature(temperature_percent);
      } break;
      // Handling of button press greater than 1s and less than 5s
      case APP_BUTTON_PRESS_DURATION_LONG: {
        sl_btmesh_change_switch_position(SL_BTMESH_LIGHTING_CLIENT_TOGGLE);
      } break;
#ifdef SL_CATALOG_BTMESH_SCENE_CLIENT_PRESENT
      // Handling of button press greater than 5s
      case APP_BUTTON_PRESS_DURATION_VERYLONG: {
        sl_btmesh_select_scene(1);
      } break;
#endif // SL_CATALOG_BTMESH_SCENE_CLIENT_PRESENT
      default:
        break;
    }
  }
#endif
#if SL_SIMPLE_BUTTON_COUNT >= 2
  // Selecting action by duration
  switch (duration) {
    // Handling of button press less than 0.25s
    case APP_BUTTON_PRESS_DURATION_SHORT: {
      lightness_percent = button == BUTTON_PRESS_BUTTON_0
                          ? clamp_add(lightness_percent, DECREASE, MAX_PERCENT)
                          : clamp_add(lightness_percent, INCREASE, MAX_PERCENT);
      sl_btmesh_set_lightness(lightness_percent);
    } break;
    // Handling of button press greater than 0.25s and less than 1s
    case APP_BUTTON_PRESS_DURATION_MEDIUM: {
      temperature_percent = button == BUTTON_PRESS_BUTTON_0
                            ? clamp_add(temperature_percent, DECREASE, MAX_PERCENT)
                            : clamp_add(temperature_percent, INCREASE, MAX_PERCENT);
      sl_btmesh_set_temperature(temperature_percent);
    } break;
    // Handling of button press greater than 1s and less than 5s
    case APP_BUTTON_PRESS_DURATION_LONG: {
      if (button == BUTTON_PRESS_BUTTON_0) {
        sl_btmesh_change_switch_position(SL_BTMESH_LIGHTING_CLIENT_OFF);
      } else {
        sl_btmesh_change_switch_position(SL_BTMESH_LIGHTING_CLIENT_ON);
      }
    } break;
#ifdef SL_CATALOG_BTMESH_SCENE_CLIENT_PRESENT
    // Handling of button press greater than 5s
    case APP_BUTTON_PRESS_DURATION_VERYLONG: {
      if (button == BUTTON_PRESS_BUTTON_0) {
        sl_btmesh_select_scene(1);
      } else {
        sl_btmesh_select_scene(2);
      }
    } break;
#endif // SL_CATALOG_BTMESH_SCENE_CLIENT_PRESENT
    default:
      break;
  }
#endif
}

/*******************************************************************************
 * Provisioning Decorator Callbacks
 ******************************************************************************/
// Called when the Provisioning starts
void sl_btmesh_on_node_provisioning_started(uint16_t result)
{
  // Change buttons to LEDs in case of shared pin
  change_buttons_to_leds();

  sl_status_t sc = app_timer_start(&app_led_blinking_timer,
                                   APP_LED_BLINKING_TIMEOUT,
                                   app_led_blinking_timer_cb,
                                   NO_CALLBACK_DATA,
                                   true);

  app_assert_status_f(sc, "Failed to start periodic timer");

#if defined(SL_CATALOG_BTMESH_WSTK_LCD_PRESENT) || defined(SL_CATALOG_APP_LOG_PRESENT)
  app_show_btmesh_node_provisioning_started(result);
#else
  (void)result;
#endif // defined(SL_CATALOG_BTMESH_WSTK_LCD_PRESENT) || defined(SL_CATALOG_APP_LOG_PRESENT)
}

// Called when the Provisioning finishes successfully
void sl_btmesh_on_node_provisioned(uint16_t address,
                                   uint32_t iv_index)
{
  sl_status_t sc = app_timer_stop(&app_led_blinking_timer);
  app_assert_status_f(sc, "Failed to stop periodic timer");
  // Turn off LED
  init_done = true;
  sl_simple_led_turn_off(sl_led_led0.context);
#if SL_SIMPLE_LED_COUNT >= 2
  sl_simple_led_turn_off(sl_led_led1.context);
#endif
  change_leds_to_buttons();

#if defined(SL_CATALOG_BTMESH_WSTK_LCD_PRESENT) || defined(SL_CATALOG_APP_LOG_PRESENT)
  app_show_btmesh_node_provisioned(address, iv_index);
#else
  (void)address;
  (void)iv_index;
#endif // defined(SL_CATALOG_BTMESH_WSTK_LCD_PRESENT) || defined(SL_CATALOG_APP_LOG_PRESENT)
}

/***************************************************************************//**
 * Timer Callbacks
 ******************************************************************************/
static void app_led_blinking_timer_cb(app_timer_t *handle, void *data)
{
  (void)data;
  (void)handle;
  if (!init_done) {
    // Toggle LEDs
    sl_simple_led_toggle(sl_led_led0.context);
#if SL_SIMPLE_LED_COUNT >= 2
    sl_simple_led_toggle(sl_led_led1.context);
#endif
  }
}

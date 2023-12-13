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
#include "sl_sleeptimer.h"

#include "sl_btmesh.h"
#include "sl_bluetooth.h"
#include "app.h"
#include "app_assert.h"
#include "app_log.h"

#include "gatt_db.h"

#include "sl_btmesh_sensor_client.h"

/* Buttons and LEDs headers */
#include "app_button_press.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "app_timer.h"

#ifdef SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT
#include "sl_btmesh_factory_reset.h"
#endif // SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT

#ifdef SL_CATALOG_BTMESH_PROVISIONING_DECORATOR_PRESENT
#include "sl_btmesh_provisioning_decorator.h"
#endif // SL_CATALOG_BTMESH_PROVISIONING_DECORATOR_PRESENT

#include "app_btmesh_util.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
#include "sl_btmesh_wstk_lcd.h"
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

/// High Priority
#define HIGH_PRIORITY                  0
/// No Timer Options
#define NO_FLAGS                       0
/// Callback has no parameters
#define NO_CALLBACK_DATA               NULL
/// timeout for registering new devices after startup
#define DEVICE_REGISTER_SHORT_TIMEOUT  100
/// timeout for registering new devices after startup
#define DEVICE_REGISTER_LONG_TIMEOUT   20000
/// timeout for periodic sensor data update
#define SENSOR_DATA_TIMEOUT            2000
/// Timeout for Blinking LED during provisioning
#define APP_LED_BLINKING_TIMEOUT       250
/// Length of the display name buffer
#define NAME_BUF_LEN                   20
/// Length of boot error message buffer
#define BOOT_ERR_MSG_BUF_LEN           30
/// Used button indexes
#define BUTTON_PRESS_BUTTON_0          0
#define BUTTON_PRESS_BUTTON_1          1

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
#define lcd_print(...) sl_btmesh_LCD_write(__VA_ARGS__)
#else
#define lcd_print(...)
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

// -------------------------------
// Periodic timer handles
static app_timer_t app_sensor_data_timer;
static app_timer_t app_update_registered_devices_timer;
static app_timer_t app_led_blinking_timer;

// -------------------------------
// Periodic timer callbacks
static void app_sensor_data_timer_cb(app_timer_t *handle,
                                     void *data);
static void app_update_registered_devices_timer_cb(app_timer_t *handle,
                                                   void *data);
static void app_led_blinking_timer_cb(app_timer_t *handle,
                                      void *data);

/// Number of active Bluetooth connections
static uint8_t num_connections = 0;

static bool init_done = false;

/// Currently displayed property ID
static mesh_device_properties_t current_property = PRESENT_AMBIENT_TEMPERATURE;

/// Property IDs supported by application
static void sensor_client_change_current_property(void);

// Handles button press and does a factory reset
static bool handle_reset_conditions(void);

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
#endif //SINGLE_LED
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

/*******************************************************************************
 * Application Init.
 ******************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
  app_log("Bt Mesh Sensor Client initialized" APP_LOG_NL);
  // Ensure right init order in case of shared pin for enabling buttons
  change_buttons_to_leds();
  // Change LEDs to buttons in case of shared pin
  change_leds_to_buttons();
  handle_reset_conditions();
}

/*******************************************************************************
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

/*******************************************************************************
 * Get the currently set property ID
 *
 * @return Current property ID
 ******************************************************************************/
mesh_device_properties_t app_get_current_property(void)
{
  return current_property;
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
  snprintf(name,
           NAME_BUF_LEN,
           "sensor client %02x%02x",
           uuid->data[14],
           uuid->data[15]);

  app_log("Device name: '%s'" APP_LOG_NL, name);

  result = sl_bt_gatt_server_write_attribute_value(gattdb_device_name,
                                                   0,
                                                   strlen(name),
                                                   (uint8_t *)name);
  app_log_status_error_f(result,
                         "sl_bt_gatt_server_write_attribute_value() failed" APP_LOG_NL);

  // Show device name on the LCD
  lcd_print(name, SL_BTMESH_WSTK_LCD_ROW_NAME_CFG_VAL);
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
#endif // SL_CATALOG_BTN1_PRESENT
#endif // SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT
  return true;
}

/***************************************************************************//**
 * Update registered devices after the specified timeout
 *
 * @param[in] timeout_ms Timer timeout, in milliseconds.
 ******************************************************************************/
static void schedule_registered_device_update(uint32_t timeout_ms)
{
  sl_status_t sc =
    app_timer_start(&app_update_registered_devices_timer,
                    timeout_ms,
                    app_update_registered_devices_timer_cb,
                    NO_CALLBACK_DATA,
                    false);
  app_assert_status_f(sc, "Failed to start timer");
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
    case sl_btmesh_evt_node_initialized_id:
      if (evt->data.evt_node_initialized.provisioned) {
        schedule_registered_device_update(DEVICE_REGISTER_SHORT_TIMEOUT);
      }
      break;
    case sl_btmesh_evt_node_provisioned_id:
      schedule_registered_device_update(DEVICE_REGISTER_LONG_TIMEOUT);
      break;
    default:
      break;
  }
}

void update_registered_devices(void)
{
  sl_status_t sc;

  sl_btmesh_sensor_client_update_registered_devices(current_property);

  sc = app_timer_start(&app_sensor_data_timer,
                       SENSOR_DATA_TIMEOUT,
                       app_sensor_data_timer_cb,
                       NO_CALLBACK_DATA,
                       true);

  app_assert_status_f(sc, "Failed to start periodic timer");
}

/***************************************************************************//**
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

void app_button_press_cb(uint8_t button, uint8_t duration)
{
  (void)duration;
  if (duration == APP_BUTTON_PRESS_NONE) {
    return;
  }
  // button pressed
  if (button == BUTTON_PRESS_BUTTON_0) {
    if (duration < APP_BUTTON_PRESS_DURATION_LONG) {
      app_log("PB0 pressed" APP_LOG_NL);
      sensor_client_change_current_property();
    } else {
      app_log("PB0 long pressed" APP_LOG_NL);
      update_registered_devices();
    }
  } else if (button == BUTTON_PRESS_BUTTON_1) {
    app_log("PB1 pressed" APP_LOG_NL);
    update_registered_devices();
  }
}

/***************************************************************************//**
 * Timer Callbacks
 ******************************************************************************/
static void app_sensor_data_timer_cb(app_timer_t *handle,
                                     void *data)
{
  (void)data;
  (void)handle;
  sl_btmesh_sensor_client_get_sensor_data(current_property);
}

static void app_update_registered_devices_timer_cb(app_timer_t *handle,
                                                   void *data)
{
  (void)data;
  (void)handle;
  sl_status_t sc;

  sl_btmesh_sensor_client_update_registered_devices(current_property);

  sc = app_timer_start(&app_sensor_data_timer,
                       SENSOR_DATA_TIMEOUT,
                       app_sensor_data_timer_cb,
                       NO_CALLBACK_DATA,
                       true);

  app_assert_status_f(sc, "Failed to start periodic timer");
}

static void app_led_blinking_timer_cb(app_timer_t *handle,
                                      void *data)
{
  (void)data;
  (void)handle;
  if (!init_done) {
    // Toggle LEDs
    sl_led_led0.toggle(sl_led_led0.context);
#if SL_SIMPLE_LED_COUNT >= 2
    sl_led_led1.toggle(sl_led_led1.context);
#endif
  }
}

/***************************************************************************//**
 * It changes currently displayed property ID.
 ******************************************************************************/
static void sensor_client_change_current_property(void)
{
  switch (current_property) {
    case PRESENT_AMBIENT_TEMPERATURE:
      current_property = PEOPLE_COUNT;
      break;
    case PEOPLE_COUNT:
      current_property = PRESENT_AMBIENT_LIGHT_LEVEL;
      break;
    case PRESENT_AMBIENT_LIGHT_LEVEL:
      current_property = PRESENT_AMBIENT_TEMPERATURE;
      break;
    default:
      app_log("Unsupported property ID change" APP_LOG_NL);
      break;
  }
}

/***************************************************************************//**
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

  app_show_btmesh_node_provisioning_started(result);
}

// Called when the Provisioning fails
void sl_btmesh_on_node_provisioning_failed(uint16_t result)
{
  app_show_btmesh_node_provisioning_failed(result);
  // Small delay before reboot
  sl_sleeptimer_delay_millisecond(2000);
  sl_bt_system_reset(0);
}

// Called when the Provisioning finishes successfully
void sl_btmesh_on_node_provisioned(uint16_t address,
                                   uint32_t iv_index)
{
  sl_status_t sc = app_timer_stop(&app_led_blinking_timer);
  app_assert_status_f(sc, "Failed to stop periodic timer");
  // Turn off LED
  init_done = true;
  sl_led_led0.turn_off(sl_led_led0.context);
#if SL_SIMPLE_LED_COUNT >= 2
  sl_led_led1.turn_off(sl_led_led1.context);
#endif
  // Change LEDs to buttons in case of shared pin
  change_leds_to_buttons();

  app_show_btmesh_node_provisioned(address, iv_index);
}

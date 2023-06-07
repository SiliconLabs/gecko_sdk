/***************************************************************************//**
 * @file
 * @brief Silicon Labs SoC BT Mesh DFU Distributor Example Project
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

#include "sl_bluetooth.h"
#include "sl_bt_api.h"
#include "app.h"
#include "gatt_db.h"
#include "app_assert.h"
#include "app_log.h"
#include "app_btmesh_util.h"

#include "app_button_press.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "app_timer.h"
#include "sl_btmesh_blob_storage.h"

#ifdef SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT
#include "sl_btmesh_factory_reset.h"
#endif // SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT

#ifdef SL_CATALOG_BTMESH_PROVISIONING_DECORATOR_PRESENT
#include "sl_btmesh_provisioning_decorator.h"
#endif // SL_CATALOG_BTMESH_PROVISIONING_DECORATOR_PRESENT

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
#include "sl_btmesh_wstk_lcd.h"
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
/// Callback has not parameters
#define NO_CALLBACK_DATA               (void *)NULL
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
#define lcd_next_page() sl_btmesh_LCD_next_page()
#define lcd_prev_page() sl_btmesh_LCD_prev_page()
#else
#define lcd_print(...)
#define lcd_next_page()
#define lcd_prev_page()
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

/// periodic timer handle
static app_timer_t app_led_blinking_timer;

/// periodic timer callback
static void app_led_blinking_timer_cb(app_timer_t *handle, void *data);
// Handles button press and does a factory reset
static bool handle_reset_conditions(void);
// Set device name in the GATT database
static void set_device_name(uuid_128 *uuid);

/*******************************************************************************
 * Global variables
 ******************************************************************************/
/// number of active Bluetooth connections
static uint8_t num_connections = 0;

static bool init_done = false;

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
  app_log("Bt Mesh Distributor initialized" APP_LOG_NL);
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
           "distributor %02x%02x",
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
 * Configuration of segmentation and reassembly
 ******************************************************************************/
static void set_sar_config(void)
{
  sl_status_t sc;
  // The SAR transmitter configuration getter and setter functions don't require
  // initialization call and it is not mandatory to have SAR Configuration Server
  // in the Device Composition Data.
  // These are necessary only to handle SAR Config messages.
  uint8_t segment_interval_step;
  uint8_t unicast_retrans_count;
  uint8_t unicast_retrans_wo_progress_count;
  uint16_t unicast_retrans_interval_step;
  uint16_t unicast_retrans_interval_increment;
  uint8_t multicast_retrans_count;
  uint16_t multicast_retrans_interval_step;
  // Get the current SAR Configuration Server Transmitter state to modify
  // the critical parameter only and keep the default values of others.
  sc = sl_btmesh_sar_config_server_get_sar_transmitter(&segment_interval_step,
                                                       &unicast_retrans_count,
                                                       &unicast_retrans_wo_progress_count,
                                                       &unicast_retrans_interval_step,
                                                       &unicast_retrans_interval_increment,
                                                       &multicast_retrans_count,
                                                       &multicast_retrans_interval_step);
  app_assert_status_f(sc, "Failed to get SAR Tx Config");
  // The BLOB Transfer procedure has a high-level retransmission logic which
  // detects missing chunks and retransmits the missing ones.
  // The retransmissions are disabled in Lower Transport layer because it slows
  // down the BLOB Transfer significantly.
  multicast_retrans_count = 0;
  sc = sl_btmesh_sar_config_server_set_sar_transmitter(segment_interval_step,
                                                       unicast_retrans_count,
                                                       unicast_retrans_wo_progress_count,
                                                       unicast_retrans_interval_step,
                                                       unicast_retrans_interval_increment,
                                                       multicast_retrans_count,
                                                       multicast_retrans_interval_step);
  app_assert_status_f(sc, "Failed to set SAR Tx Config");
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
  if (sl_simple_button_get_state(&sl_button_btn0) == SL_SIMPLE_BUTTON_PRESSED) {
    // Disable button presses
    app_button_press_disable();
    // Full factory reset
    sl_btmesh_initiate_full_reset();
    return false;
  }

#if SL_SIMPLE_BUTTON_COUNT >= 2
  // If PB1 is held down then do node factory reset
  if (sl_simple_button_get_state(&sl_button_btn1) == SL_SIMPLE_BUTTON_PRESSED) {
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
void app_button_press_cb(uint8_t button, uint8_t duration)
{
  (void) duration;
  switch (button) {
    case BUTTON_PRESS_BUTTON_0:
      lcd_next_page();
      break;
    case BUTTON_PRESS_BUTTON_1:
      lcd_prev_page();
      break;
  }
}

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
    set_sar_config();
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

/***************************************************************************//**
 * Timer Callbacks
 ******************************************************************************/
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

// -----------------------------------------------------------------------------
// Factory Reset Callbacks

/*******************************************************************************
 * Called during the factory reset of the device.
 ******************************************************************************/
void sl_btmesh_factory_reset_on_full_reset(void)
{
  app_show_btmesh_factory_reset_full_reset();

  // Delete all BLOBs from BLOB storage
  // Note: Delete all operation may take ~5-15s based on flash type and size
  app_log("Erasing BLOB storage objects (duration: ~5-15s)" APP_LOG_NL);
  sl_status_t sc = sl_btmesh_blob_storage_delete_all();
  app_assert_status_f(sc, "BLOB storage erase failed");

  sc = app_btmesh_nvm_erase_all();
  app_assert_status_f(sc, "NVM erase failed");
}

/*******************************************************************************
 * Called during the factory reset of the node.
 ******************************************************************************/
void sl_btmesh_factory_reset_on_node_reset(void)
{
  app_show_btmesh_factory_reset_node_reset();
}

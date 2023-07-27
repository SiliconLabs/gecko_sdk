/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "em_common.h"
#include "app_assert.h"
#include "app_log.h"
#include "sl_bluetooth.h"
#include "app.h"
#include "sl_component_catalog.h"
#include "throughput_ui.h"
#include "throughput_types.h"
#include "throughput_peripheral.h"
#include "throughput_central.h"
#include "sl_status.h"
#include "sl_simple_button.h"
#include "sl_simple_button_instances.h"
#include "app_timer.h"

#ifdef SL_CATALOG_SIMPLE_LED_PRESENT
#include "sl_simple_led_instances.h"
#endif

#if SL_SIMPLE_BUTTON_COUNT >= 2
#define PB0               SL_SIMPLE_BUTTON_INSTANCE(0)
#define PB1               SL_SIMPLE_BUTTON_INSTANCE(1)
#elif SL_SIMPLE_BUTTON_COUNT == 1
#define PB0               SL_SIMPLE_BUTTON_INSTANCE(0)
#define PB1               PB0
#define LED0              SL_SIMPLE_LED_INSTANCE(0)
#define BUTTON_TIMEOUT    1000
#endif // SL_SIMPLE_BUTTON_COUNT

#define PB0_VALUE    ((uint8_t)(1 << 0))  ///< Button 0 pressed.
#define PB1_VALUE    ((uint8_t)(1 << 1))  ///< Button 1 pressed.

/// Enabled, if switching roles (central - peripheral)
bool switching_roles = false;

// Desired role for throughput
throughput_role_t global_desired_role;

/// Current role for throughput
throughput_role_t role;

/// Current button state for testing
uint8_t button_previous = 0;

/// Mask first button release
bool mask_release = false;

/// Current button state for testing
throughput_notification_t type  = sl_bt_gatt_notification;

/// Current state of buttons
uint8_t button_current;

/// Change of buttons
uint8_t button_change = 0;

#if SL_SIMPLE_BUTTON_COUNT == 1

/// Timer for button press handling
app_timer_t button_timer;

/// Timer rised for short press
bool button_timer_rised = false;

#endif //SL_SIMPLE_BUTTON_COUNT

/*******************************************************************************
 *******************  FORWARD DECLARATION OF FUNCTIONS   ***********************
 ******************************************************************************/
static void app_handle_button_press(void);
static void enable_new_throughput_role(throughput_role_t new_role);
static sl_status_t set_role_request_and_disable_current_role(throughput_role_t role_request);
static void set_role(throughput_role_t new_role);
static void handle_cli_switch_command(throughput_role_t role_request);

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/
static void enable_new_throughput_role(throughput_role_t new_role)
{
  switch (new_role) {
    case THROUGHPUT_ROLE_CENTRAL:
      set_role(new_role);
      throughput_central_enable();
      break;

    case THROUGHPUT_ROLE_PERIPHERAL:
      set_role(new_role);
      throughput_peripheral_enable();
      break;
  }
}

static sl_status_t set_role_request_and_disable_current_role(throughput_role_t role_request)
{
  sl_status_t sc = 0;

  // If state is not disconnected, we have to make sure, it will be disconnected
  switch (role) {
    case THROUGHPUT_ROLE_CENTRAL:
      sc = throughput_central_disable();
      break;

    case THROUGHPUT_ROLE_PERIPHERAL:
      sc = throughput_peripheral_disable();
      break;

    default:
      // Set the current role and desired role to the same role
      set_role(role);
      sc = SL_STATUS_NOT_FOUND;
      break;
  }

  if (sc == SL_STATUS_OK) {
    global_desired_role = role_request;
  }

  return sc;
}

static void set_role(throughput_role_t new_role)
{
  role = new_role;
  // Make sure the global, desired role will change
  global_desired_role = role;
}

static void handle_cli_switch_command(throughput_role_t role_request)
{
  sl_status_t sc = SL_STATUS_OK;

  if (role != role_request) {
    sc = set_role_request_and_disable_current_role(role_request);
  } else {
    app_log_warning("Already in that state." APP_LOG_NL);
  }

  if (sc != SL_STATUS_OK) {
    app_log_warning("There was an error during state change. STATUS: %lx" APP_LOG_NL, sc);
  }
}

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
uint8_t app_check_buttons()
{
  uint8_t ret = 0;
  if (sl_button_get_state(PB0) == SL_SIMPLE_BUTTON_PRESSED) {
    ret |= PB0_VALUE;
  }
  if (sl_button_get_state(PB1) == SL_SIMPLE_BUTTON_PRESSED) {
    ret |= PB1_VALUE;
  }
  return ret;
}

/**************************************************************************//**
 * Checks buttons
 * @param[in] handle the button handle
 *****************************************************************************/
void sl_button_on_change(const sl_button_t *handle)
{
  (void) handle;
  // Check states
  button_current = app_check_buttons();
}

/**************************************************************************//**
 * Set test type
 * @param[in] test_type type of the test:
 *  - sl_bt_gatt_notification or
 *  - sl_bt_gatt_indication
 *****************************************************************************/
void app_set_test_type(throughput_notification_t test_type)
{
  type = test_type;
#ifdef SL_CATALOG_SIMPLE_LED_PRESENT
#if SL_SIMPLE_LED_COUNT > 0
  if (test_type == sl_bt_gatt_indication) {
    sl_led_turn_on(LED0);
  } else {
    sl_led_turn_off(LED0);
  }
#endif // SL_SIMPLE_LED_COUNT
#endif // SL_CATALOG_SIMPLE_LED_PRESENT
}

/**************************************************************************//**
 * Start or stop the test
 * @param[in] start true if start is required
 *****************************************************************************/
void app_test(bool start)
{
  sl_status_t sc;
  if (start) {
    // Start test
    app_log_info("Starting test..." APP_LOG_NL);
    if (role == THROUGHPUT_ROLE_PERIPHERAL) {
      sc = throughput_peripheral_start(type);
      if (sc != SL_STATUS_OK) {
        app_log_warning("Failed to start test." APP_LOG_NL);
        if (sc == SL_STATUS_INVALID_STATE) {
          app_log_warning("Not in subscribed state!" APP_LOG_NL);
        }
      }
    } else {
      sc = throughput_central_set_type(type);
      if (sc != SL_STATUS_OK) {
        app_log_warning("Failed to set test type." APP_LOG_NL);
      } else {
        sc = throughput_central_start();
        if (sc != SL_STATUS_OK) {
          app_log_warning("Failed to start test." APP_LOG_NL);
          if (sc == SL_STATUS_INVALID_STATE) {
            app_log_warning("Not in subscribed state!" APP_LOG_NL);
          }
        }
      }
    }
  } else {
    // Stop
    if (role == THROUGHPUT_ROLE_PERIPHERAL) {
      sc = throughput_peripheral_stop();
      if (sc != SL_STATUS_OK) {
        app_log_warning("Failed to stop test." APP_LOG_NL);
      } else {
        app_log_info("Test Stopped." APP_LOG_NL);
      }
    } else {
      sc = throughput_central_stop();
      if (sc != SL_STATUS_OK) {
        app_log_warning("Failed to stop test." APP_LOG_NL);
      } else {
        app_log_info("Test Stopped." APP_LOG_NL);
      }
    }
  }
}

#if SL_SIMPLE_BUTTON_COUNT == 1

/**************************************************************************//**
 * Timer callback
 *****************************************************************************/
void app_button_timer_callback(app_timer_t *timer, void *data)
{
  (void) data;
  (void) timer;
  button_timer_rised = true;
  app_test(true);
}
#endif //SL_SIMPLE_BUTTON_COUNT

/**************************************************************************//**
 * Handle buttons during operation
 *****************************************************************************/
void app_handle_button_press()
{
#if SL_SIMPLE_BUTTON_COUNT >= 2
  app_set_test_type((throughput_notification_t)button_current);
  app_test(button_current);
#elif SL_SIMPLE_BUTTON_COUNT == 1
  if (button_current) {
    button_timer_rised = false;
    app_timer_start(&button_timer,
                    BUTTON_TIMEOUT,
                    app_button_timer_callback,
                    NULL,
                    false);
  } else {
    app_timer_stop(&button_timer);
    if (button_timer_rised) {
      app_test(false);
    } else {
      if (type == sl_bt_gatt_notification) {
        type = sl_bt_gatt_indication;
      } else {
        type = sl_bt_gatt_notification;
      }
      app_set_test_type(type);
    }
  }
#endif // SL_SIMPLE_BUTTON_COUNT
}

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
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
  // Mask first button release
  if (mask_release && button_change && !button_current) {
    button_change = 0;
    mask_release = false;
  }

  // Identify button change
  button_change = (button_current ^ button_previous);

  // There is a button change
  if (button_change) {
    // Handle button press during operation
    app_handle_button_press();
  }

  // Save current button states
  button_previous = button_current;

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
      app_log("Throughput Test initialized" APP_LOG_NL);
      if (app_check_buttons()) {
        // Enable throughput test in Central mode if button is pressed
        app_log_info("Button is pressed on start: Central mode set." APP_LOG_NL);
        set_role(THROUGHPUT_ROLE_CENTRAL);

        throughput_central_enable();
        // Mask first button release
        mask_release = true;
      } else {
        // Enable throughput test in Peripheral mode
        app_log_info("Peripheral mode set." APP_LOG_NL);
        set_role(THROUGHPUT_ROLE_PERIPHERAL);

        throughput_peripheral_enable();
      }
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      app_log_info("Connection opened" APP_LOG_NL);
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      app_log_info("Connection closed" APP_LOG_NL);
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

/**************************************************************************//**
 * CLI command to switch from current state to central
 *****************************************************************************/
void cli_switch_to_central(void)
{
  handle_cli_switch_command(THROUGHPUT_ROLE_CENTRAL);
}

/**************************************************************************//**
 * CLI command to switch from current state to peripheral
 *****************************************************************************/
void cli_switch_to_peripheral(void)
{
  handle_cli_switch_command(THROUGHPUT_ROLE_PERIPHERAL);
}

/*******************************************************************************
 ******************************   CALLBACKS    *********************************
 ******************************************************************************/

/**************************************************************************//**
 * Callback to handle transmission start event.
 *****************************************************************************/
void throughput_peripheral_on_start(void)
{
  app_log_info("Throughput test started");
  app_log_nl();
}

/**************************************************************************//**
 * Callback to handle transmission finished event.
 * @param[in] throughput throughput value in bits/second (bps)
 * @param[in] count data volume transmitted, in bytes
 *****************************************************************************/
void throughput_peripheral_on_finish(throughput_value_t throughput,
                                     throughput_count_t count)
{
  app_log_info("Throughput test finished: %lu bps, %lu packets",
               throughput,
               count);
  app_log_nl();
  throughput_ui_set_throughput(throughput);
  throughput_ui_set_count(count);
  throughput_ui_update();
}

/**************************************************************************//**
 * Callback to handle transmission start event.
 *****************************************************************************/
void throughput_central_on_start(void)
{
  app_log_info("Throughput test: reception started");
  app_log_nl();
}

/**************************************************************************//**
 * Callback to handle transmission finished event.
 * @param[in] throughput throughput value in bits/second (bps)
 * @param[in] count data volume transmitted, in bytes
 * @param[in] lost number of packets lost
 * @param[in] error number of wrong packets
 * @param[in] time total measurement time
 *****************************************************************************/
void throughput_central_on_finish(throughput_value_t throughput,
                                  throughput_count_t count,
                                  throughput_count_t lost,
                                  throughput_count_t error,
                                  throughput_time_t time)
{
  app_log_info("Throughput test: reception finished " APP_LOG_NL
               "%lu bps" APP_LOG_NL
               "%lu packets" APP_LOG_NL
               "%lu lost" APP_LOG_NL
               "%lu error" APP_LOG_NL
               "in %lu sec" APP_LOG_NL,
               throughput,
               count,
               lost,
               error,
               time);
  throughput_ui_set_throughput(throughput);
  throughput_ui_set_count(count);
  throughput_ui_update();
}

/**************************************************************************//**
 * Callback to handle state change.
 * @param[in] state current state
 *****************************************************************************/
void throughput_central_on_state_change(throughput_state_t state)
{
  throughput_ui_set_state(state);
  throughput_ui_update();

  if (state == THROUGHPUT_STATE_UNINITALIZED) {
    enable_new_throughput_role(THROUGHPUT_ROLE_PERIPHERAL);
  }
}

/**************************************************************************//**
 * Callback to handle state change.
 * @param[in] state current state
 *****************************************************************************/
void throughput_peripheral_on_state_change(throughput_state_t state)
{
  throughput_ui_set_state(state);
  throughput_ui_update();

  if (state == THROUGHPUT_STATE_UNINITALIZED) {
    enable_new_throughput_role(THROUGHPUT_ROLE_CENTRAL);
  }
}

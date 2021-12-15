/***************************************************************************//**
 * @file
 * @brief Automation IO GATT service
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

#include "stdbool.h"
#include "sl_status.h"
#include "gatt_db.h"
#include "app_assert.h"
#include "app_log.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "sl_gatt_service_aio.h"

// -----------------------------------------------------------------------------
// Private macros

// AIO digital states defined by the BLE standard
#define AIO_DIGITAL_STATE_INACTIVE  0
#define AIO_DIGITAL_STATE_ACTIVE    1
#define AIO_DIGITAL_STATE_TRISTATE  2
#define AIO_DIGITAL_STATE_UNKNOWN   3

#define AIO_DIGITAL_STATE_MASK      3
#define AIO_DIGITAL_STATE_SIZE      2
// AIO digital state is represented on 1 byte, thus 4 digitals are supported
#define AIO_DIGITAL_COUNT_MAX       4

#if (SL_SIMPLE_BUTTON_COUNT > AIO_DIGITAL_COUNT_MAX) \
  || (SL_SIMPLE_LED_COUNT > AIO_DIGITAL_COUNT_MAX)
#error Maximal AIO count exceeded.
#endif

// -----------------------------------------------------------------------------
// Private variables

static bool aio_notification_enabled = false;
static bool aio_button_changed = false;
static uint8_t aio_connection = 0;

// -----------------------------------------------------------------------------
// Private function declarations

static uint8_t aio_digital_in_get_state(void);
static uint8_t aio_digital_out_get_state(void);
static void aio_digital_out_set_state(uint8_t state);

static void aio_digital_in_notify(void);
static void aio_system_boot_cb(void);
static void aio_connection_opened_cb(sl_bt_evt_connection_opened_t *data);
static void aio_connection_closed_cb(sl_bt_evt_connection_closed_t *data);
static void aio_digital_in_read_cb(sl_bt_evt_gatt_server_user_read_request_t *data);
static void aio_digital_out_read_cb(sl_bt_evt_gatt_server_user_read_request_t *data);
static void aio_digital_in_changed_cb(sl_bt_evt_gatt_server_characteristic_status_t *data);
static void aio_digital_out_write_cb(sl_bt_evt_gatt_server_user_write_request_t *data);

// -----------------------------------------------------------------------------
// Private function definitions

static uint8_t aio_digital_in_get_state(void)
{
  uint8_t aio_state = 0;
  sl_button_state_t btn_state;
  uint8_t i;

  // read button states
  for (i = 0; i < SL_SIMPLE_BUTTON_COUNT; i++) {
    btn_state = sl_button_get_state(SL_SIMPLE_BUTTON_INSTANCE(i));
    if (btn_state == SL_SIMPLE_BUTTON_PRESSED) {
      aio_state |= AIO_DIGITAL_STATE_ACTIVE << (i * AIO_DIGITAL_STATE_SIZE);
    }
    app_log_info("AIO in: %d=%d", i, btn_state);
    app_log_nl();
  }

  return aio_state;
}

static uint8_t aio_digital_out_get_state(void)
{
  uint8_t aio_state = 0;
  sl_led_state_t led_state;
  uint8_t i;

  // read led states
  for (i = 0; i < SL_SIMPLE_LED_COUNT; i++) {
    led_state = sl_led_get_state(SL_SIMPLE_LED_INSTANCE(i));
    if (led_state == SL_LED_CURRENT_STATE_ON) {
      aio_state |= AIO_DIGITAL_STATE_ACTIVE << (i * AIO_DIGITAL_STATE_SIZE);
    }
  }
  return aio_state;
}

static void aio_digital_out_set_state(uint8_t state)
{
  uint8_t led_state, i;
  for (i = 0; i < SL_SIMPLE_LED_COUNT; i++) {
    led_state = (state >> (i * AIO_DIGITAL_STATE_SIZE)) & AIO_DIGITAL_STATE_MASK;
    if (led_state == AIO_DIGITAL_STATE_ACTIVE) {
      sl_led_turn_on(SL_SIMPLE_LED_INSTANCE(i));
    } else {
      sl_led_turn_off(SL_SIMPLE_LED_INSTANCE(i));
    }
    app_log_info("AIO out: %d=%d", i, led_state);
    app_log_nl();
  }
}

static void aio_digital_in_notify(void)
{
  sl_status_t sc;
  uint8_t value = aio_digital_in_get_state();
  sc = sl_bt_gatt_server_send_notification(
    aio_connection,
    gattdb_aio_digital_in,
    1,
    &value);
  app_assert_status(sc);
}

static void aio_system_boot_cb(void)
{
  sl_status_t sc;
  uint8_t value_in = SL_SIMPLE_BUTTON_COUNT;
  uint8_t value_out = SL_SIMPLE_LED_COUNT;
  sc = sl_bt_gatt_server_write_attribute_value(gattdb_aio_num_of_digitals_in, 0, 1, &value_in);
  app_assert_status(sc);
  sc = sl_bt_gatt_server_write_attribute_value(gattdb_aio_num_of_digitals_out, 0, 1, &value_out);
  app_assert_status(sc);
}

static void aio_connection_opened_cb(sl_bt_evt_connection_opened_t *data)
{
  (void)data;
  // Reset LED state
  aio_digital_out_set_state(0);
}

static void aio_connection_closed_cb(sl_bt_evt_connection_closed_t *data)
{
  (void)data;
  // Reset LED state
  aio_digital_out_set_state(0);
  // Disable notifications
  aio_notification_enabled = false;
}

static void aio_digital_in_read_cb(sl_bt_evt_gatt_server_user_read_request_t *data)
{
  sl_status_t sc;
  uint8_t value = aio_digital_in_get_state();
  sc = sl_bt_gatt_server_send_user_read_response(
    data->connection,
    data->characteristic,
    0,
    1,
    &value,
    NULL);
  app_assert_status(sc);
}

static void aio_digital_out_read_cb(sl_bt_evt_gatt_server_user_read_request_t *data)
{
  sl_status_t sc;
  uint8_t value = aio_digital_out_get_state();
  sc = sl_bt_gatt_server_send_user_read_response(
    data->connection,
    data->characteristic,
    0,
    1,
    &value,
    NULL);
  app_assert_status(sc);
}

static void aio_digital_in_changed_cb(sl_bt_evt_gatt_server_characteristic_status_t *data)
{
  aio_connection = data->connection;
  // indication or notification enabled
  if (sl_bt_gatt_disable != data->client_config_flags) {
    // enable notifications
    aio_notification_enabled = true;
    // send the first notification
    aio_digital_in_notify();
  }
  // indication and notification disabled
  else {
    aio_notification_enabled = false;
  }
}

static void aio_digital_out_write_cb(sl_bt_evt_gatt_server_user_write_request_t *data)
{
  sl_status_t sc;
  uint8_t att_errorcode = 0;

  if (data->value.len == 1) {
    aio_digital_out_set_state(data->value.data[0]);
  } else {
    att_errorcode = 0x0D; // Invalid Attribute Value Length
  }

  sc = sl_bt_gatt_server_send_user_write_response(data->connection,
                                                  data->characteristic,
                                                  att_errorcode);
  app_assert_status(sc);
}

// -----------------------------------------------------------------------------
// Public function definitions

void sl_gatt_service_aio_on_event(sl_bt_msg_t *evt)
{
  // Handle stack events
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_system_boot_id:
      aio_system_boot_cb();
      break;

    case sl_bt_evt_connection_opened_id:
      aio_connection_opened_cb(&evt->data.evt_connection_opened);
      break;

    case sl_bt_evt_connection_closed_id:
      aio_connection_closed_cb(&evt->data.evt_connection_closed);
      break;

    case sl_bt_evt_gatt_server_user_read_request_id:
      switch (evt->data.evt_gatt_server_user_read_request.characteristic) {
        case gattdb_aio_digital_in:
          aio_digital_in_read_cb(&evt->data.evt_gatt_server_user_read_request);
          break;
        case gattdb_aio_digital_out:
          aio_digital_out_read_cb(&evt->data.evt_gatt_server_user_read_request);
          break;
      }
      break;

    case sl_bt_evt_gatt_server_characteristic_status_id:
      if ((gattdb_aio_digital_in == evt->data.evt_gatt_server_characteristic_status.characteristic)
          && (sl_bt_gatt_server_client_config == (sl_bt_gatt_server_characteristic_status_flag_t)evt->data.evt_gatt_server_characteristic_status.status_flags)) {
        // client characteristic configuration changed by remote GATT client
        aio_digital_in_changed_cb(&evt->data.evt_gatt_server_characteristic_status);
      }
      break;

    case sl_bt_evt_gatt_server_user_write_request_id:
      if (gattdb_aio_digital_out == evt->data.evt_gatt_server_user_write_request.characteristic) {
        aio_digital_out_write_cb(&evt->data.evt_gatt_server_user_write_request);
      }
      break;
  }
}

void sl_gatt_service_aio_step(void)
{
  if (aio_button_changed) {
    aio_button_changed = false;
    aio_digital_in_notify();
  }
}

void sl_gatt_service_aio_on_change(void)
{
  if (aio_notification_enabled) {
    aio_button_changed = true;
  }
}

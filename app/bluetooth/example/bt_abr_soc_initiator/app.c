/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sl_bluetooth.h"
#include "app.h"

#include "abr_initiator.h"
#include "initiator_config.h"
#include "abr_initiator_component_config.h"
#include "abr_ui.h"
#include "abr_ui_types.h"
#include "sl_component_catalog.h"
#include "sl_simple_button.h"
#include "sl_simple_button_instances.h"
#include "sl_rail_util_hadm_antenna_offset_config.h"

#define PB0               SL_SIMPLE_BUTTON_INSTANCE(0)

static void abr_on_result(abr_rtl_result_t *result, void *user_data);

static abr_initiator_config_t initiator_config;
// This number comes from the matching network group delay + pcb trace delay +
// antenna delay.
// The offset is interpreted in cm (centimeters)
static int16_t *ant_offset_cm;
static int16_t ant_offset_cm_wireless[SL_RAIL_UTIL_HADM_ANTENNA_COUNT] = SL_RAIL_UTIL_HADM_ANTENNA_OFFSET_WIRELESS_CM;
static int16_t ant_offset_cm_wired[SL_RAIL_UTIL_HADM_ANTENNA_COUNT] = SL_RAIL_UTIL_HADM_ANTENNA_OFFSET_WIRED_CM;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////

  uint8_t mode = ABR_INITIATOR_MODE_PBR; // PBR, the default mode
  sl_button_state_t button_pressed = SL_SIMPLE_BUTTON_RELEASED;

  if (!ABR_INITIATOR_ANTENNA_OFFSET) {
    ant_offset_cm = ant_offset_cm_wireless;
    app_log_info("Wireless antenna offset will be used." APP_LOG_NL);
  } else {
    ant_offset_cm = ant_offset_cm_wired;
    app_log_info("Wired antenna offset will be used." APP_LOG_NL);
  }

  app_log_filter_threshold_set(APP_LOG_LEVEL_INFO);
  app_log_filter_threshold_enable(true);
  app_log_info(APP_LOG_NL);
  app_log_info("Silicon Labs ABR Initiator" APP_LOG_NL);
  app_log_info("--------------------------" APP_LOG_NL);

  app_log_info("Minimum CS procedure interval: %u" APP_LOG_NL, ABR_INITIATOR_MIN_CS_INTERVAL);
  app_log_info("Maximum CS procedure interval: %u"  APP_LOG_NL, ABR_INITIATOR_MAX_CS_INTERVAL);

  // Default parameters
  abr_initiator_config_set_default(&initiator_config);
  abr_ui_init();

  // Log channel map
  app_log_info("CS channel map:" APP_LOG_NL "    ");
  for (uint32_t i = 0; i < initiator_config.channel_map_len; i++) {
    app_log_append_info("0x%02x ", initiator_config.channel_map.data[i]);
  }
  app_log_append_info(APP_LOG_NL);

  // Configured parameters
  initiator_config.rssi_measurement_enabled = ABR_RSSI_MEASUREMENT_ENABLED;

  if (SL_SIMPLE_BUTTON_COUNT >= 1) {
    button_pressed = sl_button_get_state(PB0);
  }

  if (ABR_INITIATOR_MODE == ABR_INITIATOR_MODE_DYNAMIC) {
    if (button_pressed == SL_SIMPLE_BUTTON_PRESSED) {
      mode = ABR_INITIATOR_MODE_RTT; // RTT
    }
  } else {
    mode = ABR_INITIATOR_MODE;
  }

  switch (mode) {
    case ABR_INITIATOR_MODE_RTT: // RTT
      initiator_config.mode = sl_bt_cs_mode_rtt;
      abr_ui_write_text("RTT mode", ROW_MODE);
      break;
    case ABR_INITIATOR_MODE_PBR: // PBR
      initiator_config.mode = sl_bt_cs_mode_pbr;
      abr_ui_write_text("PBR mode", ROW_MODE);
      break;
    default:
      app_assert(1, "Invalid operation mode selected. Please select either 1 (RTT) or 2 (PBR)");
      break;
  }

  // Set up the distance display
  abr_ui_set_alignment(GLIB_ALIGN_CENTER);
  abr_ui_write_text("ABR distance", ROW_DISTANCE_TEXT);
  abr_ui_print_value(0.0f, ROW_DISTANCE_VALUE, "m");
  abr_ui_write_text("Likeliness", ROW_LIKELINESS_TEXT);
  abr_ui_print_value(0.0f, ROW_LIKELINESS_VALUE, NULL);
  if (initiator_config.rssi_measurement_enabled) {
    abr_ui_write_text("RSSI distance", ROW_RSSI_DISTANCE_TEXT);
    abr_ui_print_value(0.0f, ROW_RSSI_DISTANCE_VALUE, "m");
  }
  abr_ui_write_text("Bit error rate", ROW_BIT_ERROR_RATE_TEXT);
  abr_ui_print_value(0, ROW_BIT_ERROR_RATE_VALUE, NULL);
  abr_ui_update();
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
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);

      abr_initiator_init(abr_on_result, &initiator_config);

      // Set antenna offset on the SoC
      // This can be called any time after booting.
      sc = sl_bt_cs_set_antenna_configuration(SL_RAIL_UTIL_HADM_ANTENNA_COUNT * 2,
                                              (uint8_t *) ant_offset_cm);
      app_assert_status(sc);
      abr_initiator_enable();
      break;

    // -------------------------------
    // Default event handler.
    default:
      // All other event is handled by the initiator.
      break;
  }
}

static void abr_on_result(abr_rtl_result_t *result, void *user_data)
{
  (void) user_data;

  app_log_info("Measurement result: %lu mm" APP_LOG_NL,
               (uint32_t)(result->distance * 1000.f));

  uint32_t likeliness_whole = (uint32_t)result->likeliness;
  uint32_t likeliness_frac = (uint32_t)((result->likeliness - (float)likeliness_whole) * 100.0f);
  app_log_info("Measurement likeliness: %lu.%02lu" APP_LOG_NL,
               likeliness_whole,
               likeliness_frac);

  abr_ui_set_alignment(GLIB_ALIGN_CENTER);
  abr_ui_print_value(result->distance, ROW_DISTANCE_VALUE, "m");
  abr_ui_print_value(result->likeliness, ROW_LIKELINESS_VALUE, NULL);
  if (initiator_config.rssi_measurement_enabled) {
    abr_ui_print_value(result->rssi_distance,
                       ROW_RSSI_DISTANCE_VALUE,
                       "m");
    app_log_info("RSSI distance: %lu mm" APP_LOG_NL,
                 (uint32_t)(result->rssi_distance * 1000.f));
  }

  app_log_info("CS bit error rate: %u" APP_LOG_NL, result->cs_bit_error_rate);
  abr_ui_print_value(result->cs_bit_error_rate, ROW_BIT_ERROR_RATE_VALUE, NULL);

  app_log_info("Measurement finished" APP_LOG_NL);
  abr_ui_update();
}

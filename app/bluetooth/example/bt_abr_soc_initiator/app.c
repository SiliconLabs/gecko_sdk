/***************************************************************************//**
 * @file
 * @brief Core application logic.
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
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "app.h"

#include "abr_initiator.h"
#include "initiator_config.h"
#include "abr_ui.h"
#include "abr_ui_types.h"
#include "sl_component_catalog.h"
#include "sl_simple_button.h"
#include "sl_simple_button_instances.h"

#define PB0               SL_SIMPLE_BUTTON_INSTANCE(0)

static void abr_on_result(abr_rtl_result_t *result, void *user_data);

static abr_initiator_config_t initiator_config;

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

  // Default parameters
  abr_initiator_config_set_default(&initiator_config);
  abr_ui_init();

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
      initiator_config.submode = 0xff;
      abr_ui_write_text("RTT mode", ROW_MODE);
      break;
    case ABR_INITIATOR_MODE_PBR: // PBR
      initiator_config.mode = sl_bt_cs_mode_pbr;
      initiator_config.submode = sl_bt_cs_mode_rtt;
      abr_ui_write_text("PBR mode", ROW_MODE);
      break;
    default:
      app_assert(1, "Invalid operation mode selected. Please select either 1 (RTT) or 2 (PBR)");
      break;
  }

  // Set up the distance display
  abr_ui_set_alignment(GLIB_ALIGN_CENTER);
  if (initiator_config.rssi_measurement_enabled) {
    abr_ui_write_text("ABR distance", ROW_DISTANCE_TEXT);
    abr_ui_print_distance(0.0f, ROW_DISTANCE_VALUE);
    abr_ui_write_text("RSSI distance", ROW_RSSI_DISTANCE_TEXT);
    abr_ui_print_distance(0.0f, ROW_RSSI_DISTANCE_VALUE);
  } else {
    abr_ui_write_text("Distance", ROW_DISTANCE_TEXT);
    abr_ui_print_distance(0.0f, ROW_DISTANCE_VALUE);
  }
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
  app_log_info("Measurement result: %lu mm",
               (uint32_t)(result->distance * 1000.f));

  abr_ui_set_alignment(GLIB_ALIGN_CENTER);
  abr_ui_print_distance(result->distance, ROW_DISTANCE_VALUE);
  if (initiator_config.rssi_measurement_enabled) {
    abr_ui_print_distance(result->rssi_distance, ROW_RSSI_DISTANCE_VALUE);
    app_log_append_info(" | RSSI distance: %lu mm" APP_LOG_NL,
                        (uint32_t)(result->rssi_distance * 1000.f));
  } else {
    app_log_append_info(APP_LOG_NL);
  }
  abr_ui_update();
}

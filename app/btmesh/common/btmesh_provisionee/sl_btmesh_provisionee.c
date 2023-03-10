/***************************************************************************//**
 * @file
 * @brief
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

#include "sl_status.h"
#include "sl_common.h"

#include "sl_bt_api.h"
#include "sl_btmesh_api.h"

#include <string.h>
#include "app_assert.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "sl_btmesh_provisionee.h"
#include "sl_btmesh_provisionee_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup provisionee
 * @{
 ******************************************************************************/

// Suppress compiler warning of unused static function
#define SL_UNUSED  __attribute__((unused))

#define AUTH_VAL_SIZE_MAX 32

static size_t auth_val_size = AUTH_VAL_SIZE_MAX;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
/***************************************************************************//**
 * Dispatch the execution to one of the callback functions
 * based on the provided input action.
 *
 * @param[in] input_action field from ::sl_btmesh_evt_node_input_oob_request_t
 * @param[in] input_size field from ::sl_btmesh_evt_node_input_oob_request_t
 ******************************************************************************/
SL_UNUSED static void on_input_oob_request(uint8_t input_action, uint8_t input_size);

/***************************************************************************//**
 * Dispatch the execution to one of the callback functions
 * based on the provided output action.
 *
 * @param[in] output_action field from ::sl_btmesh_evt_node_display_output_oob_t
 * @param[in] data field from ::sl_btmesh_evt_node_display_output_oob_t
 ******************************************************************************/
SL_UNUSED static void on_output_oob_data(uint8_t output_action, uint8array* data);

/***************************************************************************//**
 * Convert a big endian uint8array's lowest 4 bytes to an uint32_t number
 *
 * @param[in] data uint8array containing the authentication value
 * @return the converted number
 ******************************************************************************/
SL_UNUSED static uint32_t oob_data_to_num(uint8array *data);

void sl_bt_provisionee_on_event(sl_bt_msg_t* evt)
{
  sl_status_t sc;
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_system_boot_id:
    #if SL_BTMESH_PROVISIONEE_OOB_ENABLE_CFG_VAL
      sc = sl_btmesh_node_init_oob(SL_BTMESH_PROVISIONEE_OOB_PUBLIC_KEY_ENABLE,
                                   SL_BTMESH_PROVISIONEE_AUTH_METHODS,
                                   SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_ACTIONS,
                                   SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_SIZE,
                                   SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_ACTIONS,
                                   SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_SIZE,
                                   SL_BTMESH_PROVISIONEE_OOB_INFO);
    #else
      sc = sl_btmesh_node_init();
    #endif
      log_status_error_f(sc, "Initialization failed" NL);
      sl_btmesh_provisionee_on_init(sc);
      break;

    default:
      break;
  }
}

void sl_btmesh_provisionee_on_event(sl_btmesh_msg_t* evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_node_initialized_id:
      if (!(evt->data.evt_node_initialized.provisioned)) {
        sl_status_t sc;
      #if SL_BTMESH_PROVISIONEE_INIT_PROV_RECORDS_CFG_VAL
        sc = sl_btmesh_node_init_provisioning_records();
        app_assert_status_f(sc, "Failed to init provisioning records");
      #endif
      #if SL_BTMESH_PROVISIONEE_AUTO_UNPROV_BEACONING_CFG_VAL
        sc = sl_btmesh_node_start_unprov_beaconing(SL_BTMESH_PROVISIONEE_AUTO_UNPROV_BEACONING_CFG_VAL);
        app_assert_status_f(sc, "Failed to start unprovisioned beaconing");
      #endif
      }
      break;

  #if (SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB || SL_BTMESH_PROVISIONEE_AUTH_STATIC_OOB)
    case sl_btmesh_evt_node_start_received_id:
      auth_val_size = evt->data.evt_node_start_received.algorithm == 0 ? 16 : 32;
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB
    case sl_btmesh_evt_node_display_output_oob_id:
      on_output_oob_data(evt->data.evt_node_display_output_oob.output_action,
                         &(evt->data.evt_node_display_output_oob.data));
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB
    case sl_btmesh_evt_node_input_oob_request_id:
      on_input_oob_request(evt->data.evt_node_input_oob_request.input_action,
                           evt->data.evt_node_input_oob_request.input_size);
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_STATIC_OOB
    case sl_btmesh_evt_node_static_oob_request_id:
      sl_btmesh_on_static_oob_request(auth_val_size);
      break;
  #endif
    default:
      break;
  }
}

sl_status_t sl_btmesh_provisionee_input_oob_num(uint32_t oob_num)
{
  app_assert(auth_val_size >= 4, "auth_val_size should be at least 4.");
  app_assert(auth_val_size <= AUTH_VAL_SIZE_MAX, "auth_val_size should be at most AUTH_VAL_SIZE_MAX.");
  uint8_t auth_val_buff[AUTH_VAL_SIZE_MAX] = { 0 };
  uint8_t last_index = auth_val_size - 1;
  for (uint8_t i = 0; i < 4; i++) {
    auth_val_buff[last_index - i] = (oob_num >> (8 * i)) & 0xFF;
  }
  return sl_btmesh_node_send_input_oob_request_response(auth_val_size, auth_val_buff);
}

sl_status_t sl_btmesh_provisionee_input_oob_str(char* oob_str)
{
  uint8_t auth_val_buff[AUTH_VAL_SIZE_MAX] = { 0 };
  strncpy((char*)auth_val_buff, oob_str, AUTH_VAL_SIZE_MAX);
  return sl_btmesh_node_send_input_oob_request_response(auth_val_size, auth_val_buff);
}

static void on_input_oob_request(uint8_t input_action, uint8_t input_size)
{
  (void)input_size;
  switch (input_action) {
  #if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_PUSH
    case sl_btmesh_node_oob_input_action_push:
      sl_btmesh_on_input_oob_request_push(input_size);
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_TWIST
    case sl_btmesh_node_oob_input_action_twist:
      sl_btmesh_on_input_oob_request_twist(input_size);
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_NUMERIC
    case sl_btmesh_node_oob_input_action_numeric:
      sl_btmesh_on_input_oob_request_numeric(input_size);
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_ALPHA
    case sl_btmesh_node_oob_input_action_alpha:
      sl_btmesh_on_input_oob_request_alphanumeric(input_size);
      break;
  #endif

    default:
      break;
  }
}

static uint32_t oob_data_to_num(uint8array *data)
{
  app_assert(data->len >= 4, "Data should be at least 4 byte long");
  uint32_t num = 0;
  uint8_t last_index = data->len - 1;
  for (uint8_t i = 0; i < 4; i++) {
    num |= data->data[last_index - i] << (8 * i);
  }
  return num;
}

static void on_output_oob_data(uint8_t output_action, uint8array* data)
{
  (void)data;
  switch (output_action) {
  #if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_BLINK
    case sl_btmesh_node_oob_output_action_blink:
      sl_btmesh_on_output_oob_blink(oob_data_to_num(data));
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_BEEP
    case sl_btmesh_node_oob_output_action_beep:
      sl_btmesh_on_output_oob_beep(oob_data_to_num(data));
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_VIBRATE
    case sl_btmesh_node_oob_output_action_vibrate:
      sl_btmesh_on_output_oob_vibrate(oob_data_to_num(data));
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_NUMERIC
    case sl_btmesh_node_oob_output_action_numeric:
      sl_btmesh_on_output_oob_numeric(oob_data_to_num(data));
      break;
  #endif

  #if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_ALPHA
    case sl_btmesh_node_oob_output_action_alpha:
      sl_btmesh_on_output_oob_alphanumeric((char*)(data->data));
      break;
  #endif

    default:
      break;
  }
}

SL_WEAK void sl_btmesh_provisionee_on_init(sl_status_t result)
{
  (void)result;
}

#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_PUSH
SL_WEAK void sl_btmesh_on_input_oob_request_push(uint8_t input_size)
{
  (void)input_size;
  log_info("Input OOB request push" NL);
}
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_TWIST
SL_WEAK void sl_btmesh_on_input_oob_request_twist(uint8_t input_size)
{
  (void)input_size;
  log_info("Input OOB request twist" NL);
}
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_NUMERIC
SL_WEAK void sl_btmesh_on_input_oob_request_numeric(uint8_t input_size)
{
  (void)input_size;
  log_info("Input OOB request numeric" NL);
}
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_ALPHA
SL_WEAK void sl_btmesh_on_input_oob_request_alpha(uint8_t input_size)
{
  (void)input_size;
  log_info("Input OOB request alphanumeric" NL);
}
#endif

#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_BLINK
SL_WEAK void sl_btmesh_on_output_oob_blink(uint32_t oob_num)
{
  log_info("Output OOB blink: %lu" NL, oob_num);
}
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_BEEP
SL_WEAK void sl_btmesh_on_output_oob_beep(uint32_t oob_num)
{
  log_info("Output OOB beep: %lu" NL, oob_num);
}
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_VIBRATE
SL_WEAK void sl_btmesh_on_output_oob_vibrate(uint32_t oob_num)
{
  log_info("Output OOB vibrate: %lu" NL, oob_num);
}
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_NUMERIC
SL_WEAK void sl_btmesh_on_output_oob_numeric(uint32_t oob_num)
{
  log_info("Output OOB numeric: %lu" NL, oob_num);
}
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_ALPHA
SL_WEAK void sl_btmesh_on_output_oob_alphanumeric(char* oob_str)
{
  log_info("Output OOB alphanumeric: %s" NL, oob_str);
}
#endif

#if SL_BTMESH_PROVISIONEE_AUTH_STATIC_OOB
SL_WEAK void sl_btmesh_on_static_oob_request(size_t oob_size)
{
  (void)oob_size;
  log_info("Static OOB request" NL);
}
#endif

/** @} (end addtogroup provisionee) */

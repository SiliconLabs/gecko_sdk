/***************************************************************************//**
 * @file
 * @brief Generic Level Client module for Delta Set and Move Set Unacknowledged
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

// -----------------------------------------------------------------------------
// Includes

#include "sl_status.h"

// BT Mesh stack headers
#include "sl_btmesh_generic_model_capi_types.h"
#include "sl_btmesh_api.h"
#include "sl_btmesh_dcd.h"
#include "sl_btmesh_lib.h"

#include "sl_bt_api.h"

#include "sl_btmesh_generic_level_client_ext.h"
#include "sl_btmesh_generic_level_client_ext_config.h"

#include "app_timer.h"
#include "app_assert.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

// Warning! app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

// -----------------------------------------------------------------------------
// Macros

/// No flags used for message
#define NO_FLAGS          0
/// Immediate transition time is 0 seconds
#define TRANS_IMMEDIATE   0
/// Callback has no parameters
#define NO_CALLBACK_DATA  NULL

// -----------------------------------------------------------------------------
// Enums, structs, typedefs

// -----------------------------------------------------------------------------
// Private function declarations

/***************************************************************************//**
 * Initialize the Generic Level Client model
 ******************************************************************************/
static void generic_client_init(void);

/***************************************************************************//**
 * Process responses from the generic client server
 *
 * @param[in] model_id       Client model ID
 * @param[in] element_index  Client model element index
 * @param[in] client_addr    Address of the client model which sent the message
 * @param[in] server_addr    Address of the server model that responded
 * @param[in] current        Current state of the model
 * @param[in] target         Requested state of the model
 * @param[in] remaining_ms   Remaining time of the transition in ms
 * @param[in] response_flags Message flags
 ******************************************************************************/
static void generic_level_client_ext_on_response(uint16_t model_id,
                                                 uint16_t element_index,
                                                 uint16_t client_addr,
                                                 uint16_t server_addr,
                                                 const struct mesh_generic_state *current,
                                                 const struct mesh_generic_state *target,
                                                 uint32_t remaining_ms,
                                                 uint8_t response_flags);

/***************************************************************************//**
 * Wrapper for mesh_lib_generic_client_register_handler with an assert which
 * detects if the Btmesh API call results in error. The parameters of the two
 * functions are the same but the wrapper does not have a return value.
 *
 * @param[in] model_id      Model for which functions are being registered
 * @param[in] element_index Element where the model resides
 * @param[in] response      Function for server responses
 ******************************************************************************/
static void generic_client_register_handler(uint16_t model_id,
                                            uint16_t elem_index,
                                            mesh_lib_generic_client_server_response_cb response);

/***************************************************************************//**
 * Publish one Generic Level request, depending on the request kind
 *
 * @param[in] retrans        Indicates if it's the first request or a retransmission
 * @param[in] kind           Type of request. One of the following:
 *                           mesh_generic_request_level_delta
                             mesh_generic_request_level_move
                             mesh_generic_request_level_halt
 ******************************************************************************/
static void send_request(bool retrans, mesh_generic_request_t kind);

/// Periodic timer callbacks

/***************************************************************************//**
 * Generic Level Delta retransmission timer callback
 *
 * @param[in] handle Pointer to handle instance
 * @param[in] data   Pointer to input data
 ******************************************************************************/
static void on_delta_retransmission_timer_expiry(app_timer_t *handle,
                                                 void *data);

/***************************************************************************//**
 * Generic Level Move retransmission timer callback
 *
 * @param[in] handle Pointer to handle instance
 * @param[in] data   Pointer to input data
 ******************************************************************************/
static void on_move_retransmission_timer_expiry(app_timer_t *handle,
                                                void *data);

/***************************************************************************//**
 * Move Halt retransmission timer callback
 *
 * @param[in] handle Pointer to handle instance
 * @param[in] data   Pointer to input data
 ******************************************************************************/
static void on_halt_retransmission_timer_expiry(app_timer_t *handle,
                                                void *data);

// -----------------------------------------------------------------------------
// Static variables

/// Transaction ID of the current message
static uint8_t trid = 0;
/// Number of requests to be sent
static uint8_t request_count;
/// Periodic retransmission timer handle
static app_timer_t retransmission_timer;
/// Requested delta level
static int32_t delta_level = 0;
/// Requested move level
static int16_t move_level = 0;

// -----------------------------------------------------------------------------
// Private function definitions

/*******************************************************************************
 * Initialize the Generic Level Client model
 ******************************************************************************/
static void generic_client_init(void)
{
  generic_client_register_handler(MESH_GENERIC_LEVEL_CLIENT_MODEL_ID,
                                  BTMESH_GENERIC_LEVEL_CLIENT_EXT_MAIN,
                                  generic_level_client_ext_on_response);
}

/***************************************************************************//**
 * Wrapper for mesh_lib_generic_client_register_handler with an assert which
 * detects if the Btmesh API call results in error. The parameters of the two
 * functions are the same but the wrapper does not have a return value.
 * @param[in] model_id   Model for which functions are being registered
 * @param[in] elem_index Element where the model resides
 * @param[in] response   Function for server responses
 ******************************************************************************/
static void generic_client_register_handler(uint16_t model_id,
                                            uint16_t elem_index,
                                            mesh_lib_generic_client_server_response_cb response)
{
  sl_status_t sc;

  sc = mesh_lib_generic_client_register_handler(model_id, elem_index, response);
  log_status_error_f(sc, "Failed to register Generic Level Client Ext handler" APP_LOG_NL);
}

/*******************************************************************************
 * Publish one Generic Level request, depending on the request kind
 ******************************************************************************/
static void send_request(bool retrans, mesh_generic_request_t kind)
{
  uint16_t requested_delay;
  if (kind != mesh_generic_request_level_delta
      && kind != mesh_generic_request_level_move
      && kind != mesh_generic_request_level_halt) {
    return;
  }
  struct mesh_generic_request req;
  sl_status_t sc;

  req.kind = kind;
  switch (kind) {
    case mesh_generic_request_level_delta:
      req.delta = delta_level;
      requested_delay = SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_TIMEOUT_CFG_VAL;
      break;
    case mesh_generic_request_level_move:
      req.level = move_level;
      requested_delay = SL_BTMESH_GENERIC_LEVEL_EXT_MOVE_RETRANSMISSION_TIMEOUT_CFG_VAL;
      break;
    case mesh_generic_request_level_halt:
      requested_delay = SL_BTMESH_GENERIC_LEVEL_EXT_HALT_RETRANSMISSION_TIMEOUT_CFG_VAL;
      break;
    default:
      return;
  }

  if (retrans == false) {
    trid++;
  }

  // Delay for the request is calculated so that the last request will have
  // a zero delay and each of the previous request have delay that increases
  // in configurable steps. The default setting is using three requests per
  // button press with delays set as 100, 50 and 0 ms
  uint16_t delay = (request_count - 1) * requested_delay;

  sc = mesh_lib_generic_client_publish(MESH_GENERIC_LEVEL_CLIENT_MODEL_ID,
                                       BTMESH_GENERIC_LEVEL_CLIENT_EXT_MAIN,
                                       trid,
                                       &req,
                                       TRANS_IMMEDIATE,
                                       delay,
                                       NO_FLAGS
                                       );

  if (sc == SL_STATUS_OK) {
    log_info("Generic level request sent, kind = %u, trid = %u, delay = %u" NL, kind, trid, delay);
  } else {
    log_status_error_f(sc, "Generic Level Client Publish failed" NL);
  }

  // Keep track of how many requests have been sent
  if (request_count > 0) {
    (request_count)--;
  }
}

// -----------------------------------------------------------------------------
// Public function definitions

/*******************************************************************************
 * Handle BT Mesh events.
 *
 * This function is called automatically by Universal Configurator after
 * enabling the component.
 *
 * @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_on_event(sl_btmesh_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id:
    case sl_btmesh_evt_node_provisioned_id:
      generic_client_init();
      break;
    case sl_btmesh_evt_node_initialized_id:
      if (evt->data.evt_node_initialized.provisioned) {
        generic_client_init();
      }
      break;
    default:
      break;
  }
}

/*******************************************************************************
 * Send Generic Level Delta Set Unacknowledged message
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_delta_set_unack(int32_t delta)
{
  request_count = SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_COUNT_CFG_VAL;

  delta_level = delta;

  send_request(false, mesh_generic_request_level_delta);  // Send the first request

  // If there are more requests to send, start a repeating soft timer
  // to trigger retransmission of the request after the configured delay
  if (request_count > 0) {
    sl_status_t sc = app_timer_start(&retransmission_timer,
                                     SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_TIMEOUT_CFG_VAL,
                                     on_delta_retransmission_timer_expiry,
                                     NO_CALLBACK_DATA,
                                     true);
    app_assert_status_f(sc, "Failed to start delta periodic timer");
  }
}

/*******************************************************************************
 * Send Generic Level Move Set Unacknowledged message
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_move_set_unack(int16_t delta_level)
{
  request_count = SL_BTMESH_GENERIC_LEVEL_EXT_MOVE_RETRANSMISSION_COUNT_CFG_VAL;

  move_level = delta_level;

  send_request(false, mesh_generic_request_level_move);  // Send the first request

  // If there are more requests to send, start a repeating soft timer
  // to trigger retransmission of the request after the configured delay
  if (request_count > 0) {
    sl_status_t sc = app_timer_start(&retransmission_timer,
                                     SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_TIMEOUT_CFG_VAL,
                                     on_move_retransmission_timer_expiry,
                                     NO_CALLBACK_DATA,
                                     true);
    app_assert_status_f(sc, "Failed to start move periodic timer");
  }
}

/*******************************************************************************
 * Halt previous Generic Level Move command
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_halt(void)
{
  request_count = SL_BTMESH_GENERIC_LEVEL_EXT_HALT_RETRANSMISSION_COUNT_CFG_VAL;

  send_request(false, mesh_generic_request_level_halt);  // Send the first request

  // If there are more requests to send, start a repeating soft timer
  // to trigger retransmission of the request after the configured delay
  if (request_count > 0) {
    sl_status_t sc = app_timer_start(&retransmission_timer,
                                     SL_BTMESH_GENERIC_LEVEL_EXT_DELTA_RETRANSMISSION_TIMEOUT_CFG_VAL,
                                     on_halt_retransmission_timer_expiry,
                                     NO_CALLBACK_DATA,
                                     true);
    app_assert_status_f(sc, "Failed to start halt periodic timer");
  }
}

// -----------------------------------------------------------------------------
// Event / callback definitions

/***************************************************************************//**
 * Generic Level Delta retransmission timer callback
 ******************************************************************************/
static void on_delta_retransmission_timer_expiry(app_timer_t *handle,
                                                 void *data)
{
  (void)data;
  (void)handle;

  // First parameter (true) indicates that this is a retransmission
  send_request(true, mesh_generic_request_level_delta);
  // stop retransmission timer if it was the last attempt
  if (request_count == 0) {
    sl_status_t sc = app_timer_stop(&retransmission_timer);
    app_assert_status_f(sc, "Failed to stop periodic timer");
  }
}

/***************************************************************************//**
 * Generic Level Move retransmission timer callback
 ******************************************************************************/
static void on_move_retransmission_timer_expiry(app_timer_t *handle,
                                                void *data)
{
  (void)data;
  (void)handle;

  // First parameter (true) indicates that this is a retransmission
  send_request(true, mesh_generic_request_level_move);
  // stop retransmission timer if it was the last attempt
  if (request_count == 0) {
    sl_status_t sc = app_timer_stop(&retransmission_timer);
    app_assert_status_f(sc, "Failed to stop periodic timer");
  }
}

/***************************************************************************//**
 * Move Halt retransmission timer callback
 ******************************************************************************/
static void on_halt_retransmission_timer_expiry(app_timer_t *handle,
                                                void *data)
{
  (void)data;
  (void)handle;

  // First parameter (true) indicates that this is a retransmission
  send_request(true, mesh_generic_request_level_halt);
  // stop retransmission timer if it was the last attempt
  if (request_count == 0) {
    sl_status_t sc = app_timer_stop(&retransmission_timer);
    app_assert_status_f(sc, "Failed to stop periodic timer");
  }
}

/*******************************************************************************
 * Process responses from the generic client server
 ******************************************************************************/
static void generic_level_client_ext_on_response(uint16_t model_id,
                                                 uint16_t element_index,
                                                 uint16_t client_addr,
                                                 uint16_t server_addr,
                                                 const struct mesh_generic_state *current,
                                                 const struct mesh_generic_state *target,
                                                 uint32_t remaining_ms,
                                                 uint8_t response_flags)
{
  (void)model_id;
  (void)element_index;
  (void)client_addr;
  (void)server_addr;
  (void)current;
  (void)target;
  (void)remaining_ms;
  (void)response_flags;
}

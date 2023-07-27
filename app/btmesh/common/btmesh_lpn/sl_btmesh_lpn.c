/***************************************************************************//**
 * @file
 * @brief Low Power Node implementation
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
#include "sl_status.h"

#include "sl_bt_api.h"
#include "sl_btmesh_api.h"
#include "sl_btmesh_config.h"

#include <stdio.h>
#include "app_assert.h"
#include "app_timer.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "sl_btmesh_lpn.h"
#include "sl_btmesh_lpn_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup lpn
 * @{
 ******************************************************************************/

/// High Priority
#define HIGH_PRIORITY                  0
/// No Timer Options
#define NO_FLAGS                       0
/// Callback has not parameters
#define NO_CALLBACK_DATA               (void *)NULL

/// Friend finding timer handler
static app_timer_t lpn_friend_find_timer;
/// Node configuration timer handler
static app_timer_t lpn_node_configured_timer;
/// High throughput timer handler
static app_timer_t lpn_high_throughput_timer;

/// High throughput timing list head
static sl_btmesh_lpn_high_throughput_timer_t *lpn_high_throughput_head;

/// Friend finding timer callback
static void lpn_friend_find_timer_cb(app_timer_t *handle,
                                     void *data);
/// Node configuration timer callback
static void lpn_node_configured_timer_cb(app_timer_t *handle,
                                         void *data);
/// High throughput timer callback
static void lpn_high_throughput_timer_cb(app_timer_t *handle,
                                         void *data);

/// Flag for indicating that lpn feature is active
static uint8_t lpn_active = 0;

/// Number of active proxy connections
static uint8_t num_mesh_proxy_conn = 0;

/// Address of the friend node if the friendship is active otherwise it is zero
static uint16_t friend_address = 0;

// Stores the netkey index of the network which the low power node belongs to
static uint16_t lpn_friend_netkey_idx = 0;

static void lpn_establish_friendship(void);

static void set_configuration_timer(uint32_t delay);

/***************************************************************************//**
 * Initialize LPN functionality with configuration and friendship establishment.
 ******************************************************************************/
void sl_btmesh_lpn_feature_init(void)
{
  sl_status_t result = SL_STATUS_OK;
  size_t netkey_bytes_written;

  // The sl_btmesh_node_get_networks API does not copy any netkey indexes if the
  // buffer is not long enough for all netkey indexes. It is expected that only
  // one netkey is present in the device but this array is allocated to provide
  // space for SL_BTMESH_CONFIG_MAX_NETKEYS netkey indexes to be on the safe
  // side.
  uint8_t netkey_bytes[SL_BTMESH_CONFIG_MAX_NETKEYS * 2];

  // Do not initialize LPN if lpn is currently active
  // or any GATT proxy connection is opened
  if (lpn_active || num_mesh_proxy_conn) {
    return;
  }

  // Initialize LPN functionality.
  result = sl_btmesh_lpn_init();
  if (result != SL_STATUS_OK) {
    log_status_error_f(result,
                       "LPN initialization failed" NL);
    return;
  }
  lpn_active = 1;
  log_info("LPN initialized" NL);
  sl_btmesh_lpn_on_init();

  // Configure LPN minimum friend queue length
  result = sl_btmesh_lpn_config(sl_btmesh_lpn_queue_length,
                                SL_BTMESH_LPN_MIN_QUEUE_LENGTH_CFG_VAL);
  if (result != SL_STATUS_OK) {
    log_status_error_f(result,
                       "LPN queue configuration failed" NL);
    return;
  }
  // Configure LPN poll timeout
  result = sl_btmesh_lpn_config(sl_btmesh_lpn_poll_timeout,
                                SL_BTMESH_LPN_POLL_TIMEOUT_CFG_VAL);
  if (result != SL_STATUS_OK) {
    log_status_error_f(result,
                       "LPN poll timeout configuration failed" NL);
    return;
  }
  // Configure LPN receive delay
  result = sl_btmesh_lpn_config(sl_btmesh_lpn_receive_delay,
                                SL_BTMESH_LPN_RECEIVE_DELAY_CFG_VAL);
  if (result != SL_STATUS_OK) {
    log_status_error_f(result,
                       "LPN receive delay configuration failed" NL);
    return;
  }
  // Configure LPN request retries
  result = sl_btmesh_lpn_config(sl_btmesh_lpn_request_retries,
                                SL_BTMESH_LPN_REQUEST_RETRIES_CFG_VAL);
  if (result != SL_STATUS_OK) {
    log_status_error_f(result,
                       "LPN request retries configuration failed" NL);
    return;
  }
  // Configure LPN retry interval
  result = sl_btmesh_lpn_config(sl_btmesh_lpn_retry_interval,
                                SL_BTMESH_LPN_RETRY_INTERVAL_CFG_VAL);
  if (result != SL_STATUS_OK) {
    log_status_error_f(result,
                       "LPN retry interval configuration failed" NL);
    return;
  }

  // It is necessary to determine the netkey index because it is assigned by the
  // provisioner device and it can't be assumed that it is always 0 or other
  // constant value. If the node is part of multiple networks then it tries to
  // establish friendship with the first netkey in the list.
  result = sl_btmesh_node_get_networks(sizeof(netkey_bytes),
                                       &netkey_bytes_written,
                                       &netkey_bytes[0]);

  if (result != SL_STATUS_OK) {
    log_status_error_f(result,
                       "LPN get networks request failed" NL);
  } else if (netkey_bytes_written < 2) {
    // Defensive programming: this should not occur because at this point the
    // node is provisioned therefore at least one netkey shall be saved in the
    // node
    log_error("LPN get networks provided invalid number of netkey bytes (0x%zu)" NL,
              netkey_bytes_written);
  } else {
    // The get networks API provides the netkeys in little endian format
    lpn_friend_netkey_idx = (netkey_bytes[1] << 8) | netkey_bytes[0];

    // Establish friendship with the lpn_friend_netkey_idx network key
    // The lpn_establish_friendship function uses global variable to identify
    // the network index because it does not change after provisioning but the
    // this function is called after a proxy connection is closed too and the
    // sl_btmesh_lpn_terminate_friendship API needs the netkey index as well so
    // the netkey index shall be stored.
    lpn_establish_friendship();
  }

  // Set initial head value to NULL
  lpn_high_throughput_head = NULL;
}

/***************************************************************************//**
 * Deinitialize LPN functionality.
 ******************************************************************************/
void sl_btmesh_lpn_feature_deinit(void)
{
  sl_status_t result = 0;

  if (!lpn_active) {
    return; // lpn feature is currently inactive
  }

  // Cancel friend finding timer
  sl_status_t sc = app_timer_stop(&lpn_friend_find_timer);
  app_assert_status_f(sc, "Failed to stop timer");

  // Terminate friendship if exist
  result = sl_btmesh_lpn_terminate_friendship(lpn_friend_netkey_idx);
  log_status_error_f(result, "Friendship termination failed" NL);
  // turn off lpn feature
  result = sl_btmesh_lpn_deinit();
  log_status_error_f(result, "LPN deinit failed" NL);

  lpn_active = 0;
  friend_address = 0;
  log_info("LPN deinitialized" NL);
  sl_btmesh_lpn_on_deinit();
}

/*******************************************************************************
* Return if the friendship is active between LPN and friend node
*******************************************************************************/
bool sl_btmesh_lpn_is_friendship_active(void)
{
  return (0 != friend_address);
}

/*******************************************************************************
* Poll the Friend node for stored messages and security updates
*******************************************************************************/
sl_status_t sl_btmesh_lpn_poll_request(void)
{
  return sl_btmesh_lpn_poll(lpn_friend_netkey_idx);
}

/*******************************************************************************
 *  Handling of mesh lpn events.
 *  It handles:
 *   - lpn_friendship_established_id
 *   - lpn_friendship_failed_id
 *   - lpn_friendship_terminated_id
 *
 *  @param[in] evt  Pointer to incoming lpn event.
 ******************************************************************************/
void sl_btmesh_lpn_on_event(sl_btmesh_msg_t* evt)
{
  sl_btmesh_evt_node_initialized_t *data;

  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_node_initialized_id:
      data = (sl_btmesh_evt_node_initialized_t *)&(evt->data);
      if (data->provisioned) {
        sl_btmesh_lpn_feature_init();
      }
      break;
    case sl_btmesh_evt_prov_initialized_id:
    case sl_btmesh_evt_node_provisioned_id:
      set_configuration_timer(SL_BTMESH_LPN_TIMEOUT_AFTER_PROVISIONED_CFG_VAL);
      break;

    case sl_btmesh_evt_node_model_config_changed_id:
      set_configuration_timer(SL_BTMESH_LPN_TIMEOUT_AFTER_CONFIG_MODEL_CHANGED_CFG_VAL);
      break;

    case sl_btmesh_evt_node_config_set_id:
      set_configuration_timer(SL_BTMESH_LPN_TIMEOUT_AFTER_CONFIG_SET_CFG_VAL);
      break;

    case sl_btmesh_evt_node_key_added_id:
      set_configuration_timer(SL_BTMESH_LPN_TIMEOUT_AFTER_KEY_CFG_VAL);
      break;

    case sl_btmesh_evt_lpn_friendship_established_id:
      friend_address = evt->data.evt_lpn_friendship_established.friend_address;
      sl_btmesh_lpn_on_friendship_established(friend_address);
      break;

    case sl_btmesh_evt_lpn_friendship_failed_id: {
      sl_btmesh_lpn_on_friendship_failed(
        evt->data.evt_lpn_friendship_failed.reason);

      // try again after timer expires
      sl_status_t sc = app_timer_start(&lpn_friend_find_timer,
                                       SL_BTMESH_LPN_FRIEND_FIND_TIMEOUT_CFG_VAL,
                                       lpn_friend_find_timer_cb,
                                       NO_CALLBACK_DATA,
                                       false);
      app_assert_status_f(sc, "Failed to start timer");

      break;
    }

    case sl_btmesh_evt_lpn_friendship_terminated_id:
      sl_btmesh_lpn_on_friendship_terminated(
        evt->data.evt_lpn_friendship_terminated.reason);
      friend_address = 0;
      if (num_mesh_proxy_conn == 0) {
        // try again after timer expires
        sl_status_t sc = app_timer_start(&lpn_friend_find_timer,
                                         SL_BTMESH_LPN_FRIEND_FIND_TIMEOUT_CFG_VAL,
                                         lpn_friend_find_timer_cb,
                                         NO_CALLBACK_DATA,
                                         false);
        app_assert_status_f(sc, "Failed to start timer");
      }
      break;

    /* Proxy Events*/
    case sl_btmesh_evt_proxy_connected_id:
      num_mesh_proxy_conn++;
      // turn off lpn feature after GATT proxy connection is opened
      sl_btmesh_lpn_feature_deinit();
      break;

    case sl_btmesh_evt_proxy_disconnected_id:
      if (num_mesh_proxy_conn > 0) {
        if (--num_mesh_proxy_conn == 0) {
          // Initialize lpn when there is no active proxy connection
          sl_btmesh_lpn_feature_init();
        }
      }
      break;

    default:
      break;
  }
}

sl_status_t sl_btmesh_lpn_high_throughput_register(sl_btmesh_lpn_high_throughput_timer_t *handle,
                                                   uint32_t timeout,
                                                   sl_btmesh_lpn_high_throughput_operation_mode_t mode)
{
  sl_status_t retval = SL_STATUS_OK;

  handle->timeout = timeout;
  handle->mode = mode;
  if (lpn_high_throughput_head == NULL) {
    // If head is not yet set, set this as the head
    lpn_high_throughput_head = handle;
    // Since head was not set, the timer is turned off as well
    sl_status_t sc = app_timer_start(&lpn_high_throughput_timer,
                                     handle->timeout,
                                     lpn_high_throughput_timer_cb,
                                     NULL,
                                     false);
    log_status_error_f(sc, "Failed to start timer" NL);
  } else if (lpn_high_throughput_head == handle) {
    // If only one element is registered, the loop below would not detect it
    retval = SL_STATUS_ALREADY_EXISTS;
  } else {
    sl_btmesh_lpn_high_throughput_timer_t *tmp;
    for (tmp = lpn_high_throughput_head; tmp->next != NULL; tmp = tmp->next) {
      if (handle == tmp) {
        retval = SL_STATUS_ALREADY_EXISTS;
      }
    }
    // In case the last element is the one given
    if (handle == tmp) {
      retval = SL_STATUS_ALREADY_EXISTS;
    }
    // SL_STATUS_OK indicates that no match has been found; append to the end
    if (SL_STATUS_OK == retval) {
      // Put handle at the end of the list
      tmp->next = handle;
    }
  }
  // SL_STATUS_OK indicates successful append, i.e. handle is at the end of list
  if (SL_STATUS_OK == retval) {
    // Indicate list end
    handle->next = NULL;
  }

  // If the registered handler requests a faster timer that's already running,
  // restart timer with the faster.
  // This might also be the case for re-registering a slowing timer as well.
  if (lpn_high_throughput_timer.timeout_ms > handle->timeout) {
    sl_status_t sc = app_timer_start(&lpn_high_throughput_timer,
                                     handle->timeout,
                                     lpn_high_throughput_timer_cb,
                                     NULL,
                                     false);
    log_status_error_f(sc, "Failed to start timer" NL);
  }
  return retval;
}

sl_status_t sl_btmesh_lpn_high_throughput_unregister(sl_btmesh_lpn_high_throughput_timer_t *handle)
{
  if (lpn_high_throughput_head == NULL) {
    // If no head, nothing is to be unregistered
    return SL_STATUS_NOT_FOUND;
  } else if (lpn_high_throughput_head == handle) {
    // Special case for the head being unregistered
    // This also works if only one element have been registered
    lpn_high_throughput_head = lpn_high_throughput_head->next;
    handle->next = NULL;
    return SL_STATUS_OK;
  } else {
    sl_btmesh_lpn_high_throughput_timer_t *tmp;
    // Find the entry to be removed and remove it
    for (tmp = lpn_high_throughput_head; tmp->next != NULL; tmp = tmp->next) {
      if (handle == tmp->next) {
        tmp->next = tmp->next->next;
        handle->next = NULL;
        return SL_STATUS_OK;
      }
    }
  }
  // No element was found in the loop above
  return SL_STATUS_NOT_FOUND;
}

/***************************************************************************//**
 * Establishes friendship and logs if the request fails
 ******************************************************************************/
static void lpn_establish_friendship(void)
{
  sl_status_t result;

  log_info("Trying to find a friend..." NL);
  result = sl_btmesh_lpn_establish_friendship(lpn_friend_netkey_idx);

  log_status_error_f(result, "Friend not found" NL);
}

/***************************************************************************//**
 *  Set the timer that delay LPN initialization to enable quick configuration
 *  over advertising bearer.
 *
 *  @param[in] delay  Time to set for the timer.
 ******************************************************************************/
static void set_configuration_timer(uint32_t delay)
{
  sl_status_t sc = app_timer_start(&lpn_node_configured_timer,
                                   delay,
                                   lpn_node_configured_timer_cb,
                                   NO_CALLBACK_DATA,
                                   false);
  app_assert_status_f(sc, "Failed to start timer");
}

/**************************************************************************//**
 * @addtogroup btmesh_lpn_tmr_cb Timer Callbacks
 * @{
 *****************************************************************************/
static void lpn_friend_find_timer_cb(app_timer_t *handle, void *data)
{
  (void)data;
  (void)handle;

  lpn_establish_friendship();
}

static void  lpn_node_configured_timer_cb(app_timer_t *handle, void *data)
{
  (void)data;
  (void)handle;

  if (!lpn_active) {
    log_info("Trying to initialize lpn..." NL);
    sl_btmesh_lpn_feature_init();
  }
}

static void lpn_high_throughput_timer_cb(app_timer_t *handle, void *data)
{
  (void)data;
  (void)handle;

  // Execute main operation; poll friend
  sl_btmesh_lpn_poll(lpn_friend_netkey_idx);

  // If all element were unregistered beforehand, simply return
  if (lpn_high_throughput_head == NULL) {
    return;
  }

  // Find fastest timeout handler
  sl_btmesh_lpn_high_throughput_timer_t *tmp;
  sl_btmesh_lpn_high_throughput_timer_t *fastest = lpn_high_throughput_head;
  for (tmp = lpn_high_throughput_head;
       tmp != NULL; tmp = tmp->next) {
    if (fastest->timeout > tmp->timeout) {
      fastest = tmp;
    }
  }

  if (fastest->timeout < SL_BTMESH_LPN_POLL_TIMEOUT_CFG_VAL) {
    // Start a timer with the timeout value
    sl_status_t sc = app_timer_start(&lpn_high_throughput_timer,
                                     fastest->timeout,
                                     lpn_high_throughput_timer_cb,
                                     NULL,
                                     false);
    app_assert_status_f(sc, "Failed to start timer");

    switch (fastest->mode) {
      case SL_BTMESH_LPN_HIGH_THROUGHPUT_SLOWING:
        // If this is set to be slowed down, increase timeout
        fastest->timeout <<= 1;
        break;
      default:
        // Intentionally left empty
        break;
    }
  } else {
    // If the timer has a slower timeout than the default, unregister it
    sl_btmesh_lpn_high_throughput_unregister(fastest);
  }
}

/** @} (end addtogroup btmesh_lpn_tmr_cb) */

/// @addtogroup btmesh_lpn_weak_cb Weak implementation of Callbacks
/// @{

SL_WEAK void sl_btmesh_lpn_on_init(void)
{
}

SL_WEAK void sl_btmesh_lpn_on_deinit(void)
{
}

SL_WEAK void sl_btmesh_lpn_on_friendship_established(uint16_t node_address)
{
  (void) node_address;
}

SL_WEAK void sl_btmesh_lpn_on_friendship_failed(uint16_t reason)
{
  (void) reason;
}

SL_WEAK void sl_btmesh_lpn_on_friendship_terminated(uint16_t reason)
{
  (void) reason;
}

/// @} (end addtogroup btmesh_lpn_weak_cb)

/** @} (end addtogroup lpn) */

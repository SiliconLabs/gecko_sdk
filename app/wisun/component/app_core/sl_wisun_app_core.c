/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Core Component
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "sl_component_catalog.h"
#include "sl_status.h"
#include "sl_wisun_app_core.h"
#include "sl_wisun_app_core_util_config.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_status.h"
#include "sl_wisun_api.h"
#include "sl_sleeptimer.h"
#include "wisun_test_certificates.h"
#include "sl_wisun_event_mgr.h"
#include "sl_wisun_trace_util.h"

#if defined(SL_CATALOG_WISUN_APP_SETTING_PRESENT)
#  include "sl_wisun_app_setting.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Release mutex and return
 *****************************************************************************/
#define _return_and_mtx_release() \
  do {                            \
    _app_wisun_mutex_release();   \
    return;                       \
  } while (0)

/**************************************************************************//**
 * @brief Release mutex and return value
 *****************************************************************************/
#define _return_val_and_mtx_release(retval) \
  do {                                      \
    _app_wisun_mutex_release();             \
    return (retval);                        \
  } while (0)

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Acquire application mutex
 * @details Internal mutex lock
 *****************************************************************************/
static inline void _app_wisun_mutex_acquire(void);

/**************************************************************************//**
 * @brief Release application mutex
 * @details Internal mutex release
 *****************************************************************************/
static inline void _app_wisun_mutex_release(void);

/**************************************************************************//**
 * @brief Storing address to the current address
 * @details helper function
 * @param[in] addr_name address name
 * @param[in] addr_type address type
 * @param[in] addr address
 *****************************************************************************/
static inline void _store_address(const char *addr_name,
                                  const sl_wisun_ip_address_type_t addr_type,
                                  sl_wisun_ip_address_t *addr);

/**************************************************************************//**
 * @brief Setting error flag
 * @details It sets the error by a flag
 * @param[in] flag is a flag bit
 *****************************************************************************/
static inline void _app_wisun_core_set_error(app_core_error_state_flag_t flag);

/**************************************************************************//**
 * @brief Storing the current address
 * @details
 *****************************************************************************/
static void _store_current_addresses(void);

/**************************************************************************//**
 * @brief Get Length of certifacete string
 * @details special port of strnlen with different types
 * @param[in] cert Certificate ptr
 * @param[in] max_cert_len certificate buffer max length
 * @return uint16_t length of certificate string
 *****************************************************************************/
static uint16_t _get_cert_str_len(const uint8_t *cert, const uint16_t max_cert_len);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

#if !defined(SL_CATALOG_WISUN_APP_SETTING_PRESENT)
typedef struct app_setting_wisun{
  char network_name[SL_WISUN_NETWORK_NAME_SIZE + 1];
  uint8_t network_size;
  int8_t tx_power;
} app_setting_wisun_t;

static app_setting_wisun_t _app_default_settings = {
  .network_name = "Wi-SUN Network",
  .network_size = SL_WISUN_NETWORK_SIZE_TEST,
  .tx_power = 20U,
};
#endif

/**************************************************************************//**
 * @brief App framework mutex
 *****************************************************************************/
static osMutexId_t _app_wisun_network_mtx;

/**************************************************************************//**
 * @brief App framework mutex control block
 *****************************************************************************/
__ALIGNED(8) static uint8_t _app_wisun_network_mtx_cb[osMutexCbSize] = { 0 };

/**************************************************************************//**
 * @brief App framework mutex attribute
 *****************************************************************************/
static const osMutexAttr_t _app_wisun_network_mtx_attr = {
  .name      = "AppWisunNetworkMutex",
  .attr_bits = osMutexRecursive,
  .cb_mem    = _app_wisun_network_mtx_cb,
  .cb_size   = sizeof(_app_wisun_network_mtx_cb)
};

/**************************************************************************//**
 * @brief Current address storage
 *****************************************************************************/
static current_addr_t _current_addr;

/**************************************************************************//**
 * @brief Timestamp variable for internal usage
 *****************************************************************************/
static uint32_t _timestamp =  0U;

/**************************************************************************//**
 * @brief error flag for errors
 *****************************************************************************/
static app_core_error_state_flag_t _error_flag = CONNECTION_FAILED_ERROR_FLAG_BIT;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* Network update event handler */
void sl_wisun_network_update_event_hnd(sl_wisun_evt_t *evt)
{
  if (evt->evt.network_update.status == SL_STATUS_OK) {
    printf("[Network update]\r\n");
    if (evt->evt.network_update.flags & (1 << SL_WISUN_NETWORK_UPDATE_FLAGS_GLOBAL_IP)) {
      _store_address("GLOBAL", SL_WISUN_IP_ADDRESS_TYPE_GLOBAL, &_current_addr.global);
    }
    if (evt->evt.network_update.flags & (1 << SL_WISUN_NETWORK_UPDATE_FLAGS_PRIMARY_PARENT)) {
      _store_address("PRIM_PARENT", SL_WISUN_IP_ADDRESS_TYPE_PRIMARY_PARENT, &_current_addr.primary_parent);
    }
    if (evt->evt.network_update.flags & (1 << SL_WISUN_NETWORK_UPDATE_FLAGS_SECONDARY_PARENT)) {
      _store_address("SEC_PARENT", SL_WISUN_IP_ADDRESS_TYPE_SECONDARY_PARENT, &_current_addr.secondary_parent);
    }
  }
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Connected event handler */
void sl_wisun_connected_event_hnd(sl_wisun_evt_t *evt)
{
  uint32_t curr_timestamp = 0;
  uint32_t time_ms = 0;
  (void) evt;
  if (evt->evt.connected.status != SL_STATUS_OK) {
    printf("[Connection failed. Status: %lu]", evt->evt.connected.status);
    return;
  }
  // store the current addresses
  _store_current_addresses();
  curr_timestamp = sl_sleeptimer_get_tick_count();
  time_ms = sl_sleeptimer_tick_to_ms(curr_timestamp - _timestamp);
  printf("[%lu s]\r\n", time_ms / 1000U);
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Socket disconnected event handler */
void sl_wisun_disconnected_event_hnd(sl_wisun_evt_t *evt)
{
  _timestamp = sl_sleeptimer_get_tick_count();
  printf("[Disconnected]\r\n");
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Socket connection lost event handler*/
void sl_wisun_connection_lost_event_hnd(sl_wisun_evt_t *evt)
{
  sl_status_t stat;
  char network_name[SL_WISUN_NETWORK_NAME_SIZE + 1] = { 0 };

#if defined(SL_CATALOG_WISUN_APP_SETTING_PRESENT)
  (void)app_wisun_setting_get_network_name(network_name, sizeof(network_name));
  stat = sl_wisun_util_connect((const uint8_t *)network_name);
#else
  stat = sl_wisun_util_connect((const uint8_t *)_app_default_settings.network_name);
#endif

  if (stat == SL_STATUS_OK) {
    printf("[Connection lost, connecting to \"%s\"]\r\n", network_name);
  }
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Error event handler */
void sl_wisun_error_event_hnd(sl_wisun_evt_t *evt)
{
  printf("[Wi-SUN network error occured. Status: %lu\n",
         evt->evt.error.status);
}

/* Join state event handler */
void sl_wisun_join_state_event_hnd(sl_wisun_evt_t *evt)
{
#if HEARTBEAT_ENABLED
  (void) evt;
#else
  const char *join_state_str = NULL;
  // if heartbeat not enabled, print join state
  join_state_str = app_wisun_trace_util_conn_state_to_str(evt->evt.join_state.join_state);
  printf("[Join state: %s (%lu)]\r\n", join_state_str, evt->evt.join_state.join_state);
#endif
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Wisun app core init */
void app_wisun_core_init(void)
{
  // init wisun network mutex
  _app_wisun_network_mtx = osMutexNew(&_app_wisun_network_mtx_attr);
  assert(_app_wisun_network_mtx != NULL);
}

/* App core get error */
bool app_wisun_core_get_error(app_core_error_state_flag_t flag)
{
  return (bool)(_error_flag & (1 << flag));
}

/*Connecting to the wisun network*/
void app_wisun_network_connect(void)
{
  sl_status_t ret = SL_STATUS_FAIL;
  const uint32_t max_cert_str_len = 2048U;
  sl_wisun_join_state_t join_state = SL_WISUN_JOIN_STATE_DISCONNECTED;
  app_setting_wisun_t setting = { 0 };

  _app_wisun_mutex_acquire(); // get mutex

  // gets settings (network name, network size and TX power)
#if defined(SL_CATALOG_WISUN_APP_SETTING_PRESENT)
  ret = app_wisun_setting_get(&setting);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to get settings\r\n");
    _app_wisun_core_set_error(SETTING_ERROR_FLAG_BIT);
    _return_and_mtx_release();
  }
#else
  memcpy(&setting, &_app_default_settings, sizeof(app_setting_wisun_t));
#endif

  // check the join state before the connection progress.
  ret = sl_wisun_get_join_state(&join_state);
  __CHECK_FOR_STATUS(ret);
  if (join_state != SL_WISUN_JOIN_STATE_DISCONNECTED) {
    printf("[Failed: already connecting or connected]\r\n");
    _return_and_mtx_release();
  }

  // sets the network name
  ret = sl_wisun_set_network_size((sl_wisun_network_size_t)setting.network_size);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set network size: %lu]\r\n", ret);
    _app_wisun_core_set_error(SET_NETWORK_SIZE_ERROR_FLAG_BIT);
    _return_and_mtx_release();
  }

  // sets the TX power
  ret = sl_wisun_set_tx_power(setting.tx_power);

  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set TX power: %lu]\r\n", ret);
    _app_wisun_core_set_error(SET_TX_POWER_ERROR_FLAG_BIT);
    _return_and_mtx_release();
  }

  // sets the trusted certificate
  ret = sl_wisun_set_trusted_certificate(SL_WISUN_CERTIFICATE_OPTION_IS_REF,
                                         _get_cert_str_len(WISUN_ROOT_CERTIFICATE, max_cert_str_len) + 1,
                                         WISUN_ROOT_CERTIFICATE);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set the trusted certificate: %lu]\r\n", ret);
    _app_wisun_core_set_error(SET_TRUSTED_CERTIFICATE_ERROR_FLAG_BIT);
    _return_and_mtx_release();
  }

  // sets the device certificate
  ret = sl_wisun_set_device_certificate(SL_WISUN_CERTIFICATE_OPTION_IS_REF | SL_WISUN_CERTIFICATE_OPTION_HAS_KEY,
                                        _get_cert_str_len(WISUN_CLIENT_CERTIFICATE, max_cert_str_len) + 1,
                                        WISUN_CLIENT_CERTIFICATE);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set the device certificate: %lu]\r\n", ret);
    _app_wisun_core_set_error(SET_DEVICE_CERTIFICATE_ERROR_FLAG_BIT);
    _return_and_mtx_release();
  }

  // sets the device private key
  ret = sl_wisun_set_device_private_key(SL_WISUN_PRIVATE_KEY_OPTION_IS_REF,
                                        _get_cert_str_len(WISUN_CLIENT_KEY, max_cert_str_len) + 1,
                                        WISUN_CLIENT_KEY);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set the device private key: %lu]\r\n", ret);
    _app_wisun_core_set_error(SET_DEVICE_PRIVATE_KEY_ERROR_FLAG_BIT);
    _return_and_mtx_release();
  }

  // connects to the network using the network name
  ret = sl_wisun_util_connect((const uint8_t *)setting.network_name);
  if (ret == SL_STATUS_OK) {
    _timestamp = sl_sleeptimer_get_tick_count();
    printf("\r\n[Connecting to \"%s\"]\r\n", setting.network_name);
  } else {
    _app_wisun_core_set_error(CONNECTION_FAILED_ERROR_FLAG_BIT);
    printf("\r\n[Connection failed: %lu]\r\n", ret);
  }
  _app_wisun_mutex_release();
}

void app_wisun_get_current_addresses(current_addr_t * const dest_addresses)
{
  _app_wisun_mutex_acquire();
  memcpy(&dest_addresses->global, &_current_addr.global, sizeof(sl_wisun_ip_address_t));
  memcpy(&dest_addresses->border_router, &_current_addr.border_router, sizeof(sl_wisun_ip_address_t));
  memcpy(&dest_addresses->link_local, &_current_addr.link_local, sizeof(sl_wisun_ip_address_t));
  memcpy(&dest_addresses->primary_parent, &_current_addr.primary_parent, sizeof(sl_wisun_ip_address_t));
  memcpy(&dest_addresses->secondary_parent, &_current_addr.secondary_parent, sizeof(sl_wisun_ip_address_t));
  _app_wisun_mutex_release();
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

/* Mutex acquire */
static inline void _app_wisun_mutex_acquire(void)
{
  assert(osMutexAcquire(_app_wisun_network_mtx, osWaitForever) == osOK);
}

/* Mutex release */
static inline void _app_wisun_mutex_release(void)
{
  assert(osMutexRelease(_app_wisun_network_mtx) == osOK);
}

/* Storing address */
static inline void _store_address(const char *addr_name,
                                  const sl_wisun_ip_address_type_t addr_type,
                                  sl_wisun_ip_address_t *addr)
{
  sl_status_t stat = SL_STATUS_FAIL;
  stat = sl_wisun_get_ip_address(addr_type, addr);
  if (addr_type != SL_WISUN_IP_ADDRESS_TYPE_PRIMARY_PARENT
      && addr_type != SL_WISUN_IP_ADDRESS_TYPE_SECONDARY_PARENT) {
    if (stat != SL_STATUS_OK) {
      printf("[Getting '%s' address failed!]\r\n", addr_name);
    } else {
      printf("[%-14s: %s]\r\n", addr_name, app_wisun_trace_util_get_ip_address_str(addr));
    }
  }
}

/* Setting error */
static inline void _app_wisun_core_set_error(app_core_error_state_flag_t flag)
{
  _error_flag |= (1 << flag);
}

/* Storing current addresses */
static void _store_current_addresses(void)
{
  memset(&_current_addr, 0, sizeof(current_addr_t));
  printf("\r\nAddresses:\r\n");
  _store_address("GLOBAL", SL_WISUN_IP_ADDRESS_TYPE_GLOBAL, &_current_addr.global);
  _store_address("LINK_LOCAL", SL_WISUN_IP_ADDRESS_TYPE_LINK_LOCAL, &_current_addr.link_local);
  _store_address("BORDER_ROUTER", SL_WISUN_IP_ADDRESS_TYPE_BORDER_ROUTER, &_current_addr.border_router);
  _store_address("PRIMARY_PARENT", SL_WISUN_IP_ADDRESS_TYPE_PRIMARY_PARENT, &_current_addr.primary_parent);
  _store_address("SECONDARY_PARENT", SL_WISUN_IP_ADDRESS_TYPE_SECONDARY_PARENT, &_current_addr.secondary_parent);
}

/* Get certificate length */
static uint16_t _get_cert_str_len(const uint8_t *cert, const uint16_t max_cert_len)
{
  uint16_t n = 0;
  if (cert == NULL) {
    return 0U;
  }
  for (n = 0; n < max_cert_len && *cert; n++, cert++) {
    ;
  }
  return n;
}

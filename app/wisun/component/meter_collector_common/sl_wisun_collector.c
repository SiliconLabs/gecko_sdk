/***************************************************************************//**
 * @file
 * @brief
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

#include <string.h>
#include <assert.h>
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_collector.h"
#include "sl_wisun_meter_collector_config.h"
#include "sl_wisun_collector_config.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_sleeptimer.h"
#include "sl_component_catalog.h"
#include "sl_wisun_trace_util.h"
#include "sli_wisun_meter_collector.h"
#include "sl_mempool.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Meter response timeout factor
#define SL_WISUN_COLLECTOR_TIMEOUT_FACTOR                               4U

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Create the socket shared by the sender and recevier threads
 *****************************************************************************/
static void _create_common_socket(void);

/**************************************************************************//**
 * @brief Collector send request
 * @details Handler function
 * @param[in] sockid The socket used for sending or SOCKET_INVALID_ID for ad-hoc socket creation
 * @param[in] meter Meter entry
 * @param[in] req The request to send
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _collector_send_request(const int32_t sockid,
                                           sl_wisun_meter_entry_t *meter,
                                           sl_wisun_meter_request_t *req);

/**************************************************************************//**
 * @brief Collector receive response
 * @details Handler function
 * @param[in] sockid The socket used for receiving
 * @return sl_wisun_meter_entry_t*
 *****************************************************************************/
static sl_wisun_meter_entry_t * _collector_recv_response(int32_t sockid);

/**************************************************************************//**
 * @brief Collector receiver thread
 * @details Receiver thread handler function
 * @param[in] args Arguments
 *****************************************************************************/
static void _collector_recv_thread_fnc(void * args);

/**************************************************************************//**
 * @brief Collector get meter entry by address
 * @details Handler function
 * @param remote_addr Remote address
 * @return sl_wisun_meter_entry_t* Meter entry or NULL on error
 *****************************************************************************/
static sl_wisun_meter_entry_t *_collector_get_meter_entry_by_address(const wisun_addr_t * const remote_addr);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Mempool to store registered meters
static sl_mempool_t _meters_mempool = { 0 };

/// Meter internal storage
static sl_wisun_meter_entry_t _meters[SL_WISUN_COLLECTOR_MAX_REG_METER] = { 0 };

static sl_wisun_meter_request_t _measurement_req = { 0 };

/// Collector internal handler
static sl_wisun_collector_hnd_t _collector_hnd = { 0 };

/// Collector receiver task attributes
static const osThreadAttr_t _collector_recv_task_attr = {
  .name        = "CollectorRecvTask",
  .attr_bits   = osThreadDetached,
  .cb_mem      = NULL,
  .cb_size     = 0,
  .stack_mem   = NULL,
  .stack_size  = app_stack_size_word_to_byte(SL_WISUN_COLLECTOR_STACK_SIZE_WORD),
  .priority    = osPriorityBelowNormal,
  .tz_module   = 0
};

/// Collector receiver thread ID
static osThreadId_t _collector_recv_thr_id = NULL;

/// Socket shared among the sender and receiver threads
static int32_t _common_socket = SOCKET_INVALID_ID;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

int32_t sl_wisun_collector_get_shared_socket(void)
{
  return(_common_socket);
}

void sl_wisun_collector_init()
{
  sl_wisun_meter_request_t req = { 0 };

  sl_wisun_collector_init_common_resources();

  // init collector-meter token
  sl_wisun_mc_init_token(SL_WISUN_METER_COLLECTOR_TOKEN);

  // Set measurement request
  req.buff = (uint8_t *)SL_WISUN_METER_COLLECTOR_TOKEN;
  req.length = sl_wisun_mc_get_token_size();
  sl_wisun_collector_set_measurement_request(&req);
}

void sl_wisun_collector_inherit_common_hnd(sl_wisun_collector_hnd_t *hnd)
{
  // do not overwrite resource_hnd and get_meter
  _collector_hnd.send = hnd->send;
  _collector_hnd.recv = hnd->recv;
  _collector_hnd.timeout = hnd->timeout;
  hnd->get_meter = _collector_hnd.get_meter;
}

void sl_wisun_collector_init_common_resources(void)
{
  // Create mempool for meters
  sl_status_t stat = SL_STATUS_FAIL;
  stat = sl_mempool_create(&_meters_mempool,
                           SL_WISUN_COLLECTOR_MAX_REG_METER,
                           sizeof(sl_wisun_meter_entry_t),
                           _meters,
                           sizeof(_meters));
  assert(stat == SL_STATUS_OK);

  // init collector handler
  sl_wisun_collector_set_handler(&_collector_hnd,
                                 _collector_recv_response,
                                 _collector_send_request,
                                 NULL,
                                 _collector_get_meter_entry_by_address);
  sl_wisun_collector_init_hnd(&_collector_hnd);

  _collector_recv_thr_id = osThreadNew(_collector_recv_thread_fnc, NULL, &_collector_recv_task_attr);
  assert(_collector_recv_thr_id != NULL);
}

/* Register meter */
sl_status_t sl_wisun_collector_register_meter(const wisun_addr_t *meter_addr)
{
  sl_wisun_meter_entry_t *tmp_meter_entry = NULL;
  sl_mempool_block_hnd_t *block = NULL;

  sl_wisun_mc_mutex_acquire(_collector_hnd);

  if (meter_addr == NULL) {
    sl_wisun_mc_release_mtx_and_return_val(_collector_hnd, SL_STATUS_FAIL);
  }

  block = _meters_mempool.blocks;

  // Check if meter is already registered
  while (block != NULL) {
    tmp_meter_entry = (sl_wisun_meter_entry_t *) block->start_addr;
    if (sl_wisun_collector_compare_address(&tmp_meter_entry->addr, meter_addr)) {
      sl_wisun_mc_release_mtx_and_return_val(_collector_hnd, SL_STATUS_ALREADY_EXISTS);
    }
    block = block->next;
  }

  tmp_meter_entry = sl_mempool_alloc(&_meters_mempool);
  if (tmp_meter_entry == NULL) {
    sl_wisun_mc_release_mtx_and_return_val(_collector_hnd, SL_STATUS_FAIL);
  }

  tmp_meter_entry->schedule_tick_counter = 0U;
  tmp_meter_entry->schedule = SL_WISUN_METER_DEFAULT_PERIOD_MS;
  memcpy(&tmp_meter_entry->addr, meter_addr, sizeof(wisun_addr_t));

  sl_wisun_mc_mutex_release(_collector_hnd);

  return SL_STATUS_OK;
}

/* Remove meter */
sl_status_t sl_wisun_collector_remove_meter(const wisun_addr_t *meter_addr)
{
  sl_wisun_meter_entry_t *tmp_meter_entry = NULL;
  sl_mempool_block_hnd_t *block = NULL;

  sl_wisun_mc_mutex_acquire(_collector_hnd);

  if (meter_addr == NULL) {
    sl_wisun_mc_release_mtx_and_return_val(_collector_hnd, SL_STATUS_FAIL);
  }

  block = _meters_mempool.blocks;

  while (block != NULL) {
    tmp_meter_entry = (sl_wisun_meter_entry_t *) block->start_addr;
    if (sl_wisun_collector_compare_address(&tmp_meter_entry->addr, meter_addr)) {
      sl_mempool_free(&_meters_mempool, tmp_meter_entry);
      sl_wisun_mc_release_mtx_and_return_val(_collector_hnd, SL_STATUS_OK);
    }
    block = block->next;
  }

  sl_wisun_mc_mutex_release(_collector_hnd);

  return SL_STATUS_FAIL;
}

/* compare addresses */
bool sl_wisun_collector_compare_address(const wisun_addr_t *addr1, const wisun_addr_t *addr2)
{
  uint8_t *p1 = (uint8_t *)&addr1->sin6_addr;
  uint8_t *p2 = (uint8_t *)&addr2->sin6_addr;
  for (uint8_t i = 0; i < sizeof(in6_addr_t); ++i) {
    if (p1[i] != p2[i]) {
      return false;
    }
  }
  return true;
}

/* Measurement loop */
void sl_wisun_collector_measurement_request_loop(void)
{
  sl_wisun_meter_entry_t *tmp_meter_entry = NULL;
  sl_mempool_block_hnd_t *block = NULL;
  const char *ip_addr = NULL;
  sl_status_t res = SL_STATUS_OK;

  sl_wisun_mc_mutex_acquire(_collector_hnd);
  if (_collector_hnd.send == NULL) {
    sl_wisun_mc_release_mtx_and_return(_collector_hnd);
  }
  block = _meters_mempool.blocks;

  while (block != NULL) {
    tmp_meter_entry = (sl_wisun_meter_entry_t *) block->start_addr;
    // send request by schedule
    if (tmp_meter_entry->schedule_tick_counter == tmp_meter_entry->schedule) {
      res = _collector_hnd.send(_common_socket, tmp_meter_entry, &_measurement_req);
      if (res != SL_STATUS_OK) {
        ip_addr = app_wisun_trace_util_get_ip_str(&tmp_meter_entry->addr.sin6_addr);
        printf("[Collector cannot send measurement request to the meter: %s]\n", ip_addr);
        app_wisun_trace_util_destroy_ip_str(ip_addr);
      }
      tmp_meter_entry->req_sent_timestamp = sl_sleeptimer_get_tick_count();
      tmp_meter_entry->schedule_tick_counter = 0U;
    }
    tmp_meter_entry->schedule_tick_counter++;

    block = block->next;
  }
  sl_wisun_mc_mutex_release(_collector_hnd);
}

void sl_wisun_collector_set_measurement_request(const sl_wisun_meter_request_t * const req)
{
  sl_wisun_mc_mutex_acquire(_collector_hnd);
  memcpy(&_measurement_req, req, sizeof(_measurement_req));
  sl_wisun_mc_mutex_release(_collector_hnd);
}
// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static void _create_common_socket(void)
{
  int32_t res                   = SOCKET_INVALID_ID;
  wisun_addr_t collector_addr   = { 0 };

  _common_socket = socket(AF_WISUN, SOCK_DGRAM, IPPROTO_UDP);
  assert(_common_socket != SOCKET_INVALID_ID);

  collector_addr.sin6_family = AF_WISUN;
  collector_addr.sin6_addr = in6addr_any;
  collector_addr.sin6_port = htons(SL_WISUN_COLLECTOR_PORT);

  res = bind(_common_socket, (const struct sockaddr *) &collector_addr,
             sizeof(struct sockaddr_in6));
  assert(res != SOCKET_RETVAL_ERROR);
}

static sl_status_t _collector_send_request(const int32_t sockid,
                                           sl_wisun_meter_entry_t *meter,
                                           sl_wisun_meter_request_t *req)
{
#if !defined(SL_CATALOG_WISUN_COAP_PRESENT)
  int32_t res = SOCKET_INVALID_ID;
  socklen_t len = 0;
  sl_status_t retval = SL_STATUS_OK;

  if (sockid == SOCKET_INVALID_ID) {
    return SL_STATUS_FAIL;
  }

  len = sizeof(meter->addr);

  res = sendto(sockid,
               req->buff,
               req->length, 0,
               (const struct sockaddr *)&meter->addr,
               len);

  if (res == SOCKET_RETVAL_ERROR) {
    retval = SL_STATUS_FAIL;
  }

  return retval;
#else
  (void) sockid;
  (void) meter;
  (void) req;
  return false;
#endif
}

static sl_wisun_meter_entry_t * _collector_recv_response(int32_t sockid)
{
#if !defined(SL_CATALOG_WISUN_COAP_PRESENT)
  sl_wisun_meter_packet_packed_t packet = { 0 };
  wisun_addr_t remote_addr              = { 0 };
  const char *ip_addr                   = NULL;
  sl_wisun_meter_entry_t *meter         = NULL;
  socklen_t len                         = 0;
  int32_t res                           = SOCKET_INVALID_ID;

  len = sizeof(remote_addr);
  memset(&packet, 0, sizeof(packet));
  res = recvfrom(sockid, &packet, sizeof(packet), 0,
                 (struct sockaddr *)&remote_addr, &len);
  if (res == sizeof(packet)) {
    sl_wisun_mc_mutex_acquire(_collector_hnd);
    meter = _collector_hnd.get_meter(&remote_addr);
    sl_wisun_mc_mutex_release(_collector_hnd);
    if (meter != NULL) {
      ip_addr = app_wisun_trace_util_get_ip_str(&remote_addr.sin6_addr);
      meter->schedule = packet.schedule;
      printf("['%s' meter scheduled: %lu ms]\n", ip_addr, meter->schedule);
      sl_wisun_mc_print_mesurement(ip_addr, &packet, true);
      app_wisun_trace_util_destroy_ip_str(ip_addr);
      return meter;
    } else {
      printf("[Unknown remote message received!]\n");
    }
  }
  return NULL;
#else
  (void) sockid;
  return NULL;
#endif
}

static void _collector_recv_thread_fnc(void * args)
{
  sl_wisun_meter_entry_t *meter = NULL;
  uint32_t response_time_ms     = 0;

  (void) args;

  _create_common_socket();

  SL_WISUN_THREAD_LOOP {
    if (!app_wisun_network_is_connected()) {
      msleep(1000);
      continue;
    }

    meter = NULL;
    if (_collector_hnd.recv != NULL) {
      meter = _collector_hnd.recv(_common_socket);
    }
    if (meter != NULL) {
      meter->resp_recv_timestamp = sl_sleeptimer_get_tick_count();
      response_time_ms = sl_sleeptimer_tick_to_ms(meter->resp_recv_timestamp
                                                  - meter->req_sent_timestamp);
      printf("[Response time: %ldms]\n", response_time_ms);
      if (response_time_ms > (meter->schedule * SL_WISUN_COLLECTOR_TIMEOUT_FACTOR)) {
        _collector_hnd.timeout(meter);
      }
    }
    msleep(1);
  }
}

static sl_wisun_meter_entry_t *_collector_get_meter_entry_by_address(const wisun_addr_t * const remote_addr)
{
  sl_wisun_meter_entry_t *tmp_meter_entry = NULL;
  sl_mempool_block_hnd_t *block = NULL;

  if (remote_addr == NULL) {
    return NULL;
  }

  block = _meters_mempool.blocks;

  while (block != NULL) {
    tmp_meter_entry = (sl_wisun_meter_entry_t *) block->start_addr;
    if (sl_wisun_collector_compare_address(&tmp_meter_entry->addr, remote_addr)) {
      return tmp_meter_entry;
    }
    block = block->next;
  }

  return NULL;
}

sl_status_t sl_wisun_collector_get_meter(const wisun_addr_t *meter_addr,
                                         sl_wisun_meter_entry_t * const dest_meter)
{
  sl_wisun_meter_entry_t *meter = NULL;
  sl_status_t retval = SL_STATUS_FAIL;

  sl_wisun_mc_mutex_acquire(_collector_hnd);

  meter = _collector_get_meter_entry_by_address(meter_addr);

  if (meter != NULL) {
    memcpy(dest_meter, meter, sizeof(sl_wisun_meter_entry_t));
    retval = SL_STATUS_OK;
  }

  sl_wisun_mc_mutex_release(_collector_hnd);

  return retval;
}

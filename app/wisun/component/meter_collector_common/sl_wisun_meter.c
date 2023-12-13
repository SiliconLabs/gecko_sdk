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
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "cmsis_os2.h"
#include "em_device.h"
#include "sl_mempool.h"
#include "sl_component_catalog.h"
#include "sl_sleeptimer.h"
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_event_mgr.h"
#include "sl_wisun_meter.h"
#include "sl_wisun_meter_config.h"
#include "sl_wisun_trace_util.h"
#include "sli_wisun_meter_collector.h"
#include "socket/socket.h"
#if defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  #include "sl_wisun_rht_measurement.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// Size of the meter buffers in bytes
#define SL_WISUN_METER_BUFFER_LEN                                       512U
/// Wake up event flag mask
#define SL_WISUN_LFN_WAKE_UP_EVT_MSK                                    0x0001U

/// Macro for dispatching the thread if the given result is not SL_STATUS_OK
#define sl_wisun_check_result_and_dispatch_if_nok(__res, __socket, __storage) \
  if (__res != SL_STATUS_OK) {                                                \
    sl_wisun_meter_error_handler(__res, __socket, __storage);                 \
    app_wisun_dispatch_thread();                                              \
    continue;                                                                 \
  }

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

#if SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
/**************************************************************************//**
 * @brief LFN Wake up meter event handler
 * @details Custom callback implementation.
 *          It sets an OS status flag to notify meter task
 * @param[in] evt Event descriptor
 *****************************************************************************/
static void _wisun_lfn_wake_up_meter_hnd(sl_wisun_evt_t *evt);

/**************************************************************************//**
 * @brief Meter parse
 * @details Handler function
 * @param[in] raw Received data buffer
 * @param[in] packet_data_len Length of the received packet
 * @param[out] req Received request type
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _meter_parse_request(const void * const raw,
                                        int32_t packet_data_len,
                                        sl_wisun_request_type_t * const req);

/**************************************************************************//**
 * @brief Meter build
 * @details Handler function
 * @param[in] req Request type
 * @param[in] packets Pointer to the packet buffer
 * @param[in] nr_of_packets Number of packets to build
 * @param[out] buf Buffer to store packed data
 * @param[out] len Length of the buffer
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _meter_build_packets(const sl_wisun_request_type_t req,
                                        const sl_wisun_meter_packet_t * const packets,
                                        const uint8_t nr_of_packets,
                                        uint8_t * const buf,
                                        uint32_t * const len);

/***************************************************************************//**
 * @brief Meter measurement brancing
 * @details Handler function
 * @param[in] collector_mempool Pointer to the collectors mempool
 * @param[in] schedule Schedule time for the measurements
 * @return true If measurement is necessary
 * @return false If measurement is not necessary
 ******************************************************************************/
static bool _meter_is_measurement_necessary(sl_mempool_t *collector_mempool,
                                            const uint32_t schedule);

/***************************************************************************//**
 * @brief Meter sending brancing
 * @details Handler function
 * @param[in] storage Pointer to the measurement packet storage
 * @param[in] collector Pointer to a collector entry
 * @param[out] nr_of_packets Number of packets to send
 * @return true If sending is necessary
 * @return false If sending is not necessary
 ******************************************************************************/
static bool _meter_is_sending_necessary(sl_wisun_meter_packet_storage_t *storage,
                                        sl_wisun_collector_entry_t *collector,
                                        uint8_t *nr_of_packets);

/**************************************************************************//**
 * @brief Create the socket shared by the sender and receiver threads
 *****************************************************************************/
static void _create_common_socket(void);

/**************************************************************************//**
 * @brief Measure parameters and send to the Collector (client)
 * @details Generate packet id, measure temperature, humidity and light
 * @param[in] collector_addr Collector address structure
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On error
 *****************************************************************************/
static sl_status_t _sl_wisun_meter_meas_params_and_send(const sockaddr_in6_t * const collector_addr);

/**************************************************************************//**
 * @brief Handle resource discovery request
 * @details Build and send a response packet
 * @param[in] collector_addr Collector address structure
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On error
 *****************************************************************************/
static sl_status_t _sl_wisun_meter_handle_rd_request(const sockaddr_in6_t * const collector_addr);

/**************************************************************************//**
 * @brief Meter send response
 * @details Handler function
 * @param[in] sockid The socket to use for transmission
 * @param[in] buf Buffer that contains the data for the transmission
 * @param[in] coll_addr Collector address
 * @param[in] response_len Length of the buffer
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _sl_wisun_meter_send_response(const int32_t sockid,
                                                 const uint8_t *buf,
                                                 const sockaddr_in6_t * const coll_addr,
                                                 const uint32_t response_len);

/**************************************************************************//**
 * @brief Meter receive request
 * @details Handler function
 * @param[in] sockid The socket used for receiving
 * @param[out] remote_addr The address of the requester
 * @param[out] packet_data_len Size of the received packet
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _sl_wisun_meter_recv_request(const int32_t sockid,
                                                sockaddr_in6_t *remote_addr,
                                                int32_t * const packet_data_len);

/**************************************************************************//**
 * @brief Meter handle request
 * @details Make actions according to the received request
 * @param[in] req Request type
 * @param[in] remote_addr Address of the requester
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _sl_wisun_meter_handle_request(const sl_wisun_request_type_t req,
                                                  const sockaddr_in6_t * const remote_addr);

/**************************************************************************//**
 * @brief Meter measure params
 * @details Get measurement data from the attached sensors
 * @param[out] packet Pointer to the packet to be used for storing measured data
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static void _sl_wisun_meter_meas_params(sl_wisun_meter_packet_t *packet);

/**************************************************************************//**
 * @brief Meter store params
 * @details Stores a measurement packet to the internal packet storage
 * @param[in] packet Pointer to the packet to be stored
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _sl_wisun_meter_store_packet(const sl_wisun_meter_packet_t * const packet);

/**************************************************************************//**
 * @brief Meter measurement cycle
 * @details Measure params
 * @param[in] schedule Schedule time for measurements
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On error
 *****************************************************************************/
static sl_status_t _sl_wisun_meter_measurement_cycle(const uint32_t schedule);

/**************************************************************************//**
 * @brief Meter sending cycle
 * @details Send packets to the collectors if necessary
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _sl_wisun_meter_sending_cycle(void);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Internal meter handler
static sl_wisun_meter_hnd_t _meter_hnd                  = { 0 };

/// Internal buffer for measurement packets
static sl_wisun_meter_packet_t _meas_packet_buffer[SL_WISUN_METER_MEASUREMENT_BUFFER_SIZE] = { 0 };

/// Mempool to store registered collectors
static sl_mempool_t _collectors_mempool                 = { 0 };

/// Registered collector internal storage
static sl_wisun_collector_entry_t _reg_collectors[SL_WISUN_METER_MAX_REG_COLLECTOR] = { 0 };

/// Socket shared among the sender and receiver threads
static int32_t _common_socket                           = SOCKET_INVALID_ID;

/// Internal storage for raw rx data
static uint8_t _rx_buf[SL_WISUN_METER_BUFFER_LEN]       = { 0U };

/// Internal storage for tx data
static uint8_t _tx_buf[SL_WISUN_METER_BUFFER_LEN]       = { 0U };

/// Length of the tx response in bytes
static uint32_t _response_len                           = 0U;

/// Internal storage for measurement packets
static sl_wisun_meter_packet_storage_t _packet_storage  = {
  .buffer = _meas_packet_buffer,
  .buf_size = SL_WISUN_METER_MEASUREMENT_BUFFER_SIZE,
  .stored = 0U
};

/// LFN wake up event flag
static osEventFlagsId_t _lfn_wake_up_evt = NULL;

/// LFN wake up event flag attributes
static const osEventFlagsAttr_t _evt_attr = {
  .name      = "LfnWakeUpEvt",
  .attr_bits = 0,
  .cb_mem    = NULL,
  .cb_size   = 0
};
#endif

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* Generate packet id */
SL_WEAK void sl_wisun_meter_gen_packet_id(sl_wisun_meter_packet_t *packet)
{
  static uint16_t id = 0U;
  packet->id = id++;
}

/* Measure temperature */
SL_WEAK void sl_wisun_meter_get_temperature(sl_wisun_meter_packet_t *packet)
{
#if !defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  /* Dummy temperature values table */
  static const uint16_t dummy_temp[] = { 32500U, 31200U, 29300U, 30000U, 28100U };
  static const uint16_t dummy_temp_size = sizeof(dummy_temp) / sizeof(uint16_t);
  packet->temperature = dummy_temp[packet->id % dummy_temp_size];
#else
  sl_status_t stat = SL_STATUS_FAIL;
  uint32_t dummy = 0U;

  stat = sl_wisun_rht_get(&dummy, &packet->temperature);
  if (stat != SL_STATUS_OK) {
    printf("[Si70xx Temperature measurement error]\n");
  }
#endif
}

/* Measure relative humidity */
SL_WEAK void sl_wisun_meter_get_humidity(sl_wisun_meter_packet_t *packet)
{
#if !defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  /* Dummy humidity values table */
  static const uint16_t dummy_hum[] = { 40500U, 41200U, 39300U, 38000U, 37100U };
  static const uint16_t dummy_hum_size = sizeof(dummy_hum) / sizeof(uint16_t);
  packet->humidity = dummy_hum[packet->id % dummy_hum_size];
#else
  sl_status_t stat = SL_STATUS_FAIL;
  int32_t dummy = 0U;

  stat = sl_wisun_rht_get(&packet->humidity, &dummy);

  if (stat != SL_STATUS_OK) {
    printf("[Si70xx Humidity measurement error]\n");
  }
#endif
}

/* Measure light */
SL_WEAK void sl_wisun_meter_get_light(sl_wisun_meter_packet_t *packet)
{
  /* Dummy lux table */
  static const uint16_t dummy_lux[]    = { 512U, 480U, 600U, 580U, 555U };
  static const uint16_t dummy_lux_size = sizeof(dummy_lux) / sizeof(uint16_t);
  static uint16_t cnt                  = 0U;

  if (cnt == dummy_lux_size) {
    cnt = 0U;
  }

  packet->light = dummy_lux[cnt++];
}

#if SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
void sl_wisun_meter_init(void)
{
  // Init meter-collector common component
#if !defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  sl_wisun_meter_set_initializer(&_meter_hnd, NULL);
#else
  sl_wisun_meter_set_initializer(&_meter_hnd, sl_wisun_rht_init);
#endif
  sl_wisun_meter_init_common_resources(_meter_parse_request,
                                       _meter_build_packets);

  // Register LFN wake up event callback for meter
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_LFN_WAKE_UP_IND_ID,
                                        _wisun_lfn_wake_up_meter_hnd);
  // Create lfn wake up event flag
#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
  _lfn_wake_up_evt = osEventFlagsNew(&_evt_attr);
  assert(_lfn_wake_up_evt != NULL);
#endif
}

void sl_wisun_meter_init_common_resources(sl_wisun_meter_parse_t parser,
                                          sl_wisun_meter_build_hnd_t build)
{
  sl_status_t stat = SL_STATUS_FAIL;

  // Create mempool for registered collectors
  stat = sl_mempool_create(&_collectors_mempool,
                           SL_WISUN_METER_MAX_REG_COLLECTOR,
                           sizeof(sl_wisun_collector_entry_t),
                           _reg_collectors,
                           sizeof(_reg_collectors));
  assert(stat == SL_STATUS_OK);

  sl_wisun_meter_set_handler(&_meter_hnd,
                             parser,
                             build,
                             _meter_is_measurement_necessary,
                             _meter_is_sending_necessary);
  // Init meter handler
  sl_wisun_meter_init_hnd(&_meter_hnd);
}

/* Register collector */
sl_status_t sl_wisun_meter_register_collector(const sockaddr_in6_t * const coll_addr)
{
  const sl_mempool_block_hnd_t *block         = NULL;
  sl_wisun_collector_entry_t *tmp_coll_entry  = NULL;
  bool res                                    = false;
  const char *ip_addr                         = NULL;

  sl_wisun_mc_mutex_acquire(_meter_hnd);

  if (coll_addr == NULL) {
    sl_wisun_mc_release_mtx_and_return_val(_meter_hnd, SL_STATUS_FAIL);
  }

  block = _collectors_mempool.blocks;

  // Check if collector is already registered
  while (block != NULL) {
    tmp_coll_entry = (sl_wisun_collector_entry_t *) block->start_addr;
    if (sl_wisun_mc_compare_address(&tmp_coll_entry->addr, coll_addr)) {
      sl_wisun_mc_release_mtx_and_return_val(_meter_hnd, SL_STATUS_ALREADY_EXISTS);
    }
    block = block->next;
  }

  tmp_coll_entry = sl_mempool_alloc(&_collectors_mempool);
  if (tmp_coll_entry == NULL) {
    sl_wisun_mc_release_mtx_and_return_val(_meter_hnd, SL_STATUS_FAIL);
  }
  memcpy(&tmp_coll_entry->addr, coll_addr, sizeof(sockaddr_in6_t));

  // Send a response to the registration request to the collector
  res = _sl_wisun_meter_meas_params_and_send(coll_addr);
  if (res != SL_STATUS_OK) {
    ip_addr = app_wisun_trace_util_get_ip_str(&coll_addr->sin6_addr);
    printf("[Meter cannot send measurement packet to the collector: %s]\n",
           ip_addr);
    app_wisun_trace_util_destroy_ip_str(ip_addr);
    sl_wisun_mc_release_mtx_and_return_val(_meter_hnd, SL_STATUS_FAIL);
  }

  sl_wisun_mc_mutex_release(_meter_hnd);
  return SL_STATUS_OK;
}

/* Remove collector */
sl_status_t sl_wisun_meter_remove_collector(const sockaddr_in6_t * const coll_addr)
{
  const sl_mempool_block_hnd_t *block               = NULL;
  const sl_wisun_collector_entry_t *tmp_coll_entry  = NULL;
  const char *ip_addr                               = NULL;
  bool is_collector_registered                      = false;

  sl_wisun_mc_mutex_acquire(_meter_hnd);

  if (coll_addr == NULL) {
    sl_wisun_mc_release_mtx_and_return_val(_meter_hnd, SL_STATUS_FAIL);
  }

  block = _collectors_mempool.blocks;

  while (block != NULL) {
    tmp_coll_entry = (sl_wisun_collector_entry_t *) block->start_addr;
    if (sl_wisun_mc_compare_address(&tmp_coll_entry->addr, coll_addr)) {
      is_collector_registered = true;
      break;
    }
    block = block->next;
  }
  if (tmp_coll_entry == NULL || is_collector_registered == false) {
    sl_wisun_mc_release_mtx_and_return_val(_meter_hnd, SL_STATUS_FAIL);
  }

  ip_addr = app_wisun_trace_util_get_ip_str(&coll_addr->sin6_addr);
  printf("[Collector has been removed: %s]\n", ip_addr);
  app_wisun_trace_util_destroy_ip_str(ip_addr);
  sl_mempool_free(&_collectors_mempool, tmp_coll_entry);

  sl_wisun_mc_mutex_release(_meter_hnd);

  return SL_STATUS_OK;
}

/* Error handler */
SL_WEAK void sl_wisun_meter_error_handler(const sl_status_t status,
                                          const int32_t socket_id,
                                          sl_wisun_meter_packet_storage_t *storage)
{
  (void) status;
  (void) socket_id;
  (void) storage;
}

void sl_wisun_meter_process(void)
{
  uint32_t schedule                 = 0U;
  sl_status_t res                   = SL_STATUS_FAIL;
  static sockaddr_in6_t remote_addr = { 0 };
  int32_t packet_data_len           = 0;
  sl_wisun_request_type_t req       = SL_WISUN_MC_REQ_UNKNOWN;

#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
  const sl_wisun_lfn_params_t *lfn_params = NULL;
  sl_wisun_device_type_t device_type      = SL_WISUN_ROUTER;
#endif

  // Init reference token
  sl_wisun_mc_init_token(SL_WISUN_METER_COLLECTOR_TOKEN);

  // Get the device schedule
#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
  device_type = app_wisun_get_device_type();
  lfn_params = app_wisun_get_lfn_params();
  if (lfn_params != NULL) {
    schedule = lfn_params->data_layer.unicast_interval_ms;
  } else {
    schedule = SL_WISUN_METER_SCHEDULE_TIME;
  }
#else
  schedule = SL_WISUN_METER_SCHEDULE_TIME;
#endif

  _create_common_socket();

  // Receiver loop
  SL_WISUN_THREAD_LOOP {
#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
    if (device_type == SL_WISUN_LFN) {
      osEventFlagsWait(_lfn_wake_up_evt,
                       SL_WISUN_LFN_WAKE_UP_EVT_MSK,
                       osFlagsWaitAny,
                       osWaitForever);
    }
#endif
    // Read data from socket buffer
    res = _sl_wisun_meter_recv_request(_common_socket, &remote_addr, &packet_data_len);

    if (res == SL_STATUS_OK) {
      // Parse received raw data
      res = _meter_hnd.parse(_rx_buf, packet_data_len, &req);
      sl_wisun_check_result_and_dispatch_if_nok(res, _common_socket, &_packet_storage);

      // Handle received request
      res = _sl_wisun_meter_handle_request(req, &remote_addr);
      sl_wisun_check_result_and_dispatch_if_nok(res, _common_socket, &_packet_storage);
    }

    // Measure parameters if necessary
    res = _sl_wisun_meter_measurement_cycle(schedule);
    sl_wisun_check_result_and_dispatch_if_nok(res, _common_socket, &_packet_storage);

    // Send measurement data to registered collectors if necessary
    res = _sl_wisun_meter_sending_cycle();
    sl_wisun_check_result_and_dispatch_if_nok(res, _common_socket, &_packet_storage);

#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
    // dispatch thread
    app_wisun_dispatch_thread();
#endif
  }
}
#endif

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

#if SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
static void _wisun_lfn_wake_up_meter_hnd(sl_wisun_evt_t *evt)
{
  (void) evt;
  (void) osEventFlagsSet(_lfn_wake_up_evt, SL_WISUN_LFN_WAKE_UP_EVT_MSK);
}

static sl_status_t _meter_parse_request(const void * const raw,
                                        int32_t packet_data_len,
                                        sl_wisun_request_type_t * const req)
{
#if !defined(SL_CATALOG_WISUN_COAP_PRESENT)
  const char *raw_ptr = NULL;
  uint16_t maxlen     = SL_WISUN_METER_BUFFER_LEN;
  const char *token   = NULL;
  uint16_t token_len  = 0U;
  uint16_t i          = 0U;

  if ((raw == NULL) || (packet_data_len == 0) || (req == NULL)) {
    return SL_STATUS_FAIL;
  }

  raw_ptr = (char *)raw;

  // Parsing request
  if (strncmp(raw_ptr, SL_WISUN_METER_REQUEST_TYPE_STR_REGISTER, maxlen) == 0) {
    *req = SL_WISUN_MC_REQ_REGISTER;
  } else if (strncmp(raw_ptr, SL_WISUN_METER_REQUEST_TYPE_STR_ASYNC, maxlen) == 0) {
    *req = SL_WISUN_MC_REQ_ASYNC;
  } else if (strncmp(raw_ptr, SL_WISUN_METER_REQUEST_TYPE_STR_REMOVE, maxlen) == 0) {
    *req = SL_WISUN_MC_REQ_REMOVE;
  } else {
    *req = SL_WISUN_MC_REQ_UNKNOWN;
  }

  // Checking the token
  token = raw_ptr;
  while (*(token++) && (i++ < maxlen)) ;
  if (i > maxlen) {
    return SL_STATUS_FAIL;
  }

  token_len = sl_wisun_mc_get_token_size();

  if (!sl_wisun_mc_compare_token(token, token_len)) {
    printf("error token: %s\n", token);
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
#else
  (void) raw;
  (void) packet_data_len;
  (void) req;
  return SL_STATUS_FAIL;
#endif
}

static sl_status_t _meter_build_packets(const sl_wisun_request_type_t req,
                                        const sl_wisun_meter_packet_t * const packets,
                                        const uint8_t nr_of_packets,
                                        uint8_t * const buf,
                                        uint32_t * const len)
{
#if !defined(SL_CATALOG_WISUN_COAP_PRESENT)
  static sl_wisun_meter_packet_packed_t packed_packet = { 0 };
  uint32_t response_len                               = 0U;
  uint32_t packed_len                                 = sizeof(sl_wisun_meter_packet_packed_t);

  (void) req;

  if ((packets == NULL)
      || (nr_of_packets == 0)
      || (buf == NULL)
      || (len == NULL)) {
    return SL_STATUS_FAIL;
  }

  for (uint8_t i = 0U; i < nr_of_packets; i++) {
    sl_wisun_mc_pack_measurement_packet(&packed_packet, &packets[i]);
    memcpy(&buf[response_len], &packed_packet, packed_len);
    response_len += packed_len;
  }
  *len = response_len;

  return SL_STATUS_OK;
#else
  (void) req;
  (void) packets;
  (void) nr_of_packets;
  (void) buf;
  (void) len;
  return SL_STATUS_FAIL;
#endif
}

static bool _meter_is_measurement_necessary(sl_mempool_t *collectors_mempool,
                                            const uint32_t schedule)
{
  static uint32_t new_timestamp = 0U;
  static uint32_t old_timestamp = 0U;

  if (collectors_mempool == NULL || collectors_mempool->blocks == NULL) {
    return false;
  }

  new_timestamp = sl_sleeptimer_get_tick_count();
  if (sl_sleeptimer_tick_to_ms(new_timestamp - old_timestamp) > schedule) {
    old_timestamp = new_timestamp;
    return true;
  } else {
    return false;
  }
}

static bool _meter_is_sending_necessary(sl_wisun_meter_packet_storage_t *storage,
                                        sl_wisun_collector_entry_t *collector,
                                        uint8_t *nr_of_packets)
{
  (void) collector;

  if (storage == NULL || storage->stored != storage->buf_size) {
    *nr_of_packets = 0U;
    return false;
  } else {
    *nr_of_packets = SL_WISUN_METER_MEASUREMENT_BUFFER_SIZE;
    return true;
  }
}

static void _create_common_socket(void)
{
  static sockaddr_in6_t meter_addr  = { 0 };
  int32_t res                       = SOCKET_INVALID_ID;

  _common_socket = socket(AF_INET6, (SOCK_DGRAM | SOCK_NONBLOCK), IPPROTO_UDP);
  assert(_common_socket != SOCKET_INVALID_ID);

  meter_addr.sin6_family  = AF_INET6;
  meter_addr.sin6_addr    = in6addr_any;
  meter_addr.sin6_port    = htons(SL_WISUN_METER_PORT);

  res = bind(_common_socket,
             (const struct sockaddr *) &meter_addr,
             sizeof(struct sockaddr_in6));
  assert(res != SOCKET_RETVAL_ERROR);
}

static sl_status_t _sl_wisun_meter_meas_params_and_send(const sockaddr_in6_t * const collector_addr)
{
  static sl_wisun_meter_packet_t packet = { 0 };
  sl_status_t res                       = SL_STATUS_FAIL;
  uint32_t len                          = 0U;

  _sl_wisun_meter_meas_params(&packet);
  sl_wisun_mc_mutex_acquire(_meter_hnd);
  _meter_hnd.build(SL_WISUN_MC_REQ_ASYNC, &packet, 1U, _tx_buf, &len);
  res = _sl_wisun_meter_send_response(_common_socket, _tx_buf, collector_addr, len);
  sl_wisun_mc_mutex_release(_meter_hnd);
  return res;
}

static sl_status_t _sl_wisun_meter_handle_rd_request(const sockaddr_in6_t * const collector_addr)
{
  static sl_wisun_meter_packet_t packet = { 0 };
  sl_status_t res                       = SL_STATUS_FAIL;
  uint32_t len                          = 0U;

  sl_wisun_mc_mutex_acquire(_meter_hnd);
  _meter_hnd.build(SL_WISUN_MC_REQ_RD, &packet, 1U, _tx_buf, &len);
  res = _sl_wisun_meter_send_response(_common_socket, _tx_buf, collector_addr, len);
  sl_wisun_mc_mutex_release(_meter_hnd);
  return res;
}

static sl_status_t _sl_wisun_meter_send_response(const int32_t sockid,
                                                 const uint8_t *buf,
                                                 const sockaddr_in6_t * const coll_addr,
                                                 const uint32_t response_len)
{
  socklen_t addr_len  = 0U;
  int32_t res         = SOCKET_INVALID_ID;

  if ((buf == NULL) || (coll_addr == NULL) || (response_len == 0)) {
    return SL_STATUS_FAIL;
  }

  addr_len = sizeof(*coll_addr);
  res = sendto(sockid,
               buf,
               response_len,
               0,
               (const struct sockaddr *)coll_addr,
               addr_len);

  if (res == SOCKET_RETVAL_ERROR) {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

static sl_status_t _sl_wisun_meter_recv_request(const int32_t sockid,
                                                sockaddr_in6_t *remote_addr,
                                                int32_t * const packet_data_len)
{
  socklen_t addrlen = 0U;
  int32_t res       = SOCKET_INVALID_ID;

  if (remote_addr == NULL || packet_data_len == NULL) {
    return SL_STATUS_FAIL;
  }

  *packet_data_len = -1;
  addrlen = sizeof(sockaddr_in6_t);
  res = recvfrom(sockid,
                 _rx_buf,
                 SL_WISUN_METER_BUFFER_LEN,
                 0,
                 (struct sockaddr *)remote_addr,
                 &addrlen);

  // No received data or failure
  if (res <= 0) {
    return SL_STATUS_FAIL;
  }

  if (!memcmp(&remote_addr->sin6_addr, &in6addr_any, sizeof(in6addr_any))) {
    printf("[Invalid address received]\n");
    return SL_STATUS_FAIL;
  }

  *packet_data_len = res;
  return SL_STATUS_OK;
}

static sl_status_t _sl_wisun_meter_handle_request(const sl_wisun_request_type_t req,
                                                  const sockaddr_in6_t * const remote_addr)
{
  const char *collector_ip = NULL;
  sl_status_t res          = SL_STATUS_FAIL;

  if (remote_addr == NULL) {
    return SL_STATUS_FAIL;
  }

  collector_ip = app_wisun_trace_util_get_ip_str(&remote_addr->sin6_addr);
  switch (req) {
    case SL_WISUN_MC_REQ_ASYNC:
      printf("[Async request from %s]\n", collector_ip);
      res = _sl_wisun_meter_meas_params_and_send(remote_addr);
      break;
    case SL_WISUN_MC_REQ_REGISTER:
      printf("[Registration request from %s]\n", collector_ip);
      res = sl_wisun_meter_register_collector(remote_addr);
      break;
    case SL_WISUN_MC_REQ_REMOVE:
      printf("[Remove request from %s]\n", collector_ip);
      res = sl_wisun_meter_remove_collector(remote_addr);
      break;
    case SL_WISUN_MC_REQ_RD:
      printf("[Resource discovery request from %s]\n", collector_ip);
      res = _sl_wisun_meter_handle_rd_request(remote_addr);
      break;
    default:
      res = SL_STATUS_FAIL;
      break;
  }

  app_wisun_trace_util_destroy_ip_str(collector_ip);
  return res;
}

static void _sl_wisun_meter_meas_params(sl_wisun_meter_packet_t *packet)
{
  // Fill packet
  sl_wisun_meter_gen_packet_id(packet);
  sl_wisun_meter_get_temperature(packet);
  sl_wisun_meter_get_humidity(packet);
  sl_wisun_meter_get_light(packet);
}

static sl_status_t _sl_wisun_meter_store_packet(const sl_wisun_meter_packet_t * const packet)
{
  sl_wisun_mc_mutex_acquire(_meter_hnd);
  if (packet == NULL || _packet_storage.stored >= _packet_storage.buf_size) {
    sl_wisun_mc_release_mtx_and_return_val(_meter_hnd, SL_STATUS_FAIL);
  }

  _packet_storage.buffer[_packet_storage.stored] = *packet;
  _packet_storage.stored++;

  sl_wisun_mc_mutex_release(_meter_hnd);

  return SL_STATUS_OK;
}

static sl_status_t _sl_wisun_meter_measurement_cycle(const uint32_t schedule)
{
  static sl_wisun_meter_packet_t packet = { 0 };
  sl_status_t res                       = SL_STATUS_FAIL;

  if (!_meter_hnd.is_measurement_necessary(&_collectors_mempool, schedule)) {
    return SL_STATUS_OK;
  }

  _sl_wisun_meter_meas_params(&packet);
  res = _sl_wisun_meter_store_packet(&packet);

  return res;
}

static sl_status_t _sl_wisun_meter_sending_cycle(void)
{
  sl_mempool_block_hnd_t *block               = NULL;
  sl_wisun_collector_entry_t *tmp_coll_entry  = NULL;
  const char *ip_addr                         = NULL;
  sl_status_t res                             = SL_STATUS_FAIL;
  uint8_t nr_of_packets                       = 0U;

  sl_wisun_mc_mutex_acquire(_meter_hnd);

  block = _collectors_mempool.blocks;

  while (block != NULL) {
    tmp_coll_entry = (sl_wisun_collector_entry_t *)block->start_addr;

    if (!_meter_hnd.is_sending_necessary(&_packet_storage, tmp_coll_entry, &nr_of_packets)) {
      block = block->next;
      continue;
    }

    res = _meter_hnd.build(SL_WISUN_MC_REQ_REGISTER,
                           _packet_storage.buffer,
                           nr_of_packets,
                           _tx_buf,
                           &_response_len);
    if (res != SL_STATUS_OK) {
      printf("[Building failure]\n");
      block = block->next;
      continue;
    }

    ip_addr = app_wisun_trace_util_get_ip_str(&tmp_coll_entry->addr.sin6_addr);

    res = _sl_wisun_meter_send_response(_common_socket,
                                        _tx_buf,
                                        &tmp_coll_entry->addr,
                                        _response_len);

    if (res == SL_STATUS_OK) {
      printf("[%s: Measurement packet has been sent (%lu bytes)]\n", ip_addr, _response_len);
    } else {
      printf("[%s: Measurement packet has not been sent]\n", ip_addr);
    }

    app_wisun_trace_util_destroy_ip_str(ip_addr);
    block = block->next;
  }

  if (_packet_storage.stored == _packet_storage.buf_size) {
    _packet_storage.stored = 0U;
  }

  sl_wisun_mc_mutex_release(_meter_hnd);
  return SL_STATUS_OK;
}
#endif

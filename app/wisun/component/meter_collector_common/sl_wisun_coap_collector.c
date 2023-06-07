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
#include "sl_wisun_coap_collector.h"
#include <string.h>
#include "sl_string.h"
#include "sl_status.h"
#include "sl_wisun_meter_collector_config.h"
#include "sl_wisun_collector.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define __cleanup_and_return_val(__packet, __buff, __retval) \
  do {                                                       \
    sl_wisun_coap_free((__packet));                          \
    sl_wisun_coap_free((__buff));                            \
    sl_wisun_mc_mutex_release(_coap_collector_hnd);          \
    return (__retval);                                       \
  } while (0)

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief CoAP Collector send request
 * @details Handler function
 * @param[in] meter Meter entry
 * @param[in] req Meter request
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _coap_collector_send_request(const int32_t sockid,
                                                sl_wisun_meter_entry_t * meter,
                                                sl_wisun_meter_request_t * req);

/**************************************************************************//**
 * @brief CoAP Collector receive response
 * @details Handler function
 * @param[in] sockid Socket ID
 * @return sl_wisun_meter_entry_t* Meter entry or NULL on failure
 *****************************************************************************/
static sl_wisun_meter_entry_t * _coap_collector_recv_response(int32_t sockid);

/**************************************************************************//**
 * @brief CoAP Collector update meter status
 * @details Update meter fields from received packet
 * @param[in,out] meter meter
 * @param[in] parsed received parsed packet
 *****************************************************************************/
static void _update_meter_status(sl_wisun_meter_entry_t *meter, sl_wisun_coap_packet_t* parsed);

/**************************************************************************//**
 * @brief CoAP Collector get schedule from payload
 * @details Get schedule value from json payload.
 * @param[in] payload_ptr payload_ptr
 * @return Schedule value.
 *****************************************************************************/
static uint32_t _get_schedule_from_payload(uint8_t *payload_ptr);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Internal CoAP Collector handler
static sl_wisun_collector_hnd_t _coap_collector_hnd = { 0 };

/// Measurement get request
static sl_wisun_meter_request_t _meas_req = { 0 };

/// LED put request
static sl_wisun_meter_request_t _led_req  = { 0 };

/// Receiver buffer
static uint8_t _recv_buff[SL_WISUN_COAP_METER_COLLECTOR_RECV_BUFF_SIZE] = { 0 };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* Wi-SUN CoAP Collector component init */
void sl_wisun_coap_collector_init(void)
{
  sl_wisun_collector_set_initializer(&_coap_collector_hnd, sl_wisun_collector_init_common_resources);

  sl_wisun_collector_init_hnd(&_coap_collector_hnd);
  // Init coap collector handler
  sl_wisun_collector_set_handler(&_coap_collector_hnd,
                                 _coap_collector_recv_response,
                                 _coap_collector_send_request,
                                 NULL,
                                 NULL);
  sl_wisun_collector_inherit_common_hnd(&_coap_collector_hnd);
}

/* CoAP collector prepare request */
sl_status_t sl_wisun_coap_collector_prepare_meas_request(void)
{
  int16_t builder_res = -1;                // builder result
  sl_wisun_coap_packet_t *packet = NULL;

  // lock
  sl_wisun_mc_mutex_acquire(_coap_collector_hnd);

  sl_wisun_coap_free(_meas_req.buff);
  _meas_req.buff = NULL;

  packet = (sl_wisun_coap_packet_t *)sl_wisun_coap_malloc(sizeof(sl_wisun_coap_packet_t));

  if (packet == NULL) {
    printf("[Coap packet buffer cannot be allocated]\n");
    __cleanup_and_return_val(packet, _meas_req.buff, SL_STATUS_FAIL);
  }

  // Init request for meters
  memset(packet, 0, sizeof(sl_wisun_coap_packet_t));
  packet->uri_path_ptr     = (uint8_t *) SL_WISUN_COAP_METER_COLLECTOR_MEASUREMENT_URI_PATH;
  packet->uri_path_len     = strlen(SL_WISUN_COAP_METER_COLLECTOR_MEASUREMENT_URI_PATH);
  packet->msg_code         = COAP_MSG_CODE_REQUEST_GET;
  packet->content_format   = COAP_CT_TEXT_PLAIN;
  packet->payload_len      = 0;
  packet->payload_ptr      = NULL;
  packet->options_list_ptr = NULL;
  packet->msg_id           = SL_WISUN_COAP_METER_COLLECTOR_DEFAULT_MESSAGE_ID;

  _meas_req.length = sl_wisun_coap_builder_calc_size(packet);

  printf("[Building request message (%d bytes)]\n", _meas_req.length);
  _meas_req.buff = sl_wisun_coap_malloc(_meas_req.length);

  if (_meas_req.buff == NULL) {
    printf("[Coap message buffer cannot be allocated]\n");
    __cleanup_and_return_val(packet, _meas_req.buff, SL_STATUS_FAIL);
  }

  builder_res = sl_wisun_coap_builder(_meas_req.buff, packet);
  if (builder_res < 0) {
    printf("[Coap builder error: %s]\n", builder_res == -1 ? "Message Header structure" : "NULL ptr arg");
    __cleanup_and_return_val(packet, _meas_req.buff, SL_STATUS_FAIL);
  }
  // Set measurement request which is sent periodically
  sl_wisun_collector_set_measurement_request(&_meas_req);

  // only packet should be freed
  sl_wisun_coap_free(packet);

  sl_wisun_mc_mutex_release(_coap_collector_hnd);

  return SL_STATUS_OK;
}

sl_status_t sl_wisun_coap_collector_prepare_led_toggle_request(const uint8_t led_id)
{
  int16_t builder_res  = -1;                // builder result
  const char *payload  = NULL;
  uint16_t payload_len = 0;
  sl_wisun_coap_packet_t *packet = NULL;

  // lock
  sl_wisun_mc_mutex_acquire(_coap_collector_hnd);

  sl_wisun_coap_free(_led_req.buff);
  _led_req.buff = NULL;

  packet = (sl_wisun_coap_packet_t *)sl_wisun_coap_malloc(sizeof(sl_wisun_coap_packet_t));

  if (packet == NULL) {
    printf("[Coap packet buffer cannot be allocated]\n");
    __cleanup_and_return_val(packet, _led_req.buff, SL_STATUS_FAIL);
  }

  payload = sl_wisun_mc_get_led_payload_by_id(led_id);
  payload_len = sl_strnlen((char *)payload, SL_WISUN_METER_LED_TOGGLE_PAYLOAD_STR_MAX_LEN) + 1;

  // Init request for meters
  memset(packet, 0, sizeof(sl_wisun_coap_packet_t));
  packet->uri_path_ptr     = (uint8_t *) SL_WISUN_COAP_METER_COLLECTOR_LED_TOGGLE_URI_PATH;
  packet->uri_path_len     = strlen(SL_WISUN_COAP_METER_COLLECTOR_LED_TOGGLE_URI_PATH);
  packet->msg_code         = COAP_MSG_CODE_REQUEST_PUT;
  packet->content_format   = COAP_CT_TEXT_PLAIN;
  packet->payload_len      = payload_len;
  packet->payload_ptr      = (uint8_t *)payload;
  packet->options_list_ptr = NULL;
  packet->msg_id           = SL_WISUN_COAP_METER_COLLECTOR_DEFAULT_MESSAGE_ID;

  _led_req.length = sl_wisun_coap_builder_calc_size(packet);

  printf("[Building request message (%d bytes)]\n", _led_req.length);
  _led_req.buff = sl_wisun_coap_malloc(_led_req.length);

  if (_led_req.buff == NULL) {
    printf("[Coap message buffer cannot be allocated]\n");
    __cleanup_and_return_val(packet, _led_req.buff, SL_STATUS_FAIL);
  }

  builder_res = sl_wisun_coap_builder(_led_req.buff, packet);
  if (builder_res < 0) {
    printf("[Coap builder error: %s]\n", builder_res == -1 ? "Message Header structure" : "NULL ptr arg");
    __cleanup_and_return_val(packet, _led_req.buff, SL_STATUS_FAIL);
  }

  // only packet should be freed
  sl_wisun_coap_free(packet);

  sl_wisun_mc_mutex_release(_coap_collector_hnd);

  return SL_STATUS_OK;
}

sl_status_t sl_wisun_coap_collector_send_led_toggle_request(const wisun_addr_t * const meter_addr)
{
  sl_wisun_meter_entry_t meter = { 0 };
  sl_status_t retval = SL_STATUS_FAIL;

  retval = sl_wisun_collector_get_meter(meter_addr, &meter);
  if (retval != SL_STATUS_OK) {
    return SL_STATUS_FAIL;
  }
  retval = _coap_collector_send_request(sl_wisun_collector_get_shared_socket(),
                                        &meter,
                                        &_led_req);
  return retval;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static sl_status_t _coap_collector_send_request(const int32_t sockid,
                                                sl_wisun_meter_entry_t * meter,
                                                sl_wisun_meter_request_t * req)
{
  int32_t res = SOCKET_INVALID_ID;
  socklen_t len = 0;
  sl_status_t retval = SL_STATUS_OK;

  if (sockid == SOCKET_INVALID_ID) {
    return false;
  }

  len = sizeof(meter->addr);

  res = sendto(sockid, req->buff, req->length, 0,
               (const struct sockaddr *)&meter->addr, len);
  if (res == SOCKET_RETVAL_ERROR) {
    retval = SL_STATUS_FAIL;
  }

  return retval;
}

static sl_wisun_meter_entry_t * _coap_collector_recv_response(int32_t sockid)
{
  wisun_addr_t remote_addr       = { 0 };
  sl_wisun_coap_packet_t* parsed = NULL;
  const char *ip_addr            = NULL;
  sl_wisun_meter_entry_t *meter  = NULL;
  socklen_t len                  = 0;
  int32_t res                    = SOCKET_INVALID_ID;

  len = sizeof(remote_addr);
  res = recvfrom(sockid, _recv_buff, SL_WISUN_COAP_METER_COLLECTOR_RECV_BUFF_SIZE, 0,
                 (struct sockaddr *)&remote_addr, &len);
  if (res <= 0) {
    return NULL;
  }

  meter = _coap_collector_hnd.get_meter(&remote_addr);

  if (meter == NULL) {
    printf("[Unknown remote message received!]\n");
    return NULL;
  }

  ip_addr = app_wisun_trace_util_get_ip_str(&remote_addr.sin6_addr);
  parsed = sl_wisun_coap_parser(res, _recv_buff);

  if (parsed == NULL) {
    printf("[CoAP Parser failure]\n");
    return NULL;
  }

  _update_meter_status(meter, parsed);

  printf("[%s]\n", ip_addr);
  sl_wisun_coap_print_packet(parsed, false);
  sl_wisun_coap_destroy_packet(parsed);
  app_wisun_trace_util_destroy_ip_str(ip_addr);

  return meter;
}

static void _update_meter_status(sl_wisun_meter_entry_t *meter, sl_wisun_coap_packet_t* parsed)
{
  if (parsed->payload_ptr != NULL) {
    meter->schedule = _get_schedule_from_payload(parsed->payload_ptr);
  }
}

static uint32_t _get_schedule_from_payload(uint8_t *payload_ptr)
{
  char *scedule_value;
  uint32_t scedule_value_uint32   = SL_WISUN_METER_DEFAULT_PERIOD_MS;
  char *scedule_value_start_ptr   = strchr((const char*)payload_ptr, '-') + 1;
  char *scedule_value_end_ptr     = strchr((const char*)scedule_value_start_ptr, '"');
  size_t schedule_value_length    = scedule_value_end_ptr - scedule_value_start_ptr;

  scedule_value = (char*)app_wisun_malloc(schedule_value_length);
  if (scedule_value == NULL) {
    printf("[Payload parse failure: could not allocate buffer]\n");
    return scedule_value_uint32;
  }

  strncpy(scedule_value, scedule_value_start_ptr, schedule_value_length);
  scedule_value_uint32 = atoi(scedule_value);

  if (scedule_value_uint32 == 0) {
    printf("[Payload parse failure: schedule value could not represen as int]\n");
    scedule_value_uint32 = SL_WISUN_METER_DEFAULT_PERIOD_MS;
  }

  app_wisun_free(scedule_value);

  return scedule_value_uint32;
}

#undef __cleanup_and_return_val

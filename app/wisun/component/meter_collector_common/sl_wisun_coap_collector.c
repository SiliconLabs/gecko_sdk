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
#include "sl_wisun_trace_util.h"

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
 * @brief CoAP Collector parse
 * @details Handler function
 * @param[in] raw Received data buffer
 * @param[in] packet_data_len Length of the received packet
 * @param[in] remote_addr Address of the sender
 * @return sl_wisun_meter_entry_t* Meter entry or NULL on failure
 *****************************************************************************/
static sl_wisun_meter_entry_t *_coap_collector_parse_response(void *raw,
                                                              int32_t packet_data_len,
                                                              const sockaddr_in6_t * const remote_addr);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Internal CoAP Collector handler
static sl_wisun_collector_hnd_t _coap_collector_hnd = { 0 };

/// Requests
static sl_wisun_meter_request_t _async_meas_req     = { 0 };
static sl_wisun_meter_request_t _registration_req   = { 0 };
static sl_wisun_meter_request_t _removal_req        = { 0 };
static sl_wisun_meter_request_t _led_req            = { 0 };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* Wi-SUN CoAP Collector component init */
void sl_wisun_coap_collector_init(void)
{
  sl_wisun_collector_set_initializer(&_coap_collector_hnd,
                                     sl_wisun_collector_init_common_resources);

  sl_wisun_collector_init_hnd(&_coap_collector_hnd);
  // Init coap collector handler
  sl_wisun_collector_set_handler(&_coap_collector_hnd,
                                 _coap_collector_parse_response,
                                 NULL);
  sl_wisun_collector_inherit_common_hnd(&_coap_collector_hnd);

  sl_wisun_coap_collector_prepare_request(SL_WISUN_MC_REQ_ASYNC, &_async_meas_req);
  sl_wisun_coap_collector_prepare_request(SL_WISUN_MC_REQ_REGISTER, &_registration_req);
  sl_wisun_coap_collector_prepare_request(SL_WISUN_MC_REQ_REMOVE, &_removal_req);
}

/* CoAP collector prepare request */
sl_status_t sl_wisun_coap_collector_prepare_request(const sl_wisun_request_type_t req_type,
                                                    sl_wisun_meter_request_t * const req)
{
  sl_wisun_coap_packet_t *packet  = NULL;
  int16_t builder_res             = -1;

  if (req_type >= SL_WISUN_MC_REQ_UNKNOWN || req == NULL) {
    return SL_STATUS_FAIL;
  }

  // lock
  sl_wisun_mc_mutex_acquire(_coap_collector_hnd);

  sl_wisun_coap_free(req->buff);
  req->buff = NULL;

  packet = (sl_wisun_coap_packet_t *)sl_wisun_coap_malloc(sizeof(sl_wisun_coap_packet_t));

  if (packet == NULL) {
    printf("[Coap packet buffer cannot be allocated]\n");
    __cleanup_and_return_val(packet, req->buff, SL_STATUS_FAIL);
  }

  // Init request for meters
  memset(packet, 0, sizeof(sl_wisun_coap_packet_t));
  packet->uri_path_ptr     = (uint8_t *) SL_WISUN_COAP_METER_COLLECTOR_MEASUREMENT_URI_PATH;
  packet->uri_path_len     = strlen(SL_WISUN_COAP_METER_COLLECTOR_MEASUREMENT_URI_PATH);
  packet->msg_code         = COAP_MSG_CODE_REQUEST_GET;
  packet->content_format   = COAP_CT_TEXT_PLAIN;
  packet->payload_ptr      = NULL;
  packet->options_list_ptr = NULL;
  packet->msg_id           = SL_WISUN_COAP_METER_COLLECTOR_DEFAULT_MESSAGE_ID;

  switch (req_type) {
    case SL_WISUN_MC_REQ_ASYNC:
      packet->payload_ptr = (uint8_t *) SL_WISUN_METER_REQUEST_TYPE_STR_ASYNC;
      packet->payload_len = strlen(SL_WISUN_METER_REQUEST_TYPE_STR_ASYNC);
      break;
    case SL_WISUN_MC_REQ_REGISTER:
      packet->payload_ptr = (uint8_t *) SL_WISUN_METER_REQUEST_TYPE_STR_REGISTER;
      packet->payload_len = strlen(SL_WISUN_METER_REQUEST_TYPE_STR_REGISTER);
      break;
    case SL_WISUN_MC_REQ_REMOVE:
      packet->payload_ptr = (uint8_t *) SL_WISUN_METER_REQUEST_TYPE_STR_REMOVE;
      packet->payload_len = strlen(SL_WISUN_METER_REQUEST_TYPE_STR_REMOVE);
      break;
    default:
      break;
  }

  req->length = sl_wisun_coap_builder_calc_size(packet);

  printf("[Building request message (%d bytes)]\n", req->length);
  req->buff = sl_wisun_coap_malloc(req->length);

  if (req->buff == NULL) {
    printf("[Coap message buffer cannot be allocated]\n");
    __cleanup_and_return_val(packet, req->buff, SL_STATUS_FAIL);
  }

  builder_res = sl_wisun_coap_builder(req->buff, packet);
  if (builder_res < 0) {
    printf("[Coap builder error: %s]\n",
           builder_res == -1 ? "Message Header structure" : "NULL ptr arg");
    __cleanup_and_return_val(packet, req->buff, SL_STATUS_FAIL);
  }

  switch (req_type) {
    case SL_WISUN_MC_REQ_ASYNC:
      sl_wisun_collector_set_async_measurement_request(req);
      break;
    case SL_WISUN_MC_REQ_REGISTER:
      sl_wisun_collector_set_registration_request(req);
      break;
    case SL_WISUN_MC_REQ_REMOVE:
      sl_wisun_collector_set_removal_request(req);
      break;
    default:
      break;
  }

  // only packet should be freed
  sl_wisun_coap_free(packet);

  sl_wisun_mc_mutex_release(_coap_collector_hnd);

  return SL_STATUS_OK;
}

sl_status_t sl_wisun_coap_collector_prepare_led_toggle_request(const uint8_t led_id)
{
  sl_wisun_coap_packet_t *packet  = NULL;
  const char *payload             = NULL;
  uint16_t payload_len            = 0;
  int16_t builder_res             = -1;

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
  payload_len = sl_strnlen((char *)payload,
                           SL_WISUN_METER_LED_TOGGLE_PAYLOAD_STR_MAX_LEN) + 1;

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
    printf("[Coap builder error: %s]\n",
           builder_res == -1 ? "Message Header structure" : "NULL ptr arg");
    __cleanup_and_return_val(packet, _led_req.buff, SL_STATUS_FAIL);
  }

  sl_wisun_coap_free(packet);

  sl_wisun_mc_mutex_release(_coap_collector_hnd);

  return SL_STATUS_OK;
}

sl_status_t sl_wisun_coap_collector_send_led_toggle_request(const sockaddr_in6_t *meter_addr)
{
  sl_status_t retval  = SL_STATUS_FAIL;

  retval = sl_wisun_collector_send_request(sl_wisun_collector_get_shared_socket(),
                                           meter_addr,
                                           &_led_req);

  return retval;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static sl_wisun_meter_entry_t *_coap_collector_parse_response(void *raw,
                                                              int32_t packet_data_len,
                                                              const sockaddr_in6_t * const remote_addr)
{
  sl_wisun_meter_entry_t *meter     = NULL;
  const char *ip_addr               = NULL;
  sl_wisun_coap_packet_t *parsed    = NULL;
  uint8_t nr_of_packets             = 0U;
  sl_wisun_request_type_t resp_type = SL_WISUN_MC_REQ_UNKNOWN;

  parsed = sl_wisun_coap_parser(packet_data_len, raw);

  if (parsed == NULL) {
    printf("[CoAP Parser failure]\n");
    return NULL;
  }

  for (uint16_t i = 0; i < parsed->payload_len; i++) {
    if (parsed->payload_ptr[i] == '#') {
      nr_of_packets++;
    }
  }

  if (nr_of_packets == 1) {
    resp_type = SL_WISUN_MC_REQ_ASYNC;
  } else {
    resp_type = SL_WISUN_MC_REQ_REGISTER;
  }

  sl_wisun_mc_mutex_acquire(_coap_collector_hnd);
  if (resp_type == SL_WISUN_MC_REQ_ASYNC) {
    meter = sl_wisun_collector_get_async_meter_entry_by_address(remote_addr);
  }
  if (meter == NULL) {
    meter = sl_wisun_collector_get_registered_meter_entry_by_address(remote_addr);
  }
  sl_wisun_mc_mutex_release(_coap_collector_hnd);

  if (meter == NULL) {
    printf("[Unknown remote message received!]\n");
    return NULL;
  }

  ip_addr = app_wisun_trace_util_get_ip_str(&remote_addr->sin6_addr);
  printf("[%s]\n", ip_addr);
  sl_wisun_coap_print_packet(parsed, false);
  sl_wisun_coap_destroy_packet(parsed);
  app_wisun_trace_util_destroy_ip_str(ip_addr);

  return meter;
}

#undef __cleanup_and_return_val

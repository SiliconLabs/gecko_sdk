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
#include "em_device.h"
#include "sl_wisun_coap_meter.h"
#include "sl_component_catalog.h"
#include "sl_string.h"
#include "sl_wisun_app_core.h"
#include "sl_wisun_coap_rhnd.h"
#include "sli_wisun_coap_rd.h"
#include "sl_wisun_trace_util.h"

#if !defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  #include "sl_wisun_led_driver.h"
#endif

#if defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  #include "sl_wisun_rht_measurement.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// JSON formated measurement data maximum size
#define JSON_MEASUREMENT_DATA_SIZE                (350U)

#define JSON_MEASUREMENT_FORMAT_STR \
  "  {\n"                           \
  "    \"%s\" :\n"                  \
  "    {\n"                         \
  "      \"id\": %u,\n"             \
  "      \"temp\": %lu.%lu,\n"      \
  "      \"hum\": %lu.%lu,\n"       \
  "      \"lx\": %u\n"              \
  "    }\n"                         \
  "  }"

/// Measurement plain text buffer size
#define RHT_AND_LIGHT_MEAS_PLAIN_TXT_DATA_SIZE    (32U)

#define add_response_beginning(buf, ip) \
  snprintf(buf, JSON_MEASUREMENT_DATA_SIZE, "{\"%s\" : \n[", ip)

#define add_response_line(buf, packet)             \
  snprintf(buf,                                    \
           JSON_MEASUREMENT_DATA_SIZE,             \
           "\n\"#%u: %lu.%luC %lu.%lu%% %ulux\",", \
           packet.id,                              \
           packet.temperature / 1000,              \
           (packet.temperature % 1000) / 10,       \
           packet.humidity / 1000,                 \
           (packet.humidity % 1000) / 10,          \
           packet.light)

#define add_response_ending(buf) \
  snprintf(buf, JSON_MEASUREMENT_DATA_SIZE, "\n]}")

/// Measurement type enumeration
typedef enum measurement_type {
  /// Measure All
  COAP_METER_MEASUREMENT_ALL,
  /// Measure temperature
  COAP_METER_MEASUREMENT_TEMPERATURE,
  /// Measure humidity
  COAP_METER_MEASUREMENT_HUMIDITY,
  /// Measure light
  COAP_METER_MEASUREMENT_LIGHT
} measurement_type_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

#if SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
/**************************************************************************//**
 * @brief CoAP meter parse
 * @details Handler function
 * @param[in] raw Received data buffer
 * @param[in] packet_data_len Length of the received packet
 * @param[out] req NULL
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _coap_meter_parse_request(const void * const raw,
                                             int32_t packet_data_len,
                                             sl_wisun_request_type_t * const req);

/**************************************************************************//**
 * @brief Coap meter build
 * @details Handler function
 * @param[in] req Request type
 * @param[in] packets Pointer to the packet buffer
 * @param[in] nr_of_packets Number of packets to build
 * @param[in, out] buf Buffer to store packed data
 * @param[out] len Length of the buffer
 * @return SL_STATUS_OK On success
 * @return SL_STATUS_FAIL On failure
 *****************************************************************************/
static sl_status_t _coap_meter_build_packets(const sl_wisun_request_type_t req,
                                             const sl_wisun_meter_packet_t * const packets,
                                             const uint8_t nr_of_packets,
                                             uint8_t * const buf,
                                             uint32_t * const len);
#else

/**************************************************************************//**
 * @brief Create formated json string from measurement packet
 * @details Use snprintf to static buffer
 * @param[in] packet packet
 * @param[in] ip_str_global node global ipv6 address
 * @return const char* pointer to the static buff
 *****************************************************************************/
static const char *_meter_packet2json(const sl_wisun_meter_packet_t * const packet,
                                      const char *ip_str_global);

/**************************************************************************//**
 * @brief Prepare measurement by measurement type
 * @details Helper function
 * @param[in] req_packet Request packet
 * @param[in] measurement Measurement type
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
static sl_wisun_coap_packet_t *_prepare_measurement_resp(const sl_wisun_coap_packet_t * const req_packet,
                                                         const measurement_type_t measurement);

#if !defined(SL_CATALOG_POWER_MANAGER_PRESENT)
/**************************************************************************//**
 * @brief Convert LED ID.
 * @details Helper function to convert uint8_t LED ID to sl_wisun_led_id_t
 * @param[in] led_id LED ID raw value
 * @return sl_wisun_led_id_t converted LED ID
 *****************************************************************************/
static sl_wisun_led_id_t _coap_meter_convert_led_id(const uint8_t led_id);
#endif
#endif

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// Internal CoAP Meter handler
static sl_wisun_meter_hnd_t _coap_meter_hnd = { 0 };

/// Dummy request packet
static sl_wisun_coap_packet_t dummy_req_pkt = {
  .token_len = 0,
  .coap_status = COAP_STATUS_OK,
  .msg_code = COAP_MSG_CODE_REQUEST_GET,
  .msg_type = COAP_MSG_TYPE_NON_CONFIRMABLE,
  .content_format = COAP_CT_TEXT_PLAIN,
  .msg_id = SL_WISUN_COAP_METER_COLLECTOR_DEFAULT_MESSAGE_ID,
  .payload_len = 0,
  .payload_ptr = NULL,
  .uri_path_ptr = (uint8_t *)SLI_WISUN_COAP_RD_CORE_STR,
  .uri_path_len = 0,
  .options_list_ptr = NULL
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
void sl_wisun_coap_meter_init(void)
{
  // init meter for having proper meter content
  sl_wisun_meter_init();

  // Init meter-collector common component
#if !defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  sl_wisun_meter_set_initializer(&_coap_meter_hnd, NULL);
#else
  sl_wisun_meter_set_initializer(&_coap_meter_hnd, sl_wisun_rht_init);
#endif

#if SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
  sl_wisun_meter_init_common_resources(_coap_meter_parse_request,
                                       _coap_meter_build_packets);
  sl_wisun_meter_set_handler(&_coap_meter_hnd, NULL, NULL, NULL, NULL);
#endif
  sl_wisun_meter_init_hnd(&_coap_meter_hnd);

  dummy_req_pkt.uri_path_len = strlen((char *)dummy_req_pkt.uri_path_ptr);
}

#if !SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
sl_wisun_coap_packet_t *sl_wisun_coap_meter_measurement_response_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  return _prepare_measurement_resp(req_packet, COAP_METER_MEASUREMENT_ALL);
}

sl_wisun_coap_packet_t *sl_wisun_coap_meter_temperature_response_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  return _prepare_measurement_resp(req_packet, COAP_METER_MEASUREMENT_TEMPERATURE);
}

sl_wisun_coap_packet_t *sl_wisun_coap_meter_humidity_response_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  return _prepare_measurement_resp(req_packet, COAP_METER_MEASUREMENT_HUMIDITY);
}

sl_wisun_coap_packet_t *sl_wisun_coap_meter_light_response_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  return _prepare_measurement_resp(req_packet, COAP_METER_MEASUREMENT_LIGHT);
}

#if !defined(SL_CATALOG_POWER_MANAGER_PRESENT)
sl_wisun_coap_packet_t *sl_wisun_coap_meter_led_toggle_response_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_coap_packet_t *resp_packet = NULL;
  int8_t led_id = 0;

  // Init packet
  resp_packet = sl_wisun_coap_build_response(req_packet, COAP_MSG_CODE_RESPONSE_BAD_REQUEST);
  if (resp_packet == NULL) {
    return NULL;
  }
  // Check request packet
  if (req_packet->msg_code != COAP_MSG_CODE_REQUEST_PUT) {
    printf("[Not valid measurement request]\n");
    return resp_packet;
  }

  // Toggle LEDn
  led_id = (int8_t)sl_wisun_mc_get_led_id_from_payload((const char *)req_packet->payload_ptr);
  if (sl_wisun_led_toggle(_coap_meter_convert_led_id(led_id)) == SL_STATUS_FAIL) {
    printf("[LED Toggle failed: %d]\n", led_id);
    resp_packet->msg_code = COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE;
  } else {
    resp_packet->msg_code = COAP_MSG_CODE_RESPONSE_CHANGED;
  }

  return resp_packet;
}
#endif
#endif

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
#if SL_WISUN_COAP_MC_OPTIMIZED_MODE_ENABLE
static sl_status_t _coap_meter_parse_request(const void * const raw,
                                             int32_t packet_data_len,
                                             sl_wisun_request_type_t * const req)
{
  const sl_wisun_coap_packet_t *parsed  = NULL;
  char *raw_ptr                         = NULL;

  if ((raw == NULL) || (packet_data_len == 0) || (req == NULL)) {
    return SL_STATUS_FAIL;
  }

  parsed = sl_wisun_coap_parser(packet_data_len, (uint8_t *)raw);
  if (parsed == NULL) {
    printf("[CoAP Parser failure]\n");
    return SL_STATUS_FAIL;
  }
  sl_wisun_coap_print_packet(parsed, false);

  // Handling response and empty packets
  if (!sl_wisun_coap_rhnd_is_request_packet(parsed)) {
    *req = SL_WISUN_MC_REQ_UNKNOWN;
    return SL_STATUS_FAIL;
  }

  if ((strncmp((char *)parsed->uri_path_ptr,
               (char *)&SLI_WISUN_COAP_RD_CORE_STR[1],
               parsed->uri_path_len) == 0)
      && parsed->msg_code == COAP_MSG_CODE_REQUEST_GET) {
    *req = SL_WISUN_MC_REQ_RD;
    return SL_STATUS_OK;
  }

  if (strncmp((char *)parsed->uri_path_ptr,
              (char *)&SL_WISUN_COAP_METER_COLLECTOR_MEASUREMENT_URI_PATH[1],
              parsed->uri_path_len) != 0) {
    *req = SL_WISUN_MC_REQ_UNKNOWN;
    return SL_STATUS_FAIL;
  }

  raw_ptr = (char *)parsed->payload_ptr;

  // Parse request
  if (parsed->payload_len == 0) {
    *req = SL_WISUN_MC_REQ_ASYNC;
  } else if (strncmp(raw_ptr,
                     SL_WISUN_METER_REQUEST_TYPE_STR_REGISTER,
                     parsed->payload_len) == 0) {
    *req = SL_WISUN_MC_REQ_REGISTER;
  } else if (strncmp(raw_ptr,
                     SL_WISUN_METER_REQUEST_TYPE_STR_ASYNC,
                     parsed->payload_len) == 0) {
    *req = SL_WISUN_MC_REQ_ASYNC;
  } else if (strncmp(raw_ptr,
                     SL_WISUN_METER_REQUEST_TYPE_STR_REMOVE,
                     parsed->payload_len) == 0) {
    *req = SL_WISUN_MC_REQ_REMOVE;
  } else {
    *req = SL_WISUN_MC_REQ_UNKNOWN;
  }

  return SL_STATUS_OK;
}

static sl_status_t _coap_meter_build_packets(const sl_wisun_request_type_t req,
                                             const sl_wisun_meter_packet_t * const packets,
                                             const uint8_t nr_of_packets,
                                             uint8_t * const buf,
                                             uint32_t * const len)
{
  sl_wisun_coap_packet_t *packet                  = NULL;
  static sl_wisun_app_core_current_addr_t addresses                 = { 0 };
  const char *ip_str_global                       = NULL;
  uint16_t payload_len                            = 0U;
  static char payload[JSON_MEASUREMENT_DATA_SIZE] = { 0 };
  int16_t builder_res                             = -1;
  const sl_wisun_coap_rhnd_resource_t *resource   = NULL;
  char *discovery_payload                         = NULL;

  if ((packets == NULL)
      || (nr_of_packets == 0)
      || (buf == NULL)
      || (len == NULL)) {
    return SL_STATUS_FAIL;
  }

  sl_wisun_mc_mutex_acquire(_coap_meter_hnd);
  if (req == SL_WISUN_MC_REQ_RD) {
    // send rd resp
    resource = sl_wisun_coap_rhnd_get_resources();
    discovery_payload = sli_wisun_coap_rd_parser(resource, &dummy_req_pkt, &payload_len);
    packet = sli_wisun_coap_rd_build_response(discovery_payload, payload_len, &dummy_req_pkt);
  } else {
    packet = (sl_wisun_coap_packet_t *)sl_wisun_coap_malloc(sizeof(sl_wisun_coap_packet_t));

    if (packet == NULL) {
      printf("[Coap packet buffer cannot be allocated]\n");
      sl_wisun_coap_free(packet);
      sl_wisun_mc_mutex_release(_coap_meter_hnd);
      return SL_STATUS_FAIL;
    }

    // Init request for meters
    memset(packet, 0, sizeof(sl_wisun_coap_packet_t));
    packet->uri_path_ptr      = (uint8_t *) SL_WISUN_COAP_METER_COLLECTOR_MEASUREMENT_URI_PATH;
    packet->uri_path_len      = strlen(SL_WISUN_COAP_METER_COLLECTOR_MEASUREMENT_URI_PATH);
    packet->msg_code          = COAP_MSG_CODE_RESPONSE_CONTENT;
    packet->content_format    = COAP_CT_JSON;
    packet->payload_len       = 0;
    packet->payload_ptr       = NULL;
    packet->options_list_ptr  = NULL;
    packet->msg_id            = SL_WISUN_COAP_METER_COLLECTOR_DEFAULT_MESSAGE_ID;
    packet->msg_type          = COAP_MSG_TYPE_NON_CONFIRMABLE;

    sl_wisun_app_core_get_current_addresses(&addresses);
    ip_str_global = app_wisun_trace_util_get_ip_str(&addresses.global);

    // Build payload
    payload_len = add_response_beginning(payload, ip_str_global);
    for (uint8_t i = 0; i < nr_of_packets; i++) {
      payload_len += add_response_line(&payload[payload_len], packets[i]);
    }
    payload_len -= 1;
    payload_len += add_response_ending(&payload[payload_len]);

    packet->payload_ptr = (uint8_t *)payload;
    packet->payload_len = payload_len;
  }

  *len = sl_wisun_coap_builder_calc_size(packet);

  printf("[Building response message (%lu bytes)]\n", *len);

  builder_res = sl_wisun_coap_builder(buf, packet);
  if (builder_res < 0) {
    printf("[Coap builder error: %s]\n",
           builder_res == -1 ? "Message Header structure" : "NULL ptr arg");
    sl_wisun_coap_free(packet);
    sl_wisun_mc_mutex_release(_coap_meter_hnd);
    return SL_STATUS_FAIL;
  }

  sl_wisun_coap_free(packet);

  sl_wisun_mc_mutex_release(_coap_meter_hnd);

  return SL_STATUS_OK;
}

#else

static const char *_meter_packet2json(const sl_wisun_meter_packet_t * const packet,
                                      const char *ip_str_global)
{
  static char buff[JSON_MEASUREMENT_DATA_SIZE] = { 0 };
  snprintf(buff,
           JSON_MEASUREMENT_DATA_SIZE,
           JSON_MEASUREMENT_FORMAT_STR,
           ip_str_global,
           packet->id,
           packet->temperature / 1000,
           (packet->temperature % 1000) / 10,
           packet->humidity / 1000,
           (packet->humidity % 1000) / 10,
           packet->light);
  return buff;
}

static sl_wisun_coap_packet_t *_prepare_measurement_resp(const sl_wisun_coap_packet_t * const req_packet,
                                                         const measurement_type_t measurement)
{
  sl_wisun_coap_packet_t * resp_packet  = NULL;
  sn_coap_content_format_e ct_format    = COAP_CT_JSON;
  size_t max_content_size               = 0U;
  static sl_wisun_app_core_current_addr_t addresses       = { 0 };
  const char *ip_str_global             = NULL;
  char *content                         = NULL;
  static sl_wisun_meter_packet_t packet = { 0 };

  // Init packet
  resp_packet = sl_wisun_coap_build_response(req_packet, COAP_MSG_CODE_RESPONSE_BAD_REQUEST);
  if (resp_packet == NULL) {
    return NULL;
  }

  if (measurement == COAP_METER_MEASUREMENT_ALL) {
    ct_format = COAP_CT_JSON;
    max_content_size = JSON_MEASUREMENT_DATA_SIZE;

    // Get IP address
    sl_wisun_app_core_get_current_addresses(&addresses);
    ip_str_global = app_wisun_trace_util_get_ip_str(&addresses.global);
  } else {
    ct_format = COAP_CT_TEXT_PLAIN;
    max_content_size = RHT_AND_LIGHT_MEAS_PLAIN_TXT_DATA_SIZE;
    // Allocate string buffer for particular sensor measurement
    content = sl_wisun_coap_malloc(RHT_AND_LIGHT_MEAS_PLAIN_TXT_DATA_SIZE);
  }

  // Measure all parameters
  if (measurement == COAP_METER_MEASUREMENT_ALL) {
    sl_wisun_meter_gen_packet_id(&packet);
    sl_wisun_meter_get_temperature(&packet);
    sl_wisun_meter_get_humidity(&packet);
    sl_wisun_meter_get_light(&packet);
    content = (char *)_meter_packet2json(&packet, ip_str_global);

    // Temperature measurement
  } else if (measurement == COAP_METER_MEASUREMENT_TEMPERATURE) {
    sl_wisun_meter_get_temperature(&packet);
    snprintf(content,
             max_content_size,
             "%lu.%lu Cdeg", packet.temperature / 1000,
             (packet.temperature % 1000) / 10);

    // Humidity measurement
  } else if (measurement == COAP_METER_MEASUREMENT_HUMIDITY) {
    sl_wisun_meter_get_humidity(&packet);
    snprintf(content,
             max_content_size,
             "%lu.%lu %%", packet.humidity / 1000,
             (packet.humidity % 1000) / 10);

    // Light measurement
  } else if (measurement == COAP_METER_MEASUREMENT_LIGHT) {
    sl_wisun_meter_get_light(&packet);
    snprintf(content,
             max_content_size,
             "%u lux", packet.light);
  }

  resp_packet->msg_code       = COAP_MSG_CODE_RESPONSE_CONTENT;
  resp_packet->content_format = ct_format;
  resp_packet->payload_ptr    = (uint8_t *) content;
  resp_packet->payload_len    = (uint16_t) sl_strnlen(content, max_content_size);
  return resp_packet;
}

static sl_wisun_led_id_t _coap_meter_convert_led_id(const uint8_t led_id)
{
  switch (led_id) {
    case SL_WISUN_METER_LED0: return SL_WISUN_LED0_ID;
    case SL_WISUN_METER_LED1: return SL_WISUN_LED1_ID;
    default:                  return SL_WISUN_LED_UNKNOW_ID;
  }
}
#endif

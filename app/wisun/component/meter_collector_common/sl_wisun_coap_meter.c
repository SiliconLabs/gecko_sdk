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

#if defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  #include "sl_wisun_rht_measurement.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// JSON formated measurement data maximum size
#define JSON_MEASUREMENT_DATA_SIZE                (100U)

/// Measurement plain text buffer size
#define RHT_AND_LIGHT_MEAS_PLAIN_TXT_DATA_SIZE    (32U)

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

/**************************************************************************//**
 * @brief Create formated json string from measurement packet
 * @details Use snprintf to static buffer
 * @param[in] packet packet
 * @return const char* pointer to the static buff
 *****************************************************************************/
static const char *_meter_packet2json(const sl_wisun_meter_packet_t *packet);

/**************************************************************************//**
 * @brief Prepare measurement by measurement type
 * @details Helper function
 * @param[in] req_packet Request packet
 * @param[in,out] resp_packet Response packet
 * @param[in] measurement Measurement type
 *****************************************************************************/
static void _prepare_measurement_resp(const sl_wisun_coap_packet_t * const req_packet,
                                      sl_wisun_coap_packet_t * const resp_packet,
                                      measurement_type_t measurement);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Internal CoAP Meter handler
static sl_wisun_meter_hnd_t _coap_meter_hnd = { 0 };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
void sl_wisun_coap_meter_init(void)
{
  // Init meter-collector common component
#if !defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  sl_wisun_meter_set_initializer(&_coap_meter_hnd, NULL);
#else
  sl_wisun_meter_set_initializer(&_coap_meter_hnd, sl_wisun_rht_init);
#endif
  sl_wisun_meter_init_hnd(&_coap_meter_hnd);
}

static void _prepare_measurement_resp(const sl_wisun_coap_packet_t * const req_packet,
                                      sl_wisun_coap_packet_t * const resp_packet,
                                      measurement_type_t measurement)
{
  sl_wisun_meter_packet_t packet     = { 0U }; // static packet
  char *content                      = NULL;   // Json content
  sl_wisun_coap_packet_t *tmp        = NULL;
  size_t max_content_size            = 0;
  sn_coap_content_format_e ct_format = COAP_CT_JSON;

  // Init packet
  tmp = sl_wisun_coap_build_response(req_packet, COAP_MSG_CODE_RESPONSE_BAD_REQUEST);
  if (tmp == NULL) {
    printf("[Failure: build response]\n");
    return;
  }
  memcpy(resp_packet, tmp, sizeof(sl_wisun_coap_packet_t));
  sl_wisun_coap_destroy_packet(tmp);

  if (req_packet->msg_code != COAP_MSG_CODE_REQUEST_GET) {
    printf("[Not valid measurement request]\n");
    return;
  }

  if (measurement == COAP_METER_MEASUREMENT_ALL) {
    ct_format = COAP_CT_JSON;
    max_content_size = JSON_MEASUREMENT_DATA_SIZE;
  } else {
    ct_format = COAP_CT_TEXT_PLAIN;
    max_content_size = RHT_AND_LIGHT_MEAS_PLAIN_TXT_DATA_SIZE;
    // allocate string buffer for particular sensor measurement
    content = sl_wisun_coap_malloc(RHT_AND_LIGHT_MEAS_PLAIN_TXT_DATA_SIZE);
  }

  // Measure all parameters
  if (measurement == COAP_METER_MEASUREMENT_ALL) {
    sl_wisun_meter_gen_packet_id(&packet);
    sl_wisun_meter_get_temperature(&packet);
    sl_wisun_meter_get_humidity(&packet);
    sl_wisun_meter_get_light(&packet);
    content = (char *)_meter_packet2json(&packet);

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

  resp_packet->msg_code         = COAP_MSG_CODE_RESPONSE_CONTENT;
  resp_packet->content_format   = ct_format;
  resp_packet->payload_ptr      = (uint8_t *) content;
  resp_packet->payload_len      = (uint16_t) sl_strnlen(content, max_content_size);
}

void sl_wisun_coap_meter_measurement_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                                 sl_wisun_coap_packet_t * const resp_packet)
{
  _prepare_measurement_resp(req_packet, resp_packet, COAP_METER_MEASUREMENT_ALL);
}

void sl_wisun_coap_meter_temperature_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                                 sl_wisun_coap_packet_t * const resp_packet)
{
  _prepare_measurement_resp(req_packet, resp_packet, COAP_METER_MEASUREMENT_TEMPERATURE);
}

void sl_wisun_coap_meter_humidity_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                              sl_wisun_coap_packet_t * const resp_packet)
{
  _prepare_measurement_resp(req_packet, resp_packet, COAP_METER_MEASUREMENT_HUMIDITY);
}

void sl_wisun_coap_meter_light_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                           sl_wisun_coap_packet_t * const resp_packet)
{
  _prepare_measurement_resp(req_packet, resp_packet, COAP_METER_MEASUREMENT_LIGHT);
}

void sl_wisun_coap_meter_led_toggle_response_cb(const sl_wisun_coap_packet_t * const req_packet,
                                                sl_wisun_coap_packet_t * const resp_packet)
{
  int8_t led_id = 0;
  sl_wisun_coap_packet_t *tmp     = NULL;

  // Init packet
  tmp = sl_wisun_coap_build_response(req_packet, COAP_MSG_CODE_RESPONSE_BAD_REQUEST);
  memcpy(resp_packet, tmp, sizeof(sl_wisun_coap_packet_t));
  sl_wisun_coap_destroy_packet(tmp);

  // Check request packet
  if (req_packet->msg_code != COAP_MSG_CODE_REQUEST_PUT) {
    printf("[Not valid measurement request]\n");
    return;
  }

  // Toggle LEDn
  led_id = (int8_t)sl_wisun_mc_get_led_id_from_payload((const char *)req_packet->payload_ptr);
  if (sl_wisun_led_toggle(sl_wisun_coap_meter_convert_led_id(led_id)) == SL_STATUS_FAIL) {
    printf("[LED Toggle failed: %d]\n", led_id);
    resp_packet->msg_code = COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE;
  } else {
    resp_packet->msg_code = COAP_MSG_CODE_RESPONSE_CHANGED;
  }
}

sl_wisun_led_id_t sl_wisun_coap_meter_convert_led_id(const uint8_t led_id)
{
  switch (led_id) {
    case SL_WISUN_METER_LED0: return SL_WISUN_LED0_ID;
    case SL_WISUN_METER_LED1: return SL_WISUN_LED1_ID;
    default:                  return SL_WISUN_LED_UNKNOW_ID;
  }
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static const char *_meter_packet2json(const sl_wisun_meter_packet_t *packet)
{
  static char buff[JSON_MEASUREMENT_DATA_SIZE] = { 0 };
  snprintf(buff, JSON_MEASUREMENT_DATA_SIZE,
           "  {\n    \"id\": %u,\n    \"temp\": %lu.%lu,\n    \"hum\": %lu.%lu,\n    \"lx\": %u\n  }\n",
           packet->id,
           packet->temperature / 1000,
           (packet->temperature % 1000) / 10,
           packet->humidity / 1000,
           (packet->humidity % 1000) / 10,
           packet->light);
  return buff;
}

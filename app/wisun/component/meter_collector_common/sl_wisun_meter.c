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
#include <stdio.h>
#include <string.h>
#include "em_device.h"
#include "sl_wisun_meter.h"
#include "sl_component_catalog.h"
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_trace_util.h"
#if defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  #include "sl_wisun_rht_measurement.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

#if !defined(SL_CATALOG_WISUN_COAP_PRESENT)
/**************************************************************************//**
 * @brief Measure parameters and send to the Collector (client).
 * @details Generate packet id, measure temperature, humidity and light
 * @param[in] sockd_meter socket id of meter (UDP server)
 * @param[in] collector_addr Collector address structure
 * @param[in] schedule request period in ms
 * @return true On success
 * @return false On error
 *****************************************************************************/
static bool sl_wisun_meter_meas_params_and_send(const int32_t sockd_meter,
                                                const sockaddr_in6_t *collector_addr,
                                                uint16_t schedule);
#endif
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Internal meter handler
static sl_wisun_meter_hnd_t _meter_hnd = { 0 };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
void sl_wisun_meter_init(void)
{
  // Init meter-collector common component
#if !defined(SL_CATALOG_TEMP_SENSOR_PRESENT)
  sl_wisun_meter_set_initializer(&_meter_hnd, NULL);
#else
  sl_wisun_meter_set_initializer(&_meter_hnd, sl_wisun_rht_init);
#endif
  sl_wisun_meter_init_hnd(&_meter_hnd);
}

/* Generate packet id */
SL_WEAK void sl_wisun_meter_gen_packet_id(sl_wisun_meter_packet_t *packet)
{
  static uint16_t id = 0;
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
  uint32_t dummy = 0;

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
  int32_t dummy = 0;

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

#if !defined(SL_CATALOG_WISUN_COAP_PRESENT)
void sl_wisun_meter_process(void)
{
  static uint8_t received_token[SL_WISUN_METER_COLLECTOR_TOKEN_MAX_SIZE] = { 0U };
  static wisun_addr_t meter_addr                           = { 0U };
  static wisun_addr_t collector_addr                       = { 0U };
  const char *collector_ip                                 = NULL;
  int32_t sockd_meter                                      = SOCKET_INVALID_ID;
  int32_t r                                                = SOCKET_RETVAL_ERROR;
  socklen_t len                                            = 0UL;
  uint16_t token_len                                       = 0U;
  uint16_t meter_schedule                                  = SL_WISUN_METER_DEFAULT_PERIOD_MS;
#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
  const sl_wisun_lfn_params_t *lfn_params                  = NULL;
#endif

  // init reference token
  sl_wisun_mc_init_token(SL_WISUN_METER_COLLECTOR_TOKEN);
  token_len = sl_wisun_mc_get_token_size();

  // getting the device schedule
#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
  lfn_params = app_wisun_get_lfn_params();
  if (lfn_params != NULL) {
    meter_schedule = lfn_params->data_layer.unicast_interval_ms;
  }
#endif

  // creating socket
  sockd_meter = socket(AF_WISUN, SOCK_DGRAM, IPPROTO_UDP);
  assert_res(sockd_meter, "Wi-SUN Meter socket()");

  // fill the server address structure
  meter_addr.sin6_family = AF_WISUN;
  meter_addr.sin6_addr = in6addr_any;
  meter_addr.sin6_port = htons(SL_WISUN_METER_PORT);

  // bind address to the socket
  r = bind(sockd_meter, (const struct sockaddr *) &meter_addr, sizeof(struct sockaddr_in6));
  assert_res(r, "Wi-SUN Meter bind()");

  len = sizeof(collector_addr);
  // receiver loop
  SL_WISUN_THREAD_LOOP {
    // receive token
    r = recvfrom(sockd_meter, received_token, token_len, 0,
                 (struct sockaddr *) &collector_addr, &len);

    if (r > 0) {
      // not valid address
      if (!memcmp(&collector_addr.sin6_addr, &in6addr_any, sizeof(in6addr_any))) {
        printf("[Not valid address received]\n");
        msleep(1);
        continue;
      }

      // compare token
      if (!sl_wisun_mc_compare_token(received_token, r)) {
        msleep(1);
        continue;
      }

      // if token matched, send measurement packet
      collector_ip = app_wisun_trace_util_get_ip_str(&collector_addr.sin6_addr);
      if (!sl_wisun_meter_meas_params_and_send(sockd_meter, &collector_addr, meter_schedule)) {
        printf("[%s: Measurement has NOT been sent]\n", collector_ip);
      } else {
        printf("[%s: Measurement packet has been sent (%d bytes)]\n",
               collector_ip, sizeof(sl_wisun_meter_packet_t));
      }
      app_wisun_trace_util_destroy_ip_str(collector_ip);
    }

    // dispatch thread
    msleep(1);
  }
}
#endif
// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

#if !defined(SL_CATALOG_WISUN_COAP_PRESENT)
/* measure and send packet */
static bool sl_wisun_meter_meas_params_and_send(const int32_t sockd_meter,
                                                const sockaddr_in6_t *collector_addr,
                                                uint16_t schedule)
{
  sl_wisun_meter_packet_t packet;
  sl_wisun_meter_packet_packed_t packed_packet;
  socklen_t len = sizeof(sockaddr_in6_t);
  wisun_addr_t dest = { 0 };
  bool res = true;
  sl_wisun_mc_mutex_acquire(_meter_hnd);
  // fill packet
  sl_wisun_meter_gen_packet_id(&packet);
  packet.schedule = schedule;
  sl_wisun_meter_get_temperature(&packet);
  sl_wisun_meter_get_humidity(&packet);
  sl_wisun_meter_get_light(&packet);

  // send to on meter socket to the collector
  sl_wisun_mc_pack_measurement_packet(&packed_packet, &packet);

  memcpy(&dest, collector_addr, sizeof(wisun_addr_t));
  dest.sin6_port = htons(SL_WISUN_COLLECTOR_PORT);
  if (sendto(sockd_meter, &packed_packet, sizeof(sl_wisun_meter_packet_packed_t), 0,
             (const struct sockaddr *) &dest, len) == -1) {
    res = false;
  }
  sl_wisun_mc_mutex_release(_meter_hnd);
  return res;
}
#endif

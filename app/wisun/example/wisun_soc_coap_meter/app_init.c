/***************************************************************************//**
 * @file
 * @brief Application init
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
#include <string.h>
#include "app_init.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_wisun_event_mgr.h"
#include "sl_wisun_coap_meter.h"
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_app_core_util_config.h"
#include "sl_wisun_coap_rhnd.h"
#include "sl_wisun_coap_meter_collector_config.h"
#include "app.h"
#include "app_custom_callback.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// CoAP Meter measurement resource type ALL
#define SL_WISUN_COAP_METER_RESOURCE_RT_ALL          "all"

/// CoAP Meter measurement resource type temperature
#define SL_WISUN_COAP_METER_RESOURCE_RT_TEMPERATURE  "temperature"

/// CoAP Meter measurement resource type humidity
#define SL_WISUN_COAP_METER_RESOURCE_RT_HUMIDITY     "humidity"

/// CoAP Meter measurement resource type light
#define SL_WISUN_COAP_METER_RESOURCE_RT_LIGHT        "light"

/// CoAP Meter measurement interface sensor
#define SL_WISUN_COAP_METER_RESOURCE_IF_SENSOR       "sensor"

/// CoAP Meter gpio resource type LED
#define SL_WISUN_COAP_METER_RESOURCE_RT_LED          "led"

/// CoAP Meter gpio interface
#define SL_WISUN_COAP_METER_RESOURCE_IF_LED          "gpio"

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
void app_init(void)
{
  sl_wisun_coap_rhnd_resource_t coap_resource = { 0 };

  // Init project info
  app_wisun_project_info_init("Wi-SUN CoAP Meter Application");

  // Init meter collector
  sl_wisun_coap_meter_init();

  // Init resource handler
  sl_wisun_coap_rhnd_init();

  // Init sensor all
  coap_resource.data.uri_path          = SL_WISUN_COAP_METER_COLLECTOR_MEASUREMENT_URI_PATH;
  coap_resource.data.resource_type     = SL_WISUN_COAP_METER_RESOURCE_RT_ALL;
  coap_resource.data.interface         = SL_WISUN_COAP_METER_RESOURCE_IF_SENSOR;
  coap_resource.auto_response          = sl_wisun_coap_meter_measurement_response_cb;
  coap_resource.discoverable           = true;
  assert(sl_wisun_coap_rhnd_resource_add(&coap_resource) == SL_STATUS_OK);

  // Init sensor temperature
  coap_resource.data.uri_path          = SL_WISUN_COAP_METER_COLLECTOR_TEMPERATURE_SENSOR_URI_PATH;
  coap_resource.data.resource_type     = SL_WISUN_COAP_METER_RESOURCE_RT_TEMPERATURE;
  coap_resource.data.interface         = SL_WISUN_COAP_METER_RESOURCE_IF_SENSOR;
  coap_resource.auto_response          = sl_wisun_coap_meter_temperature_response_cb;
  coap_resource.discoverable           = true;
  assert(sl_wisun_coap_rhnd_resource_add(&coap_resource) == SL_STATUS_OK);

  // Init sensor humidity
  coap_resource.data.uri_path          = SL_WISUN_COAP_METER_COLLECTOR_HUMIDITY_SENSOR_URI_PATH;
  coap_resource.data.resource_type     = SL_WISUN_COAP_METER_RESOURCE_RT_HUMIDITY;
  coap_resource.data.interface         = SL_WISUN_COAP_METER_RESOURCE_IF_SENSOR;
  coap_resource.auto_response          = sl_wisun_coap_meter_humidity_response_cb;
  coap_resource.discoverable           = true;
  assert(sl_wisun_coap_rhnd_resource_add(&coap_resource) == SL_STATUS_OK);

  // Init sensor light
  coap_resource.data.uri_path          = SL_WISUN_COAP_METER_COLLECTOR_LIGHT_SENSOR_URI_PATH;
  coap_resource.data.resource_type     = SL_WISUN_COAP_METER_RESOURCE_RT_LIGHT;
  coap_resource.data.interface         = SL_WISUN_COAP_METER_RESOURCE_IF_SENSOR;
  coap_resource.auto_response          = sl_wisun_coap_meter_light_response_cb;
  coap_resource.discoverable           = true;
  assert(sl_wisun_coap_rhnd_resource_add(&coap_resource) == SL_STATUS_OK);

  // Init led resource
  coap_resource.data.uri_path          = SL_WISUN_COAP_METER_COLLECTOR_LED_TOGGLE_URI_PATH;
  coap_resource.data.resource_type     = SL_WISUN_COAP_METER_RESOURCE_RT_LED;
  coap_resource.data.interface         = SL_WISUN_COAP_METER_RESOURCE_IF_LED;
  coap_resource.auto_response          = sl_wisun_coap_meter_led_toggle_response_cb;
  coap_resource.discoverable           = true;
  assert(sl_wisun_coap_rhnd_resource_add(&coap_resource) == SL_STATUS_OK);

  /* Register callbacks */
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_CONNECTED_IND_ID,
                                        app_custom_connected_callback);
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_SOCKET_DATA_IND_ID,
                                        app_custom_socket_data_callback);
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_SOCKET_DATA_SENT_IND_ID,
                                        app_custom_socket_data_sent_callback);

  /* Creating App main thread */
  const osThreadAttr_t app_task_attr = {
    .name        = "AppMain",
    .attr_bits   = osThreadDetached,
    .cb_mem      = NULL,
    .cb_size     = 0,
    .stack_mem   = NULL,
    .stack_size  = app_stack_size_word_to_byte(APP_MAIN_STACK_SIZE_WORD),
    .priority    = osPriorityNormal,
    .tz_module   = 0
  };
  osThreadId_t app_thr_id = osThreadNew(app_task,
                                        NULL,
                                        &app_task_attr);
  assert(app_thr_id != NULL);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

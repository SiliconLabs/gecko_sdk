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
#include "sl_component_catalog.h"
#include "app_init.h"
#include "sl_cmsis_os2_common.h"
#include "sl_wisun_app_core.h"
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_app_core_config.h"
#include "sl_wisun_network_measurement.h"
#include "sl_wisun_network_measurement_remote_ctrl.h"
#include "sl_wisun_network_measurement_stat.h"
#include "sl_wisun_event_mgr.h"
#include "app.h"
#include "app_custom_callback.h"
#include "sl_wisun_coap_rhnd.h"

#if defined(SL_CATALOG_GUI_PRESENT)
#include "sl_gui.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Network Measurement Remote CoAP Control CLI ping resource path
#define SL_WISUN_COAP_REMOTE_CTRL_PING_URI_PATH             "/cli/ping"

/// Network Measurement Remote CoAP Control CLI ping resource
#define SL_WISUN_COAP_REMOTE_CTRL_PING_RESOURCE_RT          "ping"

/// Network Measurement Remote CoAP Control CLI iperf resource path
#define SL_WISUN_COAP_REMOTE_CTRL_IPERF_URI_PATH            "/cli/iperf"

/// Network Measurement Remote CoAP Control CLI iperf resource
#define SL_WISUN_COAP_REMOTE_CTRL_IPERF_RESOURCE_RT         "iperf"

/// Network Measurement Remote CoAP Control CLI neighbour info resource path
#define SL_WISUN_COAP_REMOTE_CTRL_NBR_INFO_URI_PATH         "/cli/nbrinfo"

/// Network Measurement Remote CoAP Control CLI iperf resource
#define SL_WISUN_COAP_REMOTE_CTRL_NBR_INFO_RESOURCE_RT      "nbrinfo"

/// Network Measurement Remote CoAP Control CLI interface
#define SL_WISUN_COAP_REMOTE_CTRL_RESOURCE_IF_CLI           "cli"

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
  sl_wisun_app_core_util_project_info_init("Wi-SUN Network Measurement Application");

#if defined(SL_CATALOG_GUI_PRESENT)
  // Init display
  sl_display_init();

  // Init GUI
  sl_gui_init();
#endif

  // Init cli ping resource
  coap_resource.data.uri_path          = SL_WISUN_COAP_REMOTE_CTRL_PING_URI_PATH;
  coap_resource.data.resource_type     = SL_WISUN_COAP_REMOTE_CTRL_PING_RESOURCE_RT;
  coap_resource.data.interface         = SL_WISUN_COAP_REMOTE_CTRL_RESOURCE_IF_CLI;
  coap_resource.auto_response          = sl_wisun_coap_remote_cli_ping_cb;
  coap_resource.discoverable           = true;
  assert(sl_wisun_coap_rhnd_resource_add(&coap_resource) == SL_STATUS_OK);

  // Init iperf ping resource
  coap_resource.data.uri_path          = SL_WISUN_COAP_REMOTE_CTRL_IPERF_URI_PATH;
  coap_resource.data.resource_type     = SL_WISUN_COAP_REMOTE_CTRL_IPERF_RESOURCE_RT;
  coap_resource.data.interface         = SL_WISUN_COAP_REMOTE_CTRL_RESOURCE_IF_CLI;
  coap_resource.auto_response          = sl_wisun_coap_remote_cli_iperf_cb;
  coap_resource.discoverable           = true;
  assert(sl_wisun_coap_rhnd_resource_add(&coap_resource) == SL_STATUS_OK);

  // Init nbr info resource
  coap_resource.data.uri_path          = SL_WISUN_COAP_REMOTE_CTRL_NBR_INFO_URI_PATH;
  coap_resource.data.resource_type     = SL_WISUN_COAP_REMOTE_CTRL_NBR_INFO_RESOURCE_RT;
  coap_resource.data.interface         = SL_WISUN_COAP_REMOTE_CTRL_RESOURCE_IF_CLI;
  coap_resource.auto_response          = sl_wisun_coap_remote_cli_nbr_cb;
  coap_resource.discoverable           = true;
  assert(sl_wisun_coap_rhnd_resource_add(&coap_resource) == SL_STATUS_OK);

  // Register callbacks
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_CONNECTED_IND_ID,
                                        app_custom_connected_callback);
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_SOCKET_DATA_IND_ID,
                                        app_custom_socket_data_callback);
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_SOCKET_DATA_SENT_IND_ID,
                                        app_custom_socket_data_sent_callback);
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_JOIN_STATE_IND_ID,
                                        app_custom_join_state_callback);
  app_wisun_em_custom_callback_register(SL_WISUN_MSG_REGULATION_TX_LEVEL_IND_ID,
                                        app_custom_regulation_tx_level_callback);

  // Creating App main thread
  const osThreadAttr_t app_task_attr = {
    .name        = "AppMain",
    .attr_bits   = osThreadDetached,
    .cb_mem      = NULL,
    .cb_size     = 0,
    .stack_mem   = NULL,
    .stack_size  = app_stack_size_word_to_byte(SL_WISUN_APP_CORE_MAIN_STACK_SIZE_WORD),
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

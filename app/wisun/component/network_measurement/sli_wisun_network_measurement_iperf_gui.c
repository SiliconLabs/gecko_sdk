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
#include <inttypes.h>
#include <assert.h>

#include "sl_status.h"
#include "sl_iperf.h"
#include "sl_iperf_types.h"
#include "sl_sleeptimer.h"
#include "sl_component_catalog.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_app_core.h"
#include "sl_wisun_app_setting.h"
#include "sl_wisun_network_measurement_gui.h"
#include "sli_wisun_network_measurement_iperf_gui.h"
#include "sl_wisun_network_measurement.h"
#include "sl_wisun_network_measurement_config.h"
#include "sl_display.h"
#include "sl_gui.h"
#include "socket.h"
#include "sl_wisun_ping.h"
#include "silabs_wisun_logo.h"
#include "sl_wisun_network_measurement_stat.h"
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

#define MAX_BANDWIDTH_OPTIONS         (6U)
#define MAX_DURATION_OPTIONS          (4U)
#define MAX_INTERVAL_OPTIONS          (4U)
#define STR_BUFF_SIZE                 (1024)

#define MAX_NODE_STRING_LEN           (20)

#define NODE_PRIMARY_PARENT_STR       "Primary Parent"
#define NODE_SECONDARY_PARENT_STR     "Secondary Parent"

#define DEFAULT_BANDWIDTH_KBITS       (20)

/// Print iperf server settings format string
#define IPERF_START_STAT_FORMAT_STR \
  "Port: %u\n\
Remote Address: %s\n\
Bandwidth:  %lu\n\
Buffer Length: %u\n\
Duration: %u\n\
Interval: %u\n"

/// Print neighbor statistic format string
#define IPERF_RESULT_STAT_FORMAT_STR \
  "nbr_calls:\n%lu\n\
bytes:\n%lu\n\
tot_packets:\n%lu\n\
nbr_rcv_snt_packets:\n%lu\n\
errs:\n%lu\n\
transitory_error_cnts:\n%lu\n\
last_recv_pkt_cnt:\n%lu\n\
ts_curr_recv_ms:\n%llu\n\
ts_prev_recv_ms:\n%llu\n\
ts_curr_sent_ms:\n%llu\n\
ts_prev_sent_ms:\n%llu\n\
udp_jitter:\n%lld\n\
udp_rx_last_pkt:\n%lu\n\
udp_lost_pkt:\n%lu\n\
udp_out_of_order:\n%lu\n\
udp_dup_pkt:\n%lu\n\
udp_async_error:\n%d\n\
end_err:\n%d\n\
ts_start_ms:\n%llu\n\
ts_end_ms:\n%llu\n\
bandwidth:\n%lu\n\
finack_tot_len:\n%lu\n\
finack_duration_ms:\n%llu\n\
finack_pkt:\n%lu\n"

/// Remote address structure
typedef struct remote_addr{
  char node_str[MAX_NODE_STRING_LEN];
  char addr_str[SL_IPERF_IP_STR_BUFF_LEN];
} remote_addr_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief iPerf settings main form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_setting_main_form(void *args);

/**************************************************************************//**
 * @brief Port info form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_info_port_form(void *args);

/**************************************************************************//**
 * @brief Remote address setting form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_setting_remote_addr(void *args);

/**************************************************************************//**
 * @brief Bandwidth setting form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_setting_bandwidth_form(void *args);

/**************************************************************************//**
 * @brief Bandwidth setting helper
 * @details Helper function
 * @param[in] args Arguments
 *****************************************************************************/
static void _set_bandwidth(void *args);

/**************************************************************************//**
 * @brief Bandwidth format info form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_info_bw_format_form(void *args);

/**************************************************************************//**
 * @brief Buffer length info form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_setting_buff_len_form(void *args);

/**************************************************************************//**
 * @brief Duration setting form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_setting_duration_form(void *args);

/**************************************************************************//**
 * @brief Duration setting helper
 * @details Helper function
 * @param[in] args Arguments
 *****************************************************************************/
static void _set_duration(void *args);

/**************************************************************************//**
 * @brief Interval setting form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_setting_interval_form(void *args);

/**************************************************************************//**
 * @brief Interval setting helper
 * @details Helper function
 * @param[in] args Arguments
 *****************************************************************************/
static void _set_interval(void *args);

/**************************************************************************//**
 * @brief Main server client form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_server_client_main_form(void *args);

/**************************************************************************//**
 * @brief Iperf start measurement helper
 * @details Helper function
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_start(void *args);

/**************************************************************************//**
 * @brief Client mode set helper
 * @details Helper function
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_set_client(void *args);

/**************************************************************************//**
 * @brief Server mode set helper
 * @details Helper function
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_set_server(void *args);

/**************************************************************************//**
 * @brief Results info form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _iperf_result_form(void *args);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// String internal buffer allocation
static char _str_buff[STR_BUFF_SIZE] = { 0 };

/// bandwidth options
static const app_enum_t _bandwidth_options[MAX_BANDWIDTH_OPTIONS] = {
  { .value_str = "1", .value = 1U },
  { .value_str = "5", .value = 5U },
  { .value_str = "10", .value = 10U },
  { .value_str = "15", .value = 15U },
  { .value_str = "20", .value = 20U },
  { .value_str = "25", .value = 25U }
};

/// duration options
static const app_enum_t _duration_options[MAX_DURATION_OPTIONS] = {
  { .value_str = "5", .value = 5U },
  { .value_str = "10", .value = 10U },
  { .value_str = "20", .value = 20U },
  { .value_str = "30", .value = 30U }
};

/// interval options
static const app_enum_t _interval_options[MAX_INTERVAL_OPTIONS] = {
  { .value_str = "1", .value = 1U },
  { .value_str = "2", .value = 2U },
  { .value_str = "5", .value = 5U },
  { .value_str = "10", .value = 10U }
};

/// iperf structure with default settings of options
static sl_iperf_opt_t _options = {
  .bandwidth   = DEFAULT_BANDWIDTH_KBITS,
  .bw_format   = SL_IPERF_OPT_BW_FORMAT_KBITS_PER_SEC,
  .interval_ms = SL_IPERF_DEFAULT_INTERVAL_MS,
  .mode        = SL_IPERF_MODE_SERVER,
  .protocol    = SL_IPERF_IPROTOV6_UDP,
  .port        = SL_IPERF_SERVER_DEFAULT_PORT,
  .duration_ms = SL_IPERF_CLIENT_DEFAULT_SEND_TIME_MS,
  .buf_len     = SL_IPERF_BUFFER_SIZE
};

static sl_iperf_test_t _last_test = { 0U };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void sli_wisun_nwm_iperf_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();

  sl_gui_title_set_label("iPerf2 Measurement");
  sl_gui_title_update();
  sl_gui_optionlist_add_item("Back", sl_wisun_nwm_main_form, NULL);
  sl_gui_optionlist_add_item("Server", _iperf_set_server, NULL);
  sl_gui_optionlist_add_item("Client", _iperf_set_client, NULL);
  sl_gui_optionlist_add_item("Settings", _iperf_setting_main_form, NULL);
  sl_gui_optionlist_add_item("Last result", _iperf_result_form, NULL);
  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static void _iperf_server_client_main_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();

  if (_options.mode == SL_IPERF_MODE_SERVER) {
    sl_gui_title_set_label("iPerf2 Server");
  } else {
    sl_gui_title_set_label("iPerf2 Client");
  }

  sl_gui_title_update();

  sl_gui_textbox_init();
  snprintf(_str_buff, STR_BUFF_SIZE, IPERF_START_STAT_FORMAT_STR,
           _options.port,
           _options.remote_addr,
           _options.bandwidth,
           //_options.bw_format,
           _options.buf_len,
           _options.duration_ms / 100U,
           _options.interval_ms / 100U);
  sl_gui_textbox_set(_str_buff);
  sl_gui_textbox_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Start");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Back");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, _iperf_start, NULL);
  sl_gui_button_set_callback(SL_GUI_BUTTON0, sli_wisun_nwm_iperf_form, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

static void _iperf_result_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();
  sl_gui_title_set_label("iPerf2 Result");
  sl_gui_title_update();
  sl_gui_textbox_init();

  snprintf(_str_buff, STR_BUFF_SIZE, IPERF_RESULT_STAT_FORMAT_STR,
           _last_test.statistic.nbr_calls,
           _last_test.statistic.bytes,
           _last_test.statistic.tot_packets,
           _last_test.statistic.nbr_rcv_snt_packets,
           _last_test.statistic.errs,
           _last_test.statistic.transitory_error_cnts,
           _last_test.statistic.last_recv_pkt_cnt,
           _last_test.statistic.ts_curr_recv_ms,
           _last_test.statistic.ts_prev_recv_ms,
           _last_test.statistic.ts_curr_recv_ms,
           _last_test.statistic.ts_curr_sent_ms,
           _last_test.statistic.udp_jitter,
           _last_test.statistic.udp_rx_last_pkt,
           _last_test.statistic.udp_lost_pkt,
           _last_test.statistic.udp_out_of_order,
           _last_test.statistic.udp_dup_pkt,
           _last_test.statistic.udp_async_error,
           _last_test.statistic.end_err,
           _last_test.statistic.ts_start_ms,
           _last_test.statistic.ts_end_ms,
           _last_test.statistic.bandwidth,
           _last_test.statistic.finack_tot_len,
           _last_test.statistic.finack_duration_ms,
           _last_test.statistic.finack_pkt
           );
  sl_gui_textbox_set(_str_buff);
  sl_gui_textbox_update();

  sl_gui_button_set_label(SL_GUI_BUTTON0, "Back");
  sl_gui_button_set_callback(SL_GUI_BUTTON0, sli_wisun_nwm_iperf_form, NULL);
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_txt_box, NULL);

  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_display_update();
}

static void _iperf_setting_main_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();
  sl_gui_title_set_label("iPerf2 Setting");
  sl_gui_title_update();
  sl_gui_optionlist_add_item("Back", sli_wisun_nwm_iperf_form, NULL);
  sl_gui_optionlist_add_item("Port (ro)", _iperf_info_port_form, NULL);
  sl_gui_optionlist_add_item("Remote Address", sli_wisun_neighbors_select_form,
                             (sl_widget_event_args_t)_iperf_setting_remote_addr);
  sl_gui_optionlist_add_item("Bandwidth", _iperf_setting_bandwidth_form, NULL);
  sl_gui_optionlist_add_item("Bandwidth Format (ro)", _iperf_info_bw_format_form, NULL);
  sl_gui_optionlist_add_item("Buffer Length (ro)", _iperf_setting_buff_len_form, NULL);
  sl_gui_optionlist_add_item("Duration", _iperf_setting_duration_form, NULL);
  sl_gui_optionlist_add_item("Interval", _iperf_setting_interval_form, NULL);
  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

static void _iperf_info_port_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();
  sl_gui_title_set_label("Port");
  sl_gui_title_update();

  sl_gui_textbox_init();
  sl_gui_textbox_set("5001");
  sl_gui_textbox_update();

  sl_gui_button_set_label(SL_GUI_BUTTON0, "Back");
  sl_gui_button_set_callback(SL_GUI_BUTTON0, _iperf_setting_main_form, NULL);
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_txt_box, NULL);

  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_gui_button_update(SL_GUI_BUTTON0);

  sl_display_update();
}

static void _iperf_setting_remote_addr(void *args)
{
  sl_wisun_nwm_node_stat_t *stat = (sl_wisun_nwm_node_stat_t *) args;
  const char *ip_str             = NULL;

  ip_str = app_wisun_trace_util_get_ip_str(&stat->addr.sin6_addr);
  memcpy(_options.remote_addr, ip_str, SL_IPERF_IP_STR_BUFF_LEN);
  sl_display_renderer(_iperf_setting_main_form, NULL, 0);
  app_wisun_trace_util_destroy_ip_str(ip_str);
}

static void _iperf_setting_bandwidth_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();
  snprintf(_str_buff, STR_BUFF_SIZE, "Bandwidth %d [Kbits/s]", _options.duration_ms);
  sl_gui_title_set_label(_str_buff);
  sl_gui_title_update();
  for (uint8_t i = 0; i < MAX_BANDWIDTH_OPTIONS; i++) {
    sl_gui_optionlist_add_item(_bandwidth_options[i].value_str,
                               _set_bandwidth,
                               (void *)&_bandwidth_options[i].value);
  }
  sl_gui_optionlist_add_item("Back", _iperf_setting_main_form, NULL);
  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

static void _set_bandwidth(void *args)
{
  _options.bandwidth = *(uint32_t *)args;
  sl_display_renderer(_iperf_setting_main_form, NULL, 0);
}

static void _iperf_info_bw_format_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();
  sl_gui_title_set_label("Bandwidth Format (ro)");
  sl_gui_title_update();

  sl_gui_textbox_init();
  sl_gui_textbox_set("Kbits/s");
  sl_gui_textbox_update();

  sl_gui_button_set_label(SL_GUI_BUTTON0, "Back");
  sl_gui_button_set_callback(SL_GUI_BUTTON0, _iperf_setting_main_form, NULL);
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_txt_box, NULL);

  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_gui_button_update(SL_GUI_BUTTON0);

  sl_display_update();
}

static void _iperf_setting_buff_len_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();
  sl_gui_title_set_label("Buffer Length [byte]");
  sl_gui_title_update();

  sl_gui_textbox_init();
  sl_gui_textbox_set("1234 bytes");
  sl_gui_textbox_update();

  sl_gui_button_set_label(SL_GUI_BUTTON0, "Back");
  sl_gui_button_set_callback(SL_GUI_BUTTON0, _iperf_setting_main_form, NULL);
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_txt_box, NULL);

  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_gui_button_update(SL_GUI_BUTTON0);

  sl_display_update();
}

static void _iperf_setting_duration_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();
  snprintf(_str_buff, STR_BUFF_SIZE, "Duration %d [s]", _options.duration_ms);
  sl_gui_title_set_label(_str_buff);
  sl_gui_title_update();
  for (uint8_t i = 0; i < MAX_DURATION_OPTIONS; i++) {
    sl_gui_optionlist_add_item(_duration_options[i].value_str,
                               _set_duration,
                               (void *)&_duration_options[i].value);
  }
  sl_gui_optionlist_add_item("Back", _iperf_setting_main_form, NULL);
  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

static void _set_duration(void *args)
{
  _options.duration_ms = *(uint16_t *)args;
  sl_display_renderer(_iperf_setting_main_form, NULL, 0);
}

static void _iperf_setting_interval_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();
  snprintf(_str_buff, STR_BUFF_SIZE, "Interval %d [s]", _options.interval_ms);
  sl_gui_title_set_label(_str_buff);
  sl_gui_title_update();
  for (uint8_t i = 0; i < MAX_INTERVAL_OPTIONS; i++) {
    sl_gui_optionlist_add_item(_interval_options[i].value_str,
                               _set_interval,
                               (void *)&_interval_options[i].value);
  }
  sl_gui_optionlist_add_item("Back", _iperf_setting_main_form, NULL);
  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}
static void _set_interval(void *args)
{
  _options.interval_ms = *(uint16_t *)args;
  sl_display_renderer(_iperf_setting_main_form, NULL, 0);
}

static void _iperf_set_client(void *args)
{
  (void) args;
  _options.mode = SL_IPERF_MODE_CLIENT;
  printf("\nOptions.mode set: %d\n", _options.mode);
  sl_display_renderer(_iperf_server_client_main_form, NULL, 0);
}

static void _iperf_set_server(void *args)
{
  (void) args;
  _options.mode = SL_IPERF_MODE_SERVER;
  sl_display_renderer(_iperf_server_client_main_form, NULL, 0);
}

static void _iperf_start(void *args)
{
  (void) args;
  sl_iperf_test_t test = { 0U };
  _options.protocol = SL_IPERF_IPROTOV6_UDP;
  // start timer
  sl_gui_init_all_widget();
  if (_options.mode == SL_IPERF_MODE_SERVER) {
    sl_gui_title_set_label("Server running...");
  } else {
    sl_gui_title_set_label("Client running...");
  }
  sl_gui_title_update();
  sl_gui_textbox_init();
  snprintf(_str_buff, STR_BUFF_SIZE, IPERF_START_STAT_FORMAT_STR,
           _options.port,
           _options.remote_addr,
           _options.bandwidth,
           //_options.bw_format,
           _options.buf_len,
           _options.duration_ms / 100U,
           _options.interval_ms / 100U);
  sl_gui_textbox_set(_str_buff);
  sl_gui_textbox_update();
  sl_display_update();
  // init test
  sl_iperf_test_init(&test, _options.mode, _options.protocol);
  // set stored options
  memcpy(&test.opt, &_options, sizeof(sl_iperf_opt_t));
  printf("Start iperf");
  // adds the test to the queue
  if (!sl_iperf_test_add(&test)) {
    printf("[Adding test to queue failed]\n");
    return;
  }
  if (!sl_iperf_test_get(&_last_test)) {
    printf("[Getting test to queue failed]\n");
    return;
  }
  sl_gui_title_set_label("Done");
  sl_gui_title_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Back");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_nwm_iperf_form, NULL);
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Result");
  sl_gui_button_set_callback(SL_GUI_BUTTON0, _iperf_result_form, NULL);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_display_update();
}

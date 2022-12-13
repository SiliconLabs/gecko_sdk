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
#include "sl_component_catalog.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_app_core.h"
#include "sl_wisun_app_setting.h"
#include "sl_wisun_network_measurement_gui.h"
#include "sli_wisun_network_measurement_iperf_gui.h"
#include "sli_wisun_network_measurement_ping_gui.h"
#include "sli_wisun_network_measurement_settings_gui.h"
#include "sl_wisun_network_measurement.h"
#include "sl_wisun_network_measurement_config.h"
#include "sl_display.h"
#include "sl_gui.h"
#include "socket.h"
#include "sl_wisun_ping.h"
#include "silabs_wisun_logo.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Internal string buffer size
#define STR_BUFF_SIZE                   (512U)

/// Max Packet count option size
#define MAX_PACKET_COUNT_OPTION         (7U)

/// Max Packet length option size
#define MAX_PACKET_LENGTH_OPTION        (8U)

/// Max Measurement type option size
#define MAX_MEAS_TYPE_OPTION            (3U)

/// Max regulatory domain count
#define MAX_REG_DOMAIN_COUNT            (16U)

/// Max networ size count
#define MAX_NETWORK_SIZE_COUNT          (6U)

/// TX remaining string "exceeded"
#define TX_REMAINING_EXCEEDED_STR       "[Exceeded]"

/// TX remaining string "remaining"
#define TX_REMAINING_REMAINING_STR      "[Remaining]"

/// TX remaining string "not available"
#define TX_REMAINING_NOT_AVAILABLE_STR  "[Not available]"

/// Print Statistic format string
#define PRINT_FULL_STAT_FORMAT_STR \
  "[%s]\n\
Packets:       %u\n\
Packet length: %u\n\
Lost packets:  %u\n\
Packet loss:   %u%%\n\
Min. Time[ms]: %lu\n\
Max. Time[ms]: %lu\n\
Avg. Time[ms]: %lu\n\
lifetime:      %lu\n\
mac_tx_count:  %lu\n\
mac_tx_fail:   %lu\n\
mac_tx_ms_cnt: %lu\n\
mac_tx_ms_fail:%lu\n\
rpl_rank:      %u\n\
etx:           %u\n\
rsl_out:       %u\n\
rsl_in:        %u\n"

/// Print neighbor statistic format string
#define PRINT_NEIGHBOR_STAT_FORMAT_STR \
  "[%s]\n\
lifetime:      %lu\n\
mac_tx_count:  %lu\n\
mac_tx_fail:   %lu\n\
mac_tx_ms_cnt: %lu\n\
mac_tx_ms_fail:%lu\n\
rpl_rank:      %u\n\
etx:           %u\n\
rsl_out:       %u\n\
rsl_in:        %u\n"

/// Print ping statistic format string
#define PRINT_PING_STAT_FORMAT_STR \
  "[%s]\n\
Packets:       %u\n\
Packet length: %u\n\
Lost packets:  %u\n\
Packet loss:   %u%%\n\
Min. Time[ms]: %lu\n\
Max. Time[ms]: %lu\n\
Avg. Time[ms]: %lu\n"

/// Print Node Info format string for FAN1.0
#define PRINT_FAN10_NODE_INFO_FORMAT_STR \
  "Network Name:\n%s\n\
Nw. size: %s(%d)\n\
TX Power: %d\n\
Profile: %s\n\
Reg. domain: %s(%d)\n\
Op. class: %d\n\
Op. mode: 0x%x\n\
Global:\n[%s]\n\
Border Router:\n[%s]\n\
Primary Parent:\n[%s]\n\
Secondary Parent:\n[%s]\n\
TX budget: %lums\n%s\n"

/// Print Node Info format string for FAN1.1
#define PRINT_FAN11_NODE_INFO_FORMAT_STR \
  "Network Name:\n%s\n\
Nw. size: %s(%d)\n\
TX Power: %d\n\
Profile: %s\n\
Reg. domain: %s(%d)\n\
Ch. Plan ID: %d\n\
Phy Mode ID: %d\n\
Global:\n[%s]\n\
Border Router:\n[%s]\n\
Primary Parent:\n[%s]\n\
Secondary Parent:\n[%s]\n\
TX budget: %lums\n%s\n"

/// Network Measurement settings structure
typedef struct sl_wisun_nwm_setting {
  /// Packet count
  uint16_t packet_count;
  /// Packet length
  uint16_t packet_length;
  /// Measurement type
  sl_wisun_nwm_target_type_t meas_type;
} sl_wisun_nwm_setting_t;

/// Node info structure type definition
typedef struct node_info {
  /// Addresses
  current_addr_t addresses;
  /// Settings
  app_setting_wisun_t settings;
} node_info_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Node info form
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _node_info_form(void *args);

/**************************************************************************//**
 * @brief Set neighbor info textbox
 * @details Form renderer
 * @param[in] args Arguments
 *****************************************************************************/
static void _set_nbinfo_txtbox(void *args);

/**************************************************************************//**
 * @brief Get the tx remaining budget string
 * @param[in] tx_remaining_budget TX remianing budget
 *****************************************************************************/
static inline const char* _tx_remaining_budget(const uint32_t tx_remaining_budget);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// String internal buffer allocation
static char _str_buff[STR_BUFF_SIZE] = { 0 };

/// Primary Parent temp statistic storage
static sl_wisun_nwm_node_stat_t _primary_parent_stat;

/// Secondary Parent temp statistic storage
static sl_wisun_nwm_node_stat_t _secondary_parent_stat;

/// Children temp statistic storage
static sl_wisun_nwm_node_stat_t _children_stat[SL_WISUN_MAX_CHILDREN_COUNT];

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void sli_wisun_nwm_logo_form(void *args)
{
  sl_wisun_nwm_logo_form_args_t *logo_form_args = (sl_wisun_nwm_logo_form_args_t *)args;
  static char buff[4U] = { 0 };

  sl_display_draw_bitmap(0, 0,
                         SILABS_WISUN_LOGO_WIDTH,
                         SILABS_WISUN_LOGO_HEIGHT,
                         silabs_wisun_logo_bits);
  sl_display_draw_string_on_line(logo_form_args->network_name, 2, GLIB_ALIGN_CENTER, 0, 0, false);
  sl_display_draw_string_on_line(logo_form_args->join_state_str, 10, GLIB_ALIGN_CENTER, 0, 0, false);
  snprintf(buff, 4U, "(%ld)", logo_form_args->join_state);
  sl_display_draw_string_on_line(buff, 11, GLIB_ALIGN_CENTER, 0, 0, false);
}

void sl_wisun_nwm_main_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();

  sl_gui_title_set_label("Network Measurement");
  sl_gui_title_update();
  sl_gui_optionlist_add_item("Ping", sli_wisun_nwm_ping_form, NULL);
  sl_gui_optionlist_add_item("iPerf", sli_wisun_nwm_iperf_form, NULL);
  sl_gui_optionlist_add_item("Node info", _node_info_form, NULL);
  sl_gui_optionlist_add_item("Neighbors info", sli_wisun_neighbors_select_form,
                             (sl_widget_event_args_t)_set_nbinfo_txtbox);
  sl_gui_optionlist_add_item("Settings", sli_wisun_settings_form, NULL);
  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

void sli_wisun_settings_form(void *args)
{
  (void) args;
  sl_gui_init_all_widget();

  sl_gui_title_set_label("Settings");
  sl_gui_title_update();
  sl_gui_optionlist_add_item("Back", sl_wisun_nwm_main_form, NULL);
  sl_gui_optionlist_add_item("PHY", sli_wisun_nwm_phy_select_form, NULL);

  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

void sli_wisun_scroll_optionlist_and_set_select(void *args)
{
  (void) args;
  sl_gui_optionlist_scroll_down();
  sl_gui_optionlist_update();
  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_display_update();
}

void sli_wisun_scroll_txt_box(void *args)
{
  (void) args;
  sl_gui_textbox_scroll_down();
  sl_gui_textbox_update();
  sl_display_update();
}

void sli_wisun_neighbors_select_form(void *args)
{
  sl_widget_event_callback_t callback = (sl_widget_event_callback_t) args;
  bool parent_available = false;
  uint8_t children_count = 0;

  (void) args;
  sl_gui_init_all_widget();

  sl_gui_title_set_label("Neighbors");
  sl_gui_title_update();

  sl_wisun_nwm_get_nodes(NULL, 0);

  parent_available = sl_wisun_nwm_get_primary_parent_stat(&_primary_parent_stat);

  sl_wisun_nwm_get_children_stat(_children_stat,
                                 sizeof(_children_stat) / sizeof(sl_wisun_nwm_node_stat_t),
                                 &children_count);

  sl_gui_optionlist_add_item("Back to Main Menu", sl_wisun_nwm_main_form, NULL);

  if (parent_available) {
    sl_gui_optionlist_add_item("Primary Parent",
                               callback,
                               (void *)&_primary_parent_stat);
  }

  parent_available = sl_wisun_nwm_get_secondary_parent_stat(&_secondary_parent_stat);

  if (parent_available) {
    sl_gui_optionlist_add_item("Secondary Parent",
                               callback,
                               (void *)&_secondary_parent_stat);
  }

  if (children_count) {
    for (uint8_t i = 0; i < children_count; ++i) {
      sl_gui_optionlist_add_item(_children_stat[i].name,
                                 callback,
                                 (void *)&_children_stat[i]);
    }
  }

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

static void _node_info_form(void *args)
{
  static node_info_t node_info = { 0U };
  const char *ip_str_global    = NULL;
  const char *ip_str_br        = NULL;
  const char *ip_str_pp        = NULL;
  const char *ip_str_sp        = NULL;
  uint32_t tx_remaining_budget = 0UL; // Hold the remaning TX budget if applicable
  bool valid                   = false; // Indicates if the remaining budget returned is a usable value.

  (void) args;

  sl_gui_title_set_label("Node Info");

  sl_gui_title_update();
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Back");
  sl_gui_button_set_callback(SL_GUI_BUTTON0, sl_wisun_nwm_main_form, NULL);
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_txt_box, NULL);

  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_gui_button_update(SL_GUI_BUTTON0);

  // getting IP addresses
  app_wisun_get_current_addresses(&node_info.addresses);

  // getting settings
  app_wisun_setting_get(&node_info.settings);

  // get remanining transmission budget if applicable
  if ( app_wisun_get_regulation_active() == true ) {
    valid = app_wisun_get_remaining_tx_budget(&tx_remaining_budget);
  }

  ip_str_global = app_wisun_trace_util_get_ip_str(&node_info.addresses.global);
  ip_str_br = app_wisun_trace_util_get_ip_str(&node_info.addresses.border_router);
  ip_str_pp = app_wisun_trace_util_get_ip_str(&node_info.addresses.primary_parent);
  ip_str_sp = app_wisun_trace_util_get_ip_str(&node_info.addresses.secondary_parent);

  if (node_info.settings.phy.type == SL_WISUN_PHY_CONFIG_FAN10) {
    snprintf(_str_buff, STR_BUFF_SIZE,
             PRINT_FAN10_NODE_INFO_FORMAT_STR,
             node_info.settings.network_name,
             app_wisun_trace_util_nw_size_to_str(node_info.settings.network_size),
             node_info.settings.network_size,
             node_info.settings.tx_power,
             app_wisun_trace_util_phy_cfg_type_to_str(node_info.settings.phy.type),
             app_wisun_trace_util_reg_domain_to_str(node_info.settings.phy.config.fan10.reg_domain),
             node_info.settings.phy.config.fan10.reg_domain,
             node_info.settings.phy.config.fan10.op_class,
             node_info.settings.phy.config.fan10.op_mode,
             ip_str_global,
             ip_str_br,
             ip_str_pp,
             ip_str_sp,
             (valid ? tx_remaining_budget : 0UL),
             (valid ? _tx_remaining_budget(tx_remaining_budget) : TX_REMAINING_NOT_AVAILABLE_STR));
  } else if (node_info.settings.phy.type == SL_WISUN_PHY_CONFIG_FAN11) {
    snprintf(_str_buff, STR_BUFF_SIZE,
             PRINT_FAN11_NODE_INFO_FORMAT_STR,
             node_info.settings.network_name,
             app_wisun_trace_util_nw_size_to_str(node_info.settings.network_size),
             node_info.settings.network_size,
             node_info.settings.tx_power,
             app_wisun_trace_util_phy_cfg_type_to_str(node_info.settings.phy.type),
             app_wisun_trace_util_reg_domain_to_str(node_info.settings.phy.config.fan11.reg_domain),
             node_info.settings.phy.config.fan11.reg_domain,
             node_info.settings.phy.config.fan11.chan_plan_id,
             node_info.settings.phy.config.fan11.phy_mode_id,
             ip_str_global,
             ip_str_br,
             ip_str_pp,
             ip_str_sp,
             (valid ? tx_remaining_budget : 0UL),
             (valid ? _tx_remaining_budget(tx_remaining_budget) : TX_REMAINING_NOT_AVAILABLE_STR));
  } else {
    snprintf(_str_buff, STR_BUFF_SIZE, "Wrong phy profile: %lu", node_info.settings.phy.type);
  }
  sl_gui_textbox_set(_str_buff);
  sl_gui_textbox_update();
  sl_display_update();

  app_wisun_trace_util_destroy_ip_str(ip_str_global);
  app_wisun_trace_util_destroy_ip_str(ip_str_br);
  app_wisun_trace_util_destroy_ip_str(ip_str_pp);
  app_wisun_trace_util_destroy_ip_str(ip_str_sp);
}

static void _set_nbinfo_txtbox(void *args)
{
  sl_wisun_nwm_node_stat_t *stat = (sl_wisun_nwm_node_stat_t *) args;
  const char *ip_str             = NULL;

  ip_str = app_wisun_trace_util_get_ip_str(&stat->addr.sin6_addr);

  sl_gui_title_set_label(stat->name);
  sl_gui_title_update();

  sl_gui_textbox_init();

  snprintf(_str_buff, STR_BUFF_SIZE, PRINT_NEIGHBOR_STAT_FORMAT_STR,
           ip_str,
           stat->stat.lifetime,
           stat->stat.mac_tx_count,
           stat->stat.mac_tx_failed_count,
           stat->stat.mac_tx_ms_count,
           stat->stat.mac_tx_ms_failed_count,
           stat->stat.rpl_rank,
           stat->stat.etx,
           stat->stat.rsl_out,
           stat->stat.rsl_in);

  sl_gui_textbox_set(_str_buff);
  sl_gui_textbox_update();

  sl_gui_button_set_label(SL_GUI_BUTTON0, "Back");
  sl_gui_button_set_callback(SL_GUI_BUTTON0, sli_wisun_neighbors_select_form, NULL);
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_txt_box, NULL);

  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_gui_button_update(SL_GUI_BUTTON0);

  sl_display_update();
  app_wisun_trace_util_destroy_ip_str(ip_str);
}

static inline const char* _tx_remaining_budget(const uint32_t tx_remaining_budget)
{
  if (tx_remaining_budget == 0UL) {
    return TX_REMAINING_EXCEEDED_STR;
  } else {
    return TX_REMAINING_REMAINING_STR;
  }
}

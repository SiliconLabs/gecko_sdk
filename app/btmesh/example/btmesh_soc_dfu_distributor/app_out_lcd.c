/***************************************************************************//**
 * @file
 * @brief Application Output LCD code
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

#include <stdbool.h>
#include <stdio.h>
#include "em_common.h"
#include "sl_status.h"
#include "sl_malloc.h"

#include "app.h"
#include "app_log.h"
#include "app_btmesh_util.h"

#include "sl_btmesh_api.h"

#include "sl_btmesh_wstk_lcd.h"
#include "sl_btmesh_factory_reset.h"
#include "sl_btmesh_provisioning_decorator.h"
#include "sl_btmesh_fw_distribution_server.h"

struct dist_status {
  uint16_t addr;
  sl_btmesh_fw_dist_server_dist_node_phase_t phase;
} *dist_status = NULL;

#define FIRST_DIST_PAGE 1
#define FIRST_DIST_LINE 2
#define NODES_PER_PAGE (LCD_ROW_MAX - FIRST_DIST_LINE + 1)

// -----------------------------------------------------------------------------
// Static function prototypes

/***************************************************************************//**
 * Display the number of FW images residing on the device.
 *
 * Update is needed when adding or deleting firmware images from distributor.
 *
 * @param[in] current_fw_list_length Length of the FW image list
 * @param[in] max_fw_list_length Maximum length of the FW image list. Depends on
 *                               bootloader storage configuration.
 ******************************************************************************/
static void lcd_print_dist_fw_list(uint16_t current_fw_list_length,
                                   uint16_t max_fw_list_length);

/***************************************************************************//**
 * Display the number of nodes participating in the update.
 *
 * Update is needed when adding a node, removing nodes, or a node fails.
 *
 * @param[in] num_active_nodes Number of actively updating nodes
 * @param[in] node_count Number of nodes that ever participated in the current
 *                       update
 ******************************************************************************/
static void lcd_print_dist_node_list(uint16_t num_active_nodes,
                                     uint16_t node_count);

/***************************************************************************//**
 * Display the state of the distribution.
 *
 * Updates the distribution state display in human readable form based on the
 * state code.
 *
 * @param[in] state State of the distribution
 ******************************************************************************/
static void lcd_print_dist_state(uint8_t state);

/***************************************************************************//**
 * Display FW update progress in precentage.
 *
 * @param[in] progress Progress in percentage
 * @param[in] node_count Number of nodes that ever participated in the current
 *                       update
 ******************************************************************************/
static void lcd_print_dist_fw_update_progress(float progress,
                                              uint16_t node_count);

// -----------------------------------------------------------------------------
// Factory Reset Callbacks

/*******************************************************************************
 * Shows factory full reset information
 ******************************************************************************/
void app_show_btmesh_factory_reset_full_reset(void)
{
  app_log("Factory reset" APP_LOG_NL);
  sl_status_t status = sl_btmesh_LCD_write("Factory reset",
                                           SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

/*******************************************************************************
 * Shows factory node reset information
 ******************************************************************************/
void app_show_btmesh_factory_reset_node_reset(void)
{
  app_log("Node reset" APP_LOG_NL);
  sl_status_t status = sl_btmesh_LCD_write("Node reset",
                                           SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

// -----------------------------------------------------------------------------
// BT mesh Friend Node Callbacks

/*******************************************************************************
 * Called when the Friend Node establishes friendship with another node.
 *
 * @param[in] netkey_index Index of the network key used in friendship
 * @param[in] lpn_address Low Power Node address
 ******************************************************************************/
void sl_btmesh_friend_on_friendship_established(uint16_t netkey_index,
                                                uint16_t lpn_address)
{
  app_log("BT mesh Friendship established with LPN "
          "(netkey idx: %u, lpn addr: 0x%04x)" APP_LOG_NL,
          netkey_index,
          lpn_address);
  sl_status_t status = sl_btmesh_LCD_write("FRIEND",
                                           SL_BTMESH_WSTK_LCD_ROW_FRIEND_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)netkey_index;
  (void)lpn_address;
}

/*******************************************************************************
 * Called when the friendship that was successfully established with a Low Power
 * Node has been terminated.
 *
 * @param[in] netkey_index Index of the network key used in friendship
 * @param[in] lpn_address Low Power Node address
 * @param[in] reason Reason for friendship termination
 ******************************************************************************/
void sl_btmesh_friend_on_friendship_terminated(uint16_t netkey_index,
                                               uint16_t lpn_address,
                                               uint16_t reason)
{
  app_log("BT mesh Friendship terminated with LPN "
          "(netkey idx: %d, lpn addr: 0x%04x, reason: 0x%04x)" APP_LOG_NL,
          netkey_index,
          lpn_address,
          reason);
  sl_status_t status = sl_btmesh_LCD_write("NO LPN",
                                           SL_BTMESH_WSTK_LCD_ROW_FRIEND_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)netkey_index;
  (void)lpn_address;
  (void)reason;
}

// -----------------------------------------------------------------------------
// Provisioning Decorator Callbacks

/*******************************************************************************
 *  Called at node initialization time to provide provisioning information
 ******************************************************************************/
void sl_btmesh_on_provision_init_status(bool provisioned,
                                        uint16_t address,
                                        uint32_t iv_index)
{
  if (provisioned) {
    app_show_btmesh_node_provisioned(address, iv_index);
  } else {
    app_log("BT mesh node is unprovisioned, started unprovisioned beaconing..." APP_LOG_NL);
    sl_status_t status = sl_btmesh_LCD_write("unprovisioned",
                                             SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
    app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  }
}

/*******************************************************************************
 *  Called from sl_btmesh_on_node_provisioning_started callback in app.c
 ******************************************************************************/
void app_show_btmesh_node_provisioning_started(uint16_t result)
{
  app_log("BT mesh node provisioning is started (result: 0x%04x)" APP_LOG_NL, result);
  sl_status_t status = sl_btmesh_LCD_write("provisioning...",
                                           SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)result;
}

/*******************************************************************************
 *  Called from sl_btmesh_on_node_provisioned callback in app.c
 ******************************************************************************/
void app_show_btmesh_node_provisioned(uint16_t address,
                                      uint32_t iv_index)
{
  app_log("BT mesh node is provisioned (address: 0x%04x, iv_index: 0x%lx)" APP_LOG_NL,
          address,
          iv_index);
  sl_status_t status = sl_btmesh_LCD_write("provisioned",
                                           SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);

  (void)address;
  (void)iv_index;
}

/*******************************************************************************
 *  Called when the Provisioning fails
 ******************************************************************************/
void sl_btmesh_on_node_provisioning_failed(uint16_t result)
{
  app_log("BT mesh node provisioning failed (result: 0x%04x)" APP_LOG_NL, result);
  sl_status_t status = sl_btmesh_LCD_write("prov failed...",
                                           SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)result;
}

// -----------------------------------------------------------------------------
// Firmware Distributor Server callbacks

static void lcd_print_dist_fw_list(uint16_t current_fw_list_length,
                                   uint16_t max_fw_list_length)
{
  char tmp_str[LCD_ROW_LEN];
  snprintf(tmp_str,
           sizeof(tmp_str),
           "Fw list: %d/%d",
           current_fw_list_length,
           max_fw_list_length);

  sl_status_t status = sl_btmesh_LCD_write(tmp_str,
                                           SL_BTMESH_WSTK_LCD_ROW_DIST_FW_LIST_CFG_VAL);

  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

static void lcd_print_dist_node_list(uint16_t num_active_nodes,
                                     uint16_t node_count)
{
  char tmp_str[LCD_ROW_LEN];
  snprintf(tmp_str,
           sizeof(tmp_str),
           "Dist node:%u/%u",
           num_active_nodes,
           node_count);

  sl_status_t status = sl_btmesh_LCD_write(tmp_str,
                                           SL_BTMESH_WSTK_LCD_ROW_DIST_NODE_LIST_CFG_VAL);

  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

static void lcd_print_dist_state(uint8_t state)
{
  char tmp_str[LCD_ROW_LEN];

  const char *state_string =
    sl_btmesh_fw_distribution_server_distribution_state_to_string((sl_btmesh_fw_dist_server_dist_step_t) state);

  strncpy(tmp_str, state_string, LCD_ROW_LEN);
  // Null termination is necessary if the string is truncated
  tmp_str[LCD_ROW_LEN - 1] = '\0';

  sl_status_t status = sl_btmesh_LCD_write(tmp_str,
                                           SL_BTMESH_WSTK_LCD_ROW_DIST_STATE_CFG_VAL);

  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

static void lcd_print_dist_fw_update_progress(float progress,
                                              uint16_t node_count)
{
  int integral = (int)progress;
  int decimal = ((int)(progress * 10)) % 10;
  char buffer[LCD_ROW_LEN] = { 0 };
  for (uint16_t i = 0; i < node_count; ++i) {
    switch (dist_status[i].phase) {
      case sl_btmesh_fw_dist_server_dist_node_phase_transfer_error:
      case sl_btmesh_fw_dist_server_dist_node_phase_verification_failed:
        // Empty
        break;
      default:
        sprintf(buffer,
                "x%04X:        %3d.%01d%%",
                dist_status[i].addr,
                integral,
                decimal);
        sl_status_t status =
          sl_btmesh_LCD_write_paged(buffer,
                                    i % NODES_PER_PAGE + FIRST_DIST_LINE,
                                    i / NODES_PER_PAGE + FIRST_DIST_PAGE);
        app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
        break;
    }
  }
}

void sl_btmesh_fw_distribution_server_on_node_added(uint16_t elem_index,
                                                    uint16_t server_address,
                                                    uint8_t  update_fw_image_idx,
                                                    uint16_t node_count)
{
  (void) elem_index;
  (void) update_fw_image_idx;
  char buffer[LCD_ROW_LEN] = { 0 };
  dist_status = sl_realloc(dist_status, node_count * sizeof(struct dist_status));
  dist_status[node_count - 1].addr = server_address;
  dist_status[node_count - 1].phase = sl_btmesh_fw_dist_server_dist_node_phase_unknown;
  sl_status_t status =
    sl_btmesh_LCD_write_paged("Distribution",
                              1,
                              (node_count / NODES_PER_PAGE) + FIRST_DIST_PAGE);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  sprintf(buffer,
          "x%04X :         -----",
          dist_status[node_count - 1].addr);
  status =
    sl_btmesh_LCD_write_paged(buffer,
                              (node_count - 1)
                              % NODES_PER_PAGE + FIRST_DIST_LINE,
                              (node_count - 1)
                              / NODES_PER_PAGE + FIRST_DIST_PAGE);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  lcd_print_dist_node_list(node_count, node_count);
}

void sl_btmesh_fw_distribution_server_on_all_nodes_deleted(uint16_t elem_index)
{
  (void) elem_index;
  sl_free(dist_status);
  dist_status = NULL;
  lcd_print_dist_node_list(0, 0);
}

void sl_btmesh_fw_distribution_server_on_distribution_state_changed(uint16_t elem_index,
                                                                    sl_btmesh_fw_dist_server_dist_step_t state,
                                                                    uint16_t num_active_nodes,
                                                                    uint16_t node_count)
{
  (void) elem_index;
  (void) num_active_nodes;
  (void) node_count;

  lcd_print_dist_state(state);
}

void sl_btmesh_fw_distribution_server_on_distribution_blob_progress_changed(uint16_t elem_index,
                                                                            uint32_t confirmed_tx_bytes,
                                                                            uint32_t blob_size,
                                                                            uint16_t node_count)
{
  (void) elem_index;
  float progress = SL_PROG_TO_PCT(blob_size, confirmed_tx_bytes);

  lcd_print_dist_fw_update_progress(progress, node_count);
}

void sl_btmesh_fw_distribution_server_on_distribution_node_failed(uint16_t elem_index,
                                                                  uint16_t server_address,
                                                                  sl_btmesh_fw_dist_server_dist_node_phase_t update_phase,
                                                                  sl_btmesh_fw_update_server_update_status_t update_status,
                                                                  uint8_t  mbt_status,
                                                                  uint8_t  progress,
                                                                  uint8_t  fw_index,
                                                                  uint16_t num_active_nodes,
                                                                  uint16_t node_count)
{
  (void) elem_index;   (void) server_address;
  (void) update_phase; (void) update_status;
  (void) mbt_status;   (void) progress;
  (void) fw_index;

  char buffer[LCD_ROW_LEN] = { 0 };
  for (uint16_t i = 0; i < node_count; ++i) {
    if (dist_status[i].addr == server_address) {
      dist_status[i].phase = update_phase;
      switch (dist_status[i].phase) {
        case sl_btmesh_fw_dist_server_dist_node_phase_transfer_error:
          sprintf(buffer,
                  "x%04X : transfer err.",
                  dist_status[i].addr);
          break;
        case sl_btmesh_fw_dist_server_dist_node_phase_verification_failed:
          sprintf(buffer,
                  "x%04X : verif. failed",
                  dist_status[i].addr);
          break;
        default:
          sprintf(buffer,
                  "x%04X :  unknown err.",
                  dist_status[i].addr);
      }
      sl_btmesh_LCD_write_paged(buffer,
                                i % NODES_PER_PAGE + FIRST_DIST_LINE,
                                i / NODES_PER_PAGE + FIRST_DIST_PAGE);
    }
  }
  lcd_print_dist_node_list(num_active_nodes, node_count);
}

void sl_btmesh_fw_distribution_server_on_firmware_added(uint16_t elem_index,
                                                        uint16_t client_address,
                                                        uint32_t fw_size,
                                                        uint16_t fw_list_idx,
                                                        uint16_t current_fw_list_length,
                                                        uint16_t max_fw_list_length,
                                                        const uint8_t *fwid_data,
                                                        uint8_t fwid_length)
{
  (void) elem_index;
  (void) client_address;
  (void) fw_size;
  (void) fw_list_idx;
  (void) fwid_data;
  (void) fwid_length;

  lcd_print_dist_fw_list(current_fw_list_length, max_fw_list_length);
}

void sl_btmesh_fw_distribution_server_on_firmware_deleted(uint16_t elem_index,
                                                          uint16_t client_address,
                                                          uint16_t current_fw_list_length,
                                                          uint16_t max_fw_list_length,
                                                          const uint8_t *fwid_data,
                                                          uint8_t fwid_length)
{
  (void) elem_index;
  (void) client_address;
  (void) fwid_data;
  (void) fwid_length;
  lcd_print_dist_fw_list(current_fw_list_length, max_fw_list_length);
}

void sl_btmesh_fw_distribution_server_on_all_firmware_deleted(uint16_t elem_index,
                                                              uint16_t client_address,
                                                              uint16_t max_fw_list_length)
{
  (void) elem_index;
  (void) client_address;
  lcd_print_dist_fw_list(0, max_fw_list_length);
}

// -----------------------------------------------------------------------------
// BLOB Transfer Server

static void lcd_print_dist_upload_progress(float progress)
{
  char tmp_str[LCD_ROW_LEN];
  snprintf(tmp_str,
           sizeof(tmp_str),
           "Upload progress: %d%%",
           (uint8_t) progress);

  sl_status_t status =
    sl_btmesh_LCD_write(tmp_str,
                        SL_BTMESH_WSTK_LCD_ROW_DIST_UPLOAD_PROGRESS_CFG_VAL);

  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

void sl_btmesh_blob_transfer_server_transfer_start(sl_bt_uuid_64_t const *const blob_id)
{
  (void) blob_id;
  lcd_print_dist_upload_progress(0.0);
}

void sl_btmesh_blob_transfer_server_transfer_progress(sl_bt_uuid_64_t const *const blob_id,
                                                      float progress)
{
  (void) blob_id;
  lcd_print_dist_upload_progress(progress);
}

void sl_btmesh_blob_transfer_server_transfer_done(sl_bt_uuid_64_t const *const blob_id)
{
  (void) blob_id;
  lcd_print_dist_upload_progress(100.0);
}

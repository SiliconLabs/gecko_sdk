/***************************************************************************//**
 * @file
 * @brief Application Output LCD code
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
// Includes

#include <stdbool.h>
#include <stdio.h>
#include "em_common.h"
#include "sl_status.h"

#include "app.h"
#include "app_log.h"

#include "sl_bt_api.h"
#include "sl_btmesh_api.h"

#ifdef SL_CATALOG_BTMESH_FRIEND_PRESENT
#include "sl_btmesh_friend.h"
#endif // SL_CATALOG_BTMESH_FRIEND_PRESENT

#include "sl_btmesh_lighting_server.h"

#ifdef SL_CATALOG_BTMESH_PROVISIONING_DECORATOR_PRESENT
#include "sl_btmesh_provisioning_decorator.h"
#endif // SL_CATALOG_BTMESH_PROVISIONING_DECORATOR_PRESENT

#ifdef SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT
#include "sl_btmesh_factory_reset.h"
#endif // SL_CATALOG_BTMESH_FACTORY_RESET_PRESENT

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
#include "sl_btmesh_wstk_lcd.h"

#define lcd_print(...) sl_btmesh_LCD_write(__VA_ARGS__)
#else
#define lcd_print(...) SL_STATUS_OK
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

// -----------------------------------------------------------------------------
// Event / callback definitions

/*******************************************************************************
 * Called when the Friend Node establishes friendship with another node
 ******************************************************************************/
void sl_btmesh_friend_on_friendship_established(uint16_t netkey_index,
                                                uint16_t lpn_address)
{
  app_log("BT mesh Friendship established with LPN "
          "(netkey idx: %u, lpn addr: 0x%04x)" APP_LOG_NL,
          netkey_index,
          lpn_address);
  sl_status_t status = lcd_print("FRIEND",
                                 SL_BTMESH_WSTK_LCD_ROW_FRIEND_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)netkey_index;
  (void)lpn_address;
}

/*******************************************************************************
 * Called when the friendship that was successfully established with a Low Power
 * Node has been terminated
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
  sl_status_t status = lcd_print("NO LPN",
                                 SL_BTMESH_WSTK_LCD_ROW_FRIEND_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)netkey_index;
  (void)lpn_address;
  (void)reason;
}

/*******************************************************************************
 * Called when the UI shall be updated with the changed state of
 * lightning server during a transition
 ******************************************************************************/
void sl_btmesh_lighting_server_on_ui_update(uint16_t lightness_level)
{
  uint16_t lightness_percent = (lightness_level * 100 + 99) / 65535;
  app_log("BT mesh Lightness: %5u%%" APP_LOG_NL, lightness_percent);
  #ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  // Temporary buffer to format the LCD output text
  char tmp_str[LCD_ROW_LEN];
  snprintf(tmp_str, LCD_ROW_LEN, "Lightness: %5u%%", lightness_percent);
  #endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

  sl_status_t status = lcd_print(tmp_str, SL_BTMESH_WSTK_LCD_ROW_LIGHTNESS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

/*******************************************************************************
 * Called at node initialization time to provide provisioning information
 ******************************************************************************/
void sl_btmesh_on_provision_init_status(bool provisioned,
                                        uint16_t address,
                                        uint32_t iv_index)
{
  if (provisioned) {
    app_show_btmesh_node_provisioned(address, iv_index);
  } else {
    app_log("BT mesh node is unprovisioned, "
            "started unprovisioned beaconing..." APP_LOG_NL);
    sl_status_t status = lcd_print("unprovisioned",
                                   SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
    app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  }
}

/*******************************************************************************
 * Called when the Provisioning starts
 ******************************************************************************/
void app_show_btmesh_node_provisioning_started(uint16_t result)
{
  app_log("BT mesh node provisioning is started (result: 0x%04x)" APP_LOG_NL,
          result);
  sl_status_t status = lcd_print("provisioning...",
                                 SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)result;
}

/*******************************************************************************
 * Called when the Provisioning finishes successfully
 ******************************************************************************/
void app_show_btmesh_node_provisioned(uint16_t address,
                                      uint32_t iv_index)
{
  app_log("BT mesh node is provisioned (address: 0x%04x, iv_index: 0x%lx)" APP_LOG_NL,
          address,
          iv_index);
  sl_status_t status = lcd_print("provisioned",
                                 SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)address;
  (void)iv_index;
}

/*******************************************************************************
 * Called when the Provisioning fails
 ******************************************************************************/
void app_show_btmesh_node_provisioning_failed(uint16_t result)
{
  app_log("BT mesh node provisioning failed (result: 0x%04x)" APP_LOG_NL, result);
  sl_status_t status = lcd_print("prov failed...",
                                 SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)result;
}

/*******************************************************************************
 * Shows the node reset information
 ******************************************************************************/
void app_show_btmesh_node_reset(void)
{
  app_log("Node reset" APP_LOG_NL);
  sl_status_t status = lcd_print("Node reset",
                                 SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

/*******************************************************************************
 * Called when full reset is established, before system reset
 ******************************************************************************/
void sl_btmesh_factory_reset_on_full_reset(void)
{
  app_log("Factory reset" APP_LOG_NL);
  sl_status_t status = lcd_print("Factory reset",
                                 SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

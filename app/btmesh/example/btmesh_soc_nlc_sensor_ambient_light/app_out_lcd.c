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

#include "sl_btmesh_api.h"

#include "sl_btmesh_device_properties.h"

#include "sl_btmesh_sensor_server.h"

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
// Macros

/// Integer part of illuminance
#define INT_ILLUM(x)  (x / 100)
/// Fractional part of illuminance
#define FRAC_ILLUM(x) (x % 100)

// -----------------------------------------------------------------------------
// Event / callback definitions

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

/*******************************************************************************
 * Called when node reset is established, before system reset
 ******************************************************************************/
void sl_btmesh_factory_reset_on_node_reset(void)
{
  app_log("Node reset" APP_LOG_NL);
  sl_status_t status = lcd_print("Node reset",
                                 SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

/*******************************************************************************
 *  Called when a light measurement is done
 ******************************************************************************/
void sl_btmesh_sensor_server_on_light_measurement(illuminance_t light)
{
  sl_status_t status = SL_STATUS_OK;
  if ((illuminance_t)SL_BTMESH_SENSOR_LIGHT_VALUE_UNKNOWN == light) {
    app_log("Illuminance: UNKNOWN" APP_LOG_NL);
    status = lcd_print("Illuminance: N/K",
                       SL_BTMESH_WSTK_LCD_ROW_ILLUMINANCE_CFG_VAL);
  } else {
    app_log("Illuminance:   %4lu.%02lu lx" APP_LOG_NL,
            INT_ILLUM(light),
            FRAC_ILLUM(light));
    #ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
    char str[LCD_ROW_LEN];
    snprintf(str,
             LCD_ROW_LEN,
             "Illum: %4u.%02u lx",
             (uint16_t)(INT_ILLUM(light)),
             (uint8_t)(FRAC_ILLUM(light)));
    status = lcd_print(str, SL_BTMESH_WSTK_LCD_ROW_ILLUMINANCE_CFG_VAL);
    #endif
  }
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
}

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
    sl_status_t status = lcd_print("unprovisioned",
                                   SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
    app_log_status_level_f(APP_LOG_LEVEL_ERROR, status, "LCD write failed");
  }
}

/*******************************************************************************
 *  Called from sl_btmesh_on_node_provisioning_started callback in app.c
 ******************************************************************************/
void app_show_btmesh_node_provisioning_started(uint16_t result)
{
  app_log("BT mesh node provisioning is started (result: 0x%04x)" APP_LOG_NL, result);
  sl_status_t status = lcd_print("provisioning...",
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
  sl_status_t status = lcd_print("provisioned",
                                 SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)address;
  (void)iv_index;
}

/*******************************************************************************
 *  Called from sl_btmesh_on_node_provisioning_failed callback in app.c
 ******************************************************************************/
void app_show_btmesh_node_provisioning_failed(uint16_t result)
{
  app_log("BT mesh node provisioning failed (result: 0x%04x)" APP_LOG_NL, result);
  sl_status_t status = lcd_print("prov failed...",
                                 SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
  app_log_status_error_f(status, "LCD write failed" APP_LOG_NL);
  (void)result;
}

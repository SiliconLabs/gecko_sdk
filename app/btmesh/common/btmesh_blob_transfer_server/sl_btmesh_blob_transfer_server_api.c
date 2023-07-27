/***************************************************************************//**
 * @file
 * @brief Weak implementation of user API functions
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
#include "sl_btmesh.h"
#include "sl_common.h"

#include "sl_btmesh_blob_transfer_server_api.h"
#include "sl_btmesh_blob_storage.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
#include "sl_btmesh_wstk_lcd.h"
#include <stdio.h>
// First block flag
static bool first_block;
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT

SL_WEAK void sl_btmesh_blob_transfer_server_transfer_start(sl_bt_uuid_64_t const *const blob_id)
{
  (void)blob_id;
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("BLOB Transfer Start", SL_BTMESH_WSTK_LCD_ROW_BLOB_STATUS_CFG_VAL);
  char blob_id_buff[3 * 8] = { 0 };
  sprintf(blob_id_buff,
          "0x%02X%02X%02X%02X%02X%02X%02X%02X",
          blob_id->data[0],
          blob_id->data[1],
          blob_id->data[2],
          blob_id->data[3],
          blob_id->data[4],
          blob_id->data[5],
          blob_id->data[6],
          blob_id->data[7]);
  sl_btmesh_LCD_write(blob_id_buff, SL_BTMESH_WSTK_LCD_ROW_BLOB_ID_CFG_VAL);
  first_block = true;
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
}

SL_WEAK void sl_btmesh_blob_transfer_server_transfer_progress(sl_bt_uuid_64_t const *const blob_id,
                                                              float progress)
{
  (void)blob_id;
  (void)progress;
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  if (first_block) {
    sl_btmesh_LCD_write("BLOB Transfer Prog.",
                        SL_BTMESH_WSTK_LCD_ROW_BLOB_STATUS_CFG_VAL);
    first_block = false;
  }
  char prog_buff[8] = { 0 };
  sprintf(prog_buff, "%3u.%01u %%", (uint8_t)progress, (uint8_t)(((uint16_t)(progress * 10)) % 10));
  sl_btmesh_LCD_write(prog_buff, SL_BTMESH_WSTK_LCD_ROW_BLOB_PROGRESS_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
}

SL_WEAK void sl_btmesh_blob_transfer_server_transfer_done(sl_bt_uuid_64_t const *const blob_id)
{
  (void)blob_id;
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("BLOB Transfer Done", SL_BTMESH_WSTK_LCD_ROW_BLOB_STATUS_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
}

SL_WEAK void sl_btmesh_blob_transfer_server_transfer_abort(sl_bt_uuid_64_t const *const blob_id)
{
  (void)blob_id;
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("BLOB Transfer Aborted", SL_BTMESH_WSTK_LCD_ROW_BLOB_STATUS_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
}

SL_WEAK void sl_btmesh_blob_transfer_server_storage_full(void)
{
#ifdef SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
  sl_btmesh_LCD_write("BLOB Storage Full", SL_BTMESH_WSTK_LCD_ROW_BLOB_STATUS_CFG_VAL);
#endif // SL_CATALOG_BTMESH_WSTK_LCD_PRESENT
}

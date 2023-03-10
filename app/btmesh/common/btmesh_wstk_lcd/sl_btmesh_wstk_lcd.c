/***************************************************************************//**
 * @file
 * @brief LCD driver implementation file
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdio.h>
#include <string.h>
#include "sl_btmesh_wstk_graphics.h"
#include "sl_btmesh_wstk_lcd.h"
#include "sl_btmesh_wstk_lcd_config.h"
#include "sl_malloc.h"

#include "app_assert.h"

/***************************************************************************//**
 * Refresh selected page.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FAIL If display manipulation failed
 ******************************************************************************/
static sl_status_t refresh_page();

/// Array for storing the LCD content
static char *LCD_data = NULL;
/// Number of pages stored
static uint8_t page_cnt = 0;
/// Page displayed
static uint8_t page_select = 0;

/***************************************************************************//**
 * @addtogroup disp_interface
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Call a callback function at the given frequency.
 *
 * @param[in] pFunction  Pointer to function that should be called at the
 *                       given frequency.
 * @param[in] argument   Argument to be given to the function.
 * @param[in] frequency  Frequency at which to call function at.
 *
 * @return  Status code of the operation.
 *
 * @note This is needed by the LCD driver
 ******************************************************************************/
int rtcIntCallbackRegister(void (*pFunction)(void *),
                           void *argument,
                           unsigned int frequency)
{
  (void)pFunction;
  (void)argument;
  (void)frequency;

  return 0;
}

sl_status_t sl_btmesh_LCD_init(void)
{
  graphInit(SL_BTMESH_WSTK_LCD_GRAPH_INIT_TEXT_CFG_VAL);

  return sl_btmesh_LCD_write(SL_BTMESH_WSTK_LCD_INIT_TEXT_CFG_VAL, SL_BTMESH_WSTK_LCD_ROW_STATUS_CFG_VAL);
}

sl_status_t sl_btmesh_LCD_write(const char *str, uint8_t row)
{
  return sl_btmesh_LCD_write_paged(str, row, 0);
}

sl_status_t sl_btmesh_LCD_write_paged(const char *str, uint8_t row, uint8_t page)
{
  char *pPage;
  char *pRow;

  if (row > LCD_ROW_MAX || row < 1) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  uint8_t page_cnt_tmp = page_cnt;
  if (page >= page_cnt) {
    page_cnt = page + 1;
    LCD_data = sl_realloc(LCD_data, LCD_ROW_MAX * LCD_ROW_LEN * page_cnt);
    app_assert(LCD_data != NULL, "LCD allocation error.");
    memset(&LCD_data[LCD_ROW_MAX * LCD_ROW_LEN * page_cnt_tmp],
           0,
           LCD_ROW_MAX * LCD_ROW_LEN * (page_cnt - page_cnt_tmp));
  }

  pPage = &(LCD_data[page * LCD_ROW_MAX * LCD_ROW_LEN]);

  pRow  = &(pPage[(row - 1) * LCD_ROW_LEN]);

  strcpy(pRow, str);

  pPage[LCD_ROW_MAX * LCD_ROW_LEN - 1] = '\0';

  if ((page == page_select) || ((page - 1) == page_select)) {
    return refresh_page();
  } else {
    // Not necessary to print hidden page
    return SL_STATUS_OK;
  }
}

sl_status_t sl_btmesh_LCD_remove_page(uint8_t page)
{
  if ((page == 0) || (page >= page_cnt)) {
    return SL_STATUS_INVALID_INDEX;
  }
  if (page != (page_cnt - 1)) {
    memcpy(&LCD_data[LCD_ROW_MAX * LCD_ROW_LEN * page],
           &LCD_data[LCD_ROW_MAX * LCD_ROW_LEN * (page + 1)],
           LCD_ROW_MAX * LCD_ROW_LEN * (page_cnt - page));
  }
  LCD_data = sl_realloc(LCD_data, LCD_ROW_MAX * LCD_ROW_LEN * --page_cnt);
  app_assert(LCD_data != NULL, "LCD allocation error.");
  // Make sure display shows consistent data
  if (page == page_select) {
    return sl_btmesh_LCD_select_page(0);
  } else if (page < page_select) {
    return sl_btmesh_LCD_prev_page();
  }
  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_LCD_clear_pages(void)
{
  LCD_data = sl_realloc(LCD_data, LCD_ROW_MAX * LCD_ROW_LEN);
  app_assert(LCD_data != NULL, "LCD allocation error.");
  memset(LCD_data, 0, LCD_ROW_MAX * LCD_ROW_LEN);
  page_cnt = 1;
  return sl_btmesh_LCD_select_page(0);
}

sl_status_t sl_btmesh_LCD_select_page(uint8_t page)
{
  if (page < page_cnt) {
    page_select = page;
    return refresh_page();
  }
  return SL_STATUS_INVALID_INDEX;
}

sl_status_t sl_btmesh_LCD_next_page(void)
{
  if (page_select == page_cnt - 1) {
    return SL_STATUS_OK;
  }
  ++page_select;
  return refresh_page();
}

sl_status_t sl_btmesh_LCD_prev_page(void)
{
  if (page_select == 0) {
    return SL_STATUS_OK;
  }
  --page_select;
  return refresh_page();
}

/** @} (end addtogroup disp_interface) */

static sl_status_t refresh_page()
{
  char LCD_message[LCD_ROW_MAX * LCD_ROW_LEN] = { 0 };
  char *pPage;
  char *pRow;
  pPage = &(LCD_data[page_select * LCD_ROW_MAX * LCD_ROW_LEN]);

  for (int i = 0; i < LCD_ROW_MAX; ++i) {
    pRow = &(pPage[i * LCD_ROW_LEN]);
    strcat(LCD_message, pRow);
    strcat(LCD_message, "\n");
  }

  sl_status_t status = graphWriteString(LCD_message);

  if ((page_select > 0) && (SL_STATUS_OK == status)) {
    status = graphDrawArrow(SL_BTMESH_LCD_LEFT_ARROW);
  }
  if ((page_select < page_cnt - 1) && (SL_STATUS_OK == status)) {
    status = graphDrawArrow(SL_BTMESH_LCD_RIGHT_ARROW);
  }

  return status;
}

/***************************************************************************//**
 * @file
 * @brief BT Mesh WSTK LCD driver header file
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

#ifndef SL_BTMESH_WSTK_LCD_H
#define SL_BTMESH_WSTK_LCD_H

#include <stdint.h>
#include "sl_status.h"
#include "sl_btmesh_wstk_lcd_config.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * \defgroup lcd_driver LCD Driver
 * \brief Driver for SPI LCD Display.
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup disp_interface
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup lcd_driver
 * @{
 ******************************************************************************/

/*******************************************************************************
 * LCD content can be updated one row at a time using function LCD_write().
 * Row number is passed as parameter, the possible values are defined below.
 ******************************************************************************/
/** up to 9 rows available on screen */
#define LCD_ROW_MAX          9
/** up to 21 characters, plus line break each row */
#define LCD_ROW_LEN         22

/***************************************************************************//**
 * Initialize LCD.
 *
 * Called once at startup.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FAIL If writing header failed
 ******************************************************************************/
sl_status_t sl_btmesh_LCD_init(void);

/***************************************************************************//**
 * This function is used to write one line on the LCD.
 *
 * @note This uses @ref sl_btmesh_LCD_write_paged to write onto page 0.
 *
 * @param[in] str  Pointer to string which is displayed in the specified row.
 * @param[in] row  Selects which line of LCD display is written,
 *                 possible values are defined as LCD_ROW_xxx.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_INVALID_PARAMETER If row is invalid
 * @retval SL_STATUS_FAIL If writing failed
 ******************************************************************************/
sl_status_t sl_btmesh_LCD_write(const char *str, uint8_t row);

/***************************************************************************//**
 * This function is used to write one line on the LCD onto the given page.
 *
 * Pages are handled dynamically
 *
 * @param[in] str  Pointer to string which is displayed in the specified row.
 * @param[in] row  Selects which line of LCD display is written,
 *                 possible values are defined as LCD_ROW_xxx.
 * @param[in] page Page identifier. Zero-based.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_INVALID_PARAMETER If row is invalid
 * @retval SL_STATUS_FAIL If writing failed
 ******************************************************************************/
sl_status_t sl_btmesh_LCD_write_paged(const char *str,
                                      uint8_t row,
                                      uint8_t page);

/***************************************************************************//**
 * Select page to be displayed and display it.
 *
 * @param[in] page Page index to display. Zero-based.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FAIL If page refresh failed
 * @retval SL_STATUS_INVALID_INDEX If page index is out of range
 ******************************************************************************/
sl_status_t sl_btmesh_LCD_select_page(uint8_t page);

/***************************************************************************//**
 * Select next page to be displayed and display it.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success, or last page is displayed
 * @retval SL_STATUS_FAIL If page refresh failed
 ******************************************************************************/
sl_status_t sl_btmesh_LCD_next_page(void);

/***************************************************************************//**
 * Select previous page to be displayed and display it.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success, or last page is displayed
 * @retval SL_STATUS_FAIL If page refresh failed
 ******************************************************************************/
sl_status_t sl_btmesh_LCD_prev_page(void);

/***************************************************************************//**
 * Remove page.
 *
 * If currently displayed page is removed, display a valid one. If last page is
 * removed, display the first one. If page is removed from before the currently
 * displayed page refresh page so consistency is upheld.
 *
 * Page 0 can't be removed.
 *
 * @param[in] page Page index to remove. Zero-based.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_INVALID_INDEX If page is out of range or 0.
 * @retval SL_STATUS_FAIL If page needed to be refreshed and was unsuccessful
 ******************************************************************************/
sl_status_t sl_btmesh_LCD_remove_page(uint8_t page);

/***************************************************************************//**
 * Remove every page except the first.
 *
 * Refreshes page.
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_FAIL If page refresh is unsuccessful
 ******************************************************************************/
sl_status_t sl_btmesh_LCD_clear_pages(void);

/** @} (end addtogroup lcd_driver) */
/** @} (end addtogroup disp_interface) */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* SL_BTMESH_WSTK_LCD_H */

/***************************************************************************//**
 * @file
 * @brief Displays text on the LCD
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

#ifndef SL_BTMESH_WSTK_GRAPHICS_H
#define SL_BTMESH_WSTK_GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sl_status.h"

/// Enumeration of possible arrows to be drawn
typedef enum {
  /// Left arrow
  SL_BTMESH_LCD_LEFT_ARROW = 1 << 0,
    /// Right arrow
    SL_BTMESH_LCD_RIGHT_ARROW = 1 << 1,
    /// Left arrow and right arrow
    SL_BTMESH_LCD_LEFT_RIGHT_ARROW = SL_BTMESH_LCD_LEFT_ARROW
                                   | SL_BTMESH_LCD_RIGHT_ARROW
} sl_btmesh_LCD_arrow;

// -----------------------------------------------------------------------------
// Public Function Declarations

/***************************************************************************//**
 *  @brief Initialize graphics stack.
 *
 *  @param[in] header Header Text on display
 ******************************************************************************/
void graphInit(char *header);

/***************************************************************************//**
 * @brief Display a string on the LCD center aligned.
 *
 * @param[in]  string  String to be displayed
 *
 * @returns Status of the command.
 * @retval SL_STATUS_OK   In case of success
 * @retval SL_STATUS_FAIL In case of failure
 ******************************************************************************/
sl_status_t graphWriteString(char *string);

/***************************************************************************//**
 * Draw arrows on the page.
 *
 * @param[in] arrow Arrow to be drawn
 *
 * @return Status code
 * @retval SL_STATUS_OK   In case of success
 * @retval SL_STATUS_FAIL In case of failure
 ******************************************************************************/
sl_status_t graphDrawArrow(sl_btmesh_LCD_arrow arrow);

#ifdef __cplusplus
}
#endif

#endif /* SL_BTMESH_WSTK_GRAPHICS_H */

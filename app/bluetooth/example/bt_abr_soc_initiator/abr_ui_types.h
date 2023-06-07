/***************************************************************************//**
 * @file
 * @brief User Interface type definitions for ABR UI.
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

#ifndef ABR_UI_TYPES_H
#define ABR_UI_TYPES_H

/*******************************************************************************
 ********************************  TYPEDEFS  ***********************************
 ******************************************************************************/

// Enum type for UI rows
typedef enum {
  ROW_SYSTEM = 1,
  ROW_ROLE,
  ROW_MODE,
  ROW_DISTANCE_TEXT = 5,
  ROW_DISTANCE_VALUE,
  ROW_RSSI_DISTANCE_TEXT = 8,
  ROW_RSSI_DISTANCE_VALUE,
  ROW_STATE = 11
} abr_ui_row_t;

#define ABR_UI_DISTANCE_FORMAT            "DIST: %f"

#endif // ABR_UI_TYPES_H

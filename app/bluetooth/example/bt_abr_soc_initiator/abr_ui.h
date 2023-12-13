/***************************************************************************//**
 * @file
 * @brief User Interface for ABR display UI
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

#ifndef ABR_UI_H
#define ABR_UI_H

#include "glib.h"
#include "abr_initiator_interface.h"

#define ABR_UI_STATE_CONNECTED_TEXT       "ST: Connected"
#define ABR_UI_STATE_DISCONNECTED_TEXT    "ST: Disconnected"
#define ABR_UI_STATE_SCANNING_TEXT        "ST: Scanning..."
#define ABR_UI_STATE_UNINITIALIZED_TEXT   "ST: Uninited"

/*******************************************************************************
 ******************************   PROTOTYPES   *********************************
 ******************************************************************************/

/**************************************************************************//**
 * @brief
 *   Initialize the the display and the UI
 *****************************************************************************/
void abr_ui_init(void);

/**************************************************************************//**
 * @brief
 *   Updates the the display
 *****************************************************************************/
void abr_ui_update(void);

/**************************************************************************//**
 * @brief
 *   Set the UI text aligment
 *
 * @param[in] alignment text aligment to use
 *****************************************************************************/
void abr_ui_set_alignment(GLIB_Align_t alignment);

/**************************************************************************//**
 * @brief
 *   Write text on the UI
 *
 * @param[in] str pointer to the text to print
 * @param[in] row row to print the text on
 *****************************************************************************/
void abr_ui_write_text(char *str, uint8_t row);

/**************************************************************************//**
 * @brief
 *   Print the calculated value on the UI
 *
 * @param[in] value the calculated value
 * @param[in] row number of the row to print on
 * @param[in] unit unit string, in case of NULL no unit displayed
 *****************************************************************************/
void abr_ui_print_value(float value, uint8_t row, char *unit);

/**************************************************************************//**
 * @brief
 *   Set the state on UI.
 *
 * @param[in] state current state
 *****************************************************************************/
void abr_ui_set_state(const abr_state_t state);

#endif // ABR_UI_H

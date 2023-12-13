/***************************************************************************//**
 * @file
 * @brief ABR display logic
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

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "glib.h"
#include "dmd/dmd.h"
#include "app_assert.h"

#include "abr_ui_types.h"
#include "abr_ui.h"
#include "abr_initiator_interface.h"

#define FONT_TYPE                   ((GLIB_Font_t *)&GLIB_FontNormal8x8)
#define BUFFER_SIZE                 40

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static GLIB_Context_t glib_context;
static GLIB_Align_t glib_text_alignment;
static void clear_row(uint8_t row);

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/
static void clear_row(uint8_t row)
{
  const char empty[] = "                    ";
  GLIB_drawStringOnLine(&glib_context,
                        empty,
                        row,
                        GLIB_ALIGN_LEFT,
                        0,
                        0,
                        true);
}

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
void abr_ui_init(void)
{
  EMSTATUS status;

  status = DMD_init(0);
  app_assert(DMD_OK == status, "Failed to init display driver\n");

  status = GLIB_contextInit(&glib_context);
  app_assert(DMD_OK == status, "Failed to init display context\n");

  glib_context.backgroundColor = White;
  glib_context.foregroundColor = Black;

  GLIB_setFont(&glib_context, FONT_TYPE);
  GLIB_clear(&glib_context);
  abr_ui_set_alignment(GLIB_ALIGN_LEFT);

  abr_ui_write_text("Silabs ABR", ROW_SYSTEM);
  abr_ui_write_text("Initiator", ROW_ROLE);
  abr_ui_set_state(ABR_STATE_UNINITALIZED);
  abr_ui_update();
}

void abr_ui_update(void)
{
  DMD_updateDisplay();
}

void abr_ui_set_alignment(GLIB_Align_t alignment)
{
  glib_text_alignment = alignment;
}

void abr_ui_write_text(char *str, uint8_t row)
{
  if (!strlen(str)) {
    return;
  }
  clear_row(row);
  GLIB_drawStringOnLine(&glib_context,
                        str,
                        row,
                        glib_text_alignment,
                        0,
                        0,
                        true);
}

void abr_ui_print_value(float value, uint8_t row, char *unit)
{
  char *unit_str = "";
  if (unit != NULL) {
    unit_str = unit;
  }
  char buffer[BUFFER_SIZE];
  uint32_t base = truncf(value);
  uint32_t ext = (value - (float)base) * 100;
  sprintf(buffer, "%lu.%02lu%s", base, ext, unit_str);
  abr_ui_write_text(buffer, row);
}

/******************************************************************************
 * Sets the PHY on UI.
 *****************************************************************************/
void abr_ui_set_state(const abr_state_t state)
{
  clear_row(ROW_STATE);
  abr_ui_set_alignment(GLIB_ALIGN_LEFT);
  switch (state) {
    case ABR_STATE_CONNECTED:
      abr_ui_write_text(ABR_UI_STATE_CONNECTED_TEXT, ROW_STATE);
      break;
    case ABR_STATE_SCANNING:
      abr_ui_write_text(ABR_UI_STATE_SCANNING_TEXT, ROW_STATE);
      break;
    case ABR_STATE_UNINITALIZED:
      abr_ui_write_text(ABR_UI_STATE_UNINITIALIZED_TEXT, ROW_STATE);
      break;
    default:
      abr_ui_write_text(ABR_UI_STATE_DISCONNECTED_TEXT, ROW_STATE);
      break;
  }
  abr_ui_update();
}

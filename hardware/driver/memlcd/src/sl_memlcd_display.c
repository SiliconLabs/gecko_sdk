/***************************************************************************//**
 * @file
 * @brief Sharp Memory LCD driver
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

#include <stddef.h>
#include "sl_memlcd.h"
#include "sl_memlcd_display.h"

sl_status_t sl_memlcd_init(void)
{
  sl_memlcd_t memlcd = {
    .width = SL_MEMLCD_DISPLAY_WIDTH,
    .height = SL_MEMLCD_DISPLAY_HEIGHT,
    .bpp = SL_MEMLCD_DISPLAY_BPP,
    .color_mode = SL_MEMLCD_COLOR_MODE_MONOCHROME,
    .spi_freq = SL_MEMLCD_SCLK_FREQ,
    .extcomin_freq = SL_MEMLCD_EXTCOMIN_FREQUENCY,
    .setup_us = SL_MEMLCD_SCS_SETUP_US,
    .hold_us = SL_MEMLCD_SCS_HOLD_US,
    .custom_data = NULL,
  };

  return sl_memlcd_configure(&memlcd);
}

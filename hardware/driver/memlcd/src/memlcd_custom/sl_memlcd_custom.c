/***************************************************************************//**
 * @file
 * @brief Custom Memory LCD Interface
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#if !defined(MEMLCD)
#error "Memory LCD functions must be implemented. Remove error by adding -DMEMLCD in compiler options"
#endif

/***************************************************************************//**
 *  @brief
 *    STUB - This function needs to be redefined by the user to use a custom
 *    memory LCD with the GLIB library.
 *
 *  @return
 *    SL_STATUS_NOT_AVAILABLE
 ******************************************************************************/
SL_WEAK sl_status_t sl_memlcd_init(void)
{
  return SL_STATUS_NOT_AVAILABLE;
}

/***************************************************************************//**
 *  @brief
 *    STUB - This function needs to be redefined by the user to use a custom
 *    memory LCD with the GLIB library.
 *
 *  @return
 *    SL_STATUS_NOT_AVAILABLE
 ******************************************************************************/
SL_WEAK const sl_memlcd_t *sl_memlcd_get(void)
{
  return NULL;
}

/***************************************************************************//**
 *  @brief
 *    STUB - This function needs to be redefined by the user to use a custom
 *    memory LCD with the GLIB library.
 *
 *  @return
 *    SL_STATUS_NOT_AVAILABLE
 ******************************************************************************/
SL_WEAK sl_status_t sl_memlcd_power_on(const sl_memlcd_t *device, bool on)
{
  (void) device;        // Suppress compiler warning: unused parameter.
  (void) on;            // Suppress compiler warning: unused parameter.

  return SL_STATUS_NOT_AVAILABLE;
}

/***************************************************************************//**
 *  @brief
 *    STUB - This function needs to be redefined by the user to use a custom
 *    memory LCD with the GLIB library.
 *
 *  @return
 *    SL_STATUS_NOT_AVAILABLE
 ******************************************************************************/
SL_WEAK sl_status_t sl_memlcd_draw(const sl_memlcd_t *device,
                                   const void *data,
                                   unsigned int row_start,
                                   unsigned int row_count)
{
  (void) device;        // Suppress compiler warning: unused parameter.
  (void) data;          // Suppress compiler warning: unused parameter.
  (void) row_start;     // Suppress compiler warning: unused parameter.
  (void) row_count;     // Suppress compiler warning: unused parameter.

  return SL_STATUS_NOT_AVAILABLE;
}

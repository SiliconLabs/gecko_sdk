/***************************************************************************//**
 * @file
 * @brief Custom Memory LCD Interface
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
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

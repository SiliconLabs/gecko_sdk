/***************************************************************************//**
 * @file
 * @brief Custom Memory LCD Driver
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
#ifndef SL_MEMLCD_DISPLAY_H
#define SL_MEMLCD_DISPLAY_H

#include "sl_status.h"
#include "sl_common.h"

#if defined(MEMLCD_CUSTOM_DRIVER)
#include "sl_memlcd_custom_config.h"
#else
#include "sl_memlcd_display_custom_config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup memlcd MEMLCD - Memory LCD
 * @{
 ******************************************************************************/
/***************************************************************************//**
 * @brief
 *   Initialize the memory LCD.
 *
 * @return
 *   SL_STATUS_OK if there are no errors.
 ******************************************************************************/
sl_status_t sl_memlcd_init(void);

#ifdef __cplusplus
}
#endif

/** @} (end group memlcd) */

#endif

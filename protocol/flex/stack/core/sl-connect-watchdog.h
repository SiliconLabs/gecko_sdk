/***************************************************************************//**
 * @brief Header for including sl_watchdog.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __SL_CONNECT_WATCHDOG_H__
#define __SL_CONNECT_WATCHDOG_H__

#if (defined(EMBER_TEST) || defined(SL_CONNECT_DISABLE_WATCHDOG)) // Watchdog stubs
#define WDOGn_Feed(wdog)
#define WDOGn_Enable(wdog, condition)
#else
#include "em_wdog.h"
#endif // EMBER_TEST

void sl_connect_watchdog_init(void);

#endif // __SLI_CONNECT_WATCHDOG_H__

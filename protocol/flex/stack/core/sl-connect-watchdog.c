/***************************************************************************//**
 * @brief Watchdog init
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

#include "include/ember.h"
#include "em_cmu.h"
#include "em_wdog.h"
#include "em_rmu.h"
#include "sl-connect-watchdog.h"

void sl_connect_watchdog_init(void)
{
#ifndef SL_CONNECT_DISABLE_WATCHDOG

  // Enable LE interface
#if !defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_HFLE, true);
  CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);
#endif

#if defined(_SILICON_LABS_32B_SERIES_2) && !defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
  CMU_ClockEnable(cmuClock_WDOG0, true);
#endif

  // Make sure FULL reset is used on WDOG timeout
#if defined(_RMU_CTRL_WDOGRMODE_MASK)
  RMU_ResetControl(rmuResetWdog, rmuResetModeFull);
#endif
  WDOG_Init_TypeDef init = WDOG_INIT_DEFAULT;

  // The default timeout of wdogPeriod_64k will trigger
  // watchdog reset after 2 seconds (64k / 32k) and
  // warning interrupt is triggered after 1.5 seconds (75% of timeout).
  init.perSel = wdogPeriod_64k;
  init.warnSel = wdogWarnTime75pct;

  // Counter keeps running during debug halt
  init.debugRun = 0;

#if defined(_WDOG_CTRL_CLKSEL_MASK)
  init.clkSel = wdogClkSelLFRCO;
#else
  // Series 2 devices select watchdog oscillator with the CMU.
  CMU_CLOCK_SELECT_SET(WDOG0, LFRCO);
#endif

  WDOGn_Init(DEFAULT_WDOG, &init);

  /* Enable WARN interrupt. */
#if defined(WDOG_IF_WARN) && !defined(BOOTLOADER)
  NVIC_ClearPendingIRQ(WDOG0_IRQn);
  WDOGn_IntClear(DEFAULT_WDOG, WDOG_IF_WARN);
  NVIC_EnableIRQ(WDOG0_IRQn);
  WDOGn_IntEnable(DEFAULT_WDOG, WDOG_IEN_WARN);
#endif

#endif // SL_CONNECT_DISABLE_WATCHDOG
}

#if (_SILICON_LABS_32B_SERIES >= 1)
void WDOG0_IRQHandler(void)
{
  uint32_t interrupts;

  interrupts = WDOGn_IntGet(DEFAULT_WDOG);
  WDOGn_IntClear(DEFAULT_WDOG, interrupts);
}
#endif

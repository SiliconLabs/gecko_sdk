/***************************************************************************//**
 * @file sl_legacy_hal_wdog_config.h
 * @brief Legacy HAL watchdog configuration file.
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

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_LEGACY_HAL_WDOG_CONFIG_H
#define SL_LEGACY_HAL_WDOG_CONFIG_H

// <h> Legacy HAL WDOG Configurations

// <e SL_LEGACY_HAL_DISABLE_WATCHDOG> Disable calling halInternalEnableWatchDog in base-replacement.c's halInit().
// <i> Default: 0
#define SL_LEGACY_HAL_DISABLE_WATCHDOG 0
// </e>

// <o SL_LEGACY_HAL_WDOGn> WDOG to use for SL_LEGACY_HAL_WDOGn.
// <i> Default: 0
// <0=> WDOG0
// <1=> WDOD1
#define SL_LEGACY_HAL_WDOGn 0

// <o SL_LEGACY_HAL_WDOG_PERIOD> Period for SL_LEGACY_HAL_WDOG timeout.
// <i> Default: wdogPeriod_64k
// <i> The default period of wdogPeriod_64k will trigger watchdog reset after 2 seconds (64k / 32k) and warning interrupt is triggered after 1.5 seconds (75% of timeout).
// <wdogPeriod_9=> wdogPeriod_9 / 9 clock periods
// <wdogPeriod_17=> wdogPeriod_17 / 17 clock periods
// <wdogPeriod_33=> wdogPeriod_33 / 33 clock periods
// <wdogPeriod_65=> wdogPeriod_65 / 65 clock periods
// <wdogPeriod_129=> wdogPeriod_129 / 129 clock periods
// <wdogPeriod_257=> wdogPeriod_257 / 257 clock periods
// <wdogPeriod_513=> wdogPeriod_513 / 513 clock periods
// <wdogPeriod_1k=> wdogPeriod_1k / 1025 clock periods
// <wdogPeriod_2k=> wdogPeriod_2k / 2049 clock periods
// <wdogPeriod_4k=> wdogPeriod_4k / 4097 clock periods
// <wdogPeriod_8k=> wdogPeriod_8k / 8193 clock periods
// <wdogPeriod_16k=> wdogPeriod_16k / 16385 clock periods
// <wdogPeriod_32k=> wdogPeriod_32k / 32769 clock periods
// <wdogPeriod_64k=> wdogPeriod_64k / 65537 clock periods
// <wdogPeriod_128k=> wdogPeriod_128k / 131073 clock periods
// <wdogPeriod_256k=> wdogPeriod_256k / 262145 clock periods
#define SL_LEGACY_HAL_WDOG_PERIOD wdogPeriod_64k

// <o SL_LEGACY_HAL_WDOG_WARNING> Warning for SL_LEGACY_HAL_WDOG timeout.
// <i> Default: wdogWarnTime75pct
// <i> The default warning of wdogWarnTime75pct will trigger warning interrupt after 1.5 seconds (75% of timeout) if the period is wdogPeriod_64k.
// <wdogWarnDisable=> wdogWarnDisable / Watchdog warning period is disabled
// <wdogWarnTime25pct=> wdogWarnTime25pct / Watchdog warning period is 25% of the timeout
// <wdogWarnTime50pct=> wdogWarnTime50pct / Watchdog warning period is 50% of the timeout
// <wdogWarnTime75pct=> wdogWarnTime75pct / Watchdog warning period is 75% of the timeout
#define SL_LEGACY_HAL_WDOG_WARNING wdogWarnTime75pct

// <e SL_LEGACY_HAL_WDOG_DEBUG_RUN> Counter keeps running during debug halt.
// <i> Default: 0
#define SL_LEGACY_HAL_WDOG_DEBUG_RUN 0
// </e>

// </h>

#endif /* SL_LEGACY_HAL_WDOG_CONFIG_H */

// <<< end of configuration section >>>

/**
 * @file
 * ZAF wrapper for the platform watchdog.
 *
 * @warning This is a temporary, internal ZAF module and must not be used by applications. The
 *          interface might be changed or removed completely and replaced by something else.
 * @copyright 2021 Silicon Laboratories Inc.
 */
#ifndef ZAF_APPLICATIONUTILITIES_ZAF_WATCHDOG_H_
#define ZAF_APPLICATIONUTILITIES_ZAF_WATCHDOG_H_

#include <stdbool.h>

/**
 * Returns whether the watchdog is enabled.
 * @return true if watchdog is enabled, false if not.
 */
bool ZAF_is_watchdog_enabled(void);

/**
 * Enables or disables the watchdog based on the input.
 * @param enable true enables the watchdog and false disables it.
 */
void ZAF_enable_watchdog(bool enable);

#endif /* ZAF_APPLICATIONUTILITIES_ZAF_WATCHDOG_H_ */

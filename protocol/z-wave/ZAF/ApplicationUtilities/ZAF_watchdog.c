/**
 @copyright 2021 Silicon Laboratories Inc.
*/
#include "ZAF_watchdog.h"
#include "em_wdog.h"

bool ZAF_is_watchdog_enabled(void) {
  return WDOG_IsEnabled();
}

void ZAF_enable_watchdog(bool enable) {
  WDOG_Enable(enable);
}

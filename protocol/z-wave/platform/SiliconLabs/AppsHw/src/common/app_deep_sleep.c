/**
 * @file
 * Platform abstraction for all sleeping reporting applications
 *
 * @copyright 2021 Silicon Laboratories Inc.
 */
#include "app_hw.h"
#include "board.h"

void app_hw_deep_sleep_wakeup_handler(void)
{
  uint32_t em4_wakeup_flags = Board_GetGpioEm4Flags();

  if (0 != em4_wakeup_flags) {
    Board_ProcessEm4PinWakeupFlags(em4_wakeup_flags);
  }
}

/**
 * @file
 * Utilities for accessing the Silicon Labs bootloader reset cause.
 * @copyright 2019 Silicon Laboratories Inc.
 */

#include <btl_reset_cause_util.h>
#include <em_device.h>
#include <btl_reset_info.h>
//#define DEBUGPRINT
#include <DebugPrint.h>
#include <ZAF_Common_interface.h>
#include <stddef.h>
#include <ZW_system_startup_api.h>

extern BootloaderResetCause_t m_resetinfo;
static BootloaderResetCause_t * pBootInfo = &m_resetinfo;

bool CC_FirmwareUpdate_IsFirstBoot(uint16_t * pBootReason)
{
  bool isFirstBoot = false;
  DPRINTF("\nBTL rst reason: %x", pBootInfo->reason);

  //First boot is always triggered by Software Reset.
  if (GetResetReason() != ERESETREASON_SOFTWARE)
  {
    pBootReason = NULL;
    return false;
  }

  if ((BOOTLOADER_RESET_REASON_GO <= pBootInfo->reason) && (BOOTLOADER_RESET_REASON_TIMEOUT >= pBootInfo->reason))
  {
    // We booted after a firmware update.
    isFirstBoot = true;
  }

  *pBootReason = pBootInfo->reason;

  // Make sure to clear this reason so that we do not trigger the above on every boot.
  pBootInfo->reason = 0xFFFF; // Using a value unknown to the bootloader (btl_reset_info.h)

  return isFirstBoot;
}

void CC_FirmwareUpdate_InvalidateImage(void)
{
  pBootInfo->signature = BOOTLOADER_RESET_SIGNATURE_INVALID;
}

/***************************************************************************//**
 * @file
 * @brief Reset cause signaling for the Silicon Labs bootloader
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "core/btl_reset.h"
#include "api/btl_reset_info.h"
#include <stdbool.h>

/// Reset signature when counter is active
#define BOOTLOADER_RESET_COUNTER_SIGNATURE      0xABC0u
/// Mask for accessing the counter signature
#define BOOTLOADER_RESET_COUNTER_SIGNATURE_MASK 0xFFF0u

#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
extern uint32_t __ResetReasonStart__;
#elif defined(__ICCARM__)
#pragma section = "BOOTLOADER_RESET_REASON"
#endif
#endif

void reset_setResetReason(uint16_t resetReason)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t *cause = (BootloaderResetCause_t *) (resetReasonBase);

  cause->reason = resetReason;

  if (!reset_resetCounterEnabled()) {
    // Only update the signature when the counter is not in use.
    cause->signature = BOOTLOADER_RESET_SIGNATURE_VALID;
  }
}

void reset_invalidateResetReason(void)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t *cause = (BootloaderResetCause_t *) (resetReasonBase);

  cause->signature = BOOTLOADER_RESET_SIGNATURE_INVALID;
}

void reset_enableResetCounter(void)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t *cause = (BootloaderResetCause_t *) (resetReasonBase);

  // Set the upper 12 bits to a shorter signature and use the lower 4 bits
  // for the counter value (starts at 0).
  cause->signature = (BOOTLOADER_RESET_COUNTER_SIGNATURE
                      & BOOTLOADER_RESET_COUNTER_SIGNATURE_MASK);
}

void reset_disableResetCounter(void)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t *cause = (BootloaderResetCause_t *) (resetReasonBase);

  cause->signature = BOOTLOADER_RESET_SIGNATURE_VALID;
}

bool reset_resetCounterEnabled(void)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t *cause = (BootloaderResetCause_t *) (resetReasonBase);

  if ((cause->signature & BOOTLOADER_RESET_COUNTER_SIGNATURE_MASK)
      == BOOTLOADER_RESET_COUNTER_SIGNATURE) {
    return true;
  } else {
    return false;
  }
}

uint8_t reset_getResetCounter(void)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t *cause = (BootloaderResetCause_t *) (resetReasonBase);

  // Return 0 if the reset counter is not enabled
  return (uint8_t)(reset_resetCounterEnabled() ? cause->signature & 0xFu : 0u);
}

void reset_incrementResetCounter(void)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t *cause = (BootloaderResetCause_t *) (resetReasonBase);

  // Only increment when the counter signature is set
  if (reset_resetCounterEnabled()) {
    if ((cause->signature & 0xFu) < 0xFu) {
      cause->signature++;
    } else {
      // Set counter back to 0 in case of overflow.
      cause->signature &= BOOTLOADER_RESET_COUNTER_SIGNATURE_MASK;
    }
  }
}

void reset_resetWithReason(uint16_t resetReason)
{
  reset_setResetReason(resetReason);

  // Trigger a software system reset
#if defined(RMU_PRESENT)
  // Set reset mode to EXTENDED reset
  RMU->CTRL = (RMU->CTRL & ~_RMU_CTRL_SYSRMODE_MASK) | RMU_CTRL_SYSRMODE_EXTENDED;
#endif
  NVIC_SystemReset();
}

uint16_t reset_classifyReset(void)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t* cause = (BootloaderResetCause_t*) (resetReasonBase);

  if (cause->signature == BOOTLOADER_RESET_SIGNATURE_VALID) {
    return reset_getResetReason();
  } else if ((cause->signature == 0x0000u)
             && (cause->reason == 0x0001u)) {
    // BLE reset cause
    return BOOTLOADER_RESET_REASON_BOOTLOAD;
  } else {
    return BOOTLOADER_RESET_REASON_UNKNOWN;
  }
}

uint16_t reset_getResetReason(void)
{
#if defined BOOTLOADER_ENABLE
#if defined(__GNUC__)
  uint32_t resetReasonBase = (uint32_t)&__ResetReasonStart__;
#elif defined(__ICCARM__)
  void *resetReasonBase =   __section_begin("BOOTLOADER_RESET_REASON");
#endif
#else
  uint32_t resetReasonBase = SRAM_BASE;
#endif
  BootloaderResetCause_t* cause = (BootloaderResetCause_t*) (resetReasonBase);
  return cause->reason;
}

/***************************************************************************//**
 * @file
 * @brief Core helper functions for Silicon Labs bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef BTL_HELPER_H
#define BTL_HELPER_H

#include "em_device.h"

static inline void cleanUpRAM(uint32_t startAddr, const uint32_t endAddr)
{
  volatile uint32_t *volatile ramStart = (volatile uint32_t *volatile)startAddr;
  while ((uint32_t)ramStart < endAddr) {
    *ramStart = 0u;
    ramStart++;
  }
}

static inline void jumpToApplicationRoutine(uint32_t startOfAppSpace)
{
#if defined(BOOTLOADER_SECURE)
  // We should not leave any traces of the secure bootloader before jumping into the application
  // clean up entire RAM content except for the reset reason word
  __ASM volatile(
    "ldr r4,=0                 \n"
    "mov r2, %[ramBase]        \n" // Load start address
    "mov r3, %[ramEnd]         \n" // Load end address
    "ram_clean_up_loop:        \n"
    "cmp r2, r3                \n" // Check if we have reached the end address
    "beq ram_clean_up_finished \n"
    "str r4, [r2, r4]          \n" // Clear the RAM content pointed by R2
    "add r2, r2, #4            \n" // Increment by 4 to get to the next word address
    "b ram_clean_up_loop       \n"
    "ram_clean_up_finished:    \n"
#else
  // Load SP and PC of application
  __ASM volatile(
#endif // BOOTLOADER_SECURE
    "mov r0, %[startOfAppSpace]       \n" // Load address of SP into R0
    "ldr r1, [r0]                     \n" // Load SP into R1
    "msr msp, r1                      \n" // Set MSP
    "msr psp, r1                      \n" // Set PSP
    "ldr r0, [r0, #4]                 \n" // Load PC into R0
    "mov pc, r0                       \n" // Set PC
    : // No outputs
#if defined(BOOTLOADER_SECURE)
    :[startOfAppSpace] "r" (startOfAppSpace), [ramBase] "r" (SRAM_BASE + 4u), [ramEnd] "r" (SRAM_BASE + SRAM_SIZE)  // Inputs
    : "r0", "r1", "r2", "r3", "r4" // Clobbered registers
    );
#else
    :[startOfAppSpace] "r" (startOfAppSpace)  // Inputs
    : "r0", "r1" // Clobbered registers
    );
#endif
}

#endif // BTL_HELPER_H

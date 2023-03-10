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
#if defined(_SILICON_LABS_32B_SERIES_2)
#include "fih.h"
#endif
// Linker Symbols
#if defined (__GNUC__)
extern uint32_t __StackTop, __StackLimit;
extern uint32_t __data_start__, __data_end__;
extern uint32_t __bss_start__, __bss_end__;
#else
extern uint32_t CSTACK$$Base, CSTACK$$Limit;
extern uint32_t STACKSEAL$$Limit, HEAP$$Base;
#endif
#if defined(_SILICON_LABS_32B_SERIES_2)
static inline fih_int cleanUpRAM(uint32_t startAddr, const uint32_t endAddr)
{
  fih_int fih_rc = FIH_FAILURE;
  volatile uint32_t *volatile ramStart = (volatile uint32_t *)startAddr;
  while ((uint32_t)ramStart < endAddr) {
    *ramStart = 0u;
    ramStart++;
  }
  fih_rc = FIH_SUCCESS;
  FIH_RET(fih_rc);
}
#endif
static inline void jumpToApplicationRoutine(uint32_t startOfAppSpace)
{
#if defined(BOOTLOADER_SECURE)

// Erase rw section
  __ASM volatile(
    "ldr r3,=0                  \n"
    "mov r1, %[rwStart]         \n" // Load start address
    "mov r2, %[rwEnd]           \n" // Load end address
#if defined(__GNUC__)
    "mov r4, %[bssStart]        \n" // Load bss section start address
    "mov r5, %[bssEnd]          \n" // Load bss section end address
#endif
    "data_clean_up_loop:        \n"
    "cmp r1, r2                 \n" // Check if we have reached the end address
    "beq data_clean_up_finished \n"
    "str r3, [r1]               \n" // Clear the RAM content pointed by R1
    "add r1, r1, #4             \n" // Increment by 4 to get to the next word address
    "b data_clean_up_loop       \n"
    "data_clean_up_finished:    \n"
#if defined(__GNUC__)
    "bss_clean_up_loop:         \n"
    "cmp r4, r5                 \n" // Check if we have reached the end address
    "beq bss_clean_up_finished  \n"
    "str r3, [r4]               \n" // Clear the RAM content pointed by R4
    "add r4, r4, #4             \n" // Increment by 4 to get to the next word address
    "b bss_clean_up_loop        \n"
    "bss_clean_up_finished:     \n"
#endif
    : //No outputs
#if defined(__GNUC__)
    :[rwStart] "r" (&__data_start__), [rwEnd] "r" (&__data_end__), [bssStart] "r" (&__bss_start__), [bssEnd] "r" (&__bss_end__) //Inputs
    : "r1", "r2", "r3", "r4", "r5" //Clobbered registers
    );
#else
    :[rwStart] "r" (&STACKSEAL$$Limit), [rwEnd] "r" (&HEAP$$Base) //Inputs
    : "r1", "r2", "r3" //Clobbered registers
    );
#endif

#if defined(TEST_BOOTLOADER_RAM_CLEAN_UP)
  __ASM volatile(
    "mov r5, %[dataSection]       \n"     // Address of the last word in the rw section
    "mov r6, %[stackSection]      \n"     // Address of the last word in the stack section
    "mov r7, #0xFEEB              \n"     // Magic word stored at the end of data and stack sections
    "sub r5, r5, #4               \n"
    "sub r6, r6, #4               \n"
    "str r7, [r5]                 \n"     // Store magic word at the end of data section
    "str r7, [r6]                 \n"     // Store magic word at the end of stack section
    : //No outputs
#if defined(__GNUC__)
    :[dataSection] "r" (&__bss_end__), [stackSection] "r" (&__StackTop) //Inputs
    : "r5", "r6", "r7", "r3" //Clobbered registers
    );
#else
    :[dataSection] "r" (&HEAP$$Base), [stackSection] "r" (&CSTACK$$Limit) //Inputs
    : "r5", "r6", "r7", "r3" //Clobbered registers
    );
#endif
#endif  // end of TEST_BOOTLOADER_RAM_CLEAN_UP

#endif // end of BOOTLOADER_SECURE

#if defined(BOOTLOADER_SECURE)
  // We should not leave any traces of the secure bootloader before jumping into the application
  // clean up entire RAM content except for the reset reason word
  __ASM volatile(
    "ldr r4,=0                 \n"
    "mov r2, %[stackBase]      \n" // Load start address
    "mov r3, %[stackTop]       \n" // Load end address
#if defined(TEST_BOOTLOADER_RAM_CLEAN_UP)
    "sub r3, r3, #4            \n" // Account for magic word at the top of stack section
#endif
    "mov r1, %[ramBase]        \n"
    "cmp r2, r1                \n" // Check if stack base is equal to SRAM_BASE
    "bne ram_clean_up_loop     \n"
    "add r2, r2, #4            \n" // Increment by 4 to omit reset reason word in SRAM
    "ram_clean_up_loop:        \n"
    "cmp r2, r3                \n" // Check if we have reached the end address
    "beq ram_clean_up_finished \n"
    "str r4, [r2]              \n" // Clear the RAM content pointed by R2
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
#if defined(__GNUC__)
    :[startOfAppSpace] "r" (startOfAppSpace), [stackBase] "r" (&__StackLimit), [stackTop] "r" (&__StackTop), [ramBase] "r" (SRAM_BASE)  // Inputs
    : "r0", "r1", "r2", "r3", "r4" // Clobbered registers
    );
#else
    :[startOfAppSpace] "r" (startOfAppSpace), [stackBase] "r" (&CSTACK$$Base), [stackTop] "r" (&CSTACK$$Limit), [ramBase] "r" (SRAM_BASE)
    : "r0", "r1", "r2", "r3", "r4" // Clobbered registers
    );
#endif // __GNUC__
#else
    :[startOfAppSpace] "r" (startOfAppSpace)  // Inputs
    : "r0", "r1" // Clobbered registers
    );
#endif  // BOOTLOADER_SECURE
}

#endif // BTL_HELPER_H

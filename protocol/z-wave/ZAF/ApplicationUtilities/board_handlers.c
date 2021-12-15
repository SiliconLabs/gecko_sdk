/**
 * @file
 * This file implements default exception handlers.
 * @copyright 2019 Silicon Laboratories Inc.
 *
 */

#include "Board.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

/* this might not work if the FPU is active, because then FPU registers are also pushed on the stack. */
#define PC_STACK_POS 8

void BoardHandlersInit() {
  //Enable Busfaults and usage faults
  SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA_Msk;
  SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;
}

static void  fault_blink() {
  while(1) {
    Led(LED_D2,OFF);
    Led(LED_D3,ON);
    for(int i=0; i< 1000000; i++) ;
    Led(LED_D2,ON);
    Led(LED_D3,OFF);
    for(int i=0; i< 1000000; i++) ;
  }
}
void Default_Handler() {
  uint32_t* sp = (uint32_t*)__get_PSP();
  DPRINTF("%s exception code %i On PC=%08X ",__func__,SCB->ICSR & 0xff, sp[PC_STACK_POS]);
  fault_blink();
}

void HardFault_Handler() {
  uint32_t* sp = (uint32_t*)__get_PSP();
  DPRINTF("%s exception code %i On PC=%08X ",__func__,SCB->ICSR & 0xff, sp[PC_STACK_POS]);
  fault_blink();
}

void BusFault_Handler() {
  uint32_t* sp = (uint32_t*)__get_PSP();
  DPRINTF("%s exception code %i On PC=%08X ",__func__,SCB->ICSR & 0xff, sp[PC_STACK_POS]);
  fault_blink();
}
void UsageFault_Handler() {
  uint32_t* sp = (uint32_t*)__get_PSP();
  DPRINTF("%s exception code %i On PC=%08X ",__func__,SCB->ICSR & 0xff, sp[PC_STACK_POS]);
  fault_blink();
}

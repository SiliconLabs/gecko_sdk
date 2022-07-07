/**************************************************************************//**
 * @file
 * @brief CMSIS Compatible EFR32FG23 startup file in C for IAR EWARM
 ******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories, Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/

#include <stdbool.h>
#include "em_device.h"        /* The correct device header file. */

#ifdef BOOTLOADER_ENABLE
#include "api/btl_interface.h"

#endif

#pragma language=extended
#pragma segment="CSTACK"

#ifdef BOOTLOADER_ENABLE
extern MainBootloaderTable_t mainStageTable;

extern void SystemInit2(void);

/*----------------------------------------------------------------------------
 * Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void (*pFunc)(void);

#endif

/* IAR start function */
extern void __iar_program_start(void);
/* CMSIS init function */
extern void SystemInit(void);

/* Auto defined by linker */
extern unsigned char CSTACK$$Limit;

__weak void Reset_Handler(void)
{
  SystemInit();

#ifdef BOOTLOADER_ENABLE
  SystemInit2();
#endif

  __iar_program_start();
}

/* Provide a dummy value for the sl_app_properties symbol. */
void sl_app_properties(void);   /* Prototype to please MISRA checkers. */
__weak void sl_app_properties(void)
{
}

__weak void NMI_Handler(void)
{
  while (true) {
  }
}

__weak void HardFault_Handler(void)
{
  while (true) {
  }
}

__weak void MemManage_Handler(void)
{
  while (true) {
  }
}

__weak void BusFault_Handler(void)
{
  while (true) {
  }
}

__weak void UsageFault_Handler(void)
{
  while (true) {
  }
}

__weak void SVC_Handler(void)
{
  while (true) {
  }
}

__weak void DebugMon_Handler(void)
{
  while (true) {
  }
}

__weak void PendSV_Handler(void)
{
  while (true) {
  }
}

__weak void SysTick_Handler(void)
{
  while (true) {
  }
}
__weak void SMU_SECURE_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SMU_PRIVILEGED_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SMU_NS_PRIVILEGED_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EMU_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER1_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER2_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER3_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER4_IRQHandler(void)
{
  while (true) {
  }
}
__weak void USART0_RX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void USART0_TX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART0_RX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART0_TX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART1_RX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART1_TX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART2_RX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART2_TX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void ICACHE0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void BURTC_IRQHandler(void)
{
  while (true) {
  }
}
__weak void LETIMER0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SYSCFG_IRQHandler(void)
{
  while (true) {
  }
}
__weak void MPAHBRAM_IRQHandler(void)
{
  while (true) {
  }
}
__weak void LDMA_IRQHandler(void)
{
  while (true) {
  }
}
__weak void LFXO_IRQHandler(void)
{
  while (true) {
  }
}
__weak void LFRCO_IRQHandler(void)
{
  while (true) {
  }
}
__weak void ULFRCO_IRQHandler(void)
{
  while (true) {
  }
}
__weak void GPIO_ODD_IRQHandler(void)
{
  while (true) {
  }
}
__weak void GPIO_EVEN_IRQHandler(void)
{
  while (true) {
  }
}
__weak void I2C0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void I2C1_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EMUDG_IRQHandler(void)
{
  while (true) {
  }
}
__weak void AGC_IRQHandler(void)
{
  while (true) {
  }
}
__weak void BUFC_IRQHandler(void)
{
  while (true) {
  }
}
__weak void FRC_PRI_IRQHandler(void)
{
  while (true) {
  }
}
__weak void FRC_IRQHandler(void)
{
  while (true) {
  }
}
__weak void MODEM_IRQHandler(void)
{
  while (true) {
  }
}
__weak void PROTIMER_IRQHandler(void)
{
  while (true) {
  }
}
__weak void RAC_RSM_IRQHandler(void)
{
  while (true) {
  }
}
__weak void RAC_SEQ_IRQHandler(void)
{
  while (true) {
  }
}
__weak void HOSTMAILBOX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SYNTH_IRQHandler(void)
{
  while (true) {
  }
}
__weak void ACMP0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void ACMP1_IRQHandler(void)
{
  while (true) {
  }
}
__weak void WDOG0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void WDOG1_IRQHandler(void)
{
  while (true) {
  }
}
__weak void HFXO0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void HFRCO0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void HFRCOEM23_IRQHandler(void)
{
  while (true) {
  }
}
__weak void CMU_IRQHandler(void)
{
  while (true) {
  }
}
__weak void AES_IRQHandler(void)
{
  while (true) {
  }
}
__weak void IADC_IRQHandler(void)
{
  while (true) {
  }
}
__weak void MSC_IRQHandler(void)
{
  while (true) {
  }
}
__weak void DPLL0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EMUEFP_IRQHandler(void)
{
  while (true) {
  }
}
__weak void DCDC_IRQHandler(void)
{
  while (true) {
  }
}
__weak void VDAC_IRQHandler(void)
{
  while (true) {
  }
}
__weak void PCNT0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SW0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SW1_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SW2_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SW3_IRQHandler(void)
{
  while (true) {
  }
}
__weak void KERNEL0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void KERNEL1_IRQHandler(void)
{
  while (true) {
  }
}
__weak void M33CTI0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void M33CTI1_IRQHandler(void)
{
  while (true) {
  }
}
__weak void FPUEXH_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SETAMPERHOST_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SEMBRX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SEMBTX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void LESENSE_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SYSRTC_APP_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SYSRTC_SEQ_IRQHandler(void)
{
  while (true) {
  }
}
__weak void LCD_IRQHandler(void)
{
  while (true) {
  }
}
__weak void KEYSCAN_IRQHandler(void)
{
  while (true) {
  }
}
__weak void RFECA0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void RFECA1_IRQHandler(void)
{
  while (true) {
  }
}

#pragma data_alignment=256
#pragma location = ".intvec"
const tVectorEntry __vector_table[] = {
  { .topOfStack = &CSTACK$$Limit },    /* Initial Stack Pointer.
                                        * With IAR, the CSTACK is defined
                                        * via project options settings.   */
  { Reset_Handler },
  { NMI_Handler },
  { HardFault_Handler },
  { MemManage_Handler },
  { BusFault_Handler },
  { UsageFault_Handler },
  { 0 },
  { 0 },
  { 0 },
#ifdef BOOTLOADER_ENABLE
  { (pFunc) & mainStageTable },
#else
  { 0 },
#endif
  { SVC_Handler },
  { DebugMon_Handler },
  { sl_app_properties },
  { PendSV_Handler },
  { SysTick_Handler },
  { SMU_SECURE_IRQHandler },        /* -16 - SMU_SECURE */
  { SMU_PRIVILEGED_IRQHandler },    /* -15 - SMU_PRIVILEGED */
  { SMU_NS_PRIVILEGED_IRQHandler }, /* -14 - SMU_NS_PRIVILEGED */
  { EMU_IRQHandler },               /* -13 - EMU */
  { TIMER0_IRQHandler },            /* -12 - TIMER0 */
  { TIMER1_IRQHandler },            /* -11 - TIMER1 */
  { TIMER2_IRQHandler },            /* -10 - TIMER2 */
  { TIMER3_IRQHandler },            /* -9 - TIMER3 */
  { TIMER4_IRQHandler },            /* -8 - TIMER4 */
  { USART0_RX_IRQHandler },         /* -7 - USART0_RX */
  { USART0_TX_IRQHandler },         /* -6 - USART0_TX */
  { EUSART0_RX_IRQHandler },        /* -5 - EUSART0_RX */
  { EUSART0_TX_IRQHandler },        /* -4 - EUSART0_TX */
  { EUSART1_RX_IRQHandler },        /* -3 - EUSART1_RX */
  { EUSART1_TX_IRQHandler },        /* -2 - EUSART1_TX */
  { EUSART2_RX_IRQHandler },        /* -1 - EUSART2_RX */
  { EUSART2_TX_IRQHandler },        /* 00 - EUSART2_TX */
  { ICACHE0_IRQHandler },           /* 01 - ICACHE0 */
  { BURTC_IRQHandler },             /* 02 - BURTC */
  { LETIMER0_IRQHandler },          /* 03 - LETIMER0 */
  { SYSCFG_IRQHandler },            /* 04 - SYSCFG */
  { MPAHBRAM_IRQHandler },          /* 05 - MPAHBRAM */
  { LDMA_IRQHandler },              /* 06 - LDMA */
  { LFXO_IRQHandler },              /* 07 - LFXO */
  { LFRCO_IRQHandler },             /* 08 - LFRCO */
  { ULFRCO_IRQHandler },            /* 09 - ULFRCO */
  { GPIO_ODD_IRQHandler },          /* 10 - GPIO_ODD */
  { GPIO_EVEN_IRQHandler },         /* 11 - GPIO_EVEN */
  { I2C0_IRQHandler },              /* 12 - I2C0 */
  { I2C1_IRQHandler },              /* 13 - I2C1 */
  { EMUDG_IRQHandler },             /* 14 - EMUDG */
  { AGC_IRQHandler },               /* 15 - AGC */
  { BUFC_IRQHandler },              /* 16 - BUFC */
  { FRC_PRI_IRQHandler },           /* 17 - FRC_PRI */
  { FRC_IRQHandler },               /* 18 - FRC */
  { MODEM_IRQHandler },             /* 19 - MODEM */
  { PROTIMER_IRQHandler },          /* 20 - PROTIMER */
  { RAC_RSM_IRQHandler },           /* 21 - RAC_RSM */
  { RAC_SEQ_IRQHandler },           /* 22 - RAC_SEQ */
  { HOSTMAILBOX_IRQHandler },       /* 23 - HOSTMAILBOX */
  { SYNTH_IRQHandler },             /* 24 - SYNTH */
  { ACMP0_IRQHandler },             /* 25 - ACMP0 */
  { ACMP1_IRQHandler },             /* 26 - ACMP1 */
  { WDOG0_IRQHandler },             /* 27 - WDOG0 */
  { WDOG1_IRQHandler },             /* 28 - WDOG1 */
  { HFXO0_IRQHandler },             /* 29 - HFXO0 */
  { HFRCO0_IRQHandler },            /* 30 - HFRCO0 */
  { HFRCOEM23_IRQHandler },         /* 31 - HFRCOEM23 */
  { CMU_IRQHandler },               /* 32 - CMU */
  { AES_IRQHandler },               /* 33 - AES */
  { IADC_IRQHandler },              /* 34 - IADC */
  { MSC_IRQHandler },               /* 35 - MSC */
  { DPLL0_IRQHandler },             /* 36 - DPLL0 */
  { EMUEFP_IRQHandler },            /* 37 - EMUEFP */
  { DCDC_IRQHandler },              /* 38 - DCDC */
  { VDAC_IRQHandler },              /* 39 - VDAC */
  { PCNT0_IRQHandler },             /* 40 - PCNT0 */
  { SW0_IRQHandler },               /* 41 - SW0 */
  { SW1_IRQHandler },               /* 42 - SW1 */
  { SW2_IRQHandler },               /* 43 - SW2 */
  { SW3_IRQHandler },               /* 44 - SW3 */
  { KERNEL0_IRQHandler },           /* 45 - KERNEL0 */
  { KERNEL1_IRQHandler },           /* 46 - KERNEL1 */
  { M33CTI0_IRQHandler },           /* 47 - M33CTI0 */
  { M33CTI1_IRQHandler },           /* 48 - M33CTI1 */
  { FPUEXH_IRQHandler },            /* 49 - FPUEXH */
  { SETAMPERHOST_IRQHandler },      /* 50 - SETAMPERHOST */
  { SEMBRX_IRQHandler },            /* 51 - SEMBRX */
  { SEMBTX_IRQHandler },            /* 52 - SEMBTX */
  { LESENSE_IRQHandler },           /* 53 - LESENSE */
  { SYSRTC_APP_IRQHandler },        /* 54 - SYSRTC_APP */
  { SYSRTC_SEQ_IRQHandler },        /* 55 - SYSRTC_SEQ */
  { LCD_IRQHandler },               /* 56 - LCD */
  { KEYSCAN_IRQHandler },           /* 57 - KEYSCAN */
  { RFECA0_IRQHandler },            /* 58 - RFECA0 */
  { RFECA1_IRQHandler },            /* 59 - RFECA1 */
};

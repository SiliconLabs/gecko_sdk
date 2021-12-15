/**************************************************************************//**
 * @file
 * @brief CMSIS Compatible EFR32FG25 startup file in C for IAR EWARM
 ******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories, Inc. www.silabs.com</b>
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
__weak void ETAMPDET_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER4_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER5_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER6_IRQHandler(void)
{
  while (true) {
  }
}
__weak void TIMER7_IRQHandler(void)
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
__weak void EUSART3_RX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART3_TX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART4_RX_IRQHandler(void)
{
  while (true) {
  }
}
__weak void EUSART4_TX_IRQHandler(void)
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
__weak void USB_IRQHandler(void)
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
__weak void RFFPLL_IRQHandler(void)
{
  while (true) {
  }
}
__weak void USBPLL0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void AHB2AHB0_IRQHandler(void)
{
  while (true) {
  }
}
__weak void AHB2AHB1_IRQHandler(void)
{
  while (true) {
  }
}
__weak void AHB2AHB2_IRQHandler(void)
{
  while (true) {
  }
}
__weak void AHB2AHB3_IRQHandler(void)
{
  while (true) {
  }
}
__weak void RFTIMER_IRQHandler(void)
{
  while (true) {
  }
}
__weak void SOFTM_IRQHandler(void)
{
  while (true) {
  }
}
__weak void RFLDMA_IRQHandler(void)
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
  { ETAMPDET_IRQHandler },          /* -8 - ETAMPDET */
  { TIMER4_IRQHandler },            /* -7 - TIMER4 */
  { TIMER5_IRQHandler },            /* -6 - TIMER5 */
  { TIMER6_IRQHandler },            /* -5 - TIMER6 */
  { TIMER7_IRQHandler },            /* -4 - TIMER7 */
  { EUSART0_RX_IRQHandler },        /* -3 - EUSART0_RX */
  { EUSART0_TX_IRQHandler },        /* -2 - EUSART0_TX */
  { EUSART1_RX_IRQHandler },        /* -1 - EUSART1_RX */
  { EUSART1_TX_IRQHandler },        /* 00 - EUSART1_TX */
  { EUSART2_RX_IRQHandler },        /* 01 - EUSART2_RX */
  { EUSART2_TX_IRQHandler },        /* 02 - EUSART2_TX */
  { EUSART3_RX_IRQHandler },        /* 03 - EUSART3_RX */
  { EUSART3_TX_IRQHandler },        /* 04 - EUSART3_TX */
  { EUSART4_RX_IRQHandler },        /* 05 - EUSART4_RX */
  { EUSART4_TX_IRQHandler },        /* 06 - EUSART4_TX */
  { ICACHE0_IRQHandler },           /* 07 - ICACHE0 */
  { BURTC_IRQHandler },             /* 08 - BURTC */
  { LETIMER0_IRQHandler },          /* 09 - LETIMER0 */
  { SYSCFG_IRQHandler },            /* 10 - SYSCFG */
  { MPAHBRAM_IRQHandler },          /* 11 - MPAHBRAM */
  { LDMA_IRQHandler },              /* 12 - LDMA */
  { LFXO_IRQHandler },              /* 13 - LFXO */
  { LFRCO_IRQHandler },             /* 14 - LFRCO */
  { ULFRCO_IRQHandler },            /* 15 - ULFRCO */
  { GPIO_ODD_IRQHandler },          /* 16 - GPIO_ODD */
  { GPIO_EVEN_IRQHandler },         /* 17 - GPIO_EVEN */
  { I2C0_IRQHandler },              /* 18 - I2C0 */
  { I2C1_IRQHandler },              /* 19 - I2C1 */
  { EMUDG_IRQHandler },             /* 20 - EMUDG */
  { AGC_IRQHandler },               /* 21 - AGC */
  { BUFC_IRQHandler },              /* 22 - BUFC */
  { FRC_PRI_IRQHandler },           /* 23 - FRC_PRI */
  { FRC_IRQHandler },               /* 24 - FRC */
  { MODEM_IRQHandler },             /* 25 - MODEM */
  { PROTIMER_IRQHandler },          /* 26 - PROTIMER */
  { RAC_RSM_IRQHandler },           /* 27 - RAC_RSM */
  { RAC_SEQ_IRQHandler },           /* 28 - RAC_SEQ */
  { HOSTMAILBOX_IRQHandler },       /* 29 - HOSTMAILBOX */
  { SYNTH_IRQHandler },             /* 30 - SYNTH */
  { ACMP0_IRQHandler },             /* 31 - ACMP0 */
  { ACMP1_IRQHandler },             /* 32 - ACMP1 */
  { WDOG0_IRQHandler },             /* 33 - WDOG0 */
  { WDOG1_IRQHandler },             /* 34 - WDOG1 */
  { HFXO0_IRQHandler },             /* 35 - HFXO0 */
  { HFRCO0_IRQHandler },            /* 36 - HFRCO0 */
  { HFRCOEM23_IRQHandler },         /* 37 - HFRCOEM23 */
  { CMU_IRQHandler },               /* 38 - CMU */
  { AES_IRQHandler },               /* 39 - AES */
  { IADC_IRQHandler },              /* 40 - IADC */
  { MSC_IRQHandler },               /* 41 - MSC */
  { DPLL0_IRQHandler },             /* 42 - DPLL0 */
  { 0 },                            /* Reserved */
  { DCDC_IRQHandler },              /* 44 - DCDC */
  { VDAC_IRQHandler },              /* 45 - VDAC */
  { PCNT0_IRQHandler },             /* 46 - PCNT0 */
  { USB_IRQHandler },               /* 47 - USB */
  { SW0_IRQHandler },               /* 48 - SW0 */
  { SW1_IRQHandler },               /* 49 - SW1 */
  { SW2_IRQHandler },               /* 50 - SW2 */
  { SW3_IRQHandler },               /* 51 - SW3 */
  { KERNEL0_IRQHandler },           /* 52 - KERNEL0 */
  { KERNEL1_IRQHandler },           /* 53 - KERNEL1 */
  { M33CTI0_IRQHandler },           /* 54 - M33CTI0 */
  { M33CTI1_IRQHandler },           /* 55 - M33CTI1 */
  { FPUEXH_IRQHandler },            /* 56 - FPUEXH */
  { SETAMPERHOST_IRQHandler },      /* 57 - SETAMPERHOST */
  { SEMBRX_IRQHandler },            /* 58 - SEMBRX */
  { SEMBTX_IRQHandler },            /* 59 - SEMBTX */
  { LESENSE_IRQHandler },           /* 60 - LESENSE */
  { SYSRTC_APP_IRQHandler },        /* 61 - SYSRTC_APP */
  { SYSRTC_SEQ_IRQHandler },        /* 62 - SYSRTC_SEQ */
  { RFECA0_IRQHandler },            /* 63 - RFECA0 */
  { RFECA1_IRQHandler },            /* 64 - RFECA1 */
  { RFFPLL_IRQHandler },            /* 65 - RFFPLL */
  { USBPLL0_IRQHandler },           /* 66 - USBPLL0 */
  { AHB2AHB0_IRQHandler },          /* 67 - AHB2AHB0 */
  { AHB2AHB1_IRQHandler },          /* 68 - AHB2AHB1 */
  { AHB2AHB2_IRQHandler },          /* 69 - AHB2AHB2 */
  { AHB2AHB3_IRQHandler },          /* 70 - AHB2AHB3 */
  { RFTIMER_IRQHandler },           /* 71 - RFTIMER */
  { SOFTM_IRQHandler },             /* 72 - SOFTM */
  { RFLDMA_IRQHandler },            /* 73 - RFLDMA */
};

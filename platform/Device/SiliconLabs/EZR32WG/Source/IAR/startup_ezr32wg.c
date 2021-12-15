/***************************************************************************//**
 * @file
 * @brief CMSIS Compatible EZR32WG startup file in C for IAR EWARM
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
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
 ******************************************************************************/

#include <stdbool.h>
#include "em_device.h"        /* The correct device header file. */

#pragma language=extended
#pragma segment="CSTACK"

/* IAR start function */
extern void __iar_program_start(void);
/* CMSIS init function */
extern void SystemInit(void);

/* Auto defined by linker */
extern unsigned char CSTACK$$Limit;

__weak void Reset_Handler(void)
{
  SystemInit();
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

__weak void DMA_IRQHandler(void)
{
  while (true) {
  }
}

__weak void GPIO_EVEN_IRQHandler(void)
{
  while (true) {
  }
}

__weak void TIMER0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void USARTRF0_RX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void USARTRF0_TX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void USB_IRQHandler(void)
{
  while (true) {
  }
}

__weak void ACMP0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void ADC0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void DAC0_IRQHandler(void)
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

__weak void GPIO_ODD_IRQHandler(void)
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

__weak void USART1_RX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void USART1_TX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void LESENSE_IRQHandler(void)
{
  while (true) {
  }
}

__weak void USART2_RX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void USART2_TX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void UART0_RX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void UART0_TX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void UART1_RX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void UART1_TX_IRQHandler(void)
{
  while (true) {
  }
}

__weak void LEUART0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void LEUART1_IRQHandler(void)
{
  while (true) {
  }
}

__weak void LETIMER0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void PCNT0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void PCNT1_IRQHandler(void)
{
  while (true) {
  }
}

__weak void PCNT2_IRQHandler(void)
{
  while (true) {
  }
}

__weak void RTC_IRQHandler(void)
{
  while (true) {
  }
}

__weak void BURTC_IRQHandler(void)
{
  while (true) {
  }
}

__weak void CMU_IRQHandler(void)
{
  while (true) {
  }
}

__weak void VCMP_IRQHandler(void)
{
  while (true) {
  }
}

__weak void MSC_IRQHandler(void)
{
  while (true) {
  }
}

__weak void AES_IRQHandler(void)
{
  while (true) {
  }
}

__weak void EMU_IRQHandler(void)
{
  while (true) {
  }
}

__weak void FPUEH_IRQHandler(void)
{
  while (true) {
  }
}

#pragma data_alignment=256
#pragma location = ".intvec"
const tVectorEntry __vector_table[] = {
  { .topOfStack = &CSTACK$$Limit },  /* With IAR, the CSTACK is defined via */
                                     /* project options settings */

  { Reset_Handler             },
  { NMI_Handler               },
  { HardFault_Handler         },
  { MemManage_Handler         },
  { BusFault_Handler          },
  { UsageFault_Handler        },
  { 0                         },
  { 0                         },
  { 0                         },
  { 0                         },
  { SVC_Handler               },
  { DebugMon_Handler          },
  { sl_app_properties         },
  { PendSV_Handler            },
  { SysTick_Handler           },

  { DMA_IRQHandler            },              /* 0 */
  { GPIO_EVEN_IRQHandler      },              /* 1 */
  { TIMER0_IRQHandler         },              /* 2 */
  { USARTRF0_RX_IRQHandler    },              /* 3 */
  { USARTRF0_TX_IRQHandler    },              /* 4 */
  { USB_IRQHandler            },              /* 5 */
  { ACMP0_IRQHandler          },              /* 6 */
  { ADC0_IRQHandler           },              /* 7 */
  { DAC0_IRQHandler           },              /* 8 */
  { I2C0_IRQHandler           },              /* 9 */
  { I2C1_IRQHandler           },              /* 10 */
  { GPIO_ODD_IRQHandler       },              /* 11 */
  { TIMER1_IRQHandler         },              /* 12 */
  { TIMER2_IRQHandler         },              /* 13 */
  { TIMER3_IRQHandler         },              /* 14 */
  { USART1_RX_IRQHandler      },              /* 15 */
  { USART1_TX_IRQHandler      },              /* 16 */
  { LESENSE_IRQHandler        },              /* 17 */
  { USART2_RX_IRQHandler      },              /* 18 */
  { USART2_TX_IRQHandler      },              /* 19 */
  { UART0_RX_IRQHandler       },              /* 20 */
  { UART0_TX_IRQHandler       },              /* 21 */
  { UART1_RX_IRQHandler       },              /* 22 */
  { UART1_TX_IRQHandler       },              /* 23 */
  { LEUART0_IRQHandler        },              /* 24 */
  { LEUART1_IRQHandler        },              /* 25 */
  { LETIMER0_IRQHandler       },              /* 26 */
  { PCNT0_IRQHandler          },              /* 27 */
  { PCNT1_IRQHandler          },              /* 28 */
  { PCNT2_IRQHandler          },              /* 29 */
  { RTC_IRQHandler            },              /* 30 */
  { BURTC_IRQHandler          },              /* 31 */
  { CMU_IRQHandler            },              /* 32 */
  { VCMP_IRQHandler           },              /* 33 */
  { 0                         },              /* 34 - Reserved */
  { MSC_IRQHandler            },              /* 35 */
  { AES_IRQHandler            },              /* 36 */
  { 0                         },              /* 37 - Reserved */
  { EMU_IRQHandler            },              /* 38 */
  { FPUEH_IRQHandler          },              /* 39 */
};

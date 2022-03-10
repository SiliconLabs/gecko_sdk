/***************************************************************************//**
 * @file
 * @brief CMSIS Compatible MGM13 startup file in C for IAR EWARM
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

__weak void EMU_IRQHandler(void)
{
  while (true) {
  }
}

__weak void FRC_PRI_IRQHandler(void)
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

__weak void RAC_SEQ_IRQHandler(void)
{
  while (true) {
  }
}

__weak void RAC_RSM_IRQHandler(void)
{
  while (true) {
  }
}

__weak void BUFC_IRQHandler(void)
{
  while (true) {
  }
}

__weak void LDMA_IRQHandler(void)
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

__weak void IDAC0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void I2C0_IRQHandler(void)
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

__weak void LEUART0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void PCNT0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void CMU_IRQHandler(void)
{
  while (true) {
  }
}

__weak void MSC_IRQHandler(void)
{
  while (true) {
  }
}

__weak void CRYPTO0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void LETIMER0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void AGC_IRQHandler(void)
{
  while (true) {
  }
}

__weak void PROTIMER_IRQHandler(void)
{
  while (true) {
  }
}

__weak void PRORTC_IRQHandler(void)
{
  while (true) {
  }
}

__weak void RTCC_IRQHandler(void)
{
  while (true) {
  }
}

__weak void SYNTH_IRQHandler(void)
{
  while (true) {
  }
}

__weak void CRYOTIMER_IRQHandler(void)
{
  while (true) {
  }
}

__weak void RFSENSE_IRQHandler(void)
{
  while (true) {
  }
}

__weak void FPUEH_IRQHandler(void)
{
  while (true) {
  }
}

__weak void SMU_IRQHandler(void)
{
  while (true) {
  }
}

__weak void WTIMER0_IRQHandler(void)
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

__weak void I2C1_IRQHandler(void)
{
  while (true) {
  }
}

__weak void VDAC0_IRQHandler(void)
{
  while (true) {
  }
}

__weak void CSEN_IRQHandler(void)
{
  while (true) {
  }
}

__weak void LESENSE_IRQHandler(void)
{
  while (true) {
  }
}

__weak void CRYPTO1_IRQHandler(void)
{
  while (true) {
  }
}

__weak void TRNG0_IRQHandler(void)
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
#ifdef BOOTLOADER_ENABLE
  { (pFunc) & mainStageTable },
#else
  { 0                         },
#endif
  { SVC_Handler               },
  { DebugMon_Handler          },
  { sl_app_properties         },
  { PendSV_Handler            },
  { SysTick_Handler           },
  { EMU_IRQHandler            },              /* 0 */
  { FRC_PRI_IRQHandler        },              /* 1 */
  { WDOG0_IRQHandler          },              /* 2 */
  { WDOG1_IRQHandler          },              /* 3 */
  { FRC_IRQHandler            },              /* 4 */
  { MODEM_IRQHandler          },              /* 5 */
  { RAC_SEQ_IRQHandler        },              /* 6 */
  { RAC_RSM_IRQHandler        },              /* 7 */
  { BUFC_IRQHandler           },              /* 8 */
  { LDMA_IRQHandler           },              /* 9 */
  { GPIO_EVEN_IRQHandler      },              /* 10 */
  { TIMER0_IRQHandler         },              /* 11 */
  { USART0_RX_IRQHandler      },              /* 12 */
  { USART0_TX_IRQHandler      },              /* 13 */
  { ACMP0_IRQHandler          },              /* 14 */
  { ADC0_IRQHandler           },              /* 15 */
  { IDAC0_IRQHandler          },              /* 16 */
  { I2C0_IRQHandler           },              /* 17 */
  { GPIO_ODD_IRQHandler       },              /* 18 */
  { TIMER1_IRQHandler         },              /* 19 */
  { USART1_RX_IRQHandler      },              /* 20 */
  { USART1_TX_IRQHandler      },              /* 21 */
  { LEUART0_IRQHandler        },              /* 22 */
  { PCNT0_IRQHandler          },              /* 23 */
  { CMU_IRQHandler            },              /* 24 */
  { MSC_IRQHandler            },              /* 25 */
  { CRYPTO0_IRQHandler        },              /* 26 */
  { LETIMER0_IRQHandler       },              /* 27 */
  { AGC_IRQHandler            },              /* 28 */
  { PROTIMER_IRQHandler       },              /* 29 */
  { PRORTC_IRQHandler         },              /* 30 */
  { RTCC_IRQHandler           },              /* 31 */
  { SYNTH_IRQHandler          },              /* 32 */
  { CRYOTIMER_IRQHandler      },              /* 33 */
  { RFSENSE_IRQHandler        },              /* 34 */
  { FPUEH_IRQHandler          },              /* 35 */
  { SMU_IRQHandler            },              /* 36 */
  { WTIMER0_IRQHandler        },              /* 37 */
  { USART2_RX_IRQHandler      },              /* 38 */
  { USART2_TX_IRQHandler      },              /* 39 */
  { I2C1_IRQHandler           },              /* 40 */
  { VDAC0_IRQHandler          },              /* 41 */
  { CSEN_IRQHandler           },              /* 42 */
  { LESENSE_IRQHandler        },              /* 43 */
  { CRYPTO1_IRQHandler        },              /* 44 */
  { TRNG0_IRQHandler          },              /* 45 */
  { 0                         },              /* 46 - Reserved */
};

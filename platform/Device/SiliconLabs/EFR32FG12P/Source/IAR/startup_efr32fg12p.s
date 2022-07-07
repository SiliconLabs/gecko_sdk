;/**************************************************************************//**
; * @file
; * @brief    CMSIS Core Device Startup File
; *           Silicon Labs EFR32FG12P Device Series
; ******************************************************************************
; * # License
; *
; * The licensor of this software is Silicon Laboratories Inc. Your use of this
; * software is governed by the terms of Silicon Labs Master Software License
; * Agreement (MSLA) available at
; * www.silabs.com/about-us/legal/master-software-license-agreement. This
; * software is Third Party Software licensed by Silicon Labs from a third party
; * and is governed by the sections of the MSLA applicable to Third Party
; * Software and the additional terms set forth below.
; *
; *****************************************************************************/
;/*
; * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
;
; When debugging in RAM, it can be located in RAM with at least a 128 byte
; alignment, 512 byte alignment is requied if all interrupt vectors are in use.
;
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;
        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(9)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     sl_app_properties
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts

        DCD     EMU_IRQHandler            ; 0: EMU Interrupt
        DCD     FRC_PRI_IRQHandler        ; 1: FRC_PRI Interrupt
        DCD     WDOG0_IRQHandler          ; 2: WDOG0 Interrupt
        DCD     WDOG1_IRQHandler          ; 3: WDOG1 Interrupt
        DCD     FRC_IRQHandler            ; 4: FRC Interrupt
        DCD     MODEM_IRQHandler          ; 5: MODEM Interrupt
        DCD     RAC_SEQ_IRQHandler        ; 6: RAC_SEQ Interrupt
        DCD     RAC_RSM_IRQHandler        ; 7: RAC_RSM Interrupt
        DCD     BUFC_IRQHandler           ; 8: BUFC Interrupt
        DCD     LDMA_IRQHandler           ; 9: LDMA Interrupt
        DCD     GPIO_EVEN_IRQHandler      ; 10: GPIO_EVEN Interrupt
        DCD     TIMER0_IRQHandler         ; 11: TIMER0 Interrupt
        DCD     USART0_RX_IRQHandler      ; 12: USART0_RX Interrupt
        DCD     USART0_TX_IRQHandler      ; 13: USART0_TX Interrupt
        DCD     ACMP0_IRQHandler          ; 14: ACMP0 Interrupt
        DCD     ADC0_IRQHandler           ; 15: ADC0 Interrupt
        DCD     IDAC0_IRQHandler          ; 16: IDAC0 Interrupt
        DCD     I2C0_IRQHandler           ; 17: I2C0 Interrupt
        DCD     GPIO_ODD_IRQHandler       ; 18: GPIO_ODD Interrupt
        DCD     TIMER1_IRQHandler         ; 19: TIMER1 Interrupt
        DCD     USART1_RX_IRQHandler      ; 20: USART1_RX Interrupt
        DCD     USART1_TX_IRQHandler      ; 21: USART1_TX Interrupt
        DCD     LEUART0_IRQHandler        ; 22: LEUART0 Interrupt
        DCD     PCNT0_IRQHandler          ; 23: PCNT0 Interrupt
        DCD     CMU_IRQHandler            ; 24: CMU Interrupt
        DCD     MSC_IRQHandler            ; 25: MSC Interrupt
        DCD     CRYPTO0_IRQHandler        ; 26: CRYPTO0 Interrupt
        DCD     LETIMER0_IRQHandler       ; 27: LETIMER0 Interrupt
        DCD     AGC_IRQHandler            ; 28: AGC Interrupt
        DCD     PROTIMER_IRQHandler       ; 29: PROTIMER Interrupt
        DCD     RTCC_IRQHandler           ; 30: RTCC Interrupt
        DCD     SYNTH_IRQHandler          ; 31: SYNTH Interrupt
        DCD     CRYOTIMER_IRQHandler      ; 32: CRYOTIMER Interrupt
        DCD     RFSENSE_IRQHandler        ; 33: RFSENSE Interrupt
        DCD     FPUEH_IRQHandler          ; 34: FPUEH Interrupt
        DCD     SMU_IRQHandler            ; 35: SMU Interrupt
        DCD     WTIMER0_IRQHandler        ; 36: WTIMER0 Interrupt
        DCD     WTIMER1_IRQHandler        ; 37: WTIMER1 Interrupt
        DCD     PCNT1_IRQHandler          ; 38: PCNT1 Interrupt
        DCD     PCNT2_IRQHandler          ; 39: PCNT2 Interrupt
        DCD     USART2_RX_IRQHandler      ; 40: USART2_RX Interrupt
        DCD     USART2_TX_IRQHandler      ; 41: USART2_TX Interrupt
        DCD     I2C1_IRQHandler           ; 42: I2C1 Interrupt
        DCD     USART3_RX_IRQHandler      ; 43: USART3_RX Interrupt
        DCD     USART3_TX_IRQHandler      ; 44: USART3_TX Interrupt
        DCD     VDAC0_IRQHandler          ; 45: VDAC0 Interrupt
        DCD     CSEN_IRQHandler           ; 46: CSEN Interrupt
        DCD     LESENSE_IRQHandler        ; 47: LESENSE Interrupt
        DCD     CRYPTO1_IRQHandler        ; 48: CRYPTO1 Interrupt
        DCD     TRNG0_IRQHandler          ; 49: TRNG0 Interrupt
        DCD     0                         ; 50: Reserved Interrupt

__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        PUBWEAK sl_app_properties
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
sl_app_properties     ; Provide a dummy value for the sl_app_properties symbol.
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        ; Device specific interrupt handlers

        PUBWEAK EMU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EMU_IRQHandler
        B EMU_IRQHandler

        PUBWEAK FRC_PRI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FRC_PRI_IRQHandler
        B FRC_PRI_IRQHandler

        PUBWEAK WDOG0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDOG0_IRQHandler
        B WDOG0_IRQHandler

        PUBWEAK WDOG1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDOG1_IRQHandler
        B WDOG1_IRQHandler

        PUBWEAK FRC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FRC_IRQHandler
        B FRC_IRQHandler

        PUBWEAK MODEM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MODEM_IRQHandler
        B MODEM_IRQHandler

        PUBWEAK RAC_SEQ_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RAC_SEQ_IRQHandler
        B RAC_SEQ_IRQHandler

        PUBWEAK RAC_RSM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RAC_RSM_IRQHandler
        B RAC_RSM_IRQHandler

        PUBWEAK BUFC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BUFC_IRQHandler
        B BUFC_IRQHandler

        PUBWEAK LDMA_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LDMA_IRQHandler
        B LDMA_IRQHandler

        PUBWEAK GPIO_EVEN_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_EVEN_IRQHandler
        B GPIO_EVEN_IRQHandler

        PUBWEAK TIMER0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER0_IRQHandler
        B TIMER0_IRQHandler

        PUBWEAK USART0_RX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART0_RX_IRQHandler
        B USART0_RX_IRQHandler

        PUBWEAK USART0_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART0_TX_IRQHandler
        B USART0_TX_IRQHandler

        PUBWEAK ACMP0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ACMP0_IRQHandler
        B ACMP0_IRQHandler

        PUBWEAK ADC0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC0_IRQHandler
        B ADC0_IRQHandler

        PUBWEAK IDAC0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
IDAC0_IRQHandler
        B IDAC0_IRQHandler

        PUBWEAK I2C0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C0_IRQHandler
        B I2C0_IRQHandler

        PUBWEAK GPIO_ODD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_ODD_IRQHandler
        B GPIO_ODD_IRQHandler

        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler

        PUBWEAK USART1_RX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_RX_IRQHandler
        B USART1_RX_IRQHandler

        PUBWEAK USART1_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_TX_IRQHandler
        B USART1_TX_IRQHandler

        PUBWEAK LEUART0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LEUART0_IRQHandler
        B LEUART0_IRQHandler

        PUBWEAK PCNT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PCNT0_IRQHandler
        B PCNT0_IRQHandler

        PUBWEAK CMU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CMU_IRQHandler
        B CMU_IRQHandler

        PUBWEAK MSC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MSC_IRQHandler
        B MSC_IRQHandler

        PUBWEAK CRYPTO0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CRYPTO0_IRQHandler
        B CRYPTO0_IRQHandler

        PUBWEAK LETIMER0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LETIMER0_IRQHandler
        B LETIMER0_IRQHandler

        PUBWEAK AGC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
AGC_IRQHandler
        B AGC_IRQHandler

        PUBWEAK PROTIMER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PROTIMER_IRQHandler
        B PROTIMER_IRQHandler

        PUBWEAK RTCC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTCC_IRQHandler
        B RTCC_IRQHandler

        PUBWEAK SYNTH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SYNTH_IRQHandler
        B SYNTH_IRQHandler

        PUBWEAK CRYOTIMER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CRYOTIMER_IRQHandler
        B CRYOTIMER_IRQHandler

        PUBWEAK RFSENSE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RFSENSE_IRQHandler
        B RFSENSE_IRQHandler

        PUBWEAK FPUEH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPUEH_IRQHandler
        B FPUEH_IRQHandler

        PUBWEAK SMU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SMU_IRQHandler
        B SMU_IRQHandler

        PUBWEAK WTIMER0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WTIMER0_IRQHandler
        B WTIMER0_IRQHandler

        PUBWEAK WTIMER1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WTIMER1_IRQHandler
        B WTIMER1_IRQHandler

        PUBWEAK PCNT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PCNT1_IRQHandler
        B PCNT1_IRQHandler

        PUBWEAK PCNT2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PCNT2_IRQHandler
        B PCNT2_IRQHandler

        PUBWEAK USART2_RX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_RX_IRQHandler
        B USART2_RX_IRQHandler

        PUBWEAK USART2_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_TX_IRQHandler
        B USART2_TX_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK USART3_RX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_RX_IRQHandler
        B USART3_RX_IRQHandler

        PUBWEAK USART3_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_TX_IRQHandler
        B USART3_TX_IRQHandler

        PUBWEAK VDAC0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
VDAC0_IRQHandler
        B VDAC0_IRQHandler

        PUBWEAK CSEN_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CSEN_IRQHandler
        B CSEN_IRQHandler

        PUBWEAK LESENSE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LESENSE_IRQHandler
        B LESENSE_IRQHandler

        PUBWEAK CRYPTO1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CRYPTO1_IRQHandler
        B CRYPTO1_IRQHandler

        PUBWEAK TRNG0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TRNG0_IRQHandler
        B TRNG0_IRQHandler


        END

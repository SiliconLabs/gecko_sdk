;/**************************************************************************//**
; * @file
; * @brief    CMSIS Core Device Startup File for
; *           Silicon Labs WGM160 Device Series
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

;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
                IF :DEF: __STACK_SIZE
Stack_Size      EQU     __STACK_SIZE
                ELSE
Stack_Size      EQU     0x00000400
                ENDIF

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
                IF :DEF: __HEAP_SIZE
Heap_Size       EQU     __HEAP_SIZE
                ELSE
Heap_Size       EQU     0x00000C00
                ENDIF

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY, ALIGN=9
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     sl_app_properties         ; Application properties
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts

                DCD     EMU_IRQHandler            ; 0: EMU Interrupt
                DCD     WDOG0_IRQHandler          ; 1: WDOG0 Interrupt
                DCD     LDMA_IRQHandler           ; 2: LDMA Interrupt
                DCD     GPIO_EVEN_IRQHandler      ; 3: GPIO_EVEN Interrupt
                DCD     SMU_IRQHandler            ; 4: SMU Interrupt
                DCD     TIMER0_IRQHandler         ; 5: TIMER0 Interrupt
                DCD     USART0_RX_IRQHandler      ; 6: USART0_RX Interrupt
                DCD     USART0_TX_IRQHandler      ; 7: USART0_TX Interrupt
                DCD     ACMP0_IRQHandler          ; 8: ACMP0 Interrupt
                DCD     ADC0_IRQHandler           ; 9: ADC0 Interrupt
                DCD     IDAC0_IRQHandler          ; 10: IDAC0 Interrupt
                DCD     I2C0_IRQHandler           ; 11: I2C0 Interrupt
                DCD     I2C1_IRQHandler           ; 12: I2C1 Interrupt
                DCD     GPIO_ODD_IRQHandler       ; 13: GPIO_ODD Interrupt
                DCD     TIMER1_IRQHandler         ; 14: TIMER1 Interrupt
                DCD     TIMER2_IRQHandler         ; 15: TIMER2 Interrupt
                DCD     TIMER3_IRQHandler         ; 16: TIMER3 Interrupt
                DCD     USART1_RX_IRQHandler      ; 17: USART1_RX Interrupt
                DCD     USART1_TX_IRQHandler      ; 18: USART1_TX Interrupt
                DCD     USART2_RX_IRQHandler      ; 19: USART2_RX Interrupt
                DCD     USART2_TX_IRQHandler      ; 20: USART2_TX Interrupt
                DCD     UART0_RX_IRQHandler       ; 21: UART0_RX Interrupt
                DCD     UART0_TX_IRQHandler       ; 22: UART0_TX Interrupt
                DCD     UART1_RX_IRQHandler       ; 23: UART1_RX Interrupt
                DCD     UART1_TX_IRQHandler       ; 24: UART1_TX Interrupt
                DCD     LEUART0_IRQHandler        ; 25: LEUART0 Interrupt
                DCD     LEUART1_IRQHandler        ; 26: LEUART1 Interrupt
                DCD     LETIMER0_IRQHandler       ; 27: LETIMER0 Interrupt
                DCD     PCNT0_IRQHandler          ; 28: PCNT0 Interrupt
                DCD     PCNT1_IRQHandler          ; 29: PCNT1 Interrupt
                DCD     PCNT2_IRQHandler          ; 30: PCNT2 Interrupt
                DCD     RTCC_IRQHandler           ; 31: RTCC Interrupt
                DCD     CMU_IRQHandler            ; 32: CMU Interrupt
                DCD     MSC_IRQHandler            ; 33: MSC Interrupt
                DCD     CRYPTO0_IRQHandler        ; 34: CRYPTO0 Interrupt
                DCD     CRYOTIMER_IRQHandler      ; 35: CRYOTIMER Interrupt
                DCD     FPUEH_IRQHandler          ; 36: FPUEH Interrupt
                DCD     USART3_RX_IRQHandler      ; 37: USART3_RX Interrupt
                DCD     USART3_TX_IRQHandler      ; 38: USART3_TX Interrupt
                DCD     USART4_RX_IRQHandler      ; 39: USART4_RX Interrupt
                DCD     USART4_TX_IRQHandler      ; 40: USART4_TX Interrupt
                DCD     WTIMER0_IRQHandler        ; 41: WTIMER0 Interrupt
                DCD     WTIMER1_IRQHandler        ; 42: WTIMER1 Interrupt
                DCD     WTIMER2_IRQHandler        ; 43: WTIMER2 Interrupt
                DCD     WTIMER3_IRQHandler        ; 44: WTIMER3 Interrupt
                DCD     I2C2_IRQHandler           ; 45: I2C2 Interrupt
                DCD     VDAC0_IRQHandler          ; 46: VDAC0 Interrupt
                DCD     TIMER4_IRQHandler         ; 47: TIMER4 Interrupt
                DCD     TIMER5_IRQHandler         ; 48: TIMER5 Interrupt
                DCD     TIMER6_IRQHandler         ; 49: TIMER6 Interrupt
                DCD     USART5_RX_IRQHandler      ; 50: USART5_RX Interrupt
                DCD     USART5_TX_IRQHandler      ; 51: USART5_TX Interrupt
                DCD     CSEN_IRQHandler           ; 52: CSEN Interrupt
                DCD     LESENSE_IRQHandler        ; 53: LESENSE Interrupt
                DCD     EBI_IRQHandler            ; 54: EBI Interrupt
                DCD     ACMP2_IRQHandler          ; 55: ACMP2 Interrupt
                DCD     ADC1_IRQHandler           ; 56: ADC1 Interrupt
                DCD     LCD_IRQHandler            ; 57: LCD Interrupt
                DCD     SDIO_IRQHandler           ; 58: SDIO Interrupt
                DCD     ETH_IRQHandler            ; 59: ETH Interrupt
                DCD     CAN0_IRQHandler           ; 60: CAN0 Interrupt
                DCD     CAN1_IRQHandler           ; 61: CAN1 Interrupt
                DCD     USB_IRQHandler            ; 62: USB Interrupt
                DCD     RTC_IRQHandler            ; 63: RTC Interrupt
                DCD     WDOG1_IRQHandler          ; 64: WDOG1 Interrupt
                DCD     LETIMER1_IRQHandler       ; 65: LETIMER1 Interrupt
                DCD     TRNG0_IRQHandler          ; 66: TRNG0 Interrupt
                DCD     QSPI0_IRQHandler          ; 67: QSPI0 Interrupt
                DCD     YKGW_FF_IRQHandler        ; 68: YKGW_FF Interrupt
                DCD     YKGW_SMART_IRQHandler     ; 69: YKGW_SMART Interrupt

__Vectors_End
__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                EXPORT  sl_app_properties         [WEAK]
sl_app_properties     ; Provide a dummy value for the sl_app_properties symbol.
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  EMU_IRQHandler            [WEAK]
                EXPORT  WDOG0_IRQHandler          [WEAK]
                EXPORT  LDMA_IRQHandler           [WEAK]
                EXPORT  GPIO_EVEN_IRQHandler      [WEAK]
                EXPORT  SMU_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  USART0_RX_IRQHandler      [WEAK]
                EXPORT  USART0_TX_IRQHandler      [WEAK]
                EXPORT  ACMP0_IRQHandler          [WEAK]
                EXPORT  ADC0_IRQHandler           [WEAK]
                EXPORT  IDAC0_IRQHandler          [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  GPIO_ODD_IRQHandler       [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  USART1_RX_IRQHandler      [WEAK]
                EXPORT  USART1_TX_IRQHandler      [WEAK]
                EXPORT  USART2_RX_IRQHandler      [WEAK]
                EXPORT  USART2_TX_IRQHandler      [WEAK]
                EXPORT  UART0_RX_IRQHandler       [WEAK]
                EXPORT  UART0_TX_IRQHandler       [WEAK]
                EXPORT  UART1_RX_IRQHandler       [WEAK]
                EXPORT  UART1_TX_IRQHandler       [WEAK]
                EXPORT  LEUART0_IRQHandler        [WEAK]
                EXPORT  LEUART1_IRQHandler        [WEAK]
                EXPORT  LETIMER0_IRQHandler       [WEAK]
                EXPORT  PCNT0_IRQHandler          [WEAK]
                EXPORT  PCNT1_IRQHandler          [WEAK]
                EXPORT  PCNT2_IRQHandler          [WEAK]
                EXPORT  RTCC_IRQHandler           [WEAK]
                EXPORT  CMU_IRQHandler            [WEAK]
                EXPORT  MSC_IRQHandler            [WEAK]
                EXPORT  CRYPTO0_IRQHandler        [WEAK]
                EXPORT  CRYOTIMER_IRQHandler      [WEAK]
                EXPORT  FPUEH_IRQHandler          [WEAK]
                EXPORT  USART3_RX_IRQHandler      [WEAK]
                EXPORT  USART3_TX_IRQHandler      [WEAK]
                EXPORT  USART4_RX_IRQHandler      [WEAK]
                EXPORT  USART4_TX_IRQHandler      [WEAK]
                EXPORT  WTIMER0_IRQHandler        [WEAK]
                EXPORT  WTIMER1_IRQHandler        [WEAK]
                EXPORT  WTIMER2_IRQHandler        [WEAK]
                EXPORT  WTIMER3_IRQHandler        [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  VDAC0_IRQHandler          [WEAK]
                EXPORT  TIMER4_IRQHandler         [WEAK]
                EXPORT  TIMER5_IRQHandler         [WEAK]
                EXPORT  TIMER6_IRQHandler         [WEAK]
                EXPORT  USART5_RX_IRQHandler      [WEAK]
                EXPORT  USART5_TX_IRQHandler      [WEAK]
                EXPORT  CSEN_IRQHandler           [WEAK]
                EXPORT  LESENSE_IRQHandler        [WEAK]
                EXPORT  EBI_IRQHandler            [WEAK]
                EXPORT  ACMP2_IRQHandler          [WEAK]
                EXPORT  ADC1_IRQHandler           [WEAK]
                EXPORT  LCD_IRQHandler            [WEAK]
                EXPORT  SDIO_IRQHandler           [WEAK]
                EXPORT  ETH_IRQHandler            [WEAK]
                EXPORT  CAN0_IRQHandler           [WEAK]
                EXPORT  CAN1_IRQHandler           [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  WDOG1_IRQHandler          [WEAK]
                EXPORT  LETIMER1_IRQHandler       [WEAK]
                EXPORT  TRNG0_IRQHandler          [WEAK]
                EXPORT  QSPI0_IRQHandler          [WEAK]
                EXPORT  YKGW_FF_IRQHandler        [WEAK]
                EXPORT  YKGW_SMART_IRQHandler     [WEAK]


EMU_IRQHandler
WDOG0_IRQHandler
LDMA_IRQHandler
GPIO_EVEN_IRQHandler
SMU_IRQHandler
TIMER0_IRQHandler
USART0_RX_IRQHandler
USART0_TX_IRQHandler
ACMP0_IRQHandler
ADC0_IRQHandler
IDAC0_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
GPIO_ODD_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
USART1_RX_IRQHandler
USART1_TX_IRQHandler
USART2_RX_IRQHandler
USART2_TX_IRQHandler
UART0_RX_IRQHandler
UART0_TX_IRQHandler
UART1_RX_IRQHandler
UART1_TX_IRQHandler
LEUART0_IRQHandler
LEUART1_IRQHandler
LETIMER0_IRQHandler
PCNT0_IRQHandler
PCNT1_IRQHandler
PCNT2_IRQHandler
RTCC_IRQHandler
CMU_IRQHandler
MSC_IRQHandler
CRYPTO0_IRQHandler
CRYOTIMER_IRQHandler
FPUEH_IRQHandler
USART3_RX_IRQHandler
USART3_TX_IRQHandler
USART4_RX_IRQHandler
USART4_TX_IRQHandler
WTIMER0_IRQHandler
WTIMER1_IRQHandler
WTIMER2_IRQHandler
WTIMER3_IRQHandler
I2C2_IRQHandler
VDAC0_IRQHandler
TIMER4_IRQHandler
TIMER5_IRQHandler
TIMER6_IRQHandler
USART5_RX_IRQHandler
USART5_TX_IRQHandler
CSEN_IRQHandler
LESENSE_IRQHandler
EBI_IRQHandler
ACMP2_IRQHandler
ADC1_IRQHandler
LCD_IRQHandler
SDIO_IRQHandler
ETH_IRQHandler
CAN0_IRQHandler
CAN1_IRQHandler
USB_IRQHandler
RTC_IRQHandler
WDOG1_IRQHandler
LETIMER1_IRQHandler
TRNG0_IRQHandler
QSPI0_IRQHandler
YKGW_FF_IRQHandler
YKGW_SMART_IRQHandler
                B       .
                ENDP

                ALIGN

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF

                END

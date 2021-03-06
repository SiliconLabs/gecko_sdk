;/**************************************************************************//**
; * @file
; * @brief    CMSIS Core Device Startup File
; *           Silicon Labs EFM32HG Device Series
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
; alignment, 256 byte alignment is requied if all interrupt vectors are in use.
;
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;


                MODULE   ?cstartup

                ;; Forward declaration of sections.
                SECTION  CSTACK:DATA:NOROOT(3)


                SECTION  .intvec:CODE:NOROOT(8)
                EXTERN   __iar_program_start
                EXTERN   SystemInit
                PUBLIC   __vector_table
                PUBLIC   __vector_table_0x1c
                PUBLIC   __Vectors
                PUBLIC   __Vectors_End
                PUBLIC   __Vectors_Size

                DATA

__vector_table
                DCD      sfe(CSTACK)                         ; Top of Stack
                DCD      Reset_Handler                       ; Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      0                                   ; Reserved
                DCD      0                                   ; Reserved
                DCD      0                                   ; Reserved
__vector_table_0x1c
                DCD      0                                   ; Reserved
                DCD      0                                   ; Reserved
                DCD      0                                   ; Reserved
                DCD      0                                   ; Reserved
                DCD      SVC_Handler                         ; -5 SVCall Handler
                DCD      0                                   ; Reserved
                DCD      sl_app_properties                   ; -3 Application properties
                DCD      PendSV_Handler                      ; -2 PendSV Handler
                DCD      SysTick_Handler                     ; -1 SysTick Handler

        ; External Interrupts

                DCD      DMA_IRQHandler                      ; 0: DMA Interrupt
                DCD      GPIO_EVEN_IRQHandler                ; 1: GPIO_EVEN Interrupt
                DCD      TIMER0_IRQHandler                   ; 2: TIMER0 Interrupt
                DCD      ACMP0_IRQHandler                    ; 3: ACMP0 Interrupt
                DCD      ADC0_IRQHandler                     ; 4: ADC0 Interrupt
                DCD      I2C0_IRQHandler                     ; 5: I2C0 Interrupt
                DCD      GPIO_ODD_IRQHandler                 ; 6: GPIO_ODD Interrupt
                DCD      TIMER1_IRQHandler                   ; 7: TIMER1 Interrupt
                DCD      USART1_RX_IRQHandler                ; 8: USART1_RX Interrupt
                DCD      USART1_TX_IRQHandler                ; 9: USART1_TX Interrupt
                DCD      LEUART0_IRQHandler                  ; 10: LEUART0 Interrupt
                DCD      PCNT0_IRQHandler                    ; 11: PCNT0 Interrupt
                DCD      RTC_IRQHandler                      ; 12: RTC Interrupt
                DCD      CMU_IRQHandler                      ; 13: CMU Interrupt
                DCD      VCMP_IRQHandler                     ; 14: VCMP Interrupt
                DCD      MSC_IRQHandler                      ; 15: MSC Interrupt
                DCD      AES_IRQHandler                      ; 16: AES Interrupt
                DCD      USART0_RX_IRQHandler                ; 17: USART0_RX Interrupt
                DCD      USART0_TX_IRQHandler                ; 18: USART0_TX Interrupt
                DCD      USB_IRQHandler                      ; 19: USB Interrupt
                DCD      TIMER2_IRQHandler                   ; 20: TIMER2 Interrupt


                DS32    (11)                 ; Remaining Interrupts are left out

__Vectors_End

__Vectors       EQU      __vector_table
__Vectors_Size  EQU      __Vectors_End - __Vectors

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
                THUMB

; Reset Handler

                PUBWEAK  Reset_Handler
                SECTION  .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__iar_program_start
                BX       R0


                PUBWEAK NMI_Handler
                PUBWEAK sl_app_properties
                PUBWEAK HardFault_Handler
                PUBWEAK SVC_Handler
                PUBWEAK PendSV_Handler
                PUBWEAK SysTick_Handler

                PUBWEAK DMA_IRQHandler
                PUBWEAK GPIO_EVEN_IRQHandler
                PUBWEAK TIMER0_IRQHandler
                PUBWEAK ACMP0_IRQHandler
                PUBWEAK ADC0_IRQHandler
                PUBWEAK I2C0_IRQHandler
                PUBWEAK GPIO_ODD_IRQHandler
                PUBWEAK TIMER1_IRQHandler
                PUBWEAK USART1_RX_IRQHandler
                PUBWEAK USART1_TX_IRQHandler
                PUBWEAK LEUART0_IRQHandler
                PUBWEAK PCNT0_IRQHandler
                PUBWEAK RTC_IRQHandler
                PUBWEAK CMU_IRQHandler
                PUBWEAK VCMP_IRQHandler
                PUBWEAK MSC_IRQHandler
                PUBWEAK AES_IRQHandler
                PUBWEAK USART0_RX_IRQHandler
                PUBWEAK USART0_TX_IRQHandler
                PUBWEAK USB_IRQHandler
                PUBWEAK TIMER2_IRQHandler

                SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
sl_app_properties     ; Provide a dummy value for the sl_app_properties symbol.
HardFault_Handler
SVC_Handler
PendSV_Handler
SysTick_Handler

DMA_IRQHandler
GPIO_EVEN_IRQHandler
TIMER0_IRQHandler
ACMP0_IRQHandler
ADC0_IRQHandler
I2C0_IRQHandler
GPIO_ODD_IRQHandler
TIMER1_IRQHandler
USART1_RX_IRQHandler
USART1_TX_IRQHandler
LEUART0_IRQHandler
PCNT0_IRQHandler
RTC_IRQHandler
CMU_IRQHandler
VCMP_IRQHandler
MSC_IRQHandler
AES_IRQHandler
USART0_RX_IRQHandler
USART0_TX_IRQHandler
USB_IRQHandler
TIMER2_IRQHandler

Default_Handler
                B        .

                END

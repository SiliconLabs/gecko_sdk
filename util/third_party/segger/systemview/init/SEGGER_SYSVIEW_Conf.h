/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 1995 - 2019 SEGGER Microcontroller GmbH             *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView * Real-time application analysis           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the SystemView and RTT protocol, and J-Link.       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* condition is met:                                                  *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this condition and the following disclaimer.             *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView version: 3.10                                    *
*                                                                    *
**********************************************************************
-------------------------- END-OF-HEADER -----------------------------

File    : SEGGER_SYSVIEW_Conf.h
Purpose : SEGGER SystemView configuration.
Revision: $Rev: 17066 $
*/

#ifndef SEGGER_SYSVIEW_CONF_H
#define SEGGER_SYSVIEW_CONF_H

#include "sl_systemview_config.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if (SEGGER_SYSVIEW_TIMESTAMP_SOURCE == SEGGER_SYSVIEW_TIMESTAMP_SOURCE_SLEEPTIMER)
#include "sl_sleeptimer.h"
#endif

#if defined(SL_CATALOG_SYSTEMVIEW_UART_RECORDER_PRESENT)
#include "sli_uart_recorder.h"
#endif

#include "em_core.h"

/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/

#if (defined(SL_CATALOG_SYSTEMVIEW_UART_RECORDER_PRESENT) && defined(SL_CATALOG_KERNEL_PRESENT))
#define SEGGER_SYSVIEW_ON_EVENT_RECORDED(NumBytes)   sli_uart_recorder_notify_event_recorded()
#else
#define SEGGER_SYSVIEW_ON_EVENT_RECORDED(NumBytes)
#endif

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
/*********************************************************************
*
*       SystemView buffer configuration
*/
#ifndef   SEGGER_SYSVIEW_RTT_BUFFER_SIZE
  #define SEGGER_SYSVIEW_RTT_BUFFER_SIZE        1024                            // Number of bytes that SystemView uses for the buffer.
#endif

#ifndef   SEGGER_SYSVIEW_RTT_CHANNEL
  #define SEGGER_SYSVIEW_RTT_CHANNEL            1                               // The RTT channel that SystemView will use. 0: Auto selection
#endif

#ifndef   SEGGER_SYSVIEW_USE_STATIC_BUFFER
  #define SEGGER_SYSVIEW_USE_STATIC_BUFFER      1                               // Use a static buffer to generate events instead of a buffer on the stack
#endif

#ifndef   SEGGER_SYSVIEW_POST_MORTEM_MODE
  #define SEGGER_SYSVIEW_POST_MORTEM_MODE       0                               // 1: Enable post mortem analysis mode
#endif

#ifndef   SEGGER_SYSVIEW_CAN_RESTART
  #define SEGGER_SYSVIEW_CAN_RESTART            1                               // 1: Send the SystemView start sequence on every start command, not just on the first. Enables restart when SystemView Application disconnected unexpectedly.
#endif

/*********************************************************************
*
*       SystemView Id configuration
*/
#ifndef   SEGGER_SYSVIEW_ID_BASE
  #define SEGGER_SYSVIEW_ID_BASE                0x10000000                      // Default value for the lowest Id reported by the application. Can be overridden by the application via SEGGER_SYSVIEW_SetRAMBase(). (i.e. 0x20000000 when all Ids are an address in this RAM)
#endif

#ifndef   SEGGER_SYSVIEW_ID_SHIFT
  #define SEGGER_SYSVIEW_ID_SHIFT               2                               // Number of bits to shift the Id to save bandwidth. (i.e. 2 when Ids are 4 byte aligned)
#endif
/*********************************************************************
*
*       SystemView interrupt configuration
*/

#define SEGGER_SYSVIEW_GET_INTERRUPT_ID()  (__get_IPSR())

/*********************************************************************
*
*       SystemView timestamp configuration
*/
#if (SEGGER_SYSVIEW_TIMESTAMP_SOURCE == SEGGER_SYSVIEW_TIMESTAMP_SOURCE_DWT)
#define SEGGER_SYSVIEW_GET_TIMESTAMP()      DWT->CYCCNT
#define SYSVIEW_TIMESTAMP_FREQ              (SystemCoreClock)
#elif (SEGGER_SYSVIEW_TIMESTAMP_SOURCE == SEGGER_SYSVIEW_TIMESTAMP_SOURCE_SLEEPTIMER)
#define SEGGER_SYSVIEW_GET_TIMESTAMP()      sl_sleeptimer_get_tick_count()
#define SYSVIEW_TIMESTAMP_FREQ              sl_sleeptimer_get_timer_frequency()
#else
#error "SEGGER_SYSVIEW_TIMESTAMP_SOURCE must be set to SEGGER_SYSVIEW_TIMESTAMP_SOURCE_DWT or SEGGER_SYSVIEW_TIMESTAMP_SOURCE_SLEEPTIMER"
#endif
#define SEGGER_SYSVIEW_TIMESTAMP_BITS       32        // Define number of valid bits low-order delivered by clock source

#endif  // SEGGER_SYSVIEW_CONF_H

/*************************** End of file ****************************/

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
*       SystemView version: 3.20                                    *
*                                                                    *
**********************************************************************
-------------------------- END-OF-HEADER -----------------------------

File    : SEGGER_SYSVIEW_Init.c
Purpose : Sample setup configuration of SystemView without an OS.
Revision: $Rev: 9599 $
*/

#include <stddef.h>
#include "em_core.h"
#include "sl_sysview_custom_api.h"
#include "SEGGER_SYSVIEW.h"
#include "SEGGER_SYSVIEW_Conf.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if (SEGGER_SYSVIEW_TIMESTAMP_SOURCE == SEGGER_SYSVIEW_TIMESTAMP_SOURCE_SLEEPTIMER)
#include "sl_status.h"
#include "sl_sleeptimer.h"
#endif

#if defined(SL_CATALOG_SYSTEMVIEW_UART_RECORDER_PRESENT)
#include "sli_uart_recorder.h"
#endif

// System core clock frequency.
extern uint32_t SystemCoreClock;

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
// The application name to be displayed in SystemViewer
#ifndef SYSVIEW_APP_NAME
#define SYSVIEW_APP_NAME        "Silicon Labs Gecko SDK Application"
#endif

// The target device name
#ifndef SYSVIEW_DEVICE_NAME
#if (__CORTEX_M == 0U)
#define SYSVIEW_DEVICE_NAME     "Cortex-M0+"
#elif (__CORTEX_M == 3U)
#define SYSVIEW_DEVICE_NAME     "Cortex-M3"
#elif (__CORTEX_M == 4U)
#define SYSVIEW_DEVICE_NAME     "Cortex-M4"
#elif (__CORTEX_M == 33U)
#define SYSVIEW_DEVICE_NAME     "Cortex-M33"
#else
#define SYSVIEW_DEVICE_NAME     "Cortex-M"
#endif
#endif

// System Frequency. SystemcoreClock is used in most CMSIS compatible projects.
#define SYSVIEW_CPU_FREQ        (SystemCoreClock)

// The lowest RAM address used for IDs (pointers)
#define SYSVIEW_RAM_BASE        (0x10000000)

#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)
#include "os.h"
#define SYSVIEW_KERNEL_MICRIUM_OS
extern SEGGER_SYSVIEW_OS_API SYSVIEW_X_OS_TraceAPI;
#elif defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
#define SYSVIEW_KERNEL_FREERTOS
extern SEGGER_SYSVIEW_OS_API SYSVIEW_X_OS_TraceAPI;
#endif

static SEGGER_SYSVIEW_MODULE gecko_sdk_module;

/********************************************************************* 
*
*       _cbSendSystemDesc()
*
*  Function description
*    Sends SystemView description strings.
*/
static void _cbSendSystemDesc(void) {
  SEGGER_SYSVIEW_SendSysDesc("N="SYSVIEW_APP_NAME",D="SYSVIEW_DEVICE_NAME);
  SEGGER_SYSVIEW_SendSysDesc("I#15=SysTick");

#if defined(SYSVIEW_KERNEL_MICRIUM_OS)
  SEGGER_SYSVIEW_SendSysDesc("O=Micrium OS Kernel");
#elif defined(SYSVIEW_KERNEL_FREERTOS)
  SEGGER_SYSVIEW_SendSysDesc("O=FreeRTOS");
#endif
}

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

void SEGGER_SYSVIEW_Conf(void) {
  SEGGER_SYSVIEW_OS_API *os_api = NULL;

#if (SEGGER_SYSVIEW_TIMESTAMP_SOURCE == SEGGER_SYSVIEW_TIMESTAMP_SOURCE_SLEEPTIMER)
  // Initialize Sleeptimer module in case not already done.
  sl_status_t status = SL_STATUS_OK;
  status = sl_sleeptimer_init();
  if (status != SL_STATUS_OK) {
    return;
  }
#endif

#if (SEGGER_SYSVIEW_TIMESTAMP_SOURCE == SEGGER_SYSVIEW_TIMESTAMP_SOURCE_DWT) && !defined(SL_COMPONENT_CATALOG_KERNEL_PRESENT)
  // Enable DWT and ensure it is functionnal even when no debugger attached.
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  ITM->LAR          = 0xc5acce55;
  DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;
#endif

  // Register Gecko SDK module
  gecko_sdk_module.EventOffset = 0;
  gecko_sdk_module.NumEvents = 28671;
  gecko_sdk_module.pfSendModuleDesc = 0;
  gecko_sdk_module.pNext = 0;
  gecko_sdk_module.sModule = "M=GeckoSDK";

#if defined(SYSVIEW_KERNEL_MICRIUM_OS) || defined(SYSVIEW_KERNEL_FREERTOS)
  os_api = &SYSVIEW_X_OS_TraceAPI;
#endif

  SEGGER_SYSVIEW_Init(SYSVIEW_TIMESTAMP_FREQ, SYSVIEW_CPU_FREQ,
                      os_api, _cbSendSystemDesc);
  SEGGER_SYSVIEW_SetRAMBase(SYSVIEW_RAM_BASE);
  SEGGER_SYSVIEW_RegisterModule(&gecko_sdk_module);
}

int sl_systemview_GetGSDKEventOffset(void) {
  return gecko_sdk_module.EventOffset;
}

/*************************** End of file ****************************/

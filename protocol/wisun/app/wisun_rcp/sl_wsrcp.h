/***************************************************************************//**
 * Copyright 2021 Silicon Laboratories Inc. www.silabs.com
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available here[1]. This software is distributed to you in
 * Source Code format and is governed by the sections of the MSLA applicable to
 * Source Code.
 *
 * [1] www.silabs.com/about-us/legal/master-software-license-agreement
 *
 ******************************************************************************/
#ifndef SL_WSRCP_H
#define SL_WSRCP_H

#include <stdint.h>
#include <stdbool.h>
#include <cmsis_os2.h>
#include <em_device.h>
#include <em_ldma.h>
#include <dmadrv.h>
#include "sl_component_catalog.h"
#include "sli_wisun_timer_service.h"

#if defined SL_CATALOG_CPC_SECONDARY_PRESENT
#include <sl_cpc.h>
#elif defined SL_CATALOG_IOSTREAM_UART_COMMON_PRESENT
#include "sl_wsrcp_uart_plt.h"
#else
#include "sl_wsrcp_uart.h"
#endif

struct ws_mac_ctxt;

enum {
    RX_UART = 1 << 0,
    TIMER_EXPIRED = 1 << 1,
};

struct sl_wsrcp_app {
    osEventFlagsId_t main_events;
    osThreadId_t main_task;

#if defined SL_CATALOG_CPC_SECONDARY_PRESENT
    sl_cpc_endpoint_handle_t cpc_ep;
#elif defined SL_CATALOG_IOSTREAM_UART_COMMON_PRESENT
    struct sl_wsrcp_uart_plt uart_plt;
#else
    struct sl_wsrcp_uart uart;
#endif
    struct sl_wsrcp_mac *rcp_mac;
    sli_wisun_timer_context_t rcp_timer_context;
};

// This global variable is necessary for IRQ handling. Beside this use case,
// please never use it.
extern struct sl_wsrcp_app g_rcp_ctxt;

void wisun_rcp_init(void);

#endif

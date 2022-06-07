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

#include <cmsis_os2.h>
#include <sl_iostream.h>
#include <sl_iostream_rtt.h>
#include <sl_common.h>
#include <SEGGER_RTT.h>

#include "sl_micrium_debug.h"
#include "sl_wsrcp.h"
#include "sl_wsrcp_mac.h"
#include "sl_wsrcp_uart.h"
#include "sl_wsrcp_log.h"

// See warning in sl_wsrcp.h
struct sl_wsrcp_app g_rcp_ctxt = { 0 };

static int wisun_rcp_uart_tx(void *cb_data, const void *buf, int buf_len)
{
    struct sl_wsrcp_app *rcp_app = &g_rcp_ctxt;
    int ret;

    osMutexAcquire(rcp_app->uart_tx_lock, osWaitForever);
    ret = uart_tx(cb_data, buf, buf_len);
    osMutexRelease(rcp_app->uart_tx_lock);
    return ret;
}

static int wisun_rcp_uart_rx(void *cb_data, void *buf, int buf_len)
{
    return uart_rx(cb_data, buf, buf_len);
}

void wisun_rcp_main(void *arg)
{
    struct sl_wsrcp_app *rcp_app = arg;
    uint32_t flags;

    rcp_app->rcp_mac = wsmac_register(wisun_rcp_uart_tx, wisun_rcp_uart_rx, rcp_app);
    for (;;) {
        flags = osEventFlagsWait(rcp_app->main_events, RX_UART, osFlagsWaitAny, osWaitForever);
        if (flags & 0x10000000)
            WARN("Error: %08" PRIu32, flags);
        if (flags & RX_UART) {
            while (wsmac_rx_host(rcp_app->rcp_mac))
                /* empty */;
        }
    }

}

void wisun_rcp_init(void)
{
    struct sl_wsrcp_app *rcp_app = &g_rcp_ctxt;
    const osThreadAttr_t thread_attr = {
        .name = "Wi-SUN MAC",
        .stack_size = 2048, // Default value is not enough
    };

    uart_init(rcp_app);
    SEGGER_RTT_SetFlagsUpBuffer(0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    export_debugger_data();
    // Note: this function is launched before the Operating System, you can't
    // acquire anymutex in.
    rcp_app->uart_tx_lock = osMutexNew(NULL);
    rcp_app->main_events = osEventFlagsNew(NULL);
    rcp_app->main_task = osThreadNew(wisun_rcp_main, rcp_app, &thread_attr);
}

SL_WEAK void assertEFM(const char *file, int line)
{
    BUG("assert in %s:%d\n", file, line);
}
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
#include "sl_wsrcp_utils.h"
#include "sl_wsrcp_mac.h"
#include "sl_wsrcp_log.h"

// See warning in sl_wsrcp.h
struct sl_wsrcp_app g_rcp_ctxt = { 0 };

/* CPC and UART does not handle reset sequence in the same way:
 *
 *                       |       CPC        |      UART
 * ----------------------|------------------|-------------------
 * reset the CPU         | on cpc error     | on reset request
 * send reset indication | on reset request | on boot
 */

#if defined SL_CATALOG_CPC_SECONDARY_PRESENT
#include <sl_cpc.h>
#include "sl_wsrcp_cpc.h"

void cpc_rx_ready(uint8_t cpc_ep, void *user_param)
{
    struct sl_wsrcp_app *rcp_app = container_of((sl_cpc_endpoint_handle_t *)user_param, struct sl_wsrcp_app, cpc_ep);
    (void)cpc_ep;

    osEventFlagsSet(rcp_app->main_events, RX_UART);
}

void cpc_on_error(uint8_t cpc_ep, void *user_param)
{
    (void)cpc_ep;
    (void)user_param;

    NVIC_SystemReset();
}

void wsmac_on_reset_req(struct sl_wsrcp_mac *rcp_mac)
{
    wsmac_send_reset_ind(rcp_mac);
}

static void wisun_rcp_init_bus(struct sl_wsrcp_app *rcp_app)
{
    cpc_init(&rcp_app->cpc_ep);
    rcp_app->rcp_mac = wsmac_register(cpc_tx, cpc_rx, &rcp_app->cpc_ep);
    wsmac_init_timers(rcp_app->rcp_mac, &rcp_app->rcp_timer_context);
}

#elif defined SL_CATALOG_IOSTREAM_UART_COMMON_PRESENT

#include "sl_wsrcp_uart_plt.h"

static int wisun_rcp_uart_plt_tx(void *cb_data, const void *buf, int buf_len)
{
    return uart_plt_tx(cb_data, buf, buf_len);
}

static int wisun_rcp_uart_plt_rx(void *cb_data, void *buf, int buf_len)
{
    return uart_plt_rx(cb_data, buf, buf_len);
}

void uart_plt_rx_ready(struct sl_wsrcp_uart_plt *uart_ctxt)
{
    struct sl_wsrcp_app *rcp_app = container_of(uart_ctxt, struct sl_wsrcp_app, uart_plt);

    osEventFlagsSet(rcp_app->main_events, RX_UART);
}

void uart_plt_crc_error(struct sl_wsrcp_uart_plt *uart_ctxt, uint16_t crc, int frame_len, uint8_t header, uint8_t irq_err_counter)
{
    struct sl_wsrcp_app *rcp_app = container_of(uart_ctxt, struct sl_wsrcp_app, uart_plt);

    wsmac_report_rx_crc_error(rcp_app->rcp_mac, crc, frame_len, header, irq_err_counter);
}

void wsmac_on_reset_req(struct sl_wsrcp_mac *rcp_mac)
{
    (void)rcp_mac;

    NVIC_SystemReset();
}

static void wisun_rcp_init_bus(struct sl_wsrcp_app *rcp_app)
{
    uart_plt_init(&rcp_app->uart_plt);
    rcp_app->rcp_mac = wsmac_register(wisun_rcp_uart_plt_tx, wisun_rcp_uart_plt_rx, &rcp_app->uart_plt);
    wsmac_init_timers(rcp_app->rcp_mac, &rcp_app->rcp_timer_context);
    wsmac_send_reset_ind(rcp_app->rcp_mac);
}

#else

#include "sl_wsrcp_uart.h"

static int wisun_rcp_uart_tx(void *cb_data, const void *buf, int buf_len)
{
    return uart_tx(cb_data, buf, buf_len);
}

static int wisun_rcp_uart_rx(void *cb_data, void *buf, int buf_len)
{
    return uart_rx(cb_data, buf, buf_len);
}

void uart_rx_ready(struct sl_wsrcp_uart *uart_ctxt)
{
    struct sl_wsrcp_app *rcp_app = container_of(uart_ctxt, struct sl_wsrcp_app, uart);

    osEventFlagsSet(rcp_app->main_events, RX_UART);
}

void uart_crc_error(struct sl_wsrcp_uart *uart_ctxt, uint16_t crc, int frame_len, uint8_t header, uint8_t irq_err_counter)
{
    struct sl_wsrcp_app *rcp_app = container_of(uart_ctxt, struct sl_wsrcp_app, uart);

    wsmac_report_rx_crc_error(rcp_app->rcp_mac, crc, frame_len, header, irq_err_counter);
}

void wsmac_on_reset_req(struct sl_wsrcp_mac *rcp_mac)
{
    (void)rcp_mac;

    NVIC_SystemReset();
}

static void wisun_rcp_init_bus(struct sl_wsrcp_app *rcp_app)
{
    uart_init(&rcp_app->uart);
    rcp_app->rcp_mac = wsmac_register(wisun_rcp_uart_tx, wisun_rcp_uart_rx, &rcp_app->uart);
    wsmac_init_timers(rcp_app->rcp_mac, &rcp_app->rcp_timer_context);
    wsmac_send_reset_ind(rcp_app->rcp_mac);
}

#endif

static void wisun_rcp_on_phy_timer_expiration(sli_wisun_timer_context_t *ctxt)
{
  struct sl_wsrcp_app *rcp_app = container_of((sli_wisun_timer_context_t *)ctxt, struct sl_wsrcp_app, rcp_timer_context);
  osEventFlagsSet(rcp_app->main_events, TIMER_EXPIRED);
}

void wisun_rcp_main(void *arg)
{
    struct sl_wsrcp_app *rcp_app = arg;
    uint32_t flags;

    sli_wisun_timer_context_setup(&rcp_app->rcp_timer_context, wisun_rcp_on_phy_timer_expiration, "wisun_rcp");
    wisun_rcp_init_bus(rcp_app);
    for (;;) {
        flags = osEventFlagsWait(rcp_app->main_events, RX_UART | TIMER_EXPIRED, osFlagsWaitAny, osWaitForever);
        if (flags & 0x10000000)
            WARN("Error: %08" PRIu32, flags);
        if (flags & RX_UART) {
            while (wsmac_rx_host(rcp_app->rcp_mac))
                /* empty */;
        }
        if (flags & TIMER_EXPIRED) {
            sli_wisun_timer_context_dispatcher(&rcp_app->rcp_timer_context);
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

    sl_iostream_set_default(sl_iostream_rtt_handle);
    SEGGER_RTT_SetFlagsUpBuffer(0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    export_debugger_data();
    // Note: this function is launched before the Operating System, you can't
    // acquire anymutex in.
    rcp_app->main_events = osEventFlagsNew(NULL);
    rcp_app->main_task = osThreadNew(wisun_rcp_main, rcp_app, &thread_attr);
}

void assertEFM(const char *file, int line)
{
    BUG("assert in %s:%d\n", file, line);
}

void HardFault_Handler(void) 
{
    NVIC_SystemReset();
}

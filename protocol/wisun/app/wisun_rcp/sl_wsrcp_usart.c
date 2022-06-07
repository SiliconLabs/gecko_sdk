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

#include <string.h>
#include <em_usart.h>
#include <em_cmu.h>
#include <em_gpio.h>
#include "sl_wsrcp.h"
#include "sl_wsrcp_log.h"
#include "sl_wsrcp_uart.h"

#define UART_PERIPHERAL         USART0
#define UART_PERIPHERAL_NO      0
#define UART_CLOCK              cmuClock_USART0
#define UART_RX_IRQ             USART0_RX_IRQn

#define UART_TX_PORT            gpioPortA
#define UART_TX_PIN             0
#define UART_TX_LOC             0

#define UART_RX_PORT            gpioPortA
#define UART_RX_PIN             1
#define UART_RX_LOC             0

void uart_init(struct sl_wsrcp_app *rcp_app)
{
    USART_InitAsync_TypeDef config = USART_INITASYNC_DEFAULT;

    ring_init(&rcp_app->rx_buf, rcp_app->rx_buf_data, sizeof(rcp_app->rx_buf_data));
    rcp_app->sdk_uart = UART_PERIPHERAL;
    //CORE_SetNvicRamTableHandler(UART_RX_IRQ, uart_rx_irq);
    NVIC_ClearPendingIRQ(UART_RX_IRQ);
    NVIC_EnableIRQ(UART_RX_IRQ);
#if defined(_CMU_HFPERCLKEN0_MASK)
    CMU_ClockEnable(cmuClock_HFPER, true);
#endif
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(UART_CLOCK, true);
    GPIO_PinModeSet(UART_TX_PORT, UART_TX_PIN, gpioModePushPull, 1);
    GPIO_PinModeSet(UART_RX_PORT, UART_RX_PIN, gpioModeInputPull, 1);
    config.enable = usartDisable;
    USART_InitAsync(rcp_app->sdk_uart, &config);

    #if defined(USART_ROUTEPEN_TXPEN)
        rcp_app->sdk_uart->ROUTELOC0 &= ~(_USART_ROUTELOC0_TXLOC_MASK | _USART_ROUTELOC0_RXLOC_MASK);
        rcp_app->sdk_uart->ROUTELOC0 |= UART_TX_LOC << _USART_ROUTELOC0_TXLOC_SHIFT;
        rcp_app->sdk_uart->ROUTELOC0 |= UART_RX_LOC << _USART_ROUTELOC0_RXLOC_SHIFT;
        rcp_app->sdk_uart->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;
    #else
        #error Not supported
    #endif
    rcp_app->sdk_uart->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
    USART_IntClear(rcp_app->sdk_uart, 0xFFFFFFFF);
    USART_IntEnable(rcp_app->sdk_uart, USART_IF_RXDATAV);
    USART_Enable(rcp_app->sdk_uart, usartEnable);
}

void USART0_RX_IRQHandler(void)
{
    struct sl_wsrcp_app *rcp_app = &g_rcp_ctxt;
    int ret;

    if (!(rcp_app->sdk_uart->STATUS & USART_STATUS_RXDATAV)) {
        WARN("unexpected IRQ");
        return;
    }

    if ((rcp_app->sdk_uart->IF & USART_IF_RXOF)) {
        WARN("RX buffer overflow");
        USART_IntClear(rcp_app->sdk_uart, USART_IF_RXOF);
        rcp_app->irq_rxof_cnt++;
    }
    ret = ring_push(&rcp_app->rx_buf, USART_Rx(rcp_app->sdk_uart));
    BUG_ON(ret, "buffer overflow");
    osEventFlagsSet(rcp_app->main_events, RX_UART);
}

void uart_tx_byte(struct sl_wsrcp_app *rcp_app, uint8_t data)
{
    USART_Tx(rcp_app->sdk_uart, data);
}

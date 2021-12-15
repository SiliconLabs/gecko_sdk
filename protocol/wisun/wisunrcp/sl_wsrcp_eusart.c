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
#include <em_eusart.h>
#include <em_cmu.h>
#include <em_gpio.h>
#include "sl_wsrcp.h"
#include "sl_wsrcp_log.h"
#include "sl_wsrcp_uart.h"


#define UART_PERIPHERAL         EUSART0
#define UART_PERIPHERAL_NO      0
#define UART_CLOCK              cmuClock_EUSART0
#define UART_RX_IRQ             EUSART0_RX_IRQn

#define UART_TX_PORT            gpioPortA
#define UART_TX_PIN             8
#define UART_TX_LOC             0

#define UART_RX_PORT            gpioPortA
#define UART_RX_PIN             9
#define UART_RX_LOC             0


// Used for debug to display the data sent/received on the bus
static char trace_buffer[128];

void uart_init(struct sl_wsrcp_app *rcp_app)
{
    EUSART_UartInit_TypeDef init = EUSART_UART_INIT_DEFAULT_HF;

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
    EUSART_UartInitHf(rcp_app->sdk_uart, &init);

    GPIO->EUSARTROUTE[EUSART_NUM(UART_PERIPHERAL)].ROUTEEN = GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_RXPEN;
    GPIO->EUSARTROUTE[EUSART_NUM(UART_PERIPHERAL)].TXROUTE = (UART_TX_PORT << _GPIO_EUSART_TXROUTE_PORT_SHIFT)
                                 | (UART_TX_PIN << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
    GPIO->EUSARTROUTE[EUSART_NUM(UART_PERIPHERAL)].RXROUTE = (UART_RX_PORT << _GPIO_EUSART_RXROUTE_PORT_SHIFT)
                                 | (UART_RX_PIN << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
    CMU_ClockEnable(cmuClock_PRS, true);
    CMU_ClockEnable(UART_CLOCK, true);
    CMU_ClockSelectSet(cmuClock_EM01GRPCCLK, cmuSelect_HFRCODPLL);
    if (UART_CLOCK == cmuClock_EUSART0) {
        CMU_ClockSelectSet(cmuClock_EUSART0CLK, cmuSelect_EM01GRPCCLK);
    }
    EUSART_IntClear(rcp_app->sdk_uart, 0xFFFFFFFF);
    EUSART_IntEnable(rcp_app->sdk_uart, EUSART_IF_RXFL);
    EUSART_Enable(rcp_app->sdk_uart, eusartEnable);
}

void EUSART0_RX_IRQHandler(void)
{
    struct sl_wsrcp_app *rcp_app = &g_rcp_ctxt;
    int ret;

    if ((EUSART_IntGetEnabled(rcp_app->sdk_uart) & EUSART_IF_RXFL) == 0u) {
        WARN("unexpected IRQ");
        return;
    }

    ret = ring_push(&rcp_app->rx_buf, EUSART_Rx(rcp_app->sdk_uart));
    BUG_ON(ret, "buffer overflow");
    osEventFlagsSet(rcp_app->main_events, RX_UART);

    EUSART_IntClear(rcp_app->sdk_uart, EUSART_IF_RXFL);
}

void uart_tx_byte(struct sl_wsrcp_app *rcp_app, uint8_t data)
{
    EUSART_Tx(rcp_app->sdk_uart, data);
}

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
#ifndef SL_WSRCP_CPC_H
#define SL_WSRCP_CPC_H
#include <cmsis_os2.h>
#include <sl_iostream.h>
#include "sl_ring.h"

struct sl_wsrcp_uart_plt {
    sl_iostream_t *stream;
    osMutexId_t tx_lock;
    int irq_overflow_cnt;

    // Note it may be possible to drop rx_ring and save 4kB of data. The user
    // would get the data directly from buf_rx. However, navigating in buf_rx is
    // not easy and is error prone.
    struct ring rx_ring;
    uint8_t rx_ring_data[4096];

};

void uart_plt_init(struct sl_wsrcp_uart_plt *uart_ctxt);
int uart_plt_tx(struct sl_wsrcp_uart_plt *uart_ctxt, const void *buf, int buf_len);
int uart_plt_rx(struct sl_wsrcp_uart_plt *uart_ctxt, void *buf, int buf_len);

// Called when a CRC error is detected in receveided frames before the frame is
// discarded. This funtion is declared "weak". So, the user can overload it and
// choose to increment a counter or report the error to the host.
void uart_plt_crc_error(struct sl_wsrcp_uart_plt *uart, uint16_t crc, int frame_len, uint8_t header, uint8_t irq_err_counter);

// Called from IRQ when new data are available. This funtion is declared "weak".
// So, the user can overload it. The user can post de necessary events from this
// callback (using osEventFlagsSet, osSemaphoreRelease, etc...). The user MUST
// NOT sleep in this function. He should neither handle data in this callback.
void uart_plt_rx_ready(struct sl_wsrcp_uart_plt *uart);

#endif

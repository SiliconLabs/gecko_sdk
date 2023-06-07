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
#include <cmsis_os2.h>
#include <sl_iostream.h>
#include <sl_iostream_handles.h>

#include "sl_ring.h"
#include "sl_wsrcp_log.h"
#include "sl_wsrcp_crc.h"
#include "sl_wsrcp_log.h"
#include "sl_wsrcp_uart_plt.h"

// Used for debug to display the data sent/received on the bus
static char trace_buffer[128];

__WEAK void uart_plt_rx_ready(struct sl_wsrcp_uart_plt *uart_ctxt)
{
    (void)uart_ctxt;
}

__WEAK void uart_plt_crc_error(struct sl_wsrcp_uart_plt *uart_ctxt, uint16_t crc, int frame_len, uint8_t header, uint8_t irq_overflow_cnt)
{
    (void)uart_ctxt;
    (void)crc;
    (void)frame_len;
    (void)header;
    (void)irq_overflow_cnt;
}

static int append_escaped_byte(uint8_t *buffer, uint8_t byte)
{
    if (byte == 0x7D || byte == 0x7E) {
        buffer[0] = 0x7D;
        buffer[1] = byte ^ 0x20;
        return 2;
    } else {
        buffer[0] = byte;
        return 1;
    }
}

int uart_plt_tx(struct sl_wsrcp_uart_plt *uart_ctxt, const void *buf, int buf_len)
{
    uint16_t crc = crc16(buf, buf_len);
    const uint8_t *buf8 = buf;
    uint8_t tmp_buf[1024];
    int buf_cnt = 0;
    size_t xfer_cnt;

    osMutexAcquire(uart_ctxt->tx_lock, osWaitForever);
    while (buf_cnt < buf_len) {
        xfer_cnt = 0;
        while (buf_cnt < buf_len && xfer_cnt < sizeof(tmp_buf) - 7) {
            xfer_cnt += append_escaped_byte(tmp_buf + xfer_cnt, buf8[buf_cnt]);
            buf_cnt++;
        }
        if (buf_cnt == buf_len) {
            xfer_cnt += append_escaped_byte(tmp_buf + xfer_cnt, crc & 0xFF);
            xfer_cnt += append_escaped_byte(tmp_buf + xfer_cnt, crc >> 8);
            tmp_buf[xfer_cnt++] = 0x7E;
        }
        sl_iostream_write(uart_ctxt->stream, tmp_buf, xfer_cnt);
    }
    osMutexRelease(uart_ctxt->tx_lock);

    TRACE(TR_HDLC, "hdlc tx: %s (%d bytes)",
           bytes_str(buf, buf_len, NULL, trace_buffer, sizeof(trace_buffer), DELIM_SPACE | ELLIPSIS_STAR), buf_len);
    return buf_len;
}

void uart_plt_rx_thread(void *arg)
{
    struct sl_wsrcp_uart_plt *uart_ctxt = arg;
    // Avoid allocating too much data in stack
    static uint8_t buf[256];
    size_t len;
    unsigned int i;
    int ret;

    for (;;) {
        sl_iostream_read(uart_ctxt->stream, buf, sizeof(buf), &len);
        for (i = 0; i < len; i++) {
            ret = ring_push(&uart_ctxt->rx_ring, buf[i]);
            BUG_ON(ret, "buffer overflow");
        }
        uart_plt_rx_ready(uart_ctxt);
    }
}

int uart_plt_rx(struct sl_wsrcp_uart_plt *uart_ctxt, void *buf, int buf_len)
{
    uint8_t *buf8 = buf;
    uint16_t crc;
    int i, frame_len;
    int data;

    while (ring_get(&uart_ctxt->rx_ring, 0) == 0x7E)
        ring_pop(&uart_ctxt->rx_ring);

    for (i = 0, data = 0; data != 0x7E; i++) {
        data = ring_get(&uart_ctxt->rx_ring, i);
        if (data < 0)
            return 0;
    }

    frame_len = 0;
    do {
        BUG_ON(frame_len >= buf_len);
        data = ring_pop(&uart_ctxt->rx_ring);
        BUG_ON(data < 0);
        if (data == 0x7D)
            buf8[frame_len++] = ring_pop(&uart_ctxt->rx_ring) ^ 0x20;
        else if (data != 0x7E)
            buf8[frame_len++] = data;
    } while (data != 0x7E);
    if (frame_len <= 2) {
        WARN("short frame");
        return uart_plt_rx(uart_ctxt, buf, buf_len);
    }
    frame_len -= sizeof(uint16_t);
    crc = crc16(buf8, frame_len);
    if (memcmp(buf8 + frame_len, &crc, sizeof(uint16_t))) {
        WARN("bad crc, frame dropped");
        uart_plt_crc_error(uart_ctxt, *(uint16_t *)(buf8 + frame_len), frame_len, buf8[0], uart_ctxt->irq_overflow_cnt);
        uart_ctxt->irq_overflow_cnt = 0;
        return uart_plt_rx(uart_ctxt, buf, buf_len);
    }
    TRACE(TR_HDLC, "hdlc rx: %s (%d bytes)",
           bytes_str(buf, frame_len, NULL, trace_buffer, sizeof(trace_buffer), DELIM_SPACE | ELLIPSIS_STAR), frame_len);
    return frame_len;
}

void uart_plt_init(struct sl_wsrcp_uart_plt *uart_ctxt)
{
    ring_init(&uart_ctxt->rx_ring, uart_ctxt->rx_ring_data, sizeof(uart_ctxt->rx_ring_data));
    uart_ctxt->tx_lock = osMutexNew(NULL);
    uart_ctxt->stream = sl_iostream_vcom_handle;
    uart_ctxt->irq_overflow_cnt = 0;
    osThreadNew(uart_plt_rx_thread, uart_ctxt, NULL);
}

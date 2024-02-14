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
#include <common/bits.h>
#include <common/endian.h>

#include "sl_ring.h"
#include "sl_wsrcp_log.h"
#include "sl_wsrcp_crc.h"
#include "sl_wsrcp_log.h"
#include "sl_wsrcp_uart_plt.h"

#define MASK_PAYLOAD_LEN 0x07ff

// Used for debug to display the data sent/received on the bus
static char trace_buffer[128];

__WEAK void uart_plt_rx_ready(struct sl_wsrcp_uart_plt *uart_ctxt)
{
    (void)uart_ctxt;
}

__WEAK void uart_plt_crc_error(struct sl_wsrcp_uart_plt *uart_ctxt, uint8_t irq_overflow_cnt)
{
    (void)uart_ctxt;
    (void)irq_overflow_cnt;
}

int uart_plt_tx(struct sl_wsrcp_uart_plt *uart_ctxt, const void *buf, int buf_len)
{
    uint8_t hdr[4], fcs[2];

    BUG_ON(buf_len > FIELD_MAX(MASK_PAYLOAD_LEN));
    write_le16(hdr,     FIELD_PREP(MASK_PAYLOAD_LEN, buf_len));
    write_le16(hdr + 2, crc16(CRC_INIT_HCS, hdr, 2));
    write_le16(fcs,     crc16(CRC_INIT_FCS, buf, buf_len));

    osMutexAcquire(uart_ctxt->tx_lock, osWaitForever);
    sl_iostream_write(uart_ctxt->stream, hdr, sizeof(hdr));
    sl_iostream_write(uart_ctxt->stream, buf, buf_len);
    sl_iostream_write(uart_ctxt->stream, fcs, sizeof(fcs));
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
    uint8_t hdr[4], fcs[2];
    bool garbage = false;
    uint8_t *buf8 = buf;
    uint16_t len;

    while (1) {
        // Search for a valid header
        while (ring_data_len(&uart_ctxt->rx_ring) >= 4) {
            ring_get_buf(&uart_ctxt->rx_ring, 0, hdr, 4);
            if (crc16(CRC_INIT_HCS, hdr, 2) == read_le16(hdr + 2))
                break;
            garbage = true;
            ring_pop(&uart_ctxt->rx_ring);
        }
        WARN_ON(garbage, "rx-bus: garbage found");
        if (ring_data_len(&uart_ctxt->rx_ring) < 4)
            return 0; // No valid header found

        len = FIELD_GET(MASK_PAYLOAD_LEN, read_le16(hdr));
        if (ring_data_len(&uart_ctxt->rx_ring) < 4u + len + 2)
            return 0; // Frame not fully received

        BUG_ON(buf_len < len);
        ring_get_buf(&uart_ctxt->rx_ring, 4, buf8, len);
        ring_get_buf(&uart_ctxt->rx_ring, 4 + len, fcs, sizeof(fcs));

        if (crc16(CRC_INIT_FCS, buf8, len) == read_le16(fcs)) {
            ring_pop_buf(&uart_ctxt->rx_ring, NULL, 4 + len + 2);
            return len;
        }

        WARN("rx-bus: invalid FCS");
        uart_plt_crc_error(uart_ctxt, uart_ctxt->irq_overflow_cnt);
        ring_pop(&uart_ctxt->rx_ring);
    }
}

void uart_plt_init(struct sl_wsrcp_uart_plt *uart_ctxt)
{
    ring_init(&uart_ctxt->rx_ring, uart_ctxt->rx_ring_data, sizeof(uart_ctxt->rx_ring_data));
    uart_ctxt->tx_lock = osMutexNew(NULL);
    uart_ctxt->stream = sl_iostream_vcom_handle;
    uart_ctxt->irq_overflow_cnt = 0;
    osThreadNew(uart_plt_rx_thread, uart_ctxt, NULL);
}

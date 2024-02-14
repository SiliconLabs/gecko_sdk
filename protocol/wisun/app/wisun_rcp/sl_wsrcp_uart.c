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
#include <em_cmu.h>
#include <em_gpio.h>
#include <common/bits.h>
#include <common/endian.h>

#include "sl_wsrcp.h"
#include "sl_wsrcp_crc.h"
#include "sl_wsrcp_log.h"
#include "sl_wsrcp_utils.h"
#include "sl_wsrcp_uart.h"
#include "sl_wsrcp_uart_config.h"
#include "sl_wsrcp_mac.h"

#define MASK_PAYLOAD_LEN 0x07ff

__WEAK void uart_rx_ready(struct sl_wsrcp_uart *uart_ctxt)
{
    (void)uart_ctxt;
}

__WEAK void uart_crc_error(struct sl_wsrcp_uart *uart_ctxt, uint8_t irq_overflow_cnt)
{
    (void)uart_ctxt;
    (void)irq_overflow_cnt;
}

static bool uart_handle_rx_dma_complete(unsigned int chan, unsigned int seq_num, void *user_param)
{
    CORE_DECLARE_IRQ_STATE;
    struct sl_wsrcp_uart *uart_ctxt = user_param;
    int ret;
    unsigned int i;

    (void)chan;
    (void)seq_num;

    // Protect descr_cnt_rx and rx_ring against uart_handle_rx_dma_timeout()
    CORE_ENTER_ATOMIC();
    for (i = 0; i < sizeof(uart_ctxt->buf_rx[0]); i++) {
        ret = ring_push(&uart_ctxt->rx_ring, uart_ctxt->buf_rx[uart_ctxt->descr_cnt_rx][i]);
        BUG_ON(ret, "buffer overflow");
    }
    uart_ctxt->descr_cnt_rx += 1;
    uart_ctxt->descr_cnt_rx %= ARRAY_SIZE(uart_ctxt->buf_rx);
    uart_rx_ready(uart_ctxt);
    CORE_EXIT_ATOMIC();
    return true;
}

static bool uart_handle_tx_dma_complete(unsigned int chan, unsigned int seq_num, void *user_param)
{
    struct sl_wsrcp_uart *uart_ctxt = user_param;

    (void)chan;
    (void)seq_num;

    osSemaphoreRelease(uart_ctxt->tx_dma_lock);
    return true;
}

void uart_handle_rx_dma_timeout(struct sl_wsrcp_uart *uart_ctxt)
{
    CORE_DECLARE_IRQ_STATE;
    LDMA_TransferCfg_t ldma_cfg = LDMA_TRANSFER_CFG_PERIPHERAL(UART_LDMA_SIGNAL_RX);
    int remaining, descr_cnt_rx, ret;
    size_t i;

    // Protect descr_cnt_rx and rx_ring against uart_handle_rx_dma_complete()
    CORE_ENTER_ATOMIC();
    // Begin of realtime constrained section
    // (with USART, we need to execute that in less than 5µs for a 2Mbps UART link)
    // (with EUSART, thanks to it 16bytes depth fifo , we need to execute the
    // code below in less than 40µs for a 4Mbps UART link)
    DMADRV_StopTransfer(uart_ctxt->dma_chan_rx);
    DMADRV_TransferRemainingCount(uart_ctxt->dma_chan_rx, &remaining);
    descr_cnt_rx = uart_ctxt->descr_cnt_rx;
    uart_ctxt->descr_cnt_rx += 1;
    uart_ctxt->descr_cnt_rx %= ARRAY_SIZE(uart_ctxt->buf_rx);
    DMADRV_LdmaStartTransfer(uart_ctxt->dma_chan_rx, &ldma_cfg,
                             &(uart_ctxt->descr_rx[uart_ctxt->descr_cnt_rx]),
                             uart_handle_rx_dma_complete, uart_ctxt);
    // End of realtime constrained section

    for (i = 0; i < sizeof(uart_ctxt->buf_rx[0]) - remaining; i++) {
        ret = ring_push(&uart_ctxt->rx_ring, uart_ctxt->buf_rx[descr_cnt_rx][i]);
        BUG_ON(ret, "buffer overflow");
    }
    uart_rx_ready(uart_ctxt);
    CORE_EXIT_ATOMIC();
}

void uart_handle_rx_overflow(struct sl_wsrcp_uart *uart_ctxt)
{
    WARN("IRQ overflow");
    uart_ctxt->irq_overflow_cnt++;
}

int uart_tx(struct sl_wsrcp_uart *uart_ctxt, const void *buf, int buf_len)
{
    LDMA_TransferCfg_t ldma_cfg = LDMA_TRANSFER_CFG_PERIPHERAL(UART_LDMA_SIGNAL_TX);
    LDMA_Descriptor_t *dma_descr;
    const uint8_t *buf8 = buf;
    uint16_t buf_offset = 0;
    uint16_t buf_cpy_len;
    uint16_t buf_remaining;
    uint16_t dma_buf_offset;
    uint16_t dma_buf_remaining;
    uint8_t *dma_buf;

    BUG_ON(buf_len > FIELD_MAX(MASK_PAYLOAD_LEN));
    // Only double buffering is supported
    BUG_ON(ARRAY_SIZE(uart_ctxt->descr_tx) != 2);
    BUG_ON(sizeof(uart_ctxt->buf_tx[0]) > DMADRV_MAX_XFER_COUNT);

    osMutexAcquire(uart_ctxt->tx_lock, osWaitForever);
    while (buf_offset < buf_len) {
        dma_buf   = uart_ctxt->buf_tx[uart_ctxt->descr_cnt_tx];
        dma_descr = &uart_ctxt->descr_tx[uart_ctxt->descr_cnt_tx];
        dma_buf_offset = 0;

        if (buf_offset == 0) {
            write_le16(dma_buf,     FIELD_PREP(MASK_PAYLOAD_LEN, buf_len));
            write_le16(dma_buf + 2, crc16(CRC_INIT_HCS, dma_buf, 2));
            dma_buf_offset = 4;
        }
        dma_buf_remaining = sizeof(uart_ctxt->buf_tx[0]) - dma_buf_offset;
        buf_remaining     = buf_len - buf_offset;
        if (dma_buf_remaining < buf_remaining + 2) {
            // If there is space to push the remaining data but not the FCS,
            // keep one data byte for the next DMA buffer.
            buf_cpy_len = min(buf_remaining - 1, dma_buf_remaining);
            memcpy(dma_buf + dma_buf_offset, buf8 + buf_offset, buf_cpy_len);
            dma_buf_offset += buf_cpy_len;
            buf_offset     += buf_cpy_len;
        } else {
            memcpy(dma_buf + dma_buf_offset, buf8 + buf_offset, buf_remaining);
            dma_buf_offset += buf_remaining;
            buf_offset     += buf_remaining;
            write_le16(dma_buf + dma_buf_offset, crc16(CRC_INIT_FCS, buf8, buf_len));
            dma_buf_offset += 2;
        }
        dma_descr->xfer.xferCnt = dma_buf_offset - 1;
        osSemaphoreAcquire(uart_ctxt->tx_dma_lock, osWaitForever);
        DMADRV_LdmaStartTransfer(uart_ctxt->dma_chan_tx, &ldma_cfg,
                                 dma_descr, uart_handle_tx_dma_complete, uart_ctxt);
        uart_ctxt->descr_cnt_tx = (uart_ctxt->descr_cnt_tx + 1) % ARRAY_SIZE(uart_ctxt->descr_tx);
    }
    osMutexRelease(uart_ctxt->tx_lock);
    return buf_len;
}

static void uart_timeout(struct sli_wisun_timer *timer)
{
    struct sl_wsrcp_uart *uart_ctxt = container_of(timer, struct sl_wsrcp_uart, timer);

    // If a frame header was received but the payload takes too long to be
    // received, assume that the frame was canceled, and search for a new
    // header in the remaining bytes.
    WARN("rx-bus: frame timeout");
    ring_pop(&uart_ctxt->rx_ring);
    uart_rx_ready(uart_ctxt);
}

int uart_rx(struct sl_wsrcp_uart *uart_ctxt, void *buf, int buf_len)
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

        if (!sli_wisun_timer_is_running(&uart_ctxt->timer))
            sli_wisun_timer_start_relative_s(&uart_ctxt->timer, 2);
        len = FIELD_GET(MASK_PAYLOAD_LEN, read_le16(hdr));
        if (ring_data_len(&uart_ctxt->rx_ring) < 4u + len + 2)
            return 0; // Frame not fully received

        BUG_ON(buf_len < len);
        ring_get_buf(&uart_ctxt->rx_ring, 4, buf8, len);
        ring_get_buf(&uart_ctxt->rx_ring, 4 + len, fcs, sizeof(fcs));

        if (crc16(CRC_INIT_FCS, buf8, len) == read_le16(fcs)) {
            ring_pop_buf(&uart_ctxt->rx_ring, NULL, 4 + len + 2);
            sli_wisun_timer_stop(&uart_ctxt->timer);
            return len;
        }

        WARN("rx-bus: invalid FCS");
        uart_crc_error(uart_ctxt, uart_ctxt->irq_overflow_cnt);
        ring_pop(&uart_ctxt->rx_ring);
    }
}

void uart_init(struct sl_wsrcp_uart *uart_ctxt, struct sli_wisun_timer_context *timer_ctxt)
{
    LDMA_TransferCfg_t ldma_cfg = LDMA_TRANSFER_CFG_PERIPHERAL(UART_LDMA_SIGNAL_RX);
    unsigned int i, next;

    ring_init(&uart_ctxt->rx_ring, uart_ctxt->rx_ring_data, sizeof(uart_ctxt->rx_ring_data));
    uart_ctxt->tx_lock = osMutexNew(NULL);
    uart_ctxt->tx_dma_lock = osSemaphoreNew(1, 1, NULL);
    uart_ctxt->hw_regs = UART_PERIPHERAL;
    for (i = 0; i < ARRAY_SIZE(uart_ctxt->descr_rx); i++) {
        uart_ctxt->descr_rx[i].xfer.structType  = ldmaCtrlStructTypeXfer;
        uart_ctxt->descr_rx[i].xfer.blockSize   = ldmaCtrlBlockSizeUnit1;
        uart_ctxt->descr_rx[i].xfer.reqMode     = ldmaCtrlReqModeBlock;
        uart_ctxt->descr_rx[i].xfer.doneIfs     = 1;

        uart_ctxt->descr_rx[i].xfer.size        = ldmaCtrlSizeByte;
        uart_ctxt->descr_rx[i].xfer.xferCnt     = sizeof(uart_ctxt->buf_rx[0]) - 1;

        uart_ctxt->descr_rx[i].xfer.srcInc      = ldmaCtrlSrcIncNone;
        uart_ctxt->descr_rx[i].xfer.srcAddrMode = ldmaCtrlSrcAddrModeAbs;
        uart_ctxt->descr_rx[i].xfer.srcAddr     = (uintptr_t)&(uart_ctxt->hw_regs->RXDATA);

        uart_ctxt->descr_rx[i].xfer.dstInc      = ldmaCtrlDstIncOne;
        uart_ctxt->descr_rx[i].xfer.dstAddrMode = ldmaCtrlDstAddrModeAbs;
        uart_ctxt->descr_rx[i].xfer.dstAddr     = (uintptr_t)&(uart_ctxt->buf_rx[i]);

        uart_ctxt->descr_rx[i].xfer.linkMode    = ldmaLinkModeAbs;
        uart_ctxt->descr_rx[i].xfer.link        = 1;

        next = i + 1;
        next %= ARRAY_SIZE(uart_ctxt->descr_rx);
        uart_ctxt->descr_rx[i].xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&uart_ctxt->descr_rx[next]);
    }

    for (i = 0; i < ARRAY_SIZE(uart_ctxt->descr_tx); i++) {
        uart_ctxt->descr_tx[i].xfer.structType  = ldmaCtrlStructTypeXfer;
        uart_ctxt->descr_tx[i].xfer.blockSize   = ldmaCtrlBlockSizeUnit1;
        uart_ctxt->descr_tx[i].xfer.reqMode     = ldmaCtrlReqModeBlock;
        uart_ctxt->descr_tx[i].xfer.doneIfs     = 1;

        uart_ctxt->descr_tx[i].xfer.size        = ldmaCtrlSizeByte;

        uart_ctxt->descr_tx[i].xfer.srcInc      = ldmaCtrlDstIncOne;
        uart_ctxt->descr_tx[i].xfer.srcAddrMode = ldmaCtrlDstAddrModeAbs;
        uart_ctxt->descr_tx[i].xfer.srcAddr     = (uintptr_t)&(uart_ctxt->buf_tx[i]);

        uart_ctxt->descr_tx[i].xfer.dstInc      = ldmaCtrlSrcIncNone;
        uart_ctxt->descr_tx[i].xfer.dstAddrMode = ldmaCtrlSrcAddrModeAbs;
        uart_ctxt->descr_tx[i].xfer.dstAddr     = (uintptr_t)&(uart_ctxt->hw_regs->TXDATA);
    }
    uart_hw_init(uart_ctxt);
    DMADRV_Init();
    DMADRV_AllocateChannel(&uart_ctxt->dma_chan_tx, NULL);
    DMADRV_AllocateChannel(&uart_ctxt->dma_chan_rx, NULL);
    DMADRV_LdmaStartTransfer(uart_ctxt->dma_chan_rx, &ldma_cfg,
                             &(uart_ctxt->descr_rx[0]),
                             uart_handle_rx_dma_complete, uart_ctxt);
    sli_wisun_timer_init(&uart_ctxt->timer, timer_ctxt, uart_timeout, "UART frame timeout");
}

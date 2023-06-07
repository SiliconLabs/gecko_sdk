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
#include <sl_cpc.h>
#include <sli_cpc.h>

#if __has_include("sl_cpc_drv_secondary_spi_config.h")
#include "sl_cpc_drv_secondary_spi_config.h"
#endif

#if defined(SL_CPC_DRV_SPI_EXP_BITRATE) && SL_CPC_DRV_SPI_EXP_BITRATE != 1000000
#error SPI can only be used with a 1MHz clock
#endif

#include "sl_wsrcp_log.h"

// Used for debug to display the data sent/received on the bus
static char trace_buffer[128];
static osSemaphoreId_t g_tx_lock;

__WEAK void cpc_rx_ready(uint8_t cpc_ep, void *user_param)
{
    (void)cpc_ep;
    (void)user_param;
}

__WEAK void cpc_on_error(uint8_t cpc_ep, void *user_param)
{
    (void)cpc_ep;
    (void)user_param;
}

static void cpc_tx_complete(uint8_t cpc_ep, void *buffer, void *user_param, sl_status_t status)
{
    //sl_cpc_endpoint_handle_t *cpc_ep = user_param;

    (void)cpc_ep;
    (void)buffer;
    (void)user_param;
    (void)status;

    osSemaphoreRelease(g_tx_lock);
}

int cpc_tx(void *ctxt, void *buf, int buf_len)
{
    sl_cpc_endpoint_handle_t *cpc_ep = ctxt;
    int ret;

    ret = sl_cpc_write(cpc_ep, buf, buf_len, 0, NULL);
    TRACE(TR_HDLC, "hdlc tx: %s (%d bytes)",
           bytes_str(buf, buf_len, NULL, trace_buffer, sizeof(trace_buffer), DELIM_SPACE | ELLIPSIS_STAR), buf_len);
    osSemaphoreAcquire(g_tx_lock, osWaitForever);
    return ret;
}

int cpc_rx(void *ctxt, void *buf, int buf_len)
{
    sl_cpc_endpoint_handle_t *cpc_ep = ctxt;
    sl_status_t ret;
    void *cpc_buf;
    uint16_t cpc_buf_len;

    ret = sl_cpc_read(cpc_ep, &cpc_buf, &cpc_buf_len, 0, SL_CPC_FLAG_NO_BLOCK);
    if (ret)
        return 0;
    BUG_ON(cpc_buf_len > buf_len);
    memcpy(buf, cpc_buf, cpc_buf_len);
    sl_cpc_free_rx_buffer(cpc_buf);
    TRACE(TR_HDLC, "hdlc rx: %s (%d bytes)",
           bytes_str(buf, cpc_buf_len, NULL, trace_buffer, sizeof(trace_buffer), DELIM_SPACE | ELLIPSIS_STAR), cpc_buf_len);
    return cpc_buf_len;
}

void cpc_init(sl_cpc_endpoint_handle_t *cpc_ep)
{
    int ret;

    g_tx_lock = osSemaphoreNew(1, 0, NULL);
    // sl_cpc_init();
    ret = sli_cpc_open_service_endpoint(cpc_ep, SL_CPC_ENDPOINT_WISUN, 0, 1);
    BUG_ON(ret);
    ret = sl_cpc_set_endpoint_option(cpc_ep, SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE,
                                     (void *)cpc_rx_ready);
    BUG_ON(ret);
    ret = sl_cpc_set_endpoint_option(cpc_ep, SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE_ARG,
                                     cpc_ep);
    BUG_ON(ret);
    ret = sl_cpc_set_endpoint_option(cpc_ep, SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED,
                                     (void *)cpc_tx_complete);
    BUG_ON(ret);
    ret = sl_cpc_set_endpoint_option(cpc_ep, SL_CPC_ENDPOINT_ON_ERROR,
                                     (void *)cpc_on_error);
    BUG_ON(ret);
}

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
#ifndef SL_WSRCP_UART_H
#define SL_WSRCP_UART_H

#include <stdint.h>

struct sl_wsrcp_app;

void uart_init(struct sl_wsrcp_app *rcp_app);
int uart_tx(struct sl_wsrcp_app *rcp_app, const void *buf, int buf_len);
int uart_rx(struct sl_wsrcp_app *rcp_app, void *buf, int buf_len);
void uart_tx_byte(struct sl_wsrcp_app *rcp_app, uint8_t data);

#endif

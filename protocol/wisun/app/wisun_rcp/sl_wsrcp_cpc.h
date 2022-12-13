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

#include <sl_cpc.h>

#include "sl_ring.h"

void cpc_init(sl_cpc_endpoint_handle_t *cpc_ep);
int cpc_tx(void *cpc_ep, const void *buf, int buf_len);
int cpc_rx(void *cpc_ep, void *buf, int buf_len);

#endif

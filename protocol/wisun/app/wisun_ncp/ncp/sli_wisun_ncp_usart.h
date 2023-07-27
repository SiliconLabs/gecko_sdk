/***************************************************************************//**
 * @file sli_wisun_ncp_usart.h
 * @brief Wi-SUN NCP USART handling
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SLI_WISUN_NCP_USART_H
#define SLI_WISUN_NCP_USART_H

#include "sl_common.h"
#include "em_core.h"
#include "sl_status.h"

/**************************************************************************//**
 *****************************************************************************/
void sli_wisun_ncp_uart_init(void);

/**************************************************************************//**
 *****************************************************************************/
void sli_wisun_ncp_uart_transmit(uint32_t len, const uint8_t* data);

/**************************************************************************//**
 *****************************************************************************/
void sli_wisun_ncp_uart_transmit_cb(sl_status_t status);

/**************************************************************************//**
 *****************************************************************************/
void sli_wisun_ncp_uart_receive(void);

/**************************************************************************//**
 *****************************************************************************/
void sli_wisun_ncp_uart_receive_cb(sl_status_t status,
                                   uint32_t len,
                                   const uint8_t* data);

/**************************************************************************//**
 *****************************************************************************/
int sli_wisun_ncp_uart_timeout_cb(uint32_t timeout_count,
                                  uint32_t len,
                                  const uint8_t *data);

#endif  // SLI_WISUN_NCP_USART_H

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
#ifndef SL_WSRCP_CRC_H
#define SL_WSRCP_CRC_H

#include <stdint.h>

#define CRC_INIT_HCS 0xffff
#define CRC_INIT_FCS 0xc6c6

uint16_t crc16(uint16_t crc, const uint8_t *data, int len);

#endif



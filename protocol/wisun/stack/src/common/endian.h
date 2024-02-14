/*
 * Copyright (c) 2023 Silicon Laboratories Inc. (www.silabs.com)
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at [1].  This software is distributed to you in
 * Object Code format and/or Source Code format and is governed by the sections
 * of the MSLA applicable to Object Code, Source Code and Modified Open Source
 * Code. By using this software, you agree to the terms of the MSLA.
 *
 * [1]: https://www.silabs.com/about-us/legal/master-software-license-agreement
 */
#ifndef ENDIAN_H
#define ENDIAN_H
#include <stdint.h>
#include "common/int24.h"

/*
 * Convert native numbers to/from little/big endian. These functions are only
 * needed when the user want to read/write with a binary protocol (in the wsbrd
 * case: when working with spinel and Wi-SUN frames).
 *
 * This file includes support for int24_t since this size is commonly used in
 * 802.15.4 protocols.
 */

uint16_t read_be16(const uint8_t ptr[2]);
uint16_t read_le16(const uint8_t ptr[2]);
uint24_t read_be24(const uint8_t ptr[3]);
uint24_t read_le24(const uint8_t ptr[3]);
uint32_t read_be32(const uint8_t ptr[4]);
uint32_t read_le32(const uint8_t ptr[4]);
uint64_t read_be64(const uint8_t ptr[8]);
uint64_t read_le64(const uint8_t ptr[8]);

uint8_t *write_be16(uint8_t ptr[2], uint16_t val);
uint8_t *write_le16(uint8_t ptr[2], uint16_t val);
uint8_t *write_be24(uint8_t ptr[3], uint24_t val);
uint8_t *write_le24(uint8_t ptr[3], uint24_t val);
uint8_t *write_be32(uint8_t ptr[4], uint32_t val);
uint8_t *write_le32(uint8_t ptr[4], uint32_t val);
uint8_t *write_be64(uint8_t ptr[8], uint64_t val);
uint8_t *write_le64(uint8_t ptr[8], uint64_t val);

#endif

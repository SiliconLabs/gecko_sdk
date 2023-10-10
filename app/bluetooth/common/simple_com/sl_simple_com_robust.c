/***************************************************************************//**
 * @file
 * @brief Robust Communication
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
// -----------------------------------------------------------------------------
// Includes
#include <stdbool.h>
#include <string.h>
#include "sl_simple_com_robust.h"
#ifndef HOST_TOOLCHAIN
#include "sl_simple_com_config.h"
#else // HOST_TOOLCHAIN
#include "host_comm_config.h"
#endif // HOST_TOOLCHAIN

#define PREAMBLE_BYTE         0b01011010 // 0x5A
#define MAX_PAYLOAD_LENGTH    2047
#define PAYLOAD_LENGTH_MASK   0b11100000
#define CRC_PRESENT_FLAG      0b00010000

// -----------------------------------------------------------------------------
// Private function declarations

/**************************************************************************//**
 * Calculate CRC-4 checksum using the x^4 + x + 1 polynomial
 *
 * @param[in] data pointer to the input data
 * @param[in] len length of the input data in nibbles
 * @return CRC-4 checksum
 *****************************************************************************/
static uint8_t crc4(const uint8_t *data, size_t len);

#if defined(SL_SIMPLE_COM_ROBUST_CRC) && SL_SIMPLE_COM_ROBUST_CRC == 1
/**************************************************************************//**
 * Calculate CRC-8 checksum using the x^8 + x^2 + x + 1 polynomial
 *
 * @param[in] data pointer to the input data
 * @param[in] len size of the input data in bytes
 * @return CRC-8 checksum
 *****************************************************************************/
static uint8_t crc8(const uint8_t *data, size_t len);
#endif

// -----------------------------------------------------------------------------
// Private function definitions

// Calculate CRC-4 checksum using the x^4 + x + 1 polynomial
uint8_t crc4(const uint8_t *data, size_t len)
{
  static const uint8_t table[] = {
    0x0, 0x7, 0xe, 0x9, 0x5, 0x2, 0xb, 0xc, 0xa, 0xd, 0x4, 0x3, 0xf, 0x8, 0x1, 0x6
  };

  uint8_t crc = 0xa; // CRC value of the preamble 0x5A
  for (size_t i = 0; i < len; i++) {
    uint8_t shift = i % 2 == 0 ? 4 : 0; // high nibbles have even index
    uint8_t nibble = (data[i / 2] >> shift) & 0x0F;
    crc = table[crc ^ nibble];
  }
  return crc;
}

#if defined(SL_SIMPLE_COM_ROBUST_CRC) && SL_SIMPLE_COM_ROBUST_CRC == 1
// Calculate CRC-8 checksum using the x^8 + x^2 + x + 1 polynomial
static uint8_t crc8(const uint8_t *data, size_t len)
{
  uint32_t crc = 0; // initial value
  for (size_t i = 0; i < len; i++) {
    crc ^= data[i] << 8;
    for (size_t j = 8; j > 0; j--) {
      if (crc & 0x8000) {
        crc ^= (0x1070 << 3);
      }
      crc <<= 1;
    }
  }
  return (uint8_t)(crc >> 8);
}
#endif

// -----------------------------------------------------------------------------
// Public function definitions

// Pack data between preamble byte and (if turned on) CRC checksum
size_t sl_simple_com_robust_pack_data(uint8_t *packed_data_ptr,
                                      const uint8_t *data,
                                      uint16_t len)
{
  if (packed_data_ptr == NULL || data == NULL || len > MAX_PAYLOAD_LENGTH) {
    return 0;
  }
  size_t packed_data_size = sl_simple_com_robust_get_pack_buffer_size(len);

  // Building the 3 header bytes: preamble (1 byte),
  // Payload length (11 bits), CRC present flag (1 bit), header CRC-4 (4 bits)
  packed_data_ptr[0] = PREAMBLE_BYTE;
  // 2nd byte of the header contains the lower 8 bits of payload length
  packed_data_ptr[1] = (uint8_t)len;
  // Upper 3 bits of the 3rd byte of the header contains the higher 3 bits of payload length
  packed_data_ptr[2] = (uint8_t)((len >> 3) & PAYLOAD_LENGTH_MASK);
#if defined(SL_SIMPLE_COM_ROBUST_CRC) && SL_SIMPLE_COM_ROBUST_CRC == 1
  packed_data_ptr[2] |= CRC_PRESENT_FLAG;
#endif
  // Calculate CRC value for header, exclude preamble
  packed_data_ptr[2] |= crc4(packed_data_ptr + 1, 3);

  // Payload
  memcpy(&packed_data_ptr[SL_SIMPLE_COM_ROBUST_HEADER_SIZE], data, len);

  // CRC-8
#if defined(SL_SIMPLE_COM_ROBUST_CRC) && SL_SIMPLE_COM_ROBUST_CRC == 1
  packed_data_ptr[packed_data_size - 1] = crc8(data, len);
#endif
  return packed_data_size;
}

// Unpack packets from byte stream looking for valid headers
sl_simple_com_robust_result_t sl_simple_com_robust_unpack_data(uint8_t *data,
                                                               size_t len)
{
  sl_simple_com_robust_result_t result = {
    .status = SL_STATUS_FAIL,
    .payload = NULL,
    .payload_size = 0,
    .processed = 0
  };

  if (data == NULL) {
    result.status = SL_STATUS_NULL_POINTER;
    return result;
  }
  if (len <= SL_SIMPLE_COM_ROBUST_HEADER_SIZE) {
    result.status = SL_STATUS_EMPTY;
    return result;
  }

  // Find and validate the message header
  size_t margin = len - SL_SIMPLE_COM_ROBUST_HEADER_SIZE;
  while ((data[result.processed] != PREAMBLE_BYTE
          || crc4(data + result.processed + 1, 4) != 0)
         && result.processed < margin) {
    result.processed++;
  }
  // No valid frame found
  if (result.processed >= margin) {
    result.status = SL_STATUS_NOT_FOUND;
    return result;
  }

  // Shift input data to the beginning of the frame
  data += result.processed;
  len -= result.processed;

  // Check payload CRC flag
  bool crc_present = (data[2] & CRC_PRESENT_FLAG) != 0;

  // Get payload length from header (11 bits)
  result.payload_size = data[1] | ((data[2] & PAYLOAD_LENGTH_MASK) << 3);

  // Check if the incoming data contains the whole payload
  size_t message_size = SL_SIMPLE_COM_ROBUST_HEADER_SIZE + result.payload_size;
  if (crc_present) {
    message_size++;
  }

  if (len < message_size) {
    result.status = SL_STATUS_FAIL;
    return result;
  }

  result.processed += message_size;
  result.payload = data + SL_SIMPLE_COM_ROBUST_HEADER_SIZE;

  // If payload CRC is present, validate
#if defined(SL_SIMPLE_COM_ROBUST_CRC) && SL_SIMPLE_COM_ROBUST_CRC == 1
  if (crc_present) {
    if (crc8(result.payload, result.payload_size + 1) != 0) {
      result.status = SL_STATUS_FAIL;
      return result;
    }
  }
#endif // SL_SIMPLE_COM_ROBUST_CRC

  result.status = SL_STATUS_OK;
  return result;
}

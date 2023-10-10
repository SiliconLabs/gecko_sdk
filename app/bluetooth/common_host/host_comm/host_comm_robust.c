/***************************************************************************//**
 * @file
 * @brief Host layer for robust communication
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

#include <string.h>
#include "sl_simple_com_robust.h"
#include "host_comm.h"
#include "host_comm_robust.h"
#include "host_comm_config.h"

typedef struct {
  uint16_t len;
  uint8_t data[DEFAULT_HOST_BUFLEN];
} buf_t;

static buf_t buf_in_packed = { 0 };
static buf_t buf_in_unpacked = { 0 };
static buf_t buf_out = { 0 };

// Pack and write data to NCP.
int32_t host_comm_robust_tx(uint32_t len, const uint8_t *data)
{
  if (sl_simple_com_robust_get_pack_buffer_size(len) > DEFAULT_HOST_BUFLEN) {
    return -1;
  }

  buf_out.len = sl_simple_com_robust_pack_data(buf_out.data, data, (size_t)len);
  return host_comm_tx(buf_out.len, buf_out.data);
}

// Read data from NCP.
int32_t host_comm_robust_rx(uint32_t len, uint8_t *data)
{
  int32_t ret = -1;

  if (data == NULL) {
    return ret;
  }

  // Copy data from the unpacked buffer with the desired length.
  if (buf_in_unpacked.len >= len) {
    memcpy(data, buf_in_unpacked.data, len);
    buf_in_unpacked.len -= len;
    memmove(buf_in_unpacked.data,
            &buf_in_unpacked.data[len],
            buf_in_unpacked.len);
    ret = len;
  }

  return ret;
}

// Peek if readable data exists.
int32_t host_comm_robust_peek(void)
{
  int32_t raw_rx_len = host_comm_peek();

  // Copy new data from host_comm RX buffer to temporary buffer.
  if (raw_rx_len > 0) {
    // If full, circulate data
    if (buf_in_packed.len + raw_rx_len > DEFAULT_HOST_BUFLEN) {
      int32_t overflow = buf_in_packed.len + raw_rx_len - DEFAULT_HOST_BUFLEN;
      buf_in_packed.len -= overflow;
      memmove(buf_in_packed.data,
              &buf_in_packed.data[overflow],
              buf_in_packed.len);
    }

    int32_t ret = host_comm_rx(raw_rx_len,
                               (uint8_t *)&buf_in_packed.data[buf_in_packed.len]);
    if (ret > 0) {
      buf_in_packed.len += ret;
    }
  }

  // Unpack. If successful, move from packed buffer to unpacked buffer.
  if (buf_in_packed.len > 0) {
    sl_simple_com_robust_result_t result;
    int32_t unpack_rx_len = buf_in_packed.len;

    // Clamp incoming data length to maximum available space.
    // (Overestimating required space.)
    if (buf_in_unpacked.len + unpack_rx_len > DEFAULT_HOST_BUFLEN) {
      unpack_rx_len = DEFAULT_HOST_BUFLEN - buf_in_unpacked.len;
    }

    result = sl_simple_com_robust_unpack_data(buf_in_packed.data, unpack_rx_len);
    if (result.status == SL_STATUS_OK) {
      memcpy(&buf_in_unpacked.data[buf_in_unpacked.len],
             result.payload,
             result.payload_size);
      buf_in_unpacked.len += result.payload_size;

      buf_in_packed.len -= result.processed;
      memmove(buf_in_packed.data,
              &buf_in_packed.data[result.processed],
              buf_in_packed.len);
    }
  }

  // Return the length of the unpacked buffer.
  return (int32_t)buf_in_unpacked.len;
}

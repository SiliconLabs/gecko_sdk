/***************************************************************************//**
 * @file
 * @brief Robust Communication Interface
 * Packeting layer providing reliable communication with guaranteeing data
 * integrity. This module can be used to pack bytes between a header and a CRC
 * value and unpack and validate packets from a data stream.
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

#ifndef SL_SIMPLE_COM_ROBUST_H
#define SL_SIMPLE_COM_ROBUST_H

/***********************************************************************************************//**
 * @addtogroup simple_com
 * @{
 **************************************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include "sl_status.h"
#ifndef HOST_TOOLCHAIN
#include "sl_simple_com_config.h"
#else // HOST_TOOLCHAIN
#include "host_comm_config.h"
#endif // HOST_TOOLCHAIN

#define SL_SIMPLE_COM_ROBUST_HEADER_SIZE         3

// Get required buffer size for packed data
#if defined(SL_SIMPLE_COM_ROBUST_CRC) && SL_SIMPLE_COM_ROBUST_CRC == 1
#define sl_simple_com_robust_get_pack_buffer_size(len) (len + SL_SIMPLE_COM_ROBUST_HEADER_SIZE + 1)
#else // SL_SIMPLE_COM_ROBUST_CRC
#define sl_simple_com_robust_get_pack_buffer_size(len) (len + SL_SIMPLE_COM_ROBUST_HEADER_SIZE)
#endif // SL_SIMPLE_COM_ROBUST_CRC

typedef struct {
  sl_status_t status; // SL_STATUS_OK if a packet was found and validated with success
  uint8_t *payload; // Pointer to the beginning of the payload
  size_t payload_size; // Payload length in bytes
  size_t processed; // Number of bytes processed from the input buffer
} sl_simple_com_robust_result_t;

/**************************************************************************//**
 * Pack data between preamble byte and (if turned on) CRC checksum
 * This function adds a 3 byte header containing preamble byte, payload
 * length, CRC flag and CRC value to the header. If CRC is required an 8 bit
 * CRC value will be calculated for the payload and added to the end of packet.
 *
 * @param[out] packed_data_ptr pointer where the packed data should be loaded
 * @param[in] data pointer to the data to be packed
 * @param[in] len size of the data to be packed
 * @return the size of packed data
 *****************************************************************************/
size_t sl_simple_com_robust_pack_data(uint8_t *packed_data_ptr,
                                      const uint8_t *data,
                                      uint16_t len);

/**************************************************************************//**
 * Unpack packets from byte stream looking for valid headers.
 * This function searches valid headers and extracts payload after the header
 * into destination buffer. Header is validated by 4 bit header CRC and payload
 * can be also validated by optional CRC check.
 *
 * @param[in] data pointer to the data to be unpacked
 * @param[in] len size of the data to be unpacked
 * @return the result of the action
 *****************************************************************************/
sl_simple_com_robust_result_t sl_simple_com_robust_unpack_data(uint8_t *data,
                                                               size_t len);

/** @} (end addtogroup simple_com) */
#endif // SL_SIMPLE_COM_ROBUST_H

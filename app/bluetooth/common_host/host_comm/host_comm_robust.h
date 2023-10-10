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

#ifndef HOST_COMM_ROBUST_H
#define HOST_COMM_ROBUST_H

/**************************************************************************//**
 * Pack and write data to NCP.
 *
 * @param[in] len Number of bytes to write.
 * @param[in] data Data to write.
 *
 * @return Number of written bytes, -1 on error.
 *****************************************************************************/
int32_t host_comm_robust_tx(uint32_t len, const uint8_t *data);

/**************************************************************************//**
 * Read data from NCP.
 *
 * @param[in] len Number of bytes to read.
 * @param[in] data Read data.
 *
 * @return Number of bytes read, -1 on error.
 *****************************************************************************/
int32_t host_comm_robust_rx(uint32_t len, uint8_t *data);

/**************************************************************************//**
 * Peek if readable data exists.
 *
 * @return Number of bytes on the buffer, -1 on error.
 *****************************************************************************/
int32_t host_comm_robust_peek(void);

#endif // HOST_COMM_ROBUST_H

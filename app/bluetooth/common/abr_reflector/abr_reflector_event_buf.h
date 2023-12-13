/***************************************************************************//**
 * @file
 * @brief ABR reflector CS event buffer manager
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

#ifndef ABR_REFLECTOR_EVENT_BUF_H
#define ABR_REFLECTOR_EVENT_BUF_H

#include "sl_common.h"
#include "sl_bt_api.h"

#define CS_EVENT_BUF_DATA_MAX_LEN 256

typedef struct {
  uint8_t data[CS_EVENT_BUF_DATA_MAX_LEN];  // Array for storing the raw CS result data
  uint8_t data_len;                         // Length of the raw CS result data
  uint16_t procedure_index;                 // Procedure index of the CS measurement data
  uint16_t subevent_index;                  // Subevent index of the CS measurement data
  bool empty;                               // Show whether it's an occupied ot free slot which can be overwritten
  bool indication_sent;                     // Shows whether we sent an indication to the initiator about this result
  uint8_t conn_handle;                      // Handle of the connection which initiated the CS procedure
} cs_event_data_t;

/**************************************************************************//**
 * Clear all data from the CS event buffer.
 *****************************************************************************/
void abr_cs_event_buf_clear(void);

/**************************************************************************//**
 * Tell the number of free slots available in the CS event buffer.
 *
 * @return the number of free slots available in the CS event buffer
 *****************************************************************************/
uint32_t abr_cs_event_buf_get_free_space(void);

/**************************************************************************//**
 * Purge any data from the CS event buffer associated with a connection.
 * Useful when an initiator disconnects and we don't want any
 * leftover measurement data in the buffer.
 *
 * @param[in] conn_handle the connection handle to erase all data for
 *****************************************************************************/
void abr_cs_event_buf_purge_data(const uint8_t conn_handle);

/**************************************************************************//**
 * Find a pointer to a buffer element which is free to write,
 * yields NULL if no writable elements are available.
 *
 * @return pointer to a free buffer element, NULL if none available
 *****************************************************************************/
cs_event_data_t *abr_cs_event_buf_get_element_for_write(void);

/**************************************************************************//**
 * Provide a pointer to the next available data for a given connection,
 * yields NULL if no next data is available.
 *
 * @param[in] conn_handle the connection handle for which the data is requested
 *
 * @return pointer to the next available data, NULL if none available
 *****************************************************************************/
cs_event_data_t *abr_cs_event_buf_get_next_element(const uint8_t conn_handle);

/**************************************************************************//**
 * Find and return an exact result from the CS event buffer.
 *
 * @param[in] conn_handle the connection handle for which the data is requested
 * @param[in] procedure_index procedure index of requested the result
 * @param[in] subevent_index subevent index of requested the result
 *
 * @return pointer to the result if available, NULL if not found
 *****************************************************************************/
cs_event_data_t *abr_cs_event_buf_find(const uint8_t conn_handle,
                                       const uint16_t procedure_index,
                                       const uint16_t subevent_index);

/**************************************************************************//**
 * Find a pointer to the next available data which we haven't sent
 * an indication about for a given connection.
 *
 * @param[in] conn_handle the connection handle for which the data is requested
 *
 * @return pointer to the result if available, NULL if none available
 *****************************************************************************/
cs_event_data_t *abr_cs_event_buf_get_next_unindicated(const uint8_t conn_handle);

#endif // ABR_REFLECTOR_EVENT_BUF_H

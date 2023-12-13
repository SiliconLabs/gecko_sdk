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

#include "abr_reflector_event_buf.h"
#include "abr_reflector_config.h"

static cs_event_data_t cs_event_buffer[ABR_REFLECTOR_CS_EVENT_BUF_SIZE];

// Returns the first free and writable index in the CS event buffer
static bool abr_cs_event_buf_get_write_idx(uint32_t *const wr_idx);

void abr_cs_event_buf_clear(void)
{
  for (uint32_t i = 0u; i < ABR_REFLECTOR_CS_EVENT_BUF_SIZE; i++) {
    cs_event_buffer[i].empty = true;
  }
}

static bool abr_cs_event_buf_get_write_idx(uint32_t *const wr_idx)
{
  if (wr_idx == NULL) {
    return false;
  }
  for (uint32_t i = 0u; i < ABR_REFLECTOR_CS_EVENT_BUF_SIZE; i++) {
    if (cs_event_buffer[i].empty) {
      *wr_idx = i;
      return true;
    }
  }
  return false;
}

uint32_t abr_cs_event_buf_get_free_space(void)
{
  uint32_t free_space = 0u;
  for (uint32_t i = 0u; i < ABR_REFLECTOR_CS_EVENT_BUF_SIZE; i++) {
    if (cs_event_buffer[i].empty) {
      free_space++;
    }
  }
  return free_space;
}

void abr_cs_event_buf_purge_data(const uint8_t conn_handle)
{
  for (uint32_t i = 0u; i < ABR_REFLECTOR_CS_EVENT_BUF_SIZE; i++) {
    if (cs_event_buffer[i].conn_handle == conn_handle) {
      cs_event_buffer[i].empty = true;
    }
  }
}

cs_event_data_t *abr_cs_event_buf_get_element_for_write(void)
{
  uint32_t wr_idx;
  if (!abr_cs_event_buf_get_write_idx(&wr_idx)) {
    return NULL;
  }
  return &cs_event_buffer[wr_idx];
}

cs_event_data_t *abr_cs_event_buf_get_next_element(const uint8_t conn_handle)
{
  for (uint32_t i = 0u; i < ABR_REFLECTOR_CS_EVENT_BUF_SIZE; i++) {
    if (!cs_event_buffer[i].empty && cs_event_buffer[i].conn_handle == conn_handle) {
      return &cs_event_buffer[i];
    }
  }
  return NULL;
}

cs_event_data_t *abr_cs_event_buf_find(const uint8_t conn_handle,
                                       const uint16_t procedure_index,
                                       const uint16_t subevent_index)
{
  for (uint32_t i = 0u; i < ABR_REFLECTOR_CS_EVENT_BUF_SIZE; i++) {
    if (!cs_event_buffer[i].empty
        && cs_event_buffer[i].procedure_index == procedure_index
        && cs_event_buffer[i].subevent_index == subevent_index
        && cs_event_buffer[i].conn_handle == conn_handle) {
      return &cs_event_buffer[i];
    }
  }
  return NULL;
}

cs_event_data_t *abr_cs_event_buf_get_next_unindicated(const uint8_t conn_handle)
{
  for (uint32_t i = 0u; i < ABR_REFLECTOR_CS_EVENT_BUF_SIZE; i++) {
    // If the current event is not empty & the connection handle matches & indication has not been sent yet
    if (!cs_event_buffer[i].empty
        && cs_event_buffer[i].conn_handle == conn_handle
        && !cs_event_buffer[i].indication_sent) {
      return &cs_event_buffer[i];
    }
  }
  return NULL;
}

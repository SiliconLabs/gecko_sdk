/***************************************************************************//**
 * @file
 * @brief ESL Tag response implementation
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdint.h>
#include "esl_tag_log.h"
#include "esl_tag_core.h"
#include "circular_queue.h"
#include "esl_tag_response.h"

static Queue_t esl_response_queue;
static bool esl_core_on_response_queue_overflow(const Queue_t *queue,
                                                void *data)
{
  (void)queue;
  (void)data;
  // The event queue is overflowing but we don't allow overwriting the oldest
  // entry in the buffer. Rather, we're going just to drop the new response
  // since it doesn't fit
  return false; // disallow the overwrite
}

void esl_core_respones_init()
{
  // Initialize the queue for ESL responses
  bool init_result = queueInit(&esl_response_queue, ESL_PAYLOAD_MAX_LENGTH);

  (void)init_result;  // remove the compiler warning if asserts are disabled
  // ESL responses queue init failed! Circular queue max length must be >= 48!
  sl_bt_esl_assert(init_result);

  queueOverflow(&esl_response_queue, &esl_core_on_response_queue_overflow);
}

sl_status_t esl_core_build_response(tlv_t tlv, const void *input_data)
{
  sl_status_t   result = SL_STATUS_WOULD_OVERFLOW;
  uint8_t       length = esl_core_get_tlv_len(tlv);
  const uint8_t *data  = (uint8_t *)input_data;

  if (esl_response_queue.size - esl_response_queue.count > length) {
    queueAdd(&esl_response_queue, (void *)(uint32_t)tlv);

    while (length--) {
      queueAdd(&esl_response_queue, (void *)(uint32_t)(*data++));
    }

    result = SL_STATUS_OK;
  } else {
    esl_core_set_last_error(ESL_ERROR_CAPACITY_LIMIT);
  }

  return result;
}

uint8_t esl_core_get_responses(uint8_t remaining_length, uint8_t *buf_p)
{
  uint8_t length = 0;
  // Invalid function invocation!
  sl_bt_esl_assert(buf_p != NULL);

  while (!queueIsEmpty(&esl_response_queue)) {
    tlv_t   next_tlv = (tlv_t)(uint32_t)queuePeek(&esl_response_queue);
    uint8_t data_len = esl_core_get_tlv_len(next_tlv) + 1;
    // only allow getting responses with full integrity, get them all possible
    if (data_len <= remaining_length) {
      remaining_length -= data_len;
      while (data_len--) {
        *buf_p++ = (uint8_t)(uint32_t)queueRemove(&esl_response_queue);
        ++length;
      }
    } else {
      break;
    }
  }

  return length;
}

/**************************************************************************//**
 * Purge all ESL Tag responses from the queue (if any).
 *****************************************************************************/
void esl_core_purge_responses()
{
  esl_core_set_last_error(ESL_ERROR_VENDOR_NOERROR);
  queueInit(&esl_response_queue, ESL_PAYLOAD_MAX_LENGTH);
}

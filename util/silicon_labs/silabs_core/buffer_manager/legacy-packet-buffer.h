/***************************************************************************//**
 * @file
 * @brief legacy packet buffer support
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef LEGACY_PACKET_BUFFER_H
#define LEGACY_PACKET_BUFFER_H

#include "sl_status.h"

uint8_t *emberGetLinkedBuffersPointer(Buffer buffer, uint8_t index);

sl_status_t emberReallyAppendToLinkedBuffers(EmberMessageBuffer *buffer,
                                             uint8_t *contents,
                                             uint8_t length,
                                             bool reallyAppend);
sl_status_t emberReallySetLinkedBuffersLength(Buffer *buffer,
                                              uint8_t newLength);

uint8_t emberGetLinkedBuffersByte(Buffer buffer, uint8_t index);
void emberSetLinkedBuffersByte(Buffer buffer, uint8_t index, uint8_t byte);

Buffer emberCopyLinkedBuffers(Buffer buffer);
void emberCopyBufferBytes(Buffer to,
                          uint16_t toIndex,
                          Buffer from,
                          uint16_t fromIndex,
                          uint16_t count);

uint16_t emberGetLinkedBuffersLowHighInt16u(Buffer buffer,
                                            uint8_t index);
void emberSetLinkedBuffersLowHighInt16u(Buffer buffer,
                                        uint8_t index,
                                        uint16_t value);
uint32_t emberGetLinkedBuffersLowHighInt32u(EmberMessageBuffer buffer,
                                            uint8_t index);
void emberSetLinkedBuffersLowHighInt32u(EmberMessageBuffer buffer,
                                        uint8_t index,
                                        uint32_t value);

EmberMessageBuffer
emberFillStackBuffer(unsigned int count, ...);

#define emberLinkedBufferContents(buffer) emberMessageBufferContents(buffer)

#define emberReleaseMessageBuffer(buffer) do {} while (0);
#define emberHoldMessageBuffer(buffer) do {} while (0);

#define emberAppendToLinkedBuffers(buffer, contents, length) \
  emberReallyAppendToLinkedBuffers(&(buffer), (contents), (length), true)

#define emberExtendLinkedBuffer(buffer, length) \
  emberReallyAppendToLinkedBuffers(&(buffer), NULL, (length), false)

#define emberSetLinkedBuffersLength(buffer, newlength) \
  emberReallySetLinkedBuffersLength(&(buffer), newlength)

#define emberSetMessageBufferLength emberSetLinkedBuffersLength

//----------------------------------------------------------------
// Macros for the MessageBuffer interface.

#define emberMessageBufferContents sli_legacy_buffer_manager_get_buffer_pointer
#define emberMessageBufferLength sli_legacy_buffer_manager_get_buffer_length

#define sli_legacy_packet_buffer_packet_header_payload(header) sli_legacy_buffer_manager_get_payload_link(header)

#define sli_legacy_packet_buffer_set_packet_header_payload(header, payload) \
  sli_legacy_buffer_manager_set_payload_link((header), (payload))

#define emberFillLinkedBuffers(contents, length) \
  sli_legacy_buffer_manager_really_fill_buffer((contents), (length), false)

 #define emberFillLinkedAsyncBuffers(contents, length) \
  sli_legacy_buffer_manager_really_fill_buffer((contents), (length), true)

#define sli_legacy_packet_buffer_queue_add sli_legacy_buffer_manager_buffer_queue_add
#define sli_legacy_packet_buffer_queue_remove_head sli_legacy_buffer_manager_buffer_queue_remove_head
#define sli_legacy_packet_buffer_queue_remove sli_legacy_buffer_manager_buffer_queue_remove
#define sli_legacy_packet_buffer_queue_is_empty sli_legacy_buffer_manager_buffer_queue_is_empty

#undef EMBER_NULL_MESSAGE_BUFFER
#define EMBER_NULL_MESSAGE_BUFFER NULL_BUFFER

#define emberCopyFromLinkedBuffers(buffer, startIndex, contents, length) \
  sli_legacy_packet_buffer_really_copy_to_linked_buffers((const uint8_t *) (contents), (buffer), (startIndex), (length), 0)

#define emberCopyToLinkedBuffers(contents, buffer, startIndex, length) \
  sli_legacy_packet_buffer_really_copy_to_linked_buffers((const uint8_t *) (contents), (buffer), (startIndex), (length), 1)

#define sli_legacy_buffer_manager_copy_from_linked_buffers(contents, buffer, length) \
  sli_legacy_packet_buffer_really_copy_to_linked_buffers((const uint8_t *) (contents), (buffer), (0), (length), 0)

#define emberAllocateStackBuffer() \
  sli_legacy_buffer_manager_really_allocate_buffer(0, false)

#define PACKET_BUFFER_SIZE 32

#endif // LEGACY_PACKET_BUFFER_H

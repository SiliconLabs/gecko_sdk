/***************************************************************************//**
 * @file
 * @brief queues of buffers
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

#ifndef BUFFER_QUEUE_H
#define BUFFER_QUEUE_H

bool sli_legacy_buffer_manager_buffer_queue_is_empty(Buffer *queue);
Buffer sli_legacy_buffer_manager_generic_queue_head(Buffer *queue, uint16_t i);
#define sli_legacy_buffer_manager_buffer_queue_head(queue) (sli_legacy_buffer_manager_generic_queue_head((queue), QUEUE_LINK))
#define sli_legacy_buffer_manager_payload_queue_head(queue) (sli_legacy_buffer_manager_generic_queue_head((queue), PAYLOAD_LINK))

void sli_legacy_buffer_manager_generic_queue_add(Buffer *queue, Buffer newTail, uint16_t i);
#define sli_legacy_buffer_manager_buffer_queue_add(queue, newTail) \
  (sli_legacy_buffer_manager_generic_queue_add((queue), (newTail), QUEUE_LINK))
#define sli_legacy_buffer_manager_payload_queue_add(queue, newTail) \
  (sli_legacy_buffer_manager_generic_queue_add((queue), (newTail), PAYLOAD_LINK))

void sli_legacy_buffer_manager_buffer_queue_pre_insert_buffer(Buffer *queue, Buffer bufferToInsert, Buffer bufferToInsertBefore);

// Add as the head, not the tail.
void sli_legacy_buffer_manager_buffer_queue_addToHead(Buffer *queue, Buffer newHead);

Buffer sli_legacy_buffer_manager_generic_queue_removeHead(Buffer *queue, uint16_t i);
#define sli_legacy_buffer_manager_buffer_queue_remove_head(queue) \
  (sli_legacy_buffer_manager_generic_queue_removeHead((queue), QUEUE_LINK))
#define sli_legacy_buffer_manager_payload_queue_remove_head(queue) \
  (sli_legacy_buffer_manager_generic_queue_removeHead((queue), PAYLOAD_LINK))

uint16_t sli_legacy_buffer_manager_generic_queue_remove(Buffer *queue, Buffer buffer, uint16_t i);
#define sli_legacy_buffer_manager_buffer_queue_remove(queue, buffer) \
  (sli_legacy_buffer_manager_generic_queue_remove((queue), (buffer), QUEUE_LINK))

// The number of buffers in the queue, not the number of bytes.
uint16_t sli_legacy_buffer_manager_buffer_queue_length(Buffer *queue);

// Doubled up with sli_legacy_buffer_manager_buffer_queue_remove() to save flash.
#define sli_legacy_buffer_manager_buffer_queue_byte_length(queueIndex) \
  (sli_legacy_buffer_manager_generic_queue_remove((queueIndex), NULL_BUFFER, QUEUE_LINK))
#define sli_legacy_buffer_manager_payload_queue_byte_length(queueIndex) \
  (sli_legacy_buffer_manager_generic_queue_remove((queueIndex), NULL_BUFFER, PAYLOAD_LINK))

// How to walk down a queue:
//   Buffer finger = sli_legacy_buffer_manager_buffer_queue_head(queue);
//   while (finger != NULL_BUFFER) {
//     ...
//     finger = sli_legacy_buffer_manager_buffer_queue_next(queue, finger);
//   }
//
// To remove one or more elements while walking a queue, put all the
// buffers on temporary queue and then move the live values back to the
// original:
//
//  Buffer temp = queue;
//  queue = NULL_BUFFER;
//  while (! sli_legacy_buffer_manager_buffer_queue_is_empty(&temp)) {
//    Buffer next = sli_legacy_buffer_manager_buffer_queue_remove_head(&temp);
//    if (isLive next) {
//      sli_legacy_buffer_manager_buffer_queue_add(&queue, next);
//    }
//  }

Buffer sli_legacy_buffer_manager_buffer_queue_next(Buffer *queue, Buffer finger);

// Remove the first 'count' bytes from the queue of buffers, truncating
// the final head if necessary;

uint16_t sli_legacy_buffer_manager_remove_bytes_from_generic_queue(Buffer *queue, uint16_t count, uint16_t i);
#define sli_legacy_buffer_manager_remove_bytes_from_buffer_queue(queue, count) \
  (sli_legacy_buffer_manager_remove_bytes_from_generic_queue((queue), (count), QUEUE_LINK))
#define sli_legacy_buffer_manager_remove_bytes_from_payload_queue(queue, count) \
  (sli_legacy_buffer_manager_remove_bytes_from_generic_queue((queue), (count), PAYLOAD_LINK))

void sli_legacy_buffer_manager_copy_from_generic_queue(Buffer *queue, uint16_t count, uint8_t *to, uint16_t i);
#define sli_legacy_buffer_manager_copy_from_buffer_queue(queue, count, to) \
  (sli_legacy_buffer_manager_copy_from_generic_queue((queue), (count), (to), QUEUE_LINK))
#define sli_legacy_buffer_manager_copy_from_payload_queue(queue, count, to) \
  (sli_legacy_buffer_manager_copy_from_generic_queue((queue), (count), (to), PAYLOAD_LINK))

// Converting back and forth between linked payloads and queues.
void sli_legacy_buffer_manager_linked_payload_to_payload_queue(Buffer *queue);
void sli_legacy_buffer_manager_payload_queue_to_linked_payload(Buffer *queue);

//----------------------------------------------------------------
// Experimental utilities to use a queue of buffers as an extensible
// vector (a one-dimensional array).

typedef struct {
  Buffer values;        // initialize this to NULL_BUFFER
  uint16_t valueSize;     // sizeof(whateverGoesInTheVector)
  uint16_t valueCount;    // initialize to zero
  uint16_t emptyCount;    // initialize to zero
} Vector;

typedef bool (*EqualityPredicate)(const void *x, const void *y);

// Returns the first element in the vector for which
// predicate(element, target) returns true.  If indexLoc is non-NULL
// the index of the element is stored there.
void *emVectorSearch(Vector *vector,
                     EqualityPredicate predicate,
                     const void *target,
                     uint16_t *indexLoc);

// Return the 'index'th element of the vector.
void *emVectorRef(Vector *vector, uint16_t index);

// Add space for 'quanta' more elements to the vector.
void *emVectorAdd(Vector *vector, uint16_t quanta);

// Returns the index of 'value' in 'vector', or -1 if it isn't there.
// This is intended for use in debugging.
uint16_t sli_legacy_buffer_manager_vector_find_index(Vector *vector, const uint8_t *value);

// Returns the number of elements that match predicate(element, target)
uint16_t sli_legacy_buffer_manager_vector_match_count(Vector *vector,
                                                      EqualityPredicate predicate,
                                                      const void *target);

#endif // BUFFER_QUEUE_H

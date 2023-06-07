/***************************************************************************//**
 * @file
 * @brief Buffer allocation and management routines.
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

/**
 * @addtogroup packet_buffer
 * These buffers are contiguous blocks of bytes.  Buffers are allocated
 * linearly from a single chunk of memory.  When space gets short any
 * buffers still in use can be moved to the beginning of buffer memory,
 * which consolidates any unused space.
 *
 * 'Buffer' values are actually offsets from the beginning of buffer
 * memory.  Using uint8_ts would require additional memory for the
 * mapping between the uint8_ts and memory locations.
 *
 * In fact, Buffers are offsets from one before the beginning of buffer
 * memory.  The first buffer is thus 0x0001.  This allows us to use 0x0000
 * as the null buffer, just as C uses zero for the null pointer.
 *
 * In general the buffer functions are not safe for use in ISRs.
 * The one exception is the PHY->MAC queue, which is handled specially.
 * It is safe for an ISR to allocate a new buffer and put it on the
 * PHY->MAC queue.
 *
 * Any code which holds on to buffers beyond the context in which they
 * are allocated must provide a marking function to prevent them from
 * being garbage collected.  See sli_legacy_buffer_manager_reclaim_unused_buffers for details.
 * @{
 */

#ifndef __BUFFER_MANAGEMENT_H__
#define __BUFFER_MANAGEMENT_H__

typedef uint16_t Buffer;
#define NULL_BUFFER 0x0000u

typedef Buffer MessageBufferQueue;
typedef Buffer PacketHeader;
typedef Buffer EmberMessageBuffer;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
/** @brief Allocates a buffer
 *
 */
Buffer sli_legacy_buffer_manager_allocate_buffer(uint16_t dataSizeInBytes);
#else
Buffer sli_legacy_buffer_manager_really_allocate_buffer(uint16_t dataSizeInBytes, bool async);

#define sli_legacy_buffer_manager_allocate_buffer(dataSizeInBytes) \
  sli_legacy_buffer_manager_really_allocate_buffer(dataSizeInBytes, false)
#endif

/** @brief gets a pointer to the specified buffer
 *
 */
uint8_t* sli_legacy_buffer_manager_get_buffer_pointer(Buffer buffer);

/** @brief gets the length of the specified buffer
 *
 */
uint16_t sli_legacy_buffer_manager_get_buffer_length(Buffer buffer);

/** @brief allocates a buffer and fills it with the given null terminated string
 *
 * 'contents' may be NULL, in which case NULL_BUFFER is returned.
 */
Buffer sli_legacy_buffer_manager_fill_string_buffer(const uint8_t *contents);

#ifdef DOXYGEN_SHOULD_SKIP_THIS
/** @brief Allocates a buffer and fills with length bytes of contents
 *
 */
Buffer sli_legacy_buffer_manager_fill_buffer(const uint8_t *contents, uint16_t length);
#else
#define sli_legacy_buffer_manager_fill_buffer(contents, length) \
  sli_legacy_buffer_manager_really_fill_buffer(contents, length, false)

Buffer sli_legacy_buffer_manager_really_fill_buffer(const uint8_t *contents, uint16_t length, bool async);
#endif

/** @brief returns the number of bytes of buffer space currently in use
 *
 */
uint16_t sli_legacy_buffer_manager_buffer_bytes_used(void);
/** @brief returns the number of available bytes remaining in the buffer system
 *
 */
uint16_t sli_legacy_buffer_manager_buffer_bytes_remaining(void);
/** @brief returns the number of bytes allocated to the buffer system
 *
 */
uint16_t sli_legacy_buffer_manager_buffer_bytes_total(void);

// Every buffer has two links to other buffers.  For packets, these
// are used to organize buffers into queues and to associate header
// and payload buffers.

#ifndef DOXYGEN_SHOULD_SKIP_THIS
Buffer sli_legacy_buffer_manager_get_buffer_link(Buffer buffer, uint8_t i);
void sli_legacy_buffer_manager_set_buffer_link(Buffer buffer, uint8_t i, Buffer newLink);

#define QUEUE_LINK   0
#define PAYLOAD_LINK 1

#define sli_legacy_buffer_manager_get_queue_link(buffer)   (sli_legacy_buffer_manager_get_buffer_link((buffer), QUEUE_LINK))
#define sli_legacy_buffer_manager_get_payload_link(buffer) (sli_legacy_buffer_manager_get_buffer_link((buffer), PAYLOAD_LINK))

#define sli_legacy_buffer_manager_set_queue_link(buffer, new) \
  (sli_legacy_buffer_manager_set_buffer_link((buffer), QUEUE_LINK, (new)))
#define sli_legacy_buffer_manager_set_payload_link(buffer, new) \
  (sli_legacy_buffer_manager_set_buffer_link((buffer), PAYLOAD_LINK, (new)))

// Bookkeeping.
void sli_legacy_buffer_manager_initialize_buffers(void);
bool sli_legacy_buffer_manager_points_into_heap(void *pointer);

uint16_t sli_legacy_buffer_manager_get_traced_bytes(void);
#endif

/** @brief returns whether the given buffer is valid
 *
 */
bool sli_legacy_buffer_manager_is_valid_buffer(Buffer buffer);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Buffer space can be reserved to prevent it from being allocated
// asynchronously (typically by the radio receive ISR).  Reserving
// buffer space splits the available memory into two parts, with
// synchronous allocation getting the reserved amount and asynchronous
// allocation getting anything left over.  Neither is allowed to
// overrun its allotment.
//
// Reserving an insufficient amount of memory is a bug.  An assert
// fires if memory has been reserved and a synchronous allocation asks
// for more memory than is available in the reserved portion.
//
// NULL_BUFFER is returned if an asynchronous allocation cannot be
// satisified or if there is no reservation in place and a synchronous
// allocation cannot be satisfied.

#define sli_legacy_buffer_manager_allocate_async_buffer(dataSizeInBytes) \
  sli_legacy_buffer_manager_really_allocate_buffer(dataSizeInBytes, true)

Buffer sli_legacy_buffer_manager_allocate_indirect_buffer(uint8_t *contents,
                                                          void    *freePtr,
                                                          uint16_t length);

bool sli_legacy_buffer_manager_set_reserved_buffer_space(uint16_t dataSizeInBytes);
void sli_legacy_buffer_manager_end_buffer_space_reservation(void);
#endif

//----------------------------------------------------------------

/** @brief Truncates the buffer.  New length cannot be longer than the old length.
 *
 */
void sli_legacy_buffer_manager_set_buffer_length(Buffer buffer, uint16_t length);

/** @brief Truncates the buffer, removing bytes from the front.  New length cannot be longer than the old length.
 *
 */
void sli_legacy_buffer_manager_set_buffer_length_from_end(Buffer buffer, uint16_t length);

typedef void (*Marker)(Buffer *buffer);
typedef void (*BufferMarker)(void);

/** @brief Reclaims unused buffers and compacts the heap
 *
 * Reclaims all buffers not reachable from 'roots', the PHY->MAC
 * queue, by one of marker functions.  The marker functions should
 * call their argument on all known buffer references.
 *
 * The idea is that single top level references, such as a queue,
 * can be put in 'roots', whereas buffers stored in data structures,
 * such as the retry table, are handled by marker functions.
 *
 * Surviving buffers moved to the beginning of the heap, which
 * amalgamates the free memory into a single contiguous block.  This
 * should only be called when there are no references to buffers outside
 * of 'roots', the PHY->MAC queue, and the locations passed to
 * the marker functions.
 *
 * IMPORTANT: BufferMarker routines should not reference buffers after
 * they have been marked.  The buffers may be in an inconsistent state
 * until the reclaimation has completed.

 *
 * Right:
 *   void myBufferMarker(void)
 *   {
 *     ... myBuffer ...
 *     sli_legacy_buffer_manager_mark_buffer(&myBuffer);
 *   }
 *
 * Wrong:
 *   void myBufferMarker(void)
 *   {
 *     sli_legacy_buffer_manager_mark_buffer(&myBuffer);
 *     ... myBuffer ...
 *   }
 *
 */
void sli_legacy_buffer_manager_reclaim_unused_buffers(const BufferMarker *markers);

/** @brief Marks the passed buffer.  Called from Marker function
 */
void sli_legacy_buffer_manager_mark_buffer(Buffer *root);

/** @brief weakly mark buffer
 *
 * sli_legacy_buffer_manager_mark_buffer_weak only operates during the update references phase
 * if emMark Buffer is called on the same buffer elsewhere, the weak
 * reference will be updated.  If a buffer is only weakly marked, the
 * update phase will replace it with NULL_BUFFER
 */
void sli_legacy_buffer_manager_mark_buffer_weak(Buffer *root);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
bool sli_legacy_buffer_manager_mark_amalgamate_queue(Buffer *queue);

void sli_legacy_buffer_manager_reclaim_unused_buffers_and_amalgamate(const BufferMarker *markers,
                                                                   uint8_t* scratchpad,
                                                                   uint16_t scratchpadSize);

void sli_legacy_buffer_manager_print_buffers(uint8_t port, const BufferMarker *markers);

// A utility for marking a buffer via a pointer to its contents.
void sli_legacy_buffer_manager_mark_buffer_pointer(void **pointerLoc);
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Only used by flex
/** Applications that use buffers must mark them by defining this function.
 * The stack uses this when reclaiming unused buffers.
 */
void emberMarkApplicationBuffersHandler(void);
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
uint16_t sli_legacy_buffer_manager_buffer_chain_byte_length(Buffer buffer, uint8_t link);
#define sli_legacy_buffer_manager_total_payload_length(buffer) \
  (sli_legacy_buffer_manager_buffer_chain_byte_length((buffer), 1))
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// The PHY->MAC queue is special in that it can be added to in ISR context.
void sli_802154phy_phy_to_mac_queue_add(Buffer newTail);
Buffer sli_802154phy_phy_to_mac_queue_remove_head(void);
bool sli_802154phy_phy_to_mac_queue_is_empty(void);
void sli_legacy_buffer_manager_empty_phy_to_mac_queue(void);

void sli_legacy_buffer_manager_multi_phy_to_mac_queue_add(uint8_t mac_index, Buffer newTail);
Buffer sli_legacy_buffer_manager_multi_phy_to_mac_queue_remove_head(uint8_t mac_index);
bool sli_legacy_buffer_manager_multi_phy_to_mac_queue_is_empty(uint8_t mac_index);
void sli_legacy_buffer_manager_multi_empty_phy_to_mac_queue(uint8_t mac_index);

// Allow the wakeup code to save and restore the heap pointer.  This is
// much faster than sli_legacy_buffer_manager_reclaim_unused_buffers() but requires that the caller
// knows that there are no references anywhere to newly allocated buffers.
uint16_t sli_legacy_buffer_manager_save_heap_state(void);
void sli_legacy_buffer_manager_restore_heap_state(uint16_t state);

// This handler is called when freeing memory allocated with
// emberAllocateMemoryForPacketHandler(). You will be passed the reference that was
// supplied when allocating the memory. If you passed NULL as the objectRef
// value then this callback is not called.
void emberFreeMemoryForPacketHandler(void *objectRef);

// This function can be used to hook an external memory allocator into the
// stack. It will be called when we need to allocate large packets. If a value
// other than NULL is returned that pointer will be used to store packet data.
// You must also fill in the objectRef parameter with whatever reference you
// would like passed to the emberFreeMemoryForPacketHandler() when we're done
// with this memory. If you set the objectRef to NULL then the free handler will
// not be called.
void *emberAllocateMemoryForPacketHandler(uint32_t size, void **objectRef);

// This function can be used to get the object reference for a buffer allocated
// using one of the callbacks above. If you did not specify an object reference
// or this is a regular ember buffer then NULL will be returned.
void* emberGetObjectRefFromBuffer(Buffer b);

//----------------------------------------------------------------
// Utilities used by buffer-malloc.c

Buffer sli_legacy_buffer_manager_buffer_pointer_to_buffer(uint16_t *bufferPointer);
Buffer sli_legacy_buffer_manager_following_buffer(Buffer buffer);
void sli_legacy_buffer_manager_merge_buffers(Buffer first, Buffer second);
Buffer sli_legacy_buffer_manager_split_buffer(Buffer buffer, uint16_t newLength);

// Prototypes for the MessageBuffer interface
void sli_legacy_packet_buffer_really_copy_to_linked_buffers(const uint8_t *contents,
                                                            Buffer buffer,
                                                            uint8_t startIndex,
                                                            uint8_t length,
                                                            uint8_t direction);

#define bufferUse(tag)    do { sli_legacy_buffer_manager_buffer_usage(tag); } while (0)
#define endBufferUse(tag) do { sli_legacy_buffer_manager_end_buffer_usage(); } while (0)
void sli_legacy_buffer_manager_buffer_usage(const char *tag);
void sli_legacy_buffer_manager_end_buffer_usage(void);

//----------------------------------------------------------------
// The heap is allocated elsewhere.

extern uint16_t heapMemory[];
extern const uint32_t heapMemorySize;

// This is a no-op on real hardware.  It only has an effect in simulation.
void sli_legacy_buffer_manager_resize_heap(uint32_t newSize);
#endif //DOXYGEN_SHOULD_SKIP_THIS

/** @} END addtogroup */

#endif

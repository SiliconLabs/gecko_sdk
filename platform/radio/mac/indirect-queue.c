/***************************************************************************//**
 * @file indirect-queue.c
 *
 * @brief Manages the pool of indirect messages. These messages cannot be
 *  transmitted until after we receive a poll message from the destination. There
 *  are 3 types of indirect messages:
 *     * Queued headers addressed to short destination addresses.
 *     * Queued headers addressed to long destination addresses.
 *     * Just-in-time (JIT) messages.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include PLATFORM_HEADER
#ifdef UNIFIED_MAC_SCRIPTED_TEST
#define EVENT_CONTROL_SYSTEM
#endif
#include "hal/hal.h"
#include "event_control/event.h"
#include "core/ember-stack.h"
#include "buffer_manager/buffer-management.h"
#include "buffer_manager/buffer-queue.h"
#include "mac-types.h"
#include "lower-mac.h"
#include "upper-mac.h"
#include "mac-header.h"
#include "mac-command.h"
#include "mac-child.h"
#include "indirect-queue.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
#include "lower-mac-spinel.h"
#endif

#ifdef EMBER_TEST
  #define EMBER_TEST_ASSERT(n) assert(n)
#else
  #define EMBER_TEST_ASSERT(n)
#endif

//----------------------------------------------------------------
#define LONG_INDIRECT_POOL_SIZE 5
#define INDIRECT_TRANSMIT_TRIES 3

//----------------------------------------------------------------
#ifndef EVENT_CONTROL_SYSTEM
static void mac_indirect_event_handler(EmberEvent *event);

EmberEvent sl_mac_indirect_event = {
  {
    &emStackEventQueue,
    mac_indirect_event_handler,
    NULL,
    #ifndef EMBER_TEST
    ""
    #else
    "mac indirect"
    #endif
  },
  NULL
};
#else
EmberEventControl sl_mac_indirect_event;
#endif
static uint16_t lastEventTimeMS;

static Buffer longIndirectPool = NULL_BUFFER;
static Buffer shortIndirectPool = NULL_BUFFER;

static uint16_t indirectTimeoutMs;

extern uint16_t *sl_mac_child_status;
static sl_mac_child_status_flags_t childPolledBitField[SL_MAC_MAX_SUPPORTED_NETWORKS] = { 0 };
static sl_mac_child_status_flags_t childIsExpectingMessageBitField[SL_MAC_MAX_SUPPORTED_NETWORKS] = { 0 };

//----------------------------------------------------------------
// Forward declarations.

static PacketHeader matchingPoolAddress(bool isShort, uint8_t *address, uint8_t nwk_index);
static void removeHeaderFromPool(PacketHeader header);
static uint16_t timeoutPools(uint16_t elapsedTicks, uint8_t nwk_index);
static void recalculateMacDataPendingBitField(void);

typedef bool (*sli_transient_function_type) (EmberNodeId);
static sli_transient_function_type sli_transient_entry_present = NULL;
//-------------------------------------------------------
// Initialize.
void sli_mac_transient_table_init(void* p_fn)
{
  sli_transient_entry_present = (sli_transient_function_type) p_fn;
}
void sl_mac_indirect_queue_init(uint16_t timeoutMs)
{
  sli_mac_inactivate_event(sl_mac_indirect_event);
  longIndirectPool = NULL_BUFFER;
  shortIndirectPool = NULL_BUFFER;
  indirectTimeoutMs = timeoutMs;
}

void sl_mac_mark_indirect_buffers(void)
{
  emMarkBuffer(&longIndirectPool);
  emMarkBuffer(&shortIndirectPool);
}

void sl_mac_set_indirect_transmission_timeout(uint16_t newTimeoutMs)
{
  indirectTimeoutMs = newTimeoutMs;
}

//-------------------------------------------------------
// Interface upwards.
// Since this function is called by a higher layer, the child tables should
// already be pointed to the correct ones based on the current network index.
sl_status_t sl_mac_indirect_submit(PacketHeader header)
{
  uint16_t nowMS = halCommonGetInt16uMillisecondTick();
  uint16_t timeout = indirectTimeoutMs;
  uint8_t childIndex = sl_mac_header_outgoing_child_index(header);

  if (sl_mac_destination_mode(header) == MAC_FRAME_DESTINATION_MODE_SHORT) {
    // only want to do this if there isn't an entry in the child table
    bool isInTransientTable = false;
    if (childIndex == 0xFF) {
      isInTransientTable = (sli_transient_entry_present)
                           ? sli_transient_entry_present(sl_mac_destination(header))
                           : false;
    }
    if ((childIndex != 0xFF) || isInTransientTable) {
      #ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
      if (!sl_mac_check_additional_pending_data(header)) {
        uint16_t dest = sl_mac_destination(header);
        sl_mac_spinel_add_src_match_short_entry(dest);
      }
      #endif
      sl_mac_set_child_flag(childIndex, SL_MAC_CHILD_HAS_PENDING_SHORT_INDIRECT_MESSAGE, true);
      // Short addressed indirect messages are only sent to children
      ATOMIC(emBufferQueueAdd(&shortIndirectPool, header); )
    } else {
      return SL_STATUS_NOT_FOUND;
    }
  } else {
    if (emBufferQueueLength(&longIndirectPool) < LONG_INDIRECT_POOL_SIZE) {
      if (childIndex != 0xFF) {
#ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
        if (!sl_mac_check_additional_pending_data(header)) {
          uint8_t *destpointer = sl_mac_destination_pointer(header);
          sl_mac_spinel_add_src_match_ext_entry(destpointer);
        }
#endif
        sl_mac_set_child_flag(childIndex, SL_MAC_CHILD_HAS_PENDING_LONG_INDIRECT_MESSAGE, true);
      }
      // Zigbee sends long indirect messages to nodes not in the child table
      ATOMIC(emBufferQueueAdd(&longIndirectPool, header); )
    } else {
      return SL_STATUS_FULL;
    }
  }
  if (sli_mac_event_is_active(sl_mac_indirect_event)) {
    timeout += elapsedTimeInt16u(lastEventTimeMS, nowMS);
  } else {
    lastEventTimeMS = nowMS;
    sli_mac_set_event_delay_ms(sl_mac_indirect_event, timeout);
  }

  sl_mac_in_memory_overhead_t *in_memory_packet
    = (sl_mac_in_memory_overhead_t *) (emGetBufferPointer(header));
  in_memory_packet->appended_info.indirect_queue_info.indirect_timeout = timeout;
  in_memory_packet->appended_info.indirect_queue_info.indirect_tries = INDIRECT_TRANSMIT_TRIES;

  return SL_STATUS_OK;
}

//-------------------------------------------------------
// When a poll arrives we need to decide whether to set the data pending flag in the ack.

bool sl_mac_long_id_data_pending(EmberEUI64 address)
{
  // This function is called from the ISR context to determine whether data pending
  // flag needs to be set in the mac ack. Therefore, it is not okay to access buffer
  // queues in this function as buffer compaction may be in progress in main while
  // this function fires

  // This function only gets called during association since source addressing =
  // long address only during that time. After receiving an association request,
  // we add an entry into the child table. But this is only done for end devices and
  // sleepy end devices. Therefore, we can always return true for routers and check
  // the child table for end devices and sleepy end devices to try and prevent them
  // from staying awake when it isnt necessary

  // Check if EUI64 is in the child table
  uint8_t childIndex = sl_mac_child_long_index(address);

  // No entry in child table - therefore, EUI is of a router. Return true
  // to avoid accessing buffers
  if ( 0xFF == childIndex ) {
    return true;
  } else {
    // Check flag in the child table to see if there is data pending for the child
    return (SL_MAC_CHILD_HAS_PENDING_LONG_INDIRECT_MESSAGE
            == (sl_mac_get_child_info_flags(childIndex) & SL_MAC_CHILD_HAS_PENDING_LONG_INDIRECT_MESSAGE));
  }
}

//-------------------------------------------------------
// When a data request arrives we need to reply with the correct message.
//
// Applications that want to know when we get a poll from a stranger
// define this handler.

bool sl_mac_indirect_process_poll(uint8_t mac_index, PacketHeader header)
{
  bool expectingData = ((sl_mac_header_mac_info(header)
                         & EMBER_MAC_INFO_OUTGOING_FRAME_PENDING)
                        != 0);
  uint8_t *source = sl_mac_source_pointer(header);
  uint8_t nwk_index = sl_mac_nwk_index(header);
  SL_MAC_MULTI_PAN_CODE({
    // Check if the network index is valid
    if (nwk_index >= SL_MAC_MAX_SUPPORTED_NETWORKS) {
      EMBER_TEST_ASSERT(0);
      return false;
    }
    // Get the current network index and make sure it matches the network index from the packet
    if (sli_mac_get_current_child_table_network_index() != nwk_index) {
      EMBER_TEST_ASSERT(0);
      return false;
    }
  });

  if (sl_mac_source_mode(header) == MAC_FRAME_SOURCE_MODE_LONG) {
    if (expectingData) {
      PacketHeader match = matchingPoolAddress(false, source, nwk_index);

      if (match != NULL_BUFFER) {
        sl_mac_in_memory_overhead_t *in_memory_packet
          = (sl_mac_in_memory_overhead_t *) (emGetBufferPointer(match));

        if (sl_mac_submit(MAC_INDEX,
                          in_memory_packet->info.nwk_index,
                          match,
                          SL_MAC_TRANSMIT_PRIORITY_HIGH,
                          sl_mac_indirect_transmit_complete,
                          0)) {
          in_memory_packet->appended_info.indirect_queue_info.submit_flag = true;
        }
      }
    }
    return true;        // Long ID packets belong to the MAC.
  } else {
    EmberNodeId address = emberFetchLowHighInt16u(source);
    uint8_t childIndex = sl_mac_child_index(address);
    bool isInTransientTable = false;
    if (childIndex == SL_MAC_CHILD_INVALID_INDEX) {
      isInTransientTable = (sli_transient_entry_present)
                           ? sli_transient_entry_present(address)
                           : false;
    }
    if ((childIndex == SL_MAC_CHILD_INVALID_INDEX)  && !isInTransientTable) {
      return false;     // Unknown device; let the network layer deal with it.
    } else {
      sl_mac_child_status_flags_t mask;
      if (childIndex != SL_MAC_CHILD_INVALID_INDEX) {
        mask = ((sl_mac_child_status_flags_t) 1) << childIndex;
        childPolledBitField[nwk_index] |= mask;
      }

      if (expectingData
          &&  (isInTransientTable ||  sl_mac_child_has_pending_message(childIndex))) {
        if ( isInTransientTable || (sl_mac_get_child_info_flags(childIndex)
                                    & (SL_MAC_CHILD_HAS_PENDING_SHORT_INDIRECT_MESSAGE
                                       | SL_MAC_CHILD_HAS_PENDING_LONG_INDIRECT_MESSAGE))) {
          uint8_t temp[2];
          PacketHeader match;
          temp[0] = LOW_BYTE(address);
          temp[1] = HIGH_BYTE(address);
          match = matchingPoolAddress(true, temp, nwk_index);
          sl_mac_in_memory_overhead_t *in_memory_packet
            = (sl_mac_in_memory_overhead_t *) (emGetBufferPointer(match));

          if (match == NULL_BUFFER) {
            sl_mac_set_child_flag(childIndex,
                                  (SL_MAC_CHILD_HAS_PENDING_SHORT_INDIRECT_MESSAGE
                                   | SL_MAC_CHILD_HAS_PENDING_LONG_INDIRECT_MESSAGE),
                                  false);
#ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
            uint16_t dest = sl_mac_destination(match);
            sl_mac_spinel_clear_src_match_short_entry(dest);
#endif
          } else if (sl_mac_submit(MAC_INDEX,
                                   in_memory_packet->info.nwk_index,
                                   match,
                                   SL_MAC_TRANSMIT_PRIORITY_HIGH,
                                   sl_mac_indirect_transmit_complete,
                                   0)) {
            in_memory_packet->appended_info.indirect_queue_info.submit_flag = true;
          }
        } else {
          childIsExpectingMessageBitField[nwk_index] |= mask;
        }
      }
      return true;      // Network doesn't care about polls from children.
    }
  }
}

//-------------------------------------------------------
// When creating a mac header we need to decide whether to set the data pending
// flag.

bool sl_mac_check_additional_pending_data(PacketHeader header)
{
  bool isShort = (sl_mac_destination_mode(header)
                  == MAC_FRAME_DESTINATION_MODE_SHORT);
  uint8_t *dest = sl_mac_destination_pointer(header);
  uint8_t nwk_index = sl_mac_nwk_index(header);
  SL_MAC_MULTI_PAN_CODE({
    // Check if the network index is valid
    if (nwk_index >= SL_MAC_MAX_SUPPORTED_NETWORKS) {
      EMBER_TEST_ASSERT(0);
      return false;
    }
  });

  if (matchingPoolAddress(isShort, dest, nwk_index)
      != NULL_BUFFER) {
    return true;
  }

  if (sli_mac_push_child_table_pointer(nwk_index) == SL_STATUS_OK) {
    if (isShort) {
      uint8_t childIndex = sl_mac_child_index(emberFetchLowHighInt16u(dest));
      if (childIndex != 0xFF
          && (sl_mac_child_status[(childIndex)] & 0x710) != 0) { // CHILD_HAS_PENDING_MESSAGE
        sli_mac_pop_child_table_pointer();
        return true;
      }
    }
    // Restore the Child Table Pointers
    sli_mac_pop_child_table_pointer();
  }

  return false;
}

//-------------------------------------------------------
// After the mac completes a transmission we check to see if it is in the pool.
//

void sl_mac_indirect_transmit_complete(uint8_t mac_index, sl_status_t status, PacketHeader packet, uint8_t tag)
{
  Buffer *indirect_queue = ((sl_mac_destination_mode(packet)
                             == MAC_FRAME_DESTINATION_MODE_SHORT)
                            ? &shortIndirectPool
                            : &longIndirectPool);

  Buffer finger = emBufferQueueHead(indirect_queue);

  while (finger != NULL_BUFFER) {
    if (packet == finger) {
      sl_mac_in_memory_overhead_t *in_memory_packet
        = (sl_mac_in_memory_overhead_t *) (emGetBufferPointer(finger));
      in_memory_packet->appended_info.indirect_queue_info.indirect_tries -= 1;

      if (status == SL_STATUS_OK
          || status == SL_STATUS_MAC_NO_DATA
          || in_memory_packet->appended_info.indirect_queue_info.indirect_tries == 0) {
        ATOMIC(removeHeaderFromPool(finger); )

        sl_mac_upper_mac_state_t * state = sl_mac_upper_mac_state + MAC_INDEX;
        sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters + sl_mac_nwk_index(packet);
        sl_mac_transmit_complete_callback_t callback = current_nwk_radio_params->indirect_tx_complete_callback;
        if (callback != NULL) {
          callback(MAC_INDEX, status, packet, tag);
        }
      } else {
        recalculateMacDataPendingBitField();
      }
#ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
      if (!sl_mac_check_additional_pending_data(finger)) {
        if (indirect_queue == &shortIndirectPool) {
          uint16_t dest = sl_mac_destination(finger);
          sl_mac_spinel_clear_src_match_short_entry(dest);
        } else {
          uint8_t *destpointer = sl_mac_destination_pointer(finger);
          sl_mac_spinel_clear_src_match_ext_entry(destpointer);
        }
      }
#endif
    }
    finger = emBufferQueueNext(indirect_queue, finger);
  }
}

//-------------------------------------------------------
// Removes any headers whose timelimit has been reached.
#ifndef EVENT_CONTROL_SYSTEM
static void mac_indirect_event_handler(EmberEvent *event)
#else
void sl_mac_indirect_event_handler(void)
#endif
{
  uint16_t nowMS = (halCommonGetInt16uMillisecondTick());
  uint16_t elapsedTicks = elapsedTimeInt16u(lastEventTimeMS, nowMS);
  uint16_t minTimeoutTicks;

  lastEventTimeMS = nowMS;

  minTimeoutTicks = timeoutPools(elapsedTicks, 0xFF);

  if (minTimeoutTicks == MAX_INT16U_VALUE) {
    sli_mac_inactivate_event(sl_mac_indirect_event);
  } else {
    sli_mac_set_event_delay_ms(sl_mac_indirect_event,
                               minTimeoutTicks);
  }
}

void sl_mac_indirect_purge(uint8_t nwk_index)
{
  timeoutPools(MAX_INT16U_VALUE, nwk_index);
}

//-------------------------------------------------------
// Process any incoming polls.
//
// If a child has multiple pending messages, we use the following
// priority to determine which goes first:
//  1. queued unicast
//  2. 0xFFFF broadcast
//  3. Application
// This ordering is derived from two rules: send unicast information
// before broadcast, and send messages that time out before messages
// that don't.

void sl_mac_indirect_check_poll_flags(void)
{
  uint8_t nwk_index = 0;
#ifndef EMBER_MULTI_NETWORK_STRIPPED
  for (nwk_index = 0; nwk_index < SL_MAC_MAX_SUPPORTED_NETWORKS; nwk_index++)
#endif // EMBER_MULTI_NETWORK_STRIPPED
  {
    if (childPolledBitField[nwk_index] != 0) {
      // Set the child pointers for the new network
      if (sli_mac_push_child_table_pointer(nwk_index) == SL_STATUS_OK) {
        sl_mac_child_status_flags_t mask = 1;
        for (uint8_t child_index = 0;
             ((child_index < sl_mac_child_table_size) && childPolledBitField[nwk_index]);
             child_index++) {
          bool polled = false;
          bool expectsMessage = false;

          if (mask & childPolledBitField[nwk_index]) {
            polled = true;
            childPolledBitField[nwk_index] &= ~mask;
            if (mask & childIsExpectingMessageBitField[nwk_index]) {
              expectsMessage = true;
              childIsExpectingMessageBitField[nwk_index] &= ~mask;
            }
          }

          if (polled
              && (sl_mac_get_child_info_flags(child_index) & SL_MAC_CHILD_IS_PRESENT)) {
            bool sendAppJitMessage =
              (expectsMessage
               && ((sl_mac_child_status[child_index] & 0x0110) // (CHILD_PENDING_APPLICATION_JIT
                                                               //  | CHILD_PENDING_SLEEPY_BROADCAST)
                   == 0x0010));                                // CHILD_PENDING_APPLICATION_JIT

            UNUSED uint8_t mac_index = sl_mac_get_child_mac_index(child_index);
            sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;
            sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters + nwk_index;
            sl_mac_poll_received_callback_t poll_rx_callback = current_nwk_radio_params->poll_rx_callback;

            // Notify poll received
            if (poll_rx_callback) {
              // NOTE: The poll_rx_callback function will be changing and restoring
              // the current network index which may change what the child table pointers are
              // pointing to based on the push operation above. We must there pop the pointers from
              // the stack and then re-push after the following call.
              sli_mac_pop_child_table_pointer();

              poll_rx_callback(child_index, nwk_index);
              // See above NOTE.
              if (sli_mac_push_child_table_pointer(nwk_index) != SL_STATUS_OK) {
                continue;
              }
            }

            if (expectsMessage && !sendAppJitMessage) {
              sl_mac_set_child_flag(child_index, SL_MAC_CHILD_EXPECTING_JIT_MESSAGE, true);
              sl_mac_kickstart(MAC_INDEX);
            }

            EmberNodeId child_id = sl_mac_child_short_id(child_index);
            sl_mac_poll_handler_t poll_handler_callback = current_nwk_radio_params->poll_handler_callback;

            // Handle poll
            if (poll_handler_callback) {
              sl_mac_set_callback_network_index(nwk_index);
              poll_handler_callback(child_id, sendAppJitMessage);
              sl_mac_set_callback_network_index(0xFF);
            }
          }
          mask <<= 1;
        }

        // Restore the child pointers to the old network
        sli_mac_pop_child_table_pointer();
      }
    }
  }
}

//-------------------------------------------------------
// Private functions.

static PacketHeader matchingPoolAddress(bool isShort, uint8_t *address, uint8_t nwk_index)
{
  Buffer *indirect_queue;
  uint8_t addressSize;

  if (isShort) {
    indirect_queue = &shortIndirectPool;
    addressSize = 2;
  } else {
    indirect_queue = &longIndirectPool;
    addressSize = EUI64_SIZE;
  }

  Buffer finger = emBufferQueueHead(indirect_queue);

  while (finger != NULL_BUFFER) {
    sl_mac_in_memory_overhead_t *in_memory_packet
      = (sl_mac_in_memory_overhead_t *) (emGetBufferPointer(finger));
    if (!in_memory_packet->appended_info.indirect_queue_info.submit_flag
        && (MEMCOMPARE(address,
                       sl_mac_destination_pointer(finger),
                       addressSize)
            == 0)
        && (nwk_index == in_memory_packet->info.nwk_index)) {
      return finger;
    }
    finger = emBufferQueueNext(indirect_queue, finger);
  }
  return NULL_BUFFER;
}

static void recalculateMacDataPendingBitField(void)
{
  // Clear short and long pending flags for all entries in the child table
#ifndef EMBER_MULTI_NETWORK_STRIPPED
  for (uint8_t nwk_index = 0; nwk_index < SL_MAC_MAX_SUPPORTED_NETWORKS; nwk_index++)
#endif // EMBER_MULTI_NETWORK_STRIPPED
  {
    if (sli_mac_push_child_table_pointer(NWK_INDEX) == SL_STATUS_OK) {
      sl_mac_set_sleepy_children_flags((SL_MAC_CHILD_HAS_PENDING_SHORT_INDIRECT_MESSAGE
                                        | SL_MAC_CHILD_HAS_PENDING_LONG_INDIRECT_MESSAGE),
                                       false);

      sli_mac_pop_child_table_pointer();
    }
  }

  // Loop 2 times - First time set flags for devices that are still in the short indirect queue
  // second time around, the loop does the same thing for the the long indirect queue.
  for (uint8_t i = 0; i < 2; i++) {
    Buffer finger;
    Buffer *indirect_queue;
    uint8_t flag;

    if ( i == 0 ) {
      indirect_queue = &shortIndirectPool;
      flag = SL_MAC_CHILD_HAS_PENDING_SHORT_INDIRECT_MESSAGE;
    } else {
      indirect_queue = &longIndirectPool;
      flag = SL_MAC_CHILD_HAS_PENDING_LONG_INDIRECT_MESSAGE;
    }

    finger = emBufferQueueHead(indirect_queue);
    while (finger != NULL_BUFFER) {
  #ifndef EMBER_MULTI_NETWORK_STRIPPED
      UNUSED uint8_t nwk_index = sl_mac_nwk_index(finger);
  #endif // EMBER_MULTI_NETWORK_STRIPPED
      if (NWK_INDEX < SL_MAC_MAX_SUPPORTED_NETWORKS) {
        // Switch the child table pointers to the new network
        if (sli_mac_push_child_table_pointer(NWK_INDEX) == SL_STATUS_OK) {
          uint8_t childIndex = sl_mac_header_outgoing_child_index(finger);
          if (childIndex != 0xFF) {
            sl_mac_set_child_flag(childIndex, flag, true);
          }
          finger = emBufferQueueNext(indirect_queue, finger);

          // Restore the child table pointers
          sli_mac_pop_child_table_pointer();
        }
      }
    }
  }
}

static void removeHeaderFromPool(PacketHeader header)
{
  if (sl_mac_destination_mode(header)
      == MAC_FRAME_DESTINATION_MODE_SHORT) {
    emBufferQueueRemove(&shortIndirectPool, header);
    recalculateMacDataPendingBitField();
  } else {
    emBufferQueueRemove(&longIndirectPool, header);
  }
}

// The queue has the headers in the order in which they were added, so
// any that time out must be at the head of the queue.  We move them
// them to another queue and then decrement the time on the remaining
// headers.
// This function takes in 2 parameters, elapsedTicks and nwk_index.
// A network index of 0xFF with the valid elapsedTicks value must be passed
// in to update the indirect_queue entries and check for timed out entries.
// When any other network index is passed in, only the entries that match the
// network index will be updated. This can be used to purge all the entries
// for a given network index by passing in the max value for elapsedTicks.
static uint16_t timeoutPools(uint16_t elapsedTicks, uint8_t nwk_index)
{
  uint16_t minTimeoutTicks = MAX_INT16U_VALUE;
  Buffer completedHeaders = NULL_BUFFER;
  Buffer *indirect_queue = &longIndirectPool;

  DECLARE_INTERRUPT_STATE;

  while (true) {
    DISABLE_INTERRUPTS();
    while (!emBufferQueueIsEmpty(indirect_queue)) {
      Buffer head = emBufferQueueHead(indirect_queue);
      sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *) (emGetBufferPointer(head));
      if (in_memory_packet->appended_info.indirect_queue_info.indirect_timeout <= elapsedTicks) {
        if ((nwk_index == 0xFF) || (sl_mac_nwk_index(head) == nwk_index)) {
          emBufferQueueRemoveHead(indirect_queue);
          emBufferQueueAdd(&completedHeaders, head);
        }
      } else {
        break;
      }
    }

    if (indirect_queue == &shortIndirectPool) {
      recalculateMacDataPendingBitField();
    }

    Buffer finger = emBufferQueueHead(indirect_queue);
    while (finger != NULL_BUFFER) {
      if ((nwk_index == 0xFF) || (sl_mac_nwk_index(finger) == nwk_index)) {
        sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *) (emGetBufferPointer(finger));
        uint16_t remaining = in_memory_packet->appended_info.indirect_queue_info.indirect_timeout - elapsedTicks;
        in_memory_packet->appended_info.indirect_queue_info.indirect_timeout = remaining;
        if (remaining < minTimeoutTicks) {
          minTimeoutTicks = remaining;
        }
      }
      finger = emBufferQueueNext(indirect_queue, finger);
    }
    RESTORE_INTERRUPTS();
    if (indirect_queue == &shortIndirectPool) {
      break;
    } else {
      indirect_queue = &shortIndirectPool;
    }
  }

  while (!emBufferQueueIsEmpty(&completedHeaders)) {
    PacketHeader header = emBufferQueueRemoveHead(&completedHeaders);
    sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *) (emGetBufferPointer(header));
    uint8_t pkt_nwk_index = sl_mac_nwk_index(header);

    EMBER_TEST_ASSERT(pkt_nwk_index < SL_MAC_MAX_SUPPORTED_NETWORKS);

    if (!in_memory_packet->appended_info.indirect_queue_info.submit_flag) {
      if (pkt_nwk_index < SL_MAC_MAX_SUPPORTED_NETWORKS) {
        if (sli_mac_push_child_table_pointer(pkt_nwk_index) == SL_STATUS_OK) {
          uint8_t child_index = sl_mac_header_outgoing_child_index(header);
          if (child_index != 0xFF) {
            UNUSED uint8_t mac_index = sl_mac_get_child_mac_index(child_index);
            sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;
            sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters + pkt_nwk_index;   //sl_mac_nwk_index(header);
            sl_mac_transmit_complete_callback_t callback = current_nwk_radio_params->indirect_tx_complete_callback;
            if (callback != NULL) {
              callback(MAC_INDEX, SL_STATUS_MAC_INDIRECT_TIMEOUT, header, 0);
            }
          } else {
            // TODO: Zigbee sends long indirect messages to nodes not in the child table
          }
          sli_mac_pop_child_table_pointer();
#ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
          if (!sl_mac_check_additional_pending_data(header)) {
            if (indirect_queue == &shortIndirectPool) {
              uint16_t dest = sl_mac_destination(header);
              sl_mac_spinel_clear_src_match_short_entry(dest);
            } else {
              uint8_t *destpointer = sl_mac_destination_pointer(header);
              sl_mac_spinel_clear_src_match_ext_entry(destpointer);
            }
          }
#endif
        }
      }
    }
  }
  return minTimeoutTicks;
}

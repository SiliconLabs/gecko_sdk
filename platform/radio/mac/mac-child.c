/***************************************************************************//**
 * @file mac-child.c
 *
 * @brief MAC layer child interface
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

#include PLATFORM_HEADER
#include "buffer_manager/buffer-management.h"
#include "buffer_manager/buffer-queue.h"
#include "stack/core/ember-stack.h"
#include "mac-types.h"
#include "lower-mac.h"
#include "upper-mac.h"
#include "mac-header.h"
#include "mac-child.h"

#ifndef EMBER_STACK_CONNECT
  #ifndef  ZIGBEE_MAX_NETWORK_ADDRESS
  #define ZIGBEE_MAX_NETWORK_ADDRESS      0xFFF7
  #endif
#endif

sl_mac_child_entry_t *sl_mac_child_table = NULL;
uint16_t *sl_mac_child_status = NULL;
uint8_t sl_mac_child_table_size = SL_MAC_MAX_CHILD_TABLE_SIZE;

sl_status_t sl_mac_child_table_init(sl_mac_child_entry_t *childTable,
                                    uint16_t *childStatus,
                                    uint8_t childTableSize)
{
  if (childTable == NULL
      || childStatus == NULL
      || childTableSize > SL_MAC_MAX_CHILD_TABLE_SIZE) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_child_table = childTable;
  sl_mac_child_status = childStatus;
  sl_mac_child_table_size = childTableSize;

  for (int i = 0; i < childTableSize; i++) {
    sl_mac_child_table[i].info = 0;
    sl_mac_child_table[i].mac_index = 0;
    sl_mac_child_table[i].short_id = EMBER_NO_CHILD_DEFAULT;
    MEMSET(sl_mac_child_table[i].long_id, 0xFF, EUI64_SIZE);
  }
  MEMSET(sl_mac_child_status, 0, childTableSize * sizeof(uint16_t));

  return SL_STATUS_OK;
}

sl_status_t sl_mac_add_child(uint8_t macIndex,
                             uint8_t childIndex,
                             EmberNodeId shortId,
                             EmberEUI64 longId,
                             sl_mac_child_status_flags_t info)
{
  if (sl_mac_child_table == NULL) {
    return SL_STATUS_INVALID_STATE;
  }

  if (macIndex >= MAX_MAC_INDEX
      || childIndex >= sl_mac_child_table_size) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];

  if (child_entry->mac_index == macIndex
      && child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    return SL_STATUS_ALREADY_EXISTS;
  }

  child_entry->mac_index = macIndex;
  child_entry->short_id = shortId;
  MEMCOPY((uint8_t *) child_entry->long_id, (uint8_t *) longId, EUI64_SIZE);
  child_entry->info = (SL_MAC_CHILD_IS_PRESENT | info);
  return SL_STATUS_OK;
}

sl_status_t sl_mac_remove_child(uint8_t childIndex)
{
  if (sl_mac_child_table == NULL) {
    return SL_STATUS_INVALID_STATE;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];

  child_entry->info = 0;
  child_entry->mac_index = 0;
  child_entry->short_id = EMBER_NO_CHILD_DEFAULT;
  MEMSET(child_entry->long_id, 0xFF, EUI64_SIZE);

  return SL_STATUS_OK;
}

sl_status_t sl_mac_update_child(uint8_t macIndex,
                                uint8_t childIndex,
                                EmberNodeId shortId,
                                EmberEUI64 longId,
                                sl_mac_child_status_flags_t info)
{
  if (sl_mac_child_table == NULL) {
    return SL_STATUS_INVALID_STATE;
  }

  if (macIndex >= MAX_MAC_INDEX
      || childIndex >= sl_mac_child_table_size) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];

  if (child_entry->mac_index == macIndex
      && child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    child_entry->short_id = shortId;
    MEMCOPY((uint8_t *) child_entry->long_id, (uint8_t *) longId, EUI64_SIZE);
    child_entry->info = (SL_MAC_CHILD_IS_PRESENT | info);
    return SL_STATUS_OK;
  }

  return SL_STATUS_INVALID_STATE;
}

EmberNodeId sl_mac_child_short_id(uint8_t childIndex)
{
  if (sl_mac_child_table == NULL) {
    return EMBER_NULL_NODE_ID;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return EMBER_NULL_NODE_ID;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];
  if (child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    return child_entry->short_id;
  }
  return EMBER_NULL_NODE_ID;
}

uint8_t *sl_mac_child_long_id(uint8_t childIndex)
{
  if (sl_mac_child_table == NULL) {
    return NULL;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return NULL;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];
  if (child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    return child_entry->long_id;
  }

  return NULL;
}

EmberNodeId sl_mac_find_child_short_id(EmberEUI64 longId)
{
  if (sl_mac_child_table == NULL) {
    return EMBER_NULL_NODE_ID;
  }

  if (longId == NULL) {
    return EMBER_NULL_NODE_ID;
  }

  uint8_t i = 0;
  for (i = 0; i < sl_mac_child_table_size; i++) {
    sl_mac_child_entry_t *child_entry = &sl_mac_child_table[i];
    if (MEMCOMPARE(child_entry->long_id, longId, EUI64_SIZE) == 0
        && child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
      return child_entry->short_id;
    }
  }
  return EMBER_NULL_NODE_ID;
}

//static const EmberEUI64 NULL_EUI = { 0, 0, 0, 0, 0, 0, 0, 0 };
//#define isNullEui(eui) (MEMCOMPARE(eui, NULL_EUI, EUI64_SIZE) == 0)

uint8_t sl_mac_child_find_long_index(uint8_t startIndex, EmberEUI64 longId)
{
  if (sl_mac_child_table == NULL) {
    return 0xFF;
  }

  // only 0xFF is mostly checked for index as invalid value,
  // returning this can give false positives.
  if (startIndex >= sl_mac_child_table_size) {
    return 0xFF;
  }

  uint8_t i = 0;
  for (i = startIndex; i < sl_mac_child_table_size; i++) {
    sl_mac_child_entry_t *child_entry = &sl_mac_child_table[i];
    if (longId == NULL
        && (child_entry->info & SL_MAC_CHILD_IS_PRESENT) == 0) {
      // If longId is NULL, find the first free index for use.
      return i;
    } else if (longId != NULL && MEMCOMPARE(child_entry->long_id, longId, EUI64_SIZE) == 0
               && (child_entry->info & SL_MAC_CHILD_IS_PRESENT)) {
      // Otherwise, find a match.
      return i;
    }
  }
  return 0xFF;
}

uint8_t sl_mac_child_index(EmberNodeId shortId)
{
  if (sl_mac_child_table == NULL) {
    return 0xFF;
  }

  uint8_t i = 0;
  for (i = 0; i < sl_mac_child_table_size; i++) {
    sl_mac_child_entry_t *child_entry = &sl_mac_child_table[i];
    if (child_entry->short_id == shortId
        && child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
      return i;
    }
  }
  return 0xFF;
}

uint8_t sl_mac_child_long_index(EmberEUI64 longId)
{
  return sl_mac_child_find_long_index(0, longId);
}

bool sl_mac_child_lookup_eui64_by_id(EmberNodeId id, EmberEUI64 eui64)
{
  uint8_t index = sl_mac_child_index(id);
  if (index != 0xFF) {
    uint8_t *eui = sl_mac_child_long_id(index);
    if (eui != NULL) {
      MEMCOPY(eui64, eui, EUI64_SIZE);
      return true;
    }
  }
  return false;
}

sl_status_t sl_mac_set_child_id(uint8_t childIndex, EmberNodeId nodeId)
{
  if (sl_mac_child_table == NULL) {
    return SL_STATUS_INVALID_STATE;
  }
#ifndef EMBER_STACK_CONNECT
  if (nodeId > ZIGBEE_MAX_NETWORK_ADDRESS) {
    return SL_STATUS_INVALID_PARAMETER;
  }
#endif
  if (childIndex >= sl_mac_child_table_size) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];

  if (child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    child_entry->short_id = nodeId;
    return SL_STATUS_OK;
  }

  return SL_STATUS_INVALID_STATE;
}

sl_status_t sl_mac_set_child_long_id(uint8_t childIndex, EmberEUI64 longId)
{
  if (sl_mac_child_table == NULL) {
    return SL_STATUS_INVALID_STATE;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];

  if (child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    MEMCOPY(child_entry->long_id, longId, EUI64_SIZE);
    return SL_STATUS_OK;
  }

  return SL_STATUS_INVALID_STATE;
}

uint8_t sl_mac_header_outgoing_child_index(PacketHeader header)
{
  return ((sl_mac_destination_mode(header) == MAC_FRAME_DESTINATION_MODE_SHORT)
          ? sl_mac_child_index(sl_mac_destination(header))
          : sl_mac_child_long_index(sl_mac_destination_pointer(header)));
}

uint8_t sl_mac_header_incoming_child_index(PacketHeader header)
{
  return ((sl_mac_source_mode(header) == MAC_FRAME_SOURCE_MODE_SHORT)
          ? sl_mac_child_index(sl_mac_source(header))
          : sl_mac_child_long_index(sl_mac_source_pointer(header)));
}

// This should be called when the PHY wants to know whether to put framePending
// as true or false in a MAC ACK. Other things besides this function should be
// checked, too, of course. This should not be called when deciding if we can
// send a JIT message to the child right now. See
// sl_mac_child_expecting_jit_message for that.
bool sl_mac_child_has_pending_message(uint8_t childIndex)
{
  if (sl_mac_child_table == NULL) {
    return false;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];
  if (child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
#ifndef EMBER_SCRIPTED_TEST
    if (sl_mac_child_status[childIndex] & 0x710) { // CHILD_HAS_PENDING_MESSAGE = 0x710
      return true;
    }
#endif
    return ((child_entry->info & SL_MAC_CHILD_HAS_PENDING_MESSAGE) != 0);
  }
  return false;
}

// This should be called when processing a poll and inspecting whether we can
// send JIT messages to the child right now. This should not be called when
// the PHY wants to know whether we can set frame pending or not (see
// sl_mac_child_has_pending_message for that)
bool sl_mac_child_expecting_jit_message(uint8_t childIndex)
{
  if (sl_mac_child_table == NULL) {
    return false;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return false;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];
  if (child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    return ((child_entry->info & SL_MAC_CHILD_EXPECTING_JIT_MESSAGE) != 0);
  }
  return false;
}

uint8_t sl_mac_get_child_mac_index(uint8_t childIndex)
{
  if (sl_mac_child_table == NULL) {
    return 0xFF;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return 0xFF;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];
  if (child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    return child_entry->mac_index;
  }
  return 0xFF;
}

bool sl_mac_set_child_mac_index(uint8_t childIndex, uint8_t macIndex)
{
  if (sl_mac_child_table == NULL) {
    return false;
  }

  if (childIndex >= sl_mac_child_table_size || macIndex >= MAX_MAC_INDEX) {
    return false;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];
  if (!(child_entry->info & SL_MAC_CHILD_IS_PRESENT)) {
    return false;
  }
  child_entry->mac_index = macIndex;
  return true;
}

sl_mac_child_status_flags_t sl_mac_get_child_info_flags(uint8_t childIndex)
{
  if (sl_mac_child_table == NULL) {
    return 0x00;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return 0x00;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];
  if (child_entry->info & SL_MAC_CHILD_IS_PRESENT) {
    return child_entry->info;
  }

  return 0x00;
}

sl_status_t sl_mac_set_child_flag(uint8_t childIndex, sl_mac_child_status_flags_t flags, bool set)
{
  if (sl_mac_child_table == NULL) {
    return SL_STATUS_INVALID_STATE;
  }

  if (childIndex >= sl_mac_child_table_size) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_child_entry_t *child_entry = &sl_mac_child_table[childIndex];

  if (flags != SL_MAC_CHILD_IS_PRESENT && !(child_entry->info & SL_MAC_CHILD_IS_PRESENT)) {
    return SL_STATUS_NOT_FOUND;
  }

  if (set) {
    child_entry->info |= flags;
  } else {
    child_entry->info &= ~flags;
  }

  return SL_STATUS_OK;
}

sl_status_t sl_mac_set_sleepy_children_flags(sl_mac_child_status_flags_t mask, bool set)
{
  if (sl_mac_child_table == NULL) {
    return SL_STATUS_INVALID_STATE;
  }

  uint8_t i = 0;
  for (i = 0; i < sl_mac_child_table_size; i++) {
    sl_mac_child_entry_t *child_entry = &sl_mac_child_table[i];
    if ((child_entry->info & SL_MAC_CHILD_IS_PRESENT) != 0
        && (child_entry->info & SL_MAC_CHILD_IS_RX_ON_WHEN_IDLE) == 0) {
      if (set) {
        child_entry->info |= mask;
      } else {
        child_entry->info &= ~mask;
      }
    }
  }

  return SL_STATUS_OK;
}

bool sl_mac_check_any_child_flags(sl_mac_child_status_flags_t flags)
{
  if (sl_mac_child_table == NULL) {
    return false;
  }

  uint8_t i = 0;
  for (i = 0; i < sl_mac_child_table_size; i++) {
    sl_mac_child_entry_t *child_entry = &sl_mac_child_table[i];
    if ((child_entry->info & flags) != 0) {
      return true;
    }
  }
  return false;
}

bool sl_mac_child_id_is_sleepy(EmberNodeId id)
{
  uint8_t childIndex = sl_mac_child_index(id);
  return (childIndex != SL_MAC_CHILD_INVALID_INDEX
          && sl_mac_child_is_sleepy(childIndex));
}

bool sl_mac_child_id_is_valid(EmberNodeId id)
{
  return (sl_mac_child_index(id) != SL_MAC_CHILD_INVALID_INDEX);
}

#ifndef EMBER_MULTI_NETWORK_STRIPPED
#define MAX_CHILD_TABLE_POINTER_STACK_DEPTH   2
static sl_mac_child_table_pointers_t sl_mac_child_table_pointers[SL_MAC_MAX_SUPPORTED_NETWORKS];
static sl_mac_child_table_pointers_t child_table_pointer_stack[MAX_CHILD_TABLE_POINTER_STACK_DEPTH];
// Index of the element on top of the stack (-1 means the stack is empty)
int8_t current_child_table_pointer_stack_index = -1;

// Noted: the declaration of the following functions are located in
// platform/radio/mac/mac-multi-network.h where is aware of EMBER_MULTI_NETWORK_STRIPPED
sl_status_t sli_mac_init_child_table_pointers(uint8_t nwk_index,
                                              sl_mac_child_entry_t *child_table,
                                              uint16_t *child_status)
{
  // If the child table pointers are valid, then save them to the network index
  if (nwk_index < SL_MAC_MAX_SUPPORTED_NETWORKS) {
    sl_mac_child_table_pointers[nwk_index].child_table = child_table;
    sl_mac_child_table_pointers[nwk_index].child_status = child_status;
    return SL_STATUS_OK;
  }
  return SL_STATUS_FAIL;
}

// This function will return the network index whose child table pointer matches the
// currently used child table. It will return a valud of 0xFF failure if no match is found.
uint8_t sli_mac_get_current_child_table_network_index(void)
{
  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    if (sl_mac_child_table_pointers[i].child_table == sl_mac_child_table) {
      return i;
    }
  }
  return 0xFF;
}

//------------------------------------------------------------------------------
// Child Table Pointer push and pop stack system.
// The following APIs will also be called from Interrupt Context.
//------------------------------------------------------------------------------

// This function will select the correct child table based on the network index
// and push the current pointers on the stack. This API is also called from
// interrupt context.
sl_status_t sli_mac_push_child_table_pointer(uint8_t nwk_index)
{
  // Assert if the current stack index is less than -1
  assert(current_child_table_pointer_stack_index >= -1);

  // Disable Interrupts since this can be called from an ISR
  DECLARE_INTERRUPT_STATE;
  DISABLE_INTERRUPTS();

  if (nwk_index < SL_MAC_MAX_SUPPORTED_NETWORKS) {
    // Push the index on the stack if we have room
    if (((current_child_table_pointer_stack_index + 1) < MAX_CHILD_TABLE_POINTER_STACK_DEPTH)
        && (sl_mac_child_table_pointers[nwk_index].child_table != NULL)
        && (sl_mac_child_table_pointers[nwk_index].child_status != NULL)) {
      current_child_table_pointer_stack_index++;
      child_table_pointer_stack[current_child_table_pointer_stack_index].child_table = sl_mac_child_table;
      child_table_pointer_stack[current_child_table_pointer_stack_index].child_status = sl_mac_child_status;

      // Point to the child table based on network index
      sl_mac_child_table = sl_mac_child_table_pointers[nwk_index].child_table;
      sl_mac_child_status = sl_mac_child_table_pointers[nwk_index].child_status;

      // Restore Saved Interrupt State
      RESTORE_INTERRUPTS();

      return SL_STATUS_OK;
    }
  }

  // Restore Saved Interrupt State
  RESTORE_INTERRUPTS();

  return SL_STATUS_FAIL;
}

// This function will will point back to the child tables being used before
// the sl_mac_push_child_table_pointer was called. This API is also called from
// interrupt context.
sl_status_t sli_mac_pop_child_table_pointer(void)
{
  // Assert if stack is already empty
  assert(current_child_table_pointer_stack_index >= 0);

  // Disable Interrupts since this can be called from an ISR
  DECLARE_INTERRUPT_STATE;
  DISABLE_INTERRUPTS();

  // Restore the child table pointers from the stack.
  // It should be non-null since it is checked in push.
  sl_mac_child_table = child_table_pointer_stack[current_child_table_pointer_stack_index].child_table;
  sl_mac_child_status = child_table_pointer_stack[current_child_table_pointer_stack_index].child_status;

  // Update the stack index
  current_child_table_pointer_stack_index--;

  // Restore Saved Interrupt State
  RESTORE_INTERRUPTS();

  return SL_STATUS_OK;
}
// End Child Table Pointer push and pop stack system.
//------------------------------------------------------------------------------
#endif // EMBER_MULTI_NETWORK_STRIPPED

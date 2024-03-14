/***************************************************************************//**
 * @file sl_zigbee_tlv_core.c
 * @brief source for tlv processing
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "stack/include/ember-types.h"
#include "buffer_manager/legacy-packet-buffer.h"
#include "include/sl_zigbee_tlv_core.h"

// searches a chain for a tlv link that matches the given tag id
// returns SL_STATUS_NOT_FOUND
sl_status_t sli_tlv_chain_find_link_tag(sl_zigbee_tlv_chain *tlv,
                                        tlv_link_t *t,
                                        uint8_t tag_id);

// increment to the next tlv link in the chain
sl_status_t sli_tlv_chain_get_next_tlv_link(sl_zigbee_tlv_chain *chain);

int sli_tlv_chain_count_tag_occurrences(sl_zigbee_tlv_chain *tlvs, uint8_t tag);

static sl_zigbee_tlv_t* sli_tlv_chain_get_next_tlv(sl_zigbee_tlv_chain *chain);

// Following functions will be provided by the global tlv component if enabled.
// we will have default weak definititions for these here for all non-zigbee stack builds

WEAK(bool sl_zigbee_stack_tlv_id_is_manufacturer_specifc(uint8_t tag))
{
  return false;
}
WEAK(sl_status_t sl_zigbee_stack_specific_tlv_check(uint8_t tag,
                                                    uint16_t len,
                                                    sl_zigbee_tlv_tag_min_length_t *env,
                                                    bool encapRecurse))
{
  return SL_STATUS_NOT_SUPPORTED;
}

// add counters for invalid tlvs?
sl_status_t sli_tlv_chain_is_valid_with_local_env(sl_zigbee_tlv_chain *tlvs,
                                                  sl_zigbee_tlv_tag_min_length_t *env,
                                                  bool encapRecurse)
{
  sl_zigbee_tlv_chain finger;
  finger = *tlvs;
  sl_status_t status = SL_STATUS_OK;
  if (finger.length == 0) {
    status = SL_STATUS_EMPTY;
  }
  while (status == SL_STATUS_OK) {
    uint8_t tag = TLV_LINK_TAG_ID(finger.head);
    // NOTE TLV_LINK_LENGTH is the raw length byte
    uint16_t len = TLV_LINK_LENGTH(finger.head) + 1;
    status = sli_tlv_chain_get_next_tlv_link(&finger);
    if (status != SL_STATUS_INVALID_INDEX) {
      if (sli_tlv_chain_count_tag_occurrences(tlvs, tag) > 1
          && !sl_zigbee_stack_tlv_id_is_manufacturer_specifc(tag)) {
        status = SL_STATUS_ALREADY_EXISTS;
      } else {
        sl_status_t temp_status = sl_zigbee_stack_specific_tlv_check(tag, len, env, encapRecurse);
        if (temp_status == SL_STATUS_NOT_SUPPORTED) {
          temp_status = status;
        } else {
          status = temp_status;
        }
      }
    }
  }
  return (status == SL_STATUS_EMPTY ? SL_STATUS_OK : status);
}

sl_status_t sli_tlv_chain_find_link_tag(sl_zigbee_tlv_chain *tlvs,
                                        tlv_link_t *t_out,
                                        uint8_t tag_id)
{
  sl_zigbee_tlv_chain finger;
  finger.head = tlvs->head;
  finger.length = tlvs->length;
  tlv_link_t result = NULL;
  sl_status_t status = SL_STATUS_OK;
  while ((status == SL_STATUS_OK) && !result) {
    uint8_t tag = TLV_LINK_TAG_ID(finger.head);
    if (tag == tag_id) {
      result = finger.head;
    } else {
      status = sli_tlv_chain_get_next_tlv_link(&finger);
    }
  }
  *t_out = result;
  return (status == SL_STATUS_EMPTY ? SL_STATUS_NOT_FOUND : status);
}

int sli_tlv_chain_count_tag_occurrences(sl_zigbee_tlv_chain *tlvs, uint8_t tag)
{
  sl_zigbee_tlv_chain finger;
  tlv_link_t t = tlvs->head;
  size_t rem = tlvs->length;
  finger.head = t;
  finger.length = rem;
  int count = 0;
  sl_status_t status = SL_STATUS_OK;
  while (status == SL_STATUS_OK) {
    if (TLV_LINK_TAG_ID(finger.head) == tag) {
      count++;
      if (count > 1) {
        break;
      }
    }
    status = sli_tlv_chain_get_next_tlv_link(&finger);
  }
  return count;
}

/**
 * ==== TLV Chain Core ====
 * traverse serialized tlvs as a linked data-struct
 */

// increment to the next tlv link in the chain
sl_status_t sli_tlv_chain_get_next_tlv_link(sl_zigbee_tlv_chain *chain)
{
  if (chain->length == 0) {
    return SL_STATUS_EMPTY;
  }
  tlv_link_t *t = &chain->head;
  size_t *r = &chain->length;
  size_t link_len = TLV_LINK_TOTAL_LENGTH(*t);

  if (link_len > *r
      || link_len <= TLV_HEADER_LENGTH) {
    return SL_STATUS_INVALID_INDEX;
  } else {
    *t += link_len;
    *r -= link_len;
    return *r == 0 ? SL_STATUS_EMPTY : SL_STATUS_OK;
  }
}

uint16_t sl_zigbee_tlv_serial_length(const sl_zigbee_tlv_t *tlv)
{
  return TLV_HEADER_LENGTH + sl_zigbee_tlv_get_length(tlv);
}

sl_status_t sli_zigbee_tlv_deserialize_tlv(uint8_t *tlv_link,
                                           sl_zigbee_tlv_t *tlv_struct,
                                           uint16_t max_len)
{
  if (TLV_LINK_DATA_SIZE(tlv_link) > max_len) {
    // we need to allow for messages to be LONGER
    // but we can only copy up to max len
    // solution is to copy max_len bytes...
    sl_zigbee_tlv_set_length(tlv_struct, max_len);
  } else {
    sli_zigbee_tlv_set_length_raw(tlv_struct, TLV_LINK_LENGTH(tlv_link));
  }
  sl_zigbee_tlv_set_tag(tlv_struct, TLV_LINK_TAG_ID(tlv_link));
  MEMMOVE(sl_zigbee_tlv_get_value_ptr(tlv_struct),
          TLV_LINK_DATA(tlv_link),
          sl_zigbee_tlv_get_length(tlv_struct));
  return SL_STATUS_OK;
}

static void serialize_tlv(uint8_t *tlv_start,
                          sl_zigbee_tlv_t *tlv_struct)
{
  TLV_LINK_TAG_ID(tlv_start) = sl_zigbee_tlv_get_tag(tlv_struct);
  TLV_LINK_LENGTH(tlv_start) = sli_zigbee_tlv_get_length_raw(tlv_struct);
  MEMMOVE(TLV_LINK_DATA(tlv_start),
          sl_zigbee_tlv_get_value_ptr(tlv_struct),
          sl_zigbee_tlv_get_length(tlv_struct));
}

// Message Buffer APIs

sl_status_t sl_zigbee_tlv_check_general_format_env(Buffer buff,
                                                   uint16_t index,
                                                   sl_zigbee_tlv_tag_min_length_t *env)
{
  sl_status_t status = SL_STATUS_FAIL;
  uint16_t total_length = sli_legacy_buffer_manager_get_buffer_length(buff);
  if (total_length >= index) {
    sl_zigbee_tlv_chain chain = { .rem = 0 };
    chain.head = sli_legacy_buffer_manager_get_buffer_pointer(buff) + index;
    chain.length = total_length - index;
    status = sli_tlv_chain_is_valid_with_local_env(&chain, env, false);
  }
  return status;
}

// either we
// 1) serialize the tlv and use some append api to add that to the end of the
// buffer
//
// or we
// 2) manually traverse the tlv_chain in the buffer, set
// the length of the buffer, and write the tlv data directly
// we went with option 1)
sl_status_t sl_zigbee_tlv_concat_to_buffer(Buffer *buffer_handle,
                                           uint16_t index,
                                           sl_zigbee_tlv_t *tlv)
{
  Buffer buff = *buffer_handle;
  if (buff == NULL_BUFFER) {
    return SL_STATUS_FAIL;
  }
  uint16_t buffer_len = sli_legacy_buffer_manager_get_buffer_length(buff);
  if (buffer_len < index) {
    return SL_STATUS_WOULD_OVERFLOW;
  }
  //   method 1
  // serialize the tlv
  uint8_t scratch[TLV_HEADER_LENGTH + MAX_TLV_LENGTH];
  uint16_t tlv_length = sl_zigbee_tlv_serial_length(tlv);
  serialize_tlv(scratch, tlv);
  // append to buffer
  EmberStatus status = emberAppendToLinkedBuffers(buff, scratch, tlv_length);
  // return success
  *buffer_handle = buff;
  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t sl_zigbee_tlv_search_buffer_payload_for_id(Buffer buff,
                                                       uint16_t index,
                                                       uint8_t tag_id,
                                                       sl_zigbee_tlv_t *result,
                                                       uint16_t max_len)
{
  // validate the index vs the length of the buffer
  uint16_t buffer_len = sli_legacy_buffer_manager_get_buffer_length(buff);
  if (buffer_len <= index) {
    return SL_STATUS_NOT_FOUND;
  }
  // create a tlv_chain from the tlv payload
  sl_zigbee_tlv_chain chain;
  chain.head = sli_legacy_buffer_manager_get_buffer_pointer(buff) + index;
  chain.length = buffer_len - index;
  // search the tlv chain for a matching tag id
  tlv_link_t t;
  sl_status_t status = sli_tlv_chain_find_link_tag(&chain,
                                                   &t,
                                                   tag_id);
  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }
  // deserialize if a result tlv is passed
  if (result != NULL) {
    status = sli_zigbee_tlv_deserialize_tlv(t, result, max_len);
  }
  return status;
}

// NOTE this allows for tlvs to be extracted without a copy operation
// TODO revisit old tlv code and change to this api where possible
sl_status_t sl_zigbee_tlv_ptr_find_by_id(uint8_t *tlvs_start,
                                         uint16_t remaining,
                                         uint8_t tag_id,
                                         sl_zigbee_tlv_t **result)
{
  if (result == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  sl_zigbee_tlv_chain chain = { .head = tlvs_start, .length = remaining };
  tlv_link_t t;
  sl_status_t status = sli_tlv_chain_find_link_tag(&chain, &t, tag_id);
  if (status == SL_STATUS_OK) {
    if (result != NULL) {
      *result = (sl_zigbee_tlv_t *) t;
    }
  }
  return status;
}

// Encapsulation TLV APIs

sl_status_t sl_zigbee_encap_tlv_add_tlv(sl_zigbee_tlv_t *encap_tlv,
                                        uint16_t max_len,
                                        sl_zigbee_tlv_t *tlv)
{
  // figure out if there is enough space to fit the tlv
  // NOTE we really want the index to start writing, which is the length - 1
  // or in our case it is the raw value of the length field
  uint16_t current_idx = sli_zigbee_tlv_get_length_raw(encap_tlv);
  if (current_idx != 0) {
    current_idx++;
  }
  uint16_t added_len = sl_zigbee_tlv_serial_length(tlv);
  if (current_idx + added_len > max_len) {
    return SL_STATUS_FAIL;
  } else {
    // add the tlv to the end of the chain
    serialize_tlv(sl_zigbee_tlv_get_value_ptr(encap_tlv) + current_idx, tlv);
    sl_zigbee_tlv_set_length(encap_tlv, current_idx + added_len);
    return SL_STATUS_OK;
  }
}

sl_status_t sl_zigbee_encap_tlv_find_tag_id(sl_zigbee_tlv_t *encap_tlv,
                                            uint8_t tag_id,
                                            sl_zigbee_tlv_t *result,
                                            uint16_t max_len)
{
  sl_zigbee_tlv_chain chain;
  chain.head = sl_zigbee_tlv_get_value_ptr(encap_tlv);
  chain.length = sl_zigbee_tlv_get_length(encap_tlv);
  tlv_link_t t;
  sl_status_t status = sli_tlv_chain_find_link_tag(&chain,
                                                   &t,
                                                   tag_id);
  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }
  if (result) {
    status = sli_zigbee_tlv_deserialize_tlv(t, result, max_len);
  }
  return status;
}

bool sli_zigbee_encap_tlv_check_format(sl_zigbee_tlv_t *encap_tlv)
{
  sl_zigbee_tlv_chain chain;
  chain.head = sl_zigbee_tlv_get_value_ptr(encap_tlv);
  chain.length = sl_zigbee_tlv_get_length(encap_tlv);
  sl_status_t status = sli_tlv_chain_is_valid_with_local_env(&chain, NULL, true);
  return status == SL_STATUS_OK;
}

#ifdef EMBER_TEST
// debug helpers

#define TLV_DBG_PRINTF(...) printf(__VA_ARGS__)

static uint16_t tlv_dbg_count(sl_zigbee_tlv_chain t)
{
  uint16_t count = 0;
  sl_status_t status = SL_STATUS_OK;
  while (status == SL_STATUS_OK) {
    count++;
    status = sli_tlv_chain_get_next_tlv_link(&t);
  }
  return count;
}

static uint8_t * tlv_dbg_get_tlv_index(sl_zigbee_tlv_chain chain, uint16_t i)
{
  uint16_t count = tlv_dbg_count(chain);
  if (i >= count) {
    return NULL;
  } else {
    for (uint16_t j = 0; j < i; j++) {
      (void) sli_tlv_chain_get_next_tlv_link(&chain);
    }
    return chain.head;
  }
}

UNUSED static void tlv_dbg_print(uint8_t *tlvs, size_t length)
{
  sl_zigbee_tlv_chain chain;
  chain.head = tlvs;
  chain.length = length;
  TLV_DBG_PRINTF("\n");
  for (uint16_t i = 0; i < tlv_dbg_count(chain); i++) {
    uint8_t *finger = tlv_dbg_get_tlv_index(chain, i);
    TLV_DBG_PRINTF("| tlv #%d | ", i);
    TLV_DBG_PRINTF("tag: %03d | ", TLV_LINK_TAG_ID(finger));
    TLV_DBG_PRINTF("length-1: %03d | ", TLV_LINK_LENGTH(finger));
    TLV_DBG_PRINTF("value: ");
    for (uint16_t j = 0; j < TLV_LINK_DATA_SIZE(finger); j++) {
      TLV_DBG_PRINTF("%02x ", finger[j + TLV_HEADER_LENGTH]);
    }
    TLV_DBG_PRINTF("|\n");
  }
}
#else
#define TLV_DBG_PRINTF(...) {}
#endif //EMBER_TEST

sl_status_t sl_zigbee_tlv_initialize_chain(sl_zigbee_tlv_chain *chain,
                                           uint8_t *memory,
                                           const size_t chain_length,
                                           const size_t memory_length)
{
  if (chain == NULL || memory == NULL) {
    return SL_STATUS_NULL_POINTER;
  } else if (memory_length + chain_length <= TLV_HEADER_LENGTH) {
    return SL_STATUS_INVALID_COUNT;
  }

  // NOTE setting the memory to a known value might make it easier to debug
  MEMSET(memory, 0x5f, memory_length);

  chain->head = memory;
  chain->length = chain_length;
  chain->rem = memory_length;

  return SL_STATUS_OK;
}

// NOTE advances the head of chain and returns a pointer to the new head
// NOTE requires that the chain be coherent
static sl_zigbee_tlv_t* sli_tlv_chain_get_next_tlv(sl_zigbee_tlv_chain *chain)
{
  if (chain == NULL || chain->length == 0) {
    return NULL;
  }
  sl_zigbee_tlv_t* t = (sl_zigbee_tlv_t *) chain->head;
  size_t step_len = sl_zigbee_tlv_serial_length(t);
  // if the step is tool long or too short return an error
  if (step_len > chain->length
      || step_len <= TLV_HEADER_LENGTH) {
    return NULL;
  } else {
    // advance the iterator forward
    chain->head += step_len;
    chain->length -= step_len;
    return t;
  }
}

sl_status_t sl_zigbee_tlv_chain_find_by_id(sl_zigbee_tlv_chain *chain,
                                           uint8_t tag_id,
                                           sl_zigbee_tlv_t **result)
{
  if (chain == NULL
      || chain->head == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  sl_zigbee_tlv_chain _shadow_chain;
  sl_status_t status = sl_zigbee_tlv_initialize_full_chain(&_shadow_chain,
                                                           chain->head,
                                                           chain->length);
  if (status != SL_STATUS_OK) {
    return status;
  }
  sl_zigbee_tlv_t *finger = NULL;
  bool found = false;
  do {
    finger = sli_tlv_chain_get_next_tlv(&_shadow_chain);
    if (finger != NULL) {
      found = sl_zigbee_tlv_get_tag(finger) == tag_id;
    }
  } while (finger != NULL && !found);

  if (finger == NULL) {
    return SL_STATUS_NOT_FOUND;
  }
  if (result != NULL) {
    *result = finger;
  }
  return SL_STATUS_OK;
}

sl_status_t sl_zigbee_tlv_chain_add_tlv_block(sl_zigbee_tlv_chain *chain,
                                              const uint8_t tag_id,
                                              const uint8_t length,
                                              sl_zigbee_tlv_t **result)
{
  if (chain == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  uint16_t serial_len = length + TLV_HEADER_LENGTH;
  if (serial_len > chain->rem) {
    return SL_STATUS_WOULD_OVERFLOW;
  }

  sl_zigbee_tlv_t *tlv_next = (sl_zigbee_tlv_t *) (chain->head + chain->length);
  sl_zigbee_tlv_set_tag(tlv_next, tag_id);
  sl_zigbee_tlv_set_length(tlv_next, length);
  // NOTE watermark the value for debugging
  // TODO debug mode only
  MEMSET(sl_zigbee_tlv_get_value_ptr(tlv_next), 0xbf, length);
  chain->length += serial_len;
  chain->rem -= serial_len;
  if (result != NULL) {
    *result = tlv_next;
  }
  return SL_STATUS_OK;
}

sl_status_t sl_zigbee_tlv_chain_add_tlv(sl_zigbee_tlv_chain *chain,
                                        const sl_zigbee_tlv_t *t)
{
  if (chain == NULL || t == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  uint16_t serial_len = sl_zigbee_tlv_serial_length(t);
  if (serial_len >= chain->rem) {
    return SL_STATUS_WOULD_OVERFLOW;
  }
  sl_zigbee_tlv_t *tlv_next = (sl_zigbee_tlv_t *) (chain->head + chain->length);
  MEMCOPY(tlv_next, t, serial_len);
  chain->length += serial_len;
  chain->rem -= serial_len;
  return SL_STATUS_OK;
}

sl_status_t sl_zigbee_tlv_chain_append_to_buffer(sl_zigbee_tlv_chain *chain,
                                                 Buffer *buffer_handle)
{
  if (chain == NULL || buffer_handle == NULL || *buffer_handle == NULL_BUFFER) {
    return SL_STATUS_NULL_POINTER;
  }
  return emberAppendToLinkedBuffers(*buffer_handle, chain->head, chain->length);
}

bool sl_zigbee_tlv_chain_contains_all_tags(sl_zigbee_tlv_chain *tlvs,
                                           sl_zigbee_tlv_tag_list *list)
{
  tlv_link_t tlv_pointer;

  if (list->tag_ids != NULL) {
    for (uint8_t i = 0; i < list->length; i++) {
      if (sli_tlv_chain_find_link_tag(tlvs, &tlv_pointer, list->tag_ids[i]) != SL_STATUS_OK) {
        return false;
      }
    }
  }
  return true;     //return true if all tags are present
}

bool sl_zigbee_tlv_chain_contains_any_tag(sl_zigbee_tlv_chain *tlvs,
                                          sl_zigbee_tlv_tag_list *list)
{
  tlv_link_t tlv_pointer;

  if (list->tag_ids != NULL) {
    for (uint8_t i = 0; i < list->length; i++) {
      if (sli_tlv_chain_find_link_tag(tlvs, &tlv_pointer, list->tag_ids[i]) == SL_STATUS_OK) {
        return true;
      }
    }
  }

  return false;   // return false if no matching tag was found
}

uint8_t sl_zigbee_tlv_chain_get_tlv_count(sl_zigbee_tlv_chain *chain)
{
  uint8_t count = 0;
  sl_status_t status = SL_STATUS_OK;
  do {
    status = sli_tlv_chain_get_next_tlv_link(chain);
    count++;
  } while (status != SL_STATUS_EMPTY);

  return count--;
}

sl_status_t sl_zigbee_tlv_chain_next_tlv(sl_zigbee_tlv_chain *tlvs,
                                         sl_zigbee_tlv_t **next)
{
  if (tlvs == NULL) {
    return SL_STATUS_NULL_POINTER;
  } else if (tlvs->length == 0) {
    return SL_STATUS_EMPTY;
  } else {
    sl_zigbee_tlv_t *first = (sl_zigbee_tlv_t *) tlvs->head;
    uint16_t skip = sl_zigbee_tlv_serial_length(first);
    if (skip > tlvs->length) {
      return SL_STATUS_WOULD_OVERFLOW;
    }
    tlvs->head += skip;
    tlvs->length -= skip;
    if (next != NULL) {
      *next = first;
    }
    return SL_STATUS_OK;
  }
}

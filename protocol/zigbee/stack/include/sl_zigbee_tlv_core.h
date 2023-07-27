/***************************************************************************//**
 * @file sl_zigbee_tlv_core.h
 * @brief Stack TLV defines
 * this header defines public portions of the TLV Interface
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

#ifndef SL_ZIGBEE_TLV_CORE_H
#define SL_ZIGBEE_TLV_CORE_H

#include "buffer_manager/buffer-management.h"
#include "sl_status.h"

#define TLV_HEADER_LENGTH 2

#define MAX_TLV_LENGTH 256

/**
 * ==== TLV Data Model ====
 * as a way simplifying the handling of TLV Data, we are using
 * a structured data approach.  TLVs will primarily be handled
 * by the stack/application via structs that separate out the
 * tag, length, value into distinct members that can be referenced.
 *
 * In support of this we are defininig a generic version of the TLV
 * struct that can be passed to TLV handling APIs with a undefined
 * length array member.  This data type is useful for argument
 * passing, but actual TLV data needs to be instantiated into
 * concrete versions of the struct, with defined maximum lengths.
 * In order to make defining these concrete sub-types easier, we
 * have macro-ized the struct definition, with parameterized
 * array length
 */

typedef struct {
  /// tag byte
  uint8_t tag_id;
  /// length value (encodes number of value bytes -1)
  uint8_t length;
  /// variable length data field
  uint8_t value[];
} sl_zigbee_tlv_t;

// macro-ize defining concrete tlv structs
// NOTE the definition of this macro must be kept in sync with the struct definition above
#define CONCRETE_TLV_DEFINE(MAX_LEN) struct { \
    uint8_t tag_id;                           \
    uint8_t length;                           \
    uint8_t value[(MAX_LEN)];}

// example of using the macro to define tlv data types
// this will create a new TLV type with max-length of 255
#define WILDCARD_TLV_MAX_LEN 255
typedef CONCRETE_TLV_DEFINE (WILDCARD_TLV_MAX_LEN) sl_wildcard_tlv_t;

/**
 * @brief returns the number of bytes in the value field of a tlv
 * @param tlv a pointer to the tlv struct
 * @return the number of bytes contained in the tlv
 */
#ifdef DOXYGEN_SHOULD_SKIP_THIS
size_t sl_zigbee_tlv_value_byte_length(sl_zigbee_tlv_t *tlv);
#else
#define sl_zigbee_tlv_value_byte_length(t) ((t)->length + 1)
#endif // DOXYGEN_SHOULD_SKIP_THIS

// EMZIGBEE-6645
// NOTE here are some macros that should be used to access the fields of TLVs
// these should be documented as doxygen if possible
// TODO doxygenize this and add doc-string comments
#define sl_zigbee_tlv_get_tag(t) ((t)->tag_id)
#define sl_zigbee_tlv_set_tag(t, set) ((t)->tag_id = (set))

// NOTE we have two interfaces for the tlv length due to the encoding
// these will encode/decode the length to reflect the number of bytes in the value
#define sl_zigbee_tlv_get_length(t) ((t)->length + 1)
#define sl_zigbee_tlv_set_length(t, set) ((t)->length = (set) - 1)
// these directly reflect the raw length byte
#define sli_zigbee_tlv_get_length_raw(t) ((t)->length)
#define sli_zigbee_tlv_set_length_raw(t, set) ((t)->length = set)

#define sl_zigbee_tlv_get_value_ptr(t) ((t)->value)

/**
 * @brief returns the number of bytes in the tlv (including tag and length byte)
 * @param tlv a pointer to the tlv data
 * @return the number of bytes in the tlv
 */
uint16_t sl_zigbee_tlv_serial_length(const sl_zigbee_tlv_t *tlv);

/**
 * ==== TLV Serialization ====
 * We abstract away the TLV serialization to lower the burden
 * on calling contexts to process TLV payloads.  The APIs below
 * handle serializing and de-serializing structured TLV data in
 * message payloads.  The below APIs are intended for general use
 * and operate by passing in a message buffer, with the index of
 * the TLV payload.  TLV data is handled by the structured data
 * model, and is transformed into serialized TLVs by the API
 * internals
 */

// a TLV environment can be defined as an array containing a
// mapping of tag id to min length with a terminator entry at the end
typedef struct {
  // NOTE: we use the pad byte at the beginning to determine
  // which element of an array of these is the end
  uint8_t isEnd;
  uint8_t tag_id;
  uint16_t min_length;
} sl_zigbee_tlv_tag_min_length_t;

#define ENV_LIST_TERMINATOR 0xFF

#define TLV_ENV_TERMINATOR { .isEnd = ENV_LIST_TERMINATOR, }

// functions for handling serialized tlvs
sl_status_t sl_zigbee_tlv_check_general_format_env(Buffer buff,
                                                   uint16_t index,
                                                   sl_zigbee_tlv_tag_min_length_t *env);

#define sl_zigbee_tlv_check_general_format(buff, index) \
  sl_zigbee_tlv_check_general_format_env((buff), (index), NULL)

sl_status_t sl_zigbee_tlv_concat_to_buffer(Buffer *buffer_handle,
                                           uint16_t index,
                                           sl_zigbee_tlv_t *tlv);

/**
 * @brief searches for a TLV matching tag_id in buff, starting a index
 * @note if found max_copy_len bytes will be copied into the result struct
 */
sl_status_t sl_zigbee_tlv_search_buffer_payload_for_id(Buffer buff,
                                                       uint16_t index,
                                                       uint8_t tag_id,
                                                       sl_zigbee_tlv_t *result,
                                                       uint16_t max_copy_len);

/**
 * @brief searches for a tlv matching the given tag id within the chain of tlvs passed in
 * @param[in]  tlvs_start  a pointer to the beginning of the tlv chain
 * @param[in]  tag_id  the tag id to be searched for
 * @param[out] result  a reference to location where the tlv result will be stored
 * @return a status indicating whether the tlv was found
 */
sl_status_t sl_zigbee_tlv_ptr_find_by_id(uint8_t *tlvs_start,
                                         uint16_t remaining,
                                         uint8_t tag_id,
                                         sl_zigbee_tlv_t **result);

// TODO remove encap tlv apis in favor of sl_zigbee_tlv_chain apis?
// Encapsulation TLVs
// appends tlv to the encapsulated tlvs chain
sl_status_t sl_zigbee_encap_tlv_add_tlv(sl_zigbee_tlv_t *encap_tlv,
                                        uint16_t max_len,
                                        sl_zigbee_tlv_t *tlv);

// searches the encapsulated tlv chain
sl_status_t sl_zigbee_encap_tlv_find_tag_id(sl_zigbee_tlv_t *encap_tlv,
                                            uint8_t tag_id,
                                            sl_zigbee_tlv_t *result,
                                            uint16_t max_len);

// Function to Validate Tag Length
bool sli_zigbee_tlv_validate_tag_length(uint8_t tag,
                                        uint16_t len,
                                        sl_zigbee_tlv_tag_min_length_t *env);

// Helper functions for Encapsulated TLVs
bool sli_zigbee_tlv_is_encap_tag_id(uint8_t tag_id);
bool sli_zigbee_encap_tlv_check_format(sl_zigbee_tlv_t *encap_tlv);

// NOTE one idea is to make the format checker more robust
// by passing in the calling environment as a mapping of local
// tag-ids to minimum viable length.  This would let us validate
// all lengths at once rather than as a separate global and local
// component.  It would also encourage a design where message
// modules would define a set of these mappings for each of the
// messages they would implement.

// NOTE ideally want the above APIs to look something like...
// more flexible data structure, more intuitive api
// since it matches more closesly to the internal api it will be a lot slimmer
// NOTE the application will be responsible for making sure that memory stays valid
// for the lifetime of the chain...
/**
 * @brief a fixed-width buffer that can be used to add tlvs
 */
typedef struct tlv_chain {
  uint8_t *head;
  size_t length;
  size_t rem;
} sl_zigbee_tlv_chain;

/**
 * @brief A list of Tags with a given length
 */
typedef struct {
  // NOTE: we use the pad byte at the beginning to determine
  // which element of an array of these is the end
  uint8_t length;
  uint8_t* tag_ids;
} sl_zigbee_tlv_tag_list;

/**
 * @brief returns true if a TLV chain contains all tags from a list
 *
 *  @params:
 *  *tlvs - The TLV chain to search through
 *  *list - List of Tags to be seached for
 *  @return true if the TLV chain contains all tags from the list,
 *  false otherwise
 */
bool sl_zigbee_tlv_chain_contains_all_tags (sl_zigbee_tlv_chain* tlvs,
                                            sl_zigbee_tlv_tag_list* list);

/**
 * @brief returns true if a TLV chain contains none of the tags from a list
 *
 *  @params:
 *  *tlvs - The TLV chain to search through
 *  *list - List of Tags to be seached for
 *  @return true if the TLV chain contains none of the tags from the list,
 *  false otherwise
 */
bool sl_zigbee_tlv_chain_contains_any_tag(sl_zigbee_tlv_chain* tlvs,
                                          sl_zigbee_tlv_tag_list* list);

// TODO maybe macro-ize the empty and full versions to this...?
/**
 * @brief given an allocated block of memory will create a struct-wrapper
 * @param[in|out] chain the memory location containing the target chain struct
 * @param[in] memory the location of memory that tlvs will be written to
 * @param[in] chain_length the length of the chain in bytes
 * @param[in] memory_length the amount of available memory in bytes
 * @return a status code indicating whether initialization was successful
 */
sl_status_t sl_zigbee_tlv_initialize_chain(sl_zigbee_tlv_chain *chain,
                                           uint8_t *memory,
                                           const size_t chain_length,
                                           const size_t memory_length);

/**
 * @brief given an allocated block of memory will create a struct-wrapper
 * @param[in|out] chain the memory location containing the target chain struct
 * @param[in] memory the location of memory that tlvs will be written to
 * @param[in] remain the amount of available memory in bytes
 * @return a status code indicating whether initialization was successful
 */
#define sl_zigbee_tlv_initialize_empty_chain(c, m, r) sl_zigbee_tlv_initialize_chain((c), (m), 0, (r))

/**
 * @brief given an allocated block of memory will create a struct-wrapper
 * @param[in|out] chain the memory location containing the target chain struct
 * @param[in] memory the location of memory that tlvs will be written to
 * @param[in] length the length of the chain in bytes
 * @return a status code indicating whether initialization was successful
 */
#define sl_zigbee_tlv_initialize_full_chain(c, m, l) sl_zigbee_tlv_initialize_chain((c), (m), (l), 0)
// TODO create a corresponding de-init?

/**
 * @brief returns a pointer to the first tlv matching the tag id
 * @param[in] chain a the chain struct to search
 * @param[in] tag_id the target tag id to search for
 * @param[out] result a pointer to the result ptr
 * @return a status code indicating whether or not the tlv was successfully found
 */
sl_status_t sl_zigbee_tlv_chain_find_by_id(sl_zigbee_tlv_chain *chain,
                                           uint8_t tag_id,
                                           sl_zigbee_tlv_t **result);

/**
 * @brief adds a tlv to the end of the tlv chain if there is space
 * @param [in|out] chain the chain of tlvs to add to
 * @param [in] t a pointer to the tlv to add
 * @return a status code indicating whether or not the tlv was successfully added to the chain
 */
sl_status_t sl_zigbee_tlv_chain_add_tlv(sl_zigbee_tlv_chain *chain,
                                        const sl_zigbee_tlv_t *t);

/**
 * @brief adds an empty tlv with the given length and tag to the chain
 * @param [in|out] chain the chain of tlvs to add to
 * @param [in] tag_id the tag id to add to the chain
 * @param [in] length how much space to reserve for the tlv
 * @param [out] result if not null will contain the created tlv block
 * @return a status code indicating whether the operation was successful
 */
sl_status_t sl_zigbee_tlv_chain_add_tlv_block(sl_zigbee_tlv_chain *chain,
                                              const uint8_t tag_id,
                                              const uint8_t length,
                                              sl_zigbee_tlv_t **result);

/**
 * @brief takes the contents in the tlv-chain and appends
 * to the end of the given buffer
 * @param [in] chain the chain of tlvs to append (will append .length bytes)
 * @param [in|out] buffer_handle pointer to the buffer that should be appended to
 * @return a status code indicating the success
 */
sl_status_t sl_zigbee_tlv_chain_append_to_buffer(sl_zigbee_tlv_chain *chain,
                                                 Buffer *buffer_handle);

// validates no broken links and no duplicates
// (except encapsulation tlvs for now)
sl_status_t sli_tlv_chain_is_valid_with_local_env(sl_zigbee_tlv_chain *tlvs,
                                                  sl_zigbee_tlv_tag_min_length_t *env,
                                                  bool encapRecurse);

#define sli_tlv_chain_is_valid(ts) \
  sli_tlv_chain_is_valid_with_local_env((ts), NULL, false)

/**
 * @brief takes the contents in a tlv-chain and counts the number of valid TLVs
 * @param  chain chain of tlvs
 * @return the count of valid TLVs in the given chain
 */
uint8_t sl_zigbee_tlv_chain_get_tlv_count(sl_zigbee_tlv_chain *chain);

/**
 * @brief treat tlv chain as a one-way iterator, moving the head forward and returning
 * the next tlv
 * @param tlvs the tlv chain
 * @param next output parameter, contains the next tlv if it exists
 * @return SL_STATUS_EMPTY when there are no more tlvs in the chain
 *         SL_STATUS_WOULD_OVERFLOW if traversing the next in chain would overrun the chain
 *         SL_STATUS_OK otherwise
 */
sl_status_t sl_zigbee_tlv_chain_next_tlv(sl_zigbee_tlv_chain *tlvs,
                                         sl_zigbee_tlv_t **next);

// tlvs as a flat array
// NOTE these are mostly only used in tests and a couple of internal functions
// please avoid referring to these symbols directly in favor of the apis above
typedef uint8_t* tlv_link_t;

#define TLV_LINK_TAG_ID(t) ((t)[0])
#define TLV_LINK_LENGTH(t) ((t)[1])
#define TLV_LINK_DATA(t) ((t) + TLV_HEADER_LENGTH)
// the length of the data is encoded as L - 1
#define TLV_LINK_DATA_SIZE(t) (TLV_LINK_LENGTH(t) + 1)

#define TLV_LINK_TOTAL_LENGTH(t) (TLV_HEADER_LENGTH + TLV_LINK_DATA_SIZE(t))

#endif /* SL_ZIGBEE_TLV_CORE_H */

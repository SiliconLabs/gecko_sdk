/***************************************************************************//**
 * @file
 * @brief Wi-SUN CoAP resource discovery
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <string.h>
#include "sl_string.h"
#include "sli_wisun_coap_rd.h"
#include "sl_wisun_coap.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// CoAP RD CT attribte label
#define COAP_RD_ATTR_CT_LABEL             "ct"

/// CoAP RD CT attribte default value
#define COAP_RD_ATTR_CT_DEF_VAL           "40"

/// CoAP RD RT attribte label
#define COAP_RD_ATTR_RT_LABEL             "rt"

/// CoAP RD IF attribte label
#define COAP_RD_ATTR_IF_LABEL             "if"

/// CoAP RD CT attribte querry
#define COAP_RD_ATTR_CT_QUERRY            "ct="

/// CoAP RD RT attribte querry
#define COAP_RD_ATTR_RT_QUERRY            "rt="

/// CoAP RD IF attribte querry
#define COAP_RD_ATTR_IF_QUERRY            "if="

/// Resource delimiter char
#define COAP_RD_RESOURCE_DELIMITER_CHAR   ','

/// Resourc URI str chars
#define COAP_RD_RESOURCE_URI_STR_CHARS    "<>;\"\";\"\""

/// Resource dir str chars
#define COAP_RD_RESOURCE_DIR_STR_CHARS    "<>;"

/// Resource template str format
#define COAP_RD_RESOURCE_TEMPLATE_STR_FORMAT \
  "<%s>;" COAP_RD_ATTR_RT_QUERRY "\"%s\";" COAP_RD_ATTR_IF_QUERRY "\"%s\""

/// Resource dir tempalte str format
#define COAP_RD_DIR_TEMPLATE_STR_FORMAT \
  "<%s>;" COAP_RD_ATTR_CT_QUERRY COAP_RD_ATTR_CT_DEF_VAL

/// CoAP max querry string length
#define COAP_RD_MAX_QUERRY_LENGTH         (SL_WISUN_COAP_URI_PATH_MAX_SIZE)

/// String buff to string length
#define __buff_to_strlen(__lbl) \
  (sizeof(__lbl) - 1U)

/// Count of attributes
#define COAP_RD_ATTR_COUNT \
  (sizeof(_attributes) / sizeof(coap_rd_attribute_t))

/// Enum for all supported items (inc. attributes)
typedef enum coap_rd_attribute_type {
  /// URI path identification
  COAP_RD_URI = 0,
  /// content-format identification
  COAP_RD_CT,
  /// resource type identification
  COAP_RD_RT,
  /// interface identification
  COAP_RD_IF
} coap_rd_attribute_type_t;

/// String with cached length
typedef struct str_cache {
  /// String ptr
  const char *str;
  /// Length of string
  size_t len;
  /// Next ptr
  struct str_cache *next;
} str_cache_t;

// CoAP RD attribute
typedef struct coap_rd_attribute {
  /// Type
  coap_rd_attribute_type_t type;
  /// Label string
  str_cache_t label;
  /// Default value string
  str_cache_t def_val;
  /// Querry string
  str_cache_t querry;
} coap_rd_attribute_t;

/// CoAP RD querry parse
typedef struct coap_rd_querry_parse {
  /// Querry pattern
  str_cache_t querry_pattern;
  /// Attribute
  const coap_rd_attribute_t *attr;
  /// Resource list
  sl_wisun_coap_rhnd_resource_t *resources;
  /// Dir list
  str_cache_t *dir;
} coap_rd_querry_parse_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief String cache to string
 * @details Helper function, pointer must be freed after usage
 * @param[in] sc String cache
 * @return char* String ptr on heap
 *****************************************************************************/
static char *_sc_to_str(const str_cache_t * const sc);

/**************************************************************************//**
 * @brief Destroy string
 * @details Helper function, free heap
 * @param[in] str String ptr
 *****************************************************************************/
__STATIC_INLINE void _destroy_str(const char *str);

/**************************************************************************//**
 * @brief Get attribute by type
 * @details Helper function
 * @param[in] type Type of the attribute
 * @return const coap_rd_attribute_t* Attribute
 *****************************************************************************/
static const coap_rd_attribute_t *_get_attr_by_type(const coap_rd_attribute_type_t type);

/**************************************************************************//**
 * @brief Check string ptr in the buffer
 * @details Helper function to avoid string buff out of index
 * @param[in] str String ptr
 * @param[in] str_len String total length
 * @param[in] c_ptr Pointer to check
 * @return true if the c_ptr is in the buffer, otherwise false
 *****************************************************************************/
__STATIC_INLINE bool _check_str_buff_ptr(const char *str,
                                         const size_t str_len,
                                         const char *c_ptr);

/**************************************************************************//**
 * @brief Check string cache is not NULL
 * @details Helper function
 * @param[in] str
 * @return true if the str is not NULL, otherwise false
 *****************************************************************************/
__STATIC_INLINE bool _check_str_cache(str_cache_t *str);

/**************************************************************************//**
 * @brief Get querry
 * @details Helper function
 * @param[in] uri_querry_request URI querry string
 * @param[in] parsed Parse instance
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
static sl_status_t _get_querry(const char *uri_querry_request,
                               coap_rd_querry_parse_t * const parsed);

/**************************************************************************//**
 * @brief Is discovery request
 * @details Helper function
 * @param[in] uri_path_str URI path string
 * @return true if it's a discovery request, otherwise false
 *****************************************************************************/
__STATIC_INLINE bool _is_discovery_request(const char *uri_path_str);

/**************************************************************************//**
 * @brief Is URI querry
 * @details Helper function
 * @param[in] packet Packet
 * @return true if it's a URI querry, otherwise false
 *****************************************************************************/
__STATIC_INLINE bool _is_uri_querry(const sl_wisun_coap_packet_t * const packet);

/**************************************************************************//**
 * @brief Get resource attribute
 * @details helper function
 * @param[in] resource Resource
 * @param[in] attr Attribute
 * @return const char* Attribute value of resource
 *****************************************************************************/
__STATIC_INLINE const char * _get_resource_attr(const sl_wisun_coap_rhnd_resource_t * const resource,
                                                const coap_rd_attribute_t *const attr);

/**************************************************************************//**
 * @brief Is pattern matched
 * @details Helper function
 * @param[in] resource Resource
 * @param[in] parsed Parse instance
 * @return true if pattern is matched, otherwise false
 *****************************************************************************/
static bool _is_pattern_matched(const sl_wisun_coap_rhnd_resource_t * const resource,
                                const coap_rd_querry_parse_t * const parsed);

/**************************************************************************//**
 * @brief Add resource
 * @details Helper function to add resource. Resource is allocated on heap
 * @param[in] resource Resource
 * @param[in,out] parsed Parse instance
 * @return sl_status_t
 *****************************************************************************/
static sl_status_t _add_resource(sl_wisun_coap_rhnd_resource_t *resource,
                                 coap_rd_querry_parse_t * parsed);

/**************************************************************************//**
 * @brief Destroy resources of parse instance
 * @details Helper function
 * @param[in] parsed Parse instance
 *****************************************************************************/
static void _destroy_resources(const coap_rd_querry_parse_t * const parsed);

/**************************************************************************//**
 * @brief Parse URI querry
 * @details Parse and fill parse instance with matched resources
 * @param[in] resources Available resources
 * @param[in] uri_querry_request URI querry request string
 * @param[out] dest Destination parse instance
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
static sl_status_t _parse_uri_querry(const sl_wisun_coap_rhnd_resource_t * const resources,
                                     const char *uri_querry_request,
                                     coap_rd_querry_parse_t * const dest);

/**************************************************************************//**
 * @brief Get URI querry string
 * @details Helper function. String is allocated on heap, must be freed
 * @param[in] packet Packet
 * @return char* URI querry string
 *****************************************************************************/
static char *_get_uri_querry_string(const sl_wisun_coap_packet_t * const packet);

/**************************************************************************//**
 * @brief Calculate resource discovery response payload size
 * @details Function used to allocate proper size of buffer
 * @param[in] parsed Parse instance
 * @param[in] calc_dir Indicate requirement of calculate directory part of payload
 * @return size_t Calculated payload size
 *****************************************************************************/
static size_t _calc_rd_response_str_size(const coap_rd_querry_parse_t * const parsed,
                                         const bool calc_dir);

/**************************************************************************//**
 * @brief Get first level dir length
 * @details Helper function
 * @param[in] uri_path URI path string
 * @return size_t Length of first level dir
 *****************************************************************************/
static size_t _get_first_level_dir_len(const char *uri_path);

/**************************************************************************//**
 * @brief Add dir to list of parse instance
 * @details Allocate dir ptr on the heap
 * @param[in] uri_path URI path string
 * @param[out] dest Destination parse instance
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
static sl_status_t _add_dir_to_list(const char *uri_path,
                                    coap_rd_querry_parse_t * const dest);

/**************************************************************************//**
 * @brief Destroy dir list of parse instance
 * @details Free memory
 * @param[out] dest Destination parse instance
 *****************************************************************************/
static void _destroy_dir_list(coap_rd_querry_parse_t * const dest);

/**************************************************************************//**
 * @brief Parse resource directories
 * @details Parse first level directories of resources
 * @param[in] resources Resource list
 * @param[out] dest Destination parse instance
 *****************************************************************************/
static void _parse_resource_dir(const sl_wisun_coap_rhnd_resource_t * const resources,
                                coap_rd_querry_parse_t * const dest);

/**************************************************************************//**
 * @brief Print directory to payload buff
 * @details Helper function
 * @param[in] buf Payload buffer
 * @param[in] dir Directory string
 * @param[in,out] remaind_str_size Remained string size
 * @return char* Pointer to next free char
 *****************************************************************************/
static char *_print_dir_to_buff(char * const buf,
                                const str_cache_t * const dir,
                                size_t * const remaind_str_size);

/**************************************************************************//**
 * @brief Print resource to payload buff
 * @details Helper function
 * @param[in] buf Payload buffer
 * @param[in] dir Directory string
 * @param[in,out] remaind_str_size Remained string size
 * @return char* Pointer to next free char
 *****************************************************************************/
static char *_print_resource_to_buff(char * const buf,
                                     const sl_wisun_coap_rhnd_resource_t * const resource,
                                     size_t * const remaind_str_size);

/**************************************************************************//**
 * @brief Print delimiter char to payload buff
 * @details Helper function
 * @param[in] buf Payload buffer
 * @param[in,out] remaind_str_size Remained string size
 * @return char* Pointer to next free char
 *****************************************************************************/
static char *_print_delimiter_to_buff(char * const buf,
                                      size_t * const remaind_str_size);

/**************************************************************************//**
 * @brief Build response payload string
 * @details Build payload string to allocate buffer on heap
 * @param[in] parse Parse instance
 * @param[in] max_str_length Length of allocated string buffer
 * @param[in] add_dir_list True if the dir lis required
 * @return char* String result ptr
 *****************************************************************************/
static char *_build_resp_payload_str(const coap_rd_querry_parse_t * const parse,
                                     const size_t max_str_length,
                                     const bool add_dir_list);
/**************************************************************************//**
 * @brief Filter resources by dir
 * @details Match resource by first-level directory
 * @param[in] uri_path URI path string
 * @param[in] resources Resource list
 * @param[out] parse Parse instance
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
static sl_status_t _filter_by_dirs(const char *uri_path,
                                   const sl_wisun_coap_rhnd_resource_t * const resources,
                                   coap_rd_querry_parse_t * const parse);

/**************************************************************************//**
 * @brief Add all discoverable resource
 * @details Helper function to add available and discoverable resources
 * @param[in] resources Available resources
 * @param[out] parse Parse instance
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
static sl_status_t _add_all_discoverable_resource(const sl_wisun_coap_rhnd_resource_t * const resources,
                                                  coap_rd_querry_parse_t const * parse);
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

static const coap_rd_attribute_t _attributes[] = {
  // Content type
  {
    .type    = COAP_RD_CT,
    .label   = { .str = COAP_RD_ATTR_CT_LABEL,
                 .len = __buff_to_strlen(COAP_RD_ATTR_CT_LABEL) },
    .def_val = { .str = COAP_RD_ATTR_CT_DEF_VAL,
                 .len = __buff_to_strlen(COAP_RD_ATTR_CT_DEF_VAL) },
    .querry  = { .str = COAP_RD_ATTR_CT_QUERRY,
                 .len = __buff_to_strlen(COAP_RD_ATTR_CT_QUERRY) }
  },

  // Resource type
  {
    .type    = COAP_RD_RT,
    .label   = { .str = COAP_RD_ATTR_RT_LABEL,
                 .len = __buff_to_strlen(COAP_RD_ATTR_RT_LABEL) },
    .def_val = { .str = NULL,
                 .len = 0UL },
    .querry  = { .str = COAP_RD_ATTR_RT_QUERRY,
                 .len = __buff_to_strlen(COAP_RD_ATTR_RT_QUERRY) }
  },

  // Interface
  {
    .type    = COAP_RD_IF,
    .label   = { .str = COAP_RD_ATTR_IF_LABEL,
                 .len = __buff_to_strlen(COAP_RD_ATTR_IF_LABEL) },
    .def_val = { .str = NULL,
                 .len = 0UL },
    .querry  = { .str = COAP_RD_ATTR_IF_QUERRY,
                 .len = __buff_to_strlen(COAP_RD_ATTR_IF_QUERRY) }
  },
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

char * sli_wisun_coap_rd_parser(const sl_wisun_coap_rhnd_resource_t * const resources,
                                const sl_wisun_coap_packet_t * const packet,
                                uint16_t * const rd_length)
{
  char *uri_path_str                        = NULL;
  char *uri_querry_str                      = NULL;
  char *res_str                             = NULL;
  coap_rd_querry_parse_t parsed             = { 0U };
  bool is_discovery_req                     = false;
  bool is_uri_querry                        = false;
  bool is_dir_required                      = false;
  sl_status_t stat                          = SL_STATUS_OK;

  // check resources
  if (resources == NULL) {
    return NULL;
  }

  // Check the uri length and other parameters
  if (packet == NULL
      || (packet->uri_path_len == 0U)
      || (packet->uri_path_len > SL_WISUN_COAP_URI_PATH_MAX_SIZE)) {
    return NULL;
  }
  // Check the message code to decide if get request received
  if (packet->msg_code != COAP_MSG_CODE_REQUEST_GET) {
    return NULL;
  }

  // Get URI path
  uri_path_str = sl_wisun_coap_get_uri_path_str(packet);
  if (uri_path_str == NULL) {
    return NULL;
  }

  is_discovery_req = _is_discovery_request(uri_path_str);
  is_uri_querry = _is_uri_querry(packet);

  // parse resource dirs
  _parse_resource_dir(resources, &parsed);

  // 1. Parse Discovery request URI querry
  if (is_discovery_req && is_uri_querry) {
    // Get '\0' terminated uri querry str from packet
    uri_querry_str = _get_uri_querry_string(packet);
    if (uri_querry_str == NULL) {
      return NULL;
    }
    // Parse and get matched list of resources
    stat = _parse_uri_querry(resources, uri_querry_str, &parsed);
    is_dir_required = false;

    // 2. Discovery request only, without uri querry (full resource list)
  } else if (is_discovery_req) {
    stat = _add_all_discoverable_resource(resources, &parsed);
    is_dir_required = true;

    // 3. Create response for not complete resource path
  } else {
    stat = _filter_by_dirs(uri_path_str, resources, &parsed);
    is_dir_required = false;
  }

  // If there is not any matched resource, set all resource to list
  if (parsed.resources == NULL && stat != SL_STATUS_FAIL) {
    stat = _add_all_discoverable_resource(resources, &parsed);
    is_dir_required = true;
  }

  *rd_length = _calc_rd_response_str_size(&parsed, is_dir_required);

  // Build response string payload
  if (stat == SL_STATUS_OK) {
    res_str = _build_resp_payload_str(&parsed, *rd_length, is_dir_required);
  } else {
    res_str = NULL;
  }

  // clean-up
  _destroy_dir_list(&parsed);
  _destroy_resources(&parsed);
  _destroy_str(uri_querry_str);
  sl_wisun_coap_destroy_uri_path_str(uri_path_str);

  return res_str;
}

// Resource Discovery response building
sl_wisun_coap_packet_t *sli_wisun_coap_rd_build_response(const char * const payload,
                                                         const uint16_t payload_len,
                                                         const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_coap_packet_t *packet = NULL;

  packet = sl_wisun_coap_build_response(req_packet, COAP_MSG_CODE_RESPONSE_CONTENT);

  if (packet != NULL) {
    packet->payload_ptr      = (uint8_t*)payload;
    packet->payload_len      = payload_len;
    packet->content_format   = COAP_CT_LINK_FORMAT;
  } else {
    // cleanup
    _destroy_str(payload);
  }

  return packet;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static char *_sc_to_str(const str_cache_t * const sc)
{
  char *str = NULL;
  str = sl_wisun_coap_malloc(sc->len + 1U);
  if (str == NULL) {
    return NULL;
  }

  memcpy(str, sc->str, sc->len);
  str[sc->len] = '\0';
  return str;
}

__STATIC_INLINE void _destroy_str(const char *str)
{
  sl_wisun_coap_free((void *)str);
}

static const coap_rd_attribute_t *_get_attr_by_type(const coap_rd_attribute_type_t type)
{
  for (size_t i = 0; i < COAP_RD_ATTR_COUNT; ++i) {
    if (_attributes[i].type == type) {
      return &_attributes[i];
    }
  }
  return NULL;
}

__STATIC_INLINE bool _check_str_buff_ptr(const char *str,
                                         const size_t str_len,
                                         const char *c_ptr)
{
  return (bool) (c_ptr >= str && c_ptr < (str + str_len));
}

__STATIC_INLINE bool _check_str_cache(str_cache_t *str)
{
  return (bool) (str != NULL && str->len && str->str != NULL);
}

static sl_status_t _get_querry(const char *uri_querry_request, coap_rd_querry_parse_t * const parsed)
{
  size_t querry_tot_len = 0UL;
  char *p = NULL;
  sl_status_t stat = SL_STATUS_FAIL;

  querry_tot_len = sl_strnlen((char *)uri_querry_request, COAP_RD_MAX_QUERRY_LENGTH);
  parsed->querry_pattern.len = 0;

  for (size_t i = 0; i < COAP_RD_ATTR_COUNT; ++i) {
    // skip if there isn't querry str
    if (_attributes[i].querry.str == NULL) {
      continue;
    }

    parsed->querry_pattern.str = strstr(uri_querry_request, _attributes[i].querry.str);

    if (parsed->querry_pattern.str != NULL) {
      parsed->attr = &_attributes[i];
      p = (char *)parsed->querry_pattern.str + parsed->attr->querry.len;
      parsed->querry_pattern.str = _check_str_buff_ptr(uri_querry_request, querry_tot_len, p) ? p : NULL;
      parsed->querry_pattern.len = sl_strnlen((char *)parsed->querry_pattern.str, COAP_RD_MAX_QUERRY_LENGTH);
      stat = SL_STATUS_OK;
      break;
    }
  }

  return stat;
}

__STATIC_INLINE bool _is_discovery_request(const char *uri_path_str)
{
  return (bool) (!strncmp(uri_path_str, SLI_WISUN_COAP_RD_CORE_STR, SL_WISUN_COAP_URI_PATH_MAX_SIZE));
}

__STATIC_INLINE bool _is_uri_querry(const sl_wisun_coap_packet_t * const packet)
{
  return (bool) (packet->options_list_ptr != NULL
                 && packet->options_list_ptr->uri_query_ptr != NULL
                 && packet->options_list_ptr->uri_query_len);
}

__STATIC_INLINE const char * _get_resource_attr(const sl_wisun_coap_rhnd_resource_t * const resource,
                                                const coap_rd_attribute_t * const attr)
{
  switch (attr->type) {
    case COAP_RD_RT: return resource->data.resource_type;
    case COAP_RD_IF: return resource->data.interface;
    default:         return NULL;
  }
}

static bool _is_pattern_matched(const sl_wisun_coap_rhnd_resource_t * const resource,
                                const coap_rd_querry_parse_t * const parsed)
{
  int32_t r            = 0L;
  const char *attr_val = NULL;

  // get resource attribute
  attr_val = _get_resource_attr(resource, parsed->attr);
  if (attr_val == NULL) {
    return false;
  }

  // completely match attribute value with pattern string
  r = strncmp(attr_val, parsed->querry_pattern.str, COAP_RD_MAX_QUERRY_LENGTH);

  return !r ? true : false;
}

static sl_status_t _add_resource(sl_wisun_coap_rhnd_resource_t *resource,
                                 coap_rd_querry_parse_t * parsed)
{
  sl_wisun_coap_rhnd_resource_t *iter = NULL;
  sl_wisun_coap_rhnd_resource_t *tail = NULL;
  sl_wisun_coap_rhnd_resource_t *rs   = NULL;

  // Empty list
  if (parsed->resources == NULL) {
    rs = sl_wisun_coap_malloc(sizeof(sl_wisun_coap_rhnd_resource_t));
    if (rs == NULL) {
      return SL_STATUS_FAIL;
    }
    memcpy(rs, resource, sizeof(sl_wisun_coap_rhnd_resource_t));
    rs->next = NULL;
    parsed->resources = rs;
    return SL_STATUS_OK;
  }

  iter = parsed->resources;
  // move to the end of the list
  while (iter != NULL) {
    tail = iter;
    iter = iter->next;
  }

  rs = sl_wisun_coap_malloc(sizeof(sl_wisun_coap_rhnd_resource_t));
  if (rs == NULL) {
    return SL_STATUS_FAIL;
  }
  memcpy(rs, resource, sizeof(sl_wisun_coap_rhnd_resource_t));
  rs->next = NULL;
  tail->next = rs;

  return SL_STATUS_OK;
}

static void _destroy_resources(const coap_rd_querry_parse_t * const parsed)
{
  sl_wisun_coap_rhnd_resource_t *iter = NULL;
  sl_wisun_coap_rhnd_resource_t *rs   = NULL;

  iter = parsed->resources;

  while (iter != NULL) {
    rs = iter;
    iter = iter->next;
    sl_wisun_coap_free((void *) rs);
  }
}

static sl_status_t _parse_uri_querry(const sl_wisun_coap_rhnd_resource_t * const resources,
                                     const char *uri_querry_request,
                                     coap_rd_querry_parse_t * const dest)
{
  sl_wisun_coap_rhnd_resource_t *iter = NULL;
  sl_status_t stat                    = SL_STATUS_FAIL;

  // clear resource list
  dest->resources = NULL;

  // Get querry properties
  stat = _get_querry(uri_querry_request, dest);
  if (stat == SL_STATUS_FAIL) {
    return stat;
  }

  // Check querry pattern string
  if (!_check_str_cache(&dest->querry_pattern) || dest->attr == NULL) {
    return SL_STATUS_FAIL;
  }

  // iterate resources and add matched resources to linked list
  iter = (sl_wisun_coap_rhnd_resource_t *)resources;
  while (iter != NULL) {
    // if pattern is matched with particular attribute of the resource
    if (iter->discoverable && _is_pattern_matched(iter, dest)) {
      // add resource to linked list of matched resources
      if (_add_resource(iter, dest) == SL_STATUS_FAIL) {
        return SL_STATUS_FAIL;
      }
    }
    iter = iter->next;
  }
  return SL_STATUS_OK;
}

static char *_get_uri_querry_string(const sl_wisun_coap_packet_t * const packet)
{
  char *str = NULL;

  str = sl_wisun_coap_malloc(packet->options_list_ptr->uri_query_len + 1U);
  if (str != NULL) {
    memcpy(str, packet->options_list_ptr->uri_query_ptr,
           packet->options_list_ptr->uri_query_len);
    str[packet->options_list_ptr->uri_query_len] = '\0';
  }
  return str;
}

static size_t _calc_rd_response_str_size(const coap_rd_querry_parse_t * const parsed,
                                         const bool calc_dir)
{
  sl_wisun_coap_rhnd_resource_t *r_iter = NULL;
  str_cache_t *d_iter                   = NULL;
  const coap_rd_attribute_t *attr_ct    = NULL;
  const coap_rd_attribute_t *attr_rt    = NULL;
  const coap_rd_attribute_t *attr_if    = NULL;
  size_t res                            = 0UL;

  // get used attribute values
  attr_ct = _get_attr_by_type(COAP_RD_CT);
  attr_rt = _get_attr_by_type(COAP_RD_RT);
  attr_if = _get_attr_by_type(COAP_RD_IF);

  if (attr_if == NULL || attr_rt == NULL || attr_ct == NULL) {
    return 0UL;
  }

  // calc direcory list length if it's required
  if (calc_dir) {
    d_iter = parsed->dir;

    while (d_iter != NULL) {
      res += __buff_to_strlen(COAP_RD_RESOURCE_DIR_STR_CHARS);
      res += attr_ct->querry.len + attr_ct->def_val.len;
      res += d_iter->len;
      res += 1U; // delimiter
      d_iter = d_iter->next;
    }
  }

  // iterate resources
  r_iter = parsed->resources;

  while (r_iter != NULL) {
    res += __buff_to_strlen(COAP_RD_RESOURCE_URI_STR_CHARS);
    res += sl_strnlen((char *)r_iter->data.uri_path, SL_WISUN_COAP_URI_PATH_MAX_SIZE);
    res += attr_rt->querry.len;
    res += sl_strnlen((char *)r_iter->data.resource_type, COAP_RD_MAX_QUERRY_LENGTH);
    res += attr_if->querry.len;
    res += sl_strnlen((char *)r_iter->data.interface, COAP_RD_MAX_QUERRY_LENGTH);
    res += 1U; // delimiter
    r_iter = r_iter->next;
  }

  // remove last ',' delimiter
  if (res > 0UL) {
    --res;
  }

  return res;
}

static size_t _get_first_level_dir_len(const char *uri_path)
{
  const char *p = uri_path;
  size_t tot_uri_p_len = 0UL;
  size_t str_len = 0UL;

  tot_uri_p_len = sl_strnlen((char *)uri_path, SL_WISUN_COAP_URI_PATH_MAX_SIZE);

  // validate uri path
  if ( !tot_uri_p_len || *p != '/') {
    return 0UL;
  }

  // skip leading '/'
  ++p;

  while (_check_str_buff_ptr(uri_path, tot_uri_p_len, p)) {
    if (*p == '/') {
      str_len = p - uri_path;
      break;
    }
    ++p;
  }
  return str_len;
}

static sl_status_t _add_dir_to_list(const char *uri_path, coap_rd_querry_parse_t * const dest)
{
  str_cache_t *dir  = NULL;
  str_cache_t *iter = NULL;
  str_cache_t *tail = NULL;
  size_t len        = 0UL;

  // Get first level dir
  len = _get_first_level_dir_len(uri_path);
  if (!len) {
    return SL_STATUS_FAIL;
  }

  // First dir
  if (dest->dir == NULL) {
    dir = sl_wisun_coap_malloc(sizeof(str_cache_t));
    if (dir == NULL) {
      return SL_STATUS_FAIL;
    }
    dest->dir = dir;
    dest->dir->str = uri_path;
    dest->dir->len = len;
    dest->dir->next = NULL;
    return SL_STATUS_OK;
  }

  iter = dest->dir;

  // check already added and move to the end of the list
  while (iter != NULL) {
    if (iter->len == len && !memcmp(iter->str, uri_path, iter->len)) {
      return SL_STATUS_FAIL;
    }
    tail = iter;
    iter = iter->next;
  }

  // Allocate new dir element
  dir = sl_wisun_coap_malloc(sizeof(str_cache_t));
  if (dir == NULL) {
    return SL_STATUS_FAIL;
  }

  // fill with params
  dir->str = uri_path;
  dir->len = len;
  dir->next = NULL;

  // add to tail
  tail->next = dir;

  return SL_STATUS_OK;
}

static void _destroy_dir_list(coap_rd_querry_parse_t * const dest)
{
  str_cache_t *iter = NULL;
  str_cache_t *dir  = NULL;

  iter = dest->dir;

  while (iter != NULL) {
    dir = iter;
    iter = iter->next;
    sl_wisun_coap_free((void *) dir);
  }
}

static void _parse_resource_dir(const sl_wisun_coap_rhnd_resource_t * const resources,
                                coap_rd_querry_parse_t * const dest)
{
  sl_wisun_coap_rhnd_resource_t *iter = NULL;

  iter = (sl_wisun_coap_rhnd_resource_t *) resources;
  while (iter != NULL) {
    (void) _add_dir_to_list(iter->data.uri_path, dest);
    iter = iter->next;
  }
}

static char *_print_dir_to_buff(char * const buf,
                                const str_cache_t * const dir,
                                size_t * const remaind_str_size)
{
  char *str = buf;
  char *tmp = NULL;
  int32_t r = 0L;

  tmp = _sc_to_str(dir);
  if (tmp == NULL) {
    return NULL;
  }

  r = snprintf(str, *remaind_str_size + 1U, COAP_RD_DIR_TEMPLATE_STR_FORMAT, tmp);

  _destroy_str(tmp);

  if (r >= 0L && (size_t)r <= *remaind_str_size) {
    str += r;
    *remaind_str_size -= r;
    return str;
  }

  return NULL;
}

static char *_print_resource_to_buff(char * const buf,
                                     const sl_wisun_coap_rhnd_resource_t * const resource,
                                     size_t * const remaind_str_size)
{
  char *str = buf;
  int32_t r  = 0L;

  r = snprintf(str, *remaind_str_size + 1U,
               COAP_RD_RESOURCE_TEMPLATE_STR_FORMAT,
               resource->data.uri_path,
               resource->data.resource_type,
               resource->data.interface);

  if (r >= 0L && (size_t)r <= *remaind_str_size) {
    str += r;
    *remaind_str_size -= r;
    return str;
  }

  return NULL;
}

static char *_print_delimiter_to_buff(char * const buf,
                                      size_t * const remaind_str_size)
{
  char *str = buf;
  int32_t r  = 0L;

  r = snprintf(str, *remaind_str_size + 1U, "%c", COAP_RD_RESOURCE_DELIMITER_CHAR);
  if (r >= 0L && (size_t)r <= *remaind_str_size) {
    str += r;
    *remaind_str_size -= r;
    return str;
  }
  return NULL;
}

static char *_build_resp_payload_str(const coap_rd_querry_parse_t * const parse,
                                     const size_t max_str_length,
                                     const bool add_dir_list)
{
  char *str                             = NULL;
  char *p                               = NULL;
  sl_wisun_coap_rhnd_resource_t *r_iter = NULL;
  str_cache_t *d_iter                   = NULL;
  size_t remaind_str_size               = 0UL;

  str = (char *) sl_wisun_coap_malloc(max_str_length + 1U);
  remaind_str_size = max_str_length;
  if (str == NULL) {
    return NULL;
  }

  p = str;
  // iterate lists
  if (add_dir_list) {
    d_iter = parse->dir;

    while (d_iter != NULL) {
      p = _print_dir_to_buff(p, d_iter, &remaind_str_size);
      p = _print_delimiter_to_buff(p, &remaind_str_size);
      d_iter = d_iter->next;
    }
  }

  // iterate resources
  r_iter = parse->resources;

  while (r_iter != NULL) {
    p = _print_resource_to_buff(p, r_iter, &remaind_str_size);
    if (r_iter->next != NULL) {
      p = _print_delimiter_to_buff(p, &remaind_str_size);
    }
    r_iter = r_iter->next;
  }
  // terminate string
  str[max_str_length] = '\0';

  return str;
}

static sl_status_t _filter_by_dirs(const char *uri_path,
                                   const sl_wisun_coap_rhnd_resource_t * const resources,
                                   coap_rd_querry_parse_t * const parse)
{
  sl_wisun_coap_rhnd_resource_t *r_iter = NULL;
  str_cache_t *d_iter                   = NULL;
  size_t uri_path_len                   = 0UL;
  size_t first_lev_dir_len              = 0UL;

  // calculate uri path length
  uri_path_len = sl_strnlen((char *) uri_path, SL_WISUN_COAP_URI_PATH_MAX_SIZE);

  // iterate directories
  d_iter = parse->dir;
  while (d_iter != NULL) {
    // if uri path is matched with directory
    if (uri_path_len == d_iter->len
        && !memcmp(uri_path, d_iter->str, d_iter->len)) {
      // find and add all resources for directory
      r_iter = (sl_wisun_coap_rhnd_resource_t * ) resources;
      while (r_iter != NULL) {
        first_lev_dir_len = _get_first_level_dir_len(r_iter->data.uri_path);
        if (r_iter->discoverable
            && first_lev_dir_len == uri_path_len
            && !memcmp(d_iter->str, r_iter->data.uri_path, d_iter->len)) {
          if (_add_resource(r_iter, parse) == SL_STATUS_FAIL) {
            return SL_STATUS_FAIL;
          }
        }
        r_iter = r_iter->next;
      }

      // only one match is possible
      break;
    }
    d_iter = d_iter->next;
  }
  // if this is not a first level dir, return fail
  return parse->resources == NULL ? SL_STATUS_FAIL : SL_STATUS_OK;
}

static sl_status_t _add_all_discoverable_resource(const sl_wisun_coap_rhnd_resource_t * const resources,
                                                  coap_rd_querry_parse_t const * parse)
{
  sl_wisun_coap_rhnd_resource_t *iter = NULL;

  iter = (sl_wisun_coap_rhnd_resource_t *) resources;
  while (iter != NULL) {
    if (iter->discoverable && _add_resource(iter, (coap_rd_querry_parse_t *) parse) == SL_STATUS_FAIL) {
      return SL_STATUS_FAIL;
    }
    iter = iter->next;
  }
  return SL_STATUS_OK;
}

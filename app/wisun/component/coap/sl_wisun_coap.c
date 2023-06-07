/***************************************************************************//**
 * @file
 * @brief Wi-SUN CoAP handler
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "sl_wisun_coap.h"
#include "sl_wisun_coap_rhnd.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Release coap mutex and return
#define __release_wisun_coap_mtx_and_ret() \
  do {                                     \
    _wisun_coap_mutex_release();           \
    return;                                \
  } while (0)

/// Release coap mutex and return with value
#define __release_wisun_coap_mtx_and_retval(__value) \
  do {                                               \
    _wisun_coap_mutex_release();                     \
    return (__value);                                \
  } while (0)

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Default CoAP TX implementation
 * @details Empty function, for coap lib
 * @param[in,out] packet_data Packet data
 * @param[out] packet_data_size Packaet size
 * @param[out] addr Address
 * @param[in,out] param Param
 * @return uint8_t res
 *****************************************************************************/
static uint8_t _default_coap_tx_callback(uint8_t *packet_data,
                                         uint16_t packet_data_size,
                                         sn_nsdl_addr_s *addr,
                                         void *param);

/**************************************************************************//**
 * @brief Default CoAP RX implementation
 * @details Empty function for CoAP lib
 * @param[in,out] header Header
 * @param[in,out] addr Address
 * @param[in,out] param Params
 * @return int8_t res
 *****************************************************************************/
static int8_t _default_coap_rx_callback(sn_coap_hdr_s *header,
                                        sn_nsdl_addr_s *addr,
                                        void *param);

/**************************************************************************//**
 * @brief Internal Mutex acquire
 * @details Simple inline function with assert
 *****************************************************************************/
__STATIC_INLINE void _wisun_coap_mutex_acquire(void);

/**************************************************************************//**
 * @brief Internal Mutex release
 * @details Simple inline function with assert
 *****************************************************************************/
__STATIC_INLINE void _wisun_coap_mutex_release(void);

/**************************************************************************//**
 * @brief Internal pretty buffer printer
 * @details Print buffers with given length, optionally in hex format
 * @param[in] buff_ptr buffer pointer to print
 * @param[in] len size of the buffer
 * @param[in] hex_format enable or disable hex format
 *****************************************************************************/
__STATIC_INLINE void _pretty_buff_print(const uint8_t *buff_ptr,
                                        const uint16_t len,
                                        const bool hex_format);
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Wisun internal CoAP handler
 *****************************************************************************/
static sl_wisun_coap_t _coap;

/**************************************************************************//**
 * @brief Wi-SUN CoAP mutex
 *****************************************************************************/
static osMutexId_t _wisun_coap_mtx;

/**************************************************************************//**
 * @brief Wi-SUN CoAP mutex attribute
 *****************************************************************************/
static const osMutexAttr_t _wisun_coap_mtx_attr = {
  .name      = "WisunCoapMutex",
  .attr_bits = osMutexRecursive,
  .cb_mem    = NULL,
  .cb_size   = 0U
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* Init CoAP descriptor */
void sl_wisun_coap_init(const sl_wisun_coap_tx_callback tx_callback,
                        const sl_wisun_coap_rx_callback rx_callback,
                        const sl_wisun_coap_version_t   version)
{
  // init wisun coap mutex
  _wisun_coap_mtx = osMutexNew(&_wisun_coap_mtx_attr);
  assert(_wisun_coap_mtx != NULL);

  _wisun_coap_mutex_acquire();

#if SL_WISUN_COAP_MEM_USE_STATIC_MEMORY_POOL
  // init memory
  _wisun_coap_mem_init();
#endif
  // init handler
  _coap.malloc      = sl_wisun_coap_malloc;                       // malloc
  _coap.free        = sl_wisun_coap_free;                         // free
  _coap.tx_callback = tx_callback == NULL
                      ? &_default_coap_tx_callback : tx_callback; // tx callback
  _coap.rx_callback = rx_callback == NULL
                      ? &_default_coap_rx_callback : rx_callback; // rx callback
  _coap.version     = version;                                    // coap version

  // lib handler init
  _coap.handler     = sn_coap_protocol_init(_coap.malloc,
                                            _coap.free,
                                            _coap.tx_callback,
                                            _coap.rx_callback);

  _wisun_coap_mutex_release();

  sl_wisun_coap_rhnd_init();
}

/* Wi-SUN CoAP malloc */
void *sl_wisun_coap_malloc(uint16_t size)
{
  void *p_mem;
  _wisun_coap_mutex_acquire();
  p_mem = _wisun_coap_mem_malloc(size);
  _wisun_coap_mutex_release();
  return p_mem;
}

/* Wi-SUN CoAP free */
void sl_wisun_coap_free(void *addr)
{
  _wisun_coap_mutex_acquire();
  _wisun_coap_mem_free(addr);
  _wisun_coap_mutex_release();
}

/* Wi-SUN CoAP parser */
sl_wisun_coap_packet_t* sl_wisun_coap_parser(uint16_t packet_data_len,
                                             uint8_t *packet_data)
{
  sl_wisun_coap_packet_t* res;
  _wisun_coap_mutex_acquire();
  res = sn_coap_parser(_coap.handler,
                       packet_data_len,
                       packet_data,
                       &_coap.version);
  _wisun_coap_mutex_release();
  return res;
}

/* Wi-SUN CoAP builder calculate size */
uint16_t sl_wisun_coap_builder_calc_size(const sl_wisun_coap_packet_t *message)
{
  uint16_t res;
  res = sn_coap_builder_calc_needed_packet_data_size(message);
  return res;
}

/* Wi-SUN CoAP builder */
int16_t sl_wisun_coap_builder(uint8_t *dest_buff,
                              const sl_wisun_coap_packet_t *message)
{
  int16_t res;
  res = sn_coap_builder(dest_buff, message);
  return res;
}

/* Wi-SUN CoAP parser */
sl_wisun_coap_packet_t *sl_wisun_coap_build_response(const sl_wisun_coap_packet_t *req,
                                                     sl_wisun_coap_message_code_t msg_code)
{
  sl_wisun_coap_packet_t * res;
  _wisun_coap_mutex_acquire();
  res = sn_coap_build_response(_coap.handler, req, (uint8_t) msg_code);
  _wisun_coap_mutex_release();
  return res;
}

/* Wi-SUN CoAP print packet */
void sl_wisun_coap_print_packet(const sl_wisun_coap_packet_t *packet, const bool hex_format)
{
  if (packet == NULL) {
    return;
  }
  _wisun_coap_mutex_acquire();

  // according to JSON shape the print put together
  // start of the JSON
  printf("{\n");

  printf("  \"token_len\": %u,\n", packet->token_len);
  printf("  \"coap_status\": %u,\n", packet->coap_status);
  printf("  \"msg_code\": %u,\n", packet->msg_code);
  printf("  \"msg_type\": %u,\n", packet->msg_type);
  printf("  \"content_format\": %u,\n", packet->content_format);
  printf("  \"msg_id\": %u,\n", packet->msg_id);
  printf("  \"payload_len\": %u,\n", packet->payload_len);
  printf("  \"uri_path_len\": %u,\n", packet->uri_path_len);

  // token
  printf("  \"token\": \"");
  if (!packet->token_len) {
    printf("n/a\",\n");
  } else {
    _pretty_buff_print(packet->token_ptr, (uint16_t) packet->token_len, hex_format);
    printf("\",\n");
  }

  // uri path
  printf("  \"uri_path\": \"");
  if (!packet->uri_path_len) {
    printf("n/a\",\n");
  } else {
    _pretty_buff_print(packet->uri_path_ptr, packet->uri_path_len, hex_format);
    printf("\",\n");
  }

  // payload
  printf("  \"payload\": ");
  if (!packet->payload_len) {
    printf("\"n/a\",\n");
  } else {
    printf("%s", packet->content_format == COAP_CT_JSON ? "\n" : "\"");
    _pretty_buff_print(packet->payload_ptr, packet->payload_len, hex_format);
    printf("%s", packet->content_format == COAP_CT_JSON ? "\n" : "\"");
  }
  // end of JSON
  printf("}\n");

  _wisun_coap_mutex_release();
}

char * sl_wisun_coap_get_uri_path_str(const sl_wisun_coap_packet_t * const packet)
{
  char *uri_path  = NULL;
  char *p         = NULL;
  size_t buff_len = 0UL;

  // Check packet
  if (packet == NULL
      || packet->uri_path_ptr == NULL
      || !packet->uri_path_len) {
    return NULL;
  }

  // Allocate buffer to string
  buff_len = packet->uri_path_len + 2U;
  uri_path = (char *)sl_wisun_coap_malloc(buff_len);
  if (uri_path == NULL) {
    return NULL;
  }

  // Add '/' if it's missing
  if (packet->uri_path_ptr[0U] != '/') {
    uri_path[0U] = '/';
    p = &uri_path[1U];
  } else {
    p = uri_path;
  }

  memcpy(p, packet->uri_path_ptr, packet->uri_path_len);

  // Terminate string buffer
  uri_path[buff_len - 1] = 0U;

  return uri_path;
}

/* Wi-SUN CoAP destroy packet */
void sl_wisun_coap_destroy_packet(sl_wisun_coap_packet_t *packet)
{
  sn_coap_parser_release_allocated_coap_msg_mem(_coap.handler, packet);
}

/* Wi-SUN CoAP get lib handler */
const sl_wisun_coap_handle_t* sl_wisun_coap_get_lib_handler(void)
{
  return _coap.handler;
}

char * sl_wisun_coap_get_payload_str(const sl_wisun_coap_packet_t * const packet)
{
  char *str = NULL;
  if (packet == NULL
      || !packet->payload_len
      || packet->payload_ptr == NULL) {
    return NULL;
  }

  str = (char *)sl_wisun_coap_malloc(packet->payload_len + 1U);
  if (str == NULL) {
    return NULL;
  }
  memcpy(str, packet->payload_ptr, packet->payload_len);
  str[packet->payload_len] = '\0';
  return str;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

/* Default CoAP TX callback */
static uint8_t _default_coap_tx_callback(uint8_t *packet_data, uint16_t packet_data_size,
                                         sn_nsdl_addr_s *addr, void *param)
{
  (void) packet_data;
  (void) packet_data_size;
  (void) addr;
  (void) param;
  return 0;
}

/* Default CoAP RX callback */
static int8_t _default_coap_rx_callback(sn_coap_hdr_s *header, sn_nsdl_addr_s *addr, void *param)
{
  (void) header;
  (void) addr;
  (void) param;
  return 0;
}

/* Mutex acquire */
__STATIC_INLINE void _wisun_coap_mutex_acquire(void)
{
  if (osKernelGetState() == osKernelRunning) {
    assert(osMutexAcquire(_wisun_coap_mtx, osWaitForever) == osOK);
  }
}

/* Mutex release */
__STATIC_INLINE void _wisun_coap_mutex_release(void)
{
  if (osKernelGetState() == osKernelRunning) {
    assert(osMutexRelease(_wisun_coap_mtx) == osOK);
  }
}

/* Pretty buffer printer */
__STATIC_INLINE void _pretty_buff_print(const uint8_t *buff_ptr, const uint16_t len, const bool hex_format)
{
  if (buff_ptr == NULL || len == 0) {
    return;
  }
  for (uint16_t i = 0; i < len; ++i) {
    if (hex_format) {
      printf(i < len - 1 ? "0x%02x " : "0x%02x", buff_ptr[i]);
    } else {
      printf("%c", buff_ptr[i]);
    }
  }
}

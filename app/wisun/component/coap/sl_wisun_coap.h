/***************************************************************************//**
 * @file
 * @brief Wi-SUN CoAP handler
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

#ifndef __SL_WISUN_COAP_H__
#define __SL_WISUN_COAP_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "sn_config.h"
#include "sn_coap_protocol.h"
#include "sn_coap_header.h"
#include "sl_wisun_types.h"
#include "sli_wisun_coap_mem.h"

/**************************************************************************//**
 * @addtogroup SL_WISUN_COAP_API CoAP
 * @ingroup SL_WISUN_COAP
 * @{
 *****************************************************************************/

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

#if  defined(SL_COAP_UNIT_TEST)
#warning Unit test enabled
/// CoAP Service loop for unit tests
#define SL_COAP_SERVICE_LOOP()       for (uint8_t i = 0U; i < SL_COAP_SERVICE_LOOP_EXPECTED_CNT; ++i)
#else
/// CoAP Service loop
#define SL_COAP_SERVICE_LOOP()       while (1)
#endif

/**************************************************************************//**
 * @defgroup SL_WISUN_COAP_TYPES CoAP type definitions
 * @ingroup SL_WISUN_COAP
 * @{
 *****************************************************************************/

/// Maximum size of the URI path string
#define SL_WISUN_COAP_URI_PATH_MAX_SIZE   (128U)

/// Wi-SUN CoAP handler for Wi-SUN component
typedef struct coap_s sl_wisun_coap_handle_t;

/// Wi-SUN CoAP malloc function pointer typedef
typedef void *(*sl_wisun_coap_malloc_t)(uint16_t size);

/// Wi-SUN CoAP free function pointer typedef
typedef void (*sl_wisun_coap_free_t)(void *mem);

/// Wi-SUN CoAP version typedef
typedef coap_version_e sl_wisun_coap_version_t;

/// Wi-SUN CoAP TX callback function pointer typedef
typedef uint8_t (*sl_wisun_coap_tx_callback)(uint8_t *packet_data, uint16_t packet_data_size,
                                             sn_nsdl_addr_s *addr, void *param);
/// Wi-SUN CoAP RX callback function pointer typedef
typedef int8_t (*sl_wisun_coap_rx_callback)(sn_coap_hdr_s *header, sn_nsdl_addr_s *addr, void *param);

/// Wi-SUN CoAP message typedef
typedef sn_coap_hdr_s sl_wisun_coap_packet_t;

/// Wi-SUN CoAP message code typedef
typedef sn_coap_msg_code_e sl_wisun_coap_message_code_t;

/// Wi-SUN CoAP message type typedef
typedef sn_coap_msg_type_e sl_wisun_coap_message_type_t;

/// Wi-SUN CoAP option number typedef
typedef sn_coap_option_numbers_e sl_wisun_coap_option_num_t;

/// Wi-SUN CoAP option list typedef
typedef sn_coap_options_list_s sl_wisun_coap_option_list_t;

/// Wi-SUN CoAP descriptor structure
typedef struct sl_wisun_coap {
  /// lib handler
  sl_wisun_coap_handle_t*    handler;
  /// malloc function
  sl_wisun_coap_malloc_t     malloc;
  /// free function
  sl_wisun_coap_free_t       free;
  /// TX callback
  sl_wisun_coap_tx_callback  tx_callback;
  /// RX callback
  sl_wisun_coap_rx_callback  rx_callback;
  /// CoAP version
  sl_wisun_coap_version_t    version;
} sl_wisun_coap_t;

/** @} (end SL_WISUN_COAP_TYPES) */

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Initialize Wi-SUN CoAP.
 * @details Set the Wi-SUN CoAP internal descriptor.
 * @param[in] tx_callback TX callback, if it's NULL, the default callback is applied
 * @param[in] rx_callback RX callback, if it's NULL, the default callback is applied
 * @param[in] version CoAP version
 *****************************************************************************/
void sl_wisun_coap_init(const sl_wisun_coap_tx_callback tx_callback,
                        const sl_wisun_coap_rx_callback rx_callback,
                        const sl_wisun_coap_version_t   version);

/**************************************************************************//**
 * @brief Initialize Wi-SUN CoAP default.
 * @details Initializes the internal descriptor with default values.
 *****************************************************************************/
__STATIC_INLINE void sl_wisun_coap_init_default(void)
{
  sl_wisun_coap_init(NULL, NULL, COAP_VERSION_1);
}

/**************************************************************************//**
 * @brief Implement malloc.
 * @details OS-dependent thread-safe implementation.
 * @param size size for malloc
 * @return void* the memory pointer
 *****************************************************************************/
void *sl_wisun_coap_malloc(uint16_t size);

/**************************************************************************//**
 * @brief Free Wi-SUN CoAP.
 * @details OS-dependent thread-safe implementation.
 * @param addr address ptr
 *****************************************************************************/
void sl_wisun_coap_free(void *addr);

/**************************************************************************//**
 * @brief CoAP parser wrapper function.
 * @details Used sn_coap_parser
 * @param[in] packet_data_len packet data size
 * @param[in] packet_data packet data ptr
 * @return sl_wisun_coap_packet_t* Parsed packet pointer
 *****************************************************************************/
sl_wisun_coap_packet_t* sl_wisun_coap_parser(uint16_t packet_data_len,
                                             uint8_t *packet_data);

/**************************************************************************//**
 * @brief CoAP packet calc size wrapper.
 * @details Used sn_coap_builder_calc_needed_packet_data_size.
 * @param[in] message message ptr
 * @return uint16_t size
 *****************************************************************************/
uint16_t sl_wisun_coap_builder_calc_size(const sl_wisun_coap_packet_t *message);

/**************************************************************************//**
 * @brief CoAP message builder Wi-SUN.
 * @details Used sl_wisun_coap_builder.
 * @param[out] dest_buff destination buffer for raw message
 * @param[in] message message structure
 * @return int16_t On success bytes of built message,
 *                 on failure -1 if CoAP header structure is wrong
 *                            -2 if NULL ptr set as argument
 *****************************************************************************/
int16_t sl_wisun_coap_builder(uint8_t *dest_buff,
                              const sl_wisun_coap_packet_t *message);

/**************************************************************************//**
 * @brief Build generic response for request wrapper function.
 * @details Used sn_coap_build_response.
 * @param[in] req request
 * @param[in] msg_code message code to build
 * @return sl_wisun_coap_header_t* built packet ptr on the heap
 *****************************************************************************/
sl_wisun_coap_packet_t *sl_wisun_coap_build_response(const sl_wisun_coap_packet_t *req,
                                                     sl_wisun_coap_message_code_t msg_code);

/**************************************************************************//**
 * @brief Print CoAP packets and all of attached buffer, payload, token, uri_path.
 * @details Pretty printer function, with hex format option for buffers
 * @param[in] packet packet to print
 * @param[in] hex_format hex format bool to decide buffer print format
 *****************************************************************************/
void sl_wisun_coap_print_packet(const sl_wisun_coap_packet_t *packet,
                                const bool hex_format);

/**************************************************************************//**
 * @brief Prepare URI path string
 * @details '\0' terminated string in the heap, it must be freed
 * @param[in] packet Packet
 * @return char* URI path string, NULL on error
 *****************************************************************************/
char * sl_wisun_coap_get_uri_path_str(const sl_wisun_coap_packet_t * const packet);

/**************************************************************************//**
 * @brief Destroy URI path string
 * @details Call free on allocated pointer
 * @param[in] uri_str URI string ptr
 *****************************************************************************/
__STATIC_INLINE void sl_wisun_coap_destroy_uri_path_str(char *uri_str)
{
  sl_wisun_coap_free((void *) uri_str);
}

/**************************************************************************//**
 * @brief Get the library handler pointer from the internal handler structure.
 * @details Not thread safe! It is needed only to use Pelion mbed-coap library functions
 * @return const sl_wisun_coap_handle_t* pointer to the lib handler
 *****************************************************************************/
const sl_wisun_coap_handle_t* sl_wisun_coap_get_lib_handler(void);

/**************************************************************************//**
 * @brief Destroy packet.
 * @details It must be used to avoid memory leaks!
 *          Free the all of allocated buffer for packet
 * @param packet packet
 *****************************************************************************/
void sl_wisun_coap_destroy_packet(sl_wisun_coap_packet_t *packet);

/**************************************************************************//**
 * @brief Prepare payload string
 * @details '\0' terminated string in the heap, it must be freed
 * @param[in] packet Packet
 * @return char* payload string, NULL on error
 *****************************************************************************/
char * sl_wisun_coap_get_payload_str(const sl_wisun_coap_packet_t * const packet);

/**************************************************************************//**
 * @brief Destroy payload string
 * @details '\0' terminated string in the heap, it must be freed
 * @param[in] str String
 *****************************************************************************/
__STATIC_INLINE void sl_wisun_coap_destroy_payload_str(char *str)
{
  sl_wisun_coap_free((void *) str);
}

/** @}*/

#ifdef __cplusplus
}
#endif
#endif

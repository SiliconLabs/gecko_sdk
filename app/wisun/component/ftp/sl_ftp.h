/***************************************************************************//**
 * @file
 * @brief File Transfer Portocol header file
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __SL_FTP_H__
#define __SL_FTP_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "sl_common.h"
#include "cmsis_os2.h"
#include "sl_ftp_config.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif

/// FTP debug macro function
#if defined(SL_FTP_DEBUG)
#define sl_ftp_debug(format, ...)  \
  do {                             \
    printf("[FTP_DEBUG] ");        \
    printf(format, ##__VA_ARGS__); \
  } while (0)
#else
#define sl_ftp_debug(format, ...) \
  (void) 0UL;
#endif

/// FTP Localhost string
#define SL_FTP_LOCAL_HOST_STR               "::"

/// FTP invalid socket ID
#define SL_FTP_INVALID_SOCKID               (-1)

/// FTP error value
#define SL_FTP_ERROR                        SL_FTP_INVALID_SOCKID

#if SL_FTP_ENABLE_TFTP_PROTOCOL

/// TFTP Localhost string (alias)
#define SL_TFTP_LOCAL_HOST_STR              SL_FTP_LOCAL_HOST_STR

/// TFTP invalid socket ID (alias)
#define SL_TFTP_INVALID_SOCKID              SL_FTP_INVALID_SOCKID

/// TFTP error value (alias)
#define SL_TFTP_ERROR                       SL_FTP_ERROR

#endif
// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief FTP Init
 * @details Initialize FTP service
 ******************************************************************************/
void sl_ftp_init(void);

/***************************************************************************//**
 * @brief Dump buffer
 * @details Util function to dump buffer in hex format
 * @param[in] data_ptr Data ptr
 * @param[in] data_size Data size
 ******************************************************************************/
void sl_ftp_dump_buff(const uint8_t * const data_ptr, const uint16_t data_size);

/***************************************************************************//**
 * @brief Delay ms
 * @details Portable function
 * @param delay_ms Milliseconds
 ******************************************************************************/
void sl_ftp_delay_ms(const uint32_t delay_ms);

/***************************************************************************//**
 * @brief FTP network is connected
 * @details Portable function
 * @return true if network is connected, otherwise false
 ******************************************************************************/
bool sl_ftp_is_network_connected(void);

/***************************************************************************//**
 * @brief FTP get global IP address
 * @details Portable function
 * @return Global address string representation
 ******************************************************************************/
const char * sl_ftp_get_global_addr(void);

/***************************************************************************//**
 * @brief FTP Close
 * @details Portable function
 * @param sockid Socket ID
 * @return int32_t Closed socket ID on success, -1 on error
 ******************************************************************************/
int32_t sl_ftp_socket_close(int32_t sockid);

#if SL_FTP_ENABLE_FTP_PROTOCOL

/***************************************************************************//**
 * @brief FTP TCP socket create
 * @details Portable function
 * @return int32_t Socket ID
 ******************************************************************************/
int32_t sl_ftp_tcp_socket_create(void);

/***************************************************************************//**
 * @brief FTP TCP socket connect
 * @details Portable function
 * @param[in] sockid Socket ID
 * @param[in] host Host address string
 * @param[in] port Host port
 * @return int32_t 0 on success, -1 on error
 ******************************************************************************/
int32_t sl_ftp_tcp_socket_connect(int32_t sockid, const char *host, uint16_t port);

/***************************************************************************//**
 * @brief FTP TCP send
 * @details Portable function
 * @param sockid Socket ID
 * @param buff Buffer to send
 * @param len Length of buffer
 * @return int32_t Count of sent bytes on success, -1 on error
 ******************************************************************************/
int32_t sl_ftp_tcp_socket_send(int32_t sockid, const void *buff, uint32_t len);

/***************************************************************************//**
 * @brief FTP TCP receive
 * @details Portable function
 * @param sockid Socket ID
 * @param buff Buffer storage for receiving
 * @param len Length of buffer
 * @return int32_t Count of received bytes on success, -1 on error
 ******************************************************************************/
int32_t sl_ftp_tcp_socket_recv(int32_t sockid, void *buff, uint32_t len);

#endif

#if SL_FTP_ENABLE_TFTP_PROTOCOL

/// Define SL_TFTP_DEBUG
#if defined(SL_FTP_DEBUG)
#ifndef SL_TFTP_DEBUG
#define SL_TFTP_DEBUG
#endif
#endif

/// Define tftp debug print
#define sl_tftp_debug     sl_ftp_debug

/***************************************************************************//**
 * @brief TFTP Dump buffer
 * @details Alias function
 *
 * @param[in] data_ptr Data ptr
 * @param[in] data_size Data size
 ******************************************************************************/
__STATIC_INLINE void sl_tftp_dump_buff(const uint8_t * const data_ptr, const uint16_t data_size)
{
  sl_ftp_dump_buff(data_ptr, data_size);
}

/***************************************************************************//**
 * @brief TFTP Delay ms
 * @details Alias function
 * @param delay_ms Milliseconds
 ******************************************************************************/
__STATIC_INLINE void sl_tftp_delay_ms(const uint32_t delay_ms)
{
  sl_ftp_delay_ms(delay_ms);
}

/***************************************************************************//**
 * @brief TFTP network is connected
 * @details Alias function
 * @return true if network is connected, otherwise false
 ******************************************************************************/
__STATIC_INLINE bool sl_tftp_is_network_connected(void)
{
  return sl_ftp_is_network_connected();
}

/***************************************************************************//**
 * @brief TFTP get global IP address
 * @details Portable function
 * @return Global address string representation
 ******************************************************************************/
__STATIC_INLINE const char * sl_tftp_get_global_addr(void)
{
  return sl_ftp_get_global_addr();
}

/***************************************************************************//**
 * @brief TFTP Close
 * @details Alias function
 * @param sockid Socket ID
 * @return int32_t Closed socket ID on success, -1 on error
 ******************************************************************************/
__STATIC_INLINE int32_t sl_tftp_socket_close(int32_t sockid)
{
  return sl_ftp_socket_close(sockid);
}

/***************************************************************************//**
 * @brief TFTP udp socket create
 * @details Portable function
 * @return int32_t Socket ID
 ******************************************************************************/
int32_t sl_tftp_udp_socket_create(void);

/**************************************************************************//**
 * @brief TFTP Send a message on a UDP socket.
 * @details Preferred in datagram mode (UDP).
 * @param[in] sockid socket ID
 * @param[in] buff buffer pointer to send
 * @param[in] len length of data to send
 * @param[in] dest_addr destination address ptr, the structure must be prepared for UDP sockets
 * @return On success, these calls return the number of bytes sent. On error, -1 is returned
 *****************************************************************************/
int32_t sl_tftp_udp_sendto(int32_t sockid, const void *buff, uint32_t len, const void *dest_addr);

/**************************************************************************//**
 * @brief TFTP Receive messages on a UDP socket
 * @details Receives data on a socket whether or not it is connection-oriented.
 * @param[in] sockid socket id
 * @param[out] buff destination buffer ptr
 * @param[in] len length of data to read
 * @param[out] src_addr Source address
 * @return return the number of bytes received, or -1 if an error occurred
 *****************************************************************************/
int32_t sl_tftp_udp_recvfrom(int32_t sockid, void *buff, uint32_t len, void *src_addr);

/**************************************************************************//**
 * @brief Get UDP address bytes
 * @details Create address bytes from host string and port
 * @param[in] host Host string
 * @param[in] port Port
 * @param[in,out] dst Destiantion ptr
 * @param[in] dst_size Destination size
 *****************************************************************************/
void sl_tftp_udp_get_addr_bytes(const char *host,
                                uint16_t port,
                                void * const dst,
                                size_t dst_size);
#endif

#ifdef __cplusplus
}
#endif
#endif

/***************************************************************************//**
 * @file
 * @brief Wi-SUN POSIX File Transfer Portocol portable implementation
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <string.h>
#include <assert.h>
#include "sl_ftp.h"
#include "socket.h"
#include "sl_socket_config.h"
#include "cmsis_os2.h"
#include "sl_wisun_app_core_util.h"
#if SL_FTP_ENABLE_TFTP_PROTOCOL
#include "sl_tftp_clnt.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief Delay ms
 * @details Portable function
 * @param delay_ms Milliseconds
 ******************************************************************************/
void sl_ftp_delay_ms(const uint32_t delay_ms)
{
  (void) osDelay(delay_ms);
}

/***************************************************************************//**
 * @brief FTP network is connected
 * @details Portable function
 * @return true if network is connected, otherwise false
 ******************************************************************************/
bool sl_ftp_is_network_connected(void)
{
  return app_wisun_network_is_connected();
}

/***************************************************************************//**
 * @brief FTP Close
 * @details Portable function
 * @param sockid Socket ID
 * @return int32_t Closed socket ID on success, -1 on error
 ******************************************************************************/
int32_t sl_ftp_socket_close(int32_t sockid)
{
  return close(sockid);
}

#if SL_FTP_ENABLE_FTP_PROTOCOL

/***************************************************************************//**
 * @brief FTP TCP socket create
 * @details Portable function
 * @return int32_t Socket ID
 ******************************************************************************/
int32_t sl_ftp_tcp_socket_create(void)
{
  return socket(AF_WISUN, SOCK_STREAM, IPPROTO_TCP);
}

/***************************************************************************//**
 * @brief FTP TCP socket connect
 * @details Portable function
 * @param[in] sockid Socket ID
 * @param[in] host Host address string
 * @param[in] port Host port
 * @return int32_t 0 on success, -1 on error
 ******************************************************************************/
int32_t sl_ftp_tcp_socket_connect(int32_t sockid, const char *host, uint16_t port)
{
  wisun_addr_t waddr = { 0U };

  if (inet_pton(AF_WISUN, host,
                &waddr.sin6_addr.s6_addr) == SOCKET_RETVAL_ERROR) {
    return SOCKET_RETVAL_ERROR;
  }

  waddr.sin6_family = AF_WISUN;
  waddr.sin6_port = port;

  return connect(sockid, (const struct sockaddr *)&waddr, sizeof(wisun_addr_t));
}

/***************************************************************************//**
 * @brief FTP TCP send
 * @details Portable function
 * @param sockid Socket ID
 * @param buff Buffer to send
 * @param len Length of buffer
 * @return int32_t Count of sent bytes on success, -1 on error
 ******************************************************************************/
int32_t sl_ftp_tcp_socket_send(int32_t sockid, const void *buff, uint32_t len)
{
  return send(sockid, buff, len, 0L);
}

/***************************************************************************//**
 * @brief FTP TCP receive
 * @details Portable function
 * @param sockid Socket ID
 * @param buff Buffer storage for receiving
 * @param len Length of buffer
 * @return int32_t Count of received bytes on success, -1 on error
 ******************************************************************************/
int32_t sl_ftp_tcp_socket_recv(int32_t sockid, void *buff, uint32_t len)
{
  return recv(sockid, buff, len, 0L);
}
#endif

#if SL_FTP_ENABLE_TFTP_PROTOCOL

_Static_assert(SL_SOCKET_BUFFER_SIZE >= (SL_TFTP_DATA_BLOCK_SIZE + sizeof(uint16_t) * 2UL),
               "TFTP: Not enough socket buffer size. SL_SOCKET_BUFFER_SIZE >= (SL_TFTP_DATA_BLOCK_SIZE + 4)");

/***************************************************************************//**
 * @brief TFTP udp socket create
 * @details Portable function
 * @return int32_t Socket ID
 ******************************************************************************/
int32_t sl_tftp_udp_socket_create(void)
{
  return socket(AF_WISUN, SOCK_DGRAM, IPPROTO_UDP);
}

/**************************************************************************//**
 * @brief TFTP Send a message on a UDP socket.
 * @details Preferred in datagram mode (UDP).
 * @param[in] sockid socket ID
 * @param[in] buff buffer pointer to send
 * @param[in] len length of data to send
 * @param[in] dest_addr destination address ptr, the structure must be prepared for UDP sockets
 * @return On success, these calls return the number of bytes sent. On error, -1 is returned
 *****************************************************************************/
int32_t sl_tftp_udp_sendto(int32_t sockid, const void *buff, uint32_t len, const void *dest_addr)
{
  return sendto(sockid, buff, len, 0L, (const struct sockaddr *)dest_addr, sizeof(wisun_addr_t));
}

/**************************************************************************//**
 * @brief TFTP Receive messages on a UDP socket
 * @details Receives data on a socket whether or not it is connection-oriented.
 * @param[in] sockid socket id
 * @param[out] buff destination buffer ptr
 * @param[in] len length of data to read
 * @param[out] src_addr Source address
 * @return return the number of bytes received, or -1 if an error occurred
 *****************************************************************************/
int32_t sl_tftp_udp_recvfrom(int32_t sockid, void *buff, uint32_t len, void *src_addr)
{
  socklen_t addr_len = sizeof(wisun_addr_t);
  return recvfrom(sockid, buff, len, 0L, (struct sockaddr *)src_addr, &addr_len);
}

void sl_tftp_udp_get_addr_bytes(const char *host,
                                uint16_t port,
                                void * const dst,
                                size_t dst_size)
{
  wisun_addr_t waddr = { 0U };

  if (dst == NULL || !dst_size) {
    return;
  }

  if (inet_pton(AF_WISUN, host,
                &waddr.sin6_addr.s6_addr) == SOCKET_RETVAL_ERROR) {
    memset(dst, 0U, dst_size);
  }

  waddr.sin6_family = AF_WISUN;
  waddr.sin6_port = port;

  if (dst_size < sizeof(wisun_addr_t)) {
    memset(dst, 0U, dst_size);
  } else {
    memcpy(dst, &waddr, sizeof(wisun_addr_t));
  }
}

#endif

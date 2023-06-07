/***************************************************************************//**
 * @file
 * @brief File Transfer Portocol portable interface
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

#include "sl_ftp.h"
#include "sl_ftp_config.h"
#if SL_FTP_ENABLE_FTP_PROTOCOL
#include "sl_ftp_clnt.h"
#endif
#if SL_FTP_ENABLE_TFTP_PROTOCOL
#include "sl_tftp_clnt.h"
#endif

void sl_ftp_init(void)
{
#if SL_FTP_ENABLE_FTP_PROTOCOL
  sl_ftp_clnt_service_init();
#endif
#if SL_FTP_ENABLE_TFTP_PROTOCOL
  sl_tftp_clnt_service_init();
#endif
}

/// Print line length
#define SL_FTP_DATA_PRINT_LINE_LEN   20UL

void sl_ftp_dump_buff(const uint8_t * const data_ptr, const uint16_t data_size)
{
  size_t byte_cnt = 0UL;
  for (size_t i = 0; i < data_size; ++i) {
    if (i == (data_size - 1U)) {
      printf("0x%.2x\n", data_ptr[i]);
    } else if (byte_cnt < SL_FTP_DATA_PRINT_LINE_LEN - 1U) {
      printf("0x%.2x, ", data_ptr[i]);
    } else {
      printf("0x%.2x,\n", data_ptr[i]);
    }

    if (byte_cnt == SL_FTP_DATA_PRINT_LINE_LEN - 1U) {
      byte_cnt = 0U;
    } else {
      ++byte_cnt;
    }
  }
  printf("\n");
}

__WEAK void sl_ftp_delay_ms(const uint32_t delay_ms)
{
  (void) delay_ms;
}

__WEAK int32_t sl_ftp_socket_close(int32_t sockid)
{
  (void) sockid;
  return SL_FTP_ERROR;
}

__WEAK bool sl_ftp_is_network_connected(void)
{
  (void) 0UL;
  return false;
}

#if SL_FTP_ENABLE_FTP_PROTOCOL
__WEAK int32_t sl_ftp_tcp_socket_create(void)
{
  (void) 0UL;
  return SL_FTP_ERROR;
}

__WEAK int32_t sl_ftp_tcp_socket_connect(int32_t sockid, const char *host, uint16_t port)
{
  (void) sockid;
  (void) host;
  (void) port;
  return SL_FTP_ERROR;
}

__WEAK int32_t sl_ftp_tcp_socket_send(int32_t sockid, const void *buff, uint32_t len)
{
  (void) sockid;
  (void) buff;
  (void) len;
  return SL_FTP_ERROR;
}

__WEAK int32_t sl_ftp_tcp_socket_recv(int32_t sockid, void *buff, uint32_t len)
{
  (void) sockid;
  (void) buff;
  (void) len;
  return SL_FTP_ERROR;
}
#endif

#if SL_FTP_ENABLE_TFTP_PROTOCOL

__WEAK int32_t sl_tftp_udp_socket_create(void)
{
  return SL_FTP_ERROR;
}

__WEAK int32_t sl_tftp_udp_sendto(int32_t sockid, const void *buff, uint32_t len, const void *dest_addr)
{
  (void) sockid;
  (void) buff;
  (void) len;
  (void) dest_addr;
  return SL_TFTP_ERROR;
}

__WEAK int32_t sl_tftp_udp_recvfrom(int32_t sockid, void *buff, uint32_t len, void *src_addr)
{
  (void) sockid;
  (void) buff;
  (void) len;
  (void) src_addr;
  return SL_TFTP_ERROR;
}
#endif

/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdio.h>
#include <stdlib.h>

#include "socket/socket.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_udp_client.h"

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

/* create tcp client */
void sl_wisun_udp_client_create(void)
{
  int32_t sockid = SOCKET_INVALID_ID; // client socket id

  // create client socket
  sockid = socket(AF_INET6, (SOCK_DGRAM | SOCK_NONBLOCK), IPPROTO_IP);

  if (sockid == SOCKET_INVALID_ID) {
    printf("[Failed to create socket: %ld]\n", sockid);
    return;
  } else {
    printf("[Socket created: %ld]\n", sockid);
  }
}

/* close tcp client socket */
void sl_wisun_udp_client_close(const int32_t sockid)
{
  if (close(sockid) == SOCKET_RETVAL_ERROR) {
    printf("[Failed to close socket: %ld]\n", sockid);
  }
}

/* write to tcp client socket */
void sl_wisun_udp_client_write(const int32_t sockid, const char *remote_ip_address,
                               const uint16_t remote_port, const char *str)
{
  int32_t res;
  static sockaddr_in6_t server_addr;
  if (remote_ip_address == NULL) {
    printf("[Failed: IP address is NULL ptr]\n");
    return;
  }

  if (str == NULL) {
    printf("[Failed: Data to write is NULL ptr]\n");
    return;
  }

  // setting the server address
  server_addr.sin6_family = AF_INET6;
  server_addr.sin6_port = remote_port;
  if (inet_pton(AF_INET6, remote_ip_address,
                &server_addr.sin6_addr) == SOCKET_RETVAL_ERROR) {
    printf("[Invalid IP address: %s]\n", remote_ip_address);
    return;
  }

  res = sendto(sockid, str, strlen(str), 0,
               (const struct sockaddr *) &server_addr, sizeof(server_addr));
  if (res == SOCKET_RETVAL_ERROR) {
    printf("[Failed to send on socket: %ld]\n", sockid);
  }
}

/* read on tcp client socket */
void sl_wisun_udp_client_read(const int32_t sockid, const uint16_t size)
{
  char *c = (char *) app_wisun_malloc((size + 1) * sizeof(char));
  int32_t res;
  static sockaddr_in6_t server_addr;
  socklen_t len = sizeof(server_addr);

  res = recvfrom(sockid, c, size, 0,
                 (struct sockaddr *)&server_addr, &len);
  if (res == SOCKET_RETVAL_ERROR || !res) {
    app_wisun_free(c);
    return;
  }
  printf("%s\r\n", c);
  app_wisun_free(c);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

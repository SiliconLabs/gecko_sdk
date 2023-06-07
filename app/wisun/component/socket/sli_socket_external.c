/***************************************************************************//**
 * @file
 * @brief External socket
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
#include "sl_common.h"
#include "sli_socket_external.h"
#include "sli_socket_hnd.h"

SL_WEAK int32_t sli_socket_external_socket(sock_domain_t domain,
                                           sock_type_t type,
                                           int32_t protocol)
{
  (void) domain;
  (void) type;
  (void) protocol;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_close(int32_t sockfd)
{
  (void) sockfd;
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_bind(int32_t sockfd,
                                         const struct sockaddr *addr,
                                         socklen_t addrlen)
{
  (void) sockfd;
  (void) addr;
  (void) addrlen;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_listen(int32_t sockfd,
                                           int32_t backlog)
{
  (void) sockfd;
  (void) backlog;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_accept(int32_t sockfd,
                                           struct sockaddr *addr,
                                           socklen_t *addrlen)
{
  (void) sockfd;
  (void) addr;
  (void) addrlen;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_send(int32_t sockfd,
                                         const void *buf,
                                         uint32_t len,
                                         int32_t flags)
{
  (void) sockfd;
  (void) buf;
  (void) len;
  (void) flags;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_sendto(int32_t sockfd,
                                           const void *buf,
                                           uint32_t len,
                                           int32_t flags,
                                           const struct sockaddr *dest_addr,
                                           socklen_t addrlen)
{
  (void) sockfd;
  (void) buf;
  (void) len;
  (void) flags;
  (void) dest_addr;
  (void) addrlen;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_recv(int32_t sockfd,
                                         const void *buf,
                                         uint32_t len,
                                         int32_t flags)
{
  (void) sockfd;
  (void) buf;
  (void) len;
  (void) flags;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_recvfrom(int32_t sockfd,
                                             void *buf,
                                             uint32_t len,
                                             int32_t flags,
                                             struct sockaddr *src_addr,
                                             socklen_t *addrlen)
{
  (void) sockfd;
  (void) buf;
  (void) len;
  (void) flags;
  (void) src_addr;
  (void) addrlen;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_getsockopt(int32_t sockfd,
                                               int32_t level,
                                               int32_t optname,
                                               void *optval,
                                               socklen_t *optlen)
{
  (void) sockfd;
  (void) level;
  (void) optname;
  (void) optval;
  (void) optlen;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_setsockopt(int32_t sockfd,
                                               int32_t level,
                                               int32_t optname,
                                               const void *optval,
                                               socklen_t optlen)
{
  (void) sockfd;
  (void) level;
  (void) optname;
  (void) optval;
  (void) optlen;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

SL_WEAK int32_t sli_socket_external_connect(int32_t sockfd,
                                            const struct sockaddr *addr,
                                            socklen_t addrlen)
{
  (void) sockfd;
  (void) addr;
  (void) addrlen;
  sli_socket_hnd_set_errno(EINVAL);
  return SOCKET_RETVAL_ERROR;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

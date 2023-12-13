/***************************************************************************//**
 * @file socket.h
 * @brief socket API
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

#ifndef __SOCKET_H__
#define __SOCKET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include "sl_status.h"
#include "sl_common.h"

/// Socket API error return value
#define SOCKET_RETVAL_ERROR                   (-1L)
/// Socket API OK return value
#define SOCKET_RETVAL_OK                      (0L)
/// Invalid socket ID
#define SOCKET_INVALID_ID                     (SOCKET_RETVAL_ERROR)

/// Initialization value for IPv6 wildcard address
#define IN6ADDR_ANY_INIT { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } }

/**************************************************************************//**
 * @addtogroup SL_WISUN_SOCKET_API Socket API
 * @ingroup SL_WISUN_API
 * @{
 *****************************************************************************/

/** \name Protocol levels used for socket_setsockopt. */
///@{
#define SOL_SOCKET           0   ///< Socket option level
#define SOL_APPLICATION      1   ///< Application socket option level
#define IPPROTO_IPV6        41   ///< IPV6 socket option level
///@}

// For backward compatibility
#define APP_LEVEL_SOCKET     SOL_APPLICATION

/** \name Option names for application level */

/** \name application level socket options
 *
 * application level socket options summary
 *
 * | opt_name              | data type         | set/get         | sendmsg | recvmsg |
 * | :-------------------: | :---------- ----: | :-------------: | :-----: | :-------|
 * | SO_EVENT_MODE         | int16_t           |     Set only    |   No    | Yes     |
 * | SO_NONBLOCK           | int16_t           |     Set only    |   Yes   | Yes     |
 */

///@{
/// Specify event mode of a socket.
/// When set, optval must point to an uint32_t.
///
/// Possible values are:
/// - #SL_WISUN_SOCKET_EVENT_MODE_INDICATION: received data is included in
///   SL_WISUN_MSG_SOCKET_DATA_IND_ID indication
///
/// - #SL_WISUN_SOCKET_EVENT_MODE_POLLING: only the amount of received data is
///   included #SL_WISUN_MSG_SOCKET_DATA_AVAILABLE_IND_ID indication. recv() or
///   recvfrom() shouldbe invoked after indication reception to retrieve data

#define SO_EVENT_MODE           10
#define SOCKET_EVENT_MODE       SO_EVENT_MODE

/// Enable/disable nonblocking mode.
/// This option takes an uint32_t value.
///
/// Possible values are:
///   - (1) enables nonblocking mode
///   - (0) disables nonblocking mode
#define   SO_NONBLOCK             11
///@}

/** \name Option names for socket level. */

/** \name socket level options
 *
 * socket level options summary
 *
 * | opt_name              | data type         | set/get         | sendmsg | recvmsg |
 * | :-------------------: | :---------- ----: | :-------------: | :-----: | :-------|
 * | SO_RCVBUF             | int32_t           |     Set/Get     |   No    | Yes     |
 * | SO_SNDBUF             | int32_t           |     Set/Get     |   Yes   | No      |
 * | SO_SNDLOWAT           | int32_t           |     Set/Get     |   Yes   | No      |
 */

///@{
/// Specify receive buffer size in payload bytes.
/// When set, optval must point to an int32_t.
///
/// 0 means unread data are dropped, unless read in data callback.
#define SO_RCVBUF                    1

/// Specify send buffer size in payload bytes.
/// When set, optval must point to an int32_t.
///
/// Used only for stream sockets.
#define SO_SNDBUF                    2

/// Specify send low water mark in payload bytes.
/// When set, optval must point to an int32_t.
#define SO_SNDLOWAT                  4

///@}


/** \name Option names for IPv6 protocol level */

/**  \name IPv6 socket options
 * IPv6 socket options summary
 *
 * | opt_name              | Data type         | set/getsockopt  | sendmsg | recvmsg |
 * | :-------------------: | :---------- ----: | :-------------: | :-----: | :-------|
 * | IPV6_UNICAST_HOPS     | int16_t           |     Set/Get     |   Yes   | No      |
 * | IPV6_MULTICAST_HOPS   | int16_t           |     Set/Get     |   Yes   | No      |
 * | IPV6_JOIN_GROUP       | ns_ipv6_mreq_t    |     Set only    |   Yes   | Yes     |
 * | IPV6_LEAVE_GROUP      | ns_ipv6_mreq_t    |     Set only    |   Yes   | Yes     |
 * | SO_EDFE_MODE          | uint32_t          |     Set only    |   Yes   | No      |
 */

///@{
/// Set the unicast hop limit for the socket.
/// When set, optval must point to an int16_t.
///
/// -1 in the value means use the route default, otherwise it should be between 0 and 255.
#define IPV6_UNICAST_HOPS            2
/// Set the multicast hop limit for the socket.
/// When set, optval must point to an int16_t.
///
/// -1 in the value means use the route default, otherwise it should be between 0 and 255.
#define IPV6_MULTICAST_HOPS          3
/// Join a multicast group.
/// When set, optval must point to an in6_addr_t.
#define IPV6_JOIN_GROUP             15
/// Leave a multicast group.
/// When set, optval must point to an in6_addr_t.
#define IPV6_LEAVE_GROUP            16
/// Experimental: Enable Extended Directed Frame Exchange mode.
/// When set, optval must point to an uint32_t.
#define SO_EDFE_MODE              0xfb
#define SOCKET_EDFE_MODE          SO_EDFE_MODE
///@}

/// Size of an IPv6 address
#define IPV6_ADDR_SIZE 16

/// When bitwise ored with socket's type,
/// it sets the O_NONBLOCK status flag on the opened socket file description
#define SOCK_NONBLOCK 0X00010000

/// Socket address length type definition
typedef uint32_t socklen_t;

/// Socket id
typedef int32_t sl_wisun_socket_id_t;

/// Enumerations for socket event mode
typedef enum {
  /// SL_WISUN_MSG_SOCKET_DATA_IND_ID is sent to the app with the packet contained in the indication
  SL_WISUN_SOCKET_EVENT_MODE_INDICATION = 0,
  /// SL_WISUN_MSG_SOCKET_DATA_AVAILABLE_IND_ID is sent to the app indicating the amount of data received
  /// recv() or recvfrom() should be invoked after indication reception to retrieve data
  /// This is the default socket event mode option
  SL_WISUN_SOCKET_EVENT_MODE_POLLING    = 1
} sl_wisun_socket_event_mode_t;

/// Supported address families
typedef enum socket_domain {
  AF_INET6 = 0  ///< IP version 6
} sl_socket_domain_t;

/// Socket types
typedef enum socket_type {
  SOCK_STREAM   = 1,  ///< stream (connection) socket (TCP)
  SOCK_DGRAM    = 2,  ///< datagram (connectionless ) socket (UDP)
  SOCK_RAW      = 3,   ///< raw socket
} sl_socket_type_t;

/// IP protocols
typedef enum socket_protocol {
  IPPROTO_IP   = 0,  ///< Dummy protocol
  IPPROTO_ICMP = 1,  ///< Internet Control Message Protocol
  IPPROTO_TCP  = 2,  ///< Transmission Control Protocol
  IPPROTO_UDP  = 3   ///< User Datagram Protocol
} sl_socket_protocol_t;

/// Socket address
struct sockaddr {
  uint16_t sa_family;    ///< address family, AF_XXXX
  uint8_t  sa_data[26];  ///< 26 bytes of protocol address (IPv6)
};

/// IPv6 Internet address
typedef struct in6_addr {
  uint8_t address[IPV6_ADDR_SIZE];  ///< IPv6 address
} in6_addr_t;

/// IPv6 wildcard address
extern const in6_addr_t in6addr_any;

/// IPv6 address format
typedef struct sockaddr_in6 {
    uint16_t    sin6_family;    ///< AF_INET6
    uint16_t    sin6_port;      ///< Transport layer port
    uint32_t    sin6_flowinfo;  ///< IPv6 flow information
    in6_addr_t  sin6_addr;      ///< IPv6 address
    uint32_t    sin6_scope_id;  ///< Scope ID
} sockaddr_in6_t;


/**************************************************************************//**
 * Creates an endpoint for communication and returns an Id that refers to that
 * endpoint.
 *
 * @param[in] domain Specifies a communication domain. It selects the protocol
 *                   family which will be used for communication. Must be set
 *                   to AF_INET6 (IPv6 network socket)
 * @param[in] type The communication semantics
 *                   It can be:
 *                      - #SOCK_STREAM  - TCP stream socket type
 *                      - #SOCK_DGRAM   - UDP datagram socket type
 *                      - #SOCK_RAW     - Raw Socket type (ICMP)
 * @param[in] protocol Specifies the particular protocol to be used.
 *                   It can be:
 *                      - #IPPROTO_ICMP  - Ping
 *                      - #IPPROTO_IP and IPPROTO_TCP  - TCP stream sockets
 *                      - #IPPROTO_IP and IPPROTO_UDP  - UDP datagram sockets
 * @return The socket's id on success, (-1) on failure.
 *****************************************************************************/
int32_t socket(int32_t domain, int32_t type, int32_t protocol);

/**************************************************************************//**
 * Close a socket.
 *
 * @param[in] sockid socket id
 * @return 0 on success, -1 on failure.
 *
 * Close a socket and remove from the socket handler storage.
 *****************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS

int32_t sl_close(int32_t sockid);

#define close(sockid) sl_close(sockid)
#else
int32_t close(int32_t sockid);
#endif
/**************************************************************************//**
 * Bind a name to a socket.
 *
 * @param[in] sockid socket id
 * @param[in] addr address structure ptr
 * @param[in] addrlen address structure size
 * @return 0 on success, -1 on failure.
 *
 * Assigns the address to the socket, referred to by the socket ID, as specified
 * by addr. It is normally necessary to assign a local address using bind()
 * before a #SOCK_STREAM socket may receive connections.
 *****************************************************************************/
int32_t bind(int32_t sockid, const struct sockaddr *addr, socklen_t addrlen);

/**************************************************************************//**
 * Send a message on a socket.
 *
 * @param[in] sockid socket descriptor.
 * @param[in] buff pointer to data buffer to send.
 * @param[in] len length of data buffer to send.
 * @param[in] flags flags to select send options. Ignored in our implementation.
 * @return The number of bytes sent on success, -1 if an error occurred.
 *
 * Preferred with connection-oriented sockets (TCP).
 *****************************************************************************/
int32_t send(int32_t sockid, const void *buff, uint32_t len, int32_t flags);

/**************************************************************************//**
 * Send a message to a given address.
 *
 * @param[in] sockid socket descriptor.
 * @param[in] buff pointer to data buffer to send.
 * @param[in] len length of data buffer to send.
 * @param[in] flags flags to select send options. Ignored in our implementation.
 * @param[in] dest_addr pointer to destination address buffer; Required for datagram sockets.
 * @param[in] addr_len length of  destination address buffer.
 * @return The number of bytes sent on success, -1 if an error occurred.
 *
 * Preferred in datagram mode (UDP).
 *****************************************************************************/
int32_t sendto(int32_t sockid, const void *buff, uint32_t len,
               int32_t flags, const struct sockaddr *dest_addr, socklen_t addr_len);

/**************************************************************************//**
 * Receive messages from a socket
 *
 * @param[in] sockid descriptor of socket to receive the message from.
 * @param[out] buf pointer to destination data buffer.
 * @param[in] len length of destination data buffer.
 * @param[in] flags flags to select type of message reception. Ignored in our
 *            implementation.
 * @param[in] src_addr pointer to a sockaddr structure in which the sending
 *                     address is to be stored.
 * @param[in] addrlen length of the supplied sockaddr structure.
 * @return The number of bytes received on success, -1 if an error occurred.
 *
 * Receives data on a socket whether or not it is connection-oriented.
 *****************************************************************************/
int32_t recvfrom(int32_t sockid, void *buf, uint32_t len, int32_t flags,
                 struct sockaddr *src_addr, socklen_t *addrlen);

/**************************************************************************//**
 * Receive a message from a socket.
 *
 * @param[in] sockid descriptor of socket to receive the message from.
 * @param[out] buf pointer to destination data buffer.
 * @param[in] len length of destination data buffer.
 * @param[in] flags flags to select type of message reception. Ignored in our
 *            implementation.
 * @return The number of bytes received on success, -1 if an error occurred.
 *
 * Should be used for connection-oriented protocol (TCP)
 *****************************************************************************/
int32_t recv(int32_t sockid, void *buf, uint32_t len, int32_t flags);

/**************************************************************************//**
 * Accept a connection on a socket.
 *
 * @param[in] sockid socket descriptor
 * @param[in,out] addr A pointer to sockaddr structure filled in with the address
 *                of the peer (remote) socket. When addr is NULL, nothing is
 *                filled in; in this case, addrlen is not used, and should also
 *                be NULL.
 *
 * @param[in,out] addrlen The caller must initialize it to contain the size (in
 *                bytes) of the structure pointed to by addr. On return it will
 *                contain the actual size of the peer address.
 * @return The socket id of the accepted socket on success, -1 if an error occurred.
 *
 * Used with connection-based socket types (TCP).
 * It extracts the first connection request on the queue of pending connections for the
 * listening socket.
 *****************************************************************************/
int32_t accept(int32_t sockid, struct sockaddr *addr, socklen_t *addrlen);

/**************************************************************************//**
 * Initiate a connection on a socket.
 *
 * @param[in] sockid socket descriptor.
 * @param[in] addr If the socket sockid is of type #SOCK_DGRAM, addr is the address
 *            to which datagrams are sent by default and the only address from
 *            which datagrams are received.
 *            If the socket is of type #SOCK_STREAM, this call attempts to make a
 *            connection to the socket that is bound to the address specified by addr.
 * @param[in] addrlen length of the supplied sockaddr structure.
 * @return 0 on connection or binding success, -1 if an error occurred.
 *
 * Connects the socket referred to by the sockid to the address specified by address.
 *****************************************************************************/
int32_t connect(int32_t sockid, const struct sockaddr *addr, socklen_t addrlen);

/**************************************************************************//**
 * Listen for connections on a socket.
 *
 * @param[in] sockid socket id
 * @param[in] backlog Argument defines the maximum length to
 *                    which the queue of pending connections for sockid may grow.
 *                    Not implemented for Wi-SUN, the connection queue size is always 1
 * @return 0 on success, -1 if an error occurred.
 *
 * Marks the socket referred to by sockid as a passive socket, that is, as a
 * socket that will be used to accept incoming connection requests using accept.
 *****************************************************************************/
int32_t listen(int32_t sockid, int32_t backlog);

/**************************************************************************//**
 * Set socket option designated by optname at a given protocol level to the
 * value pointed by optval.
 * @param[in] sockid socket ID
 * @param[in] level protocol level at which the option resides.
 *                  it could be:
 *                    - #SOL_SOCKET
 *                    - #IPPROTO_IPV6
 *                    - #SOL_APPLICATION
 * @param[in] optname option name.
 *                    it could be:
 *                      - for #SOL_SOCKET level:
 *                          - #SO_RCVBUF
 *                          - #SO_SNDBUF
 *                          - #SO_SNDLOWAT
 *                      - for #IPPROTO_IPV6 level:
 *                          - #IPV6_UNICAST_HOPS
 *                          - #IPV6_MULTICAST_HOPS
 *                          - #IPV6_JOIN_GROUP
 *                          - #IPV6_LEAVE_GROUP
 *                          - #SO_EDFE_MODE
 *                      - for #SOL_APPLICATION:
 *                          - #SO_EVENT_MODE
 *                          - #SO_NONBLOCK
 * @param[in] optval Pointer to the socket option new value. The type
 *                   of variable pointed by optval depends level and
 *                   optname values.
 * @param[in] optlen Must be the size of the symbol pointed by optval.
 * @return 0 on success, -1 if an error occurred.
 *
 * This function can set socket properties.
 *****************************************************************************/
int32_t setsockopt(int32_t sockid, int32_t level, int32_t optname,
                   const void *optval, socklen_t optlen);

/**************************************************************************//**
 * Get socket option.
 *
 * @param[in] sockid socket descriptor.
 * @param[in] level socket protocol level.
 * @param[in] optname Option name.
 *                    Supported options:
 *                      - for #SOL_SOCKET level:
 *                          - #SO_RCVBUF
 *                          - #SO_SNDBUF
 *                          - #SO_SNDLOWAT
 *                      - for #IPPROTO_IPV6 level:
 *                          - #IPV6_UNICAST_HOPS
 *                          - #IPV6_MULTICAST_HOPS
 * @param[out] optval option value structure pointer.
 * @param[in] optlen size of the option value structure.
 * @return 0 on success, -1 if an error occurred.
 *
 * The function gets socket option by optname, and copies option data to optval ptr.
 *****************************************************************************/
int32_t getsockopt(int32_t sockid, int32_t level, int32_t optname,
                   void *optval, socklen_t *optlen);

/**************************************************************************//**
 * Convert the long host byte order to network order.
 *
 * @param[in] hostlong Long host integer
 * @return Long network integer
 *
 * This function converts the unsigned integer hostlong from host byte order to network byte order.
 * For Wi-SUN, the conversion is not needed. Dummy implementation
 *****************************************************************************/
__STATIC_INLINE uint32_t htonl(uint32_t hostlong)
{
  return hostlong;
}

/**************************************************************************//**
 * Convert the short host byte order to network order.
 *
 * @param[in] hostshort Short host integer
 * @return Short network integer
 *
 * This function converts the unsigned short integer hostshort from host byte order to network byte order.
 * For Wi-SUN, the conversion is not needed. Dummy implementation
 *****************************************************************************/
__STATIC_INLINE uint16_t htons(uint16_t hostshort)
{
  return hostshort;
}

/**************************************************************************//**
 * Convert the long network byte order to host byte order.
 *
 * @param[in] netlong Long network integer
 * @return Long host integer
 *
 * This function converts the unsigned integer netlong from network byte order to host byte order.
 * For Wi-SUN, the conversion is not needed. Dummy implementation
 *****************************************************************************/
__STATIC_INLINE uint32_t ntohl(uint32_t netlong)
{
  return netlong;
}

/**************************************************************************//**
 * Convert the short network byte order to host byte order.
 *
 * @param[in] netshort
 * @return Short host integer
 *
 * This function converts the unsigned short integer netshort from the network
 * byte order to host byte order.For Wi-SUN, the conversion is not needed.
 * Dummy implementation.
 *****************************************************************************/
__STATIC_INLINE uint16_t ntohs(uint16_t netshort)
{
  return netshort;
}

/**************************************************************************//**
 * Convert the IPv4 and IPv6 addresses from text to binary form.
 *
 * @param[in] af The address family. Only AF_INET6 is supported by our implementation.
 * @param[in] src Source string
 * @param[out] dst Destination address pointer
 * @return 1 on succes, -1 if an error occurred. (POSIX described the 0 value too)
 *
 * This function converts the character string src into a network address structure
 * in the af address family, then copies the network address structure to dst.
 * AF_INET (IPv4) case not supported.
 *****************************************************************************/
int32_t inet_pton(int32_t af, const char *src, void *dst);

/**************************************************************************//**
 * Convert IPv6 addresses from binary to text form.
 *
 * @param[in] af - Address family.
 *               - Only AF_INET6 is supported
 * @param[in] src Source address in byte form
 * @param[out] dst Destination buffer ptr
 * @param[in] size Size of the destination buffer.
 * @return It returns a non-null pointer to dst. NULL if an error occurred.
 *
 * Converts the network address structure src in the af address family into a character string.
 * The resulting string is copied to the buffer pointed to by dst,
 * which must be a non-null pointer.
 * The caller specifies the number of bytes available in this buffer in the argument size.
 * AF_INET (IPv4) case not supported.
 *****************************************************************************/
const char *inet_ntop(int32_t af, const void *src, char *dst, socklen_t size);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* End socket.h */
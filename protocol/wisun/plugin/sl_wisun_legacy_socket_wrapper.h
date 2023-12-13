/***************************************************************************//**
 * @file sl_wisun_legacy_socket_wrapper.h
 * @brief Wrapper around our new posix socket API exposing our legacy socket API
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_WISUN_LEGACY_SOCKET_WRAPPER_H
#define SL_WISUN_LEGACY_SOCKET_WRAPPER_H

#include "sl_wisun_types.h"

/**
 * @addtogroup SL_WISUN_SL_SOCKET_COMPAT Silicon Labs socket API (deprecated)
 * @{
*/

/**************************************************************************//**
 * Open a socket.
 *
 * @param[in] protocol Protocol type of the socket
 * @param[out] socket_id ID of the opened socket
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function opens a socket. Up to 10 sockets may be open at any
 * given time, including those opened implicitly via
 * sl_wisun_accept_on_socket().
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #socket() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_open_socket(sl_wisun_socket_protocol_t protocol,
                                 sl_wisun_socket_id_t *socket_id) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Close a socket.
 *
 * @param[in] socket_id ID of the socket
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #close() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_close_socket(sl_wisun_socket_id_t socket_id) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Write data to an unconnected socket.
 *
 * @param[in] socket_id ID of the socket
 * @param[in] remote_address IP address of the remote peer
 * @param[in] remote_port Port number of the remote peer
 * @param[in] data_length Amount of data to write
 * @param[in] data Pointer to the data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function initiates a data transmission to a remote peer and can only
 * be used on an unconnected UDP or ICMP socket. Completion of the transmission
 * is indicated with a #SL_WISUN_MSG_SOCKET_DATA_SENT_IND_ID event. The function
 * takes a copy of the data, so the caller may free the resource when the function
 * returns.
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #sendto() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_sendto_on_socket(sl_wisun_socket_id_t socket_id,
                                      const sl_wisun_ip_address_t *remote_address,
                                      uint16_t remote_port,
                                      uint16_t data_length,
                                      const uint8_t *data) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Set a TCP socket to listening state.
 *
 * @param[in] socket_id ID of the socket
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets a TCP socket to listening state, allowing it to act as
 * a server socket, i.e., to receive connection requests from clients.
 * Connection requests are indicated with
 * #SL_WISUN_MSG_SOCKET_CONNECTION_AVAILABLE_IND_ID events and accepted using
 * sl_wisun_accept_on_socket(). This function can only be used on an unconnected
 * TCP socket.
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #listen() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_listen_on_socket(sl_wisun_socket_id_t socket_id) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Accept a pending connection request on a TCP socket.
 *
 * @param[in] socket_id ID of the socket on listening state
 * @param[out] remote_socket_id ID of the new connected socket
 * @param[out] remote_address IP address of the remote peer
 * @param[out] remote_port Port number of the remote peer
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function accepts a pending connection request from a remote peer and
 * creates a new connected TCP socket for the connection. To decline a
 * connection request, the request must be accepted and then closed using
 * sl_wisun_close_socket(). The function can only be used on a TCP socket in
 * listening state.
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #accept() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_accept_on_socket(sl_wisun_socket_id_t socket_id,
                                      sl_wisun_socket_id_t *remote_socket_id,
                                      sl_wisun_ip_address_t *remote_address,
                                      uint16_t *remote_port) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Initiate a connection from a socket to a remote peer socket.
 *
 * @param[in] socket_id ID of the socket
 * @param[in] remote_address IP address of the remote peer
 * @param[in] remote_port Port number of the remote peer
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function initiates a connection from a local socket to to a remote peer
 * socket. The result of the connection is indicated with a
 * #SL_WISUN_MSG_SOCKET_CONNECTED_IND_ID event. Connecting a socket is
 * mandatory for TCP client sockets but may be also used on other types of
 * sockets. A connected socket can only receive and transmit data with the
 * designated peer. This function can only be used on an unconnected TCP or
 * UDP socket.
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #connect() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_connect_socket(sl_wisun_socket_id_t socket_id,
                                    const sl_wisun_ip_address_t *remote_address,
                                    uint16_t remote_port) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Bind a socket to a specific local address and/or a port number.
 *
 * @param[in] socket_id ID of the socket
 * @param[in] local_address Local IP address to use on the socket. NULL if not bound.
 * @param[in] local_port Local port number to use on the socket. Zero if not bound.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function binds the local address and/or the port of a socket. When the
 * local address is bound, the socket will only accept traffic sent to the
 * specified address and the transmitted packets will use the address as the
 * source address. If not bound, the socket will accept data sent to any valid
 * address of the device. The source address is selected by the stack.
 * Binding the local port number sets the port number for received and
 * transmitted packets. If not bound, the stack will select a port number
 * automatically. This function can only be used on an unconnected TCP or UDP
 * socket. Once bound to a specific address and/or port, the value cannot
 * be changed.
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #bind() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_bind_socket(sl_wisun_socket_id_t socket_id,
                                 const sl_wisun_ip_address_t *local_address,
                                 uint16_t local_port) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Write data to a connected socket.
 *
 * @param[in] socket_id ID of the socket
 * @param[in] data_length Amount of data to write
 * @param[in] data Pointer to the data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function initiates transmission of data to a connected remote peer and
 * can only be used on a connected socket. Completion of the transmission is
 * indicated with a #SL_WISUN_MSG_SOCKET_DATA_SENT_IND_ID event. The function
 * takes a copy of the data, so the caller may free the resource when the function
 * returns.
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #send() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_send_on_socket(sl_wisun_socket_id_t socket_id,
                                    uint16_t data_length,
                                    const uint8_t *data) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Read data from a socket.
 *
 * @param[in] socket_id ID of the socket
 * @param[out] remote_address IP address of the remote peer
 * @param[out] remote_port Port number of the remote peer
 * @param[in,out] data_length Amount of data to read on input, amount of data read on output
 * @param[in] data Pointer to where the read data is stored
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function reads buffered data from a socket. When reading data from a
 * UDP or ICMP socket, the entire packet must be read. Any data left unread is
 * discarded after this call. TCP sockets allow reading only a part of the
 * buffered data.
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #recvfrom() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_receive_on_socket(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_ip_address_t *remote_address,
                                       uint16_t *remote_port,
                                       uint16_t *data_length,
                                       uint8_t *data) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Set a socket option.
 *
 * @param[in] socket_id ID of the socket
 * @param[in] option Socket option to set
 *   - #SL_WISUN_SOCKET_OPTION_EVENT_MODE: Event mode
 *   - #SL_WISUN_SOCKET_OPTION_MULTICAST_GROUP: Multicast group
 *   - #SL_WISUN_SOCKET_OPTION_SEND_BUFFER_LIMIT: Tx buffer limit
 *   - #SL_WISUN_SOCKET_OPTION_EDFE_MODE: Enable/disable EDFE mode
 *   - #SL_WISUN_SOCKET_OPTION_UNICAST_HOP_LIMIT: Socket unicast hop limit
 *   - #SL_WISUN_SOCKET_OPTION_MULTICAST_HOP_LIMIT: Socket multicast hop limit
 * @param[in] option_data Socket option specific data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #setsockopt() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_set_socket_option(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_socket_option_t option,
                                       const sl_wisun_socket_option_data_t *option_data) SL_DEPRECATED_API_SDK_4_4 ;

/**************************************************************************//**
 * Get a socket option.
 *
 * @param[in] socket_id ID of the socket
 * @param[in] option Socket option to get
 *   - #SL_WISUN_SOCKET_OPTION_SEND_BUFFER_LIMIT: Send buffer limit
 * @param[out] option_data Socket option specific data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function retrieves the value of a socket option.
 *
 * @deprecated This function will be removed in the future versions of the
 * Wi-SUN stack. See #getsockopt() for a replacement.
 *****************************************************************************/
sl_status_t sl_wisun_get_socket_option(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_socket_option_t option,
                                       sl_wisun_socket_option_data_t *option_data) SL_DEPRECATED_API_SDK_4_4 ;


/** @} (end addtogroup SL_WISUN_SL_SOCKET_COMPAT) */

#endif  // SL_WISUN_LEGACY_SOCKET_WRAPPER_H
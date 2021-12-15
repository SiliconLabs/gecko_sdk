/***************************************************************************//**
 * @file sl_wisun_api.h
 * @brief Wi-SUN API
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

#ifndef SL_WISUN_API_H
#define SL_WISUN_API_H

#include "sl_wisun_types.h"
#include "sl_wisun_events.h"
#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************//**
 * @addtogroup SL_WISUN_API Wi-SUN Stack API
 * @{
 *****************************************************************************/

/** @{
 * @name Callbacks
 */

/**************************************************************************//**
 * @brief Callback handler for a single event.
 * @details This function is called when the stack sends an event to the
 *          application. The application can declare its own version this
 *          function to customize event handling. The default implementation
 *          discards all events.
 * @param evt The event to be handled
 * @see #SL_WISUN_EVT
 *****************************************************************************/
void sl_wisun_on_event(sl_wisun_evt_t *evt);


/**
 * @}
 */

/**************************************************************************//**
 * @brief Set the size of the Wi-SUN network.
 * @details This function sets the size of the network. The value is used to
 *          adjust internal behavior, such as timing parameters, to optimize
 *          device behavior in regard to the size. The device will function
 *          with any setting but may exhibit non-optimal behavior. Setting
 *          the size too large may cause slow connection speeds and increased
 *          latency. Conversely, a value too small may cause increased network
 *          traffic.
 * @param[in] size Size of the network
 *    <br/><b>SL_WISUN_NETWORK_SIZE_AUTOMATIC</b>: network size is managed automatically
 *    <br/><b>SL_WISUN_NETWORK_SIZE_SMALL</b>: less than 100 nodes
 *    <br/><b>SL_WISUN_NETWORK_SIZE_MEDIUM</b>: 100 to 800 nodes
 *    <br/><b>SL_WISUN_NETWORK_SIZE_LARGE</b>: 800 to 1500 nodes
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_network_size(sl_wisun_network_size_t size);

/**************************************************************************//**
 * @brief Initiate connection to a Wi-SUN network.
 * @details This function initiates connection to a Wi-SUN network. Completion
 *          of the request is indicated with a #SL_WISUN_MSG_CONNECTED_IND_ID
 *          event.
 * @param[in] name Name of the Wi-SUN network as a zero-terminated string
 * @param[in] reg_domain Regulatory domain of the Wi-SUN network
 * @param[in] op_class Operating class of the Wi-SUN network
 * @param[in] op_mode Operating mode of the Wi-SUN network
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_connect(const uint8_t *name,
                             sl_wisun_regulatory_domain_t reg_domain,
                             sl_wisun_operating_class_t op_class,
                             sl_wisun_operating_mode_t op_mode);

/**************************************************************************//**
 * @brief Read an IP address.
 * @param[in] address_type Type of the IP address to read
 *    <br/><b>SL_WISUN_IP_ADDRESS_TYPE_LINK_LOCAL</b>: Link-local IPv6 address of the device
 *    <br/><b>SL_WISUN_IP_ADDRESS_TYPE_GLOBAL</b>: Global unicast IPv6 address of the device
 *    <br/><b>SL_WISUN_IP_ADDRESS_TYPE_BORDER_ROUTER</b>: Global unicast IPv6 address of the border router
 *    <br/><b>SL_WISUN_IP_ADDRESS_TYPE_PRIMARY_PARENT</b>: Link-local IPv6 address of the primary parent
 *    <br/><b>SL_WISUN_IP_ADDRESS_TYPE_SECONDARY_PARENT</b>: Link-local IPv6 address of the secondary parent
 * @param[out] address IP address to read
 * @return SL_STATUS_OK if successful, an error code otherwise.
 *****************************************************************************/
sl_status_t sl_wisun_get_ip_address(sl_wisun_ip_address_type_t address_type,
                                    sl_wisun_ip_address_t *address);

/**************************************************************************//**
 * @brief Open a socket.
 * @param[in] protocol Protocol type of the socket
 * @param[out] socket_id ID of the opened socket
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_open_socket(sl_wisun_socket_protocol_t protocol,
                                 sl_wisun_socket_id_t *socket_id);

/**************************************************************************//**
 * @brief Close a socket.
 * @param[in] socket_id ID of the socket
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_close_socket(sl_wisun_socket_id_t socket_id);

/**************************************************************************//**
 * @brief Write data to an unconnected socket.
 * @details This function initiates transmission of data to a remote peer and
 *          can only be used on an unconnected UDP or ICMP socket.
 *          Completion of the transmission is indicated with a
 *          #SL_WISUN_MSG_SOCKET_DATA_SENT_IND_ID event. The function takes a copy
 *          of the data, the caller may free the resource when the function
 *          returns.
 * @param[in] socket_id ID of the socket
 * @param[in] remote_address IP address of the remote peer
 * @param[in] remote_port Port number of the remote peer
 * @param[in] data_length Amount of data to write
 * @param[in] data Pointer to the data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_sendto_on_socket(sl_wisun_socket_id_t socket_id,
                                      const sl_wisun_ip_address_t *remote_address,
                                      uint16_t remote_port,
                                      uint16_t data_length,
                                      const uint8_t *data);

/**************************************************************************//**
 * @brief Set a TCP socket to listening state.
 * @details This function sets a TCP socket to listening state, allowing
 *          it to act as a server socket, i.e., to receive connection requests
 *          from clients. Connection requests are indicated with
 *          #SL_WISUN_MSG_SOCKET_CONNECTION_AVAILABLE_IND_ID events and accepted
 *          using sl_wisun_accept_on_socket(). This function can only be
 *          used on an unconnected TCP socket.
 * @param[in] socket_id ID of the socket
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_listen_on_socket(sl_wisun_socket_id_t socket_id);

/**************************************************************************//**
 * @brief Accept a pending connection request on a TCP socket.
 * @details This function accepts a pending connection request from a remote
 *          peer and creates a new connected TCP socket for the connection.
 *          To decline a connection request, the request must be accepted and
 *          then closed using sl_wisun_close_socket(). Use this function
 *          only on a TCP socket on listening state.
 * @param[in] socket_id ID of the socket on listening state
 * @param[out] remote_socket_id ID of the new connected socket
 * @param[out] remote_address IP address of the remote peer
 * @param[out] remote_port Port number of the remote peer
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_accept_on_socket(sl_wisun_socket_id_t socket_id,
                                      sl_wisun_socket_id_t *remote_socket_id,
                                      sl_wisun_ip_address_t *remote_address,
                                      uint16_t *remote_port);

/**************************************************************************//**
 * @brief Initiate a connection from a socket to a remote peer socket.
 * @details This function initiates a connection from a local socket to
 *          to a remote peer socket. The result of the connection is indicated
 *          with a #SL_WISUN_MSG_SOCKET_CONNECTED_IND_ID event. Connecting
 *          a socket is mandatory for TCP client sockets but may be also
 *          used on other types of sockets. A connected socket can only
 *          receive and transmit data with the designated peer. Use this
 *          function only on an unconnected TCP or UDP socket.
 * @param[in] socket_id ID of the socket
 * @param[in] remote_address IP address of the remote peer
 * @param[in] remote_port Port number of the remote peer
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_connect_socket(sl_wisun_socket_id_t socket_id,
                                    const sl_wisun_ip_address_t *remote_address,
                                    uint16_t remote_port);

/**************************************************************************//**
 * @brief Bind a socket to a specific local address and/or a port number.
 * @details This function binds the local address and/or the port of a socket.
 *          When the local address is bound, the socket will only accept traffic
 *          sent to the specified address and the transmitted packets will use
 *          the address as the source address. If not bound, the socket will
 *          accept data sent to any valid address of the device and the source
 *          address is selected by the stack. Binding the local port number
 *          sets the port number for received and transmitted packets. If not
 *          bound, the stack will select a port number automatically.
 *          This function can only be used on an unconnected TCP or UDP socket.
 * @param[in] socket_id ID of the socket
 * @param[in] local_address Local IP address to use on the socket. NULL if not bound.
 * @param[in] local_port Local port number to use on the socket. Zero if not bound.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_bind_socket(sl_wisun_socket_id_t socket_id,
                                 const sl_wisun_ip_address_t *local_address,
                                 uint16_t local_port);

/**************************************************************************//**
 * @brief Write data to a connected socket.
 * @details This function initiates transmission of data to a connected remote
 *          peer and can only be used on a connected socket. Completion of
 *          the transmission is indicated with
 *          a #SL_WISUN_MSG_SOCKET_DATA_SENT_IND_ID event. The function takes
 *          a copy of the data, the caller may free the resource when the
 *          function returns.
 * @param[in] socket_id ID of the socket
 * @param[in] data_length Amount of data to write
 * @param[in] data Pointer to the data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_send_on_socket(sl_wisun_socket_id_t socket_id,
                                    uint16_t data_length,
                                    const uint8_t *data);

/**************************************************************************//**
 * @brief Read data from a socket.
 * @details This function reads buffered data from a socket. When reading data
 *          from a UDP or ICMP socket, the entire packet must be read.
 *          Any data left unread is discarded after this call. TCP sockets
 *          allow reading only a part of the buffered data.
 * @param[in] socket_id ID of the socket
 * @param[out] remote_address IP address of the remote peer
 * @param[out] remote_port Port number of the remote peer
 * @param[in,out] data_length Amount of data to read on input, amount of data read on output
 * @param[in] data Pointer to where the read data is stored
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_receive_on_socket(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_ip_address_t *remote_address,
                                       uint16_t *remote_port,
                                       uint16_t *data_length,
                                       uint8_t *data);

/**************************************************************************//**
 * @brief Disconnect from the Wi-SUN network.
 * @details This function disconnects an active connection or cancels
 *          an ongoing connection attempt.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_disconnect();

/**************************************************************************//**
 * @brief Set a trusted certificate used to verify the authentication server certificate.
 * @param[in] certificate_options Options for the certificate
 *   <br/><b>SL_WISUN_CERTIFICATE_OPTION_APPEND</b>: Append the certificate to the list of trusted certificates
 *                                                   instead of replacing the previous entries
 *   <br/><b>SL_WISUN_CERTIFICATE_OPTION_IS_REF</b>: The application guarantees the certificate data will remain
 *                                                   in scope and can therefore be referenced instead of copied
 * @param[in] certificate_length Size of the certificate data
 * @param[in] certificate Pointer to the certificate data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_trusted_certificate(uint16_t certificate_options,
                                             uint16_t certificate_length,
                                             const uint8_t *certificate);

/**************************************************************************//**
 * @brief Set the device certificate used to authenticate to the authentication server.
 * @param[in] certificate_options Options for the certificate.
 *   <br/><b>SL_WISUN_CERTIFICATE_OPTION_APPEND</b>: Append the certificate to the list of device certificates
 *                                                   instead of replacing the previous entries
 *   <br/><b>SL_WISUN_CERTIFICATE_OPTION_IS_REF</b>: The application guarantees the certificate data will remain
 *                                                   in scope and can therefore be referenced instead of copied
 *   <br/><b>SL_WISUN_CERTIFICATE_OPTION_HAS_KEY</b>: The certificate has a private key
 * @param[in] certificate_length Size of the certificate data
 * @param[in] certificate Pointer to the certificate data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_device_certificate(uint16_t certificate_options,
                                            uint16_t certificate_length,
                                            const uint8_t *certificate);

/**************************************************************************//**
 * @brief Set the private key of the device certificate.
 * @param[in] key_options Options for the private key
 *   <br/><b>SL_WISUN_PRIVATE_KEY_OPTION_IS_REF</b>: The application guarantees the private key data will remain
 *                                                   in scope and can therefore be referenced instead of copied
 * @param[in] key_length Size of the private key data
 * @param[in] key Pointer to the private key data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_device_private_key(uint16_t key_options,
                                            uint16_t key_length,
                                            const uint8_t *key);

/**************************************************************************//**
 * @brief Read a set of statistics.
 * @details This function reads a set of statistics from the stack. Statistics
 *          are cumulative and reset when a connection is initiated.
 * @param[in] statistics_type Type of statistics to read
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_PHY</b>: PHY/RF statistics
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_MAC</b>: MAC statistics
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_FHSS</b>: Frequency hopping statistics
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_WISUN</b>: Wi-SUN statistics
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_NETWORK</b>: 6LoWPAN/IP stack statistics
 * @param[out] statistics Set of statistics read
 * @return SL_STATUS_OK if successful, an error code otherwise.
 *****************************************************************************/
sl_status_t sl_wisun_get_statistics(sl_wisun_statistics_type_t statistics_type,
                                    sl_wisun_statistics_t *statistics);

/**************************************************************************//**
 * @brief Set a socket option.
 * @param[in] socket_id ID of the socket
 * @param[in] option Socket option to set
 *   <br/><b>SL_WISUN_SOCKET_OPTION_EVENT_MODE</b>: Event mode
 *   <br/><b>SL_WISUN_SOCKET_OPTION_MULTICAST_GROUP</b>: Multicast group
 * @param[in] option_data Socket option specific data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_socket_option(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_socket_option_t option,
                                       const sl_wisun_socket_option_data_t *option_data);

/**************************************************************************//**
 * @brief Set the maximum TX power.
 * @details This function sets the maximum TX power to be used. The device
 *          may utilize a lower value based on internal decision making or
 *          hardware limitations but will never exceed the given value.
 * @param[in] tx_power TX power in dBm
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_tx_power(int8_t tx_power);

/**************************************************************************//**
 * @brief Set a channel plan.
 * @details This function sets an application-specific channel plan to be used
 *          in the following connections. By default, the channel plan is set
 *          indirectly based on the regulatory domain and the operating class
 *          given in sl_wisun_connect().
 * @param[in] ch0_frequency Frequency of the first channel in kHz
 * @param[in] number_of_channels Number of channels
 * @param[in] channel_spacing Spacing between the channels
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_channel_plan(uint32_t ch0_frequency,
                                      uint16_t number_of_channels,
                                      sl_wisun_channel_spacing_t channel_spacing);

/**************************************************************************//**
 * @brief Set a mask of operating channels.
 * @details This function sets a mask of channels the device is allowed to
 *          operate in. By default, all channels in the channel plan are
 *          allowed. The mask can only be used to further restrict the channels,
 *          channels outside the channel plan or channels internally excluded
 *          are ignored. This mask will be used in the following connections.
 * @param[in] channel_mask Mask of operating channels
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_channel_mask(const sl_wisun_channel_mask_t *channel_mask);

/**************************************************************************//**
 * @brief Add a MAC address to the list of allowed addresses.
 * @details This function adds a MAC address to the list of allowed addresses.
 *          When the first address is added to the list, the list of denied
 *          addresses is cleared and the device will start preventing
 *          communication with any device whose MAC address does not match any
 *          of addresses on the list. By default, all MAC addresses are allowed.
 * @param[in] address MAC address
 *   <br/><b>broadcast address</b>: allow all MAC addresses
 *   <br/><b>unicast address</b>: allow the given MAC address
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_allow_mac_address(const sl_wisun_mac_address_t *address);

/**************************************************************************//**
 * @brief Add a MAC address to the list of denied addresses.
 * @details This function adds a MAC address to the list of denied addresses.
 *          When the first address is added to the list, the list of allowed
 *          addresses is cleared and the device will start preventing
 *          communication with any device whose MAC address matches any of
 *          the addresses on the list. By default, all MAC addresses
 *          are allowed.
 * @param[in] address MAC address
 *   <br/><b>broadcast address</b>: deny all MAC addresses
 *   <br/><b>unicast address</b>: deny the given MAC address
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_deny_mac_address(const sl_wisun_mac_address_t *address);

/**************************************************************************//**
 * @brief Get a socket option.
 * @details This function retrieves the value of a socket option.
 * @param[in] socket_id ID of the socket
 * @param[in] option Socket option to get
 *   <br/><b>SL_WISUN_SOCKET_OPTION_SEND_BUFFER_LIMIT</b>: Send buffer limit
 * @param[out] option_data Socket option specific data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_socket_option(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_socket_option_t option,
                                       sl_wisun_socket_option_data_t *option_data);

/**************************************************************************//**
 * @brief Get the current join state.
 * @details This function retrieves the current state of the connection
 *          process. The function can only be used when a connection has been
 *          initiated.
 * @param[out] join_state Join state
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_join_state(sl_wisun_join_state_t *join_state);

/**************************************************************************//**
 * @brief Clear the credential cache.
 * @details This function clears the cached authentication credentials stored
 *          in non-volatile storage. The function is intended for test purposes.
 *          Note that clearing the credential cache may prevent the node from
 *          reconnecting to the same parent until the corresponding cache entry
 *          has expired on the parent.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_clear_credential_cache();

/**************************************************************************//**
 * @brief Get the current MAC address in use.
 * @param[out] address MAC address
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_mac_address(sl_wisun_mac_address_t *address);

/**************************************************************************//**
 * @brief Set the MAC address to be used.
 * @details This function sets the MAC address to be used in the following
 *          connections. By default, the device will use the built-in unique
 *          device MAC address. The address is reset to the built-in value
 *          upon power up.
 * @param[in] address MAC address
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_mac_address(const sl_wisun_mac_address_t *address);

/**************************************************************************//**
 * @brief Reset a set of statistics in the stack.
 * @param[in] statistics_type Type of statistics to reset
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_PHY</b>: PHY/RF statistics
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_MAC</b>: MAC statistics
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_FHSS</b>: Frequency hopping statistics
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_WISUN</b>: Wi-SUN statistics
 *   <br/><b>SL_WISUN_STATISTICS_TYPE_NETWORK</b>: 6LoWPAN/IP stack statistics
 * @return SL_STATUS_OK if successful, an error code otherwise.
 *****************************************************************************/
sl_status_t sl_wisun_reset_statistics(sl_wisun_statistics_type_t statistics_type);

/**************************************************************************//**
 * @brief Get the number of RPL neighbors (parents and children).
 * @param[out] neighbor_count Number of neighbors
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_neighbor_count(uint8_t *neighbor_count);

/**************************************************************************//**
 * @brief Get the list of RPL neighbors (parents and children).
 * @param[in,out] neighbor_count Number of neighbors to read on input,
 *                               number of neighbors read on output
 * @param[out] neighbor_mac_addresses Pointer to memory where to store neighbor
 *                                    MAC addresses
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_neighbors(uint8_t *neighbor_count,
                                   sl_wisun_mac_address_t *neighbor_mac_addresses);

/**************************************************************************//**
 * @brief Get information about a RPL neighbor (parent or child).
 * @param[in] neighbor_mac_address Pointer to neighbor MAC address
 * @param[out] neighbor_info Pointer to where the read information is stored
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_neighbor_info(const sl_wisun_mac_address_t *neighbor_mac_address,
                                       sl_wisun_neighbor_info_t *neighbor_info);

/**************************************************************************//**
 * @brief Set unicast settings.
 * @details This function sets the unicast channel hopping schedule to be used
 *          in the following connections. The Unicast Dwell Interval specifies
 *          the duration during which the node will listen to a channel within
 *          its listening schedule.
 * @param[in] dwell_interval_ms Unicast Dwell Interval (15-255 ms)
 *                              (default: 255 ms)
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_unicast_settings(uint8_t dwell_interval_ms);

/** @} (end SL_WISUN_API) */

#ifdef __cplusplus
}
#endif

#endif  // SL_WISUN_API_H

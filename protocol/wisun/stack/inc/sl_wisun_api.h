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
#include "sl_wisun_connection_params_api.h"
#include "sl_wisun_lfn_params_api.h"
#include "socket/socket.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************//**
 * @addtogroup SL_WISUN_API Wi-SUN Stack API
 *
 * Wi-SUN Stack API is based on requests from the application to the stack and
 * events from the stack to the application. Requests are made using function
 * calls, where a function call either performs the required action immediately
 * or initiates an internal operation within the stack, which terminates with an
 * event. All events contain a status code, indicating the result of the
 * requested operation. Events are also used by the stack to notify the
 * application of any important information, such as the state of the
 * connection.
 *
 * The application is expected to override sl_wisun_on_event() to handle events
 * from the stack. Because all events share a common header, the function may be
 * implemented as a switch statement. The event-specific data can be accessed
 * through the #sl_wisun_evt_t::evt union.
 *
 *     void sl_wisun_on_event(sl_wisun_evt_t *evt)
 *     {
 *       switch (evt->header.id) {
 *         case SL_WISUN_MSG_CONNECTED_IND_ID:
 *           handle_connected_event(evt->evt.connected);
 *           break;
 *         default:
 *           break;
 *       }
 *     }
 *
 * The API is thread-safe, which means can be called from multiple RTOS tasks. The
 * stack guarantees that only a single request is executed at a time and that requests
 * are handled in the order they were made. Event callback is executed in a
 * different context than the request, so the API functions may be called from
 * the event callback.
 *
 * @{
 *****************************************************************************/

/**
 * @name Callbacks
 * @{
 */

/**************************************************************************//**
 * Callback handler for a single event.
 *
 * @param evt The event to be handled
 *
 * This function is called when the stack sends an event to the application.
 * The application can declare its own version this function to customize
 * event handling. The default implementation discards all events.
 *
 * @see #SL_WISUN_EVT
 *****************************************************************************/
void sl_wisun_on_event(sl_wisun_evt_t *evt);

/**
 * @}
 */

/**************************************************************************//**
 * Initiate a connection to a Wi-SUN network.
 *
 * @param[in] name Name of the Wi-SUN network as a zero-terminated string
 * @param[in] phy_config Pointer to PHY configuration
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function initiates connection to a Wi-SUN network. Completion of the
 * request is indicated with a #SL_WISUN_MSG_CONNECTED_IND_ID event.
 *****************************************************************************/
sl_status_t sl_wisun_join(const uint8_t *name, sl_wisun_phy_config_t *phy_config);

/**************************************************************************//**
 * Read an IP address.
 *
 * @param[in] address_type Type of the IP address to read
 *   - #SL_WISUN_IP_ADDRESS_TYPE_LINK_LOCAL: Link-local IPv6 address of the device
 *   - #SL_WISUN_IP_ADDRESS_TYPE_GLOBAL: Global unicast IPv6 address of the device
 *   - #SL_WISUN_IP_ADDRESS_TYPE_BORDER_ROUTER: Global unicast IPv6 address of the border router
 *   - #SL_WISUN_IP_ADDRESS_TYPE_PRIMARY_PARENT: Link-local IPv6 address of the primary parent
 *   - #SL_WISUN_IP_ADDRESS_TYPE_SECONDARY_PARENT: Link-local IPv6 address of the secondary parent
 * @param[out] address IP address to read
 * @return SL_STATUS_OK if successful, an error code otherwise.
 *****************************************************************************/
sl_status_t sl_wisun_get_ip_address(sl_wisun_ip_address_type_t address_type,
                                    in6_addr_t *address);

/**************************************************************************//**
 * Disconnect from the Wi-SUN network.
 *
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function disconnects an active connection or cancels an ongoing
 * connection attempt.
 *****************************************************************************/
sl_status_t sl_wisun_disconnect();

/**************************************************************************//**
 * Set a trusted certificate used to verify the authentication server certificate.
 *
 * @param[in] certificate_options Options for the certificate
 *   - #SL_WISUN_CERTIFICATE_OPTION_APPEND: Append the certificate to the list of trusted certificates
 *                                          instead of replacing the previous entries
 *   - #SL_WISUN_CERTIFICATE_OPTION_IS_REF: The application guarantees the certificate data will remain
 *                                          in scope and can therefore be referenced instead of copied
 * @param[in] certificate_length Size of the certificate data
 * @param[in] certificate Pointer to the certificate data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_trusted_certificate(uint16_t certificate_options,
                                             uint16_t certificate_length,
                                             const uint8_t *certificate);

/**************************************************************************//**
 * Set the device certificate used to authenticate to the authentication server.
 *
 * @param[in] certificate_options Options for the certificate.
 *   - #SL_WISUN_CERTIFICATE_OPTION_APPEND: Append the certificate to the list of device certificates
 *                                          instead of replacing the previous entries
 *   - #SL_WISUN_CERTIFICATE_OPTION_IS_REF: The application guarantees the certificate data will remain
 *                                          in scope and can therefore be referenced instead of copied
 *   - #SL_WISUN_CERTIFICATE_OPTION_HAS_KEY: The certificate has a private key
 * @param[in] certificate_length Size of the certificate data
 * @param[in] certificate Pointer to the certificate data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_device_certificate(uint16_t certificate_options,
                                            uint16_t certificate_length,
                                            const uint8_t *certificate);

/**************************************************************************//**
 * Set the private key of the device certificate.
 *
 * @param[in] key_options Options for the private key
 *   - #SL_WISUN_PRIVATE_KEY_OPTION_IS_REF: The application guarantees the private key data will remain
 *                                          in scope and can therefore be referenced instead of copied
 * @param[in] key_length Size of the private key data
 * @param[in] key Pointer to the private key data
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_device_private_key(uint16_t key_options,
                                            uint16_t key_length,
                                            const uint8_t *key);

/**************************************************************************//**
 * Read a set of statistics.
 *
 * @param[in] statistics_type Type of statistics to read
 *   - #SL_WISUN_STATISTICS_TYPE_PHY: PHY/RF statistics
 *   - #SL_WISUN_STATISTICS_TYPE_MAC: MAC statistics
 *   - #SL_WISUN_STATISTICS_TYPE_FHSS: Frequency hopping statistics
 *   - #SL_WISUN_STATISTICS_TYPE_WISUN: Wi-SUN statistics
 *   - #SL_WISUN_STATISTICS_TYPE_NETWORK: 6LoWPAN/IP stack statistics
 *   - #SL_WISUN_STATISTICS_TYPE_REGULATION: Regional regulation statistics
 *   - #SL_WISUN_STATISTICS_TYPE_HEAP: Heap usage statistics
 * @param[out] statistics Set of statistics read
 * @return SL_STATUS_OK if successful, an error code otherwise.
 *
 * This function reads a set of statistics from the stack. Statistics are
 * cumulative and reset when a connection is initiated or by calling
 * sl_wisun_reset_statistics().
 *****************************************************************************/
sl_status_t sl_wisun_get_statistics(sl_wisun_statistics_type_t statistics_type,
                                    sl_wisun_statistics_t *statistics);

/**************************************************************************//**
 * Set the maximum TX power.
 *
 * @param[in] tx_power TX power in dBm
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the maximum TX power. The device may use
 * a lower value based on internal decision making or hardware limitations but
 * will never exceed the given value.
 *****************************************************************************/
sl_status_t sl_wisun_set_tx_power(int8_t tx_power);

/**************************************************************************//**
 * Set a mask of operating channels.
 *
 * @param[in] channel_mask Mask of operating channels
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets a mask of channels the device is allowed to operate in
 * for unicast frequency hopping. By default, all channels in the channel plan
 * are allowed. The mask can only be used to further restrict the channels.
 * Channels outside the channel plan or channels internally excluded are
 * ignored. This mask will be used in the following connections.
 *
 * @warning By comparison to the Wi-SUN FAN specification, the channel mask
 *          logic is inverted. The specification references a mask of excluded
 *          channels.
 *****************************************************************************/
sl_status_t sl_wisun_set_allowed_channel_mask(const sl_wisun_channel_mask_t *channel_mask);

/**************************************************************************//**
 * Set a mask of operating channels.
 *
 * @param[in] channel_mask Mask of operating channels
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets a mask of channels the device is allowed to operate in
 * for unicast frequency hopping. By default, all channels in the channel plan
 * are allowed. The mask can only be used to further restrict the channels.
 * Channels outside the channel plan or channels internally excluded are
 * ignored. This mask will be used in the following connections.
 *****************************************************************************/
sl_status_t sl_wisun_set_channel_mask(const sl_wisun_channel_mask_t *channel_mask);

/**************************************************************************//**
 * Add a MAC address to the list of allowed addresses.
 *
 * @param[in] address MAC address
 *   - **sl_wisun_broadcast_mac**: allow all MAC addresses
 *   - **unicast address**: allow the given MAC address
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function adds a MAC address to the list of allowed addresses. When the
 * first address is added to the list, the list of denied addresses is cleared
 * and the device will start preventing communication with any device whose MAC
 * address does not match any of addresses on the list. By default, all MAC
 * addresses are allowed. Up to 10 MAC addresses may be added to the list.
 * The access list affects only directly connected nodes such as parents,
 * children, and neighbors.
 *****************************************************************************/
sl_status_t sl_wisun_allow_mac_address(const sl_wisun_mac_address_t *address);

/**************************************************************************//**
 * Add a MAC address to the list of denied addresses.
 *
 * @param[in] address MAC address
 *   - **sl_wisun_broadcast_mac**: deny all MAC addresses
 *   - **unicast address**: deny the given MAC address
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function adds a MAC address to the list of denied addresses. When the
 * first address is added to the list, the list of allowed addresses is cleared
 * and the device will start preventing communication with any device whose MAC
 * address matches any of the addresses on the list. By default, all MAC
 * addresses are allowed. Up to 10 MAC addresses may be added to the list.
 * The access list affects only directly connected nodes such as parents,
 * children, and neighbors.
 *****************************************************************************/
sl_status_t sl_wisun_deny_mac_address(const sl_wisun_mac_address_t *address);

/**************************************************************************//**
 * Get the current join state.
 *
 * @param[out] join_state Join state
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function retrieves the current state of the connection process. The
 * function can only be used once a connection has been initiated.
 *****************************************************************************/
sl_status_t sl_wisun_get_join_state(sl_wisun_join_state_t *join_state);

/**************************************************************************//**
 * Clear the credential cache.
 *
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function clears the cached authentication credentials stored in
 * non-volatile storage. The function is intended for test purposes. Note that
 * clearing the credential cache may prevent the node from reconnecting to the
 * same parent until the corresponding cache entry has expired on the parent.
 *****************************************************************************/
sl_status_t sl_wisun_clear_credential_cache();

/**************************************************************************//**
 * Get the current device MAC address in use.
 *
 * @param[out] address MAC address
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_mac_address(sl_wisun_mac_address_t *address);

/**************************************************************************//**
 * Set the device MAC address to be used.
 *
 * @param[in] address MAC address
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the MAC address for use in the following connections.
 * By default, the device will use the built-in unique device MAC address.
 * The address is reset to the built-in value upon power up.
 *****************************************************************************/
sl_status_t sl_wisun_set_mac_address(const sl_wisun_mac_address_t *address);

/**************************************************************************//**
 * Reset a set of statistics in the stack.
 *
 * @param[in] statistics_type Type of statistics to reset
 *   - #SL_WISUN_STATISTICS_TYPE_PHY: PHY/RF statistics
 *   - #SL_WISUN_STATISTICS_TYPE_MAC: MAC statistics
 *   - #SL_WISUN_STATISTICS_TYPE_FHSS: Frequency hopping statistics
 *   - #SL_WISUN_STATISTICS_TYPE_WISUN: Wi-SUN statistics
 *   - #SL_WISUN_STATISTICS_TYPE_NETWORK: 6LoWPAN/IP stack statistics
 * @return SL_STATUS_OK if successful, an error code otherwise.
 *****************************************************************************/
sl_status_t sl_wisun_reset_statistics(sl_wisun_statistics_type_t statistics_type);

/**************************************************************************//**
 * Get the number of RPL neighbors (parents and children).
 *
 * @param[out] neighbor_count Number of neighbors
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_neighbor_count(uint8_t *neighbor_count);

/**************************************************************************//**
 * Get a list of RPL neighbor (parents and children) MAC addresses.
 *
 * @param[in,out] neighbor_count Maximum number of neighbors to read on input,
 *                               number of neighbors read on output
 * @param[out] neighbor_mac_addresses Pointer to memory where to store neighbor
 *                                    MAC addresses
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_neighbors(uint8_t *neighbor_count,
                                   sl_wisun_mac_address_t *neighbor_mac_addresses);

/**************************************************************************//**
 * Get information about a RPL neighbor (parent or child).
 *
 * @param[in] neighbor_mac_address Pointer to neighbor MAC address
 * @param[out] neighbor_info Pointer to where the read information is stored
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_neighbor_info(const sl_wisun_mac_address_t *neighbor_mac_address,
                                       sl_wisun_neighbor_info_t *neighbor_info);

/**************************************************************************//**
 * Set unicast settings.
 *
 * @param[in] dwell_interval_ms Unicast Dwell Interval (15-255 ms)
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the parameters for unicast channel hopping to be used in
 * the following connections. The Unicast Dwell Interval specifies the duration
 * which the node will listen to a channel within its listening schedule.
 * The default value is 255 ms.
 *****************************************************************************/
sl_status_t sl_wisun_set_unicast_settings(uint8_t dwell_interval_ms);

/**************************************************************************//**
 * Set the private key of the device certificate.
 *
 * @param[in] key_id Key ID of the private key
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the device private key using a key identifier,
 * referencing a key stored in PSA cryptography module. The corresponding
 * device certificate must still be set using sl_wisun_set_device_certificate().
 * The stored key must have correct PSA key attributes, see the
 * Wi-SUN FAN Security Concepts and Design Considerations document for
 * details.
 *****************************************************************************/
sl_status_t sl_wisun_set_device_private_key_id(uint32_t key_id);

/**************************************************************************//**
 * Set the regional regulation.
 *
 * @param[in] regulation Regional regulation
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the regional regulation for use in the following
 * connections. The selected regional regulation will impact both the Wi-SUN
 * stack performance and its behavior. See regulation standards for details.
 * No regulation is set by default.
 *****************************************************************************/
sl_status_t sl_wisun_set_regulation(sl_wisun_regulation_t regulation);

/**************************************************************************//**
 * Set the thresholds for transmission duration level event.
 *
 * @param[in] warning_threshold Warning threshold in percent or -1 to disable
 * @param[in] alert_threshold Alert threshold in percent or -1 to disable
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the thresholds for transmission duration level event.
 * When set and when a regional regulation is enabled using
 * sl_wisun_set_regulation(), a #SL_WISUN_MSG_REGULATION_TX_LEVEL_IND_ID event
 * is sent when one of the configured thresholds is exceeded. This can be used
 * by the application to prevent exceeding the total transmission duration
 * allowed in the regional regulation. Thresholds are defined as a percentage
 * of the maximum transmission duration permitted by the regional regulation.
 *****************************************************************************/
sl_status_t sl_wisun_set_regulation_tx_thresholds(int8_t warning_threshold,
                                                  int8_t alert_threshold);

/**************************************************************************//**
 * Set the async transmission fragmentation parameters.
 *
 * @param[in] fragment_duration_ms Max duration of a fragment in ms (min 500 ms)
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * Async transmissions, such as Wi-SUN PAN advertisement packets, are sent
 * to every allowed operating channel and may therefore block broadcast and
 * unicast traffic. This impact can be reduced by splitting the channel list
 * into fragments based on the maximum transmission duration and by forcing a
 * delay between the fragments, allowing other traffic to occur. This function
 * sets the maximum duration of a PA, PAS, PC, and PCS advertisement period
 * fragments. A small value trades off longer connection times for shorter
 * latencies. Setting the duration to #SL_WISUN_ADVERT_FRAGMENT_DISABLE disables
 * async transmission fragmentation.
 *
 * By default, the maximum fragment duration is set to 500 ms.
 *****************************************************************************/
sl_status_t sl_wisun_set_advert_fragment_duration(uint32_t fragment_duration_ms);

/**************************************************************************//**
 * Enable an algorithm that trades off unicast communication reliability
 * for latency.
 *
 * @param[in] mode Transmission mode to use
 *   - #SL_WISUN_UNICAST_TX_MODE_DEFAULT: Default transmission mode.
 *   - #SL_WISUN_UNICAST_TX_MODE_SLOT: High reliability, high latency.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * Enable an algorithm that trades off unicast communication reliability
 * for latency. The mechanism is only effective when all the neighbors are enabled.
 * Enabling this option is detrimental when used with unaware Wi-SUN devices.
 *****************************************************************************/
sl_status_t sl_wisun_set_unicast_tx_mode(uint8_t mode);

/**************************************************************************//**
 * Set the device type.
 *
 * @param[in] device_type Type of the device
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the operational mode of the node.
 *****************************************************************************/
sl_status_t sl_wisun_set_device_type(sl_wisun_device_type_t device_type);

/**************************************************************************//**
 * Set the mode switch configuration.
 *
 * @param[in] mode Mode switch configuration of the neighbor. If set to
 *                 #SL_WISUN_MODE_SWITCH_DEFAULT, the configuration of
 *                 the neighbor is reset back to the default mode switch
 *                 behavior.
 * @param[in] phy_mode_id PhyModeId to use when mode is set to
 *                        #SL_WISUN_MODE_SWITCH_ENABLED, ignored otherwise.
 * @param[in] neighbor_address MAC address of the neighbor to configure.
 *                             If set to #sl_wisun_broadcast_mac, configures
 *                             the default mode switch behavior for all
 *                             non-configured neighbors.
 * @param[in] reserved Reserved for future use, set to false.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_config_mode_switch(uint8_t mode,
                                        uint8_t phy_mode_id,
                                        const sl_wisun_mac_address_t *neighbor_address,
                                        bool reserved);

/**************************************************************************//**
 * Set the PHY mode switch configuration.
 *
 * @param[in] mode Mode switch configuration of the neighbor. If set to
 *                 #SL_WISUN_MODE_SWITCH_DEFAULT, the configuration of
 *                 the neighbor is reset back to the default mode switch
 *                 behavior.
 * @param[in] phy_mode_id PhyModeId to use when mode is set to
 *                        #SL_WISUN_MODE_SWITCH_ENABLED, ignored otherwise.
 * @param[in] neighbor_address MAC address of the neighbor to configure.
 *                             If set to #sl_wisun_broadcast_mac, configures
 *                             the default mode switch behavior for all
 *                             non-configured neighbors.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_mode_switch(uint8_t mode,
                                     uint8_t phy_mode_id,
                                     const sl_wisun_mac_address_t *neighbor_address);

/**************************************************************************//**
 * Configure the FFN parameter set.
 *
 * @param[in] params Parameter set to use
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the FFN parameter set. These parameters impact
 * connection time, bandwidth usage, and latency. Use of a predefined
 * parameter set is recommended (@ref SL_WISUN_FFN_PARAMETER_SETS).
 * The function must be called before initiating a connection.
 *****************************************************************************/
sl_status_t sl_wisun_set_connection_parameters(const sl_wisun_connection_params_t *params);

/**************************************************************************//**
 * Set the POM-IE configuration.
 *
 * @param[in] phy_mode_id_count Number of PhyModeId to configure
 * @param[in] phy_mode_ids List of phy_mode_id_count PhyModeId. It must
 *                         contain the base operating mode.
 * @param[in] is_mdr_command_capable Indicate if the device supports MAC mode switch.
 *                                   Feature currently unsupported, must be set to 0.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the PHY operating mode information advertised to neighboring
 * nodes. By default the PhyModeId list contains the first fifteen PhyModeId listed
 * in radio multi-PHY configuration, MAC mode switch is disabled.
 *****************************************************************************/
sl_status_t sl_wisun_set_pom_ie(uint8_t phy_mode_id_count,
                                uint8_t phy_mode_ids[SL_WISUN_MAX_PHY_MODE_ID_COUNT],
                                uint8_t is_mdr_command_capable);

/**************************************************************************//**
 * Get the POM-IE configuration.
 *
 * @param[out] phy_mode_id_count Number of PhyModeId retrieved
 * @param[out] phy_mode_ids List of phy_mode_id_count PhyModeId. Caller must allocate
 *                          space for at least #SL_WISUN_MAX_PHY_MODE_ID_COUNT entries.
 * @param[out] is_mdr_command_capable Set to 1 if the device supports MAC mode switch,
 *                                    0 otherwise
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function retrieves the PHY operating mode information advertised
 * to neighboring nodes.
 *****************************************************************************/
sl_status_t sl_wisun_get_pom_ie(uint8_t *phy_mode_id_count,
                                uint8_t *phy_mode_ids,
                                uint8_t *is_mdr_command_capable);

/**************************************************************************//**
 * Get the Wi-SUN stack version.
 *
 * @param[out] major Wi-SUN stack version major
 * @param[out] minor Wi-SUN stack version minor
 * @param[out] patch Wi-SUN stack version patch
 * @param[out] build Build number, set to 0 in public versions
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_stack_version(uint8_t *major,
                                       uint8_t *minor,
                                       uint8_t *patch,
                                       uint16_t *build);

/**************************************************************************//**
 * Configure the LFN parameter set.
 *
 * @param[in] params Parameter set to use
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the LFN parameter set. These parameters impact
 * connection time, bandwidth usage, power consumption, and latency.
 * Use of a predefined parameter set is recommended
 * (@ref SL_WISUN_LFN_PARAMETER_SETS).
 * The function must be called before initiating a connection.
 ******************************************************************************/
sl_status_t sl_wisun_set_lfn_parameters(const sl_wisun_lfn_params_t *params);

/**************************************************************************//**
 * Set the maximum number of LFN children.
 *
 * @param[in] lfn_limit Maximum number of LFN children [0, 10]
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets the maximum number of LFN children this node can
 * parent.
 ******************************************************************************/
sl_status_t sl_wisun_set_lfn_support(uint8_t lfn_limit);

/**************************************************************************//**
 * Set the PTI state.
 *
 * @param[in] pti_state PTI state
 *   - **true**: PTI is enabled
 *   - **false**: PTI is disabled
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * This function sets Packet Trace Interface (PTI) state. PTI is enabled
 * by default.
 *****************************************************************************/
sl_status_t sl_wisun_set_pti_state(bool pti_state);

/**************************************************************************//**
 * Trigger the transmission of a frame (FAN Discovery, RPL).
 *
 * @param[in] frame_type Type of frame
 * @return SL_STATUS_OK if successful, an error code otherwise
 *
 * No frame is transmitted if the associated Trickle timer is not started, if
 * exists.
 *****************************************************************************/
sl_status_t sl_wisun_trigger_frame(sl_wisun_frame_type_t frame_type);

/**************************************************************************//**
 * Set the security state.
 *
 * @param[in] security_state Security state
 *   - **0**: Security is disabled
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_set_security_state(uint32_t security_state);

/**************************************************************************//**
 * Get the Wi-SUN network information.
 *
 * @param[out] network_info Pointer to network information
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_network_info(sl_wisun_network_info_t *network_info);

/**************************************************************************//**
 * Get RPL information.
 *
 * @param[out] rpl_info Pointer to RPL information
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_rpl_info(sl_wisun_rpl_info_t *rpl_info);

/**************************************************************************//**
 * Get the mask of channels excluded from channel plan
 *
 * @param[in] type Type of channel mask
 * @param[out] channel_mask Pointer to mask
 * @param[out] channel_count Number of channels in mask
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t sl_wisun_get_excluded_channel_mask(sl_wisun_channel_mask_type_t type,
                                               sl_wisun_channel_mask_t *channel_mask,
                                               uint8_t *channel_count);

/** @} (end SL_WISUN_API) */

#ifdef __cplusplus
}
#endif

#endif  // SL_WISUN_API_H

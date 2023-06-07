/***************************************************************************//**
 * @file  sl_zigbee_zdo_security.h
 * @brief ZDO Security functionality described in R23 including retrieving and
 * generating Authentication Token
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_ZIGBEE_ZDO_SECURITY_H
#define SL_ZIGBEE_ZDO_SECURITY_H

#include "stack/include/sl_zigbee_stack_specific_tlv.h"
#include "sl_enum.h"

// Local TLV Defines
// Authentication Token ID
#define SLI_ZIGBEE_ZDO_AUTHENTICATION_TOKEN_ID_TAG_ID   0
#define SLI_ZIGBEE_ZDO_AUTHENTICATION_TOKEN_ID_MIN_LEN  1
#define SLI_ZIGBEE_ZDO_AUTHENTICATION_TOKEN_ID_MAX_LEN  1
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_AUTHENTICATION_TOKEN_ID_MAX_LEN) sl_zigbee_local_tlv_authentication_token_id_t;

//security decommissioning
#define SLI_ZIGBEE_ZDO_SECURITY_DECOMMISSION_TAG_ID   0
#define SLI_ZIGBEE_ZDO_SECURITY_DECOMMISSION_MIN_LEN  1
#define SLI_ZIGBEE_ZDO_SECURITY_DECOMMISSION_MAX_LEN  255
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_SECURITY_DECOMMISSION_MAX_LEN) sl_zigbee_local_tlv_security_decommission_t;

// Target IEEE Address
#define SLI_ZIGBEE_ZDO_TARGET_IEEE_ADDRESS_TAG_ID 0
#define SLI_ZIGBEE_ZDO_TARGET_IEEE_ADDRESS_MIN_LEN 8
#define SLI_ZIGBEE_ZDO_TARGET_IEEE_ADDRESS_MAX_LEN 8
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_TARGET_IEEE_ADDRESS_MAX_LEN) sl_zigbee_local_tlv_target_ieee_address_t;

// Device Authentication Level
#define SLI_ZIGBEE_ZDO_DEVICE_AUTHENTICATION_LEVEL_TAG_ID 0
#define SLI_ZIGBEE_ZDO_DEVICE_AUTHENTICATION_LEVEL_MIN_LEN 10
#define SLI_ZIGBEE_ZDO_DEVICE_AUTHENTICATION_LEVEL_MAX_LEN 10
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_DEVICE_AUTHENTICATION_LEVEL_MAX_LEN) sl_zigbee_local_tlv_device_authentication_level_t;

SL_ENUM(sl_zigbee_initial_join_method) {
  INITIAL_JOIN_METHOD_TYPE_ANONYMOUS               = 0,
  INITIAL_JOIN_METHOD_TYPE_INSTALL_CODE_KEY        = 1,
  INITIAL_JOIN_METHOD_TYPE_WELL_KNOWN_PASSPHRASE   = 2,
  INITIAL_JOIN_METHOD_TYPE_INSTALL_CODE_PASSPHRASE = 3,
};

SL_ENUM(sl_zigbee_active_link_key_type) {
  ACITVE_LINK_KEY_TYPE_NOT_UPDATED                    = 0,
  ACITVE_LINK_KEY_TYPE_KEY_REQUEST_METHOD             = 1,
  ACITVE_LINK_KEY_TYPE_ANONYMOUS_KEY_NEGOTIATION      = 2,
  ACITVE_LINK_KEY_TYPE_AUTHENTICATED_KEY_NEGOTIATION  = 3,
  ACITVE_LINK_KEY_TYPE_CERTIFICATE_BASED_KEY_EXCHANGE = 4,
};

/** @brief Gets Authentication Level of queried device
 *
 * @param dest Short address of where you want to send the request (trust center)
 * @param target EUI64 of queried device
 *
 * @return An ::sl_status value that indicates whether the request was
 * successful or if an error status needs to be sent back.
 */
sl_status_t sl_zigbee_get_authentication_level(EmberNodeId dest, EmberEUI64 target);

extern void sl_zigbee_set_authenticaion_level(EmberEUI64 target,
                                              sl_zigbee_initial_join_method *initial_join_method,
                                              sl_zigbee_active_link_key_type *active_link_key_type);

/** @brief Internal function for generating Get Authentication Level Request
 *
 * @param dest Short address of where you want to send the request
 * @param aps_options APS options
 * @param target EUI64 of queried device
 *
 * @return An ::sl_status value that indicates whether the request was
 * successful or if an error status needs to be sent back.
 */
sl_status_t sli_zigbee_generate_get_authentication_level_req(EmberNodeId dest, EmberApsOption aps_options, EmberEUI64 target);

/** @brief Handler for Security Get Authentication Level Request.
 * This function will check if the request is valid and call functions
 * to get the initial join method and active link key update method of
 * the inquired device
 *
 * @param request Buffer containing the ZDO payload
 * @param payload_index Index pointing to the TLV data in the payload
 * @param source address of the device sending the request
 * @param options APS Options
 * @param sequence Sequence number of the ZDO message
 *
 * @return An ::sl_status value that indicates whether the request was
 * successful or if an error status needs to be sent back.
 */
sl_status_t sli_zigbee_zdo_handle_get_authentication_level_req(Buffer request,
                                                               uint8_t payload_index,
                                                               EmberNodeId source,
                                                               EmberApsOption options,
                                                               uint8_t sequence);

/** @brief Handler for Security Get Authentication Level Response.
 * This function will check if the response is valid and pass the received
 * information up to an application callback function.
 *
 * @param request Buffer containing the ZDO payload
 * @param payload_index Index pointing to the TLV data in the payload
 * @param source Short address of the device sending the request
 *
 * @return An ::sl_status value that indicates whether the response was
 * successful or if an error status needs to be sent back.
 */
sl_status_t sli_zigbee_zdo_handle_get_authentication_level_rsp(Buffer response,
                                                               uint8_t payload_index,
                                                               EmberNodeId source);

extern void sl_zigbee_get_authentication_level_callback(EmberZdoStatus rsp_status, EmberEUI64 target, uint8_t join_method, uint8_t link_key_update);

#define SLI_ZIGBEE_ZDO_LINK_KEY_FEATURES_AND_CAPABILITIES_TAG_ID 0
#define SLI_ZIGBEE_ZDO_LINK_KEY_FEATURES_AND_CAPABILITIES_MIN_LEN 1
#define SLI_ZIGBEE_ZDO_LINK_KEY_FEATURES_AND_CAPABILITIES_MAX_LEN 1
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_LINK_KEY_FEATURES_AND_CAPABILITIES_MAX_LEN) sl_zigbee_local_tlv_link_key_features_and_capabilities_id_t;

#define SLI_ZIGBEE_ZDO_SECURITY_CHALLENGE_TAG_ID 0
#define SLI_ZIGBEE_ZDO_SECURITY_CHALLENGE_MIN_LEN 32
#define SLI_ZIGBEE_ZDO_SECURITY_CHALLENGE_MAX_LEN 32
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_SECURITY_CHALLENGE_MAX_LEN) sl_zigbee_local_tlv_security_challenge_t;

/** @brief Sends the Security Retrieve Authentication Token Request.
 *
 * This function will generate the Authentication Token ID TLV and
 * send the Security Retrieve Authentication Token Request ZDO Command.
 *
 * @param destination Device to send the request to
 * @param options APS Options
 *
 * @return An ::sl_status value that indicates the success or failure of
 * generating and sending the ZDO command.
 */
sl_status_t sl_zigbee_zdo_generate_retrieve_authentication_token_req(EmberNodeId destination,
                                                                     EmberApsOption options);

/** @brief Handler for Security Retrieve Authentication Token Request.
 * This function will check if the request is valid and call functions
 * to generate the authentication token and send it to the destination
 * address passed in.
 *
 * @param request Buffer containing the ZDO payload
 * @param payload_index Index pointing to the TLV data in the payload
 * @param source Destination Address to send the response to
 * @param options APS Options
 *
 * @return An ::sl_status value that indicates whether the request was
 * successful or if an error status needs to be sent back.
 */
sl_status_t sli_zigbee_zdo_handle_retrieve_authentication_token_req(Buffer request,
                                                                    uint8_t payload_index,
                                                                    EmberNodeId source,
                                                                    EmberApsOption options,
                                                                    uint8_t sequence);

/** @brief Sends the Security Device Decommissioning Request.
 *
 * This function will generate the Security Decommissioning TLV and
 * send the Security Decommissioning Request ZDO Command.
 *
 * @param destination Device to send the request to
 * @param encrypt should this message be APS encrypted or not
 * @param eui64_list list of EUI64 of devices that need to be decommisioned
 *
 * @return An ::sl_status value that indicates the success or failure of
 * generating and sending the ZDO command.
 */
sl_status_t sli_zigbee_zdo_generate_security_decommission_req(EmberNodeId destination,
                                                              bool encrypt,
                                                              void* eui64_list,
                                                              uint8_t counts);

/** @brief Handler for Security Device Decommissioning Request.
 * This function will check if the request is valid and call functions
 * to remove binding and link key table entries for given devices
 *
 * @param request Buffer containing the ZDO payload
 * @param payload_index Index pointing to the TLV data in the payload
 * @param source Destination Address to send the response to
 * @param options APS Options
 *
 * @return An ::sl_status value that indicates whether the request was
 * successful or if an error status needs to be sent back.
 */
sl_status_t sli_zigbee_zdo_handle_security_decommission_req(Buffer request,
                                                            uint8_t payload_index,
                                                            EmberNodeId source,
                                                            EmberApsOption options,
                                                            uint8_t sequence);

/** @brief Sends the Clear Binding Request.
 *
 * This function will generate the Clear Binding TLV and
 * send the Clear Binding Request ZDO Command.
 *
 * @param destination Device to send the request to
 * @param encrypt should this message be APS encrypted or not
 * @param eui64_list list of EUI64 of devices that need to be decommisioned
 *
 * @return An ::sl_status value that indicates the success or failure of
 * generating and sending the ZDO command.
 */
sl_status_t sli_zigbee_zdo_generate_clear_all_bindings_req(EmberNodeId destination,
                                                           bool encrypt,
                                                           void* eui64_list,
                                                           uint8_t counts);

/** @brief Handler for Clear Binding Request.
 * This function will check if the request is valid and call functions
 * to remove binding entries for given devices, including all devices given wildcard eui64
 *
 * @param request Buffer containing the ZDO payload
 * @param payload_index Index pointing to the TLV data in the payload
 * @param source Destination Address to send the response to
 * @param options APS Options
 *
 * @return An ::sl_status value that indicates whether the request was
 * successful or if an error status needs to be sent back.
 */
sl_status_t sli_zigbee_zdo_handle_clear_all_bindings_req(Buffer request,
                                                         uint8_t payload_index,
                                                         EmberNodeId source,
                                                         EmberApsOption options,
                                                         uint8_t sequence);

/** @brief Handler for Security Retrieve Authentication Token Response.
 * This function will handle the Retrieve Authentication Token Response, check
 * the Authentication Token provided and save it.
 *
 * @param response Response Buffer containing the response data
 * @param payload_index Index pointing to the TLV data in the payload
 * @param source Short address of the device sending the response
 *
 * @return An ::sl_status value that indicates whether the response was
 * successful or if an error status needs to be sent back.
 */
sl_status_t sli_zigbee_zdo_handle_retrieve_authentication_token_rsp(Buffer response,
                                                                    uint8_t payload_index,
                                                                    EmberNodeId source);

/** @brief Get the Symmetric Passphrase for a device.
 * This function will return the Symmetric Passphrase for a device if one exists.
 * If a long address (EUI64) is provided, that will be checked first.
 * If the long address is set to NULL, then the Short Id is used.
 * If a matching entry is found, then return SUCCESS, else FAILURE.
 *
 * @param eui64 Long Address of device to match in the passphrase key store
 * @param short_id Short Address of device to match in the passphrase key store
 * @param passphrase Pointer to the buffer for the passphrase to be copied into
 *
 * @return An ::sl_status value that indicates outcome of the operation.
 */
sl_status_t sl_zigbee_get_symmetric_passphrase(EmberEUI64 eui64,
                                               EmberNodeId short_id,
                                               uint8_t *passphrase);

/** @brief Application-defined callback to notify completion of symmetric passphrase operation
 *
 * @param status status of processing this response (SL_STATUS_OK if successful op)
 */
extern void sl_zigbee_zdo_retrieve_authentication_token_complete_callback(sl_status_t status);

/** @brief Schedules sending the Security Retrieve Authentication Token Request.
 *
 * This function will schedule an event to send the Retrieve Authentication Token
 * request after a short delay. This allows the calling function to continue
 * and have the event framework send out the command.
 *
 * @param destination Device to send the request to
 * @param options APS Options
 *
 */
void sl_zigbee_retrieve_authentication_token(EmberNodeId destination,
                                             EmberApsOption options);

// security challenge request and response
/**
 * @brief sends a security challenge request out over the air
 * @param destShort the short id of the message destination
 * @param keyToChallenge the key data being challenged (synchronized)
 * @return A valid sl_status_t
 */
sl_status_t sl_zigbee_send_security_challenge_request(EmberNodeId destShort,
                                                      EmberKeyData *keyToChallenge);
/**
 * @brief handles an incoming security challenge by validating the contents
 * and issuing a response
 * @param request a message buffer containing the request
 * @param index the location of the message payload within the buffer
 * @param sourceShort the short id of the node who sent the request
 * @param rspSequence the sequence number of the request frame
 * @return a status code indicating whether processing was successful
 */
sl_status_t sli_zigbee_process_security_challenge_request(Buffer request,
                                                          uint16_t index,
                                                          EmberNodeId sourceShort,
                                                          uint8_t rspSequence);

/**
 * @brief handles an incoming security challenge response, validating the challenge
 * and updating the corresponding frame counter
 * @param response a message buffer containing the response
 * @param index the location of the response payload within the buffer
 * @param sourceShort the short id of the responder
 * // TODO response sequence number?
 */
void sli_zigbee_process_security_challenge_response(Buffer response,
                                                    uint16_t index,
                                                    EmberNodeId sourceShort);

#endif // SL_ZIGBEE_ZDO_SECURITY_H

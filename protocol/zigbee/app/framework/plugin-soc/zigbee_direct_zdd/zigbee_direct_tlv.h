/***************************************************************************//**
 * @file zigbee_direct_tlv.h
 * @brief Zigbee Direct TLVs are defined in the Zigbee Direct specification
 * this header defines Zigbee Direct TLVs
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

#ifndef SILABS_ZIGBEE_DIRECT_TLV_H
#define SILABS_ZIGBEE_DIRECT_TLV_H

#include "stack/include/sl_zigbee_tlv_core.h"
/**
 * Zigbee Direct TLVs
 * define tag id, minimum length, maximum length, concrete tlv_structs
 * for right now min and max will largely be the same but it sets a better
 * precedent to define all of these constants
 *
 * Zigbee direct TLV definitions must include certain attributes...
 * 1. Tag ID :: a unique identifier for the TLV.  Global TLV definitions must
 *    be in the range of 0x40-0xFF (64-255).
 * 2. Minimum Length :: the minimum valid length of the TLV.  TLV validation
 *    will throw an error if it encounters a Global TLV with < min_length
 * 3. Maximum Length :: the maximum number of expected bytes. Used to define
 *    and allocate TLV data structures.  When a TLV is encountered that is greater
 *    than the expected length we copy only up to what we know
 * Each Global TLV has a typedef'd struct, and possibly other helper functionality
 */

/**
 * Extended PAN ID - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_TAG_ID 0x00
#define SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_MIN_LEN 7
#define SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_MAX_LEN 7
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_MAX_LEN) sl_zigbee_direct_tlv_extended_pan_id_t;

/**
 * Short PAN ID - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_PAN_ID_TAG_ID 0x01
#define SL_ZIGBEE_DIRECT_TLV_PAN_ID_MIN_LEN 1
#define SL_ZIGBEE_DIRECT_TLV_PAN_ID_MAX_LEN 1
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_PAN_ID_MAX_LEN) sl_zigbee_direct_tlv_pan_id_t;

/**
 * Network Channel - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_TAG_ID 0x02
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_MIN_LEN 4
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_MAX_LEN 4
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_MAX_LEN) sl_zigbee_direct_tlv_network_channel_mask_t;

/**
 * Network Key - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_TAG_ID 0x03
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_MIN_LEN 15
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_MAX_LEN 15
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_MAX_LEN) sl_zigbee_direct_tlv_network_key_t;

/**
 * Link Key - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_LINK_KEY_TAG_ID 0x04
#define SL_ZIGBEE_DIRECT_TLV_LINK_KEY_MIN_LEN 16
#define SL_ZIGBEE_DIRECT_TLV_LINK_KEY_MAX_LEN 16
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_LINK_KEY_MAX_LEN) sl_zigbee_direct_tlv_link_key_t;

/**
 * Device Type - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_TAG_ID 0x05
#define SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_MIN_LEN 0
#define SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_MAX_LEN 0
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_MAX_LEN) sl_zigbee_direct_tlv_device_type_t;

#define SL_ZIGBEE_DIRECT_DEVICE_TYPE_COO 0x00
#define SL_ZIGBEE_DIRECT_DEVICE_TYPE_RTR 0x01
#define SL_ZIGBEE_DIRECT_DEVICE_TYPE_ZED 0x02

/**
 * NWK Address - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_TAG_ID 0x06
#define SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_MIN_LEN 1
#define SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_MAX_LEN 1
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_MAX_LEN) sl_zigbee_direct_tlv_nwk_address_t;

/**
 * Joining Method - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_JOINING_METHOD_TAG_ID 0x07
#define SL_ZIGBEE_DIRECT_TLV_JOINING_METHOD_MIN_LEN 0
#define SL_ZIGBEE_DIRECT_TLV_JOINING_METHOD_MAX_LEN 0
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_JOINING_METHOD_MAX_LEN) sl_zigbee_direct_tlv_joining_method_t;

/**
 * IEEE Address - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_TAG_ID 0x08
#define SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_MIN_LEN 7
#define SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_MAX_LEN 7
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_MAX_LEN) sl_zigbee_direct_tlv_ieee_address_t;

/**
 * Trust Center Address - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_TAG_ID 0x09
#define SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_MIN_LEN 7
#define SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_MAX_LEN 7
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_MAX_LEN) sl_zigbee_direct_tlv_trust_center_address_t;

/**
 * Network status map - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_TAG_ID 0x0A
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_MIN_LEN 0
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_MAX_LEN 0
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_MAX_LEN) sl_zigbee_direct_tlv_network_status_map_t;

#define SL_ZIGBEE_DIRECT_NETWORK_STATUS_MAP_JOINED_STATUS_BITMASK 0x07
#define SL_ZIGBEE_DIRECT_NETWORK_STATUS_MAP_OPEN_CLOSE_STATUS_BITMASK 0x08
#define SL_ZIGBEE_DIRECT_NETWORK_STATUS_MAP_OPEN_CLOSE_STATUS_BIT 0x04
#define SL_ZIGBEE_DIRECT_NETWORK_STATUS_MAP_NETWORK_TYPE_BITMASK 0x10
#define SL_ZIGBEE_DIRECT_NETWORK_STATUS_MAP_NETWORK_TYPE_BIT 0x10

/**
 * Network update ID - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_TAG_ID 0x0B
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_MIN_LEN 0
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_MAX_LEN 0
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_MAX_LEN) sl_zigbee_direct_tlv_network_update_id_t;

/**
 * Network active key sequence number - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_TAG_ID 0x0C
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_MIN_LEN 0
#define SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_MAX_LEN 0
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_MAX_LEN) sl_zigbee_direct_tlv_network_active_key_seq_number_t;

/**
 * Distributed security admin key - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_DISTRIBUTED_SECURITY_ADMIN_KEY_TAG_ID 0x0D
#define SL_ZIGBEE_DIRECT_TLV_DISTRIBUTED_SECURITY_ADMIN_KEY_MIN_LEN 15
#define SL_ZIGBEE_DIRECT_TLV_DISTRIBUTED_SECURITY_ADMIN_KEY_MAX_LEN 15
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_DISTRIBUTED_SECURITY_ADMIN_KEY_MAX_LEN) sl_zigbee_direct_tlv_distributed_security_admin_key_t;

/**
 * Status code - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_STATUS_CODE_TAG_ID 0x0E
#define SL_ZIGBEE_DIRECT_TLV_STATUS_CODE_KEY_MIN_LEN 1
#define SL_ZIGBEE_DIRECT_TLV_STATUS_CODE_KEY_MAX_LEN 1
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_STATUS_CODE_KEY_MAX_LEN) sl_zigbee_direct_tlv_status_code_t;

#define SL_ZIGBEE_DIRECT_STATUS_DOMAIN_GENERAL 0
#define SL_ZIGBEE_DIRECT_STATUS_DOMAIN_FORM 1
#define SL_ZIGBEE_DIRECT_STATUS_DOMAIN_JOIN 2
#define SL_ZIGBEE_DIRECT_STATUS_DOMAIN_PJOIN 3
#define SL_ZIGBEE_DIRECT_STATUS_DOMAIN_LEAVE 4
#define SL_ZIGBEE_DIRECT_STATUS_DOMAIN_MJOIN 5
#define SL_ZIGBEE_DIRECT_STATUS_DOMAIN_IDENTIFY 6
#define SL_ZIGBEE_DIRECT_STATUS_DOMAIN_FUB 7

#define SL_ZIGBEE_DIRECT_STATUS_CODE_SUCCESS 0
#define SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR 1
#define SL_ZIGBEE_DIRECT_STATUS_CODE_DECRYPT_FAIL 2

/**
 * Extended status code - Commissioning Service
 */
#define SL_ZIGBEE_DIRECT_TLV_EXTENDED_STATUS_CODE_TAG_ID 0x0F
#define SL_ZIGBEE_DIRECT_TLV_EXTENDED_STATUS_CODE_KEY_MIN_LEN 0x00
#define SL_ZIGBEE_DIRECT_TLV_EXTENDED_STATUS_CODE_KEY_MAX_LEN 0xFF
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_EXTENDED_STATUS_CODE_KEY_MAX_LEN) sl_zigbee_direct_tlv_extended_status_code_t;

/**
 * NPDU message - Tunneling Service
 */
#define SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_MESSAGE_TAG_ID 0x00
#define SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_REQUEST_MIN_LEN 1
#define SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_REQUEST_MAX_LEN 0xF2
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_REQUEST_MAX_LEN) sl_zigbee_direct_tunneling_tlv_npdu_message_t;

/**
 * Key negotiation method - Security Service
 */
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_SELECTED_KEY_NEGOTIATION_METHOD_TAG_ID 0x00
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_SELECTED_KEY_NEGOTIATION_METHOD_MIN_LEN 1
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_SELECTED_KEY_NEGOTIATION_METHOD_MAX_LEN 1
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_SECURITY_TLV_SELECTED_KEY_NEGOTIATION_METHOD_MAX_LEN) sl_zigbee_direct_security_selected_key_negotioation_method_t;

/**
 * P256 public point - Security Service
 */
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_TAG_ID 0x01
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_MIN_LEN 71
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_MAX_LEN 71
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_MAX_LEN) sl_zigbee_direct_security_p256_public_point_t;

/**
 * curve 25519 public point - Security Service
 */
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_TAG_ID 0x02
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_MIN_LEN 39
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_MAX_LEN 39
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_MAX_LEN) sl_zigbee_direct_security_c25519_public_point_t;

/**
 * Key sequence number - Security Service
 */
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_KEY_SEQUENCE_NUMBER_TAG_ID 0x03
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_KEY_SEQUENCE_NUMBER_MIN_LEN 0 // was 32?
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_KEY_SEQUENCE_NUMBER_MAX_LEN 0 // was 32?
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_SECURITY_TLV_KEY_SEQUENCE_NUMBER_MAX_LEN) sl_zigbee_direct_security_key_sequence_number_t;

/**
 * Mac tag - Security Service
 */
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_MAC_TAG_TAG_ID 0x04
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_MAC_TAG_MIN_LEN 32
#define SL_ZIGBEE_DIRECT_SECURITY_TLV_MAC_TAG_MAX_LEN 32
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_SECURITY_TLV_MAC_TAG_MAX_LEN) sl_zigbee_direct_security_mac_tag_t;

/**
 * Provisional Link Key - Manage Joiners Characteristic
 */
#define SL_ZIGBEE_DIRECT_TLV_PROVISIONAL_LINK_KEY_TAG_ID 0x00
#define SL_ZIGBEE_DIRECT_TLV_PROVISIONAL_LINK_KEY_MIN_LEN 15
#define SL_ZIGBEE_DIRECT_TLV_PROVISIONAL_LINK_KEY_MAX_LEN 15
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_PROVISIONAL_LINK_KEY_MAX_LEN) sl_zigbee_direct_provisional_link_key_command_t;

/**
 * Joiners IEEE Address - Manage Joiners Characteristic
 */
#define SL_ZIGBEE_DIRECT_TLV_JOINERS_IEEE_ADDRESS_TAG_ID 0x01
#define SL_ZIGBEE_DIRECT_TLV_JOINERS_IEEE_ADDRESS_MIN_LEN 7
#define SL_ZIGBEE_DIRECT_TLV_JOINERS_IEEE_ADDRESS_MAX_LEN 7
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_JOINERS_IEEE_ADDRESS_MAX_LEN) sl_zigbee_direct_joiners_ieee_address_command_t;

/**
 * Manage Joiners command - Manage Joiners Characteristic
 */
#define SL_ZIGBEE_DIRECT_TLV_MANAGE_JONERS_COMMAND_TAG_ID 0x02
#define SL_ZIGBEE_DIRECT_TLV_MANAGE_JONERS_COMMAND_MIN_LEN 0
#define SL_ZIGBEE_DIRECT_TLV_MANAGE_JONERS_COMMAND_MAX_LEN 0
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_DIRECT_TLV_MANAGE_JONERS_COMMAND_MAX_LEN) sl_zigbeedirect_manage_joiners_command_t;

#endif // SILABS_ZIGBEE_DIRECT_TLV_H

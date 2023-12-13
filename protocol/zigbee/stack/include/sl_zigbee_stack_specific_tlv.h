/***************************************************************************//**
 * @file sl_zigbee_stack_specific_tlv.h
 * @brief Global and local Stack TLV defines
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_ZIGBEE_STACK_SPECIFIC_TLV_H
#define SL_ZIGBEE_STACK_SPECIFIC_TLV_H

#include "sl_zigbee_tlv_core.h"

#define BEACON_APPENDIX_VERSION         1
#define BEACON_APPENDIX_VERSION_LENGTH  1

#define TLV_HEADER_LENGTH 2
// NOTE the idea here is that unless there is some idea of an "empty"
// encapsulation tlv then it doesn't make sense for an encapsulation tlv
// to contain any less than 3 bytes
#define TLV_ENCAP_MIN_LENGTH (TLV_HEADER_LENGTH + 1)
#define ZB_LOCAL_TLV_LOCAL_TAG_END 64

/**
 * @brief given a Buffer handle and a list of tag ids, will append the TLV values to the buffer
 * @param buffer a reference to a message Buffer
 * @param index the starting index of the TLVs
 * @param tag_c the count of the argument tag ids
 * @param tag_v a pointer to the list of uint8 tag ids
 * @return An ::sl_status that indicates whether the configurations were added successfully to
 *         the TLVs in the given Buffer
 */
sl_status_t sl_zigbee_global_tlv_add_configurations(Buffer *buffer,
                                                    uint16_t index,
                                                    uint8_t tag_c,
                                                    uint8_t *tag_v);

/**
 * @brief given a list of tag ids, will return a buffer containing the local configuration values
 * @param tag_c the count of the argument tag ids
 * @param tag_v a pointer to the list of uint8 tag ids
 * @return a Buffer containing the serialized form of all recognized global tag ids with values,
 *         or NULL_BUFFER if an error occurred
 */
Buffer sl_zigbee_global_tlv_get_configurations(uint8_t tag_c, uint8_t *tag_v);

/**
 * Global TLVs
 * define tag id, minimum length, maximum length, concrete tlv_structs (?)
 * for right now min and max will largely be the same but it sets a better
 * precedent to define all of these constants
 *
 * Global TLV definitions must include certain attributes...
 * 1. Tag ID :: a unique identifier for the TLV.  Global TLV definitions must
 *    be in the range of 0x40-0xFF (64-255).
 * 2. Minimum Length :: the minimum valid length of the TLV.  TLV validation
 *    will throw an error if it encounters a Global TLV with < min_length
 * 3. Maximum Length :: the maximum number of expected bytes. Used to define
 *    and allocate TLV data structures.  When a TLV is encountered that is greater
 *    than the expected length we copy only up to what we know
 * Each Global TLV has a typedef'd struct, and possibly other helper functionality
 */

// NOTE Stack TLVs are defined in Annex I of Zigbee pro core R23 specification

/**
 * MFG Specific TLVs
 */
#define SL_ZIGBEE_GLOBAL_TLV_MFG_SPECIFIC_TAG_ID 64
#define SL_ZIGBEE_GLOBAL_TLV_MFG_SPECIFIC_MIN_LEN 2
#define SL_ZIGBEE_GLOBAL_TLV_MFG_SPECIFIC_MAX_LEN 255
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_MFG_SPECIFIC_MAX_LEN) sl_zigbee_global_tlv_mfg_specific_t;
// MFG Specific TLVs are the only valid duplicate tag ids
#define TLV_TAG_ID_IS_MFG_SPECIFIC(tag) ((tag) == SL_ZIGBEE_GLOBAL_TLV_MFG_SPECIFIC_TAG_ID)

/**
 * Supported Key Negotiation Methods
 */
// TODO adjust the lengths here
#define SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_TAG_ID 65
#define SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_MIN_LEN 2
#define SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_MAX_LEN 10
// Expected | SupportedKeyNegotiationMethodsBitmask (1) - SupportedSecretBitmask (1) - EUI64 (8)
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_MAX_LEN) sl_zigbee_global_tlv_supp_key_negotiation_t;

/// Helpers
/**
 * @brief generates the local device's supported key negotiation method bitmask TLV
 */
sl_zigbee_global_tlv_supp_key_negotiation_t sl_zigbee_global_tlv_supp_key_negotiation(void);
#define SL_ZIGBEE_DLK_NEGOTIATION_TLV_PROTOCOL_INDEX 0
#define SL_ZIGBEE_DLK_NEGOTIATION_TLV_SECRET_INDEX 1
#define SL_ZIGBEE_DLK_NEGOTIATION_TLV_LONG_ID_INDEX 2

/**
 * PAN ID Conflict Report
 */
#define SL_ZIGBEE_GLOBAL_TLV_PAN_ID_CONFLICT_TAG_ID 66
#define SL_ZIGBEE_GLOBAL_TLV_PAN_ID_CONFLICT_MIN_LEN 2
#define SL_ZIGBEE_GLOBAL_TLV_PAN_ID_CONFLICT_MAX_LEN 2
// Expected | ID Conflict Count (2)
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_PAN_ID_CONFLICT_MAX_LEN) sl_zigbee_global_tlv_pan_id_conflict_t;

/**
 * @brief returns the current values of the global pan id conflict report tlv
 */
sl_zigbee_global_tlv_pan_id_conflict_t sl_zigbee_global_tlv_pan_id_conflict(void);

/**
 * Next PAN ID
 */
#define SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_TAG_ID 67
#define SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_MIN_LEN 2
#define SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_MAX_LEN 2
// Expected | Next PAN ID (2)
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_MAX_LEN) sl_zigbee_global_tlv_next_pan_id_t;

/// Helpers
/**
 * @brief returns a Next PAN ID TLV data struct with the given PAN
 * @param pan_id the PAN ID to be contained in the resulting TLV
 * @return a TLV data struct
 */
sl_zigbee_global_tlv_next_pan_id_t sl_zigbee_global_tlv_next_pan_from_pan(EmberPanId pan_id);
/**
 * @brief given a reference to a Next PAN ID TLV struct, return the pan id
 * @param tlv a handle of the given TLV
 * @return the contained PAN ID
 */
EmberPanId sl_zigbee_global_tlv_next_pan_get_pan(sl_zigbee_global_tlv_next_pan_id_t *tlv);

/**
 * Next Channel Change
 */
#define SL_ZIGBEE_GLOBAL_TLV_NEXT_CHANNEL_CHANGE_TAG_ID 68
#define SL_ZIGBEE_GLOBAL_TLV_NEXT_CHANNEL_CHANGE_MIN_LEN 4
#define SL_ZIGBEE_GLOBAL_TLV_NEXT_CHANNEL_CHANGE_MAX_LEN 4
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_NEXT_CHANNEL_CHANGE_MAX_LEN) sl_zigbee_global_tlv_next_channel_change_t;

/**
 * Symmetric Passphrase
 */
#define ZB_GLOBAL_TLV_SYMMETRIC_PASSPHRASE_TAG_ID 69
#define ZB_GLOBAL_TLV_SYMMETRIC_PASSPHRASE_MIN_LEN 16
#define ZB_GLOBAL_TLV_SYMMETRIC_PASSPHRASE_MAX_LEN 16
typedef CONCRETE_TLV_DEFINE (ZB_GLOBAL_TLV_SYMMETRIC_PASSPHRASE_MAX_LEN) sl_zigbee_global_tlv_symmetric_passphrase_t;

/// Helpers
/**
 * @brief returns a Next Channel Change data struct encoded with the given parameters
 * @param page a uint representing the page number
 * @param channel a uint representing the channel number
 * @return a TLV data struct
 */
sl_zigbee_global_tlv_next_channel_change_t sl_zigbee_global_tlv_next_channel_from_pg_ch(uint8_t page,
                                                                                        uint8_t channel);
/**
 * @brief given a reference to a Next Channel Change TLV struct, return the encoded bitmask
 * @param tlv a handle of the given TLV
 * @return the contained channel change bitmask
 */
uint32_t sl_zigbee_global_tlv_next_channel_change_get_bitmask(sl_zigbee_global_tlv_next_channel_change_t *tlv);

/// Helpers
/**
 * @brief returns a Symmetric Passphrase TLV with the given passphrase
 * @param passphrase a pointer to the passphrase to be used
 * @return a TLV data struct
 */
sl_zigbee_global_tlv_symmetric_passphrase_t sl_zigbee_global_tlv_symmetric_passphrase(uint8_t *passphrase);

/**
 * Router Information
 */
#define SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_TAG_ID 70
#define SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_MIN_LEN 2
#define SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_MAX_LEN 2
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_MAX_LEN) sl_zigbee_global_tlv_router_information_t;

/** @brief encodes Router Information bitmask data, as per the definition of the Router Information Global TLV */
enum sl_router_info_bitmask_fields {
  /// This bit indicates the 'hub connectivity' of the local device.
  ROUTER_INFO_MASK_HUB_CONNECTIVITY     = 0x0001,
  /// This bit indicates the 'long uptime' of the router.  If the device has been operational for 24+ hours this bit should be set
  ROUTER_INFO_MASK_LONG_UPTIME          = 0x0002,
  /// This bit indicates 'preferred parent' status of the router.  extends the hub connectivity. allows the device to inform joiners
  /// or not they are a 'good' candidate for joining.
  ROUTER_INFO_MASK_PREFERRED_PARENT     = 0x0004,
  /// This bit indicates whether the device has battery backup
  ROUTER_INFO_MASK_BATTERY_BACKUP       = 0x0008,
  /// This bit indicates whether the router supports responding to enhanced beacon requests
  ROUTER_INFO_MASK_ENHANCED_BEACONS     = 0x0010,
  /// This bit indicates whether the router supports the MAC Data Poll Keepalive mechanism
  ROUTER_INFO_MASK_MAC_DATA_POLL        = 0x0020,
  /// This bit indicates whether the router suports the End Device Keepalive mechanism
  ROUTER_INFO_MASK_END_DEVICE_KEEPALIVE = 0x0040,
  /// This bit indicates whether the router supports power negotiation with end devices
  ROUTER_INFO_MASK_POWER_NEGOTIATION    = 0x0080,
  /// The remaining bits (8-15) are reserved and shall be 0
};

// Helpers
/**
 * @brief generates the local device's router information TLV
 */
sl_zigbee_global_tlv_router_information_t sl_zigbee_global_tlv_router_information(void);
/**
 * @brief returns the router information bitmask from the router information TLV
 */
uint16_t sl_zigbee_global_tlv_router_information_get_bitmask(sl_zigbee_global_tlv_router_information_t *tlv);

/**
 * Device Capability Extension
 */
#define SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_TAG_ID 76
#define SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_MIN_LEN 1
#define SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_MAX_LEN 2
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_MAX_LEN) sl_zigbee_global_tlv_device_capability_extension_t;

/**
 * @brief generates the local device capability extension TLV
 */
sl_zigbee_global_tlv_device_capability_extension_t sl_zigbee_global_tlv_device_capability_extension_param(uint16_t bitmask);

/**
 * Fragmentation Parameters
 */
#define SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_TAG_ID 71
#define SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_MIN_LEN 5
#define SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_MAX_LEN 5
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_MAX_LEN) sl_zigbee_global_tlv_fragmentation_param_t;

/// Helpers
/**
 * @brief generates the local device's fragmentation parameters TLV
 */
sl_zigbee_global_tlv_fragmentation_param_t sl_zigbee_global_tlv_fragmentation_param(void);

/**
 * Joiner Encapsulation
 */
#define SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_TAG_ID 72
#define SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_MIN_LEN TLV_ENCAP_MIN_LENGTH
#define SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_MAX_LEN 255
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_MAX_LEN) sl_zigbee_global_tlv_joiner_encap_t;

/// Helpers
/**
 * @brief generates the local device's joiner encapsulation TLV
 */
sl_status_t sl_zigbee_global_tlv_joiner_encapsulation(sl_zigbee_global_tlv_joiner_encap_t *encapTlv);

/**
 * Beacon Appendix Encapsulation
 */
#define SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_TAG_ID 73
#define SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_MIN_LEN TLV_ENCAP_MIN_LENGTH
#define SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_MAX_LEN 255
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_MAX_LEN) sl_zigbee_global_tlv_beacon_appendix_encap_t;

/// Helpers
/**
 * @brief generates the local device's beacon appendix encapsulation TLV
 */
sl_status_t sl_zigbee_global_tlv_beacon_appendix_encapsulation(sl_zigbee_global_tlv_beacon_appendix_encap_t *encapTlv);

/**
 * Configuration Params
 */
#define SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_TAG_ID 75
#define SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_MIN_LEN 2
#define SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_MAX_LEN 2
typedef CONCRETE_TLV_DEFINE (SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_MAX_LEN) sl_zigbee_global_tlv_configuration_params_t;

/// Config Mode Params
#define CONFIG_MODE_PARAM_ZDO_RESTRICTED_MODE_MASK (0x0000 | BIT(0))
#define CONFIG_MODE_PARAM_TRANSPORT_KEY_SECURITY_MASK (0x0000 | BIT(1))
#define CONFIG_MODE_PARAM_LEAVE_WITHOUT_REJOIN_MASK (0x0000 | BIT(2))
#define CONFIG_MODE_PARAM_RESERVED_FIELDS_MASK (0xFFFF & ~(BIT(0)   \
                                                           | BIT(1) \
                                                           | BIT(2)))
/// Helpers
/**
 * @brief generates a Configuration Mode Parameters TLV containing the given bitmask
 * @param mask the configuration mode parameters bitmask
 *        BIT(0)    - ZDO Restricted Mode (1 - on | 0 - off)
 *        BIT(1)    - Transport Key Security isRequired?
 *        BIT(2)    - Network Leave Without Rejoin isAllowed?
 *        BIT(3:15) - RESERVED
 * @return a Configuration Parameters TLV struct
 */
sl_zigbee_global_tlv_configuration_params_t sl_zigbee_global_tlv_configuration_params_from_bitmask(uint16_t mask);
/**
 * @brief returns the Configuration Mode Parameters bitmask contained in the given TLV
 * @param tlv a handle for the Configuration Params TLV
 * @return the bitmask contained in the value field of the given TLV
 */
uint16_t sl_zigbee_global_tlv_configuration_params_get_bitmask(sl_zigbee_global_tlv_configuration_params_t *tlv);

#define ZB_GLOBAL_TLV_TAG_ID_END 76

typedef union zigbee_global_tlv_union {
  sl_zigbee_global_tlv_supp_key_negotiation_t supportedKeymaskTlv;
  sl_zigbee_global_tlv_pan_id_conflict_t panConflictTlv;
  sl_zigbee_global_tlv_next_pan_id_t nextPanTlv;
  sl_zigbee_global_tlv_next_channel_change_t nextChannelTlv;
  sl_zigbee_global_tlv_symmetric_passphrase_t passphraseTlv;
  sl_zigbee_global_tlv_router_information_t routerInfoTlv;
  sl_zigbee_global_tlv_fragmentation_param_t fragmentationTlv;
  sl_zigbee_global_tlv_joiner_encap_t joinerEncapTlv;
  sl_zigbee_global_tlv_beacon_appendix_encap_t beaconAppendixEncapTlv;
  sl_zigbee_global_tlv_configuration_params_t configModeTlv;
  sl_zigbee_global_tlv_device_capability_extension_t deviceCapExtTlv;
  sl_zigbee_tlv_t tlv;
} sl_zigbee_global_tlv_u;

// without some kind of bit math to be able to identify encapsulation tlvs
// we have to define them explicitly
extern uint8_t sl_zigbee_encap_tlv_global_tag_ids[];

// EMZIGBEE-5835 prototype "smart encapsulation tlv tags"

#endif /* SL_ZIGBEE_STACK_SPECIFIC_TLV_H */

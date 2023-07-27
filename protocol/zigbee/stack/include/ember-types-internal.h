/***************************************************************************//**
 * @file
 * @brief This file holds internal definitions for files both internal and
 * externally available with the Gecko SDK. These definitions are not meant to
 * be modified or referenced by any user code.
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

#ifndef SILABS_EMBER_TYPES_INTERNAL_H
#define SILABS_EMBER_TYPES_INTERNAL_H

#include PLATFORM_HEADER
#include "ember.h"

#include "multi-mac.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#if defined EMBER_TEST
 #define EMBER_TEST_EXTERNAL
 #define EMBER_TEST_EXTERNAL_CONST
#else // EMBER_TEST
 #define EMBER_TEST_EXTERNAL static
 #define EMBER_TEST_EXTERNAL_CONST static const
#endif // EMBER_TEST

// Use user provided power value while forming/joining a network to be a max
// power value in link power delta calculation.
#if defined(MAC_DUAL_PRESENT) || defined(SL_CATALOG_ZIGBEE_PHY_2_4_SUBGHZ_SWITCH_COORDINATOR_PRESENT)
// Internal tests use the simulated PHY_EM250 phy.h
// Everything else for hardware can use upper-mac.h, which will
// pull in the right phy.h
#if !defined(ZIGBEE_STACK_ON_HOST) && !defined(PHY_EM250)
#include "upper-mac.h"
#endif // !defined(ZIGBEE_STACK_ON_HOST) && !defined(PHY_EM250)
#define sli_zigbee_sub_ghz_radio_channel sl_mac_upper_mac_state[1].nwk_radio_parameters[0].channel
#define sli_zigbee_sub_ghz_radio_power sl_mac_upper_mac_state[1].nwk_radio_parameters[0].tx_power
#define MAX_RADIO_POWER_USER_PROVIDED  sli_zigbee_sub_ghz_radio_power
#elif defined(EMBER_MULTI_NETWORK_STRIPPED)
#if !defined(ZIGBEE_STACK_ON_HOST) && !defined(PHY_EM250)
#include "upper-mac.h"
#define MAX_RADIO_POWER_USER_PROVIDED  (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].tx_power)
#else // MAC_DUAL_PRESENT || SL_CATALOG_ZIGBEE_PHY_2_4_SUBGHZ_SWITCH_COORDINATOR_PRESENT, !EMBER_MULTI_NETWORK_STRIPPED
// there is no radio on Linux, so this value is picked at random
#define MAX_RADIO_POWER_USER_PROVIDED  10
#endif//#ifndef ZIGBEE_STACK_ON_HOST
#else
extern uint8_t sli_zigbee_current_network_index;
extern void sli_zigbee_enable_application_current_network(void);
extern void sli_zigbee_restore_current_network_internal(void);
#define sli_zigbee_restore_current_network() (sli_zigbee_restore_current_network_internal())
#if !defined(ZIGBEE_STACK_ON_HOST) && !defined(PHY_EM250)
#include "upper-mac.h"
#define MAX_RADIO_POWER_USER_PROVIDED   (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].tx_power)
#else
// there is no radio on Linux, so this value is picked at random
#define MAX_RADIO_POWER_USER_PROVIDED  10
#endif//#ifndef ZIGBEE_STACK_ON_HOST
#endif

typedef uint8_t sli_802154mac_frame_info_element_type;
enum {
  EM_MAC_FRAME_INFO_ELEMENT_HEADER_TYPE  = 0,
  EM_MAC_FRAME_INFO_ELEMENT_PAYLOAD_TYPE = 1,
};

/**
 * @brief 802.15.4 Info Elements.
 *   This struct defines where the Info elements live in the packet.
 *   The index is relative to the PacketHeader and includes the
 *   Packet Header overhead (as opposed to beginning at the start of the
 *   packet).  This is because at the point we are dealing with
 *   IEs we are in the upper MAC / stack and operating directly
 *   on full MAC packets.  Right now only the MAC Beacon
 *   request is allowed to have IEs and that is consumed by the stack.
 */
typedef struct {
  uint16_t id;
  sli_802154mac_frame_info_element_type type;
  uint8_t indexInPacket;
  uint8_t length;
} sli_802154mac_info_element_field;

typedef enum {
  EM_MAC_FRAME_INFO_ELEMENTS_NOT_PRESENT,
  EM_MAC_FRAME_INFO_ELEMENTS_PRESENT_AND_VALID,
  EM_MAC_FRAME_INFO_ELEMENTS_PRESENT_WITH_ERRORS,
} sli_802154mac_frame_info_element_parse_result;

enum {
  NULL_OPERATION,
  GENERATE_EPHEMERAL_KEYS,
  DSA_SIGN,
  DSA_VERIFY,
  CALCULATE_SMACS_AS_INITIATOR,
  CALCULATE_SMACS_AS_RESPONDER,
  GENERATE_EPHEMERAL_KEYS_283K1,
  DSA_SIGN_283K1,
  DSA_VERIFY_283K1,
  CALCULATE_SMACS_AS_INITIATOR_283K1,
  CALCULATE_SMACS_AS_RESPONDER_283K1,
};
typedef uint8_t CryptoOperation;

enum {
  PACKET_VALIDATE_UNKNOWN              = 0,
  PACKET_VALIDATE_MAC_COMMAND          = 1,
  PACKET_VALIDATE_NWK                  = 2,
  PACKET_VALIDATE_NWK_COMMAND          = 3,
  PACKET_VALIDATE_APS                  = 4,
  PACKET_VALIDATE_APS_COMMAND          = 5,
};
typedef uint8_t PacketValidateType;

// This is negative logic to support all devices currently in the field
// without this bit set.
#define KEY_IS_NOT_AUTHORIZED (1UL << 16) // RAM bitmask value (private)
#define TC_EUI64_HAS_CHANGED_BITMASK (1UL << 28) // RAM bitmask value (private)
#define TCSO_EUI64_HAS_OCCURRED_BITMASK (1UL << 29) // RAM bitmask value (private)
// management code
//----------------------------------------------------------------
// PAN ID state
//
// PAN ID conflict states.  These need to be invalid PAN IDs because we encode
// the state in 'newPanId'.  We use these to:
//  - Put in a delay between PAN ID reports, to keep from flooding the network.
//  - Implement the required delay between receiving a PAN ID update and
//    actually changing the PAN ID.
// New states will be needed If we implement the suggested-but-not-actually-
// required active scan before sending a report or picking a new PAN ID.

#define PAN_ID_OKAY            0xFFFF
#define PAN_ID_REPORT_SENT     0xFFFE
//      PAN_ID_UPDATE_RECEIVED <any valid PAN ID>

// association code
// To make it easy to translate from the internal enumeration to
// the external one we embed the external enumeration in the low
// four bits of the internal.  Doing it this way also makes sure
// that every internal value has a corresponding external value.

enum {
  NETWORK_INITIAL                     = EMBER_NO_NETWORK,

  NETWORK_JOINING                     = EMBER_JOINING_NETWORK,
  NETWORK_JOINED_UNAUTHENTICATED      = EMBER_JOINING_NETWORK + 0x10,
  NETWORK_JOIN_FAILED                 = EMBER_JOINING_NETWORK + 0x20,
  NETWORK_JOINING_USING_REJOIN        = EMBER_JOINING_NETWORK + 0x30,
  NETWORK_JOINED_WAITING_FOR_LINK_KEY = EMBER_JOINING_NETWORK + 0x40,

  NETWORK_JOINED                      = EMBER_JOINED_NETWORK,

  NETWORK_JOINED_NO_PARENT            = EMBER_JOINED_NETWORK_NO_PARENT,
  NETWORK_ORPHAN_SCAN                 = EMBER_JOINED_NETWORK_NO_PARENT + 0x10,
  NETWORK_ORPHAN_SCAN_COMPLETE        = EMBER_JOINED_NETWORK_NO_PARENT + 0x20,
  NETWORK_REJOINING                   = EMBER_JOINED_NETWORK_NO_PARENT + 0x30,
  NETWORK_REJOINED_UNAUTHENTICATED    = EMBER_JOINED_NETWORK_NO_PARENT + 0x40,
  NETWORK_LEAVING_AND_REJOINING       = EMBER_JOINED_NETWORK_NO_PARENT + 0x50,

  NETWORK_JOINED_S2S_INITIATOR        = EMBER_JOINED_NETWORK_S2S_INITIATOR,
  NETWORK_JOINED_S2S_TARGET           = EMBER_JOINED_NETWORK_S2S_TARGET,

  NETWORK_LEAVING                     = EMBER_LEAVING_NETWORK,
};

// NOTE from association.h
typedef struct {
  // Configured values for joining or rejoining
  EmberJoinMethod joinMethod;
  EmberPanId      panIdToJoinTo;
  uint8_t         extendedPanIdToJoinTo[EXTENDED_PAN_ID_SIZE];

  // Internal state variables
  bool            beaconReceived;
  bool            scanComplete;
  EmberStatus     rejoinReason;
  EmberStatus     reasonForFailure;
  uint8_t         pollAttemptsRemaining;
} JoinState;

// NOTE from sl_zigbee_network_commissioning.h
typedef PacketHeader (*sli_zigbee_network_request_t)(EmberNodeId destination, EmberJoinMethod join_method);

#endif // SILABS_EMBER_TYPES_INTERNAL_H

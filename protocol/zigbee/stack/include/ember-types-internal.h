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
#ifndef ZIGBEE_STACK_ON_HOST
#include "upper-mac.h"
#endif
#include "multi-mac.h"
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if defined EMBER_TEST
 #define EMBER_TEST_EXTERNAL
 #define EMBER_TEST_EXTERNAL_CONST
#else // EMBER_TEST
 #define EMBER_TEST_EXTERNAL static
 #define EMBER_TEST_EXTERNAL_CONST const static
#endif // EMBER_TEST

// Use user provided power value while forming/joining a network to be a max
// power value in link power delta calculation.
#if defined(MAC_DUAL_PRESENT) || defined(SL_CATALOG_ZIGBEE_PHY_2_4_SUBGHZ_SWITCH_COORDINATOR_PRESENT)
#define emSubGhzRadioChannel sl_mac_upper_mac_state[1].nwk_radio_parameters[0].channel
#define emSubGhzRadioPower sl_mac_upper_mac_state[1].nwk_radio_parameters[0].tx_power
#define MAX_RADIO_POWER_USER_PROVIDED  emSubGhzRadioPower
#elif defined(EMBER_MULTI_NETWORK_STRIPPED)
#define emEnableApplicationCurrentNetwork()
#define emRestoreCurrentNetwork()
#ifndef ZIGBEE_STACK_ON_HOST
#define MAX_RADIO_POWER_USER_PROVIDED  (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].tx_power)
#else
// there is no radio on Linux, so this value is picked at random
#define MAX_RADIO_POWER_USER_PROVIDED  10
#endif//#ifndef ZIGBEE_STACK_ON_HOST
#else
extern uint8_t emCurrentNetworkIndex;
extern void emEnableApplicationCurrentNetwork(void);
extern void emRestoreCurrentNetworkInternal(void);
#define emRestoreCurrentNetwork() (emRestoreCurrentNetworkInternal())
#ifndef ZIGBEE_STACK_ON_HOST
#define MAX_RADIO_POWER_USER_PROVIDED   (sl_mac_upper_mac_state[0].nwk_radio_parameters[emCurrentNetworkIndex].tx_power)
#else
// there is no radio on Linux, so this value is picked at random
#define MAX_RADIO_POWER_USER_PROVIDED  10
#endif//#ifndef ZIGBEE_STACK_ON_HOST
#endif

typedef uint8_t EmMacFrameInfoElementType;
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
  EmMacFrameInfoElementType type;
  uint8_t indexInPacket;
  uint8_t length;
} EmMacInfoElementField;

typedef enum {
  EM_MAC_FRAME_INFO_ELEMENTS_NOT_PRESENT,
  EM_MAC_FRAME_INFO_ELEMENTS_PRESENT_AND_VALID,
  EM_MAC_FRAME_INFO_ELEMENTS_PRESENT_WITH_ERRORS,
} EmMacFrameInfoElementParseResult;

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

#endif // SILABS_EMBER_TYPES_INTERNAL_H

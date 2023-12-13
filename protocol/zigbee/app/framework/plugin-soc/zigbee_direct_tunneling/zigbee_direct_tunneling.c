/***************************************************************************//**
 * @file zigbee_direct_tunneling.c
 * @brief Zigbee Direct - Zigbee Direct tunneling code
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
#include PLATFORM_HEADER

#include "hal.h"
#include "ember.h"
#include "af.h"
#include "sl_cli.h"
#include "sl_component_catalog.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "stack/include/ember-types.h"
#include "stack/include/sl_zigbee_tlv_core.h"
#include "stack/include/sl_zigbee_stack_specific_tlv.h"
#include "stack/include/sl_zigbee_address_info.h"
#include "stack/include/zigbee-security-manager.h"
#include "zigbee_direct_tlv.h"
#include "zigbee_direct_common.h"
#include <string.h>

// Defined by the Zigbee Spec
#define  SL_ZIGBEE_REJOIN_REQUEST  0x06
#define  SL_ZIGBEE_REJOIN_RESPONSE 0x07
#define  SL_ZIGBEE_NETWORK_COMMISSIONING_REQUEST  0x0E
#define  SL_ZIGBEE_NETWORK_COMMISSIONING_RESPONSE 0x0F

// this is the index from the start of phy header + phy len
#define SL_ZIGBEE_REJOIN_RESPONSE_INDEX 34
#define SL_ZIGBEE_REJOIN_REQUEST_INDEX 26

static bool commissioning_request_received = FALSE;
static bool commissioning_request_is_rejoin = FALSE;

extern bleConnectionTable_t bleConnectionTable[SL_BT_CONFIG_MAX_CONNECTIONS];
extern sl_status_t sli_tlv_chain_find_link_tag(sl_zigbee_tlv_chain *tlv,
                                               tlv_link_t *t,
                                               uint8_t tag_id);
extern void sli_zigbee_direct_send_commissioning_response(uint8_t status, EmberNodeId dst, EmberEUI64 longDest);
extern bool sli_zigbee_direct_send_ephemeral_key(EmberNodeId destinationShortId,
                                                 EmberEUI64 destinationLongId,
                                                 EmberEUI64 sourceOrPartnerLongId,
                                                 uint8_t keyType,
                                                 EmberKeyData* keyData,
                                                 uint8_t options);
extern sl_status_t sli_zigbee_transient_device_mgmt_finish(sl_zigbee_address_info *device_ids,
                                                           bool store);

static uint8_t commissioning_tlvs[100];
static uint8_t commissioning_tlvs_size;
static uint8_t sl_zigbee_direct_transport_key_type = 0x00;

static void sli_handle_commissioning_request(uint8array *message, uint8_t tlv_length, uint8_t offset)
{
  sl_nwk_packet_exchange_t my_nwk_packet;
  EmberStatus status;
  commissioning_request_received = TRUE;
  commissioning_request_is_rejoin = TRUE;

  sl_zigbee_app_debug_println("Association Type %X, Capabilities: %X TLV length: %X", message->data[21 + offset], message->data[22 + offset], tlv_length);
  sl_zigbee_app_debug_print("Attached TLVs");
  for (uint8_t i = 0; i < tlv_length; i++) {
    sl_zigbee_app_debug_print(" %X", message->data[i + 23 + offset]);
    commissioning_tlvs[i] = message->data[i + 23 + offset];
  }
  sl_zigbee_app_debug_println("");
  commissioning_tlvs_size = tlv_length;

  //extract the EUI64 from packet
  MEMCOPY(sl_zvd_eui, &message->data[12 + offset], EUI64_SIZE);
  sl_zigbee_app_debug_print("Extracted EUI64:");
  for (uint8_t i = 0; i < EUI64_SIZE; i++) {
    sl_zigbee_app_debug_print(" %X", sl_zvd_eui[i]);
  }
  sl_zigbee_app_debug_println("");

  if (message->data[21 + offset] == 0x01) { // re-join
    commissioning_request_is_rejoin = TRUE;
  } else if (message->data[21 + offset] == 0x00) { //initial join
    commissioning_request_is_rejoin = FALSE;
  } else {
    commissioning_request_is_rejoin = FALSE;
    commissioning_request_received = FALSE;
    sl_zigbee_core_debug_println("WARNING unhandled commissioning type %X", message->data[21 + offset]);
  }

  //assemble re-join command and pass upstream
  message->data[20 + offset] = 0x06;
  message->data[21 + offset] = message->data[22 + offset]; //capability information

  sl_zigbee_app_debug_print("Fake re-join command: ");
  for (uint8_t i = 0; i < 22 + offset; i++) {
    sl_zigbee_app_debug_print(" %X", message->data[i]);
  }
  sl_zigbee_app_debug_println("");

  my_nwk_packet.bitmask = (message->data[2] & 0x01);
  my_nwk_packet.mac_interface_id = 0;
  my_nwk_packet.network_packet = &message->data[4];
  my_nwk_packet.network_packet_length = message->data[3] - tlv_length; // fake re-join request length
  my_nwk_packet.nwk_index = 0;
  status = slx_zigbee_add_to_incoming_network_queue(-40, 255, &my_nwk_packet);
  emberRtosStackWakeupIsrHandler();
  sl_zigbee_core_debug_println("Submitted fake rejoin request to incoming queue with Status:%X", status);

  incoming_counter = 0; //reset frame counter
}

void sl_zigbee_direct_tunnel_write(uint8_t connection, uint8array *writeValue)
{
  EmberStatus status = EMBER_SUCCESS;
  tlv_link_t sl_tlv_pointer;
  sl_nwk_packet_exchange_t my_nwk_packet;

  sl_zigbee_app_debug_print("Received tunnel data [%X", writeValue->data[0]);
  for (uint8_t i = 1; i < writeValue->len; i++) {
    sl_zigbee_app_debug_print(" %X", writeValue->data[i]);
  }
  sl_zigbee_app_debug_println("]");

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_zigbee_tunnel_2))) {
    sl_bt_gatt_server_send_user_write_response(connection, gattdb_zigbee_tunnel_2, ES_ERR_APPLICATION_SPECIFIC);
    return;
  }

  writeValue->len = writeValue->len - 8;
  sl_zigbee_tlv_chain sl_my_tlv_chain = { writeValue->data, writeValue->len };

  if (sli_tlv_chain_find_link_tag(&sl_my_tlv_chain, &sl_tlv_pointer, SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_MESSAGE_TAG_ID) == SL_STATUS_OK) {
    sl_zigbee_app_debug_println("Received a NPDU request with flags: %X and length: %X Message [%X", writeValue->data[2], writeValue->data[3], writeValue->data[4]);
    for (uint8_t i = 1; i < writeValue->data[3]; i++) {
      sl_zigbee_app_debug_print(" %X", writeValue->data[i + 4]);
    }
    sl_zigbee_app_debug_println("]");

    sl_bt_gatt_server_send_user_write_response(connection, gattdb_zigbee_tunnel_2, ES_WRITE_OK);

    if (writeValue->data[20] == SL_ZIGBEE_REJOIN_REQUEST) {
      sl_zvd_node_id = emberFetchLowHighInt16u(&writeValue->data[8]);
      sl_zigbee_app_debug_println("Received Re-join Request: Identified ZVDs Network Address to be %2X", sl_zvd_node_id);
    } else if ((writeValue->data[20] == SL_ZIGBEE_NETWORK_COMMISSIONING_REQUEST)
               && (writeValue->data[5] == 0x10)) {
      sl_zvd_node_id = emberFetchLowHighInt16u(&writeValue->data[8]);
      sl_zigbee_app_debug_println("Received Network Commissioning Request 1. Identified ZVDs Network Address to be %2X", sl_zvd_node_id);
      if (writeValue->data[2] & 0x01) {
        sl_zigbee_core_debug_println("ERROR Security Enable flag is set to true for a NWK commissioning Request, continuing anyway");
      }
      sli_handle_commissioning_request(writeValue, (writeValue->len - 22), 0);
      return;
    } else if ((writeValue->data[28] == SL_ZIGBEE_NETWORK_COMMISSIONING_REQUEST)
               && (writeValue->data[5] == 0x18)) { // In case long source is included
      sl_zvd_node_id = emberFetchLowHighInt16u(&writeValue->data[8]);
      sl_zigbee_app_debug_println("Received Network Commissioning Request 2. Identified ZVDs Network Address to be %2X", sl_zvd_node_id);
      if (writeValue->data[2] & 0x01) {
        sl_zigbee_core_debug_println("ERROR Security Enable flag is set to true for a NWK commissioning Request, continuing anyway");
      }
      sli_handle_commissioning_request(writeValue, (writeValue->len - 30), 8);
      return;
    }

    my_nwk_packet.bitmask = (writeValue->data[2] & 0x01);
    my_nwk_packet.mac_interface_id = 0;
    my_nwk_packet.network_packet = &writeValue->data[4];
    my_nwk_packet.network_packet_length = writeValue->data[3];
    my_nwk_packet.nwk_index = 0;
    my_nwk_packet.nwk_short_address = sl_zvd_node_id;
    slx_zigbee_add_to_incoming_network_queue(-40, 255, &my_nwk_packet);
    emberRtosStackWakeupIsrHandler();
  }
  sl_zigbee_core_debug_println("Added to incoming queue with Status:%X", status);
}

void sl_zigbee_direct_tunnel_indicate(uint8_t *packet, uint8_t length)
{
  uint8_t sl_my_data[SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_REQUEST_MAX_LEN + 10]; //+8 for MIC and FC have been included
  EmberStatus status;
  sl_status_t ble_status;

  sl_my_data[4] = SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_MESSAGE_TAG_ID; //Type
  sl_my_data[5] = length + 1; //Length
  if (packet[1] & 0x02) { //Value: Flags //packet[5]
    sl_zigbee_app_debug_println("Setting security flag");
    sl_my_data[6] = 0x01; // Flags -> Security enabled
  } else {
    sl_zigbee_app_debug_println("Clearing security flag");
    sl_my_data[6] = 0x00;
  }
  sl_my_data[7] = length; //Value: NPDU length

  sl_zigbee_app_debug_println("length: %X", length);

  MEMCOPY(&sl_my_data[8], packet, length);//Value: NPDU

  //set security bit in NWK header (bit 9) to 0
  sl_my_data[9] &= 0xFD;

  sl_zigbee_app_debug_print("Sending NPDU Indication: [%X", sl_my_data[4]);
  for (uint8_t j = 1; j < length + 4; j++) {
    sl_zigbee_app_debug_print(" %X", sl_my_data[j + 4]);
  }
  sl_zigbee_app_debug_println("]");

  status = sl_zigbee_direct_security_encrypt_packet(emberGetEui64(), &sl_my_data[4], length + 4, gattdb_zigbee_tunnel_2);
  if (status != EMBER_SUCCESS) {
    sl_zigbee_app_debug_println("Issue encrypting");
    return;
  }
  sl_zigbee_app_debug_print("Sending encrypted NPDU Indication: [%X", sl_my_data[0]);
  for (uint8_t j = 1; j < length + 12; j++) {
    sl_zigbee_app_debug_print(" %X", sl_my_data[j]);
  }
  sl_zigbee_app_debug_println("]");

  ble_status = sl_bt_gatt_server_send_indication(bleConnectionTable[0].connectionHandle,
                                                 gattdb_zigbee_tunnel_2,
                                                 length + 12,
                                                 sl_my_data);
  if (ble_status != SL_STATUS_OK) {
    sl_zigbee_app_debug_println("Error: ble sent with status %2X", ble_status);
  }
}

EmberPacketAction emberAfIncomingPacketFilterCallback(EmberZigbeePacketType packetType,
                                                      uint8_t* packetData,
                                                      uint8_t* size_p,
                                                      void *data)
{
  sl_zigbee_app_debug_print("Incoming packet type %X:", packetType);
  for (uint8_t j = 0; j < *size_p; j++) {
    sl_zigbee_app_debug_print(" %X", packetData[j]);
  }
  sl_zigbee_app_debug_println("");

  // catch tunneling transport key message for ZVD
  if ((packetType == EMBER_ZIGBEE_PACKET_TYPE_APS_COMMAND)
      && (packetData[0] == 0x0e)  // 0x0e = APS_CMD_TUNNEL
      && (memcmp(&packetData[1], sl_zvd_eui, EUI64_SIZE) == 0)) {
    sl_zigbee_app_debug_println("Caught aps tunnel command for ZVD");
    // If the APS command frame is not using APS layer security, the APSME of the ZDD SHALL examine the APSME command identifier,
    // and in case of a Transport Key message, the StandardKeyType field of that message.
    // If the StandardKeyType equals 'Standard network key' (0x01) the message is considered a Transport Key message conveying
    // an active or prospective network key and the APSME SHALL decline forwarding of this frame to the ZVD.
    if ((packetData[9] & 0x20) == 0x00) {  // No APS security
      if ((packetData[11] == 0x05) && (packetData[12] == 0x01)) {    // 0x05 = APS_CMD_TRANSPORT_KEY //0x01 Standard network key
        sl_zigbee_app_debug_println("Caught unencrypted Transport Key Message with standard key type, dropping and disconnecting!");
        sl_bt_connection_close(sl_my_connection);
        return EMBER_DROP_PACKET;
      }
    } else {  //APS security
      // If the APS command frame is using APS layer encryption, the APSME of the ZDD SHALL examine the auxiliary security header,
      // and in particular the Key Identifier sub-field of the Security Control field. If the Key Identifier equals 'key-transport key' (0x02)
      // the message is already decrypted here, so I am here assuming it was decrypted using the well-known key.
      sl_zigbee_app_debug_println("Tunnel command is using APS crypto");
      uint8_t pkt = packetData[11] & 0x18;
      if (sli_zigbee_direct_tc_is_zigbee_direct_aware == false) {
        sl_zigbee_app_debug_println("It is a legacy network");
        if (pkt == 0x10) {          //key-transport key
          sl_zigbee_app_debug_println("Caught Key Transport Key Message!");

          EmberStatus status = EMBER_SUCCESS;
          if (status == EMBER_SUCCESS) {
            sl_zigbee_app_debug_println("Decryption with default key succeeded!");
          } else {
            sl_zigbee_app_debug_println("No luck decrypting with default key", status);
          }

          sl_zb_sec_man_key_t zigbeeAlliance09Key = ZIGBEE_3_CENTRALIZED_SECURITY_LINK_KEY;
          status = sl_zb_sec_man_import_link_key(0xFF,
                                                 sl_zvd_eui,
                                                 &zigbeeAlliance09Key);
          sl_zigbee_app_debug_println("Adding well known key with status: %x", status);
          status = sli_zigbee_direct_send_ephemeral_key(sl_zvd_node_id,
                                                        sl_zvd_eui,
                                                        NULL, //should be ok as this is the TC address
                                                        0xB0, //KEY_TRANSPORT_EPHEMERAL_GLOBAL_LINK_KEY
                                                        NULL,
                                                        0x02);//ENCRYPTION_APS
          sl_zigbee_app_debug_println("Sent transport key with type KEY_TRANSPORT_EPHEMERAL_GLOBAL_LINK_KEY and status %X", status);
          return EMBER_DROP_PACKET;
        } else if (pkt == 0x20) {         //key-load key
          sl_zigbee_app_debug_println("Caught  Key Load Key Message!");
          sl_zigbee_direct_transport_key_type = 0x00;
          sl_zigbee_address_info my_zvd_address_info;
          memcpy(my_zvd_address_info.device_long, sl_zvd_eui, EUI64_SIZE);
          my_zvd_address_info.device_short = sl_zvd_node_id;
          sli_zigbee_transient_device_mgmt_finish(&my_zvd_address_info, true);
          //let it go its way...
        }
      } else {  //TC is Zigbee Direct aware
        if ( pkt == 0x10) {           //key-transport key
          sl_zigbee_app_debug_println("Caught suspect Transport Key Message, dropping and disconnecting!");
          sl_bt_connection_close(sl_my_connection);
          return EMBER_DROP_PACKET;
        } else {
          sl_zigbee_app_debug_println("Moving device on from transient table"); //this is not happening in ZD aware situation
          sl_zigbee_address_info my_zvd_address_info;
          memcpy(my_zvd_address_info.device_long, sl_zvd_eui, EUI64_SIZE);
          my_zvd_address_info.device_short = sl_zvd_node_id;
          sli_zigbee_transient_device_mgmt_finish(&my_zvd_address_info, true);
        }
      }
    }
  }
  return EMBER_ACCEPT_PACKET;
}

static void ble_tx_handler(PacketHeader packet,
                           uint8_t *packetData,
                           uint8_t mac_index,
                           uint8_t nwk_index)

{
  uint8_t len = packetData[0];
  uint8_t networkPayloadIndex = sl_mac_flat_payload_offset(packetData, true);
  // Outgoing Network Packet Filtering
  uint16_t sl_nodeId = emberFetchLowHighInt16u(&packetData[networkPayloadIndex + 2]);
  sl_zigbee_app_debug_print("ble_tx_handler sl_zvd_node_id %4X != networkPayloadIndex %d len %d\n ",
                            sl_zvd_node_id, networkPayloadIndex, len);
  if (sl_nodeId >= EMBER_BROADCAST_ADDRESS) {
    // there is no other way to check if this is broadcast
    // this has already also been submitted to macSubmit
    sl_zigbee_app_debug_println("Forwarding Broadcast to ZVD");
    sl_zigbee_direct_tunnel_indicate(packetData, len /* *size_p*/);
  } else {   //this message has arrived here, being aimed for BLE interface ID
    uint8_t network_packet_length = len - networkPayloadIndex;
    sl_zigbee_app_debug_println("Outgoing Packet Filter NWK_DATA ");
    for (uint8_t i = networkPayloadIndex; i < network_packet_length; i++) {
      sl_zigbee_app_debug_print(" %X", packetData[i]);
    }
    sl_zigbee_app_debug_println("");

    // check for re-join response
    if ((packetData[SL_ZIGBEE_REJOIN_RESPONSE_INDEX] == SL_ZIGBEE_REJOIN_RESPONSE) && (commissioning_request_received)) {
      sl_zigbee_app_debug_println("Packet is re-join response, mangle it, length %X", networkPayloadIndex);
      commissioning_request_received = FALSE;
      packetData[SL_ZIGBEE_REJOIN_RESPONSE_INDEX] = SL_ZIGBEE_NETWORK_COMMISSIONING_RESPONSE; //turn into a NWK association response
    }
    sl_zigbee_direct_tunnel_indicate(packetData + networkPayloadIndex, network_packet_length);
    sl_zigbee_app_debug_println("Packet is for ZVD, drop it");
  }

  //catching an association response
  if (len > (networkPayloadIndex + 21)) { // raw-mac
    if ((packetData[networkPayloadIndex + 21] == 0x02) && (memcmp(&packetData[networkPayloadIndex + 5], sl_zvd_eui, EUI64_SIZE) == 0)) { //0x02 = association
      sl_zigbee_app_debug_println("Caught association response, sending commissioning response");
      sli_zigbee_direct_send_commissioning_response(packetData[24], sl_zvd_node_id, sl_zvd_eui); //status of association response
      //DROP_PACKET;
    }
  }
  return;
}

#define MAX_FLAT_PACKET_SIZE 127
uint8_t outgoing_flat_packet[MAX_FLAT_PACKET_SIZE];
void sli_zigbee_af_plugin_zdd_tunneling_redirect_outgoing_message_callback(uint8_t mac_index,
                                                                           EmberMessageBuffer packet,
                                                                           EmberTransmitPriority priority)
{
  // a mac level raw packet is received here
  uint8_t packetLength = emberMessageBufferLength(packet);
  emberCopyFromLinkedBuffers(packet,
                             0,
                             outgoing_flat_packet,
                             packetLength);
  ble_tx_handler(packet, outgoing_flat_packet, mac_index, 0);
  return;
}

EmberPacketAction emberAfOutgoingPacketFilterCallback(EmberZigbeePacketType packetType,
                                                      uint8_t* packetData,
                                                      uint8_t* size_p,
                                                      void* data)
{
  sl_zigbee_app_debug_print("Outgoing Packet type %X [", packetType);
  for (uint8_t i = 0; i < *size_p; i++) {
    sl_zigbee_app_debug_print(" %X:", packetData[i]);
  }
  sl_zigbee_app_debug_println("]");

  if ((packetType == EMBER_ZIGBEE_PACKET_TYPE_NWK_DATA) || (packetType == EMBER_ZIGBEE_PACKET_TYPE_NWK_COMMAND)) {
    if (emberFetchLowHighInt16u(&packetData[2]) == sl_zvd_node_id) {
      sl_zigbee_app_debug_print("Outgoing Packet Filter NWK_DATA ");
      for (uint8_t i = 0; i < *size_p; i++) {
        sl_zigbee_app_debug_print(" %X", packetData[i]);
      }
      sl_zigbee_app_debug_println("");

      // check for re-join response
      if ((packetData[24] == SL_ZIGBEE_REJOIN_RESPONSE) && (commissioning_request_received)) {
        sl_zigbee_app_debug_println("Packet is re-join response, mangle it, length %X", *size_p);
        commissioning_request_received = FALSE;
        packetData[24] = SL_ZIGBEE_NETWORK_COMMISSIONING_RESPONSE; //turn into a NWK association response
      }
      sl_zigbee_direct_tunnel_indicate(packetData, *size_p);
      sl_zigbee_app_debug_println("Packet is for ZVD, drop it");
      return EMBER_DROP_PACKET;
    }
  }

  if ((packetType == EMBER_ZIGBEE_PACKET_TYPE_APS_COMMAND)) {
    // check for update device (APS Command 0x06)
    if ((packetData[0] == 0x06) && (commissioning_request_received)) {
      packetData[*size_p - 1] = 0x01;    //fake type to be 0x01
      sl_zigbee_app_debug_println("Caught Update Device, appending TLVs of length %X", commissioning_tlvs_size);
      MEMCOPY(&packetData[*size_p], commissioning_tlvs, commissioning_tlvs_size);
      *size_p = *size_p + commissioning_tlvs_size;
      return EMBER_MANGLE_PACKET;
    }

    // check for transport key (APS Command 0x05)
    if (packetData[0] == 0x05) {
      sl_zigbee_app_debug_println("Caught Transport Key Command");
      return EMBER_ACCEPT_PACKET;
    }
  }
  return EMBER_ACCEPT_PACKET;
}

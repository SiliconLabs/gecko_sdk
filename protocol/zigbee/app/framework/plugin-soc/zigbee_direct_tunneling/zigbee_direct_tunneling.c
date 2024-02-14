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
#include "rail.h"
#include "ember.h"
#include "af.h"
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

// Defined by the Zigbee Spec todo delete once on a r23 compliant stack
#define  SL_ZIGBEE_REJOIN_REQUEST  0x06
#define  SL_ZIGBEE_REJOIN_RESPONSE 0x07
#define  SL_ZIGBEE_NETWORK_COMMISSIONING_REQUEST  0x0E
#define  SL_ZIGBEE_NETWORK_COMMISSIONING_RESPONSE 0x0F
// this is the index from the start of phy header + phy len
#define SL_ZIGBEE_REJOIN_RESPONSE_INDEX 34
#define SL_ZIGBEE_REJOIN_REQUEST_INDEX 26
#define LONG_SOURCE_INCLUDED 0x18
#define LONG_SOURCE_NOT_INCLUDED 0x10
#define NPDU_INDEX_FLAGS 2
#define NPDU_INDEX_LENGTH 3
#define MAX_MTU 512 //maximum usable MTU size

//prototypes
extern bleConnectionTable_t bleConnectionTable[SL_BT_CONFIG_MAX_CONNECTIONS];
extern void sli_zigbee_direct_send_commissioning_response(uint8_t status, EmberNodeId dst, EmberEUI64 longDest);
extern bool sli_zigbee_direct_send_ephemeral_key(EmberNodeId destinationShortId,
                                                 EmberEUI64 destinationLongId,
                                                 EmberEUI64 sourceOrPartnerLongId,
                                                 uint8_t keyType,
                                                 EmberKeyData* keyData,
                                                 uint8_t options);
extern sl_status_t sli_zigbee_transient_device_mgmt_finish(sl_zigbee_address_info *device_ids,
                                                           bool store);
//global variables
static bool commissioning_request_received = false;
static uint8_t commissioning_tlvs[100];
static uint8_t commissioning_tlvs_size;
static sl_nwk_packet_exchange_t my_nwk_packet;
static uint8_t packet_from_zvd[MAX_MTU];

//local events
static sl_zigbee_event_t zb_incoming_tunnel_data_event;
static sl_zigbee_event_t zb_schedule_indication_event;
static sl_zigbee_event_t zb_tunnel_indicate_event;

#define INCOMING_COMMAND_ID_INDEX 21
//this is needed with a pre r23 stack which doesn't natively handle commissioning request/responses
static void sli_handle_commissioning_request(uint8array *message, uint8_t tlv_length, uint8_t offset)
{
  uint8_t length_without_tlvs;

  if (message->data[NPDU_INDEX_LENGTH] > tlv_length) {
    length_without_tlvs = message->data[NPDU_INDEX_LENGTH] - tlv_length;
  } else {
    return;
  }

  sl_zigbee_app_debug_println("Association Type %X, Capabilities: %X TLV length: %X", message->data[21 + offset], message->data[22 + offset], tlv_length);
  sl_zigbee_app_debug_print("Attached TLVs:");
  for (uint8_t i = 0; i < tlv_length; i++) {
    sl_zigbee_app_debug_print(" %X", message->data[i + 23 + offset]);
    commissioning_tlvs[i] = message->data[i + 23 + offset];
  }
  sl_zigbee_app_debug_println("");
  commissioning_tlvs_size = tlv_length;

  //extract the EUI64 from packet
  MEMCOPY(sl_zvd_eui, &message->data[12 + offset], EUI64_SIZE);
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  sl_zigbee_app_debug_print("Extracted EUI64:");
  for (uint8_t i = 0; i < EUI64_SIZE; i++) {
    sl_zigbee_app_debug_print(" %X", sl_zvd_eui[i]);
  }
  sl_zigbee_app_debug_println("");
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  // confirm that commissioning request type is either 0x00 (initial join), 0x01 (rejoin), or 0x02 (establish secure link)
  if ((message->data[INCOMING_COMMAND_ID_INDEX + offset] >= 0x00) && (message->data[INCOMING_COMMAND_ID_INDEX + offset] <= 0x02)) {
    commissioning_request_received = true;
  } else {
    commissioning_request_received = false;
    sl_zigbee_core_debug_println("WARNING unhandled commissioning type %X", message->data[INCOMING_COMMAND_ID_INDEX + offset]);
  }

  //assemble re-join command and pass upstream
  message->data[20 + offset] = 0x06; //re-join command ID
  message->data[21 + offset] = message->data[22 + offset]; //capability information

#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  sl_zigbee_app_debug_print("Fake re-join command: ");
  for (uint8_t i = 0; i < 22 + offset; i++) {
    sl_zigbee_app_debug_print(" %X", message->data[i]);
  }
  sl_zigbee_app_debug_println("");
#endif //SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

  my_nwk_packet.bitmask = (message->data[NPDU_INDEX_FLAGS] & 0x01);
  my_nwk_packet.mac_interface_id = 0;
  MEMCOPY(packet_from_zvd, &message->data[4], length_without_tlvs);
  my_nwk_packet.network_packet = packet_from_zvd;
  my_nwk_packet.network_packet_length = length_without_tlvs;
  my_nwk_packet.nwk_index = 0;
  sl_zigbee_event_set_active(&zb_incoming_tunnel_data_event);
  sl_zigbee_common_rtos_wakeup_stack_task();
  incoming_counter = 0; //reset frame counter
}

//this is called when data is arriving via the BLE tunneling service
void sl_zigbee_direct_tunnel_write(uint8_t connection, uint8array *writeValue)
{
  sl_zigbee_tlv_t *payload_tlv_ptr;

#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  sl_zigbee_app_debug_print("Received tunnel data [%X", writeValue->data[0]);
  for (uint8_t i = 1; i < writeValue->len; i++) {
    sl_zigbee_app_debug_print(" %X", writeValue->data[i]);
  }
  sl_zigbee_app_debug_println("]");
#endif //SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_zigbee_tunnel_2))) {
    sl_bt_gatt_server_send_user_write_response(connection, gattdb_zigbee_tunnel_2, ES_ERR_APPLICATION_SPECIFIC);
    return;
  }
  writeValue->len = writeValue->len - 8;

  if (sl_zigbee_tlv_ptr_find_by_id(writeValue->data, writeValue->len, SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_MESSAGE_TAG_ID, &payload_tlv_ptr) == SL_STATUS_OK) {
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
    sl_zigbee_app_debug_println("Received a NPDU request with flags: %X and length: %X Message [%X", writeValue->data[2], writeValue->data[3], writeValue->data[4]);
    for (uint8_t i = 1; i < writeValue->data[3]; i++) {
      sl_zigbee_app_debug_print(" %X", writeValue->data[i + 4]);
    }
    sl_zigbee_app_debug_println("]");
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

    sl_bt_gatt_server_send_user_write_response(connection, gattdb_zigbee_tunnel_2, ES_WRITE_OK);

    if ((writeValue->data[20] == SL_ZIGBEE_REJOIN_REQUEST) && (writeValue->data[5] == LONG_SOURCE_NOT_INCLUDED)) {
      sl_zvd_node_id = emberFetchLowHighInt16u(&writeValue->data[8]);
      sl_zigbee_app_debug_println("Received Re-join Request: Identified ZVDs Network Address to be %2X", sl_zvd_node_id);
    } else if ((writeValue->data[20] == SL_ZIGBEE_NETWORK_COMMISSIONING_REQUEST)
               && (writeValue->data[5] == LONG_SOURCE_NOT_INCLUDED)) {
      sl_zvd_node_id = emberFetchLowHighInt16u(&writeValue->data[8]);
      sl_zigbee_app_debug_println("Received Network Commissioning Request 1. Identified ZVDs Network Address to be %2X", sl_zvd_node_id);
      sli_handle_commissioning_request(writeValue, (writeValue->len - 22), 0);
      return;
    } else if ((writeValue->data[28] == SL_ZIGBEE_NETWORK_COMMISSIONING_REQUEST)
               && (writeValue->data[5] == LONG_SOURCE_INCLUDED)) {
      sl_zvd_node_id = emberFetchLowHighInt16u(&writeValue->data[8]);
      sl_zigbee_app_debug_println("Received Network Commissioning Request 2. Identified ZVDs Network Address to be %2X", sl_zvd_node_id);
      sli_handle_commissioning_request(writeValue, (writeValue->len - 30), 8);
      return;
    }

    my_nwk_packet.bitmask = (writeValue->data[2] & 0x01);
    my_nwk_packet.mac_interface_id = 0;
    MEMCOPY(packet_from_zvd, &writeValue->data[4], writeValue->data[3]);
    my_nwk_packet.network_packet = packet_from_zvd;
    my_nwk_packet.network_packet_length = writeValue->data[3];
    my_nwk_packet.nwk_index = 0;
    my_nwk_packet.nwk_short_address = sl_zvd_node_id;

    //ATOMIC(sl_zigbee_event_set_delay_ms(&zb_incoming_tunnel_data_event, 5); );
    sl_zigbee_event_set_active(&zb_incoming_tunnel_data_event);
    sl_zigbee_common_rtos_wakeup_stack_task();
  }
}

//queue NPDU(s) to be sent to the ZVD
#define NPDU_TLV_OVERHEAD 4
uint8_t outgoing_npdu_queue[MAX_MTU];
uint16_t outgoing_npdu_queue_size = NPDU_TLV_OVERHEAD;
static void sli_zigbee_direct_queue_outgoing_npdu(uint8_t *packet, uint8_t length)
{
  sl_status_t status;
  uint16_t max_mtu;

  status =  sl_bt_gatt_server_get_mtu(bleConnectionTable[0].connectionHandle, &max_mtu);   //todo support more than a single connection
  if ((status != SL_STATUS_OK) || (outgoing_npdu_queue_size + length + 6) >  max_mtu) {
    sl_zigbee_app_debug_println("Can't queue further outgoing messages, max MTU reached");
    return;   //todo we may want to do more than to just drop the message if max mtu is reached, maybe queue?
  }

  sl_zigbee_app_debug_println("Queuing %X characters to Outgoing queue of size %2X", length, outgoing_npdu_queue_size);
  outgoing_npdu_queue[outgoing_npdu_queue_size++] = SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_MESSAGE_TAG_ID; //Type
  outgoing_npdu_queue[outgoing_npdu_queue_size++] = length + 1; //Length
  if (packet[1] & 0x02) {  //Value: Flags
    sl_zigbee_app_debug_println("Setting NPDU security flag");
    outgoing_npdu_queue[outgoing_npdu_queue_size++] = 0x01;  // Flags -> Security enabled
  } else {
    sl_zigbee_app_debug_println("Clearing NPDU security flag");
    outgoing_npdu_queue[outgoing_npdu_queue_size++] = 0x00;
  }
  outgoing_npdu_queue[outgoing_npdu_queue_size++] = length; //Value: NPDU length

  MEMCOPY(&outgoing_npdu_queue[outgoing_npdu_queue_size], packet, length); //Value: NPDU
  outgoing_npdu_queue[outgoing_npdu_queue_size + 1] &= 0xFD;    // always set security bit in NWK header (bit 9) to 0
  outgoing_npdu_queue_size += length;

  //trigger event for sending if not already active
  if ((sl_zigbee_event_is_scheduled(&zb_schedule_indication_event) == false) && (sl_zigbee_event_is_scheduled(&zb_tunnel_indicate_event) == false)) {
    sl_zigbee_event_set_active(&zb_schedule_indication_event);
    sl_zigbee_common_rtos_wakeup_stack_task();
  }
}

//schedule an indication to be sent for the next connection interval
void sli_zigbee_af_schedule_indication_event_handler(sl_zigbee_event_t *event)
{
  uint32_t access_address;
  uint8_t role;
  uint32_t crc_init;
  uint16_t interval;
  uint16_t supervision_timeout;
  uint8_t central_clock_accuracy;
  uint8_t central_phy;
  uint8_t peripheral_phy;
  uint8_t channel_selection_algorithm;
  uint8_t hop;
  sl_bt_connection_channel_map_t channel_map;
  uint8_t channel;
  uint16_t event_counter;
  uint32_t time_to_next_connection_event;
  RAIL_Time_t rail_time;

  sl_zigbee_event_set_inactive(&zb_schedule_indication_event);

  sl_bt_connection_get_scheduling_details(bleConnectionTable[0].connectionHandle,
                                          &access_address,
                                          &role,
                                          &crc_init,
                                          &interval,
                                          &supervision_timeout,
                                          &central_clock_accuracy,
                                          &central_phy,
                                          &peripheral_phy,
                                          &channel_selection_algorithm,
                                          &hop,
                                          &channel_map,
                                          &channel,
                                          &event_counter,
                                          &time_to_next_connection_event);

  rail_time = RAIL_GetTime();
  time_to_next_connection_event = time_to_next_connection_event - rail_time;
  time_to_next_connection_event = (time_to_next_connection_event >> 10);

  sl_zigbee_app_debug_println("time_to_next_connection_event ms %4X", time_to_next_connection_event);

  if (time_to_next_connection_event <= 1) {
    sl_zigbee_event_set_active(&zb_tunnel_indicate_event);
  } else {
    sl_zigbee_event_set_delay_ms(&zb_tunnel_indicate_event, (time_to_next_connection_event - 2)); //allow 2ms slack
  }
  sl_zigbee_common_rtos_wakeup_stack_task();
}

// and send send NPDU(s) via the tunnel to the ZVD
void sli_zigbee_af_tunnel_indicate_event_handler(sl_zigbee_event_t *event)
{
  sl_status_t status;

  sl_zigbee_event_set_inactive(&zb_tunnel_indicate_event);

  if (sl_zigbee_direct_security_encrypt_packet(emberGetEui64(), &outgoing_npdu_queue[4], outgoing_npdu_queue_size + 4, gattdb_zigbee_tunnel_2) != EMBER_SUCCESS) {
    return;
  }

  status = sl_bt_gatt_server_send_indication(bleConnectionTable[0].connectionHandle,
                                             gattdb_zigbee_tunnel_2,
                                             outgoing_npdu_queue_size + 12,
                                             outgoing_npdu_queue);
  if (status != SL_STATUS_OK) {
    sl_zigbee_app_debug_println("Error: BLE TX with status %2X", status);
  }
  outgoing_npdu_queue_size = NPDU_TLV_OVERHEAD;
}

EmberPacketAction emberAfIncomingPacketFilterCallback(EmberZigbeePacketType packetType,
                                                      uint8_t* packetData,
                                                      uint8_t* size_p,
                                                      void *data)
{
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  sl_zigbee_app_debug_print("Incoming packet type %X:", packetType);
  for (uint8_t j = 0; j < *size_p; j++) {
    sl_zigbee_app_debug_print(" %X", packetData[j]);
  }
  sl_zigbee_app_debug_println("");
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

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

//todo loose this with r23 compliant stack, no need to mangle outgoing packets any more
EmberPacketAction emberAfOutgoingPacketFilterCallback(EmberZigbeePacketType packetType,
                                                      uint8_t* packetData,
                                                      uint8_t* size_p,
                                                      void* data)
{
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  sl_zigbee_app_debug_print("Outgoing Packet type %0X [", packetType);
  for (uint8_t i = 0; i < *size_p; i++) {
    sl_zigbee_app_debug_print(" %0X:", packetData[i]);
  }
  sl_zigbee_app_debug_println("]");
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

  if ((packetType == EMBER_ZIGBEE_PACKET_TYPE_NWK_DATA) || (packetType == EMBER_ZIGBEE_PACKET_TYPE_NWK_COMMAND)) {
    if (emberFetchLowHighInt16u(&packetData[2]) == sl_zvd_node_id) {
    #ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
      sl_zigbee_app_debug_print("Outgoing Packet Filter NWK_DATA ");
      for (uint8_t i = 0; i < *size_p; i++) {
        sl_zigbee_app_debug_print(" %0X", packetData[i]);
      }
      sl_zigbee_app_debug_println("");
    #endif //SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

      // check for re-join response
      if ((*size_p >= 24) && (packetData[24] == SL_ZIGBEE_REJOIN_RESPONSE) && (commissioning_request_received)) {
        sl_zigbee_app_debug_println("Packet is re-join response, mangle it, length %X", *size_p);
        commissioning_request_received = false;
        packetData[24] = SL_ZIGBEE_NETWORK_COMMISSIONING_RESPONSE; //turn into a NWK association response
      }

      sli_zigbee_direct_queue_outgoing_npdu(packetData, *size_p);
      sl_zigbee_app_debug_println("Packet is for ZVD, drop it");
      return EMBER_DROP_PACKET;
    }
  }

  if ((packetType == EMBER_ZIGBEE_PACKET_TYPE_APS_COMMAND)) {
    // check for update device (APS Command 0x06)
    if ((packetData[0] == 0x06) && (commissioning_request_received)) {
      packetData[*size_p - 1] = 0x01;    //fake type to be 0x01
      sl_zigbee_app_debug_println("Caught Update Device, appending TLVs of length %0X", commissioning_tlvs_size);
      MEMCOPY(&packetData[*size_p], commissioning_tlvs, commissioning_tlvs_size);
      *size_p = *size_p + commissioning_tlvs_size;
      return EMBER_MANGLE_PACKET;
    }
  }
  return EMBER_ACCEPT_PACKET;
}

//the event to handle data coming over BLE from the ZVD
static void sli_zigbee_af_incoming_tunnel_data_event_handler(sl_zigbee_event_t *event)
{
  EmberStatus status;

  status = slx_zigbee_add_to_incoming_network_queue(-40, 255, &my_nwk_packet);
  sl_zigbee_core_debug_println("Submitted to incoming queue with Status:%0X", status);
  sl_zigbee_common_rtos_wakeup_stack_task();
}

//this function is handling outgoing packets targetting the ZVD
static void ble_tx_handler(uint8_t *packetData,
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
    sli_zigbee_direct_queue_outgoing_npdu(packetData, len);
  } else {   //this message has arrived here, being aimed for BLE interface ID
    uint8_t network_packet_length = len - networkPayloadIndex;
    sl_zigbee_app_debug_println("Forwarding Unicast to ZVD");
    for (uint8_t i = networkPayloadIndex; i < network_packet_length; i++) {
      sl_zigbee_app_debug_print(" %X", packetData[i]);
    }
    sl_zigbee_app_debug_println("");

    // check for re-join response todo remove once on r23 compliant stack
    if ((packetData[SL_ZIGBEE_REJOIN_RESPONSE_INDEX] == SL_ZIGBEE_REJOIN_RESPONSE) && (commissioning_request_received)) {
      sl_zigbee_app_debug_println("Packet is re-join response, mangle it, length %X", networkPayloadIndex);
      commissioning_request_received = false;
      packetData[SL_ZIGBEE_REJOIN_RESPONSE_INDEX] = SL_ZIGBEE_NETWORK_COMMISSIONING_RESPONSE; //turn into a NWK commissioning response
    }
    sli_zigbee_direct_queue_outgoing_npdu(packetData + networkPayloadIndex, network_packet_length);
    sl_zigbee_app_debug_println("Packet is for ZVD, drop it");
  }

  //catching an association response todo remove once on r23 compliant stack
  if (len > (networkPayloadIndex + 21)) { // raw-mac
    if ((packetData[networkPayloadIndex + 21] == 0x02) && (memcmp(&packetData[networkPayloadIndex + 5], sl_zvd_eui, EUI64_SIZE) == 0)) { //0x02 = association
      sl_zigbee_app_debug_println("Caught association response, sending commissioning response");
      sli_zigbee_direct_send_commissioning_response(packetData[24], sl_zvd_node_id, sl_zvd_eui); //status of association response
      //DROP_PACKET;
    }
  }
}

// This is called by the Zigbee Stack
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
  ble_tx_handler(outgoing_flat_packet, mac_index, 0);
}

// Initialization of tunneling events
void sli_zigbee_af_zdd_tunneling_init(uint8_t init_level)
{
  switch (init_level) {
    case SL_ZIGBEE_INIT_LEVEL_EVENT:
    {
      sl_zigbee_event_init(&zb_incoming_tunnel_data_event, sli_zigbee_af_incoming_tunnel_data_event_handler);
      sl_zigbee_event_init(&zb_schedule_indication_event, sli_zigbee_af_schedule_indication_event_handler);
      sl_zigbee_event_init(&zb_tunnel_indicate_event, sli_zigbee_af_tunnel_indicate_event_handler);
      break;
    }

    default:
      break;
  }
}

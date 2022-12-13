/***************************************************************************//**
 * @file
 * @brief Utility internal code that provides useful CLI commands and
 * application logic to perform dynamic multiprotocol testing between ZigBee and
 * BLE.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "af.h" // includes sl_component_catalog.h
#include "sl_cli.h"
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#ifdef SL_CATALOG_ZIGBEE_DEBUG_EXTENDED_PRESENT
#include "ember-debug.h"
#endif //SL_CATALOG_ZIGBEE_DEBUG_EXTENDED_PRESENT
#ifdef SL_CATALOG_ZIGBEE_DEBUG_BASIC_PRESENT
#include "zigbee_debug_channel.h"
#endif //SL_CATALOG_ZIGBEE_DEBUG_BASIC_PRESENT
#include "network_test_config.h"

//------------------------------------------------------------------------------
// Defines and variables.
#define MAX_ZIGBEE_TX_TEST_MESSAGE_LENGTH   70
#define ZIGBEE_TX_TEST_MAX_INFLIGHT         5

typedef struct {
  bool in_use;
  uint32_t start_time;
  uint8_t seqn;
} in_flight_info_t;
#define MAXIMUM_MESSAGE_LENGTH 255
static struct {
  EmberApsOption aps_options;
  EmberNodeId destination;
  uint8_t message_length;
  uint16_t message_total_count;
  uint16_t message_running_count;
  uint16_t message_success_count;
  uint8_t max_in_flight;
  uint8_t current_in_flight;
  uint16_t tx_delay_ms;
  uint32_t start_time;
  uint32_t min_send_time_ms;
  uint32_t max_send_time_ms;
  uint32_t sum_send_time_ms;
  in_flight_info_t in_flight_info_table[ZIGBEE_TX_TEST_MAX_INFLIGHT];
  uint8_t message_payload[MAXIMUM_MESSAGE_LENGTH];
} zigbee_tx_test_info;

static sl_zigbee_event_t zigbee_tx_test_event;
static uint16_t sequence_counter;

static sl_zigbee_event_t zigbee_large_network_event;
void zigbee_large_network_event_handler(sl_zigbee_event_t *event);

//------------------------------------------------------------------------------
// Extern and Forward declarations

extern EmberStatus emAfSend(EmberOutgoingMessageType type,
                            uint16_t indexOrDestination,
                            EmberApsFrame *aps_frame,
                            uint8_t messageLength,
                            uint8_t *message,
                            uint16_t *messageTag,
                            EmberNodeId alias,
                            uint8_t sequence);
static void print_zigbee_tx_test_stats(void);
void zigbee_tx_test_event_handler(sl_zigbee_event_t *event);

//------------------------------------------------------------------------------
// ZigBee callbacks and event handlers

void sli_zigbee_network_test_init(uint8_t init_level)
{
  switch (init_level) {
    case SL_ZIGBEE_INIT_LEVEL_EVENT:
    {
      sl_zigbee_event_init(&zigbee_tx_test_event, zigbee_tx_test_event_handler);
      sl_zigbee_event_init(&zigbee_large_network_event, zigbee_large_network_event_handler);
      break;
    }

    default:
    {
      break;
    }
  }
}

void sli_zigbee_network_test_message_sent_callback(EmberIncomingMessageType type,
                                                   uint16_t index_or_destination,
                                                   EmberApsFrame *aps_frame,
                                                   EmberMessageBuffer message,
                                                   EmberStatus status)
{
  (void)type;
  (void)index_or_destination;
  (void)message;

  // This is a message sent out as part of the ZigBee TX test
  if ((aps_frame->profileId == 0x7F01 && aps_frame->clusterId == 0x0001)
      || (aps_frame->clusterId == 0x0042)) {
    uint32_t packet_send_time_ms = 0xFFFFFFFF;
    uint8_t i;

    if (zigbee_tx_test_info.current_in_flight > 0) {
      zigbee_tx_test_info.current_in_flight--;
    }

    for (i = 0; i < ZIGBEE_TX_TEST_MAX_INFLIGHT; i++) {
      if (zigbee_tx_test_info.in_flight_info_table[i].seqn == aps_frame->sequence
          || (aps_frame->clusterId == 0x0042)) {
        zigbee_tx_test_info.in_flight_info_table[i].in_use = false;
        packet_send_time_ms =
          elapsedTimeInt32u(zigbee_tx_test_info.in_flight_info_table[i].start_time,
                            halCommonGetInt32uMillisecondTick());
        break;
      }
    }

    if (status == EMBER_SUCCESS) {
      zigbee_tx_test_info.message_success_count++;
      zigbee_tx_test_info.sum_send_time_ms += packet_send_time_ms;

      if (zigbee_tx_test_info.min_send_time_ms > packet_send_time_ms) {
        zigbee_tx_test_info.min_send_time_ms = packet_send_time_ms;
      }
      if (zigbee_tx_test_info.max_send_time_ms < packet_send_time_ms) {
        zigbee_tx_test_info.max_send_time_ms = packet_send_time_ms;
      }
    }

    if (zigbee_tx_test_info.current_in_flight == 0
        && zigbee_tx_test_info.message_running_count
        >= zigbee_tx_test_info.message_total_count) {
      print_zigbee_tx_test_stats();
    }
  }
}

static void print_zigbee_tx_test_stats(void)
{
  uint32_t total_send_time_ms =
    elapsedTimeInt32u(zigbee_tx_test_info.start_time,
                      halCommonGetInt32uMillisecondTick());
  uint64_t throughput = (zigbee_tx_test_info.message_success_count
                         * zigbee_tx_test_info.message_length * 8);
  throughput = throughput * 1000;
  throughput = throughput / total_send_time_ms;

  sl_zigbee_app_debug_print("ZigBee TX done\n");
  sl_zigbee_app_debug_print("Total time %lums\n", total_send_time_ms);
  sl_zigbee_app_debug_print("Success messages: %d out of %d\n",
                            zigbee_tx_test_info.message_success_count,
                            zigbee_tx_test_info.message_total_count);
  sl_zigbee_app_debug_print("Throughput: %llu bits/s\n", throughput);

  if (zigbee_tx_test_info.message_success_count > 0) {
    sl_zigbee_app_debug_print("Min packet send time: %lu ms\n",
                              zigbee_tx_test_info.min_send_time_ms);
    sl_zigbee_app_debug_print("Max packet send time: %lu ms\n",
                              zigbee_tx_test_info.max_send_time_ms);
    sl_zigbee_app_debug_print("Avg packet send time: %lu ms\n",
                              (zigbee_tx_test_info.sum_send_time_ms
                               / zigbee_tx_test_info.message_success_count));
  }
}

void zigbee_tx_test_start_random(sl_cli_command_arg_t *arguments)
{
  // If a test is already in progress, do not corrupt the ongoing test data
  if (sl_zigbee_event_is_scheduled(&zigbee_large_network_event)) {
    sl_zigbee_app_debug_print("Test is in progress. Exiting\n");
    return;
  }

  zigbee_tx_test_info.message_length = sl_cli_get_argument_uint8(arguments, 0);
  zigbee_tx_test_info.message_total_count = sl_cli_get_argument_uint16(arguments, 1);
  zigbee_tx_test_info.max_in_flight = sl_cli_get_argument_uint8(arguments, 2);
  zigbee_tx_test_info.destination = sl_cli_get_argument_uint16(arguments, 3);
  zigbee_tx_test_info.tx_delay_ms = 0;
  sequence_counter = sl_cli_get_argument_uint16(arguments, 4);

  if (zigbee_tx_test_info.max_in_flight > ZIGBEE_TX_TEST_MAX_INFLIGHT) {
    sl_zigbee_app_debug_print("Error: max allowed in flight is %d\n",
                              ZIGBEE_TX_TEST_MAX_INFLIGHT);
    return;
  }

  if (zigbee_tx_test_info.message_total_count == 0
      || zigbee_tx_test_info.message_total_count == 0xFFFF) {
    sl_zigbee_app_debug_print("Error: invalid message count\n");
    return;
  }

  // First byte is the message length
  zigbee_tx_test_info.message_payload[0] = 0xFA;
  zigbee_tx_test_info.message_payload[1] = 0xDE;
  zigbee_tx_test_info.message_payload[2] = 0xFE;
  // Indices 3,4 are sequence number set in the event handler

  // Init the the rest of the message payload with progressive byte values
  for (uint8_t i = 5; i < zigbee_tx_test_info.message_length; i++) {
    zigbee_tx_test_info.message_payload[i] = i - 5;
  }

  zigbee_tx_test_info.current_in_flight = 0;
  zigbee_tx_test_info.message_running_count = 0;
  zigbee_tx_test_info.message_success_count = 0;
  zigbee_tx_test_info.start_time = halCommonGetInt32uMillisecondTick();
  zigbee_tx_test_info.min_send_time_ms = 0xFFFFFFFF;
  zigbee_tx_test_info.max_send_time_ms = 0;
  zigbee_tx_test_info.sum_send_time_ms = 0;

  for (uint8_t i = 0; i < ZIGBEE_TX_TEST_MAX_INFLIGHT; i++) {
    zigbee_tx_test_info.in_flight_info_table[i].in_use = false;
  }

  sl_zigbee_app_debug_print("ZigBee TX test started\n");

  // Set event to active - do not call handler from here since this is run
  // from the CLI task context. sli_cli_post_cmd_hook will post a flag that
  // allows the Zigbee task to run at which point in time the event handler will
  // run and start the test. !!! ember APIs are not thread safe !!!
  sl_zigbee_event_set_active(&zigbee_large_network_event);
}

void zigbee_large_network_event_handler(sl_zigbee_event_t *event)
{
  EmberApsFrame apsf;
  apsf.sourceEndpoint = 0x01;
  apsf.destinationEndpoint = 0x01;
  apsf.options = EMBER_AF_DEFAULT_APS_OPTIONS;
  apsf.clusterId = 0x0042; // counted packets cluster
  apsf.sequence = 0x00;

  if (zigbee_tx_test_info.max_in_flight > 0
      && zigbee_tx_test_info.current_in_flight >= zigbee_tx_test_info.max_in_flight) {
    // Max in flight reached, wait and try again.
    sl_zigbee_event_set_delay_ms(&zigbee_large_network_event, 1);
    return;
  }

  // fourth and fifth bytes are sequence counters
  zigbee_tx_test_info.message_payload[3] = (sequence_counter >> 8);
  zigbee_tx_test_info.message_payload[4] = (sequence_counter);

  if (EMBER_SUCCESS == emberAfSendUnicast(EMBER_OUTGOING_DIRECT,
                                          zigbee_tx_test_info.destination,
                                          &apsf,
                                          zigbee_tx_test_info.message_length,
                                          zigbee_tx_test_info.message_payload)) {
    zigbee_tx_test_info.message_running_count++;
    zigbee_tx_test_info.current_in_flight++;
    sequence_counter++;
    uint8_t i;
    for (i = 0; i < ZIGBEE_TX_TEST_MAX_INFLIGHT; i++) {
      if (!zigbee_tx_test_info.in_flight_info_table[i].in_use) {
        zigbee_tx_test_info.in_flight_info_table[i].in_use = true;
        zigbee_tx_test_info.in_flight_info_table[i].seqn = apsf.sequence;
        zigbee_tx_test_info.in_flight_info_table[i].start_time = halCommonGetInt32uMillisecondTick();
        break;
      }
    }
    assert(i < ZIGBEE_TX_TEST_MAX_INFLIGHT);
  }

  if (zigbee_tx_test_info.message_running_count
      >= zigbee_tx_test_info.message_total_count) {
    sl_zigbee_event_set_inactive(&zigbee_large_network_event);
  } else {
    sl_zigbee_event_set_active(&zigbee_large_network_event);
  }
}

void zigbee_tx_test_event_handler(sl_zigbee_event_t *event)
{
  (void)event;

  EmberApsFrame aps_frame;
  uint16_t message_tag;
  uint8_t i;

  if (zigbee_tx_test_info.max_in_flight > 0
      && zigbee_tx_test_info.current_in_flight >= zigbee_tx_test_info.max_in_flight) {
    // Max in flight reached, wait and try again.
    sl_zigbee_event_set_delay_ms(&zigbee_tx_test_event, 1);
    return;
  }

  aps_frame.sourceEndpoint = 0xFF;
  aps_frame.destinationEndpoint = 0xFF;
  aps_frame.options = zigbee_tx_test_info.aps_options;
  aps_frame.profileId = 0x7F01; // test profile ID
  aps_frame.clusterId = 0x0001; // counted packets cluster

  // First byte is the message length
  zigbee_tx_test_info.message_payload[0] = zigbee_tx_test_info.message_length;

  // Second and third bytes are the message counter
  zigbee_tx_test_info.message_payload[1] = LOW_BYTE(zigbee_tx_test_info.message_running_count);
  zigbee_tx_test_info.message_payload[2] = HIGH_BYTE(zigbee_tx_test_info.message_running_count);

  // fourth and fifth bytes are sequence counters
  zigbee_tx_test_info.message_payload[3] = (sequence_counter >> 8);
  zigbee_tx_test_info.message_payload[4] = (sequence_counter);

  uint8_t outgoing_type =  (zigbee_tx_test_info.destination == 0xFFFF) ? EMBER_OUTGOING_BROADCAST : EMBER_OUTGOING_DIRECT;
  if (emAfSend(outgoing_type,
               zigbee_tx_test_info.destination,
               &aps_frame,
               zigbee_tx_test_info.message_length,
               zigbee_tx_test_info.message_payload,
               &message_tag,
               0xFFFF,
               0) == EMBER_SUCCESS) {
    zigbee_tx_test_info.message_running_count++;
    zigbee_tx_test_info.current_in_flight++;
    sequence_counter++;

    for (i = 0; i < ZIGBEE_TX_TEST_MAX_INFLIGHT; i++) {
      if (!zigbee_tx_test_info.in_flight_info_table[i].in_use) {
        zigbee_tx_test_info.in_flight_info_table[i].in_use = true;
        zigbee_tx_test_info.in_flight_info_table[i].seqn = aps_frame.sequence;
        zigbee_tx_test_info.in_flight_info_table[i].start_time =
          halCommonGetInt32uMillisecondTick();
        break;
      }
    }
    assert(i < ZIGBEE_TX_TEST_MAX_INFLIGHT);
  }

  if (zigbee_tx_test_info.message_running_count
      >= zigbee_tx_test_info.message_total_count) {
    sl_zigbee_event_set_inactive(&zigbee_tx_test_event);
  } else {
    sl_zigbee_event_set_delay_ms(&zigbee_tx_test_event,
                                 zigbee_tx_test_info.tx_delay_ms);
  }
}

// ZigBee related commands
void zigbee_tx_test_start_command(sl_cli_command_arg_t *arguments)
{
  uint8_t i;

  // If a test is already in progress, do not corrupt the ongoing test data
  if (sl_zigbee_event_is_scheduled(&zigbee_tx_test_event)) {
    sl_zigbee_app_debug_print("Test is in progress. Exiting\n");
    return;
  }

  zigbee_tx_test_info.message_length = sl_cli_get_argument_uint8(arguments, 0);

  if (zigbee_tx_test_info.message_length > MAX_ZIGBEE_TX_TEST_MESSAGE_LENGTH) {
    sl_zigbee_app_debug_print("Error: max allowed message payload is %d\n",
                              MAX_ZIGBEE_TX_TEST_MESSAGE_LENGTH);
    return;
  }

  zigbee_tx_test_info.max_in_flight = sl_cli_get_argument_uint8(arguments, 3);

  if (zigbee_tx_test_info.max_in_flight > ZIGBEE_TX_TEST_MAX_INFLIGHT) {
    sl_zigbee_app_debug_print("Error: max allowed in flight is %d\n",
                              ZIGBEE_TX_TEST_MAX_INFLIGHT);
    return;
  }

  zigbee_tx_test_info.message_total_count = sl_cli_get_argument_uint16(arguments, 1);

  if (zigbee_tx_test_info.message_total_count == 0
      || zigbee_tx_test_info.message_total_count == 0xFFFF) {
    sl_zigbee_app_debug_print("Error: invalid message count\n");
    return;
  }

  zigbee_tx_test_info.tx_delay_ms = sl_cli_get_argument_uint16(arguments, 2);
  zigbee_tx_test_info.destination = sl_cli_get_argument_uint16(arguments, 4);
  zigbee_tx_test_info.aps_options = sl_cli_get_argument_uint16(arguments, 5);
  // Init the the rest of the message payload with progressive byte values
  for (i = 5; i < zigbee_tx_test_info.message_length; i++) {
    zigbee_tx_test_info.message_payload[i] = i - 5;
  }

  zigbee_tx_test_info.current_in_flight = 0;
  zigbee_tx_test_info.message_running_count = 0;
  zigbee_tx_test_info.message_success_count = 0;
  zigbee_tx_test_info.start_time = halCommonGetInt32uMillisecondTick();
  zigbee_tx_test_info.min_send_time_ms = 0xFFFFFFFF;
  zigbee_tx_test_info.max_send_time_ms = 0;
  zigbee_tx_test_info.sum_send_time_ms = 0;

  for (i = 0; i < ZIGBEE_TX_TEST_MAX_INFLIGHT; i++) {
    zigbee_tx_test_info.in_flight_info_table[i].in_use = false;
  }

  sl_zigbee_app_debug_print("ZigBee TX test started\n");

  // Set event to active - do not call handler from here since this is run
  // from the CLI task context. sli_cli_post_cmd_hook will post a flag that
  // allows the Zigbee task to run at which point in time the event handler will
  // run and start the test. !!! ember APIs are not thread safe !!!
  sl_zigbee_event_set_active(&zigbee_tx_test_event);
}

void zigbee_tx_test_stop_command(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  sl_zigbee_event_set_inactive(&zigbee_tx_test_event);
  zigbee_tx_test_info.message_total_count = 0;
}

#ifndef EZSP_HOST

void zigbee_set_passive_ack_config(sl_cli_command_arg_t *arguments)
{
  uint8_t config = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t min_acks_needed = sl_cli_get_argument_uint8(arguments, 1);

  if (config > SL_PASSIVE_ACK_THRESHOLD_WITH_REBROADCAST_ALL_NODES) {
    sl_zigbee_app_debug_print("Invalid config\n");
    return;
  }

  sl_set_passive_ack_config((sl_passive_ack_config_enum_t)config, min_acks_needed);

  sl_zigbee_app_debug_print("Passive ACKs configured: config=%d, min_acks=%d\n",
                            config, min_acks_needed);
}

#endif // EZSP_HOST

#if (LARGE_NETWORK_TESTING == 1)

#include "sl_zigbee_pro_stack_config.h"
extern uint8_t emNewBroadcastEntryThreshold;

// raw 0x0042 { FA DE FE 00 01}
// send 0xffff 1 1

// For ping
// raw 0x0043 { FA DE FE 00 01}
// send 0x0000 1 1
bool emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd)
{
  // Print debug message for latency timing.
  if (cmd->apsFrame->clusterId == 0x0042) {
    uint8_t *msg_contents = cmd->buffer;
    if (msg_contents[0] == 0xFA && msg_contents[1] == 0xDE ) {
      emDebugBinaryFormat(EM_DEBUG_LATENCY, "BBBB",
                          0x00, // frame control, top bit is start/stop
                          2, //2 byte sequence number
                          msg_contents[3],
                          msg_contents[4]);
      return true;
    }
  } else if (cmd->apsFrame->clusterId == 0x0043) {
    EmberApsFrame apsFrame;
    memcpy(&apsFrame, cmd->apsFrame, sizeof(apsFrame));
    apsFrame.clusterId = 0x0044;
    (void)emberAfSendUnicast(EMBER_OUTGOING_DIRECT,
                             cmd->source,
                             &apsFrame,
                             cmd->bufLen,
                             cmd->buffer);

    return true;
  } else if (cmd->apsFrame->clusterId == 0x0044) {
    #define INDEX_OF_SEQ_NUM_START 0x03
    #define INDEX_OF_SEQ_NUM_END   0x04

    sl_zigbee_app_debug_print("\nPing returned [");
    sl_zigbee_app_debug_print("%02X %02X", cmd->buffer[INDEX_OF_SEQ_NUM_START], cmd->buffer[INDEX_OF_SEQ_NUM_END]);
    sl_zigbee_app_debug_print("]\n");
    return true;
  }
  return false;
}
// raw 0x0042 { FA DE FE 00 01}
// send 0xffff 1 1
bool emberAfPreMessageSendCallback(EmberAfMessageStruct* messageStruct,
                                   EmberStatus* status)
{
  // Print debug message for latency timing.
  if (messageStruct->apsFrame->clusterId == 0x0042) {
    uint8_t *msg_contents = messageStruct->message;
    if (msg_contents[0] == 0xFA && msg_contents[1] == 0xDE ) {
      emDebugBinaryFormat(EM_DEBUG_LATENCY, "BBBB",
                          0x80, // frame control, top bit is start/stop
                          2, //2 byte sequence number
                          msg_contents[3],
                          msg_contents[4]);
      *status = EMBER_SUCCESS;
    }
  }
  return false;
}

void emberAfMainInitCallback(void)
{
  emNewBroadcastEntryThreshold = EMBER_BROADCAST_TABLE_SIZE;
}
#endif // #if (LARGE_NETWORK_TESTING == 1)

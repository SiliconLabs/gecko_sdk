/***************************************************************************//**
 * @file
 * @brief Routines for the Throughput plugin, which provides a mechanism for
 *        measuring network throughput.
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

#include <stdint.h>
#include "app/framework/include/af.h"
#include "app/framework/util/af-main.h"
#include "math.h"
#include "app/framework/plugin/counters/counters.h"
#ifdef UNIX_HOST
#include <time.h>
#endif // UNIX_HOST
#define MAX_PACKET_LENGTH 127
#define ZIGBEE_TX_TEST_MAX_INFLIGHT         5

typedef struct {
  bool inUse;
  uint32_t startTime;
  uint8_t seqn;
} InflightInfo;

static struct {
  EmberApsOption apsOptions;
  EmberNodeId destination;
  uint8_t payloadLength;
  uint8_t headerLength;
  uint8_t packetLength;
  uint16_t messageTotalCount;
  uint16_t messageRunningCount;
  uint16_t messageSuccessCount;
  uint8_t maxInFlight;
  uint8_t currentInFlight;
  uint16_t txIntervalMs;
  uint32_t startTime;
  uint32_t runTime;
  uint32_t testTimeout;
  uint32_t minSendTimeMs;
  uint32_t maxSendTimeMs;
  uint32_t sumSendTimeMs;
  uint32_t varSendTimeMs;
  InflightInfo inflightInfoTable[ZIGBEE_TX_TEST_MAX_INFLIGHT];
} testParams;

#include "sl_cli.h"
//stack events and handlers
static sl_zigbee_event_t packetSendEvent;
static void packetSendEventHandler(sl_zigbee_event_t * event);

//Other declarations
static uint8_t isRunning = 0;
extern uint16_t emberCounters[EMBER_COUNTER_TYPE_COUNT];
extern const char * titleStrings[];
static void getHeaderLen(void);
static void printParameter(uint8_t printSelection);
static void printCounter(uint8_t);
static void printAllParameters(void);
static void printResult(void);
static void startTest(void);
static void stopTest(void);
static void clearCounters(void);
enum printSelection {
  DESTINATION = 0,
  COUNT,
  INTERVAL,
  HEADER,
  PAYLOAD,
  PACKET,
  INFLIGHT,
  APSOPTIONS,
  TESTTIMEOUT
};

//---internal callback

void sli_zigbee_af_throughput_init_callback(uint8_t init_level)
{
  (void)init_level;

  sl_zigbee_event_init(&packetSendEvent,
                       packetSendEventHandler);
}

//-------------------------------------------------

static void printParameter(uint8_t printSelection)
{
  switch (printSelection) {
    case DESTINATION:
      emberAfCorePrintln("Destination nodeID: 0x%2x ", testParams.destination);
      break;
    case COUNT:
      emberAfCorePrintln("Packets to send: %d ", testParams.messageTotalCount);
      break;
    case INTERVAL:
      emberAfCorePrintln("Transmit interval: %d ms", testParams.txIntervalMs);
      break;
    case HEADER:
      emberAfCorePrintln("Header size: %dB", testParams.headerLength);
      break;
    case PAYLOAD:
      emberAfCorePrintln("Payload size: %dB", testParams.payloadLength);
      break;
    case PACKET:
      emberAfCorePrintln("Packet size: %dB", testParams.packetLength);
      break;
    case INFLIGHT:
      emberAfCorePrintln("Packets in flight: %d", testParams.maxInFlight);
      break;
    case APSOPTIONS:
      emberAfCorePrintln("APS Options = 0x%2x", testParams.apsOptions);
      break;
    case TESTTIMEOUT:
      emberAfCorePrintln("Timeout: %d ms", testParams.testTimeout);
      break;
    default:
      emberAfCorePrintln("Err");
  }
}

static void printAllParameters(void)
{
  emberAfCorePrintln(" ");
  emberAfCorePrintln("TEST PARAMETERS");
  printParameter(DESTINATION);
  printParameter(COUNT);
  printParameter(INTERVAL);
  printParameter(PAYLOAD);
  printParameter(PACKET);
  printParameter(INFLIGHT);
  printParameter(APSOPTIONS);
  printParameter(TESTTIMEOUT);
}

static void printResult(void)
{
  uint32_t mean, var, std;

  if (isRunning) {
    emberAfCorePrintln("Test still in progress");
    testParams.runTime = elapsedTimeInt32u(testParams.startTime, halCommonGetInt32uMillisecondTick());
  }
  uint64_t appThroughput = (testParams.messageSuccessCount
                            * testParams.payloadLength);
  appThroughput = appThroughput * 8 * 1000 / testParams.runTime;

  uint64_t phyThroughput = (testParams.messageSuccessCount
                            * testParams.packetLength);
  phyThroughput = phyThroughput * 8 * 1000 / testParams.runTime;

  emberAfCorePrintln(" ");
  emberAfCorePrintln("THROUGHPUT RESULTS");
  emberAfCorePrintln("Total time %u ms", testParams.runTime);
  emberAfCorePrintln("Success messages: %d out of %d",
                     testParams.messageSuccessCount,
                     testParams.messageTotalCount);
  emberAfCorePrintln("Payload Throughput: %u bits/s", appThroughput);
  emberAfCorePrintln("Phy Throughput: %u bits/s", phyThroughput);
  if (testParams.messageSuccessCount > 0) {
    mean = testParams.sumSendTimeMs / testParams.messageSuccessCount;
    //10X scaling factor makes large number less likely to overflow
    var = testParams.varSendTimeMs * 10 / testParams.messageSuccessCount;
    if (var > (mean * mean) ) {
      var -= (mean * mean);
      std = sqrt(fabs(var));
    } else {
      std = 0;
    }

    emberAfCorePrintln("Min packet send time: %u ms",
                       testParams.minSendTimeMs);
    emberAfCorePrintln("Max packet send time: %u ms",
                       testParams.maxSendTimeMs);
    emberAfCorePrintln("Avg packet send time: %u ms", mean);
    emberAfCorePrintln("STD packet send time: %u ms", std);
  }
}

static void startTest(void)
{
  uint8_t i;

  if (isRunning) {
    emberAfCorePrintln("Test already in progress");
    return;
  }

  if (testParams.packetLength <= 50) {
    emberAfCorePrintln("Err: Invalid Packet Size");
    printAllParameters();
    return;
  }

  if (testParams.messageTotalCount == 0) {
    emberAfCorePrintln("Err: Invalid Count");
    printAllParameters();
    return;
  }

  isRunning = 1;
  testParams.currentInFlight = 0;
  testParams.messageRunningCount = 0;
  testParams.messageSuccessCount = 0;
  testParams.startTime = halCommonGetInt32uMillisecondTick();
  testParams.runTime = 0;
  testParams.minSendTimeMs = 0xFFFFFFFF;
  testParams.maxSendTimeMs = 0;
  testParams.sumSendTimeMs = 0;
  testParams.varSendTimeMs = 0;
  for (i = 0; i < ZIGBEE_TX_TEST_MAX_INFLIGHT; i++) {
    testParams.inflightInfoTable[i].inUse = false;
  }
  clearCounters();
  emberAfCorePrintln("Starting Test");
  packetSendEventHandler(&packetSendEvent);
}

static void stopTest(void)
{
  sl_zigbee_event_set_inactive(&packetSendEvent);
  testParams.messageTotalCount = 0;
  isRunning = 0;
  emberAfCorePrintln("Test Aborted");
}

static void clearCounters(void)
{
  emberAfCorePrintln("Clearing counters");
  emberAfPluginCountersClear();
}

static bool messageSentHandler(EmberOutgoingMessageType type,
                               uint16_t indexOrDestination,
                               EmberApsFrame* apsFrame,
                               uint16_t msgLen,
                               uint8_t* message,
                               EmberStatus status)
{
  (void)type;
  (void)indexOrDestination;
  (void)msgLen;
  (void)message;

  // Is this is a message sent out as part of the throughput test?
  if (apsFrame->profileId == 0x7F01 && apsFrame->clusterId == 0x0001) {
    uint32_t packetSendTimeMs = 0xFFFFFFFF;
    uint8_t i;

    testParams.currentInFlight--;

    for (i = 0; i < ZIGBEE_TX_TEST_MAX_INFLIGHT; i++) {
      if (testParams.inflightInfoTable[i].seqn == apsFrame->sequence) {
        testParams.inflightInfoTable[i].inUse = false;
        packetSendTimeMs = elapsedTimeInt32u(testParams.inflightInfoTable[i].startTime, halCommonGetInt32uMillisecondTick());
        break;
      }
    }

    #ifdef EMBER_TEST
    assert(packetSendTimeMs != 0xFFFFFFFF);
    #endif

    if ((status == EMBER_SUCCESS) && (packetSendTimeMs != 0xFFFFFFFF)) {
      testParams.messageSuccessCount++;
      testParams.sumSendTimeMs += packetSendTimeMs;

      if (testParams.minSendTimeMs > packetSendTimeMs) {
        testParams.minSendTimeMs = packetSendTimeMs;
      }
      if (testParams.maxSendTimeMs < packetSendTimeMs) {
        testParams.maxSendTimeMs = packetSendTimeMs;
      }

      //10X scaling factor makes large number less likely to overflow
      testParams.varSendTimeMs += packetSendTimeMs * packetSendTimeMs / 10;
    }

    if (testParams.currentInFlight == 0
        && testParams.messageRunningCount
        == testParams.messageTotalCount) {
      emberAfCorePrintln("Test Complete");
      testParams.runTime = elapsedTimeInt32u(testParams.startTime, halCommonGetInt32uMillisecondTick());
      printResult();
    }
    return true;
  }
  return false;
}

#ifdef EZSP_HOST
void sli_zigbee_af_throughput_message_sent_callback(EmberOutgoingMessageType type,
                                                    uint16_t indexOrDestination,
                                                    EmberApsFrame *apsFrame,
                                                    uint8_t messageTag,
                                                    EmberStatus status,
                                                    uint8_t messageLength,
                                                    uint8_t *messageContents)
{
  messageSentHandler(type,
                     indexOrDestination,
                     apsFrame,
                     messageLength,
                     messageContents,
                     status);
}
#else // SoC
void sli_zigbee_af_throughput_message_sent_callback(EmberIncomingMessageType type,
                                                    uint16_t indexOrDestination,
                                                    EmberApsFrame *apsFrame,
                                                    EmberMessageBuffer messageBuf,
                                                    EmberStatus status)
{
  messageSentHandler(type,
                     indexOrDestination,
                     apsFrame,
                     sli_legacy_buffer_manager_get_buffer_length(messageBuf),
                     sli_legacy_buffer_manager_get_buffer_pointer(messageBuf),
                     status);
}
#endif // EZSP_HOST

static void getHeaderLen(void)
{
  EmberApsFrame* testFrame;
  testFrame = emberAfGetCommandApsFrame();
  uint8_t maxPayloadLen = emberAfMaximumApsPayloadLength(
    EMBER_OUTGOING_DIRECT,
    testParams.destination,
    testFrame);
  testParams.headerLength = MAX_PACKET_LENGTH - maxPayloadLen;
}

static void printCounter(uint8_t id)
{
  emberAfCorePrintln("%p: %u ", titleStrings[id], emberCounters[id]);
}
static void packetSendEventHandler(sl_zigbee_event_t * event)
{
  EmberApsFrame apsFrame;
  uint8_t messagePayload[EMBER_AF_MAXIMUM_APS_PAYLOAD_LENGTH];
  uint16_t messageTag[1] = { 0 };
  uint8_t i;
  uint32_t txIntervalAdjustmentMs;
  uint32_t adjustedTxIntervalMs;

  uint32_t currentTimeMs = halCommonGetInt32uMillisecondTick();
  uint32_t totalRunTimeMs = elapsedTimeInt32u(testParams.startTime, currentTimeMs);
  if ((totalRunTimeMs >= testParams.testTimeout)
      && (testParams.testTimeout > 0)) {
    emberAfCorePrintln("Timeout Exceeded");
    stopTest();
    return;
  }
  messagePayload[0] = testParams.payloadLength;
  messagePayload[1] = LOW_BYTE(testParams.messageRunningCount);
  messagePayload[2] = HIGH_BYTE(testParams.messageRunningCount);
  for (i = 3; i < testParams.payloadLength; i++) {
    messagePayload[i] = i - 3;
  }
  if (testParams.maxInFlight > 0
      && testParams.currentInFlight >= testParams.maxInFlight) {
    sl_zigbee_event_set_delay_ms(&packetSendEvent, 1);
    return;
  }
  apsFrame.sourceEndpoint = 0xFF;
  apsFrame.destinationEndpoint = 0xFF;
  apsFrame.options = testParams.apsOptions;
  apsFrame.profileId = 0x7F01; // test profile ID
  apsFrame.clusterId = 0x0001; // counted packets cluster

  if (sli_zigbee_af_send(EMBER_OUTGOING_DIRECT,
                         testParams.destination,
                         &apsFrame,
                         testParams.payloadLength,
                         messagePayload,
                         messageTag,
                         0xFFFF,
                         0) == EMBER_SUCCESS) {
    testParams.messageRunningCount++;
    testParams.currentInFlight++;

    for (i = 0; i < ZIGBEE_TX_TEST_MAX_INFLIGHT; i++) {
      if (!testParams.inflightInfoTable[i].inUse) {
        testParams.inflightInfoTable[i].inUse = true;
        testParams.inflightInfoTable[i].seqn = apsFrame.sequence;
        testParams.inflightInfoTable[i].startTime =
          halCommonGetInt32uMillisecondTick();
        break;
      }
    }
    assert(i < ZIGBEE_TX_TEST_MAX_INFLIGHT);
  }

  if (testParams.messageRunningCount
      >= testParams.messageTotalCount) {
    sl_zigbee_event_set_inactive(&packetSendEvent);
    isRunning = 0;
  } else {
    // txIntervalAdjustment subtracts out time spent in this function from the send loop timer,
    // which makes a significant difference for host applications using ncp-uart
    txIntervalAdjustmentMs = elapsedTimeInt32u(currentTimeMs, halCommonGetInt32uMillisecondTick());
    if (txIntervalAdjustmentMs >= testParams.txIntervalMs) {
      adjustedTxIntervalMs = 0;
    } else {
      adjustedTxIntervalMs = testParams.txIntervalMs - txIntervalAdjustmentMs;
    }
    sl_zigbee_event_set_delay_ms(&packetSendEvent,
                                 adjustedTxIntervalMs);
  }
}

void sli_zigbee_af_throughput_cli_print_parameters(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  printAllParameters();
}

void sli_zigbee_af_throughput_cli_set_all_parameters(sl_cli_command_arg_t *arguments)
{
  static uint8_t minPacketLen;

  testParams.destination = sl_cli_get_argument_uint16(arguments, 0);
  testParams.messageTotalCount = sl_cli_get_argument_uint16(arguments, 1);
  testParams.txIntervalMs = sl_cli_get_argument_uint16(arguments, 2);
  testParams.packetLength = sl_cli_get_argument_uint8(arguments, 3);
  testParams.maxInFlight = sl_cli_get_argument_uint8(arguments, 4);
  testParams.apsOptions = sl_cli_get_argument_uint16(arguments, 5);
  testParams.testTimeout = sl_cli_get_argument_uint32(arguments, 6);

  // Check packet length parameter
  getHeaderLen();
  minPacketLen = testParams.headerLength + 4;
  if (testParams.packetLength < minPacketLen) {
    testParams.packetLength = minPacketLen;
  } else if (testParams.packetLength > MAX_PACKET_LENGTH) {
    testParams.packetLength = MAX_PACKET_LENGTH;
  }
  testParams.payloadLength = testParams.packetLength - testParams.headerLength;

  // Check in-flight parameter
  if (testParams.maxInFlight > ZIGBEE_TX_TEST_MAX_INFLIGHT) {
    testParams.maxInFlight = ZIGBEE_TX_TEST_MAX_INFLIGHT;
  } else if (testParams.maxInFlight <= 0) {
    testParams.maxInFlight = 1;
  }
  printAllParameters();
}

void sli_zigbee_af_throughput_cli_set_destination(sl_cli_command_arg_t *arguments)
{
  testParams.destination = sl_cli_get_argument_uint16(arguments, 0);
  getHeaderLen();
  testParams.packetLength = testParams.payloadLength + testParams.headerLength;
  if (testParams.packetLength > MAX_PACKET_LENGTH) {
    testParams.payloadLength = MAX_PACKET_LENGTH - testParams.headerLength;
  }
  printParameter(DESTINATION);
  printParameter(PACKET);
}

void sli_zigbee_af_throughput_cli_set_test_count(sl_cli_command_arg_t *arguments)
{
  testParams.messageTotalCount = sl_cli_get_argument_uint16(arguments, 0);
  printParameter(COUNT);
}

void sli_zigbee_af_throughput_cli_set_interval(sl_cli_command_arg_t *arguments)
{
  testParams.txIntervalMs = sl_cli_get_argument_uint16(arguments, 0);
  printParameter(INTERVAL);
}

void sli_zigbee_af_throughput_cli_set_packet_size(sl_cli_command_arg_t *arguments)
{
  static uint8_t minPacketLen;

  testParams.packetLength = sl_cli_get_argument_uint8(arguments, 0);
  getHeaderLen();
  minPacketLen = testParams.headerLength + 4;

  if (testParams.packetLength < minPacketLen) {
    testParams.packetLength = minPacketLen;
  } else if (testParams.packetLength > MAX_PACKET_LENGTH) {
    testParams.packetLength = MAX_PACKET_LENGTH;
  }
  testParams.payloadLength = testParams.packetLength - testParams.headerLength;

  emberAfCorePrintln("Max packet: 127");
  printParameter(HEADER);
  printParameter(PAYLOAD);
  printParameter(PACKET);
}

void sli_zigbee_af_throughput_cli_set_in_flight_count(sl_cli_command_arg_t *arguments)
{
  testParams.maxInFlight = sl_cli_get_argument_uint8(arguments, 0);
  if (testParams.maxInFlight > ZIGBEE_TX_TEST_MAX_INFLIGHT) {
    testParams.maxInFlight = ZIGBEE_TX_TEST_MAX_INFLIGHT;
  } else if (testParams.maxInFlight <= 0) {
    testParams.maxInFlight = 1;
  }
  printParameter(INFLIGHT);
}

void sli_zigbee_af_throughput_cli_set_aps_ack_on(sl_cli_command_arg_t *arguments)
{
  testParams.apsOptions |= EMBER_APS_OPTION_RETRY;
  printParameter(APSOPTIONS);
}

void sli_zigbee_af_throughput_cli_set_aps_ack_off(sl_cli_command_arg_t *arguments)
{
  testParams.apsOptions &= ~EMBER_APS_OPTION_RETRY;
  printParameter(APSOPTIONS);
}

void sli_zigbee_af_throughput_cli_set_test_timeout(sl_cli_command_arg_t *arguments)
{
  testParams.testTimeout = sl_cli_get_argument_uint32(arguments, 0);
  printParameter(TESTTIMEOUT);
}

void sli_zigbee_af_throughput_cli_clear_counters(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  clearCounters();
}

void sli_zigbee_af_throughput_cli_stop_test(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  stopTest();
}

void sli_zigbee_af_throughput_cli_start_test(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  startTest();
}

void sli_zigbee_af_throughput_cli_print_result(sl_cli_command_arg_t *arguments)
{
  (void) arguments;

  printResult();
}

void sli_zigbee_af_throughput_cli_print_counters(sl_cli_command_arg_t *arguments)
{
  #ifdef EZSP_HOST
  ezspReadCounters(emberCounters);
  #endif // EZSP_HOST
  emberAfCorePrintln(" ");
  emberAfCorePrintln("COUNTERS");
  printCounter(EMBER_COUNTER_PHY_CCA_FAIL_COUNT);
  printCounter(EMBER_COUNTER_MAC_TX_UNICAST_SUCCESS);
  printCounter(EMBER_COUNTER_MAC_TX_UNICAST_RETRY);
  printCounter(EMBER_COUNTER_MAC_TX_UNICAST_FAILED);
  printCounter(EMBER_COUNTER_APS_DATA_TX_UNICAST_SUCCESS);
  printCounter(EMBER_COUNTER_APS_DATA_TX_UNICAST_RETRY);
  printCounter(EMBER_COUNTER_APS_DATA_TX_UNICAST_FAILED);
}

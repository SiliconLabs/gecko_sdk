/***************************************************************************//**
 * @brief Implements a lower MAC layer that runs on top of RAIL and the 802.15.4
 * provided features (autoacking, filtering, etc).
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

#include PLATFORM_HEADER

#ifdef UNIFIED_MAC_SCRIPTED_TEST
#define EMBER_STACK_CONNECT
#endif
#include "core/ember-stack.h"
#include "hal/hal.h"
#include "mac-command.h"
#include "lower-mac.h"
#include "upper-mac.h"
#include "mac-child.h"
#include "scan.h"
#include "mac-phy.h"

#if defined(EMBER_STACK_CONNECT) || defined(UNIFIED_MAC_SCRIPTED_TEST)
#include "network/association.h"
#include "network/child-table.h"
#include "framework/packet-header.h"
#include "framework/counters.h"
#define SLI_COEX_SUPPORTED 0
#define SLI_ANTDIV_SUPPORTED 0
#else
#include "mac/mac.h"
#include "mac-header.h"
#include "stack/routing/zigbee/child.h"
#include "core/ember-multi-network.h"

#ifndef SLI_COEX_SUPPORTED
#define SLI_COEX_SUPPORTED 1
#endif // SLI_COEX_SUPPORTED

#ifndef SLI_ANTDIV_SUPPORTED
#define SLI_ANTDIV_SUPPORTED 1
#endif // SLI_ANTDIV_SUPPORTED

#endif // EMBER_STACK_CONNECT || UNIFIED_MAC_SCRIPTED_TEST

#define SLI_DMP_TUNING_SUPPORTED SLI_COEX_SUPPORTED // DMP_TUNING requires COEX

#include "rail.h"
#include "rail_ieee802154.h"
#include "rail_util_ieee802154/sl_rail_util_ieee802154_phy_select.h"

#include "em_common.h" // for SL_WEAK

//This isn't really a limit at all, but it has been the default from the
//beginning.  ECC code lowers it
uint16_t emMaxPhyToMacQueueLength = 1000;

uint8_t emMfglibMode = 0u;
int8_t emSynthFreqOffset; //mfglib

// Some of the default CSMA default values.

// Comes from phy/phy.h (in lower-mac.h)
// but it is not included in connect
#ifdef EMBER_STACK_CONNECT
#define RADIO_CCA_ATTEMPT_MAX_DEFAULT                5
#endif

#define RADIO_BACKOFF_EXPONENT_MIN_DEFAULT           3
#define RADIO_BACKOFF_EXPONENT_MAX_DEFAULT           5

#define RADIO_IDLE_TIME_US                           100

#define LOWER_MAC_ACK_RX_NONE                        0xFF
#define LOWER_MAC_ACK_RX_FRAME_PENDING_NOT_SET       0x00
#define LOWER_MAC_ACK_RX_FRAME_PENDING_SET           0x01
#define LOWER_MAC_ACK_RX_TIMEOUT                     0x02

// Internal flags
//If updating these, also update "internalFlagsPrintTags" in lower-mac-debug.h
#define FLAG_RADIO_INIT_DONE                         0x0001
#define FLAG_ONGOING_TX_DATA                         0x0002
#define FLAG_ONGOING_TX_ACK                          0x0004
#define FLAG_WAITING_FOR_ACK                         0x0008
#define FLAG_SYMBOL_TIMER_RUNNING                    0x0010
#define FLAG_CURRENT_TX_USE_CSMA                     0x0020
#define FLAG_DATA_POLL_FRAME_PENDING_SET             0x0040
#define FLAG_CALIBRATION_NEEDED                      0x0080
#define FLAG_IDLE_PENDING                            0x0100
#define FLAG_CURRENT_TX_USE_WAKE_UP_FRAMES           0x0200

#define TX_COMPLETE_RESULT_SUCCESS                   0x00
#define TX_COMPLETE_RESULT_CCA_FAIL                  0x01
#define TX_COMPLETE_RESULT_OTHER_FAIL                0x02
#define TX_COMPLETE_RESULT_NONE                      0xFF

#ifdef CSL_SUPPORT
// PHY LEN (1) + FC (2) + SEQ (1) + DEST_PAN (2) + DEST (2) + SRC (2) + HEADER IE (2) + RENDEZVOUS TIME IE (4) + CRC (2)
#define WAKEUP_FRAME_SIZE_BYTES_WITH_CRC            18
#define WAKEUP_FRAME_SIZE_BYTES_NO_CRC              (WAKEUP_FRAME_SIZE_BYTES_WITH_CRC - EMBER_PHY_CRC_LENGTH)
#define RADIO_PREAMBLE_PLUS_SYNC_WORD_BYTES         5 // preamble (4) + sync (1)
#define USEC_PER_SYMBOL_2_4_GHZ                     16
#define SYMBOL_PER_BYTE_2_4_GHZ                     2
#define USEC_PER_BYTE_2_4_GHZ                       (USEC_PER_SYMBOL_2_4_GHZ * SYMBOL_PER_BYTE_2_4_GHZ)
#define TIME_BETWEEN_WAKEUP_FRAMES_IN_USEC          100  // macCslInterval
#define TIME_BETWEEN_WAKEUP_FRAMES_IN_SYMBOLS       (TIME_BETWEEN_WAKEUP_FRAMES_IN_USEC / USEC_PER_SYMBOL_2_4_GHZ)
#define WAKEUP_FRAME_TX_TIME_IN_SYMBOLS             ((WAKEUP_FRAME_SIZE_BYTES_WITH_CRC + RADIO_PREAMBLE_PLUS_SYNC_WORD_BYTES) * SYMBOL_PER_BYTE_2_4_GHZ)
#define WAKEUP_FRAME_TX_TIME_IN_US                  ((WAKEUP_FRAME_SIZE_BYTES_WITH_CRC + RADIO_PREAMBLE_PLUS_SYNC_WORD_BYTES) * USEC_PER_BYTE_2_4_GHZ)

// TODO: EMZIGBEE-8554: Change the Tx Default Priority to use a macro to set the priority based on the
// BLE Advertisement priorities
//
// EMZIGBEE-8549
// Set the Tx priority to 25 which is in between the default calculated BLE advertisement priority range of 23-26
// This is needed to allow Zigbee to transmit reliably and not get pre-empted by BLE advertisement priorities.
#undef RADIO_SCHEDULER_TX_DEFAULT_PRIORITY
#define RADIO_SCHEDULER_TX_DEFAULT_PRIORITY       25
#endif // CSL_SUPPORT

#define ONGOING_TX_FLAGS   (FLAG_ONGOING_TX_DATA | FLAG_ONGOING_TX_ACK)

#define ED_CCA_THRESHOLD  -75 // dBm  - default for 2.4GHz 802.15.4
#define rx_frame_detect_disable()                                     \
  (void) RAIL_ConfigRxOptions(connectRailHandle,                      \
                              RAIL_RX_OPTION_DISABLE_FRAME_DETECTION, \
                              RAIL_RX_OPTION_DISABLE_FRAME_DETECTION)
#define rx_frame_detect_enable()                                      \
  (void) RAIL_ConfigRxOptions(connectRailHandle,                      \
                              RAIL_RX_OPTION_DISABLE_FRAME_DETECTION, \
                              RAIL_RX_OPTIONS_NONE)

#if     SLI_COEX_SUPPORTED

#include "coexistence/protocol/ieee802154_uc/coexistence-802154.h"
#include "rail_util_ant_div/sl_rail_util_ant_div.h"

#if     SLI_DMP_TUNING_SUPPORTED
static EmberMultiprotocolPriorities radioSchedulerPriorityTable = {
  RADIO_SCHEDULER_BACKGROUND_RX_DEFAULT_PRIORITY,
  RADIO_SCHEDULER_TX_DEFAULT_PRIORITY,
  RADIO_SCHEDULER_ACTIVE_RX_DEFAULT_PRIORITY,
};

SL_WEAK void emRadioConfigScheduledCallback(bool scheduled)
{
  // no-op
}
#endif//SLI_DMP_TUNING_SUPPORTED

RAIL_Handle_t emPhyRailHandle; // Exposed for Coex/PTA/RHO
#define connectRailHandle emPhyRailHandle

#ifdef  EMBER_TEST
static sl_rail_util_ieee802154_stack_status_t onPtaStackEvent(sl_rail_util_ieee802154_stack_event_t ptaStackEvent,
                                                              uint32_t supplement)
{
  //sToDo: still no support for this in unified-mac upper-mac
  /*
     sl_rail_util_coex_cb_t cb = (sl_rail_util_coex_cb_t) supplement;
     if (ptaStackEvent == SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_PENDED_MAC) {
     extern EmMacTxMode emMacTestTxMode; // In upper-mac.c
     if (emMacTestTxMode == MAC_TX_MODE_MAC_HO) {
      return SL_RAIL_UTIL_IEEE802154_STACK_STATUS_HOLDOFF;
     } else if (emMacTestTxMode == MAC_TX_MODE_GRANT) {
      // Assert Tx REQUEST  and wait for GRANT
      sl_rail_util_coex_set_tx_request(SL_RAIL_UTIL_COEX_REQ_ON | SL_RAIL_UTIL_COEX_TX_PRI | SL_RAIL_UTIL_COEX_REQCB_GRANTED, cb);
      return SL_RAIL_UTIL_IEEE802154_STACK_STATUS_CB_PENDING;
     } else { // MAC_TX_MODE_NORMAL
      // Proceed with a normal transmit
     }
     } else {
     // In test/simulation all other events are ignored
     }
   */
  return SL_RAIL_UTIL_IEEE802154_STACK_STATUS_SUCCESS; // No callback
}
#else//!EMBER_TEST
static sl_rail_util_ieee802154_stack_status_t onPtaStackEvent(sl_rail_util_ieee802154_stack_event_t ptaStackEvent,
                                                              uint32_t supplement)
{
  sl_rail_util_ieee802154_stack_status_t status = sl_rail_util_ieee802154_on_event(ptaStackEvent, supplement);
#if     SLI_DMP_TUNING_SUPPORTED
  if (radioSchedulerPriorityTable.backgroundRx
      != radioSchedulerPriorityTable.activeRx) {
    switch (ptaStackEvent) {
      case SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_STARTED:
        // Escalate priority for the duration of this Rx (and any ACK)
        RAIL_SetTaskPriority(connectRailHandle,
                             radioSchedulerPriorityTable.activeRx,
                             RAIL_TASK_TYPE_START_RX);
        break;
      case SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_FILTERED:
      case SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_CORRUPTED:
      case SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_BLOCKED:
      case SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_ABORTED:
      case SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_SENT:
      case SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ENDED:
        // Deescalate priority now that Rx (and any ACK) has finished
        RAIL_SetTaskPriority(connectRailHandle,
                             radioSchedulerPriorityTable.backgroundRx,
                             RAIL_TASK_TYPE_START_RX);
        break;
      default:
        break;
    }
  }
#endif//SLI_DMP_TUNING_SUPPORTED
  return status;
}
#endif//EMBER_TEST

// Try to transmit the current outgoing frame subject to MAC-level PTA
static void tryTxCurrentPacket(void);
// True if actively receiving a frame
static bool isReceivingFrame(void);

// rhoActive covers both external and internal RHO users distinctly, so not bool
enum {
  RHO_INACTIVE = 0,
  RHO_EXT_ACTIVE,
  RHO_INT_ACTIVE, //TODO: Not currently used in this lower-mac
  RHO_BOTH_ACTIVE,
};
static uint8_t rhoActive = RHO_INACTIVE;

extern void emRadioEnablePta(bool enable);
#else//!SLI_COEX_SUPPORTED

#define onPtaStackEvent(event, supplement) 0
#define tryTxCurrentPacket txCurrentPacket

static RAIL_Handle_t connectRailHandle;

#endif//SLI_COEX_SUPPORTED

// Variables for the CSL feature
#ifdef CSL_SUPPORT
static uint16_t macCslMaxPeriodMs = 125;    // length of all wakeup frames; 0 means don't use wake up frames
static uint16_t macCslPeriodMs = 120;       // period between rx windows; 0 means CSL is off
static uint16_t macCslChannelSampleMs = 5;  // duration of an rx window
static uint16_t cslPacketsSent;
static bool payloadFrameLoadedInTxFifo;
static bool wakeupFrameReceived = false;
static bool dutyCyclingEnabled = false;

// We continuously fill this FIFO with wakeup frames and even the final payload
// frame
static uint8_t wakeupFrame[WAKEUP_FRAME_SIZE_BYTES_NO_CRC];
static uint8_t cslFrameFifo[EMBER_PHY_MAX_PACKET_LENGTH * 4]; // 512
static uint16_t totalWakeupFramesToSend;
static uint16_t numWakeupFrameBeingSent;

static void addPayloadFrameInFifo(void);
static void addNextWakeupFrameInFifo(void);
static void fillTxFifoWithWakeupFrames(void);
static sl_status_t configureDutyCycling(bool enable);
static void updateDutyCyclingConfig(void);
static bool isWakeupFrame(uint8_t *macFrame, uint8_t *ieData);
static void radioScheduleRx(RAIL_Time_t startTime,
                            RAIL_TimeMode_t startMode,
                            uint8_t priority,
                            RAIL_Time_t endTime);
#endif // CSL_SUPPORT

// -----------------------------------------------------------------------------
// Variables
#ifndef EVENT_CONTROL_SYSTEM
void emLowerMacEventHandler(EmberEvent *event);

EmberEvent emLowerMacEvent = { {
                                 &emStackEventQueue,
                                 emLowerMacEventHandler,
                                 NULL,
                                 #ifndef EMBER_TEST
                                 ""
                                 #else
                                 "lower MAC"
                                 #endif
                               },
                               NULL };
#ifdef CSL_SUPPORT
void emLowerMacCslEventHandler(EmberEvent *event);

EmberEvent emLowerMacCslEvent = { {
                                    &emStackEventQueue,
                                    emLowerMacCslEventHandler,
                                    NULL,
                                 #ifndef EMBER_TEST
                                    ""
                                 #else
                                    "lower MAC CSL"
                                 #endif
                                  },
                                  NULL };
#endif
#else
EmberEventControl emLowerMacEvent;
#endif

uint8_t emLowerMacState;

uint8_t emMacMaxRetries = DEFAULT_MAC_MAX_RETRIES;

// this is a global state, similar to mac retries
static uint8_t current_force_tx_after_failed_cca_attempts = 0;
static uint8_t default_force_tx_after_failed_cca_attempts = 0;

static volatile uint16_t miscInternalFlags = 0;

static RAIL_CsmaConfig_t csmaParams;

static uint8_t currentChannel = 11;
static uint8_t currentRadioChannel = 0xFF;

static uint8_t *currentOutgoingPacket = NULL;

#ifdef EMBER_STACK_CONNECT
static Buffer currentIncomingFrame = NULL_BUFFER;
#else
static PacketHeader currentIncomingFrame;
#endif

static uint8_t macRetries = 0;

static volatile uint8_t txCompleteStatusPending = TX_COMPLETE_RESULT_NONE;
static volatile uint8_t ackReceivedPending = LOWER_MAC_ACK_RX_NONE;
#ifdef EMBER_STACK_CONNECT
static int8_t ackReceivedRssi;
#endif

// This implements a work-around for RAIL_LIB-2726.
static volatile RAIL_Time_t lastRxWithAckTime;

static void railCallbackHandler(RAIL_Handle_t railHandle, RAIL_Events_t events);

static RAILSched_Config_t railSchedState;

static RAIL_Config_t railCfg = {
  .eventsCallback = railCallbackHandler,
  .scheduler = &railSchedState,
};

#ifndef EMBER_STACK_CONNECT
static uint8_t emMacOutgoingSequenceNumber = 0;
#define STACK_WAKEUP_ISR_HANDLER  emberRtosStackWakeupIsrHandler()
#else
#define STACK_WAKEUP_ISR_HANDLER  emberStackIsrHandler()
#endif

// -----------------------------------------------------------------------------
// Static forward declarations.

#if defined(EMBER_TEST) || defined(EMBER_STACK_CONNECT)
static void railConfigChangedCallback(RAIL_Handle_t railHandle,
                                      const RAIL_ChannelConfigEntry_t *entry);
#endif

#ifndef EMBER_STACK_CONNECT
static uint8_t convertRssiToLqi(uint8_t lqi, int8_t rssiDbm); // Fwd decl
#endif//EMBER_STACK_CONNECT

// Transition to IDLE state.
static void radioSetIdle(void);

// Transition to RX state.
static void radioSetRx(void);

// Load the passed TX buffer and transition to TX state.
static void radioSetTx(uint8_t *dataPtr,
                       uint8_t dataLength,
                       uint16_t transactionTimeUs);

// Idle the radio (set it to either IDLE or RX based on the current IDLE mode).
static void radioIdle(void);

// Transmit the current outgoing frame.
static void txCurrentPacket(void);
// Perform operations upon completing transmission of current outgoing frame.
static void txCompleted(sl_status_t status);

// Called before the PHY actually powers up the radio for Rx or Tx and after
// the PHY has powered it down.
#ifndef EMBER_TEST
static void radioPowerFem(bool powerUp);
#endif

// Set or clear the passed flag.
static void setInternalFlag(uint16_t flag, bool val);
// Returns true if the passed flag is set, false otherwise.
static bool getInternalFlag(uint16_t flag);
// Returns true if at least one of the passed flags is set, false otherwise.
#define getInternalFlags(flags) getInternalFlag(flags)

// Returns true if the current outgoing packet is a data poll, false otherwise.
static bool currentOutgoingPacketIsDataRequest(void);

static void RAILCb_TimerExpired(void* params);

static void initDoneCallback(RAIL_Handle_t railHandle);
extern const RAIL_ChannelConfig_t *channelConfigs[];

static int8_t getEdCcaThreshold(void);

//copied from phy/phy.h for use by mfglib, but stack doesn't include phy/phy.h
void emRadioEnableAutoAck(bool enable);
void emRadioEnableAddressMatching(uint8_t enable);
uint8_t emRadioAddressMatchingEnabled(void);

// -----------------------------------------------------------------------------
// Debug stuff

//#define LOWER_MAC_DEBUG

#include "lower-mac-debug.h"

// -----------------------------------------------------------------------------
// Internal APIs and handlers.

extern const RAIL_ChannelConfig_t *channelConfigs[];
extern const RAIL_TxPowerConfig_t* halInternalPa2p4GHzInit;
extern const RAIL_TxPowerConfig_t* halInternalPaSubGHzInit;

#if     SLI_COEX_SUPPORTED

static RAIL_Events_t currentEventConfig = RAIL_EVENTS_NONE;

static void updateEvents(RAIL_Events_t mask, RAIL_Events_t values)
{
  RAIL_Events_t newEventConfig = (currentEventConfig & ~mask) | (values & mask);
  if (newEventConfig != currentEventConfig) {
    currentEventConfig = newEventConfig;
    LOWER_MAC_ASSERT(RAIL_ConfigEvents(connectRailHandle, mask, values)
                     == RAIL_STATUS_NO_ERROR);
  }
}

#else//!SLI_COEX_SUPPORTED

static inline void updateEvents(RAIL_Events_t mask, RAIL_Events_t values)
{
  LOWER_MAC_ASSERT(RAIL_ConfigEvents(connectRailHandle, mask, values)
                   == RAIL_STATUS_NO_ERROR);
}

#endif//SLI_COEX_SUPPORTED

SL_WEAK RAIL_Status_t sl_rail_util_plugin_config_2p4ghz_radio(RAIL_Handle_t railHandle)
{
  return RAIL_IEEE802154_Config2p4GHzRadio(railHandle);
}

void sl_mac_lower_mac_init(uint8_t mac_index, RadioPowerMode mode)
{
  UNUSED_VAR(mac_index);
  RAIL_IEEE802154_Config_t rail154Config = {
    .addresses = NULL,
    .ackConfig = {
      .enable = true,
      .ackTimeout = 0, // configured in the init API
      .rxTransitions = {
        .success = RAIL_RF_STATE_RX,
        .error = RAIL_RF_STATE_RX,
      },
      .txTransitions = {
        .success = RAIL_RF_STATE_RX,
        .error = RAIL_RF_STATE_RX,
      },
    },
    .timings = {
      .idleToRx = RADIO_IDLE_TIME_US,
      .idleToTx = RADIO_IDLE_TIME_US,
      // turnaround time: sl_mac_get_symbol_duration_us() can only be called
      // after we pushed the radio config.
      .txToRx = 0,
      .rxToTx = 0,
      .rxSearchTimeout = 0, // not used
      .txToRxSearchTimeout = 0, // not used
    },
    .framesMask = RAIL_IEEE802154_ACCEPT_STANDARD_FRAMES,
    .promiscuousMode = false,
    .isPanCoordinator = false,
  };

  uint8_t randomSeedBuffer[4];

  LOWER_MAC_DEBUG_INIT();

  // Don't re-initialize RAIL if we already did.
  if (getInternalFlag(FLAG_RADIO_INIT_DONE)) {
    return;
  }

  setInternalFlag(FLAG_RADIO_INIT_DONE, true);

  emLowerMacState = EMBER_MAC_STATE_RADIO_INIT;

  // TODO: ack timeout: this is way too long (accounts for slow PHY configs), we
  // should come up with a formula that depends on the symbol time.
#ifdef EMBER_STACK_CONNECT
  rail154Config.ackConfig.ackTimeout = emberMacAckTimeoutMS * 1000;
#else
  rail154Config.ackConfig.ackTimeout = 672; // 54-12 symbols * 16us/sym = 672
#endif

  connectRailHandle = RAIL_Init(&railCfg, initDoneCallback);
  LOWER_MAC_ASSERT(connectRailHandle != NULL);

#ifdef  EMBER_STACK_CONNECT
  RAIL_PtiProtocol_t ptiProtocol = RAIL_PTI_PROTOCOL_CONNECT;
#else//!EMBER_STACK_CONNECT
  RAIL_PtiProtocol_t ptiProtocol = RAIL_PTI_PROTOCOL_ZIGBEE;
#endif//EMBER_STACK_CONNECT
  LOWER_MAC_ASSERT(RAIL_SetPtiProtocol(connectRailHandle, ptiProtocol)
                   == RAIL_STATUS_NO_ERROR);

  // This API returns first available channel in config.
  #if defined(EMBER_TEST) || defined(EMBER_STACK_CONNECT)
  RAIL_ConfigChannels(connectRailHandle,
                      channelConfigs[0],
                      railConfigChangedCallback);
  #endif
#ifndef EMBER_STACK_CONNECT
  sl_rail_util_plugin_config_2p4ghz_radio(connectRailHandle);
  // we are not using connect or subgig, for connect this is called in railConfigChangedCallback
  RAIL_ConfigTxPower(connectRailHandle, halInternalPa2p4GHzInit);
#endif

  // Actually set the turnaround time params.
  rail154Config.timings.rxToTx =
    EMBER_MAC_ACK_TURNAROUND_DELAY_SYMBOLS * sl_mac_get_symbol_duration_us();
  rail154Config.timings.txToRx =
    EMBER_MAC_ACK_TURNAROUND_DELAY_SYMBOLS * sl_mac_get_symbol_duration_us();

  LOWER_MAC_ASSERT(RAIL_IEEE802154_Init(connectRailHandle, &rail154Config)
                   == RAIL_STATUS_NO_ERROR);
  LOWER_MAC_ASSERT(RAIL_IEEE802154_SetLongAddress(connectRailHandle,
                                                  emberGetEui64(),
                                                  0) // 0-index
                   == RAIL_STATUS_NO_ERROR);

  // Initialize the CSMA params to its default values.
  csmaParams.csmaMinBoExp = RADIO_BACKOFF_EXPONENT_MIN_DEFAULT;
  csmaParams.csmaMaxBoExp = RADIO_BACKOFF_EXPONENT_MAX_DEFAULT;
  csmaParams.csmaTries = RADIO_CCA_ATTEMPT_MAX_DEFAULT;

  csmaParams.ccaThreshold = getEdCcaThreshold();
  csmaParams.ccaBackoff =
    EMBER_MAC_UNIT_BACKOFF_PERIOD_SYMBOLS * sl_mac_get_symbol_duration_us();
  csmaParams.ccaDuration = 8 * sl_mac_get_symbol_duration_us();
  csmaParams.csmaTimeout = 0;

  updateEvents(RAIL_EVENTS_ALL,
               (0
                | RAIL_EVENT_CAL_NEEDED
                | RAIL_EVENT_RX_PACKET_RECEIVED
                | RAIL_EVENT_RX_ACK_TIMEOUT
                | RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
                | RAIL_EVENT_TXACK_PACKET_SENT
                | RAIL_EVENT_TXACK_ABORTED
                | RAIL_EVENT_TXACK_BLOCKED
                | RAIL_EVENT_TXACK_UNDERFLOW
                | RAIL_EVENT_TX_PACKET_SENT
                | RAIL_EVENT_TX_UNDERFLOW
                | RAIL_EVENT_TX_ABORTED
                | RAIL_EVENT_TX_BLOCKED
                | RAIL_EVENT_TX_CHANNEL_BUSY
                | RAIL_EVENT_CONFIG_UNSCHEDULED
                | RAIL_EVENT_SCHEDULER_STATUS
#ifdef CSL_SUPPORT
                | RAIL_EVENT_RX_CHANNEL_HOPPING_COMPLETE
                | RAIL_EVENT_TX_FIFO_ALMOST_EMPTY
#endif // CSL_SUPPORT
               ));

#ifndef EMBER_STACK_CONNECT
  // Register the RSSI -> LQI conversion callback to fix the LQI values
  RAIL_ConvertLqi(connectRailHandle, &convertRssiToLqi);
#endif//EMBER_STACK_CONNECT

#ifdef EMBER_STACK_CONNECT
  LOWER_MAC_ASSERT(RAIL_Calibrate(connectRailHandle,
                                  NULL,
                                  RAIL_CAL_ONETIME_IRCAL)
                   == RAIL_STATUS_NO_ERROR);
#else
  uint32_t dummy;
  LOWER_MAC_ASSERT(RAIL_IEEE802154_CalibrateIr2p4Ghz(connectRailHandle, &dummy) == RAIL_STATUS_NO_ERROR);
#endif

  LOWER_MAC_ASSERT(RAIL_GetRadioEntropy(connectRailHandle,
                                        randomSeedBuffer, 4) == 4);

// Don't seed the random generation in simulation: it is already done in child.c
// with the node ID (to have deterministic test results).
#if !defined(EMBER_TEST)
  halStackSeedRandom(emFetchInt32u(true, randomSeedBuffer));
#endif

#if     SLI_COEX_SUPPORTED
  emRadioEnableAutoAck(true); // Might suspend AutoACK if RHO already in effect
  emRadioEnablePta(sl_rail_util_coex_is_enabled());
#else//!SLI_COEX_SUPPORTED
  LOWER_MAC_ASSERT(RAIL_ConfigRxOptions(connectRailHandle,
                                        RAIL_RX_OPTION_TRACK_ABORTED_FRAMES,
                                        RAIL_RX_OPTION_TRACK_ABORTED_FRAMES)
                   == RAIL_STATUS_NO_ERROR);
#endif//SLI_COEX_SUPPORTED

  //emRadioEnableAddressMatching(emRadioAddressMatchingEnabled());

  radioIdle();
}
#ifndef EVENT_CONTROL_SYSTEM
void emLowerMacEventHandler(EmberEvent *event)
#else
void emLowerMacEventHandler(void)
#endif
{
  LOWER_MAC_DECLARE_INTERRUPT_STATE();

  LOWER_MAC_ASSERT(!getInternalFlag(FLAG_ONGOING_TX_DATA));

  sli_mac_inactivate_event(emLowerMacEvent);

  // Work-around for RAIL_LIB-2726.
  ATOMIC(
    if (getInternalFlag(FLAG_ONGOING_TX_ACK)
        && (elapsedTimeInt32u(lastRxWithAckTime, RAIL_GetTime())
#ifdef EMBER_STACK_CONNECT
            > emberMacAckTimeoutMS * 1000)) {
#else
            > 964)) {
#endif
    setInternalFlag(FLAG_ONGOING_TX_ACK, false);
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_ACK_SENT_WORKAROUND, 0);
  }
    );

  // Initial transmission attempt
  if (emLowerMacState == EMBER_MAC_STATE_BUSY) {
#ifdef EMBER_STACK_CONNECT
    sl_status_t status;
#endif

    LOWER_MAC_DISABLE_INT();
    // If the node is currently TXing an ACK, set the event active and try
    // the TX later.
    if (getInternalFlag(FLAG_ONGOING_TX_ACK)) {
      sli_mac_activate_event(emLowerMacEvent);

      LOWER_MAC_RESTORE_INT();
      return;
    }
    LOWER_MAC_RESTORE_INT();

    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_EVENT, 0);

#ifdef EMBER_STACK_CONNECT
    status = emMacPrepareTransmitBuffer(currentOutgoingPacket);

    if (status != SL_STATUS_OK) {
      sl_mac_lower_mac_set_idle(0);
      txCompleted(status);
      return;
    }
#endif
    // We turn off the autoAck in mfglib mode (see radioSetTx()) hence emLowerMacState should never set
    // to EMBER_MAC_STATE_TX_WAITING_FOR_ACK, otherwise loweMacState would never call txComplete or idle
    // and hence subsequent operations will be stalled.
    ATOMIC(
      emLowerMacState = ((sl_mac_flat_ack_requested(currentOutgoingPacket, true) && (emMfglibMode == 0u))
                         ? EMBER_MAC_STATE_TX_WAITING_FOR_ACK
                         : EMBER_MAC_STATE_TX_NO_ACK);
      setInternalFlag(FLAG_ONGOING_TX_DATA, true);
      tryTxCurrentPacket();
      );

#ifdef EMBER_STACK_CONNECT
    emCounterHandler(EMBER_COUNTER_PHY_OUT_PACKETS, 1);
#else
    //no equivalent ciunetr type, but for zigbee we need the sent sequence number
    emMacOutgoingSequenceNumber = sl_mac_flat_sequence_number(currentOutgoingPacket, true);
#endif
  } else if (emLowerMacState == EMBER_MAC_STATE_TX_WAITING_FOR_ACK
             && ackReceivedPending == LOWER_MAC_ACK_RX_NONE) {
#if     SLI_ANTDIV_SUPPORTED
    // If antenna diversity is enabled toggle the selected antenna.
    sl_rail_util_ant_div_toggle_tx_antenna();
#endif//SLI_ANTDIV_SUPPORTED
    if (macRetries > 0) {
      LOWER_MAC_DISABLE_INT();
      // If the node is currently TXing an ACK, set the event active and try
      // the TX later.
      if (getInternalFlag(FLAG_ONGOING_TX_ACK)) {
        sli_mac_activate_event(emLowerMacEvent);

        LOWER_MAC_RESTORE_INT();
        return;
      }
      LOWER_MAC_RESTORE_INT();

      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_EVENT, 1);

      // No ack received, try again
      macRetries--;

      ATOMIC(
        setInternalFlag(FLAG_ONGOING_TX_DATA, true);
        tryTxCurrentPacket();
        );
#ifdef EMBER_STACK_CONNECT
      emCounterHandler(EMBER_COUNTER_MAC_OUT_UNICAST_RETRY, 1);
#else
      emBuildAndSendCounterInfo(EMBER_COUNTER_MAC_TX_UNICAST_RETRY, EMBER_NULL_NODE_ID /*emMacShortDestination(lowerMacState.outgoingHeader) */, 0);
#endif
    } else {
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_EVENT, 2);

      // Run out of attempts, fail.
      sl_mac_lower_mac_set_idle(0);

      txCompleted(SL_STATUS_MAC_NO_ACK_RECEIVED);
    }
  } else if (emLowerMacState == EMBER_MAC_STATE_EXPECTING_DATA) {
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_EVENT, 3);

    // Timed out waiting for data.
    sl_mac_lower_mac_set_idle(0);

    RAIL_YieldRadio(connectRailHandle);

    txCompleted(SL_STATUS_MAC_NO_DATA);
  } else {
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_EVENT, 4);
  }
}

#ifdef CSL_SUPPORT
void emLowerMacCslEventHandler(EmberEvent *event)
{
  sli_mac_inactivate_event(emLowerMacCslEvent);

  // We get here after we received a wake up frame. We don't care if we
  // received the payload or not; we simply go back to duty cycling
  wakeupFrameReceived = false;
  sl_status_t status = configureDutyCycling(true);
  if (status == SL_STATUS_OK) {
    radioSetRx();
  }
  if (sl_mac_lower_mac_is_idle(0)) {
    RAIL_YieldRadio(connectRailHandle);
  }
}
#endif

void sl_mac_lower_mac_send(uint8_t mac_index, uint8_t *packet, sl_mac_tx_options_bitmask_t tx_options)
{
  bool use_csma = (tx_options & EMBER_MAC_USE_CSMA);
  UNUSED_VAR(mac_index);
  LOWER_MAC_ASSERT(sl_mac_lower_mac_is_idle(0));

  currentOutgoingPacket = packet;

  // We use CSMA only if the passed flag is set AND the number of CSMA tries is
  // non-zero. This allows the application to control CSMA by manipulating the
  // csmaParams struct and the stack to send out certain packets without CSMA
  // (for example, the frequency hopping messages).
  setInternalFlag(FLAG_CURRENT_TX_USE_CSMA,
                  (use_csma && (csmaParams.csmaTries > 0)));

#ifdef CSL_SUPPORT
  bool use_wakeup_frames = (tx_options & EMBER_MAC_USE_WAKEUP_FRAMES);

  // macCslMaxPeriodMs must be nonzero in order to send with wake up frames
  if (macCslMaxPeriodMs && use_wakeup_frames) {
    setInternalFlag(FLAG_CURRENT_TX_USE_WAKE_UP_FRAMES,
                    use_wakeup_frames);
  }
#endif // CSL_SUPPORT

  macRetries = emMacMaxRetries;
  current_force_tx_after_failed_cca_attempts = (use_csma ? default_force_tx_after_failed_cca_attempts : 0);
  emLowerMacState = EMBER_MAC_STATE_BUSY;

  sli_mac_activate_event(emLowerMacEvent);
  #ifdef EVENT_CONTROL_SYSTEM
  emberMarkTaskActive(emStackTask);// prevent idleling untill we complete the send
  #endif
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_EVENT, 5);
}

void sl_mac_lower_mac_tick(void)
{
  LOWER_MAC_DECLARE_INTERRUPT_STATE();
  LOWER_MAC_DISABLE_INT();

  // First, idle the radio if pending if the MAC is still idle, otherwise don't
  // bother.
  if (getInternalFlag(FLAG_IDLE_PENDING)) {
    if (sl_mac_lower_mac_is_idle(0)) {
      radioIdle();
    } else {
      setInternalFlag(FLAG_IDLE_PENDING, false);
    }
  }

  (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TICK, 0U);

  // Here interrupts are still disabled.

  // Next, handle tx complete status.
  if (txCompleteStatusPending != TX_COMPLETE_RESULT_NONE) {
    sl_status_t retStatus;
    if (txCompleteStatusPending == TX_COMPLETE_RESULT_SUCCESS) {
      retStatus = SL_STATUS_OK;
    } else if (txCompleteStatusPending == TX_COMPLETE_RESULT_CCA_FAIL) {
      retStatus = SL_STATUS_CCA_FAILURE;
    } else {
      // We map all the other errors to SL_STATUS_TRANSMIT_INCOMPLETE.
      retStatus = SL_STATUS_TRANSMIT_INCOMPLETE;
    }

    txCompleteStatusPending = TX_COMPLETE_RESULT_NONE;

    if (emLowerMacState == EMBER_MAC_STATE_TX_NO_ACK
        || retStatus != SL_STATUS_OK) {
      sl_mac_lower_mac_set_idle(0);
      LOWER_MAC_RESTORE_INT();
      txCompleted(retStatus);
      LOWER_MAC_DISABLE_INT();
    }
  }

  // Here interrupts are still disabled.

  // Next, handle incoming ACKs.
  if (emLowerMacState == EMBER_MAC_STATE_TX_WAITING_FOR_ACK
      && ackReceivedPending != LOWER_MAC_ACK_RX_NONE) {
    if (ackReceivedPending == LOWER_MAC_ACK_RX_TIMEOUT) {
      // Set the event active and let the event handler manage ACK retry (or
      // TX failure if we are out of retries).
      sli_mac_activate_event(emLowerMacEvent);
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_TICK, 0);
      ackReceivedPending = LOWER_MAC_ACK_RX_NONE;
      LOWER_MAC_RESTORE_INT();
    } else if (ackReceivedPending == LOWER_MAC_ACK_RX_FRAME_PENDING_NOT_SET
               || ackReceivedPending == LOWER_MAC_ACK_RX_FRAME_PENDING_SET) {
      bool dataRequestSent = currentOutgoingPacketIsDataRequest();
      bool framePending =
        (ackReceivedPending == LOWER_MAC_ACK_RX_FRAME_PENDING_SET);

      sli_mac_inactivate_event(emLowerMacEvent);
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_TICK, 1);
      ackReceivedPending = LOWER_MAC_ACK_RX_NONE;

      // Outgoing packet was a DATA REQUEST and the ACK has the frame pending
      // bit set: wait for incoming data.
      if (dataRequestSent && framePending) {
        emLowerMacState = EMBER_MAC_STATE_EXPECTING_DATA;
        sli_mac_set_event_delay_ms(emLowerMacEvent,
                                   EMBER_MAC_DATA_REQUEST_TIMEOUT_MS);
        LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_TICK, 2);
        radioSetRx();
        LOWER_MAC_RESTORE_INT();
      } else {
        sl_mac_lower_mac_set_idle(0);
        LOWER_MAC_RESTORE_INT();
        LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_TICK, 3);
        txCompleted((dataRequestSent) ? SL_STATUS_MAC_NO_DATA : SL_STATUS_OK);
      }
    }
  } else {
    // Clean up ackReceivedPending in case it was set by some spurious callback
    // while the node was no longer waiting for an ACK.
    ackReceivedPending = LOWER_MAC_ACK_RX_NONE;
    LOWER_MAC_RESTORE_INT();
  }

  LOWER_MAC_ASSERT_INTERRUPT_COUNTER();

  if (getInternalFlag(FLAG_CALIBRATION_NEEDED)) {
    setInternalFlag(FLAG_CALIBRATION_NEEDED, false);

    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_TICK, 4);
#ifdef EMBER_STACK_CONNECT
    emMacRadioNeedsCalibratingCallback();
#else
    emberRadioNeedsCalibratingHandler();
#endif
  }

  // Here interrupts are enabled. The phyToMac queue is ISR protected.

  //--------------------------
  // Process an incoming frame
  {
    bool idleNotificationPending = false;

    currentIncomingFrame = emPhyToMacQueueRemoveHead();
    if (currentIncomingFrame == NULL_BUFFER) {
      return;
    }

#ifdef EMBER_STACK_CONNECT
    emCounterHandler(EMBER_COUNTER_PHY_IN_PACKETS, 1); // no zigbee equivalent ?
#endif

    if (emLowerMacState == EMBER_MAC_STATE_EXPECTING_DATA) {
      sli_mac_inactivate_event(emLowerMacEvent);
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_TICK, 5);
      sl_mac_lower_mac_set_idle(0);
#ifndef EMBER_STACK_CONNECT
      sl_mac_packet_send_complete_callback(0, SL_STATUS_OK);
#endif
      idleNotificationPending = true;
    }

    if (sl_mac_lower_mac_is_idle(0)) {
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_TICK, 6);
      radioIdle();
    }

    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_TICK, 7);

    // Hand the packet to the upper MAC.
    sl_mac_receive_callback(0, currentIncomingFrame);

    currentIncomingFrame = NULL_BUFFER;

    // if idleNotificationPending is true and the internal state is still IDLE,
    // call the idle notification API.
    if (idleNotificationPending && emLowerMacState == EMBER_MAC_STATE_IDLE) {
      #ifdef EMBER_STACK_CONNECT
      emNotifyMacIsIdle(0);
      #else
      sl_mac_notify_mac_is_idle(0);
      #endif
    }
  }

  LOWER_MAC_ASSERT_INTERRUPT_COUNTER();
}

bool sl_mac_incoming_pending(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  return (!emPhyToMacQueueIsEmpty());
}

bool sl_mac_activity_pending(void)
{
  return (!sl_mac_lower_mac_is_idle(0)
          || getInternalFlags(ONGOING_TX_FLAGS
                              | FLAG_IDLE_PENDING
                              | FLAG_SYMBOL_TIMER_RUNNING)
          || txCompleteStatusPending != TX_COMPLETE_RESULT_NONE
          || ackReceivedPending != LOWER_MAC_ACK_RX_NONE);
}

void sl_mac_purge_incoming_queue(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  while (emPhyToMacQueueRemoveHead() != NULL_BUFFER) ;
}

void sl_mac_set_csma_params(sl_mac_csma_parameters_t *macParams)
{
  csmaParams.csmaMinBoExp = macParams->minBackoffExp;
  csmaParams.csmaMaxBoExp = macParams->maxBackoffExp;
  csmaParams.csmaTries = ((macParams->checkCca)
                          ? macParams->maxCcaAttempts
                          : 0);

  emMacMaxRetries = macParams->maxRetries;
}

void sl_mac_get_csma_params(sl_mac_csma_parameters_t *macParams)
{
  macParams->minBackoffExp = csmaParams.csmaMinBoExp;
  macParams->maxBackoffExp = csmaParams.csmaMaxBoExp;
  macParams->checkCca = (csmaParams.csmaTries > 0);
  macParams->maxCcaAttempts = csmaParams.csmaTries;

  macParams->maxRetries = emMacMaxRetries;
}

bool sl_mac_lower_mac_get_check_cca(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  return (csmaParams.csmaTries > 0U);
}

static uint8_t old_csma_tries = 0U;
void sl_mac_lower_mac_disable_check_cca(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  if (csmaParams.csmaTries > 0U) {
    old_csma_tries = csmaParams.csmaTries;
  }
  csmaParams.csmaTries = 0U;
}

void sl_mac_lower_mac_enable_check_cca(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  if (old_csma_tries > 0U) {
    csmaParams.csmaTries = old_csma_tries;
  }
}

void sl_mac_set_aux_address_filtering(EmberNodeId nodeId, uint8_t index)
{
  // RAIL supports up to 3 sets of addresses. Index 0 is reserved to the main
  // set of addresses.
  LOWER_MAC_ASSERT(index != 0 && index < 3);

  LOWER_MAC_ASSERT(RAIL_IEEE802154_SetShortAddress(connectRailHandle,
                                                   nodeId,
                                                   index)
                   == RAIL_STATUS_NO_ERROR);
  LOWER_MAC_ASSERT(RAIL_IEEE802154_SetPanId(connectRailHandle,
                                            emberGetPanId(),
                                            index)
                   == RAIL_STATUS_NO_ERROR);
  LOWER_MAC_ASSERT(RAIL_IEEE802154_SetLongAddress(connectRailHandle,
                                                  emberGetEui64(),
                                                  index)
                   == RAIL_STATUS_NO_ERROR);
}

// -----------------------------------------------------------------------------
// Radio APIs wrappers

void sl_mac_lower_mac_set_node_id(uint8_t mac_index, uint8_t addr_filter_index, EmberNodeId nodeId)
{
  UNUSED_VAR(mac_index);
  LOWER_MAC_ASSERT(RAIL_IEEE802154_SetShortAddress(connectRailHandle, nodeId, addr_filter_index)
                   == RAIL_STATUS_NO_ERROR);
}

void sl_mac_lower_mac_set_pan_id(uint8_t mac_index, uint8_t addr_filter_index, EmberPanId panId)
{
  UNUSED_VAR(mac_index);
  LOWER_MAC_ASSERT(RAIL_IEEE802154_SetPanId(connectRailHandle, panId, addr_filter_index)
                   == RAIL_STATUS_NO_ERROR);
}

void sl_mac_set_coordinator(bool isCoordinator)
{
  LOWER_MAC_ASSERT(RAIL_IEEE802154_SetPanCoordinator(connectRailHandle,
                                                     isCoordinator)
                   == RAIL_STATUS_NO_ERROR);
}

bool sl_mac_lower_mac_is_idle(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  #ifdef CSL_SUPPORT
  return ((emLowerMacState == EMBER_MAC_STATE_IDLE) && (!wakeupFrameReceived));
  #else
  return (emLowerMacState == EMBER_MAC_STATE_IDLE);
  #endif
}

void sl_mac_lower_mac_set_idle(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  emLowerMacState = EMBER_MAC_STATE_IDLE;
}

bool sl_mac_lower_mac_is_expecting_data(void)
{
  return (emLowerMacState == EMBER_MAC_STATE_EXPECTING_DATA);
}

// We don't store the idle mode here at the lower MAC, we just get it from the
// upper MAC.
sl_status_t sl_mac_lower_mac_set_radio_idle_mode(uint8_t mac_index, RadioPowerMode mode)
{
  UNUSED_VAR(mac_index);
  LOWER_MAC_ASSERT(sl_mac_lower_mac_is_idle(mac_index));

  radioIdle();

  return SL_STATUS_OK;
}

sl_status_t sl_mac_lower_mac_set_radio_power(uint8_t mac_index, int8_t power)
{
  UNUSED_VAR(mac_index);
  // Power level is in deci dBm
  RAIL_Status_t status = RAIL_SetTxPowerDbm(connectRailHandle, power * 10);

  return ((status == RAIL_STATUS_NO_ERROR)
          ? SL_STATUS_OK
          : SL_STATUS_INVALID_PARAMETER);
}

int8_t sl_mac_lower_mac_get_radio_power(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  return (int8_t)(RAIL_GetTxPowerDbm(connectRailHandle) / 10);
}

uint8_t sl_mac_lower_mac_get_radio_channel(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  return currentChannel;
}

sl_status_t sl_mac_lower_mac_set_radio_channel(uint8_t mac_index, uint8_t channel)
{
  UNUSED_VAR(mac_index);
  LOWER_MAC_ASSERT(sl_mac_lower_mac_is_idle(0) || sl_mac_lower_mac_is_expecting_data());

  if (!sl_mac_lower_mac_channel_is_valid(0, channel)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  currentChannel = channel;

  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SET_CHANNEL, channel);

  if (sl_mac_lower_mac_is_idle(0)) {
    radioIdle();
  } else { // Expecting data
    radioSetRx();
  }

  (void) RAIL_SetFreqOffset(connectRailHandle, ((int16_t)emSynthFreqOffset) << 7);
  return SL_STATUS_OK;
}

bool sl_mac_lower_mac_channel_is_valid(uint8_t mac_index, uint8_t mac_page_chan)
{
  UNUSED_VAR(mac_index);
  return (RAIL_IsValidChannel(connectRailHandle, mac_page_chan) == 0);
}

void sl_mac_radio_ok_to_idle(void)
{
  if (sl_mac_lower_mac_is_idle(0)) {
    radioIdle();
  }
}

void sl_mac_set_cca_threshold(int8_t threshold)
{
  csmaParams.ccaThreshold = threshold;
}
//something similar to emSetSimulatorEnergyLevel to make this variable
#ifdef UNIFIED_MAC_SCRIPTED_TEST

static uint8_t energyLevels[SL_NUM_802_15_4_CHANNELS] = { -40, -39, -38, -37,
                                                          -36, -40, -39, -38,
                                                          -37, -36, -40, -39,
                                                          -38, -37, -36, -40, };
// this is here instead of rail-stub, because it requires the current channel
int16_t RAIL_GetRssi(RAIL_Handle_t railHandle, bool wait)
{
  if (currentChannel >= SL_MIN_802_15_4_CHANNEL_NUMBER) {
    return energyLevels[currentChannel - SL_MIN_802_15_4_CHANNEL_NUMBER];
  }
  return -128;
}
#endif

void sl_mac_lower_mac_update_active_radio_config(void)
{
  RadioPowerMode currentMode = sl_mac_get_radio_idle_mode(0U);
  (void) sl_mac_lower_mac_set_radio_idle_mode(0U, EMBER_RADIO_POWER_MODE_OFF);
  (void) sl_rail_util_plugin_config_2p4ghz_radio(connectRailHandle);
  (void) sl_mac_lower_mac_set_radio_idle_mode(0U, currentMode);
}

// TODO - FLEX-593: switch to use the RAIL_StartAverageRssi() API.
int8_t sl_mac_radio_energy_detection(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  // The RAIL_GetRssi() returns the RSSI in quarter dBm.
  int8_t rssiVal = (int8_t)(RAIL_GetRssi(connectRailHandle, true) / 4);

  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_GET_RSSI, rssiVal);

  // TODO: we should ensure this is being called while the radio is in RX. What
  // if an ACK is being sent? What does RAIL_GetRssi() return?

  return rssiVal;
}

uint16_t sl_mac_get_symbol_duration_us(void)
{
  uint32_t symbol_rate = RAIL_GetSymbolRate(connectRailHandle);
  if (symbol_rate) {
    symbol_rate = (uint16_t)(1000000 / symbol_rate);
    return (symbol_rate > 0) ? symbol_rate : 1;
  } else {
    return 1;
  }
}

uint16_t sl_mac_get_bit_duration_us(void)
{
  uint32_t bit_rate = RAIL_GetBitRate(connectRailHandle);
  if (bit_rate) {
    bit_rate = (uint16_t)(1000000 / bit_rate);
    return (bit_rate > 0) ? bit_rate : 1;
  } else {
    return 1;
  }
}

sl_status_t sl_mac_lower_mac_schedule_symbol_timer(uint8_t mac_index, uint16_t symbols)
{
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SYMBOL_TIMER, 0);

  setInternalFlag(FLAG_SYMBOL_TIMER_RUNNING, true);

  RAIL_SetTimer(connectRailHandle,
                symbols * sl_mac_get_symbol_duration_us(),
                RAIL_TIME_DELAY,
                RAILCb_TimerExpired);

  return SL_STATUS_OK;
}

void sl_mac_lower_mac_cancel_symbol_timer(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SYMBOL_TIMER, 1);

  LOWER_MAC_ASSERT(getInternalFlag(FLAG_SYMBOL_TIMER_RUNNING));

  setInternalFlag(FLAG_SYMBOL_TIMER_RUNNING, false);

  RAIL_CancelTimer(connectRailHandle);
}

uint32_t sl_mac_get_mac_timer(void)
{
  return RAIL_GetTime();
}

#ifdef EMBER_STACK_CONNECT
// Note, this is just a temporary buffer system thing. We probably won't need this after the new buffer system
uint32_t sl_mac_get_current_packet_sync_word_detection_elapsed_time_us(void)
{
  uint8_t *currentIncomingFramePtr;
  uint16_t currentIncomingFrameBufferLength;
  uint32_t syncTimeUs;

  LOWER_MAC_ASSERT(currentIncomingFrame != NULL_BUFFER);

  currentIncomingFramePtr = emGetBufferPointer(currentIncomingFrame);
  currentIncomingFrameBufferLength = emGetBufferLength(currentIncomingFrame);

  syncTimeUs = emberFetchLowHighInt32u(currentIncomingFramePtr
                                       + currentIncomingFrameBufferLength
                                       - EMBER_APPENDED_INFO_TOTAL_LENGTH
                                       + EMBER_APPENDED_INFO_SYNC_TIME_OFFSET);

  return elapsedTimeInt32u(syncTimeUs, RAIL_GetTime());
}

uint8_t sl_mac_get_current_packet_appended_flags(void)
{
  uint8_t *currentIncomingFramePtr;
  uint16_t currentIncomingFrameBufferLength;

  LOWER_MAC_ASSERT(currentIncomingFrame != NULL_BUFFER);

  currentIncomingFramePtr = emGetBufferPointer(currentIncomingFrame);
  currentIncomingFrameBufferLength = emGetBufferLength(currentIncomingFrame);

  return currentIncomingFramePtr[currentIncomingFrameBufferLength
                                 - EMBER_APPENDED_INFO_TOTAL_LENGTH
                                 + EMBER_APPENDED_INFO_FLAGS_OFFSET];
}

int8_t sl_mac_get_current_packet_rssi(void)
{
  uint8_t *currentIncomingFramePtr;
  uint16_t currentIncomingFrameBufferLength;

  LOWER_MAC_ASSERT(currentIncomingFrame != NULL_BUFFER);

  currentIncomingFramePtr = emGetBufferPointer(currentIncomingFrame);
  currentIncomingFrameBufferLength = emGetBufferLength(currentIncomingFrame);

  return (int8_t)currentIncomingFramePtr[currentIncomingFrameBufferLength
                                         - EMBER_APPENDED_INFO_TOTAL_LENGTH
                                         + EMBER_APPENDED_INFO_RSSI_OFFSET];
}
#endif

void sl_mac_calibrate_current_channel(void)
{
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_CALIBRATE,
                             RAIL_CAL_ALL_PENDING);

// TODO: some simulation RAIL files need to be polished
#if !defined(EMBER_TEST)

#ifdef EMBER_STACK_CONNECT
  RAIL_Calibrate(connectRailHandle, NULL, RAIL_CAL_ALL_PENDING);
#else
  RAIL_CalMask_t pending = RAIL_GetPendingCal(connectRailHandle);
  if (pending & RAIL_CAL_TEMP_VCO) {
    RAIL_CalibrateTemp(connectRailHandle);
  }
#endif //EMBER_STACK_CONNECT

#endif
}

// TODO: this is a temporary API needed for a temporary workaround in the HAL
// code: basically the code in assert-crash-handlers.c now calls emRadioSleep().
// This API is now also needed for a weird use case in misc-onboard.c
void sl_mac_lower_mac_radio_sleep(void)
{
  // Need to clear the outgoing pending and cancel the TX sent timer so that we
  // can change the radio state without hitting the debug asserts.
  LOWER_MAC_DEBUG_SET_OUTGOING_PENDING(false, false);
  LOWER_MAC_DEBUG_CANCEL_TX_SENT_TIMER(false);

#if defined(MAC_DEBUG_TOKEN)
  LOWER_MAC_DEBUG_DUMP_ACTIONS_TO_TOKEN();
#else
  LOWER_MAC_DEBUG_DUMP_ACTIONS();
#endif

  RAIL_Idle(connectRailHandle, RAIL_IDLE_ABORT, true);
  (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_IDLED, 0U);
  (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_IDLED, 0U);

#ifndef EMBER_TEST
  halStackRadioPowerDownBoard();
  // Note:
  // We call halStackRadioPowerMainControl from here, which is documented to not
  // be called from ISR context -- so if sl_mac_lower_mac_radio_sleep is called
  // from interrupt context that contract is broken.
  //
  // Currently the only user of this API that is called in interrupt context is
  // in Zigbee's assert-crash-handlers.c, but we're already crashing there, so
  // we can ignore it for that case.
  radioPowerFem(false);
#endif
}

void sl_mac_lower_mac_radio_wakeup(void)
{
  radioIdle();
}

// -----------------------------------------------------------------------------
// RAIL callbacks related functions.

// This callback fires if transmission was successful.
// Notice that we configure RAIL so that the radio goes back to RX after any
// TX operation.
static void packetSentCallback(bool isAck)
{
#ifdef CSL_SUPPORT
  if (getInternalFlag(FLAG_CURRENT_TX_USE_WAKE_UP_FRAMES)) {
    cslPacketsSent++;
    if (cslPacketsSent != (totalWakeupFramesToSend + 1)) {
      fillTxFifoWithWakeupFrames();
      return;
    }
    setInternalFlag(FLAG_CURRENT_TX_USE_WAKE_UP_FRAMES, false);

    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_CSL_TX_COMPLETE,
                               cslPacketsSent);
  }
#endif // CSL_SUPPORT

  if (isAck) {
    // We successfully sent out an ACK.
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_TX_ACK_SENT, 0xFF);

    setInternalFlag(FLAG_ONGOING_TX_ACK, false);

    // We acked the packet we received after a poll: we can yield now.
    if (emLowerMacState == EMBER_MAC_STATE_EXPECTING_DATA) {
      RAIL_YieldRadio(connectRailHandle);
    }
  } else if (getInternalFlag(FLAG_ONGOING_TX_DATA)) {
    current_force_tx_after_failed_cca_attempts = 0;
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_TX_DATA_SENT,
                               txCompleteStatusPending);

    LOWER_MAC_ASSERT(txCompleteStatusPending == TX_COMPLETE_RESULT_NONE);

    setInternalFlag(FLAG_ONGOING_TX_DATA, false);

    txCompleteStatusPending = TX_COMPLETE_RESULT_SUCCESS;

    if (emLowerMacState == EMBER_MAC_STATE_TX_WAITING_FOR_ACK) {
      setInternalFlag(FLAG_WAITING_FOR_ACK, true);
      (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ACK_WAITING, 0U);
    }

    LOWER_MAC_DEBUG_ASSERT_OUTGOING_PENDING(true, false);
    LOWER_MAC_DEBUG_SET_OUTGOING_PENDING(false, false);
    LOWER_MAC_DEBUG_CANCEL_TX_SENT_TIMER(true);

    if (emLowerMacState == EMBER_MAC_STATE_TX_NO_ACK) {
      (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ENDED, 0U);
      RAIL_YieldRadio(connectRailHandle);
    }

    STACK_WAKEUP_ISR_HANDLER;
  }
}

// This callback fires if transmission failed.
// Notice that we configure RAIL so that the radio goes back to RX after any
// TX operation.
static void txFailedCallback(bool isAck, uint8_t status)
{
  if (isAck) {
    // We failed to send out an ACK.
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_TX_FAILED_ACK,
                               status);

    setInternalFlag(FLAG_ONGOING_TX_ACK, false);
  } else if (getInternalFlag(FLAG_ONGOING_TX_DATA)) {
    if (status == TX_COMPLETE_RESULT_CCA_FAIL
        && current_force_tx_after_failed_cca_attempts > 0) {
      current_force_tx_after_failed_cca_attempts -= 1;
      if (current_force_tx_after_failed_cca_attempts == 0) {
        setInternalFlag(FLAG_CURRENT_TX_USE_CSMA, false);
      }
      setInternalFlag(FLAG_ONGOING_TX_DATA, false);
      emLowerMacState = EMBER_MAC_STATE_BUSY;
      // Activate the event to try to send again
      sli_mac_activate_event(emLowerMacEvent);
      #ifdef EVENT_CONTROL_SYSTEM
      emberMarkTaskActive(emStackTask);
      #endif
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_MAC_EVENT, 5);
    } else {
      current_force_tx_after_failed_cca_attempts = 0;
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_TX_FAILED_DATA,
                                 status);

      setInternalFlag(FLAG_ONGOING_TX_DATA, false);

      LOWER_MAC_ASSERT(txCompleteStatusPending == TX_COMPLETE_RESULT_NONE);

      txCompleteStatusPending = status;

      LOWER_MAC_DEBUG_ASSERT_OUTGOING_PENDING(true, false);
      LOWER_MAC_DEBUG_SET_OUTGOING_PENDING(false, false);
      LOWER_MAC_DEBUG_CANCEL_TX_SENT_TIMER(true);

      STACK_WAKEUP_ISR_HANDLER;
    }
  }
  #ifndef EMBER_STACK_CONNECT
  if (status == TX_COMPLETE_RESULT_CCA_FAIL) {
    emBuildAndSendCounterInfo(EMBER_COUNTER_PHY_CCA_FAIL_COUNT, EMBER_NULL_NODE_ID /*emMacShortDestination(lowerMacState.outgoingHeader) */, 0);
  }
  #endif
}

static void packetReceivedCallback(void)
{
  RAIL_RxPacketInfo_t packetInfo;
  RAIL_RxPacketDetails_t packetDetails;
  RAIL_RxPacketHandle_t packetHandle;
  Buffer rxPacketBuffer;
  uint8_t macHdr[EMBER_MAC_HEADER_SEQUENCE_NUMBER_OFFSET + 1];
  uint8_t *rxPacket = macHdr;
  uint8_t appendedFlags = 0x00;

  packetHandle = RAIL_GetRxPacketInfo(connectRailHandle,
                                      RAIL_RX_PACKET_HANDLE_NEWEST,
                                      &packetInfo);

  LOWER_MAC_ASSERT(packetHandle != RAIL_RX_PACKET_HANDLE_INVALID);
  if (packetInfo.packetStatus != RAIL_RX_PACKET_READY_SUCCESS) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_CORRUPTED,
                           (uint32_t) isReceivingFrame());
    return;
  }

  LOWER_MAC_ASSERT(RAIL_GetRxPacketDetailsAlt(connectRailHandle,
                                              packetHandle,
                                              &packetDetails)
                   == RAIL_STATUS_NO_ERROR);

  // Adding 2 bytes to account for CRC, which the way we configured RAIL is not
  // included in the packetBytes field of RAIL_RxPacketInfo_t.
  uint16_t length = packetInfo.packetBytes + 2U;
  // Store the timestamp in the packet details
  RAIL_Time_t *timestamp = &packetDetails.timeReceived.packetTime;
  LOWER_MAC_ASSERT(RAIL_GetRxTimeSyncWordEnd(connectRailHandle,
                                             length,
                                             timestamp)
                   == RAIL_STATUS_NO_ERROR);

  // Peek at the MAC header and seq# for handling incoming ACKs specially
  LOWER_MAC_ASSERT(RAIL_PeekRxPacket(connectRailHandle,
                                     packetHandle,
                                     macHdr,
                                     sizeof(macHdr),
                                     0) == sizeof(macHdr));

  if (emMfglibMode == 0u  // no autoAck in promiscuous mode hence this `if` block is not needed in mfglibmode.
      && sl_mac_flat_frame_type(rxPacket, true) == EMBER_MAC_HEADER_FC_FRAME_TYPE_ACK) {
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RX_PACKET,
                               (1 | ((uint64_t)sl_mac_flat_sequence_number(rxPacket, true) << 32)));
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ENDED,
                           (uint32_t) isReceivingFrame());

    // We should only receive from RAIL an ACK if we are waiting for an ACK and
    // we should only receive ACks with matching sequence number. However, we
    // check here for sanity purposes and discard any spurious ACK.
    if (emLowerMacState == EMBER_MAC_STATE_TX_WAITING_FOR_ACK
        && sl_mac_flat_sequence_number(rxPacket, true) == emMacOutgoingSequenceNumber) {
      #ifndef EMBER_TEST
      // limit the scope of this check, since it could only occure if
      // mfglib 'promiscuous' receives go thru this code.
      // This is not tested in simulation, and causes unncessary failure in scripted/unit tests
      LOWER_MAC_ASSERT(packetDetails.isAck);
      #endif
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RX_PACKET,
                                 (2 | ((uint64_t)emMacOutgoingSequenceNumber << 32)));

      bool framePendingInAck = sl_mac_flat_frame_pending(rxPacket, true);
      (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ACK_RECEIVED,
                             (uint32_t) framePendingInAck);

      setInternalFlag(FLAG_WAITING_FOR_ACK, false);

      ackReceivedPending = framePendingInAck
                           ? LOWER_MAC_ACK_RX_FRAME_PENDING_SET
                           : LOWER_MAC_ACK_RX_FRAME_PENDING_NOT_SET;

#ifdef EMBER_STACK_CONNECT
      ackReceivedRssi = packetDetails.rssi;
#endif

      // Yield the radio upon receiving an ACK as long as it is not related to
      // a data request.
      if (!currentOutgoingPacketIsDataRequest()) {
        RAIL_YieldRadio(connectRailHandle);
      }
    }
    return;
  }

  rxPacketBuffer = emAllocateAsyncBuffer(packetInfo.packetBytes
                                         + EMBER_APPENDED_INFO_TOTAL_LENGTH);

  if (rxPacketBuffer == NULL_BUFFER) {
#ifdef EMBER_STACK_CONNECT
    emCounterHandler(EMBER_COUNTER_MAC_DROP_IN_MEMORY, 1);
#endif
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RX_PACKET, 0);
    // We won't know what kind of packet it was so the best we can do
    // is mark it corrupted in an out-of-memory situation.
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_CORRUPTED,
                           (uint32_t) isReceivingFrame());
    return;
  }

  rxPacket = emGetBufferPointer(rxPacketBuffer);
   #ifdef UNIFIED_MAC_SCRIPTED_TEST
  LOWER_MAC_ASSERT(RAIL_PeekRxPacket(connectRailHandle,
                                     packetHandle,
                                     rxPacket,
                                     packetInfo.packetBytes,
                                     0) == packetInfo.packetBytes);
  #else
  // Copy the packet out of RAIL FIFO.
  RAIL_CopyRxPacket(rxPacket, &packetInfo);
  #endif

#ifdef CSL_SUPPORT
  // Check if this is a Wakeup Frame
  uint8_t ieIndex = 0;
  if (emMfglibMode == 0u && isWakeupFrame(rxPacket, &ieIndex)) {
    // Get the rendezvous time and setup event to clear things after reception of the data frame
    if (wakeupFrameReceived == false) {
      sl_mac_rendezvous_ie_t *rendezvous_ie = (sl_mac_rendezvous_ie_t *)&rxPacket[ieIndex];
      uint32_t rendezvous_time_in_ms = (((rendezvous_ie->rendezvous_time * 10) * USEC_PER_SYMBOL_2_4_GHZ) / 1000) + 5;

      // When we receive a wake up frame, disable duty cycling and keep the
      // receiver on until the rendezvous time plus some tolerance

      RAIL_SchedulerInfo_t rxSchedulerInfo = {
        .priority = 0,  // highest priority - we don't want to miss the payload
        .slipTime = 0,
        .transactionTime = 0
      };
      sl_status_t status = configureDutyCycling(false);
      if (status == SL_STATUS_OK) {
        (void)RAIL_StartRx(connectRailHandle,
                           currentChannel,
                           &rxSchedulerInfo);
      }
      wakeupFrameReceived = true;
      sli_mac_set_event_delay_ms(emLowerMacCslEvent, rendezvous_time_in_ms);
      // Wakup the stack task (if it is currently suspended).
      STACK_WAKEUP_ISR_HANDLER;
    }
    return;
  }

  wakeupFrameReceived = false;

#endif // CSL_SUPPORT

  // Incoming frame requires an ACK.
  if (sl_mac_flat_ack_requested(rxPacket, true)) {
    (void) onPtaStackEvent((RAIL_IsRxAutoAckPaused(connectRailHandle)
                            ? SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_BLOCKED
                            : SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACKING),
                           (uint32_t) isReceivingFrame());
    bool isDataRequest =
      (sl_mac_flat_frame_type(rxPacket, true) == EMBER_MAC_HEADER_FC_FRAME_TYPE_COMMAND
       && sl_mac_flat_payload(rxPacket, true)[EMBER_MAC_PAYLOAD_COMMAND_ID_OFFSET]
       == MAC_DATA_REQUEST);

    setInternalFlag(FLAG_ONGOING_TX_ACK, true);

    // Work-around for RAIL_LIB-2726.
    lastRxWithAckTime = RAIL_GetTime();

    if (isDataRequest) {
      if (getInternalFlag(FLAG_DATA_POLL_FRAME_PENDING_SET)) {
        appendedFlags |= EMBER_APPENDED_INFO_FLAG_ACK_FRAME_PENDING_SET;
        setInternalFlag(FLAG_DATA_POLL_FRAME_PENDING_SET, false);

        // Incoming data poll, corresponding ACK frame pending bit set.
        LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RX_PACKET,
                                   (3 | ((uint64_t)sl_mac_flat_sequence_number(rxPacket) << 32)));
      } else {
        // Incoming data poll, corresponding ACK frame pending bit not set.
        LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RX_PACKET,
                                   (4 | ((uint64_t)sl_mac_flat_sequence_number(rxPacket) << 32)));
      }
    } else {
      // Incoming frame other than a data poll requiring an ACK.
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RX_PACKET,
                                 (5 | ((uint64_t)sl_mac_flat_sequence_number(rxPacket) << 32)));
    }
  } else {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ENDED,
                           (uint32_t) isReceivingFrame());
    // Incoming frame not requiring an ACK.
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RX_PACKET,
                               (6 | ((uint64_t)sl_mac_flat_sequence_number(rxPacket) << 32)));

    // We received a frame that does not require an ACK as result of a data
    // poll: we yield the radio here.
    if (emLowerMacState == EMBER_MAC_STATE_EXPECTING_DATA) {
      RAIL_YieldRadio(connectRailHandle);
    }
  }

#ifdef EMBER_STACK_CONNECT
  // Write the lower MAC appended info (RSSI, syncTime and flags) and add the
  // packet to the incoming queue.

  rxPacket[packetInfo.packetBytes + EMBER_APPENDED_INFO_RSSI_OFFSET]
    = packetDetails.rssi;

  emberStoreLowHighInt32u(rxPacket + packetInfo.packetBytes
                          + EMBER_APPENDED_INFO_SYNC_TIME_OFFSET,
                          packetDetails.timeReceived.packetTime);

  rxPacket[packetInfo.packetBytes + EMBER_APPENDED_INFO_FLAGS_OFFSET] =
    appendedFlags;

  emPhyToMacQueueAdd(rxPacketBuffer);

#else // EMBER_STACK_CONNECT
  uint8_t *appendedInfo = rxPacket + packetInfo.packetBytes;

#ifndef EMBER_MULTI_NETWORK_STRIPPED
  uint8_t current_nwk_index = sl_mac_get_current_radio_network_index(0);
  uint8_t nwk_index_bitmask = 0;
  uint16_t pan_id = EMBER_BROADCAST_PAN_ID;

  // The order of operation has been optimized for better code readability and save some code space.
  // 1. Check for broadcast pan ids. If yes, duplicate the incoming packet for all active networks
  //    - If yes, then all incoming packets should be tagged with the current network index
  //    - Also duplicate the packet if pan id matches any other active network
  // 2. For all other packets (unicast), tag the incoming packet with the network index if the
  //    pan id matches.
  // 3. Check if a scan is in progress.
  // 4. If mfglibMode is enabled then item 1 and 2 is not needed, instead tag all packets to current nwk index.

  // Check if broadcast pan is set for the incoming packet
  if (emMfglibMode == 0u) {
    if (sl_mac_is_broadcast_pan(rxPacket, true)) {
      // Get all active network indices on the current radio channel
      sl_mac_get_matching_nwk_index_bitmask(0, EMBER_BROADCAST_PAN_ID, currentRadioChannel, &nwk_index_bitmask);
    } else {
      // Get network indices matching the incoming pan id and add it to the current bitbask
      if (sl_mac_get_pan_id(rxPacket, true, &pan_id) == SL_STATUS_OK) {
        sl_mac_get_matching_nwk_index_bitmask(0, pan_id, currentRadioChannel, &nwk_index_bitmask);
      }
    }
  }

  // Check if a scan is in progress or if there is no matching network
  // If there is no matching network to handle the incoming packet (such as beacons when we are not scanning)
  // then set the index to current index and pass it to the higher layer to handle. This will also
  // be useful in promiscuous mode.
  if (sl_mac_scan_pending() || (nwk_index_bitmask == 0)) {
    // Set the network index bitmask to the current network
    nwk_index_bitmask |= 1 << current_nwk_index;
  }
#endif // EMBER_MULTI_NETWORK_STRIPPED

  appendedInfo[APPENDED_INFO_CHANNEL_OVERWRITE_BYTE_INDEX] = currentRadioChannel;  //emRadioChannel;

#ifdef EMBER_TEST
  // We now apply RSSI_DBM_OFFSET_RAIL so upper layers need not be PHY-specific
  appendedInfo[APPENDED_INFO_RSSI_BYTE_INDEX] = -35;  //RSSI_DBM_OFFSET_RAIL;
  appendedInfo[APPENDED_INFO_LQI_BYTE_INDEX]  = 0xFF;
#else
  // We now apply RSSI_DBM_OFFSET_RAIL so upper layers need not be PHY-specific
  appendedInfo[APPENDED_INFO_RSSI_BYTE_INDEX] = packetDetails.rssi
                                                + 0;  //RSSI_DBM_OFFSET_RAIL;
  appendedInfo[APPENDED_INFO_LQI_BYTE_INDEX]  = packetDetails.lqi;
#endif

  // RAIL doesn't support providing a 'gain' metric, nor is one
  // needed by test apps or stack, so we just provide dummy value.
  appendedInfo[APPENDED_INFO_GAIN_BYTE_INDEX] = 0xFF;
  appendedInfo[APPENDED_INFO_MAC_TIMER_BYTE_2_INDEX] = BYTE_2(packetDetails.timeReceived.packetTime);
  appendedInfo[APPENDED_INFO_MAC_TIMER_BYTE_1_INDEX] = BYTE_1(packetDetails.timeReceived.packetTime);
  appendedInfo[APPENDED_INFO_MAC_TIMER_BYTE_0_INDEX] = BYTE_0(packetDetails.timeReceived.packetTime);

  // on chip this byte already includes the CRC length
  // And previously the _radioreceive in hardware-mac-sim used to add this to.
  // However, in simulated rf_hal version of _radioreceive this does not get added
  #ifdef EMBER_TEST
  rxPacket[0] += PHY_APPENDED_CRC_SIZE;
  #endif
  if (appendedFlags & EMBER_APPENDED_INFO_FLAG_ACK_FRAME_PENDING_SET) {
    rxPacket[1] |= MAC_FRAME_FLAG_ACK_REQUIRED;
  } else {
    rxPacket[1] &= ~MAC_FRAME_FLAG_ACK_REQUIRED;
  }

#ifndef EMBER_MULTI_NETWORK_STRIPPED
  // Queue and duplicate packets as needed
  uint16_t originalRxBufferLen = emGetBufferLength(rxPacketBuffer);
  Buffer *rxPacketBufferPtr = &rxPacketBuffer;
  Buffer newRxPacketBuffer = NULL_BUFFER;

  // Send the Received Packet to all the networks that matched
  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    if ((nwk_index_bitmask & (1U << i)) != 0U) {
      if (rxPacket == NULL) {
        newRxPacketBuffer = emAllocateAsyncBuffer(originalRxBufferLen);
        // If the buffer allocation fails, then break out of the loop
        // since all subsequent requests will be for the same size
        if (newRxPacketBuffer == NULL_BUFFER) {
          break;
        }

        // Point to the new buffer now
        rxPacketBufferPtr = &newRxPacketBuffer;

        // Copy old buffer contents to the new one
        rxPacket = emGetBufferPointer(newRxPacketBuffer);
        emCopyFromLinkedBuffers(rxPacket, rxPacketBuffer, originalRxBufferLen);
        appendedInfo = rxPacket + packetInfo.packetBytes;
      }

      // Overwrite the Network Index byte
      appendedInfo[APPENDED_INFO_NETWORK_OVERWRITE_BYTE_INDEX]
        = (i) | (PHY_THIS_ID << APPENDED_INFO_NETWORK_OVERWRITE_PHY_ID_SHIFT);
      emPhyToMacQueueAdd(*rxPacketBufferPtr);
      rxPacket = NULL;
    }
  }
#else
  appendedInfo[APPENDED_INFO_NETWORK_OVERWRITE_BYTE_INDEX]
    = sl_mac_get_current_radio_network_index(0) //mac_index
      | (PHY_THIS_ID << APPENDED_INFO_NETWORK_OVERWRITE_PHY_ID_SHIFT);
  emPhyToMacQueueAdd(rxPacketBuffer);
#endif // EMBER_MULTI_NETWORK_STRIPPED

#endif // EMBER_STACK_CONNECT
#ifdef EVENT_CONTROL_SYSTEM
  // don't let the stack or event task idle.
  emberMarkTaskActive(emStackTask);
#endif
  // Wakup the stack task (if it is currently suspended).
  STACK_WAKEUP_ISR_HANDLER;
}

static void ackTimeoutCallback(void)
{
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RX_ACK_TIMEOUT, 0xFF);
  LOWER_MAC_ASSERT(emLowerMacState == EMBER_MAC_STATE_TX_WAITING_FOR_ACK);
  LOWER_MAC_ASSERT(getInternalFlag(FLAG_WAITING_FOR_ACK));

  (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ACK_TIMEDOUT,
                         (uint32_t) macRetries);

  setInternalFlag(FLAG_WAITING_FOR_ACK, false);

  ackReceivedPending = LOWER_MAC_ACK_RX_TIMEOUT;

  RAIL_YieldRadio(connectRailHandle);

  STACK_WAKEUP_ISR_HANDLER;
}

static void initDoneCallback(RAIL_Handle_t railHandle)
{
  emLowerMacState = EMBER_MAC_STATE_IDLE;

  setInternalFlag(FLAG_IDLE_PENDING, true);
}

extern void halInternalAssertFailed(const char* filename, int linenumber);

void RAILCb_AssertFailed(RAIL_Handle_t railHandle, uint32_t errorCode)
{
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_ASSERT, errorCode);

  halInternalAssertFailed("librail.a", errorCode);
}

static void RAILCb_TimerExpired(void* params)
{
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SYMBOL_TIMER, 2);

  LOWER_MAC_ASSERT(getInternalFlag(FLAG_SYMBOL_TIMER_RUNNING));

  setInternalFlag(FLAG_SYMBOL_TIMER_RUNNING, false);

  sl_mac_symbol_timer_expired_handler_isr(0);

  STACK_WAKEUP_ISR_HANDLER;
}

static void dataRequestCommandCallback(RAIL_Handle_t railHandle)
{
  RAIL_IEEE802154_Address_t address;
#ifdef EMBER_STACK_CONNECT
  EmberMacAddress sourceAddr;
#endif

  // We could end up with the frame pending flags set and not consumed by a
  // subsequent RX of a data poll if the RX fails. We clear both flags here to
  // make sure the frame pending bit for the next data poll is set correctly.
  setInternalFlag(FLAG_DATA_POLL_FRAME_PENDING_SET, false);

  if (RAIL_IEEE802154_GetAddress(railHandle, &address)
      == RAIL_STATUS_NO_ERROR) {
#ifdef EMBER_STACK_CONNECT
    if (address.length == RAIL_IEEE802154_ShortAddress) {
      sourceAddr.mode = EMBER_MAC_ADDRESS_MODE_SHORT;
      sourceAddr.addr.shortAddress = address.shortAddress;
    } else if (address.length == RAIL_IEEE802154_LongAddress) {
      sourceAddr.mode = EMBER_MAC_ADDRESS_MODE_LONG;
      MEMCOPY(sourceAddr.addr.longAddress, address.longAddress, EUI64_SIZE);
    } else {
      sourceAddr.mode = EMBER_MAC_ADDRESS_MODE_NONE;
    }

    if (emMacGetFramePendingByAddress(&sourceAddr)) {
      if (RAIL_IEEE802154_SetFramePending(railHandle) == SL_STATUS_OK) {
        setInternalFlag(FLAG_DATA_POLL_FRAME_PENDING_SET, true);
      }
    } else {
    }
#else
    bool pending = false;
    if (address.length == RAIL_IEEE802154_ShortAddress) {
        #define MAX_EXPECTED_BYTES (1U + 2U + 1U + 2U) // PHR, FCF, seq, DstPan
        #define PAN_ID_START_IDX 4
      SL_MAC_MULTI_PAN_CODE({
        //  get the rail info struct
        RAIL_RxPacketInfo_t packetInfo;
        uint8_t pkt[MAX_EXPECTED_BYTES];
        RAIL_GetRxIncomingPacketInfo(railHandle, &packetInfo);
        if (packetInfo.packetBytes < MAX_EXPECTED_BYTES) {
          return;
        }
        // extract what we are interested in
        packetInfo.packetBytes = MAX_EXPECTED_BYTES;
        if (packetInfo.firstPortionBytes >= MAX_EXPECTED_BYTES) {
          packetInfo.firstPortionBytes = MAX_EXPECTED_BYTES;
          packetInfo.lastPortionData = NULL;
        }
        // copy the packet from the rx buffer
        RAIL_CopyRxPacket(pkt, &packetInfo);
        // extract pan id
        uint16_t panId = HIGH_LOW_TO_INT(pkt[PAN_ID_START_IDX + 1],
                                         pkt[PAN_ID_START_IDX]);
        // lookup the nwk index for current channel / mac index 0
        uint8_t nwk_index = sl_mac_get_nwk_index_matching_pan(0,
                                                              currentRadioChannel,
                                                              panId);
        // NOTE: nwk index might return 0xff, but we know it matches at least one
        //       of the nwks
        if (nwk_index == 0xFF) {
          // if we didn't match the pan id it's probably a broadcast data req
          // we'll use the "current" index to handle the data poll
          nwk_index = sl_mac_get_current_radio_network_index(0);
        }
        // push the child table pointer
        if (sli_mac_push_child_table_pointer(nwk_index) != SL_STATUS_OK) {
          return;
        }
      });

      // find the child index in the correct table
      uint8_t child_index = sl_mac_child_index(address.shortAddress);
      //  set pending flag
      pending = (child_index == 0xFF) // unknown child, set frame pending to send a leave
                || sl_mac_child_has_pending_message(child_index);
      sli_mac_pop_child_table_pointer();
    } else if (address.length == RAIL_IEEE802154_LongAddress) {
      pending = sl_mac_long_id_data_pending(address.longAddress);
    }

    if (pending ) {
      if (RAIL_IEEE802154_SetFramePending(railHandle) == SL_STATUS_OK) {
        setInternalFlag(FLAG_DATA_POLL_FRAME_PENDING_SET, true);
      }
    } else {
    }

#endif
  }
}

static void schedulerEventCallback(RAIL_Handle_t railHandle)
{
  switch (RAIL_GetSchedulerStatus(railHandle)) {
    case RAIL_SCHEDULER_STATUS_SCHEDULE_FAIL:
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SCHEDULER_EVENT, 0);
      // We were in the process of TXing an ACK, failed now.
      if (getInternalFlag(FLAG_ONGOING_TX_ACK)) {
        //DMM: How can this error happen for an ACK, which isn't scheduled??
        (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_ABORTED,
                               (uint32_t) isReceivingFrame());
        txFailedCallback(true, 0xFF);
      }
      // We were in the process of TXing a data frame, treat it as a CCA_FAIL.
      if (getInternalFlag(FLAG_ONGOING_TX_DATA)) {
        (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_BLOCKED,
                               (uint32_t) (emLowerMacState
                                           == EMBER_MAC_STATE_TX_WAITING_FOR_ACK));
        txFailedCallback(false, TX_COMPLETE_RESULT_CCA_FAIL);
      }
      break;
    case RAIL_SCHEDULER_STATUS_EVENT_INTERRUPTED:
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SCHEDULER_EVENT, 1);
      // We were in the process of TXing an ACK, failed now.
      if (getInternalFlag(FLAG_ONGOING_TX_ACK)) {
        (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_ABORTED,
                               (uint32_t) isReceivingFrame());
        txFailedCallback(true, 0xFF);
      }
      // We were in the process of TXing a data frame, which got pre-empted by
      // a higher priority task. Treat this as a OTHER_FAIL assuming some
      // portion of it might have gotten on-air.
      if (getInternalFlag(FLAG_ONGOING_TX_DATA)) {
        (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ABORTED,
                               (uint32_t) (emLowerMacState
                                           == EMBER_MAC_STATE_TX_WAITING_FOR_ACK));
        txFailedCallback(false, TX_COMPLETE_RESULT_CCA_FAIL);
      }
      break;
    case RAIL_SCHEDULER_STATUS_NO_ERROR:
    case RAIL_SCHEDULER_STATUS_UNSUPPORTED:
    case RAIL_SCHEDULER_STATUS_CCA_CSMA_TX_FAIL:
    case RAIL_SCHEDULER_STATUS_CCA_LBT_TX_FAIL:
    case RAIL_SCHEDULER_STATUS_SINGLE_TX_FAIL:
    case RAIL_SCHEDULER_STATUS_SCHEDULED_TX_FAIL:
    case RAIL_SCHEDULER_STATUS_SCHEDULED_RX_FAIL:
    case RAIL_SCHEDULER_STATUS_INTERNAL_ERROR:
    default:
      // Unexpected statuses for the scheduler event in our protocol
      LOWER_MAC_ASSERT(false);
      break;
  }
}

static void configUnscheduledCallback(void)
{
  // We are waiting for an ACK: we will never get the ACK we were waiting for.
  // We want to call ackTimeoutCallback() only if the PACKET_SENT event
  // already fired (which would clear the FLAG_ONGOING_TX_DATA flag).
  if (getInternalFlag(FLAG_WAITING_FOR_ACK)) {
    ackTimeoutCallback();
  }

  // We are about to send an ACK, which it won't happen.
  if (getInternalFlag(FLAG_ONGOING_TX_ACK)) {
    txFailedCallback(true, 0xFF);
  }
}

static void railCallbackHandler(RAIL_Handle_t railHandle, RAIL_Events_t events)
{
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_RAIL_EVENTS,
                             (uint64_t)events);
#if     SLI_COEX_SUPPORTED
  if (events & (RAIL_EVENT_RX_SYNC1_DETECT | RAIL_EVENT_RX_SYNC2_DETECT)) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_STARTED,
                           (uint32_t) isReceivingFrame());
  }
  if (events & RAIL_EVENT_SIGNAL_DETECTED) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_SIGNAL_DETECTED, 0U);
  }
#endif//SLI_COEX_SUPPORTED

  if ((events & RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND)
     #if     SLI_COEX_SUPPORTED
      && !RAIL_IsRxAutoAckPaused(railHandle)
     #endif//SLI_COEX_SUPPORTED
      ) {
    dataRequestCommandCallback(railHandle);
  }

#if     SLI_COEX_SUPPORTED
  if (events & RAIL_EVENT_RX_FILTER_PASSED) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACCEPTED,
                           (uint32_t) isReceivingFrame());
  }
#endif//SLI_COEX_SUPPORTED

  if (events & RAIL_EVENT_TX_PACKET_SENT) {
    packetSentCallback(false);
  } else
  if (events & RAIL_EVENT_TX_CHANNEL_BUSY) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_BLOCKED,
                           (uint32_t) (emLowerMacState
                                       == EMBER_MAC_STATE_TX_WAITING_FOR_ACK));
    txFailedCallback(false, TX_COMPLETE_RESULT_CCA_FAIL);
  } else
  if (events & RAIL_EVENT_TX_BLOCKED) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_BLOCKED,
                           (uint32_t) (emLowerMacState
                                       == EMBER_MAC_STATE_TX_WAITING_FOR_ACK));
    txFailedCallback(false, TX_COMPLETE_RESULT_OTHER_FAIL);
  } else
  if (events & (RAIL_EVENT_TX_UNDERFLOW | RAIL_EVENT_TX_ABORTED)) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ABORTED,
                           (uint32_t) (emLowerMacState
                                       == EMBER_MAC_STATE_TX_WAITING_FOR_ACK));
    txFailedCallback(false, TX_COMPLETE_RESULT_OTHER_FAIL);
  } else {
    // Pre-completion events are processed in their logical order:
#if     SLI_COEX_SUPPORTED
    if (events & RAIL_EVENT_TX_START_CCA) {
      // We are starting RXWARM for a CCA check
      (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_CCA_SOON, 0U);
    }
    if (events & RAIL_EVENT_TX_CCA_RETRY) {
      // We failed a CCA check and need to retry
      (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_CCA_BUSY, 0U);
    }
    if (events & RAIL_EVENT_TX_CHANNEL_CLEAR) {
      // We're going on-air
      (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_STARTED, 0U);
    }
#endif//SLI_COEX_SUPPORTED
  }

  if (events & RAIL_EVENT_RX_PACKET_RECEIVED) {
    packetReceivedCallback();
  }
#if     SLI_COEX_SUPPORTED
  if (events & RAIL_EVENT_RX_FRAME_ERROR) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_CORRUPTED,
                           (uint32_t) isReceivingFrame());
  }
  // The following 3 events cause us to not receive a packet
  if (events & (RAIL_EVENT_RX_PACKET_ABORTED
                | RAIL_EVENT_RX_ADDRESS_FILTERED
                | RAIL_EVENT_RX_FIFO_OVERFLOW)) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_FILTERED,
                           (uint32_t) isReceivingFrame());
  }
#endif//SLI_COEX_SUPPORTED
  if (events & RAIL_EVENT_TXACK_PACKET_SENT) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_SENT,
                           (uint32_t) isReceivingFrame());
    packetSentCallback(true);
  }
  if (events & (RAIL_EVENT_TXACK_ABORTED | RAIL_EVENT_TXACK_UNDERFLOW)) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_ABORTED,
                           (uint32_t) isReceivingFrame());
    txFailedCallback(true, 0xFF);
  }
  if (events & RAIL_EVENT_TXACK_BLOCKED) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_BLOCKED,
                           (uint32_t) isReceivingFrame());
    txFailedCallback(true, 0xFF);
  }

  // Deal with ACK timeout after possible RX completion in case RAIL
  // notifies us of the ACK and the timeout simultaneously -- we want
  // the ACK to win over the timeout.
  if (events & RAIL_EVENT_RX_ACK_TIMEOUT) {
    if (getInternalFlag(FLAG_WAITING_FOR_ACK)) {
      ackTimeoutCallback();
    }
  }

  if (events & RAIL_EVENT_CONFIG_UNSCHEDULED) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_IDLED, 0U);
    configUnscheduledCallback();
  }

#if     SLI_DMP_TUNING_SUPPORTED
  if (events & RAIL_EVENT_CONFIG_SCHEDULED) {
    // Application callback that user can sign up for
    emRadioConfigScheduledCallback(true);
  }
#endif//SLI_DMP_TUNING_SUPPORTED

  if (events & RAIL_EVENT_SCHEDULER_STATUS) {
    schedulerEventCallback(railHandle);
  }

  if (events & RAIL_EVENT_CAL_NEEDED) {
    setInternalFlag(FLAG_CALIBRATION_NEEDED, true);
  }

#ifdef CSL_SUPPORT
  // This is called by RAIL when our RX on has completed. Our duty cycle
  // dictates that we'll go idle now, but the radio could sleep, so we put a
  // timer in RAIL to wake up in some time. This scheduleRx call does *not*
  // interfere with the duty cycle
  // This is called when our duty cycle RX completes. This happens in two cases
  // a) we heard no wake up frame. Schedule a timer in mcsCslPeriodMs*1000 from
  //    now, so that we wake up
  // b) we heard a wake up frame. We canceled our duty cycling after we heard it
  //    and we turned on RX via RAIL_StartRx. Do nothing here if that's the case
  if (events & RAIL_EVENT_RX_CHANNEL_HOPPING_COMPLETE) {
    if (!wakeupFrameReceived) {
      radioScheduleRx(macCslPeriodMs * 1000, RAIL_TIME_DELAY, 0, 0);
    }
  }

  if (events & RAIL_EVENT_TX_FIFO_ALMOST_EMPTY) {
    fillTxFifoWithWakeupFrames();
  }
#endif // CSL_SUPPORT
}

#define DEFAULT_TX_POWER_DECI_DBM   0

#if defined(EMBER_TEST) || defined(EMBER_STACK_CONNECT)
static void railConfigChangedCallback(RAIL_Handle_t railHandle,
                                      const RAIL_ChannelConfigEntry_t *entry)
{
  bool isSubGHz = (entry->baseFrequency < 1000000000UL);
  RAIL_TxPowerConfig_t halPaConfig;
  RAIL_TxPowerConfig_t currentPaConfig;
  RAIL_TxPower_t currentTxPower;

  RAIL_GetTxPowerConfig(railHandle, &currentPaConfig);

  // RAIL_ConfigTxPower() wipes out the current TX power setting:
  // if RAIL_ConfigTxPower() was never called before, RAIL_GetTxPowerDbm() can
  // not be called, so in that case we set it to some default value. Otherwise
  // we get the current TX power level and set it again after we call
  // RAIL_ConfigTxPower().
  if (currentPaConfig.mode == RAIL_TX_POWER_MODE_NONE) {
    currentTxPower = DEFAULT_TX_POWER_DECI_DBM;
  } else {
    currentTxPower = RAIL_GetTxPowerDbm(railHandle);
  }

  if (isSubGHz) {
    halPaConfig = *halInternalPaSubGHzInit;
  } else {
    halPaConfig = *halInternalPa2p4GHzInit;
  }

  LOWER_MAC_ASSERT(RAIL_ConfigTxPower(railHandle, &halPaConfig)
                   == RAIL_STATUS_NO_ERROR);

  RAIL_SetTxPowerDbm(railHandle, currentTxPower);
}
#endif

// -----------------------------------------------------------------------------
// Other misc static functions.

static void radioSetIdle(void)
{
  // Ensure that radio state is not being changed during TX.
  LOWER_MAC_DEBUG_ASSERT_OUTGOING_PENDING(false, false);

  RAIL_YieldRadio(connectRailHandle);

  if (RAIL_GetRadioState(connectRailHandle) != RAIL_RF_STATE_IDLE) {
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SET_RADIO_STATE_IDLE, 0);
    RAIL_Idle(connectRailHandle, RAIL_IDLE_ABORT, true);
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_IDLED, 0U);
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_IDLED, 0U);
  }
}

static void radioSetRx(void)
{
  RAIL_SchedulerInfo_t rxSchedulerInfo = {
   #if     SLI_DMP_TUNING_SUPPORTED
    .priority = radioSchedulerPriorityTable.backgroundRx
   #else//!SLI_DMP_TUNING_SUPPORTED
    .priority = RADIO_SCHEDULER_BACKGROUND_RX_DEFAULT_PRIORITY
   #endif//SLI_DMP_TUNING_SUPPORTED
  };

  LOWER_MAC_DECLARE_INTERRUPT_STATE();

  // Ensure that radio state is not being changed during TX.
  LOWER_MAC_DEBUG_ASSERT_OUTGOING_PENDING(false, false);

  LOWER_MAC_DISABLE_INT();

  if (currentRadioChannel != currentChannel
      || RAIL_GetRadioState(connectRailHandle) == RAIL_RF_STATE_IDLE) {
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SET_RADIO_STATE_RX, 0);

    currentRadioChannel = currentChannel;

    LOWER_MAC_ASSERT(RAIL_StartRx(connectRailHandle,
                                  currentChannel,
                                  &rxSchedulerInfo) == RAIL_STATUS_NO_ERROR);
  }

  LOWER_MAC_RESTORE_INT();
}

#ifdef CSL_SUPPORT
static void radioScheduleRx(RAIL_Time_t startTime,
                            RAIL_TimeMode_t startMode,
                            uint8_t priority,
                            RAIL_Time_t endTime)
{
  RAIL_SchedulerInfo_t schedulerInfo = {
#if     SLI_DMP_TUNING_SUPPORTED
    .priority = radioSchedulerPriorityTable.activeRx,
#else//!SLI_DMP_TUNING_SUPPORTED
    .priority = RADIO_SCHEDULER_ACTIVE_RX_DEFAULT_PRIORITY,
#endif//SLI_DMP_TUNING_SUPPORTED
    .slipTime = 0,
    .transactionTime = 128
  };

  RAIL_ScheduleRxConfig_t rxSchedule = {
    .start = startTime,
    .startMode = RAIL_TIME_DELAY,
    .end = 0U,
    .endMode = RAIL_TIME_DISABLED,
    .rxTransitionEndSchedule = 0U,
    .hardWindowEnd = 0U
  };

  rxSchedule.start = startTime;
  rxSchedule.startMode = startMode;

  if (priority != 0xFF) {
    schedulerInfo.priority = priority;
  }

  if (endTime != 0) {
    rxSchedule.end = endTime;
    rxSchedule.endMode = RAIL_TIME_DELAY;
  }

  LOWER_MAC_DECLARE_INTERRUPT_STATE();

  // Ensure that radio state is not being changed during TX.
  LOWER_MAC_DEBUG_ASSERT_OUTGOING_PENDING(false, false);

  LOWER_MAC_DISABLE_INT();

  currentRadioChannel = currentChannel;

  // Idle the radio before calling RAIL_ScheduleRx
  RAIL_Idle(connectRailHandle, RAIL_IDLE_ABORT, true);

  LOWER_MAC_ASSERT(RAIL_ScheduleRx(connectRailHandle,
                                   currentRadioChannel,
                                   &rxSchedule,
                                   &schedulerInfo) == RAIL_STATUS_NO_ERROR);

  LOWER_MAC_RESTORE_INT();
}

// This function writes to a buffer the Rendezvous Time IE
uint8_t writeRendezvousIe(uint8_t* buffer)
{
  uint8_t* finger = buffer;
  // Header IE has format
  // length (bits 0-6) element ID (bits 7-14) type (bit 15) content ('length' bytes)
  uint16_t ieHeader = ((EMBER_802_15_4_IE_HEADER_LENGTH_RENDEZVOUS_TIME << EMBER_802_15_4_IE_HEADER_LENGTH_RENDEZVOUS_TIME_OFFSET)
                       | (EMBER_802_15_4_IE_HEADER_ELEMENT_ID_RENDEZVOUS_TIME << EMBER_802_15_4_IE_HEADER_ELEMENT_ID_RENDEZVOUS_TIME_OFFSET));
  emberStoreLowHighInt16u(finger, ieHeader);
  finger += 2;

  // -1 here because it's the time after this current frame transmits
  uint16_t symbolsUntilPayload = (totalWakeupFramesToSend - numWakeupFrameBeingSent - 1)
                                 * (TIME_BETWEEN_WAKEUP_FRAMES_IN_SYMBOLS + WAKEUP_FRAME_TX_TIME_IN_SYMBOLS);
  uint16_t rendezvousTimeInSymbols = symbolsUntilPayload / 10;  // Time until payload frame, in units of 10 symbols
  emberStoreLowHighInt16u(finger, rendezvousTimeInSymbols);
  finger += 2;
  uint16_t wakeupIntervalInSymbols = TIME_BETWEEN_WAKEUP_FRAMES_IN_SYMBOLS;
  emberStoreLowHighInt16u(finger, wakeupIntervalInSymbols);
  finger += 2;

  return (finger - buffer);
}

void createWakeupFrameFromPayload(uint8_t* payload)
{
  uint8_t* finger = wakeupFrame;

  // 15.4 defines multipurpose frames with a different frame control
  uint16_t frameControl = (EMBER_MAC_HEADER_FC_FRAME_TYPE_MULTIPURPOSE
                           | EMBER_MULTIPURPOSE_MAC_HEADER_FC_LONG_FRAME_CONTROL_BIT
                           | EMBER_MULTIPURPOSE_MAC_HEADER_FC_DEST_ADDR_MODE_SHORT
                           | EMBER_MULTIPURPOSE_MAC_HEADER_FC_SRC_ADDR_MODE_SHORT
                           | EMBER_MULTIPURPOSE_MAC_HEADER_FC_PAN_ID_PRESENT_BIT
                           | EMBER_MULTIPURPOSE_MAC_HEADER_FC_IE_PRESENT_BIT);
  uint16_t panId = sl_mac_flat_src_panid(payload, true);
  uint16_t dest = sl_mac_flat_dest_short_address(payload, true);
  uint16_t source = sl_mac_flat_src_short_address(payload, true);
  uint8_t bytesWritten;

  *finger = WAKEUP_FRAME_SIZE_BYTES_WITH_CRC - EMBER_PHY_HEADER_LENGTH; // length byte does not include length byte itself
  finger += 1;
  emberStoreLowHighInt16u(finger, frameControl);
  finger += 2;
  *finger = sli_mac_get_next_sequence();
  finger += 1;
  emberStoreLowHighInt16u(finger, panId);
  finger += 2;
  emberStoreLowHighInt16u(finger, dest);
  finger += 2;
  emberStoreLowHighInt16u(finger, source);
  finger += 2;
  bytesWritten = writeRendezvousIe(finger);
  finger += bytesWritten;
  // We do not need to allocate nor write the CRC bytes. RAIL takes care of that.
}

static void addPayloadFrameInFifo(void)
{
  if (!payloadFrameLoadedInTxFifo) {
    uint16_t bytesFreeInTxFifo = RAIL_GetTxFifoSpaceAvailable(connectRailHandle);
    uint16_t payloadFrameSize = sl_mac_flat_phy_packet_length(currentOutgoingPacket) - EMBER_PHY_CRC_LENGTH;
    if (bytesFreeInTxFifo >= payloadFrameSize) {
      uint16_t bytesWritten = RAIL_WriteTxFifo(connectRailHandle,
                                               currentOutgoingPacket,
                                               payloadFrameSize,
                                               false);

#ifndef LOWER_MAC_DEBUG
      (void)bytesWritten;
#else // LOWER_MAC_DEBUG
      LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_CSL_PAYLOAD_ADDED,
                                 bytesWritten);
#endif // LOWER_MAC_DEBUG

      payloadFrameLoadedInTxFifo = true;
    }
  }
}

static void addNextWakeupFrameInFifo(void)
{
  // The wakeup frame is already constructed. We just need to update mac
  // sequence and Rendezvous Time IE
  numWakeupFrameBeingSent++;
  wakeupFrame[EMBER_MULTIPURPOSE_MAC_HEADER_SEQUENCE_NUMBER_OFFSET] = sli_mac_get_next_sequence();
  (void)writeRendezvousIe(wakeupFrame + EMBER_MULTIPURPOSE_MAC_HEADER_IE_OFFSET);
  (void)RAIL_WriteTxFifo(connectRailHandle,
                         wakeupFrame,
                         WAKEUP_FRAME_SIZE_BYTES_NO_CRC,
                         false);
}

static void fillTxFifoWithWakeupFrames(void)
{
  if (!getInternalFlag(FLAG_CURRENT_TX_USE_WAKE_UP_FRAMES)) {
    return;
  }

  bool framesAdded = false;

  uint16_t bytesFreeInTxFifo = RAIL_GetTxFifoSpaceAvailable(connectRailHandle);
  while (bytesFreeInTxFifo > WAKEUP_FRAME_SIZE_BYTES_NO_CRC) {
    if (numWakeupFrameBeingSent == (totalWakeupFramesToSend - 1)) {
      break;
    }
    addNextWakeupFrameInFifo();
    bytesFreeInTxFifo -= WAKEUP_FRAME_SIZE_BYTES_NO_CRC;
    framesAdded = true;
  }

  if (framesAdded) {
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_CSL_LAST_WAKEUP_FRAME_ADDED,
                               numWakeupFrameBeingSent + 1);
  }

  // If we loaded all wakeup frames, try to load the payload frame, too. If the
  // TX FIFO doesn't have enough room, we'll try again when we get either the
  // RAIL_EVENT_TX_FIFO_ALMOST_EMPTY or RAIL_EVENT_TX_PACKET_SENT events
  if (numWakeupFrameBeingSent == (totalWakeupFramesToSend - 1)) {
    addPayloadFrameInFifo();
  }
}

static void addFirstWakeupFrameInFifo(uint8_t* payload)
{
  uint32_t usPerWakeupFrame = WAKEUP_FRAME_TX_TIME_IN_US + RADIO_IDLE_TIME_US;
  uint32_t macCslMaxPeriodUs = macCslMaxPeriodMs * 1000;
  totalWakeupFramesToSend = (macCslMaxPeriodUs / usPerWakeupFrame);
  numWakeupFrameBeingSent = 0;

  MEMSET(cslFrameFifo, 0x00, sizeof(cslFrameFifo));

  createWakeupFrameFromPayload(payload);

  MEMCOPY(cslFrameFifo, wakeupFrame, sizeof(wakeupFrame));

  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_CSL_LAST_WAKEUP_FRAME_ADDED,
                             numWakeupFrameBeingSent + 1);
}
#endif // CSL_SUPPORT

static RAIL_SchedulerInfo_t txSchedulerInfo = {
  .priority = RADIO_SCHEDULER_TX_DEFAULT_PRIORITY,
  .slipTime = 500000,
  .transactionTime = 0, // filled in later
};

// This is always called with interrupts disabled.

static void radioSetTx(uint8_t *dataPtr,
                       uint8_t dataLength,
                       uint16_t transactionTimeUs)
{
  RAIL_Status_t status;
  uint16_t txFifoSize;
  RAIL_TxOptions_t txOptions = RAIL_TX_OPTIONS_DEFAULT;
  bool ackRequested = ( (emMfglibMode != 0u) ? false : sl_mac_flat_ack_requested(dataPtr, true) );

#if     SLI_DMP_TUNING_SUPPORTED
  txSchedulerInfo.priority = radioSchedulerPriorityTable.tx;
#endif//SLI_DMP_TUNING_SUPPORTED
  txSchedulerInfo.transactionTime = transactionTimeUs;

  if (ackRequested) {
    txOptions |= RAIL_TX_OPTION_WAIT_FOR_ACK;
  }

#if     (SLI_ANTDIV_SUPPORTED && defined(RAIL_TX_OPTION_ANTENNA0))
  // Translate Tx antenna diversity mode into RAIL Tx Antenna options:
  // If enabled, use the currently-selected antenna, otherwise leave
  // both options 0 so Tx antenna tracks Rx antenna.
  if (sl_rail_util_ant_div_get_tx_antenna_mode() != SL_RAIL_UTIL_ANTENNA_MODE_DISABLED) {
    txOptions |= ((sl_rail_util_ant_div_get_tx_antenna_selected() == SL_RAIL_UTIL_ANTENNA_SELECT_ANTENNA1)
                  ? RAIL_TX_OPTION_ANTENNA0 : RAIL_TX_OPTION_ANTENNA1);
  }
#endif//(SLI_ANTDIV_SUPPORTED && defined(RAIL_TX_OPTION_ANTENNA0))

  // Ensure that radio state is not being changed during TX.
  LOWER_MAC_DEBUG_ASSERT_OUTGOING_PENDING(false, false);

  uint16_t txFifoLengthRequested = EMBER_PHY_MAX_PACKET_LENGTH;

#ifdef CSL_SUPPORT
  if (getInternalFlag(FLAG_CURRENT_TX_USE_WAKE_UP_FRAMES)) {
    addFirstWakeupFrameInFifo(dataPtr);

    // Hijack the buffer to send with a new buffer that contains a wake up frame
    dataPtr = cslFrameFifo;
    dataLength = WAKEUP_FRAME_SIZE_BYTES_NO_CRC;

    RAIL_TxRepeatConfig_t txRepeatConfig = {
      .iterations = totalWakeupFramesToSend,
      .repeatOptions = 0,
      .delayOrHop = RAIL_TRANSITION_TIME_KEEP
    };

    (void)RAIL_SetNextTxRepeat(connectRailHandle, &txRepeatConfig);

    txFifoLengthRequested = sizeof(cslFrameFifo);
  }
#endif // CSL_SUPPORT

  txFifoSize = RAIL_SetTxFifo(connectRailHandle,
                              dataPtr,
                              dataLength,
                              txFifoLengthRequested);

#ifndef LOWER_MAC_DEBUG
  (void)txFifoSize;
#else // LOWER_MAC_DEBUG
  LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SET_TX_FIFO,
                             txFifoSize);
#endif // LOWER_MAC_DEBUG

  currentRadioChannel = currentChannel;

#ifdef CSL_SUPPORT
  if (getInternalFlag(FLAG_CURRENT_TX_USE_WAKE_UP_FRAMES)) {
    cslPacketsSent = 0;
    payloadFrameLoadedInTxFifo = false;
    fillTxFifoWithWakeupFrames();
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_CSL_WAKEUP_FRAMES_ADDED,
                               numWakeupFrameBeingSent + 1);
  }
#endif // CSL_SUPPORT

  if (getInternalFlag(FLAG_CURRENT_TX_USE_CSMA)) {
    status = RAIL_StartCcaCsmaTx(connectRailHandle,
                                 currentRadioChannel,
                                 txOptions,
                                 &csmaParams,
                                 &txSchedulerInfo);

    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SET_RADIO_STATE_TX,
                               ackRequested
                               ? (((uint64_t)sl_mac_flat_sequence_number(dataPtr) << 32) | (0x11 | (status << 8)))
                               : (((uint64_t)sl_mac_flat_sequence_number(dataPtr) << 32) | (0x10 | (status << 8))));
  } else {
    status = RAIL_StartTx(connectRailHandle,
                          currentRadioChannel,
                          txOptions,
                          &txSchedulerInfo);
    if (status == RAIL_STATUS_NO_ERROR) {
      (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_STARTED, 0U);
    }

    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_SET_RADIO_STATE_TX,
                               ackRequested
                               ? (((uint64_t)sl_mac_flat_sequence_number(dataPtr) << 32) | (0x01 | (status << 8)))
                               : (((uint64_t)sl_mac_flat_sequence_number(dataPtr) << 32) | (0x00 | (status << 8))));
  }

#ifdef CSL_SUPPORT
  if ((status == RAIL_STATUS_NO_ERROR)
      && getInternalFlag(FLAG_CURRENT_TX_USE_WAKE_UP_FRAMES)) {
    // When sending  wake up frames, we tell RAIL to alert us when the TX FIFO
    // drops below a certain threshold, so that we can fill it up again with
    // more frames. The threshold is high here because we don't want interrupt
    // latency to happen and find out the FIFO is (now) empty, causing a
    // RAIL_EVENT_TX_UNDERFLOW error to occur
    uint16_t threshold = (uint16_t)(0.95 * txFifoSize);
    uint16_t txThreshold = RAIL_SetTxFifoThreshold(connectRailHandle, threshold);

#ifndef LOWER_MAC_DEBUG
    (void)txThreshold;
#else // LOWER_MAC_DEBUG
    LOWER_MAC_DEBUG_ADD_ACTION(LOWER_MAC_DEBUG_ACTION_CSL_TX_FIFO_THRESHOLD,
                               txThreshold);
#endif // LOWER_MAC_DEBUG
  }
#endif // CSL_SUPPORT

  if (status != RAIL_STATUS_NO_ERROR) {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_BLOCKED,
                           (uint32_t) ackRequested);
  }

  LOWER_MAC_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

static void radioIdle(void)
{
  LOWER_MAC_DECLARE_INTERRUPT_STATE();

  LOWER_MAC_ASSERT(sl_mac_lower_mac_is_idle(0));

  LOWER_MAC_DISABLE_INT();

  // Ongoing TX task, defer idling the radio.
  if (getInternalFlags(ONGOING_TX_FLAGS)) {
    setInternalFlag(FLAG_IDLE_PENDING, true);
    LOWER_MAC_RESTORE_INT();
    return;
  }

  setInternalFlag(FLAG_IDLE_PENDING, false);

  if (EMBER_RADIO_POWER_MODE_ED_ON != EMBER_RADIO_POWER_MODE_RX_ON) {
    // Neeeded because of a define in phy/phy.h (line 471)
    if (sl_mac_get_radio_idle_mode(0) == EMBER_RADIO_POWER_MODE_ED_ON) {
      rx_frame_detect_disable();

#ifndef EMBER_TEST
      radioPowerFem(true);
      halStackRadioPowerUpBoard();
#endif

      radioSetRx();
      LOWER_MAC_RESTORE_INT();
      return;
    }
  }

  switch (sl_mac_get_radio_idle_mode(0)) {
    case EMBER_RADIO_POWER_MODE_RX_ON:
      rx_frame_detect_enable();
      //Note: We may need to move the radio to Idle state, if a WF router
      //wants to move from duty cycled Rx to RX_ON_WHEN_IDLE state.
      //radioSetIdle();

#ifndef EMBER_TEST
      radioPowerFem(true);
      halStackRadioPowerUpBoard();
#endif
      radioSetRx();
      break;
    case EMBER_RADIO_POWER_MODE_OFF:
      radioSetIdle();
#ifndef EMBER_TEST
      halStackRadioPowerDownBoard();
      radioPowerFem(false);
#endif
      break;

#ifdef CSL_SUPPORT
    // TODO: right now make test uses base's phy/phy.h, which doesn't define
    // EMBER_RADIO_POWER_MODE_DC_RX; only mac-phy.h defines it.
    // Eventually zigbee will stop using base's phy.h and this should be
    // reverted
    case EMBER_RADIO_POWER_MODE_DC_RX:
      rx_frame_detect_enable();
      radioPowerFem(true);
      halStackRadioPowerUpBoard();
      radioScheduleRx(macCslPeriodMs * 1000, RAIL_TIME_DELAY, 0, 0);
      break;
#endif // CSL_SUPPORT

    default:
      LOWER_MAC_ASSERT(0);
  }

  LOWER_MAC_RESTORE_INT();
}

// This is always called with interrupts disabled.
static void txCurrentPacket(void)
{
#ifndef EMBER_TEST
  halStackIndicateActivity(true);
#endif
  uint16_t transactionTimeUs = 0;

  LOWER_MAC_ASSERT(getInternalFlag(FLAG_ONGOING_TX_DATA));

  LOWER_MAC_ASSERT(emLowerMacState == EMBER_MAC_STATE_TX_WAITING_FOR_ACK
                   || emLowerMacState == EMBER_MAC_STATE_TX_NO_ACK);

  LOWER_MAC_ASSERT(currentOutgoingPacket != NULL);

  if (getInternalFlag(FLAG_CURRENT_TX_USE_CSMA)) {
    transactionTimeUs += CSMA_OVERHEAD_US;
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_PENDED_PHY,
                           (uint32_t) true);
  } else {
    (void) onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_PENDED_PHY,
                           (uint32_t) false);
  }

  transactionTimeUs += sl_mac_get_bit_duration_us() * 8
                       * (EMBER_PHY_PREAMBLE_LENGTH
                          + EMBER_PHY_SFD_LENGTH
                          + EMBER_PHY_HEADER_LENGTH
                          + sl_mac_flat_phy_payload_length(currentOutgoingPacket)
                          + EMBER_PHY_CRC_LENGTH);

  if (emLowerMacState == EMBER_MAC_STATE_TX_WAITING_FOR_ACK) {
    transactionTimeUs +=
      EMBER_MAC_ACK_TURNAROUND_DELAY_SYMBOLS * sl_mac_get_symbol_duration_us()
      + (sl_mac_get_bit_duration_us() * 8
         * (EMBER_PHY_PREAMBLE_LENGTH
            + EMBER_PHY_SFD_LENGTH
            + EMBER_PHY_HEADER_LENGTH
            + 3
            + EMBER_PHY_CRC_LENGTH));
  }

  radioSetTx(currentOutgoingPacket,
             sl_mac_flat_phy_packet_length(currentOutgoingPacket) - EMBER_PHY_CRC_LENGTH,
             transactionTimeUs);

  LOWER_MAC_DEBUG_ASSERT_OUTGOING_PENDING(false, false);
  LOWER_MAC_DEBUG_SET_OUTGOING_PENDING(true, false);
  LOWER_MAC_DEBUG_START_TX_SENT_TIMER(true);

#ifndef EMBER_TEST
  halStackIndicateActivity(false);
#endif
}

static void txCompleted(sl_status_t status)
{
#ifdef EMBER_STACK_CONNECT
  int8_t savedAckRssi = ackReceivedRssi;
#endif

  radioIdle();
  #ifdef EMBER_STACK_CONNECT
  emNotifyMacIsIdle(0);
  #else
  //sl_mac_notify_mac_is_idle(0);
  //move to after the callback
  #endif

#ifdef EMBER_STACK_CONNECT
  emLowerMacPacketSendCompleteCallback(status, savedAckRssi, currentOutgoingPacket);
#else
  sl_mac_packet_send_complete_callback(0, status);
  sl_mac_notify_mac_is_idle(0);
#endif
}

// Called in main-line context (never ISR context) before the PHY actually
// powers up the radio for Rx or Tx and after the PHY has powered it down.
#ifndef EMBER_TEST
static void radioPowerFem(bool powerUp)
{
  // Only notify the HAL when preparing to power up from OFF
  // or after having really powered down, and such notification
  // is not redundant.
  static bool femPowered = false;
  if ((sl_mac_get_radio_idle_mode(0) == EMBER_RADIO_POWER_MODE_OFF)
      && (powerUp != femPowered)) {
    femPowered = powerUp;
    halStackRadioPowerMainControl(powerUp);
  }
}
#endif

static void setInternalFlag(uint16_t flag, bool val)
{
  LOWER_MAC_DECLARE_INTERRUPT_STATE();

  LOWER_MAC_DISABLE_INT();

  if (val) {
    miscInternalFlags |= flag;
  } else {
    miscInternalFlags &= ~flag;
  }

  LOWER_MAC_RESTORE_INT();
}

static bool getInternalFlag(uint16_t flag)
{
  return ((miscInternalFlags & flag) != 0);
}

static bool currentOutgoingPacketIsDataRequest(void)
{
  LOWER_MAC_ASSERT(currentOutgoingPacket != NULL);

  return ((sl_mac_flat_frame_type(currentOutgoingPacket, true)
           == EMBER_MAC_HEADER_FC_FRAME_TYPE_COMMAND)
          && (sl_mac_flat_payload(currentOutgoingPacket, true)[EMBER_MAC_PAYLOAD_COMMAND_ID_OFFSET]
              == MAC_DATA_REQUEST));
}

#ifndef EMBER_STACK_CONNECT
#define PHY_MIN_RSSI -100
#define PHY_MIN_RSSI_ED (PHY_MIN_RSSI + 10) // 15.4: 10 dB above sensitivity
#define PHY_MAX_RSSI -36
#define PHY_MAX_ED   0xff
#define PHY_MAX_LQI  0xff

// No casts in this macro so it can be used for constant expressions
// Here rssi must be >= PHY_MIN_RSSI and < PHY_MAX_RSSI for a valid result
#define RSSI_TO_LQI(rssi) ((((rssi) - PHY_MIN_RSSI) * 256) \
                           / (PHY_MAX_RSSI - PHY_MIN_RSSI))
#define RSSI_TO_ED(rssi) ((((rssi) - PHY_MIN_RSSI_ED) * 256) \
                          / (PHY_MAX_RSSI - PHY_MIN_RSSI_ED))

// For EFR32, the RSSI range of [-100..-36] is mapped to an LQI range [0..255].
// These values are chosen in part to be compatible with EM35x divisions.
// Those were chosen too close together because of the very narrow dBm range of
// LQI values on that chip. These are spread apart more because that is
// better for differentiating link qualities, but not so much as to create
// a dramatic interoperability difference.
static uint8_t emCostDivisions[] = {
//          >=RSSI                LQI  index  cost
//            ----                ---  -----  ----
  RSSI_TO_LQI(-80),          // =  80    0      1
  RSSI_TO_LQI(-84),          // =  64    1      3
  RSSI_TO_LQI(-88),          // =  48    2      5
  RSSI_TO_LQI(PHY_MIN_RSSI), // =   0    3      7
};

void emSetCostDivisions(const uint8_t *costDivisions)
{
  MEMCOPY(emCostDivisions, costDivisions, sizeof(uint8_t) * 4);
}

uint8_t emCostDivision(uint8_t cost)
{
  return emCostDivisions[(cost >> 1)];
}

static uint8_t convertRssiToLqi(uint8_t lqi, int8_t rssiDbm)
{
  UNUSED_VAR(lqi);
  // Following non zero -RAIL_GetRssiOffset() would increase the RSSI value to map to better lqi values
  // Since it shows RAIL_SetRssiOffset() has been used to correct the RSSI values to be lower for CCA (IOTREQ-1434, RAIL_LIB-3457)
  // range check should have been already done
  int16_t offsettedRssiDbm =  (int16_t)(rssiDbm - RAIL_GetRssiOffset(RAIL_EFR32_HANDLE) - RAIL_GetRssiOffset(connectRailHandle));
  // Enforce Limits
  if (offsettedRssiDbm <= PHY_MIN_RSSI) {
    return 0;
  }
  if (offsettedRssiDbm >= PHY_MAX_RSSI ) {
    return PHY_MAX_LQI;
  }

  return (uint8_t) RSSI_TO_LQI(offsettedRssiDbm);
}
#endif

void sl_mac_lower_mac_set_eui64(uint8_t mac_index, uint8_t addr_filter_index, EmberEUI64 eui64)
{
  UNUSED_VAR(mac_index);
  LOWER_MAC_ASSERT(RAIL_IEEE802154_SetLongAddress(connectRailHandle,
                                                  eui64,
                                                  addr_filter_index)
                   == RAIL_STATUS_NO_ERROR);
}

// stub for zigbee for now
void emRadioInit(RadioPowerMode initialRadioPowerMode)
{
  UNUSED_VAR(initialRadioPowerMode);
}

bool sl_mac_lower_mac_radio_is_on(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  return !(RAIL_GetRadioState(connectRailHandle) == RAIL_RF_STATE_IDLE);
}

bool emRadioGetRandomNumbers(uint16_t *rn, uint8_t count)
{
  uint16_t countBytes = count * sizeof(uint16_t);

  // Collect entropy from the radio over the air. This should be good enough
  // to be used directly as a random number according to the hardware team.
  if (RAIL_GetRadioEntropy(connectRailHandle, (uint8_t*)rn, countBytes) != countBytes) {
    return false;
  }

  return true;
}

#ifndef EMBER_STACK_CONNECT
const uint8_t generated_irCalConfig[] = {
  24, 63, 1, 6, 4, 16, 1, 0, 0, 1, 1, 6, 0, 16, 39, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0
};

const uint32_t generated_phyInfo[] = {
  1UL,
  0x00618618, // 97.5238095238
  (uint32_t) NULL,
#ifndef EMBER_TEST
  (uint32_t) generated_irCalConfig,
#else
  (uint32_t) NULL,
#endif
#ifdef RADIO_CONFIG_ENABLE_TIMING
  (uint32_t) &generated_timing,
#else
  (uint32_t) NULL,
#endif
};

const uint32_t generated[] = {
  0x01031FF0UL, 0x0037003FUL,
  /* 1FF4 */ 0x00000000UL,
  #ifndef EMBER_TEST
  /* 1FF8 */ (uint32_t) generated_phyInfo,
  #else
  (uint32_t) NULL,
  #endif
  0x00020004UL, 0x00157001UL,
  /* 0008 */ 0x0000007FUL,
  0x00020018UL, 0x00000000UL,
  /* 001C */ 0x00000000UL,
  0x00070028UL, 0x00000000UL,
  /* 002C */ 0x00000000UL,
  /* 0030 */ 0x00000000UL,
  /* 0034 */ 0x00000000UL,
  /* 0038 */ 0x00000000UL,
  /* 003C */ 0x00000000UL,
  /* 0040 */ 0x000007A0UL,
  0x00010048UL, 0x00000000UL,
  0x00020054UL, 0x00000000UL,
  /* 0058 */ 0x00000000UL,
  0x000400A0UL, 0x00004000UL,
  /* 00A4 */ 0x00004CFFUL,
  /* 00A8 */ 0x00004100UL,
  /* 00AC */ 0x00004DFFUL,
  0x00012000UL, 0x00000704UL,
  0x00012010UL, 0x00000000UL,
  0x00012018UL, 0x00008408UL,
  0x00013008UL, 0x0100AC13UL,
  0x00023030UL, 0x00106147UL,
  /* 3034 */ 0x00000001UL,
  0x00013040UL, 0x00000000UL,
  0x000140A0UL, 0x0F00277AUL,
  0x000140B8UL, 0x00E3C000UL,
  0x000140F4UL, 0x00001020UL,
  0x00024134UL, 0x00000880UL,
  /* 4138 */ 0x000087E6UL,
  0x00024140UL, 0x0088008FUL,
  /* 4144 */ 0x4D52E6C0UL,
  0x00044160UL, 0x00000000UL,
  /* 4164 */ 0x00000000UL,
  /* 4168 */ 0x00000006UL,
  /* 416C */ 0x00000006UL,
  0x00086014UL, 0x00000010UL,
  /* 6018 */ 0x0413F920UL,
  /* 601C */ 0x00520007UL,
  /* 6020 */ 0x000000C8UL,
  /* 6024 */ 0x00000000UL,
  /* 6028 */ 0x03000000UL,
  /* 602C */ 0x00000000UL,
  /* 6030 */ 0x00000000UL,
  0x00066050UL, 0x00FF0264UL,
  /* 6054 */ 0x00000C41UL,
  /* 6058 */ 0x00000000UL,
  /* 605C */ 0x000807B0UL,
  /* 6060 */ 0x000000A7UL,
  /* 6064 */ 0x00000000UL,
  0x000C6078UL, 0x08E00141UL,
  /* 607C */ 0x744AC39BUL,
  /* 6080 */ 0x000003F0UL,
  /* 6084 */ 0x01959000UL,
  /* 6088 */ 0x00000001UL,
  /* 608C */ 0x30100101UL,
  /* 6090 */ 0x7F7F7050UL,
  /* 6094 */ 0x00000000UL,
  /* 6098 */ 0x00000000UL,
  /* 609C */ 0x00000000UL,
  /* 60A0 */ 0x00000000UL,
  /* 60A4 */ 0x00000000UL,
  0x000760E4UL, 0x8BA80080UL,
  /* 60E8 */ 0x00000000UL,
  /* 60EC */ 0x07830464UL,
  /* 60F0 */ 0x3AC81388UL,
  /* 60F4 */ 0x0006209CUL,
  /* 60F8 */ 0x00206100UL,
  /* 60FC */ 0x208556B7UL,
  0x00036104UL, 0x001247A9UL,
  /* 6108 */ 0x00003020UL,
  /* 610C */ 0x0000BB88UL,
  0x00016120UL, 0x00000000UL,
  0x00086130UL, 0x00FA53E8UL,
  /* 6134 */ 0x00000000UL,
  /* 6138 */ 0x00000000UL,
  /* 613C */ 0x00000000UL,
  /* 6140 */ 0x00000000UL,
  /* 6144 */ 0x00000000UL,
  /* 6148 */ 0x00000000UL,
  /* 614C */ 0x00000001UL,
  0x00067014UL, 0x000270FAUL,
  /* 7018 */ 0x00001800UL,
  /* 701C */ 0x850A0000UL,
  /* 7020 */ 0x00000000UL,
  /* 7024 */ 0x00000082UL,
  /* 7028 */ 0x01800000UL,
  0x00027048UL, 0x00003D3CUL,
  /* 704C */ 0x000019BCUL,
  0x00037070UL, 0x00220103UL,
  /* 7074 */ 0x00083007UL,
  /* 7078 */ 0x00552300UL,

  0xFFFFFFFFUL,
};

RAIL_ChannelConfigEntryAttr_t generated_entryAttr = {
  { 0xFFFFFFFFUL }
};

const RAIL_ChannelConfigEntry_t generated_channels[] = {
  {
    .phyConfigDeltaAdd = NULL,
    .baseFrequency = 2405000000,
    .channelSpacing = 5000000,
    .physicalChannelOffset = 0,
    .channelNumberStart = 11,
    .channelNumberEnd = 26,
    .maxPower = RAIL_TX_POWER_MAX,
    .attr = &generated_entryAttr
  },
};

const RAIL_ChannelConfig_t generated_channelConfig = {
  generated,
  NULL,
  generated_channels,
  1
};
const RAIL_ChannelConfig_t *channelConfigs[] = {
  &generated_channelConfig,
  NULL
};
#endif

EmberStatus emberForceTxAfterFailedCca(uint8_t csmaAttempts)
{
  if (csmaAttempts > FORCE_TX_AFTER_FAILED_CCA_ATTEMPTS_LIMIT) {
    return EMBER_BAD_ARGUMENT;
  }

  default_force_tx_after_failed_cca_attempts = csmaAttempts;
  return EMBER_SUCCESS;
}

//temporary workaround until Andrew's changes to this are merged here
bool emRadioCheckRadio(void)
{
  // EFR32 calibration events are: IRCal and tempcal
  // RAIL Cal requests update the stack via pending bits
  // (RAILCb_CalNeeded callback fires also)
  //return RAIL_GetPendingCal(connectRailHandle);
  return false;
}

//-----mfglib

//------------------------------------------------------------------------------
// Diagnostic Transmit APIs
//-------------------------

void sl_mac_lower_mac_start_transmit_stream(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  (void)RAIL_StartTxStream(connectRailHandle, currentChannel, RAIL_STREAM_PN9_STREAM);
}

void sl_mac_lower_mac_stop_transmit_stream(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  (void)RAIL_StopTxStream(connectRailHandle);
}

void sl_mac_lower_mac_start_transmit_tone(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  (void)RAIL_StartTxStream(connectRailHandle, currentChannel, RAIL_STREAM_CARRIER_WAVE);
}

void sl_mac_lower_mac_stop_transmit_tone(uint8_t mac_index)
{
  UNUSED_VAR(mac_index);
  (void)RAIL_StopTxStream(connectRailHandle);
}

uint8_t sl_mac_lower_mac_convert_rssi_to_ed(uint8_t mac_index, int8_t rssi)
{
  UNUSED_VAR(mac_index);
  return RAIL_IEEE802154_ConvertRssiToEd(rssi);
}
//------------------------------------------------------------------------------
// Address and Filtering APIs
//---------------------------
static bool addressMatchingEnabled = true;

void emRadioEnableAddressMatching(uint8_t enable)
{
  if (getInternalFlag(FLAG_RADIO_INIT_DONE)) {
    RAIL_IEEE802154_SetPromiscuousMode(connectRailHandle,
                                       !enable);
  } else {
    // Do not defer to emRadioInit() time
    return;
  }
  addressMatchingEnabled = (bool) enable;
}

uint8_t emRadioAddressMatchingEnabled(void)
{
  return (uint8_t) addressMatchingEnabled;
}

static bool autoAckEnabled = true;

void emRadioEnableAutoAck(bool enable)
{
  LOWER_MAC_DECLARE_INTERRUPT_STATE();
  LOWER_MAC_DISABLE_INT(); // Protect against emRadioHoldOffIsr() while changing Radio config
  autoAckEnabled = enable;
  if (getInternalFlag(FLAG_RADIO_INIT_DONE)) {
    #if     SLI_COEX_SUPPORTED
    if ((rhoActive >= RHO_INT_ACTIVE) // Internal always holds ACKs
        || ((rhoActive > RHO_INACTIVE)
            && ((sl_rail_util_coex_get_options()
                 & SL_RAIL_UTIL_COEX_OPT_ACK_HOLDOFF)
                != SL_RAIL_UTIL_COEX_OPT_DISABLED))) {
      RAIL_PauseRxAutoAck(connectRailHandle, true);
    } else
    #endif
    {
      RAIL_PauseRxAutoAck(connectRailHandle, !autoAckEnabled);
    }
  }
  LOWER_MAC_RESTORE_INT();
}

bool emRadioAutoAckEnabled(void)
{
  return autoAckEnabled;
}

//----end of mfglib calls

#ifdef EMBER_TEST
volatile bool emMfglibTransmitComplete = false; //mfglib

uint16_t emGetTxPowerMode(void)
{
  //mfglib
  return 0;
}

bool emRadioPacketTraceEnabled(void)
{
  //zigbee-pro-stack-alt-mac, alternate-mac
  return false;
}

#endif // EMBER_TEST

EmberStatus emberSetTxPowerMode(uint16_t txPowerMode)
{
  //af-main-soc
  return SL_STATUS_OK;
}

//zigbee stubs : ToDo: need sto be removed after we figure out what to do with mfglib
void (*emMfglibRxCallback)(uint8_t *packet, uint8_t linkQuality, int8_t rssi) = NULL;

// Temporary stub invoked in diagnostic.c from legacy hal.
SL_WEAK void emRadioSleep(void)
{
}

// -----------------------------------------------------------------------------
// Coex RHO/PTA support

#ifndef ED_CCA_THRESHOLD_UNINIT
#define ED_CCA_THRESHOLD_UNINIT 127
#endif//ED_CCA_THRESHOLD_UNINIT

static int8_t edCcaThreshold = ED_CCA_THRESHOLD_UNINIT;

static void setEdCcaThreshold(int8_t thresholddBm)
{
  if (thresholddBm == ED_CCA_THRESHOLD_UNINIT) {
   #ifdef  EMBER_STACK_CONNECT
    thresholddBm = emRadioCcaThreshold;
   #else//!EMBER_STACK_CONNECT
    // The first time setEdCcaThreshold() is called we use the
    // CCA_THRESHOLD mfg token, if present, else we use the default.
    // Subsequent calls to setEdCcaThreshold will ignore the
    // token/default value and use whatever value the user passes in.
    tokTypeMfgCcaThreshold ccaThresholdToken = 0xFFFF; // Assume unset
    thresholddBm = ED_CCA_THRESHOLD;
    halCommonGetMfgToken(&ccaThresholdToken, TOKEN_MFG_CCA_THRESHOLD);
    // The format of this token is now (per RAIL_LIB-1373):
    // uint8_t ccaThresholdSubNeg     : 7, // bits <15:9> unsigned but negated
    // bool    ccaThreshold2p4Invalid : 1, // bit  <8> 1=invalid 0=valid
    // int8_t  ccaThreshold2p4        : 8, // bits <7:0> signed 2's complement
    // where:
    // ccaThresholdSubNeg is 7-bit unsigned value where values 0 and 127
    //   both mean "use default" (which is what allows us to jimmy SubGHz
    //   CCA threshold oonfiguration into this pre-existing token), and
    //   values 1..126 are negated to map to -1..-126 dBm, respectively.
    // ccaThreshold2p4Invalid indicates whether ccaThreshold2p4 is valid;
    // ccaThreshold2p4 is the actual signed 2's complement CCA threshold;
    // This PHY can support both SubGHz and 2.4GHz thresholds:
    if ((0x0100U & ccaThresholdToken) == 0U) {
      // The lsb of the high byte has been cleared.
      // Interpret the low byte as the CCA threshold.
      thresholddBm = (int8_t)(ccaThresholdToken & 0x00FFU);
    }
   #endif//EMBER_STACK_CONNECT
  }
 #if     SLI_COEX_SUPPORTED
  {
    LOWER_MAC_DECLARE_INTERRUPT_STATE();
    LOWER_MAC_DISABLE_INT(); // Protect against emRadioHoldOffIsr() while changing Radio config
    edCcaThreshold = thresholddBm;

    if (getInternalFlag(FLAG_RADIO_INIT_DONE)) {
      if (rhoActive > RHO_INACTIVE) {
        thresholddBm = RAIL_RSSI_INVALID_DBM;
      }
      LOWER_MAC_ASSERT(RAIL_SetCcaThreshold(connectRailHandle, thresholddBm)
                       == RAIL_STATUS_NO_ERROR);
    } else {
      // Defer to lower-mac-init time
    }
    LOWER_MAC_RESTORE_INT();
  }
 #else//!SLI_COEX_SUPPORTED
  edCcaThreshold = thresholddBm;
 #endif//SLI_COEX_SUPPORTED
}

static int8_t getEdCcaThreshold(void)
{
  if (edCcaThreshold == ED_CCA_THRESHOLD_UNINIT) {
    setEdCcaThreshold(ED_CCA_THRESHOLD_UNINIT);
  }
  return edCcaThreshold;
}

int8_t sl_mac_get_ed_cca_threshold(void)
{
  return getEdCcaThreshold();
}

#if     SLI_COEX_SUPPORTED

static bool ptaGntEventReported;

static void onPtaGrantTx(sl_rail_util_coex_req_t ptaStatus)
{
  // Only pay attention to first PTA Grant callback, ignore any further ones
  if (ptaGntEventReported) {
    return; // This avoids EMZIGBEE-1347
  }
  ptaGntEventReported = true;

  LOWER_MAC_ASSERT(ptaStatus == SL_RAIL_UTIL_COEX_REQCB_GRANTED);
  // PTA is telling us we've gotten GRANT and should send ASAP *without* CSMA
  setInternalFlag(FLAG_CURRENT_TX_USE_CSMA, false);

  txCurrentPacket();
}

static void tryTxCurrentPacket(void)
{
  LOWER_MAC_ASSERT(getInternalFlag(FLAG_ONGOING_TX_DATA));
  LOWER_MAC_ASSERT(emLowerMacState == EMBER_MAC_STATE_TX_WAITING_FOR_ACK
                   || emLowerMacState == EMBER_MAC_STATE_TX_NO_ACK);
  LOWER_MAC_ASSERT(currentOutgoingPacket != NULL);

  ptaGntEventReported = false;
  sl_rail_util_ieee802154_stack_status_t ptaStatus =
    onPtaStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_PENDED_MAC,
                    (uint32_t) &onPtaGrantTx);
  if (ptaStatus == SL_RAIL_UTIL_IEEE802154_STACK_STATUS_SUCCESS) {
    // Normal case where PTA allows us to start the (CSMA) transmit below
    txCurrentPacket();
  } else if (ptaStatus == SL_RAIL_UTIL_IEEE802154_STACK_STATUS_CB_PENDING) {
    // onPtaGrantTx() callback will take over (and might already have)
  } else if (ptaStatus == SL_RAIL_UTIL_IEEE802154_STACK_STATUS_HOLDOFF) {
    // General concern about mac hold off: Before, without this mode,
    // a series of MAC packets queued up to send would each have to
    // exhaust their series of n CSMA backoffs and CCA attempts before
    // failing back to the NWK layer for retry. With this mode,
    // a series of MAC packets would all fail immediately, one right
    // after another, bing-bang-boom. I don't know how this will affect
    // the NWK layer's retry mechanism or overall network performance.
    //
    // Instead of calling radioTransmitCompleteCallback(), we only want
    // the subset that radioTransmitCompleteInternalCallback() provides
    // because the former assumes emPhyDcSendPktAsap() was called which
    // is not the case here.
    txFailedCallback(false, TX_COMPLETE_RESULT_OTHER_FAIL);
  }
}

static bool isReceivingFrame(void)
{
  return (RAIL_GetRadioState(connectRailHandle) & RAIL_RF_STATE_RX_ACTIVE)
         == RAIL_RF_STATE_RX_ACTIVE;
}

static void emRadioHoldOffInternalIsr(uint8_t active)
{
  if (active != rhoActive) {
    rhoActive = active; // Update rhoActive early
    if (getInternalFlag(FLAG_RADIO_INIT_DONE)) {
      setEdCcaThreshold(edCcaThreshold);
      emRadioEnableAutoAck(autoAckEnabled);
    } else {
      // Defer to lower-mac init time
    }
  }
}

// External APIs used by Coex Plugin

void emRadioHoldOffIsr(bool active)
{
  emRadioHoldOffInternalIsr((uint8_t) active | (rhoActive & ~RHO_EXT_ACTIVE));
}

static void changeDynamicEvents(void)
{
  // ActiveRx priority needs the following events:
  // - RX_SYNC1_DETECT     (not normally enabled; enable/disable here)
  // - RX_SYNC2_DETECT     (not normally enabled; enable/disable here)
  // - RX_FRAME_ERROR      (not normally enabled; enable/disable here)
  // - RX_FIFO_OVERFLOW    (not normally enabled; enable/disable here)
  // - RX_PACKET_ABORTED   (not normally enabled; enable/disable here)
  // - RX_ADDRESS_FILTERED (not normally enabled; enable/disable here)
  // - RX_PACKET_RECEIVED  (always enabled)
  //
  // Rx PTA needs the following events:
  // - RX_SYNC1_DETECT     (not normally enabled; enable/disable here)
  // - RX_SYNC2_DETECT     (not normally enabled; enable/disable here)
  // - RX_FRAME_ERROR      (not normally enabled; enable/disable here)
  // - RX_FIFO_OVERFLOW    (not normally enabled; enable/disable here)
  // - RX_PACKET_ABORTED   (not normally enabled; enable/disable here)
  // - RX_ADDRESS_FILTERED (not normally enabled; enable/disable here)
  // - RX_FILTER_PASSED    (not normally enabled; enable/disable here)
  // - RX_PACKET_RECEIVED  (always enabled)
  //
  // Tx PTA needs the following events:
  // - TX_START_CCA        (not normally enabled; enable/disable here)
  // - TX_CCA_RETRY        (not normally enabled; enable/disable here)
  // - TX_CHANNEL_CLEAR    (not normally enabled; enable/disable here)
  // - TX_CHANNEL_BUSY     (always enabled)
  // - TX_UNDERFLOW        (always enabled)
  // - TX_ABORTED          (always enabled)
  // - TX_BLOCKED          (always enabled)
  // - TX_PACKET_SENT      (always enabled)
  // - TXACK_UNDERFLOW     (always enabled)
  // - TXACK_ABORTED       (always enabled)
  // - TXACK_BLOCKED       (always enabled)
  // - TXACK_PACKET_SENT   (always enabled)
  //
  // Notice the RX and TX PTA events enabled/disabled here as a group are
  // a proper superset of all the other use cases; the code below assumes
  // this. Additionally, note that the events here are strictly mutually
  // exclusive with the events enabled in the call to updateEvents within
  // lower-mac init. This exclusivity must be maintained in order to not disable
  // events the the app wants on regardless of which features are enabled.
  const RAIL_Events_t eventMask = RAIL_EVENTS_NONE
                                  | RAIL_EVENT_RX_SYNC1_DETECT
                                  | RAIL_EVENT_RX_SYNC2_DETECT
                                  | RAIL_EVENT_RX_FRAME_ERROR
                                  | RAIL_EVENT_RX_FIFO_OVERFLOW
                                  | RAIL_EVENT_RX_ADDRESS_FILTERED
                                  | RAIL_EVENT_RX_PACKET_ABORTED
                                  | RAIL_EVENT_RX_FILTER_PASSED
                                  | RAIL_EVENT_TX_CHANNEL_CLEAR
                                  | RAIL_EVENT_TX_CCA_RETRY
                                  | RAIL_EVENT_TX_START_CCA
                                  | RAIL_EVENT_SIGNAL_DETECTED
  ;
  RAIL_Events_t eventValues = RAIL_EVENTS_NONE;

  if (sl_rail_util_coex_is_enabled()) {
    eventValues |= eventMask;
  }
 #if     SLI_DMP_TUNING_SUPPORTED
  else if (radioSchedulerPriorityTable.backgroundRx
           != radioSchedulerPriorityTable.activeRx) {
    eventValues |= (RAIL_EVENT_RX_SYNC1_DETECT
                    | RAIL_EVENT_RX_SYNC2_DETECT
                    | RAIL_EVENTS_RX_COMPLETION);
  } else {
    // Sate MISRA: Disable these events with eventValues == RAIL_EVENTS_NONE
  }
 #endif//SLI_DMP_TUNING_SUPPORTED
  updateEvents(eventMask, eventValues);
}

void emRadioEnablePta(bool enable)
{
  if (!getInternalFlag(FLAG_RADIO_INIT_DONE)) {
    return; // Defer to lower-mac init time
  }

  changeDynamicEvents();

  // When PTA is enabled, we want to negate PTA_REQ as soon as an incoming
  // frame is aborted, e.g. due to filtering.  To do that we must turn off
  // the TRACKABFRAME feature that's normally on to benefit sniffing on PTI.
  // That feature has the unfortunate side effect of delaying RXABORT
  // notification until the full packet has been received, even tho it
  // won't be processed.
  LOWER_MAC_ASSERT(RAIL_ConfigRxOptions(connectRailHandle,
                                        RAIL_RX_OPTION_TRACK_ABORTED_FRAMES,
                                        (enable
                                         ? RAIL_RX_OPTIONS_NONE
                                         : RAIL_RX_OPTION_TRACK_ABORTED_FRAMES))
                   == RAIL_STATUS_NO_ERROR);
}

uint8_t emPhyGetChannelPageInUse(void)
{
  return 0U; // This lower-MAC currently only supports 802.15.4 channel page 0
}

//This does not seem to be ever used, but since the status of coex testing is not clear,
//I replicate this here from pre-umac zigbee code
/*
 * Truth table
 * m=SL_RAIL_UTIL_COEX_OPT_MAC_HOLDOFF, f=SL_RAIL_UTIL_COEX_OPT_FORCE_HOLDOFF
 * mf
 * 00:EmMacTxMode = MAC_TX_MODE_NORMAL w/o force holdoff
 * 01:EmMacTxMode = MAC_TX_MODE_NORMAL w/force holdoff
 * 10:EmMacTxMode = MAC_TX_MODE_GRANT
 * 11:EmMacTxMode = MAC_TX_MODE_MAC_HO
 */
void emSetMacTxMode(EmMacTxMode txMode)
{
  if (txMode == MAC_TX_MODE_NORMAL) {
    sl_rail_util_coex_set_bool(SL_RAIL_UTIL_COEX_OPT_MAC_AND_FORCE_HOLDOFFS, false);
  } else if (txMode == MAC_TX_MODE_GRANT) {
    sl_rail_util_coex_set_bool(SL_RAIL_UTIL_COEX_OPT_MAC_HOLDOFF, true);
    sl_rail_util_coex_set_bool(SL_RAIL_UTIL_COEX_OPT_FORCE_HOLDOFF, false);
  } else if (txMode == MAC_TX_MODE_MAC_HO) {
    sl_rail_util_coex_set_bool(SL_RAIL_UTIL_COEX_OPT_MAC_AND_FORCE_HOLDOFFS, true);
  }
}

#endif//SLI_COEX_SUPPORTED

// -----------------------------------------------------------------------------
// DMP Tuning support

#if     SLI_DMP_TUNING_SUPPORTED

void emRadioEnableConfigScheduledCallback(bool enable)
{
  updateEvents(RAIL_EVENT_CONFIG_SCHEDULED,
               enable ? RAIL_EVENT_CONFIG_SCHEDULED : RAIL_EVENTS_NONE);
}

bool emRadioConfigScheduledCallbackEnabled(void)
{
  return ((currentEventConfig & RAIL_EVENT_CONFIG_SCHEDULED) != 0U);
}

// This API should only be called prior to sl_mac_lower_mac_init() or when
// the radio is OFF -- otherwise its new priorities won't be put
// into effect until the next time the radio gets turned on.
EmberStatus emberRadioSetSchedulerPriorities(const EmberMultiprotocolPriorities *priorities)
{
  RAIL_Version_t railVersion;
  RAIL_GetVersion(&railVersion, false);
  if (railVersion.multiprotocol) {
    radioSchedulerPriorityTable = *priorities;
    changeDynamicEvents();
    return EMBER_SUCCESS;
  } else {
    return EMBER_INVALID_CALL;
  }
}

EmberStatus emberRadioGetSchedulerPriorities(EmberMultiprotocolPriorities *priorities)
{
  RAIL_Version_t railVersion;
  RAIL_GetVersion(&railVersion, false);
  if (railVersion.multiprotocol) {
    *priorities = radioSchedulerPriorityTable;
    return EMBER_SUCCESS;
  } else {
    return EMBER_INVALID_CALL;
  }
}

EmberStatus emberRadioSetSchedulerSliptime(uint32_t slipTime)
{
  RAIL_Version_t railVersion;
  RAIL_GetVersion(&railVersion, false);
  if (railVersion.multiprotocol) {
    txSchedulerInfo.slipTime = slipTime;
    return EMBER_SUCCESS;
  } else {
    return EMBER_INVALID_CALL;
  }
}

EmberStatus emberRadioGetSchedulerSliptime(uint32_t *slipTime)
{
  RAIL_Version_t railVersion;
  RAIL_GetVersion(&railVersion, false);
  if (railVersion.multiprotocol) {
    if (slipTime != NULL) {
      *slipTime = txSchedulerInfo.slipTime;
    }
    return EMBER_SUCCESS;
  } else {
    return EMBER_INVALID_CALL;
  }
}

#endif//SLI_DMP_TUNING_SUPPORTED

// -----------------------------------------------------------------------------
// Antenna Diversity plugin support

#if     SLI_ANTDIV_SUPPORTED

#ifndef RAIL_RX_OPTIONS_ANTENNA
#define RAIL_RX_OPTIONS_ANTENNA \
  (RAIL_RX_OPTION_ANTENNA0 | RAIL_RX_OPTION_ANTENNA1)
#endif//RAIL_RX_OPTIONS_ANTENNA

static RAIL_Events_t getRxAntOptions(sl_rail_util_antenna_mode_t mode)
{
  switch (mode) {
    default:
    case SL_RAIL_UTIL_ANTENNA_MODE_DISABLED: // Leave antenna untouched (e.g. from Tx)
      return RAIL_RX_OPTIONS_NONE;
      break;
    case SL_RAIL_UTIL_ANTENNA_MODE_ENABLE1:
      return RAIL_RX_OPTION_ANTENNA0;
      break;
    case SL_RAIL_UTIL_ANTENNA_MODE_ENABLE2:
      return RAIL_RX_OPTION_ANTENNA1;
      break;
    case SL_RAIL_UTIL_ANTENNA_MODE_DIVERSITY: // Use radio config's diversity scheme
      return RAIL_RX_OPTIONS_ANTENNA;
      break;
  }
}

EmberStatus emRadioConfigRxAntenna(sl_rail_util_antenna_mode_t mode)
{
  if (connectRailHandle == NULL) {
    // This call is premature, before radio is initialized.
    // Defer to when we're re-called as part of sl_rail_util_plugin_config_2p4ghz_radio().
    return EMBER_SUCCESS;
  }
  // Tell RAIL what Rx antenna mode to use
  return (RAIL_ConfigRxOptions(connectRailHandle, RAIL_RX_OPTIONS_ANTENNA,
                               getRxAntOptions(mode))
          == RAIL_STATUS_NO_ERROR) ? EMBER_SUCCESS : EMBER_ERR_FATAL;
}

#endif//SLI_ANTDIV_SUPPORTED

#ifdef CSL_SUPPORT
static sl_status_t configureDutyCycling(bool enable)
{
  RAIL_Status_t rail_status = RAIL_STATUS_NO_ERROR;

  dutyCyclingEnabled = enable;

  RAIL_RxDutyCycleConfig_t dc_config = {
    .mode = RAIL_RX_CHANNEL_HOPPING_MODE_PREAMBLE_SENSE,
    .parameter = macCslChannelSampleMs * 1000,  // microseconds to receive
    .delayMode = RAIL_RX_CHANNEL_HOPPING_DELAY_MODE_STATIC,
    .delay = macCslPeriodMs * 1000              // microseconds off
  };

  // We must always idle RAIL before enabling or disabling duty cycling

  if (enable) {
    RAIL_Idle(connectRailHandle, RAIL_IDLE_ABORT, true);
    rail_status = RAIL_ConfigRxDutyCycle(connectRailHandle, &dc_config);
  } else {
    // We use RAIL_IDLE_FORCE_SHUTDOWN based on input from the RAIL team
    // (RAIL_IDLE_ABORT wans't working when disabling)
    RAIL_Idle(connectRailHandle, RAIL_IDLE_FORCE_SHUTDOWN, true);
  }

  if (rail_status == RAIL_STATUS_NO_ERROR) {
    rail_status = RAIL_EnableRxDutyCycle(connectRailHandle, enable);
  }

  return (rail_status == RAIL_STATUS_NO_ERROR) ? SL_STATUS_OK : SL_STATUS_FAIL;
}
#endif // CSL_SUPPORT

#ifdef CSL_SUPPORT
static void updateDutyCyclingConfig(void)
{
  if (dutyCyclingEnabled) {
    // Reconfigure Duty Cycling parameters
    sl_status_t status = configureDutyCycling(true);
    if (status == SL_STATUS_OK) {
      radioSetRx();
    }
  }
}
#endif

sl_status_t sl_mac_enable_duty_cycling(void)
{
#ifdef CSL_SUPPORT
  RAIL_Status_t rail_status;
  sl_status_t status;

  // Only the zigbee stack calls this function. Zigbee uses duty cycling for
  // unsynchronized CSL, which receives and acts on wake up frames.
  // First, we need to configure RAIL to pass up wake up frames to the lower MAC

  rail_status = RAIL_IEEE802154_AcceptFrames(connectRailHandle,
                                             (RAIL_IEEE802154_ACCEPT_STANDARD_FRAMES | RAIL_IEEE802154_ACCEPT_MULTIPURPOSE_FRAMES));
  if (rail_status != RAIL_STATUS_NO_ERROR) {
    return SL_STATUS_INITIALIZATION;
  }

  rail_status = RAIL_IEEE802154_ConfigEOptions(connectRailHandle, RAIL_IEEE802154_E_OPTION_GB868, RAIL_IEEE802154_E_OPTION_GB868);
  if (rail_status != RAIL_STATUS_NO_ERROR) {
    return SL_STATUS_INITIALIZATION;
  }

  status = configureDutyCycling(true);

  if (status == SL_STATUS_OK) {
    radioSetRx();
  }

  return status;
#else // CSL_SUPPORT
  return SL_STATUS_NOT_AVAILABLE;
#endif // CSL_SUPPORT
}

// CSL related APIs
sl_status_t sl_mac_set_mac_csl_max_period(uint8_t mac_index, uint16_t mac_csl_max_period_ms)
{
#ifdef CSL_SUPPORT
  UNUSED_VAR(mac_index);
  macCslMaxPeriodMs = mac_csl_max_period_ms;
  return SL_STATUS_OK;
#else // CSL_SUPPORT
  return SL_STATUS_NOT_AVAILABLE;
#endif // CSL_SUPPORT
}

uint16_t sl_mac_get_mac_csl_max_period(uint8_t mac_index)
{
#ifdef CSL_SUPPORT
  UNUSED_VAR(mac_index);
  return macCslMaxPeriodMs;
#else // CSL_SUPPORT
  return 0;
#endif // CSL_SUPPORT
}

sl_status_t sl_mac_set_mac_csl_period(uint8_t mac_index, uint16_t mac_csl_period_ms)
{
#ifdef CSL_SUPPORT
  UNUSED_VAR(mac_index);
  macCslPeriodMs = mac_csl_period_ms;
  updateDutyCyclingConfig();
  return SL_STATUS_OK;
#else // CSL_SUPPORT
  return SL_STATUS_NOT_AVAILABLE;
#endif // CSL_SUPPORT
}

uint16_t sl_mac_get_mac_csl_period(uint8_t mac_index)
{
#ifdef CSL_SUPPORT
  UNUSED_VAR(mac_index);
  return macCslPeriodMs;
#else // CSL_SUPPORT
  return 0;
#endif // CSL_SUPPORT
}

sl_status_t sl_mac_set_mac_csl_channel_sample(uint8_t mac_index, uint16_t mac_csl_channel_sample_ms)
{
#ifdef CSL_SUPPORT
  UNUSED_VAR(mac_index);
  macCslChannelSampleMs = mac_csl_channel_sample_ms;
  updateDutyCyclingConfig();
  return SL_STATUS_OK;
#else // CSL_SUPPORT
  return SL_STATUS_NOT_AVAILABLE;
#endif // CSL_SUPPORT
}

uint16_t sl_mac_get_mac_csl_channel_sample(uint8_t mac_index)
{
#ifdef CSL_SUPPORT
  UNUSED_VAR(mac_index);
  return macCslChannelSampleMs;
#else // CSL_SUPPORT
  return 0;
#endif // CSL_SUPPORT
}

#ifdef CSL_SUPPORT
bool isWakeupFrame(uint8_t *mac_frame, uint8_t *ie_data)
{
  // Get the frame control bytes
  sl_mac_long_frame_control_t *mac_frame_control = (sl_mac_long_frame_control_t *)&mac_frame[EMBER_MAC_HEADER_OFFSET];
  uint8_t idx = EMBER_MULTIPURPOSE_MAC_HEADER_SEQUENCE_NUMBER_OFFSET;

  if (mac_frame_control->frame_type == EMBER_MAC_HEADER_FC_FRAME_TYPE_MULTIPURPOSE) {
    // Get the Header IE
    if (mac_frame_control->ie_present == true) {
      // Check if Sequence Number is present
      if (mac_frame_control->seq_num_suppression == 0) {
        idx += 1;
      }

      // Check if the PAN ID is present
      if (mac_frame_control->pan_id_present != 0) {
        idx += sizeof(EmberPanId);
      }

      // Check the destination addressing mode
      if (mac_frame_control->dest_addr_mode == EMBER_MAC_ADDRESS_MODE_SHORT) {
        idx += sizeof(EmberNodeId);
      } else if (mac_frame_control->dest_addr_mode == EMBER_MAC_ADDRESS_MODE_LONG) {
        idx += EUI64_SIZE;
      }

      // Check the source addressing mode
      if (mac_frame_control->src_addr_mode == EMBER_MAC_ADDRESS_MODE_SHORT) {
        idx += sizeof(EmberNodeId);
      } else if (mac_frame_control->src_addr_mode == EMBER_MAC_ADDRESS_MODE_LONG) {
        idx += EUI64_SIZE;
      }

      // Verify the IE is for the Rendezvous Time IE and is valid
      sl_mac_header_ie_t *header_ie = (sl_mac_header_ie_t *)&mac_frame[idx];
      if ((header_ie->length == EMBER_802_15_4_IE_HEADER_LENGTH_RENDEZVOUS_TIME)
          && (header_ie->element_id == EMBER_802_15_4_IE_HEADER_ELEMENT_ID_RENDEZVOUS_TIME)) {
        idx += sizeof(sl_mac_header_ie_t);
        *ie_data = idx;
        return true;
      }
    }
  }

  return false;
}
#endif // CSL_SUPPORT

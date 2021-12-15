/***************************************************************************//**
 *
 * @file
 * @brief Scanning for beacons.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#define EVENT_CONTROL_SYSTEM
#endif
#include "hal/hal.h"
#include "sl_status.h"
#include "core/ember-stack.h"
#include "buffer_manager/buffer-management.h"
#include "buffer_manager/legacy-packet-buffer.h"
#include "mac-types.h"
#include "mac-header.h"
#include "lower-mac.h"
#include "upper-mac.h"
#include "scan.h"
#include "mac-command.h"
#include "event_control/event.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT
#ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
#include "openthread/error.h"
#include "openthread/platform/radio.h"
#endif
#if defined(UNIFIED_MAC_SCRIPTED_TEST)
#include "scripted_test_framework.h"
#define energyReadScriptCheck(rssiValue) \
  postTestCheck("emScanTimerIsr", "energyRead", "i", rssiValue)
#else
  #define energyReadScriptCheck(rssiValue)
#endif

#define UMAC_SCAN_DEBUG(x)
//#define UMAC_SCAN_DEBUG(x) x

//static / internal code
typedef uint8_t sl_network_scan_t;
enum {
  /** An energy scan for each channel looks for its RSSI value. */
  SL_ENERGY_SCAN,
  /** An active scan for each channel looks for available networks. */
  SL_ACTIVE_SCAN,
};

#define SL_MAX_SCAN_TYPE  SL_ACTIVE_SCAN
#define SYMBOLS_PER_SUPERFRAME      960
#define SYMBOLS_PER_ENERGY_READING    8 // we take a reading every 8 symbols
#define KICKSTART_DWELL_DURATION      1

// Energy scan results are stored in a buffer, with one byte for the RSSI
// and the next for the channel.
#define ENERGY_SCAN_RSSI_OFFSET    0
#define ENERGY_SCAN_CHANNEL_OFFSET 1
#define ENERGY_SCAN_RECORD_SIZE    2

#ifndef EVENT_CONTROL_SYSTEM
static void mac_scan_event_handler(EmberEvent *event);

EmberEvent sl_mac_scan_event = { {
                                   &emStackEventQueue,
                                   mac_scan_event_handler,
                                   emIsrEventMarker,
                                   #ifndef EMBER_TEST
                                   ""
                                   #else
                                   "MAC scan"
                                   #endif
                                 },
                                 NULL };
#define call_scan_event_handler() mac_scan_event_handler(&sl_mac_scan_event)
#else
EmberEventControl sl_mac_scan_event;
#define call_scan_event_handler() sl_mac_scan_event_handler()
#endif
Buffer sl_energy_scan_result_summary_buffer = NULL_BUFFER;
uint8_t energy_scan_result_summary_index = 0;

#define ENERGY_SCAN_RESULTS_SUMMARY_BUFFER_SIZE 52 //sToDo: seem to be only one reading, and chnnel id per channel (2 * 26)

// Internal state
static uint8_t  sl_scan_type;
static uint8_t  sl_next_channel;      // Next channel to scan.
static uint32_t sl_scan_frame_counter; // How many 'frames' left in the current scan.
static uint8_t  sl_scan_duration;     // Scan lasts 2 << (scan_duration + 1) frames
static uint32_t sl_scan_channel_mask;  // Channels we are scanning; this doubles as
//  an error mask; bits below nextChannel
//  indicate an error scanning that channel.
static uint8_t  sl_scan_transmit_retries; // Number of times we have tried to send
static sl_mac_scan_request_result_t  sl_go_to_next_channel_decision = SL_MAC_SCAN_GOTO_NEXT_CHANNEL;// ToDo: not sure how to initialize this correctly

static uint8_t sl_tag = 0;

static uint8_t sl_scanning_mac_index = 0;

// if true, sets the radio PAN ID to 0xFFFF when scanning. Zigbee's ZLL wants
// to preserve the current PAN when scanning because it does things with it
// during ZLL scanning. All other scan types are okay with having the radio PAN
// to be 0xFFFF when scanning.
static bool broadcast_pan_when_scanning;

//variables for energy_scan rolling average, and rolling variance
#define SLI_FIXED_POINT_ARITHMATICS_SHIFT 8
// rolling window  size = 2^(ENERGY_READS_WINDOW_LOG)
// this value is dependent on SLI_FIXED_POINT_ARITHMATICS_SHIFT,
// and could result to inaccurate estimations if changed randomly
#define ENERGY_READS_WINDOW_LOG 4
#define ENERGY_READS_MIN 127
#define ENERGY_READS_MAX -128
static int16_t energy_reads_average;
static uint16_t energy_reads_variance;
static int8_t energy_reads_min;
static int8_t energy_reads_max;
static uint32_t energy_reads_count;
/**
 * @brief A bitmask to scan all 2.4 GHz 802.15.4 channels.
 */
#define SL_MAC_ALL_802_15_4_CHANNELS_MASK 0x07FFF800UL

/**
 * @brief A bitmask for the channel page within a channel mask.
 */
#define SL_ALL_CHANNEL_PAGE_MASK 0xF8000000UL

/**
 * @brief SubGhz channel bitmasks for page 29.
 */
#define SL_ALL_SUBGHZ_CHANNELS_MASK_FOR_PAGES_29 0x1FF

/**
 * @brief The channel page value used to indicate just the 2.4GHz channels.
 */
#define SL_NO_CHANNEL_PAGE_IN_USE           0

#define SL_MIN_802_15_4_CHANNEL_NUMBER  11
#define SL_MAX_802_15_4_CHANNEL_NUMBER  26
/**
 * @brief The minimum SubGhz channel number is 0.
 */
#define SL_MIN_SUBGHZ_CHANNEL_NUMBER 0
#define SL_MAC_MAX_SCAN_DURATION  14
#define SL_MAC_RECOMMENDED_SCAN_DURATION 3
#define SL_MAC_SUBGHZ_SCAN_DURATION 5

#define GET_MIN_CHANNEL_NUMBER_ON_CURRENT_PAGE(macPgChan)  emMacPgChanPg(macPgChan) == 0 \
  ? SL_MIN_802_15_4_CHANNEL_NUMBER                                                       \
  : SL_MIN_SUBGHZ_CHANNEL_NUMBER

void sl_assert(const char *file, int line)
{
  (void)file;  // Unused parameter
  (void)line;  // Unused parameter
  // Wait forever until the watchdog fires
  while (1) ;
}

#if defined(NDEBUG)
#define SL_ASSERT(expr)
#else
#if defined(USER_ASSERT)
#define SL_ASSERT(expr)   ((expr) ? ((void)0) : USER_ASSERT(__FILE__, __LINE__))
#else
#define SL_ASSERT(expr)   ((expr) ? ((void)0) : sl_assert(__FILE__, __LINE__))
#endif
#endif

static sl_status_t mac_prepare_for_scan(sl_network_scan_t scanType,
                                        sl_channel_mask_t mask,
                                        uint8_t scan_duration,
                                        int8_t tx_power,
                                        bool set_pan_id_to_broadcast_pan);

static void mac_shutdown_scan_start(uint8_t mac_index);

static bool scan_next_channel(void);
static sl_status_t start_channel_scan(void);
static void cleanup_scan_state(void);
static void report_energy_scan_rssi_per_channel(void);

static sl_status_t scan_dwell(uint8_t mac_index, uint16_t duration)
{
  if (duration != 0xFFFF) {
    return sl_mac_schedule_symbol_timer(MAC_INDEX, sl_scan_timer_handler, duration);
  }
  return SL_STATUS_INVALID_PARAMETER;
}

static void tx_complete_callback(uint8_t mac_index, sl_status_t status, PacketHeader packet, uint8_t tag)
{
  UMAC_SCAN_DEBUG(fprintf(stderr, "\ntx_complete_callback status %x sl_scan_channel_mask %4x\n", status, sl_scan_channel_mask));

  // ToDo: do we need a check  on packet type/tag?
  if (sl_scan_type != SL_ACTIVE_SCAN) {
    // This packet was not sent as part of an active scan.
    return;
  }

  if (status == SL_STATUS_OK) {
    // When the scan is complete, any 0's in this mask represent send successes.
    sl_scan_channel_mask &= ~((uint32_t) BIT32(sl_mac_lower_mac_get_radio_channel(MAC_INDEX)));
    if (scan_dwell(MAC_INDEX, KICKSTART_DWELL_DURATION) != SL_STATUS_OK ) {
      // XXXJAR SL_ASSERT(false);
    }
  } else {
    // attempt to retransmit 2 more times before failure
    sl_scan_transmit_retries++;

    if (3 <= sl_scan_transmit_retries
        || start_channel_scan() != SL_STATUS_OK) {
      call_scan_event_handler();
    }
  }
  return;
}
/*
 * the following function is not internally used by zigbee, but it is kept inline
 * with active_scan_request_callback on zigbee side, if used by customer through start_active_scasn
 */
static sl_mac_scan_request_result_t active_scan_default_beacon_request_callback(uint8_t channel, Buffer *scan_packet)
{
  // unlike the old code we have the current channel when we get here, and not the next channel
  // so we need the following to check if enahnced beacon request on subghz send is needed
  channel++;
  if (*scan_packet == NULL_BUFFER) { // first time calling this callback druring scan
    #if defined(MAC_DUAL_PRESENT) || SINGLE_PHY_MULTIPAGE_SUPPORT
    if (emMacPgChanPg(channel)) {
      Buffer payload_info_elements = sli_mac_make_enhanced_beacon_request_payload_info(0, 0, true /* first_join */);
      *scan_packet = sl_mac_make_enhanced_beacon_request(sl_scanning_mac_index /* mac_index */, 0 /*nwk_index*/, payload_info_elements);
      payload_info_elements = NULL_BUFFER;
    } else
    #endif
    {
      *scan_packet = sl_mac_make_beacon_request(sl_scanning_mac_index /* mac_index */, 0 /*nwk_index*/);
    }
    if (*scan_packet == NULL_BUFFER) {
      return SL_MAC_SCAN_ABORT;
    }
  }

  return SL_MAC_SCAN_GOTO_NEXT_CHANNEL;
}

//// public APIs

sl_mac_receive_callback_t sl_mac_active_response_callback = NULL;
sl_mac_scan_complete_callback_t sl_mac_scan_complete_callback = NULL;
sli_mac_energy_scan_complete_callback_t sli_mac_energy_scan_complete_callback = NULL;
sl_mac_energy_scan_result_callback_t sl_mac_energy_response_callback = NULL;
sl_mac_send_scan_request_callback_t sl_mac_scan_request_callback = active_scan_default_beacon_request_callback;

sl_status_t sl_mac_active_scan(sl_channel_mask_t mask,
                               uint8_t scan_duration,
                               int8_t tx_power,
                               sl_mac_receive_callback_t response_callback,
                               sl_mac_scan_complete_callback_t scan_complete_callback)
{
  if (sl_mac_scan_pending()) {
    return SL_STATUS_MAC_SCANNING;
  }

  if (scan_complete_callback == NULL) {
    // since we use this handlere to decide if there is a scan pending or not,
    // it is important to make sure it is not NULL
    return SL_STATUS_INVALID_HANDLE;
  }

  sl_mac_active_response_callback = response_callback;
  sl_mac_scan_complete_callback = scan_complete_callback;
  return mac_prepare_for_scan(SL_ACTIVE_SCAN,
                              mask,
                              scan_duration,
                              tx_power,
                              true);  // set_pan_id_to_broadcast_pan
}

sl_status_t sl_mac_energy_scan(sl_channel_mask_t mask,
                               uint8_t scan_duration,
                               sl_mac_energy_scan_result_callback_t response_callback,
                               sl_mac_scan_complete_callback_t scan_complete_callback)
{
  if (sl_mac_scan_pending()) {
    return SL_STATUS_MAC_SCANNING;
  }

  if (scan_complete_callback == NULL) {
    // since we use this handlere to decide if there is a scan pending or not,
    // it is important to make sure it is not NULL
    return SL_STATUS_INVALID_HANDLE;
  }

  sl_mac_energy_response_callback = response_callback;
  sl_mac_scan_complete_callback = scan_complete_callback;
  return mac_prepare_for_scan(SL_ENERGY_SCAN,
                              mask,
                              scan_duration,
                              3,      // tx_power - not used
                              true);  // set_pan_id_to_broadcast_pan
}

sl_status_t sli_mac_energy_scan(sl_channel_mask_t mask,
                                uint8_t scan_duration,
                                sli_mac_energy_scan_complete_callback_t scan_complete_callback)
{
  if (sl_mac_scan_pending()) {
    return SL_STATUS_MAC_SCANNING;
  }

  if (scan_complete_callback == NULL) {
    // since we use this handlere to decide if there is a scan pending or not,
    // it is important to make sure it is not NULL
    return SL_STATUS_INVALID_HANDLE;
  }

  sli_mac_energy_scan_complete_callback = scan_complete_callback;
  return mac_prepare_for_scan(SL_ENERGY_SCAN,
                              mask,
                              scan_duration,
                              3,      // tx_power - not used
                              true);  // set_pan_id_to_broadcast_pan
}

sl_status_t sl_mac_raw_active_scan(sl_channel_mask_t mask,
                                   uint8_t scan_duration,
                                   sl_mac_send_scan_request_callback_t beacon_request_callback,
                                   int8_t tx_power,
                                   sl_mac_receive_callback_t response_callback,
                                   sl_mac_scan_complete_callback_t scan_complete_callback,
                                   bool set_pan_id_to_broadcast_pan)
{
  UMAC_SCAN_DEBUG(fprintf(stderr, "\nsl_mac_raw_active_scan mask %4x sl_mac_scan_pending() %d \n", mask, sl_mac_scan_pending()));

  if (sl_mac_scan_pending()) {
    return SL_STATUS_MAC_SCANNING;
  }

  if (scan_complete_callback == NULL) {
    // since we use this handlere to decide if there is a scan pending or not,
    // it is important to make sure it is not NULL
    return SL_STATUS_INVALID_HANDLE;
  }

  if (beacon_request_callback == NULL) {
    return SL_STATUS_INVALID_PARAMETER; // can also treat it just like default active scan
  } else {
    sl_mac_scan_request_callback = beacon_request_callback;
  }
  sl_mac_active_response_callback = response_callback;
  sl_mac_scan_complete_callback = scan_complete_callback;
  return mac_prepare_for_scan(SL_ACTIVE_SCAN,
                              mask,
                              scan_duration,
                              tx_power,
                              set_pan_id_to_broadcast_pan);
}

// it is a fake scan to enable us to send/receive beacon-req/beacon on alt-mac interface
// by ptting the umac mode in scan_pending

sl_status_t sli_mac_alt_mac_scan(sl_mac_scan_complete_callback_t scan_complete_callback)
{
  if (sl_mac_scan_pending()) {
    return SL_STATUS_MAC_SCANNING;
  }

  if (scan_complete_callback == NULL) {
    // since we use this handlere to decide if there is a scan pending or not,
    // it is important to make sure it is not NULL
    return SL_STATUS_INVALID_HANDLE;
  }
  sl_mac_scan_complete_callback = scan_complete_callback;
  return SL_STATUS_OK;
}

// Returns whether a scan is in progress
bool sl_mac_scan_pending()
{
  return (sl_mac_scan_complete_callback
          || sli_mac_energy_scan_complete_callback);
}

void sl_mac_mark_scan_buffer(void)
{
  emMarkBuffer(&sl_energy_scan_result_summary_buffer);
}
//static functions implementation

void cleanup_scan_state()
{
  sl_mac_active_response_callback = NULL;
  sl_mac_scan_complete_callback = NULL;
  sli_mac_energy_scan_complete_callback = NULL;
  sl_mac_scan_request_callback = active_scan_default_beacon_request_callback;
  sl_go_to_next_channel_decision = SL_MAC_SCAN_GOTO_NEXT_CHANNEL;   // ToDo: correct initialization value
  sl_scan_channel_mask = 0;
}

sl_status_t mac_prepare_for_scan(sl_network_scan_t scanType,
                                 sl_channel_mask_t mask,
                                 uint8_t scan_duration,
                                 int8_t tx_power,
                                 bool set_pan_id_to_broadcast_pan)
{
  UMAC_SCAN_DEBUG(fprintf(stderr, "\nmac_prepare_for_scan %x mask %4X scan_duration %d\n", scanType, mask, scan_duration));
  //-------------------------------------
//--------checking the scan type-----
//-------------------------------------
  if (scanType > SL_MAX_SCAN_TYPE) {
    UMAC_SCAN_DEBUG(fprintf(stderr, "\nfailed due to wrong scan type\n"));
    cleanup_scan_state();
    return SL_STATUS_MAC_INCORRECT_SCAN_TYPE;
  }

  //-------------------------------------
//--------checking the scan duration-----
//-------------------------------------
  if (scan_duration > SL_MAC_MAX_SCAN_DURATION) {
    UMAC_SCAN_DEBUG(fprintf(stderr, "\nfailed due to wrong scan duration\n"));
    cleanup_scan_state();
    return SL_STATUS_BAD_SCAN_DURATION;
  }
  //----------------------------------------------------------
//--------checking the specicific requiremnet per scan type-----
//------------------------------------------------------------

  if (scanType == SL_ACTIVE_SCAN ) {
    // this does not come from the public API anymore
    if (sl_mac_lower_mac_set_radio_power(0, tx_power) != SL_STATUS_OK) {
      UMAC_SCAN_DEBUG(fprintf(stderr, "\nfailed to set radio power to %d\n", tx_power));
      cleanup_scan_state();
      return SL_STATUS_INVALID_PARAMETER;
    }
  } else if (scanType == SL_ENERGY_SCAN) {
    energy_reads_average = ENERGY_READS_MIN << SLI_FIXED_POINT_ARITHMATICS_SHIFT;
    energy_reads_min = ENERGY_READS_MIN;
    energy_reads_max = ENERGY_READS_MAX;
    energy_reads_variance = 0;
    energy_reads_count = 0;
    //if we need the results as a summary
    if (sli_mac_energy_scan_complete_callback != NULL) {
      sl_energy_scan_result_summary_buffer =
        emAllocateBuffer(ENERGY_SCAN_RESULTS_SUMMARY_BUFFER_SIZE);
      if (sl_energy_scan_result_summary_buffer == NULL_BUFFER) {
        cleanup_scan_state();
        return SL_STATUS_FAIL;
      }
    }
  }

//-------------------------------------
//--------checking the channel mask-----
//-------------------------------------
  uint8_t channel_page = SL_NO_CHANNEL_PAGE_IN_USE;

  // If device has phy support for subghz band, then scanning can be done on either of
// the bands (2.4Ghz or SubGhz).
#if (defined(EMBER_TEST) || SINGLE_PHY_MULTIPAGE_SUPPORT || defined(MULTI_MAC_PRESENT))

  // Validate channel mask depending on
  if (mask & SL_ALL_CHANNEL_PAGE_MASK) {
    //subGhz channel page
#ifdef MAC_DUAL_PRESENT
    sl_scanning_mac_index = PHY_INDEX_PRO2PLUS;
#endif  //MAC_DUAL_PRESENT

    channel_page = (mask & SL_ALL_CHANNEL_PAGE_MASK) >> SL_MAX_CHANNELS_PER_PAGE;

    // Validate channel_page range
    if (channel_page < 28 || channel_page > 31) {
      return SL_STATUS_INVALID_CHANNEL_MASK;
    }
    // There are only 8 channels on page 29.
    if (channel_page == 29) {
      if ((mask & SL_ALL_SUBGHZ_CHANNELS_MASK_FOR_PAGES_29)
          != (mask & (~SL_ALL_CHANNEL_PAGE_MASK))) {
        return SL_STATUS_INVALID_CHANNEL_MASK;
      }
    }
  } else
#endif
  {
#ifdef MAC_DUAL_PRESENT
    sl_scanning_mac_index = PHY_INDEX_NATIVE;
#endif  //MAC_DUAL_PRESENT
    // Make sure provided channel mask is valid
    if ((mask & SL_MAC_ALL_802_15_4_CHANNELS_MASK) != mask) {
      UMAC_SCAN_DEBUG(fprintf(stderr, "\nfailed to provide correct channel mask\n"));
      cleanup_scan_state();
      return SL_STATUS_INVALID_CHANNEL_MASK;
    }
  }

  if (mask == 0) {
    int8_t channel = sl_mac_lower_mac_get_radio_channel(sl_scanning_mac_index);
#if (defined(EMBER_TEST) || SINGLE_PHY_MULTIPAGE_SUPPORT || defined(MULTI_MAC_PRESENT))
    channel_page = emMacPgChanPg(channel);
#endif
    mask = PG_CH_BITMASK32(channel);
    scan_duration = channel_page ? SL_MAC_SUBGHZ_SCAN_DURATION
                    : SL_MAC_RECOMMENDED_SCAN_DURATION;
  }

//-------------------------------------
//--------final step: scan variable settings, and mac suspend-----
//-------------------------------------

  sl_scan_type = scanType;
  sl_scan_duration = scan_duration;

  sl_scan_channel_mask = mask & (~SL_ALL_CHANNEL_PAGE_MASK);
  sl_next_channel = emMacPgChan(channel_page, 0); // no support for actual subgig yet

  if (sl_mac_suspend_operation(sl_scanning_mac_index, mac_shutdown_scan_start, sl_mac_active_response_callback) != SL_STATUS_OK) {
    UMAC_SCAN_DEBUG(fprintf(stderr, "\nfaile dto do sl_mac_suspend_operation\n"));
    cleanup_scan_state();
    return SL_STATUS_BUSY;
  }

  broadcast_pan_when_scanning = set_pan_id_to_broadcast_pan;

  return SL_STATUS_OK;
}

void mac_shutdown_scan_start(uint8_t mac_index)
{
  if (sl_scan_type  == SL_ENERGY_SCAN ) {
    sl_mac_lower_mac_set_radio_idle_mode(MAC_INDEX, EMBER_RADIO_POWER_MODE_ED_ON);
  } else {
    sl_mac_lower_mac_set_radio_idle_mode(MAC_INDEX, EMBER_RADIO_POWER_MODE_RX_ON);
  }

  // Most scans want our local PAN ID to be 0xFFFF. ZLL is one example that does
  // not.
  if (broadcast_pan_when_scanning) {
    // DUAL_PAN - default to setting to the 0th rail index?
    sl_mac_lower_mac_set_pan_id(MAC_INDEX, 0, EMBER_BROADCAST_PAN_ID);
  }
  call_scan_event_handler();
}

// When the event runs we report any new energy results and try the next
// channel. If there is no next channel we report any errors and shut down.
#ifndef EVENT_CONTROL_SYSTEM
void mac_scan_event_handler(EmberEvent *event)
#else
void sl_mac_scan_event_handler(void)
#endif
{
  sli_mac_inactivate_event(sl_mac_scan_event);
  if (sl_scan_type == SL_ENERGY_SCAN) {
    report_energy_scan_rssi_per_channel();
  }

  if (!scan_next_channel()) {
    if (sl_scan_type == SL_ACTIVE_SCAN ) {
      uint8_t i;
      for (i = GET_MIN_CHANNEL_NUMBER_ON_CURRENT_PAGE(sl_next_channel);
           i <= SL_MAX_802_15_4_CHANNEL_NUMBER;
           i++) {
        if ((sl_scan_channel_mask & (uint32_t) BIT32(i)) != 0) {
          sl_mac_scan_complete_callback_t callback = sl_mac_scan_complete_callback;
          if (callback != NULL) {
            callback(SL_STATUS_FAIL, sl_scan_channel_mask);
          }
        }
      }
    } else if (sl_scan_type == SL_ENERGY_SCAN) {
    } // end of if sl_energy_scan
    sli_scan_stop();
  }
}

void sli_scan_stop(void)
{
  UMAC_SCAN_DEBUG(fprintf(stderr, "\nsli_scan_stop\n"));
  sl_mac_scan_complete_callback_t active_or_extenal_energy_callback = sl_mac_scan_complete_callback;
  sli_mac_energy_scan_complete_callback_t internal_energy_callback = sli_mac_energy_scan_complete_callback;

  // could be called twice, with a failure above? but this would be the final call
  if (sl_energy_scan_result_summary_buffer != NULL_BUFFER) {
    emSetBufferLength(sl_energy_scan_result_summary_buffer, energy_scan_result_summary_index);
  }
  energy_scan_result_summary_index = 0;
  cleanup_scan_state();

  sl_mac_resume_operation(sl_scanning_mac_index);

  //call the callback as the last action, because callback might start a new scan
  if (active_or_extenal_energy_callback != NULL) {
    active_or_extenal_energy_callback(SL_STATUS_OK, sl_scan_channel_mask);
  }

  if (internal_energy_callback != NULL) {
    internal_energy_callback(sl_energy_scan_result_summary_buffer);
    sl_energy_scan_result_summary_buffer = EMBER_NULL_MESSAGE_BUFFER;
  }
}

// When the timer goes off we're done if that was the last frame and
// otherwise go around again.

void sl_scan_timer_handler(void)
{
  uint16_t next_timeout = 0;

  if (sl_scan_type == SL_ENERGY_SCAN) {
    // Energy Scans aren't kick-started but read RSSI after each dwell.
    int8_t currentRSSI;
    //sToDo: we might need to change teh logic here, to contain the channel info in the result buf, or rebuild buf

    currentRSSI  = sl_mac_radio_energy_detection(sl_scanning_mac_index);
    energy_reads_count++;

    energyReadScriptCheck(currentRSSI);

    if (energy_reads_max < currentRSSI) {
      energy_reads_max = currentRSSI;
    }

    if (energy_reads_min > currentRSSI) {
      energy_reads_min = currentRSSI;
    }
    if (energy_reads_count == 1) {
      //first  read
      energy_reads_average = (uint16_t) (((uint16_t) currentRSSI) << SLI_FIXED_POINT_ARITHMATICS_SHIFT);
    } else {
      int16_t prv_avg = energy_reads_average;

      // new rolling avg = ((win-1)* old + currentRSSI)/win
      energy_reads_average = prv_avg
                             - ((uint16_t) (prv_avg >> ENERGY_READS_WINDOW_LOG))
                             + ((uint16_t) (((uint16_t) currentRSSI) << ENERGY_READS_WINDOW_LOG));
      // for variance I am using the Inceremntal algorithm
      // it would perhaps be better if mean uses  teh same algorithm,
      // but without the floating point logic I could not get the precision right
      // https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Weighted_incremental_algorithm
      energy_reads_variance += ((currentRSSI - (energy_reads_average >> SLI_FIXED_POINT_ARITHMATICS_SHIFT)) * (currentRSSI - (prv_avg >> SLI_FIXED_POINT_ARITHMATICS_SHIFT)));
    }

    // *next_incoming_rssi++ = currentRSSI;
    if (sl_scan_frame_counter != 0) {
      next_timeout = SYMBOLS_PER_ENERGY_READING;
    }
  } else if (sl_scan_frame_counter != 0) {     /*other scan types*/
    next_timeout = SYMBOLS_PER_SUPERFRAME;
  }

  UMAC_SCAN_DEBUG(fprintf(stderr, "\nsl_scan_timer_handler sl_scan_frame_counter %d next_timeout %d\n", sl_scan_frame_counter, next_timeout));

  if (next_timeout == 0) {
    // Enable the scan event, which will scan the next channel.
    if (!sli_mac_event_is_active(sl_mac_scan_event)) {
      sli_mac_activate_event(sl_mac_scan_event);
    }
  } else {
    scan_dwell(sl_scanning_mac_index, next_timeout);
    sl_scan_frame_counter--;
  }
}

//----------------------------------------------------------------
static sl_mac_scan_request_result_t go_to_next_scan_channel(uint8_t channel)
{
  return sl_go_to_next_channel_decision;
}

static uint8_t get_next_scan_channel(uint8_t channel)
{
  UMAC_SCAN_DEBUG(fprintf(stderr, "\n get_next_scan_channel %d sl_go_to_next_channel_decision  %x == SL_MAC_SCAN_REQUEST_STAY_ON_CHANNEL %x\n",
                          sl_next_channel, sl_go_to_next_channel_decision, SL_MAC_SCAN_REQUEST_STAY_ON_CHANNEL));

  if (sl_go_to_next_channel_decision == SL_MAC_SCAN_REQUEST_STAY_ON_CHANNEL ) {
    return channel;
  } else if (sl_go_to_next_channel_decision == SL_MAC_SCAN_GOTO_NEXT_CHANNEL ) {
    return channel + 1;
  } else {
    return SL_MAX_802_15_4_CHANNEL_NUMBER  + 1;
  }
}

//
// Returns true if succeeds in finding a channel to scan.
static bool scan_next_channel(void)
{
  UMAC_SCAN_DEBUG(fprintf(stderr, "\n scan_next_channel %d \n",
                          sl_next_channel));

  if (SL_MAX_802_15_4_CHANNEL_NUMBER < emMacPgChanCh(sl_next_channel)) {
    return false;
  }

  if (go_to_next_scan_channel(sl_next_channel) == SL_MAC_SCAN_GOTO_NEXT_CHANNEL ) {
    while ((sl_scan_channel_mask & (uint32_t) BIT32(emMacPgChanCh(sl_next_channel))) == 0 ) {
      sl_next_channel += 1;

      if (SL_MAX_802_15_4_CHANNEL_NUMBER < emMacPgChanCh(sl_next_channel)) {
        return false;
      }
    }
  }

  if (sl_next_channel != sl_mac_lower_mac_get_radio_channel(sl_scanning_mac_index)) {
    if (sl_mac_lower_mac_set_radio_channel(sl_scanning_mac_index, (sl_next_channel)) != SL_STATUS_OK) {
      return false;
    }
  }

  sl_scan_transmit_retries = 0;
  return start_channel_scan() == SL_STATUS_OK;
}

static sl_status_t start_channel_scan(void)
{
  // this must be initialized first, since even though it is overridden
  //  in some cases, the default may be used in the scaling.
  sl_scan_frame_counter = BIT32(sl_scan_duration) + 1;

  UMAC_SCAN_DEBUG(fprintf(stderr, "\n start_channel_scan scan type %2x initial duration(sl_scan_frame_counter) %d\n", sl_scan_type, sl_scan_frame_counter));

  sl_status_t status = SL_STATUS_OK;
  Buffer sl_scan_packet = NULL_BUFFER;

  switch (sl_scan_type) {
    case SL_ACTIVE_SCAN:
      sl_go_to_next_channel_decision = sl_mac_scan_request_callback(sl_next_channel, &sl_scan_packet);
      if (sl_scan_packet != NULL_BUFFER) {
        status = sl_mac_submit(0, sl_mac_nwk_index(sl_scan_packet), sl_scan_packet, TRANSMIT_PRIORITY_BYPASS_SHUTDOWN, tx_complete_callback, sl_tag);
      }
      sl_next_channel = get_next_scan_channel(sl_next_channel);

      UMAC_SCAN_DEBUG(fprintf(stderr, "\n start_channel_scan submit status %x\n", status));
      return status;
    case SL_ENERGY_SCAN:
      // During energy scans we stop every few symbols to take an RSSI reading,
      // which is done by increasing the frame count and shortening the frames.
      // scanFrameCounter normally accounts for the kickstart, but we don't do
      // that for energy scans, hence the -1:
      sl_scan_frame_counter =
        sl_scan_frame_counter * (SYMBOLS_PER_SUPERFRAME
                                 / SYMBOLS_PER_ENERGY_READING) - 1;

#ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
      otError error = otPlatRadioEnergyScan(NULL, sl_next_channel, 200);
      status = (error == OT_ERROR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
#else
      status = scan_dwell(sl_scanning_mac_index, SYMBOLS_PER_ENERGY_READING);
#endif
      // energy detection
      sl_next_channel = get_next_scan_channel(sl_next_channel);
      return status;

    default:
      SL_ASSERT(0);
      return SL_STATUS_FAIL;
  }
}

static void report_energy_scan_rssi_per_channel(void)
{
  uint8_t channel = sl_mac_lower_mac_get_radio_channel(sl_scanning_mac_index);
  // end of while loop
  if (energy_reads_count) {
    energy_reads_variance = (energy_reads_count > 1)
                            ? (uint16_t)(energy_reads_variance / (energy_reads_count - 1)) : 0;

    sl_mac_energy_scan_result_callback_t callback = sl_mac_energy_response_callback;
    if (callback != NULL) {
      callback(channel, energy_reads_min, energy_reads_max, energy_reads_average >> SLI_FIXED_POINT_ARITHMATICS_SHIFT);
    }
    if (sli_mac_energy_scan_complete_callback != NULL
        &&  ((energy_scan_result_summary_index +  2) < ENERGY_SCAN_RESULTS_SUMMARY_BUFFER_SIZE)  ) {  //sToDo: we might need to change the logic here, to contain the channel info in the result buf, or rebuild buf
      //we probably need the results in the form of a summarized result buffer over all the channels for zigbee internal OTA energy scan response
      int8_t* energy_scan_result_summary_buffer_ptr = (int8_t*)emGetBufferPointer(sl_energy_scan_result_summary_buffer);
      energy_scan_result_summary_buffer_ptr[energy_scan_result_summary_index++] = energy_reads_max;
      energy_scan_result_summary_buffer_ptr[energy_scan_result_summary_index++] = channel;
    }

    energy_reads_average = ENERGY_READS_MIN << SLI_FIXED_POINT_ARITHMATICS_SHIFT;
    energy_reads_min = ENERGY_READS_MIN;
    energy_reads_max = ENERGY_READS_MAX;
    energy_reads_variance = 0;
    energy_reads_count = 0;
  }
}

#ifdef SL_CATALOG_LOWER_MAC_SPINEL_PRESENT
void sli_set_energy_scan_results(int8_t rssiValue)
{
  energy_reads_average = rssiValue;
  energy_reads_min = rssiValue;
  energy_reads_max = rssiValue;
  energy_reads_count = 1;

  if (!sli_mac_event_is_active(sl_mac_scan_event)) {
    sli_mac_activate_event(sl_mac_scan_event);
  }
}
#endif
